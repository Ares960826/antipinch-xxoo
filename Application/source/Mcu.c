/*
 * Mcu.c
 *
 *  Created on: 2021年3月26日
 *      Author: shenh4
 */
#include <flash_eeprom.h>
#include "Mcu.h"
#include "xl_nvic.h"
#include "xl_gpio.h"
#include "xl_ics.h"
#include "xl_sim.h"
#include "xl_ftm.h"
#include "xl_adc.h"
#include "xl_irq.h"
#include "xl_wdog.h"
#include "xl_port.h"
#include "system_XL6600.h"
#include "Debug.h"
#include "AppLin.h"
#include "002_ASW\sub_task.h"

#include "Ubat.h"
#include "switch.h"
#include "motor.h"
#include "relay.h"
#include "hallpos.h"
#include "sysfunc.h"
#include "apfunc.h"
#include "aplib.h"
#include "thermo.h"

#include "AppIF.h"
#include "syst_security.h"
#include "FlashApManage.h"

void Mcu_Init() {
	//step 1:20210807 AFT
	//deinit it
	WDOG_DeInit(WDOG);
	WDOG_EnableCmd(WDOG, DISABLE);
	//disable the wdg clock by SIM module
	SIM_SCGC_Cmd(SIM_SCGC_WDG,DISABLE);	// SIM_SCGC_WDG=0x00000800u=2048
    //END 20210807 AFT
	//Clk Configuration
	CLOCK_Configuration();
	//WDOG Configuration
	WDOG_Configuration(WDOG_STAT_INIT);
	//NVIC Configuration
	NVIC_Configuration();	// (1-50)3.3.2 可嵌套向量的中断控制器(NVIC)配置
	//ADC Configuration
	ADC_Configuration(ADC0);
	//IRQ Configuration IRQ
	IRQ_Configuration();
	//Flash Configuration
	//	FLASH_Configuration();


	//Module
	//ModuleSBC
	Configure_SBCModule();
	//ModuleRelay	继电器
	Configure_RelayModule();
	//ModuleHall
	Configure_HallSensorModule();
	//ModuleMainConnector
	Configure_MainConnectorModule();
	//ModuleDebug
	//Configure_Debug();
	FlashAP_Init();
	//当上电状态为休眠唤醒时，从eeprom恢复保存数据?????ZAP
	// SY_RamCtlCheck();
	//if(1)
	if(/*((SY_uc_StatusRAMStack&0x05) >0) ||*/((bsc_Pmu_GetResetStatus() & 0x80) > 0))//power on reset
	{
		bsc_Pmu_ClrResetStatus();
		l_SetLinIdleCnt(AppLINIDLE_MAX-150U);
		SY_uc_poweron_sw=SY_CON_SW_INVALID;
		SY_uc_poweron = SY_CON_DATA;
		ini_adapt(); 					//CHANGE TO POR ZAP 20210706
		HallPosData.u16_WinPos = 0;		//CHANGE TO POR
		HallPosData.u16_WinPosI = 0;	//CHANGE TO POR
		HallPosData.u8_BlockUpCnt = 0;	//CHANGE TO POR
		HallPosData.u8_BlockDownCnt = 0;//CHANGE TO POR
		HallPosData.u16_SoftStopPos =0;	//CHANGE TO POR
		HallPosData.u8_SoftStopCnt=0;	//CHANGE TO POR
		HallPosData.Flg.Ubyte=0;		//CHANGE TO POR

		BatData.Flg.Bits.bl_LowVoltage = FALSE;//CHANGE TO POR
		BatData.Flg.Bits.bl_HighVoltage = FALSE;//CHANGE TO POR


		MotorData.Flg.Bits.bl_MotClose =FALSE;//CHANGE TO POR
		MotorData.Flg.Bits.bl_MotOpen =FALSE;//CHANGE TO POR
		MotorData.Flg.Bits.bl_MotPrvUp =FALSE;//CHANGE TO POR
		MotorData.Flg.Bits.bl_MotRun =FALSE;//CHANGE TO POR
		MotorData.Flg.Bits.bl_MotStop =TRUE;//CHANGE TO POR
		MotorData.Flg.Bits.bl_MotUp =FALSE;//CHANGE TO POR

		SY_RamCtlInit();//change to pOR
		SY_RamCtlUpdate();
	}
	else
	{
		l_SetLinIdleCnt(0);
		SY_uc_poweron= 0;
		//SYS_DataRestore();
	}
	//	FlashAp_ReadWriteTest();

	/*	PMU must be 1st Function	*/
#if 0
	bsc_PmuInit();
	bsc_ScuInit();
	bsc_MonInit();
	bsc_PortInit();
	bsc_IntInit();
	bsc_LsInit();
	bsc_ADC1Init();
	bsc_CCU6Init();
	bsc_LinInit();
	bsc_CCU6_StartTmr_T12();
	bsc_HsInit();
	bsc_ADC2Init();
	PIT_1MS_Init();
	Api_EepromInit();
#endif
}

