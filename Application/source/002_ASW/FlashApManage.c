/*
 * FlashApManage.c
 *
 *  Created on: 2021Äê5ÔÂ11ÈÕ
 *      Author: lih
 */


/*
 * FlashAPManage.c
 *
 *  Created on: May 12, 2021
 *      Author: lih
 *
 * Release Record£º
 * Saving AP dynamic data into the allocated Flash
 * Reading AP dynamic data from the allocated Flash
 *
 * Ver1.0      May 12, 2021
 */

#include "system_XL6600.h"
#include "OS.h"
#include "xl_nvic.h"
#include "Types.h"
#include "Typedef.h"
#include "complier_sw.h"
#include "Hallpos.h"
#include "motor.h"
#include "param.h"
#include "apfunc.h"
#include "string.h"
#include "FlashApManage.h"
#include "xl_flash.h"
#include "flash.h"
#include "AppIF.h"

#define  FlashAp_Testing      1      //compiler knob just for FlashAP_Writing test


uint8_t FlashAp_DataBuf[Cells_DymAPDATA];


/**                      Private Function Declarations                         **
*******************************************************************************/
static signed char Get_active_block(uint32_t FlashDataSectorAds);

static void FlashAP_Fct_PrepareDataAds(void);

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


#define FlashAP_st_Waiting          0
#define FlashAP_st_WriteDataHeader  1
#define FlashAP_st_WriteAPData      2
#define FlashAP_st_ChkWrtResult     3

#define FlashAp_Sector_Size    		1024
#define FlashAp_Block_Size     		256
#define FlashAp_Sector_NUM      	2
#define FlashAp_Block_NUM      		4

#define BlkHeaderAdsBias  	0
#define BlkDataAdsBias 		8
#define BlkEndAdsBias  		248


#define FlashApDataSector0_Ads    0x07000
#define FlashApDataSector1_Ads    0x07400

#define BlockHeaderFlag     0x55aa55aa
#define BlockEndFlag        0xaa55aa55

#define FlashAp_WrtNUM           Cells_DymAPDATA/8

#define m_FlashAP_Enable_Writing     0x55AA

#define m_FlashAP_Disable_Writing    0xAA55

/*
Private variable

*/

uint16_t FlashAp_u16_StFlashWriting;   // rebound controller for FlashAP_Writing task

uint8_t FlashAP_u8_Writing_Status,FlashAp_u8_ErrorTryMax;


signed char FlashAP_s8_CurBlkCnt, FlashAP_s8_CurSctCnt;   //current ads where data are read
signed char FlashAP_s8_WrtBlkCnt, FlashAP_s8_WrtSctCnt;   //writing target ads when data will be written
uint16_t FlashAp_WrtCnt = 0;
uint16_t FlashAp_u16_EnableWriting;
uint32_t * FlashAp_p_WrtData;
uint32_t FlashAp_WrtTargetAds;




void  FlashAP_Init(void)
{
	FlashAp_u16_EnableWriting = m_FlashAP_Enable_Writing;
    FlashAp_u8_ErrorTryMax = 1;
}


/*
 *  Public function  FlashAP_Initiate_Save()
 *  Initiate FlashAp_writing task
 *  work with FlashAP_fct_Chk_WrtState()
 */
void  FlashAP_Initiate_Save(void)
{
	FlashAP_Fct_PrepareDataAds();
	FlashAP_u8_Writing_Status = FlashAP_st_WriteDataHeader;
}

/*
 *  Public function  FlashAP_fct_Chk_WrtState()
 *  return flag which indicates if  FlashAp_writing task is busy
 *  1: ok    come on
 *  0: busy  get out
 */

uint8_t  FlashAP_fct_Chk_WrtState(void)
{
   if(FlashAP_st_Waiting == FlashAP_u8_Writing_Status )
   {
	   return(TRUE);
   }
   return(FALSE);
}

uint8_t FlashAP_fct_Chk_WrtEnable(void)
{
	if(FlashAp_u16_EnableWriting == m_FlashAP_Enable_Writing)
	{
		return(TRUE);
	}
	return(FALSE);

}

/*
 *  Private function  Get_active_block
 *  Search valid block in current sector
 */

