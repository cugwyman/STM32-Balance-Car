#include "timer.h"
#include "key.h"
#include "key_4x4.h"
#include "oled.h"

//ͨ�ö�ʱ��5�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
u8 number_send_A[10];
u8 number_send_B[10];
u8 number_send_C[10];
u8 num_cnt_A;
u8 num_cnt_B;
u8 num_cnt_C;
u8 send_sign = 0;
void TIMER_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM5��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM5�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM5_IRQHandler(void)   //TIM5�ж�,���������ܸģ���startup_stm32f10x_hd.s�ļ�ȷ����
{
    
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //���TIM5�����жϷ������
	{
        static u8 cnt = 0;
//        get_mpu();
//        get_pwm();
//        motor_proc(left_pwm, right_pwm);
        cnt++;
        if(cnt % 25 == 0)	   //150msɨ��һ��
        {
            cnt = 0;
//            KeyScan();
            key_value = keyscanf();
            if(key_value!=0x10)
            {
                if(key_value==key_A)
                {
                    channel = 'A';
                    OLED_Clear();
                }
                if(key_value==key_B)
                {
                    channel = 'B';
                    OLED_Clear();
                }
                if(key_value==key_C)
                {
                    channel = 'C';
                    OLED_Clear();
                }
                if(key_value==key_D)
                {
                    OLED_Clear();
                    Item++;
                    if(Item>3)	
                    Item = 0;
                
                }
                if(key_value==OK)
                    send_sign = ~send_sign;
                if(channel == 'A')
                {
                    if(Item == 1)
                    {
                        number_send_A[0] = key_value;

//                        if(key_value <= 9)
//                        {
//                            number_send_A[num_cnt_A] = key_value;
//                            num_cnt_A++;
//                            if(num_cnt_A > 9)
//                                num_cnt_A = 0;
//                        }
                    }
                }
                if(channel == 'B')
                {
                    if(Item == 1)
                    {
                        number_send_B[0] = key_value;
//                        if(key_value <= 9)
//                        {
//                            number_send_B[num_cnt_B] = key_value;
//                            num_cnt_B++;
//                            if(num_cnt_B > 9)
//                                num_cnt_B = 0;
//                        }
                    }
                }
                if(channel == 'C')
                {
                    if(Item == 1)
                    {
                        number_send_C[0] = key_value;
//                        if(key_value <= 9)
//                        {
//                            number_send_C[num_cnt_C] = key_value;
//                            num_cnt_C++;
//                            if(num_cnt_C > 9)
//                                num_cnt_C = 0;
//                        }
                    }
                }

            }
//            printf("%d\n", key_value);
//            switch(Item)
//            {
//                case 0:
//                    TIM_SetCompare1(TIM3,100);	//tm3 ch1
//                    TIM_SetCompare2(TIM3,100);    //tm3 ch2
//                    TIM_SetCompare3(TIM3,100);    //tm3 ch2
//                    break;
//                case 1:
//                    TIM_SetCompare1(TIM3,100);	//tm3 ch1
//                    TIM_SetCompare2(TIM3,100);    //tm3 ch2
//                    TIM_SetCompare3(TIM3,100);    //tm3 ch2
//                    break;
//                case 2:
//                    TIM_SetCompare1(TIM3,100);	//tm3 ch1
//                    TIM_SetCompare2(TIM3,100);    //tm3 ch2
//                    TIM_SetCompare3(TIM3,100);    //tm3 ch2
//                    break;
//                default: break;
//               

//            }
        }
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx�����жϱ�־ 
	}
}












