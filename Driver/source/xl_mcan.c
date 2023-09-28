/**
  ******************************************************************************
  * @file     xl_mcan.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about MCAN firmware program 
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
#include "xl_mcan.h"

	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup MCAN MCAN Module 
  * @brief MCAN Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MCAN_Private_Functions
  * @{
  */
/**
 * @brief  将MCAN外设寄存器去初始化,复位.
 * @param  MCANx: 选择MCAN外设.
 * @retval None.
 */
void MCAN_DeInit(MCAN_Type* MCANx)
{
	/* Deinitializes to default reset values */
	MCANx->CANMOD	=	0x01;
	MCANx->CANCMR	=	0x00;
	MCANx->CANBTR0	=	0x00;
	MCANx->CANBTR1	=	0x00;	
	MCANx->CANIER	=	0x00;
}

/**
 * @brief  根据在MCAN_InitStruct中指定参数初始化MCAN外设.
 * @param  MCANx: 选择MCAN外设.
 * @param  MCAN_InitStruct: MCAN初始化配置结构体
 * @retval None
 */
void MCAN_Init(MCAN_Type* MCANx, const MCAN_InitTypeDef* MCAN_InitStruct)
{
	/* enter reset mode */
	MCAN_SetMode(MCANx,MCAN_RESETMODE);

	/* Set the nominal bit timing register */
	MCANx->CANBTR0 &= ~(MCAN_CANBTR0_BRP_MASK | MCAN_CANBTR0_SJW_MASK);
	MCANx->CANBTR0 |= ((MCAN_InitStruct->MCAN_BRP) | (MCAN_InitStruct->MCAN_SJW << MCAN_CANBTR0_SJW_SHIFT));
	
	MCANx->CANBTR1 &= ~(MCAN_CANBTR1_TSEG1_MASK | MCAN_CANBTR1_TSEG2_MASK |\
										MCAN_CANBTR1_SAMP_MASK);
	MCANx->CANBTR1 |= ((MCAN_InitStruct->MCAN_TSEG1) | (MCAN_InitStruct->MCAN_TSEG2 << MCAN_CANBTR1_TSEG2_SHIFT)|\
										(MCAN_InitStruct->MCAN_SAMP << MCAN_CANBTR1_SAMP_SHIFT));


	/* Set the FD data bit timing register */
	MCANx->CANFDBTR0 &= ~(MCAN_CANFDBTR0_FDBRP_MASK | MCAN_CANFDBTR0_FDSJW_MASK);
	MCANx->CANFDBTR0 |= ((MCAN_InitStruct->MCAN_FDBRP) | (MCAN_InitStruct->MCAN_FDSJW << MCAN_CANFDBTR0_FDSJW_SHIFT));
						
	MCANx->CANFDBTR1 &= ~(MCAN_CANFDBTR1_FDTSEG1_MASK | MCAN_CANFDBTR1_FDTSEG2_MASK |\
											MCAN_CANFDBTR1_FDSAMP_MASK);
	MCANx->CANFDBTR1 |= ((MCAN_InitStruct->MCAN_FDTSEG1) | (MCAN_InitStruct->MCAN_FDTSEG2 << MCAN_CANFDBTR1_FDTSEG2_SHIFT)|\
											(MCAN_InitStruct->MCAN_FDSAMP << MCAN_CANFDBTR1_FDSAMP_SHIFT));
	
	/* clear reset mode if in this mode*/			
	MCANx->CANMOD &= ~MCAN_CANMOD_RM_MASK; 
}

/**
 * @brief  MCANx使能
 * @param  MCANx: 选择MCAN外设.
 * @param  State: MCANx使能状态
 *		这个参数可以取下面的值:
 *			@arg ENABLE: MCANx使能
 *			@arg DISABLE: MCANx失能
 * @retval None.
 */
void MCAN_Enable(MCAN_Type* MCANx, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		MCANx->CANCMR |= MCAN_CANCMR_EN_MASK;
	}
	else
	{
		MCANx->CANCMR &= ~MCAN_CANCMR_EN_MASK;
	}
}

/**
 * @brief  启用或禁用MCAN FD
 * @param  MCANx: 选择MCAN外设.
 * @param  State: MCANx FD使能状态
  *		这个参数可以取下面的值:
 *			@arg ENABLE: MCANx FD使能
 *			@arg DISABLE: MCANx FD失能
 * @retval None.
 */
