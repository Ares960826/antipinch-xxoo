/*******************************************************************************
|  File Name:    LinDcm.c
|  Description:  Lin Diagnostic source file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170323       0.01           $BAb5~(B              $B=iHG(B
| 20170331       0.02           $BAb5~(B        $B=$2~(BDcm_ServiceTable_t?$B7?(B
|******************************************************************************/


#include "Typedef.h"
#include <string.h>
#include "XL6600.h"
#include "lin.h"
#include "AppIF.h"
#include "lin_lin21tl_api.h"
#include "LinDcm_Cfg.h"
#include "LinDcm.h"
#include "flash.h"


/** Negtive response code */
#define DCM_E_GENERAL_REJECT                                (0X10U)
#define DCM_E_SERVICE_NOT_SUPPORTED                         (0X11U)
#define DCM_E_SUBFUNC_NOT_SUPPORTED                         (0X12U)
#define DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT    (0X13U)
#define DCM_E_BUSY_REPEAT_REQUEST                           (0X21U)
#define DCM_E_CONDITION_NOT_CORRECT                         (0X22U)
#define DCM_E_NOT_COMPLETED                                 (0X23U)
#define DCM_E_REQUEST_SEQUENCE_ERROR                        (0X24U)
#define DCM_E_REQUEST_OUT_OF_RANGE                          (0X31U)
#define DCM_E_SECURITY_ACCESS_DENIED                        (0X33U)
#define DCM_E_INVALID_KEY                                   (0X35U)
#define DCM_E_EXCEEDED_NUMBER_OF_ATTEMPTS                   (0X36U)
#define DCM_E_REQUIRED_TIME_DELAY_NOT_EXPIRED               (0X39U)
#define DCM_E_UPLOAD_DOWNLOAD_NOT_ACCEPTED                  (0X70U)
#define DCM_E_TRANSFER_DATA_SUSPENDED                       (0X71U)
#define DCM_E_GENERAL_PROGRAMMING_FAILURE                   (0X72U)
#define DCM_E_WRONG_BLOCK_SEQUENCE_COUNTER                  (0X73U)
#define DCM_E_PENDING                                       (0X78U)
#define DCM_E_SUBFUNC_NOT_SUPPORTED_INACTIVE_SESSION        (0X7EU)
#define DCM_E_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION        (0X7FU)
#define DCM_E_VOLTAGE_TOO_HIGH                              (0X92U)
#define DCM_E_VOLTAGE_TOO_LOW                               (0X93U)

/** SID negative response */
#define DCM_RSP_SID_NRC (0X7FU)

/*    SID Positice Response Mask    */
#define DCM_RSP_SID_POS_MASK    (0X40U)




/*    Sid Length    */
#define DCM_SIDLENGTH_10    (2U)
#define DCM_SIDLENGTH_11    (1U)
#define DCM_SIDLENGTH_22    (3U)
#define DCM_SIDLENGTH_23    (3U)
#define DCM_SIDLENGTH_3E    (1U)
#define DCM_SIDLENGTH_31    (4U)

#define DCM_NRC_LENGTH      (3U)


/*    Session Mask    */
#define DCM_SESSION_DEFAULT            (0X01U)
#define DCM_SESSION_PROGRAMMING        (0X32U)
#define    DCM_SESSION_EXTEND          (0X88U)

#define _DIAG_SERVICES_DEMO_NUM        6


typedef uint8_t Dcm_Session_t;
typedef void (* Dcm_ServiceFc_t)(void);

typedef enum {Dcm_BufFul,Dcm_BufIdle} Dcm_BufSts_t;

typedef enum {Dcm_WReq = 0U,Dcm_GReq = 1U,Dcm_WSnd = 2U}    Dcm_Step_t;

typedef struct
{
    /* service Id */
    uint8_t SID;

    /* if function address is supportted */
    bool_t funcAddrSupportted;

    /* supportted session mode */
    Dcm_Session_t sessionSupp[DCM_SESSION_SUPPORT_NUM];

    /* service function */
    Dcm_ServiceFc_t serviceFct;

}Dcm_ServiceTable_t;

