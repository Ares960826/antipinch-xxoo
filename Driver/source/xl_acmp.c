/**
  ******************************************************************************
  * @file     xl_acmp.c
  * @author   kirk  ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about ACMP firmware program 
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
#include "xl_acmp.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup ACMP ACMP Module 
  * @brief ACMP Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup ACMP_Private_Functions 
  * @{
  */ 

/**
  * @brief ��������ACMP�Ĵ���״̬.
  * @param ACMPx: ����ACMP����
  * @retval None
  */
void ACMP_DeInit(ACMP_Type *ACMPx)	
{
	/* set default values to each register.*/
	ACMPx->CS = 0u ;
	ACMPx->C0 = 0u ;
	ACMPx->C1 = 0u ;
	ACMPx->C2 = 0u ;
}

/**
  * @brief ��ʼ��ACMP��ֵ.
	* @param ACMPx: ����ACMP����
  * @param ACMP_InitStruct: ָ��ACMP_InitTypeDef �ṹ����ACMP����������.
  * @retval None
  */
void ACMP_Init(ACMP_Type *ACMPx,const  ACMP_InitTypeDef *ACMP_InitStruct)
{
	uint8_t tmpreg;

	/*configure the register.*/
	
	/* set the C1 register.*/
	tmpreg = ((( ACMP_InitStruct->ACMP_DACRefVoltage << ACMP_C1_DACREF_SHIFT) & ACMP_C1_DACREF_MASK) | \
							(ACMP_InitStruct->ACMP_DACValue & ACMP_C1_DACVAL_MASK));
	
	if(ACMP_InitStruct->ACMP_DACEN == ENABLE)
	{
		tmpreg |= ACMP_C1_DACEN_MASK;
	}
	else
	{
		tmpreg &= ~ACMP_C1_DACEN_MASK;
	}
	
	ACMPx->C1 = tmpreg;

	 /*configure the register.*/
	/* Get the CS Register. */
	tmpreg = ACMPx ->CS ;
	/* clear the HYST and ACMOD bit.*/
	tmpreg &= (uint8_t)(~(ACMP_CS_HYST_MASK | ACMP_CS_ACMOD_MASK));
	/* Set the HYST and ACMOD bit.*/
	tmpreg |=  (( ACMP_InitStruct->ACMP_IntTrigMode & ACMP_CS_ACMOD_MASK) | \
				( ( ACMP_InitStruct->ACMP_HystMode << ACMP_CS_HYST_SHIFT) & ACMP_CS_HYST_MASK) );
	
	
	/* Write to ACMP CS */
	ACMPx->CS = tmpreg ;
	
	/* select the positive input and negative input.*/
	ACMPx->C0 =(((ACMP_InitStruct->ACMP_InputP << ACMP_C0_ACPSEL_SHIFT) & ACMP_C0_ACPSEL_MASK) | \
							(ACMP_InitStruct->ACMP_InputN & ACMP_C0_ACNSEL_MASK));

				
	/* ACMP Input pin enable.*/
	ACMPx->C2 = (ACMP_InitStruct->ACMP_InputPin & ACMP_C2_ACIPE_MASK);
}

/**
  * @brief ����ACMP��ֵ.
	* @param ACMPx: ����ACMP����
  * @param NewState: ʹ�ܺ�ʧ��ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE ��ʹ��
  *			@arg DISENABLE ��ʧ��
  * @retval None
  */
void ACMP_EnableCmd(ACMP_Type *ACMPx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable ACMP. */
		ACMPx->CS |= ACMP_CS_ACE_MASK;
	}
	else 
	{
		/* Disable ACMP. */
		ACMPx->CS &= ~ACMP_CS_ACE_MASK;
	}
}

/**
  * @brief ����ACMP�ж�.
  * @param  ACMPx: ����ACMP����
  * @param  NewState: ʹ�ܺ�ʧ��ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE ��ʹ��
  *			@arg DISENABLE ��ʧ��
  * @retval None
  */
void ACMP_InterruptEn(ACMP_Type *ACMPx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable ACMP Interrupt. */
		ACMPx ->CS |= ACMP_CS_ACIE_MASK;
	}
	else 
	{
		/* Disable ACMP Interrupt. */
		ACMPx ->CS &= ~ACMP_CS_ACIE_MASK;
	}
}

/**
  * @brief ���ö���pin���߼����.
  * @param  ACMPx: ����ACMP����
  * @param  NewState: ʹ�ܺ�ʧ��ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE ��ʹ��
  *			@arg DISENABLE ��ʧ��
  * @retval None
  */
void ACMP_OutputPinEn(ACMP_Type *ACMPx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* can be placed onto external pin. */
		ACMPx->CS |= ACMP_CS_ACOPE_MASK;
	}
	else 
	{
		/* cannot be placed onto external pin. */
		ACMPx->CS &= ~ACMP_CS_ACOPE_MASK;
	}
}

/**
  * @brief �õ��Ƚ��߼����.
  * @param ACMPx: ����ACMP����
  * @retval �����߼�����ߵ͵�ƽ.
  */
uint8_t ACMP_GetOutPutLogic(const ACMP_Type *ACMPx)
{
	/* Return the output logic.*/
	return ((ACMPx->CS & ACMP_CS_ACO_MASK)>>ACMP_CS_ACO_SHIFT);
}

/**
  * @brief �õ�ACMP�жϱ�־λ��ֵ.
  * @param ACMPx: ����ACMP����.
  * @retval ACMP�жϱ�־ 0/1
  */
uint8_t ACMP_GetIntFlag(const ACMP_Type *ACMPx)
{
	/* Return the output logic.*/
	return ((ACMPx->CS & ACMP_CS_ACF_MASK)>>ACMP_CS_ACF_SHIFT);
}

/**
  * @brief ���ACMP�жϱ�־λ��ֵ.
  * @param ACMPx: ����ACMP����
  * @retval None
  */
void ACMP_ClearIntFlag(ACMP_Type *ACMPx)
{
	/*  Clears the logic  ACMP Interrupt Flag Bit in the ACMP module.*/
  ACMPx->CS &= ~ACMP_CS_ACF_MASK;
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


