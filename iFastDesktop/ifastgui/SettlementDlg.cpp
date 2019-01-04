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
// ^FILE   : SettlementDlg.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ----------------------------------------------------------
//
// ^CLASS    : SettlementDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for settlement dialog
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "settlementdlg.h"
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\settlementprocessincludes.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstedit.h>
#include <ifastbp\addressprocessincludes.h>
#include <ifastcbo\financialinstitution.hpp>
#include <bfproc\abstractprocess.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTELEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SettlementDlg > dlgCreator( CMD_GUI_SETTELEMENT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "SettlementDlg" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );
   I_CHAR * const DISPLAY_SETTLE_ONLY           = I_("DisplaySettleOnly");
   I_CHAR * const DISPLAY_ALL                   = I_("DisplayAll");
   I_CHAR * const RESET_ITEM                    = I_("Reset");

   const I_CHAR * const FUND_CODE               = I_( "FundCode" );
   const I_CHAR * const BROKER_CODE             = I_( "BrokerCode" );
   const UINT SETTLEMENT_SEARCH                 = 1001;
   const I_CHAR * const ONBTNBANK               = I_( "OnBtnBank" );
   const I_CHAR * const SPACE_STRING            = I_( " " );
   const I_CHAR * const USER_ACCESS_CODE        = I_( "UserAccessCode" );
   const I_CHAR * const DIRECT_DEPST_REDEMPTION = I_( "D1" );
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
}

struct _BankLabel
{
   const I_CHAR* _bankTypeId;
   UINT  BankTypeDesc;      
};

const struct _BankLabel BankLabels[] = {
   I_("01"), IDS_LBL_ABA_NBR,
   I_("02"), IDS_LBL_NBR,
   I_("03"), IDS_LBL_INSTIT_NBR,
   I_("04"), IDS_LBL_SWIFT_CODE,
   I_("05"), IDS_LBL_NBR,
   I_("06"), IDS_LBL_INSTIT_NBR,
   I_("07"), IDS_LBL_NBR,
   I_("08"), IDS_LBL_NBR,
   I_("09"), IDS_LBL_NBR,
   I_("10"), IDS_LBL_NBR,
};

const UINT BankLabelControls[] = {
   IDC_LBL_FIELD1,
   IDC_LBL_FIELD2,
   IDC_LBL_FIELD3,
   IDC_LBL_FIELD4,
   IDC_LBL_FIELD5,
   IDC_LBL_FIELD6,
};

const UINT BankTextControls[] = {
   IDC_TXT_FIELD1,
   IDC_TXT_FIELD2,
   IDC_TXT_FIELD3,
   IDC_TXT_FIELD4,
   IDC_TXT_FIELD5,
   IDC_TXT_FIELD6,
};

const UINT AllBankControls[] = {
   IDC_RD_BENEFICIARY,
   IDC_RD_CORRESPONDENT,
   IDC_BTN_BANK,
   IDC_LBL_FIELD1,
   IDC_LBL_FIELD2,
   IDC_LBL_FIELD3,
   IDC_LBL_FIELD4,
   IDC_LBL_FIELD5,
   IDC_LBL_FIELD6,
   IDC_TXT_FIELD1,
   IDC_TXT_FIELD2,
   IDC_TXT_FIELD3,
   IDC_TXT_FIELD4,
   IDC_TXT_FIELD5,
   IDC_TXT_FIELD6,
};

const UINT AllAddressControls[] = {
   IDC_TXT_NAME,
   IDC_TXT_ADDRESS_LINES,
   IDC_TXT_POSTCODE,
   IDC_TXT_COUNTRYCODE,
   IDC_EDT_ADDRESS_NAME1,
   IDC_EDT_ADDRESS_NAME2,
   IDC_EDT_ADDRESS_LINE,
   IDC_EDT_POSTCODE,
   IDC_CMB_COUNTRYCODE,
   IDC_TXT_ADDRESS_CODE,
   IDC_EDT_ADDR_CODE,
};

const UINT AddressTextControls[] = {
   IDC_TXT_NAME,
   IDC_TXT_ADDRESS_LINES,
   IDC_TXT_POSTCODE,
   IDC_TXT_COUNTRYCODE,
   IDC_EDT_ADDRESS_NAME1,
   IDC_EDT_ADDRESS_NAME2,
   IDC_EDT_ADDRESS_LINE,
   IDC_EDT_POSTCODE,
   IDC_CMB_COUNTRYCODE,   
   IDC_EDT_ADDR_CODE,
};

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettlePermCode;
   extern CLASS_IMPORT const BFIntegerFieldId AutoBatch;
   extern CLASS_IMPORT const BFTextFieldId PayInstructExists;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId EPASettlementHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AllowChqChange;
   extern CLASS_IMPORT const BFTextFieldId TradelevelOveride;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId FundIDList;
}
namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}
static const int _numBankLabels = sizeof(BankLabels)/sizeof(_BankLabel); 
static const int _numBankTextControls = sizeof(BankTextControls)/sizeof(UINT);
static const int _numBankLabelControls = sizeof(BankLabelControls)/sizeof(UINT); 
static const int _numAllBankControls = sizeof(AllBankControls)/sizeof(UINT);
static const int _numAllAddressControls = sizeof(AllAddressControls)/sizeof(UINT);
static const int _numAddressTextControls = sizeof(AddressTextControls)/sizeof(UINT);
//*****************************************************************************
// Public methods
//*****************************************************************************
SettlementDlg::SettlementDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SettlementDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_bTotal = true;
	m_bSettleAll = false;
	m_bSettleOnly =  false;
	m_bAlreadySearch =  false;
	m_bExcludeStopSettle = true; //Always default "Exclude Stop Settle" to YES.
	setGridUpdated(true);
   //{{AFX_DATA_INIT(SettlementDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void SettlementDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SettlementDlg)
   DDX_Check(pDX, IDC_CHK_SETTLE_ONLY, m_bSettleOnly);
   DDX_Check(pDX, IDC_CHK_SETTLE_ALL, m_bSettleAll);
   DDX_Check(pDX, IDC_CHK_EXCLUDE_TRADES_STOP_SETTLE_FLAG, m_bExcludeStopSettle);
   DDX_Control(pDX, IDC_RD_BENEFICIARY, m_btn_bankBene);
   DDX_Control(pDX, IDC_RD_CORRESPONDENT, m_btn_bankCorr);
   DDX_Control(pDX, IDC_BTN_BANK, m_btnBank);

//	DDX_Radio(pDX,IDC_RD_TOTAL_ALL,m_RdTotal);
//	DDX_Radio(pDX,IDC_RD_TOTAL_SETTLE,m_RdTotalSettle);

   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY SettlementDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   getParameter( Settlement_Para::FROM_SCR, _dstrFromScr );


   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(SettlementDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SettlementDlg)
ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED( IDC_BTN_DETAIL, OnBtnDetail )  
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )  
ON_BN_CLICKED( IDC_RD_TOTAL_SETTLE, OnRdTotalSettle )
ON_BN_CLICKED( IDC_RD_TOTAL_ALL, OnRdTotal )
ON_BN_CLICKED( IDC_CHK_SETTLE_ONLY, OnChkSettleOnly )
ON_BN_CLICKED( IDC_CHK_SETTLE_ALL, OnChkSettleAll )
ON_BN_CLICKED( IDC_CHK_EXCLUDE_TRADES_STOP_SETTLE_FLAG, OnChkExcludeStopSettle )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENSELECTADDRESSDLG, OpenSelectAddressDlg )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC, OpenIdnAccountsDlg )

ON_BN_CLICKED( IDC_RD_BENEFICIARY, OnRdBeneficiary )
ON_BN_CLICKED( IDC_RD_CORRESPONDENT, OnRdCorrespondent )
ON_BN_CLICKED( IDC_BTN_BANK, OnBtnBank )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL SettlementDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   EnableControls(false);
   //I am not sure how we are going to handle that, for now leave it like this(SP)   
   return(TRUE);
}


