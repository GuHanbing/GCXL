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
			case CHASE_BLACK: Calc_Motor(temp.data1,0.7);  break;
			case UP_RIGHT:  Turn(temp.data1);break;
			case STAY:   Turn(0);break;
		  case UP_LEFT:Turn(-1*temp.data1);break;
		  case UP:     Straight(1);break;
		  case BACK:   Straight(-1);break;
	    case BACK_LEFT:break;
	    case BACK_RGHT:break;
			default:break;
		}
		if(motorFlag)
		{
			if(temp.wheel==last)
			{
			motoL=0.3*motoL+0.7*LL;
			motoR=0.3*motoR+0.7*LR;
			}
	    Set_Pwm(motoL,motoR);
		  LL=motoL;
		  LR=motoR;
			last=temp.wheel;
		}
	//	Set_Pwm(7199,7199);
	}
  
}

void Straight(double speed)
{
	motoL=speed*MOTOR_MAX_PWM;
	motoR=speed*MOTOR_MAX_PWM;
}
void Turn(double dir)
{
	
	motoL=dir*MOTOR_MAX_PWM;
	motoR=-dir*MOTOR_MAX_PWM;

}

void Calc_Motor(double err,double chasu)
{
	double all;

	all=MOTOR_MAX_PWM-fabs(err)*0.6*MOTOR_MAX_PWM;
	motoL=(int)(all+err*chasu*MOTOR_MAX_PWM);
	motoR=(int)(all-err*chasu*MOTOR_MAX_PWM);
	if(err==1.1)
	{
				motoL=5000;
		motoR=-2000;
	}
	if(err==-1.1)
	{
		motoL=-2000;
		motoR=5000;
	}	
}

