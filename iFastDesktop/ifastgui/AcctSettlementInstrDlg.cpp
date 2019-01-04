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
// ^FILE   : AcctSettlementInstrDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AcctSettlementInstrDlg
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

#include "AcctSettlementInstrDlg.h"

#include <ifastcbo\dstcworksession.hpp>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\settlementinstrprocessincludes.h>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctSettlementInstrDlg > dlgCreator( CMD_GUI_SETTLEMENT_INSTRUCTIONS_ACCTLVL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("AcctSettlementInstrDlg");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleLocationAcctLvlHeading;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

AcctSettlementInstrDlg::AcctSettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: SettlementInstrDlg( pParent, pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AcctSettlementInstrDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
AcctSettlementInstrDlg::~AcctSettlementInstrDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL AcctSettlementInstrDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Title
   DString dstrShrNum, dstrAccountNum, dstrEntityName;

   // Get Shareholder Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Account Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Entity Name
   if ( !dstrAccountNum.empty() ) {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName );

	SetUserAccesFunctionCode( UAF::SETTLE_LOCATION_ACCT_LVL );

	return(TRUE);
}

//*****************************************************************************
void AcctSettlementInstrDlg::setSettlementInstructionsControls()
{
	// Group Box title should be 'Accountholder Settlement Instructions'
	CString cstrAcctHolderSettle;
	cstrAcctHolderSettle.LoadString(TXT_ACCTHLDR_SETTLEMENT_INSTR);
	DString dstrDialogCaption = DString(cstrAcctHolderSettle);	
	SetDlgItemText( IDC_GRP_BOX_SETTLEMENT_INSTR, dstrDialogCaption.c_str() );

// Hide Clearing Method --> clearing method is no longer displayed
//	GetDlgItem( IDC_TXT_CLEARING_METHOD )->ShowWindow( false );
//	GetDlgItem( IDC_CMB_SETTL_INSTR_CLEARING_METHOD )->ShowWindow( false );	
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSettlementInstrDlg.cpp-arc  $
// 
//    Rev 1.2   Nov 24 2011 15:47:26   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.1   Nov 26 2004 16:56:32   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.0   Oct 13 2004 15:39:16   VADEANUM
// Initial revision.
//
