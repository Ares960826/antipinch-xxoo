/**
  ******************************************************************************
  * @file     xl_ewm.c
  * @author   kirk  ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about EWM firmware program 
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
#include "xl_ewm.h"
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup EWM EWM Module 
  * @brief EWM Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
	
/** @defgroup EWM_Private_Functions
  * @{
  */ 
	
/**
  * @brief  ��ʼ��EWM
  * @param  EWMx:����EWM����
  * @param  EWM_InitStruct:����EWM��ʼ�������ṹ��
  * @retval None
  */
void EWM_Init(EWM_Type* EWMx,const  EWM_InitTypeDef* EWM_InitStruct)
{
	uint8_t temp;
	
	EWMx->CMPH = EWM_InitStruct->EWM_CMPHValue;
	EWMx->CMPL = EWM_InitStruct->EWM_CMPLValue;
	EWMx->CLKDIV = EWM_InitStruct->EWM_Clock_Div;
	
	temp = (uint8_t)EWMx->CTRL;
	
	temp |= (uint8_t)((EWM_InitStruct->EWM_ClockSource << EWM_CTRL_CLK_SEL_SHIFT) | \
					 (EWM_InitStruct->EWM_ResetIntEnable << EWM_CTRL_INTREN_OUT_SHIFT) | \
					 (EWM_InitStruct->EWM_CMPLIntEnable << EWM_CTRL_INTREN_CMPL_SHIFT) | \
					 (EWM_InitStruct->EWM_InputEnable << EWM_CTRL_INEN_SHIFT) | \
					 (EWM_InitStruct->EWM_InputLevel << EWM_CTRL_ASSIN_SHIFT) | \
					 (EWM_InitStruct->EWM_Enable)); 
	EWMx->CTRL = (uint32_t)temp;
}

/**
  * @brief  EWMˢ��Server
  * @param  EWMx:����EWM����
  * @param  nCount��ʱ������
  * @retval �ж�״̬
  */
void EWM_UpdateServ(EWM_Type *EWMx)
{
	EWMx->SERV = 0xB4;
	EWMx->SERV = 0x2C;
}
/**
  * @brief  EWM�õ��ж�״̬
  * @param  EWMx:����EWM����
  * @param  EWM_InterruptStatusType:����EWM�ж�����
  * @retval �ж�״̬
  */
uint8_t EWM_GetInterruptStatus(const EWM_Type *EWMx)
{
	return (uint8_t) EWMx->INTR_STATE;
}

/**
  * @brief  EWM����жϱ�־
  * @param  EWMx:����EWM����
  * @param  EWM_InterruptStatusType:EWM�ж�����
 *	 �����������ȡ�����ֵ:
 *			@arg EWM_CMPL_INT_STATUS: CMPL�ж�״̬
 *			@arg EWM_RESET_INT_STATUS: ��λ�ж�״̬
 *			@arg EWM_LTCMPL_INT_STATUS: ������δ����CMPL�ж�״̬
 *			@arg EWM_GTCMPH_INT_STATUS: �������ﵽCMPH�ж�״̬
 *			@arg EWM_OUT15CLOCK_INT_STATUS: û����15�����������ˢ���ж�״̬
 *			@arg EWM_EXTERNAL_INT_STATUS: �ⲿ�źŷ�����ת�ж�״̬
 *			@arg EWM_CLEAR_ALL_INT: CMPL�ж�״̬
  * @retval None
  */
void EWM_ClearInterruptStatus(EWM_Type *EWMx,uint8_t EWM_InterruptStatusType)
{
	EWMx->INTR_STATE |= (uint32_t)EWM_InterruptStatusType;
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


