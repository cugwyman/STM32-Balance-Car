#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "mpu6050.h"
#include "usmart.h"   
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "encoder.h"
#include "timer.h"
#include "mode_switch.h"
#include "OLED.h"
#include "infrared.h"

/**********************************************
 *   
 *      STM32 Balance Car ƽ�⳵ V1.2
 *               2017.7.30
 *     CUG     Wyman    ���������Լ���
 *          
 *     IDE              Keil MDK V5.23
 *     MCU              STM32F103ZET6
 *     Attitude transducer     MPU6050
 *     Motor drivers    BTN
 *     Motor            DC motor
 *     
 *     To be added      CCD, Keyboard...
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
 *  2017.7.29   V1.1
 *  
 *  1.ֱ�������Ѽ��룬���庯����control.c,ʵ����timer.c
 *
 *  2017.7.30   V1.2
 *  
 *  1.add OLED module
 *  2.add infrared module ����ѭ��ģ��ST118
 *  3.connect ir and direction_PID  Ŀǰ���򻷸��ݺ���ѭ������
 *
 **********************************************/

 	
 int main(void)
 {	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    mode_init();
	uart_init(115200);	 	//�ο������ڷ���
	delay_init();	//��ʱ��ʼ�� 
//	usmart_dev.init(72);		//��ʼ��USMART
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
    OLED_Init();        
    infrared_init();
	PWM_Init(4800-1,3-1);	    //PWMƵ��=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arrΪռ�ձȼ���ķ�ĸ
    ENCODER_Init();
	MPU_Init();					//��ʼ��MPU6050
    TIMER_Init(50-1,7200-1);      //5ms��ʱ�ж�
 	while(1)
	{
        BlackLine();//��ʾ���ߵ����

	} 	
}

