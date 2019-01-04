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
// ^FILE   : IdentAccDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03 Feb 2000
//
// ----------------------------------------------------------
//
// ^CLASS    : IdentAccDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif
#ifndef IdentAccDlg_H
   #include "IdentAccDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif
#ifndef DSTBUTTON_H
   #include <uibase\DSTButton.h>
#endif
#ifndef DSTLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif
#ifndef FILLSEARCHCRITERIAPROCESSINCLUDES_H
   #include <ifastbp\FillSearchCriteriaProcessIncludes.h>
#endif
#ifndef GENERICINTERFACECONTAINER_HPP
   #include <bfproc\GenericInterfaceContainer.hpp>
#endif
#ifndef IDENTIFYACCOUNTSPROCESSINCLUDES_HPP
   #include <ifastbp\IdentAccProcessIncludes.h>
#endif

#ifndef BFUSERSESSION_HPP
   #include <bfcbo\BFUserSession.hpp>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FILL_SEARCH_CRITERIA;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_IDENT_ACC;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< IdentAccDlg > dlgCreator( CMD_GUI_IDENT_ACC );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "IdentAccDlg" );

   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const MFDSTC = I_( "MFDSTC" );
   const I_CHAR * const LFCR = I_( "\r\n" );
   const I_CHAR * const LV_ENTITY_IDS = I_( "List View Entity Ids" );
   const I_CHAR * const LV_ENTITIES = I_( "List View Entities" );
   const I_CHAR * const LV_ACCOUNTS = I_( "List View Accounts" );
   const I_CHAR * const CANADA = I_( "Canada" );
   const I_CHAR * const JAPAN = I_( "Japan" );
   const I_CHAR * const MARKET = I_( "Market" );
//   const I_CHAR * const ONRBADDRESS11 = I_( "OnRbAddress11" );
//   const I_CHAR * const ONRBADDRESS01 = I_( "OnRbAddress01" );
   const I_CHAR * const ONBTNSEARCH = I_( "OnBtnSearch" );
   const I_CHAR * const DOSEARCH = I_( "doSearch" );
   const I_CHAR * const ONBTNGETACCOUNTS = I_( "OnBtnGetAccounts" );
   const I_CHAR * const KANA_NAME = I_( "KanaName" );
   const I_CHAR * const KANJI_NAME = I_( "KanjiName" );
   const I_CHAR * const IDI_LABEL1 = I_( "LABEL1" );
   const I_CHAR * const IDI_LABEL2 = I_( "LABEL2" );

}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED1;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED2;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchAccountUsing;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
IdentAccDlg::IdentAccDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( IdentAccDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( NULL )
, m_rpGIFiller( NULL )
, m_usingList( BF::AllContainerIds )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(IdentAccDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void IdentAccDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(IdentAccDlg)
   DDX_Control(pDX, IDC_BTN_NEW_ACCOUNT, m_BtnNewAccount);
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY IdentAccDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   //at this point we should have the filler process in the container;
   //look for it

   getParent()->getParameter( IDENTACCPROC::FROM_SYSTEMATIC, m_systematic );

   if( m_rpGIFiller == NULL )
   {

      GenericInterface* pWorkSessionProcess = NULL;
      pWorkSessionProcess = getWorkSession();

      if( pWorkSessionProcess )
         m_rpGIFiller = getGIContainer()->findGI( &pWorkSessionProcess->getBFSession()->getUserSession(), CMD_BPROC_FILL_SEARCH_CRITERIA );
      else
         m_rpGIFiller = getGIContainer()->findGI( getBFSession(), CMD_BPROC_FILL_SEARCH_CRITERIA );
//      m_rpGIFiller = getGIContainer()->findGI( 0, CMD_BPROC_FILL_SEARCH_CRITERIA );

      DString searchCriteriaKey = SEARCHCRITERIA::ACCOUNT_SEARCH;
      DString searchUsingList;

      m_rpGIFiller->setCurrentListItem( NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteriaKey );
      m_rpGIFiller->getField( NULL, SEARCHCRITERIA::CURRENT_USING_LIST, searchUsingList );
      m_usingList = BFContainerId( searchUsingList.convertToULong() );
   }


   assert( m_rpGIFiller != NULL );
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( IdentAccDlg, BaseMainDlg )
//{{AFX_MSG_MAP(IdentAccDlg)
ON_BN_CLICKED(IDC_BTN_GET_ACCOUNTS, OnBtnGetAccounts)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_COMMAND(ID_ACCELL_ENTITY_LIST, OnAccellEntityList)
ON_COMMAND(ID_ACCEL_ACCOUNT_LIST, OnAccelAccountList)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ACCOUNTS, OnDblclkLvAccounts)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ENTITIES, OnDblclkLvEntities)
ON_BN_CLICKED(IDC_BTN_NEW_ACCOUNT, OnBtnNewAccount)
ON_BN_CLICKED(IDC_BTN_NEW_SHAREHOLDER, OnBtnNewShareholder)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL IdentAccDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   //I am not sure how we are going to handle that, for now leave it like this(SP)
   m_dstrMarket = ConfigManager::getManager( MFDSTC )->retrieveConfig( MARKET ).getValueAsString( MARKET );

   if( m_dstrMarket == CANADA )
   {
   }
   else if( m_dstrMarket == JAPAN )
   {
   }
   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_IDACCSEARCH ) );
   return(TRUE);
}

