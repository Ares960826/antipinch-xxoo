/*
 * Task.h
 *
 *  Created on: 2021Äê3ÔÂ25ÈÕ
 *      Author: shenh4
 */
#ifndef TASK_H
#define TASK_H
/* =================================================================================== */
//#include "project.h"
#include "typedef.h"

/* =================================================================================== */
#define     Os_Event_PerTask    4u

#define     OS_Event            0u
#define     OS_Period_1ms       1u
#define     OS_Period_2ms       2u
#define     OS_Period_4ms       4u
#define     OS_Period_5ms       5u
#define     OS_Period_10ms      10u
#define     OS_Period_20ms      20u
#define     OS_Period_50ms      50u
#define     OS_Period_100ms     100u
#define     OS_Period_250ms     250u
#define     OS_Period_1000ms    1000u
#define     OS_Period_5000ms    5000u


#ifndef	BIT0
	#define BIT0		0x01
	#define BIT1		0x02
	#define BIT2		0x04
	#define BIT3		0x08
	#define BIT4		0x10
	#define BIT5		0x20
	#define BIT6		0x40
	#define BIT7		0x80
	#define BIT8		0x0100
	#define BIT9		0x0200
	#define BIT10		0x0400
	#define BIT11		0x0800
	#define BIT12		0x1000
	#define BIT13		0x2000
	#define BIT14		0x4000
	#define BIT15		0x8000

	#define BIT_0		0x01
	#define BIT_1		0x02
	#define BIT_2		0x04
	#define BIT_3		0x08
	#define BIT_4		0x10
	#define BIT_5		0x20
	#define BIT_6		0x40
	#define BIT_7		0x80
	#define BIT_8		0x0100
	#define BIT_9		0x0200
	#define BIT_10		0x0400
	#define BIT_11		0x0800
	#define BIT_12		0x1000
	#define BIT_13		0x2000
	#define BIT_14		0x4000
	#define BIT_15		0x8000
#endif

/* =================================================================================== */
typedef void (*pfunct_Os)(void);

/* =================================================================================== */
typedef struct
{
    uint8_t task_event;
    uint16_t timer_offset;
    uint16_t timer_period;
	pfunct_Os task_ptr;
}os_event_config_type;

/* =================================================================================== */
typedef struct
{
	uint8_t task_id;
    uint8_t event_num;
    os_event_config_type notify_event[Os_Event_PerTask];
}os_task_config_type;

/* =================================================================================== */
/* define event list, BIT0 used to message event */
#define Task_ID_Event_Nan            0
#define Task_ID_Message_Event        BIT0
#define Task_ID_APP_1MS_Event        BIT1
#define Task_ID_APP_2MS_Event        BIT1
#define Task_ID_APP_10MS_Event       BIT1
#define Task_ID_APP_50MS_Event       BIT1
#define Task_ID_APP_100MS_Event      BIT1
#define Task_ID_APP_5S_Event         BIT1
#define Task_ID_Ecum_Event           BIT1
#define Task_ID_Haptic_Dma_Event     BIT1
#define Task_ID_ADC_Event            BIT1
#define Task_ID_Lin_Event            BIT1
#define Task_ID_WDG_Event            BIT1
#define Task_ID_Touch_Event          BIT1
#define Task_ID_Sensor_State_Event   BIT1
#define Task_ID_Adc_Dac_Event        BIT1
#define Task_ID_Led_Event            BIT1
#define Task_ID_Eeprom_Event         BIT1
#define Task_ID_Scroll_Event         BIT1
#define Task_ID_Haptic_Event         BIT1
#define Task_ID_Heating_Event        BIT1
#define Task_ID_FunctionSafety_Event BIT1

/* =================================================================================== */
/* define task list */
enum
{
    Task_ID_Ecum = 0,
	Task_ID_Lin,
    Task_ID_ADC,
	Task_ID_WDG,
	Task_ID_APP_1MS_TASK,
	Task_ID_APP_2MS_TASK,
	Task_ID_APP_10MS_TASK,
	Task_ID_APP_50MS_TASK,
	Task_ID_APP_100MS_TASK,
	Task_ID_APP_5S_TASK,
	TASK_ID_MAX_NUM,
};

/* =================================================================================== */
extern const os_task_config_type os_task_config_table[TASK_ID_MAX_NUM];

/* =================================================================================== */
extern void Task_Ecum_Message_Handler(void);
extern void Task_Lin_Message_Handler(void);
extern void Task_ADC_Message_Handler(void);
extern void Task_WDG_Message_Handler(void);
extern void Task_SLEEP_Message_Handler(void);
/* =================================================================================== */
#endif  /* TASK_H */
/* [] END OF FILE */


