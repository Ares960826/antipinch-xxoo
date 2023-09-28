
#include "Typedef.h"
#include "complier_sw.h"
#include "appl_const.h"
#include "param.h"


#define EE_INIT(X)  =X

__attribute__((__section__(".check_data")))  const uint16_t  EE_CHKSUM       EE_INIT(0xFFFF); //(0xFFFF) ; /*factory  */


__attribute__((__section__(".check_data")))  const uint16_t  EE_LEN          EE_INIT(0x01FE);


_Init_Static_Rom const strk_eedat2 CFLASH_EEDAT2 =
  {
   init_ee_Par_Customer ,         
   init_ee_Par_VehicleType,     
   init_ee_Par_DoorType,
   init_ee_Par_Ver,          
   init_ee_RKEDelay 
  };

_Init_Static_Rom const strk_eedat1 CFLASH_EEDAT1 =
  {
   init_ee_ID,
   init_ee_freechar,
   init_ee_valid_file,
   init_ee_par_versionh,
   init_ee_par_versionl
  };

#if 1

	


 _Init_Static_Rom const struct strk_positionen CFLASH_POSITION =
 {

	   init_max_pos,
	   init_pos_cal_bot_pos
 };


_Init_Static_Rom const struct strk_thermo_flsh CFLASH_THERMO =
 {
  init_motor_ini_temp,     
  init_motor_cooling_point, 
  init_motor_min_temp,    
  init_motor_heating_point, 
  init_motor_limit3,     
  init_motor_limit2,     
  init_motor_limit1,     
  init_motor_turnon_thd          
 };


_Init_Static_Rom const struct strk_key_flsh CFLASH_KEY =
      {
       init_man_open,      
       init_man_close,     
       init_debounce_time, 
       init_man_express,   
       init_key_t1_time,   
       init_key_error      
      };




  

_Init_Static_Rom const struct strk_gen_flsh CFLASH_GEN =
      {
       init_motor_stop_delay,      
       init_tolerance_max,      
       init_hall_tout_close,   
       init_hall_tout_open     
      };




_Init_Static_Rom const strk_psw_flsh1 CFLASH_PSW =
      {
		 CHALLDIR,           			//hall ·½Ïò
		 CMOTOR_DIRECTION+100,        	//motor ·½Ïò
		 CEnable_SIMDATASEND+100, 		  //·ÂÕæÊý¾Ý·¢ËÍ disable
		 CDisable_Adapt+100,            //×ÔÊÊÓ¦ enable
		 CDisable_RROAD+100,      		  //»µÂ·ÂË²¨ enable
		 CEnable_ADAPT2,        	      //ADAPT2 Ê¹ÓÃ
		 CDisable_AP_STARTUP,//+100,     	//Æô¶¯·À¼Ð enable
		 CDisable_SFILTER+100,          //³å»÷ÂË²¨ enable
		 CDisable_AP+100,              	//·À¼Ð¹¦ÄÜ enable 
		 CDisable_AP_BLOCK+100,        	//¶Â×ª·À¼Ð enable
		 CDisable_AP_D2+100,         	  //d2Ëã·¨²ÎÓë enable
		 CEnable_VOLTAGE_LOCK,          //APÐÂËã·¨ enabled	
		 CEnable_ADC_TM+100,            //ADC ÎÂ¶È
		 CDisable_Sleepmode+100,        //ÔÊÐí½øÈëË¯ÃßÄ£Ê½ enable 
		 CDisable_Autokey+100,        	//ÔÊÐíÓÐ×Ô¶¯ÉÏÏÂ¹¦ÄÜ enable
		 CDisable_Thermo+100,           //ÈÈ±£»¤ enable 
		 CDisable_ADC+100,              //ADC enable 
		 CDisable_LINF,                	//lin app disable
		 CDisable_AP_10S,           //±£Áô 
		 CDisable_TABLE_OFF,        //±ê¶¨Ê¹ÓÃµçÑ¹±í¸ñ disable
		 psw_Checksum                	  //checksum

      };


#endif

_Init_Static_Rom const uint8_t  EE_EEPROM_CHECKSUMME_ENDE_= 0x55;

	
#undef struct


_Init_Static_Rom const uint8_t  TABLE_THD_V_OFFS[72]=
			{ 0,4,7,11,14,18,21,25,28,32,
              35,36,37,38,39,41,42,43,44,45,
              46,50,54,58,62,66,70,74,78,82,
              86,89,93,96,99,103,106,109,112,116,
              119,127,136,144,153,161,169,178,186,195, 
              203,204,205,206,207,209,210,211,212,213,
              214,216,218,219,221,223,225,227,228,230,
              232,234
          };
          
                        
          
         