signed char Get_active_block( uint32_t t_FlashDataSectorAds )
{
	signed char   tmp8_a;
    unsigned char tmp8_cnt;
    uint8_t  *tmp8_A;
    uint32_t *tmp32_adsa, *tmp32_adsb;
	uint32  Tmp32_chksum;

	tmp8_a = 0x7f;
	for(tmp8_a = (FlashAp_Block_NUM-1); tmp8_a>=0; tmp8_a--)
	{
		tmp32_adsa = (uint32_t*)(t_FlashDataSectorAds + (tmp8_a)*FlashAp_Block_Size + BlkHeaderAdsBias);
		tmp32_adsb = (uint32_t*)(t_FlashDataSectorAds + (tmp8_a)*FlashAp_Block_Size + BlkEndAdsBias);

		if((BlockHeaderFlag == *tmp32_adsa)&&(BlockEndFlag == *tmp32_adsb))
		{
			Tmp32_chksum = 0;

			for(tmp8_cnt = 0;tmp8_cnt<Cells_DymAPDATA;tmp8_cnt++)
			{
				tmp8_A = (uint8_t *)(tmp32_adsa)+BlkDataAdsBias+tmp8_cnt;
				Tmp32_chksum += *tmp8_A;

			}

			if( Tmp32_chksum == *(tmp32_adsb+1)) return(tmp8_a);

		}

	}
	return(0x7f);//no valid data

}



/*
 *  DataBuff:   array saving dynamic AP parameters
 *  return value£º
 *  Data_buff[SIZE_DymAPDATA]
    FlashAP_s8_CurBlkCnt
    FlashAP_s8_CurSctCnt
 *
 *
 * */

uint8_t Flash_ReadApData(uint8_t DataID, uint8_t* Data_Buff)
{
	signed char  tmp8_blkcnt;
	signed char tmp8_sectorcnt,tmp_s8_rcnt;  //this variable must be signed char
	uint16_t tmp16_returnVal,tmp16_cnt;
	uint8 *tmp_p;

	FLASH_STATUS  Flash_status_a;

	tmp8_sectorcnt = 0xff;
	tmp8_blkcnt = 0xff;

    for(tmp8_sectorcnt = (FlashAp_Sector_NUM - 1); tmp8_sectorcnt>=0; tmp8_sectorcnt--)
    {
		tmp8_blkcnt = Get_active_block(FlashApDataSector0_Ads + tmp8_sectorcnt * FlashAp_Sector_Size);

		if (tmp8_blkcnt >= FlashAp_Block_NUM)
		{//no valid data in the sector,  Erase this sector
			tmp16_returnVal = App_FlashEraseSector(FlashApDataSector0_Ads + tmp8_sectorcnt * FlashAp_Sector_Size,30000);
		}
		else //if(tmp8_blkcnt < FlashAp_Block_NUM)
		{//get the valid data in the current sector

			FlashAP_s8_CurBlkCnt = tmp8_blkcnt;
			FlashAP_s8_CurSctCnt = tmp8_sectorcnt;
			//read data from defined flash
			tmp_p = (uint8 *)(FlashApDataSector0_Ads + tmp8_sectorcnt * FlashAp_Sector_Size + tmp8_blkcnt*FlashAp_Block_Size+BlkDataAdsBias);



			for(tmp16_cnt = 0; tmp16_cnt < SIZE_DymAPDATA; tmp16_cnt++)
			{
				*Data_Buff++ = *(tmp_p++);
			}


			if((FlashAp_Block_NUM-1)==FlashAP_s8_CurBlkCnt)
			{
				    if((FlashAp_Sector_NUM-1)!=FlashAP_s8_CurSctCnt)
				    {
						tmp_s8_rcnt = FlashAP_s8_CurSctCnt + 1;

						tmp_s8_rcnt %= FlashAp_Sector_NUM;
						{//if get data from the last sector, check if the first sector is virgin. if not, erase the first sector tmp8_sectorcnt=0

							tmp16_returnVal = App_FlashEraseSector(FlashApDataSector0_Ads + tmp_s8_rcnt*FlashAp_Sector_Size,30000);
						}
				    }
				    else
				    {
				    	for(tmp_s8_rcnt = 0;tmp_s8_rcnt <= (FlashAp_Sector_NUM-1); tmp_s8_rcnt++ )
				    	{
				    		tmp16_returnVal = App_FlashEraseSector(FlashApDataSector0_Ads + tmp_s8_rcnt*FlashAp_Sector_Size,30000);

				    	}


				    }
			}
			return(1);

		}
    }
    //when no valid data can be found, erase sector0 and set default
//    tmp16_returnVal = App_FlashEraseSector(FlashApDataSector0_Ads,30000);
	if(tmp8_sectorcnt<0)
	{//no valid sector can be found, erase sector if it is not a virgin zone
		FlashAP_s8_CurBlkCnt = -1;
		FlashAP_s8_CurSctCnt = 0;
    	for(tmp_s8_rcnt = 0;tmp_s8_rcnt <= (FlashAp_Sector_NUM-1); tmp_s8_rcnt++ )
    	{
    		tmp16_returnVal = App_FlashEraseSector(FlashApDataSector0_Ads + tmp_s8_rcnt*FlashAp_Sector_Size,30000);

    	}


		return(0);
	}
}

