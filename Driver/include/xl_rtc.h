/**
  ******************************************************************************
  * @file     xl_rtc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the RTC 
  *           firmware library.
  ******************************************************************************
  * @attention
	*
  * 2019 by Chipways Communications,Inc. All Rights Reserved.
  * This software is supplied under the terms of a license
  * agreement or non-disclosure agreement with Chipways.
  * Passing on and copying of this document,and communication
  * of its contents is not permitted without prior written
  * authorization.
  *
  * <h2><center>&copy; COPYRIGHT 2019 Chipways</center></h2>
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/	  
#ifndef __XL_RTC_H_
#define __XL_RTC_H_

#ifdef __cplusplus
extern "C"{
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
/* Register define ------------------------------------------------------------*/
	
/* SC Bit Fields */
#define RTC_SC_RTCEN_MASK                     0x01u
#define RTC_SC_RTCEN_SHIFT                    0
#define RTC_SC_RTCO_MASK                      0x10u
#define RTC_SC_RTCO_SHIFT                     4
#define RTC_SC_RTIE_MASK                      0x40u
#define RTC_SC_RTIE_SHIFT                     6
#define RTC_SC_RTIF_MASK                      0x80u
#define RTC_SC_RTIF_SHIFT                     7
#define RTC_SC_RTCPS_MASK                     0x700u
#define RTC_SC_RTCPS_SHIFT                    8
#define RTC_SC_RTCLKS_MASK                    0xC000u
#define RTC_SC_RTCLKS_SHIFT                   14
	
/* MOD Bit Fields */
#define RTC_MOD_MOD_MASK                      0xFFFFu
#define RTC_MOD_MOD_SHIFT                     0

/* CNT Bit Fields */
#define RTC_CNT_CNT_MASK                      0xFFFFu
#define RTC_CNT_CNT_SHIFT                     0

/* STAMP CFG Bit Fields */
#define RTC_STAMP_CFG_CNTEN_MASK                      0x01u
#define RTC_STAMP_CFG_CNTEN_SHIFT                     0

/* STAMP CNT Bit Fields */
#define RTC_STAMP_CNT_CNTH_MASK                      0x00000000FFFFFFFFu
#define RTC_STAMP_CNT_CNTH_SHIFT                     0

#define RTC_STAMP_CNT_CNTL_MASK                      0xFFFFFFFF00000000u
#define RTC_STAMP_CNT_CNTL_SHIFT                     31

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /*!< RTC״̬�Ϳ��ƼĴ���, offset: 0x0 */
  __IO uint32_t MOD;                               /*!< RTCģ���Ĵ���, offset: 0x4 */
  __I  uint32_t CNT;                               /*!< RTC�������Ĵ���, offset: 0x8 */
	   uint32_t RESERVED0[0x39];
  __IO uint32_t STAMP_CFG;                         /*!< STAMP���üĴ���, offset: 0xF0 */
	   uint32_t RESERVED1;
  __IO uint64_t STAMP_CNT;                         /*!< STAMP�����Ĵ���, offset: 0xF8 */
} RTC_Type, *RTC_MemMapPtr;							
extern RTC_Type* RTC;	

/** @addtogroup XL6600_StdPeriph_Driver  
  * @{
  */

/** @addtogroup RTC 
  * @{
  */


/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief RTC ��ʼ���ṹ�嶨��
 */
typedef struct 
{	
		uint8_t 	  RTC_ClkSrc;							  	/*!< ʵʱʱ��Դѡ�� */
		uint8_t 		RTC_ClkPres;								/*!< ʵʱʱ��Ԥ��Ƶ��ѡ�� */
		
}RTC_InitTypeDef, *RTC_MsgConfigPtr;


/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_Exported_Constants RTCģ��ʹ�ò�������
  * @{
  */

/** @defgroup RTC_Clocks_SourceSelect RTCʱ��Դѡ��
  * @{
  */
#define RTC_External_Clock									((uint8_t)0x0)			    	/*!< OSCCLK��Ϊʱ��Դ */
#define RTC_Realtime_Clock									((uint8_t)0x1)			    	/*!< LPOCLK��Ϊʱ��Դ */
#define RTC_Internal_Clock									((uint8_t)0x2)				    /*!< ICSIRCLK��Ϊʱ��Դ */
#define RTC_Bus_Clock										((uint8_t)0x3)				        /*!< APBCLK��Ϊʱ��Դ */
/**
  * @}
  */


/**
	* @defgroup RTC_Clock_Prescaler_Select RTCʱ�ӷ�Ƶѡ��
  * @{
  */
#define RTC_Clk_Prescaler_off		    				((uint8_t)0x0)				/*!< �ر� */
#define RTC_Clk_Prescaler_1or128						((uint8_t)0x1)				/*!< ���RTCLKS=x0����Ϊ1�����RTCLKS=x1����Ϊ128 */
#define RTC_Clk_Prescaler_2or256						((uint8_t)0x2)				/*!< ���RTCLKS=x0����Ϊ2�����RTCLKS=x1����Ϊ256 */
#define RTC_Clk_Prescaler_4or512						((uint8_t)0x3)				/*!< ���RTCLKS=x0����Ϊ4�����RTCLKS=x1����Ϊ512 */
#define RTC_Clk_Prescaler_8or1024						((uint8_t)0x4)				/*!< ���RTCLKS=x0����Ϊ8�����RTCLKS=x1����Ϊ1024 */
#define RTC_Clk_Prescaler_16or2048					((uint8_t)0x5)				/*!< ���RTCLKS=x0����Ϊ16�����RTCLKS=x1����Ϊ2048 */
#define RTC_Clk_Prescaler_32or100						((uint8_t)0x6)				/*!< ���RTCLKS=x0����Ϊ32�����RTCLKS=x1����Ϊ100 */
#define RTC_Clk_Prescaler_64or1000					((uint8_t)0x7)				/*!< ���RTCLKS=x0����Ϊ64�����RTCLKS=x1����Ϊ1000 */
/**
  * @}
  */


/**
	* @}
	*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void RTC_DeInit(RTC_Type *RTCx);
void RTC_Init(RTC_Type *RTCx, const RTC_InitTypeDef *RTC_InitStruct);
void RTC_InterruptEn(RTC_Type *RTCx,FunctionalState NewState);
void RTC_CountOutputEn(RTC_Type *RTCx,FunctionalState NewState);
ITStatus RTC_GetInterruptFlag(const RTC_Type *RTCx);
void RTC_ClrInterruptFlag(RTC_Type *RTCx);
void RTC_SetModValue(RTC_Type *RTCx,uint16_t RTC_ModValue);
uint16_t RTC_GetCountValue(const RTC_Type *RTCx);
void RTC_EnableCmd(RTC_Type *RTCx, FunctionalState NewState);
void RTC_TimeStampEnableCmd(RTC_Type *RTCx, FunctionalState NewState);
uint64_t RTC_GetStampCountValue(const RTC_Type *RTCx);
#ifdef __cplusplus
}
#endif
#endif     /*__XL_RTC_H__ */

/**
  * @}
  */

/**
  * @}
  */
