
/*******************************************************************************
|  File Name:    keyPort.c
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
#include "lin.h"
#include "lin_cfg.h"
#include "hallpos.h"
#include "motor.h"
#include "sysfunc.h"
#include "param.h"
#include "relay.h"
#include "Ubat.h"
#include "switch.h"
#include "appif.h"
//#include "ap.h"
#include "appl_const.h"
#include "keyport.h"
//#include "thermo.h"


typedef enum {LIN_FL = 0x20,LIN_FR = 0x21,LIN_RL = 0x22,LIN_RR = 0x23};



T_FLAG16 	mctrl_status;  //notice only read
T_FLAG16 	diff_status;
uint16_t AP_ui_AP_off;

LINDriverStatusType LINBusStatus;
volatile T_FLAG8  LA_T8_Flag6;
volatile T_FLAG8  LA_T8_Flag7;
volatile T_FLAG8  LA_T8_Flag8;
volatile T_FLAG8  LA_T8_Flag9;



uint16_t 	SS_ui_StudyStopPos;

// T_FLAG16 diff_status;   //dont need  ap.c def
volatile T_FLAG8 	syst_flag;

volatile uint8_t  	RT_bi_functest_f;

volatile uint16_t   HA_ui_WinPos;			//³µ´°Î»ÖÃ
volatile uint8_t  	LD_uc_NAD1;                /* node address */
volatile uint8_t  	LD_uc_TempNAD;             /* NAD-NAD_FL*/

volatile uint8_t  lin_uc_command=0;
volatile uint8_t  lin_uc_sysmode=0 ;


uint8_t		MB_uc_UpBlockCnt;		 //read
uint8_t		MB_uc_DownBlockCnt;		   //read


uint8_t		MC_uc_MotorStopDelay;  // read & set !!!

uint8_t 	SY_uc_poweron;
volatile uint8_t 	 	SY_uc_poweron_sw;

uint8_t      AD_uc_MotorVoltage;
volatile uint16_t    	BA_ui_Crank_Timeout;
volatile uint16_t    	BA_ui_VoltTremble_Timeout;
volatile uint8_t   		BA_uc_VoltageBuf[4];
volatile uint8_t   		BA_uc_VoltageCnt;

#define BATCP(a,b)  ((a>b)?a-b: b-a) 
uint8_t  SY_bi_Volt_TrembleFlag;




void KeyPort_Init(void)
{
	AP_ui_AP_off = 0;

	//from ad_conv
	SY_bi_BatDrop_happened = FALSE;
	SY_bi_Volt_TrembleFlag = FALSE;


	//from lin_app.c
	LA_T8_Flag6.by=0;
	LA_T8_Flag7.by = 0;
	LA_T8_Flag8.by=0;
	LA_T8_Flag9.by = 0;
	lin_uc_command=0;
	lin_uc_sysmode=0 ;

	LD_uc_NAD1 = c_ee_Par_DoorType;   //c_ee_Par_DoorType

	if((LD_uc_NAD1>=NAD_FL) && (LD_uc_NAD1<=(NAD_FL+3)))
	{
	  LD_uc_TempNAD=LD_uc_NAD1-NAD_FL;
	}
	else
	{
	  LD_uc_TempNAD=0;
	}
		diff_status.cr.wo = 0;
}

uint8_t KeyPort_SaveData(uint8_t* buf)
{
	uint8_t len=0;
	
	return len;

}

void KeyPort_RestoreData(uint8_t* const buf)
{

}


//l_u8_rd_L_Pas_Wdw_CenterSwitch // l_u8_rd_LI0_L_Pas_Wdw_CenterSwitch //Ä£°å

// _rd_L_  //  _rd_LI0_L_

