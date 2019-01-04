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
// ^FILE   : ProtectedFundSetupDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ----------------------------------------------------------
//
// ^CLASS    : ProtectedFundSetupDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfproc\AbstractProcess.hpp>
#include "ProtectedFundSetupDlg.hpp"
#include <uibase\DSTButton.h>
#include <uibase\DSTComboBox.h>
#include <uibase\DSTEdit.h>
#include <ifastbp\ProtectedFundProcessincludes.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PROTECTED_FUND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ProtectedFundSetupDlg > dlgCreator( CMD_GUI_PROTECTED_FUND );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ProtectedFundSetupDlg" );
   const I_CHAR *LV_PROTECTED_FUNDS_LIST = I_("ProtectedFundsList"); 
   const I_CHAR * const FUND_CODE = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE = I_( "ClassCode" );
   const I_CHAR * const FUND_NUMBER = I_( "FundNumber" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PROTECTED_FUND_SETUP;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
ProtectedFundSetupDlg::ProtectedFundSetupDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ProtectedFundSetupDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ProtectedFundSetupDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ProtectedFundSetupDlg::DoDataExchange( CDataExchange* pDX )

{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ProtectedFundSetupDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY ProtectedFundSetupDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( ProtectedFundSetupDlg, BaseMainDlg )
//{{AFX_MSG_MAP(ProtectedFundSetupDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDelete )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ProtectedFundSetupDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void ProtectedFundSetupDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	SetUserAccesFunctionCode(UAF::PROTECTED_FUND_SETUP);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_PROTECTED_FUNDS_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_PROTECTED_FUNDS_LIST);

   AddListControl( CLASSNAME, IDC_LV_PROTECTED_FUNDS_LIST, LV_PROTECTED_FUNDS_LIST, 
      ifds::ProtectedFundsListHeadingSet, IFASTBP_PROC::PROTECTED_FUND_LIST );
   AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::FundCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_CLASS_CODE, IFASTBP_PROC::PROTECTED_FUND_LIST,
      ifds::ClassCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::FundNumber, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::PROTECTED_FUND_LIST,
      ifds::EffectiveDate, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::PROTECTED_FUND_LIST,
      ifds::StopDate, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_INSURANCE_CODE, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::InsurCode, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_INSURANCE_COST, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::InsurCost, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_CONTRACT_GAP, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::ContractGapType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_RESETS_ALLOWED, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::ResetsAllowed, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_MATURITY_YEARS, IFASTBP_PROC::PROTECTED_FUND_LIST, 
      ifds::MaturityYears, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PROTECTED_FUNDS_LIST);

   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MATURITY_YEARS))->SetAllowedChars(I_("0123456789"));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_INSURANCE_COST))->SetAllowedChars(I_("0123456789."));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_RESETS_ALLOWED))->SetAllowedChars(I_("0123456789"));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MATURITY_YEARS))->SetMaxCharNum(6);
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_RESETS_ALLOWED))->SetMaxCharNum(6);
   doRefresh( this, NULL_STRING );
}


//******************************************************************************
bool ProtectedFundSetupDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   LoadListControl(IDC_LV_PROTECTED_FUNDS_LIST); //this will load the controls
   return true;
}

//*************************************************************************
void ProtectedFundSetupDlg::ControlUpdated( UINT controlID, 
   const DString &strValue )
{
}

//******************************************************************************
void ProtectedFundSetupDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_PROTECTED_FUNDS_LIST);
}

//******************************************************************************
void ProtectedFundSetupDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl( IDC_LV_PROTECTED_FUNDS_LIST );
}

//******************************************************************************
void ProtectedFundSetupDlg::OnBtnDelete()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;

   DeleteFromListControl( IDC_LV_PROTECTED_FUNDS_LIST );
}

//******************************************************************
void ProtectedFundSetupDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::PROTECTED_FUND_LIST);
}

