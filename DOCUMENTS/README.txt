Technical Documentation by Wyman

NXP Up-Right Car

NXP光电直立平衡车技术文档

一、目的：
	用于恩智浦智能车竞赛

二、环境：  
	MCU：K60 Cortex-M4
	Camera：SONY CCD
	Gyro：ENC-03
	Acce：MMA7361
	Model：E
	Encoder：512
	Bluetooth
	Motor Driver：Piao's PCB
	Others: Piao's PCB

三、命名规则：
	1.函数名用大写首字母的驼峰命名法(没有下划线，下同)；
	2.变量名用小写首字母的驼峰命名法；
	3.宏定义用由下划线隔开的大写单词拼接；
	4.用到库的函数名字不改，方便他人移植。

V0.1 2017.2.16 by Wyman

一、添加的文件：
	devices：
	VisualScope.c	VisualScope.h
	ssd1306.c	ssd1306.h
	
	user:
	main.c
	System.c	System.h
	CollectData.c	CollectData.h
	Motor.c		Motor.h
	Encoder.c	Encoder.h
	Angle.c		Angle.h
	Velocity.c	Velocity.h
	Direction.c	Direction.h
	ImgProc.c	ImgProc.h
	TrackIdentify.c	TrackIdentify.h
	Display.c	Display.h
	Uarts.c		Uarts.h

	documents
	PinMap.h
	Param.h
	ReadMe.txt

二、添加的变量和函数:

1. devices

VisualScope:
void VisualScope_Output(float data1 ,float data2 ,float data3 ,float data4);
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);

ssd1306:
void ssd1306_init(void);
void OLED_Fill(unsigned char dat);
void OLED_Enable(void);
void OLED_Disable(void);
void OLED_ShowStr(unsigned char x, unsigned char y, char *str);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);


2. user

System:
int32_t AC_Out;
int32_t VC_Out;
int32_t DC_Out;
int32_t Left_Out, Right_Out;
#if defined(SINGLE_VC) || defined(VC) || defined(DC)
int32_t speed;
float distance;
#endif

static void NVICInit(void);
static void TimerInit(void);
static void MainProcess(void);

void GeneralInit(void);


CollectData:
static int32_t Gyro_Zero;
static int32_t DirGyro_Zero;

void CollectInit(void);
void SensorGet(int32_t* leftSensor, int32_t* rightSensor);
int32_t MiddleSensorGet(void);
int32_t GyroGet(void);
int32_t DirGyroGet(void);
void AcceGet(int32_t* mmax, int32_t* mmaz);


Motor:
#define  MOTOR_STOP  MotorOut(0, 0)

void MotorInit(void);
void MotorOut(int16_t LEFT_MOTOR_OUT, int16_t RIGHT_MOTOR_OUT);


Encoder:
void EncoderInit(void);
int32_t EncoderGet(void);


Angle:
float Kal_Gyro;
int32_t gyro;
int32_t mmax, mmaz;
int32_t angleMma;
int32_t angle, angleSpeed;
float Angle_Kalman;
float angleSpeedIntegral;

static float KalmanFilter(float angle_kal, float angle_speed_kal);
static int32_t AnglePID(float set, float nextPoint);
int32_t AngleProc(void);


Velocity:
int VC_Set = 0;

void Gear_Get(void);
int32_t VelocityPID(int32_t set, int32_t nextpoint);
int32_t VelocityProc(int32_t speed);


Direction:
static int32_t DirectionPID(int32_t leftSensor, int32_t rightSensor, int32_t dirAngleSpeed);
int32_t DirectionProc(int32_t speed);


ImgProc:
uint8_t imgBuf[IMG_ROW][IMG_COL];
uint16_t imgProcFlag;

static uint8_t imgBufRow;
static uint8_t imgRealRow;

static void ImgProcHREF(uint32_t pinxArray);
static void ImgProcVSYN(uint32_t pinxArray);
void ImgProcInit(void);


TrackIdentify:
uint16_t MidLine[IMG_ROW];

