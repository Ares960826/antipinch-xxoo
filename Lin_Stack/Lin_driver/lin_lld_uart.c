/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup UART_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      bsp/UART/lin_lld_UART.c
*
* @author    FPT Software
*
* @brief     UART for LIN network
*
******************************************************************************/

/******************************************************************************
 *
 * History:
 *
 * 20101027		v1.0	First version
 * 20111005		v1.1	Updated hardware support, multi timers
 *
 *****************************************************************************/

#include "lin_lld_uart.h"
#include "lin_hw_cfg.h"
#include "lin_common_proto.h"
#include "lin_lld_timesrv.h"
#include "lin_cfg.h"
#include "xl_sim.h"
#include "xl_nvic.h"
#include "xl_irq.h"

#define XL6600D_ADD
static void lin_wakeup_pin()
{
	IRQ_InitTypeDef IRQ_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	SIM_SCGC_Cmd(SIM_SCGC_IRQ,ENABLE);   /*irq clk enable*/
	SIM_PINSEL_IRQ(LIN_WAKEUP_IRQ_GROUP);	/*select irq group*/


	NVIC_InitStruct.NVIC_IRQChannel = LIN_WAKEUP_IRQ_N + 31;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);

	IRQ_InitStruct.IRQ_EdgeSelect = IRQ_Falledge_Lowlevel; /* IRQ is falling-edge or falling-edge/low-level sensitive. */
	IRQ_InitStruct.IRQ_ModeSelect = IRQ_Detect_Edge;/*IRQ event is detected only on falling/rising edges*/
	IRQ_Init(IRQ, LIN_WAKEUP_IRQ_N, &IRQ_InitStruct);

	IRQ_PullDevDisableCmd(IRQ,LIN_WAKEUP_IRQ_N,ENABLE);

	IRQ_PinEnableCmd(IRQ, LIN_WAKEUP_IRQ_N, ENABLE);
}

#if (LIN_MODE == _SLAVE_MODE_)

/***** Globle variable data *****/

/* pUART func ifc checksum_mode state  l_status cnt_byte  *ptr current_pid *response_buffer
  pid_out tbit frame_timeout_cnt res_frame_timeout_cnt idle_timeout_cnt */

/**
* @var static tUART *pUART
*/
static tUART          *pUART = (tUART*)UART_ADDR;

/**
* @var static l_u8          ifc
*/
static l_u8          ifc = 0xFF;

/**
* @var static l_u8          state
*/
static l_u8          state = UNINIT;

/**
* @var static lin_status    l_status
*/
static lin_status    l_status;

/**
* @var static l_u8          cnt_byte
*/
static l_u8          cnt_byte = 0;

/**
* @var static l_u8         *ptr
*/
static l_u8          *ptr = 0;

/**
* @var static l_u8          current_id
*/
static l_u8          current_id = 0x00;

/**
* @var static l_u8         *response_buffer
*/
static l_u8          *response_buffer = 0;

/**
* @var static l_u8          pid
*/
static l_u8          pid = 0x80;

/**
* @var static l_u16          tbit
*/
static l_u16         tbit = 0;

/**
* @var static l_u16          frame_timeout_cnt
*/
static l_u16         frame_timeout_cnt = 0;

/**
* @var static l_u16          res_frame_timeout_cnt
*/
static l_u16         res_frame_timeout_cnt = 0;

/**
* @var static l_u16          idle_timeout_cnt
*/
static l_u16         idle_timeout_cnt = 0;

l_u8 lin_master_request_sleep = 0u;



extern const l_u16 lin_max_frame_res_timeout_val[8];

extern l_u8 lin_lld_response_buffer[10];



/***** LOW-LEVEL API *****/

void lin_lld_uart_init
  (
    /* [IN] LIN interface name*/
    l_ifc_handle iii
  )
{

/*--------------------------------------------------------------------*/

  tU32 tmp;
  tU32 Fractional;
  tU08 temp1=0;
  /* Resyn initialization */
  /* Config */
  ifc=(l_u8)iii;
  response_buffer=lin_lld_response_buffer;
  /* Set UART is Master or Slave */
  tbit=(1000000/LIN_BAUD_RATE);
  /* Initialize UART */
  /* Set baud rate */
  tmp = MCU_BUS_FREQ/LIN_BAUD_RATE/16;
  //tmp = (MCU_BUS_FREQ/LIN_BAUD_RATE)>>4;
  if((tU32)pUART == UART0_ADDR){
 	  SIM->SCGC &= ~SIM_SCGC_UART0_MASK;
 	  SIM->SCGC |=  SIM_SCGC_UART0_MASK;
   }else if((tU32)pUART == UART1_ADDR){
 	  SIM->SCGC &= ~SIM_SCGC_UART1_MASK;
 	  SIM->SCGC |=  SIM_SCGC_UART1_MASK;
   }else if((tU32)pUART == UART2_ADDR){
 	  SIM->SCGC &= ~SIM_SCGC_UART2_MASK;
 	  SIM->SCGC |=  SIM_SCGC_UART2_MASK;
   }
    //20211116 for uart ini reset
  /*enable uart*/
     pUART->SGW |= UART_SGW_EN_MASK;
     while( ( (pUART->USR)&((uint32_t)0x01)) != 0u)
  	{
  	 temp1=pUART->RBR;
  	}
     pUART->SGW &= (~UART_SGW_EN_MASK);
    //endof 20211116 for uart ini reset
  /*unlock dll dlh*/
   pUART->LCR.bit.dlab = 1;
  Fractional =(((MCU_BUS_FREQ/16) - (LIN_BAUD_RATE * tmp))<<4u) / LIN_BAUD_RATE;
  pUART->DLH	= (tmp>>8)&0xFF;
   pUART->DLL = tmp & 0xFF;
   pUART->DLF	= Fractional;

  /* Enable use of 13bit breaks and UART frame for LIN */
   pUART->LCR.dword &= ~(UART_LCR_STOP_MASK);
   pUART->LCR.dword |= UART_LINBreakLength_13b | UART_LCR_DLS_MASK;    /* one start bit, eight data bits, one stop bit */
  /*enable rx tx*/
   pUART->LCR.bit.dlab = 0;
   /**disable fifo */
      pUART->FCR = 0;

  pUART->IER |= (UART_IER_ERBFI_MASK | UART_IER_ELSI_MASK);
  pUART->LSR; /* clear LIN Break Detection flag       */
 pUART->IIR;
  /*enable uart*/
   pUART->SGW |= UART_SGW_EN_MASK;
  /* Receive data not inverted */
   /*wake up config*/
   //lin_wakeup_pin();
  /* Enter IDLE state */
  lin_goto_idle_state();
} /* End of function lin_lld_uart_init( l_ifc_handle iii ) */
/*--------------------------------------------------------------------*/

