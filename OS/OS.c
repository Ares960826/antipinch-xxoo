/*
 * OS.c
 *
 *  Created on: 2021$BG/(B3$B7n(B25$BF|(B
 *      Author: shenh4
 */

#ifndef OS_C
#define OS_C

/*----------------------------------------------------------------------------*/

/*****************/
/* Include Files */
/*****************/
#include "Os.h"
#include "Mcu.h"
#include "delay.h"
#include "xl_nvic.h"
#include "Debug.h"
#include "system_XL6600.h"
#include "sub_task.h"
#include "xl_wdog.h"
//#include "Mcu.h"
//#include "ProjCfg.h"
/*------------------------ end of Include Files ------------------------------*/

//#define MCU_RAM_SIZE            16384u  /* 16KByte */
#define MCU_RAM_SIZE            10240u  /* 10KByte */
//#define stack_start            0x20000000
#define STACK_START_ADDR        (0x20000000 + MCU_RAM_SIZE)
#define STACK_SIZE              2048u  /* unit: byte */
#define STACK_END_ADDR          (STACK_START_ADDR - STACK_SIZE)
#define STACK_FILL_BYTE         0x5Au


/**********************/
/* Public Const Array */
/**********************/

/*-- Define timer,message and task used by the os kernel --*/
uint8_t uxCriticalNesting = 0u;
uint8_t xSchedulerRunning = 0u;                  /* os running request */
uint16_t os_overloadcounter = 0u;                /* cpu overload times */
uint8_t os_msg_num = 0u;                         /* message number in message queue */
uint8_t os_tick_count = 0u;                      /* counter for recording how many ticks has passed by */
OS_TMR_T os_timer[MAX_TIMER_NUMBER][Os_Event_PerTask]; 	/* task config timer */
OS_MSG_T os_msg_q[MAX_MESSAGE_NUMBER];		/* message queue */
OS_TCB_T os_task_tcb[MAX_TASK_NUMBER];		/* task control block */

/*------------------------ end of Public Const Array -------------------------*/


/****************************/
/* Private Macro Definition */
/****************************/

/*------------------ end of Private Macro Definition -------------------------*/



/*****************************/
/* Private Type or Structure */
/*****************************/

/*------------------ end of Private Type or Structure ------------------------*/


/*********************************/
/* Private Variable - use static */
/*********************************/
volatile uint8_t  StackUsagePercent = 0u;

/*------------------ end of Private Variable ---------------------------------*/

/*******************************************/
/* Private Function Prototype - use static */
/*******************************************/
static void Os_Stack_Init(void);
static void Os_Idle_Task(void);

/*------------------ end of Private Function Prototype -----------------------*/


/********************/
/* Private Function */
/********************/

/*******************************************************************************
 * FUNCTION :  	   mem_copy()
 * DESCRIPTION :   copy data stored in the source address to the target address
 * INPUT       :   dest   --- destination address
 *				   src    --- resource address
 *				   length --- the length of the whole copied address
 * RETURN      :   void
 * WARNINGS:
 *
 ******************************************************************************/
static void Mem_Copy(uint8_t *dest, uint8_t *src, uint8_t length)
{
	if((NULL == dest) || (NULL == src) || (0u == length))
	{
		return;
	}

	while(length--)
	{
		*dest++ = *src++;
	}
}

/*******************************************************************************
 * FUNCTION :  	   get_bitnum()
 * DESCRIPTION :   find position of the first bit 1
 * INPUT       :   dest   --- data_in
 * RETURN      :   uint8_t
 * WARNINGS:
 *
 ******************************************************************************/
static uint8_t Get_Bitposition(uint8_t os_task_id, uint16_t notify_event)
{
    uint8_t i = 0u;

    if ((os_task_id >= MAX_TASK_NUMBER) || (0u == notify_event))
	{
		return ERROR_TIMER_GENERAL;
	}

    for(i = 0u; i < Os_Event_PerTask; i++)
    {
        if(os_task_config_table[os_task_id].notify_event[i].task_event == notify_event)
        {
            break;
        }
	}

    if(Os_Event_PerTask == i)
    {
        return ERROR_TIMER_GENERAL;
    }

    return i;
}

