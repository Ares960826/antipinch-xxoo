/**
  ******************************************************************************
  * @file     system_XL6600.c
  * @author   xu.wang
  * @version  V3.0.0
  * @date     4-Jun-2019
  * @brief    This file provide function about system XL6600 firmware program 
	* 					Provides a system configuration function and a global variable that contains
	*           the system frequency. It configures the device and initializes the oscillator
	*           (PLL) that is part of the microcontroller device.
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

/* Includes ---------------------------------------------------------------*/

#include "system_xl6600.h"
#include "xl6600.h"
#include "xl_sim.h"
#include "xl_wdog.h"
#include "xl_ics.h"
#include "xl_osc.h"
#include "xl_flash.h"

static uint32_t OSC_ClockSource;


/**
 * @brief  SystemInit����
 */
void SystemInit(void) 
{
	FMC->FCPC0 |= FMC_FCPC0_CEN_MASK;
	
	SIM_SCGC_Cmd(SIM_SCGC_WDG,ENABLE);
	WDOG_EnableCmd(WDOG,ENABLE);
	WDOG_ClrInt(WDOG);
	WDOG_CountRestart(WDOG);
	WDOG_DeInit(WDOG);
	WDOG_EnableCmd(WDOG,DISABLE);
	
	SIM_SCGC_Cmd(SIM_SCGC_WDG,DISABLE);

}

/**
 * @brief �����ڲ�ʱ��
 * @param  ICS_IRCSel: IRCƵ��ѡ��	# IRC��Internal Reference Clock��Ƶ�����ڲ��ο�ʱ�ӵ�Ƶ�ʣ�������Ϊϵͳʱ�ӵĲο�
 *			@arg ICS_IRC_50K ��50K
 *			@arg ICS_IRC_37o5K ��37.5K
 * @param  FactorValue: ��Ƶϵ��			# FLL��Frequency-Locked Loop��
 *			@arg ICS_FLLFACTOR_1280 ��1280��Ƶ
 *			@arg ICS_FLLFACTOR_1920 ��1920��Ƶ
 * @retval None
 * FLL �ϵ�׶δ�FLASH����������
 */