void MCAN_FDCmd(MCAN_Type* MCANx, FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the can FD */
		MCANx->CANMOD |= MCAN_CANMOD_FDM_MASK ;
	}
	else 
	{
		/* Disable the can FD */
		MCANx->CANMOD &= ~MCAN_CANMOD_FDM_MASK ;
	}	
}

/**
 * @brief 在FD模式下选择发送格式类型。
 * @param  MCANx: 选择MCAN外设.
 * @param  FdFormat: 在FD模式下选择发送格式类型。
  *		这个参数可以取下面的值:
 *			@arg MCAN_FDM_NOMFrame: 发送帧为普通CAN数据帧
 *			@arg MCAN_FDM_FDFrame: 发送帧为CAN FD帧
 * @retval None.
 */
void MCAN_FDSendFormatSel(MCAN_Type* MCANx, uint8_t FdFormat)
{
	if(FdFormat == MCAN_FDM_FDFrame )
	{
	/* send the FD frame in FD mode */
		MCANx->CANMOD |= MCAN_CANMOD_FDTREN_MASK ;
	}
	else 
	{
	/* send the nominal frame in FD mode */
		MCANx->CANMOD &= ~MCAN_CANMOD_FDTREN_MASK ;
	}	
}

/**
 * @brief 设置补偿时间。
 * @param  MCANx: 选择MCAN外设.
 * @param  CompensateTime:设置发送延时补偿的时间,范围为0x00~0x1F
 * @retval None.
 */
void MCAN_FDTDCSet(MCAN_Type* MCANx, uint32_t CompensateTime)
{
	/* set the compensation time  */		
	MCANx->CANTDCS &= ~MCAN_CANTDCS_TDCT_MASK;
	MCANx->CANTDCS |= (CompensateTime & (uint32_t)0x1F);
}

/**
 * @brief 启用或禁用MCAN FD延时补偿功能
 * @param  MCANx: 选择MCAN外设.
 * @param  NewState: 选择状态
  *		这个参数可以取下面的值:
 *			@arg ENABLE: 使能MCAN FD延时补偿功能
 *			@arg DISABLE: 失能MCAN FD延时补偿功能
 * @retval None.
 */
void MCAN_FDTDCENCmd(MCAN_Type* MCANx, FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the FD time delay compensation feature */
		MCANx->CANMOD |= MCAN_CANMOD_FDTDCEN_MASK ;
	}
	else
	{
		/* Disable the FD time delay compensation feature */
		MCANx->CANMOD &= ~MCAN_CANMOD_FDTDCEN_MASK ;
	}
}

/**
 * @brief  设置开关点补偿时间.
 * @param  MCANx: 选择MCAN外设.
 * @param  CompensateTime: 补偿设定时间,范围为0x00~0x7F.
 * @retval None.
 */
void MCAN_FDHFCSet(MCAN_Type* MCANx, uint32_t CompensateTime)
{
	/* set the compensation time  */		
	MCANx->CANHFC &= ~MCAN_CANHFC_HFCT_MASK;
	MCANx->CANHFC |= (CompensateTime & (uint32_t)0x7F);
}

/**
 * @brief  根据在MCAN_FilterStruct中的指定参数配置MCAN外设过滤模式.
 * @param  MCANx: 选择MCAN外设.
 * @param  MCAN_FilterStruct:指向包含MCAN外设配置信息的MCAN_FilterDef 结构的指针.
 * @retval None.
 */
