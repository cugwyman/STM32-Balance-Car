#include "Angle.h"
#include "fuzzy.h"
#include <math.h>
#include "MPU6050.h"
float Kal_Gyro;
float gyro;
int16_t mmax, mmaz;
float angle, angleSpeed;
float Angle_Kalman;
int16_t Pre_Angle_Kalman;
float angleSpeedIntegral;

float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 },{ 0, 1 } };

/**
 * @brief  卡尔曼滤波, 输入带有噪声的参数组, 返回可靠的参数组, 此处用于获得变化较稳定的角度值
 * @param[in]  angle_kal 由加速度计得到的角度参量
 * \param[in]  angle_speed_kal 由陀螺仪得到的角速度参量
 * @retval 稳定可靠的角度值, 用于直立控制
 */

static float KalmanFilter(float Accel,float Gyro)		
{
    static float Angle = 0, Gyro_y = 0;
	Angle+=(Gyro - Q_bias) * dt; //先验估计

	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3]= Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;	//zk-先验估计
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //后验估计
	Q_bias	+= K_1 * Angle_err;	 //后验估计
	Gyro_y   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
	return Angle;
}

/**
 * @brief  角度PID准闭环
 * @param[in]  set 设定目标角度, 尽可能接近实际的机械零点, 在头文件Param.h中定义为AC_Set
 * \param[in]  nextPoint 当前角度值
 * @retval 角度环输出, 作为标准电机输出的一环
 */
static int32_t AnglePID(float set, float nextPoint)
{ 
    float error;
    float P, D;
    int32_t incpid;
    
    error = set - nextPoint;
    P = AC_PID_P * error;
    D = AC_PID_D * angleSpeed;
    
    incpid = P - D;
    return(incpid);
}

/**
 * @brief  标准角度环处理
 * @retval 角度环输出, 作为标准电机输出的一环
 */
int32_t AngleProc() 
{
//    AcceGet(&mmax, &mmaz);
    angle = -atan2f((float)g_Acc_xtemp,(float)g_Acc_ztemp) * 180 / PI;

    angleSpeed = GyroGet() / 16.4;
	angleSpeedIntegral += angleSpeed * 0.005;
    Angle_Kalman = KalmanFilter(angle, angleSpeed);
    
    if(Angle_Kalman < 0)
        Angle_Kalman = 0;
    return -AnglePID(MODE.AC_Set, Angle_Kalman);
}
