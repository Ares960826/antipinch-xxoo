/**
  ******************************************************************************
  * @file     xl_flash.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about FLASH firmware program 
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
#include "xl_flash.h"
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH FLASH Module 
  * @brief FLASH Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	

/** @defgroup FMC_Private_Functions
  * @{
 */
 
/**
 * @brief FLASH初始化.
 * @param BusClock:当前Flash时钟
 * @retval 返回FLASH状态.
   *		这个参数可以取下面的值:
 *			@arg FLASH_ERR_INIT_CCIF：加载命令未完成
 *			@arg FLASH_ERR_INIT_CLK1M：CLK1M错误 
 */
uint16_t FLASH_Init(uint8_t BusClockMhz)
{
	 uint16_t errorstatus; 
	 uint32_t clk1M = (uint32_t)BusClockMhz - 1u;
	 uint32_t fcpco;
		
	 errorstatus = FLASH_ERR_SUCCESS; 
	
	 if((FMC->FSTAT & FMC_FSTAT_CCIF_MASK) != FMC_FSTAT_CCIF_MASK)/*
	 * FMC->FSTAT=0x8000 0000u; FMC_FSTAT_CCIF_MASK=0x8000 0000u*/
	 {
		 errorstatus |=  (uint16_t)FLASH_ERR_INIT_CCIF; /*
		 * Flash状态和掩码不一致，则记录错误状态
		 * (1-210)15.4.1 Flash 状态寄存器（FSTAT）-> CCIF命令完成标志*/
	 }
	 else
	 {
		 fcpco = FMC->FCPC0;
		 if(BusClockMhz>48u)
		 {
			 /* high speed ,>48Mhz  */
			 fcpco |= FMC_FCPC0_HSMD_MASK;/*
			 * (1-217)15.4.7 Flash 控制器参数寄存器（FCPC0）->HSMD设置低速和高速FLASH时序控制
			 * 0 - 时钟为小于等于48MHz时，该为置0
			 * 1 - 时钟大于48MHz时，该位必须置1，否则可能造成FLASH编程操作失败*/
		 }
		 else
		 {
			 /* low speed ,<=48Mhz  */
			 fcpco &=~FMC_FCPC0_HSMD_MASK;
		 }	 
		 /* clk1m is not locked  */
		 if((fcpco & FMC_FCPC0_CLK1MLCK_MASK) != FMC_FCPC0_CLK1MLCK_MASK)
		 { 
			 /* first clear the clk1M bit */
			 fcpco &= ~FMC_FCPC0_CLK1M_MASK;
			 
			 fcpco |= (clk1M << FMC_FCPC0_CLK1M_SHIFT);
			 
			 FMC->FCPC0 = fcpco;
		 }
		 else	//
		 {
				/* clk1m is locked  */
			 if((fcpco & FMC_FCPC0_CLK1M_MASK)!= (clk1M<<FMC_FCPC0_CLK1M_SHIFT))
			 {
					/* clk1m locked is wrong  */ 
					errorstatus |= (uint16_t)FLASH_ERR_INIT_CLKIM;		 
			 }
		 }	
	 }		 
	 return errorstatus;
}


 
 
/**
 * @brief flash保护配置
 * @param FLASH_ProtectType:保护参数配置结构体
 * @retval None
 */
void FLASH_ProtecConfig(const FLASH_ProtectTypeDef *FLASH_ProtectType)
{
	uint32_t temp;
 
	temp = FMC->FOSP;
	/* first clear the protection bits */
	temp &= ~(uint32_t)FLASH_PROTECT_MASK;
	/* set the protection bits */ 
	temp |= ((uint32_t)FLASH_ProtectType->FLASH_POPEN<<FMC_FOSP_FPOPEN_SHIFT) | ((uint32_t)FLASH_ProtectType->FLASH_FPHDIS<<FMC_FOSP_FPHDIS_SHIFT) |\
					((uint32_t)FLASH_ProtectType->FLASH_FPHS<<FMC_FOSP_FPHS_SHIFT) | ((uint32_t)FLASH_ProtectType->FLASH_FPLDIS<<FMC_FOSP_FPLDIS_SHIFT) |\
					((uint32_t)FLASH_ProtectType->FLASH_FPLS<<FMC_FOSP_FPLS_SHIFT);
	FMC->FOSP = temp;
}

/**
 * @brief flash命令完成中断使能.
 * @param  NewState：选择是否使能
  *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISABLE ：失能
 * @retval None
 */
