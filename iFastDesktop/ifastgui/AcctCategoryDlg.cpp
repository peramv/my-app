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
// ^FILE   : AcctCategoryDlg.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : January 24, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : AcctCategoryDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  Account category dialog
//
//******************************************************************************

#include "stdafx.h"
#include <bfdata\bfdata.hpp>
#include "mfdstc.h"
#include "acctcategorydlg.hpp"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\acctcategoryprocessincludes.h>
#include <assert.h>
#include <bfproc\concretedialogcreator.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <uibase\dstlistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_CATEGORY;
static ConcreteDialogCreator< AcctCategoryDlg > dlgCreator( CMD_GUI_ACCT_CATEGORY );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AcctCategoryDlg" );
   const I_CHAR * const ID_LV_CATEGORY          = I_( "AccountCategoryList" );
   const I_CHAR * const ESTATE                  = I_( "52" );
   const I_CHAR * const DEATH_OF_NOTIFICATION   = I_( "51" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT;
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//fund on fund
namespace ACCOUNT_CATEGORY
{   
   extern CLASS_IMPORT I_CHAR * const FUND_ON_FUND; 
   extern CLASS_IMPORT I_CHAR * const SWIFT_PAYMENT_METHOD;
   extern CLASS_IMPORT I_CHAR * const HST_EXCEPTION;
   extern CLASS_IMPORT I_CHAR * const DEBIT_SWIFT_PAYMENT_METHOD;
   extern CLASS_IMPORT I_CHAR * const PRIVATE_WEALTH_OPT_OUT;
}

namespace ACCOUNT_CATEGORY_CONTROLS
{   
   //group of controls with fields part of a Swift Payment   
   const UINT SWIFT_PAYMENT_METHOD   = 1;   
   //group of controls with fields part of a Fund on Fund   
   const UINT FUND_ON_FUND           = 2;
}

   
//******************************************************************************

AcctCategoryDlg::AcctCategoryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AcctCategoryDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_bNewItem = false;

   //{{AFX_DATA_INIT(AcctCategoryDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

AcctCategoryDlg::~AcctCategoryDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AcctCategoryDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AcctCategoryDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdmin)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AcctCategoryDlg message handlers


//******************************************************************************

void AcctCategoryDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::ACCT_CATEGORY);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_CATEGORY);

   GetDlgItem(IDC_BTN_ADD)->EnableWindow(hasCreatePermission(UAF::ACCT_CATEGORY) || hasCreatePermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT));

   AddListControl( CLASSNAME, IDC_LV_CATEGORY, ID_LV_CATEGORY, ifds::AcctCategHeading, IFASTBP_PROC::CATEGORY_LIST );

   AddControl( CTRL_COMBO,IDC_CMB_CATEGORY,IFASTBP_PROC::CATEGORY_LIST, ifds::AcctCategory, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CATEGORY);

   //fund on fund
   AddControl( CTRL_COMBO,IDC_CMB_ACC_VALUE,    IFASTBP_PROC::CATEGORY_LIST, ifds::CatValue,    CTRLFLAG_INITCOMBO_BY_SUB_LIST, ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD );
   AddControl( CTRL_EDIT , IDC_EDT_CAT_VALUE,   IFASTBP_PROC::CATEGORY_LIST,  ifds::CatValue,   CTRLFLAG_DEFAULT, ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND );
   doRefresh(this, NULL_STRING);   
}

//******************************************************************************
SEVERITY AcctCategoryDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return(NO_CONDITION);
}

//******************************************************************************
void AcctCategoryDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
	CString strName;

   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum, false);
   dstrAccountNum.strip().stripLeading('0');


   // Get Entity Name
   if ( !dstrAccountNum.empty() ) 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), dstrAccountNum, dstrEntityName);

   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//******************************************************************************
bool AcctCategoryDlg::doRefresh( GenericInterface * rpGICaller, 
                                 const I_CHAR * szOriginalCommand )
{
   SetDlgCaption();
   LoadListControl( IDC_LV_CATEGORY );

   //In case all catagories are filtered out by ListViewControlFilter which results in an empty listcontrol.
   if (GetList(IDC_LV_CATEGORY)->GetItemCount() <= 0)
   {
       AddToListControl(IDC_LV_CATEGORY);
   }

   DString strCategoryType;
   getParent()->getField(this, IFASTBP_PROC::CATEGORY_LIST, ifds::AcctCategory, strCategoryType, false );

   if (strCategoryType == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD || 
       strCategoryType == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD ||
       strCategoryType == ACCOUNT_CATEGORY::HST_EXCEPTION)
   {
      LoadControls (ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD);
   }
   else if (strCategoryType == ACCOUNT_CATEGORY::FUND_ON_FUND)
   {
      LoadControls (ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND);
   }

   return(true);
}

//******************************************************************************
void AcctCategoryDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_CATEGORY);
   GetDlgItem(IDC_CMB_CATEGORY)->SetFocus();
}

//******************************************************************************
void AcctCategoryDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_CATEGORY);
}

//******************************************************************************
void AcctCategoryDlg::OnBtnAdmin() 
{
   ShowAdminDates(IFASTBP_PROC::CATEGORY_LIST);
}

//******************************************************************************
void AcctCategoryDlg::OnBtnReset() 
{
   ResetListItem( IDC_LV_CATEGORY );
}

