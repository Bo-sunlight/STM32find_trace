#ifndef __MAGIC_H
#define __MAGIC_H	

#include <stm32f10x.h>    // 优先使用用户目录中文件，方便修改优化。这个文件是必须的， 各种地址和参数的宏定义
#include "stdio.h"        // printf要用到
#include "string.h"

////////////////////////////////////////////////////////////////////////////////// 
// 【 2 】GPIO引脚编号定义
#define  PIN0                  ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define  PIN1                  ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define  PIN2                  ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define  PIN3                  ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define  PIN4                  ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define  PIN5                  ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define  PIN6                  ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define  PIN7                  ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define  PIN8                  ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define  PIN9                  ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define  PIN10                 ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define  PIN11                 ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define  PIN12                 ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define  PIN13                 ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define  PIN14                 ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define  PIN15                 ((uint16_t)0x8000)  /*!< Pin 15 selected */  
 

// 时钟使能_宏定义_为兼容F4xx的格式 *********************** 
#define  RCC_APB2ENR_GPIOAEN   ((uint32_t)0x00000004)         /*!< I/O port A clock enable */
#define  RCC_APB2ENR_GPIOBEN   ((uint32_t)0x00000008)         /*!< I/O port B clock enable */
#define  RCC_APB2ENR_GPIOCEN   ((uint32_t)0x00000010)         /*!< I/O port C clock enable */
#define  RCC_APB2ENR_GPIODEN   ((uint32_t)0x00000020)         /*!< I/O port D clock enable */
#define  RCC_APB2ENR_GPIOEEN   ((uint32_t)0x00000040)         /*!< I/O port D clock enable */

////////////////////////////////////////////////////////////////////////////////// 
// 【 4 】 GPIOSet()专用参数
#define GPIO_MODE_AIN	        0	    // 模拟输入模式
#define GPIO_MODE_IN            1		// 普通输入模式
#define GPIO_MODE_OUT		    2		// 普通输出模式
#define GPIO_MODE_AF		    3		// AF功能模式

#define GPIO_OTYPE_PP		    0		// 推挽输出
#define GPIO_OTYPE_OD		    1		// 开漏输出 

#define GPIO_OSPEED_10M		    1		// GPIO速度2Mhz
#define GPIO_OSPEED_2M		    2		// GPIO速度2Mhz
#define GPIO_OSPEED_50M		    3		// GPIO速度50Mhz

#define GPIO_PUPD_NOPULL        0		// 不带上下拉
#define GPIO_PUPD_UP		    1		// 上拉
#define GPIO_PUPD_DOWN		    2		// 下拉


//  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
//  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
//  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
//  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
//  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
//  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
//  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
//  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
//  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
//  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
//  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
//  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
//  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
//  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
//  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
//  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
//  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
//  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
//  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
//  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
//  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
//  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
//  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
//  RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
//  USBWakeUp_IRQn              = 42      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */  


// 2_3大初始化函数
void  GPIOSet( GPIO_TypeDef* GPIOx,  u32 PINx,  u8 MODE,  u8 OTYPE,  u8 OSPEED,  u8 PUPD);
void  NVICSet(u8 NVIC_Channel,u8 Preemption);           // 优先级设置, 已分好组, 4位抢占级, 16级, 无子级
void  EXTISet(GPIO_TypeDef* GPIOx, u16 PINx, u8 TRIM);  // 外部中断配置函数



#endif



