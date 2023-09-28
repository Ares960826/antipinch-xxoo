/*
 * AppIF.c
 *
 *  Created on: Mar 27, 2021
 *      Author: wyanw003
 */
#include "Typedef.h"
#include "lin.h"
#include "xl_adc.h"
#include "002_ASW/sub_task.h"
#include "xl_gpio.h"
#include "IRQCall.h"
#include "flash_eeprom.h"
#include "lowpower.h"
#include "IRQCall.h"
#include "Debug.h"
#include "xl_wdog.h"
#include "lin.h"
#include "AppIF.h"

uint8_t  lin_appif_status_feedback=0;
extern uint8_t lin_master_request_sleep;
uint16_t Lin_appif_u16_IdleCnt=0;
/*
bool_t PIT_Tst1MsFlg(void){
	return getTst1MsFlg();
}
void PIT_Clr1MsFlg(void){
	bool_t bClear = 0;
	setTst1MsFlg(bClear);
}
*/


/*
 *  Inner func , controls the GPIO
 *  PullUp   -> 1
 *  PullDown -> 0
 */
void setGPIOSignalLevel(bool_t bPullUp,uint8_t uGPIOEnum) {
	if(bPullUp) {
		GPIO_SetPin(uGPIOEnum);
	}
	else {
		GPIO_ClrPin(uGPIOEnum);
	}
}

/*
 * Enable the POWER_DET -> Enable
 * 1: High -> enable
 * 0: Low  -> disable
 */
void bsc_HS_PowerPin1Op(bool_t OutputVal){
	//PTD1
	setGPIOSignalLevel(OutputVal,GPIO_PTD1);
}

/*
 *
 *  Get the Vehicle Enable ADValue
 *  Voltage refers to VDDA
 *  returnValue -> ADValue
 */
uint16_t bsc_AD_Get_Vehicle_Enable(void){
	//AD4
	return getVehicleEnableAD();
}


/*
 *  After POWER_DET -> Enable , FeedBack will come
 *  Get the BATT ADValue
 *  Voltage refers to VDDA
 *  returnValue -> voltage feedback
 */
uint16_t bsc_AD_Get_Raw_Bat(void)
{
	//AD8
	return getBattAD();
}

/*
 * Enable the Relay -> UpEnable
 * 1: High -> enable
 * 0: Low  -> disable
 */
void bsc_LS_RelayPinA(bool_t OutputVal){
	//set Up_EN PTE1
	setGPIOSignalLevel(OutputVal,GPIO_PTE1);
}

/*
 * Enable the Relay -> DownEnable
 * 1: High -> enable
 * 0: Low  -> disable
 */
void bsc_LS_RelayPinB(bool_t OutputVal){
	//set Up_EN PTE0
	setGPIOSignalLevel(OutputVal,GPIO_PTE0);
}

/*
 *  After Relay -> UpEnable , FeedBack will come
 *  Get the RelayUp ADValue
 *  Voltage refers to VDDA
 *  return will be the voltage feedback
 */
uint16_t bsc_Relay_AfeedbackIp(){
	//AD11
	return getRelayUpAD();
}

/*
 *  After Relay -> DownEnable , FeedBack will come
 *  Get the RelayDown ADValue
 *  Voltage refers to VDDA
 *  returnValue -> voltage feedback
 */
uint16_t bsc_Relay_BfeedbackIp(){
	//AD11
	return getRelayDownAD();
}


/*
 * Get the HALL SPD Counter
 * return the bothedge that happened in hallSensor
 *
 * PS:the counter will be reset to zero , after this func is called
 */
uint16_t bsc_Get_HALL_SPD_Counter(void)
{
	//get the counter
	return getBothEdgeCounter();
}

/*
 * Get the HallSpd pin level(FTM -> GPIO)
 * 1: High
 * 0: Low
 */
bool_t   bsc_Get_HALL_SPD_Stat(void)
{
	//receive Hall_Speed PTH2
	return (GPIO_ReadPin(GPIO_PTH2) == GPIO_Input_High);
}

/*
 * Get the HallDir pin level
 * 1: High
 * 0: Low
 */
bool_t   bsc_Get_HALL_DIR_Stat(void){
	//receive Hall_DIR PTE7
	return (GPIO_ReadPin(GPIO_PTE7) == GPIO_Input_High);
}


uint16_t bsc_Get_EnIp(void){
	//forgot the map...
	return (GPIO_ReadPin(GPIO_PTB0));
	//return 0;
}

/*
	//App Not Use
	void bsc_HS_PowerPin1Op(bool_t OutputVal){
		//PTA5
		setGPIOSignalLevel(OutputVal,GPIO_PTA5);
	}
*/


/*
uint16_t bsc_Get_UpIp(void){
	//forgot the map...
	return 0;
}

uint16_t bsc_Get_ExIp(void){
	//forgot the map...
	return 0;
}

uint16_t bsc_Get_EnIp(void){
	//forgot the map...
	return 0;
}

uint16_t bsc_Get_DnIp(void){
	return 0;
}
*/
/*
 *	extern uint16_t bsc_Get_UpIp(void);
 *	extern uint16_t bsc_Get_ExIp(void);
 *	extern uint16_t bsc_Get_EnIp(void);
 *	extern uint16_t bsc_Get_DnIp(void);
 *  All func above , will turn to the func below
 *  Get the key AD Value
 *  Voltage refers to VDDA
 *  returnValue -> voltage feedback
*/
uint16_t bsc_Get_KeyIp(void){
	//return the keyAD
	return getKeyAD();
}