void lin_lld_uart_deinit
  (
  )
{
  state=UNINIT;
  pUART->SGW &= ~UART_SGW_EN_MASK;
  lin_lld_uart_int_disable();
}


void lin_lld_uart_tx_wake_up
  (
  )
{
  l_u8 uart_flag_sr1;
  if((state == IDLE) || (state == SLEEP_MODE)) {
    uart_flag_sr1 = pUART->LSR & 0xff;
    /* Send wake signal byte=0x80 */
    pUART->THR = UARTTHR_WAKE_SIGNAL;
    /* Set Lin state to idle */
    lin_goto_idle_state();
  }
/*--------------------------------------------------------------------*/
} /* End function lin_lld_UART_tx_wake_up() */


void lin_lld_uart_int_enable
  (
  )
{
  /* Can't enable in interrupt context */
  if((state == PROC_CALLBACK) || (state==UNINIT) || (state==SLEEP_MODE)) return;

  /* Enable UART Channel*/
  pUART->SGW &= (~UART_SGW_TXDIR_MASK);
   pUART->IER |= UART_IER_ERBFI_MASK;
  /* Enable timeout interrupt 0 channel */


} /* End function lin_lld_UART_int_enable() */
/*--------------------------------------------------------------------*/

void lin_lld_uart_int_disable
  (
  )
{
/*--------------------------------------------------------------------*/
  /* Can't disable in interrupt context */
  if((state == PROC_CALLBACK) || (state==UNINIT) || (state==SLEEP_MODE)) return;

  while(state != IDLE) { }
  /* Disable UART Channel*/
  pUART->SGW |= UART_SGW_TXDIR_MASK;
  pUART->IER &= (~UART_IER_ERBFI_MASK);
  /* Disable timeout interrupt 0 channel */
} /* End function lin_lld_UART_int_disable() */


void lin_lld_uart_ignore_response
  (
  )
{
  lin_goto_idle_state();
}


void lin_lld_uart_set_low_power_mode
  (
  )
{
  /* Configure Hw code */
  //IRQ_InterruptEn(IRQ, LIN_WAKEUP_IRQ_N, ENABLE);
  /* Set Lin status = receiving data*/
  state=SLEEP_MODE;
}


void lin_lld_uart_rx_response
  (
    /* [IN] Length of response data expect to wait */
    l_u8  msg_length
  )
{
  /* Put response length and pointer of response buffer into descriptor */
  *(response_buffer)=msg_length;
  cnt_byte=0;
  ptr=response_buffer;
  /* Set Lin status = receiving data*/
  state=RECV_DATA;
}

void lin_lld_uart_tx_response
  (
  )
{
  /* calculate checksum */
  response_buffer[*(response_buffer)+1] = lin_checksum(response_buffer, pid);
  cnt_byte=1;
  /* Send First byte */
  pUART->THR = response_buffer[1];
  /* Set LIN Status */
  state = SEND_DATA;

/*--------------------------------------------------------------------*/
} /* End function lin_lld_UART_tx_response() */


l_u8 lin_lld_uart_get_status
  (
  )
{
  return l_status.byte;
}


l_u8 lin_lld_uart_get_state()
{
  return state;
}


