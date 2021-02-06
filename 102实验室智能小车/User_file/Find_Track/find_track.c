#include "find_track.h"
#define Pi 3.141592f
find_track find_tracks;
extern openmv openmv_data;
void find_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIOE2,3,4
}

void Beep_Mental_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIOSet(GPIOB ,PIN0 ,GPIO_MODE_OUT ,GPIO_OTYPE_PP ,GPIO_OSPEED_50M , GPIO_PUPD_NOPULL );
	BEEP_OFF;                        

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIOE2,3,4	
}

void Find_light_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure1; 

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIOE2,3,4	
	
	GPIO_InitStructure1.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPD;       //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure1);  
	
}

void find_light_control(void)
{
		 if(find_light1==0&&find_light2==1&&find_light3==1)       //左转	 
		 {
			PWMA = 1600;
			PWMB = 1600;
		  AIN1=0,AIN2=1;   //右电机
	    BIN1=1,BIN2=0;  
		 }			 
		 
		 else if(find_light1==1&&find_light2==1&&find_light3==0)       //右转
		 {
	    PWMA = 1600;
			PWMB = 1600;
		  AIN1=1,AIN2=0;   //右电机
	    BIN1=0,BIN2=1;  
		 }
	   else
		 {
			PWMA = 1000;
			PWMB = 1000;
	  	AIN1=1,AIN2=0;         
	    BIN1=1,BIN2=0;   
		 }
		   
}

void Remind_light_beep(void)
{
	 int flag = 0;
	static int i = 0;
	if(openmv_data.datas[0]!=0 && i==0 )
	{
		 BEEP_ON;
		LED_RED_ON;
		delay_ms(500);
		LED_RED_TOGGLE;
		BEEP_TOGGLE;
		i = 1;
	}
	
	if(detect_mental == 0 && flag == 0)
	{
		find_tracks.detect_mental_cout++;
		BEEP_ON;
		LED_RED_ON;
		delay_ms(500);
		LED_RED_TOGGLE;
		BEEP_TOGGLE;
		flag = 1;
	}
	
		if(find_tracks.find_flags2 == 1 && flag == 0 )
	{
		BEEP_ON;
		LED_RED_ON;
		delay_ms(500);
		LED_RED_TOGGLE;
		BEEP_TOGGLE;
		flag = 1;
		find_tracks.find_flags2 = 0;
	}
}

void find_control()                             
{
	 if(find_1==0&&find_2==0&&find_3==0&&find_4==0)       //直行
	 {
		 
		  find_tracks.find_zero_lines = 1;
	        Go_foward();
	 }
	
	 else if(find_1==0&&find_2==0&&find_3==0&&find_4==1)        //大右转   第四个检测到黑线（从左往右）
		 	         Go_big_right();   
	
	 else if(find_1==0&&find_2==0&&find_3==1&&find_4==0)      //右转   第3个检测到黑线（从左往右）
		 	         Go_right();
                                
	 else if(find_1==0&&find_2==1&&find_3==0&&find_4==0)      //左转      第2个检测到黑线（从左往右）
		 		              Go_left();   
	 
	 	 else if(find_1==1&&find_2==0&&find_3==0&&find_4==0)      //大左转      第2个检测到黑线（从左往右）
		 		              Go_big_left();  

	  else if(find_1==1&&find_2==1&&find_3==0&&find_4==0)         //大左转   第1、2个检测到黑线（从左往右）
	             Go_big_left();
	 
	 	 else if(find_1==0&&find_2==0&&find_3==1&&find_4==1)        //大右转   第3、4个检测到黑线（从左往右）
	             Go_big_right();
		 
		 else if(find_1==1&&find_2==1&&find_3==1&&find_4==0)         //大左转   第1、2个检测到黑线（从左往右）
	             Go_big_left();
	 
	 	 else if(find_1==0&&find_2==1&&find_3==1&&find_4==1)        //大右转   第3、4个检测到黑线（从左往右）
	             Go_big_right();
    else 
         		Go_foward();
 }

void Go_foward()
{
			PWMA = 2000;
			PWMB = 2000;
	  	AIN1=1,AIN2=0;         
	    BIN1=1,BIN2=0;   
}

void Go_left()
{
			PWMA = Turn_PWM;
			PWMB = Turn_PWM;
		  AIN1=0,AIN2=1;   //右电机
	    BIN1=1,BIN2=0;  
}

void Go_right()
{
			PWMA = Turn_PWM;
			PWMB = Turn_PWM;
	  	AIN1=1,AIN2=0;   //右电机
	    BIN1=0,BIN2=1; 
}

void Go_big_left()
{
			PWMA = Turn_Big_PWM;
			PWMB = Turn_Big_PWM;
	
		  AIN1=0,AIN2=1;   //右电机
	    BIN1=1,BIN2=0;  
  
	
}
void Go_big_right()
{
			PWMA = Turn_Big_PWM;
			PWMB = Turn_Big_PWM;
	  	AIN1=1,AIN2=0;   //右电机
	    BIN1=0,BIN2=1; 
}

void Go_return()
{
			PWMA = Turn_PWM;
			PWMB = Turn_PWM;
	  	AIN1=0,AIN2=1;   //右电机
	    BIN1=0,BIN2=1;   
}

void Turn_off()
{
	
		  AIN1=0,AIN2=0;   //右电机
	    BIN1=0,BIN2=0;  
}

void Display_Time(void)
{
		OLED_ShowString(25,0,"102",16);      //8*16 “TIME:”
	  OLED_ShowCHinese(50,0,0);
		OLED_ShowCHinese(67,0,1);
		OLED_ShowCHinese(84,0,2);
	
	OLED_ShowString(0,3,"TIME:",12);      //8*16 “TIME:”
	OLED_Num2(50,3,find_tracks.Clock_Shi);
	OLED_ShowString(65,3,":",12);       //8*16 “:” 
  OLED_Num2(54,3,find_tracks.Clock_minute);
	OLED_ShowString(88,3,":",12);       //8*16 “:”
	OLED_Num2(58,3,find_tracks.Clock_Second);
  find_tracks.Encoder_Sum_flag  = 0;
}

void Display_Code(void)
{
	OLED_ShowString(0,5,"CODE:",12);//8*16 “CODE:”
	OLED_Num3(50,5,(double)openmv_data.datas[0]);
}

void Display_Distance(void)
{
	OLED_ShowString(0,7,"DISA:",12);//8*16 “DISTANCE:”
//		 OLED_Float2(38,7,find_tracks.distance,3,1);
	   		OLED_Float(48,7,(double)find_tracks.distance,2);
		OLED_ShowString(98,7,"CM",12);//8*16 “CODE:”
}

void Count_Distance(void)
{
//		find_tracks.Encoder_Sum = find_tracks.Encoder_Sum+Read_Encoder(4);
		find_tracks.distance = find_tracks.distance+Read_Encoder(4)*(2*3.4*Pi)/1500;
}

void display(void)
{
		if(find_tracks.Encoder_Sum_flag == 1)
	{
			Display_Distance();
			Display_Code();
			Display_Time();
			Count_Distance();
	}	
}
	