typedef struct
{
    uint8_t                 RxBuf[BUFFERMAXSIZE];
    uint16_t                RxBufLen;
    Dcm_BufSts_t            RxSts    : 1;
    uint8_t                 TxBuf[BUFFERMAXSIZE];
    uint16_t                TxBufLen;
    Dcm_BufSts_t             TxSts    : 1;
    bool_t                     NewReq    : 1;
    Dcm_Session_t            Dcm_Session;
    bool_t                    ResetTimer;
    uint16_t                P2Timer;
    uint16_t                S3Timer;
    Dcm_Step_t                Dcm_Step    : 2;
} Dcm_RunTimeEnvirment_t;

/*******************************************************************************
Name               : Dcm_ServiceFinish
Syntax             : static void Dcm_ServiceFinish(void)
Parameters(in)     : None
Parameters(out)    : None
Return value       : None
Description        : ?$BB+I~(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1         $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_ServiceFinish(void);

/*******************************************************************************
Name            : Dcm_RecvMsg10
Syntax          : static void Dcm_RecvMsg10(void)
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : $10 Service Handler
Requirement     : None
Call By         : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg10(void);

/*******************************************************************************
Name            : Dcm_RecvMsg11
Syntax            : static void Dcm_RecvMsg11(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $11 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg11(void);

/*******************************************************************************
Name            : Dcm_RecvMsg22
Syntax            : static void Dcm_RecvMsg11(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $22 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg22(void);

/*******************************************************************************
Name            : Dcm_RecvMsg2E
Syntax            : static void Dcm_RecvMsg2E(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $2E Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg2E(void);

/*******************************************************************************
Name            : Dcm_RecvMsg3E
Syntax            : static void Dcm_RecvMsg3E(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $3E Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg3E(void);

/*******************************************************************************
Name            : Dcm_RecvMsg31
Syntax            : static void Dcm_RecvMsg31(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $31 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20180115    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg31(void);

/*******************************************************************************
Name            : DcmServiceProcess
Syntax            : static void DcmServiceProcess(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BI~(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void DcmServiceProcess(void);

/*******************************************************************************
Name            : DcmCommunication
Syntax            : static void DcmCommunication(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BI~(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void DcmCommunication(void);

/*******************************************************************************
Name            : Dcm_ServiceHandle
Syntax            : static void Dcm_ServiceHandle(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BI~(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_ServiceHandle(void);

/*******************************************************************************
Name              : Dcm_FindService
Syntax            : static bool_t Dcm_FindService(uint8_t Sid,const Dcm_ServiceTable_t **Dcm_ServicePtr)
Parameters(in)    : Sid : $BMW(B??$BE*(BSID
Parameters(out)   : Dcm_ServicePtr : Sid$B;2?tI=;X(B?
Return value      : TRUE : $BI~(B?$B;Y;}(B
                   FALSE : $BIT;Y;}(B?$BI~(B?
Description       : ?$BY2(BDcm$BI~(B?
Requirement       : None
Call By           : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
2            $BAb5~(B        20170331    $B=$2~7A;2!$E:2C(BConst$B8BDjId(B
|******************************************************************************/
static bool_t Dcm_FindService(uint8_t Sid,const Dcm_ServiceTable_t * *Dcm_ServicePPtr);

/*******************************************************************************
Name            : Dcm_CheckSessionSupp
Syntax            : static bool_t Dcm_CheckSessionSupp(const Dcm_Session_t  sessionTable[])
Parameters(in)    : sessionTable : Service$B;Y;}E*2q(B?$BLO<0NsI=(B
Parameters(out) : None
Return value    : TRUE : $BEvA02q(B?$B;Y;}(B?$BI~(B?
                  FALSE : $BEvA02q(B??$B;Y;}(B?$BI~(B?
Description        : ??$BEvA02q(B?$B@'H];Y;}(B?$BI~(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
2            $BAb5~(B        20170331    $B=$2~7A;2(B?$B7?(B?$B?t(B??$B7?;X(B?
|******************************************************************************/
static bool_t Dcm_CheckSessionSupp(const Dcm_Session_t  sessionTable[]);

