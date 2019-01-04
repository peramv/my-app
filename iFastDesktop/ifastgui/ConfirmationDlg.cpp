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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ConfirmationDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfirmationDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include "confirmationdlg.h"

#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>
#include <bfsessn\bfcpsessiontags.h>
#include <ifastawd\DSTCAWDSession.hpp>

#include <bfproc\bpglobal.h>
#include <bfproc\bpsessiontags.h>
#include <bfproc\GenericInterfaceContainer.hpp>
#include <configmanager.hpp>
#include <ifastbp\confirmationprocessincludes.h>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\dstbutton.h>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <uibase\dstedit.h>
#include <ifastbp\remarksprocessincludes.h>
#include <ifastbp\TransCancelProcessincludes.h>
#include <ifastbp\accdetailsprocessincludes.h>
#include <bfproc\AbstractProcess.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastdataimpl\dse_dstc0001_vw.hpp>
#include <assert.h>
#include "dstcview.h"
#include "DiscardMsgDlg.h"
#ifndef BrowserLaunch_H
   #include "BrowserLaunch.h"
#endif
#include <ifastbp\BrowserLaunchProcess.hpp>

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CONFIRMATION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ConfirmationDlg > dlgCreator( CMD_GUI_CONFIRMATION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME                      = I_( "ConfirmationDlg" );
   const I_CHAR *LV_CONFIRMATIONLIST            = I_( "Confirmation List" );
   const int MAX_CHAR_NUM_OF_REMARK             = 70;
   const int MAX_NUM_LINES_FOR_REMARKS          = 10;
   const I_CHAR *const Y                        = I_( "Y" );
   const I_CHAR *POSTOK                         = I_( "PostOk" );
   const I_CHAR *IDENT_ACCOUNT_PROCESS          = I_("IdentAccProcess");
   const I_CHAR *TRADES_PROCESS                 = I_("TradesProcess");
   const I_CHAR *AWD_PTR                        = I_("_AwdInterface_Ptr_");
   const I_CHAR *CALLED_FROM_AMS_GLOBAL         = I_("AmsGlobal");
   const I_CHAR *CALLED_FROM_MKT_INDEX          = I_("MktIndex");
   const I_CHAR *CALLED_FROM_MANUAL_DIVIDEND    = I_("ManualDividend");
   const I_CHAR *CALLED_FROM_SETTLELOC          = I_("SettleLocationSysLvl");
   const I_CHAR *CALLED_FROM_FEEMODEL           = I_("FeeModel");
   const I_CHAR *CALLED_FROM_FEEPARAM           = I_("FeeParam");
   const I_CHAR *CALLED_FROM_AGGREGATEDORDER    = I_("AggregatedOrder");
   const I_CHAR *CALLED_FROM_TXNCANCEL          = I_("TxnCancel");
   const I_CHAR *CALLED_FROM_REBOOK             = I_("REBOOK");
   const I_CHAR *CALLED_FROM_SAVINGS_DIRECTIVE  = I_("SavingsDirective");
   const I_CHAR *CALLED_FROM_TRANS_HIST_DILUTION = I_("TransHistDilution");
   const I_CHAR *CALLED_FROM_BROKER_CUT_OFF		= I_("BrokerCutOff");

   const I_CHAR *UPDATE_AWD                     = I_("UPDATE AWD" );
   const I_CHAR *CREATED                        = I_("CREATED" );
   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );

}

namespace SessionTags
{
   extern const I_CHAR *MGMCO;
}

namespace CND
{  // Conditions used
   extern const long GUI_AWD_FAILED_UPDATE_OR_CREATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Remark_sub;
   extern CLASS_IMPORT const BFTextFieldId BOTime;
   extern CLASS_IMPORT const BFTextFieldId CallEndTime;

}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GOVT_FILING_AMENDMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BROWSER_LAUNCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SMART_FORM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_CLASS_LIMITATION;  //IN2831230 - Fund Limitation Option
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FOREIGN_TAX_REVIEW;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_RULES_MAINTENANCE;

//*****************************************************************************

ConfirmationDlg::ConfirmationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ConfirmationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_pAwdInterface( NULL )
, m_pAwdSession( NULL )
, m_bCommentAccessible( true )
, m_dstrAWDEvent( NULL_STRING )
, m_bAwdDisabled( false )
, m_bCreateNew( false )
, m_dstrDispRebook(NULL_STRING )
, m_InvokedBrowserScreen( NULL_STRING )
, remarkListkey(NULL)
, m_bRefreshStatusList(false)
, m_FormatRemarksCount(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ConfirmationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void ConfirmationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ConfirmationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(ConfirmationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ConfirmationDlg)
ON_BN_CLICKED(IDC_CHK_AWD, OnChkAwdOrRemark)
ON_BN_CLICKED(IDC_CHK_REMARK, OnChkAwdOrRemark)
ON_BN_CLICKED(IDC_RB_END, OnRbEnd)
ON_BN_CLICKED(IDC_RB_GET_WORK, OnRbGetWork)
ON_BN_CLICKED(IDC_RB_REFRESH, OnRbRefresh)
ON_BN_CLICKED(IDC_RD_UPADET_ORIG, OnRbUpdateOrig)
ON_BN_CLICKED(IDC_RD_CLONE_UPDATE, OnRbCloneUpdate)
ON_BN_CLICKED(IDC_RB_RETAIN_WORK, OnRbNewSearch)
ON_BN_CLICKED (IDC_CHK_UPD_ALL_CIF_RELATED, OnChkUpdAllCIFRelated)
ON_BN_CLICKED (IDC_CHK_WORKOBJECT, OnBtnWrkObject)
ON_CBN_SELCHANGE(IDC_CB_WU_UNIT, OnSelchangeCbWuUnit)
ON_CBN_SELCHANGE(IDC_CB_WU_WRKT, OnSelchangeCbWuWkType)
ON_EN_CHANGE(IDC_EDT_COMMENT, OnEnChangeRemarkComment)
//ON_EN_KILLFOCUS(IDC_EDT_COMMENT, OnEnChangeRemarkComment)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

SEVERITY ConfirmationDlg::init2()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, DOINIT);

   getParameter (CONFPROC::PARM_AWDEVENT, m_dstrAWDEvent);
   getParameter (CONFPROC::PARM_CALLED_FROM, m_dstrCalledFrom);
   getParameter (CONFPROC::CREATING_ACCOUNT, m_dstrCreatingAcct);
   getParameter (TRANSCANCEL::DISPLAY_REBOOK, m_dstrDispRebook);
   getParameter (TRANSCANCEL::BULK_CANCEL, m_dstrBulkCancel);
   getParameter (I_("Batch"), m_dstrBatchNum);
   getParameter( I_("InvokedBrowserName"), m_InvokedBrowserScreen );
   getParameter( CONFPROC::COMMIT_PARENT_DATA_GROUPS, m_CommitParentDataGroups);

   m_dstrDispRebook.strip().upperCase();
   m_dstrAWDEvent.upperCase();
   m_dstrBulkCancel.strip().upperCase();
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
BOOL ConfirmationDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   DString dstrShrNum, 
      dstrAccountNum,
      dstrCreatingShareholder;

   bool bIsSmartFrom = m_InvokedBrowserScreen == CMD_BPROC_SMART_FORM ? true : false;

   if (!bIsSmartFrom)
   {
		getParent()->getField( this, BF::NullContainerId, CONFPROC::CREATING_SHAREHOLDER, dstrCreatingShareholder );
		if (dstrCreatingShareholder == Y)
		{
			CString cstrNewShr;
			cstrNewShr.LoadString(TXT_NEWSHAREHOLDER);
			SetShrAcctCaption(dstrShrNum, dstrAccountNum, DString(cstrNewShr));
		}
		else if (Y != m_dstrBulkCancel)
		{
			DString dstrEntityName (NULL_STRING);
			getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum);
			getGlobal (WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum);
			dstrAccountNum.stripLeading('0');
			if (!dstrAccountNum.empty())
			{
				dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
                                                                                                          dstrAccountNum,
                                                                                                          dstrEntityName);
			}
			SetShrAcctCaption (dstrShrNum, dstrAccountNum, dstrEntityName);
		}
   }
   initControls();

   UINT nShow = m_dstrDispRebook ==  Y ? SW_SHOW:SW_HIDE;
   GetDlgItem (IDC_RD_REBOOK)->ShowWindow (nShow);
   GetDlgItem( IDOK )->EnableWindow( TRUE );

   return TRUE;
}

