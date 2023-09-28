 /**
  ******************************************************************************
  * @file     xl_eeprom.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about EEPROM firmware program 
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
#include "xl_eeprom.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup EEPROM EEPROM_Module 
  * @brief EEPROM Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static Timer_Type sTimer_Type;

#if (USER_HARDWARE_OR_SOFTWARE == 0u)
	static uint8_t I2C_SEND_SPEED_H;
	static uint8_t I2C_SEND_SPEED_L;

	static uint8_t I2C_READ_SPEED_H;
	static uint8_t I2C_READ_SPEED_L;
#endif
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static uint8_t EEPROM_Timeout(uint32_t time);
	
/** @defgroup EEPROM_Private_Functions 
  * @{
  */ 

#if (USER_HARDWARE_OR_SOFTWARE == 0u)
static void IO_I2C_Start()
{
	uint16_t i;
	
	SET_SDA_OUTPUT();
	I2C_SDA_H();
	I2C_SCK_H();
	for(i=0;i<0x1;i++){};
	I2C_SDA_L();
	for(i=0;i<0x1;i++){};
	I2C_SCK_L();
}

static void IO_I2C_Stop()
{
	uint16_t i;
	
	SET_SDA_OUTPUT();
	I2C_SCK_L();
	I2C_SDA_L();	
	for(i=0;i<0x1;i++){};
	I2C_SCK_H();
	I2C_SDA_H();
	for(i=0;i<0x1;i++){};
}

static void IO_I2C_Ack()
{
	uint16_t i;
	
	I2C_SCK_L();
	SET_SDA_OUTPUT();
	I2C_SDA_L();	
	for(i=0;i<0x1;i++){};
	I2C_SCK_H();
	for(i=0;i<0x1;i++){};
	I2C_SCK_L();
}

static void IO_I2C_NAck()
{
	uint16_t i;
	
	I2C_SCK_L();
	SET_SDA_OUTPUT();
	I2C_SDA_H();	
	for(i=0;i<0x1;i++){};
	I2C_SCK_H();
	for(i=0;i<0x1;i++){};
	I2C_SCK_L();
}

static uint8_t IO_I2C_WaitAck(uint32_t time)
{
	uint8_t timeflag = 0;
	sTimer_Type.timer_cnt = time;
	SET_SDA_OUTPUT();
	I2C_SDA_H();
	I2C_SCK_H();	
	
	SET_SDA_INPUT();

	while(GPIO_ReadPin(GPIO_PTH3))
	{
		
		if(EEPROM_Timeout(time) == 1u)
		{
			timeflag = 1;
			SET_SDA_OUTPUT();
			IO_I2C_Stop();
			break;
		}
	}
	if(0 == timeflag)
	{
		I2C_SCK_L();
		SET_SDA_OUTPUT();
	}

	return timeflag;
}

static void IO_I2C_Send_Byte(uint8_t data)
{
	uint16_t i;
	
	SET_SDA_OUTPUT();
	//send bit7
	if(data & 0x80)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};
	//send bit6
	if(data & 0x40)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};
	//send bit5
	if(data & 0x20)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};	
	//send bit4
	if(data & 0x10)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};	
	//send bit3
	if(data & 0x08)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};	
	//send bit2
	if(data & 0x04)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};	
	//send bit1
	if(data & 0x02)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
	for(i=0;i<I2C_SEND_SPEED_L;i++){};	
	//send bit0
	if(data & 0x01)
	{
		I2C_SDA_H();
	}
	else
	{
		I2C_SDA_L();
	}
	I2C_SCK_H();
	for(i=0;i<I2C_SEND_SPEED_H;i++){};
	I2C_SCK_L();
}

static uint8_t IO_I2C_Read_Byte(uint8_t ack)
{
	uint8_t cnt=0,receive=0;
	uint16_t i;
	SET_SDA_INPUT();
	for(cnt=0;cnt<8;cnt++)
	{
		I2C_SCK_L();	
		for(i=0;i<I2C_READ_SPEED_L;i++){};
		I2C_SCK_H();
		receive<<=1;
		for(i=0;i<I2C_READ_SPEED_H;i++){};
		if(GPIO_ReadPin(GPIO_PTH3))
			receive++;
	}
	if(!ack)
	{
		IO_I2C_NAck();
	}
	else
	{
		IO_I2C_Ack();
	}
	return receive;
}
#endif

/**
  * @brief  EEPROM初始化
  * @param  systemclk I2C外设系统时钟,单位Hz
  * @retval None
  */
