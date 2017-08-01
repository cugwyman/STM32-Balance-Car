#include "gpio.h"
#include "common.h"
#include "oledbase.h"
#include "OLED.h"
#include "root.h"
#include "ImgProc.h"
#include "MainProc.h"

//****************************************************************************
//  函数名：Oled_Init_n(void)
//  功能：对OLED屏幕进行初始化
//  说明：无
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

/*oled显示信息函数_______________________*/

//****************************************************************************
//  函数名：Oled_Printf_Number(int x,int y,int z,int m,int n,int l)
//  功能：OLED分别显示5个变量,l为显示的列位置
//  说明：OLED_Disp_Data为显示两位数函数
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
//  函数名：Oled_PrintfPhoto(unsigned char table[row][line])
//  功能：OLED显示二值化后的图像(row*line)
//  说明：分辨率通过改变数组大少改变
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
