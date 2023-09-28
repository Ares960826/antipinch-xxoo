/**
  ******************************************************************************
  * @file     xl_osc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the OSC 
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
#ifndef XL_OSC_H_
#define XL_OSC_H_

#ifdef __cplusplus
extern "C" {
#endif
	

/* Includes ------------------------------------------------------------------*/
#include "XL6600.h"

/* Register define ------------------------------------------------------------*/
#define OSC_CR_OSCINIT_MASK                      0x1u
#define OSC_CR_OSCINIT_SHIFT                     0u

#define OSC_CR_HGO_MASK                          0x2u
#define OSC_CR_HGO_SHIFT                         1u

#define OSC_CR_RANGE_MASK                        0x4u
#define OSC_CR_RANGE_SHIFT                       2u

#define OSC_CR_OSCOS_MASK                        0x10u
#define OSC_CR_OSCOS_SHIFT                       4u

#define OSC_CR_OSCSTEN_MASK                      0x20u
#define OSC_CR_OSCSTEN_SHIFT                     5u

#define OSC_CR_OSCEN_MASK                        0x80u
#define OSC_CR_OSCEN_SHIFT                       7u

/* TCR Bit Fields */
#define OSC_TCR_ECLK_MASK                        0x7FFFu
#define OSC_TCR_ECLK_SHIFT                       0u

#define OSC_TCR_CV_MASK                          0x8000u
#define OSC_TCR_CV_SHIFT                         15u

/** OSC - Register Layout Typedef
 * (1-239) 第 17 章 振荡器（OSC）
 * (1-61) 3.6 时钟模块 - 3.6.2 OSC 配置
 * (1-241) 17.5 存储器映像和寄存器定义
 * 		-> (1-242)17.5.1 OSC 控制寄存器 (CR)
 * 		-> (1-243)17.5.2 OSC 扩展时间设置寄存器 (TCR)*/
typedef struct {
	__IO uint32_t CR;                          /*!< OSC 控制寄存器, offset: 0x0 (1-242)17.5.1 OSC 控制寄存器 (CR)*/
	__IO uint32_t TCR;                         /*!< OSC 扩展时间控制寄存器, offset: 0x4 (1-243)17.5.2 OSC 扩展时间设置寄存器 (TCR)*/
} OSC_Type;

extern  OSC_Type*	OSC;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup OSC 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief OSC初始化结构体定义
  */ 
typedef struct 
{
		uint8_t   OSC_OutputSelect;                /*!< OSC 输出选择 */
		uint8_t   OSC_RangeSelect;                 /*!< 频率范围选择 */
		uint8_t   OSC_ModeSelect;                  /*!< 高增益振荡器选择 */
	
}OSC_InitTypeDef;

/** @defgroup OSC_Exported_Constants OSC模块使用参数定义
  * @{
  */

/** @defgroup OSC_OutSelect OSC输出选择
  * @{
  */
#define OSC_EXTERNAL_COLOCK          						((uint8_t)0x00)   /*!< 选择外部时钟源        */
#define OSC_OSCCILLATOR_COLOR          					((uint8_t)0x10)   /*!< 选择OSC时钟源 */
/**
  * @}
  */

/** @defgroup OSC_RangeSelect OSC频率范围选择
  * @{
  */
#define OSC_RANGE_LOW           								((uint8_t)0x00)   /*!< 32kHz */
#define OSC_RANGE_HIGH         									((uint8_t)0x04)   /*!< 4 to 24MHz */
/**
  * @}
  */
/** @defgroup OSC_WorkMode OSC工作模式
  * @{
  */
#define OSC_LP_MODE          										((uint8_t)0x00)   /*!< 低功耗模式 */
#define OSC_HG_MODE        											((uint8_t)0x02)   /*!< 高增益模式 */
/**
  * @}
  */	

/** @defgroup OSC_InitResult OSC初始化结果
  * @{
  */
#define OSC_INITSTATUS_FAILED        						((uint8_t)0x00)       /*!< OSC 初始化失败      */
#define OSC_INITSTATUS_SUCESS        						((uint8_t)0x01)       /*!< OSC 初始化成功      */

/**
* @}
*/

/**
* @}
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void OSC_Deinit(void);
void OSC_Init(const OSC_InitTypeDef *OSC_InitStruct);
void OSC_EnableCmd(FunctionalState State);
void OSC_ModuleInStopModeCmd(FunctionalState NewState);
void OSC_SetExtTime(uint32_t ExpTime);
uint8_t OSC_GetInitStatus(void);
uint8_t OSC_GetRange(void);

#ifdef __cplusplus
}
#endif		
	
#endif   /*__XL_OSC_H__ */
/**
* @}
*/

/**
* @}
*/