//*****************************************************************************
void SettlementDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );
   CWaitCursor wait;
	
   setGridUpdated (false);
   BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
   
   if (pBControl)
   {
      pBControl->Store();
   }
   
   if (getParent()->performSearch( this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_START ) <= WARNING)
   {
      EnableSearchCriteria (false);
      m_bAlreadySearch = true;
      ConnectControlsToData(IDC_SETTLEMENT_LIST); 
//      LoadGrid( IDC_SETTLEMENT_LIST, ifds::SettlementListHeadSet );
      GetDlgItem (IDC_RD_TOTAL_SETTLE)->EnableWindow (true);  
      GetDlgItem (IDC_RD_TOTAL_ALL)->EnableWindow (true); 
      LoadListControl (IDC_LST_TOTAL);
      ConnectControlToData (IDC_CMB_SETTLE_BATCH_NBR, true);
      LoadControl (IDC_CMB_SETTLE_BATCH_NBR);
      
      DString dstrSettleAll;
      
      getParent()->getField (this, IFASTBP_PROC::SETTLEMENT_LIST, ifds::SettleAll, dstrSettleAll, false);
      dstrSettleAll.strip();
      if (dstrSettleAll == I_("Y"))
      {
         CheckDlgButton (IDC_CHK_SETTLE_ALL, true);
      }
      DString dstrValue;
      
      DSTComboBox* pCmb = dynamic_cast<DSTComboBox* >(GetControl(IDC_CMB_SEARCH_USING) );
      
      if (pCmb)
      {
         int i = pCmb->GetCurSel();
         dstrValue = *reinterpret_cast <DString *> (pCmb->GetItemData (i));
         getParent()->setField (this, IFASTBP_PROC::SETTLEMENT, ifds::SearchType, dstrValue, true);
      }
      GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
      
      DString dstrUpdate;
      
      getParent()->getField (this, IFASTBP_PROC::SETTLEMENT, SETTL_PROC::PERMIT_UPDATE, dstrUpdate);
      GetDlgItem(IDC_CHK_SETTLE_ALL)->EnableWindow (dstrUpdate == YES);
      GetDlgItem(IDC_CHK_SETTLE_ONLY)->EnableWindow (true);
      GetDlgItem(IDC_BTN_DETAIL)->EnableWindow (true);
      SetDefID (IDOK);
      GetDlgItem (IDOK)->EnableWindow (dstrUpdate == YES);
      GetDlgItem (IDC_BTN_RESET)->EnableWindow (dstrUpdate == YES);

      DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );
      if (ghwnd)
      {
         ghwnd->reLoadGrid ();
      }
   }
   else
   {
      LoadControls (SETTLEMENT_SEARCH);
      ConditionMessageBox (MYFRAME(), GETCURRENTHIGHESTSEVERITY());
   }
	setGridUpdated (true);
}
//************************************************************************************
void SettlementDlg::EnableSearchCriteria(bool bEnable)
{ 
   GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(bEnable);
   GetDlgItem(IDC_CHK_EXCLUDE_TRADES_STOP_SETTLE_FLAG)->EnableWindow(bEnable);
}
//*************************************************************************************
void SettlementDlg::OnRdTotalSettle()
{
   m_bTotal = false;
   ((CButton* )GetDlgItem(IDC_RD_TOTAL_ALL))->SetCheck(0);
   ((CButton* )GetDlgItem(IDC_RD_TOTAL_SETTLE))->SetCheck(1);
   LoadListControl(IDC_LST_TOTAL);
}
//**************************************************************************************
void SettlementDlg::OnRdTotal()
{
   m_bTotal = true;
   ((CButton* )GetDlgItem(IDC_RD_TOTAL_ALL))->SetCheck(1);
   ((CButton* )GetDlgItem(IDC_RD_TOTAL_SETTLE))->SetCheck(0);
   LoadListControl(IDC_LST_TOTAL);
}

//***************************************************************************************
void SettlementDlg::OnChkSettleOnly()
{
   I_CHAR* dstrMessage;
   UpdateData();
   if( m_bSettleOnly )
   {
      dstrMessage = DISPLAY_SETTLE_ONLY;
   }
   else
   { //display all
      dstrMessage = DISPLAY_ALL;
   }

//   if( getParent()->send(this,dstrMessage) == true )
   {
      DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );
      if( ghwnd )
         ghwnd->reLoadGrid();
   }
   ClearEnableChildControls();

}
//********************************************************************************
void SettlementDlg::OnChkSettleAll()
{
   UpdateData();
   DString dstrSettleAll = I_("N");
   if( m_bSettleAll )
   {
      dstrSettleAll = I_("Y");
   }
   getParent()->setField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::SettleAll, dstrSettleAll,false);
   DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );
   if( ghwnd )
      ghwnd->reLoadGrid();
   LoadListControl(IDC_LST_TOTAL); 
}
//********************************************************************************
void SettlementDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SETTLEMENT_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::SETTLEMENT_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadGrid( IDC_SETTLEMENT_LIST, ifds::SettlementListHeadSet );      
      // refresh grid control
      DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );
      if (ghwnd)
      {
		 ghwnd->setUseCBOSubstitutions( MARKET_IDS::LUXEMBOURG == DSTCommonFunctions::getMarket() );
         ghwnd->RedrawWindow();
      }

   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}
//******************************************************************************
void SettlementDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   I_CHAR* dstrMessage = DISPLAY_ALL;
   //getParent()->send(this,dstrMessage);
	DString dstrSettle,dstrOrgSettle;
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::Settled, dstrSettle,false);
	dstrSettle.strip().upperCase();
   ResetGridItem( IDC_SETTLEMENT_LIST );
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::Settled, dstrOrgSettle,false);
	dstrOrgSettle.strip().upperCase();
	if(dstrOrgSettle != dstrSettle )
	{
      dstrMessage = RESET_ITEM;
      getParent()->send(this,dstrMessage);
		LoadControl(IDC_TXT_NBR_RECORDS); 
	}
/*
   if( m_bSettleOnly )
   {
      dstrMessage = DISPLAY_SETTLE_ONLY;
      //getParent()->send(this,dstrMessage);
   }
*/
   DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );
   if( ghwnd ){
      ghwnd->reLoadGrid();
	}
	LoadListControl( IDC_LST_TOTAL );
}
//*****************************************************************************
void SettlementDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   // SetUserAccesFunctionCode(UAF::ACCOUNT_DETAIL);//have to be changed to SHAREHOLDER
   addControlsForSearchCriteria();
   addControlsForSettle();
   DisplayBankAddress( true );
   DisplaySearchRelated( );
   checkPermissionForInqUpdate();

   SetDefID(IDC_BTN_SEARCH);
   CheckRadioButton( IDC_RD_TOTAL_ALL,IDC_RD_TOTAL_SETTLE, IDC_RD_TOTAL_ALL ); 

   if( GetDlgItem(IDC_BTN_SEARCH)->IsWindowEnabled() )
   {
      if( _dstrFromScr == Settlement_Para::ACCT_DETAIL || _dstrFromScr == Settlement_Para::TRANS_HISTORY ||
          _dstrFromScr == Settlement_Para::FROM_AWD)
      {
         OnBtnSearch();
         setDlgTitle();
      }
   }

   DSTComboBox *pCmbBatchName = dynamic_cast <DSTComboBox*> (GetControl (IDC_CMB_SETTLE_BATCH_NBR));

   if (pCmbBatchName)
   {
      pCmbBatchName->LimitText (10);
   }
    DString dstrTradeLevelOveride;
	bool bPymtRoutingAppl;
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption (ifds::TradelevelOveride, dstrTradeLevelOveride,getDataGroupId(),false);
	bPymtRoutingAppl = ( dstrTradeLevelOveride == YES);
	GetDlgItem(IDC_CMB_PAYMENT_ROUTING_TYPE)	-> ShowWindow(bPymtRoutingAppl);
	GetDlgItem(IDC_STATIC_PAYMENT_ROUTING_TYPE) -> ShowWindow(bPymtRoutingAppl);
	DSTGridWnd *pGrid = GetGrid( IDC_SETTLEMENT_LIST );
	if(pGrid)
	{
		pGrid->setUseCBOSubstitutions( MARKET_IDS::LUXEMBOURG == DSTCommonFunctions::getMarket() );
		ReInitGrid( CLASSNAME, IDC_SETTLEMENT_LIST, I_("SettlementTradeList"), 
				IFASTBP_PROC::SETTLEMENT_LIST, IDC_SETTLEMENT_LIST, ifds::SettlementListHeadSet,
				ifds::NullFieldId, DSTGridWnd::GRID_TYPE::LIST );
	}
	
}

//******************************************************************************
bool SettlementDlg::doRefresh( GenericInterface * rpGICaller,
                               const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return(true);
}

//********************************************************************************
bool SettlementDlg::addControlsForSearchCriteria( )
{ 
   TRACE_METHOD( CLASSNAME, I_("addControlsForSearchCriteria") );

   AddControl( CTRL_COMBO, IDC_CMB_SEARCH_USING, IFASTBP_PROC::SETTLEMENT, 
               ifds::SearchType, CTRLFLAG_INITCOMBO_BY_SUB_LIST , SETTLEMENT_SEARCH  );

   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT_NUMBER, IFASTBP_PROC::SETTLEMENT, 
               ifds::AccountNum, 0 , SETTLEMENT_SEARCH);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ACCOUNT_NUMBER))->SetAllowedChars(I_("0123456789"));

   AddControl( CTRL_COMBO, IDC_CMB_STL_CURRENCY_SETTLE_DATE, IFASTBP_PROC::SETTLEMENT, 
               ifds::SettleCurrency, CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE ,SETTLEMENT_SEARCH);

   AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::FundCode, 0 , SETTLEMENT_SEARCH);

   AddControl( CTRL_EDIT, IDC_EDT_WIRE_NUMBER, IFASTBP_PROC::SETTLEMENT, 
               ifds::WireOrdNum, 0 , SETTLEMENT_SEARCH);
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_WIRE_NUMBER) )->SetAllowedChars(I_("0123456789"));

   AddControl( CTRL_EDIT, IDC_EDT_TRANS_NUMBER, IFASTBP_PROC::SETTLEMENT, 
               ifds::TransNum, 0 , SETTLEMENT_SEARCH);
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_TRANS_NUMBER) )->SetAllowedChars(I_("0123456789"));

   AddControl( CTRL_DATE, IDC_DTP_FROM, IFASTBP_PROC::SETTLEMENT, 
               ifds::StartDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, SETTLEMENT_SEARCH );

   AddControl( CTRL_DATE, IDC_DTP_TO, IFASTBP_PROC::SETTLEMENT, 
               ifds::EndDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, SETTLEMENT_SEARCH );

   AddControl( CTRL_COMBO, IDC_CMB_TRANS_TYPE, IFASTBP_PROC::SETTLEMENT, 
               ifds::TransType, CTRLFLAG_INITCOMBO_BY_SUB_LIST , SETTLEMENT_SEARCH);

   AddControl( CTRL_STATIC, IDC_STC_CO_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::CompanyCode, 0 , SETTLEMENT_SEARCH);

   AddControl( CTRL_COMBO, IDC_CMB_CURRENCY_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::SettleCurrency, CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE , SETTLEMENT_SEARCH);
