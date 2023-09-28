/**
  ******************************************************************************
  * @file     xl_pwt.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PWT firmware program 
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
#include "xl_pwt.h"
	


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PWT PWT Module 
  * @brief PWT Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWT_Private_Functions 
  * @{
  */ 

/**
  * @brief  PWT默认初始化
  * @param  PWTx: 输入可用的PWT外设
  * @retval None
  */ 
void PWT_DeInit(PWT_Type *PWTx)
{
	/* Deinitializes to default reset values */
	PWTx->R1 = 0x00000000;
}

/**
  * @brief  PWT初始化
  * @param  PWTx: 输入可用的PWT外设
  * @param  PWT_InitStruct: PWT_InitTypeDef类型的指针，包含了PWT外设的设置信息。
  * @retval None
  */
void PWT_Init(PWT_Type *PWTx,const PWT_InitTypeDef *PWT_InitStruct)
{
	uint32_t tmpreg;

/*---------------------------- PWT R1 Configuration ------------------------*/
	/* Get the PWT R1 value */
	tmpreg = PWTx->R1 ;

	/* Clear PCLKS,PINSEL,EDGE,PRE bits */
	tmpreg &= ~(PWT_R1_PCLKS_MASK | PWT_R1_PINSEL_MASK |PWT_R1_EDGE_MASK | PWT_R1_PRE_MASK);

	/* Set PCLKS,PINSEL,EDGE,PRE bits */
	tmpreg |= (PWT_InitStruct->PWT_ClkSource | PWT_InitStruct->PWT_PulseInputSelect | \
						 PWT_InitStruct->PWT_EdgeSensitivity | PWT_InitStruct->PWT_ClkPrescaler);	
	
	/* Write to PWT R1 */
	PWTx->R1 = tmpreg ;
}

/**
 * @brief  PWT使能
 * @param  PWTx: 输入可用的PWT外设。
 * @param  NewState: 
 *		这个参数可以取下面的值:
 *			@arg ENABLE: PWT使能
 *			@arg DISABLE: PWT失能
 * @retval None
 */
void PWT_EnableCmd(PWT_Type *PWTx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the PWT */
		PWTx->R1 |= PWT_R1_PWTEN_MASK;
	}
	else 
	{
		/* Disable the PWT */
		PWTx->R1 &= ~PWT_R1_PWTEN_MASK;
	}
}

/**
  * @brief  PWT中断使能
  * @param  PWTx: 输入可用的PWT外设
  * @param  NewState: PWT中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: PWT中断使能
  *			@arg DISABLE: PWT中断失能
  * @retval None
  */
void PWT_InterruptEn(PWT_Type *PWTx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enables the PWT module to generate an interrupt */
		PWTx->R1 |= PWT_R1_PWTIE_MASK;
	}
	else 
	{
		/* Disable the PWT module to generate an interrupt */
		PWTx->R1 &= ~PWT_R1_PWTIE_MASK;
	}
}

/**
  * @brief PWT脉宽数据就绪中断使能
  * @param  PWTx: 输入可用的PWT外设
  * @param  NewState: PWT脉宽数据就绪中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: PWT脉宽数据就绪中断使能
  *			@arg DISABLE: PWT脉宽数据就绪中断失能
  * @retval None
  */
void PWT_PWTRDYIntCmd(PWT_Type *PWTx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enables the data ready interrupt. */
		PWTx->R1 |= PWT_R1_PRDYIE_MASK;
	}
	else 
	{
		/* Disable the data ready interrupt. */
		PWTx->R1 &= ~PWT_R1_PRDYIE_MASK;
	}
}

/**
  * @brief PWT溢出中断使能
  * @param  PWTx: 输入可用的PWT外设
  * @param  NewState: PWT溢出中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: PWT溢出中断使能
  *			@arg DISABLE: PWT溢出中断失能
  * @retval None
  */
void PWT_OverflowIntCmd(PWT_Type *PWTx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enables the counter overflow interrupt. */
		PWTx->R1 |= PWT_R1_POVIE_MASK;
	}
	else 
	{
		/* Disable the counter overflow interrupt. */
		PWTx->R1 &= ~PWT_R1_POVIE_MASK;
	}
}

/**
  * @brief PWT软件复位
  * @param  PWTx: 输入可用的PWT外设
  * @retval None
  */
void PWT_SetSoftReset(PWT_Type *PWTx)
{
	/* Performs a soft reset to the PWT. This field always reads as 0. */
	PWTx->R1 |= PWT_R1_PWTSR_MASK;
}

/**
 * @brief 获取PWT溢出标志
 * @param  PWTx: 输入可用的PWT外设
 * @retval 返回溢出标志
 */
FlagStatus PWT_GetOverflowFlag(const PWT_Type *PWTx)
{
	return ((PWTx->R1 & PWT_R1_PWTOV_MASK) == PWT_R1_PWTOV_MASK);
}

/**
  * @brief 清空PWT溢出标志位
  * @param  PWTx: 输入可用的PWT外设
  * @retval 返回溢出标志
  */
void PWT_ClrOverflowFlag(PWT_Type *PWTx)
{
	if((PWTx->R1 & PWT_R1_PWTOV_MASK) == PWT_R1_PWTOV_MASK)
	{
		PWTx->R1 &= ~PWT_R1_PWTOV_MASK;
	}
}

/**
  * @brief 获取PWT脉宽是否有效标志
  * @param  PWTx: 输入可用的PWT外设
  * @retval 返回溢出标志
  */
FlagStatus PWT_GetPWTRDY(const PWT_Type *PWTx)
{
	return ((PWTx->R1 & PWT_R1_PWTRDY_MASK) == PWT_R1_PWTRDY_MASK);
}

/**
  * @brief 清空PWT脉宽有效标志
  * @param  PWTx: 输入可用的PWT外设
  * @retval 返回溢出标志
  */
void PWT_ClrPWTRDYFlag(PWT_Type *PWTx)
{
	/* Dummy read while CHF is set */
	if((PWTx->R1 & PWT_R1_PWTRDY_MASK) == PWT_R1_PWTRDY_MASK)
	{
		PWTx->R1 &= ~PWT_R1_PWTRDY_MASK;
	}
}

/**
  * @brief  获取PWT的正脉冲宽度
  * @param  PWTx: 输入可用的PWT外设。
  * @retval 返回PWT的正脉冲宽度
  */
uint16_t PWT_GetPPW(const PWT_Type *PWTx)
{
	uint16_t  PPWVal;
	PPWVal = (uint16_t )((PWTx->R1 & PWT_R1_PPW_MASK) >> 16); 
	return PPWVal ;
}

/**
  * @brief 获取PWT的负脉冲宽度
  * @param  PWTx: 输入可用的PWT外设。
  * @retval 返回PWT的负脉冲宽度
  */
uint16_t PWT_GetNPW(const PWT_Type *PWTx)
{
	uint16_t NPWVal;
	NPWVal = (uint16_t )(PWTx->R2 & PWT_R2_NPW_MASK);
	return NPWVal ;
}

/**
  * @brief 获得PWT计数器的值
  * @param  PWTx: 输入可用的PWT外设。
  * @retval 返回PWT计数器的值
  */
uint16_t PWT_GetPWTCounter(const PWT_Type *PWTx)
{
	uint16_t PWTCounter;
	PWTCounter = (uint16_t )((PWTx->R2 & PWT_R2_PWTC_MASK) >> 16);
	return PWTCounter ;
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