void FlashAP_Fct_PrepSrcData(void)
{
	unsigned char   Tmp8_len,Tmp8_cnt;
	// Prepare data
		Tmp8_len = HP_SaveData(&FlashAp_DataBuf[0]);
		Tmp8_len+= BAT_SaveData(&FlashAp_DataBuf[Tmp8_len]);
		Tmp8_len+= MOT_SaveData(&FlashAp_DataBuf[Tmp8_len]);
		Tmp8_len+= APL_SaveData(&FlashAp_DataBuf[Tmp8_len]);

		FlashAp_p_WrtData = (uint32_t *)FlashAp_DataBuf;
}

void  FlashAP_Fct_PrepTgtAds(void)
{
	//get target address


		if((FlashAp_Block_NUM-1) == FlashAP_s8_CurBlkCnt)
		{//change to the other sector because the current block is already the last block of current sector
			FlashAP_s8_WrtSctCnt = FlashAP_s8_CurSctCnt +1;
			FlashAP_s8_WrtSctCnt  %= FlashAp_Sector_NUM;
			FlashAP_s8_WrtBlkCnt = 0;
		}
		else
		{
			FlashAP_s8_WrtSctCnt = FlashAP_s8_CurSctCnt;
			FlashAP_s8_WrtBlkCnt = FlashAP_s8_CurBlkCnt+1;
		}

}

void FlashAP_Fct_PrepareDataAds(void)
{
	FlashAP_Fct_PrepSrcData();

	FlashAP_Fct_PrepTgtAds();


}





