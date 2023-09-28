
/*******************************************************************************
|  File Name:    relay.c
|  Description:  relay stuck process
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Types.h"
#include "Typedef.h"
#include "AppIF.h"
#include "relay.h"
//#include "port_user.h"
#include "hallpos.h"
#include "motor.h"
#include "sysfunc.h"
//#include "adc1_user.h"
#include "switch.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/

extern void window_stop(void) ;
typedef struct{
	uint8_t	u8_TimeCnt;
	uint8_t	u8_StuckCnt;
	bool_t	bl_StuckFlg;
	RelOnOff_t	LogiSts;
	RelOnOff_t	PhySts;
}Relsts_t;

typedef struct{
	Relsts_t RelA;
	Relsts_t RelB;
	uint16_t	u16_MotorRunTime;
}RelayData_t;


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static void StuckCheck(Relsts_t* relsts,Relx_t rel);
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

static RelayData_t RelayData;

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
Name			: PIT_1MS_ISR
Syntax			: INTERRUPT void PIT_1MS_ISR(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 1Ms Period Interrupt(Use SysTick)
Requirement		: None
Call By			: MCU Interrupt Controller
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/


void	REL_Init(void)
{
	RelayData.RelA.LogiSts = REL_OFF;
	RelayData.RelB.LogiSts = REL_OFF;
	RelayData.RelA.bl_StuckFlg = FALSE;
	RelayData.RelB.bl_StuckFlg = FALSE;
	RelayData.RelA.u8_StuckCnt = 0;
	RelayData.RelB.u8_StuckCnt = 0;
	RelayData.RelA.u8_TimeCnt = 0;
	RelayData.RelB.u8_TimeCnt = 0;
	RelayData.u16_MotorRunTime = 0;
	
}

bool_t REL_TstRelAStuckFlg(void)
{
	return (RelayData.RelA.bl_StuckFlg);
}
bool_t REL_TstRelBStuckFlg(void)
{
	return (RelayData.RelB.bl_StuckFlg);
}
void	REL_SetRelALogiSts(RelOnOff_t status)
{
		RelayData.RelA.LogiSts = status;
}
void	REL_SetRelBLogiSts(RelOnOff_t status)
{
	RelayData.RelB.LogiSts = status;
}

RelOnOff_t REL_GetRelLogiSts(Relx_t rel)
{
	RelOnOff_t ret = REL_OFF;
	if (rel == REL_A)
	{
	
			ret = RelayData.RelA.LogiSts;
		
	}else if (rel == REL_B)
	{

			ret = RelayData.RelB.LogiSts;	

	}
	return ret;	

}

RelOnOff_t	REL_GetRelPhySts(Relx_t rel)
{
	RelOnOff_t ret = REL_OFF;
	if (rel == REL_A)
	{
		if (bsc_Relay_AfeedbackIp() > (bsc_AD_Get_Raw_Bat()/6 ))
		{
			ret = REL_ON;
		}
	}else if (rel == REL_B)
	{
		if (bsc_Relay_BfeedbackIp()> (bsc_AD_Get_Raw_Bat()/6 ))
		{
			ret = REL_ON;	
		}
	}
	return ret;
}


void REL_10ms_Job(void)
{
	RelayData.RelA.PhySts = REL_GetRelPhySts(REL_A);
	RelayData.RelB.PhySts = REL_GetRelPhySts(REL_B);
	
	if(MOT_TstMotorRunFlg()==FALSE)
	{
			StuckCheck(&RelayData.RelA,REL_A);
			StuckCheck(&RelayData.RelB,REL_B);

	}

	
	if (REL_TstRelAStuckFlg()||REL_TstRelBStuckFlg())
	{
			SYS_SetWakeSrc(C_ALIVE_RELAYSTICK);
	}else{
			SYS_ClrWakeSrc(C_ALIVE_RELAYSTICK);
	}
	
	//////////////////////motor run time check///////////////////////////
	if(MOT_TstMotorRunFlg())
	{
		if(RelayData.u16_MotorRunTime<3000U)	// = 30s 
		{
				RelayData.u16_MotorRunTime++;
				
		}else
		{
			window_stop();
			key_checkstop();
			HP_Normalize_ExitCall();
			RelayData.u16_MotorRunTime = 0U;
		}

	}else{
		RelayData.u16_MotorRunTime = 0U;
	}
}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
static void StuckCheck(Relsts_t* relsts,Relx_t rel)
{
	relsts->PhySts = REL_GetRelPhySts(rel);
	
	if( relsts->bl_StuckFlg == FALSE) 
	{
			if(relsts->LogiSts==REL_OFF) 
			{
					if(relsts->PhySts==REL_ON) 
					{
						if(relsts->u8_StuckCnt < 4)
						{
							relsts->u8_StuckCnt++;
						}
						if(relsts->u8_StuckCnt>3)
						{
								relsts->bl_StuckFlg = TRUE;  
								Motor_BLOCK();
								relsts->u8_StuckCnt=200;                 
								HP_Normalize_ExitCall();
						}
					} 
					else 
					{
						if(relsts->u8_StuckCnt>0) 	relsts->u8_StuckCnt--;
					}
			}
	}
	else
	{  
			if(relsts->u8_StuckCnt>0 )
			{
				relsts->u8_StuckCnt-- ;
			}
			else
			{
				if(relsts->u8_TimeCnt<3)
				{
					relsts->u8_TimeCnt++;
					Motor_OFF();
					relsts->bl_StuckFlg=FALSE;
				}
			}
	}
}

