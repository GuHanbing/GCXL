#include "FSM.h"
#include "algorithm.h"
#include "./LIGHT/light.h"

extern uint8_t rIMG[120][160];
extern int valid;
extern int barrier,blackR,blackL;
sta State={FIND_WAY,CHASE_BLACK};
com Command;

void StateShift();
void StateHandle();

void Analysis()
{
	if(State.sec==STAY)
	{
		
	}
	else
	{
	FindWay(rIMG,8);
	
	Calc_Center_Error();
	}
	StateShift();
	StateHandle();
}

void StateShift()
{
	static int time1[5]={0},time2[5]={0},time3[5]={0};
	switch(State.pri)
  {
	  case START:
		
		
		
		
		break;
		case FIND_WAY:

			if(valid>30&&blackR==EXIST)
			{
				if(State.memory[BARRIER]==NEVER&&State.memory[STEP1]==NEVER&&State.memory[STEP2]==NEVER)//Ì¨½×1
				{
					State.memory[STEP1]=EVER;
				State.pri=STEP1;
				State.sec=UP_RIGHT;
				break;	
				}	
				if(State.memory[BARRIER]==EVER&&State.memory[STEP1]==EVER&&State.memory[STEP2]==NEVER)                 //Ì¨½×2
				{
					State.memory[STEP2]=EVER;
				State.pri=STEP2;
				State.sec=UP_RIGHT;
				break;
				}						
			}
		if(barrier==EXIST&&State.memory[STEP1]==EVER&&State.memory[BARRIER]==NEVER&&valid<30)                        //ÕÏ°­
		{
			State.memory[BARRIER]=EVER;
				State.pri=BARRIER;
				State.sec=UP_RIGHT;
		}
    break;	
		
    case STEP1:
			if(State.sec==UP_RIGHT)
			{
       time1[0]++;
			if(time1[0]>10)
				State.sec=UP;
		}
			if(State.sec==UP)
			{
				time1[1]++;
		if(time1[1]>6)
			State.sec=BACK;
	   }
		if(State.sec==BACK)
		{
				time1[2]++;
		if(time1[2]>4)
			State.sec=UP_LEFT;
	  }
		if(State.sec==UP_LEFT)
		{
			time1[3]++;
			if(time1[3]>5)
			State.pri=FIND_WAY;
		}
		break;
		
		case BARRIER:
		if(State.sec==UP_RIGHT)
		{
		 time2[0]++;
		if(time2[0]>10)
		State.sec=UP;
	}
		if(State.sec==UP)
		{
		 time2[1]++;
		if(time2[1]>12)
			State.sec=UP_LEFT;
	}
		if(State.sec==UP_LEFT)
		{
		 time2[2]++;
		if(time2[1]>5)
		 State.pri=FIND_WAY;
	}
		break;
    case STEP2:
    			if(State.sec==UP_RIGHT)
			{
       time1[0]++;
			if(time1[0]>10)
				State.sec=UP;
		}
			if(State.sec==UP)
			{
				time1[1]++;
		if(time1[1]>6)
			State.sec=BACK;
	   }
		if(State.sec==BACK)
		{
				time1[2]++;
		if(time1[2]>4)
			State.sec=UP_LEFT;
	  }
		if(State.sec==UP_LEFT)
		{
			time1[3]++;
			if(time1[3]>5)
			State.pri=FIND_WAY;
		}

    break;
   	
		case STOP:
			
		
		
    break;
		default:break;
	}
}


void StateHandle()
{
	com temp;

	switch(State.pri)
  {
	  case START:
		
		
		
		break;
		
		case FIND_WAY:
    
		temp.wheel=CHASE_BLACK;
		SendCommand(temp);
    break;	
		
    case STEP1:
		
    temp.wheel=State.sec;	
		SendCommand(temp);
		
		break;
		case BARRIER:
			temp.wheel=State.sec;	
		SendCommand(temp);
		break;
    case STEP2:
			temp.wheel=State.sec;	
		SendCommand(temp);


    break;
	
		case STOP:
			
		
    break;
		default:break;
	
	}
}




/**********************************************Ö¸Áî******************************************/


void SendCommand(com temp)
{
  Command.state=UNREAD;
  Command.wheel=temp.wheel;
  Command.data1=temp.data1;
  Command.data2=temp.data2;
  Command.data3=temp.data3;
}

int ReadCommand(com * temp)
{
  if(Command.state==UNREAD)
  {
    Command.state=READ;
    temp->wheel=Command.wheel;
    temp->data1=Command.data1;
    temp->data2=Command.data2;
    temp->data3=Command.data3;
    return 1;                      
  }
  else
    return 0;                     
}