//*****************************************************************************
void IdentAccDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   AddListControl( CLASSNAME, IDC_LV_ENTITIES, LV_ENTITIES, 
                   ifds::IdentAcctEntitiesHeadingSet, IFASTBP_PROC::ENTITY_SEARCH_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_TIMER );                   
   AddListControl( CLASSNAME, IDC_LV_IDS, LV_ENTITY_IDS, 
                   ifds::EntityIDSHeadingSet, IFASTBP_PROC::ENTITY_IDS_LIST, IDC_LV_ENTITIES, true, LISTFLAG_NOT_AUTO_ADD  );
   AddListControl( CLASSNAME, IDC_LV_ACCOUNTS, LV_ACCOUNTS, 
                   ifds::IdentAcctAccountsHeadingSet, IFASTBP_PROC::ACCOUNT_LIST, true, LISTFLAG_NOT_AUTO_ADD  );

   AddControl( CTRL_COMBO, IDC_CMB_USING, BF::NullContainerId, ifds::SearchAccountUsing, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT, IDC_EDT_SEARCH1, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT, IDC_EDT_SEARCH2, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT, IDC_EDT_SEARCH3, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address1, 
               CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_STATIC, IDC_BTN_GET_ACCOUNTS, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_BTN_MORE, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDOK, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_BTN_SEARCH, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_LBL_SEARCH1, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_LBL_SEARCH2, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_LBL_SEARCH3, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   doRefresh( this, NULL_STRING );
}

//******************************************************************************
bool IdentAccDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   FocusOnControl( IDC_EDT_SEARCH1 );
   ConnectControlsToData();
   EnableControl( IDC_EDT_SEARCH1, true );
   EnableControl( IDC_EDT_SEARCH2, true );
   EnableControl( IDC_EDT_SEARCH3, true );
   EnableControl( IDC_BTN_MORE, false );
   EnableControl( IDC_BTN_GET_ACCOUNTS, false );
   m_BtnNewAccount.EnableWindow( false );
   LoadControl( IDC_CMB_USING );
   prepareSearchFields( SEARCHACCOUNTUSING::ACCOUNT_NUMBER );
//	if(m_systematic == I_("Y")){  // temporarilly disable 
   CWnd* wnd = dynamic_cast<CWnd*>(GetDlgItem(IDC_BTN_NEW_SHAREHOLDER));
   if( wnd )wnd  ->EnableWindow(false);
//	}
   return(true);
}