SYS_CLK_STATUS SystemSetFEI(uint8_t ICS_IRCSel, uint8_t ICS_FLLFSel)
{
	uint32_t coreclk;
	uint32_t busclk;
	uint32_t timeout = 0xFFFFFu;
	
	SYS_CLK_STATUS ClkState = SYS_CLK_OK;	// SYS_CLK_OK=0
	
	//FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	
	// ����ⲿ����ʹ��,�Ƚ�����
	if((OSC->CR & OSC_CR_OSCEN_MASK) == OSC_CR_OSCEN_MASK)	/*
	* OSC->CR=111 0000 0000; OSC_CR_OSCEN_MASK=1000 0000; OSC_CR_OSCEN_MASK=0x80u=1000 0000
	* */
	{
		// ѡ���ڲ�ʱ��
		ICS_ClocksSelect(ICS_CLOCKS_IRC); /*
		* ICS_CLOCKS_IRC=(uint8_t)0x01*/
		
		// �����ⲿ����
		OSC->CR &= ~OSC_CR_OSCEN_MASK; /*
		* ~OSC_CR_OSCEN_MASK=~(0x80u)=0111 1111=0x7Fu*/
		OSC->CR |= 0x16u; /*
		* OSC->CR=(0x7Fu || 0x16u)=(0111 1111||0001 0110)=0111 1111=0x7Fu*/
		OSC->CR |= OSC_CR_OSCEN_MASK;/*
		* OSC->CR=(0x7Fu || 0x80u)=(0111 1111||1000 0000)=1111 1111=0xFF*/
		// �ȴ��ⲿ�������
		while((OSC->CR & OSC_CR_OSCINIT_MASK) != OSC_CR_OSCINIT_MASK)/*
		* (0xFFu&0x01u)=0x01u != 0x01u*/
		{
			timeout--;	//1048575
			if((timeout<50u)||(timeout>0xFFFFFu))
			{	// ����ʧ�����˳� QUESTION
				OSC->CR &= ~OSC_CR_OSCEN_MASK;/*
				* OSC->CR=0xFFu; ~(OSC_CR_OSCEN_MASK)=~(0x80u)=0x7Fu
				* -> OSC->CR=0xFFu&0x7Fu=1111 1111 & 0111 1111=0x7Fu*/
				break;
			}
		}
		// �����ⲿ����
		OSC->CR &= ~OSC_CR_OSCEN_MASK;
	}
	// ѡ���ڲ�ʱ��
	ICS_ClocksSelect(ICS_CLOCKS_IRC);	/*
	* ICS_CLOCKS_IRC��ʱ��ԴΪ�ڲ�ʱ��(IRC)*/
	FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);	// Flash���� �ȴ�(2CYCLE-2)����
	if(ICS_IRCSel == ICS_IRC_50K)//50k	// IRC Ƶ��ѡ��
	{
		ICS_IRCSelect(ICS_IRC_50K);
		if(ICS_FLLFSel == ICS_FLLFACTOR_1920) // ��Ƶϵ��ѡ��
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
			coreclk = 96000000;
		}
		else//1280
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
			coreclk = 64000000;
		}
	}
	else//37.5k
	{
		ICS_IRCSelect(ICS_IRC_37o5K);
		if(ICS_FLLFSel == ICS_FLLFACTOR_1920)//72
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
			coreclk = 72000000;
		}
		else//1280
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
			coreclk = 48000000;
		}
	}
	// ѡ���ڲ��ο�ʱ��
	ICS_IREFSSelect(ICS_IREFS_IRC);
	ICS_IRCEnableCmd(ENABLE);	// �����ڲ���׼ʱ��(IRC) - ʹ�� IRC
	ICS_FllLPModeStopEnableCmd(DISABLE);	// FLL�ڵ͹�����״̬ѡ�� - ֹͣ�͹���ģʽ
	// �ȴ�����
	timeout = 0xFFFFFu;
	while(0u == ICS_GetStatus(ICS_STATUS_LOCK))
	{
		timeout--;
		if((timeout<50u)||(timeout>0xFFFFFu))
		{
			ClkState = ICS_STATUS_UNLOCK;
			break;
			//return feeState;
		}
	}
	if(ClkState == SYS_CLK_OK)
	{	// ���ݺ���Ƶ����������Ƶ��
		//coreclk = Get_SystemCoreClock();
		if(coreclk > 50000000u)
		{
			 //SIM_CLKDIV_OUTDIV2(2u);
			busclk = coreclk>>1u;	// ��Ƶ��һ��
		}
		// ��ʼ��Flash
		timeout = 0xFFFFFu;
		while(FLASH_ERR_SUCCESS != FLASH_Init((uint8_t)(busclk/1000000u)))
		{
			timeout--;
			if((timeout<50u)||(timeout>0xFFFFFu))
			{
				ClkState = FLASH_INIT_ERROR;
				break;
				//return feeState;
			}
		}
		if(ClkState == SYS_CLK_OK)
		{	// ��������Ƶ������Flash�ȴ�����
			if(busclk > 90000000u)	
			{
				FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
			}
			else if(busclk > 60000000u)
			{
				FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
			}
			else if(busclk > 30000000u)
			{
				FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
			}
			else
			{
				FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
			}
		}
		else
		{
			FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
		}
		// ���ݺ���Ƶ����������ʱ�ӷ�Ƶ
		if(coreclk > 50000000u)
		{
			 SIM_CLKDIV_OUTDIV2(2u);
		}
		else//20210807 AFT
		{
			SIM_CLKDIV_OUTDIV2(1u);//20210807 AFT
		}
		// ѡ�� FLL ��Ϊϵͳʱ��
		ICS_ClocksSelect(ICS_CLOCKS_FLL);
	}

	return ClkState;
}
/**
 * @brief ʹ���ⲿʱ��
 * @param  osc_clkfre: �ⲿ����Ƶ��
 * @param  ICS_FLLFSel: ��Ƶϵ��
 *			@arg ICS_FLLFACTOR_1280 ��1280��Ƶ
 *			@arg ICS_FLLFACTOR_1920 ��1920��Ƶ
 * @param  osc_bdiv: OSC��һ��Ƶ��
 *		�����������ȡ�����ֵ:
 *			@arg ICS_RDIV_1or32   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ1  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ32��
 *			@arg ICS_RDIV_2or64   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ2  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ64��
 *			@arg ICS_RDIV_4or128  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ4  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ128��
 *			@arg ICS_RDIV_8or256  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ8  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ256��
 *			@arg ICS_RDIV_16or512 ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ16 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ512��       
 *			@arg ICS_RDIV_32or1024��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ32 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ1024��
 *			@arg ICS_RDIV_64      ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ64 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 *			@arg ICS_RDIV_128     ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ128��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 * @param  osc_bdiv2: OSC�ڶ���Ƶ��
 *		�����������ȡ�����ֵ:
 *			@arg ICS_RDIV2_1  ��1��Ƶ
 *			@arg ICS_RDIV2_2  ��2��Ƶ
 *			@arg ICS_RDIV2_3  ��3��Ƶ
 *			@arg ICS_RDIV2_4  ��4��Ƶ
 *			@arg ICS_RDIV2_5  ��5��Ƶ  
 *			@arg ICS_RDIV2_6  ��6��Ƶ
 *			@arg ICS_RDIV2_7  ��7��Ƶ
 *			@arg ICS_RDIV2_8  ��8��Ƶ
 * @retval None
 */
