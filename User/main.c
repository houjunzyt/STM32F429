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
		rt_kprintf("Fatfs_Mutex互斥量创建成功！ \n\n");		
	rt_thread_init(&FatFsInit_ThreadTCB, /* 线程控制块 */
									"FatFs", /* 线程名字 */
									FatFsInit_Thread, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&FatFsInit_ThreadStk[0], /* 线程栈起始地址 */
									sizeof(FatFsInit_ThreadStk), /* 线程栈大小 */
									3, /* 线程的优先级 */
									100); /* 线程时间片 */									
	rt_thread_startup(&FatFsInit_ThreadTCB); /* 启动线程，开启调度 */	
	rt_thread_init(&emWin_ThreadTCB, /* 线程控制块 */
									"emWin", /* 线程名字 */
									emWin_Thread, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&emWin_ThreadStk[0], /* 线程栈起始地址 */
									sizeof(emWin_ThreadStk), /* 线程栈大小 */
									3, /* 线程的优先级 */
									100); /* 线程时间片 */
	rt_thread_startup(&emWin_ThreadTCB); /* 启动线程，开启调度 */
	rt_thread_init(&Touch_ThreadTCB, /* 线程控制块 */
									"Touch", /* 线程名字 */
									Touch_Thread, /* 线程入口函数 */
									RT_NULL, /* 线程入口函数参数 */
									&Touch_ThreadStk[0], /* 线程栈起始地址 */
									sizeof(Touch_ThreadStk), /* 线程栈大小 */
									3, /* 线程的优先级 */
									20); /* 线程时间片 */									
	rt_thread_startup(&Touch_ThreadTCB); /* 启动线程，开启调度 */
}

static void	emWin_Thread(void *parameter)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);	// 使能CRC时钟，用于emwin验证	
	GUI_Init();															// emwin初始化
	WM_MULTIBUF_Enable(1);											// 开启多缓冲	
	while(1)
	{
		GUIDEMO_Main();
	}	
}

static void	Touch_Thread(void *parameter)
{
	while(1)
	{	
		GUI_TouchScan();		// 调用触摸检测函数
		rt_thread_delay(20);
	}
}

static void FatFsInit_Thread(void* parameter)
{
	rt_err_t Ret=RT_NULL;
	uint8_t MyFile_ReadBuffer[6];
	rt_mutex_take(Fatfs_Mutex,RT_WAITING_FOREVER); /* 等待时间：一直等 */
	FatFs_Check();			//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
	FatFs_GetVolume();	// 计算设备容量
	FIL	MyFile;			// 文件对象
	FRESULT 	MyFile_Res;    // 操作结果 
	UINT 	MyFile_Num;		//	数据长度
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//打开文件，若不存在则创建该文件
	if(MyFile_Res == FR_OK)
	{
		printf("文件打开/创建成功，准备写入数据...\r\n");
		
		MyFile_Res = f_write(&MyFile,"HOUJUN",6,&MyFile_Num);	//向文件写入数据
		if (MyFile_Res == FR_OK)	
		{
			printf("写入成功\r\n");
		}
		else
		{
			printf("文件写入失败，请检查SD卡或重新格式化!\r\n");
			f_close(&MyFile);	  //关闭文件		
		}
		f_close(&MyFile);	  //关闭文件			
	}
	else
	{
		printf("无法打开/创建文件，请检查SD卡或重新格式化!\r\n");
		f_close(&MyFile);	  //关闭文件	
	}
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//打开文件，若不存在则创建该文件
	MyFile_Res = f_read(&MyFile,MyFile_ReadBuffer,6,&MyFile_Num);			// 读取文件
	if(MyFile_Res == FR_OK)
	{
		printf("文件读取成功，正在校验数据...\r\n");
		printf("%s\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("无法读取文件，请检查SD卡或重新格式化!\r\n");
	}	
	
	f_close(&MyFile);	  //关闭文件	

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
