
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
		BatFilter();	// ���е�ص�ѹ����
		CheckUBat();	// ����ص�ѹ״̬
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
     tmp = bsc_AD_Get_Raw_Bat();	// ��ADC��ȡԭʼ��ص�ѹ����
     if(tmp<911)	// ����ԭʼ��ѹ���ݽ���ת���ͷ�Χ����
    	 BatData.u8_VoltageADC = (uint8_t)((tmp*272)/1000)+7 ;
     else
    	 BatData.u8_VoltageADC = 255;
     	 //BatData.u16_temperature = bsc_ADC2_GetChResult_mVC(5u); //bsc_ADC2_GetChResult(5u);
		 //BatData.u16_temperature2 =  bsc_ADC2_GetChResult(5u);
      if (BatData.u8_VoltageFilter==0)// �����ѹ����ֵΪ0������г�ʼ��
      {
         BatData.u16_VoltageFiltBuf=BatData.u8_VoltageADC<<4;// ��ʼ����ѹ���˻�����
         BatData.u8_VoltageFilter=BatData.u8_VoltageADC;// ���õ�ѹ����ֵ
      }
      // �����߼����ڵ�ѹƽ������
      if (BatData.u8_VoltageFilter < BatData.u8_VoltageADC)
      {// ������˵�ѹС��ADC��ѹ - ���ݵ�ѹ�����ƽ������
         if (BatData.u8_VoltageADC-BatData.u8_VoltageFilter<10)
         {
            if (BatData.u8_VoltageADC-BatData.u8_VoltageFilter<5)
            {
               if ((BatData.u8_VoltageADC-BatData.u8_VoltageFilter<2))
               {}	// ��ѹ��ǳ�С�������д���
               else
               {
                  BatData.u16_VoltageFiltBuf+=1;// ΢����ѹ���˻�����
               }
            }
            else
            {
               BatData.u16_VoltageFiltBuf+=8;// �еȵ�����ѹ���˻�����
            }
         }
         else
         {
            BatData.u16_VoltageFiltBuf +=(uint16_t) BatData.u8_VoltageADC;
            // ����ȵ�����ѹ���˻�����
         }
      }
      else	// ������˵�ѹ���ڻ����ADC��ѹ
      {
         if (BatData.u8_VoltageFilter > BatData.u8_VoltageADC)// ������˵�ѹ����ADC��ѹ
         {	// ���ݵ�ѹ�����ƽ������
            if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<10)
            {
               if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<5)
               {
                  if (BatData.u8_VoltageFilter-BatData.u8_VoltageADC<2)
                  {}	// ��ѹ��ǳ�С�������д���
                  else
                  {
                     BatData.u16_VoltageFiltBuf-=1;	// ΢����ѹ���˻�����
                  }
               }
               else
               {
                  BatData.u16_VoltageFiltBuf-=8;	// �еȵ�����ѹ���˻�����
               }
            }
            else
            {
               BatData.u16_VoltageFiltBuf -=(uint16_t) BatData.u8_VoltageADC;
               // ����ȵ�����ѹ���˻�����
            }
         }
      }
      BatData.u8_VoltageFilter=(uint8_t) (BatData.u16_VoltageFiltBuf>>4);
      // ���µ�ѹ����ֵ
}

