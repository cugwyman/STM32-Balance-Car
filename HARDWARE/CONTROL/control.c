#include "control.h"

float pitch; 		
short gyroy, gyroz;	

void get_data(void)
{
    float pitch_temp=0, roll_temp=0, yaw_temp=0; 		//欧拉角零点
    short gyrox_temp=0, gyroy_temp=0, gyroz_temp=0;	//陀螺仪零点

    mpu_dmp_get_data(&pitch_temp, &roll_temp, &yaw_temp);
    MPU_Get_Gyroscope(&gyrox_temp, &gyroy_temp, &gyroz_temp);	//得到陀螺仪数据
    pitch = pitch_temp - pitch_zero;
    gyroy = gyroy_temp - gyroy_zero;
    gyroz = gyroz_temp - gyroz_zero;
}

static int32_t angle_PID(float set, float nextPoint)
{ 
    float error;
    float P, D;
    int32_t incpid;
    
    error = set - nextPoint;
    P = AC_PID_P * error;
    D = AC_PID_D * gyroy;
    
//    lastError = error;
    
    incpid = P - D;
    
    return incpid;
}

static int32_t velocity_PID(int32_t set, int32_t nextpoint) 
{
	float error;
    static float lastError = 0, prevError = 0;
	float P, I, D;
	static int32_t incpid = 0;

	error = set - nextpoint;
	P = VC_PID_P * ( error - lastError );
	I = VC_PID_I * error;
	D = VC_PID_D * ( error - 2 * lastError + prevError );
    if(I > 10)
        I = 0;
    if(I < -10)
        I = 0;
	prevError = lastError;
	lastError = error;
	 
	incpid += P + I + D;
	 
	return incpid;
}

int32_t angle_proc(void)
{
    return -angle_PID(AC_Set, pitch);
}

int32_t velocity_proc(int32_t speed) 
{
    static uint8_t count = 0;
    static int32_t VC_Out_Old = 0, VC_Out_New = 0;
    int32_t VC_Out;
    
    if( count >= VC_PERIOD )
    {
        count = 0;
        VC_Out_Old = VC_Out_New;
        VC_Out_New = velocity_PID(VC_Set, speed);
//        VC_Out_New = VelocityPID(30, speed);        
        if( VC_Out_New > VC_Out_MAX )
            VC_Out_New = VC_Out_MAX;
        else if( VC_Out_New < -VC_Out_MAX )
            VC_Out_New = -VC_Out_MAX;
    }
    count++;
    
    VC_Out = VC_Out_Old + (VC_Out_New - VC_Out_Old) * count / VC_PERIOD;
    return VC_Out;
}