void lin_lld_uart_timeout(void)
{
/* Multi frame support */
	/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
	if (LD_CHECK_N_CR_TIMEOUT == tl_check_timeout_type){
	   if(0 == --tl_check_timeout){
	     /* update status of transport layer */
	     tl_service_status = LD_SERVICE_ERROR;
	     tl_receive_msg_status = LD_N_CR_TIMEOUT;
	     tl_rx_msg_status = LD_N_CR_TIMEOUT;
	     tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
	     tl_diag_state = LD_DIAG_IDLE;
	   }
	}

	if (LD_CHECK_N_AS_TIMEOUT == tl_check_timeout_type){
	   if(0 == --tl_check_timeout){
	      /* update status of transport layer */
	     tl_service_status = LD_SERVICE_ERROR;
	     tl_tx_msg_status = LD_N_AS_TIMEOUT;
	     tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
	     tl_diag_state = LD_DIAG_IDLE;
	   }
	}
#endif /* END (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)  */
  switch(state) {
    case IDLE:
      if(idle_timeout_cnt==0) {
        /* Set LIN mode to sleep mode */
        lin_goto_sleep_flg = 1;
        /* trigger callback */
        CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_BUS_ACTIVITY_TIMEOUT, 0xFF);
        /* goback to IDLE, reset max idle timeout */
        idle_timeout_cnt=_MAX_IDLE_TIMEOUT_;
        /* disable LIN break detect interrupt */
        pUART->IER &= (~UART_IER_ELSI_MASK) ;
        /* Set state to sleep mode */
        state = SLEEP_MODE;
        /* set irq wake up*/
        //IRQ_InterruptEn(IRQ, LIN_WAKEUP_IRQ_N, ENABLE);//20210811 zap
      } else idle_timeout_cnt--;
      break;
    case SEND_PID:    /* Master */
    case RECV_SYN:
    case RECV_PID:
    case SEND_DATA:
    case SEND_DATA_COMPLETED:
      /* timeout send has occurred - change state of the node and inform core */
      if(0 == frame_timeout_cnt)
        lin_goto_idle_state();
      else frame_timeout_cnt--;
      break;
    case RECV_DATA:
      /* timeout receive has occurred - change state of the node and inform core */
      if(0 == res_frame_timeout_cnt) {
        if(cnt_byte){
          /* set lin status: error_in_response */
          l_status.byte |= LIN_STA_ERROR_RESP;
        /* trigger callback */
          CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_NODATA_TIMEOUT, current_id);
        }
        lin_goto_idle_state();
      } else res_frame_timeout_cnt--;
      break;
    case PROC_CALLBACK:
      break;
    default:
    ;
  }
} /* End function lin_lld_UART_timeout() */


/*** INTERNAL FUNTIONS ***/


void lin_goto_idle_state
  (
  )
{
  /* set lin status: ~bus_activity */
  l_status.byte &= ~LIN_STA_BUS_ACTIVITY;
  /* Set max idle timeout */
  idle_timeout_cnt=_MAX_IDLE_TIMEOUT_;
  state=IDLE;
  /* Enable LBK detect */
  pUART->IER |= UART_IER_ELSI_MASK ;
} /* End function lin_goto_idle_state() */

