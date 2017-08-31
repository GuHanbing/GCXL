#ifndef __PID_H
#define __PID_H
#include "./sys/sys.h" 

extern float Target_voltage;//目标电压值
extern float KP;//比例放大系数
extern float KI;//积分时间
extern float KD;//微分时间

int Position_PID (float Encoder,float Target);//当前值，目标值
int Incremental_PID (float Encoder,float Target);//当前值，目标值
void Xianfu_Pwm(void);//限幅

#endif
