
/*******************************************************************************
|  File Name:    motor.h
|  Description:  define task
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
|
|******************************************************************************/
#ifndef MOTOR_H
#define MOTOR_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Typedef.h"
#include "complier_sw.h"
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/
typedef struct{
	union														//save
	{
		uint8_t Ubyte;
		struct
		{
			uint8_t bl_MotPrvUp	: 1;
			uint8_t bl_MotRun	: 1;
			uint8_t bl_MotUp	: 1;
			uint8_t bl_MotOpen	: 1;
			uint8_t bl_MotClose	: 1;
			uint8_t bl_MotStop	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;	
}MOT_Save_t;
//extern _Init_SAVE_RAM  MotorData;
typedef struct{
	uint16_t	u16_CtrlUp;
	uint16_t	u16_CtrlDown;
	uint16_t	u16_CtrlStop;

	uint16_t	u16_StopDelay;
	uint16_t	u16_StopPosition;

	union														//save
	{
		uint8_t Ubyte;
		struct
		{
			uint8_t bl_MotPrvUp	: 1;
			uint8_t bl_MotRun	: 1;
			uint8_t bl_MotUp	: 1;
			uint8_t bl_MotOpen	: 1;
			uint8_t bl_MotClose	: 1;
			uint8_t bl_MotStop	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;

}MotorData_t;
extern _Init_SAVE_RAM  MotorData_t MotorData;
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/
void MOT_Init(void);
void MOT_2ms_Job(void);
void MOT_Task(void);
void MOT_SetUp(uint16_t prio);
void MOT_ClrUp(uint16_t prio);
void MOT_SetDn(uint16_t prio);
void MOT_ClrDn(uint16_t prio);
void MOT_SetStop(uint16_t prio);
void MOT_ClrStop(uint16_t prio);
uint16_t MOT_GetStopCause(void);
void Motor_DIRA(void);
void Motor_DIRB(void);
void Motor_OFF(void);
void Motor_BLOCK(void);

uint16_t MOT_GetStopPosition(void);
void MOT_SetMotStopDelay2ms(uint16_t delaytime);

bool_t MOT_TstAPMotStopDelay(void);
bool_t		MOT_TstMotorUpFlg(void);
bool_t		MOT_TstMotorRunFlg(void);
bool_t		MOT_TstMotorPrvUpFlg(void);
bool_t		MOT_TstMotorOpenFlg(void);
bool_t		MOT_TstMotorCloseFlg(void);
bool_t		MOT_TstMotorStopFlg(void);
uint16_t MOT_GetMotDelay(void);

uint8_t MOT_SaveData(uint8_t* buf);
void MOT_RestoreData(uint8_t* buf);

#endif