/* =================================================================================== */
static void Os_Stack_Init(void)
{
    uint8_t  *stack_ptr = 0u;

#if(OS_STACK_STATISTIC_ENABLE == 0u)
    stack_ptr = (uint8_t *)(STACK_END_ADDR);
    *stack_ptr = STACK_FILL_BYTE;
#else
    uint16_t i = 0u;
    uint16_t count = 0u;

    /* Init the ram from the half size position of the stack */
    count = STACK_SIZE / 2u;
    stack_ptr = (uint8_t *)(STACK_START_ADDR - (STACK_SIZE / 2u) - 1u);

    /* The stack grows from high address to low address */
    for(i = 0u; i < count; i++)
    {
        *stack_ptr = STACK_FILL_BYTE;
        stack_ptr--;
    }
#endif
}

static void Os_Idle_Task(void)
{	// µ˜”√”¶”√≥Ã–Úµƒ∫ÛÃ®»ŒŒÒ
	APPBackGroundTask(); /*TODO: how to avoid OS call App functions*/
}

/*------------------ end of Private Function ---------------------------------*/


/*******************/
/* Public Function */
/*******************/

/*******************************************************************************

 * FUNCTION :  void os_init()
 * DESCRIPTION :  Initialize some tasks to run when OS is active.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
void Os_Init(void)
{
	uint8_t i = 0u;
    uint8_t j = 0u;

	/*-- init os task/timer/event data structure --*/
	os_tick_count = 0u;
    uxCriticalNesting = 0u;
    os_overloadcounter = 0u;
    // NOTE:≥ı ºªØÀ˘”–µƒ ±º‰∫Õ ±º‰ƒ£øÈ
	for(i = 0u; i < MAX_TIMER_NUMBER; i++)
	{
        for(j = 0u; j < Os_Event_PerTask; j++)
        {
    		os_timer[i][j].status = 0x00u;
    		os_timer[i][j].count = 0x00u;
    		os_timer[i][j].period = 0x00u;
            os_timer[i][j].offset = 0x00u;
    		os_timer[i][j].notify_task_id = 0xffu;
    		os_timer[i][j].notify_event	= 0x00u;		/* no event to notify */
        }
	}

	os_msg_num	= 0u;
	for(i = 0u; i < MAX_MESSAGE_NUMBER; i++)
	{
		os_msg_q[i].task_id = 0xffu;
		os_msg_q[i].message_data[0]	= 0x00u;
		os_msg_q[i].message_data[1]	= 0x00u;
		os_msg_q[i].message_data[2]	= 0x00u;
	}

	for(i = 0; i < MAX_TASK_NUMBER; i++)
	{
		os_task_tcb[i].event = 0x00u;			/* clear event and message */
		os_task_tcb[i].msg_count = 0x00u;
        for(j = 0; j < Os_Event_PerTask; j++)
        {
		    os_task_tcb[i].task_ptr[j] = os_task_config_table[i].notify_event[j].task_ptr;
        }
	}

    Os_Stack_Init();

    Os_Start();
	/*-- end --*/
}

/*******************************************************************************

 * FUNCTION :  void os_overload_monitor()
 * DESCRIPTION :  cpu overload monitor.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
 void Os_Overload_Monitor(void)
{
   	if(os_tick_count > 1u)
	{
        os_overloadcounter++;
	}
}

/*******************************************************************************

 * FUNCTION :  void os_stack_monitor()
 * DESCRIPTION :  monitor stack.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
 void Os_Stack_Monitor(void)
{
    uint8_t  *stack_ptr = 0u;	// ∂—’ª÷∏’Î

    stack_ptr = (uint8_t *)STACK_END_ADDR;	// ÷∏œÚ∂—’ªµƒ’ªµ◊

    if(STACK_FILL_BYTE != *stack_ptr)	// Check if the stack has overflowed
    {
        while(1u)	// Infinite loop if stack overflow occurs
        {
            /* Stack overflow, do nothing */
        	Debug("Stack Error \n");
        }
    }
