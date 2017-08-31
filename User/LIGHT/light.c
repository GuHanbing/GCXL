#include "./LIGHT/light.h"

int barrier,blackR,blackL;
void TIM1_UP_IRQHandler(void)
{
	if(TIM1->SR&0X0001)
	{
		Sta_Refresh();
	}
	TIM1->SR&=~(1<<0);
}



void Light_Init()
{
	RCC->APB2ENR|=1<<2;
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
	if(LIGHT_U==0)
		barrier=EXIST;
	else
		barrier=NONE;
	
	if(LIGHT_R==1)
		blackR=EXIST;
	else
		blackR=NONE;
	
}











