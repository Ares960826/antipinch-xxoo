/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*Name     :  appl_const.h                                                           *
;*Project  :  AntiPinch                                                    *
;*Device   :  S12VR64					                                       *
;*AUTHOR   :  AP project team						                                       *
;*DATE     :  2010/05/20					                                   *
;*SW VER   :  0.1					                                           *
;*HW VER   :    					                                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;* COPYRIGHT STEC(C) Shanghai SIIC Transportation Electric CO.,ltd             *
;*                                                                             *
;* ALL RIGHTS RESERVED                                                         *
;*                                                                             *
;* The reproduction, transmission, or use of this document or its content is   *
;* not permitted without express written authority. Offenders will be liable   *
;* for damages.                                                                *
;* All rights, including rights created by patent grant or registration of a   *
;* utility model or design, are reserved.                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef _APPL_CONST_H
#define _APPL_CONST_H
#include "Typedef.h"
#include "complier_sw.h"


typedef struct 
       {
        uint16_t  HALL_DIR;          
        uint16_t  MOT_DIR;           
        uint16_t  EN_SIMDATASEND;           
        uint16_t  DIS_ADAPT;         
        uint16_t  DIS_RROAD;       
        uint16_t  USE_RROAD2;   
        uint16_t  DIS_APSTARTUP;     
        uint16_t  DIS_SFILTER;       
        uint16_t  DISABLE_AP;           
        uint16_t  DIS_AP_BLOCK;     
        uint16_t  DIS_AP_D2;     
        uint16_t  EN_VOLT_LOCK;        
        uint16_t  EN_ADC_TM;        
        uint16_t  DIS_SLEEPMODE;     
        uint16_t  DIS_AUTOKEY;       
        uint16_t  DIS_THERMO;        
        uint16_t  DIS_ADC;           
        uint16_t  DIS_LINF;            
        uint16_t  DIS_AP_10S;           
        uint16_t  DIS_TABLE_OFF;     
        uint16_t  psw_CHECKSUM;      
       }strk_psw_flsh1;

extern _Init_Static_Rom const strk_psw_flsh1 CFLASH_PSW;
#define C_HALL_DIR          CFLASH_PSW.HALL_DIR
#define C_MOTOR_DIR         CFLASH_PSW.MOT_DIR
#define C_EN_SIMDATASEND    CFLASH_PSW.EN_SIMDATASEND
#define C_DIS_ADAPT         CFLASH_PSW.DIS_ADAPT
#define C_DIS_RROAD         CFLASH_PSW.DIS_RROAD
#define C_USE_ADAPT2     	  CFLASH_PSW.USE_RROAD2
#define C_DIS_APSTARTUP     CFLASH_PSW.DIS_APSTARTUP
#define C_DIS_SFILTER       CFLASH_PSW.DIS_SFILTER
#define C_DISABEL_AP        CFLASH_PSW.DISABLE_AP
#define C_DIS_AP_BLOCK      CFLASH_PSW.DIS_AP_BLOCK
#define C_DIS_AP_D2		    CFLASH_PSW.DIS_AP_D2
#define C_EN_VLOT_LOCK      CFLASH_PSW.EN_VOLT_LOCK
#define C_EN_ADC_TM         CFLASH_PSW.EN_ADC_TM
#define C_DIS_SLEEPMODE     CFLASH_PSW.DIS_SLEEPMODE
#define C_DIS_AUTOKEY       CFLASH_PSW.DIS_AUTOKEY
#define C_DIS_THERMO        CFLASH_PSW.DIS_THERMO
#define C_DIS_ADC           CFLASH_PSW.DIS_ADC
#define C_DIS_LINF          CFLASH_PSW.DIS_LINF
#define C_DIS_AP_10S        CFLASH_PSW.DIS_AP_10S
#define C_DIS_TABLE_OFF     CFLASH_PSW.DIS_TABLE_OFF
#define C_psw_CHECKSUM      CFLASH_PSW.psw_CHECKSUM


extern volatile _Init_Static_Rom const uint16_t   EE_ERR1;
extern volatile _Init_Static_Rom const uint16_t   EE_ERR2;
extern volatile _Init_Static_Rom const uint16_t   EE_ERR3;
extern volatile _Init_Static_Rom const uint16_t   EE_ERR4;
extern volatile _Init_Static_Rom const uint16_t   EE_ERR5;
extern volatile _Init_Static_Rom const uint16_t   EE_ERR6;