#if(OS_STACK_STATISTIC_ENABLE == 1u)
    uint16_t i = 0u;
    uint16_t count = 0u;

    else
    {
        /* Calculate the stack usage rate */
        /* Stack is initialised from the half size position of the stack */
        count = STACK_SIZE / 2u;
        stack_ptr = (uint8_t *)(STACK_END_ADDR);

        /* The stack grows from high address to low address */
        for(i = 0u; i < count; i++)
        {
            if(STACK_FILL_BYTE != *stack_ptr)
            {
                StackUsagePercent = 100u - ((i * 100u) / STACK_SIZE);
                break;
            }
            else
            {
                stack_ptr++;
            }
        }

        if(i >= count)
        {
            StackUsagePercent = 50u;
        }
    }
#endif  /* OS_STACK_STATISTIC_ENABLE */
}

 void Sys_Tick_Timer_Start(){
	uint32_t temp;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	uint8_t fac_us = Get_SystemCoreClock()/1000000;
	SysTick->LOAD=1000*fac_us; 				//??$B2C(B? nus = 1000
	SysTick->VAL=0x00;        				//$B@66u(B?$B?t4o(B
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; //?$B;OE]?t(B
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
 }

/*******************************************************************************

 * FUNCTION :  void os_start()
 * DESCRIPTION :  start os task.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
void Os_Start(void)
{
	uint8_t i = 0u;
    uint8_t j = 0u;

	/*-- init os task/timer/event data structure --*/
	os_tick_count = 0u;
    xSchedulerRunning = pdTRUE;

	for(i = 0u; i < MAX_TASK_NUMBER; i++)
	{
        for(j = 0u; j < os_task_config_table[i].event_num; j++)
        {
            if(os_task_config_table[i].notify_event[j].timer_period != OS_Event)
            {
                Os_Timer_Start_Periodic(os_task_config_table[i].task_id, os_task_config_table[i].notify_event[j].task_event);
            }
        }
    }

    Sys_Tick_Timer_Start();
	//Systick_Init();

    //open wdog  64ms
    WDOG_Configuration(WDOG_STAT_RUNNING);

	/*-- end --*/
}


/*******************************************************************************
 * FUNCTION :  os_schedule()
 * DESCRIPTION :  select a ready task to run. This function has to be called whenever the system is idle.
                  It will always select the highest priority ready task.
                  ’‚∂Œ¥˙¬Î «“ª∏ˆºÚµ•µƒ≤Ÿ◊˜œµÕ≥µ˜∂»∫Ø ˝£¨√˚Œ™Os_Schedule°£À¸µƒ÷˜“™ƒøµƒ «‘⁄œµÕ≥ø’œ– ±—°‘Ò“ª∏ˆ◊º±∏∫√µƒ»ŒŒÒ¿¥‘À––°£
                  ’‚∏ˆ∫Ø ˝ª· º÷’—°‘Ò◊Ó∏ﬂ”≈œ»º∂µƒ◊º±∏∫√µƒ»ŒŒÒ°£
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
void Os_Schedule(void)
{
    uint8_t j = 0u;
	uint8_t i = 0u;
    uint16_t event = 0u;	// event ”√”⁄¥Ê¥¢»ŒŒÒµƒ ¬º˛
	OS_TCB_T *ptcb = os_task_tcb;	// ptcb  «“ª∏ˆ÷∏œÚ»ŒŒÒøÿ÷∆øÈ£®Task Control Block£©µƒ÷∏’Î

	while(1u)
	{
        if(xSchedulerRunning == pdTRUE)	// ºÏ≤Èµ˜∂»≥Ã–Ú «∑Ò’˝‘⁄‘À––
        {
            Os_Stack_Monitor();
        	event = ptcb->event;	// ªÒ»°µ±«∞»ŒŒÒµƒ ¬º˛
        	if(0u != event)			// ºÏ≤È «∑Ò÷¡…Ÿ”–“ª∏ˆ ¬º˛Œ™»ŒŒÒ◊º±∏∫√¡À
        	{
                for(j = 0u; j < os_task_config_table[i].event_num; j++)
                {		// —≠ª∑µ±«∞»ŒŒÒµƒÀ˘”– ¬º˛
                    if((event & os_task_config_table[i].notify_event[j].task_event) == os_task_config_table[i].notify_event[j].task_event)
                    {	// ºÏ≤È ¬º˛ «∑ÒŒ™»ŒŒÒ◊º±∏∫√¡À
            			if((ptcb->task_ptr[j]) != NULL)
            			{// ºÏ≤È»ŒŒÒ÷∏’Î «∑Ò≤ªŒ™ø’
            				(*ptcb->task_ptr[j])();		// Run the task		QUESTION
                            Os_Event_Clear(i, os_task_config_table[i].notify_event[j].task_event);// Clear the event
            			}
            			else	// »Áπ˚task_ptrŒ™NULL£¨‘ÚΩ¯»ÎŒﬁœﬁ—≠ª∑
            			{
            				while(1u){
            					Debug("task_ptr Error \n");
            				}; /* if task_ptr is NULL, watchdog should work */

            			}
                    }
                }
        	}

        	++ptcb;		// Move to the next task
        	if((++i) >= TASK_ID_MAX_NUM) // TASK_ID_MAX_NUM=10
        	{	// »Áπ˚“——°÷–À˘”–»ŒŒÒ£¨«Î÷ÿ÷√
        		i = 0u;
        		ptcb = os_task_tcb;
        		Os_Idle_Task();
        	}

        	if(os_tick_count > 0u)		/* deal with os_tick */
        	{	// ºÏ≤È «∑Ò”–œµÕ≥’Òµ¥–Ë“™¥¶¿Ì
                Os_Overload_Monitor();	// cpuπ˝‘ÿº‡≤‚
        		CPU_ENTER_CRITICAL();	// Ω¯»Î—œ∏Òƒ£ Ω£∫Ω˚÷πÕ‚≤ø÷–∂œ£ø
        		os_tick_count--;
        		CPU_EXIT_CRITICAL();
        		Os_Tick();
        	}
        }

	}
}


