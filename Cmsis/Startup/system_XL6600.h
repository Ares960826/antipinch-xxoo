/**
  ******************************************************************************
  * @file     system_xl6600.h
  * @author   xu.wang
  * @version  V3.0.0
  * @date     4-Jun-2019
  * @brief    This file contains all the functions prototypes for the system
  *           firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/	
#ifndef SYSTEM_XL6600_H_
#define SYSTEM_XL6600_H_                      /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include "typedef.h"


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */
	
/** @addtogroup system
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

	
/* Exported constants --------------------------------------------------------*/
	
	
typedef enum {
	SYS_CLK_OK = 0,
	OSC_INIT_ERROR = 1,
	OSC_DIV_ERROR = 2,
	ICS_STATUS_UNLOCK = 3,
	FLASH_INIT_ERROR = 4
}SYS_CLK_STATUS;	
	
/**
	* @defgroup OSC_CLOCK   OSC时钟和分频定义
	* @{
	*/
//#define OSC_CLOCK_HZ  	24000000
//#define OSC_RDIV  			512
/**
  * @}
  */
	
/**
  * @}
  */
																						
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void SystemInit (void);
SYS_CLK_STATUS SystemSetFEI(uint8_t ICS_IRCSel,uint8_t ICS_FLLFSel);
SYS_CLK_STATUS SystemSetFEE(uint32_t osc_clkfre, uint8_t ICS_FLLFSel, uint8_t osc_bdiv,uint8_t osc_bdiv2);
uint32_t SystemSetFBI(void);
void SystemSetFBILP(void);
void SystemSetFBE(uint32_t osc_clkfre);
void SystemSetFBELP(void);
uint32_t Get_ICSOUTClock(void);
uint32_t Get_SystemCoreClock(void);
uint32_t Get_FTM_PWT_Clock(void);
uint32_t Get_BusClock(void);
uint32_t Get_PeripheralClock(void);

#ifdef __cplusplus
}
#endif

#endif  
/**
  * @}
  */

/**
  * @}
  */


