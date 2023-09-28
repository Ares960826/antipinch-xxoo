#ifndef FLASH_EEPROM_H__
#define FLASH_EEPROM_H__

#include "XL6600.h"
#include "xl_sim.h"
#include "xl_flash.h"
#include "flash.h"

#ifdef USE_EEFLASH_CONFING
	//#define EFLASH_INIT_DATA     0xFF
	#define EEFLASH_SIZE 	EFLASH_SIZE_1008_BYTE
	#define EEFLASH_HOT_SIZE     10
	
	
	#if (EEFLASH_SIZE == EFLASH_SIZE_504_BYTE)
		#define VERIFIED_SECTOR_NUM										2u
		#define VERIFIED_SECTOR_BASE									(252u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_756_BYTE)
		#define VERIFIED_SECTOR_NUM										3u
		#define VERIFIED_SECTOR_BASE									(250u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_1008_BYTE)
		#define VERIFIED_SECTOR_NUM										4u
		#define VERIFIED_SECTOR_BASE									(248u/2 - VERIFIED_SECTOR_NUM)
	
	#elif (EEFLASH_SIZE == EFLASH_SIZE_1260_BYTE)
		#define VERIFIED_SECTOR_NUM										5u
		#define VERIFIED_SECTOR_BASE									(246u/2 - VERIFIED_SECTOR_NUM)
			
	#elif (EEFLASH_SIZE == EFLASH_SIZE_1512_BYTE)
		#define VERIFIED_SECTOR_NUM										6u
		#define VERIFIED_SECTOR_BASE									(244u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_1764_BYTE)
		#define VERIFIED_SECTOR_NUM										7u
		#define VERIFIED_SECTOR_BASE									(242u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_2016_BYTE)
		#define VERIFIED_SECTOR_NUM										8u
		#define VERIFIED_SECTOR_BASE									(240u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_2268_BYTE)
		#define VERIFIED_SECTOR_NUM										9u
		#define VERIFIED_SECTOR_BASE									(238u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_2520_BYTE)
		#define VERIFIED_SECTOR_NUM										10u
		#define VERIFIED_SECTOR_BASE									(236u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_2772_BYTE)
		#define VERIFIED_SECTOR_NUM										11u
		#define VERIFIED_SECTOR_BASE									(234u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_3024_BYTE)
		#define VERIFIED_SECTOR_NUM										12u
		#define VERIFIED_SECTOR_BASE									(232u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_3276_BYTE)
		#define VERIFIED_SECTOR_NUM										13u
		#define VERIFIED_SECTOR_BASE									(230u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_3528_BYTE)
		#define VERIFIED_SECTOR_NUM										14u
		#define VERIFIED_SECTOR_BASE									(228u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_3780_BYTE)
		#define VERIFIED_SECTOR_NUM										15u
		#define VERIFIED_SECTOR_BASE									(226u/2 - VERIFIED_SECTOR_NUM)
		
	#elif (EEFLASH_SIZE == EFLASH_SIZE_4032_BYTE)
		#define VERIFIED_SECTOR_NUM										16u
		#define VERIFIED_SECTOR_BASE									(224u/2 - VERIFIED_SECTOR_NUM)
	#else
		#define VERIFIED_SECTOR_NUM										1u
		#define VERIFIED_SECTOR_BASE									(254u/2 - VERIFIED_SECTOR_NUM)
	#endif
		
	#define VERIFIED_SECTOR_MIDLE  (VERIFIED_SECTOR_BASE+VERIFIED_SECTOR_NUM)*1024
	
#endif


typedef struct 
{
      
  uint8_t Data[EEFLASH_SIZE];

	uint8_t Sector_EraseValue[VERIFIED_SECTOR_NUM][2];
	uint32_t Sector_EraseCount[VERIFIED_SECTOR_NUM][2];
	uint16_t Point_Address[VERIFIED_SECTOR_NUM];
	
	uint32_t Sector_address[VERIFIED_SECTOR_NUM];

}Flash_Eeprom_Type;
extern Flash_Eeprom_Type Flash_Eeprom;	

typedef enum
{
	EFLASH_ERROR_SUCCESS,
	EFLASH_ERROR_ADDRESS,
	EFLASH_ERROR_ADDRESS_OVERLOW,
	EFLASH_ERROR_ADDRESS_2BYTE_ALINE,
	EFLASH_ERROR_ADDRESS_4BYTE_ALINE,
	EFLASH_ERROR_FLASH,
	EFLASH_ERROR_FLASH_TIMEOUT,
	
	EFLASH_WARNING_COVER_PAGE0,
}EFLASH_STATUS;


EFLASH_STATUS EEFlash_Init(void);
EFLASH_STATUS EEflash_Change_Page(EFLASH_STATUS page);
EFLASH_STATUS EEflash_Write_1Byte(uint16_t addr, uint8_t data);
EFLASH_STATUS EEflash_Write_2Byte(uint16_t addr, uint16_t data);
EFLASH_STATUS EEflash_Write_4Byte(uint16_t addr, uint32_t data);
uint8_t EEflash_Read_Data(uint16_t addr);

EFLASH_STATUS EEFlash_DisposalData(uint8_t erase_value);
#endif 

