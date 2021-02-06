#include "USART2.h"

void uart2_init(u32 bound)
{
      //GPIO端口设置
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
       NVIC_InitTypeDef NVIC_InitStructure;
      //|RCC_APB2Periph_AFIO
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //PA2
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽
      GPIO_Init(GPIOA, &GPIO_InitStructure);
  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
      GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//复位串口2
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//停止复位

    
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
     USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
     USART_InitStructure.USART_Parity = USART_Parity_No;///奇偶校验位
     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
 
     USART_Init(USART2, &USART_InitStructure); ; //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
     USART_Cmd(USART2, ENABLE);                    //使能串口 
}

#if USART2_INTERRUPT
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2,USART_IT_TXE) != RESET)
  {   
//    USART_SendData(USART2, TxBuffer[TxCounter++]); 
//    USART_ClearITPendingBit(USART2, USART_IT_TXE);
//    if(TxCounter == count) USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
  }
	
	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		USART2->DR;
		USART2->SR;
		OPNMV_DataHandle((unsigned char)USART2->DR);//处理数据
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}
#endif





