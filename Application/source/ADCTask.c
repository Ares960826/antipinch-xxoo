/*
 * AppLed.c
 *
 *  Created on: 2021Äê3ÔÂ25ÈÕ
 *      Author: shenh4
 */

/* ======================================================================================================= */
#include <ADCTask.h>
#include <EcumTask.h>
#include "Debug.h"
#include "xl_adc.h"
#include "AppIF.h"

void Task_ADC_Handler(void)
{
	//uint16_t tmp=0;
	//set the ChannelSet
	//Down IP AD -> ADC_SE3
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD3);


	//VEHICLE_ENABLE_AD -> ADC_SE4
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD4);

	//Exp. IP AD -> ADC_SE3
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD5);

	//UP IP _AD -> ADC_SE6
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD6);
	//BATT_AD -> ADC_SE8
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD8);
	//RelayDown -> ADC_SE10
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD10);
	//RelayUp -> ADC_SE11
	ADC_SetChannel(ADC0,ADC_CHANNEL_AD11);
	//?? -> ADC_TEMPSENSOR
	ADC_SetChannel(ADC0,ADC_CHANNEL_TEMPSENSOR);

	//tmp = bsc_AD_Get_Raw_Bat();

    //Debug("Battery[%d]\n",(uint8_t)((tmp*173+700)/1000));

    //Debug("UpEnableFD[%d]\n",bsc_Relay_AfeedbackIp());
    //Debug("UDownEnableFD[%d]\n",bsc_Relay_BfeedbackIp());

    //Debug("KeyEnableFD[%d]\n",bsc_Get_KeyIp());
    //Debug("Thermal[%0.1f]\n",bsc_AD_Get_Raw_Thermal());
}
