
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "sys.h" 
#include "delay.h"
#include "CCD.h"
#include "Rodeidentify.h"



//摄像头初始化
void CCD_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);  //二值化数据口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PB端口时钟

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);					      //根据设定参数初始化GPIOD 

 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	
}






