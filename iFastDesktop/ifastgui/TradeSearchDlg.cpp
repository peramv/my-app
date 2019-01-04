//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TradeSearchDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/25/2003
//
// ^CLASS    : TradeSearchDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef TRADESEARCHDLG_H
   #include "TradeSearchDlg.h"
#endif
#include <ifastbp\tradesearchprocessincludes.h>
#include <ifastbp\transcancelprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcommonfunction.hpp>


#include <ifastbp\HypoRedProcessIncludes.h>
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradeSearchDlg > dlgCreator( CMD_GUI_TRADE_SEARCH );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_CANCEL;

namespace
{
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const CLASSNAME         = I_( "TradeSearchDlg" );
   const I_CHAR * const LV_RESULTS        = I_( "ResultsList" );
   const I_CHAR * const CRITERIA_SCREEN   = I_( "CriteriaScreen" );
   const I_CHAR * const RESULTS_SCREEN    = I_( "ResultsScreen" );
   const I_CHAR * const NETWORK           = I_( "NetworkID" );
   const I_CHAR * const ACCOUNTNUM        = I_( "AccountNum" );
   const I_CHAR * const TRANSNUM          = I_( "TransNum" );
   const I_CHAR * const WIREORD           = I_( "WireOrdNum" );
   const I_CHAR * const EXTTRANS          = I_( "ExtTransNum" );
   const I_CHAR * const SENDREF           = I_( "SendRefNum" );
   const I_CHAR * const PARTREF           = I_( "PartRefNum" );
   const I_CHAR * const MASTERREF         = I_( "MasterRefNum" );
   const I_CHAR * const FUND_CODE         = I_( "rxFundCode" );
   const I_CHAR * const EXTERNAL_ID       = I_( "ExternalIdType" );
   const I_CHAR * const PURCHASE          = I_( "ED" );
   const I_CHAR * const REDEMPTION        = I_( "PW" );
   const I_CHAR * const TRADEDATE         = I_( "TradeDate" );
   const I_CHAR * const FUNDCLASS         = I_( "FundCode" );
   const I_CHAR * const TRANSTYPE         = I_( "TransType" ); 

   //transactions
   const I_CHAR *pALLFUND           = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM        = I_( "AccountNum" );
   const I_CHAR *pTRANSID           = I_( "TransId" );
   const I_CHAR *pFUNDCODE          = I_( "FundCode" );
   const I_CHAR *pCLASSCODE         = I_( "ClassCode" );
   const I_CHAR *pNUMENTRY          = I_( "NumEntry" );
   const I_CHAR *pPENDING           = I_( "Pending" );
   const I_CHAR *pTRANSTYPE         = I_( "TransType" );
   const I_CHAR *pTRANSNUM          = I_( "TransNum" );
   const I_CHAR *pTRADEDATE         = I_( "TradeDate" );
   const I_CHAR *pINQUIRYONLY       = I_( "InquiryOnly" );
   const I_CHAR *pFUNDNUMBER        = I_( "FundNumber" );
   const I_CHAR *pFUNDWKN           = I_( "FundWKN" );
   const I_CHAR *pFUNDISIN          = I_( "FundISIN" );

   const I_CHAR * const ALL_TRADES        = I_("All");
}

namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const ALLOC_ELIG; // Trantype is one of ("ED,PW,AW,AF,AF91,RC,P,S,V");
}
namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADE_SEARCH;
   extern CLASS_IMPORT I_CHAR * const MSG_SEARCH;
   extern CLASS_IMPORT I_CHAR * const BULK_CANCELLATION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId BulkCancelAllowed;
   extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
}

//******************************************************************************
TradeSearchDlg::TradeSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TradeSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_strScreenType(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	
   //{{AFX_DATA_INIT(TradeSearchDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
TradeSearchDlg::~TradeSearchDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void TradeSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(TradeSearchDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TradeSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradeSearchDlg)
   ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
   ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
   ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
   ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
   ON_BN_CLICKED(IDC_BTN_BULK_CANCEL, OnBtnBulkCancel )
   ON_MESSAGE( WM_LAUNCH_IDENT_ACC,OpenIdentifyAccountsDlg )
   ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
   ON_BN_CLICKED(IDC_BTN_MESSAGE, OnBtnMessage)
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_RADIO_PENDING, OnRBPending)
   ON_BN_CLICKED(IDC_RADIO_TRANSACTION, OnRBTransaction)
   ON_NOTIFY(NM_DBLCLK, IDC_LV_RESULTS, OnDblclkLvResults)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TradeSearchDlg message handlers


//******************************************************************************
void TradeSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   SetUserAccesFunctionCode(UAF::TRADE_SEARCH);
   addControls();
   showCriteria();
}

