#include "FSM.h"
#include "algorithm.h"
#include "./LIGHT/light.h"
#include "string.h"
extern uint8_t rIMG[120][160];
extern int valid;
extern int barrier,blackR,blackL,blackUL,blackUR;
extern double cErr;
sta State={START,CHASE_BLACK};
com Command;

void StateShift();
void StateHandle();
void FindBlock_R();
void FindBlock_W();
void Data_precondition()
{
	if(State.sec==STAY)
	{
		
	}
	else
	{
		if(State.sec==UP_RIGHT)
			FindWay(rIMG,5,0);
		else
	    FindWay(rIMG,5,1);
	Calc_Center_Error();
	}
	
	//FindBlock_W();
}
void Analysis()
{

	StateShift();
	StateHandle();
}

int Step_shift();
int Step_Left_Judge();
int Step_Right_Judge();
extern int motorFlag;
extern int bRightFlag;
int clrFlag=0;
void StateShift()
{
	static int  time2[5]={0,0,0,0,0};
	if(bRightFlag>0)
		bRightFlag--;
	switch(State.pri)
  {
	  case START:
		if(motorFlag)
		{
		State.pri=FIND_WAY;
		State.sec=CHASE_BLACK;
		}
		break;
		case FIND_WAY:

		  if( State.sec==CHASE_BLACK_C&&blackUL==EXIST&&blackUR==EXIST)
				State.sec=CHASE_BLACK;
			if(valid>30&&blackR==EXIST)
			{
				if(State.memory[BARRIER]==NEVER&&State.memory[STEP1]==NEVER&&State.memory[STEP2]==NEVER&&bRightFlag>0&&bRightFlag<510)//台阶1
				{
					State.memory[STEP1]=EVER;
				State.pri=STEP1;
				State.sec=UP;
				break;	
				}	
				if(State.memory[BARRIER]==EVER&&State.memory[STEP1]==EVER&&State.memory[STEP2]==NEVER&&bRightFlag>0&&bRightFlag<500)                 //台阶2
				{
					 clrFlag=1;
					State.memory[STEP2]=EVER;
				State.pri=STEP2;
				State.sec=UP;
				break;
				}						
			}
		if(barrier==EXIST&&State.memory[STEP1]==EVER&&State.memory[BARRIER]==NEVER&&valid<90)                        //障碍
		{
			State.memory[BARRIER]=EVER;
				State.pri=BARRIER;
				State.sec=UP_RIGHT;
		}
    break;	
		
    case STEP1:
		Step_shift();	
		break;
		case BARRIER:
		if(State.sec==UP_RIGHT)
		{
		 time2[0]++;
		if(time2[0]>110)
		State.sec=UP;
	}
		if(State.sec==UP)
		{
		 time2[1]++;
		if(time2[1]>160&&time2[1]<840-20)
		{
			if(blackUL==EXIST&&blackUR==EXIST)
				time2[1]=840-20;                     //向前延时让车头超出黑线再左转
		}
		if(time2[1]>840)
			State.sec=UP_LEFT;
	}
		if(State.sec==UP_LEFT)
		{
		 time2[2]++;
		if(time2[2]>60||1==Step_Left_Judge())
		{
		 State.pri=FIND_WAY;
		 State.sec=CHASE_BLACK_C;
		}
	}
		break;
    case STEP2:
    Step_shift();
   	break;
		case STOP:
			
		
		
    break;
		default:break;
	}
}

