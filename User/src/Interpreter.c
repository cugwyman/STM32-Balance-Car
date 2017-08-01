#include "Interpreter.h"
#include "string.h"
#include "stdlib.h"
#include "uart.h"

static char messageBuf[COMMAND_BUF_SIZE];
static char* messageBytePtr = messageBuf;
static bool isMasterModifyingSlave;
static bool isSlaveSynchronizingMaster;
static bool inSwitchSector;
static bool inParamSector;

static bool IsUpper(char charac);
static bool IsLower(char charac);
static void DebugSend(const char* message);
static void ReturnParam(void);
static void ResponseOK(void);
static void ResponseError(void);
static bool CommandParse(const char* message);
static bool SectorDeclarationParse(const char* message);
static void SwitchModificationParse(const char* message);
static void UpdateParamValueAsInt16(int16_t* param, const char* message);
static void UpdateParamValueAsDouble(double* param, const char* message);
static void ParamModificationParse(const char* message);

void MessageParse(uint16_t byte) {
    bool lineReceived = false;
    
    if(messageBytePtr - messageBuf < COMMAND_BUF_SIZE - 1) {
        *messageBytePtr = byte;
        if(*messageBytePtr == '\n') {
            lineReceived = true;
            messageBytePtr--;
            *messageBytePtr = 0;
        } else {
            messageBytePtr++;
            *messageBytePtr = 0;
        }
    } else {
        messageBytePtr = messageBuf;
        *messageBytePtr = 0;
    }
    
    if(lineReceived) {
        if(CommandParse(messageBuf)) {
            // do nothing
        } else if(isMasterModifyingSlave) {
            if(SectorDeclarationParse(messageBuf)) {
                // do nothing
            } else if(inSwitchSector) {
                SwitchModificationParse(messageBuf);
            } else if(inParamSector) {
                ParamModificationParse(messageBuf);
            }
        }
    }
}

bool IsUpper(char charac) {
    return charac >= 'A' && charac <= 'Z';
}

bool IsLower(char charac) {
    return charac >= 'a' && charac <= 'z';
}

void DebugSend(const char* message) {
    UART_printf(DATACOMM_DEBUG_CHL, message);
}

void ReturnParam() {
    char responseBuf[RESPONSE_BUF_SIZE];
    sprintf(responseBuf,
        "%s\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %lf\r\n"    "%s %lf\r\n"    "%s %lf\r\n"
        "%s %lf\r\n"    "%s %lf\r\n"    "%s %lf\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %d\r\n"
        "%s %d\r\n"     "%s %d\r\n"     "%s %f\r\n"
        "%s %f\r\n"     "%s %f\r\n"     "%s %f\r\n"
        "%s\r\n",
        START_OF_RESPONSE,
        MOTOR_HEADER, motor_on, ENCODER_HEADER, encoder_on, SPEED_CONTROL_HEADER, speed_control_on,
        DIRECTION_CONTROL_HEADER, direction_control_on, IMG_TRANS_HEADER, img_trans_on, STATE_TRANS_HEADER, state_trans_on,
        MODE_SWITCH_HEADER, mode_switch_on, USE_INC_PID_HEADER, use_inc_pid, USE_FTM_QD_HEADER, use_ftm_qd,
        SPEED_CONTROL_LEFT_P_HEADER, leftPid.kp, SPEED_CONTROL_LEFT_I_HEADER, leftPid.ki, SPEED_CONTROL_LEFT_D_HEADER, leftPid.kd,
        SPEED_CONTROL_RIGHT_P_HEADER, rightPid.kp, SPEED_CONTROL_RIGHT_I_HEADER, rightPid.ki, SPEED_CONTROL_RIGHT_D_HEADER, rightPid.kd,
        STEER_ACTUATOR_LEFT_VALUE_HEADER, steer_actuator_left, STEER_ACTUATOR_MIDDLE_VALUE_HEADER, steer_actuator_middle,
        STEER_ACTUATOR_RIGHT_VALUE_HEADER, steer_actuator_right,
        SPEED_CONTROL_LEFT_SPEED_HEADER, leftPid.targetValue, SPEED_CONTROL_RIGHT_SPEED_HEADER, rightPid.targetValue,
        SPEED_CONTROL_SUM_ERR_MAX_HEADER, speed_control_sum_err_max,
        SPEED_CONTROL_SPEED_HEADER, speed_control_speed, IMG_BORDER_SCAN_COMPENSATION_HEADER, img_border_scan_compensation,
        WIDE_ROAD_SIZE_HEADER, wide_road_size,
        CURVES_SENSITIVITY_HEADER, curve_sensitivity, SLOPE_SENSITIVITY_HEADER, slope_sensitivity,
        INFLEXION_SENSITIVITY_HEADER, inflexion_sensitivity,
        CROSS_ROAD_SIZE_HEADER, cross_road_size, STRAIGHT_ROAD_SENSITIVITY_HEADER, straight_road_sensitivity,
        DIRECTION_CONTROL_KD_HEADER, direction_control_kd,
        DIRECTION_CONTROL_KPJ_HEADER, direction_control_kpj, DIRECTION_CONTROL_KPC_HEADER, direction_control_kpc,
        DIRECTION_CONTROL_ANGLE_MAX_HEADER, direction_control_angle_max,
        END_OF_RESPONSE
    );
    DebugSend(responseBuf);
}

void ResponseOK() {
    DebugSend(OK_RESPONSE);
}

void ResponseError() {
    DebugSend(ERROR_RESPONSE);
}

