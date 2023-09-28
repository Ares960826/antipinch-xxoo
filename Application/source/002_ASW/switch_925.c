
#include "complier_sw.h"  /* compiler switches                    */
#include "typedef.h"

  
#include "appl_const.h"


#include "Debug.h"
#include "switch.h"
#include "motor.h"
#include "keyport.h"
#include "sysfunc.h"
#include "apfunc.h"
#include "AppIF.h"

extern void window_stop(void) ;

extern uint16_t    AP_ui_AP_off;
//#include "defram.h" 
volatile T_FLAG8  SW_T8_Flag;       //zap 20100730



unsigned char SW_ub_KeyAct = 0;
unsigned char SW_ub_KeyOld = 0;
unsigned char SW_ub_KeyErr = 0;

unsigned char SW_ub_Lin_Func = 0;
unsigned char SW_ub_Local_Func = 0;
unsigned char SW_ub_Win_Status = 0;
unsigned char SW_ub_Win_Func = 0;
unsigned char SW_ub_Win_Func_Old=0;


static unsigned int SW_ui_DebounceUp = 0;
static unsigned int SW_ui_DebounceDown = 0;
static unsigned int SW_ui_DebounceExpress = 0;
static unsigned int SW_ui_AutoTimeCnt = 0;
static unsigned int SW_ui_DebounceIgnite = 0;


unsigned char SW_uc_EnableCriticalValue=0;  /*Enable信号临界值临时存放*/

unsigned int lin_ui_cnt;
unsigned char lin_uc_command_old;
unsigned char lin_uc_err;
unsigned char SW_uc_Status;  
unsigned char lin_uc_command_pre;
unsigned char SW_uc_command_pre;
unsigned char SW_uc_keyinputold;


#define SWStatusIDLE 0
#define SWStatus1    1  
#define SWStatus2    2  



void key_init(void);
void key(void);
void key_debounce(unsigned int *keycnt,unsigned char *inpkey,unsigned char keymask);
void key_checkstop(void);
void key_setmotorprio(void);

//zap 20100730
#define C_DEBOUNCE_ENABLE_ACTIVE     15   //30ms 
#define C_DEBOUNCE_ENABLE_INACTIVE   5    //10ms 
#define C_RKE_VALID_TIME             10000//10000*2ms=20S
#define C_DOORTYPE_FL                0x20 //FL
#define C_RKEDelay_BasicT            25   //车窗依次动作延时基数 2ms*25*c_RKEDelay（appl_const.h）


//zap 20100730
#define C_INPUT_STATES_MAX	26 
#define C_WIN_STATES_MAX	  17 
#define C_INPUT_SWBothAct   5


