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
  __IO uint32_t PDOR;                              /*!< 端口数据输出寄存器, offset: 0x0 */
  __O  uint32_t PSOR;                              /*!< (1-634)30.3.3 端口置位输出寄存器(PSOR), offset: 0x4 */
  __O  uint32_t PCOR;                              /*!< (1-635)30.3.4 端口清零输出寄存器(PCOR), offset: 0x8 */
  __O  uint32_t PTOR;                              /*!< 端口跳变输出寄存器, offset: 0xC */
  __I  uint32_t PDIR;                              /*!< (1-637)30.3.6 端口数据输入寄存器(PDIR), offset: 0x10 */
  __IO uint32_t PDDR;                              /*!< (1-637)30.3.6 端口数据输入寄存器(PDIR), offset: 0x14 */
  __IO uint32_t PIDR;                              /*!< (1-639)30.3.8 端口输入禁用寄存器(PIDR), offset: 0x18 */
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
/** @defgroup GPIO_Exported_Constants GPIO模块使用参数定义
  * @{
  * NOTE: (1-632)30.3.1 GPIO 寄存器位分配
  */
/** @defgroup GPIO_Direction_Seclect GPIO方向定义选择
  * @{
  */
typedef enum 
{	
		GPIO_Direction_Input		=0,				   /*!< 引脚配置为通用输入 */
		GPIO_Direction_Output,						   /*!< 引脚配置为通用输出 */
		GPIO_Direction_High_Z                          /*!< 引脚配置为高阻态 */
}GPIO_Direction_Mode;
/**
	* @}
	*/

/** @defgroup GPIO_OutputLevel_Seclect GPIO输出电平定义选择
  * @{
  */
typedef enum 
{
		GPIO_Output_Low		=0,							 /*!< 输出逻辑0 */
		GPIO_Output_High									 /*!< 输出逻辑1 */
}GPIO_Output_Level;
/**
	* @}
	*/
 
/** @defgroup GPIO_InputLevel_Seclect GPIO输入电平定义选择
  * @{
  */
typedef enum
{
		GPIO_Input_Low		=0,							 /*!< 输入逻辑0 */		
		GPIO_Input_High										  /*!< 输入逻辑1 */	
}GPIO_Input_Def;		
/**
	* @}
	*/

/** @defgroup GPIO_PINNum_Define GPIO引脚定义
  * @{
  */
