/*******************************************************************************
|  File Name:    Hallpos.c
|  Description:  Hall & Window Position handle
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
|
|******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "system_XL6600.h"
//#include "Mcu.h"
#include "OS.h"
#include "xl_nvic.h"
#include "Types.h"
#include "Typedef.h"
#include "complier_sw.h"
//#include "port_user.h"
//#include "ccu6_user.h"
//#include "cpu_User.h"
#include "param.h"
#include "Hallpos.h"
#include "motor.h"
#include "apfunc.h"
#include "string.h"
#include "thermo.h"
#include "keyport.h"
#include "appl_const.h"
#define MAX_U16 (65535U)
#include "IRQCall.h"
#include "testmode.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
 

#define C_60S_B5 		12u

/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static void Hall_Process(void);
static void Position_Process(void);
static void SoftStop_Process(void);
static void HallTimeOut_Process(void);
static void Motor_Blocked(void);


//uint8_t buf[20]={'H','E','L','L','O',' ','W','O','R','L','D','!',' ',' ',' ',' ',' ',' ','H','H'};
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*
typedef struct{
	volatile bool_t	bl_HallDir;
	volatile bool_t	bl_HallSpd;
	volatile uint16_t u16_HallPW;
	volatile uint16_t u16_WinPosI;

	volatile uint16_t u16_WinPos;				//save
	
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
*/

_Init_SAVE_RAM HallPosData_t HallPosData;

	
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/



void HP_Init(void)
{

	HallPosData.bl_HallDir = bsc_Get_HALL_DIR_Stat();
	HallPosData.bl_HallSpd = bsc_Get_HALL_SPD_Stat();
	HallPosData.u16_HallPW =0;
	

	//HallPosData.u16_WinPos = 0;//CHANGE TO POR
	//HallPosData.u16_WinPosI = 0;//CHANGE TO POR
	//HallPosData.u8_BlockUpCnt = 0;//CHANGE TO POR
	//HallPosData.u8_BlockDownCnt = 0;//CHANGE TO POR
	//HallPosData.u16_SoftStopPos =0;//CHANGE TO POR
	//HallPosData.u8_SoftStopCnt=0;//CHANGE TO POR
	
	
//	HallPosData.Flg.Bits.bl_PosSysNormFlg = FALSE;//CHANGE TO POR
//	HallPosData.Flg.Bits.bl_BeingBlockPos = FALSE;//CHANGE TO POR
//	HallPosData.Flg.Bits.bl_InSSTPosFlg = FALSE;//CHANGE TO POR
//	HallPosData.Flg.Bits.bl_SSTCntFlg = FALSE;	//CHANGE TO POR
//	HallPosData.Flg.Bits.bl_SSTPosFlg = FALSE;//CHANGE TO POR

	HallPosData.Flg2.Bits.bl_BlockDn = FALSE;
	HallPosData.Flg2.Bits.bl_BlockUp = FALSE;
	HallPosData.Flg2.Bits.bl_PosChangeFlg = FALSE;
	HallPosData.Flg2.Bits.bl_CalcAP = FALSE;
    HallPosData.Flg2.Bits.bl_InAPZoneFlg = FALSE;
    HallPosData.Flg2.Bits.bl_InAPZone4_20Flg = FALSE;
	HallPosData.Flg2.Bits.bl_InAPZone20_200Flg = FALSE;
	HallPosData.Flg2.Bits.bl_InBeakZoneFlg= FALSE;


	HallPosData.u16_MaxPos=0;
	HallPosData.u16_NegativePos = 0 ;
	HallPosData.u16_UninitDnPos = 0 ;
	HallPosData.u16_HallErrorCnt=0;
	HallPosData.bl_HallTimeOutFlg = FALSE;
	HallPosData.u16_HallTimeOutCnt = HallPosConfig.u16_hall_tout_val;
	HallPosData.u16_DTC_HallErrCnt=0;
	HallPosData.u8_RunTimeCnt = 0;
	


	//((HP_Save_t* )buf) ->u16_SoftStopPos = HallPosData.u16_SoftStopPos;
	//	((HP_Save_t* )buf) ->u16_WinPos = HallPosData.u16_WinPos;
	//	((HP_Save_t* )buf) ->u8_BlockDownCnt = HallPosData.u8_BlockDownCnt;
	//	((HP_Save_t* )buf) ->u8_BlockUpCnt = HallPosData.u8_BlockUpCnt;
	//	((HP_Save_t* )buf) ->u8_SoftStopCnt = HallPosData.u8_SoftStopCnt;
	//	((HP_Save_t* )buf) ->Flg.Ubyte = HallPosData.Flg.Ubyte;
}