//******************************************************************************
SEVERITY TradeSearchDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   return(sevRtn);
}
//******************************************************************************
void TradeSearchDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    

	//list controls
	AddListControl( CLASSNAME,IDC_LV_RESULTS, LV_RESULTS, ifds::PendingSearchHeadingSet,
      IFASTBP_PROC::PENDING_LIST, 0,true, LISTFLAG_NOT_AUTO_ADD );

	//controls
   
   AddControl( CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::CRITERIA, ifds::SearchType,
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_NETWORK_ID, IFASTBP_PROC::CRITERIA, ifds::NetworkID   , 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_DATE,  IDC_DTP_FROM_DATE, IFASTBP_PROC::CRITERIA, ifds::FromDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );    
   AddControl( CTRL_DATE,  IDC_DTP_TO_DATE, IFASTBP_PROC::CRITERIA, ifds::ToDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );   
	AddControl( CTRL_EDIT, IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::CRITERIA, ifds::TransNum, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_DATE,  IDC_DTP_ACCOUNT_DATE, IFASTBP_PROC::CRITERIA, ifds::ToDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	
	AddControl( CTRL_DATE,  IDC_DTP_TRADE_DATE, IFASTBP_PROC::CRITERIA, ifds::TradeDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_FUND_NUMBER, IFASTBP_PROC::CRITERIA, ifds::FundNumber, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_FUND_CODE, IFASTBP_PROC::CRITERIA, ifds::FundCode, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_CLASS_CODE, IFASTBP_PROC::CRITERIA, ifds::ClassCode, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_WKN, IFASTBP_PROC::CRITERIA, ifds::FundWKN, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_ISIN, IFASTBP_PROC::CRITERIA, ifds::FundISIN, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

	 AddControl(CTRL_STATIC, IDC_STATIC_FUND_NAME, IFASTBP_PROC::CRITERIA, ifds::FundName,
		 CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	
	 AddControl( CTRL_DATE,  IDC_DTP_TRADE_DATE_FROM, IFASTBP_PROC::CRITERIA, ifds::FromDate, 
		 CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	 AddControl( CTRL_DATE,  IDC_DTP_TRADE_DATE_TO, IFASTBP_PROC::CRITERIA, ifds::ToDate, 
		 CTRLFLAG_AUTO_UPDATE_ON_CHANGE ); 
	 AddControl( CTRL_EDIT, IDC_EDIT_ACCOUNT, IFASTBP_PROC::CRITERIA, ifds::AccountNum, 
		 CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	 AddControl( CTRL_COMBO, IDC_CMB_TRANS_TYPE_FC, IFASTBP_PROC::CRITERIA, ifds::TradesSearchTransType,
		 CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );

	 DSTEdit* pEditAct = dynamic_cast<DSTEdit*>(GetControl(IDC_EDIT_ACCOUNT));
	 pEditAct->SetAllDigits(true);

   DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE));
   pEdit->SetAllDigits(true);

	AddControl( CTRL_COMBO, IDC_CMB_EXTERNAL_ID_TYPE, IFASTBP_PROC::CRITERIA, ifds::ExternalIdType,
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
	addControlGroupIDForPermissionCheck(0);
	//addControlGroupIDForPermissionCheck(IDC_LV_RESULTS);

	GetDlgItem( IDC_BTN_BULK_CANCEL )->EnableWindow( false );
}

//******************************************************************************

bool TradeSearchDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   return(true);
}

//******************************************************************************
void TradeSearchDlg::OnBtnRefresh() 
{
	TRACE_METHOD( CLASSNAME, I_( "OnBtnRefresh" ) );

	GetDlgItem(IDC_BTN_REFRESH)->SetFocus();
	CWaitCursor wait;

   getParent()->reset(this, IFASTBP_PROC::CRITERIA);
	ReregisterObservers();
	showCriteria();
	CheckPermission();

	GetDlgItem( IDC_BTN_BULK_CANCEL )->EnableWindow( false );
}

//******************************************************************************
void TradeSearchDlg::OnBtnBrowse() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBrowse" ) );

	GetDlgItem(IDC_BTN_BROWSE)->SetFocus();
	CWaitCursor wait;

   DString strAccNum, strFund, strClass, strAllFundMode(I_("N")), strTransId,
      strTransNum, strTradeDate, strTransType;

   if (isPending())
   {
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::rxAcctNum, strAccNum, true);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, strFund, true);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, strClass, true);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, strTradeDate, true);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, strTransType, true);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, strTransNum, true);


      setParameter(pACCOUNTNUM, strAccNum);
      setParameter(pFUNDCODE, strFund);
      setParameter(pCLASSCODE, strClass);
      setParameter(pTRANSTYPE, strTransType);
      setParameter(pTRANSNUM, strTransNum);
      setParameter(pTRADEDATE, strTradeDate);
      setParameter(pPENDING, YES);
      setParameter(pALLFUND, YES);

   }
   else
   {
      getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::AccountNum, strAccNum, true);
      getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::TransId, strTransId, true);
      getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::rxFundCode, strFund, true);
      getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::rxClassCode, strClass, true);
      setParameter(pACCOUNTNUM, strAccNum);
      setParameter(pTRANSID, strTransId);
      setParameter(pFUNDCODE, strFund);
      setParameter(pCLASSCODE, strClass);
      setParameter(pPENDING, NO);
      setParameter(pALLFUND, NO);
      setParameter (I_("CalledFrom"), I_( "TradeSearch") );
   }

   try
   {
      bool bModal = true;
      E_COMMANDRETURN eRtn = CMD_OK;
      SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );
      eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
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
void TradeSearchDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );

	GetDlgItem(IDC_BTN_MORE)->SetFocus();
	CWaitCursor wait;

   SEVERITY sev = NO_SEVERITY;
   if (isPending())
      sev = getParent()->performSearch(this, IFASTBP_PROC::PENDING_LIST, SEARCH_NEXT_BLOCK );
   else
      sev = getParent()->performSearch(this, IFASTBP_PROC::TRANSACTION_LIST, SEARCH_NEXT_BLOCK );
   if (sev>WARNING)
   {
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }
   showResults();
}

