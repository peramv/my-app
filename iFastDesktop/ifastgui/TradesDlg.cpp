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
//    Copyright 2000 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : TradesDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July, 2004
//
//----------------------------------------------------------
//
// ^CLASS  : TradesDlg
//
//
//******************************************************************************
#include "stdafx.h"
#include <assert.h>
#include <ifastcsi\ifastcsi.h>
#include <ifastcsi\csisession.h>

#include "mfdstc.h"
#include "dstcview.h"
#include "tradesdlg.h"
//ui's
#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\dstdatetime.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dsttabctrl.h>
#include <ifastcbo\financialinstitution.hpp>
//cbo's
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\FundDetail.hpp>
#include <ifastcbo\CurrencyClass.hpp>

//bp's
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastbp\fillsearchcriteriaprocessincludes.h>
#include <ifastbp\searchprocessincludes.h>
#include <ifastbp\tradesprocessincludes.h>
#include <ifastbp\tradesprocess.hpp>
//awd
#include <ifastawd\DSTCAWDSession.hpp>


//business processes to be invoked
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SETTLEMENT_LOCATION_TRADE;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_DILUTION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SAVINGS_DIRECTIVE;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_CLONE_ACCOUNT_BROWSER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_RRIF_LIF_LRIF_INFO;
extern CLASS_IMPORT const I_CHAR *CMD_GUI_ACCOUNT_DETAILS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_RESP_BENEF_ALLOCATION_LIST;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_RESP_TRANSFER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_GRANT_CONTRIB;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_PSE_EAP;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_MATSWP_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_GIA_INVEST_ATTRIBS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_GI_INVESTMENT_DETAILS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_ESTATE_ALLOCATION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_ALERT_MESSAGES;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_REMARKS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_RDSP_TRANSFER;

//this gui process
extern CLASS_IMPORT const I_CHAR *CMD_GUI_TRADES;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradesDlg > dlgCreator (CMD_GUI_TRADES);

#ifdef   _DEBUG
   #define  new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR* const CLASSNAME                   = I_("TradesDlg");
   const I_CHAR* const LV_TRADES                   = I_("ListViewTrades");
   const I_CHAR* const LV_ALLOCATIONS              = I_("ListViewAllocations");
   const I_CHAR* const LV_ESTATE_ALLOCATION        = I_("ListViewAllocations");
   const I_CHAR* const LV_SPLIT_COMMISSIONS        = I_("ListViewSplitCommissions");
   const I_CHAR* const LV_DILUTION_LIST            = I_("ListViewDilutions");
   const I_CHAR* const LV_MAT_INSTR                = I_("ListViewMatInstr");
   const I_CHAR* const LV_SPLIT_TRADE_PAY_INSTRUCT = I_("ListPayInstruct");
   const I_CHAR* const LV_MULTI_SETTLEMNT_LOCATIONS= I_("MultipleSettleLocations");
   const I_CHAR* const LV_BENEFICIARY_ALLOCATION   = I_("BeneficiaryAllocation");
   const I_CHAR* const LV_RESP_TRANSFERS           = I_("RESPTransfers");
   const I_CHAR* const GRD_TRADE_ATTRIBUTES        = I_("TradeAttributesGrid");
   const I_CHAR* const GRD_FEES                    = I_("FeesGrid");
   const I_CHAR* const LV_SAV_DIRECTIVE            = I_("SavingsDirective");
   const I_CHAR* const CLEARING                    = I_("R"); 
   const I_CHAR* const DECIMAL_DIGITS              = I_("DecimalDigits");
   const I_CHAR* const CALLER                      = I_("Caller");
   const I_CHAR* const DEPOSIT_TYPE                = I_("DepositType"); 
   const I_CHAR* const RED_CODE                    = I_("RedCode");
   const I_CHAR* const FROM_AWD                    = I_("FromAWD");
   const I_CHAR* const TRADE_DATE                  = I_("EffectiveDate"); //P0184541_FN01_InvescoQESItrans,ToDo: check if remove ->ok?
   const I_CHAR* const LV_GI_INVEST                = I_("GIInvestments");
   const I_CHAR* const ALLOWED_CHARACTERS		   = I_("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,-_/\\{}[]:;");
   const I_CHAR* const ACCOUNT_NUM                 = I_("AccountNum");
   const I_CHAR* const TRANSID	                   = I_("TransId");
   const I_CHAR* const YES   	                   = I_("Y");
   const I_CHAR* const NO   	                   = I_("N");
   const I_CHAR* const RDSP_TAX_TYPE			   = I_("RS");
   const UINT     NO_CONTROL                       =  0x00000;
   const UINT     FIRST_TAB_ITEM                   =  0x00000;
}

namespace TRADE_CONTROLS
{
//group of controls with fields part of a trade object 
   const UINT TRADE = 1;
//group of controls with fields part of a trade object (one side)
   const UINT ONE_SIDE = 2;
//group of controls with fields part of a trade object (from side)
   const UINT FROM_SIDE = 3;
//group of controls with fields part of a trade object (to side)
   const UINT TO_SIDE = 4;
//group of controls with fields part of an account object (one side)
   const UINT ACCOUNT = 5; 
//group of controls with fields part of an account object (from side)
   const UINT ACCOUNT_FROM = 6;
//group of controls with fields part of an account object (to side)
   const UINT ACCOUNT_TO = 7;
//group of controls with fields part of a shareholder object (one side)
   const UINT SHAREHOLDER = 8; 
//group of controls with fields part of a shareholder object (from side)
   const UINT SHAREHOLDER_FROM = 9; 
//group of controls with fields part of a shareholder object (to side)
   const UINT SHAREHOLDER_TO = 10;
//group of controls with fields part of an address object (one side)
   const UINT ADDRESS = 11; 
//group of controls with fields part of an address object (from side)
   const UINT ADDRESS_FROM = 12; 
//group of controls with fields part of an address object (to side)
   const UINT ADDRESS_TO = 13;
//group of controls with fields part of a bank instructions object
   const UINT BANK = 14; 
//group of controls with fields part of a shareholder address
   const UINT SHAREHOLDER_ADDRESS = 15;
//account field
   const UINT ACCOUNT_FIELD = 16;
//account from fields
   const UINT ACCOUNT_FROM_FIELD = 17;
//account to field
   const UINT ACCOUNT_TO_FIELD = 18;
//tax rates controls
   const UINT TAX_RATES = 19;
//tax rates control check
   const UINT CHK_TAX_RATES = 20;
//trade date control
   const UINT TRADE_DATE = 21;
//settle location tab controls
   const UINT SETTLE_LOCATION = 22;
//eusd
   const UINT EUSD = 23;
//settle location 'TO' tab controls
   const UINT SETTLE_LOCATION_TO = 24;
//settle location 'TO' tab controls
   const UINT PSE_EAP = 25;
//tax rates for IWT
   const UINT IWT_TAX_RATES = 26;
//GIA ATTRIBT
   const UINT GIA_ATTRIB = 27;
//G1G2Details
   const UINT G1G2 =28;
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRADE_TAX_RATE_OVERRIDE;
   extern CLASS_IMPORT I_CHAR * const SAVINGS_DIRECTIVE;
   extern CLASS_IMPORT I_CHAR * const CLONE_ACCOUNT;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId GRRepayReason; 
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonCommon;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonQESI;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonRDSP;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramLenList;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramTypeList;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramYearList;
   extern CLASS_IMPORT const BFTextFieldId MatSweepInstructListHeading;
   extern CLASS_IMPORT const BFTextFieldId GIRedemOrder;
   extern CLASS_IMPORT const BFTextFieldId RightToCancel; 
   extern CLASS_IMPORT const BFTextFieldId LV_EstateAllocation;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId SDRTExemptCode;
   extern CLASS_IMPORT const BFTextFieldId AWDFieldFlag;
   extern CLASS_IMPORT const BFTextFieldId HighRiskDispMode;
   extern CLASS_IMPORT const BFTextFieldId AlertViewed;
   extern CLASS_IMPORT const BFTextFieldId RemarkAlertExists;
   extern CLASS_IMPORT const BFTextFieldId AlertMessageExists;
   extern CLASS_IMPORT const BFTextFieldId TrackTrActive;
   extern CLASS_IMPORT const BFNumericFieldId AltFndIdntfr;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFTextFieldId FullMoneyOutIndc;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFDateFieldId RDSPPaymtDate;
}

namespace MFCAN_IP_PARAM
{
  const I_CHAR * const ACCOUNT_TO         = I_("AccountTo");
}

namespace ALERT_MSG_PARAM
{
    extern CLASS_IMPORT I_CHAR * const ACCOUNT_NUM;
    extern CLASS_IMPORT I_CHAR * const FROM_SCREEN;
    extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_NUM;
}

namespace ALERT_MSG_OPENED_FROM
{
    extern CLASS_IMPORT I_CHAR * const TRADE;
}

typedef struct 
{
   public: const UINT	STATIC_LABEL ;
           const UINT   EDIT_CONTROL ;

}TAB_CONTROL_FIELD_MAPPING; 

//the controls are in IDD_TRADES2G1G2_HELPER
const TAB_CONTROL_FIELD_MAPPING G1G2DetailsTabControls[] =   
{  
    // LABEL                      // EDIT CONTROL
    { IDC_STC_LBL_G1_UNITS ,        IDC_EDT_G1_UNITS           } , 
    { IDC_STC_LBL_G2_UNITS ,        IDC_EDT_G2_UNITS           } , 
    { IDC_STC_LBL_G1_BALANCE ,      IDC_TXT_G1_BALANCE         } ,
    { IDC_STC_LBL_G2_BALANCE ,      IDC_TXT_G2_BALANCE         } ,  
};
int  numG1G2DetailsTabControls = sizeof(G1G2DetailsTabControls)/sizeof( TAB_CONTROL_FIELD_MAPPING );   

BEGIN_MESSAGE_MAP (TradesDlg, BaseMainDlg)
//{{AFX_MSG_MAP (TradesDlg)
ON_BN_CLICKED (IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED (IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED (IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED (IDC_BTN_HISTORY, OnBtnHistory)
ON_BN_CLICKED (IDC_BTN_BATCH, OnBtnBatch)
ON_BN_CLICKED (IDC_BTN_CLONE_ACCOUNT, OnBtnCloneAcct)
ON_BN_CLICKED (IDC_BTN_TAB_INFO_DETAILS, OnBtnInfoDetails)
ON_BN_CLICKED (IDC_BTN_TAB_FEES_DETAILS, OnBtnFeesDetails)
ON_BN_CLICKED (IDC_CHK_OVERRIDE, OnChkOverride)
ON_BN_CLICKED (IDC_CHK_OVERRIDE_TIS, OnChkOverrideTIS)
ON_BN_CLICKED (IDC_CHK_OVERRIDE_COST, OnChkOverrideCost)
ON_MESSAGE (UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE (UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE (UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
ON_MESSAGE (UM_OPENSELECTADDRESSDLG, OpenAddrBookDlg)
ON_MESSAGE (WM_LAUNCH_IDENT_ACC, OpenAccountSearchDlg)
ON_MESSAGE (UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg)
ON_MESSAGE (UM_OPENASSOCIDHELPER, OpenAssocTransIdHelper)
ON_MESSAGE (UM_OPENEXTERNALINSTITUTION, OpenExternalInstitutionSearchDlg)
ON_NOTIFY (NM_DBLCLK, IDC_LV_ALLOCATIONS, OnDblclkLvAllocations)
ON_NOTIFY (NM_DBLCLK, IDC_LV_SPLIT_COMMISSIONS, OnDblclkLvSplitCommissions)
ON_NOTIFY (NM_KILLFOCUS, IDC_DTP_SETTLE_DATE, OnKillFocusSettleDate)
ON_BN_CLICKED(IDC_BTN_ALERT_MESSAGES, OnBtnAlertMessage)

//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

//*****************************************************************************
//Publicmethods
//*****************************************************************************
TradesDlg::TradesDlg ( CWnd* pParent, 
                       GenericInterfaceContainer* pGIC, 
                       GenericInterface* pGIParent, 
                       const Command& rCommand)
: BaseMainDlg ( TradesDlg::IDD, 
                pParent, 
                pGIC, 
                pGIParent, 
                rCommand,
                CLASSNAME), 
m_strMarket (NULL_STRING),
m_accountNum (NULL_STRING),
m_strCurrentTabInfoPage (NULL_STRING),
m_strCurrentTabFeesPage (NULL_STRING),
m_pAttributesGrdWnd (NULL),
m_pFeesGrdWnd (NULL),
m_pFeesTabCtrl (NULL),
m_pInfoTabCtrl (NULL),
m_pCWndF4Focus (NULL),
m_initialSettleDate (NULL_STRING),
m_initialSettleInDate (NULL_STRING),
m_bSettleDateOverriden (false),
m_bTradeListSelectionInProgress (false),
m_bAllocationListSelectionInProgress (false),
m_bEstateAllocationListSelectionInProgress(false),
m_bSplitCommissionListSelectionInProgress (false),
m_bRepInfoPageRegistered (false),
m_bRemarksPageRegistered (false),
m_bFeesPageRegistered (false),
m_bSearchInProgress (false),
m_bSettleDateKillFocusInProgress (false),
m_popSalesRepCreateQuestion (false),
m_bMaturityInstrSelectionInProgress (false),
m_bDilutionListSelectionInProgress (false),
m_bInvestmentDetailsListSelectionInProgress(false),
m_bEUSDPageRegistered (false),
m_bPayInstructSelectionInProgress (false),
m_bMultipleSettleLocSelectionInProgress (false),
m_bRESPBenefAllocationInProgress (false),
m_bRESPTransfersInProgress (false),
m_bG1G2PageRegistered(false),
m_initialCashDate (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME,NULL_STRING);
   //{{AFX_DATA_INIT (TradesDlg)
   //}}AFX_DATA_INIT
   m_strMarket = DSTCommonFunctions::getMarket ();  
}

//*****************************************************************************
void TradesDlg::DoDataExchange ( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange (pDX);
   //{{AFX_DATA_MAP (TradesDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY TradesDlg::doInit ()
{
   TRACE_METHOD (CLASSNAME, DOINIT);
   getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, m_accountNum);
   getParameter (MFCAN_IP_PARAM::CALLER, m_Caller);
   return NO_CONDITION;
}

//*****************************************************************************
BOOL TradesDlg::OnInitDialog () 
{
   TRACE_METHOD (CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog ();
   
   if (m_Caller == FROM_AWD)
   {
		MoveDialog(GUIPOS_DESKTOPBOTTOM, 0);            
   }

//show/hide controls based on the market
   return TRUE;
}

//*****************************************************************************
void TradesDlg::OnPostInitDialog ()
{
   TRACE_METHOD (CLASSNAME,ONPOSTINITDIALOG);
   CWaitCursor wait;

   DSTCWorkSession *pDSTCWorkSession = 
                  dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
   
   DString dstrAltFndIdntfr;
   pDSTCWorkSession->getOption(ifds::AltFndIdntfr, dstrAltFndIdntfr, BF::HOST, false );
   dstrAltFndIdntfr.stripAll();

//security access inits
   addBtnAddForPermissionCheck ( IDC_BTN_ADD, 
                                 IDC_LV_TRANSACTIONS);
   addBtnDeleteForPermissionCheck ( IDC_BTN_DELETE, 
                                    IDC_LV_TRANSACTIONS);
//transactions list control, bottom part of the screen   
   AddListControl ( CLASSNAME, 
                    IDC_LV_TRANSACTIONS, 
                    LV_TRADES, 
                    ifds::TradingHeadingSet, 
                    IFASTBP_PROC::TRADES_LIST, 
                    0, 
                    true, 
                    0
   );
//allocations list control
   AddListControl ( CLASSNAME, 
                    IDC_LV_ALLOCATIONS, 
                    LV_ALLOCATIONS, 
                    ifds::Trading_AllocationHeadingSet, 
                    IFASTBP_PROC::FUND_ALLOCATION, 
                    IDC_LV_TRANSACTIONS, 
                    true, 
                    LISTFLAG_NOT_AUTO_ADD
   );
//split commissions list
   AddListControl ( CLASSNAME, 
                    IDC_LV_SPLIT_COMMISSIONS, 
                    LV_SPLIT_COMMISSIONS, 
                    ifds::SplitCommissionDetailsHeadingSet, 
                    IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
                    0, 
                    true
   );
   AddListControl ( CLASSNAME, 
                    IDC_LV_DILUTIONS, 
                    LV_DILUTION_LIST, 
                    ifds::DilutionHeadSet, 
                    DILUTION_LIST, 
                    IDC_LV_TRANSACTIONS, 
                    true, 
                    LISTFLAG_NOT_AUTO_ADD
   );
   
   AddListControl ( CLASSNAME, 
                    IDC_LV_PAY_INSTRUCT, 
                    LV_SPLIT_TRADE_PAY_INSTRUCT, 
                    ifds::TradePayInstructHeadSet, 
                    TRADE_PAY_INSTRUCT_LIST, 
                    IDC_LV_TRANSACTIONS, 
                    true, 
                    LISTFLAG_NOT_AUTO_ADD);

   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      AddListControl ( CLASSNAME, 
                       IDC_LV_MULTIPLE_SETTL_LOCS, 
                       LV_MULTI_SETTLEMNT_LOCATIONS, 
                       ifds::TradeSettleLocationsListHeading, 
                       TRADE_MULTI_SETTLEMENT_LOC_LIST, 
                       IDC_LV_TRANSACTIONS, 
                       true, 
                       LISTFLAG_NOT_AUTO_ADD);
   }
   if (m_strMarket == MARKET_IDS::CANADA)
   {
//resp
      AddListControl ( CLASSNAME, 
                       IDC_LV_BENEFICARY_ALLOCATION, 
                       LV_BENEFICIARY_ALLOCATION, 
                       ifds::RESPBenefAllocHeading,  
                       RESP_BENEF_ALLOC_LIST, 
                       IDC_LV_TRANSACTIONS, 
                       true, 
                       LISTFLAG_NOT_AUTO_ADD);
      AddListControl ( CLASSNAME, 
                       IDC_LV_ACCT_BENEF, 
                       LV_RESP_TRANSFERS, 
                       ifds::RESPTransferHeading,  
                       RESP_TRANSFER_LIST, 
                       IDC_LV_TRANSACTIONS, 
                       true, 
                       LISTFLAG_NOT_AUTO_ADD);

      AddListControl ( CLASSNAME, 
                     IDC_LV_INVESTMENT_DETAILS, 
                     LV_GI_INVEST, 
                     ifds::GIInvestmentDetailsHeading, 
                     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, 
                     0, 
                     true, 
                     LISTFLAG_NOT_AUTO_ADD );
      GetList (IDC_LV_INVESTMENT_DETAILS)->Show (false);

//pse-eap tab
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSE_TYPE, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSETYPE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::PSEProgramTypeList,
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::PSE_EAP);   
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSE_LENGTH, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSELENGTH, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::PSEProgramLenList,
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::PSE_EAP);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSE_YEAR, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PSEYEAR, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::PSEProgramYearList,
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::PSE_EAP); 
      
      GetControl (IDC_STC_PSE_TYPE)->Show (false);
      GetControl (IDC_STC_PSETYPE)->Show (false);
      GetControl (IDC_STC_PSE_LENGTH)->Show (false);
      GetControl (IDC_STC_PSELENGTH)->Show (false);
      GetControl (IDC_STC_PSE_YEAR)->Show (false);
      GetControl (IDC_STC_PSEYEAR)->Show (false);
//Mat Instructions
      AddListControl ( CLASSNAME, 
                       IDC_LV_MAT_INSTR, 
                       LV_MAT_INSTR, 
                       ifds::MatSweepInstructListHeading, 
                       MAT_SWEEP_INSTRUCTIONS_LIST, 
                       IDC_LV_TRANSACTIONS, 
                       true, 
                       LISTFLAG_NOT_AUTO_ADD
      );
//estate allocations list control
   AddListControl ( CLASSNAME, 
                    IDC_LV_ESTATE_ALLOCATION, 
                    LV_ESTATE_ALLOCATION, 
                    ifds::LV_EstateAllocation, 
                    IFASTBP_PROC::ESTATE_ALLOCATION, 
                    IDC_LV_TRANSACTIONS, 
                    true, 
                    LISTFLAG_NOT_AUTO_ADD
   );
//GIA Attrib
      AddControl ( CTRL_STATIC, 
                   IDC_STC_TYPE_OF_INVESTMENT, 
                   CTRLFLAG_GUI_FIELD);
	   AddControl ( CTRL_COMBO, 
                   IDC_CMB_TYPE_OF_INVESTMENT, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::IntInvestType,
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::GIA_ATTRIB);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_TYPE_OF_INT_CALC, 
                   CTRLFLAG_GUI_FIELD);
	   AddControl ( CTRL_COMBO, 
                   IDC_CMB_TYPE_OF_INT_CALC, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::IntCalcMthd,
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::GIA_ATTRIB);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_TERM_OF_DEPOSIT, 
                   CTRLFLAG_GUI_FIELD);
	   AddControl ( CTRL_COMBO, 
                   IDC_CMB_TERM_OF_DEPOSIT, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::InvestTerm,
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::GIA_ATTRIB);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_INT_FREQ, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_COMBO, 
                   IDC_CMB_INT_FREQ_TRADE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::IntCredFreq,
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST,
                   TRADE_CONTROLS::GIA_ATTRIB);
      GetControl (IDC_STC_TYPE_OF_INVESTMENT)->Show (false);
      GetControl (IDC_CMB_TYPE_OF_INVESTMENT)->Show (false);
      GetControl (IDC_STC_TYPE_OF_INT_CALC)->Show (false);
      GetControl (IDC_CMB_TYPE_OF_INT_CALC)->Show (false);
      GetControl (IDC_STC_TERM_OF_DEPOSIT)->Show (false);
      GetControl (IDC_CMB_TERM_OF_DEPOSIT)->Show (false);     
      GetControl (IDC_STC_INT_FREQ)->Show (false);
      GetControl (IDC_CMB_INT_FREQ_TRADE)->Show (false);
   }

//grids
//the attributes grid
   AddGrid ( CLASSNAME, 
             IDC_GRD_TRADE_ATTRIBUTES, 
             GRD_TRADE_ATTRIBUTES, 
             IFASTBP_PROC::TRADES_LIST, 
             IDC_LV_TRANSACTIONS, 
             ifds::TradeAttributesHeading, 
             ifds::TradeAttributesFields
   );
//init the grid variable
   m_pAttributesGrdWnd = GetGrid (IDC_GRD_TRADE_ATTRIBUTES);
   assert (m_pAttributesGrdWnd);
   if (m_pAttributesGrdWnd)
   {
      m_pAttributesGrdWnd->setUseCBOSubstitutions ();
      m_pAttributesGrdWnd->SetRowHeight (0,39,20);

      CGXGridParam* cgxParam = m_pAttributesGrdWnd->GetParam ();

      cgxParam->EnableTrackRowHeight (0);
      cgxParam->EnableMoveRows (FALSE);
      cgxParam->EnableMoveCols (FALSE);
   }
//the fees grid
   AddGrid ( CLASSNAME, 
             IDC_GRD_FEES, 
             GRD_FEES,
             TRANS_FEE_LIST, 
             IDC_LV_TRANSACTIONS, 
             ifds::TradeFeesHeading, 
             ifds::NullFieldId,
             DSTGridWnd::GRID_TYPE::LIST
   );
//init the grid variable
   m_pFeesGrdWnd = GetGrid (IDC_GRD_FEES);
   assert (m_pFeesGrdWnd);
   if (m_pFeesGrdWnd)
   {
      m_pFeesGrdWnd->SetRowHeight (0,39,20);

      CGXGridParam* cgxParam = m_pFeesGrdWnd->GetParam ();
      CGXProperties* pProp = cgxParam->GetProperties( );

      pProp->SetDisplayHorzLines (TRUE);
      pProp->SetDisplayVertLines (TRUE);
   }
//transction type (ED,PW,XR,TR,....)
   AddControl ( CTRL_COMBO, 
                IDC_CMB_TRANSACTION_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::TradesTransType, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                IDC_LV_TRANSACTIONS
   );

   AddControl (CTRL_COMBO, IDC_CMB_BATCH_NMB, IFASTBP_PROC::TRADES_LIST, ifds::BatchName, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST  | CTRLFLAG_COMBO_EDIT, TRADE_CONTROLS::TRADE);
   
   DSTComboBox *pCmbBatchName = dynamic_cast <DSTComboBox*> (GetControl (IDC_CMB_BATCH_NMB));

   if (pCmbBatchName)
   {
      pCmbBatchName->LimitText (15);
   }
//trace number
   AddControl ( CTRL_STATIC, 
                IDC_STC_TRACE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Trace, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::TRADE
   );
//transaction number
   AddControl ( CTRL_STATIC, 
                IDC_STC_TRANS_NUM, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::TransNum, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE
   );
//transaction status (Good/Bad)
   AddControl ( CTRL_COMBO, 
                IDC_CMB_STATUS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::GoodBad, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                TRADE_CONTROLS::TRADE
   );   
//account/fund controls for one sided transaction (purchases, redemptions,...)
//grouping box for account/fund controls
   AddControl ( CTRL_STATIC, 
                IDC_STC_ACCT_FUND_INFO, 
                CTRLFLAG_GUI_FIELD
   );
//account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_ACCOUNT, 
                CTRLFLAG_GUI_FIELD
   );
//account edit box, only allows digits
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ACCOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AccountNum, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ACCOUNT_FIELD
   );
   dynamic_cast <DSTEdit *> (GetControl (IDC_EDT_ACCOUNT))->
         SetAllowedChars (I_("0123456789"));
//alt account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_ALT_ACCOUNT_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//alt account edit control
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ALT_ACCOUNT, 
                ACCOUNT, 
                ifds::AltAccount, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ACCOUNT
   );
//other reference control applies only for Lux markets
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//other reference label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_OTHER_REFERENCE, 
                   CTRLFLAG_GUI_FIELD
      );
//other reference edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_OTHER_REFERENCE, 
                   ACCOUNT, 
                   ifds::XrefNum, 
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::ACCOUNT
      );

      //Override TIS  check box
      AddControl( CTRL_CHECKBOX, 
                  IDC_CHK_OVERRIDE_TIS, 
                  IFASTBP_PROC::TRADES_LIST, 
                  ifds::OverrideTIS, 
                  CTRLFLAG_DEFAULT, 
                  TRADE_CONTROLS::EUSD
      );

      //TIS edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_TIS, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::TIS, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::EUSD
      );

      //Override Cost  check box
      AddControl( CTRL_CHECKBOX, 
                  IDC_CHK_OVERRIDE_COST, 
                  IFASTBP_PROC::TRADES_LIST, 
                  ifds::OverrideCost, 
                  CTRLFLAG_DEFAULT, 
                  TRADE_CONTROLS::EUSD
      );

      //Cost edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_COST, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::Cost, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::EUSD
						 );

      // Don't allow negatives for this control
	   DSTEdit *dstEditTIS = 
         dynamic_cast<DSTEdit *> (GetDlgItem (IDC_EDT_TIS));
      // Don't allow negatives for this control
	   DSTEdit *dstEditCost = 
         dynamic_cast<DSTEdit *> (GetDlgItem (IDC_EDT_COST));

      if (NULL != dstEditTIS)
	   {
			DString dstrPercentageMask = DSTCommonFunctions::getMask (ifds::TIS);
         int iDecimalPointPos = dstrPercentageMask.find (I_("."));
         int iMaxNumDigitsBeforeDecimalPoint = iDecimalPointPos - dstrPercentageMask.length() + iDecimalPointPos + 2;

         dstEditTIS->AllowNonnegativeDecimalNumbers(
            iMaxNumDigitsBeforeDecimalPoint, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
	   }

		if (NULL != dstEditCost)
	   {
		   DString dstrPercentageMask = DSTCommonFunctions::getMask (ifds::Cost);
         int iDecimalPointPos = dstrPercentageMask.find (I_("."));
         int iMaxNumDigitsBeforeDecimalPoint = iDecimalPointPos - dstrPercentageMask.length() + iDecimalPointPos + 2;

         dstEditCost->AllowNonnegativeDecimalNumbers(
            iMaxNumDigitsBeforeDecimalPoint, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
	   }      
   }
//'Fund' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND, 
                CTRLFLAG_GUI_FIELD
   );
//fund number edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FUND_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromFundNumber, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ONE_SIDE

   );
//fund code edit box 
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FUND_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromFund, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ONE_SIDE
   );
//fund 'Class' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND_CLASS, 
                CTRLFLAG_GUI_FIELD
   );
//fund class edit box 
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FUND_CLASS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromClass, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ONE_SIDE
   );
//WKN/ISIN number controls are applicable only for Lux markets
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//'ISIN' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_ISIN, 
                   CTRLFLAG_GUI_FIELD
      );
//ISIN number edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_ISIN, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundISIN, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::ONE_SIDE
      );
//'WKN' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_WKN, 
                   CTRLFLAG_GUI_FIELD
      );
//'WKN' number edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_WKN, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundWKN, 
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::ONE_SIDE
      );
      AddControl ( CTRL_STATIC, 
                   IDC_STC_LFC, 
                   CTRLFLAG_GUI_FIELD
      );
//'LFC' number edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_LFC, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundLFC, 
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::ONE_SIDE
      );
	   AddControl ( CTRL_STATIC, 
                   IDC_STC_CUSIP, 
                   CTRLFLAG_GUI_FIELD
      );
//'CUSIP' number edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_CUSIP, 
                   IFASTBP_PROC::TRADES_LIST, 
				   ifds::CUSIP, 
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::ONE_SIDE
      );
   }
//fund settle units label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND_SETTLE_UNITS_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//fund settle units value
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND_SETTLE_UNITS, 
                ACCOUNT_HOLDINGS, 
                ifds::SettledUnits, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::ONE_SIDE
   );
//fund market value label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND_MKT_VALUE_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//fund market value value
   AddControl ( CTRL_STATIC, 
                IDC_STC_FUND_SETTLE_VALUE, 
                ACCOUNT_HOLDINGS, 
                ifds::SettledValue, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::ONE_SIDE
   );
//account market value label
   AddControl ( CTRL_STATIC, 
                IDC_STC_ACCT_MKT_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//account market value (account balance)
   AddControl ( CTRL_STATIC, 
                IDC_STC_ACCT_MKT_VALUE, 
                ACCOUNT, 
                ifds::AccountBalance, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::ONE_SIDE
   );
//grouping box for shareholder info controls   
   AddControl ( CTRL_STATIC, 
                IDC_STC_SHAREHOLDER_INFO, 
                CTRLFLAG_GUI_FIELD
   );
//'Shareholder' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_SHAREHOLDER_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//shareholder number
   AddControl ( CTRL_STATIC, 
                IDC_STC_SHAREHOLDER, 
                SHAREHOLDER, 
                ifds::ShrNum, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::SHAREHOLDER
   );
//'Address' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_ADDRESS, 
                CTRLFLAG_GUI_FIELD
   );
//shareholder address
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ADDRESS, 
                ADDRESS, 
                ifds::TradeAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK, 
                TRADE_CONTROLS::ADDRESS
   );
//'Cautions' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_CAUTIONS, 
                CTRLFLAG_GUI_FIELD
   );  
//cautions values
   AddControl ( CTRL_COMBO, 
                IDC_CMB_CAUTIONS, 
                CTRLFLAG_GUI_FIELD
   );

//from side for Exchange/Transfer/Rollover,...

//from grouping box
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM, 
                CTRLFLAG_GUI_FIELD
   );
//from account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_ACCOUNT, 
                CTRLFLAG_GUI_FIELD
   );  
//from account edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_ACCOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AccountNum, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::ACCOUNT_FROM_FIELD
   );
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_FROM_ACCOUNT))->
         SetAllowedChars (I_ ("0123456789"));
//from alternate account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_ALT_ACCOUNT_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//from alternate account edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_ALT_ACCOUNT, 
                ACCOUNT, 
                ifds::AltAccount, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::ACCOUNT_FROM
   );
//other reference controls should only apply for Lux markets
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//other 'Ref' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FROM_OTHER_REFERENCE, 
                   CTRLFLAG_GUI_FIELD
      );
//from side other reference edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FROM_OTHER_REFERENCE, 
                   ACCOUNT, 
                   ifds::XrefNum, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::ACCOUNT_FROM
      );
   }
   //fund
//'From Fund' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_FUND, 
                CTRLFLAG_GUI_FIELD
   );
//from fund number edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_FUND_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromFundNumber, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::FROM_SIDE
   );
//from fund code edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_FUND_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromFund, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::FROM_SIDE
   );
//from fund 'class' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_FUND_CLASS, 
                CTRLFLAG_GUI_FIELD
   );
//from fund class edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_FUND_CLASS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromClass, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::FROM_SIDE
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_FUND_SETTLE_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_FUND_SETTLE_UNITS, 
                ACCOUNT_HOLDINGS, 
                ifds::SettledUnits, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::FROM_SIDE
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_FUND_SETTLE_VALUE, 
                ACCOUNT_HOLDINGS, 
                ifds::SettledValue, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::FROM_SIDE
   );
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FROM_ADDRESS, 
                ADDRESS, 
                ifds::TradeAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK,
                TRADE_CONTROLS::ADDRESS_FROM
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_SHAREHOLDER_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_SHAREHOLDER, 
                SHAREHOLDER, 
                ifds::ShrNum, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::SHAREHOLDER_FROM
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_ACCT_MKT_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_ACCT_MKT, 
                ACCOUNT, 
                ifds::AccountBalance, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::FROM_SIDE
   );
   AddControl ( CTRL_STATIC, 
                IDC_STC_FROM_CAUTIONS, 
                CTRLFLAG_GUI_FIELD
   );
   AddControl ( CTRL_COMBO, 
                IDC_CMB_FROM_CAUTIONS, 
                CTRLFLAG_GUI_FIELD
   );
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//from side 'ISIN' label      
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FROM_ISIN, 
                   CTRLFLAG_GUI_FIELD
      );
//from side ISIN number value
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FROM_ISIN, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundISIN, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::FROM_SIDE
      );
//from side 'WKN' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FROM_WKN, 
                   CTRLFLAG_GUI_FIELD
      );
//from side WKN number value
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FROM_WKN, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundWKN, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::FROM_SIDE
      );
//from side 'LFC' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FROM_LFC, 
                   CTRLFLAG_GUI_FIELD
      );
//from side LFC number value
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FROM_LFC, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundLFC, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::FROM_SIDE
      );
	  //from side 'CUSIP' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FROM_CUSIP, 
                   CTRLFLAG_GUI_FIELD
      );
//from side CUSIP number value
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FROM_CUSIP, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::CUSIP, 
                   CTRLFLAG_DEFAULT,  
                   TRADE_CONTROLS::FROM_SIDE
      );
   }

   //to side for Exchange/Transfer/Rollover,...

//to side grouping box
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO, 
                CTRLFLAG_GUI_FIELD
   );
//to side account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_ACCOUNT, 
                CTRLFLAG_GUI_FIELD
   );  
//to side account edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_ACCOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AccountTo, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::ACCOUNT_TO_FIELD
   );
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_TO_ACCOUNT))->
         SetAllowedChars (I_("0123456789"));
