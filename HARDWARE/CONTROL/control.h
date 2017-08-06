#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "mode_switch.h"
#include "encoder.h"
#include "infrared.h"
#include "usart.h"

#include "Param.h"
#include "Config.h"
#include "Typedef.h"

extern mode MODE;

extern float pitch, roll, yaw; 		
extern short groyx, gyroy, gyroz;
extern int speed;
extern int16_t state;//·½ÏòÆ«²î
extern int32_t ac_pwm, vc_pwm, dc_pwm, left_pwm, right_pwm;

void get_pwm(void);
void get_mpu(void);
int get_speed(void);
void motor_proc(int32_t LEFT_MOTOR_OUT, int32_t RIGHT_MOTOR_OUT);
int32_t angle_proc(void);
int32_t velocity_proc(int32_t speed); 
int32_t direction_proc(int32_t speed);

#endif

