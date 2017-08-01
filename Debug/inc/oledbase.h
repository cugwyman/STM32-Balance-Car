/**
  ******************************************************************************
  * @file    oled.h
  * @author  ***
  * @version V2.5
  * @date    2014.12.7
  * @brief   597898332@qq.com    
  * @note    此文件为芯片OLED的底层功能函数头文件
  ******************************************************************************
  */

#ifndef __CH_LIB_OLEDBASE_H__
#define __CH_LIB_OLEDBASE_H__


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "common.h"
#include "fonts.h"

#define Byte  unsigned char
#define word  unsigned int
#define dword unsigned long 



//__OLED__pin_map__________________________________________________

#define		OELD_DC_PORT	PTE      //只改此处不可行，OLED_Init中端口号也
#define		OELD_DC_PIN		3       //需要做相应改动//A 12 13 16 15
#define		OELD_RST_PORT	PTE
#define		OELD_RST_PIN	4
#define		OELD_D1_PORT	PTE
#define		OELD_D1_PIN    5
#define		OELD_D0_PORT	PTE
#define		OELD_D0_PIN	   6


//__________________________________________________________________

 enum
{
	FC_ST_16 = 0,		/* 宋体15x16点阵 （宽x高） */
	FC_ST_12 = 1		/* 宋体12x12点阵 （宽x高） */
};

typedef struct
{
	uint16_t usFontCode;	/* 字体代码 0 表示16点阵 */
	uint16_t usTextColor;	/* 字体颜色 0 或 1 */
	uint16_t usBackColor;	/* 文字背景颜色 0 或 1 */
	uint16_t usSpace;		/* 文字间距，单位 = 像素 */
}FONT_T;




//__OLED__子函数声明__________________________________________________

void OLED_Init(void);                      
void OLED_WrDat(unsigned char dat);
void OLED_WrCmd(unsigned char cmd);
void OLED_Set_Pos(unsigned char x,unsigned char y);
void OLED_Fill(unsigned char bmp_dat);
void OLED_CLS(void);
void OLED_DLY_ms(unsigned int ms);

void OLED_StartDraw(void);
void OLED_EndDraw(void);
void OLED_ClrScr(uint8_t _ucMode);

void OLED_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont);
void OLED_PutPixel(uint16_t _usX, uint16_t _usY, uint8_t _ucColor);

uint8_t OLED_GetPixel(uint16_t _usX, uint16_t _usY);
void OLED_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint8_t _ucColor);
void OLED_DrawPoints(uint16_t *x, uint16_t *y, uint16_t _usSize, uint8_t _ucColor);
void OLED_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint8_t _ucColor);
void OLED_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint8_t _ucColor);
void OLED_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t *_ptr);
void OLED_DrawWave(uint16_t _ptr, uint16_t Y);
void OLED_Disp_Data(int x,int y,int value);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);

extern FONT_T tFont12, tFont16;
#endif
