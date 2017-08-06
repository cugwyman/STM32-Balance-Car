#include "key4x4.h"
#include "usart.h"
#include "delay.h"

//4x4����ɨ�裨�жϣ�

u8 key_data[4][4]={{13,3,2,1},{14,6,5,4},{15,9,8,7},{16,12,10,11}};
u8 key_value;
u8 Keyboard_Val =0;

unsigned char Keyboard_Change_Flag =0;
u8  key_pressed_flag=0;
void Delay(vu32 nCount) {
 for(; nCount!=0;nCount--); 
}

void KEY4x4_Init(void) //IO��ʼ��
{ 
 	
 	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
    
	//�������� 
	GPIO_InitStructure.GPIO_Pin = Keyboard_Row;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF, Keyboard_Row);
	
	//�������   
	GPIO_InitStructure.GPIO_Pin  = Keyboard_Line;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOE
	GPIO_SetBits(GPIOF, Keyboard_Line);

}

void Init_Keyboard_Interrupt(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    KEY4x4_Init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��(ʹ���жϺ�����ӳ��ʱҪʹ�ܸ��ù���ʱ��)
    
    EXTI_ClearITPendingBit(Keyboard_EXTI_Row1);
    GPIO_EXTILineConfig(Keyboard_EXTI_PortSource,Keyboard_EXTI_PinSource1);
    EXTI_ClearITPendingBit(Keyboard_EXTI_Row2);
    GPIO_EXTILineConfig(Keyboard_EXTI_PortSource,Keyboard_EXTI_PinSource2);
    EXTI_ClearITPendingBit(Keyboard_EXTI_Row3);
    GPIO_EXTILineConfig(Keyboard_EXTI_PortSource,Keyboard_EXTI_PinSource3);
    EXTI_ClearITPendingBit(Keyboard_EXTI_Row4);
    GPIO_EXTILineConfig(Keyboard_EXTI_PortSource,Keyboard_EXTI_PinSource4);
    
    EXTI_InitStructure.EXTI_Line= Keyboard_EXTI_Line;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
	 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn|EXTI4_IRQn|EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}


//void EXTI15_10_IRQHandler(void){
//  	u32 ReadValue;
//	  u32 tmpFlag=0;//������Ҫ���жϱ�־λ
//    delay_ms(5);
//	  ReadValue=GPIO_ReadInputData(Keyboard_Control_Port);
//    printf("ReadValue2=%x\n",ReadValue);
//	printf("\n");
//	tmpFlag=(ReadValue&0x7800);
//	
//	printf("tmpFlag=%x\n",tmpFlag);

////	  printf("EXTI->PR=%x\n",EXTI->PR);
//	GPIO_ResetBits(Keyboard_Control_Port,Keyboard_Row);
////	printf("\n");
//    EXTI_ClearFlag(Keyboard_EXTI_Line);
//	
//}




//GPIO�˿�ѡ�з�ʽ��ʽѡ��
void EXTI15_10_IRQHandler(void){
	key_pressed_flag=1;
    printf("in interrupt\n");

    key_value = key_scan();

	EXTI_ClearFlag(Keyboard_EXTI_Line);
}

u8  key_scan(void){
	u32 tmpFlag=0;//������Ҫ���жϱ�־λ
	u32 ReadValue;
	u8 i=0;
	ReadValue=GPIO_ReadInputData(Keyboard_Control_Port);
	tmpFlag=(ReadValue&0x7800);
	
	switch(tmpFlag)
    {
        case Keyboard_EXTI_Row1:
            GPIO_ResetBits(Keyboard_Control_Port ,Keyboard_Line); 
            for(i=0;i<4;i++){
                GPIO_SetBits(Keyboard_Control_Port,(Keyboard_LineBase<<i));
                if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_1)){
                    Delay(DELAY_COUNT);
                    if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_1)){
                        Keyboard_Val=key_data[0][i];
                        Keyboard_Change_Flag =1;
                        break;
					}
				}	
			}
			GPIO_SetBits(Keyboard_Control_Port ,Keyboard_Line);
			break;
				
		case Keyboard_EXTI_Row2:
            GPIO_ResetBits(Keyboard_Control_Port ,Keyboard_Line); 
            for(i=0;i<4;i++){
                GPIO_SetBits(Keyboard_Control_Port,(Keyboard_LineBase<<i));
                if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_2)){
                    Delay(DELAY_COUNT);
                    if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_2)){
                        Keyboard_Val=key_data[1][i];
                        Keyboard_Change_Flag =1;
                        break;
					}
				}	
			}
			GPIO_SetBits(Keyboard_Control_Port ,Keyboard_Line);
			break;
				
		case Keyboard_EXTI_Row3:
            GPIO_ResetBits(Keyboard_Control_Port ,Keyboard_Line); 
            for(i=0;i<4;i++){
                GPIO_SetBits(Keyboard_Control_Port,(Keyboard_LineBase<<i));
                if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_3)){
                    Delay(DELAY_COUNT);
                    if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_3)){
                                Keyboard_Val=key_data[2][i];
                                Keyboard_Change_Flag =1;
                                break;
                    }
                }	
			}
			GPIO_SetBits(Keyboard_Control_Port ,Keyboard_Line);
			break;
				
		case Keyboard_EXTI_Row4:
		GPIO_ResetBits(Keyboard_Control_Port ,Keyboard_Line); 
            for(i=0;i<4;i++){
                GPIO_SetBits(Keyboard_Control_Port,(Keyboard_LineBase<<i));
                if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_4)){
//			    	Delay(DELAY_COUNT);
                    if(GPIO_ReadInputDataBit(Keyboard_Control_Port ,Keyboard_Row_4)){
                                Keyboard_Val=key_data[3][i];
                                Keyboard_Change_Flag =1;
                                break;
                    }
                }	
            }
            GPIO_SetBits(Keyboard_Control_Port ,Keyboard_Line);
            break;
            
        default:
            break;
	}
	GPIO_ResetBits(Keyboard_Control_Port,Keyboard_Row);
	return Keyboard_Val;
}