void MCAN_FilterConfig(MCAN_Type* MCANx, const MCAN_FilterDef* MCAN_FilterStruct)
{
	uint32_t MCAN_Mask;
	uint32_t MCAN_ID;

	/* enter reset mode */
	MCAN_SetMode(MCANx,MCAN_RESETMODE);

	/* Set the filter mode */	
	MCANx->CANMOD &=~MCAN_CANMOD_AFM_MASK;
	MCANx->CANMOD |= (MCAN_FilterStruct->MCAN_FiltMode << MCAN_CANMOD_AFM_SHIFT);

	/* config the accept and mask register */	
	/* if use single filter, 32bit filter  */			
	if(MCAN_FilterStruct->MCAN_FiltMode==MCAN_Single_Filter)
	{
		/* ID(standard )+RTR=12 bit*/	
		if(MCAN_FilterStruct->MCAN_IDMode==MCAN_Standard_Frame)
		{
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_IDAR)<<21);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_IDMR)<<21);
			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[1]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[1]=(MCAN_Mask>>16);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[2]=0xFF;  //data bytes1 do not care
			MCANx->CANAR.CANACR[3]=(MCAN_ID);
			MCANx->CANAR.CANAMR[3]=0xFF;	 //data bytes2 do not care		
		}
		/* ID( extended)+RTR=30 bit*/
		else if(MCAN_FilterStruct->MCAN_IDMode==MCAN_Extended_Frame)
		{
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_IDAR)<<3);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_IDMR)<<3);
			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[1]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[1]=(MCAN_Mask>>16);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[2]=(MCAN_Mask>>8);
			MCANx->CANAR.CANACR[3]=(MCAN_ID);
			MCANx->CANAR.CANAMR[3]=(MCAN_Mask);										
		}
		else
		{
			MCAN_ID=(uint32_t)(MCAN_FilterStruct->MCAN_IDAR);
			MCAN_Mask=(uint32_t)(MCAN_FilterStruct->MCAN_IDMR);
			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[1]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[1]=(MCAN_Mask>>16);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[2]=(MCAN_Mask>>8);
			MCANx->CANAR.CANACR[3]=(MCAN_ID);
			MCANx->CANAR.CANAMR[3]=(MCAN_Mask);				
		}
	}
	/* else use dual filter, 16bit filter  */
	else		
	{	
		/* ID(standard )+RTR=12 bit*/				
		if(MCAN_FilterStruct->MCAN_IDMode==MCAN_Standard_Frame)
		{
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_IDAR)<<5);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_IDMR)<<5);
			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>8);
			MCANx->CANAR.CANACR[1]=(MCAN_ID);
			MCANx->CANAR.CANAMR[1]=(MCAN_Mask | 0x0000000Fu);
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_DIDAR)<<5);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_DIDMR)<<5);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[2]=(MCAN_Mask>>8);
			MCANx->CANAR.CANACR[3]=(MCAN_ID);
			MCANx->CANAR.CANAMR[3]=(MCAN_Mask| 0x0000000Fu);					
		}
		/* ID( extended)+RTR=30 bit*/
		else if(MCAN_FilterStruct->MCAN_IDMode==MCAN_Extended_Frame)
		{
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_IDAR)<<3);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_IDMR)<<3);						

			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[1]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[1]=((MCAN_Mask>>16) | 0x0000000Fu);
			
			MCAN_ID=(uint32_t)((MCAN_FilterStruct->MCAN_DIDAR)<<3);
			MCAN_Mask=(uint32_t)((MCAN_FilterStruct->MCAN_DIDMR)<<3);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[2]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[3]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[3]=((MCAN_Mask>>16)| 0x0000000Fu);	
		}
		else
		{
			MCAN_ID=(uint32_t)(MCAN_FilterStruct->MCAN_IDAR);
			MCAN_Mask=(uint32_t)(MCAN_FilterStruct->MCAN_IDMR);
			/* according to the accept rule */			
			MCANx->CANAR.CANACR[0]=(MCAN_ID>>24);
			MCANx->CANAR.CANAMR[0]=(MCAN_Mask>>24);
			MCANx->CANAR.CANACR[1]=(MCAN_ID>>16);
			MCANx->CANAR.CANAMR[1]=(MCAN_Mask>>16);
			MCANx->CANAR.CANACR[2]=(MCAN_ID>>8);
			MCANx->CANAR.CANAMR[2]=(MCAN_Mask>>8);
			MCANx->CANAR.CANACR[3]=(MCAN_ID);
			MCANx->CANAR.CANAMR[3]=(MCAN_Mask);			
		}
	}			

	/* clear reset mode if in this mode*/			
	MCANx->CANMOD &=~MCAN_CANMOD_RM_MASK; 
}

/**
 * @brief  加载传输到TX缓冲区所需的数据。
 * @param  MCANx: 选择MCAN外设.
 * @param  TxMessage: 指向一个包含MCAN Id，MCAN DLC和MCAN数据的结构。
 * @retval None.
 */
