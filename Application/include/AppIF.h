/*
 * AppIF.h
 *
 *  Created on: Mar 27, 2021
 *      Author: wyanw003
 */

#ifndef APPLICATION_INCLUDE_APPIF_H_
#define APPLICATION_INCLUDE_APPIF_H_
#define AppIF_lin_CHEKCPERIOD 10

typedef enum {
    LIN_IDLE,
    LIN_PROCESSING,
    LIN_MASTER_REQUEST_SLEEP,
    LIN_IDLE_TIMEOUT_SLEEP
}Lin_Status;

#define AppLINIDLE_MAX  3900

extern uint8_t lin_appif_status_feedback;
extern uint16_t Lin_appif_u16_IdleCnt;
/*
 * os schedule: 1ms callback will come, so not need anymore
   extern bool_t PIT_Tst1MsFlg(void);
   extern void PIT_Clr1MsFlg(void);
*/

/*
 * Enable the POWER_EN -> Enable
 * 1: High -> enable
 * 0: Low  -> disable
 */
extern void     bsc_HS_PowerPin1Op(bool_t OutputVal);

/*
 *
 *  Get the Vehicle Enable ADValue
 *  Voltage refers to VDDA
 *  returnValue -> ADValue
 */
extern uint16_t bsc_AD_Get_Vehicle_Enable(void);


/*
 *  After POWER_DET -> Enable , FeedBack will come
 *  Get the BATT ADValue
 *  Voltage refers to VDDA
 *  returnValue -> voltage feedback
 */
extern uint16_t bsc_AD_Get_Raw_Bat(void);

/*
 * Enable the Relay -> UpEnable
 * 1: High -> enable
 * 0: Low  -> disable
 */
extern void bsc_LS_RelayPinA(bool_t OutputVal);

/*
 * Enable the Relay -> DownEnable
 * 1: High -> enable
 * 0: Low  -> disable
 */
extern void bsc_LS_RelayPinB(bool_t OutputVal);

/*
 *  After Relay -> UpEnable , FeedBack will come
 *  Get the RelayUp ADValue
 *  Voltage refers to VDDA
 *  return will be the voltage feedback
 */
extern uint16_t bsc_Relay_AfeedbackIp();

/*
 *  After Relay -> DownEnable , FeedBack will come
 *  Get the RelayDown ADValue
 *  Voltage refers to VDDA
 *  returnValue -> voltage feedback
 */
extern uint16_t bsc_Relay_BfeedbackIp();


/*
 * Get the HALL SPD Counter
 * return the bothedge that happened in hallSensor
 *
 * PS:the counter will be reset to zero , after this func is called
 */
extern uint16_t bsc_Get_HALL_SPD_Counter(void);

/*
 * Get the HallSpd pin level(FTM -> GPIO)
 * 1: High
 * 0: Low
 */
extern bool_t   bsc_Get_HALL_SPD_Stat(void);

/*
 * Get the HallDir pin level
 * 1: High
 * 0: Low
 */
extern bool_t   bsc_Get_HALL_DIR_Stat(void);


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
extern uint16_t bsc_Get_KeyIp(void);

/*
 *  Inner Thermal Chip
 *  Get the Thermal ADValue
 */
extern float bsc_AD_Get_Raw_Thermal(void);

/*
 * E2Prom write , write 1Byte once
 * Time cost: 81us  (Page not flip)
 *            10.3ms(Page flip)
 * Use the simulator course
 */
#define IS_BOOTLOADER_DATA_INVAILD_ID 1000
#define IS_BOOTLOADER_NEED_UPDATE_ID  1001
extern bool_t Api_EepromWrite(uint16_t u16_P_DataID,uint8_t u8_P_DataOffset,uint8_t u8_P_ByteLen,const uint8_t * CP_P_DataBuffer);

/*
 * E2Prom read , read 1Byte once
 * Use the simulator course
 */
extern bool_t Api_EepromRead(uint16_t u16_P_DataID,uint8_t u8_P_DataOffset,uint8_t u8_P_ByteLen,uint8_t * const CP_P_DataBuffer);

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
extern uint32_t bsc_Pmu_GetResetStatus(void);
extern void bsc_Pmu_ClrResetStatus(void);
/*
 *  chaoda add here
 */
extern bool_t eeprom_TstLinFlg(void);

/*
 *  chaoda add here
 */
extern void   eeprom_ClrLinFlg(void);

/*
 *  Feed Dog
 */
extern void bsc_FeedCOP(void);

/*
 *  Go to sleep mode
 */
extern void bsc_FailSleep(void);

/*
 *  Go to stop mode
 */
extern void bsc_FailStop(void);


/*
 * 	Go to get Enbale pin
 * */
extern uint16_t bsc_Get_EnIp(void);


/*
   //App Not Use
   extern void bsc_LsInit(void);
*/

/*
	//App Not Use
	extern void bsc_HsInit(void);
 */

/*
 	//Not use
	extern void bsc_HS_PowerPin1Op(bool_t OutputVal);
 */

/*
	//App Not Use
	extern void bsc_PortInit(void);
*/

/*
	//App Not Use
	extern void bsc_MonInit(void);
*/

/*
	//App Not Use
	extern void bsc_AdcInit(void);
*/

/*
	//App Not Use
	extern bool_t Api_EepromInit(void);
*/

/*
	//App Not Use
	extern void bsc_PmuInit(void);
*/
extern Lin_Status lin_network_state_get(void);
extern uint16_t l_GetLinIdleCnt(void);
extern void l_SetLinIdleCnt(uint16_t u16_app_cnt);

#endif /* APPLICATION_INCLUDE_APPIF_H_ */