void EdgeSearch( uint16_t n );
uint16_t CurveCal(uint16_t n);
uint16_t SlopeCal( uint16_t n);
uint16_t BlockRec(uint16_t n);
uint16_t CircleRec(uint16_t n);



Display:
void DisplayInit(void);
void DisTest(void);


Uarts:
void UartInit(void);
void ImgTrans(uint8_t imgBuf[IMG_ROW][IMG_COL]);


三、添加的宏参数：

Param.h:

/* 宏开关 */
#define AC
#define VC
//#define DC
#define xOUT_JUDGE
#define xSINGLE_VC
#define DYNAMIC_DC_PID
#define xFIX
//#define RS_JUDGE
#define xSLOW_DOWN
#define x__DEBUG__

///* 传感器采样滤波 */
//#define SENSOR_FLTR_SAMPLE  10

/* 角度环 */
#define Kalman_Sample_Time   0.0055//0.0065//0.0055
#define AC_PID_P           190.0 // 160.0
#define AC_PID_D             5.5// 5.5 //  
#define MMAX_ZERO        1956//1380//1939 //0du
#define MMAZ_ZERO        716//876 //780 
#define GYRO_ZERO_SAMPLE  1000
#define MMA_GAIN          0.073//0.232//    //0-90°，即正反车测值z-x的max减min=2000多，90/2000多得比例
#define MMA_SCALE         3.178//*1.2//send to Kalman scale, end is 0.232

/* 速度环 */
#define VC_PID_P           200.0//200.0 // 
#define VC_PID_I             0.2 //   0.25
#define VC_PID_D            50.0
#define VC_Out_MAX       25000
#define VC_PERIOD            4

/* 方向环 */
#ifdef DYNAMIC_DC_PID
#define DC_PID_P_COEF      470.0
#define DC_P_MIN          3200
#define DC_P_MAX         50000
#else  /* xDYNAMIC_DC_PID */
#define DC_PID_P         20000
#endif /* DYNAMIC_DC_PID */

#define DC_PID_D             8.0 // 10.5
#define DC_PERIOD            2

#define OUT_JUDGE_STD       50
#define TURN_FLAG	       300

/* 角度和速度设定目标 */
#define AC_Set              178//214//
#define VSET_GEAR4          90
#define VSET_GEAR3          80
#define VSET_GEAR2          70
#define VSET_GEAR1          60
#define VSET_GEAR0           0

//Camera
#define  IMG_ROW        50
#define  IMG_COL        225
#define  IMG_ABDN_ROW   19
#define  IMG_ROW_INTV   5

#define  IMG_WHITE      0xfe
#define  IMG_BLACK      0x00
#define  IMG_FRAME_FIN  0xff

#define  IMG_MIDPOINT    112

//Road Flag
#define  STRAIGHTROAD    1
#define  CURVEROAD       2
#define  LEFTCURVE       3
#define  RIGHTCURVE      4
#define  NORMALS         5
#define  OPPOSITES       6
#define  CROSSROAD       7
#define  LEFTBLOCK       8
#define  RIGHTBLOCK      9
#define  RAMP            10
#define  CIRCLE          11

/* 电机参数 */
#define MOTOR_OUT_MAX     9000
#define FIX_OUT           0

/* 发车延时 */
#define BEGIN_DELAY       4000

//NVIC
#define  HREF_IRQ  PORTD_IRQn
#define  VSYN_IRQ  PORTC_IRQn
#define  TIMR_IRQ  PIT0_IRQn

//PIT
#define  PIT_CHL  HW_PIT_CH0
#define  PIT_PRD  5000


对应引脚：

PinMap.h:

/* Motor */         
#ifdef MOTOR
#define LEFT_MOTOR_FORWARD_MAP  FTM0_CH7_PD07//PWM3
#define LEFT_MOTOR_REVERSE_MAP  FTM0_CH6_PD06//PWM4
#define RIGHT_MOTOR_FORWARD_MAP FTM0_CH5_PD05//PWM2
#define RIGHT_MOTOR_REVERSE_MAP FTM0_CH4_PD04//PWM1
#define MOTOR_PORT              HW_FTM0
#define LEFT_MOTOR_FORWARD_CHL  HW_FTM_CH7
#define LEFT_MOTOR_REVERSE_CHL  HW_FTM_CH6
#define RIGHT_MOTOR_FORWARD_CHL HW_FTM_CH5
#define RIGHT_MOTOR_REVERSE_CHL HW_FTM_CH4
#endif

