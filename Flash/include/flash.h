#ifndef FLASH_H__
#define FLASH_H__

#include "XL6600.h"
#include "xl_sim.h"
#include "xl_flash.h"


#ifndef DATA_FLASH_ADDRESS
	//#define DATA_FLASH_ADDRESS 0x0003C000
	#define DATA_FLASH_ADDRESS 0x00018000
#endif

#define USE_EEFLASH_CONFING

#ifdef USE_EEFLASH_CONFING
	#define EFLASH_SIZE_252_BYTE   252
	#define EFLASH_SIZE_504_BYTE   504
	#define EFLASH_SIZE_756_BYTE   756
	#define EFLASH_SIZE_1008_BYTE  1008
	#define EFLASH_SIZE_1260_BYTE  1260
	#define EFLASH_SIZE_1512_BYTE  1512
	#define EFLASH_SIZE_1764_BYTE  1764
	#define EFLASH_SIZE_2016_BYTE  2016
	#define EFLASH_SIZE_2268_BYTE  2268
	#define EFLASH_SIZE_2520_BYTE  2520
	#define EFLASH_SIZE_2772_BYTE  2772
	#define EFLASH_SIZE_3024_BYTE  3024
	#define EFLASH_SIZE_3276_BYTE  3276
	#define EFLASH_SIZE_3528_BYTE  3528
	#define EFLASH_SIZE_3780_BYTE  3780
	#define EFLASH_SIZE_4032_BYTE  4032 
#endif



#define APP_FLASH_ERR_BASE                    FLASH_ERR_BASE

#define APP_FLASH_ERR_SUCCESS									FLASH_ERR_SUCCESS
#define APP_FLASH_ERR_INVALID_PARAM						FLASH_ERR_INVALID_PARAM
#define APP_FLASH_ERR_ACCESS									FLASH_ERR_ACCESS
#define APP_FLASH_ERR_PROTECTION							FLASH_ERR_PROTECTION
#define APP_FLASH_ERR_ECC											FLASH_ERR_ECC
#define APP_FLASH_ERR_ERASEVERIFY							FLASH_ERR_ERASEVERIFY
#define APP_FLASH_ERR_INIT_CCIF								FLASH_ERR_INIT_CCIF
#define APP_FLASH_ERR_INIT_CLKIM							FLASH_ERR_INIT_CLKIM
#define APP_FLASH_ERR_ERASE_TIMEOUT						(APP_FLASH_ERR_BASE+0x20)



#ifndef FLASH_SECTOR_SIZE
	#define FLASH_SECTOR_SIZE 1024
#endif

#if defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__)

	#define __disable_irq()    __asm volatile("cpsid i")
	#define __enable_irq()    __asm volatile("cpsie i")

#endif

#ifndef DATA_FLASH_ADDRESS
	//#define DATA_FLASH_ADDRESS 0x0003C000
#endif


#ifndef FLASH_SECTOR_SIZE
	#define FLASH_SECTOR_SIZE 1024
#endif

#if defined(__GNUC__)
#undef _Init_Flash_Ram
#define _Init_Flash_Ram __attribute__((__section__(".flash_ram")))
#else
#undef _Init_Flash_Ram
#define _Init_Flash_Ram
#endif

extern bool_t LINFrameDetectedFlg;

typedef enum
{
	FLASH_STATUS_SUCCESS = FLASH_ERR_SUCCESS,
	FLASH_STATUS_INVALID_PARAM = FLASH_ERR_INVALID_PARAM,
	FLASH_STATUS_ACCESS	 = FLASH_ERR_ACCESS	,
	FLASH_STATUS_PROTECTION = FLASH_ERR_PROTECTION,
	FLASH_STATUS_ECC = FLASH_ERR_ECC,
	FLASH_STATUS_ERASEVERIFY = FLASH_ERR_ERASEVERIFY,
	FLASH_STATUS_INIT_CCIF = FLASH_ERR_INIT_CCIF,
	FLASH_STATUS_INIT_CLKIM = FLASH_ERR_INIT_CLKIM,
	FLASH_STATUS_TIMEOUT = 0x3FFF
}FLASH_STATUS;



uint16_t App_FlashEraseSector(uint32_t targetaddress,uint32_t time) __attribute__((__section__(".flash_ram")));
uint16_t App_FlashWriteData(uint32_t TargetAddress, uint32_t DwData0, uint32_t DwData1,uint32_t time) __attribute__((__section__(".flash_ram")));
uint64_t App_FlashReadData(uint32_t *TargetAddress) __attribute__((__section__(".flash_ram")));
#endif 




