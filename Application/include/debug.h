#ifndef DEBUG_H_
#define DEBUG_H_

#include "XL6600.h"
#include "xl_uart.h"

#if (defined (__GNUC__) && defined(TRACE))
	#include "Trace.h"
#endif

//#define USER_DEBUG        /*open this macro will affect LIN communication, because that USER_DEBUG print data by swd communication*/

#ifdef  USER_DEBUG
	#if defined (__GNUC__)
		#if defined(TRACE)
			//#define Debug(expr ...)   trace_printf(expr)
			#define Debug(format,...)   trace_printf(format,##__VA_ARGS__)
		#else
			#define Debug(format,...)  printf(format,##__VA_ARGS__)
		#endif
	#else
		#define Debug(format,...)  printf(format,##__VA_ARGS__)
	#endif
#else
	#define Debug(format,...)
#endif

void XL6600_UartDebug_Config(UART_Type *UARTx);

#endif



