#include "Encoder.h"
#include "ftm.h"
#include "uart.h"
#include "DataComm.h"

/**
 * @brief  编码器初始化, 使用两个正交解码通道, MAP在头文件PinMap.h中定义
 */
void EncoderInit(void) {
    FTM_QD_QuickInit(LEFT_ENCODER_MAP,  kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(RIGHT_ENCODER_MAP, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
}

/**
 * @brief  编码器采集, 获得脉冲计数(衡量电机实际转速)
 * @retval 左右轮速度平均值, 用于速度闭环和方向环动态P变化
 */
int32_t EncoderGet(void) {
    int16_t leftSpeed, rightSpeed;
    uint8_t leftDir, rightDir;
    
    FTM_QD_GetData(LEFT_ENCODER_CHL, &leftSpeed, &leftDir);
    FTM_QD_ClearCount(LEFT_ENCODER_CHL);
    FTM_QD_GetData(RIGHT_ENCODER_CHL, &rightSpeed, &rightDir);
    FTM_QD_ClearCount(RIGHT_ENCODER_CHL);
    
    leftSpeed = -leftSpeed;
	return (leftSpeed + rightSpeed) / 2;
}
