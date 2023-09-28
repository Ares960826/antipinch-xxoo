/**
  ******************************************************************************
  * @file     xl_fmc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the fmc 
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
#ifndef __XL_FLASH_H__
#define __XL_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include <XL6600.h>
/* Register define ------------------------------------------------------------*/
/* FSTAT Bit Fields */
#define FMC_FSTAT_SEC_MASK                       0x00800000u
#define FMC_FSTAT_SEC_SHIFT                      23

#define FMC_FSTAT_MGSTAT_MASK                    0x03000000u
#define FMC_FSTAT_MGSTAT_SHIFT                   24

#define FMC_FSTAT_MGBUSY_MASK                    0x08000000u
#define FMC_FSTAT_MGBUSY_SHIFT                   27

#define FMC_FSTAT_FPVIOL_MASK                    0x10000000u
#define FMC_FSTAT_FPVIOL_SHIFT                   28

#define FMC_FSTAT_ACCERR_MASK                    0x20000000u
#define FMC_FSTAT_ACCERR_SHIFT                   29

#define FMC_FSTAT_CCIF_MASK                      0x80000000u
#define FMC_FSTAT_CCIF_SHIFT                     31

/* FCCOBF0 Bit Fields */
#define FMC_FCCOBF0_FADDR_MASK                   0x00FFFFFFu
#define FMC_FCCOBF0_FADDR_SHIFT                  0u

#define FMC_FCCOBF0_FCMD_MASK               		 0xFF000000u
#define FMC_FCCOBF0_FCMD_SHIFT              		 24u

/* FCCOBF1 Bit Fields */
#define FMC_FCCOBF1_DATA0_MASK               		 0xFFFFFFFFu
#define FMC_FCCOBF1_DATA0_SHIFT              		 0

/* FCCOBF2 Bit Fields */ 
#define FMC_FCCOBF2_DATA1_MASK               		 0xFFFFFFFFu
#define FMC_FCCOBF2_DATA1_SHIFT              		 0

/* FCNFG Bit Fields */
#define FMC_FCNFG_ECC_DISABLE_AREA_MASK          0x0000000Fu
#define FMC_FCNFG_ECC_DISABLE_AREA_SHIFT         0

#define FMC_FCNFG_CCIE_MASK               		 	 0x80000000u
#define FMC_FCNFG_CCIE_SHIFT              		 	 31

/* FRLD Bit Fields */
#define FMC_FRLD_FRLD_MASK               		 	   0x699655AAu
#define FMC_FRLD_FRLD_SHIFT              		 	   0

