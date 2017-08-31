#include "./MOTOR/motor.h"
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ��   
	GPIOA->CRL&=0X0000FFFF;   //PORTA4 5 6 7�������
	GPIOA->CRL|=0X22220000;   //PORTA4 5 6 7�������
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	MiniBalance_Motor_Init(); //��ʼ�������������IO
	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��    
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��     
	GPIOB->CRL&=0XFFFFFF00;   //PORTB0 1�������
	GPIOB->CRL|=0X000000BB;   //PORTB0 1�������
	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	TIM3->CCMR2|=6<<12;//CH4 PWM1ģʽ	
	TIM3->CCMR2|=6<<4; //CH3 PWM1ģʽ	
	TIM3->CCMR2|=1<<11;//CH4Ԥװ��ʹ��	 
	TIM3->CCMR2|=1<<3; //CH3Ԥװ��ʹ��	  
	TIM3->CCER|=1<<12; //CH4���ʹ��	   
	TIM3->CCER|=1<<8;  //CH3���ʹ��	
	TIM3->CR1=0x8000;  //ARPEʹ�� 
	TIM3->CR1|=0x01;   //ʹ�ܶ�ʱ��3 										  
} 


/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
			if(moto1>MOTOR_MAX_PWM)
			 moto1=MOTOR_MAX_PWM;
			if(moto2>MOTOR_MAX_PWM)
			 moto2=MOTOR_MAX_PWM;
			if(moto1<0)			BIN2=1,			BIN1=0;
			else 	          BIN2=0,			BIN1=1;

			PWMB=myabs(moto1);
		  if(moto2<0)	AIN1=0,			AIN2=1;
			else        AIN1=1,			AIN2=0;
			PWMA=myabs(moto2);	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

