#ifndef __VELOCITY_H
#define __VELOCITY_H

#include "Root.h"

extern mode MODE;

extern int16_t VC_Max;
extern int16_t VC_Min;
extern int16_t VC_Set;
extern int32_t AC_Max;
extern int32_t AC_Min;
extern int32_t AC_Set;
extern int16_t Pre_Sight_Set;

void GearInit(void);
void Mode3(void);
void Mode2(void);
void Mode1(void);
void Mode0(void);
int32_t VelocityPID(int32_t set, int32_t nextpoint);
int32_t VelocityProc(int32_t speed);

#endif
