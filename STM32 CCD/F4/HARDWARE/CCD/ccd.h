#ifndef __CCD_H
#define __CCD_H	 
#include "stm32f4xx.h"

#define SEND_BUF_SIZE 60	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.
#define  LINE     400  
extern u8  image[200][200]; 
void CCD_init(void);


#endif

