/**
  ******************************************************************************
  * @file     xl_port.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PORT firmware program 
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
#include "xl_port.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PORT PORT Module
  * @brief PORT Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PORT_Private_Functions
  * @{
  */ 

/**
  * @brief PORTĬ�ϳ�ʼ��
  * @param  None.
  * @retval None.
  */ 
void PORT_DeInit(void)
{
	/* Deinitializes to default reset values */
	PORT->IOFLT0 = 0x00C00000;
	PORT->IOFLT1 = 0x00000000;
	PORT->PUE0 = 	 0x00100000;
	PORT->PUE1 = 	 0x00000000;
	PORT->PUE2 =	 0x00000000;
	PORT->HDRVE =  0x00000000;
}

/**
  * @brief �����������ŵ��˲���
  * @param IOflt0ConfigPtr: port_ioflt0_config ���͵�ָ�룬������PORT IOFLT0 �����������Ϣ
  * @retval None.
  */ 
void PORT_IOFLT0Config(const port_ioflt0_config *IOflt0ConfigPtr)
{										 
	PORT->IOFLT0 = (uint32_t)(IOflt0ConfigPtr->iofltdiv3 | IOflt0ConfigPtr->iofltdiv2 | \
							  IOflt0ConfigPtr->iofltdiv1 | IOflt0ConfigPtr->iofltnmi | \
							  IOflt0ConfigPtr->iofltkbi1 | IOflt0ConfigPtr->iofltkbi0 | \
							  IOflt0ConfigPtr->iofltrst | IOflt0ConfigPtr->iofltpth | \
							  IOflt0ConfigPtr->iofltptg | IOflt0ConfigPtr->iofltptf | \
							  IOflt0ConfigPtr->iofltpte | IOflt0ConfigPtr->iofltptd | \
							  IOflt0ConfigPtr->iofltptc | IOflt0ConfigPtr->iofltptb | \
							  IOflt0ConfigPtr->iofltpta);
}
	
/**
  * @brief �����������ŵ��˲���
  * @param IOflt1ConfigPtr: port_ioflt1_config ���͵�ָ�룬����PORT IOFLT1 �����������Ϣ
  * @retval None.
  */ 
void PORT_IOFLT1Config(const port_ioflt1_config *IOflt1ConfigPtr)
{
	uint16_t tmpreg;

	/*---------------------------- PORT IOFLT1 Configuration ------------------------*/	
	/* get the present value in IOFLT1 Register. */
	tmpreg = (uint16_t)PORT->IOFLT1 ;
	/* Clear the bits in IOFLT1. */
	tmpreg &= ~(uint16_t)(PORT_IOFLT1_FLTI_MASK | PORT_IOFLT1_FLTIRQ_MASK| PORT_IOFLT1_FLTFTM0_MASK | \
					  	  PORT_IOFLT1_FLTFTM1_MASK | PORT_IOFLT1_FLTPWT_MASK | \
						  PORT_IOFLT1_FLTI2C0_MASK | PORT_IOFLT1_FLTI2C1_MASK);
	/* Configure the bits. */
	tmpreg |= (IOflt1ConfigPtr->ioflti2c1 | IOflt1ConfigPtr->ioflti2c0 | \
			   IOflt1ConfigPtr->iofltpwt  | IOflt1ConfigPtr->iofltftm1 | \
			   IOflt1ConfigPtr->iofltftm0 | IOflt1ConfigPtr->iofltirq | \
			   IOflt1ConfigPtr->iofltpti);
	/* data write to IOFLT1 register. */
	PORT->IOFLT1 = tmpreg ;
}


/**
  * @brief 	PORT�˲�������3ʱ��ѡ��
  * @param clk: ʱ��ѡ�����
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTDIV3SetLPOCLK: LPOʱ�Ӳ���Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv2: LPOʱ��2��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv4: LPOʱ��4��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv8: LPOʱ��8��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv16: LPOʱ��16��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv32: LPOʱ��32��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv64: LPOʱ��64��Ƶ
  *			@arg Port_FLTDIV3SetLPOCLKDiv128: LPOʱ��128��Ƶ
  * @retval None.
  */ 
void PORT_FLTDIV3ConSet(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV3_MASK;
	PORT->IOFLT0 |= clk;
}

/**
  * @brief 	PORT�˲�������2ʱ��ѡ��
  * @param clk: ʱ��ѡ�����
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTDIV2SetBUSCLKDiv32: ����ʱ��32��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv64: ����ʱ��64��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv128: ����ʱ��128��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv256: ����ʱ��256��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv512: ����ʱ��512��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv1024: ����ʱ��1024��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv2048: ����ʱ��2048��Ƶ
  * 		@arg Port_FLTDIV2SetBUSCLKDiv4096: ����ʱ��4096��Ƶ
  * @retval None.
  */ 
