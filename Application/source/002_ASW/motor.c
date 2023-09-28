
/*******************************************************************************
|  File Name:    motor.c
|  Description:  motor control source file
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
#include "Types.h"
#include "Typedef.h"
//#include "ls_user.h"
#include "AppIF.h"
#include "hallpos.h"
#include "relay.h"
#include "motor.h"
#include "param.h"
#include "Hallpos.h"
#include "appl_const.h"
#include "complier_sw.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/
//typedef struct{
//	uint16_t	u16_CtrlUp;
//	uint16_t	u16_CtrlDown;
//	uint16_t	u16_CtrlStop;
//
//	uint16_t	u16_StopDelay;
//	uint16_t	u16_StopPosition;
//
//	union														//save
//	{
//		uint8_t Ubyte;
//		struct
//		{
//			uint8_t bl_MotPrvUp	: 1;
//			uint8_t bl_MotRun	: 1;
//			uint8_t bl_MotUp	: 1;
//			uint8_t bl_MotOpen	: 1;
//			uint8_t bl_MotClose	: 1;
//			uint8_t bl_MotStop	: 1;
//			uint8_t Bit6	: 1;
//			uint8_t Bit7	: 1;
//		} Bits;
//	}Flg;
//
//}MotorData_t;




/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


static void window_up(void);
void window_stop(void);
static void window_down(void);
static void op_rel(dir_t dir);
#ifdef TEST_RELAY
static bool_t test_rel(dir_t dir);
#endif

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

_Init_SAVE_RAM  MotorData_t MotorData;


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
Name			: MOT_Init
Syntax			: void MOT_Init(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 
Requirement		: None
Call By			: 
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
void MOT_Init(void)
{
//	MotorData.Flg.Bits.bl_MotClose =FALSE;//CHANGE TO POR
//	MotorData.Flg.Bits.bl_MotOpen =FALSE;//CHANGE TO POR
//	MotorData.Flg.Bits.bl_MotPrvUp =FALSE;//CHANGE TO POR
//	MotorData.Flg.Bits.bl_MotRun =FALSE;//CHANGE TO POR
//	MotorData.Flg.Bits.bl_MotStop =TRUE;//CHANGE TO POR
//	MotorData.Flg.Bits.bl_MotUp =FALSE;//CHANGE TO POR
	
	MotorData.u16_CtrlDown = 0;
	MotorData.u16_CtrlStop = 0;
	MotorData.u16_CtrlUp = 0;
	MotorData.u16_StopDelay = 0;
	MotorData.u16_StopPosition = 0;
	

}

uint16_t MOT_GetStopPosition(void)
{
	return MotorData.u16_StopPosition;
}

void MOT_SetUp(uint16_t prio)
{
		MotorData.u16_CtrlUp |=prio;
}
void MOT_ClrUp(uint16_t prio)
{
		MotorData.u16_CtrlUp &= (prio^0xFFFFU);
}
void MOT_SetDn(uint16_t prio)
{
		MotorData.u16_CtrlDown |=prio;
}
void MOT_ClrDn(uint16_t prio)
{
		MotorData.u16_CtrlDown &= (prio^0xFFFFU);
}
void MOT_SetStop(uint16_t prio)
{
		MotorData.u16_CtrlStop |=prio;
}
void MOT_ClrStop(uint16_t prio)
{
		MotorData.u16_CtrlStop &= (prio^0xFFFFU);
}

uint16_t MOT_GetStopCause(void)
{
		return MotorData.u16_CtrlStop;
}
void MOT_SetMotStopDelay2ms(uint16_t delaytime)
{
	if (delaytime < MotorConfig.u16_stop_delay)
	{
		MotorData.u16_StopDelay = delaytime; //base 2ms
	}else{
		MotorData.u16_StopDelay = MotorConfig.u16_stop_delay;
	}
}

bool_t MOT_TstAPMotStopDelay(void)
{
	bool_t ret = FALSE;
	if (MotorConfig.u16_stop_delay > MotorData.u16_StopDelay)
	{
			if ( (MotorConfig.u16_stop_delay - MotorData.u16_StopDelay) >= 2u)
			{
				ret = TRUE;
			}
	}
	return ret;
}

uint16_t MOT_GetMotDelay(void)
{
	return MotorData.u16_StopDelay;
}

bool_t		MOT_TstMotorUpFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotUp);
}
bool_t		MOT_TstMotorRunFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotRun);
}
bool_t		MOT_TstMotorPrvUpFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotPrvUp);
}
bool_t		MOT_TstMotorOpenFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotOpen);
}
bool_t		MOT_TstMotorCloseFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotClose);
}
bool_t		MOT_TstMotorStopFlg(void)
{
		return (MotorData.Flg.Bits.bl_MotStop);
}

void MOT_2ms_Job(void)
{
	if(MotorData.u16_StopDelay > 0)
	{
		MotorData.u16_StopDelay--;
	}
}
void MOT_Task(void)
{
		if(REL_TstRelAStuckFlg() || REL_TstRelBStuckFlg())
			// 检查继电器A或B是否卡住，如果是，则返回并不执行后续代码
			return;
		// 使用有效的优先级位掩码来更新电机控制信号
		 MotorData.u16_CtrlUp 	&=MotorConfig.u16_valid_up_prio;
		 MotorData.u16_CtrlDown &=MotorConfig.u16_valid_down_prio;
		 MotorData.u16_CtrlStop &=MotorConfig.u16_valid_stop_prio;
    
     if (MotorData.u16_CtrlUp> MotorData.u16_CtrlDown)
     {// 判断电机应该向上、向下还是停止
        if (MotorData.u16_CtrlUp>MotorData.u16_CtrlStop)
        {// 如果向上控制信号优先级最高，执行升窗操作
           window_up();		
        }
        else	// 如果停止控制信号优先级最高
        {
           if (MotorData.Flg.Bits.bl_MotRun)
           {// 同时，如果电机正在运行，设置停止延迟
              MotorData.u16_StopDelay=MotorConfig.u16_stop_delay;	
           }
           window_stop();	// 执行停止操作
        }
     }
     else
     {
        if ( MotorData.u16_CtrlDown>MotorData.u16_CtrlStop)
        {// 如果向下控制信号优先级最高，执行降窗操作
           window_down();
        }
        else
        {// 如果停止控制信号优先级最高，并且电机正在运行，设置停止延迟
           if (MotorData.Flg.Bits.bl_MotRun)
           {
              MotorData.u16_StopDelay=MotorConfig.u16_stop_delay;		
           }
           window_stop();	// 执行窗口停止操作
  	      }
      }
}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
static void window_up(void)
{
   if (MotorData.u16_StopDelay == 0)   
   {
	  HP_ClrBlockUpFlg();
      HP_ClrBlockDnFlg();
      HP_ResetBlockDownCnt();
      #ifdef TEST_RELAY
      if (test_rel(DIR_UP) == FALSE)          	
		#else
		if (TRUE)
		#endif
      {
         MotorData.Flg.Bits.bl_MotClose=TRUE;		
         MotorData.Flg.Bits.bl_MotOpen=FALSE;		
         MotorData.Flg.Bits.bl_MotStop=FALSE;		

         op_rel(DIR_UP);          
         
         MotorData.Flg.Bits.bl_MotUp=TRUE;    
         
         if (!MotorData.Flg.Bits.bl_MotRun)  
         {
            HP_Hall_TCntReload();       
            
            HP_ClrInSoftStopPosFlg();
            
            MotorData.Flg.Bits.bl_MotRun=TRUE;       
         }
      }
      else
      {
         MotorData.u16_StopDelay = 25u;
         window_stop();
      }
   }
}

void window_stop(void)
{
	   MotorData.Flg.Bits.bl_MotClose=FALSE;
	   MotorData.Flg.Bits.bl_MotOpen=FALSE;
	   MotorData.Flg.Bits.bl_MotStop=TRUE;

	   
	   Motor_OFF();   
	   
	   HP_Hall_TCntReload();

	   if (MotorData.Flg.Bits.bl_MotRun)      
	   {
	   	  
	      MotorData.Flg.Bits.bl_MotRun=FALSE;    
	      
	      MotorData.u16_StopPosition = HP_GetHallWPos() ;
	      
	      if (MotorData.Flg.Bits.bl_MotUp) 
	      {
	         MotorData.Flg.Bits.bl_MotPrvUp=TRUE;	
	      }
	      else
	      {
	         MotorData.Flg.Bits.bl_MotPrvUp=FALSE;
	      }
	   }

}
static void window_down(void)
{
   if (MotorData.u16_StopDelay==0)   
   {
      HP_ClrBlockUpFlg();
      HP_ClrBlockDnFlg();
      HP_ResetBlockUpCnt();

			#ifdef TEST_RELAY
      if (test_rel(DIR_DOWN)==FALSE)            	
			#else
			if (TRUE)
			#endif	
      {
         
         MotorData.Flg.Bits.bl_MotClose=FALSE;		
         MotorData.Flg.Bits.bl_MotOpen=TRUE;		
         MotorData.Flg.Bits.bl_MotStop=FALSE;		

         
         op_rel(DIR_DOWN);            
         
         MotorData.Flg.Bits.bl_MotUp=FALSE;  	
         
         if (!MotorData.Flg.Bits.bl_MotRun)        
         {
            HP_Hall_TCntReload();       
            HP_ClrInSoftStopPosFlg();
            MotorData.Flg.Bits.bl_MotRun=TRUE;        
         }
      }
      else
      {
         
         MotorData.u16_StopDelay=25u;	
         window_stop();	
      }
   }

}
static void op_rel(dir_t dir)
{
	RT_ClearBUF();
	if (dir == DIR_UP)
	{
		//if(MotorConfig.bl_motor_dir == MOT_CCW){
		if(C_MOTOR_DIR==CMOTOR_DIRECTION){
			Motor_DIRB(); //Motor_DIRA();  //adapt old vr parameter
		}else{
			Motor_DIRA(); //	Motor_DIRB(); 	 //adapt old vr parameter
		}
	
	}else if (dir == DIR_DOWN){
		//if(MotorConfig.bl_motor_dir == MOT_CCW){
		if(C_MOTOR_DIR==CMOTOR_DIRECTION){
			Motor_DIRA(); //Motor_DIRB();	 //adapt old vr parameter
		}else{
			Motor_DIRB(); //	Motor_DIRA();	 //adapt old vr parameter
		}	
	
	}
}


void Motor_DIRA(void)
{
	bsc_LS_RelayPinA(TRUE);
	bsc_LS_RelayPinB(FALSE);
	
			REL_SetRelALogiSts(REL_ON);
			REL_SetRelBLogiSts(REL_OFF);

}

void Motor_DIRB(void)
{
	bsc_LS_RelayPinA(FALSE);
	bsc_LS_RelayPinB(TRUE);
			REL_SetRelALogiSts(REL_OFF);
			REL_SetRelBLogiSts(REL_ON);
}

void Motor_OFF(void)
{
	bsc_LS_RelayPinA(FALSE);
	bsc_LS_RelayPinB(FALSE);
			REL_SetRelALogiSts(REL_OFF);
			REL_SetRelBLogiSts(REL_OFF);	
}

void Motor_BLOCK(void)
{
	bsc_LS_RelayPinA(TRUE);
	bsc_LS_RelayPinB(TRUE);
			REL_SetRelALogiSts(REL_ON);
			REL_SetRelBLogiSts(REL_ON);
}

uint8_t MOT_SaveData(uint8_t* buf)
{
	uint8_t len;

	len = sizeof(MOT_Save_t);
	
	((MOT_Save_t* )buf) ->Flg.Ubyte = MotorData.Flg.Ubyte;

	
	return len;		
	
	
}

void MOT_RestoreData(uint8_t* buf)
{
	 MotorData.Flg.Ubyte = ((MOT_Save_t* )buf) ->Flg.Ubyte;
}



