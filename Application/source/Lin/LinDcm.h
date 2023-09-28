/*******************************************************************************
|  File Name:    LinDcm.h
|  Description:  Lin Diagnostic Header file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20170323	   0.01       	$BAb5~(B          	$B=iHG(B
|******************************************************************************/

#ifndef SOURCES_004_LINSTACK_LINDCM_H_
#define SOURCES_004_LINSTACK_LINDCM_H_

#ifndef TRUE
#define TRUE  (1U)
#endif
#ifndef FALSE
#define FALSE (0U)
#endif

/*******************************************************************************
Name			: DcmInit
Syntax			: void DcmInit(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Diagnostic Init
Requirement		: None
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170323	$B=iHG(B
|******************************************************************************/
void DcmInit(void);

/*******************************************************************************
Name			: DcmMainFunction
Syntax			: void DcmMainFunction(void)
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Diagnostic$B>u(B?$B4y(B
Requirement		: $B0J(BDCM_PERIOD$BDj(B????$B<~4|(B?$BMQ(B
Call By			: Application Layer
history
<No.>    <author>    <time>    <description>
1			$BAb5~(B		20170323	$B=iHG(B
|******************************************************************************/
void DcmMainFunction(void);



#endif /* SOURCES_004_LINSTACK_LINDCM_H_ */
