#include "flash.h"
#include "xl_flash.h"
#include "xl_gpio.h"


bool_t LINFrameDetectedFlg = 0u;

uint16_t App_FlashEraseSector(uint32_t targetaddress,uint32_t time)
{
	uint8_t flag=0;
	uint16_t errorstatus;
	uint16_t reterror;
    uint32_t *lsr = (uint32_t *)(0x4006A014);
    uint32_t *rbr = (uint32_t *)(0x4006A000);

	errorstatus = FLASH_ERR_SUCCESS;
	
	if(FLASH_ERR_SUCCESS !=FLASH_EraseSector(targetaddress))  //擦除扇区
	{
		errorstatus = APP_FLASH_ERR_INVALID_PARAM;
	}
	else
	{
		__disable_irq();
		FLASH_LaunchCMD();	//加载命令
		while(0u == FLASH_GetCmdFinshFlag())//检测命令是否完成
		{
			time--;
			if(time<0x0F)
			{
				flag=1;
				reterror = APP_FLASH_ERR_ERASE_TIMEOUT;
				break;
			}

            if((*lsr & 0x10) || (*rbr == 0x55))
            {
                LINFrameDetectedFlg = 1u;
            }
		}
		if(!flag)
		{
			errorstatus=FLASH_CheckErrStatus();//flash状态
			switch(errorstatus)
			{
				case FLASH_ERR_INVALID_PARAM:
					reterror = APP_FLASH_ERR_INVALID_PARAM;
				break;
				case FLASH_ERR_ACCESS:
					reterror = APP_FLASH_ERR_ACCESS;
				break;
				case FLASH_ERR_PROTECTION:
					reterror = APP_FLASH_ERR_PROTECTION;
				break;
				case FLASH_ERR_ECC:
					reterror = APP_FLASH_ERR_ECC;
				break;
				case FLASH_ERR_ERASEVERIFY:
					reterror = APP_FLASH_ERR_ERASEVERIFY;
				break;
				case FLASH_ERR_INIT_CCIF:
					reterror = APP_FLASH_ERR_INIT_CCIF;
				break;
				case FLASH_ERR_INIT_CLKIM:
					reterror = APP_FLASH_ERR_INIT_CLKIM;
				break;
				default:
					reterror = APP_FLASH_ERR_SUCCESS;
				break;
			}
		}
	}
	__enable_irq();
	return reterror;
}

/*
*DwData0: 32Bits_L
*DwData1: 32Bits_H
*/
uint16_t App_FlashWriteData(uint32_t TargetAddress, uint32_t DwData0, uint32_t DwData1,uint32_t time)
{
	uint16_t errorstatus;
	uint8_t flag;
    uint32_t *lsr = (uint32_t *)(0x4006A014);
    uint32_t *rbr = (uint32_t *)(0x4006A000);

	errorstatus = FLASH_ERR_SUCCESS;
	
	if(FLASH_ERR_SUCCESS != FLASH_Program2LongWord( TargetAddress, DwData0, DwData1))//写入双字数据
	{
		errorstatus = FLASH_ERR_INVALID_PARAM;
	}
	else
	{
		__disable_irq();
		FLASH_LaunchCMD();	
	
		while(0u == FLASH_GetCmdFinshFlag())//检测命令是否完成
		{
			time--;
			if(time<0x0F)
			{
				flag=1;
				errorstatus = APP_FLASH_ERR_ERASE_TIMEOUT;
				break;
			}

            if((*lsr & 0x10) || (*rbr == 0x55))
            {
                LINFrameDetectedFlg = 1u;
            }
		}
		if(!flag)
		{
			errorstatus=FLASH_CheckErrStatus();//flash状态
			switch(errorstatus)
			{
				case FLASH_ERR_INVALID_PARAM:
					errorstatus = APP_FLASH_ERR_INVALID_PARAM;
				break;
				case FLASH_ERR_ACCESS:
					errorstatus = APP_FLASH_ERR_ACCESS;
				break;
				case FLASH_ERR_PROTECTION:
					errorstatus = APP_FLASH_ERR_PROTECTION;
				break;
				case FLASH_ERR_ECC:
					errorstatus = APP_FLASH_ERR_ECC;
				break;
				case FLASH_ERR_ERASEVERIFY:
					errorstatus = APP_FLASH_ERR_ERASEVERIFY;
				break;
				case FLASH_ERR_INIT_CCIF:
					errorstatus = APP_FLASH_ERR_INIT_CCIF;
				break;
				case FLASH_ERR_INIT_CLKIM:
					errorstatus = APP_FLASH_ERR_INIT_CLKIM;
				break;
				default:
					errorstatus = APP_FLASH_ERR_SUCCESS;
				break;
			}
		}
		__enable_irq();
	}
	return errorstatus;
}

uint64_t App_FlashReadData(uint32_t *TargetAddress)
{
	uint64_t data;
	__disable_irq();
	data = FLASH_ReadLongWord(TargetAddress);//读取双字数据
	__enable_irq();
	return data;
}




