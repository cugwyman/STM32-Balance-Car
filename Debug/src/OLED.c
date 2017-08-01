#include "gpio.h"
#include "common.h"
#include "oledbase.h"
#include "OLED.h"
#include "root.h"
#include "ImgProc.h"
#include "MainProc.h"

//****************************************************************************
//  ��������Oled_Init_n(void)
//  ���ܣ���OLED��Ļ���г�ʼ��
//  ˵������
//*****************************************************************************/ 
void Oled_Init_n(void)
{
	OLED_Init();                                
	OLED_StartDraw();                            
	OLED_ClrScr(0);
	OLED_EndDraw();
//	OLED_DispStr(54,24,"CUG",&tFont16);
//	OLEDPrintf(0,0,"Welcome!");
//	OLED_DrawCircle(64,32,30,0xff);
//	OLED_Disp_Data(60,30,6);
}

/*oled��ʾ��Ϣ����_______________________*/

//****************************************************************************
//  ��������Oled_Printf_Number(int x,int y,int z,int m,int n,int l)
//  ���ܣ�OLED�ֱ���ʾ5������,lΪ��ʾ����λ��
//  ˵����OLED_Disp_DataΪ��ʾ��λ������
//*****************************************************************************/ 
void Oled_Printf_Number(int x,int y,int z,int m,int n,int l)
{
	OLED_Disp_Data(l,0,x);  
 	OLED_Disp_Data(l,12,y);   
 	OLED_Disp_Data(l,24,z); 
 	OLED_Disp_Data(l,36,m);   
	OLED_Disp_Data(l,48,n);      
}

//****************************************************************************
//  ��������Oled_PrintfPhoto(unsigned char table[row][line])
//  ���ܣ�OLED��ʾ��ֵ�����ͼ��(row*line)
//  ˵�����ֱ���ͨ���ı�������ٸı�
//*****************************************************************************
void Oled_PrintfPhoto1(byte table[IMG_ROW][IMG_COL])
{
	int i,j,h;
	
	for(i=0;i<IMG_ROW-1;i++)
	{
		h=0;
		for(j=0;j<IMG_COL;j+=2)
		{
				if(2*h==resultSet.middleLine[i])
				{
					OLED_PutPixel(h,IMG_ROW-2-i,0);	
				}
				else
				{
					if(table[i][j]==0)
						OLED_PutPixel(h,IMG_ROW-2-i,1);
					else
						OLED_PutPixel(h,IMG_ROW-2-i,0);	
				}
			h++;
		}
	}
}
