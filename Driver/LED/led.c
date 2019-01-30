#include "delay.h"
#include "led.h"

/***********************************************************
*�������ܣ�LED��ʼ��
*�����������
*����ֵ  ����
***********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|LED2_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	/*��������ģʽΪ���ģʽ*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*�������ŵ��������Ϊ�������*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*������������Ϊ 2MHz */
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);/*���ÿ⺯����ʹ���������õ� GPIO_InitStructure ��ʼ�� GPIO*/

	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);/*���ÿ⺯����ʹ���������õ� GPIO_InitStructure ��ʼ�� GPIO*/
}
