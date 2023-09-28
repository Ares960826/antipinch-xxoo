/**
  ******************************************************************************
  * @file     xl_sim.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the SIM 
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
/* Define to prevent recursive inclusion -------------------------------------*/	
#ifndef __XL_SIM_H_
#define __XL_SIM_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ---------------------------------------------------------------*/
#include "xl6600.h"

/* Register define ------------------------------------------------------------*/
	
/* SRSID Bit Fields */
#define SIM_SRSID_ECCERR_MASK                    0x00000001u
#define SIM_SRSID_ECCERR_SHIFT                  0
#define SIM_SRSID_LVD_MASK                       0x00000002u
#define SIM_SRSID_LVD_SHIFT                      1
#define SIM_SRSID_WDOG_MASK                      0x00000020u
#define SIM_SRSID_WDOG_SHIFT                     5
#define SIM_SRSID_PIN_MASK                       0x00000040u
#define SIM_SRSID_PIN_SHIFT                      6
#define SIM_SRSID_POR_MASK                       0x00000080u
#define SIM_SRSID_POR_SHIFT                      7
#define SIM_SRSID_SW_MASK                        0x00000400u
#define SIM_SRSID_SW_SHIFT                       10
#define SIM_SRSID_PINID_MASK                     0x000F0000u
#define SIM_SRSID_PINID_SHIFT                    16	

/* SOPT0 Bit Fields */
#define SIM_SOPT0_NMIE_MASK                      0x00000002u
#define SIM_SOPT0_NMIE_SHIFT                     1
#define SIM_SOPT0_RSTPE_MASK                     0x00000004u
#define SIM_SOPT0_RSTPE_SHIFT                    2
#define SIM_SOPT0_SWDE_MASK                      0x00000008u
#define SIM_SOPT0_SWDE_SHIFT                     3
#define SIM_SOPT0_ACTRG_MASK                     0x00000020u
#define SIM_SOPT0_ACTRG_SHIFT                    5
#define SIM_SOPT0_RXDFE_MASK                     0x00000300u
#define SIM_SOPT0_RXDFE_SHIFT                    8
#define SIM_SOPT0_RTCC_MASK                      0x00000400u
#define SIM_SOPT0_RTCC_SHIFT                     10
#define SIM_SOPT0_ACIC_MASK                      0x00000800u
#define SIM_SOPT0_ACIC_SHIFT                     11
#define SIM_SOPT0_RXDCE_MASK                     0x00001000u
#define SIM_SOPT0_RXDCE_SHIFT                    12
#define SIM_SOPT0_FTMSYNC_MASK                   0x00004000u
#define SIM_SOPT0_FTMSYNC_SHIFT                  14
#define SIM_SOPT0_TXDME_MASK                     0x00008000u
#define SIM_SOPT0_TXDME_SHIFT                    15
#define SIM_SOPT0_BUSREF_MASK                    0x00070000u
#define SIM_SOPT0_BUSREF_SHIFT                   16
#define SIM_SOPT0_CLKOE_MASK                     0x00080000u
#define SIM_SOPT0_CLKOE_SHIFT                    19
#define SIM_SOPT0_DLYACT_MASK                    0x00800000u
#define SIM_SOPT0_DLYACT_SHIFT                   23
#define SIM_SOPT0_DELAY_MASK                     0xFF000000u
#define SIM_SOPT0_DELAY_SHIFT                    24

/* SOPT1 Bit Fields */
#define SIM_SOPT1_ACPWTS_MASK                    0x8u
#define SIM_SOPT1_ACPWTS_SHIFT                   3
#define SIM_SOPT1_UARTPWTS_MASK                  0x60u
#define SIM_SOPT1_UARTPWTS_SHIFT                 5
#define SIM_SOPT1_ADHWT_MASK					 0xF00u
#define SIM_SOPT1_ADHWT_SHIFT					 8

/* PINSEL0 Bit Fields */
#define SIM_PINSEL0_UART0PS_MASK                 0x0000000Cu
#define SIM_PINSEL0_UART0PS_SHIFT                2
#define SIM_PINSEL0_FTM0PS0_MASK                 0x00000030u
#define SIM_PINSEL0_FTM0PS0_SHIFT                4
#define SIM_PINSEL0_FTM0PS1_MASK                 0x000000C0u
#define SIM_PINSEL0_FTM0PS1_SHIFT                6
#define SIM_PINSEL0_FTM1PS0_MASK                 0x00000300u
#define SIM_PINSEL0_FTM1PS0_SHIFT                8
#define SIM_PINSEL0_FTM1PS1_MASK                 0x00000C00u
#define SIM_PINSEL0_FTM1PS1_SHIFT                10
#define SIM_PINSEL0_FTMFLT2PS_MASK               0x00003000u
#define SIM_PINSEL0_FTMFLT2PS_SHIFT              12
#define SIM_PINSEL0_FTMFLT1PS_MASK               0x0000C000u
#define SIM_PINSEL0_FTMFLT1PS_SHIFT              14
#define SIM_PINSEL0_BUSOUTPS_MASK                0x00030000u
#define SIM_PINSEL0_BUSOUTPS_SHIFT               16
#define SIM_PINSEL0_TCLK2PS_MASK                 0x000C0000u
#define SIM_PINSEL0_TCLK2PS_SHIFT                18
#define SIM_PINSEL0_TCLK1PS_MASK                 0x00300000u
#define SIM_PINSEL0_TCLK1PS_SHIFT                20
#define SIM_PINSEL0_TCLK0PS_MASK                 0x00C00000u
#define SIM_PINSEL0_TCLK0PS_SHIFT                22
#define SIM_PINSEL0_FTM0CLKPS_MASK               0x03000000u
#define SIM_PINSEL0_FTM0CLKPS_SHIFT              24
#define SIM_PINSEL0_FTM1CLKPS_MASK               0x0C000000u
#define SIM_PINSEL0_FTM1CLKPS_SHIFT              26
#define SIM_PINSEL0_FTM2CLKPS_MASK               0x30000000u
#define SIM_PINSEL0_FTM2CLKPS_SHIFT              28
#define SIM_PINSEL0_PWTCLKPS_MASK                0xC0000000u
#define SIM_PINSEL0_PWTCLKPS_SHIFT               30

