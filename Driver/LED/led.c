#include "delay.h"
#include "led.h"

/***********************************************************
*函数功能：LED初始化
*传入参数：无
*返回值  ：无
***********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|LED2_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	/*设置引脚模式为输出模式*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;/*设置引脚速率为 2MHz */
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);/*调用库函数，使用上面配置的 GPIO_InitStructure 初始化 GPIO*/

	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);/*调用库函数，使用上面配置的 GPIO_InitStructure 初始化 GPIO*/
}
