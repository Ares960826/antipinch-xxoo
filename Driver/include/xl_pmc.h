/**
  ******************************************************************************
  * @file     xl_pmc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the PMC 
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
#ifndef __XL_PMC_H__
#define __XL_PMC_H__

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/

/* SPMSC Bit Fields */
#define PMC_SPMSC_LVDE_MASK                     0x4u
#define PMC_SPMSC_LVDE_SHIFT                    2
#define PMC_SPMSC_LVDSE_MASK                    0x8u
#define PMC_SPMSC_LVDSE_SHIFT                   3
#define PMC_SPMSC_LVDRE_MASK                    0x10u
#define PMC_SPMSC_LVDRE_SHIFT                   4
#define PMC_SPMSC_LVWIE_MASK                    0x20u
#define PMC_SPMSC_LVWIE_SHIFT                   5
#define PMC_SPMSC_LVWACK_MASK                   0x40u
#define PMC_SPMSC_LVWACK_SHIFT                  6
#define PMC_SPMSC_LVWF_MASK                     0x80u
#define PMC_SPMSC_LVWF_SHIFT                    7
#define PMC_SPMSC_LVWV_MASK                     0x3000u
#define PMC_SPMSC_LVWV_SHIFT                    12
#define PMC_SPMSC_LVDV_MASK                     0x4000u
#define PMC_SPMSC_LVDV_SHIFT                    14
	
/** PMC - Register Layout Typedef */
typedef struct 
{
  __IO uint32_t SPMSC;                             /*!< ϵͳ��Դ����״̬�Ϳ��ƼĴ���, offset: 0x0 */
} PMC_Type;
extern PMC_Type* PMC;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup PMC 
  * @{
  */


/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief PMC��ʼ���ṹ�嶨��
  */
typedef struct  
{
	uint8_t PMC_LVWIntEnable;                       /*!< ʹ�� LVWF ��Ӳ���ж����� */
	uint8_t PMC_LVDRstEnable;                       /*!< ʹ�ܵ͵�ѹ�������Ӳ����λ */
	uint8_t PMC_LVDStopEnable;                      /*!< ��ѹ����� Stop ģʽ�µ�ʹ��            */
	uint8_t PMC_LVDectEnable;                       /*!< ��ѹ���ʹ�� */
	uint8_t PMC_lvdvselect;                                  /*!< ��ѹ����ѹѡ�� */
	uint8_t PMC_lvwvselect;                                  /*!< ��ѹ������ѹѡ�� */
}PMC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup PMC_Exported_Constants PMCģ��ʹ�ò�������
  * @{
  */

/** @defgroup PMC_Mode_Seclect PMCģʽѡ����
  * @{
  */
#define PMC_ModeRun                     0                   /*!< runģʽ */
#define PMC_ModeWait                    1                   /*!< waitģʽ */
#define PMC_ModeStop4                   2                   /*!< ʹ��Stopģʽ�µ�ѹ��� */
#define PMC_ModeStop3                   3                   /*!< ʧ��Stopģʽ�µ�ѹ��� */
/**
	* @}
	*/

/** @defgroup Low-Voltage_Detect_Voltage_Select PMC�͵�ѹ��ⶨ��
  * @{
  */
#define	PMC_LVDV_LowTrip                0                /*!< ѡ��͵�ƽ����� */
#define	PMC_LVDV_HighTrip               1                /*!< ѡ��ߵ�ƽ����� */
/**
	* @}
	*/
	

/** @defgroup Low-Voltage_Warning_Voltage_Select PMC�͵�ѹ����
  * @{
  */
#define	PMC_LVWV_LowTrip                0               /*!< ѡ��͵�ƽ����� */
#define	PMC_LVWV_Mid1Trip               1               /*!< ѡ���м��ƽ1 ����� */
#define	PMC_LVWV_Mid2Trip               2               /*!< ѡ���м��ƽ2 ����� */
#define	PMC_LVWV_HighTrip               3               /*!< ѡ��ߵ�ƽ����� */
/**
	* @}
	*/	

/**
	* @}
	*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void PMC_Deinit(void);
void PMC_Init(const PMC_InitTypeDef *PMC_InitStruct);
void PMC_SetMode(uint8_t u8PmcMode);
FlagStatus PMC_GetLVWFlag(void);
void PMC_ClrLVWFlag(void);

#ifdef __cplusplus
}
#endif

#endif /*__XL_PMC_H__ */	
/**
  * @}
  */

/**
  * @}
  */