void lin_lld_uart_rx_isr
  (
  )
{
/*--------------------------------------------------------------------*/
	l_u8 uart_flag_iir;
	l_u8 uart_flag_lsr;
	l_u8 uart_flag_usr;
	l_u8 tmp_byte;

  /******************************
  *** 1. BREAK DETECTED
  *******************************/
  /* if the lbkdif is set */
  uart_flag_lsr = pUART->LSR & 0xff ;

  if((pUART->IER & UART_IER_EDSSI_MASK) && (!(uart_flag_lsr & UART_LSR_BI_MASK)))
  {
  	  /* Clear flag */

  	   /* Disable rx edged detection */
  	 /* End Resynchronization */

     if (SLEEP_MODE == state){
          lin_goto_idle_state();
          lin_goto_sleep_flg = 0;
          lin_master_request_sleep = 0;
      }

  	  /* Enable Break interrupt */
     pUART->IER |= UART_IER_ELSI_MASK;

  	  /* Receive data not inverted */
     pUART->IER &= ~UART_IER_EDSSI_MASK;
       /* check state of node is SLEEP_MODE */
  	  return;
  }
  /******************************
  *** 3. FRAME ERROR DETECTED
  *******************************/
  if(0 != (uart_flag_lsr&UART_LSR_FE_MASK)) {
	/* Clear FE flags */
	tmp_byte = pUART->RBR & 0xff;
	/* set lin status: error_in_response, framing_error */
	l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_FRAME_ERR);
	/* trigger callback */
	if((state == RECV_DATA)||(state == SEND_DATA) || (state == SEND_DATA_COMPLETED)) {
	    CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_FRAME_ERR, current_id);
	}
    lin_goto_idle_state();
  }
  uart_flag_iir = pUART->IIR;
  if(uart_flag_lsr & UART_LSR_BI_MASK) {
   /* Clear flag */
   /* Enable Active Edge interrupt */
	  pUART->IER |= UART_IER_EDSSI_MASK;
   /* Disable Break interrupt */
	  pUART->IER &= ~UART_IER_ELSI_MASK;
    /* check state of node is SLEEP_MODE */
   if (SLEEP_MODE == state){
      lin_goto_idle_state();
      return;
    }
    /* reset lin status */
    l_status.byte = LIN_STA_BUS_ACTIVITY;
    /* Set max frame timeout */
    frame_timeout_cnt = lin_max_frame_res_timeout_val[7];
    /******************************
    *** 1.2 SLAVE NODE: Wait for SYN
    *******************************/
    /* Start resyn */
       /* Enable Active Edge interrupt */
     /* UARTBDH_RXEDGIE_MASK; */
    pUART->RBR;
    state=RECV_SYN;
    /* Disable LBK detect */
    pUART->IER &= ~UART_IER_ELSI_MASK;
    return;
  } else {
	  tmp_byte = pUART->RBR & 0xff;
    /******************************
    *** 4. BYTE RECIEVED
    *******************************/
    if(0 != (uart_flag_iir&UART_IID_RxDataAvailable)) {
      switch(state) {
        /******************************
        *** 4.2 SLAVE: Receiving SYN byte
        *******************************/
        case RECV_SYN:
          if (0x55 == tmp_byte){
            state=RECV_PID;
          } else {
#if (LIN_PROTOCOL == PROTOCOL_J2602)
   CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_READBACK_ERR, current_id);
#endif /* End of (LIN_PROTOCOL == PROTOCOL_J2602) */
            lin_goto_idle_state();
          }
          break;
        /******************************
        *** 4.3 SLAVE: Receiving PID
        *******************************/
        case RECV_PID:
            /* checkparity and extrait PID */
            current_id=lin_process_parity(tmp_byte, CHECK_PARITY);
            /* Keep the PID */
            pid = tmp_byte;
            if(current_id !=0xFF) {
              /*****************************************/
              /*** ID received correctly - parity OK ***/
              /*****************************************/
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_PID_OK, current_id);
              /* Set Maximum response frame timeout */
              res_frame_timeout_cnt = lin_max_frame_res_timeout_val[*(response_buffer) - 1];
            }

            else {
               /*****************************************/
              /*** ID Parity Error                   ***/
              /*****************************************/
              /* set lin status: parity_error */
              l_status.byte |= LIN_STA_PARITY_ERR;
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_PID_ERR, 0xFF);
              lin_goto_idle_state();
            }

          break;
        /******************************
        *** 4.4 SLAVE: Receiving data
        *******************************/
        case RECV_DATA:
          ptr++;
          *(ptr)=tmp_byte;
          /* Check bytes received fully */
          if(cnt_byte==(response_buffer[0])) {
            /* checksum checking */
            if(lin_checksum(response_buffer, pid)==tmp_byte) {
              /*******************************************/
              /***  RX Buffer Full - Checksum OK       ***/
              /*******************************************/
              /* set lin status: successful_transfer */
              l_status.byte |= LIN_STA_SUCC_TRANSFER;
              /* disable RX interrupt */
              pUART->SGW |= UART_SGW_TXDIR_MASK;
              pUART->IER &= ~UART_IER_ERBFI_MASK;
              state=PROC_CALLBACK;
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_RX_COMPLETED, current_id);

              /* enable RX interrupt */
              pUART->SGW &= ~UART_SGW_TXDIR_MASK;
              pUART->IER |= UART_IER_ERBFI_MASK;
              if (SLEEP_MODE != state){
                lin_goto_idle_state();
              }
            }

            else {
               /*******************************************/
              /***  RX Buffer Full - Checksum ERROR    ***/
              /*******************************************/
              /* set lin status: error_in_response, checksum_error */
              l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_CHECKSUM_ERR);
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_CHECKSUM_ERR, current_id);
              lin_goto_idle_state();
            }

          }
          cnt_byte++;
          break;

        /******************************
        *** 4.5 SLAVE: Sending data
        *******************************/
        case SEND_DATA:
          /* Check for READBACK error */
          if (0==(uart_flag_lsr&UART_LSR_THRE_MASK)){
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_READBACK_ERR, current_id);
            lin_goto_idle_state();
            break;
          }else{
            if (tmp_byte != response_buffer[cnt_byte]){
              CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_READBACK_ERR, current_id);
              lin_goto_idle_state();
              break;
            }
          }
          if(cnt_byte <= (response_buffer[0])) {
            /* Send data bytes and checksum */
            cnt_byte++;
            pUART->THR = response_buffer[cnt_byte];
          } else {
            /* TX transfer complete */
            l_status.byte |= LIN_STA_SUCC_TRANSFER;
            /* Disable RX interrupt */
            pUART->SGW |= UART_SGW_TXDIR_MASK;
            pUART->IER &= ~UART_IER_ERBFI_MASK;
            state = PROC_CALLBACK;
            /* trigger CALLBACK */
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_TX_COMPLETED, current_id);
            /* Enable RX interrupt */
            pUART->SGW &= ~UART_SGW_TXDIR_MASK;
            pUART->IER |= UART_IER_ERBFI_MASK;
            lin_goto_idle_state();
          }
          break;
         /******************************
        *** 4.8 SLAVE: Low power mode
        *******************************/
        case SLEEP_MODE:
          if ((tmp_byte == 0xF0) || (tmp_byte == 0xE0) || (tmp_byte == 0xC0) || (tmp_byte == 0x80) || (tmp_byte == 0x00)) {
            /* Set idle timeout again */
            lin_goto_idle_state();
            /* Enable LIN break detect interrupt */
            pUART->IER |= UART_IER_ELSI_MASK ;
          }
          break;
        default:
          break;
      }
    }
  }
} /* End function lin_lld_UART_rx_isr() */

#endif /* End (LIN_MODE == _SLAVE_MODE_) */

/*--------------------------------------------------------------------*/

#if (LIN_MODE == _MASTER_MODE_)
/***** Globle variable data *****/

extern lin_node lin_node_descrs[NUM_OF_UART_CHANNEL];
extern const l_u16 lin_max_frame_res_timeout_val[LIN_NUM_OF_IFCS][8];

#ifdef MULTI_TIMER_MODE
extern const l_u16 max_idle_timeout[LIN_NUM_OF_IFCS];
#endif /* End  MULTI_TIMER_MODE */
/***** LOW-LEVEL API *****/


