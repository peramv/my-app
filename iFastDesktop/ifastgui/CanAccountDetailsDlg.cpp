// ANAccountDetailsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "canaccountdetailsdlg.h"
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastbp\accdetailsprocessincludes.h>
#include <assert.h>

// Note: ConcreteDialogCreator is instantiated in AccountDetailsDlg.cpp

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME = I_( "BaseAccountDetailsDlg" );
   const I_CHAR * const LV_ACCOUNTDETAILS = I_( "AccountDetails" );
   const I_CHAR * const LV_ENTITYDETAILS = I_( "EntityDetails" );
   const I_CHAR *LV_ENTITYIDS = I_( "EntityIDs" );              //Aug 3, 1999
   const I_CHAR * const LV_FUNDSDETAILS = I_( "FundDetails" );
   const I_CHAR * const LV_PENDINGDETAILS = I_( "PendingDetails" );
   const I_CHAR * const LV_HISTORYDETAILS = I_( "HistoryDetails" );
   const I_CHAR * const EMPTY_STRING = I_( "" );
   const I_CHAR * const SPACE_STRING = I_( " " );
   const I_CHAR * const Y_STRING = I_( "Y" );
   const I_CHAR * const FIRST_CHAR_K = I_( "K" );
   const I_CHAR * const FIRST_CHAR_ONE = I_( "1" );
   const I_CHAR * const FIRST_CHAR_ZERO = I_( "0" );
   const I_CHAR * const SETTLED_YES = I_( "Yes" );
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUMBER_FIELD = I_( "ShareholderNum" );
   const I_CHAR * const TRANS_ID_FIELD = I_( "TransId" );
   const I_CHAR * const KEY = I_( "Key" );
   const I_CHAR * const ALL_FUND_MODE = I_( "AllFundMode" );
   const I_CHAR * const IN_ACCT_NUM_FIELD = I_( "InAcctNum" );
   const I_CHAR * const FUND_CODE_FIELD = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE_FIELD = I_( "ClassCode" );
   const I_CHAR * const NUM_ENTRY_FIELD = I_( "NumEntry" );
   const I_CHAR * const PENDING = I_( "Pending" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const TRADE_DATE_FIELD = I_( "TradeDate" );
   const I_CHAR * const TRANS_TYPE_FIELD = I_( "TransType" );
   const I_CHAR * const TRANS_NUMBER_FIELD = I_( "TransNum" );
   const I_CHAR * const MODUSER = I_( "ModUser" );
   const I_CHAR * const MODDATE = I_( "ModDate" );
   const I_CHAR * const PROCESSUSER = I_( "Username" );
   const I_CHAR * const PROCESSDATE = I_( "ProcessDate" );
   const I_CHAR * const DEFAULT_Y_N = I_( "DefaultYN" );
   const I_CHAR * const ENTITY_ID_PARAM    =   I_("EntityID");
   const I_CHAR * const STRING_D    =   I_("D");
   const I_CHAR * const STRING_U    =   I_("U");
   const I_CHAR * const ADDRESS_CODE    =   I_("AddressCode");
   const I_CHAR * const TO = I_("TO");
   const I_CHAR * const EO = I_("EO");
   const I_CHAR * const TR = I_("TR");
   const I_CHAR * const REGISTRATION_ADDRESS = I_("01");
   const I_CHAR * const ACTIVE = I_("1");

}


/////////////////////////////////////////////////////////////////////////////
// CANAccountDetailsDlg dialog


