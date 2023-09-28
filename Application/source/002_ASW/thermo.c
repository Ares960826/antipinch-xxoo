/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*Name     :  thermo.c                                                           *
;*Project  :  AntiPinch                                                    *
;*Device   :  S12VR64					                                       *
;*AUTHOR   :  AP project team						                                       *
;*DATE     :  2010/05/20					                                   *
;*SW VER   :  0.1					                                           *
;*HW VER   :    					                                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;* COPYRIGHT STEC(C) Shanghai SIIC Transportation Electric CO.,ltd             *
;*                                                                             *
;* ALL RIGHTS RESERVED                                                         *
;*                                                                             *
;* The reproduction, transmission, or use of this document or its content is   *
;* not permitted without express written authority. Offenders will be liable   *
;* for damages.                                                                *
;* All rights, including rights created by patent grant or registration of a   *
;* utility model or design, are reserved.                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */


//#include "hidef.h" /* for EnableInterrupts macro */
//#include "derivative.h" /* include peripheral declarations */
#include "complier_sw.h"
//#include "typegene.h"
//#include "io_ctrldef.h"
//#include "mcuconfig.h"
#include "appl_const.h"
//#include "syst_func.h"
//#include "mot_control.h"
//#include "ad_conv.h"
#include "motor.h"
#include "AppIF.h"
#include "keyport.h"
#include "sysfunc.h"
#include "IRQCall.h"

uint16_t   TP_ui_Motor_Temperature ;
uint8_t  TP_uc_Motor_times;

//uint16_t   AD_ui_MotorTemperature;

uint8_t  SY_bi_Thermo_Limit;
uint8_t  SY_bi_Thermo_Limit_1;
uint8_t  SY_bi_Thermo_Limit_2;


void thermo_calc(void);
void thermo_block_calc(uint16_t   ix);
uint16_t   get_voltage_idx(void);
uint16_t   get_temperature(uint16_t   index) ;


#define       c_u_9v              90
#define       c_u_10v             100
#define       c_u_11v             110
#define       c_u_12v             120
#define       c_u_13v             130
#define       c_u_14v             140
#define       c_u_15v             150


//标定数据
const uint16_t   TAB_THERMO_VALUE[4*8] =
               {
                11,13,1,1,//4,8,1,1,   // 0 <9V  --> 0.20?, 0.40?, 0.05?, 0.05?			
                11,13,1,1,//3,6,1,1,   // 1 <10V --> 0.15?, 0.30?, 0.05?, 0.05?			
                14,14,1,1,//3,6,1,1,   // 2 <11V --> 0.15?, 0.30?, 0.05?, 0.05?			
                15,15,1,1,//3,6,1,1,   // 3 <12V --> 0.15?, 0.30?, 0.05?, 0.05?			
                16,16,1,1,//3,6,1,1,   // 4 <13V --> 0.15?, 0.30?, 0.05?, 0.05?			
                18,18,1,1,//3,6,1,1,   // 5 <14V --> 0.15?, 0.30?, 0.05?, 0.05?			
                18,18,1,1,//3,6,1,1,   // 6 <15V --> 0.15?, 0.30?, 0.05?, 0.05?			
                18,20,1,1 //4,9,1,1    // 7 >15V --> 0.20?, 0.45?, 0.05?, 0.05?			

               };
               

const uint16_t   TAB_THERMO_VALUE_BLOCK[2*8] =
               {

                300,750,    
                200,500,                                
                200,500,                                    
                200,500,                                       
                200,500,                                     
                200,500,                                   
                200,500,                                      
                300,750                                
               };
//标定数据结束