void MCAN_LoadTransmitData(MCAN_Type *MCANx, const MCAN_MsgTypeDef* TxMessage)
{
	uint8_t i = 0;
	uint32_t datasize = 0;

	/* Set up the Tx frame information */
	MCANx->CANTB[0]= (0x000000FFu&((TxMessage->MCAN_FF << 7) | (TxMessage->MCAN_RTR << 6) | (TxMessage->MCAN_FDBRS << 5)| \
									 (TxMessage->MCAN_FDESI << 4) | (TxMessage->MCAN_DLC)));

	 /* get actually data size  */
	if((TxMessage->MCAN_DLC) < MCAN_DLC_DATASIZE12)
	{
		datasize=(TxMessage->MCAN_DLC);
	}
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE12)
	{
		datasize=12;
	}
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE16)
	{
		datasize=16;
	}
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE20)
	{
		datasize=20;
	}	
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE24)
	{
		datasize=24;
	}
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE32)
	{
		datasize=32;
	}
	else if ((TxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE48)
	{
		datasize=48;
	}		
	else		
	{
		datasize=64;
	}

	/* Set up the ID */
	if (TxMessage->MCAN_FF == MCAN_Standard_Frame)
	{
		MCANx->CANTB[1]=(0xFFu&(TxMessage->MCAN_ID>>3));
		MCANx->CANTB[2]=(0xF0u&((TxMessage->MCAN_ID<<5)|(TxMessage->MCAN_RTR<<4)));	
		
		/* Set up the data field */
		for (i=0;i<datasize;i++)
		{
			 MCANx->CANTB[i+3u] = (uint32_t)TxMessage->MCAN_Data[i];
		}
	}
	else
	{
		MCANx->CANTB[1]=(0xFFu&(TxMessage->MCAN_ID>>21));
		MCANx->CANTB[2]=(0xFFu&(TxMessage->MCAN_ID>>13));
		MCANx->CANTB[3]=(0xFFu&(TxMessage->MCAN_ID>>5));	
		MCANx->CANTB[4]=(0xFCu&((TxMessage->MCAN_ID<<3)|(TxMessage->MCAN_RTR<<2)));	
		
		/* Set up the data field */
		for (i=0;i<datasize;i++)
		{
			 MCANx->CANTB[i+5u] = (uint32_t)TxMessage->MCAN_Data[i];
		}
	}
}

/**
 * @brief  接收数据
 * @param  MCANx: 选择MCAN外设.
 * @param  RxMessage:  指向包含MCAN Id, MCAN DLC, MCAN数据的结构接收消息的指针。
 * @retval None.
 */
void MCAN_ReceiveData(MCAN_Type *MCANx, MCAN_MsgTypeDef* RxMessage)
{
	uint8_t i=0;
	uint32_t temp=0;
	uint32_t datasize = 0;

	/* Get the FF */	
	RxMessage->MCAN_FF = ((0x80u & MCANx->CANRB[0]) >> 7);
	/* Get the RTR */	
	RxMessage->MCAN_RTR = (0x40u & MCANx->CANRB[0]);
	/* Get the BRS */	
	RxMessage->MCAN_FDBRS = (0x20u & MCANx->CANRB[0]);
	/* Get the ESI */	
	RxMessage->MCAN_FDESI = (0x10u & MCANx->CANRB[0]);
	/* Get the DLC */
	RxMessage->MCAN_DLC = (0x0Fu & MCANx->CANRB[0]);

	/*  get actually data size  */
	if((RxMessage->MCAN_DLC) < MCAN_DLC_DATASIZE12)
	{
		datasize=(RxMessage->MCAN_DLC);
	}
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE12)
	{
		datasize=12;
	}
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE16)
	{
		datasize=16;
	}
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE20)
	{
		datasize=20;
	}	
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE24)
	{
		datasize=24;
	}
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE32)
	{
		datasize=32;
	}
	else if ((RxMessage->MCAN_DLC) == MCAN_DLC_DATASIZE48)
	{
		datasize=48;
	}		
	else		
	{
		datasize=64;
	}

	/* Get the Id and data */
	if (RxMessage->MCAN_FF == MCAN_Standard_Frame)
	{
		/* Get the Id  */
		temp = MCANx->CANRB[1]<<8;
		RxMessage->MCAN_ID = (0x7FFu & ((temp| MCANx->CANRB[2])>>5));
		
		/* Get the data field */
		for (i=0;i<datasize;i++)
		{
			RxMessage->MCAN_Data[i] = (uint8_t)MCANx->CANRB[i+3u];
		}
	}
	else
	{
		/* Get the Id  */
		temp = MCANx->CANRB[1]<<24;
		temp |= MCANx->CANRB[2]<<16;
		temp |= MCANx->CANRB[3]<<8;
		temp |= MCANx->CANRB[4];
		temp >>=3;
		RxMessage->MCAN_ID = 0x1FFFFFFFu & temp;
		
		/* Get the data field */
		for (i=0;i<datasize;i++)
		{
			RxMessage->MCAN_Data[i] = (uint8_t)MCANx->CANRB[i+5u];
		}		
	}
	/* RX finished, return to Normal Operating Mode	*/	
	MCAN_SetCmd(MCANx,MCAN_ReleaseReceiveBuffer); //Aaron he add 20180328
}