static void CheckUBat(void)
{
   switch (BatData.VoltageState)// ���ݵ�ص�ѹ״̬���в�ͬ�Ĵ���
   {
      case stBATOK:	// ��ص�ѹ����״̬
      {
         if (BatData.u8_VoltageFilter < C_U_BAT_LOW-C_U_BAT_TOL )
        	 // �����ѹ������ֵ�������͵�ѹ��ʱ״̬
         {
               BatData.u16_HighLowVoltage_Timeout = C_U_LOW_TIME;						
               BatData.VoltageState = stBATLOW_TIME;
         }
         else
         {	// �����ѹ������ֵ�������ߵ�ѹ��ʱ״̬
            if (BatData.u8_VoltageFilter > C_U_BAT_HIGH+C_U_BAT_TOL)								
            {
               BatData.u16_HighLowVoltage_Timeout = C_U_HIGH_TIME;					
               BatData.VoltageState = stBATHIGH_TIME;
            }
         }
         break;
      }
      case stBATLOW_TIME:	// �͵�ѹ��ʱ״̬
      {	// �����ѹ����������ֵ
         if (BatData.u8_VoltageFilter < C_U_BAT_LOW-C_U_BAT_TOL )  								
         {
            if (BatData.u16_HighLowVoltage_Timeout == 0 )
            	// ��ʱ�����õ͵�ѹ��־������͵�ѹ״̬
            {
							BatData.Flg.Bits.bl_LowVoltage = TRUE;										
              BatData.VoltageState = stBATLOW;
            }
         }
         else	// �����ѹ�ָ�����ص�����״̬
         {
            BatData.VoltageState = stBATOK;										
         }
         break;
      }
      case stBATHIGH_TIME:	// �ߵ�ѹ��ʱ״̬
      {
         if (BatData.u8_VoltageFilter > C_U_BAT_HIGH+C_U_BAT_TOL)										
         {	// �����ѹ����������ֵ
            if (BatData.u16_HighLowVoltage_Timeout == 0 )
            {	// ��ʱ�����øߵ�ѹ��־������ߵ�ѹ״̬
               BatData.Flg.Bits.bl_HighVoltage = TRUE;
               BatData.VoltageState = stBATHIGH;
            }
         }
         else	// �����ѹ�ָ�����ص�����״̬
         {
            BatData.VoltageState = stBATOK;										
         }
         break;
      }
      case stBATLOW:		// ��ص�ѹ��״̬
      case stBATLOW_ON:		// ��ص�ѹ�͵��Ѿ��ڴ����״̬
      {
		MOT_SetStop(BatConfig.u16_bat_prio); // ���õ��ֹͣ�����ȼ��ɵ�����þ���
         if (BatData.u8_VoltageFilter > (C_U_BAT_LOW + C_U_OFFSET)) 					
         {	// �����ѹ�ָ���һ�����ߵ�ˮƽ
            if (BatData.VoltageState == stBATLOW_ON)
            {// ����Ѿ��ڴ���͵�ѹ
               if (BatData.u16_HighLowVoltage_Timeout == 0)							
               {// ��ʱ��������ֹͣ��ȡ���͵�ѹ��־���ص�����״̬
                  MOT_ClrStop(BatConfig.u16_bat_prio);						
                  BatData.Flg.Bits.bl_LowVoltage = FALSE;
                  BatData.VoltageState = stBATOK;	// ���봦��͵�ѹ��״̬
               }
            }
            else	// �����û�п�ʼ����͵�ѹ
            {
               BatData.u16_HighLowVoltage_Timeout = C_U_LOW_TIME;						
               BatData.VoltageState = stBATLOW_ON;	// ���봦��͵�ѹ��״̬
            }
         }
         else	// �����ѹ��Ȼ�ܵ�
         {
            BatData.VoltageState = stBATLOW;	// �����ڵ͵�ѹ״̬
         }
         break;
      }
      case stBATHIGH:  // ��ص�ѹ��״̬
	  case stBATHIGH_ON:  // ��ص�ѹ�ߵ��Ѿ��ڴ����״̬
	  {
		  MOT_SetStop(BatConfig.u16_bat_prio);  // ���õ��ֹͣ�����ȼ��ɵ�����þ���
		  // �����ѹ����һ�����͵�ˮƽ
		  if (BatData.u8_VoltageFilter < (C_U_BAT_HIGH - C_U_OFFSET))
		  {
			  // ����Ѿ��ڴ���ߵ�ѹ
			  if (BatData.VoltageState == stBATHIGH_ON)
			  {
				  // ��ʱ��������ֹͣ��ȡ���ߵ�ѹ��־���ص�����״̬
				  if (BatData.u16_HighLowVoltage_Timeout == 0)
				  {
					  MOT_ClrStop(BatConfig.u16_bat_prio);
					  BatData.Flg.Bits.bl_HighVoltage = FALSE;
					  BatData.VoltageState = stBATOK;
				  }
			  }
			  else  // �����û�п�ʼ����ߵ�ѹ
			  {
				  BatData.u16_HighLowVoltage_Timeout = C_U_HIGH_TIME;
				  BatData.VoltageState = stBATHIGH_ON;  // ���봦��ߵ�ѹ��״̬
			  }
		  }
		  else  // �����ѹ��Ȼ�ܸ�
		  {
			  BatData.VoltageState = stBATHIGH;  // �����ڸߵ�ѹ״̬
		  }
		  break;
	  }
	  case stBATHIGH_WAKE_UP:  // �ߵ�ѹ����״̬
	  {
		  // ��ʱ�󣬸��ݵ�ѹˮƽ�����Ƿ����ߵ�ѹ״̬��ص�����״̬
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
	  break;  // ����δ����ĵ�ѹ״̬
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


