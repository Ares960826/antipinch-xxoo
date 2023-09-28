/**
  ******************************************************************************
  * @file     xl_gpio.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the GPIO 
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
#ifndef __XL_GPIO_H_
#define __XL_GPIO_H_

#ifdef __cplusplus
entern "C"{
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR;                              /*!< �˿���������Ĵ���, offset: 0x0 */
  __O  uint32_t PSOR;                              /*!< (1-634)30.3.3 �˿���λ����Ĵ���(PSOR), offset: 0x4 */
  __O  uint32_t PCOR;                              /*!< (1-635)30.3.4 �˿���������Ĵ���(PCOR), offset: 0x8 */
  __O  uint32_t PTOR;                              /*!< �˿���������Ĵ���, offset: 0xC */
  __I  uint32_t PDIR;                              /*!< (1-637)30.3.6 �˿���������Ĵ���(PDIR), offset: 0x10 */
  __IO uint32_t PDDR;                              /*!< (1-637)30.3.6 �˿���������Ĵ���(PDIR), offset: 0x14 */
  __IO uint32_t PIDR;                              /*!< (1-639)30.3.8 �˿�������üĴ���(PIDR), offset: 0x18 */
} GPIO_Type;
extern GPIO_Type * GPIOA;
extern GPIO_Type * GPIOB;
extern GPIO_Type * GPIOC;
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO 
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIOģ��ʹ�ò�������
  * @{
  * NOTE: (1-632)30.3.1 GPIO �Ĵ���λ����
  */
/** @defgroup GPIO_Direction_Seclect GPIO������ѡ��
  * @{
  */
typedef enum 
{	
		GPIO_Direction_Input		=0,				   /*!< ��������Ϊͨ������ */
		GPIO_Direction_Output,						   /*!< ��������Ϊͨ����� */
		GPIO_Direction_High_Z                          /*!< ��������Ϊ����̬ */
}GPIO_Direction_Mode;
/**
	* @}
	*/

/** @defgroup GPIO_OutputLevel_Seclect GPIO�����ƽ����ѡ��
  * @{
  */
typedef enum 
{
		GPIO_Output_Low		=0,							 /*!< ����߼�0 */
		GPIO_Output_High									 /*!< ����߼�1 */
}GPIO_Output_Level;
/**
	* @}
	*/
 
/** @defgroup GPIO_InputLevel_Seclect GPIO�����ƽ����ѡ��
  * @{
  */
typedef enum
{
		GPIO_Input_Low		=0,							 /*!< �����߼�0 */		
		GPIO_Input_High										  /*!< �����߼�1 */	
}GPIO_Input_Def;		
/**
	* @}
	*/

/** @defgroup GPIO_PINNum_Define GPIO���Ŷ���
  * @{
  */
/* in GPIOA register */
#define    GPIO_PTA0 			0       /*!< GPIO����PTA0 */
#define    GPIO_PTA1            1       /*!< GPIO����PTA1 */
#define    GPIO_PTA2            2       /*!< GPIO����PTA2 */
#define    GPIO_PTA3            3       /*!< GPIO����PTA3 */
#define    GPIO_PTA4            4       /*!< GPIO����PTA4 */
#define    GPIO_PTA5            5       /*!< GPIO����PTA5 */
#define    GPIO_PTA6            6       /*!< GPIO����PTA6 */
#define    GPIO_PTA7            7       /*!< GPIO����PTA7 */
#define    GPIO_PTB0            8       /*!< GPIO����PTB0 */
#define    GPIO_PTB1            9       /*!< GPIO����PTB1 */
#define    GPIO_PTB2            10      /*!< GPIO����PTB2 */
#define    GPIO_PTB3            11      /*!< GPIO����PTB3 */
#define    GPIO_PTB4            12      /*!< GPIO����PTB4 */
#define    GPIO_PTB5            13      /*!< GPIO����PTB5 */
#define    GPIO_PTB6            14      /*!< GPIO����PTB6 */
#define    GPIO_PTB7            15      /*!< GPIO����PTB7 */
#define    GPIO_PTC0            16      /*!< GPIO����PTC0 */
#define    GPIO_PTC1            17      /*!< GPIO����PTC1 */
#define    GPIO_PTC2            18      /*!< GPIO����PTC2 */
#define    GPIO_PTC3            19      /*!< GPIO����PTC3 */
#define    GPIO_PTC4            20      /*!< GPIO����PTC4 */
#define    GPIO_PTC5            21      /*!< GPIO����PTC5 */
#define    GPIO_PTC6            22      /*!< GPIO����PTC6 */
#define    GPIO_PTC7            23      /*!< GPIO����PTC7 */
#define    GPIO_PTD0            24      /*!< GPIO����PTD0 */
#define    GPIO_PTD1            25      /*!< GPIO����PTD1 */
#define    GPIO_PTD2            26      /*!< GPIO����PTD2 */
#define    GPIO_PTD3            27      /*!< GPIO����PTD3 */
#define    GPIO_PTD4            28      /*!< GPIO����PTD4 */
#define    GPIO_PTD5            29      /*!< GPIO����PTD5 */
#define    GPIO_PTD6            30      /*!< GPIO����PTD6 */
#define    GPIO_PTD7            31      /*!< GPIO����PTD7 */
/* in GPIOB register */
#define    GPIO_PTE0            32      /*!< GPIO����PTE0 */
#define    GPIO_PTE1            33      /*!< GPIO����PTE1 */
#define    GPIO_PTE2            34      /*!< GPIO����PTE2 */
#define    GPIO_PTE3            35      /*!< GPIO����PTE3 */
#define    GPIO_PTE4            36      /*!< GPIO����PTE4 */
#define    GPIO_PTE5            37      /*!< GPIO����PTE5 */
#define    GPIO_PTE6            38      /*!< GPIO����PTE6 */
#define    GPIO_PTE7            39      /*!< GPIO����PTE7 */
#define    GPIO_PTF0            40      /*!< GPIO����PTF0 */
#define    GPIO_PTF1            41      /*!< GPIO����PTF1 */
#define    GPIO_PTF2            42      /*!< GPIO����PTF2 */
#define    GPIO_PTF3            43      /*!< GPIO����PTF3 */
#define    GPIO_PTF4            44      /*!< GPIO����PTF4 */
#define    GPIO_PTF5            45      /*!< GPIO����PTF5 */
#define    GPIO_PTF6            46      /*!< GPIO����PTF6 */
#define    GPIO_PTF7            47      /*!< GPIO����PTF7 */
#define    GPIO_PTG0            48      /*!< GPIO����PTG0 */
#define    GPIO_PTG1            49      /*!< GPIO����PTG1 */
#define    GPIO_PTG2            50      /*!< GPIO����PTG2 */
#define    GPIO_PTG3            51      /*!< GPIO����PTG3 */
#define    GPIO_PTG4            52      /*!< GPIO����PTG4 */
#define    GPIO_PTG5            53      /*!< GPIO����PTG5 */
#define    GPIO_PTG6            54      /*!< GPIO����PTG6 */
#define    GPIO_PTG7            55      /*!< GPIO����PTG7 */
#define    GPIO_PTH0            56      /*!< GPIO����PTH0 */
#define    GPIO_PTH1            57      /*!< GPIO����PTH1 */
#define    GPIO_PTH2            58      /*!< GPIO����PTH2 */
#define    GPIO_PTH3            59      /*!< GPIO����PTH3 */
#define    GPIO_PTH4            60      /*!< GPIO����PTH4 */
#define    GPIO_PTH5            61      /*!< GPIO����PTH5 */
#define    GPIO_PTH6            62      /*!< GPIO����PTH6 */
#define    GPIO_PTH7            63      /*!< GPIO����PTH7 */
/* in GPIOC register */
#define    GPIO_PTI0            64      /*!< GPIO����PTI0 */
#define    GPIO_PTI1            65      /*!< GPIO����PTI1 */
#define    GPIO_PTI2            66      /*!< GPIO����PTI2 */
#define    GPIO_PTI3            67      /*!< GPIO����PTI3 */
#define    GPIO_PTI4            68      /*!< GPIO����PTI4 */
#define    GPIO_PTI5            69      /*!< GPIO����PTI5 */
#define    GPIO_PTI6            70      /*!< GPIO����PTI6 */
/**
	* @}
	*/
	
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void GPIO_DeInit(GPIO_Type *GPIOx);
void GPIO_SetPinDir(uint8_t gpioPin,GPIO_Direction_Mode GPIO_Mode);
void GPIO_SetPinOutput(uint8_t gpioPin, GPIO_Output_Level Output);
void GPIO_TogglePin(uint8_t gpioPin);
void GPIO_SetPin(uint8_t gpioPin);
void GPIO_ClrPin(uint8_t gpioPin);
uint32_t GPIO_ReadReg(const GPIO_Type *GPIOx);
GPIO_Input_Def GPIO_ReadPin(uint8_t gpioPin);
GPIO_Direction_Mode GPIO_ReadPinDir(uint8_t gpioPin);
#ifdef __cplusplus
}
#endif


#endif			/*__XL_GPIO_H__ */
/**
  * @}
  */

/**
  * @}
  */