/*******************************************************************************
Name            : Dcm_SendNcr
Syntax            : static void Dcm_SendNcr(uint8_t Code)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ?$BAwH]Dj$(D5;(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_SendNcr(uint8_t Code);

/*******************************************************************************
Name            : Dcm_CheckSidLength
Syntax            : static bool_t Dcm_CheckSidLength(uint16_t Length)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ?$BAwH]Dj$(D5;(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static bool_t Dcm_CheckSidLength(uint16_t Length);

/*******************************************************************************
Name            : Dcm_ResetTimer
Syntax            : static void Dcm_ResetTimer(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : MCU?$B0L(B?$BM}H!?t(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
|******************************************************************************/
static void Dcm_ResetTimer(void);

/*******************************************************************************
Name            : Dcm_P2ServerEnable
Syntax            : static void Dcm_P2ServerEnable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B;HG=(BP2??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerEnable(void);

/*******************************************************************************
Name            : Dcm_P2ServerDisable
Syntax            : static void Dcm_P2ServerDisable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B6X;_(BP2??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerDisable(void);

/*******************************************************************************
Name            : Dcm_P2ServerCheck
Syntax            : static void Dcm_P2ServerCheck(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ??P2??$B4o@'H]D6(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerCheck(void);

/*******************************************************************************
Name            : Dcm_S3ServerEnable
Syntax            : static void Dcm_S3ServerEnable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B;HG=(BS3??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerEnable(void);

/*******************************************************************************
Name            : Dcm_S3ServerDisable
Syntax            : static void Dcm_S3ServerDisable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B6X;_(BS3??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerDisable(void);

/*******************************************************************************
Name            : Dcm_S3ServerCheck
Syntax            : static void Dcm_S3ServerCheck(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ??S3??$B4o@'H]D6(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerCheck(void);

/*******************************************************************************
Name            : Dcm_McuReset
Syntax            : static void Dcm_McuReset(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : MCU?$B0LH!?t(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170327    $B=iHG(B
|******************************************************************************/
static void Dcm_McuReset(void);

static const uint8_t diagServiceFlag[_DIAG_SERVICES_DEMO_NUM] =
{
    DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER,
    DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER,
    DIAGSRV_SESSION_CONTROL_ORDER,
    DIAGSRV_ECU_RESET_ORDER,
    DIAGSRV_TESTER_PRESENT_ORDER,
    DIAGSRV_ROUTINE_CONTROL_ORDER
};

static const Dcm_ServiceTable_t Dcm_ServiceTable[] =
{
        {0X10U,TRUE,{DCM_SESSION_DEFAULT,DCM_SESSION_PROGRAMMING,DCM_SESSION_EXTEND},    &Dcm_RecvMsg10},
        {0X11U,TRUE,{DCM_SESSION_PROGRAMMING,DCM_SESSION_EXTEND,DCM_SESSION_EXTEND},    &Dcm_RecvMsg11},
        {0X22U,TRUE,{DCM_SESSION_DEFAULT,DCM_SESSION_EXTEND,DCM_SESSION_EXTEND},        &Dcm_RecvMsg22},
        {0X2EU,TRUE,{DCM_SESSION_DEFAULT,DCM_SESSION_EXTEND,DCM_SESSION_EXTEND},        &Dcm_RecvMsg2E},
        {0X3EU,TRUE,{DCM_SESSION_DEFAULT,DCM_SESSION_PROGRAMMING,DCM_SESSION_EXTEND},    &Dcm_RecvMsg3E},
        {0X31U,TRUE,{DCM_SESSION_DEFAULT,DCM_SESSION_PROGRAMMING,DCM_SESSION_EXTEND},   &Dcm_RecvMsg31}
};

Dcm_RunTimeEnvirment_t DcmRte;

