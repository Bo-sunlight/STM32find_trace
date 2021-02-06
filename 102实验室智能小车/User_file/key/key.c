#include "key.h"
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	
//	GPIOSet(KEY_GPIO ,KEY_PIN ,GPIO_MODE_IN ,GPIO_OTYPE_PP ,GPIO_OSPEED_50M , GPIO_PUPD_UP );
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(WK_UP==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(WK_UP==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(WK_UP==1)key_up=1; 	    
 	return 0;// 无按键按下
}


void KEY1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	           //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
} 
/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：单击 
**************************************************************************/
int KEY1_Scan(void)
{
			static u8 flag_key=1;//按键按松开标志   static只能初始化一次
			if(flag_key&&KEY==0)
			{
				flag_key=0;       //不进入按键松开函数就一直是0
				return 1;	// 按键按下  
			}
			else if(1==KEY)			
			{
				flag_key=1;
				return 0;//无按键按下
			}
}


