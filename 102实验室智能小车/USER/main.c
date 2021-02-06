#include "stm32f10x.h"
#include "usart.h"	 
#include "USART2.h"
#include "timme.h"
#include "sys.h"
#include "key.h"
extern find_track find_tracks;
int ho; //测试

int main(void)
{
    delay_init();	    	 //延时函数初始化	 
  	LED_Init();
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 PA02
		Encoder_Init_TIM4();           //=====初始化编码器4  PB06  PB07
		uart2_init(115200);                      //PA2 3
	  OLED_Init();                     //PB8 9
	  OLED_Clear();									  //=====OLED清屏
		Timer2_Init(999,7199);          //定时器二
		TIM1_PWM_Init(7199,0);   			 //=====初始化PWM 10KHZ,用于驱动电机。PA08  PA11 
		Motor_Init();                  
		find_Init();       
    Beep_Mental_Init();	
  	Find_light_Init();
		while(1)
		{      
      Remind_light_beep();
			display();
		
		if(find_1==1&&find_2==1&&find_3==1&&find_4==1)          
		 {
		  find_tracks.find_four_lines = ~find_tracks.find_four_lines;
		 	find_tracks.find_flags2 = 1;
			PWMA = 3800;
			PWMB = 3800;
	  	AIN1=1,AIN2=0;         
	    BIN1=1,BIN2=0;   
		 }
			
			if(find_tracks.detect_mental_cout == 1)                                    //第一次检测到金属，开始寻迹
			{
				  TIM_Cmd(TIM4, ENABLE); 
         	TIM_Cmd(TIM2, ENABLE); 
				find_tracks.find_four_lines = 0;
			}
/************************************************************/			
		 else if( find_tracks.detect_mental_cout == 2)                               //第二次次检测到金属，
		 {
			 Turn_off();
			 TIM_Cmd(TIM2, DISABLE);  //使能TIMx	
		 }
/************************************************************/				 
	   if(find_tracks.detect_mental_cout >= 0  && find_tracks.detect_mental_cout <= 1)  //没有检测到金属和第一次检测到金属寻迹
			   find_control();
/************************************************************/		
//		 if(find_tracks.find_flags3 == 1 && find_tracks.find_four_lines == 1)                                           //光源寻迹
//		 {
//			 find_light_control();
//			 find_tracks.find_flags3 = 0;
//		 }
/************************************************************/				 
		}
}




