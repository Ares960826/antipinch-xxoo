/**
  ******************************************************************************
  * @file     xl_pmc.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PMC firmware program 
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
#include "xl_pmc.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PMC PMC Module 
  * @brief PMC Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PMC_Private_Functions
  * @{
  */ 

/**
  * @brief  ��PMC��ģ������Ϊ��ʼ״̬��
  * @param  None
  * @retval None.
  */
void PMC_Deinit(void)
{
	PMC->SPMSC = 0x001Cu;
}

/**
  * @brief  PMC��ʼ��
  * @param  PMC_InitStruct: PMC_InitTypeDef ����ָ�룬������PMC��ʼ�����õĲ�����Ϣ
  * @retval None
  */
void PMC_Init(const PMC_InitTypeDef *PMC_InitStruct)
{
	uint16_t tmpreg;

	/*********************** configure the register. ****************************/
	/* Get the PMC SPMSC value */
	tmpreg = (uint16_t)PMC->SPMSC ;
	/* clear the bits in SPMSC register */
	tmpreg &= ~(uint16_t)(PMC_SPMSC_LVDE_MASK | PMC_SPMSC_LVDSE_MASK | PMC_SPMSC_LVDRE_MASK | \
			PMC_SPMSC_LVWIE_MASK | PMC_SPMSC_LVWV_MASK | PMC_SPMSC_LVDV_MASK) ;
	/* set PMC SPMSC: System Power Management Status and Control Register */
	tmpreg |= ( (uint16_t)( ((uint16_t)PMC_InitStruct->PMC_LVWIntEnable  << PMC_SPMSC_LVWIE_SHIFT) & PMC_SPMSC_LVWIE_MASK) | \
						(uint16_t)( ((uint16_t)PMC_InitStruct->PMC_LVDRstEnable << PMC_SPMSC_LVDRE_SHIFT) & PMC_SPMSC_LVDRE_MASK) | \
						(uint16_t)( ((uint16_t)PMC_InitStruct->PMC_LVDStopEnable << PMC_SPMSC_LVDSE_SHIFT) & PMC_SPMSC_LVDSE_MASK) | \
						(uint16_t)( ((uint16_t)PMC_InitStruct->PMC_LVDectEnable  << PMC_SPMSC_LVDE_SHIFT) & PMC_SPMSC_LVDE_MASK) | \
						(uint16_t)( ((uint16_t)PMC_InitStruct->PMC_lvwvselect << PMC_SPMSC_LVWV_SHIFT) & PMC_SPMSC_LVWV_MASK) | \
						(uint16_t)( ((uint16_t)PMC_InitStruct->PMC_lvdvselect << PMC_SPMSC_LVDV_SHIFT) & PMC_SPMSC_LVDV_MASK) );
	/* Write to PMC SPMSC */
	PMC->SPMSC = tmpreg ;
}


/**
  * @brief  �����С��ȴ���ֹͣ����������PMCģʽ
  * @param  u8PmcMode: Ҫָ����PMC��ģʽ.
  *		�����������ȡ�����ֵ:
  *			@arg PMC_ModeRun: ����ģʽ
  *			@arg PMC_ModeWait: WAITģʽ
  *			@arg PMC_ModeStop4: STOPģʽʹ��LVD
  *			@arg PMC_ModeStop3: STOPģʽ����LVD
  * @retval None
  */
void PMC_SetMode(uint8_t u8PmcMode)
{
    switch(u8PmcMode & 0x3u)
    {
        case PMC_ModeRun:
            break;
        case PMC_ModeWait:
			/* Clear the SLEEPDEEP bit to make sure we go into WAIT (sleep) mode instead
			 * of deep sleep.
			 */
			SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
			/* using KEIL's uVision, use the CMSIS intrinsic */
			__WFI();
			break;
        case PMC_ModeStop4:
			/* enable LVD in stop mode */
			PMC->SPMSC |= (PMC_SPMSC_LVDE_MASK | PMC_SPMSC_LVDSE_MASK);
			/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
			SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
			/* using KEIL's uVision, use the CMSIS intrinsic */
			__WFI();
			break;
        case PMC_ModeStop3:
		default:
			/* disable LVD in stop mode */
			PMC->SPMSC &= ~(PMC_SPMSC_LVDE_MASK | PMC_SPMSC_LVDRE_MASK | PMC_SPMSC_LVDSE_MASK);
			/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
			SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
			/* using KEIL's uVision, use the CMSIS intrinsic */
			__WFI();
            break;
    }
}

/**
  * @brief  ���lvm�����־λ
  * @param  None.
  * @retval PMC��־λ
  */
FlagStatus PMC_GetLVWFlag(void)
{	
	FlagStatus ret;
	if( (PMC->SPMSC & PMC_SPMSC_LVWF_MASK) == PMC_SPMSC_LVWF_MASK)
	{
		ret = SET;
	}
	else
	{
		ret= RESET;
	}
	
	return ret;
}

/**
  * @brief  ���lvm�����־λ.
  * @param  None.
  * @retval None.
  */
void PMC_ClrLVWFlag(void)
{
	if((PMC->SPMSC & PMC_SPMSC_LVWF_MASK) == PMC_SPMSC_LVWF_MASK)
	{
		/* LVWF must be cleared by writing LVWACK */
		PMC->SPMSC |= PMC_SPMSC_LVWACK_MASK; 
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