/* PINSEL1 Bit Fields */
#define SIM_PINSEL1_FTM2PS0_MASK                 0x00000003u
#define SIM_PINSEL1_FTM2PS0_SHIFT                0
#define SIM_PINSEL1_FTM2PS1_MASK                 0x0000000Cu
#define SIM_PINSEL1_FTM2PS1_SHIFT                2
#define SIM_PINSEL1_FTM2PS2_MASK                 0x00000030u
#define SIM_PINSEL1_FTM2PS2_SHIFT                4
#define SIM_PINSEL1_FTM2PS3_MASK                 0x000000C0u
#define SIM_PINSEL1_FTM2PS3_SHIFT                6
#define SIM_PINSEL1_FTM2PS4_MASK                 0x00000100u
#define SIM_PINSEL1_FTM2PS4_SHIFT                8
#define SIM_PINSEL1_FTM2PS5_MASK                 0x00000200u
#define SIM_PINSEL1_FTM2PS5_SHIFT                9
#define SIM_PINSEL1_I2C1PS_MASK                  0x00000400u
#define SIM_PINSEL1_I2C1PS_SHIFT                 10
#define SIM_PINSEL1_SPI1PS_MASK                  0x00000800u
#define SIM_PINSEL1_SPI1PS_SHIFT                 11
#define SIM_PINSEL1_UART1PS_MASK                 0x00001000u
#define SIM_PINSEL1_UART1PS_SHIFT                12
#define SIM_PINSEL1_UART2PS_MASK                 0x00002000u
#define SIM_PINSEL1_UART2PS_SHIFT                13
#define SIM_PINSEL1_PWTIN0PS_MASK                0x00004000u
#define SIM_PINSEL1_PWTIN0PS_SHIFT               14
#define SIM_PINSEL1_PWTIN1PS_MASK                0x00008000u
#define SIM_PINSEL1_PWTIN1PS_SHIFT               15
#define SIM_PINSEL1_SPI0PS_MASK                  0x00010000u
#define SIM_PINSEL1_SPI0PS_SHIFT                 16
#define SIM_PINSEL1_EWMPS_MASK                   0x00060000u
#define SIM_PINSEL1_EWMPS_SHIFT                  17
#define SIM_PINSEL1_IRQPS_MASK                   0x00380000u
#define SIM_PINSEL1_IRQPS_SHIFT                  19
#define SIM_PINSEL1_ACMP1PS_MASK                 0x00400000u
#define SIM_PINSEL1_ACMP1PS_SHIFT                22
#define SIM_PINSEL1_RTCPS_MASK                   0x00800000u
#define SIM_PINSEL1_RTCPS_SHIFT                  23
#define SIM_PINSEL1_I2C0PS_MASK                  0x01000000u
#define SIM_PINSEL1_I2C0PS_SHIFT                 24
#define SIM_PINSEL1_FTM0PS2_MASK                  0x02000000u
#define SIM_PINSEL1_FTM0PS2_SHIFT                 25
#define SIM_PINSEL1_FTM0PS3_MASK                  0x04000000u
#define SIM_PINSEL1_FTM0PS3_SHIFT                 26
#define SIM_PINSEL1_FTM1PS2_MASK                  0x08000000u
#define SIM_PINSEL1_FTM1PS2_SHIFT                 27
#define SIM_PINSEL1_FTM1PS3_MASK                  0x10000000u
#define SIM_PINSEL1_FTM1PS3_SHIFT                 28
#define SIM_PINSEL1_FTM2PS6_MASK                  0x20000000u
#define SIM_PINSEL1_FTM2PS6_SHIFT                 29
#define SIM_PINSEL1_FTM2PS7_MASK                  0x40000000u
#define SIM_PINSEL1_FTM2PS7_SHIFT                 30

/* SCGC Bit Fields */
#define SIM_SCGC_RTC_MASK                        0x00000001u
#define SIM_SCGC_RTC_SHIFT                       0
#define SIM_SCGC_PIT_MASK                        0x00000002u
#define SIM_SCGC_PIT_SHIFT                       1
#define SIM_SCGC_EWM_MASK                        0x00000004u
#define SIM_SCGC_EWM_SHIFT                       2
#define SIM_SCGC_PWT_MASK                        0x00000010u
#define SIM_SCGC_PWT_SHIFT                       4
#define SIM_SCGC_FTM0_MASK                       0x00000020u
#define SIM_SCGC_FTM0_SHIFT                      5
#define SIM_SCGC_FTM1_MASK                       0x00000040u
#define SIM_SCGC_FTM1_SHIFT                      6
#define SIM_SCGC_FTM2_MASK                       0x00000080u
#define SIM_SCGC_FTM2_SHIFT                      7
#define SIM_SCGC_CLMA_MASK                       0x00000100u
#define SIM_SCGC_CLMA_SHIFT                      8
#define SIM_SCGC_CLMB_MASK                       0x00000200u
#define SIM_SCGC_CLMB_SHIFT                      9
#define SIM_SCGC_CRC_MASK                        0x00000400u
#define SIM_SCGC_CRC_SHIFT                       10
#define SIM_SCGC_WDG_MASK						 0x00000800u	
#define SIM_SCGC_WDG_SHIFT						 11
#define SIM_SCGC_MCAN_MASK                       0x00004000u
#define SIM_SCGC_MCAN_SHIFT                      14
#define SIM_SCGC_I2C0_MASK                       0x00010000u
#define SIM_SCGC_I2C0_SHIFT                      16
#define SIM_SCGC_I2C1_MASK                       0x00020000u
#define SIM_SCGC_I2C1_SHIFT                      17
#define SIM_SCGC_SPI0_MASK                       0x00040000u
#define SIM_SCGC_SPI0_SHIFT                      18
#define SIM_SCGC_SPI1_MASK                       0x00080000u
#define SIM_SCGC_SPI1_SHIFT                      19
#define SIM_SCGC_UART0_MASK                      0x00100000u
#define SIM_SCGC_UART0_SHIFT                     20
#define SIM_SCGC_UART1_MASK                      0x00200000u
#define SIM_SCGC_UART1_SHIFT                     21
#define SIM_SCGC_UART2_MASK                      0x00400000u
#define SIM_SCGC_UART2_SHIFT                     22
#define SIM_SCGC_KBI0_MASK                       0x01000000u
#define SIM_SCGC_KBI0_SHIFT                      24
#define SIM_SCGC_KBI1_MASK                       0x02000000u
#define SIM_SCGC_KBI1_SHIFT                      25
#define SIM_SCGC_IRQ_MASK                        0x08000000u
#define SIM_SCGC_IRQ_SHIFT                       27
#define SIM_SCGC_DMA_MASK                        0x10000000u
#define SIM_SCGC_DMA_SHIFT                       28
#define SIM_SCGC_ADC_MASK                        0x20000000u
#define SIM_SCGC_ADC_SHIFT                       29
#define SIM_SCGC_ACMP0_MASK                      0x40000000u
#define SIM_SCGC_ACMP0_SHIFT                     30
#define SIM_SCGC_ACMP1_MASK                      0x80000000u
#define SIM_SCGC_ACMP1_SHIFT                     31

