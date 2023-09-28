/**
  ******************************************************************************
  * @file     xl_rtc.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about RTC firmware program 
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
#include "xl_rtc.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC RTC Module 
  * @brief RTC Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
/** @defgroup RTC_Private_Functions
  * @{
  */ 

/**
  * @brief  RTC默认初始化
  * @param  RTCx: 输入可用的RTC外设
  * @retval None
  */
void RTC_DeInit(RTC_Type *RTCx)
{
	/* Deinitializes to default reset values */
	RTCx->SC = 0x0000;
}

/**
  * @brief 初始化RTC
  * @param  RTCx: 输入可用的RTC外设。
  * @param  RTC_InitStruct:RTC_InitTypeDef类型的指针，包含了RTC外设的设置信息
  * @retval None
  */
void RTC_Init(RTC_Type *RTCx, const RTC_InitTypeDef *RTC_InitStruct)
{
	uint32_t tmpreg;

	/*---------------------------- RTC SC Configuration ------------------------*/
	/* Get the RTC SC value. */
	tmpreg = RTCx->SC ;

	/* Clear bits Value in SC register.*/
	tmpreg &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);

	/* Set the bit RTCLKS,RTCPS in CR Register. */

	tmpreg |= (uint32_t)((((uint32_t)(((uint32_t)(RTC_InitStruct->RTC_ClkSrc))<<RTC_SC_RTCLKS_SHIFT))&RTC_SC_RTCLKS_MASK) \
							|(((uint32_t)(((uint32_t)(RTC_InitStruct->RTC_ClkPres))<<RTC_SC_RTCPS_SHIFT))&RTC_SC_RTCPS_MASK));

	/* Write to RTC SC Register. */
	RTCx->SC = tmpreg ;
}

/**
  * @brief RTC使能
  * @param  RTCx: 输入可用的RTC外设。
  * @param  NewState: RTC使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: RTC使能
  *			@arg DISABLE: RTC失能
  * @retval None
  */
void RTC_EnableCmd(RTC_Type *RTCx, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		RTCx->SC |= RTC_SC_RTCEN_MASK;
	}
	else
	{
		RTCx->SC &= (~RTC_SC_RTCEN_MASK);
	}
}

/**
  * @brief RTC中断使能
  * @param  RTCx: 输入可用的RTC外设。
  * @param  NewState: RTC中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: RTC中断使能
  *			@arg DISABLE: RTC中断失能
  * @retval None
  */
void RTC_InterruptEn(RTC_Type *RTCx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Real-time interrupt requests are enabled. */
		RTCx->SC |= RTC_SC_RTIE_MASK;
	}
	else 
	{
		/* Real-time interrupt requests are disabled. */
		RTCx->SC &= ~RTC_SC_RTIE_MASK;
	}
}

/**
  * @brief RTC实时输出使能
  * @param  RTCx: 输入可用的RTC外设
  * @param  NewState: RTC实时输出使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能RTC实时输出
  *			@arg DISABLE: 失能RTC实时输出
  * @retval None
  */
void RTC_CountOutputEn(RTC_Type *RTCx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Real-time counter output enabled. */
		RTCx->SC |= RTC_SC_RTCO_MASK;
	}
	else 
	{
		/* Real-time counter output disabled. */
		RTCx->SC &= ~RTC_SC_RTCO_MASK;
	}
}

/**
  * @brief 获取RTC实时中断标志位
  * @param  RTCx: 输入可用的RTC外设。
  * @retval 实时中断标志位
  */
ITStatus RTC_GetInterruptFlag(const RTC_Type *RTCx)
{
	return ((RTCx->SC  & RTC_SC_RTIF_MASK) == RTC_SC_RTIF_MASK);
}

/**
  * @brief 清空RTC实时中断标志位
  * @param  RTCx: 输入可用的RTC外设。
  * @retval None
  */
void RTC_ClrInterruptFlag(RTC_Type *RTCx)
{
	/* Writing a logic 1 clears the bit and the real-time interrupt request */
	RTCx->SC |= RTC_SC_RTIF_MASK;
}

/**
  * @brief 设置RTC模数寄存器
  * @param  RTCx: 输入可用的RTC外设
  * @param  RTC_ModValue: RTC的模数值
  * @retval None
  */
void RTC_SetModValue(RTC_Type *RTCx,uint16_t RTC_ModValue)
{
	/* modulo Value of RTC. */
	RTCx->MOD = RTC_ModValue;
}

/**
  * @brief 获得RTC计数器的当前值
  * @param  RTCx: 输入可用的RTC外设。
  * @retval None
  */
uint16_t RTC_GetCountValue(const RTC_Type *RTCx)
{
	uint16_t countvalue;

	/* the value of the current RTC count. */
	countvalue= (uint16_t)RTCx->CNT ;

	return countvalue;
}


/**
  * @brief RTC时间戳计数器使能
  * @param  RTCx: 输入可用的RTC外设
  * @param  NewState: RTC时间戳使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能RTC时间戳计数
  *			@arg DISABLE: 失能RTC时间戳计数
  * @retval None
  */
void RTC_TimeStampEnableCmd(RTC_Type *RTCx, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		RTCx->STAMP_CFG |= RTC_STAMP_CFG_CNTEN_MASK;
	}
	else
	{
		RTCx->STAMP_CFG &= ~RTC_STAMP_CFG_CNTEN_MASK;
	}
}

/**
  * @brief 获取RTC时间戳计数
  * @param  RTCx: 输入可用的RTC外设。
  * @retval None
  */
uint64_t RTC_GetStampCountValue(const RTC_Type *RTCx)
{
	uint64_t countvalue;

	/* the value of the current RTC count. */
	countvalue= (uint64_t)RTCx->STAMP_CNT ;

	return countvalue;
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


