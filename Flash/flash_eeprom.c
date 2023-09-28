#include "flash_eeprom.h"
#include "xl_gpio.h"
#include "debug.h"
#include "debug.h"
#if 1

#define VERIFIED_SECTOR_CONSUME_BYTE   8*VERIFIED_SECTOR_NUM

Flash_Eeprom_Type Flash_Eeprom;


uint32_t flash_hot_rand=0;


//uint16_t addr_temp=0;
//uint32_t data_temp=0;
//	
//uint8_t sector_index=0;
//uint32_t address=0;
//uint64_t read_data;

/**
*  
*/
EFLASH_STATUS EEFlash_Init(void)
{
	uint16_t flash_errorstatus = APP_FLASH_ERR_SUCCESS;
	EFLASH_STATUS errorstatus = EFLASH_ERROR_SUCCESS;
	uint16_t i=0;
	uint8_t j=0;
	uint32_t addr_sector_flag1[4];
	uint32_t Sector_Erase_Count[VERIFIED_SECTOR_NUM][2];
	uint8_t isUpdata=0;
	uint8_t max_erase_value;
	
	uint64_t addr_sector_flag[VERIFIED_SECTOR_NUM][2];
	
	uint32_t address=0;
	uint8_t sector_index=0;
	uint32_t addr_temp=0;
	uint32_t data_temp=0;
	uint64_t read_data;
	
	uint16_t ram_address=0;
	uint32_t reset_data[4];
	
	uint8_t flag=0;
	uint8_t first_flag=0;
	uint8_t erase_value_flag=0;

	
//	for(i=0;i<EEFLASH_SIZE;i++)
//	{
//		Flash_Eeprom.Data[i] = EFLASH_INIT_DATA;
//	}
	__disable_irq();
	for(i=0;i<VERIFIED_SECTOR_NUM;i++)
	{
		addr_sector_flag1[0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+1+i)*1024)-4));
		addr_sector_flag1[1] = FLASH_ReadLongWord((void *)(((VERIFIED_SECTOR_BASE+1+i)*1024)-8));
		addr_sector_flag1[2] = FLASH_ReadLongWord((void *)(((VERIFIED_SECTOR_BASE+VERIFIED_SECTOR_NUM+1+i)*1024)-4));
		addr_sector_flag1[3] = FLASH_ReadLongWord((void *)(((VERIFIED_SECTOR_BASE+VERIFIED_SECTOR_NUM+1+i)*1024)-8));
	
		addr_sector_flag[i][0] = (uint64_t)((uint64_t)addr_sector_flag1[1] << 32) + addr_sector_flag1[0];
		addr_sector_flag[i][1] = (uint64_t)((uint64_t)addr_sector_flag1[3] << 32) + addr_sector_flag1[2];
	}
	__enable_irq();
	
	for(i=0;i<VERIFIED_SECTOR_NUM;i++)
	{
		if(((addr_sector_flag[i][0] | 0x00000000FFFFFFFF)!=0x55AA55AAFFFFFFFF)&&((addr_sector_flag[i][1] | 0x00000000FFFFFFFF)!=0x55AA55AAFFFFFFFF))
		{
			continue;
		}
		else
		{
			first_flag=1;
			break;
		}
	}
	
	if(!first_flag)
	{
		for(i=0;i<VERIFIED_SECTOR_NUM*2;i++)
		{
			flash_errorstatus =App_FlashEraseSector(((VERIFIED_SECTOR_BASE+i)*1024u),30000);
			if(flash_errorstatus != APP_FLASH_ERR_SUCCESS)
			{
				if(flash_errorstatus == APP_FLASH_ERR_ERASE_TIMEOUT)
				{
					errorstatus = EFLASH_ERROR_FLASH_TIMEOUT;
				}
				else
				{
					errorstatus = EFLASH_ERROR_FLASH;
				}
				flag=1;
			}
			else
			{
				continue;
			}
		}
		if(!flag)
		{
			for(i=0;i<VERIFIED_SECTOR_NUM;i++)
			{
				Flash_Eeprom.Sector_EraseCount[i][0] = 1;//获取擦除的次数
				Flash_Eeprom.Sector_EraseCount[i][1] = 1;
				Flash_Eeprom.Sector_address[i] = (VERIFIED_SECTOR_BASE+i)*1024;//获取地址
			}
			
			for(i=0;i<VERIFIED_SECTOR_NUM;i++)
			{
				flash_errorstatus = App_FlashWriteData(((VERIFIED_SECTOR_BASE+i+1)*1024u)-8 , 0x55AA55AA, 0xFFFF0000 + ((uint32_t)i<<8),30000);
				if(flash_errorstatus != APP_FLASH_ERR_SUCCESS)
				{
					if(flash_errorstatus == APP_FLASH_ERR_ERASE_TIMEOUT)
					{
						errorstatus = EFLASH_ERROR_FLASH_TIMEOUT;
					}
					else
					{
						errorstatus = EFLASH_ERROR_FLASH;
					}
					flag=1;
				}
				else
				{
					flash_errorstatus = App_FlashWriteData(((VERIFIED_SECTOR_BASE+i+1)*1024u)-16 , Flash_Eeprom.Sector_EraseCount[i][0], Flash_Eeprom.Sector_EraseCount[i][0],30000);
					if(flash_errorstatus != APP_FLASH_ERR_SUCCESS)
					{
						if(flash_errorstatus == APP_FLASH_ERR_ERASE_TIMEOUT)
						{
							errorstatus = EFLASH_ERROR_FLASH_TIMEOUT;
						}
						else
						{
							errorstatus = EFLASH_ERROR_FLASH;
						}
						flag=1;
					}
					else
					{
						continue;
					}
				}
			}
		}
	}
	else
	{
		for(i=0;i<VERIFIED_SECTOR_NUM;i++)
		{
			if(((addr_sector_flag[i][0] | 0x00000000FFFFFFFF) == 0x55AA55AAFFFFFFFF)&&(addr_sector_flag[i][1] == 0xFFFFFFFFFFFFFFFF))
			{
				Sector_Erase_Count[i][0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-12));
				Sector_Erase_Count[i][1] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-16));		
				address = ((VERIFIED_SECTOR_BASE+i)*1024u);
				sector_index  = (uint8_t)((addr_sector_flag[i][0] & 0x000000000000FF00) >> 8);
			}
			else if((addr_sector_flag[i][0] == 0xFFFFFFFFFFFFFFFF)&&((addr_sector_flag[i][1] | 0x00000000FFFFFFFF) == 0x55AA55AAFFFFFFFF))
			{
				Sector_Erase_Count[i][0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-12));
				Sector_Erase_Count[i][1] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-16));

				address = ((VERIFIED_SECTOR_BASE+(i + VERIFIED_SECTOR_NUM))*1024u);
				sector_index  = (uint8_t)((addr_sector_flag[i][1] & 0x000000000000FF00) >> 8);
			}
			else if(((addr_sector_flag[i][0]| 0x00000000FFFFFFFF) == 0x55AA55AAFFFFFFFF)&&((addr_sector_flag[i][1] | 0x00000000FFFFFFFF) == 0x55AA55AAFFFFFFFF))
			{
				reset_data[0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-20));
				reset_data[1] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-24));
				reset_data[2] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-20));
				reset_data[3] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-24));
				
				if((reset_data[0] == 0xFFFFFFFF) && (reset_data[1] == 0xFFFFFFFF))
				{
					Sector_Erase_Count[i][0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-12));
					Sector_Erase_Count[i][1] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1))*1024u)-16));
					address = ((VERIFIED_SECTOR_BASE+i)*1024u);
					sector_index  = (uint8_t)((addr_sector_flag[i][0] & 0x000000000000FF00) >> 8);
				}
				else if((reset_data[3] == 0xFFFFFFFF) && (reset_data[2] == 0xFFFFFFFF))
				{
					Sector_Erase_Count[i][0] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-12));
					Sector_Erase_Count[i][1] = FLASH_ReadLongWord((void*)(((VERIFIED_SECTOR_BASE+(i+1+VERIFIED_SECTOR_NUM))*1024u)-16));

					address = ((VERIFIED_SECTOR_BASE+(i + VERIFIED_SECTOR_NUM))*1024u);
					sector_index  = (uint8_t)((addr_sector_flag[i][1] & 0x000000000000FF00) >> 8);
				}
				
			}
				
			Flash_Eeprom.Sector_EraseCount[sector_index][0] = (Sector_Erase_Count[i][0] & 0x00FFFFFF);
			Flash_Eeprom.Sector_EraseCount[sector_index][1] = (Sector_Erase_Count[i][1] & 0x00FFFFFF);
			
			Flash_Eeprom.Sector_EraseValue[sector_index][0] = (uint8_t)(Sector_Erase_Count[i][0] >> 24u);
			Flash_Eeprom.Sector_EraseValue[sector_index][1] = (uint8_t)(Sector_Erase_Count[i][1] >> 24u);
			Flash_Eeprom.Sector_address[sector_index] = address;
		}
		
		for(i=0;i<VERIFIED_SECTOR_NUM -1;i++)
		{
			if(Flash_Eeprom.Sector_EraseValue[i][0] != Flash_Eeprom.Sector_EraseValue[i+1][0])
			{
				if(Flash_Eeprom.Sector_EraseValue[i][0] > Flash_Eeprom.Sector_EraseValue[i+1][0])
				{
					max_erase_value = Flash_Eeprom.Sector_EraseValue[i][0];
					flash_hot_rand = (Flash_Eeprom.Sector_EraseValue[i+1][0]+1)*EEFLASH_HOT_SIZE;
				}
				else
				{
					max_erase_value = Flash_Eeprom.Sector_EraseValue[i+1][0];
					flash_hot_rand = (Flash_Eeprom.Sector_EraseValue[i][0]+1)*EEFLASH_HOT_SIZE;
				}
				erase_value_flag = 1;
				break;
			}
		}
		if(!erase_value_flag)
		{
			max_erase_value = Flash_Eeprom.Sector_EraseValue[i][0] + 1;
			flash_hot_rand = (Flash_Eeprom.Sector_EraseValue[i][0]+1)*EEFLASH_HOT_SIZE;
		}
		for(i=0;i<VERIFIED_SECTOR_NUM;i++)
		{
			if((Flash_Eeprom.Sector_EraseCount[i][0] > flash_hot_rand) || (Flash_Eeprom.Sector_EraseCount[i][1] > flash_hot_rand))
			{
				if((Flash_Eeprom.Sector_EraseValue[i][0] < flash_hot_rand/EEFLASH_HOT_SIZE)&&(Flash_Eeprom.Sector_EraseValue[i][1] < flash_hot_rand/EEFLASH_HOT_SIZE))
				{
					isUpdata=1;
					break;
				}
			}
		}
		
		if(isUpdata)
		{
			if(FLASH_ERR_SUCCESS != EEFlash_DisposalData(max_erase_value))
			{
				flag = 1;
			}
		}
	}
	
	if((first_flag) && (!flag))
	{
		for(j=0;j<VERIFIED_SECTOR_NUM;j++)
		{
			for(i=0;i<126;i++)
			{
				__disable_irq();
				read_data = FLASH_ReadLongWord((void*)(Flash_Eeprom.Sector_address[j] + 8*i));
				__enable_irq();
				addr_temp = (uint32_t)(read_data >> 32u);
				data_temp = (uint32_t)(read_data & 0xFFFFFFFF);
			
				ram_address = (uint16_t)addr_temp;
				
				if((addr_temp&0x0000FFFF) == 0x0000FFFF)
				{
					Flash_Eeprom.Point_Address[j] = i;
					break;
				}
				else
				{
					if(ram_address>4032)
					{
						//printf("i:%d  j:%d\r\n",i,j);
						__asm("WFI");
						//WIFI;
					}
//					Flash_Eeprom.Data[addr_temp] = (uint8_t)(data_temp>>24u);
//					Flash_Eeprom.Data[addr_temp+1] = (uint8_t)(data_temp>>16u);
//					Flash_Eeprom.Data[addr_temp+2] = (uint8_t)(data_temp>>8);
//					Flash_Eeprom.Data[addr_temp+3] = (uint8_t)data_temp;
					if((data_temp&0xFF000000) == 0xFF000000)
					{
						if((addr_temp & 0x01080000) == 0x01080000)
						{
							Flash_Eeprom.Data[ram_address] = (uint8_t)(data_temp>>24u);
						}
					}
					else
					{
						Flash_Eeprom.Data[ram_address] = (uint8_t)(data_temp>>24u);
					}
					
					if((data_temp&0x00FF0000) == 0x00FF0000)
					{
						if((addr_temp & 0x01040000) == 0x01040000)
						{
							Flash_Eeprom.Data[ram_address+1] = (uint8_t)(data_temp>>16u);
						}
					}
					else 
					{
						Flash_Eeprom.Data[ram_address+1] = (uint8_t)(data_temp>>16u);
					}
					
					if((data_temp&0x0000FF00) == 0x0000FF00)
					{
						if((addr_temp & 0x01020000) == 0x01020000)
						{
							Flash_Eeprom.Data[ram_address+2] = (uint8_t)(data_temp>>8u);
						}
					}
					else
					{
						Flash_Eeprom.Data[ram_address+2] = (uint8_t)(data_temp>>8u);
					}
					
					if((data_temp&0x000000FF) == 0x000000FF)
					{
						if((addr_temp & 0x01010000) == 0x01010000)
						{
							Flash_Eeprom.Data[ram_address+3] = (uint8_t)(data_temp);
						}
					}
					else
					{
						Flash_Eeprom.Data[ram_address+3] = (uint8_t)(data_temp);
					}
					
					//printf("i:%d  j:%d\r\n",i,j);
//					printf("index:%d   data:0x%x\r\n",addr_temp,Flash_Eeprom.Data[addr_temp]);
//					printf("index:%d   data:0x%x\r\n",addr_temp+1,Flash_Eeprom.Data[addr_temp+1]);
//					printf("index:%d   data:0x%x\r\n",addr_temp+2,Flash_Eeprom.Data[addr_temp+2]);
//					printf("index:%d   data:0x%x\r\n",addr_temp+3,Flash_Eeprom.Data[addr_temp+3]);
				}
			}
			if(Flash_Eeprom.Point_Address[j]>=125)
			{
				if(EFLASH_ERROR_SUCCESS != EEflash_Change_Page(j + EFLASH_WARNING_COVER_PAGE0))
				{
					errorstatus = EFLASH_ERROR_FLASH;
				}
			}
		}
	}	
	return errorstatus;
}