//to side alternate account label
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_ALT_ACCOUNT_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//to side alternate account edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_ALT_ACCOUNT, 
                ACCOUNT_TO, 
                ifds::AltAccount, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::ACCOUNT_TO
   );
//other reference controls should only apply for Lux markets
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//to side other 'Ref' label      
      AddControl ( CTRL_STATIC, 
                   IDC_STC_TO_OTHER_REFERENCE, 
                   CTRLFLAG_GUI_FIELD);
//to side other ref edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_TO_OTHER_REFERENCE, 
                   ACCOUNT_TO, 
                   ifds::XrefNum, 
                   CTRLFLAG_DEFAULT,
                   TRADE_CONTROLS::ACCOUNT_TO);
   }
   //fund
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_FUND, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_FUND_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ToFundNumber, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TO_SIDE);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_FUND_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ToFund, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::TO_SIDE);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_FUND_CLASS, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_FUND_CLASS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ToClass, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TO_SIDE);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_FUND_SETTLE_LABEL, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_FUND_SETTLE_UNITS, 
                ACCOUNT_HOLDINGS_TO, 
                ifds::SettledUnits, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TO_SIDE);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_FUND_SETTLE_VALUE, 
                ACCOUNT_HOLDINGS_TO, 
                ifds::SettledValue, 
                CTRLFLAG_DEFAULT,  
                TRADE_CONTROLS::TO_SIDE);   
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TO_ADDRESS, 
                ADDRESS_TO, 
                ifds::TradeAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK,
                TRADE_CONTROLS::ADDRESS_TO);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_SHAREHOLDER_LABEL, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_SHAREHOLDER, 
                SHAREHOLDER_TO, 
                ifds::ShrNum, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::SHAREHOLDER_TO);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_ACCT_MKT_LABEL, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_ACCT_MKT, 
                ACCOUNT_TO, 
                ifds::AccountBalance, 
                CTRLFLAG_NOT_UPDATABLE, 
                TRADE_CONTROLS::TO_SIDE);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TO_CAUTIONS, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_COMBO, 
                IDC_CMB_TO_CAUTIONS, 
                CTRLFLAG_GUI_FIELD);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
//to side 'ISIN' label
      AddControl ( CTRL_STATIC, 
                   IDC_STC_TO_ISIN, 
                   CTRLFLAG_GUI_FIELD
      );
//to side ISIN number edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_TO_ISIN, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FundToISIN, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::TO_SIDE
      );
      DString dstrAltFndIdntfr;
	   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);

   //to side 'WKN' label
         AddControl ( CTRL_STATIC, 
                      IDC_STC_TO_WKN, 
                      CTRLFLAG_GUI_FIELD
         );
   //to side WKN number edit box
         AddControl ( CTRL_EDIT, 
                      IDC_EDT_TO_WKN, 
                      IFASTBP_PROC::TRADES_LIST, 
                      ifds::FundToWKN, 
                      CTRLFLAG_DEFAULT, 
                      TRADE_CONTROLS::TO_SIDE
         );
   //to side 'LFC' label
         AddControl ( CTRL_STATIC, 
                      IDC_STC_TO_LFC, 
                      CTRLFLAG_GUI_FIELD
         );
   //to side LFC number edit box
         AddControl ( CTRL_EDIT, 
                      IDC_EDT_TO_LFC, 
                      IFASTBP_PROC::TRADES_LIST, 
                      ifds::FundToLFC, 
                      CTRLFLAG_DEFAULT, 
                      TRADE_CONTROLS::TO_SIDE
         );
		   //to side 'CUSIP' label
         AddControl ( CTRL_STATIC, 
                      IDC_STC_TO_CUSIP, 
                      CTRLFLAG_GUI_FIELD
         );
   //to side CUSIP number edit box
         AddControl ( CTRL_EDIT, 
                      IDC_EDT_TO_CUSIP, 
                      IFASTBP_PROC::TRADES_LIST, 
                      ifds::ToCUSIP, 
                      CTRLFLAG_DEFAULT, 
                      TRADE_CONTROLS::TO_SIDE
         );

   //   }
   //   else
   //   {
   ////to side 'LFC' label
   //      AddControl ( CTRL_STATIC, IDC_STC_TO_LFC, CTRLFLAG_GUI_FIELD);
   ////to side LFC number edit box
   //      AddControl ( CTRL_EDIT, IDC_EDT_TO_LFC, IFASTBP_PROC::TRADES_LIST, ifds::FundToLFC, CTRLFLAG_DEFAULT, TRADE_CONTROLS::TO_SIDE);
   //   }
   }
//dates /order type
//effective date, trade date
   AddControl ( CTRL_DATE, 
                IDC_DTP_TRADE_DATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::EffectiveDate, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE_DATE
   );
//settlement date
   AddControl ( CTRL_DATE, 
                IDC_DTP_SETTLE_DATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::SettleDate, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
//deposit date
   AddControl ( CTRL_DATE, 
                IDC_DTP_DEPOSIT_DATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::DepositDate, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
//wire/order num
   AddControl ( CTRL_COMBO, 
                IDC_CMB_ORDER_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::OrderType, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST,
                TRADE_CONTROLS::TRADE
   );
//wire number
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ORDER_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::WireOrdNum, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
   dynamic_cast <DSTEdit*> (GetControl (IDC_EDT_ORDER_NBR))->
         SetMaxCharNum (20);
//amount, gross net
   //gross/net 
   AddControl ( CTRL_COMBO, 
                IDC_CMB_GROSS_NET, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::GrossOrNet, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                TRADE_CONTROLS::TRADE
   );
   //amount type
   AddControl ( CTRL_COMBO, 
                IDC_CMB_AMOUNT_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AmtType, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                TRADE_CONTROLS::TRADE
   );
   //amount
   AddControl ( CTRL_EDIT, 
                IDC_EDT_AMOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Amount, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_AMOUNT))->
         SetAllowedChars (I_(".0123456789"));
// The Fees Tab Controls 
//tax rates, only for canadian market
   if (m_strMarket == MARKET_IDS::CANADA)
   {
      //'Federal Tax' label 
      AddControl ( CTRL_STATIC, 
                   IDC_STC_FED_RATE, 
                   CTRLFLAG_GUI_FIELD);  
      //federal tax rate edit box
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FED_RATE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FedRate, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::TAX_RATES);

      // Don't allow negatives for this control
	   DSTEdit *dstEditFedTaxRate = 
         dynamic_cast<DSTEdit *> (GetDlgItem (IDC_EDT_FED_RATE));

      if (NULL != dstEditFedTaxRate)
	   {
		   DString dstrPercentageMask = DSTCommonFunctions::getMask (ifds::FedRate);
         int iDecimalPointPos = dstrPercentageMask.find (I_("."));

         dstEditFedTaxRate->AllowNonnegativeDecimalNumbers(
            iDecimalPointPos, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
	   }
      //'Provincial Tax' label 
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PROV_RATE, 
                   CTRLFLAG_GUI_FIELD
      );
      //provincial tax rate edit box
	   AddControl ( CTRL_EDIT, 
                   IDC_EDT_PROV_RATE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ProvRate, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::TAX_RATES
      );

      // Don't allow negatives for this control
	   DSTEdit *dstEditProvTaxRate = 
         dynamic_cast< DSTEdit * >(GetDlgItem (IDC_EDT_PROV_RATE));

      if (NULL != dstEditProvTaxRate)
	   {
		   DString dstrPercentageMask = DSTCommonFunctions::getMask (ifds::ProvRate);
         int iDecimalPointPos = dstrPercentageMask.find (I_( "." ));

         dstEditProvTaxRate->AllowNonnegativeDecimalNumbers (
            iDecimalPointPos, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
	   }
      //federal rate type
	   AddControl ( CTRL_COMBO, 
                   IDC_CMB_FED_RATE_TYPE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::TransRatePUDFed, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::TAX_RATES
      );
      //provincial rate type
      AddControl ( CTRL_COMBO, 
                   IDC_CMB_PROV_RATE_TYPE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::TransRatePUDProv, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::TAX_RATES
      );
      //override tax check box
      AddControl( CTRL_CHECKBOX, 
                  IDC_CHK_OVERRIDE_TAX, 
                  IFASTBP_PROC::TRADES_LIST, 
                  ifds::OverrideTax, 
                  CTRLFLAG_DEFAULT, 
                  TRADE_CONTROLS::CHK_TAX_RATES
      );
   }
   else if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      //'Provincial Tax' label 
      AddControl ( CTRL_STATIC, 
                   IDC_STC_PROV_RATE, 
                   CTRLFLAG_GUI_FIELD
      );
      //provincial tax rate edit box
	   AddControl ( CTRL_EDIT, 
                   IDC_EDT_PROV_RATE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ProvRate, 
                   CTRLFLAG_DEFAULT, 
                   TRADE_CONTROLS::IWT_TAX_RATES
      );

      // Don't allow negatives for this control
      DSTEdit *dstEditProvTaxRate = 
         dynamic_cast< DSTEdit * >(GetDlgItem (IDC_EDT_PROV_RATE));

      if (NULL != dstEditProvTaxRate)
      {
         DString dstrPercentageMask = DSTCommonFunctions::getMask (ifds::ProvRate);
         int iDecimalPointPos = dstrPercentageMask.find (I_( "." ));

         dstEditProvTaxRate->AllowNonnegativeDecimalNumbers (
            iDecimalPointPos, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
      }
      //provincial rate type
      AddControl ( CTRL_COMBO, 
                   IDC_CMB_PROV_RATE_TYPE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::TransRatePUDProv, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                   TRADE_CONTROLS::IWT_TAX_RATES
      );
      //override tax check box
      AddControl( CTRL_CHECKBOX, 
                  IDC_CHK_OVERRIDE_TAX, 
                  IFASTBP_PROC::TRADES_LIST, 
                  ifds::OverrideTax, 
                  CTRLFLAG_DEFAULT, 
                  TRADE_CONTROLS::CHK_TAX_RATES
      );
      
      if (pDSTCWorkSession->isIWTClient(getDataGroupId()))
      {
         CString cstrChkOverideTaxForIWT = NULL_STRING;
         cstrChkOverideTaxForIWT.LoadString (TXT_OVERRIDE_TAX_FOR_IWT);
         GetDlgItem (IDC_CHK_OVERRIDE_TAX)->SetWindowText (cstrChkOverideTaxForIWT);
      }

   }

// The Informational Tab Controls
//broker/branch/sales rep
//'Broker' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BROKER, 
                CTRLFLAG_GUI_FIELD
   );
//broker code edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BROKER_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Broker, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE
   );
//broker name
   AddControl ( CTRL_STATIC, 
                IDC_STC_BROKER_NAME, 
                BROKER, 
                ifds::BrokerName, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE
   );
//'Branch' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BRANCH, 
                CTRLFLAG_GUI_FIELD
   );  
//branch code edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BRANCH_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Branch, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE
   );
//branch name
   AddControl ( CTRL_STATIC, 
                IDC_STC_BRANCH_NAME, 
                BRANCH,
                ifds::BranchName, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
//'Sls rep' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_SALES_REP, 
                CTRLFLAG_GUI_FIELD
   );
//sls rep code edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_SALES_REP_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::SlsrepCode, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::TRADE
   );
//sls rep name
   AddControl ( CTRL_STATIC, 
                IDC_STC_SALES_REP_NAME, 
                AGENT,
                ifds::SlsrepName, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE
   );
//remarks page 
//remarks edit box
   AddControl ( CTRL_EDIT, 
                IDC_EDT_REMARKS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::RemarksLine, 
                CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP, 
                TRADE_CONTROLS::TRADE
   );
   dynamic_cast<DSTEdit*> (GetControl 
         (IDC_EDT_REMARKS))->SetMaxCharNum (50);
//address page
//address 'Code' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_SHAREHOLDER_ADDR_CODE, 
                CTRLFLAG_GUI_FIELD
   );
//address code edit box, only allow two digits
   AddControl ( CTRL_EDIT, 
                IDC_EDT_SHAREHOLDER_ADDR_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AddrCode, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::SHAREHOLDER_ADDRESS
   );
   dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_SHAREHOLDER_ADDR_CODE))->
         SetMaxCharNum (2);
   dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_SHAREHOLDER_ADDR_CODE))->
         SetAllowedChars (I_("0123456789"));
//shareholder address
   AddControl ( CTRL_EDIT, 
                IDC_EDT_SHAREHOLDER_ADDR, 
                SHAREHOLDER_ADDRESS, 
                ifds::TradeAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK,
                TRADE_CONTROLS::SHAREHOLDER_ADDRESS
   );
//banking page
//'Bank Name' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_NAME_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//bank name value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_NAME, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::InstName, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::BANK
   );
//'Bank Nbr.' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ID_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//bank nbr value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ID, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankIdValue, 
                CTRLFLAG_DEFAULT, 
                TRADE_CONTROLS::BANK
   );
//bank 'Acct Name' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NAME_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//bank acct name value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NAME, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankAcctName, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::BANK
   );
//bank 'Acct Nbr.' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NBR_LABEL, 
                CTRLFLAG_GUI_FIELD
   );
//bank account number value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankAcctNum, 
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::BANK
   );
//settle location fields
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      AddControl ( CTRL_STATIC, 
                   IDC_STC_SETTLE_LOCATION_LABEL, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_SETTLE_LOCATION, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FrSettlLocCode, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_SETTLE_LOCATION_LABEL_TO, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_SETTLE_LOCATION_TO, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ToSettlLocCode, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION_TO);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_CLEARING_METHOD_LABEL, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_CLEARING_METHOD, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FrClearingMethod, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_CLEARING_METHOD_LABEL_TO, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_CLEARING_METHOD_TO, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ToClearingMethod, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION_TO);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_SETTLE_INSTRUCTIONS_CODE, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FrSettlInstrCode, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL_TO, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ToSettlInstrCode, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION_TO);
      AddControl ( CTRL_STATIC, 
                   IDC_STC_DELIVERY_TO_LABEL, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_DELIVERY_2, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FrDeliveryTo, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION);	
      AddControl ( CTRL_STATIC, 
                   IDC_STC_DELIVERY_TO_LABEL_TO, 
                   CTRLFLAG_GUI_FIELD);
      AddControl ( CTRL_EDIT, 
                   IDC_STC_DELIVERY_2_TO, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::ToDeliveryTo, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE,
                   TRADE_CONTROLS::SETTLE_LOCATION_TO);

     GetDlgItem (IDC_STC_DELIVERY_2)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_DELIVERY_2_TO)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_SETTLE_INSTRUCTIONS_CODE)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_CLEARING_METHOD)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_CLEARING_METHOD_TO)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_SETTLE_LOCATION)->EnableWindow (FALSE);
     GetDlgItem (IDC_STC_SETTLE_LOCATION_TO)->EnableWindow (FALSE);
   }
//the info details button, to be registered with all info tab's pages
   AddControl ( CTRL_STATIC, 
                IDC_BTN_TAB_INFO_DETAILS, 
                CTRLFLAG_GUI_FIELD);
//the fees details button, to be registered with all fee tab's pages
   AddControl ( CTRL_STATIC, 
                IDC_BTN_TAB_FEES_DETAILS, 
                CTRLFLAG_GUI_FIELD);

// The Fees Tab Control
   m_pFeesTabCtrl = AddTabControl (CLASSNAME, IDC_TAB_FEES, I_("FeesTab"));
   assert (m_pFeesTabCtrl);
   if (m_pFeesTabCtrl)
   {
      //the fees page
      m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_FEES);
//do not show the grid for now
      GetGrid (IDC_GRD_FEES)->Show (false);
//do not show the allocation list
      GetList (IDC_LV_ALLOCATIONS)->Show (false);
//do not show the estate allocation list
//do not show the splits list
      GetList (IDC_LV_SPLIT_COMMISSIONS)->Show (false);
//in a canadian market do not show the tax rates
      if (m_strMarket == MARKET_IDS::CANADA)
      {
         GetControl (IDC_CHK_OVERRIDE_TAX)->Show (false);
         GetControl (IDC_STC_FED_RATE)->Show (false);
         GetControl (IDC_EDT_FED_RATE)->Show (false);
         GetControl (IDC_CMB_FED_RATE_TYPE)->Show (false);
         GetControl (IDC_STC_PROV_RATE)->Show (false);
         GetControl (IDC_EDT_PROV_RATE)->Show (false);
         GetControl (IDC_CMB_PROV_RATE_TYPE)->Show (false);
         GetList (IDC_LV_ESTATE_ALLOCATION)->Show (false);
      }
      if (m_strMarket == MARKET_IDS::LUXEMBOURG)
      {
         GetControl (IDC_CHK_OVERRIDE_TIS)->Show (false);
         GetControl (IDC_EDT_TIS)->Show (false);
         GetControl (IDC_CHK_OVERRIDE_COST)->Show (false);
         GetControl (IDC_EDT_COST)->Show (false);
         GetControl (IDC_CHK_OVERRIDE_TAX)->Show (false);
         GetControl (IDC_STC_PROV_RATE)->Show (false);
         GetControl (IDC_EDT_PROV_RATE)->Show (false);
         GetControl (IDC_CMB_PROV_RATE_TYPE)->Show (false);
      }

//show the tab cotrol, though
      ShowTabCtrl (IDC_TAB_FEES, true);
   }
//info tab control
   m_pInfoTabCtrl = AddTabControl (CLASSNAME, IDC_TAB_INFO, I_("InfoTab"));
   assert (m_pInfoTabCtrl);
   if (m_pInfoTabCtrl)
   {
//broker/branch/sls rep info page
      m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_REP_INFO);
//do not show rep info controls for now
      GetControl (IDC_STC_BROKER)->Show (false);
      GetControl (IDC_EDT_BROKER_CODE)->Show (false);
      GetControl (IDC_STC_BROKER_NAME)->Show (false);
      GetControl (IDC_STC_BRANCH)->Show (false);
      GetControl (IDC_EDT_BRANCH_CODE)->Show (false);
      GetControl (IDC_STC_BRANCH_NAME)->Show (false);
      GetControl (IDC_STC_SALES_REP)->Show (false);
      GetControl (IDC_EDT_SALES_REP_CODE)->Show (false);
      GetControl (IDC_STC_SALES_REP_NAME)->Show (false);
//remarks page
      m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_REMARKS);
//do not show remarks for now
      GetControl (IDC_EDT_REMARKS)->Show (false);
//do not show banking controls 
      GetControl (IDC_STC_BANK_NAME_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_NAME)->Show (false);
      GetControl (IDC_STC_BANK_ID_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ID)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NAME_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NAME)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NBR_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NBR)->Show (false);
//do not show address controls
      GetControl (IDC_STC_SHAREHOLDER_ADDR_CODE)->Show (false);
      GetControl (IDC_EDT_SHAREHOLDER_ADDR_CODE)->Show (false);
      GetControl (IDC_EDT_SHAREHOLDER_ADDR)->Show (false);
//do not show settle location controls
      if (m_strMarket == MARKET_IDS::LUXEMBOURG)
      {
         GetControl (IDC_STC_SETTLE_LOCATION_LABEL)->Show (false);
         GetControl (IDC_STC_SETTLE_LOCATION_LABEL_TO)->Show (false);
         GetControl (IDC_STC_SETTLE_LOCATION)->Show (false);
         GetControl (IDC_STC_SETTLE_LOCATION_TO)->Show (false);
         GetControl (IDC_STC_CLEARING_METHOD_LABEL)->Show (false);
         GetControl (IDC_STC_CLEARING_METHOD_LABEL_TO)->Show (false);
         GetControl (IDC_STC_CLEARING_METHOD)->Show (false);
         GetControl (IDC_STC_CLEARING_METHOD_TO)->Show (false);
         GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL)->Show (false);
         GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL_TO)->Show (false);
         GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE)->Show (false);
         GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO)->Show (false);
         GetControl (IDC_STC_DELIVERY_2)->Show (false);
         GetControl (IDC_STC_DELIVERY_TO_LABEL)->Show (false);
         GetControl (IDC_STC_DELIVERY_2_TO)->Show (false);
         GetControl (IDC_STC_DELIVERY_TO_LABEL_TO)->Show (false);
      }
//do not show the dilution list
      GetList (IDC_LV_DILUTIONS)->Show (false);
      
//do not show the trade pay instruct list
      GetList (IDC_LV_PAY_INSTRUCT)->Show (false);

      if (m_strMarket == MARKET_IDS::LUXEMBOURG)
      {
         GetList (IDC_LV_MULTIPLE_SETTL_LOCS)->Show (false);
      }

	  if (m_strMarket == MARKET_IDS::CANADA)
     {
         GetList (IDC_LV_MAT_INSTR)->Show (false);
         GetList (IDC_LV_BENEFICARY_ALLOCATION)->Show (false);
         GetList (IDC_LV_ACCT_BENEF)->Show (false); //resp transfers
     }
//in the end show the tab control
      ShowTabCtrl (IDC_TAB_INFO, true);
   }
//purchase total
   AddControl ( CTRL_STATIC, 
                IDC_STC_PURCHASE_TOTAL, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_PURCHASE_TOTAL, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::PurchaseTotal,
                CTRLFLAG_DEFAULT,
                TRADE_CONTROLS::TRADE);

   //Allow only Unsigned Decimal                
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_AMOUNT))
      ->setInputAllowedUnsignedDecimal();
   
   //G1G2-Details tab
   if( m_strMarket == MARKET_IDS::LUXEMBOURG )
   {
       AddControl (CTRL_STATIC, IDC_STC_LBL_G1_UNITS, CTRLFLAG_GUI_FIELD );
       AddControl (CTRL_STATIC, IDC_STC_LBL_G2_UNITS, CTRLFLAG_GUI_FIELD );
       AddControl (CTRL_STATIC, IDC_STC_LBL_G1_BALANCE, CTRLFLAG_GUI_FIELD );
       AddControl (CTRL_STATIC, IDC_STC_LBL_G2_BALANCE, CTRLFLAG_GUI_FIELD );
       AddControl ( CTRL_EDIT, IDC_EDT_G1_UNITS, IFASTBP_PROC::TRADES_LIST, ifds::G1Impact, CTRLFLAG_DEFAULT, TRADE_CONTROLS::G1G2 );
       AddControl ( CTRL_EDIT, IDC_EDT_G2_UNITS, IFASTBP_PROC::TRADES_LIST, ifds::G2Impact, CTRLFLAG_DEFAULT ,TRADE_CONTROLS::G1G2 );
       AddControl ( CTRL_STATIC, IDC_TXT_G1_BALANCE, ACCOUNT_HOLDINGS, ifds::Grp1Shares,CTRLFLAG_DEFAULT,TRADE_CONTROLS::G1G2 );
       AddControl ( CTRL_STATIC, IDC_TXT_G2_BALANCE, ACCOUNT_HOLDINGS, ifds::Grp2Shares,CTRLFLAG_DEFAULT,TRADE_CONTROLS::G1G2);
       dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_G1_UNITS))->SetAllowedChars (I_(".0123456789"));
       dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_G2_UNITS))->SetAllowedChars (I_(".0123456789"));
       dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_G1_UNITS))->setInputAllowedUnsignedDecimal();
       dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_G2_UNITS))->setInputAllowedUnsignedDecimal();     
       showG1G2Controls(false);  
   }    

   GetDlgItem(IDC_BTN_ALERT_MESSAGES)->EnableWindow(false);

   doRefresh (this, NULL);

   CWnd* pRemarksPostWnd = GetDlgItem(IDC_EDT_REMARKS);
   if (NULL != pRemarksPostWnd)
   {
       if (DSTEdit* pDSTEditpRemarksPost = dynamic_cast<DSTEdit*>(pRemarksPostWnd))
       {
           pDSTEditpRemarksPost->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }
}

//******************************************************************************
bool TradesDlg::doRefresh( GenericInterface* rpGICaller, 
                            const I_CHAR* szOriginalCommand)
{
   TRACE_METHOD ( CLASSNAME, 
                  DOREFRESH);
   if (szOriginalCommand == NULL) //from init dialog
   {
   //disable everything
      GetControl (IDC_BTN_TAB_INFO_DETAILS)->Enable (false);
      GetControl (IDC_BTN_TAB_FEES_DETAILS)->Enable (false);
      GetControl (IDC_BTN_TAB_INFO_DETAILS)->Show (false);
      GetControl (IDC_BTN_TAB_FEES_DETAILS)->Show (false);
   //tabs
      m_pInfoTabCtrl->EnableWindow (false);
      m_pFeesTabCtrl->EnableWindow (false);
   //in the beginning disconnect all controls, 
      //trade controls
      ConnectControlsToData (TRADE_CONTROLS::TRADE, false);
      ConnectControlsToData (TRADE_CONTROLS::FROM_SIDE, false);
      ConnectControlsToData (TRADE_CONTROLS::TO_SIDE, false);
      //address controls
      ConnectControlsToData (TRADE_CONTROLS::ADDRESS, false);
      ConnectControlsToData (TRADE_CONTROLS::ADDRESS_FROM, false);
      ConnectControlsToData (TRADE_CONTROLS::ADDRESS_TO, false);
      //acount controls
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT, false);
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FIELD, false);
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FROM, false);
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FROM_FIELD, false);
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_TO, false);
      ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_TO_FIELD, false);
      //shareholder controls
      ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER, false);
      ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_FROM, false);
      ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_TO, false);
      //bank controls
      ConnectControlsToData (TRADE_CONTROLS::BANK, false);
      //shareholder address controls
      ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_ADDRESS, false);
      //tax rates address controls
      ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, false);
      ConnectControlsToData (TRADE_CONTROLS::CHK_TAX_RATES, false);
      //settle location
      ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION, false);
	  ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION_TO, false);
      if( m_strMarket == MARKET_IDS::LUXEMBOURG )
          ConnectControlsToData (TRADE_CONTROLS::G1G2, false);
      //the attributes grid control
      m_pAttributesGrdWnd->Enable (false);
      //the list controls
      ConnectListToData (IDC_LV_ALLOCATIONS, false);
      if (m_strMarket == MARKET_IDS::CANADA)
         ConnectListToData (IDC_LV_ESTATE_ALLOCATION, false);
      ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, false);
   //load initial controls
      LoadListControl (IDC_LV_TRANSACTIONS);
      ConnectControlsToData (TRADE_CONTROLS::EUSD, false);
   }
   return true;
}

//******************************************************************************
bool TradesDlg::doSend ( GenericInterface *rpGICaller,
                         const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   bool bRet = true;

   if (DString (szMessage) == I_("RefreshTradesList"))
   {
      DString selectionKey;

      getParameter (MFCAN_IP_PARAM::LIST_KEY, selectionKey); 
      LoadListControl (IDC_LV_TRANSACTIONS, &selectionKey);
      if (GETHIGHESTSEVERITY () > WARNING)
      {
         // Display error
         ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
         bRet = false;
      }
   }
   else
   {
      bRet = BaseMainDlg::doSend (rpGICaller, szMessage);
   }
   return bRet;
}

//******************************************************************************
BOOL TradesDlg::PreTranslateMessage (MSG*pMsg)
{
   if ( pMsg->message == WM_KEYDOWN && 
        (int) (pMsg->wParam) == VK_F4)
   {
      CWnd *pFocusingWnd = m_pCWndF4Focus = GetFocus ();
      if (dynamic_cast<CGXEditControl*>(pFocusingWnd) == nullptr && 
         !IsSelectedCtrlUpdateable ())
      {
         return TRUE;
      }
      
      if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_BROKER_CODE))
      {
         PostMessage (UM_OPENBROKERLISTDLG);
      }
      else if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_BRANCH_CODE)) 
      {
         PostMessage (UM_OPENBRANCHLISTDLG);
      } 
      else if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_SALES_REP_CODE)) 
      {
         PostMessage (UM_OPENSLSREPLISTDLG);
      }
      else if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_SHAREHOLDER_ADDR_CODE)) 
      {
         PostMessage (UM_OPENSELECTADDRESSDLG);
      }
      else if ( m_pCWndF4Focus == GetDlgItem (IDC_EDT_ACCOUNT) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_ACCOUNT) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_ACCOUNT)) 
      {
         PostMessage (WM_LAUNCH_IDENT_ACC);
      }
      else if ( m_pCWndF4Focus == GetDlgItem (IDC_EDT_FUND_CODE) || //one side
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FUND_CLASS) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FUND_NBR) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_ISIN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_WKN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_FUND_CODE) || //from side
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_FUND_CLASS) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_FUND_NBR) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_ISIN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_WKN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_FUND_CODE) || //to side
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_FUND_CLASS) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_FUND_NBR) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_ISIN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_WKN) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_LFC) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_LFC) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_LFC)   ||
				m_pCWndF4Focus == GetDlgItem (IDC_EDT_CUSIP) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_FROM_CUSIP) ||
                m_pCWndF4Focus == GetDlgItem (IDC_EDT_TO_CUSIP)   

                ) 
      {
         PostMessage (UM_OPENFUNDCLASSLISTDLG);
      }
      else if (m_pCWndF4Focus == m_pAttributesGrdWnd)
      {
         if (m_pAttributesGrdWnd->GetCurrentRowKey () == I_("AssocTransId"))
         {
            DString isAssociationToOriginalContribAllowed;

	         DString isPSEEAPAllowed;

	         getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, 
                                    IsAssociationToOriginalContribAllowed, 
                                    isAssociationToOriginalContribAllowed, false);
            if (isAssociationToOriginalContribAllowed == I_("Y"))
            {
               PostMessage (UM_OPENASSOCIDHELPER);
            }
         }
         else if (m_pAttributesGrdWnd->GetCurrentRowKey () == I_("ExternalInstitution"))
         {
            const BFProperties* pProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::TRADES_LIST, ifds::ExternalInstitution);
            if( pProp && !pProp->isReadOnly())
            {
               PostMessage (UM_OPENEXTERNALINSTITUTION);
            }
         }         
      }
      else if (dynamic_cast<CGXEditControl*>(m_pCWndF4Focus) && m_pAttributesGrdWnd)
      {
         if (m_pAttributesGrdWnd->GetCurrentRowKey () == I_("ExternalInstitution"))
         {
            const BFProperties* pProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::TRADES_LIST, ifds::ExternalInstitution);
            if( pProp && !pProp->isReadOnly() )
               PostMessage (UM_OPENEXTERNALINSTITUTION);
         }
      }
   }
   return BaseMainDlg::PreTranslateMessage (pMsg);
}

//**********************************************************************
void TradesDlg::PostOk (bool bOkStatus)
{	
	if (bOkStatus)
	{
	}
}

//**********************************************************************************
void TradesDlg::ControlUpdated ( UINT controlID, 
                                 const DString &strValue)
{
   switch (controlID)
   {  
      case IDC_CMB_TRANSACTION_TYPE:
         {
            show2Sides (strValue);
			m_tradeTransactionType = strValue;  // stored for being sent to Dilution screen
//security access
            if (DSTCommonFunctions::codeInList ( strValue, 
                                                 TRADETYPE::PURCHASE_LIKE))
            {
               SetUserAccesFunctionCode (UAF::TRADING_PURCHASE);
            }
            else if (DSTCommonFunctions::codeInList ( strValue, 
                                                      TRADETYPE::EXCHANGE_LIKE))
            {
               SetUserAccesFunctionCode (UAF::TRADING_EXCHANGE);
            }
            else if (DSTCommonFunctions::codeInList ( strValue, 
                                                      TRADETYPE::REDEMPTION_LIKE) ||
                     strValue == TRADETYPE::ROLLOVER)
            {
               SetUserAccesFunctionCode (UAF::TRADING_REDEMPTION);
            }
            else 
            {
               //this will disable everything
               SetUserAccesFunctionCode (NULL);
            }

            bool bOneSideTrade = isOneSideTrade (strValue);
//make sure the cautions combo are emptied
            if (bOneSideTrade)
            {
               resetCautionsCombo ( IDC_STC_CAUTIONS,
                                    IDC_CMB_CAUTIONS);
            }
            else
            {
               resetCautionsCombo ( IDC_STC_FROM_CAUTIONS,
                                    IDC_CMB_FROM_CAUTIONS);
               resetCautionsCombo ( IDC_STC_TO_CAUTIONS,
                                    IDC_CMB_TO_CAUTIONS);
            }

            DString isAccountSetAndValid,
               isAccountToSetAndValid;

            getParent ()->getField ( this,
                                     ACCOUNT,
                                     IsAccountSetAndValid,
                                     isAccountSetAndValid,
                                     false);
            getParent ()->getField ( this,
                                     ACCOUNT_TO,
                                     IsAccountSetAndValid,
                                     isAccountToSetAndValid,
                                     false);
            bool bConnectOneSide = 
               isAccountSetAndValid == I_("Y") && bOneSideTrade;
            bool bConnectFromSide = 
               isAccountSetAndValid == I_("Y") && !bOneSideTrade;
            bool bConnectToSide = 
               isAccountToSetAndValid == I_("Y") && !bOneSideTrade;

//always connect the date
            ConnectControlsToData (TRADE_CONTROLS::TRADE_DATE);
            LoadControls (TRADE_CONTROLS::TRADE_DATE);
//always connect/disconnect one side account controls
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FIELD, bOneSideTrade);
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT, bOneSideTrade);
            if (bOneSideTrade)
            {
               LoadControls (TRADE_CONTROLS::ACCOUNT_FIELD);
               if (!bConnectOneSide)
               {
                  LoadControls (TRADE_CONTROLS::ACCOUNT);
               }
            }
            ConnectControlsToData (TRADE_CONTROLS::ONE_SIDE, bConnectOneSide);
            ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER, bConnectOneSide);
            ConnectControlsToData (TRADE_CONTROLS::ADDRESS, bConnectOneSide);
//always connect/disconnect from side account controls
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FROM_FIELD, !bOneSideTrade);
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_FROM, !bOneSideTrade);
            if (!bOneSideTrade)
            {
               LoadControls (TRADE_CONTROLS::ACCOUNT_FROM_FIELD);
               if (!bConnectFromSide)
               {
                  LoadControls (TRADE_CONTROLS::ACCOUNT_FROM);
               }
            }
            //connect from side only if account num is valid
            ConnectControlsToData (TRADE_CONTROLS::FROM_SIDE, bConnectFromSide);
            ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_FROM, bConnectFromSide);
            ConnectControlsToData (TRADE_CONTROLS::ADDRESS_FROM, bConnectFromSide);
//always connect/disconnect to side account controls
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_TO_FIELD, !bOneSideTrade);
            ConnectControlsToData (TRADE_CONTROLS::ACCOUNT_TO, !bOneSideTrade);
            if (!bOneSideTrade)
            {
               LoadControls (TRADE_CONTROLS::ACCOUNT_TO_FIELD);
               if (!bConnectToSide)
               {
                  LoadControls (TRADE_CONTROLS::ACCOUNT_TO);
               }
            }
            //connect to side only if account to num is valid
            ConnectControlsToData (TRADE_CONTROLS::TO_SIDE, bConnectToSide);
            ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_TO, bConnectToSide);
            ConnectControlsToData (TRADE_CONTROLS::ADDRESS_TO, bConnectToSide);
