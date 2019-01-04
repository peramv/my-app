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
// ^FILE   : ChequeDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : ChequeDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef CHEQUEDLG_H
   #include "ChequeDlg.h"
#endif

#ifndef CHEQUEPROCESSINCLUDES_H
   #include <ifastbp\ChequeProcessIncludes.h>
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\dstlistctrl.h>
#endif

#ifndef  DSTSTATIC_h
   #include <uibase\DSTStatic.h>
#endif

#ifndef  DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

#ifndef DSTCGLOB_VW_HPP
   #include <ifastdataimpl\dse_DSTCGLOB_VW.hpp>
#endif

#ifndef LISTVIEWHEADING_HPP
   #include <ifastdataimpl\dse_ListViewHeading.hpp>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CHEQUE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ChequeDlg > dlgCreator( CMD_GUI_CHEQUE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME             = I_( "ChequeDlg" );
   const I_CHAR *FN_DOLISTITEMCHANGED  = I_( "DoListItemChanged" );
   const I_CHAR *FN_GETOVERRIDEITEMSTRING = I_( "GetOverrideItemString" );
   const I_CHAR *FN_ONBTNADMINDATES = I_(" OnBtnAdminDates " );
   const I_CHAR *FN_ONBTNTRANS = I_( "OnBtnTrans" );

   const I_CHAR *LV_CHEQUELIST         = I_( "Cheque List" );
   const I_CHAR *LV_CHEQUEFUNDLIST     = I_( "Cheque Fund List" );
   const I_CHAR *LV_CHEQUEREMITTANCELIST = I_( "Cheque Remittance List" );
   const I_CHAR *SUMMARY_TYPE_RECORD   = I_( "S" );
   const I_CHAR *DETAIL_TYPE_RECORD    = I_( "D" );
   const I_CHAR * const Y              = I_( "Y" );
   const I_CHAR *FUND_NUMBER           = I_( "Baycom" );
   const I_CHAR *ALL_FUND_MODE         = I_( "AllFundMode" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const CHEQUE_LIST;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ChequeAddr;
   extern CLASS_IMPORT const BFTextFieldId RemittanceChequeHeading;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

ChequeDlg::ChequeDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ChequeDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_dstrSelectedChequeKey(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ChequeDlg)
   //}}AFX_DATA_INIT
   //m_rbFixed = 1;
   //m_bRemarksInquiryAllowed = true;
}

//*****************************************************************************

void ChequeDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ChequeDlg)
   DDX_Control(pDX, IDC_BTN_ADM_DATES, m_btnAdminDates);
   DDX_Control(pDX, IDC_BTN_TRANS, m_btnTransactions);
   //}}AFX_DATA_MAP
}

//*****************************************************************************

