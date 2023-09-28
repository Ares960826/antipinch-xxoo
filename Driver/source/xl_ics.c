/**
  ******************************************************************************
  * @file     xl_ics.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about ICS firmware program 
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
#include "xl_ics.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup ICS ISC Module 
  * @brief ICS Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

	
/** @defgroup ICS_Private_Functions
  * @{
 */ 	

/**
 * @brief  ��ICS����Ĵ����ָ�Ĭ��ֵ
 * @param  ICSx: ָ��ICS����
 * @retval None
 */
void ICS_DeInit(void)
{
	/* Deinitializes to default reset values */
	ICS->C1 = 0x04;
	ICS->C2 = 0x02;
	ICS->C3 = 0x00;
	ICS->C4 = 0x00;
}

/**
 * @brief ʱ��Դѡ��
 * @param  Clksel: ʱ��Դѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ICS_CLOCKS_FLL��ʱ��ԴΪFLL���         
 *			@arg ICS_CLOCKS_IRC��ʱ��ԴΪ�ڲ�ʱ��(IRC)    
 *			@arg ICS_CLOCKS_OSC��ʱ��ԴΪ�ⲿʱ��(OSC)   
 *			@arg ICS_CLOCKS_RESERVED������
 * @retval None
 */
void ICS_ClocksSelect(uint8_t Clksel)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_CLKS_MASK;
	
	temp |= (uint8_t)(Clksel<<ICS_C1_CLKS_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief ʱ�ӻ�׼��Ƶ
 * @param  BDiv: ��Ƶϵ��
 *		�����������ȡ�����ֵ:
 *			@arg ICS_RDIV_1or32   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ1  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ32��
 *			@arg ICS_RDIV_2or64   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ2  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ64��
 *			@arg ICS_RDIV_4or128  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ4  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ128��
 *			@arg ICS_RDIV_8or256  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ8  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ256��
 *			@arg ICS_RDIV_16or512 ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ16 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ512��       
 *			@arg ICS_RDIV_32or1024��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ32 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ1024��
 *			@arg ICS_RDIV_64      ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ64 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 *			@arg ICS_RDIV_128     ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ128��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 * @retval None
 */
void ICS_BaseDivider(uint8_t RDiv)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_RDIV_MASK;
	
	temp |= (uint8_t)(RDiv<<ICS_C1_RDIV_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief ʱ�ӻ�׼��Ƶ2
 * @param  BDiv: ��Ƶϵ��
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
void ICS_BaseDivider2(uint8_t RDiv2)
{
	uint8_t temp;
	
	temp = ICS->C4;
	
	temp &= ~ICS_C4_RDIV2_MASK;
	
	temp |= (uint8_t)(RDiv2<<ICS_C4_RDIV2_SHIFT);
	
	ICS->C4 = temp;
}

/**
 * @brief ʱ�ӻ�׼��Ƶ
 * @param  None
 * @retval ��Ƶֵ
 *		�����������ȡ�����ֵ:
 *			@arg ICS_RDIV_1or32   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ1  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ32��
 *			@arg ICS_RDIV_2or64   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ2  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ64��
 *			@arg ICS_RDIV_4or128  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ4  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ128��
 *			@arg ICS_RDIV_8or256  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ8  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ256��
 *			@arg ICS_RDIV_16or512 ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ16 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ512��       
 *			@arg ICS_RDIV_32or1024��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ32 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ1024��
 *			@arg ICS_RDIV_64      ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ64 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 *			@arg ICS_RDIV_128     ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ128��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 */
uint8_t ICS_GetBaseDivider(void)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ICS_C1_RDIV_MASK;
	
	temp >>= ICS_C1_RDIV_SHIFT;
	
	return temp;
}

/**
 * @brief ��ȡOSC�Ļ�׼��Ƶ��2�ķ�Ƶֵ
 * @param  None
 * @retval ��Ƶֵ
 *		�����������ȡ�����ֵ:
 *			@arg ICS_RDIV_1or32   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ1  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ32��
 *			@arg ICS_RDIV_2or64   ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ2  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ64��
 *			@arg ICS_RDIV_4or128  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ4  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ128��
 *			@arg ICS_RDIV_8or256  ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ8  ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ256��
 *			@arg ICS_RDIV_16or512 ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ16 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ512��       
 *			@arg ICS_RDIV_32or1024��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ32 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ1024��
 *			@arg ICS_RDIV_64      ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ64 ��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 *			@arg ICS_RDIV_128     ��(OSC_CR[RANGE]=0)Ƶ�ʷ�ΧΪ32kHz��Ƶ��Χ����Ƶϵ��Ϊ128��Ƶ�ʷ�ΧΪ4-24MHz��Ƶ��Χ����Ƶϵ��Ϊ������
 */
uint8_t ICS_GetBaseDivider2(void)
{
	uint8_t temp;
	temp = ICS->C4;
	
	temp &= ICS_C4_RDIV2_MASK;
	
	temp >>= ICS_C4_RDIV2_SHIFT;
	
	return temp + 1u;
}

/**
 * @brief FLLʱ�ӻ�׼ѡ��
 * @param  FllSel: FLLѡ��Ļ�׼ʱ��Դ
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_IREFS_OSC ���ⲿOSCʱ��Դ
 *			@arg ICS_IREFS_IRC ���ڲ�IRCʱ��Դ
 * @retval None
 * 	NOTE:
 * 		(1-60)3.6 ʱ��ģ��->3.6.1 ICS ����
 */
void ICS_IREFSSelect(uint8_t FllSel)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_IREFS_MASK;
	
	temp |= (uint8_t)(FllSel<<ICS_C1_IREFS_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief �ڲ���׼ʱ��(IRC)ʹ��
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ���ڲ���׼ʱ��(IRC)��Ч
 *			@arg DISABLE ���ڲ���׼ʱ��(IRC)��Ч
 * @retval None
 */
void ICS_IRCEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C1 |= ICS_C1_IRCLKEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C1 &= ~ICS_C1_IRCLKEN_MASK;
	}
}