void PORT_FLTDIV2Set(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV2_MASK;
	PORT->IOFLT0 |= clk;
}

/**
  * @brief 	PORT�˲�������1ʱ��ѡ��
  * @param clk: ʱ��ѡ�����
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTDIV1SetBUSCLKDiv2: ����ʱ��2��Ƶ
  * 		@arg Port_FLTDIV1SetBUSCLKDiv4: ����ʱ��4��Ƶ
  * 		@arg Port_FLTDIV1SetBUSCLKDiv8: ����ʱ��8��Ƶ
  * 		@arg Port_FLTDIV1SetBUSCLKDiv16: ����ʱ��16��Ƶ
  * @retval None.
  */ 
void PORT_FLTDIV1Set(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV1_MASK;
	PORT->IOFLT0 |= clk;
}	

/**
  * @brief 	NMI�����˲���ѡ��
  * @param NMIFilter: NMI�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTNMINoFilter: ���˲���
  * 		@arg Port_FLTNMIFLTDIV1: �˲�������1
  * 		@arg Port_FLTNMIFLTDIV2: �˲�������2
  * 		@arg Port_FLTNMIFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTNMISET(uint32_t NMIFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTNMI_MASK;
	PORT->IOFLT0 |= NMIFilter;
}

/**
  * @brief 	KBI1�����˲���ѡ��
  * @param KBI1Filter: KBI1�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTKBI1NoFilter: ���˲���
  * 		@arg Port_FLTKBI1FLTDIV1: �˲�������1
  * 		@arg Port_FLTKBI1FLTDIV2: �˲�������2
  * 		@arg Port_FLTKBI1FLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTKBI1SET(uint32_t KBI1Filter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTKBI1_MASK;
	PORT->IOFLT0 |= KBI1Filter;
}

/**
  * @brief 	KBI0�����˲���ѡ��
  * @param KBI0Filter: KBI0�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTKBI0NoFilter: ���˲���
  * 		@arg Port_FLTKBI0FLTDIV1: �˲�������1
  * 		@arg Port_FLTKBI0FLTDIV2: �˲�������2
  * 		@arg Port_FLTKBI0FLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTKBI0SET(uint32_t KBI0Filter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTKBI0_MASK;
	PORT->IOFLT0 |= KBI0Filter;
}

/**
  * @brief 	Reset�����˲���ѡ��
  * @param RSTFilter: RESET�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTRSTNoFilter: ���˲���
  * 		@arg Port_FLTRSTFLTDIV1: �˲�������1
  * 		@arg Port_FLTRSTFLTDIV2: �˲�������2
  * 		@arg Port_FLTRSTFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTRSTSET(uint32_t RSTFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTRST_MASK;
	PORT->IOFLT0 |= RSTFilter;
}

/**
  * @brief 	FLTH�����˲���ѡ��
  * @param FLTHFilter: FLTH�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTHBUSCLK: ����ʱ��
  * 		@arg Port_FLTHFLTDIV1: �˲�������1
  * 		@arg Port_FLTHFLTDIV2: �˲�������2
  * 		@arg Port_FLTHFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTHSET(uint32_t FLTHFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTH_MASK;
	PORT->IOFLT0 |= FLTHFilter;
}

/**
  * @brief 	FLTG�����˲���ѡ��
  * @param FLTGFilter: FLTG�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTGBUSCLK: ����ʱ��
  * 		@arg Port_FLTGFLTDIV1: �˲�������1
  * 		@arg Port_FLTGFLTDIV2: �˲�������2
  * 		@arg Port_FLTGFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTGSET(uint32_t FLTGFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTG_MASK;
	PORT->IOFLT0 |= FLTGFilter;
}

/**
  * @brief 	FLTF�����˲���ѡ��
  * @param FLTFFilter: FLTF�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTFBUSCLK: ����ʱ��
  * 		@arg Port_FLTFFLTDIV1: �˲�������1
  * 		@arg Port_FLTFFLTDIV2: �˲�������2
  * 		@arg Port_FLTFFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTFSET(uint32_t FLTFFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTF_MASK;
	PORT->IOFLT0 |= FLTFFilter;
}

/**
  * @brief 	FLTE�����˲���ѡ��
  * @param FLTEFilter: FLTE�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTEBUSCLK: ����ʱ��
  * 		@arg Port_FLTEFLTDIV1: �˲�������1
  * 		@arg Port_FLTEFLTDIV2: �˲�������2
  * 		@arg Port_FLTEFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTESET(uint32_t FLTEFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTE_MASK;
	PORT->IOFLT0 |= FLTEFilter;
}

/**
  * @brief 	FLTD�����˲���ѡ��
  * @param FLTDFilter: FLTD�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTDBUSCLK: ����ʱ��
  * 		@arg Port_FLTDFLTDIV1: �˲�������1
  * 		@arg Port_FLTDFLTDIV2: �˲�������2
  * 		@arg Port_FLTDFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTDSET(uint32_t FLTDFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTD_MASK;
	PORT->IOFLT0 |= FLTDFilter;
}

/**
  * @brief 	FLTC�����˲���ѡ��
  * @param FLTCFilter: FLTC�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTCBUSCLK: ����ʱ��
  * 		@arg Port_FLTCFLTDIV1: �˲�������1
  * 		@arg Port_FLTCFLTDIV2: �˲�������2
  * 		@arg Port_FLTCFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTCSET(uint32_t FLTCFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTC_MASK;
	PORT->IOFLT0 |= FLTCFilter;
}

/**
  * @brief 	FLTB�����˲���ѡ��
  * @param FLTBFilter: FLTB�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTBBUSCLK: ����ʱ��
  * 		@arg Port_FLTBFLTDIV1: �˲�������1
  * 		@arg Port_FLTBFLTDIV2: �˲�������2
  * 		@arg Port_FLTBFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTBSET(uint32_t FLTBFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTB_MASK;
	PORT->IOFLT0 |= FLTBFilter;
}

/**
  * @brief 	FLTA�����˲���ѡ��
  * @param FLTAFilter: FLTA�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTABUSCLK: ����ʱ��
  * 		@arg Port_FLTAFLTDIV1: �˲�������1
  * 		@arg Port_FLTAFLTDIV2: �˲�������2
  * 		@arg Port_FLTAFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTASET(uint32_t FLTAFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTA_MASK;
	PORT->IOFLT0 |= FLTAFilter;
}

/**
  * @brief 	FLTEWM�����˲���ѡ��
  * @param FLTEWMFilter: FLTEWM�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTEWMNoFilter: ���˲���
  * 		@arg Port_FLTEWMFLTDIV1: �˲�������1
  * 		@arg Port_FLTEWMFLTDIV2: �˲�������2
  * 		@arg Port_FLTIEWMBUSCLK: ����ʱ��
  * @retval None.
  */ 
