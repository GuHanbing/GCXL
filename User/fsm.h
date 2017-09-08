#ifndef __FSM_H
#define __FSM_H 
#include "stm32f10x.h"
#include "math.h"

typedef	enum
{
	  STAY,
		UP_RIGHT,
		UP_LEFT,
		UP,
		BACK,
		BACK_LEFT,
		BACK_RGHT,
    CHASE_BLACK,
}whe;




typedef struct
{
	enum                  
	{
		START=0,
		FIND_WAY,                    
    STEP1,
    STEP2,		
		STOP,
    BARRIER,		
	}pri;
  whe sec;
  enum
	{
		NEVER=0,
		EVER,
	}memory[6];
}sta;

void Data_precondition();
void Analysis(void);
/**********************************************ЦёБо******************************************/


typedef struct 
{
  whe wheel;
  double data1;
  double data2;
  double data3;
  enum
  {
    READ,
    UNREAD,
  }state;
}com;

void StateHandle();

void SendCommand(com temp);
int ReadCommand(com * temp);





#endif