/* Encoder */    //1 GND  2 3.3-5V  3 A  4 B
#ifdef ENCODER
#define LEFT_ENCODER_MAP        FTM1_QD_PHA_PA12_PHB_PA13
#define RIGHT_ENCODER_MAP       FTM2_QD_PHA_PB18_PHB_PB19
#define LEFT_ENCODER_CHL        HW_FTM1
#define RIGHT_ENCODER_CHL       HW_FTM2
#endif


/* Gyro */
#ifdef COLLECTDATA
#define GYRO_MAP                ADC1_SE9_PB1//V2
#define DIR_GYRO_MAP            ADC1_SE8_PB0//V3

/* Acce */
#define ACCE_MMAX_MAP           ADC0_SE13_PB3 
#define ACCE_MMAZ_MAP           ADC0_SE12_PB2
#endif


/* Dipswitch */
#ifdef DIPSWITCH
#define DIP_PORT                HW_GPIOC
#define DIP1_PIN                0
#define DIP2_PIN                1
#define DIP3_PIN                2
#define DIP4_PIN                3
#endif


/* LEDSwitch */
#ifdef LEDSWITCH
#define LED_PORT                HW_GPIOA
#define LED1_PIN                15
#define LED2_PIN                16
#endif

/* Uarts */

#define  DATACOMM_IMG_TRANS_MAP     UART0_RX_PB16_TX_PB17
#define  DATACOMM_IMG_TRANS_BAUD    115200
#define  DATACOMM_IMG_TRANS_CHL     HW_UART0
#define  DATACOMM_VISUALSCOPE_MAP   UART0_RX_PB16_TX_PB17
#define  DATACOMM_VISUALSCOPE_BAUD  115200
#define  DATACOMM_VISUALSCOPE_CHL   HW_UART0

/* Camera */
#ifdef IMGPROC
#define  CAMERA_HREF_PORT  HW_GPIOD
#define  CAMERA_HREF_PIN   1
#define  CAMERA_VSYN_PORT  HW_GPIOC
#define  CAMERA_VSYN_PIN   18
#define  CAMERA_DATA_PORT  HW_GPIOC
#define  CAMERA_DATA_PIN   17
#define  CAMERA_ODEV_PORT  HW_GPIOD
#define  CAMERA_ODEV_PIN   0
#define  CAMERA_DATA_READ  PCin(17)
#endif

/* Buzzer */
#ifdef BUZZER
#define BUZ_PORT                HW_GPIOB
#define BUZ_PIN                 21
#endif

/* IR */
#ifdef IR
#define BUZ_PORT                HW_GPIOE
#define BUZ_PIN                 24
#endif


Uarts.c:

UART_QuickInit(UART0_RX_PB16_TX_PB17, 115200);

Display.c:

I2C_QuickInit(I2C1_SCL_PE01_SDA_PE00,100*1000);




V0.2 2017.2.17 by Wyman

一、添加的文件：
	devices：    
    LQ12864.c   LQ12864.h
    
二、删除的文件：
	devices：    
    ssd1306.c   ssd1306.h
    
    drivers:
    cpuidy.c    cpuidy.h
    
三、修改的文件：
    user：
    Display.c
    
    
    
V0.3 2017.2.18 by Wyman

一、添加的变量和函数
    user:
    Direction.c
    
    int32_t dirGyro;
    int32_t dirAngleSpeed;
    float dirAngleSpeedIntegral;

    dirGyro = DirGyroGet();
    dirAngleSpeed = -dirGyro;
    dirAngleSpeedIntegral += dirAngleSpeed * 0.0025;




V0.4 2017.2.18 by LiuLu

