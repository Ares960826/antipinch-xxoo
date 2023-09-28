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
 * @brief FLASH��ʼ��.
 * @param BusClock:��ǰFlashʱ��
 * @retval ����FLASH״̬.
   *		�����������ȡ�����ֵ:
 *			@arg FLASH_ERR_INIT_CCIF����������δ���
 *			@arg FLASH_ERR_INIT_CLK1M��CLK1M���� 
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
		 * Flash״̬�����벻һ�£����¼����״̬
		 * (1-210)15.4.1 Flash ״̬�Ĵ�����FSTAT��-> CCIF������ɱ�־*/
	 }
	 else
	 {
		 fcpco = FMC->FCPC0;
		 if(BusClockMhz>48u)
		 {
			 /* high speed ,>48Mhz  */
			 fcpco |= FMC_FCPC0_HSMD_MASK;/*
			 * (1-217)15.4.7 Flash �����������Ĵ�����FCPC0��->HSMD���õ��ٺ͸���FLASHʱ�����
			 * 0 - ʱ��ΪС�ڵ���48MHzʱ����Ϊ��0
			 * 1 - ʱ�Ӵ���48MHzʱ����λ������1������������FLASH��̲���ʧ��*/
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
 * @brief flash��������
 * @param FLASH_ProtectType:�����������ýṹ��
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
 * @brief flash��������ж�ʹ��.
 * @param  NewState��ѡ���Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISABLE ��ʧ��
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
 * @brief flash�ر�ECC����
 * @param  ecc_area��ѡ������򣬴�Flash������ַ���ϼ���
 *		�����������ȡ�����ֵ:
 *			@arg FLASH_ECC_DISABLE_AREA_0KB  ��0Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_1KB  ��1Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_2KB  ��2Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_4KB  ��4Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_8KB  ��8Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_16KB ��16Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_32KB ��32Kb������
 *			@arg FLASH_ECC_DISABLE_AREA_64KB ��64Kb������
 * @retval None
 */
void FLASH_DisableECCArea(uint8_t ecc_area)
{
	FMC->FCNFG |= (uint32_t)ecc_area;
}

/**
 * @brief flash  ��������
 * @param  NewState��ѡ���Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISABLE ��ʧ��
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
 * @brief flash��stopģʽ�½�������ģʽ
 * @param  NewState��ѡ���Ƿ�ʹ��״̬.
  *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISABLE ��ʧ��
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
 * @brief CLK1M��������ʹ��
 * @param  NewState��ѡ���Ƿ�ʹ��״̬.
  *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISABLE ��ʧ��
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
 * @brief ����flash��ȡ�ȴ����ں���
 *
 * @param ReadWaitCycle:��ȡ�ȴ����ڵĲ�������
 * @retval None
*/
void FLASH_SetReadWait(FLASH_ReadWaitCycleDef ReadWaitCycle)
{
  // ����ֲ�����temp,�����ݴ�FMC->FCPC0�Ĵ�����ֵ
  uint32_t temp;

  // ��ȡFMC->FCPC0�Ĵ�����ǰ��ֵ��temp
  // FMC����Flash Memory Controller,��flash�洢��������
  // FCPC0�����е�һ�����ƼĴ���
  temp = FMC->FCPC0;

  // ��temp��ֵ�뷴���RWCλ������������,��RWCλ����
  // RWCλ��������flash��ȡ�ȴ�����
  temp &= ~FMC_FCPC0_RWC_MASK;

  // ��ReadWaitCycle����FMC_FCPC0_RWC_SHIFTλ,�õ�RWC��ֵ
  // Ȼ����temp��������,����RWCλ��ֵ
  temp  |= ((uint32_t)ReadWaitCycle<<FMC_FCPC0_RWC_SHIFT);

  // ��������temp��ֵд��FMC->FCPC0,����flash��ȡ�ȴ�����
  FMC->FCPC0 = temp;
}

/**
 * @brief flash�õ���������жϱ�־
 * @param None
 * @retval �ж�״̬��־
  *		�����������ȡ�����ֵ:
 *			@arg 0 �������������ڽ�����
 *			@arg 1 �������������
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
 * @brief ��ȡ�洢������æ��־
 * @param None
 * @retval �洢������æ��־(Set or Reset)
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
 * @brief  flash������������жϱ�־
 * @param None
 * @retval None
 */
void FLASH_LaunchCMD(void)
{
	/* Launch a command */ 
	FMC->FSTAT |= 0x80000000u; 
}

/**
 * @brief flash������״̬.
 * @param None
 * @retval ����FLASH״̬.
  *		�����������ȡ�����ֵ:
 *			@arg FLASH_ERR_ACCESS ��flash���ʴ����־
 *			@arg FLASH_ERR_PROTECTION ��flash����Υ����־
 *			@arg FLASH_ERR_ECC ��ECCУ�����
 *			@arg FLASH_ERR_ERASEVERIFY ��������֤����
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
 * @brief flash�������������    
 * @param TargetAddress�� д��flash�ĵ�ַ
  *		�����������ȡ�����ֵ:
 *        DwData0��д�����ݸ���
 *        DwData1��д�����ݵ���
 * @return ����flash error״̬.
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
 * @brief Flash��˫������
 * @param TargetAddress�� д��flash�ĵ�ַ
 * @retval ����������
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
 * @brief ��������flash
 * @param None
 * @retval ����FLASH״̬.
 */
void FLASH_EraseChip(void)
{		

	FMC->FSTAT = FMC_FSTAT_FPVIOL_MASK|FMC_FSTAT_ACCERR_MASK;	
	
	/* Write to specify the command code to be loaded */
	FMC->FCCOBF0 = ((uint32_t)FLASH_CMD_ERASE_CHIP << FMC_FCCOBF0_FCMD_SHIFT);
	
}

/**
 * @brief Flash��������
 * @param  TargetAddress: ���������ĵ�ַ
 * @retval ����FLASH״̬.
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
 * @brief flash����
 * @param None
 * @retval ����FLASH״̬.
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
 * @brief �ṩ������������
 * @param  TargetAddress:���������ĵ�ַ
 * @retval ����FLASH�����Ľ��
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
 * @brief Flash ����оƬ�������������flash��������.
 * @param None
 * @retval ����FLASH״̬.
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
 * @brief Flash���¼���
 * @param None
 * @retval ����FLASH״̬.
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
 * @brief flash��ȫ����.
 * @param None
 * @retval ����FLASH��ȫ����.
 */
uint8_t FLASH_GetFlashSecurity(void)
{	
	uint8_t flashsecurity;

	/* Get the flash security configuration. */
	flashsecurity=(uint8_t)((FMC->FSTAT&FMC_FSTAT_SEC_MASK)>>FMC_FSTAT_SEC_SHIFT);

	return flashsecurity;
}

/**
 * @brief flash��������.
 * @param None
 * @retval ����FLASH��������.
 */
uint8_t FLASH_GetFlashProtection(void)
{	
	uint8_t flashprotection;

	/* Get the flash protection configuration. */
	flashprotection=(uint8_t)((FMC->FOSP & FLASH_PROTECT_MASK)>>8u);
	
	return flashprotection;
}


/**
 * @brief flashѡ������.
 * @param None
 * @retval ����FLASHѡ������.
 */
uint8_t FLASH_GetFlashOption(void)
{	
	uint8_t flashoption;

	/* Get the flash option configuration. */
	flashoption=(uint8_t)((FMC->FOSP&FMC_FOSP_FOPT_MASK)>>FMC_FOSP_FOPT_SHIFT);
	
	return flashoption;
}

/**
 * @brief  ������Կ����.
 * @param  KeyHigh:������Կ��32λ.
 * @param  Keylow:������Կ��32λ.
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





