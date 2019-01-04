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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccountReviewDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AccountReviewDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the AccountReview dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcfuncs.h>
///#include "dse_dstcglob_vw.hpp"
#include <ifastcbo\dstcworksession.hpp>
#include "accountreviewdlg.h"
#include <ifastbp\accountreviewprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNTREVIEW;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccountReviewDlg > dlgCreator( CMD_GUI_ACCOUNTREVIEW );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME     = I_( "AccountReviewDlg" );
   const I_CHAR * const LV_ACCOUNTREVIEW  = I_( "AccountReview" );
   const I_CHAR * const STRING_Y       = I_( "Y" );
}

namespace CND
{
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CommentsSub;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTREVIEW;
}


//******************************************************************************

AccountReviewDlg::AccountReviewDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AccountReviewDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
,m_bAccountReviewListSelectionInProgress (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   getParameter( ACCOUNTREVIEWLITERALS::ACCOUNT_NUM,        m_dstrAccountNumber );
   getParameter( ACCOUNTREVIEWLITERALS::SHAREHOLDER_NUMBER, m_dstrShrNum );

   //{{AFX_DATA_INIT(AccountReviewDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

AccountReviewDlg::~AccountReviewDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void AccountReviewDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AccountReviewDlg)
   DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AccountReviewDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AccountReviewDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_COMMAND(ID_ACCEL_REMARKSLIST, OnAccelAccountReviewlist)
ON_COMMAND(ID_ACCEL_DETAILS, OnAccelDetails)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AccountReviewDlg message handlers

BOOL AccountReviewDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );   

   BaseMainDlg::OnInitDialog();

   DisplayCaption();

   if( !m_hAccel )
   {
///      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_ACCOUNTREVIEW ) );	[CHANGE]
   }
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AccountReviewDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::ACCOUNTREVIEW);
   AddListControl( CLASSNAME, IDC_LV_ACCOUNTREVIEW, LV_ACCOUNTREVIEW, ifds::AccountReviewHeadingSet, IFASTBP_PROC::ACCOUNTREVIEW_LIST, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, true );
   AddControl( CTRL_EDIT, IDC_EDT_COMMENTS, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::CommentsSub, CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_ACCOUNTREVIEW);
   AddControl( CTRL_DATE, IDC_DATE_SCHEDULED, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::SchedReviewDate, CTRLFLAG_DEFAULT, IDC_LV_ACCOUNTREVIEW );
   AddControl( CTRL_DATE, IDC_DATE_REVIEWED, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::ActualReviewDate, CTRLFLAG_DEFAULT , IDC_LV_ACCOUNTREVIEW );
   GetDlgItem( IDC_DATE_SCHEDULED )->ShowWindow( true );
   GetDlgItem( IDC_DATE_REVIEWED )->ShowWindow( true );

   DSTEdit *editComments = dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_COMMENTS ) );
   editComments->SetMaxCharNum( 70 );

   CWaitCursor wait;
   LoadListControl( IDC_LV_ACCOUNTREVIEW );

//CP20030319   ConnectControlsToData ( IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   // HACK: Fix this dreadful hack.  Note that '1' is the old actual value of ACCOUNTREVIEW_LIST
   ConnectControlsToData ( 1 );
   if( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::ACCOUNTREVIEW_LIST) > 24 )
   {
      m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
   }
   if( (getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::ACCOUNTREVIEW_LIST) == 1) &&
       (getParentProcess()->isCurrentListItemDummy(this, IFASTBP_PROC::ACCOUNTREVIEW_LIST)) )
   {
      GetDlgItem( IDC_EDT_COMMENTS )->EnableWindow( false );
      GetDlgItem( IDC_DATE_SCHEDULED )->EnableWindow( false );
      GetDlgItem( IDC_DATE_REVIEWED )->EnableWindow( false );
      GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );
      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
      GetDlgItem( IDC_LV_ACCOUNTREVIEW )->EnableWindow( false );
   }
}

//******************************************************************************

bool AccountReviewDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
   DisplayCaption();
   LoadListControl( IDC_LV_ACCOUNTREVIEW );
   return(true);
}

//******************************************************************************

void AccountReviewDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::ACCOUNTREVIEW_LIST );
}

//******************************************************************************

void AccountReviewDlg::OnBtnMore() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;

   cursel = GetList( IDC_LV_ACCOUNTREVIEW )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNTREVIEW_LIST );

   SetMessageStatusBar( TXT_LOAD_ACCOUNTREVIEW );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ACCOUNTREVIEW );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_ACCOUNTREVIEW )->SetSelection( crtKey );
      }
   }

   m_BtnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_LV_ACCOUNTREVIEW )->SetSelection(cursel, true, true);
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************

