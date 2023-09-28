
/*******************************************************************************
|  File Name:    Hallpos.h
|  Description:  Hall & Window Position handle
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
|
|******************************************************************************/
#ifndef HALLPOS_H
#define HALLPOS_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Typedef.h"
#include "complier_sw.h"
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/
typedef enum{
	DIR_DOWN = 0u,
	DIR_UP,
	
}dir_t;

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/

typedef struct{
	uint16_t u16_WinPos;				//save
	uint8_t	u8_BlockUpCnt;			//save
	uint8_t	u8_BlockDownCnt;		//save
	uint16_t	u16_SoftStopPos; 	//save
	uint8_t	u8_SoftStopCnt;			//save
	union
	{
		uint8_t Ubyte;
		struct
		{
			uint8_t bl_PosSysNormFlg	: 1;
			uint8_t bl_SSTPosFlg	: 1;
			uint8_t bl_SSTCntFlg	: 1;
			uint8_t bl_BeingBlockPos	: 1;
			uint8_t bl_InSSTPosFlg	: 1;
			uint8_t Bit5	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;								//save
}HP_Save_t;

//HallPosData_t
typedef struct{
	volatile bool_t	bl_HallDir;
	volatile bool_t	bl_HallSpd;
	volatile uint16_t u16_HallPW;
	volatile uint16_t u16_WinPosI;

	volatile uint16_t u16_WinPos;	//save

	uint8_t	u8_BlockUpCnt;			//save
	uint8_t	u8_BlockDownCnt;		//save
	uint16_t	u16_SoftStopPos; 	//save
	uint8_t	u8_SoftStopCnt;			//save

	union
	{
		uint8_t Ubyte;
		struct
		{
			uint8_t bl_PosSysNormFlg	: 1;
			uint8_t bl_SSTPosFlg	: 1;
			uint8_t bl_SSTCntFlg	: 1;
			uint8_t bl_BeingBlockPos	: 1;
			uint8_t bl_InSSTPosFlg	: 1;
			uint8_t Bit5	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;											//save

	union
	{
		uint8_t Ubyte;
		struct
		{
			uint8_t bl_BlockUp	: 1;
			uint8_t bl_BlockDn	: 1;
			uint8_t bl_PosChangeFlg	: 1;
			uint8_t bl_CalcAP	: 1;
			uint8_t bl_InAPZoneFlg	: 1;
			uint8_t bl_InAPZone4_20Flg	: 1;
			uint8_t bl_InAPZone20_200Flg	: 1;
			uint8_t bl_InBeakZoneFlg	: 1;
		} Bits;
	}Flg2;

	uint16_t u16_MaxPos;
	uint16_t	u16_NegativePos;
	uint16_t	u16_UninitDnPos;

	uint16_t	u16_HallErrorCnt;
	bool_t	bl_HallTimeOutFlg;
	uint16_t	u16_HallTimeOutCnt;
	uint16_t	u16_DTC_HallErrCnt;
	uint8_t		u8_RunTimeCnt;
}HallPosData_t;
extern _Init_SAVE_RAM HallPosData_t HallPosData;
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/
void HP_Init(void);
void HP_Task(void);
void HP_10ms_Job(void);
void HP_5s_Job(void);

/*******************************************************************************
**                      Global Service Function Declarations                  **
*******************************************************************************/

void HP_SetNegPos(uint16_t pos);

bool_t HP_GetHallDirection(void); //Hall dir

bool_t HP_TstHallTimeOutFlg(void);
void HP_Hall_TCntReload(void); //Reload hall timeout cnt

void HP_ResetBlockUpCnt(void);
void HP_ResetBlockDownCnt(void);
uint8_t HP_GetBlockUpCnt(void);
uint8_t HP_GetBlockDownCnt(void);

uint16_t HP_GetHallPulseWidth(void);
uint8_t HP_GetHallErrorCnt(void);
uint16_t HP_GetHallWPos(void);

uint16_t HP_GetMaxWinPos(void);
uint16_t HP_GetSoftStopPos(void);

bool_t HP_TstPosChangeFlg(void);
void HP_ClrPosChangeFlg(void);

void HP_ClrCalcAPFlg(void);
bool_t	HP_TstCalcAPFlg(void);

bool_t HP_TstInSoftStopPosFlg(void);
void HP_ClrInSoftStopPosFlg(void);


bool_t HP_TstInSoftStopPosFlg(void);
void HP_ClrInSoftStopPosFlg(void);

bool_t HP_TstBlockUpFlg(void);
void HP_ClrBlockUpFlg(void);

bool_t HP_TstBlockDnFlg(void);
void HP_ClrBlockDnFlg(void);

bool_t HP_TstInAPZoneFlg(void);
bool_t HP_TstInAPZone4_20Flg(void);
bool_t HP_TstInAPZone20_200Flg(void);
bool_t HP_TstInBeakZoneFlg(void);

bool_t HP_TstHallErrFlg(void);

bool_t HP_TstPosSysNormFlg(void);
void HP_Normalize_EnteyCall(void);
void HP_Normalize_ExitCall(void);

uint8_t HP_SaveData(void* buf);
void HP_RestoreData(void* const buf);

#endif