SEVERITY ChequeDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   getParameter( CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum );
   return(NO_CONDITION);
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(ChequeDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ChequeDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_TRANS, OnBtnTrans)
ON_BN_CLICKED(IDC_BTN_CHQHISTORICAL, OnBtnHistorical)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL ChequeDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   AddListControl( CLASSNAME, IDC_LV_CHEQUES, LV_CHEQUELIST, ifds::ChequesListHeadingSet, IFASTBP_PROC::CHEQUE_LIST, 0, true );

   AddControl( CTRL_EDIT,   IDC_EDT_DEST_ADDRESS,     IFASTBP_PROC::CHEQUE_LIST, ifds::ChequeAddr, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_TRANS_NBR,        IFASTBP_PROC::CHEQUE_LIST, ifds::TransNum    , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_ACC_NBR,          IFASTBP_PROC::CHEQUE_LIST, ifds::BankAcctNum , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_CHEQUE_AGE,       IFASTBP_PROC::CHEQUE_LIST, ifds::ChequeAge   , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_DELIVERY_METHOD,  IFASTBP_PROC::CHEQUE_LIST, ifds::DeliveryCode , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_BANK_DATE,        IFASTBP_PROC::CHEQUE_LIST, ifds::BankRecDate , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_CANCELLED_DATE,   IFASTBP_PROC::CHEQUE_LIST, ifds::CanDate     , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );
   AddControl( CTRL_STATIC, IDC_TXT_CANCELLED_USER,   IFASTBP_PROC::CHEQUE_LIST, ifds::CancelUser  , CTRLFLAG_NOT_UPDATABLE, IDC_LV_CHEQUES );

   AddControl(CTRL_DATE, IDC_DTP_ISSUEDATE,           IFASTBP_PROC::CHEQUE_LIST, ifds::PrintDate, 0, IDC_LV_CHEQUES );
   AddControl(CTRL_DATE, IDC_DTP_STAGE_STAMPDATE,     IFASTBP_PROC::CHEQUE_LIST, ifds::StageStampDate, 0, IDC_LV_CHEQUES );
   AddControl(CTRL_DATE, IDC_DTP_REMITTANCEDATE,      IFASTBP_PROC::CHEQUE_LIST, ifds::RemittanceDate, 0, IDC_LV_CHEQUES );
   AddControl(CTRL_COMBO,IDC_CMB_CHQ_STAGE,           IFASTBP_PROC::CHEQUE_LIST, ifds::ChqStage, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CHEQUES);
   AddControl(CTRL_COMBO,IDC_CMB_CHQSTATUS,           IFASTBP_PROC::CHEQUE_LIST, ifds::ChqStatus, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CHEQUES);
   AddControl(CTRL_EDIT, IDC_EDT_CHQ_COMMENT,         IFASTBP_PROC::CHEQUE_LIST, ifds::ChqComments, CTRLFLAG_DEFAULT, IDC_LV_CHEQUES );
   AddControl(CTRL_COMBO,IDC_CMB_ASSIGNEDBY,          IFASTBP_PROC::CHEQUE_LIST, ifds::StageAssignBy, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CHEQUES);

    
   AddListControl( CLASSNAME, IDC_LV_FUND, LV_CHEQUEFUNDLIST, ifds::ChequesDetailHeadingSet, IFASTBP_PROC::CHEQUE_DETAILS_LIST, IDC_LV_CHEQUES, true, LISTFLAG_NOT_AUTO_ADD );

   AddListControl( CLASSNAME, IDC_LV_REMITTANCE_CHQ_INFO, LV_CHEQUEREMITTANCELIST, ifds::RemittanceChequeHeading, IFASTBP_PROC::CHEQUE_LIST/*REMITTANCE_CHEQUE*/, 0/*IDC_LV_CHEQUES*/, false, LISTFLAG_NOT_AUTO_ADD );

   UpdateData(FALSE);

   return(TRUE);   // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void ChequeDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::CHEQUE_LIST);
   addControlGroupIDForPermissionCheck(IDC_LV_CHEQUES);   

   m_btnTransactions.EnableWindow( FALSE );
   m_btnAdminDates.EnableWindow( FALSE );

   GetDlgItem (IDC_BTN_MORE)->EnableWindow (false);
   GetDlgItem (IDC_BTN_CHQHISTORICAL)->EnableWindow (false);

   GenericInterface* Parent = getParent();

   SetAccount( m_dstrAccountNum );

   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, CHQPROC::SHAREHOLDER_NUMBER, dstrShrNum );
   getParent()->getField( this, CHQPROC::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption( dstrShrNum, m_dstrAccountNum, dstrEntityName );

   if( Parent->getFirstListItemKey(this, IFASTBP_PROC::CHEQUE_LIST) != NULL_STRING )
   {
      m_btnTransactions.EnableWindow(TRUE);
      m_btnAdminDates.EnableWindow(TRUE);
      GetDlgItem (IDC_BTN_CHQHISTORICAL)->EnableWindow (true);

      Parent->getField( this, IFASTBP_PROC::CHEQUE_LIST, ifds::rxAcctNum, m_dstrAccountNum );
      m_dstrAccountNum.strip(); 
      SetAccount( m_dstrAccountNum );

      DString dstrShrNum, dstrEntityName;
      getParent()->getField( this, CHQPROC::SHAREHOLDER_NUMBER, dstrShrNum );
      getParent()->getField( this, CHQPROC::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
      SetShrAcctCaption( dstrShrNum, m_dstrAccountNum, dstrEntityName );

  	  GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::CHEQUE_LIST));

      LoadListControl( IDC_LV_CHEQUES, NULL );
   }

	GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::CHEQUE_LIST));

   ShowWindow(SW_SHOW);
}

//********************************************************************************************

void ChequeDlg::DoPreListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
	if( listControlID == IDC_LV_CHEQUES )
	{
		DString dstrAccountNum;

		getParent()->getField( this, IFASTBP_PROC::CHEQUE_LIST, ifds::rxAcctNum, dstrAccountNum);
		bool bEnable = dstrAccountNum == NULL_STRING || dstrAccountNum.empty () ? false : true;
		m_btnTransactions.EnableWindow(bEnable);

		GetDlgItem( IDC_EDT_DEST_ADDRESS )->SetWindowText( NULL_STRING );
	}
}

