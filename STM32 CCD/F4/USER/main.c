#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "ccd.h" 
#include "exti.h" 
#include "dma.h"

/*
 *  CUG Wyman Chen Sun
 *  STM32F4 SONY CCD
 *  max picture[80][110]
 */
 
u8 *SendBuff;

int main(void)
{ 
    
	u16 i,t;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(128000);	//串口初始化波特率为128000
	LED_Init();     	//初始化与LED连接的硬件接口  
    CCD_init();
    EXTIX_Init();  

	while(1)
	{
		for(i=0;i<80;i++)
 		  for(t=0;t<110;t++)          		
			{
				if( image[i][t]==0xff) image[i][t]=0xfe;
				USART_SendData(USART1, image[i][t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
			}
		
				USART_SendData(USART1, 0xff);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
	}
}


