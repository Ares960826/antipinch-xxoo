/**
  ******************************************************************************
  * @file     xl_spi.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the SPI 
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
#ifndef XL_SPI_H_
#define XL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/
/* CTRLR0 Bit Fields */
#define SPI_CTRLR0_DFS_MASK                    0xFu
#define SPI_CTRLR0_DFS_SHIFT                   0
#define SPI_CTRLR0_SCPH_MASK                   0x40u
#define SPI_CTRLR0_SCPH_SHIFT                  6
#define SPI_CTRLR0_SCPOL_MASK                  0x80u
#define SPI_CTRLR0_SCPOL_SHIFT                 7
#define SPI_CTRLR0_TMOD_MASK                   0x300u
#define SPI_CTRLR0_TMOD_SHIFT                  8
#define SPI_CTRLR0_SLVOE_MASK                  0x400u
#define SPI_CTRLR0_SLVOE_SHIFT                 10
#define SPI_CTRLR0_SRL_MASK                    0x800u
#define SPI_CTRLR0_SRL_SHIFT                   11
	
/* CTRLR1 Bit Fields */
#define SPI_CTRLR1_NDF_MASK                    0xFFFFu
#define SPI_CTRLR1_NDF_SHIFT                   0

/* SPIENR Bit Fields */      
#define SPI_SPIENR_SPIE_MASK                   0x1u
#define SPI_SPIENR_SPIE_SHIFT                  0

/* SER Bit Fields */
#define SPI_SER_SSEF_MASK                      0x1u
#define SPI_SER_SSEF_SHIFT                     0

/* BAUDR Bit Fields */
#define SPI_BAUDR_SCKDV_MASK                   0xFFFFu
#define SPI_BAUDR_SCKDV_SHIFT                  0

/* TXFTLR Bit Fields */
#define SPI_TXFTLR_TFTL_MASK                   0xFu
#define SPI_TXFTLR_TFTL_SHIFT                  0

/* RXFTLR Bit Fields */
#define SPI_RXFTLR_RFTL_MASK                   0xFu
#define SPI_RXFTLR_RFTL_SHIFT                  0

/* TXFLR Bit Fields */
#define SPI_TXFLR_TFL_MASK                     0x1Fu
#define SPI_TXFLR_TFL_SHIFT                    0

/* RXFLR Bit Fields */
#define SPI_RXFLR_RFL_MASK                     0x1Fu
#define SPI_RXFLR_RFL_SHIFT                    0

 /* SR Bit Fields */
#define SPI_SR_BUSY_MASK                       0x1u
#define SPI_SR_BUSY_SHIFT                      0
#define SPI_SR_TFNF_MASK                       0x2u
#define SPI_SR_TFNF_SHIFT                      1
#define SPI_SR_TFE_MASK                        0x4u
#define SPI_SR_TFE_SHIFT                       2
#define SPI_SR_RFNE_MASK                       0x8u
#define SPI_SR_RFNE_SHIFT                      3
#define SPI_SR_RFF_MASK                        0x10u
#define SPI_SR_RFF_SHIFT                       4
#define SPI_SR_TXE_MASK                        0x20u
#define SPI_SR_TXE_SHIFT                       5
#define SPI_SR_DCOL_MASK                       0x40u
#define SPI_SR_DCOL_SHIFT                      6

 /* IMR Bit Fields */
#define SPI_IMR_TXEIM_MASK                     0x1u
#define SPI_IMR_TXEIM_SHIFT                    0
#define SPI_IMR_TXOIM_MASK                     0x2u
#define SPI_IMR_TXOIM_SHIFT                    1
#define SPI_IMR_RXUIM_MASK                     0x4u
#define SPI_IMR_RXUIM_SHIFT                    2
#define SPI_IMR_RXOIM_MASK                     0x8u
#define SPI_IMR_RXOIM_SHIFT                    3
#define SPI_IMR_RXFIM_MASK                     0x10u
#define SPI_IMR_RXFIM_SHIFT                    4

 /* ISR Bit Fields */
