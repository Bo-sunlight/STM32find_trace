#include "led.h"

void LED_Init(void)
{
 
	    GPIOSet(LED_RED_GPIO ,LED_RED_PIN ,GPIO_MODE_OUT ,GPIO_OTYPE_PP ,GPIO_OSPEED_50M , GPIO_PUPD_NOPULL );
      LED_RED_ON;                                      
}

