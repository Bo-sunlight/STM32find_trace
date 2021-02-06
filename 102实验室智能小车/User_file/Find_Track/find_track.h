#ifndef __FIND_TRACK
#define __FIND_TRACK
#include <sys.h>	

typedef struct
{
  char    Clock_num ; 
	char    Clock_minute; 
	char    Clock_Second; 
  char    Clock_Shi; 
	float   distance;
	int     Encoder_Sum;
	char    Encoder_Sum_flag;
	char    detect_mental_cout;
	char   find_four_lines;
	char    find_zero_lines;
	char    find_flags2;
	char     find_flags3;
}find_track;



#define find_1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)        //寻迹模块输入
#define find_2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define find_3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define find_4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)

#define find_light1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define find_light2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define find_light3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)

#define detect_mental GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)  //金属探测输入

#define BEEP_ON        GPIOB->BSRR |= GPIO_Pin_0 <<16           // 置低电平
#define BEEP_OFF         GPIOB->BSRR |= GPIO_Pin_0 
#define BEEP_TOGGLE     GPIOB->ODR  ^= GPIO_Pin_0                // 电平反转

#define Turn_PWM  2500
#define Turn_Big_PWM  3000

void Find_light_Init(void);
void find_light_control(void);
void Beep_Mental_Init(void);
void Remind_light_beep(void);

void find_Init(void);
void find_control(void);

void Go_foward(void);

void Go_left(void);
void Go_right(void);

void Go_big_left(void);
void Go_big_right(void);

void Go_return(void);
void Turn_off(void);

void Display_Time(void); //时间显示
void Display_Code(void);//二维码显示
void Display_Distance(void); //距离显示
void Count_Distance(void);
void display(void);

#endif


