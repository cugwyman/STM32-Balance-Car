#ifndef _SPEED_CONTROL_H
#define _SPEED_CONTROL_H

#include "root.h"

void SpeedControlProc(int16_t leftSpeed, int16_t rightSpeed);
void SpeedTargetSet(uint16_t imgProcFlag);

//extern PID leftPid, rightPid;
extern int16_t leftSpeed, rightSpeed;
extern int16_t speed_control_sum_err_max;
extern int16_t speed_control_speed;
extern int16_t speed_control_acc_speed;
extern int16_t speed_control_dec_speed;

#endif
