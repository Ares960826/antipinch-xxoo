
/*******************************************************************************
|  File Name:    keyport.h
|  Description:  keyport header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef KEYPORT_H_
#define KEYPORT_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "typedef.h"
#include "Hallpos.h"
#include "motor.h"

#include "appif.h"
//#include <adc1.h>
//#include <mon.h>

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//Timer!!
#define C_2S_B2		1000
#define C_5S_B2		2500
#define C_10S_B2	5000

//////////////////////////////////////////
#define Powermode_OFF   0
#define Powermode_ON    0x02
#define Powermode_start 0x04

#define LINWin_CON_ManualUp   0x01
#define LINWin_CON_ManualDown 0x02 
#define LINWin_CON_AutoUp     0x03
#define LINWin_CON_AutoDown   0x04

#define LA_CON_Lefthand_d     0
#define LA_CON_Righthand_d    1


#define DATA_VALID   2

#define LA_CON_VocValid 0x64

#define SY_CON_DATA   16  // 10ms*16 =160ms  > 150 ms
#define SY_CON_SW_INVALID 25 //50ms =25*2		  //poweron time 

#define NAD_FL   0x20
#define NAD_FR   0x21
#define NAD_RL   0x22
#define NAD_RR   0x23


//LINDriverStatusType begin
#define LIN_STATUS_RUN        0x01    /* Driver is in run state                                   */
#define LIN_STATUS_IDLE       0x02    /* No-Bus_activity timeout is expired                       */
#define LIN_STATUS_PENDING    0x04    /* LIN bus frame is pending                                 */
//LINDriverStatusType end

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/

typedef volatile uint8_t   LINDriverStatusType;   /* uint8_t  unsigned   8  bits  */





/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

extern volatile T_FLAG8  LA_T8_Flag6;
#define LA_bi_PWLHiEftCndA          LA_T8_Flag6.Bits.Bit0
#define LA_bi_PWLRevsng             LA_T8_Flag6.Bits.Bit1
#define LA_bi_PWLSnsngSysFltDetc    LA_T8_Flag6.Bits.Bit2
#define LA_bi_PWLThrmlProtnA        LA_T8_Flag6.Bits.Bit3
#define LA_bi_PWLRelayFltDetc       LA_T8_Flag6.Bits.Bit4
//#define LA_bi_              LA_T8_Flag6.Bits.Bit5
//#define LA_bi_              LA_T8_Flag6.Bits.Bit6
//#define LA_bi_          LA_T8_Flag6.Bits.Bit7


extern volatile T_FLAG8  LA_T8_Flag7;
#define LA_bi_RespEr            LA_T8_Flag7.Bits.Bit6
#define LA_bi_PWLNotNormd       LA_T8_Flag7.Bits.Bit7



extern volatile T_FLAG8 LA_T8_Flag8 ;

#define  LA_bi_PWLOpEnb1           LA_T8_Flag8.Bits.Bit0 //
//#define  LA_bi_PWLOpEnb           LA_T8_Flag8.Bits.Bit1 //
#define  LA_bi_WndShrtMv_ShrtDrop  LA_T8_Flag8.Bits.Bit2
#define  LA_bi_WndShrtMv_ShrtRise  LA_T8_Flag8.Bits.Bit3 //
#define  LA_bi_PWLlocal_sw_disable LA_T8_Flag8.Bits.Bit4 //
//#define  LA_bi_    LA_T8_Flag8.Bits.Bit5 //
//#define  LA_bi_  LA_T8_Flag8.Bits.Bit6 //
/*
extern volatile T_FLAG8 LA_T8_Flag9 ;

#define  LA_bi_Lin_Enable        LA_T8_Flag9.Bits.Bit0 //车窗使能
#define  LA_bi_Lin_LOCKCommand   LA_T8_Flag9.Bits.Bit1 //globalstop
#define  LA_bi_Lin_UNLOCKCommand LA_T8_Flag9.Bits.Bit2 //globalstop
#define  LA_bi_Lin_GlobalClose   LA_T8_Flag9.Bits.Bit3 //关窗激活
#define  LA_bi_Lin_GlCloseRes    LA_T8_Flag9.Bits.Bit4 //
#define  LA_bi_Lin_GlobalOpen    LA_T8_Flag9.Bits.Bit5 //开窗激活
#define  LA_bi_Lin_GlOpenRes     LA_T8_Flag9.Bits.Bit6 //
#define  LA_bi_Lin_ChildLockSt   LA_T8_Flag9.Bits.Bit7 //childlock


extern volatile T_FLAG8 LA_T8_Flag10 ;

#define  LA_bi_Lin_GlobalPreClo     LA_T8_Flag10.Bits.Bit0 //
#define  LA_bi_Lin_GlobalPreOpen    LA_T8_Flag10.Bits.Bit1 //
#define  LA_bi_Lin_GlobalPreStop1   LA_T8_Flag10.Bits.Bit2 //
#define  LA_bi_Lin_GlobalPreStop2   LA_T8_Flag10.Bits.Bit3 //
#define  LA_bi_Lin_VoiceDelay       LA_T8_Flag10.Bits.Bit4 //
#define  LA_bi_Lin_VoicePre         LA_T8_Flag10.Bits.Bit5 //
#define  LA_bi_Lin_VoiceStop        LA_T8_Flag10.Bits.Bit6 //
#define  LA_bi_Lin_VoicePreStop     LA_T8_Flag10.Bits.Bit7 //
*/

