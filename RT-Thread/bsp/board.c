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

//systick相关寄存器定义以及初始化函数
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
* @brief 开发板硬件初始化函数
* @param 无
* @retval 无
*
* @attention
* RTT 把开发板相关的初始化函数统一放到 board.c 文件中实现，
* 当然，你想把这些函数统一放到 main.c 文件也是可以的。
*/
void rt_hw_board_init()//RTT启动调用，时钟和串口
{	
#if 0
	/* 更新系统时钟 */
	SystemCoreClockUpdate(); //固件库提供
	
	/* SysTick 初始化 */
	_SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);  
#endif	
	SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );//使用固件库的systick初始化
	//硬件初始化
	Usart1_Config();//串口初始化
	SDRAM_Init();//SDRAM初始化
	LED_Init();//板载LED灯初始化
	Touch_Init();		//触摸屏初始化
	if(SDRAM_Test())
	{
		printf("SDRAM init Success\n");
	}
	else
	{
		printf("SDRAM init fail\n");
	}
	LCD_Init();			// LCD控制器初始化
	
	
	/*硬件 BSP 初始化统统放在这里，比如 LED，串口， LCD 等*/ 
	
   /* 调用组件初始化函数 (use INIT_BOARD_EXPORT())  */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();   
#endif
   /*控制台设置函数,主要是配置rt_kprintf()函数的输出内容具体从什么设备打印*/
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);  //将在看service.c里面实现
#endif
    /*内存初始化函数 mem.c里面实现*/
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());  
#endif
}

extern u32 TimingDelay;//delay.c中通过记录中断次数达到延时
 /**
 * @brief SysTick 中断服务函数
 * @param 无
 * @retval 无
 *
 * @attention
 * SysTick 中断服务函数在固件库文件 stm32f10x_it.c 中也定义了，而现在
 * 在 board.c 中又定义一次，那么编译的时候会出现重复定义的错误，解决
 * 方法是可以把 stm32f10x_it.c 中的注释或者删除即可。
 */
void SysTick_Handler(void)  
{
	/* 进入中断 */
	rt_interrupt_enter();
	if (TimingDelay != 0x00) 
	{
		TimingDelay--;
	}
	/* 更新时基 */
	rt_tick_increase();
	/* 离开中断 */
	rt_interrupt_leave();
}


/**
* @brief 重映射串口 DEBUG_USARTx 到 rt_kprintf()函数
* Note： DEBUG_USARTx 是在 bsp_usart.h 中定义的宏，默认使用串口 1
* @param str：要输出到串口的字符串
* @retval 无
*
* @attention
*
*/
void rt_hw_console_output(const char *str)
{
	/* 进入临界段 */
 rt_enter_critical();

 /* 直到字符串结束 */
 while (*str!='\0')
 {
 /* 换行 */
	if (*str=='\n')
 {
	 USART_SendData(DEBUGUSART, '\r');
	 while (USART_GetFlagStatus(DEBUGUSART, USART_FLAG_TXE) == RESET);
	 }

	 USART_SendData(DEBUGUSART, *str++);
	 while (USART_GetFlagStatus(DEBUGUSART, USART_FLAG_TXE) == RESET);
	 }
	 /* 退出临界段 */
	 rt_exit_critical();
 }
