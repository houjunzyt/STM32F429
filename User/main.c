#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"


int main(void)
{
	SysTick_Config(SystemCoreClock/100000);//us级别定时
	LED_Init();
  while(1)
	{
		LED1_ON;
		LED2_ON;
		Delay_ms(1000);
		LED1_OFF;
		LED2_OFF;
		Delay_ms(1000);	
	}
}