EFLASH_STATUS EEflash_DisposalChange_Page(uint8_t max_page, uint8_t min_page,uint32_t max_address, uint32_t min_address)
{
	EFLASH_STATUS errorstatus = FLASH_ERR_SUCCESS;
	uint16_t i=0;
	uint8_t flag=0;
	uint32_t max_tempH;
	uint32_t max_tempL;
	
	uint32_t min_tempH;
	uint32_t min_tempL;
	
	uint32_t max_write_address;
	uint32_t min_write_address;
	
	uint8_t max_write_address_flag;
	uint8_t min_write_address_flag;
	
	uint8_t max_point = 0;
	uint8_t min_point = 0;
	uint32_t max_erasecount[2] = {0};
	uint32_t min_erasecount[2] = {0};
	
	uint8_t min_erasevalue[2] = {0};
	uint8_t max_erasevalue[2] = {0};
	
	if(min_address >= VERIFIED_SECTOR_MIDLE)
	{
		min_write_address = min_address - VERIFIED_SECTOR_NUM*1024;
		min_write_address_flag = 0;
	}
	else
	{
		min_write_address = min_address + VERIFIED_SECTOR_NUM*1024;
		min_write_address_flag = 1;
	}
	
	if(max_address >= VERIFIED_SECTOR_MIDLE)
	{
		max_write_address = max_address - VERIFIED_SECTOR_NUM*1024;
		max_write_address_flag = 0;
	}
	else
	{
		max_write_address = max_address + VERIFIED_SECTOR_NUM*1024;
		max_write_address_flag = 1;
	}
	
	max_point = Flash_Eeprom.Point_Address[max_page];
	min_point = Flash_Eeprom.Point_Address[min_page];
	
	min_erasecount[0] = Flash_Eeprom.Sector_EraseCount[min_page][0];
	min_erasecount[1] = Flash_Eeprom.Sector_EraseCount[min_page][1];
	
	max_erasecount[0] = Flash_Eeprom.Sector_EraseCount[max_page][0];
	max_erasecount[1] = Flash_Eeprom.Sector_EraseCount[max_page][1];
	
	min_erasevalue[0] = Flash_Eeprom.Sector_EraseValue[min_page][0];
	min_erasevalue[1] = Flash_Eeprom.Sector_EraseValue[min_page][1];
	
	max_erasevalue[0] = Flash_Eeprom.Sector_EraseValue[max_page][0];
	max_erasevalue[1] = Flash_Eeprom.Sector_EraseValue[max_page][1];
	
	
	
	Flash_Eeprom.Point_Address[max_page] = 0;
	Flash_Eeprom.Point_Address[min_page] = 0;
	
	for(i=0;i<126;i++)
	{	
		max_tempH = FLASH_ReadLongWord((void*)(max_address + 8*i));//address
		max_tempL = FLASH_ReadLongWord((void*)(max_address + 8*i + 4));//data
		
		min_tempH = FLASH_ReadLongWord((void*)(min_address + 8*i));//address
		min_tempL = FLASH_ReadLongWord((void*)(min_address + 8*i + 4));//data

		if((max_tempH != 0xFFFFFFFF) && (max_tempL != 0xFFFFFFFF))
		{
			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(min_write_address + Flash_Eeprom.Point_Address[min_page]*8 , max_tempH, max_tempL,30000u))
			{
				flag = 1;
				errorstatus = EFLASH_ERROR_FLASH;
				Flash_Eeprom.Point_Address[max_page] = max_point;
				Flash_Eeprom.Point_Address[min_page] = min_point;
			}
			else
			{
				if((min_tempH != 0xFFFFFFFF) && (min_tempL != 0xFFFFFFFF))
				{
					if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(max_write_address + Flash_Eeprom.Point_Address[max_page]*8 , min_tempH, min_tempL,30000u))
					{
						flag = 1;
						errorstatus = EFLASH_ERROR_FLASH;
						Flash_Eeprom.Point_Address[max_page] = max_point;
						Flash_Eeprom.Point_Address[min_page] = min_point;
					}
					else
					{
						Flash_Eeprom.Point_Address[min_page]++;
						Flash_Eeprom.Point_Address[max_page]++;
					}
				}
			}
		}
	}
	
	
	if(!flag)
	{
		max_erasevalue[0]++;
		max_erasevalue[1]++;
	
		min_erasecount[0]++;
		min_erasecount[1]++;
	
		max_erasecount[0]++;
		max_erasecount[1]++;
		
		min_tempH = ((min_erasevalue[0] << 24u) + min_erasecount[0]);
		min_tempL = ((min_erasevalue[1] << 24u) + min_erasecount[1]);
		
		max_tempH = ((max_erasevalue[0] << 24u) + max_erasecount[0]);
		max_tempL = ((max_erasevalue[1] << 24u) + max_erasecount[1]);
		
		if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(max_write_address + 1024 - 16 , max_tempL, max_tempH,30000u))
		{
			flag = 1;
			errorstatus = EFLASH_ERROR_FLASH;
		}
		else
		{
			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(min_write_address + 1024 - 16 , min_tempL, min_tempH,30000u))
			{
				flag = 1;
				errorstatus = EFLASH_ERROR_FLASH;
			}
			else
			{
				if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(min_write_address + 1024 - 8 , 0x55AA55AA, (0xFFFF0000+(max_page<<8) + min_write_address_flag),30000u))
				{
					flag = 1;
					errorstatus = EFLASH_ERROR_FLASH;
				}
				else
				{
					if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(max_write_address + 1024 - 8 , 0x55AA55AA, (0xFFFF0000+(min_page<<8) + max_write_address_flag),30000u))
					{
						flag = 1;
						errorstatus = EFLASH_ERROR_FLASH;
					}
					else
					{
						
					}
				}
			}
		}
	}
	
	if(!flag)
	{
		if(APP_FLASH_ERR_SUCCESS != App_FlashEraseSector(min_address,30000))
		{
			errorstatus = EFLASH_ERROR_FLASH;
		}
		else
		{
			if(APP_FLASH_ERR_SUCCESS != App_FlashEraseSector(max_address,30000))
			{
				errorstatus = EFLASH_ERROR_FLASH;
			}
			else
			{
				Flash_Eeprom.Sector_address[max_page] = min_write_address;
				Flash_Eeprom.Sector_address[min_page] = max_write_address;
				
				Flash_Eeprom.Sector_EraseCount[max_page][0] = min_erasecount[0];
				Flash_Eeprom.Sector_EraseCount[max_page][1] = min_erasecount[1];
				Flash_Eeprom.Sector_EraseCount[min_page][0] = max_erasecount[0];
				Flash_Eeprom.Sector_EraseCount[min_page][1] = max_erasecount[1];
				
				Flash_Eeprom.Sector_EraseValue[min_page][0] = max_erasevalue[0];
				Flash_Eeprom.Sector_EraseValue[min_page][1] = max_erasevalue[1];
				
				Flash_Eeprom.Sector_EraseValue[max_page][0] = min_erasevalue[0];
				Flash_Eeprom.Sector_EraseValue[max_page][1] = min_erasevalue[1];
			}
		}
	}
	return errorstatus;
}

