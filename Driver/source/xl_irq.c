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
  * @brief IRQ默认初始化
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道
	*		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @retval None.
  */
void IRQ_DeInit(IRQ_Type *IRQx,uint8_t IRQ_Channel)
{
	/* Reset all the register to a known state. */
	IRQx->SC[IRQ_Channel] = 0x00u ;
}

 /**
  * @brief IRQ初始化
  * @param IRQx: 选择IRQ外设
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @param IRQ_InitStuct: 指向包含指定IRQ外设配置信息的IRQ_InitTypeDef结构.
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
  * @brief IRQ引脚禁用内部上拉设备
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @param NewState:IRQ上拉失能状态
  *		这个参数可以为以下值:
	*		这个参数可以取下面的值:
  *			@arg ENABLE: 失能内部上拉设备
  *			@arg DISABLE: 使能内部上拉设备
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
  * @brief IRQ使能
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @param NewState:IRQ使能状态
	  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能IRQ功能
  *			@arg DISABLE: 失能IRQ功能
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
  * @brief IRQ中断使能
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @param NewState:IRQ中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能IRQ中断
  *			@arg DISABLE: 失能IRQ中断
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
  * @brief 获取中断请求标志。
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
  * @retval IRQ flag bit.返回IRQ标志位。
  */
FlagStatus IRQ_GetFlag(const IRQ_Type *IRQx,uint8_t IRQ_Channel)
{
	return ((IRQx->SC[IRQ_Channel] & IRQ_SC_IRQF_MASK ) == IRQ_SC_IRQF_MASK);
}

 /**
  * @brief 清除中断请求标志。
  * @param IRQx: 选择IRQ外设。
  * @param IRQ_Channel: 选择IRQ通道.
  *		这个参数可以取下面的值:
  *			@arg EXTI0: 外部中断通道0
  *			@arg EXTI1: 外部中断通道1
  *			@arg EXTI2: 外部中断通道2
  *			@arg EXTI3: 外部中断通道3
  *			@arg EXTI4: 外部中断通道4
  *			@arg EXTI5: 外部中断通道5
  *			@arg EXTI6: 外部中断通道6
  *			@arg EXTI7: 外部中断通道7
  *			@arg EXTI8: 外部中断通道8
  *			@arg EXTI9: 外部中断通道9
  *			@arg EXTI19: 外部中断通道10
  *			@arg EXTI11: 外部中断通道11
  *			@arg EXTI12: 外部中断通道12
  *			@arg EXTI13: 外部中断通道13
  *			@arg EXTI14: 外部中断通道14
  *			@arg EXTI15: 外部中断通道15
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