/* in GPIOA register */
#define    GPIO_PTA0 			0       /*!< GPIO引脚PTA0 */
#define    GPIO_PTA1            1       /*!< GPIO引脚PTA1 */
#define    GPIO_PTA2            2       /*!< GPIO引脚PTA2 */
#define    GPIO_PTA3            3       /*!< GPIO引脚PTA3 */
#define    GPIO_PTA4            4       /*!< GPIO引脚PTA4 */
#define    GPIO_PTA5            5       /*!< GPIO引脚PTA5 */
#define    GPIO_PTA6            6       /*!< GPIO引脚PTA6 */
#define    GPIO_PTA7            7       /*!< GPIO引脚PTA7 */
#define    GPIO_PTB0            8       /*!< GPIO引脚PTB0 */
#define    GPIO_PTB1            9       /*!< GPIO引脚PTB1 */
#define    GPIO_PTB2            10      /*!< GPIO引脚PTB2 */
#define    GPIO_PTB3            11      /*!< GPIO引脚PTB3 */
#define    GPIO_PTB4            12      /*!< GPIO引脚PTB4 */
#define    GPIO_PTB5            13      /*!< GPIO引脚PTB5 */
#define    GPIO_PTB6            14      /*!< GPIO引脚PTB6 */
#define    GPIO_PTB7            15      /*!< GPIO引脚PTB7 */
#define    GPIO_PTC0            16      /*!< GPIO引脚PTC0 */
#define    GPIO_PTC1            17      /*!< GPIO引脚PTC1 */
#define    GPIO_PTC2            18      /*!< GPIO引脚PTC2 */
#define    GPIO_PTC3            19      /*!< GPIO引脚PTC3 */
#define    GPIO_PTC4            20      /*!< GPIO引脚PTC4 */
#define    GPIO_PTC5            21      /*!< GPIO引脚PTC5 */
#define    GPIO_PTC6            22      /*!< GPIO引脚PTC6 */
#define    GPIO_PTC7            23      /*!< GPIO引脚PTC7 */
#define    GPIO_PTD0            24      /*!< GPIO引脚PTD0 */
#define    GPIO_PTD1            25      /*!< GPIO引脚PTD1 */
#define    GPIO_PTD2            26      /*!< GPIO引脚PTD2 */
#define    GPIO_PTD3            27      /*!< GPIO引脚PTD3 */
#define    GPIO_PTD4            28      /*!< GPIO引脚PTD4 */
#define    GPIO_PTD5            29      /*!< GPIO引脚PTD5 */
#define    GPIO_PTD6            30      /*!< GPIO引脚PTD6 */
#define    GPIO_PTD7            31      /*!< GPIO引脚PTD7 */
/* in GPIOB register */
#define    GPIO_PTE0            32      /*!< GPIO引脚PTE0 */
#define    GPIO_PTE1            33      /*!< GPIO引脚PTE1 */
#define    GPIO_PTE2            34      /*!< GPIO引脚PTE2 */
#define    GPIO_PTE3            35      /*!< GPIO引脚PTE3 */
#define    GPIO_PTE4            36      /*!< GPIO引脚PTE4 */
#define    GPIO_PTE5            37      /*!< GPIO引脚PTE5 */
#define    GPIO_PTE6            38      /*!< GPIO引脚PTE6 */
#define    GPIO_PTE7            39      /*!< GPIO引脚PTE7 */
#define    GPIO_PTF0            40      /*!< GPIO引脚PTF0 */
#define    GPIO_PTF1            41      /*!< GPIO引脚PTF1 */
#define    GPIO_PTF2            42      /*!< GPIO引脚PTF2 */
#define    GPIO_PTF3            43      /*!< GPIO引脚PTF3 */
#define    GPIO_PTF4            44      /*!< GPIO引脚PTF4 */
#define    GPIO_PTF5            45      /*!< GPIO引脚PTF5 */
#define    GPIO_PTF6            46      /*!< GPIO引脚PTF6 */
#define    GPIO_PTF7            47      /*!< GPIO引脚PTF7 */
#define    GPIO_PTG0            48      /*!< GPIO引脚PTG0 */
#define    GPIO_PTG1            49      /*!< GPIO引脚PTG1 */
#define    GPIO_PTG2            50      /*!< GPIO引脚PTG2 */
#define    GPIO_PTG3            51      /*!< GPIO引脚PTG3 */
#define    GPIO_PTG4            52      /*!< GPIO引脚PTG4 */
#define    GPIO_PTG5            53      /*!< GPIO引脚PTG5 */
#define    GPIO_PTG6            54      /*!< GPIO引脚PTG6 */
#define    GPIO_PTG7            55      /*!< GPIO引脚PTG7 */
#define    GPIO_PTH0            56      /*!< GPIO引脚PTH0 */
#define    GPIO_PTH1            57      /*!< GPIO引脚PTH1 */
#define    GPIO_PTH2            58      /*!< GPIO引脚PTH2 */
#define    GPIO_PTH3            59      /*!< GPIO引脚PTH3 */
#define    GPIO_PTH4            60      /*!< GPIO引脚PTH4 */
#define    GPIO_PTH5            61      /*!< GPIO引脚PTH5 */
#define    GPIO_PTH6            62      /*!< GPIO引脚PTH6 */
#define    GPIO_PTH7            63      /*!< GPIO引脚PTH7 */
/* in GPIOC register */
#define    GPIO_PTI0            64      /*!< GPIO引脚PTI0 */
#define    GPIO_PTI1            65      /*!< GPIO引脚PTI1 */
#define    GPIO_PTI2            66      /*!< GPIO引脚PTI2 */
#define    GPIO_PTI3            67      /*!< GPIO引脚PTI3 */
#define    GPIO_PTI4            68      /*!< GPIO引脚PTI4 */
#define    GPIO_PTI5            69      /*!< GPIO引脚PTI5 */
#define    GPIO_PTI6            70      /*!< GPIO引脚PTI6 */
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