//*****************************************************************************
void ConfirmationDlg::initControls()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   //AWD Controls
   //AddControl( CTRL_COMBO, IDC_CB_WU_UNIT, IFASTBP_PROC::CONFIRMATION, ifds::Using_AWD, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_COMBO, IDC_CB_WU_UNIT, IFASTBP_PROC::CONFIRMATION, ifds::BusinessArea, CTRLFLAG_DEFAULT);
   AddControl( CTRL_COMBO, IDC_CB_WU_WRKT, IFASTBP_PROC::CONFIRMATION, ifds::WorkType, CTRLFLAG_DEFAULT  );
   AddControl( CTRL_COMBO, IDC_CB_WU_STAT, IFASTBP_PROC::CONFIRMATION, ifds::StatusDesc, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT,  IDC_EDT_AWD_BATCH, IFASTBP_PROC::CONFIRMATION, ifds::Batch);

   AddControl( CTRL_COMBO, IDC_CB_REMARK_TYPE, IFASTBP_PROC::REMARKS_LIST, ifds::RemarkType, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_EDIT, IDC_EDT_COMMENT, IFASTBP_PROC::REMARKS_LIST, ifds::Remark_sub, CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP );
   // Radio buttons - End, Get Work, New Search (Retain Work), Refresh
   AddControl( CTRL_CHECKBOX, IDC_RB_END, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_GET_WORK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_RETAIN_WORK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_REFRESH, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RD_REBOOK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   // Check buttons - Remark, AWD Comment
   AddControl( CTRL_CHECKBOX, IDC_CHK_REMARK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_CHK_AWD, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   // Ok and Cancel buttons
   AddControl( CTRL_STATIC, IDOK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   //AddControl( CTRL_STATIC, IDCANCEL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   // AWD static text
   AddControl( CTRL_STATIC, IDC_ST_WU_UNIT, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_ST_WU_WRKT, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_ST_WU_STAT, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_TXT_BATCH, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   // Check box to determine whether to Create/Update or not.
   AddControl( CTRL_CHECKBOX, IDC_CHK_WORKOBJECT, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   //added for AIM enhancements PET2360/06 - CIF

   AddControl (CTRL_CHECKBOX, IDC_CHK_UPD_ALL_CIF_RELATED, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD);

   DSTEdit* remarkEdit = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENT ) );
   if( remarkEdit != NULL )
   {
      remarkEdit->SetMaxCharNum( MAX_CHAR_NUM_OF_REMARK );
	  remarkEdit->LimitText( (MAX_CHAR_NUM_OF_REMARK + 2)* MAX_NUM_LINES_FOR_REMARKS - 2 );
   }

   DSTButton *checkEndBtn = dynamic_cast<DSTButton*>( GetControl( IDC_RB_END ) );
   DSTButton *checkRefreshBtn = dynamic_cast<DSTButton*>( GetControl( IDC_RB_REFRESH ) );

   // Disable Refresh button
   if (  m_dstrCalledFrom == CALLED_FROM_AMS_GLOBAL ||
         m_dstrCalledFrom == CALLED_FROM_MKT_INDEX ||
         m_dstrCalledFrom == CALLED_FROM_SETTLELOC ||
         m_dstrCalledFrom == CALLED_FROM_MANUAL_DIVIDEND ||
         m_dstrCalledFrom == CALLED_FROM_FEEMODEL ||
         m_dstrCalledFrom == CALLED_FROM_FEEPARAM ||
         m_dstrCalledFrom == CALLED_FROM_AGGREGATEDORDER ||
		 m_dstrCalledFrom == CALLED_FROM_BROKER_CUT_OFF ||
         I_( "Y" ) == m_dstrBulkCancel)
   {
      checkRefreshBtn->Enable (false);
   }
   if (m_dstrCalledFrom == I_("ModifyPendingTradesWithLoss"))
   {
      checkEndBtn->Enable (false);
      if( checkRefreshBtn )
      {
         checkRefreshBtn->SetCheck( 1 );
         OnRbRefresh();
      }
   }
   else if (checkEndBtn) // Set the End Button as default
   {
      checkEndBtn->SetCheck( 1 );
      OnRbEnd();
   }

   // PMI - 3rd May 2007 - If browser screen has already
   // performed the updates, then disable the cancel button
   // on the confirmation dialog.
   DString dstrUpdatesAlreadyPeformed;
     
   if (m_dstrCalledFrom == I_("BrowserLaunch"))
   {
	  BrowserLaunch * pBrowserLaunch = static_cast< BrowserLaunch * >( getParent()->getParent());

	  if ( pBrowserLaunch->updatesAlreadyPeformed() == true )
	  {
        CWnd* pCWnd = GetDlgItem( IDCANCEL );

        if ( pCWnd != NULL )
        {
           pCWnd->EnableWindow( false );
        }
	  }

      if (m_InvokedBrowserScreen == CMD_BPROC_FUND_RULES_MAINTENANCE && checkRefreshBtn)
      {
          checkRefreshBtn->Enable(false);
      }
   }

   DString dstrFromRemarks;
   getParent()->getField (this, CONFPROC::FROM_REMARKS, dstrFromRemarks);
   m_bFromRemarks = dstrFromRemarks == I_("Y");

   // Setup remarks/comments
   DSTButton *checkRemarkBtn = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_REMARK));
   DSTButton *checkAwdBtn = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_AWD));

   if (checkRemarkBtn != NULL || checkAwdBtn != NULL)
   {
      DString dstrRemarkAvailable;

      getParent()->getField (this, CONFPROC::REMARKS_AVAILABLE, dstrRemarkAvailable);
      if (m_bCommentAccessible = (dstrRemarkAvailable == Y))
      {
         checkRemarkBtn->SetCheck( 1 );

         //  Look for a new remark
         bool bFoundNew = false;
         if( m_bFromRemarks )
         {
            int iNum = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::REMARKS_LIST );
            const DString &key = getParent()->getFirstListItemKey (this, IFASTBP_PROC::REMARKS_LIST);
            for (int iCtr = 1; iCtr <= iNum; ++iCtr)
            {
               AbstractProcess *pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
               if( pParentProcess->isCurrentListItemNew (this, IFASTBP_PROC::REMARKS_LIST))
               {
                  bFoundNew = true;
                  break;
               }
               getParent()->getNextListItemKey( this, IFASTBP_PROC::REMARKS_LIST );
            }
            checkRemarkBtn->Enable( false ); // Disable Remark Check box
         }
         if( !bFoundNew || !m_bFromRemarks ) // Create a new remark
         {
            remarkListkey = &( getParent()->getKeyForNewListItem( this, IFASTBP_PROC::REMARKS_LIST ) );
            getParent()->setCurrentListItem( this, IFASTBP_PROC::REMARKS_LIST, *remarkListkey );
         }
         if( !bFoundNew && m_bFromRemarks )
         {
            dstrRemarkAvailable = I_("N");
            m_bCommentAccessible = false;
         }
         ConnectControlToData( IDC_EDT_COMMENT, true );
         ConnectControlToData( IDC_CB_REMARK_TYPE, true );
      }
      if (!m_bCommentAccessible)
      {
         checkRemarkBtn->SetCheck (0);
         GetControl (IDC_CHK_REMARK)->Enable (false);
         checkAwdBtn->SetCheck (0);   // Disable AWD Comment - temp.
         ConnectControl (IDC_EDT_COMMENT, false);
         ConnectControl (IDC_CB_REMARK_TYPE, false);
      }
   }
   ConnectControlsToData();
   LoadControl (IDC_EDT_COMMENT);
   UpdateComment ();

   // Set AwdDisabled
   if (!m_bAwdDisabled)
   {
      m_bAwdDisabled = !BFCPSession::usingAwd ();
   }
   if (!m_bAwdDisabled)
   {
      if (m_dstrCalledFrom == I_("AWDComments"))
      {
	     DSTEdit *remarkEdit = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENT ) );
		 if( remarkEdit )
		 {
			 remarkEdit->setNumLine( MAX_NUM_LINES_FOR_REMARKS );
		 }
         m_bCommentAccessible = true;
         assert (checkAwdBtn);
         checkAwdBtn->SetCheck (1);
         OnChkAwdOrRemark ();
      }

      m_bAwdDisabled = true;
      LoadControl (IDC_EDT_AWD_BATCH);

      try
      {
        if( getSession() != NULL )
         {
            m_pAwdSession = getSession()->getAwdSession();
         }
         if( m_pAwdSession != NULL )
         {
            const BFAwdData *pAwdWork = m_pAwdSession->getProcessWork();
            m_bAwdDisabled = false;
			//if we have a current work object, by default, check AWD comments
			if( pAwdWork )
			{
				checkAwdBtn->SetCheck (1);
			}
         }
      }
      catch ( ... )
      {
      }
   }
   displayCloneControls (!m_bAwdDisabled);

   if (m_bAwdDisabled)
   {
      EnableAWD (false);
// if there is no awd, getwork has to be disabled
      GetDlgItem (IDC_RB_GET_WORK)->EnableWindow (false);
      GetDlgItem (IDC_ST_AWD_WRKASGN)->EnableWindow (false);
      GetDlgItem (IDC_ST_AWD)->EnableWindow (false);
      GetDlgItem (IDC_CHK_WORKOBJECT )->ShowWindow (SW_HIDE);
      GetDlgItem (IDC_RB_END)->SetFocus ();
      if (GetDlgItem (IDC_EDT_COMMENT)->IsWindowEnabled())
      {
         GetDlgItem (IDC_EDT_COMMENT)-> SetFocus ();
      }
   }
   else
   {
      ConfigureAWDControls ();
   }

   // Enable "AWD Comments" CheckBox if this is an AWD Portal event.
   if(((CDSTCView*)GetMainView())->HasWorkEvent()) {
      GetControl (IDC_CHK_AWD)->Enable (m_bCommentAccessible);
      UpdateComment ();
   }


   DString showUpdateAllCIF;

   getParent()->getField (this, CONFPROC::SHOW_UPDATE_ALL_CIF, showUpdateAllCIF);
   GetControl (IDC_CHK_UPD_ALL_CIF_RELATED)->Show (showUpdateAllCIF == I_("1"));
}
//*****************************************************************************
void ConfirmationDlg::displayCloneControls (bool bUsingAWD)
{
   bool bDisplayClone = false;

   DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   if( pSession )
   {
      bDisplayClone = pSession->canClone() && bUsingAWD ;
   }
   UINT nShowClone = bDisplayClone? SW_SHOW:SW_HIDE;
   UINT nShowCreatNew = ( !bDisplayClone && bUsingAWD )?SW_SHOW:SW_HIDE;
   GetDlgItem( IDC_RD_CLONE_UPDATE )->ShowWindow( nShowClone );
   GetDlgItem( IDC_RD_UPADET_ORIG )->ShowWindow( nShowClone );
   GetDlgItem( IDC_WORK_OBJECT )->ShowWindow( nShowCreatNew );
   GetDlgItem( IDC_CHK_WORKOBJECT )->ShowWindow( nShowCreatNew );
   if(bDisplayClone)
   {
      CButton *pBt = (CButton*)( GetDlgItem( IDC_RD_UPADET_ORIG ) );
      pBt->SetCheck(1);
   }
   if( nShowCreatNew == SW_SHOW )
   {
     CString cstrWorkObject;
     cstrWorkObject.LoadString( TXT_CREATE_NEW );
     GetDlgItem( IDC_WORK_OBJECT )->SetWindowText( cstrWorkObject );
   }
}
//*****************************************************************************
void ConfirmationDlg::ConfigureAWDControls( )
{
   // Setup AWD-related controls
   EnableAWD (true);

   DSTCAWDSession *pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   if (pSession)
   {
      pSession->setupWorkArea (UPDATE_AWD);

      string_vector list = pSession->getAwdBusinessAreaList();
      string_vector_const_iterator  iter;
      CComboBox* pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_UNIT);

	  // strip the space for theitems in the drop down		
      for (iter = list.begin(); iter != list.end(); ++iter)
      {
		  DString tmp = *iter;
          pCmb->AddString ( tmp.strip().c_str() );
      }

      //updateStatusList();

      DString time;

      pSession->getAwdField (ifds::BOTime, time);
      pSession->setAwdField (ifds::BOTime, time);

     // if call started,  then disable getWork radio button
      GetDlgItem(IDC_RB_GET_WORK)->EnableWindow( !( pSession->isCallStarted() ) );

   // there is already  a work object and
   // the call has not started
     if( !(pSession->isContainerEmpty() ) && ! ( pSession->isCallStarted() ) )
     {
        // select Business Area
        DString dstrCopmanyId,
           dstrBusArea;

        pSession->getAwdField(ifds::BusinessArea,dstrBusArea);
        //pSession->getBusinessAreaByCompanyId( dstrCopmanyId, dstrBusArea ); 
		CComboBox* pCmb1 = (CComboBox*) GetDlgItem(IDC_CB_WU_UNIT);

		// use exact match to select the item
		pCmb1->SetCurSel( pCmb1->FindStringExact(-1,dstrBusArea.strip().c_str()) );

        OnSelchangeCbWuUnit();		
		m_bRefreshStatusList = true;
        pCmb1 = (CComboBox*) GetDlgItem(IDC_CB_WU_WRKT);
        DString dstrTemp = pSession->getCurrentWork();
        pCmb1->SelectString(0,dstrTemp.strip().c_str() );
// select status        
		OnSelchangeCbWuWkType();
		pCmb1 = (CComboBox*) GetDlgItem(IDC_CB_WU_STAT );
        dstrTemp =   pSession->getCurrentStatus();
        pCmb1->SelectString(0,dstrTemp.strip().c_str() );

        CString cstrWorkObject;
        cstrWorkObject.LoadString( TXT_UPDATE_EXISTING );
        GetDlgItem( IDC_WORK_OBJECT )->SetWindowText( cstrWorkObject );
        m_bCreateNew = false;

        // Check box
         DSTButton *pChkbox = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_WORKOBJECT ) );
         if( pChkbox )
         {
            pChkbox->SetCheck( 1 );  // Always true for Update Existing
         }
         GetDlgItem( IDC_CHK_WORKOBJECT )->EnableWindow( FALSE );

        OnRbUpdateExisting();
     }
     else
     {// there is no work object

        // Set Static to 'Create New'
        pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_UNIT);
        DString dstrValue;
        pSession->getAwdField(ifds::BusinessArea,dstrValue);
        pCmb->SelectString(0,dstrValue.strip().c_str() );
        OnSelchangeCbWuUnit();
        pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_WRKT);
        pSession->getAwdField(ifds::WorkType,dstrValue);
        pCmb->SelectString(0,dstrValue.strip().c_str() );
		updateStatusList();
        pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_STAT);
        pSession->getAwdField(ifds::StatusDesc,dstrValue);
        pCmb->SelectString(0,dstrValue.strip().c_str() );

        // Default is Not Checked for Manulife until the next release.
        // Next release a generic control will be used to determine the default.
        DSTButton *pChkbox = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_WORKOBJECT ) );
        if( pChkbox )
        {
           pChkbox->SetCheck( 0 );
        }
        m_bCreateNew = true;
        OnRbCreateNew ();
     }
   }
}
//*****************************************************************************