void HP_Task(void)
{
		Hall_Process();		// ������������������ݻ��¼����������ڵ�����ƻ�λ�ü��
		HallTimeOut_Process();	// ��������������ĳ�ʱ�¼����������ڴ��������ϻָ�
		#ifdef AP_SIM_DEBUG
			APF_SendData();
		#endif	
		Position_Process();	// ����λ����صļ�����¼����������ڵ�����ƻ򵼺�
		SoftStop_Process(); // ������ֹͣ�߼�����������ƽ����ֹͣ����������豸
}


void HP_10ms_Job(void)
{
	if(HallPosData.u16_HallTimeOutCnt > 0)
	{
			HallPosData.u16_HallTimeOutCnt--;
	}
}
void HP_5s_Job(void)
{
	HallPosData.u16_HallErrorCnt = 0; 
	if (HallPosData.u8_RunTimeCnt > 0u)
	{
		HallPosData.u8_RunTimeCnt--;
	}
}

//Hh added for AP_Disable
void HP_SetNegPos(uint16_t pos)
{
	HallPosData.u16_NegativePos = pos;
}


bool_t HP_GetHallDirection(void)
{
	return(HallPosData.bl_HallDir);
}

bool_t HP_TstHallTimeOutFlg(void)
{
	bool_t ret=FALSE;
	if(HallPosData.u16_HallTimeOutCnt==0)
	{
		ret = TRUE;
	}
	return(ret);
}

void HP_ResetBlockUpCnt()
{
		HallPosData.u8_BlockUpCnt = 0;
		
}

uint8_t HP_GetBlockUpCnt()
{
		return (HallPosData.u8_BlockUpCnt);
		
}
uint8_t HP_GetBlockDownCnt()
{
		return (HallPosData.u8_BlockDownCnt);
		
}

void HP_ResetBlockDownCnt()
{
	HallPosData.u8_BlockDownCnt = 0;
}


void HP_Hall_TCntReload(void)
{
	HallPosData.u16_HallTimeOutCnt = HallPosConfig.u16_hall_tout_val;
}

uint16_t HP_GetHallPulseWidth(void)
{
	return(HallPosData.u16_HallPW);
}
uint8_t HP_GetHallErrorCnt(void)
{
	return(HallPosData.u16_HallErrorCnt);
}
uint16_t HP_GetHallWPos(void)
{
		return(HallPosData.u16_WinPos);
}

uint16_t HP_GetMaxWinPos(void)
{
		return(HallPosData.u16_MaxPos);
}
uint16_t HP_GetSoftStopPos(void)
{
		return(HallPosData.u16_SoftStopPos);
}
bool_t HP_TstPosChangeFlg(void)
{
		return(HallPosData.Flg2.Bits.bl_PosChangeFlg);

}
void HP_ClrPosChangeFlg(void)
{
		HallPosData.Flg2.Bits.bl_PosChangeFlg = FALSE;
}
bool_t HP_TstCalcAPFlg(void)
{
		return(HallPosData.Flg2.Bits.bl_CalcAP);
	
}
void HP_ClrCalcAPFlg(void)
{
		HallPosData.Flg2.Bits.bl_CalcAP = FALSE;
}


bool_t HP_TstInSoftStopPosFlg(void)
{
		return(HallPosData.Flg.Bits.bl_InSSTPosFlg);

}