//broker
   AddControl( CTRL_EDIT, IDC_EDT_BROKER_NBR, IFASTBP_PROC::SETTLEMENT, 
               ifds::BrokerCode, 0 , SETTLEMENT_SEARCH);

   AddControl( CTRL_COMBO, IDC_CMB_VOL_STL_TYPE, IFASTBP_PROC::SETTLEMENT, 
               ifds::VolSettleType, CTRLFLAG_INITCOMBO_BY_SUB_LIST , SETTLEMENT_SEARCH);

   AddControl( CTRL_DATE, IDC_DTP_TRADE_DATE, IFASTBP_PROC::SETTLEMENT, 
               ifds::TradeDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, SETTLEMENT_SEARCH );

   AddControl( CTRL_DATE, IDC_DTP_SETTLE_DATE, IFASTBP_PROC::SETTLEMENT, 
               ifds::SettleDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, SETTLEMENT_SEARCH);

   AddControl( CTRL_COMBO, IDC_CMB_STL_CURRENCY, IFASTBP_PROC::SETTLEMENT, 
               ifds::SettleCurrency, CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE , SETTLEMENT_SEARCH);

   AddControl( CTRL_EDIT, IDC_EDT_BROKER_FUND_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::FundCode, 0 , SETTLEMENT_SEARCH);

   AddControl( CTRL_COMBO, IDC_CMB_SETTLE_BATCH_NBR, IFASTBP_PROC::SETTLEMENT, 
               ifds::rxBatchName, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST  | CTRLFLAG_COMBO_EDIT, SETTLEMENT_SEARCH);

   // External Id Search
   AddControl( CTRL_COMBO, IDC_CMB_EXTERNAL_ID_TYPE, IFASTBP_PROC::SETTLEMENT, 
               ifds::ExternalIdType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SETTLEMENT_SEARCH);
   AddControl( CTRL_EDIT, IDC_EDT_EXTERNAL_ID, IFASTBP_PROC::SETTLEMENT, 
               ifds::ExternalId, 0 , SETTLEMENT_SEARCH);

//EPA broker
   AddControl( CTRL_EDIT, IDC_EDT_EPA_BROKER_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::BrokerCode, 0 , SETTLEMENT_SEARCH);

   AddControl( CTRL_DATE, IDC_DTP_EPA_DATE, IFASTBP_PROC::SETTLEMENT, 
               ifds::SettleDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, SETTLEMENT_SEARCH);

//Registration Agent
   AddControl( CTRL_EDIT, IDC_EDT_REG_AGENT_CODE, IFASTBP_PROC::SETTLEMENT, 
               ifds::RegAgentCode, 0 , SETTLEMENT_SEARCH);

   ConnectControlToData(IDC_CMB_SEARCH_USING,true );
   LoadControl( IDC_CMB_SEARCH_USING );
   ConnectControlToData(IDC_CMB_SETTLE_BATCH_NBR, true);
   LoadControl (IDC_CMB_SETTLE_BATCH_NBR);

   GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);

   return(true);
}

//****************************************************************************
void SettlementDlg::addControlsForSettle()
{

   AddGrid( CLASSNAME, IDC_SETTLEMENT_LIST, I_("SettlementTradeList"),
            IFASTBP_PROC::SETTLEMENT_LIST, IDC_SETTLEMENT_LIST, ifds::SettlementListHeadSet,
            ifds::NullFieldId,DSTGridWnd::GRID_TYPE::LIST );

   AddListControl( CLASSNAME, IDC_LST_TOTAL, I_("SettlementTotalList"),
                   ifds::SettlementTotalHeading, IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,0,true,LISTFLAG_NOT_AUTO_ADD );

   AddControl( CTRL_EDIT, IDC_TXT_NBR_RECORDS, IFASTBP_PROC::SETTLEMENT_TOTAL_LIST, 
               SETTL_PROC::TOTAL_COUNT, 0 , IDC_LST_TOTAL );


   AddGrid( CLASSNAME, IDC_GRID_ATTRIB, I_("Grid_Attribute"), 
            IFASTBP_PROC::SETTLEMENT_LIST, IDC_SETTLEMENT_LIST, ifds::TradingAttributesHeadingSet, 
            ifds::SettlementGridSet );

   AddControl( CTRL_COMBO, IDC_CMB_DELIVERY_MOTHOD, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::DeliveryMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);


   AddControl( CTRL_COMBO, IDC_CMB_SETTLE_METHOD, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::SettledBy, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_PAY_TYPE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::PayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_SUPPRESS_CODE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::SuppressCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_PAYMENT_METHOD, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::PayMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_DATE, IDC_DTP_VALUE_DATE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::ValueDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_FILE_PROCESSOR, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::ACHProcessor, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_BANK_CHARGES, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BankChrgs, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);


   AddControl( CTRL_EDIT, IDC_EDT_ADDR_CODE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::AddrCode, 0 , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS_NAME1, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::Name1, 0 , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS_NAME2, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::Name2, 0 , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS_LINE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::ShareholderAddress,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_SETTLEMENT_LIST );

   AddControl( CTRL_EDIT, IDC_EDT_POSTCODE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::PostalCode, 0 , IDC_SETTLEMENT_LIST);

   AddControl( CTRL_COMBO, IDC_CMB_COUNTRYCODE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::CountryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);
   
   AddControl(  CTRL_COMBO, IDC_CMB_PAYMENT_ROUTING_TYPE, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::PymtRoutingMthd, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_SETTLEMENT_LIST);


   DSTGridWnd * grdWnd = GetGrid( IDC_GRID_ATTRIB );
   //grdWnd->setUseCBOSubstitutions();
   grdWnd->GetParam( )->EnableTrackRowHeight( 0 );
   grdWnd->SetRowHeight(0,39,20);
   grdWnd = GetGrid( IDC_SETTLEMENT_LIST );
   grdWnd->SetSorting(true);

   CGXGridParam* cgxParam = grdWnd->GetParam( );
   cgxParam->EnableMoveRows( FALSE );
   cgxParam->EnableMoveCols( FALSE );

   for( int i= 0; i<_numBankTextControls; i++ )
   {
      if( i< 2 )
      {
         AddControl( CTRL_EDIT, BankTextControls[i], BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );    //   CTRL_STATIC
      }
      else
      {
         AddControl( CTRL_STATIC, BankTextControls[i], BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );   
      }
   }   
}

//***********************************************************
void SettlementDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_SEARCH_USING:
         DisplaySearchRelated();
         checkPermissionForInqUpdate();
         break;

      case IDC_CMB_PAY_TYPE:
         {
            DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_GRID_ATTRIB) );
            if( ghwnd )
               ghwnd->reLoadGrid();
         }
      case IDC_CMB_PAYMENT_METHOD:
         DisplayBankAddress();
         //this is temp solution, it should be handled by base class
         break;

      case IDC_CMB_VOL_STL_TYPE:
         {
            DString dstrVolSettleType; 
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT,  ifds::VolSettleType,dstrVolSettleType,false);
            dstrVolSettleType.strip();
            CString cstrLable;
            if( dstrVolSettleType == I_("I") )
            {
               cstrLable.LoadString(IDS_SETTLE_CURRENCY);
            }
            else
            {
               cstrLable.LoadString(IDS_FUND_CURREENCY);
            }
            cstrLable += _T(":");

            GetDlgItem(IDC_TXT_STL_CURRENCY)->SetWindowText ( cstrLable );     
         }
         break;
      case IDC_EDT_ADDR_CODE:
         LoadControl(IDC_EDT_ADDRESS_NAME1);
         LoadControl(IDC_EDT_ADDRESS_NAME2);
         LoadControl(IDC_EDT_ADDRESS_LINE);
         LoadControl(IDC_EDT_POSTCODE);
         LoadControl(IDC_CMB_COUNTRYCODE);
         break;

      default:
         break;
   }
}
//*********************************************************************************************************
bool SettlementDlg::GetCellValue( UINT ctrlId,
                                  const DString &rowKey,
                                  const DString &colKey,
                                  DString &strOut,
                                  bool bFormatted)
{
   if( ctrlId == IDC_SETTLEMENT_LIST )
   {
      if( colKey == I_("SettleCurrency") )
      {
         getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::SettleCurrency,strOut,bFormatted);

         return(true);
      }
   }

   return(false);

}

