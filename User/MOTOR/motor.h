#ifndef __MOTOR_H
#define __MOTOR_H
	 
#include "./sys/sys.h" 
#define PWMA   TIM3->CCR4
#define AIN2   PAout(7)
#define AIN1   PAout(6)
#define BIN1   PAout(4)
#define BIN2   PAout(5)
#define PWMB   TIM3->CCR3
#define MOTOR_MAX_PWM 719
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
void Set_Pwm(int moto1,int moto2);
int myabs(int a);
#endif
