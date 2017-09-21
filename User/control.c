#include "control.h"
#include "math.h"
#include "FSM.h"
#include "./key/bsp_key.h" 
extern double cErr;
int motoL,motoR;
void Turn(double dir);
void Straight(double speed);
int motorFlag=0;
void control()
{
	static int LL,LR;
	com temp;
	int valid=0;
	whe last;
	valid=ReadCommand(&temp);
	if(valid==1)
	{

		switch(temp.wheel)
		{
			case CHASE_BLACK: Calc_Motor(temp.data1,0.6);  break;
			case UP_RIGHT:  Turn(temp.data1);break;
			case STAY:   Turn(0);break;
		  case UP_LEFT:Turn(-1*temp.data1);break;
		  case UP:     Straight(0.8);break;
		  case BACK:   Straight(-0.7);break;
	    case BACK_LEFT:break;
	    case BACK_RGHT:break;
			default:break;
		}
		if(motorFlag)
		{
//			if(temp.wheel==last)
//			{
//			motoL=0.3*motoL+0.7*LL;
//			motoR=0.3*motoR+0.7*LR;
//			}
//		if(motoL<0)
//		 motoL=0;
//	  if(motoR<0)
//		 motoR=0;
	    Set_Pwm(motoL,motoR);
		  LL=motoL;
		  LR=motoR;
			last=temp.wheel;
		}
//	Set_Pwm(719,-719);
	}
  
}

void Straight(double speed)
{
	motoL=speed*MOTOR_MAX_PWM;
	motoR=speed*MOTOR_MAX_PWM;
}
void Turn(double dir)
{
	
//	motoL=0.7*MOTOR_MAX_PWM;
//	motoR=-0.6*MOTOR_MAX_PWM;
	
//		motoL=1.2*dir*MOTOR_MAX_PWM;
//	motoR=-1.2*dir*MOTOR_MAX_PWM;
	if(dir<0)
	{
		motoL=-600;
		motoR=600;
	}
else
{
			motoL=600;
		motoR=-600;
}
if(dir==0)
{
	motoL=0;
	motoR=0;
}
}

void Calc_Motor(double err,double chasu)
{
	double all;

	all=MOTOR_MAX_PWM-fabs(err)*0.2*MOTOR_MAX_PWM;
	motoL=(int)(all+err*chasu*MOTOR_MAX_PWM)+150;
	motoR=(int)(all-err*chasu*MOTOR_MAX_PWM)+150;
		if(motoL<0)
		 motoL*=0.8;
	  if(motoR<0)
		 motoR*=0.8;
//	if(err==0)
//	{
//				motoL=5000;
//		motoR=5000;
//	}
//	if(motoL<0)
//		motoL=0;
//	if(motoR<0)
//		motoR=0;
		if(err==0)
		{
		motoL=680;
		motoR=665;
		}
	if(err==1.1)
	{
		motoL=MOTOR_MAX_PWM;
		motoR=150;
	}
	if(err==-1.1)
	{
		motoL=150;
		motoR=MOTOR_MAX_PWM;
	}	
}