void lin_lld_uart_init
  (
    /* [IN] UART channel name */
    uart_channel_name  channel,
    /* [IN] LIN interface name*/
    l_ifc_handle iii
  )
{
  lin_node *lnode_p;
  tUART* _pUART;
  lin_configuration *lconf_p;
  tU32 DivisorLatch;
  tU32 Fractional;

  lnode_p = (lin_node *)&lin_node_descrs[channel];
  _pUART = lnode_p->pUART;
  lconf_p = (lin_configuration *)&lin_ifc_configuration[iii];

  /* Config */
  lnode_p->ifc=(l_u8)iii;
  lnode_p->response_buffer=lconf_p->response_buffer;
  /* Set UART is Master or Slave */
  lnode_p->func=(l_bool)lconf_p->function;
  lnode_p->tbit=(l_u16)(1000000/lconf_p->baud_rate);

  /* Select clock source for UART */
  if((tU32)_pUART == UART0_ADDR){
	  SIM->SCGC &= ~SIM_SCGC_UART0_MASK;
	  SIM->SCGC |=  SIM_SCGC_UART0_MASK;
  }else if((tU32)_pUART == UART1_ADDR){
	  SIM->SCGC &= ~SIM_SCGC_UART1_MASK;
	  SIM->SCGC |=  SIM_SCGC_UART1_MASK;
  }else if((tU32)_pUART == UART2_ADDR){
	  SIM->SCGC &= ~SIM_SCGC_UART2_MASK;
	  SIM->SCGC |=  SIM_SCGC_UART2_MASK;
  }



  /* Initialize UART */
  /* Set baud rate */
  /*unlock dll dlh*/
  _pUART->LCR.bit.dlab = 1;
  DivisorLatch = (MCU_BUS_FREQ/lconf_p->baud_rate/16);
  Fractional =(((MCU_BUS_FREQ/16) - (lconf_p->baud_rate * DivisorLatch))<<4u) / lconf_p->baud_rate;
  _pUART->DLH	= (DivisorLatch>>8)&0xFF;
  _pUART->DLL = DivisorLatch & 0xFF;
  _pUART->DLF	= Fractional;

  /* Enable use of 13bit breaks and UART frame for LIN */

   _pUART->LCR.dword &= ~(UART_LCR_STOP_MASK);
   _pUART->LCR.dword |= UART_LINBreakLength_13b | UART_LCR_DLS_MASK;    /* one start bit, eight data bits, one stop bit */
   _pUART->LCR.dword |= UART_LCR_DLAB_MASK;
   _pUART->LCR.bit.dlab = 0;
   /**disable fifo */
   _pUART->FCR = 0;
  /*enable rx tx*/



    _pUART->IER = 0;
   _pUART->IER |= (UART_IER_ERBFI_MASK | UART_IER_ELSI_MASK);      /* enable RX complete interrupt  and line status       */
  //_pUART->iER |= UART_IER_ETBEI_MASK;      /* enable TX complete interrupt         */
   Fractional = _pUART->LSR; /* clear LIN Break Detection flag       */
   Fractional = _pUART->IIR;
   /*enable uart*/
   _pUART->SGW |= UART_SGW_EN_MASK;

   /*wake up config*/
      //lin_wakeup_pin();
  /* Enter IDLE state */
  lin_goto_idle_state(channel);

} /* End function lin_lld_uart_init(uart_channel_name  channel, l_ifc_handle iii) */


void lin_lld_uart_deinit
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  lin_node *lnode_p;
  lnode_p = (lin_node *)&lin_node_descrs[channel];
  lnode_p->state=UNINIT;
  lnode_p->pUART->SGW &= ~UART_SGW_EN_MASK;
  lin_lld_uart_int_disable(channel);
} /* End function lin_lld_UART_deinit(UART_channel_name  channel) */


void lin_lld_uart_tx_header
  (
    /* [IN] UART channel name */
    uart_channel_name  channel,
    /* [IN] PID to be send */
    l_u8  pid_id
  )
{
  lin_node *lnode_p;
  /* Check the UART is Master ? */
  lnode_p = (lin_node *)&lin_node_descrs[channel];
  if(lnode_p->func) return;
  /* Make PID and put PID into the ongoing buffer */
  lnode_p->current_id = pid_id;
  lnode_p->pid = lin_process_parity(pid_id, MAKE_PARITY);
  /* Set LIN Status */
  lnode_p->state = SEND_BREAK;
  /* Send Break*/
  lnode_p->pUART->PATTERN |= UART_PATTERN_BC_MASK;
} /* End function lin_lld_UART_tx_header(UART_channel_name  channel, l_u8  pid_id) */


void lin_lld_uart_tx_wake_up
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  //l_u8 uart_flag_sr1;
  lin_node *lnode_p;
  lnode_p = (lin_node *)&lin_node_descrs[channel];
  if((lnode_p->state == IDLE) || (lnode_p->state == SLEEP_MODE)) {
    //uart_flag_sr1 = lnode_p->pUART->uartsr1.byte;
    /* Send wake signal byte=0x80 */
    lnode_p->pUART->THR = UARTTHR_WAKE_SIGNAL;
    /* Set Lin state to idle */
    lin_goto_idle_state(channel);
  }
}

void lin_lld_UART_int_enable
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  lin_node *lnode_p;
  #if (UART_VERSION == UART_V2)
	lnode_p = &lin_node_descrs[channel];
  #else
	lnode_p = (lin_node *)&lin_node_descrs[channel];
  #endif /* End (UART_VERSION == UART_V2) */

  /* Can't enable in interrupt context */
  if((lnode_p->state == PROC_CALLBACK) || (lnode_p->state==UNINIT) || (lnode_p->state==SLEEP_MODE)) return;

  /* Enable UART Channel*/
  lnode_p->pUART->SGW &= (~UART_SGW_TXDIR_MASK);
  lnode_p->pUART->IER |= UART_IER_ERBFI_MASK;
}


void lin_lld_uart_int_disable
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  lin_node *lnode_p;
  #if (UART_VERSION == UART_V2)
	lnode_p = &lin_node_descrs[channel];
  #else
	lnode_p = (lin_node *)&lin_node_descrs[channel];
  #endif /* End (UART_VERSION == UART_V2) */

  /* Can't disable in interrupt context */
  if((lnode_p->state == PROC_CALLBACK) || (lnode_p->state==UNINIT) || (lnode_p->state==SLEEP_MODE)) return;

  while(lnode_p->state != IDLE) { }
  /* Disable UART Channel*/
  lnode_p->pUART->SGW |= UART_SGW_TXDIR_MASK;
  lnode_p->pUART->IER &= (~UART_IER_ERBFI_MASK);
}


