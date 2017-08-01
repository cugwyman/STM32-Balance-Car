#ifndef __CH_LIB_MPU6050_H__
#define __CH_LIB_MPU6050_H__

#include "i2c.h"
#include "DataComm.h"
#include "root.h"
#include "gpio.h"

//************6050�ڲ��Ĵ�������***************
#define	 AUX_VDDIO					0x01		//1		����I2C��Դѡ��Ĵ���			
#define	 SELF_TEST_X				0x0D		//13 	X���Լ�Ĵ���
#define	 SELF_TEST_Y				0x0E		//14 	Y���Լ�Ĵ���		
#define	 SELF_TEST_Z				0x0F		//15 	Z���Լ�Ĵ���
#define	 SELF_TEST_A				0x10		//16	���ٶȼ��Լ�
#define	 SMPLRT_DIV				 	0x19		//19	����Ƶ�ʷ�Ƶ�Ĵ���
#define	 CONFIG					 	0x1A		//26	���üĴ���		
#define  GYRO_CONFIG				0x1B		//27	���������üĴ���	
#define  ACCEL_CONFIG 				0x1C		//28	���ټ���üĴ����				
#define  FF_THR	 					0x1D		//29	����������ֵ�Ĵ���				
#define  FF_DUR						0x1E		//30	�����������ʱ��Ĵ���			
#define  MOT_THR					0x1F		//31	�˶�̽����ֵ�Ĵ���			
#define  MOT_DUR					0x20		//32	�˶�̽�����ʱ��Ĵ���				
#define  ZRMOT_THR					0x21		//33	���˶���ֵ���Ĵ���				
#define  ZRMOT_DUR					0x22		//34	���˶�����ʱ��Ĵ���		
#define  FIFO_EN					0x23		//35	FIFOʹ�ܼĴ���				
#define  INT_PIN_CFG				0x37		//55	�ж�����/��·ʹ�����üĴ���			
#define  INT_ENABLE					0x38		//56	�ж�ʹ�ܼĴ���				
#define  INT_STATUS					0x3A		//58	�ж�״̬�Ĵ���				
#define  ACCEL_XOUT_H				0x3B		//59	���ټƲ���ֵ�Ĵ���		X��߰�λ		
#define  ACCEL_XOUT_L				0x3C		//60	���ټƲ���ֵ�Ĵ���		X��Ͱ�λ
#define  ACCEL_YOUT_H				0x3D		//61	���ټƲ���ֵ�Ĵ���		Y��߰�λ		
#define  ACCEL_YOUT_L				0x3E		//62	���ټƲ���ֵ�Ĵ���		Y��Ͱ�λ		
#define  ACCEL_ZOUT_H				0x3F		//63	���ټƲ���ֵ�Ĵ���		Z��߰�λ		
#define  ACCEL_ZOUT_L				0x40		//64	���ټƲ���ֵ�Ĵ���		Z��Ͱ�λ		
#define  TEMP_OUT_H					0x41		//65	�¶Ȳ���ֵ�Ĵ���		�߰�λ			
#define  TEMP_OUT_L					0x42		//66	�¶Ȳ���ֵ�Ĵ���		�Ͱ�λ			
#define  GYRO_XOUT_H				0x43		//67	�����ǲ���ֵ�Ĵ���		X��߰�λ		
#define  GYRO_XOUT_L				0x44		//68	�����ǲ���ֵ�Ĵ���		X��Ͱ�λ		
#define  GYRO_YOUT_H				0x45		//69	�����ǲ���ֵ�Ĵ���		Y��߰�λ		
#define  GYRO_YOUT_L				0x46		//70	�����ǲ���ֵ�Ĵ���		Y��Ͱ�λ		
#define  GYRO_ZOUT_H				0x47		//71	�����ǲ���ֵ�Ĵ���		Z��߰�λ		
#define  GYRO_ZOUT_L				0x48		//72	�����ǲ���ֵ�Ĵ���		Z��Ͱ�λ		
#define  MOT_DETECT_STATUS			0x61		//97	�˶�̽��״̬�Ĵ���				
#define  I2C_SLV0_D0				0x63		//99	I2C0ģʽ��������Ĵ���				
#define  I2C_SLV1_D0				0x64		//100	I2C1ģʽ��������Ĵ���			
#define  I2C_SLV2_D0				0x65		//101	I2C2ģʽ��������Ĵ���			
#define  I2C_SLV3_D0				0x66		//102	I2C3ģʽ��������Ĵ���			
#define  I2C_MST_DELAY_CTRL			0x67		//103	I2C����ģʽ��ʱ���ƼĴ���				
#define  SINGLE_PATH_RESET			0x68		//104	�����ź�·����λ�Ĵ��������ģ��������ź�·����			
#define  MOT_DETECT_CTRL			0x69		//105	�˶�̽����ƼĴ���			
#define  USER_CTRL					0x6A		//106	�û����ƼĴ���			
#define  PWR_MGMT_1					0x6B		//107	��Դ����Ĵ���1			
#define  PWR_MGMT_2					0x6C		//108	��Դ����Ĵ���2		
#define  FIFO_COUNTH				0x72		//		FIFO�������Ĵ����߰�λ		
#define  FIFO_COUNTL				0x73		//		FIFO�������Ĵ����Ͱ�λ		
#define  FIFO_R_W					0x74		//		FIFO��д�Ĵ���		
#define  WHO_AM_I					0x75		//		�����֤�Ĵ���		

extern int16_t g_Acc_xtemp, g_Acc_ztemp, g_Gry_ztemp, g_Gry_ytemp;

//void Kalman_Filter(float Accel,float Gyro);
void mpu6050_init(void);
void Read_Acc_Gry(void);
//void AngleCalculate(void);

void CollectInit(void);
int16_t GyroGet(void);
int16_t DirGyroGet(void);
void AcceGet(int16_t* mmax, int16_t* mmaz);

#endif