void ConfirmationDlg::updateStatusList()
{
   CComboBox* pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_STAT);
   if( pCmb != NULL )
   {
     //check to see if there is anything selected
     CString strCurrSel = "";
	 int iCurSel = pCmb->GetCurSel();
	 if( iCurSel >= 0 )
	 {
		 pCmb->GetWindowText( strCurrSel );
	 }
     DSTCAWDSession *pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
	 if( pSession != NULL )
	 {
		CString strBusinesssArea, strWorkType;
		// is there a business area selected?
		pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_UNIT);
		if( pCmb != NULL)
		{
			iCurSel = pCmb->GetCurSel();
			if( iCurSel >= 0 )
			{
				pCmb->GetWindowText( strBusinesssArea );
			}
		}

		//is there a work type selected?
        pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_WRKT);
		if( pCmb != NULL)
		{
			iCurSel = pCmb->GetCurSel();
			if( iCurSel >= 0 )
			{
				pCmb->GetWindowText( strWorkType );
			}
		}

		string_vector list = pSession->getAwdStatusList( (DString) strBusinesssArea, (DString) strWorkType );
		string_vector_const_iterator  iter;

		pCmb = (CComboBox*) GetDlgItem(IDC_CB_WU_STAT);
		//first, clean it up
		pCmb->ResetContent();
		for( iter = list.begin(); iter != list.end(); ++iter)
		{
			pCmb->AddString(( *iter ).c_str() );
		}
		if (pCmb->FindString(0,CREATED )== CB_ERR)
		{
			pCmb->AddString ((new DString (CREATED))->c_str());
		}

		int iPos = pCmb->FindString(0,strCurrSel );
		if( iPos == CB_ERR )
		{
			//try once again without trailing spaces
            strCurrSel.Trim();
			iPos = pCmb->FindString(0,strCurrSel );
		}
		if( strCurrSel.IsEmpty() || iPos == CB_ERR )
		{
			pCmb->SetCurSel(0);  // select the first one for status
		}
		else
		{
			pCmb->SetCurSel(iPos);
		}
	 }
   }
}

//*****************************************************************************
// the method will be removed later Yingbao
//
void ConfirmationDlg::GetBusinessArea( const DString &dstrCompanyId, DString &dstrBusinessArea )
{
   dstrBusinessArea = NULL_STRING;
   string_vector  listTemp;
   string_vector_const_iterator  iter;

   // Iterate AWD Business Area list in MGMCO to find matching ID
   bool  bFound = false;
   if( !dstrCompanyId.empty() )
   {
      ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::Session );
      Configuration sysTable = pConfigManager->retrieveConfig( SessionTags::MGMCO);

      DString  dstrTempBusinessArea = NULL_STRING;
      listTemp = m_pAwdInterface->getBusinessAreaList();
      iter = listTemp.begin();

      while( (iter != listTemp.end()) && !bFound )
      {
         dstrTempBusinessArea = *iter;
         dstrTempBusinessArea.strip();
         if( bFound = (dstrCompanyId == sysTable.getValueAsString( dstrTempBusinessArea ).stripAll( I_CHAR('\t') )) )
         {
            dstrBusinessArea = dstrTempBusinessArea;
            break;
         }
         iter++;
      }
   }
}

//******************************************************************************
bool ConfirmationDlg::doRefresh (GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand)
{
   return true;
}

//******************************************************************************
void ConfirmationDlg::SetComboItem (int id, DString item)
{
   CComboBox *pCmb = (CComboBox*) GetDlgItem(id);
   int iIndex = pCmb->FindString( -1, item.c_str() );
   if (CB_ERR != iIndex)
   {
      pCmb->SetCurSel (iIndex);
   }
}

//*****************************************************************************
void ConfirmationDlg::EnableAWD (bool update)
{
   GetControl (IDC_CB_WU_UNIT)->Enable (update);
   GetControl (IDC_ST_WU_UNIT)->Enable (update);
   GetControl (IDC_CB_WU_WRKT)->Enable (update);
   GetControl (IDC_ST_WU_WRKT)->Enable (update);
   GetControl (IDC_CB_WU_STAT)->Enable (update);
   GetControl (IDC_ST_WU_STAT)->Enable (update);
   GetControl (IDC_TXT_BATCH)->Enable (update);
   GetControl (IDC_EDT_AWD_BATCH)->Enable (update);
   GetControl (IDC_RB_RETAIN_WORK)->Enable( update );
   GetControl (IDC_CHK_AWD)->Enable (m_bCommentAccessible ? update : false);
   UpdateComment ();
}

