#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"  	

//ccd 
#define row  70//ͼ������
#define line 100//ͼ������
#define standard line/2 //ͼ�����ĵ�

extern  int h,k;  //hΪʵ��������kΪ�ɼ���������
extern  unsigned char image[row][line];		//�ɼ�ԭʼͼ���ά����
extern  int left[row];             //��߽�����
extern  int right[row];            //�ұ߽�����
extern  int bottom[row];           //��������

void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 	

#endif