//******************************************************************************
void TradeSearchDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

	GetDlgItem(IDC_BTN_SEARCH)->SetFocus();

	DString strValidCriteria, strPending;
	getParent()->getField(this, ifds::ValidTradeCriteria, strValidCriteria, false);
	if (strValidCriteria == NO)
	{
		CString strValidCriteria;
      DString strSearchType;
      LoadControls();
		strValidCriteria.LoadString(TXT_VALID_CRITERIA);
		AfxMessageBox(strValidCriteria, MB_OK | MB_ICONSTOP);
	   getParent()->getField(this, ifds::SearchType, strSearchType, false);
      if (strSearchType.strip() == NETWORK)
		   GetDlgItem(IDC_CMB_NETWORK_ID)->SetFocus();
      else if( strSearchType.strip() == TRADEDATE )
			GetDlgItem(IDC_DTP_TRADE_DATE)->SetFocus();
	  else if( strSearchType.strip() == FUNDCLASS )
	  {	   
		   if( !isPending() )
			GetDlgItem(IDC_DTP_TRADE_DATE_FROM)->SetFocus();
		   else
			GetDlgItem(IDC_EDIT_FUND_CODE)->SetFocus();
	  }
     else if( ALL_TRADES == strSearchType || TRANSTYPE == strSearchType)
        GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
	  else
		   GetDlgItem(IDC_EDT_SEARCH_VALUE)->SetFocus();
		return;
	}

	CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCHING );

   SEVERITY sev = NO_SEVERITY;
   if (isPending())
      sev = getParent()->performSearch(this, IFASTBP_PROC::PENDING_LIST, SEARCH_START );
   else
      sev = getParent()->performSearch(this, IFASTBP_PROC::TRANSACTION_LIST, SEARCH_START );
   if (sev>WARNING)
   {
      SetMessageStatusBar( NULL_STRING );
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }

   showResults();
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void TradeSearchDlg::OnBtnBulkCancel() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBulkCancel" ) );
	
   CWaitCursor wait;  

   try
   {
      int iItemNumber = 0;
	  iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::TRANSACTION_LIST );		
	  if ( iItemNumber > 0 )
	  {
		DString dstrTradeDate, dstrFund, dstrClass, dstrTransNum;
		getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::TradeDate,   dstrTradeDate, true );
		getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::rxFundCode,  dstrFund,      true );
		getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::rxClassCode, dstrClass,     true );	
		getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::TransNum,    dstrTransNum,  true);

	      
		setParameter( TRANSCANCEL::BULK_CANCEL, I_( "Y" ) );
		setParameter( TRANSCANCEL::TRADE_DATE,  dstrTradeDate );
		setParameter( TRANSCANCEL::FUND,        dstrFund );
		setParameter( TRANSCANCEL::CLASS,       dstrClass );
		setParameter( TRANSCANCEL::TRANS_NUM,   dstrTransNum );

		bool bModal = true;
		E_COMMANDRETURN eRtn = CMD_OK;
		SetMessageStatusBar( TXT_LOAD_TRANSCANCEL );

		eRtn = invokeCommand( getParent(), 
								CMD_BPROC_TRANS_CANCEL, 
								PROC_NO_TYPE, 
								isModal(), 
								NULL );

		switch( eRtn )
		{
			case CMD_OK:
			case CMD_CANCEL:
			case CMD_MODELESS_INPROCESS:
				break;
			default:
				// Display error
				ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
				break;
		}
	  }
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
void TradeSearchDlg::showCriteria()
{
	TRACE_METHOD( CLASSNAME, I_( "showCriteria" ) );

	m_strScreenType = CRITERIA_SCREEN;

	//list controls
	GetList(IDC_LV_RESULTS)->ShowWindow(false);

	//static controls, frames (group boxes)
	GetDlgItem(IDC_RESULTS_FRAME)->ShowWindow(SW_HIDE);

   //combo boxes
	GetControl(IDC_CMB_USING)->Show(true);

	//show or hide account searching related controls
   DString strSearchType;
	getParent()->getField(this, ifds::SearchType, strSearchType, false);
	showAccountSearchControls(strSearchType==ACCOUNTNUM);
	
   //radio buttons
	GetDlgItem(IDC_RADIO_PENDING)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_TRANSACTION)->EnableWindow(true);

	ConnectControlsToData();
   ConnectListToData( IDC_LV_RESULTS, false ); 
	
	// connect or didconnect base on the search type
	ConnectControlToData( IDC_DTP_ACCOUNT_DATE, strSearchType == ACCOUNTNUM);
	
	LoadControls();

	//buttons
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(true);
	GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);

   CButton* pRB = (CButton*) GetDlgItem(IDC_RADIO_PENDING);
   pRB->SetCheck(1);
   pRB = (CButton*) GetDlgItem(IDC_RADIO_TRANSACTION);
   pRB->SetCheck(0);
   OnRBPending();

	GetDlgItem(IDC_CMB_USING)->SetFocus();
	CheckPermission();
}

//******************************************************************************
void TradeSearchDlg::showResults()
{
	TRACE_METHOD( CLASSNAME, I_( "showResults" ) );

	m_strScreenType = RESULTS_SCREEN;

	GetList(IDC_LV_RESULTS)->ShowWindow(SW_SHOW);
	
	//buttons
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(false);

	//static controls, frames (group boxes)
	GetDlgItem(IDC_RESULTS_FRAME)->ShowWindow(SW_SHOW);

   //radio buttons
	GetDlgItem(IDC_RADIO_PENDING)->EnableWindow(false);
	GetDlgItem(IDC_RADIO_TRANSACTION)->EnableWindow(false);

   ConnectListToData( IDC_LV_RESULTS, true ); 

   LoadListControl(IDC_LV_RESULTS);
   
   if (isPending())
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_LIST ) );
   else
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::TRANSACTION_LIST ) );

	GetList(IDC_LV_RESULTS)->SetFocus();

	CheckPermission();


	// If Seaching for processed transaction, using "Trade Date"	
	DString dstrSearchType, dstrBulkAllowed;  	
	getParent()->getField( this, ifds::SearchType, dstrSearchType, false );
    if( dstrSearchType.strip() == TRADEDATE && 
		!isPending() &&
		hasUpdatePermission( UAF::BULK_CANCELLATION ) )
	{		         
		getParent()->getField(this, IFASTBP_PROC::CRITERIA, ifds::BulkCancelAllowed, dstrBulkAllowed, false );
	}

	GetDlgItem( IDC_BTN_BULK_CANCEL )->EnableWindow( I_( "Y" ) == dstrBulkAllowed.stripAll().upperCase() );
}