/*******************************************************************************
 * FUNCTION :  os_tick()
 * DESCRIPTION :  This function is called from os_schedule().
                  It will update the task schedule timer
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
 void Os_Tick(void)
 {
    uint8_t i = 0u;
    uint8_t j = 0u;
	static OS_TCB_T *ptcb;	// ÷∏œÚ»ŒŒÒøÿ÷∆øÈ£®Task Control Block£©µƒ÷∏’Î

	ptcb = os_task_tcb;		// ≥ı ºªØptcb÷∏’Î

	for(i = 0u; i < MAX_TIMER_NUMBER; i++)
	{	// ±È¿˙À˘”–∂® ±∆˜
        for(j = 0u; j < os_task_config_table[i].event_num; j++)
        {// ±È¿˙µ±«∞∂® ±∆˜œ‡πÿµƒÀ˘”– ¬º˛
    		if((os_timer[i][j].status) & 0x01u)			/* timer start bit =1 */
    		{// ºÏ≤È∂® ±∆˜ «∑Ò“—∆Ù∂Ø£®start bit = 1£©
                if(os_timer[i][j].offset == 0u)         /* wait for offset timer ready */
                {// ºÏ≤È∆´“∆∂® ±∆˜ «∑Ò◊º±∏∫√
        			if(os_timer[i][j].count)
        			{// ºÏ≤È∂® ±∆˜º∆ ˝
        				/* timer expires, then set corresponding event, we assume there is no interrupt nesting.
        					so, we do not have to disable interrupt  */
        				if((os_timer[i][j].notify_task_id < MAX_TASK_NUMBER) && (--os_timer[i][j].count == 0u))
        				{// »Áπ˚∂® ±∆˜µΩ∆⁄£¨…Ë÷√œ‡”¶µƒ ¬º˛
        					ptcb = &os_task_tcb[os_timer[i][j].notify_task_id];
        					CPU_ENTER_CRITICAL();					/* need to disable interrupt if not called from isr */
        					(ptcb->event) |= (os_timer[i][j].notify_event);//notify event for timer out
        					CPU_EXIT_CRITICAL();
        					if((os_timer[i][j].status) & 0x80u)			/* if periodic, reset counter */
        					{// »Áπ˚ «÷‹∆⁄–‘∂® ±∆˜£¨÷ÿ÷√º∆ ˝∆˜
        						(os_timer[i][j].count) = (os_timer[i][j].period);
        					}
        					else	// QUESTION
        					{
        						os_timer[i][j].status	= 0x0u;		/* on shot, stop the timer */
        					}
        				}
        			}
                }
                else
                {
                    os_timer[i][j].offset--;
                }
    		}
        }
	}
}