#define CHALLDIR				0xf38a
#define CMOTOR_DIRECTION		0x5906
#define CEnable_SIMDATASEND			0x23f0
#define CDisable_Adapt			0x37e0
#define CDisable_RROAD			0x37e1
#define CEnable_ADAPT2		      0x37ec
#define CDisable_AP_STARTUP		0x37e2
#define CDisable_SFILTER		0x37e3
#define CDisable_AP				0x37e4
#define CDisable_AP_BLOCK		0x37e5
#define CDisable_AP_D2			0x37e6
#define CEnable_VOLTAGE_LOCK	  0x47e6
#define CEnable_ADC_TM			0x37e7
#define CDisable_Sleepmode		0x37e8
#define CDisable_Autokey		0x37e9
#define CDisable_Thermo			0x37ea
#define CDisable_ADC			0x37eb
#define CDisable_LINF			0x37eC
#define Disable_AP_STUP1		0x37ed
#define Disable_AP_STUP2		0x37ee
#define CDisable_AP_10S		  0x37ef
#define CDisable_TABLE_OFF		0x37f0

typedef struct 
      {
       uint8_t  EE_ID;
       uint8_t  EE_FreeChar;
       uint16_t	  EE_Valid_File;
       uint8_t  EE_Par_VersionH;
       uint8_t  EE_Par_VersionL;
      }strk_eedat1;


extern __attribute__((__section__(".check_data")))  const uint16_t  EE_CHKSUM; /*dd96  */
extern __attribute__((__section__(".check_data")))  const uint16_t  EE_LEN;

extern _Init_Static_Rom const strk_eedat1 CFLASH_EEDAT1;

#define c_ee_id        					CFLASH_EEDAT1.EE_ID  
#define c_ee_freechar           CFLASH_EEDAT1.EE_FreeChar     
#define c_ee_valid_file         CFLASH_EEDAT1.EE_Valid_File   
#define c_ee_par_versionh       CFLASH_EEDAT1.EE_Par_VersionH 
#define c_ee_par_versionl       CFLASH_EEDAT1.EE_Par_VersionL



#define Start_EE_PARAMETER      &EE_LEN
#define EE_PARAMETER_CHSUM      0x4000 
#define Start_EE2_PARAMETER     &EE_LEN+0x200 
#define EE2_PARAMETER_CHSUM     0x4200 



#define init_ee_checksumH       0x4E 
#define init_ee_checksumL       0xc6 
#define init_ee_BlockLenH       0x00 
#define init_ee_BlockLenL       0xDE 



#define init_ee_par_versionh    0x01  
#define init_ee_par_versionl    0x01  


#define ee_max_BlockLength      0x200   

#define init_ee_ID     SW_ID 

#define init_ee_freechar        0x00   
#define init_ee_valid_file      EE_FILE_EXIST  


#define OrgEEParameter          0x00    
#define CopyEEParameter         0x01   


#define  c_key_up_prio             init_key_up_prio //CFLASH_MPRIO.key_up_prio
#define  c_key_down_prio           init_key_down_prio //CFLASH_MPRIO.key_down_prio
#define  c_key_stop_prio           init_key_stop_prio //CFLASH_MPRIO.key_stop_prio
#define  c_thermo_prio             init_thermo_prio //CFLASH_MPRIO.thermo_prio
#define  c_thermomax_prio          init_thermomax_prio //CFLASH_MPRIO.thermomax_prio


#define init_apreverse_prio    0x2000
#define init_apstop_prio       0x1000                                 
#define init_block_prio        0x4000
#define init_thermo_prio       0x0008
#define init_thermomax_prio    0x8000
#define init_pos_prio          0x0020

#ifdef CS_EnableUBattery
  #define init_battery_prio    0x0040
#else 
  #define init_battery_prio    0x0000
#endif

#define init_key_up_prio       0x0004
#define init_key_down_prio     0x0002
#define init_key_stop_prio     0x0001
#define init_key_softstop_prio 0x0010

#define init_linf_up_prio   0x0000
#define init_linf_down_prio 0x0000



#define  init_valid_key_up_prio       init_key_up_prio+init_linf_up_prio
#define  init_valid_key_down_prio     init_apreverse_prio+init_key_down_prio+init_linf_down_prio
#define  init_valid_key_stop_prio     init_apstop_prio+init_block_prio+init_thermo_prio+init_thermomax_prio+ \
                                      init_pos_prio+init_battery_prio+init_key_stop_prio+init_key_softstop_prio




struct strk_positionen
      {

       uint16_t    pos_max_pos; 				
       uint16_t    pos_cal_bot_pos;
      };

extern _Init_Static_Rom const struct strk_positionen CFLASH_POSITION;




#define  c_max_pos          CFLASH_POSITION.pos_max_pos
#define  c_pos_cal_bot_pos  CFLASH_POSITION.pos_cal_bot_pos
			