void FLASH_CCIEnableCmd( FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the FLASH Command Complete interrupt */
		FMC->FCNFG |= FMC_FCNFG_CCIE_MASK;
	}
	else 
	{
		/* Disable the FLASH Command Complete interrupt */
		FMC->FCNFG &= ~FMC_FCNFG_CCIE_MASK;
	}
}

/**
 * @brief flash关闭ECC功能
 * @param  ecc_area：选择的区域，从Flash的最大地址往上计数
 *		这个参数可以取下面的值:
 *			@arg FLASH_ECC_DISABLE_AREA_0KB  ：0Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_1KB  ：1Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_2KB  ：2Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_4KB  ：4Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_8KB  ：8Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_16KB ：16Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_32KB ：32Kb的区间
 *			@arg FLASH_ECC_DISABLE_AREA_64KB ：64Kb的区间
 * @retval None
 */
void FLASH_DisableECCArea(uint8_t ecc_area)
{
	FMC->FCNFG |= (uint32_t)ecc_area;
}

/**
 * @brief flash  缓存是能
 * @param  NewState：选择是否使能
  *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISABLE ：失能
 * @retval None
 */
void FLASH_CacheCmd( FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the cache */
		FMC->FCPC0 |= FMC_FCPC0_CEN_MASK;
	}
	else 
	{
		/* Disable the cache */
		FMC->FCPC0 &= ~FMC_FCPC0_CEN_MASK;
	}
}
 /**
 * @brief flash在stop模式下进入休眠模式
 * @param  NewState：选择是否使能状态.
  *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISABLE ：失能
 * @retval None
 */
void FLASH_SleepInStopCmd( FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* alow to enter sleep mode in stop mode */
		FMC->FCPC0 |= FMC_FCPC0_DPSTB_MASK;
	}
	else 
	{
		/* Can not enter sleep mode in stop mode */
		FMC->FCPC0 &= ~FMC_FCPC0_DPSTB_MASK;
	}
}


 /**
 * @brief CLK1M锁定控制使能
 * @param  NewState：选择是否使能状态.
  *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISABLE ：失能
 * @retval None
 */
void FLASH_LockClk1MCmd( FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* alow to enter sleep mode in stop mode */
		FMC->FCPC0 |= FMC_FCPC0_CLK1MLCK_MASK;
	}
	else 
	{
		/* Can not enter sleep mode in stop mode */
		FMC->FCPC0 &= ~FMC_FCPC0_CLK1MLCK_MASK;
	}
}

/**
 * @brief 设置flash读取等待周期函数
 *
 * @param ReadWaitCycle:读取等待周期的参数类型
 * @retval None
*/
void FLASH_SetReadWait(FLASH_ReadWaitCycleDef ReadWaitCycle)
{
  // 定义局部变量temp,用于暂存FMC->FCPC0寄存器的值
  uint32_t temp;

  // 读取FMC->FCPC0寄存器当前的值到temp
  // FMC代表Flash Memory Controller,是flash存储器控制器
  // FCPC0是其中的一个控制寄存器
  temp = FMC->FCPC0;

  // 将temp的值与反码的RWC位掩码做与运算,将RWC位清零
  // RWC位用于设置flash读取等待周期
  temp &= ~FMC_FCPC0_RWC_MASK;

  // 将ReadWaitCycle左移FMC_FCPC0_RWC_SHIFT位,得到RWC的值
  // 然后与temp做或运算,设置RWC位的值
  temp  |= ((uint32_t)ReadWaitCycle<<FMC_FCPC0_RWC_SHIFT);

  // 将运算后的temp的值写入FMC->FCPC0,设置flash读取等待周期
  FMC->FCPC0 = temp;
}

/**
 * @brief flash得到命令完成中断标志
 * @param None
 * @retval 中断状态标志
  *		这个参数可以取下面的值:
 *			@arg 0 ：闪存命令正在进行中
 *			@arg 1 ：闪存命令完成
 */
uint8_t FLASH_GetCmdFinshFlag(void)
{
	uint8_t sta;
	if((FMC->FSTAT & FMC_FSTAT_CCIF_MASK) == FMC_FSTAT_CCIF_MASK)
	{
		sta = 1;
	}
	else
	{
		sta = 0;
	}
	return sta; 
}



/**
 * @brief 获取存储器控制忙标志
 * @param None
 * @retval 存储器控制忙标志(Set or Reset)
 */
uint8_t FLASH_GetControllerBusyFlag(void)
{
	uint8_t sta;
	if((FMC->FSTAT & FMC_FSTAT_MGBUSY_MASK) == FMC_FSTAT_MGBUSY_MASK)
	{
		sta = 1;
	}
	else
	{
		sta = 0;
	}
	return sta; 
}

