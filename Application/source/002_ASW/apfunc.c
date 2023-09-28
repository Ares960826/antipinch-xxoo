
/*******************************************************************************
|  File Name:    apfunc.c
|  Description: Antipinch Action source file
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
#include "complier_sw.h"
#include "Typedef.h"
#include "apfunc.h"
#include "hallpos.h"
#include "motor.h"
#include "sysfunc.h"
#include "keyport.h"
#include "switch.h"
#include "ubat.h"
#include "param.h"
#include "APLIB.h"
#include "appl_const.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define REV_MODE1
#define BLOCK_ANTIPINCH

/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/
typedef struct{
	bool_t	bl_ApConditionReady;
	bool_t	bl_InApRevSts;
	
	uint16_t	u16_ApStopPos;
	uint16_t	u16_ApRevPos;
	
	bool_t	bl_ApOff;
	
	uint16_t u16_ApOff_Time;
	uint8_t		u8_ApOff_Sts;
	uint16_t	u16_WinStartPos;
	uint8_t	u8_SendDataFlg;

	uint8_t		u8_APCnt;
	uint8_t  	u8_SendWinDownCnt;
}ApfData_t;



/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static void APF_DisableAP(void);
static void APF_MotorStop(void);
static void APF_Reverse(void);
#ifdef AP_SIM_DEBUG
static void APF_SData_Init(void);
#endif

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

static ApfData_t ApfData;

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#ifdef AP_SIM_DEBUG
void APF_SendData(void);
#endif

/*******************************************************************************

Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APF_Init(void)
{
	ApfData.bl_InApRevSts = FALSE;
	ApfData.bl_ApConditionReady =FALSE;
	ApfData.bl_ApOff = FALSE;
	ApfData.u8_ApOff_Sts = 0u;
	ApfData.u8_APCnt = 0u;
	ApfData.u8_SendDataFlg = 0u;
	ApfData.u8_SendWinDownCnt = 0;
	#ifdef AP_SIM_DEBUG
		APF_SData_Init();
	#endif
	
	
}
/*******************************************************************************
Name			: APF_Judge
Syntax			:void APF_Judge(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: judge ap condition
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/


void APF_Judge(void)
{
		bool_t tmpRun;
		uint8_t	tmpVoltage;
		bool_t	tmpDir;
		bool_t	tmpDirPrv;
		bool_t	tmpSealArea;
		bool_t	tmpProtectArea;
		uint16_t	tmpPos;
		uint16_t	tmpHpw;
		bool_t	tmpAPFlag = FALSE;
		
	
		APF_DisableAP();
		// 获取电机、电压、方向等状态信息
		tmpRun = MOT_TstMotorRunFlg();
		tmpVoltage = Ubat_GetVoltageFiltered();
		tmpDir = MOT_TstMotorCloseFlg();
		tmpDirPrv = MOT_TstMotorPrvUpFlg();
		tmpSealArea = HP_TstInBeakZoneFlg();
		tmpProtectArea = HP_TstInAPZoneFlg();
		// 更新电机和位置状态（这些函数没有实现，可能是用于调试或其他目的）
		APL_MotSts(tmpVoltage, tmpRun,  tmpDir , tmpDirPrv);//none
		APL_PosSts(tmpSealArea,  tmpProtectArea );//none
		#ifdef AP_SIM_DEBUG
			APF_SendData();	// 如果定义了AP_SIM_DEBUG，发送调试数据
		#endif
		if (HP_TstCalcAPFlg() == TRUE)
		{	// 如果需要计算防夹功能
				if (MOT_TstMotorCloseFlg() == TRUE && HP_TstPosSysNormFlg() == TRUE)
				{	// 如果电机正在关闭并且位置系统正常
					//RT_HallDataLoad();
					// 获取霍尔窗口位置和脉宽
					tmpPos = HP_GetHallWPos();
					tmpHpw = HP_GetHallPulseWidth();
					// 计算是否需要防夹
					tmpAPFlag = APL_Calc(tmpPos,tmpHpw);	
				}
				HP_ClrCalcAPFlg();	// 清除计算防夹标志
				
				#ifdef AP_SIM_DEBUG
				if ((MOT_TstMotorCloseFlg()))
				{
							APF_LoadSData();
							
					ApfData.u8_SendWinDownCnt=1u;
				}else if ( ((MOT_TstMotorCloseFlg() == FALSE) && ApfData.u8_SendWinDownCnt<40u && ApfData.bl_ApConditionReady))
				{
					ApfData.u8_SendWinDownCnt++;
					APF_LoadSData();
				}
				
				#endif
				
		}
		
		if(HP_TstBlockUpFlg()|| tmpAPFlag)
		{	// 如果检测到向上堵转或需要防夹
			APL_InitData();		// 初始化数据
			#ifdef BLOCK_ANTIPINCH // 如果定义了BLOCK_ANTIPINCH，停止电机
				APF_MotorStop();	// 如果定义了BLOCK_ANTIPINCH，停止电机
			#endif			
		}else{
			if (MOT_TstMotorStopFlg())
			{// 如果电机已停止，初始化数据
					APL_InitData();
				
			}
		}
		APF_Reverse();
}

/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
bool_t APF_TstAPOffFlg(void)
{
	return ApfData.bl_ApOff ;
}
/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
bool_t APF_TstAPRdyFlg(void)
{
	return ApfData.bl_ApConditionReady ;
}
/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APF_2ms_Job(void)
{
	if (ApfData.u16_ApOff_Time > 0)
		ApfData.u16_ApOff_Time--;
}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
Name			: APF_MotorStop
Syntax			:void APF_MotorStop(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Stop Motor
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APF_MotorStop(void)
{
   if ((HP_TstInAPZoneFlg()==TRUE) && (ApfData.bl_ApOff == FALSE))       
   {
      if (ApfData.bl_ApConditionReady==FALSE)    							
      {
 			if ( 1 ) //(KEY_TstManualFlg() == FALSE)) //manual key disable ap
            {
               
				ApfData.bl_ApConditionReady = TRUE;
				ApfData.u8_SendDataFlg |= 0x0080;
				ApfData.u16_ApStopPos=HP_GetHallWPos();
				ApfData.u16_WinStartPos = MOT_GetStopPosition();
				MOT_SetStop(ApfConfig.u16_apstop_prio);
				//APL_InitData();
            }
      }
   }

}

/*******************************************************************************
Name			: APF_Reverse
Syntax			:void APF_Reverse(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Reverse 
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void APF_Reverse(void)
{
	uint16_t	tmppos;
	
	if (ApfData.bl_ApConditionReady)		
	{
		tmppos = HP_GetHallWPos();
		if (ApfData.bl_InApRevSts == FALSE)    								
		{
			if (MOT_TstMotorStopFlg() == TRUE && MOT_TstAPMotStopDelay() == TRUE)						
			{
					MOT_SetMotStopDelay2ms(0u);
					#ifdef REV_MODE1
						ApfData.u16_ApRevPos = tmppos + ApfConfig.u16_aprev_distance1;
					#endif
					#ifdef REV_MODE2
						ApfData.u16_ApRevPos = HP_GetSoftStopPos(); //
					#endif
					#ifdef REV_MODE3
						//ApfData.u16_ApRevPos = ApfData.u16_WinStartPos + 50;
						ApfData.u16_ApRevPos = ApfData.u16_WinStartPos; 	//return to initial position 
					#endif
					

					ApfData.bl_InApRevSts=TRUE;   

					MOT_ClrStop(ApfConfig.u16_apstop_prio);
					MOT_SetDn(ApfConfig.u16_apreverse_prio);			
			}
			else
			{
					MOT_SetStop(ApfConfig.u16_apstop_prio);				
			}
		}
		else
		{    
			if(((tmppos > ApfData.u16_ApRevPos) ||(HP_TstBlockDnFlg()==TRUE)||(HP_TstInSoftStopPosFlg()==TRUE)))
			{
					MOT_SetStop(ApfConfig.u16_apstop_prio);
					MOT_ClrDn(ApfConfig.u16_apreverse_prio);
				
						ApfData.bl_ApConditionReady  = FALSE;
						ApfData.bl_InApRevSts = FALSE;

						ApfData.u8_SendDataFlg = 0u;
						ApfData.u8_SendWinDownCnt = 0;	
				

						//#ifdef AP_OFF_AP_10SECONDS  //adapt VR project
							if (CDisable_AP_10S == C_DIS_AP_10S){
									ApfData.u16_ApOff_Time = 5000u;  //2ms base,  10 seconds
									ApfData.u8_ApOff_Sts++;
							}
							

						//#endif			    

			}
			else
			{
						if (MOT_TstMotorOpenFlg() == FALSE)
						{
							 ApfData.bl_ApConditionReady  = FALSE;
							 ApfData.bl_InApRevSts = FALSE;
						}
			}
		}
				SYS_SetWakeSrc (C_ALIVE_ANTIPINCH);
		}
		else
		{		
				ApfData.bl_InApRevSts = FALSE;
				MOT_ClrDn(ApfConfig.u16_apreverse_prio);
				MOT_ClrStop(ApfConfig.u16_apstop_prio);
				SYS_ClrWakeSrc(C_ALIVE_ANTIPINCH);
		}		
}

/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
static void APF_DisableAP(void)
{
	if (ApfData.u16_ApOff_Time > 0)
	{
			if (ApfData.u8_ApOff_Sts >= 2u)
			{
				ApfData.bl_ApOff = TRUE;
				
				if (HP_TstBlockUpFlg())
				{
						ApfData.bl_ApOff = FALSE;
						ApfData.u8_ApOff_Sts = 0u;
				}
				
			}
			
	}else{
			ApfData.bl_ApOff = FALSE;
			ApfData.u8_ApOff_Sts = 0u;
	}	
}

bool_t APF_TstInRev(void)
{
	return ApfData.bl_InApRevSts;
}
/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/

uint8_t APF_SaveData(uint8_t* buf)
{
	uint8_t len;

	len = sizeof(APF_Save_t);
	
	((APF_Save_t* )buf)->u8_APCnt  = ApfData.u8_APCnt;
	
	return len;
}

/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/

void APF_RestoreData(uint8_t* const buf)
{
	
	ApfData.u8_APCnt= ((APF_Save_t* )buf)->u8_APCnt;
	
}



/*******************************************************************************
Name			: APF_Init
Syntax			:void APF_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Init apfunc data
Requirement		: None
Call By			: Application layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/

#ifdef AP_SIM_DEBUG

#define SCI_BUFFER_SIZE  30
#define FIELDMAX	7

uint8_t    SD_uc_SendCnt;							
uint8_t    SD_ar_SendBuf[SCI_BUFFER_SIZE][FIELDMAX+1];	
uint8_t    SD_uc_UpBufIn;						
uint8_t    SD_uc_UpBufOut;						
bool_t 		 SD_bl_Buffer_Full;
bool_t		 SD_bl_Buffer_Empty;
bool_t		 SD_bl_Sending;

void APF_SData_Init(void)
{
	SD_bl_Buffer_Empty = TRUE;
	SD_bl_Buffer_Full  = FALSE;
	SD_uc_UpBufOut  = 0;
	SD_uc_UpBufIn   = 0;
	SD_uc_SendCnt = 0;
	UART1->SCONCLR.bit.TICLR = 1u;
	SD_bl_Sending = FALSE;
}


void  APF_LoadSData(void)
{
	union t_intbyte
	{
			struct
			{
					unsigned char HI_Byte ;
				  unsigned char LO_Byte ;
				  
					
			} byte;
		 uint16_t  word;
	}intbyte;

	 if (1)
   {
        if (!SD_bl_Buffer_Full)
      	{
         intbyte.word=HP_GetHallWPos();							//load position
         SD_ar_SendBuf[SD_uc_UpBufIn][0] = intbyte.byte.LO_Byte;
         SD_ar_SendBuf[SD_uc_UpBufIn][1] = intbyte.byte.HI_Byte;
         intbyte.word=HP_GetHallPulseWidth();								//load hall width
				//if (MOT_TstMotorCloseFlg())	
					//在防夹下降阶段也输出脉宽用于图像显示
				{
         SD_ar_SendBuf[SD_uc_UpBufIn][2] = intbyte.byte.LO_Byte;
         SD_ar_SendBuf[SD_uc_UpBufIn][3] = intbyte.byte.HI_Byte;
        }
				 SD_ar_SendBuf[SD_uc_UpBufIn][4] =  Ubat_GetVoltageFiltered();	//load voltage
         SD_ar_SendBuf[SD_uc_UpBufIn][5] = APL_GetInfo();
				 SD_ar_SendBuf[SD_uc_UpBufIn][6] = APL_GetFlag();
				 SD_ar_SendBuf[SD_uc_UpBufIn][6] |= ApfData.u8_SendDataFlg ;
         SD_ar_SendBuf[SD_uc_UpBufIn][7] = APL_GetInfo2();  			  
         SD_bl_Buffer_Empty = FALSE;    
        

         if (MOT_TstMotorRunFlg() == TRUE)
         {
              SD_ar_SendBuf[SD_uc_UpBufIn][6] |= 0x10;
         }
         else
         {
	          SD_ar_SendBuf[SD_uc_UpBufIn][6] &= 0xEF;
					}
				 
				 
				  SD_uc_UpBufIn++;
         if(SD_uc_UpBufIn>= SCI_BUFFER_SIZE) 
         {
           SD_uc_UpBufIn = 0;
         }
         
         if(SD_uc_UpBufIn == SD_uc_UpBufOut) 
         { //buffer is full  can not load data again
           SD_bl_Buffer_Full = TRUE;
         }
      }
   }
}

void APF_SendData(void)
{

	if(!SD_bl_Buffer_Empty)
	{
		
		if ((UART1->SCON.bit.TI != 0 && SD_bl_Sending == TRUE) || (UART1->SCON.bit.TI == 0 && SD_bl_Sending == FALSE) )
			{
				UART1->SCONCLR.bit.TICLR = 1u;
				UART1->SBUF.reg = SD_ar_SendBuf[SD_uc_UpBufOut][SD_uc_SendCnt];
				SD_bl_Sending = TRUE;
				++SD_uc_SendCnt;    
				if (SD_uc_SendCnt > FIELDMAX)  
				{
					SD_uc_SendCnt = 0;
					SD_uc_UpBufOut++;
					if(SD_uc_UpBufOut>= SCI_BUFFER_SIZE) 
					{
						 SD_uc_UpBufOut = 0;
					}
					if(SD_uc_UpBufOut == SD_uc_UpBufIn){
					SD_bl_Buffer_Empty = TRUE;

					}
					
					SD_bl_Buffer_Full = FALSE;
				}
				//while (UART1->SCON.bit.TI == 0) {};
			}
	}
}
#endif
