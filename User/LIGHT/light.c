#include "./LIGHT/light.h"
#include "control.h"
int barrier=NONE,blackR=NONE,blackL=NONE;
void TIM1_UP_IRQHandler(void)
{
	if(TIM1->SR&0X0001)
	{
		Sta_Refresh();
		control();
	}
	TIM1->SR&=~(1<<0);
}



void Light_Init()
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRH&=0XFFF00FFF;	//PA12设置成输入	  
	GPIOA->CRH|=0X00088000;   
	GPIOA->ODR|=1<<12;
	GPIOA->ODR|=1<<11;

	
	RCC->APB2ENR|=1<<11;//TIM1时钟使能    
 	TIM1->ARR=5;      //设定计数器自动重装值   
	TIM1->PSC=7199;      //预分频器7200,得到10Khz的计数时钟
	TIM1->DIER|=1<<0;   //允许更新中断				
	TIM1->DIER|=1<<6;   //允许触发中断	   
	TIM1->CR1|=0x01;    //使能定时器
	MY_NVIC_Init(1,3,TIM1_UP_IRQn,2);


}

void Sta_Refresh()
{
	if(LIGHT_U==0)
		barrier=EXIST;
	else
		barrier=NONE;

	if(LIGHT_R==1)
		blackR=EXIST;
	else
		blackR=NONE;
	
}