/*******************************************************************************
Name            : DcmInit
Syntax            : void DcmInit(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Diagnostic Init
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
void DcmInit(void)
{
    // 设置新请求标志为FALSE，表示当前没有新的诊断请求
    DcmRte.NewReq = FALSE;

    // 设置接收状态为"空闲"，表示当前没有正在处理的接收数据
    DcmRte.RxSts = Dcm_BufIdle;

    // 初始化接收缓冲区长度为0，表示没有接收到任何数据
    DcmRte.RxBufLen = 0U;

    // 设置发送状态为"空闲"，表示当前没有正在处理的发送数据
    DcmRte.TxSts = Dcm_BufIdle;

    // 似乎是一个错误，因为它再次初始化了接收缓冲区长度。这可能是一个代码错误，应该初始化TxBufLen。
    DcmRte.RxBufLen = 0U;

    // 设置当前的诊断会话为默认会话
    DcmRte.Dcm_Session = DCM_SESSION_DEFAULT;

    // 设置复位计时器标志为FALSE，表示当前没有复位请求
    DcmRte.ResetTimer = FALSE;

    // 初始化S3计时器为0，S3计时器通常用于监视客户端和服务器之间的通信超时
    DcmRte.S3Timer = 0U;

    // 初始化P2计时器为0，P2计时器通常用于监视服务器响应的超时
    DcmRte.P2Timer = 0U;

    // 设置诊断步骤为等待请求，表示当前系统正在等待新的诊断请求
    DcmRte.Dcm_Step = Dcm_WReq;
}


/*******************************************************************************
Name            : DcmMainFunction
Syntax            : void DcmMainFunction(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Diagnostic$B>u(B?$B4y(B
Requirement        : $B0J(BDCM_PERIOD$BDj(B????$B<~4|(B?$BMQ(B
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
void DcmMainFunction(void)
{
    Dcm_P2ServerCheck();
    DcmServiceProcess();
    DcmCommunication();

}

/*******************************************************************************
Name            : DcmServiceProcess
Syntax            : static void DcmServiceProcess(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BI~(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void DcmServiceProcess(void)
{
    if(Dcm_BufIdle == DcmRte.TxSts)
    {
        Dcm_ResetTimer();
        if(TRUE == DcmRte.NewReq)
        {
            Dcm_S3ServerDisable();
            DcmRte.NewReq = FALSE;
            Dcm_ServiceHandle();
            DcmRte.RxSts = Dcm_BufIdle;
        }
        else
        {
            Dcm_S3ServerCheck();
            Dcm_S3ServerEnable();
        }
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : DcmCommunication
Syntax            : static void DcmCommunication(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BDL(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void DcmCommunication(void)
{
    uint8_t index = 0u;
    uint8_t tx_status = ld_tx_status();
    uint8_t rx_status = ld_rx_status();
    if((tx_status > LD_COMPLETED) || (rx_status > LD_COMPLETED))
    {
        ld_init();
        DcmInit();
    }
    else
    {
        switch(DcmRte.Dcm_Step)
        {
            case Dcm_WReq :
            {
                DcmRte.RxBufLen = BUFFERMAXSIZE;
                for (index = 0; index < _DIAG_SERVICES_DEMO_NUM; index++)
                {
                    if (diag_get_flag(diagServiceFlag[index]))
                    {
                        ld_receive_message((l_u16*)&DcmRte.RxBufLen,&DcmRte.RxBuf[0]);
                        diag_clear_flag(diagServiceFlag[index]);
                        DcmRte.Dcm_Step = Dcm_GReq;
                        break;
                    }
                }
            } break;
            case Dcm_GReq :
            {
                if((LD_COMPLETED == rx_status) && (DcmRte.NewReq != TRUE))
                {
                    DcmRte.RxSts = Dcm_BufFul;
                    DcmRte.NewReq = TRUE;
                    Dcm_P2ServerEnable();
                }
                else
                {
                    ;
                }
            } break;
            case Dcm_WSnd :
            {
                if(LD_COMPLETED == tx_status)
                {
                    DcmRte.TxSts = Dcm_BufIdle;
                    DcmRte.Dcm_Step = Dcm_WReq;
                }
                else
                {
                    ;
                }
            } break;
            default :
            {
                ;
            } break;
        }
    }
}

/*******************************************************************************
Name            : Dcm_ServiceHandle
Syntax            : static void Dcm_ServiceHandle(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : Dcm$BI~(B??$BM}(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_ServiceHandle(void)
{
    bool_t Ret = FALSE;
    bool_t FindSid = FALSE;
    const Dcm_ServiceTable_t *Dcm_ServicePtr = NULL;
    /*    Find Service Index    */
    FindSid = Dcm_FindService(DcmRte.RxBuf[0],&Dcm_ServicePtr);
    if(TRUE == FindSid)
    {
        /*    Check Session    */
        Ret = Dcm_CheckSessionSupp(Dcm_ServicePtr->sessionSupp);
    }
    else
    {
        ;
    }
    if(TRUE == Ret)
    {
        Dcm_ServicePtr->serviceFct();
    }
    else
    {
        if(FALSE == FindSid)
        {
            /*    $BIT;Y;}(B?$BI~(B?        */
            Dcm_SendNcr(DCM_E_SERVICE_NOT_SUPPORTED);
        }
        else
        {
            /*    $BEvA02q(B?$BIT;Y;}(B?$BI~(B?    */
            Dcm_SendNcr(DCM_E_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION);
        }
    }

}

