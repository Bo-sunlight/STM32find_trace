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
     
    // 模拟输入    
    if(mode == GPIO_MODE_AIN){
        reg |= 0;       
    }      
    // 普通输入    
    if(mode == GPIO_MODE_IN) {   
        if(pupd==0)  reg |= 0x01<<2;
        else         reg |= 0x02<<2;
    }
    
    if((ospeed &0x03)==0) ospeed= 0x03;       // 输出速度，
    // 普通输出
    if(mode==GPIO_MODE_OUT){
        reg = ospeed & 0x03;                  // 引脚速度
        reg |= (otype & 0x01)<<2;             // 普通推挽、开漏
    }    
    // 复用输出
    if(mode ==GPIO_MODE_AF){
        reg = ospeed & 0x03;                  // 引脚速度
        reg |= ((otype | 0x02) & 0x03) <<2;   // 复用推挽、开漏
    }      
    
    // CHL, pin 0~7          
    for(i=0; i<8; i++) 
    {      
        nowPin = (u32) 0x01 << i;         // 当前要判断的引脚号     
        if((allPin & nowPin) != 0) {      // 当前引脚要配置
           GPIOx->CRL &= ~(0x0F<<(i*4));  // 清0
           GPIOx->CRL |= reg<<(i*4);      // 写入新配置                
        }          
    }          
    
    // CRH, pin 8~15         
    for(i=0; i<8; i++)     {      
        nowPin = (u32) 0x01 << (i+8);     // 当前要判断的引脚号     
        if((allPin & nowPin) != 0) {      // 当前引脚要配置
           GPIOx->CRH &= ~(0x0F<<(i*4));  // 清0
           GPIOx->CRH |= reg<<(i*4);      // 写入新配置                
        }          
    }             
    
    if(pupd== GPIO_PUPD_UP )   GPIOx->BSRR |= allPin ;
    if(pupd== GPIO_PUPD_DOWN)  GPIOx->BSRR |= allPin << 16;      
}

/***************************************************************************** 
 * 函  数： EXTISet
 * 功  能： 外部中断配置函数
 *         重要: 一次只能配置1个IO口,  2020-2-26
 *         只针对GPIOA~G;不包括PVD,RTC和USB唤醒这三个
 *         该函数会自动开启对应中断,以及屏蔽线  
 *         
 * 参  数： 【GPIOx】:GPIOA~G, 代表GPIOA~G
 *          【BITx】:PIN0~15, 需要使能的位;
 *          【TRIM】:触发模式, EXTI_FTIR/1:下降沿;  EXTI_RTIR/2:上升沿; 3:任意电平触发
 * 返  回： 无
*****************************************************************************/
void EXTISet(GPIO_TypeDef* GPIOx, u16 PINx, u8 TRIM)
{
    u8 gpioNum = 0,i,offSet;
    u8 pinNum  = 0;
    
    // 转换GPIOx为数字
    if(GPIOx==GPIOA )  gpioNum=0;
    if(GPIOx==GPIOB )  gpioNum=1;
    if(GPIOx==GPIOC )  gpioNum=2;
    if(GPIOx==GPIOD )  gpioNum=3; 
    if(GPIOx==GPIOE )  gpioNum=4; 
    if(GPIOx==GPIOF )  gpioNum=5; 
    if(GPIOx==GPIOG )  gpioNum=6; 
    
    // 转换PINx为数字
    for(i=0; i<16; i++){
        if( PINx== ((u32)1<<i)){
            pinNum=i;
            break;
        }          
    }    
    
    offSet   = (pinNum%4)*4;                    // 寄存器内偏移
	RCC->APB2ENR |=0x01;                           // 使能io复用时钟			 
	AFIO->EXTICR[pinNum/4] &=~(0x000F << offSet);  // 清0
	AFIO->EXTICR[pinNum/4] |=  gpioNum << offSet;  // EXTI.BITx映射到GPIOx.BITx 
	// 使能line BITx上的中断, 1:使能  0:屏蔽
	EXTI->IMR |= PINx ;                            
     // 触发沿
    if(TRIM & 0x01)  EXTI->FTSR |= PINx ;          // line BITx上事件下降沿触发
	if(TRIM & 0x02)  EXTI->RTSR |= PINx ;          // line BITx上事件上升降沿触发
}


/******************************************************************************
 * 函  数： NVICSet
 * 功  能： 优先级设置，为方便管理及使用FreeRTOS，统一使用4位抢占级(16级),0位子优先级(0级)
 *         直接调用即可，不用提前配置
 * 参  数： NVIC_Channel中断类型，Preemption优先级
 * 返回值： 无
******************************************************************************/
void NVICSet(u8 NVIC_Channel, u8 Preemption)
{    
    static u8 setGrouped=0;
    if(setGrouped ==0){
        // 全局分级设置,统一为组4, 值0b11,即：NVIC->IPx中高4位:主级4位(16级), 子级0位(0级）  
        SCB->AIRCR = ((u32)0x05FA0000)|(0x03<<8);   // 优先级分组设置, 已查,是3， F103和F429寄存器通用	    
        setGrouped =1;
    }
    
    // 通道中断优先级设置
    NVIC->IP[NVIC_Channel] &= ~(0xF<<4);                     // 清空 		 
    NVIC->IP[NVIC_Channel]  =  (Preemption&0xF)<<4;          // 写入抢占级\优先级
    // 通道中断使能
    NVIC->ISER[NVIC_Channel/32] |= 1 << (NVIC_Channel % 32); // 使能中断通道	    
    //NVIC->ICER[];   		                                 // 中断失能, 很少用到	   
}



