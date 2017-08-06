#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "OscilloScope.h"

/*У��ͷ������ݺ���_______________________*/

//****************************************************************************
//  ��������CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
//  ���ܣ�У�麯��
//  ˵������
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
//  ��������OutPut_Data(float a,float b,float c,float d)
//  ���ܣ��������ݺ���
//  ˵������
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
		USART_SendData(USART1, databuf[i]);//���ͺ���(����1)
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}     
}

/*��_______________________*/

//****************************************************************************
//  ��������Output_Ccd(unsigned char CCD_Value[])
//  ���ܣ���
//  ˵������
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
//  ��������StoDChange(char dat[],char num)
//  ���ܣ���
//  ˵������
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