const unsigned char PRIO_TABLE_LIN[C_INPUT_STATES_MAX * C_WIN_STATES_MAX] = 
{

/*00*/		/*| 			0 		1 		2 		3 		4 		  5      6 		  7      8 		9 		10 		11 		12		13		14		15		16		*/
/*00*/		/*|							|		                Switch				             |     				LIN							              |		both 	  	*/
/*00*/		/*Sw	Lin		idle	stop	SMU		SMD		SMU2	SAU    SMD2	  SAD    LMU		LMD		LAU0	LAU	  LAD0	LAD	BMU		BMD	|	err	*/
/*00*/		      			0,		0,		1,		1,		5,		5,      7,		7,      1,		1,		11,		11,		13,		13,		1,		1,		1,  
/*01*/		/*		MU*/	8,		1,		1,		1,		5,		5,      7,		7,      8,		1,		1,		1,		1,		1,		1,		1,		1,   
/*02*/		/*		MD*/	9,		1,		1,		1,		1,		1,      7,		7,      1,		9,		1,		1,		1,		1,		1,		1,		1,   
/*03*/		/*		AU*/	10,		1,		1,		1,		5,		5,      7,		7,      10,		1,		10,		1,		1,		1,		1,		1,		1,   
/*04*/		/*		AD*/	12,		1,		1,		1,		5,		5,      7,		7,      1,		12,		1,		1,		12,		1,		1,		1,		1,   
/*05*/		/*MU	MU*/	1,		1,		2,		1,		1,		1,      1,		1,      2,		1,		1,		1,		1,		1,		1,		1,		1,  
/*06*/		/*MU	MD*/	1,		1,		1,		1,		1,		1,      1,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*07*/		/*MU	AU*/	1,		1,		2,		1,		1,		1,      1,		1,      1,		1,		2,		1,		1,		1,		1,		1,		1,  
/*08*/		/*MU	AD*/	1,		1,		2,		1,		1,		1,      1,		1,      1,		1,		1,		1,		2,		1,		1,		1,		1,  
/*09*/		/*MD	MU*/	1,		1,		1,		3,		1,		1,      1,		1,      3,		1,		1,		1,		1,		1,		1,		1,		1,  
/*10*/		/*MD	MD*/	1,		1,		1,		3,		1,		1,      1,		1,      1,		3,		1,		1,		1,		1,		1,		1,		1,  
/*11*/		/*MD	AU*/	1,		1,		1,		3,		1,		1,      1,		1,      1,		1,		3,		1,		1,		1,		1,		1,		1,  
/*12*/		/*MD	AD*/	1,		1,		1,		3,		1,		1,      1,		1,      1,		1,		1,		1,		3,		1,		1,		1,		1,  
/*13*/		/*AU	MU*/	1,		1,		4,		1,		4,		1,      1,		1,      4,		1,		1,		1,		1,		1,		1,		1,		1,  
/*14*/		/*AU	MD*/	1,		1,		1,		1,		1,		1,      1,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*15*/		/*AU	AU*/	1,		1,		4,		1,		4,		1,      1,		1,      1,		1,		4,		1,		1,		1,		1,		1,		1,  
/*16*/		/*AU	AD*/	1,		1,		4,		1,		4,		1,      1,		1,      1,		1,		1,		1,		4,		1,		1,		1,		1,  
/*17*/		/*AD	MU*/	1,		1,		1,		6,		1,		1,      6,		1,      6,		1,		1,		1,		1,		1,		1,		1,		1,  
/*18*/		/*AD	MD*/	1,		1,		1,		6,		1,		1,      6,		1,      1,		6,		1,		1,		1,		1,		1,		1,		1,  
/*19*/		/*AD	AU*/	1,		1,		1,		6,		1,		1,      6,		1,      1,		1,		6,		1,		1,		1,		1,		1,		1,  
/*20*/		/*AD	AD*/	1,		1,		1,		6,		1,		1,      6,		1,      1,		1,		1,		1,		6,		1,		1,		1,		1,  
/*00*/		//---------------------------------------------------------------------------------------------------------------------------/
/*21*/		/*MU	*/		2,		1,		2,		1,		1,		1,      1,		1,      2,		1,		2,		2,		2,		2,		1,		1,		1,   
/*22*/		/*MD	*/		3,		1,		1,		3,		1,		1,      1,		1,      3,		3,		3,		3,		3,		3,		1,		1,		1,   
/*23*/		/*AU	*/		4,		1,		4,		1,		4,		1,      1,		1,      4,		1,		4,		4,		4,		4,    1,		1,		1,  
/*24*/		/*AD	*/		6,		1,		1,		6,		1,		1,      6,		1,      6,		6,		6,		6,		6,		6,		1,		1,		1,  
/*25*/		/*Both act*/1,		1,		1,		1,		1,		1,      1,		1,      1,		1,		1,		1,		1,		1,		1,		1,		1,  

			//-------------------------------------------------------------------------------------------------------------------------------/

};

