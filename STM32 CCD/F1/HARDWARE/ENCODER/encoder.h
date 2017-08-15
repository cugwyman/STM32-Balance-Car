#ifndef __ENCODER_H
#define __ENCODER_H
#include "stm32f10x.h"
void TIM2_Configuration(void);
void TIM2_Encoder_Write(int data);
int TIM2_Encoder_Read(void);


void TIM4_Configuration(void);
void TIM4_Encoder_Write(int data);
int TIM4_Encoder_Read(void);

void ENCODER_Init(void);

#endif