/* UUIDL Bit Fields */
#define SIM_UUIDL_ID_MASK                        0xFFFFFFFFu
#define SIM_UUIDL_ID_SHIFT                       0

/* UUIDML Bit Fields */
#define SIM_UUIDML_ID_MASK                       0xFFFFFFFFu
#define SIM_UUIDML_ID_SHIFT                      0

/* UUIDMH Bit Fields */
#define SIM_UUIDMH_SS_MASK                       0x0000000Fu
#define SIM_UUIDMH_SS_SHIFT                      0
#define SIM_UUIDMH_FS_MASK                       0x000000F0u
#define SIM_UUIDMH_FS_SHIFT                      4
#define SIM_UUIDMH_VER_MASK                      0x0000FF00u
#define SIM_UUIDMH_VER_SHIFT                     8
#define SIM_UUIDMH_DEVID_MASK                    0xFFFF0000u
#define SIM_UUIDMH_DEVID_SHIFT                   16

/* CLKDIV Bit Fields */
#define SIM_CLKDIV_OUTDIV1_MASK					 0x000000FFu
#define SIM_CLKDIV_OUTDIV1_SHIFT				 0
#define SIM_CLKDIV_OUTDIV2_MASK					 0x0000FF00u/*
*(1-173)12.2.10 时钟分频器寄存器(CLKDIV)->OUTDIV2 - 时钟 2 输出分频器值*/
#define SIM_CLKDIV_OUTDIV2_SHIFT				 8
#define SIM_CLKDIV_OUTDIV3_MASK					 0x00FF0000u
#define SIM_CLKDIV_OUTDIV3_SHIFT				 16
#define SIM_CLKDIV_OUTDIV4_MASK					 0xFF000000u
#define SIM_CLKDIV_OUTDIV4_SHIFT				 24

/* SCGC1 Bit Fields */
#define SIM_SCGC1_FTM0F_MASK                     0x00000001u
#define SIM_SCGC1_FTM0F_SHIFT                    0
#define SIM_SCGC1_FTM1F_MASK                     0x00000002u
#define SIM_SCGC1_FTM1F_SHIFT                    1
#define SIM_SCGC1_FTM2F_MASK                     0x00000004u
#define SIM_SCGC1_FTM2F_SHIFT                    2
#define SIM_SCGC1_RTCOEC_MASK                    0x00000020u
#define SIM_SCGC1_RTCOEC_SHIFT                   5
#define SIM_SCGC1_ADCALTC_MASK                   0x00000040u
#define SIM_SCGC1_ADCALTC_SHIFT                  6
#define SIM_SCGC1_FTM0T_MASK                     0x01000000u
#define SIM_SCGC1_FTM0T_SHIFT                    24
#define SIM_SCGC1_FTM1T_MASK                     0x02000000u
#define SIM_SCGC1_FTM1T_SHIFT                    25
#define SIM_SCGC1_FTM2T_MASK                     0x04000000u
#define SIM_SCGC1_FTM2T_SHIFT                    26
#define SIM_SCGC1_WDOGLPO_MASK                   0x8000000u
#define SIM_SCGC1_WDOGLPO_SHIFT                  27
#define SIM_SCGC1_RTCLPOC_MASK                   0x10000000u
#define SIM_SCGC1_RTCLPOC_SHIFT                  28
#define SIM_SCGC1_FTM0FF_MASK                    0x20000000u
#define SIM_SCGC1_FTM0FF_SHIFT                   29
#define SIM_SCGC1_FTM1FF_MASK                    0x40000000u
#define SIM_SCGC1_FTM1FF_SHIFT                   30
#define SIM_SCGC1_FTM2FF_MASK                    0x80000000u
#define SIM_SCGC1_FTM2FF_SHIFT                   31

