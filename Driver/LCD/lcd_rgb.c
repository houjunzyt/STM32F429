#include "lcd_rgb.h"

//uint32_t LCD_MemoryAdd;
//uint8_t LCD_FRAME_BUFFER[(LCD_MemoryAdd_OFFSET)*2] __EXRAM;

//uint32_t LCD_LAYER0_FRAME_BUFFER;									
//uint32_t LCD_LAYER1_FRAME_BUFFER;

void LCD_GPIO_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd( LCD_GPIO_CLK,ENABLE); 	
						
	GPIO_InitStruct.GPIO_Pin   = LTDC_R0_PIN;                             
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

	// LCD ��ɫ R �������� 
	GPIO_PinAFConfig(LTDC_R0_PORT, LTDC_R0_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R1_PORT, LTDC_R1_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R2_PORT, LTDC_R2_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R3_PORT, LTDC_R3_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R4_PORT, LTDC_R4_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R5_PORT, LTDC_R5_PINSOURCE, GPIO_AF_LTDC);	
	GPIO_PinAFConfig(LTDC_R6_PORT, LTDC_R6_PINSOURCE, GPIO_AF_LTDC);
	GPIO_PinAFConfig(LTDC_R7_PORT, LTDC_R7_PINSOURCE, GPIO_AF_LTDC);	

	GPIO_InitStruct.GPIO_Pin = LTDC_R0_PIN;	
	GPIO_Init(LTDC_R0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R1_PIN;
	GPIO_Init(LTDC_R1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R2_PIN;
	GPIO_Init(LTDC_R2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R3_PIN;
	GPIO_Init(LTDC_R3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R4_PIN;
	GPIO_Init(LTDC_R4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R5_PIN;
	GPIO_Init(LTDC_R5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R6_PIN;
	GPIO_Init(LTDC_R6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R7_PIN;
	GPIO_Init(LTDC_R7_PORT, &GPIO_InitStruct);

  
  // LCD ��ɫ G �������� 
  
	GPIO_PinAFConfig(LTDC_G0_PORT, LTDC_G0_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G1_PORT, LTDC_G1_PINSOURCE, GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_G2_PORT, LTDC_G2_PINSOURCE, GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_G3_PORT, LTDC_G3_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G4_PORT, LTDC_G4_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G5_PORT, LTDC_G5_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G6_PORT, LTDC_G6_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_G7_PORT, LTDC_G7_PINSOURCE, GPIO_AF_LTDC);  
  
	GPIO_InitStruct.GPIO_Pin = LTDC_G0_PIN;
	GPIO_Init(LTDC_G0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G1_PIN;
	GPIO_Init(LTDC_G1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G2_PIN;
	GPIO_Init(LTDC_G2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G3_PIN;
	GPIO_Init(LTDC_G3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G4_PIN;
	GPIO_Init(LTDC_G4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G5_PIN;
	GPIO_Init(LTDC_G5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G6_PIN;
	GPIO_Init(LTDC_G6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G7_PIN;
	GPIO_Init(LTDC_G7_PORT, &GPIO_InitStruct);

  
  // LCD ��ɫ B �������� 
  
	GPIO_PinAFConfig(LTDC_B0_PORT, LTDC_B0_PINSOURCE, GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_B1_PORT, LTDC_B1_PINSOURCE, GPIO_AF_LTDC); 	
	GPIO_PinAFConfig(LTDC_B2_PORT, LTDC_B2_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B3_PORT, LTDC_B3_PINSOURCE, GPIO_AF_LTDC);
	GPIO_PinAFConfig(LTDC_B4_PORT, LTDC_B4_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B5_PORT, LTDC_B5_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B6_PORT, LTDC_B6_PINSOURCE, GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_B7_PORT, LTDC_B7_PINSOURCE, GPIO_AF_LTDC);  

	GPIO_InitStruct.GPIO_Pin = LTDC_B0_PIN;
	GPIO_Init(LTDC_B0_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LTDC_B1_PIN;
	GPIO_Init(LTDC_B1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LTDC_B2_PIN;
	GPIO_Init(LTDC_B2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B3_PIN;
	GPIO_Init(LTDC_B3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B4_PIN;
	GPIO_Init(LTDC_B4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B5_PIN;
	GPIO_Init(LTDC_B5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B6_PIN;
	GPIO_Init(LTDC_B6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B7_PIN;
	GPIO_Init(LTDC_B7_PORT, &GPIO_InitStruct);

  
  //������
	GPIO_PinAFConfig(LTDC_CLK_PORT,   LTDC_CLK_PINSOURCE,  GPIO_AF_LTDC); 
	GPIO_PinAFConfig(LTDC_HSYNC_PORT, LTDC_HSYNC_PINSOURCE,GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_VSYNC_PORT, LTDC_VSYNC_PINSOURCE,GPIO_AF_LTDC);  
	GPIO_PinAFConfig(LTDC_DE_PORT,    LTDC_DE_PINSOURCE,   GPIO_AF_LTDC);
    
	GPIO_InitStruct.GPIO_Pin = LTDC_CLK_PIN;
	GPIO_Init(LTDC_CLK_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_HSYNC_PIN;
	GPIO_Init(LTDC_HSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_VSYNC_PIN;
	GPIO_Init(LTDC_VSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_DE_PIN;
	GPIO_Init(LTDC_DE_PORT, &GPIO_InitStruct);
			
	//����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = LTDC_Black_PIN; 
	GPIO_Init(LTDC_Black_PORT, &GPIO_InitStruct);

	GPIO_SetBits(LTDC_Black_PORT,LTDC_Black_PIN);
}

// ��������ʼ��LCD������
//	˵������emWin��ʼ���ﱻ����
//
void LCD_Init(void)
{ 
	u16 LCD_PLLSAIN = 0;		//���ڱ�Ƶ��PLLSAIN��������ȡ��ΧΪ50~432
	u8  LCD_PLLSAIR = 3;		//���ڷ�Ƶ��PLLSAIR��������ȡ��ΧΪ2~7
	u8  LCD_CLKDIV	 = 8;		//LCDʱ�ӷ�Ƶ������Ĭ������Ϊ8��Ƶ����ֵ�ϵ���RCC_PLLSAIDivR_Div8
	
//	LCD_MemoryAdd=(uint32_t)&LCD_FRAME_BUFFER;
//	LCD_LAYER0_FRAME_BUFFER=LCD_MemoryAdd;									
//	LCD_LAYER1_FRAME_BUFFER=LCD_MemoryAdd + LCD_MemoryAdd_OFFSET;
	
	LTDC_InitTypeDef       LTDC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE); 

	LCD_GPIO_Config();  //��ʼ��LCD����

	LCD_PLLSAIN = LCD_CLK * LCD_PLLSAIR * LCD_CLKDIV;	//������Ҫʹ�õ�LCDʱ�Ӽ���PLLSAIN��������ȡ��ΧΪ50~432
	RCC_PLLSAIConfig(LCD_PLLSAIN,7,LCD_PLLSAIR);  		//ʱ������
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div8);	 		//LCDʱ�ӷ�Ƶ���ã�Ҫ��LCD_CLKDIV��Ӧ
	RCC_PLLSAICmd(ENABLE);		//ʹ��PLLSAIʱ��
	while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET);	//�ȴ�ʱ���������
	
	LTDC_InitStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL;     
	LTDC_InitStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL;     
	LTDC_InitStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL;     
	LTDC_InitStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC;
              
	LTDC_InitStruct.LTDC_BackgroundRedValue = 0;            
	LTDC_InitStruct.LTDC_BackgroundGreenValue = 0;          
	LTDC_InitStruct.LTDC_BackgroundBlueValue = 0;   

	LTDC_InitStruct.LTDC_HorizontalSync =HSW;
	LTDC_InitStruct.LTDC_VerticalSync = VSW;
	LTDC_InitStruct.LTDC_AccumulatedHBP =HBP;
	LTDC_InitStruct.LTDC_AccumulatedVBP = VBP;
	LTDC_InitStruct.LTDC_AccumulatedActiveW = LCD_Width+HBP;
	LTDC_InitStruct.LTDC_AccumulatedActiveH = LCD_Height+VBP;
	LTDC_InitStruct.LTDC_TotalWidth =LCD_Width + HBP + HFP; 
	LTDC_InitStruct.LTDC_TotalHeigh =LCD_Height + VBP + VFP;

	LTDC_Init(&LTDC_InitStruct);	//��ʼ��LCD������
	LTDC_Cmd(ENABLE);	//ʹ��LCD������
}  

