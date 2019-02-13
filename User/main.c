#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"
#include "touch_043.h"
#include "touch_iic.h"

int i __EXRAM;

int main(void)
{
	SysTick_Config(SystemCoreClock/100000);//us级别定时
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
	char * kk=malloc(1024*sizeof(char));
	for(i=0;i<1024;i++)
	{
		kk[i]=i;
	}
	printf("%d :%d\n",5,kk[5]);
	printf("%d :%d\n",200,kk[200]);
	printf("kaka:%x\n",(int)&i);
  while(1)
	{
		Touch_Scan(); //触摸扫描
		if(touchInfo.flag==1)		// 若发生触摸
		{
			printf("坐标值：%d,%d\n",touchInfo.x[0],touchInfo.y[0]);		// y坐标
		}	
	}
}



