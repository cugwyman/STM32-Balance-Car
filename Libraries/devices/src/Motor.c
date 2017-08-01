#include "Motor.h"
#include "ftm.h"

/* ��FTM0���õ��PWM,QuickInitռ�ձ�50% */
void MotorInit(void) {
    FTM_PWM_QuickInit(LEFT_MOTOR_FORWARD_MAP, kPWM_EdgeAligned, 10000);
    FTM_PWM_QuickInit(LEFT_MOTOR_REVERSE_MAP, kPWM_EdgeAligned, 10000);
    FTM_PWM_QuickInit(RIGHT_MOTOR_FORWARD_MAP, kPWM_EdgeAligned, 10000);
    FTM_PWM_QuickInit(RIGHT_MOTOR_REVERSE_MAP, kPWM_EdgeAligned, 10000);

    MotorOut(FIX_OUT, FIX_OUT);
}

/**
 * @brief  ��׼������, �����������ͷ��Ŵ���
 * @param[in]  LEFT_MOTOR_OUT  �������, ���ž�������ת
 * \param[in]  RIGHT_MOTOR_OUT �ҵ�����, ���ž�������ת
 */
void MotorOut(int32_t LEFT_MOTOR_OUT, int32_t RIGHT_MOTOR_OUT) {
    if( LEFT_MOTOR_OUT > MOTOR_OUT_MAX ){
        LEFT_MOTOR_OUT = MOTOR_OUT_MAX;
    }
    else if( LEFT_MOTOR_OUT < -MOTOR_OUT_MAX ){
        LEFT_MOTOR_OUT = -MOTOR_OUT_MAX;
    }
    
    if( RIGHT_MOTOR_OUT > MOTOR_OUT_MAX ){
        RIGHT_MOTOR_OUT = MOTOR_OUT_MAX;
    }
    else if( RIGHT_MOTOR_OUT < -MOTOR_OUT_MAX ){
        RIGHT_MOTOR_OUT = -MOTOR_OUT_MAX;
    }
    
    if( LEFT_MOTOR_OUT >= 0 ){
        FTM_PWM_ChangeDuty(MOTOR_PORT, LEFT_MOTOR_FORWARD_CHL, LEFT_MOTOR_OUT);
        FTM_PWM_ChangeDuty(MOTOR_PORT, LEFT_MOTOR_REVERSE_CHL, 0);
    }
    else{
        FTM_PWM_ChangeDuty(MOTOR_PORT, LEFT_MOTOR_FORWARD_CHL, 0);
        FTM_PWM_ChangeDuty(MOTOR_PORT, LEFT_MOTOR_REVERSE_CHL, -LEFT_MOTOR_OUT);
    }
    
    if( RIGHT_MOTOR_OUT >= 0 ){
        FTM_PWM_ChangeDuty(MOTOR_PORT, RIGHT_MOTOR_FORWARD_CHL, RIGHT_MOTOR_OUT);
        FTM_PWM_ChangeDuty(MOTOR_PORT, RIGHT_MOTOR_REVERSE_CHL, 0);
    }
    else{
        FTM_PWM_ChangeDuty(MOTOR_PORT, RIGHT_MOTOR_FORWARD_CHL, 0);
        FTM_PWM_ChangeDuty(MOTOR_PORT, RIGHT_MOTOR_REVERSE_CHL, -RIGHT_MOTOR_OUT);
    }
}

