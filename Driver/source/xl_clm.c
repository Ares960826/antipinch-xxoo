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
  * @brief  CLM��ʼ��
  * @param  CLMx: ������õ�CLM����
  * @param  CLM_InitStruct: CLM_InitTypeDef���͵�ָ�룬������CLM�����������Ϣ��
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
 * @brief  CLMʹ��
 * @param  CLMx: ������õ�CLM���衣
 * @retval None
 */
void CLM_EnableCmd(CLM_Type* CLMx)
{
	CLMx->CTRL |= (uint16_t)(0x01u & CLM_CTRL_CLMEN_MASK);
	CLMx->CTRL |= (uint16_t)(0xA5u & CLM_CTRL_CLMEN_MASK);
	CLMx->CTRL |= (uint16_t)(0x01u & CLM_CTRL_CLMEN_MASK);
}

/**
 * @brief  CLM����Ƶ��ƫ������
 * @param  CLMx: ������õ�CLM���衣
 * @param  value: ����Ƶ��ƫ������
 * @retval None
 */
void CLM_Set_CLML(CLM_Type* CLMx, uint16_t value)
{
	CLMx->CLML  = value;
}

/**
 * @brief  CLM����Ƶ��ƫ������
 * @param  CLMx: ������õ�CLM���衣
 * @param  value: ����Ƶ��ƫ������
 * @retval None
 */
void CLM_Set_CLMH(CLM_Type* CLMx, uint16_t value)
{
	CLMx->CLMH = value;
}

/**
 * @brief  CLM��ȡ��λ��־
 * @param  CLMx: ������õ�CLM���衣
 * @retval ��λ״̬(SET or RESET)
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


