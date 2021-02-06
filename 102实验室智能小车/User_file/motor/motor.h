#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	

 /**************************************************************************
 作  者 ：大鱼电子
淘宝地址：https://shop119207236.taobao.com
**************************************************************************/

#define PWMB   TIM1->CCR1  //PA8

#define AIN2   PBout(13)
#define AIN1   PBout(12)

#define BIN1   PBout(14)
#define BIN2   PBout(15)

#define PWMA   TIM1->CCR4  //PA11

void Motor_Init(void);
void Set_Pwm(int moto1,int moto2);
int myabs(int a);
void TIM1_PWM_Init(u16 arr,u16 psc);
void Xianfu_Pwm(void);
void Turn_Off(float angle, float voltage);
#endif
