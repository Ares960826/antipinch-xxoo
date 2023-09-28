/*
 * Mcu.h
 *
 *  Created on: 2021Äê3ÔÂ26ÈÕ
 *      Author: shenh4
 */

#ifndef APPLICATION_INCLUDE_MCU_H_
#define APPLICATION_INCLUDE_MCU_H_

#include "xl_adc.h"

//Mcu Init/Deinit
extern void Mcu_Init(void);
extern void Mcu_Deinit(void);

//App Init
extern void App_Init(void);

//Clock
extern void CLOCK_Configuration(void);
//NVIC
extern void NVIC_Configuration(void);
//FTM
extern void FTM1_Configuration(void);
//IRQ
extern void IRQ_Configuration(void);
//FLASH
extern void FLASH_Configuration(void);
//ADC
extern void ADC_Configuration(ADC_Type* ADCx);
//Lin
extern void LIN_Configuration(void);
//Wdog
typedef enum{
	WDOG_STAT_INIT = 0u,
	WDOG_STAT_RUNNING,
}WDOG_STATUS;
extern void WDOG_Configuration(WDOG_STATUS eStatus);

//SBC
extern void Configure_SBCModule(void);
//Relay
extern void Configure_RelayModule(void);
//HallSensor
extern void Configure_HallSensorModule(void);
//MainConnector
extern void Configure_MainConnectorModule(void);
//Debug
extern void Configure_Debug(void);

#endif /* APPLICATION_INCLUDE_MCU_H_ */
