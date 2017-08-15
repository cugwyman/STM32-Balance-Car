#include "ccd.h"  
#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h" 
  
u8  image[200][200]={0};
int x=0,y=0,z=0,w=0;
void CCD_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin =0x00ff;          //GPI0 0~7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3
	
}
//�ⲿ�ж�2�������           //���ж�
void EXTI2_IRQHandler(void)
{	
	if((z>=40)&&(z<400))
	{
	  for(w=0;w<110;w++);
	  for(w=400;w>0;w--)
    if(w%2==0)
       {image[x][y]=PFin(7);y++;}	      
		y=0;
		w=0;
		x++;
	}
	z++;
//	 LED0=!LED0;	
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������          //���ж�
void EXTI3_IRQHandler(void)
{
	 y=0;
	 x=0;
	 z=0;
   LED1=!LED1;	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