//*****************************************************************************
void ConfirmationDlg::OnRbUpdateExisting()
{
   GetDlgItem (IDC_CB_WU_UNIT)->EnableWindow ( true );           // Business Area - Combo
   GetDlgItem (IDC_ST_WU_UNIT)->EnableWindow ( true );           // Business Area - Static Text
   GetDlgItem (IDC_CB_WU_WRKT)->EnableWindow ( true );           // Work Type - Combo
   GetDlgItem (IDC_ST_WU_WRKT)->EnableWindow ( true );           // Work Type - Static Text
   GetDlgItem (IDC_CB_WU_STAT)->EnableWindow ( true );           // Status - Combo
   GetDlgItem (IDC_ST_WU_STAT)->EnableWindow ( true );           // Status - Static Text
   GetDlgItem (IDC_TXT_BATCH)->EnableWindow ( true );           // Batch - Text
   GetDlgItem (IDC_EDT_AWD_BATCH)->EnableWindow ( true );        // Batch - Edit
   if (m_bCommentAccessible)
   {
      GetDlgItem (IDC_CHK_AWD)->EnableWindow (true);               // AWD Comment - Checkbox	  
   }
}

//*****************************************************************************

void ConfirmationDlg::OnRbCreateNew()
{
   GetDlgItem( IDC_CB_WU_UNIT )->EnableWindow( true );            // Business Area - Combo
   GetDlgItem( IDC_ST_WU_UNIT )->EnableWindow( true );            // Business Area - Static Text
   GetDlgItem( IDC_CB_WU_WRKT )->EnableWindow( true );            // Work Type - Combo
   GetDlgItem( IDC_ST_WU_WRKT )->EnableWindow( true );            // Work Type - Static Text
   GetDlgItem(IDC_TXT_BATCH)->EnableWindow( true );               // Batch - Text
   GetDlgItem(IDC_EDT_AWD_BATCH)->EnableWindow( true );              // Batch - Edit

   DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   DString dstrStatus (NULL_STRING);
   bool bCallStart = false;

   if (pSession)
   {
      pSession->getAwdField(ifds::StatusDesc, dstrStatus);
      dstrStatus.stripAll();
      bCallStart = pSession->isCallStarted();
   }

   GetDlgItem (IDC_CB_WU_STAT)->EnableWindow (dstrStatus == NULL_STRING || !bCallStart);            // Status - Combo
   GetDlgItem (IDC_ST_WU_STAT)->EnableWindow (true);            // Status - Static Text
   if (m_bCommentAccessible)
   {
      GetDlgItem( IDC_CHK_AWD )->EnableWindow (true);               // AWD Comment - Checkbox
   }
}

//*****************************************************************************

void ConfirmationDlg::OnBtnWrkObject()
{
	DSTButton *checkAwdBtn = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_AWD));
	DSTButton *checkWOBtn = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_WORKOBJECT));
	if( checkAwdBtn && checkWOBtn )
	{
		if (m_bCommentAccessible && checkWOBtn->GetCheck() == 1 )
		{			       
		   {
		      checkAwdBtn->SetCheck (1);
		   }
		}
		else
		{
			checkAwdBtn->SetCheck (0);
		}
	}
}

//*****************************************************************************
void ConfirmationDlg::OnRbNone()
{

   GetDlgItem( IDC_CB_WU_UNIT )->EnableWindow( false );           // Business Area - Combo
   GetDlgItem( IDC_ST_WU_UNIT )->EnableWindow( false );           // Business Area - Static Text
   GetDlgItem( IDC_CB_WU_WRKT )->EnableWindow( false );           // Work Type - Combo
   GetDlgItem( IDC_ST_WU_WRKT )->EnableWindow( false );           // Work Type - Static Text
   GetDlgItem( IDC_CB_WU_STAT )->EnableWindow( false );           // Status - Combo
   GetDlgItem( IDC_ST_WU_STAT )->EnableWindow( false );           // Status - Static Text
   GetDlgItem( IDC_TXT_BATCH )->EnableWindow( false );            // Batch - Text
   GetDlgItem( IDC_EDT_AWD_BATCH )->EnableWindow( false );           // Batch - Edit

   if (m_bCommentAccessible)
   {
	  DSTButton *checkAwdBtn = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_AWD));
	  if( checkAwdBtn )
	  {
         checkAwdBtn->SetCheck (0);
	  }
	  GetDlgItem (IDC_CHK_AWD)->EnableWindow( false );              // AWD Comment - Checkbox
   }
}



//*****************************************************************************
void ConfirmationDlg::OnChkAwdOrRemark ()
{
   if (!m_bCommentAccessible)
   {
      return;
   }
   UpdateComment ();
}

//*****************************************************************************
void ConfirmationDlg::OnRbEnd()
{
   getParent()->setField( this, BF::NullContainerId, CONFPROC::CHOICE_FIELD, CONFPROC::END );
}

//*****************************************************************************
void ConfirmationDlg::OnRbGetWork()
{
   getParent()->setField( this, BF::NullContainerId, CONFPROC::CHOICE_FIELD, CONFPROC::GETWORK );
}

//*****************************************************************************
void ConfirmationDlg::OnRbRefresh()
{
   getParent()->setField( this, BF::NullContainerId, CONFPROC::CHOICE_FIELD, CONFPROC::REFRESH );
}

//*****************************************************************************
void ConfirmationDlg::OnRbNewSearch()
{
   getParent()->setField( this, BF::NullContainerId, CONFPROC::CHOICE_FIELD, CONFPROC::NEWSEARCH );
}

//*****************************************************************************
void ConfirmationDlg::OnRbCloneUpdate ()
{

   CButton *pBt = (CButton*)( GetDlgItem( IDC_RD_CLONE_UPDATE ) );

   if( pBt != NULL && pBt->GetCheck() == 1)
   {
      DSTButton *checkEndBtn = dynamic_cast <DSTButton*> (GetControl (IDC_RB_END));
      DSTButton *checkGetworkBtn = dynamic_cast <DSTButton*> (GetControl (IDC_RB_GET_WORK));
      DSTButton *checkRefreshBtn  = dynamic_cast <DSTButton*> (GetControl (IDC_RB_REFRESH));

      assert (checkEndBtn);
      assert (checkGetworkBtn);
      assert (checkRefreshBtn);
      checkEndBtn->SetCheck (0); //do not have the 'End' button checked
      checkEndBtn->EnableWindow (false);
      checkGetworkBtn->EnableWindow (false);
      checkRefreshBtn->SetCheck (1);
      OnRbRefresh ();
   }
}

//*****************************************************************************
void ConfirmationDlg::OnRbUpdateOrig ()
{
   DSTButton *checkEndBtn = dynamic_cast <DSTButton*> (GetControl (IDC_RB_END));
   DSTButton *checkGetworkBtn = dynamic_cast<DSTButton*> (GetControl (IDC_RB_GET_WORK));

   assert (checkEndBtn);
   assert (checkGetworkBtn);
   checkEndBtn->EnableWindow (true);
   checkGetworkBtn->EnableWindow (true);
}

//****************************************************************************** 
void ConfirmationDlg::OnChkUpdAllCIFRelated()
{
   CWaitCursor wait;

   if (((CButton *) GetDlgItem (IDC_CHK_UPD_ALL_CIF_RELATED))->GetCheck() != 1)
	{		
		getParent()->setField ( this, 
                              IFASTBP_PROC::CONFIRMATION, 
                              ifds::UpdAllNonFin, 
                              I_("N"), 
                              false);
	}
	else
	{
		getParent()->setField ( this, 
                              IFASTBP_PROC::CONFIRMATION, 
                              ifds::UpdAllNonFin, 
                              I_("Y"), 
                              false);
	}
}

//*****************************************************************************
void ConfirmationDlg::UpdateComment()
{
   DSTButton *checkRemarkBtn = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_REMARK ) );
   DSTButton *checkAwdBtn = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_AWD ) );
   DSTEdit *remarkEdit = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENT ) );
   DSTComboBox *pCmbRemarkType = dynamic_cast< DSTComboBox * >( GetDlgItem( IDC_CB_REMARK_TYPE ) );

   bool bEnable = ((checkRemarkBtn && checkRemarkBtn->GetCheck()) ||
                   (checkAwdBtn && checkAwdBtn->GetCheck()) ) && !m_bFromRemarks;
   if (remarkEdit)
   {
      remarkEdit->Enable( bEnable );
      bool bEnableRemark = ( checkRemarkBtn && checkRemarkBtn->GetCheck() );
      pCmbRemarkType->Enable( bEnableRemark && !m_bFromRemarks );
      remarkEdit->SetRemoveUnwantedCharsAfterPaste(true);
   }
}