/*******************************************************************************
Name            : Dcm_FindService
Syntax            : static bool_t Dcm_FindService(uint8_t Sid,Dcm_ServiceTable_t * *Dcm_ServicePtr)
Parameters(in)    : Sid : $BMW(B??$BE*(BSID
Parameters(out) : Dcm_ServicePtr : Sid$B;2?tI=;X(B?
Return value    : TRUE : $BI~(B?$B;Y;}(B
                  FALSE : $BIT;Y;}(B?$BI~(B?
Description        : ?$BY2(BDcm$BI~(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static bool_t Dcm_FindService(uint8_t Sid,const Dcm_ServiceTable_t ** Dcm_ServicePPtr)
{
    bool_t Ret = FALSE;
    uint8_t Index;
    for(Index = 0U;Index < (sizeof(Dcm_ServiceTable)/sizeof(Dcm_ServiceTable_t));Index++)
    {
        if(Sid == Dcm_ServiceTable[Index].SID)
        {
            *Dcm_ServicePPtr = &Dcm_ServiceTable[Index];
            Ret = TRUE;
            break;
        }
        else
        {
            ;
        }
    }
    return Ret;
}

/*******************************************************************************
Name            : Dcm_CheckSessionSupp
Syntax            : static bool_t Dcm_CheckSessionSupp(const Dcm_Session_t  sessionTable[])
Parameters(in)    : sessionTable : Service$B;Y;}E*2q(B?$BLO<0NsI=(B
Parameters(out) : None
Return value    : TRUE : $BEvA02q(B?$B;Y;}(B?$BI~(B?
                  FALSE : $BEvA02q(B??$B;Y;}(B?$BI~(B?
Description        : ??$BEvA02q(B?$B@'H];Y;}(B?$BI~(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
2            $BAb5~(B        20170331    $B=$2~7A;2(B?$B7?(B?$B?t(B?$B;X(B?
|******************************************************************************/
static bool_t Dcm_CheckSessionSupp(const Dcm_Session_t  sessionTable[])
{
    bool_t Ret = FALSE;
    uint8_t Index;
    for(Index = 0U;Index < DCM_SESSION_SUPPORT_NUM;Index++)
    {
        if(sessionTable[Index] == DcmRte.Dcm_Session)
        {
            Ret = TRUE;
            break;
        }
        else
        {
            ;
        }
    }
    return Ret;
}


/*******************************************************************************
Name            : Dcm_SendNcr
Syntax            : static void Dcm_SendNcr(uint8_t Code)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ?$BAwH]Dj$(D5;(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_SendNcr(uint8_t Code)
{
    if(Dcm_BufIdle == DcmRte.TxSts)
    {
        DcmRte.TxBuf[0] = DCM_RSP_SID_NRC;
        DcmRte.TxBuf[1] = DcmRte.RxBuf[0];
        DcmRte.TxBuf[2] = Code;
        DcmRte.TxBufLen = DCM_NRC_LENGTH;

        Dcm_ServiceFinish();
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_CheckSidLength
Syntax            : static bool_t Dcm_CheckSidLength(uint16_t Length)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ?$BAwH]Dj$(D5;(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static bool_t Dcm_CheckSidLength(uint16_t Length)
{
    bool_t Ret;
    if(Length == DcmRte.RxBufLen)
    {
        Ret = TRUE;
    }
    else
    {
        Ret = FALSE;
    }
    return Ret;
}

/*******************************************************************************
Name            : Dcm_ServiceFinish
Syntax            : static void Dcm_ServiceFinish(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ?$BB+I~(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_ServiceFinish(void)
{
    /*    Request To Send Response Pdu    */
    ld_send_message(DcmRte.TxBufLen,DcmRte.TxBuf);
    Dcm_P2ServerDisable();
    DcmRte.TxSts = Dcm_BufFul;
    DcmRte.Dcm_Step = Dcm_WSnd;
}