#define SPI_ISR_TXEIS_MASK                     0x1u
#define SPI_ISR_TXEIS_SHIFT                    0
#define SPI_ISR_TXOIS_MASK                     0x2u
#define SPI_ISR_TXOIS_SHIFT                    1
#define SPI_ISR_RXUIS_MASK                     0x4u
#define SPI_ISR_RXUIS_SHIFT                    2
#define SPI_ISR_RXOIS_MASK                     0x8u
#define SPI_ISR_RXOIS_SHIFT                    3
#define SPI_ISR_RXFIS_MASK                     0x10u
#define SPI_ISR_RXFIS_SHIFT                    4

 /* RISR Bit Fields */
#define SPI_RISR_TXEIR_MASK                    0x1u
#define SPI_RISR_TXEIR_SHIFT                   0
#define SPI_RISR_TXOIR_MASK                    0x2u
#define SPI_RISR_TXOIR_SHIFT                   1
#define SPI_RISR_RXUIR_MASK                    0x4u
#define SPI_RISR_RXUIR_SHIFT                   2
#define SPI_RISR_RXOIR_MASK                    0x8u
#define SPI_RISR_RXOIR_SHIFT                   3
#define SPI_RISR_RXFIR_MASK                    0x10u
#define SPI_RISR_RXFIR_SHIFT                   4

 /* TXOICR Bit Fields */
#define SPI_TXOICR_CTXOI_MASK                  0x1u
#define SPI_TXOICR_CTXOI_SHIFT                 0

 /* RXOICR Bit Fields */
#define SPI_RXOICR_CRXOI_MASK                  0x1u
#define SPI_RXOICR_CRXOI_SHIFT                 0

 /* RXUICR Bit Fields */
#define SPI_RXUICR_CRXUI_MASK                  0x1u
#define SPI_RXUICR_CRXUI_SHIFT                 0

 /* ICR Bit Fields */
#define SPI_ICR_CI_MASK                        0x1u
#define SPI_ICR_CI_SHIFT                       0

 /* DMACR Bit Fields */
#define SPI_DMACR_RDMAE_MASK                   0x1u
#define SPI_DMACR_RDMAE_SHIFT                  0
#define SPI_DMACR_TDMAE_MASK                   0x2u
#define SPI_DMACR_TDMAE_SHIFT                  1

 /* DMATDLR Bit Fields */
#define SPI_DMATDLR_DMATDL_MASK                0xFu
#define SPI_DMATDLR_DMATDL_SHIFT               0
#define SPI_DMATDLR_DMATDL_WIDTH               4

 /* DMARDLR Bit Fields */
#define SPI_DMARDLR_DMARDL_MASK                0xFu
#define SPI_DMARDLR_DMARDL_SHIFT               0

 /* DR Bit Fields */
#define SPI_DR_DR_MASK                         0xFFFFu
#define SPI_DR_DR_SHIFT                        0

 /* MODE Bit Fields */
#define SPI_MODE_MSTR_MASK                     0x1u
#define SPI_MODE_MSTR_SHIFT                    0

 /* MODE Bit Fields */
#define SPI_MODE_PACK_MASK                     0x2u
#define SPI_MODE_PACK_SHIFT                    1


