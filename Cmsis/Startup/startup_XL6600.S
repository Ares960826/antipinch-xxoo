/**
  ******************************************************************************
  * @file      startup_Xl6600.s
  * @author    chipways
  * @version   V3.5.0
  * @date      11-March-2011
  * @brief     xl6600d High Density Devices vector table for Atollic toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address,
  *                - Configure the clock system
  *                - Configure external SRAM mounted on xl6600d board
  *                  to be used as data memory (optional, to be enabled by user)
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M3 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, CHIPWAYS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 CHIPWAYS</center></h2>
  ******************************************************************************
  */

    .syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

.global	g_pfnVectors
.global	Default_Handler

.global GPIOA
.global GPIOB
.global GPIOC
.global IRQ
.global	SCB
.global	NVIC
.global SysTick
.global	SIM
.global	KBI0
.global	KBI1
.global	PIT
.global	RTC
.global	PWT
.global	UART0
.global	UART1
.global	UART2
.global	WDOG
.global	MCAN
.global	ICS
.global	OSC
.global	FTM0
.global	FTM1
.global	FTM2
.global	FMC
.global	I2C0
.global	I2C1
.global	SPI0
.global	SPI1
.global	PORT
.global	PMC
.global	ACMP0
.global	ACMP1
.global	ADC0
.global	CLMA
.global	CLMB
.global	CRC
.global	DMA
.global	EWM

/* start address for the initialization values of the .data section.
defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

.equ  BootRAM,        0xF1E0F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section	.text.Reset_Handler
	.weak	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:

/* Copy the data segment initializers from flash to SRAM */
  movs	r1, #0
  b	LoopCopyDataInit
  
CopyDataInit:
	ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
/*	b	LoopFillZerobss	*/
 	movs	r1, #0
	b	LoopCopyFalshCodeInit

CopyFlashCodeInit:
	ldr	r3, =_flash_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyFalshCodeInit:
	ldr	r0, =_flash_start
	ldr	r3, =_flash_end
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyFlashCodeInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
	
/* Zero fill the bss segment. */
FillZerobss:
	movs	r3, #0
	str	r3, [r2], #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss
/* Initialize the stack pointer */
 	ldr	r0,=_estack
  mov	r13,r0
/* Call the clock system intitialization function.*/
    bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
	bl	main
	bx	lr
.size	Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	Reserved16_IRQHandler
	.word	Reserved17_IRQHandler
	.word	Reserved18_IRQHandler
	.word	Reserved19_IRQHandler
	.word	Reserved20_IRQHandler
	.word	FMC_IRQHandler
	.word	PMC_IRQHandler
	.word	DMA_IRQHandler
	.word	I2C0_IRQHandler
	.word	I2C1_IRQHandler
	.word	SPI0_IRQHandler
	.word	SPI1_IRQHandler
	.word	UART0_IRQHandler
	.word	UART1_IRQHandler
	.word	UART2_IRQHandler
	.word	ADC0_IRQHandler
	.word	ACMP0_IRQHandler
	.word	FTM0_IRQHandler
	.word	FTM1_IRQHandler
	.word	FTM2_IRQHandler
	.word	RTC_IRQHandler
	.word	ACMP1_IRQHandler
	.word	PIT_CH0_IRQHandler
	.word	PIT_CH1_IRQHandler
	.word	KBI0_IRQHandler
	.word	KBI1_IRQHandler
	.word	Reserved42_IRQHandler
	.word	ICS_IRQHandler
	.word	WDOG_IRQHandler
	.word	PWT_IRQHandler
	.word	MCAN_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	EXTI5_IRQHandler
	.word	EXTI6_IRQHandler
	.word	EXTI7_IRQHandler
	.word	EXTI8_IRQHandler
	.word	EXTI9_IRQHandler
	.word	EXTI10_IRQHandler
	.word	EXTI11_IRQHandler
	.word	EXTI12_IRQHandler
	.word	EXTI13_IRQHandler
	.word	EXTI14_IRQHandler
	.word	EXTI15_IRQHandler
	.word	EWM_IRQHandler
	.word	Reserved21_IRQHandler
	.word	BootRAM       /* @0x1E0. This is for boot in RAM mode for
                         xl6600d High Density devices. */
GPIOA:
    .word	0x40100000
GPIOB:
	.word	0x40100040
GPIOC:
	.word	0x40100080
IRQ:
	.word	0x40031000
SysTick:
	.word	0xE000E010
NVIC:
	.word	0xE000E100
SCB:
	.word	0xE000ED00
SIM:
	.word	0x40048000
KBI0:
	.word	0x40079000
KBI1:
	.word	0x4007A000
PIT:
	.word	0x40037000
RTC:
	.word	0x4003D000
PWT:
	.word	0x40033000
UART0:
	.word	0x4006A000
UART1:
	.word	0x4006B000