void PORT_FLTEWMSET(uint32_t FLTEWMFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTEWM_MASK;
	PORT->IOFLT1 |= FLTEWMFilter;
}

/**
  * @brief 	FLTI2C1�����˲���ѡ��
  * @param FLTI2C1Filter: FLTI2C1�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTI2C1NoFilter: ���˲���
  * 		@arg Port_FLTI2C1FLTDIV1: �˲�������1
  * 		@arg Port_FLTI2C1FLTDIV2: �˲�������2
  * 		@arg Port_FLTI2C1BUSCLK: ����ʱ��
  * @retval None.
  */ 
void PORT_FLTI2C1SET(uint32_t FLTI2C1Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI2C1_MASK;
	PORT->IOFLT1 |= FLTI2C1Filter;
}

/**
  * @brief 	FLTI2C0�����˲���ѡ��
  * @param FLTI2C0Filter: FLTI2C0�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTI2C0NoFilter: ���˲���
  * 		@arg Port_FLTI2C0FLTDIV1: �˲�������1
  * 		@arg Port_FLTI2C0FLTDIV2: �˲�������2
  * 		@arg Port_FLTI2C0BUSCLK: ����ʱ��
  * @retval None.
  */ 
void PORT_FLTI2C0SET(uint32_t FLTI2C0Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI2C0_MASK;
	PORT->IOFLT1 |= FLTI2C0Filter;
}