//the rest of trade controls should be connected regardless
            ConnectControlsToData (TRADE_CONTROLS::TRADE, bConnectOneSide || bConnectFromSide);
            if (isAccountSetAndValid != I_("Y"))
            {
               if (bOneSideTrade)
               {
                  if (!m_accountNum.empty())
                  {
                     GetDlgItem (IDC_EDT_ACCOUNT)->SetWindowText (m_accountNum.c_str());
                  }
               }
               else
               {
                  if (!m_accountNum.empty())
                  {
                     GetDlgItem (IDC_EDT_FROM_ACCOUNT)->SetWindowText (m_accountNum.c_str());
                  }
               }
            }

			DString dstrDeconversion;
			getParent ()->getField ( this,
                                     IFASTBP_PROC::TRADES_LIST,
                                     ifds::Deconversion,
                                     dstrDeconversion,
                                     false);

            break;
         }
      case IDC_EDT_ACCOUNT:
         {
            DString accountNum,
               isAccountSetAndValid;
            
            GetControl (IDC_EDT_ACCOUNT)->GetText (accountNum);
            getParent ()->getField ( this,
                                     ACCOUNT,
                                     IsAccountSetAndValid,
                                     isAccountSetAndValid,
                                     false);
            //load the account related controls only if the account num is valid
            if ( isAccountSetAndValid == I_("Y") && 
                 !accountNum.empty())
            {
               if (m_bTradeListSelectionInProgress)
               {
                  //connect the list controls, 
                  ConnectListToData (IDC_LV_ALLOCATIONS, true);
                  ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, true);
                  //and load the trade controls 
                  LoadControls (TRADE_CONTROLS::ACCOUNT);
                  ConnectControlsToData (TRADE_CONTROLS::ONE_SIDE, true);
                  LoadControls (TRADE_CONTROLS::ONE_SIDE);
                  ConnectControlsToData (TRADE_CONTROLS::TRADE, true);
                  LoadControls (TRADE_CONTROLS::TRADE);
                  ConnectControlsToData  (TRADE_CONTROLS::TRADE_DATE, true);
                  LoadControls (TRADE_CONTROLS::TRADE_DATE);
                  ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER, true);
                  LoadControls (TRADE_CONTROLS::SHAREHOLDER);
                  ConnectControlsToData (TRADE_CONTROLS::ADDRESS, true);
                  LoadControls (TRADE_CONTROLS::ADDRESS);
                  fillCautionsCombo ( IDC_STC_CAUTIONS,
                                      IDC_CMB_CAUTIONS,
                                      SHAREHOLDER,
                                      ACCOUNT,
                                      ACCOUNT_CATEGORY_LIST);
//load the informational tab control
                  if (m_pInfoTabCtrl)
                  {
                     m_pInfoTabCtrl->EnableWindow (true);
                     updateInfoTabCtrl (true);
                  }                  
//load the fees tab control
                  if (m_pFeesTabCtrl)
                  {
                     m_pFeesTabCtrl->EnableWindow (true);
                     updateFeesTabCtrl (true);
                  }                  
//enable the attributes grid control
                  m_pAttributesGrdWnd->Enable (true);
//get the intial settle date value
                  getParent ()->getField ( this,
                                           IFASTBP_PROC::TRADES_LIST,
                                           ifds::SettleDate,
                                           m_initialSettleDate,
                                           false);

                   getParent ()->getField ( this,
                                           IFASTBP_PROC::TRADES_LIST,
                                           ifds::SettleInDate,
                                           m_initialSettleInDate,
                                           false);

                   DString settleDateOverridden;

                   getParent ()->getField ( this,
                                            IFASTBP_PROC::TRADES_LIST,
                                            ifds::SettleDateOverriden,
                                            settleDateOverridden,
                                            false);

                   m_bSettleDateOverriden = settleDateOverridden == I_("Y") ? true : false;

//finally, set the internal parameter to the value of the last account num
                  m_accountNum = accountNum;

				  getParent ()->getField ( this,
                                           IFASTBP_PROC::TRADES_LIST,
                                           ifds::CashDate,
                                           m_initialCashDate,
                                           false);

                  updateNetworkIDExternalTransNum();
               }

               if (m_pAttributesGrdWnd && !m_bTradeListSelectionInProgress)
               {
                  m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("DepositCode"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("RedemptionCode"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
               }

               openAlertMsgAndRemarkScreen();
            }
            else
            {
               GetControl (IDC_EDT_ACCOUNT)->LoadErrorState ();
            }
            break;
         }
      case IDC_EDT_FROM_ACCOUNT:
         {
            DString accountNum,
               isAccountSetAndValid;
            
            GetControl (IDC_EDT_FROM_ACCOUNT)->GetText (accountNum);
            getParent ()->getField ( this,
                                     ACCOUNT,
                                     IsAccountSetAndValid,
                                     isAccountSetAndValid,
                                     false);
            //load the account related controls only if the account num is valid
            if ( isAccountSetAndValid == I_("Y") &&
                 !accountNum.empty())
            {
               if (m_bTradeListSelectionInProgress)
               {
                  //connect the list controls, 
                  ConnectListToData (IDC_LV_ALLOCATIONS, true);
                  ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, true);
                  //and load the trade controls
                  LoadControls (TRADE_CONTROLS::ACCOUNT_FROM);
                  ConnectControlsToData (TRADE_CONTROLS::TRADE, true);
                  LoadControls (TRADE_CONTROLS::TRADE);
                  ConnectControlsToData  (TRADE_CONTROLS::TRADE_DATE, true);
                  LoadControls (TRADE_CONTROLS::TRADE_DATE);
                  ConnectControlsToData (TRADE_CONTROLS::FROM_SIDE, true);
                  LoadControls (TRADE_CONTROLS::FROM_SIDE);
                  ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_FROM, true);
                  LoadControls (TRADE_CONTROLS::SHAREHOLDER_FROM);
                  ConnectControlsToData (TRADE_CONTROLS::ADDRESS_FROM, true);
                  LoadControls (TRADE_CONTROLS::ADDRESS_FROM);
                  fillCautionsCombo ( IDC_STC_FROM_CAUTIONS,
                                      IDC_CMB_FROM_CAUTIONS,
                                      SHAREHOLDER,
                                      ACCOUNT,
                                      ACCOUNT_CATEGORY_LIST);
//load the informational tab control
                  if (m_pInfoTabCtrl)
                  {
                     m_pInfoTabCtrl->EnableWindow (true);
                     updateInfoTabCtrl (true);
                  }                  
//load the fees tab control
                  if (m_pFeesTabCtrl)
                  {
                     m_pFeesTabCtrl->EnableWindow (true);
                     updateFeesTabCtrl (true);
                  }                  
//enable the attributes grid control
                  m_pAttributesGrdWnd->Enable (true);
//get the initial settle date value
                  getParent ()->getField ( this,
                                           IFASTBP_PROC::TRADES_LIST,
                                           ifds::SettleDate,
                                           m_initialSettleDate,
                                           false);

                  getParent ()->getField ( this,
                                           IFASTBP_PROC::TRADES_LIST,
                                           ifds::SettleInDate,
                                           m_initialSettleInDate,
                                           false);

                  DString settleDateOverridden;

                  getParent ()->getField ( this,
                                       IFASTBP_PROC::TRADES_LIST,
                                       ifds::SettleDateOverriden,
                                       settleDateOverridden,
                                       false);

                  m_bSettleDateOverriden = settleDateOverridden == I_("Y") ? true : false;
//finally, set the internal parameter to the value of the last account num
                  m_accountNum = accountNum;

				  getParent ()->getField ( this,
					  IFASTBP_PROC::TRADES_LIST,
					  ifds::CashDate,
					  m_initialCashDate,
					  false);

                  updateNetworkIDExternalTransNum();
               }

               if (m_pAttributesGrdWnd && !m_bTradeListSelectionInProgress)
               {
                  m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("DepositCode"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("RedemptionCode"), I_("Value"));
                  m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
               }

               openAlertMsgAndRemarkScreen();
            }
            else
            {
               GetControl (IDC_EDT_FROM_ACCOUNT)->LoadErrorState ();
            }
            break;
         }
      case IDC_EDT_TO_ACCOUNT:
         {
            DString accountTo,
               isAccountToSetAndValid;

            GetControl (IDC_EDT_TO_ACCOUNT)->GetText (accountTo);
            getParent ()->getField ( this,
                                     ACCOUNT_TO,
                                     IsAccountSetAndValid,
                                     isAccountToSetAndValid,
                                     false);
            GetControl (IDC_EDT_TO_ACCOUNT)->GetText (accountTo);
            if (m_pAttributesGrdWnd && !m_bTradeListSelectionInProgress)
            {
               m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
               m_pAttributesGrdWnd->reloadCell (I_("DepositCode"), I_("Value"));
               m_pAttributesGrdWnd->reloadCell (I_("RedemptionCode"), I_("Value"));
               m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
            }
            //load the to side of the transaction
            if ( isAccountToSetAndValid == I_("Y") &&
                 !accountTo.empty())
            {
               updateBeneficiaryAllocationPage ();
               updatePSEEAPPage ();
               //if (GetControl (IDC_EDT_ACCOUNT)->IsEnabled ())
               {
                  LoadControls (TRADE_CONTROLS::ACCOUNT_TO);
                  ConnectControlsToData (TRADE_CONTROLS::TO_SIDE, true);
                  LoadControls (TRADE_CONTROLS::TO_SIDE);
                  ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_TO, true);
                  LoadControls (TRADE_CONTROLS::SHAREHOLDER_TO);
                  ConnectControlsToData  (TRADE_CONTROLS::ADDRESS_TO, true);
                  LoadControls (TRADE_CONTROLS::ADDRESS_TO);
                  fillCautionsCombo ( IDC_STC_TO_CAUTIONS,
                                      IDC_CMB_TO_CAUTIONS,
                                      SHAREHOLDER_TO,
                                      ACCOUNT_TO,
                                      ACCOUNT_CATEGORY_LIST_TO);
               }
            }
            else //disconnect the to side is the account to gets changed and has errors or is empty
            {
               GetControl (IDC_EDT_TO_ACCOUNT)->LoadErrorState ();
               ConnectControlsToData (TRADE_CONTROLS::TO_SIDE, false);
               ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_TO, false);
               ConnectControlsToData (TRADE_CONTROLS::ADDRESS_TO, false);
               resetCautionsCombo ( IDC_STC_TO_CAUTIONS,
                                    IDC_CMB_TO_CAUTIONS);
            }
            updateAllocationsPage ();
            updateSettleLocPage ();
            break;
         }
      case IDC_EDT_ALT_ACCOUNT:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::ALT_ACCOUNT_AND_BROKER_CODE,
                                   strValue,
                                   SEARCH_ALT_ACCOUNT,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_FROM_ALT_ACCOUNT:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::ALT_ACCOUNT_AND_BROKER_CODE,
                                   strValue,
                                   SEARCH_ALT_ACCOUNT_FROM,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_TO_ALT_ACCOUNT:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::ALT_ACCOUNT_AND_BROKER_CODE,
                                   strValue,
                                   SEARCH_ALT_ACCOUNT_TO,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_OTHER_REFERENCE:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER,
                                   strValue,
                                   SEARCH_X_REF_NUM,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_FROM_OTHER_REFERENCE:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER,
                                   strValue,
                                   SEARCH_X_REF_NUM_FROM,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_TO_OTHER_REFERENCE:
         {
            if (!m_bSearchInProgress)
            {
               searchForAccounts ( SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER,
                                   strValue,
                                   SEARCH_X_REF_NUM_TO,
                                   controlID);
            }
            break;
         }
      case IDC_EDT_BROKER_CODE:
         {
            LoadControl (IDC_STC_BROKER_NAME);
            if (!m_bTradeListSelectionInProgress)
            {
               updateInfoTabCtrl (true);
               updateSplitCommissionsPage ();
               //also reload the fees grid
               updateFeesPage ();
            }
            break;
         }
      case IDC_EDT_BRANCH_CODE:
         {
            LoadControl (IDC_STC_BRANCH_NAME);
            if (!m_bTradeListSelectionInProgress)
            {
               updateInfoTabCtrl (true);
               updateSplitCommissionsPage ();
            }
            break;
         }
      case IDC_EDT_SALES_REP_CODE:
         {
            LoadControl (IDC_STC_SALES_REP_NAME);
            if (!m_bTradeListSelectionInProgress)
            {
               DString shouldAskForRep;

               getParent ()->getField ( this,
                                        IFASTBP_PROC::TRADES_LIST,
                                        ShouldAskForRep,
                                        shouldAskForRep,
                                        false);
               if (shouldAskForRep == I_("Y"))
               {
                  if (m_popSalesRepCreateQuestion) //only if a change in salesrep value
                  {
                     CString noSlsrep;

                     noSlsrep.LoadString (TXT_NO_SLSREP);

                     int choice = AfxMessageBox (noSlsrep, MB_YESNO | MB_ICONQUESTION);

                     if (choice == IDYES) //should turn the create rep flag on
                     {
                        getParent ()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::CreateRep, I_("Y"));
                     }
                     else
                     {
                        //turn the create rep flag off
                        getParent ()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::CreateRep, I_("N"));
                     }
                     GetControl (IDC_EDT_SALES_REP_CODE)->LoadErrorState ();
                  }
               }
               else
               {
                  //turn the create rep flag off
                  getParent ()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::CreateRep, I_("N"));
               }
               updateInfoTabCtrl (true);
               updateSplitCommissionsPage ();
            }
            break;
         }
      case IDC_DTP_TRADE_DATE:
         {
            LoadControl (IDC_DTP_TRADE_DATE); 
            GetControl (IDC_EDT_SHAREHOLDER_ADDR_CODE)->LoadErrorState ();
            LoadControl (IDC_EDT_SHAREHOLDER_ADDR);
            GetControl (IDC_EDT_BROKER_CODE)->LoadErrorState ();
            GetControl (IDC_EDT_BRANCH_CODE)->LoadErrorState ();
            GetControl (IDC_EDT_SALES_REP_CODE)->LoadErrorState ();
//fund settled value/units, might change with the change of effective date,
//also the effectiveness if the below fields might change
            if (!m_bTradeListSelectionInProgress)
            {
               updateSplitCommissionsPage ();
               //also reload the fees grid
               updateFeesPage ();
               updateDilutionPage ();
               updateSavingsDirectivePage();

               if (m_pAttributesGrdWnd)
               {
                  m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
               }
            }
            break;
         }
      case IDC_DTP_SETTLE_DATE:
         {
            LoadControl (IDC_DTP_SETTLE_DATE);
            break;
         }
      case IDC_DTP_DEPOSIT_DATE:
         {
            LoadControl (IDC_DTP_DEPOSIT_DATE);
            break;
         }
      case IDC_EDT_FUND_NBR:
      case IDC_EDT_WKN:
      case IDC_EDT_LFC:
	  case IDC_EDT_CUSIP:
      case IDC_EDT_ISIN:
      case IDC_EDT_FUND_CODE:
      case IDC_EDT_FUND_CLASS:
         {
            GetControl (controlID)->LoadErrorState ();
//could change the precision on the amount, 
            LoadControl (IDC_EDT_AMOUNT); 
            LoadControl (IDC_STC_FUND_SETTLE_UNITS);
            LoadControl (IDC_STC_FUND_SETTLE_VALUE);
            LoadControl (IDC_DTP_TRADE_DATE); 

            DString fundCode,
               classCode;
            
            GetControl (IDC_EDT_FUND_CODE)->GetText (fundCode);
            GetControl (IDC_EDT_FUND_CLASS)->GetText (classCode);
            if (!m_bTradeListSelectionInProgress)
            {
               if (!fundCode.empty() && !classCode.empty())
               {
                  //updateAllocationsPage ();
                  if ( GetControl (IDC_EDT_FUND_CODE)->IsValid () &&
                       GetControl (IDC_EDT_FUND_CLASS)->IsValid ())
                  {
                     updateFeesPage ();
                     updateInfoTabCtrl (true);
                     updateEstateAllocationPage ();  
                     updateG1G2Page();                   
                  }
               }
			   updateAllocationsPage ();
               if (m_pAttributesGrdWnd)
               {
                  m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
               }
               updateSavingsDirectivePage();
            }
            break;
         }
      case IDC_EDT_FROM_FUND_NBR:
      case IDC_EDT_FROM_WKN:
      case IDC_EDT_FROM_LFC:
	  case IDC_EDT_FROM_CUSIP:
      case IDC_EDT_FROM_ISIN:
      case IDC_EDT_FROM_FUND_CODE:
      case IDC_EDT_FROM_FUND_CLASS:
         {
            GetControl (controlID)->LoadErrorState ();
            LoadControl (IDC_STC_FROM_FUND_SETTLE_UNITS);
            LoadControl (IDC_STC_FROM_FUND_SETTLE_VALUE);

            DString fundCode,
               classCode;
            //Changed from IDC_EDT_FUND_*
            GetControl (IDC_EDT_FROM_FUND_CODE)->GetText (fundCode);
            GetControl (IDC_EDT_FROM_FUND_CLASS)->GetText (classCode);
//could change the precision on the amount, 
            LoadControl (IDC_EDT_AMOUNT); 
            if (!m_bTradeListSelectionInProgress)
            {
               if (!fundCode.empty() && !classCode.empty())
               {
                  
                  if ( GetControl (IDC_EDT_FROM_FUND_CODE)->IsValid () &&
                       GetControl (IDC_EDT_FROM_FUND_CLASS)->IsValid ())
                  {
                     updateSplitCommissionsPage ();
                     updateFeesPage ();
                     updateInfoTabCtrl (true);
                  }
               }

               if (m_pAttributesGrdWnd)
               {
                  m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
               }
            }
            break;
         }
      case IDC_EDT_TO_FUND_NBR:
      case IDC_EDT_TO_WKN:
      case IDC_EDT_TO_LFC:
	  case IDC_EDT_TO_CUSIP:
      case IDC_EDT_TO_ISIN:
      case IDC_EDT_TO_FUND_CODE:
      case IDC_EDT_TO_FUND_CLASS:
         {
            GetControl (controlID)->LoadErrorState ();
            LoadControl (IDC_STC_TO_FUND_SETTLE_UNITS);
            LoadControl (IDC_STC_TO_FUND_SETTLE_VALUE);

            DString fundCode,
               classCode;
            
            GetControl (IDC_EDT_TO_FUND_CODE)->GetText (fundCode);
            GetControl (IDC_EDT_TO_FUND_CLASS)->GetText (classCode);
            if (!m_bTradeListSelectionInProgress)
            {
               if (!fundCode.empty() && !classCode.empty())
               {
                  //updateAllocationsPage ();
                  if ( GetControl (IDC_EDT_TO_FUND_CODE)->IsValid () &&
                       GetControl (IDC_EDT_TO_FUND_CLASS)->IsValid ())
                  {
                     updateFeesPage ();
                     updateInfoTabCtrl (true);
                     updateEstateAllocationPage();

                  }
               }
			   updateAllocationsPage ();

               if (m_pAttributesGrdWnd)
               {
                   m_pAttributesGrdWnd->reloadCell (I_("GuaranteesOverride"), I_("Value"));
               }
               updateSavingsDirectivePage();
            }
            break;
         }
      case IDC_EDT_SHAREHOLDER_ADDR_CODE:
         {
            LoadControl (IDC_EDT_SHAREHOLDER_ADDR);
            break;
         }
      case IDC_STC_BANK_ID:
         {
            m_pAttributesGrdWnd->reloadCell (I_("PayType"), I_("Value"));
            break;
         }
      case IDC_CMB_AMOUNT_TYPE:
         {
//Change allocation list column heading according to the amount type
            CString strText;
            DSTListCtrl* pListCtrl = GetList (IDC_LV_ALLOCATIONS);
            if (pListCtrl)
            {
               LVCOLUMN lvColumn;
               lvColumn.mask     = LVCF_TEXT;

               if (strValue == I_ ("U"))
               {
                  strText.LoadString (TXT_UNITS);
               }
               else
               {
                  strText.LoadString (TXT_AMOUNT);
               }
               lvColumn.pszText  = const_cast<LPTSTR> ((LPCTSTR)strText);
               pListCtrl->SetColumn (4, &lvColumn);
            }
           if ( !m_bTradeListSelectionInProgress &&
                GetControl (IDC_CMB_AMOUNT_TYPE)->IsValid())
            {
               updateAllocationsPage ();
               //also reload the fees grid
               updateFeesPage ();
               updateEstateAllocationPage();
            }

            LoadControl (IDC_EDT_AMOUNT);
            updateGIInvestmentsPage();
            break;
         }
      case IDC_EDT_AMOUNT:
         {
            LoadControl (IDC_EDT_AMOUNT); //to be formatted
            LoadControl (IDC_EDT_PURCHASE_TOTAL);
            if ( !m_bTradeListSelectionInProgress &&
                 GetControl (IDC_EDT_AMOUNT)->IsValid())
            {
               updateAllocationsPage ();
               updateBeneficiaryAllocationPage ();
               updateTaxRatesPage ();
               //also reload the fees grid
               updateFeesPage ();
               updateEstateAllocationPage();
               updateG1G2Page();
            }
            break;
         }
      case IDC_EDT_PURCHASE_TOTAL :
         {
            double dec_purchase_total = DSTCommonFunctions::convertToDouble (strValue);

            GetControl (IDC_STC_PURCHASE_TOTAL)->Show (dec_purchase_total != 0);
            GetControl (IDC_EDT_PURCHASE_TOTAL)->Show (dec_purchase_total != 0);
            GetControl (IDC_EDT_PURCHASE_TOTAL)->Enable (false);
            break;
         }
      case IDC_CMB_TERM_OF_DEPOSIT:
      case IDC_CMB_INT_FREQ_TRADE:
         {
            if (!m_bTradeListSelectionInProgress)
            {
               updateSplitCommissionsPage ();
               updateFeesPage ();
            }
         }
         break;
      default:
         break;
   }
   if( controlID == IDC_EDT_FROM_FUND_CODE ||
       controlID == IDC_EDT_FROM_FUND_CLASS ||
       controlID == IDC_EDT_FUND_CLASS ||
       controlID == IDC_EDT_FUND_CODE ||
       controlID == IDC_CMB_AMOUNT_TYPE  )
   {
      DString dstrAmountDecimalDigit;
      DString dstrAmount;
      
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, AmountDecimalDigit, dstrAmountDecimalDigit, false);
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::Amount, dstrAmount, false);
      
      int iAmountDecimalDigit = dstrAmountDecimalDigit.asInteger();
            dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_AMOUNT))
         ->setMaxNumDigitsAfterDecimalPoint(iAmountDecimalDigit);
         
      int exPrecision = DSTCommonFunctions::NumOfDecimals(dstrAmount);
      
      // Removing trailing digit if the new precision is less than the existing one.
      if(iAmountDecimalDigit < exPrecision) 
      {
         dstrAmount.stripTrailing(I_('0'));
         dstrAmount = dstrAmount.substr(0, dstrAmount.size() - (exPrecision - iAmountDecimalDigit));
         
         getParent()->setField(this, IFASTBP_PROC::TRADES_LIST, ifds::Amount, dstrAmount, false);
      }
   }
   //froce update the precision
   if( IDC_EDT_G1_UNITS ==  controlID || IDC_EDT_G2_UNITS ==  controlID )
   {
      DString dstrAmountDecimalDigit;//G1 g2 should have the same precision as of amount
      DString dstrG1Units, dstrG2Units;      
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, AmountDecimalDigit, dstrAmountDecimalDigit, false);
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::G1Impact, dstrG1Units, false);
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::G2Impact, dstrG2Units, false);
      int iAmountDecimalDigit = dstrAmountDecimalDigit.asInteger();
      dynamic_cast<DSTEdit*>(GetControl(controlID))->setMaxNumDigitsAfterDecimalPoint(iAmountDecimalDigit);
      int exPrecision = (IDC_EDT_G1_UNITS ==  controlID) ? DSTCommonFunctions::NumOfDecimals(dstrG1Units) :
                                                           DSTCommonFunctions::NumOfDecimals(dstrG2Units);
      // Removing trailing digit if the new precision is less than the existing one.
      if(iAmountDecimalDigit < exPrecision) 
      {
        switch (controlID )
        {
           case IDC_EDT_G1_UNITS :
            {
             dstrG1Units.stripTrailing(I_('0'));
             dstrG1Units = dstrG1Units.substr(0, dstrG1Units.size() - (exPrecision - iAmountDecimalDigit));         
             getParent()->setField(this, IFASTBP_PROC::TRADES_LIST, ifds::G1Impact, dstrG1Units, false);
             break;
            }
           case IDC_EDT_G2_UNITS :
            {
             dstrG2Units.stripTrailing(I_('0'));
             dstrG2Units = dstrG2Units.substr(0, dstrG2Units.size() - (exPrecision - iAmountDecimalDigit));         
             getParent()->setField(this, IFASTBP_PROC::TRADES_LIST, ifds::G2Impact, dstrG2Units, false);
             break;
            }
            default:
             break;
        }
      }
      updateG1G2Page();
    }
}

//******************************************************************************
void TradesDlg::GridControlUpdated ( UINT ctrlId,
                                    const DString &rowKey, 
                                    const DString &colKey,
                                    const DString &strNewValue, 
                                    bool bFormatted,
                                    SEVERITY nSeverity)
{
	if (rowKey == I_("RedemptionCode") && colKey == I_("Value") && nSeverity <= WARNING)
	{
		makeFreshDlg();
	}
}

//**********************************************************************************
bool TradesDlg::SetDataFromControl( UINT controlID,
                                    const DString &strValue,
                                    bool bFormatted,
                                    SEVERITY &sevRtn,
                                    int index /*= 0*/)
{
   if (controlID == IDC_EDT_SALES_REP_CODE)
   {
      DString slsrepCode;
      
      getParent()->getField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::SlsrepCode, 
                              slsrepCode, 
                              false);
      m_popSalesRepCreateQuestion = strValue != slsrepCode;
      if (m_popSalesRepCreateQuestion) //turn the create rep flag off
      {
         getParent ()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::CreateRep, I_("N"));
      }
   }

   if (controlID == IDC_DTP_SETTLE_DATE)
   {

      if (!m_bTradeListSelectionInProgress)
      {
         if (m_bSettleDateKillFocusInProgress) //is this a result of a kill focus?
         {
            DString settleDateOverridden;

            /*BOOL isDroppedDown = 
               dynamic_cast <DSTDateTime*> (GetControl (IDC_DTP_SETTLE_DATE))->IsDroppedDown();*/

            getParent ()->getField ( this,
                                       IFASTBP_PROC::TRADES_LIST,
                                       ifds::SettleDateOverriden,
                                       settleDateOverridden,
                                       false);

            if ( /*!isDroppedDown && */
                  !strValue.empty() &&
                  DSTCommonFunctions::CompareDates (strValue, m_initialSettleDate) != DSTCommonFunctions::EQUAL &&
                  settleDateOverridden == I_("N"))
            {
               getParent()->setField ( this, 
                                       IFASTBP_PROC::TRADES_LIST, 
                                       ifds::SettleDateOverriden, 
                                       I_("Y"), 
                                       false);
            }

            m_bSettleDateOverriden = settleDateOverridden == I_("Y") ? true : false;

            //reset the flag, done processing
            m_bSettleDateKillFocusInProgress = false;
         }
      }
   }
   
   return false;
}

//******************************************************************************
void TradesDlg::tabSelectionChanged ( UINT tabControlID, 
                                      const DString &pageName)
{
   DString modPerm;

   getParent()->getField ( this, 
                           IFASTBP_PROC::TRADES_LIST, 
                           ifds::TransModPerm,
                           modPerm, 
                           false);
   if (tabControlID == IDC_TAB_INFO)
   {
      CString cstrRemarksPageName, 
         cstrRepInfoPageName,
         cstrSettleLocation;

      cstrRemarksPageName.LoadString (TXT_TAB_TITLE_REMARKS);
      cstrRepInfoPageName.LoadString (TXT_TAB_TITLE_REP_INFO);
      cstrSettleLocation.LoadString (TXT_TAB_TITLE_SETTL_LOC);
      bool bEnableForSettleLoc = 
         pageName.c_str () == cstrSettleLocation && (modPerm == I_("2") || modPerm == I_("3"));
      GetDlgItem (IDC_BTN_TAB_INFO_DETAILS)->
         EnableWindow ( (modPerm != I_("1") && !bEnableForSettleLoc) ||
                         pageName.c_str () == cstrRemarksPageName ||
                         pageName.c_str () == cstrRepInfoPageName ? FALSE : TRUE);
      m_strCurrentTabInfoPage = pageName; //save selection
   }
   else if (tabControlID == IDC_TAB_FEES)
   {
      CString cstrAllocationPageName, 
         cstrSplitCommPageName,
         cstrTaxRatesPageName,
         cstrGridPageName,
         cstrSavingsDirectivePageName,
         cstrG1G2DetailsPageName;
      CString cstrEstateAllocationPageName;

      DString isEUSDApplicable;

      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               IsEUSDApplicable,
                               isEUSDApplicable,
                               false);

      cstrAllocationPageName.LoadString (TXT_TAB_TITLE_ALLOCATION);
      cstrSplitCommPageName.LoadString (TXT_TAB_TITLE_SPLIT_COMM);
      cstrTaxRatesPageName.LoadString (TXT_TAB_TITLE_TAX_RATE);
      cstrSavingsDirectivePageName.LoadString (TXT_TAB_TITLE_EUSD);
      cstrGridPageName.LoadString (TXT_TAB_TITLE_FEES);
      cstrEstateAllocationPageName.LoadString (TXT_TAB_TITLE_ESTATE_ALLOC);
      cstrG1G2DetailsPageName.LoadString(TXT_TAB_G1G2_DETAILS);
      GetDlgItem (IDC_BTN_TAB_FEES_DETAILS)->
         EnableWindow ( modPerm == I_("1") && 
                        (pageName.c_str () == cstrAllocationPageName || 
                         pageName.c_str () == cstrEstateAllocationPageName ||
                         pageName.c_str () == cstrSplitCommPageName  || 
                         isEUSDApplicable == I_("Y") ) ? TRUE : FALSE
                      );
      m_strCurrentTabFeesPage = pageName; //save selection
      if (pageName.c_str() == cstrTaxRatesPageName)
      {
         DString overrideTax;

         getParent()->getField ( this, 
                                 IFASTBP_PROC::TRADES_LIST, 
                                 ifds::OverrideTax,
                                 overrideTax, 
                                 false);

         if (overrideTax == I_("Y"))
         {
            if (m_strMarket == MARKET_IDS::CANADA)
            {
               ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, true);
               LoadControls (TRADE_CONTROLS::TAX_RATES);
            }
            else if(m_strMarket == MARKET_IDS::LUXEMBOURG)
            {
               ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, true);
               LoadControls (TRADE_CONTROLS::IWT_TAX_RATES);

               DSTCWorkSession *pDSTCWorkSession = 
                                    dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
               if (pDSTCWorkSession->isIWTClient(getDataGroupId()))
               {
                  DString dstrAccountNum;
                  MFAccount *pMFAccount = NULL;
                  getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);
                  if( pDSTCWorkSession->getMFAccount (getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING &&
                     pMFAccount )
                  {
                     if ( !pMFAccount->isIWTNonTaxable(getDataGroupId()) )
                     {
                        GetDlgItem (IDC_EDT_PROV_RATE)->EnableWindow (false);
                        GetDlgItem (IDC_CMB_PROV_RATE_TYPE)->EnableWindow (false);
                     }
                  }
               } // isIWTClient
            }
         }
         else
         {
            if (m_strMarket == MARKET_IDS::CANADA)
            {
				/* For Canada, we always show the rate */
               	ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, true);
				LoadControls (TRADE_CONTROLS::TAX_RATES);
				
				GetControl (IDC_EDT_FED_RATE)->Enable (false);
				GetControl (IDC_CMB_FED_RATE_TYPE)->Enable (false);
				GetControl (IDC_EDT_PROV_RATE)->Enable (false);
				GetControl (IDC_CMB_PROV_RATE_TYPE)->Enable (false);
            }
            else if(m_strMarket == MARKET_IDS::LUXEMBOURG)
            {
               ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, false);
            }
         }
      }
      if (pageName.c_str() == cstrSavingsDirectivePageName)
      {
         if (isEUSDApplicable == I_("Y"))
         {
            ConnectControlsToData (TRADE_CONTROLS::EUSD, true);
            LoadControls (TRADE_CONTROLS::EUSD);
         }
         else
         {
            ConnectControlsToData (TRADE_CONTROLS::EUSD, false);
         }
      }
      if (pageName.c_str() == cstrG1G2DetailsPageName )
      {
         DString dstrG1G2ApplicableTrade;//, dstrTransType;
         getParent ()->getField ( this, IFASTBP_PROC::TRADES_LIST, isG1G2Applicable, dstrG1G2ApplicableTrade, false ); 
         if( I_("Y") == dstrG1G2ApplicableTrade )
         {
            ConnectControlsToData (TRADE_CONTROLS::G1G2, true);
            LoadControls (TRADE_CONTROLS::G1G2);
         }
         else
         {
            ConnectControlsToData (TRADE_CONTROLS::G1G2, false);
         }
      }
   }
}

//******************************************************************************
void TradesDlg::DoPreListItemChanged ( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem,
                                       bool bIsDummyItem)
{
   switch (listControlID)
   {
      case IDC_LV_TRANSACTIONS:
         {
            m_bTradeListSelectionInProgress = true;
            break;
         }
      case IDC_LV_ALLOCATIONS:
         {
            m_bAllocationListSelectionInProgress = true;
            break;
         }
      case IDC_LV_ESTATE_ALLOCATION:
         {
            m_bEstateAllocationListSelectionInProgress = true;
            break;
         }
      case IDC_LV_SPLIT_COMMISSIONS:
         {
            m_bSplitCommissionListSelectionInProgress = true;
            break;
         }
      case IDC_LV_DILUTIONS:
         {
            m_bDilutionListSelectionInProgress = true;
            break;
         }
      case IDC_LV_MAT_INSTR:
         {
            m_bMaturityInstrSelectionInProgress = true;
            break;
         }
      case IDC_LV_PAY_INSTRUCT:
         {
            m_bPayInstructSelectionInProgress = true;
            break;
         }
	  case IDC_LV_MULTIPLE_SETTL_LOCS:
         {
            m_bMultipleSettleLocSelectionInProgress = true;
            break;
         }
      case IDC_LV_BENEFICARY_ALLOCATION:
         {
            m_bRESPBenefAllocationInProgress = true;
            break;
         }
      case IDC_LV_ACCT_BENEF:
         {
            m_bRESPTransfersInProgress = true;
            break;
         }
      case IDC_LV_INVESTMENT_DETAILS:
         {
            m_bInvestmentDetailsListSelectionInProgress = true;
            break;
         }

		default:
         break;
   }
}

