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
  __IO uint8_t CS;                                 /*!< ACMP���ƺ�״̬�Ĵ���, offset: 0x0 */
  __IO uint8_t C0;                                 /*!< ACMP���ƼĴ���0, offset: 0x1 */
  __IO uint8_t C1;                                 /*!< ACMP���ƼĴ���1, offset: 0x2 */
  __IO uint8_t C2;                                 /*!< ACMP���ƼĴ���2, offset: 0x3 */
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
 * @brief ACMP ��ʼ���ṹ�嶨��
 */
typedef struct
{
	FunctionalState ACMP_DACEN;                /*!< ʹ���ڲ�6λDAC */
	uint8_t ACMP_DACRefVoltage;                /*!< ΪDACѡ��ο���ѹ */
	uint8_t ACMP_DACValue;                     /*!< Ϊ�ڲ�DAC��ֵ */

	uint8_t ACMP_HystMode;                     /*!< ģ��Ƚ�������ѡ�� */  
	uint8_t ACMP_IntTrigMode;                  /*!< ʹ���жϴ��� */

	uint8_t ACMP_InputP;                       /*!< �������������뵽�Ƚ��� */
	uint8_t ACMP_InputN;                       /*!< �����½������뵽�Ƚ��� */

	uint8_t ACMP_InputPin;                     /*!< ACMP��������ʹ�� */
	
}ACMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup ACMP_Exported_Constants ACMPģ��ʹ�ò�������
  * @{
  */

/**
	* @defgroup ACMP_Hyst   ACMPģ��Ƚ�������ѡ��
	* @{
	*/
#define ACMP_Hyst_20mv                0                  /*!< ACMP����20mv */
#define ACMP_Hyst_30mv	              1                  /*!< ACMP����30mv */
/**
  * @}
  */

/**
	* @defgroup ACMP_InterruptEdge_Seclect ACMP�жϴ�����ʽ
	* @{
	*/
#define ACMP_Int_FallEdge             0                  /*!< ACMP�ж�������½��ط��� */
#define	ACMP_Int_RiseEdge             1                  /*!< ACMP�ж�����������ط��� */
#define ACMP_Int_FallEdge_1           2                  /*!< ACMP�ж�������½��ط��� */
#define ACMP_Int_FallorRiseEdge       3                  /*!< ACMP�ж�������½��ػ������ط��� */
/**
  * @}
  */

/**
	* @defgroup ACMP_PositiveChannel_Seclect  ACMP��������ѡ��
	* @{
	*/
#define ACMP_Positive_EXT0            0                 /*!< �������ⲿ��׼0 */
#define	ACMP_Positive_EXT1            1                 /*!< �������ⲿ��׼1 */
#define	ACMP_Positive_EXT2            2                 /*!< �������ⲿ��׼2 */
#define	ACMP_Positive_DAC             3                 /*!< ������DAC��� */
/**
  * @}
  */

/**
	* @defgroup ACMP_NegativeChannel_Seclect  ACMP��������ѡ��
	* @{
	*/
#define	ACMP_Negative_EXT0            0                /*!< �������ⲿ��׼0 */
#define	ACMP_Negative_EXT1            1                /*!< �������ⲿ��׼1 */
#define	ACMP_Negative_EXT2            2                /*!< �������ⲿ��׼2 */
#define	ACMP_Negative_DAC             3                /*!< ������DAC��� */
/**
  * @}
  */

/**
	* @defgroup ACMP_DAC_Reference_Seclect ACMP��DAC�ο���ѹѡ��
	* @{
	*/
#define  ACMP_DACRef_BANDGAP          0               /*!< DACѡ���϶��׼��Ϊ��׼ */
#define  ACMP_DACRef_VDDA             1               /*!< DACѡ��VDDA��Ϊ��׼ */
/**
  * @}
  */

/**
	* @defgroup ACMP_Channel_Seclect ACMP��ͨ��ѡ��
	* @{
	*/
#define ACMP_INNUll                   0                /*!< ACMP�ⲿ������Ž��� */
#define	ACMP_IN0                      1                /*!< ACMP�ⲿ�������0 */
#define	ACMP_IN1                      2                /*!< ACMP�ⲿ�������1 */
#define	ACMP_IN1IN0                   3                /*!< ACMP�ⲿ�������0��1 */
#define	ACMP_IN2                      4                /*!< ACMP�ⲿ�������2 */
#define	ACMP_IN2IN0                   5                /*!< ACMP�ⲿ�������0��2 */
#define	ACMP_IN2IN1                   6                /*!< ACMP�ⲿ�������1��2 */
#define	ACMP_IN2IN1IN0                7                /*!< ACMP�ⲿ�������0��1��2 */
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

