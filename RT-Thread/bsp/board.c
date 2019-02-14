/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
#include "board.h"
#include <rthw.h>
#include <rtthread.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"
#include "touch_043.h"
#include "touch_iic.h"
#include "lcd_rgb.h"

#if 0

//systick��ؼĴ��������Լ���ʼ������
#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemCoreClockUpdate(void);

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }
    
    _SYSTICK_LOAD = ticks - 1; 
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;  
    
    return 0;
}
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1536
static uint32_t rt_heap[RT_HEAP_SIZE];	// heap default size: 6K(1536 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
* @brief ������Ӳ����ʼ������
* @param ��
* @retval ��
*
* @attention
* RTT �ѿ�������صĳ�ʼ������ͳһ�ŵ� board.c �ļ���ʵ�֣�
* ��Ȼ���������Щ����ͳһ�ŵ� main.c �ļ�Ҳ�ǿ��Եġ�
*/
void rt_hw_board_init()//RTT�������ã�ʱ�Ӻʹ���
{	
#if 0
	/* ����ϵͳʱ�� */
	SystemCoreClockUpdate(); //�̼����ṩ
	
	/* SysTick ��ʼ�� */
	_SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);  
#endif	
	SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );//ʹ�ù̼����systick��ʼ��
	//Ӳ����ʼ��
	Usart1_Config();//���ڳ�ʼ��
	SDRAM_Init();//SDRAM��ʼ��
	LED_Init();//����LED�Ƴ�ʼ��
	Touch_Init();		//��������ʼ��
	if(SDRAM_Test())
	{
		printf("SDRAM init Success\n");
	}
	else
	{
		printf("SDRAM init fail\n");
	}
	LCD_Init();			// LCD��������ʼ��
	
	
	/*Ӳ�� BSP ��ʼ��ͳͳ����������� LED�����ڣ� LCD ��*/ 
	
   /* ���������ʼ������ (use INIT_BOARD_EXPORT())  */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();   
#endif
   /*����̨���ú���,��Ҫ������rt_kprintf()������������ݾ����ʲô�豸��ӡ*/
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);  //���ڿ�service.c����ʵ��
#endif
    /*�ڴ��ʼ������ mem.c����ʵ��*/
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());  
#endif
}

extern u32 TimingDelay;//delay.c��ͨ����¼�жϴ����ﵽ��ʱ
 /**
 * @brief SysTick �жϷ�����
 * @param ��
 * @retval ��
 *
 * @attention
 * SysTick �жϷ������ڹ̼����ļ� stm32f10x_it.c ��Ҳ�����ˣ�������
 * �� board.c ���ֶ���һ�Σ���ô�����ʱ�������ظ�����Ĵ��󣬽��
 * �����ǿ��԰� stm32f10x_it.c �е�ע�ͻ���ɾ�����ɡ�
 */
void SysTick_Handler(void)  
{
	/* �����ж� */
	rt_interrupt_enter();
	if (TimingDelay != 0x00) 
	{
		TimingDelay--;
	}
	/* ����ʱ�� */
	rt_tick_increase();
	/* �뿪�ж� */
	rt_interrupt_leave();
}


/**
* @brief ��ӳ�䴮�� DEBUG_USARTx �� rt_kprintf()����
* Note�� DEBUG_USARTx ���� bsp_usart.h �ж���ĺ꣬Ĭ��ʹ�ô��� 1
* @param str��Ҫ��������ڵ��ַ���
* @retval ��
*
* @attention
*
*/
void rt_hw_console_output(const char *str)
{
	/* �����ٽ�� */
 rt_enter_critical();

 /* ֱ���ַ������� */
 while (*str!='\0')
 {
 /* ���� */
	if (*str=='\n')
 {
	 USART_SendData(DEBUGUSART, '\r');
	 while (USART_GetFlagStatus(DEBUGUSART, USART_FLAG_TXE) == RESET);
	 }

	 USART_SendData(DEBUGUSART, *str++);
	 while (USART_GetFlagStatus(DEBUGUSART, USART_FLAG_TXE) == RESET);
	 }
	 /* �˳��ٽ�� */
	 rt_exit_critical();
 }
