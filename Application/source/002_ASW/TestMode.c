/*
 * TestMode.c
 *
 *  Created on: 2021��10��28��
 *      Author: huangh
 */
#include "Types.h"
#include "Typedef.h"
#include "AppIF.h"
#include "relay.h"
#include "hallpos.h"
#include "motor.h"
#include "sysfunc.h"
#include "switch.h"
#include "appl_const.h"
#include "complier_sw.h"
#include "appif.h"
#include "param.h"
#include "TestMode.h"


union t_intbyte
{
    struct
    {
        uint8_t HI_Byte ;
        uint8_t LO_Byte ;
    } byte;
   uint16_t word;
};


extern volatile uint16_t HA_ui_PWTimeEnd;

extern  volatile uint16_t   HA_ui_WinPos;

extern  uint16_t   AP_ui_PWAct;


#define   TM_CON_60ms           30              //60ms

#define   TM_CON_TestTimeoutLimit 30000         //60S=30000*2ms  60Sʱ�䴰

#define   TM_CON_EntryTimeoutLimit 1000         //2S=1000*2ms   2Sʱ�䴰

volatile uint16_t  TM_ui_TestTimeCnt;       /*����ģʽ ʱ����� 45Sʱ�䴰*/

volatile uint8_t TM_uc_SWUp_Cnt;          /*switch up filter count*/

volatile uint8_t TM_uc_SWDown_Cnt;        /*switch down filter count*/

volatile uint8_t TM_uc_WindowUp_Cnt;      /*up times*/

volatile uint8_t TM_uc_WindowDown_Cnt;    /*down times*/

volatile T_FLAG8  TM_T8_Flag1;

volatile T_FLAG8  RT_T8_statusflag;     /*status flag*/

uint8_t  RT_uc_a_connect_FLAG;    /*relay A connect flag*/

uint8_t  RT_uc_b_connect_FLAG;	  /*relay B connect flag*/

uint8_t  RT_uc_a_break_FLAG ;     /*relay A stop flag*/

uint8_t  RT_uc_b_break_FLAG ;    /*relay B stop flag*/

uint8_t RT_uc_a_connect_time;  /*relay A connect time*/

uint8_t RT_uc_b_connect_time;  /*relay B connect time*/

uint8_t RT_uc_a_connectCnt;    /*relay A connect count*/

uint8_t RT_uc_b_connectCnt;    /*relay B connect count*/

uint8_t RT_uc_a_break_time;    /*relay A break time*/

uint8_t RT_uc_b_break_time;    /*relay B break time*/

uint8_t RT_uc_a_breakCnt;      /*relay A break count */

uint8_t RT_uc_b_breakCnt;      /*relay B break count */

uint8_t RT_uc_a_feedback;      /*relay A ����״̬����*/

uint8_t RT_uc_b_feedback;      /*relay B ����״̬����*/

uint16_t RT_ui_pw_tmp;           /*��ǰ��׽����HALLֵ����*/

uint16_t RT_ui_pw_act;           /*HALL����*/

uint16_t RT_ui_pw_begin;         /*ǰһ�β�׽����HALLֵ*/

#define RT_CON_SUC  0x01

#define RT_CON_ERR  0x04



uint8_t   RT_uc_buf_pt;      /*������ָ��*/

#define RT_CON_BUFFER_SIZE 60      /*������size*/

uint8_t   RT_uc_TestBuf[RT_CON_BUFFER_SIZE][2]  ; /*������*/

uint8_t   RT_uc_DCMBuf[10]  ; /*������*/

uint16_t RT_ui_HALLCNT;

union t_intbyte  intbyte;

/*O_WINACT_PIN1 AP_bi_MonitorRelA--- GET_SIGNAL_RLY_A --RT_uc_a_connect_FLAG*/
/*O_WINACT_PIN2 AP_bi_MonitorRelB--- GET_SIGNAL_RLY_B --RT_uc_b_connect_FLAG*/

void RT_init(void);

uint8_t RT_relaycheck(uint8_t relay_fd,uint8_t r_flag,uint8_t* r_cnt,uint8_t *r_value);

void RT_relaytest(void);

void  RT_HallDataLoad(void);