void HP_ClrInSoftStopPosFlg(void)
{
	HallPosData.Flg.Bits.bl_InSSTPosFlg = FALSE;
}



bool_t HP_TstBlockUpFlg(void)
{
		return(HallPosData.Flg2.Bits.bl_BlockUp);
}

void HP_ClrBlockUpFlg(void)
{
	HallPosData.Flg2.Bits.bl_BlockUp = FALSE;
	HallPosData.Flg.Bits.bl_BeingBlockPos = FALSE;	//only for HallPos
}

bool_t HP_TstBlockDnFlg(void)
{
	return(HallPosData.Flg2.Bits.bl_BlockDn);
}
void HP_ClrBlockDnFlg(void)
{
	HallPosData.Flg2.Bits.bl_BlockDn = FALSE;
}

bool_t HP_TstInAPZoneFlg(void)
{
		return(HallPosData.Flg2.Bits.bl_InAPZoneFlg);

}
bool_t HP_TstInAPZone4_20Flg(void)
{
		return(HallPosData.Flg2.Bits.bl_InAPZone4_20Flg);

}
bool_t HP_TstInAPZone20_200Flg(void)
{
		return(HallPosData.Flg2.Bits.bl_InAPZone20_200Flg);

}

bool_t HP_TstInBeakZoneFlg(void)
{
		return(HallPosData.Flg2.Bits.bl_InBeakZoneFlg);
}

bool_t HP_TstPosSysNormFlg(void)
{
		return(HallPosData.Flg.Bits.bl_PosSysNormFlg);

}
bool_t HP_TstHallErrFlg(void)
{
	bool_t ret=FALSE;
	if (HallPosData.u16_DTC_HallErrCnt != 0u)
	{
		ret= TRUE;
	}
	return ret;

}
void HP_Normalize_EnteyCall(void)
{
	CPU_ENTER_CRITICAL();
	HallPosData.u16_WinPos = 0 ; 
	HallPosData.u16_WinPosI = 0; 
	CPU_EXIT_CRITICAL();
	HallPosData.Flg.Bits.bl_PosSysNormFlg = TRUE;
	HallPosData.u16_NegativePos = 0;
	HallPosData.u16_UninitDnPos = 0;
	
}
void HP_Normalize_ExitCall(void)
{
	CPU_ENTER_CRITICAL();
	HallPosData.u16_WinPos = 0 ; 
	HallPosData.u16_WinPosI = 0; 
	CPU_EXIT_CRITICAL();
	HallPosData.Flg.Bits.bl_PosSysNormFlg = FALSE;	
	HallPosData.u16_NegativePos = 0;
	HallPosData.u16_UninitDnPos = 0;
}


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
static void Hall_Process(void)
{
		uint8_t u8_tmp;
	    for(u8_tmp = 40; u8_tmp > 0; --u8_tmp) // ѭ�������������Ƿ��ȶ�
	    {
	        if (HallPosData.bl_HallDir == bsc_Get_HALL_DIR_Stat())
	        {
	            break;
	        }
	    }
		if (u8_tmp == 0){	// ������������ȶ��������¼��ػ�������ͼ�����
				HallPosData.bl_HallDir = bsc_Get_HALL_DIR_Stat();
				HP_Hall_TCntReload();
			
		}
		else{
			//unstable hall 	// ���������ȶ�����ʱ��������
		}
		
		if (g_bl_NewHPWFlg){	// ����Ƿ����µĻ��������ȱ�־
			HallPosData.u16_HallPW = bsc_Get_HALL_SPD_Counter();
			CPU_ENTER_CRITICAL();
			g_bl_NewHPWFlg = FALSE;	//clear hall pulse capture global flag
			CPU_EXIT_CRITICAL();

		//if (((HallPosData.bl_HallDir) && (HallPosConfig.bl_hall_dir_cfg == DIR_UP)) ||
		//       ((!HallPosData.bl_HallDir) && (HallPosConfig.bl_hall_dir_cfg != DIR_UP)))
        //if (((HallPosData.bl_HallDir) && (C_HALL_DIR == CHALLDIR)) ||
        //((!HallPosData.bl_HallDir) && (C_HALL_DIR != CHALLDIR)))
		if (((HallPosData.bl_HallDir) && (C_HALL_DIR != CHALLDIR)) ||
			((!HallPosData.bl_HallDir) && (C_HALL_DIR == CHALLDIR)))
			// �����������Ƿ���Ԥ�跽��һ��
		{
			if (HallPosData.u16_WinPosI == 0)	// �������һ�£�������Ӧ����
			{
				++HallPosData.u16_NegativePos;
			}
			else
			{
				HallPosData.u16_NegativePos = 0;
				--HallPosData.u16_WinPosI;
			}

			if (MOT_TstMotorUpFlg())	 // ������Ƿ�������
			{
			 HallPosData.u16_DTC_HallErrCnt = 0;
			}
			else
			{
			 ++HallPosData.u16_HallErrorCnt;
			}

			RT_ui_HALLCNT++;
		}
		else
		{
			if (HallPosData.Flg.Bits.bl_PosSysNormFlg == FALSE)
			{	// �������һ�£�������Ӧ����
			 ++HallPosData.u16_UninitDnPos;
			}
			else
			{
			 ++HallPosData.u16_WinPosI;
			}
			if (MOT_TstMotorUpFlg())	// ������Ƿ�������
			{
			 ++HallPosData.u16_HallErrorCnt;
			}
			else
			{
			 HallPosData.u16_DTC_HallErrCnt = 0;
			}

			RT_ui_HALLCNT++;

		}
		// ���´���λ�ú����¼��ػ���������
		HallPosData.u16_WinPos=HallPosData.u16_WinPosI;
		HP_Hall_TCntReload();
		// ���ü����λ�øı��־
		HallPosData.Flg2.Bits.bl_CalcAP	= TRUE;
		HallPosData.Flg2.Bits.bl_PosChangeFlg = TRUE;

		/*			buf[0] = (uint8_t)((HallPosData.u16_WinPos >>8 )&0xFF) ;
					buf[1] = (uint8_t)HallPosData.u16_WinPos &0xFF ;

					buf[2] = (uint8_t)((HallPosData.u16_HallPW >>8 )&0xFF) ;
					buf[3] = (uint8_t)HallPosData.u16_HallPW &0xFF ;


					buf[4] = Ubat_GetVoltageFiltered();
					buf[5] = Ubat_GetVoltageFiltered();
					buf[6] = Ubat_GetVoltageFiltered();
					buf[7] = Ubat_GetVoltageFiltered();

					SCI0_Send_Packet(buf,8); //test
		*/

 		}
}


