/**
  ******************************************************************************
  * @file     main.c
  * @author   software
  * @version  V3.0.0
  * @date     4-Jun-2019
  * @brief    This file provide function about pit firmware program 
  ******************************************************************************
  * @attention
	*
  * 2019 by Chipways Communications,Inc. All Rights Reserved.
  * This software is supplied under the terms of a license
  * agreement or non-disclosure agreement with Chipways.
  * Passing on and copying of this document,and communication
  * of its contents is not permitted without prior written
  * authorization.
  *
  * <h2><center>&copy; COPYRIGHT 2019 Chipways</center></h2>
  ******************************************************************************
  */
#include "xl_pit.h"
#include "xl_gpio.h"
#include "xl_sim.h"
#include "debug.h"
#include "system_XL6600.h"
#include <stdio.h>
#include "OS.h"
#include "Mcu.h"
#include "switch.h"
#include "complier_sw.h"
#include "appl_const.h"
#include "LinDcm_Cfg.h"
#include "testmode.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

bool_t cheksum_bool=FALSE;


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/**
 * @brief  mainº¯Êý
 */
//#define SOP_PRODUCT
int32_t main (void) 
{
	//Init Mcu
	Mcu_Init();
	//Init App
	App_Init();
	TM_init();
	key_init();
    /* Os Init */
    Os_Init();
    /* Os Start */
    #ifdef SOP_PRODUCT

	if((EE_CHKSUM == Get_EEChecksum()) && (SW_CustomerID == c_ee_Par_Customer) ) //ProductConfig.CustomerID )   //checksum by Comy
	{
		cheksum_bool = TRUE;
	}
	#else

	cheksum_bool = TRUE;//for test
	#endif

    Os_Schedule();
    //DeInit Mcu
    Mcu_Deinit();
    return 0;
}




/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if 0
void MCU_init(void)
{

}
#endif




