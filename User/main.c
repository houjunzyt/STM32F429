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

struct rt_thread emWin_TaskTCB;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t emWin_TaskStk[4096] __EXRAM;
static void emWin_Task(void* parameter);


struct rt_thread Touch_TaskTCB;
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t Touch_TaskStk[512] __EXRAM;
static void Touch_Task(void* parameter);

int main(void)
{
	rt_thread_init(&emWin_TaskTCB, /* 线程控制块 */
									"emWin", /* 线程名字 */
									emWin_Task, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&emWin_TaskStk[0], /* 线程栈起始地址 */
									sizeof(emWin_TaskStk), /* 线程栈大小 */
									3, /* 线程的优先级 */
									100); /* 线程时间片 */
	rt_thread_startup(&emWin_TaskTCB); /* 启动线程，开启调度 */
	rt_thread_init(&Touch_TaskTCB, /* 线程控制块 */
									"Touch", /* 线程名字 */
									Touch_Task, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&Touch_TaskStk[0], /* 线程栈起始地址 */
									sizeof(Touch_TaskStk), /* 线程栈大小 */
									3, /* 线程的优先级 */
									20); /* 线程时间片 */									
	rt_kprintf("thread init success \n");
	rt_thread_startup(&Touch_TaskTCB); /* 启动线程，开启调度 */		
}

static	void	emWin_Task (void *parameter)
{
	rt_kprintf("task2\n");
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);	// 使能CRC时钟，用于emwin验证	
	GUI_Init();															// emwin初始化
	WM_MULTIBUF_Enable(1);											// 开启多缓冲	
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
		GUI_TouchScan();		// 调用触摸检测函数
		rt_thread_delay(20);
	}
}