void EEPROM_Init(uint32_t systemclk)
{
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	I2C_InitTypeDef I2C_InitStructure;
	
	GPIO_SetPinDir(GPIO_PTE4,GPIO_Direction_Output);
	GPIO_SetPin(GPIO_PTE4);
	
	SIM_PINSEL_I2C1(I2C1_PS_PTH4_PTH3);
	
	SIM_SCGC_Cmd(SIM_SCGC_I2C1, ENABLE);
	
	
	PORT_PullPinCmd(PORT_PTH4, ENABLE);
	PORT_PullPinCmd(PORT_PTH3, ENABLE);
	
	I2C_InitStructure.I2C_SourceClk = (uint16_t)(systemclk/1000000u);
	I2C_InitStructure.I2C_HSMasterModeCode = I2C_HSMasterCode_0;
	
	I2C_InitStructure.I2C_RXTL = 0;
	I2C_InitStructure.I2C_TXTL = 0;
	
	I2C_InitStructure.I2C_MADmode = I2C_7BitAddrMaster;//I2C_10BitAddrMaster  I2C_7BitAddrMaster
	I2C_InitStructure.I2C_SADmode = I2C_7BitAddrSlave;
	I2C_InitStructure.I2C_MasterModeEn = I2C_MasterModeEnabled;//I2C_MasterModeDisabled  I2C_MasterModeEnabled
	I2C_InitStructure.I2C_SlaveModeDis = I2C_SlaveModeDisabled;//I2C_SlaveModeEnabled  I2C_SlaveModeDisabled
	I2C_InitStructure.I2C_SlaveAddress =  0;
	I2C_InitStructure.I2C_TargetAddress = (uint32_t)0xA0 >> 1u;
	
	I2C_InitStructure.I2C_SpeedMode = I2C_StandardMode;//I2C_FastMode     I2C_StandardMode
	I2C_InitStructure.I2C_SendRestart = I2C_SendRestartDisabled;
	
	I2C_EnableCmd(I2C1, DISABLE );
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_InterruptEn(I2C1 ,I2C_TXEMPTYInterrupt ,DISABLE );
	I2C_InterruptEn(I2C1 ,I2C_RXFULLInterrupt ,DISABLE);
	I2C_EnableCmd(I2C1, ENABLE);
#else
	GPIO_SetPinDir(GPIO_PTH3,GPIO_Direction_Output);//SDA
	GPIO_SetPinDir(GPIO_PTH4,GPIO_Direction_Output);//SCK
	
	PORT_PullPinCmd(PORT_PTH3,ENABLE);
	PORT_PullPinCmd(PORT_PTH4,ENABLE);
	
	switch(systemclk)
	{
		case 64000000:
			I2C_SEND_SPEED_H = 0x07;
			I2C_SEND_SPEED_L = 0x02;
			I2C_READ_SPEED_H = 0x02;
			I2C_READ_SPEED_L = 0x02;
		break;
		case 72000000:
			I2C_SEND_SPEED_H = 0x08;
			I2C_SEND_SPEED_L = 0x03;
			I2C_READ_SPEED_H = 0x02;
			I2C_READ_SPEED_L = 0x03;
		break;
		case 96000000:
			I2C_SEND_SPEED_H = 0x0C;
			I2C_SEND_SPEED_L = 0x07;
			I2C_READ_SPEED_H = 0x05;
			I2C_READ_SPEED_L = 0x07;
		break;
		case 60000000:
			I2C_SEND_SPEED_H = 0x08;
			I2C_SEND_SPEED_L = 0x04;
			I2C_READ_SPEED_H = 0x02;
			I2C_READ_SPEED_L = 0x02;
		break;
		case 90000000:
			I2C_SEND_SPEED_H = 0x0E;
			I2C_SEND_SPEED_L = 0x09;
			I2C_READ_SPEED_H = 0x04;
			I2C_READ_SPEED_L = 0x04;
		break;
		default:
			I2C_SEND_SPEED_H = 0x07;
			I2C_SEND_SPEED_L = 0x02;
			I2C_READ_SPEED_H = 0x02;
			I2C_READ_SPEED_L = 0x02;
		break;
	}
#endif
}


/**
  * @brief  EEPROM回复未初始化状态和关闭功能
  * @param  None
  * @retval None
  */
void EEPROM_DeInit(void)
{
	#if (USER_HARDWARE_OR_SOFTWARE == 1u)
		I2C_InterruptEn(I2C1 ,I2C_TXEMPTYInterrupt ,DISABLE );
		I2C_InterruptEn(I2C1 ,I2C_RXFULLInterrupt ,DISABLE);
		I2C_EnableCmd(I2C1, DISABLE);
		
		SIM_SCGC_Cmd(SIM_SCGC_I2C1, DISABLE);
		
		PORT_PullPinCmd(PORT_PTH4, DISABLE);
		PORT_PullPinCmd(PORT_PTH3, DISABLE);
	#endif
	
}

