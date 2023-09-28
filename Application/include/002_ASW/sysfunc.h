
/*******************************************************************************
|  File Name:    sysfunc.h
|  Description:  Period Interrupt header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef SYSFUNC_H_
#define SYSFUNC_H_
#include "Types.h"
#include "Typedef.h"

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/


#define HARDWARE_TEST
typedef enum {ON,OFF} OnOff_t;


/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/

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
Name			: SYS_Init
Syntax			: void SYS_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init System Variable
Requirement		: None
Call By			: application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_Init(void);


/*******************************************************************************
Name			: SYS_SetWakeSrc
Syntax			: void SYS_SetWakeSrc(uint16_t src)
Parameters(in)	: Source of keep WAKE
Parameters(out) : None
Return value	: None
Description		: Set Global Flag bit of keepalive
Requirement		: None
Call By			: application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_SetWakeSrc(uint16_t src);

/*******************************************************************************
Name			: SYS_ClrWakeSrc
Syntax			: void SYS_ClrWakeSrc(uint16_t src)
Parameters(in)	: Source of keep WAKE
Parameters(out) : None
Return value	: None
Description		: Clear Global Flag bit of keepalive
Requirement		: None
Call By			: application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_ClrWakeSrc(uint16_t src);

/*******************************************************************************
Name			: SYS_Sleep
Syntax			: void SYS_Sleep(void)
Parameters(in)	: 
Parameters(out) : None
Return value	: None
Description		: MCU sleep 
Requirement		: None
Call By			: application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_Sleep(void);

void SYS_DataRestore(void);
void SYS_DataSave(void);

#endif