//******************************************************************************
void TradeSearchDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );
	DString strSearchType;
	getParent()->getField(this, ifds::SearchType, strSearchType, false);
	switch( controlID )
   {
      case IDC_CMB_USING:
         {				
			showNetworkControls(strValue==NETWORK);
            GetDlgItem( IDC_STATIC_SEARCH_FIELD ) ->ShowWindow( ALL_TRADES != strValue && 
                                                                TRANSTYPE  != strValue);
			if (strValue != NETWORK)
            {
			   showAccountSearchControls(strValue==ACCOUNTNUM);
            }
			GetDlgItem( IDC_TXT_EXTERNAL_ID_TYPE )->ShowWindow( strValue == EXTERNAL_ID );
			GetDlgItem( IDC_CMB_EXTERNAL_ID_TYPE )->ShowWindow( strValue == EXTERNAL_ID );
			GetDlgItem( IDC_TXT_EXTERNAL_ID_TYPE )->ShowWindow( strValue == EXTERNAL_ID );
			GetDlgItem( IDC_CMB_EXTERNAL_ID_TYPE )->EnableWindow( strValue == EXTERNAL_ID );
			ConnectControlToData( IDC_CMB_EXTERNAL_ID_TYPE, false );

			showTradeDateSearchControls( strValue == TRADEDATE );
			showFundClassSearchControls( strValue == FUNDCLASS );
			enableFundClassControls(strValue == TRADEDATE || strValue == FUNDCLASS);
//edit search value...
		 /*GetDlgItem (IDC_EDT_SEARCH_VALUE)->EnableWindow (strValue != NETWORK && strValue != TRADEDATE);
         GetControl (IDC_EDT_SEARCH_VALUE)->Show (strValue != NETWORK && strValue != TRADEDATE); shashi*/
		 GetDlgItem (IDC_EDT_SEARCH_VALUE)->EnableWindow (strValue != NETWORK && strValue != TRADEDATE && strValue != FUNDCLASS &&
                                                          ALL_TRADES != strValue && TRANSTYPE  != strValue); 
         GetControl (IDC_EDT_SEARCH_VALUE)->Show (strValue != NETWORK && strValue != TRADEDATE && strValue != FUNDCLASS &&
                                                  ALL_TRADES != strValue && TRANSTYPE  != strValue);



			if (strValue==NETWORK)
               LoadControl(IDC_CMB_NETWORK_ID);
            else if(TRANSTYPE == strValue)
               LoadControl(IDC_CMB_TRANS_TYPE_FC);
            else if(ALL_TRADES == strValue)
               break;//load no further controlls  
            else
            {		
				//reinit IDC_EDT_SEARCH_VALUE with the right field
				if ( strValue == EXTERNAL_ID )
					reInitEditSearch( I_( "ExternalId" ) );
				else               
					reInitEditSearch(strValue);

				if ( strValue == TRADEDATE )
					LoadControl( IDC_DTP_TRADE_DATE );
				
				if ( strValue == FUNDCLASS )
				{
					if(!isPending())
					{
					  LoadControl( IDC_DTP_TRADE_DATE_FROM );
					  LoadControl( IDC_DTP_TRADE_DATE_TO );
					}
					LoadControl( IDC_CMB_TRANS_TYPE_FC );
				}
               //set all digits if it is transaction number search
               DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE));
               if (strValue==TRANSNUM || strValue==WIREORD || strValue==ACCOUNTNUM )//or it should be numeric for all search types?
                  pEdit->SetAllDigits(true);
               else
                  pEdit->SetAllDigits(false);

               //connect to data and re-load IDC_EDT_SEARCH_VALUE
               ConnectControlToData(IDC_EDT_SEARCH_VALUE, true);
               LoadControl(IDC_EDT_SEARCH_VALUE);
			   if(strValue==ACCOUNTNUM)
			   {	
			   		ConnectControlToData(IDC_DTP_ACCOUNT_DATE, true, true );
					LoadControl(IDC_DTP_ACCOUNT_DATE);
			   }
			   else if ( strValue == EXTERNAL_ID )
			   {											
					ConnectControlToData( IDC_CMB_EXTERNAL_ID_TYPE, true );
					LoadControl( IDC_CMB_EXTERNAL_ID_TYPE );

						// Hide and disconnect Date related controls							
						GetDlgItem(IDC_TXT_FROM_DATE)->ShowWindow( false );
						GetDlgItem(IDC_TXT_ACCOUNT_DATE)->ShowWindow( false );
						GetDlgItem(IDC_DTP_ACCOUNT_DATE)->EnableWindow( false );
						GetControl(IDC_DTP_ACCOUNT_DATE)->Show( false );
						ConnectControlToData(IDC_DTP_ACCOUNT_DATE, false );

						GetDlgItem(IDC_TXT_TO_DATE)->ShowWindow( false );						
						GetDlgItem(IDC_DTP_TO_DATE)->EnableWindow( false );
						GetControl(IDC_DTP_TO_DATE)->Show( false );
						ConnectControlToData(IDC_DTP_TO_DATE, false );

						GetDlgItem( IDC_DTP_FROM_DATE )->EnableWindow( false );
						GetControl( IDC_DTP_FROM_DATE )->Show( false );		
						ConnectControlToData(IDC_DTP_FROM_DATE, false );
				}
				else
				{
					ConnectControlToData(IDC_DTP_ACCOUNT_DATE, false );
					LoadControl(IDC_DTP_FROM_DATE);
				}
				CheckPermission();
			}
	      }
         break;
		case IDC_EDIT_FUND_NUMBER:
         {
				if ( strSearchType == TRADEDATE || strSearchType == FUNDCLASS )
				{
					LoadControl( IDC_EDIT_FUND_CODE );
					LoadControl( IDC_EDIT_CLASS_CODE );
					LoadControl( IDC_EDIT_WKN );
					LoadControl( IDC_EDIT_ISIN );
					LoadControl( IDC_STATIC_FUND_NAME );
				}
			}
			break;
		case IDC_EDIT_FUND_CODE:
         {
				if ( strSearchType == TRADEDATE || strSearchType == FUNDCLASS )
				{
					LoadControl( IDC_EDIT_FUND_NUMBER );
					LoadControl( IDC_EDIT_CLASS_CODE );
					LoadControl( IDC_EDIT_WKN );
					LoadControl( IDC_EDIT_ISIN );
					LoadControl( IDC_STATIC_FUND_NAME );
				}
			}
			break;
		case IDC_EDIT_CLASS_CODE:
         {
				if ( strSearchType == TRADEDATE || strSearchType == FUNDCLASS )
				{
					LoadControl( IDC_EDIT_FUND_CODE );
					LoadControl( IDC_EDIT_FUND_NUMBER );
					LoadControl( IDC_EDIT_WKN );
					LoadControl( IDC_EDIT_ISIN );
					LoadControl( IDC_STATIC_FUND_NAME );
				}
			}
			break;
		case IDC_EDIT_WKN:
         {
				if ( strSearchType == TRADEDATE || strSearchType == FUNDCLASS )
				{
					LoadControl( IDC_EDIT_FUND_CODE );
					LoadControl( IDC_EDIT_CLASS_CODE );
					LoadControl( IDC_EDIT_FUND_NUMBER );
					LoadControl( IDC_EDIT_ISIN );
					LoadControl( IDC_STATIC_FUND_NAME );
				}
			}
			break;
		case IDC_EDIT_ISIN:
         {
				if ( strSearchType == TRADEDATE || strSearchType == FUNDCLASS )
				{
					LoadControl( IDC_EDIT_FUND_CODE );
					LoadControl( IDC_EDIT_CLASS_CODE );
					LoadControl( IDC_EDIT_WKN );
					LoadControl( IDC_EDIT_FUND_NUMBER );
					LoadControl( IDC_STATIC_FUND_NAME );
				}
			}
			break;
		default:
         break;
   }
}
//******************************************************************************
void TradeSearchDlg::showNetworkControls(bool bShowNetwork)
{
   GetDlgItem(IDC_CMB_NETWORK_ID)->EnableWindow(bShowNetwork);
	GetControl(IDC_CMB_NETWORK_ID)->Show(bShowNetwork);
   GetDlgItem(IDC_DTP_FROM_DATE)->EnableWindow(bShowNetwork);
   GetControl(IDC_DTP_FROM_DATE)->Show(bShowNetwork);
	GetDlgItem(IDC_DTP_TO_DATE)->EnableWindow(bShowNetwork);
	GetControl(IDC_DTP_TO_DATE)->Show(bShowNetwork);

   UINT nShow = SW_HIDE;
   if (bShowNetwork) nShow = SW_SHOW;

   GetDlgItem(IDC_TXT_FROM_DATE)->ShowWindow(nShow);
	GetDlgItem(IDC_TXT_TO_DATE)->ShowWindow(nShow);

}

