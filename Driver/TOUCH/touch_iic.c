#include "touch_iic.h"  

/*****************************************************************************************
*	�� �� ��: Touch_IIC_GPIO_Config
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��ʼ��IIC��GPIO��,�������
*	˵    ��: ����IICͨ���ٶȲ��ߣ������IO���ٶ�����Ϊ2M����
******************************************************************************************/

void Touch_IIC_GPIO_Config (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(Touch_IIC_SCL_CLK | Touch_IIC_SDA_CLK | Touch_INT_CLK | Touch_RST_CLK , ENABLE);	//��ʼ��IO��ʱ��

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   	// ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 		// ��©���
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	// �ٶȵȼ�2M  

	GPIO_InitStructure.GPIO_Pin = Touch_IIC_SCL_PIN; 		// SCL
	GPIO_Init(Touch_IIC_SCL_PORT, &GPIO_InitStructure);				   	

	GPIO_InitStructure.GPIO_Pin = Touch_IIC_SDA_PIN; 		// SDA	
	GPIO_Init(Touch_IIC_SDA_PORT, &GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      	// �������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		 	// ����	
	
	GPIO_InitStructure.GPIO_Pin = Touch_INT_PIN; 		//	INT
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);				

	GPIO_InitStructure.GPIO_Pin = Touch_RST_PIN; 		//	RST
	GPIO_Init(Touch_RST_PORT, &GPIO_InitStructure);					   

	GPIO_SetBits(Touch_IIC_SCL_PORT,Touch_IIC_SCL_PIN);	// SCL����ߵ�ƽ
	GPIO_SetBits(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN);	// SDA����ߵ�ƽ
	GPIO_ResetBits(Touch_INT_PORT,Touch_INT_PIN); 			// INT����͵�ƽ
	GPIO_SetBits(Touch_RST_PORT,Touch_RST_PIN);				// RST�����	��ƽ	
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_Delay
*	��ڲ���: a - ��ʱʱ��
*	�� �� ֵ: ��
*	��������: ����ʱ����
*	˵    ��: Ϊ����ֲ�ļ�����Ҷ���ʱ����Ҫ�󲻸ߣ����Բ���Ҫʹ�ö�ʱ������ʱ
******************************************************************************************/

void Touch_IIC_Delay(u32 a)
{
	int i;
	while (a --)				
	{
		for (i = 0; i < 10; i++);
	}
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_INT_Out
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ����IIC��INT��Ϊ���ģʽ
*	˵    ��: ��
******************************************************************************************/

void Touch_INT_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;      	// ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      	// �������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;		 	// ����	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;    	// �ٶȵȼ�2M 
	GPIO_InitStructure.GPIO_Pin   = Touch_INT_PIN ;  		// ��ʼ�� INT ����
	
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);		
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_INT_In
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ����IIC��INT��Ϊ����ģʽ
*	˵    ��: ��
******************************************************************************************/

void Touch_INT_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   		//	����ģʽ
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;		//	��������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		//	�ٶȵȼ�2M
	GPIO_InitStructure.GPIO_Pin 	= Touch_INT_PIN ;  		//	��ʼ�� INT ����
	
	GPIO_Init(Touch_INT_PORT, &GPIO_InitStructure);
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_Start
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: IIC��ʼ�ź�
*	˵    ��: ��SCL���ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�������Ϊ��ʼ�ź�
******************************************************************************************/

void Touch_IIC_Start(void)
{
	Touch_IIC_SDA(1);		
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_Stop
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: IICֹͣ�ź�
*	˵    ��: ��SCL���ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�������Ϊ��ʼ�ź�
******************************************************************************************/

void Touch_IIC_Stop(void)
{
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_ACK
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: IICӦ���ź�
*	˵    ��: ��SCLΪ�ߵ�ƽ�ڼ䣬SDA�������Ϊ�͵�ƽ������Ӧ���ź�
******************************************************************************************/

void Touch_IIC_ACK(void)
{
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(0);
	Touch_IIC_Delay(IIC_DelayVaule);	
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(0);		// SCL�����ʱ��SDAӦ�������ߣ��ͷ�����
	Touch_IIC_SDA(1);		
	
	Touch_IIC_Delay(IIC_DelayVaule);

}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_NoACK
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: IIC��Ӧ���ź�
*	˵    ��: ��SCLΪ�ߵ�ƽ�ڼ䣬��SDA����Ϊ�ߵ�ƽ��������Ӧ���ź�
******************************************************************************************/

void Touch_IIC_NoACK(void)
{
	Touch_IIC_SCL(0);	
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	
	Touch_IIC_SCL(0);
	Touch_IIC_Delay(IIC_DelayVaule);
}

/*****************************************************************************************
*	�� �� ��: Touch_IIC_WaitACK
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: �ȴ������豸����Ӧ���ź�
*	˵    ��: ��SCLΪ�ߵ�ƽ�ڼ䣬����⵽SDA����Ϊ�͵�ƽ��������豸��Ӧ����
******************************************************************************************/

u8 Touch_IIC_WaitACK(void)
{
	Touch_IIC_SDA(1);
	Touch_IIC_Delay(IIC_DelayVaule);
	Touch_IIC_SCL(1);
	Touch_IIC_Delay(IIC_DelayVaule);	
	
	if( GPIO_ReadInputDataBit(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN) != 0) //�ж��豸�Ƿ���������Ӧ		
	{
		Touch_IIC_SCL(0);	
		return ACK_ERR;	//��Ӧ��
	}
	else
	{
		Touch_IIC_SCL(0);	
		return ACK_OK;	//Ӧ������
	}
}

/*****************************************************************************************
*	�� �� ��:	Touch_IIC_WriteByte
*	��ڲ���:	IIC_Data - Ҫд���8λ����
*	�� �� ֵ:	ACK_OK  - �豸��Ӧ����
*          	ACK_ERR - �豸��Ӧ����
*	��������:	дһ�ֽ�����
*	˵    ��:��λ��ǰ
******************************************************************************************/

u8 Touch_IIC_WriteByte(u8 IIC_Data)
{
	u8 i;

	for (i = 0; i < 8; i++)
	{
		Touch_IIC_SDA(IIC_Data & 0x80);
		
		Touch_IIC_Delay( IIC_DelayVaule );
		Touch_IIC_SCL(1);
		Touch_IIC_Delay( IIC_DelayVaule );
		Touch_IIC_SCL(0);		
		if(i == 7)
		{
			Touch_IIC_SDA(1);			
		}
		IIC_Data <<= 1;
	}

	return Touch_IIC_WaitACK(); //�ȴ��豸��Ӧ
}

/*****************************************************************************************
*	�� �� ��:	Touch_IIC_ReadByte
*	��ڲ���:	ACK_Mode - ��Ӧģʽ������1�򷢳�Ӧ���źţ�����0������Ӧ���ź�
*	�� �� ֵ:	ACK_OK  - �豸��Ӧ����
*          	ACK_ERR - �豸��Ӧ����
*	��������:��һ�ֽ�����
*	˵    ��:1.��λ��ǰ
*				2.Ӧ�������������һ�ֽ�����ʱ���ͷ�Ӧ���ź�
******************************************************************************************/

u8 Touch_IIC_ReadByte(u8 ACK_Mode)
{
	u8 IIC_Data = 0;
	u8 i = 0;
	
	for (i = 0; i < 8; i++)
	{
		IIC_Data <<= 1;
		
		Touch_IIC_SCL(1);
		Touch_IIC_Delay( IIC_DelayVaule );
		IIC_Data |= (GPIO_ReadInputDataBit(Touch_IIC_SDA_PORT,Touch_IIC_SDA_PIN) & 0x01);	
		Touch_IIC_SCL(0);
		Touch_IIC_Delay( IIC_DelayVaule );
	}
	
	if ( ACK_Mode == 1 )				//	Ӧ���ź�
		Touch_IIC_ACK();
	else
		Touch_IIC_NoACK();		 	// ��Ӧ���ź�
	
	return IIC_Data; 
}