void lin_lld_uart_ignore_response
  (
    /* [IN] UART channel name */
	uart_channel_name  channel
  )
{
  lin_goto_idle_state(channel);
}


void lin_lld_uart_set_low_power_mode
  (
    /* [IN] UART channel name */
	uart_channel_name  channel
  )
{
  lin_node *lnode_p;

  /* Get Lin node descriptor */
  lnode_p = (lin_node *)&lin_node_descrs[channel];

  /* Configure Hw code */
  IRQ_InterruptEn(IRQ, LIN_WAKEUP_IRQ_N, ENABLE);
  /* Set Lin status = receiving data*/
  lnode_p->state=SLEEP_MODE;
}


void lin_lld_uart_rx_response
  (
    /* [IN] UART channel name */
	uart_channel_name  channel,
    /* [IN] Length of response data expect to wait */
    l_u8  msg_length
  )
{
  lin_node *lnode_p;

  /* Get Lin node descriptor */
  #if (UART_VERSION == UART_V2)
	lnode_p = &lin_node_descrs[channel];
  #else
	lnode_p = (lin_node *)&lin_node_descrs[channel];
  #endif /* End (UART_VERSION == UART_V2) */

  /* Put response length and pointer of response buffer into descriptor */
  *(lnode_p->response_buffer)=msg_length;
  lnode_p->cnt_byte=0;
  lnode_p->ptr=lnode_p->response_buffer;

  /* Set Lin status = receiving data*/
  lnode_p->state=RECV_DATA;
}

void lin_lld_uart_tx_response
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  lin_node *lnode_p;
  lnode_p = (lin_node *)&lin_node_descrs[channel];

  /* calculate checksum */
  lnode_p->response_buffer[*(lnode_p->response_buffer)+1] = lin_checksum(lnode_p->response_buffer , lnode_p->pid);
  lnode_p->cnt_byte=1;
  /* Send First byte */
  lnode_p->pUART->THR = lnode_p->response_buffer[1];
  /* Set LIN Status */
  lnode_p->state = SEND_DATA;
} /* End function lin_lld_UART_tx_response(UART_channel_name  channel) */


void lin_lld_uart_timeout
  (
    /* [IN] UART channel name */
	uart_channel_name  channel
  )
{
  register lin_node *lnode_p;
#ifdef MULTI_TIMER_MODE
   l_u8 i;
#endif /* End MULTI_TIMER_MODE */
/* multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  lin_configuration * conf;
  lin_tl_descriptor *tl_conf;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
  lnode_p = (lin_node *)&lin_node_descrs[channel];
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)

  conf = (lin_configuration *)&lin_ifc_configuration[(l_ifc_handle)lnode_p->ifc];
  /* Get TL configuration */
  tl_conf = conf->tl_desc;

  if (LD_CHECK_N_CR_TIMEOUT == tl_conf->tl_check_timeout_type){
    if(0 == --tl_conf->tl_check_timeout){
      /* switch to normal table */
      if (_MASTER_ == conf->function){
        *(conf->active_schedule_id) = *(conf->previous_schedule_id);
        conf->schedule_start_entry[*(conf->active_schedule_id)] = 0;
      }
      /* update status of transport layer */
      *conf->diagnostic_mode = DIAG_NONE;
      *conf->tl_service_status = LD_SERVICE_ERROR;
      tl_conf->tl_receive_msg_status = LD_N_CR_TIMEOUT;
      tl_conf->tl_rx_msg_status = LD_N_CR_TIMEOUT;
      tl_conf->tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
    }
  }

  if (LD_CHECK_N_AS_TIMEOUT == tl_conf->tl_check_timeout_type){
    if(0 == --tl_conf->tl_check_timeout){
      /* switch to normal table */
      if (_MASTER_ == conf->function){
        *(conf->active_schedule_id) = *(conf->previous_schedule_id);
        conf->schedule_start_entry[*(conf->active_schedule_id)] = 0;
      }
      /* update status of transport layer */
      *conf->diagnostic_mode = DIAG_NONE;
      *conf->tl_service_status = LD_SERVICE_ERROR;
      tl_conf->tl_tx_msg_status = LD_N_AS_TIMEOUT;
      tl_conf->tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
    }
  }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)*/

switch(lnode_p->state) {

    case IDLE:
      if(lnode_p->idle_timeout_cnt==0) {
        /* trigger callback */
        CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_BUS_ACTIVITY_TIMEOUT, 0xFF);
        /* goback to IDLE, reset max idle timeout */
        lnode_p->idle_timeout_cnt=_MAX_IDLE_TIMEOUT_;
        /* disable LIN break detect interrupt */
        lnode_p->pUART->IER &= (~UART_IER_ELSI_MASK) ;
      } else lnode_p->idle_timeout_cnt--;

      break;

    case SEND_PID:    /* Master */
    case RECV_SYN:
    case RECV_PID:
    case SEND_DATA:
    case SEND_DATA_COMPLETED:
      /* timeout send has occurred - change state of the node and inform core */
      if(0 == lnode_p->frame_timeout_cnt)
        lin_goto_idle_state(channel);
      else lnode_p->frame_timeout_cnt--;
      break;
    case RECV_DATA:
      /* timeout receive has occurred - change state of the node and inform core */
      if(0 == lnode_p->res_frame_timeout_cnt) {
        if(lnode_p->cnt_byte){
          /* set lin status: error_in_response */
          lnode_p->l_status.byte |= LIN_STA_ERROR_RESP;
        /* trigger callback */
          CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_NODATA_TIMEOUT, lnode_p->current_id);
        }
        lin_goto_idle_state(channel);
      } else lnode_p->res_frame_timeout_cnt--;

      break;
    case PROC_CALLBACK:
      break;
    default:
      break;
  }
} /* End function lin_lld_UART_timeout(UART_channel_name  channel) */

