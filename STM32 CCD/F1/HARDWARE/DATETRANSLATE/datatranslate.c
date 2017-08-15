#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "datatranslate.h"
#include "CCD.h"
#include "road_identify.h"

extern  unsigned char image[row][line];
extern int left[row];             //×ó±ß½çÊý×é
extern int right[row];            //ÓÒ±ß½çÊý×é
extern int bottom[row];           //ÖÐÏßÊý×
extern int ph;
/*Ð£ÑéºÍ·¢ËÍÊý¾Ýº¯Êý_______________________*/
void Uart_PrintfPhoto(void);
//****************************************************************************
//  º¯ÊýÃû£ºCRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
//  ¹¦ÄÜ£ºÐ£Ñéº¯Êý
//  ËµÃ÷£ºÎÞ
//*****************************************************************************/ 
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++)
	{      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) 
		{
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

//****************************************************************************
//  º¯ÊýÃû£ºOutPut_Data(float a,float b,float c,float d)
//  ¹¦ÄÜ£º·¢ËÍÊý¾Ýº¯Êý
//  ËµÃ÷£ºÎÞ
//*****************************************************************************/ 
void OutPut_Data(float a,float b,float c,float d)
{	
	float OutData[4] = {0};
	int temp[4] = {0};
	unsigned int temp1[4] = {0};
	unsigned char databuf[10] = {0};
	unsigned char i;
	unsigned short CRC16 = 0;
	OutData[0]=a;
	OutData[1]=b;
	OutData[2]=c;
	OutData[3]=d;
	for(i=0;i<4;i++)
	{
		temp[i]  = (int)OutData[i];
		temp1[i] = (unsigned int)temp[i];
	}   
	for(i=0;i<4;i++) 
	{
		databuf[i*2]   = (unsigned char)(temp1[i]%256);
		databuf[i*2+1] = (unsigned char)(temp1[i]/256);
	}
  
	CRC16 = CRC_CHECK(databuf,8);
	databuf[8] = CRC16%256;
	databuf[9] = CRC16/256;
  
	for(i=0;i<10;i++) 
	{
		USART_SendData(USART1, databuf[i]);//·¢ËÍº¯Êý(´®¿Ú1)
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}     
}

/*ÎÞ_______________________*/

//****************************************************************************
//  º¯ÊýÃû£ºOutput_Ccd(unsigned char CCD_Value[])
//  ¹¦ÄÜ£ºÎÞ
//  ËµÃ÷£ºÎÞ
//*****************************************************************************/ 
void Output_Ccd(unsigned char CCD_Value[])
{
	int i;
    USART_SendData(USART1, 0xff);
    USART_SendData(USART1, 0x00);

	for(i=0;i<128;i++)
	{
		if(CCD_Value[i]>254) CCD_Value[i]=254;
		if(CCD_Value[i]<1) CCD_Value[i]=1;
		USART_SendData(USART1, CCD_Value[i]);
	}
}

//****************************************************************************
//  º¯ÊýÃû£ºStoDChange(char dat[],char num)
//  ¹¦ÄÜ£ºÎÞ
//  ËµÃ÷£ºÎÞ
//*****************************************************************************/ 
float StoDChange(char dat[],char num)
{
	//num 4
	char i,sign=0;
	float fdata;
    if(dat[4]=='-') 
		sign=1;
    else 
		sign=0;
	for(i=num;i<10;i++)
	{
		if(dat[i]>='0' && dat[i]<='9') 
			dat[i]=dat[i]-'0';
		else if(dat[i]>='A' && dat[i]<='F') 
			dat[i]=dat[i]-'A';
		else if(dat[i]=='\0') 
			break;
		else 
			dat[i]=0;
	}   
	fdata=dat[num]*100+dat[num+1]*10+dat[num+2]+dat[num+3]/10.0+dat[num+4]/100.0; 
	if(sign==1) 
		fdata=-fdata; 
	return fdata; 
}

/*ºìÊ÷Î°ÒµÉÏÎ»»»ú(·¢ËÍÍ¼Ïñ)______________________*/

//****************************************************************************
//  º¯ÊýÃû£ºUart_PrintfPhoto(void)
//  ¹¦ÄÜ£ºÍ¨¹ýÀ¶ÑÀÏòÉÏÎ»»ú·¢ËÍ¶þÖµ»¯ºóÍ¼Ïñ
//  ËµÃ÷£ºÎÞ
//*****************************************************************************/ 

void Uart_PrintfPhoto(void)
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<=line-1;j++)
		{
//			if(image[i][j]==0x00)
//			USART_SendData(USART1,0x00);
//			else
//			USART_SendData(USART1,0xfe);
				USART_SendData(USART1,image[i][j]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
		}				
	}
     USART_SendData(USART1,0xff);
}

//****************************************************************************
//  º¯ÊýÃû£ºUart_PrintfPhoto1(void)
//  ¹¦ÄÜ£ºÍ¨¹ýÀ¶ÑÀÏòÉÏÎ»»ú·¢ËÍ¶þÖµÍ¼¼°ÆäÖÐÏßÎ»ÖÃ
//  ËµÃ÷£º×óÓÒ±ß½ç·¢ËÍ0xA0,ÈüµÀÖÐÐÄ·¢ËÍ0xfe£¬Ç°Õ°ÐÐµ×É«Ç³Ò»Ð©
//*****************************************************************************/ 
void Uart_PrintfPhoto1(void)
{
	static   int i,j;
		for(i=row-1;i>=0;i--)
		{
			for(j=0;j<=line-1;j++)
			{
				if(i==ph)
				{
					if((j==left[i])||(j==right[i]))	{	
				
						USART_SendData(USART1,0x00);
					if (j==bottom[i]){
						 USART_SendData(USART1,0xfe);
					 }
					
					}
					else
					{
						if(image[i][j]==0x10)	
							USART_SendData(USART1,0x20);
						else
							USART_SendData(USART1,0xe0);
					}
				}
				else
				{
					if((j==left[i])||(j==right[i]))	{
						USART_SendData(USART1,0xa0);
				   	if (j==bottom[i]){
						 USART_SendData(USART1,0xfe);
					 }
					}
					else
					{
						if(image[i][j]==0x01)	
							USART_SendData(USART1,0x00);
						else
							USART_SendData(USART1,0xfe);
					}
				}
			}				
		}
		USART_SendData(USART1,0xff);
}