一、添加的变量和函数
    user:
    Direction.c    
    sensorGet相关函数及变量
    
    Trackidentify.c
    void SensorGet(float* farimg, float* nearimg);
    uint16_t  LeftEdge[IMG_ROW],RightEdge[IMG_ROW];

    Uarts.c
    void ImgTrans2(uint8_t imgBuf[IMG_ROW][IMG_COL]);//返回有中线的图像

    
二、删除的变量和函数    

    CollectData:
    void SensorGet(int32_t* leftSensor, int32_t* rightSensor);
    int32_t MiddleSensorGet(void);
    
三、修改的函数

    Trackidentify.c
    void EdgeSearch( uint16_t n )
    优化赛道边线判别算法
    注释部分未应用函数
    
    ImgProc.c
    修改部分函数
    
    
    
V0.4 2017.2.19 by Wyman

一、添加的宏参数    
    #define VC_SET               3

V0.5 2017.2.20 by Wyman

一、修改的参数    

    ImaProc.c
    采集跑到延迟调到152；
    
    加方向陀螺仪，目前速度30左右
    
    #define VC_SET           29//27//21// 18//  10

    /* 方向环 */
    #ifdef DYNAMIC_DC_PID               //按VC_SET
    #define DC_PID_P_COEF      120 // 100 // 120 //70 //90  //            470.0
    #define DC_P_MIN           3000//2200// 1000//500//700 //            3200
    #define DC_P_MAX           4200//3300// 1314//800//1212//            50000
    #else  /* xDYNAMIC_DC_PID */
    #define DC_PID_P         1314
    #endif /* DYNAMIC_DC_PID */

    #define DC_PID_D           4//3// 1.6//1.3// 8.0 // 10.5
    #define DC_PERIOD            2

    ......

    翻车停止注释了。在Motor.c
	
V0.6 2017.2.20 by liulu
一、修改的地方
在场中断中加入ImgProcAnalyze函数判断十字、圆环、停车线等特殊情况



V0.7 2017.3.3 by wyman

PinMap.h

Encoder left<=>right


Encoder.c
    rightSpeed = -rightSpeed;
	change into
    leftSpeed = -leftSpeed;


V0.8 2017.3.3 by liulu

完善左右搜线算法，改方向环偏差输入为前十行中线均值与图像中线的偏差

V0.9 2017.3.3 by wyman

加入圆环识别算法，见imgproc及trackidentify.c

V1.0 2017.3.5 by liulu

修改圆环识别+处理算法，见imgproc及trackidentify.c

整圈试跑无误，速度0.5米/秒

V1.1 2017.3.10 by wyman

1. Encoder.c
    加入示波器，可测双编码
    
    leftSpeed = -leftSpeed;
	change into
    rightSpeed = -rightSpeed;

2. 重新测参数，积分待加大，PID重新调

3. system.c
            Left_Out = AC_Out - VC_Out + DC_Out;
            Right_Out = AC_Out - VC_Out - DC_Out;
        DC_Out符号

V1.2 2017.3.14 by liulu

摄像头黑0白1——>黑1白0

V1.3 2017.3.15 by wyman

加入计时和识别停止线功能
ImgProc.c
StopFlagAnalyze
StopFlag
time

V1.4 2017.3.17 by wyman

加入拨码开关
Velocity.c
void GearInit(void)

V1.5 2017.3.18 by wyman

加入文件TypeDef.h

加入结构体
typedef struct PID_speed_mode {
    int16_t DC_PID_P_COEF;
    int16_t DC_P_MIN;
    int16_t DC_P_MAX;
    float DC_PID_D;
    int16_t DC_Out_MAX;
    
    int16_t VC_Set;
    int16_t foresight;
}
mode;
取消相关宏定义
修改相关函数原型中的参数

修改函数
Velocity.c
void GearInit(void)
拨码开关对应函数Moden()共四档；

2.0 2017.3.19 by wyman

校内赛一等奖版参数，3档35m19s

Velocity.c