SYS_CLK_STATUS SystemSetFEE(uint32_t osc_clkfre, uint8_t ICS_FLLFSel, uint8_t osc_bdiv,uint8_t osc_bdiv2)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
	
	uint32_t temp;
	uint32_t temp1;
	//uint8_t stat_flag;
  uint32_t coreclk;
	uint32_t busclk;
	uint32_t timeout = 0xFFFFu;

	SYS_CLK_STATUS ClkState = SYS_CLK_OK;
	
	
	OSC_EnableCmd(DISABLE);
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u==OSC_GetInitStatus())
	{
		timeout--;
		if((timeout<50u)||(timeout>0xFFFFu))
		{
			ClkState = OSC_INIT_ERROR;
			break;
			//return feeState;
		}
	}
	
	if(ClkState == SYS_CLK_OK)
	{
		//FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	
		if(OSC_RANGE_HIGH == OSC_GetRange())
		{
			temp = (uint32_t)((uint32_t)1u<<(osc_bdiv+5u));
			temp *= ((uint32_t)osc_bdiv2+1u);
		}
		else
		{
			temp = (uint32_t)((uint32_t)1u<<(osc_bdiv));
			temp *= ((uint32_t)osc_bdiv2+1u);
		}
			
		temp1 = osc_clkfre/temp;
		
		if((temp1<30000u) || (temp1>65000u))
		{
			//stat_flag=0;
			ClkState = OSC_DIV_ERROR;
			
			OSC_EnableCmd(DISABLE);
			sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
			sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
			sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
			OSC_Init(&sOSC_InitTypeDef);
			OSC_EnableCmd(DISABLE);
		}
		else
		{
			
			ICS_BaseDivider(osc_bdiv);//�����ⲿʱ�ӷ�Ƶֵ
			
			ICS_BaseDivider2(osc_bdiv2);
			
			ICS_ClocksSelect(ICS_CLOCKS_IRC);
			FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
			if(ICS_FLLFSel == ICS_FLLFACTOR_1920)
			{
				ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
				coreclk = temp1 * 1920;
			}
			else//1280
			{
				ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
				coreclk = temp1 * 1280;
			}
			/*FLL is not must close in stop mode*/
			//ICS_FllStopModeCloseEnableCmd(ICS,DISABLE);
			
			//SystemSetFBI();//�ڲ���·ʱ��		
			//ICS_ClocksSelect(ICS_CLOCKS_IRC);
			
			ICS_IREFSSelect(ICS_IREFS_OSC); 
			
			/*FLL ����·ģʽ�²�����*/
			ICS_FllLPModeStopEnableCmd(DISABLE);
			
			timeout = 0xFFFFu;
			
			while(0u==ICS_GetStatus(ICS_STATUS_LOCK))
			{
				timeout--;
				if((timeout<50u)||(timeout>0xFFFFu))
				{
					ClkState = ICS_STATUS_UNLOCK;
					break;
					//return feeState;
				}
			}
			if(ClkState == SYS_CLK_OK)
			{
				OSC_ClockSource = osc_clkfre;
				/*ѡ��IREFS(FLL)ʱ��ԴΪ�ⲿʱ��*/
				//ICS_IREFSSelect(ICS_IREFS_OSC); 
					
				//coreclk = Get_SystemCoreClock();
				
				if(coreclk > 50000000u)
				{
					//SIM_CLKDIV_OUTDIV2(2);
					busclk = coreclk>>1u;
				}
					
				timeout = 0xFFFFFu;
				while(FLASH_ERR_SUCCESS != FLASH_Init((uint8_t)(busclk/1000000u)))
				{
					timeout--;
					if((timeout<50u)||(timeout>0xFFFFu))
					{
						ClkState = FLASH_INIT_ERROR;
						break;
					}
				}
				if(ClkState == SYS_CLK_OK)
				{
					if(busclk > 90000000u)	
					{
						FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
					}
					else if(busclk > 60000000u)
					{
						FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
					}
					else if(busclk > 30000000u)
					{
						FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
					}
					else
					{
						FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
					}
					
					if(coreclk > 50000000u)
					{
						SIM_CLKDIV_OUTDIV2(2);
					}
					ICS_ClocksSelect(ICS_CLOCKS_FLL);
				}
				else
				{
					FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
				}
			}
			else
			{
				ICS_IREFSSelect(ICS_IREFS_IRC); 
				
				OSC_EnableCmd(DISABLE);
				sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
				sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
				sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
				OSC_Init(&sOSC_InitTypeDef);
				OSC_EnableCmd(DISABLE);
			}
		}
	}
	else
	{
		OSC_EnableCmd(DISABLE);
		sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
		sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
		sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
		OSC_Init(&sOSC_InitTypeDef);
		OSC_EnableCmd(DISABLE);
	}
	
	
	return ClkState;
}

