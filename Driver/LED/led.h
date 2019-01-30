#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx.h"

//����
#define LED1_PIN       GPIO_Pin_12
#define LED1_GPIO_PORT GPIOD
#define LED1_GPIO_CLK  RCC_AHB1Periph_GPIOD

//�Ƶ�
#define LED2_PIN       GPIO_Pin_7
#define LED2_GPIO_PORT GPIOG
#define LED2_GPIO_CLK  RCC_AHB1Periph_GPIOG


#define digitalHi(p,i)     {p->BSRRL|=i;} //����Ϊ�ߵ�ƽ
#define digitalLo(p,i)     {p->BSRRH|=i;} //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

#define LED1_TOGGLE   digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF      digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON       digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE   digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF      digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON       digitalLo(LED2_GPIO_PORT,LED2_PIN)

void LED_Init(void);

#endif