UART2:
	.word	0x4006C000
WDOG:
	.word	0x40052000
MCAN:
	.word	0x40024000
ICS:
	.word	0x40064000
OSC:
	.word	0x40065000
FTM0:
	.word	0x40038000
FTM1:
	.word	0x40039000
FTM2:
	.word	0x4003A000
FMC:
	.word	0x40020000
I2C0:
	.word	0x40066000
I2C1:
	.word	0x40067000
SPI0:
	.word	0x40076000
SPI1:
	.word	0x40077000
PORT:
	.word	0x40140000
PMC:
	.word	0x4007D000
ACMP0:
	.word	0x40073000
ACMP1:
	.word	0x40074000
ADC0:
	.word	0x4003B000
CLMA:
	.word	0x4007E000
CLMB:
	.word	0x4007F000
CRC:
	.word	0x40032000
DMA:
	.word	0x40080000
EWM:
	.word	0x4007C000
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  .weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

  .weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

  .weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	Reserved16_IRQHandler
	.thumb_set Reserved16_IRQHandler,Default_Handler

	.weak	Reserved17_IRQHandler
	.thumb_set Reserved17_IRQHandler,Default_Handler

	.weak	Reserved18_IRQHandler
	.thumb_set Reserved18_IRQHandler,Default_Handler

	.weak	Reserved19_IRQHandler
	.thumb_set Reserved19_IRQHandler,Default_Handler

	.weak	Reserved20_IRQHandler
	.thumb_set Reserved20_IRQHandler,Default_Handler

	.weak	FMC_IRQHandler
	.thumb_set FMC_IRQHandler,Default_Handler

	.weak	PMC_IRQHandler
	.thumb_set PMC_IRQHandler,Default_Handler

	.weak	DMA_IRQHandler
	.thumb_set DMA_IRQHandler,Default_Handler

	.weak	I2C0_IRQHandler
	.thumb_set I2C0_IRQHandler,Default_Handler

	.weak	I2C1_IRQHandler
	.thumb_set I2C1_IRQHandler,Default_Handler

	.weak	SPI0_IRQHandler
	.thumb_set SPI0_IRQHandler,Default_Handler

	.weak	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler

	.weak	UART0_IRQHandler
	.thumb_set UART0_IRQHandler,Default_Handler

	.weak	UART1_IRQHandler
	.thumb_set UART1_IRQHandler,Default_Handler

	.weak	UART2_IRQHandler
	.thumb_set UART2_IRQHandler,Default_Handler

	.weak	ADC0_IRQHandler
	.thumb_set ADC0_IRQHandler,Default_Handler

	.weak	ACMP0_IRQHandler
	.thumb_set ACMP0_IRQHandler,Default_Handler

	.weak	FTM0_IRQHandler
	.thumb_set FTM0_IRQHandler,Default_Handler

	.weak	FTM1_IRQHandler
	.thumb_set FTM1_IRQHandler,Default_Handler

	.weak	FTM2_IRQHandler
	.thumb_set FTM2_IRQHandler,Default_Handler

	.weak	RTC_IRQHandler
	.thumb_set RTC_IRQHandler,Default_Handler

	.weak	ACMP1_IRQHandler
	.thumb_set ACMP1_IRQHandler,Default_Handler

	.weak	PIT_CH0_IRQHandler
	.thumb_set PIT_CH0_IRQHandler,Default_Handler

	.weak	PIT_CH1_IRQHandler
	.thumb_set PIT_CH1_IRQHandler,Default_Handler

	.weak	KBI0_IRQHandler
	.thumb_set KBI0_IRQHandler,Default_Handler

	.weak	KBI1_IRQHandler
	.thumb_set KBI1_IRQHandler,Default_Handler

	.weak	Reserved42_IRQHandler
	.thumb_set Reserved42_IRQHandler,Default_Handler

	.weak	ICS_IRQHandler
	.thumb_set ICS_IRQHandler,Default_Handler

	.weak	WDOG_IRQHandler
	.thumb_set WDOG_IRQHandler,Default_Handler

	.weak	PWT_IRQHandler
	.thumb_set PWT_IRQHandler,Default_Handler

	.weak	MCAN_IRQHandler
	.thumb_set MCAN_IRQHandler,Default_Handler

	.weak	EXTI0_IRQHandler
	.thumb_set EXTI0_IRQHandler,Default_Handler

	.weak	EXTI1_IRQHandler
	.thumb_set EXTI1_IRQHandler,Default_Handler

	.weak	EXTI2_IRQHandler
	.thumb_set EXTI2_IRQHandler,Default_Handler

	.weak	EXTI3_IRQHandler
	.thumb_set EXTI3_IRQHandler,Default_Handler

	.weak	EXTI4_IRQHandler
	.thumb_set EXTI4_IRQHandler,Default_Handler

	.weak	EXTI5_IRQHandler
	.thumb_set EXTI5_IRQHandler,Default_Handler

	.weak	EXTI6_IRQHandler
	.thumb_set EXTI6_IRQHandler,Default_Handler

	.weak	EXTI7_IRQHandler
	.thumb_set EXTI7_IRQHandler,Default_Handler

	.weak	EXTI8_IRQHandler
	.thumb_set EXTI8_IRQHandler,Default_Handler

	.weak	EXTI9_IRQHandler
	.thumb_set EXTI9_IRQHandler,Default_Handler

	.weak	EXTI10_IRQHandler
	.thumb_set EXTI10_IRQHandler,Default_Handler

	.weak	EXTI11_IRQHandler
	.thumb_set EXTI11_IRQHandler,Default_Handler

	.weak	EXTI12_IRQHandler
	.thumb_set EXTI12_IRQHandler,Default_Handler

	.weak	EXTI13_IRQHandler
	.thumb_set EXTI13_IRQHandler,Default_Handler

	.weak	EXTI14_IRQHandler
	.thumb_set EXTI14_IRQHandler,Default_Handler

	.weak	EXTI15_IRQHandler
	.thumb_set EXTI15_IRQHandler,Default_Handler

	.weak	EWM_IRQHandler
	.thumb_set EWM_IRQHandler,Default_Handler

	.weak	Reserved21_IRQHandler
	.thumb_set Reserved21_IRQHandler,Default_Handler

