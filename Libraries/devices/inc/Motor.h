#ifndef __MOTOR_H
#define __MOTOR_H

#define MOTOR
#define  MOTOR_STOP  MotorOut(0, 0)

#include "Root.h"

void MotorInit(void);
void MotorOut(int32_t LEFT_MOTOR_OUT, int32_t RIGHT_MOTOR_OUT);


#endif