/**
 * @brief  �ڲ���׼ʱ��ֹͣʹ�ܣ������ڲ�ʱ����ICS����Stopģʽʱ�Ƿ񱣳�ʹ��
 * @param  ICSx: ָ��ICS����
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ���ڲ���׼ʱ����stopģʽ�½���
 *			@arg DISABLE ���ڲ���׼ʱ����stopģʽ�²�����
 * @retval None
 */
void ICS_IREFStopEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C1 &= ~ICS_C1_IREFSTEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C1 |= ICS_C1_IREFSTEN_MASK;
	}
}
/**
 * @brief  ����ʱ�ӷ�Ƶ
 * @param  BDiv: ��Ƶϵ��(1-128)
 * @retval None
 */
void ICS_BusDivder(uint8_t BDiv)
{
	uint8_t temp;
	
	temp = ICS->C2;
	
	temp &= ~ICS_C2_BDIV_MASK;
	
	temp |= (uint8_t)((BDiv-1u) << ICS_C2_BDIV_SHIFT);
	
	ICS->C2 = temp;
}

/**
 * @brief  �õ�ICS_OUTCLK�ķ�Ƶֵ
 * @param  None
 * @retval ��Ƶֵ
 */
uint8_t ICS_GetBusDivder(void)
{	
	return (uint8_t)(ICS->C2 >> 1);
}

/**
 * @brief  FLL�ڵ͹����ǽ���ѡ��
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ���͹���ģʽ�½���
 *			@arg DISABLE ���͹���ģʽ�²�����
 * @retval None
 */
void ICS_FllLPModeStopEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C2 |= ICS_C2_LP_MASK;
	}
	else 
	{
		/*  */
		ICS->C2 &= ~ICS_C2_LP_MASK;
	}
}

/**
 * @brief  ʧ���ж�ʹ�ܣ��ù�����FLL��ʧ����Ч
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��ʧ���ж�
 *			@arg DISABLE ����ʹ��ʧ���ж�
 * @retval None
 */
void ICS_LosingLockIntEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 |= ICS_C4_LOLIE_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 &= ~ICS_C4_LOLIE_MASK;
	}
}
/**
 * @brief  ʧ���ж�ʹ�ܣ��ù�����FLL��ʧ����Ч
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ��FLL��stopģʽ��ǿ�ƹضϣ���LPΪ0
 *			@arg DISABLE ��FLL��stopģʽ�¸���LP��־ѡ��ض�
 * @retval None
 */
void ICS_FllStopModeCloseEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 &= ~ICS_C4_FLLSTEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 |= ICS_C4_FLLSTEN_MASK;
	}
}
/**
 * @brief ʱ�Ӽ��ʹ��
 * @param  State: ʹ��״̬
 *	 �����������ȡ�����ֵ:
 *			@arg ENABLE ����ʧ�ⲿʱ��ʱ����һ����λ����
 *			@arg DISABLE ������ʱ�Ӽ��
 * @retval None
 */
void ICS_ClockMonitorEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 |= ICS_C4_CME_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 &= ~ICS_C4_CME_MASK;
	}
}

/**
 * @brief  IRCʱ��ѡ��
 * @param  IRCValue: IRCʱ��
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_IRC_50K ��IRCΪ54kHz
 *			@arg ICS_IRC_37o5K ��IRCΪ37.5kHz
 * @retval None
 */
void ICS_IRCSelect(uint8_t IRCValue)
{
	uint32_t temp;
	
	temp = ICS->CFG;
	
	temp &= ~ICS_CFG_IRCSEL_MASK;
	
	temp |= (uint32_t)(0x55690000u | (uint32_t)((uint32_t)IRCValue << (uint32_t)ICS_CFG_IRCSEL_SHIFT));
	
	ICS->CFG = temp;
}