//uint32_t sector_erasecount[VERIFIED_SECTOR_NUM];
EFLASH_STATUS EEFlash_DisposalData(uint8_t erase_value)
{
	EFLASH_STATUS errorstatus = FLASH_ERR_SUCCESS;
	uint8_t i=0;
	uint8_t j=0;
	uint32_t sector_erasecount[VERIFIED_SECTOR_NUM];
//	uint8_t sector_index[VERIFIED_SECTOR_NUM];
//	uint8_t sector_Disposal[VERIFIED_SECTOR_NUM];
//	uint8_t sector_erasethreshold[VERIFIED_SECTOR_NUM][2];
	
//	uint32_t sector_erasevalue[2];
	
	uint32_t max_address = 0;
	uint32_t min_address = 0;
	
//	uint64_t sector_userflag=0;
	uint32_t sector_min=0;
	uint32_t sector_max=0;
	uint8_t sector_mintag=0;
	uint8_t sector_maxtag=0;
	uint8_t end_mintag=0;
	
	uint32_t old_address = 0;
	uint32_t new_address = 0;
	uint32_t tempH = 0;
	uint32_t tempL = 0;
	uint8_t point_address=0;
	uint8_t flag = 0;
	uint8_t min_write_address_flag = 0;
	
	uint32_t Sector_EraseH=0;
	uint32_t Sector_EraseL=0;
//	uint32_t sector_address[VERIFIED_SECTOR_NUM];
//	uint32_t sector_midaddress = (VERIFIED_SECTOR_BASE+VERIFIED_SECTOR_NUM)*1024;
//	uint32_t temp=0;

	for(i=0;i<VERIFIED_SECTOR_NUM;i++)
	{
		if(Flash_Eeprom.Sector_EraseValue[i][0] < erase_value)
		{
			sector_erasecount[j++] = Flash_Eeprom.Sector_EraseCount[i][0];
			end_mintag = i;
		}
	}

	if(j<=1)
	{

		old_address = Flash_Eeprom.Sector_address[end_mintag];
		point_address = Flash_Eeprom.Point_Address[end_mintag];
		Flash_Eeprom.Point_Address[end_mintag] = 0;
		if(old_address >= VERIFIED_SECTOR_MIDLE)
		{
			new_address = old_address - VERIFIED_SECTOR_NUM*1024;
			min_write_address_flag = 0;
		}
		else
		{
			new_address = old_address + VERIFIED_SECTOR_NUM*1024;
			min_write_address_flag = 1;
		}
		for(i=0;i<126;i++)
		{
			tempH = FLASH_ReadLongWord((void*)(old_address + 8*i));//data
			tempL = FLASH_ReadLongWord((void*)(old_address + 8*i + 4));//address		
			
			if((tempH != 0xFFFFFFFF) && (tempL != 0xFFFFFFFF))
			{
				if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(new_address + Flash_Eeprom.Point_Address[end_mintag]*8 , tempH, tempL,30000u))
				{
					flag = 1;
					errorstatus = EFLASH_ERROR_FLASH;
					Flash_Eeprom.Point_Address[end_mintag] = point_address;
					break;
				}
				else
				{
					Flash_Eeprom.Point_Address[end_mintag]++;
				}
			}
		}
		if(!flag)
		{
			Flash_Eeprom.Sector_EraseValue[end_mintag][0]++;
			Flash_Eeprom.Sector_EraseValue[end_mintag][1]++;
			
			if(old_address >= VERIFIED_SECTOR_MIDLE)
			{
				Flash_Eeprom.Sector_EraseCount[end_mintag][1]++;
			}
			else
			{
				Flash_Eeprom.Sector_EraseCount[end_mintag][0]++;
			}

			Sector_EraseH = (((uint32_t)Flash_Eeprom.Sector_EraseValue[end_mintag][1] << 24u) | (Flash_Eeprom.Sector_EraseCount[end_mintag][1]));
			Sector_EraseL = (((uint32_t)Flash_Eeprom.Sector_EraseValue[end_mintag][0] << 24u) | (Flash_Eeprom.Sector_EraseCount[end_mintag][0]));

			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData((uint32_t)(new_address + 1024 - 16) , Sector_EraseH, Sector_EraseL,30000u))
			{
				errorstatus = EFLASH_ERROR_FLASH;
			}
			else
			{
				if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(new_address + 1024 - 8 , 0x55AA55AA, (0xFFFF0000+((uint32_t)end_mintag<<8) + min_write_address_flag),30000u))
				{
					errorstatus = EFLASH_ERROR_FLASH;
				}
				else
				{
						if(APP_FLASH_ERR_SUCCESS != App_FlashEraseSector(old_address,30000))
						{
							errorstatus = EFLASH_ERROR_FLASH;
						}
						else
						{
							Flash_Eeprom.Sector_address[end_mintag] = new_address;
						}
				}
			}
		}
	}
	else
	{
		sector_min = sector_erasecount[0];
		sector_max = sector_erasecount[0];
		for(i=1;i<j;i++)
		{
			if(sector_min > sector_erasecount[i])
			{
				sector_min = sector_erasecount[i];
			}
			else if(sector_max < sector_erasecount[i])
			{
				sector_max = sector_erasecount[i];
			}
		}
		
		for(i=0;i<VERIFIED_SECTOR_NUM;i++)
		{
			if(sector_min == Flash_Eeprom.Sector_EraseCount[i][0])
			{
				sector_mintag = i;
				min_address = Flash_Eeprom.Sector_address[sector_mintag];
			}
			else if(sector_max == Flash_Eeprom.Sector_EraseCount[i][0])
			{
				if(Flash_Eeprom.Sector_EraseValue[i][0] < erase_value)
				{
					sector_maxtag = i;
					max_address = Flash_Eeprom.Sector_address[sector_maxtag];
				}
			}
			
			if((min_address > 0) && (max_address>0))
			{
				break;
			}
		}
		
		if(APP_FLASH_ERR_SUCCESS != EEflash_DisposalChange_Page(sector_maxtag, sector_mintag, max_address,  min_address))
		{
			errorstatus = EFLASH_ERROR_FLASH;
		}
	}
	return errorstatus;
}


