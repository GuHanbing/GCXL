#include "./PID/pid.h"

float Target_voltage=1.0;
float KP=5,KI=0,KD=0;


/************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (float Encoder,float Target)        //PID
{ 	
	 float KP=300,KI=12,KD=0;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=KP*Bias+KI*Integral_bias+KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}

/**************************************************************************
函数功能：增量PID控制器
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PID (float Encoder,float Target)
{ 		
	 static float Bias,Pwm,Last_bias,Last2_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=KP*(Bias-Last_bias)+KI*Bias+KD*(Bias-2*Last_bias+Last2_bias);   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差
   Last2_bias=Last_bias;
	 return Pwm;                         //增量输出
}

