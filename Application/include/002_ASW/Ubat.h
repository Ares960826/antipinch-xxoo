
/*******************************************************************************
|  File Name:    Ubat.h
|  Description:  Motor Battery header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef Ubat_H_
#define Ubat_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "complier_sw.h"
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/
typedef struct{
	union
	{
		uint8_t Ubyte;	//save data
		struct
		{
			uint8_t bl_LowVoltage	: 1;
			uint8_t bl_HighVoltage	: 1;
			uint8_t Bit2	: 1;
			uint8_t Bit3	: 1;
			uint8_t Bit4	: 1;
			
			uint8_t Bit5	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;
}BAT_Save_t;

typedef enum{
		stBATOK = 0u,
		stBATLOW_TIME,
		stBATHIGH_TIME,
		stBATLOW,
		stBATHIGH,
		stBATHIGH_WAKE_UP,
		stBATLOW_ON,
		stBATHIGH_ON,
}volt_sts_t;


//BatData_t
typedef struct{
	union
	{
		uint8_t Ubyte;	//save data
		struct
		{
			uint8_t bl_LowVoltage	: 1;
			uint8_t bl_HighVoltage	: 1;
			uint8_t Bit2	: 1;
			uint8_t Bit3	: 1;
			uint8_t Bit4	: 1;

			uint8_t Bit5	: 1;
			uint8_t Bit6	: 1;
			uint8_t Bit7	: 1;
		} Bits;
	}Flg;
	int16_t u16_temperature;
	int16_t u16_temperature2;
	uint8_t u8_VoltageFilter;
	uint8_t	u8_VoltageADC;
	uint16_t	u16_VoltageFiltBuf;
	uint16_t	u16_HighLowVoltage_Timeout;
	volt_sts_t	VoltageState;
}BatData_t;
extern _Init_SAVE_RAM BatData_t BatData;
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
Name			: Ubat_GetRawVoltage()
Syntax			:  uint16_t Ubat_GetRawVoltage(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Get current battery voltage from ADC1
Requirement		: None
Call By			:Application Layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
uint8_t Ubat_GetRawVoltage(void);


/*******************************************************************************
Name			: Ubat_GetVoltageFiltered()
Syntax			:  uint16_t Ubat_GetVoltageFiltered(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Get Filtered Voltage 
Requirement		: None
Call By			:Application Layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
uint8_t Ubat_GetVoltageFiltered(void);
void BAT_Init(void);
void Ubat_Task(void);
void Ubat_2ms_Job(void);

uint8_t BAT_SaveData(uint8_t* buf);
void BAT_RestoreData(uint8_t* const buf);

bool_t Ubat_TstHighVoltageFlg(void);
bool_t Ubat_TstLowVoltageFlg(void);
#endif
