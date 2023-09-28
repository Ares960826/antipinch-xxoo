
/*******************************************************************************
|  File Name:    param.h
|  Description:  Period Interrupt header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170629	   0.01       	Cj          	Init
|******************************************************************************/
#ifndef PARAM_H_
#define PARAM_H_
#include "Typedef.h"
#include "complier_sw.h"
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                             **
*******************************************************************************/

typedef enum{ 
	MOT_CW=0u,
	MOT_CCW
}MOTDIR;



typedef struct{
	uint16_t	u16_pos_priority;
	uint16_t	u16_sst_priority;
	uint16_t	u16_blk_priority;
	
	bool_t		bl_hall_dir_cfg;
	uint16_t 	u16_hall_tout_val;
	
	uint8_t 	u8_winpos_tolerance;
	uint8_t		u8_beakpos;
	uint16_t 	u16_apzone_top; //4mm
	uint16_t 	u16_apzone20_pos; //20mm
	uint16_t 	u16_apzone_bottom; //200mm
	uint16_t	u16_step_val;
	

	uint16_t	u16_poserr_up; //
	uint16_t	u16_poserr_dn;
	uint16_t	u16_poserr_max; //error maxpos
	uint8_t		u8_hallerr_max;
	
	uint16_t 	u16_softstop_minpos;
	uint8_t		u8_softstopoffset;
	uint8_t		u8_softstopcnt;
}HallPosConfig_t;


typedef struct{
	bool_t	bl_motor_dir;
	uint16_t	u16_stop_delay;
	uint16_t u16_valid_up_prio;
	uint16_t u16_valid_down_prio;
	uint16_t u16_valid_stop_prio;
	
}MotorConfig_t;

typedef struct{
	uint16_t	u16_bat_prio;

}BatConfig_t;

typedef struct{
	uint16_t	u16_apstop_prio;
	uint16_t	u16_apreverse_prio;
	
	uint16_t	u16_aprev_distance1;
	uint16_t	u16_aprev_distance2;

}ApfConfig_t;




#ifdef DOOR_FL
#define		bl_hall_dir_cfg_default				1                     //Front&Rear have defferent dir
#endif

#ifdef DOOR_FR
#define		bl_hall_dir_cfg_default				1
#endif

#ifdef DOOR_RL
#define		bl_hall_dir_cfg_default				0
#endif

#ifdef DOOR_RR
#define		bl_hall_dir_cfg_default				0
#endif
#define		u16_hall_tout_val_default			init_hall_tout_close //30


#define		u8_winpos_tolerance_default			init_tolerance_max	//30
#define		u8_beakpos_default					init_beakarea	//	45
#define		u16_apzone_top_default 				init_aparea_top //40
#define		u16_apzone20_pos_default 			init_aparea_top	//90
#define		u16_apzone_bottom_default 			init_aparea_bottom //600
#define		u16_step_val_default				init_step_val		//	65535


#define		u16_poserr_up_default 				init_negpos_max//60
#define		u16_poserr_dn_default				init_negpos_max//	60
#define		u16_poserr_max_default  			init_max_pos //1400
#define		u8_hallerr_max_default				init_hallerr_max	//40

#define		u16_softstop_minpos_default			init_softstop_minpos	//500
#define		u8_softstopoffset_default			init_softstop_offset 	//24 //FL 24/26   //FR :30
#define		u8_softstopcnt_default				init_softstop_tcnt		//20

#define		u8_debounce_time_default			init_debounce_time		//15
#define		u8_enable_debounce_time_default		10
#define		u16_keystuck_time_default			init_key_error	//		15000
#ifdef DOOR_FL
	#define		u8_door_type_default							0x20 //0x20 :FL //0x21 : FR //0x22 :RL //0x23 :RR
#endif
#ifdef DOOR_FR
	#define		u8_door_type_default							0x21 //0x20 :FL //0x21 : FR //0x22 :RL //0x23 :RR
#endif
#ifdef DOOR_RL
	#define		u8_door_type_default							0x22 //0x20 :FL //0x21 : FR //0x22 :RL //0x23 :RR
#endif
#ifdef DOOR_RR
	#define		u8_door_type_default							0x23 //0x20 :FL //0x21 : FR //0x22 :RL //0x23 :RR
#endif

#define		u16_key_prio_up_default						0x0004
#define		u16_key_prio_dn_default						0x0002
#define		u16_key_prio_stop_default					0x0001
#define		bl_disable_autokey_default					0
#define		u16_Postag_default							60	//Õ∏∆¯Œª÷√hall÷µ
#define		u8_vdown_cnt_default						200
#define		u16_default_voicemaxpos_default				1000

#define		u16_tp_prio_default				0x0008
#define		u16_tp2_prio_default			0x8000
#define		u16_apstop_prio_default			0x1000
#define		u16_apreverse_prio_default		0x2000
#define		u16_aprev_distance1_default		init_rev_pos	//300
#define		u16_aprev_distance2_default		init_rev_pos	//100

#define		u16_bat_prio_default				0x0040

#define		u16_pos_priority_default			0x0020
#define		u16_sst_priority_default			0x0010
#define		u16_blk_priority_default			0x4000
#ifdef DOOR_FL
#define	 bl_motor_dir_default					MOT_CCW                     //Front&Rear have defferent dir
#endif

#ifdef DOOR_FR
#define	 bl_motor_dir_default					MOT_CCW   
#endif

#ifdef DOOR_RL
#define	 bl_motor_dir_default					MOT_CW   
#endif

#ifdef DOOR_RR
#define	 bl_motor_dir_default					MOT_CW   
#endif
#define		u16_stop_delay_default				50
#define		u16_valid_up_prio_default			u16_key_prio_up_default
#define		u16_valid_down_prio_default		u16_key_prio_dn_default+u16_apreverse_prio_default
#define		u16_valid_stop_prio_default		u16_key_prio_stop_default+u16_apstop_prio_default+u16_bat_prio_default+ \
																				u16_pos_priority_default+u16_sst_priority_default+u16_blk_priority_default+\
																				u16_tp_prio_default+u16_tp2_prio_default
																				
																				



/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
 //extern _Init_Static_Rom const  ProductConfig_t ProductConfig;
 
 extern _Init_Static_Rom const  ApfConfig_t ApfConfig;

 extern _Init_Static_Rom const  BatConfig_t BatConfig;

 extern _Init_Static_Rom const  MotorConfig_t MotorConfig;

 extern _Init_Static_Rom const  HallPosConfig_t HallPosConfig;

 //extern const  KeyConfig_t KeyConfig;

/*******************************************************************************
**                      Global Function Declarations                         **
*******************************************************************************/



#endif