EFLASH_STATUS EEflash_Write_1Byte(uint16_t addr, uint8_t data)
{
	EFLASH_STATUS errorstatus = FLASH_ERR_SUCCESS;
	uint32_t tempH;
	uint32_t tempL;
	uint32_t address_sector=0;
	uint32_t write_flag=0x0100;
	if(addr>=EEFLASH_SIZE)
	{
		errorstatus = EFLASH_ERROR_ADDRESS_OVERLOW;
	}
	else if((Flash_Eeprom.Data[addr] == data) && (data!=0))
	{
		errorstatus = FLASH_ERR_SUCCESS;
	}
	else
	{
		switch(addr%4)
		{
			case 0:
				tempH = addr;
				tempL = ((data<<24u) | ((uint32_t)Flash_Eeprom.Data[addr+1])<<16u  | ((uint32_t)Flash_Eeprom.Data[addr+2])<<8u | ((uint32_t)Flash_Eeprom.Data[addr+3]));
			break;
			case 1:
				tempH = addr-1;
				tempL = (((uint32_t)Flash_Eeprom.Data[addr-1]<<24u) | (data<<16u)  | ((uint32_t)Flash_Eeprom.Data[addr+1]<<8u) | ((uint32_t)Flash_Eeprom.Data[addr+2]));
			break;
			case 2:
				tempH = addr-2;
				tempL = (((uint32_t)Flash_Eeprom.Data[addr-2]<<24u) | ((uint32_t)Flash_Eeprom.Data[addr-1]<<16u)  | (data<<8u) | ((uint32_t)Flash_Eeprom.Data[addr+1]));
			break;
			case 3:
				tempH = addr-3;
				tempL = (((uint32_t)Flash_Eeprom.Data[addr-3]<<24u) | ((uint32_t)Flash_Eeprom.Data[addr-2]<<16u)  | ((uint32_t)Flash_Eeprom.Data[addr-1]<<8u) | (data));
			break;
		}
		
		if((tempL & 0x000000FF) == 0x000000FF)
		{
			write_flag = write_flag | (1);
		}
		if((tempL & 0x0000FF00) == 0x0000FF00)
		{
			write_flag = write_flag | (1<<1u);
		}
		if((tempL & 0x00FF0000) == 0x00FF0000)
		{
			write_flag = write_flag | (1<<2u);
		}
		if((tempL & 0xFF000000) == 0xFF000000)
		{
			write_flag = write_flag | (1<<3u);
		}
		
		tempH = tempH | (write_flag<<16u);
		address_sector = addr%(4*VERIFIED_SECTOR_NUM);
		
		if(Flash_Eeprom.Point_Address[address_sector>>2u]<125u)
		{
			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(Flash_Eeprom.Sector_address[address_sector>>2u] + Flash_Eeprom.Point_Address[address_sector>>2u]*8 , tempL, tempH,30000u))
			{
				errorstatus = EFLASH_ERROR_FLASH;

			}
			else
			{
				Flash_Eeprom.Data[addr] = data;
				Flash_Eeprom.Point_Address[address_sector>>2u]++;
			}
		}
		else if(Flash_Eeprom.Point_Address[address_sector>>2u] == 125u)
		{
			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(Flash_Eeprom.Sector_address[address_sector>>2u] + Flash_Eeprom.Point_Address[address_sector>>2u]*8 , tempL, tempH,30000u))
			{
				errorstatus = EFLASH_ERROR_FLASH;

			}
			else
			{
				Flash_Eeprom.Data[addr] = data;
				Flash_Eeprom.Point_Address[address_sector>>2u]++;
				errorstatus = (EFLASH_STATUS)((address_sector>>2u) + 7u);
			}
		}
		else
		{
			errorstatus = EFLASH_ERROR_ADDRESS;
		}
	}
	return errorstatus;
}

