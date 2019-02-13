#ifndef __TOUCH_H
#define __TOUCH_H

#include "stm32f4xx.h"
#include "touch_iic.h"  
#include "usart.h"

/*------------------------------------ ��ض��� -----------------------------------*/  		

#define TOUCH_MAX   5	//���������

typedef struct 
{
	u8  flag;			//	������־λ��Ϊ1ʱ��ʾ�д�������
	u8  num;				//	��������
	u16 x[TOUCH_MAX];	//	x����
	u16 y[TOUCH_MAX];	//	y����
}TouchStructure;

extern TouchStructure touchInfo;	// �������ݽṹ������	

/*------------------------------------ �Ĵ涨�� -----------------------------------*/  		

#define GT9XX_IIC_RADDR 0xBB			// IIC��ʼ����ַ
#define GT9XX_IIC_WADDR 0xBA

#define GT9XX_CFG_ADDR 	0x8047		// �̼�������Ϣ�Ĵ�����������ʼ��ַ
#define GT9XX_READ_ADDR 0x814E		// ������Ϣ�Ĵ���
#define GT9XX_ID_ADDR 	0x8140		// �������ID�Ĵ���

/*------------------------------------ �������� -----------------------------------*/  		

u8 	Touch_Init(void);		// ��������ʼ��
void 	Touch_Scan(void);    // ����ɨ��
void  GT9XX_Reset(void);   // ִ�и�λ����
void 	GT9XX_SendCfg(void);	// ����GT9147���ò���
void 	GT9XX_ReadCfg(void);	// ��ȡGT9147���ò���
	
#endif

