#include "algorithm.h"
#include "string.h"
extern uint8_t rIMG[120][160];
extern uint8_t gIMG[120][160];
extern uint8_t bIMG[120][160];
int Center[120];
int bLeftFlag=0;
int bRightFlag=0;
double cErr=0;


int Max(int a,int b)
{
if(a>b)
	return a;
else
	return b;
}

int Min(int a,int b)
{
if(a<b)
	return a;
else
	return b;
}

void FindWay(uint8_t img[][160],int black)
{
	int col,row,stRow;
	int stFlag=0,bFlag=0;
	int bSt,bEd;
	int width[120]={0};
	int bLeft=0,bRight=0;
	memset(Center,0,sizeof(Center));
	for(row=119;row>=100;row--)
	{
		for(col=0;col<=158;col++)
		{
			if(img[row][col]<black)
			{
				if(bFlag==0)
				{
				bSt=col;
				bFlag=1;
				}
				if(bFlag==1)
				{
					width[row]++;
				}
			}
			else
			{
				if(bFlag==1)
				{
					if(width[row]>=5&&width[row]<25)
					{
						bEd=col;
					Center[row]=(bSt+bEd)/2;
					stFlag=1;
						stRow=row;
						break;
					}

						bFlag=0;

				}
			}
			
		}
		if(stFlag==1)
		{
			break;
		}
	}
	bFlag=0;
	if(stFlag==1)
	{
		for(row=stRow-1;row>=10;row--)
		{
			bFlag=0;
			for(col=Max(Center[row+1]-15,1);col<=Min(Center[row+1]+15,158);col++)
			{
				if(bFlag==0&&img[row][col]<black)
			  {
				 bSt=col;
				 bFlag=1;
					continue;
			  }
			  if(bFlag==1)
				{
					if(img[row][col]<black)
				 {
					width[row]++;
				 }
				 else
				 {
					if(width[row]>=3&&width[row]<25)
					{
					 bEd=col;
					 Center[row]=(bSt+bEd)/2;
					if(Center[row+1]-width[row+1]/2-bSt>=10)
					{
						bLeft++;
						Center[row]=Center[row+1];
						width[row]=width[row+1];
					  
				  }    
					if(bEd-(Center[row+1]+width[row+1]/2)>=10)
					{
						bRight++;
						Center[row]=Center[row+1];
						width[row]=width[row+1];
					  
				  } 
					 bFlag=0;
           break;
				 }
		  	}  
		
		 }
			
	 }
		
 }
	}
//	if(bLeft>=5)
//		bLeftFlag=1;
//	else
//		bLeftFlag=0;
	if(bRight>=5)
		bRightFlag=1;
	else
		bRightFlag=0;	
}

int valid=0;
void Calc_Center_Error()
{
	static double last_err=0;
	int i=0;
	double sum=0;
	valid=0;
	for(i=80;i<120;i++)
	{
		if(Center[i]!=0)
		{
			sum+=(double)(Center[i]-90)/18.0;
			valid++;
		}
	}
	if(valid>20)
	{
	  cErr=sum/i;
		cErr*=40.0/valid;
		last_err=cErr;
	}
	else
	{
		if(last_err<-0.1)
			cErr=-1.5;
				if(last_err>0.1)
			cErr=1.5;
	}
//	if(fabs(cErr)<0.3)
//		cErr*=0.4;
	if(cErr<-1)
		cErr=-1;
	if(cErr>1)
		cErr=1;	
	WayShow(Center,160,120);
}


