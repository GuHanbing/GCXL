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
	com temp;
	int valid=0;
	valid=ReadCommand(&temp);
	if(valid==1)
	{
		switch(temp.wheel)
		{
			case CHASE_BLACK: Calc_Motor(cErr,0.8);  break;
			case UP_RIGHT:  Turn(1);break;
			case 	  STAY:   Turn(0);break;
		  case UP_LEFT:   Turn(-1);break;
		  case UP:        Straight(1);break;
		  case BACK:      Straight(-1);break;
	    case 	BACK_LEFT:break;
	    case 	BACK_RGHT:break;

			default:break;
		}

		if(motorFlag)
		 Set_Pwm(motoL,motoR);
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

	all=MOTOR_MAX_PWM-fabs(err)*0.5*MOTOR_MAX_PWM;
	motoL=(int)(all+err*chasu*MOTOR_MAX_PWM);
	motoR=(int)(all-err*chasu*MOTOR_MAX_PWM);
	

}