//*****************************************************************************
bool ConfirmationDlg::PreOk()
{
   TRACE_METHOD( CLASSNAME, PREOK );

   GetDlgItem (IDOK)->EnableWindow (FALSE);
   bool bReturn = true;

   try
      {
         if (m_dstrCalledFrom == I_("BrowserLaunch"))
         {
            CStringArray paramArray;
            CComVariant pVarResult = NULL;
            BrowserLaunch * pBrowserLaunch = static_cast< BrowserLaunch * >(getParent()->getParent());

            if (pBrowserLaunch)
            {
               bool ret = pBrowserLaunch->CallJScript (L"update", paramArray, &pVarResult);
               
               if (ret && pVarResult.vt != VT_NULL)
               {
                  CString strupdate (_bstr_t(pVarResult).Detach ());
                  DString dstrupdate (strupdate);

                  if (dstrupdate == I_("fail"))
                  {
                     SetTransactionError (true);
                     return false;
                  }

                  CComVariant pBrowserResults;
                  
                  ret = pBrowserLaunch->CallJScript (L"getResult", paramArray, &pBrowserResults);
                  if (pBrowserResults.vt != VT_NULL)
                  {
                     CString csBrowserResults (_bstr_t(pBrowserResults).Detach ());
                     DString browserResults (csBrowserResults);
                     
                     I_CHAR *temp = const_cast<I_CHAR*> (browserResults.c_str ());

                     do
                     {
                        DString tag,
	                        value;

                        temp = parseIdiString (temp, tag, value);

                        if (I_("AccountNum") == tag && !value.empty())
                        {
                           setGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, value);
                        }
                        else if (I_("ShareholderNum") == tag && !value.empty())
                        {
	                        setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, value);
                        }

                     } while (temp && temp != NULL_STRING && *temp);
                  }
               }
            }
         }
      }
      catch(...)
      {
         //failed java script call
      }


   bool bChecked = false;
   // Make sure values exist for Business Area, Work Type, and Status for AWD
   DSTButton *pChkbox = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_WORKOBJECT ) );
   if( pChkbox )
   {
      bChecked = (pChkbox->GetCheck() == 1);
   }
   if( !m_bAwdDisabled && bChecked )
   {
      bool bFoundEmpty = false;
      CString cstrValue;
      GetDlgItemText( IDC_CB_WU_UNIT, cstrValue );
      bFoundEmpty = ( cstrValue.IsEmpty() == TRUE );
      GetDlgItemText( IDC_CB_WU_WRKT, cstrValue );
      bFoundEmpty |= ( cstrValue.IsEmpty() == TRUE );
      GetDlgItemText( IDC_CB_WU_STAT, cstrValue );
      bFoundEmpty |= ( cstrValue.IsEmpty() == TRUE );

      if( bFoundEmpty )
      {
         AfxMessageBox( TXT_AWD_VALUES_REQUIRED, MB_OK | MB_ICONSTOP );
         bReturn = false;
      }
   }

   if(remarkListkey == NULL || !bReturn )
   { //if business does not require add remark to database
      // or there is error on AWD fields, skip create remark
      return bReturn;
   }
   int iAddRemark = 0;
   CButton *pChkRemark = dynamic_cast<CButton*>( GetControl( IDC_CHK_REMARK ) );
   if(pChkRemark )
   {
      iAddRemark = pChkRemark->GetCheck();
   }

//check if user inputs some comments
   CString cstrRemarkComment;
   GetDlgItemText (IDC_EDT_COMMENT, cstrRemarkComment);
   cstrRemarkComment.TrimLeft();

   if( iAddRemark == 0 || cstrRemarkComment.IsEmpty() )
   {
         getParent()->resetCurrentItem(IFASTBP_PROC::REMARKS_LIST);
       // user does not want to create a remark in shareholder remark,
       //or user does not input any remark
       // the remark should be back to dummy item
       return( bReturn );
   }
   if( iAddRemark ==  1 )
   {
      //now business allow create shareholder remark and user wantS to create remark
      // remark control is not empty
      // always points to the item just created
      getParent()->setCurrentListItem(this,IFASTBP_PROC::REMARKS_LIST,*remarkListkey);
       // Set the Account Num
      DString dstrAccountNum;
      getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum);
      dstrAccountNum.strip().stripLeading ('0');
      getParent()->setField (this, IFASTBP_PROC::REMARKS_LIST,
      ifds::AccountNum, dstrAccountNum, false);

   }

   return( bReturn );
}

//*****************************************************************************
void ConfirmationDlg::PostOk (bool bOK)
{
   //TRACE_METHOD( CLASSNAME, POSTOK );
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION,
                CLASSNAME,
                I_("POSTOK"));      

   if (bOK)
   {
      DSTButton *checkEndBtn        = dynamic_cast<DSTButton*> (GetControl (IDC_RB_END));
      DSTButton *checkRefreshBtn    = dynamic_cast<DSTButton*> (GetControl (IDC_RB_REFRESH));
      DSTButton *checkGetworkBtn    = dynamic_cast<DSTButton*> (GetControl (IDC_RB_GET_WORK));
      DSTButton *checkNewSearchBtn  = dynamic_cast<DSTButton*> (GetControl (IDC_RB_RETAIN_WORK));
      DSTButton *checkRebookBtn     = dynamic_cast<DSTButton*> (GetControl (IDC_RD_REBOOK));
      DSTButton *pCheckbox          = dynamic_cast<DSTButton*> (GetControl (IDC_CHK_WORKOBJECT));

      bool bChecked = false;

      if (pCheckbox)
      {
         bChecked = (pCheckbox->GetCheck() == 1);
      }
      // Update AWD Work Object
      if (!m_bAwdDisabled && bChecked)
      {
         SetAWDUpdate();
      }

      CDSTCView* dstcView = ((CDSTCView*)GetMainView());
      if(dstcView->HasWorkEvent()) 
      {
         DSTButton *checkAWD = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_AWD ) );
         if( (checkAWD != NULL) && checkAWD->GetCheck() )
         {
            CString cstrComments;
            GetDlgItemText(IDC_EDT_COMMENT, cstrComments);
   			if( !cstrComments.Trim().IsEmpty() )
            {
               dstcView->SetWorkComment(DString(cstrComments));
            }
         }

      }

      DString dstrCreatingShareholder;

      getParent()->getField ( this,
                              BF::NullContainerId,
                              CONFPROC::CREATING_SHAREHOLDER,
                              dstrCreatingShareholder);
      GenericInterfaceContainer* pGIC = getGIContainer();
      DSTCWorkSession *pDSCTWorkSession = dynamic_cast <DSTCWorkSession *>(getParent()->getBFWorkSession());
      GenericInterface* pGITransHistory (NULL);

      assert (pDSCTWorkSession);
      if (pGIC)
      {
         pGITransHistory = pGIC->findGI (getBFWorkSession(), CMD_BPROC_TRANS_HISTORY);
      }

      ((CDSTCView*)GetMainView())->UpdateWorkEvent();

//kill the work session and close everything
      if (checkEndBtn != NULL && checkEndBtn->GetCheck() == 1)
      {
         if (dstrCreatingShareholder == Y)
         {
            DString dstrAccountNum,
               dstrShrNum;

            getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum);
            getGlobal (WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum);

            CString cstrMsgA,
               cstrMsgB;

            cstrMsgA.LoadString (TXT_NEW_ACCOUNT);
            cstrMsgB.LoadString (TXT_NEW_SHRNUM);
            cstrMsgA = cstrMsgA + dstrAccountNum.stripLeading( '0' ).c_str();
            cstrMsgB = cstrMsgB + dstrShrNum.stripLeading( '0' ).c_str();
            cstrMsgA = cstrMsgA + "\n" + cstrMsgB;
            AfxMessageBox (cstrMsgA, MB_OK | MB_ICONINFORMATION);
         }
         ((CDSTCView*)GetMainView())->setCurrWorkSessionPGI (getWorkSession());
         const Command rCmd = getParent()->getParent()->getCommand();
         
         if(m_CommitParentDataGroups == NULL_STRING &&
            (!rCmd.isModal() || rCmd.getKey() != I_("GUIDLG_BROWSER_LAUNCH")))
         {
            GetMainView()->PostMessage (UM_ENDCURRENTSESSION, IDC_BTN_END, 0);
         }
         else
         {
            BFWorkSession * worksession = getBFWorkSession();
            worksession->setIsEndSession(true);
         }

         if (m_dstrCalledFrom == I_("FeeModelCopyToGroup")){
            CString cstrMsgA;
            cstrMsgA.LoadString(IDS_FEEMODEL_COPIED_TO_HOUSEHOLD);
            AfxMessageBox (cstrMsgA, MB_OK | MB_ICONINFORMATION);
         }
      }
      else if (checkGetworkBtn != NULL && checkGetworkBtn->GetCheck() == 1)
      {
         GetMainView()->PostMessage (WM_COMMAND, IDC_BTN_GETWORK);
      }
      else if (checkRefreshBtn != NULL && checkRefreshBtn->GetCheck() == 1)
      {
         if (m_dstrCalledFrom == I_("BrowserLaunch") && m_InvokedBrowserScreen == CMD_BPROC_SMART_FORM)
         {
            dstrCreatingShareholder = Y;
         }

         pDSCTWorkSession->refreshData ();
         if (dstrCreatingShareholder == Y )
         {
            GetMainView()->PostMessage (UM_LAUNCHDETAILS);
         }
         
//see whether we can refresh the transaction history screen
         if (( m_dstrCalledFrom == CALLED_FROM_TXNCANCEL ||
               m_dstrCalledFrom == CALLED_FROM_REBOOK ||
               m_dstrCalledFrom == CALLED_FROM_SAVINGS_DIRECTIVE ||
               m_dstrCalledFrom == CALLED_FROM_TRANS_HIST_DILUTION) && pGITransHistory) //if exists...
         {
            pGITransHistory->send (this, I_("RefreshHistory"));
         }

         if (m_dstrCalledFrom == I_("HoldingComp"))
         {
            GetMainView()->PostMessage (UM_HOLDING_COMP);
         }

      }
      else if (checkNewSearchBtn != NULL && checkNewSearchBtn->GetCheck() == 1)
      {
         GetMainView()->PostMessage (UM_NEWSEARCH);
      }
      else if (checkRebookBtn != NULL && checkRebookBtn->GetCheck  () == 1)
      {
         //refresh the work session
         pDSCTWorkSession->refreshData ();
//see whether we can refresh the transaction history screen
         if (m_dstrCalledFrom == CALLED_FROM_TXNCANCEL && pGITransHistory) //if exists...
         {
            setParameter (I_("Batch"), m_dstrBatchNum);
            pGITransHistory->send (this, I_("RefreshAndRebook"));
         }
      }
   }
   GetDlgItem( IDOK )->EnableWindow( TRUE );
}

