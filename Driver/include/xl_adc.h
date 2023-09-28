/**
  ******************************************************************************
  * @file     xl_adc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the ADC 
  *           firmware library.
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
#ifndef XL_ADC_H__
#define XL_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
	
/* Register define ------------------------------------------------------------*/
/* CR Bit Fields */
#define ADC_CR_MODE_MASK                        0x3u
#define ADC_CR_MODE_SHIFT                       0

#define ADC_CR_FSE_MASK                         0x4u
#define ADC_CR_FSE_SHIFT                        2

#define ADC_CR_FDEP_MASK                        0x38u
#define ADC_CR_FDEP_SHIFT                       3

#define ADC_CR_CCE_MASK                         0x40u
#define ADC_CR_CCE_SHIFT                        6

#define ADC_CR_AIE_MASK                         0x80u
#define ADC_CR_AIE_SHIFT                        7

#define ADC_CR_TRGSEL_MASK                      0x100u
#define ADC_CR_TRGSEL_SHIFT                     8

#define ADC_CR_COSBEN_MASK                      0x200u
#define ADC_CR_COSBEN_SHIFT                     9

#define ADC_CR_LPE_MASK                         0x400u
#define ADC_CR_LPE_SHIFT                        10

#define ADC_CR_LSTE_MASK                        0x800u
#define ADC_CR_LSTE_SHIFT                       11

#define ADC_CR_REFSEL_MASK                      0x3000u
#define ADC_CR_REFSEL_SHIFT                     12

#define ADC_CR_CLKSEL_MASK                      0xC000u
#define ADC_CR_CLKSEL_SHIFT                     14

#define ADC_CR_CFE_MASK                         0x10000u
#define ADC_CR_CFE_SHIFT                        16

#define ADC_CR_CFRE_MASK                        0x20000u
#define ADC_CR_CFRE_SHIFT                       17

#define ADC_CR_CFGRE_MASK                       0x40000u
#define ADC_CR_CFGRE_SHIFT                      18

#define ADC_CR_CFSEL_MASK                       0x80000u
#define ADC_CR_CFSEL_SHIFT                      19

#define ADC_CR_ADACKS_MASK                      0x100000u
#define ADC_CR_ADACKS_SHIFT                     20

#define ADC_CR_ECOBD_MASK                      0x200000u
#define ADC_CR_ECOBD_SHIFT                     21

#define ADC_CR_DMATXEN_MASK                     0x400000u
#define ADC_CR_DMATXEN_SHIFT                    22

#define ADC_CR_DMARXEN_MASK                     0x800000u
#define ADC_CR_DMARXEN_SHIFT                    23

#define ADC_CR_ADIV_MASK                        0x3000000u
#define ADC_CR_ADIV_SHIFT                       24

/* SR Bit Fields */
#define ADC_SR_RFCNT_MASK                       0xFu
#define ADC_SR_RFCNT_SHIFT                      0

#define ADC_SR_RFF_MASK                         0x10u
#define ADC_SR_RFF_SHIFT                        4

#define ADC_SR_REF_MASK                         0x20u
#define ADC_SR_REF_SHIFT                        5

#define ADC_SR_CCF_MASK                         0x80u
#define ADC_SR_CCF_SHIFT                        7

#define ADC_SR_CB_MASK                          0x100u
#define ADC_SR_CB_SHIFT                         8

#define ADC_SR_CFF_MASK                         0x200u
#define ADC_SR_CFF_SHIFT                        9

#define ADC_SR_CEF_MASK                         0x400u
#define ADC_SR_CEF_SHIFT                        10

/* CSR Bit Fields */
#define ADC_CSR_ADCH_MASK                       0x1Fu
#define ADC_CSR_ADCH_SHIFT                      0
/* RDR Bit Fields */
#define ADC_RDR_DATA_MASK                       0xFFFu
#define ADC_RDR_DATA_SHIFT                      0
/* CVR Bit Fields */
#define ADC_CVR_CVL_MASK                        0xFFFu
#define ADC_CVR_CVL_SHIFT                       0

#define ADC_CVR_CVH_MASK                        0xFFF0000u
#define ADC_CVR_CVH_SHIFT                       16
/* EHTMR Bit Fields */
#define ADC_EHTMR_EN_MASK                       0x1u
#define ADC_EHTMR_EN_SHIFT                      0

