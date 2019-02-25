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
#include "sdio.h"

#include  "GUI.h"
#include  "WM.h"
#include  "GUI_Touch.h"
#include  "GUIDEMO.h"

#include "ff.h"

struct rt_thread emWin_ThreadTCB;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t emWin_ThreadStk[4096] __EXRAM;
static void emWin_Thread(void* parameter);

struct rt_thread Touch_ThreadTCB;
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t Touch_ThreadStk[512] __EXRAM;
static void Touch_Thread(void* parameter);

struct rt_thread FatFsInit_ThreadTCB;
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t FatFsInit_ThreadStk[512] __EXRAM;
static void FatFsInit_Thread(void* parameter);

static rt_mutex_t Fatfs_Mutex=RT_NULL;


int main(void)
{
	Fatfs_Mutex=rt_mutex_create("Fatfs_mux",RT_IPC_FLAG_PRIO);
	if (Fatfs_Mutex != RT_NULL)
		rt_kprintf("Fatfs_Mutex�����������ɹ��� \n\n");		
	rt_thread_init(&FatFsInit_ThreadTCB, /* �߳̿��ƿ� */
									"FatFs", /* �߳����� */
									FatFsInit_Thread, /* �߳���ں��� */
									RT_NULL, /* �߳���ں������� */
									&FatFsInit_ThreadStk[0], /* �߳�ջ��ʼ��ַ */
									sizeof(FatFsInit_ThreadStk), /* �߳�ջ��С */
									3, /* �̵߳����ȼ� */
									100); /* �߳�ʱ��Ƭ */									
	rt_thread_startup(&FatFsInit_ThreadTCB); /* �����̣߳��������� */	
	rt_thread_init(&emWin_ThreadTCB, /* �߳̿��ƿ� */
									"emWin", /* �߳����� */
									emWin_Thread, /* �߳���ں��� */
									RT_NULL, /* �߳���ں������� */
									&emWin_ThreadStk[0], /* �߳�ջ��ʼ��ַ */
									sizeof(emWin_ThreadStk), /* �߳�ջ��С */
									3, /* �̵߳����ȼ� */
									100); /* �߳�ʱ��Ƭ */
	rt_thread_startup(&emWin_ThreadTCB); /* �����̣߳��������� */
	rt_thread_init(&Touch_ThreadTCB, /* �߳̿��ƿ� */
									"Touch", /* �߳����� */
									Touch_Thread, /* �߳���ں��� */
									RT_NULL, /* �߳���ں������� */
									&Touch_ThreadStk[0], /* �߳�ջ��ʼ��ַ */
									sizeof(Touch_ThreadStk), /* �߳�ջ��С */
									3, /* �̵߳����ȼ� */
									20); /* �߳�ʱ��Ƭ */									
	rt_thread_startup(&Touch_ThreadTCB); /* �����̣߳��������� */
}

static void	emWin_Thread(void *parameter)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);	// ʹ��CRCʱ�ӣ�����emwin��֤	
	GUI_Init();															// emwin��ʼ��
	WM_MULTIBUF_Enable(1);											// �����໺��	
	while(1)
	{
		GUIDEMO_Main();
	}	
}

static void	Touch_Thread(void *parameter)
{
	while(1)
	{	
		GUI_TouchScan();		// ���ô�����⺯��
		rt_thread_delay(20);
	}
}

static void FatFsInit_Thread(void* parameter)
{
	rt_err_t Ret=RT_NULL;
	uint8_t MyFile_ReadBuffer[6];
	rt_mutex_take(Fatfs_Mutex,RT_WAITING_FOREVER); /* �ȴ�ʱ�䣺һֱ�� */
	FatFs_Check();			//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
	FatFs_GetVolume();	// �����豸����
	FIL	MyFile;			// �ļ�����
	FRESULT 	MyFile_Res;    // ������� 
	UINT 	MyFile_Num;		//	���ݳ���
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//���ļ������������򴴽����ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���/�����ɹ���׼��д������...\r\n");
		
		MyFile_Res = f_write(&MyFile,"HOUJUN",6,&MyFile_Num);	//���ļ�д������
		if (MyFile_Res == FR_OK)	
		{
			printf("д��ɹ�\r\n");
		}
		else
		{
			printf("�ļ�д��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
			f_close(&MyFile);	  //�ر��ļ�		
		}
		f_close(&MyFile);	  //�ر��ļ�			
	}
	else
	{
		printf("�޷���/�����ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
	}
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//���ļ������������򴴽����ļ�
	MyFile_Res = f_read(&MyFile,MyFile_ReadBuffer,6,&MyFile_Num);			// ��ȡ�ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���ȡ�ɹ�������У������...\r\n");
		printf("%s\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("�޷���ȡ�ļ�������SD�������¸�ʽ��!\r\n");
	}	
	
	f_close(&MyFile);	  //�ر��ļ�	

	Ret=rt_thread_suspend(&FatFsInit_ThreadTCB);
	if(Ret==RT_EOK)
	{
		rt_kprintf("FatFs thread suspend success\n");
	}
	else
	{
		rt_kprintf("FatFs thread suspend FAILED\n");
	}
	rt_mutex_release(Fatfs_Mutex);
}
