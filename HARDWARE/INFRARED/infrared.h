#ifndef __INFRARED_H
#define __INFRARED_H
#include "stm32f10x.h"

//定义st188传感器引脚
#define ST188LL GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define ST188L GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)
#define ST188M GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#define ST188R GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define ST188RR GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)


#define ST188DATA (ST188LL<<4)+(ST188L<<3)+(ST188M<<2)+(ST188R<<1)+ST188RR//有黑线是1

void infrared_init(void);
s16 get_ir_dir_error(u8 state);
void BlackLine(void);

#endif