//******************************************************************************
void TradeSearchDlg::showAccountSearchControls(bool bShowAcctSearch)
{
   GetDlgItem(IDC_DTP_FROM_DATE)->EnableWindow(false);
   GetControl(IDC_DTP_FROM_DATE)->Show(SW_HIDE);
	GetDlgItem(IDC_DTP_TO_DATE)->EnableWindow(false);
	GetControl(IDC_DTP_TO_DATE)->Show(SW_HIDE);
	GetDlgItem(IDC_TXT_FROM_DATE)->ShowWindow(false);
	GetDlgItem(IDC_TXT_TO_DATE)->ShowWindow(false);
	GetDlgItem(IDC_DTP_ACCOUNT_DATE)->EnableWindow(bShowAcctSearch);
   GetControl(IDC_DTP_ACCOUNT_DATE)->Show(bShowAcctSearch);
	ConnectControl(IDC_DTP_ACCOUNT_DATE, bShowAcctSearch);
	
	UINT nShow = SW_HIDE;
   if (bShowAcctSearch) nShow = SW_SHOW;
   
	GetDlgItem(IDC_TXT_ACCOUNT_DATE)->ShowWindow(nShow);
	
}

//******************************************************************************
void TradeSearchDlg::showTradeDateSearchControls(bool bShowTradeDateSearch)
{
    GetDlgItem( IDC_DTP_TRADE_DATE )->EnableWindow( bShowTradeDateSearch );
	GetControl( IDC_DTP_TRADE_DATE )->Show( bShowTradeDateSearch );
	ConnectControlToData(IDC_DTP_TRADE_DATE, bShowTradeDateSearch );
}
//******************************************************************************
void TradeSearchDlg::showFundClassSearchControls(bool bShowFundClassSearch)
{
	
	bool bIsPending = isPending();
	GetDlgItem( IDC_DTP_TRADE_DATE_FROM )->EnableWindow( bShowFundClassSearch &&
														 !bIsPending );
	GetDlgItem( IDC_DTP_TRADE_DATE_FROM )->ShowWindow( bShowFundClassSearch &&
														 !bIsPending );
	ConnectControlToData(IDC_DTP_TRADE_DATE_FROM, bShowFundClassSearch &&
														 !bIsPending );

	GetDlgItem( IDC_DTP_TRADE_DATE_TO )->EnableWindow( bShowFundClassSearch &&
														 !bIsPending );
	GetDlgItem( IDC_DTP_TRADE_DATE_TO )->ShowWindow( bShowFundClassSearch &&
														 !bIsPending );
	ConnectControlToData(IDC_DTP_TRADE_DATE_TO, bShowFundClassSearch &&
														 !bIsPending );

	GetDlgItem( IDC_EDIT_ACCOUNT )->EnableWindow( bShowFundClassSearch );
	GetDlgItem( IDC_EDIT_ACCOUNT )->ShowWindow( bShowFundClassSearch );
	ConnectControlToData(IDC_EDIT_ACCOUNT, bShowFundClassSearch );

	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->EnableWindow( bShowFundClassSearch );
	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->ShowWindow( bShowFundClassSearch );
	ConnectControlToData(IDC_CMB_TRANS_TYPE_FC, bShowFundClassSearch );

	UINT nShow = SW_HIDE;
    if (bShowFundClassSearch) nShow = SW_SHOW;

	GetDlgItem( IDC_STATIC_FROM_DATE )->ShowWindow( nShow && !bIsPending );
	GetDlgItem( IDC_STATIC_TO_DATE )->ShowWindow( nShow && !bIsPending );
	GetDlgItem( IDC_STATIC_ACCOUNT )->ShowWindow( nShow);
	GetDlgItem( IDC_STATIC_TRANS_TYPE_FC )->ShowWindow( nShow );
	GetDlgItem( IDC_STATIC_SEARCH_FIELD )->ShowWindow( !bIsPending );
	
	 
}
//******************************************************************************
void TradeSearchDlg::enableFundClassControls(bool bShowFundClassControls)
{
	DString dstrMarket = DSTCommonFunctions::getMarket();
	bool isLux = ( dstrMarket == MARKET_IDS::LUXEMBOURG  );
	bool bIsPending = isPending();

	GetDlgItem( IDC_EDIT_FUND_NUMBER )->EnableWindow( bShowFundClassControls );
	GetControl( IDC_EDIT_FUND_NUMBER )->Show( bShowFundClassControls );
	ConnectControlToData(IDC_EDIT_FUND_NUMBER, bShowFundClassControls );

	GetDlgItem( IDC_EDIT_FUND_CODE )->EnableWindow( bShowFundClassControls );
	GetControl( IDC_EDIT_FUND_CODE )->Show( bShowFundClassControls );
	ConnectControlToData(IDC_EDIT_FUND_CODE, bShowFundClassControls );

	GetDlgItem( IDC_EDIT_CLASS_CODE )->EnableWindow(bShowFundClassControls);
	GetControl (IDC_EDIT_CLASS_CODE )->Show(bShowFundClassControls);
	ConnectControlToData(IDC_EDIT_CLASS_CODE, bShowFundClassControls );


	GetDlgItem( IDC_EDIT_WKN )->EnableWindow(bShowFundClassControls && isLux && !bIsPending );
	GetControl (IDC_EDIT_WKN )->Show(bShowFundClassControls && isLux && !bIsPending );
	ConnectControlToData(IDC_EDIT_WKN, bShowFundClassControls && isLux && !bIsPending );

	GetDlgItem( IDC_EDIT_ISIN )->EnableWindow(bShowFundClassControls && isLux && !bIsPending );
	GetControl (IDC_EDIT_ISIN )->Show(bShowFundClassControls && isLux && !bIsPending );
	ConnectControlToData(IDC_EDIT_ISIN, bShowFundClassControls && isLux && !bIsPending);

	UINT nShow = SW_HIDE;
	if (bShowFundClassControls) nShow = SW_SHOW;

	GetDlgItem( IDC_STATIC_FUND )->ShowWindow( nShow);
	GetDlgItem( IDC_STATIC_CLASS )->ShowWindow( nShow );
	GetDlgItem( IDC_STATIC_WKN )->ShowWindow( nShow && isLux && !bIsPending );
	GetDlgItem( IDC_STATIC_ISIN )->ShowWindow( nShow && isLux && !bIsPending );
	GetDlgItem( IDC_STATIC_FUND_NAME )->ShowWindow( nShow );

}
//******************************************************************************
void TradeSearchDlg::reInitEditSearch(const DString& strSearchUsing)
{
   BFFieldId idField = BFFieldId::getId(strSearchUsing);
   ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::CRITERIA, idField);

   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
   int length = pProps->getLength();
   if( length > 0 )
      (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE)))->SetMaxCharNum( length );
}