//热保护计算 
void  thermo_calc(void)
{
  uint16_t  tempe;
  uint16_t   tempe_v;

   if (C_DIS_THERMO != CDisable_Thermo)
   {
      if (TP_ui_Motor_Temperature < c_motor_min_temp)
      {
         TP_ui_Motor_Temperature = c_motor_min_temp;							//不低于最低的标定温值
      }
     tempe_v=(bsc_AD_Get_Raw_Bat()+3)/6;

      if ((bsc_Relay_AfeedbackIp()> tempe_v)|| (bsc_Relay_BfeedbackIp()>tempe_v))  //ZAP(>=6V)
      {
       
          tempe=get_temperature(0);
          TP_ui_Motor_Temperature =TP_ui_Motor_Temperature + tempe;		//继电器有吸合 电机在运转，加热

          if( (bsc_AD_Get_Raw_Thermal()<50) ||(bsc_AD_Get_Raw_Thermal()>110))//add sth zap (0-60->50+temp)
          {
            if(TP_ui_Motor_Temperature<c_motor_heating_point)
            {               
              TP_ui_Motor_Temperature =TP_ui_Motor_Temperature + 10;  
            }
         }
      }
      else
      {
        
         TP_ui_Motor_Temperature =TP_ui_Motor_Temperature- get_temperature(2);		//继电器断开 电机不在运转，冷却
      }
      
      
      if (TP_ui_Motor_Temperature < c_motor_limit3)    
      {
      	//不高于温度保护Limit3级
         if ((TP_ui_Motor_Temperature >= c_motor_limit2 ) ||								//大于Limit2级
         ((SY_bi_Thermo_Limit_1==FALSE) && (TP_ui_Motor_Temperature >= c_motor_limit1 )) )	//大于Limit1级 且是上电以来第一次
         {
            if ((MOT_TstMotorStopFlg()) && (MOT_GetStopCause() < c_thermo_prio))		
            {
            //电机已停，但不是热保护停止的。设定热保护停止标志                
               //MC_MCtrl_Stop |=c_thermo_prio;
			   MOT_SetStop(c_thermo_prio);
               SY_bi_Thermo_Limit=TRUE;
               if(!SY_bi_Thermo_Limit_1) 
               {
                SY_bi_Thermo_Limit_1=TRUE;
                if(TP_ui_Motor_Temperature<c_motor_limit2)
              	TP_ui_Motor_Temperature= c_motor_limit1;
               }
            }
            else
            {
            	//电机没有停，允许继续完成本次运行
            	
            }
            
         }
         else
         {
         //电机温度不高于limit值
            if(!SY_bi_Thermo_Limit_2)
            {
              
              if ((TP_ui_Motor_Temperature < c_motor_turnon_thd))
              {	
              //满足冷却条件，清除热保护
                 //MC_MCtrl_Stop &=c_thermo_prio_mask;
                 //MC_MCtrl_Stop &=c_thermomax_prio_mask;
                 MOT_ClrStop(c_thermo_prio);
				MOT_ClrStop(c_thermomax_prio);
								
                 SY_bi_Thermo_Limit=FALSE;
              }
            } 
            else
            {
             /*
               if(TP_uc_Motor_times<2)
               {
                
                 if ((TP_ui_Motor_Temperature < (c_motor_limit1)))
                {	
                //满足冷却条件，清除热保护
                   
                   if(SY_bi_Thermo_Limit) 
                   {
                   //MC_MCtrl_Stop &=c_thermo_prio_mask;
                   //MC_MCtrl_Stop &=c_thermomax_prio_mask;
                      MOT_ClrStop(c_thermo_prio);
											MOT_ClrStop(c_thermomax_prio);
										 //if(TP_uc_Motor_times==0)
                      //TP_ui_Motor_Temperature=c_motor_limit2-3000; 
                      
                      SY_bi_Thermo_Limit=FALSE; 
                      TP_uc_Motor_times++;
                   }
                   
                } 
               }
               else
               {
              }*/
            }
            if (TP_ui_Motor_Temperature <= c_motor_ini_temp)
            {	
            //满足冷却条件，清除热保护
               //MC_MCtrl_Stop &=c_thermo_prio_mask;
               //MC_MCtrl_Stop &=c_thermomax_prio_mask;
              MOT_ClrStop(c_thermo_prio);
							MOT_ClrStop(c_thermomax_prio);
							SY_bi_Thermo_Limit_1=FALSE;
               SY_bi_Thermo_Limit_2=FALSE;
               SY_bi_Thermo_Limit=FALSE;
               TP_uc_Motor_times=0;
            }
            
         }
      }
      else
      {
         //>Limit3级 ，立即停止
         //MC_MCtrl_Stop |= c_thermomax_prio;
				 MOT_SetStop(c_thermomax_prio);
         SY_bi_Thermo_Limit=TRUE;
      }
      
      if(TP_ui_Motor_Temperature >= c_motor_limit2 ) 
      SY_bi_Thermo_Limit_2=TRUE;
      
      if (TP_ui_Motor_Temperature>c_motor_ini_temp) 
      {
       	//温度还在初始值以上，没有冷却到位，系统不得进入休眠
         //SY_uc_KeepAlive |=C_ALIVE_THERMO;
				SYS_SetWakeSrc(C_ALIVE_THERMO);
      }
      else
      {
         //冷却到位，清除热保护Alive位
         //SY_uc_KeepAlive &=C_ALIVE_THERMO_MASK;
					SYS_ClrWakeSrc(C_ALIVE_THERMO);
         
      }
   }
}


