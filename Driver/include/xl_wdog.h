 /**
  ******************************************************************************
  * @file     xl_uart.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the WDOG 
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
  
#ifndef __XL_WDOG_H_
#define __XL_WDOG_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "xl6600.h"
	
/* Register define ------------------------------------------------------------*/

/* CS1 Bit Fields */
#define WDOG_CS1_EN_MASK                        0x00000001u
#define WDOG_CS1_EN_SHIFT                       0
#define WDOG_CS1_RMOD_MASK                      0x00000002u
#define WDOG_CS1_RMOD_SHIFT                     1
#define WDOG_CS1_RPL_MASK                       0x0000001Cu
#define WDOG_CS1_RPL_SHIFT                      2
	
/* TORR Bit Fields */
#define WDOG_TORR_TOP_MASK                      0x0000001Fu
#define WDOG_TORR_TOP_SHIFT                     0
	
/* CCVR Bit Fields */							
#define WDOG_CCVR_CCV_MASK                      0xFFFFFFFFu
#define WDOG_CCVR_CCV_SHIFT                     0

/* CRR Bit Fields */
#define WDOG_CRR_CR_MASK                   			0x000000FFu
#define WDOG_CRR_CR_SHIFT                				0

/* STAT Bit Fields */
#define WDOG_STAT_INT_MASK                   		0x00000001u
#define WDOG_STAT_INT_SHIFT                     0

/* EOI Bit Fields */
#define WDOG_EOI_IC_MASK                   			0x00000001u
#define WDOG_EOI_IC_SHIFT                       0

/* CS2 Bit Fields */
#define WDOG_CS2_CLK_MASK                       0x00000003u
#define WDOG_CS2_CLK_SHIFT                      0
#define WDOG_CS2_PRES_MASK                      0x00000008u
#define WDOG_CS2_PRES_SHIFT                     3u
#define WDOG_CS2_STOP_MASK                      0x00000010u
#define WDOG_CS2_STOP_SHIFT                     4u
#define WDOG_CS2_WAIT_MASK                      0x00000020u
#define WDOG_CS2_WAIT_SHIFT                     5u
#define WDOG_CS2_DEBUG_MASK                     0x00000040u
#define WDOG_CS2_DEBUG_SHIFT                    6u

/** ICS - Register Layout Typedef */
typedef struct {
  __IO uint32_t CS1;                             /*!< (1-186)14.2.1 WDOG 控制寄存器(CS1), offset: 0x00 */
  __IO uint32_t TORR;                            /*!< (1-187)14.2.2 WDOG 定时溢出范围寄存器(TORR), offset: 0x04 */
  __I  uint32_t CCVR;                            /*!< (1-188)14.2.3 WDOG 计数值寄存器 (CCVR), offset: 0x08 */
  __O  uint32_t CRR;                             /*!< (1-189)14.2.4 WDOG 计数器重启寄存器(CRR), offset: 0x0c *//*
  * 作为防止意外重启的安全功z能，必须写入值0x76*/
  __I  uint32_t STAT;                            /*!< (1-190)14.2.5 WDOG 中断状态寄存器 (STAT), offset: 0x10 */
  __I  uint32_t EOI;                             /*!< (1-191)14.2.6 WDOG 中断清零寄存器(EOI), offset: 0x14 */
	     uint32_t RESERVED_0[58];
  __IO uint32_t CS2;                             /*!< Watchdog时钟和调试模式寄存器, offset: 0x100 */	
} WDOG_Type;
extern WDOG_Type*		WDOG;


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDOG
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief WDOG初始化结构体定义
  */
typedef struct 
{
	uint8_t                WDOG_ClkSource;          /*!< WDOG 时钟源选择 */
	uint8_t                WDOG_PulseLength;        /*!< 复位脉冲长度 */
	uint8_t                WDOG_ResponseMode;       /*!< 应答模式 */
	FunctionalState        WDOG_PRESEn;             /*!< 256预分频器使能 */
	FunctionalState        WDOG_STOPEn;             /*!< Stop模式下使能 */
	FunctionalState        WDOG_WAITEn;             /*!< Wait模式下使能 */
	FunctionalState        WDOG_DEBUGEn;   	        /*!< Debug模式下使能 */                
}WDOG_InitTypeDef, *WDOG_InitConfigPtr;


/* Exported constants --------------------------------------------------------*/
/** @defgroup WDOG_Exported_Constants WDOG模块使用参数定义
  * @{
  */

/** @defgroup WDOG_ClocksSource_Select WDOG时钟源选择
  * @{
  */
#define WDOG_Bus_Clock						   				((uint8_t)0x0)				/*!< APBCLK */
#define WDOG_LPO_Clock					  	 				((uint8_t)0x1)				/*!< LPOCLK
* 低功耗振荡器(LPO)模块：向 RTC 和 WDOG 提供 32kHz 基准时钟的片上低功耗振荡器
* 32kHz输出，LPOCLK可作为RTC或WDOG模块的时钟源*/
#define WDOG_Internal_Clock					 				((uint8_t)0x2)				/*!< ICSIRCLK */
#define WDOG_External_Clock					 				((uint8_t)0x3)				/*!< OSCCLK */
/**
	* @}
	*/

/** @defgroup WDOG_ResetPulse_Seclect WDOG复位时钟脉冲定义
  * @{
  */
#define WDOG_PclkCycles_2	           				((uint8_t)0x0)      /*!< 2时钟源周期 */
#define WDOG_PclkCycles_4		         				((uint8_t)0x1)      /*!< 4时钟源周期 */
#define WDOG_PclkCycles_8		         				((uint8_t)0x2)      /*!< 8时钟源周期 */      
#define WDOG_PclkCycles_16		       				((uint8_t)0x3)      /*!< 16时钟源周期 */
#define WDOG_PclkCycles_32		       				((uint8_t)0x4)      /*!< 32时钟源周期 */
#define WDOG_PclkCycles_64		       				((uint8_t)0x5)      /*!< 64时钟源周期 */
#define WDOG_PclkCycles_128		       				((uint8_t)0x6)      /*!< 128时钟源周期 */
#define WDOG_PclkCycles_256		       				((uint8_t)0x7)      /*!< 256时钟源周期 */
/**
	* @}
	*/
	
/** @defgroup WDOG_Response_Mode WDOG相应模式定义
  * @{
  */	
#define WDOG_ResponseMode_Reset          		((uint8_t)0x0)      /*!< 生成一个系统复位 */
#define WDOG_ResponseMode_Interrupt      		((uint8_t)0x1)      /*!< 首先生成一个中断，如果在第二个定时溢出发生的时间内未清零此中断，则会生成一个系统复位 */
/**
	* @}
	*/ 

/**
  * @}
  */
	

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void WDOG_DeInit(WDOG_Type *WDOGx);
void WDOG_Init(WDOG_Type *WDOGx, const WDOG_InitTypeDef *WDOG_InitStruct);
void WDOG_EnableCmd(WDOG_Type *WDOGx,FunctionalState State);
void WDOG_SetTimeoutPeriod(WDOG_Type *WDOGx,uint8_t TimeoutIndex);
uint32_t WDOG_GetCurrentVal(const WDOG_Type *WDOGx);
void WDOG_CountRestart(WDOG_Type *WDOGx);
FlagStatus WDOG_GetIntStatus(const WDOG_Type *WDOGx);
void WDOG_ClrInt(const WDOG_Type *WDOGx);

#ifdef __cplusplus
}
#endif	
	
#endif 
/**
  * @}
  */ 

/**
  * @}
  */ 
