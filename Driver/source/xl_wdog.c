 /**
  ******************************************************************************
  * @file     xl_wdog.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about WDOG firmware program 
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
#include "xl_wdog.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup WDOG WDOG Module 
  * @brief WDOG Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
	
/** @defgroup WDOG_Private_Functions 
  * @{
  */ 

/**
  * @brief  设置WatchDOG外设寄存器为初始状态
  * @param  WDOGx: WDT外设。
  * @retval None
  */
void WDOG_DeInit(WDOG_Type *WDOGx)
{
	/* Deinitializes to default reset values */
	//WDOGx->CS2 = 0x00;
	WDOGx->CS1 = 0x00;	/*
	* (1-186)14.2.1 WDOG 控制寄存器(CS1)*
	* WDOGx=0x4005 2000u = 0100 0000 0000 0101 0010 0...*/
}

/**
  * @brief 初始化WTD模式
  * @param  WDOGx: 选择WDT外设。
  * @param  WDOG_InitStruct: WDOG_InitTypeDef 类型的指针，包含特定的WDT外设的设置信息
  * @retval None
  */
void WDOG_Init(WDOG_Type *WDOGx, const WDOG_InitTypeDef *WDOG_InitStruct)
{
	uint8_t tmpreg1;
	uint32_t tmpreg;

	/*---------------------------- WDT CS2 Configuration ------------------------*/	
	/* Get the WDT CS1 value */
	tmpreg1 = (uint8_t)WDOGx->CS2 ;

	/* Clear RPL, RMOD bits */
	//tmpreg1 &= ~(WDOG_CS2_CLK_MASK | WDOG_CS2_PRES_MASK | WDOG_CS2_STOP_MASK | WDOG_CS2_WAIT_MASK | WDOG_CS2_DEBUG_MASK);
	tmpreg1 &= ~0x7Fu;

	/* Set the bit in CS1 Register */
	tmpreg1 |= (uint8_t)(WDOG_InitStruct->WDOG_ClkSource | \
				((uint32_t)WDOG_InitStruct->WDOG_DEBUGEn << WDOG_CS2_DEBUG_SHIFT) | \
				((uint32_t)WDOG_InitStruct->WDOG_PRESEn << WDOG_CS2_PRES_SHIFT)   | \
				((uint32_t)WDOG_InitStruct->WDOG_STOPEn << WDOG_CS2_STOP_SHIFT)   | \
				((uint32_t)WDOG_InitStruct->WDOG_WAITEn << WDOG_CS2_WAIT_SHIFT));
	
	/* Write to WDT CS1 */
	WDOGx->CS2 = (uint32_t)tmpreg1;

/*---------------------------- WDT CS1 Configuration ------------------------*/	
	/* Get the WDT CS1 value */
	tmpreg = WDOGx->CS1;

	/* Clear RPL, RMOD bits */
	tmpreg &= ~(WDOG_CS1_RMOD_MASK | WDOG_CS1_RPL_MASK);

	/* Set the bit in CS1 Register */
	tmpreg |= (((uint32_t)WDOG_InitStruct->WDOG_PulseLength << WDOG_CS1_RPL_SHIFT) | \
	           ((uint32_t)WDOG_InitStruct->WDOG_ResponseMode << WDOG_CS1_RMOD_SHIFT));

	/* Write to WDT CS1 */
	WDOGx->CS1 = tmpreg ;
/*------------------------------------ end --------------------------------*/	
}

/**
  * @brief  WDOG使能
  * @param  WDOGx: 选择WODG外设。
  * @param  State: WDOG使能状态
  *		这个参数可以为以下值:
  *			@arg ENABLE: WDOG使能
  *			@arg DISABLE: WDOG失能
  * @retval None
  */
void WDOG_EnableCmd(WDOG_Type *WDOGx,FunctionalState State)
{
	if(State !=DISABLE)
	{
		/* Enable the WDT */
		WDOGx->CS1 |= WDOG_CS1_EN_MASK;		// WDOG_CS1_EN_MASK=0x00000001u
		// CS1[0] |= 0x0000 0001u -> CS1[0x0000 0001u]
	}
	else 
	{
		/* Disable the WDT */
		WDOGx->CS1 &= ~WDOG_CS1_EN_MASK;	/*
		* (1-186)14.2.1 WDOG 控制寄存器(CS1)
		* CS1[0] &= ~(0x0000 0001u) = 0xFFFF FFFEu
		* -> CS1[0] &= 0xFFFF FFFEu = .... 1110
		* -> CS1=0	*/
	}
}

/**
  * @brief  建立看门狗时钟分频
  * @param  WDOGx: 选择WDT外设。
  * @param  TimeoutIndex: 超时时间
  * @retval None
  */
void WDOG_SetTimeoutPeriod(WDOG_Type *WDOGx, uint8_t TimeoutIndex)
{
	WDOGx->TORR &= ~WDOG_TORR_TOP_MASK;
	WDOGx->TORR |= TimeoutIndex;
}

/**
  * @brief  获得内部计数器的值
  * @param  WDOGx: 选择WDT外设。
  * @retval 计数器的当前值
  */
uint32_t WDOG_GetCurrentVal(const WDOG_Type *WDOGx)
{
	return WDOGx->CCVR ;
}

/**
  * @brief  重启 WDT
  * @param  WDOGx: 选择WDT外设。
  * @retval None
  */
void WDOG_CountRestart(WDOG_Type *WDOGx)
{	
	/* write the value 0x76 to the register */
	WDOGx->CRR = 0x76;		
}

/**
  * @brief  获得WDOG中断状态
  * @param  WDOGx: 选择WDT外设。
  * @retval 中断状态
  */
FlagStatus WDOG_GetIntStatus(const WDOG_Type *WDOGx)
{
	FlagStatus  ret;
	
	/* get the interrupt status */
	if(WDOGx->STAT != 0u)
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
  * @brief  清空WDOG中断
  * @param  WDOGx: 选择WDT外设。
  * @retval None
  */
void WDOG_ClrInt(const WDOG_Type *WDOGx)
{
	/* Dummy read to clear */
	(void)(WDOGx->EOI);
}

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */
/**
  * @}
  */

/**
  * @}
  */


