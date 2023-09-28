/**
  ******************************************************************************
  * @file     xl_crc.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about CRC firmware program 
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
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------*/
#include "xl_crc.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC CRC Module 
  * @brief CRC Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	

/** @defgroup CRC_Private_Functions
  * @{
  */ 	
		
/**
  * @brief  CRC恢复初始状态
  * @return 返回执行状态.
  */
void CRC_Deinit(void)
{	
	/* De-initialize the PMC module return to the default state. */
	CRC->CTRL = 0x00000000u;
	CRC->GPOLY = 0x00000000u;	
	CRC->INIT = 0xFFFFFFFFu;
}

/**
  * @brief  CRC初始化
  * @param CRC_InitStruct: CRC初始化配置结构体
  * @retval None
  */
void CRC_Init(const CRC_InitTypeDef *CRC_InitStruct)
{
	uint32_t tmpreg;
	
	/* configure the register. */
	/* Get the CTRL Register. */
	tmpreg = CRC->CTRL;
	/* clear the CTRL bit*/
	tmpreg &= ~(CRC_CTRL_TOT_MASK | CRC_CTRL_TCRC_MASK | CRC_CTRL_T16_MASK | CRC_CTRL_INV_MASK);
	/* set CRC control register */
	tmpreg |= ((((uint32_t)CRC_InitStruct->CRC_WriteTranspose << CRC_CTRL_TOT_SHIFT) & CRC_CTRL_TOT_MASK) |\
						(((uint32_t)CRC_InitStruct->CRC_DataWidth << CRC_CTRL_TCRC_SHIFT) & CRC_CTRL_TCRC_MASK)|\
	          (((uint32_t)CRC_InitStruct->CRC_Transpose16Only << CRC_CTRL_T16_SHIFT) & CRC_CTRL_T16_MASK) |\
						(((uint32_t)CRC_InitStruct->CRC_DataOutInvert << CRC_CTRL_INV_SHIFT) & CRC_CTRL_INV_MASK));
	

	/* Write to CRC CTRL */
	CRC->CTRL = tmpreg ;
	
	if(CRC_InitStruct->CRC_DataWidth	==	CRC_Width32Bits)
	{
		/*  set 32-bit CRC Polynomial register */
		CRC->GPOLY = (uint32_t)(CRC_InitStruct->CRC_PolyData);
	}
	else
	{
		/*  set 16-bit CRC Polynomial register */
		CRC->GPOLY=(uint16_t)(CRC_InitStruct->CRC_PolyData);
	}
}

/**
  * @brief  CRC 16位模计算.
  * @param  InitValue: 初始值
  * @param  *msg:  计算的数据
  * @param  SizeBytes:  计算的长度
  * @return 返回CRC16位数据计算结果.
  */
