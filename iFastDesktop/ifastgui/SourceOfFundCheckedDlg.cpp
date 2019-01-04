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
// ^FILE   :SourceOfFundCheckedDlg.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : May 2015
//
// ----------------------------------------------------------
//
// ^CLASS    : SourceOfFundCheckedDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "SourceOfFundCheckedDlg.h"
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

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SourceOfFundCheckedDlg > dlgCreator( CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME			= I_("SourceOfFundCheckedDlg");
   const I_CHAR * PENDPROCRECORD_TYPE       = I_( "PendProcRecordType" );
   const I_CHAR * const PENDING             = I_( "Pend" ); //PENDPROCRECORD_TYPE from pending view
   const I_CHAR * const HISTORY             = I_( "Proc" ); //PENDPROCRECORD_TYPE from history view
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId SourceofFundsChecked;
    extern CLASS_IMPORT const BFTextFieldId NotApplicable;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SOURCE_OF_FUNDS_CHECKED;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
SourceOfFundCheckedDlg::SourceOfFundCheckedDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SourceOfFundCheckedDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TradeAuthorizationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void SourceOfFundCheckedDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TradeAuthorizationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(SourceOfFundCheckedDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradeAuthorizationDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL SourceOfFundCheckedDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 		
	return TRUE;
}

//******************************************************************************
void SourceOfFundCheckedDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
	 
    AddControl (CTRL_COMBO, IDC_CMB_SOURCE_OF_FUNDS_CHECKED, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::SourceofFundsChecked, CTRLFLAG_INITCOMBO_BY_SUB_LIST  ); 
    ConnectControlsToData ();
	LoadControls();	  
	SetUserAccesFunctionCode (UAF::SOURCE_OF_FUNDS_CHECKED); 	
    addControlGroupIDForPermissionCheck(0);
    enableControlsOnScreen();     
}

//*****************************************************************************
bool SourceOfFundCheckedDlg::doRefresh (GenericInterface * rpGICaller, 
                                 const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return( true );
}

//*****************************************************************************
SEVERITY SourceOfFundCheckedDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter (PENDPROCRECORD_TYPE, m_RecordType);
   
	m_bDialogInit = true;

	return NO_CONDITION;
}

//******************************************************************************
void SourceOfFundCheckedDlg::enableControlsOnScreen()
{
	GetDlgItem(IDC_CMB_SOURCE_OF_FUNDS_CHECKED)->EnableWindow(hasUpdatePermission(GetUserAccesFunctionCode()));
    GetDlgItem(IDOK)->EnableWindow(hasUpdatePermission(GetUserAccesFunctionCode()));
}

//******************************************************************************
/* $Log::  
*/