//******************************************************************************
void TradesDlg::DoListItemChanged ( UINT listControlID,
                                    const DString &strKey, 
                                    bool isNewItem,
                                    bool bIsDummyItem)
{  
	switch (listControlID)
   {
      case IDC_LV_TRANSACTIONS:
         {
            DString isAccountSetAndValid,
               isAccountCloningAllowed;

            getParent ()->getField ( this,
                                     ACCOUNT,
                                     IsAccountSetAndValid,
                                     isAccountSetAndValid,
                                     false);
            getParent ()->getField ( this,
                                     IFASTBP_PROC::TRADES_LIST,
                                     IsAccountCloningAllowed,
                                     isAccountCloningAllowed,
                                     false);
            bool bIsAccountSetAndValid = isAccountSetAndValid == I_("Y");

            updateInfoTabCtrl (true);
            updateFeesTabCtrl (true);
//enable/disable 'History' button
            GetDlgItem (IDC_BTN_HISTORY)->EnableWindow (bIsAccountSetAndValid);
//enable/diable 'Clone Acct' button
            GetDlgItem (IDC_BTN_CLONE_ACCOUNT)->EnableWindow (
                  hasReadPermission (UAF::CLONE_ACCOUNT)  && 
                  bIsAccountSetAndValid && 
                  isAccountCloningAllowed == I_("Y"));
//enable/disable the attributes grid/tab controls
            m_pAttributesGrdWnd->Enable (bIsAccountSetAndValid);
            m_pInfoTabCtrl->EnableWindow (bIsAccountSetAndValid);
            m_pFeesTabCtrl->EnableWindow (bIsAccountSetAndValid);
//reset button should be enabled only if the element is new
            GetDlgItem (IDC_BTN_RESET)->EnableWindow (bIsAccountSetAndValid && isNewItem);
            m_bTradeListSelectionInProgress = false;

            DString dstrAlertMessageExists;
            if (bIsAccountSetAndValid)
                getParent()->getField(this, ACCOUNT, ifds::AlertMessageExists, dstrAlertMessageExists, false);

            GetDlgItem(IDC_BTN_ALERT_MESSAGES)->EnableWindow(bIsAccountSetAndValid && dstrAlertMessageExists == YES);

            break;
         }
      case IDC_LV_ALLOCATIONS:
         {
            m_bAllocationListSelectionInProgress = false;
            break;
         }
      case IDC_LV_ESTATE_ALLOCATION:
         {
            m_bEstateAllocationListSelectionInProgress = false;
            break;
         }
         
      case IDC_LV_SPLIT_COMMISSIONS:
         {
            m_bSplitCommissionListSelectionInProgress = false;
            break;
         }
      case IDC_LV_DILUTIONS:
         {
            m_bDilutionListSelectionInProgress = false;
            break;
         }
      case IDC_LV_MAT_INSTR:
         {
            m_bMaturityInstrSelectionInProgress = false;
            break;
         }
      case IDC_LV_PAY_INSTRUCT:
         {
            m_bPayInstructSelectionInProgress = false;
            break;
         }
	  case IDC_LV_MULTIPLE_SETTL_LOCS:
         {
            m_bMultipleSettleLocSelectionInProgress = false;
            break;
         }
	  case IDC_LV_BENEFICARY_ALLOCATION:
         {
            m_bRESPBenefAllocationInProgress = false;
            break;
         }
      case IDC_LV_ACCT_BENEF:
         {
            m_bRESPTransfersInProgress = false;
            break;
         }
      case IDC_LV_INVESTMENT_DETAILS:
         {
            m_bInvestmentDetailsListSelectionInProgress = false;
            break;
         }
		default:
         break;
   }
}

//*************************************************************************
bool TradesDlg::SetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              const DString &strIn,
                              bool bFormatted,
                              SEVERITY &sevRtn)
{
   if (ctrlId == IDC_GRD_TRADE_ATTRIBUTES)
   {  
      if (rowKey == I_("ValueDate"))
      {
			if (!m_bTradeListSelectionInProgress)
         {
		      DString orderType;
   		  
            getParent ()->getField ( this,
                                    IFASTBP_PROC::TRADES_LIST,
                                    ifds::OrderType,
                                    orderType,
                                    false);
            if (orderType == I_("N"))
            {
		         getParent()->setField ( this, 
                                       IFASTBP_PROC::TRADES_LIST, 
                                       ifds::ValueDateOverriden, 
                                       I_("Y"), 
                                       false);
            }
         }
      }
   }
   return false;
}


//*************************************************************************
bool TradesDlg::OnGridSetCellValue ( UINT ctrlId, 
                                     const DString &rowKey, 
                                     const DString &colKey, 
                                     const DString &strIn)
{
   if (ctrlId == IDC_GRD_TRADE_ATTRIBUTES)
   {
      if (rowKey == I_("PayInstrOption"))
      {
         updateInfoTabCtrl (false);
      }
      else if (rowKey == I_("SettleInDate"))
      {
         DString settleDate;

          getParent ()->getField ( this,
                                   IFASTBP_PROC::TRADES_LIST,
                                   ifds::SettleDate,
                                   settleDate,
                                   false);

          if (m_bSettleDateOverriden)
             return true;

            if (!strIn.empty() &&
                DSTCommonFunctions::CompareDates (settleDate, strIn) == DSTCommonFunctions::FIRST_EARLIER &&
                DSTCommonFunctions::CompareDates (strIn, m_initialSettleInDate) != DSTCommonFunctions::EQUAL)
            {
               getParent()->setField ( this, 
                                       IFASTBP_PROC::TRADES_LIST, 
                                       ifds::SettleDateOverriden, 
                                       I_("Y"), 
                                       false);

               m_bSettleDateOverriden = true;
            }

     }
      else if ( rowKey == I_("PayType") ||
                rowKey == I_("PayMethod")) 
      {
         updateInfoTabCtrl (false);
         //force a reload on the pay type cell, this will clear/set errors
         m_pAttributesGrdWnd->reloadCell (I_("PayType"), I_("Value"));
         if (rowKey == I_("PayType"))
         {
            GetControl (IDC_CMB_AMOUNT_TYPE)->LoadErrorState();
         }
      }
      else if ( rowKey == I_("SettlementCurrency") ||
                rowKey == I_("LUX_SettlementCurrency") || //for redemption
                rowKey == I_("CAD_SettlementCurrency")) //for redemption
      {
         LoadControls (TRADE_CONTROLS::BANK);
         //reload the pay type cell, this will clear/set errors
         m_pAttributesGrdWnd->reloadCell (I_("PayType"), I_("Value"));
         if (!m_bTradeListSelectionInProgress)
         {
            updateSplitCommissionsPage ();
            updateFeesPage ();
         }
         LoadControl (IDC_EDT_PURCHASE_TOTAL);
      }
      else if (rowKey == I_("RedemptionCode"))
      {
         DString strTransType;
         getParent()->getField(this, 
                               IFASTBP_PROC::TRADES_LIST, 
                               ifds::TradesTransType, 
                               strTransType,
                               false);
         strTransType.strip().upperCase();
      
         if (!m_bTradeListSelectionInProgress)
         {
            m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
            m_pAttributesGrdWnd->reloadCell (I_("GRRepayReason"), I_("Value"));
            m_pAttributesGrdWnd->reloadCell (I_("RESPReportHRDC"), I_("Value"));
            //IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
            m_pAttributesGrdWnd->reloadCell (I_("EAPCESGPaid"), I_("Value"));

            if (DSTCommonFunctions::codeInList ( strTransType, 
                                                 TRADETYPE::REDEMPTION_LIKE))
            {
               m_pAttributesGrdWnd->reloadCell (I_("ExternalInstitution"), I_("Value"));
            }
            
            updateFeesPage ();
            updateAllocationsPage ();
            updatePSEEAPPage ();
            updateTaxRatesPage ();
            updateRESPTransferPage ();
         }
      }

      else if (rowKey == I_("DepositCode"))
      {
         DString strTransType;
         getParent()->getField(this, 
                               IFASTBP_PROC::TRADES_LIST, 
                               ifds::TradesTransType, 
                               strTransType,
                               false);
         strTransType.strip().upperCase();
      
         if (!m_bTradeListSelectionInProgress)
         {
            m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
            
            if (DSTCommonFunctions::codeInList ( strTransType, 
                                                 TRADETYPE::PURCHASE_LIKE))
            {
               m_pAttributesGrdWnd->reloadCell (I_("ExternalInstitution"), I_("Value"));
            }
            
            updateSplitCommissionsPage ();
            updateFeesPage ();
            updateBeneficiaryAllocationPage ();
            updateRESPTransferPage ();
			updateRDSPTransferPage ();
         }
      }
      else if (rowKey == I_("AcquisitionFeeOption"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updateFeesPage ();
         }
      }
      else if (rowKey == I_("ROAAmount"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updateSplitCommissionsPage ();
            updateFeesPage ();
         }
      }
      else if ( rowKey == I_("AccountabilityCode") ||
                rowKey == I_("BackdatedReason"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updateDilutionPage ();
         }
      }
      else if ( rowKey == I_("FileProcessor"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updatePayInstructPage ();
         }
      }
      else if ( rowKey == I_("GRRepayReason"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            m_pAttributesGrdWnd->reloadCell (I_("RESPReportHRDC"), I_("Value"));
         }
      }
	 
	  else if (rowKey == I_("RDRAdvice"))
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updateSplitCommissionsPage ();
            updateFeesPage ();
         }
      }
	  else if (rowKey == I_("CashDate"))
	  {
		  DString dstrCashDate;

		  getParent ()->getField ( this,
			  IFASTBP_PROC::TRADES_LIST,
			  ifds::CashDate,
			  dstrCashDate,
			  false);


		  if (!strIn.empty() &&
			  DSTCommonFunctions::CompareDates (dstrCashDate, m_initialCashDate) != DSTCommonFunctions::EQUAL)
		  {
			  getParent()->setField ( this, 
				  IFASTBP_PROC::TRADES_LIST, 
				  ifds::CashDateOverriden, 
				  I_("Y"), 
				  false);

   }

     }
   }
   else if (ctrlId == IDC_GRD_FEES)
   {
      if (colKey == I_("FeeRate")|| colKey == I_("FeeType") || colKey == I_("FeeOption")  )
      {
         if (!m_bTradeListSelectionInProgress)
         {
            updateSplitCommissionsPage ();
            updateGIInvestmentsPage();
         }
      }
   }
   return true;
}

//buttons handlers
//******************************************************************************
void TradesDlg::OnBtnAdd ()
{
   CWaitCursor wait;

//the list controls
   ConnectListToData (IDC_LV_ALLOCATIONS, false);
   ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, false);
   if (m_strMarket == MARKET_IDS::CANADA)
   {
      ConnectListToData (IDC_LV_ESTATE_ALLOCATION, false);
   }

   AddToListControl (IDC_LV_TRANSACTIONS);
   makeFreshDlg ();
}

//******************************************************************************
void TradesDlg::OnBtnDelete ()
{
   CWaitCursor wait;

//the list controls
   ConnectListToData (IDC_LV_ALLOCATIONS, false);
   ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, false);
   
   if (m_strMarket == MARKET_IDS::CANADA)
   {
      ConnectListToData (IDC_LV_ESTATE_ALLOCATION, false);
   }
   
   DeleteFromListControl (IDC_LV_TRANSACTIONS);
   makeFreshDlg ();
}

//******************************************************************************
void TradesDlg::OnBtnReset () 
{
   CWaitCursor wait;

//the list controls
   ConnectListToData (IDC_LV_ALLOCATIONS, false);
   ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, false);
   if (m_strMarket == MARKET_IDS::CANADA)
   {
      ConnectListToData (IDC_LV_ESTATE_ALLOCATION, false);
   }
   DSTListCtrl *pTransactionsListCtrl = GetList (IDC_LV_TRANSACTIONS);

   if (pTransactionsListCtrl)
   {
      ResetListItem (IDC_LV_TRANSACTIONS);
      pTransactionsListCtrl->setAutoAddFlag (true); //this will set the list NOT to be an auto add list
//setting the flag will actually signal the process to delete the current item 
//and create a new 'light' trade.
      getParent()->setField ( this, 
                              Reset,
                              I_("Y"));
      pTransactionsListCtrl->setAutoAddFlag (false);
   }
   makeFreshDlg ();
}

//******************************************************************************
void TradesDlg::OnBtnHistory () 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_ ("OnBtnHistory"));

   CWaitCursor wait;

   DString transType, 
      accountNum,
      tradeDate,
      transNum;

   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);
   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, transType, false);
   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::EffectiveDate, tradeDate, false);
   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, transNum, false);
   setParameter (MFCAN_IP_PARAM::TRANS_TYPE, transType);
   setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
   setParameter (MFCAN_IP_PARAM::TRADE_DATE, tradeDate);
   setParameter (I_("NumEntry"), accountNum);
   setParameter (I_("Pending"), I_("N"));
   setParameter (I_("Reprint"), I_("N"));	
   setParameter (I_("TxnCancel"), I_("N"));	

   SetMessageStatusBar (TXT_LOAD_TRANSACTION_HISTORY);
   try
   {
      switch ( invokeCommand ( getParent(), 
                               CMD_BPROC_TRANS_HISTORY,
                               PROC_SUPPORT, 
                               false, //modeless
                               NULL))
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   SetMessageStatusBar (NULL_STRING);
}

//******************************************************************************
void TradesDlg::OnBtnCloneAcct ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OnBtnCloneAcct"));

   DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   CWaitCursor wait;   
   DString accountNum, dstrEntityName;

   getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),accountNum,dstrEntityName );

   setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   CString cstrCloneAcctNum,cstrName;
   cstrCloneAcctNum.LoadString(TXT_CLONE_ACCT_ACCT_NUM);
   DString screenTitle = DString(cstrCloneAcctNum) + accountNum;
   cstrName.LoadString(TXT_NAME_TXT);
   screenTitle += DString(cstrName) + dstrEntityName;

   DString urlParamsIDI;

   addIDITagValue (urlParamsIDI, I_("AccountNum"), accountNum);
   addIDITagValue (urlParamsIDI, I_("screen"), I_("CloneAccount"));
   setParameter (I_("UrlParams"), urlParamsIDI);
   setParameter (I_("BrowserTitle"), screenTitle);
   setParameter (I_("from_screen"), I_("TradesDlg"));

   SetMessageStatusBar (TXT_CLONE_ACCOUNT);
   try
   {
      switch ( invokeCommand ( getParent(), 
                               CMD_BPROC_CLONE_ACCOUNT_BROWSER,
                               PROC_NO_TYPE, 
                               true, //modal
                               NULL))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString clonedAccountNum;

               //getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ClonedAcountNum, clonedAccountNum);
               getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, clonedAccountNum);
               if (!clonedAccountNum.empty())
               {
                  getParent()->setField ( this, 
                                          IFASTBP_PROC::TRADES_LIST, 
                                          ifds::AccountTo, 
                                          clonedAccountNum, 
                                          false);
                  LoadControl (IDC_EDT_TO_ACCOUNT);
//refresh account details with the new account
                  GenericInterfaceContainer* pGIC = getGIContainer();
                  GenericInterface* pGIAcctDetails = NULL;

                  assert (pDSTCWorkSession);
                  if (pGIC)
                  {
                     pGIAcctDetails = pGIC->findGI (getBFWorkSession(), CMD_GUI_ACCOUNT_DETAILS);
                     if (pGIAcctDetails)
                     {
                        pGIAcctDetails->refresh (this, I_("AfterCloneOnTradeEntry"));
                     }
                  }

//open-up the RRIF screen if this is a new RRIF account 
                  MFAccount *pMFAccount (NULL);
                  DString shrNum;
                  getParent()->getField (this, SHAREHOLDER_TO, ifds::ShrNum, shrNum);
                  clonedAccountNum.strip();
                  clonedAccountNum.stripLeading ('0');
                  if ( pDSTCWorkSession->getMFAccount (getDataGroupId(), clonedAccountNum, pMFAccount) <= WARNING &&
                       pMFAccount)
                  {
                     if (pMFAccount->isRRIFAccount (getDataGroupId()))
                     {
                        DString lastName,
                           firstName;

                        //getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, lastName);
                        //getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, firstName);
                        setParameter (RRIF_LIF_LRIF::LAST_NAME_FIELD, lastName);
                        setParameter (RRIF_LIF_LRIF::FIRST_NAME_FIELD, firstName);
                        setParameter (RRIF_LIF_LRIF::ACCOUNT_NUMBER_FIELD, clonedAccountNum);
                        setParameter (RRIF_LIF_LRIF::SHAREHOLDER_FIELD, shrNum);
                        SetMessageStatusBar (TXT_LOAD_RIF_LIF);
                        E_COMMANDRETURN eRtn1 = invokeCommand (getParent(), CMD_BPROC_RRIF_LIF_LRIF_INFO, PROC_NO_TYPE, false, NULL);
                        switch (eRtn1)
                        {
                           case CMD_OK:
                           case CMD_MODELESS_INPROCESS:
                           case CMD_CANCEL:
                              break;
                           default:
                              // Display error
                              ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
                              break;
                        }
                        SetMessageStatusBar (NULL_STRING);
                     }
                  }
               }
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   SetMessageStatusBar (NULL_STRING);
}

//******************************************************************************
void TradesDlg::OnBtnBatch () 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OnBtnBatch"));

   CWaitCursor wait;

   executeCsiProcess (DcCsiProcesses::PATCH_ORDER_ENTRY_INFO);
   if (!getParent ()->send (this, I_("RefreshBatch")))
   {
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
   else
   {
      LoadControl (IDC_STC_BATCH);
   }
}

//******************************************************************************
void TradesDlg::OnBtnInfoDetails()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnInfoDetails"));
   CWaitCursor wait;

   CString cstrAddressPageName, 
      cstrBankPageName,
      cstrSettlLoc,
      cstrDilutionPageName,
      cstrPayInstructPageName,
      cstrSettlLocTo,
      cstrMultiplseSettlLoc,
      cstrRESPBenefAlloc,
      cstrPSEEAP,
      cstrRESPTransfer,
	  cstrGIAAttrib,
	  cstrGIInvestmentDetails,
	  cstrMatInstr,
	  cstrRDSPTransfer;

   cstrAddressPageName.LoadString (TXT_TAB_TITLE_ADDRESS);
   cstrBankPageName.LoadString (TXT_TAB_TITLE_BANKING);
   cstrSettlLoc.LoadString (TXT_TAB_TITLE_SETTL_LOC);
   cstrSettlLocTo.LoadString (TXT_TAB_TITLE_SETTL_LOC_TO);
   cstrDilutionPageName.LoadString (TXT_TAB_TITLE_DILUTION);
   cstrPayInstructPageName.LoadString (TXT_TAB_TITLE_PAY_INSTRUCT);
   cstrMultiplseSettlLoc.LoadString (TXT_TAB_MULTIPLE_SETTLE_LOCS);
   cstrRESPBenefAlloc.LoadString (TXT_TAB_BENEFICIARY_ALLOCS);
   cstrPSEEAP.LoadString (TXT_TAB_PSE_EAP);
   cstrRESPTransfer.LoadString (TXT_TAB_RESP_TRANSFERS);
   cstrGIAAttrib.LoadString (TXT_TAB_TITLE_GIA_ATTRIB);
   cstrGIInvestmentDetails.LoadString (TXT_TAB_TITLE_GI_INVESTMENTS);
   cstrMatInstr.LoadString (TXT_TAB_TITLE_MAT_INSTR);
   cstrRDSPTransfer.LoadString (TXT_TAB_RDSP_TRANSFERS);

   if (m_strCurrentTabInfoPage.c_str () == cstrAddressPageName)
   {
      OpenAddrBookDlg (NULL, NULL);
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrBankPageName)
   {
      try
      {
         DString accountNum, 
            tradeKey;

         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::AccountNum, 
                                  accountNum);
         tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                          IFASTBP_PROC::TRADES_LIST);

         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
         setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
         setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::TRADE);

   //invoke the banking instructions dialog 
         switch ( invokeCommand ( getParent(), 
                                  CMD_BPROC_BANK_INSTRUCTIONS,
                                  PROC_SUPPORT, 
                                  true, //modal
                                  NULL))
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
                  LoadControls (TRADE_CONTROLS::BANK);
                  //reload the pay type cell, this will clear/set errors
                  m_pAttributesGrdWnd->reloadCell (I_("PayType"), I_("Value"));
                  break;
               }
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox ( FRAMEBELOW (), 
                                     GETHIGHESTSEVERITY ());
               break;
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrSettlLoc ||
            m_strCurrentTabInfoPage.c_str () == cstrSettlLocTo )
   {
      try
      {
         DString tradeKey;

         tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                          IFASTBP_PROC::TRADES_LIST);

         setParameter (I_("FromScreen"), CLASSNAME);
         setParameter (I_("MainListKey"), tradeKey);
         if ( m_strCurrentTabInfoPage.c_str () == cstrSettlLoc )
         {
            setParameter (I_("Side"), I_("From"));
         }
         else if (m_strCurrentTabInfoPage.c_str () == cstrSettlLocTo)
         {
            setParameter (I_("Side"), I_("To"));
         }
   //invoke the settle location dialog 
         switch ( invokeCommand ( getParent(), 
                                  CMD_BPROC_SETTLEMENT_LOCATION_TRADE,
                                  PROC_SUPPORT, 
                                  true, //modal
                                  NULL))
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
            case CMD_CANCEL:
               {
                  if ( m_strCurrentTabInfoPage.c_str () == cstrSettlLoc ||
                       m_strCurrentTabInfoPage.c_str () == cstrSettlLocTo)
                  {
                     LoadControls (TRADE_CONTROLS::SETTLE_LOCATION);
                     LoadControls (TRADE_CONTROLS::SETTLE_LOCATION_TO);
                     LoadControl  (IDC_CMB_ORDER_TYPE);
                  }
                  break;
               }
               break;
            default:
               // Display error
               ConditionMessageBox ( FRAMEBELOW (), 
                                     GETHIGHESTSEVERITY ());
               break;
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrDilutionPageName)
   {
      DString tradeKey;

      tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                       IFASTBP_PROC::TRADES_LIST);
      setParameter (I_("FromScr"), I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
	  setParameter (I_("TransType4Dilution"), m_tradeTransactionType);

      switch (getParentProcess ()->invokeProcessFromChild ( this, 
																				CMD_BPROC_DILUTION, 
																				PROC_SUPPORT))
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {               
					DString accountable,
						backDatedReason,
						settleNetwork,
						dilutionLinkNum;
					
					getParameter (I_("Accountable"), accountable);
					getParameter (I_("BackDatedReason"), backDatedReason);
					getParameter (I_("SettleNetwork"), settleNetwork);
					getParameter (I_("DilutionLinkNum"), dilutionLinkNum);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::Accountable, 
													accountable, 
													false);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::BackDatedReason, 
													backDatedReason, 
													false);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::SettleNetwork, 
													settleNetwork, 
													false);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::DilutionLinkNum, 
													dilutionLinkNum, 
													false);
					updateDilutionPage ();

					m_pAttributesGrdWnd->reloadCell (I_("SettleNetwork"), I_("Value"));
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;      
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrPayInstructPageName)
   {
      DString tradeKey,
         transNum;

      tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                       IFASTBP_PROC::TRADES_LIST);
      getParent ()->getField ( this, 
                               IFASTBP_PROC::TRADES_LIST, 
                               ifds::TransNum, 
                               transNum);
      setParameter (MFCAN_IP_PARAM::CALLER, I_("TradeEntry"));
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
      switch (getParentProcess ()->invokeProcessFromChild ( this, 
																				CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS, 
																				PROC_SUPPORT))
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {               
					DString payType,
						payMethod,
                  fileProcessor;
					
					getParameter (I_("PayType"), payType);
					getParameter (I_("PayMethod"), payMethod);
               getParameter (I_("ACHProcessor"), fileProcessor);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::TradesPayType, 
													payType, 
													false);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::PayMethod, 
													payMethod, 
													false);
					getParent()->setField ( this, 
													IFASTBP_PROC::TRADES_LIST, 
													ifds::ACHProcessor, 
													fileProcessor, 
													false);
					updateInfoTabCtrl (false);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;      
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrMultiplseSettlLoc)
   {
      DString tradeKey;
      DString dstrAmountDecimalDigit;

      tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, AmountDecimalDigit, dstrAmountDecimalDigit, false);

      setParameter (CALLER, I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (DECIMAL_DIGITS, dstrAmountDecimalDigit);
      
	  switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS, PROC_SUPPORT))
	  {
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {               					
			      updateInfoTabCtrl (false);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;      
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrRESPBenefAlloc)
   {
	   DString tradeKey, accountNum, dstrAmountDecimalDigit, transNum;

	   tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

	   getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum);
	   getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, AmountDecimalDigit, dstrAmountDecimalDigit, false);
	   getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, transNum);

	   setParameter (CALLER, I_("TradeEntry") );
	   setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
	   setParameter (DECIMAL_DIGITS, dstrAmountDecimalDigit);
	   setParameter (ACCOUNT_NUM, accountNum);
	   setParameter (TRANSID, transNum);

	   switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_RESP_BENEF_ALLOCATION_LIST, PROC_SUPPORT))
	   {
	   case CMD_OK:
	   case CMD_MODELESS_INPROCESS:
		   {               					
			   getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, RefreshRESPBenefAllocation, I_("Refresh"), false);
			   updateBeneficiaryAllocationPage ();
			   break;
		   }
	   case CMD_CANCEL:
		   break;
	   default:
		   // Display error
		   ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		   break;      
	   }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrPSEEAP)
   {
      DString accountNum, 
         tradeKey;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::TRADES_LIST, 
                               ifds::AccountNum, 
                               accountNum);
      tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                         IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (CALLER, I_("TradeEntry"));
      
	  switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_PSE_EAP, PROC_SUPPORT))
	  {
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {               					
               updatePSEEAPPage ();
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;      
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrRESPTransfer)
   {
      CWaitCursor wait;

      DString transType, 
            accountNum,
			accountTo,
            tradeDate,
            tradeKey,
            transNum,
			depositType,
			redCode;

      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);
	  getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountTo, accountTo, false); //P0184541_FN01_InvescoQESItrans
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, transType, false);
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::EffectiveDate, tradeDate, false);
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, transNum, false);
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::DepositType, depositType, false); 
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::RedCode, redCode, false);

      tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::TRANS_TYPE, transType);
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (MFCAN_IP_PARAM::ACCOUNT_TO, accountTo);  
      setParameter (TRADE_DATE, tradeDate);//P0184541_FN01_InvescoQESItrans, ToDo: check if remove-> ok?
      setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
      setParameter (CALLER, I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (DEPOSIT_TYPE, depositType); 
      setParameter (RED_CODE, redCode);

      switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_RESP_TRANSFER, PROC_SUPPORT))
      {
	      case CMD_OK:
	      case CMD_MODELESS_INPROCESS:
            {               					
			      getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, RefreshRESPTransfers, I_("Refresh"), false);
               updateRESPTransferPage ();
               break;
            }
		      break;
	      case CMD_CANCEL:
            break;         	
	      default:
		      // Display error
		      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		      break;
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrGIAAttrib)
   {
      CWaitCursor wait;

      DString	accountNum,
				tradeKey;

      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);

      tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (CALLER, I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      
	  // call GIA CMD_BPROC....
      switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_GIA_INVEST_ATTRIBS, PROC_SUPPORT))
      {
	      case CMD_OK:
	      case CMD_MODELESS_INPROCESS:
            {               					
               updateGIAAttribPage ();
               updateSplitCommissionsPage ();
               updateFeesPage ();
               break;
            }
		      break;
	      case CMD_CANCEL:
            break;         	
	      default:
		      // display error
		      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		      break;
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrGIInvestmentDetails)
   {
      CWaitCursor wait;

      DString	accountNum,
				tradeKey;

      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);

      tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (CALLER, I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      
	  // call GIA CMD_BPROC....
      switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_GI_INVESTMENT_DETAILS, PROC_SUPPORT))
      {
	      case CMD_OK:
	      case CMD_MODELESS_INPROCESS:
            {               					
               updateGIInvestmentsPage();
               LoadControl(IDC_EDT_AMOUNT);
               LoadListControl(IDC_LV_INVESTMENT_DETAILS);
               break;
            }
		      break;
	      case CMD_CANCEL:
            break;         	
	      default:
		      // display error
		      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		      break;
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrMatInstr)
   {
      CWaitCursor wait;

      DString	accountNum,
				tradeDate,
				tradeKey,
				transNum;

      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::EffectiveDate, tradeDate, false);
      getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, transNum, false);

      tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
	   setParameter (TRADE_DATE, tradeDate);
      setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
      setParameter (CALLER, I_("TradeEntry") );
      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (MFCAN_IP_PARAM::RESET, I_("Y"));      
      
      switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_MATSWP_INSTRUCTIONS, PROC_SUPPORT))
      {
	      case CMD_OK:
	      case CMD_MODELESS_INPROCESS:
            {               					
               updateMaturityInstrPage ();
               break;
            }
		      break;
	      case CMD_CANCEL:
            break;         	
	      default:
		      // Display error
		      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		      break;
      }
   }
   else if (m_strCurrentTabInfoPage.c_str () == cstrRDSPTransfer)
   {
	   CWaitCursor wait;

	   DString transType, 
		   accountNum,		 
		   tradeDate,
		   tradeKey,
		   transNum,
		   depositType,
		   redCode;

	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);	  
	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, transType, false);
	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::EffectiveDate, tradeDate, false);
	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, transNum, false);
	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::DepositType, depositType, false); 
	   getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::RedCode, redCode, false);

	   tradeKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

	   setParameter (MFCAN_IP_PARAM::TRANS_TYPE, transType);
	   setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);	  
	   setParameter (TRADE_DATE, tradeDate);
	   setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
	   setParameter (CALLER, I_("TradeEntry") );
	   setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
	   setParameter (DEPOSIT_TYPE, depositType); 
	   setParameter (RED_CODE, redCode);

	   switch (getParentProcess ()->invokeProcessFromChild (this, CMD_BPROC_RDSP_TRANSFER, PROC_SUPPORT))
	   {
	   case CMD_OK:
	   case CMD_MODELESS_INPROCESS:
		   {               					
			   getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, RefreshRDSPTransfers, I_("Refresh"), false);
			   updateRDSPTransferPage ();
			   break;
		   }
		   break;
	   case CMD_CANCEL:
		   break;         	
	   default:
		   // Display error
		   ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
		   break;
	   }
   }
   //

   cstrGIAAttrib.LoadString (TXT_TAB_TITLE_GIA_ATTRIB);
   cstrMatInstr.LoadString (TXT_TAB_TITLE_MAT_INSTR);
}

//******************************************************************************
void TradesDlg::OnDblclkLvSplitCommissions (NMHDR* pNMHDR, LRESULT* pResult) 
{
   OnBtnFeesDetails ();
   *pResult = 0;
}

//******************************************************************************
void TradesDlg::OnDblclkLvAllocations (NMHDR* pNMHDR, LRESULT* pResult) 
{
   OnBtnFeesDetails ();
   *pResult = 0;
}

//******************************************************************************
void TradesDlg::OnBtnFeesDetails ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnFeesDetails"));
   CWaitCursor wait;

   CString cstrAllocationsPageName, 
      cstrSplitCommPageName;
   CString cstrEstateAllocationPageName;

   cstrAllocationsPageName.LoadString (TXT_TAB_TITLE_ALLOCATION);
   cstrSplitCommPageName.LoadString (TXT_TAB_TITLE_SPLIT_COMM);
   cstrEstateAllocationPageName.LoadString (TXT_TAB_TITLE_ESTATE_ALLOC);

   DString tradeCurrentKey,
      allocationCurrentKey;

   if ( m_strCurrentTabFeesPage.c_str () == cstrAllocationsPageName ||
        m_strCurrentTabFeesPage.c_str () == cstrSplitCommPageName)
   {
      tradeCurrentKey = 
         getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);
      allocationCurrentKey = 
         getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::FUND_ALLOCATION);
   }
   if ( m_strCurrentTabFeesPage.c_str () == cstrEstateAllocationPageName)
   {
      allocationCurrentKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::FUND_ALLOCATION);
      tradeCurrentKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);
   }

   if (m_strCurrentTabFeesPage.c_str () == cstrAllocationsPageName)
   {
      DString accountNum;

      if (!isOneSideTrade ())
      {
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::AccountTo, 
                                  accountNum);
      }
      else
      {
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::AccountNum, 
                                  accountNum);
      }
      try
      {
         DString transNum,
            transType;
   
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::TransNum, 
                                  transNum);
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::TradesTransType, 
                                  transType,
                                  false);
         if (!allocationCurrentKey.empty())
         {
            transNum.strip ().stripLeading ('0');
            setParameter (MFCAN_IP_PARAM::CALLER, I_ ("Trade"));
            setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
            setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeCurrentKey);
            setParameter (MFCAN_IP_PARAM::SUB_LIST_KEY, allocationCurrentKey);
            setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
            setParameter (MFCAN_IP_PARAM::TRANS_TYPE, transType);
            setParameter (I_("Allocation Type"), I_ ("Trade One-Time"));
            switch (getParentProcess ()->
                     invokeProcessFromChild ( this, 
                                              CMD_BPROC_ALLOCATIONS, 
                                              PROC_SUPPORT)
                  )
            {
               case CMD_OK:
               case CMD_MODELESS_INPROCESS:
                  {
                     updateAllocationsPage ();
                     //reload the fees grid, as well
                     updateFeesPage ();
                     break;
                  }
               case CMD_CANCEL:
                  break;
               default:
                  // Display error
                  ConditionMessageBox ( FRAMEBELOW (), 
                                       GETHIGHESTSEVERITY ());
                  break;
            }
            //force a selction on this tab, to solve a window painting issue
            m_pFeesTabCtrl->SelectTab (TXT_TAB_TITLE_ALLOCATION, true);
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
   else if (m_strCurrentTabFeesPage.c_str () == cstrEstateAllocationPageName)
   {
      DString accountNum;

      if (!isOneSideTrade ())
      {
         getParent ()->getField ( this, IFASTBP_PROC::TRADES_LIST, ifds::AccountTo, accountNum);
      }
      else
      {
         getParent ()->getField ( this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum);
      }
      try
      {
         //DString transNum,
         //   transType;
   
         //getParent ()->getField ( this, 
         //                         IFASTBP_PROC::TRADES_LIST, 
         //                         ifds::TransNum, 
         //                         transNum);
         //getParent ()->getField ( this, 
         //                         IFASTBP_PROC::TRADES_LIST, 
         //                         ifds::TradesTransType, 
         //                         transType,
         //                         false);
//         if (!allocationCurrentKey.empty())
         {
//            transNum.strip ().stripLeading ('0');
            setParameter (MFCAN_IP_PARAM::CALLER, I_ ("Trade"));
            setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
            setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeCurrentKey);
            setParameter (MFCAN_IP_PARAM::SUB_LIST_KEY, allocationCurrentKey);
            switch (getParentProcess ()->invokeProcessFromChild ( this, CMD_BPROC_ESTATE_ALLOCATION, PROC_SUPPORT)
                  )
            {
               case CMD_OK:
               case CMD_MODELESS_INPROCESS:
                  {
                     updateEstateAllocationPage();
                     //reload the fees grid, as well
                     updateFeesPage ();
                     break;
                  }
               case CMD_CANCEL:
                  break;
               default:
                  // Display error
                  ConditionMessageBox ( FRAMEBELOW (), 
                                       GETHIGHESTSEVERITY ());
                  break;
            }
            //force a selction on this tab, to solve a window painting issue
            m_pFeesTabCtrl->SelectTab (TXT_TAB_TITLE_ESTATE_ALLOC, true);
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
   else if (m_strCurrentTabFeesPage.c_str () == cstrSplitCommPageName)
   {
      try
      {
         DString transTypeDesc,
            splitCommListKey;

         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::TradesTransType, 
                                  transTypeDesc, 
                                  true);
         transTypeDesc.strip();
         splitCommListKey = 
               getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
         if (!splitCommListKey.empty())
         {
 			DString acqFeeType;

	        getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, AcqFeeType, acqFeeType, false);

   //set parameters on the split commission process
            setParameter (I_("MainListKey"), tradeCurrentKey);
            setParameter (I_("AllocationListKey"), allocationCurrentKey);
            setParameter (I_("SplitCommListKey"), splitCommListKey);
            setParameter (I_("TransactionTypeDescription"), transTypeDesc);
            setParameter (MFCAN_IP_PARAM::CALLER, I_("Trade"));
            setParameter (I_("FeeType"), acqFeeType);

            switch (getParentProcess ()->
                     invokeProcessFromChild ( this, 
                                                CMD_BPROC_SPLITCOMMISSION, 
                                                PROC_SUPPORT))
            {
               case CMD_OK:
               case CMD_MODELESS_INPROCESS:
                  {
                     updateSplitCommissionsPage ();
                     break;
                  }
               case CMD_CANCEL:
                  break;
               default:
                  // Display error
                  ConditionMessageBox ( FRAMEBELOW (), 
                                        GETHIGHESTSEVERITY ());
                  break;
            }
            //force a selction on this tab, to solve a window painting issue
            m_pFeesTabCtrl->SelectTab (TXT_TAB_TITLE_SPLIT_COMM, true);
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
}

//****************************************************************************** 
void TradesDlg::OnChkOverride()
{
   CWaitCursor wait;
   
   DSTCWorkSession *pDSTCWorkSession = 
            dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   if (((CButton *) GetDlgItem (IDC_CHK_OVERRIDE_TAX))->GetCheck() != 1)
	{		
		getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideTax, 
                              I_("N"), 
                              false);

      if (m_strMarket == MARKET_IDS::CANADA)
      {
		 // For Canada, we always show the tax value and save the default to DB
         ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, true);
		 GetControl (IDC_EDT_FED_RATE)->Enable (false);
		 GetControl (IDC_CMB_FED_RATE_TYPE)->Enable (false);
		 GetControl (IDC_EDT_PROV_RATE)->Enable (false);
		 GetControl (IDC_CMB_PROV_RATE_TYPE)->Enable (false);
      }
      else if(m_strMarket == MARKET_IDS::LUXEMBOURG)
      {
         ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, false);
      }
   }
   else
   {
      getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideTax, 
                              I_("Y"), 
                              false);

      if (m_strMarket == MARKET_IDS::CANADA)
      {
         ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, true);
         LoadControls (TRADE_CONTROLS::TAX_RATES);
		
         bool bUpdate = hasUpdatePermission (UAF::TRADE_TAX_RATE_OVERRIDE);

		 GetControl (IDC_EDT_FED_RATE)->Enable (bUpdate);
		 GetControl (IDC_CMB_FED_RATE_TYPE)->Enable (bUpdate);
		 GetControl (IDC_EDT_PROV_RATE)->Enable (bUpdate);
		 GetControl (IDC_CMB_PROV_RATE_TYPE)->Enable (bUpdate);
      }
      else if(m_strMarket == MARKET_IDS::LUXEMBOURG)
      {
         ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, true);
         LoadControls (TRADE_CONTROLS::IWT_TAX_RATES);
         
         if (pDSTCWorkSession->isIWTClient(getDataGroupId()))
         {
            DString dstrAccountNum;
            MFAccount *pMFAccount = NULL;
            getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);
            if( pDSTCWorkSession->getMFAccount (getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING &&
                pMFAccount )
            {
               if ( !pMFAccount->isIWTNonTaxable(getDataGroupId()) )
               {
                  GetDlgItem (IDC_EDT_PROV_RATE)->EnableWindow (false);
                  GetDlgItem (IDC_CMB_PROV_RATE_TYPE)->EnableWindow (false);
               }
            }
         } // isIWTClient
      }
	}
}