const unsigned char PRIO_TABLE_SW[C_INPUT_STATES_MAX * C_WIN_STATES_MAX] = 
{

/*00*/		/*| 			0 		1 		2 		3 		4 		  5      6 		  7      8 		9 		10 		11 		12		13		14		15		16		*/
/*00*/		/*|							|		                Switch				             |     				LIN							              |		both 	  	*/
/*00*/		/*Sw	Lin		idle	stop	SMU		SMD		SMU2	SAU    SMD2	  SAD    LMU		LMD		LAU0	LAU 	LAD0	LAD	BMU		BMD	|	err	*/
/*00*/		      			0,		0,		1,		1,		5,		5,      7,		7,      1,		1,		11,		11,		13,		13,		1,		1,		1,  
/*01*/		/*		MU*/	8,		1,		8,		1,		8,		8,      8,		8,      8,		1,		1,		1,		1,		1,		1,		1,		1,   
/*02*/		/*		MD*/	9,		1,		9,		9,		9,		9,      9,		9,      1,		9,		1,		1,		1,		1,		1,		1,		1,   
/*03*/		/*		AU*/	10,		1,		10,		1,		10,		10,     10,		10,     10,		1,		10,		1,		1,		1,		1,		1,		1,   
/*04*/		/*		AD*/	12,		1,		12,		12,		12,		12,     12,		12,     1,		12,		1,		1,		12,		1,		1,		1,		1,   
          /*LIN SW  */
/*05*/		/*MU	MU*/	1,		1,		8,		1,		1,		1,      1,		1,      8,		1,		1,		1,		1,		1,		1,		1,		1,  
/*06*/		/*MU	MD*/	1,		1,		1,		3,		1,		1,      1,		1,      1,		1,		1,		1,		1,		1,		1,		1,		1,  
/*07*/		/*MU	AU*/	1,		1,		8,		1,		8,		1,      1,		1,      8,		1,		1,		1,		1,		1,		1,		1,		1,  
/*08*/		/*MU	AD*/	1,		1,		1,		8,		1,		1,      8,		1,      8,		1,		1,		1,		1,		1,		1,		1,		1,  
/*09*/		/*MD	MU*/	1,		1,		9,		1,		1,		1,      1,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*10*/		/*MD	MD*/	1,		1,		1,		9,		1,		1,      1,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*11*/		/*MD	AU*/	1,		1,		9,		1,		9,		1,      1,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*12*/		/*MD	AD*/	1,		1,		1,		9,		1,		1,      9,		1,      1,		9,		1,		1,		1,		1,		1,		1,		1,  
/*13*/		/*AU	MU*/	1,		1,		10,		1,		1,		1,      1,		1,      10,		1,		10,		1,		1,		1,		1,		1,		1,  
/*14*/		/*AU	MD*/	1,		1,		1,		3,		1,		1,      1,		1,      1,		1,		1,		1,		1,		1,		1,		1,		1,  
/*15*/		/*AU	AU*/	1,		1,		10,		1,		10,		1,      1,		1,      10,		1,		10,		1,		1,		1,		1,		1,		1,  
/*16*/		/*AU	AD*/	1,		1,		1,		10,		1,		1,      10,		1,      10,		1,		10,		1,		1,		1,		1,		1,		1,  
/*17*/		/*AD	MU*/	1,		1,		12,		1,		1,		1,      1,		1,      1,		12,		1,		1,		12,		1,		1,		1,		1,  
/*18*/		/*AD	MD*/	1,		1,		1,		12,		1,		1,      1,		1,      1,		12,		1,		1,		12,		1,		1,		1,		1,  
/*19*/		/*AD	AU*/	1,		1,		12,		1,		12,		1,      1,		1,      1,		12,		1,		1,		12,		1,		1,		1,		1,  
/*20*/		/*AD	AD*/	1,		1,		1,		12,		1,		1,      12,		1,      1,		12,		1,		1,		12,		1,		1,		1,		1,  
/*00*/		// Sw---------------------------------------------------------------------------------------------------------------------------/
/*21*/		/*MU	*/		2,		1,		2,		1,		1,		1,      1,		1,      1,		1,		11,		11,		13,		13,		1,		1,		1,   
/*22*/		/*MD	*/		3,		1,		1,		3,		1,		1,      1,		1,      1,		1,		1,		1,		13,		13,		1,		1,		1,   
/*23*/		/*AU	*/		4,		1,		4,		1,		4,		1,      1,		1,      1,		1,		11,		11,		13,		13,   1,		1,		1,  
/*24*/		/*AD	*/		6,		1,		1,		6,		1,		1,      6,		1,      1,		1,		11,		11,		13,		13,		1,		1,		1,  
/*25*/		/*Both act*/1,		1,		1,		1,		1,		1,      1,		1,      1,		1,		1,		1,		1,		1,		1,		1,		1,  

			//-------------------------------------------------------------------------------------------------------------------------------/

};