//*****************************************************************************
bool IdentAccDlg::SetDataFromControl( UINT controlID,
                                      const DString &strValue,
                                      bool bFormatted,
                                      SEVERITY &sevRtn,
                                      int index
                                    )
{
   sevRtn = NO_CONDITION;
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CMB_USING:
         {
            prepareSearchFields( strValue );
            bRtn = true;
            break;
         }
      case IDC_EDT_SEARCH1:
      case IDC_EDT_SEARCH2:
      case IDC_EDT_SEARCH3:
         {
            //do nothing
            bRtn = true;
            break;
         }
      default:
         break;
   }
   return(bRtn);
}

//*****************************************************************************
bool IdentAccDlg::GetDataForControl(
                                   UINT controlID,
                                   DString &strValueOut,
                                   bool bFormatted,
                                   int index
                                   ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_EDT_ADDRESS:
         {
            DString str;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address1, str );
            if( !str.strip().empty() )
               strValueOut += str.strip() + LFCR;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address2, str );
            if( !str.strip().empty() )
               strValueOut += str.strip() + LFCR;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address3, str );
            if( !str.strip().empty() )
               strValueOut += str.strip() + LFCR;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address4, str );
            if( !str.strip().empty() )
               strValueOut += str.strip() + LFCR;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address5, str );
            if( !str.strip().empty() )
               strValueOut += str.strip() + LFCR;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::PostalCode, str );
            if( !str.strip().empty() )
               strValueOut += str.strip();
            bRtn = true;
            break;
         }

      case IDC_CMB_USING:
         {
            strValueOut = SEARCHACCOUNTUSING::ACCOUNT_NUMBER;
            bRtn = true;
            break;
         }
      case IDC_LBL_SEARCH1:
         {
            strValueOut = m_label1;
            bRtn = true;
            break;
         }
      case IDC_LBL_SEARCH2:
         {
            strValueOut = m_label2;
            bRtn = true;
            break;
         }
      case IDC_LBL_SEARCH3:
         {
            strValueOut = m_label1;
            bRtn = true;
            break;
         }
      case IDC_EDT_SEARCH1:
      case IDC_EDT_SEARCH2:
      case IDC_EDT_SEARCH3:
         {
            CString cValueOut;

            GetDlgItem( controlID )->GetWindowText( cValueOut );
            strValueOut = cValueOut;
            bRtn = true;
            break;
         }
      default:
         break;
   }
   return(bRtn);
}

//******************************************************************************
bool IdentAccDlg::GetOverrideItemString( long lSubstituteId, const DString &ColumnKey, DString &strOut )
{
   if( lSubstituteId == ifds::IdentAcctAccountsHeadingSet.getId() )
   {
      if( ColumnKey == KANA_NAME )
      {
         getParent()->getField( this, IDENTACCPROC::ACC_HOLDER_KANA_NAME, strOut );
         return(true);
      }
      else if( ColumnKey == KANJI_NAME )
      {
         getParent()->getField( this, IDENTACCPROC::ACC_HOLDER_KANJI_NAME, strOut );
         return(true);
      }
   }
   return(false);
}

//*****************************************************************************
void IdentAccDlg::DoPreListItemChanged( UINT listControlID, const DString &strKey, bool isNewItem, bool bIsDummyItem )
{
   if( listControlID == IDC_LV_ENTITIES )
   {/* temporarily 
      if ( GetList( IDC_LV_ENTITIES )->GetNextSelection() >= 0 && m_systematic != I_("Y"))// There is an entity selected
         m_BtnNewAccount.EnableWindow(true);
      else
         m_BtnNewAccount.EnableWindow(false);
    tempor end
    */
      GetList( IDC_LV_ACCOUNTS )->DeleteAllItems();
      EnableControl( IDOK, false );
   }

   if( m_searchCode == SEARCHACCOUNTUSING::SHAREHOLDER_NUMBER )
   {
      GetList( IDC_LV_ENTITIES )->Enable( false );
      GetControl( IDC_EDT_ADDRESS )->Enable( false );
   }
   else
   {
      GetList( IDC_LV_ENTITIES )->Enable( true );
      GetControl( IDC_EDT_ADDRESS )->Enable( true );
   }

   if( m_searchCode == SEARCHACCOUNTUSING::ACCOUNT_NUMBER )
   {
      GetList( IDC_LV_IDS )->DeleteAllItems();
      GetList( IDC_LV_IDS )->Enable( false );
   }
   else
   {
      GetList( IDC_LV_IDS )->Enable( true );
   }

}