/**
 * @brief �ڲ���·
 * @param  None
 * @retval �ڲ���·ʱ�ӵ�Ƶ��
 */
uint32_t SystemSetFBI(void)
{
	uint32_t temp;
        uint32_t coreclk;
	/* ICS Clocks is IRC*/
	ICS_ClocksSelect(ICS_CLOCKS_IRC);
	/*FLL ����·ģʽ�²�����*/
	ICS_FllLPModeStopEnableCmd(DISABLE);
	
	if(ICS_GetIRCFre() == ICS_IRC_37o5K)
	{
		temp = 150000u;
	}
	else
	{
		temp = 100000u;
	}
	
        coreclk = Get_SystemCoreClock();
        if(coreclk > 50000000u)
         {
             SIM_CLKDIV_OUTDIV2(2);
         }
        
	if(Get_BusClock() > 90000000u)	
	{
		FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
	}
	else if(Get_BusClock() > 60000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	}
	else if(Get_BusClock() > 30000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
	}
	else
	{
		FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
	}
	
	return temp;
}
/**
 * @brief �ڲ���·�͹���
 * @param  None
 * @retval None
 */
void SystemSetFBILP(void)
{
	/* ICS Clocks is IRC*/
	ICS_ClocksSelect(ICS_CLOCKS_IRC);
	//ICS_IRCSelect(ICS_IRC_37o5K);
	//ICS_IREFStopEnableCmd(ENABLE);
	/*FLL Factor is 1280*/
	ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
	/*FLL is must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(ENABLE);
	
	//ICS_FllLPModeStopEnableCmd(ENABLE);
}
/**
 * @brief �ⲿ��·
 * @param  None
 * @retval None
 */
void SystemSetFBE(uint32_t osc_clkfre)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
        uint32_t coreclk;
	
	OSC_EnableCmd(DISABLE);
	
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u==OSC_GetInitStatus()){};
	
	/*ѡ��ICSΪ�ⲿ��׼ʱ��*/		
	ICS_ClocksSelect(ICS_CLOCKS_OSC);		
	
	/*ѡ��IREFS(FLL)ʱ��ԴΪ�ⲿʱ��*/
	ICS_IREFSSelect(ICS_IREFS_OSC);
	
	/*ѡ��IREFS��stopģʽ�²�ֹͣʹ��*/
	ICS_IREFStopEnableCmd(DISABLE);
	
	/*FLL Factor is 1280*/
	ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
	/*FLL is not must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(DISABLE);
	/*FLL ����·ģʽ�²�����*/
	ICS_FllLPModeStopEnableCmd(ENABLE);
	
	//ICS_IRCEnableCmd(ICS,DISABLE);
	OSC_ClockSource = osc_clkfre;
        
        coreclk = Get_SystemCoreClock();
        if(coreclk > 50000000u)
         {
             SIM_CLKDIV_OUTDIV2(2);
         }
	
	if(Get_BusClock() > 90000000u)	
	{
		FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
	}
	else if(Get_BusClock() > 60000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	}
	else if(Get_BusClock() > 30000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
	}
	else
	{
		FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
	}
		
}
/**
 * @brief �ⲿ��·�͹���
 * @param  ICSx: ָ��ICS����
 * @param  FactorValue: ��Ƶϵ��
 *			@arg ICS_FLLFactorSelect1280 ��1280��Ƶ
 *			@arg ICS_FLLFactorSelect1920 ��1920��Ƶ
 * @retval None
 */
