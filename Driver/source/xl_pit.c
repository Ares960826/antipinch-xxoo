/**
  ******************************************************************************
  * @file     xl_pit.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PIT firmware program 
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
#include "xl_pit.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PIT PIT Module 
  * @brief PIT Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
	#define PIT_CLEAR_MASK     ((uint8_t)0x02)	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup PIT_Private_Functions
  * @{
  */ 
	
/**
  * @brief  PIT默认初始化
  * @param  None
  * @retval None
  */
void PIT_DeInit(void)
{
	/* Deinitializes to default reset values */
	PIT->CHANNEL[0].CTR = 0x00;
	PIT->CHANNEL[1].CTR = 0x00;
	PIT->CHAIN=0x00;	
}

/**
  * @brief PTT初始化
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @param  PIT_Mode: 模式选择
  *		这个参数可以取下面的值:
  *        @arg PIT_Run_Mode: 自由运行模式
  *        @arg PIT_Count_Mode: 用户定义计数模式
  * @param  CLK_DIV: 时钟分频(0~65535)
  * @retval None
  */
void PIT_Init(uint8_t Channel,uint8_t PIT_Mode,uint16_t CLK_DIV)
{
	uint32_t tmpreg;

	/*---------------------------- PIT CTR Configuration ------------------------*/	
	/* Get the PIT CTR value. */
	tmpreg = PIT->CHANNEL[Channel].CTR ;

	/* Clear MODE bit Value in CTR register.*/
	tmpreg &= ~PIT_CLEAR_MASK;

	/* Set the bit MODE in CTR Register. */
	tmpreg |= (PIT_Mode);

	//Aaron He add clock divider
	PIT->PIT_DIV[Channel] = CLK_DIV;

	/* Write to PIT CTR Register. */
	PIT->CHANNEL[Channel].CTR = tmpreg ;
}

/**
  * @brief PIT使能
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @param  NewState: 使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: PIT使能
  *			@arg DISABLE: PIT失能
  * @retval None.
  */
void PIT_EnableCmd(uint8_t Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable PIT bits for PIT. */
		PIT->CHANNEL[Channel].CTR |= PIT_CTR_EN_MASK;
	}
	else 
	{
		/* Disable PIT bits for PIT. */
		PIT->CHANNEL[Channel].CTR &= ~PIT_CTR_EN_MASK;
	}
}

/**
  * @brief PIT中断使能
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @param  NewState: 使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: PIT使能
  *			@arg DISABLE: PIT失能
  * @retval None.
  */
void PIT_InterruptEn(uint8_t Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* ENABLE PIT interrupt for PIT. */
		PIT->CHANNEL[Channel].CTR &= ~PIT_CTR_IM_MASK;			
	}
	else
	{
		/* DISABLE PIT interrupt for PIT. */
		PIT->CHANNEL[Channel].CTR |= PIT_CTR_IM_MASK;
	}
}

/**
  * @brief 为PIT设置信道模值.
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @param  loadVal: 被加载到PIT中的值.
  * @retval None.
  */
void PIT_SetLoadCount(uint8_t Channel,uint32_t loadVal)
{
	/* Value to be load into PIT. */
	PIT->CHANNEL[Channel].LC = loadVal ;
}

/**
  * @brief 得到PIT的通道电流值.
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @retval current Value.返回电流值.
  */
uint32_t PIT_GetCurrentVal(uint8_t Channel)
{
	uint32_t currentVal;
	
	/* get the current Value. */
	currentVal = PIT->CHANNEL[Channel].CV ;

	/* return the value. */
	return currentVal ;
}

/**
  * @brief 清除PIT中断.
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @retval None.
  */
void PIT_ClrInterrupt(uint8_t Channel)
{
	/* clear the interrupt from PIT.*/
	PIT->CHANNEL[Channel].EOI;
}

/**
  * @brief 返回PIT的中断状态.
  * @param  Channel: PIT通道号
  *		这个参数可以取下面的值:
  *        @arg PIT_Channel0: PIT通道0
  *        @arg PIT_Channel1: PIT通道1
  * @retval interrupt status.返回中断状态.
  */
ITStatus PIT_GetIntStatus(uint8_t Channel)
{
	/* return interrupt status. */
	return ((PIT->CHANNEL[Channel].IS & PIT_IS_IS_MASK) == PIT_IS_IS_MASK);
}

/**
  * @brief 获取PIT的中断状态.
  * @retval 中断状态
  */
uint8_t PIT_GetAllIntStatus(void)
{
	/* return all interrupt status. */
	return (uint8_t)(PIT->AIS & PIT_AIS_AIS_MASK);
}

/**
  * @brief 清除所有活动中的中断.
  * @param  None
  * @retval None.
  */
void PIT_ClrAllInterrupt(void)
{
	/* Dummy reading the register and clear all active interrupts. */
	(void)(PIT->AEOI);
}

/**
  * @brief 获取无屏蔽中断状态.
  * @param  None
  * @retval 返回无屏蔽中断状态
  */
uint8_t PIT_GetRawIntStatus(void)
{
	/* return unmasked interrupt status. */
	return (uint8_t)(PIT->RAWIS & PIT_RAWIS_RAWIS_MASK);
}


/**
  * @brief PIT 冻结模式启用或禁用.
  * @param  NewState: 使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 冻结模式使能
  *			@arg DISABLE: 冻结模式失能
  * @retval None.
  */
void PIT_FreezeCmd(FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Timers are stopped in debug mode . */
		PIT->CHAIN |= PIT_DEBUG_FRZ_MASK;			
	}
	else
	{
		/* Timers continue to run in debug mode . */
		PIT->CHAIN &= ~PIT_DEBUG_FRZ_MASK;
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

