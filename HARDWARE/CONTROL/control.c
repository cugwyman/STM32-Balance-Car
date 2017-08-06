#include "control.h"

float pitch, roll, yaw; 		
short groyx, gyroy, gyroz;
int speed;
int16_t state;//方向偏差
int32_t ac_pwm, vc_pwm, dc_pwm, left_pwm, right_pwm;
#ifdef DYNAMIC_DC_PID
float DC_PID_P;
#endif

/***
 *@brief 获取PWM
 *       由timer.c的定时中断调用
 ***/
void get_pwm(void)
{
    get_mpu();
    speed = get_speed();
    ac_pwm = angle_proc();
    vc_pwm = velocity_proc(speed);
    dc_pwm = direction_proc(speed);
    left_pwm = ac_pwm - vc_pwm + dc_pwm;
    right_pwm = ac_pwm - vc_pwm - dc_pwm;
}

/***
 *@brief 获取姿态解算数据
 *       已修正零点
 ***/
void get_mpu(void)
{
//    float pitch_temp, roll_temp, yaw_temp; 	
//    short gyrox_temp, gyroy_temp, gyroz_temp;	

//    while
        (mpu_dmp_get_data(&pitch, &roll, &yaw));
    {
//        printf("DMPREADunsucceed\n");
    }
    MPU_Get_Gyroscope(&groyx, &gyroy, &gyroz);	//得到陀螺仪数据
//    pitch = pitch_temp - pitch_zero;
//    gyroy = gyroy_temp - gyroy_zero;
//    gyroz = gyroz_temp - gyroz_zero;
}

/***
 *@brief 获取编码器数据
 *       已修正零点
 ***/
int get_speed(void)
{
    int leftSpeed, rightSpeed;
    leftSpeed = TIM2_Encoder_Read();//读计数TIM2个数,存放到leftSpeed
    rightSpeed = TIM4_Encoder_Read();//读计数TIM4个数,存放到rightSpeed
    TIM2_Encoder_Write(0);//TIM2计数寄存器赋0
	TIM4_Encoder_Write(0);//TIM4计数寄存器赋0
	return (abs(leftSpeed) + abs(rightSpeed)) / 2;
}

/**
 * @brief  标准电机输出, 做了溢出处理和符号处理
 * @param[in]  LEFT_MOTOR_OUT  左电机输出, 符号决定正倒转
 * \param[in]  RIGHT_MOTOR_OUT 右电机输出, 符号决定正倒转
 */
void motor_proc(int32_t LEFT_MOTOR_OUT, int32_t RIGHT_MOTOR_OUT) 
{
    if( LEFT_MOTOR_OUT > MOTOR_OUT_MAX ){
        LEFT_MOTOR_OUT = MOTOR_OUT_MAX;
    }
    else if( LEFT_MOTOR_OUT < -MOTOR_OUT_MAX ){
        LEFT_MOTOR_OUT = -MOTOR_OUT_MAX;
    }
    
    if( RIGHT_MOTOR_OUT > MOTOR_OUT_MAX ){
        RIGHT_MOTOR_OUT = MOTOR_OUT_MAX;
    }
    else if( RIGHT_MOTOR_OUT < -MOTOR_OUT_MAX ){
        RIGHT_MOTOR_OUT = -MOTOR_OUT_MAX;
    }
    
    if( LEFT_MOTOR_OUT >= 0 ){
		GPIO_ResetBits(GPIOC, GPIO_Pin_6);
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
        TIM_SetCompare1(TIM3,left_pwm);		//tm3 ch1
    }
    else{
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
		GPIO_SetBits(GPIOC, GPIO_Pin_6);
        TIM_SetCompare1(TIM3,-left_pwm);	//tm3 ch1
    }
    
    if( RIGHT_MOTOR_OUT >= 0 ){
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
        TIM_SetCompare2(TIM3,right_pwm);    //tm3 ch2
    }
    else{
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
        TIM_SetCompare2(TIM3,-right_pwm);    //tm3 ch2
    }
}

/***
 *@brief 角度环PID
 *       P为角度偏差
 *       D为陀螺仪y轴测量数据
 ***/

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

/***
 *@brief 速度环PID
 *       增量式
 ***/

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

/***
 *@brief 方向环PID
 *       P为方向偏差
 *       D为陀螺仪z轴测量数据
 ***/

static int32_t direction_PID(float DC_PID_P, float DC_PID_D) 
{
    int32_t P, D;
    int32_t incpid;

//    state = DirectionErrorGet(resultSet.middleLine,IMG_COL / 2);
    state = get_ir_dir_error(ST188DATA);
    
    P = DC_PID_P * state / 25 ;
    D = DC_PID_D * gyroz / 100;
    
    incpid = P + D;
    
    return incpid;
}

/***
 *@brief  角度环process
 *@retval 角度环输出PWM
 ***/

int32_t angle_proc(void)
{
    return -angle_PID(AC_Set, pitch);
}

/***
 *@brief  速度环process
 *@retval 速度环输出PWM
 ***/

int32_t velocity_proc(int32_t speed) 
{
    static uint8_t count = 0;
    static int32_t VC_Out_Old = 0, VC_Out_New = 0;
    int32_t VC_Out;
    
    if( count >= VC_PERIOD )
    {
        count = 0;
        VC_Out_Old = VC_Out_New;
        VC_Out_New = velocity_PID(MODE.VC_Set, speed);
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

/***
 *@brief  方向环process
 *@param[in]  DC_PID_P 根据速度计算的动态P
 *@retval 方向环输出PWM
 ***/

int32_t direction_proc(int32_t speed)
{
    static uint8_t count = 0;
    static int16_t pregyroz = 0;
    static int32_t DC_Out_Old = 0, DC_Out_New = 0;
    int32_t DC_Out;
    
    gyroz = gyroz * 0.9 + pregyroz * 0.1;
    pregyroz = gyroz;
    if( count >= DC_PERIOD )
    {
        count = 0;
        DC_Out_Old = DC_Out_New;

                
        #ifdef DYNAMIC_DC_PID
        DC_PID_P = MODE.DC_PID_P_COEF * speed ;
        if( DC_PID_P > MODE.DC_P_MAX )
        {
            DC_PID_P = MODE.DC_P_MAX;
        }
        else if( DC_PID_P < MODE.DC_P_MIN )
        {
            DC_PID_P = MODE.DC_P_MIN;
        }
        #endif
                
        DC_Out_New = direction_PID(DC_PID_P, MODE.DC_PID_D);
            
        if( DC_Out_New > MODE.DC_Out_MAX )
        {
            DC_Out_New = MODE.DC_Out_MAX;
        }
        else if( DC_Out_New < -MODE.DC_Out_MAX )
        {
            DC_Out_New = -MODE.DC_Out_MAX;
        }
    }
    count++;

    DC_Out = DC_Out_Old + (DC_Out_New - DC_Out_Old) * count / DC_PERIOD;
    
    return DC_Out;
}
