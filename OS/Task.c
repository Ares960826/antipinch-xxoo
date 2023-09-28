/*
 * Task.c
 *
 *  Created on: 2021年3月25日
 *      Author: shenh4
 */

/* =================================================================================== */
/* Include related head files */
#include <ADCTask.h>
#include <EcumTask.h>
#include <WDGTask.h>
#include "Task.h"
#include "OS.h"
#include "AppLin.h"
#include "002_ASW\sub_task.h"
/*
#include "Mcu.h"
#include "App_touch.h"
#include "App_led.h"
#include "App_adc_dac.h"

#include "App_haptic.h"
#include "App_SensorMan.h"
#include "App_eeprom.h"
#include "DMA_abstract.h"
#include "App_scroll.h"
#include "App_heating.h"
#include "FunctionSafety.h"
*/

/* =================================================================================== */
extern char Os_Message_Get(uint8_t task_id, uint8_t *msg_buffer);
/* =================================================================================== */
const os_task_config_type os_task_config_table[TASK_ID_MAX_NUM] =
{

    {Task_ID_Ecum,            2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    Task_Ecum_Message_Handler},           {Task_ID_Ecum_Event,             0u,      OS_Period_1000ms,      Task_Ecum_Handler},       {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_Lin,             2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    Task_Lin_Message_Handler},            {Task_ID_Lin_Event,              0u,      OS_Period_5ms,      	 Task_Lin_Handler},        {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
    {Task_ID_ADC,             2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    Task_ADC_Message_Handler},            {Task_ID_ADC_Event,              0u,      OS_Period_2ms,      	 Task_ADC_Handler},        {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_WDG,             2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    Task_WDG_Message_Handler},            {Task_ID_WDG_Event,              0u,      OS_Period_10ms,		 Task_WDG_Handler},        {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_1MS_TASK,    2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},            					{Task_ID_APP_1MS_Event,          0u,      OS_Period_1ms,         APP_1ms_Task},            {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_2MS_TASK,    2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},            					{Task_ID_APP_2MS_Event,          1u,      OS_Period_2ms,         APP_2ms_Task},            {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_10MS_TASK,   2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},            					{Task_ID_APP_10MS_Event,         0u,      OS_Period_10ms,        APP_10ms_Task},           {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_50MS_TASK,   2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},            					{Task_ID_APP_50MS_Event,         2u,      OS_Period_50ms,        APP_50ms_Task},           {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_100MS_TASK,  2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},         						{Task_ID_APP_100MS_Event,        4u,      OS_Period_100ms,       APP_100ms_Task},          {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
	{Task_ID_APP_5S_TASK,     2u,   {{Task_ID_Message_Event,   0u,   OS_Event,    NULL},            					{Task_ID_APP_5S_Event,           6u,      OS_Period_5000ms,      APP_5s_Task},             {Task_ID_Event_Nan,     0u,      0u,      NULL},    {Task_ID_Event_Nan,     0u,      0u,      NULL}}},
};

/* =================================================================================== */
void Task_Ecum_Message_Handler(void)
{
    /* message handler */
    uint8_t message_data[3u] = {0u};

    (void)Os_Message_Get(Task_ID_Ecum, message_data);
}

/* =================================================================================== */
void Task_Lin_Message_Handler(void)
{
    /* message handler */
    uint8_t message_data[3u] = {0u};

    (void)Os_Message_Get(Task_ID_Lin, message_data);
}

/* =================================================================================== */
void Task_ADC_Message_Handler(void)
{
    /* message handler */
    uint8_t message_data[3u] = {0u};

    (void)Os_Message_Get(Task_ID_ADC, message_data);
}

/* =================================================================================== */
void Task_WDG_Message_Handler(void)
{
    /* message handler */
    uint8_t message_data[3u] = {0u};

    (void)Os_Message_Get(Task_ID_WDG, message_data);
}

/* =================================================================================== */


/* =================================================================================== */
/* [] END OF FILE */
