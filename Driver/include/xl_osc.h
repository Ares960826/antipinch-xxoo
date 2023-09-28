/**
  ******************************************************************************
  * @file     xl_osc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the OSC 
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
#ifndef XL_OSC_H_
#define XL_OSC_H_

#ifdef __cplusplus
extern "C" {
#endif
	

/* Includes ------------------------------------------------------------------*/
#include "XL6600.h"

/* Register define ------------------------------------------------------------*/
#define OSC_CR_OSCINIT_MASK                      0x1u
#define OSC_CR_OSCINIT_SHIFT                     0u

#define OSC_CR_HGO_MASK                          0x2u
#define OSC_CR_HGO_SHIFT                         1u

#define OSC_CR_RANGE_MASK                        0x4u
#define OSC_CR_RANGE_SHIFT                       2u

#define OSC_CR_OSCOS_MASK                        0x10u
#define OSC_CR_OSCOS_SHIFT                       4u

#define OSC_CR_OSCSTEN_MASK                      0x20u
#define OSC_CR_OSCSTEN_SHIFT                     5u

#define OSC_CR_OSCEN_MASK                        0x80u
#define OSC_CR_OSCEN_SHIFT                       7u

/* TCR Bit Fields */
#define OSC_TCR_ECLK_MASK                        0x7FFFu
#define OSC_TCR_ECLK_SHIFT                       0u

#define OSC_TCR_CV_MASK                          0x8000u
#define OSC_TCR_CV_SHIFT                         15u

/** OSC - Register Layout Typedef
 * (1-239) �� 17 �� ������OSC��
 * (1-61) 3.6 ʱ��ģ�� - 3.6.2 OSC ����
 * (1-241) 17.5 �洢��ӳ��ͼĴ�������
 * 		-> (1-242)17.5.1 OSC ���ƼĴ��� (CR)
 * 		-> (1-243)17.5.2 OSC ��չʱ�����üĴ��� (TCR)*/
typedef struct {
	__IO uint32_t CR;                          /*!< OSC ���ƼĴ���, offset: 0x0 (1-242)17.5.1 OSC ���ƼĴ��� (CR)*/
	__IO uint32_t TCR;                         /*!< OSC ��չʱ����ƼĴ���, offset: 0x4 (1-243)17.5.2 OSC ��չʱ�����üĴ��� (TCR)*/
} OSC_Type;

extern  OSC_Type*	OSC;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup OSC 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief OSC��ʼ���ṹ�嶨��
  */ 
typedef struct 
{
		uint8_t   OSC_OutputSelect;                /*!< OSC ���ѡ�� */
		uint8_t   OSC_RangeSelect;                 /*!< Ƶ�ʷ�Χѡ�� */
		uint8_t   OSC_ModeSelect;                  /*!< ����������ѡ�� */
	
}OSC_InitTypeDef;

/** @defgroup OSC_Exported_Constants OSCģ��ʹ�ò�������
  * @{
  */

/** @defgroup OSC_OutSelect OSC���ѡ��
  * @{
  */
#define OSC_EXTERNAL_COLOCK          						((uint8_t)0x00)   /*!< ѡ���ⲿʱ��Դ        */
#define OSC_OSCCILLATOR_COLOR          					((uint8_t)0x10)   /*!< ѡ��OSCʱ��Դ */
/**
  * @}
  */

/** @defgroup OSC_RangeSelect OSCƵ�ʷ�Χѡ��
  * @{
  */
#define OSC_RANGE_LOW           								((uint8_t)0x00)   /*!< 32kHz */
#define OSC_RANGE_HIGH         									((uint8_t)0x04)   /*!< 4 to 24MHz */
/**
  * @}
  */
/** @defgroup OSC_WorkMode OSC����ģʽ
  * @{
  */
#define OSC_LP_MODE          										((uint8_t)0x00)   /*!< �͹���ģʽ */
#define OSC_HG_MODE        											((uint8_t)0x02)   /*!< ������ģʽ */
/**
  * @}
  */	

/** @defgroup OSC_InitResult OSC��ʼ�����
  * @{
  */
#define OSC_INITSTATUS_FAILED        						((uint8_t)0x00)       /*!< OSC ��ʼ��ʧ��      */
#define OSC_INITSTATUS_SUCESS        						((uint8_t)0x01)       /*!< OSC ��ʼ���ɹ�      */

/**
* @}
*/

/**
* @}
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void OSC_Deinit(void);
void OSC_Init(const OSC_InitTypeDef *OSC_InitStruct);
void OSC_EnableCmd(FunctionalState State);
void OSC_ModuleInStopModeCmd(FunctionalState NewState);
void OSC_SetExtTime(uint32_t ExpTime);
uint8_t OSC_GetInitStatus(void);
uint8_t OSC_GetRange(void);

#ifdef __cplusplus
}
#endif		
	
#endif   /*__XL_OSC_H__ */
/**
* @}
*/

/**
* @}
*/

