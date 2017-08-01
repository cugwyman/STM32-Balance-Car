#ifndef _PARAM_H
#define _PARAM_H

//Angle
#define AC_Out_MAX           8000

#define Kalman_Sample_Time   0.005
#define AC_PID_P             300
#define AC_PID_D             36
#define GYRO_ZERO_SAMPLE     1000

/* Speed */
#define VC_PID_P             50
#define VC_PID_I             0
#define VC_PID_D             10
#define VC_Out_MAX           5000
#define VC_PERIOD            4

/* Direction */
#define DC_PERIOD            2

/* Motor */
#define MOTOR_OUT_MAX     7800
#define FIX_OUT           0

//NVIC
#define  HREF_IRQ  PORTD_IRQn
#define  VSYN_IRQ  PORTC_IRQn
#define  TIMR_IRQ  PIT0_IRQn

//PIT
#define  PIT_CHL  HW_PIT_CH0
#define  PIT_PRD  5000

//Camera
#define  IMG_ABDN_ROW    50
#define  IMG_ROW_INTV    4
#define  IMG_READ_DELAY  114 //170 for 8 nops

//Image Proc Bit Map Relative
/* byte is 8 (2^3) bits */
#define  SHIFT  3
/* make the after-shifted bit no more than 1 << 0x07 */
#define  MASK   0x07

#define  IMG_ROW    50
#define  IMG_COL    225
#define  WHITE_VAL  0
#define  IMG_WHITE  0xfe
#define  IMG_BLACK  0x00
#define  IMG_EOF    0xff

//Image Proc Flag
#define  STRAIGHT_ROAD  1
#define  CROSS_ROAD     2
#define  CIRCLE         3
#define  LEFTCURVE      4
#define  RIGHTCURVE     5
#define  RINGEND        6
#define  RAMP           7
#define  BARRIER        8

#define Left true
#define Right false

#endif
