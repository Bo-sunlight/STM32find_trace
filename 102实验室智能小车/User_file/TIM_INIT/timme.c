#include "timme.h"
#include "led.h"
extern find_track find_tracks;

void Timer2_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //    指定抢占式优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  ////指定响应式优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM2, DISABLE);  //使能TIMx	
}


void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			find_tracks.Encoder_Sum_flag = 1;       //读取编码器标志位
			
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		        find_tracks.Clock_num++;
        if(find_tracks.Clock_num>=10)
            {		
              LED_RED_TOGGLE;							
							find_tracks.Clock_num=0;
							find_tracks.Clock_Second++;
							if(find_tracks.Clock_Second>=60)
							{
								find_tracks.Clock_Second=0;
								find_tracks.Clock_minute++;
								if(find_tracks.Clock_minute>=60)
								{
									find_tracks.Clock_minute=0;
									find_tracks.Clock_Shi++;
								}
							}

            }		
						
		}
}







