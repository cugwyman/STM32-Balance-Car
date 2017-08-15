#include "EXTI.h"
#include "delay.h" 
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h" 
#include "road_identify.h"
#include "CCD.h"
#include "usart.h"
 int h,k;  //h为实际行数，k为采集数组行数
u8 image[row][line];		//采集原始图像二维数组
 int left[row];             //左边界数组
 int right[row];            //右边界数组
 int bottom[row];           //中线数组
 extern float error_sum;



//配置外部中断    摄像头 行场中断
void EXTIX_Init(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef	EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PB端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_7 ;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);					      //根据设定参数初始化GPIOD 
	
	EXTI_ClearITPendingBit(EXTI_Line2);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
	EXTI_ClearITPendingBit(EXTI_Line3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
  EXTI_InitStruct.EXTI_Line=EXTI_Line2 | EXTI_Line3;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//上升沿触发
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStruct);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);

}


//外部中断2服务程序          //行中断
void EXTI2_IRQHandler(void)
{	
	
	
		int x; 
//	printf("ok");
	  if((h>19)&&(k<row))
		{
			if(h%3==0)//采集图像数据
			{
				for(x=0;x<=95;x++);
				for(x=line-1;x>=0;x--)
                {
//				for(x=line-1;x>=0;x--)
		    image[k][x]=PFin(7);
//                    image[k][x]=(GPIOF->IDR&0X00ff);
//				printf("%x\n",image[k][x]);
//     						printf("%d\n",image[k][x]);
		
                }
//			if(h%5==1){
////			Searchborder(k);//搜边界  k++;
//			}				
                k++;
			} 
        }
    h++;
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序          //场中断
void EXTI3_IRQHandler(void)
{   
	k=0;
	h=0;

//	printf("ok");

//   void  ErrorGet();
   EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}