#define C_SWITCH_DECODE_MAX 17

#define DECODE_STOP        0x00
#define DECODE_AUTO        0x04
#define DECODE_MAN_OPEN    0x01
#define DECODE_MAN_CLOSE   0x02
#define DECODE_AUTO_OPEN   0x05
#define DECODE_AUTO_CLOSE  0x06   
 
const unsigned char DECODE_TABLE[C_SWITCH_DECODE_MAX] = 
{
      DECODE_STOP,        /*  stop                    0   */
      DECODE_STOP,        /*  stop                    1   */
      DECODE_MAN_CLOSE,   /*  switch man up           2   */
      DECODE_MAN_OPEN,    /*  switch man down         3   */
      DECODE_MAN_CLOSE,   /*    4   */
      DECODE_AUTO_CLOSE,  /*    5   */
      DECODE_MAN_OPEN,    /*    6   */
      DECODE_AUTO_OPEN,   /*    7   */
      DECODE_MAN_CLOSE,   /*    8   */
      DECODE_MAN_OPEN,    /*    9   */
      DECODE_AUTO_CLOSE,  /*    10   */
      DECODE_AUTO_CLOSE,  /*    11   */
      DECODE_AUTO_OPEN,   /*    12  */
      DECODE_AUTO_OPEN,   /*    13	*/
      DECODE_STOP,   /*    14  */
      DECODE_STOP,    /*    15  */
      DECODE_STOP,		    /*	16	*/  //both switch active then stop window			
	   
};


const unsigned char CONVTAB[7] = {0, 2, 1, 5, 0, 4, 3};  //1/2/5/6 -> 2/1/4/3   (5:both active)


unsigned char convert(unsigned char input)
{
  switch(input)
  {
    case 0:
      SW_uc_keyinputold=0;
      break;
    case 1:
      if(SW_uc_keyinputold>0) input +=4;
      break;
    case 2:
      if(SW_uc_keyinputold>0) input +=4;
      break;
    case 5:
       SW_uc_keyinputold=input;
    break;
    case 6:
       SW_uc_keyinputold=input;
    break;
    default:
    break;
  }
	if (input <= 6) {
	  
		return CONVTAB[input];
	}
	else
		return 0;
	
}


void key_init_st()
{
    SW_ub_KeyAct = 0;
    SW_ub_KeyOld = 0;


    SW_ub_Lin_Func = 0;
    SW_ub_Local_Func = 0;
    SW_ub_Win_Status = 0;
    SW_ub_Win_Func = 0;
    SW_ub_Win_Func_Old=0;
    SW_ui_DebounceUp = 0;
    SW_ui_DebounceDown = 0;
    SW_ui_AutoTimeCnt = 0;

    SW_ui_DebounceIgnite = 0;
      
    SW_uc_EnableCriticalValue=0;  /*Enable信号临界值临时存放*/
    SW_T8_Flag.by=0;
    
    lin_ui_cnt=0;
    lin_uc_err =0;        
    lin_uc_command_old=0;
    SW_uc_command_pre=0;
    lin_uc_command_pre=0;
    
    SW_uc_keyinputold=0;
}
void key_init()
{
	key_init_st();

    SW_ub_KeyErr = 0;
}


