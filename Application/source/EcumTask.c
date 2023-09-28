/*
 * Ecum.c
 *
 *  Created on: 2021Äê3ÔÂ25ÈÕ
 *      Author: shenh4
 */

#include <EcumTask.h>
#include "AppLin.h"
#include "AppIF.h"
#include "Os.h"


#define ECUM_WAKEUP_TIMEOUT_COUNT			10u		/* 10*20ms = 200ms */

static void Ecum_Lin_Bus_Sleep_Check(void);

EcumState_t Ecumstate = ECUM_STATE_STARTUP;

EcumTaskState_t Ecumtaskstate[TASK_ID_NUM] =
{
    {TASK_ID_LED,               ECUM_STATE_TRANSITION_FAIL}
};

EcumTaskWorkState_t Ecumtasksleepstate[TASK_ID_NUM] =
{
	{TASK_ID_LED,               ECUM_SLEEP_READY_NOT_OK}
};

EcumTaskWorkState_t Ecumtaskwakeupstate[TASK_ID_NUM] =
{
	{TASK_ID_LED,               ECUM_WAKEUP_READY_NOT_OK}
};

static uint8_t ucEcmWakeupTime = 0;

static void Ecum_State_Manage(void);
static void Ecum_Startup_Condition_Check(void);
static void Ecum_Normal_Condition_Check(void);
static void Ecum_Limited_Condition_Check(void);
static void Ecum_Pre_Sleep_Condition_Check(void);
static void Ecum_Pre_Sleep_Condition_Clear(void);
static void Ecum_Sleep_Condition_Check(void);
static void Ecum_Wakeup_Condition_Check(void);
static void Ecum_Wakeup_Condition_Clear(void);
static void Ecum_Wakeup_Timeout_Check(void);
static void Ecum_Wakeup_Timeout_Clear(void);
static EcuStateTrans_t Ecum_State_Transition_Ok_Check();
static void Ecum_State_Transition_Ok_Clear(void);


void Task_Ecum_Handler(void)
{
	Ecum_State_Manage();
}

/* ======================================================================================================= */
static void Ecum_State_Manage(void)
{
#if (1u == BAT_VOL_CHECK_ENABLE)
    Ecum_Battery_Voltage_Check();
#endif

    Ecum_Lin_Bus_Sleep_Check();


}

/* ======================================================================================================= */
static void Ecum_Startup_Condition_Check(void)
{
    Ecumstate = ECUM_STATE_STARTUP_TO_NORMAL;
}

/* ======================================================================================================= */
static void Ecum_Normal_Condition_Check(void)
{
    static uint8_t eol_sleep_delay_cnt = 0u;

#if (1u == BAT_VOL_CHECK_ENABLE)
    if(BAT_STATE_VOL_NORMAL != Batstate)
    {
        Ecum_Task_Trans_State_Clear();
        Ecumstate = ECUM_STATE_NORMAL_TO_LIMITED;
    }
#endif
    /* Check go to sleep mode condition */

#if 0
    if((TRUE == Get_No_Force_Touched_State()) && (TRUE == Get_Lin_Transfer_State()) && (EOL_TEST_MODE != Get_EOL_Test_Mode()))
    {
        Ecum_Pre_Sleep_Mode_Switch();
    }
    /* Check EOL power */
    if(EOL_SYS_POWER_SLEEP_MODE == Get_EOL_Sys_Power_Mode())
    {
        eol_sleep_delay_cnt++;
        if(eol_sleep_delay_cnt > ECUM_EOL_SLEEP_DELAY_CNT)
        {
            eol_sleep_delay_cnt = 0u;
            Ecum_Pre_Sleep_Mode_Switch();
        }
    }
#endif
}

/* ======================================================================================================= */
static void Ecum_Limited_Condition_Check(void)
{
#if (1u == BAT_VOL_CHECK_ENABLE)
    if(BAT_STATE_VOL_NORMAL == Batstate)
    {
        Ecum_Task_Trans_State_Clear();
        Ecumstate = ECUM_STATE_LIMITED_TO_NORMAL;
    }
#endif
}

/* ======================================================================================================= */
static void Ecum_Pre_Sleep_Condition_Check(void)
{
    uint8_t task_id = 0u;
    EcumWorkState_t sleep_state = ECUM_SLEEP_READY_OK;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
        if(ECUM_SLEEP_READY_OK != Ecumtasksleepstate[task_id].task_work_state)
        {
        	sleep_state = ECUM_SLEEP_READY_NOT_OK;
            break;
        }
    }

    if(ECUM_SLEEP_READY_OK == sleep_state)
    {
    	Ecumstate = ECUM_STATE_SLEEP;
    }
}

/* ======================================================================================================= */
static void Ecum_Pre_Sleep_Condition_Clear(void)
{
    uint8_t task_id = 0u;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
    	Ecumtasksleepstate[task_id].task_work_state = ECUM_SLEEP_READY_NOT_OK;
    }
}

/* ======================================================================================================= */
static void Ecum_Sleep_Condition_Check(void)
{
	/* Os Shutdown */
	Os_Shutdown();

	/* Deinit NextInput */
	//NextInput_Deinit();

	/* Clear NextInput Int */
	//NextInput_Clear_INT(NI_NUM_0);

	/*Deinit watch dog*/
	//WatchDog_Deinit();

	/* Port Set Sleep mode */
	//PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr_Sleep);

	/* Power Manager Set Sleep mode */
	//(void)POWER_SYS_SetMode(1, POWER_MANAGER_POLICY_AGREEMENT);
}