//********************************************************************************************************
bool SettlementDlg::PreOk()
{
   DString dstrSettleCnt;  
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,
                         SETTL_PROC::TOTAL_COUNT_SETTLE,dstrSettleCnt,true );
   dstrSettleCnt.strip().stripLeading('0');
   if( NULL_STRING != dstrSettleCnt )
   {
      CDialog dlg(IDD_CONFIRM_SETTLE,this);
      if( dlg.DoModal( ) == IDCANCEL )
      {
         return(false);
      }
   }
   return(true);
}

//*********************************************************************************************************
bool SettlementDlg::GetOverrideItemString( long lSubstituteId,
                                         const DString& ColumnKey,
                                           DString& strOut )
{
   if( lSubstituteId == ifds::SettlementTotalHeading.getId() )
   {
      if( ColumnKey == I_("Currency") )
      {
         getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::Currency,strOut,false);
         return(true);
      }
      if( IsDlgButtonChecked(IDC_RD_TOTAL_SETTLE) )
      {
         if( ColumnKey == I_("CountTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::CountTotalSettel,strOut);
            return(true);
         }
         if( ColumnKey == I_("PurchaseTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::PurchaseTotalSettle,strOut);
            return(true);
         }
         if( ColumnKey == I_("RedemptTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::RedemptionTotalSettle,strOut);
            return(true);
         }
         if( ColumnKey == I_("NetTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::NetTotalSettle,strOut);
            return(true);
         }
         if( ColumnKey == I_("ExchangeInTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::ExchangeInTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("ExchangeOutTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::ExchangeOutTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("TransferInTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::TransferInTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("TransferOutTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::TransferOutTotal,strOut);
            return(true);
         }
      }
      else if( IsDlgButtonChecked(IDC_RD_TOTAL_ALL) )
      {
         if( ColumnKey == I_("CountTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::CountTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("PurchaseTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::PurchaseTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("RedemptTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::RedemptTotal,strOut);
            return(true);
         }
         if( ColumnKey == I_("NetTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::NetTotal,strOut);
            return(true);

         }
         if( ColumnKey == I_("ExchangeInTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::ExchangeInTotal,strOut);
            return(true);

         }
         if( ColumnKey == I_("ExchangeOutTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::ExchangeOutTotal,strOut);
            return(true);

         }
         if( ColumnKey == I_("TransferInTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::TransferInTotal,strOut);
            return(true);

         }
         if( ColumnKey == I_("TransferOutTotal") )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::TransferOutTotal,strOut);
            return(true);

         }
      }
      else
      {
         assert(0);
      }
   }
   return(false);
}

//*******************************************************************************
void SettlementDlg::DisplayBankAddress(bool bInitial  )
{

   bool bBank, bAddress ;
   DString dstrPymtGen;
   if( bInitial )
   {
      bBank =false;
      bAddress =false;
   }
   else
   {
      DString dstrPayType,dstrPaymentMethod;
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::PayType,dstrPayType,false );
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::PayMethod,dstrPaymentMethod,false );
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::PymtGen,dstrPymtGen,false );
      bBank = ( ((dstrPayType.strip() == DIRECT_DEPST_REDEMPTION) &&
                 dstrPaymentMethod.strip() == I_("DDER") &&
                 DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA) || 
                 ((dstrPayType.strip() == I_("E")) &&
                 (dstrPaymentMethod.strip() == I_("WIRE") || dstrPaymentMethod.strip() == I_("EFT"))) );

      bAddress = dstrPayType.strip() == I_("S") ||
                 dstrPayType.strip() == I_("E") && 
                 dstrPaymentMethod.strip() == I_("CHQ");
   }

   UINT nShowAddress = bAddress? SW_SHOW : SW_HIDE;
   UINT nShowBank = bBank? SW_SHOW:SW_HIDE;

   for( int i = 0; i<_numAllBankControls; i++ )
   {
      GetDlgItem ( AllBankControls [i] )->ShowWindow ( nShowBank );
      if(IDC_BTN_BANK == AllBankControls [i])
          GetDlgItem(IDC_BTN_BANK)->EnableWindow( !(I_("Y") == dstrPymtGen.strip() && SW_SHOW == nShowBank) );
   }
   for( int i = 0; i< _numAllAddressControls; i++ )
   {
      GetDlgItem ( AllAddressControls [i] )->ShowWindow ( nShowAddress );
   }
   for( int i = 4 ; i < _numAddressTextControls; i++ )
   {
      if ( !bInitial )
      {
         ConnectControlToData ( AddressTextControls[i], bAddress );
         LoadControl( AddressTextControls[i] );	
      }
   }
   if( nShowBank == SW_SHOW )
   {
      lockRdCorrespondent();
      OnRdBeneficiary ();
   }
}

//***************************************************************************************
void SettlementDlg::DisplaySearchRelated(  )
{
   DString searchType; 
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT,ifds::SearchType,searchType,false);
   searchType.strip();

   UINT nShowBroker =  searchType == Settlement_Para::BROKER ? SW_SHOW:SW_HIDE;
   UINT nAccount =  searchType == Settlement_Para::ACCOUNT || searchType == Settlement_Para::ACCT_WIRENUMBER ? SW_SHOW:SW_HIDE;
   UINT nWireOrder =  searchType == Settlement_Para::WIRE_ORDER || searchType == Settlement_Para::ACCT_WIRENUMBER ? SW_SHOW:SW_HIDE;
   UINT nTransNumber =  searchType == Settlement_Para::TRANS_NUMBER ? SW_SHOW:SW_HIDE;
   UINT nCurrency =  searchType == Settlement_Para::SETTLE_CURRENCY ? SW_SHOW:SW_HIDE;
   UINT nFund =  searchType == Settlement_Para::FUND ? SW_SHOW:SW_HIDE;

   UINT nSettleCurrency = ( searchType == Settlement_Para::ACCOUNT ||  
                            searchType == Settlement_Para::TRADE_DATE ||
                            searchType == Settlement_Para::SETTLE_DATE )? SW_SHOW:SW_HIDE;
   UINT nTransType = ( searchType == Settlement_Para::BROKER ||  
                       searchType == Settlement_Para::TRADE_DATE ||
                       searchType == Settlement_Para::SETTLE_DATE ||
                       searchType == Settlement_Para::REGISTRATION_AGENT )? SW_SHOW:SW_HIDE;

   UINT nCompanyCode = ( searchType == Settlement_Para::BROKER ||  
                         searchType == Settlement_Para::TRADE_DATE ||
                         searchType == Settlement_Para::SETTLE_DATE )? SW_SHOW:SW_HIDE;


   UINT nFromToDate = ( searchType == Settlement_Para::TRADE_DATE ||
                        searchType == Settlement_Para::SETTLE_DATE )? SW_SHOW:SW_HIDE;

   UINT nShowExternalId =  searchType == Settlement_Para::EXTERNAL_ID ? SW_SHOW:SW_HIDE;

   UINT nShowEPABroker =  searchType == Settlement_Para::EPA_BROKER ? SW_SHOW:SW_HIDE;

   UINT nShowRegAgent =  searchType == Settlement_Para::REGISTRATION_AGENT ? SW_SHOW:SW_HIDE;

   UINT nShowSettleDate =  searchType == Settlement_Para::BROKER ||
                           searchType == Settlement_Para::REGISTRATION_AGENT
                           ? SW_SHOW:SW_HIDE;

// Currency
   GetDlgItem ( IDC_TXT_CURRENCY_CODE )->ShowWindow (nCurrency);
   ConnectControlToData(IDC_CMB_CURRENCY_CODE,nCurrency?true:false,true);
// Account Number
   GetDlgItem ( IDC_TXT_ACCOUNT_NUMBER )->ShowWindow (nAccount);
   ConnectControlToData(IDC_EDT_ACCOUNT_NUMBER,nAccount?true:false,true);

// Fund
   GetDlgItem ( IDC_TXT_FUND_CODE )->ShowWindow (nFund);
   ConnectControlToData(IDC_EDT_FUND_CODE,nFund?true:false,true);

// Wire Order
   GetDlgItem ( IDC_TXT_WIRE_NUMBER )->ShowWindow (nWireOrder);
   ConnectControlToData(IDC_EDT_WIRE_NUMBER,nWireOrder?true:false,true);

// Transaction Number
   GetDlgItem ( IDC_TXT_TRANS_NUMBER )->ShowWindow (nTransNumber);
   ConnectControlToData(IDC_EDT_TRANS_NUMBER,nTransNumber?true:false,true);

// FromToDate
   GetDlgItem ( IDC_TXT_FROM )->ShowWindow (nFromToDate);
   GetDlgItem ( IDC_TXT_TO )->ShowWindow (nFromToDate);
   ConnectControlToData(IDC_DTP_FROM,nFromToDate?true:false,true);
   ConnectControlToData(IDC_DTP_TO,nFromToDate?true:false,true);

// TransType
   GetDlgItem ( IDC_TXT_TRANS_TYPE )->ShowWindow (nTransType);
   GetDlgItem ( IDC_CMB_TRANS_TYPE )->ShowWindow (nTransType);
   ConnectControlToData(IDC_CMB_TRANS_TYPE,nTransType?true:false,true);

// Company Code
   GetDlgItem ( IDC_TXT_CO_CODE )->ShowWindow (nCompanyCode);
   ConnectControlToData(IDC_STC_CO_CODE,nCompanyCode?true:false,true);

// Stl Currency at 2nd line
   GetDlgItem ( IDC_TXT_STL_CURRENCY_SETTLE_DATE )->ShowWindow (nSettleCurrency);
   ConnectControlToData(IDC_CMB_STL_CURRENCY_SETTLE_DATE,nSettleCurrency?true:false,true);


// Broker
   GetDlgItem ( IDC_TXT_BROKER_NBR )->ShowWindow (nShowBroker);
   GetDlgItem ( IDC_TXT_BROKER_FUND_CODE )->ShowWindow (nShowBroker);
   GetDlgItem ( IDC_TXT_STL_CURRENCY )->ShowWindow (nShowBroker);
   GetDlgItem ( IDC_TXT_TRADE_DATE )->ShowWindow (nShowBroker);
   GetDlgItem ( IDC_TXT_VOL_STL_TYPE )->ShowWindow (nShowBroker);

// External ID
   GetDlgItem( IDC_TXT_EXT_ID_TYPE )->ShowWindow( nShowExternalId );
   GetDlgItem( IDC_CMB_EXTERNAL_ID_TYPE )->ShowWindow( nShowExternalId );
   GetDlgItem( IDC_TXT_EXTERNAL_ID )->ShowWindow( nShowExternalId );
   GetDlgItem( IDC_EDT_EXTERNAL_ID )->ShowWindow( nShowExternalId );

//EPA broker
   GetDlgItem( IDC_TXT_EPA_BROKER_CODE )->ShowWindow( nShowEPABroker );
   GetDlgItem( IDC_EDT_EPA_BROKER_CODE )->ShowWindow( nShowEPABroker );
   GetDlgItem( IDC_TXT_EPA_DATE )->ShowWindow( nShowEPABroker );
   GetDlgItem( IDC_DTP_EPA_DATE )->ShowWindow( nShowEPABroker );

//Reg Agent
   GetDlgItem( IDC_TXT_REG_AGENT_CODE )->ShowWindow(nShowRegAgent);
   ConnectControlToData(IDC_EDT_REG_AGENT_CODE,nShowRegAgent?true:false,true);

   DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_SETTLEMENT_LIST) );

   if( ghwnd )
   {
      if ( searchType == Settlement_Para::EPA_BROKER )
      {
         //Reinit the grid
         ReInitGrid( CLASSNAME, 
                     IDC_SETTLEMENT_LIST, 
                     I_("SettlementTradeList"), 
                     IFASTBP_PROC::SETTLEMENT_LIST, 
                     IDC_SETTLEMENT_LIST, ifds::EPASettlementHeadingSet, 
                     ifds::NullFieldId,
                     DSTGridWnd::GRID_TYPE::LIST);
      }
      else
      {
		DSTGridWnd *pGrid = GetGrid( IDC_SETTLEMENT_LIST );
		if(pGrid)
		{
		pGrid->setUseCBOSubstitutions( MARKET_IDS::LUXEMBOURG == DSTCommonFunctions::getMarket() );
        ReInitGrid( CLASSNAME, 
                     IDC_SETTLEMENT_LIST, 
                     I_("SettlementTradeList"), 
                     IFASTBP_PROC::SETTLEMENT_LIST, 
                     IDC_SETTLEMENT_LIST, 
                     ifds::SettlementListHeadSet, 
                     ifds::NullFieldId,
                     DSTGridWnd::GRID_TYPE::LIST);
		}
      }
   }

   ConnectControlToData(IDC_EDT_BROKER_NBR,nShowBroker?true:false,true);
   ConnectControlToData(IDC_EDT_BROKER_FUND_CODE,nShowBroker?true:false,true);
   ConnectControlToData(IDC_CMB_VOL_STL_TYPE,nShowBroker?true:false,true);
   ConnectControlToData(IDC_DTP_TRADE_DATE,nShowBroker?true:false,true);
   ConnectControlToData(IDC_CMB_STL_CURRENCY,nShowBroker?true:false,true);


   GetDlgItem ( IDC_TXT_SETTLE_DATE )->ShowWindow (nShowSettleDate);
   ConnectControlToData(IDC_DTP_SETTLE_DATE,nShowSettleDate?true:false,true);

   ConnectControlToData( IDC_CMB_EXTERNAL_ID_TYPE, nShowExternalId ? true:false, true );
   ConnectControlToData( IDC_EDT_EXTERNAL_ID,      nShowExternalId ? true:false, true );

   ConnectControlToData(IDC_EDT_EPA_BROKER_CODE,nShowEPABroker?true:false,true);
   ConnectControlToData(IDC_DTP_EPA_DATE,nShowEPABroker?true:false,true);

   LoadControls( SETTLEMENT_SEARCH );
}

//***************************************************************************************
void SettlementDlg::setDlgTitle()
{
   CString  cstrAccount;
   DString  dstrTitle;
   cstrAccount.LoadString(TXT_ACCOUNT_NBR);  
   DString dstrShrNum,dstrName,dstrAccountNum; 
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,SETTL_PROC::SHR_NUM,dstrShrNum);
   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,SETTL_PROC::ENTITY_NAME,dstrName);

   getParent()->getField(this,IFASTBP_PROC::SETTLEMENT,ifds::AccountNum,dstrAccountNum);

   dstrTitle = I_(":")+dstrShrNum +SPACE_STRING +(LPCTSTR)cstrAccount + I_(":")+ dstrAccountNum + SPACE_STRING + dstrName;
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrName);
}

