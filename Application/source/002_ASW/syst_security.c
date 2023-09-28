/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*Name     :  syst_security.c                                                         *
;*Project  :  AntiPinch   ¤ù¡G                                                 *
;*Device   :  S12VR64					                                                 *
;*AUTHOR   :  AP project team						                                       *
;*DATE     :  2010/05/20					                                             *
;*SW VER   :  0.1					                                                     *
;*HW VER   :    					                                                     *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;* COPYRIGHT STEC(C) Shanghai SIIC Transportation Electric CO.,ltd             *
;*                                                                             *
;* ALL RIGHTS RESERVED                                                         *
;*                                                                             *
;* The reproduction, transmission, or use of this document or its content is   *
;* not permitted without express written authority. Offenders will be liable   *
;* for damages.                                                                *
;* All rights, including rights created by patent grant or registration of a   *
;* utility model or design, are reserved.                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#include "Types.h"
#include "Typedef.h"


#include "syst_security.h"
#include "complier_sw.h"

//#define STACK_TOP_GUARD       0xFFFF   // initialized with macro INIT_STACK
//#define STACK_BOTTOM_GUARD    0x0000   // initialized with function clr_mem()

//#pragma DATA_SEG ZRAM_SYTEST0

//#pragma DATA_SEG RAM_SYTEST1
_Init_SAVE_RAM volatile T_UBYTE  SY_uc_BitRamCtl     ;//__attribute__((__section__(".test_ram)"))) ;
_Init_SAVE_RAM volatile T_UWORD  SY_ui_ByteRamCtlKey ;//__attribute__((__section__(".test_ram)"))) ;
_Init_SAVE_RAM volatile T_UWORD  SY_ui_ByteRamCtlTM  ;//__attribute__((__section__(".test_ram)"))) ;
_Init_SAVE_RAM volatile T_UWORD  SY_ui_RamCtrlCHKSUM ;//__attribute__((__section__(".test_ram)"))) ;

/* Declaration of the two words used as border of the stack */
//#include "defram.h"
//T_UWORD SY_UserStackBottom;           /* border on the bottom */
//T_UWORD SY_UserStackTop;              /* border on the top */

//volatile T_FLAG8  SY_T8_StatusFlag;
_Init_SAVE_RAM volatile uint8_t  SY_uc_StatusRAMStack;
volatile uint8_t  SY_uc_sleep;
volatile uint8_t  SY_uc_poweron_sw;
/* Private functions */
/* ----------------- */
uint16_t  SY_RamCtl_Calc(void);

void SY_RamCtlInit(void);
void SY_RamCtlUpdate(void);
void SY_RamCtlCheck(void);

/******************************************************************************
* Description:                                                                *
*                                                                             *
* SY_RamCtl_Calc(void)                                                        *
*                                                                             *
* system RAM  valuables calculate                                             *
*                                                                             * 
* Parameters:                                                                 *
*                                                                             *
* Return: checksum                                                            *
*                                                                             *
******************************************************************************/
uint16_t  SY_RamCtl_Calc(void)
{
  uint16_t   SY_ui_tempchk;

	SY_ui_tempchk = 0;
  
	SY_ui_tempchk += (uint16_t )SY_uc_BitRamCtl;
	SY_ui_tempchk += SY_ui_ByteRamCtlTM; 
	SY_ui_tempchk += SY_ui_RamCtrlCHKSUM; 

	return((uint16_t )SY_ui_tempchk);
}  

/******************************************************************************
* Description:                                                                *
*                                                                             *
* SY_RamCtlInit(void)                                                         *
*                                                                             *
* system RAM valuables initialize                                             *
*                                                                             * 
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
void SY_RamCtlInit(void)
{
 SY_uc_StatusRAMStack = 0;
 SY_uc_BitRamCtl = 0x22;
 SY_ui_ByteRamCtlKey = 0x55AA;
 SY_ui_ByteRamCtlTM = 0x55AA;
 SY_ui_RamCtrlCHKSUM = 0xAA55- SY_RamCtl_Calc(); 
}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* SY_RamCtlUpdate(void)                                                       *
*                                                                             *
* system RAM valuables update                                                 *
*                                                                             * 
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/

void SY_RamCtlUpdate(void)
{
  T_UWORD SY_ui_tempram;
  SY_uc_BitRamCtl++;
  SY_ui_ByteRamCtlTM++;

  SY_ui_tempram=(T_UWORD)(0xAA55 - SY_RamCtl_Calc());

	SY_ui_RamCtrlCHKSUM = SY_ui_RamCtrlCHKSUM + SY_ui_tempram;
}

/******************************************************************************
* Description:                                                                *
*                                                                             *
* SY_RamCtlCheck(void)                                                        *
*                                                                             *
* system RAM valuables check                                                  *
*                                                                             * 
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
void SY_RamCtlCheck(void)
{
 if(( SY_ui_ByteRamCtlKey!=0x55AA)||(SY_RamCtl_Calc()!=0xAA55))
 {
   
   //SY_bi_RamCtl_err = TRUE;
   SY_uc_StatusRAMStack |=0x05;
 }
 else   SY_uc_StatusRAMStack &=0xFA;//SY_bi_RamCtl_err = FALSE;
}

/******************************************************************************
* Description:                                                                *
*                                                                             *
* SY_StackCtrlCheck(void)                                                     *
*                                                                             *
* system Stack check                                                          *
*                                                                             * 
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/


