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
 * (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）-> CLK1M - 1MHz分频系数*/
#define FMC_FCPC0_CLK1M_SHIFT              		 	 10u

#define FMC_FCPC0_RWC_MASK               		 		 0x001E0000u/*
 * (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）-> RWC - 读等待周期设置; 可设置0 ~ 15个HCLK时钟等待周期
 * 0000 不等待; 0001 等待1个周期; 0010 等待2个周期;...*/
#define FMC_FCPC0_RWC_SHIFT              		 		 17u

#define FMC_FCPC0_CEN_MASK               		 		 0x00200000u
#define FMC_FCPC0_CEN_SHIFT              		 		 21

#define FMC_FCPC0_DPSTB_MASK               		 	 0x00400000u
#define FMC_FCPC0_DPSTB_SHIFT              		 	 22

#define FMC_FCPC0_CLK1MLCK_MASK            	 		 0x40000000u/*
 * (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）-> CLK1MLCK - CLK1M的锁定控制
 * 0 - 可修改CLK1M值; 1 - 禁止修改CLK1M值*/
#define FMC_FCPC0_CLK1MLCK_SHIFT              	 30

#define FMC_FCPC0_HSMD_MASK            	 		     0x80000000u/*
 * (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）-> HSMD - 设置低速和高速FLASH时序控制
 * 0 - 时钟为小于等于48MHz时，该为置0
 * 1 - 时钟大于48MHz时，该位必须置1，否则可能造成FLASH编程操作失败*/
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
 * (1-196)第 15 章 Flash 存储器控制器(FMC)*/

typedef struct
{
	__IO	uint32_t FSTAT;                          /*!< (1-210)15.4.1 Flash状态寄存器, offset: 0x0 */
	__IO	uint32_t FCCOBF0;                        /*!< Flash命令寄存器0, offset: 0x4 */
	__IO	uint32_t FCCOBF1;                        /*!< Flash命令寄存器1, offset: 0x8 */
	__IO	uint32_t FCCOBF2;                        /*!< Flash命令寄存器2, offset: 0xC */
	__IO	uint32_t FCNFG;                          /*!< Flash配置寄存器, offset: 0x10 */
	__IO	uint32_t FRLD;                           /*!< Flash配置字段重新加载寄存器, offset: 0x14 */
	__IO	uint32_t RESERVED1[2];
	__IO	uint32_t FCPC0;                          /*!< (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）, offset: 0x20 */
	__IO	uint32_t RESERVED2[5];//3	
	__IO	uint32_t FOSP;                           /*!< Flash安全选择寄存器, offset: 0x30 */
	__IO	uint32_t RESERVED3;//3						
	__IO	uint32_t KEYLOW;						 						 /*!< Flash后门秘钥低寄存器, offset: 0x40 */
	__IO	uint32_t RESERVED4;
	__IO	uint32_t KEYHIGH;												 /*!< Flash后门秘钥高寄存器, offset: 0x48 */
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
	* @brief FLASH保护配置结构体定义
	*/
typedef struct
{    
	FunctionalState  FLASH_POPEN;         /*!< FLASH操作保护使能 */  
	uint8_t  FLASH_FPHDIS;                /*!< Flash保护较高地址范围禁用 */
	uint8_t  FLASH_FPLDIS;                /*!< Flash保护较低地址范围禁用 */
	uint8_t FLASH_FPHS;                   /*!<  Flash保护较高地址大小 */
	uint8_t FLASH_FPLS;                   /*!<  Flash保护较低地址大小 */
	
} FLASH_ProtectTypeDef, *FLASH_ProtectConfigPtr;

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLAHS_Exported_Constants FLASH模块使用参数定义
  * @{
  */

/**
  *	@defgroup Flash_Exported_Types Flash初始化状态
  * @{
  */

#define FLASH_InitStatus_Failed       				((uint8_t)0x00)   /*!< FLASH初始化失败 */
#define FLASH_InitStatus_Success      				((uint8_t)0x01)   /*!< FLASH初始化成功 */																			
/**
* @}
*/

/** 
	* @defgroup Flash_Protect_Commad_List Flash保护命令
  * @{
  */
#define FLASH_PROTECT_MASK             				0x0000FF00u				      

#define FLASH_FPHS_1KB                  			((uint8_t)0x00)           /*!< FLASH保护高地址范围0x7C00-0x7FFF */
#define FLASH_FPHS_2KB                  			((uint8_t)0x01)           /*!< FLASH保护高地址范围0x7800-0x7FFF */
#define FLASH_FPHS_4KB                  			((uint8_t)0x02)           /*!< FLASH保护高地址范围0x7000-0x7FFF */
#define FLASH_FPHS_8KB                  			((uint8_t)0x03)           /*!< FLASH保护高地址范围0x6000-0x7FFF */

																					 
#define FLASH_FPLS_2KB					      				((uint8_t)0x00)			      /*!< FLASH保护低地址范围0x0000-x07FF */	
#define FLASH_FPLS_4KB					      				((uint8_t)0x00)			      /*!< FLASH保护低地址范围0x0000-x0FFF */	
#define FLASH_FPLS_8KB					      				((uint8_t)0x00)			      /*!< FLASH保护低地址范围0x0000-x1FFF */
#define FLASH_FPLS_16KB					      				((uint8_t)0x00)		      	/*!< FLASH保护低地址范围0x0000-x3FFF */	
/**
  * @}
  */
	
/** 
  * @defgroup Flash_ECC/Erase_Error  Flash ECC错误，擦除校验错误
  * @{
  */
#define FLASH_FSTAT_MGSTAT0_MASK       				0x01000000u					/*!< FLASH闪存命令错误标志0 */
#define FLASH_FSTAT_MGSTAT1_MASK       				0x03000000u     	  /*!< FLASH闪存命令错误标志1 */
/**
  * @}
  */

/** 
  * @defgroup Flash_Start_Address/Sector_Size Flash起始地址和扇区的大小
  * @{
  */	
#define FLASH_SECTOR_SIZE			         				1024							  /*!< FLASH扇区大小 */
#define FLASH_START_ADDRESS			       				0							  	  /*!< FLASH起始地址 */
/**
  * @}
  */

/** 
  * @defgroup Flash_Error_Type Flash错误状态定义
  * @{
  */
#define FLASH_ERR_BASE		     		     				0x3000							     
#define FLASH_ERR_SUCCESS			         				0u							/*!< 无错误 */
#define FLASH_ERR_INVALID_PARAM		     					(FLASH_ERR_BASE+1)	      	/*!< 无效参数错误 */
#define FLASH_ERR_ACCESS			         				(FLASH_ERR_BASE+8)			/*!< flash访问错误标志 */
#define FLASH_ERR_PROTECTION	    	   					(FLASH_ERR_BASE+0x10)		/*!< flash保护违反标志 */
#define FLASH_ERR_ECC			             				(FLASH_ERR_BASE+0x11)		/*!< flash ecc校验错误 */
#define FLASH_ERR_ERASEVERIFY			     				(FLASH_ERR_BASE+0x12)		/*!< flash擦除验证错误 */
#define FLASH_ERR_INIT_CCIF			       					(FLASH_ERR_BASE+0x14)		/*!< 加载命令未完成 *//*
 * (1-210)15.4.1 Flash 状态寄存器（FSTAT）-> CCIF命令完成标志*/
#define FLASH_ERR_INIT_CLKIM			     				(FLASH_ERR_BASE+0x18)		/*!< CLK1M错误 */
/**
  * @}
  */
	
/** 
  * @defgroup Flash_Commad_List Flash命令列表
  * @{
  */
#define FLASH_CMD_ERASE_CHIP						  		0x01			/*!< 擦除整块FLASH */	
#define FLASH_CMD_ERASE_SECTOR					  		0x02			/*!< 擦除扇区 */	
#define FLASH_CMD_PROGRAM											0x03			/*!< FLASH编程命令 */
#define FLASH_CMD_POWER_ON_RESET				  		0x04			/*!< FLASH上电复位 */
#define FLASH_CMD_READ							    			0x05			/*!< FLASH读命令 */
#define FLASH_CMD_ERASE_VERIFY_SECTOR					0x06			/*!< 扇区擦除校验 */
#define FLASH_CMD_ERASE_VERIFY_CHIP						0x07			/*!< 芯片擦除校验 */
/**
  * @}
  */
	
/** 
  * @defgroup Flash_Disable_ECC_Area Flash禁用ECC区域
  * @{
  */
#define FLASH_ECC_DISABLE_AREA_0KB					  		0x00			/*!< ECC禁用0KB地址空间 */	
#define FLASH_ECC_DISABLE_AREA_1KB					  		0x01			/*!< ECC禁用1KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_2KB					  		0x02			/*!< ECC禁用2KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_4KB					  		0x03			/*!< ECC禁用4KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_8KB					  		0x04			/*!< ECC禁用8KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_16KB					  		0x05			/*!< ECC禁用16KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_32KB					  		0x06			/*!< ECC禁用32KB地址空间 */
#define FLASH_ECC_DISABLE_AREA_64KB					  		0x07			/*!< ECC禁用64KB地址空间 */
/**
  * @}
  */
	
/**
  * @brief Flash_Wead_Wait_Cycle Flash读等待时间周期
  * @{
  */	
typedef enum 
{ 	
	FLASH_READWAIT_NO              =0,            /*!< 无等待 */
  FLASH_READWAIT_1CYCLE          ,              /*!< 读等待1个周期 */
  FLASH_READWAIT_2CYCLE          ,              /*!< 读等待2个周期 */	
  FLASH_READWAIT_3CYCLE          ,              /*!< 读等待3个周期 */
	FLASH_READWAIT_4CYCLE          ,              /*!< 读等待4个周期 */
	FLASH_READWAIT_5CYCLE          ,              /*!< 读等待5个周期 */	
  FLASH_READWAIT_6CYCLE          ,              /*!< 读等待6个周期 */
	FLASH_READWAIT_7CYCLE          ,              /*!< 读等待7个周期 */
	FLASH_READWAIT_8CYCLE          ,              /*!< 读等待8个周期 */	
  FLASH_READWAIT_9CYCLE          ,              /*!< 读等待9个周期 */
	FLASH_READWAIT_10CYCLE         ,              /*!< 读等待10个周期 */
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


