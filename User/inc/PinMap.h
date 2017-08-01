#ifndef _PINMAP_H
#define _PINMAP_H

/* Motor */
#define LEFT_MOTOR_FORWARD_MAP  FTM0_CH7_PD07//PWM3ºÚ  ±³¶Ô¾µÍ·£¬ÓÒ±ßÊÇÓÒ
#define LEFT_MOTOR_REVERSE_MAP  FTM0_CH6_PD06//PWM4°×
#define RIGHT_MOTOR_REVERSE_MAP FTM0_CH5_PD05//PWM2×Ï
#define RIGHT_MOTOR_FORWARD_MAP FTM0_CH4_PD04//PWM1»Ò
#define MOTOR_PORT              HW_FTM0
#define LEFT_MOTOR_FORWARD_CHL  HW_FTM_CH7
#define LEFT_MOTOR_REVERSE_CHL  HW_FTM_CH6
#define RIGHT_MOTOR_REVERSE_CHL HW_FTM_CH5
#define RIGHT_MOTOR_FORWARD_CHL HW_FTM_CH4

/* Encoder */    //1 GND  2 3.3-5V  3 A  4 B
#define RIGHT_ENCODER_MAP      FTM1_QD_PHA_PA12_PHB_PA13
#define LEFT_ENCODER_MAP       FTM2_QD_PHA_PB18_PHB_PB19//»Æ³È
#define RIGHT_ENCODER_CHL      HW_FTM1
#define LEFT_ENCODER_CHL       HW_FTM2

/* Gyro */
#define GYRO_MAP             ADC0_SE13_PB3   //V2
#define DIR_GYRO_MAP         ADC0_SE12_PB2   //V1

/* Acce */
#define ACCE_MMAX_MAP           ADC1_SE8_PB0 
#define ACCE_MMAZ_MAP           ADC1_SE9_PB1

//Data Communication
#define  DATACOMM_IMG_TRANS_MAP     UART0_RX_PB16_TX_PB17
#define  DATACOMM_IMG_TRANS_CHL     HW_UART0
#define  DATACOMM_IMG_TRANS_BAUD    115200
#define  DATACOMM_VISUALSCOPE_CHL   DATACOMM_IMG_TRANS_CHL

//Camera
#define  CAMERA_HREF_PORT  HW_GPIOD
#define  CAMERA_HREF_PIN   0
#define  CAMERA_VSYN_PORT  HW_GPIOC
#define  CAMERA_VSYN_PIN   18
#define  CAMERA_DATA_PORT  HW_GPIOD
#define  CAMERA_DATA_PIN   1
#define  CAMERA_ODEV_PORT  HW_GPIOD
#define  CAMERA_ODEV_PIN   3
#define  CAMERA_DATA_READ  PDin(CAMERA_DATA_PIN)

//Mode Switch
#define DIP_PORT                HW_GPIOA
#define DIP1_PIN                17
#define DIP2_PIN                16
#define DIP3_PIN                15
#define DIP4_PIN                14

//Alert
#define  BUZZLE_PORT  HW_GPIOA
#define  BUZZLE_PIN   19
#define  BUZZLE_ON    (PAout(BUZZLE_PIN) = 1)
#define  BUZZLE_OFF   (PAout(BUZZLE_PIN) = 0)
#define  BUZZLE_REVERSE			(PAout(BUZZLE_PIN) = !PAout(BUZZLE_PIN))

//Joystick
#define  JOYSTICK_NORTH_PORT    HW_GPIOC
#define  JOYSTICK_NORTH   0
#define  JOYSTICK_SOUTH_PORT    HW_GPIOB
#define  JOYSTICK_SOUTH   22
#define  JOYSTICK_WEST_PORT     HW_GPIOB
#define  JOYSTICK_WEST    21
#define  JOYSTICK_EAST_PORT     HW_GPIOB
#define  JOYSTICK_EAST    23
#define  JOYSTICK_MIDDLE_PORT   HW_GPIOC
#define  JOYSTICK_MIDDLE  1

#endif