void  RT_OtherTestDataLoad(void);

void   RT_ClearBUF(void);

uint16_t tup,tdn,texp,tbat6;

#define ManUp_active      (tup < tbat6)
#define ManDown_active    (tdn < tbat6 )


#define   specialmode_hardware_entry   ((tup < tbat6) | (tdn <tbat6 ))

void specialmode_entry(void);
/******************************************************************************
* Description:                                                                *
*                                                                             *
* specialmode_entry(void)                                                        *
*                                                                             *
* Test mode hardware entrance:Both up and down are active for sometime        *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
/*****************************************************************/
/******����ģʽ���Ӳ�������жϣ�UP��DOWN����ͬʱΪ�͵�ʱ�䡵110ms****/
/*****************************************************************/
void specialmode_entry(void)
{
  /*
   *
  uint16_t temp;


	tup = getKeyAD();
	texp = getExpIPAD();
	tdn = getDwonIPAD();
	tbat6 = bsc_AD_Get_Raw_Bat()/6 ;

    TM_init();   //����ģʽ������ʼ��

     //both up and down are active,then wait for 110ms, above 5ms

     temp = 0;

     //whole cycles  (111.281ms+4.658(above)=115.939ms),

     while(!specialmode_hardware_entry)

     {
    		tup = getKeyAD();
    		texp = getExpIPAD();
    		tdn = getDwonIPAD();
    		tbat6 = bsc_AD_Get_Raw_Bat()/6 ;
       MCR_DELAY_NOP9;
       MCR_DELAY_NOP9;
       MCR_DELAY_NOP9;

       temp++;

       bsc_FeedCOP();

       if(temp>10000)  break;

     }
     //����ѭ��ʵ��110.5ms���ӳ���λ����ʼ����ɹ�7.3ms ,���Ϲ�117.8ms.

     if((temp>=10000)&&(!specialmode_hardware_entry))

     {
       temp = 0;


       //test mode entry

	TM_bi_HWEntryAccess=1;


      }

*/
}


/**************only for test motor ************/
/******************************************************************************
* Description:                                                                *
*                                                                             *
* TM_init()                                                                   *
*                                                                             *
* Test mode variables initialize                                              *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
/*����ģʽ��������ʼ�� */
void TM_init()
{

    TM_ui_TestTimeCnt=0;

    TM_uc_SWUp_Cnt=0;

    TM_uc_SWDown_Cnt=0;

    TM_uc_WindowUp_Cnt=0;

    TM_uc_WindowDown_Cnt=0;



    TM_T8_TestStatusFlag=0;



}

bool_t TM_GetTMStatus(void){

	return TM_bi_beingTestMode;
}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* TM_Entry()                                                                  *
*                                                                             *
* Test mode enter:                                                            *
* if TestModeHardwareEntrance is right,then open 2senconds time window        *
* 1>detect 60ms down inactive and up active                                   *
* 2>detect 60ms up inactive and down active                                   *
* 3>detect 60ms down inactive and up active                                   *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
/*����ģʽ���*/
/*һ�ϵ磬UP��DOWNͬʱ��Ч��110ms,��ʼ����ģʽ�������*/
/*����ģʽ������2S�� */
/*1> ��60ms down inac &&up active */
/*2> ��60ms up inactive&&down ac  */
/*3> ��60ms down inac &&up active */
void TM_Entry()
{
	tup = getKeyAD();
	texp = getExpIPAD();
	tdn = getDwonIPAD();
	tbat6 = bsc_AD_Get_Raw_Bat()/6 ;


        TM_ui_TestTimeCnt++;



         if(TM_ui_TestTimeCnt<TM_CON_EntryTimeoutLimit)  //  2s VCAR
        {

            if( ManUp_active && (!ManDown_active ))  //up act&&down inactive
            {

                    if(TM_uc_SWDown_Cnt<250)    //in case over
                    {

                        TM_uc_SWDown_Cnt++;

                    }

            }
            else if(ManDown_active && (!ManUp_active))  //down act &&up inactive
            {

                   if(TM_uc_WindowDown_Cnt>0)
                    {

                        if(TM_uc_SWUp_Cnt<250)//in case over
                        {

                            TM_uc_SWUp_Cnt++;

                        }

                    }

            }
            else  if(ManDown_active &&  ManUp_active ) //down active&&up active
            {
                if(TM_uc_SWDown_Cnt>=TM_CON_60ms)                //down ��Ч��60ms
                {

                    TM_uc_WindowDown_Cnt ++;

                }

                TM_uc_SWDown_Cnt=0;

                if(TM_uc_SWUp_Cnt>=TM_CON_60ms)                 //up ��Ч��60ms
                {

                    TM_uc_WindowUp_Cnt++;

                }

                TM_uc_SWUp_Cnt=0;

                if((TM_uc_WindowDown_Cnt>=2)&&(TM_uc_WindowUp_Cnt>=1))//����ģʽ�����������
                {

                	Motor_OFF();

                    TM_init();

                    HP_Normalize_ExitCall();

                    TM_bi_beingTestMode=1;

                }
            }
            else
            {

                TM_init();

            }
        }

        else
        {

            TM_init();

        }

      }
