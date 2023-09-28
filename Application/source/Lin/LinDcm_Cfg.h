/*******************************************************************************
|  File Name:    LinDcm_Cfg.h
|  Description:  Lin Diagnostic Config Header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170323	   0.01       	曹京          	初版
| 20170324	   0.02			曹京			加入$22服???符表?型
|******************************************************************************/
#include "Typedef.h"
#ifndef SOURCES_004_LINSTACK_LINDCM_CFG_H_
#define SOURCES_004_LINSTACK_LINDCM_CFG_H_

#define DCM_SESSION_SUPPORT_NUM	(3U)

/*	接收到Dcm?求到?求?送回??文的??	*/
#define	DCM_P2Server_MAX				(50U)
/*	ECU停留在非默?会?的最大??			*/
#define DCM_S3Server_MAX				(2000U)


#define DCM_PERIOD		(5U)
#define BUFFERMAXSIZE	(131U)

typedef union
{
		uint16_t checksum16;
    uint8_t  cheksum8[2];
}check_sum_CRC;                //by Comy
/*
 *
 *---------------------------$22-------------------------------
 *
 */

#define DCM_READDID_NUM				(3U)

#define DCM_READDID_INFORMATION			(0XA00AU)
#define DCM_READDID_CALIBRATION_VER		(0XB00BU)

#define DCM_READDID_DATAS						(0XD00DU)

#define DCM_FLASH_ADDR					(0X4000U)

typedef uint16_t (* Dcm_ReadDataFct)(uint8_t * Data);

typedef struct
{
	/* read data Id */
    const uint16_t DID;

    /* read data funtion */
    const Dcm_ReadDataFct readDataFct;
}Dcm_ReadDidRowType;


extern const Dcm_ReadDidRowType Dcm_ReadDidRow[DCM_READDID_NUM];

/*
 *
 *--------------------------EOF $22-----------------------------
 *
 */



/*
 *
 *---------------------------$2E-------------------------------
 *
 */
#define	DCM_WRITEDID_NUM	(4U)

#define DCM_CALVER_BEGADDR  (0x00006C00U)
#define DCM_CALVER_ENDADDR  (0x00006E00U)

#define FLS_PAGESIZE    (0X80U)

#define FLS_FACTORY_MSG_BASICADDR   (0x00006800U)
#define FLS_CALIBRATION_BASICADDR   (0x00006C00U)

#define FLS_BOOT_APP_FLAG0 0x00000055
#define FLS_BOOT_APP_FLAG1 0x00000000


typedef struct
{
	/*	数据ID	*/
	const uint16_t 	DID;
	/*	数据?度	*/
	const uint8_t 	Length;
	/*	数据起始地址	*/
	uint8_t * const Addr;
}	Dcm_WriteDidRowType;

extern const Dcm_WriteDidRowType Dcm_WriteDidRow[DCM_WRITEDID_NUM];

/*
 *
 *--------------------------EOF $2E-----------------------------
 *
 */

void MotorRunHall(uint16_t HallNum);
uint16_t GetHallResult(uint8_t Result[]);

uint16_t Get_EEChecksum(void);
bool_t Dcm_CalibrationWriteHandle(uint8_t * const Dest,const uint8_t * const Source,uint8_t Length);

#endif /* SOURCES_004_LINSTACK_LINDCM_CFG_H_ */