void AccountReviewDlg::OnBtnReset() 
{
   ResetListItem( IDC_LV_ACCOUNTREVIEW );
   doRefresh( this, NULL_STRING );
}

//******************************************************************************

BOOL AccountReviewDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}

//******************************************************************************

void AccountReviewDlg::OnAccelAccountReviewlist() 
{
   // TODO: Add your command handler code here
   GetDlgItem(IDC_LV_ACCOUNTREVIEW)->SetFocus();
}

//******************************************************************************

void AccountReviewDlg::OnAccelDetails() 
{
   // TODO: Add your command handler code here
   GetDlgItem(IDC_EDT_COMMENTS)->SetFocus();
}

//******************************************************************************

void AccountReviewDlg::DisplayCaption() 
{
   DString dstrEntityName;

   if( !m_dstrAccountNumber.empty() )
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
                                                                                    getDataGroupId(), 
                                                                                    m_dstrAccountNumber, 
                                                                                    dstrEntityName);
   else
      dstrEntityName = NULL_STRING;

   SetShrAcctCaption( m_dstrShrNum, m_dstrAccountNumber, dstrEntityName );
}

//******************************************************************************

bool AccountReviewDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   DString dstrTemp;
   if( dstrColumnKey == I_("Comments1") )
   {
      dstrOut = NULL_STRING;
      getParent()->getField (this, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::Comments1, dstrTemp);
      dstrTemp.stripLeading(I_(' ')).stripTrailing(I_(' '));
      dstrOut = dstrTemp;
      getParent()->getField (this, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::Comments2, dstrTemp);
      dstrTemp.stripLeading(I_(' ')).stripTrailing(I_(' '));
      dstrOut += I_(" ") + dstrTemp;
      getParent()->getField (this, IFASTBP_PROC::ACCOUNTREVIEW_LIST, ifds::Comments3, dstrTemp);
      dstrTemp.stripLeading(I_(' ')).stripTrailing(I_(' '));
      dstrOut += I_(" ") + dstrTemp;
      return(true);
   }
   return(false);
}

//**********************************************************************************
void AccountReviewDlg::ControlUpdated ( UINT controlID, 
												    const DString &strValue)
{
   switch (controlID)
   {
      case IDC_DATE_REVIEWED:
         {
				if (!m_bAccountReviewListSelectionInProgress)
				{
					DString strCurrentKey =  getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNTREVIEW_LIST );
					LoadListControl( IDC_LV_ACCOUNTREVIEW,&strCurrentKey );
				}
				break;
			}
		default:
			break;
	}
}

//******************************************************************************
void AccountReviewDlg::DoPreListItemChanged ( UINT listControlID,
															 const DString &strKey,
															 bool bIsNewItem,
															 bool bIsDummyItem)
{

   switch (listControlID)
   {
      case IDC_LV_ACCOUNTREVIEW:
         {
            m_bAccountReviewListSelectionInProgress = true;
            break;
         }
		default:
			break;
	}
}

//******************************************************************************
void AccountReviewDlg::DoListItemChanged ( UINT listControlID,
														 const DString &strKey, 
														 bool isNewItem,
														 bool bIsDummyItem)
{  
	switch (listControlID)
   {
      case IDC_LV_ACCOUNTREVIEW:
         {
            m_bAccountReviewListSelectionInProgress = false;
            break;
         }
		default:
			break;
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountReviewDlg.cpp-arc  $
// 
//    Rev 1.10   Dec 07 2005 16:01:16   AGUILAAM
// IN 485796 - highlight record that was just modified.
// 
//    Rev 1.9   Dec 07 2005 15:42:52   AGUILAAM
// IN 485796 - update record with blank actual review date will not be sent by Desktop; will be updated on the View side.
// 
//    Rev 1.8   Sep 15 2005 15:09:50   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Mar 18 2005 11:43:00   aguilaam
// IN_234826: additional fix/ clean-up for account review screen
// 
//    Rev 1.6   Mar 17 2005 14:12:48   aguilaam
// IN_234826: display shrnum, acctnum, entity owner name on acctreview screen
// 
//    Rev 1.5   Mar 21 2003 18:30:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:55:26   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Jul 12 2002 19:01:10   HERNANDO
// Disable controls if list only contains dummy record.
// 
//    Rev 1.2   31 May 2002 13:54:48   HERNANDO
// Revised for Rel47.
// 
//    Rev 1.1   22 May 2002 19:15:34   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   08 May 2002 18:12:34   HERNANDO
// Initial revision.
 * 
 */