CANAccountDetailsDlg::CANAccountDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseAccountDetailsDlg( pParent, pGIC, pGIParent, rCommand )
{
   //{{AFX_DATA_INIT(CANAccountDetailsDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CANAccountDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseAccountDetailsDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CANAccountDetailsDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CANAccountDetailsDlg, BaseAccountDetailsDlg)
//{{AFX_MSG_MAP(CANAccountDetailsDlg)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANAccountDetailsDlg message handlers
//bool CANAccountDetailsDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
//{  
//	return true;
//}

void CANAccountDetailsDlg::ItemchangedLvAccounts(int index)
{
   if( index != -1 )
   {
      DString* key = (DString*)m_lvAccounts.GetItemData( index );

      getParent()->setCurrentListItem( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, *key );

      int state = m_ckbAllFunds.GetCheck();
      if( state == 1 )
         //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "All" ) );
         getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("Y"),false);
      else
      {
         //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "FundMode" ) ); // The key doesn't matter, this is used to set the right transaction list ptr
         getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("N"),false);
      }
      displayTitle();
      fillAccountInfo();
// ying	      fillAddressSelectList();
      //m_lbSelectAddr.SetCurSel( 0 );
// ying        m_cmbAddrSel.SetCurSel( 0 );
      fillShrAddressList();
      m_lvKanjiAddr.SetSelection( 0 );
      //m_lvKanaAddr.SetSelection( 0 );
      fillEntitiesList();
      if( m_lvEntities.GetItemCount() )
         m_lvEntities.SetSelection( 0 );
      //m_lvEntitiesIds.SetSelection( 0 );
      loadRRIFString();
      CButton *pRadioButton1 = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
      CButton *pRadioButton2 = static_cast < CButton* > ( GetDlgItem( IDC_RB_PENDING_TRADES ) );
      int iCheck = pRadioButton2->GetCheck( );
      //int nrListItems = getParent()->getNumberOfItemsInList( this, ACCDETLIT::PENDING_TRADES_LIST);
      DString strPendingTrades;
      getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PendingTrade, strPendingTrades, false);
      if( iCheck == 1 && strPendingTrades.strip() != I_("Y") )
      {
//	        	m_lvTransactions.SaveSettings( CLASSNAME, LV_PENDINGDETAILS );
         pRadioButton2->SetCheck( 0 );
         pRadioButton1->SetCheck( 1 );
         pRadioButton2->EnableWindow( false );
         m_lvTransactions.DeleteAllColumns();
//	        	m_lvTransactions.LoadSettings( CLASSNAME, LV_HISTORYDETAILS );
         SetTransHeading();
         TranPendingState = 1;
      }
      else if( strPendingTrades != I_("Y") )
         pRadioButton2->EnableWindow( false );
      else
         pRadioButton2->EnableWindow( true );

      fillFundList( );
      if( m_lvFunds.GetItemCount() )
         m_lvFunds.SetSelection( 0 );//this will also fill transactions list, too

      fillTransactionsList( );
      fillPendingTradesList( );
      fillCautionsList();
      fillOptionsList();
      fillAttributesList();
      setGlobalInformation();
   }
   else
   {
      //throw exception : no selection
   }
}

void CANAccountDetailsDlg::fillShrAddressList()
{

   DString str, temp, strKanjiCode;
   CString code;
   int i = 0;


   m_lvKanjiAddr.DeleteAllItems();

   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) == EMPTY_STRING )
      return;

   do
   {
      //   if( i != 0 )
      //      assert( 0 );

      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, str, false );
      str.strip();
      if( str != REGISTRATION_ADDRESS )//want to display the registration address
         continue;

      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrStatus, str, false );
      str.strip();
      if( str != ACTIVE )//want to display an active status address only
         continue;

      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::EffectiveDate, str, false );
      str.strip();
      DString strStopDate, curDate;
      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::StopDate, strStopDate, false );
      strStopDate.strip();
	  DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	  dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate,curDate,BF::HOST);
      curDate.strip();
      if( !DSTCommonFunctions::IsDateBetween(str, strStopDate,curDate) )
	  {
         continue;//want to display the current active address (they can have multiple active addresses
	  }

      getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::Name1, str );
      str.strip();
      //str.stripLeading( '0' );
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
      break;//only show one address
      //getParent()->getField( this, ACCDETLIT::ADDRESS_LIST, DBR::CountryCode, str );
      //str.strip();
      //getParent()->getField( this, ACCDETLIT::ADDRESS_LIST, DBR::CountryName, str );//
      //str.strip();//
      /*str += SPACE_STRING;
      str += SPACE_STRING;
      str += temp;*/
      /*if( str != EMPTY_STRING )
      {
         m_lvKanjiAddr.InsertItem( i, str.c_str() );
         i++;
      }*/
//      i = 0;
   }
   while( getParent()->getNextListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) != EMPTY_STRING );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CanAccountDetailsDlg.cpp-arc  $
 * 
 *    Rev 1.13   18 Dec 2008 09:43:16   kovacsro
 * IN#1281980 - display the current active address (instead of the most recent)
 * 
 *    Rev 1.12   Mar 21 2003 18:33:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Jun 26 2002 18:42:12   HERNANDO
 * Added call to fillAttributesList in ItemchangedLvAccounts.
 * 
 *    Rev 1.9   22 May 2002 19:15:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   Apr 26 2002 10:17:22   YINGBAOL
 * fix mutiaccount RRIF refresh issue--PTS 10007965
 * 
 *    Rev 1.7   27 Mar 2002 20:00:54   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   15 Feb 2002 14:09:36   KOVACSRO
 * Have to call fillTransactionsList( ) when an account is selected
 * 
 *    Rev 1.5   13 Feb 2002 14:31:58   KOVACSRO
 * sync-up : Showing the active registration address rather than the first one in the list.
 * 
 *
 */
