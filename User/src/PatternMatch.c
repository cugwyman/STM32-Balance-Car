#include "PatternMatch.h"
#include "ImgUtility.h"
#include "ImgProc.h"
#include "Motor.h"
#include "stdio.h"
#include "uart.h"
#include "gpio.h"
#include "Velocity.h"

static inline float Abs(float);
static inline float Min(float, float);
static inline float Max(float, float);
static inline bool OpstSign(int16_t, int16_t);
static inline bool InRange(int16_t value, int16_t lbound, int16_t hbound);



inline float Abs(float input) 
{
    return input >= 0 ? input : -input;
}

inline float Min(float a, float b) 
{
    return a > b ? b : a;
}

inline float Max(float a, float b) 
{
    return a > b ? a : b;
}

inline bool OpstSign(int16_t a, int16_t b) 
{
    return (a & 0x8000) ^ (b & 0x8000);
}

inline bool InRange(int16_t value, int16_t lbound, int16_t hbound) 
{
    return value > lbound && value < hbound;
}
