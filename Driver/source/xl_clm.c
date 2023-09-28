/**
  ******************************************************************************
  * @file     xl_clm.c
  * @author   kirk.gong
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about CLM firmware program 
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
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

	
/* Includes ---------------------------------------------------------------*/
#include "xl_clm.h"
	


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup CLM Module 
  * @brief CLM Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CLM_Private_Functions 
  * @{
  */ 

/**
  * @brief  CLM初始化
  * @param  CLMx: 输入可用的CLM外设
  * @param  CLM_InitStruct: CLM_InitTypeDef类型的指针，包含了CLM外设的设置信息。
  * @retval None
  */
uint8_t CLM_Init(CLM_Type* CLMx, const CLM_InitTypeDef *CLM_InitStruct)
{
	if(CLM_InitStruct->CLM_SAMPLE_CLOCK == CLM_SCLK_IRC_CLK)
	{
		CLMx->CTRL |= CLM_CTRL_SCLK_SEL_MASK;
	}
	else
	{
		CLMx->CTRL &= (~CLM_CTRL_SCLK_SEL_MASK);
	}
	
	CLMx->CLML = CLM_InitStruct->CLM_CLML;
	CLMx->CLMH = CLM_InitStruct->CLM_CLMH;

	return 1;
} 


/**
 * @brief  CLM使能
 * @param  CLMx: 输入可用的CLM外设。
 * @retval None
 */
void CLM_EnableCmd(CLM_Type* CLMx)
{
	CLMx->CTRL |= (uint16_t)(0x01u & CLM_CTRL_CLMEN_MASK);
	CLMx->CTRL |= (uint16_t)(0xA5u & CLM_CTRL_CLMEN_MASK);
	CLMx->CTRL |= (uint16_t)(0x01u & CLM_CTRL_CLMEN_MASK);
}

/**
 * @brief  CLM设置频率偏移下限
 * @param  CLMx: 输入可用的CLM外设。
 * @param  value: 输入频率偏移下限
 * @retval None
 */
void CLM_Set_CLML(CLM_Type* CLMx, uint16_t value)
{
	CLMx->CLML  = value;
}

/**
 * @brief  CLM设置频率偏移上限
 * @param  CLMx: 输入可用的CLM外设。
 * @param  value: 输入频率偏移上限
 * @retval None
 */
void CLM_Set_CLMH(CLM_Type* CLMx, uint16_t value)
{
	CLMx->CLMH = value;
}

/**
 * @brief  CLM获取复位标志
 * @param  CLMx: 输入可用的CLM外设。
 * @retval 复位状态(SET or RESET)
 */
uint8_t CLM_GetResetFlag(const CLM_Type* CLMx)
{
	return (uint8_t)CLMx->RSTF & CLM_RSTF_RSTF_MASK;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */


