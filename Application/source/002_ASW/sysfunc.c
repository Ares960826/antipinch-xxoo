
/*******************************************************************************
|  File Name:    Pit.c
|  Description:  Period Interrupt source file
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
#include "sysfunc.h"
#include "hallpos.h"
#include "motor.h"
#include "Ubat.h"
#include "aplib.h"
#include "apfunc.h"
#include "AppIF.h"

#include "switch.h"
#include "keyport.h"
#include "FlashApManage.h"
#include "flash.h"
#include "lin_lld_uart.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define C_T_1S		10u
#define C_T_2S		20u

#define C_T_20S		200u
#define C_T_19S		190u
#define C_T_16S		160u

#define	ENABLE_INACTIVE					1u
#define SIZE_DATA  sizeof(HP_Save_t)+sizeof(BAT_Save_t)+sizeof(MOT_Save_t)+sizeof(APL_Save_t) // keyport
	
/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

static uint16_t g_u16_WakeSrc;
static uint8_t	g_u8_SleepCnt;
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
Name			: SYS_Init
Syntax			: void SYS_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init System Variable
Requirement		: None
Call By			: MCU Interrupt Controller
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_Init(void)
{
	g_u16_WakeSrc = 0u;
	g_u8_SleepCnt = C_T_1S;
}

/*******************************************************************************
Name			: SYS_SetWakeSrc
Syntax			: void SYS_SetWakeSrc(uint16_t src)
Parameters(in)	: Source of keep WAKE
Parameters(out) : None
Return value	: None
Description		: Set Global Flag bit of keepalive
Requirement		: None
Call By			: MCU Interrupt Controller
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_SetWakeSrc(uint16_t src)
{
	g_u16_WakeSrc |= src;
}

/*******************************************************************************
Name			: SYS_ClrWakeSrc
Syntax			: void SYS_ClrWakeSrc(uint16_t src)
Parameters(in)	: Source of keep WAKE
Parameters(out) : None
Return value	: None
Description		: Clear Global Flag bit of keepalive
Requirement		: None
Call By			: MCU Interrupt Controller
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void SYS_ClrWakeSrc(uint16_t src)
{
	g_u16_WakeSrc &= (src ^ C_VALID_ALIVE);
}



void SYS_DataRestore(void)
{
	
	/*uint8_t slen;
	bool_t bReadok;

	uint8_t tmp8_return;
	tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);


	if (tmp8_return == 1)
	{
		HP_RestoreData(&FlashAp_DataBuf[0]);
		slen = sizeof(HP_Save_t);
		BAT_RestoreData(&FlashAp_DataBuf[slen]);
		slen += sizeof(BAT_Save_t);
		MOT_RestoreData(&FlashAp_DataBuf[slen]);
		slen += sizeof(MOT_Save_t);
		APL_RestoreData(&FlashAp_DataBuf[slen]);
		slen +=sizeof(APL_Save_t);
	}*/
}
//?????zap
void SYS_DataSave(void)
{
	uint8_t slen;

	uint8_t buf[SIZE_DATA];

		slen = HP_SaveData(&buf[0]);
		slen+= BAT_SaveData(&buf[slen]);
		slen+= MOT_SaveData(&buf[slen]);
		slen+= APL_SaveData(&buf[slen]);
	
		//Api_EepromWrite(0u,0u,slen,buf);
	
}

/*******************************************************************************
Name			: SYS_Sleep
Syntax			: void SYS_Sleep()
Parameters(in)	: 
Parameters(out) : None
Return value	: None 
Description		: 
Requirement		: None
Call By			: MCU Interrupt Controller
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/

void SYS_Sleep(void)
{
	uint16_t tmp_time;
	if (MOT_TstMotorRunFlg()==FALSE)
	{
		if (g_u8_SleepCnt >0)
		{
			g_u8_SleepCnt--;
		}
		if (g_u8_SleepCnt == 0)
		{
			if(g_u16_WakeSrc==0)
			{
				/* if (HP_TstPosChangeFlg()==TRUE)
				 {
					//Flash AP data saving  just before the GoSleeping

					if(	(TRUE == FlashAP_fct_Chk_WrtState())
						&&(TRUE == FlashAP_fct_Chk_WrtEnable())
					  )  //lihui  saving AP dynamic parameters in Flash  2021-5-11  used in XL6600
					  {

							FlashAP_Initiate_Save();
							eeprom_ClrLinFlg();
							 //feed watchdog
							bsc_FeedCOP();
							tmp_time = 100;
							do
							{

								FlashAP_task_WriteApData();
								tmp_time--;
								if(TRUE == FlashAP_fct_Chk_WrtState())
								{
									tmp_time=0;
								}

							}while(tmp_time>0);

							if(TRUE==eeprom_TstLinFlg())
							{
								eeprom_ClrLinFlg();
								__disable_irq();
								lin_goto_idle_state();
								__enable_irq();
								FlashAP_Init();
								SYS_DataRestore();
							}

					 }
					HP_ClrPosChangeFlg();
				 }*/
				 if(bsc_Get_EnIp() && 	 (lin_lld_get_state()==SLEEP_MODE)||(lin_lld_get_state()==UNINIT)) //inactive
				 {
					//SLEEP
					bsc_FailSleep();
				 }
			}
			else
			{
				if (g_u8_SleepCnt < C_T_1S) g_u8_SleepCnt = C_T_1S;
			}
		}



	}
	else
	{
			g_u8_SleepCnt = C_T_20S;
	}
}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