//***************************************************************************************
void SettlementDlg::GetCellProperties( UINT ctrlId, 
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
   dstrAllowedChar = NULL_STRING;

   if( colKey  == _T("Settled") )
   {
      idContainer       = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField           = ifds::Settled;
      nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
      cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
      idSubstitution    = ifds::Settled;
   }
   else if( colKey  == _T("GNSettle") )
   {
      idContainer       = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField           = ifds::GNSettle;
      nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
      cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;    
      nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
      idSubstitution    = ifds::GNSettle;

   }
   else if( colKey  == _T("AccountNum") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::AccountNum;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }

   else if( colKey  == _T("TradesTransType") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::TransType;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("WireOrdNum") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::WireOrdNum;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }

   else if( colKey  == _T("FundCode") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::FundCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("ClassCode") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::ClassCode;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("NetAmt") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::NetAmt;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("GrossAmt") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::GrossAmt;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("SettleCurrency") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::SettleCurrency;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("PayType") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::PayType;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("PayMethod") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::PayMethod;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("FundWKN") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::FundWKN;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("FundISIN") )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::FundISIN;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( _T("Valoren") == colKey )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::Valoren;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( _T("TDCC")== colKey  )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::TDCC;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( _T("CUSIP") == colKey )
   {
      idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
      idField     = ifds::CUSIP;
      nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
      cellCtrlType = GX_IDS_CTRL_STATIC;    
   }
   else if( colKey  == _T("Attribute") )
   {
      nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
   }
   else if( colKey  == _T("Value") )
   {
      if( rowKey == _T("AltAccount") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::AltAccount;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   

      }
      else if( rowKey == _T("TransNum") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::TransNum;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;    
      }
      else if( rowKey == _T("TradeDate") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::TradeDate;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_DATETIME;   
      }
      else if( rowKey == _T("SettleDate") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::SettleDate;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_DATETIME;   
      }

      else if( rowKey == _T("Units") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::Units;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }

      else if( rowKey == _T("Price") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::Price;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("SettleCurrency") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::SettleCurrency;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("ExchangeRate") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::ExchRate;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("Commission") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::Commission;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("DistFee") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::DistFee;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("Fee") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::Fee;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("Extra") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::Commission2;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }

      else if( rowKey == _T("BrokerCode") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::BrokerCode;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("BranchCode") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::BranchCode;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("SlsrepCode") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::SlsrepCode;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("GrossNet") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::ExpGNSettle;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("OrigOrderSource") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::OrderSource;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("OrigSettleSource") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::SettleSource;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }


      else if( rowKey == _T("OrigSettleType") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::SettleType;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
      else if( rowKey == _T("BatchNum") )
      {
         idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
         idField     = ifds::BatchName;
         nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_STATIC;   
      }
	  else if( rowKey == _T("CashDate") )
      {
		  idContainer = IFASTBP_PROC::SETTLEMENT_LIST ;
		  idField     = ifds::CashDate;
		  nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
		  cellCtrlType= GX_IDS_CTRL_DATETIME;
      }
   }
}

//*******************************************************************************
bool SettlementDlg::OnGridSetCellValue( UINT ctrlId,
                                        const DString &rowKey,
                                        const DString &colKey,
                                        const DString &strIn)
{

   if( colKey  == _T("Settled") || colKey  == _T("GNSettle") )
   {
      LoadListControl(IDC_LST_TOTAL); 
   }
   if( colKey  == _T("Settled") )
   {
      //PostMessage(UM_REFRESHGRID );
   }

   return(false);

}

//******************************************************************************

LRESULT SettlementDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      


      // Set Search Parameters (Code, Class, Number) for Fund Class Dialog
      switch( m_uiDialogItem )
      {
         case IDC_EDT_FUND_CODE:
         case IDC_EDT_BROKER_FUND_CODE:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUND_CODE, dstrFundCode );
            }
            break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode;
               getParameter ( FUND_CODE, dstrFundCode );

               if( ( GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE  ) ) || 
                   ( GetFocus() == GetDlgItem( IDC_EDT_BROKER_FUND_CODE ) ) )
               {

                  getParent()->setField( this, IFASTBP_PROC::SETTLEMENT, ifds::FundCode, dstrFundCode );
                  if( m_uiDialogItem == IDC_EDT_FUND_CODE )
                     LoadControl ( IDC_EDT_FUND_CODE );
                  else if( m_uiDialogItem == IDC_EDT_BROKER_FUND_CODE )
                     LoadControl ( IDC_EDT_BROKER_FUND_CODE );


               }
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

