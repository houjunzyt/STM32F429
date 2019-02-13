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
	SysTick_Config(SystemCoreClock/100000);//us����ʱ
	Usart1_Config();//���ڳ�ʼ��
	SDRAM_Init();//SDRAM��ʼ��
	LED_Init();//����LED�Ƴ�ʼ��
	Touch_Init();		//��������ʼ��
	
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
		Touch_Scan(); //����ɨ��
		if(touchInfo.flag==1)		// ����������
		{
			printf("����ֵ��%d,%d\n",touchInfo.x[0],touchInfo.y[0]);		// y����
		}	
	}
}