/******************************************************************************
* Description:                                                                *
*                                                                             *
* TM_Progress()                                                               *
*                                                                             *
* Test mode:open 60seconds time window                                        *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
/*���Թ���,����60Sʱ�䴰*/
void TM_Progress()
{



       TM_ui_TestTimeCnt++;

       if(TM_ui_TestTimeCnt>TM_CON_TestTimeoutLimit) //����60S���˳�����ģʽ���ָ�δ��ʼ��״̬
       {

           //Motor_OFF;
           //MC_MCtrl_Stop |=c_pos_prio;					//��ֹͣ�����־
    	   MOT_SetStop(HallPosConfig.u16_pos_priority);
           TM_init();

           HP_Normalize_ExitCall();

       }


}

/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_init()                                                                   *
*                                                                             *
* relay test variables initialize                                              *

*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return: none                                                                *
*                                                                             *
******************************************************************************/
/*relay ������ʼ��*/

void RT_init()
{
    uint8_t i,j;
    RT_T8_statusflag.by=0;

    RT_uc_a_connect_FLAG=0;

    RT_uc_b_connect_FLAG=0;

    RT_uc_a_break_FLAG=0 ;

    RT_uc_b_break_FLAG=0 ;

    RT_uc_a_connect_time = 0;

    RT_uc_b_connect_time=0;

    RT_uc_a_connectCnt=0;

    RT_uc_b_connectCnt=0;

    RT_uc_a_break_time=0;

    RT_uc_b_break_time=0;

    RT_uc_a_breakCnt=0;

    RT_uc_b_breakCnt=0;

    RT_uc_a_feedback=0;

    RT_uc_b_feedback=0;

    for(i=0;i<60;i++) {

        for(j=0;j<2;j++)
        {

            RT_uc_TestBuf[i][j]=0;

        }
    }
    RT_uc_buf_pt=0;

    RT_ui_pw_tmp=0;

    RT_ui_pw_act=0;

    RT_ui_pw_begin=0;
}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_relaycheck                                                               *
*                                                                             *
* relay connect time and break time check                                     *
*                                                                             *
* Parameters: RT_T8_statusflag,                                               *
*                                                                             *
* Return: RT_uc_a_connect_time,RT_uc_a_connect_time,                          *
*         RT_uc_a_break_time,RT_uc_b_break_time                               *
******************************************************************************/
/*��Ƭ������������̵�����������״̬��ͬʱ�����м�ʱ**/

uint8_t RT_relaycheck(uint8_t relay_fd,uint8_t r_flag,uint8_t *r_cnt,uint8_t *r_value)
{

    if(!relay_fd)
    {
       r_flag = 0;

       if(*r_cnt > 0)
       {
            *r_value = *r_cnt;
       }

    }
    else
    {
        if(!r_flag)
        {
           r_flag=1;

           *r_cnt=0;
        }
    }
    return r_flag;
}

/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_relaytest()                                                              *
*                                                                             *
* use  RT_relaycheck()                                                        *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return:                                                                     *
*                                                                             *
******************************************************************************/
/*��Ƭ������������̵�����������״̬��ͬʱ�����м�ʱ**/

