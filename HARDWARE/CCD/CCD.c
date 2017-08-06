
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "sys.h" 
#include "delay.h"
#include "CCD.h"
#include "Rodeidentify.h"



//����ͷ��ʼ��
void CCD_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);  //��ֵ�����ݿ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOD 

 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	            //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	            //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	
}






