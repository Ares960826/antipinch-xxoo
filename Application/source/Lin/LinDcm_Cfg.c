/*******************************************************************************
|  File Name:    LinDcm_Cfg.c
|  Description:  Lin Diagnostic Config Source file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170324	   0.01       	$BAb5~(B          	$B=iHG(B
|******************************************************************************/

#include "Typedef.h"
#include "flash.h"
#include "complier_sw.h"
#include "LinDcm.h"
#include "LinDcm_Cfg.h"
#include "appl_const.h"
#include "testmode.h"

//#include "relaytst.h"

/* CRC16 polynomial */
#define CRC_POLYNOMIAL_16           (0X1021U)

typedef struct
{
	uint32_t AddrBeg;
    uint32_t Size;
} Fls_AddrRange_t;

/*******************************************************************************
Name			: Dcm22_ReadProductInfo
Syntax			: static uint16_t Dcm22_ReadProductInfo(uint8_t Data[])
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: $22$BI~(B?$B!$(B?$B<h(B?$BIJ9E7o!$(B?$B7o5ZB6B>?.B)(B
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170331	$B=$2~7A;2(B?$B?t(B?$B;X(B?
|******************************************************************************/
static uint16_t Dcm22_ReadProductInfo(uint8_t Data[]);

static uint16_t Dcm22_ReadDatas(uint8_t Data[]);

/*******************************************************************************
Name			: Dcm22_ReadCalibrationVersion
Syntax			: static uint16_t Dcm22_ReadCalibrationVersion(uint8_t Data[])
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: $22$BI~(B?$B!$(B?$B<h(B?$BDj;2?tHGK\(B
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170331	$B=$2~7A;2(B?$B7?(B?$B?t(B?$B;X(B?
|******************************************************************************/
static uint16_t Dcm22_ReadCalibrationVersion(uint8_t Data[]);
void Read_Cheksum_Version(uint8_t Data[]);

static uint16_t Dcm22_ReadFuncData(uint8_t Data[]);

/*******************************************************************************
Name			: Crc_CalculateCRC16
Syntax			: static uint16_t Crc_CalculateCRC16(uint16_t Crc_Length,uint8_t  Crc_DataPtr[],uint16_t InitCrc)
Parameters(in)	:	Crc_Length	: $B9;(B?$B?t?x(B?$BEY(B
					Crc_DataPtr : $B9;(B?$B?t?x;X(B?
					InitCrc		: $B=i;O(BCrc?
Parameters(out) : None
Return value	: 16$B0L(BCrc$B9;(B??
Description		: 16$B0L(BCrc$B9;(B?
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170328	$B2CF~=i;O2=(BCrc?$B:n(B?$B7A;2(B
3			$BAb5~(B		20170331	$B=$2~7A;2(B?$B7?(B?$B?t(B?$B;X(B?
|******************************************************************************/
static uint16_t Crc_CalculateCRC16(uint16_t Crc_Length,uint8_t  Crc_DataPtr[],uint16_t InitCrc);

static bool_t Fls_ChkAddrValid(const Fls_AddrRange_t AddrInfo[],uint32_t Addr);


/*
 * 	$B<{MW(B?$BCVE*;2?tNsI=(B
 */

/*	$22$BI~(B??$B<h?t?x;2?tNsI=(B	*/
const Dcm_ReadDidRowType Dcm_ReadDidRow[DCM_READDID_NUM] =
{
		/*	?$B<h(BID						  $B?t?x(B?$B<hH!?t(B		*/
		{DCM_READDID_INFORMATION,		&Dcm22_ReadProductInfo},
		{DCM_READDID_CALIBRATION_VER,	&Dcm22_ReadCalibrationVersion},
		{DCM_READDID_DATAS,	&Dcm22_ReadFuncData},

};

