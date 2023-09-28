/**
  ******************************************************************************
  * @file     xl_ics.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the ICS 
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
#ifndef XL_ICS_H_
#define XL_ICS_H_

#ifdef __cplusplus
extern "C"{
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
/* Register define ------------------------------------------------------------*/
	
/* C1 Bit Fields */
#define ICS_C1_IREFSTEN_MASK                     0x1u
#define ICS_C1_IREFSTEN_SHIFT                    0u

#define ICS_C1_IRCLKEN_MASK                      0x2u
#define ICS_C1_IRCLKEN_SHIFT                     1u

#define ICS_C1_IREFS_MASK                        0x4u
#define ICS_C1_IREFS_SHIFT                       2u

#define ICS_C1_RDIV_MASK                         0x38u
#define ICS_C1_RDIV_SHIFT                        3u

#define ICS_C1_CLKS_MASK                         0xC0u
#define ICS_C1_CLKS_SHIFT                        6u

/* C2 Bit Fields */
#define ICS_C2_LP_MASK                           0x01u
#define ICS_C2_LP_SHIFT                          0u

#define ICS_C2_BDIV_MASK                         0xFEu
#define ICS_C2_BDIV_SHIFT                        1u

/* C3 Bit Fields */
#define ICS_C3_SCTRIM_MASK                       0xFFu
#define ICS_C3_SCTRIM_SHIFT                      0u

/* C4 Bit Fields */
#define ICS_C4_RDIV2_MASK                        0x1Cu
#define ICS_C4_RDIV2_SHIFT                       2u

#define ICS_C4_CME_MASK                          0x20u
#define ICS_C4_CME_SHIFT                         5u

#define ICS_C4_FLLSTEN_MASK                      0x40u
#define ICS_C4_FLLSTEN_SHIFT                     6u

#define ICS_C4_LOLIE_MASK                        0x80u
#define ICS_C4_LOLIE_SHIFT                       7u

/* S Bit Fields */
#define ICS_S_CLKST_MASK                         0xCu
#define ICS_S_CLKST_SHIFT                        2u

#define ICS_S_IREFST_MASK                        0x10u
#define ICS_S_IREFST_SHIFT                       4u

#define ICS_S_LOCK_MASK                          0x40u
#define ICS_S_LOCK_SHIFT                         6u

#define ICS_S_LOLS_MASK                          0x80u
#define ICS_S_LOLS_SHIFT                         7u

/* CFG Bit Fields */
#define ICS_CFG_FLLFSEL_MASK                     0x1u
#define ICS_CFG_FLLFSEL_SHIFT                    0u

#define ICS_CFG_IRCSEL_MASK                      0x2u
#define ICS_CFG_IRCSEL_SHIFT                     1u

#define ICS_CFG_WPROT_MASK                       0xFFFF0000u
#define ICS_CFG_WPROT_SHIFT                      16

