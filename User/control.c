#include "control.h"
#include "math.h"
extern double cErr;

void control()
{
  Calc_Motor(cErr,0.8);
}

void Calc_Motor(double err,double chasu)
{
	double all;
	int motoL,motoR;
	all=MOTOR_MAX_PWM-fabs(err)*0.5*MOTOR_MAX_PWM;
	motoL=(int)(all+err*chasu*MOTOR_MAX_PWM);
	motoR=(int)(all-err*chasu*MOTOR_MAX_PWM);
	Set_Pwm(motoL,motoR);

}
void ReadCommand()
{


}