/*	$2E$BI~(B?$B<LF~?t?x;2?tNsI=(B	*/
const Dcm_WriteDidRowType Dcm_WriteDidRow[DCM_WRITEDID_NUM] =
{
    /*  $B<L(BID	    $B?t?xBg>.(B	    $B<LF~?t?xCOT.(B	*/


    {0x01D0U,   128U,       (uint8_t *)0x00006C00U},
    {0x01D1U,   128U,       (uint8_t *)0x00006C80U},
    {0x01D2U,   128U,       (uint8_t *)0x00006D00U},

	{0xC00CU,   32U,        (uint8_t *)0x00006F00U},//6F00
    //{0x01D3U,   128U,       (uint8_t *)0x00006D80U}
    //{0x01D4U,   128U,       (uint8_t *)0x00006E00U}
    //{0x01D5U,   128U,       (uint8_t *)0x00006E80U},
    //{0x01D6U,   128U,       (uint8_t *)0x00006F00U},
    //{0x01D7U,   128U,       (uint8_t *)0x00006F80U}   //DID$B992~(B 01D7 32U$B2~@.(BFLS_PAGESIZE
};

/*
 * EOF	$B;2?tNsI=(B
 */
const uint8_t SwVer[4] = {SW_ID,'1','0','1'};  //SW_ID$B^1$(DH2(B?$B[9zd(B?$(De:$B'e(B?$(De^8%(B???2019-3-1
const uint8_t HwVer[3] = {'C','1','1'};   //C12
//const uint8_t PaVer[2] = {'0','1'};

/*
#ifdef DOOR_FL
	__attribute__((section(".static_data"),used)) const uint8_t DoorTyp[2] = {'2','0'};
#endif
#ifdef DOOR_FR
	__attribute__((section(".static_data"),used)) const uint8_t DoorTyp[2] = {'2','1'};
#endif
#ifdef DOOR_RL
	__attribute__((section(".static_data"),used)) const uint8_t DoorTyp[2] = {'2','2'};
#endif
#ifdef DOOR_RR
	__attribute__((section(".static_data"),used)) const uint8_t DoorTyp[2] = {'2','3'};
#endif
*/

const Fls_AddrRange_t FlashValidAddr =
{
    FLS_FACTORY_MSG_BASICADDR,0x800U
};



static uint16_t Dcm22_ReadFuncData(uint8_t Data[])
{

    uint8_t ldm_t;

    RT_OtherTestDataLoad_2();
    for(ldm_t=0;ldm_t<10;ldm_t++)
    Data[ldm_t] =RT_uc_DCMBuf[ldm_t];

    return 10U;
}



/*******************************************************************************
Name			: Dcm22_ReadProductInfo
Syntax			: static uint16_t Dcm22_ReadProductInfo(uint8_t Data[])
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: $22$BI~(B?$B!$(B?$B<h(B?$BIJ9E7o!$(B?$B7o5ZB6B>?.B)(B
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170331	$B=$2~7A;2(B?$B?t(B?$B;X(B?
|******************************************************************************/
static uint16_t Dcm22_ReadProductInfo(uint8_t Data[])
{
    Data[0] = 0U;
    Data[1] = 0U;
    Data[2] = 0U;
    Data[3] = 0U;
    Data[4] = 0U;
    Data[5] = 0U;
    Data[6] = 0U;
    Data[7] = 0U;
    Data[8] = SwVer[0];
    Data[9] = SwVer[1];
    Data[10] = SwVer[2];
    Data[11] = SwVer[3];

    Data[12] = HwVer[0];
    Data[13] = HwVer[1];
    Data[14] = HwVer[2];

    Data[15] = ((c_ee_Par_Ver>>4)&0x0F)+0x30;//PaVer[0];
    Data[16] = (c_ee_Par_Ver&0x0F)+0x30;//PaVer[1];

    Data[17] = ((c_ee_Par_DoorType>>4)&0x0F)+0x30;
    Data[18] = (c_ee_Par_DoorType&0x0F)+0x30;

    return 19U;
}

/*******************************************************************************
Name			: Dcm22_ReadDatas
Syntax			: static uint16_t Dcm22_ReadDatas(uint8_t Data[])
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: $22$BI~(B?$B!$(B?$B<h(B:?????
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1:xulei 20190712 add the function : DID-0XD00D-read-datas.
|******************************************************************************/
static uint16_t Dcm22_ReadDatas(uint8_t Data[])
{

		Data[0] = 0;
    Data[1] = 0;
    Data[2] = 0;
    Data[3] = 0;
    Data[4] = 0;
    Data[5] = 0;
    Data[6] = 0;
    Data[7] = 0;
    Data[8] = 0;
    Data[9] = 0;
    return 10U;
}

