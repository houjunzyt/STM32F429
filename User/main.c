#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "sdram.h"
#include "usart.h"
#include "touch_043.h"
#include "touch_iic.h"
#include "lcd_rgb.h"

int i __EXRAM;
void LCD_AlphaTest(void);
int main(void)
{
	SysTick_Config(SystemCoreClock/100000);//us级别定时
	Usart1_Config();//串口初始化
	SDRAM_Init();//SDRAM初始化
	LED_Init();//板载LED灯初始化
	Touch_Init();		//触摸屏初始化
	LCD_Init();			// LCD控制器初始化
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
		LCD_AlphaTest();	//透明度测试
		Touch_Scan(); //触摸扫描
		if(touchInfo.flag==1)		// 若发生触摸
		{
			printf("坐标值：%d,%d\n",touchInfo.x[0],touchInfo.y[0]);		// y坐标
		}	
	}
}


void LCD_AlphaTest(void)
{
	LCD_DisplayMode(Mode_H);	//设置横屏
	LCD_SetFont(&Font24);		//设置字体

	LCD_SetLayer(0);		//切换到层0	
	LCD_SetColor(LCD_BLACK);	
	LCD_SetBackColor(LIGHT_BLUE);   
	LCD_Clear();
	LCD_DisplayString(10,20,"  STM32F429 LCD Layer 0"); 

	LCD_SetLayer(1);	//切换到层1
	LCD_SetBackColor(LIGHT_YELLOW & 0x00FFFFFF);  //透明度100%，高8位的数字越小透明度越高
	LCD_Clear();											 //此时前景层完全透明

	LCD_SetColor(LCD_BLACK & 0x0DFFFFFF);		
	LCD_SetBackColor(LIGHT_YELLOW & 0x0DFFFFFF);  	
	LCD_DisplayString(10,60," STM32F429 LCD Layer 1,Alpha:95%  "); 

	LCD_SetColor(LCD_BLACK & 0x33FFFFFF);			
	LCD_SetBackColor(LIGHT_YELLOW & 0x33FFFFFF); 
	LCD_DisplayString(10,90," STM32F429 LCD Layer 1,Alpha:80%  "); 

	LCD_SetColor(LCD_BLACK & 0x66FFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0x66FFFFFF); 
	LCD_DisplayString(10,120," STM32F429 LCD Layer 1,Alpha:60%  "); 

	LCD_SetColor(LCD_BLACK & 0x99FFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0x99FFFFFF); 
	LCD_DisplayString(10,150," STM32F429 LCD Layer 1,Alpha:40%  "); 

	LCD_SetColor(LCD_BLACK & 0xccFFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0xCCFFFFFF); 
	LCD_DisplayString(10,180," STM32F429 LCD Layer 1,Alpha:20%  "); 

	LCD_SetColor(LCD_BLACK & 0xffFFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0xFFFFFFFF); 
	LCD_DisplayString(10,210," STM32F429 LCD Layer 1,Alpha: 0%  "); 

	Delay_ms(1000);
}