bool CommandParse(const char* message) {
    if(!strcmp(message, MODIFY_COMMAND)) {
        isMasterModifyingSlave = true;
    } else if(!strcmp(message, END_OF_COMMAND)) {
        if(isSlaveSynchronizingMaster) {
            ReturnParam();
        } else if(isMasterModifyingSlave) {
            ResponseOK();
        } else {
            ResponseError();
        }
        isMasterModifyingSlave = false;
        isSlaveSynchronizingMaster = false;
        inSwitchSector = false;
        inParamSector = false;
    } else {
        return false;
    }
    // drop down here from if or else if
    return true;
}

bool SectorDeclarationParse(const char* message) {
    if(!strcmp(message, DECLARE_SWITCH_SECTOR)) {
        inParamSector = false;
        inSwitchSector = true;
    } else if(!strcmp(message, DECLARE_PARAM_SECTOR)) {
        inSwitchSector = false;
        inParamSector = true;
    } else {
        return false;
    }
    // drop down here from if or else if
    return true;
}

void SwitchModificationParse(const char* message) {
    if(!strcasecmp(message, MOTOR_HEADER)) {
        if(IsUpper(*message)) {
            motor_on = true;
        } else if(IsLower(*message)) {
            motor_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, ENCODER_HEADER)) {
        if(IsUpper(*message)) {
            encoder_on = true;
        } else if(IsLower(*message)) {
            encoder_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, SPEED_CONTROL_HEADER)) {
        if(IsUpper(*message)) {
            speed_control_on = true;
        } else if(IsLower(*message)) {
            speed_control_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, DIRECTION_CONTROL_HEADER)) {
        if(IsUpper(*message)) {
            direction_control_on = true;
        } else if(IsLower(*message)) {
            direction_control_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, STEER_ACTUATOR_HEADER)) {
        if(IsUpper(*message)) {
            steer_actuator_on = true;
        } else if(IsLower(*message)) {
            steer_actuator_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, IMG_TRANS_HEADER)) {
        if(IsUpper(*message)) {
            img_trans_on = true;
        } else if(IsLower(*message)) {
            img_trans_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, STATE_TRANS_HEADER)) {
        if(IsUpper(*message)) {
            state_trans_on = true;
        } else if(IsLower(*message)) {
            state_trans_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, MODE_SWITCH_HEADER)) {
        if(IsUpper(*message)) {
            mode_switch_on = true;
        } else if(IsLower(*message)) {
            mode_switch_on = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, USE_INC_PID_HEADER)) {
        if(IsUpper(*message)) {
            use_inc_pid = true;
        } else if(IsLower(*message)) {
            use_inc_pid = false;
        } else {
            ResponseError();
        }
    } else if(!strcasecmp(message, USE_FTM_QD_HEADER)) {
        if(IsUpper(*message)) {
            use_ftm_qd = true;
        } else if(IsLower(*message)) {
            use_ftm_qd = false;
        } else {
            ResponseError();
        }
    } else {
        ResponseError();
    }
}

void UpdateParamValueAsInt16(int16_t* param, const char* message) {
    const char* value = &message[PARAM_NAME_LENGTH + 1];
    *param = atoi(value);
}

void UpdateParamValueAsInt32(int32_t* param, const char* message) {
    const char* value = &message[PARAM_NAME_LENGTH + 1];
    *param = atoi(value);
}

void UpdateParamValueAsDouble(double* param, const char* message) {
    const char* value = &message[PARAM_NAME_LENGTH + 1];
    *param = atof(value);
}

void ParamModificationParse(const char* message) {
    if(!strncmp(message, SPEED_CONTROL_LEFT_P_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&leftPid.kp, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_LEFT_I_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&leftPid.ki, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_LEFT_D_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&leftPid.kd, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_RIGHT_P_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&rightPid.kp, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_RIGHT_I_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&rightPid.ki, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_RIGHT_D_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&rightPid.kd, message);
        
    } else if(!strncmp(message, STEER_ACTUATOR_LEFT_VALUE_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&steer_actuator_left, message);
        
    } else if(!strncmp(message, STEER_ACTUATOR_MIDDLE_VALUE_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&steer_actuator_middle, message);
        
    } else if(!strncmp(message, STEER_ACTUATOR_RIGHT_VALUE_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&steer_actuator_right, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_LEFT_SPEED_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&leftPid.targetValue, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_RIGHT_SPEED_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&rightPid.targetValue, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_SUM_ERR_MAX_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&speed_control_sum_err_max, message);
        
    } else if(!strncmp(message, SPEED_CONTROL_SPEED_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&speed_control_speed, message);
        
    } else if(!strncmp(message, IMG_BORDER_SCAN_COMPENSATION_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&img_border_scan_compensation, message);
        
    } else if(!strncmp(message, WIDE_ROAD_SIZE_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&wide_road_size, message);
        
    } else if(!strncmp(message, CURVES_SENSITIVITY_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&curve_sensitivity, message);
        
    } else if(!strncmp(message, SLOPE_SENSITIVITY_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&slope_sensitivity, message);
        
    } else if(!strncmp(message, INFLEXION_SENSITIVITY_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&inflexion_sensitivity, message);
        
    } else if(!strncmp(message, CROSS_ROAD_SIZE_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&cross_road_size, message);
        
    } else if(!strncmp(message, STRAIGHT_ROAD_SENSITIVITY_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsInt16(&straight_road_sensitivity, message);
        
    } else if(!strncmp(message, DIRECTION_CONTROL_KD_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&direction_control_kd, message);
        
    } else if(!strncmp(message, DIRECTION_CONTROL_KPJ_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&direction_control_kpj, message);
        
    } else if(!strncmp(message, DIRECTION_CONTROL_KPC_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&direction_control_kpc, message);
        
    } else if(!strncmp(message, DIRECTION_CONTROL_ANGLE_MAX_HEADER, PARAM_NAME_LENGTH)) {
        UpdateParamValueAsDouble(&direction_control_angle_max, message);
        
    } else {
        ResponseError();
    }
}
