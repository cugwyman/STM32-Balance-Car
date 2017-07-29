#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "mpu6050.h"
#include "usmart.h"   
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "encoder.h"
#include "timer.h"

 
/************************************************
*
*   TO DO:6050��㣬ֱ������
*
************************************************/

 	
 int main(void)
 {	 
//	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
//	u8 key;
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
//	short temp;					//�¶�	
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//�ο������ڷ���
	delay_init();	//��ʱ��ʼ�� 
//	usmart_dev.init(72);		//��ʼ��USMART
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD  ,��OLED,A2345
	PWM_Init(4800-1,3-1);	    //PWMƵ��=72000000/4800/3=5Khz  clk/(arr+1)/(psc+1)=freq,arrΪռ�ձȼ���ķ�ĸ
    ENCODER_Init();
	MPU_Init();					//��ʼ��MPU6050
    TIMER_Init(50-1,7200-1);      //5ms��ʱ�ж�
 	while(1)
	{
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES)
//		{
//			report=!report;
//		}
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
//			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			if(report)mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
//			if(report)usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
//			if((t%10)==0)
//			{ 
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//��ʾС������ 
//				temp=pitch*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,220,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//��ʾС������ 
//				temp=roll*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//��ʾС������ 
//				temp=yaw*10;
//				if(temp<0)
//				{
//					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
//					temp=-temp;		//תΪ����
//				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
//				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//��ʾ��������	    
//				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//��ʾС������  
//				t=0;
//				LED0=!LED0;//LED��˸
//			}
		}
//		t++; 
	} 	
}
 

//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{   	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
	USART_SendData(USART1,c);  
} 
//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}
//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1
}	
//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
}  

