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
  * @brief KBI默认初始化
  * @param KBIx: 选择KBI外设.
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
  * @brief KBI初始化
  * @param KBIx: 选择KBI外设.
  * @param KBI_InitStruct: 指向包含指定KBI外设配置信息的KBI_InitTypeDef结构.
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
  * @brief 配置一个指定的pin位.
  * @param KBIx: 选择KBI外设.
  * @param KBI_Pin:  指定pin(KBI_P0~KBI_P31)
  * @param EdgeSelect:  边缘选择
  *		这个参数可以取下面的值:
  *			@arg KBI_FallEdge_LowLevel: 选择下降沿和低电平
  *			@arg KBI_RiseEdge_HighLevel: 选择上升沿和高电平
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
  * @brief 配置所有的pin位.
  * @param KBIx: 选择KBI外设.
  * @param KBI_Pin: 指定pin(KBI_P0~KBI_P31)
  * @param EdgeRegSelect: 选择pin边缘
  *		这个参数可以取下面的值:
  *			@arg KBI_FallEdge_LowLevel: 下降沿和低电平
  *			@arg KBI_RiseEdge_HighLevel: 上升沿和高电平
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
  * @brief 启动一个KBI中断.
  * 这个函数用于启动一个KBI中断.
  * @param  KBIx: 选择KBI外设
  * @param  NewState:KBI中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能KBI中断
  *			@arg DISABLE: 使能KBI中断
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
  * @brief 指示何时检测到KBI中断请求.
  * @param KBIx: 选择KBI外设。
  * @retval  是否检测到了一个KBI中断请求：（SET or RESET）
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
 * @brief 清除相应的中断标志位。
 * @param KBIx: 选择KBI外设。
 * @retval  None.
 */
void KBI_ClrInterruptFlag(KBI_Type *KBIx)
{
	/*Write a 1 to KBACK to clear the flag.*/
	KBIx->SC |= KBI_SC_KBACK_MASK;
}

/**
  * @brief 复位KIB_SP寄存器.
  * @param KBIx:  选择KBI外设。
  * @retval None.
  */
void KBI_RstSP(KBI_Type *KBIx)
{
	/*Write a 1 to RSTKBSP to reset clesr the KBIxSP register.*/
	KBIx->SC |= KBI_SC_RSTKBSP_MASK;
}
	
/**
  * @brief 获取KBI源pin寄存器字段。
  * @param KBIx: 选择KBI外设。
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
