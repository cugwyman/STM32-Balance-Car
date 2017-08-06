#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "encoder.h"
#include "timer.h"
#include "mode_switch.h"
#include "OLED.h"
#include "infrared.h"
#include "OscilloScope.h"
#include "key4x4.h"
#include "EXTI.h"
#include "road_identify.h"

/**********************************************
 *   
 *      STM32 Balance Car ƽ�⳵ V1.3
 *               2017.8.6
 *     CUG     Wyman    Sun    Chen
 *          
 *     IDE              Keil MDK V5.23
 *     MCU              STM32F103ZET6
 *     Attitude transducer     MPU6050
 *     Motor drivers    BTN
 *     Motor            DC motor     
 *
 **********************************************/
  	
 int main(void)
 {	 
    u8 OLED_cnt = 0;
    #ifdef SendPicture
    u8 send_row,send_line;
    #endif
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	//��ʱ��ʼ�� 
    mode_init();
	uart_init(115200);	 	
//	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
//    Init_Keyboard_Interrupt();
    Key_IO_Init();	 //����IO����
    OLED_Init();        
//    infrared_init();
//	PWM_Init(4800-1,3-1);	    //PWMƵ��=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arrΪռ�ձȼ���ķ�ĸ
//    ENCODER_Init();           //��B6789
    printf("MPUInit\n");
	MPU_Init();					//��ʼ��MPU6050
    printf("MPUsucceed\n");
	while(mpu_dmp_init())
        printf("DMPunsucceed\n");
	EXTIX_Init();  //�ⲿ�жϳ�ʼ��

    TIMER_Init(50-1,7200-1);      //5ms��ʱ�ж�
 	while(1)
	{
        OLED_cnt++;
        
        //send picture
        #ifdef SendPicture
        if(OLED_cnt % 10==0)
        {
            for(send_row=row-1;send_row>=0;send_row--)
            {
                for(send_line=0;send_line<=line-1;send_line++)
                {
                    USART_SendData(USART1,image[send_row][send_line]);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
                }
            }
            USART_SendData(USART1,0xff);
            while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);            
        }
        #endif
        //OLED display
        if(OLED_cnt % 60==0)
        {
            OLED_cnt = 0;
                    printf("%d,  %d,  %d\n", (int)pitch, gyroy, gyroz);

            switch(Param)
            {
                case 1:
                    OLED_ShowChar(120,2,'<',16);
                    OLED_ShowChar(120,4,' ',16);            
                    OLED_ShowChar(120,6,' ',16);
                    break;
                case 2:
                    OLED_ShowChar(120,2,' ',16);
                    OLED_ShowChar(120,4,'<',16);
                    OLED_ShowChar(120,6,' ',16);
                    break;
                case 3:    
                    OLED_ShowChar(120,2,' ',16);
                    OLED_ShowChar(120,4,' ',16);
                    OLED_ShowChar(120,6,'<',16);            
                    break;
                default:break;
            }
            switch(Item)
            {
                case 0:
                    OLED_ShowString(0,0,(u8 *)"CUG",16);
                    OLED_ShowString(0,2,(u8 *)"Wyman",16);
                    OLED_ShowString(0,4,(u8 *)"Sun",16);
                    OLED_ShowString(0,6,(u8 *)"Chen",16);        
                    break;
                case 1:
                    OLED_ShowString(0,0,(u8 *)"dirPID",16);
                    OLED_ShowString(0,2,(u8 *)"P",16);
                    OLED_ShowString(0,4,(u8 *)"I",16);
                    OLED_ShowString(0,6,(u8 *)"D",16);
                    OLED_ShowNum(68,2,MODE.DC_PID_P_COEF,2,16);
                    OLED_ShowNum(68,4,0,2,16);
                    OLED_ShowNum(68,6,MODE.DC_PID_D,2,16);
                    break;
                default:break;
            }
        }
//            OLED_ShowChar(52,4,'c',16);
//            OLED_ShowNum(68,4,key_value,2,16);
//        BlackLine();//��ʾ���ߵ����
//        OutPut_Data(pitch, gyroy, gyroz, pitch_zero);
//        printf("%d,  %d,  %d,  %d\n", ST188LL, ST188L, ST188M, ST188R);
        delay_ms(5);
	} 	
}