/*******************************************************************************
 * FUNCTION :  os_timer_start_one_shot()
 * DESCRIPTION :  start the timer one shot
 * INPUT       :  os_timer_id --- which timer
                  notify_event ---- event to be sent when timer expires
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:   	can't be called from isr
 ******************************************************************************/
uint8_t Os_Timer_Start_One_Shot(uint8_t os_task_id, uint16_t notify_event)
{
    uint8_t bitpos = 0u;
	OS_TMR_T *ptimer;

    bitpos = Get_Bitposition(os_task_id, notify_event);

	if((os_task_id >= MAX_TASK_NUMBER) || (0u == notify_event) || (bitpos >= Os_Event_PerTask))
	{
		return ERROR_TIMER_GENERAL;
	}

	CPU_ENTER_CRITICAL();
	ptimer = &os_timer[os_task_id][bitpos];
	ptimer->notify_task_id = os_task_config_table[os_task_id].task_id;
	ptimer->notify_event = os_task_config_table[os_task_id].notify_event[bitpos].task_event;
	ptimer->period = 1u;
	ptimer->count = 1u;
    ptimer->offset = os_task_config_table[os_task_id].notify_event[bitpos].timer_offset;
	ptimer->status = 0x01;     			/* set the START bit */
	CPU_EXIT_CRITICAL();

	return ERROR_NONE;
}

/*******************************************************************************
 * FUNCTION :  os_timer_start_periodic()
 * DESCRIPTION :  start the periodic timer
 * INPUT       :  os_timer_id --- which timer
                  notify_event ---- event to be sent when timer expires
 * OUTPUT      :
 * RETURN      :  0: ok
 * WARNINGS:   	can't be called from isr
 ******************************************************************************/
uint8_t Os_Timer_Start_Periodic(uint8_t os_task_id, uint16_t notify_event)
{
    uint8_t bitpos = 0u;
	OS_TMR_T *ptimer;

    bitpos = Get_Bitposition(os_task_id, notify_event);

	if((os_task_id >= MAX_TASK_NUMBER) || (0u == notify_event) || (bitpos >= Os_Event_PerTask))
	{
		return ERROR_TIMER_GENERAL;
	}

	CPU_ENTER_CRITICAL();
	ptimer = &os_timer[os_task_id][bitpos];
	ptimer->notify_task_id = os_task_config_table[os_task_id].task_id;
	ptimer->notify_event = os_task_config_table[os_task_id].notify_event[bitpos].task_event;
	ptimer->period = os_task_config_table[os_task_id].notify_event[bitpos].timer_period;
	ptimer->count = os_task_config_table[os_task_id].notify_event[bitpos].timer_period;
    ptimer->offset = os_task_config_table[os_task_id].notify_event[bitpos].timer_offset;
	ptimer->status = 0x81u;     			/* set the PERIODIC & START bit */
	CPU_EXIT_CRITICAL();

	return ERROR_NONE;
}

/*******************************************************************************
 * FUNCTION :  os_timer_stop()
 * DESCRIPTION :  stop the  timer
 * INPUT       :  os_timer_id --- which timer
               :  notify_event ---- event to be sent when timer expires
 * OUTPUT      :
 * RETURN      :  0: ok
 * WARNINGS:
 ******************************************************************************/
uint8_t Os_Timer_Stop(uint8_t os_task_id, uint16_t notify_event)
{
    uint8_t bitpos = 0u;
	OS_TMR_T *ptimer;

    bitpos = Get_Bitposition(os_task_id, notify_event);

	if((os_task_id >= MAX_TIMER_NUMBER) || (bitpos >= Os_Event_PerTask))
	{
		return ERROR_TIMER_OVERFLOW;
	}

	ptimer	= &os_timer[os_task_id][bitpos];
	CPU_ENTER_CRITICAL();
	if((ptimer->notify_task_id < MAX_TASK_NUMBER) &&(ptimer->status & 0x01u))
	{
		os_task_tcb[ptimer->notify_task_id].event &= ~ptimer->notify_event;	/* clear the event for the task */
	}
	(ptimer->status) &= ~0x01u;	/* timer marked as free */
	CPU_EXIT_CRITICAL();

	return ERROR_NONE;
}

