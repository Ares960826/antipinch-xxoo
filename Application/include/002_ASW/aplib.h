
/*******************************************************************************
|  File Name:    aplib.h
|  Description:  Antipinch Action header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef APLIB_H_
#define APLIB_H_
#include "Typedef.h"
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/
typedef struct{
	uint16_t		data[44];	//save data
}APL_Save_t;

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
Name			: APL_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: AP Function Init
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APL_Init(void);	//QUESTION: ²»´æÔÚ
void ini_adapt(void); //CHANGE TO POR ZAP 20210706
/*******************************************************************************
Name			: APL_Task
Syntax			:void APL_Task(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: judge ap condition
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APL_2ms_Task(void);
void APL_InitData(void);
void APL_MotSts(uint8_t voltage,bool_t run, bool_t dir,bool_t dirprv);
void APL_PosSts(bool_t sealarea, bool_t protectarea );
bool_t APL_Calc( uint16_t pos, uint16_t hpw);
uint8_t APL_SaveData(uint8_t* buf);
void APL_RestoreData(uint8_t* const buf);

uint8_t APL_GetInfo(void);
uint8_t APL_GetInfo2(void);
uint8_t APL_GetFlag(void);
#endif
