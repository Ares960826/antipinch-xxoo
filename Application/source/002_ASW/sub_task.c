/*******************************************************************************
|  File Name:    Task.c
|  Description:  Task schedule
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
|
|******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
//#include "001_ComHeader\Typedef.h"
//#include "Pit.h"
#include "Typedef.h"
#include "sysfunc.h"
#include "Ubat.h"
#include "switch.h"
#include "motor.h"
#include "relay.h"
#include "hallpos.h"
//#include "lincomp_Tle9842.h"
#include "LinDcm.h"
#include "002_ASW\sub_task.h"
#include "Debug.h"
#include "AppIF.h"
#include "xl_gpio.h"
#include "AppLin.h"
#include "thermo.h"
#include "apfunc.h"
#include "testmode.h"
#include "syst_security.h"
#include "aplib.h"
#include "FlashApManage.h"
#include "KeyPort.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static void LinTask2Ms(void);
static void LinTask10Ms(void);

extern void window_stop(void);

extern bool_t cheksum_bool;
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

void APP_1ms_Task(void)
{
	
}

void APP_2ms_Task(void){
	LinTask2Ms();


    if(!TM_bi_beingTestMode)
    {
   	  if (1) //(TM_bi_HWEntryAccess)
   	  TM_Entry();     	        /*²âÊÔÄ£Ê½Èë¿Ú*/
    }
    else
    {
      TM_Progress();		       	/*²âÊÔÄ£Ê½*/
    }

	KeyPort_2msTask();
	MOT_2ms_Job();
	Ubat_2ms_Job();
	APF_2ms_Job();
	APL_2ms_Task();
	KeyPort_Prev();
	
	key();
	KeyPort_After();
	KEY_UpdateInfoData();

	FlashAP_task_WriteApData();  //lihui  add a 2ms period task for AP data writing

}

void APP_10ms_Task(void){
	
	LinTask10Ms();
	HP_10ms_Job();
	REL_10ms_Job();

	KeyPort_10msTask();
	SY_RamCtlUpdate();

}

void APP_50ms_Task(void){
	thermo_50msjob();
	SY_RamCtlCheck();
	if((SY_uc_StatusRAMStack&0x05) >0)
	{
		window_stop();
		for(;;)
		{}
	}
}

volatile static unsigned int uCount = 0;
void APP_100ms_Task(void){
	SYS_Sleep();
}

void APP_5s_Task(void)
{
	HP_5s_Job();
	//bsc_FailStop();
}

void APPBackGroundTask(void)
{
	if( cheksum_bool == TRUE)
	{
		Ubat_Task();
		HP_Task();
		APF_Judge();
		MOT_Task();
		RT_relaytest();		//�̵���
		RT_OtherTestDataLoad();
		key_checkstop();
	}
}

static void LinTask2Ms(void)
{
	//l_irqmask lin_irqState = 0U;
	//lin_irqState = l_sys_irq_disable();
	//ld_task();
    //DcmMainFunction();
	//l_sys_irq_restore(lin_irqState);
}

static void LinTask10Ms(void)
{
	/*	Lin NetWork Status Check
	 * 	This function must be run in a period defined by LINCHK_PERIOD
	 */

	uint16_t tmpTimecnt;
	uint8_t  bLinSts;
	bLinSts = lin_network_state_get();
	tmpTimecnt = l_GetLinIdleCnt();

	if(bLinSts >0){

		if ((tmpTimecnt == (AppLINIDLE_MAX+20)) ){
			SYS_ClrWakeSrc(C_ALIVE_LINF);  //sleep commmand
			LA_bi_PWLOpEnb1 = 0;
		}
		else if (AppLINIDLE_MAX  ==  tmpTimecnt)
		{


			SYS_ClrWakeSrc(C_ALIVE_LINF);

		}

	}else
	{

		if(SY_uc_poweron > 0 )
		{
			SY_uc_poweron--;
		}

		SYS_SetWakeSrc(C_ALIVE_LINF);


	}



}