//******************************************************************************
void TradesDlg::OnKillFocusSettleDate (NMHDR* pNMHDR, LRESULT* pResult)
{
    m_bSettleDateKillFocusInProgress = true;
    *pResult = 0;
}

//******************************************************************************
bool TradesDlg::doDisablePermCheckButton (UINT nID)
{
   bool bReturn = false;

   DString modPerm;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::TRADES_LIST,
                            ifds::TransModPerm, 
                            modPerm,
                            false);
   if (nID == IDC_BTN_ADD || nID == IDC_BTN_DEL)
   {
      bReturn = modPerm == I_("0") || 
                (modPerm > I_("1") && (nID != IDC_BTN_DEL || modPerm != I_("4"))); 
   }
   return bReturn;
}

//******************************************************************************
void TradesDlg::doDisableNonPermButtons  ()
{
}

//******************************************************************************
void TradesDlg::GetCellProperties ( UINT ctrlId, 
                                    const DString &rowKey, 
                                    const DString &colKey, 
                                    BFContainerId &idContainer,
                                    BFFieldId &idField,
                                    DString &listItemKey,
                                    int &nCellState,
                                    UINT &cellCtrlType, 
                                    int &nCtrlInitMode,
                                    BFFieldId &idSubstitution,
                                    DString &comboList, 
                                    DString &mask,
                                    int& nComboSortingMode,
                                    DString&  dstrAllowedChar )
{
   dstrAllowedChar = NULL_STRING; 
   if (ctrlId == IDC_GRD_TRADE_ATTRIBUTES)
   {
      if (colKey  == I_("Attribute"))
      {
         nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
      }
      else if (colKey  == I_("Value"))
      {
         if (rowKey == I_("PayInstrOption"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::PayInstrOption;
            idSubstitution = ifds::PayInstrOption;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("PayType"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::TradesPayType;
            idSubstitution = ifds::TradesPayType;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("PayMethod"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::PayMethod;
            idSubstitution = ifds::PayMethod;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("FileProcessor"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ACHProcessor;
            idSubstitution = ifds::ACHProcessor;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("DepositCode"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DepositType;
            idSubstitution = ifds::DepositType;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("SettlementCurrency") ||
                   rowKey == I_("LUX_SettlementCurrency") || //for redemption
                   rowKey == I_("CAD_SettlementCurrency") ||   //for redemption
                   rowKey == I_("ToCurrency")) //for transfers/exchanges/rollovers
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettleCurrency;
            idSubstitution = ifds::SettleCurrency;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("ExchangeRate") ||
                   rowKey == I_("LUX_ExchangeRate") ||
                   rowKey == I_("CAD_ExchangeRate"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ExchRate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if (rowKey == I_("AccountabilityCode"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::Accountable;
            idSubstitution = ifds::Accountable;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nComboSortingMode = DSTGridWnd::GRD_CMB_SORT_STATE::DESC_ASCENDING;
         }
         else if (rowKey == I_("BackdatedReason"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::BackDatedReason;
            idSubstitution = ifds::BackDatedReason;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
		 else if (rowKey == I_("SettleNetwork"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettleNetwork;
            idSubstitution = ifds::SettleNetwork;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("AcquisitionFeeOption"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::AcqFeeOption;
            idSubstitution = ifds::AcqFeeOption;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("Discount"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DiscountRate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
            mask           = I_("&.&&&&########");
         }
         else if (rowKey == I_("FundBroker"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::FundBrokerCode;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("AggregateOption"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::AggregateOption;
            idSubstitution = ifds::AggregateOption;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("AggOrdAdjustNum"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::AggOrdAdjustNum;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("NetworkID"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::NetworkID;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SendRefNum"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SendRefNum;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("DealDate"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DealDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
         }
         else if (rowKey == I_("SettleInDate"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettleInDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
         }
         else if (rowKey == I_("DealTime"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DealTime;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_MASKEDIT;
            mask           = I_ ("##:##");
         }
         else if (rowKey == I_("CashDate"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::CashDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
         }
         else if (rowKey == I_("ValueDate"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ValueDate;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         }
         else if (rowKey == I_("DepositId"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DepId;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("ProvinceOfSales"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ProvSales;
            idSubstitution = ifds::ProvSales;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SourceOfFund"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SrcOfFund;
            idSubstitution = ifds::SrcOfFund;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SourceOfAccount"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SrcOfAccount;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("SettleBy"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettledBy;
            idSubstitution = ifds::SettledBy;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("OrderSource"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::OrderSource;
            idSubstitution = ifds::OrderSource;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SettlementSource"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettleSource;
            idSubstitution = ifds::SettleSource;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SettlementType"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SettleType;
            idSubstitution = ifds::SettleType;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("ExpectedSettlementGN"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ExpGNSettle;
            idSubstitution = ifds::ExpGNSettle;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("TaxReceiptIssued"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RecptIssued;
            idSubstitution = ifds::RecptIssued;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         }
         else if (rowKey == I_("CertificateRequired"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::CertRequired;
            idSubstitution = ifds::CertRequired;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("ConfirmRequired"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ConfirmRequired;
            idSubstitution = ifds::ConfirmRequired;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("NetworkRespRequired"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::NetworkRespRequired;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("OtherConfirmType"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::OtherConfirmType;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("InitialPurchase"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::InitPurch;
            nCellState     = DSTGridWnd::CELL_STATE::READ_ONLY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
         else if (rowKey == I_("BorrowedFunds"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::BorrowedFunds;
            idSubstitution = ifds::BorrowedFunds;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("MFPayment"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::MFPayment;
            idSubstitution = ifds::MFPayment;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("MCHFileIndicator"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::MCHFileIndicator;
            idSubstitution = ifds::MCHFileIndicator;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("SecRecFileIndicator"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SecRecFileIndicator;
            idSubstitution = ifds::SecRecFileIndicator;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("ESGSettle"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ESGSettle;
            idSubstitution = ifds::ESGSettle;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("CAD_SuppressCode") ||
                   rowKey == I_("LUX_SuppressCode"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SuppressCode;
            idSubstitution = ifds::SuppressCode;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("CAD_DeliveryMethod") ||
                   rowKey == I_("LUX_DeliveryMethod"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::DeliveryMethod;
            idSubstitution = ifds::DeliveryMethod;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("RedemptionCode"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RedCode;
            idSubstitution = ifds::RedCode;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("PFCrystalisation"))
         {
         idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::PFCrystalisation;
            idSubstitution = ifds::PFCrystalisation;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("PaymentInfo"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::PaymentInfo;
            idSubstitution = ifds::PaymentInfo;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("PendTrdContract"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::PendTrdContract;
            idSubstitution = ifds::PendTrdContract;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("ValuationDt")) 
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ValuationDt;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         }
         else if (rowKey == I_("LSIFReason"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::LSIFCode;
            idSubstitution = ifds::LSIFCode;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("BankCharges"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::BankChrgs;
            idSubstitution = ifds::BankChrgs;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("FromCurrency"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::FromCurrency;
            idSubstitution = ifds::FromCurrency;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("UseEnteredFee"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::UseEnteredFee;
            idSubstitution = ifds::UseEnteredFee;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("ROAAmount"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::ROAAmount;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if (rowKey == I_("CloneAcctAMS"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::CloneAcctAMS;
            idSubstitution = ifds::CloneAcctAMS;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("LinkedEntityId"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::LinkedEntityId;
            idSubstitution = ifds::LinkedEntityId;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("AssocTransId"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::AssocTransId;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if ( rowKey == I_("RESPReportHRDC"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RESPReportHRDC;
            idSubstitution = ifds::RESPReportHRDC;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("GRRepayReason"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idSubstitution = ifds::GRRepayReason;
            idField        = ifds::GRRepayReason;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("OCRdmYear"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::OCRdmYear;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if ( rowKey == I_("RESPContrDetlTaxYear"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RESPContrDetlTaxYear;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if ( rowKey == I_("Tainted"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::Tainted;
            idSubstitution = ifds::Tainted;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if ( rowKey == I_("AssistedContrAmt"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::AssistedContrAmt;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if (rowKey == I_("EAPCESGPaid"))
         {//IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::EAPCESGPaid;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
         else if ( rowKey == I_("RedemOrder"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RedemOrder;
            idSubstitution = ifds::GIRedemOrder;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else if (rowKey == I_("GuaranteesOverride"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::GuaranteesOverride;
            idSubstitution = ifds::GuaranteesOverride;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
		 else if (rowKey == I_("RightToCancel"))   
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RightToCancel;
            idSubstitution = ifds::RightToCancel;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
		 
		 else if (rowKey == I_("RDRAdvice"))
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::RDRAdvice;
            idSubstitution = ifds::RDRAdvice;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
		 else if (rowKey == I_("SDRTExemptCode"))   
         {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::SDRTExemptCode;
            idSubstitution = ifds::SDRTExemptCode;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_EDIT;
         }
		 else if (rowKey == I_("ExtTransNum"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::ExtTransNum;
			 idSubstitution = ifds::ExtTransNum;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 DString dstrAWDFieldFlag;
			 DSTCWorkSession *pDSTCWorkSession = 
                 dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
			 if( pDSTCWorkSession )
				{ 
				  pDSTCWorkSession->getOption (ifds::AWDFieldFlag, dstrAWDFieldFlag,BF::HOST,false);
				  if(dstrAWDFieldFlag.stripAll() == I_("Y"))
				   {
				     cellCtrlType   = IDS_CTRL_ALPHNUMEDIT;	
					 dstrAllowedChar = ALLOWED_CHARACTERS ;
                   }
			    }
			 else
				{
					cellCtrlType   = GX_IDS_CTRL_EDIT;
				}               
		 }
		 else if (rowKey == I_("PSDAdvice"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::PSDAdvice;
			 idSubstitution = ifds::PSDAdvice;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if (rowKey == I_("PymtRoutingMthd"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::PymtRoutingMthd;
			 idSubstitution = ifds::PymtRoutingMthd;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		else if (rowKey == I_("EventReceiptDate"))
		{
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::EventReceiptDate;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_DATETIME;
		}
		else if (rowKey == I_("EventReceiptTime"))
		{
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::EventReceiptTime;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_EDIT; 
			//mask           = I_ ("##:##:##");
		}
		 else if (rowKey == I_("Platform"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::Platform;
			 idSubstitution = ifds::Platform;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if (rowKey == I_("SourceOfTrade"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::SourceOfTrade;
			 idSubstitution = ifds::SourceOfTrade;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if (rowKey == I_("ChannelOfTrade"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::ChannelOfTrade;
			 idSubstitution = ifds::ChannelOfTrade;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
         else if ( I_("DeliveryNetwork") == rowKey )
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::DeliveryNetwork;
			 idSubstitution = ifds::DeliveryNetwork;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("RefundAmtOpt") == rowKey )
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::RefundAmtOpt;
			 idSubstitution = ifds::RefundAmtOpt;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("CrossSysAcctNum") == rowKey)
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::CrossSysAcctNum;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = IDS_CTRL_NUMEDIT;//need to set the number of character to 14...
		 }
		 else if ( I_("AggregationType") == rowKey)
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::AggregationType;
			 idSubstitution = ifds::AggregationType;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("SourceofFundsChecked") == rowKey)
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::SourceofFundsChecked;
			 idSubstitution = ifds::SourceofFundsChecked;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("ExternalInstitution") == rowKey)
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::ExternalInstitution;
			 idSubstitution = ifds::ExternalInstitution;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_EDIT; 
			 //cellCtrlType   = IDS_CTRL_ALPHNUMEDIT2;
		 }
		 else if ( rowKey == I_("Deconversion"))
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::Deconversion;
			 idSubstitution = ifds::Deconversion;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("OrderRouting") == rowKey )
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::OrderRouting;
			 idSubstitution = ifds::OrderRouting;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if (I_("TradeInDate") == rowKey )
		 {
            idContainer    = IFASTBP_PROC::TRADES_LIST;
            idField        = ifds::TradeInDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
		 }
		 else if (I_("ValuationInDt") == rowKey)
		 {
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::ValuationInDt;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_DATETIME;
		 }

		 else if ( I_("PricingCode") == rowKey )
		 {
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::PricingCode;
			idSubstitution = ifds::PricingCode;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }		
		 else if ( I_("PriceInCode") == rowKey )
		 {
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::PriceInCode;
			idSubstitution = ifds::PriceInCode;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("FullMoneyOutIndc") == rowKey )
		 {
			idContainer    = IFASTBP_PROC::TRADES_LIST;
			idField        = ifds::FullMoneyOutIndc;
			idSubstitution = ifds::FullMoneyOutIndc;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("GateOverrideIndicator") == rowKey )
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::GateOverrideIndicator;
			 idSubstitution = ifds::GateOverrideIndicator;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
		 }
		 else if ( I_("RDSPPaymtDate") == rowKey )
		 {
			 idContainer    = IFASTBP_PROC::TRADES_LIST;
			 idField        = ifds::RDSPPaymtDate;			 		
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_DATETIME;
		 }
		 else 
		 {
			 nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
		 }
      }
   }
   else if (ctrlId == IDC_GRD_FEES)
   {
      if (colKey == I_("FeeName"))
      {
         idContainer    = TRANS_FEE_LIST;
         idField        = ifds::TransFeeCode;
         idSubstitution = ifds::TransFeeCode;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      if (colKey == I_("FeeType"))
      {
         idContainer    = TRANS_FEE_LIST;
         idField        = ifds::FeeType;
         idSubstitution = ifds::FeeType;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      if (colKey == I_("FeeRate"))
      {
         idContainer    = TRANS_FEE_LIST;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;

         DString isChargeFee;

         getParent ()->getField ( this,
                                  TRANS_FEE_LIST,
                                  IsChargeFee,
                                  isChargeFee,
                                  false);
         if (isChargeFee == I_("Y"))
         {
            idField        = ifds::FeeCharge;
            idSubstitution = ifds::FeeCharge;
            cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         }
         else
         {
            idField        = ifds::FeeRate;
            cellCtrlType   = IDS_CTRL_NUMEDIT;
         }
      }
      if (colKey == I_("FeeOption"))
      {
         idContainer    = TRANS_FEE_LIST;
         idField        = ifds::TradeFeeOption;
         idSubstitution = ifds::TradeFeeOption;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      if (colKey == I_("FeeCurrency"))
      {
         idContainer    = TRANS_FEE_LIST;
         idField        = ifds::Currency;
         idSubstitution = ifds::Currency;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      if (colKey == I_("ChargeOption"))
      {
         idContainer    = TRANS_FEE_LIST;
         idField        = ifds::ChargeOption;
         idSubstitution = ifds::ChargeOption;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
   }
}

//******************************************************************************
bool TradesDlg::GetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              DString &strOut,
                              bool bFormatted)
{
   return false;
}

//method, looks for accounts based on search criteria (Alt Acct, Other Ref)
//******************************************************************************
void TradesDlg::searchForAccounts ( const DString &searchUsing, 
                                    const DString &firstValue,
                                    const BFContainerId &idSearch,
                                    UINT controlID)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("searchForAccounts"));
   CWaitCursor wait;

   m_bSearchInProgress = true; //search started

   DString accountNum;
   UINT accountControlID = -1;
   UINT otherControlID = -1;

   if ( idSearch == SEARCH_ALT_ACCOUNT_TO ||
        idSearch == SEARCH_X_REF_NUM_TO)
   {
      accountControlID = IDC_EDT_TO_ACCOUNT;
   }
   else if ( idSearch == SEARCH_ALT_ACCOUNT_FROM ||
             idSearch == SEARCH_X_REF_NUM_FROM)
   {
      accountControlID = IDC_EDT_FROM_ACCOUNT;
   }
   else if ( idSearch == SEARCH_ALT_ACCOUNT ||
             idSearch == SEARCH_X_REF_NUM)
   {
      accountControlID = IDC_EDT_ACCOUNT;
   }
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      if (idSearch == SEARCH_ALT_ACCOUNT)
      {
         otherControlID = IDC_EDT_OTHER_REFERENCE;
      }
      else if (idSearch == SEARCH_ALT_ACCOUNT_FROM)
      {
         otherControlID = IDC_EDT_FROM_OTHER_REFERENCE;
      }
      else if (idSearch == SEARCH_ALT_ACCOUNT_TO)
      {
         otherControlID = IDC_EDT_TO_OTHER_REFERENCE;
      }
      else if (idSearch == SEARCH_X_REF_NUM)
      {
         otherControlID = IDC_EDT_ALT_ACCOUNT;
      }
      else if (idSearch == SEARCH_X_REF_NUM_FROM)
      {
         otherControlID = IDC_EDT_FROM_ALT_ACCOUNT;
      }
      else if (idSearch == SEARCH_X_REF_NUM_TO)
      {
         otherControlID = IDC_EDT_TO_ALT_ACCOUNT;
      }
   }

   BaseControl *pAccountControl = GetControl (accountControlID);

   if (pAccountControl)
   {
      pAccountControl->GetText (accountNum);
      if ( !m_bTradeListSelectionInProgress && //do not search if user changes the list trades selection
           !firstValue.empty() && //do not search if search criteria is empty
            ( pAccountControl->LoadErrorState () > WARNING || //search if account is in an invalid state, or
              accountNum.empty() || //if account num is empty, or
              GetControl (controlID)->LoadErrorState() > WARNING)) //if the search control is in an invalid state
      {
         setParameter ( SRCHLIT::SEARCH_CRITERIA_CODE, 
                        SEARCHCRITERIA::ACCOUNT_SEARCH);
         setParameter ( SRCHLIT::SEARCH_USING_CODE, 
                        searchUsing);
         setParameter ( SRCHLIT::FIRST_VALUE, 
                        firstValue);
         setParameter ( I_("BackgroundSearch"),  //do not want to show account details if a match after search
                        I_("Y"));
         setParameter ( I_("NoVerifySearchIfOneMatch"),  //do not want to show verify search if one match
                        I_("Y"));
         if (getParentProcess ()->performSearch ( this, 
                                                  idSearch,
                                                  SEARCH_START) <= WARNING)
         {
            //if user hit cancel on the verify search dialog 
            //reload the search control
            DString isCancelHitOnVerifySearch;

            getParent ()->getField ( this,
                                     IFASTBP_PROC::TRADES_LIST,
                                     IsCancelHitOnVerifySearch,
                                     isCancelHitOnVerifySearch,
                                     false);
            if (isCancelHitOnVerifySearch == I_("Y"))
            {
               //loading the control triggers another call of this method, 
               //but the search will not be performed, since the 'search field' is empty
               GetControl (controlID)->Load ();
               //turn the flag off
               getParent ()->setField ( this,
                                        IFASTBP_PROC::TRADES_LIST,
                                        IsCancelHitOnVerifySearch,
                                        I_("N"));
            }
            else
            {
               if (GetControl (accountControlID)->LoadErrorState () > WARNING)
               {
                  GetControl (controlID)->Load ();
               }
            }
         }
         else
         {
            //loading the control triggers another call of this method, 
            //but the search will not be performed, since the 'search field' is empty, on error
            GetControl (controlID)->Load ();
         }
         LoadControl (accountControlID);
      }
   }
//always load the error state of the control that triggers the search
   GetControl (controlID)->LoadErrorState ();
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (otherControlID)->LoadErrorState ();
   }
   
   m_bSearchInProgress = false; //search donee
}


//F4 helper dialogs
//******************************************************************
LRESULT TradesDlg::OpenBrokerListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenBrokerListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode;

      GetControlText (IDC_EDT_BROKER_CODE, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);

//invoke the broker dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_BROKER, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter (I_("BrokerCode"), brokerCode);
               if (!brokerCode.empty ())
               {
		            getParent()->setField ( this, 
                                          IFASTBP_PROC::TRADES_LIST, 
                                          ifds::Broker, 
                                          brokerCode, 
                                          false);
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************
LRESULT TradesDlg::OpenBranchListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenBranchListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode;

      GetControlText (IDC_EDT_BROKER_CODE, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);
//invoke the branch dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_BRANCH, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString branchCode;

               getParameter (I_("BranchCode"), branchCode);
               if (!branchCode.empty ())
               {
		            getParent()->setField ( this, 
                                          IFASTBP_PROC::TRADES_LIST, 
                                          ifds::Branch, 
                                          branchCode, 
                                          false);
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************
LRESULT TradesDlg::OpenSlsRepListDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenSlsRepListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode,
         branchCode;

      GetControlText (IDC_EDT_BROKER_CODE, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);
      GetControlText (IDC_EDT_BRANCH_CODE, branchCode);
      setParameter (I_("BranchCode"), branchCode);
//invoke the sales rep dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_SLSREP, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString slsrepCode;

               getParameter (I_("AgentCode"), slsrepCode);
               if (!slsrepCode.empty ())
               {
		            getParent()->setField ( this, 
                                          IFASTBP_PROC::TRADES_LIST, 
                                          ifds::SlsrepCode, 
                                          slsrepCode, 
                                          false);
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************
LRESULT TradesDlg::OpenAddrBookDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenAddrBookDlg"));
   CWaitCursor wait;

   try
   {
      DString accountNum,
         shrNum;

      getParent ()->getField ( this,
                               SHAREHOLDER,
                               ifds::ShrNum,
                               shrNum,
                               false);
      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               ifds::AccountNum,
                               accountNum,
                               false);
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (MFCAN_IP_PARAM::SHR_NUM, shrNum);
      SetMessageStatusBar (TXT_LOAD_ADDRESS_BOOK);
//invoke the address dialog 
      switch (invokeCommand ( getParent(), 
                              CMD_BPROC_ADDRESSES,
                              PROC_SUPPORT, 
                              true, //modal
                              NULL))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString addrCode,
                  _addrCode;

               getParent ()->getField ( this,
                                        IFASTBP_PROC::TRADES_LIST,
                                        ifds::AddrCode,
                                        _addrCode,
                                        false);
               getParameter (I_("AddressCode"), addrCode);
               if (!addrCode.empty ())
               {
                  if (addrCode != _addrCode)
                  {
                     SetControlText (IDC_EDT_SHAREHOLDER_ADDR_CODE, addrCode);
                     LoadControl (IDC_EDT_SHAREHOLDER_ADDR_CODE);
                  }
                  else //force a load on the entire address, data might have changed
                  {
                     LoadControl (IDC_EDT_SHAREHOLDER_ADDR);
                  }
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   SetMessageStatusBar (NULL_STRING);
   return 0;
}

//******************************************************************
LRESULT TradesDlg::OpenAccountSearchDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenAccountSearchDlg"));
   CWaitCursor wait;

   DString accountNum;

//don't allow user to open account search unless they cleared the account number, why (???)
   if (accountNum.empty())
   {
      try
      {
   //invoke the account search helper dialog
         switch (getParentProcess ()->
                    invokeProcessFromChild ( this, 
                                             CMD_BPROC_IDENT_ACC, 
                                             PROC_SUPPORT))
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
                  getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
                  if (!accountNum.empty ())
                  {
                     int iAccountNumCtrlId = m_pCWndF4Focus->GetDlgCtrlID ();
                  
                     SetControlText (iAccountNumCtrlId, accountNum);
                     LoadControl (iAccountNumCtrlId);
                  }
                  break;
               }
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox ( FRAMEBELOW (), 
                                     GETHIGHESTSEVERITY ());
               break;
         }
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
   return 0;
}

//******************************************************************************
LRESULT TradesDlg::OpenFundClassListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenFundClassListDlg"));
   CWaitCursor wait;      

   try
   {
      int iFundCtrlId = m_pCWndF4Focus->GetDlgCtrlID ();
      DString shrNum, 
         accountNum, 
         transType;

//find whether the control is 'to side' one
      bool bToSideFundControl = iFundCtrlId == IDC_EDT_TO_FUND_CODE ||
                                iFundCtrlId == IDC_EDT_TO_FUND_CLASS ||
                                iFundCtrlId == IDC_EDT_TO_FUND_NBR ||
                                iFundCtrlId == IDC_EDT_TO_ISIN ||
                                iFundCtrlId == IDC_EDT_TO_WKN ||
                                iFundCtrlId == IDC_EDT_TO_LFC ||
								iFundCtrlId == IDC_EDT_TO_CUSIP;
      
      if (!bToSideFundControl)
      {
         getParent ()->getField (this, SHAREHOLDER, ifds::ShrNum, shrNum);
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::AccountNum, 
                                  accountNum, 
                                  false);
      }
      else
      {
         getParent ()->getField (this, SHAREHOLDER_TO, ifds::ShrNum, shrNum);
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::TRADES_LIST, 
                                  ifds::AccountTo, 
                                  accountNum, 
                                  false);
      }
      getParent ()->getField ( this, 
                               IFASTBP_PROC::TRADES_LIST, 
                               ifds::TradesTransType, 
                               transType, 
                               false);
      if (transType == TRADETYPE::ROLLOVER) //filter for 'LSIF'funds
      {
         setParameter (I_("FundCategory"), I_("L")); //filter for LSIF funds
      }
      shrNum.strip ().stripLeading (I_CHAR ('0'));
      accountNum.strip ().stripLeading (I_CHAR ('0'));
      setParameter (MFCAN_IP_PARAM::SHR_NUM, shrNum);
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);

      bool bGetFundAndClass = false,
         bGetFundNumber = false,
         bGetWKNNumber = false,
         bGetISINNumber = false,
         bGetLFCNumber = false,
		 bGetCUSIPNumber = false;

      int iFundCodeCtrlId = -1,
         iFundClassCtrlId = -1;

      switch (iFundCtrlId)
      {
         case IDC_EDT_FUND_CODE:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
            }
            //let it fall through
         case IDC_EDT_FROM_FUND_CODE:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
               }
            }
            //let it fall through
         case IDC_EDT_TO_FUND_CODE:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
               }

               CString cstrFundCode;
               
               GetDlgItem (iFundCtrlId)->GetWindowText (cstrFundCode);
               setParameter (MFCAN_IP_PARAM::FUND_CODE, DString (cstrFundCode));
               iFundCodeCtrlId = iFundCtrlId;
               bGetFundAndClass = true;
            }
            break;
         case IDC_EDT_FUND_CLASS:
            {
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_FROM_FUND_CLASS:
            {
               if (iFundCodeCtrlId == -1) //not set yet?
               {
                  iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
               }
            }
            //let it fall through
         case IDC_EDT_TO_FUND_CLASS:
            {
               if (iFundCodeCtrlId == -1) //not set yet?
               {
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrFundClass;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrFundClass);
               setParameter (MFCAN_IP_PARAM::CLASS_CODE, DString (cstrFundClass));
               iFundClassCtrlId = iFundCtrlId;
               bGetFundAndClass = true;
            }
            break;
         case IDC_EDT_FUND_NBR:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_FROM_FUND_NBR:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
               }
            }
            //let it fall through
         case IDC_EDT_TO_FUND_NBR:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrFundNumber;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrFundNumber);
               setParameter (MFCAN_IP_PARAM::FUND_NUMBER, DString (cstrFundNumber));
               bGetFundNumber = true;
            }
            break;
         case IDC_EDT_WKN:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_FROM_WKN:
            if (iFundClassCtrlId == -1) //not set yet?
            {
               iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_TO_WKN:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrWKKNumber;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrWKKNumber);
               setParameter (MFCAN_IP_PARAM::FUND_WKN, DString (cstrWKKNumber));
               bGetWKNNumber = true;
            }
            break;
         case IDC_EDT_LFC:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_FROM_LFC:
            if (iFundClassCtrlId == -1) //not set yet?
            {
               iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_TO_LFC:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrLFCNumber;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrLFCNumber);
               setParameter (MFCAN_IP_PARAM::FUND_LFC, DString (cstrLFCNumber));
               bGetLFCNumber = true;
            }
            break;
		     //let it fall through
		  case IDC_EDT_CUSIP:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
         case IDC_EDT_FROM_CUSIP:
            if (iFundClassCtrlId == -1) //not set yet?
            {
               iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_TO_CUSIP:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrCUSIPNumber;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrCUSIPNumber);
			   setParameter (MFCAN_IP_PARAM::CUSIP, DString (cstrCUSIPNumber));
               bGetCUSIPNumber = true;
            }
            break;
         case IDC_EDT_ISIN:
            {
               iFundClassCtrlId = IDC_EDT_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_FROM_ISIN:
            if (iFundClassCtrlId == -1) //not set yet?
            {
               iFundClassCtrlId = IDC_EDT_FROM_FUND_CLASS;
               iFundCodeCtrlId = IDC_EDT_FROM_FUND_CODE;
            }
            //let it fall through
         case IDC_EDT_TO_ISIN:
            {
               if (iFundClassCtrlId == -1) //not set yet?
               {
                  iFundClassCtrlId = IDC_EDT_TO_FUND_CLASS;
                  iFundCodeCtrlId = IDC_EDT_TO_FUND_CODE;
               }
               CString cstrISINNumber;

               GetDlgItem (iFundCtrlId)->GetWindowText (cstrISINNumber);
               setParameter (MFCAN_IP_PARAM::FUND_ISIN, DString (cstrISINNumber));
               bGetISINNumber = true;
            }
            break;
      }
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_FUNDCLASS, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString parameter,
                  fundCode,
                  classCode;

               getParameter (MFCAN_IP_PARAM::FUND_CODE, fundCode);
               getParameter (MFCAN_IP_PARAM::CLASS_CODE, classCode);
               if (bGetFundAndClass)
               {
                  SetControlText (iFundCodeCtrlId, fundCode);
                  SetControlText (iFundClassCtrlId, classCode);
                  //should be already set
                  assert (iFundCodeCtrlId != -1); 
                  assert (iFundClassCtrlId != -1);
                  LoadControl (iFundCodeCtrlId);
                  LoadControl (iFundClassCtrlId);
               }
               else if (bGetFundNumber)
               {
                  getParameter (MFCAN_IP_PARAM::FUND_NUMBER, parameter);
               }
               else if (bGetWKNNumber)
               {
                  getParameter (MFCAN_IP_PARAM::FUND_WKN, parameter);
               }
               else if (bGetLFCNumber)
               {
                  getParameter (MFCAN_IP_PARAM::FUND_LFC, parameter);
               }
			   else if (bGetCUSIPNumber)
			   {
				    getParameter (MFCAN_IP_PARAM::CUSIP, parameter);
			   }
               else if (bGetISINNumber)
               {
                  getParameter (MFCAN_IP_PARAM::FUND_ISIN, parameter);
               }
               if (!parameter.empty()) //all the others...
               {
                  SetControlText (iFundCtrlId, parameter);
                  LoadControl (iFundCtrlId);
               }
               else //hopefully fund and class are never empty
               {
                  SetControlText (iFundCodeCtrlId, fundCode);
                  SetControlText (iFundClassCtrlId, classCode);
                  //should be already set
                  assert (iFundCodeCtrlId != -1); 
                  assert (iFundClassCtrlId != -1);
                  LoadControl (iFundCodeCtrlId);
                  LoadControl (iFundClassCtrlId);
               }
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
         break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************************
LRESULT TradesDlg::OpenAssocTransIdHelper (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenAssocTransIdHelpe"));
   try
   {
      CWaitCursor wait;   
      E_COMMANDRETURN eRtn = CMD_OK;
   
      DString screenTitle (I_("Grant Contribution Screen for Beneficiary:")),
         urlParamsIDI,
         accountNum,
         entityId,
         grRepayReasonCode,
         depositType,
         redCode,
		 effectiveDate,
		 paymentDate;	

      if (isOneSideTrade ())
      {
         getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, accountNum, false);
      }
      else 
      {
         getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountTo, accountNum, false);
      }
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::LinkedEntityId, entityId, false);
      
      DString entityIdName, reasonCodeName, dstrAmount;
      
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::LinkedEntityId, entityIdName);
      screenTitle += entityIdName;
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::GRRepayReason, grRepayReasonCode, false);
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::GRRepayReason, reasonCodeName);
	  CString cstrRepaymentCode;
	  cstrRepaymentCode.LoadString(TXT_REPAYMENT_REASON_CODE);
      screenTitle += DString(cstrRepaymentCode) + reasonCodeName;
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::DepositType, depositType, false);
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::RedCode, redCode, false);

      if (!accountNum.empty ())
      {
         addIDITagValue (urlParamsIDI, I_("AccountNum"), accountNum);
      }      
      if (!entityId.empty())
      {
         addIDITagValue (urlParamsIDI, I_("RESPBenID"), entityId);
      }
      if (!grRepayReasonCode.empty())
      {
         addIDITagValue (urlParamsIDI, I_("ReasonCode"), grRepayReasonCode);
      }
      if (!depositType.empty())
      {
         addIDITagValue (urlParamsIDI, I_("DepositType"), depositType);
      }
      if (!redCode.empty())
      {
         addIDITagValue (urlParamsIDI, I_("RedCode"), redCode);
      }
	  if (DSTCommonFunctions::codeInList(depositType,I_("20,35,49,73"))) // 20-CESG Grant,35-SAGES Grant Payment,49-RDSP Grant,73-Additional CESG Grant
	  {
		  getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::Amount, dstrAmount, false);
		  addIDITagValue (urlParamsIDI, I_("GRAmount"), dstrAmount);
	  }
	  else 
		  addIDITagValue (urlParamsIDI, I_("GRAmount"), I_("0.00"));
	        
      addIDITagValue (urlParamsIDI, I_("screen"), I_("GrantContrib")); //DesktopWeb conversion
      
	  DString taxType, screenTitleRDSP;
	  getParent()->getField( this, ACCOUNT, ifds::TaxType, taxType, false );
	  taxType.strip().upperCase();

	  if (taxType == RDSP_TAX_TYPE)
	  {		  
		  if ( redCode == I_("BP"))	// RDSP Bond Repayment
			  screenTitleRDSP = I_("Bond Repayment Screen: AccountNumber = ");
		  else if (redCode == I_("GP"))	// RDSP Grant Repayment
			  screenTitleRDSP = I_("Grant Repayment Screen: AccountNumber = ");
		  else if (redCode == I_("RB"))	// RDSP Bond Return
			  screenTitleRDSP = I_("Bond Return Screen: AccountNumber = ");
		  else if (redCode == I_("RG"))	// RDSP Grant Repayment
			  screenTitleRDSP = I_("Grant Return Screen: AccountNumber = ");
		  else // RDSP Grant
			  screenTitleRDSP = I_("Grant Contribution Screen: AccountNumber = ");

		  screenTitle = screenTitleRDSP + accountNum;

		  getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::EffectiveDate, effectiveDate, false);
		  addIDITagValue (urlParamsIDI, I_("TradeDate"), effectiveDate);
		  getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::RDSPPaymtDate, paymentDate, false);
		  addIDITagValue (urlParamsIDI, I_("PaymentDate"), paymentDate);
	  }

      setParameter (I_("UrlParams"), urlParamsIDI);
      setParameter(I_("BrowserTitle"), screenTitle );
      setParameter (I_("from_screen"), I_("TradesDlg"));
      eRtn = invokeCommand (getParent(), CMD_BPROC_GRANT_CONTRIB, PROC_SUPPORT, true, NULL);

      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            DString dstrReturnResult;

            getParameter (I_("BrowserResults"), dstrReturnResult);
            I_CHAR *temp = const_cast<I_CHAR*> (dstrReturnResult.c_str ());

            do
            {
               DString tag,
	               value;

               temp = parseIdiString (temp, tag, value);

               if (I_("EntityID") == tag && value != entityId)
               {
	               getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::LinkedEntityId, value);
                  m_pAttributesGrdWnd->reloadCell (I_("LinkedEntityId"), I_("Value"));
               }
               else if (I_("TransID") == tag)
               {
	               getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::AssocTransId, value);
                  m_pAttributesGrdWnd->reloadCell (I_("AssocTransId"), I_("Value"));
               }

            } while (temp && temp != NULL_STRING && *temp);
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
   return 0;
}

//******************************************************************************
LRESULT TradesDlg::OpenExternalInstitutionSearchDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenExternalInstitutionSearchDlg"));
   try
   {
      DString tradeKey;

      tradeKey = getParent ()->getCurrentListItemKey ( this, 
                                                       IFASTBP_PROC::TRADES_LIST);

      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);

      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString extInstitutionCode;

               getParameter (I_("ExternalInstitution"), extInstitutionCode);
               if (!extInstitutionCode.empty ())
               {
                  getParent()->setField ( this, 
                                          IFASTBP_PROC::TRADES_LIST, 
                                          ifds::ExternalInstitution, 
                                          extInstitutionCode, 
                                          false);

                  m_pAttributesGrdWnd->reloadCell (I_("ExternalInstitution"), I_("Value"));
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                                  GETHIGHESTSEVERITY ());
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
   return 0;
}

//convenient methods
//******************************************************************************
void TradesDlg::show2Sides (const DString &transType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("show2Sides"));
   
   CWaitCursor wait;
   
   bool bShow2Sides = !isOneSideTrade (transType);
   
   GetControl (IDC_STC_ACCT_FUND_INFO)->Show (!bShow2Sides);
   GetControl (IDC_STC_SHAREHOLDER_INFO)->Show (!bShow2Sides);
   GetControl (IDC_STC_ACCOUNT)->Show (!bShow2Sides);
   GetControl (IDC_EDT_ACCOUNT)->Show (!bShow2Sides);
   GetControl (IDC_STC_ALT_ACCOUNT_LABEL)->Show (!bShow2Sides);
   GetControl (IDC_EDT_ALT_ACCOUNT)->Show (!bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_OTHER_REFERENCE)->Show (!bShow2Sides);
      GetControl (IDC_EDT_OTHER_REFERENCE)->Show (!bShow2Sides);
   }
   GetControl (IDC_STC_FUND)->Show (!bShow2Sides);
   GetControl (IDC_EDT_FUND_NBR)->Show (!bShow2Sides);
   GetControl (IDC_EDT_FUND_CODE)->Show (!bShow2Sides);
   GetControl (IDC_STC_FUND_CLASS)->Show (!bShow2Sides);
   GetControl (IDC_EDT_FUND_CLASS)->Show (!bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_ISIN)->Show (!bShow2Sides);
      GetControl (IDC_EDT_ISIN)->Show (!bShow2Sides);

      DString dstrAltFndIdntfr;
	   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);

      GetControl (IDC_STC_WKN)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_EDT_WKN)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_STC_LFC)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("1"));
      GetControl (IDC_EDT_LFC)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("1"));

	  GetControl (IDC_STC_CUSIP)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("2"));
      GetControl (IDC_EDT_CUSIP)->Show (!bShow2Sides && dstrAltFndIdntfr == I_("2"));

   }
   GetControl (IDC_STC_FUND_SETTLE_UNITS_LABEL)->Show (!bShow2Sides);
   GetControl (IDC_STC_FUND_SETTLE_UNITS)->Show (!bShow2Sides);
   GetControl (IDC_STC_FUND_MKT_VALUE_LABEL)->Show (!bShow2Sides);
   GetControl (IDC_STC_FUND_SETTLE_VALUE)->Show (!bShow2Sides);
   GetControl (IDC_STC_ACCT_MKT_LABEL)->Show (!bShow2Sides);
   GetControl (IDC_STC_ACCT_MKT_VALUE)->Show (!bShow2Sides);
   GetControl (IDC_STC_ADDRESS)->Show (!bShow2Sides);
   GetControl (IDC_EDT_ADDRESS)->Show (!bShow2Sides);
   GetControl (IDC_STC_SHAREHOLDER_LABEL)->Show (!bShow2Sides);
   GetControl (IDC_STC_SHAREHOLDER)->Show (!bShow2Sides);
   GetControl (IDC_STC_SHAREHOLDER)->Show (!bShow2Sides);
   GetControl (IDC_STC_CAUTIONS)->Show (!bShow2Sides);
   GetControl (IDC_CMB_CAUTIONS)->Show (!bShow2Sides);

//from side
   GetControl (IDC_STC_FROM)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_ACCOUNT)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_ACCOUNT)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_ALT_ACCOUNT_LABEL)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_ALT_ACCOUNT)->Show (bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_FROM_OTHER_REFERENCE)->Show (bShow2Sides);
      GetControl (IDC_EDT_FROM_OTHER_REFERENCE)->Show (bShow2Sides);
   }
   GetControl (IDC_STC_FROM_FUND)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_FUND_NBR)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_FUND_CODE)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_FUND_CLASS)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_FUND_CLASS)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_FUND_SETTLE_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_FUND_SETTLE_UNITS)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_FUND_SETTLE_VALUE)->Show (bShow2Sides);
   GetControl (IDC_EDT_FROM_ADDRESS)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_SHAREHOLDER_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_SHAREHOLDER)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_ACCT_MKT_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_ACCT_MKT)->Show (bShow2Sides);
   GetControl (IDC_STC_FROM_CAUTIONS)->Show (bShow2Sides);
   GetControl (IDC_CMB_FROM_CAUTIONS)->Show (bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_FROM_ISIN)->Show (bShow2Sides);
      GetControl (IDC_EDT_FROM_ISIN)->Show (bShow2Sides);

      DString dstrAltFndIdntfr;
	   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);

      GetControl (IDC_STC_FROM_WKN)->Show (bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_EDT_FROM_WKN)->Show (bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_STC_FROM_LFC)->Show (bShow2Sides && dstrAltFndIdntfr == I_("1"));
      GetControl (IDC_EDT_FROM_LFC)->Show (bShow2Sides && dstrAltFndIdntfr == I_("1"));

	  GetControl (IDC_STC_FROM_CUSIP)->Show (bShow2Sides && dstrAltFndIdntfr == I_("2"));
      GetControl (IDC_EDT_FROM_CUSIP)->Show (bShow2Sides && dstrAltFndIdntfr == I_("2"));
   }
//to side
   GetControl (IDC_STC_TO)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_ACCOUNT)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_ACCOUNT)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_ALT_ACCOUNT_LABEL)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_ALT_ACCOUNT)->Show (bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_TO_OTHER_REFERENCE)->Show (bShow2Sides);
      GetControl (IDC_EDT_TO_OTHER_REFERENCE)->Show (bShow2Sides);
   }
   GetControl (IDC_STC_TO_FUND)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_FUND_NBR)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_FUND_CODE)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_FUND_CLASS)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_FUND_CLASS)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_FUND_SETTLE_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_FUND_SETTLE_UNITS)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_FUND_SETTLE_VALUE)->Show (bShow2Sides);
   GetControl (IDC_EDT_TO_ADDRESS)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_SHAREHOLDER_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_SHAREHOLDER)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_ACCT_MKT_LABEL)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_ACCT_MKT)->Show (bShow2Sides);
   GetControl (IDC_STC_TO_CAUTIONS)->Show (bShow2Sides);
   GetControl (IDC_CMB_TO_CAUTIONS)->Show (bShow2Sides);
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetControl (IDC_STC_TO_ISIN)->Show (bShow2Sides);
      GetControl (IDC_EDT_TO_ISIN)->Show (bShow2Sides);

      DString dstrAltFndIdntfr;
	   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);

      GetControl (IDC_STC_TO_WKN)->Show (bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_EDT_TO_WKN)->Show (bShow2Sides && dstrAltFndIdntfr == I_("0"));
      GetControl (IDC_STC_TO_LFC)->Show (bShow2Sides && dstrAltFndIdntfr == I_("1"));
      GetControl (IDC_EDT_TO_LFC)->Show (bShow2Sides && dstrAltFndIdntfr == I_("1"));

	  GetControl (IDC_STC_TO_CUSIP)->Show (bShow2Sides && dstrAltFndIdntfr == I_("2"));
      GetControl (IDC_EDT_TO_CUSIP)->Show (bShow2Sides && dstrAltFndIdntfr == I_("2"));

   }

   DString isAccountSetAndValid;

   getParent ()->getField ( this,
                            ACCOUNT,
                            IsAccountSetAndValid,
                            isAccountSetAndValid,
                            false);
   if (isAccountSetAndValid != I_("Y"))
   {
      m_pAttributesGrdWnd->reLoadGrid ();
   }
}

//******************************************************************************
bool TradesDlg::isOneSideTrade (const DString &transType)
{
   return DSTCommonFunctions::codeInList (transType, TRADETYPE::ONE_SIDE_TRADE);
}

//******************************************************************
bool TradesDlg::isOneSideTrade ()
{
   DString transType;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            ifds::TradesTransType,
                            transType,
                            false);

   return isOneSideTrade (transType);
}

//******************************************************************************
void TradesDlg::resetCautionsCombo ( UINT comboLabelId,
                                     UINT comboId)
{
   DSTComboBox *pCautionsCombo = dynamic_cast <DSTComboBox*> (GetControl (comboId));

   pCautionsCombo->ResetContent ();
//set the cautions label
   CString strCautionsLabel,
      strFormat (" (%d):"),
      strNumCautions;
   int iNumCautions = 0;

   strCautionsLabel.LoadString (TXT_CAUTIONS_LABEL);
   strNumCautions.Format (strFormat, iNumCautions);
   strCautionsLabel += strNumCautions;
   GetDlgItem (comboLabelId)->SetWindowText (strCautionsLabel);
}

//******************************************************************************
void TradesDlg::fillCautionsCombo ( UINT comboLabelId,
                                    UINT comboId,
                                    const BFContainerId &shareholderContainerId,
                                    const BFContainerId &accountContainerId,
                                    const BFContainerId &acctCategoryListContainerId)
{
#define ADD_CAUTION(containerId, fieldId, textId) \
   getParent()->getField ( \
                          this, \
                          containerId, \
                          fieldId, \
                          str, \
                          false \
                         ); \
   if (str == I_("Y")) \
   { \
      lbString.LoadString (textId); \
      pCautionsCombo->AddString (lbString); \
      ++iNumCautions; \
   }
//adding new macro to have custom formatted strings to display 
#define ADD_CAUTION_CUSTOM_STRING(containerId, fieldId, string ) \
   getParent()->getField ( \
                          this, \
                          containerId, \
                          fieldId, \
                          str, \
                          false \
                         ); \
   if (str == I_("Y")) \
   { \
      pCautionsCombo->AddString (string); \
      ++iNumCautions; \
   }

   DSTComboBox *pCautionsCombo = 
      dynamic_cast <DSTComboBox*> (GetControl (comboId));

   pCautionsCombo->ResetContent ();
//add the account categories
   pCautionsCombo->FillInListValues ( acctCategoryListContainerId,
                                      ifds::AcctCategory);
   
   int iNumCautions = pCautionsCombo->GetCount();
   CString lbString;
   DString str;

//for DTA
   getParent()->getField ( this,
                           accountContainerId,
                           ifds::DTAType,
                           str,
                           true); //get the description
   if (!str.empty())
   {
      lbString = str.c_str ();
      pCautionsCombo->AddString (lbString);
      ++iNumCautions;
   }

	//NetworkID

	DString dstrNetworkID;
   getParent()->getField ( this,
                           accountContainerId,
                           ifds::NetworkID,
                           dstrNetworkID,
                           true); //get the NetWorkID
   if (!dstrNetworkID.empty())
   {
      lbString = dstrNetworkID.c_str ();
      pCautionsCombo->AddString (lbString);
      ++iNumCautions;
   }

//start adding the account cautions
   ADD_CAUTION ( accountContainerId, 
                 ifds::PendingTrade, 
                 ROW_DETAILS_CAUTIONS_PENDING_TRADE);
   ADD_CAUTION ( shareholderContainerId,
                 ifds::Remarks, 
                 ROW_DETAILS_CAUTIONS_REMARKS);
   ADD_CAUTION ( accountContainerId, 
                 ifds::Certificates, 
                 ROW_DETAILS_CAUTIONS_CERTIFICATES_ISSUED);
   ADD_CAUTION ( accountContainerId, 
                 ifds::StopPurchase, 
                 ROW_DETAILS_CAUTIONS_STOP_PURCHASE);
   ADD_CAUTION ( accountContainerId, 
                 ifds::StopRed, 
                 ROW_DETAILS_CAUTIONS_STOP_REDEEM);
   ADD_CAUTION ( accountContainerId, 
                 ifds::StopRedSettle, 
                 IDS_STOP_REDEEMPTION_SETTLE);
   ADD_CAUTION ( accountContainerId, 
                 ifds::StopXferOut, 
                 ROW_DETAILS_CAUTIONS_STOP_TRANS_OUT);
   ADD_CAUTION ( accountContainerId, 
                 ifds::StopXferIn, 
                 ROW_DETAILS_CAUTIONS_STOP_TRANS_IN);
   ADD_CAUTION ( accountContainerId, 
                 ifds::UnsettledTrn, 
                 ROW_DETAILS_CAUTIONS_UNSETTLED_TRANSACTION);
   
   ADD_CAUTION_CUSTOM_STRING ( accountContainerId, 
                               ifds::HighestEntityRisk, 
                               getCustomString( accountContainerId,ifds::HighestEntityRisk) );

   ADD_CAUTION ( accountContainerId, 
                 ifds::ExistAssignee, 
                 ROW_DETAILS_CAUTIONS_EXIST_ASSIGNEE);
   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      ADD_CAUTION ( accountContainerId, 
                    ifds::ApplyPST, 
                    IDS_PST_EXEMPT);
      ADD_CAUTION ( accountContainerId, 
                    ifds::GSTExempt, 
                    IDS_GST_EXEMPT);
   }
//set the selection on first item   
   pCautionsCombo->SetCurSel (0);
//set the cautions label
   CString strCautionsLabel,
      strFormat (" (%d):"),
      strNumCautions;

   strCautionsLabel.LoadString (TXT_CAUTIONS_LABEL);
   strNumCautions.Format (strFormat, iNumCautions);
   strCautionsLabel += strNumCautions;
   GetDlgItem (comboLabelId)->SetWindowText (strCautionsLabel);
}

//******************************************************************************
void TradesDlg::updateRepInfoPage ()
{
//register controls with the broker/branch/sls rep info page
//these controls should be shown all the time
   if (!m_bRepInfoPageRegistered)
   {
      m_pInfoTabCtrl->registerControl (IDC_STC_BROKER, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_EDT_BROKER_CODE, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_STC_BROKER_NAME, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_STC_BRANCH, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_EDT_BRANCH_CODE, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_STC_BRANCH_NAME, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_STC_SALES_REP, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_EDT_SALES_REP_CODE, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_STC_SALES_REP_NAME, TXT_TAB_TITLE_REP_INFO);
      m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_REP_INFO);
      m_bRepInfoPageRegistered = true;
   }
}

//******************************************************************************
void TradesDlg::updateRemarksPage ()
{
//register controls with the remarks page
//these controls should be shown all the time
   if (!m_bRemarksPageRegistered)
   {
      m_pInfoTabCtrl->registerControl (IDC_EDT_REMARKS, TXT_TAB_TITLE_REMARKS);
      m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_REMARKS);
      m_bRemarksPageRegistered = true;
   }
}

//******************************************************************************
bool TradesDlg::updateBankingPage ()
{
   DString isBankingNeeded;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsBankingNeeded,
                            isBankingNeeded,
                            false);
   
   ConnectControlsToData (TRADE_CONTROLS::BANK, isBankingNeeded == I_("Y"));
   if (isBankingNeeded == I_("Y")) //add the banking tab page and controls
   {
      if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_BANKING))
      {
//add banking page
         m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_BANKING, 1);
