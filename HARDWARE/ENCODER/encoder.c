#include "encoder.h"

/***********************************************************
      编码器接口模式 ， 速度检测与方向检测TIM2/4用于编码模式
      PA0(TIM2_CH1)接；PA1(TIM2_CH2)接
	  PB6(TIM4_CH1)接；PB7(TIM4_CH2)接
***********************************************************/
//****************TIM2用于编码模式**************
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能由APB1控制的TIM2端口时钟
	TIM_DeInit(TIM2); 	//TIM2初始化
	
	//GPIO配置PA0,PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //使能PA端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //PA0、PA2 浮空输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM2编码模式
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
   	
  	/* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0; 	  			//不分频
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   			//设置计数器溢出后的重载初值
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 		//用以上参数初始化定时器时间基础模块		

	TIM_Cmd(TIM2, ENABLE); 	//使能定时器2
}

//***************TIM2计数寄存器赋值**************
void TIM2_Encoder_Write(int data)
{
    TIM2->CNT = data;
}

//*************读计数TIM2个数**************
int TIM2_Encoder_Read(void)
{ 
	s16 data;
	data=(s16)(TIM_GetCounter(TIM2));
	return (int)data;
}

//***********读计数TIM4个数**************
int TIM4_Encoder_Read(void)
{
	s16 data;
	data=(s16)(TIM_GetCounter(TIM4));
	return (int)data;
}

//***************TIM4计数寄存器赋值***********
void TIM4_Encoder_Write(int data)
  {
    TIM4->CNT = data;
  }

//*****************TIM4用于编码模式************* 
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能由APB1控制的TIM4端口时钟
	TIM_DeInit(TIM4); 	//TIM4初始化
	
	//GPIO配置PB6,PB7
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //使能PB端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //PB6,PB7 浮空输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM4编码模式
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
   	
  	/* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0; 	  			//不分频
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   			//设置计数器溢出后的重载初值65535.不可大于65535 因为F103的定时器是16位的。
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 		//用以上参数初始化定时器时间基础模块		

	TIM_Cmd(TIM4, ENABLE); 	//使能定时器4
}


void ENCODER_Init(void)
{
    TIM2_Configuration();
    TIM4_Configuration();
}


