#ifndef __USART2_E
#define __USART2_E
#include "sys.h"
#include "openmv_data.h"

#define USART2_INTERRUPT  1         //1为执行串口中断函数
void uart2_init(u32 bound);

#endif