/*******************************************************************************
Name			: Dcm22_ReadCalibrationVersion
Syntax			: static uint16_t Dcm22_ReadCalibrationVersion(uint8_t Data[])
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: $22$BI~(B?$B!$(B?$B<h(B?$BDj;2?tHGK\(B
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170331	$B=$2~7A;2(B?$B7?(B?$B?t(B?$B;X(B?$B!$M3;X(B?$BA`:n2~(B?$B?t(B?$B:w0zA`:n(B
|******************************************************************************/
static uint16_t Dcm22_ReadCalibrationVersion(uint8_t Data[])
{
	uint16_t Crc = 0U;
	uint8_t Index;
	for(Index = 0U;Index < DCM_WRITEDID_NUM;Index++)
	{
        uint32_t DataBlockEnd = 0U;
        DataBlockEnd = (uint32_t)Dcm_WriteDidRow[Index].Addr + (uint32_t)Dcm_WriteDidRow[Index].Length;
        if(((uint32_t)Dcm_WriteDidRow[Index].Addr >= DCM_CALVER_BEGADDR) && (DataBlockEnd < DCM_CALVER_ENDADDR))
        {
            Crc = Crc_CalculateCRC16((uint16_t)Dcm_WriteDidRow[Index].Length,Dcm_WriteDidRow[Index].Addr,Crc);
        }
		else
        {
            ;
        }
	}
	Data[0] = (uint8_t)(Crc >> 8U);
	Data[1] = (uint8_t)(Crc & 0X00FFU);

	return 2U;
}

/*******************************************************************************
Name			: Crc_CalculateCRC16
Syntax			: static uint16_t Crc_CalculateCRC16(uint16_t Crc_Length,uint8_t  Crc_DataPtr[],uint16_t InitCrc)
Parameters(in)	:	Crc_Length	: $B9;(B?$B?t?x(B?$BEY(B
					Crc_DataPtr : $B9;(B?$B?t?x;X(B?
					InitCrc		: $B=i;O(BCrc?
Parameters(out) : None
Return value	: 16$B0L(BCrc$B9;(B??
Description		: 16$B0L(BCrc$B9;(B?
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170324	$B=iHG(B
2			$BAb5~(B		20170328	$B2CF~=i;O2=(BCrc?$B:n(B?$B7A;2(B
3			$BAb5~(B		20170331	$B=$2~7A;2(B?$B7?(B?$B?t(B?$B;X(B??$B7?(B
|******************************************************************************/
static uint16_t Crc_CalculateCRC16(uint16_t Crc_Length,uint8_t  Crc_DataPtr[],uint16_t InitCrc)
{
	uint16_t CrcValue_u16 = InitCrc;
	uint16_t Index = 0U;
	while (Crc_Length > 0U)
	{
		uint8_t i; /* loop counter 1..8     */

		CrcValue_u16 ^= ((uint16_t)(Crc_DataPtr[Index]) << 8);
		Index++;

		for (i = 0U; i < 8U; i++)
		{
			if ((CrcValue_u16 & 0x8000U) > 0U)
			{
				CrcValue_u16 = (CrcValue_u16 << 1) ^ CRC_POLYNOMIAL_16;
			}
			else
			{
				CrcValue_u16 <<= 1;
			}
		}
		Crc_Length --;
	}

	return CrcValue_u16;
}

void MotorRunHall(uint16_t HallNum)
{
    ;
}

uint16_t GetHallResult(uint8_t Result[])
{
    Result[0] = 0X12U;
    Result[1] = 0X34U;
    Result[2] = 0X56U;
    Result[3] = 0X78U;
    return 4U;
}


/************cheksum-2018-10-19 by Comy***************/
uint16_t Get_EEChecksum(void)
{
	 check_sum_CRC checksum;
	 Read_Cheksum_Version(&(checksum.cheksum8[0]));
	 return checksum.checksum16;
}