void App_Init(void)
{
#if 1
	//Task_init();
	BAT_Init();
	APF_Init();
	SYS_Init();

	KeyPort_Init();
	MOT_Init();
	REL_Init();
	HP_Init();				// 霍尔
	APL_Init();				// 防夹
	//TP_Init();
	thermo_init();
	//hd_Init(); //???????ZAP
	//RT_init();
	//SY_RamCtlInit();//change to pOR

	//POWER_DET_EN
	bsc_HS_PowerPin1Op(1);
#endif
}

//Mcu Init/Deinit
volatile int exit_code = 0;
void Mcu_Deinit() {
    //ExitCode
    for(;;) {
      Debug("Main error\n");
      if(exit_code != 0) {
        break;
      }
    }
}


void CLOCK_Configuration() {
	//Init Clock
	SYS_CLK_STATUS ClkState = SYS_CLK_OK;	// SYS_CLK_OK=0
	ClkState=SystemSetFEI(ICS_IRC_50K, ICS_FLLFACTOR_1280);//64M
    if(ClkState != SYS_CLK_OK) //20210807 AFT
    {
    	NVIC_SystemReset();
    }
	//For debug only
	//XL6600_UartDebug_Config(UART2);
}

void ADC_Configuration(ADC_Type* ADCx){

	//Declare
	ADC_InitTypeDef ADC_InitStruct={0};
	ADC_FIFOTypeDef ADC_FIFOStruct={0};

	//Generate the ADC Clock
	SIM_SCGC_Cmd(SIM_SCGC_ADC, ENABLE);	// 使能之后才能够进行配置

	//According to the spec, 10Bit is enough
	ADC_InitStruct.ADC_Mode=ADC_MODE_10BIT;
	//BusClock: 32MHz
	ADC_InitStruct.ADC_ClockSource=ADC_CLOCK_BUS_CLOCK;
	//divide 4
	ADC_InitStruct.ADC_ClkDivide=ADC_ADIV_DIVIDE_4;
	//Max Voltage is VDDA(MCU)
	ADC_InitStruct.ADC_ReferVoltage=ADC_VREF_VDDA;
	//longTime Enable(?)
	ADC_InitStruct.ADC_LongTimeConvert=ENABLE;
	//LP don't need
	ADC_InitStruct.ADC_LowPowerConvert=DISABLE;
	//Init ADC0
	ADC_Init(ADC0, &ADC_InitStruct);

	//ADC Interrupt(enable)
	ADC_InterruptEn(ADC0, ENABLE);
	//software trigger(?)
	ADC_SetTriggerMode(ADC0,ADC_SOFTWARE_TRIGGER);
	//OneTime
	ADC_SetConventionMode(ADCx,ADC_CONVENTION_ONCE);
	//ADC_SetConventionMode(ADCx,ADC_CONVENTION_CONTINUOUS);

	//FIFO...
	//ADC_FIFOStruct.ADC_FIFOLevel=ADC_FIFO_DISABLE;
	ADC_FIFOStruct.ADC_FIFOLevel=ADC_FIFO_LEVEL7; //ADC_FIFO_LEVEL6;
	ADC_FIFOStruct.ADC_ChannelScan=ENABLE;
	ADC_FIFOConfig(ADC0, &ADC_FIFOStruct);

	//ADC0 enable
	ADC_EnableCmd(ADC0,ENABLE);
}

//NVIC
void NVIC_Configuration() {

	//NVIC init
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//IRQ0 SysTick SysTick 定时器
	NVIC_InitStructure.NVIC_IRQChannel = (uint8_t)SysTick_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);

	//IRQ1 ADC
	NVIC_InitStructure.NVIC_IRQChannel = (uint8_t)ADC0_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);

	//IRQ1 FTM1
	NVIC_InitStructure.NVIC_IRQChannel = FTM1_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);

    //PTA2 -> (IRQPS = 0 & EXIT2)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
    //子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    //使能中断
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_Init
    NVIC_Init(&NVIC_InitStructure);


	//IRQ3 PTB8
	//PTB8 -> (IRQPS = 0 & EXIT8)
	NVIC_InitStructure.NVIC_IRQChannel = EXTI8_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);


	//IRQ3 PTB8
	//PTB8 -> (IRQPS = 0 & EXIT8)
	NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);


