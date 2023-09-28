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
 *  NAD and PID init ��ʼ��NAD��PID
 */
static void lin_nad_pid_init(void)
{
    lin_configured_NAD = LIN_DIAG_NAD_INIT;
    // ��lin_configured_NAD����ΪԤ����ĳ�ʼ���NADֵ��

    if(c_ee_Par_DoorType >= LIN_doortype_default)
    {
    	lin_configuration_RAM[2] = lin_pid_cfg[c_ee_Par_DoorType - LIN_doortype_default];
    	// ���������ͣ�c_ee_Par_DoorType����ֵ����lin_pid_cfg������ѡ��һ��PID��������洢��lin_configuration_RAM�ĵ�2������λ�á�
    	if (c_ee_Par_DoorType >= LIN_doortype_default + 2)
    	{
    		lin_configuration_RAM[1] = 0x16;
    		// ��������͵�ֵ���ڻ����Ĭ��������ֵ��2����lin_configuration_RAM�ĵ�1������λ������Ϊ0x16��
    	}
    }
}






void lin_stack_init(void)
{
#ifdef SIMDATA_OUT   // ���������SIMDATA_OUT,��ִ���������

	SIM_SCGC_Cmd(SIM_SCGC_UART0,DISABLE); // �ȹر�UART0ʱ��
	NVIC_InitTypeDef NVIC_InitStructure;
	UART_InitTypeDef UART_InitStructure;
	SIM_SCGC_Cmd(SIM_SCGC_UART0,ENABLE); // �ٴ�UART0ʱ��

	/* UART0_PIN_SEL */
    // ����UART0ʹ��PTA2��PTA3����
    SIM_PINSEL_UART0(UART0_PS_PTA2_PTA3);

    // ʹ��LIN�շ���
    GPIO_SetPin(GPIO_PTD2);

    // ����LIN�շ���ʹ������Ϊ���
    GPIO_SetPinDir(GPIO_PTD2,GPIO_Direction_Output);

	UART_InitStructure.UART_SourceClk = Get_PeripheralClock(); // ��ȡ����ʱ��
	UART_InitStructure.UART_BaudRate = 38400;		// ���ò�����Ϊ38400
	UART_InitStructure.UART_DataLength = UART_DataLength_8b; // ���ݳ���8λ
	UART_InitStructure.UART_StopBits = UART_StopBits_1; // 1λֹͣλ
	UART_InitStructure.UART_Parity = UART_Parity_No; // ��У��λ
	UART_Init(UART0, &UART_InitStructure); // ��ʼ��UART0

	NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn; // ����UART0�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	UART_EnableCmd(UART0, ENABLE); // ʹ��UART0
#else
    /* UART0_PIN_SEL */
    SIM_PINSEL_UART0(UART0_PS_PTA2_PTA3);// ����UART0ʹ��PTA2��PTA3����
    /*enable Lin transceiverv */
    GPIO_SetPin(GPIO_PTD2);// ʹ��LIN�շ���
    /* set Lin transceiverv enable pin*/
    GPIO_SetPinDir(GPIO_PTD2, GPIO_Direction_Output);// ����LIN�շ���ʹ������Ϊ���

    /*NAD and PID init*/
    lin_nad_pid_init();// ��ʼ�������ַ��Э���ʶ��

    /*timeout timer FTM2 */
    (void)l_sys_init();// ϵͳ��ʼ��

    /*uart 0 parameter */
    (void)l_ifc_init(LI0);// LIN�ӿڳ�ʼ��

    /*init transport layer */
    ld_init();// ������ʼ��

    /*DCM init*/
    DcmInit();// ���ͨ�Ź����ʼ��
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


