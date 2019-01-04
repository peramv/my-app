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
// ^FILE   :InterestSegmentDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : InterestSegmentDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "InterestSegmentDlg.h"
#include <configmanager.hpp>

#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\InvestmentHistoryProcessIncludes.h>
#include <ifastbp\InterestSegmentProcessIncludes.h>
#include <ifastbp\InterestSegmentProcess.hpp>

#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_INTEREST_SEGMENT_LIST;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< InterestSegmentDlg > dlgCreator( CMD_GUI_INTEREST_SEGMENT_LIST );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME						= I_( "Segment Interest" );
   const I_CHAR * LV_SEGMENT_INTEREST_LIST				= I_( "Segment Interest List" );
}

namespace CND //Conditions used
{  
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId InterestSegmentDetailsList;
	extern CLASS_IMPORT const BFTextFieldId InvHisIntSegment;
	extern CLASS_IMPORT const BFDecimalFieldId InvHisRate;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
InterestSegmentDlg::InterestSegmentDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( InterestSegmentDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(InterestSegmentDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void InterestSegmentDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(InterestSegmentDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(InterestSegmentDlg, BaseMainDlg)
//{{AFX_MSG_MAP(InterestSegmentDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL InterestSegmentDlg::OnInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	//				DlgName		ListControlID			 listName					idField							  idContainer
	AddListControl (CLASSNAME, IDC_LV_INTEREST_SEGMENTS, LV_SEGMENT_INTEREST_LIST,	ifds::InterestSegmentDetailsList, IFASTBP_PROC::INTEREST_SEGMENT_LIST);

	return TRUE;
}

//******************************************************************************
void InterestSegmentDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	addControlGroupIDForPermissionCheck (IDC_LV_INTEREST_SEGMENTS);

	doRefresh (this, NULL_STRING);
}

//*****************************************************************************
bool InterestSegmentDlg::doRefresh ( GenericInterface * rpGICaller, 
									   const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetAccount( m_dstrAccountNum );

	SetDlgCaption();

	ConnectListToData( IDC_LV_INTEREST_SEGMENTS, true );

	ConnectControlsToData();

	LoadControls();

	LoadListControl( IDC_LV_INTEREST_SEGMENTS );

	return true;
}

//**********************************************************************************
void InterestSegmentDlg::SetDlgCaption()
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
SEVERITY InterestSegmentDlg::doInit()
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
/* $Log:   Y:/VCS/BF iFAST/ifastgui/InterestSegmentDlg.cpp-arc  $
// 
//    Rev 1.0   Dec 09 2011 19:51:28   wp040100
// Initial revision.
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
