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
  * @brief  RTCĬ�ϳ�ʼ��
  * @param  RTCx: ������õ�RTC����
  * @retval None
  */
void RTC_DeInit(RTC_Type *RTCx)
{
	/* Deinitializes to default reset values */
	RTCx->SC = 0x0000;
}

/**
  * @brief ��ʼ��RTC
  * @param  RTCx: ������õ�RTC���衣
  * @param  RTC_InitStruct:RTC_InitTypeDef���͵�ָ�룬������RTC�����������Ϣ
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
  * @brief RTCʹ��
  * @param  RTCx: ������õ�RTC���衣
  * @param  NewState: RTCʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: RTCʹ��
  *			@arg DISABLE: RTCʧ��
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
  * @brief RTC�ж�ʹ��
  * @param  RTCx: ������õ�RTC���衣
  * @param  NewState: RTC�ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: RTC�ж�ʹ��
  *			@arg DISABLE: RTC�ж�ʧ��
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
  * @brief RTCʵʱ���ʹ��
  * @param  RTCx: ������õ�RTC����
  * @param  NewState: RTCʵʱ���ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��RTCʵʱ���
  *			@arg DISABLE: ʧ��RTCʵʱ���
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
  * @brief ��ȡRTCʵʱ�жϱ�־λ
  * @param  RTCx: ������õ�RTC���衣
  * @retval ʵʱ�жϱ�־λ
  */
ITStatus RTC_GetInterruptFlag(const RTC_Type *RTCx)
{
	return ((RTCx->SC  & RTC_SC_RTIF_MASK) == RTC_SC_RTIF_MASK);
}

/**
  * @brief ���RTCʵʱ�жϱ�־λ
  * @param  RTCx: ������õ�RTC���衣
  * @retval None
  */
void RTC_ClrInterruptFlag(RTC_Type *RTCx)
{
	/* Writing a logic 1 clears the bit and the real-time interrupt request */
	RTCx->SC |= RTC_SC_RTIF_MASK;
}

/**
  * @brief ����RTCģ���Ĵ���
  * @param  RTCx: ������õ�RTC����
  * @param  RTC_ModValue: RTC��ģ��ֵ
  * @retval None
  */
void RTC_SetModValue(RTC_Type *RTCx,uint16_t RTC_ModValue)
{
	/* modulo Value of RTC. */
	RTCx->MOD = RTC_ModValue;
}

/**
  * @brief ���RTC�������ĵ�ǰֵ
  * @param  RTCx: ������õ�RTC���衣
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
  * @brief RTCʱ���������ʹ��
  * @param  RTCx: ������õ�RTC����
  * @param  NewState: RTCʱ���ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��RTCʱ�������
  *			@arg DISABLE: ʧ��RTCʱ�������
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
  * @brief ��ȡRTCʱ�������
  * @param  RTCx: ������õ�RTC���衣
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


