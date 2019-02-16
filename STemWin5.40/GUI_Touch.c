/***
	***************************************************************************************
	*	@file  	GUI_Touch.c
	*	@version V1.0
	*  @date    2017-12-1
	*	@author  ���ͿƼ�
	*	@brief   emwin������ֲ
   ***************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨������STM32F429���İ� + 4.3��RGBҺ����
	*	�Ա���ַ��https://shop212360197.taobao.com
	*	QQ����Ⱥ��536665479
	*
	***************************************************************************************
***/

#include	"GUI_Touch.h"


GUI_PID_STATE GUI_TouchState ;	// emWin���������ṹ��

/*****************************************************************************************
*	�� �� ��: GUI_TouchScan
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ���ݴ���������emwin
*	˵    ��: ��SysTick�ж��ﱻ����
******************************************************************************************/
void	GUI_TouchScan(void){
	
	Touch_Scan(); //����ɨ��
	if( touchInfo.flag == 1)		// ����������
	{
		GUI_TouchState.x = touchInfo.x[0];		// x����
		GUI_TouchState.y = touchInfo.y[0];		// y����
		GUI_TouchState.Pressed = 1;				// �������±�־λ
		GUI_PID_StoreState(&GUI_TouchState);	// ���ݴ�������
	}
	else
	{
		GUI_TouchState.Pressed = 0;				//	�޴�������
		GUI_PID_StoreState(&GUI_TouchState);	// ���ݴ�������
	}	
}
