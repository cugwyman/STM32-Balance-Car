#include "encoder.h"

/***********************************************************
      �������ӿ�ģʽ �� �ٶȼ���뷽����TIM2/4���ڱ���ģʽ
      PA0(TIM2_CH1)�ӣ�PA1(TIM2_CH2)��
	  PB6(TIM4_CH1)�ӣ�PB7(TIM4_CH2)��
***********************************************************/
//****************TIM2���ڱ���ģʽ**************
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ����APB1���Ƶ�TIM2�˿�ʱ��
	TIM_DeInit(TIM2); 	//TIM2��ʼ��
	
	//GPIO����PA0,PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʹ��PA�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //PA0��PA2 ��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM2����ģʽ
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
   	
  	/* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0; 	  			//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   			//���ü��������������س�ֵ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 		//�����ϲ�����ʼ����ʱ��ʱ�����ģ��		

	TIM_Cmd(TIM2, ENABLE); 	//ʹ�ܶ�ʱ��2
}

//***************TIM2�����Ĵ�����ֵ**************
void TIM2_Encoder_Write(int data)
{
    TIM2->CNT = data;
}

//*************������TIM2����**************
int TIM2_Encoder_Read(void)
{ 
	s16 data;
	data=(s16)(TIM_GetCounter(TIM2));
	return (int)data;
}

//***********������TIM4����**************
int TIM4_Encoder_Read(void)
{
	s16 data;
	data=(s16)(TIM_GetCounter(TIM4));
	return (int)data;
}

//***************TIM4�����Ĵ�����ֵ***********
void TIM4_Encoder_Write(int data)
  {
    TIM4->CNT = data;
  }

//*****************TIM4���ڱ���ģʽ************* 
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ����APB1���Ƶ�TIM4�˿�ʱ��
	TIM_DeInit(TIM4); 	//TIM4��ʼ��
	
	//GPIO����PB6,PB7
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʹ��PB�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //PB6,PB7 ��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//TIM4����ģʽ
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
   	
  	/* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0; 	  			//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   			//���ü��������������س�ֵ65535.���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 		//�����ϲ�����ʼ����ʱ��ʱ�����ģ��		

	TIM_Cmd(TIM4, ENABLE); 	//ʹ�ܶ�ʱ��4
}


void ENCODER_Init(void)
{
    TIM2_Configuration();
    TIM4_Configuration();
}


