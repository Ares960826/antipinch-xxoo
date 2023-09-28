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
* @file      bsp/UART/lin_isr.c
*
* @author    FPT Software
*
* @brief     Interrupt service routine used in LIN driver
*
******************************************************************************/

/******************************************************************************
 *
 * History:
 *
 * 20140422		v1.0	First version for KEA family support
 *
 *****************************************************************************/

#include "lin_hw_cfg.h"
#include "lin_lld_timesrv.h"
#include "lin_lld_uart.h"
#include "xl_ftm.h"
#include "system_xl6600.h"
#include "xl_irq.h"
#include "complier_sw.h"

  /**********************************************************************************************
* Local functions
**********************************************************************************************/
#if _UART0_==1
void UART0_IRQHandler ();
  /***********************************************************************************************
  *
  * @brief    UART2_SCI2_IRQHandler - Uart1 reception interrupt, calls the user defined callback function
  * @param    none
  * @return   none
  *
  ************************************************************************************************/
#ifndef SIMDATA_OUT
  void UART0_IRQHandler ()
  {
#if (LIN_MODE == _MASTER_MODE_)
	  lin_lld_uart_rx_isr(UART0);
#else
	  lin_lld_uart_rx_isr();
#endif /* (LIN_MODE == _MASTER_MODE_) */

  }
#endif /*end _UART0_==1*/
#endif

#if _UART1_==1
void UART1_IRQHandler ();
  /***********************************************************************************************
  *
  * @brief    UART2_SCI2_IRQHandler - Uart1 reception interrupt, calls the user defined callback function
  * @param    none
  * @return   none
  *
  ************************************************************************************************/
  void UART1_IRQHandler ()
  {
#if (LIN_MODE == _MASTER_MODE_)
	  lin_lld_uart_rx_isr(UART1);
#else
	  lin_lld_uart_rx_isr();
#endif /* (LIN_MODE == _MASTER_MODE_) */

  }
#endif /*end _UART1_==1*/


#if _UART2_==1
void UART2_IRQHandler ();
  /***********************************************************************************************
  *
  * @brief    UART2_SCI2_IRQHandler - Uart1 reception interrupt, calls the user defined callback function
  * @param    none
  * @return   none
  *
  ************************************************************************************************/
  void UART2_IRQHandler ()
  {
#if (LIN_MODE == _MASTER_MODE_)
	  lin_lld_uart_rx_isr(UART2);
#else
	  lin_lld_uart_rx_isr();
#endif /* (LIN_MODE == _MASTER_MODE_) */

  }
#endif /*end _UART2_==1*/



  /***********************************************************************************************
  *
  * @brief    FTM2_IRQHandler - Interrupt for FTM channels, clear flag, set new tiemout and execute callback
  * @param    none
  * @return   none
  *
  ************************************************************************************************/
void FTM2_IRQHandler();
void FTM2_IRQHandler()
  {

    if (FTM_GetOverFlowFlag(FTM2) )  /* If the CHF of the channel is equal to 0 */
  	{
    	FTM_ClrOverFlowFlag(FTM2);	 /* Read to clear flag */
  		  			/* Clear flag */
  		 	 	 	 	 	 	 	 	 	 	 /* Refresh interrupt period */
  		lin_lld_timer_isr();
  	}
  }

void LIN_WAKEUP_IRQ_HANDLE(void){
	if(IRQ_GetFlag(IRQ, LIN_WAKEUP_IRQ_N)){
		IRQ_InterruptEn(IRQ, LIN_WAKEUP_IRQ_N, DISABLE);
		IRQ_ClrFlag(IRQ, LIN_WAKEUP_IRQ_N);
	}

}
