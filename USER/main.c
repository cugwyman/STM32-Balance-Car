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
 *      STM32 Balance Car 平衡车 V1.2
 *               2017.7.30
 *     CUG     Wyman    名字你们自己加
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
 *  1.外设均在HARDWARE文件夹,控制control.c暂时也放在此，参数、开关等h文件在DOCUMENT文件夹
 *  2.全局变量统一在其定义处的C文件自身的h文件处进行外部引用，
 *  3.6050暂时通过硬件I2C直接读取DMP
 *  4.引脚安排在README.txt
 *
 *  2017.7.29   V1.1
 *  
 *  1.直立控制已加入，具体函数在control.c,实现在timer.c
 *
 *  2017.7.30   V1.2
 *  
 *  1.add OLED module
 *  2.add infrared module 红外循迹模块ST118
 *  3.connect ir and direction_PID  目前方向环根据红外循迹控制
 *
 **********************************************/

 	
 int main(void)
 {	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    mode_init();
	uart_init(115200);	 	//参考风力摆发送
	delay_init();	//延时初始化 
//	usmart_dev.init(72);		//初始化USMART
	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
    OLED_Init();        
    infrared_init();
	PWM_Init(4800-1,3-1);	    //PWM频率=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arr为占空比计算的分母
    ENCODER_Init();
	MPU_Init();					//初始化MPU6050
    TIMER_Init(50-1,7200-1);      //5ms定时中断
 	while(1)
	{
        BlackLine();//显示黑线的情况

	} 	
}

