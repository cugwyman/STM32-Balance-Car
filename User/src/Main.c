/*
 *      NXP Up-Right Car V5.0
 *  CUG ³Ë·ç¶Ó wyman  liulu  sun
 */
#include "MainProc.h"
#include "DataComm.h"
#include "uart.h"
#include "ImgUtility.h"
#include "gpio.h"
#include "Joystick.h"

int main(void)
{
    MainInit();
    while(1) {
//        JoystickInt();
//        BUZZLE_OFF;
        ImgTrans(&resultSet);
//        StateTrans(Angle_Kalman , angleSpeedIntegral , angleSpeed , angle);
//        printf("%d\t  ring = %d\t    AC = %d\t      VC = %d\t    DC = %d\t    state = %d\t    Right = %d\t    speed = %d\t   angle = %f\n",resultSet.imgProcFlag, ringDistance, AC_Out, VC_Out, DC_Out,  state, Right_Out, speed, Angle_Kalman);
//        printf("%d\n", (int)Angle_Kalman);
        DelayMs(20);
//        Oled_PrintfPhoto1(imgBuf);
	}
}

