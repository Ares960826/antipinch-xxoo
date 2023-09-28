
#ifndef APPARAM_H_
#define APPARAM_H_

#include "Typedef.h"
#include "appl_const.h"

/*
	these parameter define ref  appl__Init_Static_Rom const.h
	*/
/*
#define CEnable_SIMDATASEND			0x3830
#define CDisable_Adapt					0x3831
#define CDisable_RROAD					0x3832
#define CEnable_ADAPT2		      0x3833
#define CDisable_AP_STARTUP			0x3834
#define CDisable_SFILTER				0x3835
#define CDisable_AP							0x3836
#define CDisable_AP_BLOCK				0x3837
#define CDisable_AP_D2					0x3838
#define CEnable_VOLTAGE_LOCK	  0x3839
#define Disable_AP_STUP1				0x383A
#define Disable_AP_STUP2				0x383B
#define CDisable_AP_10S		  		0x383C
#define CDisable_TABLE_OFF			0x383D


#define C_EN_SIMDATASEND    CFLASH_CFUNCSW.EN_SIMDATASEND
#define C_DIS_ADAPT         CFLASH_CFUNCSW.DIS_ADAPT
#define C_DIS_RROAD         CFLASH_CFUNCSW.DIS_RROAD
#define C_USE_ADAPT2     	  CFLASH_CFUNCSW.USE_ADAPT2
#define C_DIS_APSTARTUP     CFLASH_CFUNCSW.DIS_APSTARTUP
#define C_DIS_SFILTER       CFLASH_CFUNCSW.DIS_SFILTER
#define C_DISABEL_AP        CFLASH_CFUNCSW.DISABLE_AP
#define C_DIS_AP_BLOCK      CFLASH_CFUNCSW.DIS_AP_BLOCK
#define C_DIS_AP_D2		    	CFLASH_CFUNCSW.DIS_AP_D2
#define C_EN_VLOT_LOCK      CFLASH_CFUNCSW.EN_VOLT_LOCK
#define C_DIS_TABLE_OFF     CFLASH_CFUNCSW.DIS_TABLE_OFF
*/

struct strc_adapt_flsh
{
		uint8_t  ADA_MAX1;         
		uint8_t  ADA_MAX2;         
		uint8_t  ADA_INI_START;    
		uint8_t  ADA_SHIFT_POS;    
		uint8_t  ADA_NOUSED;        
		uint8_t  ADA_NOUSED2;           
		uint16_t TAB_ADA_INI[8];   
};

struct strc_AP_flsh
       {

         uint16_t    rev_pos;
         uint16_t    min_revpos;
         uint8_t  up_fix;
         uint8_t  down_fix;
         uint8_t  AP_rev_stop_delay;

         uint8_t  pwnum;
         int16_t    d1_max;
         int16_t    d1_min;
         int16_t    in_comp1;
         int16_t    in_comp2;
         int16_t    in_comp3;
         int16_t    in_comp4;
         int16_t    beak_offset;
         int16_t    acc_max;
         int16_t    acc_min;

         uint8_t  es_pointe;
         uint8_t  es_pointd;
         uint8_t  es_pointc;
         uint8_t  es_pointb;
         uint8_t  es_pointa;
         int16_t    es_thdoffe;
         int16_t    es_thdoffd;
         int16_t    es_thdoffc;
         int16_t    es_thdoffb;
         int16_t    es_thdoffa;

         uint8_t  n_v_factor;
         uint8_t  thd_v_factor;
         int16_t    stdthd ;

         uint8_t  stepcnt;
         uint16_t   fixthd;
         uint8_t   slope;

         uint16_t   rf_iniup;
         uint16_t   rf_inidown;
         uint8_t   rf_width;
         uint8_t   rrd1;
         uint8_t   rrd2;
         uint8_t   rf_delay;
         
        uint8_t    min_delay; //lowvoltage;
        int16_t        set_rr;     //lv_thd2;
        uint16_t      rr_ini_min;
         uint8_t     hf_WIDTH_MAX;
         uint8_t     hf_WIDTH_MAX2;
         int16_t      hf_D1D2_POS;
         int16_t      hf_D1D2_NEG;
         uint8_t     hf_LOV;
         uint16_t    hf_LOSPEED;
         int16_t      hf_POINT0_D1D2;
         uint8_t     hf_POINT1_COUNT;
         int16_t      hf_DN1;
         int16_t      hf_DN2;
         uint8_t     hf_POINT2_COUNT;
         int16_t      hf_DN3;
         int16_t      hf_DN4;

         uint8_t     hf_SU_WIDTH_MAX;
         uint8_t     hf_SU_WIDTH_MAX2;
         int16_t      hf_SU_D1D2_POS;
         int16_t      hf_SU_D1D2_NEG;
         uint8_t     hf_SU_POINT1_COUNT;
         int16_t      hf_SU_DN1;
         int16_t      hf_SU_DN2;
         uint8_t     hf_SU_POINT2_COUNT;
         int16_t      hf_SU_DN3;
         int16_t      hf_SU_DN4;
 
        int16_t        apthd_stup_offset;     //
        uint8_t    thd_off_mul;
               
         };
			 
