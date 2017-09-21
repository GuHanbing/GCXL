#ifndef __ALGORITHM_H
#define __ALGORITHM_H 
#include "./ov7725/bsp_ov7725.h"
#include "stm32f10x.h"
#include "math.h"

#define CENTER 76



typedef struct
{
	char num;
	char st;
	char ed;
	char line;
}
Tuan;


typedef struct
{
	char num;
	char area;
	char left;
	char right;
	char top;
	char buttom;
	int center_x;
	int center_y;
}Block;
void FindWay(uint8_t img[][160],int black,int flag,int left,int right);
void Calc_Center_Error(void);














#endif

