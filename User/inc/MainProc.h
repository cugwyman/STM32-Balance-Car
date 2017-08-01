#ifndef _MAINPROC_H
#define _MAINPROC_H

#include "root.h"

#include "Motor.h"
#include "Encoder.h"
#include "DataComm.h"
#include "ImgProc.h"
#include "DirectionControl.h"
//#include "ModeSwitch.h"

#include "CollectData.h"
#include "Angle.h"
#include "Velocity.h"
#include "Direction.h"
#include "OLED.h"
#include "Fuzzy.h"
#include "MPU6050.h"

extern int32_t AC_Out;
extern int32_t VC_Out;
extern int32_t DC_Out;
extern bool speed_up_down;
extern int32_t Left_Out, Right_Out;
extern float distance;
extern float time;

//#if defined(SINGLE_VC) || defined(VC) || defined(DC)
extern int32_t speed;
extern int32_t preSpeed;

//#endif

void MainInit(void);
void OLEDPrintf(uint8_t x, uint8_t y, char *str, ...);
void OLEDClrRow(uint8_t row);

#endif
