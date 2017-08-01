#include "Joystick.h"
#include "gpio.h"
#include "MainProc.h"
#include "stdio.h"
#include "oledbase.h"

static struct _temp_handle {
    int16_t index;
    union {
        int16_t i16;
        int32_t i32;
        float f;
		bool b;
    } u;
} temp = {
    0, 0
};

static struct _param_handle {
    int16_t index;
    enum { INT16, INT32, FLOAT, BOOL } type[MODIFIABLE_PARAM_NUM];
    char *name[MODIFIABLE_PARAM_NUM];
    void *(ref[MODIFIABLE_PARAM_NUM]);
    float div[MODIFIABLE_PARAM_NUM];
} param = {
    0,
    { BOOL, BOOL, INT16, INT16, FLOAT },
    { "ringDir", "speed", "pre_sight", "VC_Set", "ku" },
    { &MODE.ringDir, &speed_up_down, &MODE.pre_sight,
        &MODE.VC_Set, &MODE.Ku },
    { 0, 0, 1, 1, 0.1 }
};

void JoystickInt(void);
//void Joystick_up(uint32_t pinxArray);
//void Joystick_down(uint32_t pinxArray);
//void Joystick_left(uint32_t pinxArray);
//void Joystick_right(uint32_t pinxArray);
//void Joystick_middle(uint32_t pinxArray);

static void ParamShow(void);
static void ParamFetch(void);
static void ParamInc(void);
static void ParamDec(void);
static void ParamUpdate(void);

void JoystickInit() {
	ParamFetch();
    ParamShow();
    GPIO_QuickInit(JOYSTICK_NORTH_PORT, JOYSTICK_NORTH, kGPIO_Mode_IPD);
    GPIO_QuickInit(JOYSTICK_SOUTH_PORT, JOYSTICK_SOUTH, kGPIO_Mode_IPD);
    GPIO_QuickInit(JOYSTICK_WEST_PORT, JOYSTICK_WEST, kGPIO_Mode_IPD);
    GPIO_QuickInit(JOYSTICK_EAST_PORT, JOYSTICK_EAST, kGPIO_Mode_IPD);
    GPIO_QuickInit(JOYSTICK_MIDDLE_PORT, JOYSTICK_MIDDLE, kGPIO_Mode_IPD);
//    GPIO_CallbackInstall(JOYSTICK_NORTH_PORT, JoystickInt);
//	GPIO_CallbackInstall(JOYSTICK_SOUTH_PORT, Joystick_down);
//	GPIO_CallbackInstall(JOYSTICK_WEST_PORT, Joystick_left);
//	GPIO_CallbackInstall(JOYSTICK_EAST_PORT, Joystick_right);
//	GPIO_CallbackInstall(JOYSTICK_MIDDLE_PORT, Joystick_middle);
//    GPIO_ITDMAConfig(JOYSTICK_NORTH_PORT, JOYSTICK_NORTH, kGPIO_IT_RisingEdge, ENABLE);
//    GPIO_ITDMAConfig(JOYSTICK_SOUTH_PORT, JOYSTICK_SOUTH, kGPIO_IT_RisingEdge, ENABLE);
//    GPIO_ITDMAConfig(JOYSTICK_WEST_PORT, JOYSTICK_WEST, kGPIO_IT_RisingEdge, ENABLE);
//    GPIO_ITDMAConfig(JOYSTICK_EAST_PORT, JOYSTICK_EAST, kGPIO_IT_RisingEdge, ENABLE);
//    GPIO_ITDMAConfig(JOYSTICK_MIDDLE_PORT, JOYSTICK_MIDDLE, kGPIO_IT_RisingEdge, ENABLE);
    
}

void JoystickInt(void) {
    if(GPIO_ReadBit(JOYSTICK_NORTH_PORT,JOYSTICK_NORTH)) {
        ParamInc();
        ParamShow();
    } else if(GPIO_ReadBit(JOYSTICK_SOUTH_PORT,JOYSTICK_SOUTH)) {
        ParamDec();
        ParamShow();
    } else if(GPIO_ReadBit(JOYSTICK_WEST_PORT,JOYSTICK_WEST)) {
        if(--param.index < 0) {
            param.index = MODIFIABLE_PARAM_NUM - 1;
        }
        ParamFetch();
        ParamShow();
    } else if(GPIO_ReadBit(JOYSTICK_EAST_PORT,JOYSTICK_EAST)) {
        param.index = (param.index + 1) % MODIFIABLE_PARAM_NUM;
        ParamFetch();
        ParamShow();
    } else if(GPIO_ReadBit(JOYSTICK_MIDDLE_PORT,JOYSTICK_MIDDLE)) {
        ParamUpdate();
        ParamShow();
        DelayMs(100);
        OLEDPrintf(54, 30, "OK!");
    }
}


void ParamShow() {
    OLEDClrRow(3);
	OLEDClrRow(30);
    DelayMs(100);
//	OLED_DispStr(54,24,"CUG",&tFont16);
//	OLED_DrawCircle(64,32,30,0xff);
//	printf("show");
    switch(param.type[temp.index]) {
        case INT16:
            OLEDPrintf(5, 3, "%s: %d", param.name[temp.index], temp.u.i16);
            break;
        case INT32:
            OLEDPrintf(5, 3, "%s: %d", param.name[temp.index], temp.u.i32);
            break;
        case FLOAT:
            OLEDPrintf(5, 3, "%s: %.4f", param.name[temp.index], temp.u.f);
            break;
		case BOOL:
			if(temp.index == 0)
			{
				if(temp.u.b)
					OLEDPrintf(5, 3, "%s: left", param.name[temp.index]);
				else
					OLEDPrintf(5, 3, "%s: right", param.name[temp.index]);
			}
			else
			{
				if(temp.u.b)
					OLEDPrintf(5, 3, "%s:  OK!", param.name[temp.index]);
				else
					OLEDPrintf(5, 3, "%s:  close!", param.name[temp.index]);
			}
    }
}

void ParamFetch() {
    temp.index = param.index;
    switch(param.type[param.index]) {
        case INT16:
            temp.u.i16 = *(int16_t *)(param.ref[param.index]);
            break;
        case INT32:
            temp.u.i32 = *(int32_t *)(param.ref[param.index]);
            break;
        case FLOAT:
            temp.u.f = *(float *)(param.ref[param.index]);
            break;
		case BOOL:
			temp.u.b = *(bool *) (param.ref[param.index]);
    }
}

void ParamInc() {
    switch(param.type[temp.index]) {
        case INT16:
            temp.u.i16 += param.div[temp.index];
            break;
        case INT32:
            temp.u.i32 += param.div[temp.index];
            break;
        case FLOAT:
            temp.u.f += param.div[temp.index];
            break;
		case BOOL:
			temp.u.b = true;
    }
}

void ParamDec() {
    switch(param.type[temp.index]) {
        case INT16:
            temp.u.i16 -= param.div[temp.index];
            break;
        case INT32:
            temp.u.i32 -= param.div[temp.index];
            break;
        case FLOAT:
            temp.u.f -= param.div[temp.index];
            break;
		case BOOL:
			temp.u.b = false;
    }
}

void ParamUpdate() {
    switch(param.type[temp.index]) {
        case INT16:
            *(int16_t *)(param.ref[temp.index]) = temp.u.i16;
            break;
        case INT32:
            *(int32_t *)(param.ref[temp.index]) = temp.u.i32;
            break;
        case FLOAT:
            *(float *)(param.ref[temp.index]) = temp.u.f;
            break;
		case BOOL:
			*(bool *) (param.ref[temp.index]) = temp.u.b;
    }
}