struct strc_volt_flsh
{
			uint8_t    volt_crack_val;
			uint16_t     crank_time;
			uint8_t    volt_tremble_val;
			uint16_t     tremble_time;
			uint16_t     Norm_Min_Room_Temp;
};

struct strc_func_sw
{
		uint16_t    EN_SIMDATASEND;
		uint16_t    DIS_ADAPT;
		uint16_t    DIS_RROAD;
		uint16_t    USE_ADAPT2;
		uint16_t    DIS_APSTARTUP;
		uint16_t    DIS_SFILTER;
		uint16_t    DISABLE_AP;
		uint16_t    DIS_AP_BLOCK;
		uint16_t    DIS_AP_D2;
		uint16_t    EN_VOLT_LOCK;
		uint16_t    DIS_TABLE_OFF;
};


 
#define C_ADABUF_SIZE  	8
#define C_ADAVAL_SEAL 	4
#define C_ADAVAL_MAX    10


#define  C_ADAVAL_MAX1          CFLASH_ADAPT.ADA_MAX1
#define  C_ADAVAL_MAX2          CFLASH_ADAPT.ADA_MAX2

#define  C_ADA_INI_START        CFLASH_ADAPT.ADA_INI_START
#define  C_ADA_SHIFT_POS        CFLASH_ADAPT.ADA_SHIFT_POS

#define  C_ADA_NOUSED           CFLASH_ADAPT.ADA_NOUSED
#define  C_ADA_NOUSED2          CFLASH_ADAPT.ADA_NOUSED2

#define  C_TAB_ADA_INI          CFLASH_ADAPT.TAB_ADA_INI
#define  C_SIZE_TAB_ADA         sizeof(CFLASH_ADAPT.TAB_ADA_INI)/2


#define init_ADA_MAX1       15     
#define init_ADA_MAX2        5     
#define init_ADA_INI_START  15     
#define init_ADA_SHIFT_POS    2     

#define init_ADA_NOUSED1      2     
#define init_ADA_NOUSED2      2     

#define init_TAB_ADA_INI0  0xFFFF  
#define init_TAB_ADA_INI1  0xFFFF  
#define init_TAB_ADA_INI2  0x8888  
#define init_TAB_ADA_INI3  0x4568  
#define init_TAB_ADA_INI4  0x1122  
#define init_TAB_ADA_INI5  0x0000  
#define init_TAB_ADA_INI6  0x0000  
#define init_TAB_ADA_INI7  0x0000 




