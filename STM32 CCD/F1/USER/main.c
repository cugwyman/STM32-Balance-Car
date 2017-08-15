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
*         STM32 Balance Car 平衡车
 *               2017.7.29
 *     CUG     Wyman    名字你们自己加
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
 *  1.外设均在HARDWARE文件夹,控制control.c暂时也放在此，参数、开关等h文件在DOCUMENT文件夹
 *  2.全局变量统一在其定义处的C文件自身的h文件处进行外部引用，
 *  3.6050暂时通过硬件I2C直接读取DMP
 *  4.引脚安排在README.txt
 *
 **********************************************/

// 	extern  unsigned char image[row][line];
extern u8 image[row][line];		//采集原始图像二维数组


int main(void)
 {	 
     	int i,j;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//  mode_init();
	delay_init();	//延时初始化 
	uart_init(115200);	 	//参考风力摆发送
//	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
//	LCD_Init();			   		//初始化LCD  ,用OLED,A2345
//	PWM_Init(4800-1,3-1);	    //PWM频率=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arr为占空比计算的分母
//  ENCODER_Init();
//	MPU_Init();					//初始化MPU6050
//  TIMER_Init(50-1,7200-1);      //5ms定时中断
//	CCD_init();//摄像头初始化
	EXTIX_Init();  //外部中断初始化
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