extern  T_FLAG16                mctrl_status;
#define Motor_bi_Running        mctrl_status.Bits.Bit0
#define Motor_bi_Dir_Up         mctrl_status.Bits.Bit1
#define Motor_bi_Block_Up       mctrl_status.Bits.Bit2  //reach top
#define Motor_bi_SStopCntCondition          mctrl_status.Bits.Bit3
#define Motor_bi_Block_Down     mctrl_status.Bits.Bit4  //reach bottom
#define Motor_bi_InRawSt        mctrl_status.Bits.Bit5
#define Motor_bi_Prv_Updir      mctrl_status.Bits.Bit6
#define Motor_bi_BeingBlockPos   mctrl_status.Bits.Bit7
#define Motor_bi_Close          mctrl_status.Bits.Bit8
#define Motor_bi_Open           mctrl_status.Bits.Bit9
#define Motor_bi_Stop           mctrl_status.Bits.Bit10
//#define
#define Motor_bi_BeingInSStopPos      mctrl_status.Bits.Bit15



extern uint16_t SS_ui_StudyStopPos;
extern  volatile T_FLAG8 syst_flag; 
#define SY_bi_Enable_Active     syst_flag.Bits.Bit0
#define SY_bi_Enable_Filted     syst_flag.Bits.Bit1
#define SY_bi_BatDrop_happened       syst_flag.Bits.Bit2
#define SY_bi_Disable_Auto      syst_flag.Bits.Bit3
#define SY_bi_Manual_Key        syst_flag.Bits.Bit4
#define SY_bi_Buffer_Full	     syst_flag.Bits.Bit5
#define SY_bi_DisableSimDataSend         syst_flag.Bits.Bit6
#define SY_bi_Buffer_Empty      syst_flag.Bits.Bit7


#define C_ALIVE_KEY            0x01
#define C_ALIVE_THERMO         0x02
#define C_ALIVE_ANTIPINCH      0x04
#define C_ALIVE_LINF           0x08
#define C_ALIVE_RELAYSTICK     0x10


#define C_VALID_ALIVE          (C_ALIVE_KEY+C_ALIVE_THERMO+C_ALIVE_ANTIPINCH+C_ALIVE_LINF+C_ALIVE_RELAYSTICK)

#define C_ALIVE_KEY_MASK       (C_ALIVE_KEY ^C_VALID_ALIVE)
#define C_ALIVE_THERMO_MASK    (C_ALIVE_THERMO ^C_VALID_ALIVE)
#define C_ALIVE_ANTIPINCH_MASK (C_ALIVE_ANTIPINCH ^C_VALID_ALIVE)
#define C_ALIVE_LINF_MASK      (C_ALIVE_LINF ^C_VALID_ALIVE)
#define C_ALIVE_RELAYSTICK_MASK (C_ALIVE_RELAYSTICK ^C_VALID_ALIVE)

extern volatile uint8_t  RT_bi_functest_f;

extern uint8_t  MC_uc_MotorStopDelay;
extern volatile unsigned short  HA_ui_WinPos;	
extern volatile uint8_t  LD_uc_TempNAD; 
extern volatile uint8_t  LD_uc_NAD1;

extern volatile uint8_t  lin_uc_command;
extern volatile uint8_t  lin_uc_sysmode ;


/*

extern volatile uint8_t  lin_uc_Steer_Whl_Type;
extern volatile uint8_t  lin_uc_EMS_EngStatus;
extern volatile uint8_t  lin_uc_PowerModeValid;
extern volatile uint8_t  lin_uc_PowerMode;
extern volatile uint8_t  lin_uc_Steer_Whl_Type;
extern volatile uint8_t  lin_uc_VehicleType; 
extern volatile uint8_t  lin_uc_switchcommand;  
extern volatile unsigned short  lin_ui_speed;
extern volatile uint8_t  lin_uc_temperature;
extern volatile uint8_t  lin_uc_voicecommand ;
*/


extern LINDriverStatusType LINBusStatus;




extern uint8_t  MB_uc_UpBlockCnt;		 //read
extern uint8_t  MB_uc_DownBlockCnt;		   //read
extern uint8_t  AD_uc_MotorVoltage;

extern unsigned short POS_ui_VocTag;  //set function
extern uint8_t  MC_uc_MotorStopDelay;  // read & set !!!



extern volatile uint8_t  SY_uc_poweron_sw;
extern uint8_t SY_uc_poweron;
 //////////////
 
extern uint8_t  SY_bi_Volt_TrembleFlag;

extern uint16_t  AP_ui_AP_off;
 
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
Name			: KEY_Init
Syntax			:  void KEY_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Key Init
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
  

/*******************************************************************************
Name			: KEY_GetKey
Syntax			:  uint8_t KEY_GetKey(void)
Parameters(in)	: None
Parameters(out) : None
Return value	:  1: Manual down /2: Manual up /5: auto down /6 auto up  / 3 7 : error
Description		: current key value
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
extern void KeyPort_Init(void);

extern void KeyPort_Prev(void);
extern void KeyPort_After(void);
extern void KeyPort_10msTask(void);
extern void  KeyPort_2msTask(void);
extern void KeyPort_CheckBat(void);
extern void KEY_UpdateInfoData(void);

extern uint8_t KeyPort_SaveData(uint8_t* buf);
extern void KeyPort_RestoreData(uint8_t* const buf);


//bool_t APF_TstAPRdyFlg(void);
//bool_t APF_TstAPOffFlg(void);
//bool_t APF_TstInRev(void);


#endif