void Mode3(void)//大漂
{
    MODE.VC_Set = 49;
    MODE.foresight = 32;
    
    MODE.DC_PID_P_COEF = 76;
    MODE.DC_P_MIN = 800;
    MODE.DC_P_MAX = 2500;
    MODE.DC_PID_D = 3;
    MODE.DC_Out_MAX = 2800;
}
    
void Mode2(void)//小漂
{
    MODE.VC_Set = 45;
    MODE.foresight = 29;
    
    MODE.DC_PID_P_COEF = 74;
    MODE.DC_P_MIN = 800;
    MODE.DC_P_MAX = 2400;
    MODE.DC_PID_D = 2.9;
    MODE.DC_Out_MAX = 2700;
}

void Mode1(void)
{
    MODE.VC_Set = 38;
    MODE.foresight = 27;
    
    MODE.DC_PID_P_COEF = 70;
    MODE.DC_P_MIN = 800;
    MODE.DC_P_MAX = 2200;
    MODE.DC_PID_D = 2.8;
    MODE.DC_Out_MAX = 2500;
}

void Mode0(void)
{
    MODE.VC_Set = 33;
    MODE.foresight = 24;
    
    MODE.DC_PID_P_COEF = 68;
    MODE.DC_P_MIN = 800;
    MODE.DC_P_MAX = 2100;
    MODE.DC_PID_D = 2.7;
    MODE.DC_Out_MAX = 2400;
}


Param.h

#ifndef __PARAM_H
#define __PARAM_H

/* 宏开关 */
#define AC
#define VC
#define DC
#define xOUT_JUDGE
#define xSINGLE_VC
#define DYNAMIC_DC_PID
#define xFIX
//#define RS_JUDGE
//#define SLOW_DOWN
#define x__DEBUG__

///* 传感器采样滤波 */
//#define SENSOR_FLTR_SAMPLE  10

/* 角度环 */
#define Kalman_Sample_Time   0.0055
#define AC_PID_P           200.0 // 160.0
#define AC_PID_D             4.5 //   3.5
#define MMAX_ZERO         1956
#define MMAZ_ZERO          716
#define GYRO_ZERO_SAMPLE  1000
#define MMA_GAIN          0.073//0.232//    //0-90°，即正反车测值z-x的max减min=2000多，90/2000多得比例
#define MMA_SCALE         3.178//*1.2//send to Kalman scale, end is 0.232

/* 速度环 */
#define VC_PID_P           200.0 //190.0// 
#define VC_PID_I             0.15//   0.25
#define VC_PID_D             35
#define VC_Out_MAX       8000//25000
#define VC_PERIOD            4
//#define MODE.VC_Set           50//27//21// 18//  10//40设定，速度为30
//#define VC_MAX           52
//#define VC_MIN           48

/* 方向环 */
//#ifdef DYNAMIC_DC_PID               //按MODE.VC_Set
//#define MODE.DC_PID_P_COEF      70 //3// 100 // 120 //70 //90  //            470.0
//#define MODE.DC_P_MIN           800//2200// 1000//500//700 //            3200
//#define MODE.DC_P_MAX           2200//3300// 1314//800//1212//            50000
//#else  /* xDYNAMIC_DC_PID */
//#define DC_PID_P         1314
//#endif /* DYNAMIC_DC_PID */

//#define MODE.DC_PID_D           2.8//3// 1.6//1.3// 8.0 // 10.5
//#define MODE.DC_Out_MAX       2500//4000//
#define DC_PERIOD            2

#define DC_OUT_COEF_LEFT   1
#define DC_OUT_COEF_RIGHT  1

//#define dirAngleSpeedMax    300
//#define dirAngleSpeedMin    -300

#define OUT_JUDGE_STD       50
#define TURN_FLAG	       200

/* 角度和速度设定目标 */
#define AC_Set              260//156//170zero,小往后
//#define VSET_GEAR4          40
//#define VSET_GEAR3          37
//#define VSET_GEAR2          34
////#define VSET_GEAR1          38
//#define VSET_GEAR0           0

//#define  foresight4       30//23//17//15
//#define  foresight3       28//23//17//15
//#define  foresight2       26//23//17//15