/*******************************************************************************
 * FUNCTION :  os_message_send()
 * DESCRIPTION :  send a message to a specific task
 * INPUT       :  task_id --- where to send
                  msg_data ---- data to be sent. msg_data lenght must be 3  bytes
 * OUTPUT      :
 * RETURN      :  0 -- success;  ~0 -- error code
 * WARNINGS:  message will be copied to the system message bufffer
              should not be called from ISR
 *
 ******************************************************************************/
uint8_t Os_Message_Send(uint8_t task_id, uint8_t *msg_data)
{
	uint8_t *pmsg;
	OS_TCB_T *ptcb;

	if(task_id >= MAX_TASK_NUMBER)
	{
		return ERROR_TASK_GENERAL;
	}

	CPU_ENTER_CRITICAL();
	if(MAX_MESSAGE_NUMBER <= os_msg_num)
	{
		CPU_EXIT_CRITICAL();

		return ERROR_MESSAGE_OVERFLOW;
	}

	/*-- copy the msg into the system buffer --*/
	os_msg_q[os_msg_num].task_id	= task_id;
	pmsg = (uint8_t *)&os_msg_q[os_msg_num++].message_data[0];
	CPU_EXIT_CRITICAL();
	pmsg[0]	= msg_data[0];
	pmsg[1]	= msg_data[1];
	pmsg[2]	= msg_data[2];
	/*-- end --*/

	/*-- task message counter add 1, and set task message ready --*/
	ptcb = &os_task_tcb[task_id];
	CPU_ENTER_CRITICAL();
	if(++(ptcb->msg_count) >= 1u)
	{
		(ptcb->event) |= 0x0001u;			/* set message ready bit */
	}
	CPU_EXIT_CRITICAL();
	/*-- end --*/

	return ERROR_NONE;
}

/*******************************************************************************
 * FUNCTION :  isr_message_send()
 * DESCRIPTION :  send a message to a specific task
 * INPUT       :  task_id --- where to send
                  msg_data ---- data to be sent. msg_data lenght must be 3  bytes
 * OUTPUT      :
 * RETURN      :  0 -- success;  ~0 -- error code
 * WARNINGS:  message will be copied to the system message bufffer
              the only way to send message to tasks from isr
 *
 ******************************************************************************/
uint8_t Isr_Message_Send(uint8_t task_id, uint8_t *msg_data)
{
	uint8_t *pmsg;
	OS_TCB_T *ptcb;

	if(task_id >= MAX_TASK_NUMBER)
	{
		return ERROR_TASK_GENERAL;
	}

	if(MAX_MESSAGE_NUMBER <= os_msg_num)
	{
		return ERROR_MESSAGE_OVERFLOW;
	}

	/*-- copy the msg into the system buffer --*/
	os_msg_q[os_msg_num].task_id = task_id;
	pmsg = (uint8_t *)&os_msg_q[os_msg_num++].message_data[0];
	pmsg[0]	= msg_data[0];
	pmsg[1]	= msg_data[1];
	pmsg[2]	= msg_data[2];
	/*-- end --*/

	/*-- task message counter add 1, and set task message ready --*/
	ptcb = &os_task_tcb[task_id];
	if (++(ptcb->msg_count) >= 1u)
	{
		(ptcb->event) |= 0x0001u;
	}
	/*-- end --*/

	return ERROR_NONE;
}

/*******************************************************************************
 * FUNCTION :  os_message_get()
 * DESCRIPTION :  get a message to a specific task's message queue
 * INPUT       :   task_id ---where to get the message
 * OUTPUT      :   msg_buffer --- the buffer to receive the message. buffer lenght must be 3 bytes
 * RETURN      :  positive value ( >= 0) -- success, and number of unread msg still in
                                            the system buffer;
                  negative value -- error code or message none
 * WARNINGS:  	 should not be called from ISR
 *
 ******************************************************************************/