void KeyPort_LinInput(void)
{
	uint8_t tmp;
	 if (l_flg_tst_LI0_BCMSysPwrMd_lL1() == TRUE){

		 	 lin_uc_sysmode = l_u8_rd_LI0_BCMSysPwrMd_lL1();
		    l_flg_clr_LI0_BCMSysPwrMd_lL1();
	 }
	 if (lin_configuration_RAM[2] == 0x8 || lin_configuration_RAM[2] == 0x17){



		 if (l_flg_tst_LI0_DrvrWndShrtMvReq_l() == TRUE){
			  tmp = l_u8_rd_LI0_DrvrWndShrtMvReq_l();
			  if(tmp==1) LA_bi_WndShrtMv_ShrtDrop=1;
			  else if(tmp==2)  LA_bi_WndShrtMv_ShrtRise=1;
			  else{
				LA_bi_WndShrtMv_ShrtDrop=0;
				LA_bi_WndShrtMv_ShrtRise=0;
			  }

			  l_flg_clr_LI0_DrvrWndShrtMvReq_l();
		 }

		 if (l_flg_tst_LI0_DrvrPWLOpEnb_l() == TRUE ){
			 LA_bi_PWLOpEnb1 = l_bool_rd_LI0_DrvrPWLOpEnb_l();
				l_flg_clr_LI0_DrvrPWLOpEnb_l();

		 }

		 if (l_flg_tst_LI0_DrvrWndOpReq_l() == TRUE){
			 lin_uc_command= l_u8_rd_LI0_DrvrWndOpReq_l();
			 if (lin_uc_command<5){

			 }else{
				 lin_uc_command = 0;
			 }
			 l_flg_clr_LI0_DrvrWndOpReq_l();
		 }




		 if (l_flg_tst_LI0_DrvrWndLclSwDsbld_l() == TRUE){
			 LA_bi_PWLlocal_sw_disable = l_bool_rd_LI0_DrvrWndLclSwDsbld_l();
			 l_flg_clr_LI0_DrvrWndLclSwDsbld_l();
		 }

	 }else if (lin_configuration_RAM[2] == 0x9 || lin_configuration_RAM[2] == 0x18){



		 if (l_flg_tst_LI0_FrtPsngWndShrtMvReq_l() == TRUE){
			  tmp = l_u8_rd_LI0_DrvrWndShrtMvReq_l();
			  if(tmp==1) LA_bi_WndShrtMv_ShrtDrop=1;
			  else if(tmp==2)  LA_bi_WndShrtMv_ShrtRise=1;
			  else{
				LA_bi_WndShrtMv_ShrtDrop=0;
				LA_bi_WndShrtMv_ShrtRise=0;
			  }

			  l_flg_clr_LI0_FrtPsngWndShrtMvReq_l();
		 }

		 if (l_flg_tst_LI0_FrtPsngPWLOpEnb_l() == TRUE ){
			 LA_bi_PWLOpEnb1 = l_bool_rd_LI0_FrtPsngPWLOpEnb_l();
			 l_flg_clr_LI0_FrtPsngPWLOpEnb_l();

		 }

		 if (l_flg_tst_LI0_FrtPsngWndOpReq_l() == TRUE){
			 lin_uc_command= l_u8_rd_LI0_FrtPsngWndOpReq_l();
			 if (lin_uc_command<5){

			 }else{
				 lin_uc_command = 0;
			 }
			 l_flg_clr_LI0_FrtPsngWndOpReq_l();
		 }




		 if (l_flg_tst_LI0_FrtPsngWndLclSwDsbld_l() == TRUE){
			 LA_bi_PWLlocal_sw_disable = l_bool_rd_LI0_FrtPsngWndLclSwDsbld_l();
			 l_flg_clr_LI0_FrtPsngWndLclSwDsbld_l();
		 }
	 }


}

void motsts_update()
{
	//AP_bi_CalculateDiffV = HP_TstCalcAPFlg();
	AD_uc_MotorVoltage = Ubat_GetVoltageFiltered();
	HA_ui_WinPos = HP_GetHallWPos();
	SS_ui_StudyStopPos = HP_GetSoftStopPos();
	
	Motor_bi_Running = 	 MOT_TstMotorRunFlg();
	Motor_bi_Dir_Up =  MOT_TstMotorUpFlg();
	Motor_bi_Block_Up = HP_TstBlockUpFlg();
	//Motor_bi_SStopCntCondition =	//used in ap.c , but no ref // test check it
	Motor_bi_Block_Down =  HP_TstBlockDnFlg();
	Motor_bi_InRawSt = 	 !HP_TstPosSysNormFlg();
	Motor_bi_Prv_Updir =  MOT_TstMotorPrvUpFlg();
	//Motor_bi_BeingBlockPos = 
	Motor_bi_Close = MOT_TstMotorCloseFlg();
	Motor_bi_Open =  MOT_TstMotorOpenFlg();
	Motor_bi_Stop =	 MOT_TstMotorStopFlg();
	Motor_bi_BeingInSStopPos = HP_TstInSoftStopPosFlg(); 
}

