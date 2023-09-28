/**
  ******************************************************************************
  * @file     xl_acmp.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the ACMP
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
#ifndef __XL_ACMP_H__
#define __XL_ACMP_H__

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
/* Register define ------------------------------------------------------------*/

/* CS Bit Fields */
#define ACMP_CS_ACMOD_MASK                       0x3u
#define ACMP_CS_ACMOD_SHIFT                      0
#define ACMP_CS_ACOPE_MASK                       0x4u
#define ACMP_CS_ACOPE_SHIFT                      2
#define ACMP_CS_ACO_MASK                         0x8u
#define ACMP_CS_ACO_SHIFT                        3
#define ACMP_CS_ACIE_MASK                        0x10u
#define ACMP_CS_ACIE_SHIFT                       4
#define ACMP_CS_ACF_MASK                         0x20u
#define ACMP_CS_ACF_SHIFT                        5
#define ACMP_CS_HYST_MASK                        0x40u
#define ACMP_CS_HYST_SHIFT                       6
#define ACMP_CS_ACE_MASK                         0x80u
#define ACMP_CS_ACE_SHIFT                        7
/* C0 Bit Fields */
#define ACMP_C0_ACNSEL_MASK                      0x3u
#define ACMP_C0_ACNSEL_SHIFT                     0
#define ACMP_C0_ACPSEL_MASK                      0x30u
#define ACMP_C0_ACPSEL_SHIFT                     4
/* C1 Bit Fields */
#define ACMP_C1_DACVAL_MASK                      0x3Fu
#define ACMP_C1_DACVAL_SHIFT                     0
#define ACMP_C1_DACREF_MASK                      0x40u
#define ACMP_C1_DACREF_SHIFT                     6
#define ACMP_C1_DACEN_MASK                       0x80u
#define ACMP_C1_DACEN_SHIFT                      7
/* C2 Bit Fields */
#define ACMP_C2_ACIPE_MASK                       0x7u
#define ACMP_C2_ACIPE_SHIFT                      0

/** ACMP - Register Layout Typedef */
typedef struct {
  __IO uint8_t CS;                                 /*!< ACMP控制和状态寄存器, offset: 0x0 */
  __IO uint8_t C0;                                 /*!< ACMP控制寄存器0, offset: 0x1 */
  __IO uint8_t C1;                                 /*!< ACMP控制寄存器1, offset: 0x2 */
  __IO uint8_t C2;                                 /*!< ACMP控制寄存器2, offset: 0x3 */
} ACMP_Type;
extern  ACMP_Type* ACMP0;
extern  ACMP_Type* ACMP1;


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup ACMP 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief ACMP 初始化结构体定义
 */
typedef struct
{
	FunctionalState ACMP_DACEN;                /*!< 使能内部6位DAC */
	uint8_t ACMP_DACRefVoltage;                /*!< 为DAC选择参考电压 */
	uint8_t ACMP_DACValue;                     /*!< 为内部DAC设值 */

	uint8_t ACMP_HystMode;                     /*!< 模拟比较器迟滞选择 */  
	uint8_t ACMP_IntTrigMode;                  /*!< 使能中断触发 */

	uint8_t ACMP_InputP;                       /*!< 设置上升沿输入到比较器 */
	uint8_t ACMP_InputN;                       /*!< 设置下降沿输入到比较器 */

	uint8_t ACMP_InputPin;                     /*!< ACMP输入引脚使能 */
	
}ACMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup ACMP_Exported_Constants ACMP模块使用参数定义
  * @{
  */

/**
	* @defgroup ACMP_Hyst   ACMP模拟比较器迟滞选择
	* @{
	*/
#define ACMP_Hyst_20mv                0                  /*!< ACMP迟滞20mv */
#define ACMP_Hyst_30mv	              1                  /*!< ACMP迟滞30mv */
/**
  * @}
  */

/**
	* @defgroup ACMP_InterruptEdge_Seclect ACMP中断触发方式
	* @{
	*/
#define ACMP_Int_FallEdge             0                  /*!< ACMP中断在输出下降沿发生 */
#define	ACMP_Int_RiseEdge             1                  /*!< ACMP中断在输出上升沿发生 */
#define ACMP_Int_FallEdge_1           2                  /*!< ACMP中断在输出下降沿发生 */
#define ACMP_Int_FallorRiseEdge       3                  /*!< ACMP中断在输出下降沿或上升沿发生 */
/**
  * @}
  */

/**
	* @defgroup ACMP_PositiveChannel_Seclect  ACMP正极输入选择
	* @{
	*/
#define ACMP_Positive_EXT0            0                 /*!< 正输入外部基准0 */
#define	ACMP_Positive_EXT1            1                 /*!< 正输入外部基准1 */
#define	ACMP_Positive_EXT2            2                 /*!< 正输入外部基准2 */
#define	ACMP_Positive_DAC             3                 /*!< 正输入DAC输出 */
/**
  * @}
  */

/**
	* @defgroup ACMP_NegativeChannel_Seclect  ACMP负极输入选择
	* @{
	*/
#define	ACMP_Negative_EXT0            0                /*!< 负输入外部基准0 */
#define	ACMP_Negative_EXT1            1                /*!< 负输入外部基准1 */
#define	ACMP_Negative_EXT2            2                /*!< 负输入外部基准2 */
#define	ACMP_Negative_DAC             3                /*!< 负输入DAC输出 */
/**
  * @}
  */

/**
	* @defgroup ACMP_DAC_Reference_Seclect ACMP的DAC参考电压选择
	* @{
	*/
#define  ACMP_DACRef_BANDGAP          0               /*!< DAC选择带隙基准作为基准 */
#define  ACMP_DACRef_VDDA             1               /*!< DAC选择VDDA作为基准 */
/**
  * @}
  */

/**
	* @defgroup ACMP_Channel_Seclect ACMP的通道选择
	* @{
	*/
#define ACMP_INNUll                   0                /*!< ACMP外部输出引脚禁用 */
#define	ACMP_IN0                      1                /*!< ACMP外部输出引脚0 */
#define	ACMP_IN1                      2                /*!< ACMP外部输出引脚1 */
#define	ACMP_IN1IN0                   3                /*!< ACMP外部输出引脚0和1 */
#define	ACMP_IN2                      4                /*!< ACMP外部输出引脚2 */
#define	ACMP_IN2IN0                   5                /*!< ACMP外部输出引脚0和2 */
#define	ACMP_IN2IN1                   6                /*!< ACMP外部输出引脚1和2 */
#define	ACMP_IN2IN1IN0                7                /*!< ACMP外部输出引脚0、1和2 */
/**
  * @}
  */
																						
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void ACMP_DeInit(ACMP_Type *ACMPx);
void ACMP_Init(ACMP_Type *ACMPx,const ACMP_InitTypeDef *ACMP_InitStruct);
void ACMP_EnableCmd(ACMP_Type *ACMPx,FunctionalState NewState);
void ACMP_InterruptEn(ACMP_Type *ACMPx,FunctionalState NewState);
void ACMP_OutputPinEn(ACMP_Type *ACMPx,FunctionalState NewState);
uint8_t ACMP_GetOutPutLogic(const ACMP_Type *ACMPx);
uint8_t ACMP_GetIntFlag(const ACMP_Type *ACMPx);
void ACMP_ClearIntFlag(ACMP_Type *ACMPx);

#ifdef __cplusplus
}
#endif

#endif /*__XL_ACMP_H__ */	

/**
  * @}
  */

/**
  * @}
  */