//********************************************************************************************
bool ChequeDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   TRACE_METHOD( CLASSNAME, FN_GETOVERRIDEITEMSTRING );
   if( lSubstituteId == ifds::ChequesDetailHeadingSet.getId() )
   {
      if( dstrColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::CHEQUE_DETAILS_LIST, ifds::FundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::CHEQUE_DETAILS_LIST, ifds::ClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, dstrOut );
         return(true);
      }
   }
   return(false);
}

//******************************************************************************

bool ChequeDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   GenericInterface * Parent = getParent();
   m_btnTransactions.EnableWindow(FALSE);
   m_btnAdminDates.EnableWindow(FALSE);
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (false);
   GetDlgItem (IDC_BTN_CHQHISTORICAL)->EnableWindow (false);

   if( Parent->getFirstListItemKey(this, IFASTBP_PROC::CHEQUE_LIST) != NULL_STRING )
   {
      Parent->getField( this, IFASTBP_PROC::CHEQUE_LIST, ifds::rxAcctNum, m_dstrAccountNum );
      m_btnTransactions.EnableWindow( TRUE );
      m_btnAdminDates.EnableWindow( TRUE );
      GetDlgItem (IDC_BTN_CHQHISTORICAL)->EnableWindow (true);

      m_dstrAccountNum.strip(); 
      SetAccount( m_dstrAccountNum );
      SetAccountCaption();
      GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::CHEQUE_LIST));
      LoadListControl( IDC_LV_CHEQUES, NULL );
   }
   else
   {
      getParameter( CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum );
      SetAccount( m_dstrAccountNum );
      SetAccountCaption();
      ClearControls( BF::AllContainerIds );
   }
   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, CHQPROC::SHAREHOLDER_NUMBER, dstrShrNum );
   getParent()->getField( this, CHQPROC::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption( dstrShrNum, m_dstrAccountNum, dstrEntityName );

   UpdateData(FALSE);

   return(true);
}

//******************************************************************************

void ChequeDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, FN_ONBTNADMINDATES );
   ShowAdminDates( IFASTBP_PROC::CHEQUE_LIST );
}

//******************************************************************************

void ChequeDlg::OnBtnTrans() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, FN_ONBTNTRANS );
   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_TRANSACTION_DETAILS );
   E_COMMANDRETURN eRtn;
   bool bModal = false;   // Default to modeless
   GenericInterface* Parent = getParent();
   try
   {
      GenericInterface* Parent = getParent();

      if( Parent->getFirstListItemKey(this, IFASTBP_PROC::CHEQUE_LIST) != NULL_STRING )
      {
         Parent->getField( this, IFASTBP_PROC::CHEQUE_LIST, ifds::rxAcctNum, m_dstrAccountNum );
         m_dstrAccountNum.strip(); 
         setParameter( CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum );
         setParameter( ALL_FUND_MODE, Y );
		 eRtn = invokeCommand( Parent, CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, false, NULL );
      };
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void ChequeDlg::OnBtnHistorical() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
	CWaitCursor wait;   
	IFastHistoricalInfo f;
	
	f( this, IFASTBP_PROC:: CHEQUE_LIST );
}

//******************************************************************************
void ChequeDlg::OnBtnMore() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
	CWaitCursor wait;

	static int cursel = GetList (IDC_LV_CHEQUES)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);
	const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::CHEQUE_LIST );

	if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
	{
		LoadListControl( IDC_LV_CHEQUES );
		
		if( *crtKey != NULL_STRING )
		{
			GetList( IDC_LV_CHEQUES )->SetSelection( crtKey );
		}
	}

	SetMessageStatusBar(NULL_STRING); 

	GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::CHEQUE_LIST));
	GetList (IDC_LV_CHEQUES)->SetSelection (cursel, true, true);
}
//******************************************************************************
void ChequeDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
	if( listControlID ==  IDC_LV_CHEQUES )
	{
		m_dstrSelectedChequeKey = strKey;
		LoadListControl( IDC_LV_REMITTANCE_CHQ_INFO, &strKey );
	}
}

