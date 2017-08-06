#include "control.h"

float pitch, roll, yaw; 		
short groyx, gyroy, gyroz;
int speed;
int16_t state;//����ƫ��
int32_t ac_pwm, vc_pwm, dc_pwm, left_pwm, right_pwm;
#ifdef DYNAMIC_DC_PID
float DC_PID_P;
#endif

/***
 *@brief ��ȡPWM
 *       ��timer.c�Ķ�ʱ�жϵ���
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
 *@brief ��ȡ��̬��������
 *       ���������
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
    MPU_Get_Gyroscope(&groyx, &gyroy, &gyroz);	//�õ�����������
//    pitch = pitch_temp - pitch_zero;
//    gyroy = gyroy_temp - gyroy_zero;
//    gyroz = gyroz_temp - gyroz_zero;
}

/***
 *@brief ��ȡ����������
 *       ���������
 ***/
int get_speed(void)
{
    int leftSpeed, rightSpeed;
    leftSpeed = TIM2_Encoder_Read();//������TIM2����,��ŵ�leftSpeed
    rightSpeed = TIM4_Encoder_Read();//������TIM4����,��ŵ�rightSpeed
    TIM2_Encoder_Write(0);//TIM2�����Ĵ�����0
	TIM4_Encoder_Write(0);//TIM4�����Ĵ�����0
	return (abs(leftSpeed) + abs(rightSpeed)) / 2;
}

/**
 * @brief  ��׼������, �����������ͷ��Ŵ���
 * @param[in]  LEFT_MOTOR_OUT  �������, ���ž�������ת
 * \param[in]  RIGHT_MOTOR_OUT �ҵ�����, ���ž�������ת
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
 *@brief �ǶȻ�PID
 *       PΪ�Ƕ�ƫ��
 *       DΪ������y���������
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
 *@brief �ٶȻ�PID
 *       ����ʽ
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
 *@brief ����PID
 *       PΪ����ƫ��
 *       DΪ������z���������
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
 *@brief  �ǶȻ�process
 *@retval �ǶȻ����PWM
 ***/

int32_t angle_proc(void)
{
    return -angle_PID(AC_Set, pitch);
}

/***
 *@brief  �ٶȻ�process
 *@retval �ٶȻ����PWM
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
 *@brief  ����process
 *@param[in]  DC_PID_P �����ٶȼ���Ķ�̬P
 *@retval �������PWM
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
