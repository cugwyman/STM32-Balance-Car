#ifndef _DATACOMM_H
#define _DATACOMM_H

#include "root.h"
#include "Interpreter.h"

void DataCommInit(void);
void ImgTransOnlyBorderAndMiddleLine(int8_t* leftBorder, int8_t* middleLine, int8_t* rightBorder);// recommanded
void ImgTrans(img_proc_struct* resultSetPtr);
void StateTrans(float a, float b, float c, float d);

extern bool img_trans_on, state_trans_on, mode_switch_on;

#endif
