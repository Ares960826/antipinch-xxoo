/**
  ******************************************************************************
  * @file     xl_ewm.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the EWM
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
#ifndef XL_EWM_H_
#define XL_EWM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------*/	
#include "XL6600.h"
	
/* Register define ------------------------------------------------------------*/
#define EWM_CTRL_CLK_SEL_MASK                       		0x60u
#define EWM_CTRL_CLK_SEL_SHIFT                      		5
#define EWM_CTRL_INTREN_OUT_MASK                       		0x10u
#define EWM_CTRL_INTREN_OUT_SHIFT                      		4
#define EWM_CTRL_INTREN_CMPL_MASK                       	0x08u
#define EWM_CTRL_INTREN_CMPL_SHIFT                      	3
#define EWM_CTRL_INEN_MASK                       			0x04u
#define EWM_CTRL_INEN_SHIFT                      			2
#define EWM_CTRL_ASSIN_MASK                       			0x02u
#define EWM_CTRL_ASSIN_SHIFT                      			1
#define EWM_CTRL_ENABLE_MASK                       			0x01u
#define EWM_CTRL_ENABLE_SHIFT                      			0
	
#define EWM_SERV_SERV_MASK                       			0xFFu
#define EWM_SERV_SERV_SHIFT                      			0
	
#define EWM_CMPL_CMPL_MASK                       			0xFFFFu
#define EWM_CMPL_CMPL_SHIFT                      			0

#define EWM_CMPH_CMPH_MASK                       			0xFFFFu
#define EWM_CMPH_CMPH_SHIFT                      			0

#define EWM_CLKDIV_CLK_DIV_MASK                       		0xFFFFu
#define EWM_CLKDIV_CLK_DIV_SHIFT                      		0

#define EWM_INTR_STATE_RESET_MASK                       	0x02u
#define EWM_INTR_STATE_RESET_SHIFT                      	1
#define EWM_INTR_STATE_INT_MASK                       		0x01u
#define EWM_INTR_STATE_INT_SHIFT                      		0

/** EWM - Register Layout Typedef */
typedef struct {
	__IO uint32_t        CTRL;                     					/*!< 控制寄存器, offset:0x00*/
	__IO uint32_t        SERV;                      				/*!< 刷新寄存器, offset:0x04*/
	__IO uint32_t        CMPL;                      				/*!< 窗口设置下限寄存器, offset:0x08*/
	__IO uint32_t        CMPH;                      				/*!< 窗口设置上限寄存器, offset:0x0C*/
	__IO uint32_t        CLKDIV;                   					/*!< 计数时钟分频寄存器, offset:0x0C*/
	__IO uint32_t        INTR_STATE;          					  	/*!< 中断状态寄存器, offset:0x0C*/
} EWM_Type;
extern EWM_Type* 	EWM;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup EWM 
  * @{
  */


/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief EWM 初始化结构体定义
 */

typedef struct
{	
	uint8_t 	EWM_ClockSource;                  /*!< EWM时钟源 */
	uint8_t     EWM_ResetIntEnable;             /*!< EWM外部复位中断使能 */
	uint8_t     EWM_CMPLIntEnable;              /*!< CMPL中断使能 */
	uint8_t     EWM_InputEnable;                /*!< EWM输入功能使能 */
	uint8_t     EWM_InputLevel;                 /*!< EWM输入电平 */
	uint8_t     EWM_Enable;                     /*!< EWM模块使能 */
	uint16_t 	EWM_CMPHValue;                    /*!< EWM窗口设置上限寄存器值 */
	uint16_t 	EWM_CMPLValue;                    /*!< EWM窗口设置下限寄存器值 */ 
	uint16_t 	EWM_Clock_Div;                    /*!< EWM时钟分频系数 */
}EWM_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup EWM_Exported_Constants EWM模块使用参数定义
  * @{
  */

/**
	* @defgroup EWM_Clock_Source   EWM时钟源定义
	* @{
	*/																				  
#define EWM_CLK_SEL_PCLK                  			((uint8_t)0x0)	        /*!< APBCLK */	
#define EWM_CLK_SEL_LPO_CLK                  		((uint8_t)0x1)	        /*!< 低功耗时钟LPO */	
#define EWM_CLK_SEL_OSC_CLK                  		((uint8_t)0x2)		      /*!< 外部振荡器OSC */
#define EWM_CLK_SEL_ICS_IRCLK                  		((uint8_t)0x3)	      /*!< 内部基准时钟IRC */

/**
	* @defgroup EWM_Input_Level   EWM输入电平选择
	* @{
	*/
#define EWM_IN_LEVE_H       0x01                     /*!< EWM输入电平为高 */                  
#define EWM_IN_LEVE_L       0x00                     /*!< EWM输入电平为低 */

/**
	* @defgroup EWM_Interrupt_Status   EWM中断状态
	* @{
	*/
#define EWM_CMPL_INT_STATUS      								0x01                 /*!< CMPL中断状态 */
#define EWM_RESET_INT_STATUS      								0x02               /*!< 复位中断状态 */
#define EWM_LTCMPL_INT_STATUS      								0x04               /*!< 计数器未到达CMPL中断状态 */
#define EWM_GTCMPH_INT_STATUS      								0x08               /*!< 计数器到达CMPH中断状态 */
#define EWM_OUT15CLOCK_INT_STATUS      							0x10             /*!< 没有在15个周期内完成刷新中断状态 */
#define EWM_EXTERNAL_INT_STATUS      							0x20               /*!< 外部信号发生翻转中断状态 */
#define EWM_CLEAR_ALL_INT										0x3F                     /*!< 清除所有中断 */


/**
  * @}
  */
																						
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void EWM_Init(EWM_Type *EWMx,const EWM_InitTypeDef *EWM_InitStruct);
void EWM_UpdateServ(EWM_Type *EWMx);
uint8_t EWM_GetInterruptStatus(const EWM_Type *EWMx);
void EWM_ClearInterruptStatus(EWM_Type *EWMx,uint8_t EWM_InterruptStatusType);


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

