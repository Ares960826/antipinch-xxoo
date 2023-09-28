/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup UART_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      bsp/UART/lin_lld_timesrv.c
*
* @author    FPT Software
*
* @brief     Timer for KEA
*
******************************************************************************/

/******************************************************************************
 *
 * History:
 * 2014   v1.0  First version for Kinetis timer handler
 *
 *****************************************************************************/

#include "lin_lld_timesrv.h"
#include "lin_lld_uart.h"
#include "lin_common_proto.h"
#include "lin_hw_cfg.h"
#include "xl_sim.h"
#include "xl_ftm.h"
#include "xl_nvic.h"
#include "system_xl6600.h"

/*base timer*/
void lin_lld_timer_K_init(void)
{
	FTM_InitTypeDef FTM_InitStructure;
	SIM->SCGC &= ~SIM_SCGC_FTM2; /* disable Clock for FTM2 */
	/* config irq */
	NVIC_InitTypeDef NVIC_InitStructure;	// 定义NVIC初始化
	NVIC_InitStructure.NVIC_IRQChannel = FTM2_IRQn;	// 设置FTM2的中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;// 设置抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;	// 设置子优先级为5
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// 启用中断
	NVIC_Init(&NVIC_InitStructure);	// 初始化NVIC
	SIM->SCGC 	|= SIM_SCGC_FTM2; /* Enable Clock for FTM2 */
	SIM->SCGC1 	|= SIM_SCGC1_FTM2T;
	FTM_WriteProtectDisable(FTM2);	// 禁用FTM2的写保护

	FTM_InitStructure.FTM_Prescaler = FTM_CLOCK_PS_DIV128;		/* Select Preescaler in this case 128.20 Mhz/128 =156.25 Khz. *//* Counter increase by one every 6.4 us */
	/* 设置预分频值为128，这意味着20 MHz/128 = 156.25 KHz，计数器每6.4微秒增加1 */
	FTM_InitStructure.FTM_ClkSource = FTM_CLOCK_SYSTEMCLOCK;	/* div4 clk*//*FTM2 use system clock*/
	// FTM2使用系统时钟
	/* Enable Channle 0*/
	/* Enable channel 0 interrupt */
	/* Channel as Output compare mode */
	/* Select interrupt frequency*/
	/* Interrupt every TIME_BASE_PERIOD/6.4 counts,  equal to every TIME_BASE_PERIOD */

	/* 以下部分配置FTM的通道0 */
	FTM_SetCountInitValue(FTM2 ,1);	// 设置FTM2的计数初始值为1
	FTM_SetModValue(FTM2 ,(TIME_BASE_PERIOD/(1000/(Get_FTM_PWT_Clock()*0.001/128))));/* Interrupt every TIME_BASE_PERIOD/6.4 counts,  equal to every TIME_BASE_PERIOD */
	/* 设置中断频率，每TIME_BASE_PERIOD/6.4计数，相当于每个TIME_BASE_PERIOD */
	FTM_Init(FTM2 ,&FTM_InitStructure);	// 初始化FTM2
	FTM_OverflowITCmd(FTM2 ,ENABLE);	// 使能FTM2的溢出中断
}

#ifdef MULTI_TIMER_MODE
   void lin_lld_timer_isr(l_u8 index)
   {
      /* Timeout for UART channel */
      lin_lld_uart_timeout(lin_virtual_ifc[index]);
      /*** Master task firing ***/
   }
#else /* Else MULTI_TIMER_MODE */
   void lin_lld_timer_isr(void)
   {
   #if LIN_MODE == _MASTER_MODE_
     l_u8 i;
     /* Timeout for UART channel */
     for(i=0; i<LIN_NUM_OF_IFCS; i++) {
       lin_lld_uart_timeout(lin_virtual_ifc[i]);
     }
     /*** Master task firing ***/
   #else
     lin_lld_uart_timeout();
   #endif /* End LIN_MODE == _MASTER_MODE_ */
   }
#endif /* End MULTI_TIMER_MODE */

/**
* @}
*/
