#include "magec.h"
#include "stm32f10x.h"

void GPIOSet( GPIO_TypeDef* GPIOx,  u32 allPin,  u8 mode,  u8 otype,  u8 ospeed,  u8 pupd)
{
    u32 reg = 0; 
    u32 nowPin=0;  
    u32 i;  
    
    if(GPIOx==GPIOA )   RCC->APB2ENR |= RCC_APB2ENR_GPIOAEN ;
    if(GPIOx==GPIOB )   RCC->APB2ENR |= RCC_APB2ENR_GPIOBEN ;
    if(GPIOx==GPIOC )   RCC->APB2ENR |= RCC_APB2ENR_GPIOCEN ;
    if(GPIOx==GPIOD )   RCC->APB2ENR |= RCC_APB2ENR_GPIODEN ;
    if(GPIOx==GPIOE )   RCC->APB2ENR |= RCC_APB2ENR_GPIOEEN ;    
     
    // ģ������    
    if(mode == GPIO_MODE_AIN){
        reg |= 0;       
    }      
    // ��ͨ����    
    if(mode == GPIO_MODE_IN) {   
        if(pupd==0)  reg |= 0x01<<2;
        else         reg |= 0x02<<2;
    }
    
    if((ospeed &0x03)==0) ospeed= 0x03;       // ����ٶȣ�
    // ��ͨ���
    if(mode==GPIO_MODE_OUT){
        reg = ospeed & 0x03;                  // �����ٶ�
        reg |= (otype & 0x01)<<2;             // ��ͨ���졢��©
    }    
    // �������
    if(mode ==GPIO_MODE_AF){
        reg = ospeed & 0x03;                  // �����ٶ�
        reg |= ((otype | 0x02) & 0x03) <<2;   // �������졢��©
    }      
    
    // CHL, pin 0~7          
    for(i=0; i<8; i++) 
    {      
        nowPin = (u32) 0x01 << i;         // ��ǰҪ�жϵ����ź�     
        if((allPin & nowPin) != 0) {      // ��ǰ����Ҫ����
           GPIOx->CRL &= ~(0x0F<<(i*4));  // ��0
           GPIOx->CRL |= reg<<(i*4);      // д��������                
        }          
    }          
    
    // CRH, pin 8~15         
    for(i=0; i<8; i++)     {      
        nowPin = (u32) 0x01 << (i+8);     // ��ǰҪ�жϵ����ź�     
        if((allPin & nowPin) != 0) {      // ��ǰ����Ҫ����
           GPIOx->CRH &= ~(0x0F<<(i*4));  // ��0
           GPIOx->CRH |= reg<<(i*4);      // д��������                
        }          
    }             
    
    if(pupd== GPIO_PUPD_UP )   GPIOx->BSRR |= allPin ;
    if(pupd== GPIO_PUPD_DOWN)  GPIOx->BSRR |= allPin << 16;      
}

/***************************************************************************** 
 * ��  ���� EXTISet
 * ��  �ܣ� �ⲿ�ж����ú���
 *         ��Ҫ: һ��ֻ������1��IO��,  2020-2-26
 *         ֻ���GPIOA~G;������PVD,RTC��USB����������
 *         �ú������Զ�������Ӧ�ж�,�Լ�������  
 *         
 * ��  ���� ��GPIOx��:GPIOA~G, ����GPIOA~G
 *          ��BITx��:PIN0~15, ��Ҫʹ�ܵ�λ;
 *          ��TRIM��:����ģʽ, EXTI_FTIR/1:�½���;  EXTI_RTIR/2:������; 3:�����ƽ����
 * ��  �أ� ��
*****************************************************************************/
void EXTISet(GPIO_TypeDef* GPIOx, u16 PINx, u8 TRIM)
{
    u8 gpioNum = 0,i,offSet;
    u8 pinNum  = 0;
    
    // ת��GPIOxΪ����
    if(GPIOx==GPIOA )  gpioNum=0;
    if(GPIOx==GPIOB )  gpioNum=1;
    if(GPIOx==GPIOC )  gpioNum=2;
    if(GPIOx==GPIOD )  gpioNum=3; 
    if(GPIOx==GPIOE )  gpioNum=4; 
    if(GPIOx==GPIOF )  gpioNum=5; 
    if(GPIOx==GPIOG )  gpioNum=6; 
    
    // ת��PINxΪ����
    for(i=0; i<16; i++){
        if( PINx== ((u32)1<<i)){
            pinNum=i;
            break;
        }          
    }    
    
    offSet   = (pinNum%4)*4;                    // �Ĵ�����ƫ��
	RCC->APB2ENR |=0x01;                           // ʹ��io����ʱ��			 
	AFIO->EXTICR[pinNum/4] &=~(0x000F << offSet);  // ��0
	AFIO->EXTICR[pinNum/4] |=  gpioNum << offSet;  // EXTI.BITxӳ�䵽GPIOx.BITx 
	// ʹ��line BITx�ϵ��ж�, 1:ʹ��  0:����
	EXTI->IMR |= PINx ;                            
     // ������
    if(TRIM & 0x01)  EXTI->FTSR |= PINx ;          // line BITx���¼��½��ش���
	if(TRIM & 0x02)  EXTI->RTSR |= PINx ;          // line BITx���¼��������ش���
}


/******************************************************************************
 * ��  ���� NVICSet
 * ��  �ܣ� ���ȼ����ã�Ϊ�������ʹ��FreeRTOS��ͳһʹ��4λ��ռ��(16��),0λ�����ȼ�(0��)
 *         ֱ�ӵ��ü��ɣ�������ǰ����
 * ��  ���� NVIC_Channel�ж����ͣ�Preemption���ȼ�
 * ����ֵ�� ��
******************************************************************************/
void NVICSet(u8 NVIC_Channel, u8 Preemption)
{    
    static u8 setGrouped=0;
    if(setGrouped ==0){
        // ȫ�ַּ�����,ͳһΪ��4, ֵ0b11,����NVIC->IPx�и�4λ:����4λ(16��), �Ӽ�0λ(0����  
        SCB->AIRCR = ((u32)0x05FA0000)|(0x03<<8);   // ���ȼ���������, �Ѳ�,��3�� F103��F429�Ĵ���ͨ��	    
        setGrouped =1;
    }
    
    // ͨ���ж����ȼ�����
    NVIC->IP[NVIC_Channel] &= ~(0xF<<4);                     // ��� 		 
    NVIC->IP[NVIC_Channel]  =  (Preemption&0xF)<<4;          // д����ռ��\���ȼ�
    // ͨ���ж�ʹ��
    NVIC->ISER[NVIC_Channel/32] |= 1 << (NVIC_Channel % 32); // ʹ���ж�ͨ��	    
    //NVIC->ICER[];   		                                 // �ж�ʧ��, �����õ�	   
}