void KeyPort_Prev(void)
{
   uint16_t   temp_vs=0;
   uint16_t   temp_key=0;

	KeyPort_LinInput();
	MB_uc_DownBlockCnt = HP_GetBlockDownCnt();
	MB_uc_UpBlockCnt = HP_GetBlockUpCnt();
	MC_uc_MotorStopDelay = (uint8_t) MOT_GetMotDelay();    //16->8bit
	motsts_update();
}



void KeyPort_After(void)
{
	 MOT_SetMotStopDelay2ms((uint16_t)MC_uc_MotorStopDelay);	//writeback 
}

void KeyPort_10msTask(void)
{   //powermode cranking

}

void  KeyPort_2msTask(void)
{
       

}





void KEY_UpdateInfoData(void)
{
	
	uint32_t l_ui_temp;
	uint32_t  pos;
	uint8_t tmp;
	tmp= 0;


    if((SW_ub_KeyAct&0x07)== c_man_close) tmp =0x1;
    else if((SW_ub_KeyAct&0x07)== c_man_open) tmp =0x2;
    else if((SW_ub_KeyAct&0x07)== 0x06) tmp =0x3;
    else if((SW_ub_KeyAct&0x07)== 0x05) tmp =0x4;
    else {
    }

    l_u8_wr_LI0_DrvrWndLclSwSts_l(tmp);
		
	tmp = 0;


    if(!Motor_bi_InRawSt)
    {
      SS_ui_StudyStopPos = HP_GetSoftStopPos();
      pos = HP_GetHallWPos();
      if(SS_ui_StudyStopPos )
      {
         l_ui_temp = SS_ui_StudyStopPos;
      }else{
    	  l_ui_temp = c_pos_cal_bot_pos;
      }

	 if(pos>=l_ui_temp)
	 {
		 tmp = 200;

	 }
	 else
	 {
	   if(pos<c_tolerance_max)
	   {
		   tmp = 0;
	   }
	   else
	   {

			tmp =(uint8_t )(((unsigned long)pos*200+ (l_ui_temp/2))/(unsigned long)l_ui_temp) ;

	   }
	 }




      l_u8_wr_LI0_DrvrWndDclnSpc_l(tmp);


    }
    else
    {
    	l_u8_wr_LI0_DrvrWndDclnSpc_l(0xff);

    }
        
//HHneed
	if (TP_TstThermalPFlg())
	{
		l_bool_wr_LI0_DrvrPWLThrmlProtnA_l(1);
	}
	else
	{
		l_bool_wr_LI0_DrvrPWLThrmlProtnA_l(0);
	}

	if (REL_TstRelAStuckFlg()||REL_TstRelBStuckFlg())
	{
		tmp = 1;
	}
	else{
		tmp = 0;
	}
	l_bool_wr_LI0_DrvrPWLRelayFltDetc_l(tmp);

	//window initialize
    if(!HP_TstPosSysNormFlg()) //LA_bi_WinInitialSt=1; //window initialize
	{
    	l_bool_wr_LI0_DrvrPWLNotNormd_l(1);
	}else
	{
		l_bool_wr_LI0_DrvrPWLNotNormd_l(0);
	}
    if(APF_TstAPOffFlg())//LA_bi_Wdw_Obs_InhibitSts=1;
    {
    	l_bool_wr_LI0_DrvrPWLHiEftCndA_l(1);
	}
    else
    {
    	l_bool_wr_LI0_DrvrPWLHiEftCndA_l(0);
	}
    if(APF_TstInRev())
	{
    	l_bool_wr_LI0_DrvrPWLRevsng_l(1);
	}
	else
	{
		l_bool_wr_LI0_DrvrPWLRevsng_l(0);
	}
	if (HP_TstHallErrFlg() == TRUE)
	{
		tmp = 1;
	}
	else{
		tmp = 0;
	}
	l_bool_wr_LI0_DrvrPWLSnsngSysFltDetc_l(tmp);

    //lin err
    //if(LD_bi_response_err)LA_bi_LinResponseERR=1;  //work not corretly   
		//l_bool_wr_DDAPWL_01_LIN_Response_Error(0);  //Hh test it check
    //volt
	

		
	}

	
//bool_t APF_TstAPRdyFlg(void)
//{
//	return 	  0;
//}
//
//bool_t APF_TstAPOffFlg(void)
//{
//	bool_t ret =false;
//
//	return ret;
//
//}
//
//bool_t APF_TstInRev(void)
//{
//   return 0;
//
//}






///////////////////////END FILE/////////////////////////////
