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
// ^FILE   :KYCBrokerDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : KYCBrokerDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "KYCBrokerDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\kycbrokerprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
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
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_KYC_BROKER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< KYCBrokerDlg > dlgCreator( CMD_GUI_KYC_BROKER ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("KYCBrokerDlg");
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
}

namespace ifds
{
	//extern CLASS_IMPORT const BFTextFieldId DocListExists;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
KYCBrokerDlg::KYCBrokerDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( KYCBrokerDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(KYCBrokerDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void KYCBrokerDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(KYCBrokerDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(KYCBrokerDlg, BaseMainDlg)
//{{AFX_MSG_MAP(KYCBrokerDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL KYCBrokerDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

    AddControl( CTRL_STATIC, IDC_STC_BROKERCODE, IFASTBP_PROC::BROKER_LIST, ifds::BrokerCode);
    AddControl( CTRL_STATIC, IDC_STC_BROKERNAME, IFASTBP_PROC::BROKER_LIST, ifds::BrokerName);
	AddControl( CTRL_COMBO, IDC_CMB_KYC_REGULATION, IFASTBP_PROC::BROKER_LIST, ifds::KYCRegulation, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_AML_AGREEMENT, IFASTBP_PROC::BROKER_LIST, ifds::AMLAgreement, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_AUTHSIGN, IFASTBP_PROC::BROKER_LIST, ifds::KYCSignture, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_KYC_STATUS, IFASTBP_PROC::BROKER_LIST, ifds::KYCStatus, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

	ConnectControlsToData();
	LoadControls();

	return(TRUE);
}

//******************************************************************************
void KYCBrokerDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	GetDlgItem (IDC_CMB_KYC_REGULATION)->EnableWindow (false);
	GetDlgItem (IDC_CMB_AML_AGREEMENT)->EnableWindow (false);
	GetDlgItem (IDC_CMB_AUTHSIGN)->EnableWindow (false);
	GetDlgItem (IDC_CMB_KYC_STATUS)->EnableWindow (false);

	doRefresh(this, NULL_STRING);   
}



//*****************************************************************************
bool KYCBrokerDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   SetDlgCaption();

   return( true );
}


//**********************************************************************************
void KYCBrokerDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
}

//**********************************************************************************

void KYCBrokerDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

	DString dstrBrokerCode;
	CString title;

	getParent()->getField( this, ifds::BrokerCode, dstrBrokerCode, false );
	
	GetWindowText (title);

	CString newTitile = title + dstrBrokerCode.c_str();
	
	SetWindowText(newTitile);
}

//*****************************************************************************

SEVERITY KYCBrokerDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter(ACCOUNT_NUM, dstrAccountNum );
   	
	return( NO_CONDITION );
}