uint16_t CRC_Cal16(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes)
{
	uint16_t data_out;
	uint32_t i;

	/* init value set */
	CRC->INIT = InitValue;
	CRC->CTRL |= CRC_CTRL_INIT_MASK;

  /* Wait for calculation completion */
	for(i=0; i<SizeBytes; i++)
	{
		CRC->DATAIN = msg[i];
		CRC->CTRL |= CRC_CTRL_CALC_MASK;			
	}
	
	if((CRC->CTRL & CRC_CTRL_T16_MASK) == CRC_CTRL_T16_MASK)
	{
		/* read DATAOUT low 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT);
	}
	else if((CRC->CTRL & 0x00000100u) != 0x00000100u)
	{
		/* read DATAOUT low 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT);
	}
	else
	{
		/* read DATAOUT high 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT >> 16u);		
	}

	return(data_out);
}

/**
  * @brief  CRC 16位模快速计算.
  * @param  InitValue: 初始值
  * @param  *msg:  计算的数据
  * @param  SizeBytes:  计算的长度
  * @return 返回CRC16位数据计算结果.
  */
uint16_t CRC_Cal16_Fast(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes)
{
	uint16_t data_out;
	uint32_t i;


	uint32_t temp;

	
	uint16_t integer4=0;
	uint16_t integer8=0;
	uint16_t integer16=0;
	uint16_t integer32=0;
	
	uint16_t integer4_1=0;
	uint16_t integer8_1=0;
	uint16_t integer16_1=0;
	uint16_t integer32_1=0;
	
	uint8_t remainder32=0;
	
	temp = CRC->CTRL;
	temp |= CRC_CTRL_INIT_MASK;
	
	
	/* init value set */
	CRC->INIT = InitValue;
	CRC->CTRL |= CRC_CTRL_INIT_MASK;
	
	integer32 = SizeBytes>>5;
	integer32_1 = integer32<<5;
	remainder32 = SizeBytes-integer32_1;
	
	integer16 = remainder32>>4;
	integer16_1 = integer16<<4;
	remainder32 = remainder32-integer16_1;
	
	integer8 = remainder32>>3;
	integer8_1 = integer8<<3;
	remainder32 = remainder32-integer8_1;
	
	integer4 = remainder32>>2;
	integer4_1 = integer4<<2;
	remainder32 = integer32_1 + integer16_1 + integer8_1 + integer4_1;
	
	temp = CRC->CTRL;
	temp |= CRC_CTRL_CALC_MASK;
	
	for(i=0;i<integer32;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer16;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer8;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer4;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=remainder32;i<SizeBytes;i++)
	{
		CRC->DATAIN = msg[i++];
		CRC->CTRL = temp;
	}
  
	
	if((CRC->CTRL & CRC_CTRL_T16_MASK) == CRC_CTRL_T16_MASK)
	{
		/* read DATAOUT low 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT);
	}
	else if((CRC->CTRL & 0x00000100u) != 0x00000100u)
	{
		/* read DATAOUT low 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT);
	}
	else
	{
		/* read DATAOUT high 16 bits */		
		data_out=(uint16_t)(CRC->DATAOUT >> 16u);		
	}

	return(data_out);
}

/**
  * @brief  CRC 32位模计算.
  * @param  InitValue: 初始值
  * @param  *msg:  计算的数据
  * @param  SizeBytes:  计算的长度
  * @return 返回CRC32位数据计算结果.
  */
uint32_t CRC_Cal32(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes)
{
	uint32_t data_out;
	uint32_t i;
	/* init value set */
	CRC->INIT = InitValue;
	CRC->CTRL |= CRC_CTRL_INIT_MASK;

	/*Wait for calculation completion*/
	for(i=0; i<SizeBytes;i++)
	{
		CRC->DATAIN = msg[i];
	  CRC->CTRL |= CRC_CTRL_CALC_MASK;			
	}
	data_out=CRC->DATAOUT;
	return(data_out);
}

/**
  * @brief  CRC 32位模快速计算.
  * @param  InitValue: 初始值
  * @param  *msg:  计算的数据
  * @param  SizeBytes:  计算的长度
  * @return 返回CRC32位数据计算结果.
  */
uint32_t CRC_Cal32Fast(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes)
{
	uint32_t data_out;
	uint32_t i;
	uint32_t temp;

	
	uint16_t integer4=0;
	uint16_t integer8=0;
	uint16_t integer16=0;
	uint16_t integer32=0;
	
	uint16_t integer4_1=0;
	uint16_t integer8_1=0;
	uint16_t integer16_1=0;
	uint16_t integer32_1=0;
	
	uint8_t remainder32=0;
	
	/* init value set */
	CRC->INIT = InitValue;
	CRC->CTRL |= CRC_CTRL_INIT_MASK;
	
	integer32 = SizeBytes>>5;
	integer32_1 = integer32<<5;
	remainder32 = SizeBytes-integer32_1;
	
	integer16 = remainder32>>4;
	integer16_1 = integer16<<4;
	remainder32 = remainder32-integer16_1;
	
	integer8 = remainder32>>3;
	integer8_1 = integer8<<3;
	remainder32 = remainder32-integer8_1;
	
	integer4 = remainder32>>2;
	integer4_1 = integer4<<2;
	remainder32 = integer32_1 + integer16_1 + integer8_1 + integer4_1;
	
	temp = CRC->CTRL;
	temp |= CRC_CTRL_CALC_MASK;
	
	for(i=0;i<integer32;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer16;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer8;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=0;i<integer4;)
	{
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
			CRC->DATAIN = msg[i++];  CRC->CTRL = temp;  CRC->DATAIN = msg[i++];  CRC->CTRL = temp;
	}
	
	for(i=remainder32;i<SizeBytes;i++)
	{
		CRC->DATAIN = msg[i++];
		CRC->CTRL = temp;
	}

	data_out=CRC->DATAOUT;

	return(data_out);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */


/*******************************************************************************
 * EOF
 ******************************************************************************/