//******************************************************************************
BOOL SettlementDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND_CODE;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_BROKER_FUND_CODE ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_BROKER_FUND_CODE;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_BROKER_NBR ) )
      {
         PostMessage( UM_OPENBROKERLISTDLG );      
         m_uiDialogItem = IDC_EDT_BROKER_NBR;
      }

      else if( GetFocus() == GetDlgItem( IDC_EDT_ADDR_CODE ) )
      {
         PostMessage( UM_OPENSELECTADDRESSDLG );      
         m_uiDialogItem = IDC_EDT_ADDR_CODE;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ADDRESS_LINE ) )
      {
         PostMessage( UM_OPENSELECTADDRESSDLG );      
         m_uiDialogItem = IDC_EDT_ADDRESS_LINE;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_POSTCODE ) )
      {
         PostMessage( UM_OPENSELECTADDRESSDLG );      
         m_uiDialogItem = IDC_EDT_POSTCODE;
      }
      else if( GetFocus() == GetDlgItem( IDC_CMB_COUNTRYCODE ) )
      {
         PostMessage( UM_OPENSELECTADDRESSDLG );      
         m_uiDialogItem = IDC_CMB_COUNTRYCODE;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ACCOUNT_NUMBER ) )
      {
         PostMessage( WM_LAUNCH_IDENT_ACC );
         m_uiDialogItem = IDC_EDT_ACCOUNT_NUMBER;
      }


   }


   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************
LRESULT SettlementDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode;

      GetControlText( IDC_EDT_BROKER_NBR, brokerCode );
      setParameter( BROKER_CODE, brokerCode );
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString brokerCode;

               getParameter( BROKER_CODE, brokerCode );
               if( brokerCode != NULL_STRING )
               {
//                  SetControlText( IDC_EDT_BROKER, brokerCode );
                  bool success = SetControlText( IDC_EDT_BROKER_NBR, brokerCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER_NBR ));
                  if( !success && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
                  LoadControl(IDC_CMB_VOL_STL_TYPE);  
               }
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

//******************************************************************************

void SettlementDlg::setupBankControls( bool bCorrespBank, const BFContainerId& idContainer )
{   
   _iMaxBankLabels = 0;
   int iCurrentLabel = 1;  //Start after the Bank ID type
   DString dstrBankIdType;
   BFFieldId idField = ifds::NullFieldId;
   if ( bCorrespBank )
      idField = ifds::BankIdTypeCB;
   else
      idField = ifds::BankIdType;

   getParent()->getField ( this, idContainer, idField, dstrBankIdType, false );                 
   ReInitControl ( BankTextControls [0], idContainer, idField );
   ConnectControlToData ( BankTextControls[0], true );   
   int iLength, iMaxLenght;
   bool bIsAllDigits ;
   CString cstrLabel;
  
//   clearBankInfo();
   if( FinancialInstitution::getBankIdNumInfo( dstrBankIdType, iLength, bIsAllDigits, iMaxLenght ) && iLength != 0 )
   {
      for( int i = 0; i<_numBankLabels; i++ )
      {
         if( BankLabels[i]._bankTypeId == dstrBankIdType )
         {
            cstrLabel.LoadString ( BankLabels[i].BankTypeDesc );
            break;
         }
      }
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->ShowWindow ( true );
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->SetWindowText ( cstrLabel );
      if( bCorrespBank )
         idField = ifds::BankIdValueCB;
      else
         idField = ifds::BankIdValue;
      ReInitControl ( BankTextControls [iCurrentLabel], idContainer, idField );
      ConnectControlToData ( BankTextControls[iCurrentLabel], true );
      GetDlgItem ( BankTextControls[iCurrentLabel])->ShowWindow ( true );
      ++iCurrentLabel ;
   }

   if( FinancialInstitution::getBankTransitNumInfo ( dstrBankIdType, iLength, bIsAllDigits, iMaxLenght ) && iLength != 0 )
   {
      cstrLabel.LoadString ( COL_BANKINS_TRANSITNBR );
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->ShowWindow ( true );      
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->SetWindowText ( cstrLabel );
      if( bCorrespBank )
         idField = ifds::TransitNoCB;
      else
         idField = ifds::TransitNo;
      ReInitControl ( BankTextControls [iCurrentLabel], idContainer, idField);
      ConnectControlToData ( BankTextControls[iCurrentLabel], true );
      GetDlgItem ( BankTextControls[iCurrentLabel])->ShowWindow ( true );
      iCurrentLabel++;
   }
   cstrLabel.LoadString ( LBL_BANK_INST_NAME );
   GetDlgItem ( BankLabelControls [iCurrentLabel] )->ShowWindow ( true );
   GetDlgItem ( BankLabelControls [iCurrentLabel] )->SetWindowText ( cstrLabel );
   if( bCorrespBank )
      idField = ifds::InstNameCB;
   else
      idField = ifds::InstName;
   ReInitControl ( BankTextControls [iCurrentLabel], idContainer, idField);
   ConnectControlToData ( BankTextControls[iCurrentLabel], true );
   GetDlgItem ( BankTextControls[iCurrentLabel])->ShowWindow ( true );
   iCurrentLabel++;

   if( !bCorrespBank && FinancialInstitution::getBankAccNumInfo ( dstrBankIdType, iLength, bIsAllDigits, iMaxLenght ) && iLength != 0 )
   {
      cstrLabel.LoadString ( LBL_BANK_ACCT_NBR );
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->ShowWindow ( true );      
      GetDlgItem ( BankLabelControls [iCurrentLabel] )->SetWindowText ( cstrLabel );
      ReInitControl ( BankTextControls [iCurrentLabel], idContainer, ifds::BankAcctNum);
      cstrLabel.LoadString ( LBL_BANK_ACCT_NAME );
      GetDlgItem ( BankLabelControls [iCurrentLabel+1] )->ShowWindow ( true );
      GetDlgItem ( BankLabelControls [iCurrentLabel+1] )->SetWindowText ( cstrLabel );
      ReInitControl ( BankTextControls [iCurrentLabel+1], idContainer, ifds::BankAcctName);
      ConnectControlToData ( BankTextControls[iCurrentLabel], true );
      ConnectControlToData ( BankTextControls[iCurrentLabel+1], true );
      GetDlgItem ( BankTextControls[iCurrentLabel])->ShowWindow ( true );
      GetDlgItem ( BankTextControls[iCurrentLabel+1])->ShowWindow ( true );
      iCurrentLabel  +=2;
   }

   //Hide the rest of the Labels/Text fields.
   _iMaxBankLabels = iCurrentLabel ;
   while( iCurrentLabel  < _numBankLabelControls )
   {
      GetDlgItem ( BankLabelControls[iCurrentLabel] )->ShowWindow ( false );
      GetDlgItem ( BankTextControls[iCurrentLabel])->ShowWindow ( false );
      ConnectControlToData ( BankTextControls[iCurrentLabel], false );
      ++iCurrentLabel ;
   }   
   LoadControls();
}

//***************************************************************************************
void SettlementDlg::clearBankInfo( )
{   
   for( int i = 0; i <= _numBankTextControls; i++ )
   {
      ClearControl ( BankTextControls [i] );
   }
}

//***************************************************************************************
void SettlementDlg::OnRdBeneficiary() 
{
   m_btn_bankBene.SetCheck(1);
   m_btn_bankCorr.SetCheck(0);
   setupBankControls ( false, IFASTBP_PROC::SETTLEMENT_LIST );
}

//***************************************************************************************
void SettlementDlg::OnRdCorrespondent() 
{
   m_btn_bankBene.SetCheck(0);
   m_btn_bankCorr.SetCheck(1);
   setupBankControls ( true, IFASTBP_PROC::SETTLEMENT_LIST );
}

