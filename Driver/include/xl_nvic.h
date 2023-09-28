/**
  ******************************************************************************
  * @file     xl_nvic.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the NVIC
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
#ifndef __XL_NVIC_H__
#define __XL_NVIC_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ---------------------------------------------------------------*/
#include "xl6600.h"


#define SCB_AIRCR_PRIGROUP_Pos              8U                                            
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)               

	 
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup NVIC 
  * @{
  */
	 
/* Exported types ------------------------------------------------------------*/ 
/**
 * @brief NVIC ��ʼ���ṹ�嶨��
 */
typedef struct
{
  uint8_t NVIC_IRQChannel;                    /*!< �����ж�ͨ�� */

  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< IRQ�ж���ռʽ���ȼ�����Χ0��3 */

  uint8_t NVIC_IRQChannelSubPriority;         /*!< IRQ�ж������ȼ�����Χ0��3 */

  FunctionalState NVIC_IRQChannelCmd;         /*!< IRQͨ��ʹ�ܻ���ʧ��         */   
} NVIC_InitTypeDef;
 

/* Exported constants --------------------------------------------------------*/
/** @defgroup NVIC_Exported_Constants NVICģ��ʹ�ò�������
  * @{
  */
/** @defgroup Vector_Table_Base �����ж�������
  * @{
  */ 
#define AIRCR_VECTKEY_MASK    				((uint32_t)0x05FA0000)
#define NVIC_VectTab_RAM             	((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           	((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup System_Low_Power NVICϵͳ�͹��Ķ���
  * @{
  */
#define NVIC_LP_SEVONPEND            	((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            	((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          	((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup Preemption_Priority_Group NVIC�ж��鶨��
  * @{
  */
#define NVIC_PriorityGroup_0         	((uint32_t)0x700) /*!< 0λ��ռʽ���ȼ���4λ�����ȼ� */
#define NVIC_PriorityGroup_1         	((uint32_t)0x600) /*!< 1λ��ռʽ���ȼ���3λ�����ȼ� */
#define NVIC_PriorityGroup_2         	((uint32_t)0x500) /*!< 2λ��ռʽ���ȼ���2λ�����ȼ� */
#define NVIC_PriorityGroup_3         	((uint32_t)0x400) /*!< 3λ��ռʽ���ȼ���1λ�����ȼ� */
#define NVIC_PriorityGroup_4         	((uint32_t)0x300) /*!< 4λ��ռʽ���ȼ���0λ�����ȼ� */
/**
  * @}
  */

/** @defgroup SysTick_clock_source  Coreʱ��Դ
  * @{
  */
#define SysTick_CLKSource_HCLK_Div8    0xFFFFFFFBu
#define SysTick_CLKSource_HCLK         0x00000004u
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(const NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
#ifdef __cplusplus
}
#endif

#endif /* __XL_NVIC_H__ */
/**
  * @}
  */

/**
  * @}
  */