/**
 * @brief  flash清除闪存命令中断标志
 * @param None
 * @retval None
 */
void FLASH_LaunchCMD(void)
{
	/* Launch a command */ 
	FMC->FSTAT |= 0x80000000u; 
}

/**
 * @brief flash检测错误状态.
 * @param None
 * @retval 返回FLASH状态.
  *		这个参数可以取下面的值:
 *			@arg FLASH_ERR_ACCESS ：flash访问错误标志
 *			@arg FLASH_ERR_PROTECTION ：flash保护违反标志
 *			@arg FLASH_ERR_ECC ：ECC校验错误
 *			@arg FLASH_ERR_ERASEVERIFY ：擦除验证错误
 */
uint16_t FLASH_CheckErrStatus(void)
{
	
	uint16_t Errstatus;
	
	Errstatus = FLASH_ERR_SUCCESS;

	/* Access Error */
	if((FMC->FSTAT & FMC_FSTAT_ACCERR_MASK) == FMC_FSTAT_ACCERR_MASK)
	{
		Errstatus |= (uint16_t)FLASH_ERR_ACCESS;
	}
	
	/* Flash Protection Violation */	
	if((FMC->FSTAT & FMC_FSTAT_FPVIOL_MASK) == FMC_FSTAT_FPVIOL_MASK)
	{
		Errstatus |= (uint16_t)FLASH_ERR_PROTECTION;		
	}
	
	/* ECC error */		
	if((FMC->FSTAT & FMC_FSTAT_MGSTAT_MASK) == FLASH_FSTAT_MGSTAT0_MASK)
	{
		Errstatus |= (uint16_t)FLASH_ERR_ECC;		
	}
	
	/* erase verify error */		
	if((FMC->FSTAT & FMC_FSTAT_MGSTAT_MASK) == FLASH_FSTAT_MGSTAT1_MASK)
	{
		Errstatus |= (uint16_t)FLASH_ERR_ERASEVERIFY;		
	}
	return (Errstatus);
}

/**
 *
 * @brief flash编程两个字数据    
 * @param TargetAddress： 写入flash的地址
  *		这个参数可以取下面的值:
 *        DwData0：写入数据高字
 *        DwData1：写入数据低字
 * @return 返回flash error状态.
 */
uint16_t FLASH_Program2LongWord( uint32_t TargetAddress, uint32_t DwData0, uint32_t DwData1)
{
		
	uint16_t errorstatus;
	
	errorstatus = FLASH_ERR_SUCCESS;
	
	if((TargetAddress & 0x07u) != 0x00u)
	{
		errorstatus = FLASH_ERR_INVALID_PARAM;
	}
	else
	{
		// Clear error flags
		FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;	
		
		/* Write to specify the command code to be loaded */
		FMC->FCCOBF0 =(((uint32_t)FLASH_CMD_PROGRAM << FMC_FCCOBF0_FCMD_SHIFT)|(TargetAddress));
			
		/* Write to specify the Longword 0 program value to be loaded	*/	
		FMC->FCCOBF1 = DwData0;

		/* Write to specify the Longword 0 program value to be loaded	*/	
		FMC->FCCOBF2 = DwData1;
	}
	
	return (errorstatus);
}
/**
 * @brief Flash读双字数据
 * @param TargetAddress： 写入flash的地址
 * @retval 读出的数据
 */

uint64_t FLASH_ReadLongWord(const uint32_t *TargetAddress)
{
	uint32_t rdata1,rdata2;
	uint64_t data;
	
	rdata1 = TargetAddress[0];
	rdata2 = TargetAddress[1]; 
	
	data = ((uint64_t)rdata2 << 32) | (uint64_t)rdata1;
	
	return  data;
}


void FLASH_ReadLongWordCmd(uint32_t TargetAddress)
{

	FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_READ<<FMC_FCCOBF0_FCMD_SHIFT) | (TargetAddress);
	
	FLASH_LaunchCMD();

}

/**
 * @brief 擦除整个flash
 * @param None
 * @retval 返回FLASH状态.
 */
void FLASH_EraseChip(void)
{		

	FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;	
	
	/* Write to specify the command code to be loaded */
	FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_ERASE_CHIP << FMC_FCCOBF0_FCMD_SHIFT);
	
}

/**
 * @brief Flash扇区擦除
 * @param  TargetAddress: 擦除扇区的地址
 * @retval 返回FLASH状态.
 */
