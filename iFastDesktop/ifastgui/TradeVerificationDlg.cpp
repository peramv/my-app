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
// ^FILE   : TradeVerificationDlg.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 21-Jul-2014
//
// ^CLASS    : TradeVerificationDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif
#ifndef TradeVerificationDlg_H
   #include "TradeVerificationDlg.h"
#endif
#ifndef TRADEVERIFICATIONSEARCHPROCESSINCLUDES_H
    #include <ifastbp\TradeVerificationsearchprocessincludes.h>
#endif
#include <ifastbp\TradeVerificationProcess.hpp>
//#include <ifastbp\transcancelprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcommonfunction.hpp>
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_VERIFICATION_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradeVerificationDlg > dlgCreator( CMD_GUI_TRADE_VERIFICATION_SEARCH );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
//special Message to Handle the grid selection inoder to have the errro message populated..
#define UM_LOAD_ERROR_MSG      WM_APP + 1500

namespace
{
    const I_CHAR * const YES               = I_( "Y" );
    const I_CHAR * const NO                = I_( "N" );
    const I_CHAR * const CLASSNAME         = I_( "TradeVerificationDlg" );
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
	const I_CHAR * const SPONSORCODE       = I_( "SponsorCode" );
	const I_CHAR * const PLATFORM          = I_( "Platform" );
    //transactions
    const I_CHAR *pALLFUND                 = I_( "AllFundMode" );
    const I_CHAR *pACCOUNTNUM              = I_( "AccountNum" );
    const I_CHAR *pTRANSID                 = I_( "TransId" );
    const I_CHAR *pFUNDCODE                = I_( "FundCode" );
    const I_CHAR *pCLASSCODE               = I_( "ClassCode" );
    const I_CHAR *pNUMENTRY                = I_( "NumEntry" );
    const I_CHAR *pPENDING                 = I_( "Pending" );
    const I_CHAR *pTRANSTYPE               = I_( "TransType" );
    const I_CHAR *pTRANSNUM                = I_( "TransNum" );
    const I_CHAR *pTRADEDATE               = I_( "TradeDate" );
    const I_CHAR *pINQUIRYONLY             = I_( "InquiryOnly" );
    const I_CHAR *pFUNDNUMBER              = I_( "FundNumber" );
    const I_CHAR *pFUNDWKN                 = I_( "FundWKN" );
    const I_CHAR *pFUNDISIN                = I_( "FundISIN" );
    const I_CHAR * const IS_NEWSEARCH      = I_( "IsNewSearch" );
    const I_CHAR * const ALL_TRADES        = I_("All");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
    extern CLASS_IMPORT const BFTextFieldId VerifyTrade;
    extern CLASS_IMPORT const BFTextFieldId DeleteTrade;
    extern CLASS_IMPORT const BFTextFieldId TradeVerificationSearchHeading;
    extern CLASS_IMPORT const BFTextFieldId FundNumber;
    extern CLASS_IMPORT const BFTextFieldId FundName;
    extern CLASS_IMPORT const BFTextFieldId FundWKN;
    extern CLASS_IMPORT const BFTextFieldId FundISIN;
    extern CLASS_IMPORT const BFTextFieldId AltAccount;
}

namespace CND
{//Conditionsused
    extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const TRADE_VERIFICATION;
}
namespace COLOUMKEY
{
    const I_CHAR * const TRANSTYPE     =   _T("TransType");
    const I_CHAR * const VERIFYTRADE   =   _T("VerifyTrade");
    const I_CHAR * const DELETETRADE   =   _T("DeleteTrade");
    const I_CHAR * const ACCTNUM       =   _T("rxAcctNum");
    const I_CHAR * const TRANSNUM      =   _T("TransNum");
    const I_CHAR * const FUND          =   _T("FundCode");
    const I_CHAR * const CLASS         =   _T("ClassCode");
    const I_CHAR * const TRADEDATE     =   _T("TradeDate");
    const I_CHAR * const AMOUNTTYPE    =   _T("AmountType");
    const I_CHAR * const NETWORK_ID    =   _T("NetworkID");
	const I_CHAR * const SPONSORCODE   =   _T("SponsorCode");
	const I_CHAR * const FUNDGROUP     =   _T("FundGroup");
    const I_CHAR * const PLATFORM      =   _T("Platform");
	const I_CHAR * const PRICETYPE   =   _T("PriceType");
	const I_CHAR * const PRICEINTYPE   =   _T("PriceInCode");
	const I_CHAR * const WAIVEGATINGIND   =   _T("GateOverrideIndicator");

}

