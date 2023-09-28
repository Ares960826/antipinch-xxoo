/*
 * TestMode.h
 *
 *  Created on: 2021年10月28日
 *      Author: huangh
 */

#ifndef _TESTMODE_H_
#define _TESTMODE_H_
#include "XL6600.h"


 #define   MCR_DELAY_NOP9    __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \
                             __NOP(); \

extern void specialmode_entry(void);

extern volatile uint16_t  TM_ui_TestTimeCnt;

extern volatile T_FLAG8  TM_T8_Flag1;

#define TM_T8_TestStatusFlag        TM_T8_Flag1.by
#define TM_bi_HWEntryAccess         TM_T8_Flag1.Bits.Bit0       /*满足工厂模式入口的初始硬件条件 ：up&&down both low level*/
#define TM_bi_beingTestMode         TM_T8_Flag1.Bits.Bit1       /*测试模式*/

#define C_ui_TM_HALL_TIMEOUT      100 //100*10ms=1S



void TM_init(void);

void TM_Entry(void);

void TM_Progress(void);

extern volatile T_FLAG8  RT_T8_statusflag;        /*status flag*/
#define RT_bi_a_connect_pre          RT_T8_statusflag.Bits.Bit0 /*copy relay A connect flag*/
#define RT_bi_b_connect_pre          RT_T8_statusflag.Bits.Bit1 /*copy relay B connect flag*/
#define RT_bi_a_break_pre            RT_T8_statusflag.Bits.Bit2 /*copy relay A break flag*/
#define RT_bi_b_break_pre            RT_T8_statusflag.Bits.Bit3 /*copy relay B break flag*/
#define RT_bi_functest_f             RT_T8_statusflag.Bits.Bit4 /*fuction test flag*/

extern uint8_t  RT_uc_a_connect_FLAG;    /*relay A connect flag*/
extern uint8_t  RT_uc_b_connect_FLAG;	 /*relay B connect flag*/
extern uint8_t  RT_uc_a_break_FLAG ;     /*relay A stop flag*/
extern uint8_t  RT_uc_b_break_FLAG ;    /*relay B stop flag*/

extern uint8_t RT_uc_a_connect_time;  /*relay A connect time*/
extern uint8_t RT_uc_b_connect_time;  /*relay B connect time*/
extern uint8_t RT_uc_a_connectCnt;    /*relay A connect time count */
extern uint8_t RT_uc_b_connectCnt;    /*relay B connect time count */
extern uint8_t RT_uc_a_break_time;    /*relay A break  time*/
extern uint8_t RT_uc_b_break_time;    /*relay B break time*/
extern uint8_t RT_uc_a_breakCnt;      /*relay A break time count */
extern uint8_t RT_uc_b_breakCnt;      /*relay B break time count */
extern uint8_t   RT_uc_DCMBuf[10]  ;
extern uint16_t RT_ui_HALLCNT;

extern void RT_init(void);
extern uint8_t RT_relaycheck(uint8_t relay_fd,uint8_t r_flag,uint8_t* r_cnt,uint8_t *r_value);
extern void RT_relaytest(void);
extern void  RT_HallDataLoad(void);
extern void  RT_OtherTestDataLoad(void);
extern void  RT_OtherTestDataLoad_2(void);
extern void   RT_ClearBUF(void);

extern bool_t TM_GetTMStatus(void);

#endif /* _TESTMODE_H_ */