//******************************************************************************
void SettlementDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNBANK);
   CWaitCursor wait;

   try
   {
      SetMessageStatusBar(TXT_LOAD_BANKING);   

      DString dstrSettlementKey,
         strUserAccessCode,
         dstrAccountNum,
         payInstructExists,
         payToEntity,
         str;

      dstrSettlementKey = getParent()->
         getCurrentListItemKey(this, IFASTBP_PROC::SETTLEMENT_LIST);
      getParent()->getField(this, IFASTBP_PROC::SETTLEMENT, 
         ifds::SettlePermCode, strUserAccessCode, false);
      getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
         ifds::AccountNum, dstrAccountNum, false);
      getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
         ifds::PayInstructExists, payInstructExists, false );
      getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
         ifds::PayToEntity, payToEntity, false );

      setParameter(USER_ACCESS_CODE, strUserAccessCode);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SETTLEMENT);
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);
      setParameter(MFCAN_IP_PARAM::LIST_KEY, dstrSettlementKey);
      setParameter(I_("PayInstructExists"), payInstructExists);
      setParameter(I_("PayToEntity"), payToEntity);

      if ( !payInstructExists.strip().upperCase().empty() && 
           payInstructExists.strip().upperCase() == I_("Y") )
      {
         DString brokerCode,
                 branchCode,
                 slsrepCode;

         if ( payToEntity.strip().upperCase() == PAY_TO::BROKER )
         {
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BrokerCode, brokerCode, false );

            setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
         }
         else if (payToEntity.strip().upperCase() == PAY_TO::BRANCH)
         {
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BrokerCode, brokerCode, false );
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BranchCode, branchCode, false );

            setParameter (MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
            setParameter (MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
         }
         else if (payToEntity.strip().upperCase() == PAY_TO::SALESREP)
         {
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BrokerCode, brokerCode, false );
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::BranchCode, branchCode, false );
            getParent()->getField(this, IFASTBP_PROC::SETTLEMENT_LIST, 
               ifds::SlsrepCode, slsrepCode, false );

            setParameter (MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
            setParameter (MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
            setParameter (MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
         }
      }

      E_COMMANDRETURN eRtn = invokeCommand(getParent(), 
         CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

      if (eRtn != CMD_CANCEL)
      {
         if (m_btn_bankBene.GetCheck () == 1)
         {
            OnRdBeneficiary();
         }
         else
         {
            OnRdCorrespondent();
         }
         lockRdCorrespondent();
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
LRESULT SettlementDlg::OpenSelectAddressDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      DString dstrShrNum;

      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::ShrNum, dstrShrNum,false);      
      setParameter( ADDRLIT::SETTLEMENT, I_("YES") );
      dstrShrNum.strip();

      setParameter( ADDRLIT::SHAREHOLDER_NUM, dstrShrNum );


      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrAddressKey;

               getParameter( ADDRLIT::ADDRESS_KEY, dstrAddressKey );
               if( dstrAddressKey != NULL_STRING )
               {
                  getParent()->setField(this,IFASTBP_PROC::SETTLEMENT_LIST,SETTL_PROC::COPY_ADDRESS,dstrAddressKey);
                  loadAddressInfo();

               }
               break;
            }
         case CMD_CANCEL:
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
   return(0);
}

//*******************************************************************************
void SettlementDlg::loadAddressInfo()
{
   LoadControl( IDC_EDT_ADDR_CODE );
   LoadControl( IDC_EDT_ADDRESS_NAME1 );
   LoadControl( IDC_EDT_ADDRESS_NAME2 );
   LoadControl( IDC_EDT_ADDRESS_LINE );
   LoadControl( IDC_EDT_POSTCODE );
   LoadControl( IDC_CMB_COUNTRYCODE );

}
//**********************************************************************************
void SettlementDlg::EnableControls(bool bEnable )
{
   GetDlgItem(IDC_CHK_SETTLE_ALL)->EnableWindow(bEnable);
   GetDlgItem(IDC_CHK_SETTLE_ONLY)->EnableWindow(bEnable);
   GetDlgItem(IDC_RD_TOTAL_ALL)->EnableWindow(bEnable);
   GetDlgItem(IDC_RD_TOTAL_SETTLE)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_PAY_TYPE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_SUPPRESS_CODE)->EnableWindow(bEnable); 
   GetDlgItem(IDC_CMB_SETTLE_METHOD)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_DELIVERY_MOTHOD)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_PAYMENT_METHOD)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_FILE_PROCESSOR)->EnableWindow(bEnable);
   GetDlgItem(IDC_DTP_VALUE_DATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_BANK_CHARGES)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DETAIL)->EnableWindow(bEnable);

}


//*************************************************************************************
void SettlementDlg::ClearEnableChildControls( )
{
   int iNum = getParent()->getNumberOfItemsInList( this,IFASTBP_PROC::SETTLEMENT_LIST);
   bool bEnable = iNum > 0;
   ConnectControlsToData(IDC_SETTLEMENT_LIST,iNum > 0 );
   
   DisplayBankAddress();

   GetDlgItem( IDC_BTN_DETAIL )->EnableWindow(bEnable);
   GetDlgItem( IDC_BTN_RESET )->EnableWindow(bEnable);
   GetDlgItem( IDC_GRID_ATTRIB )->EnableWindow(bEnable);
   if( !bEnable )
   {

      GetDlgItem( IDC_RD_BENEFICIARY )->EnableWindow(false);
      GetDlgItem( IDC_RD_CORRESPONDENT )->EnableWindow(false);
   }
}

//********************************************************************************
bool SettlementDlg::GetDataForControl( UINT controlID,
                                       DString &strValueOut,
                                       bool bFormatted,
                                       int index ) const
{
   bool bRet = false;
   switch( controlID )
   {
      case IDC_CMB_SETTLE_METHOD:   


         break;

      case IDC_TXT_NBR_RECORDS:
         if( m_bTotal )
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,
                                  SETTL_PROC::TOTAL_COUNT,strValueOut,true  );

         }
         else
         {
            getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,
                                  SETTL_PROC::TOTAL_COUNT_SETTLE,strValueOut,true );

         }
         bRet = true;
         break;
      case IDC_EDT_ADDR_CODE:    
         getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,
                               ifds::AddrCode,strValueOut,false  );
         bRet = true;
         break;
/*	
   case IDC_CMB_FILE_PROCESSOR:		
    ConnectControlToData(IDC_CMB_FILE_PROCESSOR,true );
    getParent()->getField(this,SETTL_PROC::SETTLEMENT_LIST,
      ifds::ACHProcessor,strValueOut,false	);
    bRet = true;

    break
*/
   }

   return(bRet);

}
//***********************************************************************************
void SettlementDlg::OnBtnDetail()
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDetail" ) );

   DString dstrTransId,dstr;
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::TransId, dstrTransId,false);      
      setParameter( I_("ReqTransid0"), dstrTransId );
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::FundCode, dstr,false);      
      setParameter( I_("FundCode"), dstr );
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::ClassCode, dstr,false);      
      setParameter( I_("ClassCode"), dstr );
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::AccountNum, dstr,false);      
      setParameter( I_("AccountNum"), dstr );

      setParameter( I_("FromSettlementScreen"), I_("Y"));

      eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_SUPPORT, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         case CMD_CANCEL:
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
}

//***********************************************************************************
void SettlementDlg::lockRdCorrespondent()
{
   DString dstrCorrespInfo;
   getParent()->getField (this, IFASTBP_PROC::SETTLEMENT_LIST, SETTL_PROC::CORRESPONDENT_INFO, dstrCorrespInfo );
   if( dstrCorrespInfo == YES )
      GetDlgItem( IDC_RD_CORRESPONDENT )->EnableWindow ( true );
   else
      GetDlgItem( IDC_RD_CORRESPONDENT )->EnableWindow ( false );
}

//******************************************************************************
LRESULT SettlementDlg::OpenIdnAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );
   try
   {
      switch( getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_IDENT_ACC,PROC_SUPPORT ) )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstAcctNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstAcctNum );
               dstAcctNum.strip();
               bool bRetVal = SetControlText( IDC_EDT_ACCOUNT_NUMBER, dstAcctNum );
               BaseControl* pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_ACCOUNT_NUMBER ));
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();
               if( !bRetVal )
               {
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

//*******************************************************************************************
bool SettlementDlg::ListViewControlFilter( long lSubstituteId, const DString *strKey  )

{
   if( lSubstituteId == ifds::SettlementTotalHeading.getId() )
   {
      if( IsDlgButtonChecked(IDC_RD_TOTAL_SETTLE) )
      {
         DString dstrCount;
         getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_TOTAL_LIST,ifds::CountTotalSettel,dstrCount);
         dstrCount.strip().stripAll( I_CHAR( ',' ) );      
         int iCount = dstrCount.asInteger();
         if( iCount > 0 )
            return(true);
         else
         {
            LoadControl(IDC_TXT_NBR_RECORDS);       
            return(false);
         }
      }
   }
   return(true);
}
//******************************************************************************
void SettlementDlg::checkPermissionForInqUpdate()
{
   DString dstrInq,dstrUpdate;
   getParent()->getField(this, IFASTBP_PROC::SETTLEMENT,SETTL_PROC::PERMIT_INQ,dstrInq);
   getParent()->getField(this, IFASTBP_PROC::SETTLEMENT,SETTL_PROC::PERMIT_UPDATE,dstrUpdate);
   GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(dstrInq == YES && !m_bAlreadySearch );
//	GetDlgItem(IDC_BTN_MORE)->EnableWindow(dstrInq == YES);

}

//*****************************************************************************
bool SettlementDlg::GridControlFilter( UINT ctrlId, const DString &rowKey )
{
	if( ctrlId == IDC_SETTLEMENT_LIST && m_bSettleOnly )
	{
		DString dstrSettle;
      getParent()->getField(this,IFASTBP_PROC::SETTLEMENT_LIST,ifds::Settled, dstrSettle,false);
		dstrSettle.strip().upperCase();
		if( dstrSettle == NO )
		{
			return false;
		}		
	}
	return true;
}