static void Position_Process(void)
{	// ����һ������λ����Ϣ�ĺ���
	if(MOT_TstMotorRunFlg() && MOT_TstMotorUpFlg())
	{// ������Ƿ������к�����
		if((HallPosData.u16_WinPos > HallPosConfig.u16_apzone_top) &&
			(HallPosData.u16_WinPos < HallPosConfig.u16_apzone_bottom))
		{	// ������AP����ı�־
			HallPosData.Flg2.Bits.bl_InAPZoneFlg = TRUE;
			if (HallPosData.u16_WinPos > HallPosConfig.u16_apzone20_pos)
			{// ��鴰��λ���Ƿ���20-200��AP������
					HallPosData.Flg2.Bits.bl_InAPZone20_200Flg = TRUE;
					HallPosData.Flg2.Bits.bl_InAPZone4_20Flg = FALSE;
			}
			else{// �����AP����ı�־
					HallPosData.Flg2.Bits.bl_InAPZone20_200Flg = FALSE;
					HallPosData.Flg2.Bits.bl_InAPZone4_20Flg = TRUE;
			}}
		else{// �����AP����ı�־
				HallPosData.Flg2.Bits.bl_InAPZoneFlg = FALSE;
				HallPosData.Flg2.Bits.bl_InAPZone20_200Flg = FALSE;
				HallPosData.Flg2.Bits.bl_InAPZone4_20Flg = FALSE;
		}}
	else{// �����AP����ı�־
			HallPosData.Flg2.Bits.bl_InAPZoneFlg = FALSE;
			HallPosData.Flg2.Bits.bl_InAPZone20_200Flg = FALSE;
			HallPosData.Flg2.Bits.bl_InAPZone4_20Flg = FALSE;			
		}
		if(HallPosData.u16_WinPos < (uint16_t) HallPosConfig.u8_beakpos)
		{// ��鴰��λ���Ƿ���Beak������
			HallPosData.Flg2.Bits.bl_InBeakZoneFlg= TRUE;
		}
		else{
			HallPosData.Flg2.Bits.bl_InBeakZoneFlg= FALSE;
		}
		
		if (((HallPosData.Flg.Bits.bl_PosSysNormFlg == FALSE) && (MOT_TstMotorRunFlg() == FALSE))||(APF_TstAPOffFlg() == TRUE ))
	   {// ���λ��ϵͳ�Ƿ����������ҵ���Ƿ�ֹͣ������AP�Ƿ�ر�
	      HallPosData.u16_NegativePos = 0; 
	      HallPosData.u16_UninitDnPos = 0;      
	   }

		if (MOT_TstMotorRunFlg()==TRUE)
		{}// ������Ƿ�������
		else
		{// ��������ʱ�������ΪԤ����ĳ���C_60S_B5
			HallPosData.u8_RunTimeCnt = C_60S_B5;
		}
	#ifdef HARDWARE_TEST	// �������Ӳ������ģʽ
		if(HallPosData.u16_HallErrorCnt > (uint16_t) HallPosConfig.u8_hallerr_max) 
		{	// ���������������������ֵ��ֹͣ���
				MOT_SetStop(HallPosConfig.u16_pos_priority);
				HP_Normalize_ExitCall();	// �����������˳�����
				if(HallPosData.u16_HallErrorCnt > (uint16_t) HallPosConfig.u8_hallerr_max)
				{	// ����������������Ȼ�������ֵ������DTC�����������
					if (HallPosData.u16_DTC_HallErrCnt < MAX_U16)
						HallPosData.u16_DTC_HallErrCnt++;
				}
				HallPosData.u16_HallErrorCnt = 0;	// ���û����������
		}
		else
		{
				MOT_ClrStop(HallPosConfig.u16_pos_priority);
				// ���û�д���������ֹͣ״̬
		}	
	#else	// ���������Ӳ������ģʽ
		if(
			((HallPosData.Flg.Bits.bl_PosSysNormFlg == FALSE) && (HallPosData.u16_UninitDnPos > HallPosConfig.u16_poserr_max || HallPosData.u16_NegativePos > HallPosConfig.u16_poserr_max) )||
			(HallPosData.u16_WinPos > HallPosConfig.u16_poserr_max) ||
			((HallPosData.Flg.Bits.bl_PosSysNormFlg == TRUE) && (HallPosData.u16_NegativePos > HallPosConfig.u16_poserr_up)) ||
			((HallPosData.Flg.Bits.bl_PosSysNormFlg==FALSE) && (MOT_TstMotorUpFlg() == TRUE) && (HallPosData.u16_NegativePos > HallPosConfig.u16_step_val) && (TM_GetTMStatus() != TRUE))||
			(HallPosData.u16_HallErrorCnt > (uint16_t) HallPosConfig.u8_hallerr_max) ||
		  (HallPosData.u8_RunTimeCnt == 0u))
		{	// ��������κ��쳣��ֹͣ���
				MOT_SetStop(HallPosConfig.u16_pos_priority);
				HP_Normalize_ExitCall();	// �����������˳�����
				if(HallPosData.u16_HallErrorCnt > (uint16_t) HallPosConfig.u8_hallerr_max)
				{	// ���������������������ֵ������DTC�����������
					if (HallPosData.u16_DTC_HallErrCnt < MAX_U16)
						HallPosData.u16_DTC_HallErrCnt++;
				}
				HallPosData.u16_HallErrorCnt = 0;	// ���û����������
		}else
		{	// ���û�д���������ֹͣ״̬
			MOT_ClrStop(HallPosConfig.u16_pos_priority);
		}
	#endif
}

