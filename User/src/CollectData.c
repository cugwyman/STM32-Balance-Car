//#include "CollectData.h"
//#include "adc.h"

//static int32_t Gyro_Zero;//���������
//static int32_t DirGyro_Zero;//�������������



///**
// * @brief  �����ǲɼ�, ����ֱ��������(�辭���˲�)
// * @retval �����ǲɼ�(��ȥ���)
// */
//int32_t GyroGet(void) 
//{
//	return ADC_QuickReadValue(GYRO_MAP) - Gyro_Zero;
//}

///**
// * @brief  ���������ǲɼ�, ���ڷ��򻷿���
// * @retval ���������ǲɼ�(��ȥ���)
// */
//int32_t DirGyroGet(void) 
//{
//    return ADC_QuickReadValue(DIR_GYRO_MAP) - DirGyro_Zero;
//}

///**
// * @brief  ���ٶȼƲɼ�, ����ֱ��������(�辭���˲�)
// * @param[in]  mmax ���ٶȼ�X��ɼ�, ��ָ��ȡ��
// * \param[in]  mmaz ���ٶȼ�Z��ɼ�, ��ָ��ȡ��
// */
//void AcceGet(int32_t* mmax, int32_t* mmaz) 
//{
//    *mmax = ADC_QuickReadValue(ACCE_MMAX_MAP) - MMAX_ZERO;
//    *mmaz = ADC_QuickReadValue(ACCE_MMAZ_MAP) - MMAZ_ZERO;
//}