#if DEBUG
	//IRQ3 PTB8
	//PTB8 -> (IRQPS = 0 & EXIT8)
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_IRQn;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;
	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init
	NVIC_Init(&NVIC_InitStructure);
#endif
}


/**
 * SIM_SCGC1_Cmd
 * @brief  系统时钟选通1
 * @param  SCGC_Type: 指定外设时钟使能状态
 *		这个参数可以为以下值:
 *			@arg SIM_SCGC1_FTM0F: 	FTM0选用ICSFFCLK时钟使能
 *			@arg SIM_SCGC1_FTM1F: 	FTM1选用ICSFFCLK时钟使能
 *			@arg SIM_SCGC1_FTM2F: 	FTM2选用ICSFFCLK时钟使能
 *			@arg SIM_SCGC1_RTCEC: 	RTC选用OSCERCLK时钟使能
 *			@arg SIM_SCGC1_ADCALTC: ADC选用ALTCLK时钟使能
 *			@arg SIM_SCGC1_FTM0T:  	FTM0选用TIMERCLK时钟使能
 *			@arg SIM_SCGC1_FTM1T:  	FTM1选用TIMERCLK时钟使能
 *			@arg SIM_SCGC1_FTM2T:  	FTM2选用TIMERCLK时钟使能
 *			@arg SIM_SCGC1_RTCLPOC: RTC选用LPOCLK时钟使能
 * @param  State: 选定指定的外设
 *		这个参数可以取下面的值:
 *			@arg ENABLE: 使能相应模块
 *			@arg DISABLE: 关闭相应模块
 * @retval None
 */

//FTM
void FTM1_Configuration()
{
	//FTM init
	FTM_InitTypeDef FTM_InitStructure;

	//set PTG7 -> FTM2CH5
	//SIM_PINSEL_FTM2CH5(FTM2CH5_PS_PTG7);
	//set PTH2 -> FTM1CH0
	SIM_PINSEL_FTM1CH0(FTM1CH0_PS_PTH2);
	//Enable the SCG Module
	SIM_SCGC_Cmd(SIM_SCGC_FTM1,ENABLE);

	//FTM1 Enable the TIMERCLK
	//FTM1T -> T:ISOUTCLK -> TIMER FTM/PWT Clock
	//FTM1F -> T:ICSFFCLK -> TCLK(External Clock)
	SIM_SCGC1_Cmd(SIM_SCGC1_FTM1T, ENABLE);

	//WP
	FTM_WriteProtectDisable(FTM1);

	//IMPORTANT !!!	MARK
	//target loopTime 2us
	//FTMtick = (10^6)/2 = 500000
	/* Set Prescale Factor */
	FTM_InitStructure.FTM_Prescaler = FTM_CLOCK_PS_DIV128;
	/* Set Clock Source */
	FTM_InitStructure.FTM_ClkSource = FTM_CLOCK_SYSTEMCLOCK;
	// After that -> 64M/128 = 500000(Times)  -> set ModValue (500000/10) = 100ms

	//due to inputCaptureMode -> ignore the Count
	//Set INIT value(1~x)
	//FTM_SetCountInitValue(FTM2 ,1);
	/*  Sets the FTM peripheral timer modulo value */
	//uint32_t uFreq = Get_SystemCoreClock()/128;
	//uFreq > 2^16 -> temp set (1/10)s
	//FTM_SetModValue(FTM2 , uFreq/10 );

	//bothEdge capture VIP
	FTM_InputCaptureInit(FTM1,FTM_CHANNEL0, FTM_INPUTCAPTURE_BOTHEDGE);
	//set ModeValue = Max -> reduce the overflow times/interrupts
	FTM_SetModValue(FTM1,0xFFFF);
	/*  Initializes the FTM module */
	FTM_Init(FTM1 ,&FTM_InitStructure);

	FTM_ClrChannelFlag(FTM1,FTM_CHANNEL0);
	//FTM1 channel0 Enable the Interrupt Signal
	FTM_ChannelIntCmd(FTM1,FTM_CHANNEL0,ENABLE);
	//DISABLE the overflow Tag
	FTM_OverflowITCmd(FTM1 ,DISABLE);
}
/**
 * IRQ_Configuration
 * @brief
 * 		(1-83)3.11.3 IRQ 配置
 * @param
 * @retval None
 */