/*******************************************************************************
Name            : Dcm_RecvMsg10
Syntax            : static void Dcm_RecvMsg10(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $10 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170323    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg10(void)
{
    bool_t Ret = FALSE;
    uint8_t SubFunc;
    uint8_t updateFlag;
    Ret = Dcm_CheckSidLength(DCM_SIDLENGTH_10);
    if(TRUE == Ret)
    {
        SubFunc = DcmRte.RxBuf[1];
        switch(SubFunc)
        {
            case DCM_SESSION_DEFAULT :
            {
                DcmRte.Dcm_Session = DCM_SESSION_DEFAULT;
            } break;
            case DCM_SESSION_PROGRAMMING :
            {
                DcmRte.Dcm_Session = DCM_SESSION_PROGRAMMING;
                updateFlag = 0x55;
                //Api_EepromWrite(IS_BOOTLOADER_NEED_UPDATE_ID, 0, 1, &updateFlag);
                //ZAP??????
                (void)App_FlashEraseSector(FLS_FACTORY_MSG_BASICADDR,30000);
                (void)App_FlashWriteData(FLS_FACTORY_MSG_BASICADDR,  (uint32_t)FLS_BOOT_APP_FLAG0, (uint32_t)FLS_BOOT_APP_FLAG1, 30000);

                //
                NVIC_SystemReset();
            } break;
            case DCM_SESSION_EXTEND :
            {
                DcmRte.Dcm_Session = DCM_SESSION_EXTEND;
            } break;
            default :
            {
                Dcm_SendNcr(DCM_E_SUBFUNC_NOT_SUPPORTED);
                Ret = FALSE;
            } break;

        }
    }
    else
    {
        ;
    }
    if(TRUE == Ret)
    {
        if(Dcm_BufIdle == DcmRte.TxSts)
        {
            DcmRte.TxBuf[0] = DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
            DcmRte.TxBuf[1] = DcmRte.RxBuf[1];
            DcmRte.TxBufLen = 2U;
            Dcm_ServiceFinish();
        }
    }
    else
    {
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }


}

/*******************************************************************************
Name            : Dcm_RecvMsg11
Syntax            : static void Dcm_RecvMsg11(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $11 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg11(void)
{
    bool_t Ret = FALSE;
    Ret = Dcm_CheckSidLength(DCM_SIDLENGTH_11);

    if(TRUE == Ret)
    {
        if(Dcm_BufIdle == DcmRte.TxSts)
        {
            DcmRte.TxBuf[0] = DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
            DcmRte.TxBufLen = 1U;
            Dcm_ServiceFinish();
            DcmRte.ResetTimer = TRUE;
        }
    }
    else
    {
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
}

/*******************************************************************************
Name            : Dcm_RecvMsg22
Syntax            : static void Dcm_RecvMsg22(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $22 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
2            $BAb5~(B        20170327    $B2CF~(BWriteId$B2s(B?
|******************************************************************************/
static void Dcm_RecvMsg22(void)
{
    bool_t Ret = FALSE;
    uint16_t readDid;
    bool_t didFind = FALSE;
    bool_t WrdidFind = FALSE;
    uint8_t readTableIndex = 0U;
    uint8_t WriteTableIndex = 0U;

    Ret = Dcm_CheckSidLength(DCM_SIDLENGTH_22);

    if(TRUE == Ret)
    {

        readDid = (uint16_t)DcmRte.RxBuf[1] << 8U;
        readDid += (uint16_t)DcmRte.RxBuf[2];

        for(readTableIndex = 0U;readTableIndex < DCM_READDID_NUM;readTableIndex++)
        {
            if(readDid == Dcm_ReadDidRow[readTableIndex].DID)
            {
                DcmRte.TxBufLen = 3U + Dcm_ReadDidRow[readTableIndex].readDataFct(&DcmRte.TxBuf[3]);
            didFind = TRUE;
                break;
            }
            else
            {
                ;
            }
        }

        if(FALSE == didFind)
        {

            for(WriteTableIndex = 0U;WriteTableIndex < DCM_WRITEDID_NUM;WriteTableIndex++)
            {
                if(readDid == Dcm_WriteDidRow[WriteTableIndex].DID)
                {
                    memcpy((void *)((uint32_t)&DcmRte.TxBuf[3]),(void *)((uint32_t)Dcm_WriteDidRow[WriteTableIndex].Addr),Dcm_WriteDidRow[WriteTableIndex].Length);
                    DcmRte.TxBufLen = 3U + (uint16_t)Dcm_WriteDidRow[WriteTableIndex].Length;
                    WrdidFind = TRUE;
                    break;
                }
                else
                {
                    ;
                }
            }
        }

        if((FALSE == didFind) && (FALSE == WrdidFind))
        {
            /*    ?$B5a(BID$BITB8:_(B    */
            Ret = FALSE;
            Dcm_SendNcr(DCM_E_REQUEST_OUT_OF_RANGE);
        }
        else
        {
            ;
        }
    }
    else
    {
        /*    ?$BJ8(B?$BEYIT@5$(DOl(B    */
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if(TRUE == Ret)
    {
        DcmRte.TxBuf[0] =DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
        DcmRte.TxBuf[1] =DcmRte.RxBuf[1];
        DcmRte.TxBuf[2] =DcmRte.RxBuf[2];
        Dcm_ServiceFinish();
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_RecvMsg2E
Syntax            : static void Dcm_RecvMsg2E(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $2E Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg2E(void)
{
    bool_t Ret = FALSE;
    uint16_t WriteDid;
    uint8_t WriteTableIndex = DCM_WRITEDID_NUM;
    bool_t didFind = FALSE;
    bool_t WriteFlag = FALSE;

    if(DcmRte.RxBufLen > DCM_SIDLENGTH_23)
    {
        Ret = TRUE;
        WriteDid = (uint16_t)DcmRte.RxBuf[1] << 8U;
        WriteDid += (uint16_t)DcmRte.RxBuf[2];
        while ((WriteTableIndex > 0U) && (FALSE == didFind))
        {
            WriteTableIndex --;
            if (WriteDid == Dcm_WriteDidRow[WriteTableIndex].DID)
            {
                didFind = TRUE;
            }
            else
            {
            ;
            }
        }

        if(TRUE == didFind)
        {
            /*    Call Flash Program    Function */
            if(Dcm_WriteDidRow[WriteTableIndex].Length == (DcmRte.RxBufLen - DCM_SIDLENGTH_23))
            {
                Ret = TRUE;
            }
            else
            {
                Ret = FALSE;
                /*    ?$BJ8(B?$BEYIT@5$(DOl(B    */
                Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
            }
        }
        else
        {
            /*    ?$B5a(BID$BITB8:_(B    */
            Ret = FALSE;
            Dcm_SendNcr(DCM_E_REQUEST_OUT_OF_RANGE);
        }
    }
    else
    {
        Ret = FALSE;
        /*    ?$BJ8(B?$BEYIT@5$(DOl(B    */
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }


    if(TRUE == Ret)
    {
        WriteFlag = Dcm_CalibrationWriteHandle(Dcm_WriteDidRow[WriteTableIndex].Addr,&DcmRte.RxBuf[3],(uint16_t)Dcm_WriteDidRow[WriteTableIndex].Length);
        if(TRUE == WriteFlag)
        {
            DcmRte.TxBuf[0] =DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
            DcmRte.TxBuf[1] =DcmRte.RxBuf[1];
            DcmRte.TxBuf[2] =DcmRte.RxBuf[2];
            DcmRte.TxBufLen = 3U;
            Dcm_ServiceFinish();
        }
        else
        {
            Dcm_SendNcr(DCM_E_GENERAL_PROGRAMMING_FAILURE);
        }
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_RecvMsg3E
Syntax            : static void Dcm_RecvMsg3E(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $3E Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg3E(void)
{
    bool_t Ret = FALSE;
    Ret = Dcm_CheckSidLength(DCM_SIDLENGTH_3E);
    if(TRUE == Ret)
    {
        DcmRte.TxBuf[0] =DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
        DcmRte.TxBufLen = 1U;
        Dcm_ServiceFinish();
    }
    else
    {
        Ret = FALSE;
        /*    ?$BJ8(B?$BEYIT@5$(DOl(B    */
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
}

/*******************************************************************************
Name            : Dcm_RecvMsg31
Syntax            : static void Dcm_RecvMsg31(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $31 Service Handler
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20180115    $B=iHG(B
|******************************************************************************/
static void Dcm_RecvMsg31(void)
{
    /*  NAD PCI SID 12 12 34  DcmRte.RxBuf*/
    bool_t Ret = FALSE;
    Ret = Dcm_CheckSidLength(DCM_SIDLENGTH_31);
    if(TRUE == Ret)
    {
        switch(DcmRte.RxBuf[1])
        {
            case 1U :
            {
                /*  Start Hall Run  */
                uint16_t HallNum = ((uint16_t)DcmRte.RxBuf[2] << 8U) + (uint16_t)DcmRte.RxBuf[3];
                MotorRunHall(HallNum);
                DcmRte.TxBufLen = 1U;
                DcmRte.TxBuf[0] =DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
                Dcm_ServiceFinish();
            } break;
            case 3U :
            {
                /*  GetResult   */
                DcmRte.TxBufLen = 1U + GetHallResult(&DcmRte.TxBuf[1]);
                DcmRte.TxBuf[0] =DcmRte.RxBuf[0] + DCM_RSP_SID_POS_MASK;
                Dcm_ServiceFinish();
            } break;
            default :
            {
                Dcm_SendNcr(DCM_E_SUBFUNC_NOT_SUPPORTED);
            } break;
        }

    }
    else
    {
        Ret = FALSE;
        /*    ?$BJ8(B?$BEYIT@5$(DOl(B    */
        Dcm_SendNcr(DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
}

/*******************************************************************************
Name            : Dcm_ResetTimer
Syntax            : static void Dcm_ResetTimer(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : MCU?$B0L(B?$BM}H!?t(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170324    $B=iHG(B
|******************************************************************************/
static void Dcm_ResetTimer(void)
{
    if(TRUE == DcmRte.ResetTimer)
    {
        /*    Reset    */
        Dcm_McuReset();
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_P2ServerEnable
Syntax            : static void Dcm_P2ServerEnable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B;HG=(BP2??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerEnable(void)
{
    DcmRte.P2Timer = DCM_P2Server_MAX /    DCM_PERIOD;
}

/*******************************************************************************
Name            : Dcm_P2ServerDisable
Syntax            : static void Dcm_P2ServerDisable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B6X;_(BP2??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerDisable(void)
{
    DcmRte.P2Timer = 0U;
}

/*******************************************************************************
Name            : Dcm_P2ServerCheck
Syntax            : static void Dcm_P2ServerCheck(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ??P2??$B4o@'H]D6(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_P2ServerCheck(void)
{
    if(DcmRte.P2Timer > 0U)
    {
        DcmRte.P2Timer--;
        if(0U == DcmRte.P2Timer)
        {
            /*    P2    TimeOut    */
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}


/*******************************************************************************
Name            : Dcm_S3ServerEnable
Syntax            : static void Dcm_S3ServerEnable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B;HG=(BS3??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerEnable(void)
{
    if((DcmRte.S3Timer == 0U) && (DcmRte.Dcm_Session != DCM_SESSION_DEFAULT))
    {
        DcmRte.S3Timer = DCM_S3Server_MAX / DCM_PERIOD;
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_S3ServerDisable
Syntax            : static void Dcm_S3ServerDisable(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : $B6X;_(BS3??$B4o(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerDisable(void)
{
    DcmRte.S3Timer = 0U;
}

/*******************************************************************************
Name            : Dcm_S3ServerCheck
Syntax            : static void Dcm_S3ServerCheck(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : ??S3??$B4o@'H]D6(B?
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170401    $B=iHG(B
|******************************************************************************/
static void Dcm_S3ServerCheck(void)
{
    if(DcmRte.S3Timer > 0U)
    {
        DcmRte.S3Timer--;
        if(0U == DcmRte.S3Timer)
        {
            /*    S3    TimeOut    */
            DcmRte.Dcm_Session = DCM_SESSION_DEFAULT;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : Dcm_McuReset
Syntax            : static void Dcm_McuReset(void)
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : MCU?$B0LH!?t(B
Requirement        : None
Call By            : Application Layer
history
<No.>    <author>    <time>    <description>
1            $BAb5~(B        20170327    $B=iHG(B
|******************************************************************************/
static void Dcm_McuReset(void)
{
    /*    MCU    ?$B0LBe(B?    */
    ;
}
