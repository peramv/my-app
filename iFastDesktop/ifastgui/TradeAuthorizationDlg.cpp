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
//    Copyright 2004 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   :TradeAuthorizationDlg.cpp
// ^AUTHOR : 
// ^DATE   : Feb 24, 2009
//
// ----------------------------------------------------------
//
// ^CLASS    : TradeAuthorizationDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "TradeAuthorizationDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>

#include <ifastbp\transhistoryprocessincludes.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_AUTHORIZATION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradeAuthorizationDlg > dlgCreator( CMD_GUI_TRADE_AUTHORIZATION ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME			= I_("TradeAuthorizationDlg");
   const I_CHAR * const PENDPROCRECORD_TYPE = I_( "PendProcRecordType" );
   const I_CHAR * const Y                   = I_( "Y" );
   const I_CHAR * const PENDING             = I_( "Pend" ); //PENDPROCRECORD_TYPE from pending view
   const I_CHAR * const HISTORY             = I_( "Proc" ); //PENDPROCRECORD_TYPE from history view
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId EnableTradeAuthorization;
	extern CLASS_IMPORT const BFTextFieldId EnableTradeRestrictionFields;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADE_AUTHORIZATION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
TradeAuthorizationDlg::TradeAuthorizationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TradeAuthorizationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TradeAuthorizationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TradeAuthorizationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TradeAuthorizationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(TradeAuthorizationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradeAuthorizationDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TradeAuthorizationDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddControl (CTRL_COMBO, IDC_CMB_AUTHORIZATION, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::StcPendTrdAuthorization, CTRLFLAG_INITCOMBO_BY_SUB_LIST); 
	AddControl (CTRL_COMBO, IDC_CMB_TRADE_RESTRICTION_REASONS, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::TradeRestrictionReason, CTRLFLAG_INITCOMBO_BY_SUB_LIST); 
	AddControl (CTRL_COMBO, IDC_CMB_TRADE_RESTRICTION_CODES, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::TradeRestriction, CTRLFLAG_INITCOMBO_BY_SUB_LIST); 
	
	return TRUE;
}

//******************************************************************************
void TradeAuthorizationDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	SetUserAccesFunctionCode (UAF::TRADE_AUTHORIZATION); 
	addControlGroupIDForPermissionCheck(0);

	ConnectControlsToData ();
	LoadControls();	

	enableControlsOnScreen();

    m_bDialogInit = false;
}

//*****************************************************************************
bool TradeAuthorizationDlg::doRefresh (GenericInterface * rpGICaller, 
                                 const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return( true );
}

//*****************************************************************************
SEVERITY TradeAuthorizationDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter (PENDPROCRECORD_TYPE, m_RecordType);
   
	m_bDialogInit = true;

	return NO_CONDITION;
}

//******************************************************************************
void TradeAuthorizationDlg::enableControlsOnScreen()
{
	DString dstrEnableTradeAuthorization, dstrEnableTradeRestrictionFields;

	getParent()->getField(this, (m_RecordType == PENDING) ? IFASTBP_PROC::PENDING_LIST:IFASTBP_PROC::TRANS_LIST, ifds::EnableTradeAuthorization, dstrEnableTradeAuthorization);
	getParent()->getField(this, (m_RecordType == PENDING) ? IFASTBP_PROC::PENDING_LIST:IFASTBP_PROC::TRANS_LIST, ifds::EnableTradeRestrictionFields, dstrEnableTradeRestrictionFields);

	GetDlgItem(IDC_CMB_AUTHORIZATION)->EnableWindow(dstrEnableTradeAuthorization == Y);

	GetDlgItem(IDC_CMB_TRADE_RESTRICTION_REASONS)->EnableWindow(dstrEnableTradeRestrictionFields == Y);
	GetDlgItem(IDC_CMB_TRADE_RESTRICTION_CODES)->EnableWindow(dstrEnableTradeRestrictionFields == Y);
}

//******************************************************************************
/* $Log::  
*/