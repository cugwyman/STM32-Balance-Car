#ifndef _FUZZY_H
#define _FUZZY_H

#include "Root.h"
extern mode MODE;

extern int32_t speed;
extern float reFuzzy;
 
extern float   Fuzzy(float P,float D);
int32_t FUZZY_pid(int E,int EC);

#endif
