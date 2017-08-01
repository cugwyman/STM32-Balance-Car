#include "MainProc.h"
#include "ImgUtility.h"
#include "pit.h"
#include "stdlib.h"
#include "gpio.h"
#include "stdarg.h"
#include "stdio.h"
#include "oledbase.h"
#include "Joystick.h"

int32_t AC_Out;
int32_t VC_Out;
int32_t DC_Out;
bool speed_up_down;
int32_t Left_Out, Right_Out;
float distance;
float time;
int8_t change;
bool start_deal = true;
bool barrier_deal = true;
int32_t speed;
int32_t preSpeed;

static void NVICInit(void);
static void BuzzleInit(void);
static void TimerInit(void);
static void MainProc(void);

void MainInit() 
{
    DelayInit();
    DelayMs(1000);
    GearInit();    
    MotorInit();   
    CollectInit(); 
    EncoderInit();       
    DataCommInit();
//	Oled_Init_n();
//	JoystickInit();
//  BuzzleInit();
    NVICInit(); 
    ImgProcInit();     
    TimerInit();

    PIT_ITDMAConfig(PIT_CHL, kPIT_IT_TOF, ENABLE);
    GPIO_ITDMAConfig(CAMERA_HREF_PORT, CAMERA_HREF_PIN, kGPIO_IT_RisingEdge, ENABLE );
    GPIO_ITDMAConfig(CAMERA_VSYN_PORT, CAMERA_VSYN_PIN, kGPIO_IT_RisingEdge, ENABLE );
}

void NVICInit() 
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
    NVIC_SetPriority(HREF_IRQ, NVIC_EncodePriority(NVIC_PriorityGroup_2, 0, 0));
    NVIC_SetPriority(VSYN_IRQ, NVIC_EncodePriority(NVIC_PriorityGroup_2, 0, 1));
    NVIC_SetPriority(TIMR_IRQ, NVIC_EncodePriority(NVIC_PriorityGroup_2, 1, 0));
}

void BuzzleInit() 
{
    GPIO_QuickInit(BUZZLE_PORT, BUZZLE_PIN, kGPIO_Mode_OPP);//OPPø…œÏ
	BUZZLE_OFF;
}

void TimerInit() 
{
    PIT_QuickInit(PIT_CHL, PIT_PRD);
    PIT_CallbackInstall(PIT_CHL, MainProc);
    PIT_ITDMAConfig(PIT_CHL, kPIT_IT_TOF, DISABLE);
}

void OLEDPrintf(uint8_t x, uint8_t y, char *str, ...) {
    static char buf[255];
    va_list ap;
    va_start(ap, str);
    
    vsprintf(buf, str, ap);
    OLED_DispStr(x,y,buf,&tFont12);
}

void OLEDClrRow(uint8_t row) {
    // 21 spaces
    OLEDPrintf(0, row, "                     ");
}

void MainProc()
{
	static int16_t ring_time = 0;
    time += 0.005;
    static int32_t count = 0;

    if(start_deal)
    {
        if(time < 0.05)
        {
            MODE.VC_Set = 0;
            MODE.AC_Set = 0;
        }
        else if(time >= 0.05 )
        {
            MODE.VC_Set = VC_Set;
            MODE.AC_Set = AC_Set;
            #ifdef TEST_MODE
            if(time >= 0.1)
            #endif
            #ifndef TEST_MODE
            if(time >= 8)
            #endif
                start_deal = false;
        }
    }
    
    Read_Acc_Gry();
    
    #ifdef SLOW_DOWN
	{
//		if( resultSet.imgProcFlag == STRAIGHT_ROAD ) 
//		{
//				if(MODE.VC_Set < VC_Max) 
//				{
//						MODE.VC_Set++;
//				} 
//				else if(MODE.VC_Set > VC_Max) 
//				{
//						MODE.VC_Set--;
//				}
//		} else
		if( resultSet.imgProcFlag == CIRCLE || inRing) //  aroundBarrier || onRamp || RINGEND ||
		{
            if(rampDistance > 88000) {
                rampDistance = 0;
                onRamp = false;
            }
				if(MODE.VC_Set > VC_Min) 
				{
						MODE.VC_Set-=2;
				} 
				else if(MODE.VC_Set < VC_Min) 
				{
						MODE.VC_Set++;
				}
		}
		else
		{
				if(MODE.VC_Set > VC_Set) 
				{
						MODE.VC_Set--;
				} 
				else if(MODE.VC_Set < VC_Set) 
				{
						MODE.VC_Set++;
				}
		}
    }
    #endif

    #if defined(VC) || defined(DC)
    speed = EncoderGet();
    change = (speed - preSpeed);
    preSpeed = speed;
//	int16_t dist = speed *3;
//    if(inRing || ringEndDelay || ringInterval)
//        ringDistance += dist;
//    if(inCrossRoad)
//        crossRoadDistance += dist;
//    if(aroundBarrier)
//        barrierDistance += dist;
//    if(onRamp)
//        rampDistance += dist;
//    if(barrier_deal)
//    {
//        barrierDealDistance += dist;
//        if(barrierDealDistance >= 100000)
//            barrier_deal = false;
//    }
    #endif
    #ifdef VC
    VC_Out = VelocityProc(speed);
    #endif
    #ifdef AC
    AC_Out = AngleProc();
    if(AC_Out > AC_Out_MAX)
        AC_Out = AC_Out_MAX;
    if(AC_Out < -AC_Out_MAX)
        AC_Out = -AC_Out_MAX;            
    #endif
    #ifdef DC
    DC_Out = DirectionProc(speed);
    #endif
    
    Left_Out = AC_Out - VC_Out + DC_Out;
    Right_Out = AC_Out - VC_Out - DC_Out;
    MotorOut(Left_Out, Right_Out);
}

