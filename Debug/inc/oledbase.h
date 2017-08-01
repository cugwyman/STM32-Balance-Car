/**
  ******************************************************************************
  * @file    oled.h
  * @author  ***
  * @version V2.5
  * @date    2014.12.7
  * @brief   597898332@qq.com    
  * @note    ���ļ�ΪоƬOLED�ĵײ㹦�ܺ���ͷ�ļ�
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

#define		OELD_DC_PORT	PTE      //ֻ�Ĵ˴������У�OLED_Init�ж˿ں�Ҳ
#define		OELD_DC_PIN		3       //��Ҫ����Ӧ�Ķ�//A 12 13 16 15
#define		OELD_RST_PORT	PTE
#define		OELD_RST_PIN	4
#define		OELD_D1_PORT	PTE
#define		OELD_D1_PIN    5
#define		OELD_D0_PORT	PTE
#define		OELD_D0_PIN	   6


//__________________________________________________________________

 enum
{
	FC_ST_16 = 0,		/* ����15x16���� ����x�ߣ� */
	FC_ST_12 = 1		/* ����12x12���� ����x�ߣ� */
};

typedef struct
{
	uint16_t usFontCode;	/* ������� 0 ��ʾ16���� */
	uint16_t usTextColor;	/* ������ɫ 0 �� 1 */
	uint16_t usBackColor;	/* ���ֱ�����ɫ 0 �� 1 */
	uint16_t usSpace;		/* ���ּ�࣬��λ = ���� */
}FONT_T;




//__OLED__�Ӻ�������__________________________________________________

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
