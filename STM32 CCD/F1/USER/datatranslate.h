
#ifndef __DATATRANSLATE_H
#define __DATATRANSLATE_H

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
void OutPut_Data(float a,float b,float c,float d);
void Output_Ccd(unsigned char CCD_Value[]);
float StoDChange(char dat[],char num);
void Uart_PrintfPhoto(void);
void Uart_PrintfPhoto1(void);
#endif

