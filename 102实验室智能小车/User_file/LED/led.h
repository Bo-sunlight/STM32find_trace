#ifndef __LED_E
#define __LED_E
#include "sys.h"

//��ֲ������ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  LED_RED_GPIO      GPIOC
#define  LED_RED_PIN       PIN13   
#define  LED_RED_CLK       RCC_APB2Periph_GPIOB   // ���ʹ�ù̼������Ҫ����

// ��ɫ�򻯹���, ��ֲʱ�����޸�
// red
#define LED_RED_ON         LED_RED_GPIO->BSRR |= LED_RED_PIN <<16           // �õ͵�ƽ
#define LED_RED_OFF        LED_RED_GPIO->BSRR |= LED_RED_PIN 
#define LED_RED_TOGGLE     LED_RED_GPIO->ODR  ^= LED_RED_PIN                // ��ƽ��ת


void LED_Init(void);


#endif