/**
 * @brief 配置CAN控制器的模式
 * @param  MCANx: 选择MCAN外设.
 * @param  MCAN_ModeType: 模式选择
 *		这个参数可以取下面的值:
 *			@arg MCAN_NORMALMODE: 睡眠模式
 *			@arg MCAN_RESETMODE: seltest模式
 *			@arg MCAN_LISTENONLYMODE: listen noly模式
 *			@arg MCAN_SELFTESTMODE: 重置模式
 *			@arg MCAN_SLEEPMODE: 正常操作模式
 * @retval None.
 */
void MCAN_SetMode(MCAN_Type *MCANx, uint8_t MCAN_ModeType)
{
	switch(MCAN_ModeType)
	{
		case MCAN_NORMALMODE:	/* enable the normal mode */
			/* clear reset mode if in this mode*/			
			MCANx->CANMOD &=~MCAN_CANMOD_RM_MASK; 
			/* clear listen only mode if in this mode*/		
			MCANx->CANMOD &=~MCAN_CANMOD_LOM_MASK;
			/* clear self test mode if in this mode*/     		
			MCANx->CANMOD &=~MCAN_CANMOD_STM_MASK;
			/* clear sleep mode if in this mode*/		
			MCANx->CANMOD &=~MCAN_CANMOD_SM_MASK;
			break;
		case MCAN_RESETMODE:
			/* set the reset mode*/				
			MCANx->CANMOD |= MCAN_CANMOD_RM_MASK;
			break;		
		case MCAN_LISTENONLYMODE: 
			/* set the listen only mode*/
			MCANx->CANMOD |=MCAN_CANMOD_LOM_MASK;					
			break;
		case MCAN_SELFTESTMODE: 
			/* set the self test mode*/  				
			MCANx->CANMOD |=MCAN_CANMOD_STM_MASK; 
			break;			
		case MCAN_SLEEPMODE:
			/* enable wakeup interrupt */
			MCAN_InterruptEn(MCANx,MCAN_WakeUpInterruptEn,ENABLE);
			/* set the sleep mode */				
			MCANx->CANMOD |= MCAN_CANMOD_SM_MASK; 
			break;
		default:
		   /* error if do not set mode */	
			break;
	}		
}

/**
 * @brief  唤醒MCAN.
 * @param  MCANx: 选择MCAN外设.
 * @retval None.
 */
void  MCAN_WakeUp(MCAN_Type *MCANx)
{
	/* clear sleep mode */		
	MCANx->CANMOD &=~MCAN_CANMOD_SM_MASK;
}

 /**
 * @brief  设置命令位以启动MCAN控制器传输层内的操作
 * @param  MCANx: 选择CAN外设
 * @param 命令类型：中断类型
 *		这个参数可以取下面的值:
 *			@arg MCAN_TransmissionRequest: 发送请求
 *			@arg MCAN_AbortTransmission：传输中止
 *			@arg MCAN_ReleaseReceiveBuffer： 释放接收缓冲
 *			@arg MCAN_ClearDataOverrun： 清零数据溢出
 *			@arg MCAN_SelfReceptionRequest：自接收请求
 * @retval None 
 */
