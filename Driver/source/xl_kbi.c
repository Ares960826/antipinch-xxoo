/**
  ******************************************************************************
  * @file     xl_kbi.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about KBI firmware program 
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
#include "xl_kbi.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup KBI KBI Module 
  * @brief KBI Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup KBI_Private_Functions
  * @{
  */ 

/**
  * @brief KBIĬ�ϳ�ʼ��
  * @param KBIx: ѡ��KBI����.
  * @retval None.
  */
void KBI_Deinit(KBI_Type *KBIx)
{
	/* De-initialize the KBI module return to the default state. */
	KBIx->PE = 0u ;
	KBIx->ES = 0u;
	KBIx->SC = 0u ;
}

/**
  * @brief KBI��ʼ��
  * @param KBIx: ѡ��KBI����.
  * @param KBI_InitStruct: ָ�����ָ��KBI����������Ϣ��KBI_InitTypeDef�ṹ.
  * @retval None.
  */
void KBI_Init(KBI_Type *KBIx, const KBI_InitTypeDef *KBI_InitStruct)
{
	uint32_t tmpreg;

	/* configure the register */
	/* Get the CS Register. */
	tmpreg = KBIx->SC;
	/* clear the KBSPEN,KBMOD bit*/
	tmpreg &= ~ (KBI_SC_KBSPEN_MASK | KBI_SC_KBMOD_MASK);
	/* set the KBI_SC register */
	tmpreg |= ((KBI_InitStruct->KBI_SPRegValue)|(KBI_InitStruct->KBI_DetectMode));		
	/* Write to KBI SC */
	KBIx->SC = tmpreg ;
}

/**
  * @brief ����һ��ָ����pinλ.
  * @param KBIx: ѡ��KBI����.
  * @param KBI_Pin:  ָ��pin(KBI_P0~KBI_P31)
  * @param EdgeSelect:  ��Եѡ��
  *		�����������ȡ�����ֵ:
  *			@arg KBI_FallEdge_LowLevel: ѡ���½��غ͵͵�ƽ
  *			@arg KBI_RiseEdge_HighLevel: ѡ�������غ͸ߵ�ƽ
  * @retval None.
  */
void KBI_PinConfig(KBI_Type *KBIx, uint8_t KBI_Pin,uint8_t EdgeSelect)
{
	/*Enable the KBI pin speified.*/
	KBIx->PE |= (( (uint32_t)1	<<	KBI_Pin) & KBI_PE_KBIPE_MASK);
	
	/*first clear the KBI Edge Select speified.*/
	KBIx->ES &= ~(( (uint32_t)1u << KBI_Pin) & KBI_ES_KBEDG_MASK);

	/*Selet the falling edge/low-lever or rising edge/high-lever.*/
	KBIx->ES |= ( ((uint32_t)EdgeSelect << KBI_Pin) & KBI_ES_KBEDG_MASK);
}

/**
  * @brief �������е�pinλ.
  * @param KBIx: ѡ��KBI����.
  * @param KBI_Pin: ָ��pin(KBI_P0~KBI_P31)
  * @param EdgeRegSelect: ѡ��pin��Ե
  *		�����������ȡ�����ֵ:
  *			@arg KBI_FallEdge_LowLevel: �½��غ͵͵�ƽ
  *			@arg KBI_RiseEdge_HighLevel: �����غ͸ߵ�ƽ
  * @retval None.
  */
void KBI_BatchPinConfig(KBI_Type *KBIx, uint32_t KBI_Pin, uint32_t EdgeRegSelect)
{
	/* Set the pins whether enable or not.*/
	KBIx->PE = KBI_Pin;
	
	/* Set the pins edge selection.*/
	KBIx->ES = EdgeRegSelect;
}	

/**
  * @brief ����һ��KBI�ж�.
  * ���������������һ��KBI�ж�.
  * @param  KBIx: ѡ��KBI����
  * @param  NewState:KBI�ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��KBI�ж�
  *			@arg DISABLE: ʹ��KBI�ж�
  * @retval None.
  */
void KBI_InterruptEn(KBI_Type *KBIx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable KBI Interrupt. */
		KBIx ->SC |= KBI_SC_KBIE_MASK;
	}
	else 
	{
		/* Disable KBI Interrupt. */
		KBIx ->SC &= ~KBI_SC_KBIE_MASK;
	}
}

/**
  * @brief ָʾ��ʱ��⵽KBI�ж�����.
  * @param KBIx: ѡ��KBI���衣
  * @retval  �Ƿ��⵽��һ��KBI�ж����󣺣�SET or RESET��
  */
FlagStatus KBI_GetInterruptFlag(const KBI_Type *KBIx)
{
	FlagStatus ret;
	/*Whether a KBI interrupt request is detected or not.*/
	if((KBIx->SC & KBI_SC_KBF_MASK) == KBI_SC_KBF_MASK)
	{
		ret = SET;
	}		
	else	
	{
		ret = RESET;
	}
	return ret;
}

/**
 * @brief �����Ӧ���жϱ�־λ��
 * @param KBIx: ѡ��KBI���衣
 * @retval  None.
 */
void KBI_ClrInterruptFlag(KBI_Type *KBIx)
{
	/*Write a 1 to KBACK to clear the flag.*/
	KBIx->SC |= KBI_SC_KBACK_MASK;
}

/**
  * @brief ��λKIB_SP�Ĵ���.
  * @param KBIx:  ѡ��KBI���衣
  * @retval None.
  */
void KBI_RstSP(KBI_Type *KBIx)
{
	/*Write a 1 to RSTKBSP to reset clesr the KBIxSP register.*/
	KBIx->SC |= KBI_SC_RSTKBSP_MASK;
}
	
/**
  * @brief ��ȡKBIԴpin�Ĵ����ֶΡ�
  * @param KBIx: ѡ��KBI���衣
  * @retval the active pin defined as keyboard interrupt which is push. 
  */
uint32_t KBI_GetSP(const KBI_Type *KBIx)
{
	/*Get the active pin defined as keyboard interrrupt which is pushed.*/
	return (KBIx->SP & KBI_SP_SP_MASK); 
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