uint16_t FLASH_EraseSector( uint32_t TargetAddress)
{
	uint16_t errorstatus ;
	
	errorstatus = FLASH_ERR_SUCCESS;
	
	if((TargetAddress & 0x3FFu) != 0x000u)
	{
		errorstatus = FLASH_ERR_INVALID_PARAM;
	}
	else
	{
		// Clear error flags
		FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;
		
		/* Write to specify the command code to be loaded */ 
		FMC->FCCOBF0 = (((uint32_t)FLASH_CMD_ERASE_SECTOR << FMC_FCCOBF0_FCMD_SHIFT)| (TargetAddress));
		
	}
	
	return (errorstatus);
}

/**
 * @brief flash重启
 * @param None
 * @retval 返回FLASH状态.
 */
void FLASH_PowerOnReset(void)
{
	
	FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;
	
	/* Write to specify the command code to be loaded */
	FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_POWER_ON_RESET<< FMC_FCCOBF0_FCMD_SHIFT);
	
	/* Launch the command */
	FLASH_LaunchCMD();

}


/**
 * @brief 提供擦除扇区教研
 * @param  TargetAddress:擦除扇区的地址
 * @retval 返回FLASH操作的结果
 */
uint16_t FLASH_EraseVerifySector( uint32_t TargetAddress)
{
	uint16_t errorstatus = FLASH_ERR_SUCCESS;	

	if((TargetAddress & 0x3FFu) != 0x000u)
	{
		errorstatus = FLASH_ERR_INVALID_PARAM;
	}
	else
	{
		__disable_irq();
		// Clear error flags
		FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;	
		
		/* Write to specify the command code to be loaded */
		FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_ERASE_VERIFY_SECTOR<<FMC_FCCOBF0_FCMD_SHIFT) | (TargetAddress); 
		__enable_irq();
	}
	return (errorstatus);
}

/**
 * @brief Flash 擦除芯片操作会擦除整个flash记忆数据.
 * @param None
 * @retval 返回FLASH状态.
 */
void FLASH_EraseVerifyChip(void)
{
//	uint16_t errorstatus;		

	// Clear error flags
	FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;
	
	/* Write to specify the command code to be loaded */
	FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_ERASE_VERIFY_CHIP<<FMC_FCCOBF0_FCMD_SHIFT);
	
	/* Launch the command */
	FLASH_LaunchCMD();
}

/**
 * @brief Flash从新加载
 * @param None
 * @retval 返回FLASH状态.
 */
void FLASH_ConfigReload(void)
{
//	uint16_t errorstatus ;

	// Clear error flags
	FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;
	
	/* Write to specify the command code to be loaded */
	FMC->FRLD = FMC_FRLD_FRLD_MASK;
	
	/* Launch the command */
	FLASH_LaunchCMD();
}

/**
 * @brief flash安全配置.
 * @param None
 * @retval 返回FLASH安全配置.
 */
uint8_t FLASH_GetFlashSecurity(void)
{	
	uint8_t flashsecurity;

	/* Get the flash security configuration. */
	flashsecurity=(uint8_t)((FMC->FSTAT&FMC_FSTAT_SEC_MASK)>>FMC_FSTAT_SEC_SHIFT);

	return flashsecurity;
}

/**
 * @brief flash保护配置.
 * @param None
 * @retval 返回FLASH保护配置.
 */
uint8_t FLASH_GetFlashProtection(void)
{	
	uint8_t flashprotection;

	/* Get the flash protection configuration. */
	flashprotection=(uint8_t)((FMC->FOSP & FLASH_PROTECT_MASK)>>8u);
	
	return flashprotection;
}


/**
 * @brief flash选项配置.
 * @param None
 * @retval 返回FLASH选项配置.
 */
uint8_t FLASH_GetFlashOption(void)
{	
	uint8_t flashoption;

	/* Get the flash option configuration. */
	flashoption=(uint8_t)((FMC->FOSP&FMC_FOSP_FOPT_MASK)>>FMC_FOSP_FOPT_SHIFT);
	
	return flashoption;
}

/**
 * @brief  后门秘钥解锁.
 * @param  KeyHigh:后门秘钥高32位.
 * @param  Keylow:后门秘钥低32位.
 * @retval None.
 */
void FLASH_BackdoorUnlockFlash(uint32_t KeyHigh, uint32_t Keylow)
{
	FMC->KEYLOW = Keylow;
	FMC->KEYHIGH = (KeyHigh | FMC_FOSP_BACKDOOR_EN_MASK);
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





