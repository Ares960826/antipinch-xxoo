
#ifndef SYST_SECURITY_H                               /* To avoid double inclusion */
#define SYST_SECURITY_H

#include "Typedef.h"
#include "complier_sw.h"
#define SY_CON_SW_INVALID 25 //50ms =25*2

extern _Init_SAVE_RAM   volatile uint8_t  SY_uc_StatusRAMStack;

extern  volatile uint8_t  SY_uc_sleep;
extern  volatile uint8_t  SY_uc_poweron_sw;

//extern volatile T_FLAG8  SY_T8_StatusFlag;
//#define SY_bi_RamCtl_err           SY_T8_StatusFlag.bi.bit0 /*Ram err flag*/
//#define SY_bi_Stack_err            SY_T8_StatusFlag.bi.bit1 /*stack err flag*/

//#define SY_bi_sleep                SY_T8_StatusFlag.bi.bit7 /* flag*/   

extern uint16_t SY_RamCtl_Calc(void);
extern void SY_RamCtlUpdate(void);
extern void SY_RamCtlCheck(void);
extern void SY_RamCtlInit(void);
extern void SY_StackCtrlCheck(void);

#endif