/** SPI - Register Layout Typedef */
typedef struct {
 __IO uint32_t  CTRLR0;                          /*!< SPI���ƼĴ���0, offset:0x0*/
 __IO uint32_t  CTRLR1;                          /*!< SPI���ƼĴ���1, offset:0x04*/
 __IO uint32_t  SPIENR;                          /*!< SPIʹ�ܼĴ���, offset:0x08*/
      uint32_t  RESERVED_0[1];                  
 __IO uint32_t  SER;                             /*!< SPI�ӻ�ʹ�ܼĴ���, offset:0x10*/
 __IO uint32_t  BAUDR;                           /*!< SPI������ѡ��Ĵ���, offset:0x14*/
 __IO uint32_t  TXFTLR;                          /*!< SPI����FIFO��ֵ���üĴ���, offset:0x18*/
 __IO uint32_t  RXFTLR;                          /*!< SPI����FIFO��ֵ���üĴ���, offset:0x1C*/
 __I  uint32_t  TXFLR;                           /*!< SPI����FIFO��ֵ�Ĵ���, offset:0x20*/
 __I  uint32_t  RXFLR;                           /*!< SPI����FIFO��ֵ�Ĵ���, offset:0x24*/
 __I  uint32_t  SR;                              /*!< SPI״̬�Ĵ���, offset:0x28*/
 __IO uint32_t  IMR;                             /*!< SPI�ж����μĴ���, offset:0x2C*/
 __I  uint32_t  ISR;                             /*!< SPI�ж�״̬�Ĵ���, offset:0x30*/
 __I  uint32_t  RISR;                            /*!< SPIԭʼ�ж�״̬�Ĵ���, offset:0x34*/
 __I  uint32_t  TXOICR;                          /*!< SPI����FIFO����ж�����Ĵ���, offset:0x38*/
 __I  uint32_t  RXOICR;                          /*!< SPI����FIFO����ж�����Ĵ���, offset:0x3C*/
 __I  uint32_t  RXUICR;                          /*!< SPI����FIFO�����ж�����Ĵ���, offset:0x40*/
      uint32_t  RESERVED_1[1];                 
 __I  uint32_t  ICR;                             /*!< SPI�ж�����Ĵ���, offset:0x48*/
 __IO uint32_t  DMACR;                           /*!< SPI DMA���ƼĴ���, offset:0x4C*/
 __IO uint32_t  DMATDLR;                         /*!< SPI DMA��������ˮƽ�Ĵ���, offset:0x50*/
 __IO uint32_t  DMARDLR;                         /*!< SPI DMA��������ˮƽ�Ĵ���, offset:0x54*/
      uint32_t  RESERVED_2[1];                   
      uint32_t  RESERVED_3[1];                   
 __IO uint32_t  DR[36];                          /*!< SPI���ݼĴ���, array offset: 0x60, array step: 0x4*/\
 __IO uint32_t  DLY;                             /*!< SPI�����ӳٲ����Ĵ���, offset:0xF0*/
      uint32_t  RESERVED_4[1];									 			
			uint32_t  RESERVED_5[1];                  
      uint32_t  RESERVED_6[1];									
 __IO uint32_t  MODE;                            /*!< SPIģʽѡ��Ĵ���, array offset: 0x100 */
} SPI_Type;	 
//} SPI_Type, *SPI_MemMapPtr;	
extern SPI_Type* SPI0;
extern SPI_Type* SPI1;	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI 
  * @{
  */
	
/* Exported types ------------------------------------------------------------*/ 

/** 
	* @brief SPI������ʼ���ṹ��
*/
typedef struct 
{	
		uint32_t      SPI_SourceClk;    					/*!< ʱ��Դ */
		uint32_t      SPI_BAUDR;       					 	/*!< ������ѡ��      */
	  uint32_t      SPI_SRL;          					/*!< ��λ�Ĵ���ѭ�� */
	  uint32_t      SPI_TMOD;         					/*!< ����ģʽ */
	  uint32_t      SPI_SCPOL;        					/*!< ����ʱ�Ӽ��� */
	  uint32_t      SPI_SCPH;         					/*!< ����ʱ����λ */
	  uint32_t      SPI_DFS;          					/*!< ����֡��С */
	  uint32_t      SPI_NDF;	        					/*!< ����֡���� */
	  uint32_t      SPI_TFT;          					/*!< ����FIFO��ֵ */
	  uint32_t      SPI_RFT;          					/*!< ����FIFO��ֵ */
}SPI_MsterInitTypeDef, *SPI_MsterInitConfigPtr;

/** 
	* @brief SPI�ӻ���ʼ���ṹ��
*/
typedef struct 
{	
	  FunctionalState   SPI_SLVOE;    					/*!< �ӻ����ʹ�� */
	  uint32_t          SPI_SRL;      					/*!< ��λ�Ĵ���ѭ�� */
	  uint32_t          SPI_TMOD;     					/*!< ����ģʽ */
	  uint32_t          SPI_SCPOL;    					/*!< ����ʱ�Ӽ��� */
	  uint32_t          SPI_SCPH;     					/*!< ����ʱ����λ */
	  uint32_t          SPI_DFS;      					/*!< ����֡��С */
	  uint32_t          SPI_TFT;      					/*!< ����FIFO��ֵ */
	  uint32_t          SPI_RFT;      					/*!< ����FIFO��ֵ */
}SPI_SlaveInitTypeDef, *SPI_SlaveInitConfigPtr;	

/* Exported constants --------------------------------------------------------*/


/** @defgroup SPI_Exported_Constants SPIģ��ʹ�ò�������
  * @{
  */

/**
	* @defgroup SPI_Work_Mode SPI����ģʽ
	*	@brief ʱ��Դѡ��
	* @{
  */
#define SPI_SRL_NORMAL                    		((uint16_t)0x0000) /*!< ����ģʽ���� */
#define SPI_SRL_TEST                      		((uint16_t)0x0800) /*!< ����ģʽ���� */
/**
  * @}
*/

/**
	* @defgroup SPI_Transfer_Mode SPI����ģʽ
  * @{
  */
#define SPI_TransmitAndReceive            		((uint16_t)0x0000) /*!< ���ͺͽ��� */
#define SPI_TransmitOnly                  		((uint16_t)0x0100) /*!< ������ */
#define SPI_ReceiveOnly                   		((uint16_t)0x0200) /*!< ������ */
#define SPI_EEPROMRead                    		((uint16_t)0x0300) /*!< EEPROM��ȡ */
/**
  * @}
*/

/**
	* @defgroup SPI_Serial_Clock_Polarity SPIʱ�Ӽ���
  * @{
  */
#define SPI_SCPOL_Low                    		((uint16_t)0x0000) /*!< SPIʱ�Ӽ���Ϊ�� */
#define SPI_SCPOL_High                   		((uint16_t)0x0080) /*!< SPIʱ�Ӽ���λ�� */
/**
  * @}
*/

/**
	* @defgroup SPI Serial Clock Phase
	*	@brief ʱ��Դѡ��
  * @{
  */
#define SPI_SCPH_Middle                 		((uint16_t)0x0000) /*!< ����ʱ���ڵ�һ������λ���м��л� */
#define SPI_SCPH_Start                  		((uint16_t)0x0040) /*!< ����ʱ���ڵ�һ������λ��ʼʱ�л� */
/**
  * @}
*/

/**
	* @defgroup SPI_Data_Lenght SPI���ݳ���
  * @{
  */
#define SPI_DataSize_4b               		((uint16_t)0x0003) /*!< 4�Dλ�������ݴ��� */
#define SPI_DataSize_5b               		((uint16_t)0x0004) /*!< 5�Dλ�������ݴ��� */
#define SPI_DataSize_6b               		((uint16_t)0x0005) /*!< 6�Dλ�������ݴ��� */
#define SPI_DataSize_7b               		((uint16_t)0x0006) /*!< 7�Dλ�������ݴ��� */
#define SPI_DataSize_8b               		((uint16_t)0x0007) /*!< 8�Dλ�������ݴ��� */
#define SPI_DataSize_9b               		((uint16_t)0x0008) /*!< 9�Dλ�������ݴ��� */
#define SPI_DataSize_10b              		((uint16_t)0x0009) /*!< 10�Dλ�������ݴ��� */
#define SPI_DataSize_11b              		((uint16_t)0x000A) /*!< 11�Dλ�������ݴ��� */
#define SPI_DataSize_12b              		((uint16_t)0x000B) /*!< 12�Dλ�������ݴ��� */
#define SPI_DataSize_13b              		((uint16_t)0x000C) /*!< 13�Dλ�������ݴ��� */
#define SPI_DataSize_14b              		((uint16_t)0x000D) /*!< 14�Dλ�������ݴ��� */
#define SPI_DataSize_15b              		((uint16_t)0x000E) /*!< 15�Dλ�������ݴ��� */
#define SPI_DataSize_16b              		((uint16_t)0x000F) /*!< 16�Dλ�������ݴ��� */
/**
  * @}
*/

/**
	* @brief SPI_Mode SPIģʽ
  * @{
	*/
typedef enum
{
  SPI_MODE_MASTER = 0x00,        /*!< ����ģʽ */
  SPI_MODE_SLAVE  = 0x01         /*!< �ӻ�ģʽ */
	
}SPI_MODETypeDef;
/**
  * @}
*/

/**
	* @brief SPI_Data_Pack SPI���������
	* @{
	*/
typedef enum
{
  SPI_PACK_CS_LOW  = 0x00,           /*!< ƬѡΪ�� */
  SPI_PACK_CS_HIGHT   = 0x01         /*!< ƬѡΪ�� */
	
}SPI_PACKCSTypeDef;
/**
  * @}
  */

/**
	* @brief SPI TxRx_FIFO_Level SPI����/����FIFO���
  * @{
	*/
typedef enum
{
  SPI_TransmitFIFOLevel = 0x00,        /*!< ����FIFO��Ч���ݸ��� */
  SPI_ReceiveFIFOLevel  = 0x01         /*!< ����FIFO��Ч���ݸ��� */
	
}SPI_TXRXFIFOLevelDef;
/**
  * @}
	*/

/**
	* @brief SPI_Status SPI״̬
  * @{
	*/
typedef enum 
{
		SPI_SPIBusyFlagStatus = 0,                  /*!< SPI��æ��־λ */
		SPI_TransmitFIFONotFullStatus,              /*!< ����FIFOδ�� */
		SPI_TransmitFIFOEmptyStatus,                /*!< ����FIFOΪ�� */
		SPI_ReceiveFIFONotEmptyStatus,              /*!< ����FIFO��Ϊ�� */
		SPI_ReceiveFIFOFullStatus,                  /*!< ����FIFO���� */
		SPI_TransmissionErrorStatus,                /*!< ���ݷ��ʹ���ֻ��SPIΪ�ӻ�ʱ����ʹ�ô˹��� */	
		SPI_DataCollisionErrorStatus                /*!< ���ݳ�ͻ����ֻ��SPIΪ����ʱ���д˹���*/

}SPI_StatusTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Interrupt_Status SPI�ж�״̬
  * @{
	*/
typedef enum 
{
          SPI_TransmitFIFOEmptyIT = 0,         /*!< ����FIFO�ѿյ��ж����� */
          SPI_TransmitFIFOOverflowIT,          /*!< ����FIFO������ж����� */
          SPI_ReceiveFIFOUnderflowIT,          /*!< ����FIFO������ж����� */
          SPI_ReceiveFIFOOverflowIT,           /*!< ����FIFO������ж����� */
          SPI_ReceiveFIFOFullIT    ,           /*!< ����FIFO�������ж����� */
					SPI_ALLIT   = 0xFu                   /*!< �������� */
}SPI_InterruptTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Interrupt_Mask SPI�ж�����
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOEmptyITStatus = 0,          /*!< ����FIFO�ѿյ��ж�״̬ */
	  SPI_TransmitFIFOOverflowITStatus,           /*!< ����FIFO������ж�״̬ */
	  SPI_ReceiveFIFOUnderflowITStatus,           /*!< ����FIFO������ж�״̬ */
	  SPI_ReceiveFIFOOverflowITStatus,            /*!< ����FIFO������ж�״̬ */
	  SPI_ReceiveFIFOFullITStatus                 /*!< ����FIFO�������ж�״̬ */
	 
}SPI_ITStatusMaskedDef;
/**
  * @}
	*/

/**
	* @brief SPI_Raw_Interrupt_Status SPI�ж�ǰ״̬
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOEmptyRawITStatus = 0,          /*!< ����FIFOԭʼ�ж�Ϊ��״̬ */
	  SPI_TransmitFIFOOverflowRawITStatus,           /*!< ����FIFOԭʼ״̬���״̬ */
	  SPI_ReceiveFIFOUnderflowRawITStatus,           /*!< ����FIFOԭʼ�ж�����״̬ */
	  SPI_ReceiveFIFOOverflowRawITStatus,            /*!< ����FIFOԭʼ�ж����״̬ */
	  SPI_ReceiveFIFOFullRawITStatus                 /*!< ����FIFOԭʼ�ж�����״̬ */
	 
}SPI_RawITStatusTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Clear_Interrupt SPI����жϱ�־
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOOverflowITClear  = 0,           /*!< ��շ���FIFO����жϼĴ��� */
	  SPI_ReceiveFIFOOverflowITClear,                 /*!< ��ս���FIFO����жϼĴ��� */
    SPI_ReceiveFIFOUnderflowITClear,                /*!< ��ս���FIFO�����жϼĴ��� */
	  SPI_ALLITClear                                  /*!< ��������ж�״̬ */

}SPI_InterruptClearDef;
/**
  * @}
	*/


