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
	SysTick_Config(SystemCoreClock/100000);//us����ʱ
	Usart1_Config();//���ڳ�ʼ��
	SDRAM_Init();//SDRAM��ʼ��
	LED_Init();//����LED�Ƴ�ʼ��
	Touch_Init();		//��������ʼ��
	LCD_Init();			// LCD��������ʼ��
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
		LCD_AlphaTest();	//͸���Ȳ���
		Touch_Scan(); //����ɨ��
		if(touchInfo.flag==1)		// ����������
		{
			printf("����ֵ��%d,%d\n",touchInfo.x[0],touchInfo.y[0]);		// y����
		}	
	}
}


void LCD_AlphaTest(void)
{
	LCD_DisplayMode(Mode_H);	//���ú���
	LCD_SetFont(&Font24);		//��������

	LCD_SetLayer(0);		//�л�����0	
	LCD_SetColor(LCD_BLACK);	
	LCD_SetBackColor(LIGHT_BLUE);   
	LCD_Clear();
	LCD_DisplayString(10,20,"  STM32F429 LCD Layer 0"); 

	LCD_SetLayer(1);	//�л�����1
	LCD_SetBackColor(LIGHT_YELLOW & 0x00FFFFFF);  //͸����100%����8λ������ԽС͸����Խ��
	LCD_Clear();											 //��ʱǰ������ȫ͸��

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