//******************************************************************************
bool TradeSearchDlg::doDisableControl(UINT nID, bool bIsNew)
{
	TRACE_METHOD( CLASSNAME, I_( "doDisableControl" ) );

	//rules :
	//when showing criteria screen all the criteria fields are updateable
	//when showing results, all the controls are read-only
	if( nID == IDC_CMB_USING || nID == IDC_EDT_SEARCH_VALUE || nID == IDC_CMB_NETWORK_ID ||
		nID == IDC_DTP_FROM_DATE || nID == IDC_DTP_TO_DATE   || nID == IDC_DTP_ACCOUNT_DATE || nID == IDC_CMB_EXTERNAL_ID_TYPE )
   {
      return (getCurrentScreenType() != CRITERIA_SCREEN);
   }

   return(false);
}

//******************************************************************************
void TradeSearchDlg::OnRBPending() 
{
	TRACE_METHOD( CLASSNAME, I_( "OnRBPending" ) );
   
   getParent()->setField(this, IFASTBP_PROC::CRITERIA, ifds::Pending, YES, false);
   LoadControl( IDC_CMB_USING );

   ReInitListControl( IDC_LV_RESULTS, ifds::PendingSearchHeadingSet,
      IFASTBP_PROC::PENDING_LIST, LV_RESULTS );
	
}