void key_debounce(unsigned int *keycnt,unsigned char *inpkey,unsigned char keymask)
{
   /*!  
        
        \param SW_ub_KeyAct      记录经过滤波的按键状态
        \param SW_ub_KeyOld      记录经过滤波的并且有效的（没有出现按键粘连的）按键状态
   
        \param c_debounce_time 滤波时间
        \param c_key_error     当按键持续时间过长时，记录故障标志位的变量

  
   */
 //     注意这里使用了一个非常巧妙的策略，将有效位设置为１，无效位为０，这样将
   if (*inpkey != (SW_ub_KeyOld & keymask))     
   {
      
      SW_ub_KeyOld &=(0xff-keymask);   /*由keymask指定的位将被清零*/

      SW_ub_KeyOld|=*inpkey;       /*由keymask指定的位将等于inpkey*/

      if (*keycnt > c_debounce_time)
      {
         *keycnt = 1;
      }
      else
      {
         if (*keycnt > 1)
         {
            *keycnt = *keycnt - 1;
         }
         else
         {
            *keycnt = 1;
         }
      }
   }
   else
   {//若指定位 (SW_ub_KeyOld & keymask)已经和inpkey相等
      if (*keycnt > c_debounce_time)      
      {  //并且维持了c_debounce_time以上的时间
         //SW_ub_KeyAct &=(0xff-keymask);
         SW_ub_KeyAct &=(0x07-keymask);  /* clear 指定位  */
         SW_ub_KeyAct |=*inpkey ;     /* 将inpkey设定的状态传输给变量 SW_ub_KeyAct*/
         
         if (*keycnt > c_key_error)
         {
            //设置特定位的故障标志
            SW_ub_KeyErr |=*inpkey;   

         }
         else
         {
            //清除特定位的故障标志，
            SW_ub_KeyErr &=(0x07-keymask);
            *keycnt=*keycnt+1;
         }
      }
      else
      {
         *keycnt=*keycnt+1;
      }
   }
}
void lin_stick_detect(void)
{
   if(lin_uc_command_old!=SW_ub_Lin_Func) 
   {
     lin_ui_cnt=1;
     lin_uc_err =0;
   } 
   else
   {
     if(lin_ui_cnt<c_key_error) 
     {
        lin_ui_cnt++;
        
     } 
     else
     {
        lin_uc_err =SW_ub_Lin_Func;
     }
   }
   lin_uc_command_old=SW_ub_Lin_Func;
}


void key_read()
{
 //输入按键状态，输出SW_ub_Local_Func 
 
   uint8_t tmp1; 
   uint16_t tup,tdn,texp,tbat6;
   	tup = getKeyAD();
   	texp = getExpIPAD();
   	tdn = getDwonIPAD();
   	tbat6 = bsc_AD_Get_Raw_Bat()/6 ;

      if (tup < tbat6)
      {
         tmp1 = c_man_close;

      }
      else
      {
         tmp1=0;
      }

      key_debounce(&SW_ui_DebounceUp,&tmp1,c_man_close);


      if (tdn <  tbat6)
      {
         tmp1 = c_man_open;

      }
      else
      {
         tmp1=0;
      }

      key_debounce(&SW_ui_DebounceDown,&tmp1,c_man_open);

      if(texp < tbat6)
      {
         tmp1 = c_man_express;
      }
      else
      {
         tmp1=0;
      }

      key_debounce(&SW_ui_DebounceExpress,&tmp1,c_man_express);


      tmp1 = (SW_ub_KeyErr^SW_ub_KeyAct) & 0x07 ;

         ////////////////////////////
      if ((tmp1&0x03) == 0x03) {
         SW_ub_Local_Func = 0x03;
      }
      else
      {
         SW_ub_Local_Func =tmp1 ;
      }

   
    //power on
   if((SY_uc_poweron_sw>0) &&(SY_uc_poweron_sw<=SY_CON_SW_INVALID)) 
   {  
      SY_uc_poweron_sw--;             
      if(SW_ub_Local_Func> 0)
      {
        SY_uc_poweron_sw=0;
        SW_ub_Win_Status = WSTOP;
      }
     
   } 
   else
   {
      SY_uc_poweron_sw=0;
   }
   
	//endof poweron

}


