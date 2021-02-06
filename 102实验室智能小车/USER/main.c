#include "stm32f10x.h"
#include "usart.h"	 
#include "USART2.h"
#include "timme.h"
#include "sys.h"
#include "key.h"
extern find_track find_tracks;
int ho; //����

int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��	 
  	LED_Init();
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� PA02
		Encoder_Init_TIM4();           //=====��ʼ��������4  PB06  PB07
		uart2_init(115200);                      //PA2 3
	  OLED_Init();                     //PB8 9
	  OLED_Clear();									  //=====OLED����
		Timer2_Init(999,7199);          //��ʱ����
		TIM1_PWM_Init(7199,0);   			 //=====��ʼ��PWM 10KHZ,�������������PA08  PA11 
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
			
			if(find_tracks.detect_mental_cout == 1)                                    //��һ�μ�⵽��������ʼѰ��
			{
				  TIM_Cmd(TIM4, ENABLE); 
         	TIM_Cmd(TIM2, ENABLE); 
				find_tracks.find_four_lines = 0;
			}
/************************************************************/			
		 else if( find_tracks.detect_mental_cout == 2)                               //�ڶ��δμ�⵽������
		 {
			 Turn_off();
			 TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx	
		 }
/************************************************************/				 
	   if(find_tracks.detect_mental_cout >= 0  && find_tracks.detect_mental_cout <= 1)  //û�м�⵽�����͵�һ�μ�⵽����Ѱ��
			   find_control();
/************************************************************/		
//		 if(find_tracks.find_flags3 == 1 && find_tracks.find_four_lines == 1)                                           //��ԴѰ��
//		 {
//			 find_light_control();
//			 find_tracks.find_flags3 = 0;
//		 }
/************************************************************/				 
		}
}




