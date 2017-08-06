#include "EXTI.h"
#include "delay.h" 
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h" 
#include "road_identify.h"
#include "usart.h"

int h,k;  //hΪʵ��������kΪ�ɼ���������
u8 image[row][line];		//�ɼ�ԭʼͼ���ά����
int left[row];             //��߽�����
int right[row];            //�ұ߽�����
int bottom[row];           //��������
extern float error_sum;

//�����ⲿ�ж�    ����ͷ �г��ж�
void EXTIX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef	EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	            //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	            //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
	
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_5 ;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOD 
	
	EXTI_ClearITPendingBit(EXTI_Line4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4);
	EXTI_ClearITPendingBit(EXTI_Line6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
    EXTI_InitStruct.EXTI_Line=EXTI_Line4 | EXTI_Line6;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//�����ش���
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);

}


//���ж�
void EXTI4_IRQHandler(void)
{	
    int x; 
//	printf("ok");
    if((h>19)&&(k<row))
    {
        if(h%3==0)//�ɼ�ͼ������
        {
            for(x=0;x<=95;x++);
            for(x=line-1;x>=0;x--)
            {
//				for(x=line-1;x>=0;x--)
                image[k][x]=PDin(5);
//                    image[k][x]=(GPIOF->IDR&0X00ff);
//				printf("%x\n",image[k][x]);
//     						printf("%d\n",image[k][x]);
            }
//			if(h%5==1){
////			Searchborder(k);//�ѱ߽�  k++;
//			}				
            k++;
		} 
    }
    h++;
	EXTI_ClearITPendingBit(EXTI_Line4);//���LINE2�ϵ��жϱ�־λ 
}

//���ж�
void EXTI9_5_IRQHandler(void)
{   
	k=0;
	h=0;
//   void  ErrorGet();
    EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE3�ϵ��жϱ�־λ  
}