//******************************************************************************
//fund on fund
void AcctCategoryDlg::ControlUpdated ( UINT controlID, const DString &strValue)
{   
   if ( IDC_CMB_CATEGORY == controlID )
   {
      DString strCatValue;
      if (ACCOUNT_CATEGORY::FUND_ON_FUND == strValue)
      {
         GetDlgItem ( IDC_EDT_CAT_VALUE )->ShowWindow ( true );
         GetDlgItem ( IDC_EDT_CAT_VALUE )->EnableWindow ( true ); 
         GetDlgItem ( IDC_CMB_ACC_VALUE )->ShowWindow ( false ); 
         ConnectControlsToData( ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND, true );
         LoadControls (ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND);
         ConnectControlsToData( ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD, false ); 
      }
      else if (ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD == strValue ||
               ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD == strValue ||
               ACCOUNT_CATEGORY::HST_EXCEPTION == strValue)
      {
         GetDlgItem ( IDC_EDT_CAT_VALUE )->ShowWindow ( false );
         GetDlgItem ( IDC_CMB_ACC_VALUE )->ShowWindow ( true );
         ConnectControlsToData( ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND, false );
         ConnectControlsToData( ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD, true); 
         LoadControls (ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD);
      }
      else // others category
      {
         GetDlgItem ( IDC_EDT_CAT_VALUE )->ShowWindow ( true );
         GetDlgItem ( IDC_CMB_ACC_VALUE )->ShowWindow ( false );
         GetDlgItem ( IDC_EDT_CAT_VALUE )->EnableWindow ( false );
      }
   }
}

//******************************************************************************
//fund on fund
void AcctCategoryDlg::DoListItemChanged( UINT listControlID,
                                         const DString &strKey, 
                                         bool isNewItem,
                                         bool bIsDummyItem)
{
   DString strAcctCategory;
   getParent()->getField (this, IFASTBP_PROC::CATEGORY_LIST, ifds::AcctCategory, strAcctCategory, false);

   if (!isNewItem)
       SetUserAccesFunctionCode(strAcctCategory == ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT ? UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT:UAF::ACCT_CATEGORY);
   else // Either one has an add permission is enough, use it as a temporary.
       SetUserAccesFunctionCode(hasCreatePermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT) ? UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT:UAF::ACCT_CATEGORY);

   if (strAcctCategory == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD || 
       strAcctCategory == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD || 
       strAcctCategory == ACCOUNT_CATEGORY::HST_EXCEPTION)
   {
      ConnectControlsToData (ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD, true);
      LoadControls (ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD);
      ConnectControlsToData (ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND, false);
   }
   else if (strAcctCategory == ACCOUNT_CATEGORY::FUND_ON_FUND) //do the reverse
   {
      ConnectControlsToData (ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND, true);
      LoadControls (ACCOUNT_CATEGORY_CONTROLS::FUND_ON_FUND);
      ConnectControlsToData (ACCOUNT_CATEGORY_CONTROLS::SWIFT_PAYMENT_METHOD, false);
   }
}

//******************************************************************************
bool AcctCategoryDlg::doDisablePermCheckButton(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_( "doDisablePermCheckButtons" ));

   if (nID == IDC_BTN_DELETE)
   {
      DString dstrAcctCategory;

      getParent()->getField (this, ifds::AcctCategory, dstrAcctCategory, false);

      if (m_bNewItem)
         return false;

      if (dstrAcctCategory == DEATH_OF_NOTIFICATION || 
          dstrAcctCategory == ESTATE)
         return true;
   }

   return false;
}

//******************************************************************************
void AcctCategoryDlg::DoPreListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
	if (listControlID == IDC_LV_CATEGORY )
	{
		m_bNewItem = bIsNewItem;
	}
}

//******************************************************************************
void AcctCategoryDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   DString dstrAccountNum;

   getParent()->getField( this, 
                          IFASTBP_PROC::MFACCOUNT, 
                          ifds::AccountNum, 
                          dstrAccountNum ); 

   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::CATEGORY_LIST, I_( "SINGLE" ) );
}


//******************************************************************************
bool AcctCategoryDlg::ListViewControlFilter(long lSubstituteId, const DString *strKey)
{   
   bool bShow = true;

   if (lSubstituteId == ifds::AcctCategHeading.getId())
   {
      DString dstrAcctCategory;

      getParent()->getField (this, IFASTBP_PROC::CATEGORY_LIST, ifds::AcctCategory, dstrAcctCategory, false);
      dstrAcctCategory.stripAll().upperCase();

      if (!hasReadPermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT) && 
          dstrAcctCategory == ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT)
      {
          bShow = false;
      }
      
      if (!hasReadPermission(UAF::ACCT_CATEGORY) &&
          dstrAcctCategory != ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT)
      {
          bShow = false;
      }
   }
   return bShow; 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctCategoryDlg.cpp-arc  $
// 
//    Rev 1.10   Feb 01 2011 11:12:22   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.9   Dec 01 2010 04:46:40   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.8   Jul 20 2010 05:27:38   dchatcha
// IN# 2187879 - HST - New Exception Account Category.
// 
//    Rev 1.7   26 Jun 2009 13:52:18   popescu
// Incident 1741768 - Account Category not auto-populating
// 
//    Rev 1.6   Jan 12 2009 11:10:34   jankovii
// IN 1549377 Estate and Death of Notification acct category can only be added by the system
// 
//    Rev 1.5   Oct 28 2008 05:00:22   phiwponp
// PET22486FN45 - Fund on Funds Account Report.
// 
//    Rev 1.4   Aug 09 2007 14:15:12   jankovii
// PET 2388 FN01 - Swift Payment Method Id.
// 
//    Rev 1.3   Sep 15 2005 15:09:56   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Mar 21 2003 18:30:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Jan 25 2003 17:04:50   KOVACSRO
// set focus on Account Category after add.
// 
//    Rev 1.0   Jan 24 2003 13:09:26   KOVACSRO
// Initial revision.

 */