#define C_AP_REV_POS          CFLASH_AP.rev_pos
#define C_AP_MIN_REVPOS       CFLASH_AP.min_revpos
#define C_UP_FIX              CFLASH_AP.up_fix
#define C_DOWN_FIX            CFLASH_AP.down_fix
#define C_APREV_STOP_DELAY    CFLASH_AP.AP_rev_stop_delay
#define C_AP_PWNUM            CFLASH_AP.pwnum
#define C_AP_D1_MAX           CFLASH_AP.d1_max
#define C_AP_D1_MIN           CFLASH_AP.d1_min
#define C_AP_IN_COMP1         CFLASH_AP.in_comp1
#define C_AP_IN_COMP2         CFLASH_AP.in_comp2
#define C_AP_IN_COMP3         CFLASH_AP.in_comp3
#define C_AP_IN_COMP4         CFLASH_AP.in_comp4
#define C_AP_BEAK_OFFSET      CFLASH_AP.beak_offset
#define C_AP_ACC_MAX          CFLASH_AP.acc_max
#define C_AP_ACC_MIN          CFLASH_AP.acc_min
#define C_AP_ES_POINTE        CFLASH_AP.es_pointe
#define C_AP_ES_POINTD        CFLASH_AP.es_pointd
#define C_AP_ES_POINTC        CFLASH_AP.es_pointc
#define C_AP_ES_POINTB        CFLASH_AP.es_pointb
#define C_AP_ES_POINTA        CFLASH_AP.es_pointa
#define C_AP_ES_THDOFFE       CFLASH_AP.es_thdoffe
#define C_AP_ES_THDOFFD       CFLASH_AP.es_thdoffd
#define C_AP_ES_THDOFFC       CFLASH_AP.es_thdoffc
#define C_AP_ES_THDOFFB       CFLASH_AP.es_thdoffb
#define C_AP_ES_THDOFFA       CFLASH_AP.es_thdoffa
#define C_AP_N_V_FACTOR       CFLASH_AP.n_v_factor
#define C_AP_THD_V_FACTOR     CFLASH_AP.thd_v_factor
#define C_AP_STDTHD           CFLASH_AP.stdthd

#define C_AP_STEPCNT          CFLASH_AP.stepcnt
#define C_AP_FIXTHD           CFLASH_AP.fixthd
#define C_AP_SLOPE            CFLASH_AP.slope

#define C_APRF_INIUP          CFLASH_AP.rf_iniup
#define C_APRF_INIDOWN        CFLASH_AP.rf_inidown
#define C_AP_RFWIDTH          CFLASH_AP.rf_width
#define C_AP_RRD1             CFLASH_AP.rrd1
#define C_AP_RRD2             CFLASH_AP.rrd2
#define C_AP_RFDELAY          CFLASH_AP.rf_delay


#define  c_hf_rr_inimin     CFLASH_AP.rr_ini_min
#define  c_hf_set_rr       CFLASH_AP.set_rr        //????????????? ????????
#define  c_hf_min_delay    CFLASH_AP.min_delay     //????????????? ????????
#define c_hf_width_max_f1           CFLASH_AP.hf_WIDTH_MAX
#define c_hf_width_max_f2           CFLASH_AP.hf_WIDTH_MAX2
#define c_hf_d1d2_pos               CFLASH_AP.hf_D1D2_POS
#define c_hf_d1d2_neg               CFLASH_AP.hf_D1D2_NEG
#define c_hf_lov                    CFLASH_AP.hf_LOV
#define c_hf_lospeed                CFLASH_AP.hf_LOSPEED
#define c_hf_point0_d1d2            CFLASH_AP.hf_POINT0_D1D2
#define c_hf_point1_count           CFLASH_AP.hf_POINT1_COUNT
#define c_hf_dn1                    CFLASH_AP.hf_DN1
#define c_hf_dn2                    CFLASH_AP.hf_DN2
#define c_hf_point2_count           CFLASH_AP.hf_POINT2_COUNT
#define c_hf_dn3                    CFLASH_AP.hf_DN3
#define c_hf_dn4                    CFLASH_AP.hf_DN4
#define c_hf_su_width_max_f1        CFLASH_AP.hf_SU_WIDTH_MAX
#define c_hf_su_width_max_f2        CFLASH_AP.hf_SU_WIDTH_MAX2
#define c_hf_su_d1d2_pos            CFLASH_AP.hf_SU_D1D2_POS
#define c_hf_su_d1d2_neg            CFLASH_AP.hf_SU_D1D2_NEG
#define c_hf_su_point1_count        CFLASH_AP.hf_SU_POINT1_COUNT
#define c_hf_su_dn1                 CFLASH_AP.hf_SU_DN1
#define c_hf_su_dn2                 CFLASH_AP.hf_SU_DN2
#define c_hf_su_point2_count        CFLASH_AP.hf_SU_POINT2_COUNT
#define c_hf_su_dn3                 CFLASH_AP.hf_SU_DN3
#define c_hf_su_dn4                 CFLASH_AP.hf_SU_DN4

