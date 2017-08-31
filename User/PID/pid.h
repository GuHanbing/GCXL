#ifndef __PID_H
#define __PID_H
#include "./sys/sys.h" 

extern float Target_voltage;//Ŀ���ѹֵ
extern float KP;//�����Ŵ�ϵ��
extern float KI;//����ʱ��
extern float KD;//΢��ʱ��

int Position_PID (float Encoder,float Target);//��ǰֵ��Ŀ��ֵ
int Incremental_PID (float Encoder,float Target);//��ǰֵ��Ŀ��ֵ
void Xianfu_Pwm(void);//�޷�

#endif