/* FCPC0 Bit Fields */
#define FMC_FCPC0_CLK1M_MASK               		 	 0x0001FC00u/*
 * (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��-> CLK1M - 1MHz��Ƶϵ��*/
#define FMC_FCPC0_CLK1M_SHIFT              		 	 10u

#define FMC_FCPC0_RWC_MASK               		 		 0x001E0000u/*
 * (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��-> RWC - ���ȴ���������; ������0 ~ 15��HCLKʱ�ӵȴ�����
 * 0000 ���ȴ�; 0001 �ȴ�1������; 0010 �ȴ�2������;...*/
#define FMC_FCPC0_RWC_SHIFT              		 		 17u

#define FMC_FCPC0_CEN_MASK               		 		 0x00200000u
#define FMC_FCPC0_CEN_SHIFT              		 		 21

#define FMC_FCPC0_DPSTB_MASK               		 	 0x00400000u
#define FMC_FCPC0_DPSTB_SHIFT              		 	 22

#define FMC_FCPC0_CLK1MLCK_MASK            	 		 0x40000000u/*
 * (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��-> CLK1MLCK - CLK1M����������
 * 0 - ���޸�CLK1Mֵ; 1 - ��ֹ�޸�CLK1Mֵ*/
#define FMC_FCPC0_CLK1MLCK_SHIFT              	 30

#define FMC_FCPC0_HSMD_MASK            	 		     0x80000000u/*
 * (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��-> HSMD - ���õ��ٺ͸���FLASHʱ�����
 * 0 - ʱ��ΪС�ڵ���48MHzʱ����Ϊ��0
 * 1 - ʱ�Ӵ���48MHzʱ����λ������1������������FLASH��̲���ʧ��*/
#define FMC_FCPC0_HSMD_SHIFT              	     31

/* FOSP Bit Fields */
#define FMC_FOSP_FPLS_MASK                       0x00000300u
#define FMC_FOSP_FPLS_SHIFT                      8u

#define FMC_FOSP_FPLDIS_MASK                     0x00000400u
#define FMC_FOSP_FPLDIS_SHIFT                    10u

#define FMC_FOSP_FPHS_MASK                       0x00001800u
#define FMC_FOSP_FPHS_SHIFT                      11u

#define FMC_FOSP_FPHDIS_MASK                     0x00002000u
#define FMC_FOSP_FPHDIS_SHIFT                    13u

#define FMC_FOSP_RNV6_MASK                       0x00004000u
#define FMC_FOSP_RNV6_SHIFT                      14

#define FMC_FOSP_FPOPEN_MASK                     0x00008000u
#define FMC_FOSP_FPOPEN_SHIFT                    15u

#define FMC_FOSP_FSEC_MASK               		 		 0x00030000u
#define FMC_FOSP_FSEC_SHIFT              		 		 16

#define FMC_FOSP_FOPT_MASK               		 		 0xFF000000u
#define FMC_FOSP_FOPT_SHIFT              		 		 24

/* KEYHIGH Bit Fields */
#define FMC_FOSP_BACKDOOR_EN_MASK               		 		 0x80000000u
#define FMC_FOSP_BACKDOOR_EN_SHIFT              		 		 31

/** FMC - Register Layout Typedef
 * (1-196)�� 15 �� Flash �洢��������(FMC)*/

typedef struct
{
	__IO	uint32_t FSTAT;                          /*!< (1-210)15.4.1 Flash״̬�Ĵ���, offset: 0x0 */
	__IO	uint32_t FCCOBF0;                        /*!< Flash����Ĵ���0, offset: 0x4 */
	__IO	uint32_t FCCOBF1;                        /*!< Flash����Ĵ���1, offset: 0x8 */
	__IO	uint32_t FCCOBF2;                        /*!< Flash����Ĵ���2, offset: 0xC */
	__IO	uint32_t FCNFG;                          /*!< Flash���üĴ���, offset: 0x10 */
	__IO	uint32_t FRLD;                           /*!< Flash�����ֶ����¼��ؼĴ���, offset: 0x14 */
	__IO	uint32_t RESERVED1[2];
	__IO	uint32_t FCPC0;                          /*!< (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��, offset: 0x20 */
	__IO	uint32_t RESERVED2[5];//3	
	__IO	uint32_t FOSP;                           /*!< Flash��ȫѡ��Ĵ���, offset: 0x30 */
	__IO	uint32_t RESERVED3;//3						
	__IO	uint32_t KEYLOW;						 						 /*!< Flash������Կ�ͼĴ���, offset: 0x40 */
	__IO	uint32_t RESERVED4;
	__IO	uint32_t KEYHIGH;												 /*!< Flash������Կ�߼Ĵ���, offset: 0x48 */
}FMC_Type;

extern FMC_Type* FMC;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
	* @brief FLASH�������ýṹ�嶨��
	*/
typedef struct
{    
	FunctionalState  FLASH_POPEN;         /*!< FLASH��������ʹ�� */  
	uint8_t  FLASH_FPHDIS;                /*!< Flash�����ϸߵ�ַ��Χ���� */
	uint8_t  FLASH_FPLDIS;                /*!< Flash�����ϵ͵�ַ��Χ���� */
	uint8_t FLASH_FPHS;                   /*!<  Flash�����ϸߵ�ַ��С */
	uint8_t FLASH_FPLS;                   /*!<  Flash�����ϵ͵�ַ��С */
	
} FLASH_ProtectTypeDef, *FLASH_ProtectConfigPtr;

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLAHS_Exported_Constants FLASHģ��ʹ�ò�������
  * @{
  */

/**
  *	@defgroup Flash_Exported_Types Flash��ʼ��״̬
  * @{
  */

#define FLASH_InitStatus_Failed       				((uint8_t)0x00)   /*!< FLASH��ʼ��ʧ�� */
#define FLASH_InitStatus_Success      				((uint8_t)0x01)   /*!< FLASH��ʼ���ɹ� */																			
/**
* @}
*/

/** 
	* @defgroup Flash_Protect_Commad_List Flash��������
  * @{
  */
#define FLASH_PROTECT_MASK             				0x0000FF00u				      

#define FLASH_FPHS_1KB                  			((uint8_t)0x00)           /*!< FLASH�����ߵ�ַ��Χ0x7C00-0x7FFF */
#define FLASH_FPHS_2KB                  			((uint8_t)0x01)           /*!< FLASH�����ߵ�ַ��Χ0x7800-0x7FFF */
#define FLASH_FPHS_4KB                  			((uint8_t)0x02)           /*!< FLASH�����ߵ�ַ��Χ0x7000-0x7FFF */
#define FLASH_FPHS_8KB                  			((uint8_t)0x03)           /*!< FLASH�����ߵ�ַ��Χ0x6000-0x7FFF */

																					 
#define FLASH_FPLS_2KB					      				((uint8_t)0x00)			      /*!< FLASH�����͵�ַ��Χ0x0000-x07FF */	
#define FLASH_FPLS_4KB					      				((uint8_t)0x00)			      /*!< FLASH�����͵�ַ��Χ0x0000-x0FFF */	
#define FLASH_FPLS_8KB					      				((uint8_t)0x00)			      /*!< FLASH�����͵�ַ��Χ0x0000-x1FFF */
#define FLASH_FPLS_16KB					      				((uint8_t)0x00)		      	/*!< FLASH�����͵�ַ��Χ0x0000-x3FFF */	
/**
  * @}
  */
	
/** 
  * @defgroup Flash_ECC/Erase_Error  Flash ECC���󣬲���У�����
  * @{
  */
#define FLASH_FSTAT_MGSTAT0_MASK       				0x01000000u					/*!< FLASH������������־0 */
#define FLASH_FSTAT_MGSTAT1_MASK       				0x03000000u     	  /*!< FLASH������������־1 */
/**
  * @}
  */

/** 
  * @defgroup Flash_Start_Address/Sector_Size Flash��ʼ��ַ�������Ĵ�С
  * @{
  */	
#define FLASH_SECTOR_SIZE			         				1024							  /*!< FLASH������С */
#define FLASH_START_ADDRESS			       				0							  	  /*!< FLASH��ʼ��ַ */
/**
  * @}
  */

/** 
  * @defgroup Flash_Error_Type Flash����״̬����
  * @{
  */
#define FLASH_ERR_BASE		     		     				0x3000							     
#define FLASH_ERR_SUCCESS			         				0u							/*!< �޴��� */
#define FLASH_ERR_INVALID_PARAM		     					(FLASH_ERR_BASE+1)	      	/*!< ��Ч�������� */
#define FLASH_ERR_ACCESS			         				(FLASH_ERR_BASE+8)			/*!< flash���ʴ����־ */
#define FLASH_ERR_PROTECTION	    	   					(FLASH_ERR_BASE+0x10)		/*!< flash����Υ����־ */
#define FLASH_ERR_ECC			             				(FLASH_ERR_BASE+0x11)		/*!< flash eccУ����� */
#define FLASH_ERR_ERASEVERIFY			     				(FLASH_ERR_BASE+0x12)		/*!< flash������֤���� */
#define FLASH_ERR_INIT_CCIF			       					(FLASH_ERR_BASE+0x14)		/*!< ��������δ��� *//*
 * (1-210)15.4.1 Flash ״̬�Ĵ�����FSTAT��-> CCIF������ɱ�־*/
#define FLASH_ERR_INIT_CLKIM			     				(FLASH_ERR_BASE+0x18)		/*!< CLK1M���� */
/**
  * @}
  */
	
/** 
  * @defgroup Flash_Commad_List Flash�����б�
  * @{
  */
#define FLASH_CMD_ERASE_CHIP						  		0x01			/*!< ��������FLASH */	
#define FLASH_CMD_ERASE_SECTOR					  		0x02			/*!< �������� */	
#define FLASH_CMD_PROGRAM											0x03			/*!< FLASH������� */
#define FLASH_CMD_POWER_ON_RESET				  		0x04			/*!< FLASH�ϵ縴λ */
#define FLASH_CMD_READ							    			0x05			/*!< FLASH������ */
#define FLASH_CMD_ERASE_VERIFY_SECTOR					0x06			/*!< ��������У�� */
#define FLASH_CMD_ERASE_VERIFY_CHIP						0x07			/*!< оƬ����У�� */
/**
  * @}
  */
	
/** 
  * @defgroup Flash_Disable_ECC_Area Flash����ECC����
  * @{
  */
#define FLASH_ECC_DISABLE_AREA_0KB					  		0x00			/*!< ECC����0KB��ַ�ռ� */	
#define FLASH_ECC_DISABLE_AREA_1KB					  		0x01			/*!< ECC����1KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_2KB					  		0x02			/*!< ECC����2KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_4KB					  		0x03			/*!< ECC����4KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_8KB					  		0x04			/*!< ECC����8KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_16KB					  		0x05			/*!< ECC����16KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_32KB					  		0x06			/*!< ECC����32KB��ַ�ռ� */
#define FLASH_ECC_DISABLE_AREA_64KB					  		0x07			/*!< ECC����64KB��ַ�ռ� */
/**
  * @}
  */
	
/**
  * @brief Flash_Wead_Wait_Cycle Flash���ȴ�ʱ������
  * @{
  */	
typedef enum 
{ 	
	FLASH_READWAIT_NO              =0,            /*!< �޵ȴ� */
  FLASH_READWAIT_1CYCLE          ,              /*!< ���ȴ�1������ */
  FLASH_READWAIT_2CYCLE          ,              /*!< ���ȴ�2������ */	
  FLASH_READWAIT_3CYCLE          ,              /*!< ���ȴ�3������ */
	FLASH_READWAIT_4CYCLE          ,              /*!< ���ȴ�4������ */
	FLASH_READWAIT_5CYCLE          ,              /*!< ���ȴ�5������ */	
  FLASH_READWAIT_6CYCLE          ,              /*!< ���ȴ�6������ */
	FLASH_READWAIT_7CYCLE          ,              /*!< ���ȴ�7������ */
	FLASH_READWAIT_8CYCLE          ,              /*!< ���ȴ�8������ */	
  FLASH_READWAIT_9CYCLE          ,              /*!< ���ȴ�9������ */
	FLASH_READWAIT_10CYCLE         ,              /*!< ���ȴ�10������ */
}FLASH_ReadWaitCycleDef;	
/**
  * @}
  */



/**
  * @}
  */
#if defined(__GNUC__)
#undef _Init_Flash_Ram
#define _Init_Flash_Ram __attribute__((__section__(".flash_ram")))
#else
#undef _Init_Flash_Ram
#define _Init_Flash_Ram
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint16_t FLASH_Init(uint8_t BusClockMhz) _Init_Flash_Ram;
void FLASH_ProtecConfig(const FLASH_ProtectTypeDef *FLASH_ProtectType) _Init_Flash_Ram;
void FLASH_CCIEnableCmd( FunctionalState NewState) _Init_Flash_Ram;
void FLASH_CacheCmd( FunctionalState NewState) _Init_Flash_Ram;
void FLASH_SleepInStopCmd( FunctionalState NewState) _Init_Flash_Ram;
void FLASH_LockClk1MCmd( FunctionalState NewState) _Init_Flash_Ram;
void FLASH_BuffEnableCmd( FunctionalState NewState) _Init_Flash_Ram;
void FLASH_SetReadWait(FLASH_ReadWaitCycleDef ReadWaitCycle) _Init_Flash_Ram;
uint8_t FLASH_GetCmdFinshFlag(void) _Init_Flash_Ram;
uint8_t FLASH_GetControllerBusyFlag(void) _Init_Flash_Ram;
void FLASH_LaunchCMD(void) _Init_Flash_Ram;
void FLASH_ClearErrFlag(uint32_t flag) _Init_Flash_Ram;
uint16_t FLASH_CheckErrStatus(void) _Init_Flash_Ram;
uint16_t FLASH_Program2LongWord( uint32_t TargetAddress, uint32_t DwData0, uint32_t DwData1) _Init_Flash_Ram;
uint64_t FLASH_ReadLongWord(const uint32_t *TargetAddress) _Init_Flash_Ram;
void FLASH_ReadLongWordCmd(uint32_t TargetAddress) _Init_Flash_Ram;
void FLASH_EraseChip(void) _Init_Flash_Ram;
uint16_t FLASH_EraseSector( uint32_t TargetAddress) _Init_Flash_Ram;
void FLASH_PowerOnReset(void) _Init_Flash_Ram;
uint16_t FLASH_EraseVerifySector( uint32_t TargetAddress) _Init_Flash_Ram;
void FLASH_EraseVerifyChip(void) _Init_Flash_Ram;
void FLASH_ConfigReload(void) _Init_Flash_Ram;
uint8_t FLASH_GetFlashSecurity(void) _Init_Flash_Ram;
uint8_t FLASH_GetFlashProtection(void) _Init_Flash_Ram;
uint8_t FLASH_GetFlashOption(void) _Init_Flash_Ram;
void FLASH_DisableECCArea(uint8_t ecc_area) _Init_Flash_Ram;
void FLASH_BackdoorUnlockFlash(uint32_t KeyHigh, uint32_t Keylow) _Init_Flash_Ram;
#ifdef __cplusplus
}
#endif

#endif    /*__XL_FLASH_H__ */
/**
  * @}
  */

/**
  * @}
  */


