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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccountDetailsDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AccountDetailsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "accountdetailsdlg.h"
#include <ifastbp\accdetailsprocessincludes.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "canaccountdetailsdlg.h"
#include <ifastcbo\dstcommonfunction.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;
#include <bfproc\concretedialogcreator.hpp>

struct accountDialogCreator
{
   GenericInterface* operator()( GenericInterfaceContainer* pGIC, 
                                 GenericInterface* pGIParent,
                                 const Command& rCommand) const {
      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         return( new CANAccountDetailsDlg( NULL, pGIC, pGIParent, rCommand ) );
      else if( strMarket == MARKET_IDS::JAPAN )
         return( new AccountDetailsDlg( NULL, pGIC, pGIParent, rCommand ) );
      else
         return( NULL );
   }
};
static ConcreteDialogCreator< AccountDetailsDlg, accountDialogCreator > dlgCreator( CMD_GUI_ACCOUNT_DETAILS );


#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );
   const I_CHAR * const CLASSNAME = I_( "AccountDetailsDlg" );
   const I_CHAR * const EMPTY_STRING = I_( "" );
   const I_CHAR * const FIRST_CHAR_K = I_( "K" );
   const I_CHAR * const LV_HISTORYDETAILS = I_( "HistoryDetails" );
   const I_CHAR * const LV_PENDINGDETAILS = I_( "PendingDetails" );
   const I_CHAR * const SPACE_STRING = I_( " " );
}

namespace CND
{
}
//******************************************************************************

AccountDetailsDlg::AccountDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseAccountDetailsDlg( pParent, pGIC, pGIParent, rCommand )
//CP20030319: BaseAccountDetailsDlg(pParent)
{
   //{{AFX_DATA_INIT(AccountDetailsDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************

void AccountDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseAccountDetailsDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AccountDetailsDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AccountDetailsDlg, BaseAccountDetailsDlg)
//{{AFX_MSG_MAP(AccountDetailsDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// AccountDetailsDlg message handlers

//******************************************************************************

BOOL AccountDetailsDlg::OnInitDialog() 
{
   BaseAccountDetailsDlg::OnInitDialog();

   LVCOLUMN lvColumn;
   lvColumn.mask = LVCF_FMT;
   lvColumn.fmt = LVCFMT_RIGHT;
   CString lvColumns;

   m_lvKanjiAddr.InsertColumn( 0, ( LPCTSTR ) lvColumns , LVCFMT_LEFT, 304 );
   m_lvKanaAddr.InsertColumn( 0, ( LPCTSTR ) lvColumns , LVCFMT_LEFT, 304 );

   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_ENTITIES ) );
   pRadioButton->SetCheck( 1 );

   CComboBox *pAddrComboBox = static_cast < CComboBox* > ( GetDlgItem( IDC_CMB_ADDR_SEL ) );
   pAddrComboBox->ShowWindow( SW_HIDE );

   //fillAddressSelectList();called by ItemchangedLvAccounts()
   pAddrComboBox->SetCurSel( 0 );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AccountDetailsDlg::fillAddressSelectList()
{
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_SHAREHOLDER_ADDRESSES ) );
   if( !pRadioButton->GetCheck() )
      return;

   CComboBox *pAddrComboBox = static_cast < CComboBox* > ( GetDlgItem( IDC_CMB_ADDR_SEL ) );
   DString str, rez, strKanjiCode, strKanaCode;

   pAddrComboBox->ResetContent();
   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) == EMPTY_STRING )
      return;

   do
   {
      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, str, false );
      str.strip();
      str.upperCase();

      CString and;
      and.LoadString( TXT_AND );

      if( str.compare( 0, 1, FIRST_CHAR_K ) == 0 )
      {
         strKanjiCode.assign( str, 1, 2 );
         rez = strKanjiCode + SPACE_STRING + ( LPCTSTR ) and + SPACE_STRING + str;
      }
      else
      {
         strKanaCode.assign( str );
         strKanaCode.insert( 0, FIRST_CHAR_K );
         rez = str + SPACE_STRING + ( LPCTSTR ) and + SPACE_STRING + strKanaCode;
      }

      if( pAddrComboBox->FindStringExact( -1, rez.c_str() ) != CB_ERR )
         continue;
      pAddrComboBox->AddString( rez.c_str() );
   }
   while( getParent()->getNextListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) != EMPTY_STRING );

}