//Camera
#define  IMG_ROW        50
#define  IMG_COL        225
#define  IMG_ABDN_ROW   19
#define  IMG_ROW_INTV   5

#define  IMG_WHITE      0xfe
#define  IMG_BLACK      0x00
#define  IMG_FRAME_FIN  0xff

#define  IMG_MIDPOINT    112

//Road Flag
#define  CIRCLE       1
#define  STOP         2    
#define  START        3
#define  STRAIGHTROAD 4
#define  CURVEROAD    5

#define  IMG_BORDER_SCAN_COMPENSATION  30  //边界补偿变量
#define  WIDE_ROAD_SIZE                80


/* 电机参数 */
#define MOTOR_OUT_MAX     5000
#define FIX_OUT           0

/* 发车延时 */
#define BEGIN_DELAY       4000

//NVIC
#define  HREF_IRQ  PORTD_IRQn
#define  VSYN_IRQ  PORTC_IRQn
#define  TIMR_IRQ  PIT0_IRQn

//PIT
#define  PIT_CHL  HW_PIT_CH0
#define  PIT_PRD  5000


#endif


2.1 2017.4.17 by wyman

1. Motor数据类型改成int32_t
    void MotorOut(int32_t LEFT_MOTOR_OUT, int32_t RIGHT_MOTOR_OUT) 

2. Angle中部分数据类型int32_t改成float
    float gyro;
    float angleMma;
    float angle, angleSpeed;

3. float
    if( Angle_Kalman > 370.0 ){
        Angle_Kalman = 370.0;
    }
    else if( Angle_Kalman < 100.0 ){
        Angle_Kalman = 100.0;
    }

2.2 2017.4.19 by wyman

1.初始化次序作修改
void GeneralInit(void) {
    DelayInit();
    GearInit();
    UartInit();
    MotorInit();
    CollectInit();  
    EncoderInit();
//    DisplayInit();
    NVICInit();
    TimerInit();
    ImgProcInit();
    PIT_ITDMAConfig(PIT_CHL, kPIT_IT_TOF, ENABLE);
    GPIO_ITDMAConfig(CAMERA_HREF_PORT, CAMERA_HREF_PIN, kGPIO_IT_RisingEdge, ENABLE );
    GPIO_ITDMAConfig(CAMERA_VSYN_PORT, CAMERA_VSYN_PIN, kGPIO_IT_RisingEdge, ENABLE );
}

2.  TimerInit();
    ImgProcInit();
    两处的中断都DISABLE，所有初始化完毕后再ENABLE。
    

3.0 2017.5.18  重构

by wyman

Startup已添加K10 & K60，目前选择K60,k10图像有bug。
Options for target中，Device为K60,C/C++的define为MK60D10,理由同上。

by liulu

1. 所有补线都放到搜线函数里面；
2. 前瞻行附近的中线值才会影响小车控制，其余的行为无效行
3. 图像识别处理大改

3.1 2017.5.20  by wyman

1. Mainproc.c
   直道加速，圆环减速，环内减速（5ms*300）.
   
2. Imgproc.c
   圆环补线一次渐变
   
3. Param.h
   角度、速度PD大幅减小

4. Direction.c
   方向环P加斜率一次项，二次state未完善
   
3.2 2017.5.21  by liulu

1. 加坡道识别及减速，识别为完善
2. 圆环二次offset

3.3 2017.7.1   by wyman

角度环、速度环合并为串级，方向环模糊控制

3.4 2017.7.4  by liulu

1. 圆环加转向选择
2. 圆环不用offset
3. 更新拨码开关结构体

4.0 2017.7.14 by wyman

1.重回校内赛PID
2.速度动态前瞻
3.4档速度，1档圆环方向
4.上下午两套预赛程序
5.改用6050

5.0 2017.7.29 by wyman

最后一版
完善所有文件
比赛教训：
1.注意发车调节
2.用五向开关及OLED调参
3.圆环要平滑
4.车要稳，适应不同赛道
再见了，智能车:)