//*****************************************************************************

void ConfirmationDlg::OnSelchangeCbWuUnit()
{
   // TODO: Add your control notification handler code here

   CString cstrBusArea;

   GetDlgItemText ( IDC_CB_WU_UNIT, cstrBusArea );
   if( cstrBusArea.IsEmpty() )
   {
      return;
   }
//yingbao added
   DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   if( pSession )
   {

      string_vector listWorkType = pSession->getWorkTypeList( (DString) cstrBusArea );
      CComboBox *pCmbWT = (CComboBox*) GetDlgItem(IDC_CB_WU_WRKT);
      pCmbWT->ResetContent();
      string_vector_const_iterator iter = listWorkType.begin();
      while( iter != listWorkType.end() )
      {
        pCmbWT->AddString(( *iter ).c_str());
        iter++;
      }

   }

   if( m_bRefreshStatusList )
   {
	   updateStatusList();
   }
}

//*****************************************************************************

void ConfirmationDlg::OnSelchangeCbWuWkType()
{
   updateStatusList();
}

//*****************************************************************************

void ConfirmationDlg::SetAWDUpdate()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("SetAWDUpdate()") );
   SEVERITY severity = NO_CONDITION;


//yingbao start

      DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
      if( pSession && m_pAwdSession )
      {
         // save business area, worktype and status to session object.  // may be we don't need
         CString cstr;
         GetDlgItemText(IDC_CB_WU_UNIT, cstr);
         pSession->setAwdField(ifds::BusinessArea,LPCTSTR( cstr ) );
         GetDlgItemText(IDC_CB_WU_WRKT, cstr);
         pSession->setAwdField(ifds::WorkType,LPCTSTR( cstr ) );
         GetDlgItemText(IDC_CB_WU_STAT, cstr);
         pSession->setAwdField(ifds::StatusDesc,LPCTSTR( cstr ) );
         GetDlgItemText(IDC_EDT_AWD_BATCH, cstr);
         pSession->setAwdField(ifds::Batch, LPCTSTR( cstr ) );

         DString dstrAccountNum;
         getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
         dstrAccountNum.stripLeading('0');
         pSession->setAwdField(ifds::AccountNum, dstrAccountNum );

         bool bClone = false;
         bool bUpdateOrg = false;
         if( !m_bCreateNew )
         {
             CButton *pBt = (CButton*)( GetDlgItem( IDC_RD_CLONE_UPDATE ) );
             bClone = pBt->GetCheck() == 1;
             pBt = (CButton*)( GetDlgItem( IDC_RD_UPADET_ORIG ) );
             bUpdateOrg = pBt->GetCheck() == 1;
         }
         if( bClone )
         {
            if( pSession->cloneAwdObject( ) > WARNING )
            {
               //there is some issue in clone, do not continue
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               return;
            }
         }
         DSTButton *checkAWD = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_AWD ) );
         pSession->setAwdField(SessionTags::AWD_COMMENT, NULL_STRING );
         if( (checkAWD != NULL) && checkAWD->GetCheck() )
         {
            GetDlgItemText(IDC_EDT_COMMENT, cstr);
			if( !cstr.Trim().IsEmpty() )
			{
               pSession->setAwdField(SessionTags::AWD_COMMENT,LPCTSTR( cstr ) );
			}
         }
         DString  dstrAWDEventType = ( m_bCreateNew ? SessionTags::CREATE_WORK : SessionTags::UPDATE_WORK);
         if( pSession->CallInquiryUpdate(I_("UPDATE AWD" ),dstrAWDEventType,bUpdateOrg ) >= WARNING )
         {
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
         DSTButton *checkEndBtn     = dynamic_cast<DSTButton*>( GetControl( IDC_RB_END ) );
         if( checkEndBtn->GetCheck() )
         {

            if( !(pSession->isOrgWorkUpdated() ) && pSession->canClone() )
            {
               //display errormessage give user a choice.
               DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_AWD_MSGA, TXT_DISCARD_AWD_MSGB, TXT_DISCARD,TXT_CANCELED);
               if( discardDlg.DoModal() == IDCANCEL )
               {

                return;
               }

            }


            pSession->EndCall();

         }
      }


}

//******************************************************************************

void ConfirmationDlg::doPaste( UINT controlID )
{
   if( controlID == IDC_EDT_COMMENT )
   {
      m_FormatRemarksCount = 0;
   }
   return;
}

//******************************************************************************

