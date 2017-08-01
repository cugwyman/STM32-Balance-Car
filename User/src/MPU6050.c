#include "MPU6050.h"

static int16_t Gyro_Zero;//陀螺仪零点
static int16_t DirGyro_Zero;//方向陀螺仪零点
static int16_t Accx_Zero;//x零点
static int16_t Accz_Zero;//z零点

int16_t g_Acc_xtemp = 0, g_Acc_ztemp = 0, g_Gry_ztemp = 0, g_Gry_ytemp = 0;
float  Angle = 0, Gyro_y = 0;
float  acc = 0 , gry = 0;

float   OutData[4] ={0};

//*********************************************************
//              mpu6050初始化
//*********************************************************
void mpu6050_init(void)
{
	I2C_WriteSingleRegister(HW_I2C0, 0x68, PWR_MGMT_1, 0x0);     //解除休眠状态
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, SMPLRT_DIV, 0x07); //陀螺仪采样率，1KHz
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, CONFIG, 0x06);        //低通滤波器的设置，截止频率是1K，带宽是5K
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, GYRO_CONFIG, 0x18);   //陀螺仪自检及测量范围，典型值:0x18(不自检,2000deg/s)
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, ACCEL_CONFIG, 0x00);  //配置加速度传感器工作在2G模式，不自检
	DelayMs(10);
}

//*********************************************************
//              采集初始化
//*********************************************************
void CollectInit(void)
{
	uint8_t gry_ztemp1 = 0,gry_ztemp2 = 0;
	uint8_t gry_ytemp1 = 0,gry_ytemp2 = 0;
	uint8_t acc_xtemp1 = 0,acc_xtemp2 = 0;
    uint8_t acc_ztemp1 = 0,acc_ztemp2 = 0;
	int16_t Gry_ztemp = 0, Gry_ytemp = 0;
	int16_t Acc_xtemp = 0, Acc_ztemp = 0;
    uint16_t i;
    
    Gyro_Zero = 0;
	DirGyro_Zero = 0;
    Accx_Zero = 0;
    Accz_Zero = 0;
    I2C_QuickInit(I2C0_SCL_PB02_SDA_PB03,100*1000);
    GPIO_QuickInit(HW_GPIOB, 1, kGPIO_Mode_OOD);
    PBout(1) = 0;
    mpu6050_init();
	DelayMs(1);
    for(i = 0; i < GYRO_ZERO_SAMPLE; ++i)//均值滤波，取1ms内均值
    {
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x47, &gry_ztemp1);       //读取高八位
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x48, &gry_ztemp2);     //读取低八位
		Gry_ztemp = ((int16_t)gry_ztemp1<<8) + (int16_t)gry_ztemp2;
		DirGyro_Zero += Gry_ztemp;
        
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x45, &gry_ytemp1);       //读取高八位
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x46, &gry_ytemp2);     //读取低八位
		Gry_ytemp = ((int16_t)gry_ytemp1<<8) + (int16_t)gry_ytemp2;
		Gyro_Zero += Gry_ytemp;
        
        I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3B, &acc_xtemp1);       //读取高八位
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3C, &acc_xtemp2);     //读取低八位
		Acc_xtemp = ((int16_t)acc_xtemp1<<8) + (int16_t)acc_xtemp2;
		Accx_Zero += Acc_xtemp;
	
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3F, &acc_ztemp1);       //读取高八位
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x40, &acc_ztemp2);     //读取低八位
		Acc_ztemp = ((int16_t)acc_ztemp1<<8) + (int16_t)acc_ztemp2;
		Accz_Zero += Acc_ztemp;

        if(i > 0)
        {
            Gyro_Zero /= 2;
            DirGyro_Zero /= 2;
            Accx_Zero /= 2;
            Accz_Zero /= 2;
        }
		DelayMs(1);
    }
}

//*********************************************************
//             读取6050数值并求平均值 
//*********************************************************
void Read_Acc_Gry(void)
{
	uint8_t acc_xtemp1 = 0,acc_xtemp2 = 0;
    uint8_t acc_ztemp1 = 0,acc_ztemp2 = 0;
	uint8_t gry_ztemp1 = 0,gry_ztemp2 = 0;//方向陀螺仪
	uint8_t gry_ytemp1 = 0,gry_ytemp2 = 0;//角度陀螺仪

    I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3B, &acc_xtemp1);     //读取高八位
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3C, &acc_xtemp2);     //读取低八位
	g_Acc_xtemp = ((int16_t)acc_xtemp1<<8) + (int16_t)acc_xtemp2;
	
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3F, &acc_ztemp1);     //读取高八位
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x40, &acc_ztemp2);     //读取低八位
	g_Acc_ztemp = ((int16_t)acc_ztemp1<<8) + (int16_t)acc_ztemp2;

	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x47, &gry_ztemp1);     //读取高八位
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x48, &gry_ztemp2);     //读取低八位
	g_Gry_ztemp = ((int16_t)gry_ztemp1<<8) + (int16_t)gry_ztemp2;
    
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x45, &gry_ytemp1);     //读取高八位
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x46, &gry_ytemp2);     //读取低八位
	g_Gry_ytemp = ((int16_t)gry_ytemp1<<8) + (int16_t)gry_ytemp2;
}

/**
 * @brief  陀螺仪采集, 用于直立环控制(需经过滤波)
 * @retval 陀螺仪采集(已去零点)
 */
int16_t GyroGet(void) {
	return g_Gry_ytemp - Gyro_Zero;
}

/**
 * @brief  方向陀螺仪采集, 用于方向环控制
 * @retval 方向陀螺仪采集(已去零点)
 */
int16_t DirGyroGet(void) {
    return g_Gry_ztemp - DirGyro_Zero;
}

/**
 * @brief  加速度计采集, 用于直立环控制(需经过滤波)
 * @param[in]  mmax 加速度计X轴采集, 由指针取走
 * \param[in]  mmaz 加速度计Z轴采集, 由指针取走
 */
void AcceGet(int16_t* mmax, int16_t* mmaz) {
    *mmax = g_Acc_xtemp - Accx_Zero;
    *mmaz = g_Acc_ztemp - Accz_Zero;
}
