#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"

int i __EXRAM;

int main(void)
{
	SysTick_Config(SystemCoreClock/100000);//us级别定时
	Usart1_Config();
	SDRAM_Init();
	LED_Init();
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
		printf("kaka\n");
		LED1_ON;
		LED2_ON;
		Delay_ms(1000);
		LED1_OFF;
		LED2_OFF;
		Delay_ms(1000);	
	}
}



