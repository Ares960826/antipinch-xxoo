#ifndef  _OS_H_
#define  _OS_H_

/*----------------------------------------------------------------------------*/

/*****************/
/* Include Files */
/*****************/
#include "typedef.h"
//#include "project.h"
#include "Task.h"

/*------------------------ end of Include Files ------------------------------*/


/*********************/
/* conditional macro */
/*********************/

/*------------------ end of conditional macro --------------------------------*/

/*****************************/
/* Chips Relative Definition */
/*****************************/
extern void __cy_stack(void);

#define OS_STACK_SIZE           0x800u

#define vPortEnterCritical()    {if(uxCriticalNesting != 255){uxCriticalNesting++;/*CyGlobalIntDisable;*/}}
#define vPortExitCritical()     {if(uxCriticalNesting > 0){uxCriticalNesting--;if(uxCriticalNesting == 0){/*CyGlobalIntEnable;*/}}}

//#define CPU_ENTER_CRITICAL()	vPortEnterCritical()
#define CPU_ENTER_CRITICAL()	__disable_irq()
//#define CPU_EXIT_CRITICAL()		vPortExitCritical()
#define CPU_EXIT_CRITICAL()		__enable_irq()


/***************************/
/* Public Macro Definition */
/***************************/
#define OS_PROFILE

#ifdef  OS_PROFILE
#define	MSG_OVERRUN		-11
#define	MSG_UNDERRUN	-12
#define	TIMER_OVERRUN	-13
#endif

#if !defined(NULL)
#define NULL (void*)0
#endif

#define OS_Tack_Value               ((uint16_t)0x5AA5u)

#define pdTRUE			    ((uint8_t)1u)
#define pdFALSE			    ((uint8_t)0u)


/*The below definition is for OS module*/
#define	MAX_TASK_NUMBER				TASK_ID_MAX_NUM
#define	MAX_MESSAGE_NUMBER			TASK_ID_MAX_NUM
#define	MAX_TIMER_NUMBER			TASK_ID_MAX_NUM

/*Error processing table for OS module*/
#define	ERROR_NONE					0x00
#define	MESSAGE_NONE				-1

#define	ERROR_MESSAGE_GENERAL		0xf1
#define	ERROR_TASK_GENERAL			0xf2
#define	ERROR_TIMER_GENERAL			0xf3
#define	ERROR_TIMER_OVERFLOW		0xf4
#define	ERROR_MESSAGE_OVERFLOW		0xf5
#define	ERROR_MEMORY_DUMP			0xf7

/* event type */
#define	EV_NONE						0x0000		/* no event and message */
#define	EV_MSG_RDY					0x0001		/* message ready event */

/*------------------ end of Public Macro Definition --------------------------*/


/****************************/
/* Public Type or Structure	*/
/****************************/

typedef struct task_control_block_type
{
	uint16_t event;						/* 16 event bits*/
	uint8_t msg_count;					/* number of messages ready*/
	pfunct_Os task_ptr[Os_Event_PerTask];
} OS_TCB_T;

typedef struct timer_config
{
	uint8_t status;			/* bit7=1 -- periodic, bit0=1 --- start*/
	uint16_t count;			/* remaining count */
	uint16_t period;			/* period of the timer*/
	uint16_t offset;			/* offset of the timer*/
	uint8_t notify_task_id;	/* the task to be notified when the timer expires*/
	uint16_t notify_event;	/* notify event for timer out*/
}OS_TMR_T;

typedef struct message_buffer_type
{
	uint8_t task_id;
	uint8_t message_data[3];
}OS_MSG_T;

/*------------------ end of Public Type or Structure -------------------------*/


/*******************/
/* Public Variable */
/*******************/
/*-- declear timer,message and task used by the os kernel --*/
extern OS_TMR_T os_timer[MAX_TIMER_NUMBER][Os_Event_PerTask];				/* task config timer*/
extern OS_MSG_T os_msg_q[MAX_MESSAGE_NUMBER];					/* message queue*/
extern OS_TCB_T os_task_tcb[MAX_TASK_NUMBER];				/* task control block*/
extern uint8_t os_tick_count;				/* os timer tick counter*/

/*------------------ end of Public Variable ----------------------------------*/


/*****************************/
/* Public Function Prototype */
/*****************************/

/*******************************************************************************
 * FUNCTION :  void os_init()
 * DESCRIPTION :  Initialize some tasks to run when OS is active.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
extern void Os_Init(void);

/*******************************************************************************
 * FUNCTION :  void os_start()
 * DESCRIPTION :  start os task.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
extern void Os_Start(void);


/*******************************************************************************
 * FUNCTION :  os_schedule()
 * DESCRIPTION :  select a ready task to run. This function has to be called
 				  whenever the system is idle.
                  It will always select the highest priority ready task.
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
extern void Os_Schedule(void);

/*******************************************************************************
 * FUNCTION :  os_tick()
 * DESCRIPTION :  This function is called from the system timer ISR.
                  It will update the task schedule timer
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 *
 ******************************************************************************/
