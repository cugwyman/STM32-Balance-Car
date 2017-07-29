#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdint.h>
#include "mpu6050.h"
#include "inv_mpu.h"
#include "Param.h"
#include "stm32f10x.h"

void get_data(void);
int32_t angle_proc(void);


#endif