//GPIO
void IRQ_Configuration()
{
	//Init in(EXTI2) IRQ
	IRQ_InitTypeDef IRQ_InitStruct;

	//ioflt0 -> div
	port_ioflt0_config sport_ioflt0_config = { 0 };
	//ioflt1 -> map into ioflt0
	port_ioflt1_config sport_ioflt1_config = { 0 };

	//busFreq = 32Mhz
	//after div -> ~32Khz -> ~125us/4
	//32us << lin(150us)
	sport_ioflt0_config.iofltdiv2 = Port_FLTDIV2SetBUSCLKDiv1024;
	PORT_IOFLT0Config(&sport_ioflt0_config);	// 将IO口滤波器分组2加入配置
	sport_ioflt1_config.iofltirq = Port_FLTIRQFLTDIV2;
	PORT_IOFLT1Config(&sport_ioflt1_config);

	//Enable EXTI IRQ
	SIM_SCGC_Cmd(SIM_SCGC_IRQ,ENABLE);
	//Use (PTA+PTB) -> Group1 External Interrupt
	SIM_PINSEL_IRQ(IRQ_PS_GROUP1);

	//Init Lin(EXTI2) IRQ
	/*这部分通过 IRQ_Init() 初始化外部中断*
	  * 通过三个参数控制:
	 * 	(1)IRQx: 选择IRQ外设
	 * 	(2)IRQ_Channel: 选择IRQ通道
	 * 	(3)IRQ_InitStuct: 指向包含指定IRQ外设配置信息的IRQ_InitTypeDef结构*/
	//low
	IRQ_InitStruct.IRQ_EdgeSelect = IRQ_Falledge_Lowlevel;
	//edge
	IRQ_InitStruct.IRQ_ModeSelect = IRQ_Detect_Edge;
	//-> low + edge
	IRQ_Init(IRQ, EXTI2, &IRQ_InitStruct);

	//PTA2 -> Interrupt(EXTI2)
	IRQ_PinEnableCmd(IRQ, EXTI2, DISABLE);
	//PTA2 need interrupt callback
	IRQ_InterruptEn(IRQ, EXTI2, DISABLE);
	//Chip PullUp Enable
	IRQ_PullDevDisableCmd(IRQ,EXTI2,ENABLE);

	IRQ_InitStruct.IRQ_EdgeSelect = IRQ_Falledge_Lowlevel;
	//edge
	IRQ_InitStruct.IRQ_ModeSelect = IRQ_Detect_Edge;

	IRQ_Init(IRQ, EXTI8, &IRQ_InitStruct);

	//PTB0 -> Interrupt(EXTI8)
	IRQ_PinEnableCmd(IRQ, EXTI8, DISABLE);
	//PTA2 need interrupt callback
	IRQ_InterruptEn(IRQ, EXTI8, DISABLE);
	//Chip PullUp Enable
	IRQ_PullDevDisableCmd(IRQ, EXTI8,DISABLE);
}

void FLASH_Configuration(){
	//call the flash init func
	EEFlash_Init();

	/*
    for(uint16_t uIndex = 0;uIndex < 10;++uIndex){
    	uint8_t udata = (3*uIndex);
    	Api_EepromWrite(uIndex,0,1,&udata);
    }
    */

	/*
    for(uint16_t uIndex = 0;uIndex < 10;++uIndex){
    	uint8_t udata = 0;
        Api_EepromRead(uIndex,0,1,&udata);
        uint8_t aaa = udata;
    }
    */
}

void LIN_Configuration(){
    lin_stack_init();
}

