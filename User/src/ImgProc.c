#include "ImgProc.h"
#include "gpio.h"
#include "DirectionControl.h"
#include "SpeedControl.h"
#include "ImgUtility.h"
#include "DataComm.h"
#include "uart.h"
#include "Velocity.h"
#include "Angle.h"
#include "BorderSearchRelative.h"
extern mode MODE;

#ifdef USE_BMP
byte imgBuf[IMG_ROW][1 + IMG_COL / 8]; // Important extra 1 byte against overflow
#else
byte imgBuf[IMG_ROW][IMG_COL];
#endif

extern bool start_deal;
bool onRamp;
int32_t rampDistance;

int16_t dirError;
bool direction_control_on;
img_proc_struct resultSet;

static uint8_t imgBufRow = 0;
static uint8_t imgRealRow = 0;
static int16_t searchForBordersStartIndex = IMG_COL / 2;

static int16_t GetPresight(int32_t speed, int16_t VC_Set, float offset);
static void ImgProcHREF(uint32_t pinxArray);
static void ImgProcVSYN(uint32_t pinxArray);
static void ImgProc0(void);
static void ImgProc1(void);
static void ImgProc2(void);
static void ImgProc3(void);
static void ImgProcSummary(void);

static img_proc_type_array imgProc = { ImgProc0, ImgProc1, ImgProc2 ,ImgProc3 };

#ifdef USE_BMP
inline void SetImgBufAsBitMap(int16_t row, int16_t col) 
{
    imgBuf[row][col >> SHIFT] |= (1 << (col & MASK));
}

inline void ClrImgBufAsBitMap(int16_t row, int16_t col) 
{
    imgBuf[row][col >> SHIFT] &= ~(1 << (col & MASK));
}

inline bool TstImgBufAsBitMap(int16_t row, int16_t col) 
{
    return imgBuf[row][col >> SHIFT] & (1 << (col & MASK));
}
#endif

void ImgProcInit(void) 
{
    GPIO_QuickInit(CAMERA_HREF_PORT, CAMERA_HREF_PIN, kGPIO_Mode_IPU);
    GPIO_QuickInit(CAMERA_VSYN_PORT, CAMERA_VSYN_PIN, kGPIO_Mode_IPU);
    GPIO_CallbackInstall(CAMERA_HREF_PORT, ImgProcHREF);
    GPIO_CallbackInstall(CAMERA_VSYN_PORT, ImgProcVSYN);
    GPIO_ITDMAConfig(CAMERA_HREF_PORT, CAMERA_HREF_PIN, kGPIO_IT_RisingEdge, DISABLE);
    GPIO_ITDMAConfig(CAMERA_VSYN_PORT, CAMERA_VSYN_PIN, kGPIO_IT_RisingEdge, DISABLE);
    
    GPIO_QuickInit(CAMERA_DATA_PORT, CAMERA_DATA_PIN, kGPIO_Mode_IPU);
	GPIO_QuickInit(CAMERA_ODEV_PORT, CAMERA_ODEV_PIN, kGPIO_Mode_IPU);
}

void ImgProcHREF(uint32_t pinxArray) 
{
    if(imgBufRow < IMG_ROW && imgRealRow > IMG_ABDN_ROW)
    {
        imgProc[imgRealRow % IMG_ROW_INTV]();
    }
    imgRealRow++;
}

void ImgProcVSYN(uint32_t pinxArray) 
{
    ImgProcSummary();
    imgRealRow = 0;
    imgBufRow = 0;
    resultSet.leftBorderNotFoundCnt = 0;
    resultSet.rightBorderNotFoundCnt = 0;
    searchForBordersStartIndex = IMG_COL / 2;
}

void ImgProc0() 
{
    int16_t i;
    for(i = 0; i <= IMG_READ_DELAY; i++) { } //ignore points near the border
    #ifdef USE_BMP
        static byte tmpBuf[IMG_COL]; //cache
        for(i = IMG_COL - 1; i >= 0; i--)
        {
            tmpBuf[i] = CAMERA_DATA_READ;
            __ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");
            __ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");
        }
        for(i = IMG_COL - 1; i >= 0; i--) 
        {
            if(tmpBuf[i])
                SetImgBufAsBitMap(imgBufRow, i);
            else
                ClrImgBufAsBitMap(imgBufRow, i);
        }
    #else
        for(i = IMG_COL - 1; i >= 0; i--) 
        {
            imgBuf[imgBufRow][i] = CAMERA_DATA_READ;
        }
    #endif
}

void ImgProc1() 
{
Bordersearch(imgBufRow);
}

void ImgProc2() 
{

}

void ImgProc3()
{
    imgBufRow++;
}

void ImgProcSummary()
{
 
    
}
/*角度动态前瞻
int16_t GetPresight(int16_t angle, int8_t mid, int8_t offset) {
    return angle < mid-4*offset ? -4 : angle < mid-3*offset ? -3 : angle < mid-2*offset ? -2 : angle < mid-offset ? -1 : angle < mid ? 0 :
        angle < mid+offset ? 1 : angle < mid+2*offset ? 2 : angle < mid+2*offset ? 3 : 4;
}*/
/*速度动态前瞻*/
int16_t GetPresight(int32_t speed, int16_t VC_Set, float offset) {
    return speed < VC_Set-4*offset ? -3 : speed < VC_Set-3*offset ?  -2 : speed < VC_Set-2*offset ? -1 : 
           speed < VC_Set+3*offset ?  0 : speed < VC_Set+5.5*offset ? 1 : 2;
}