void MCAN_SetCmd(MCAN_Type *MCANx, uint8_t MCAN_CommandType)
{
	/* set the selected command */
	MCANx->CANCMR |= MCAN_CommandType;
}

/**
 * @brief  清除接收中断.
 * @param  MCANx: 选择MCAN外设.
 * @retval None.
 */
void MCAN_ClearReceiveInterrupt(MCAN_Type *MCANx)
{
	/* there is no further data to read in the Receive Buffer.*/	
	 /* then realse the receive buffer meantime clear receive interrupt*/
	MCAN_SetCmd(MCANx,MCAN_ReleaseReceiveBuffer);	 
}

/**
 * @brief  获取MCANx外设指定状态
 * @param  MCANx: 选择MCAN外设
 * @param  UART_StatusType: 状态类型
 *		这个参数可以取下面的值:
 *			@arg MCAN_ReceiveBufferStatus: 接收缓冲区状态
 *			@arg MCAN_DataOverrunStatus: 数据溢出状态
 *			@arg MCAN_TransBufferStatus: 发送缓冲区状态
 *			@arg MCAN_TransCompleteStatus: 传输完成状态
 *			@arg MCAN_ReceiveStatus: 接收状态
 *			@arg MCAN_TransmitStatus: 发送状态
 *			@arg MCAN_ErrorStatus: 错误状态
 *			@arg MCAN_BusStatus: 总线状态
 * @retval 当前状态(TRUE or FALSE) 
 */
FlagStatus MCAN_GetStatus(const MCAN_Type *MCANx, MCAN_StatusTypeDef MCAN_StatusType)
{
	return (((MCANx->CANSR >> (uint8_t)MCAN_StatusType)&(uint32_t)0x01) != (uint32_t)0);
}

/**
 * @brief  获取MCANx指定中断源状态
 * @param  MCANx: 选择MCAN外设
 * @param  MCAN_InterruptFlgDef: 中断类型
 *		这个参数可以取下面的值:
 *			@arg MCAN_ReceiveInterrupt: 接收中断
 *			@arg MCAN_TransmitInterrupt: 发送中断
 *			@arg MCAN_ErrorWarningInterrupt: 错误警告中断
 *			@arg MCAN_DataOverrunInterrupt: 数据溢出中断
 *			@arg MCAN_WakeUpInterrupt: 唤醒中断
 *			@arg MCAN_ErrorPassiveInterrupt: 错误被动中断
 *			@arg MCAN_ArbitrationLostInterrupt: 仲裁丢失中断
 *			@arg MCAN_BusErrorInterrupt: 总线错误中断
 * @retval 当前状态(TRUE or FALSE) 
 */
ITStatus MCAN_GetInterruptFlg(const MCAN_Type *MCANx, MCAN_InterruptFlgDef MCAN_InterruptFlg)
{
	return (((MCANx->CANIR >> (uint8_t)MCAN_InterruptFlg)&(uint32_t)0x01) != (uint32_t)0);
}

/**
 * @brief  使能MCAN指定中断
 * @param  MCANx: 选择MCAN外设
 * @param  MCAN_InterruptFlgDef: 中断类型
 *		这个参数可以取下面的值:
 *			@arg MCAN_ReceiveInterruptEn: 接收中断
 *			@arg MCAN_TransmitInterruptEn: 发送中断
 *			@arg MCAN_ErrorWarningInterruptEn: 错误警告中断
 *			@arg MCAN_DataOverrunInterruptEn: 数据溢出中断
 *			@arg MCAN_WakeUpInterruptEn: 唤醒中断
 *			@arg MCAN_ErrorPassiveInterruptEn: 错误被动中断
 *			@arg MCAN_ArbitrationLostInterruptEn: 仲裁丢失中断
 *			@arg MCAN_BusErrorInterruptEn: 总线错误中断
 * @param  State: 中断使能状态
 *		这个参数可以取下面的值:
 *			@arg ENABLE: 中断使能
 *			@arg DISABLE: 中断失能
 * @retval None
 */
