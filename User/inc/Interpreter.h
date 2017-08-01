#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "root.h"
#include "MainProc.h"

// Command
#define MODIFY_COMMAND                      "mdf"
#define END_OF_COMMAND                      "eoc"

// Response
#define START_OF_RESPONSE                   "sor"
#define OK_RESPONSE                         "ok"
#define ERROR_RESPONSE                      "err"
#define END_OF_RESPONSE                     "eor"

// Sector Declaration
#define DECLARE_SWITCH_SECTOR               "swt"
#define DECLARE_PARAM_SECTOR                "prm"

// Switch Header
#define MOTOR_HEADER                        "mtr"
#define ENCODER_HEADER                      "ecd"
#define SPEED_CONTROL_HEADER                "spd"
#define DIRECTION_CONTROL_HEADER            "dir"
#define STEER_ACTUATOR_HEADER               "sac"
#define IMG_TRANS_HEADER                    "img"
#define STATE_TRANS_HEADER                  "stt"
#define MODE_SWITCH_HEADER                  "mds"
#define USE_INC_PID_HEADER                  "inc"
#define USE_FTM_QD_HEADER                   "ftm"

// Param Header
#define SPEED_CONTROL_LEFT_P_HEADER         "slp"
#define SPEED_CONTROL_LEFT_I_HEADER         "sli"
#define SPEED_CONTROL_LEFT_D_HEADER         "sld"
#define SPEED_CONTROL_RIGHT_P_HEADER        "srp"
#define SPEED_CONTROL_RIGHT_I_HEADER        "sri"
#define SPEED_CONTROL_RIGHT_D_HEADER        "srd"

#define STEER_ACTUATOR_LEFT_VALUE_HEADER    "sal"
#define STEER_ACTUATOR_MIDDLE_VALUE_HEADER  "sam"
#define STEER_ACTUATOR_RIGHT_VALUE_HEADER   "sar"

#define SPEED_CONTROL_LEFT_SPEED_HEADER     "lsp"
#define SPEED_CONTROL_RIGHT_SPEED_HEADER    "rsp"
#define SPEED_CONTROL_SUM_ERR_MAX_HEADER    "sem"

#define SPEED_CONTROL_SPEED_HEADER          "scs"

#define IMG_BORDER_SCAN_COMPENSATION_HEADER "bsc"
#define WIDE_ROAD_SIZE_HEADER               "wrs"
#define CURVES_SENSITIVITY_HEADER           "css"
#define SLOPE_SENSITIVITY_HEADER            "sss"
#define INFLEXION_SENSITIVITY_HEADER        "iss"
#define CROSS_ROAD_SIZE_HEADER              "crs"
#define STRAIGHT_ROAD_SENSITIVITY_HEADER    "srs"
#define DIRECTION_CONTROL_KD_HEADER         "dcd"
#define DIRECTION_CONTROL_KPJ_HEADER        "dcj"
#define DIRECTION_CONTROL_KPC_HEADER        "dcc"
#define DIRECTION_CONTROL_ANGLE_MAX_HEADER  "dam"

// Parser Relative
#define PARAM_NAME_LENGTH   3
#define COMMAND_BUF_SIZE    15
#define RESPONSE_BUF_SIZE   200

void MessageParse(uint16_t byte);

#endif
