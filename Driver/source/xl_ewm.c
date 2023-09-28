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
  * @brief  初始化EWM
  * @param  EWMx:设置EWM外设
  * @param  EWM_InitStruct:设置EWM初始化参数结构体
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
  * @brief  EWM刷新Server
  * @param  EWMx:设置EWM外设
  * @param  nCount，时间周期
  * @retval 中断状态
  */
void EWM_UpdateServ(EWM_Type *EWMx)
{
	EWMx->SERV = 0xB4;
	EWMx->SERV = 0x2C;
}
/**
  * @brief  EWM得到中断状态
  * @param  EWMx:设置EWM外设
  * @param  EWM_InterruptStatusType:设置EWM中断类型
  * @retval 中断状态
  */
uint8_t EWM_GetInterruptStatus(const EWM_Type *EWMx)
{
	return (uint8_t) EWMx->INTR_STATE;
}

/**
  * @brief  EWM清除中断标志
  * @param  EWMx:设置EWM外设
  * @param  EWM_InterruptStatusType:EWM中断类型
 *	 这个参数可以取下面的值:
 *			@arg EWM_CMPL_INT_STATUS: CMPL中断状态
 *			@arg EWM_RESET_INT_STATUS: 复位中断状态
 *			@arg EWM_LTCMPL_INT_STATUS: 计数器未到达CMPL中断状态
 *			@arg EWM_GTCMPH_INT_STATUS: 计数器达到CMPH中断状态
 *			@arg EWM_OUT15CLOCK_INT_STATUS: 没有在15个周期内完成刷新中断状态
 *			@arg EWM_EXTERNAL_INT_STATUS: 外部信号发生翻转中断状态
 *			@arg EWM_CLEAR_ALL_INT: CMPL中断状态
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


