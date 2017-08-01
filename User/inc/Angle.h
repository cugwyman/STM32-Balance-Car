#ifndef __ANGLE_H
#define __ANGLE_H

#include "Root.h"
#include "CollectData.h"

#define PI 3.14159265

#define Q_angle     0.001 //Ω«∂»‘Î…˘
#define Q_gyro      0.003//0.0005//∆Ø“∆‘Î…˘
#define R_angle     0.5//0.05  //Ω«∂»≤‚¡ø‘Î…˘÷µ
#define C_0         1
#define dt          0.005                 //dt?kalman???????;  0.01385

extern mode MODE;

extern float Kal_Gyro;
extern float gyro;
extern int16_t mmax, mmaz;
extern float angle, angleSpeed;
extern float Angle_Kalman;
extern int16_t Pre_Angle_Kalman;
extern float angleSpeedIntegral;
extern int32_t VC_Out;
extern int8_t change;

int32_t AngleProc(void);

#endif
