// MatSWPInstructionDetailDlg.cpp : implementation file
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MatSWPInstructionDetailDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MatSWPInstructionDetailDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "MatSWPInstructionDetailDlg.h"

#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\MatSweepInstrDetailProcessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MATSWP_INSTR_DETLS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MatSWPInstructionDetailDlg > dlgCreator( CMD_GUI_MATSWP_INSTR_DETLS );

namespace
{
   const I_CHAR *CLASSNAME             = I_( "MatSWPInstructionDetailDlg" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MATURITYSWPEEP_INSTR;
}

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MATSWP_INSTR_DETLS;

BEGIN_MESSAGE_MAP(MatSWPInstructionDetailDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MatSWPInstructionDetailDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MatSWPInstructionDetailDlg::MatSWPInstructionDetailDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MatSWPInstructionDetailDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
SEVERITY MatSWPInstructionDetailDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;

   return(sevRtn);
}

//******************************************************************************
void MatSWPInstructionDetailDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 
	
	SetUserAccesFunctionCode (UAF::MATURITYSWPEEP_INSTR); 	
	
	AddControl (CTRL_EDIT,IDC_EDT_FUND, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::FundTo, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_CLASS, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::ClassTo, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_ACCOUNT, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::AccountTo, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_PERCENT, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::Percentage, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_FORCED_RATE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::ForcedRateAmt, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_REF_NUMBER, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::RefNum, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_FEL, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::FELAmt, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT,IDC_EDT_ADDITIONAL_AMT, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::AddlAmt, CTRLFLAG_DEFAULT); 
	
	AddControl (CTRL_COMBO,IDC_CMB_COMRED, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::CommReduction, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl (CTRL_COMBO,  IDC_CMB_TERM, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::IntInvestTerm, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_ROLLOVER_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::RolloverType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_FORCED_IND, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::ForcedRate, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_REMINING, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::RemainingFleg, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_INTEREST_FREQ, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::IntCredFreq, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_FIXPROG, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::IntInvestType, CTRLFLAG_DEFAULT |CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_CALCTYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::IntCalcMthd, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_PAYTYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::PayType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );	
	AddControl( CTRL_COMBO, IDC_CMB_BUSINESS_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::BusinessType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_CURRENCY, IFASTBP_PROC::MAT_SWEEP_INSTRUCTION_DETL, ifds::Currency, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	

               
	doRefresh( this, NULL );
}

//******************************************************************************
BOOL MatSWPInstructionDetailDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

 
   //SetShrAcctCaption(strShrNum, strAccountNum, strEntityName);

   return(TRUE);
}

//******************************************************************************
void MatSWPInstructionDetailDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
}

//******************************************************************************
bool MatSWPInstructionDetailDlg::doRefresh( GenericInterface *rpGICaller, 
                                 const I_CHAR *szOriginalCommand )
{
   ConnectControlsToData();
   LoadControls( -1L ); // Using -1 to load all controls

   return(true);  
}