//register controls with the banking page
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_NAME_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_NAME, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ID_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ID, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ACCT_NAME_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ACCT_NAME, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ACCT_NBR_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_STC_BANK_ACCT_NBR, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_BANKING);
      }
      LoadControls (TRADE_CONTROLS::BANK);
   }
   else //remove the banking tab page and controls
   {
//remove controls from the banking page
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_BANKING))
      {
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_NAME_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_NAME, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ID_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ID, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ACCT_NAME_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ACCT_NAME, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ACCT_NBR_LABEL, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_BANK_ACCT_NBR, TXT_TAB_TITLE_BANKING);
         m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_BANKING);
   //remove banking page
         m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_BANKING);
      }
//also, hide these controls
      GetControl (IDC_STC_BANK_NAME_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_NAME)->Show (false);
      GetControl (IDC_STC_BANK_ID_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ID)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NAME_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NAME)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NBR_LABEL)->Show (false);
      GetControl (IDC_STC_BANK_ACCT_NBR)->Show (false);
   }
   return isBankingNeeded == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateShareholderAddressPage ()
{
   DString isShareholderAddressNeeded;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsShareholderAddressNeeded,
                            isShareholderAddressNeeded,
                            false);
   ConnectControlsToData (TRADE_CONTROLS::SHAREHOLDER_ADDRESS, isShareholderAddressNeeded == I_("Y"));
   if (isShareholderAddressNeeded == I_("Y"))
   {
//add address page
      if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_ADDRESS))
      {
         m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_ADDRESS, 1);
   //register controls with the address page
         m_pInfoTabCtrl->registerControl (IDC_STC_SHAREHOLDER_ADDR_CODE, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->registerControl (IDC_EDT_SHAREHOLDER_ADDR_CODE, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->registerControl (IDC_EDT_SHAREHOLDER_ADDR, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_ADDRESS);
      }
      LoadControls (TRADE_CONTROLS::SHAREHOLDER_ADDRESS);
   }
   else 
   {
//remove controls with the address page
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_ADDRESS))
      {
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SHAREHOLDER_ADDR_CODE, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->removeControlFromPage (IDC_EDT_SHAREHOLDER_ADDR_CODE, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->removeControlFromPage (IDC_EDT_SHAREHOLDER_ADDR, TXT_TAB_TITLE_ADDRESS);
         m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_ADDRESS);
   //remove address page
         m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_ADDRESS);
      }
//also, hide these controls
      GetControl (IDC_STC_SHAREHOLDER_ADDR_CODE)->Show (false);
      GetControl (IDC_EDT_SHAREHOLDER_ADDR_CODE)->Show (false);
      GetControl (IDC_EDT_SHAREHOLDER_ADDR)->Show (false);
   }
   return isShareholderAddressNeeded == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateSettleLocPage ()
{
   DString isSettleLocAllowed, isClearingAccountFrom,
            isClearingAccountTo;
   
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               IsSettleLocAllowed,
                               isSettleLocAllowed,
                               false);
      getParent ()->getField ( this,
                               ACCOUNT,
                               IsClearingAccount,
                               isClearingAccountFrom,
                               false);
      getParent ()->getField ( this,
                               ACCOUNT_TO,
                               IsClearingAccount,
                               isClearingAccountTo,
                               false);
      if (isSettleLocAllowed == I_("Y"))
      {
         int iTabPos = 1;//after rep info page, always
		   
         if (isClearingAccountFrom == I_("Y"))
         {
			   if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_SETTL_LOC))
			   {
				   m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_SETTL_LOC, iTabPos); 
		   //register controls with settle location page
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_LOCATION_LABEL, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_LOCATION, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_CLEARING_METHOD_LABEL, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_CLEARING_METHOD, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_DELIVERY_TO_LABEL, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_DELIVERY_2, TXT_TAB_TITLE_SETTL_LOC);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE, TXT_TAB_TITLE_SETTL_LOC);
		   //register details button with the settle location page
				   m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_SETTL_LOC);
				   ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION, true);
			   }
            LoadControls (TRADE_CONTROLS::SETTLE_LOCATION);
		 }
		 else
		 {
			 removeTabPage(  TXT_TAB_TITLE_SETTL_LOC );
		 }
         
		 //make sure that we don't show 'TO' tab for exchanges
		   DString dstrTransType;
         
         getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, dstrTransType, false);
         if (isClearingAccountTo == I_("Y"))
         {		    
			   if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_SETTL_LOC_TO) &&
				     dstrTransType != I_("EI") &&
				     dstrTransType != I_("EO") &&
				     dstrTransType != I_("XR") )
			   {
				   int iTabPos = 1;
               
               if( m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_SETTL_LOC) )
				   {
					   iTabPos++;
				   }
				   m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_SETTL_LOC_TO, iTabPos); //after rep info page, always
		   //register controls with settle location page
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_LOCATION_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_LOCATION_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_CLEARING_METHOD_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_CLEARING_METHOD_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_DELIVERY_TO_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_DELIVERY_2_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
				   m_pInfoTabCtrl->registerControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
		   //register details button with the settle location page
				   m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_SETTL_LOC_TO);
				   ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION_TO, true);
			   }
               LoadControls (TRADE_CONTROLS::SETTLE_LOCATION_TO);
         }
         else
         {
            removeTabPage(  TXT_TAB_TITLE_SETTL_LOC_TO );
         }
      }
      else 
      {
         removeTabPage(  TXT_TAB_TITLE_SETTL_LOC );
         removeTabPage(  TXT_TAB_TITLE_SETTL_LOC_TO );
      }
   }
   return isSettleLocAllowed == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateMultipleSettleLocPage ()
{
	DString areMultipleSettleLocAllowed;

	getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, AreMultipleSettleLocAllowed, areMultipleSettleLocAllowed, false); 
	
	bool bAllowed = areMultipleSettleLocAllowed ==  I_("Y");


	if (m_strMarket != MARKET_IDS::LUXEMBOURG)
		return bAllowed;

	if (bAllowed)
    {	
		if (!m_pInfoTabCtrl->HasTab (TXT_TAB_MULTIPLE_SETTLE_LOCS))                         
		{
			m_pInfoTabCtrl->AddTab (TXT_TAB_MULTIPLE_SETTLE_LOCS); 
		
			m_pInfoTabCtrl->registerListControl (IDC_LV_MULTIPLE_SETTL_LOCS, TXT_TAB_MULTIPLE_SETTLE_LOCS);		
			m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_MULTIPLE_SETTLE_LOCS);

			ConnectListToData (IDC_LV_MULTIPLE_SETTL_LOCS, true);
		}

		if (!m_bMultipleSettleLocSelectionInProgress)
		{
			LoadListControl (IDC_LV_MULTIPLE_SETTL_LOCS);
		}
	}
	else
	{
		if (m_pInfoTabCtrl->HasTab (TXT_TAB_MULTIPLE_SETTLE_LOCS))
		{
			m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_MULTIPLE_SETTL_LOCS, TXT_TAB_MULTIPLE_SETTLE_LOCS);
			m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_MULTIPLE_SETTLE_LOCS);	
			m_pInfoTabCtrl->RemoveTab (TXT_TAB_MULTIPLE_SETTLE_LOCS);
			
			ConnectListToData (IDC_LV_MULTIPLE_SETTL_LOCS, false);
			
			GetList (IDC_LV_MULTIPLE_SETTL_LOCS)->Show (false);
		}      
	}

	return bAllowed;
}

//******************************************************************************
bool TradesDlg::updateBeneficiaryAllocationPage ()
{

	DString areRESPBenefAllocationsAllowed;

	getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, AreRESPBenefAllocationsAllowed, areRESPBenefAllocationsAllowed, false);
	
	if (m_strMarket != MARKET_IDS::CANADA)
		return false;

	if (areRESPBenefAllocationsAllowed == I_("Y"))
    {	
		if (!m_pInfoTabCtrl->HasTab (TXT_TAB_BENEFICIARY_ALLOCS))                         
		{
			m_pInfoTabCtrl->AddTab (TXT_TAB_BENEFICIARY_ALLOCS, m_pInfoTabCtrl->GetItemCount () - 1); //before Remarks
		
			m_pInfoTabCtrl->registerListControl (IDC_LV_BENEFICARY_ALLOCATION, TXT_TAB_BENEFICIARY_ALLOCS);		
			m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_BENEFICIARY_ALLOCS);

			ConnectListToData (IDC_LV_BENEFICARY_ALLOCATION, true);
		}

		if (!m_bRESPBenefAllocationInProgress)
		{
			LoadListControl (IDC_LV_BENEFICARY_ALLOCATION);
		}
	}
	else
	{
		if (m_pInfoTabCtrl->HasTab (TXT_TAB_BENEFICIARY_ALLOCS))
		{
			m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_BENEFICARY_ALLOCATION, TXT_TAB_BENEFICIARY_ALLOCS);
			m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_BENEFICIARY_ALLOCS);	
			m_pInfoTabCtrl->RemoveTab (TXT_TAB_BENEFICIARY_ALLOCS);
			
			ConnectListToData (IDC_LV_BENEFICARY_ALLOCATION, false);
			
			GetList (IDC_LV_BENEFICARY_ALLOCATION)->Show (false);
		}      
	}

	return areRESPBenefAllocationsAllowed == I_("Y");
}

//******************************************************************************
bool TradesDlg::updatePSEEAPPage ()
{
	DString isPSEEAPAllowed;

	getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, IsPSEEAPAllowed, isPSEEAPAllowed, false);
	
	if (m_strMarket != MARKET_IDS::CANADA)
		return false;

   ConnectControlsToData (TRADE_CONTROLS::PSE_EAP, isPSEEAPAllowed == I_("Y"));
	if (isPSEEAPAllowed == I_("Y"))
   {	
		if (!m_pInfoTabCtrl->HasTab (TXT_TAB_PSE_EAP))                         
		{
			m_pInfoTabCtrl->AddTab (TXT_TAB_PSE_EAP, m_pInfoTabCtrl->GetItemCount () - 1); //before Remarks
         m_pInfoTabCtrl->registerControl (IDC_STC_PSE_TYPE, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->registerControl (IDC_STC_PSETYPE, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->registerControl (IDC_STC_PSE_LENGTH, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->registerControl (IDC_STC_PSELENGTH, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->registerControl (IDC_STC_PSE_YEAR, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->registerControl (IDC_STC_PSEYEAR, TXT_TAB_PSE_EAP);
//details button		
			m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_PSE_EAP);
		}
      LoadControls (TRADE_CONTROLS::PSE_EAP);
	}
	else
	{
		if (m_pInfoTabCtrl->HasTab (TXT_TAB_PSE_EAP))
		{
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSE_TYPE, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSETYPE, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSE_LENGTH, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSELENGTH, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSE_YEAR, TXT_TAB_PSE_EAP);
         m_pInfoTabCtrl->removeControlFromPage (IDC_STC_PSEYEAR, TXT_TAB_PSE_EAP);
			m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_PSE_EAP);
			m_pInfoTabCtrl->RemoveTab (TXT_TAB_PSE_EAP);
		}
//also, hide these controls
      GetControl (IDC_STC_PSE_TYPE)->Show (false);
      GetControl (IDC_STC_PSETYPE)->Show (false);
      GetControl (IDC_STC_PSE_LENGTH)->Show (false);
      GetControl (IDC_STC_PSELENGTH)->Show (false);
      GetControl (IDC_STC_PSE_YEAR)->Show (false);
      GetControl (IDC_STC_PSEYEAR)->Show (false);
	}
	return isPSEEAPAllowed == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateRESPTransferPage ()
{

	DString isRESPTransferAllowed;

	getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, IsRESPTransferAllowed, isRESPTransferAllowed, false);
	
	if (m_strMarket != MARKET_IDS::CANADA)
		return false;

	if (isRESPTransferAllowed == I_("Y"))
    {	
		if (!m_pInfoTabCtrl->HasTab (TXT_TAB_RESP_TRANSFERS))                         
		{
			m_pInfoTabCtrl->AddTab (TXT_TAB_RESP_TRANSFERS, m_pInfoTabCtrl->GetItemCount () - 1); //before Remarks
		
			m_pInfoTabCtrl->registerListControl (IDC_LV_ACCT_BENEF, TXT_TAB_RESP_TRANSFERS);
			m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_RESP_TRANSFERS);

			ConnectListToData (IDC_LV_ACCT_BENEF, true);
		}

		if (!m_bRESPTransfersInProgress)
		{
			LoadListControl (IDC_LV_ACCT_BENEF);
		}
	}
	else
	{
		if (m_pInfoTabCtrl->HasTab (TXT_TAB_RESP_TRANSFERS))
		{
			m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_ACCT_BENEF, TXT_TAB_RESP_TRANSFERS);
			m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_RESP_TRANSFERS);	
			m_pInfoTabCtrl->RemoveTab (TXT_TAB_RESP_TRANSFERS);
			
			ConnectListToData (IDC_LV_ACCT_BENEF, false);
			
			GetList (IDC_LV_ACCT_BENEF)->Show (false);
		}      
	}

	return isRESPTransferAllowed == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateRDSPTransferPage ()
{

	DString isRDSPTransferAllowed;

	getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, IsRDSPTransferAllowed, isRDSPTransferAllowed, false);

	if (m_strMarket != MARKET_IDS::CANADA)
		return false;

	if (isRDSPTransferAllowed == I_("Y"))
	{	
		if (!m_pInfoTabCtrl->HasTab (TXT_TAB_RDSP_TRANSFERS))                         
		{
			m_pInfoTabCtrl->AddTab (TXT_TAB_RDSP_TRANSFERS, m_pInfoTabCtrl->GetItemCount () - 1); //before Remarks					
			m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_RDSP_TRANSFERS);			
		}

	}
	else
	{
		if (m_pInfoTabCtrl->HasTab (TXT_TAB_RDSP_TRANSFERS))
		{			
			m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_RDSP_TRANSFERS);	
			m_pInfoTabCtrl->RemoveTab (TXT_TAB_RDSP_TRANSFERS);						
		}      
	}

	return isRDSPTransferAllowed == I_("Y");
}


//******************************************************************************
void TradesDlg::removeTabPage( UINT iPageName )
{
   if( !m_pInfoTabCtrl )
   {
      return;
   }

   //remove controls registered with the page
   if( iPageName == TXT_TAB_TITLE_SETTL_LOC )
   {
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_SETTL_LOC))
         {
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_LOCATION_LABEL, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_LOCATION, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_CLEARING_METHOD_LABEL, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_CLEARING_METHOD, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_INSTRUCTIONS_CODE, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_DELIVERY_TO_LABEL, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_DELIVERY_2, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_SETTL_LOC);
            m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_SETTL_LOC);
            //also, hide the controls
            GetControl (IDC_STC_SETTLE_LOCATION_LABEL)->Show (false);
            GetControl (IDC_STC_SETTLE_LOCATION)->Show (false);
            GetControl (IDC_STC_CLEARING_METHOD_LABEL)->Show (false);
            GetControl (IDC_STC_CLEARING_METHOD)->Show (false);
            GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL)->Show (false);
            GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE)->Show (false);
            GetControl (IDC_STC_DELIVERY_TO_LABEL)->Show (false);
            GetControl (IDC_STC_DELIVERY_2)->Show (false);
            ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION, false);
         }
   }
   else if( iPageName == TXT_TAB_TITLE_SETTL_LOC_TO )
   {
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_SETTL_LOC_TO))
         {
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_LOCATION_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_LOCATION_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_CLEARING_METHOD_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_CLEARING_METHOD_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_DELIVERY_TO_LABEL_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_DELIVERY_2_TO, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_SETTL_LOC_TO);
            m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_SETTL_LOC_TO);
            //also, hide the controls
            GetControl (IDC_STC_SETTLE_LOCATION_LABEL_TO)->Show (false);
            GetControl (IDC_STC_SETTLE_LOCATION_TO)->Show (false);
            GetControl (IDC_STC_CLEARING_METHOD_LABEL_TO)->Show (false);
            GetControl (IDC_STC_CLEARING_METHOD_TO)->Show (false);
            GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_LABEL_TO)->Show (false);
            GetControl (IDC_STC_SETTLE_INSTRUCTIONS_CODE_TO)->Show (false);
            GetControl (IDC_STC_DELIVERY_TO_LABEL_TO)->Show (false);
            GetControl (IDC_STC_DELIVERY_2_TO)->Show (false);
            ConnectControlsToData (TRADE_CONTROLS::SETTLE_LOCATION_TO, false);
         }
   }
}

