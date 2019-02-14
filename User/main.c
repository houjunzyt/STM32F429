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

struct rt_thread led1_thread;
/* 定义线程控栈时要求 RT_ALIGN_SIZE 个字节对齐 */
ALIGN(RT_ALIGN_SIZE)
/* 定义线程栈 */
rt_uint8_t rt_led1_thread_stack[1024] __EXRAM;
static void led1_thread_entry(void* parameter);

int main(void)
{
	rt_thread_init(&led1_thread, /* 线程控制块 */
									"led1", /* 线程名字 */
									led1_thread_entry, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&rt_led1_thread_stack[0], /* 线程栈起始地址 */
									sizeof(rt_led1_thread_stack), /* 线程栈大小 */
									3, /* 线程的优先级 */
									20); /* 线程时间片 */
									
	rt_kprintf("thread init success \n");
	rt_thread_startup(&led1_thread); /* 启动线程，开启调度 */
}

static void led1_thread_entry(void* parameter)
{
	while (1)
	{
		LED1_ON;
		rt_thread_delay(500); /* 延时 500 个 tick */

		LED1_OFF;
		rt_thread_delay(500); /* 延时 500 个 tick */
	}
}

