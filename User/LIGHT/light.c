#include "./LIGHT/light.h"
#include "control.h"
#include "FSM.h"
int barrier=NONE,blackR=NONE,blackL=NONE,collisionL=NONE,collisionR=NONE;
void TIM1_UP_IRQHandler(void)
{
	static int count=0;
	if(TIM1->SR&0X0001)
	{
		Sta_Refresh();
		control();
		count++;
	}
	if(count==15)
	{
		count=0;
		Analysis();
	}
	TIM1->SR&=~(1<<0);
}



void Light_Init()
{
	RCC->APB2ENR|=1<<6;
	RCC->APB2ENR|=1<<2;
	GPIOE->CRL&=0X00FFFFFF;	//PE5,6设置成输入	  
	GPIOE->CRL|=0X88000000;   
	GPIOE->ODR|=1<<5;
	GPIOE->ODR|=1<<6;
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
	static int uT=0,rT=0,lT=0;
	if(LIGHT_U==0)
	{
		barrier=EXIST;
		uT=5;
	}
	else
	{
		if(uT>0)
		uT--;
		if(uT==0)
		barrier=NONE;
	}

	if(LIGHT_R==1)
	{
		blackR=EXIST;
		rT=50;
	}
	else
	{
				if(rT>0)
		rT--;
		if(rT==0)
		blackR=NONE;
	}
		if(LIGHT_L==1)
	{
		blackL=EXIST;
		rT=50;
	}
	else
	{
				if(rT>0)
		rT--;
		if(rT==0)
		blackR=NONE;
	}
	if(PEin(6)==0)
	{
		collisionL=EXIST;
	}
	else
		collisionR=NONE;
}











