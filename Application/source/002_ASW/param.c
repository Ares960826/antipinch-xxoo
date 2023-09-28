
/*******************************************************************************
|  File Name:    Pit.c
|  Description:  Period Interrupt source file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Typedef.h"
#include "appl_const.h"
#include "param.h"



 
 
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


/*
const ProductConfig_t ProductConfig={
	 u8_CustomerID,
   u8_VehicleTypeID,
	 u8_HardWare_Ver,
   u8_SoftWare_Ver,
	 u8_Para_Version,
   u8_FDyear,
   u8_FDmonth,
   u8_FDday,
   u8_FDhour,
};
*/


_Init_Static_Rom const ApfConfig_t ApfConfig={
		u16_apstop_prio_default,
		u16_apreverse_prio_default,
		u16_aprev_distance1_default,
		u16_aprev_distance2_default,
};


_Init_Static_Rom const BatConfig_t BatConfig={
		u16_bat_prio_default,
};

_Init_Static_Rom const MotorConfig_t MotorConfig={
		bl_motor_dir_default,
		u16_stop_delay_default,
		u16_valid_up_prio_default,
		u16_valid_down_prio_default,
		u16_valid_stop_prio_default,
};

_Init_Static_Rom const HallPosConfig_t HallPosConfig={
		u16_pos_priority_default,
		u16_sst_priority_default,
		u16_blk_priority_default,

		bl_hall_dir_cfg_default,
		u16_hall_tout_val_default,

		u8_winpos_tolerance_default,
		u8_beakpos_default,
		u16_apzone_top_default, //4mm
		u16_apzone20_pos_default, //20mm
		u16_apzone_bottom_default, //200mm
		u16_step_val_default,


		u16_poserr_up_default, //
		u16_poserr_dn_default,
		u16_poserr_max_default, //error maxpos
		u8_hallerr_max_default,

		u16_softstop_minpos_default,
		u8_softstopoffset_default,
		u8_softstopcnt_default,
};
/*
_Init_Static_Rom const KeyConfig_t KeyConfig={
		u8_debounce_time_default,
		u8_enable_debounce_time_default,
		u16_keystuck_time_default,
		u8_door_type_default,
		u16_key_prio_up_default,
		u16_key_prio_dn_default,
		u16_key_prio_stop_default,
		bl_disable_autokey_default,
		u16_Postag_default,
		u8_vdown_cnt_default,
		u16_default_voicemaxpos_default
};

_Init_Static_Rom const TpConfig_t TpConfig={
	u16_30s_time_default,
	u16_2min_Time_default,
	u16_30min_Time_default,
	u16_tp_prio_default,
	bl_disable_thp_default
};
*/
