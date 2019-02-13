#ifndef __IIC_H
#define __IIC_H

#include "stm32f4xx.h"

/*---------------------------------- IIC �������ú� ---------------------------------*/

#define Touch_IIC_SCL_CLK     RCC_AHB1Periph_GPIOC		// SCL ����ʱ��
#define Touch_IIC_SCL_PORT    GPIOC                 	// SCL ���Ŷ˿�
#define Touch_IIC_SCL_PIN     GPIO_Pin_13  				// SCL ����
         
#define Touch_IIC_SDA_CLK     RCC_AHB1Periph_GPIOB 	// SDA ����ʱ��
#define Touch_IIC_SDA_PORT    GPIOB                   // SDA ���Ŷ˿�
#define Touch_IIC_SDA_PIN     GPIO_Pin_2              // SDA ����

#define Touch_INT_CLK     RCC_AHB1Periph_GPIOA			// INT ����ʱ��
#define Touch_INT_PORT    GPIOA                   		// INT ���Ŷ˿�
#define Touch_INT_PIN     GPIO_Pin_15             		// INT ����

#define Touch_RST_CLK     RCC_AHB1Periph_GPIOI			// RST ����ʱ��
#define Touch_RST_PORT    GPIOI                   		// RST ���Ŷ˿�
#define Touch_RST_PIN     GPIO_Pin_11            		// RST ����

/*----------------------------------- IIC��ض��� ----------------------------------*/

#define ACK_OK  	1  			// ��Ӧ����
#define ACK_ERR 	0				// ��Ӧ����

// IICͨ����ʱ��Touch_IIC_Delay()����ʹ�ã�
//	ͨ���ٶ���100KHz���ң�����ʹ�ýϳ���FPC����������Ļ��������ʹ�ù��ߵ��ٶ�
#define IIC_DelayVaule  20  	

/*------------------------------------ IO�ڲ��� ------------------------------------*/   

#define Touch_IIC_SCL(a)	if (a)	\
										GPIO_SetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN);\
									else		\
										GPIO_ResetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN)		

#define Touch_IIC_SDA(a)	if (a)	\
										GPIO_SetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN);\
									else		\
										GPIO_ResetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN)		

/*------------------------------------ �������� -----------------------------------*/  		
					
void 	Touch_IIC_GPIO_Config (void);			// IIC���ų�ʼ��
void 	Touch_IIC_Delay(u32 a);					// IIC��ʱ����
void	Touch_INT_Out(void);						// INT���ݽ�����Ϊ���ģʽ
void	Touch_INT_In(void);						// INT���ݽ�����Ϊ����ģʽ								
void 	Touch_IIC_Start(void);					// ����IICͨ��
void 	Touch_IIC_Stop(void);					// IICֹͣ�ź�
void 	Touch_IIC_ACK(void);						//	������Ӧ�ź�
void 	Touch_IIC_NoACK(void);					// ���ͷ�Ӧ���ź�
u8 	Touch_IIC_WaitACK(void);				//	�ȴ�Ӧ���ź�
u8	 	Touch_IIC_WriteByte(u8 IIC_Data); 	// д�ֽں���
u8 	Touch_IIC_ReadByte(u8 ACK_Mode);		// ���ֽں���
		
#endif //__IIC_H