char Os_Message_Get(uint8_t task_id, uint8_t *msg_buffer)
{
	uint8_t i = 0u;
	OS_TCB_T *ptcb;
	OS_MSG_T *pmsg;

	if((task_id >= MAX_TASK_NUMBER) || (os_task_tcb[task_id].msg_count == 0u))
	{
		return MESSAGE_NONE;
	}

	ptcb = &os_task_tcb[task_id];
	pmsg = os_msg_q;

	/*--  retrieve the message from system buffer --*/
	for(i = 0u; i < os_msg_num; i++,pmsg++)
	{
		if(pmsg->task_id == task_id)
		{
			Mem_Copy(msg_buffer, (uint8_t *)pmsg->message_data, sizeof(pmsg->message_data));

			/*-- move one message block fronter --*/
			CPU_ENTER_CRITICAL();					/* disable interrupt to check if we move msg block end */
			for(; i < (os_msg_num-1); i++,pmsg++)
			{
				CPU_EXIT_CRITICAL();				/* enable interrupt to minimize the isr delay */
				Mem_Copy((uint8_t *)pmsg, (uint8_t *)(pmsg+1), sizeof(*pmsg));
				CPU_ENTER_CRITICAL();
			}/*-- move end --*/

			if(--(ptcb->msg_count) == 0u)
			{
				(ptcb->event) &= ~0x0001u;			/* clear msg ready flag if there is no more msg left for the task */
			}
			os_msg_num--;
			CPU_EXIT_CRITICAL();

			return (ptcb->msg_count);
		}
	}
	/*-- end --*/

	return MESSAGE_NONE;
}

/*******************************************************************************
 * FUNCTION :  os_event_post(task_id, event)
 * DESCRIPTION :  post the event to the specified task
 * INPUT       :  task_id --- which task
                  event -- bit-mapped event
 * OUTPUT      :
 * RETURN      :   none
 * WARNING:      can't be called by isr
 ******************************************************************************/
void Os_Event_Post(uint8_t task_id, uint16_t event)
{
	if(task_id >= MAX_TASK_NUMBER || 0u == event)
	{
		return;
	}

	CPU_ENTER_CRITICAL();
	(os_task_tcb[task_id].event) |= event;
	CPU_EXIT_CRITICAL();
}

/*******************************************************************************
 * FUNCTION :  isr_event_post (task_id, event)
 * DESCRIPTION :  post the event to the specified task from isr
 * INPUT       :  task_id --- which task
                  event -- bit-mapped event
 * OUTPUT      :
 * RETURN      :   none
 * WARNING:      the only way to post event to tasks from isr
 ******************************************************************************/
void Isr_Event_Post(uint8_t task_id, uint16_t event)
{
	if(task_id >= MAX_TASK_NUMBER || 0u == event)
	{
		return;
	}

	(os_task_tcb[task_id].event) |= event;
}

/*******************************************************************************
 * FUNCTION :  os_event_get(task_id)
 * DESCRIPTION :  get the event flag of the specified task
 * INPUT       :  task_id --- which task
 * OUTPUT      :
 * RETURN      :   event flag
 * WARNINGS:  since the tasking model has to be cooperative, any task should not handle
              all the events at once. Therefore, event_get() will not clear the the task's
              event flag. The calling task should use event_clear(task_id,event_bit) to
              clear the event bit which it is handling. can't be called from isr
 ******************************************************************************/
uint16_t Os_Event_Get(uint8_t task_id)
{
	if(task_id >= MAX_TASK_NUMBER)
	{
		return 0u;
	}

	return (os_task_tcb[task_id].event);
}

/*******************************************************************************
 * FUNCTION :  os_event_clear(task_id, event_it)
 * DESCRIPTION :  get the event flag of the specified task
 * INPUT       :  task_id --- which task
                  event -- the '1" bits will be cleared
 * OUTPUT      :
 * RETURN      :   event flag
 * WARNING:      can't called by isr
 ******************************************************************************/
void Os_Event_Clear(uint8_t task_id, uint16_t event)
{
	if(task_id >= MAX_TASK_NUMBER)
	{
		return;
	}

	CPU_ENTER_CRITICAL();
	os_task_tcb[task_id].event &= ~event;
	CPU_EXIT_CRITICAL();
}

/*******************************************************************************
 * FUNCTION :  os_shutdown(void)
 * DESCRIPTION :  shut down os
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 ******************************************************************************/
void Os_Shutdown(void)
{
	xSchedulerRunning = pdFALSE;
}

/*----------------------- end of Public Function -----------------------------*/
#endif /* OS_C */
