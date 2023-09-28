
/*******************************************************************************
|  File Name:    Ubat.c
|  Description:  Motor Battery source file
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
#include "Ubat.h"
//#include "adc1_user.h"
//#include "adc2_user.h"
#include "motor.h"
#include "Hallpos.h"
#include "param.h"
#include "AppIF.h"
#include "complier_sw.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define C_U_BAT_LOW       86u	//9V
#define C_U_BAT_HIGH     164u	//16V
#define C_U_BAT_TOL		  1u	//tolerance
#define C_U_OFFSET        1u

//base 2ms
#define C_U_LOW_TIME     500u  	//1s
#define C_U_HIGH_TIME    250u  	//0.5s

/*******************************************************************************
**                      Private Type Definitions                          **
*******************************************************************************/
//typedef enum{
//		stBATOK = 0u,
//		stBATLOW_TIME,
//		stBATHIGH_TIME,
//		stBATLOW,
//		stBATHIGH,
//		stBATHIGH_WAKE_UP,
//		stBATLOW_ON,
//		stBATHIGH_ON,
//}volt_sts_t;

     
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static void CheckUBat(void);
static void BatFilter(void);

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

//typedef struct{
//	union
//	{
//		uint8_t Ubyte;	//save data
//		struct
//		{
//			uint8_t bl_LowVoltage	: 1;
//			uint8_t bl_HighVoltage	: 1;
//			uint8_t Bit2	: 1;
//			uint8_t Bit3	: 1;
//			uint8_t Bit4	: 1;
//
//			uint8_t Bit5	: 1;
//			uint8_t Bit6	: 1;
//			uint8_t Bit7	: 1;
//		} Bits;
//	}Flg;
//	int16_t u16_temperature;
//	int16_t u16_temperature2;
//	uint8_t u8_VoltageFilter;
//	uint8_t	u8_VoltageADC;
//	uint16_t	u16_VoltageFiltBuf;
//	uint16_t	u16_HighLowVoltage_Timeout;
//	volt_sts_t	VoltageState;
//}BatData_t;

//static
_Init_SAVE_RAM BatData_t BatData;

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
void BAT_Init(void)
{
	BatData.u16_HighLowVoltage_Timeout = 0;
	BatData.u8_VoltageADC = 140u;
	BatData.u8_VoltageFilter = 140u;
	BatData.u16_VoltageFiltBuf = 140u;

//	BatData.Flg.Bits.bl_LowVoltage = FALSE;//CHANGE TO POR
//	BatData.Flg.Bits.bl_HighVoltage = FALSE;//CHANGE TO POR
	BatData.VoltageState = stBATOK;
}

/*******************************************************************************
Name			: Ubat_GetVoltageFiltered()
Syntax			:  uint16_t Ubat_GetVoltageFiltered(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Get Filtered Voltage 
Requirement		: None
Call By			:Application Layer
history
<No.>    <author>    <time>    <description>
1			Cj		20170629	Init
|******************************************************************************/
uint8_t Ubat_GetVoltageFiltered(void)
{
	return (BatData.u8_VoltageFilter);
}

bool_t Ubat_TstHighVoltageFlg(void)
{
	return BatData.Flg.Bits.bl_HighVoltage;
}

bool_t Ubat_TstLowVoltageFlg(void)
{
	return BatData.Flg.Bits.bl_LowVoltage;
}

void Ubat_Task(void)
{
		BatFilter();	// 进行电池电压过滤
		CheckUBat();	// 检查电池电压状态
}