/*
 *
 * Public function void FlashAP_task_WriteApData(void)
 *
Private variables:
uint8_t FlashAP_u8_CurBlkCnt, FlashAP_u8_CurSctCnt;
uint8_t FlashAP_u8_WrtBlkCnt, FlashAP_u8_WrtSctCnt;
uint8_t FlashAP_u8_Writing_Status;



*/
void FlashAP_task_WriteApData(void)
{
	unsigned char *Tmp8p_cnta;
	unsigned char *Tmp8p_cntb;


	uint32_t  Tmp32_Data0,Tmp32_Data1,Tmp32_chksum;

	uint16_t  Tmp16_FctRtn;
	unsigned char   Tmp8_len,Tmp8_cnt, tmp8_a,tmp8_b;


	if(FlashAp_u16_EnableWriting != m_FlashAP_Enable_Writing)
	{

	}
	else
	{

		switch(FlashAP_u8_Writing_Status)
		{
			case FlashAP_st_Waiting:
				break;
			case FlashAP_st_WriteDataHeader:
			//write block header
				FlashAp_WrtTargetAds = FlashApDataSector0_Ads +FlashAP_s8_WrtSctCnt*FlashAp_Sector_Size+FlashAP_s8_WrtBlkCnt*FlashAp_Block_Size;

				Tmp32_Data0 = BlockHeaderFlag;
				Tmp32_Data1 = 0xffff;

				Tmp16_FctRtn = App_FlashWriteData(FlashAp_WrtTargetAds, Tmp32_Data0,Tmp32_Data1,30000);

			//turn to other state which will activated in next time window.
				FlashAp_WrtTargetAds +=BlkDataAdsBias;
				FlashAp_WrtCnt = 0;
				FlashAP_u8_Writing_Status = FlashAP_st_WriteAPData;

				break;

			case FlashAP_st_WriteAPData:

				if(FlashAp_WrtCnt <FlashAp_WrtNUM )
				{
					Tmp32_Data0 = *FlashAp_p_WrtData++;
					Tmp32_Data1 = *FlashAp_p_WrtData++;
					Tmp16_FctRtn = App_FlashWriteData(FlashAp_WrtTargetAds + FlashAp_WrtCnt*8, Tmp32_Data0,Tmp32_Data1,30000);
					FlashAp_WrtCnt++;
				}
				else
				{// after programming data check it
					FlashAp_WrtTargetAds = FlashApDataSector0_Ads +FlashAP_s8_WrtSctCnt*FlashAp_Sector_Size+FlashAP_s8_WrtBlkCnt*FlashAp_Block_Size;
					FlashAP_u8_Writing_Status = FlashAP_st_ChkWrtResult;

				}
				break;

			case FlashAP_st_ChkWrtResult:
				//compare the data between the flash and the data buffer
				Tmp8p_cnta =  FlashAp_DataBuf;
				Tmp8p_cntb =  (uint8_t* )(FlashAp_WrtTargetAds+BlkDataAdsBias);

				Tmp32_chksum = 0;
				for(Tmp8_cnt = 0;Tmp8_cnt<Cells_DymAPDATA;Tmp8_cnt++)
				{

					Tmp32_chksum += *Tmp8p_cntb;

					if(*Tmp8p_cnta++ != *Tmp8p_cntb++)
					{
						break;
					}

				}

				if(Cells_DymAPDATA == Tmp8_cnt)
				{//if comparing result is OK, writing block-end to defined ads
//					Tmp16_FctRtn = App_FlashWriteData(FlashAp_WrtTargetAds + BlkEndAdsBias, BlockEndFlag,0xffff,30000);
					Tmp16_FctRtn = App_FlashWriteData(FlashAp_WrtTargetAds + BlkEndAdsBias, BlockEndFlag,Tmp32_chksum,30000);

					FlashAp_u16_EnableWriting = m_FlashAP_Disable_Writing;
					FlashAP_u8_Writing_Status = FlashAP_st_Waiting;
				}
				else
				{//current data writing is fail, try again
				 //2021-5-10 later new strategy will be adopted	  ...  only try twice maybe
					// sector erasing is possible, so that the dog need feeding.
					bsc_FeedCOP();


					if(FlashAp_u8_ErrorTryMax > 0 )
					{//provide twice writing access
						FlashAp_u8_ErrorTryMax--;
						FlashAP_Fct_PrepSrcData();

						//get target address

						if((FlashAp_Block_NUM-1)>FlashAP_s8_WrtBlkCnt)
						{
							FlashAP_s8_WrtBlkCnt +=1;
						}
						else
						{
								if((FlashAp_Sector_NUM-1) > FlashAP_s8_WrtSctCnt)
								{
									FlashAP_s8_WrtSctCnt += 1;
									FlashAP_s8_WrtBlkCnt = 0;

									Tmp16_FctRtn = App_FlashEraseSector(FlashApDataSector0_Ads + FlashAP_s8_WrtSctCnt*FlashAp_Sector_Size,30000);
								}
								else
								{
									for(Tmp8_cnt = 0;Tmp8_cnt <= (FlashAp_Sector_NUM-1); Tmp8_cnt++ )
									{
										Tmp16_FctRtn = App_FlashEraseSector(FlashApDataSector0_Ads + Tmp8_cnt*FlashAp_Sector_Size,30000);
									}
									FlashAP_s8_WrtSctCnt = 0;
									FlashAP_s8_WrtBlkCnt = 0;
								}
						}

						FlashAp_u16_EnableWriting = m_FlashAP_Enable_Writing;
						FlashAP_u8_Writing_Status = FlashAP_st_WriteDataHeader;


					}
					else
					{//no opportunity, just erased sector and exit
						for(Tmp8_cnt = 0;Tmp8_cnt <= (FlashAp_Sector_NUM-1); Tmp8_cnt++ )
						{
							Tmp16_FctRtn = App_FlashEraseSector(FlashApDataSector0_Ads + Tmp8_cnt*FlashAp_Sector_Size,30000);
						}
						FlashAP_s8_WrtSctCnt = 0;
						FlashAP_s8_WrtBlkCnt = 0;


						FlashAp_u16_EnableWriting = m_FlashAP_Disable_Writing;
						FlashAP_u8_Writing_Status = FlashAP_st_Waiting;

					}

				}

				break;

			default:
				break;

		}
	}
}