void Read_Cheksum_Version(uint8_t Data[])
{
	uint16_t Crc = 0U;
	uint8_t Index;
	for(Index = 0U;Index < DCM_WRITEDID_NUM;Index++)
	{
        uint32_t DataBlockEnd = 0U;
        DataBlockEnd = (uint32_t)Dcm_WriteDidRow[Index].Addr + (uint32_t)Dcm_WriteDidRow[Index].Length;
        if(((uint32_t)Dcm_WriteDidRow[Index].Addr >= DCM_CALVER_BEGADDR) && (DataBlockEnd < DCM_CALVER_ENDADDR))
        {
					if(Index == 0)     /****checksum****2018-10-19*/
					{
						Crc = Crc_CalculateCRC16((uint16_t)Dcm_WriteDidRow[Index].Length-2,Dcm_WriteDidRow[Index].Addr + 2,Crc);
					}
					else
					{
						Crc = Crc_CalculateCRC16((uint16_t)Dcm_WriteDidRow[Index].Length,Dcm_WriteDidRow[Index].Addr,Crc);
					}

        }
		else
        {
            ;
        }
	}
	Data[0] = (uint8_t)(Crc >> 8U);
	Data[1] = (uint8_t)(Crc & 0X00FFU);

	return ;
}

bool_t Dcm_CalibrationWriteHandle(uint8_t * const Dest,const uint8_t * const Source,uint8_t Length)
{
    bool_t  FW_Ret   = FALSE;
    uint8_t flashRet = FLASH_ERR_SUCCESS;
    uint8_t uIndex   = 0u;
    uint32_t uData0  = 0u;
    uint32_t uData1  = 0u;

    /*  Check The Dest Flash Range  */
    FW_Ret = Fls_ChkAddrValid(&FlashValidAddr,(uint32_t)Dest);
    if(TRUE == FW_Ret)
    {
        if(FLS_PAGESIZE < Length)
        {
            FW_Ret = FALSE;
        }
        else
        {
            ;
        }
    }
    if(TRUE == FW_Ret)
    {
        if(((uint32_t)Dest == FLS_FACTORY_MSG_BASICADDR) || ((uint32_t)Dest == FLS_CALIBRATION_BASICADDR))
        {
            flashRet = App_FlashEraseSector((uint32_t)Dest,30000);

            if(flashRet == FLASH_ERR_SUCCESS)
            {
                FW_Ret = TRUE;
            }
            else
            {
                FW_Ret = FALSE;
            }
        }
    }
    else
    {
        ;
    }
    if(TRUE == FW_Ret)
    {
        for(uIndex = 0;uIndex < (Length/8);uIndex++)
        {
            uData0 = (((uint32_t)(Source[uIndex*8+3] << 24))&0xFF000000) |
                     (((uint32_t)(Source[uIndex*8+2] << 16))&0x00FF0000) |
                     (((uint32_t)(Source[uIndex*8+1] << 8 ))&0x0000FF00) |
                     (((uint32_t)(Source[uIndex*8+0] << 0 ))&0x000000FF);

            uData1 = (((uint32_t)(Source[uIndex*8+7] << 24))&0xFF000000) |
                     (((uint32_t)(Source[uIndex*8+6] << 16))&0x00FF0000) |
                     (((uint32_t)(Source[uIndex*8+5] << 8 ))&0x0000FF00) |
                     (((uint32_t)(Source[uIndex*8+4] << 0 ))&0x000000FF);

            flashRet = App_FlashWriteData((uint32_t)(Dest + 8*uIndex), uData0, uData1, 30000);

            if(flashRet == FLASH_ERR_SUCCESS)
            {
                FW_Ret = TRUE;
            }
            else
            {
                FW_Ret = FALSE;
                break;
            }
        }
    }
    else
    {
        ;
    }

    return FW_Ret;
}

static bool_t Fls_ChkAddrValid(const Fls_AddrRange_t AddrInfo[],uint32_t Addr)
{
    bool_t FC_Ret = TRUE;
    if(Addr < AddrInfo[0].AddrBeg)
    {
        FC_Ret = FALSE;
    }
    else
    {
        FC_Ret = TRUE;
    }

    if(Addr > (AddrInfo[0].AddrBeg + AddrInfo[0].Size - 1U))
    {
        FC_Ret = FALSE;
    }
    else
    {
        FC_Ret = TRUE;
    }

    return FC_Ret;
}

