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
	__IO uint32_t        CTRL;                     					/*!< ���ƼĴ���, offset:0x00*/
	__IO uint32_t        SERV;                      				/*!< ˢ�¼Ĵ���, offset:0x04*/
	__IO uint32_t        CMPL;                      				/*!< �����������޼Ĵ���, offset:0x08*/
	__IO uint32_t        CMPH;                      				/*!< �����������޼Ĵ���, offset:0x0C*/
	__IO uint32_t        CLKDIV;                   					/*!< ����ʱ�ӷ�Ƶ�Ĵ���, offset:0x0C*/
	__IO uint32_t        INTR_STATE;          					  	/*!< �ж�״̬�Ĵ���, offset:0x0C*/
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
 * @brief EWM ��ʼ���ṹ�嶨��
 */

typedef struct
{	
	uint8_t 	EWM_ClockSource;                  /*!< EWMʱ��Դ */
	uint8_t     EWM_ResetIntEnable;             /*!< EWM�ⲿ��λ�ж�ʹ�� */
	uint8_t     EWM_CMPLIntEnable;              /*!< CMPL�ж�ʹ�� */
	uint8_t     EWM_InputEnable;                /*!< EWM���빦��ʹ�� */
	uint8_t     EWM_InputLevel;                 /*!< EWM�����ƽ */
	uint8_t     EWM_Enable;                     /*!< EWMģ��ʹ�� */
	uint16_t 	EWM_CMPHValue;                    /*!< EWM�����������޼Ĵ���ֵ */
	uint16_t 	EWM_CMPLValue;                    /*!< EWM�����������޼Ĵ���ֵ */ 
	uint16_t 	EWM_Clock_Div;                    /*!< EWMʱ�ӷ�Ƶϵ�� */
}EWM_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup EWM_Exported_Constants EWMģ��ʹ�ò�������
  * @{
  */

/**
	* @defgroup EWM_Clock_Source   EWMʱ��Դ����
	* @{
	*/																				  
#define EWM_CLK_SEL_PCLK                  			((uint8_t)0x0)	        /*!< APBCLK */	
#define EWM_CLK_SEL_LPO_CLK                  		((uint8_t)0x1)	        /*!< �͹���ʱ��LPO */	
#define EWM_CLK_SEL_OSC_CLK                  		((uint8_t)0x2)		      /*!< �ⲿ����OSC */
#define EWM_CLK_SEL_ICS_IRCLK                  		((uint8_t)0x3)	      /*!< �ڲ���׼ʱ��IRC */

/**
	* @defgroup EWM_Input_Level   EWM�����ƽѡ��
	* @{
	*/
#define EWM_IN_LEVE_H       0x01                     /*!< EWM�����ƽΪ�� */                  
#define EWM_IN_LEVE_L       0x00                     /*!< EWM�����ƽΪ�� */

/**
	* @defgroup EWM_Interrupt_Status   EWM�ж�״̬
	* @{
	*/
#define EWM_CMPL_INT_STATUS      								0x01                 /*!< CMPL�ж�״̬ */
#define EWM_RESET_INT_STATUS      								0x02               /*!< ��λ�ж�״̬ */
#define EWM_LTCMPL_INT_STATUS      								0x04               /*!< ������δ����CMPL�ж�״̬ */
#define EWM_GTCMPH_INT_STATUS      								0x08               /*!< ����������CMPH�ж�״̬ */
#define EWM_OUT15CLOCK_INT_STATUS      							0x10             /*!< û����15�����������ˢ���ж�״̬ */
#define EWM_EXTERNAL_INT_STATUS      							0x20               /*!< �ⲿ�źŷ�����ת�ж�״̬ */
#define EWM_CLEAR_ALL_INT										0x3F                     /*!< ��������ж� */


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