#define init_aparea_top      30//24 //7mm--15   37  
#define init_aparea_bottom   720//680   
#define init_max_pos          1300   //AP13 ~920  //AP14 ~960
#define init_softstop_minpos  600
#define init_beakarea         50   //10mm--24    30  // 15mm--36
#define init_negpos_max       40    
#define init_step_val         200   

#define init_hallerr_max      40    
#define init_softstop_tcnt     20
#define init_softstop_offset   32//25//35//45  
#define init_pos_cal_bot_pos   950    


struct strk_thermo_flsh
       {
        uint16_t   motor_ini_temp;     
        uint16_t   motor_cooling_point; 
        uint16_t   motor_min_temp;    
        uint16_t   motor_heating_point; 
        uint16_t   motor_limit3;     
        uint16_t   motor_limit2;     
        uint16_t   motor_limit1;     
        uint16_t   motor_turnon_thd;         
       };

extern _Init_Static_Rom const struct strk_thermo_flsh CFLASH_THERMO;

#define  c_motor_ini_temp      CFLASH_THERMO.motor_ini_temp 
#define  c_motor_cooling_point CFLASH_THERMO.motor_cooling_point 
#define  c_motor_min_temp      CFLASH_THERMO.motor_min_temp
#define  c_motor_heating_point CFLASH_THERMO.motor_heating_point
#define  c_motor_limit3        CFLASH_THERMO.motor_limit3 
#define  c_motor_limit2        CFLASH_THERMO.motor_limit2 
#define  c_motor_limit1        CFLASH_THERMO.motor_limit1 
#define  c_motor_turnon_thd    CFLASH_THERMO.motor_turnon_thd     


#define init_motor_ini_temp      22000//52000   /*  130 */
#define init_motor_cooling_point 53400//56800   /*  142 */
#define init_motor_min_temp      21000//44000   /*  110 */
#define init_motor_heating_point 53400//48000   /*  120 */
#define init_motor_limit3        61000//64000   /*  160 */
#define init_motor_limit2        58500//60000   /*  150 */
#define init_motor_limit1        53400//56800   /*  142 */
#define init_motor_turnon_thd    53000//56000   /*  140 */

struct strk_key_flsh
       {
        uint8_t       man_open;       //   0x01   
        uint8_t       man_close;      //   0x02   
        uint8_t       debounce_time;  //   16     
        uint8_t       man_express;    //   65     
        uint8_t       key_t1_time;    //   1      
        uint16_t      key_error;      //   10000    
       };

extern _Init_Static_Rom const struct strk_key_flsh CFLASH_KEY;

#define  c_man_open         CFLASH_KEY.man_open      
#define  c_man_close        CFLASH_KEY.man_close     
#define  c_debounce_time    CFLASH_KEY.debounce_time 
#define  c_man_express      CFLASH_KEY.man_express   
#define  c_key_t1_time      CFLASH_KEY.key_t1_time   
#define  c_key_error        CFLASH_KEY.key_error     




#define init_man_open         0x01
#define init_man_close        0x02
#define init_debounce_time    20            
#define init_man_express      0x04            
#define init_key_t1_time      200           
#define init_key_error        15000         









#define IMP_UMDR                4           

#define init_rev_pos            400// unused        // 300 for ap reverse distance 
#define init_min_revpos         950 //反转到底
#define init_up_fix             5*IMP_UMDR
#define init_down_fix           10*IMP_UMDR
#define init_AP_rev_stop_delay  4           
#define init_pwnum              4-1        
#define init_d1_max             200        
#define init_d1_min            -250 //-250       
#define init_in_comp1           10         
#define init_in_comp2           20         
#define init_in_comp3           30         
#define init_in_comp4           80         
#define init_beak_offset        1000       
#define init_acc_max            50         
#define init_acc_min            -5000      
#define init_es_pointe          0          
#define init_es_pointd          0          
#define init_es_pointc          0          
#define init_es_pointb          0         
#define init_es_pointa          0         
#define init_es_thdoffe         0       
#define init_es_thdoffd         0        
#define init_es_thdoffc         0          
#define init_es_thdoffb         0          
#define init_es_thdoffa         0        


#define init_n_v_factor        50//55
#define init_thd_v_factor      10//17//15 //NOTICE: TABLE  
#define init_stdthd            -1700//-2000// 01850 70N EP22 FL       -2500 // FL 90N  600w slope 90

#define init_stepcnt           12//10//11
#define init_fixthd            400//IS21 front right door is bad quality. For cold ap force adjust!
#define init_slope              35//40

#define init_rf_iniup           800 //600  //1200        
#define init_rf_inidown         2000 //3000       
#define init_rf_width           20     
#define init_rrd1               4 //2  //1     
#define init_rrd2               1 //8  //1     
#define init_rf_delay           10 //10       
struct strk_gen_flsh
       {
        uint8_t    motor_stop_delay;     
        uint8_t    tolerance_max;     
        uint8_t    hall_tout_close;  
        uint8_t    hall_tout_open;   
       };

