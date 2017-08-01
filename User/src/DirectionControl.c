#include "DirectionControl.h"
#include "ImgProc.h"
#include "uart.h"

double directionAngle;
double direction_control_kd;
double direction_control_kpj;
double direction_control_kpc;

static int16_t DirectionErrorGet(int16_t* middleLine, int16_t expectMiddle);
static int16_t DirectionControlPID(int16_t dirError);

void DirectionControlProc(int16_t* middleLine, int16_t expectMiddle) {
    SteerActuatorOut(DirectionControlPID(DirectionErrorGet(middleLine, expectMiddle)));
}

int16_t DirectionErrorGet(int16_t* middleLine, int16_t expectMiddle) {
    float avgMiddle = 0;
    for(int16_t i = pre_sight - 3; i < pre_sight + 3; ++i) {
        avgMiddle += middleLine[i];
    }
    avgMiddle /= 6;
    return expectMiddle - avgMiddle;
}

int16_t DirectionControlPID(int16_t error) {
    static int16_t lastError = 0;
    float kp = direction_control_kpj + (error * error) * direction_control_kpc;
    if(kp > 0.28) {
        kp = 0.28;
    }
	directionAngle = kp * error + direction_control_kd * (error - lastError);
    
	if(directionAngle > 14.4) {
		directionAngle = 14.4;
    } else if(directionAngle < -14.4) {
		directionAngle = -14.4;
    }
    
    lastError = error;
    
    return directionAngle * 5.556 + steer_actuator_middle;
}