const UINT criteriaFields[]=
{
  IDC_CMB_USING,
  IDC_EDT_SEARCH_VALUE,
  IDC_CMB_EXTERNAL_ID_TYPE,
  IDC_CMB_NETWORK_ID,
  IDC_EDIT_FUND_NUMBER,
  IDC_EDIT_FUND_CODE,
  IDC_EDIT_CLASS_CODE,
  IDC_EDIT_WKN,
  IDC_EDIT_ISIN,
  IDC_EDIT_ACCOUNT,
  IDC_CMB_TRANS_TYPE_FC,
  IDC_CMB_PLATFORM_TYPE,
};
static const int numCriteriaFields = sizeof( criteriaFields ) / sizeof( UINT );

//******************************************************************************
TradeVerificationDlg::TradeVerificationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TradeVerificationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_strScreenType(NULL_STRING), _bTradeVerificationCtrlsAdded(false), m_bIsFromGridLoading(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TradeVerificationDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
TradeVerificationDlg::~TradeVerificationDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void TradeVerificationDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(TradeVerificationDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
   DDX_Check(pDX, IDC_CHK_VERIFY_ALL, m_bVerifyAll);
   DDX_Check(pDX, IDC_CHK_DELETE_ALL, m_bDeleteAll);
}

/////////////////////////////////////////////////////////////////////////////
// TradeVerificationDlg message handlers
//******************************************************************************
BEGIN_MESSAGE_MAP(TradeVerificationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradeVerificationDlg)
   ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
   ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
   ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
   ON_MESSAGE( WM_LAUNCH_IDENT_ACC,OpenIdentifyAccountsDlg )
   ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
   ON_BN_CLICKED(IDC_BUTTON_VERIF_TARDE_DETAILS, OnBtnDetails)
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_CHK_VERIFY_ALL, OnChkVerifyAll)
   ON_BN_CLICKED(IDC_CHK_DELETE_ALL, OnChkDeleteAll)
   ON_MESSAGE( UM_LOAD_ERROR_MSG, OnGridSelectionChanged)
   //ON_NOTIFY(NM_DBLCLK, IDC_LV_RESULTS, OnDblclkLvResults)

END_MESSAGE_MAP()
//******************************************************************************
void TradeVerificationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   CWaitCursor wait;
   SetUserAccesFunctionCode(UAF::TRADE_VERIFICATION);
   addControls();
   showCriteria();
   GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( false );
   GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( false ); 
   GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );
   GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
   CheckDlgButton( IDC_CHK_VERIFY_ALL, false );
   CheckDlgButton( IDC_CHK_DELETE_ALL, false );
}