extern _Init_Static_Rom const struct strk_gen_flsh CFLASH_GEN;

#define  c_motor_stop_delay    CFLASH_GEN.motor_stop_delay 
#define  c_tolerance_max       CFLASH_GEN.tolerance_max 
#define  c_hall_tout_close     CFLASH_GEN.hall_tout_close
#define  c_hall_tout_open      CFLASH_GEN.hall_tout_open



#define init_motor_stop_delay    50   //50*2=100ms
#define init_tolerance_max       15 
#define init_hall_tout_close     30  //40*10ms=400ms  
#define init_hall_tout_open      30  //40*10ms=400ms

#define psw_Checksum           0xFFFF  




#define init_d1d2_thd1       0  //-100
#define init_d1d2_thd2       0 //-250
#define init_sfilter_cnt    0     //10
#define init_sfilter_length 0     //12

#define init_apthd_stup_offset      1000
//#define init_thd_off_mul     14
#define init_thd_off_mul            1    //set 0 when calibration
#define        init_volt_crank_val        20    //2V
#define        init_crank_time            30    //60ms
#define        init_volt_tremble_val      5     //0.5V
#define        init_tremble_time          20    //40ms
#define		   init_min_room_temp_norm   4000

typedef struct 
{
   uint8_t EE_Par_Customer;
   uint8_t EE_Par_VehicleType;
   uint8_t EE_Par_DoorType;
   uint8_t EE_Par_version;
   uint8_t EE_RKEDelay;
}strk_eedat2;


extern _Init_Static_Rom const strk_eedat2 CFLASH_EEDAT2;

#define c_ee_Par_Customer       CFLASH_EEDAT2.EE_Par_Customer
#define c_ee_Par_VehicleType    CFLASH_EEDAT2.EE_Par_VehicleType
#define c_ee_Par_DoorType       CFLASH_EEDAT2.EE_Par_DoorType
#define c_ee_Par_Ver            CFLASH_EEDAT2.EE_Par_version
#define c_ee_RKEDelay           CFLASH_EEDAT2.EE_RKEDelay


#define init_ee_Par_Customer     0x24   //0X09:KC-2;  0X0A:FE-6 ;0X03:AP13;0X04:KC-1;0x05:FE-7 ;0x06:FE-5 0x24:AP32
#define init_ee_Par_VehicleType  0x01   //

#ifdef DOOR_FL
	#define init_ee_Par_DoorType     0x20   //FL :0x20; FR :0x21;RL :0x22;RR :0x23;
#endif
#ifdef DOOR_FR
	#define init_ee_Par_DoorType     0x21   //FL :0x20; FR :0x21;RL :0x22;RR :0x23;
#endif
#ifdef DOOR_RL
	#define init_ee_Par_DoorType     0x22   //FL :0x20; FR :0x21;RL :0x22;RR :0x23;
#endif
#ifdef DOOR_RR
	#define init_ee_Par_DoorType     0x23   //FL :0x20; FR :0x21;RL :0x22;RR :0x23;
#endif


#define init_ee_Par_Ver          0x01
#define init_ee_RKEDelay         0x01   //0x01*25*2ms=50ms;车窗延时动作



#define init_min_delay      15//20   //120
#define init_set_rr         1500//1800//EP22-1800falseAP  //1500 //default: 0  RR1.1   : 1500
#define init_rr_inimin       400//350   //default :400 RR1.1: 350



#define        init_hf_width_max_f1      3
#define        init_hf_width_max_f2      3
#define        init_hf_d1d2_pos          1000
#define        init_hf_d1d2_neg          -1000
#define        init_hf_lov               130//110//80
#define        init_hf_lospeed           3600
#define        init_hf_point0_d1d2       -100
#define        init_hf_point1_count      6//1
#define        init_hf_dn1              -235//-300
#define        init_hf_dn2               -235//-300
#define        init_hf_point2_count      6//2
#define        init_hf_dn3               -235//-300
#define        init_hf_dn4               -235//-300
        
#define        init_hf_su_width_max_f1   6
#define        init_hf_su_width_max_f2   6
#define        init_hf_su_d1d2_pos       1000
#define        init_hf_su_d1d2_neg       -500

#define        init_hf_su_point1_count   1
#define        init_hf_su_dn1            -300//-1000
#define        init_hf_su_dn2            -300//-1000
#define        init_hf_su_point2_count   2
#define        init_hf_su_dn3            -300//-1000
#define        init_hf_su_dn4            -300//-1000

extern _Init_Static_Rom const uint32_t PW_N_VAL;
#undef struct



#endif







