#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"

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



