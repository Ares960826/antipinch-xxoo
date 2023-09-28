/**
  ******************************************************************************
  * @file     xl_pit.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the PIT 
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
#ifndef __XL_PIT_H_
#define __XL_PIT_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/

/* LC Bit Fields */
#define PIT_LC_LC_MASK														0xFFFFFFFFu
#define PIT_LC_LC_SHIFT														0
	
/* CV Bit Fields */
#define PIT_CV_CV_MASK														0xFFFFFFFFu
#define PIT_CV_CV_SHIFT														0
	
/* CTR Bit Fields */
#define PIT_CTR_EN_MASK														0x1u
#define PIT_CTR_EN_SHIFT													0
#define PIT_CTR_MODE_MASK													0x2u
#define PIT_CTR_MODE_SHIFT												1
#define PIT_CTR_IM_MASK														0x4u
#define PIT_CTR_IM_SHIFT													2
	
/* EOI Bit Fields */
#define PIT_EOI_EOI_MASK													0x1u
#define PIT_EOI_EOI_SHIFT													0

/* IS Bit Fields */	
#define PIT_IS_IS_MASK														0x1u
#define PIT_IS_IS_SHIFT														0

/* AIS Bit Fields */
#define PIT_AIS_AIS_MASK													0x3u
#define PIT_AIS_AIS_SHIFT													0

/* AEOI Bit Fields */
#define PIT_AEOI_AEOI_MASK												0x3u
#define PIT_AEOI_AEOI_SHIFT												0

/* RAWIS Bit Fields */
#define PIT_RAWIS_RAWIS_MASK											0x3u
#define PIT_RAWIS_RAWIS_SHIFT											0

/* DEBUG Bit Fields */
#define PIT_DEBUG_FRZ_MASK											  0x10u
#define PIT_DEBUG_FRZ_SHIFT											  4

/** PIT - Register Layout Typedef */
typedef struct{
	struct{
		__IO	uint32_t	LC;											  	 /*!< 定时器加载值寄存器, offset: 0x00 */
		__O		uint32_t	CV;												   /*!< 定时器当前值寄存器, offset: 0x04 */
		__IO	uint32_t	CTR;											   /*!< 定时器控制寄存器, offset: 0x08 */
		__O		uint32_t	EOI;											   /*!< 定时器中断清零寄存器, offset: 0x0C */
		__O		uint32_t	IS;												   /*!< PIT Interrupt Status Register, offset: 0x10 */
	}CHANNEL[2];
	uint32_t RESERVED_0[30];
	__O		uint32_t		AIS;												 /*!< 定时器所有中断状态寄存器, offset: 0xa0 */
	__O		uint32_t		AEOI;												 /*!< 定时器清零所有中断寄存器, offset: 0xa4 */
	__O		uint32_t		RAWIS;											 /*!< 定时器原始中断状态寄存器, offset: 0xa8 */
	uint32_t RESERVED_1[9];
	__IO	uint32_t		PIT_DIV[2];
	uint32_t RESERVED_2[10];
	__IO  uint32_t		CHAIN;											 /*!< 定时器调试模式设置寄存器, offset: 0x100 */	
}PIT_Type,*PIT_MemMapPtr;
extern PIT_Type* PIT;	


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup PIT 
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup ACMP_Exported_Constants ACMP模块使用参数定义
  * @{
  */
	
/** @defgroup PIT_Mode_Seclect PIT模式选择定义
  * @{
  */
#define PIT_Run_Mode												((uint8_t)0x00)				/*!< 自由运行模式 */
#define PIT_Count_Mode											((uint8_t)0x02)				/*!< 用户定义的计数模式 */
/**
  * @}
  */	

/** @defgroup PIT_Channels_Seclect PIT通道选择
  * @{
  */
typedef enum
{
		PIT_Channel0     =	0 ,				/*!< PIT通道0 */
		PIT_Channel1								  /*!< PIT通道1 */

}PIT_Channel;
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PIT_DeInit(void);
void PIT_Init(uint8_t Channel,uint8_t PIT_Mode,uint16_t CLK_DIV);

/* PIT channel function-----------------------------------*/
void PIT_EnableCmd(uint8_t Channel,FunctionalState NewState);
void PIT_InterruptEn(uint8_t Channel,FunctionalState NewState);

void PIT_SetLoadCount(uint8_t Channel,uint32_t loadVal);
uint32_t PIT_GetCurrentVal(uint8_t Channel);

ITStatus PIT_GetIntStatus(uint8_t Channel);
void PIT_ClrInterrupt(uint8_t Channel);

/* PIT function-----------------------------------*/
uint8_t PIT_GetAllIntStatus(void);
void PIT_ClrAllInterrupt(void);
uint8_t PIT_GetRawIntStatus(void);
void PIT_ChainCmd(FunctionalState NewState);
void PIT_FreezeCmd(FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif		/*__XL_PIT_H__ */

/**
  * @}
  */

/**
  * @}
  */


