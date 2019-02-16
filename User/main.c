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