/*查温度标定表*/
//index 0：加热
//index 2：冷却

uint16_t   get_temperature(uint16_t  index)           
{
   
   uint16_t  ux;
   if (index==0)
   {
      ux = c_motor_heating_point;	//升温拐点
   }
   else
   {
      ux = c_motor_cooling_point;	//冷却拐点
   }
   
   if (TP_ui_Motor_Temperature < ux)	//与标定的拐点比较，选不同标定值
   {
      ++index;
   }
   
   ux=get_voltage_idx();	//查电压索引值
   ux <<=2;					//×4 -> 每个电压等级对应4个温度，查行
   index += ux;  			//加上列
   
   return (TAB_THERMO_VALUE[index]); //返回加减温度值
}


//堵转时应增加的温度值
//ix : 0 200ms 短时堵转
//ix ：1 400ms 长时堵转 
void thermo_block_calc(uint16_t  ix)  
{
   
   uint16_t  ux;

   ux = get_voltage_idx(); //查电压索引值
   ux <<= 1;
   ux +=ix;  
   
   TP_ui_Motor_Temperature = TP_ui_Motor_Temperature + TAB_THERMO_VALUE_BLOCK[ux] ;	//累加电机温度值

   if(TP_ui_Motor_Temperature>init_motor_limit3)   TP_ui_Motor_Temperature=init_motor_limit3;
}

//查询电压索引


uint16_t  get_voltage_idx(void)
{
   if ((AD_uc_MotorVoltage-5)>c_u_9v)  //   >9.5V
   {
      if ((AD_uc_MotorVoltage-5)>c_u_10v)	// 10.5v
      {
         if ((AD_uc_MotorVoltage-5)>c_u_11v)	//11.5v
         {
            if ((AD_uc_MotorVoltage-5)>c_u_12v)		//12.5v
            {
               if ((AD_uc_MotorVoltage-5)>c_u_13v)		//13.5v
               {
                  if ((AD_uc_MotorVoltage-5)>c_u_14v)		//14.5v
                  {
                     if ((AD_uc_MotorVoltage-5) > c_u_15v)		//15.5v
                     {
                        return(7);
                     }
                     else
                     {
                        return(6);
                     }
                  }
                  else
                  {
                     return(5);
                  }
               }
               else
               {
                  return(4);
               }
            }
            else
            {
               return(3);
            }
         }
         else
         {
            return(2);
         }
      }
      else
      {
         return(1);
      }
   }
   else
   {
      return(0);
   }
}


void thermo_init(void)
{
   	TP_ui_Motor_Temperature = c_motor_ini_temp;
   	TP_uc_Motor_times=0;
   	SY_bi_Thermo_Limit=FALSE;  /* after a wakeup the first tmperature limit is active! */
    SY_bi_Thermo_Limit_1=FALSE; 
    SY_bi_Thermo_Limit_2=FALSE;
    //AD_ui_MotorTemperature=320;//20 ?????ZAP
	
}

void thermo_50msjob(void)
{

	//AD_ui_MotorTemperature = getThermalAD();
	thermo_calc();
}

void thermo_reset(void){
		TP_ui_Motor_Temperature = c_motor_ini_temp;
}


bool_t TP_TstThermalPFlg(void){
	
	return SY_bi_Thermo_Limit;
	
}