void key(void)
{

   	unsigned char sw_tab, lin_tab;
   	unsigned int index;
   	
	unsigned char tmp1;	
	
	key_read();
	
	sw_tab = convert (SW_ub_Local_Func);
 
  if(LA_bi_PWLlocal_sw_disable)
  sw_tab=0;
  
  lin_tab=0;
  index=0;
  //Enable pin active detect
	
  
   if (!bsc_Get_EnIp())
   {
      tmp1 = TRUE;                 
   }
   else
   {
      tmp1 = FALSE;
   }    
   
   if (tmp1 != SY_bi_Enable_Filted ) 
   {
      SY_bi_Enable_Filted = tmp1;
      SW_ui_DebounceIgnite = 0;
   }
   else
   {
      if (SW_ui_DebounceIgnite > C_DEBOUNCE_ENABLE_ACTIVE) 
      {
         SY_bi_Enable_Active = tmp1;  
      }
      else
      {
         ++SW_ui_DebounceIgnite;
      }
   }
  //lin command stick  detect
  SW_ub_Lin_Func= lin_uc_command;
  
  lin_stick_detect();

  if(SW_ub_Lin_Func!=lin_uc_err)
	lin_tab = SW_ub_Lin_Func; 
	 	
	
  if(sw_tab >= C_INPUT_SWBothAct &&  lin_tab !=0)
	{  
	  SW_ub_Win_Status = WSTOP;
	  SW_uc_Status=0;
	}
	else
	{
	  if(SW_uc_Status>0)
	  {
	    if(lin_tab>0 &&(lin_tab!=lin_uc_command_pre))
	    {
	       SW_uc_Status=SWStatus1;
	    }
	    else if(sw_tab>0 &&(sw_tab!=SW_uc_command_pre))
	    {
	       SW_uc_Status=SWStatus2; 
	    }
	    
	  }
  	switch(SW_uc_Status) 
  	{
  	  case SWStatusIDLE: 
  	  {   	    
    	  if(lin_tab>0)   //LIN
    	  {
    	    index = lin_tab;
    	    SW_uc_Status=SWStatus2;
    	     
    	  }
    	  else if(sw_tab>0) //SW
    	  {
    	    index = sw_tab + 20;
    	    SW_uc_Status=SWStatus1; 
    	    
    	  }
    	  else 
    	  {
    	    index =0;
    	  }
  	    break;
  	  }
  	  case SWStatus1:  //sw +lin
  	  { 
  	      if(lin_tab>0 && sw_tab>0)
          {
            index=sw_tab+(lin_tab<<2); 
          }
          else if(lin_tab>0)
          {
            index=lin_tab;    
          }
          else if(sw_tab>0)
          {
            index = sw_tab+20; 
          }
          else 
          {
            index=0; 
          }
  	    
      	break;
  	  }
  	 
  	  case SWStatus2:  //lin+sw
  	  { 
  	     	        
	      if(lin_tab>0) 
	      {
	        index = lin_tab + (sw_tab<<2);  
	      }
	      else if(sw_tab>0) 
	      {
	        index= sw_tab+20; 
	      }
	      else
	      {
	         index=0;
	      }   
	      break; 	        
	    }
  	 
  	  
  	  default:
  	  break;
  	  
  	  
  	  
  	} 
  	   
  	index *=C_WIN_STATES_MAX;

  	index += SW_ub_Win_Status;
  	
  	if (index < C_INPUT_STATES_MAX * C_WIN_STATES_MAX ) 
  	{
  	  if(SW_uc_Status<SWStatus2) 
  	  {     	    
  		  SW_ub_Win_Status = PRIO_TABLE_SW[index];   
  	  }
  	  else 
  	  {
  	    SW_ub_Win_Status = PRIO_TABLE_LIN[index];
  	  }
  	}
  	else
  	{
  		SW_ub_Win_Status = WSTOP;
  	}
  	if(sw_tab ==0 && lin_tab==0 && SW_ub_Win_Status<=WSTOP)  
  	{   	    
  	  SW_uc_Status=0;
  	} 
	}
   lin_uc_command_pre=lin_tab;
   SW_uc_command_pre=sw_tab;
   
   if ((!APF_TstAPRdyFlg())&&(((!SY_bi_Enable_Active) && (!LA_bi_PWLOpEnb1))  ||
       (LA_bi_PWLlocal_sw_disable && (SW_ub_Win_Status == SAU ||SW_ub_Win_Status ==  SAD)))) 
   {
       
      SW_ub_Win_Status = WSTOP;
   }
   
   
   SW_ub_Win_Func = DECODE_TABLE[SW_ub_Win_Status];
   
   

   if ((SW_ub_Win_Func==DECODE_MAN_CLOSE) || (SW_ub_Win_Func==DECODE_MAN_OPEN)) 
   {
      SY_bi_Manual_Key=TRUE;
   }
   else
   {
      SY_bi_Manual_Key=FALSE;
   }
   
    
   if ( Motor_bi_InRawSt || APF_TstAPOffFlg())   //5秒的破冰时间 禁止auto up
   {
		
    	if (SW_ub_Win_Status ==LAU0 || SW_ub_Win_Status == LAU|| SW_ub_Win_Status == SAU)  
    	{
    		SW_ub_Win_Status = WSTOP;
        SW_ub_Win_Func = DECODE_STOP; 
    	} //just up direction disable auto 
   }   
  if (((SW_ub_Win_Func & 0x03)>0)&&((SW_ub_Win_Func_Old & 0x03)>0)&&(SW_ub_Win_Func & 0x03) != (SW_ub_Win_Func_Old & 0x03))
	{
		SW_bi_Change_Direction = TRUE;	//ready key reverse
		MC_uc_MotorStopDelay = c_motor_stop_delay;
		window_stop();
		
	}  
  
   SW_ub_Win_Func_Old = SW_ub_Win_Func; 
  	
   key_setmotorprio();  
   


   if (SY_bi_Enable_Active == TRUE )
   {
      SYS_SetWakeSrc(C_ALIVE_KEY);
       
      RT_bi_functest_f=1;     //notice test check  
   }
   else
   {
      SYS_ClrWakeSrc(C_ALIVE_KEY);
		  //SY_uc_KeepAlive &=C_ALIVE_KEY_MASK;
      RT_bi_functest_f=0;
   }



}





