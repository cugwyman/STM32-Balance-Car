#include "MPU6050.h"

static int16_t Gyro_Zero;//���������
static int16_t DirGyro_Zero;//�������������
static int16_t Accx_Zero;//x���
static int16_t Accz_Zero;//z���

int16_t g_Acc_xtemp = 0, g_Acc_ztemp = 0, g_Gry_ztemp = 0, g_Gry_ytemp = 0;
float  Angle = 0, Gyro_y = 0;
float  acc = 0 , gry = 0;

float   OutData[4] ={0};

//*********************************************************
//              mpu6050��ʼ��
//*********************************************************
void mpu6050_init(void)
{
	I2C_WriteSingleRegister(HW_I2C0, 0x68, PWR_MGMT_1, 0x0);     //�������״̬
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, SMPLRT_DIV, 0x07); //�����ǲ����ʣ�1KHz
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, CONFIG, 0x06);        //��ͨ�˲��������ã���ֹƵ����1K��������5K
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, GYRO_CONFIG, 0x18);   //�������Լ켰������Χ������ֵ:0x18(���Լ�,2000deg/s)
	DelayMs(10);
	I2C_WriteSingleRegister(HW_I2C0, 0x68, ACCEL_CONFIG, 0x00);  //���ü��ٶȴ�����������2Gģʽ�����Լ�
	DelayMs(10);
}

//*********************************************************
//              �ɼ���ʼ��
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
    for(i = 0; i < GYRO_ZERO_SAMPLE; ++i)//��ֵ�˲���ȡ1ms�ھ�ֵ
    {
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x47, &gry_ztemp1);       //��ȡ�߰�λ
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x48, &gry_ztemp2);     //��ȡ�Ͱ�λ
		Gry_ztemp = ((int16_t)gry_ztemp1<<8) + (int16_t)gry_ztemp2;
		DirGyro_Zero += Gry_ztemp;
        
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x45, &gry_ytemp1);       //��ȡ�߰�λ
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x46, &gry_ytemp2);     //��ȡ�Ͱ�λ
		Gry_ytemp = ((int16_t)gry_ytemp1<<8) + (int16_t)gry_ytemp2;
		Gyro_Zero += Gry_ytemp;
        
        I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3B, &acc_xtemp1);       //��ȡ�߰�λ
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3C, &acc_xtemp2);     //��ȡ�Ͱ�λ
		Acc_xtemp = ((int16_t)acc_xtemp1<<8) + (int16_t)acc_xtemp2;
		Accx_Zero += Acc_xtemp;
	
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3F, &acc_ztemp1);       //��ȡ�߰�λ
		I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x40, &acc_ztemp2);     //��ȡ�Ͱ�λ
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
//             ��ȡ6050��ֵ����ƽ��ֵ 
//*********************************************************
void Read_Acc_Gry(void)
{
	uint8_t acc_xtemp1 = 0,acc_xtemp2 = 0;
    uint8_t acc_ztemp1 = 0,acc_ztemp2 = 0;
	uint8_t gry_ztemp1 = 0,gry_ztemp2 = 0;//����������
	uint8_t gry_ytemp1 = 0,gry_ytemp2 = 0;//�Ƕ�������

    I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3B, &acc_xtemp1);     //��ȡ�߰�λ
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3C, &acc_xtemp2);     //��ȡ�Ͱ�λ
	g_Acc_xtemp = ((int16_t)acc_xtemp1<<8) + (int16_t)acc_xtemp2;
	
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x3F, &acc_ztemp1);     //��ȡ�߰�λ
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x40, &acc_ztemp2);     //��ȡ�Ͱ�λ
	g_Acc_ztemp = ((int16_t)acc_ztemp1<<8) + (int16_t)acc_ztemp2;

	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x47, &gry_ztemp1);     //��ȡ�߰�λ
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x48, &gry_ztemp2);     //��ȡ�Ͱ�λ
	g_Gry_ztemp = ((int16_t)gry_ztemp1<<8) + (int16_t)gry_ztemp2;
    
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x45, &gry_ytemp1);     //��ȡ�߰�λ
	I2C_ReadSingleRegister(HW_I2C0, 0x68, 0x46, &gry_ytemp2);     //��ȡ�Ͱ�λ
	g_Gry_ytemp = ((int16_t)gry_ytemp1<<8) + (int16_t)gry_ytemp2;
}

/**
 * @brief  �����ǲɼ�, ����ֱ��������(�辭���˲�)
 * @retval �����ǲɼ�(��ȥ���)
 */
int16_t GyroGet(void) {
	return g_Gry_ytemp - Gyro_Zero;
}

/**
 * @brief  ���������ǲɼ�, ���ڷ��򻷿���
 * @retval ���������ǲɼ�(��ȥ���)
 */
int16_t DirGyroGet(void) {
    return g_Gry_ztemp - DirGyro_Zero;
}

/**
 * @brief  ���ٶȼƲɼ�, ����ֱ��������(�辭���˲�)
 * @param[in]  mmax ���ٶȼ�X��ɼ�, ��ָ��ȡ��
 * \param[in]  mmaz ���ٶȼ�Z��ɼ�, ��ָ��ȡ��
 */
void AcceGet(int16_t* mmax, int16_t* mmaz) {
    *mmax = g_Acc_xtemp - Accx_Zero;
    *mmaz = g_Acc_ztemp - Accz_Zero;
}