/* LP Bit Fields */
#define SIM_LP_FLASHPOFF_MASK                 	 0x00000004u
#define SIM_LP_FLASHPOFF_SHIFT                 	 2
#define SIM_LP_FLASHPOFFST_MASK                  0x00000008u
#define SIM_LP_FLASHPOFFST_SHIFT                 3
#define SIM_LP_SRAM1POFF_MASK                 	 0x00000020u
#define SIM_LP_SRAM1POFF_SHIFT                 	 5
#define SIM_LP_SRAM2POFF_MASK                 	 0x00000040u
#define SIM_LP_SRAM2POFF_SHIFT                 	 6
#define SIM_LP_SRAM3POFF_MASK                 	 0x00000080u
#define SIM_LP_SRAM3POFF_SHIFT                 	 7
#define SIM_LP_SRAM1POFFST_MASK                  0x00000200u
#define SIM_LP_SRAM1POFFST_SHIFT                 9
#define SIM_LP_SRAM2POFFST_MASK                  0x00000400u
#define SIM_LP_SRAM2POFFST_SHIFT                 10
#define SIM_LP_SRAM3POFFST_MASK                  0x00000800u
#define SIM_LP_SRAM3POFFST_SHIFT                 11
#define SIM_LP_FLASHPON_MASK                  	 0x00001000u
#define SIM_LP_FLASHPON_SHIFT                 	 12
#define SIM_LP_SRAMPON_MASK                  	 0x00002000u
#define SIM_LP_SRAMPON_SHIFT                 	 13
#define SIM_LP_WEN_MASK                 		 0xFFFF0000u
#define SIM_LP_WEN_SHIFT                 		 16

/* WAIT Bit Fields */
#define SIM_WAIT_CLKWAIT_MASK                  	 0x0000FFFFu
#define SIM_WAIT_CLKWAIT_SHIFT                 	 0
#define SIM_WAIT_DIV1US_MASK                  	 0x00FF0000u
#define SIM_WAIT_DIV1US_SHIFT                 	 16

/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SRSID;                             /**< (1-151)12.2.1 系统复位状态和 ID 寄存器(SRSID), offset: 0x0 */
  __IO uint32_t SOPT0;                             /**< 系统选项寄存器0, offset: 0x4 */
  __IO uint32_t SOPT1;                             /**< 系统选项寄存器, offset: 0x8 */
  __IO uint32_t PINSEL0;                           /**< (1-159)12.2.4 引脚选择寄存器 0 (PINSEL0), offset: 0xC */
  __IO uint32_t PINSEL1;                           /**< (1-162)12.2.5 引脚选择寄存器 1 (PINSEL1), offset: 0x10 */
  __IO uint32_t SCGC;                              /**< (1-166)12.2.6 系统时钟选通控制寄存器(SCGC), offset: 0x14 */
  __I  uint32_t UUIDL;                             /**< 通用唯一标识符低位寄存器, offset: 0x18 */
  __I  uint32_t UUIDML;                            /**< 通用唯一标识符中低位寄存器, offset: 0x1C */
  __I  uint32_t UUIDMH;                            /**< 通用唯一标识符中高位寄存器, offset: 0x20 */
  __IO uint32_t CLKDIV;                            /**< (1-173)12.2.10 时钟分频器寄存器(CLKDIV), offset: 0x24 */
  __IO uint32_t SCGC1;                             /**< (1-174)12.2.11 时钟分频器寄存器(SCGC1), offset: 0x28 */
	   uint32_t RESERVED_0[1];
  __IO uint32_t LP;                                /**< 系统功耗控制寄存器, offset: 0x30 */
  __IO uint32_t WAIT;                              /**< 系统时钟稳定等待寄存器, offset: 0x34 */
} SIM_Type;