extern void Os_Tick(void);

/*******************************************************************************
 * FUNCTION :  os_timer_start_one_shot()
 * DESCRIPTION :  start the timer one shot
 * INPUT       :  os_timer_id --- which timer
                  notify_event ---- event to be sent when timer expires
				  period --- time period
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 ******************************************************************************/
extern uint8_t Os_Timer_Start_One_Shot(uint8_t os_timer_id, uint16_t notify_event);

/*******************************************************************************
 * FUNCTION :  os_timer_start_periodic()
 * DESCRIPTION :  start the periodic timer
 * INPUT       :  os_timer_id --- which timer
                  notify_event ---- event to be sent when timer expires
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 ******************************************************************************/
extern uint8_t Os_Timer_Start_Periodic(uint8_t  os_timer_id, uint16_t notify_event);

/*******************************************************************************
 * FUNCTION :  os_timer_stop()
 * DESCRIPTION :  stop the  timer
 * INPUT       :  os_timer_id --- which timer
               :  notify_event ---- event to be sent when timer expires
 * OUTPUT      :
 * RETURN      :
 * WARNINGS:
 ******************************************************************************/
extern uint8_t Os_Timer_Stop(uint8_t os_timer_id, uint16_t notify_event);

/*******************************************************************************
 * FUNCTION :  os_message_send()
 * DESCRIPTION :  send a message to a specific task
 * INPUT       :  task_id --- where to send
                  msg_data ---- data to be sent. msg_data lenght must be 3 bytes
 * OUTPUT      :
 * RETURN      :  0 -- success;  ~0 -- error code
 * WARNINGS:  message will be copied to the system message bufffer
              should not be called from ISR
 *
 ******************************************************************************/
extern uint8_t Os_Message_Send(uint8_t task_id, uint8_t *msg_data);

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
extern uint8_t Isr_Message_Send(uint8_t task_id, uint8_t *msg_data);

/*******************************************************************************
 * FUNCTION :  os_message_get()
 * DESCRIPTION :  get a message to a specific task's message queue
 * INPUT       :   task_id ---where to get the message
 * OUTPUT      :   msg_buffer --- the buffer to receive the message. buffer lenght must be 3 bytes
 * RETURN      :  positive value ( >= 0) -- success, and number of unread msg still in
                                            the system buffer;
                  negative value -- error code
 * WARNINGS:  	 should not be called from ISR
 *
 ******************************************************************************/
 extern char Os_Message_Get(uint8_t task_id, uint8_t *msg_buffer);

/*******************************************************************************
* FUNCTION :  os_event_get(task_id)
* DESCRIPTION :	get the event flag of the specified task
* INPUT		 :	task_id --- which task
* OUTPUT 	 :
* RETURN 	 :	 event flag
* WARNINGS:	since the tasking model has to be cooperative, any task should not handle
			all the events at once. Therefore, event_get() will not clear the the task's
			event flag. The calling task should use event_clear(task_id,event_bit) to
			clear the event bit which it is handling. can't be called from isr
******************************************************************************/
extern uint16_t Os_Event_Get(uint8_t task_id);

/*******************************************************************************
 * FUNCTION :  isr_event_post (task_id, event)
 * DESCRIPTION :  post the event to the specified task from isr
 * INPUT       :  task_id --- which task
                  event -- event to post(bit-mapped)
 * OUTPUT      :
 * RETURN      :   none
 * WARNING:      the only way to post event to tasks from isr
 ******************************************************************************/
extern void Isr_Event_Post(uint8_t task_id, uint16_t event);

/*******************************************************************************
 * FUNCTION :  os_event_post(task_id, event)
 * DESCRIPTION :  post the event to the specified task
 * INPUT       :  task_id --- which task
                  event -- event to post(bit-mapped)
 * OUTPUT      :
 * RETURN      :   none
 * WARNING:      can't be called by isr
 ******************************************************************************/
extern void Os_Event_Post(uint8_t task_id, uint16_t event);

/*******************************************************************************
 * FUNCTION :  event_clear(task_id, event_it)
 * DESCRIPTION :  get the event flag of the specified task
 * INPUT       :  task_id --- which task
                  event_bit -- the '1" bits will be cleared
 * OUTPUT      :
 * RETURN      :   none
 * WARNING:      can't called by isr
 ******************************************************************************/
extern void Os_Event_Clear(uint8_t task_id, uint16_t event);

/*******************************************************************************
 * FUNCTION :  os_shutdown(void)
 * DESCRIPTION :  shut down os
 * INPUT       :
 * OUTPUT      :
 * RETURN      :
 ******************************************************************************/
extern void Os_Shutdown(void);

/*------------------ end of Public Function Prototype ------------------------*/

#endif    /*  _OS_H_   */

