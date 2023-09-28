
/*******************************************************************************
|  File Name:    apfunc.h
|  Description:  Antipinch Action header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef APFUNC_H_
#define APFUNC_H_
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
	uint8_t		u8_APCnt;	//save data
}APF_Save_t;

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
Name			: APF_Init
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
void APF_Init(void);

/*******************************************************************************
Name			: APF_Judge
Syntax			:void APF_Judge(void)
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
void APF_Judge(void);


void APF_2ms_Job(void);


bool_t APF_TstAPRdyFlg(void);
bool_t APF_TstAPOffFlg(void);
bool_t APF_TstInRev(void);
uint8_t APF_SaveData(uint8_t* buf);
void APF_RestoreData(uint8_t* const buf);

void SCI0_Send_Packet(uint8_t *ptr, uint8_t length);

#endif