/* ======================================================================================================= */
static void Ecum_Wakeup_Condition_Check(void)
{
    uint8_t task_id = 0u;
    EcumWorkState_t wakeup_state = ECUM_WAKEUP_READY_OK;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
        if(ECUM_WAKEUP_READY_OK != Ecumtaskwakeupstate[task_id].task_work_state)
        {
        	wakeup_state = ECUM_WAKEUP_READY_NOT_OK;
            break;
        }
    }

    if(ECUM_WAKEUP_READY_OK == wakeup_state)
    {
    	Ecum_State_Transition_Ok_Clear();
    	Ecumstate = ECUM_STATE_WAKEUP_TO_NORMAL;
    }
}

/* ======================================================================================================= */
static void Ecum_Wakeup_Condition_Clear(void)
{
    uint8_t task_id = 0u;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
    	Ecumtaskwakeupstate[task_id].task_work_state = ECUM_WAKEUP_READY_NOT_OK;
    }
}

/* ======================================================================================================= */
static void Ecum_Wakeup_Timeout_Check(void)
{
	if(ECUM_WAKEUP_TIMEOUT_COUNT == ucEcmWakeupTime)
	{
		Ecum_Pre_Sleep_Mode_Switch();
	}
	else
	{
		ucEcmWakeupTime++;
	}
}

/* ======================================================================================================= */
static void Ecum_Wakeup_Timeout_Clear(void)
{
	ucEcmWakeupTime = 0;
}

/* ======================================================================================================= */
static EcuStateTrans_t Ecum_State_Transition_Ok_Check(void)
{
    uint8_t task_id;
    EcuStateTrans_t trans_state;

    trans_state = ECUM_STATE_TRANSITION_OK;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
        if(ECUM_STATE_TRANSITION_OK != Ecumtaskstate[task_id].task_trans_state)
        {
            trans_state = ECUM_STATE_TRANSITION_FAIL;
            break;
        }
    }

    return trans_state;
}

/* ======================================================================================================= */
static void Ecum_State_Transition_Ok_Clear(void)
{
    uint8_t task_id = 0u;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
    	Ecumtaskstate[task_id].task_trans_state = ECUM_STATE_TRANSITION_FAIL;
    }
}

/* ======================================================================================================= */
#if(BAT_VOL_CHECK_ENABLE)
static void Ecum_Task_Trans_State_Clear(void)
{
    uint8_t task_id;

    for(task_id = 0u; task_id < TASK_ID_NUM; task_id++)
    {
        Ecumtaskstate[task_id].task_trans_state = ECUM_STATE_TRANSITION_FAIL;
    }
}
#endif

/* ======================================================================================================= */
#if(BAT_VOL_CHECK_ENABLE)
static void Ecum_Battery_Voltage_Check(void)
{
#if (1u == BAT_VOL_CHECK_ENABLE)
    uint16 voltage;
    static uint16 vol_high_tcnt = 0u;
    static uint16 vol_high_recover_tcnt = 0u;
    static uint16 vol_low_tcnt = 0u;
    static uint16 vol_low_recover_tcnt = 0u;

    voltage = BatVolGet();

    /* Battery voltage high check */
    if(voltage > BAT_VOL_HIGH_VALUE)
    {
        vol_high_tcnt++;
        if(vol_high_tcnt > BAT_VOL_HIGH_TIME_VALUE)
        {
            vol_high_tcnt = BAT_VOL_HIGH_TIME_VALUE;
            Batstate = BAT_STATE_VOL_HIGH;
        }
    }
    else
    {
        vol_high_tcnt = 0u;
    }

    /* Battery voltage high recover check */
    if(BAT_STATE_VOL_HIGH == Batstate)
    {
        if(voltage < BAT_VOL_HIGH_RECOVER_VALUE)
        {
            vol_high_recover_tcnt++;
            if(vol_high_recover_tcnt > BAT_VOL_HIGH_RECOVER_TIME_VALUE)
            {
                vol_high_recover_tcnt = 0u;
                Batstate = BAT_STATE_VOL_NORMAL;
            }
        }
        else
        {
            vol_high_recover_tcnt = 0u;
        }
    }
    else
    {
        vol_high_recover_tcnt = 0u;
    }

    /* Battery voltage low check */
    if(voltage < BAT_VOL_LOW_VALUE)
    {
        vol_low_tcnt++;
        if(vol_low_tcnt > BAT_VOL_LOW_TIME_VALUE)
        {
            vol_low_tcnt = BAT_VOL_LOW_TIME_VALUE;
            Batstate = BAT_STATE_VOL_LOW;
        }
    }
    else
    {
        vol_low_tcnt = 0u;
    }

    /* Battery voltage low recover check */
    if(BAT_STATE_VOL_LOW == Batstate)
    {
        if(voltage > BAT_VOL_LOW_RECOVER_VALUE)
        {
            vol_low_recover_tcnt++;
            if(vol_low_recover_tcnt > BAT_VOL_LOW_RECOVER_TIME_VALUE)
            {
                vol_low_recover_tcnt = 0u;
                Batstate = BAT_STATE_VOL_NORMAL;
            }
        }
        else
        {
            vol_low_recover_tcnt = 0u;
        }
    }
    else
    {
        vol_low_recover_tcnt = 0u;
    }
#endif
}
#endif


/* ======================================================================================================= */
void Ecum_Wakeup_Mode_Switch(void)
{
	Ecum_Wakeup_Condition_Clear();
	Ecum_Wakeup_Timeout_Clear();
	Ecumstate = ECUM_STATE_WAKEUP;
}

/* ======================================================================================================= */
void Ecum_Pre_Sleep_Mode_Switch(void)
{
	Ecum_Pre_Sleep_Condition_Clear();
	Ecumstate = ECUM_STATE_PRE_SLEEP;
}

static void Ecum_Lin_Bus_Sleep_Check(void)
{
    if(lin_network_sleep_state_get())
    {
        //bsc_FailStop();
    }
}

