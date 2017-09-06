/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����ͷ����ov7725��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./ov7725/bsp_ov7725.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"  
#include "./systick/bsp_SysTick.h"
#include "./sys/sys.h"
#include "./MOTOR/motor.h"
#include "./ENCODER/encoder.h"
#include "./PID/pid.h"
#include "algorithm.h"
#include "control.h"
#include "./LIGHT/light.h"
#include "FSM.h"
extern int Obc;
extern uint8_t Ov7725_vsync;

unsigned int Task_Delay[NumOfTask]; 


extern OV7725_MODE_PARAM cam_mode;


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void) 	
{		
	
	float frame_count = 0;
	uint8_t retry = 0;
  
	/* Һ����ʼ�� */
	ILI9341_Init();
	ILI9341_GramScan ( 3 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	
	/********��ʾ�ַ���ʾ��*******/
  ILI9341_DispStringLine_EN(LINE(0),"BH OV7725 Test Demo");

	USART_Config();
	LED_GPIO_Config();
	Key_GPIO_Config();
	SysTick_Init();
	
	 MiniBalance_Motor_Init();
	 MiniBalance_PWM_Init(7199,7199);
	// Set_Pwm(6200,-6200);
	printf("\r\n ** OV7725����ͷʵʱҺ����ʾ����** \r\n"); 
	Light_Init();
	/* ov7725 gpio ��ʼ�� */
	OV7725_GPIO_Config();
	
	LED_BLUE;
	/* ov7725 �Ĵ���Ĭ�����ó�ʼ�� */
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
//		if(Obc==Obs)
//		{}
		if(retry>5)
		{
			printf("\r\nû�м�⵽OV7725����ͷ\r\n");
			ILI9341_DispStringLine_EN(LINE(2),"No OV7725 module detected!");
			while(1);
		}
	}


	/*��������ͷ����������ģʽ*/
	OV7725_Special_Effect(cam_mode.effect);
	/*����ģʽ*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*���Ͷ�*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*���ն�*/
	OV7725_Brightness(cam_mode.brightness);
	/*�Աȶ�*/
	OV7725_Contrast(cam_mode.contrast);
	/*����Ч��*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*����ͼ�������ģʽ��С*/
	OV7725_Window_Set(cam_mode.cam_sx,
														cam_mode.cam_sy,
														cam_mode.cam_width,
														cam_mode.cam_height,
														cam_mode.QVGA_VGA);

	/* ����Һ��ɨ��ģʽ */
	ILI9341_GramScan( cam_mode.lcd_scan );
	
	
	
	ILI9341_DispStringLine_EN(LINE(2),"OV7725 initialize success!");
	printf("\r\nOV7725����ͷ��ʼ�����\r\n");
	
	Ov7725_vsync = 0;
	
	while(1)
	{
		/*���յ���ͼ�������ʾ*/
		if( Ov7725_vsync == 2 )
		{
			frame_count++;
			FIFO_PREPARE;  			/*FIFO׼��*/					
			ImagDisp(cam_mode.lcd_sx,
								cam_mode.lcd_sy,
								cam_mode.cam_width,
								cam_mode.cam_height);			/*�ɼ�����ʾ*/
			
			Ov7725_vsync = 0;			
			LED1_TOGGLE;
      Analysis();
	
		}
		
	
//		/*ÿ��һ��ʱ�����һ��֡��*/
//		if(Task_Delay[0] == 0)  
//		{			
//			printf("\r\nframe_ate = %.2f fps\r\n",frame_count/10);
//			frame_count = 0;
//			Task_Delay[0] = 10000;
//		}
		
	}
}




/*********************************************END OF FILE**********************/