void FlashAp_ReadWriteTest(void)
{
#if FlashAp_Testing

/* step1  Read data from the defined address
   step2  assign data
   step3  write data with interval call
   step4  check data

	write expected data to defined address
*/
	uint16_t tmp16_return;
	uint16_t tmp16_i, tmp16_cnt;
	uint16_t Tmp16_testcycle;


	uint8_t tmp8_return;


	FlashAP_Initiate_Save();

    for(Tmp16_testcycle=0; Tmp16_testcycle < 50000; Tmp16_testcycle++)
    {

		tmp16_return = App_FlashEraseSector(FlashApDataSector0_Ads + 0 * FlashAp_Sector_Size,30000);

		tmp16_return = App_FlashEraseSector(FlashApDataSector0_Ads + 1 * FlashAp_Sector_Size,30000);

	//block0_sector0
		(void)Flash_ReadApData(0,FlashAp_DataBuf);
		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+1;
		}
		do
		{
		  FlashAP_task_WriteApData();
//		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}

		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

	//block1_sector0
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+2;
		}


		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);




	//block2_sector0
		(void)Flash_ReadApData(0,FlashAp_DataBuf);
		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+3;
		}



		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

	//block3_sector0
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+4;
		}


		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

	//block0_sector1
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+5;
		}

		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}

		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

	//block1_sector1
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+6;
		}

		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);



	//block2_sector1
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+6;
		}


		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

	//block3_sector1
		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt+7;
		}


		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}
		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);
	//block0_sector0
		(void)Flash_ReadApData(0,FlashAp_DataBuf);
		FlashAP_Init();
		FlashAP_Initiate_Save();
		for(tmp16_cnt = 0; tmp16_cnt<Cells_DymAPDATA;tmp16_cnt++ )
		{
			FlashAp_DataBuf[tmp16_cnt] = 0xff-tmp16_cnt;
		}

		do
		{
		  FlashAP_task_WriteApData();
		  for(tmp16_cnt = 0; tmp16_cnt<30000;tmp16_cnt++){}

		}while(0==FlashAP_fct_Chk_WrtState());

		tmp8_return = Flash_ReadApData(0,FlashAp_DataBuf);

    }
//
//
	while(1);
#endif
}


//uint8_t Get_active_block_old( uint32_t t_FlashDataSectorAds )
//{
//// App_FlashEraseVerifySector() can not work;
//	//so this function is abandoned.
//
//	signed char   tmp8_a;
//	uint32_t *tmp32_adsa, *tmp32_adsb;
//
//	FLASH_STATUS  Flash_status_a;
//	Flash_status_a = App_FlashEraseVerifySector(t_FlashDataSectorAds,30000);
//
//	tmp8_a = 0xff;
//
//;
//
//	if(FLASH_ERR_SUCCESS !=Flash_status_a)
//	{
//		for(tmp8_a = (FlashAp_Block_NUM-1); tmp8_a>=0; tmp8_a--)
//		{
//			tmp32_adsa = (uint32_t*)(t_FlashDataSectorAds + tmp8_a*FlashAp_Block_Size + BlkHeaderAdsBias);
//			tmp32_adsb = (uint32_t*)(t_FlashDataSectorAds + tmp8_a*FlashAp_Block_Size + BlkEndAdsBias);
//
//			if((BlockHeaderFlag == *tmp32_adsa)&&(BlockEndFlag == *tmp32_adsb))
//			{
//				return(tmp8_a);
//			}
//		}
//		return(0xff);
//	}
//	else
//	{
////		return(FlashAp_Block_NUM);//current block is virgin sector
//		return(0xff);//current block is virgin sector
//	}
//
//}