/** ICS - Register Layout Typedef */
typedef struct {
  __IO uint8_t C1;                                 /*!< (1-226)16.3.1 ICS ���ƼĴ��� 1 (C1), offset: 0x0 */
  __IO uint8_t C2;                                 /*!< (1-227)16.3.2 ICS ���ƼĴ��� 2 (C2), offset: 0x1 */
  __IO uint8_t C3;                                 /*!< ICS���ƼĴ���3, offset: 0x2 */
  __IO uint8_t C4;                                 /*!< ICS���ƼĴ���4, offset: 0x3 */
  __IO uint8_t S;                                  /*!< (1-230)16.3.5 ICS ״̬�Ĵ���(S), offset: 0x4 */
	     uint8_t RESERVED_0[3];
  __IO uint32_t CFG;                               /*!< (1-232)16.3.6 ICS ʱ�����üĴ���(CFG), offset: 0x8 */
	__IO uint32_t TRIM_EN;                           /*!< ICSʱ���޵�ʹ�ܼĴ���, offset: 0xC */
} ICS_Type;
extern ICS_Type* ICS;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup ICS 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup ICS_Exported_Constants ACMPģ��ʹ�ò�������
  * @{
  */ 	

/** @defgroup Clocks_SourceSelect Clocksʱ��Դѡ��
  * @{
  */
#define ICS_CLOCKS_FLL           						((uint8_t)0x00)   /*!< ѡ��FLLΪʱ��Դ��� */
#define ICS_CLOCKS_IRC           						((uint8_t)0x01)   /*!< ѡ��IRCΪʱ��Դ��� */
#define ICS_CLOCKS_OSC           						((uint8_t)0x02)   /*!< ѡ��OSCΪʱ��Դ��� */
#define ICS_CLOCKS_RESERVED        					((uint8_t)0x03)   /*!< ʱ��Դ����*/
/**
  * @}
  */


/** @defgroup Clocks_BaseDivider Clocksʱ��Դ��׼��Ƶ
  * @{
  */
#define ICS_RDIV_1or32         							((uint8_t)0x00)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ1  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ32 */
#define ICS_RDIV_2or64           						((uint8_t)0x01)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ2  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ64 */
#define ICS_RDIV_4or128           					((uint8_t)0x02)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ4  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ128 */
#define ICS_RDIV_8or256        							((uint8_t)0x03)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ8  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ256 */
#define ICS_RDIV_16or512           					((uint8_t)0x04)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ16  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ512 */
#define ICS_RDIV_32or1024        						((uint8_t)0x05)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ32  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ1024 */
#define ICS_RDIV_64           							((uint8_t)0x06)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ64  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ���� */
#define ICS_RDIV_128        								((uint8_t)0x07)   /*!< Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ128  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ���� */													 */
/**
  * @}
  */

/** @defgroup Clocks_BaseDivider2 Clocksʱ��Դ��׼��Ƶ
  * @{
  */
#define ICS_RDIV2_1         							 ((uint8_t)0x00)   /*!< 1��Ƶ */
#define ICS_RDIV2_2          							 ((uint8_t)0x01)   /*!< 2��Ƶ */
#define ICS_RDIV2_3           						 ((uint8_t)0x02)   /*!< 3��Ƶ */
#define ICS_RDIV2_4       								 ((uint8_t)0x03)   /*!< 4��Ƶ */
#define ICS_RDIV2_5           						 ((uint8_t)0x04)   /*!< 5��Ƶ */
#define ICS_RDIV2_6        								 ((uint8_t)0x05)   /*!< 6��Ƶ */
#define ICS_RDIV2_7           						 ((uint8_t)0x06)   /*!< 7��Ƶ */
#define ICS_RDIV2_8        								 ((uint8_t)0x07)   /*!< 8��Ƶ */
/**
  * @}
  */

/** @defgroup FLL_ClocksSourceSelect FLLʱ��Դѡ��
  * @{
  */
#define ICS_IREFS_OSC         							((uint8_t)0x00)   /*!< ѡ��OSCΪFLLʱ��Դ */
#define ICS_IREFS_IRC           						((uint8_t)0x01)   /*!< ѡ��IRCΪFLLʱ��Դ */
/**
  * @}
  */


/** @defgroup ICS_ClockConfig �ڲ�ʱ��Դѡ��
  * @{
  */
#define ICS_IRC_50K         								((uint8_t)0x00u)   /*!< ѡ���ڲ�ʱ��ԴIRCƵ��Ϊ50k  */
#define ICS_IRC_37o5K           						((uint8_t)0x01u)   /*!< ѡ���ڲ�ʱ��ԴIRCƵ��Ϊ37.5k  */
/**
  * @}
  */


/** @defgroup FLL_MultiplierFactor FLL��Ƶϵ��ѡ��
  * @{
  */
#define ICS_FLLFACTOR_1280         					((uint8_t)0x00)   /*!< ѡ��Ƶ��FLLΪ1280 */
#define ICS_FLLFACTOR_1920           				((uint8_t)0x01)   /*!< ѡ��Ƶ��FLLΪ1920 */
/**
  * @}
  */
	
/** @defgroup ICS_Status ICS״̬
  * @{
  */
#define ICS_STATUS_LOSINGLOCK         				((uint8_t)0x80)   /*!< FLL��ʧ��״̬  */
#define ICS_STATUS_LOCK           						((uint8_t)0x40)   /*!< FLL������״̬  */
#define ICS_STATUS_IREF           						((uint8_t)0x10)   /*!< �ڲ���׼ʱ����Դ״̬ */
/**
  * @}
  */	
	
/** @defgroup ICS_ClocksModeStatus ʱ��ģʽ״̬
  * @{
  */
#define ICS_MODE_FLL           								((uint8_t)0x00)   /*!< ICSʱ��ģʽΪFLL���  */
#define ICS_MODE_IRC           								((uint8_t)0x01)   /*!< ICSʱ��ģʽΪIRC���  */
#define ICS_MODE_OSC           								((uint8_t)0x02)   /*!< ICSʱ��ģʽΪOSC���  */
#define ICS_MODE_RESERVED           					((uint8_t)0x03)   /*!< ICSʱ��ģʽ����  */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void ICS_DeInit(void);

void ICS_ClocksSelect(uint8_t Clksel);
void ICS_BaseDivider(uint8_t RDiv);
void ICS_BaseDivider2(uint8_t RDiv2);
void ICS_IREFSSelect(uint8_t FllSel);
void ICS_IRCEnableCmd(FunctionalState State);
void ICS_IREFStopEnableCmd(FunctionalState State);
void ICS_BusDivder(uint8_t BDiv);
uint8_t ICS_GetBusDivder(void);
void ICS_FllLPModeStopEnableCmd(FunctionalState State);
void ICS_LosingLockIntEnableCmd(FunctionalState State);
void ICS_FllStopModeCloseEnableCmd(FunctionalState State);
void ICS_ClockMonitorEnableCmd(FunctionalState State);
void ICS_IRCSelect(uint8_t IRCValue);
void ICS_FllFactorSelect(uint8_t FactorValue);
uint8_t ICS_GetStatus(uint8_t ICSStatus);
uint8_t ICS_GetClockMode(void);
uint8_t ICS_GetIRCFre(void);
uint8_t ICS_GetIREFSSelect(void);
uint8_t ICS_GetFLLMultiple(void);
uint8_t ICS_GetBaseDivider(void);
uint8_t ICS_GetBaseDivider2(void);
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