extern SIM_Type* 		SIM;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup SIM 
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup SIM_Exported_Constants SIM模块使用参数定义
  * @{
  */

/**
	* @defgroup System_Reset   系统复位标志
	* @{
	*/
#define SIM_ECCERR_RESET						SIM_SRSID_ECCERR_SHIFT
#define SIM_LVD_RESET							SIM_SRSID_LVD_SHIFT
#define SIM_WDOG_RESET							SIM_SRSID_WDOG_SHIFT
#define SIM_PIN_RESET							SIM_SRSID_PIN_SHIFT
#define SIM_POR_RESET							SIM_SRSID_POR_SHIFT
#define SIM_SW_RESET							SIM_SRSID_SW_SHIFT
/**
  * @}
  */
	
/**
	* @defgroup FTM2_Delay_Trigger   FTM2触发延迟
	* @{
	*/
#define ACMP0_OUTPUT_TRIGGER_FTM2							((uint8_t)0x00)
#define ACMP1_OUTPUT_TRIGGER_FTM2							((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup UART0_RxD_Filter    UART_RxD滤波器器选择
	* @{
	*/
#define UART0_RXD0_FILTER_NONE								((uint8_t)0x00)
#define UART0_RXD0_FILTER_ACMP0								((uint8_t)0x01)
#define UART0_RXD0_FILTER_ACMP1								((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup BUSCLK_Output_Div   BUSCLK时钟输出分频器
	* @{
	*/	
#define BUSCLOCK_OUTPUT_DIVIDE_1							((uint8_t)0x00)
#define BUSCLOCK_OUTPUT_DIVIDE_2							((uint8_t)0x01)
#define BUSCLOCK_OUTPUT_DIVIDE_4							((uint8_t)0x02)
#define BUSCLOCK_OUTPUT_DIVIDE_8							((uint8_t)0x03)
#define BUSCLOCK_OUTPUT_DIVIDE_16							((uint8_t)0x04)
#define BUSCLOCK_OUTPUT_DIVIDE_32							((uint8_t)0x05)
#define BUSCLOCK_OUTPUT_DIVIDE_64							((uint8_t)0x06)
#define BUSCLOCK_OUTPUT_DIVIDE_128							((uint8_t)0x07)
/**
	* @}
	*/
	
/**
	* @defgroup PWTIN2_To_ACMP   PWT输入连接到ACMP输出
	* @{
	*/	
#define PWTIN2_INPUT_ACMP1OUT									((uint8_t)0x00)
#define PWTIN2_INPUT_ACMP0OUT									((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup PWTIN3_To_UART   PWT输入连接到UART输出
	* @{
	*/
#define PWTIN3_INPUT_UART0RX					((uint8_t)0x00)
#define PWTIN3_INPUT_UART1RX					((uint8_t)0x01)
#define PWTIN3_INPUT_UART2RX					((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Hardware_Trigger_Source   ADC硬件触发源
	* @{
	*/	
#define ADC_HT_RTCOVERFLOW					 	 ((uint8_t)0x00)
#define ADC_HT_FTM0CH0MAP						 ((uint8_t)0x01)
#define ADC_HT_FTM2UPDATE						 ((uint8_t)0x02)
#define ADC_HT_FTM2CH0MAP						 ((uint8_t)0x03)
#define ADC_HT_PITCH0OVERFLOW				 	 ((uint8_t)0x04)
#define ADC_HT_PITCH1OVERFLOW				 	 ((uint8_t)0x05)
#define ADC_HT_ACMP0OUTPUT					 	 ((uint8_t)0x06)
#define ADC_HT_ACMP1OUTPUT					 	 ((uint8_t)0x07)
#define ADC_HT_FTM2CH1MAP						 ((uint8_t)0x08)
#define ADC_HT_FTM2CH2MAP						 ((uint8_t)0x09)
#define ADC_HT_FTM2CH3MAP						 ((uint8_t)0x0A)
#define ADC_HT_FTM2CH4MAP						 ((uint8_t)0x0B)
#define ADC_HT_FTM2CH5MAP						 ((uint8_t)0x0C)
#define ADC_HT_FTM1CH0MAP						 ((uint8_t)0x0D)
#define ADC_HT_FTM1CH1MAP						 ((uint8_t)0x0E)
#define ADC_HT_FTM0CH1MAP						 ((uint8_t)0x0F)
/**
	* @}
	*/
	
/**
	* @defgroup UART0_PIN_SEL   UART0端口引脚选择
	* @{
	*/
#define UART0_PS_PTB0_PTB1						((uint8_t)0x00)
#define UART0_PS_PTA2_PTA3						((uint8_t)0x01)
#define UART0_PS_PTC2_PTC3						((uint8_t)0x02)
/**
	* @}
	*/	

/**
	* @defgroup FTM0PS0_PIN_SEL   FTM0通道0端口引脚选择
	* @{
	*/	
#define FTM0CH0_PS_PTA0							((uint8_t)0x00)
#define FTM0CH0_PS_PTB2							((uint8_t)0x01)
#define FTM0CH0_PS_PTE5							((uint8_t)0x02)
#define FTM0CH0_PS_PTF4							((uint8_t)0x03)
/**
	* @}
	*/
	
/**
	* @defgroup FTM0PS1_PIN_SEL   FTM0通道1端口引脚选择
	* @{
	*/	
#define FTM0CH1_PS_PTA1							((uint8_t)0x00)
#define FTM0CH1_PS_PTB3							((uint8_t)0x01)
#define FTM0CH1_PS_PTE6							((uint8_t)0x02)
#define FTM0CH1_PS_PTF5							((uint8_t)0x03)
/**
	* @}
	*/
	
/**
	* @defgroup FTM1PS0_PIN_SEL   FTM1通道0端口引脚选择
	* @{
	*/	
#define FTM1CH0_PS_PTC4							((uint8_t)0x00)
#define FTM1CH0_PS_PTH2							((uint8_t)0x01)
#define FTM1CH0_PS_PTE5							((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM1PS1_PIN_SEL   FTM1通道1端口引脚选择
	* @{
	*/	
#define FTM1CH1_PS_PTC5							((uint8_t)0x00)
#define FTM1CH1_PS_PTE7							((uint8_t)0x01)
#define FTM1CH1_PS_PTE6							((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM_FLT2_PIN_SEL   FTM_FLT2端口引脚选择
	* @{
	*/	
#define FTM_FLT2_PS_PTA7						((uint8_t)0x00)
#define FTM_FLT2_PS_PTI1						((uint8_t)0x01)
#define FTM_FLT2_PS_PTF7						((uint8_t)0x02)
#define FTM_FLT2_PS_PTF6						((uint8_t)0x03)
/**
	* @}
	*/	

/**
	* @defgroup FTM_FLT1_PIN_SEL   FTM_FLT1端口引脚选择
	* @{
	*/	
#define FTM_FLT1_PS_PTA6						((uint8_t)0x00)
#define FTM_FLT1_PS_PTI1						((uint8_t)0x01)
#define FTM_FLT1_PS_PTF7						((uint8_t)0x02)
#define FTM_FLT1_PS_PTF6						((uint8_t)0x03)
/**
	* @}
	*/	
	
/**
	* @defgroup BUSOUT_PIN_SEL   BUSCLK输出端口引脚选择
	* @{
	*/	
#define BUSOUT_PS_PTH2						  ((uint8_t)0x00)
#define BUSOUT_PS_PTH6						  ((uint8_t)0x01)
#define BUSOUT_PS_PTB5						  ((uint8_t)0x02)
/**
	* @}
	*/	
	
/**
	* @defgroup TCLK2_PIN_SEL   TCLK2端口引脚选择
	* @{
	*/	
#define TCLK2_PS_PTE7						    ((uint8_t)0x00)
#define TCLK2_PS_PTH7						    ((uint8_t)0x01)
#define TCLK2_PS_PTD5						    ((uint8_t)0x02)
/**
	* @}
	*/	
	
/**
	* @defgroup TCLK1_PIN_SEL   TCLK1端口引脚选择
	* @{
	*/	
#define TCLK1_PS_PTE0						    ((uint8_t)0x00)
#define TCLK1_PS_PTH7						    ((uint8_t)0x01)
#define TCLK1_PS_PTD5						    ((uint8_t)0x02)
/**
	* @}
	*/	
	
/**
	* @defgroup TCLK0_PIN_SEL   TCLK0端口引脚选择
	* @{
	*/	
#define TCLK0_PS_PTH7						    ((uint8_t)0x01)
#define TCLK0_PS_PTD5						    ((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM0CLK_PIN_SEL   FTM0外部时钟引脚选择
	* @{
	*/	
#define FTM0CLK_PS_TCLK0										((uint8_t)0x00)
#define FTM0CLK_PS_TCLK1										((uint8_t)0x01)
#define FTM0CLK_PS_TCLK2										((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM1CLK_PIN_SEL   FTM1外部时钟引脚选择
	* @{
	*/	
#define FTM1CLK_PS_TCLK0										((uint8_t)0x00)
#define FTM1CLK_PS_TCLK1										((uint8_t)0x01)
#define FTM1CLK_PS_TCLK2										((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup ACMP_Hyst   ACMP模拟比较迟滞选择
	* @{
	*/
#define FTM2CLK_PS_TCLK0										((uint8_t)0x00)
#define FTM2CLK_PS_TCLK1										((uint8_t)0x01)
#define FTM2CLK_PS_TCLK2										((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CLK_PIN_SEL   FTM2外部时钟引脚选择
	* @{
	*/
#define PWTCLK_PS_TCLK0											((uint8_t)0x00)
#define PWTCLK_PS_TCLK1											((uint8_t)0x01)
#define PWTCLK_PS_TCLK2											((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH0_PIN_SEL   FTM2通道0引脚选择
	* @{
	*/	
#define FTM2CH0_PS_PTC0											((uint8_t)0x00)
#define FTM2CH0_PS_PTH0											((uint8_t)0x01)
#define FTM2CH0_PS_PTF0											((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH1_PIN_SEL   FTM2通道1引脚选择
	* @{
	*/	
#define FTM2CH1_PS_PTC1											((uint8_t)0x00)
#define FTM2CH1_PS_PTH1											((uint8_t)0x01)
#define FTM2CH1_PS_PTF1											((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH2_PIN_SEL   FTM2通道2引脚选择
	* @{
	*/	
#define FTM2CH2_PS_PTC2											((uint8_t)0x00)
#define FTM2CH2_PS_PTD0											((uint8_t)0x01)
#define FTM2CH2_PS_PTG4											((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH3_PIN_SEL   FTM2通道3引脚选择
	* @{
	*/	
#define FTM2CH3_PS_PTC3											((uint8_t)0x00)
#define FTM2CH3_PS_PTD1											((uint8_t)0x01)
#define FTM2CH3_PS_PTG5											((uint8_t)0x02)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH4_PIN_SEL   FTM2通道4引脚选择
	* @{
	*/	
#define FTM2CH4_PS_PTB4											((uint8_t)0x00)
#define FTM2CH4_PS_PTG6											((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup FTM2CH5_PIN_SEL   FTM2通道5引脚选择
	* @{
	*/
#define FTM2CH5_PS_PTB5											((uint8_t)0x00)
#define FTM2CH5_PS_PTG7											((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup I2C1_PIN_SEL    I2C1引脚选择
	* @{
	*/	
#define I2C1_PS_PTE1_PTE0										((uint8_t)0x00)
#define I2C1_PS_PTH4_PTH3										((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup SPI1_PIN_SEL    SPI1引脚选择
	* @{
	*/	
#define SPI1_PS_PTD0_PTD1_PTD2_PTD3					((uint8_t)0x00)
#define SPI1_PS_PTG4_PTG5_PTG6_PTG7					((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup	UART1_PIN_SEL    UART1引脚选择
	* @{
	*/
#define UART1_PS_PTC7_PTC6									((uint8_t)0x00)
#define UART1_PS_PTF3_PTF2									((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup UART2_PIN_SEL    UART2引脚选择
	* @{
	*/	
#define UART2_PS_PTD7_PTD6									((uint8_t)0x00)
#define UART2_PS_PTI1_PTI0									((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup PWTIN0_PIN_SEL    PWTIN0引脚选择
	* @{
	*/
#define PWTIN0_PS_PTD5											((uint8_t)0x00)
#define PWTIN0_PS_PTE2											((uint8_t)0x01)
/**	
	* @}
	*/
	
/**
	* @defgroup PWTIN1_PIN_SEL    PWTIN1引脚选择
	* @{
	*/
#define PWTIN1_PS_PTB0											((uint8_t)0x00)
#define PWTIN1_PS_PTH7											((uint8_t)0x01)
/**
	* @}
	*/

/**
	* @defgroup ACMP_Hyst   ACMP模拟比较迟滞选择
	* @{
	*/	
#define SPI0_PS_PTB2_PTB3_PTB4_PTB5				((uint8_t)0x00)
#define SPI0_PS_PTE0_PTE1_PTE2_PTE3				((uint8_t)0x01)
/**
	* @}
	*/


/**
	* @defgroup EWM_PIN_SEL    EWM引脚选择
	* @{
	*/
#define EWM_PS_PTA3_PTA2										((uint8_t)0x00)
#define EWM_PS_PTC4_PTA4										((uint8_t)0x01)
#define EWM_PS_PTE7_PTH2										((uint8_t)0x02)
/**
	* @}
	*/	

/**
	* @defgroup IRQ_PIN_SEL   IRQ端口引脚选择
	* @{
	*/
#define IRQ_PS_GROUP1							((uint8_t)0x00)
#define IRQ_PS_GROUP2							((uint8_t)0x01)
#define IRQ_PS_GROUP3							((uint8_t)0x02)
#define IRQ_PS_GROUP4							((uint8_t)0x03)
#define IRQ_PS_GROUP5							((uint8_t)0x04)
/**
	* @}
	*/



/**
	* @defgroup ACMP1_PIN_SEL   ACMP1端口引脚选择
	* @{
	*/	
#define ACMP1_PS_PTB5						 ((uint8_t)0x00)
#define ACMP1_PS_PTI1						 ((uint8_t)0x01)
/**
	* @}
	*/
	
/**
	* @defgroup RTCO_PIN_SEL   RTCO端口引脚选择
	* @{
	*/	
#define RTCO_PS_PTC4							((uint8_t)0x00)
#define RTCO_PS_PTC5							((uint8_t)0x01)
/**
	* @}
	*/	
	
/**
	* @defgroup I2C0_PIN_SEL    I2C0引脚选择
	* @{
	*/
#define I2C0_PS_PTA3_PTA2						((uint8_t)0x00)
#define I2C0_PS_PTB7_PTB6						((uint8_t)0x01)
/**
	* @}
	*/


/**
	* @defgroup FTM0CH2_PIN_SEL   FTM0通道2引脚选择
	* @{
	*/	
#define FTM0CH2_PS_PTH7							((uint8_t)0x00)
#define FTM0CH2_PS_PTD5							((uint8_t)0x01)
/**
	* @}
	*/

/**
	* @defgroup FTM0CH3_PIN_SEL   FTM0通道3引脚选择
	* @{
	*/	
#define FTM0CH3_PS_PTE4							((uint8_t)0x00)
#define FTM0CH3_PS_PTD4							((uint8_t)0x01)
/**
	* @}
	*/


/**
	* @defgroup FTM1CH2_PIN_SEL   FTM1通道2引脚选择
	* @{
	*/	
#define FTM1CH2_PS_PTH1							((uint8_t)0x00)
#define FTM1CH2_PS_PTB4							((uint8_t)0x01)
/**
	* @}
	*/

/**
	* @defgroup FTM1CH3_PIN_SEL   FTM1通道3引脚选择
	* @{
	*/	
#define FTM1CH3_PS_PTH0							((uint8_t)0x00)
#define FTM1CH3_PS_PTE3							((uint8_t)0x01)
/**
	* @}
	*/


/**
	* @defgroup FTM2CH6_PIN_SEL   FTM2通道6引脚选择
	* @{
	*/	
#define FTM2CH6_PS_PTF3							((uint8_t)0x00)
#define FTM2CH6_PS_PTD3							((uint8_t)0x01)
/**
	* @}
	*/

/**
	* @defgroup FTM2CH7_PIN_SEL   FTM2通道7引脚选择
	* @{
	*/	
#define FTM2CH7_PS_PTF2							((uint8_t)0x00)
#define FTM2CH7_PS_PTD2							((uint8_t)0x01)
/**
	* @}
	*/

	
	
/**
	* @defgroup SCGC_Clock_Control   外设时钟开关控制1
	* NOTE: (1-166)12.2.6 系统时钟选通控制寄存器(SCGC)
	* @{
	*/	
#define SIM_SCGC_RTC	                        0x00000001u
#define SIM_SCGC_PIT                        	0x00000002u
#define SIM_SCGC_EWM                        	0x00000004u
#define SIM_SCGC_PWT                        	0x00000010u
#define SIM_SCGC_FTM0                       	0x00000020u
#define SIM_SCGC_FTM1                       	0x00000040u
#define SIM_SCGC_FTM2                       	0x00000080u
#define SIM_SCGC_CLMA                       	0x00000100u
#define SIM_SCGC_CLMB                       	0x00000200u
#define SIM_SCGC_CRC                        	0x00000400u
#define SIM_SCGC_WDG						 	0x00000800u	

#define SIM_SCGC_MCAN                       	0x00004000u
#define SIM_SCGC_I2C0                       	0x00010000u
#define SIM_SCGC_I2C1                       	0x00020000u
#define SIM_SCGC_SPI0                       	0x00040000u
#define SIM_SCGC_SPI1                       	0x00080000u
#define SIM_SCGC_UART0                      	0x00100000u
#define SIM_SCGC_UART1                      	0x00200000u
#define SIM_SCGC_UART2                      	0x00400000u
#define SIM_SCGC_KBI0                       	0x01000000u
#define SIM_SCGC_KBI1                       	0x02000000u
#define SIM_SCGC_IRQ                        	0x08000000u
#define SIM_SCGC_DMA                        	0x10000000u
#define SIM_SCGC_ADC                        	0x20000000u
#define SIM_SCGC_ACMP0                      	0x40000000u
#define SIM_SCGC_ACMP1                      	0x80000000u
/**
	* @}
	*/
	
/**
	* @defgroup SCGC1_Clock_Control   外设时钟开关控制2
	* @{
	*/	
#define SIM_SCGC1_FTM2F	                      	0x00000001u
#define SIM_SCGC1_FTM1F                       	0x00000002u
#define SIM_SCGC1_FTM0F                       	0x00000004u
#define SIM_SCGC1_RTCEC                     	0x00000020u
#define SIM_SCGC1_ADCALTC                     	0x00000040u
#define SIM_SCGC1_FTM2T                       	0x01000000u
#define SIM_SCGC1_FTM1T                       	0x02000000u
#define SIM_SCGC1_FTM0T                      	0x04000000u
#define SIM_SCGC1_RTCLPOC                     	0x10000000u


/**
	* @}
	*/
	
/**
	* @defgroup LowerPower_FLASH_RAM_Control   LP低功耗模式Flash和RAM电源控制
	* @{
	*/
#define SIM_LP_USER_FLASH                 		0x00000004u
#define SIM_LP_STOP_FLASH	                	0x00000008u
#define SIM_LP_USER_RAM1	                	0x00000020u
#define SIM_LP_USER_RAM2                  		0x00000040u
#define SIM_LP_USER_RAM3                  		0x00000080u
#define SIM_LP_STOP_RAM1	                	0x00000200u
#define SIM_LP_STOP_RAM2                  		0x00000400u
#define SIM_LP_STOP_RAM3                  		0x00000800u
/**
	* @}
	*/
	
/**
	* @defgroup SRAM_SIZE   SRAM大小
	* @{
	*/		
#define SRAM_SIZE_24KB                  		0x00u
#define SRAM_SIZE_16KB                  		0x01u
/**
	* @}
	*/
	
/**
	* @defgroup FLASH_SIZE   FLASH大小
	* @{
	*/		
#define FLASH_SIZE_256KB                  		0x00u
#define FLASH_SIZE_128KB                  		0x01u
/**
	* @}
	*/	
	

/**
  * @}
  */
	
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void SIM_DeInit(void);
uint32_t SIM_ReadFPINID(void);
FlagStatus SIM_GetRstCauses(uint32_t ResetCause);
void SIM_ClrRstCauses(uint8_t ResetCause);
void SIM_SOPT0_NMIECmd(FunctionalState State);
void SIM_SOPT0_RSTPECmd(FunctionalState State);
void SIM_SOPT0_SWDECmd(FunctionalState State);
void SIM_SOPT0_ACMPT_FTM2Config(uint8_t TriggerType);
void SIM_SOPT0_UART0FilterConfig(uint32_t FilterType);
void SIM_SOPT0_FTM1CH1C_RTCOutputCmd(FunctionalState State);
void SIM_SOPT0_FTM1CH0C_ACMP0OCmd(FunctionalState State);
void SIM_SOPT0_FTM0CH1C_UART0ICmd(FunctionalState State);
void SIM_SOPT0_FTM2S_PWMCmd(FunctionalState State);
void SIM_SOPT0_FTM0M_UART0OutputCmd(FunctionalState State);
void SIM_SOPT0_BusClockDivide(uint8_t Divide);
void SIM_SOPT0_BusClockOutputCmd(FunctionalState State);
FlagStatus SIM_SOPT0_FTM2DelayTStatus(void);
void SIM_SOPT0_FTM2DelayTConfig(uint8_t Delay);

void SIM_SOPT1_PWTIN2InputConfig(uint8_t InputType);
void SIM_SOPT1_PWTIN3InputConfig(uint8_t InputType);
void SIM_SOPT1_ADCHardwareTConfig(uint8_t TriggerType);



void SIM_PINSEL_UART0(uint8_t PinSelect);
void SIM_PINSEL_FTM0CH0(uint8_t PinSelect);
void SIM_PINSEL_FTM0CH1(uint8_t PinSelect);
void SIM_PINSEL_FTM1CH0(uint8_t PinSelect);
void SIM_PINSEL_FTM1CH1(uint8_t PinSelect);
void SIM_PINSEL_FTMFLT2(uint8_t PinSelect);
void SIM_PINSEL_FTMFLT1(uint8_t PinSelect);
void SIM_PINSEL_BUSOUT(uint8_t PinSelect);
void SIM_PINSEL_TCLK2(uint8_t PinSelect);
void SIM_PINSEL_TCLK1(uint8_t PinSelect);
void SIM_PINSEL_TCLK0(uint8_t PinSelect);
void SIM_PINSEL_FTM0TCLK(uint8_t PinSelect);
void SIM_PINSEL_FTM1TCLK(uint8_t PinSelect);
void SIM_PINSEL_FTM2TCLK(uint8_t PinSelect);
void SIM_PINSEL_PWTTCLK(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH0(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH1(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH2(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH3(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH4(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH5(uint8_t PinSelect);
void SIM_PINSEL_I2C1(uint8_t PinSelect);
void SIM_PINSEL_SPI1(uint8_t PinSelect);
void SIM_PINSEL_UART1(uint8_t PinSelect);
void SIM_PINSEL_UART2(uint8_t PinSelect);
void SIM_PINSEL_PWTIN0(uint8_t PinSelect);
void SIM_PINSEL_PWTIN1(uint8_t PinSelect);
void SIM_PINSEL_SPI0(uint8_t PinSelect);
void SIM_PINSEL_EWM(uint8_t PinSelect);
void SIM_PINSEL_IRQ(uint8_t PinSelect);
void SIM_PINSEL_ACMP(uint8_t PinSelect);
void SIM_PINSEL_RTC(uint8_t PinSelect);
void SIM_PINSEL_I2C0(uint8_t PinSelect);
void SIM_PINSEL_FTM0CH2(uint8_t PinSelect);
void SIM_PINSEL_FTM0CH3(uint8_t PinSelect);
void SIM_PINSEL_FTM1CH2(uint8_t PinSelect);
void SIM_PINSEL_FTM1CH3(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH6(uint8_t PinSelect);
void SIM_PINSEL_FTM2CH7(uint8_t PinSelect);

void SIM_SCGC_Cmd(uint32_t SCGC_Type, FunctionalState State);

uint32_t SIM_GetUUIDL(void);
uint32_t SIM_GetUUIDML(void);
uint32_t SIM_GetUUIDMH(void);
uint8_t SIM_GetSRAMSize(void);
uint8_t SIM_GetFLASHSize(void);
uint8_t SIM_GetVer(void);
uint8_t SIM_GetDevID(void);

void SIM_CLKDIV_OUTDIV1(uint32_t divide);
void SIM_CLKDIV_OUTDIV2(uint32_t divide);
void SIM_CLKDIV_OUTDIV3(uint32_t divide);
void SIM_CLKDIV_OUTDIV4(uint32_t divide);
uint8_t SIM_GetOUTDIV1(void);
uint8_t SIM_GetOUTDIV2(void);
uint8_t SIM_GetOUTDIV3(void);
uint8_t SIM_GetOUTDIV4(void);

void SIM_SCGC1_Cmd(uint32_t SCGC1_Type, FunctionalState State);

void SIM_LP_SetLowpowerCmd(uint32_t LP_Type);
FlagStatus SIM_LP_FLASHPowerONStatus(void);
FlagStatus SIM_LP_SRAMPowerONStatus(void);

void SIM_WAIT_CLKWAITConfig(uint16_t Clkwait);
void SIM_WAIT_DIV1USConfig(uint16_t Div1us);
#ifdef __cplusplus
}
#endif	
	
	
#endif			 /*__XL_SIM_H__ */
/**
  * @}
  */

/**
  * @}
  */


