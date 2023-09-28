
/*******************************************************************************
|  File Name:    Relay.h
|  Description:  define task
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
|
|******************************************************************************/
#ifndef RELAY_H
#define RELAY_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Typedef.h"
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/
typedef enum{
	REL_OFF = 0u,
	REL_ON
}RelOnOff_t;

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/
typedef enum{
	REL_A = 0u,
	REL_B
}Relx_t;

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/
void	REL_Init(void);
void 	REL_10ms_Job(void);

bool_t REL_TstRelAStuckFlg(void);
bool_t REL_TstRelBStuckFlg(void);

RelOnOff_t	REL_GetRelPhySts(Relx_t rel);
void	REL_SetRelALogiSts(RelOnOff_t status);
void	REL_SetRelBLogiSts(RelOnOff_t status);




#endif