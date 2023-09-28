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
  * @brief  PWTĬ�ϳ�ʼ��
  * @param  PWTx: ������õ�PWT����
  * @retval None
  */ 
void PWT_DeInit(PWT_Type *PWTx)
{
	/* Deinitializes to default reset values */
	PWTx->R1 = 0x00000000;
}

/**
  * @brief  PWT��ʼ��
  * @param  PWTx: ������õ�PWT����
  * @param  PWT_InitStruct: PWT_InitTypeDef���͵�ָ�룬������PWT�����������Ϣ��
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
 * @brief  PWTʹ��
 * @param  PWTx: ������õ�PWT���衣
 * @param  NewState: 
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE: PWTʹ��
 *			@arg DISABLE: PWTʧ��
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
  * @brief  PWT�ж�ʹ��
  * @param  PWTx: ������õ�PWT����
  * @param  NewState: PWT�ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: PWT�ж�ʹ��
  *			@arg DISABLE: PWT�ж�ʧ��
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
  * @brief PWT�������ݾ����ж�ʹ��
  * @param  PWTx: ������õ�PWT����
  * @param  NewState: PWT�������ݾ����ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: PWT�������ݾ����ж�ʹ��
  *			@arg DISABLE: PWT�������ݾ����ж�ʧ��
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
  * @brief PWT����ж�ʹ��
  * @param  PWTx: ������õ�PWT����
  * @param  NewState: PWT����ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: PWT����ж�ʹ��
  *			@arg DISABLE: PWT����ж�ʧ��
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
  * @brief PWT�����λ
  * @param  PWTx: ������õ�PWT����
  * @retval None
  */
void PWT_SetSoftReset(PWT_Type *PWTx)
{
	/* Performs a soft reset to the PWT. This field always reads as 0. */
	PWTx->R1 |= PWT_R1_PWTSR_MASK;
}

/**
 * @brief ��ȡPWT�����־
 * @param  PWTx: ������õ�PWT����
 * @retval ���������־
 */
FlagStatus PWT_GetOverflowFlag(const PWT_Type *PWTx)
{
	return ((PWTx->R1 & PWT_R1_PWTOV_MASK) == PWT_R1_PWTOV_MASK);
}

/**
  * @brief ���PWT�����־λ
  * @param  PWTx: ������õ�PWT����
  * @retval ���������־
  */
void PWT_ClrOverflowFlag(PWT_Type *PWTx)
{
	if((PWTx->R1 & PWT_R1_PWTOV_MASK) == PWT_R1_PWTOV_MASK)
	{
		PWTx->R1 &= ~PWT_R1_PWTOV_MASK;
	}
}

/**
  * @brief ��ȡPWT�����Ƿ���Ч��־
  * @param  PWTx: ������õ�PWT����
  * @retval ���������־
  */
FlagStatus PWT_GetPWTRDY(const PWT_Type *PWTx)
{
	return ((PWTx->R1 & PWT_R1_PWTRDY_MASK) == PWT_R1_PWTRDY_MASK);
}

/**
  * @brief ���PWT������Ч��־
  * @param  PWTx: ������õ�PWT����
  * @retval ���������־
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
  * @brief  ��ȡPWT����������
  * @param  PWTx: ������õ�PWT���衣
  * @retval ����PWT����������
  */
uint16_t PWT_GetPPW(const PWT_Type *PWTx)
{
	uint16_t  PPWVal;
	PPWVal = (uint16_t )((PWTx->R1 & PWT_R1_PPW_MASK) >> 16); 
	return PPWVal ;
}

/**
  * @brief ��ȡPWT�ĸ�������
  * @param  PWTx: ������õ�PWT���衣
  * @retval ����PWT�ĸ�������
  */
uint16_t PWT_GetNPW(const PWT_Type *PWTx)
{
	uint16_t NPWVal;
	NPWVal = (uint16_t )(PWTx->R2 & PWT_R2_NPW_MASK);
	return NPWVal ;
}

/**
  * @brief ���PWT��������ֵ
  * @param  PWTx: ������õ�PWT���衣
  * @retval ����PWT��������ֵ
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


