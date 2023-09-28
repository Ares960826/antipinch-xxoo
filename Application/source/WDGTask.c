/*
 * AppLed.c
 *
 *  Created on: 2021Äê3ÔÂ25ÈÕ
 *      Author: shenh4
 */

/* ======================================================================================================= */
#include <WDGTask.h>
#include "Debug.h"
#include "AppIF.h"
#include "xl_gpio.h"

void Task_WDG_Handler(void)
{
	//feeddog
	bsc_FeedCOP();
}
