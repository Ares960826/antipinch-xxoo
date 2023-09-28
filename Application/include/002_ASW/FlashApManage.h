/*
 * FlashApManage.h
 *
 *  Created on: 2021Äê5ÔÂ7ÈÕ
 *      Author: lih
 */

#ifndef APPLICATION_INCLUDE_002_ASW_FLASHAPMANAGE_H_
#define APPLICATION_INCLUDE_002_ASW_FLASHAPMANAGE_H_

/**                      Public Function Declarations                         **
*******************************************************************************/
#include "Hallpos.h"
#include "Ubat.h"
#include "motor.h"
#include "aplib.h"

#define SIZE_DymAPDATA          sizeof(HP_Save_t)+sizeof(BAT_Save_t)+sizeof(MOT_Save_t)+sizeof(APL_Save_t) // keyport
#define Cells_DymAPDATA         (uint8_t)((SIZE_DymAPDATA+7)/8) *8



extern uint8_t FlashAp_DataBuf[Cells_DymAPDATA];

extern void  FlashAP_Init(void);
extern uint8_t Flash_ReadApData(uint8_t DataID, uint8_t* Data_Buff);
extern void  FlashAP_Initiate_Save(void);
extern uint8_t  FlashAP_fct_Chk_WrtState(void);
extern uint8_t  FlashAP_fct_Chk_WrtEnable(void);
extern void FlashAP_task_WriteApData(void);

extern void FlashAp_ReadWriteTest(void);



#endif /* APPLICATION_INCLUDE_002_ASW_FLASHAPMANAGE_H_ */