void RT_relaytest()
{
	// ���̵���A������״̬���߼�״̬�Ƿ�һ��
    if(REL_GetRelPhySts(REL_A)^REL_GetRelLogiSts(REL_A)) RT_uc_a_feedback=0x01; // ״̬��ͬ
    /*��Ƭ������������̵�����������״̬��ͬ*/
    else RT_uc_a_feedback=0;  // ״̬��ͬ
    /*��Ƭ������������̵�����������״̬��ͬ*/

    // ���̵���B
    if(REL_GetRelPhySts(REL_B)^REL_GetRelLogiSts(REL_B)) RT_uc_b_feedback=0x01;/*״̬��ͬ*/
    else RT_uc_b_feedback=0;                                   					/*״̬��ͬ*/
    // ���ݵ���ķ�����в�ͬ�Ĵ���
    if(C_MOTOR_DIR==CMOTOR_DIRECTION)
    {
        if(Motor_bi_Open)  // �������� - ����
        {
            RT_uc_b_connect_FLAG=RT_relaycheck( RT_uc_b_feedback,RT_uc_b_connect_FLAG,&RT_uc_b_connectCnt,&RT_uc_b_connect_time);

            if(RT_uc_b_connect_FLAG) RT_bi_b_connect_pre=1;
        }
        if(Motor_bi_Close)  // �������� - ����
        {
            RT_uc_a_connect_FLAG=RT_relaycheck( RT_uc_a_feedback,RT_uc_a_connect_FLAG,&RT_uc_a_connectCnt,&RT_uc_a_connect_time);

            if(RT_uc_a_connect_FLAG) RT_bi_a_connect_pre=1;
        }
    }
    else
    {
        if( Motor_bi_Open)  //����
        {
            RT_uc_a_connect_FLAG= RT_relaycheck( RT_uc_a_feedback,RT_uc_a_connect_FLAG,&RT_uc_a_connectCnt,&RT_uc_a_connect_time);

            if(RT_uc_a_connect_FLAG) RT_bi_a_connect_pre=1;
        }
        if(Motor_bi_Close)  //����
        {
            RT_uc_b_connect_FLAG=RT_relaycheck( RT_uc_b_feedback,RT_uc_b_connect_FLAG,&RT_uc_b_connectCnt,&RT_uc_b_connect_time);

            if(RT_uc_b_connect_FLAG) RT_bi_b_connect_pre=1;
        }
    }
 if(Motor_bi_Stop)   //�ͷ�
    {
       RT_uc_a_break_FLAG=RT_relaycheck(RT_uc_a_feedback,RT_uc_a_break_FLAG,&RT_uc_a_breakCnt,&RT_uc_a_break_time);

       if(RT_uc_a_break_FLAG) RT_bi_a_break_pre=1;

       RT_uc_b_break_FLAG=RT_relaycheck(RT_uc_b_feedback,RT_uc_b_break_FLAG,&RT_uc_b_breakCnt,&RT_uc_b_break_time);

       if(RT_uc_b_break_FLAG) RT_bi_b_break_pre=1;
    }
}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_HallDataLoad(void)                                                       *
*                                                                             *
* load hall data,wait for sending                                             *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return:                                                                     *
*                                                                             *
******************************************************************************/
/*����HALL���ݣ��ȴ�����*/
void  RT_HallDataLoad(void)

{


        /* RT_ui_pw_tmp = tmp_ui_Var ;

         RT_ui_pw_act = RT_ui_pw_tmp - RT_ui_pw_begin;

         RT_ui_pw_begin = RT_ui_pw_tmp;*/

         intbyte.word = AP_ui_PWAct;

         RT_uc_TestBuf[RT_uc_buf_pt][0] = intbyte.byte.HI_Byte; //pulse

         RT_uc_TestBuf[RT_uc_buf_pt][1] = intbyte.byte.LO_Byte;

         RT_uc_buf_pt++;

         if(RT_uc_buf_pt>= (RT_CON_BUFFER_SIZE-5))
         {

           RT_uc_buf_pt = 0;

         }



}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_OtherTestDataLoad(void)                                                  *
*                                                                             *
* load other test data,wait for sending                                       *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return:                                                                     *
*                                                                             *
******************************************************************************/
/*������Ե��������ݵ��������У��ȴ�����*/