void WDOG_Configuration(WDOG_STATUS eStatus){
	//enable the wdg clock by SIM module
	SIM_SCGC_Cmd(SIM_SCGC_WDG, ENABLE);

	//step 1:
	//deinit it
	WDOG_DeInit(WDOG);
	WDOG_EnableCmd(WDOG, DISABLE);

	//step 2:
	//configure it
	WDOG_InitTypeDef WDOG_InitStructure;
	// 32KHZ
	WDOG_InitStructure.WDOG_ClkSource = WDOG_LPO_Clock;
	//WDOG_InitStructure.WDOG_ClkSource = WDOG_Bus_Clock;
	// kernal 32clock reset everlast time
	WDOG_InitStructure.WDOG_PulseLength = WDOG_PclkCycles_32;
	// Pre En = disable (/256 no need)
	WDOG_InitStructure.WDOG_PRESEn = DISABLE;
	// send the reset signal
	WDOG_InitStructure.WDOG_ResponseMode = WDOG_ResponseMode_Reset;
	// when debug mode , enable it
	WDOG_InitStructure.WDOG_DEBUGEn = DISABLE;
	// stop Mode -> enable
	WDOG_InitStructure.WDOG_STOPEn = DISABLE;
	// wait Mode -> enable
	WDOG_InitStructure.WDOG_WAITEn = DISABLE;
	// Init
	WDOG_Init(WDOG ,&WDOG_InitStructure);
	//when wdog is init status, make the time longer
	if(eStatus == WDOG_STAT_INIT){
		// (1/ 32k * 1000) = 0.03125ms -> 2048ms / 0.03125 = 65536 -> 2^16 -> x+4=16 -> x=12
		WDOG_SetTimeoutPeriod(WDOG ,12);
	}
	else {
		// (1/ 32k * 1000) = 0.03125ms ->64ms / 0.03125 = 2048 -> 2^11 -> x+4=10 -> x=7
		WDOG_SetTimeoutPeriod(WDOG ,7);
	}


	//step 3:
	WDOG_CountRestart(WDOG);
	WDOG_EnableCmd(WDOG, ENABLE);
}

//GPIO_SBC
void Configure_SBCModule(){

	//receive ~PG_RST(In) PTA5
	//Battery -> don't need
	//GPIO_SetPinDir(GPIO_PTA5,GPIO_Direction_Input);

	//set POWER_DET_EN PTD1
	GPIO_SetPinDir(GPIO_PTD1, GPIO_Direction_Output);
	//default lowLevel
	GPIO_ClrPin(GPIO_PTD1);

	//ADC BATT_AD PTC0->ADC0_SE8
	//ADC_Configuration(ADC0,ADC_CHANNEL_AD8,0);

	//receive LIN_TX PTA2
	//receive LIN_RX PTA3
	//set LIN_EN PTD2
	LIN_Configuration();
}

//Relay
void Configure_RelayModule(){

	//receive Up_DET_AD PTC3 -> ADC0_SE11
	//ADC_Configuration(ADC0,ADC_CHANNEL_AD11,0);
	//receive Down_DET_AD PTC2 -> ADC0_SE10
	//ADC_Configuration(ADC0,ADC_CHANNEL_AD10,0);

	//set Up_EN PTE1
	GPIO_SetPinDir(GPIO_PTE1, GPIO_Direction_Output);
	//default lowLevel
	GPIO_ClrPin(GPIO_PTE1);

	//set Down_EN PTE0
	GPIO_SetPinDir(GPIO_PTE0,GPIO_Direction_Output);
	//default lowLevel
	GPIO_ClrPin(GPIO_PTE0);
}

//HallSensor
void Configure_HallSensorModule(){
	//receive Hall_Speed PTH2
	//must call this before call FTM1_Configuration
	GPIO_SetPinDir(GPIO_PTH2,GPIO_Direction_Input);
	//receive Hall_Direction PTH2
	FTM1_Configuration();

	//receive Hall_DIR PTE7(For getting the GPIO input)
	GPIO_SetPinDir(GPIO_PTE7,GPIO_Direction_Input);
}

//GPIO_MainConnector
void Configure_MainConnectorModule(){

	//receive KEY_AD PTB2 -> ADC0_SE6
	//ADC_Configuration(ADC0,ADC_CHANNEL_AD10,0);


	//set Reserve_IN PTB1
	//GPIO_SetPinDir(GPIO_PTB1,GPIO_Direction_Input);
	//GPIO_SetPinDir(GPIO_PTB1,GPIO_Direction_Output);
	//default lowLevel
	//GPIO_ClrPin(GPIO_PTB1);


	//set Enable_IN PTB0
	GPIO_SetPinDir(GPIO_PTB0,GPIO_Direction_Input);

	//set Down_Reserve_IN PTA1 -> HSIS don't write it
	//GPIO_SetPinDir(GPIO_PTA7,GPIO_Direction_Output);
	//default lowLevel
	//GPIO_ClrPin(GPIO_PTA7);

}

//GPIO_MainConnector
void Configure_Debug(){
	//set SWD_CLK PTC4
	GPIO_SetPinDir(GPIO_PTC4,GPIO_Direction_Output);
	GPIO_ClrPin(GPIO_PTC4);

	//set SWD_DIO PTA4
	GPIO_SetPinDir(GPIO_PTA4,GPIO_Direction_Output);
	GPIO_ClrPin(GPIO_PTA4);
}