void ConfirmationDlg::OnEnChangeRemarkComment()
{
   DSTEdit* remarkEdit = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENT ) );   
   //when a text is selected in the edit box and another piece of text is being pasted - to replace the selection -
   //OnEnChangeRemarkComment() is called twice: once with the selection empty and once with the selection replaced by the new text;
   //therefore, we need to format the paragraph twice ( m_FormatRemarksCount < 2 )
   //also, we don't want to interfere with word wrapping ( !remarkEdit->isWordWrappingInProcess() )
   if( remarkEdit != NULL && m_FormatRemarksCount < 2 && !remarkEdit->isWordWrappingInProcess() )
   {	  
      CString strText;		
      int iStart,iEnd, iOffset;
      remarkEdit->GetSel(iStart, iEnd);
      remarkEdit->GetWindowText( strText );	  
	  formatParagraph( strText, iOffset, MAX_CHAR_NUM_OF_REMARK, MAX_NUM_LINES_FOR_REMARKS );	  
      remarkEdit->SetWindowText( strText );
      remarkEdit->SetSel(iStart+iOffset, iEnd+iOffset);	  
      m_FormatRemarksCount++;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfirmationDlg.cpp-arc  $
 * 
 *    Rev 1.122   Aug 10 2012 17:23:46   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.121   Aug 10 2012 12:21:08   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.120   Aug 09 2012 14:26:48   dchatcha
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.119   Feb 22 2012 04:49:52   panatcha
 * IN2831230 - Fund limitation update not displaying in option window box
 * 
 *    Rev 1.118   May 17 2011 11:17:06   jankovii
 * IN 2528057 - Account Number on Confirmation Dialog is incorrect
 * 
 *    Rev 1.117   Apr 29 2011 10:06:30   jankovii
 * Sync up: IN 2511918 - Desktop refresh not working properly with SF
 * 
 *    Rev 1.116   Mar 28 2011 09:27:36   yingz
 * Fix incident 2423066 where correct business area cannot be selected when there are multiple business area starting with same prefix.
 * 
 *    Rev 1.115   Jan 14 2011 16:48:38   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.114   Nov 26 2010 15:19:40   popescu
 * PET0165541 FN03 - QESI Phase3 - fixed overlapping of the confirmation when a transaction error pops-up
 * 
 *    Rev 1.113   Mar 26 2010 14:26:10   popescu
 * QESI - Modified the way we are looking at the success/fail updates from the browser screens when the confirmation dialog pops up
 * 
 *    Rev 1.112   27 May 2009 10:23:14   popescu
 * Autobatch - passed the name of the batch to reebok functionality
 * 
 *    Rev 1.111   24 Oct 2008 15:32:04   kovacsro
 * IN#1403926 - R87 AWD issues regarding remarks formatting
 * 
 *    Rev 1.110   16 May 2008 13:29:06   kovacsro
 * IN#1223298 - formatting remarks
 * 
 *    Rev 1.109   05 May 2008 14:51:26   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.108   04 Mar 2008 15:24:50   kovacsro
 * IN#1118130 - check AWD comments by default, whenever there's an active AWD object around or the user creates a new AWD object
 * 
 *    Rev 1.107   01 Feb 2008 09:06:02   kovacsro
 * IN#1118094&1114586 - filtering the status list on the queue, bussArea and workType for AWD
 * 
 *    Rev 1.106   21 Jan 2008 11:43:10   kovacsro
 * IN#1132965 - disabled the OK button during a confirmation transaction. If the transaction fails, the OK button should be re-enabled
 * 
 *    Rev 1.105   16 Jan 2008 09:33:52   kovacsro
 * IN#1103220 - fixed trimming the remarks when length is greater than 700 and also fixed the issue with only one line instead of 10
 * 
 *    Rev 1.104   12 Nov 2007 23:44:18   popescu
 * PET 5653/01 - Internal Audit project
 * 
 *    Rev 1.103   02 Nov 2007 17:01:46   popescu
 * Internal Audit Project passed in AWDObjectId to views that have the field
 * 
 *    Rev 1.102   01 Aug 2007 09:45:40   popescu
 * GAP 6 - CIF - also added UpdateAllCIF for vew 85
 * 
 *    Rev 1.101   17 Jul 2007 15:19:08   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.100   May 14 2007 11:18:42   ivespaul
 * Incident #885542 - New env setup for destkop web and cleanup.
 *
 *    Rev 1.99   Mar 23 2007 10:57:48   popescu
 * Incident# 836286 - fixed crash in DSK when user clones an item and the system pushes the 'Created' status in the status list of the Confirmation Dlg combo.
 *
 *    Rev 1.98   Mar 13 2007 15:35:50   popescu
 * Incident# 831808 - fix the CloneAccount freeze.
 *
 *    Rev 1.97   Dec 19 2006 16:56:50   fengyong
 * PET2282 FN01 - Add Clone Account web page
 *
 *    Rev 1.96   Dec 06 2006 14:57:10   fengyong
 * Incident #763433 - refresh account detail after ok on fund limitation page
 *
 *    Rev 1.95   Sep 18 2006 15:11:58   ZHANGCEL
 * Incident #711931 -- Fix the tab issue to ensure that "End" and "Get Work" only grey out if user choose "Clone and Update"
 *
 *    Rev 1.94   Jun 08 2006 17:32:00   fengyong
 * Add BrowserLaunch
 *
 *    Rev 1.93   May 08 2006 11:43:04   popescu
 * Incident# 613483 - the standard  'Confirmation' window will pop-up for entering AWD Comments - enhancement
 *
 *    Rev 1.92   May 05 2006 17:19:00   popescu
 * Incident# 613476 - disable the GetWork and End buttons if user chooses clone and update.
 *
 *    Rev 1.91   Jan 24 2006 12:36:58   popescu
 * Incident# 524855 - enable 'refresh' button on confirmation dialog screen after dilution is modified
 *
 *    Rev 1.90   Jan 23 2006 13:55:14   zhengcon
 * Incident #521273 -- Auto Clone - Integration  - Add new LOB (Batch) field to confirmation
 *
 *    Rev 1.89   Dec 18 2005 14:48:48   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 *
 *    Rev 1.88   Nov 29 2005 15:24:26   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 *
 *    Rev 1.87   Nov 24 2005 16:30:26   porteanm
 * PET1286 FN01 - Bulk Cancellation.
 *
 *    Rev 1.86   Sep 15 2005 15:11:06   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 *
 *    Rev 1.85   Aug 17 2005 11:36:44   popescu
 * Incident 377523 - fixed the refresh error 'Dilution Records already exist' after user cancels and rebooks a transaction. Correctly removed the trans cancelation update data at the worksession level.
 *
 *    Rev 1.84   Jul 20 2005 09:54:56   Yingbaol
 * PET1235,FN01:fix refresh issue
 *
 *    Rev 1.83   Jul 15 2005 09:28:02   Yingbaol
 * PET1235,FN01: pass parameters
 *
 *    Rev 1.82   Jul 08 2005 09:41:14   Yingbaol
 * PET1235,FN01:Transaction cancellation rebook
 *
 *    Rev 1.81   Jun 20 2005 18:41:58   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 *
 *    Rev 1.80   Jun 20 2005 06:24:48   popescu
 * PET1024 FN40 - Guarantee Adjustments - displayed the Warning Conditions Message Box.
 *
 *    Rev 1.79   Jun 16 2005 10:57:58   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 *
 *    Rev 1.78   Jun 13 2005 15:53:04   Fengyong
 * #Incident 328345 - if call from modifypendingtrade with loss, disable end button.
 *
 *    Rev 1.77   Apr 12 2005 10:31:54   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 *
 *    Rev 1.76   Mar 08 2005 19:06:02   Fengyong
 * PET1190 FN04 - do not enable refresh button for cancellation submit.
 *
 *    Rev 1.75   Feb 22 2005 15:16:30   ZHANGCEL
 * Incident #248320 -- Disable <Refresh> button on Confirmation screen for AggaregatedOrder
 *
 *    Rev 1.74   Jan 17 2005 18:25:10   hernando
 * PTS10037736 - Removed reference to AWDEVENT.
 *
 *    Rev 1.73   Sep 21 2004 17:00:54   FENGYONG
 * disable refresh button for FeeModel screen
 *
 *    Rev 1.72   Aug 24 2004 16:21:22   YINGBAOL
 * PTS10032997: promot warning message if user does not update the original AWD object
 *
 *    Rev 1.71   Jul 19 2004 09:47:56   YINGBAOL
 * PTS10030071: Change the sequence of populating data.
 *
 *    Rev 1.70   May 27 2004 17:20:36   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 *
 *    Rev 1.69   May 19 2004 11:34:28   YINGBAOL
 * PET1017:fix display clone label when user does not use AWD
 *
 *    Rev 1.68   May 11 2004 14:24:44   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 *
 *    Rev 1.67   May 11 2004 10:55:24   YINGBAOL
 * PET1017:fixed display control while user does not use AWD
 *
 *    Rev 1.66   May 07 2004 15:51:16   FENGYONG
 * temp check in for other enhancement, PET1046fr1
 *
 *    Rev 1.65   May 04 2004 12:12:30   YINGBAOL
 * PET1017:Implement clone function
 *
 *    Rev 1.64   Apr 01 2004 12:20:12   HERNANDO
 * PTS10028598 - Disabled AWD frame and hid the checkbox when AWD is not active.
 *
 *    Rev 1.63   Mar 31 2004 16:22:04   YINGBAOL
 * PTS10028705: reimplement update shareholder remarks logic.
 *
 *    Rev 1.62   Mar 31 2004 10:18:58   HERNANDO
 * PTS10028598 - Added check box to determine whether to create/update work objects.
 *
 *    Rev 1.61   Mar 26 2004 17:27:26   HERNANDO
 * PTS10028590 - Clear AWD Comments.
 *
 *    Rev 1.60   Mar 22 2004 17:42:08   YINGBAOL
 * PTS10028360:change work type status
 *
 *    Rev 1.59   Mar 12 2004 10:36:42   YINGBAOL
 * PTS10027730: add CREATE work type when there is no CREATE worktype in AWD list
 *
 *    Rev 1.58   Mar 04 2004 08:53:54   YINGBAOL
 * PTS27730:Disable getwork radio butoon, when there is a call.
 *
 *    Rev 1.57   Feb 20 2004 10:54:56   YINGBAOL
 * PTS10027247:When user select End radio button,also end call
 *
 *    Rev 1.56   Jan 21 2004 11:47:46   YINGBAOL
 * PET987:Set status based on if there is a call
 *
 *    Rev 1.55   Jan 19 2004 17:40:54   YINGBAOL
 * PET987: always create AWD object there is a call
 *
 *    Rev 1.54   Jan 15 2004 11:29:40   YINGBAOL
 * PET:987 save last account number
 *
 *    Rev 1.53   Jan 12 2004 14:57:36   YINGBAOL
 * PET987: convert to DSTCAWDInterface
 *
 *    Rev 1.52   Dec 30 2003 16:27:08   HERNANDO
 * PET910 - Set object settings if settings are defined in the integration file.  If status is defined, set to read-only.  On a call, end date/time for the object will be established and used for the next object.
 *
 *    Rev 1.51   Dec 23 2003 08:41:54   HERNANDO
 * Synch'd with 1.49.1.0 - PTS 10025244, fix crash in ConfirmationDialog.
 *
 *    Rev 1.50   Dec 23 2003 08:37:16   HERNANDO
 * PET987 - Removed Create, Update, None radio buttons and replaced with label.  Fixed status list display.
 *
 *    Rev 1.49   Dec 15 2003 18:02:00   HERNANDO
 * Changed Status list.  Uses Status List based on existing queue.  First list item is default.  If no object, use the entire list.
 *
 *    Rev 1.48   Nov 23 2003 17:05:36   HERNANDO
 * PET892 FN1 - Disabled refresh if called from Settlement Location at System Level.
 *
 *    Rev 1.47   Oct 03 2003 11:06:42   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key
 *
 *    Rev 1.46   Oct 03 2003 10:10:58   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key - Work in progress
 *
 *    Rev 1.45   Jul 30 2003 11:27:22   FENGYONG
 * CIBC enhancement PET809_FN46
 *
 *    Rev 1.44   May 15 2003 11:25:08   HERNANDO
 * Disable refresh for Manual Dividends.
 *
 *    Rev 1.43   Mar 21 2003 18:34:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 *
 *    Rev 1.42   Jan 31 2003 11:25:22   HERNANDO
 * Disable refresh if from Market Index.
 *
 *    Rev 1.41   Jan 21 2003 13:20:48   YINGBAOL
 * fix account number issue
 *
 *    Rev 1.40   Nov 25 2002 10:09:58   YINGBAOL
 * add logic for AMS Global screen
 *
 *    Rev 1.39   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.38   Aug 29 2002 18:14:30   SMITHDAV
 * Additional FieldId fixes.
 *
 *    Rev 1.37   Aug 29 2002 12:57:20   SMITHDAV
 * ClientLocale and typed field changes.
 *
 *    Rev 1.36   Aug 26 2002 17:23:36   HERNANDO
 * Precautionary code - removed tabs from values referenced in the .ini tables for AWD.
 *
 *    Rev 1.35   Jul 12 2002 15:52:22   HERNANDO
 * Fixed bug - Prevent sending text after deselecting remarks radio button.  Added reset call.
 *
 *    Rev 1.34   May 28 2002 12:19:48   PURDYECH
 * BFData Implementation - Phase II
 *
 *    Rev 1.33   22 May 2002 19:15:54   PURDYECH
 * BFData Implementation
 *
 *    Rev 1.32   26 Apr 2002 10:37:50   KOVACSRO
 * Added CTRLFLAG_WORD_WRAP flag for Remarks.
 *
 *    Rev 1.31   19 Apr 2002 19:25:26   HERNANDO
 * Added refreshData of dstWorkSession in PostOk.  Added GUI_AWD_FAILED_UPDATE_OR_CREATE.
 *
 *    Rev 1.30   15 Apr 2002 14:52:26   HERNANDO
 * PTS 10007576 - Implement New Search.  Also added condition message box if AWD Update/Create failed.
 *
 *    Rev 1.29   27 Mar 2002 20:01:02   PURDYECH
 * Process/WindowFactory overhaul
 *
 *    Rev 1.28   Mar 25 2002 17:26:18   HERNANDO
 * PTS 10007573 - Removed Trade button.
 *
 *    Rev 1.26   Mar 20 2002 15:54:02   HERNANDO
 * Removed Trade Button.  Removed None Button.  Changed Create New and Update Existing.
 *
 *    Rev 1.25   Mar 15 2002 13:59:54   HERNANDO
 * Removed (Commented-out) Batch number.
 *
 *    Rev 1.24   Mar 07 2002 16:48:16   HERNANDO
 * PTS 10006922 - Set focus appropriately.  With no AWD, default End unless Edit available.
 *
 *    Rev 1.23   19 Nov 2001 11:02:58   HSUCHIN
 * re-enable refresh btn from trade process
 *
 *    Rev 1.22   Nov 13 2001 14:03:52   HERNANDO
 * Improved use of AWD Interface - increase speed, single reference.
 *
 *    Rev 1.21   Nov 09 2001 11:09:50   JANKAREN
 * bug fix for disabling refresh button when fire from trading screen
 *
 *    Rev 1.20   Nov 07 2001 11:19:04   JANKAREN
 * Disable refresh buttton when calling from trading screen
 *
 *    Rev 1.19   Jul 09 2001 19:12:00   HERNANDO
 * Sync w/1.17.2.0 - Chg call fr/ getExportAwdConvertedDataB to getExportAwdConvertedData
 *
 *    Rev 1.18   03 May 2001 14:07:30   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.17   Feb 23 2001 13:49:40   YINGBAOL
 * fix multiline edit isuues
 *
 *    Rev 1.16   Feb 19 2001 15:54:08   HERNANDO
 * Added msg post for GetWork button.
 *
 *    Rev 1.15   Jan 03 2001 10:39:08   ZHANGCEL
 * Added the logic for the "Trading" radio button enable and disable stuffs.
 *
 *    Rev 1.14   Nov 09 2000 15:08:30   HERNANDO
 * AWD is updated on confirmation always unless specified.  Fixed AWD not updating on Refresh
 *
 *    Rev 1.13   Nov 09 2000 14:38:20   HSUCHIN
 * AWD is updated on confirmation always unless specified.  Fixed AWD not updating on Refresh etc...
 *
 *    Rev 1.12   Nov 09 2000 12:23:56   HSUCHIN
 * Changed the AWD Status combo to display the next status based on the work object
 *
 *    Rev 1.11   Nov 01 2000 17:52:56   HERNANDO
 * Added alternate check for MGMCO table.
 *
 *    Rev 1.10   Oct 11 2000 14:39:26   KOVACSRO
 * If called from IdentAccProcess, disabled End and Refresh buttons. Also flow returns now to the original Trading screen (it is not re-launched).
 *
 *    Rev 1.9   Sep 29 2000 11:57:02   HERNANDO
 * Checks for Session before attempting to get AwdSession
 *
 *    Rev 1.8   Sep 27 2000 17:49:42   HERNANDO
 * Chg'd Business Logic - by default, use existing AWD work object settings over Create (Settings)
 *
 *    Rev 1.7   Sep 26 2000 17:24:26   HERNANDO
 * Added check to determine whether AWD is accessible.
 *
 *    Rev 1.6   Sep 20 2000 17:35:40   HERNANDO
 * AWD Integration; implement assigner, create AWD objs. use RRADMIN Event settings.
 *
 *    Rev 1.5   Aug 28 2000 18:06:24   HERNANDO
 * Made changes.
 *
 *    Rev 1.4   Aug 25 2000 10:43:20   YINGBAOL
 * add trade screen to NASU flow
 *
 *    Rev 1.3   Aug 24 2000 15:34:38   HERNANDO
 * AWD Work Object used to define controls
 *
 *    Rev 1.2   Aug 14 2000 15:23:48   HERNANDO
 * Revised
 *
 *    Rev 1.1   Apr 05 2000 12:03:08   DT24433
 * removed unused headers and use of GIC
 *
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.34   Feb 02 2000 18:10:00   BUZILA
 * changes
 *
 *    Rev 1.33   Jan 26 2000 19:37:50   DT24433
 * changed to not set TRXNS_ERROR parm and moved transaction error code to basemaindlg
 *
 *    Rev 1.32   Jan 26 2000 19:43:12   VASILEAD
 * Fixes
 *
 *    Rev 1.31   Jan 25 2000 11:42:06   POPESCUS
 * fix for the crash in systematics
 *
 *    Rev 1.30   Jan 23 2000 18:27:48   POPESCUS
 * disable remarks when no global account num and shareholder num exist
 *
 *    Rev 1.29   Jan 23 2000 16:58:26   POPESCUS
 * fixed the bug that freezes the app after errors in trxns and updated remarks in confirmation
 *
 *    Rev 1.28   Jan 21 2000 17:24:18   HSUCHIN
 * Dialog caption change
 *
 *    Rev 1.27   Jan 21 2000 16:33:10   HSUCHIN
 * bug fix
 *
 *    Rev 1.26   Jan 21 2000 16:22:00   HSUCHIN
 * calls DSTCommonFunctions to get Entity name rather than Global
 *
 *    Rev 1.25   Jan 21 2000 14:36:38   HSUCHIN
 * kills worksession when there is errors committing transactions and some awd stuff
 *
 *    Rev 1.24   Jan 19 2000 09:36:04   HSUCHIN
 * check in for Mihai
 *
 *    Rev 1.23   Jan 18 2000 16:36:44   HSUCHIN
 * changed the refresh to post a message to the main app rather than send the message
 *
 *    Rev 1.22   Jan 18 2000 11:29:54   POPESCUS
 * fixed some of the settings of the global values (account & shareholder)
 *
 *    Rev 1.21   Jan 17 2000 14:25:30   POPESCUS
 * quick fix in remark
 *
 *    Rev 1.20   Jan 16 2000 16:58:10   POPESCUS
 * prepared for refresh and cleaned up the code
 *
 *    Rev 1.19   Jan 14 2000 15:48:10   HSUCHIN
 * re-enable remarks
 *
 *    Rev 1.18   Jan 14 2000 09:35:06   POPESCUS
 * get the either the last active account number or the last active shareholder number
 *
 *    Rev 1.17   Jan 10 2000 13:55:48   POPESCUS
 * small temp fixes for the NASU
 *
 *    Rev 1.16   09 Jan 2000 17:43:32   HSUCHIN
 * default date for remarks added
 *
 *    Rev 1.15   07 Jan 2000 14:09:34   HSUCHIN
 * latest infra changes and remark updates
 *
 *    Rev 1.14   04 Jan 2000 17:15:24   HSUCHIN
 * temp check in for dialog changes
 *
 *    Rev 1.13   Dec 24 1999 08:41:18   VASILEAD
 * bug fix to a bug fix
 *
 *    Rev 1.12   24 Dec 1999 08:38:40   HSUCHIN
 * bug fix for post ok
 *
 *    Rev 1.11   23 Dec 1999 15:52:06   HSUCHIN
 * sync up with latest bfbase stuff.  Confirm End call now ends work session by posting a message to dstcview (temp solution).
 *
 *    Rev 1.10   Nov 25 1999 14:43:54   HSUCHIN
 * took out commit for now
 *
 *    Rev 1.9   Nov 25 1999 10:37:14   HSUCHIN
 * support Canadian Market
 *
 *    Rev 1.8   Nov 24 1999 19:06:08   HSUCHIN
 * transaction builder called on preok.
 *
 *    Rev 1.7   Nov 22 1999 15:24:34   HSUCHIN
 * redesigned and OG usage.
 *
 *    Rev 1.6   Oct 28 1999 09:35:14   YINGZ
 * for a clean Get from PVCS!
 *
 *    Rev 1.5   Aug 24 1999 12:57:30   DT24433
 * changed commented getFieldFromCurrentListItem to getField
 *
 *    Rev 1.4   Jul 27 1999 16:06:20   BUZILA
 * Increment M2
 *
 *    Rev 1.3   Jul 20 1999 14:23:52   YINGZ
 * add hour glass
 *
 *    Rev 1.2   Jul 20 1999 11:18:34   VASILEAD
 * New conditions update
 *
 *    Rev 1.1   Jul 08 1999 10:04:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
