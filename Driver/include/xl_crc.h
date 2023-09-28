/**
  ******************************************************************************
  * @file     xl_CRC.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the CRC
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
#ifndef XL_CRC_H__
#define XL_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"

/* Register define ------------------------------------------------------------*/
/* CTRL Bit Fields */
#define CRC_CTRL_CALC_MASK                       0x1u
#define CRC_CTRL_CALC_SHIFT                      0
#define CRC_CTRL_INIT_MASK                       0x2u
#define CRC_CTRL_INIT_SHIFT                      1
#define CRC_CTRL_TCRC_MASK                       0x4u
#define CRC_CTRL_TCRC_SHIFT                      2
#define CRC_CTRL_TOT_MASK                        0x300u
#define CRC_CTRL_TOT_SHIFT                       8
#define CRC_CTRL_INV_MASK                        0x800u
#define CRC_CTRL_INV_SHIFT                       11
#define CRC_CTRL_T16_MASK                        0x1000u
#define CRC_CTRL_T16_SHIFT                       12

/* GPOLY Bit Fields */
#define CRC_GPOLY_LOW_MASK                       0xFFFFu
#define CRC_GPOLY_LOW_SHIFT                      0
#define CRC_GPOLY_HIGH_MASK                      0xFFFF0000u
#define CRC_GPOLY_HIGH_SHIFT                     16

/* INIT Bit Fields */
#define CRC_INIT_LOW_MASK                        0xFFFFu
#define CRC_INIT_LOW_SHIFT                       0
#define CRC_INIT_HIGH_MASK                       0xFFFF0000u
#define CRC_INIT_HIGH_SHIFT                      16

/* DATAIN Bit Fields */
#define CRC_DATAIN_MASK                          0xFFu
#define CRC_DATAIN_SHIFT                         0

/* DATAOUT Bit Fields */
#define CRC_DATAOUT_LOW_MASK                     0xFFFFu
#define CRC_DATAOUT_LOW_SHIFT                    0
#define CRC_DATAOUT_HIGH_MASK                    0xFFFF0000u
#define CRC_DATAOUT_HIGH_SHIFT                   16

	
#define CRC_InitStatus_Failed           				((uint8_t)0x00)       /*!< CRC初始化失败 */
#define CRC_InitStatus_Success          				((uint8_t)0x01)	      /*!< CRC初始化成功 */

/** CRC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /*!< CRC配置寄存器, offset: 0x0 */
  __IO uint32_t GPOLY;                             /*!< CRC多项式寄存器, offset: 0x4 */ 	
  __IO uint32_t INIT;                              /*!< CRC初始值寄存器, offset: 0x8 */
  __O  uint32_t DATAIN;                            /*!< CRC数据输入寄存器, offset: 0x0C */
  __I  uint32_t DATAOUT;                           /*!< CRC数据输出寄存器, offset: 0x10 */
 	
} CRC_Type;
extern CRC_Type* CRC;	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/**
  * @brief  CRC 初始化结构体定义
  */
typedef struct
{
	uint32_t  CRC_PolyData;	                                    /*!< CRC计算所需的多项式值 */
	uint8_t   CRC_DataWidth;	                                  /*!< CRC协议宽度，0：16位CRC协议 ,1：32位CRC协议 */
	uint8_t   CRC_WriteTranspose;                               /*!< 写转置 */
	uint8_t 	CRC_Transpose16Only;		                          /*!< 仅在16位数据内转置 */
	uint8_t   CRC_DataOutInvert;	                              /*!< CRC计算结果取反 */

}CRC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup CRC_Exported_Constants CRC模块使用参数定义
  * @{
  */

/**
	* @defgroup CRC_Mode_Select CRC校验模式选择
	* @{
	*/
#define	CRC16_TRANSPOSE_IN32                   0              /*!< CRC16计算结果在32位数据内转置 */
#define	CRC16_TRANSPOSE_IN16                   1              /*!< CRC16计算结果仅在16位数据内转置 */
/**
  * @}
  */

/**
	* @defgroup CRC_OutData_Invert CRC输出结果转置
	* @{
	*/
#define	CRC_DATAOUT_NoInvert                   0              /*!< CRC计算结果不取反 */
#define	CRC_DATAOUT_Invert                     1              /*!< CRC计算结果取反 */
/**
  * @}
  */
	
/**
	* @defgroup CRC_Data_Transpose CRC数据翻转
	* @{
	*/
#define	CRC_NoTranspose                  			0                    /*!< 正常输出CRC结果，不进行转置 */
#define	CRC_TransposeBytes               			1                    /*!< 仅字节转置；字节中的位不转置 */
#define	CRC_TransposeBits                			2                    /*!< 字节中的位转置；字节不转置 */
#define	CRC_TransposeBoth                			3                    /*!< 字节中的位和字节均转置 */
/**
  * @}
  */
	
/**
	* @defgroup CRC_Data_Width CRC数据校验宽度
	* @{
	*/
#define	CRC_Width16Bits	                  		0u                   /*!< 16位CRC协议 */
#define	CRC_Width32Bits                   		1u                   /*!< 32位CRC协议 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void CRC_Deinit(void);
void CRC_Init(const CRC_InitTypeDef * CRC_InitStruct);
uint16_t CRC_Cal16(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes);
uint16_t CRC_Cal16_Fast(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes);
uint32_t CRC_Cal32(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes);
uint32_t CRC_Cal32Fast(uint32_t InitValue, const uint8_t *msg, uint32_t SizeBytes);
	
#ifdef __cplusplus
}
#endif

#endif /*__XL_CRC_H__ */	
/**
  * @}
  */

/**
  * @}
  */

