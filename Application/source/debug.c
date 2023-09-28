#include "debug.h"
#include "xl_nvic.h"
#include "xl_sim.h"
#include "system_xl6600.h"
#include <stdio.h>

/**
* @brief 定义Debug端口
*/
UART_Type *Debug_Port;

/**
  * @brief  Debug端口配置
  * @param  UARTx: 选择UART外设
	*		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval None
  */
void XL6600_UartDebug_Config(UART_Type *UARTx)
{	
	#if (defined (__GNUC__) && defined(TRACE))
		return;
	#else
	UART_InitTypeDef UART_InitStructure;

	if(UARTx == UART0)
	{
		Debug_Port = UART0;
		SIM_SCGC_Cmd(SIM_SCGC_UART0,ENABLE);
	}
	else if(UARTx == UART1)
	{
		Debug_Port = UART1;
		SIM_SCGC_Cmd(SIM_SCGC_UART1,ENABLE);
	}
	else if(UARTx == UART2)
	{
		Debug_Port = UART2;
		SIM_SCGC_Cmd(SIM_SCGC_UART2,ENABLE);
	}
	
	UART_InitStructure.UART_SourceClk= Get_PeripheralClock();
	UART_InitStructure.UART_BaudRate = 115200;
	UART_InitStructure.UART_DataLength = UART_DataLength_8b;
	UART_InitStructure.UART_StopBits = UART_StopBits_1;
	UART_InitStructure.UART_Parity = UART_Parity_No;
	
	UART_Init(UARTx, &UART_InitStructure);
	UART_EnableCmd(UARTx, ENABLE);
	#endif
}

#if defined(__GNUC__)
	#ifndef TRACE
		/**
		  * @brief  重定向printf()的输入
		  */
		int _write(int fd, char *ptr, int len)
		{
			int i = 0;
		
			if(fd > 2)
				return -1;
			while(i < len)
			{
				while(!UART_GetLineStatus(Debug_Port,UART_LSRTHREmpty));
				UART_SendData(Debug_Port, (uint8_t) *ptr++);
				i++;
			}
			return i;
		}
	#endif
#elif defined(__ARMCC_VERSION) || defined(__CWCC__) || defined(__IAR_SYSTEMS_ICC__)
    /**
      * @brief  重定向printf()的输出
      */
    int fputc(int ch, FILE *f)
    {
    	while(!UART_GetLineStatus(Debug_Port,UART_LSRTHREmpty));
    	UART_SendData(Debug_Port, (uint8_t) ch);
    	return ch;
    }
    /**
      * @brief  重定向printf()的输入
      */
    int fgetc(FILE *f)
    {
    	return (int)UART_ReceiveData(Debug_Port);
    }

#else
  #error Not supported compiler type
#endif






