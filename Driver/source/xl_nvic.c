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
 * @brief  �������ȼ�����:��ռ���ȼ��������ȼ�.
 * @param  NVIC_PriorityGroup: ָ�����ȼ�����λ����.
 *		�����������Ϊ����ֵ:
 *     @arg NVIC_PriorityGroup_0: ��ռ���ȼ�0λ
 *                                �����ȼ�2λ
 *     @arg NVIC_PriorityGroup_1: ��ռ���ȼ�1λ
 *                                �����ȼ�1λ
 *     @arg NVIC_PriorityGroup_2: ��ռ���ȼ�2λ
 *                                �����ȼ�0λ
 * @retval None
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
	/* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
	SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
 * @brief  ������ NVIC_InitStruct��ָ��������ʼ��NVIC����.
 * @param  NVIC_InitStruct: ָ�����ָ��NVIC����������Ϣ��NVIC_InitTypeDef�ṹ.
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
 * @brief  ����ʸ�����λ�ú�ƫ��.
 * @param  NVIC_VectTab: ָ��ʸ�����Ƿ���ROM��������.
 *		�����������Ϊ����ֵ:
 *     @arg NVIC_VectTab_RAM
 *     @arg NVIC_VectTab_FLASH
 * @param  Offset: ʸ�������ƫ���ֶ�,��ֵ������ 0x200�ı���.
 * @retval None
 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
	SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
 * @brief  ѡ��ϵͳ����͹���ģʽ������.
 * @param  LowPowerMode: Ϊϵͳָ������͹���ģʽ���µ�ģʽ.
 *		�����������Ϊ����ֵ:
 *     @arg NVIC_LP_SEVONPEND
 *     @arg NVIC_LP_SLEEPDEEP
 *     @arg NVIC_LP_SLEEPONEXIT
 * @param  NewState: ��ѹ״̬����״̬.
 *		�����������Ϊ����ֵ:
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
 * @brief  ����SysTickʱ��Դ.
 * @param  SysTick_CLKSource: ָ��SysTickʱ��Դ.
 *		�����������Ϊ����ֵ:
 *     @arg SysTick_CLKSource_HCLK_Div8: ѡ��AHBʱ�ӳ���8��Ϊϵͳʱ��Դ.
 *     @arg SysTick_CLKSource_HCLK: ѡ��AHBʱ����Ϊϵͳʱ��Դ.
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


