
#include "lowpower.h"
#include "xl_flash.h"
#include "xl_gpio.h"
#include "xl_sim.h"
#include "xl_nvic.h"
#include "xl_pmc.h"
#include "xl_ics.h"
#include "system_XL6600.h"
#include "xl_irq.h"
#include "xl_osc.h"
#include "xl_ftm.h"
#include "lin.h"
#include "Mcu.h"
#include "syst_security.h"
#include "AppIF.h"
#define LP_CON_Wait_sts 0x33
uint8_t Lowpower_uc_sleep;

extern void window_stop(void);
void Lowpower_setSleepSts(void)
{
	Lowpower_uc_sleep=LP_CON_Wait_sts;
}
void Lowpower_ClearSleepSts(void)
{
	Lowpower_uc_sleep=0;
}
//debug code
#if 0
void Enter_Sleep(void)
{
	//close IO
	//GPIOA{ PTD7~PTD0 : 31~24 }
	//GPIOA{ PTC7~PTC0 : 23~16 }
	//GPIOA{ PTB7~PTB0 : 15~8  }
	//GPIOA{ PTA7~PTA0 :  7~0  }
	//ToDo will modify the LinEn & PTB0 here
	GPIOA->PIDR = 0xFFFFFCFF;
	//GPIOB{ PTH7~PTH0 : 31~24 }
	//GPIOB{ PTG7~PTG0 : 23~16 }
	//GPIOB{ PTF7~PTF0 : 15~8  }
	//GPIOB{ PTE7~PTE0 :  7~0  }
	GPIOB->PIDR = 0xFFFFFFFF;
	//GPIOC{ Res~Res   : 31~24 }
	//GPIOC{ Res~Res   : 23~16 }
	//GPIOC{ Res~Res   : 15~8  }
	//GPIOC{ PTI7~PTI0 :  7~0  }
	GPIOC->PIDR = 0xFFFFFFFF;

	//close wodg(has been turned off by WDOG setting:WDOG_WAITEn = DISABLE)
	//SIM->SCGC &= ~SIM_SCGC_WDG_MASK

	//FLASH sleep when enter wait mode,so do nothing
	//FLASH_SleepInStopCmd(ENABLE);

	//Disable LVD Detect(not need)
	//PMC->SPMSC &= (~0x1C);

	//config enter deepsleep or sleep,so do nothing
	//NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE)

	//SWD
	//Step 1:debugSW
	//disable debugSW(not need in wait  mode)
	//SIM->SOPT0 &= (~0x0008);
	//due to debugSW is fixed(PTA4:SWD_DIO & PTC4:SWD_CLK)
	//GPIO_SetPinDir(GPIO_PTA4,GPIO_Direction_Output);
	//GPIO_ClrPin(GPIO_PTA4);
	//GPIO_SetPinDir(GPIO_PTC4,GPIO_Direction_Output);
	//GPIO_ClrPin(GPIO_PTC4);

	//SIM configure
	//must enable the sysclock:IRQ clock
	SIM->SCGC &= SIM_SCGC_IRQ_MASK;
	//disable all the other APBClock(FTM/RTC/ADC)
	SIM->SCGC1 = 0;
	//powerdown the sram(in wait mode , no nothing)
	//55aa -> Write Vaild
	//3008
	//  13bit:1    -> SRAM PowerOn
	//  12bit:1    -> Flash PowerOn
	//11~9bit:0    -> StopMode SRAM->PowerUp
	// 7~5bit:0    -> RunMode SRAM->PowerUp
	//   3bit:1    -> StopMode flash->PowerDown
	//   2bit:0    -> RunMode flash->PowerUp
	//SIM->LP = 0x55aa3008;

	//clear all the IRQFLag
	//PTB0
	IRQ_ClrFlag(IRQ,EXTI8);
	//PTB1
	IRQ_ClrFlag(IRQ,EXTI9);

	//FLL is bypass and IRC is system clock now(Wait mode not turn off the clock,so do nothing)
	//ICS_ClocksSelect(ICS_CLOCKS_IRC);
	//stop mode cant use ICS(wait mode , so do nothing)
	//ICS_IREFStopEnableCmd(ENABLE);

	//if needed , close the osc -> not need

	__asm("WFI");
}
#endif

