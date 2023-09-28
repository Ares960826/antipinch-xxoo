

#include "Typedef.h"
#include "apparam.h"
/*
const struct strc_func_sw CFLASH_CFUNCSW =
{
		CEnable_SIMDATASEND+100, 		  //?????? disable
		CDisable_Adapt+100,            //??? enable
		CDisable_RROAD+100,      		  //???? enable
		CEnable_ADAPT2,        	      //ADAPT2 ??
		CDisable_AP_STARTUP,//+100,     	//???? enable
		CDisable_SFILTER+100,          //???? enable
		CDisable_AP+100,              	//???? enable 
		CDisable_AP_BLOCK+100,        	//???? enable
		CDisable_AP_D2+100,         	  //d2???? enable
		CEnable_VOLTAGE_LOCK,          //AP??? enabled	
		CDisable_TABLE_OFF,        //???????? disable
};

*/
_Init_Static_Rom const struct strc_adapt_flsh CFLASH_ADAPT =
 {
  init_ADA_MAX1,       
  init_ADA_MAX2,       
  init_ADA_INI_START,  
  init_ADA_SHIFT_POS,  
  init_ADA_NOUSED1,     
  init_ADA_NOUSED2,        
  {       
  init_TAB_ADA_INI0, 
  init_TAB_ADA_INI1, 
  init_TAB_ADA_INI2, 
  init_TAB_ADA_INI3, 
  init_TAB_ADA_INI4, 
  init_TAB_ADA_INI5, 
  init_TAB_ADA_INI6, 
  init_TAB_ADA_INI7  
  }
 };


_Init_Static_Rom const struct strc_volt_flsh CFLASH_VOLTAGE =
{
		init_volt_crank_val,
		init_crank_time,
		init_volt_tremble_val,
		init_tremble_time,
		init_min_room_temp_norm
};

_Init_Static_Rom const struct strc_AP_flsh CFLASH_AP =
 {
  init_rev_pos,            
  init_min_revpos,         
  init_up_fix,         
  init_down_fix,        
  init_AP_rev_stop_delay,  
  init_pwnum,         
  init_d1_max,           
  init_d1_min,           
  init_in_comp1,             
  init_in_comp2,                    
  init_in_comp3,             
  init_in_comp4,                   
  init_beak_offset,      
  init_acc_max,        
  init_acc_min,        
  init_es_pointe,            
  init_es_pointd,            
  init_es_pointc,            
  init_es_pointb,            
  init_es_pointa,            
  init_es_thdoffe,             
  init_es_thdoffd,             
  init_es_thdoffc,             
  init_es_thdoffb,             
  init_es_thdoffa,             
  init_n_v_factor,       
  init_thd_v_factor,    
  init_stdthd,     
  init_stepcnt,           
  init_fixthd,          
  init_slope,              
  init_rf_iniup,          
  init_rf_inidown,        
  init_rf_width,          
  init_rrd1,           
  init_rrd2,           
  init_rf_delay,
  
	init_min_delay,
	init_set_rr,
	init_rr_inimin,
	
	init_hf_width_max_f1,
	init_hf_width_max_f2,
	init_hf_d1d2_pos,
	init_hf_d1d2_neg,
	init_hf_lov,
	init_hf_lospeed,
	init_hf_point0_d1d2,
	init_hf_point1_count,
	init_hf_dn1,
	init_hf_dn2,
	init_hf_point2_count,
	init_hf_dn3,
	init_hf_dn4,
	
	init_hf_su_width_max_f1,
	init_hf_su_width_max_f2,
	init_hf_su_d1d2_pos,
	init_hf_su_d1d2_neg,

	init_hf_su_point1_count,
	init_hf_su_dn1,
	init_hf_su_dn2,
	init_hf_su_point2_count,
	init_hf_su_dn3,
	init_hf_su_dn4,

	init_apthd_stup_offset,
	init_thd_off_mul
            
 };
 
_Init_Static_Rom  const uint32_t PW_N_VAL = 5000000;	//AP32 :5000000


/*		USE appl_const.c  TABLE_THD_V_OFFS 
 const uint8_t CFLASH_TABLE_THD[72]=  
{
					
            0,2,4,6,8,10,12,14,16,18,
            20,22,24,26,28,20,22,24,26,28,
            30,32,34,36,38,40,42,44,46,48,
            49,50,51,52,53,54,55,56,57,58,
            60,62,64,66,68,70,72,74,76,78,
            80,82,84,86,88,90,92,94,96,98,
            100,100,100,100,100,100,100,100,100,100,
            100,100
};
*/



 





