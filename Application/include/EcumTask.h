/*
 * Ecum.h
 *
 *  Created on: 2021Äê3ÔÂ25ÈÕ
 *      Author: shenh4
 */

#ifndef APPLICATION_SOURCE_ECUM_H_
#define APPLICATION_SOURCE_ECUM_H_

/* ======================================================================================================= */
#include "Typedef.h"

/* ======================================================================================================= */
#define ECUM_STATE_GET                          Ecumstate
#define ECUM_TASK_TRANS_STATE_GET(id)           Ecumtaskstate[id].task_trans_state
#define ECUM_TASK_TRANS_STATE_SET(id, state)    Ecumtaskstate[id].task_trans_state = state
#define ECUM_TASK_SLEEP_STATE_GET(id)			Ecumtasksleepstate[id].task_work_state
#define ECUM_TASK_SLEEP_STATE_SET(id,state)		Ecumtasksleepstate[id].task_work_state = state
#define ECUM_TASK_WAKEUP_STATE_GET(id)			Ecumtaskwakeupstate[id].task_work_state
#define ECUM_TASK_WAKEUP_STATE_SET(id,state)	Ecumtaskwakeupstate[id].task_work_state = state

/* =================================================================================== */
typedef enum
{
    ECUM_STATE_STARTUP = 0u,
    ECUM_STATE_NORMAL,
    ECUM_STATE_LIMITED,
    ECUM_STATE_PRE_SLEEP,
    ECUM_STATE_SLEEP,
    ECUM_STATE_WAKEUP,
    ECUM_STATE_STARTUP_TO_NORMAL,
    ECUM_STATE_STARTUP_TO_LIMITED,
    ECUM_STATE_NORMAL_TO_LIMITED,
    ECUM_STATE_LIMITED_TO_NORMAL,
    ECUM_STATE_WAKEUP_TO_NORMAL,
    ECUM_STATE_WAKEUP_TO_LIMITED,
    ECUM_STATE_NUM
}EcumState_t;

typedef enum
{
    ECUM_STATE_TRANSITION_FAIL = 0u,
    ECUM_STATE_TRANSITION_OK,
    ECUM_STATE_TRANSITION_NUM
}EcuStateTrans_t;

typedef enum
{
    BAT_STATE_VOL_NORMAL = 0u,
    BAT_STATE_VOL_HIGH,
    BAT_STATE_VOL_LOW,
    BAT_STATE_NUM
}BatState_t;

typedef enum
{
    TASK_ID_TOUCH = 0u,
    TASK_ID_SENSOR,
    TASK_ID_LED,
    TASK_ID_ADC_DAC,
    TASK_ID_LIN,
    TASK_ID_EEPROM,
    TASK_ID_NUM
}EcumTaskId_t;

typedef enum
{
	ECUM_SLEEP_READY_NOT_OK = 0u,
	ECUM_SLEEP_READY_OK,
	ECUM_WAKEUP_READY_NOT_OK,
	ECUM_WAKEUP_READY_OK,
	ECUM_WORK_NUM
}EcumWorkState_t;

typedef struct
{
    EcumTaskId_t task_id;
    EcuStateTrans_t task_trans_state;
}EcumTaskState_t;

typedef struct
{
    EcumTaskId_t task_id;
    EcumWorkState_t task_work_state;
}EcumTaskWorkState_t;
/* =================================================================================== */
EcumState_t Ecumstate;
EcumTaskState_t Ecumtaskstate[TASK_ID_NUM];
EcumTaskWorkState_t Ecumtasksleepstate[TASK_ID_NUM];
EcumTaskWorkState_t Ecumtaskwakeupstate[TASK_ID_NUM];

/* ======================================================================================================= */
extern void Task_Ecum_Handler(void);
extern void Ecum_Wakeup_Mode_Switch(void);
extern void Ecum_Pre_Sleep_Mode_Switch(void);
/* ======================================================================================================= */


#endif /* APPLICATION_SOURCE_ECUM_H_ */