void key_setmotorprio(void)
{

   //注意这里已经不考虑是自动上升还是手动上升，自动下降还是手动下降，其只是对由于按键开关发送来的命令响应
   //进行优先级的排序，上升>下降>停止。
 
	   if (
	    ((SW_ub_Win_Func & DECODE_MAN_CLOSE )==DECODE_MAN_CLOSE) &&
	    (MB_uc_UpBlockCnt < 3)
	    )
	   {
	      // set key motor command up
	      MOT_SetUp(c_key_up_prio);
				MOT_ClrDn(c_key_down_prio);
				MOT_ClrStop(c_key_stop_prio);
	   }
	   else
	   {
	      if (
	        ((SW_ub_Win_Func & DECODE_MAN_OPEN )==DECODE_MAN_OPEN) &&
	        (MB_uc_DownBlockCnt < 3)
	        )
	      {
						MOT_ClrUp(c_key_up_prio);
						MOT_SetDn(c_key_down_prio);
						MOT_ClrStop(c_key_stop_prio);
	      }
	      else
	      {
						MOT_ClrUp(c_key_up_prio);
						MOT_ClrDn(c_key_down_prio);
						MOT_SetStop(c_key_stop_prio);
	      }
	   }
  

}




void key_checkstop(void)
{
	if (MOT_TstMotorCloseFlg()|| MOT_TstMotorOpenFlg())
 	 {
		 SW_bi_Change_Direction = FALSE;	
	 }
   if ( (HP_TstBlockUpFlg() || HP_TstBlockDnFlg() || (MOT_TstMotorStopFlg() && (!SW_bi_Change_Direction))) && (SW_ub_Win_Func>0)    )
   {
    
      SW_ub_Win_Status=WSTOP;
      SW_ub_Win_Func=DECODE_STOP;
    
   }
   
   key_setmotorprio();


}