#define ADC_EHTMR_HTRGM_MASK                    0x2u
#define ADC_EHTMR_HTRGM_SHIFT                   1
/* APCTL Bit Fields */
#define ADC_PINSEL_ADPC_MASK                    0xFFFFFFu
#define ADC_PINSEL_ADPC_SHIFT                   0


/** ADC - Register Layout Typedef
 * (1-269)20.3 ADC �洢��ӳ��ͼĴ�������*/
typedef struct {
  __IO uint32_t CR;                               /*!< (1-270)20.3.1 ADC ���ƼĴ��� (CR), offset: 0x0 */
  __I  uint32_t SR;                               /*!< (1-273)20.3.2 ADC ״̬�Ĵ��� (SR), offset: 0x4 */
  __IO uint32_t CSR;                              /*!< (1-275)20.3.3 ����ͨ��ѡ��Ĵ��� (CSR), offset: 0x8 */
  __I  uint32_t RDR;                              /*!< (1-176)20.3.4 ת���������Ĵ��� (RDR), offset: 0xC */
  __IO uint32_t CVR;                              /*!< (1-277)20.3.5 ת������Ƚϱ�׼ֵ�Ĵ���(CVR), offset: 0x10 */
  __IO uint32_t EHTMR;                            /*!< ADCʹ���봥�����ƼĴ���, offset: 0x14 */   
  __IO uint32_t APCTL;                            /*!< ADCʹ���봥�����ƼĴ���, offset: 0x18 */
  __IO uint32_t CFR;                              /*!< ADC�ȽϹ���״̬�Ĵ���, offset: 0x1C */
} ADC_Type, *ADC_MemMapPtr;
extern ADC_Type* ADC0;