//鐩墠閲囩敤enter_stop杩涘叆浼戠湢
void Enter_Stop(void)
{

	__disable_irq();
	Lowpower_setSleepSts();
    //close wodg(has been turned off by WDOG setting:WDOG_WAITEn = DISABLE)
    SIM->SCGC &= ~SIM_SCGC_WDG_MASK;

    //IRQ configuration
    IRQ_Configuration();

    //disable uart0
    lin_lld_deinit();

//    SIM->SCGC &= ~(SIM_SCGC_UART0|SIM_SCGC_ADC); /* disable Clock for UART0/ADC */
//
//    SIM->SCGC1 &= ~SIM_SCGC1_FTM0T;/* disable Clock for FTM0 */
//    SIM->SCGC1 &= ~SIM_SCGC1_FTM1T;/* disable Clock for FTM1 */
//    SIM->SCGC1 &= ~SIM_SCGC1_FTM2T;/* disable Clock for FTM2 */
//    SIM->SCGC &= ~SIM_SCGC_FTM2; /* disable Clock for FTM2 */
//    SIM->SCGC &= ~SIM_SCGC_FTM1; /* disable Clock for FTM1 */
//    SIM->SCGC &= ~SIM_SCGC_FTM0; /* disable Clock for FTM0 */
    //close interrupt
    FTM_ClrChannelFlag(FTM1,FTM_CHANNEL0);
    //FTM1 channel0 Enable the Interrupt Signal
    FTM_ChannelIntCmd(FTM1,FTM_CHANNEL0,DISABLE);
    //OS interrupt
    //SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk ; //?濮嬪�掓暟
    //SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    // clear FTM2 overflow flag
    FTM_ClrOverFlowFlag(FTM2);     		//20210807
    //close interrupt
    FTM_OverflowITCmd(FTM2 ,DISABLE);   //20210807

    //ADC Interrupt(disable)
    ADC_InterruptEn(ADC0,DISABLE);
    //end of close interrupt
    //close IO
    //GPIOA{ PTD7~PTD0 : 31~24 }
    //GPIOA{ PTC7~PTC0 : 23~16 }
    //GPIOA{ PTB7~PTB0 : 15~8  }
    //GPIOA{ PTA7~PTA0 :  7~0  }
    //ToDo will modify the LinEn & PTB0 here
    GPIOA->PIDR = 0xFFFFFEFB;
    //GPIOB{ PTH7~PTH0 : 31~24 }
    //GPIOB{ PTG7~PTG0 : 23~16 }
    //GPIOB{ PTF7~PTF0 : 15~8  }
    //GPIOB{ PTE7~PTE0 :  7~0  }
    GPIOB->PIDR = 0xFFFFFFFF;
    //GPIOC{ Res~Res   : 31~24 }
    //GPIOC{ Res~Res   : 23~16 }0xFFFFFFFB
    //GPIOC{ Res~Res   : 15~8  }
    //GPIOC{ PTI7~PTI0 :  7~0  }
    GPIOC->PIDR = 0xFFFFFFFF;

    //disable the POWER_EN
    GPIO_ClrPin(GPIO_PTD1);

    //disable the LIN_EN
    GPIO_ClrPin(GPIO_PTD2);

    //set high level ;SBC into silent mode
    GPIO_SetPin(GPIO_PTA3);

    //disable the RELAY_UP
    GPIO_ClrPin(GPIO_PTE1);
    //disable the RELAY_DOWN
    GPIO_ClrPin(GPIO_PTE0);

    //set GPIO direction
    GPIO_SetPinDir(GPIO_PTC3,GPIO_Direction_Input);//up_feedback
    GPIO_SetPinDir(GPIO_PTC2,GPIO_Direction_Input);//down_feedback
    GPIO_SetPinDir(GPIO_PTB0,GPIO_Direction_Input);//ENABLE
    GPIO_SetPinDir(GPIO_PTC0,GPIO_Direction_Input);//BATT_AD
    GPIO_SetPinDir(GPIO_PTD1,GPIO_Direction_Output);//POWER_DET_EN
    GPIO_SetPinDir(GPIO_PTD2,GPIO_Direction_Output);//LIN_EN
    GPIO_SetPinDir(GPIO_PTA3,GPIO_Direction_Output);//LIN_TX
    GPIO_SetPinDir(GPIO_PTE0,GPIO_Direction_Output);//DOWN_RELAY_DRIVE
    GPIO_SetPinDir(GPIO_PTE1,GPIO_Direction_Output);//UP_RELAY_DRIVE



    //close wodg(has been turned off by WDOG setting:WDOG_WAITEn = DISABLE)
   // SIM->SCGC &= ~SIM_SCGC_WDG_MASK;

    //FLASH sleep when enter wait mode,so do nothing
    FLASH_SleepInStopCmd(ENABLE);

    //Disable LVD Detect(not need)
    PMC->SPMSC &= (~0x1C);

    //config enter deepsleep or sleep,so do nothing
    NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);
    IRQ_PinEnableCmd(IRQ, EXTI2, ENABLE);
    //PTA2 need interrupt callback LIN WAKE
    IRQ_InterruptEn(IRQ, EXTI2, ENABLE);

    IRQ_PinEnableCmd(IRQ, EXTI8, ENABLE);
    //PTA2 need interrupt callback LIN WAKE
    IRQ_InterruptEn(IRQ, EXTI8, ENABLE);