/**
 * @brief FLL��Ƶѡ��
 * @param  FactorValue: ��Ƶϵ��
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_FLLFACTOR_1280 ��1280��Ƶ
 *			@arg ICS_FLLFACTOR_1920 ��1920��Ƶ
 * @retval None
 * NOTE:
 * 	(1-237)16.4.7.1 FLL(��Ƶ��)ʱ������ ȷ��Ƶ��
 */
void ICS_FllFactorSelect(uint8_t FactorValue)
{
	uint32_t temp;
	
	temp = ICS->CFG;
	
	temp &= ~ICS_CFG_FLLFSEL_MASK;
	
	temp |= (uint32_t)(0x55690000u | (uint32_t)FactorValue);
	
	ICS->CFG = temp;
}

/**
 * @brief ��ȡICS״̬
 * @param  Status: ��Ҫ��ȡ��״̬��־
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_STATUS_LOSINGLOCK ��ʧ��״̬��ָ��FLL����״̬
 *			@arg ICS_STATUS_LOCK ������״̬��ָʾFLL�Ƿ��Ѿ���ȡ����
 *			@arg ICS_STATUS_IREF ���ڲ���׼״̬��Ϊ0����׼ʱ����Դ���ⲿʱ�ӣ�Ϊ1����׼ʱ����Դ���ڲ�ʱ��
 * @retval ���ض�ӦICS״̬�ı�־
 *	 �����������ȡ�����ֵ:
 *			@arg 1 ��״̬��1
 *			@arg 0 ��״̬��0
 */
uint8_t ICS_GetStatus(uint8_t ICSStatus)
{
	uint8_t sta;
	if(ICSStatus == (ICSStatus & ICS->S))
	{
		sta = 1;
	}
	else
	{
		sta = 0;
	}
	return sta;
}

/**
 * @brief ��ȡʱ��ģʽ
 * @param  Status: ��Ҫ��ȡ��״̬��־
 * @retval ���ض�ӦICS״̬�ı�־
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_MODE_FLL ��ʱ��ģʽΪFLL���
 *			@arg ICS_MODE_IRC ��ʱ��ģʽΪ�ڲ���׼ʱ��(IRC)
 *			@arg ICS_MODE_OSC ��ʱ��ģʽΪ�ⲿ��׼ʱ��(OSC)
 *			@arg ICS_MODE_RESERVED ������
 */
uint8_t ICS_GetClockMode(void)
{
	uint8_t temp;
	
	uint8_t clkmode;
	
	temp = ICS->S & ICS_S_CLKST_MASK;
	
	temp >>= ICS_S_CLKST_SHIFT;
	
	if(temp == ICS_MODE_FLL)
	{
		clkmode = ICS_MODE_FLL;
	}
	else if(temp == ICS_MODE_IRC)
	{
		clkmode =  ICS_MODE_IRC;
	}
	else if(temp == ICS_MODE_OSC)
	{
		clkmode =  ICS_MODE_OSC;
	}
	else
	{
		clkmode =  ICS_MODE_RESERVED;
	}
	return clkmode;
}

/**
 * @brief ��ȡIREFʱ��Դ
 * @param  None
 * @retval IREF��ʱ��Դ��־
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_IREFS_OSC ���ⲿOSCʱ��Դ
 *			@arg ICS_IREFS_IRC ���ڲ�IRCʱ��Դ
 */
uint8_t ICS_GetIREFSSelect(void)
{
	uint8_t temp;
	
	if((ICS->C1 & (uint8_t)0x04) == (uint8_t)0x04)
	{
		temp = ICS_IREFS_IRC;
	}
	else
	{
		temp = ICS_IREFS_OSC;
	}
	return temp;
}

/**
 * @brief ��ȡ��ǰIRCʱ��Ƶ��
 * @retval ���ض�ӦICS״̬�ı�־
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_IRC_50K ��IRCƵ��Ϊ100k
 *			@arg ICS_IRC_37o5K ��IRCƵ��Ϊ150k
 */
uint8_t ICS_GetIRCFre(void)
{
	uint8_t temp;
	if((ICS->CFG & (uint32_t)0x2) == (uint32_t)0x2)
	{
		temp = ICS_IRC_37o5K;
	}
	else
	{
		temp = ICS_IRC_50K;
	}
	return temp;
}

/**
 * @brief ��ȡ��ǰFLL��Ƶ���ı���
 * @retval ���ض�ӦFLL��Ƶ��ϵ���ı�־
 *	 �����������ȡ�����ֵ:
 *			@arg ICS_FLLFACTOR_1280 ��FLL��Ƶϵ����1280��
 *			@arg ICS_FLLFACTOR_1920 ��FLL��Ƶϵ����1920��
 */
uint8_t ICS_GetFLLMultiple(void)
{
	uint8_t temp;
	if((ICS->CFG & (uint32_t)0x1) == (uint32_t)0x1)
	{
		temp = ICS_FLLFACTOR_1920;
	}
	else
	{
		temp = ICS_FLLFACTOR_1280;
	}
	return temp;
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