/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC 
  * @{
  */


/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief ADC ��ʼ���ṹ�嶨��
 */
typedef struct
{
  uint32_t ADC_Mode;                       /*!< ����ADCת�����ݿ�� */
                                                
  uint32_t ADC_ReferVoltage;               /*!< ת���ο���ѹԴ */
	
  uint32_t ADC_ClockSource;                /*!< ADCת��ʱ��Դ */
	
  uint32_t ADC_ClkDivide;                  /*!< ADCת��ʱ�ӷ�Ƶϵ�� */

  FunctionalState ADC_LowPowerConvert;     /*!< ADC�͹���ת��ʹ��,���ó�ENABLE����DISABLE */
                                               

  FunctionalState ADC_LongTimeConvert;     /*!< ADC������ʱ��ʹ��, ���ó�ENABLE����DISABLE */
                                              

}ADC_InitTypeDef;


/**
  * @brief ADC_FIFO��ʼ���ṹ�嶨��
  * NOTE: 20.4.7 FIFO ����
  */
typedef struct
{
  uint32_t ADC_FIFOLevel;                   /*!< FIFO ��� */                                              
	
  FunctionalState ADC_ChannelScan;          /*!< ADC�ŵ�ɨ�蹦��ʹ��, ���ó�ENABLE����DISABLE */
                                              
}ADC_FIFOTypeDef;


/**
  * @brief ADC�Ƚ�����ʼ���ṹ�嶨��
  */
typedef struct
{
	uint32_t ADC_CompareMode;                 /*!< ADC�ȽϷ�ʽ ����С��Χ�Ƚ� */
											   
	uint32_t ADC_CompareOut;                  /*!< ADC�Ƚ����ģʽ */

	uint32_t ADC_FIFOCompareOut;              /*!< ADC FIFO �Ƚ����ģʽ */

	uint32_t ADC_CompareValueHigh;            /*!< �Ƚ�ֵΪ�� */

	uint32_t ADC_CompareValueLow;             /*!< �Ƚ�ֵΪ�� */

	FunctionalState ADC_AutoCompare;          /*!< �Զ��ȽϹ���ʹ��,���ó�ENABLE����DISABLE */
	
	FunctionalState ADC_CompareResultSwitch;  /*!< �ȽϽ��ת��,���ó�ENABLE����DISABLE */

}ADC_CompareTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_Exported_Constants ADCģ��ʹ�ò�������
  * @{
  */

/**
	* @defgroup ADC_Mode_list ADCģʽ����
	* @{
	*/
#define ADC_MODE_8BIT									  		0x0		/*!< 8λ���ģʽ */
#define ADC_MODE_10BIT											0x1		/*!< 10λ���ģʽ */
#define ADC_MODE_12BIT											0x2		/*!< 12λ���ģʽ */
/**
	* @}
	*/

/**
	* @defgroup ADC_FIFO_list ADCFIFO��ȶ���
	* @{
	*/	
#define ADC_FIFO_DISABLE                		0     /*!< FIFO���ܹر� */
#define ADC_FIFO_LEVEL2                 		1     /*!< FIFO���Ϊ2 */
#define ADC_FIFO_LEVEL3                 		2     /*!< FIFO���Ϊ3 */
#define ADC_FIFO_LEVEL4                 		3     /*!< FIFO���Ϊ4 */
#define ADC_FIFO_LEVEL5                 		4     /*!< FIFO���Ϊ5 */
#define ADC_FIFO_LEVEL6                 		5     /*!< FIFO���Ϊ6 */
#define ADC_FIFO_LEVEL7                 		6     /*!< FIFO���Ϊ7 */
#define ADC_FIFO_LEVEL8                 		7	    /*!< FIFO���Ϊ8 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_CONTINUOUS_list ADCת��ģʽ����
	* @{
	*/
#define ADC_CONVENTION_ONCE              		0x00u   /*!< ����ת�� */
#define ADC_CONVENTION_CONTINUOUS        		0x01u   /*!< ����ת�� */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Trigger_List ADC����ģʽѡ��
	* @{
	*/
#define ADC_SOFTWARE_TRIGGER             		0x00u   /*!< ������� */
#define ADC_HARDWARE_TRIGGER             		0x01u   /*!< Ӳ������ */
/**
	* @}
	*/

/**
	* @defgroup ADC_VRFF_List ADC�ο���ѹ����
	* @{
	*/
#define ADC_VREF_VREFH                   		0x00		/*!< �ο���ѹ��VREFH */
#define ADC_VREF_VDDA                    		0x01		/*!< �ο���ѹ��VDDA */
/**
	* @}
	*/
	

	
/**
	* @defgroup ADC_ClockSource_list ADCʱ��Դ����
	* @{
	*/
#define ADC_CLOCK_BUS_CLOCK							 		0x00	              /*!< ADCʱ��Դ������ʱ�� */
#define ADC_CLOCK_BUS_CLOCK_DIVIDE_2	   		            0x01	  /*!< ADCʱ��Դ������ʱ��2��Ƶ */
#define ADC_CLOCK_ALTCLK							   		0x02	              /*!< ADCʱ��Դ�Ǳ���ʱ��(ALTCLK) */
#define ADC_CLOCK_ADACK								   		0x03	              /*!< ADCʱ��Դ���첽ʱ��(ADACK) */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_CPMPARE_List ADC�Ƚ�ģʽ����
	* @{
	*/	
#define ADC_COMPAREMODE_SIZE              	0x00   /*!< ADC��С�Ƚ� */
#define ADC_COMPAREMODE_RANGE             	0x01   /*!< ADC��Χ�Ƚ� */
/**
	* @}
	*/

/**
	* @defgroup ADC_CPMPARE_out_list ADC�Ƚ����ģʽ����
	* @{
	*/	
#define ADC_COMPAREOUT_LESS              		0x00   /*!< С�ڵ��ڻ����ڷ�Χ�����ת����� */
#define ADC_COMPAREOUT_MORE              		0x01   /*!<  ���ڻ����ڷ�Χ�����ת����� */
/**
	* @}
	*/

/** 
	* @defgroup ADC_OutputSelect_List ADC�Ƚ��������ģʽ����
	* @{
	*/	
#define ADC_COMPAREFIFO_ALL              		0x00   /*!< ������ͨ��������ȽϽ��ʱ���������ɨ���� */
#define ADC_COMPAREFIFO_ONE              		0x01   /*!< ֻҪĳһ��ͨ������ȽϽ��ʱ���������ɨ���� */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_AsynchronousClk_Select_List ADC�첽ʱ��ѡ����
	* @{
	*/	
#define ADC_ADACK_NORMAL                   0x00u   /*!< ADC�첽ʱ��ʹ�ñ�׼Ƶ�� */
#define ADC_ADACK_TIMES1P5                 0x01u   /*!< ADC�첽ʱ��ʹ��1.5����׼Ƶ�� */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Deivied_List ADCʱ�ӷ�Ƶѡ��
	* @{
	*/		
#define ADC_ADIV_DIVIDE_1							   		0x00		/*!< ʱ��1��Ƶ */
#define ADC_ADIV_DIVIDE_2								 		0x01		/*!< ʱ��2��Ƶ */
#define ADC_ADIV_DIVIDE_4								 		0x02		/*!< ʱ��4��Ƶ */
#define ADC_ADIV_DIVIDE_8								 		0x03		/*!< ʱ��8��Ƶ */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Flags_Definition ADC�ȽϹ���״̬��־����
	* @{
	*/
#define ADC_FLAG_DATAFIFO_FULL           		0x10     /*!< FIFO��������־ */
#define ADC_FLAG_DATAFIFO_EMPTY          		0x20     /*!< FIFO���ݿձ�־ */
#define ADC_FLAG_CONV_FINISH             		0x80     /*!< ADCת��������־ */
#define ADC_FLAG_CONV_BUSY               		0x100    /*!< ADCת����æ��־ */
#define ADC_FLAG_ChannelFIFO_FULL        		0x200    /*!< Channel FIFO��������־ */
#define ADC_FLAG_ChannelFIFO_EMPTY       		0x400    /*!< Channel FIFO���ݿձ�־ */
/**
	* @}
	*/

/**
	* @defgroup ADC_COMPARE_FLAGs_Definition ADC��־����
	* @{
	*/
#define ADC_CHANNEL0_COMPARE_EXCEPTION			0x000001			/*!< ͨ��0�ȽϽ���쳣��־ */
#define ADC_CHANNEL1_COMPARE_EXCEPTION			0x000002			/*!< ͨ��1�ȽϽ���쳣��־ */
#define ADC_CHANNEL2_COMPARE_EXCEPTION			0x000004			/*!< ͨ��2�ȽϽ���쳣��־ */
#define ADC_CHANNEL3_COMPARE_EXCEPTION			0x000008			/*!< ͨ��3�ȽϽ���쳣��־ */
#define ADC_CHANNEL4_COMPARE_EXCEPTION			0x000010			/*!< ͨ��4�ȽϽ���쳣��־ */
#define ADC_CHANNEL5_COMPARE_EXCEPTION			0x000020			/*!< ͨ��5�ȽϽ���쳣��־ */
#define ADC_CHANNEL6_COMPARE_EXCEPTION			0x000040			/*!< ͨ��6�ȽϽ���쳣��־ */
#define ADC_CHANNEL7_COMPARE_EXCEPTION			0x000080			/*!< ͨ��7�ȽϽ���쳣��־ */
#define ADC_CHANNELALL_COMPARE_EXCEPTION		0x000100			/*!< ����ͨ���ȽϽ���쳣��־ */
#define ADC_COMPARE_CFSEL_FLAG					0x010000			    /*!< ������ѡ��ʽ��־ */
#define ADC_COMPARE_CFGRE_FLAG					0x020000			    /*!< ����ѡ���־ */
#define ADC_COMPARE_CFRE_FLAG					0x040000			      /*!< �ȽϷ�ʽѡ���־ */
#define ADC_COMPARE_CFE_FLAG					0x080000			      /*!< �Զ��ȽϹ���ʹ�ܱ�־ */
/**
	* @}
	*/


/**
	* @defgroup ADC_Channel_list ADCͨ��ѡ����
	* @{
	*/
#define ADC_CHANNEL_AD0                  		0x0     /*!< ADC����ͨ��0 */
#define ADC_CHANNEL_AD1                  		0x1     /*!< ADC����ͨ��1 */
#define ADC_CHANNEL_AD2                  		0x2     /*!< ADC����ͨ��2 */
#define ADC_CHANNEL_AD3                  		0x3     /*!< ADC����ͨ��3 */
#define ADC_CHANNEL_AD4                  		0x4     /*!< ADC����ͨ��4 */
#define ADC_CHANNEL_AD5                  		0x5     /*!< ADC����ͨ��5 */
#define ADC_CHANNEL_AD6                  		0x6     /*!< ADC����ͨ��6 */
#define ADC_CHANNEL_AD7                  		0x7     /*!< ADC����ͨ��7 */
#define ADC_CHANNEL_AD8                  		0x8     /*!< ADC����ͨ��8 */
#define ADC_CHANNEL_AD9                  		0x9     /*!< ADC����ͨ��9 */
#define ADC_CHANNEL_AD10                 		0xa     /*!< ADC����ͨ��10 */
#define ADC_CHANNEL_AD11                 		0xb     /*!< ADC����ͨ��11 */
#define ADC_CHANNEL_AD12                 		0xc     /*!< ADC����ͨ��12 */
#define ADC_CHANNEL_AD13                 		0xd     /*!< ADC����ͨ��13 */
#define ADC_CHANNEL_AD14                 		0xe     /*!< ADC����ͨ��14 */
#define ADC_CHANNEL_AD15                 		0xf     /*!< ADC����ͨ��15 */
#define ADC_CHANNEL_AD16                 		0x10    /*!< ADC����ͨ��16 */
#define ADC_CHANNEL_AD17                 		0x11    /*!< ADC����ͨ��17 */
#define ADC_CHANNEL_AD18                 		0x12    /*!< ADC����ͨ��18 */
#define ADC_CHANNEL_AD19                 		0x13    /*!< ADC����ͨ��19 */
#define ADC_CHANNEL_AD20                 		0x14    /*!< ADC����ͨ��20 */ 
#define ADC_CHANNEL_AD21                 		0x15    /*!< ADC����ͨ��21 */ 
#define ADC_CHANNEL_TEMPSENSOR           		0x16    /*!< ADC����ͨ���ڲ��¶ȴ����� */
#define ADC_CHANNEL_BANDGAP              		0x17    /*!< ADC������׼��ѹ */ 
#define ADC_CHANNEL_AD22                 		0x18    /*!< ADC����ͨ��22 */ 
#define ADC_CHANNEL_AD23                 		0x19    /*!< ADC����ͨ��23 */ 
#define ADC_CHANNEL_VSS                  		0x1A    /*!< ADC����ͨ��VSS */ 
#define ADC_CHANNEL_VREFH                		0x1D    /*!< ADC����ͨ��Vrefh */ 
#define ADC_CHANNEL_VREFL                		0x1E    /*!< ADC����ͨ��Vrefl */ 
#define ADC_CHANNEL_DISABLE              		0x1F    /*!< ADCʧ�� */
/**
	* @}
	*/

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void ADC_DeInit(ADC_Type* ADCx);
void ADC_Init(ADC_Type* ADCx, const ADC_InitTypeDef* ADC_InitStruct);
void ADC_FIFOConfig(ADC_Type* ADCx, const ADC_FIFOTypeDef* ADC_FIFOStruct);
void ADC_CompareConfig(ADC_Type* ADCx, const ADC_CompareTypeDef* ADC_CompareStruct);
void ADC_EnableCmd(ADC_Type* ADCx, FunctionalState NewState);
void ADC_HardwareTriggrMaskCmd(ADC_Type* ADCx, FunctionalState NewState);
void ADC_SetTriggerMode(ADC_Type* ADCx, uint8_t ADC_Triggermode);
void ADC_ADACKSelect(ADC_Type* ADCx, uint8_t ADC_ADACKmode);
void ADC_SetConventionMode(ADC_Type* ADCx, uint8_t ADC_ConventionMode);
void ADC_SetChannel(ADC_Type* ADCx, uint8_t channelno);
void ADC_InterruptEn(ADC_Type* ADCx, FunctionalState NewState);
void ADC_DMATxEn(ADC_Type* ADCx, FunctionalState NewState);
void ADC_DMARxEn(ADC_Type* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(const ADC_Type* ADCx);
uint16_t ADC_GetFIFOValueCounter(const ADC_Type* ADCx);
FlagStatus ADC_GetFlagStatus(const ADC_Type* ADCx, uint16_t ADC_FLAG);
FlagStatus ADC_GetCompareFlagStatus(const ADC_Type* ADCx, uint16_t ADC_COMPARE_FLAG);
void ADC_DisableChannelDigFuc(ADC_Type* ADCx, uint8_t channelno, FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif    /*__XL_ADC_H__ */
/**
  * @}
  */

/**
  * @}
  */

