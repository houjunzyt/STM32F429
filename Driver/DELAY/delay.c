#include "delay.h"

u32 TimingDelay=0;//���ڼ���Systick�жϴ���

/***************************************************
*�������ܣ�10΢�뵥λ��ʱ
*���������nTime����ʱʱ�䣺nTime*10us
*����ֵ  ����
***************************************************/
void Delay_us(__IO u32 nTime)
{
	TimingDelay=nTime;
	while (TimingDelay != 0);
}

/***************************************************
*�������ܣ����뵥λ��ʱ
*���������nTime����ʱʱ�䣺nTime*1ms
*����ֵ  ����
***************************************************/
void Delay_ms(__IO u32 nTime)
{
	Delay_us(100*nTime);
}