//******************************************************************************
void TradesDlg::updateInfoTabCtrl (bool bSelectPageRepInfo)
{
   updateRepInfoPage ();
   updateRemarksPage ();
   updateDilutionPage ();
   updatePayInstructPage ();
      
//banking
   bool bBank = updateBankingPage ();

   if (bBank)
   {
      if (!bSelectPageRepInfo)
      {
         m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_BANKING);
      }
   }

//shareholder address
   bool bAddress = updateShareholderAddressPage ();

   if (bAddress)
   {
      if (!bSelectPageRepInfo)
      {
         m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_ADDRESS);
      }
   }
//settle location
   bool bSettleLoc = updateSettleLocPage ();

   if (!bSelectPageRepInfo && bSettleLoc)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_SETTL_LOC) )
      {
         //try account to instead
          m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_SETTL_LOC_TO);
      }
   }

   //multiple settle location
   bool bMultipleSettleLoc = updateMultipleSettleLocPage ();

   if (!bSelectPageRepInfo && bMultipleSettleLoc)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_MULTIPLE_SETTLE_LOCS) )
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_MULTIPLE_SETTLE_LOCS);
      }
   }

   if (bSelectPageRepInfo || (!bBank && !bAddress && !bSettleLoc))
   {
//force the selection, if commanded so...
      if (bSelectPageRepInfo)
      {
         m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_REP_INFO, true);
      }
   }


   bool bBeneficiaryAllocation = updateBeneficiaryAllocationPage ();

   if (!bSelectPageRepInfo && bBeneficiaryAllocation)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_BENEFICIARY_ALLOCS))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_BENEFICIARY_ALLOCS);
      }
   }

   bool bUpdatePSEEAPPage = updatePSEEAPPage  ();

   if (!bSelectPageRepInfo && bUpdatePSEEAPPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_PSE_EAP))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_PSE_EAP);
      }
   }   

   bool bUpdateRESPTransferPage = updateRESPTransferPage ();

   if (!bSelectPageRepInfo && bUpdateRESPTransferPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_RESP_TRANSFERS))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_RESP_TRANSFERS);
      }
   }

   bool bUpdateGIAAttribPage = updateGIAAttribPage ();
   
   if (!bSelectPageRepInfo && bUpdateGIAAttribPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_GIA_ATTRIB))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_GIA_ATTRIB);
      }
   }   

   bool bUpdateGIInvestmentsPage = updateGIInvestmentsPage();
   if (!bSelectPageRepInfo && bUpdateGIInvestmentsPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_GI_INVESTMENTS))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_GI_INVESTMENTS);
      }
   }   


   bool bUpdateMaturityInstrPage = updateMaturityInstrPage ();
   
   if (!bSelectPageRepInfo && bUpdateMaturityInstrPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_MAT_INSTR))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_TITLE_MAT_INSTR);
      }
   }

   bool bUpdateRDSPTransferPage = updateRDSPTransferPage ();

   if (!bSelectPageRepInfo && bUpdateRDSPTransferPage)
   {
      if( !m_pInfoTabCtrl->SelectTab (TXT_TAB_RDSP_TRANSFERS))
      {
          m_pInfoTabCtrl->SelectTab (TXT_TAB_RDSP_TRANSFERS);
      }
   }

}

//******************************************************************************
void TradesDlg::updateFeesPage ()
{
   if (!m_bFeesPageRegistered)
   {
      m_pFeesTabCtrl->registerGridWnd (IDC_GRD_FEES, TXT_TAB_TITLE_FEES);
      m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_FEES);
      m_bFeesPageRegistered = true;
   }
   if ( !m_bTradeListSelectionInProgress &&
        !m_bAllocationListSelectionInProgress &&
        !m_bEstateAllocationListSelectionInProgress &&
        !m_bSplitCommissionListSelectionInProgress)
   {
      //do not force selection on the first row of the grid.
      //in this way the focus is not stolen
      m_pFeesGrdWnd->LoadGrid (false); 
   }
}

//******************************************************************************
bool TradesDlg::updateAllocationsPage ()
{
   DString areAllocationsAllowed,
      isAccountSetAndValid,
      isAccountToSetAndValid;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            AreAllocationsAllowed,
                            areAllocationsAllowed,
                            false);  
   getParent ()->getField ( this,
                            ACCOUNT,
                            IsAccountSetAndValid,
                            isAccountSetAndValid,
                            false);
   getParent ()->getField ( this,
                            ACCOUNT_TO,
                            IsAccountSetAndValid,
                            isAccountToSetAndValid,
                            false);
   bool bAddAllocations = areAllocationsAllowed == I_("Y") &&
        (isAccountSetAndValid == I_("Y") && isOneSideTrade () ||
         isAccountToSetAndValid == I_("Y") && !isOneSideTrade ());

   if (bAddAllocations)
   {
      if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_ALLOCATION))
      {
//add allocations page
         m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_ALLOCATION, 1);
//register controls with the allocations page
         m_pFeesTabCtrl->registerListControl (IDC_LV_ALLOCATIONS, TXT_TAB_TITLE_ALLOCATION);
         m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_ALLOCATION);
      }
      if (!m_bAllocationListSelectionInProgress)
      {
         LoadListControl (IDC_LV_ALLOCATIONS);
      }
   }
   else 
   {
//remove controls with the allocations page
      if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_ALLOCATION))
      {
         m_pFeesTabCtrl->removeListControlFromPage (IDC_LV_ALLOCATIONS, TXT_TAB_TITLE_ALLOCATION);
         m_pFeesTabCtrl->removeControlFromPage (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_ALLOCATION);
   //remove allocations page
         m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_ALLOCATION);
      }
//also, hide the list
      GetList (IDC_LV_ALLOCATIONS)->Show (false);
//if allocations are not allowed, it is possible that the CBO supporting list 
//gets blown-up, so reload the GUI list
      if (GetList (IDC_LV_ALLOCATIONS)->GetItemCount () > 0)
      {
         if ( !m_bAllocationListSelectionInProgress &&
              !m_bTradeListSelectionInProgress)
         {
            LoadListControl (IDC_LV_ALLOCATIONS);
         }
      }
   }
//they usually go hand in hand...
   updateSplitCommissionsPage ();
//update purchase total control...
   LoadControl (IDC_EDT_PURCHASE_TOTAL);
   return bAddAllocations;
}

//******************************************************************************
bool TradesDlg::updateEstateAllocationPage ()
{

   DString isEstateAllocationListApplicable;

   DString tradeType;

   getParent ()->getField ( this, IFASTBP_PROC::TRADES_LIST, IsEstateAllocationListApplicable,
                            isEstateAllocationListApplicable, false);


   bool bEstateAlloc = isEstateAllocationListApplicable == I_("Y");

   if (m_strMarket == MARKET_IDS::CANADA)
   {
      if (bEstateAlloc)
      {
         if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_ESTATE_ALLOC))
         {
            m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_ESTATE_ALLOC, 1);
            m_pFeesTabCtrl->registerListControl (IDC_LV_ESTATE_ALLOCATION, TXT_TAB_TITLE_ESTATE_ALLOC);
            m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_ESTATE_ALLOC);
            ConnectListToData (IDC_LV_ESTATE_ALLOCATION, true);
         }
         if (!m_bEstateAllocationListSelectionInProgress)
         {
            LoadListControl (IDC_LV_ESTATE_ALLOCATION);
         }
      }
      else
      {
         if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_ESTATE_ALLOC))
         {
            m_pFeesTabCtrl->removeListControlFromPage (IDC_LV_ESTATE_ALLOCATION, TXT_TAB_TITLE_ESTATE_ALLOC);
            m_pFeesTabCtrl->removeControlFromPage (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_ESTATE_ALLOC);
   //remove estate allocations page
            m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_ESTATE_ALLOC);
            ConnectListToData (IDC_LV_ESTATE_ALLOCATION, false);
         }

         if (!m_bEstateAllocationListSelectionInProgress)
         {
            LoadListControl (IDC_LV_ESTATE_ALLOCATION);
         }
      }
   }
   return true;
}

//******************************************************************************
bool TradesDlg::updateSplitCommissionsPage ()
{
   DString isSplitCommissionAllowed;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsSplitCommissionAllowed,
                            isSplitCommissionAllowed,
                            false);

   bool bAddSplitCommission = isSplitCommissionAllowed == I_("Y");

   if (bAddSplitCommission)
   {
      if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_SPLIT_COMM))
      {
         //connect the list to data...
         ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, true);

         DString areAllocationsAllowed;

         getParent ()->getField ( this,
                                  IFASTBP_PROC::TRADES_LIST,
                                  AreAllocationsAllowed,
                                  areAllocationsAllowed,
                                  false);
   //add split commissions page
         m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_SPLIT_COMM, areAllocationsAllowed == I_("Y") ? 2 : 1);
   //register controls with the split commissions page
         m_pFeesTabCtrl->registerListControl (IDC_LV_SPLIT_COMMISSIONS, TXT_TAB_TITLE_SPLIT_COMM);
         m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_SPLIT_COMM);
      }
      if (!m_bSplitCommissionListSelectionInProgress)
      {
         LoadListControl (IDC_LV_SPLIT_COMMISSIONS);
      }
   }
   else 
   {   
//remove controls with the splits page
      if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_SPLIT_COMM))
      {
         m_pFeesTabCtrl->removeListControlFromPage (IDC_LV_SPLIT_COMMISSIONS, TXT_TAB_TITLE_SPLIT_COMM);
         m_pFeesTabCtrl->removeControlFromPage (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_SPLIT_COMM);
//remove splits page
         m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_SPLIT_COMM);
         //disconnect the list from data
         ConnectListToData (IDC_LV_SPLIT_COMMISSIONS, false);
//also, hide the list
      }
      GetList (IDC_LV_SPLIT_COMMISSIONS)->Show (false);
   }
   return bAddSplitCommission;
}

//******************************************************************************
bool TradesDlg::updateTaxRatesPage ()
{
   DString areTaxRatesAllowed;

   DSTCWorkSession *pDSTCWorkSession = 
                     dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   
   if (m_strMarket == MARKET_IDS::CANADA)
   {
      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               AreTaxRatesAllowed,
                               areTaxRatesAllowed,
                               false);
      if (areTaxRatesAllowed == I_("Y"))
      {
         if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_TAX_RATE))
         {
      //add tax rates as last page 
            m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_TAX_RATE);
      //register controls with the tax rates page
            m_pFeesTabCtrl->registerControl (IDC_CHK_OVERRIDE_TAX, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_STC_FED_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_EDT_FED_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_CMB_FED_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_STC_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_EDT_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_CMB_PROV_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
      //register details buttom with the tax rates page
            m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_TAX_RATE);
            LoadControls (TRADE_CONTROLS::CHK_TAX_RATES);

            DString overrideTax;

            getParent()->getField ( this, 
                                    IFASTBP_PROC::TRADES_LIST, 
                                    ifds::OverrideTax,
                                    overrideTax, 
                                    false );

            ( (CButton* )GetDlgItem (IDC_CHK_OVERRIDE_TAX))->SetCheck (overrideTax == I_("Y"));

			ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, true);
			LoadControls (TRADE_CONTROLS::TAX_RATES);

            bool bUpdate = hasUpdatePermission (UAF::TRADE_TAX_RATE_OVERRIDE);
			
            GetControl (IDC_CHK_OVERRIDE_TAX)->Enable (bUpdate);
            GetControl (IDC_STC_FED_RATE)->Enable (bUpdate);
            GetControl (IDC_EDT_FED_RATE)->Enable (bUpdate);
            GetControl (IDC_CMB_FED_RATE_TYPE)->Enable (bUpdate);
            GetControl (IDC_STC_PROV_RATE)->Enable (bUpdate);
            GetControl (IDC_EDT_PROV_RATE)->Enable (bUpdate);
            GetControl (IDC_CMB_PROV_RATE_TYPE)->Enable (bUpdate);
         }
      }
      else 
      {
//remove controls with the tax rates page
         if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_TAX_RATE))
         {
            m_pFeesTabCtrl->removeControlFromPage (IDC_CHK_OVERRIDE_TAX, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_STC_FED_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_EDT_FED_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_CMB_FED_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_STC_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_EDT_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_CMB_PROV_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_TAX_RATE);
//also, hide the controls
            GetControl (IDC_CHK_OVERRIDE_TAX)->Show (false);
            GetControl (IDC_STC_FED_RATE)->Show (false);
            GetControl (IDC_EDT_FED_RATE)->Show (false);
            GetControl (IDC_CMB_FED_RATE_TYPE)->Show (false);
            GetControl (IDC_STC_PROV_RATE)->Show (false);
            GetControl (IDC_EDT_PROV_RATE)->Show (false);
            GetControl (IDC_CMB_PROV_RATE_TYPE)->Show (false);
            ConnectControlsToData (TRADE_CONTROLS::TAX_RATES, false);
         }
      }
   }
   else if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               AreTaxRatesAllowed,
                               areTaxRatesAllowed,
                               false);
      if (areTaxRatesAllowed == I_("Y"))
      {
         if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_TAX_RATE))
         {
      //add tax rates as last page 
            m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_TAX_RATE);
      //register controls with the tax rates page
            m_pFeesTabCtrl->registerControl (IDC_CHK_OVERRIDE_TAX, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_STC_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_EDT_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->registerControl (IDC_CMB_PROV_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
      //register details buttom with the tax rates page
            m_pFeesTabCtrl->registerControl (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_TAX_RATE);
            LoadControls (TRADE_CONTROLS::CHK_TAX_RATES);

            DString overrideTax;

            getParent()->getField ( this, 
                                    IFASTBP_PROC::TRADES_LIST, 
                                    ifds::OverrideTax,
                                    overrideTax, 
                                    false);

            ( (CButton* )GetDlgItem (IDC_CHK_OVERRIDE_TAX))->SetCheck (overrideTax == I_("Y"));
            if (overrideTax == I_("Y"))
            {
               ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, true);
               LoadControls (TRADE_CONTROLS::IWT_TAX_RATES);
            }
            else
            {
               ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, false);
            }

            bool bUpdate = hasUpdatePermission (UAF::TRADE_TAX_RATE_OVERRIDE);

            GetControl (IDC_CHK_OVERRIDE_TAX)->Enable (bUpdate);
            GetControl (IDC_STC_PROV_RATE)->Enable (bUpdate);
            if (pDSTCWorkSession->isIWTClient(getDataGroupId()))
            {
               DString dstrAccountNum;
               MFAccount *pMFAccount = NULL;
               getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);
               if( pDSTCWorkSession->getMFAccount (getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING &&
                   pMFAccount )
               {
                 if ( !pMFAccount->isIWTNonTaxable(getDataGroupId()) )
                  {
                     if (overrideTax == I_("Y"))
                     {
                        GetDlgItem (IDC_EDT_PROV_RATE)->EnableWindow (false);
                        GetDlgItem (IDC_CMB_PROV_RATE_TYPE)->EnableWindow (false);
                     }
                  }
               }
            } // isIWTClient

         }
      }
      else 
      {
//remove controls with the tax rates page
         if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_TAX_RATE))
         {
            m_pFeesTabCtrl->removeControlFromPage (IDC_CHK_OVERRIDE_TAX, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_STC_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_EDT_PROV_RATE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_CMB_PROV_RATE_TYPE, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->removeControlFromPage (IDC_BTN_TAB_FEES_DETAILS, TXT_TAB_TITLE_TAX_RATE);
            m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_TAX_RATE);
//also, hide the controls
            GetControl (IDC_CHK_OVERRIDE_TAX)->Show (false);
            GetControl (IDC_STC_PROV_RATE)->Show (false);
            GetControl (IDC_EDT_PROV_RATE)->Show (false);
            GetControl (IDC_CMB_PROV_RATE_TYPE)->Show (false);
            ConnectControlsToData (TRADE_CONTROLS::IWT_TAX_RATES, false);
         }
      }
   }

   return areTaxRatesAllowed == I_("Y");
}

//******************************************************************************
bool TradesDlg::updateGIAAttribPage ()
{
   DString isGIAAttribAllowed;

   DString tradeType;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsGIAAttribAllowed,
                            isGIAAttribAllowed,
                            false);
   getParent ()->getField(	this,
                        IFASTBP_PROC::TRADES_LIST,
                        ifds::TradesTransType,
                        tradeType,
                        false);


   bool bGIAAttrib = isGIAAttribAllowed == I_("Y");

   if (m_strMarket == MARKET_IDS::CANADA)
   {
      ConnectControlsToData (TRADE_CONTROLS::GIA_ATTRIB, isGIAAttribAllowed == I_("Y"));      
      if (bGIAAttrib)
      {
         if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_GIA_ATTRIB))
         {
//add GIA Attrib before remarks page (second to the last page)
			   m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_GIA_ATTRIB, m_pInfoTabCtrl->GetItemCount () - 1); // before remarks
//register controls on GIA Attrib page
            m_pInfoTabCtrl->registerControl (IDC_STC_TYPE_OF_INVESTMENT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_CMB_TYPE_OF_INVESTMENT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_STC_TYPE_OF_INT_CALC, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_CMB_TYPE_OF_INT_CALC, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_STC_TERM_OF_DEPOSIT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_CMB_TERM_OF_DEPOSIT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_STC_INT_FREQ, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->registerControl (IDC_CMB_INT_FREQ_TRADE, TXT_TAB_TITLE_GIA_ATTRIB);
//register the 'details' button
            m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_GIA_ATTRIB);
         }
         LoadControls (TRADE_CONTROLS::GIA_ATTRIB);
      }
      else 
      {   
//remove controls on the GIA Atrib page
         if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_GIA_ATTRIB))
         {
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_TYPE_OF_INVESTMENT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_CMB_TYPE_OF_INVESTMENT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_TYPE_OF_INT_CALC, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_CMB_TYPE_OF_INT_CALC, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_TERM_OF_DEPOSIT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_CMB_TERM_OF_DEPOSIT, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_STC_INT_FREQ, TXT_TAB_TITLE_GIA_ATTRIB);
            m_pInfoTabCtrl->removeControlFromPage (IDC_CMB_INT_FREQ_TRADE, TXT_TAB_TITLE_GIA_ATTRIB);
//remove the details button
            m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_GIA_ATTRIB);
//remove GIA attrib page
            m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_GIA_ATTRIB);
            GetControl (IDC_STC_TYPE_OF_INVESTMENT)->Show (false);
            GetControl (IDC_CMB_TYPE_OF_INVESTMENT)->Show (false);
            GetControl (IDC_STC_TYPE_OF_INT_CALC)->Show (false);
            GetControl (IDC_CMB_TYPE_OF_INT_CALC)->Show (false);
            GetControl (IDC_STC_TERM_OF_DEPOSIT)->Show (false);
            GetControl (IDC_CMB_TERM_OF_DEPOSIT)->Show (false);
            GetControl (IDC_STC_INT_FREQ)->Show (false);
            GetControl (IDC_CMB_INT_FREQ_TRADE)->Show (false);
         }
      }
   }
   return bGIAAttrib;
}

//******************************************************************************
bool TradesDlg::updateGIInvestmentsPage()
{
   DString isGIInvestmentListApplicable;

   DString tradeType;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsGIInvestmentListApplicable,
                            isGIInvestmentListApplicable,
                            false);
   getParent ()->getField(	this,
                        IFASTBP_PROC::TRADES_LIST,
                        ifds::TradesTransType,
                        tradeType,
                        false);


   bool bGIAAttrib = isGIInvestmentListApplicable == I_("Y");

   if (m_strMarket == MARKET_IDS::CANADA)
   {
//      ConnectControlsToData (TRADE_CONTROLS::GIA_ATTRIB, isGIAAttribAllowed == I_("Y"));      
      if (bGIAAttrib)
      {
         if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_GI_INVESTMENTS))
         {
            //connect the list to data...
            ConnectListToData (IDC_LV_INVESTMENT_DETAILS, true);
//add GIA Attrib before remarks page (second to the last page)
			   m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_GI_INVESTMENTS, m_pInfoTabCtrl->GetItemCount () - 1); // before remarks
//register controls on GI Invest page
            m_pInfoTabCtrl->registerListControl (IDC_LV_INVESTMENT_DETAILS, TXT_TAB_TITLE_GI_INVESTMENTS);
//register the 'details' button
            m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_GI_INVESTMENTS);
         }

         if (!m_bInvestmentDetailsListSelectionInProgress)
         {
            LoadListControl (IDC_LV_INVESTMENT_DETAILS);
         }
      }
      else 
      {   
//remove controls on the GIA Atrib page
         if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_GI_INVESTMENTS))
         {
            m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_INVESTMENT_DETAILS, TXT_TAB_TITLE_GI_INVESTMENTS);
//remove the details button
            m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_GI_INVESTMENTS);
//remove GI Investpage
            m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_GI_INVESTMENTS);
            //disconnect the list from data
            ConnectListToData (IDC_LV_INVESTMENT_DETAILS, false);
			   //also, hide the list
			   GetList (IDC_LV_INVESTMENT_DETAILS)->Show (false);

         }
      }
   }
   return bGIAAttrib;
}

//******************************************************************************
bool TradesDlg::updateMaturityInstrPage ()
{
   DString isMaturityInstrAllowed;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsMaturityInstrAllowed,
                            isMaturityInstrAllowed,
                            false);

   bool bMaturityInstr = isMaturityInstrAllowed == I_("Y");

   if (m_strMarket == MARKET_IDS::CANADA)
   {
      if (bMaturityInstr)
      {
         if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_MAT_INSTR))
         {
            //connect the list to data...
            ConnectListToData (IDC_LV_MAT_INSTR, true);

			   //add GIA Attrib before remarks page (second to the last page)
			   m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_MAT_INSTR, m_pInfoTabCtrl->GetItemCount () - 1); // before remarks
			   //register controls on GIA Attrib page
            m_pInfoTabCtrl->registerListControl (IDC_LV_MAT_INSTR, TXT_TAB_TITLE_MAT_INSTR);
            m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_MAT_INSTR);
         }
         if (!m_bMaturityInstrSelectionInProgress)
         {
            LoadListControl (IDC_LV_MAT_INSTR);
         }
      }
      else 
      {   
		   //remove controls on dilution page
         if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_MAT_INSTR))
         {
            m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_MAT_INSTR, TXT_TAB_TITLE_MAT_INSTR);
            m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_MAT_INSTR);
			   //remove dilution page
            m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_MAT_INSTR);
            //disconnect the list from data
            ConnectListToData (IDC_LV_MAT_INSTR, false);
			   //also, hide the list
			   GetList (IDC_LV_MAT_INSTR)->Show (false);
         }      
      }
   }
   return bMaturityInstr;
}

//******************************************************************************
void TradesDlg::updateFeesTabCtrl (bool bSelectPageFees)
{
   updateFeesPage ();
   updateAllocationsPage (); //split commission are updated in here
   updateTaxRatesPage ();
   updateEstateAllocationPage(); 
   if (bSelectPageFees)
   {
//force the selection
      m_pFeesTabCtrl->SelectTab (TXT_TAB_TITLE_FEES, true);
   }
   updateSavingsDirectivePage();
   updateG1G2Page();
}

//******************************************************************************
void TradesDlg::makeFreshDlg ()
{
   updateInfoTabCtrl (true);
   updateFeesTabCtrl (true);
   // Need to set tabs display error state correctly
   m_pInfoTabCtrl-> RefreshAllIcons ();
   m_pFeesTabCtrl-> RefreshAllIcons ();
}

//******************************************************************************
void TradesDlg::updateNetworkIDExternalTransNum()
{
   // AWD; set Network ID and External Transaction Number
   DSTCAWDSession *pDSTCAWDSession = dynamic_cast<DSTCAWDSession* > (getSession());
   
   if ( (pDSTCAWDSession && pDSTCAWDSession->isAWDWorking()) || 
        (((CDSTCView*)GetMainView())->HasWorkEvent()) )
   {
      AbstractProcess *pParentProcess = dynamic_cast <AbstractProcess*> (getParentProcess ());
      DString isRebook,isRefund;

      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               IsRebook,
                               isRebook,
                               false);
	  getParent ()->getField ( this,  
                               IFASTBP_PROC::TRADES_LIST,
                               IsRefund,
                               isRefund,
                               false);

      if ( pParentProcess && 
          (pParentProcess->isCurrentListItemNew (this, IFASTBP_PROC::TRADES_LIST) || isRebook == I_("Y") || isRefund == I_("Y")))
      {
         DString dstrObjectId, 
            dstrTransNum;

         // Set NetWork ID to 'AWD'
         getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::NetworkID, I_("AWD"), false);
         // Get AWD Object ID
         if (pDSTCAWDSession && pDSTCAWDSession->isAWDWorking()) 
         {
            pDSTCAWDSession->getAwdField (I_("ObjectID"), dstrObjectId);
         } 
         else 
         {
            dstrObjectId = ((CDSTCView*)GetMainView())->getWorkEventField(I_("AWDContentId"));
//            getGlobal( WORK_GLOBAL, ifds::AWDObjectId, dstrObjectId );
//            dstrObjectId = m_ObjectId;
         }
         // Get Transaction Number
         getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TransNum, dstrTransNum, false);
         
         // Store in ExtTransNum
         DString dstrExtTransNum = dstrObjectId + I_("-") + dstrTransNum;
         
         getParent()->setField (this, IFASTBP_PROC::TRADES_LIST, ifds::ExtTransNum, dstrExtTransNum, false);
      }
   }
}

//******************************************************************************
bool TradesDlg::updateDilutionPage ()
{
   DString isDilutionAllowed;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            IsDilutionAllowed,
                            isDilutionAllowed,
                            false);

   bool bAddDilution = isDilutionAllowed == I_("Y");

   if (bAddDilution)
   {
      if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_DILUTION))
      {
         //connect the list to data...
         ConnectListToData (IDC_LV_DILUTIONS, true);

			//add dilution page before remarks page (second to the last page )			
			m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_DILUTION, m_pInfoTabCtrl->GetItemCount () - 1); // before remarks
			//register controls on dilution page
         m_pInfoTabCtrl->registerListControl (IDC_LV_DILUTIONS, TXT_TAB_TITLE_DILUTION);
         m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_DILUTION);
      }
      if (!m_bDilutionListSelectionInProgress)
      {
         LoadListControl (IDC_LV_DILUTIONS);
      }
   }
   else 
   {   
		//remove controls on dilution page
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_DILUTION))
      {
         m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_DILUTIONS, TXT_TAB_TITLE_DILUTION);
         m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_DILUTION);
			//remove dilution page
         m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_DILUTION);
         //disconnect the list from data
         ConnectListToData (IDC_LV_DILUTIONS, false);
			//also, hide the list
			GetList (IDC_LV_DILUTIONS)->Show (false);
      }      
   }
   return bAddDilution;
}

//******************************************************************************
bool TradesDlg::updateSavingsDirectivePage ()
{
   DString isEUSDApplicable, transType;
   
   if (m_strMarket == MARKET_IDS::LUXEMBOURG)
   {
      getParent ()->getField ( this,
                               IFASTBP_PROC::TRADES_LIST,
                               IsEUSDApplicable,
                               isEUSDApplicable,
                               false);

		getParent ()->getField(	this,
                              IFASTBP_PROC::TRADES_LIST,
                              ifds::TradesTransType,
                              transType,
                              false);

		if (isEUSDApplicable == I_("Y") )
      {
         if (!m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_EUSD))
         {
      //add tax rates as last page 
            m_pFeesTabCtrl->AddTab (TXT_TAB_TITLE_EUSD);
      //register controls with the tax rates page
            m_pFeesTabCtrl->registerControl (IDC_CHK_OVERRIDE_TIS, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->registerControl (IDC_EDT_TIS, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->registerControl (IDC_CHK_OVERRIDE_COST, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->registerControl (IDC_EDT_COST, TXT_TAB_TITLE_EUSD);
			}

			LoadControls (TRADE_CONTROLS::EUSD);

         DString overrideTIS, overrideCost;

         getParent()->getField ( this, 
                                 IFASTBP_PROC::TRADES_LIST, 
                                 ifds::OverrideTIS,
                                 overrideTIS, 
                                 false);

         ( (CButton* )GetDlgItem (IDC_CHK_OVERRIDE_TIS))->SetCheck (overrideTIS == I_("Y"));

			getParent()->getField ( this, 
                                 IFASTBP_PROC::TRADES_LIST, 
                                 ifds::OverrideCost,
                                 overrideCost, 
                                 false);

         ( (CButton* )GetDlgItem (IDC_CHK_OVERRIDE_COST))->SetCheck (overrideCost == I_("Y"));

					
			DString isInScope, 
				isLookedThru;

			getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, IsFundInScope, isInScope, false);
			getParent ()->getField (this, IFASTBP_PROC::TRADES_LIST, IsFundLookedThru, isLookedThru, false);

			bool bUpdateTIS = hasUpdatePermission (UAF::SAVINGS_DIRECTIVE) && isLookedThru == I_("Y");
			bool bUpdateCost = hasUpdatePermission (UAF::SAVINGS_DIRECTIVE) && isInScope == I_("Y");

			GetControl (IDC_CHK_OVERRIDE_TIS)->Enable (bUpdateTIS);
			GetControl (IDC_EDT_TIS)->Enable (bUpdateTIS);
			GetControl (IDC_CHK_OVERRIDE_COST)->Enable (bUpdateCost);
			GetControl (IDC_EDT_COST)->Enable (bUpdateCost);
      }
      else 
      {
//remove controls 
         if (m_pFeesTabCtrl->HasTab (TXT_TAB_TITLE_EUSD))
         {
            m_pFeesTabCtrl->removeControlFromPage (IDC_CHK_OVERRIDE_TIS, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->removeControlFromPage (IDC_EDT_TIS, TXT_TAB_TITLE_EUSD);
				m_pFeesTabCtrl->removeControlFromPage (IDC_CHK_OVERRIDE_COST, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->removeControlFromPage (IDC_EDT_COST, TXT_TAB_TITLE_EUSD);
            m_pFeesTabCtrl->RemoveTab (TXT_TAB_TITLE_EUSD);
//also, hide the controls
            GetControl (IDC_CHK_OVERRIDE_TIS)->Show (false);
            GetControl (IDC_EDT_TIS)->Show (false);
            GetControl (IDC_CHK_OVERRIDE_COST)->Show (false);
            GetControl (IDC_EDT_COST)->Show (false);
            ConnectControlsToData (TRADE_CONTROLS::EUSD, false);
         }
      }
   }
   return isEUSDApplicable == I_("Y");
}

//****************************************************************************** 
void TradesDlg::OnChkOverrideTIS()
{
   CWaitCursor wait;

   if (((CButton *) GetDlgItem (IDC_CHK_OVERRIDE_TIS))->GetCheck() != 1)
	{		
		getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideTIS, 
                              I_("N"), 
                              false);
	}
	else
	{
		getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideTIS, 
                              I_("Y"), 
                              false);
	}
}

//****************************************************************************** 
void TradesDlg::OnChkOverrideCost()
{
   CWaitCursor wait;

   if (((CButton *) GetDlgItem (IDC_CHK_OVERRIDE_COST))->GetCheck() != 1)
	{		
		getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideCost, 
                              I_("N"), 
                              false);
	}
	else
	{
		getParent()->setField ( this, 
                              IFASTBP_PROC::TRADES_LIST, 
                              ifds::OverrideCost, 
                              I_("Y"), 
                              false);

	}
}

//******************************************************************************
bool TradesDlg::updatePayInstructPage ()
{
   DString arePayInstructAllowed;

   getParent ()->getField ( this,
                            IFASTBP_PROC::TRADES_LIST,
                            ArePayInstructAllowed,
                            arePayInstructAllowed,
                            false);

   bool bArePayInstructAllowed = arePayInstructAllowed == I_("Y");

   if (bArePayInstructAllowed)
   {
      if (!m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_PAY_INSTRUCT))
      {
         //connect the list to data...
         ConnectListToData (IDC_LV_PAY_INSTRUCT, true);

			//add dilution page before remarks page (second to the last page )			
			m_pInfoTabCtrl->AddTab (TXT_TAB_TITLE_PAY_INSTRUCT, m_pInfoTabCtrl->GetItemCount () - 1); // before remarks
			//register controls on dilution page
         m_pInfoTabCtrl->registerListControl (IDC_LV_PAY_INSTRUCT, TXT_TAB_TITLE_PAY_INSTRUCT);
         m_pInfoTabCtrl->registerControl (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_PAY_INSTRUCT);
      }
      if (!m_bPayInstructSelectionInProgress)
      {
         LoadListControl (IDC_LV_PAY_INSTRUCT);
      }
   }
   else 
   {   
		//remove controls on dilution page
      if (m_pInfoTabCtrl->HasTab (TXT_TAB_TITLE_PAY_INSTRUCT))
      {
         m_pInfoTabCtrl->removeListControlFromPage (IDC_LV_PAY_INSTRUCT, TXT_TAB_TITLE_PAY_INSTRUCT);
         m_pInfoTabCtrl->removeControlFromPage (IDC_BTN_TAB_INFO_DETAILS, TXT_TAB_TITLE_PAY_INSTRUCT);
			//remove dilution page
         m_pInfoTabCtrl->RemoveTab (TXT_TAB_TITLE_PAY_INSTRUCT);
         //disconnect the list from data
         ConnectListToData (IDC_LV_PAY_INSTRUCT, false);
			//also, hide the list
			GetList (IDC_LV_PAY_INSTRUCT)->Show (false);
      }      
   }
   return bArePayInstructAllowed;
}