/*** INTERNAL FUNTIONS ***/


void lin_goto_idle_state
  (
    /* [IN] UART channel name */
	uart_channel_name  channel
  )
{

  lin_node *lnode_p;
  lnode_p = (lin_node *)&lin_node_descrs[channel];
  /* set lin status: ~bus_activity */
  lnode_p->l_status.byte &= ~LIN_STA_BUS_ACTIVITY;
  /* Set max idle timeout */
  lnode_p->idle_timeout_cnt=_MAX_IDLE_TIMEOUT_;
  lnode_p->state=IDLE;
  /* Enable LBK detect */
  lnode_p->pUART->IER |= UART_IER_ELSI_MASK ;
} /* End function lin_goto_idle_state(UART_channel_name  channel) */



void lin_lld_uart_rx_isr
  (
    /* [IN] UART channel name */
    uart_channel_name  channel
  )
{
  l_u8 uart_flag_iir;
  l_u8 uart_flag_lsr;
  l_u8 uart_flag_usr;
  l_u8 tmp_byte;

  register lin_node *lnode_p;     /* local pointer to the lin node descriptor */
  volatile tUART* _pUART;
  lnode_p = (lin_node *)&lin_node_descrs[channel];
  _pUART = lnode_p->pUART;

  uart_flag_lsr = _pUART->LSR & 0xff ;
  /*rxd pin active && no lin break character*/
  if((_pUART->IER & UART_IER_EDSSI_MASK) && (!(uart_flag_lsr & UART_LSR_BI_MASK)))
  {
    /* Clear flag */
    /* check state of node is SLEEP_MODE */
    if (SLEEP_MODE == lnode_p->state){
      lin_goto_idle_state(channel);
    }

    /* Enable Break interrupt */
    _pUART->IER |= UART_IER_ELSI_MASK;
    /* Disable Active Edge interrupt */
    _pUART->IER &= ~UART_IER_EDSSI_MASK;

    /* Receive data not inverted *//*xl6600 don't have*/
    return;
  }

  uart_flag_iir = lnode_p->pUART->IIR;
 /* Check LBK flag */
  if ((uart_flag_lsr & UART_LSR_BI_MASK)){
    /* Clear flag   read clear*/
    /* Enable Active Edge interrupt */
    _pUART->IER |= UART_IER_EDSSI_MASK;
    /* Disable Break interrupt */
    _pUART->IER &= ~UART_IER_ELSI_MASK;
    /* check state of node is SLEEP_MODE */
    if (SLEEP_MODE == lnode_p->state){
      lin_goto_idle_state(channel);
      return;
    }
    /* reset lin status */
    lnode_p->l_status.byte = LIN_STA_BUS_ACTIVITY;
    /* Set max frame timeout */
    lnode_p->frame_timeout_cnt  = lin_max_frame_res_timeout_val[lnode_p->ifc][7];
    /******************************
    *** 1.1 MASTER NODE: Sending SYN field
    *******************************/
    if(lnode_p->func == 0/* Master */) {
      lnode_p->state=SEND_PID;
      /* read clr*/
      lnode_p->pUART->RBR;
      /* Send syn field */
      _pUART->THR = 0x55;
    }
    /******************************
    *** 1.2 SLAVE NODE: Wait for SYN
    *******************************/
    else {
      lnode_p->state=RECV_SYN;
    }
    /* Disable LBK interrupt */
    _pUART->IER &= ~UART_IER_ELSI_MASK;
    return;
  } else {
    tmp_byte = lnode_p->pUART->RBR & 0xff;

    /******************************
    *** 4. BYTE RECIEVED
    *******************************/
    /* Receive Data Register Full Flag */
    if(0 != (uart_flag_iir & UART_IID_RxDataAvailable)) {

      switch(lnode_p->state) {
        /******************************
        *** 4.1 MASTER: Sending PID of frame
        *******************************/
        case SEND_PID:
#ifdef XL6600D_ADD
        	 if (0x55 == tmp_byte){
#endif
        		 lnode_p->state=RECV_PID;
        		 /* Send PID byte */
        		 _pUART->THR = lnode_p->pid;
#ifdef XL6600D_ADD
			  } else {
	#if (LIN_PROTOCOL == PROTOCOL_J2602)
				CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_READBACK_ERR, current_id);
	#endif /* End of (LIN_PROTOCOL == PROTOCOL_J2602) */
				lin_goto_idle_state(channel);
			  }//xl6600 add
#endif
          break;
        /******************************
        *** 4.2 SLAVE: Receiving SYN byte
        *******************************/
        case RECV_SYN:
          if (0x55 == tmp_byte){
            lnode_p->state=RECV_PID;
          } else {
#if (LIN_PROTOCOL == PROTOCOL_J2602)
          CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_READBACK_ERR, lnode_p->current_id);
#endif /* End of (LIN_PROTOCOL == PROTOCOL_J2602) */
          lin_goto_idle_state(channel);
        }
          break;
        /******************************
        *** 4.3 SLAVE: Receiving PID
        *******************************/
        case RECV_PID:
          if(!lnode_p->func) { /*Master*/
#ifdef XL6600D_ADD
        	  if(lin_process_parity(tmp_byte, CHECK_PARITY) == lnode_p->current_id){
#endif
        		  /* trigger callback */
					CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_PID_OK, lnode_p->current_id);
					/* Set Maximum response frame timeout */
					lnode_p->res_frame_timeout_cnt = lin_max_frame_res_timeout_val[lnode_p->ifc][*(lnode_p->response_buffer) - 1];
#ifdef XL6600D_ADD
        	  }else{
        		  /* set lin status: parity_error */
				   lnode_p->l_status.byte |= LIN_STA_PARITY_ERR;
				   /* trigger callback */
				   CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_PID_ERR, lnode_p->current_id);
				   lin_goto_idle_state(channel);
        	  }
#endif
          }
          else { /* Slave node */
            /* checkparity and extrait PID */
            lnode_p->current_id= lin_process_parity(tmp_byte, CHECK_PARITY);
            /* Keep the PID */
            lnode_p->pid = tmp_byte;
            if(lnode_p->current_id !=0xFF) {
              /*****************************************/
              /*** ID received correctly - parity OK ***/
              /*****************************************/
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_PID_OK, lnode_p->current_id);
              /* Set Maximum response frame timeout */
              lnode_p->res_frame_timeout_cnt = lin_max_frame_res_timeout_val[lnode_p->ifc][*(lnode_p->response_buffer) - 1];
            }
            else {
              /*****************************************/
              /*** ID Parity Error                   ***/
              /*****************************************/
              /* set lin status: parity_error */
              lnode_p->l_status.byte |= LIN_STA_PARITY_ERR;
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_PID_ERR, 0xFF);
              lin_goto_idle_state(channel);
            }
          }
          break;

        /******************************
        *** 4.4 SLAVE: Receiving data
        *******************************/
        case RECV_DATA:
          lnode_p->ptr++;
          *(lnode_p->ptr)=tmp_byte;
          /* Check bytes received fully */
          if(lnode_p->cnt_byte==(lnode_p->response_buffer[0])) {
            /* checksum checking */
            if(lin_checksum(lnode_p->response_buffer, lnode_p->pid)==tmp_byte) {
              /*******************************************/
              /***  RX Buffer Full - Checksum OK       ***/
              /*******************************************/
              /* set lin status: successful_transfer */
              lnode_p->l_status.byte |= LIN_STA_SUCC_TRANSFER;
              /* disable RX interrupt */
              _pUART->SGW |= UART_SGW_TXDIR_MASK;
              _pUART->IER &= ~UART_IER_ERBFI_MASK;
              lnode_p->state=PROC_CALLBACK;
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_RX_COMPLETED, lnode_p->current_id);

              /* enable RX interrupt */
              _pUART->SGW &= ~UART_SGW_TXDIR_MASK;
              _pUART->IER |= UART_IER_ERBFI_MASK;
              if (SLEEP_MODE != lnode_p->state){
                lin_goto_idle_state(channel);
              }
            } else {
              /*******************************************/
              /***  RX Buffer Full - Checksum ERROR    ***/
              /*******************************************/
              /* set lin status: error_in_response, checksum_error */
              lnode_p->l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_CHECKSUM_ERR);
              /* trigger callback */
              CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_CHECKSUM_ERR, lnode_p->current_id);

              lin_goto_idle_state(channel);
            }
          }
          lnode_p->cnt_byte++;
          break;

        /******************************
        *** 4.5 SLAVE: Sending data
        *******************************/
        case SEND_DATA:
          /* Check for READBACK error */
          if (0==(uart_flag_lsr & UART_LSR_THRE_MASK)){
            CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_READBACK_ERR, lnode_p->current_id);
            lin_goto_idle_state(channel);
            break;
          }else{
            if (tmp_byte != lnode_p->response_buffer[lnode_p->cnt_byte]){
              CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_READBACK_ERR, lnode_p->current_id);
              lin_goto_idle_state(channel);
              break;
            }
          }

          if(lnode_p->cnt_byte <= (lnode_p->response_buffer[0])) {
            /* Send data bytes and checksum */
            lnode_p->cnt_byte++;
            _pUART->THR = lnode_p->response_buffer[lnode_p->cnt_byte];
          } else {
            /* TX transfer complete */
            lnode_p->l_status.byte |= LIN_STA_SUCC_TRANSFER;
            /* Disable RX interrupt */
            _pUART->SGW |= UART_SGW_TXDIR_MASK;
            _pUART->IER &= ~UART_IER_ERBFI_MASK;
            lnode_p->state = PROC_CALLBACK;
            /* trigger CALLBACK */
            CALLBACK_HANDLER((l_ifc_handle)lnode_p->ifc, LIN_LLD_TX_COMPLETED, lnode_p->current_id);
            /* Enable RX interrupt */
            _pUART->SGW &= ~UART_SGW_TXDIR_MASK;
            _pUART->IER |= UART_IER_ERBFI_MASK;
            lin_goto_idle_state(channel);
          }
          break;
         /******************************
        *** 4.8 SLAVE: Low power mode
        *******************************/
        case SLEEP_MODE:
          if ((tmp_byte == 0xF0) || (tmp_byte == 0xE0) || (tmp_byte == 0xC0) || (tmp_byte == 0x80) || (tmp_byte == 0x00)) {
             /* Set idle timeout again */
            lin_goto_idle_state(channel);
             /* disable LIN break detect interrupt */
            _pUART->IER |= UART_IER_ELSI_MASK ;
          }
          break;
        default:
          break;
      }
    }
  }
} /* End function lin_lld_UART_rx_isr(UART_channel_name  channel) */

#endif /* End (LIN_MODE == _MASTER_MODE_) */

/**
* @}
*/