//******************************************************************************
SEVERITY TradeVerificationDlg::doInit()
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doInit" ) );  

   SEVERITY sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void TradeVerificationDlg::addControls( )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "addControls" ) );   

	//controls   
    AddControl( CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::CRITERIA, ifds::SearchType,
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
    AddControl( CTRL_COMBO, IDC_CMB_NETWORK_ID, IFASTBP_PROC::CRITERIA, ifds::NetworkID   , 
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
	AddControl( CTRL_EDIT, IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::CRITERIA, ifds::TransNum, 
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
	AddControl( CTRL_STATIC, IDC_STATIC_FUND_NAME, IFASTBP_PROC::CRITERIA, ifds::FundName,
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_EDIT, IDC_EDIT_ACCOUNT, IFASTBP_PROC::CRITERIA, ifds::AccountNum, 
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
	AddControl( CTRL_COMBO, IDC_CMB_TRANS_TYPE_FC, IFASTBP_PROC::CRITERIA, ifds::TradesSearchTransType,
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
    AddControl( CTRL_COMBO, IDC_CMB_EXTERNAL_ID_TYPE, IFASTBP_PROC::CRITERIA, ifds::ExternalIdType,
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 
	AddControl( CTRL_COMBO, IDC_CMB_PLATFORM_TYPE, IFASTBP_PROC::CRITERIA, ifds::Platform, 
		        CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 
   
	DSTEdit* pEditAct = dynamic_cast<DSTEdit*>(GetControl(IDC_EDIT_ACCOUNT));
	pEditAct->SetAllDigits(true);
    DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE));
    pEdit->SetAllDigits(true);
}
//******************************************************************************
bool TradeVerificationDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doRefresh" ) );

   return(true);
}

//******************************************************************************
void TradeVerificationDlg::OnBtnReset() 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnReset" ) );  
     
    setParameter(IS_NEWSEARCH, NO);	
	CWaitCursor wait;
    getParent()->reset(this);
    //clear grid first as some controls are enabled based on the rows in the grid.
    DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
    if( ghwnd )
    {
        ghwnd->ClearGrid();
        ghwnd->ShowWindow(SW_HIDE);
        ghwnd->SetSorting(true);
    }  
	ReregisterObservers();
    ConnectControlsToData(IDC_LV_RESULTS, false);
	showCriteria();
	GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );
    GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( false );
    GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( false );
    GetDlgItem(IDC_EDT_MESSAGE)->EnableWindow(false);
    GetDlgItem(IDC_EDT_MESSAGE)->SetWindowText(NULL_STRING);
    CheckDlgButton( IDC_CHK_VERIFY_ALL, false );
    CheckDlgButton( IDC_CHK_DELETE_ALL, false );
    GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( false );
    GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( false ); 
    setSerachCriteriaReadOnly(false); 
}
//******************************************************************************
void TradeVerificationDlg::OnBtnSearch() 
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

    setParameter(IS_NEWSEARCH, YES);
    setGridUpdated (false);
    DString strValidCriteria, strPending;
	getParent()->getField(this, ifds::ValidTradeCriteria, strValidCriteria, false);
	if (strValidCriteria == NO)
	{
	  CString strValidCriteria;
      DString strSearchType;
      LoadControls();
      setSerachCriteriaReadOnly(false);
	  strValidCriteria.LoadString(TXT_VALID_CRITERIA);
	  //AfxMessageBox(strValidCriteria, MB_OK | MB_ICONSTOP); //??
	  getParent()->getField(this, ifds::SearchType, strSearchType, false);
      if (strSearchType.strip() == NETWORK)
		GetDlgItem(IDC_CMB_NETWORK_ID)->SetFocus();
	  else if( strSearchType.strip() == FUNDCLASS )
	  	GetDlgItem(IDC_EDIT_FUND_CODE)->SetFocus();
	  else
		GetDlgItem(IDC_EDT_SEARCH_VALUE)->SetFocus();      
	  return;
	}
	CWaitCursor wait;
    SetMessageStatusBar( TXT_SEARCHING );
    SEVERITY sev = NO_SEVERITY;
    sev = getParent()->performSearch(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, SEARCH_START );
    if (sev>WARNING)
    {
      setSerachCriteriaReadOnly(false);
      SetMessageStatusBar( NULL_STRING );
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
    }
   showResults();
   SetMessageStatusBar( NULL_STRING );
   setParameter(IS_NEWSEARCH, NO); 
   GetDlgItem( IDC_BTN_RESET )->EnableWindow( true );  
   setSerachCriteriaReadOnly(true);   
}