void MCAN_InterruptEn(MCAN_Type *MCANx, MCAN_InterruptEnDef MCAN_Interrupt, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected MCAN interrupts */
		MCANx->CANIER |= ((uint32_t)1<<(uint8_t)MCAN_Interrupt);
	}
	else
	{
		/* Disable the selected MCAN interrupts */
		MCANx->CANIER &= ~((uint32_t)1<<(uint8_t)MCAN_Interrupt);
	}
}

 /**
 * @brief  返回MCANx仲裁丢失捕获(ALC).
 * @param  MCANx: 选择MCAN外设.
 * @retval Arbitration Lost position.返回仲裁丢失位置。
 */
uint8_t MCAN_ArbitrationLostCap(const MCAN_Type *MCANx)
{
	/* Return the Arbitration Lost*/
	return (uint8_t)MCANx->CANALC;
}

 /**
 * @brief  返回有关总线上错误类型和位置的信息。
 * @param MCANx: 选择MCAN外设.
 * @param MCAN_BusErrorCapture: 指向包含MCAN外设配置信息的MCAN_BusErrorCaptureDef结构的指针。
 * @retval None.
 */
uint8_t MCAN_GetBusErrorType(const MCAN_Type *MCANx, MCAN_BusErrorCaptureDef MCAN_BusErrorCapture)
{
	uint8_t errorcap=0;

	/* Get the error position */
	if(MCAN_BusErrorCapture==MCAN_BusErrorPosition)
	{
		errorcap = (uint8_t)(MCANx->CANECC & MCAN_CANECC_SEGMENT_MASK);
	}
	/* Get the error direction */
	else if(MCAN_BusErrorCapture==MCAN_BusErrorDirection)
	{
		errorcap = (uint8_t)((MCANx->CANECC & MCAN_CANECC_DIR_MASK)>>5);
	}
	/* Get the error type */
	else //(Can_BusErrorCapture==MCAN_BusErrorType)
	{
		errorcap = (uint8_t)((MCANx->CANECC & MCAN_CANECC_ERROR_MASK)>>6);		
	}
	/* Return the Error Information on the bus*/
	return errorcap;
}

/**
 * @brief  返回MCANx接收错误计数器 (RXERR).
 * @param  MCANx: 选择MCAN外设.
 * @retval Receive Error Counter.返回接收到的错误计数器 。
 */
uint8_t MCAN_GetReceiveErrorCounter(const MCAN_Type *MCANx)
{
	/* Return the Receive Error Counter*/
	return (uint8_t)MCANx->CANRXERR;
}

/**
 * @brief  返回MCANx Tramsmit错误计数器 (TXERR). 
 * @param  MCANx: 选择MCAN外设.
 * @retval Transmit Error Counter.返回CANx Tramsmit错误计数器 。
 */
uint8_t MCAN_GetTransmitErrorCounter(const MCAN_Type *MCANx)
{
	/* Return the Transmit Error Counter*/
	return (uint8_t)(MCANx->CANTXERR);
}

/**
 * @brief  返回MCANx接收信息计数器(RMC).
 * @param  MCANx: 选择MCAN外设.
 * @retval Receive Message Counter.返回接收信息计数器。
 */
uint8_t MCAN_GetReceiveMessageCounter(const MCAN_Type *MCANx)
{
	/* Return the Receive Message Counter*/
	return (uint8_t)(MCANx->CANRMC);
}

/**
 * @brief  在重置模式改变错误设置.
 * @param  MCANx: 选择MCAN外设.
 * @param  MCAN_ErrorSetting: 指向包含MCAN外设配置信息的MCAN_ErrorSettingDef结构的指针。
 * @retval None.
 */
void MCAN_ErrorSettingModify(MCAN_Type *MCANx, const MCAN_ErrorSettingDef *MCAN_ErrorSetting)
{
	/* modify the error warning limit in Reset Mode */	
	MCANx->CANEWLR &= ~MCAN_CANEWLR_EWL_MASK;
	MCANx->CANEWLR |= (MCAN_ErrorSetting->MCAN_ErrorWarningLimit);

	/* modify the receive error in Reset Mode */		
	MCANx->CANRXERR &= ~MCAN_CANRXERR_RXERR_MASK;
	MCANx->CANRXERR |= (MCAN_ErrorSetting->MCAN_ReceiveErrorCount);

	/* modify the transimit error in Reset Mode */	
	MCANx->CANTXERR &= ~MCAN_CANTXERR_TXERR_MASK;
	MCANx->CANTXERR |= (MCAN_ErrorSetting->MCAN_TranmitErrorCount);
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

