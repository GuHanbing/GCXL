#include "./MOTOR/motor.h"
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<2;       //PORTA时钟使能   
	GPIOA->CRL&=0X0000FFFF;   //PORTA4 5 6 7推挽输出
	GPIOA->CRL|=0X22220000;   //PORTA4 5 6 7推挽输出
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	MiniBalance_Motor_Init(); //初始化电机控制所需IO
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能    
	RCC->APB2ENR|=1<<3;       //PORTB时钟使能     
	GPIOB->CRL&=0XFFFFFF00;   //PORTB0 1复用输出
	GPIOB->CRL|=0X000000BB;   //PORTB0 1复用输出
	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	TIM3->CCMR2|=6<<12;//CH4 PWM1模式	
	TIM3->CCMR2|=6<<4; //CH3 PWM1模式	
	TIM3->CCMR2|=1<<11;//CH4预装载使能	 
	TIM3->CCMR2|=1<<3; //CH3预装载使能	  
	TIM3->CCER|=1<<12; //CH4输出使能	   
	TIM3->CCER|=1<<8;  //CH3输出使能	
	TIM3->CR1=0x8000;  //ARPE使能 
	TIM3->CR1|=0x01;   //使能定时器3 										  
} 


/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
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
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