//******************************************************************************

void AccountDetailsDlg::SetfocusLvAccounts(NMHDR *pNMHDR, LRESULT *pResult)
{
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   BaseAccountDetailsDlg::SetfocusLvAccounts(pNMHDR, pResult);
}

//******************************************************************************

void AccountDetailsDlg::ItemchangedLvAccounts(int index)
{
   // TODO: Add your control notification handler code here

   if( index != -1 )
   {
      DString* key = (DString*)m_lvAccounts.GetItemData( index );

      getParent()->setCurrentListItem( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, *key );
      int state = m_ckbAllFunds.GetCheck();
      if( state == 1 )
      {
         //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "All" ) );
         getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("Y"),false);
      }
      else
      {
         //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "FundMode" ) ); // The key doesn't matter, this is used to set the right transaction list ptr
         getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("N"),false);
      }
      displayTitle();
      fillAccountInfo();
      fillAddressSelectList();
      m_cmbAddrSel.SetCurSel( 0 );
      fillShrAddressList();
      fillEntitiesList();
      if( m_lvEntities.GetItemCount() )
         m_lvEntities.SetSelection( 0 );

      CButton *pRadioButton1 = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
      CButton *pRadioButton2 = static_cast < CButton* > ( GetDlgItem( IDC_RB_PENDING_TRADES ) );
      int iCheck = pRadioButton2->GetCheck( );
      //int nrListItems = getParent()->getNumberOfItemsInList( this, ACCDETLIT::PENDING_TRADES_LIST );
      DString strPendingTrades;
      getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PendingTrade, strPendingTrades, false);
      //if ( iCheck == 1 && nrListItems == 0 )
      if( iCheck == 1 && strPendingTrades.strip() != I_("Y") )
      {
         m_lvTransactions.SaveSettings( CLASSNAME, LV_PENDINGDETAILS );
         m_ckbAllFunds.EnableWindow( true );
         pRadioButton2->SetCheck( 0 );
         pRadioButton1->SetCheck( 1 );
         pRadioButton2->EnableWindow( false );
         m_lvTransactions.DeleteAllColumns();
         m_lvTransactions.LoadSettings( CLASSNAME, LV_HISTORYDETAILS );
         SetTransHeading();
         TranPendingState = 1;
      } //else if ( nrListItems == 0 )
      else if( strPendingTrades != I_("Y") )
         pRadioButton2->EnableWindow( false );
      else
         pRadioButton2->EnableWindow( true );

      fillFundList( );
      if( m_lvFunds.GetItemCount() )
         m_lvFunds.SetSelection( 0 );

      fillTransactionsList( );
      fillPendingTradesList( );
      fillCautionsList();
      fillOptionsList();
      setGlobalInformation();
      //see if this account can be a model
      DString accountNum, entityId;

      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum );
      getParent()->getField( this, BF::NullContainerId, ACCDETLIT::INITIAL_ENTITY_ID, entityId );

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *pMFAccount;
      if( dstcWorkSession->getMFAccount( getDataGroupId(), accountNum, pMFAccount ) <= WARNING )
      {
         GetDlgItem( IDC_BTN_NEW_ACCOUNT )->EnableWindow( pMFAccount->isAccountModel( entityId, getDataGroupId() ) );
      }
   }
   else
   {
      //throw exception : no selection
   }

}

//******************************************************************************