//*****************************************************************************
void IdentAccDlg::OnBtnGetAccounts() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNGETACCOUNTS );

   CWaitCursor wait;

   SetMessageStatusBar( TXT_SEARCH_FOR_ACCOUNTS );
   if( getParent()->performSearch( this, IFASTBP_PROC::SEARCH_ACCOUNTS, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ACCOUNTS );
      EnableControl( IDOK, getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_LIST ) != NULL_STRING );
   }
   else
   {
      ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
   }
   SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************
void IdentAccDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNMORE );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_SEARCH_LIST );

   SetMessageStatusBar( TXT_SEARCH_FOR_ENTITIES );
   if( getParent()->performSearch( this, IFASTBP_PROC::SEARCH_MORE, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ENTITIES );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_ENTITIES )->SetSelection( crtKey );
         LoadListControl( IDC_LV_ACCOUNTS );
      }
      EnableControl( IDC_BTN_MORE, getParent()->doMoreRecordsExist( this, IFASTBP_PROC::SEARCH_MORE ) );
   }
   else
   {
      GetList( IDC_LV_ACCOUNTS )->DeleteAllItems();
      GetList( IDC_LV_ENTITIES )->DeleteAllItems();
      ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
   }
   SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************
void IdentAccDlg::OnBtnSearch() 
{
   listKey.clear();
   doSearch();
}

//*****************************************************************************

void IdentAccDlg::OnAccellEntityList() 
{
   GetList( IDC_LV_ENTITIES )->SetFocus();
}

//*****************************************************************************
void IdentAccDlg::OnAccelAccountList() 
{
   GetList( IDC_LV_ACCOUNTS )->SetFocus();
}

//*****************************************************************************
void IdentAccDlg::OnDblclkLvAccounts( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   *pResult = 0;
   if( GetList( IDC_LV_ACCOUNTS )->GetNextSelection() >= 0 )// There is an account selected
   {
      PostMessage( WM_COMMAND, IDOK );
   }
}

//*****************************************************************************
void IdentAccDlg::OnDblclkLvEntities(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;
   if( GetList( IDC_LV_ENTITIES )->GetNextSelection() >= 0 )// There is an entity selected
   {
      OnBtnGetAccounts();
   }
}