//********************************************************************************************
bool ChequeDlg::ListViewControlFilter( long lSubstituteId, const DString * strKey)
{
   bool bRet = true;
   DString dstrRecordType; //dstrCheqNumChequeList, dstrCheqNumChequeDetailsList;
   DString dstrRefNumber, dstrRefNumberDetail, dstrPrintDate, dstrPrintDateDetail;
   if( lSubstituteId == ifds::RemittanceChequeHeading.getId() )
   {
	  bRet = false;
      if( strKey && *strKey == m_dstrSelectedChequeKey )
	  {
		  bRet = true;
	  }
   }
  
   return bRet;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ChequeDlg.cpp-arc  $
 * 
 *    Rev 1.32   08 Jan 2009 14:31:14   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.31   06 Jan 2009 16:23:14   popescu
 * Incident  1536725 - fixed incorrect updates to cheques
 * 
 *    Rev 1.30   Nov 12 2008 16:27:30   jankovii
 * IN 1482694 - cheque info.
 * 
 *    Rev 1.29   Nov 04 2008 13:39:56   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.28   Sep 12 2008 15:52:46   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.27   Sep 11 2008 16:33:46   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.26   Sep 11 2008 10:43:48   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.25   Sep 09 2008 16:24:38   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.24   Sep 15 2005 15:11:00   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.23   Jun 26 2003 14:29:16   HSUCHIN
 * PTS 10018497 - bug fix to cheque details list where dialog used the wrong index to find funds associated with cheques.
 * 
 *    Rev 1.22   Mar 21 2003 18:34:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.20   Sep 30 2002 11:01:36   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.19   Sep 25 2002 14:48:10   HERNANDO
 * Bug fix - Display details list; clean-up, minor fixes.
 * 
 *    Rev 1.18   Sep 16 2002 11:58:28   HERNANDO
 * Fix - Display Admin Date.
 * 
 *    Rev 1.17   Sep 13 2002 20:25:36   HERNANDO
 * PTS 10009611 - Added DoPreListItemChanged to clear Address Edit.
 * 
 *    Rev 1.16   Sep 10 2002 14:26:54   HERNANDO
 * Fix - Display controls (Address, and other static text).
 * 
 *    Rev 1.15   Sep 05 2002 15:54:10   HERNANDO
 * Clean up.
 * 
 *    Rev 1.14   22 May 2002 19:15:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   27 Mar 2002 20:01:00   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.12   Sep 06 2001 14:06:16   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.11   14 Jun 2001 11:58:24   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.10   May 16 2001 14:30:54   JANKAREN
 * Sync up SSB(1.8.1.0)
 * 
 *    Rev 1.9   03 May 2001 14:07:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Dec 13 2000 14:39:00   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 
 *    Rev 1.7   Sep 29 2000 13:29:18   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.6   Jun 19 2000 14:44:44   HUANGSHA
 * Displaying the Shrnum and EntityName in title bar
 * 
 *    Rev 1.5   Jun 09 2000 11:47:32   BUZILA
 * cheque fix
 * 
 *    Rev 1.4   Jun 06 2000 15:38:14   BUZILA
 * fix crash
 * 
 *    Rev 1.3   Mar 24 2000 15:41:22   ZHANGCEL
 * C2 changed added
 * 
 *    Rev 1.2   Mar 20 2000 14:19:52   HSUCHIN
 * change GetFundNumber to use the one defined in DSTCommonFunctions
 * 
 *    Rev 1.1   Mar 08 2000 18:20:12   HSUCHIN
 * C2 changes added, but still needs to be converted to use new infra
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.13   Feb 02 2000 14:36:06   DT24433
 * removed ok/cancel, use ShowAdminDates
 * 
 *    Rev 1.12   Oct 24 1999 11:15:18   POPESCUS
 * Erased the remarks button
 * 
 *    Rev 1.11   Sep 24 1999 13:02:06   VASILEAD
 * Strip the leading 0's for TransNum
 * 
 *    Rev 1.10   Sep 23 1999 16:28:14   VASILEAD
 * Modified to match C1 requirements
 * 
 *    Rev 1.9   Aug 26 1999 16:11:38   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.8   Aug 17 1999 15:41:20   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.7   Aug 08 1999 14:50:40   VASILEAD
 * changed to allow proper refresh
 * 
 *    Rev 1.6   Aug 05 1999 16:12:58   YINGZ
 * strip 0 for trans num
 * 
 *    Rev 1.5   Aug 05 1999 14:37:44   VASILEAD
 * Add multicurrency support
 * 
 *    Rev 1.4   Jul 20 1999 11:18:28   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 19 1999 16:34:14   POPESCUS
 * Fixed user security access to the remarks screen
 * 
 *    Rev 1.2   Jul 19 1999 12:53:14   POPESCUS
 * Added user access security checks
 * 
 *    Rev 1.1   Jul 08 1999 10:04:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
