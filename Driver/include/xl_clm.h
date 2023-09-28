/**
  ******************************************************************************
  * @file     xl_clm.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the CLM
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
#ifndef __XL_CLM_H_
#define __XL_CLM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	/* Register define ------------------------------------------------------------*/
#define CLM_CTRL_SCLK_SEL_MASK                       0x100u
#define CLM_CTRL_SCLK_SEL_SHIFT                      8

#define CLM_CTRL_CLMEN_MASK                       0xFFu
#define CLM_CTRL_CLMEN_SHIFT                      0

#define CLM_CLML_CLML_MASK                       0xFFFFu
#define CLM_CLML_CLML_SHIFT                      0

#define CLM_CLMH_CLMH_MASK                       0xFFFFu
#define CLM_CLMH_CLMH_SHIFT                      0

#define CLM_RSTF_RSTF_MASK                       0x1u
#define CLM_RSTF_RSTF_SHIFT                      0	
	
#define CLM_SCLK_LPO_CLK 		0x00u
#define CLM_SCLK_IRC_CLK 		0x01u

/** CLM - Register Layout Typedef */
typedef struct {
	__IO uint16_t        CTRL;                      /*!< 控制寄存器, offset:0x00*/
       uint16_t RESERVED_0;
	__IO uint16_t        CLML;                      /*!< 频率偏移下限设置寄存器, offset:0x04*/
	uint16_t RESERVED_1;
       __IO uint16_t        CLMH;                 /*!< 频率偏移上限设置寄存器, offset:0x08*/
       uint16_t RESERVED_2;
	__IO uint16_t        RSTF;                      /*!< 复位标志寄存器, offset:0x0C*/
       uint16_t RESERVED_3;
} CLM_Type;	
	
extern CLM_Type* CLMA;
extern CLM_Type* CLMB;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup CLM
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief CLM初始化结构体定义
  */
typedef struct
{
	uint16_t	CLM_SAMPLE_CLOCK;
	uint16_t 	CLM_CLMH;  
	uint16_t 	CLM_CLML;  
}CLM_InitTypeDef;

/* Exported constants --------------------------------------------------------*/  

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t CLM_Init(CLM_Type* CLMx, const CLM_InitTypeDef *CLM_InitStruct);
void CLM_EnableCmd(CLM_Type* CLMx);
void CLM_Set_CLML(CLM_Type* CLMx, uint16_t value);
void CLM_Set_CLMH(CLM_Type* CLMx, uint16_t value);
uint8_t CLM_GetResetFlag(const CLM_Type* CLMx);
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


