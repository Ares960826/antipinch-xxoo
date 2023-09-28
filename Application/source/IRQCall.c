/*
 * IRQCall.c
 *
 *  Created on: Mar 27, 2021
 *      Author: wyanw003
 */


#include "xl_ftm.h"
#include "OS.h"
#include "xl_adc.h"
#include "xl_irq.h"
#include "debug.h"
#include "AppIF.h"
#include "Mcu.h"
#include "Hallpos.h"
#include "lowpower.h"
#include "switch.h"
bool_t	g_bl_NewHPWFlg=0;
volatile bool_t g_bl_HSPEEDSts=0;

//IRQ of SysTick
void SysTick_Handler(void){
	++os_tick_count;
}


//static uint8_t s_u8FTM1OverFlag = 0;
//channel5 -> channel1 -> C1v
static uint16_t s_uBothEdgeHitCnt = 0;
static uint16_t s_uPreCnt = 0;
//static uint32_t s_u1stEdgeDiffTick = 0;
//static uint32_t s_u2ndEdgeDiffTick = 0;

typedef enum
{
    FTM_INPUT_INITSTATE = 0u,
	FTM_INPUT_1STSTATE,
	FTM_INPUT_2NDSTATE,
	FTM_INPUT_NUM
}FTM_INPUT_STATE;


//IRQ of FTM
void FTM1_IRQHandler(void)
{
	uint8_t uctemp;

	//if channel event
	if(FTM_GetChannelFlag(FTM1, FTM_CHANNEL0))
	{
		//EachTime Entered , add the HitCnt(RisingEdge/FallingEdge)
	  for (uctemp=40;uctemp>0;--uctemp) 			//Ïû³ýÒì³£µÄhallÐÅºÅ
	  {
		 if (g_bl_HSPEEDSts == bsc_Get_HALL_SPD_Stat())
		 {
			break;
		 }
	  }


	  if (uctemp == 0)
	  {//Õý³£µÄhallÐÅºÅ

		 uint16_t u16C1V = 0;
		 u16C1V=FTM_GetChannelValue(FTM1, FTM_CHANNEL0);   //¼ÆÊ±Öµ¶ÁÈë
		 s_uBothEdgeHitCnt = u16C1V - s_uPreCnt;
		 s_uPreCnt=u16C1V;
		 g_bl_NewHPWFlg = 1;               //ÊÕµ½hallÖÐ¶Ï
		 g_bl_HSPEEDSts = bsc_Get_HALL_SPD_Stat();

	  }
	  else
	  {
			//hall Peak

	  }


		FTM_ClrChannelFlag(FTM1,FTM_CHANNEL0);

	}

}


uint16_t getBothEdgeCounter(){
	//get cnt
	return s_uBothEdgeHitCnt;
}


void EXTI8_IRQHandler(void)
{
	__disable_irq();
	if(IRQ_GetFlag(IRQ,EXTI8)){

			bsc_FeedCOP();//20210807

		    Lowpower_ClearSleepSts();
			//init the mcu
			Mcu_Init();
			//POWER_DET_EN
			bsc_HS_PowerPin1Op(1);
			key_init_st();
			KeyPort_Init();
			//start the watch dog
			WDOG_Configuration(WDOG_STAT_RUNNING);
		//at last , clear the interrupt flag
			IRQ_ClrFlag(IRQ,EXTI8);


	}
	__enable_irq();
}

//PTA2 LIN wake
void EXTI2_IRQHandler(void)
{
	//Need to do
	//awake the system
	__disable_irq();
	if(IRQ_GetFlag(IRQ,EXTI2)){

			bsc_FeedCOP();//20210807

		    Lowpower_ClearSleepSts();
			//init the mcu
			Mcu_Init();
			//POWER_DET_EN
			bsc_HS_PowerPin1Op(1);
			key_init_st();
			KeyPort_Init();
			//start the watch dog
			WDOG_Configuration(WDOG_STAT_RUNNING);
		//at last , clear the interrupt flag
			IRQ_ClrFlag(IRQ,EXTI2);


	}
	__enable_irq();
}

#define ADC_COUNT (7)

static uint16_t s_uDownAD = 0;
uint16_t getDwonIPAD(){
	return s_uDownAD;
}

//get vehicle enable AD
static uint16_t s_uVehicleEnableAD = 0;
uint16_t getVehicleEnableAD(){
	return s_uVehicleEnableAD;
}

static uint16_t s_uExpIPAD = 0;
uint16_t getExpIPAD(){
	return s_uExpIPAD;
}
//get key AD
static uint16_t s_uKeyAD = 0;
uint16_t getKeyAD(){
	return s_uKeyAD;
}

static uint16_t s_uBattAD = 0;
uint16_t getBattAD(){
	return s_uBattAD;
}

static uint16_t s_uRelayDownAD = 0;
uint16_t getRelayDownAD(){
	return s_uRelayDownAD;
}

static uint16_t s_uRelayUpAD = 0;
uint16_t getRelayUpAD(){
	return s_uRelayUpAD;
}

static uint16_t s_uTempsensorAD = 0;
uint16_t getThermalAD(){
	return s_uTempsensorAD;
}

void ADC0_IRQHandler(void)
{
	//fifosize
	uint16_t ufifoSize = ADC_GetFIFOValueCounter(ADC0);

	//exception
	if(ufifoSize != ADC_COUNT) {
		return ;
	}


	s_uDownAD = ADC_GetConversionValue(ADC0);


	//VEHICLE_ENABLE_AD -> ADC_SE6
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD4);
	//s_uVehicleEnableAD = ADC_GetConversionValue(ADC0);

	s_uExpIPAD = ADC_GetConversionValue(ADC0);

	//KEY_AD -> ADC_SE6
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD6);
	s_uKeyAD = ADC_GetConversionValue(ADC0);

	//BATT_AD -> ADC_SE8
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD8);
	s_uBattAD = ADC_GetConversionValue(ADC0);

	//RelayDown -> ADC_SE10
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD10);
	s_uRelayDownAD = ADC_GetConversionValue(ADC0);

	//RelayUp -> ADC_SE11
	//ADC_SetChannel(ADC0,ADC_CHANNEL_AD11);
	s_uRelayUpAD = ADC_GetConversionValue(ADC0);

	//?? -> ADC_TEMPSENSOR
	//ADC_SetChannel(ADC0,ADC_CHANNEL_TEMPSENSOR);
	s_uTempsensorAD = ADC_GetConversionValue(ADC0);

}