/*
 *  Inner Thermal Chip
 *  Get the Thermal ADValue
 */
float bsc_AD_Get_Raw_Thermal(void){
	uint16_t tmp;
	//ADC:12bit -> 10bit
	int32_t sensorValue1 = (getThermalAD() << 2);
	//Debug("sensorValue1[%d] \n",sensorValue1);
	//float votage =  (float)(sensorValue1*1.2210);
	int32_t votage =  (sensorValue1*61/50);

	float temperature = 0.0;

	if(votage > 664u)
	{
		//temperature =428.2 - votage * 0.607;
		temperature =(( 428200 - votage * 607)+500)/1000;
	}
	else
	{
		//temperature = 384.667 - votage * 0.5461;
		temperature = ((384667 - votage * 546)+500)/1000;
	}
	tmp=temperature+50;
	Debug("temp[%f] \n",tmp);
	//float -> uint16_t..... dangerous
	return tmp;
}

/*
 * E2Prom write , write 1Byte once
 * Time cost: 81us  (Page not flip)
 *            10.3ms(Page flip)
 * Use the simulator course
 */
bool_t Api_EepromWrite(uint16_t u16_P_DataID,uint8_t u8_P_DataOffset,uint8_t u8_P_ByteLen,const uint8_t * CP_P_DataBuffer){
	//exception
	//if len > 1 -> failure
	if(u8_P_ByteLen > 1){
		return 0u;
	}

	// but only 1Byte can be written once...
	EFLASH_STATUS eStatus = EEflash_Write_1Byte(u16_P_DataID,(uint8_t)*CP_P_DataBuffer);
	// if page changes...
	if(eStatus >= EFLASH_WARNING_COVER_PAGE0)
	{
		//change will cost 10ms...
		EEflash_Change_Page(eStatus);
	}
	//return success/failure
	return (eStatus == EFLASH_ERROR_SUCCESS)?(1u):(0u);
}

/*
 * E2Prom read , read 1Byte once
 * Use the simulator course
 */
bool_t Api_EepromRead(uint16_t u16_P_DataID,uint8_t u8_P_DataOffset,uint8_t u8_P_ByteLen,uint8_t * const CP_P_DataBuffer){
	// but only 1Byte can be read once...
	*CP_P_DataBuffer = EEflash_Read_Data(u16_P_DataID);
	return 1u;
}

/*
 *  Get the reset reason
 *  bit10: (SysReset Req) ? 1:0
 *  bit7 : (POR) ? 1:0
 *  bit6 : (PIN) ? 1:0
 *  bit5 : (WDG) ? 1:0
 *  bit1 : (LVD) ? 1:0
 *  bit0 : (ECC) ? 1:0
 *
 */
uint32_t bsc_Pmu_GetResetStatus(void){
	//get the rst causes
	return SIM->SRSID;
}
void bsc_Pmu_ClrResetStatus(void){
	//get the rst causes
	SIM->SRSID |=0x80;

}

/*
 *  chaoda add here
 */
bool_t eeprom_TstLinFlg(void){
	//lin...
	return LINFrameDetectedFlg;
}

/*
 *  chaoda add here
 */
void   eeprom_ClrLinFlg(void){
	//lin...
	LINFrameDetectedFlg = 0u;
	return;
}

/*
 *  Feed Dog
 */
void   bsc_FeedCOP(void){
	WDOG_CountRestart(WDOG);
	return;
}

/*
 *  Go to sleep mode
 */
void bsc_FailSleep(void){
	//enter sleep mode
	Enter_Stop();
	return;
}

/*
 *  Go to stop mode
 */
void bsc_FailStop(void){
	//enter stop mode
	Enter_Stop();
	return;
}


Lin_Status lin_network_state_get(void)
{
    uint8_t uStatue;
    Lin_Status rt;
    rt =FALSE;
    uStatue = lin_lld_get_state();

    if(uStatue == IDLE)
    {
        rt = LIN_IDLE;

        Lin_appif_u16_IdleCnt +=AppIF_lin_CHEKCPERIOD;
    }
    else
    {
    	Lin_appif_u16_IdleCnt=0;
    }
    if((uStatue == SLEEP_MODE) || (uStatue == UNINIT)||(Lin_appif_u16_IdleCnt>=(AppLINIDLE_MAX+20)))
    {
        if(lin_master_request_sleep)
        {
            rt = LIN_MASTER_REQUEST_SLEEP;
        }
        else
        {
            rt = LIN_IDLE_TIMEOUT_SLEEP;
        }
        Lin_appif_u16_IdleCnt=AppLINIDLE_MAX+20;

    }
    else
    {
    	if((Lin_appif_u16_IdleCnt >= AppLINIDLE_MAX))
		{
			/*	Idle Counter overflow or Receive Go Sleep Command	*/
    		Lin_appif_u16_IdleCnt = AppLINIDLE_MAX;

    		rt = TRUE;
		}
		else
		{
			rt = FALSE;
		}

    }
    lin_appif_status_feedback=rt;
    return rt;
}


// Huangh Get Idle time (unit ms)
uint16_t l_GetLinIdleCnt(void)
{
	return Lin_appif_u16_IdleCnt;
}
void l_SetLinIdleCnt(uint16_t u16_app_cnt)
{
	Lin_appif_u16_IdleCnt = u16_app_cnt;

}
