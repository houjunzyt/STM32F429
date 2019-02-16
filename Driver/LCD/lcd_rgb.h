#ifndef __LCD_H
#define	__LCD_H

#include "stm32f4xx.h"


#define LCD_CLK   9		//����LCD����ʱ�ӣ�����Ϊ�˷��������ֵӦ��10-70֮�䣬��λΪM

#define HBP  40
#define VBP  8
#define HSW  1
#define VSW  1
#define HFP  5
#define VFP  8

#define LCD_Width     480				//LCD�����س���
#define LCD_Height    272				//LCD�����ؿ��
#define LCD_Pixels    480*272 		//�ֱ���

#define LCD_MemoryAdd   0xD0000000 	//�Դ����ʼ��ַ  

//	�ڶ�����Դ��ƫ�Ƶ�ַ 
//	����Ԥ����emWinʹ��32λɫ��ʽʱ������������Ŀռ�
//	���㷽������32λ��ɫ��ʽΪ����ÿ�����ص�ռ4�ֽڣ�ʹ��emWin����������ռ�Ϊ��480*272*4*3
//
#define LCD_MemoryAdd_OFFSET    ((uint32_t)LCD_Width*LCD_Height*4*3)    

/*---------------------- �������� -------------------------*/ 
void     LCD_Init(void);

/*-----------------------���Ŷ���--------------------------*/

//IO��ʱ��
#define LCD_GPIO_CLK	 RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD \
							 | RCC_AHB1Periph_GPIOJ | RCC_AHB1Periph_GPIOK | RCC_AHB1Periph_GPIOI

//��ɫ������
#define LTDC_R0_PORT        	GPIOI
#define LTDC_R0_PIN         	GPIO_Pin_15
#define LTDC_R0_PINSOURCE     GPIO_PinSource15

#define LTDC_R1_PORT        	GPIOJ
#define LTDC_R1_PIN         	GPIO_Pin_0
#define LTDC_R1_PINSOURCE     GPIO_PinSource0

#define LTDC_R2_PORT        	GPIOJ
#define LTDC_R2_PIN         	GPIO_Pin_1
#define LTDC_R2_PINSOURCE     GPIO_PinSource1

#define LTDC_R3_PORT        	GPIOJ
#define LTDC_R3_PIN         	GPIO_Pin_2
#define LTDC_R3_PINSOURCE     GPIO_PinSource2

#define LTDC_R4_PORT        	GPIOJ
#define LTDC_R4_PIN         	GPIO_Pin_3
#define LTDC_R4_PINSOURCE     GPIO_PinSource3

#define LTDC_R5_PORT        	GPIOJ
#define LTDC_R5_PIN         	GPIO_Pin_4
#define LTDC_R5_PINSOURCE     GPIO_PinSource4

#define LTDC_R6_PORT        	GPIOJ
#define LTDC_R6_PIN         	GPIO_Pin_5
#define LTDC_R6_PINSOURCE     GPIO_PinSource5

#define LTDC_R7_PORT        	GPIOJ
#define LTDC_R7_PIN         	GPIO_Pin_6
#define LTDC_R7_PINSOURCE     GPIO_PinSource6

//��ɫ������
#define LTDC_G0_PORT        	GPIOJ
#define LTDC_G0_PIN         	GPIO_Pin_7
#define LTDC_G0_PINSOURCE     GPIO_PinSource7

#define LTDC_G1_PORT        	GPIOJ
#define LTDC_G1_PIN         	GPIO_Pin_8
#define LTDC_G1_PINSOURCE     GPIO_PinSource8

#define LTDC_G2_PORT        	GPIOJ
#define LTDC_G2_PIN         	GPIO_Pin_9
#define LTDC_G2_PINSOURCE     GPIO_PinSource9

#define LTDC_G3_PORT        	GPIOJ
#define LTDC_G3_PIN         	GPIO_Pin_10
#define LTDC_G3_PINSOURCE     GPIO_PinSource10

#define LTDC_G4_PORT        	GPIOJ
#define LTDC_G4_PIN         	GPIO_Pin_11
#define LTDC_G4_PINSOURCE     GPIO_PinSource11

#define LTDC_G5_PORT        	GPIOK
#define LTDC_G5_PIN         	GPIO_Pin_0
#define LTDC_G5_PINSOURCE     GPIO_PinSource0

#define LTDC_G6_PORT        	GPIOK
#define LTDC_G6_PIN         	GPIO_Pin_1
#define LTDC_G6_PINSOURCE     GPIO_PinSource1

#define LTDC_G7_PORT        	GPIOK
#define LTDC_G7_PIN         	GPIO_Pin_2
#define LTDC_G7_PINSOURCE     GPIO_PinSource2

//��ɫ������
#define LTDC_B0_PORT        	GPIOJ
#define LTDC_B0_PIN         	GPIO_Pin_12
#define LTDC_B0_PINSOURCE     GPIO_PinSource12

#define LTDC_B1_PORT       	GPIOJ
#define LTDC_B1_PIN           GPIO_Pin_13
#define LTDC_B1_PINSOURCE     GPIO_PinSource13

#define LTDC_B2_PORT        	GPIOJ
#define LTDC_B2_PIN         	GPIO_Pin_14
#define LTDC_B2_PINSOURCE     GPIO_PinSource14

#define LTDC_B3_PORT        	GPIOJ
#define LTDC_B3_PIN         	GPIO_Pin_15
#define LTDC_B3_PINSOURCE     GPIO_PinSource15

#define LTDC_B4_PORT        	GPIOK
#define LTDC_B4_PIN         	GPIO_Pin_3
#define LTDC_B4_PINSOURCE     GPIO_PinSource3

#define LTDC_B5_PORT        	GPIOK
#define LTDC_B5_PIN         	GPIO_Pin_4
#define LTDC_B5_PINSOURCE     GPIO_PinSource4

#define LTDC_B6_PORT        	GPIOK
#define LTDC_B6_PIN         	GPIO_Pin_5
#define LTDC_B6_PINSOURCE     GPIO_PinSource5

#define LTDC_B7_PORT        	GPIOK
#define LTDC_B7_PIN         	GPIO_Pin_6
#define LTDC_B7_PINSOURCE     GPIO_PinSource6

//�����ź���
#define LTDC_CLK_PORT         GPIOI					//LCDʱ������
#define LTDC_CLK_PIN          GPIO_Pin_14
#define LTDC_CLK_PINSOURCE    GPIO_PinSource14

#define LTDC_HSYNC_PORT       GPIOI					//��ͬ��
#define LTDC_HSYNC_PIN        GPIO_Pin_12
#define LTDC_HSYNC_PINSOURCE  GPIO_PinSource12

#define LTDC_VSYNC_PORT       GPIOI					//֡ͬ��
#define LTDC_VSYNC_PIN        GPIO_Pin_13
#define LTDC_VSYNC_PINSOURCE  GPIO_PinSource13

#define LTDC_DE_PORT          GPIOK					//����ʹ��
#define LTDC_DE_PIN           GPIO_Pin_7
#define LTDC_DE_PINSOURCE     GPIO_PinSource7
	
#define LTDC_Black_PORT       GPIOD					//����
#define LTDC_Black_PIN        GPIO_Pin_13

#endif 