//******************************************************************************
void TradeSearchDlg::OnRBTransaction() 
{
	TRACE_METHOD( CLASSNAME, I_( "OnRBTransaction" ) );

   getParent()->setField(this, IFASTBP_PROC::CRITERIA, ifds::Pending, NO, false);
   LoadControl( IDC_CMB_USING );

	ReInitListControl( IDC_LV_RESULTS, ifds::TransactionSearchHeadingSet,
      IFASTBP_PROC::TRANSACTION_LIST, LV_RESULTS );
}

//******************************************************************************
bool TradeSearchDlg::GetOverrideItemString( long lSubstituteId,
                            const DString& dstrColumnKey,
                            DString& strOut
                          )
{
   bool bReturn = false;
   strOut = NULL_STRING;

   CString str;
   if( lSubstituteId == ifds::PendingSearchHeadingSet.getId() )
   {
      if( dstrColumnKey == FUND_CODE )
      {
         DString dstrTransType;
         getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, strOut, false);
         getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, dstrTransType, false);

         if (strOut.strip().empty() && DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::ALLOC_ELIG))
         {
            CString strTemp;
            strTemp.LoadString(TXT_SEE_ALLOCATION);
            strOut = strTemp;
            bReturn = true;
         }
      }
   }
   return bReturn;
}

//******************************************************************************
void TradeSearchDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
   if( listControlID == IDC_LV_RESULTS )
   {
      GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(true);
      if( !bIsNewItem && !bIsDummyItem )
      {
         // Check for Message.
         DString MsgExists;
         if( isPending() )
         {
            getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::MsgExists, MsgExists, false);
         }
         else
         {
            getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::MsgExists, MsgExists, false);
         }
         GetDlgItem( IDC_BTN_MESSAGE )->EnableWindow( MsgExists == YES && hasReadPermission( UAF::MSG_SEARCH ) );
      }
   }
}

//******************************************************************************
bool TradeSearchDlg::isPending()
{
   DString strPending;
   getParent()->getField(this, IFASTBP_PROC::CRITERIA, ifds::Pending, strPending, false);
   return (strPending.strip() == YES);
}

//******************************************************************************
void TradeSearchDlg::OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvResults" ) );
   if (GetList(IDC_LV_RESULTS)->GetNextSelection()>=0)
      OnBtnBrowse();
   *pResult = 0;
}

//******************************************************************************
BOOL TradeSearchDlg::PreTranslateMessage( MSG*pMsg )
{
	if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
		DString strSearchType;
		getParent()->getField(this, ifds::SearchType, strSearchType, false);
			
      if( strSearchType.strip() == ACCOUNTNUM && GetFocus()== GetDlgItem( IDC_EDT_SEARCH_VALUE ) )
      {
         PostMessage( WM_LAUNCH_IDENT_ACC );
      }
	  else if( /*strSearchType.strip() == TRADEDATE*/ (strSearchType.strip() == TRADEDATE ||
			strSearchType.strip() == FUNDCLASS) && //shashi
			( GetFocus () == GetDlgItem (IDC_EDIT_FUND_NUMBER) || //one side
           GetFocus () == GetDlgItem (IDC_EDIT_FUND_CODE)   ||
           GetFocus () == GetDlgItem (IDC_EDIT_CLASS_CODE)  ||
           GetFocus () == GetDlgItem (IDC_EDIT_WKN)         ||
           GetFocus () == GetDlgItem (IDC_EDIT_ISIN) ) ) 
		{			
    
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
		}

	}
	return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//********************************************************************************
LRESULT TradeSearchDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter( pFUNDCODE, NULL_STRING );
      setParameter( pCLASSCODE, NULL_STRING );
      setParameter( pFUNDNUMBER, NULL_STRING );
		setParameter( pFUNDWKN, NULL_STRING );
      setParameter( pFUNDISIN, NULL_STRING );

      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDIT_FUND_CODE:
            setParameter( pFUNDCODE, dstrValue );
            break;    
         case IDC_EDIT_FUND_NUMBER:
            setParameter( pFUNDNUMBER, dstrValue );
            break;    
         case IDC_EDIT_CLASS_CODE:
            setParameter( pCLASSCODE, dstrValue );
            break;  
			case IDC_EDIT_WKN:
            setParameter( pFUNDWKN, dstrValue );
            break;    
         case IDC_EDIT_ISIN:
            setParameter( pFUNDISIN, dstrValue );
            break; 
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber, dstrFundISIN, dstrFundWKN;
               getParameter( pFUNDCODE, dstrFundCode );
               getParameter( pCLASSCODE, dstrClassCode );
               getParameter( pFUNDNUMBER, dstrFundNumber );
               getParameter( pFUNDISIN, dstrFundISIN );
               getParameter( pFUNDWKN, dstrFundWKN );

					if( !dstrFundNumber.empty() )
                  getParent()->setField( this, IFASTBP_PROC::CRITERIA, ifds::FundNumber, dstrFundNumber );
               if( !dstrFundCode.empty() )
                  getParent()->setField( this, IFASTBP_PROC::CRITERIA, ifds::FundCode, dstrFundCode );
               if( !dstrClassCode.empty() )
                  getParent()->setField( this, IFASTBP_PROC::CRITERIA, ifds::ClassCode, dstrClassCode );
               if( !dstrFundISIN.empty() )
                  getParent()->setField( this, IFASTBP_PROC::CRITERIA, ifds::FundISIN, dstrFundISIN );
               if( !dstrFundWKN.empty() )
                  getParent()->setField( this, IFASTBP_PROC::CRITERIA, ifds::FundWKN, dstrFundWKN );

					LoadControl( IDC_EDIT_FUND_NUMBER );
               LoadControl( IDC_EDIT_FUND_CODE );
               LoadControl( IDC_EDIT_CLASS_CODE );
               if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
               {
                  LoadControl( IDC_EDIT_ISIN );
                  LoadControl( IDC_EDIT_WKN );
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
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

//******************************************************************************
LRESULT TradeSearchDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );
   //don't allow user to open identify account unless they cleared the account number
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   //don't allow user to open identify account unless they cleared the account number
   CString strAccNum;
  
   CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDT_SEARCH_VALUE));
   pEdit->GetWindowText(strAccNum);

   DString dstAcctNum = NULL_STRING;
   dstAcctNum = (LPCTSTR) strAccNum;
   dstAcctNum.strip().stripLeading('0');
   if( dstAcctNum != NULL_STRING )
      return(0);

   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      eRtn = invokeCommand( getParent(), CMD_BPROC_IDENT_ACC, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrAccountNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
               dstAcctNum.strip();
               bRetVal = SetControlText( IDC_EDT_SEARCH_VALUE, dstrAccountNum );
               pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_SEARCH_VALUE ));
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();

               if( !bRetVal )
               {

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_SEARCH_VALUE ));
                  if( pBC )
                  {
                     if( pBC->IsToolTipVisible() )
                        pBC->ToggleToolTip();

                     pBC->Load();
                  }
               }
               clearParameters( );
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            //Displayerror
            ConditionMessageBox( FRAMEBELOW( ),GETHIGHESTSEVERITY( ) );
            break;
      }
   }
   catch( ConditionException&ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(0);
}

