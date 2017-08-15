#ifndef __CCD_H
#define __CCD_H	 
#include "stm32f4xx.h"

#define SEND_BUF_SIZE 60	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.
#define  LINE     400  
extern u8  image[200][200]; 
void CCD_init(void);


#endif

