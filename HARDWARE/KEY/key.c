#include "key.h"
#include "oled.h"

uint8_t Item = 0;
uint8_t Param = 1;

void Key_IO_Init(void)	 //����IO����
{
    GPIO_InitTypeDef IO_Init;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);	
    IO_Init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5;				    
    IO_Init.GPIO_Mode = GPIO_Mode_IPD;	
    GPIO_Init(GPIOE, &IO_Init);
}

void KeyScan(void)
{
//        printf("scan\n");
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) == KEY_PRESSED) //K1
	{	
//        OLED_Clear();
//        printf("add\n");
		switch(Item)
		{
			case 1:
                if(Param==1)		//����4��
                    MODE.DC_PID_P_COEF += 1;
                if(Param==3)		//����4��
                    MODE.DC_PID_D += 1;
				   break; 
//			case 2:R+=5.0;
//				   if(R >= 35.0) R = 35.0;
//				   sprintf(buf,"DS16(6,60,'���ó���:%.1f ',10)\r\n",R);
//				   GpuSend(buf);	
//			       break;  //��2�ʰ���S4���Ӿ���

//			case 3:angle+=10.0;
//				   if(angle >= 180.0) 
//				   	  angle = 180.0;
//				   sprintf(buf,"DS16(6,80,'���ýǶ�:%.1f ',10)\r\n",angle);
//				   GpuSend(buf);	
//			       break;  //��3�ʰ���S4���ӽǶ�;  
//			
//			case 5:R+=5.0;
//				   if(R >= 35.0) R = 35.0;
//				   sprintf(buf,"DS16(6,100,'���ð뾶:%.1f ',10)\r\n",R);
//				   GpuSend(buf);
//				   break;

//			case 6:R+=5.0;
//				   if(R >= 35.0) R = 35.0;
//				   sprintf(buf,"DS16(6,100,'���ð뾶:%.1f ',10)\r\n",R);
//				   GpuSend(buf);
//				   break;
//				   

			default:break;
		}				
	}

	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1) == KEY_PRESSED) //K2
	{
//        OLED_Clear();
//        printf("sub\n");
		switch(Item)
		{
			case 1:
                if(Param==1)		//����4��
                    MODE.DC_PID_P_COEF -= 1;
                if(Param==3)		//����4��
                    MODE.DC_PID_D -= 1;
                        
				   break; 
//			case 2:R-=5.0;
//				   if(R <= 15.0) R = 15.0;
//				   sprintf(buf,"DS16(6,60,'���ó���:%.1f ',10)\r\n",R);
//				   GpuSend(buf);	
//			       break;  //��2�ʰ���S4���Ӿ���

//			case 3:angle-=10.0;
//				   if(angle <= 0.0) 
//				   	  angle = 0.0;
//				   sprintf(buf,"DS16(6,80,'���ýǶ�:%.1f ',10)\r\n",angle);
//				   GpuSend(buf);	
//			       break;  //��3�ʰ���S4���ӽǶ�;  
//			
//			case 5:R-=5.0;
//				   if(R <= 15.0) R = 15.0;
//				   sprintf(buf,"DS16(6,100,'���ð뾶:%.1f ',10)\r\n",R);
//				   GpuSend(buf);
//				   break;

//			case 6:R-=5.0;
//				   if(R <= 15.0) R = 15.0;
//				   sprintf(buf,"DS16(6,100,'���ð뾶:%.1f ',10)\r\n",R);
//				   GpuSend(buf);
//				   break;
//				   

			default:break;
		}		
	}
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == KEY_PRESSED) //K3
	{
//        OLED_Clear();
//        printf("last\n");
        Param--;
        if(Param<1)		//����3��
            Param = 3;
//        OLED_Clear();
//		switch(Item)
//		{
//			case 1:Q1_Start = 1;
//				   sprintf(buf,"DS16(6,120,'��ʼ!',10)\r\n");
//				   GpuSend(buf);
//				   break; 

//			case 2:Q2_Start = 1;
//				   sprintf(buf,"DS16(6,120,'��ʼ!',10)\r\n");
//				   GpuSend(buf);
//				   break;

//			case 3:Q3_Start = 1;
//				   sprintf(buf,"DS16(6,120,'��ʼ!',10)\r\n");
//				   GpuSend(buf);
//				   break;  

//			case 4:Q4_Start = 1;
//				   sprintf(buf,"DS16(6,120,'��ʼ!',10)\r\n");
//				   GpuSend(buf);break;
//				   
//			case 5:Q5_Start = 1;
//				   RoundDir = !RoundDir;
//				   if(RoundDir == 1)
//			       	   sprintf(buf,"DS16(6,120,'˳ʱ����ת!',10)\r\n");
//				   else
//				   	   sprintf(buf,"DS16(6,120,'��ʱ����ת!',10)\r\n");
//				   GpuSend(buf);break;
//				   
//			case 6:Q6_Start = 1;	       
//			       sprintf(buf,"DS16(6,120,'��ʼ!',10)\r\n");
//				   GpuSend(buf);break;   

//			default:break;
//		}	
	} 	

    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == KEY_PRESSED)  //K4
	{
//        OLED_Clear();
//        printf("next\n");
        Param++;
        if(Param>3)		//����3��
            Param = 1;
    }
    
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == KEY_PRESSED)  //K4
	{
        OLED_Clear();
		Item++;
		if(Item>3)		//����7��
			Item = 0;
//		sprintf(buf,"DS16(6,40,'��%d��',10)\r\n",Item);
//		GpuSend(buf);
	}
}

