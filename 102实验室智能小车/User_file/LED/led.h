#ifndef __LED_E
#define __LED_E
#include "sys.h"

//移植参数区 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  LED_RED_GPIO      GPIOC
#define  LED_RED_PIN       PIN13   
#define  LED_RED_CLK       RCC_APB2Periph_GPIOB   // 如果使用固件库就需要定义

// 按色简化功能, 移植时不用修改
// red
#define LED_RED_ON         LED_RED_GPIO->BSRR |= LED_RED_PIN <<16           // 置低电平
#define LED_RED_OFF        LED_RED_GPIO->BSRR |= LED_RED_PIN 
#define LED_RED_TOGGLE     LED_RED_GPIO->ODR  ^= LED_RED_PIN                // 电平反转


void LED_Init(void);


#endif