void Ubat_2ms_Job(void)
{
	if (BatData.u16_HighLowVoltage_Timeout>0)
		BatData.u16_HighLowVoltage_Timeout--;
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
static void BatFilter(void)
{
     uint32_t tmp;
     tmp = bsc_AD_Get_Raw_Bat();	// 从ADC获取原始电池电压数据
     if(tmp<911)	// 根据原始电压数据进行转换和范围限制
    	 BatData.u8_VoltageADC = (uint8_t)((tmp*272)/1000)+7 ;
     else
    	 BatData.u8_VoltageADC = 255;
     	 //BatData.u16_temperature = bsc_ADC2_GetChResult_mVC(5u); //bsc_ADC2_GetChResult(5u);
		 //BatData.u16_temperature2 =  bsc_ADC2_GetChResult(5u);
      if (BatData.u8_VoltageFilter==0)// 如果电压过滤值为0，则进行初始化
      {
         BatData.u16_VoltageFiltBuf=BatData.u8_VoltageADC<<4;// 初始化电压过滤缓冲区
         BatData.u8_VoltageFilter=BatData.u8_VoltageADC;// 设置电压过滤值
      }
      // 以下逻辑用于电压平滑处理
      if (BatData.u8_VoltageFilter < BatData.u8_VoltageADC)
      {// 如果过滤电压小于ADC电压 - 根据电压差进行平滑处理
         if (BatData.u8_VoltageADC-BatData.u8_VoltageFilter<10)
         {
            if (BatData.u8_VoltageADC-BatData.u8_VoltageFilter<5)
            {
               if ((BatData.u8_VoltageADC-BatData.u8_VoltageFilter<2))
               {}	// 电压差非常小，不进行处理
               else
               {
                  BatData.u16_VoltageFiltBuf+=1;// 微调电压过滤缓冲区
               }
            }
            else
            {
               BatData.u16_VoltageFiltBuf+=8;// 中等调整电压过滤缓冲区
            }
         }
         else
         {
            BatData.u16_VoltageFiltBuf +=(uint16_t) BatData.u8_VoltageADC;
            // 大幅度调整电压过滤缓冲区
         }
      }
      else	// 如果过滤电压大于或等于ADC电压
      {
         if (BatData.u8_VoltageFilter > BatData.u8_VoltageADC)// 如果过滤电压大于ADC电压
         {	// 根据电压差进行平滑处理
            if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<10)
            {
               if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<5)
               {
                  if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<2)
                  {}	// 电压差非常小，不进行处理
                  else
                  {
                     BatData.u16_VoltageFiltBuf-=1;	// 微调电压过滤缓冲区
                  }
               }
               else
               {
                  BatData.u16_VoltageFiltBuf-=8;	// 中等调整电压过滤缓冲区
               }
            }
            else
            {
               BatData.u16_VoltageFiltBuf -=(uint16_t) BatData.u8_VoltageADC;
               // 大幅度调整电压过滤缓冲区
            }
         }
      }
      BatData.u8_VoltageFilter=(uint8_t) (BatData.u16_VoltageFiltBuf>>4);
      // 更新电压过滤值
}