//******************************************************************************
void TradeVerificationDlg::OnBtnDetails() 
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBrowse" ) );

	GetDlgItem(IDC_BUTTON_VERIF_TARDE_DETAILS)->SetFocus();
	CWaitCursor wait;
    DString strAccNum, strFund, strClass, strAllFundMode(I_("N")), strTransId,
       strTransNum, strTradeDate, strTransType;
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::rxAcctNum, strAccNum, true);
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::rxFundCode, strFund, true);
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::rxClassCode, strClass, true);
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::TradeDate, strTradeDate, true);
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::TransType, strTransType, true);
    getParent()->getField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::TransNum, strTransNum, true);
    setParameter(pACCOUNTNUM, strAccNum);
    setParameter(pFUNDCODE, strFund);
    setParameter(pCLASSCODE, strClass);
    setParameter(pTRANSTYPE, strTransType);
    setParameter(pTRANSNUM, strTransNum);
    setParameter(pTRADEDATE, strTradeDate);
    setParameter(pPENDING, YES);
    setParameter(pALLFUND, YES);
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
void TradeVerificationDlg::showCriteria()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "TradeVerificationDlg" ) );

	m_strScreenType = CRITERIA_SCREEN;
	GetDlgItem(IDC_RESULTS_FRAME)->ShowWindow(SW_HIDE);
	GetControl(IDC_CMB_USING)->Show(true);
	ConnectControlsToData();
	LoadControls();
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_VERIF_TARDE_DETAILS)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
}
//******************************************************************************
void TradeVerificationDlg::showResults()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "showResults" ) );

    bool bEnable;
    //below are the controls based on the search result....
    if(! _bTradeVerificationCtrlsAdded )
    {
        AddGrid   ( CLASSNAME, IDC_LV_RESULTS, I_("TradeVerificationList"),
                    IFASTBP_PROC::TRADE_VERIFICATION_LIST, IDC_LV_RESULTS, ifds::TradeVerificationSearchHeading,
                    ifds::NullFieldId,DSTGridWnd::GRID_TYPE::LIST );
        AddControl( CTRL_CHECKBOX,  IDC_CHK_VERIFY_ALL, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyAll,
		            CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE ); 
        AddControl( CTRL_CHECKBOX,  IDC_CHK_DELETE_ALL, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteAll,
		            CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE );              
       _bTradeVerificationCtrlsAdded = true;
    }
	m_strScreenType = RESULTS_SCREEN;
    ConnectControlsToData();
    ConnectControlsToData(IDC_LV_RESULTS);     
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(false);
	//static controls, frames (group boxes)
	GetDlgItem(IDC_RESULTS_FRAME)->ShowWindow(SW_SHOW);    
    DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
    if (ghwnd)
    {
        m_bIsFromGridLoading = true;
        ghwnd->reLoadGrid ();
        ghwnd->ShowWindow(SW_SHOW);
        bEnable = ghwnd->GetRowCount() > 0;
        ghwnd->SetSorting(true);
        m_bIsFromGridLoading = false;
    }
    setGridUpdated(true);   
    enableSearchResultControls();
}
//******************************************************************************
void TradeVerificationDlg::ControlUpdated( UINT controlID, const DString &strValue )
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
			GetDlgItem( IDC_TXT_EXTERNAL_ID_TYPE )->ShowWindow( EXTERNAL_ID == strValue );
			GetDlgItem( IDC_CMB_EXTERNAL_ID_TYPE )->ShowWindow( EXTERNAL_ID == strValue );
			GetDlgItem( IDC_TXT_EXTERNAL_ID_TYPE )->ShowWindow( EXTERNAL_ID == strValue );
			GetDlgItem( IDC_CMB_EXTERNAL_ID_TYPE )->EnableWindow( EXTERNAL_ID == strValue );
			ConnectControlToData( IDC_CMB_EXTERNAL_ID_TYPE, false );
			showFundClassSearchControls( FUNDCLASS == strValue );
            showTransTypeSearchControls(TRANSTYPE == strValue);
			showPlatformSet(strValue==PLATFORM);
			enableFundClassControls( TRADEDATE == strValue || FUNDCLASS == strValue );
		    GetDlgItem (IDC_EDT_SEARCH_VALUE)->EnableWindow ( NETWORK!= strValue && FUNDCLASS != strValue &&
                                                              ALL_TRADES != strValue && TRANSTYPE  != strValue &&
															  PLATFORM != strValue); 
            GetControl (IDC_EDT_SEARCH_VALUE)->Show ( NETWORK != strValue &&  FUNDCLASS != strValue &&
                                                     ALL_TRADES != strValue && TRANSTYPE  != strValue && 
													 PLATFORM != strValue );
			if ( NETWORK == strValue )
               LoadControl(IDC_CMB_NETWORK_ID);
            else if(TRANSTYPE == strValue)
               LoadControl(IDC_CMB_TRANS_TYPE_FC);
			else if( PLATFORM == strValue)
				LoadControl(IDC_CMB_PLATFORM_TYPE);
            else if(ALL_TRADES == strValue)
               break;//load no further controlls  
            else
            {		
				//reinit IDC_EDT_SEARCH_VALUE with the right field
				if ( EXTERNAL_ID == strValue)
					reInitEditSearch( I_( "ExternalId" ) );
				else               
					reInitEditSearch(strValue);				
				if ( FUNDCLASS == strValue )
					LoadControl( IDC_CMB_TRANS_TYPE_FC );
                //set all digits if it is transaction number search
                DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE));
                if ( TRANSNUM == strValue || WIREORD == strValue || ACCOUNTNUM  == strValue)//or it should be numeric for all search types?
                  pEdit->SetAllDigits(true);
                else
                  pEdit->SetAllDigits(false);
                 //connect to data and re-load IDC_EDT_SEARCH_VALUE
                  ConnectControlToData(IDC_EDT_SEARCH_VALUE, true );
                  LoadControl(IDC_EDT_SEARCH_VALUE);
			   if(EXTERNAL_ID == strValue)
			   {											
					ConnectControlToData( IDC_CMB_EXTERNAL_ID_TYPE, true );
					LoadControl( IDC_CMB_EXTERNAL_ID_TYPE );
			   }
			} 
           setSerachCriteriaReadOnly(false);            
	      }
         break;
		case IDC_EDIT_FUND_NUMBER:
         {
				if ( TRADEDATE == strSearchType || FUNDCLASS  == strSearchType)
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
				if ( TRADEDATE == strSearchType || FUNDCLASS  == strSearchType)
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
				if ( TRADEDATE == strSearchType || FUNDCLASS  == strSearchType)
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
				if ( TRADEDATE == strSearchType || FUNDCLASS  == strSearchType)
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
				if ( TRADEDATE == strSearchType || FUNDCLASS  == strSearchType)
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

   enableSearchResultControls();
}
//******************************************************************************
void TradeVerificationDlg::enableSearchResultControls()
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "enableSearchResultControls" ) );  

  bool bEnable = false;
  DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
  if (ghwnd)
  {
    bEnable = ghwnd->GetRowCount() > 0;
    GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( hasUpdatePermission( UAF::TRADE_VERIFICATION ) &&
                                                    bEnable );
    GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( hasUpdatePermission( UAF::TRADE_VERIFICATION ) &&
                                                    bEnable );
    GetDlgItem(IDC_BUTTON_VERIF_TARDE_DETAILS)->EnableWindow(bEnable);  
    GetDlgItem(IDC_EDT_MESSAGE)->EnableWindow(bEnable);
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST ) );
}
//******************************************************************************
void TradeVerificationDlg::showNetworkControls(bool bShowNetwork)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "showNetworkControls" ) );  

   GetDlgItem(IDC_CMB_NETWORK_ID)->EnableWindow(bShowNetwork);
   GetControl(IDC_CMB_NETWORK_ID)->Show(bShowNetwork);
   UINT nShow = SW_HIDE;
   if (bShowNetwork) nShow = SW_SHOW;
}
//******************************************************************************
void TradeVerificationDlg::showFundClassSearchControls(bool bShowFundClassSearch)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "showFundClassSearchControls" ) );  

	GetDlgItem( IDC_EDIT_ACCOUNT )->EnableWindow( bShowFundClassSearch );
	GetDlgItem( IDC_EDIT_ACCOUNT )->ShowWindow( bShowFundClassSearch );
	ConnectControlToData(IDC_EDIT_ACCOUNT, bShowFundClassSearch );
	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->EnableWindow( bShowFundClassSearch );
	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->ShowWindow( bShowFundClassSearch );
	ConnectControlToData(IDC_CMB_TRANS_TYPE_FC, bShowFundClassSearch );
	UINT nShow = SW_HIDE;
    if (bShowFundClassSearch) nShow = SW_SHOW;
	GetDlgItem( IDC_STATIC_ACCOUNT )->ShowWindow( nShow);
	GetDlgItem( IDC_STATIC_TRANS_TYPE_FC )->ShowWindow( nShow );	 
}
//******************************************************************************
void TradeVerificationDlg::showTransTypeSearchControls(bool bShowFundClassSearch)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "showTransTypeSearchControls" ) );  

	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->EnableWindow( bShowFundClassSearch );
	GetDlgItem( IDC_CMB_TRANS_TYPE_FC )->ShowWindow( bShowFundClassSearch );
	ConnectControlToData(IDC_CMB_TRANS_TYPE_FC, bShowFundClassSearch );
	UINT nShow = SW_HIDE;
    if (bShowFundClassSearch) nShow = SW_SHOW;
	GetDlgItem( IDC_STATIC_TRANS_TYPE_FC )->ShowWindow( nShow );	 
}
//******************************************************************************
void TradeVerificationDlg::enableFundClassControls(bool bShowFundClassControls)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "enableFundClassControls" ) ); 
    
	DString dstrMarket = DSTCommonFunctions::getMarket();
	bool isLux = ( dstrMarket == MARKET_IDS::LUXEMBOURG  );
	GetDlgItem( IDC_EDIT_FUND_NUMBER )->EnableWindow( bShowFundClassControls );
	GetControl( IDC_EDIT_FUND_NUMBER )->Show( bShowFundClassControls );
	ConnectControlToData(IDC_EDIT_FUND_NUMBER, bShowFundClassControls );
	GetDlgItem( IDC_EDIT_FUND_CODE )->EnableWindow( bShowFundClassControls );
	GetControl( IDC_EDIT_FUND_CODE )->Show( bShowFundClassControls );
	ConnectControlToData(IDC_EDIT_FUND_CODE, bShowFundClassControls );
	GetDlgItem( IDC_EDIT_CLASS_CODE )->EnableWindow(bShowFundClassControls);
	GetControl (IDC_EDIT_CLASS_CODE )->Show(bShowFundClassControls);
	ConnectControlToData(IDC_EDIT_CLASS_CODE, bShowFundClassControls );
	GetDlgItem( IDC_EDIT_WKN )->EnableWindow(bShowFundClassControls && isLux );
	GetControl (IDC_EDIT_WKN )->Show(bShowFundClassControls && isLux );
	ConnectControlToData(IDC_EDIT_WKN, bShowFundClassControls && isLux );
	GetDlgItem( IDC_EDIT_ISIN )->EnableWindow(bShowFundClassControls && isLux  );
	GetControl (IDC_EDIT_ISIN )->Show(bShowFundClassControls && isLux   );
	ConnectControlToData(IDC_EDIT_ISIN, bShowFundClassControls && isLux );

	UINT nShow = SW_HIDE;
	if (bShowFundClassControls) nShow = SW_SHOW;

	GetDlgItem( IDC_STATIC_FUND )->ShowWindow( nShow);
	GetDlgItem( IDC_STATIC_CLASS )->ShowWindow( nShow );
	GetDlgItem( IDC_STATIC_WKN )->ShowWindow( nShow && isLux );
	GetDlgItem( IDC_STATIC_ISIN )->ShowWindow( nShow && isLux);
	GetDlgItem( IDC_STATIC_FUND_NAME )->ShowWindow( nShow );

}
//******************************************************************************
void TradeVerificationDlg::reInitEditSearch(const DString& strSearchUsing)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "TradeVerificationDlg" ) ); 

   BFFieldId idField = BFFieldId::getId(strSearchUsing);
   ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::CRITERIA, idField);
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
   int length = pProps->getLength();
   if( length > 0 )
      (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_SEARCH_VALUE)))->SetMaxCharNum( length );
   GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( false );
   GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( false );
}