//******************************************************************************
bool TradesDlg::GetDataForControl( UINT controlID, 
                                   DString &dstrValueOut, 
                                   bool bFormatted, 
                                   int index) const
{
   bool bReturn = false;

   switch( controlID )
   {
      case IDC_STC_BANK_ID:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                    IFASTBP_PROC::TRADES_LIST, 
                                    ifds::BankIdType, 
                                    dstrBankIDType, 
                                    false);

            if (FinancialInstitution::getBankIdNumInfo ( dstrBankIDType, 
                                                         nMaxLength, 
                                                         bIsAllDigits, 
                                                         nAllMaxLength))
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::TRADES_LIST, 
                                           ifds::BankIdValue, 
                                           dstrValueOut, 
                                           false);
                  dstrValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }
      case IDC_STC_PSETYPE :
         {
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::TRADES_LIST, 
                                     ifds::PSEProgramTypeList, 
                                     dstrValueOut, 
                                     true);  
            bReturn = true;
            break;
         }
      case IDC_STC_PSELENGTH :
         {
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::TRADES_LIST, 
                                     ifds::PSEProgramLenList, 
                                     dstrValueOut, 
                                     true);  
            bReturn = true;
            break;
         }
      case IDC_STC_PSEYEAR :
         {
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::TRADES_LIST, 
                                     ifds::PSEProgramYearList, 
                                     dstrValueOut, 
                                     true);  
            bReturn = true;
            break;
         }
     
      default:
         bReturn = false;
      break;
   }
   return(bReturn);
}
//******************************************************************************
bool TradesDlg::updateG1G2Page ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("updateG1G2Page"));

   if( MARKET_IDS::LUXEMBOURG != m_strMarket ||
       !m_pFeesTabCtrl )
        return false;
   DString dstrG1G2ApplicableTrade;//, dstrTransType;
   getParent ()->getField ( this, IFASTBP_PROC::TRADES_LIST, isG1G2Applicable, dstrG1G2ApplicableTrade, false );
   if( I_("Y") == dstrG1G2ApplicableTrade )
   {
     if(! m_pFeesTabCtrl ->HasTab(TXT_TAB_G1G2_DETAILS) )
     {
        m_pFeesTabCtrl->AddTab (TXT_TAB_G1G2_DETAILS);                           
        //register G1 G2 Details tab controls if not 
        for(unsigned int i=0; i<numG1G2DetailsTabControls; i++)
        {
          //Register the static controls
          //AddControl(CTRL_STATIC, G1G2DetailsTabControls[i].STATIC_LABEL, CTRLFLAG_GUI_FIELD );
          if( NO_CONTROL != G1G2DetailsTabControls[i].STATIC_LABEL )                 
              m_pFeesTabCtrl->registerControl(G1G2DetailsTabControls[i].STATIC_LABEL, TXT_TAB_G1G2_DETAILS ); 
          // Register the edit controls
          if( NO_CONTROL != G1G2DetailsTabControls[i].EDIT_CONTROL )
              m_pFeesTabCtrl->registerControl(G1G2DetailsTabControls[i].EDIT_CONTROL, TXT_TAB_G1G2_DETAILS ); 
        }
        m_bG1G2PageRegistered = true;          
     } 
     LoadControls (TRADE_CONTROLS::G1G2);               
   } 
   else
   { 
      if (m_pFeesTabCtrl->HasTab (TXT_TAB_G1G2_DETAILS))
      {
        //G1 G2 Details tab 
        for(unsigned int i=0; i<numG1G2DetailsTabControls; i++)
        {
          //Register the static controls
          if( NO_CONTROL != G1G2DetailsTabControls[i].STATIC_LABEL )
             m_pFeesTabCtrl->removeControlFromPage(G1G2DetailsTabControls[i].STATIC_LABEL, TXT_TAB_G1G2_DETAILS ); 
          // Register the edit controls
          if( NO_CONTROL != G1G2DetailsTabControls[i].EDIT_CONTROL )
              m_pFeesTabCtrl->removeControlFromPage(G1G2DetailsTabControls[i].EDIT_CONTROL, TXT_TAB_G1G2_DETAILS ); 
        }
        m_pFeesTabCtrl->RemoveTab(TXT_TAB_G1G2_DETAILS); 
        m_bG1G2PageRegistered = false; 
      }
   }
   showG1G2Controls(I_("Y") == dstrG1G2ApplicableTrade);    
   return( I_("Y") == dstrG1G2ApplicableTrade );  
}
//******************************************************************************
void TradesDlg::showG1G2Controls(bool bShow)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("showG1G2Controls"));  

  for(unsigned int i=0; i<numG1G2DetailsTabControls; i++)
  {
     GetDlgItem( G1G2DetailsTabControls[i].STATIC_LABEL )->ShowWindow( bShow ); 
     if( NO_CONTROL != G1G2DetailsTabControls[i].EDIT_CONTROL )
     {
       GetDlgItem( G1G2DetailsTabControls[i].EDIT_CONTROL)->ShowWindow( bShow ); 
       ConnectControlsToData (G1G2DetailsTabControls[i].EDIT_CONTROL, bShow);
     }
  }  
  if (m_pFeesTabCtrl &&  m_pFeesTabCtrl->HasTab (TXT_TAB_G1G2_DETAILS) )
       m_pFeesTabCtrl->SelectTab (TXT_TAB_G1G2_DETAILS);   
}
//******************************************************************************
CString TradesDlg::getCustomString(const BFContainerId& bFContainerId, const BFFieldId& idField )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("getCustomString")); 
   CString cstrFormttedValue = NULL_STRING ;
   if(ifds::HighestEntityRisk == idField)
   {
       DString dstrDisplayCode;
       DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
       cstrFormttedValue.LoadString( TXT_HIGH_RISK );
       if( dstWorkSession &&
           dstWorkSession->getOption( ifds::HighRiskDispMode, dstrDisplayCode, getParent()->getDataGroupId() ) <= WARNING )
       {            
            if( I_("1") == dstrDisplayCode )
            {
              DString dstrHighRiskCode;
              getParent()->getField( this, bFContainerId, ifds::HighestEntityRisk, dstrHighRiskCode, true );
              dstrHighRiskCode = I_(" -") + dstrHighRiskCode;
              cstrFormttedValue.Append(dstrHighRiskCode.c_str());
            }        
       }
   }
   return cstrFormttedValue;
}

//******************************************************************************
void TradesDlg::OnBtnAlertMessage()
{
    openAlertMessageScreen();
}

//******************************************************************************
void TradesDlg::openAlertMsgAndRemarkScreen()
{
    DString dstrRemarkAlertExists, dstrAlertMessageExists, dstrAlertViewed;
    getParent()->getField(this, ACCOUNT, ifds::RemarkAlertExists, dstrRemarkAlertExists, false);
    getParent()->getField(this, ACCOUNT, ifds::AlertMessageExists, dstrAlertMessageExists, false);
    getParent()->getField(this, BF::NullContainerId, ifds::AlertViewed, dstrAlertViewed, false);

    if (dstrAlertViewed != YES && dstrAlertMessageExists == YES)
    {
        getParent()->setField(this, BF::NullContainerId, ifds::AlertViewed, YES, false);
        openAlertMessageScreen();

        if (dstrRemarkAlertExists == YES)
        {
            openRemarkScreen();
        }
    }

    GetDlgItem(IDC_BTN_ALERT_MESSAGES)->EnableWindow(dstrAlertMessageExists == YES);
}

//******************************************************************************
void TradesDlg::openAlertMessageScreen()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("openAlertMessageScreen"));

    try
    {
        E_COMMANDRETURN eRtn = CMD_CANCEL;

        DString dstrAccountNum, dstrShrNum;
        getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum); 
        getParent()->getField(this, SHAREHOLDER, ifds::ShrNum, dstrShrNum);

        setParameter(ALERT_MSG_PARAM::ACCOUNT_NUM, dstrAccountNum);
        setParameter(ALERT_MSG_PARAM::SHAREHOLDER_NUM, dstrShrNum );
        setParameter(ALERT_MSG_PARAM::FROM_SCREEN, ALERT_MSG_OPENED_FROM::TRADE);

        eRtn = invokeCommand(getParent(), CMD_BPROC_ALERT_MESSAGES, PROC_NO_TYPE, true, NULL);
    }
    catch (ConditionException &ce)
    {
        ConditionMessageBox(ce);
    }
    catch (...)
    {
        DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
    }   
}

//******************************************************************************
void TradesDlg::openRemarkScreen()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("openRemarkScreen"));
   
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString strAcctNum;
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, strAcctNum, false);

      
      /*int accountIndex = m_lvAccounts.GetNextSelection( );
      DString name;
      DString strMarket = DSTCommonFunctions::getMarket();
      
      if( strMarket == MARKET_IDS::JAPAN )
          getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, true );
      else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
          getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, false );
      setParameter( NAME, name);*/
      setParameter(ACCOUNT_NUM, strAcctNum );
      setParameter(I_("ORG_CMDID"), CMD_BPROC_REMARKS);
      SetMessageStatusBar( TXT_LOAD_REMARKS );

      eRtn = invokeCommand(getParent(), CMD_BPROC_REMARKS, PROC_NO_TYPE, false, NULL);

      switch( eRtn )
      {
      case CMD_OK:
         case CMD_MODELESS_INPROCESS:
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

}

//******************************************************************************
//                         RevisionControlEntries
//******************************************************************************
//
/*$Log:   Y:/VCS/BF iFAST/ifastgui/TradesDlg.cpp-arc  $
 * 
 *    Rev 1.496   Jul 27 2012 08:42:24   wp040132
 * P0199891 _FN01_Arrow_FAST_File
 * 
 *    Rev 1.495   Jul 26 2012 10:27:56   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.494   26 Jul 2012 10:11:50   if991250
 * Fix Estate Allocation for International clients
 * 
 *    Rev 1.493   25 Jul 2012 17:51:06   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.492   Jul 12 2012 19:14:44   popescu
 * Incident 3013409 - R12.4 REG Desktop - Tab sequence for exchange and transfer trades is incorrect
 * 
 *    Rev 1.491   Jul 03 2012 16:52:34   popescu
 * IN# 2984281 - iFeeTo is not populated - fixes
 * 
 *    Rev 1.490   Jul 02 2012 19:11:08   wp040132
 * P0199883_FN01_Cancellation Rights - Right To Cancel
 * 
 *    Rev 1.489   Jun 28 2012 19:45:14   popescu
 * IN# 2984281 - iFeeTo is not populated - fixes
 * 
 *    Rev 1.488   Jun 21 2012 19:03:14   dchatcha
 * IN# 2984281 - iFeeTo is not populated
 * 
 *    Rev 1.487   May 25 2012 16:14:38   dchatcha
 * IN#2924829 - P186479FN05 GuaranteeOverride is still enabled
 * 
 *    Rev 1.486   May 16 2012 11:20:12   if991250
 * IN2951488 - GI Money out
 * 
 *    Rev 1.485   Apr 26 2012 15:48:58   if991250
 * Money out refresh fees on supress changes
 * 
 *    Rev 1.484   Apr 11 2012 09:56:26   if991250
 * Money Out
 * 
 *    Rev 1.483   Apr 11 2012 11:04:48   dchatcha
 * IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
 * 
 *    Rev 1.482   Apr 03 2012 16:59:24   popescu
 * Incident 2889047 - Missing GIA Trade Entry Validation
 * 
 *    Rev 1.481   Mar 29 2012 23:19:02   dchatcha
 * IN#2901157 - Issue on SEG Trade Processing
 * 
 *    Rev 1.480   Mar 26 2012 22:37:28   dchatcha
 * P186484 FN05 Seg Trade Proceesing
 * 
 *    Rev 1.479   Mar 20 2012 16:43:42   if991250
 * IN 2885623 - GI Money Oout
 * 
 *    Rev 1.478   Mar 13 2012 17:40:44   if991250
 * IN 2879297: Money Out
 * 
 *    Rev 1.477   Mar 12 2012 18:11:38   if991250
 * GI Money Out
 * 
 *    Rev 1.476   Mar 08 2012 15:13:48   if991250
 * Account Commitment
 * 
 *    Rev 1.475   Mar 08 2012 10:04:52   if991250
 * GI Money Out
 * 
 *    Rev 1.473   Feb 21 2012 17:15:56   if991250
 * Mat Sweep Instructions - reset on modless set focus and init
 * 
 *    Rev 1.472   Feb 08 2012 04:56:24   panatcha
 * DesktopWeb conversion
 * 
 *    Rev 1.471   Jan 26 2012 21:21:32   panatcha
 * syn up : 2810924 - fixed the screen parameters
 * 
 *    Rev 1.470   Jan 20 2012 14:08:02   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.469   Jan 06 2012 13:40:04   if991250
 * IA money out
 * 
 *    Rev 1.468   Dec 22 2011 16:04:50   popescu
 * INA Commission Work - Fixed crash when selection term depoisti in the trading screen -
 * 
 *    Rev 1.467   Dec 19 2011 23:46:12   popescu
 * DSK French / last screens to be converted to extJS
 * 
 *    Rev 1.466   Dec 14 2011 15:42:40   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.465   Dec 13 2011 09:36:50   popescu
 * INA Commission Work
 * 
 *    Rev 1.464   Dec 05 2011 16:51:36   popescu
 * Fix trading crash in international market
 * 
 *    Rev 1.463   Nov 29 2011 16:15:20   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.462   Nov 28 2011 17:09:46   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.461   Nov 28 2011 12:57:48   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.460   Nov 27 2011 19:44:50   popescu
 * INA Commission Work
 * 
 *    Rev 1.459   Nov 21 2011 18:48:22   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.458   Nov 15 2011 15:36:18   popescu
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.457   Nov 08 2011 22:05:14   kitticha
 * Sync up from 12.1 - PETP0188150 FN01 IN2713809 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.456   Nov 08 2011 10:15:28   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.455   Nov 01 2011 15:38:34   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.454   Nov 01 2011 01:03:28   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.453   Oct 31 2011 17:11:26   popescu
 * P0186477/FN 03 - GIA Trading - Money In - added two new tabs to trade dlg
 * 
 *    Rev 1.452   Oct 21 2011 07:29:48   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.451   Oct 14 2011 12:14:32   panatcha
 * IN2689391 - [update] change field
 * 
 *    Rev 1.450   Oct 13 2011 06:21:46   panatcha
 * IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
 * 
 *    Rev 1.449   Aug 03 2011 11:18:26   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.448   Jun 28 2011 10:10:54   panatcha
 * P0184541_FN01_InvescoQESItrans
 * 
 *    Rev 1.447   Apr 08 2011 03:23:44   kitticha
 * Sync up from 1.443.1.2 - PETP0179308_FN01_IN2487930_Desktop not support EFT Purchase Check paytype.
 * 
 *    Rev 1.446   Mar 14 2011 10:47:30   jankovii
 * Sync up: IN 2458927 - P0181943 - SWIFT XML - Split Commission Exchanges
 * 
 *    Rev 1.445   Mar 07 2011 13:11:46   jankovii
 * Sync up: PET181943 FN01 - XMLPhase 2
 * 
 *    Rev 1.444   Jan 12 2011 14:21:40   dchatcha
 * IN# 2346626 - NeedToReportto HRSDC flag should be switched to N for RD-83 and GRRepayReason-I01 or I02.
 * 
 *    Rev 1.443   Nov 23 2010 00:21:50   dchatcha
 * Synch up: IN# 2304816 - Rel 100 QESI project. T06 special tax.
 * 
 *    Rev 1.442   Nov 22 2010 13:24:48   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.441   Sep 22 2010 06:11:10   dchatcha
 * IN# 2257866 - Trade Entry Screen - Deposit Code 52 not displayed in dropdown.
 * 
 *    Rev 1.440   Aug 05 2010 05:17:42   dchatcha
 * IN# 2202493 - QESI prerel99 - 'Need to report to HRDC' field default.
 * 
 *    Rev 1.439   Jun 11 2010 05:45:14   kitticha
 * PETP0165541 FN02 IN#2123752 - PSE Fix.
 * 
 *    Rev 1.438   Jun 04 2010 03:53:00   kitticha
 * IN#2123752 - Additional logic and validation for PSE.
 * 
 *    Rev 1.437   May 31 2010 15:30:12   jankovii
 * Sync up: IN 2117398 - All fund Transfer
 * 
 *    Rev 1.436   May 28 2010 10:22:34   dchatcha
 * PET0165541 FN02 QESI RESP phase2 - fix compile error, wrong position.
 * 
 *    Rev 1.435   May 28 2010 10:11:24   dchatcha
 * PET0165541 FN02 QESI RESP phase2 - fix compile error.
 * 
 *    Rev 1.434   May 27 2010 05:36:28   kitticha
 * PETP0165541 FN02 QESI Phase2.
 * 
 *    Rev 1.433   May 14 2010 07:17:44   dchatcha
 * PET0165541 FN01 QESI RESP Trading - reload grid cell Linkedentityid.
 * 
 *    Rev 1.432   May 12 2010 07:56:18   popescu
 * RESP - Added TaxYear and related validation
 * 
 *    Rev 1.431   May 06 2010 23:36:42   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.430   May 04 2010 00:41:02   popescu
 * RESP-QESI - added mask 2 leading zeros for PSEProgramType
 * 
 *    Rev 1.429   Apr 30 2010 15:32:44   popescu
 * RES-QESI Trading - PSE/EAP work
 * 
 *    Rev 1.428   Apr 29 2010 23:22:08   popescu
 * RES-QESI Trading - PSE/EAP work
 * 
 *    Rev 1.427   Apr 29 2010 12:44:24   popescu
 * PET0165541 FN01 QESI RESP Trading - PSE/EAP fields
 * 
 *    Rev 1.426   Apr 27 2010 16:21:12   popescu
 * PET0165541 FN01 QESI RESP Trading - restore 1.423 and added the two new fields.
 * 
 *    Rev 1.423   Apr 21 2010 14:24:54   kitticha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.422   Apr 21 2010 14:18:48   kitticha
 * PET0165541 FN01 QESI RESP Trading.
 * 
 *    Rev 1.421   Apr 21 2010 01:23:20   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.420   Apr 20 2010 00:56:36   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
 * 
 *    Rev 1.419   Apr 16 2010 18:28:16   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.418   Apr 15 2010 18:10:22   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
 * 
 *    Rev 1.417   Apr 15 2010 10:30:28   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.416   Apr 13 2010 12:57:34   kitticha
 * PET0165541_FN01_QESI_Transaction.
 * 
 *    Rev 1.415   Apr 13 2010 09:40:24   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.414   Mar 29 2010 22:51:32   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.413   Mar 29 2010 09:42:34   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.412   Mar 23 2010 10:07:40   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.411   Mar 22 2010 15:00:16   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.410   Mar 08 2010 13:22:30   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.409   Dec 02 2009 14:56:56   popescu
 * Prepare the terrain for incident 1780456, which will go in release 98 
 * 
 *    Rev 1.408   Aug 20 2009 12:40:24   dchatcha
 * List valid for international market only.
 * 
 *    Rev 1.407   Aug 14 2009 10:21:36   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.406   Aug 11 2009 13:49:30   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.405   Jul 29 2009 00:08:56   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
 * 
 *    Rev 1.404   Jul 24 2009 01:29:46   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.403   Jun 23 2009 04:21:56   wutipong
 * #1639282 Move the updateSplitCommissionPage() call to appropriate place.
 * 
 *    Rev 1.402   Jun 11 2009 12:19:14   wutipong
 * #IN1639282 Refresh SplitCommission when TransFeeList is refreshed (after from fund is changed).
 * 
 *    Rev 1.401   May 26 2009 04:13:00   wutipong
 * INC#1358908 - Sync up
 * 
 *    Rev 1.400   May 19 2009 14:26:52   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.399   Apr 20 2009 05:38:18   dchatcha
 * IN 1402420,1594221 - RL91 - Override tax rate issues. Remove code which are not consistent with latest solution for this issue.
 * 
 *    Rev 1.398   Mar 18 2009 03:48:48   wutipong
 * IN#1358908 - AIG unit rounding issue -- more fix
 * 
 *    Rev 1.397   Mar 11 2009 17:45:28   wutipong
 * IN1358908 AIG Unit Rounding Issue -- restrict user to enter decimal longer than fund unit precision to amount field, if amount type is Units.
 * 
 *    Rev 1.396   Feb 23 2009 04:10:18   dchatcha
 * IN 1402420,1594221 - RL91 - Override tax rate issues.
 * 
 *    Rev 1.395   Dec 24 2008 18:19:02   wongsakw
 * IN1393123 Non same day Switches not being settled through cycle autosettlement
 * 
 * Correcting compilation error.
 * 
 *    Rev 1.394   Dec 23 2008 17:17:38   wongsakw
 * IN1393123 -- Non same day Switches not being settled through cycle autosettlement
 * 
 * More changes based on Serban's suggestion.
 * 
 *    Rev 1.393   Dec 19 2008 17:11:42   wongsakw
 * IN1393123 Non same day switches not being settled through cycle autosettlement
 * 
 *    Rev 1.392   24 Oct 2008 11:58:50   popescu
 * Incident 1309030 - re-coded the realignment transfer logic 
 * 
 *    Rev 1.391   06 Oct 2008 13:20:54   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.390   31 Jul 2008 15:22:20   kovacsro
 * IN#1341334 - Bank Number not displayed in Trade Entry screen
 * 
 *    Rev 1.389   03 Jun 2008 15:37:08   kovacsro
 * restored rev. 1.387
 * 
 *    Rev 1.387   06 Feb 2008 11:08:58   kovacsro
 * IN#1053526 - settlm. location
 * 
 *    Rev 1.386   Jan 22 2008 15:39:46   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.385   06 Dec 2007 15:20:32   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.384   28 Sep 2007 13:30:12   kovacsro
 * IN#956765 - changed some statics into edit boxes
 * 
 *    Rev 1.383   24 Sep 2007 11:34:54   popescu
 * Hide/Show the delivery to method.
 * 
 *    Rev 1.382   17 Sep 2007 16:12:14   popescu
 * Incidetn# 956765 - moved delivery to to the main tradesdlg.cpp
 * 
 *    Rev 1.381   Sep 04 2007 16:39:48   jankovii
 * In #939902 - If Settle In date is modified manually set SettleDateOverriden to Y.
 * 
 *    Rev 1.380   Aug 10 2007 14:09:02   jankovii
 * PET 2360 FN14 FN19 - Management Fee.
 * 
 *    Rev 1.378   12 Jul 2007 17:10:16   popescu
 * AIM GAP 2 AMS - added an extra field to trading CloneAcctAMS - used in AllTransfer to copy AMS to the to acct.
 * 
 *    Rev 1.377   Mar 30 2007 14:02:18   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.375   Mar 19 2007 10:52:36   popescu
 * Incident#  831221 - called the browser version - fixed compile issues
 * 
 *    Rev 1.374   Mar 19 2007 10:10:46   popescu
 * Incident#  831221 - called the browser version
 * 
 *    Rev 1.373   Mar 14 2007 14:36:38   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.372   Dec 20 2006 16:05:26   fengyong
 * PET2282 FN01 - Screen title change
 * 
 *    Rev 1.371   Dec 20 2006 15:47:06   fengyong
 * Temp check in for PET2282 FN01 - screen title
 * 
 *    Rev 1.370   Dec 19 2006 16:56:54   fengyong
 * PET2282 FN01 - Add Clone Account web page
 * 
 *    Rev 1.369   Nov 10 2006 18:23:52   popescu
 * PET 2881/01 - added the UAF permissions
 * 
 *    Rev 1.368   Nov 10 2006 18:07:48   popescu
 * PET 2281/FN 01
 * 
 *    Rev 1.367   Nov 08 2006 17:30:10   popescu
 * PET 2281/FN 01- copy account for TA 
 * 
 *    Rev 1.366   Sep 22 2006 16:08:44   popescu
 * Incident# 639692 - removed the validation for other confirm type = '2' for network id partnerworld
 * 
 *    Rev 1.365   Sep 15 2006 19:43:32   popescu
 * STP 2217/13 - fixes
 * 
 *    Rev 1.364   Sep 07 2006 21:39:24   popescu
 * STP 2192/02
 * 
 *    Rev 1.363   Aug 29 2006 18:22:06   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.362   Aug 29 2006 18:16:08   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.360   Apr 06 2006 10:51:04   jankovii
 * PET 1334 Alternative Product.
 * 
 *    Rev 1.359   Feb 21 2006 10:45:28   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.358   Feb 20 2006 11:53:14   ZHANGCEL
 * PET 1334 - FN1 -- Added new field ESGSettle in Grid 
 * 
 *    Rev 1.357   Jan 18 2006 14:26:56   popescu
 * Incident# 519360 - dsk pushes the trade date if user changes it to a non-business date the second time,
 * 
 *    Rev 1.356   Jan 12 2006 13:48:04   AGUILAAM
 * PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
 * 
 *    Rev 1.355   Jan 10 2006 13:26:26   porteanm
 * Incident 514223 - Free/Non Age Amount Type.
 * 
 *    Rev 1.354   Jan 10 2006 12:32:30   porteanm
 * Incident 516321 - Refresh the EUSD-related fields based on fund/class even if empty - for Transfer as well.
 * 
 *    Rev 1.353   Jan 10 2006 12:21:00   porteanm
 * Incident 516321 - Refresh the EUSD-related fields based on fund/class even if empty.
 *
 *    Rev 1.352   Jan 04 2006 16:09:38   popescu
 * Incident# 511602 - The mask used for fields TIS and Cost has been changed to follow the NAV price mask based on the requierment.	
 * 
 *    Rev 1.351   Nov 30 2005 12:04:28   popescu
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.350   Nov 29 2005 15:24:32   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.349   Nov 10 2005 11:03:12   popescu
 * Incident# 450556 - if rebook and AWD enabled ExtTransNum has to be updated
 * 
 *    Rev 1.348   Sep 15 2005 12:57:56   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.347   Aug 15 2005 16:57:58   popescu
 * Incident# 379377 - fixed system crash if user enters to fund for exchange/transfer
 * 
 *    Rev 1.346   Jul 15 2005 12:08:40   popescu
 * Incident 357008 - refresh fees page if settle currency changes, synch-up from 63.0.0
 * 
 *    Rev 1.345   Jul 11 2005 20:15:00   AGUILAAM
 * PET1235_FN01: dilution, part of Rebook/Cancellation
 * 
 *    Rev 1.344   Jul 07 2005 12:17:38   AGUILAAM
 * PET1235 : dilution, part of Rebook/Cancellation
 * 
 *    Rev 1.343   Jun 30 2005 11:06:06   popescu
 * PET 1117/08 - fixed F4 no fund nbr/isin/wkn - search issue
 * 
 *    Rev 1.342   Jun 16 2005 19:00:54   popescu
 * Incident# 323484 - added Delivery Method field to attribute box on the trade entry screen
 * 
 *    Rev 1.341   Jun 10 2005 12:53:24   popescu
 * Incident#:280865 - fixed stop sign on tabs if errors in tabs and user resets the dialog
 * 
 *    Rev 1.340   Jun 07 2005 15:55:02   AGUILAAM
 * IN 314827 - Settlement Date should not revert back to default after user has specifically modified it.
 * 
 *    Rev 1.339   Jun 02 2005 09:29:42   yingbaol
 * PET1203,FN01: change ROA control as numeric
 * 
 *    Rev 1.338   May 30 2005 17:57:42   porteanm
 * PET OPC Confirm Reprint - Set Reprint/TxnCancel parameters.
 * 
 *    Rev 1.337   May 30 2005 16:11:34   popescu
 * Incident #301110 - backed out fix
 * 
 *    Rev 1.336   May 26 2005 17:21:50   popescu
 * Incident 280865 - subsequent fix for sales rep pop-up question display issue - synch-up from release 61.0.4
 * 
 *    Rev 1.335   May 24 2005 15:55:50   yingbaol
 * PET1203,FN01: refresh split commission when ROA amount changes
 * 
 *    Rev 1.334   May 20 2005 17:34:52   popescu
 * PET 1117/08 - deposit date refresh - synch-up 1.330.1.1
 * 
 *    Rev 1.333   May 19 2005 17:12:04   popescu
 * Incident # 315848 -- fixed the address display issue (pack the address lines - for Redemptions/Exchanges) - synch-up from release 61.0.3 - 1.331.1.0
 * 
 *    Rev 1.332   May 18 2005 09:06:30   yingbaol
 * PET1203,FN01: Commission Class A
 * 
 *    Rev 1.331   May 03 2005 15:32:44   Fengyong
 * #Incident 301110 - fix trade date update issue.
 * 
 *    Rev 1.330   Apr 14 2005 16:11:02   yingbaol
 * Incident 283230: Pack edit lines for address.
 * 
 *    Rev 1.329   Apr 07 2005 12:26:24   popescu
 * Incident #278545, open-up effective date field on trade entry screen
 * 
 *    Rev 1.328   Mar 24 2005 10:40:38   popescu
 * Incident # 260181, split commissions not applicable for ED's with deposittypes 9,10,18
 * 
 *    Rev 1.327   Mar 08 2005 08:21:38   popescu
 * Incident # 260166, fixed appearance of PurchaseTotal field,synch-up from release 59.0.5
 * 
 *    Rev 1.326   Mar 03 2005 11:04:42   popescu
 * Incident # 256776, fixed flickering of trading screen when user presses F3, synch-up from release 59.0.5
 * 
 *    Rev 1.325   Feb 28 2005 08:16:08   popescu
 * PET 1117/06, fixed the 'CreateRep' issue. Flag is set to Y if user chooses to create a new rep
 * 
 *    Rev 1.324   Feb 18 2005 16:58:00   popescu
 * Incident #237786, fixed refresh data flickering issue, synch-up from Release 59.0.4
 * 
 *    Rev 1.323   Feb 17 2005 17:06:02   popescu
 * Incident # 243445, fixed the fees grid refresh and renamed one  member variable to reflect the usage
 * 
 *    Rev 1.322   Feb 14 2005 19:06:38   popescu
 * 243417, always enable 'Batch' button
 * 
 *    Rev 1.321   Jan 31 2005 13:47:46   popescu
 * PTS 10038010 & 10036396 : Settlement Date and DepositDate was overriden by user and view return a new value. Refresh the new value from view. Rel_59 synch-up, Rev 1.318.1.1
 * 
 *    Rev 1.320   Jan 25 2005 11:44:14   popescu
 * PTS 10038254, force the selection on the Broker/Branch/Slslrep tab only if told so, synch-up from Rel_59, branch 1.318.1.0
 * 
 *    Rev 1.319   Jan 24 2005 17:44:32   popescu
 * PET 1117/68, SWIFT, Pwld enhancement
 * 
 *    Rev 1.318   Jan 21 2005 11:18:38   hernando
 * PET910 - .NET/AWD Testing - Retrieve ObjectID from AWD and store it in fields.
 * 
 *    Rev 1.317   Jan 19 2005 16:03:00   popescu
 * PTS 10038094, reset internal error
 * 
 *    Rev 1.316   Jan 19 2005 12:57:16   popescu
 * PTS 10037789, fixed reset locking issue
 * 
 *    Rev 1.315   Jan 18 2005 19:42:28   popescu
 * PTS 10038609, acquisition does not get refreshed if split comm changes to default
 * 
 *    Rev 1.314   Jan 14 2005 16:24:50   popescu
 * PTS 10037922, saved the traded last account num
 * 
 *    Rev 1.313   Jan 12 2005 18:53:30   popescu
 * PTS 10037339, allowed user to set Redemption Fee up
 * 
 *    Rev 1.312   Jan 12 2005 15:30:06   popescu
 * PTS 10037793, update split commission if acq fee rate changes
 * 
 *    Rev 1.311   Jan 12 2005 09:59:04   popescu
 * PTS 10037725, enable reset button only for new items
 * 
 *    Rev 1.310   Jan 11 2005 18:53:34   popescu
 * PTS 10037725, user should not be able to enter a trade with an erroneous account num
 * 
 *    Rev 1.309   Jan 10 2005 18:54:08   popescu
 * PTS 10037268, fee rate should only be entered as numeric
 * 
 *    Rev 1.308   Jan 06 2005 14:28:22   popescu
 * PTS 10037580, reloade the fees grid when there is a change on the amount type
 * 
 *    Rev 1.307   Dec 29 2004 18:42:06   popescu
 * PTS 10037326, allocations should not trigger amount is zero error if booking a purchase. Also, fixed allocations list selection.
 * 
 *    Rev 1.306   Dec 20 2004 18:27:54   popescu
 * PET 1117/56 refresh/clean the dialog after add/delete/reset
 * 
 *    Rev 1.305   Dec 16 2004 20:18:08   popescu
 * PET 1117/06, update the allocation rather the split commission when changing amount type.
 * 
 *    Rev 1.304   Dec 16 2004 19:35:34   popescu
 * PTS 10036881, fixed display issue for new trades and mod pending trades
 * 
 *    Rev 1.303   Dec 11 2004 11:48:18   popescu
 * PET 1117/56 more fixes, pending trade mods
 * 
 *    Rev 1.302   Dec 09 2004 22:31:12   popescu
 * PET 11717/06, fees and mod pending trades
 * 
 *    Rev 1.301   Dec 09 2004 12:37:54   popescu
 * PET 1117/56, more fees work /pending trade
 * 
 *    Rev 1.300   Dec 08 2004 22:08:40   popescu
 * PET 1117/06, more fees
 * 
 *    Rev 1.299   Dec 07 2004 02:45:16   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.298   Dec 07 2004 01:38:16   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.297   Dec 06 2004 10:41:14   popescu
 * PET 1117/56, fees processing
 * 
 *    Rev 1.296   Dec 03 2004 10:46:24   popescu
 * PET 1117/06, fees processing
 * 
 *    Rev 1.295   Dec 02 2004 20:59:48   popescu
 * PET 1117/06, more fee fixes
 * 
 *    Rev 1.294   Dec 02 2004 18:21:46   popescu
 * PET 1117/06/56 trades processing
 * 
 *    Rev 1.293   Nov 30 2004 20:10:42   popescu
 * PET 1117/06
 * 
 *    Rev 1.292   Nov 30 2004 07:53:38   popescu
 * PET 1117/06, made purchase total and OnBtnHistory active once again
 * 
 *    Rev 1.291   Nov 29 2004 20:31:04   popescu
 * PET 1117/06/56 fees/trades processing
 * 
 *    Rev 1.290   Nov 27 2004 21:22:18   popescu
 * PET 1117/06, trade processing
 * 
 *    Rev 1.289   Nov 25 2004 14:59:26   popescu
 * PET 1117/06, settle locations
 * 
 *    Rev 1.288   Nov 25 2004 11:44:28   popescu
 * PET 1117/06, settle locations
 * 
 *    Rev 1.287   Nov 24 2004 21:36:50   popescu
 * PET 1117/06/56. trade processing, settle location
 * 
 *    Rev 1.286   Nov 22 2004 13:09:56   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.285   Nov 17 2004 16:16:46   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.284   Nov 16 2004 10:18:00   popescu
 * PTS 10030584, set SettleDateOverridden flag to Y, if user changes the SettleDate
 * 
 *    Rev 1.283   Nov 15 2004 11:42:26   popescu
 * PET 1117/06, synch .NET Changes
 * 
 *    Rev 1.282   Nov 09 2004 19:24:02   popescu
 * PET 1117/06, trade processing
 * 
 *    Rev 1.281   Nov 09 2004 16:51:20   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.280   Nov 07 2004 14:56:46   popescu
 * PET 1117/06, synch changes
// 
//    Rev 1.8   Nov 04 2004 17:42:14   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.7   Nov 02 2004 19:19:46   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.6   Oct 28 2004 18:24:04   popescu
// PET 1117/06
// 
//    Rev 1.5   Oct 27 2004 11:27:10   popescu
// PET 1117/06
// 
//    Rev 1.4   Oct 22 2004 19:59:06   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.3   Oct 21 2004 06:29:42   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.2   Oct 01 2004 19:25:50   popescu
// PET 1117/06, SSB Germany Trade processing
// 
//    Rev 1.1   Sep 23 2004 16:01:00   popescu
// PET 1117/06 - Trade processing work in progress...
// 
//    Rev 1.0   Aug 13 2004 18:58:18   popescu
// Initial revision.
 * 
//
*/



