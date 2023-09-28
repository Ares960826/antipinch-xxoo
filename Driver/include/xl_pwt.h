/**
  ******************************************************************************
  * @file     xl_pwt.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the PWT
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
#ifndef __XL_PWT_H
#define __XL_PWT_H
 
#ifdef __cplusplus
extern "C"{
#endif

/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	/* Register define ------------------------------------------------------------*/	
/* R1 Bit Fields */
#define PWT_R1_PWTOV_MASK                     0x1u
#define PWT_R1_PWTRDY_MASK                    0x2u
#define PWT_R1_PWTRDY_SHIFT                   1
#define PWT_R1_PWTSR_MASK                     0x8u
#define PWT_R1_PWTSR_SHIFT                    3
#define PWT_R1_POVIE_MASK                     0x10u
#define PWT_R1_POVIE_SHIFT                    4
#define PWT_R1_PRDYIE_MASK                    0x20u
#define PWT_R1_PRDYIE_SHIFT                   5
#define PWT_R1_PWTIE_MASK                     0x40u
#define PWT_R1_PWTIE_SHIFT                    6
#define PWT_R1_PWTEN_MASK                     0x80u
#define PWT_R1_PWTEN_SHIFT                    7
#define PWT_R1_PRE_MASK                       0x700u
#define PWT_R1_PRE_SHIFT                      8
#define PWT_R1_EDGE_MASK                      0x1800u
#define PWT_R1_EDGE_SHIFT                     11
#define PWT_R1_PINSEL_MASK                    0x6000u
#define PWT_R1_PINSEL_SHIFT                   13
#define PWT_R1_PCLKS_MASK                     0x8000u
#define PWT_R1_PCLKS_SHIFT                    15
#define PWT_R1_PPW_MASK                       0xFFFF0000u
#define PWT_R1_PPW_SHIFT                      16

/* R2 Bit Fields */
#define PWT_R2_NPW_MASK                       0xFFFFu
#define PWT_R2_NPW_SHIFT                      0
#define PWT_R2_PWTC_MASK                      0xFFFF0000u
#define PWT_R2_PWTC_SHIFT                     16

/** PWT - Register Layout Typedef */
typedef struct {
  __IO uint32_t R1;                                /**< 脉宽定时器寄存器1, offset: 0x0 */
  __I  uint32_t R2;                                /**< 脉宽定时器寄存器2, offset: 0x4 */
} PWT_Type, *PWT_MemMapPtr;

extern PWT_Type* PWT;
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWT
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief PWT初始化结构体定义
  */
typedef struct 
{
  uint32_t 		PWT_ClkSource;							      /*!< PWT 时钟源选择 */
	uint32_t  	PWT_PulseInputSelect;					    /*!< PWT 脉冲输入选择 */
	uint32_t  	PWT_EdgeSensitivity;			        /*!< PWT 输入边沿灵敏度选择 */
	uint32_t  	PWT_ClkPrescaler;						      /*!< PWT 时钟分频选择 */
}PWT_InitTypeDef;

/* Exported constants --------------------------------------------------------*/  
/** @defgroup PWT_Exported_Constants PWT模块使用参数定义
  * @{
  */
/** @defgroup PWT_ClocksSource_Select PWT时钟源选择
  * @{
  */
#define PWT_BusClock             							((uint16_t)0x0000)					/*!< BUS_CLK总线时钟 */
#define PWT_AltClock							 						((uint16_t)0x8000)					/*!< Alternative clock可选时钟 */
/**
	* @}
	*/

/** @defgroup PWT_PulseInputs_Select PWT输入通道选择
  * @{
  */
#define PWT_Pulse_Inputs0					 						((uint16_t)0x0000)					/*!< PWTIN[0]使能为输入通道 */
#define PWT_Pulse_Inputs1					 						((uint16_t)0x2000)					/*!< PWTIN[1]使能为输入通道 */
#define PWT_Pulse_Inputs2					 						((uint16_t)0x4000)					/*!< PWTIN[2]使能为输入通道 */
#define PWT_Pulse_Inputs3					 						((uint16_t)0x6000)					/*!< PWTIN[3]使能为输入通道 */
/**
	* @}
	*/
	
/** @defgroup PWT_InputEdge_Select PWT捕获边沿
  * @{
  */
#define PWT_FallStart_FallEdge     						((uint16_t)0x0000)						/*!< 在第一个下降沿开始测量脉宽，在所有之后的下降沿上捕捉脉宽 */
#define PWT_RiseStart_FallAndRise	 						((uint16_t)0x0800)					/*!< 在第一个上升沿开始测量脉宽，在所有之后的上升沿和下降沿上捕捉脉宽 */
#define PWT_FallStart_FallAndRise	 						((uint16_t)0x1000)					/*!< 在第一个下降沿开始测量脉宽，在所有之后的上升沿和下降沿上捕捉脉宽 */
#define PWT_RiseStart_RiseEdge		 						((uint16_t)0x1800)					/*!< 在第一个上升沿开始测量脉宽，在所有之后的上升沿上捕捉脉宽 */
/**
	* @}
	*/
	
/** @defgroup PWT_ClockPrescaler_Select PWT时钟分频
  * @{
  */
#define PWT_Clock_Divided1         					((uint16_t)0x0000)					/*!< 时钟1分频 */
#define PWT_Clock_Divided2         					((uint16_t)0x0100)					/*!< 时钟2分频 */
#define PWT_Clock_Divided4				 					((uint16_t)0x0200)					/*!< 时钟4分频 */
#define PWT_Clock_Divided8				 					((uint16_t)0x0300)					/*!< 时钟8分频 */
#define PWT_Clock_Divided16				 					((uint16_t)0x0400)					/*!< 时钟16分频 */
#define PWT_Clock_Divided32				 					((uint16_t)0x0500)					/*!< 时钟32分频 */
#define PWT_Clock_Divided64				 					((uint16_t)0x0600)					/*!< 时钟64分频 */
#define PWT_Clock_Divided128			 					((uint16_t)0x0700)					/*!< 时钟128分频 */
/**
	* @}
	*/

/**
	* @}
	*/
	
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void PWT_DeInit(PWT_Type *PWTx);
void PWT_Init(PWT_Type *PWTx,const PWT_InitTypeDef *PWT_InitStruct);
void PWT_EnableCmd(PWT_Type *PWTx,FunctionalState NewState);
void PWT_InterruptEn(PWT_Type *PWTx,FunctionalState NewState);
void PWT_PWTRDYIntCmd(PWT_Type *PWTx,FunctionalState NewState);
void PWT_OverflowIntCmd(PWT_Type *PWTx,FunctionalState NewState);
void PWT_SetSoftReset(PWT_Type *PWTx);
FlagStatus PWT_GetOverflowFlag(const PWT_Type *PWTx);
void PWT_ClrOverflowFlag(PWT_Type *PWTx);
FlagStatus PWT_GetPWTRDY(const PWT_Type *PWTx);
void PWT_ClrPWTRDYFlag(PWT_Type *PWTx);
uint16_t PWT_GetPPW(const PWT_Type *PWTx);
uint16_t PWT_GetNPW(const PWT_Type *PWTx);
uint16_t PWT_GetPWTCounter(const PWT_Type *PWTx);

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


