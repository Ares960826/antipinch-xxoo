 /**
  ******************************************************************************
  * @file     xl_eeprom.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the EERPOM 
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
#ifndef __XL_EEPROM_H_
#define __XL_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "xl6600.h"
#include "xl_gpio.h"
#include "xl_port.h"
#include "xl_i2c.h"
#include "xl_nvic.h"
#include "xl_sim.h"
/* Register define ------------------------------------------------------------*/

/** EEPROM - Register Layout Typedef */
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup EEPROM_Exported_Constants EEPROM模块使用参数定义
  * @{
  */
#define USER_HARDWARE_OR_SOFTWARE  1u

#define EEPROM_BASE_ADDRESS  0x40000000u
/**
  * @}
  */


/** @defgroup EEPROM_WORK_SOFTWARE_PIN EEPROM软件工作模式Pin定义
  * @{
  */
#if (USER_HARDWARE_OR_SOFTWARE == 0u)
	#define  SET_SDA_INPUT()    {*((unsigned long *)0x40100054) &=  ~((uint32_t)1	<<	((uint8_t)GPIO_PTH3 - (uint8_t)32));  *((unsigned long *)0x40100058) &=  ~((uint32_t)1	<<	((uint8_t)GPIO_PTH3 - (uint8_t)32));}
	#define  SET_SDA_OUTPUT()   {*((unsigned long *)0x40100054) |=   ((uint32_t)1	<<	((uint8_t)GPIO_PTH3 - (uint8_t)32));  *((unsigned long *)0x40100058) &=  ~((uint32_t)1	<<	((uint8_t)GPIO_PTH3 - (uint8_t)32));}

#if defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__)
	#define I2C_SDA_H()  				{__asm volatile("cpsid i"); *((unsigned long *)0x40100044)  |= (1<<(GPIO_PTH3 -32));__asm volatile("cpsie i");}
	#define I2C_SDA_L()  				{__asm volatile("cpsid i"); *((unsigned long *)0x40100048)  |= (1<<(GPIO_PTH3 -32));__asm volatile("cpsie i");}
	#define I2C_SCK_H() 				{__asm volatile("cpsid i"); *((unsigned long *)0x40100044)  |= (1<<(GPIO_PTH4 -32));__asm volatile("cpsie i");}
	#define I2C_SCK_L() 				{__asm volatile("cpsid i"); *((unsigned long *)0x40100048)  |= (1<<(GPIO_PTH4 -32));__asm volatile("cpsie i");}
#elif defined(__ARMCC_VERSION) || defined(__CWCC__)
	#define I2C_SDA_H()  				{__disable_irq(); *((unsigned long *)0x40100044)  |= (1<<(GPIO_PTH3 -32));__enable_irq();}
	#define I2C_SDA_L()  				{__disable_irq(); *((unsigned long *)0x40100048)  |= (1<<(GPIO_PTH3 -32));__enable_irq();}
	#define I2C_SCK_H() 				{__disable_irq(); *((unsigned long *)0x40100044)  |= (1<<(GPIO_PTH4 -32));__enable_irq();}
	#define I2C_SCK_L() 				{__disable_irq(); *((unsigned long *)0x40100048)  |= (1<<(GPIO_PTH4 -32));__enable_irq();} 
#endif    
    
#endif
/**
  * @}
  */

/** @defgroup EEPROM_TIMER  EEPROM超时计数器定义
 * @{
 */
typedef struct
{
	uint8_t timer_start;
	uint32_t timer_cnt;
}Timer_Type;
/**
  * @}
  */

/**
	* @defgroup EEPROM_Status   EEPROM状态类型定义
	* @{
	*/
typedef enum
{
	EEPROM_OK = 0,
	EEPROM_SlaveID_TIMEOUT,
	EEPROM_ADDRESS_TIMEOUT,
	EEPROM_DATA_TIMEOUT,
}EEPROM_Status;
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void EEPROM_Init(uint32_t systemclk);
void EEPROM_DeInit(void);
void EEPROM_WriteProtectEn(FunctionalState NewState);
uint8_t EEPROM_WriteByte(uint32_t address,uint8_t data,uint32_t time);
EEPROM_Status EEPROM_WriteBuff(uint32_t address,const uint8_t *data,uint8_t lenght,uint32_t time);
EEPROM_Status EEPROM_WritePage(uint8_t page,const uint8_t *data,uint32_t time);
EEPROM_Status EEPROM_ReadByte(uint32_t address,uint8_t *data,uint32_t time);
EEPROM_Status EEPROM_ReadBuff(uint32_t address,uint8_t *data,uint16_t lenght,uint32_t time);

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