/**
  * @}
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void SPI_DeInit(SPI_Type *SPIx);
void SPI_SetMode(SPI_Type *SPIx,SPI_MODETypeDef SPI_MODEType);
void SPI_SetPackCS(SPI_Type *SPIx,SPI_PACKCSTypeDef SPI_PACKCSType);
void SPI_MasterInit(SPI_Type* SPIx, const SPI_MsterInitTypeDef *SPI_MasterInitStruct);
void SPI_SlaveInit(SPI_Type* SPIx,const SPI_SlaveInitTypeDef *SPI_SlaveInitStruct);
void SPI_EnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_SlaveEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_SendData(SPI_Type *SPIx,uint16_t Data);
uint16_t SPI_ReceiveData(const SPI_Type *SPIx);
uint8_t SPI_GetFIFOLevel(const SPI_Type *SPIx,SPI_TXRXFIFOLevelDef FIFOLevelDef);
uint8_t SPI_GetStatus(const SPI_Type *SPIx,SPI_StatusTypeDef SPI_StatusType);
void SPI_InterruptEn(SPI_Type *SPIx, SPI_InterruptTypeDef SPI_Interrupt, FunctionalState NewState);
uint8_t SPI_ClearInterrupt(const SPI_Type *SPIx, SPI_InterruptClearDef SPI_Interrupt2Clear);
uint8_t SPI_GetIntMaskedStatus(const SPI_Type *SPIx,SPI_ITStatusMaskedDef SPI_IntStatusType);
uint8_t SPI_GetRawIntStatus(const SPI_Type *SPIx,SPI_RawITStatusTypeDef SPI_RawIntStatusType);
void SPI_SetDMATxDataLenght(SPI_Type *SPIx,uint8_t lenght);
void SPI_SetDMARxDataLenght(SPI_Type *SPIx,uint8_t lenght);
void SPI_DMATxEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_DMARxEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_DelaySampling(SPI_Type *SPIx,uint32_t nclock);
#ifdef __cplusplus
}
#endif

#endif /*__XL_SPI_H */
/**
  * @}
*/

/**
  * @}
*/
