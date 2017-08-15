#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "mpu6050.h"
//#include "usmart.h"   
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "encoder.h"
#include "timer.h"
#include "mode_switch.h"
#include "CCD.h"
#include "EXTI.h"
#include "road_identify.h"
#include "datatranslate.h"
 extern int ph;
/************************************************
*   
*         STM32 Balance Car ƽ�⳵
 *               2017.7.29
 *     CUG     Wyman    ���������Լ���
 *          
 *     IDE              Keil MDK V5.23
 *     MCU              STM32F103ZET6
 *     Attitude transducer     MPU6050
 *     Motor drivers    BTN
 *     Motor            DC motor
 *     
 *     To be added      CCD, infrared ,OLED, Keyboard...
 *
 **********************************************/
 
/**********************************************
 *
 *  2017.7.29   V1.0
 *  
 *  1.�������HARDWARE�ļ���,����control.c��ʱҲ���ڴˣ����������ص�h�ļ���DOCUMENT�ļ���
 *  2.ȫ�ֱ���ͳһ���䶨�崦��C�ļ������h�ļ��������ⲿ���ã�
 *  3.6050��ʱͨ��Ӳ��I2Cֱ�Ӷ�ȡDMP
 *  4.���Ű�����README.txt
 *
 **********************************************/

// 	extern  unsigned char image[row][line];
extern u8 image[row][line];		//�ɼ�ԭʼͼ���ά����


int main(void)
 {	 
     	int i,j;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//  mode_init();
	delay_init();	//��ʱ��ʼ�� 
	uart_init(115200);	 	//�ο������ڷ���
//	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
//	LCD_Init();			   		//��ʼ��LCD  ,��OLED,A2345
//	PWM_Init(4800-1,3-1);	    //PWMƵ��=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arrΪռ�ձȼ���ķ�ĸ
//  ENCODER_Init();
//	MPU_Init();					//��ʼ��MPU6050
//  TIMER_Init(50-1,7200-1);      //5ms��ʱ�ж�
//	CCD_init();//����ͷ��ʼ��
	EXTIX_Init();  //�ⲿ�жϳ�ʼ��
 	while(1)
	{
//   Uart_PrintfPhoto();
//   delay_ms(50);
//// Uart_PrintfPhoto1();
	
		for(i=row-1;i>=0;i--)
		{
			for(j=0;j<=line-1;j++)
			{
//				if(j==edge_L[i]||j==edge_R[i]||j==ZX[i])
//					USART_SendData(USART1,(!picture[i][j])<<7);
//				else
				USART_SendData(USART1,image[i][j]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}
		}
		USART_SendData(USART1,0xff);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
} 	