//*****************************************************************************
void IdentAccDlg::doSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, DOSEARCH );
   CWaitCursor wait;

   m_BtnNewAccount.EnableWindow(false);

   DString firstValue;
   DString secondValue;

   if( !m_oneSearchUsing )
   {
      GetControlText( IDC_EDT_SEARCH1, firstValue );
      GetControlText( IDC_EDT_SEARCH2, secondValue );
      if( firstValue == NULL_STRING && secondValue == NULL_STRING )
      {
         DString idiStr;
         DString label1;
         DString label2;

         m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, label1 );
         m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, label2 );
         addIDITagValue( idiStr, IDI_LABEL1, label1 );
         addIDITagValue( idiStr, IDI_LABEL2, label2 );
         throw EXCEPTIONFROMFILEIDI( CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED2, idiStr );
      }
   }
   else
   {
      GetControlText( IDC_EDT_SEARCH3, firstValue );
      if( firstValue == NULL_STRING )
      {
         DString idiStr;
         DString label1;

         m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, label1 );
         addIDITagValue( idiStr, IDI_LABEL1, label1 );
         throw EXCEPTIONFROMFILEIDI( CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED1, idiStr );
      }
   }
   if( m_searchCode == SEARCHACCOUNTUSING::TELEPHONE )
   {
      DString dstrMarket = DSTCommonFunctions::getMarket();
      DString strCopyOfValue = firstValue;
      if( dstrMarket == MARKET_IDS::CANADA )
      {
         strCopyOfValue.stripAll( I_CHAR( '-') );
         strCopyOfValue.stripAll( I_CHAR( '.') );
         strCopyOfValue.stripAll();
         assert( strCopyOfValue.length() == 10 );
         secondValue = strCopyOfValue.left( 3 );
         firstValue = strCopyOfValue.right( 7 );
      }
      else if( dstrMarket == MARKET_IDS::JAPAN || dstrMarket == MARKET_IDS::LUXEMBOURG )
      {
         //do not strip '-' for Japan and Lux; they use form 4 for phone
         strCopyOfValue.stripAll( I_CHAR( '.') );
         strCopyOfValue.stripAll();
//         assert( strCopyOfValue.length() == 11 );//the dash after area code is allowed
         secondValue = strCopyOfValue.left( 3 );
         firstValue = strCopyOfValue.right( 8 );
      }
   }

   getParent()->setField( this, IDENTACCPROC::SEARCH_CODE, m_searchCode );
   getParent()->setField( this, IDENTACCPROC::FIRST_VALUE, firstValue );
   getParent()->setField( this, IDENTACCPROC::SECOND_VALUE, secondValue );
   SetMessageStatusBar( TXT_SEARCH_FOR_ENTITIES );


   try
   {

      if( getParent()->performSearch( this, IFASTBP_PROC::SEARCH_INIT, SEARCH_NEXT_BLOCK ) <= WARNING )
      {
         LoadListControl( IDC_LV_ENTITIES );
         if( GetList( IDC_LV_ENTITIES )->GetNextSelection() >= 0 )// There is an entity selected
         {
            OnBtnGetAccounts();
            EnableControl( IDC_BTN_GET_ACCOUNTS, true );
         }
         else EnableControl( IDC_BTN_GET_ACCOUNTS, false );

         EnableControl( IDC_BTN_MORE, getParent()->doMoreRecordsExist( this, IFASTBP_PROC::SEARCH_INIT ) );


         bool disableGetAccount = m_searchCode == SEARCHACCOUNTUSING::ACCOUNT_NUMBER 
                                  || m_searchCode == SEARCHACCOUNTUSING::SHAREHOLDER_NUMBER;

         if( disableGetAccount )
         {
            PostMessage( WM_COMMAND, IDC_BTN_GET_ACCOUNTS );
         }

         EnableControl( IDC_BTN_GET_ACCOUNTS, !disableGetAccount );
      }
      else
      {
         GetList( IDC_LV_ACCOUNTS )->DeleteAllItems();
         GetList( IDC_LV_ENTITIES )->DeleteAllItems();
         GetList( IDC_LV_IDS      )->DeleteAllItems();
         EnableControl( IDC_BTN_GET_ACCOUNTS, false );
         ConnectControlsToData( IDC_LV_ENTITIES, false );

         CWnd * ptr = GetDlgItem( IDC_EDT_ADDRESS );
         if( ptr )
            ptr->SetWindowText( _T("") );

         ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
      }

   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }

   SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************
void IdentAccDlg::prepareSearchFields( const DString &searchUsingKey )
{
   DString label1;
   DString label2;
   CString strColon;
   strColon.LoadString(TXT_COLON);
   m_searchCode = searchUsingKey;
   //setting the current list item will set the labels
   m_rpGIFiller->setCurrentListItem( NULL, m_usingList, searchUsingKey );
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, m_label1 );
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, m_label2 );
   if( m_label2 == NULL_STRING )
   {
      m_label1 += strColon;
      hide2EditFields();
      LoadControl( IDC_LBL_SEARCH3 );
      m_oneSearchUsing = true;
   }
   else
   {
      m_label1 += strColon;
      m_label2 += strColon;
      hide1EditField();
      LoadControl( IDC_LBL_SEARCH1 );
      LoadControl( IDC_LBL_SEARCH2 );
      m_oneSearchUsing = false;
   }
}

