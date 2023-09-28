/**
  ******************************************************************************
  * @file     xl_uart.c
  * @author   Kirk
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about NVIC firmware progreamme 
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
#include "xl_nvic.h"


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup NVIC NVIC Module 
  * @brief NVIC Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup NVIC_Private_Functions
  * @{
 */ 

 /**
 * @brief  配置优先级分组:先占优先级和子优先级.
 * @param  NVIC_PriorityGroup: 指定优先级分组位长度.
 *		这个参数可以为以下值:
 *     @arg NVIC_PriorityGroup_0: 抢占优先级0位
 *                                子优先级2位
 *     @arg NVIC_PriorityGroup_1: 先占优先级1位
 *                                抢优先级1位
 *     @arg NVIC_PriorityGroup_2: 先占优先级2位
 *                                抢优先级0位
 * @retval None
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
	/* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
	SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
 * @brief  根据在 NVIC_InitStruct中指定参数初始化NVIC外设.
 * @param  NVIC_InitStruct: 指向包含指定NVIC外设配置信息的NVIC_InitTypeDef结构.
 * @retval None
 */
void NVIC_Init(const NVIC_InitTypeDef* NVIC_InitStruct)
{
	uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

	if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
	{
		/* Compute the Corresponding IRQ Priority --------------------------------*/    
		tmppriority = ((uint32_t)0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> (uint8_t)0x08;
		tmppre = ((uint32_t)0x4 - tmppriority);
		tmpsub = tmpsub >> tmppriority;

		tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
		tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
		tmppriority = tmppriority << 0x04;
			
		NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = (uint8_t)tmppriority;

		/* Enable the Selected IRQ Channels --------------------------------------*/
		NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
		(uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
	}
	else
	{
		/* Disable the Selected IRQ Channels -------------------------------------*/
		NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
		(uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
	}
}

/**
 * @brief  设置矢量表的位置和偏移.
 * @param  NVIC_VectTab: 指定矢量表是否在ROM或闪存中.
 *		这个参数可以为以下值:
 *     @arg NVIC_VectTab_RAM
 *     @arg NVIC_VectTab_FLASH
 * @param  Offset: 矢量表基于偏移字段,该值必须是 0x200的倍数.
 * @retval None
 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
	SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
 * @brief  选择系统进入低功率模式的条件.
 * @param  LowPowerMode: 为系统指定进入低功率模式的新的模式.
 *		这个参数可以为以下值:
 *     @arg NVIC_LP_SEVONPEND
 *     @arg NVIC_LP_SLEEPDEEP
 *     @arg NVIC_LP_SLEEPONEXIT
 * @param  NewState: 低压状态的新状态.
 *		这个参数可以为以下值:
 *     @arg ENABLE
 *     @arg DISABLE	
 * @retval None
 */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SCB->SCR |= LowPowerMode;
	}
	else
	{
		SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
	}
}

/**
 * @brief  配置SysTick时钟源.
 * @param  SysTick_CLKSource: 指定SysTick时钟源.
 *		这个参数可以为以下值:
 *     @arg SysTick_CLKSource_HCLK_Div8: 选择AHB时钟除以8作为系统时钟源.
 *     @arg SysTick_CLKSource_HCLK: 选择AHB时钟作为系统时钟源.
 * @retval None
 */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
	if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
	{
		SysTick->CTRL |= (uint32_t)SysTick_CLKSource_HCLK;
	}
	else
	{
		SysTick->CTRL &= (uint32_t)SysTick_CLKSource_HCLK_Div8;
	}
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