void AccountDetailsDlg::SetfocusLvEntities(NMHDR *pNMHDR, LRESULT *pResult)
{
   BaseAccountDetailsDlg::SetfocusLvEntities(pNMHDR, pResult);
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLvFunds(NMHDR *pNMHDR, LRESULT *pResult)
{
   BaseAccountDetailsDlg::SetfocusLvFunds(pNMHDR, pResult);
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLbAttrib()
{
   BaseAccountDetailsDlg::SetfocusLbAttrib();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLbCautions()
{
   BaseAccountDetailsDlg::SetfocusLbCautions();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLbOptions()
{
   BaseAccountDetailsDlg::SetfocusLbOptions();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLvHistoryTrades(NMHDR *pNMHDR, LRESULT *pResult)
{
   BaseAccountDetailsDlg::SetfocusLvHistoryTrades(pNMHDR, pResult);
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::SetfocusLvEntitiesIds(NMHDR *pNMHDR, LRESULT *pResult)
{
   BaseAccountDetailsDlg::SetfocusLvEntitiesIds(pNMHDR, pResult);
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::RbTransHistory()
{
   BaseAccountDetailsDlg::RbTransHistory();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::RbPendingTrades()
{
   BaseAccountDetailsDlg::RbPendingTrades();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************

void AccountDetailsDlg::fillShrAddressList()
{
   DString str, temp, strKanjiCode, strKanaCode;
   CString code;
   int i = 0, j = 0;

   int index = m_cmbAddrSel.GetCurSel();

   if( index == CB_ERR )
      return;

   m_cmbAddrSel.GetLBText( index, code );
   strKanjiCode.assign( ( LPCTSTR ) code, 0, 2 );
   strKanaCode.assign( strKanjiCode );
   strKanaCode.insert( 0, FIRST_CHAR_K );

   m_lvKanjiAddr.DeleteAllItems();
   m_lvKanaAddr.DeleteAllItems();

   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) == EMPTY_STRING )
      return;

   do
   {
      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, str, false );
      str.strip();
      int rez1 = str.compare( strKanjiCode );
      int rez2 = str.compare( strKanaCode );

      if( rez1 == 0 )
      {
         if( i != 0 )
            assert( 0 );
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::Name1, str );
         str.strip();

         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::Name2, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine1, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine2, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine3, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine4, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine5, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::PostalCode, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::CountryName, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanjiAddr.InsertItem( i, str.c_str() );
            i++;
         }
         if( j != 0 )
            assert( 0 );
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::kAddrLine1, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanaAddr.InsertItem( j, str.c_str() );
            j++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::kAddrLine2, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanaAddr.InsertItem( j, str.c_str() );
            j++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::kAddrLine3, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanaAddr.InsertItem( j, str.c_str() );
            j++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::kAddrLine4, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanaAddr.InsertItem( j, str.c_str() );
            j++;
         }
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::kAddrLine5, str );
         str.strip();
         if( str != EMPTY_STRING )
         {
            m_lvKanaAddr.InsertItem( j, str.c_str() );
            j++;
         }
      }
   }
   while( getParent()->getNextListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) != EMPTY_STRING );
}

//******************************************************************************

void AccountDetailsDlg::BtnAdminDates()
{
   BaseAccountDetailsDlg::BtnAdminDates();
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountDetailsDlg.cpp-arc  $
 * 
 *    Rev 1.10   Mar 21 2003 18:30:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   22 May 2002 19:15:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 20:00:50   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   15 Feb 2002 14:08:46   KOVACSRO
 * Need to cal fillTransactionsList when an account was selected.
 * 
 *    Rev 1.5   04 Feb 2002 15:21:50   KOVACSRO
 * ItemChangedLVAccounts takes a different param.
 * 
 *    Rev 1.4   03 Dec 2001 13:03:04   KOVACSRO
 * Lazy init for shareholder address and some other tuning.
 * 
 *    Rev 1.3   10 Aug 2001 14:16:44   HSUCHIN
 * Code clean up
 * 
 *    Rev 1.2   10 Aug 2001 13:56:48   HSUCHIN
 * beautify source
*/