/**
 * @brief  EEPROM写保护
 * @param  NewState：ENABLE：打开写保护，不能写入数据，只能读。DISABLE：关闭写保护，能写入数据
 * @retval None
 */
void EEPROM_WriteProtectEn(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		GPIO_SetPin(GPIO_PTE4);
	}
	else
	{
		GPIO_ClrPin(GPIO_PTE4);
	}
}


static uint8_t EEPROM_Timeout(uint32_t time)
{
	uint8_t ret;
	
	if((sTimer_Type.timer_cnt<10u)||(sTimer_Type.timer_cnt>time))
	{
		ret = 1u;
	}
	else
	{
		sTimer_Type.timer_cnt--;
		ret = 0u;
	}
	
	return ret;
}
/**
 * @brief  EEPROM写一个字节数据
 * @param  address：写入的地址
 * @param  data：写入的数据
 * @param  time：超时时间 (time>20)
 * @retval 写状态
 */
uint8_t EEPROM_WriteByte(uint32_t address,uint8_t data,uint32_t time)
{
	EEPROM_Status status;
	uint32_t add ;
	
	status = EEPROM_OK;
	add = address - EEPROM_BASE_ADDRESS;
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	sTimer_Type.timer_cnt = time;
	while((uint8_t)0 == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
	{
		if(1u == EEPROM_Timeout(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
			break;
		}
	}
	if(status != EEPROM_ADDRESS_TIMEOUT)
	{
		I2C1->DBC = (uint32_t)((add>>8)&0x000000FFu);
		
		sTimer_Type.timer_cnt = time;
		while((uint8_t)0 == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
		{
			if(1u == EEPROM_Timeout(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
				break;
			}
		}
		if(status != EEPROM_ADDRESS_TIMEOUT)
		{
			I2C1->DBC = (uint8_t)add;
			sTimer_Type.timer_cnt = time;
			while((uint8_t)0 == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
			{
				if(1u == EEPROM_Timeout(time))
				{
					status = EEPROM_DATA_TIMEOUT;
					break;
				}
			}
			if(status != EEPROM_ADDRESS_TIMEOUT)
			{
				I2C1->DBC = ((uint32_t)data | I2C_DBC_STOP_MASK);
			}
		}
	}
#else
	IO_I2C_Start();
	IO_I2C_Send_Byte(0xA0);
	if( 1u == IO_I2C_WaitAck(time))
	{
		status = EEPROM_SlaveID_TIMEOUT;
	}
	else
	{
		IO_I2C_Send_Byte(add>>8);
		if( 1u == IO_I2C_WaitAck(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
		}
		else
		{
			IO_I2C_Send_Byte(add);
			if( 1u == IO_I2C_WaitAck(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
			}
			else
			{
				IO_I2C_Send_Byte(data);
				if( 1u == IO_I2C_WaitAck(time))
				{
					status = EEPROM_DATA_TIMEOUT;
				}
				else
				{
					IO_I2C_Stop();
				}
			}
		}
	}
#endif
	return (uint8_t)status;
}
/**
 * @brief  EEPROM写buff数据，
 * @param  address：写入的地址
 * @param  *data：写入的数据的首地址
 * @param  *lenght：数据长度，不能超过64字节
 * @param  time：超时时间 (time>20)
 * @retval 写状态
 */
EEPROM_Status EEPROM_WriteBuff(uint32_t address,const uint8_t *data,uint8_t lenght,uint32_t time)
{
	uint8_t i=0;
	EEPROM_Status status = EEPROM_OK;
	uint32_t add = address - EEPROM_BASE_ADDRESS;
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	sTimer_Type.timer_cnt = time;
	while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
	{
		if(EEPROM_Timeout(time) == 1u)
		{
			status = EEPROM_ADDRESS_TIMEOUT;
			break;
		}
	}
	
	if(status != EEPROM_ADDRESS_TIMEOUT)
	{
		I2C1->DBC = (uint32_t)(add>>8);
		
		sTimer_Type.timer_cnt = time;
		while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
		{
			if(1u == EEPROM_Timeout(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
				break;
			}
		}
		
		if(status != EEPROM_ADDRESS_TIMEOUT)
		{
			I2C1->DBC = (uint8_t)add;
			
			for(i=0; i<lenght; i++)
			{
				
				if(i < (lenght-1u))
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						I2C1->DBC = data[i];
					}
				}
				else
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						I2C1->DBC = ((uint32_t)data[i]| I2C_DBC_STOP_MASK);
					}
				}
			}
		}
	}
#else
	IO_I2C_Start();
	IO_I2C_Send_Byte(0xA0);
	if( 1u == IO_I2C_WaitAck(time))
	{
		status = EEPROM_SlaveID_TIMEOUT;
	}
	else
	{
		IO_I2C_Send_Byte(add>>8);
		if( 1u == IO_I2C_WaitAck(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
		}
		else
		{
			IO_I2C_Send_Byte(add);
			if( 1u == IO_I2C_WaitAck(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
			}
			else
			{
				for(i=0; i<lenght; i++)
				{
					IO_I2C_Send_Byte(data[i]);
					if( 1u == IO_I2C_WaitAck(time))
					{
						status = EEPROM_DATA_TIMEOUT;
						break;
					}
					else
					{
						if(i >= lenght-1u)
							IO_I2C_Stop();
					}
				}
				
			}
		}
	}
#endif
	return status;
}
/**
 * @brief  EEPROM写一页数据,页数据大小64byte
 * @param  address：写入的地址
 * @param  *data：写入的数据的首地址
 * @param  time：超时时间 (time>20)
 * @retval 写状态
 */
EEPROM_Status EEPROM_WritePage(uint8_t page,const uint8_t *data,uint32_t time)
{
	uint8_t i=0;
	EEPROM_Status status = EEPROM_OK;
	uint32_t add = (uint32_t)page*64u;
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	sTimer_Type.timer_cnt = time;
	while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
	{
		if(1u == EEPROM_Timeout(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
			break;
		}
	}
	
	if(status != EEPROM_ADDRESS_TIMEOUT)
	{
		I2C1->DBC = (uint32_t)(add>>8u);
		sTimer_Type.timer_cnt = time;
		while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
		{
			if(1u == EEPROM_Timeout(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
				break;
			}
		}
		
		if(status != EEPROM_ADDRESS_TIMEOUT)
		{
			I2C1->DBC = (uint8_t)add;
			
			for(i=0; i<64u; i++)
			{
				
				if(i < (64u-1u))
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						I2C1->DBC = data[i];//
					}
				}
				else
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						I2C1->DBC = ((uint32_t)data[i]| I2C_DBC_STOP_MASK);
					}
				}
			}
		}
	}
#else
	IO_I2C_Start();
	IO_I2C_Send_Byte(0xA0);
	if( 1u == IO_I2C_WaitAck(time))
	{
		status = EEPROM_SlaveID_TIMEOUT;
	}
	else
	{
		IO_I2C_Send_Byte(add>>8);
		if( 1u == IO_I2C_WaitAck(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
		}
		else
		{
			IO_I2C_Send_Byte(add);
			if( 1u == IO_I2C_WaitAck(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
			}
			else
			{
				for(i=0; i<64; i++)
				{
					IO_I2C_Send_Byte(data[i]);
					if( 1u == IO_I2C_WaitAck(time))
					{
						status = EEPROM_DATA_TIMEOUT;
						break;
					}
					else
					{
						if(i >= 64-1u)
							IO_I2C_Stop();
					}
				}
				
			}
		}
	}
#endif
	return status;
}
/**
 * @brief  EEPROM读一个字节
 * @param  address：读数据的地址
 * @param  data：写入的数据
 * @param  time：超时时间 (time>20)
 * @retval 读状态
 */
EEPROM_Status EEPROM_ReadByte(uint32_t address,uint8_t *data,uint32_t time)
{
	EEPROM_Status status = EEPROM_OK;
	uint32_t add = address - EEPROM_BASE_ADDRESS;
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	sTimer_Type.timer_cnt = time;
	while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
	{
		if(1u == EEPROM_Timeout(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
			break;
		}
	}
	
	if(status != EEPROM_ADDRESS_TIMEOUT)
	{
		I2C1->DBC = (uint32_t)(add>>8u);
		sTimer_Type.timer_cnt = time;
		while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
		{
			if(1u == EEPROM_Timeout(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
				break;
			}
		}
		
		if(status != EEPROM_ADDRESS_TIMEOUT)
		{
			I2C1->DBC = ((uint32_t)add|I2C_DBC_STOP_MASK);
			
			I2C1->DBC |= I2C_DBC_CMD_MASK|I2C_DBC_STOP_MASK;
			sTimer_Type.timer_cnt = time;
			while(0u == I2C_GetStatus(I2C1 ,I2C_ReceiveFIFONotEmptyStatus))
			{
				if(1u == EEPROM_Timeout(time))
				{
					status = EEPROM_DATA_TIMEOUT;
					break;
				}
			}
			*data = (uint8_t)(I2C1->DBC);
		}
	}
#else
	IO_I2C_Start();
	IO_I2C_Send_Byte(0xA0);
	if( 1u == IO_I2C_WaitAck(time))
	{
		status = EEPROM_SlaveID_TIMEOUT;
	}
	else
	{
		IO_I2C_Send_Byte(add>>8);
		if( 1u == IO_I2C_WaitAck(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
		}
		else
		{
			IO_I2C_Send_Byte(add);
			if( 1u == IO_I2C_WaitAck(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
			}
			else
			{
				IO_I2C_Start();
				IO_I2C_Send_Byte(0xA1);
				if( 1u == IO_I2C_WaitAck(time))
				{
					status = EEPROM_SlaveID_TIMEOUT;
				}
				else
				{
					*data = IO_I2C_Read_Byte(0);
					IO_I2C_Stop();
				}
			}
		}
	}
#endif
	return status;
}

/**
 * @brief  EEPROM读BUFF数据
 * @param  address：写入的地址
 * @param  *data：读入的数据首地址
 * @param  *data：读入的数据的长度
 * @param  time：超时时间 (time>20)
 * @retval 写状态
 */
EEPROM_Status EEPROM_ReadBuff(uint32_t address,uint8_t *data,uint16_t lenght,uint32_t time)
{
	uint8_t i=0;
	EEPROM_Status status = EEPROM_OK;
	uint32_t add = address - EEPROM_BASE_ADDRESS;
#if (USER_HARDWARE_OR_SOFTWARE == 1u)
	sTimer_Type.timer_cnt = time;
	while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
	{
		if(1u == EEPROM_Timeout(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
			break;
		}
	}
	
	if(status != EEPROM_ADDRESS_TIMEOUT)
	{
		I2C1->DBC = (uint32_t)(add>>8u);
		sTimer_Type.timer_cnt = time;
		while(0u == I2C_GetStatus(I2C1 ,I2C_TransmitFIFOEmptyStatus))
		{
			if(1u == EEPROM_Timeout(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
				break;
			}
		}
		if(status != EEPROM_ADDRESS_TIMEOUT)
		{
			I2C1->DBC = ((uint32_t)(add&0xFFu)|I2C_DBC_STOP_MASK);
			
			I2C1->DBC |= I2C_DBC_CMD_MASK;
			while(i < lenght)
			{
				if(i< (lenght-1u))
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						I2C1->DBC |= I2C_DBC_CMD_MASK;
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_ReceiveFIFONotEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						data[i] = (uint8_t)(I2C1->DBC);
						i++;
					}
				}
				else if(i< lenght)
				{
					if(status != EEPROM_ADDRESS_TIMEOUT)
					{
						I2C1->DBC |= (I2C_DBC_CMD_MASK|I2C_DBC_STOP_MASK);
						sTimer_Type.timer_cnt = time;
						while(0u == I2C_GetStatus(I2C1 ,I2C_ReceiveFIFONotEmptyStatus))
						{
							if(1u == EEPROM_Timeout(time))
							{
								status = EEPROM_DATA_TIMEOUT;
								break;
							}
						}
						data[i] = (uint8_t)(I2C1->DBC);
						i++;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
#else
	IO_I2C_Start();
	IO_I2C_Send_Byte(0xA0);
	if( 1u == IO_I2C_WaitAck(time))
	{
		status = EEPROM_SlaveID_TIMEOUT;
	}
	else
	{
		IO_I2C_Send_Byte(add>>8);
		if( 1u == IO_I2C_WaitAck(time))
		{
			status = EEPROM_ADDRESS_TIMEOUT;
		}
		else
		{
			IO_I2C_Send_Byte(add);
			if( 1u == IO_I2C_WaitAck(time))
			{
				status = EEPROM_ADDRESS_TIMEOUT;
			}
			else
			{
				IO_I2C_Start();
				IO_I2C_Send_Byte(0xA1);
				if( 1u == IO_I2C_WaitAck(time))
				{
					status = EEPROM_SlaveID_TIMEOUT;
				}
				else
				{
					for(i=0; i<lenght-1u;i++)
					{
						data[i] = IO_I2C_Read_Byte(1);
					}
					data[i] = IO_I2C_Read_Byte(0);
					IO_I2C_Stop();
				}
			}
		}
	}
#endif
	return status;
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




