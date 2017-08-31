#include "./PID/pid.h"

float Target_voltage=1.0;
float KP=5,KI=0,KD=0;


/************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (float Encoder,float Target)        //PID
{ 	
	 float KP=300,KI=12,KD=0;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=KP*Bias+KI*Integral_bias+KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}

/**************************************************************************
�������ܣ�����PID������
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PID (float Encoder,float Target)
{ 		
	 static float Bias,Pwm,Last_bias,Last2_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=KP*(Bias-Last_bias)+KI*Bias+KD*(Bias-2*Last_bias+Last2_bias);   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ��
   Last2_bias=Last_bias;
	 return Pwm;                         //�������
}