static void SoftStop_Process(void)
{
   bool_t Bl_tmpMotorSSCtrl;
   Bl_tmpMotorSSCtrl= FALSE;					
      
   if (HallPosData.Flg.Bits.bl_PosSysNormFlg == TRUE)  	
   {	// ���λ��ϵͳ�Ƿ�����
      if (MOT_TstMotorRunFlg() && !MOT_TstMotorUpFlg() && HallPosData.Flg.Bits.bl_SSTCntFlg)
			{	// ������Ƿ������У��Ƿ����½����Լ���ֹͣ������־�Ƿ�����
         if ((APF_TstAPRdyFlg() == TRUE )&& (HallPosData.u8_SoftStopCnt == (HallPosConfig.u8_softstopcnt-1)))	
         {	// ���AP�Ƿ�׼���ã�������ֹͣ�����Ƿ�ﵽԤ��ֵ��1
            --HallPosData.u8_SoftStopCnt;
         }
         if (HallPosData.Flg.Bits.bl_SSTPosFlg==TRUE)			
         {	// �����ֹͣλ�ñ�־�Ƿ�����
            if (HallPosData.u16_WinPos>= HallPosData.u16_SoftStopPos)	
            {// ��鴰��λ���Ƿ���ڻ������ֹͣλ��
               if (++HallPosData.u8_SoftStopCnt < HallPosConfig.u8_softstopcnt)	
               {// ������ֹͣ������������Ƿ�С��Ԥ��ֵ
                  MOT_SetStop(HallPosConfig.u16_sst_priority);
                  // ���õ��ֹͣ����������ֹͣ���Ʊ�־
                  Bl_tmpMotorSSCtrl=TRUE;
                  HallPosData.Flg.Bits.bl_InSSTPosFlg=TRUE;	
               }
               else
               {	// �����ֹͣ������־
                  HallPosData.Flg.Bits.bl_SSTCntFlg=FALSE;	
               }
            }
            
         }
      }
      else
      {// ���ݴ���λ�ã����û������ֹͣλ�ñ�־
         if  (HallPosData.u16_WinPos>= HallPosData.u16_SoftStopPos)	
         {
            HallPosData.Flg.Bits.bl_SSTPosFlg=FALSE;
         }
         else
         {
            HallPosData.Flg.Bits.bl_SSTPosFlg=TRUE;
         }
       
         if (HallPosData.Flg2.Bits.bl_BlockDn)		
         {// ����Ƿ������ж�ת
            if (HallPosData.u16_WinPos>(uint16_t) HallPosConfig.u16_softstop_minpos)
            {// ������ֹͣ������־����������ֹͣλ��
               HallPosData.Flg.Bits.bl_SSTCntFlg=TRUE;
               HallPosData.u16_SoftStopPos=HallPosData.u16_WinPos-(uint16_t )HallPosConfig.u8_softstopoffset;		
               HallPosData.u8_SoftStopCnt=0;
							HallPosData.u16_MaxPos = HallPosData.u16_WinPos;
            }
						
         }
      }
   }
   else
   {// ���λ��ϵͳ�������������ֹͣλ�úͼ�����־
      HallPosData.Flg.Bits.bl_SSTPosFlg=FALSE;
      HallPosData.Flg.Bits.bl_SSTCntFlg=FALSE;
   }
   if (Bl_tmpMotorSSCtrl==FALSE)
   {	// ���û����ֹͣ���ƣ�������ֹͣ״̬
      MOT_ClrStop(HallPosConfig.u16_sst_priority);	
   }	
}

