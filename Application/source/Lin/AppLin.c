/*
 * Lin.c
 *
 *  Created on: 2021$BG/(B3$B7n(B26$BF|(B
 *      Author: shenh4
 */
#include "Typedef.h"
#include <EcumTask.h>
#include "Debug.h"
#include "xl_gpio.h"
#include "xl_sim.h"
#include "xl_nvic.h"
#include "LinDcm.h"
#include "lin.h"
#include "AppLin.h"
#include "appl_const.h"
#define LIN_DIAG_NAD_INIT   0x0B
#define LIN_doortype_default 0x20

const uint8_t lin_pid_cfg[4] = {0x8,0x9,0x17,0x18};

void Task_Lin_Handler(){
	EcumState_t state;

	state = ECUM_STATE_GET;
	//Debug("Lin entered %u\n",s_uLinTaskCount++);
	DcmMainFunction();
}

/*
 *  NAD and PID init 初始化NAD和PID
 */
static void lin_nad_pid_init(void)
{
    lin_configured_NAD = LIN_DIAG_NAD_INIT;
    // 将lin_configured_NAD设置为预定义的初始诊断NAD值。

    if(c_ee_Par_DoorType >= LIN_doortype_default)
    {
    	lin_configuration_RAM[2] = lin_pid_cfg[c_ee_Par_DoorType - LIN_doortype_default];
    	// 根据门类型（c_ee_Par_DoorType）的值，从lin_pid_cfg数组中选择一个PID，并将其存储在lin_configuration_RAM的第2个索引位置。
    	if (c_ee_Par_DoorType >= LIN_doortype_default + 2)
    	{
    		lin_configuration_RAM[1] = 0x16;
    		// 如果门类型的值大于或等于默认门类型值加2，则将lin_configuration_RAM的第1个索引位置设置为0x16。
    	}
    }
}






void lin_stack_init(void)
{
#ifdef SIMDATA_OUT   // 如果定义了SIMDATA_OUT,则执行下面代码

	SIM_SCGC_Cmd(SIM_SCGC_UART0,DISABLE); // 先关闭UART0时钟
	NVIC_InitTypeDef NVIC_InitStructure;
	UART_InitTypeDef UART_InitStructure;
	SIM_SCGC_Cmd(SIM_SCGC_UART0,ENABLE); // 再打开UART0时钟

	/* UART0_PIN_SEL */
    // 配置UART0使用PTA2和PTA3引脚
    SIM_PINSEL_UART0(UART0_PS_PTA2_PTA3);

    // 使能LIN收发器
    GPIO_SetPin(GPIO_PTD2);

    // 设置LIN收发器使能引脚为输出
    GPIO_SetPinDir(GPIO_PTD2,GPIO_Direction_Output);

	UART_InitStructure.UART_SourceClk = Get_PeripheralClock(); // 获取外设时钟
	UART_InitStructure.UART_BaudRate = 38400;		// 设置波特率为38400
	UART_InitStructure.UART_DataLength = UART_DataLength_8b; // 数据长度8位
	UART_InitStructure.UART_StopBits = UART_StopBits_1; // 1位停止位
	UART_InitStructure.UART_Parity = UART_Parity_No; // 无校验位
	UART_Init(UART0, &UART_InitStructure); // 初始化UART0

	NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn; // 配置UART0中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	UART_EnableCmd(UART0, ENABLE); // 使能UART0
#else
    /* UART0_PIN_SEL */
    SIM_PINSEL_UART0(UART0_PS_PTA2_PTA3);// 配置UART0使用PTA2和PTA3引脚
    /*enable Lin transceiverv */
    GPIO_SetPin(GPIO_PTD2);// 使能LIN收发器
    /* set Lin transceiverv enable pin*/
    GPIO_SetPinDir(GPIO_PTD2, GPIO_Direction_Output);// 设置LIN收发器使能引脚为输出

    /*NAD and PID init*/
    lin_nad_pid_init();// 初始化网络地址和协议标识符

    /*timeout timer FTM2 */
    (void)l_sys_init();// 系统初始化

    /*uart 0 parameter */
    (void)l_ifc_init(LI0);// LIN接口初始化

    /*init transport layer */
    ld_init();// 传输层初始化

    /*DCM init*/
    DcmInit();// 诊断通信管理初始化
#endif
    /*uart0 interrupt enable*/
    //NVIC_Configuration_Uart0();
}

uint8_t lin_network_sleep_state_get(void)
{
    uint8_t uStatue;
    uint8_t rt = FALSE;

    uStatue = lin_lld_get_state();

    if(uStatue == SLEEP_MODE)
    {
        rt = TRUE;
    }

    return rt;
}

/*
 *  LIN0 hardware init
 */

//Added by HaiH
#ifdef SIMDATA_OUT
volatile uint8_t *ptr_g;                       //global pointer to data
volatile uint8_t packet_lenght=0;

void SCI0_Send_Packet(uint8_t *ptr, uint8_t length)
{

  ptr_g = ptr;
  packet_lenght = length;
  UART_EnableInterruptCmd(UART0, UART_THoldingEmptyIntEN, ENABLE);               //TDRE interrupt requests enabled
}

/**
 * @brief $BCfCG2s(B?$BH!?t(B
 * @retval None
 */
void UARTR_CallBack(UART_Type* UARTx)
{
	uint8_t temp;
	if(UART_GetLineStatus(UARTx, UART_LSRTHREmpty))
	{

		temp = *ptr_g;                           //Send data
	    UART_SendData(UARTx, temp);
	    ptr_g++;
	    packet_lenght--;

		if (packet_lenght == 0)                     //end of packet detection
		{
			UART_EnableInterruptCmd(UART0, UART_THoldingEmptyIntEN, DISABLE);                   //TDRE interrupt requests disabled
		}


	}
}


/**
 * @brief $BCfCG(B?$BM}H!?t(B
 * @retval None
 */
void UART0_IRQHandler(void)
{
	UARTR_CallBack(UART0);
}

#endif


