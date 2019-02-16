#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"
#include "touch_043.h"
#include "touch_iic.h"
#include "lcd_rgb.h"
#include "board.h"
#include "rtthread.h"

#include  "GUI.h"
#include  "WM.h"
#include  "GUI_Touch.h"
#include  "GUIDEMO.h"

//struct rt_thread led1_thread;
//ALIGN(RT_ALIGN_SIZE)
//rt_uint8_t rt_led1_thread_stack[1024] __EXRAM;
//static void led1_thread_entry(void* parameter);

struct rt_thread emWin_TaskTCB;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t emWin_TaskStk[4096];// __EXRAM;
static void emWin_Task(void* parameter);


struct rt_thread Touch_TaskTCB;
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t Touch_TaskStk[512];// __EXRAM;
static void Touch_Task(void* parameter);

int main(void)
{
//	rt_thread_init(&led1_thread, /* �߳̿��ƿ� */
//									"led1", /* �߳����� */
//									led1_thread_entry, /* �߳���ں��� */
//									RT_NULL, /* �߳���ں������� */
//									&rt_led1_thread_stack[0], /* �߳�ջ��ʼ��ַ */
//									sizeof(rt_led1_thread_stack), /* �߳�ջ��С */
//									3, /* �̵߳����ȼ� */
//									20); /* �߳�ʱ��Ƭ */
//	rt_thread_startup(&led1_thread); /* �����̣߳��������� */
	rt_thread_init(&emWin_TaskTCB, /* �߳̿��ƿ� */
									"emWin", /* �߳����� */
									emWin_Task, /* �߳���ں��� */
									RT_NULL, /* �߳���ں������� */
									&emWin_TaskStk[0], /* �߳�ջ��ʼ��ַ */
									sizeof(emWin_TaskStk), /* �߳�ջ��С */
									3, /* �̵߳����ȼ� */
									100); /* �߳�ʱ��Ƭ */
	rt_thread_startup(&emWin_TaskTCB); /* �����̣߳��������� */
	rt_thread_init(&Touch_TaskTCB, /* �߳̿��ƿ� */
									"Touch", /* �߳����� */
									Touch_Task, /* �߳���ں��� */
									RT_NULL, /* �߳���ں������� */
									&Touch_TaskStk[0], /* �߳�ջ��ʼ��ַ */
									sizeof(Touch_TaskStk), /* �߳�ջ��С */
									3, /* �̵߳����ȼ� */
									20); /* �߳�ʱ��Ƭ */									
	rt_kprintf("thread init success \n");
	rt_thread_startup(&Touch_TaskTCB); /* �����̣߳��������� */
									
}

static void led1_thread_entry(void* parameter)
{
	rt_kprintf("task1\n");
	while (1)
	{
		LED1_ON;
		rt_thread_delay(500); /* ��ʱ 500 �� tick */

		LED1_OFF;
		rt_thread_delay(500); /* ��ʱ 500 �� tick */
	}
}

static	void	emWin_Task (void *parameter)
{
	rt_kprintf("task2\n");
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);	// ʹ��CRCʱ�ӣ�����emwin��֤	
	GUI_Init();															// emwin��ʼ��
	WM_MULTIBUF_Enable(1);											// �����໺��	
	while(1)
	{
		GUIDEMO_Main();
	}	
}

static	void	Touch_Task (void *parameter)
{
	rt_kprintf("task3\n");
	while(1)
	{	
		GUI_TouchScan();		// ���ô�����⺯��
		rt_thread_delay(20);
	}
}


//LR_IROM1 0x08000000 0x00200000  {    ; load region size_region
//  ER_IROM1 0x08000000 0x00200000  {  ; load address = execution address
//   *.o (RESET, +First)
//   *(InRoot$$Sections)
//   .ANY (+RO)
//  }
//  RW_IRAM1 0x20000000 0x00030000  {  ; RW data
//   .ANY (+RW +ZI)
//  }
//  RW_IRAM2 0xD0000000 0x01000000  {  ; RW data
//   .ANY (EXRAM);extern ram
//  }
//}