//******************************************************************************
bool TradeVerificationDlg::doDisableControl(UINT nID, bool bIsNew)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doDisableControl" ) );

	//rules :
	//when showing criteria screen all the criteria fields are updateable
	//when showing results, all the controls are read-only
	if( IDC_CMB_USING == nID || IDC_EDT_SEARCH_VALUE  == nID || IDC_CMB_NETWORK_ID == nID  ||
        IDC_CMB_EXTERNAL_ID_TYPE == nID  )
   {
      return (getCurrentScreenType() != CRITERIA_SCREEN);
   }

   return(false);
}

//******************************************************************************
void TradeVerificationDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );

   GetDlgItem(IDC_BTN_MORE)->SetFocus();   CWaitCursor wait;

   SEVERITY sev = NO_SEVERITY;
   sev = getParent()->performSearch(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, SEARCH_NEXT_BLOCK );
   if (sev>WARNING)
   {
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }
   showResults();
   CheckDlgButton( IDC_CHK_DELETE_ALL, false );
   CheckDlgButton( IDC_CHK_VERIFY_ALL, false );
}
/*********************************************************************************************************/
bool TradeVerificationDlg::GetCellValue( UINT ctrlId,
                                        const DString &rowKey,
                                        const DString &colKey,
                                        DString &dstrOut,
                                        bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "GetCellValue" ) ); 
   bool bRet = false;
   if( ctrlId == IDC_LV_RESULTS )
   {
     if( COLOUMKEY::DELETETRADE == colKey )
      {
         getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteTrade, dstrOut );
         bRet = true;
      }
      else if( COLOUMKEY::VERIFYTRADE == colKey )
      {
         getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyTrade, dstrOut );
         bRet = true;
      }
      if( !m_bIsFromGridLoading ) //work aroud to set the erroe message if it is a selection change using the arrow key
      {
         DString dstrWarnMessage = NULL_STRING;
         getParent()->getField( this, IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, ifds::ErrMsg, dstrWarnMessage, false);
         CWnd *rwin = GetDlgItem(IDC_EDT_MESSAGE);
         rwin->SetWindowText(dstrWarnMessage.c_str());
      }
   }
   return(bRet);
}
//******************************************************************************
void TradeVerificationDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "DoListItemChanged" ) ); 

   if( listControlID == IDC_LV_RESULTS )
   {
      GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(true);
      if( !bIsNewItem && !bIsDummyItem )
      {
         // Check for Message.
          DString dstrWarnMessage = NULL_STRING;
          getParent()->getField( this, IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, ifds::ErrMsg, dstrWarnMessage, false);
          CWnd *rwin = GetDlgItem(IDC_EDT_MESSAGE);
          rwin->SetWindowText(dstrWarnMessage.c_str());
          DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
          enableSearchResultControls();
      }
   }
}

