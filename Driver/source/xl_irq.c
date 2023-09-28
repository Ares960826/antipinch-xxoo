/**
  ******************************************************************************
  * @file     xl_irq.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about IRQ firmware program 
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
#include "xl_irq.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup IRQ IRQ Module 
  * @brief IRQ Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup IRQ_Private_Functions
  * @{
 */ 	

/**
  * @brief IRQĬ�ϳ�ʼ��
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��
	*		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @retval None.
  */
void IRQ_DeInit(IRQ_Type *IRQx,uint8_t IRQ_Channel)
{
	/* Reset all the register to a known state. */
	IRQx->SC[IRQ_Channel] = 0x00u ;
}

 /**
  * @brief IRQ��ʼ��
  * @param IRQx: ѡ��IRQ����
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @param IRQ_InitStuct: ָ�����ָ��IRQ����������Ϣ��IRQ_InitTypeDef�ṹ.
  * @retval None.
  */
void IRQ_Init(IRQ_Type *IRQx,uint8_t IRQ_Channel, const IRQ_InitTypeDef *IRQ_InitStuct)
{
	uint32_t tmpreg;

	/* cconfigure the register */
	/* Get the CS Register. */
	tmpreg = IRQx->SC[IRQ_Channel];
	/* Cleat the IRQEDG bit,IRQMOD bit*/
	tmpreg &= ~(IRQ_SC_IRQEDG_MASK | IRQ_SC_IRQMOD_MASK);

	/* Set the IRQEDG bit,IRQMOD bit*/
	tmpreg |= ((IRQ_InitStuct->IRQ_EdgeSelect)	|	(IRQ_InitStuct->IRQ_ModeSelect));

	/* Write to IRQ SC */
	IRQx->SC[IRQ_Channel] = tmpreg ;
}

/**
  * @brief IRQ���Ž����ڲ������豸
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @param NewState:IRQ����ʧ��״̬
  *		�����������Ϊ����ֵ:
	*		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʧ���ڲ������豸
  *			@arg DISABLE: ʹ���ڲ������豸
  * @retval None.
  */
void IRQ_PullDevDisableCmd(IRQ_Type *IRQx,uint8_t IRQ_Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/*  RQ pull device disabled if IRQPE = 1.  */
		IRQx->SC[IRQ_Channel] |= IRQ_SC_IRQPDD_MASK;
	}
	else 
	{
		/* IRQ pull device enabled if IRQPE = 1. */
		IRQx->SC[IRQ_Channel] &= ~IRQ_SC_IRQPDD_MASK;
	}
}

 /**
  * @brief IRQʹ��
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @param NewState:IRQʹ��״̬
	  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��IRQ����
  *			@arg DISABLE: ʧ��IRQ����
  * @retval None.
  */
void IRQ_PinEnableCmd(IRQ_Type *IRQx,uint8_t IRQ_Channel,FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		/* Enable IRQ pin function. */
		IRQx->SC[IRQ_Channel] |= IRQ_SC_IRQPE_MASK;
	}
	else
	{
		/* Disable IRQ pin function. */
		IRQx->SC[IRQ_Channel] &= ~IRQ_SC_IRQPE_MASK;
	}
}

/**
  * @brief IRQ�ж�ʹ��
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @param NewState:IRQ�ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��IRQ�ж�
  *			@arg DISABLE: ʧ��IRQ�ж�
  * @retval None
  */
void IRQ_InterruptEn(IRQ_Type *IRQx,uint8_t IRQ_Channel,FunctionalState NewState)
{
	IRQx->SC[IRQ_Channel] |= IRQ_SC_IRQACK_MASK;
	
	if(NewState != DISABLE )
	{
		/* Enable IRQ Interrupt. */
		IRQx->SC[IRQ_Channel] |= IRQ_SC_IRQIE_MASK;
	}
	else 
	{
		/* Disable IRQ Interrupt. */
		IRQx->SC[IRQ_Channel] &= ~IRQ_SC_IRQIE_MASK;
	}
}

/**
  * @brief ��ȡ�ж������־��
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @retval IRQ flag bit.����IRQ��־λ��
  */
FlagStatus IRQ_GetFlag(const IRQ_Type *IRQx,uint8_t IRQ_Channel)
{
	return ((IRQx->SC[IRQ_Channel] & IRQ_SC_IRQF_MASK ) == IRQ_SC_IRQF_MASK);
}

 /**
  * @brief ����ж������־��
  * @param IRQx: ѡ��IRQ���衣
  * @param IRQ_Channel: ѡ��IRQͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg EXTI0: �ⲿ�ж�ͨ��0
  *			@arg EXTI1: �ⲿ�ж�ͨ��1
  *			@arg EXTI2: �ⲿ�ж�ͨ��2
  *			@arg EXTI3: �ⲿ�ж�ͨ��3
  *			@arg EXTI4: �ⲿ�ж�ͨ��4
  *			@arg EXTI5: �ⲿ�ж�ͨ��5
  *			@arg EXTI6: �ⲿ�ж�ͨ��6
  *			@arg EXTI7: �ⲿ�ж�ͨ��7
  *			@arg EXTI8: �ⲿ�ж�ͨ��8
  *			@arg EXTI9: �ⲿ�ж�ͨ��9
  *			@arg EXTI19: �ⲿ�ж�ͨ��10
  *			@arg EXTI11: �ⲿ�ж�ͨ��11
  *			@arg EXTI12: �ⲿ�ж�ͨ��12
  *			@arg EXTI13: �ⲿ�ж�ͨ��13
  *			@arg EXTI14: �ⲿ�ж�ͨ��14
  *			@arg EXTI15: �ⲿ�ж�ͨ��15
  * @retval None. 
  */
void IRQ_ClrFlag(IRQ_Type *IRQx,uint8_t IRQ_Channel)
{
	IRQx->SC[IRQ_Channel] |= IRQ_SC_IRQACK_MASK;
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