void  RT_OtherTestDataLoad(void)
{

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-5][0] = RT_uc_buf_pt;

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-4][0] = 0;  //�¶�ֵ���ֽ�

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-4][1] = (uint8_t)bsc_AD_Get_Raw_Thermal(); //AD_uc_Temperature;  //�¶�ֵ���ֽ�

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-3][0] = RT_uc_a_connect_time;    //�̵���A����ʱ��

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-3][1] = RT_uc_b_connect_time;    //�̵���B����ʱ��

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-2][0] = RT_uc_a_break_time;      //�̵���A�Ͽ�ʱ��

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-2][1] = RT_uc_b_break_time;      //�̵���B�Ͽ�ʱ��

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][0] = (RT_T8_statusflag.by & 0x0F);     //��4λ

         if(SY_bi_Enable_Active)

	       RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][0] |= 0x80;  //0b 1000 0000   //ʹ���ź� ���λ

	       if(bsc_Get_EnIp()==0)

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][0] |= 0x40;  //0b 0100 0000    //express signal��6λ

	     /*if(lin_bi_childlock & 1)

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][0] |= 0x20;  //0b 0010 0000    //ͯ���ź� ��5λ */
         if(Motor_bi_Prv_Updir)

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][0] |= 0x20;  //0b 0010 0000    //���������5λ

         RT_uc_TestBuf[RT_CON_BUFFER_SIZE-1][1] = AD_uc_MotorVoltage; //voltage����ѹֵ


}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_OtherTestDataLoad(void)                                                  *
*                                                                             *
* load other test data,wait for sending                                       *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return:                                                                     *
*                                                                             *
******************************************************************************/
/*������Ե��������ݵ��������У��ȴ�����*/

void  RT_OtherTestDataLoad_2(void)
{
    //VOLT
   RT_uc_DCMBuf[0] = AD_uc_MotorVoltage/10; //voltage����ѹֵ
   //ʹ���ź�
   if(SY_bi_Enable_Active)
   RT_uc_DCMBuf[1] = 0x01;
   else
   RT_uc_DCMBuf[1] = 0x00;
   //�Զ��ź�
   if((SW_ub_KeyAct&0x04)==0x04)
   RT_uc_DCMBuf[2] = 0x01;
   else
   RT_uc_DCMBuf[2] = 0x00;
   //HALL
   RT_uc_DCMBuf[3] = (uint8_t)RT_ui_HALLCNT;
   RT_uc_DCMBuf[4] = (uint8_t)(RT_ui_HALLCNT>>8);

   //direction
   if(Motor_bi_Prv_Updir)
   RT_uc_DCMBuf[5] = 0x01;
   else  RT_uc_DCMBuf[5] = 0x00;

   //RELAY
   if( RT_T8_statusflag.by & 0x0F ==0x0F)
   {
      if((RT_uc_a_connect_time<10) && (RT_uc_b_connect_time<10)&&
         (RT_uc_a_break_time<10) && (RT_uc_b_break_time<10))
      {
        RT_uc_DCMBuf[6]= RT_CON_SUC;
      }
      else
      {
        RT_uc_DCMBuf[6]= RT_CON_ERR;
      }
   }
   else  RT_uc_DCMBuf[6]=RT_CON_ERR;


}
/******************************************************************************
* Description:                                                                *
*                                                                             *
* RT_ClearBUF(void)                                                           *
*                                                                             *
* clear data buffer                                                           *
*                                                                             *
* Parameters:                                                                 *
*                                                                             *
* Return:                                                                     *
*                                                                             *
******************************************************************************/
//����������ݻ�����
void   RT_ClearBUF(void)
{
    uint16_t temp;

    if ( !Motor_bi_Running)

   {
        RT_uc_buf_pt=0;
        for(temp=0;temp<RT_CON_BUFFER_SIZE;temp++)
        {
             RT_uc_TestBuf[temp][0]=0;
             RT_uc_TestBuf[temp][1]=0;
        }
        for(temp=0;temp<10;temp++)
        RT_uc_DCMBuf[temp]=0;
        RT_ui_HALLCNT=0;
   }

}