extern int collisionL,collisionR;
int Step_shift()
{
	static int time1[7]={0,0,0,0,0,0,0},pos=0;
	if( clrFlag==1)
	{
		clrFlag=0;
		memset(time1,0,sizeof(time1));
		pos=0;
		//time1[4]=50;
	}
		if(State.sec==UP&&pos==0)
			{
				time1[6]++;
						if(time1[6]>40)
		{
			State.sec=BACK;
			pos++;
		}
			}
		if(State.sec==BACK&&pos==1)
		{
			time1[4]++;
			if(blackR==EXIST)
			time1[4]=100;
		if(time1[4]>130)
		{
			State.sec=UP_RIGHT;
			pos++;
		}
		return 0;
	  }
		if(State.sec==UP_RIGHT&&pos==2)
			{
       time1[0]++;
				if(time1[0]>50)
				{
					if(1==Step_Right_Judge())
					{
						State.sec=UP;
			      pos++;
						return 0;
					}
				}
			if(time1[0]>960)
			{
				State.sec=UP;
			  pos++;
		  }				
			return 0;
		}
			if(State.sec==UP&&pos==3)
			{
			 time1[1]++;
		   if(time1[1]>360||(collisionL==EXIST&&collisionR==EXIST))
			 {
			  State.sec=STAY;
			  pos++;
		   }				 
			 return 0;
	   }
		if(State.sec==STAY&&pos==4)
		{
				time1[5]++;
			if(time1[5]>380)
			{
				State.sec=BACK;
				pos++;
			}
		return 0;
	  }
		if(State.sec==BACK&&pos==5)
		{
				time1[2]++;
			if(time1[2]>40)
			{
				State.sec=UP_LEFT;
				pos++;
				
			}
		return 0;
	  }
		if(State.sec==UP_LEFT&&pos==6)
		{
			time1[3]++;
			if(time1[3]>50)
				{
					if(1==Step_Left_Judge())
					{
			      State.pri=FIND_WAY;
			     State.sec=CHASE_BLACK_C;
						return 0;
					}
				}
			if(time1[3]>time1[0]+200)
			{
			State.pri=FIND_WAY;
			State.sec=CHASE_BLACK_C;
			}
			return 0;
		}
		
		
 return 0;
}

int Step_Right_Judge()
{
	static int flag=0;
	if(blackUL==NONE&&blackUR==NONE)
		flag=1;
	if(flag==1&&blackUL==NONE&&blackUR==EXIST)
	{
		flag=2;
		//return 1;
	}
	
	if(fabs(cErr)<0.10&&flag==2&&blackUL==EXIST&&blackUR==EXIST)
	
	{
		flag=0;
		return 1;
	}
	return 0;
}

int Step_Left_Judge()
{
	static int flag=0;
	if(blackUL==NONE&&blackUR==NONE)
		flag=1;
	if(flag==1&&blackUL==EXIST&&blackUR==NONE)
	{
		flag=2;
		//return 1;
	}
	
	if(fabs(cErr)<0.20&&flag==2&&blackUL==EXIST&&blackUR==EXIST)
	
	{
		flag=0;
		return 1;
	}
	return 0;
}


void StateHandle()
{
	com temp;
  whe last;
	double last_e=0;
	static int flag=0;
	switch(State.pri)
  {
	  case START:
		
		
		break;
		
		case FIND_WAY:
    
		
		temp.wheel=CHASE_BLACK;
		if(State.sec==CHASE_BLACK)
		{
		if(blackUL==NONE&&blackUR==EXIST)
		{
			temp.data1=1.1;
     //temp.data1=0.5;
		}
//		{temp.wheel=UP_RIGHT;}
		if(blackUL==EXIST&&blackUR==NONE)
		{
			temp.data1=-1.1;
     //temp.data1=-0.5;
		}
//		{temp.wheel=UP_LEFT;}
		if(blackUL==EXIST&&blackUR==EXIST)
			temp.data1=0;
		if((blackUL==NONE&&blackUR==NONE)||flag)
    {
			if(valid<25)
			{
			temp.wheel=UP_LEFT;
		temp.data1=0.8;
			}
			else
			{
				temp.data1=cErr*2;
				State.sec=CHASE_BLACK_C;
			}
		}		
		last=temp.wheel;
		if(temp.data1!=0)
		last_e=temp.data1;
	 }
		else
		{
			temp.data1=cErr*2;
		}
		SendCommand(temp);
    break;	
		
    case STEP1:
		
    temp.wheel=State.sec;	
		temp.data1=0.7;
		SendCommand(temp);
		
		break;
		case BARRIER:
			temp.wheel=State.sec;
     temp.data1=0.8;		
		SendCommand(temp);
		break;
    case STEP2:
			temp.wheel=State.sec;
		temp.data1=0.7;
		SendCommand(temp);


    break;
	
		case STOP:
			
		
    break;
		default:break;
	
	}
}




/**********************************************指令******************************************/


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
