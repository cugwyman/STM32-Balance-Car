//#include "CollectData.h"
//#include "adc.h"

//static int32_t Gyro_Zero;//陀螺仪零点
//static int32_t DirGyro_Zero;//方向陀螺仪零点



///**
// * @brief  陀螺仪采集, 用于直立环控制(需经过滤波)
// * @retval 陀螺仪采集(已去零点)
// */
//int32_t GyroGet(void) 
//{
//	return ADC_QuickReadValue(GYRO_MAP) - Gyro_Zero;
//}

///**
// * @brief  方向陀螺仪采集, 用于方向环控制
// * @retval 方向陀螺仪采集(已去零点)
// */
//int32_t DirGyroGet(void) 
//{
//    return ADC_QuickReadValue(DIR_GYRO_MAP) - DirGyro_Zero;
//}

///**
// * @brief  加速度计采集, 用于直立环控制(需经过滤波)
// * @param[in]  mmax 加速度计X轴采集, 由指针取走
// * \param[in]  mmaz 加速度计Z轴采集, 由指针取走
// */
//void AcceGet(int32_t* mmax, int32_t* mmaz) 
//{
//    *mmax = ADC_QuickReadValue(ACCE_MMAX_MAP) - MMAX_ZERO;
//    *mmaz = ADC_QuickReadValue(ACCE_MMAZ_MAP) - MMAZ_ZERO;
//}