//******************************************************************************
void TradeSearchDlg::OnBtnMessage()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnMessage" ) );

	GetDlgItem(IDC_BTN_MESSAGE)->SetFocus();
	CWaitCursor wait;

   // Set Transaction Number
   DString TransNum;
   if( isPending() )
   {
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, TransNum, true);
   }
   else
   {
      getParent()->getField(this, IFASTBP_PROC::TRANSACTION_LIST, ifds::TransNum, TransNum, true);
   }
   setParameter( MFCAN_IP_PARAM::TRANS_NUM, TransNum );

   // Set Message Type
   setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, I_("TransNum") );

   try
   {
      bool bModal = true;
      E_COMMANDRETURN eRtn = CMD_OK;
      SetMessageStatusBar( IDS_LOADING_MSG );
      eRtn = invokeCommand( getParent(), CMD_BPROC_MSG, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradeSearchDlg.cpp-arc  $
// 
//    Rev 1.29   Jan 16 2012 13:46:10   wp040027
// P0188394_Performance Fees - Trade Search
// 
//    Rev 1.28   Sep 17 2009 11:23:20   wutipong
// IN1809321 - Modify Button disabled for pending trades
// 
//    Rev 1.27   May 07 2007 13:06:10   porteanm
// Incident 867819 - Pass CallFrom = "TradeSearch" when calling TransactionHistory dialog.
// 
//    Rev 1.26   Jun 26 2006 16:58:38   popescu
// Fix the network id trade search
// 
//    Rev 1.25   Dec 29 2005 13:17:56   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.24   Nov 26 2005 16:43:10   porteanm
// PET 1286 FN01 - Bulk Cancellation - default TradeDate to current business date.
// 
//    Rev 1.23   Nov 15 2005 14:36:38   ZHANGCEL
// PET1286 FN01 -- Hide WKN and ISIN for Canada market
// 
//    Rev 1.22   Nov 12 2005 14:10:12   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.21   Nov 10 2005 17:22:02   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.20   Nov 10 2005 15:22:22   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.19   Nov 10 2005 13:25:18   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.18   Nov 08 2005 18:38:14   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.17   Nov 08 2005 16:34:42   porteanm
// PET 1286  FN01 -- TradeDate search for a processed transaction.
// 
//    Rev 1.16   Nov 04 2005 11:12:28   ZHANGCEL
// PET 1286  FN01 -- Add TradeDate search related issue
// 
//    Rev 1.15   Sep 15 2005 15:15:34   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.14   May 24 2005 16:34:30   porteanm
// PET OPC Confirm Reprint - Call Transaction History Dlg as non-Modal.
// 
//    Rev 1.13   Feb 24 2005 11:47:50   hernando
// PET1117 FN66-68 - Added setParameter for the Message Search Type.
// 
//    Rev 1.12   Feb 22 2005 14:51:02   hernando
// PET1117 FN66-68 - Added OnBtnMessage.
// 
//    Rev 1.11   Sep 17 2004 16:08:08   popescu
// PET1046_FN02 -- Trade Search by account enhancement
// 
//    Rev 1.10   Sep 17 2004 15:34:54   ZHANGCEL
// Code lean up -- Create a new name space TRADETYPE
// 
//    Rev 1.9   Sep 15 2004 16:25:10   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.8   Sep 15 2004 15:03:52   ZHANGCEL
// Code clean up -- grouping Transtype to ALLOC_ELIG
// 
//    Rev 1.7   Sep 07 2004 15:40:48   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.6   Sep 07 2004 10:15:54   ZHANGCEL
// PET1094 -- FN8, Added AdminFee for the trade searching.
// 
//    Rev 1.5   May 11 2004 11:33:24   ZHANGCEL
// PET1046_FN02 -- Trade Search by account enhancement
// 
//    Rev 1.4   Mar 21 2003 18:41:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Mar 12 2003 13:47:20   HERNANDO
// Checked in for Robert.
// 
//    Rev 1.2   Mar 07 2003 15:54:32   KOVACSRO
// 1. TRADE_SEARCH UAF is ready.
// 2. Fixed 'see allocations' display.
// 3. Other cosmethic changes.
// 
//    Rev 1.1   Mar 04 2003 17:09:44   KOVACSRO
// some cleanup during unit testing.
// 
//    Rev 1.0   Mar 03 2003 09:52:52   KOVACSRO
// Initial revision.

*/