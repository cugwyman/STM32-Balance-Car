#ifndef __KEY4X4_H
#define __KEY4X4_H	 
#include "sys.h"
//#include "stm32f10x_lib.h"

#define Interrupt_Scan
#define DELAY_COUNT 0x0FFFF

#define Keyboard_Control_Port   GPIOF
#define Keyboard_Line_1 GPIO_Pin_10
#define Keyboard_Line_2 GPIO_Pin_5 
#define Keyboard_Line_3 GPIO_Pin_7 
#define Keyboard_Line_4 GPIO_Pin_9 

#define Keyboard_Row_1 GPIO_Pin_2
#define Keyboard_Row_2 GPIO_Pin_4
#define Keyboard_Row_3 GPIO_Pin_6
#define Keyboard_Row_4 GPIO_Pin_8

#define Keyboard_LineBase Keyboard_Line_1
#define Keyboard_RowBase Keyboard_Row_1
#define Keyboard_Line  (Keyboard_Line_1|Keyboard_Line_2|Keyboard_Line_3|Keyboard_Line_4)
#define Keyboard_Row  (Keyboard_Row_1|Keyboard_Row_2|Keyboard_Row_3|Keyboard_Row_4)

#ifdef Interrupt_Scan 
#define Keyboard_EXTI_Row1   EXTI_Line2
#define Keyboard_EXTI_Row2   EXTI_Line4
#define Keyboard_EXTI_Row3   EXTI_Line6
#define Keyboard_EXTI_Row4   EXTI_Line8

#define Keyboard_EXTI_PortSource  GPIO_PortSourceGPIOF
#define Keyboard_EXTI_PinSource1  GPIO_PinSource2 
#define Keyboard_EXTI_PinSource2  GPIO_PinSource4 
#define Keyboard_EXTI_PinSource3  GPIO_PinSource6
#define Keyboard_EXTI_PinSource4  GPIO_PinSource8

#define Keyboard_IRQ_Channel EXTI9_5_IRQChannel
#define Keyboard_EXTI_Line (Keyboard_EXTI_Row1 |Keyboard_EXTI_Row2 |Keyboard_EXTI_Row3 |Keyboard_EXTI_Row4)
#endif

//键盘全局声明
extern u8 Keyboard_Val ;//当前键值
extern unsigned char Keyboard_Change_Flag;//键值改变标志，读入新键值后，标志位清零
extern u8  key_pressed_flag;  //有按键按下时置1
extern u8 key_value;

#ifdef Interrupt_Scan
//extern void Delay(vu32 nCount);
extern u8 key_scan(void);
extern void KEY4x4_Init(void);
extern void Init_Keyboard_Interrupt(void);
#endif

#endif