void SystemSetFBELP(void)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
	
	OSC_EnableCmd(DISABLE);
	
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u != OSC_GetInitStatus()){};
	
	/*ѡ��ICSΪ�ⲿ��׼ʱ��*/
	ICS_ClocksSelect(ICS_CLOCKS_OSC);
	
	/*ѡ��IREFS��stopģʽ�²�ֹͣʹ��*/
	ICS_IREFStopEnableCmd(ENABLE);
	
	/*FLL is must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(ENABLE);
}


/**
 * @brief ��ȡFLLOutCLK�����ʱ��Ƶ��
 * @param  None
 * @retval FLL�����ʱ��Ƶ��
 */
static uint32_t Get_FllOutClock(void)
{
	uint32_t FLL_OutClock;
	uint32_t rdiv_flag;
	uint32_t rdiv2_flag;
	uint32_t rdiv_value;
	if(ICS_IREFS_IRC == ICS_GetIREFSSelect())//�ڲ�ʱ��Դ
	{
		if(ICS_IRC_37o5K == ICS_GetIRCFre())
		{
			if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
			{
				FLL_OutClock = 37500 * 1920;
			}
			else
			{
				FLL_OutClock = 37500 * 1280;
			}
		}
		else
		{
			if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
			{
				FLL_OutClock = 50000 * 1920;
			}
			else
			{
				FLL_OutClock = 50000 * 1280;
			}
		}
	}
	else//�ⲿʱ��
	{
		rdiv_flag = ICS_GetBaseDivider();
		rdiv2_flag = ICS_GetBaseDivider2();
		if(OSC_RANGE_HIGH == OSC_GetRange())
		{
			rdiv_value = (uint32_t)((uint32_t)1u<<(rdiv_flag+5u));
		}
		else
		{
			rdiv_value = (uint32_t)((uint32_t)1u<<(rdiv_flag));
		}
		rdiv_value = rdiv_value*rdiv2_flag;
		if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
		{
			FLL_OutClock = (OSC_ClockSource/rdiv_value) * 1920u;
		}
		else
		{
			FLL_OutClock = (OSC_ClockSource/rdiv_value) * 1280u;
		}
	}
	return FLL_OutClock;
}

/**
 * @brief ��ȡIcsOutCLK�����ʱ��Ƶ��
 * @param  None
 * @retval FLL�����ʱ��Ƶ��
 */
uint32_t Get_ICSOUTClock(void)
{
	uint8_t bdiv_value;
	uint32_t fll_outfre;
	fll_outfre = Get_FllOutClock();
	bdiv_value = ICS_GetBusDivder();
	
	return (fll_outfre/((uint32_t)bdiv_value+1u));
}

/**
 * @brief ��ȡ���뵽Core��ʱ��Ƶ��
 * @param  None
 * @retval ���뵽Core��ʱ��Ƶ��
 */
uint32_t Get_SystemCoreClock(void)
{
	uint32_t ics_outclk;
	uint8_t outdiv1_value;
	
	ics_outclk = Get_ICSOUTClock();
	
	outdiv1_value = SIM_GetOUTDIV1();
	
	return (ics_outclk/((uint32_t)outdiv1_value+1u));
}

/**
 * @brief ��ȡ���뵽FTM��PWT��ʱ��Ƶ��
 * @param  None
 * @retval ���뵽FTM��PWT��ʱ��Ƶ��
 */
uint32_t Get_FTM_PWT_Clock(void)
{
	uint32_t ics_outclk;
	uint8_t outdiv4_value;
	
	ics_outclk = Get_ICSOUTClock();
	
	outdiv4_value = SIM_GetOUTDIV4();
	
	return (ics_outclk/((uint32_t)outdiv4_value+1u));
}
/**
 * @brief ��ȡ���뵽BUS��Flash��ʱ��Ƶ��
 * @param  None
 * @retval ���뵽BUS��Flash��ʱ��Ƶ��
 */
uint32_t Get_BusClock(void)
{
	uint32_t core_clk;
	uint8_t outdiv2_value;
	
	core_clk = Get_SystemCoreClock();
	
//	if(core_clk > 50000000)
//	{
//		 SIM_CLKDIV_OUTDIV2(2);
//	}
	
	outdiv2_value = SIM_GetOUTDIV2();
	
	return (core_clk/((uint32_t)outdiv2_value+1u));
}
/**
 * @brief ��ȡ���뵽�����ʱ��Ƶ��
 * @param  None
 * @retval ���뵽�����ʱ��Ƶ��
 */
uint32_t Get_PeripheralClock(void)
{
	uint32_t bus_clk;
	uint8_t outdiv3_value;
	
	bus_clk = Get_BusClock();

	
	
	outdiv3_value = SIM_GetOUTDIV3();
	
	return (bus_clk/((uint32_t)outdiv3_value+1u));
}