EFLASH_STATUS EEflash_Change_Page(EFLASH_STATUS page)
{
	EFLASH_STATUS errorstatus = EFLASH_ERROR_SUCCESS;
	uint16_t i=0;
	uint8_t j=0;
	//uint16_t eflash_max_size=0;
	uint16_t eflash_start_address=0;
	uint8_t flag=0;
	uint32_t tempH;
	uint32_t tempL;
	uint32_t erase_countH=0;
	uint32_t erase_countL=0;
	uint8_t page_sec_num;
	uint8_t page_sec_num_sub;
	uint32_t sector_newaddress = 0;
	uint32_t sector_oldaddress = 0;
//	uint32_t sector_address1 = 1;
	uint8_t point_address_copy=0;
	uint32_t write_flag=0x0100;
	page_sec_num = page - 7;
	//Flash_Eeprom.Point_Address[page_sec_num]=0;

	eflash_start_address = page_sec_num*4;
	sector_oldaddress = Flash_Eeprom.Sector_address[page_sec_num];
	
	if(sector_oldaddress >= VERIFIED_SECTOR_MIDLE)
	{
		sector_newaddress = sector_oldaddress - VERIFIED_SECTOR_NUM*1024;//0x2000;
		page_sec_num_sub = 0;
	}
	else
	{
		sector_newaddress = sector_oldaddress + VERIFIED_SECTOR_NUM*1024;
		page_sec_num_sub = 1;
	}
	
	for(i=eflash_start_address; i<EEFLASH_SIZE; i+=(4*VERIFIED_SECTOR_NUM))
	{
		for(j=0;j<4;j++)
		{
			write_flag = 0x0100;
//			if(Flash_Eeprom.Data[i+j] != EFLASH_INIT_DATA)
//			{
				switch(j)
				{
					case 0:
						tempH = i+j;
						tempL = (((uint32_t)Flash_Eeprom.Data[i+j])<<24u | ((uint32_t)Flash_Eeprom.Data[i+j+1])<<16u  | ((uint32_t)Flash_Eeprom.Data[i+j+2])<<8u | ((uint32_t)Flash_Eeprom.Data[i+j+3]));
					break;
					case 1:
						tempH = i+j-1;
						tempL = (((uint32_t)Flash_Eeprom.Data[i+j-1]<<24u) | (((uint32_t)Flash_Eeprom.Data[i+j])<<16u)  | ((uint32_t)Flash_Eeprom.Data[i+j+1]<<8u) | ((uint32_t)Flash_Eeprom.Data[i+j+2]));
					break;
					case 2:
						tempH = i+j-2;
						tempL = (((uint32_t)Flash_Eeprom.Data[i+j-2]<<24u) | ((uint32_t)Flash_Eeprom.Data[i+j-1]<<16u)  | (((uint32_t)Flash_Eeprom.Data[i+j])<<8u) | ((uint32_t)Flash_Eeprom.Data[i+j+1]));
					break;
					case 3:
						tempH = i+j-3;
						tempL = (((uint32_t)Flash_Eeprom.Data[i+j-3]<<24u) | ((uint32_t)Flash_Eeprom.Data[i+j-2]<<16u)  | ((uint32_t)Flash_Eeprom.Data[i+j-1]<<8u) | (((uint32_t)Flash_Eeprom.Data[i+j])));
					break;
				}
				
				if((tempL & 0x000000FF) == 0x000000FF)
				{
					write_flag = write_flag | (1);
				}
				if((tempL & 0x0000FF00) == 0x0000FF00)
				{
					write_flag = write_flag | (1<<1u);
				}
				if((tempL & 0x00FF0000) == 0x00FF0000)
				{
					write_flag = write_flag | (1<<2u);
				}
				if((tempL & 0xFF000000) == 0xFF000000)
				{
					write_flag = write_flag | (1<<3u);
				}
				
				tempH = tempH | (write_flag<<16u);
				
				if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(sector_newaddress + point_address_copy*8 , tempL, tempH,30000u))
				{
					errorstatus = EFLASH_ERROR_FLASH;
					flag=1;
					break;
				}
				else
				{
					point_address_copy++;
					break;
				}
				
//			}
		}
		if(flag)
		{
			break;
		}
	}
	if(!flag)
	{
		if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(sector_newaddress + 1024 - 8, 0x55AA55AA, 0xFFFF0000 + (uint32_t)(page_sec_num<<8) + page_sec_num_sub, 30000))
		{
			errorstatus = EFLASH_ERROR_FLASH;
		}
		else
		{
			if(sector_newaddress >= VERIFIED_SECTOR_MIDLE)
			{
				Flash_Eeprom.Sector_EraseCount[page_sec_num][1] ++;
			}
			else
			{
				Flash_Eeprom.Sector_EraseCount[page_sec_num][0] ++;
			}
			
			erase_countH = (((uint32_t)(Flash_Eeprom.Sector_EraseValue[page_sec_num][0]<<24u)) | Flash_Eeprom.Sector_EraseCount[page_sec_num][0]);
			erase_countL = (((uint32_t)(Flash_Eeprom.Sector_EraseValue[page_sec_num][1]<<24u)) | Flash_Eeprom.Sector_EraseCount[page_sec_num][1]);

			if(APP_FLASH_ERR_SUCCESS != App_FlashWriteData(sector_newaddress + 1024 - 16 ,erase_countH , erase_countL,30000))
			{
				errorstatus = EFLASH_ERROR_FLASH;
			}
			else
			{
				if(APP_FLASH_ERR_SUCCESS != App_FlashEraseSector(Flash_Eeprom.Sector_address[page_sec_num],30000))
				{
					errorstatus = EFLASH_ERROR_FLASH;
					if(Flash_Eeprom.Sector_address[page_sec_num] >= VERIFIED_SECTOR_MIDLE)
					{
						Flash_Eeprom.Sector_EraseCount[page_sec_num][1] --;
					}
					else
					{
						Flash_Eeprom.Sector_EraseCount[page_sec_num][0] --;
					}
				}
				else
				{
					Flash_Eeprom.Sector_address[page_sec_num] = sector_newaddress;
					Flash_Eeprom.Point_Address[page_sec_num]=point_address_copy;
					if(Flash_Eeprom.Point_Address[page_sec_num]>=125)
					{
						errorstatus = EFLASH_ERROR_ADDRESS_OVERLOW;
					}
				}
			}
		}
	}
	return errorstatus;
}



uint8_t EEflash_Read_Data(uint16_t addr)
{
	 return Flash_Eeprom.Data[addr];
}

#endif