//******************************************************************************
BOOL TradeVerificationDlg::PreTranslateMessage( MSG*pMsg )
{

  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "PreTranslateMessage" ) ); 

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
   if(( WM_LBUTTONDOWN == pMsg->message || WM_LBUTTONUP   ==  pMsg->message ||
        WM_LBUTTONDBLCLK == pMsg->message ) &&  GetFocus() == GetDlgItem( IDC_LV_RESULTS ))
    {
      PostMessage(UM_LOAD_ERROR_MSG,  pMsg->wParam, pMsg->lParam );
    }
	return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//********************************************************************************
LRESULT TradeVerificationDlg::OpenFundClassListDlg( WPARAM, LPARAM )
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
LRESULT TradeVerificationDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
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

//********************************************************************************
void TradeVerificationDlg::OnChkVerifyAll()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnChkVerifyAll" ) ); 

   UpdateData();
   CheckDlgButton(IDC_CHK_DELETE_ALL, false);
   DString dstrVerifyAll = NULL_STRING;
   if(m_bVerifyAll ) dstrVerifyAll = YES;
   getParent()->setField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteAll, NULL_STRING , false);
   getParent()->setField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyAll, dstrVerifyAll , false);
   GetDlgItem( IDC_CHK_DELETE_ALL )->EnableWindow( hasUpdatePermission( UAF::TRADE_VERIFICATION ) );   
   DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
   if( ghwnd )
     ghwnd->reLoadGrid();
}
//********************************************************************************
void TradeVerificationDlg::OnChkDeleteAll()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnChkDeleteAll" ) ); 

   UpdateData();
   DString dstrDeleteAll = NULL_STRING;
   if(m_bDeleteAll ) dstrDeleteAll = YES;
   getParent()->setField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyAll, NULL_STRING , false);
   getParent()->setField(this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteAll, dstrDeleteAll, false);
   CheckDlgButton(IDC_CHK_VERIFY_ALL, false);
   GetDlgItem( IDC_CHK_VERIFY_ALL )->EnableWindow( hasUpdatePermission( UAF::TRADE_VERIFICATION ) );
   DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_LV_RESULTS) );
   if( ghwnd )
      ghwnd->reLoadGrid();
}
//***************************************************************************************
LRESULT TradeVerificationDlg::OnGridSelectionChanged( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnGridSelectionChanged" ) ); 
  // Check for Message.
  try
  {
     DString dstrWarnMessage = NULL_STRING;
     CWnd *rwin = GetDlgItem(IDC_EDT_MESSAGE);
     getParent()->getField( this, IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, ifds::ErrMsg, dstrWarnMessage, false);
     CString cstrMessage = dstrWarnMessage.c_str();
     cstrMessage.Replace(I_("\n"), _T("\r\n")) ;    
     rwin->SetWindowText(cstrMessage);
     UpdateData();
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
//***************************************************************************************
void TradeVerificationDlg::GetCellProperties( UINT ctrlId, 
                                       const DString &rowKey, 
                                       const DString &colKey, 
                                       BFContainerId& idContainer,
                                       BFFieldId &idField,
                                       DString& listItemKey,
                                       int& nCellState,
                                       UINT& cellCtrlType, 
                                       int& nCtrlInitMode,
                                       BFFieldId &idSubstitution,
                                       DString& comboList, 
                                       DString& mask, 
                                       int& nComboSortingMode ,
                                       DString& dstrAllowedChar )	
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "GetCellProperties" ) ); 

   dstrAllowedChar = NULL_STRING;

   if( COLOUMKEY::VERIFYTRADE == colKey )
   {
      idContainer       = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField           = ifds::VerifyTrade;
      nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
      cellCtrlType      = GX_IDS_CTRL_CHECKBOX3D;
      nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
      idSubstitution    = ifds::VerifyTrade;
   }
   else if( COLOUMKEY::DELETETRADE == colKey )
   {
      idContainer       = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField           = ifds::DeleteTrade;
      nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
      cellCtrlType      = GX_IDS_CTRL_CHECKBOX3D;    
      nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
      idSubstitution    = ifds::DeleteTrade;

   }
   else if( COLOUMKEY::ACCTNUM  == colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::rxAcctNum;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }

   else if( COLOUMKEY::TRANSTYPE  == colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::TransType;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::TRANSNUM  ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::TransNum;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }

   else if( COLOUMKEY::FUND  ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::rxFundCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::CLASS  ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::rxClassCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::TRADEDATE  ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::TradeDate;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::AMOUNTTYPE ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::AmountType;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::NETWORK_ID  ==  colKey )
   {
      idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
      idField     = ifds::NetworkID;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( COLOUMKEY::SPONSORCODE == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::SponsorCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;  
   }
   else if( COLOUMKEY::FUNDGROUP == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::FundGroup;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;  
   }
   else if( COLOUMKEY::PLATFORM == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::Platform;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;  
   }
   else if( COLOUMKEY::PRICETYPE == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::PricingCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC; 
   }
   else if( COLOUMKEY::PRICEINTYPE == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::PriceInCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC; 
   }
   else if( COLOUMKEY::WAIVEGATINGIND == colKey )
   {
	  idContainer = IFASTBP_PROC::TRADE_VERIFICATION_LIST ;
	  idField     = ifds::GateOverrideIndicator;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC; 
   }

 }