//*****************************************************************************
void IdentAccDlg::hide2EditFields()
{
   GetControl( IDC_EDT_SEARCH1 )->Show( false );
   GetControl( IDC_EDT_SEARCH2 )->Show( false );
   GetControl( IDC_LBL_SEARCH1 )->Show( false );
   GetControl( IDC_LBL_SEARCH2 )->Show( false );
   GetControl( IDC_EDT_SEARCH3 )->Show( true );
   GetControl( IDC_LBL_SEARCH3 )->Show( true );
   GetControl( IDC_EDT_SEARCH1 )->Clear();
   GetControl( IDC_EDT_SEARCH2 )->Clear();
   GetControl( IDC_EDT_SEARCH3 )->Clear();
}

//******************************************************************************
void IdentAccDlg::hide1EditField()
{
   GetControl( IDC_EDT_SEARCH3 )->Show( false );
   GetControl( IDC_LBL_SEARCH3 )->Show( false );
   GetControl( IDC_EDT_SEARCH1 )->Show( true );
   GetControl( IDC_EDT_SEARCH2 )->Show( true );
   GetControl( IDC_LBL_SEARCH1 )->Show( true );
   GetControl( IDC_LBL_SEARCH2 )->Show( true );
   GetControl( IDC_EDT_SEARCH1 )->Clear();
   GetControl( IDC_EDT_SEARCH2 )->Clear();
   GetControl( IDC_EDT_SEARCH3 )->Clear();
}

//******************************************************************************
BOOL IdentAccDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }
   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }
   return(isTranslated);
}

//******************************************************************************
void IdentAccDlg::OnBtnNewAccount() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnNewAccount" ) );
   CWaitCursor wait;
   if( GetList( IDC_LV_ENTITIES )->GetNextSelection() < 0 )// There isn't any entity selected
      return;

   DString strAccountNum;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_LIST, ifds::AccountNum, strAccountNum, false);
   setParameter( IDENTACCPROC::ACCOUNT_NUM, strAccountNum );
   if( getParent()->send(this, IDENTACCPROC::CREATE_NEW_ACCOUNT) )
      Exit(CMD_OK);
   else
   {
      if( GETHIGHESTSEVERITY() >= WARNING )
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   }
}

//******************************************************************************
void IdentAccDlg::OnBtnNewShareholder() 
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnNewShareholder") );
   CWaitCursor wait;

   if( getParent()->send(this, IDENTACCPROC::CREATE_NEW_SHAREHOLDER) )
      Exit(CMD_OK);
   else
   {
      if( GETHIGHESTSEVERITY() >= WARNING )
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   }
}