/**
  * @brief 	FLTPWT�����˲���ѡ��
  * @param FLTPWTFilter: FLTPWT�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTPWTNoFilter: ���˲���
  * 		@arg Port_FLTPWTFLTDIV1: �˲�������1
  * 		@arg Port_FLTPWTFLTDIV2: �˲�������2
  * 		@arg Port_FLTPWTFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTPWTSET(uint32_t FLTPWTFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTPWT_MASK;
	PORT->IOFLT1 |= FLTPWTFilter;
}

/**
  * @brief 	FLTFTM1�����˲���ѡ��
  * @param FLTFTM1Filter: FLTFTM1�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTFTM1NoFilter: ���˲���
  * 		@arg Port_FLTFTM1FLTDIV1: �˲�������1
  * 		@arg Port_FLTFTM1FLTDIV2: �˲�������2
  * 		@arg Port_FLTFTM1FLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTFTM1SET(uint32_t FLTFTM1Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTFTM1_MASK;
	PORT->IOFLT1 |= FLTFTM1Filter;
}

/**
  * @brief 	FLTFTM0�����˲���ѡ��
  * @param FLTFTM0Filter: FLTFTM0�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTFTM0NoFilter: ���˲���
  * 		@arg Port_FLTFTM0FLTDIV1: �˲�������1
  * 		@arg Port_FLTFTM0FLTDIV2: �˲�������2
  * 		@arg Port_FLTFTM0FLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTFTM0SET(uint32_t FLTFTM0Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTFTM0_MASK;
	PORT->IOFLT1 |= FLTFTM0Filter;
}

/**
  * @brief 	FLTIRQ�����˲���ѡ��
  * @param FLTIRQFilter: FLTIRQ�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTIRQNoFilter: ���˲���
  * 		@arg Port_FLTIRQFLTDIV1: �˲�������1
  * 		@arg Port_FLTIRQFLTDIV2: �˲�������2
  * 		@arg Port_FLTIRQFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTIRQSET(uint32_t FLTIRQFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTIRQ_MASK;
	PORT->IOFLT1 |= FLTIRQFilter;
}

/**
  * @brief 	FLTI�����˲���ѡ��
  * @param FLTAFilter: FLTI�˲�������ѡ��
  *		�����������ȡ�����ֵ:
  * 		@arg Port_FLTIBUSCLK: ����ʱ��
  * 		@arg Port_FLTIFLTDIV1: �˲�������1
  * 		@arg Port_FLTIFLTDIV2: �˲�������2
  * 		@arg Port_FLTIFLTDIV3: �˲�������3
  * @retval None.
  */ 
void PORT_FLTISET(uint32_t FLTIFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI_MASK;
	PORT->IOFLT1 |= FLTIFilter;
}

/**
  * @brief ���ö˿���������
  * @param PortPin: ��Ҫ���������Ķ˿�����(PORT_PTA0~PORT_PTI6)
  * @param NewState: ��������״̬
  *		�����������ȡ�����ֵ:
  * 		@arg ENABLE: ʹ����������
  *			@arg DISABLE: ʧ����������
  * @retval None.
  */ 
void PORT_PullPinCmd(uint8_t PortPin,FunctionalState NewState)
{
	/* while PortPin less than PORT_PTD7 choose PUE0 Regsiter */
	if(PortPin <= (uint8_t)PORT_PTD7)
	{
		if(NewState != DISABLE )
		{
			/* enable pinA-D pull up */
			PORT->PUE0 |= ((uint32_t)1<<PortPin);
		}
		else 
		{	
			/* disable pinA-D pull up */
			PORT->PUE0 &= ~((uint32_t)1<<PortPin);
		}
	}
	else if(PortPin <= (uint8_t)PORT_PTH7)
	{
		if(NewState != DISABLE )
		{
			/* enable pinE-H pull up */
			PORT->PUE1 |= ((uint32_t)1<<(PortPin - 32u));
		}
		else 
		{	
			/* disable pinE-H pull up */
			PORT->PUE1 &= ~((uint32_t)1<<(PortPin - 32u));
		}
	}
	else
	{
		if(NewState != DISABLE )
		{
			/* enable pinI pull up */
			PORT->PUE2 |= ((uint32_t)1<<(PortPin - 64u));
		}
		else 
		{	
			/* disable pinI pull up */
			PORT->PUE2 &= ~((uint32_t)1<<(PortPin - 64u));
		}
	}
}

/**
  * @brief ���ö˿����ŵĴ��������
  * @param hdrvePin: ��ʾ��Ҫ�������õĶ˿�
  *		�����������ȡ�����ֵ:
  * 		@arg PORT_PullPTB4: PTB4�������������
  *			@arg PORT_PullPTB5: PTB5�������������
  * 		@arg PORT_PullPTD0: PTD0�������������
  *			@arg PORT_PullPTD1: PTD1�������������
  * 		@arg PORT_PullPTE0: PTE0�������������
  *			@arg PORT_PullPTE1: PTE1�������������
  * 		@arg PORT_PullPTH0: PTH0�������������
  *			@arg PORT_PullPTH1: PTH1�������������
  * @param NewState: ���������ʹ��״̬
  *		�����������ȡ�����ֵ:
  * 		@arg ENABLE: ���������ʹ��
  *			@arg DISABLE: ���������ʧ��
  * @retval None.
  */ 
void PORT_HDRVEPinCmd(uint8_t hdrvePin,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* enable pin high drive */
		PORT->HDRVE |= ((uint32_t)1<<hdrvePin) ;
	}
	else 
	{
		/* disable pin high drive */
		PORT->HDRVE &= ~((uint32_t)1<< hdrvePin );
	}
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