#ifndef SDS//SLEEP_DISABLE_SWD
    //SWD   //not close debug pin
    //Step 1:debugSW
    //disable debugSW(not need in wait mode)
    SIM->SOPT0 &= (~0x0008);
    //due to debugSW is fixed(PTA4:SWD_DIO & PTC4:SWD_CLK)
    GPIO_SetPinDir(GPIO_PTA4,GPIO_Direction_Output);
    GPIO_ClrPin(GPIO_PTA4);
    GPIO_SetPinDir(GPIO_PTC4,GPIO_Direction_Output);
    GPIO_ClrPin(GPIO_PTC4);
#endif

    //SIM configure
    //must enable the sysclock:IRQ clock
    SIM->SCGC &= SIM_SCGC_IRQ_MASK;
    //disable all the other APBClock(FTM/RTC/ADC)
    SIM->SCGC1 = 0;
    //powerdown the sram(in wait mode , no nothing)
    //55aa -> Write Vaild
    //3008
    //  13bit:1    -> SRAM PowerOn
    //  12bit:1    -> Flash PowerOn
    //11~9bit:111  -> StopMode SRAM->PowerUp
    // 7~5bit:0    -> RunMode SRAM->PowerUp
    //   3bit:1    -> StopMode flash->PowerDown
    //   2bit:0    -> RunMode flash->PowerUp


    SIM->LP = 0x55aa3008;//stop mode flash power OFF(include ram and flash)

    //clear all the IRQFLag
    //PTB0
    IRQ_ClrFlag(IRQ,EXTI8);
    //PTB1
    IRQ_ClrFlag(IRQ,EXTI9);
    //start the watch dog
    WDOG_Configuration(WDOG_STAT_INIT);//2S
    //FLL is bypass and IRC is system clock now(Wait mode not turn off the clock,so do nothing)
    ICS_ClocksSelect(ICS_CLOCKS_IRC);
    ICS_IRCSelect(ICS_IRC_37o5K);

    SIM_CLKDIV_OUTDIV2(1u);//20210807 AFT  150k
    //stop mode cant use ICS(wait mode , so do nothing)
    ICS_IREFStopEnableCmd(ENABLE);
    ICS_FllStopModeCloseEnableCmd(ENABLE);
    //os systick disable
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk ; //寮�濮嬪�掓暟 //20210807

    //if needed , close the osc -> not need

    //enable LIN wakeup IRQ
    //PTA2 -> Interrupt(EXTI2)
    bsc_FeedCOP();
    __enable_irq();
    while(Lowpower_uc_sleep==LP_CON_Wait_sts)
	{

    	__NOP();
    	__NOP();
    	__NOP();
    	__NOP();
	  __asm("WFI");

	}
    __disable_irq();
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; //寮�濮嬪�掓暟
    bsc_FeedCOP();
    Lowpower_ClearSleepSts();
    Lin_appif_u16_IdleCnt=0;
    //check
    SY_RamCtlCheck();
	if((SY_uc_StatusRAMStack&0x05) >0)
	{
		window_stop();
		NVIC_SystemReset();
	}
	__enable_irq();

}