bool IdentAccDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   DString str;
   if( lSubstituteId == ifds::IdentAcctEntitiesHeadingSet.getId() )
   {
      getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, str );
      return(listKey.insert( str ).second != NULL);
   }

   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/IdentAccDlg.cpp-arc  $
 * 
 *    Rev 1.42   Sep 15 2005 15:13:28   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.41   Mar 21 2003 18:37:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.40   Mar 07 2003 15:01:26   PURDYECH
 * Fixed some bad container IDs
 * 
 *    Rev 1.39   Jan 29 2003 13:03:26   HSUCHIN
 * undo timer removal
 * 
 *    Rev 1.38   Jan 28 2003 15:27:34   HSUCHIN
 * removed timer control 
 * 
 *    Rev 1.37   Oct 23 2002 13:49:24   HERNANDO
 * Changed address display - removed blank lines.
 * 
 *    Rev 1.36   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.35   Oct 09 2002 16:02:22   PURDYECH
 * BFFieldId fixups
 * 
 *    Rev 1.34   Sep 30 2002 11:01:40   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.33   Aug 29 2002 12:57:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.32   24 May 2002 15:56:44   KOVACSRO
 * Added timer functionality.
 * 
 *    Rev 1.31   22 May 2002 19:16:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.30   27 Mar 2002 20:01:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.29   Sep 06 2001 14:10:06   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.28   Aug 22 2001 15:04:30   DINACORN
 * Revised quick bug for search by telephone
 * 
 *    Rev 1.27   Aug 21 2001 18:27:46   DINACORN
 * Quick bug fixed for search by telephone
 * 
 *    Rev 1.26   Aug 15 2001 10:39:46   YINGBAOL
 * disable NASU 
 * 
 *    Rev 1.25   Aug 10 2001 12:53:22   YINGBAOL
 * disable NASU if identAcctDlg lauched from systematic and allocation screen
 * 
 *    Rev 1.24   Aug 09 2001 11:30:26   YINGBAOL
 * fix new account button crash issue
 * 
 *    Rev 1.23   08 Aug 2001 12:20:04   HSUCHIN
 * beautify source
 * 
 *    Rev 1.22   08 Aug 2001 12:18:22   HSUCHIN
 * bug fix for account search to display error properly
 * 
 *    Rev 1.21   Aug 07 2001 13:20:14   YINGBAOL
 * fix second search crash problem
 * 
 *    Rev 1.20   Jul 29 2001 15:12:32   YINGBAOL
 * sync. up 1.9.1.0
 * 
 *    Rev 1.19   Jun 16 2001 15:21:58   ZHANGCEL
 * Fixed crash in the doInit()
 * 
 *    Rev 1.18   Apr 12 2001 10:32:58   YINGZ
 * fix multi entity problem
 * 
 *    Rev 1.17   Feb 09 2001 08:34:08   BUZILAMI
 * fix assert in Search for account
 * 
 * 
 *    Rev 1.16   Jan 04 2001 16:23:38   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.15   Dec 13 2000 14:44:32   KOVACSRO
 * Modified DoPreListItemChanged.
 * 
 *    Rev 1.14   Nov 13 2000 12:27:12   DINACORN
 * Fixed many bugs found by QA
 * 
 *    Rev 1.13   Oct 19 2000 17:15:00   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.12   Oct 11 2000 14:27:20   KOVACSRO
 * Implemented OnBtnNewAccount and OnBtnNewShareholder.
 * 
 *    Rev 1.11   Sep 08 2000 11:10:44   PETOLESC
 * Fixed bug in GetDataForControl().
 * 
 *    Rev 1.10   Sep 01 2000 16:27:14   PETOLESC
 * Removed RButtons.
 * 
 *    Rev 1.9   Jun 08 2000 15:21:36   YINGZ
 * fix search using shrnum and acctnum problem to meet qa requirements
 * 
 *    Rev 1.8   Jun 01 2000 13:56:46   BUZILA
 * Get Accounts button should be disabled before search for Entity 
 * 
 *    Rev 1.7   May 31 2000 16:45:12   BUZILA
 * data not found fix
 * 
 *    Rev 1.6   Apr 26 2000 09:52:38   VASILEAD
 * Fixed error message when search criterias are empty
 * 
 *    Rev 1.5   Apr 26 2000 09:45:04   POPESCUS
 * error message if search criterias are empty
 * 
 *    Rev 1.4   Apr 05 2000 12:53:36   DT24433
 * changed to use getGIContainer
 * 
 *    Rev 1.3   Mar 07 2000 15:45:02   POPESCUS
 * more work on the account search screen
 * 
 *    Rev 1.2   Mar 03 2000 19:34:06   POPESCUS
 * save the work
 * 
 *    Rev 1.1   Mar 03 2000 12:11:10   POPESCUS
 * account search work
 * 
 *    Rev 1.0   Feb 29 2000 15:35:24   BUZILA
 * Initial revision.
// 
*/
