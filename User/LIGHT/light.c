#include "./LIGHT/light.h"
#include "control.h"
#include "FSM.h"
int barrier=NONE,blackR=NONE,blackL=NONE,blackUR=NONE,blackUL=NONE,collisionL=NONE,collisionR=NONE;

void TIM1_UP_IRQHandler(void)
{
	static int count=0;
	if(TIM1->SR&0X0001)
	{
			Sta_Refresh();
			control();
			count++;
		
		if(count==10)
		{
			count=0;
			Analysis();
		}
	}
	TIM1->SR&=~(1<<0);
}



void Light_Init()
{
	RCC->APB2ENR|=1<<4;
	RCC->APB2ENR|=1<<5;
	RCC->APB2ENR|=1<<2;
	GPIOC->CRH&=0XFF0000FF;	//PC10��11��12��13���ó�����	  
	GPIOC->CRH|=0X00888800;   
	GPIOC->ODR|=1<<13;
	GPIOC->ODR|=1<<12;
	GPIOC->ODR|=1<<11;
	GPIOC->ODR|=1<<10;
	GPIOD->CRL&=0XFFFFF0FF;	//PD2���ó�����	  
	GPIOD->CRL|=0X00000800;   
	GPIOD->ODR|=1<<2;
	//GPIOE->ODR|=1<<6;
	GPIOA->CRH&=0XFFF00FFF;	//PA12���ó�����	  
	GPIOA->CRH|=0X00088000;   
	GPIOA->ODR|=1<<12;
	GPIOA->ODR|=1<<11;

	
	RCC->APB2ENR|=1<<11;//TIM1ʱ��ʹ��    
 	TIM1->ARR=5;      //�趨�������Զ���װֵ   
	TIM1->PSC=7199;      //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	TIM1->DIER|=1<<0;   //��������ж�				
	TIM1->DIER|=1<<6;   //�������ж�	   
	TIM1->CR1|=0x01;    //ʹ�ܶ�ʱ��
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
		if(PCin(11)==1)
	{
		blackUL=EXIST;
	
	}
	else
	{
   blackUL=NONE;
	}
			if(PCin(12)==1)
	{
    blackUR=EXIST;
	}
	else
	{
   blackUR=NONE;
	}
			if(PDin(2)==0)
	{
    collisionR=EXIST;
	}
	else
	{
   collisionR=NONE;
	}
	if(PCin(10)==0)
	{
		collisionL=EXIST;
	}
	else
		collisionL=NONE;
}











