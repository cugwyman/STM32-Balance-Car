/**********************************************
 *   
 *      STM32 Balance Car 平衡车 V1.3
 *               2017.8.6
 *     CUG     Wyman    Sun    Chen
 *          
 *     IDE              Keil MDK V5.23
 *     MCU              STM32F103ZET6
 *     Attitude transducer     MPU6050
 *     Motor drivers    BTN
 *     Motor            DC motor     
 *
 **********************************************/
 
/**********************************************
 *
 *  2017.7.29   V1.0
 *  
 *  1.外设均在HARDWARE文件夹,控制control.c暂时也放在此，参数、开关等h文件在DOCUMENT文件夹
 *  2.全局变量统一在其定义处的C文件自身的h文件处进行外部引用，
 *  3.6050暂时通过硬件I2C直接读取DMP
 *  4.引脚安排在README.txt
 *
 *  2017.7.29   V1.1
 *  
 *  1.直立控制已加入，具体函数在control.c,实现在timer.c
 *
 *  2017.7.30   V1.2
 *  
 *  1.add OLED module
 *  2.add infrared module 红外循迹模块ST118
 *  3.connect ir and direction_PID  目前方向环根据红外循迹控制
 *
 *  2017.8.6   V1.3
 *  
 *  1.键盘调参OLED显示finished
 *  2.add CCD
 *
 **********************************************/



	
硬件资源:    注意优先级
	1,蜂鸣器1个，B8
	2,串口1(波特率:115200,PA9/PA10)
	3,LED1个，随意，目前在B5
	4,KEY4个，随意，目前在F6/F7/F8/F9
	5,MPU6050模块一个，暂定硬件I2C，可能有bug(连接在PB10(SCL),PB11(SDA),PA15(AD0)上面,INT未用到). 
	6.OLED1个，软件I2C，A2/A3/A4/A5
    7.编码器2个，TIM2用B8/B9；TIM4用B6/B7
    8.PWM4路，TIM3（全部重映射）C6/C7/C8/C9
    9.定时中断TIM5，5ms
    10.面阵CCD,行场E3/E4，数据口相近找一个，如E5
    11.超声波1-2个,B1/B2
    12.红外ST118模块5个,E6/E7/E8/E9/E10
    
	 
注意事项:




































