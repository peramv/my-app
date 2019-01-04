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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : FundBrokerSettlementInstrDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : FundBrokerSettlementInstrDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include <configmanager.hpp>
#include <bfproc\abstractprocess.hpp>

#include "FundBrokerSettlementInstrDlg.h"

#include <ifastcbo\dstcworksession.hpp>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\settlementinstrprocessincludes.h>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR ;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundBrokerSettlementInstrDlg > dlgCreator( CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR  );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("FundBrokerSettlementInstrDlg");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FUND_BROKER_MAINTENANCE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleLocationAcctLvlHeading;
}

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId FUND_BROKER_LIST;	
}


//*****************************************************************************
// Public methods
//*****************************************************************************

FundBrokerSettlementInstrDlg::FundBrokerSettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: SettlementInstrDlg( pParent, pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   //{{AFX_DATA_INIT(AcctSettlementInstrDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
FundBrokerSettlementInstrDlg::~FundBrokerSettlementInstrDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
} 


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL FundBrokerSettlementInstrDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   
   SetUserAccesFunctionCode( UAF::FUND_BROKER_MAINTENANCE );

   // Title
   DString dstrFundBrokerCode; 
   getParent()->getParent()->getField(this, IFASTBP_PROC::FUND_BROKER_LIST, ifds::FundBrokerCode, dstrFundBrokerCode);   
   dstrFundBrokerCode.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   CString cstrSIFundBrkr;
   cstrSIFundBrkr.LoadString(TXT_SETTL_INSTR_FOR_FUND_BRKR);
   DString dstrCaption = DString(cstrSIFundBrkr) + dstrFundBrokerCode; 
   
   SetWindowText( dstrCaption.c_str() );

	return(TRUE);
}

//*****************************************************************************
void FundBrokerSettlementInstrDlg::setSettlementInstructionsControls()
{
	// Group Box title should be 'Fund Broker Settlement Instructions'
	
	CString cstrTitle;
	cstrTitle.LoadString(TXT_FUND_BRKR_SETTL_INSTR); //Fund Broker Settlement Instructions
		
	SetDlgItemText( IDC_GRP_BOX_SETTLEMENT_INSTR, cstrTitle );

}




//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//