.ifndef	RAM_TARGET
.org	0x400
/*
; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict acces to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Key 0  <0x0-0xFF:2>
;     <o1>  Backdoor Key 1  <0x0-0xFF:2>
;     <o2>  Backdoor Key 2  <0x0-0xFF:2>
;     <o3>  Backdoor Key 3  <0x0-0xFF:2>
;     <o4>  Backdoor Key 4  <0x0-0xFF:2>
;     <o5>  Backdoor Key 5  <0x0-0xFF:2>
;     <o6>  Backdoor Key 6  <0x0-0xFF:2>
;     <o7>  Backdoor Key 7  <0x0-0xFF:2>
*/
.set BackDoorK0,	0xff /* 0x11 *//* flash security key = 0x11 */
.set BackDoorK1,	0xff
.set BackDoorK2,	0xff
.set BackDoorK3,	0xff
.set BackDoorK4,	0xff
.set BackDoorK5,	0xff
.set BackDoorK6,	0xff
.set BackDoorK7,	0xff
/*
;   </h>
;     <h> FPROT
;       <i> P-Flash Protection Register
;       <o.7> FPOPEN
;         <0=> FPHDIS and FPLDIS bits define unprotected address ranges as specified by the corresponding FPHS and FPLS bits FPROT1.1
;         <1=> FPHDIS and FPLDIS bits enable protection for the address range specified by the corresponding FPHS and FPLS bits
;       <o.5> FPHDIS
;         <0=> Protection/Unprotection enabled
;         <1=> Protection/Unprotection disabled
;       <o.3..4> FPHS
;         <0=> Address range: 0x00_7C00-0x00_7FFF; protected size: 1 KB
;         <1=> Address range: 0x00_7800-0x00_7FFF; protected size: 2 KB
;         <2=> Address range: 0x00_7000-0x00_7FFF; protected size: 4 KB
;         <3=> Address range: 0x00_6000-0x00_7FFF; protected size: 8 KB
;       <o.5> FPLDIS
;         <0=> Protection/Unprotection enabled
;         <1=> Protection/Unprotection disabled
;       <o.3..4> FPLS
;         <0=> Address range: 0x00_0000-0x00_07FF; protected size: 2 KB
;         <1=> Address range: 0x00_0000-0x00_0FFF; protected size: 4 KB
;         <2=> Address range: 0x00_0000-0x00_1FFF; protected size: 8 KB
;         <3=> Address range: 0x00_0000-0x00_3FFF; protected size: 16 KB
*/
.set FPROT,	0xff
/*
;     </h>
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;         <i> This bits define the security state of the MCU.
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor key Security Enable
;         <i> These bits enable and disable backdoor key access to the FTFL module.
*/
.set FSEC,	0xff  /* 0x1f *//* flash security FSEC = 0x1f */
/*
;   </h>
;   <h> Flash Option Register (FOPT)
*/
.set FOPT,	0xff

	.byte	BackDoorK0
	.byte	BackDoorK1
	.byte	BackDoorK2
	.byte	BackDoorK3
	.byte	BackDoorK4
	.byte	BackDoorK5
	.byte	BackDoorK6
	.byte	BackDoorK7
	.byte	0xff
	.byte	0xff
	.byte	0xff
	.byte	0xff
	.byte	0xff
	.byte	FPROT
	.byte	FSEC
	.byte	FOPT
.endif

/******************* (C) COPYRIGHT 2011 CHIPWAYS *****END OF FILE****/
