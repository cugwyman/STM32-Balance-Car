#include "infrared.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "OLED.h"

/*************************************************
名称：void ST188_init()
功能：初始化ST188传感器
说明：使用的引脚 E8 E9 E10
输入参数：无
输出参数：无
返回值：  无
**************************************************/
void infrared_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6);
		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //另加的提示灯引脚初始化
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_0);
}

/*******************************************************************************
名称：s16 get_ir_dir_error(u8 state)
功能：使用ST188实现循迹功能
说明：具体转向控制需要大家自己给控制量
输入参数：ST188数据
输出参数：
返回值：  error 方向PID环的state
*******************************************************************************/
#define BIG 500
#define MIDDLE 400
#define LITTLE 300
#define MINI 0
#define SPEEDNEED 10//每10秒脉冲的个数，暂且设置我位10
s16 get_ir_dir_error(u8 state)
{
	static u8 Prestate=4;//初始化为4，即直行
	s8 error = 0;
	switch(state)
	{
		case 1://00001，偏左，向右转
            error = -20;
			Prestate=1;
			break;
		case 2://00010
            error = -10;
			Prestate=2;
			break;		
		case 3://00011
            error = -15;
			Prestate=3;
			break;		
		case 4://00100
            error = 0;
			Prestate=4;
			break;	
		case 6://00110
            error = -5;
			Prestate=6;
			break;	
		case 7://00111
            error = -10;
			Prestate=7;
			break;	
		case 8://01000
            error = 10;
			Prestate=8;
			break;	
		case 12://01100
            error = 5;
			Prestate=12;
			break;	
		case 14://01110
            error = 0;
			Prestate=14;
			break;	
		case 15://01111
            error = -5;
			Prestate=15;
			break;	
		case 16://10000
            error = 20;
			Prestate=16;
			break;	
		case 24://11000
            error = 15;
			Prestate=24;
			break;	
		case 28://11100
            error = 10;
			Prestate=28;
			break;	
		case 30://11110，不会出现的情况
            error = 5;
			Prestate=30;
			break;	
		
		default://其他不正常情况（主要是全0（无黑线）和全1（全黑，也就是车头抬得太高））
			if(Prestate == 1)
			{
                error = -20;
			}
			else if(Prestate == 2||Prestate == 7)
			{
                error = -10;
			}
			else if(Prestate == 3)
			{
                error = -15;
			}
			else if(Prestate == 4||Prestate == 14)
			{
                error = 0;
			}
			else if(Prestate == 6||Prestate == 15)
			{
                error = -5;
			}
			else if(Prestate == 8||Prestate == 28)
			{
                error = 10;
			}
			else if(Prestate == 12||Prestate == 30)
			{
                error = 5;
			}
			else if(Prestate == 16)
			{
                error = 20;
			}
			else if(Prestate == 24)
			{
                error = 15;
			}
			break;					
	}
    return error;
}

void BlackLine(void)
{
	if(ST188LL)
		{
//			OLED_P6x8Str(20,4,"1");
            OLED_ShowChar(20,4,1,16);
		}
		else
		{
//			OLED_P6x8Str(20,4,"0");
            OLED_ShowChar(20,4,1,16);
		}
		if(ST188L)
		{
//			OLED_P6x8Str(40,4,"1");
            OLED_ShowChar(20,4,1,16);
		}
		else
		{
//			OLED_P6x8Str(40,4,"0");
            OLED_ShowChar(20,4,1,16);
		}
		if(ST188M)
		{
//			OLED_P6x8Str(60,4,"1");
            OLED_ShowChar(20,4,1,16);
		}
		else
		{
//			OLED_P6x8Str(60,4,"0");
            OLED_ShowChar(20,4,1,16);
		}
		if(ST188R)
		{
//			OLED_P6x8Str(80,4,"1");
            OLED_ShowChar(20,4,1,16);
		}
		else
		{
//			OLED_P6x8Str(80,4,"0");
            OLED_ShowChar(20,4,1,16);
		}
		if(ST188RR)
		{
//			OLED_P6x8Str(100,4,"1");
            OLED_ShowChar(20,4,1,16);
		}
		else
		{
//			OLED_P6x8Str(100,4,"0");
            OLED_ShowChar(20,4,1,16);
		}
}

