/**
  ******************************************************************************
  * @file     xl_osc.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about OSC firmware program 
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
#include "xl_osc.h"     

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup OSC OSC Module 
  * @brief OSC Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CR_CLEAR_Mask       ((uint8_t)0x16)	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ICS_Private_Functions
  * @{
 */
 
/**
 * @brief 将OSC外设寄存器恢复默认值
 * @param  OSCx: 指OSC外设
 * @retval None
 */
void OSC_Deinit(void)
{
	/* Deinitializes to default reset values */
	OSC->CR &= (~0xFFu);
}

/**
 * @brief OSC初始化
 * @param  OSCx: 指OSC外设
 * @param  OSC_InitStruct: OSC参数结构体
 * @retval None
 */
void OSC_Init(const OSC_InitTypeDef *OSC_InitStruct)
{
	uint32_t temp;
	
	temp = OSC->CR;
	
	temp &= ~CR_CLEAR_Mask;
	
	temp |= (uint32_t)((uint32_t)OSC_InitStruct->OSC_ModeSelect | (uint32_t)OSC_InitStruct->OSC_OutputSelect | (uint32_t)OSC_InitStruct->OSC_RangeSelect);
	
	OSC->CR = temp;
}
/**
 * @brief  OSC使能命令
 * @param  OSCx: 指OSC外设
 * @param  State: 使能状态
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能OSC
 *			@arg DISABLE ：关闭OSC
 * @retval None
 */
void OSC_EnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/* Enable the OSC */
		OSC->CR |= OSC_CR_OSCEN_MASK;
	}
	else 
	{
		/* Disable the OSC */
		OSC->CR &= ~OSC_CR_OSCEN_MASK;
	}
}

/**
 * @brief OSC在stop模式下使能
 * @param  OSCx: 指OSC外设
 * @param  State: 使能状态
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能OSC
 *			@arg DISABLE ：关闭OSC
 * @retval None
 */
void OSC_ModuleInStopModeCmd(FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		/* Enable the OSC in Stop mode. */
		OSC->CR |= OSC_CR_OSCSTEN_MASK;
	}
	else
	{
		/* Disable the OSC in Stop mode. */
		OSC->CR &= ~OSC_CR_OSCSTEN_MASK;
	}
}

/**
 * @brief OSC外部时钟扩展
 * @param  OSCx: 指OSC外设
 * @param  ExpTime: 扩展的clk(1-32767)
 * @retval None
 */
void OSC_SetExtTime(uint32_t ExpTime)
{	
	/* set the extention time */
	OSC->TCR =  OSC_TCR_CV_MASK | (ExpTime-1u);
}
/**
 * @brief OSC初始化状态
 * @param  OSCx: 指OSC外设
 * @retval 状态结果
 *		这个参数可以取下面的值:
 *			@arg OSC_INITSTATUS_SUCESS ：成功
 *			@arg OSC_INITSTATUS_FAILED ：失败
 */
uint8_t OSC_GetInitStatus(void)
{
	uint8_t sta;
	if((OSC->CR & OSC_CR_OSCINIT_MASK) == OSC_CR_OSCINIT_MASK)
	{
		sta = OSC_INITSTATUS_SUCESS;
	}
	else
	{
		sta = OSC_INITSTATUS_FAILED;
	}
	return sta;
}

/**
 * @brief OSC初始化状态
 * @param  OSCx: 指OSC外设
 * @retval 状态结果
 *		这个参数可以取下面的值:
 *			@arg OSC_RANGE_HIGH ：4-24M
 *			@arg OSC_RANGE_LOW ：32k
 */
uint8_t OSC_GetRange(void)
{
	uint8_t temp;
	if((OSC->CR & OSC_CR_RANGE_MASK) == OSC_CR_RANGE_MASK)
	{
		temp = OSC_RANGE_HIGH;
	}
	else
	{
		temp = OSC_RANGE_LOW;
	}
	return temp;
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