//******************************************************************
BOOL ProtectedFundSetupDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && 
      (int)( pMsg->wParam ) == VK_F4 && 
      !IsSelectedCtrlUpdateable() )
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      m_pWndItemInFocus = GetFocus();
      if( m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_CLASS_CODE ) ||
          m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_CODE ) ||
          m_pWndItemInFocus == GetDlgItem( IDC_EDT_FUND_NUMBER )) 
      {
         PostMessage(UM_OPENFUNDLISTDLG);
      }
   }
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}


//******************************************************************
void ProtectedFundSetupDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(
      listControlID == IDC_LV_PROTECTED_FUNDS_LIST && !bIsNewItem && !bIsDummyItem);
}

//******************************************************************
LRESULT ProtectedFundSetupDlg::OpenFundListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      //clear all params first
      setParameter(CLASS_CODE, NULL_STRING);
      setParameter(FUND_CODE, NULL_STRING);
      setParameter(FUND_NUMBER, NULL_STRING);
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CLASS_CODE)) 
      {
         CString cstrClassCode;

         static_cast<CEdit*>(GetDlgItem(IDC_EDT_FUND_CLASS_CODE))->GetWindowText(cstrClassCode);
         setParameter(CLASS_CODE, (LPCTSTR)cstrClassCode);
      } else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CODE))
      {
         CString cstrFundCode;

         static_cast<CEdit*>(GetDlgItem(IDC_EDT_FUND_CODE))->GetWindowText(cstrFundCode);
         setParameter(FUND_CODE, (LPCTSTR)cstrFundCode);
      } else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUMBER))
      {
         CString cstrFundNumber;

         static_cast<CEdit*>(GetDlgItem(IDC_EDT_FUND_NUMBER))->GetWindowText(cstrFundNumber);
         setParameter(FUND_NUMBER, (LPCTSTR)cstrFundNumber);
      }
      //invoke the fund class dialog and process
      SetMessageStatusBar(TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;

               if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CLASS_CODE) ||
                   m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CODE))
               {
                  getParameter( CLASS_CODE, dstrClassCode);
                  getParent()->setField( this, IFASTBP_PROC::PROTECTED_FUND_LIST, 
                     ifds::ClassCode, dstrClassCode);
                  getParameter( FUND_CODE, dstrFundCode );
                  getParent()->setField( this, IFASTBP_PROC::PROTECTED_FUND_LIST, 
                     ifds::FundCode, dstrFundCode);
               }
               else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUMBER))
               {
                  getParameter(FUND_NUMBER, dstrFundNumber);
                  getParent()->setField( this, IFASTBP_PROC::PROTECTED_FUND_LIST, 
                     ifds::FundNumber, dstrFundNumber);
               }
               LoadControl(IDC_EDT_FUND_CLASS_CODE);
               LoadControl(IDC_EDT_FUND_CODE);
               LoadControl(IDC_EDT_FUND_NUMBER);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            SetMessageStatusBar(NULL_STRING);
            break;
      }
      SetMessageStatusBar(NULL_STRING);
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(0);
}

void ProtectedFundSetupDlg::OnBtnAdmDates()
{
   ShowAdminDates(IFASTBP_PROC::PROTECTED_FUND_LIST);
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ProtectedFundSetupDlg.cpp-arc  $
// 
//    Rev 1.10   Sep 15 2005 15:14:42   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.9   Aug 22 2005 10:53:46   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.8   May 26 2003 10:36:12   popescu
// by loading the list control the other controls will follow suit
// 
//    Rev 1.7   Mar 21 2003 18:39:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 05 2003 11:29:54   PURDYECH
// Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
// 
//    Rev 1.5   Feb 14 2003 11:18:36   popescu
// grayed out the fund elements if the protected fund record exists
// 
//    Rev 1.4   Feb 03 2003 11:57:04   popescu
// Displaying the history button only when the item is not new, and adding some txt message for the status bar
// 
//    Rev 1.3   Jan 28 2003 13:16:52   popescu
// Historical Info feature implementation
// 
//    Rev 1.2   Jan 20 2003 15:44:00   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
//    Rev 1.1   Jan 14 2003 11:00:10   popescu
// Added F4 functionality
// 
//    Rev 1.0   Jan 13 2003 12:49:12   popescu
// Initial Revision
 * 
*/