//********************************************************************************
void SettlementDlg::OnChkExcludeStopSettle()
{
	UpdateData();
	DString dstrExcludeStopSettle;

	dstrExcludeStopSettle = m_bExcludeStopSettle ? I_("Y"):I_("N");
	getParent()->setField(this, IFASTBP_PROC::SETTLEMENT, ifds::ExcludeStopSettle, dstrExcludeStopSettle, false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SettlementDlg.cpp-arc  $
// 
//    Rev 1.76   Apr 27 2012 09:54:22   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.75   Apr 22 2011 09:59:28   dchatcha
// IN# 2427099 - VT27548:PO17516FN02 - EPA Settlement - Total Redemption Amnt shows Zero, take out code due to there is code fix on view side.
// 
//    Rev 1.74   Mar 28 2011 06:47:26   kitticha
// IN#2473886 - More Button No Longer Working On Settlement Screen.
// 
//    Rev 1.73   Feb 25 2011 18:55:32   dchatcha
// IN# 2427099 - VT27548:PO17516FN02 - EPA Settlement - Total Redemption Amnt shows Zero.
// 
//    Rev 1.72   Dec 09 2010 15:15:08   jankovii
// IN 2339013 - P0175778: Uptreaming QA testing
// 
//    Rev 1.71   Dec 01 2010 04:28:30   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.70   Nov 25 2010 14:15:16   jankovii
// PET175778FN01 - Upstreaming Phase 2
// 
//    Rev 1.69   Jul 05 2010 02:26:00   dchatcha
// IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
// 
//    Rev 1.68   Aug 14 2009 11:03:02   dchatcha
// PET 156681 - FN 14 - Investor Authorization, Settlement screen issue.
// 
//    Rev 1.67   06 Aug 2009 17:20:10   popescu
// Incident 1788541 - fixed regression issue on the settlement screen
// 
//    Rev 1.66   29 Jul 2009 11:15:52   popescu
// Incident 1746600 - fixed grid refresh and added wait cursor - synch-up
// 
//    Rev 1.65   Jul 28 2009 07:26:50   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
// 
//    Rev 1.64   Jul 24 2009 01:36:20   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
// 
//    Rev 1.63   May 28 2009 06:39:10   wutipong
// IN1608629 - Aimprod RTS error : Disable the settlement button on the trans history dialog only when the dialog is open from settlement dialog. -- Sync Up
// 
//    Rev 1.62   May 14 2009 13:07:32   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.61   May 12 2009 13:54:44   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.60   Mar 30 2007 14:00:00   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.58   Mar 14 2007 14:37:14   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.57   Sep 15 2005 15:15:06   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.56   May 24 2005 16:35:14   porteanm
// PET OPC Confirm Reprint - Call Transaction History Dlg as non-Modal.
// 
//    Rev 1.55   Apr 25 2005 17:52:20   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.54   Dec 08 2004 15:47:42   hernando
// PET1117 FN06 - Added FundISIN and FundWKN to GetCellProperties.
// 
//    Rev 1.53   Dec 02 2004 16:27:18   yingbaol
// PTS10010256:refresh count in  total list when reset button is clicked.
// 
//    Rev 1.52   Oct 12 2004 13:41:02   YINGBAOL
// PTS10034502: initialize settleAll value to false.
// 
//    Rev 1.51   Sep 07 2004 15:02:42   VADEANUM
// PET 1094 FN4 - Activest Bank Interface.
// 
//    Rev 1.50   Dec 23 2003 14:02:28   popescu
// Synch-up with 1.48.1.0
// CIBC Pet809, FN13, clean-up, moved the banking info checks to the financial institution level
// 
//    Rev 1.49   Oct 20 2003 11:21:54   popescu
// The account num for invoking the banking instructions process should be read from the settlement list
// 
//    Rev 1.48   Sep 03 2003 11:20:42   YINGBAOL
// Filtre list item at GUI layer and solving reset issue
// 
//    Rev 1.47   Aug 02 2003 11:33:52   popescu
// set account num as param for settlement banking
// 
//    Rev 1.46   Jun 10 2003 16:11:38   popescu
// Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
// 
//    Rev 1.45   May 23 2003 10:04:40   popescu
// Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
//    Rev 1.44   May 22 2003 14:14:24   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.43   Mar 21 2003 18:40:48   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.42   Feb 17 2003 11:11:20   sanchez
// modified ReInitControl ( BankTextControls [0], idContainer, idField ); (pass idField instead of "ifds::BankIdType" in
// SettlementDlg::setupBankControls() for ticket#10013651)
// 
//    Rev 1.41   Jan 14 2003 15:07:06   ZHANGCEL
// Fix crash whenever the bank information are missing
// 
//    Rev 1.40   Nov 19 2002 10:59:58   YINGBAOL
// uncomment  SettlePermCode field
// 
//    Rev 1.39   Nov 06 2002 10:32:54   YINGBAOL
// sync. up release 49
// 
//    Rev 1.38   Oct 09 2002 23:56:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.37   Oct 08 2002 11:54:04   YINGBAOL
// fix warning when compiling
// 
//    Rev 1.36   Oct 04 2002 11:54:52   HSUCHIN
// syncup with 1.34.1.0
// 
//    Rev 1.35   Sep 19 2002 14:04:48   YINGBAOL
// GridWnd change sync
// 
//    Rev 1.34   Sep 13 2002 14:58:28   ZHANGCEL
// Disable <More> button at the begaining of the screen showing up
// 
//    Rev 1.33   Sep 11 2002 09:53:36   KOVACSRO
// Added m_strUserAccessCode
// 
//    Rev 1.32   Aug 29 2002 20:09:28   SMITHDAV
// CellProperties fixes
// 
//    Rev 1.31   Aug 29 2002 18:28:00   SMITHDAV
// Additional fixes.
// 
//    Rev 1.30   Aug 29 2002 18:16:08   SMITHDAV
// Additional FieldId fixes.
// 
//    Rev 1.29   Aug 29 2002 12:57:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.28   Aug 16 2002 13:51:24   YINGBAOL
// check permission for Setttlement
// 
//    Rev 1.27   Aug 09 2002 11:18:18   YINGBAOL
// add filtre function to total settle list
// 
//    Rev 1.26   Aug 08 2002 16:43:56   YINGBAOL
// address code enhancement
// 
//    Rev 1.25   Aug 08 2002 11:18:46   KOVACSRO
// Release 48: Added bFormatted parameter to GetCellValue
// 
//    Rev 1.24   Jul 09 2002 15:01:00   YINGBAOL
// fix TransNo etc....
// 
//    Rev 1.23   Jul 05 2002 13:40:12   YINGBAOL
// add confirm settlement dialog
// 
//    Rev 1.22   Jun 27 2002 13:25:16   YINGBAOL
// fix reset issue etc.
// 
//    Rev 1.21   Jun 24 2002 13:28:36   YINGBAOL
// only numeric values are allowed for wire number
// 
//    Rev 1.20   Jun 21 2002 14:43:54   YINGBAOL
// promote condition
// 
//    Rev 1.19   Jun 21 2002 13:14:42   YINGBAOL
// add  setDlgTitle
// 
//    Rev 1.18   Jun 20 2002 14:10:34   YINGBAOL
// add F4 for Account Search
// 
//    Rev 1.17   Jun 17 2002 15:15:18   YINGBAOL
// fix Bank display issue
// 
//    Rev 1.16   Jun 17 2002 12:04:34   HSUCHIN
// bug fix for bank info screen dynamics
// 
//    Rev 1.15   Jun 16 2002 14:07:42   HSUCHIN
// added functionality to disable corresponding bank radio
// 
//    Rev 1.14   Jun 15 2002 15:50:18   YINGBAOL
// sort list and force to save data when set search as default button
// 
//    Rev 1.13   Jun 14 2002 16:27:44   YINGBAOL
// add ExpGNSettle
// 
//    Rev 1.12   Jun 14 2002 14:44:34   YINGBAOL
// populate error message when no datda find
// 
//    Rev 1.11   Jun 14 2002 10:41:04   HSUCHIN
// sync fix to bank display
// 
//    Rev 1.10   Jun 14 2002 10:38:46   YINGBAOL
// change ReqTransid to ReqTransid0
// 
//    Rev 1.9   Jun 13 2002 17:08:32   HSUCHIN
// completed banking support
// 
//    Rev 1.8   Jun 13 2002 15:51:28   YINGBAOL
// change view 200 and launch other screen
// 
//    Rev 1.7   Jun 12 2002 17:10:28   YINGBAOL
// add logic for total count, more/detail button
// 
//    Rev 1.6   Jun 11 2002 11:46:08   YINGBAOL
// more Function added
// 
//    Rev 1.5   Jun 08 2002 13:28:50   HSUCHIN
// added preliminary banking support
// 
//    Rev 1.4   Jun 07 2002 17:02:12   YINGBAOL
// check in for chin
// 
//    Rev 1.3   Jun 06 2002 16:06:26   YINGBAOL
// save work
// 
//    Rev 1.2   Jun 04 2002 10:47:00   YINGBAOL
// save work
// 
//    Rev 1.1   May 31 2002 10:33:16   YINGBAOL
// Resource change
// 
//    Rev 1.0   May 30 2002 11:02:54   YINGBAOL
// Initial revision.
 * 
 *  

 * 
 */