//******************************************************************************
bool TradeVerificationDlg::PreOk()
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "PreOk" ) ); 
   //NO need of extra messages as alreday teh user knows by looking into teh grid for teh check boxes..
   return(true);
}

//*******************************************************************************
bool TradeVerificationDlg::OnGridSetCellValue( UINT ctrlId,
                                        const DString &rowKey,
                                        const DString &colKey,
                                        const DString &strIn)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnGridSetCellValue" ) ); 
   if( ctrlId == IDC_LV_RESULTS )
   {
      DString dstrVerify, dstrDelete, dstrVerifyPerm, dstrDeletePerm;
      bool bVerifyPerm, bDeletePerm;
      getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeletePerm, dstrDeletePerm );
      getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyPerm, dstrVerifyPerm );
      bVerifyPerm = ( dstrVerifyPerm == I_("Y") || 
                     ( dstrVerifyPerm != I_("0") && dstrVerifyPerm != I_("3")));
      bDeletePerm = ( dstrDeletePerm == I_("Y") || 
                     ( dstrDeletePerm != I_("0") && dstrDeletePerm != I_("3")));
      if( ( COLOUMKEY::DELETETRADE == colKey ) && bDeletePerm ) // if systematically selected
      {
         getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteTrade, dstrDelete );
         //getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyTrade, dstrVerify );
         if( m_bVerifyAll )
             CheckDlgButton( IDC_CHK_VERIFY_ALL, BST_UNCHECKED  );
         if( m_bDeleteAll )
             CheckDlgButton( IDC_CHK_DELETE_ALL, dstrDelete == YES );
      }
      if( ( COLOUMKEY::VERIFYTRADE == colKey) && bVerifyPerm ) //if systematically selected
      {
         //getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::DeleteTrade, dstrDelete );
         getParent()->getField( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST, ifds::VerifyTrade, dstrVerify );
         if( m_bDeleteAll )         
             CheckDlgButton( IDC_CHK_DELETE_ALL, BST_UNCHECKED );
         if( m_bVerifyAll )
            CheckDlgButton( IDC_CHK_VERIFY_ALL, dstrVerify == YES );
      }
   }
   return(false); 

}
//*******************************************************************************
void TradeVerificationDlg::setSerachCriteriaReadOnly( bool bReadOnly )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "setSerachCriteriaReadOnly" ) );
  
   for( int i=0; i<numCriteriaFields; i++ )
        GetDlgItem(criteriaFields[i])->EnableWindow( !bReadOnly );
   if( bReadOnly )
      GetDlgItem( IDC_BTN_RESET )->SetFocus();
   else
      GetDlgItem( IDC_BTN_SEARCH )->SetFocus();
}
//******************************************************************************
void TradeVerificationDlg::showPlatformSet(bool bShowPlatform)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "showPlatformSet" ) );  

   GetDlgItem(IDC_CMB_PLATFORM_TYPE)->EnableWindow(bShowPlatform);
   GetControl(IDC_CMB_PLATFORM_TYPE)->Show(bShowPlatform);
   ConnectControlToData(IDC_CMB_PLATFORM_TYPE, bShowPlatform );
   UINT nShow = SW_HIDE;
   if (bShowPlatform) nShow = SW_SHOW;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradeVerificationDlg.cpp-arc  $ 
//    Rev 1.0  July 21 2014
// Initial revision.
*/