#ifndef __CH_LIB_MPU6050_H__
#define __CH_LIB_MPU6050_H__

#include "i2c.h"
#include "DataComm.h"
#include "root.h"
#include "gpio.h"

//************6050内部寄存器定义***************
#define	 AUX_VDDIO					0x01		//1		辅助I2C电源选择寄存器			
#define	 SELF_TEST_X				0x0D		//13 	X轴自检寄存器
#define	 SELF_TEST_Y				0x0E		//14 	Y轴自检寄存器		
#define	 SELF_TEST_Z				0x0F		//15 	Z轴自检寄存器
#define	 SELF_TEST_A				0x10		//16	加速度计自检
#define	 SMPLRT_DIV				 	0x19		//19	样本频率分频寄存器
#define	 CONFIG					 	0x1A		//26	配置寄存器		
#define  GYRO_CONFIG				0x1B		//27	陀螺仪配置寄存器	
#define  ACCEL_CONFIG 				0x1C		//28	加速寂渲眉拇嫫髌				
#define  FF_THR	 					0x1D		//29	自由落体阈值寄存器				
#define  FF_DUR						0x1E		//30	自由落体持续时间寄存器			
#define  MOT_THR					0x1F		//31	运动探测阈值寄存器			
#define  MOT_DUR					0x20		//32	运动探测持续时间寄存器				
#define  ZRMOT_THR					0x21		//33	零运动阈值检测寄存器				
#define  ZRMOT_DUR					0x22		//34	零运动持续时间寄存器		
#define  FIFO_EN					0x23		//35	FIFO使能寄存器				
#define  INT_PIN_CFG				0x37		//55	中断引脚/旁路使能配置寄存器			
#define  INT_ENABLE					0x38		//56	中断使能寄存器				
#define  INT_STATUS					0x3A		//58	中断状态寄存器				
#define  ACCEL_XOUT_H				0x3B		//59	加速计测量值寄存器		X轴高八位		
#define  ACCEL_XOUT_L				0x3C		//60	加速计测量值寄存器		X轴低八位
#define  ACCEL_YOUT_H				0x3D		//61	加速计测量值寄存器		Y轴高八位		
#define  ACCEL_YOUT_L				0x3E		//62	加速计测量值寄存器		Y轴低八位		
#define  ACCEL_ZOUT_H				0x3F		//63	加速计测量值寄存器		Z轴高八位		
#define  ACCEL_ZOUT_L				0x40		//64	加速计测量值寄存器		Z轴低八位		
#define  TEMP_OUT_H					0x41		//65	温度测量值寄存器		高八位			
#define  TEMP_OUT_L					0x42		//66	温度测量值寄存器		低八位			
#define  GYRO_XOUT_H				0x43		//67	陀螺仪测量值寄存器		X轴高八位		
#define  GYRO_XOUT_L				0x44		//68	陀螺仪测量值寄存器		X轴低八位		
#define  GYRO_YOUT_H				0x45		//69	陀螺仪测量值寄存器		Y轴高八位		
#define  GYRO_YOUT_L				0x46		//70	陀螺仪测量值寄存器		Y轴低八位		
#define  GYRO_ZOUT_H				0x47		//71	陀螺仪测量值寄存器		Z轴高八位		
#define  GYRO_ZOUT_L				0x48		//72	陀螺仪测量值寄存器		Z轴低八位		
#define  MOT_DETECT_STATUS			0x61		//97	运动探测状态寄存器				
#define  I2C_SLV0_D0				0x63		//99	I2C0模式数据输出寄存器				
#define  I2C_SLV1_D0				0x64		//100	I2C1模式数据输出寄存器			
#define  I2C_SLV2_D0				0x65		//101	I2C2模式数据输出寄存器			
#define  I2C_SLV3_D0				0x66		//102	I2C3模式数据输出寄存器			
#define  I2C_MST_DELAY_CTRL			0x67		//103	I2C主机模式延时控制寄存器				
#define  SINGLE_PATH_RESET			0x68		//104	数据信号路径复位寄存器（清空模拟和数字信号路径）			
#define  MOT_DETECT_CTRL			0x69		//105	运动探测控制寄存器			
#define  USER_CTRL					0x6A		//106	用户控制寄存器			
#define  PWR_MGMT_1					0x6B		//107	电源管理寄存器1			
#define  PWR_MGMT_2					0x6C		//108	电源管理寄存器2		
#define  FIFO_COUNTH				0x72		//		FIFO计数器寄存器高八位		
#define  FIFO_COUNTL				0x73		//		FIFO计数器寄存器低八位		
#define  FIFO_R_W					0x74		//		FIFO读写寄存器		
#define  WHO_AM_I					0x75		//		身份验证寄存器		

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
