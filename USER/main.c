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
 *      STM32 Balance Car 平衡车 V1.3
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
    u8 send_BUF = 0;
    u8 send_label = 0;
    
    Temp[0] = 0x55;
    Temp[1] = 255;
    Temp[2] = 0;
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();	//延时初始化 
    mode_init();
	uart_init(9600);	 	
//	LED_Init();		  			//初始化与LED连接的硬件接口
    Key_IO_Init();	 //按键IO配置
    OLED_Init();        
//    infrared_init();
//	PWM_Init(4800-1,3-1);	    //PWM频率=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arr为占空比计算的分母
//    ENCODER_Init();           //改B6789
//    printf("MPUInit\n");
//	MPU_Init();					//初始化MPU6050
//    printf("MPUsucceed\n");
//	while(mpu_dmp_init())
//        printf("DMPunsucceed\n");
//	EXTIX_Init();  //外部中断初始化

    TIMER_Init(50-1,7200-1);      //5ms定时中断
 	while(1)
	{
////        		USART_SendData(USART1, send_BUF);//发送函数(串口1)
////                delay_ms(500);
//        OLED_cnt++;

//        //send picture
//        #ifdef SendPicture
//        if(OLED_cnt % 10==0)
//        {
//            for(send_row=row-1;send_row>=0;send_row--)
//            {
//                for(send_line=0;send_line<=line-1;send_line++)
//                {
//                    USART_SendData(USART1,image[send_row][send_line]);
//                    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//                }
//            }
//            USART_SendData(USART1,0xff);
//            while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);            
//        }
//        #endif
//        //OLED display
//        if(OLED_cnt % 20==0)
//        {
//            OLED_cnt = 0;
////                    printf("%d,  %d,  %d\n", (int)pitch, gyroy, gyroz);
////                    printf("test\n");

//            switch(Param)
//            {
//                case 1:
//                    OLED_ShowChar(120,2,'<',16);
//                    OLED_ShowChar(120,4,' ',16);            
//                    OLED_ShowChar(120,6,' ',16);
//                    break;
//                case 2:
//                    OLED_ShowChar(120,2,' ',16);
//                    OLED_ShowChar(120,4,'<',16);
//                    OLED_ShowChar(120,6,' ',16);
//                    break;
//                case 3:    
//                    OLED_ShowChar(120,2,' ',16);
//                    OLED_ShowChar(120,4,' ',16);
//                    OLED_ShowChar(120,6,'<',16);            
//                    break;
//                default:break;
//            }
//            switch(Item)
//            {
//                case 0:
////                    printf("%d\n", USART_RX_BUF[]);
////                    OLED_Clear();
////                    for(BUF = 0;BUF < sizeof(USART_RX_BUF); BUF ++)
////                    if(BUF == 0)
////                        OLED_ShowNum(0,0,123,4,16);
////                    else if(BUF == 0xff)
////                        OLED_ShowNum(0,0,456,4,16);
////                    else
////                        OLED_ShowNum(0,0,789,4,16);
//                    if(sign) 
//                    {
//                        OLED_ShowString(0,0,(u8 *)"            ",16);
//                        OLED_ShowNum(0,0,x_label,4,16);
//                        OLED_ShowNum(60,0,y_label,4,16);
//                        sign = 0;
//                    }
////                        OLED_ShowString(BUF*16,0,(u8 *)BUF,16);
//                    OLED_ShowString(0,2,(u8 *)"Wyman",16);
//                    OLED_ShowString(0,4,(u8 *)"Sun",16);
//                    OLED_ShowString(0,6,(u8 *)"Chen",16);        
//                    break;
//                case 1:
//                    OLED_ShowString(0,0,(u8 *)"dirPID",16);
//                    OLED_ShowString(0,2,(u8 *)"P",16);
//                    OLED_ShowString(0,4,(u8 *)"I",16);
//                    OLED_ShowString(0,6,(u8 *)"D",16);
//                    OLED_ShowNum(68,2,MODE.DC_PID_P_COEF,2,16);
//                    OLED_ShowNum(68,4,0,2,16);
//                    OLED_ShowNum(68,6,MODE.DC_PID_D,2,16);
//                    break;
//                default:break;
//            }
//        }
////            OLED_ShowChar(52,4,'c',16);
////            OLED_ShowNum(68,4,key_value,2,16);
////        BlackLine();//显示黑线的情况
////        OutPut_Data(pitch, gyroy, gyroz, pitch_zero);
////        printf("%d,  %d,  %d,  %d\n", ST188LL, ST188L, ST188M, ST188R);
//        delay_ms(5);

/*发送部分*/
        if(Temp[1]>0)
            Temp[1]--;
        else
            Temp[1]=255;
        if(Temp[2]<255)
            Temp[2]++;
        else
            Temp[2]=0;
            
        for(send_BUF = 0; send_BUF < 3; send_BUF++)
        {
            USART_SendData(USART1, Temp[send_BUF]);
            delay_ms(50);
        }       

	} 	
}

