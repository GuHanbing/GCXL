#include "algorithm.h"
#include "string.h"
#include "./lcd/bsp_ili9341_lcd.h"
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
	for(row=110;row>=100;row--)
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
					if(width[row]>=15&&row>80)
				{
					bEd=col;
				 if(Center[row+1]-width[row+1]/2-bSt>=6&&bEd-(Center[row+1]+width[row+1]/2)<=6)
				{
					bLeft++;
					Center[row]=Center[row+1];
					width[row]=width[row+1];
					
				}    
				 if(bEd-(Center[row+1]+width[row+1]/2)>=6&&Center[row+1]-width[row+1]/2-bSt<=6)
				{
					bRight++;
					Center[row]=Center[row+1];
					width[row]=width[row+1];
					
				} 
									 bFlag=0;
           break;
				}
				 }
				 else
				 {

					if(width[row]>=3&&width[row]<15)
					{
					 bEd=col;
					 Center[row]=(bSt+bEd)/2;


				 }

					 bFlag=0;
           break;
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
		bRightFlag=150;

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
			sum+=(double)(Center[i]-95)/18.0;
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
	//WayShow(Center,160,120);
}

int Red(int line,int col)
{
	 if(rIMG[line][col]>gIMG[line][col]/2+bIMG[line][col]-7&&rIMG[line][col]>8)
		 return 1;
	 else
		 return 0;
}


//É«¿éÊ¶±ð
int CreateTuan(Tuan (*tuan)[5],int No,int Line,int St,int Ed,int Max);
int CreateBlock(Tuan (*tuan)[5],Block * block);

Tuan rTuan[120][5];
Block rBlock[30];
void FindBlock_R()
{
	int line,col;
	int st,ed,Bwidth=0,No=0;
	int flag=0;
	int Max=0;
	memset(rTuan,0,sizeof(Tuan)*1200);
	memset(rBlock,0,sizeof(Block)*10);
	for(line=0;line<=119;line++)
	{
		flag=0;
		No=0;
		for(col=0;col<=159;col++)
		{
		if(flag==0)
		 {
			if(Red(line,col))
			{
				flag=1;
				Bwidth=0;
				st=col;
			}
		 }
		 if(flag==1)
		 {
			 if(Red(line,col))
			{
				ed=col;
			}
			else
			{
				Bwidth++;
				if(Bwidth>=8)
				{
					flag=0;
					if(ed-st+1>=14)
					{
						 CreateTuan(rTuan,No,line,st,ed,Max);
											if(rTuan[line][No].num>Max)
            Max=rTuan[line][No].num;     						
					No++;
					if(No>4)
						break;
					}


				}
			}
		 }
		}
	}
 int valid=CreateBlock(rTuan,rBlock);   
}


void ChangNo(Tuan (*tuan)[5],int Line,int origin,int change)
{
	int i,j;
	for(i=0;i<=Line-1;i++)
	{
		while(tuan[i][j].num!=0&&j<=4)
		{
			if(tuan[i][j].num==origin)
				tuan[i][j].num=change;
		}
	}
}

int CreateTuan(Tuan (*tuan)[5],int No,int Line,int St,int Ed,int Max)
{
	int link_nums=0,link_No[10];
	int line=Line-1,i=0;
	tuan[Line][No].st=St;
	tuan[Line][No].ed=Ed;
	tuan[Line][No].line=Line;
	if(Line==0)
	{
		tuan[Line][No].num=Max+1;
		return 0;
	}
	while(tuan[line][i].num!=0&&i<=4)
	{
		if((tuan[line][i].st>=St&&tuan[line][i].st<=Ed)||(tuan[line][i].ed>=St&&tuan[line][i].ed<=Ed))
		{
			link_No[link_nums]=tuan[line][i].num;
			link_nums++;
		}
		i++;
	}
	if(link_nums==0)
	{
		tuan[Line][No].num=Max+1;
		return 0;
	}
	if(link_nums==1)
	{
		tuan[Line][No].num=link_No[0];
	}
	else
	{
		tuan[Line][No].num=link_No[0];
		for(i=1;i<link_nums;i++)
		{
			ChangNo(tuan,Line,link_No[i],link_No[0]);
		}
	}
	return 0;
}

int CreateBlock(Tuan (*tuan)[5],Block * block)
{
	int i,j=0,k,valid=0;
	for(i=0;i<=119;i++)
	{
		j=0;
		while(tuan[i][j].num!=0&&j<=4)
		{
			k=tuan[i][j].num;
			block[k].area+=tuan[i][j].ed-tuan[i][j].st+1;
			if(block[k].top==0)
			{
				block[k].top=i;
				block[k].buttom=i;
				block[k].left=tuan[i][j].st;
				block[k].right=tuan[i][j].ed;
			}
			if(i>block[k].buttom)
				block[k].buttom=i;
			if(tuan[i][j].st<block[k].left)
				block[k].left=tuan[i][j].st;
			if(tuan[i][j].ed>block[k].right)
				block[k].right=tuan[i][j].ed;
			j++;
		}
	}
	for(k=0;k<=10;k++)
	{
		if(block[k].top!=0&&block[k].area>70)
		{
			valid++;
			block[k].center_x=(block[k].left+block[k].right)/2-CENTER;
			block[k].center_y=119-(block[k].top+block[k].buttom)/2;
			ILI9341_DrawCircle (block[k].center_x+CENTER,119-block[k].center_y,10,1);
		}
	}
	return valid;
}