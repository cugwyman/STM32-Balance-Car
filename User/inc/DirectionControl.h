#ifndef _DIRECTION_CONTROL_H
#define _DIRECTION_CONTROL_H

#include "root.h"

void DirectionControlProc(int16_t* middleLine, int16_t expectMiddle);

extern double directionAngle;
extern double direction_control_kd;
extern double direction_control_kpj;
extern double direction_control_kpc;

#endif