static void CheckUBat(void)
{
   switch (BatData.VoltageState)// 根据电池电压状态进行不同的处理
   {
      case stBATOK:	// 电池电压正常状态
      {
         if (BatData.u8_VoltageFilter < C_U_BAT_LOW-C_U_BAT_TOL )
        	 // 如果电压低于阈值，则进入低电压超时状态
         {
               BatData.u16_HighLowVoltage_Timeout = C_U_LOW_TIME;						
               BatData.VoltageState = stBATLOW_TIME;
         }
         else
         {	// 如果电压高于阈值，则进入高电压超时状态
            if (BatData.u8_VoltageFilter > C_U_BAT_HIGH+C_U_BAT_TOL)								
            {
               BatData.u16_HighLowVoltage_Timeout = C_U_HIGH_TIME;					
               BatData.VoltageState = stBATHIGH_TIME;
            }
         }
         break;
      }
      case stBATLOW_TIME:	// 低电压超时状态
      {	// 如果电压持续低于阈值
         if (BatData.u8_VoltageFilter < C_U_BAT_LOW-C_U_BAT_TOL )  								
         {
            if (BatData.u16_HighLowVoltage_Timeout == 0 )
            	// 超时后，设置低电压标志并进入低电压状态
            {
							BatData.Flg.Bits.bl_LowVoltage = TRUE;										
              BatData.VoltageState = stBATLOW;
            }
         }
         else	// 如果电压恢复，则回到正常状态
         {
            BatData.VoltageState = stBATOK;										
         }
         break;
      }
      case stBATHIGH_TIME:	// 高电压超时状态
      {
         if (BatData.u8_VoltageFilter > C_U_BAT_HIGH+C_U_BAT_TOL)										
         {	// 如果电压持续高于阈值
            if (BatData.u16_HighLowVoltage_Timeout == 0 )
            {	// 超时后，设置高电压标志并进入高电压状态
               BatData.Flg.Bits.bl_HighVoltage = TRUE;
               BatData.VoltageState = stBATHIGH;
            }
         }
         else	// 如果电压恢复，则回到正常状态
         {
            BatData.VoltageState = stBATOK;										
         }
         break;
      }
      case stBATLOW:		// 电池电压低状态
      case stBATLOW_ON:		// 电池电压低但已经在处理的状态
      {
		MOT_SetStop(BatConfig.u16_bat_prio); // 设置电机停止，优先级由电池配置决定
         if (BatData.u8_VoltageFilter > (C_U_BAT_LOW + C_U_OFFSET)) 					
         {	// 如果电压恢复到一个更高的水平
            if (BatData.VoltageState == stBATLOW_ON)
            {// 如果已经在处理低电压
               if (BatData.u16_HighLowVoltage_Timeout == 0)							
               {// 超时后，清除电机停止，取消低电压标志，回到正常状态
                  MOT_ClrStop(BatConfig.u16_bat_prio);						
                  BatData.Flg.Bits.bl_LowVoltage = FALSE;
                  BatData.VoltageState = stBATOK;	// 进入处理低电压的状态
               }
            }
            else	// 如果还没有开始处理低电压
            {
               BatData.u16_HighLowVoltage_Timeout = C_U_LOW_TIME;						
               BatData.VoltageState = stBATLOW_ON;	// 进入处理低电压的状态
            }
         }
         else	// 如果电压仍然很低
         {
            BatData.VoltageState = stBATLOW;	// 保持在低电压状态
         }
         break;
      }
      case stBATHIGH:  // 电池电压高状态
	  case stBATHIGH_ON:  // 电池电压高但已经在处理的状态
	  {
		  MOT_SetStop(BatConfig.u16_bat_prio);  // 设置电机停止，优先级由电池配置决定
		  // 如果电压降到一个更低的水平
		  if (BatData.u8_VoltageFilter < (C_U_BAT_HIGH - C_U_OFFSET))
		  {
			  // 如果已经在处理高电压
			  if (BatData.VoltageState == stBATHIGH_ON)
			  {
				  // 超时后，清除电机停止，取消高电压标志，回到正常状态
				  if (BatData.u16_HighLowVoltage_Timeout == 0)
				  {
					  MOT_ClrStop(BatConfig.u16_bat_prio);
					  BatData.Flg.Bits.bl_HighVoltage = FALSE;
					  BatData.VoltageState = stBATOK;
				  }
			  }
			  else  // 如果还没有开始处理高电压
			  {
				  BatData.u16_HighLowVoltage_Timeout = C_U_HIGH_TIME;
				  BatData.VoltageState = stBATHIGH_ON;  // 进入处理高电压的状态
			  }
		  }
		  else  // 如果电压仍然很高
		  {
			  BatData.VoltageState = stBATHIGH;  // 保持在高电压状态
		  }
		  break;
	  }
	  case stBATHIGH_WAKE_UP:  // 高电压唤醒状态
	  {
		  // 超时后，根据电压水平决定是否进入高电压状态或回到正常状态
		  if (BatData.u16_HighLowVoltage_Timeout == 0)
		  {
			  if (BatData.u8_VoltageFilter > C_U_BAT_HIGH + C_U_BAT_TOL)
			  {
				  MOT_SetStop(BatConfig.u16_bat_prio);
				  BatData.VoltageState = stBATHIGH;
			  }
			  else
			  {
				  BatData.Flg.Bits.bl_HighVoltage = FALSE;
				  BatData.VoltageState = stBATOK;
				  MOT_ClrStop(BatConfig.u16_bat_prio);
			  }
		  }
		  break;
	  }
	  default:
	  break;  // 其他未定义的电压状态
   }
}

uint8_t BAT_SaveData(uint8_t* buf)
{
	uint8_t len;

	len = sizeof(BAT_Save_t);
	
	((BAT_Save_t* )buf) ->Flg.Ubyte = BatData.Flg.Ubyte;
	return len;
}

void BAT_RestoreData(uint8_t* const buf)
{
	BatData.Flg.Ubyte= ((BAT_Save_t* )buf) ->Flg.Ubyte ;
	
	if (BatData.Flg.Bits.bl_HighVoltage)
	{
		BatData.VoltageState = stBATHIGH_WAKE_UP;
		BatData.u16_HighLowVoltage_Timeout = 3u;
		
	}else if (BatData.Flg.Bits.bl_LowVoltage)
	{
		BatData.VoltageState = stBATLOW;
		BatData.u16_HighLowVoltage_Timeout = 3u;
	}
}


