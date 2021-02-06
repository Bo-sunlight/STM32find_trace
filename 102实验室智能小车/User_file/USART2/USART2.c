#include "USART2.h"

void uart2_init(u32 bound)
{
      //GPIO�˿�����
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
       NVIC_InitTypeDef NVIC_InitStructure;
      //|RCC_APB2Periph_AFIO
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //PA2
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //��������
      GPIO_Init(GPIOA, &GPIO_InitStructure);
  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
      GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ

    
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
    USART_InitStructure.USART_BaudRate = bound;//����������
     USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
     USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
 
     USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
     USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
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
		OPNMV_DataHandle((unsigned char)USART2->DR);//��������
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}
#endif





