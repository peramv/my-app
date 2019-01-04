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
// ^FILE   :ProgressiveIntRateDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : ProgressiveIntRateDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "ProgressiveIntRateDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\InvestmentHistoryProcessIncludes.h>
#include <ifastbp\ProgressiveIntRateProcessIncludes.h>
#include <ifastbp\ProgressiveIntRateProcess.hpp>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\Entity.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ProgressiveIntRateDlg > dlgCreator( CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME						= I_( "ProgressiveIntRate" );
   const I_CHAR * LV_PROGRESSIVE_INTEREST_RATE_LIST		= I_( "Progressive Interest Rate List" );
}

namespace CND //Conditions used
{  
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ProgressiveIntRateDetailsList;
	extern CLASS_IMPORT const BFTextFieldId ProgressiveRateUUID;
	extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
	extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
ProgressiveIntRateDlg::ProgressiveIntRateDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ProgressiveIntRateDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ProgressiveIntRateDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ProgressiveIntRateDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ProgressiveIntRateDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ProgressiveIntRateDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ProgressiveIntRateDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ProgressiveIntRateDlg::OnInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	//				DlgName		ListControlID					   listName										idField									idContainer
	AddListControl (CLASSNAME, IDC_LV_PROGRESSIVE_INTEREST_RATE,   LV_PROGRESSIVE_INTEREST_RATE_LIST,			ifds::ProgressiveIntRateDetailsList,	IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST);

	return TRUE;
}

//******************************************************************************
void ProgressiveIntRateDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	addControlGroupIDForPermissionCheck (IDC_LV_PROGRESSIVE_INTEREST_RATE);

	doRefresh (this, NULL_STRING);
}

//*****************************************************************************
bool ProgressiveIntRateDlg::doRefresh ( GenericInterface * rpGICaller, 
									   const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetAccount( m_dstrAccountNum );

	SetDlgCaption();

	ConnectListToData( IDC_LV_PROGRESSIVE_INTEREST_RATE, true );

	ConnectControlsToData();

	LoadControls();

	LoadListControl( IDC_LV_PROGRESSIVE_INTEREST_RATE );

	return true;
}

//**********************************************************************************
void ProgressiveIntRateDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, 
		    dstrEntityName;

	//Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY ProgressiveIntRateDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

    getParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
	//getParameter (INVHISTORYPROC::INVEST_ID, m_dstrInvHisInvestId);

	return NO_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ProgressiveIntRateDlg.cpp-arc  $
// 
//    Rev 1.1   Dec 01 2011 19:04:54   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.0   Nov 27 2011 21:14:20   wp040100
// Initial revision.
//
//
 * 
 * 
// 
*/
