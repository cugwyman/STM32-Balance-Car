#ifndef __CH_LIB_KEY_OLED_BUZZER_H__
#define __CH_LIB_KEY_OLED_BUZZER_H__
#include "root.h"

void Oled_Init_n(void);
void Oled_Printf_Number(int x,int y,int z,int m,int n,int l);
void Oled_PrintfPhoto1(byte table[IMG_ROW][IMG_COL]);

#endif