#define  c_apthd_stup_offset       CFLASH_AP.apthd_stup_offset 
#define  c_thd_off_mul             CFLASH_AP.thd_off_mul

/*
#define IMP_UMDR                4           
#define init_rev_pos            350 //150mm         // 300 for ap reverse distance 
#define init_min_revpos         950 //????
#define init_up_fix             18*IMP_UMDR
#define init_down_fix           25*IMP_UMDR
#define init_AP_rev_stop_delay  1 // 1*10ms =10ms   4 *2ms =  8ms           
#define init_pwnum              4-1        
#define init_d1_max             200        
#define init_d1_min             -310       
#define init_in_comp1           15 //10         
#define init_in_comp2           30//20         
#define init_in_comp3           50 //30         
#define init_in_comp4           80 //80         
#define init_beak_offset        1000//500       
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
#define init_n_v_factor         45 // 50       //120
#define init_thd_v_factor        8 //12       //NOTICE: TABLE  
#define init_stdthd              -1400 //-1800 //-2800 //ver929=-2800      
#define init_stepcnt           14//11
#define init_fixthd           0//400//800//600//500    //IS21 front right door is bad quality. For cold ap force adjust!
#define init_slope              40
#define init_rf_iniup           800 //600  //1200        
#define init_rf_inidown         2500 //3000       
#define init_rf_width           25// 20     
#define init_rrd1               4 //2  //1     
#define init_rrd2               1 //8  //1     
#define init_rf_delay           20 //10       
#define init_min_delay      30   //20
#define init_set_rr         1500 //3500
#define init_rr_inimin       400
#define        init_hf_width_max_f1      3
#define        init_hf_width_max_f2      3
#define        init_hf_d1d2_pos          1000
#define        init_hf_d1d2_neg          -1000
#define        init_hf_lov               110
#define        init_hf_lospeed           7500
#define        init_hf_point0_d1d2       -100
#define        init_hf_point1_count      3
#define        init_hf_dn1               -250
#define        init_hf_dn2               -250
#define        init_hf_point2_count      3
#define        init_hf_dn3               -250
#define        init_hf_dn4               -250
      
#define        init_hf_su_width_max_f1   6
#define        init_hf_su_width_max_f2   6
#define        init_hf_su_d1d2_pos       1000
#define        init_hf_su_d1d2_neg       -500

#define        init_hf_su_point1_count   1
#define        init_hf_su_dn1            -300
#define        init_hf_su_dn2            -300
#define        init_hf_su_point2_count   2
#define        init_hf_su_dn3            -300
#define        init_hf_su_dn4            -300

#define 		init_apthd_stup_offset      1000
#define 		init_thd_off_mul            1    //set 0 when calibration
*/


#define  c_volt_crank_val       CFLASH_VOLTAGE.volt_crack_val 
#define  c_crank_time           CFLASH_VOLTAGE.crank_time 
#define  c_volt_tremble_val     CFLASH_VOLTAGE.volt_tremble_val
#define  c_tremble_time         CFLASH_VOLTAGE.tremble_time
#define  c_room_temp_min_norm  	CFLASH_VOLTAGE.Norm_Min_Room_Temp



/*
#define        init_volt_crank_val        20    //2V
#define        init_crank_time            30    //60ms
#define        init_volt_tremble_val      5     //0.5V
#define        init_tremble_time          20    //40ms
*/	 

			 
extern _Init_Static_Rom const struct strc_AP_flsh 		CFLASH_AP;
extern _Init_Static_Rom const struct strc_adapt_flsh 	CFLASH_ADAPT;
extern _Init_Static_Rom const struct strc_volt_flsh 		CFLASH_VOLTAGE;
extern _Init_Static_Rom const struct strc_func_sw 		CFLASH_CFUNCSW;
extern _Init_Static_Rom const uint32_t PW_N_VAL;
//extern _Init_Static_Rom const uint8_t CFLASH_TABLE_THD[72];
extern _Init_Static_Rom const uint8_t  TABLE_THD_V_OFFS[72];
#endif