static void HallTimeOut_Process(void)
{	// ��������������ĳ�ʱ����͵����ת
   if (MOT_TstMotorRunFlg() && !(HallPosData.Flg2.Bits.bl_BlockUp||HallPosData.Flg2.Bits.bl_BlockDn))    
   {	// ������Ƿ������У�����û���������½���ת
      if (HP_TstHallTimeOutFlg())
      {	// �������������Ƿ�ʱ
         HP_Hall_TCntReload(); 		// ���¼��ػ����������ļ�ʱ��
         if (MOT_TstMotorUpFlg())
         {	// ������Ƿ�������
            HallPosData.u8_BlockUpCnt++;	// ����������ת������
            if (HP_TstPosSysNormFlg())      
            {	// ���λ��ϵͳ�Ƿ�����
               if (!HallPosData.Flg.Bits.bl_BeingBlockPos)    
               {	// ����Ƿ��ڶ�ת
                 if (APF_TstAPOffFlg()) // �жϷ���ap�Ƿ�ر�
                  {
                     HP_Normalize_EnteyCall();	// ��������������
                  }
                  else
                  {
                     if (HallPosData.u16_WinPos < (uint16_t) (HallPosConfig.u8_winpos_tolerance))	
                     {	// ��鴰��λ���Ƿ����ݲΧ��
                        HP_Normalize_EnteyCall();	// ��������������
                     }
                  }
               }
               else
               {}	// ��������λ�ã���������
            }
            else
            {
               HP_Normalize_EnteyCall();	
            }
         }
         else
         {
			
			      HallPosData.u8_BlockDownCnt++;	// �����½���ת������
         }
         Motor_Blocked();	// ���õ������������
         // ���õ��ֹͣ�����ȼ���HallPosConfig.u16_blk_priorityָ��
         MOT_SetStop(HallPosConfig.u16_blk_priority);
	
      }
   }
   else
   {
      HallPosData.Flg2.Bits.bl_BlockUp=FALSE;	// ����������½�������־
      HallPosData.Flg2.Bits.bl_BlockDn=FALSE;
      // ������ֹͣ״̬�����ȼ���HallPosConfig.u16_blk_priorityָ��
      MOT_ClrStop(HallPosConfig.u16_blk_priority);
   }
}

static void Motor_Blocked(void)
{
   if (MOT_TstMotorUpFlg())				
   {		
      HallPosData.Flg2.Bits.bl_BlockUp = TRUE ;
      HallPosData.Flg.Bits.bl_BeingBlockPos = TRUE ;   
   }
   else
   {		
      HallPosData.Flg2.Bits.bl_BlockDn=TRUE;
   }
   //TP_BLOCK_Calc();          
	 thermo_block_calc(0);
}


uint8_t HP_SaveData(void* buf)
{
	uint8_t len;

	len = sizeof(HP_Save_t);
	
	((HP_Save_t* )buf) ->u16_SoftStopPos = HallPosData.u16_SoftStopPos;
	((HP_Save_t* )buf) ->u16_WinPos = HallPosData.u16_WinPos;
	((HP_Save_t* )buf) ->u8_BlockDownCnt = HallPosData.u8_BlockDownCnt;
	((HP_Save_t* )buf) ->u8_BlockUpCnt = HallPosData.u8_BlockUpCnt;
	((HP_Save_t* )buf) ->u8_SoftStopCnt = HallPosData.u8_SoftStopCnt;
	((HP_Save_t* )buf) ->Flg.Ubyte = HallPosData.Flg.Ubyte;
	
	return len;

}

void HP_RestoreData(void* const buf)
{
	 HallPosData.u16_SoftStopPos= ((HP_Save_t* )buf) ->u16_SoftStopPos ;
	 HallPosData.u16_WinPos = ((HP_Save_t* )buf) ->u16_WinPos ;
	 HallPosData.u8_BlockDownCnt = ((HP_Save_t* )buf) ->u8_BlockDownCnt;
	 HallPosData.u8_BlockUpCnt = ((HP_Save_t* )buf) ->u8_BlockUpCnt;
	 HallPosData.u8_SoftStopCnt = ((HP_Save_t* )buf) ->u8_SoftStopCnt;
	 HallPosData.Flg.Ubyte = ((HP_Save_t* )buf) ->Flg.Ubyte;
		
	 HallPosData.u16_WinPosI = 	HallPosData.u16_WinPos;
}

