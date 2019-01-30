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
// ^FILE   : TransactionHistoryDlg.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionHistoryDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "transactionhistorydlg.h"
#include "dstcview.h"

#include <configmanager.hpp>

#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>

#include <bfproc\bpsessiontags.h>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\AbstractProcess.hpp>

#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

//baycom number (fund number)
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\splitcommission.hpp>
#include <ifastcbo\supportedproductslist.hpp>
#include <ifastcbo\awdhistoryworklist.hpp>

#include <ifastbp\allocationsprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\splitcommissionsprocessincludes.h>
#include <ifastbp\tradesprocessincludes.h>
#include <ifastbp\transactionallocationsprocessincludes.h>
#include <ifastbp\transhistoryprocessincludes.h>
#include <ifastbp\transSettlementInstrprocessincludes.h>
#include <ifastbp\savingsdirectiveprocessincludes.h>
#include <ifastbp\InventorySummaryProcessIncludes.h>
#include <ifastawd\DSTCAWDSession.hpp>
#include <ifastbp\InvDetlDeductionProcessIncludes.h>
#include <ifastbp\ConfirmReprintProcessincludes.h>
#include <ifastbp\TransactionLinkProcessIncludes.h>
#include <ifastbp\RebookParamProcessIncludes.h>
#include <ifastbp\RefundProcessIncludes.h>
#include <ifastbp\TransCancelProcessincludes.h>
#include <ifastbp\ifasthistoricalparameters.hpp>
#include <ifastbp\InvestorAuthorizationInfoProcessIncludes.h>
#include <ifastbp\resptransactionsprocessincludes.h>

#include <uibase\dstcfuncs.h>

#include <ifastcbo\FundMasterList.hpp>
#include <ifastcbo\FundMaster.hpp>

#include <ifastdataimpl\dse_dstc0149_vw.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANS_HISTORY;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransactionHistoryDlg > dlgCreator( CMD_GUI_TRANS_HISTORY );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IS_TEXT                 0
#define IS_NUMBER               1
#define IS_DATE                 2
#define IS_INTEGER              3 // strip leading 0
#define ALWAYS_SHOW             4
#define IS_TIME                 5
#define IS_TIME_HHMMSS          6
#define REPLACE_BLANK_BY_NA     7
#define REPLACE_BLANK_BY_OTR    8

#define UM_CAN_REENTER     WM_USER+5000

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACB;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CHEQUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CERTIFICATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REMARKS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDINFO;
//extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANSACTION_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_MARKET_VALUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVENTORY_SUMMARY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVENTORY_DETAIL_DEDUCTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MATCHTRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT_LOCATION_TRADE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_OPC_CONFIRM_REPRINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_CANCEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_PAYMENT_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_AUTHORIZATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DILUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REBOOK;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REFUND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SAVINGS_DIRECTIVE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SETTLEMENT_LOCATION_TRADE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_RESPTRANSACTIONS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_PAYMENT_INFO_FLAG;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SHARE_LOT_BROWSER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SEG_GUARANTEE_RULES;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_ESTATE_ALLOCATION;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_AWDHISTORY;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_INVEST_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AWDHISTORY_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_NOTIONAL_ACTIVITY;

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME          = I_( "TransactionHistoryDlg" );
   const I_CHAR *ONBTNAWD           = I_( "OnBtnAwd" );
   const I_CHAR *LV_TRANS_HISTORY   = I_( "TransHistory" );
   const I_CHAR *LV_TRANS_DETAILS   = I_( "TransDetails" );
   const I_CHAR *LV_PENDING         = I_( "Pending" );
   const I_CHAR *LV_PENDING_DETAILS = I_( "PendingDetails" );
   const I_CHAR *Y                  = I_( "Y" );
   const I_CHAR *N                  = I_( "N" );
   const I_CHAR *NA                 = I_( "n/a" );
   const I_CHAR *CASH               = I_( "CASH" );
   const I_CHAR *M1                 = I_( "-1" );
   const I_CHAR *SPACE              = I_( " " );

   const I_CHAR *pALLFUND           = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM        = I_( "AccountNum" );
   const I_CHAR *pTRANSID           = I_( "TransId" );
   const I_CHAR *pSHAREHOLDERNUM    = I_( "ShareholderNum" );
   const I_CHAR *pFUNDCODE          = I_( "FundCode" );
   const I_CHAR *pCLASSCODE         = I_( "ClassCode" );
   const I_CHAR *pNUMENTRY          = I_( "NumEntry" );
   const I_CHAR *pPENDING           = I_( "Pending" );
   const I_CHAR *pTRANSTYPE         = I_( "TransType" );
   const I_CHAR *pTRANSNUM          = I_( "TransNum" );
   const I_CHAR *pTRADEDATE         = I_( "TradeDate" );
   const I_CHAR *pENTITYID          = I_( "EntityID" );
   const I_CHAR *pPENDINGRID        = I_( "PendingRid" );
   const I_CHAR *pTRANSPEND         = I_( "TransPending" );
   const I_CHAR *pREQTRANSID        = I_( "ReqTransid0" );
   const I_CHAR *pINQUIRYONLY       = I_( "InquiryOnly" );
   const I_CHAR *pPENDINGTRADE      = I_( "PendingTrade" );
   const I_CHAR *DISABLEINVINFO     = I_( "DisableInvInfo" );
   const I_CHAR *pGROSSNETMETHOD    = I_( "GrossNetMethod" );

   const I_CHAR *INACCTNUM          = I_( "InAcctNum" );
   const I_CHAR *INFUND             = I_( "InFund" );
   const I_CHAR *INCERTNUM          = I_( "InCertNum" );
   const I_CHAR *INXREFNUM          = I_( "InXrefNum" );

   const I_CHAR *FUNDCODEVALUE      = I_( "FundCodeValue" );
   const I_CHAR *CLASSCODEVALUE     = I_( "ClassCodeValue" );
   const I_CHAR *FROMDATEVALUE      = I_( "FromDateValue" );
   const I_CHAR *TODATEVALUE        = I_( "ToDateValue" );

   const I_CHAR *YES                = I_("Yes");
   const I_CHAR *MINUS              = I_(" - ");
   const I_CHAR *U                  = I_("U");

   const I_CHAR *ID                       = I_("ID");  // Distribution
   const I_CHAR *ED                       = I_("ED");  // Purchase
   const I_CHAR *INSPECIES_ED             = I_("ED71");// Purchase
   const I_CHAR *HYBRID_ED                = I_("ED72");// InSpecies Purchase
   const I_CHAR *PW                       = I_("PW");  // Hybrid Redemption
   const I_CHAR *INSPECIES_PW             = I_("PW71");// InSpecies Redemption
   const I_CHAR *HYBRID_PW                = I_("PW72");// Hybrid Redemption
   const I_CHAR *TR                       = I_("TR");  // Transfer
   const I_CHAR *XR                       = I_("XR");  // Exchange
   const I_CHAR *TI                       = I_("TI");  // Tansfer In
   const I_CHAR *TO                       = I_("TO");  // Transfer Out
   const I_CHAR *EI                       = I_("EI");  // Exchange In
   const I_CHAR *EO                       = I_("EO");  // Exchange out
   const I_CHAR *AW                       = I_("AW");  // Automatic Withdrawls
   const I_CHAR *TYPE_SWP                 = I_("S");   // SWPs (SWPs - used to be AW)
   const I_CHAR *MGMT_FEE_CODE            = I_("AF91");  // Management Fee
   const I_CHAR *ALL_FUND_TRANSFER        = I_("AFTR");  // All Fund Transfer
   const I_CHAR *INSPECIES_NONPRORATA_ED  = I_("ED73");  // InspNonProRataPurchase
   const I_CHAR *INSPECIES_NONPRORATA_PW  = I_("PW73");  // InspNonProRataRedemption


   const I_CHAR *MODUSER            = I_( "ModUser" );
   const I_CHAR *MODDATE            = I_( "ModDate" );
   const I_CHAR *PROCESSUSER        = I_( "Username" );
   const I_CHAR *PROCESSDATE        = I_( "ProcessDate" );

   const I_CHAR * const BANK_INSTRUCTION_TYPE = I_( "BankInstrType" );
   const I_CHAR * const TRANSACTION           = I_( "Transaction" );
   const I_CHAR * const PENDING               = I_( "Pending" );
   const I_CHAR * const TRANSTYPE             = I_( "TransType" );
   const I_CHAR * const WIREORDNUM            = I_( "WireOrdNum" );
   const I_CHAR * const FROMSCR               = I_( "FromScr" );
   const I_CHAR * const CHEQUE                = I_( "CHQ" );

   const I_CHAR * const PENDPROCRECORD_TYPE   = I_( "PendProcRecordType" );
   const I_CHAR * const AUTHORIZATION         = I_( "Authorization" );
   const I_CHAR * const BATCH                 = I_( "Batch" );
   const I_CHAR * const CLEARING              = I_( "R" );
   const I_CHAR * const FLAT                  = I_("0"); 
   const I_CHAR * const PERCENT               = I_("1"); 

   const I_CHAR * const TRANSHIST_PURCHASE_LIKE   = I_("ED,ID,ID57,ID58,ID59,RP,RC,RD,RM,EDIC");
   const I_CHAR * const TRANSHIST_REDEMPTION_LIKE = I_("PW,LR,RR,AF,AF91,MF,AW,PW96,PWIC");
   const I_CHAR * const TRANSHIST_EXCHANGE_LIKE   = I_("EI,EO,TI,TO,TR,XR,AFTR,TRT,TRE");
   const I_CHAR * const TRANSHIST_EXCHANGE_LIKE_2 = I_("TI04,TI08,TO04,TO08");
   const I_CHAR * const CODE_FUND_CATEGORY_LSIF   = I_( "L" );
   const I_CHAR * const EUSD_TAX_REPORTS = I_("WHAN,WHADJ,WHRE,EIAN");  //EUSD Annual Tax Withholding Report
                                                                        //EUSD Annual Tax Withholding Adjustment Report
                                                                        //EUSD Monthly Tax Withholding Reconciliation Report
                                                                        //EUSD Annual Exchange of Info Report

   const I_CHAR * const NON_REGISTERED_TAX_TYPE    = I_( "0" );
   const I_CHAR * const RRSP_TAX_TYPE              = I_( "1" );
   const I_CHAR * const RRIF_TAX_TYPE              = I_( "2" );
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE   = I_( "9" );
   const I_CHAR * const LRSP_TAX_TYPE              = I_( "U" );
   const I_CHAR * const LRIF_TAX_TYPE              = I_( "L" );
   const I_CHAR * const PRIF_TAX_TYPE              = I_( "R" );
   const I_CHAR * const FAMILY_RESP_TAX_TYPE       = I_( "M" );

   const I_CHAR * const CLIENT                     = I_( "1" );
   const I_CHAR * const INDC90                     = I_( "90" );
   const I_CHAR * const INDC                       = I_( "INDC" );
   const I_CHAR * const BLOCK                      = I_( "B" );
   const I_CHAR * const NO                         = I_( "N" );
   const I_CHAR * const OKCancel                   = I_( "OkCancel" );
   const I_CHAR * const FROM_SCR                   = I_( "CalledFrom" );
   const I_CHAR * const FROM_AWD                   = I_("FromAWD");
   const I_CHAR * const REJ_ALLOC_TAG              = I_("-Alloc");

   const int AUTO_BATCHING = 2;
   const int MULTI_SETTLE_INSTR = 2;

   const I_CHAR *szCmd[]=
   {
      CMD_BPROC_ACB,
      CMD_BPROC_CHEQUE,
      CMD_BPROC_CERTIFICATE,
      CMD_BPROC_REMARKS,
      CMD_BPROC_SYSTEMATIC,
      CMD_BPROC_FUNDINFO,
      CMD_BPROC_ADDRESSES,
      //CMD_BPROC_TRANSACTION_ALLOCATIONS,
      CMD_BPROC_ALLOCATIONS,
      CMD_BPROC_BANK_INSTRUCTIONS,
      CMD_BPROC_ENTITY,
      CMD_BPROC_HISTORICAL_MARKET_VALUE,
      CMD_BPROC_SPLITCOMMISSION,
      CMD_BPROC_MATCHTRANSFER,
      CMD_BPROC_SETTLEMENT_LOCATION_TRADE,
      CMD_BPROC_OPC_CONFIRM_REPRINT,
      CMD_BPROC_SAVINGS_DIRECTIVE,
      //CMD_BPROC_HISTORICAL_INFO,
      //CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION
      CMD_BPROC_HISTORICAL_INFO,
      CMD_BPROC_PAYMENT_INFO_FLAG,
      CMD_BPROC_ESTATE_ALLOCATION
   };
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DealDateTime;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
   extern CLASS_IMPORT const BFTextFieldId ValidDateLag;
   extern CLASS_IMPORT const BFTextFieldId ADLevyFee;
   extern CLASS_IMPORT const BFTextFieldId ADLevyFeeTransType;
   extern CLASS_IMPORT const BFTextFieldId EqualizationActive;
   extern CLASS_IMPORT const BFNumericFieldId Using_AWD;
   extern CLASS_IMPORT const BFTextFieldId AccountableMandatory;
   extern CLASS_IMPORT const BFTextFieldId SplitAcCode;
   extern CLASS_IMPORT const BFTextFieldId Cancellation;
   extern CLASS_IMPORT const BFTextFieldId OPCConfirmsBrokerScreen;
   extern CLASS_IMPORT const BFTextFieldId SuppConfirm;
   extern CLASS_IMPORT const BFTextFieldId ROATransType;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId ESGSettle;
   extern CLASS_IMPORT const BFTextFieldId SendLinkRefNum;
   extern CLASS_IMPORT const BFIntegerFieldId DivDates;
   extern CLASS_IMPORT const BFIntegerFieldId AutoBatch;
   extern CLASS_IMPORT const BFDateFieldId ExpectedSettleDate;
   extern CLASS_IMPORT const BFTextFieldId IsCancelModSEGTradeAllowed;
   extern CLASS_IMPORT const BFTextFieldId RightToCancel;  
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId SDRTExemptCode;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId ToTDCC;
   extern CLASS_IMPORT const BFTextFieldId ToValoren;
   extern CLASS_IMPORT const BFTextFieldId EnableTradeAuthorization;
   extern CLASS_IMPORT const BFTextFieldId EnableTradeRestrictionFields;
   extern CLASS_IMPORT const BFTextFieldId ExternalInstitution;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFTextFieldId OrderRouting;
   extern CLASS_IMPORT const BFTextFieldId OrigGrossNet;
   extern CLASS_IMPORT const BFTextFieldId PricingCode;
   extern CLASS_IMPORT const BFTextFieldId PriceInCode;
   extern CLASS_IMPORT const BFTextFieldId ComponentSplit;
   extern CLASS_IMPORT const BFTextFieldId DistSplitType;
   extern CLASS_IMPORT const BFTextFieldId GateOverrideIndicator;
   extern CLASS_IMPORT const BFDateFieldId RDSPPaymtDate;
}

namespace CND
{  // Conditions used
//   extern const int GUI_ERR_INVALID_FIELD_ENTRY;
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_AWD_LOOKUP_ERROR;
   extern const long GUI_AWD_EXCEPTION;
}

//user access codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const MSG_SEARCH;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const CANCEL_SETTLE;
   extern CLASS_IMPORT I_CHAR * const CANCEL_DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const TRANS_HIST_DILUTION_ALLOC_LIST;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_SEARCH;
   extern CLASS_IMPORT I_CHAR * const MODIFY_BATCH_ID;
   extern CLASS_IMPORT I_CHAR * const RDSP_NOTIONAL_ACTIVITY;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
}

namespace AWD
{  
   extern const I_CHAR *Order_Number;
   extern const I_CHAR *Account_Num;
   extern const I_CHAR *Business_Area;
   extern const I_CHAR *System_ID;
}

namespace SessionTags
{
   extern const I_CHAR *MGMCO;
   extern const I_CHAR *SESSION;
}

namespace TRADETYPE // See:  ifastids/ifastradeids.cpp
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const REINVEST_PURCHASE;
   extern CLASS_EXPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_EXPORT I_CHAR * const TRANSFER_OUT_2;    //  = I_("TO04,TO08");
   extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;   //   = I_("PW,AW,AF,RL,AF91"); // redemption, swp, admin fee, rollover
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;     //   = I_("ED,RC");  //purchase, reinvest purchase
   extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;    //   = I_("ED,RC,PW,AW,AF,RL,AF91,P,S,V");
   extern CLASS_IMPORT I_CHAR * const ALLOC_ELIG;        //   = I_("ED,PW,AW,AF,AF91,RC,P,S,V");
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;     //   = I_("TI,TO,EI,EO,XR,TR,AFTR");
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE_2;
   extern CLASS_IMPORT I_CHAR * const MONEY_OUT_TRADES;  //  = I_("TO,EO,PW,PW71,PW72,PW73,PW98,AW");
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;       //  = I_("TI");
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_2;     //  = I_("TI04,TI08");
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;       //  = I_("EI");
   extern CLASS_IMPORT I_CHAR * const ALLOW_TO_MODIFY_PENDING_TRXN;// = I_("ED,PW,AW,TR,XR,AF91,ID59,AFR,LR,AF,RC");
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;          // = I_( "ID" );
   extern CLASS_IMPORT I_CHAR * const REBOOK_ALLOWABLE_TRANS_TYPES;
   extern CLASS_IMPORT I_CHAR * const CAPITAL_GAIN_INCOME;
   extern CLASS_IMPORT I_CHAR * const SUPPLEMENTAL_INCOME;
   extern CLASS_IMPORT I_CHAR * const MFR_TARDES;
   extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION; //= I_("PW82");
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const EFT;
}

#define _MASTER_MENU                 5000
#define _BROKER_INFORMATION          5030 //TRANSACTION_PROCESSING_MENU
#define _BRANCH_INFORMATION          5050
#define _TRANSACTION_PROCESSING_MENU 5060
#define _ORDERS_PROCESSED            5070
#define _SETTLEMENTS                 5080
#define _SALES_REP_INFORMATION       5090
#define _BATCH_ORDER_ENTRY           5100
#define _AWD_HISTORY                 5101
#define _SOURCE_OF_FUNDS_CHECKED     5102

//************************************************************************************
TransactionHistoryDlg::TransactionHistoryDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TransactionHistoryDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_AwdActive( NO_AWD )
, m_bFromSettlement( false )
,rebook_( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TransactionHistoryDlg)
   m_FundCurrency = I_("");
   m_NetAmount = I_("");
   m_PreBalance = I_("");
   m_SettleDate = I_("");
   m_SettleInDate = I_("");
   m_rbHistory = 0;
   m_BatchNum = _T("");
   m_SettleBatchNum = _T("");
   m_TransNbr = _T("");
   m_FundLongName = _T("");
   m_BranchCode = _T("");
   m_BrokerCode = _T("");
   m_SlsrepCode = _T("");
   m_FundNumber = _T("");
   //}}AFX_DATA_INIT

   m_bMessageDisplayed = false;
   FundCode=M1;
   PendingFundCode=M1;
   TransId=M1;
   m_bCanReenter = true;
   m_bFromRefresh = false;
   bPopulateDetails = true;

   ALLFUND.LoadString(TXT_TRANS_ALLFUNDMODE);
}

//************************************************************************************
void TransactionHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransactionHistoryDlg)
   DDX_Control(pDX, IDC_CMB_ACTIVITY, m_Activity);
   DDX_Control(pDX, IDC_CMB_FUND, m_Fund);
   DDX_Control(pDX, IDC_LV_ATTRIBUTES, m_TransDetail);
   DDX_Control(pDX, IDC_LV_HISTORY, m_lvReportView);
   DDX_Text(pDX, IDC_TXT_FUND_CURRENCY, m_FundCurrency);
   DDX_Text(pDX, IDC_TXT_NET_AMT, m_NetAmount);
   DDX_Text(pDX, IDC_TXT_PREV_BAL, m_PreBalance);
   DDX_Text(pDX, IDC_TXT_SETTLE_DATE, m_SettleDate);
   DDX_Text(pDX, IDC_TXT_SETTLE_IN_DATE, m_SettleInDate);
   DDX_Radio(pDX, IDC_RB_HISTORY, m_rbHistory);
   DDX_Text(pDX, IDC_TXT_BATCH_NUM, m_BatchNum);
   DDX_Text(pDX, IDC_TXT_SETTLE_BATCH, m_SettleBatchNum);
   DDX_Text(pDX, IDC_TXT_TRANS_NBR, m_TransNbr);
   DDX_Text(pDX, IDC_EDIT_FUNDLONGNAME, m_FundLongName);
   DDX_Text(pDX, IDC_EDIT_BRANCH, m_BranchCode);
   DDX_Text(pDX, IDC_EDIT_BROKER, m_BrokerCode);
   DDX_Text(pDX, IDC_EDIT_SLSREP, m_SlsrepCode);
   DDX_Text(pDX, IDC_TXT_FUND_NUMBER, m_FundNumber);
   //}}AFX_DATA_MAP
}

//************************************************************************************
BEGIN_MESSAGE_MAP(TransactionHistoryDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransactionHistoryDlg)
ON_BN_CLICKED(IDC_RB_HISTORY, OnRbHistory)
ON_BN_CLICKED(IDC_RB_PENDING, OnRbPending)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ATTRIBUTES, OnDblclkLvAttributes)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LV_ATTRIBUTES, OnItemchangedLvAttributes)
ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
ON_CBN_SELENDOK(IDC_CMB_FUND, OnSelendokCmbFund)
ON_CBN_SELENDOK(IDC_CMB_ACTIVITY, OnSelendokCmbActivity)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
ON_BN_CLICKED(IDC_BTN_AWD, OnBtnAwd)
ON_BN_CLICKED(IDC_BTN_SETTLEMENT, OnBtnSettlement)
ON_BN_CLICKED( IDC_BTN_SETT_LOC,OnBtnSettlLocationInstr )
ON_BN_CLICKED( IDC_BTN_DEDUCT_DETAIL,OnBtnDeductDetail )
ON_BN_CLICKED( IDC_BTN_INVENTORY_SUMMARY,OnBtnInvSummary )
ON_BN_CLICKED( IDC_BTN_EXT_LINKS,OnBtnTransactionExternalLinks )
ON_BN_CLICKED( IDC_BTN_CLAWBACK_INFO,OnBtnInvClawbackInfo )
ON_BN_CLICKED( IDC_BTN_TXN_CANCEL,OnBtnTrxnCancelation )
ON_BN_CLICKED( IDC_BTN_DILUTION,OnBtnTrxnDilution )
ON_BN_CLICKED( IDC_BTN_REPRINT, OnBtnReprint )
ON_BN_CLICKED( IDC_BTN_INT_LINKS, OnBtnInternalLink )
ON_BN_CLICKED( IDC_BTN_SAVINGS_DIRECTIVE, OnBtnSavingsDirective )
ON_BN_CLICKED( IDC_BTN_PAYMENT_SEARCH, OnBtnPaymentSearch )
ON_BN_CLICKED( IDC_BTN_PAY_INSTRUCT, OnBtnPayInstruct )
ON_BN_CLICKED( IDC_BTN_HISTORY, OnBtnHistory )
ON_BN_CLICKED( IDC_BTN_AUTHORIZATION, OnBtnAuthorization )
ON_BN_CLICKED( IDC_BTN_BATCH, OnBtnBatch )
ON_BN_CLICKED( IDC_BTN_SETTL_LOCS, OnBtnMultiSettlInstr )
ON_BN_CLICKED( IDC_BTN_RESP_HIST, OnBtnRESPHist )
ON_BN_CLICKED( IDC_BTN_PAYMENT_INFO, OnBtnPaymentInfoFlag )
ON_BN_CLICKED( IDC_BTN_SHARELOT, OnBtnShareLot )
ON_BN_CLICKED( IDC_BTN_GUARANTEE_RULES, OnBtnGuaranteeRules )
ON_BN_CLICKED( IDC_BTN_INVESTINFO, OnBtnInvestInfo )
ON_BN_CLICKED( IDC_BTN_RDSP_NOTIONAL_ACTIVITY, OnBtnRDSPNotionalActivity )

//}}AFX_MSG_MAP
ON_MESSAGE(UM_CAN_REENTER, OnUmCanReenter)
ON_MESSAGE(WM_VIEWITEMSELECTED, OnListViewItemChanged)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TransactionHistoryDlg message handlers

//************************************************************************************
void TransactionHistoryDlg::OnRbHistory() 
{
   TRACE_METHOD( CLASSNAME, I_("OnRbHistory"));

   if( !m_bCanReenter )
   {
      return;
   }

   m_rbHistory=0;
   UpdateData(FALSE);
   m_bIsPending = false;

   m_Fund.EnableWindow(TRUE);
   m_Fund.SelectString(0,FundMode);
   m_Activity.EnableWindow(TRUE);

   OnSelendokCmbFund();
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::TRANS_LIST ) );

   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::TRANS_LIST );

   // Enable/Disable Inventory Summary button
   GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( !(DisableInvInfo == I_("Y")) && iItemNumber > 0 );

   GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( false );

   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->EnableWindow( iItemNumber > 0 );
   CString strDeductions; 
   strDeductions.LoadString(TXT_DEDUCTIONS);
   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->SetWindowText( strDeductions );

   GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( false );

   GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( false );

   GetDlgItem( IDC_BTN_SETTLEMENT )->EnableWindow( false );

   GetDlgItem( IDC_BTN_REPRINT )->EnableWindow( false );

   CString strRebook;
   strRebook.LoadString(TXT_REBOOK);
   GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( strRebook );
   GetDlgItem( IDC_BTN_MODIFY )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_BTN_MODIFY )->EnableWindow( iItemNumber > 0 );

   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( iItemNumber > 0 );
   
   GetDlgItem( IDC_BTN_DILUTION )->EnableWindow( false );

   GetDlgItem( IDC_BTN_INT_LINKS )->EnableWindow( m_lvReportView.GetItemCount() > 0 );
   GetDlgItem( IDC_BTN_SAVINGS_DIRECTIVE )->EnableWindow( false );
   GetDlgItem( IDC_BTN_PAYMENT_SEARCH )->EnableWindow( false );
   GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( false );
}

//************************************************************************************
void TransactionHistoryDlg::OnRbPending() 
{
   TRACE_METHOD( CLASSNAME, I_("OnRbPending"));

   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_LIST );

   DString dstrModPerm;
   if( iItemNumber )
   {
        getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransModPerm, dstrModPerm, false );
        dstrModPerm.upperCase();
   }

   if( !m_bCanReenter )
   {
      return;
   }
   m_bIsPending = true;
   m_rbHistory=1;
   UpdateData(FALSE);

   m_Fund.GetLBText(m_Fund.GetCurSel(),FundMode);

   m_Fund.SelectString(0,ALLFUND);
   m_Fund.EnableWindow(FALSE);
   m_Activity.EnableWindow(FALSE);

   OnSelendokCmbFund();

   // Enable/Disable Inventory Summary
   GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( !(DisableInvInfo == I_("Y")) && iItemNumber > 0 );

   GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( false );

   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->EnableWindow( iItemNumber > 0 );
   CString strFees; 
   strFees.LoadString(TXT_FEES);
   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->SetWindowText( strFees );
   
   GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( false );
   
   GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( false );

   GetDlgItem( IDC_BTN_REPRINT )->EnableWindow( false );	
     
   CString strModify;
   strModify.LoadString(TXT_MODIFY);
   GetDlgItem( IDC_BTN_MODIFY )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( strModify );
   GetDlgItem( IDC_BTN_MODIFY )->EnableWindow( iItemNumber > 0 && ( dstrModPerm != I_("0") &&  dstrModPerm != I_("3"))
      && InquiryOnly != Y );

   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( iItemNumber > 0 );

   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_LIST ) ); 
   
   GetDlgItem( IDC_BTN_TXN_CANCEL )->EnableWindow( false );

   GetDlgItem( IDC_BTN_DILUTION )->EnableWindow( false );
   GetDlgItem( IDC_BTN_INT_LINKS )->EnableWindow( false );
   GetDlgItem( IDC_BTN_SAVINGS_DIRECTIVE )->EnableWindow( false );
   GetDlgItem( IDC_BTN_PAYMENT_SEARCH )->EnableWindow( false );
   GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( true );
   GetDlgItem( IDC_BTN_PAYMENT_INFO )->EnableWindow( false );
   GetDlgItem( IDC_BTN_SHARELOT )->EnableWindow( false );
}

//************************************************************************************
BOOL TransactionHistoryDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   int col=0;

   BaseMainDlg::OnInitDialog();

   if( ReqTransid == NULL_STRING )
   {
      cmAllActivities.LoadString(COL_TRANSACTIONS_ALLACTIVITY);
      m_Activity.InsertString(col++,cmAllActivities);
   }

   cmTransactions.LoadString(COL_TRANSACTIONS_TRANS);
   m_Activity.InsertString(col++,cmTransactions);

   if( ReqTransid == NULL_STRING )
   {
      cmCashDividends.LoadString(COL_TRANSACTIONS_CASH_DIV);
      m_Activity.InsertString(col++,cmCashDividends);
   }

    if( PendingTrade.stripAll().upperCase() == I_("N"))
    {
        GetDlgItem(IDC_RB_PENDING)->EnableWindow(FALSE);
    }
    else if( PendingTrade.stripAll().upperCase() == I_("Y") )
    {
        GetDlgItem(IDC_RB_PENDING)->EnableWindow(true);
    }

   //m_Activity.SelectString(0,cmAllActivities);
   m_Activity.SetCurSel(0);

   if( ReqTransid != NULL_STRING )
   { // if it is from settlement scr
      GetDlgItem(IDC_RB_HISTORY)->EnableWindow(FALSE);
      GetDlgItem(IDC_RB_PENDING)->EnableWindow(FALSE);
    }

   ClearStaticText();

   DisplayTitle();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
//************************************************************************************

LRESULT TransactionHistoryDlg::OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier)
{
   TRACE_METHOD( CLASSNAME, I_( "OnListViewItemChanged" ) );

   if( ListIdentifier == IDC_LV_HISTORY && bPopulateDetails)
   {
      POSITION pos = NULL;
      int nCurrentSelection = -1;
      pos = m_lvReportView.GetFirstSelectedItemPosition();
      if( pos )
         nCurrentSelection = m_lvReportView.GetNextSelectedItem(pos);
      if( nCurrentSelection != (int)PreviousSelection )
         return(0);
      CWaitCursor wait;
      DString *strKey = (DString*)m_lvReportView.GetItemData( nCurrentSelection ) ;
      DString str;

      if( m_bIsPending )
      {
         SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING_DETAILS );
         GetDlgItem( IDC_BTN_SETTLEMENT )->ShowWindow( SW_SHOW );
         //GetDlgItem( IDC_BTN_SETTLEMENT )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_BTN_SETTLEMENT )->EnableWindow( false );
         GetDlgItem( IDC_BTN_MODIFY )->ShowWindow( SW_SHOW );

         getParent()->setCurrentListItem(this,IFASTBP_PROC::PENDING_LIST,*strKey);

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, PendingFundCode );
         PendingFundCode.stripAll().upperCase();
         FundCode=PendingFundCode;

         if(PendingFundCode.stripAll() == NULL_STRING || DisableInvInfo == I_("Y"))
         {
            GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( false );
         }
         else
         {
            GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( true );
         }
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, PendingClassCode );
         PendingClassCode.stripAll().upperCase();
         ClassCode=PendingClassCode;

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, PendingTradeDate );
         PendingTradeDate.stripAll();
         TradeDate=PendingTradeDate;

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, PendingTransNum );
         PendingTransNum.stripLeading('0');
         TransNum=PendingTransNum;

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, PendingTransType );
         PendingTransType.stripAll();
         TransType=PendingTransType;

         DString dstrModPerm;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransModPerm, dstrModPerm, false );
         dstrModPerm.upperCase();

         DString dstrTransType;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, dstrTransType, false );
         dstrTransType.stripAll().upperCase();

         DString dstrGrossNetMethod;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GrossNetMethod, dstrGrossNetMethod );
         dstrGrossNetMethod.strip().upperCase();

         bool bEnableModifyBtn = DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::ALLOW_TO_MODIFY_PENDING_TRXN);

         DString dstrIsCancelModSEGTradeAllowed;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::IsCancelModSEGTradeAllowed, dstrIsCancelModSEGTradeAllowed, false );
         dstrIsCancelModSEGTradeAllowed.strip().upperCase();

         bEnableModifyBtn = bEnableModifyBtn &&
                            (dstrModPerm == I_("Y") || (dstrModPerm != I_("0") && dstrModPerm != I_("3"))) &&
                            (InquiryOnly  != Y ) &&
                            dstrIsCancelModSEGTradeAllowed == I_("Y");

         DString dstrGuaranteesOverride; 
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GuaranteesOverride, dstrGuaranteesOverride, false );
         dstrGuaranteesOverride.strip().upperCase();

         GetDlgItem (IDC_BTN_MODIFY)->EnableWindow ( bEnableModifyBtn );
         //GetDlgItem (IDC_BTN_GUARANTEE_RULES)->EnableWindow (dstrGuaranteesOverride == I_("Y"));
         GetDlgItem (IDC_BTN_GUARANTEE_RULES)->EnableWindow (false);

         enableSettlementLocInstr (IFASTBP_PROC::PENDING_LIST, ifds::AccountTo);

         enableAuthorizationButton (IFASTBP_PROC::PENDING_LIST);

         enableBatchButton (IFASTBP_PROC::PENDING_LIST);

         enableMultiSettlInstrButton (IFASTBP_PROC::PENDING_LIST);
         enableRESPHistButton ();
		 enableRDSPNotionalActivityButton();

         DString dstrExternalLinksExist;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ExistExternalId, dstrExternalLinksExist, false );
         dstrExternalLinksExist.upperCase();

         GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( Y == dstrExternalLinksExist );

         // Enable/Disable Invest Info Button
         DString dstrInvestInfo;
         getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, AMT_INV_APPL, dstrInvestInfo, false);
         GetDlgItem(IDC_BTN_INVESTINFO)->EnableWindow(dstrInvestInfo == Y);

         DString payInstrExist;
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::PayInstructExists, payInstrExist, false );
         GetDlgItem( IDC_BTN_PAY_INSTRUCT )->EnableWindow (payInstrExist == Y);

         GetDlgItem( IDC_BTN_PAYMENT_SEARCH )->EnableWindow (false);
      }
      else
      {
         SetMessageStatusBar( TXT_LOAD_TRANSACTION_DETAILS );
         getParent()->setCurrentListItem(this,IFASTBP_PROC::TRANS_LIST,*strKey);
         GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( false );
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, str );
         stripComplete(str);
         TransId=str;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, FundCode );
         FundCode.stripAll().upperCase();

         if(FundCode == NULL_STRING || DisableInvInfo == I_("Y") )
            GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( false );
         else
            GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( true );

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, ClassCode );
         ClassCode.stripAll().upperCase();

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate, TradeDate );
         TradeDate.stripAll();

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, TransNum );
         TransNum.stripLeading('0');

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, TransType );
         TransType.stripAll().upperCase();

         DString strTransType;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, strTransType, false );
         strTransType.stripAll();

         DString strCancelled;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, strCancelled, false );
         strCancelled.strip().upperCase();

         DString strSettled;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Settled, strSettled, false );
         strSettled.stripAll();

         BOOL showSettlement = strSettled != Y && ReqTransid == NULL_STRING && InquiryOnly != Y && !m_bFromSettlementScreen;
         GetDlgItem( IDC_BTN_SETTLEMENT )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_BTN_SETTLEMENT )->EnableWindow( ( showSettlement == TRUE)?true:false );


         DString strReversal;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, strReversal, false );
         strReversal.strip().upperCase();

         DString strTaxType;
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, strTaxType, false );
         strTaxType.strip().upperCase();

         // check if transaction can be rebooked
         bool bCanRebook = strCancelled == Y       && strReversal == N &&
                           strTaxType   != I_("9") && strTaxType  != I_("M");
                           
         //check if user has creating permission for trade
         bool bTradePermit = hasCreatePermission( UAF::TRADING_EXCHANGE ) ||
                             hasCreatePermission( UAF::TRADING_PURCHASE ) ||
                             hasCreatePermission( UAF::TRADING_REDEMPTION );
         // if both satisfy, enable rebook
         bool bAllowTransType = DSTCommonFunctions::codeInList( strTransType, TRADETYPE::REBOOK_ALLOWABLE_TRANS_TYPES ) ||
                                DSTCommonFunctions::codeInList( strTransType, TRADETYPE::EXCHANGE_LIKE_2 );

         bool bEnableRebook = bCanRebook && bTradePermit && bAllowTransType;

         DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

         if(isTransactionCancelled())
         {
            CString strRebook;
            strRebook.LoadString(TXT_REBOOK);
            GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( strRebook );
            GetDlgItem( IDC_BTN_MODIFY )->EnableWindow( bEnableRebook ); 
         }
         else
         {
            bool bEnableRefund = bTradePermit;
            
            DString dstrRefundAllowed;
            if(pDSTCWorkSession)
            {
               pDSTCWorkSession->getOption( ifds::RefundAllowed, dstrRefundAllowed, getDataGroupId(), false );
               bEnableRefund = bEnableRefund && (dstrRefundAllowed == Y);
            }

            DString dstrIndc;
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Indc, dstrIndc );
            dstrIndc.strip();
            if(bEnableRefund && strTransType == I_("ED"))// && dstrIndc == I_("1"))
            {
               DString dstrHasRightToCancelFundLimitRule;
               getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, HAS_RIGHT_TO_CANCEL_FUND_LIMIT_RULE, dstrHasRightToCancelFundLimitRule);
               bEnableRefund = bEnableRefund && dstrHasRightToCancelFundLimitRule.strip() == Y;

               DString strSettled;
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Settled, strSettled, false );
               strSettled.stripAll();

               bEnableRefund = bEnableRefund && strSettled == Y;

               DString strReversal;
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, strReversal, false );
               strReversal.stripAll();

               bEnableRefund = bEnableRefund && strReversal != Y;

            }
            else 
            {
               bEnableRefund = false;
            }

            CString strRefund;
            strRefund.LoadString(TXT_REFUND);
            GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( strRefund );
            GetDlgItem( IDC_BTN_MODIFY )->EnableWindow(bEnableRefund); 
         }

         enableSettlementLocInstr( IFASTBP_PROC::TRANS_LIST, ifds::TfrAcct );

         enableAuthorizationButton (IFASTBP_PROC::TRANS_LIST);

         enableBatchButton (IFASTBP_PROC::TRANS_LIST);

         enableMultiSettlInstrButton (IFASTBP_PROC::TRANS_LIST);
         enableRESPHistButton ();
		 enableRDSPNotionalActivityButton();

         DString dstrExternalLinksExist;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ExistExternalId, dstrExternalLinksExist, false );
         dstrExternalLinksExist.upperCase();

         GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( Y == dstrExternalLinksExist );

         // Clawback Info Button
         DString dstrFundCategory, dstrFundConfirm;

         if (FundCode.strip() != I_( "CASH" ) )
         {
            getParent()->setCurrentListItem(this, IFASTBP_PROC::FUND_MASTER_LIST, FundCode);
            getParent()->getField(this, IFASTBP_PROC::FUND_MASTER_LIST, ifds::FundCategory, dstrFundCategory );
            // Reprint Button
            getParent()->getField(this, IFASTBP_PROC::FUND_MASTER_LIST, ifds::FundConfirm,  dstrFundConfirm, false );
         }

         bool enableClawbackBtn =  ( dstrFundCategory == CODE_FUND_CATEGORY_LSIF  &&
            ( strTransType == I_( "EO" ) ||
              strTransType == I_( "RR" ) ||
              strTransType == I_( "LR" ) ||
              strTransType == I_( "MF" ) ||
              strTransType == I_( "TO" ) || 
              // PW,AW,AF,AF91     
              DSTCommonFunctions::codeInList( strTransType, TRADETYPE::REDEMPTION_LIKE ) ) );

         GetDlgItem( IDC_BTN_CLAWBACK_INFO)->EnableWindow( enableClawbackBtn);

         // Enable/Disable Invest INFO Button
         DString dstrInvestInfoAppl;
         getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, AMT_INV_APPL, dstrInvestInfoAppl, false);
         GetDlgItem(IDC_BTN_INVESTINFO)->EnableWindow(dstrInvestInfoAppl == Y);

         DString dstrTxnCancel;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancellation, dstrTxnCancel );
         dstrTxnCancel.strip().upperCase();

         DString dstrIndc;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Indc, dstrIndc );
         dstrIndc.strip();

         // user has the permission to cancel transaction   
         bool bEnableCancel = hasUpdatePermission (UAF::CANCEL_SETTLE) && I_("N") != TxnCancel && dstrTxnCancel == Y;
// if it is a dividend, check  if user has the permission to cancel dividend
         if( bEnableCancel && 
             (dstrIndc == I_("1") || dstrIndc == I_("59")) && 
             strTransType == TRADETYPE::DIVIDEND) 
         {
            bEnableCancel = strSettled == Y && hasUpdatePermission (UAF::CANCEL_DIVIDEND);
         }

         if( strTransType == TRADETYPE::CAPITAL_GAIN_INCOME || strTransType == TRADETYPE::SUPPLEMENTAL_INCOME ) 
         {
            // on DSK doesn't allow user to cancel capital gain income and supplementary income due to
            // the functionality on these transactype will be done on other channel
            bEnableCancel = false;
         }


         if ((strTransType == TRADETYPE::DIVIDEND && FundCode.strip().upperCase() == I_( "CASH" )) ||
              strTransType == I_("EB") || strTransType == I_("PB"))
         {
            bEnableCancel = false;
         }

         DString dstrIsCancelModSEGTradeAllowed;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::IsCancelModSEGTradeAllowed, dstrIsCancelModSEGTradeAllowed, false );
         dstrIsCancelModSEGTradeAllowed.strip().upperCase();

         bEnableCancel = bEnableCancel && 
                        (dstrIsCancelModSEGTradeAllowed == I_("Y"));

         bool bIsGIFund = false;
         if( FundCode.strip().upperCase() == CASH || FundCode.strip().upperCase().empty() )
         {
            DString strTrfFund;
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrFund, strTrfFund );
            strTrfFund.strip().upperCase();
            
            FundMasterList *pFundMasterList; 

            if (pDSTCWorkSession->getMgmtCo().getFundMasterList (pFundMasterList) && 
               pFundMasterList)
            {
               bIsGIFund = pFundMasterList->isGIAFund (strTrfFund);
            }
         }

         bEnableCancel |= bIsGIFund;

         DString dstrGuaranteesOverride; 
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::GuaranteesOverride, dstrGuaranteesOverride, false );
         dstrGuaranteesOverride.strip().upperCase();

         DString dstrRefundTradeExists;
         getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, ifds::RefundTradeExists, dstrRefundTradeExists);
         bEnableCancel = bEnableCancel && !(dstrRefundTradeExists.strip() == Y);

         GetDlgItem (IDC_BTN_TXN_CANCEL)->EnableWindow (bEnableCancel);
         //GetDlgItem (IDC_BTN_GUARANTEE_RULES)->EnableWindow (dstrGuaranteesOverride == I_("Y"));
         GetDlgItem (IDC_BTN_GUARANTEE_RULES)->EnableWindow (false);

         // Reprint button
         DString dstrSystemOPCConfirmsBrokerScreen, 
         dstrAccountConfirmHold, 
         dstrGroupCode, 
         dstrGroupMstrSuppressConfirm;

         if (pDSTCWorkSession)
         {
            pDSTCWorkSession->getOption( ifds::OPCConfirmsBrokerScreen,
                                         dstrSystemOPCConfirmsBrokerScreen,
                                         getDataGroupId(), 
                                         false );

            // Check Account 
            MFAccount *pMFAccount = NULL;
            if ( 0 != AccountNum.stripAll().length() &&
                 pDSTCWorkSession->getMFAccount( getDataGroupId(),
                                                 AccountNum, 
                                                 pMFAccount ) <= WARNING &&
                 NULL != pMFAccount ) 
            {
               pMFAccount->getField( ifds::HoldMail,  dstrAccountConfirmHold, getDataGroupId() );
               pMFAccount->getField( ifds::AcctGroup, dstrGroupCode,          getDataGroupId() );
            }

            if ( !dstrGroupCode.strip().empty() )
            {
               GroupList *pGroupList = NULL;
               if ( pDSTCWorkSession->getMgmtCo().getGroupList( pGroupList ) &&
                    NULL != pGroupList )
               {
                  pGroupList->getField( dstrGroupCode, 
                                        ifds::SuppConfirm, 
                                        dstrGroupMstrSuppressConfirm,
                                        getDataGroupId() );
               }
            }
         }

         dstrSystemOPCConfirmsBrokerScreen.strip().upperCase();
         dstrAccountConfirmHold.strip().upperCase();
         dstrGroupMstrSuppressConfirm.strip().upperCase();
         dstrFundConfirm.strip().upperCase();

         bool bEnableConfirmReprint =  ( I_( "N" ) != Reprint                            &&
                                         I_( "Y" ) == dstrSystemOPCConfirmsBrokerScreen  &&
                                         I_( "Y" ) == dstrFundConfirm                    &&
                                         I_( "N" ) == dstrGroupMstrSuppressConfirm       &&
                                         I_( "N" ) == dstrAccountConfirmHold );

         GetDlgItem( IDC_BTN_REPRINT )->EnableWindow( bEnableConfirmReprint );

         // eusd
         DString eusdParticip;
         bool bEnableSavingsDirectiveBtn = false;
         DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
         pdstcWorkSession->getOption( ifds::EUSDParticip, eusdParticip, getParent()->getDataGroupId(), false );

         bEnableSavingsDirectiveBtn = eusdParticip == I_("Y") &&
                                      strCancelled == I_("N") &&
                                      strReversal  == I_("N") &&
                                      (    DSTCommonFunctions::codeInList( strTransType, TRADETYPE::PURCHASE_LIKE ) // ED,RC - purchase, reinvest purchase
                                        || DSTCommonFunctions::codeInList( strTransType, TRADETYPE::TRANSFER_IN   ) // TI;
                                        || DSTCommonFunctions::codeInList( strTransType, TRADETYPE::TRANSFER_IN_2 ) // TI04,TI08;
                                        || DSTCommonFunctions::codeInList( strTransType, TRADETYPE::EXCHANGE_IN   ) // EI;
                                        || DSTCommonFunctions::codeInList( strTransType, TRADETYPE::DIVIDEND      ) // ID;
                                      );

         GetDlgItem( IDC_BTN_SAVINGS_DIRECTIVE )->EnableWindow( bEnableSavingsDirectiveBtn) ;	

         GetDlgItem( IDC_BTN_DILUTION )->EnableWindow( true );

         DString payInstrExist;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::PayInstructExists, payInstrExist, false );
         GetDlgItem( IDC_BTN_PAY_INSTRUCT )->EnableWindow( payInstrExist == Y);

         DString payReconExist;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::PayReconExists, payReconExist, false );
         DString dstrMarket = DSTCommonFunctions::getMarket();
         GetDlgItem (IDC_BTN_PAYMENT_SEARCH)->EnableWindow ( CallFrom != I_("BrowserLaunch") && 
                                                             hasReadPermission (UAF::PAYMENT_SEARCH) && 
                                                             payReconExist == Y && 
                                                             dstrMarket != MARKET_IDS::CANADA );
         enablePaymentButton(IFASTBP_PROC::TRANS_LIST);
         enableShareLotButton();
      }

      PopulateDetails();
      SetMessageStatusBar(NULL_STRING);

      // Update AWD Button
      DString dstrNetworkID;
      getParent()->getField( this, m_bIsPending ? IFASTBP_PROC::PENDING_LIST : IFASTBP_PROC::TRANS_LIST, 
         ifds::NetworkID, dstrNetworkID, false );
      GetDlgItem( IDC_BTN_AWD )->EnableWindow( dstrNetworkID == I_("AWD") );

   }
   return(0);
}

//************************************************************************************
SEVERITY TransactionHistoryDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;

   DString dstrTemp;

   getParameter( pACCOUNTNUM, AccountNum );
   getParameter( pTRANSID, TransId );
   getParameter( pSHAREHOLDERNUM, ShareholderNum );
   getParameter( pFUNDCODE, FundCode ); 
   OrgFund = FundCode;
   getParameter( pCLASSCODE, ClassCode ); 
   OrgClass= ClassCode; 
   getParameter( pNUMENTRY, NumEntry );
   getParameter( pALLFUND, AllFundMode );
   getParameter( pTRANSTYPE, TransType);
   getParameter( pTRANSNUM, TransNum);
   getParameter( pTRADEDATE, TradeDate);
   getParameter( pENTITYID, EntityId ); 
   getParameter( pREQTRANSID, ReqTransid );
   getParameter( pINQUIRYONLY, InquiryOnly );
   getParameter( pPENDINGTRADE, PendingTrade);
   getParameter( DISABLEINVINFO, DisableInvInfo );
   getParameter( I_("DisableMsg"), DisableMsg );
   getParameter( I_("Reprint"), Reprint );
   getParameter( I_("TxnCancel"), TxnCancel );
   getParameter( I_("CalledFrom"), CallFrom );
   getParameter( FROM_SCR, FromScr );

   AccountNum.stripAll();
   TransId.stripAll();
   ShareholderNum.stripAll();
   FundCode.stripAll().upperCase();
   ClassCode.stripAll().upperCase();
   NumEntry.stripAll();
   AllFundMode.stripAll();
   TransType.stripAll();
   TransNum.stripAll().stripLeading('0');
   TradeDate.stripAll();
   CallFrom.stripAll();
   FromScr.stripAll ();

   // Pending
   getParameter( pPENDING, dstrTemp);
   dstrTemp.stripAll();
   m_bIsPending = (dstrTemp == Y);

   PendingFundCode  = FundCode;
   PendingClassCode = ClassCode;
   PendingTransType = TransType;
   PendingTransNum  = TransNum;
   PendingTradeDate = TradeDate;

   DString dstrFromSettlementScreen;
   getParameter( I_("FromSettlementScreen"), dstrFromSettlementScreen);
   m_bFromSettlementScreen = dstrFromSettlementScreen == I_("Y");
   sevRtn = NO_CONDITION;

   return(sevRtn);
}

//************************************************************************************
void TransactionHistoryDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));

   m_Activity.EnableWindow( m_bIsPending ? FALSE : TRUE );

   PopulateFundCom();

   OnSelendokCmbFund();

   int nCmdShow = SW_SHOW;
   DString dstrMarket = DSTCommonFunctions::getMarket();
   if( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG )
   {
      nCmdShow = SW_SHOW;
   }
   else if( dstrMarket == MARKET_IDS::JAPAN )
   {
      nCmdShow = SW_HIDE;
   }

   GetDlgItem( IDC_LBL_FUND_NUMBER )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_FUND_NUMBER )->ShowWindow( nCmdShow );
/**
   GetDlgItem( IDC_LBL_SETTLE_BATCH_NBR )->ShowWindow( bShow );
   GetDlgItem( IDC_TXT_SETTLE_BATCH )->ShowWindow( bShow );

   GetDlgItem( IDC_LBL_BROKER )->ShowWindow( bShow );
   GetDlgItem( IDC_LBL_BRANCH )->ShowWindow( bShow );
   GetDlgItem( IDC_LBL_SLSREP )->ShowWindow( bShow );

   GetDlgItem( IDC_EDIT_BROKER )->ShowWindow( bShow );
   GetDlgItem( IDC_EDIT_BRANCH )->ShowWindow( bShow );
   GetDlgItem( IDC_EDIT_SLSREP )->ShowWindow( bShow );

   GetDlgItem( IDC_LBL_REMARK )->ShowWindow( bShow );
   GetDlgItem( IDC_EDT_REMARK )->ShowWindow( bShow );
*/

   // Set AWD Button
   DString  dstrUsingAwd;
   getGlobal( USER_GLOBAL, ifds::Using_AWD, dstrUsingAwd );
   if (dstrUsingAwd == I_("1")) {
      m_AwdActive = AWD_SESSION;
   } else if(((CDSTCView*)GetMainView())->isWorkAgentRunning()) {
      m_AwdActive = AWD_PORTAL;
   }

   int iItemNumber = 0;
   CString cstrDeductDetlFee, cstrModifyRebook; 

   GetDlgItem( IDC_BTN_DILUTION )->EnableWindow( false );


   if (m_bIsPending)
   {            
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_LIST );	
      cstrDeductDetlFee.LoadString(TXT_FEES);      	  
      cstrModifyRebook.LoadString(TXT_MODIFY);
      GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_LIST ) );
      GetDlgItem( IDC_BTN_TXN_CANCEL )->EnableWindow( false );
      GetDlgItem( IDC_BTN_INT_LINKS )->EnableWindow( false );     
   }
   else
   {
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::TRANS_LIST );
      cstrDeductDetlFee.LoadString(TXT_DEDUCTIONS); 
      cstrModifyRebook.LoadString(TXT_REBOOK);   
      GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::TRANS_LIST ) );
   }

   // Inventory Information Button
   GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( (DisableInvInfo == I_("Y")) && iItemNumber > 0 );

   GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( false );

   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->EnableWindow( iItemNumber > 0 );	
   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->SetWindowText( cstrDeductDetlFee );

   GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( false );

   GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( false );

   GetDlgItem( IDC_BTN_SETTLEMENT )->EnableWindow( false );

   GetDlgItem( IDC_BTN_REPRINT )->EnableWindow( false );
   
   GetDlgItem( IDC_BTN_MODIFY )->EnableWindow( iItemNumber > 0 );
   GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( cstrModifyRebook );
   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( iItemNumber > 0 );

   GetDlgItem( IDC_BTN_SAVINGS_DIRECTIVE )->EnableWindow( false );
   GetDlgItem( IDC_BTN_PAYMENT_INFO )->EnableWindow( false );
   GetDlgItem( IDC_BTN_SHARELOT )->EnableWindow( false );
}

//************************************************************************************
void TransactionHistoryDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   if( !m_bCanReenter )
   {
      return;
   }
   CWaitCursor wait;
   SetMessageStatusBar( m_bIsPending ? TXT_LOAD_TRANSACTION_PENDING : TXT_LOAD_TRANSACTION_HISTORY );
   getParent()->getData(this, NULL);

   PopulateMainList();
   SetMessageStatusBar(NULL_STRING);
}

//************************************************************************************
void TransactionHistoryDlg::DisplayTitle()
{

   DString dstrShrNum;
   getParent()->getField(this, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( AccountNum );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    AccountNum,
                                                                                                    dstrEntityName);

   SetShrAcctCaption(dstrShrNum, AccountNum, dstrEntityName);        
}

//************************************************************************************
void TransactionHistoryDlg::OnDblclkLvAttributes(NMHDR* pNMHDR, LRESULT* pResult) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvAttributes" ) );

   OnBtnBrowse();

   *pResult = 0;
}

//************************************************************************************
void TransactionHistoryDlg::getFundName(DString &FundCode,DString& out)
{
   TRACE_METHOD( CLASSNAME, I_("getFundName"));
   out = NULL_STRING;
   if( FundCode != CASH && !FundCode.empty() )
   {
      getParent()->setCurrentListItem( this, IFASTBP_PROC::FUND_MASTER_LIST, FundCode.upperCase() );
      getParent()->getField( this, IFASTBP_PROC::FUND_MASTER_LIST, ifds::ElongName1/*FUND_NAME*/, out );
      out.strip().upperCase();
   }
}

//************************************************************************************
void TransactionHistoryDlg::getFundCurrency(DString &FundCode,DString& ClassCode,DString& out)
{
   TRACE_METHOD( CLASSNAME, I_("getFundCurrency"));
   out = NULL_STRING;
   if( FundCode != CASH && !FundCode.empty() )
   {
      if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_DETAIL_LIST ) != SPACE ) //Adrian
      {
         getParent()->setField( this, BF::NullContainerId, FUND_CODE, FundCode);
         getParent()->setField( this, BF::NullContainerId, CLASS_CODE, ClassCode);
         getParent()->getField( this, BF::NullContainerId, FUND_CLASS_KEY, out);

         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUND_DETAIL_LIST, out.upperCase() );
         getParent()->getField( this, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::Currency, out );
         out.strip();
      }
   }
}

//************************************************************************************
void TransactionHistoryDlg::OnItemchangedLvAttributes(NMHDR* pNMHDR, LRESULT* pResult) 
{
   if( !m_bIgnore )
   {
      TRACE_METHOD( CLASSNAME, I_("OnItemchangedLvAttributes"));
      NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

      if( LVN_SELECTED )
      {
         POSITION pos = m_TransDetail.GetFirstSelectedItemPosition();

         if( pos != NULL )
         {
            long selid=m_TransDetail.GetItemData( m_TransDetail.GetNextSelectedItem( pos ) );
            CWnd *tmp=GetDlgItem(IDC_BTN_BROWSE);
            tmp->EnableWindow(WhichDlgShouldBeLaunched(selid) != -1);
         }
      }
   }

   *pResult = 0;
}

//************************************************************************************
void TransactionHistoryDlg::OnBtnBrowse() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBrowse" ) );

   CWaitCursor wait;
   int selectedIndex = m_TransDetail.GetNextSelection( );
   if( selectedIndex == -1 )
   {
      return;
   }

   int DlgSel=WhichDlgShouldBeLaunched(m_TransDetail.GetItemData(selectedIndex));

   SetMessageStatusBar( NULL_STRING );

   DString Para1,Para2,Para3;


   if( DlgSel == _MASTER_MENU )
   {
      executeCsiProcess( DcCsiProcesses::MASTER_MENU);      
      return;
   }

   if( DlgSel == _BROKER_INFORMATION )
   {
      if( m_bIsPending )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Broker, Para1 );
         Para1.stripAll();
      }
      else
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::BrokerCode, Para1 );
         Para1.stripAll();
      }
      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      executeCsiProcess( DcCsiProcesses::BROKER_INFORMATION);     
      return;
   }

   if( DlgSel == _BRANCH_INFORMATION )
   {
      if( m_bIsPending )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Broker, Para1 );
         Para1.stripAll();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Branch, Para2 );
         Para2.stripAll();
      }
      else
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::BrokerCode, Para1 );
         Para1.stripAll();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::BranchCode, Para2 );
         Para2.stripAll();
      }
      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      setCsiParameter( DcCsiParameters::BRANCH_NUMBER, DStringA(Para2) );
      executeCsiProcess( DcCsiProcesses::BRANCH_INFORMATION );    
      return;
   }

   if( DlgSel == _TRANSACTION_PROCESSING_MENU )
   {
      executeCsiProcess( DcCsiProcesses::TRANSACTION_PROCESSING_MENU );    
      return;
   }

	if( DlgSel == _BATCH_ORDER_ENTRY )
   {
      executeCsiProcess( DcCsiProcesses::PATCH_ORDER_ENTRY_INFO );    
      return;
   }
   if( DlgSel == _ORDERS_PROCESSED )
   {
      executeCsiProcess( DcCsiProcesses::ORDERS_PROCESSED );      
      return;
   }

   if( DlgSel == _SETTLEMENTS )
   {
      executeCsiProcess( DcCsiProcesses::SETTLEMENTS );        
      return;
   }

   if( DlgSel == _SALES_REP_INFORMATION )
   {
      if( m_bIsPending )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Broker, Para1 );
         Para1.stripAll();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Branch, Para2 );
         Para2.stripAll();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::SlsrepCode, Para3 );
         Para3.stripAll();
      }
      else
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::BrokerCode, Para1 );
         Para1.stripAll();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::BranchCode, Para2 );
         Para2.stripAll();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SalesRepCode, Para3 );
         Para3.stripAll();
      }

      setCsiParameter( DcCsiParameters::BROKER_NUMBER, DStringA(Para1) );
      setCsiParameter( DcCsiParameters::BRANCH_NUMBER, DStringA(Para2) );
      setCsiParameter( DcCsiParameters::SALES_REP_NUMBER, DStringA(Para3) );
      executeCsiProcess( DcCsiProcesses::SALES_REP_INFORMATION );       
      return;
   }

   if( DlgSel == DSC_REDEMP_ACCESS.getId() )
   {
      setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(AccountNum));
      setCsiParameter( DcCsiParameters::FUND, DStringA(FundCode) );
      setCsiParameter( DcCsiParameters::CLASS, DStringA(ClassCode) );
      executeCsiProcess( DcCsiProcesses::REDEMPTION_DETAIL );  
      return;
   }

   if( DlgSel == _AWD_HISTORY )
   {
      OnBtnAwd();
      return;
   }
   if( DlgSel == _SOURCE_OF_FUNDS_CHECKED )
   {
      OnDblClickedSourceOfFundsChecked();
      return;
   }
   switch( DlgSel )
   {
      case -1:
         break;

      default:  // launch dlg
         try
         {
            //if( DlgSel == 7) goto A;//TEMPORARY
            E_COMMANDRETURN eRtn;
            bool bModal = isModal();   
						bModal = (DlgSel == 8 || DlgSel == 18 )? true:bModal; //8 :Bank

            SetMessageStatusBar( TXT_LOADING_GUI );
            setParameter(pINQUIRYONLY, InquiryOnly);
            eRtn = invokeCommand( getParent(),szCmd[DlgSel], procType, bModal, NULL );
            SetMessageStatusBar( NULL_STRING );

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
         //A: break;//TEMPORARY
   }
}

//************************************************************************************
void TransactionHistoryDlg::OnSelendokCmbFund() 
{
   TRACE_METHOD( CLASSNAME, I_("OnSelendokCmbFund"));

   if( !m_bCanReenter )
   {
      return;
   }

   DisplayTitle();   

   if (!isSelectionSpecified())
      m_bCanReenter = false;


   CWaitCursor wait;

   CString tmp;

   if( !m_bFromRefresh )
   {
      int index=m_Fund.GetCurSel();
      if( index == -1 )
      {
         index = 0;
      }
      m_Fund.GetLBText(index,tmp);
      getFunandClass(tmp, FundCode,ClassCode);
   }

   setParameter( pACCOUNTNUM, AccountNum );
   if(FundCode == OrgFund && ClassCode == OrgClass )
   {
		setParameter( pTRANSID, TransId );
   }
   else
   {
		setParameter( pTRANSID, NULL_STRING );
   }
   setParameter( pSHAREHOLDERNUM, ShareholderNum );
   NumEntry=I_("0");
   setParameter( pNUMENTRY, NumEntry ); 

   setParameter( pPENDING, m_bIsPending ? Y : N);
   setParameter( pENTITYID, EntityId ); 
   setParameter( pREQTRANSID, ReqTransid ); 
   setParameter( pALLFUND, ReqTransid != NULL_STRING? N : AllFundMode );      
   CString cmAllActivities;
   cmAllActivities.LoadString(COL_TRANSACTIONS_ALLACTIVITY);
   m_Activity.SelectString(0,cmAllActivities);

   if( m_bIsPending )
   {
      SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );
      setParameter( pFUNDCODE, PendingFundCode ); 
      setParameter( pCLASSCODE, PendingClassCode ); 
      setParameter( pTRANSTYPE, PendingTransType);
      setParameter( pTRANSNUM, PendingTransNum);
      setParameter( pTRADEDATE, PendingTradeDate);
      m_rbHistory=1;
      m_Fund.SelectString(0,ALLFUND);
      m_Fund.EnableWindow(FALSE);
      m_Activity.EnableWindow(FALSE);
   }
   else
   {
      SetMessageStatusBar( TXT_LOAD_TRANSACTION_HISTORY );
      setParameter( pFUNDCODE, FundCode ); 
      setParameter( pCLASSCODE, ClassCode ); 
      setParameter( pTRANSTYPE, TransType);	  
      //setParameter( pTRANSNUM, TransNum);
      setParameter( pTRADEDATE, TradeDate);
      m_rbHistory=0;
      m_Fund.EnableWindow(TRUE);
      makeFundClassString(FundCode, ClassCode, FundMode);
      if( AllFundMode == Y )
         m_Fund.SelectString(0,ALLFUND);
      else
         m_Fund.SelectString(0,FundMode);
      m_Activity.EnableWindow(TRUE);
   }
   UpdateData(FALSE);

   m_lvReportView.DeleteAllItems();
   m_TransDetail.DeleteAllItems();

   ClearStaticText();


   SetHeading();
   if( !m_bFromRefresh || m_bFromSettlement )
   {
      getParent()->performSearch( NULL, BF::NullContainerId, SEARCH_START); 
		m_bFromSettlement = false;
   }
   else
   {
      m_bFromRefresh = false;// preventing re-performsearch
   }

   PopulateMainList();
   SetMessageStatusBar(NULL_STRING);
   UpdateData(FALSE);

// m_Fund.SetFocus();

   PostMessage(UM_CAN_REENTER);
}

//************************************************************************************
void TransactionHistoryDlg::PopulateFundCom()
{
   TRACE_METHOD( CLASSNAME, I_("PopulateFundCom"));
   m_Fund.ResetContent();

   CString tmp;
   if( ReqTransid == NULL_STRING )
   {
      m_Fund.InsertString(-1,ALLFUND);

      DString str,str1;

      const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_LIST ));

      if( (*ty) != NULL_STRING )
      {
         do
         {
            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxFundCode/*FUND_CODE*/, str );
            str.stripAll().upperCase();
            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxClassCode/*FUND_CLASS*/, str1 );
            str1.stripAll().upperCase();
            makeFundClassString(str,str1,tmp);
            m_Fund.InsertString(-1,tmp);
         }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_LIST ))) != NULL_STRING );
      }
   }
   else
   { // if from settlement scr
      makeFundClassString(FundCode, ClassCode, tmp);
      m_Fund.InsertString(-1,tmp);
   }

   if( FundCode.empty() || AllFundMode == Y )
   {
      m_Fund.SelectString(0, ALLFUND);
   }
   else
   {
      makeFundClassString(FundCode, ClassCode, tmp);
      m_Fund.SelectString(0, tmp);
   }
}

//************************************************************************************
void TransactionHistoryDlg::getFunandClass(CString& src, DString& fundCode, DString& fundClass)
{
   if( src.CompareNoCase(ALLFUND) == 0 )
   {
      AllFundMode = Y;
      fundCode = NULL_STRING;
      fundClass = NULL_STRING;
      return;
   }

   int count = src.Find(SPACE);
   CString tmp = src.Left(count);

   fundCode = tmp.GetBuffer(0);
   tmp.ReleaseBuffer(-1);
   tmp=src.Right(src.GetLength()-count-1);
   fundClass=tmp.GetBuffer(0);
   tmp.ReleaseBuffer(-1);

   AllFundMode=N;
}

//************************************************************************************
void TransactionHistoryDlg::makeFundClassString(DString &fundCode, DString &Class, CString& out)
{
   out=ALLFUND;
   fundCode.stripAll();
   Class.stripAll();
   if( fundCode != M1 )
   {
      out=fundCode.c_str();
      out+=SPACE;
      out+=Class.c_str();
   }
}

//************************************************************************************
bool TransactionHistoryDlg::IsAllFundMode()
{
   CString tmp;
   m_Fund.GetLBText(m_Fund.GetCurSel(),tmp);
   return(tmp.CompareNoCase(ALLFUND)==0);
}

//************************************************************************************
void TransactionHistoryDlg::PopulateMainList()
{
   CWaitCursor wait;

   UpdateData();

   if( m_bIsPending )
   {
      PopulatePendingList();
   }
   else
   {
      PopulateTransList();
   }

   if( m_lvReportView.GetItemCount() > 0 )
   {
      m_lvReportView.SetFocus();
   }
   else
   {
      // Disable Inventory Summary
      GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( false );

      // Disable Invest Info Button
      GetDlgItem( IDC_BTN_INVESTINFO )->EnableWindow( false );
   }
}

//Sorting the pending trade list, 
//TransNum Desc, TradeDate Desc.
bool TransactionHistoryDlg::DateMap_Compare::operator()
( const DString& Key1,
  const DString& Key2 ) const
{  
   DString Date1 = Key1;
   DString Date2 = Key2;   

   int pos1 = Key1.find(',');
   int pos2 = Key2.find(',');

   DString TranNum1 = Key1.substr(0, pos1);
   DString TranNum2 = Key2.substr(0, pos2);

   if( TranNum1 != TranNum2 ) 
   {
	   return (TranNum1 < TranNum2)? false:true;
   }

   DSTCommonFunctions::DATE_ORDER order = DSTCommonFunctions::CompareDates( Date1.right(8), Date2.right(8));
   if( order == DSTCommonFunctions::FIRST_EARLIER )   
   {
      return(false);
   }

   return(true);
}

//************************************************************************************
void TransactionHistoryDlg::PopulatePendingList()
{
   m_lvReportView.DeleteAllItems();
   m_TransDetail.DeleteAllItems();

   DString str, fundto;
   DString _FundCode,_ClassCode,_TransType,_TransNum,_TradeDate;

   int index,col,highlight=0;

   bool bItemNotFound = true;
   //Sorting start   
   //Prepare date, key map;
   DateSortingMap.clear();
   const DString *Key=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::PENDING_LIST ));
   do
   {
       getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, _TradeDate );
       _TradeDate.stripAll();
       getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, _TransNum );
       _TransNum.stripAll();
       str = _TransNum +I_(",") + _TradeDate;
       if( (*Key) != NULL_STRING )
       {
            DateSortingMap.insert( std::map < DString, DString >::value_type(str, *Key ) );
       }
   }while( *(Key=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::PENDING_LIST ))) != NULL_STRING );

   getParent()->setField( this, CallPendigTradeDetails, I_("N") );
   //Iterator the sorted map
   for ( DateSortingIter = DateSortingMap.begin(); DateSortingIter != DateSortingMap.end(); DateSortingIter++ )
   {
       const DString *ty = &((*DateSortingIter).second); 
       getParent()->setCurrentListItem(this,IFASTBP_PROC::PENDING_LIST,*ty);
       //out put data
      col=0;

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, _TransType );
      _TransType.stripAll();

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, _FundCode );
      _FundCode.stripAll().upperCase();

      if( AreThereAllocationInThisPending() && _FundCode.empty() )
      {
         CString tmp;
         tmp.LoadString(TXT_SEE_ALLOCATION);
         index=m_lvReportView.InsertItem(99999,tmp);// column 1
      }
      else
      {
         index = m_lvReportView.InsertItem(99999,_FundCode.c_str());// column 1
      }

      m_lvReportView.SetItemData(index,(DWORD)ty);

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, _ClassCode );
      _ClassCode.stripAll().upperCase();
      m_lvReportView.SetItemText(index,++col,_ClassCode.c_str());

      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      {
         DString dstrFundNumber;
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
         dstWorkSession->GetFundNumber( _FundCode, _ClassCode, dstrFundNumber );
         m_lvReportView.SetItemText(index,++col,dstrFundNumber.c_str());
      }

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, _TradeDate );
      _TradeDate.stripAll();
      m_lvReportView.SetItemText(index,++col,_TradeDate.c_str());

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, _TransNum );
      _TransNum.stripAll().stripLeading('0');
//       m_lvReportView.SetItemText(index,++col,_TransNum.c_str());

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, str, true );
      str.strip();
      m_lvReportView.SetItemText(index,++col,str.c_str());

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::AmountType, str, true );
      str.strip();
      m_lvReportView.SetItemText(index,++col,str.c_str());

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Amount, str );
      str.stripAll().stripLeading('0');
      PrefixWithZero( str );
      m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::Amount);

      // gross/net will always be displayed
      str = I_("");

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GrossNetMethod, str );

      if (str == I_(""))
      {
          getParent()->getParameter( pGROSSNETMETHOD ,str );
      }

      str.stripAll();
      m_lvReportView.SetItemText(index,++col,str.c_str());

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::WireOrdNum, str );
      str.stripAll().stripLeading('0');;
      m_lvReportView.SetItemText(index,++col,str.c_str());

      if( HighlightThisPending(AccountNum, _FundCode, _ClassCode,
                               _TransType, _TransNum, _TradeDate) )
      {
         bItemNotFound = false;
         highlight=index;
      }

   }
   getParent()->setField( this, CallPendigTradeDetails, I_("Y") );
   //DateSortingMap.clear();
   //end of the sorting
/*
   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::PENDING_LIST ));

   if( (*ty) != NULL_STRING )
   {
      do
      {
         col=0;

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, _TransType );
         _TransType.stripAll();

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, _FundCode );
         _FundCode.stripAll().upperCase();

         if( AreThereAllocationInThisPending() && _FundCode.empty() )
         {
            CString tmp;
            tmp.LoadString(TXT_SEE_ALLOCATION);
            index=m_lvReportView.InsertItem(99999,tmp);// column 1
         }
         else
         {
            index = m_lvReportView.InsertItem(99999,_FundCode.c_str());// column 1
         }

         m_lvReportView.SetItemData(index,(DWORD)ty);

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, _ClassCode );
         _ClassCode.stripAll().upperCase();
         m_lvReportView.SetItemText(index,++col,_ClassCode.c_str());

         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         {
            DString dstrFundNumber;
            DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
            dstWorkSession->GetFundNumber( _FundCode, _ClassCode, dstrFundNumber );
            m_lvReportView.SetItemText(index,++col,dstrFundNumber.c_str());
         }

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, _TradeDate );
         _TradeDate.stripAll();
         m_lvReportView.SetItemText(index,++col,_TradeDate.c_str());

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, _TransNum );
         _TransNum.stripAll().stripLeading('0');
//       m_lvReportView.SetItemText(index,++col,_TransNum.c_str());

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, str, true );
         str.strip();
         m_lvReportView.SetItemText(index,++col,str.c_str());

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::AmountType, str, true );
         str.strip();
         m_lvReportView.SetItemText(index,++col,str.c_str());

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Amount, str );
         str.stripAll().stripLeading('0');
         PrefixWithZero( str );
         m_lvReportView.SetItemText(index,++col,str.c_str());

         // gross/net will always be displayed
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GrossOrNet, str );
         str.stripAll();
         m_lvReportView.SetItemText(index,++col,str.c_str());

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::WireOrdNum, str );
         str.stripAll().stripLeading('0');;
         m_lvReportView.SetItemText(index,++col,str.c_str());

         if( HighlightThisPending(AccountNum, _FundCode, _ClassCode,
                                  _TransType, _TransNum, _TradeDate) )
         {
            bItemNotFound = false;
            highlight=index;
         }

      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::PENDING_LIST ))) != NULL_STRING );
*/


    if( m_lvReportView.GetItemCount() > 0 )
    {
        bool MoreRecordsExist=getParent()->doMoreRecordsExist( this , BF::NullContainerId );
        CWnd *MoreBut=GetDlgItem(IDC_BTN_MORE);

        if( bItemNotFound )
        {
            //m_lvReportView.SetSelection(0);
            if( MoreRecordsExist )
            {
                PostMessage(WM_COMMAND,IDC_BTN_MORE);
            }
            else
            {
                if( !m_bMessageDisplayed )
                {
                    //MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("PopulateTransList") );
                    //DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_INVALID_FIELD_ENTRY );
                    m_bMessageDisplayed = true;
                }
            }
            if ( !isSelectionSpecified() || !MoreRecordsExist)
            {
                bPopulateDetails = true;
                m_lvReportView.SetSelection(0);
            }
            else 
                bPopulateDetails = false;
        }
        else
        {
            bPopulateDetails = true;
            m_lvReportView.SetSelection(highlight);
        }


        MoreBut->EnableWindow(MoreRecordsExist);
        if( !MoreRecordsExist )
        {
            m_lvReportView.SetFocus();
        }
    }
}

//************************************************************************************
bool TransactionHistoryDlg::HighlightThisPending(DString &_AccountNum, DString &_FundCode, DString &_ClassCode, DString &_TransType, DString &_TransNum, DString &_TradeDate)
{
   return(AccountNum==_AccountNum) && (PendingFundCode==_FundCode) && (PendingClassCode==_ClassCode) && 
   (PendingTransType==_TransType) && (PendingTransNum==_TransNum) && (PendingTradeDate==_TradeDate);
}

//************************************************************************************
void TransactionHistoryDlg::SetTransHeading()
{
   CString tmp, tmp2;
   int col=0;
   tmp.LoadString(COL_TRANSACTIONS_FUNDNAME);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_CLASS);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      tmp.LoadString(COL_TRANSACTIONS_NUMBER);
      m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   }

   tmp.LoadString(COL_TRANSACTIONS_TRADEDATE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_SETTLEDATE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_TRANSTYPE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_NAV);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,100);
   tmp.LoadString(COL_TRANSACTIONS_UNITS);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,100);
   tmp.LoadString(COL_TRANSACTIONS_GROSSAMOUNT);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,100);
   tmp.LoadString(COL_TRANSACTIONS_BALANCE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,136);
   tmp.LoadString( TXT_CANCELED );
   tmp += I_("/");
   tmp2.LoadString( TXT_TRANS_REVERSAL );
   tmp += tmp2;
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);

   m_lvReportView.LoadSettings(CLASSNAME,LV_TRANS_HISTORY);

   col=0;
   tmp.LoadString(COL_TRANSACTIONS_ATTRIBUTES);
   m_TransDetail.InsertColumn(col++,tmp,LVCFMT_LEFT,120);
   tmp.LoadString(COL_TRANSACTIONS_VALUE);
   m_TransDetail.InsertColumn(col++,tmp,LVCFMT_LEFT,180);
   m_TransDetail.LoadSettings(CLASSNAME,LV_TRANS_DETAILS);
}

//************************************************************************************
void TransactionHistoryDlg::SetPendingHeading()
{
   CString tmp;
   int col=0;

   tmp.LoadString(COL_TRANSACTIONS_FUNDNAME);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_CLASS);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      tmp.LoadString(COL_TRANSACTIONS_NUMBER);
      m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,100); //david Jun 27
   }

   tmp.LoadString(COL_TRANSACTIONS_TRADEDATE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_TRANSTYPE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);

   tmp.LoadString(COL_TRANSACTIONS_AMOUNT_TYPE);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTION_AMOUNT);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_RIGHT,100);
   tmp.LoadString(COL_TRANSACTION_GROSS_NET);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);
   tmp.LoadString(COL_TRANSACTIONS_WIRE_ORD_NBR);
   m_lvReportView.InsertColumn(col++,tmp,LVCFMT_LEFT,100);


   m_lvReportView.LoadSettings(CLASSNAME,LV_PENDING);

   col=0;
   tmp.LoadString(COL_TRANSACTIONS_ATTRIBUTES);
   m_TransDetail.InsertColumn(col++,tmp,LVCFMT_LEFT,120);
   tmp.LoadString(COL_TRANSACTIONS_VALUE);
   m_TransDetail.InsertColumn(col++,tmp,LVCFMT_LEFT,180);
   m_TransDetail.LoadSettings(CLASSNAME,LV_PENDING_DETAILS);
}

//************************************************************************************
void TransactionHistoryDlg::SetHeading()
{
   m_lvReportView.DeleteAllItems();
   m_lvReportView.DeleteAllColumns();
   m_TransDetail.DeleteAllItems();
   m_TransDetail.DeleteAllColumns();

   if( m_bIsPending )
      SetPendingHeading();
   else
      SetTransHeading();
}

//************************************************************************************
void TransactionHistoryDlg::SetTransStaticText()
{
   DString str,str1=NULL,tmp;
   CWnd *w=GetDlgItem(IDC_NET_AMT);
   w->ShowWindow(SW_SHOW);

// m_FundClass=str1.c_str();
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, str );
   str.stripAll().stripLeading('0');

   m_TransNbr=str.c_str();

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::PrevUnitBal, str );
   BFFieldId fieldId = ifds::PrevUnitBal;
   DisplayFormat( str, fieldId );
   m_PreBalance=str.stripAll().c_str();

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate, str);
   m_SettleDate=str.strip().c_str();

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::NetAmt, str);
   DisplayFormat( str, (BFFieldId)ifds::NetAmt );
   m_NetAmount=str.strip().c_str();
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderBatch, str);
   m_BatchNum=str.strip().c_str(); // it is batch num!
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleBatch, str);
   m_SettleBatchNum = str.strip().c_str();   // Settle Batch Number

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, str );
   str.stripAll().upperCase();
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, str1 );
   str1.stripAll().upperCase();

   if( str == CASH || str.empty() )
   {
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrFund, str );
      str.stripAll().upperCase();
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrClass, str1 );
      str1.stripAll().upperCase();
   }

   getFundName(str,tmp);
   m_FundLongName=tmp.c_str();
   getFundCurrency(str,str1,tmp);
   m_FundCurrency=tmp.c_str();

//baycom number
   DString dstrFundNumber;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, str );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, str1 );
   dstWorkSession->GetFundNumber( str, str1, dstrFundNumber );
   m_FundNumber = dstrFundNumber.c_str();

   DisplayCodeDesc01(IFASTBP_PROC::TRANS_LIST,ifds::BrokerCode,ifds::BrokerName,TXT_TRANS_BROKERCODE, str);
   m_BrokerCode=str.strip().c_str();
   DisplayCodeDesc01(IFASTBP_PROC::TRANS_LIST,ifds::BranchCode,ifds::BranchName,TXT_TRANS_BRANCHCODE, str);
   m_BranchCode=str.strip().c_str();
   DisplayCodeDesc01(IFASTBP_PROC::TRANS_LIST,ifds::SalesRepCode,ifds::SlsrepName,TXT_TRANS_SALESREPCODE, str);
   m_SlsrepCode=str.strip().c_str();


}

//************************************************************************************
void TransactionHistoryDlg::SetPendingStaticText()
{
   DString str,str1,tmp;

   CWnd *w=GetDlgItem(IDC_NET_AMT);
   w->ShowWindow(SW_HIDE);

   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, str );
   str.stripAll().stripLeading('0');
   m_TransNbr=str.c_str();

   m_PreBalance=NA;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::SettleDate, str);
   m_SettleDate=str.strip().c_str();

   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::SettleInDate, str);
   m_SettleInDate=str.strip().c_str();

   m_NetAmount=NULL_STRING;//str.strip().c_str();
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::BatchName, str);
   m_BatchNum=str.strip().c_str(); // it is batch num!

   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, str );
   str.stripAll().upperCase();
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, str1 );
   str1.stripAll().upperCase();

   if( str == CASH || str.empty() )
   {
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FundTo, str );
      str.stripAll().upperCase();
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ClassToCode, str1 );
      str1.stripAll().upperCase();
   }

   getFundName(str,tmp);
   m_FundLongName=tmp.c_str();
   getFundCurrency(str,str1,tmp);
   m_FundCurrency=tmp.c_str();

//baycom number
   DString dstrFundNumber;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );

   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, str );
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, str1 );
   dstWorkSession->GetFundNumber( str, str1, dstrFundNumber );
   m_FundNumber = dstrFundNumber.c_str();

   DisplayCodeDesc01(IFASTBP_PROC::PENDING_LIST,ifds::Broker,ifds::BrokerName,TXT_TRANS_BROKERCODE, str);
   m_BrokerCode=str.strip().c_str();
   DisplayCodeDesc01(IFASTBP_PROC::PENDING_LIST,ifds::Branch,ifds::BranchName,TXT_TRANS_BRANCHCODE, str);
   m_BranchCode=str.strip().c_str();
   DisplayCodeDesc01(IFASTBP_PROC::PENDING_LIST,ifds::SlsrepCode,ifds::SlsrepName,TXT_TRANS_SALESREPCODE, str);
   m_SlsrepCode=str.strip().c_str();

}

//************************************************************************************
void TransactionHistoryDlg::OnSelendokCmbActivity() 
{
   if( !m_bCanReenter )
   {
      return;
   }
   PopulateMainList();  
}

//************************************************************************************

int TransactionHistoryDlg::DisplayTransaction(const DString *ty)
{
   int index,col;
   DString str, fundcode;
   DString dstrSeqNum;
   DString dstrCancelled, dstrReversal, dstrSettled;

   col=0;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, fundcode );
   fundcode.stripAll().upperCase();

   index=m_lvReportView.InsertItem(99999,fundcode.c_str());// column 1

   m_lvReportView.SetItemData(index,(DWORD)ty);

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, str );
   str.stripAll().upperCase();
   m_lvReportView.SetItemText(index,++col,str.c_str());

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      DString dstrFundNumber;

      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
      dstWorkSession->GetFundNumber( fundcode, str, dstrFundNumber );

      m_lvReportView.SetItemText(index,++col,dstrFundNumber.c_str());
   }

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate, str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate, str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, str, true );
   str.stripLeading( I_(' ') );
   str.stripTrailing( I_(' ') );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::UnitPrice, str );// nav
   stripComplete( str );

   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::UnitPrice );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Units, str );
   stripComplete( str );
   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::Units );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::GrossAmt, str );
   stripComplete( str );
   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::Units );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Settled, dstrSettled, false );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SeqNum, dstrSeqNum, false );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, dstrCancelled, false );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, dstrReversal, false );
   dstrCancelled.stripAll().upperCase();
   dstrReversal.stripAll().upperCase();
   dstrSettled.stripAll();
   dstrSeqNum.stripAll().stripLeading('0');
   CString tmp;
   if( dstrSeqNum.empty() )
   {
      if( dstrCancelled == Y || dstrReversal == Y )
      {
         tmp.LoadString( TXT_CANCELED );
      }
      else if( dstrSettled == Y )
      {
         tmp.LoadString( TXT_SETTLED );
      }
      else
      {
         tmp.LoadString( TXT_UNSETTLED );
      }
      str = DString( tmp );
   }
   else
   {
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::UnitBalance, str );
   }
   stripComplete( str );
   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::UnitBalance );

   // Display Cancelled/Reversal value
   str = ( dstrCancelled == Y || dstrReversal == Y ) ? Y : N;
   ReplaceYandN( str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   return(index);
}

//************************************************************************************
int TransactionHistoryDlg::DisplayCashDiv(const DString *ty)
{
   int index,col;
   DString str,fundcode;

   col=0;

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrFund, fundcode );
   fundcode.stripAll().upperCase();

   index=m_lvReportView.InsertItem(99999,fundcode.c_str());// column 1
   m_lvReportView.SetItemData(index,(DWORD)ty);

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrClass, str );
   str.stripAll().upperCase();
   m_lvReportView.SetItemText(index,++col,str.c_str());

//   str = NULL_STRING;
//   m_lvReportView.SetItemText(index, ++col, str.c_str() );
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      DString dstrFundNumber;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
      dstWorkSession->GetFundNumber( fundcode, str, dstrFundNumber );
      m_lvReportView.SetItemText(index,++col,dstrFundNumber.c_str());
   }

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate, str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate, str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, str, true );
   str.strip(); //IN2458590_WO599611 - Automation script failing due to Desktop Trans type naming error

   m_lvReportView.SetItemText(index,++col,str.c_str());

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::UnitPrice, str );// nav
   stripComplete( str );

   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::UnitPrice );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Units, str );
   stripComplete( str );
   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::Units );

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::GrossAmt, str );
   stripComplete( str );
   m_lvReportView.doSetItemText(index,++col,str.c_str(), ifds::GrossAmt );

   CString tmp;
   tmp.LoadString(TXT_CASH);
   m_lvReportView.SetItemText(index,++col,tmp);

   // Display Cancelled/Reversal value
   DString dstrCancelled, dstrReversal;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, dstrCancelled, false );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, dstrReversal, false );
   dstrCancelled.stripAll().upperCase();
   dstrReversal.stripAll().upperCase();
   str = ( dstrCancelled == Y || dstrReversal == Y ) ? Y : N;
   ReplaceYandN( str );
   m_lvReportView.SetItemText(index,++col,str.c_str());

   return(index);
}

//************************************************************************************
void TransactionHistoryDlg::PopulateTransList()
{
   m_lvReportView.DeleteAllItems();
   m_TransDetail.DeleteAllItems();

   DString str, strfund, strclass;

   int index,col,highlight=0;

   bool bItemNotFound = true;

   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::TRANS_LIST ));

   if( (*ty) != NULL_STRING )
   {
      do
      {
         col=0;

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         strfund = str;
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, strclass );
         strclass.stripAll().upperCase();

         int act=GetActivity();
         index=-1;
         if( str == CASH )
         {
            if( act == 0 || act == 2 )
            {
               index = DisplayCashDiv(ty);
            }
         }
         else
         {
            if( act == 0 || act == 1 )
            {
               index = DisplayTransaction(ty);
            }
         }

         //if All fund mode select, fund class all should be empty out, no transId check needed.
         //if change fund on combo box, never be able to find matching transId between different fund 
         if( ( IsAllFundMode()|| 
                ( OrgFund != NULL_STRING && strfund != OrgFund ) ||
                ( OrgClass!= NULL_STRING && strclass != OrgClass )  
            ) &&
            CallFrom != I_( "TradeSearch" )
           )
         {
            bItemNotFound = false;
         }
         else if( index != -1 )
         {
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, str );
            stripComplete( str );
            if( TransId == str.stripAll() )
            {
               highlight=index;
               bItemNotFound = false;               
            }
         }
      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::TRANS_LIST ))) != NULL_STRING );

      if( m_lvReportView.GetItemCount() > 0 )
      {
//CP20030319         bool MoreRecordsExist=getParent()->doMoreRecordsExist( this , 1);
         // HACK:  What is the real value of the containerId supposed to be?  -1 I'll guess
         bool MoreRecordsExist=getParent()->doMoreRecordsExist( this , IFASTBP_PROC::TRANS_LIST );
         CWnd *MoreBut=GetDlgItem(IDC_BTN_MORE);
         if( bItemNotFound )
         {
            //m_lvReportView.SetSelection(0);
            if( MoreRecordsExist )
            {
               PostMessage(WM_COMMAND,IDC_BTN_MORE);
            }
            else
            {
               if( !m_bMessageDisplayed )
               {
                  //MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("PopulateTransList") );
                  //DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_INVALID_FIELD_ENTRY );
                  m_bMessageDisplayed = true;
               }
            }
            if ( !isSelectionSpecified() || !MoreRecordsExist)
            {
               bPopulateDetails = true;
               m_lvReportView.SetSelection(0);
            }
            else bPopulateDetails = false;
         }
         else
         {
            bPopulateDetails = true;
            m_lvReportView.SetSelection(highlight);
         }

         MoreBut->EnableWindow(MoreRecordsExist);
         if( !MoreRecordsExist )
         {
            m_lvReportView.SetFocus();
         }
      }
   }
}

//************************************************************************************
int TransactionHistoryDlg::GetActivity()
{
   CString tmp;
   m_Activity.GetLBText(m_Activity.GetCurSel(),tmp);

   if( tmp == cmTransactions )
   {
      return(1);
   }
   else
   {
      return( tmp == cmCashDividends ) ? 2 : 0;
   }
}

//************************************************************************************
void TransactionHistoryDlg::ClearStaticText()
{
   m_TransNbr=NULL_STRING;
   m_FundLongName=NULL_STRING;
   m_FundCurrency=NULL_STRING;
   m_PreBalance=NULL_STRING;
   m_NetAmount=NULL_STRING;
   m_SettleDate=NULL_STRING;
   m_BatchNum=NULL_STRING; 
   m_SettleBatchNum=NULL_STRING;
   m_FundNumber = NULL_STRING;
   m_BrokerCode=NULL_STRING;
   m_BranchCode=NULL_STRING;
   m_SlsrepCode=NULL_STRING;  

   UpdateData(FALSE);
}

//************************************************************************************
bool TransactionHistoryDlg::DisplayThisItem(DString& src, int ItemType)
{
   DString str;
   bool rtn = true;
   switch( ItemType )
   {
      case IS_TEXT:
         src.strip();
         if( src.empty() )
         {
            return(false);
         }
         break;

      case IS_NUMBER:
         src.stripAll();
         if( src.empty() )
         {
            src=I_("0");
         }
         break;

      case IS_INTEGER:
         src.stripAll();
         stripLeading(src,'0');
         if( src.empty() )
         {
            src = I_("0");
         }
         break;

      case IS_DATE:
         src.stripAll();
         str=src;
         if( str.stripAll('/') == NULL_STRING )
         {
            return(false);
         }
         break;

	  case IS_TIME_HHMMSS:
		 src.stripAll();
		 str=src;
		 if( str.stripAll(':').stripAll(' ') == NULL_STRING )
         {
            return(false);
         }
		 break;

      case ALWAYS_SHOW:
         break;
   }

   return(rtn);
}

//************************************************************************************
int TransactionHistoryDlg::WhichDlgShouldBeLaunched(long curSelItem)
{
   TRACE_METHOD( CLASSNAME, I_("WhichDlgShouldBeLaunched"));
   procType = PROC_NO_TYPE;

   if( m_bIsPending )
   {
      return(WhichDlgShouldBeLaunchedPending(curSelItem));
   }
   else
   {
      return(WhichDlgShouldBeLaunchedTrans(curSelItem));
   }
}

//************************************************************************************
int TransactionHistoryDlg::WhichDlgShouldBeLaunchedTrans(long curSelItem)
{
   DString str;

   SetMessageStatusBar( NULL_STRING );
   const BFFieldId curSelField( curSelItem );

   if( curSelField == ifds::UnitPrice )
   {
      SetMessageStatusBar( TXT_BROWSE_FUND_INFO );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, str );
      if( str!=CASH )
      {
         str.stripAll().upperCase();
         setParameter( FUNDCODEVALUE,         str); 
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, str );
         str.stripAll().upperCase();
         setParameter( CLASSCODEVALUE,    str); 
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate, str, false);
         setParameter( FROMDATEVALUE,         str); 
         setParameter( TODATEVALUE,        str); 
         return(5); //fund info
      }
      else
         return(-1);
   }

   // paytype code: 'E' EFT, 'S' System, 'M' Manual, 'X' Suppress
   if (curSelField == ifds::PayType2 || 
       curSelField == ifds::PayTypeDesc)
   {
      DString payType, 
         payMethod;

      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::PayType2, 
         payType, false);
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::PayMethod, 
         payMethod, false);
      
      payType.stripAll().upperCase();
      payMethod.strip().upperCase();

      if ((payMethod != CHEQUE && payType == I_("E"))  || 
          (payMethod != CHEQUE && payType == I_("D1")) || 
         payType == I_("I") || payType == I_("D") )
      {
         // bank
         SetMessageStatusBar (TXT_BROWSE_BANK);
         //current list key in the pending trade list

         DString listKey;

         listKey = 
            getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
         setParameter (MFCAN_IP_PARAM::LIST_KEY, listKey);
         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum);
         setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::TRANSACTION);
         return 8;
      }

      if (payType == I_("M") || payType == I_("S") || payType == I_("X") /*||
           ( str == I_("E") && strPayMethod.strip().upperCase() == CHEQUE)*///actually no cheque detail is created
        )
      { // cheque
         SetMessageStatusBar( TXT_BROWSE_CHEQUE );
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, str );
         stripComplete( payType );
         setParameter( pTRANSID, str ); 
         return(1);//cheque
      }
   }

   if( curSelField == ifds::Allocation )
   {
      SetMessageStatusBar(TXT_BROWSE_ALLOCATION);
      getParent()->setParameter(ALLOCATIONSPROC::ALLOCATION_TYPE, 
         ALLOCATIONSPROC::TRANSACTION_ONE_TIME);
      //caller
      setParameter(MFCAN_IP_PARAM::CALLER, ALLOCATIONSPROC::TRANS_HIST);
      //account num
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum); 
      //trans num
      setParameter(MFCAN_IP_PARAM::TRANS_NUM, TransNum); 
      //trade date
      getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, 
         ifds::TradeDate, str);
      str.strip();
      setParameter(MFCAN_IP_PARAM::TRADE_DATE, str); 
      //trans type
      getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, 
         ifds::TransType, str, false);
      str.stripAll();
      setParameter(MFCAN_IP_PARAM::TRANS_TYPE, str);
      //settle currency
      getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, 
         ifds::SettleCurrency, str);
      str.strip();
      setParameter(ALLOCATIONSPROC::SETTLE_CURRENCY, str); 
      //current list key in the pending trade list
      str = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
      setParameter(MFCAN_IP_PARAM::LIST_KEY, str);
      return 7; // allocation
   }

   if( curSelField == ifds::CertRequired )
   {
      DString str;
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, str );
      SetMessageStatusBar( TXT_BROWSE_CERTIFICATE );
      setParameter( INACCTNUM  , AccountNum ); 
      setParameter( INFUND  , str.strip()   );
      setParameter( INCERTNUM  , NULL_STRING );
      setParameter( INXREFNUM  , NULL_STRING );
      return(2); // certificate
   }

   if( curSelField == ifds::ConfIssued || curSelField == ifds::ConfirmReq )
   {// ||
//    curSelItem == DBR::OnStmt){
      if( hasReadPermission( UAF::ADDRESS_BOOK ) )
      {
         SetMessageStatusBar( TXT_BROWSE_ADDRESS_BOOK );
         setParameter( pACCOUNTNUM  , AccountNum );
         setParameter( pENTITYID, EntityId ); 
         return(6); //address book
      }
      else
      {
         return(-1); //disable access to the address book
      }

   }

   if( curSelField == ifds::OrderBatch  || 
       curSelField == ifds::OrderTrace  ||
       curSelField == ifds::OrderUser   ||
       curSelField == ifds::CancelBatch ||
       curSelField == ifds::CancelTrace ||
       curSelField == ifds::CancelUser  ||
       curSelField == ifds::SettleBatch ||
       curSelField == ifds::SettleUser  ||
       curSelField == ifds::SettleTrace )
   {
      SetMessageStatusBar( _T( "HLLAPI - Batch Order Entry menu item" ) );
      return( _BATCH_ORDER_ENTRY );
   }

   if( curSelField == ifds::BranchCode ||
       curSelField == ifds::BranchName )
   {
      SetMessageStatusBar( TXT_BROWSE_BRANCH_INFO );
      return(_BRANCH_INFORMATION);
   }

   if( curSelField == ifds::BrokerCode ||
       curSelField == ifds::BrokerName )
   {
      SetMessageStatusBar( TXT_BROWSE_BROKER_INFO );
      return(_BROKER_INFORMATION);
   }

   if( curSelField == ifds::SalesRepCode || // differ in trans and pending
       curSelField == ifds::SlsrepName )// ||
   //     curSelItem == DBR::SlsrepAltName)
   {
      SetMessageStatusBar( TXT_BROWSE_SELREP );
      return(_SALES_REP_INFORMATION);
   }

   if( curSelField == ifds::TfrAcct )
   {
//    return _TRANSACTION;
      DString dstTfrAcct, dstrTransferTransId, dstrTransType;
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, dstrTransType, false );
      dstrTransType.stripAll().upperCase();
      if( dstrTransType == TI || dstrTransType == TO || dstrTransType == TR )
      {

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrAcct, dstTfrAcct, false);
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransferTransId, dstrTransferTransId, false);
         setParameter( pACCOUNTNUM, dstTfrAcct);
         setParameter( pTRANSID, dstrTransferTransId );
         setParameter( pENTITYID, EntityId );
         return(12);
      }
      else
         return(-1);
   }

   if( curSelField == ifds::SplitComm )
   {
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SplitComm, str, false);
      if( str == Y )
      {
         DString dstrTransTypeDesc;

         getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, dstrTransTypeDesc, true);
         dstrTransTypeDesc.stripAll();
         str = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::TRANSACTION_HISTORY);
         setParameter(SPLITCOMM::ACCOUNT_NUM, AccountNum);
         setParameter(SPLITCOMM::MAIN_LIST_KEY, str);
         setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, dstrTransTypeDesc);
         setParameter(SPLITCOMM::TRANSACTION_NUMBER, TransNum);
         procType = PROC_SUPPORT;
         return(11);
      }
   }

   if( curSelField == DSC_REDEMP_ACCESS )
   {
      SetMessageStatusBar( TXT_LOAD_DSC_REDEMPTION );
      return(DSC_REDEMP_ACCESS.getId());
   }

   if( curSelField == ifds::ExtTransNum || curSelField == ifds::NetworkID )
   {
      return( _AWD_HISTORY );
   }
   
   if(curSelField == ifds::RedCode)
   {
      DString dstrDeathRedCode;
      DString dstrRedCode;
      DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      pdstcWorkSession->getOption ( ifds::DeathRedCode, dstrDeathRedCode, BF::HOST, false);
      getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, ifds::RedCode, dstrRedCode, false);
      if(DSTCommonFunctions::codeInList(dstrRedCode, dstrDeathRedCode))
      {
         DString transCurrentKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::TRANS_LIST);
         setParameter (MFCAN_IP_PARAM::CALLER, I_ ("TransHist"));
         setParameter(SPLITCOMM::ACCOUNT_NUM, AccountNum);
         setParameter (MFCAN_IP_PARAM::LIST_KEY, transCurrentKey);
         return( 18 );
      }
   }
   if( ifds::SourceofFundsChecked ==  curSelField )
   {
      SetMessageStatusBar(TXT_SOURCE_OF_FUNDS_CHECKED);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("SourceofFundsChecked"));
      setParameter(MFCAN_IP_PARAM::TRANS_NUM, TransNum);
      return (_SOURCE_OF_FUNDS_CHECKED);
   } 

   return(-1);
}

//************************************************************************************
int TransactionHistoryDlg::WhichDlgShouldBeLaunchedPending(long curSelItem)
{
   DString str;

   SetMessageStatusBar( NULL_STRING );
   const BFFieldId curSelField( curSelItem );

   if( curSelField == ifds::CertRequired )
   {//||
      if( hasReadPermission( UAF::ADDRESS_BOOK ) )
      {
         SetMessageStatusBar( TXT_BROWSE_ADDRESS_BOOK );
         setParameter( pACCOUNTNUM, AccountNum );
         setParameter( pENTITYID, EntityId ); 
         return(6); //address book
      }
      else
      {
         return(-1);
      }
   }

   if( curSelField == ifds::CertIssued )
   {
      DString str;
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, str );
      SetMessageStatusBar( TXT_BROWSE_CERTIFICATE );
      setParameter( INACCTNUM  , AccountNum ); 
      setParameter( INFUND  , str.strip() );
      setParameter( INCERTNUM  , NULL_STRING   );
      setParameter( INXREFNUM  , NULL_STRING   );
      return(2); // certificate
   }

   if (curSelField == ifds::PayType2 || 
      curSelField == ifds::PayTypeDesc)
   {
      DString payType, 
         payMethod;

      getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::PayType2, 
         payType, false);
      getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::PayMethod, 
         payMethod, false);
      
      payType.stripAll().upperCase();
      payMethod.strip().upperCase();

      if ((payMethod != CHEQUE && payType == I_("E")) || 
          (payMethod != CHEQUE && payType == I_("D1")) || 
         payType == I_("I") || payType == I_("D") )
      {
         // bank
         SetMessageStatusBar (TXT_BROWSE_BANK);
         //current list key in the pending trade list

         DString listKey;

         listKey = 
            getParent()->getCurrentListItemKey(this, IFASTBP_PROC::PENDING_LIST);
         setParameter (MFCAN_IP_PARAM::LIST_KEY, listKey);
         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum);
         setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::PENDING_TRADE);
         return 8;
      }
   }
   if( curSelField == ifds::Allocation )
   {
      SetMessageStatusBar( TXT_BROWSE_ALLOCATION );

      getParent()->setParameter(ALLOCATIONSPROC::ALLOCATION_TYPE, 
         ALLOCATIONSPROC::TRANSACTION_ONE_TIME);
      //caller
      setParameter(MFCAN_IP_PARAM::CALLER, ALLOCATIONSPROC::PENDING);
      //account num
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum); 
      //trans num
      setParameter(MFCAN_IP_PARAM::TRANS_NUM, TransNum); 
      //trade date
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, 
         ifds::TradeDate, str);
      str.strip();
      setParameter(MFCAN_IP_PARAM::TRADE_DATE, str); 
      //trans type
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, 
         ifds::TransType, str, false);
      str.stripAll();
      setParameter(MFCAN_IP_PARAM::TRANS_TYPE, str);
      //settle currency
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, 
         ifds::SettleCurrency, str);
      str.strip();
      setParameter(ALLOCATIONSPROC::SETTLE_CURRENCY, str); 
      //current list key in the pending trade list
      str = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::PENDING_LIST);
      setParameter(MFCAN_IP_PARAM::LIST_KEY, str);

      return 7; // allocation
   }
   if( curSelField == ifds::BatchUser ||
       curSelField == ifds::BatchTrace )
   {
      CString cstrBatch;
	  cstrBatch.LoadString(TXT_BATCH_ORDER_ENTRY_MENU);
	   SetMessageStatusBar( cstrBatch );
      return( _BATCH_ORDER_ENTRY );
   }

   if( curSelField == ifds::Branch ||
       curSelField == ifds::BranchName )
   {
      SetMessageStatusBar( TXT_BROWSE_BRANCH_INFO );
      return(_BRANCH_INFORMATION);
   }

   if( curSelField == ifds::Broker ||
       curSelField == ifds::BrokerName )
   {
      SetMessageStatusBar( TXT_BROWSE_BROKER_INFO );
      return(_BROKER_INFORMATION);
   }

   if( curSelField == ifds::SlsrepCode ||
       curSelField == ifds::SlsrepName )
   {
      SetMessageStatusBar( TXT_BROWSE_SELREP );
      return(_SALES_REP_INFORMATION);
   }

   if( curSelField == ifds::AccountTo )
      return(-1);

   if( curSelField == ifds::SplitComm )
   {
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::SplitComm, str, false);
      if( str == Y )
      {
         DString dstrTransTypeDesc;
 		 DString dstrFeeType; 

         getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, dstrTransTypeDesc, true);
         getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, dstrFeeType, false); 
         dstrTransTypeDesc.stripAll();
         setParameter(SPLITCOMM::ACCOUNT_NUM, AccountNum);
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::TRANSACTION_PENDING);
         str = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::PENDING_LIST);
         setParameter(SPLITCOMM::MAIN_LIST_KEY, str);
         setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, dstrTransTypeDesc);
         setParameter(SPLITCOMM::TRANSACTION_NUMBER, TransNum);
 		   setParameter(I_("FeeType"), dstrFeeType == I_("Y") ? FLAT : PERCENT);

         procType = PROC_SUPPORT;
         return(11);
      }
   }

   if( curSelField == ifds::ExtTransNum || curSelField == ifds::NetworkID )
   {
      return( _AWD_HISTORY );
   }
   
   if( ifds::SourceofFundsChecked ==  curSelField )
   {
      SetMessageStatusBar(TXT_SOURCE_OF_FUNDS_CHECKED);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("SourceofFundsChecked"));
      setParameter(MFCAN_IP_PARAM::TRANS_NUM, TransNum);
      return (_SOURCE_OF_FUNDS_CHECKED);
   } 

   return(-1);
}

//************************************************************************************
void TransactionHistoryDlg::PopulateDetails()
{
   if( m_bIsPending )
      PopulatePendingDetails();
   else
      PopulateTransDetails();

   if( m_TransDetail.GetItemCount() )
   {
      m_TransDetail.SetSelection(0);
   }
}

//************************************************************************************
void TransactionHistoryDlg::PopulateTransDetails()
{
   m_bIgnore = true;

   DString str, dstrTransType, dstrTaxType,TTStr;
   int index;

   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrTaxType, false );
   dstrTaxType.strip().upperCase();

   m_TransDetail.DeleteAllItems();

   // hide Settlement In Date:
   GetDlgItem (IDC_TXT_SETTLE_IN_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_SETTLEIN_DATE)->ShowWindow (SW_HIDE);
   
   // Display Remarks
   DString dstrRemarks;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Remarks1, str, true);
   dstrRemarks += str + I_("\r\n");
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Remarks2, str, true);
   dstrRemarks += str + I_("\r\n");
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Remarks3, str, true);
   dstrRemarks += str + I_("\r\n");
   CWnd *rwin = GetDlgItem(IDC_EDT_REMARK);
   rwin->SetWindowText(dstrRemarks.c_str());

   // Transaction Type
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, dstrTransType, false );
   dstrTransType.stripAll().upperCase();

   bool bDisplayEqAmtAndFactor = true;

   DString  dstrTempGrp1Shares( NULL_STRING ), dstrTempGrp2Shares( NULL_STRING );
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Grp1Shares, dstrTempGrp1Shares);
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Grp2Shares, dstrTempGrp2Shares);

    if( (!dstrTempGrp1Shares.empty() && DSTCommonFunctions::convertToDouble ( dstrTempGrp1Shares ) > 0 ) ||
        (!dstrTempGrp2Shares.empty() && DSTCommonFunctions::convertToDouble ( dstrTempGrp2Shares ) > 0 ) )
    {
        DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Grp1Shares, TXT_TRANS_GRP1SHARES);
        DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Grp2Shares, TXT_TRANS_GRP2SHARES);
     }
    DString  dstrTempGrp1Impact( NULL_STRING ), dstrTempGrp2Impact( NULL_STRING );
    getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::G1Impact, dstrTempGrp1Impact);
    getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::G2Impact, dstrTempGrp2Impact);
	if( ( !dstrTempGrp1Impact.empty() &&
		 ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) >   0.00000000001)||
		 ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) < - 0.00000000001) ) ||
       ( !dstrTempGrp2Impact.empty() && 
		 ( DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) >  0.00000000001 )||
		   DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) < -0.00000000001 ) )
	{
	 DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::G1Impact, TXT_G1IMPACT);
	 DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::G2Impact, TXT_G2IMPACT);
	}

   if( DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA )
   {
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::EventReceiptDate, TXT_EVENTRECEIPT_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::EventReceiptTime, TXT_EVENTRECEIPT_TIME,IS_TIME_HHMMSS);
   }

   // PURCHASES / DISTRIBUTIONS -----------------------------------------------------------------------------
   if(  DSTCommonFunctions::codeInList (dstrTransType, TRANSHIST_PURCHASE_LIKE ) )  //dstrTransType == ED || dstrTransType == ID )
   {    // begin purchases/distributions
      CString tmp;

      // Deposit Type
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::DepositType,ifds::DepositType,TXT_TRANS_DEPOSITTYPE);

      // Allocations
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Allocation, str, false);
      str.stripAll();
      if( str == Y )
      {
         CString tmp;
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());

         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      // Settled By
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettledBy,ifds::SettledBy,TXT_TRANS_SETTLEDBY);

      // Fee Percent
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::FeePercent,TXT_PENDING_FEE_RATE);
      // Order Type
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_TRANS_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString(( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT);
      m_TransDetail.SetItemText(index,1,tmp);

      // Wire Order Number
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::WireOrdNum,TXT_TRANS_WIREORDNUM);
      // Pay Type
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::PayType2,ifds::PayType2,TXT_TRANS_PAYTYPE);
      // Order Source
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::OrderSource,ifds::OrderSource,TXT_TRANS_ORDERSOURCE );
      // Settlement Source
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleSource,ifds::SettleSource,TXT_TRANS_SETTLESOURCE);
      // Settlement Type
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleType,ifds::SettleType,TXT_TRANS_SETTLETYPE);
      // Order Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderTrace,TXT_TRANS_ORDERTRACE);
      // Order User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderUser,TXT_TRANS_ORDERUSER);
      // Settle Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleTrace,TXT_TRANS_SETTLETRACE);
      // Settle User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleUser,TXT_TRANS_SETTLEUSER);
      // Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Commission,TXT_TRANS_COMMISSION,IS_NUMBER);
      // Split Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SplitComm, TXT_SPLIT_COMMISSION);
	  // Component Split
	  //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ComponentSplit, TXT_COMPONENT_SPLIT);
      // Transaction ID
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TransId,TXT_TRANS_TRANSID, IS_INTEGER);

      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::Accountable,ifds::Accountable,TXT_TRANS_ACCOUNTABLE);
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::SettleNetwork, TXT_SETTLE_NETWORK);
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::DilutionLinkNum, TXT_DILUTION_LINK_NUM);
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::FSRVLinkNum, TXT_FSRV_LINK_NUM);
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::GBCD, TXT_GBCD );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetGrossAmt,TXT_TRANS_SETGROSSAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetNetAmt,TXT_TRANS_SETNETAMT,IS_NUMBER);

      if( dstrTransType == ID )
      { // Distribution
         if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
         {
           
            DString   equalizationActive ( NULL_STRING );
            

            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::EqualizationActive, 
                                                                  equalizationActive, getDataGroupId(), false ) ;

            if( equalizationActive == I_( "Y" ))
            {
               bDisplayEqAmtAndFactor = false;
               DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::EqualFactor, TXT_TRANS_EQUALFACTOR);
               DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::EqualAmount, TXT_TRANS_EQUALAMT);
               DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::EqualAmtCurrency, TXT_TRANS_EQUALAMTCURR);
            }
         }
      }

      PopulateTransDetailsEqualizationAmt( bDisplayEqAmtAndFactor );
      
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositDate,TXT_TRANS_DEPOSITDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositId,TXT_TRANS_DEPOSITID);

      DisplayItem( IFASTBP_PROC::TRANS_LIST,ifds::ValueDate, TXT_TRANS_VALUEDATE );


      DisplayItem( IFASTBP_PROC::TRANS_LIST,ifds::ACHProcessor,TXT_TRANS_ACHPROC );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ACHProcessor, str );
      if( !str.strip().empty() )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PayMethod,TXT_TRANS_PAYMETHOD);
      }

      if( dstrTransType == ID )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrAcct,TXT_TRANS_TFRACCT,IS_INTEGER);
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrFund,TXT_TRANS_TFRFUND);
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrClass,TXT_TRANS_TFRCLASS);
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TaxCreditAmt,TXT_TAX_CREDIT_AMOUNT);
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SlsrepAltName,TXT_TRANS_SLSREPALTNAME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::UnitPrice,TXT_TRANS_UNITPRICE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SharesElig,TXT_TRANS_SHARESELIG,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CashDate,TXT_TRANS_CASHDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackAmt,TXT_TRANS_HOLDBACKAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackRate,TXT_TRANS_HOLDBACKRATE,IS_NUMBER);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossNetMethod,TXT_TRANS_GROSSORNET);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossOrNet,TXT_TRANS_GROSSORNET);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,TXT_TRANS_ROUNDFLAG);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ProvSales,ifds::ProvSales,TXT_TRANS_PROVSALES);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartFull,TXT_TRANS_PARTFULL); // TITLE CHANGED
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RvCode,ifds::RvCode,TXT_TRANS_RVCODE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RedCode,ifds::RedCode,TXT_TRANS_REDCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Initial,TXT_TRANS_INITIAL);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealDate,TXT_TRANS_DEALDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealTime,TXT_TRANS_DEALTIME,IS_TIME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExchRate,TXT_TRANS_EXCHRATE,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartnerShip,TXT_TRANS_PARTNERSHIP);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Indc,TXT_TRANS_INDC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SeqNum,TXT_TRANS_SEQNUM);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfIssued,TXT_TRANS_CONFISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfirmReq,TXT_TRANS_CONFIRMREQ);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RecptIssued,TXT_TRANS_RECPTISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OnStmt,TXT_TRANS_ONSTMT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrigAmount,TXT_ORIG_AMOUNT);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CertRequired,TXT_TRANS_CERTREQUIRED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PostUnsettled,TXT_TRANS_POSTUNSETTLED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExpSetlGN,TXT_TRANS_EXPSETLGN);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ChqSupCode,ifds::ChqSupCodeDesc,TXT_TRANS_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GroupCode,TXT_TRANS_GROUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfAccount,TXT_TRANS_SRCOFACCOUNT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_TRANS_SRCOFFUND);

      // Cancel Trace
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelTrace, str );
      str.strip('0');
      if( !str.empty() )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelBatch, str );
         str.strip();
         if( !str.empty() )
         {
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelBatch,TXT_TRANS_CANCELBATCH);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelTrace,TXT_TRANS_CANCELTRACE);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelUser,TXT_TRANS_CANCELUSER);
         }
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::VerifiedBy,TXT_TRANS_VERIFIEDBY);

      // Cancelled
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Cancelled,TXT_TRANS_CANCELLED);
      }

      // Reversal
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Reversal, TXT_TRANS_REVERSAL );
      }
      DString strDivDates;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::DivDates, 
                                                            strDivDates, getDataGroupId(), false ) ;
      if ( strDivDates.strip() == I_("1") ) {
         DisplayItem( IFASTBP_PROC::TRANS_LIST,ifds::ExDate, TXT_TRANS_EX_DATE );
      }
      DisplayResponseRequiredValueInAttributeList(IFASTBP_PROC::TRANS_LIST);

      DString dstrPaymentInfo,dstrConfIssued,dstrRvCode;
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::PaymentInfo, dstrPaymentInfo);      
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST,ifds::RvCode, dstrRvCode, false);
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST,ifds::ConfIssued, dstrConfIssued, false);

      if(!dstrPaymentInfo.empty() && (dstrRvCode ==I_("") || dstrRvCode==I_("08")) && dstrConfIssued != I_("X"))
      {		
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::PaymentInfo, TXT_PAYMENT_INFO );
      }
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RightToCancel,TXT_RIGHT_TO_CANCEL);
      //RDR Advice Provided
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RDRAdvice,TXT_RDR_ADVICE);
      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PSDAdvice,TXT_PSD_ADVICE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExternalInstitution,TXT_EXT_INSTITUTION,ALWAYS_SHOW);

   }    // end purchases/distributions

   // REDEMPTIONS / AUTOMATIC WITHDRAWLS --------------------------------------------------------------------
   else if (DSTCommonFunctions::codeInList (dstrTransType, TRANSHIST_REDEMPTION_LIKE))//( dstrTransType == PW || dstrTransType == AW || dstrTransType == TYPE_SWP )
   { // begin redemptions
      CString tmp;

      // Redemption Code
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RedCode,ifds::RedCode,TXT_TRANS_REDCODE);

      // Allocations
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Allocation, str, false);
      str.stripAll();
      if( str == Y )
      {
         CString tmp;
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      } else {
         //Redemption
         if ( dstrTransType == PW ) {
            //PTS 10023779 - Display Transfer Fund/Class when there is no allocation
            //and the fund/class is returned from view.
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrFund,TXT_TRANS_TFRFUND);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrClass,TXT_TRANS_TFRCLASS);
         }
      }
      // Fee Percent
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::FeePercent, TXT_PENDING_FEE_RATE);

      // Order Type
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_TRANS_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString(( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT);
      m_TransDetail.SetItemText(index,1,tmp);

      // Wire Order Number
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::WireOrdNum,TXT_TRANS_WIREORDNUM);
      // Pay Type
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::PayType2,ifds::PayType2,TXT_TRANS_PAYTYPE);
      // Order Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderTrace,TXT_TRANS_ORDERTRACE);
      // Order User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderUser,TXT_TRANS_ORDERUSER);
      // Settle Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleTrace,TXT_TRANS_SETTLETRACE);
      // Settle User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleUser,TXT_TRANS_SETTLEUSER);
      if( dstrTransType == PW )
      {
          //OverrideTax
          DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideTax,TXT_PENDING_OVERRIDETAX);
          //AcctLevelTax
          DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::AcctLevelTax,TXT_TRANS_ACCTLEVELTAX);
      }
      // Federal Tax Rate
      DisplayTaxRates( IFASTBP_PROC::TRANS_LIST, ifds::FedRate, ifds::TransRatePUDFed, TXT_PENDING_FEDTAXRATE );
      // Provincial Tax Rate
      DisplayTaxRates( IFASTBP_PROC::TRANS_LIST, ifds::ProvRate, ifds::TransRatePUDProv, TXT_PENDING_PROVTAXRATE );

      // Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Commission,TXT_TRANS_COMMISSION,IS_NUMBER);
      // Split Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SplitComm, TXT_SPLIT_COMMISSION);
	  // Component Split
	  //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ComponentSplit, TXT_COMPONENT_SPLIT);

      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::Accountable,ifds::Accountable,TXT_TRANS_ACCOUNTABLE);
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::SettleNetwork, TXT_SETTLE_NETWORK);
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::DilutionLinkNum, TXT_DILUTION_LINK_NUM);
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::FSRVLinkNum, TXT_FSRV_LINK_NUM);
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::GBCD, TXT_GBCD );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideDSCDesc,TXT_TRANS_OVERRIDEDSCDESC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideAmt,TXT_TRANS_OVERRIDEAMT,IS_NUMBER); 
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetGrossAmt,TXT_TRANS_SETGROSSAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetNetAmt,TXT_TRANS_SETNETAMT,IS_NUMBER);

      PopulateTransDetailsEqualizationAmt( bDisplayEqAmtAndFactor );

      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleType,ifds::SettleType,TXT_TRANS_SETTLETYPE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ChqSupCode,ifds::ChqSupCodeDesc,TXT_TRANS_CHQSUPCODE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::OrderSource,ifds::OrderSource,TXT_TRANS_ORDERSOURCE );
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleSource,ifds::SettleSource,TXT_TRANS_SETTLESOURCE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartFull,TXT_TRANS_PARTFULL); // TITLE CHANGED
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositId,TXT_TRANS_DEPOSITID);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SlsrepAltName,TXT_TRANS_SLSREPALTNAME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::UnitPrice,TXT_TRANS_UNITPRICE);
    
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SharesElig,TXT_TRANS_SHARESELIG,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CashDate,TXT_TRANS_CASHDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackAmt,TXT_TRANS_HOLDBACKAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackRate,TXT_TRANS_HOLDBACKRATE,IS_NUMBER);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossNetMethod,TXT_TRANS_GROSSORNET);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossOrNet,TXT_TRANS_GROSSORNET);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,TXT_TRANS_ROUNDFLAG);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ProvSales,ifds::ProvSales,TXT_TRANS_PROVSALES);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RvCode,ifds::RvCode,TXT_TRANS_RVCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Initial,TXT_TRANS_INITIAL);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealDate,TXT_TRANS_DEALDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealTime,TXT_TRANS_DEALTIME,IS_TIME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExchRate,TXT_TRANS_EXCHRATE,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartnerShip,TXT_TRANS_PARTNERSHIP);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Indc,TXT_TRANS_INDC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SeqNum,TXT_TRANS_SEQNUM);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TransId,TXT_TRANS_TRANSID, IS_INTEGER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfIssued,TXT_TRANS_CONFISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfirmReq,TXT_TRANS_CONFIRMREQ);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RecptIssued,TXT_TRANS_RECPTISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OnStmt,TXT_TRANS_ONSTMT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrigAmount,TXT_ORIG_AMOUNT);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CertRequired,TXT_TRANS_CERTREQUIRED);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettledBy,ifds::SettledBy,TXT_TRANS_SETTLEDBY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PostUnsettled,TXT_TRANS_POSTUNSETTLED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExpSetlGN,TXT_TRANS_EXPSETLGN);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GroupCode,TXT_TRANS_GROUPCODE);
	  
	  //P0205924.FN01 - if trantype is management fee then adds 2 fields below.
	  if (dstrTransType == MGMT_FEE_CODE){
		  DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::DealerFee, TXT_DEALER_SERVICE_FEE);
		  DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FundCompFee, TXT_FUND_COMP_FEE);
	  }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfAccount,TXT_TRANS_SRCOFACCOUNT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_TRANS_SRCOFFUND);

      // Cancel Trace
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelTrace, str );
      str.strip('0');
      if( !str.empty() )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelBatch, str );
         str.strip();
         if( !str.empty() )
         {
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelBatch,TXT_TRANS_CANCELBATCH);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelTrace,TXT_TRANS_CANCELTRACE);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelUser,TXT_TRANS_CANCELUSER);
         }
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::VerifiedBy,TXT_TRANS_VERIFIEDBY);

      // Cancelled
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Cancelled,TXT_TRANS_CANCELLED);
      }

      // Reversal
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Reversal, TXT_TRANS_REVERSAL );
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ValueDate,TXT_TRANS_VALUEDATE );

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ACHProcessor,TXT_TRANS_ACHPROC);
      getParent()->getField(this, IFASTBP_PROC::TRANS_LIST, ifds::ACHProcessor, str);
      if( !str.strip().empty() )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PayMethod,TXT_TRANS_PAYMETHOD);
      }

      // Bank Charge
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST, ifds::BankChrgs, ifds::BankChrgs, TXT_BANKCHARGE);
      DisplayResponseRequiredValueInAttributeList(IFASTBP_PROC::TRANS_LIST);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PymtRoutingMthd, TXT_PAYMENT_ROUTING_TYPE);     
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExternalInstitution,TXT_EXT_INSTITUTION,ALWAYS_SHOW);

   }   // end redemptions

   // TRANSFERS/EXCHANGES -----------------------------------------------------------------------------------
   else if( DSTCommonFunctions::codeInList( dstrTransType, TRANSHIST_EXCHANGE_LIKE   ) ||
            DSTCommonFunctions::codeInList( dstrTransType, TRANSHIST_EXCHANGE_LIKE_2 )
       )
   { // begin transfers/exchanges

      // Allocations
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Allocation, str, false);
      str.stripAll();
      if( str == Y )
      {
         CString tmp;
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      // Redemption Code
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RedCode,ifds::RedCode,TXT_TRANS_REDCODE);
      // Deposit Type
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::DepositType,ifds::DepositType,TXT_TRANS_DEPOSITTYPE);
      // Fee Percent
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::FeePercent,TXT_PENDING_FEE_RATE);
      // Transfer Account
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrAcct,TXT_TRANS_TFRACCT,IS_INTEGER);
      // Transfer Fund
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrFund,TXT_TRANS_TFRFUND);
      // Transfer Class
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrClass,TXT_TRANS_TFRCLASS);

  	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::DilutionLinkNum, TXT_DILUTION_LINK_NUM);
	  DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::FSRVLinkNum, TXT_FSRV_LINK_NUM);

      // Transfer Fund Number
      DString dstrFundNumber, dstrFund, dstrClass;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrFund, dstrFund );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrClass, dstrClass );
      dstWorkSession->GetFundNumber( dstrFund, dstrClass, dstrFundNumber );
      if( !dstrFundNumber.empty() && DisplayThisItem( dstrFundNumber, IS_NUMBER ) )
      {
         CString label;
         label.LoadString(TXT_TRANS_TFRFUNDNUM);
         int index = m_TransDetail.InsertItem(99999, label);
         m_TransDetail.SetItemText(index, 1, dstrFundNumber.c_str());
      }

     // Order Type
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderType, str ,false);
      str.strip();
      CString tmp;
      tmp.LoadString(TXT_TRANS_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString(( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT);
      m_TransDetail.SetItemText(index,1,tmp);

      // Wire Order Number
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::WireOrdNum,TXT_TRANS_WIREORDNUM);
      // Order Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderTrace,TXT_TRANS_ORDERTRACE);
      // Order User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderUser,TXT_TRANS_ORDERUSER);
      // Settle Trace
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleTrace,TXT_TRANS_SETTLETRACE);
      // Settle User
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleUser,TXT_TRANS_SETTLEUSER);
      // Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Commission,TXT_TRANS_COMMISSION,IS_NUMBER);
      // Split Commission
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SplitComm, TXT_SPLIT_COMMISSION);
	  // Component Split
	  //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ComponentSplit, TXT_COMPONENT_SPLIT);

      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::Accountable,ifds::Accountable,TXT_TRANS_ACCOUNTABLE);
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::GBCD, TXT_GBCD );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetGrossAmt,TXT_TRANS_SETGROSSAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetNetAmt,TXT_TRANS_SETNETAMT,IS_NUMBER);

      PopulateTransDetailsEqualizationAmt( bDisplayEqAmtAndFactor );

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SlsrepAltName,TXT_TRANS_SLSREPALTNAME);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::OrderSource,ifds::OrderSource,TXT_TRANS_ORDERSOURCE );
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleSource,ifds::SettleSource,TXT_TRANS_SETTLESOURCE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleType,ifds::SettleType,TXT_TRANS_SETTLETYPE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::UnitPrice,TXT_TRANS_UNITPRICE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SharesElig,TXT_TRANS_SHARESELIG,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositDate,TXT_TRANS_DEPOSITDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CashDate,TXT_TRANS_CASHDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackAmt,TXT_TRANS_HOLDBACKAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackRate,TXT_TRANS_HOLDBACKRATE,IS_NUMBER);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossNetMethod,TXT_TRANS_GROSSORNET);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossOrNet,TXT_TRANS_GROSSORNET);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,TXT_TRANS_ROUNDFLAG);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ProvSales,ifds::ProvSales,TXT_TRANS_PROVSALES);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartFull,TXT_TRANS_PARTFULL); // TITLE CHANGED
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RvCode,ifds::RvCode,TXT_TRANS_RVCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Initial,TXT_TRANS_INITIAL);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealDate,TXT_TRANS_DEALDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealTime,TXT_TRANS_DEALTIME,IS_TIME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExchRate,TXT_TRANS_EXCHRATE,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartnerShip,TXT_TRANS_PARTNERSHIP);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Indc,TXT_TRANS_INDC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SeqNum,TXT_TRANS_SEQNUM);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideDSCDesc,TXT_TRANS_OVERRIDEDSCDESC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideAmt,TXT_TRANS_OVERRIDEAMT,IS_NUMBER); 
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfIssued,TXT_TRANS_CONFISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfirmReq,TXT_TRANS_CONFIRMREQ);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RecptIssued,TXT_TRANS_RECPTISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OnStmt,TXT_TRANS_ONSTMT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrigAmount,TXT_ORIG_AMOUNT);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CertRequired,TXT_TRANS_CERTREQUIRED);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettledBy,ifds::SettledBy,TXT_TRANS_SETTLEDBY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PostUnsettled,TXT_TRANS_POSTUNSETTLED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExpSetlGN,TXT_TRANS_EXPSETLGN);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ChqSupCode,ifds::ChqSupCodeDesc,TXT_TRANS_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GroupCode,TXT_TRANS_GROUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfAccount,TXT_TRANS_SRCOFACCOUNT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_TRANS_SRCOFFUND);

      // Cancel Trace
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelTrace, str );
      str.strip('0');
      if( !str.empty() )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelBatch, str );
         str.strip();
         if( !str.empty() )
         {
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelBatch,TXT_TRANS_CANCELBATCH);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelTrace,TXT_TRANS_CANCELTRACE);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelUser,TXT_TRANS_CANCELUSER);
         }
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::VerifiedBy,TXT_TRANS_VERIFIEDBY);

      // Cancelled
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Cancelled,TXT_TRANS_CANCELLED);
      }

      // Reversal
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Reversal, TXT_TRANS_REVERSAL );
      }
	  //PF Crystalisation
	  DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PFCrystalisation,TXT_PFCRYSTALISATION);
	  //RDR Advice Provided
	  DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RDRAdvice,TXT_RDR_ADVICE);
	  DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SDRTExemptCode,TXT_SDRT_EXEMPT_CODE);   
   }     // end transfers/exchanges

   else // For all other transaction types
   {
      CString tmp;

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetGrossAmt,TXT_TRANS_SETGROSSAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SetNetAmt,TXT_TRANS_SETNETAMT,IS_NUMBER);

      PopulateTransDetailsEqualizationAmt( bDisplayEqAmtAndFactor );

      // Allocations
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Allocation, str, false);
      str.stripAll();
      if( str == Y )
      {
         CString tmp;
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId() );
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderType, str ,false);
      str.strip();

      // Order Type
      tmp.LoadString(TXT_TRANS_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString(( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT);
      m_TransDetail.SetItemText(index,1,tmp);

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::WireOrdNum,TXT_TRANS_WIREORDNUM);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrAcct,TXT_TRANS_TFRACCT,IS_INTEGER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrFund,TXT_TRANS_TFRFUND);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TfrClass,TXT_TRANS_TFRCLASS);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SlsrepAltName,TXT_TRANS_SLSREPALTNAME);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::OrderSource,ifds::OrderSource,TXT_TRANS_ORDERSOURCE );
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleSource,ifds::SettleSource,TXT_TRANS_SETTLESOURCE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettleType,ifds::SettleType,TXT_TRANS_SETTLETYPE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::UnitPrice,TXT_TRANS_UNITPRICE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::FeePercent,TXT_PENDING_FEE_RATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Commission,TXT_TRANS_COMMISSION,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::SplitComm, TXT_SPLIT_COMMISSION);
	  // Component Split
	  //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ComponentSplit, TXT_COMPONENT_SPLIT);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SharesElig,TXT_TRANS_SHARESELIG,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositDate,TXT_TRANS_DEPOSITDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CashDate,TXT_TRANS_CASHDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackAmt,TXT_TRANS_HOLDBACKAMT,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::HoldBackRate,TXT_TRANS_HOLDBACKRATE,IS_NUMBER);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossNetMethod,TXT_TRANS_GROSSORNET);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GrossOrNet,TXT_TRANS_GROSSORNET);

      //DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,TXT_TRANS_ROUNDFLAG);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ProvSales,ifds::ProvSales,TXT_TRANS_PROVSALES);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartFull,TXT_TRANS_PARTFULL); // TITLE CHANGED
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RvCode,ifds::RvCode,TXT_TRANS_RVCODE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RedCode,ifds::RedCode,TXT_TRANS_REDCODE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::DepositType,ifds::DepositType,TXT_TRANS_DEPOSITTYPE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Initial,TXT_TRANS_INITIAL);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealDate,TXT_TRANS_DEALDATE,IS_DATE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DealTime,TXT_TRANS_DEALTIME,IS_TIME);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExchRate,TXT_TRANS_EXCHRATE,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PartnerShip,TXT_TRANS_PARTNERSHIP);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Indc,TXT_TRANS_INDC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SeqNum,TXT_TRANS_SEQNUM);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::TransId,TXT_TRANS_TRANSID, IS_INTEGER);

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideDSCDesc,TXT_TRANS_OVERRIDEDSCDESC);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OverrideAmt,TXT_TRANS_OVERRIDEAMT,IS_NUMBER); 
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfIssued,TXT_TRANS_CONFISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ConfirmReq,TXT_TRANS_CONFIRMREQ);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RecptIssued,TXT_TRANS_RECPTISSUED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OnStmt,TXT_TRANS_ONSTMT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrigAmount,TXT_ORIG_AMOUNT);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CertRequired,TXT_TRANS_CERTREQUIRED);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::PayType2,ifds::PayType2,TXT_TRANS_PAYTYPE);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SettledBy,ifds::SettledBy,TXT_TRANS_SETTLEDBY);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PostUnsettled,TXT_TRANS_POSTUNSETTLED);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ExpSetlGN,TXT_TRANS_EXPSETLGN);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::ChqSupCode,ifds::ChqSupCodeDesc,TXT_TRANS_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GroupCode,TXT_TRANS_GROUPCODE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfAccount,TXT_TRANS_SRCOFACCOUNT);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_TRANS_SRCOFFUND);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderTrace,TXT_TRANS_ORDERTRACE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OrderUser,TXT_TRANS_ORDERUSER);

      // Cancel Trace
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelTrace, str );
      str.strip('0');
      if( !str.empty() )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelBatch, str );
         str.strip();
         if( !str.empty() )
         {
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelBatch,TXT_TRANS_CANCELBATCH);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelTrace,TXT_TRANS_CANCELTRACE);
            DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::CancelUser,TXT_TRANS_CANCELUSER);
         }
      }

      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleTrace,TXT_TRANS_SETTLETRACE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SettleUser,TXT_TRANS_SETTLEUSER);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::VerifiedBy,TXT_TRANS_VERIFIEDBY);
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::Accountable,ifds::Accountable,TXT_TRANS_ACCOUNTABLE);
      DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON);
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DepositId,TXT_TRANS_DEPOSITID);

      // Cancelled
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Cancelled,TXT_TRANS_CANCELLED);
      }

      // Reversal
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Reversal, str, false );
      str.upperCase().strip();
      if( str == I_("Y") )
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Reversal, TXT_TRANS_REVERSAL );
      }
      DString strDivDates;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::DivDates, 
                                                            strDivDates, getDataGroupId(), false ) ;
      if ( strDivDates.strip() == I_("1") ) {
         DisplayItem( IFASTBP_PROC::TRANS_LIST,ifds::ExDate, TXT_TRANS_EX_DATE );
      }
   }            // end_if


   SetTransStaticText();

// SetTransStaticText moves the Fund Details pointer to the correct fund in the process
// so that the SUB_PROCESS DSC_REDEMP_ACCESS will have the correct fund when 
// testing to see if the FundLoad is BEL

   // COMMON
   if( dstrTransType == PW )
   {
      getParent()->getField ( this, BF::NullContainerId, DSC_REDEMP_ACCESS , str );
      if( str == Y )
      {
         DisplayItem ( BF::NullContainerId, DSC_REDEMP_ACCESS , TXT_REDEMPTION_DETAIL );
      }
   }
   UpdateData(FALSE);

   m_bIgnore = false;


  // Tax Exempt Authorization amount

    getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ProvTaxExemptAmt, str );
    if( DSTCommonFunctions::convertToDouble( str ) != 0.0 ) 
        DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ProvTaxExemptAmt,TXT_TRANS_PRO_TAXEXEMPTAUTH,IS_NUMBER);
    getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::FedTaxExemptAmt, str );
    if( DSTCommonFunctions::convertToDouble( str ) != 0.0 ) 
        DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::FedTaxExemptAmt,TXT_TRANS_FED_TAXEXEMPTAUTH,IS_NUMBER);

   // Display SWIFT items
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::NetworkID, TXT_PENDING_NETWORKID );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ExtTransNum,  TXT_PENDING_EXTTRANSNUM );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::SendRefNum,   TXT_PENDING_SENDREFNUM );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::PartRefNum,   TXT_PENDING_PARTREFNUM );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::MasterRefNum, TXT_PENDING_MASTERREFNUM );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::SendLinkRefNum, TXT_TRANS_SENDLINKREFNUM );

   //charge er/sttr fee and/or WD fee
   if (dstrTransType == TR || dstrTransType == PW || dstrTransType == XR || dstrTransType == TO || dstrTransType == EO) 
   {
      if (dstrTransType == TR || dstrTransType == XR || dstrTransType == TO || dstrTransType == EO)
      {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ChargeERSTTRFee, 
            TXT_PENDING_SHORTTERMTRANSFER_FEE);
      } 
      else 
      {
        DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ChargeWDFee, 
            TXT_CHARGE_WD_FEE );
        DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ChargeERSTTRFee, 
            TXT_EARLYREDEMPTION_FEE );
      }
   }

   if ( dstrTransType == ED )
      DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::BorrowedFunds, TXT_BORROWED_FUNDS );

   if ( dstrTransType == PW )
   {
      DSTCWorkSession *dstWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      SupportedProductsList *pSupportedProductsList = NULL;

      if (dstWorkSession && 
         dstWorkSession->getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
         pSupportedProductsList)
      {
         if (pSupportedProductsList->isLSIFProductActive ())
         {
            DisplayItem (IFASTBP_PROC::TRANS_LIST, ifds::LSIFCode, TXT_LSIF_CWB_REASON);
         }
      }
   }
   // Delivery Method 
   DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::DeliveryMethod,TXT_DELIVERY_METHOD ); // IN 343484

//PET 1117
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FundWKN,  TXT_WKN);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FundISIN,  TXT_ISIN);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Valoren,  TXT_FROM_VALOREN );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::CUSIP,    TXT_FROM_CUSIP);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::TDCC,     TXT_FROM_TDCC);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FundLFC,     TXT_FUND_LEGACY_CODE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::AcqFeeOption,  TXT_ACQ_FEE_OPTION);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::AcqDiscountRate,  TXT_DISCOUNT_RATE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FrSettlInstrCode, TXT_SETTLE_INSTR_CODE );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ToSettlInstrCode,  TXT_TO_SETTLE_INSTR_CODE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::FundBrokerCode,  TXT_FUND_BROKER_CODE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::AggregateOption,  TXT_AGG_OPTION);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::BrkSettlDate,  TXT_BROKER_SETTLE_DATE,IS_DATE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::DeliveryNetwork,  TXT_DELIVERY_NETWORK);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::OtherConfirmType, TXT_OTHER_CONFIRM_TYPE, REPLACE_BLANK_BY_NA );
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ExternalPrice,  TXT_EXTERNAL_PRICE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ExternalSettleDate,  TXT_EXTERNAL_SETTLE_DATE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ExternalSettleAmt,  TXT_EXTERNAL_SETTLE_AMT);

   //PET1171_FN01: EU Savings Directive (Others)
   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC:: TRANS_DECIMALS) != NULL_STRING )
   {
      do
      {
         DString dstrDecimalValue;
         getParent()->getField(this, IFASTBP_PROC::TRANS_DECIMALS, ifds::DecimalValue, dstrDecimalValue );
         dstrDecimalValue.stripAll().stripLeading('0');

         double dec_value = DSTCommonFunctions::convertToDouble (dstrDecimalValue);
         if ( dec_value == 2.00)  
         {
            DString dstrDecimalType;
            getParent()->getField(this, IFASTBP_PROC::TRANS_DECIMALS, ifds::DecimalType, dstrDecimalType );

            if ( DSTCommonFunctions::codeInList( dstrDecimalType.upperCase(), EUSD_TAX_REPORTS) )
            {
               DString dstrDecimalTypeDesc;
               getParent()->getField(this, IFASTBP_PROC::TRANS_DECIMALS, ifds::DecimalTypeDesc, dstrDecimalTypeDesc );
               displayTransDec(dstrDecimalTypeDesc);
            }
         }

      } while( getParent()->getNextListItemKey( this, IFASTBP_PROC::TRANS_DECIMALS ) != NULL_STRING );
   } 
// ROA enhancement

   double dCom;
   DString amount;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST,ifds::ROAAmount,amount, false );
   dCom = DSTCommonFunctions::convertToDouble( amount );
   if( dCom > 0.0 )
   {
     DisplayItem(  IFASTBP_PROC::TRANS_LIST, ifds::ROAAmount,  TXT_ROA_AMOUNT );
   }
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST,ifds::CommissionAmnt,amount, false );
   dCom = DSTCommonFunctions::convertToDouble( amount );
   if( dCom > 0.0 )
   {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::CommissionAmnt,  TXT_COM_AMOUNT);
   }

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST,ifds::NonCommissionAmnt,amount, false );
   dCom = DSTCommonFunctions::convertToDouble( amount );
   if( dCom > 0.0 )
   {
         DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::NonCommissionAmnt,  TXT_NON_COM_AMOUNT);
   }

   str = I_( "" );   

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::AdjTransNum, str, false );   
   if( str.strip() != NULL_STRING )
   {
        DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::AdjTransNum,TXT_ADJ_TRANS_NUMBER);   
   }

    // trade suppress
    DString dstrMCHSRActive;
    DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());			 		 
    if ( NULL != pDSTCWorkSession )
    {
		pDSTCWorkSession->getOption( ifds::MCHSRActive, dstrMCHSRActive, getDataGroupId(), false );

		if (dstrMCHSRActive == I_("Y") )
		{
			DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::MCHFileTransHist, TXT_MCH_FILE_INDICATOR );
			DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::SecRecFileTransHist, TXT_SEC_REC_FILE_INDICATOR);
		}
	}

	DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::Reconciled,TXT_TRANS_RECONCILED);
	DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::LinkedEntityName,TXT_ASSOCIATED_ENTITY);

	if ( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA && 
								( dstrTransType == AW ||
								  dstrTransType == ID ||
								  dstrTransType == MGMT_FEE_CODE ) )
   {
		getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ESGSettle, str, false );
		if ( str.strip().upperCase() == I_("EX"))
		{
			DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ESGSettle, TXT_TRANS_ESG_SETTLE);
		}
	}

   DString dstrAuthorization; 
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::StcPendTrdAuthorization, dstrAuthorization );
   dstrAuthorization.strip();
   
   if (!dstrAuthorization.empty ())
   {
       DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::StcPendTrdAuthorization, TXT_TRANS_AUTHORIZATION);
   }

   DString strExpectedSettleDate;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ExpectedSettleDate, strExpectedSettleDate ,false);
   
   if ( !strExpectedSettleDate.empty() ) 
   {
      DisplayItem( IFASTBP_PROC::TRANS_LIST,ifds::ExpectedSettleDate, TXT_TRANS_EXPECT_SETTLE_DATE );
   }

   // NSCC Control Number
   NSCCControlNumber ();
   
   DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::PendTrdContract,TXT_PEND_TRADE_CONTRACT);
   DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::ValuationDt,TXT_VALUATION_DATE);       
   DString dstrGuaranteesOverride; 
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::GuaranteesOverride, dstrGuaranteesOverride, false );
   dstrGuaranteesOverride.strip().upperCase();

   if(!dstrGuaranteesOverride.empty() )
   {
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::GuaranteesOverride,TXT_GUARANTEE_OVERRIDE);
   }

   //IN3327265 - Tax jurisdiction should be displayed on the transaction history screen for all transaction types regardless of the market
   //if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   //{
      DisplayCodeDesc(IFASTBP_PROC::TRANS_LIST,ifds::TaxJuris,ifds::TaxJuris,TXT_TAX_JURIS);
   //}
   DisplayItem(IFASTBP_PROC::TRANS_LIST ,  ifds::SourceOfTrade,   TXT_SOURCE_OF_TRADE   );
   DisplayItem(IFASTBP_PROC::TRANS_LIST ,  ifds::ChannelOfTrade,  TXT_CHANNEL_OF_TRADE  );
   DisplayItem(IFASTBP_PROC::TRANS_LIST ,  ifds::Platform,		  TXT_PLATFORM );
   DisplayItem(IFASTBP_PROC::TRANS_LIST,   ifds::PSDAdvice,		  TXT_PSD_ADVICE);
   DisplayItem(IFASTBP_PROC::TRANS_LIST,   ifds::CrossSysAcctNum, TXT_CROSS_SYSTEM_ACC_NUM);
   DisplayItem(IFASTBP_PROC::TRANS_LIST,   ifds::AggregationType, TXT_AGGREGATION_TYPE);

   DString dstrDepositType;
	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::DepositType, dstrDepositType, false); 
   bool bIsMFRTrades = false;
   //don't display the ourceofFundsChecked attribute for MFR trades 
   //display only for Purchse trades.
   bIsMFRTrades = DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::MFR_TARDES );
   if( !bIsMFRTrades && I_("2") != dstrDepositType && DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::PURCHASE_LIKE ) )
       DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::SourceofFundsChecked, TXT_SOURCE_OF_FUNDS_CHECKED_ATTRB, REPLACE_BLANK_BY_NA );

   DString dstrtemp = dstrTransType.substr(0,2);
   if(dstrtemp == TRADETYPE::PURCHASE ) //Applicable for all tarnstype with ED irrespective of indicator code.
   {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::OfferPrice,TXT_TRANS_OFFER_PRICE);
   }
   if(dstrtemp == TRADETYPE::REDEMPTION ) //Applicable for all tarnstype with PW irrespective of indicator code.
   {
         DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::BidPrice,TXT_TRANS_BID_PRICE);   
   }   
   if(dstrTransType == TRADETYPE::REFUND_REDEMPTION)
   {
      DisplayItem(IFASTBP_PROC::TRANS_LIST,ifds::RefundAmtOpt,TXT_REFUND_AMOUNT_OPTION);   
   }
   if( DSTCommonFunctions::codeInList(dstrtemp,TRADETYPE::MONEY_OUT_TRADES) ) 
   {	   	   		  
	   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::Deconversion, TXT_DECONVERSION);
   }
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::OrderRouting, TXT_ORDERROUTING);
      
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::OrigGrossNet, TXT_ORIG_GROSSNET);

   if (TTStr == TRADETYPE::EXCHANGE_IN || TTStr == TRADETYPE::TRANSFER_IN)
   {
	   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::TradeInDate, TXT_TRADE_IN_DATE);
	   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ValuationInDt, TXT_VALUATION_IN_DATE);
   }
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::PricingCode, TXT_PRICING_CODE);
   if (dstrTransType != TRADETYPE::EXCHANGE_IN && dstrTransType != TRADETYPE::TRANSFER_IN)
   {
	   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::GateOverrideIndicator, TXT_WAIVEGATING_FLAG);
   }
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::ComponentSplit, TXT_COMPONENT_SPLIT);
   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::DistSplitType, TXT_DIST_SPLITTYPE);

   if (TTStr == TRADETYPE::PURCHASE)
   {
	   DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::RDSPPaymtDate, TXT_RDSP_PAYMENT_DATE);
   }

   if (dstrTransType == TRADETYPE::REFUND_REDEMPTION)
   {
		DisplayItem(IFASTBP_PROC::TRANS_LIST, ifds::RefundNAV, TXT_REFUND_NAV);
   }
}

//************************************************************************************

void TransactionHistoryDlg::PopulatePendingDetails()
{
   m_bIgnore = true;

   CString tmp;
   DString str, TTStr, strTaxType;
   int index;
   bool bBELFund = false;
   m_TransDetail.DeleteAllItems();

   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, strTaxType, false );
   strTaxType.strip().upperCase();

   // Remarks 
   DString dstrRemarks;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Remarks1, str, true);
   dstrRemarks += str + I_("\r\n");
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Remarks2, str, true);
   dstrRemarks += str + I_("\r\n");
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Remarks3, str, true);
   dstrRemarks += str + I_("\r\n");
   CWnd *rwin = GetDlgItem(IDC_EDT_REMARK);
   rwin->SetWindowText(dstrRemarks.c_str());

   // Set Static Text
   SetPendingStaticText(); // Poorly, it sets Fund Detail List for which code relies on.
   getParent()->getField ( this, BF::NullContainerId, IS_FUND_BEL, str );
   bBELFund = (str == Y);

   // get Transaction Type
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, TTStr, false );
   TTStr.stripAll().upperCase();

   CString txt;

   if (TTStr == I_("TR") || TTStr == I_("XR"))
   {
       txt.LoadString (TXT_SETTLE_OUT_DATE);
       GetDlgItem (IDC_STC_SETTLE_OUT_DATE)->SetWindowText (txt);
       GetDlgItem (IDC_TXT_SETTLE_IN_DATE)->ShowWindow (SW_SHOW);
       GetDlgItem (IDC_STC_SETTLEIN_DATE)->ShowWindow (SW_SHOW);
   }
   else
   {
       txt.LoadString (TXT_SETTLE_DATE);
       GetDlgItem (IDC_STC_SETTLE_OUT_DATE)->SetWindowText (txt);
       GetDlgItem (IDC_TXT_SETTLE_IN_DATE)->ShowWindow (SW_HIDE);
       GetDlgItem (IDC_STC_SETTLEIN_DATE)->ShowWindow (SW_HIDE);
   }
   if( DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA )
   {
    DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::EventReceiptDate, TXT_EVENTRECEIPT_DATE);
    DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::EventReceiptTime, TXT_EVENTRECEIPT_TIME,IS_TIME_HHMMSS);
   }

   // PURCHASES/DISTRIBUTIONS -------------------------------------------------------------------------------
   if(  DSTCommonFunctions::codeInList( TTStr, TRADETYPE::PURCHASE_LIKE ) )  //dstrTransType == ED || dstrTransType == ID )
   {
      // Deposit Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::DepositType,ifds::DepositType,TXT_PENDING_DEPOSITTYPE);

      // Allocations
      if( AreThereAllocationInThisPending() )
      {
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GrossNetMethod,TXT_PENDING_GROSSORNET);

      // Good/Bad
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GoodBad, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_GOODBAD);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::GoodBad.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_GOOD : TXT_PENDING_BAD );
      m_TransDetail.SetItemText(index,1,tmp);

      // Reject Code
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RejCode,ifds::RejCode,TXT_PENDING_REJCODE );
      // Payment Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::PayType2,ifds::PayType2,TXT_PENDING_PAYTYPE);
      // Order Source
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::OrderSource,ifds::OrderSource ,TXT_PENDING_ORDERSOURCE);

      // Fee Rate
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, str, false);
      str.strip();
      DisplayFeeRate( str == Y );

      // Fee in Flat/Percent
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, TXT_PENDING_FLATPERCENT );
      // Settlement Source
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleSource,ifds::SettleSource,TXT_PENDING_SETTLESOURCE );

      // Order Type + Wire Order Number
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString( (str == Y) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT );
      m_TransDetail.SetItemText(index,1,tmp);
      if( str == Y )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::WireOrdNum     ,TXT_PENDING_WIREORDNUM     );
      }

      // Settlement Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleType,ifds::SettleType,TXT_PENDING_SETTLETYPE );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Accountable,ifds::Accountable,TXT_PENDING_ACCOUNTABLE );
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
	  DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::SettleNetwork, TXT_SETTLE_NETWORK);
	  DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::DilutionLinkNum, TXT_DILUTION_LINK_NUM);
	  DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::FSRVLinkNum, TXT_FSRV_LINK_NUM);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExtraCommission,TXT_PENDING_EXTRACOMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SplitComm,TXT_SPLIT_COMMISSION);
      if( bBELFund )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BELFee         ,TXT_PENDING_BELFEE );
      }
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AdminFeeAmt       ,TXT_PENDING_ADMINFEEAMT      ,IS_NUMBER);

      displayADLCharge( TTStr );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RedCode,ifds::RedCode,TXT_PENDING_REDCODE );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::ProvSales,ifds::ProvSales,TXT_PENDING_PROVSALES);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ConfirmRequired     ,TXT_PENDING_CONFIRMREQ     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExchRate       ,TXT_PENDING_EXCHRATE       ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrCode       ,TXT_PENDING_ADDRCODE       );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrLine       ,TXT_PENDING_ADDRLINE       );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SuppressCode,ifds::SuppressCode,TXT_PENDING_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Payment        ,TXT_PENDING_PAYMENT       );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertRequired   ,TXT_PENDING_CERTREQUIRED   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertIssued     ,TXT_PENDING_CERTISSUED     );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettledBy,ifds::SettledBy,TXT_PENDING_SETTLEDBY );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepositDate      ,TXT_PENDING_DATESTAMP      ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::TimeStamp      ,TXT_PENDING_TIMESTAMP      );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OnStmt         ,TXT_PENDING_ONSTMT         );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideTax    ,TXT_PENDING_OVERRIDETAX    );
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::FedRate, ifds::TransRatePUDFed, TXT_PENDING_FEDTAXRATE );
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::ProvRate, ifds::TransRatePUDProv, TXT_PENDING_PROVTAXRATE );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExpGNSettle    ,TXT_PENDING_EXPGNSETTLE    );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_PENDING_SRCOFFUND );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfAccount   ,TXT_PENDING_SRCOFACCOUNT   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GuaranteeDate  ,TXT_PENDING_GUARANTEEDATE  ,IS_DATE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::CreditFreq,ifds::CreditFreqDesc ,TXT_PENDING_CREDITFREQ);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::MaturityDate     ,TXT_PENDING_MATURITYDATE     ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::InterestRate   ,TXT_PENDING_INTERESTRATE   ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchUser     ,TXT_PENDING_BATCHUSER     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchTrace     ,TXT_PENDING_BATCHTRACE     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepId          ,TXT_PENDING_DEPID         );

      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::PayType2, str ,false);
      str.strip().upperCase();

      if( PAYTYPE::EFT != str || !DSTCommonFunctions::codeInList( TTStr, TRADETYPE::PURCHASE ) )
      {
         DisplayItem( IFASTBP_PROC::PENDING_LIST,ifds::ValueDate,TXT_TRANS_VALUEDATE );
      }

      DisplayItem( IFASTBP_PROC::PENDING_LIST,ifds::ACHProcessor,TXT_TRANS_ACHPROC );
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::ACHProcessor, str);
      if( !str.strip().empty() )
      {
         DisplayItem( IFASTBP_PROC::PENDING_LIST,ifds::PayMethod,TXT_TRANS_PAYMETHOD );
      }
      DisplayResponseRequiredValueInAttributeList(IFASTBP_PROC::PENDING_LIST);

      DString dstrPaymentInfo;
      getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::PaymentInfo, dstrPaymentInfo);      
      if(!dstrPaymentInfo.empty())
      {		
         DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::PaymentInfo, TXT_PAYMENT_STATUS );		  
      }
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::RightToCancel,TXT_RIGHT_TO_CANCEL);
      //RDR Advice Provided
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::RDRAdvice,TXT_RDR_ADVICE);

      //DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::PSDAdvice,TXT_PSD_ADVICE);

      //display the G1Impact and G2 Impact for Cross System Transfer In Trades
      if(TTStr == TRADETYPE::CROSS_SYSTEM_TRANSFER_IN)
      {
         DString  dstrTempGrp1Impact( NULL_STRING ), dstrTempGrp2Impact( NULL_STRING );
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::G1Impact, dstrTempGrp1Impact);
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::G2Impact, dstrTempGrp2Impact);
         if( ( !dstrTempGrp1Impact.empty() &&
               ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) >   0.00000000001)||
               ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) < - 0.00000000001) ) ||
               ( !dstrTempGrp2Impact.empty() && 
               ( DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) >  0.00000000001 )||
               DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) < -0.00000000001 ) )
         {
            DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::G1Impact, TXT_G1IMPACT);
            DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::G2Impact, TXT_G2IMPACT);
         }
      }

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExternalInstitution,TXT_EXT_INSTITUTION,ALWAYS_SHOW);

   }    // end purchases/distributions

   // REDEMPTIONS -------------------------------------------------------------------------------------------
   else if(  DSTCommonFunctions::codeInList( TTStr, TRADETYPE::REDEMPTION_LIKE ) )
   {
      // Redemption Code
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RedCode,ifds::RedCode,TXT_PENDING_REDCODE );

      // Allocations
      if( AreThereAllocationInThisPending() )
      {
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      // Gross/Net
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GrossNetMethod,TXT_PENDING_GROSSORNET);

      // Good/Bad
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GoodBad, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_GOODBAD);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::GoodBad.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_GOOD : TXT_PENDING_BAD );
      m_TransDetail.SetItemText(index,1,tmp);   

      //PTS 10023779 - Add fund to/class to values to string key and display for redemptions
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::FundTo     ,TXT_PENDING_FUNDTO     );
      // Class To
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ClassToCode     ,TXT_PENDING_CLASSTOCODE     );

      // Reject Code
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RejCode,ifds::RejCode,TXT_PENDING_REJCODE );
      //pay instr option
      DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::PayInstrOption,  TXT_PAY_INSTRUCT_OPTION);
      // Payment Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::PayType2,ifds::PayType2,TXT_PENDING_PAYTYPE);
      // Address Code
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrCode       ,TXT_PENDING_ADDRCODE       );
      // Address Line
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrLine       ,TXT_PENDING_ADDRLINE       );
      // Override Tax
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideTax    ,TXT_PENDING_OVERRIDETAX    );

      // Federal Tax Rate
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::FedRate, ifds::TransRatePUDFed, TXT_PENDING_FEDTAXRATE );
      // Provincial Tax Rate
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::ProvRate, ifds::TransRatePUDProv, TXT_PENDING_PROVTAXRATE );

      // Order Type + Wire Order Number 
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT );
      m_TransDetail.SetItemText(index,1,tmp);
      if( str == Y )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::WireOrdNum     ,TXT_PENDING_WIREORDNUM     );
      }

       // Fee Rate
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, str, false);
      str.strip();
      DisplayFeeRate( str == Y );

      // Fee in Flat/Percent
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, TXT_PENDING_FLATPERCENT );
      // Order Source
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::OrderSource,ifds::OrderSource ,TXT_PENDING_ORDERSOURCE);
      // Settlement Source
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleSource,ifds::SettleSource,TXT_PENDING_SETTLESOURCE );
      // Settlement Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleType,ifds::SettleType,TXT_PENDING_SETTLETYPE );
      // Batch User
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchUser     ,TXT_PENDING_BATCHUSER     );
      // Batch Trace
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchTrace     ,TXT_PENDING_BATCHTRACE     );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Accountable,ifds::Accountable,TXT_PENDING_ACCOUNTABLE );
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::SettleNetwork, TXT_SETTLE_NETWORK);
	  DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::DilutionLinkNum, TXT_DILUTION_LINK_NUM);
	  DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::FSRVLinkNum, TXT_FSRV_LINK_NUM);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideDSCDesc    ,TXT_PENDING_OVERRIDEDSC    );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideAmt    ,TXT_PENDING_OVERRIDEAMT    ,IS_NUMBER);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SuppressCode,ifds::SuppressCode,TXT_PENDING_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::FlatPercent    ,TXT_PENDING_FLATPERCENT    );
      if( bBELFund )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BELFee         ,TXT_PENDING_BELFEE );
      }
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AdminFeeAmt       ,TXT_PENDING_ADMINFEEAMT      ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ChargeWDFee,     TXT_CHARGE_WD_FEE );			
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ChargeERSTTRFee, TXT_EARLYREDEMPTION_FEE);

      displayADLCharge( TTStr );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::DepositType,ifds::DepositType,TXT_PENDING_DEPOSITTYPE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::ProvSales,ifds::ProvSales,TXT_PENDING_PROVSALES);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ConfirmRequired     ,TXT_PENDING_CONFIRMREQ     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExchRate       ,TXT_PENDING_EXCHRATE       ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Payment        ,TXT_PENDING_PAYMENT       );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertRequired   ,TXT_PENDING_CERTREQUIRED   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertIssued     ,TXT_PENDING_CERTISSUED     );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettledBy,ifds::SettledBy,TXT_PENDING_SETTLEDBY );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepositDate      ,TXT_PENDING_DATESTAMP      ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::TimeStamp      ,TXT_PENDING_TIMESTAMP      );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OnStmt         ,TXT_PENDING_ONSTMT         );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExpGNSettle    ,TXT_PENDING_EXPGNSETTLE    );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_PENDING_SRCOFFUND );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfAccount   ,TXT_PENDING_SRCOFACCOUNT   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GuaranteeDate  ,TXT_PENDING_GUARANTEEDATE  ,IS_DATE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::CreditFreq,ifds::CreditFreqDesc ,TXT_PENDING_CREDITFREQ);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::MaturityDate     ,TXT_PENDING_MATURITYDATE     ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::InterestRate   ,TXT_PENDING_INTERESTRATE   ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExtraCommission,TXT_PENDING_EXTRACOMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SplitComm,TXT_SPLIT_COMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepId          ,TXT_PENDING_DEPID         );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ValueDate,TXT_TRANS_VALUEDATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ACHProcessor,TXT_TRANS_ACHPROC);
      getParent()->getField(this, IFASTBP_PROC::PENDING_LIST, ifds::ACHProcessor, str);
      if( !str.strip().empty() )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::PayMethod,TXT_TRANS_PAYMETHOD);
      }

      // Bank Charge
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST, ifds::BankChrgs, ifds::BankChrgs, TXT_BANKCHARGE);
      DisplayResponseRequiredValueInAttributeList(IFASTBP_PROC::PENDING_LIST);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::PymtRoutingMthd, TXT_PAYMENT_ROUTING_TYPE);

      //display the G1Impact and G2 Impact for Cross System Transfer Out Trades
     if(TTStr == TRADETYPE::CROSS_SYSTEM_TRANSFER_OUT)
     {
          DString  dstrTempGrp1Impact( NULL_STRING ), dstrTempGrp2Impact( NULL_STRING );
          getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::G1Impact, dstrTempGrp1Impact);
          getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::G2Impact, dstrTempGrp2Impact);
          if( ( !dstrTempGrp1Impact.empty() &&
		         ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) >   0.00000000001)||
		         ( DSTCommonFunctions::convertToDouble (dstrTempGrp1Impact) < - 0.00000000001) ) ||
              ( !dstrTempGrp2Impact.empty() && 
		          ( DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) >  0.00000000001 )||
		             DSTCommonFunctions::convertToDouble (dstrTempGrp2Impact) < -0.00000000001 ) )
          {
	         DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::G1Impact, TXT_G1IMPACT);
	         DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::G2Impact, TXT_G2IMPACT);
          }
     }

     DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExternalInstitution,TXT_EXT_INSTITUTION,ALWAYS_SHOW);

   } // end redemptions

   // TRANSFERS/EXCHANGES -----------------------------------------------------------------------------------
   else if(  DSTCommonFunctions::codeInList( TTStr, TRADETYPE::EXCHANGE_LIKE   ) ||
             DSTCommonFunctions::codeInList( TTStr, TRADETYPE::EXCHANGE_LIKE_2 )
       )
   {
      // Redemption Code
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RedCode,ifds::RedCode,TXT_PENDING_REDCODE );

      // Deposit Type
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::DepositType,ifds::DepositType,TXT_PENDING_DEPOSITTYPE);  

      // Allocations
      if( AreThereAllocationInThisPending() )// there are allocations
      {
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      // Good/Bad
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GoodBad, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_GOODBAD);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::GoodBad.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_GOOD : TXT_PENDING_BAD );
      m_TransDetail.SetItemText(index,1,tmp);

      // Reject Code
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RejCode,ifds::RejCode,TXT_PENDING_REJCODE );
      // Fund To
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::FundTo     ,TXT_PENDING_FUNDTO     );
      // Class To
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ClassToCode     ,TXT_PENDING_CLASSTOCODE     );

      // Fund Number To
      DString dstrFundNumber, dstrFund, dstrClass;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FundTo, dstrFund );
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ClassToCode, dstrClass );
      dstWorkSession->GetFundNumber( dstrFund, dstrClass, dstrFundNumber );
      if( !dstrFundNumber.empty() && DisplayThisItem( dstrFundNumber, IS_NUMBER ) )
      {
         CString label;
         label.LoadString(TXT_PENDING_FUNDNUM);
         int index = m_TransDetail.InsertItem(99999, label);
         m_TransDetail.SetItemText(index, 1, dstrFundNumber.c_str());
      }

      bool shouldDisplayXferOutAndXFerIn = 
         (TTStr == TRADETYPE::EXCHANGE || TTStr == TRADETYPE::TRANSFER) && 
         !SplitCommission::isTypeZERO(*(dynamic_cast<DSTCWorkSession *>(getBFWorkSession())));


      // Account To
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::AccountTo,ifds::AcctToName,TXT_PENDING_ACCOUNTTO, IS_INTEGER );

      // Fee Rate
      if (!shouldDisplayXferOutAndXFerIn)
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, str, false);
         str.strip();
         DisplayFeeRate( str == Y );
      }

      // Fee in Flat Rate/Percent
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::FlatPercent    ,TXT_PENDING_FLATPERCENT    );
      // Batch User
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchUser     ,TXT_PENDING_BATCHUSER     );
      // Batch Trace
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchTrace     ,TXT_PENDING_BATCHTRACE     );

      // Wire Order Number
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString( (str == Y) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT );
      m_TransDetail.SetItemText(index,1,tmp);
	  // P0274979-626 : Show Wire Order Num for  Pending Trade (Switch & Transfer)
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::WireOrdNum     ,TXT_PENDING_WIREORDNUM     );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Accountable,ifds::Accountable,TXT_PENDING_ACCOUNTABLE );
      DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExtraCommission,TXT_PENDING_EXTRACOMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SplitComm,TXT_SPLIT_COMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepId          ,TXT_PENDING_DEPID         );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::OrderSource,ifds::OrderSource ,TXT_PENDING_ORDERSOURCE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleType,ifds::SettleType,TXT_PENDING_SETTLETYPE );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleSource,ifds::SettleSource,TXT_PENDING_SETTLESOURCE );
      if( bBELFund )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BELFee         ,TXT_PENDING_BELFEE );
      }
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AdminFeeAmt       ,TXT_PENDING_ADMINFEEAMT      ,IS_NUMBER);

      if (TTStr == XR && !shouldDisplayXferOutAndXFerIn)
      {
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::ExchInFee, TXT_PENDING_EXCHINFEE, IS_NUMBER);
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::ExchInFlatPercent, TXT_PENDING_EXCHINFEETYPE);
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::ExchOutFee, TXT_PENDING_EXCHOUTFEE, IS_NUMBER);
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::ExchOutFlatPrcnt, TXT_PENDING_EXCHOUTFEETYPE);
      }
      if (TTStr == TR || TTStr == XR)
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ChargeERSTTRFee, TXT_PENDING_SHORTTERMTRANSFER_FEE);
      }
      
      if (shouldDisplayXferOutAndXFerIn)
      {
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::Fee, TXT_XFER_OUT_FEE, IS_NUMBER);
         DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::FeeTo, TXT_XFER_IN_FEE, IS_NUMBER);
      }

      displayADLCharge( TTStr );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::ProvSales,ifds::ProvSales,TXT_PENDING_PROVSALES);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ConfirmRequired     ,TXT_PENDING_CONFIRMREQ     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExchRate       ,TXT_PENDING_EXCHRATE       ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrCode       ,TXT_PENDING_ADDRCODE       );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrLine       ,TXT_PENDING_ADDRLINE       );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SuppressCode,ifds::SuppressCode,TXT_PENDING_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Payment        ,TXT_PENDING_PAYMENT       );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::PayType2,ifds::PayType2,TXT_PENDING_PAYTYPE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertRequired   ,TXT_PENDING_CERTREQUIRED   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertIssued     ,TXT_PENDING_CERTISSUED     );

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GrossNetMethod,TXT_PENDING_GROSSORNET);

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettledBy,ifds::SettledBy,TXT_PENDING_SETTLEDBY );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepositDate      ,TXT_PENDING_DATESTAMP      ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::TimeStamp      ,TXT_PENDING_TIMESTAMP      );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OnStmt         ,TXT_PENDING_ONSTMT         );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideDSCDesc    ,TXT_PENDING_OVERRIDEDSC    );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideAmt    ,TXT_PENDING_OVERRIDEAMT    ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideTax    ,TXT_PENDING_OVERRIDETAX    );

      // Federal Tax Rate
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::FedRate, ifds::TransRatePUDFed, TXT_PENDING_FEDTAXRATE );
      // Provincial Tax Rate
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::ProvRate, ifds::TransRatePUDProv, TXT_PENDING_PROVTAXRATE );

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExpGNSettle    ,TXT_PENDING_EXPGNSETTLE    );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_PENDING_SRCOFFUND );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfAccount   ,TXT_PENDING_SRCOFACCOUNT   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GuaranteeDate  ,TXT_PENDING_GUARANTEEDATE  ,IS_DATE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::CreditFreq,ifds::CreditFreqDesc ,TXT_PENDING_CREDITFREQ);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::MaturityDate     ,TXT_PENDING_MATURITYDATE     ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::InterestRate   ,TXT_PENDING_INTERESTRATE   ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::UseEnteredFee, TXT_PENDING_USEENTEREDFEE );
	  DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::PFCrystalisation,TXT_PFCRYSTALISATION);
	  //RDR Advice Provided
	  DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::RDRAdvice,TXT_RDR_ADVICE);
	  DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SDRTExemptCode,TXT_SDRT_EXEMPT_CODE);   
   } // end transfers/exchanges		

   else
   {
      // Allocations
      if( AreThereAllocationInThisPending() )// there are allocations
      {
         tmp.LoadString(ROW_DETAILS_ATTRIBUTES_ALLOCATIONS);
         index=m_TransDetail.InsertItem(99999,tmp);
         m_TransDetail.SetItemData(index,ifds::Allocation.getId());
         tmp.LoadString(IDS_TXT_YES);
         m_TransDetail.SetItemText(index,1,tmp);
      }

      // Order Type
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::OrderType, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_ORDERTYPE);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::OrderType.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_WIRE : TXT_PENDING_DIRECT);
      m_TransDetail.SetItemText(index,1,tmp);
      if( str == Y )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::WireOrdNum     ,TXT_PENDING_WIREORDNUM     );
      }

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Broker,ifds::BrokerName ,TXT_PENDING_BROKERCODE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Branch,ifds::BranchName ,TXT_PENDING_BRANCHCODE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SlsrepCode,ifds::SlsrepName ,TXT_PENDING_SLSREPCODE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::OrderSource,ifds::OrderSource ,TXT_PENDING_ORDERSOURCE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleType,ifds::SettleType,TXT_PENDING_SETTLETYPE );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettleSource,ifds::SettleSource,TXT_PENDING_SETTLESOURCE );
      if( bBELFund )
      {
         DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BELFee         ,TXT_PENDING_BELFEE );
      }
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::FundTo     ,TXT_PENDING_FUNDTO     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ClassToCode     ,TXT_PENDING_CLASSTOCODE     );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::AccountTo,ifds::AcctToName,TXT_PENDING_ACCOUNTTO, IS_INTEGER );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AdminFeeAmt       ,TXT_PENDING_ADMINFEEAMT      ,IS_NUMBER);

      // Fee Flat Percent
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FlatPercent, str, false);
      str.strip();
      DisplayFeeRate( str == Y );

      displayADLCharge( TTStr );

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RedCode,ifds::RedCode,TXT_PENDING_REDCODE );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::DepositType,ifds::DepositType,TXT_PENDING_DEPOSITTYPE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::ProvSales,ifds::ProvSales,TXT_PENDING_PROVSALES);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ConfirmRequired     ,TXT_PENDING_CONFIRMREQ     );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RejCode,ifds::RejCode,TXT_PENDING_REJCODE );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SettleCurrency,TXT_PENDING_SETTLECURRENCY);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExchRate       ,TXT_PENDING_EXCHRATE       ,IS_NUMBER);

      // Good/Bad
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GoodBad, str ,false);
      str.strip();
      tmp.LoadString(TXT_PENDING_GOODBAD);
      index=m_TransDetail.InsertItem(99999,tmp);
      m_TransDetail.SetItemData(index,ifds::GoodBad.getId());
      tmp.LoadString( ( str == Y ) ? TXT_PENDING_GOOD : TXT_PENDING_BAD );
      m_TransDetail.SetItemText(index,1,tmp);

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrCode       ,TXT_PENDING_ADDRCODE       );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AddrLine       ,TXT_PENDING_ADDRLINE       );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SuppressCode,ifds::SuppressCode,TXT_PENDING_CHQSUPCODE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Payment        ,TXT_PENDING_PAYMENT       );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::PayType2,ifds::PayType2,TXT_PENDING_PAYTYPE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertRequired   ,TXT_PENDING_CERTREQUIRED   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::CertIssued     ,TXT_PENDING_CERTISSUED     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExtraCommission,TXT_PENDING_EXTRACOMMISSION);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SplitComm, TXT_SPLIT_COMMISSION);

      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GrossNetMethod,TXT_PENDING_GROSSORNET);

      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SettledBy,ifds::SettledBy,TXT_PENDING_SETTLEDBY );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepositDate      ,TXT_PENDING_DATESTAMP      ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::TimeStamp      ,TXT_PENDING_TIMESTAMP      );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OnStmt         ,TXT_PENDING_ONSTMT         );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::RoundFlag,ifds::RoundFlagDesc,TXT_PENDING_ROUNDFLAG );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideDSCDesc    ,TXT_PENDING_OVERRIDEDSC    );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideAmt    ,TXT_PENDING_OVERRIDEAMT    ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideTax    ,TXT_PENDING_OVERRIDETAX    );
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::FedRate, ifds::TransRatePUDFed, TXT_PENDING_FEDTAXRATE );
      DisplayTaxRates(IFASTBP_PROC::PENDING_LIST, ifds::ProvRate, ifds::TransRatePUDProv, TXT_PENDING_PROVTAXRATE );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ExpGNSettle    ,TXT_PENDING_EXPGNSETTLE    );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfFund,ifds::SrcOfFund,TXT_PENDING_SRCOFFUND );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::SrcOfAccount   ,TXT_PENDING_SRCOFACCOUNT   );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GuaranteeDate  ,TXT_PENDING_GUARANTEEDATE  ,IS_DATE);
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::CreditFreq,ifds::CreditFreqDesc ,TXT_PENDING_CREDITFREQ);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::MaturityDate     ,TXT_PENDING_MATURITYDATE     ,IS_DATE);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::InterestRate   ,TXT_PENDING_INTERESTRATE   ,IS_NUMBER);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchUser     ,TXT_PENDING_BATCHUSER     );
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::BatchTrace     ,TXT_PENDING_BATCHTRACE     );
      DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST,ifds::Accountable,ifds::Accountable,TXT_PENDING_ACCOUNTABLE );
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::BackDatedReason, TXT_BACK_DATED_REASON);
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::DepId          ,TXT_PENDING_DEPID         );
   }

   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::DealDate, TXT_TRANS_DEALDATE, IS_DATE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::DealTime, TXT_TRANS_DEALTIME, IS_TIME);

   DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::ValuationDt, TXT_VALUATION_DATE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::PendTrdContract,TXT_PEND_TRADE_CONTRACT);
   // Display SWIFT items
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::NetworkID,    TXT_PENDING_NETWORKID );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ExtTransNum,  TXT_PENDING_EXTTRANSNUM );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::SendRefNum,   TXT_PENDING_SENDREFNUM );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::PartRefNum,   TXT_PENDING_PARTREFNUM );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::MasterRefNum, TXT_PENDING_MASTERREFNUM );


   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::DeliveryMethod, TXT_DELIVERY_METHOD ); // IN 343484

   DString dstrIndc;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Indc, dstrIndc );
   dstrIndc.strip();
   if (!dstrIndc.empty ())
   {
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Indc           ,TXT_TRANS_INDC);
   }

   if ( TTStr == ED )
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::BorrowedFunds, TXT_BORROWED_FUNDS );

   if ( TTStr == PW )
   {
      DSTCWorkSession *dstWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      SupportedProductsList *pSupportedProductsList = NULL;

      if (dstWorkSession && 
         dstWorkSession->getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
         pSupportedProductsList)
      {
         if (pSupportedProductsList->isLSIFProductActive ())
         {
            DisplayItem (IFASTBP_PROC::PENDING_LIST, ifds::LSIFCode, TXT_LSIF_CWB_REASON);
         }
      }
   }
//PET 1117
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::AltAccount,  TXT_ALTERNATE_ACCOUNT);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::RefNum,  TXT_OTHER_REFERENCE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundWKN,  TXT_WKN);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundISIN,  TXT_ISIN);
   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::Valoren,    TXT_FROM_VALOREN );
   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::CUSIP,      TXT_FROM_CUSIP);
   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::TDCC,       TXT_FROM_TDCC);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundToWKN,	  TXT_TO_WKN);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundToISIN,  TXT_TO_ISIN);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundLFC,     TXT_FUND_LEGACY_CODE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundToLFC,     TXT_FUND_TO_LEGACY_CODE);
   // TRANSFERS/EXCHANGES 
   if(  DSTCommonFunctions::codeInList( TTStr, TRADETYPE::EXCHANGE_LIKE   ) ||
        DSTCommonFunctions::codeInList( TTStr, TRADETYPE::EXCHANGE_LIKE_2 ))
   {
	DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::ToValoren,  TXT_TO_VALOREN );
	DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::ToCUSIP,    TXT_TO_CUSIP);
	DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::ToTDCC,     TXT_TO_TDCC);
   }
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::AcqFeeOption,  TXT_ACQ_FEE_OPTION);
//   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::SettleDateOverriden,  );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FrSettlInstrCode, TXT_SETTLE_INSTR_CODE );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ToSettlInstrCode,  TXT_TO_SETTLE_INSTR_CODE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::FundBrokerCode,  TXT_FUND_BROKER_CODE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::AggregateOption,  TXT_AGG_OPTION);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::BrkSettlDate,  TXT_BROKER_SETTLE_DATE,IS_DATE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::DeliveryNetwork,  TXT_DELIVERY_NETWORK);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::OtherConfirmType, TXT_OTHER_CONFIRM_TYPE, REPLACE_BLANK_BY_NA );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ExternalPrice,  TXT_EXTERNAL_PRICE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ExternalSettleDate,  TXT_EXTERNAL_SETTLE_DATE);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ExternalSettleAmt,  TXT_EXTERNAL_SETTLE_AMT);

// ROA enhancement
   DString roaTransType,transType,amount;
   getParent()->getField( this,ifds::ROATransType,roaTransType );
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST,ifds::TransType,transType, false );
   transType.strip();
   if( DSTCommonFunctions::codeInList( transType, roaTransType ) )
   {
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ROAAmount,  TXT_ROA_AMOUNT);   
   }

   str = I_("");
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::AdjTransNum, str, false );   
   if( str.strip() != NULL_STRING )
   {
        DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::AdjTransNum,TXT_ADJ_TRANS_NUMBER);
   }

   // eusd
   DString eusdParticip;
   bool bEnableSavingsDirectiveBtn = false;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::EUSDParticip, eusdParticip, getParent()->getDataGroupId(), false );

   if ( eusdParticip == I_("Y") && 
        ( DSTCommonFunctions::codeInList( transType, TRADETYPE::PURCHASE_LIKE )            // ED,RC - purchase, reinvest purchase
          ||    DSTCommonFunctions::codeInList( transType, TRADETYPE::EXCHANGE_LIKE   )      // TI,TO,EI,EO,XR,TR,AFTR;
          ||    DSTCommonFunctions::codeInList( transType, TRADETYPE::EXCHANGE_LIKE_2 )      // TI04,TO04,TI08,TO08;
        )
       )
   {
        FundDetailList *pFundDetailList = NULL;
        if ( pdstcWorkSession->getMgmtCo().getFundDetailList(pFundDetailList)  <= WARNING)
        {
            DString fundCode, classCode, tradeDate;

            if (DSTCommonFunctions::codeInList( transType, TRADETYPE::PURCHASE_LIKE ) )
            {
                getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, fundCode );
                getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, classCode );
            }
            else
            {
                getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FundTo, fundCode );
                getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ClassToCode, classCode );
            }

            getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, tradeDate );

            bool isInScope, isLookedThru;	
            isInScope = pFundDetailList->isInScope(fundCode, classCode, tradeDate);
            isLookedThru = pFundDetailList->isLookThru(fundCode, classCode, tradeDate);

            if (isInScope)
            {
                DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::Cost, TXT_TRANS_EUSD_OVERRIDE_COST );
                DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideCost, TXT_TRANS_EUSD_OVERRIDE_COST_LOG   );
            }

            if (isLookedThru)
            {
                DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::TIS, TXT_TRANS_EUSD_OVERRIDE_TIS );
                DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::OverrideTIS, TXT_TRANS_EUSD_OVERRIDE_TIS_LOG   );
            }
        }
   }

    // trade suppress
    DString dstrMCHSRActive;
    DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    if ( NULL != pDSTCWorkSession )
    {
        pDSTCWorkSession->getOption( ifds::MCHSRActive, dstrMCHSRActive, getDataGroupId(), false );

        if (dstrMCHSRActive == I_("Y") )
        {
            DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::MCHFileIndicator,  TXT_MCH_FILE_INDICATOR);
            DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::SecRecFileIndicator, TXT_SEC_REC_FILE_INDICATOR);
        }
    }

   if ( TTStr == AW  && DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
        getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ESGSettle, str, false );
        if ( str.strip().upperCase() == I_("EX"))
        {
            DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ESGSettle, TXT_TRANS_ESG_SETTLE);
        }
   }

   DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::LinkedEntityName,TXT_ASSOCIATED_ENTITY);

   DString dstrAuthorization;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::StcPendTrdAuthorization, dstrAuthorization );
   dstrAuthorization.strip();
   
   if (!dstrAuthorization.empty ())
   {
      DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::StcPendTrdAuthorization, TXT_TRANS_AUTHORIZATION);
   }

   // RESP - QESI - Trade Entry
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::AssocTransId, TXT_ASSOC_TRANS_ID, IS_NUMBER );
   //DisplayCodeDesc(IFASTBP_PROC::PENDING_LIST, ifds::GRRepayReason, ifds::GRRepayReason, TXT_GR_REPAY_REASON );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::GRRepayReason, TXT_GR_REPAY_REASON, IS_TEXT);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::RESPReportHRDC, TXT_REPORT_HRDC_REQ );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::RESPContrDetlTaxYear, TXT_RESP_TAX_YEAR, IS_NUMBER);
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::Tainted, TXT_TAINTED );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::OCRdmYear, TXT_OC_REDM_YEAR, IS_NUMBER );
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::AssistedContrAmt, TXT_ASSISTED_CONTRIB_AMT, IS_NUMBER );

   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::SourceOfTrade,   TXT_SOURCE_OF_TRADE   );
   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::ChannelOfTrade,  TXT_CHANNEL_OF_TRADE  );
   DisplayItem(IFASTBP_PROC::PENDING_LIST , ifds::Platform,		   TXT_PLATFORM );
   DisplayItem(IFASTBP_PROC::PENDING_LIST,	ifds::PSDAdvice,	   TXT_PSD_ADVICE);
   // NSCC Control Number
   NSCCControlNumber (true);
   DisplayItem(IFASTBP_PROC::PENDING_LIST,	ifds::Verified,	   TXT_VERIFIED    );
   DisplayItem(IFASTBP_PROC::PENDING_LIST,	ifds::VerifiedBy,  TXT_VERIFIED_BY );
   DString dstrGuaranteesOverride; 
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::GuaranteesOverride, dstrGuaranteesOverride, false );
   dstrGuaranteesOverride.strip().upperCase();

   if(!dstrGuaranteesOverride.empty() )
   {
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::GuaranteesOverride,TXT_GUARANTEE_OVERRIDE);
   }
   DisplayItem(IFASTBP_PROC::PENDING_LIST,   ifds::CrossSysAcctNum, TXT_CROSS_SYSTEM_ACC_NUM);
   DisplayItem(IFASTBP_PROC::PENDING_LIST,   ifds::AggregationType, TXT_AGGREGATION_TYPE);

   DString dstrDepositType;
	getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::DepositType, dstrDepositType, false); 
   bool bIsMFRTrades = false;
   //don't display the ourceofFundsChecked attribute for MFR trades
   bIsMFRTrades = DSTCommonFunctions::codeInList (TTStr, TRADETYPE::MFR_TARDES );
   if( !bIsMFRTrades && I_("2") != dstrDepositType && DSTCommonFunctions::codeInList (TTStr, TRADETYPE::PURCHASE_LIKE ))
         DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::SourceofFundsChecked, TXT_SOURCE_OF_FUNDS_CHECKED_ATTRB, REPLACE_BLANK_BY_NA );

   if(TTStr == TRADETYPE::REFUND_REDEMPTION)
   {
      DisplayItem(IFASTBP_PROC::PENDING_LIST,ifds::RefundAmtOpt,TXT_REFUND_AMOUNT_OPTION);   
   }

   if( DSTCommonFunctions::codeInList(TTStr,TRADETYPE::MONEY_OUT_TRADES) ) 
   {
	   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::Deconversion, TXT_DECONVERSION);
   }

   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::OrderRouting, TXT_ORDERROUTING);
   
   if (TTStr == TRADETYPE::EXCHANGE || TTStr == TRADETYPE::TRANSFER)
   {
	   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::TradeInDate, TXT_TRADE_IN_DATE);
	   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::ValuationInDt, TXT_VALUATION_IN_DATE);
   }

   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::PricingCode, TXT_PRICING_CODE);

    if (TTStr == TRADETYPE::EXCHANGE || TTStr == TRADETYPE::TRANSFER)
   {
	   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::PriceInCode, TXT_PRICEINCODE_CODE);
   }
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::GateOverrideIndicator, TXT_WAIVEGATING_FLAG);

   if (TTStr == TRADETYPE::PURCHASE)
   {
	   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::RDSPPaymtDate, TXT_RDSP_PAYMENT_DATE);
   }
   DisplayItem(IFASTBP_PROC::PENDING_LIST, ifds::CashDate, TXT_TRANS_CASHDATE,IS_DATE);
   UpdateData(FALSE);
   
   m_bIgnore = false;
}

//************************************************************************************

void TransactionHistoryDlg::PopulateTransDetailsEqualizationAmt( const bool bDisplayEqAmtAndFactor )
{
   DString dstrEqualAmount, dstrCapitalAmount, dstrEqualFactor;
   if( bDisplayEqAmtAndFactor )
   {
      // Equal Amount
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::EqualAmount, dstrEqualAmount );
      if ( !dstrEqualAmount.empty() && DSTCommonFunctions::convertToDouble( dstrEqualAmount ) != 0.0 )
      {
          DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::EqualAmount, TXT_TRANS_EQUALAMT );
      }
      // Equal Factor
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::EqualFactor, dstrEqualFactor );
      if ( !dstrEqualFactor.empty() && DSTCommonFunctions::convertToDouble( dstrEqualFactor ) != 0.0 )
      {
          DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::EqualFactor, TXT_TRANS_EQUALFACTOR );
      }
   }

   // Capital Amount
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CapitalAmount, dstrCapitalAmount );
   if( !dstrCapitalAmount.empty() && DSTCommonFunctions::convertToDouble( dstrCapitalAmount ) != 0.0 )
   {
      DisplayItem( IFASTBP_PROC::TRANS_LIST, ifds::CapitalAmount, TXT_TRANS_CAPITALAMOUNT );
   }
}

//************************************************************************************

void TransactionHistoryDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates() " ) );
   POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
   DString str;
   DString ModUser,ModDate,ProcUser,ProcessDate;

   if( pos != NULL )
   {
      DString *strKey=(DString*)m_lvReportView.GetItemData( m_lvReportView.GetNextSelectedItem( pos ) );
      if( m_bIsPending )
      {
         getParent()->setCurrentListItem(this,IFASTBP_PROC::PENDING_LIST,*strKey);

         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ProcessDate, ProcessDate );
         ProcessDate.stripAll();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::BatchUser, ProcUser );
         ProcUser.strip();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ModDate, ModDate );
         ModDate.strip();
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::ModUser, ModUser );
         ModUser.strip();
         
      }
      else
      {
         getParent()->setCurrentListItem(this,IFASTBP_PROC::TRANS_LIST,*strKey);

         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ModDate, ModDate );
         ModDate.stripAll();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CancelUser, ModUser );
         ModUser.strip();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::ProcessDate, ProcessDate );
         ProcessDate.stripAll();
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OrderUser, ProcUser );
         ProcUser.strip();
      }
      setParameter(MODUSER, ModUser );
      setParameter(MODDATE, ModDate );
      setParameter(PROCESSDATE, ProcessDate );
      setParameter(PROCESSUSER, ProcUser );

      try
      {
         bool bModal = true;   
         E_COMMANDRETURN eRtn = CMD_OK;
         eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, bModal, NULL );
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
   }
}

//************************************************************************************
void TransactionHistoryDlg::ReplaceYandN(DString &str)
{
   CString tmp;

   str.strip();

   if( str == Y )
   {
      tmp.LoadString(IDS_TXT_YES);
      str=tmp.GetBuffer(0);
      tmp.ReleaseBuffer(-1);
   }
   else if( str == N )
   {
      tmp.LoadString(IDS_TXT_NO);
      str=tmp.GetBuffer(0);
      tmp.ReleaseBuffer(-1);
   }
}

//************************************************************************************
void TransactionHistoryDlg::fillDisplayValTag(const BFContainerId& containerId, const BFFieldId &idCode, DString &fieldVal, DString &txtMsg)
{
    if (idCode == ifds::RejCode)
    {
        DString isAllocation;
        getParent()->getField(this, containerId, ifds::Allocation, isAllocation, false);

        if (fieldVal == I_("953") || fieldVal == I_("1753") || fieldVal == I_("1754")){
            if (isAllocation == Y)
            {
                txtMsg = DSTCommonFunctions::getDescription(fieldVal + REJ_ALLOC_TAG, ifds::RejCode);
            }
            else
            {
                DString fundCode, classCode, asOfDate, toFundCode, toClassCode;
                DString fundTag = I_("%FUND%"), classTag = I_("%CLASS%"), asOfDateTag = I_("%ASOF%");
                
                getParent()->getField(this, containerId, ifds::rxFundCode, fundCode, false);
                getParent()->getField(this, containerId, ifds::rxClassCode, classCode, false);
                getParent()->getField(this, containerId, ifds::FundTo, toFundCode, false);
                getParent()->getField(this, containerId, ifds::ClassToCode, toClassCode, false);

                fundCode.upperCase();
                classCode.upperCase();
                toFundCode.upperCase();
                toClassCode.upperCase();
                                
                if (!fundCode.empty() && !classCode.empty())
                {
                    DString originalKey, originalFund, originalClass, newKey;
                    
                    //Get original keys
                    getParent()->getField( this, BF::NullContainerId, FUND_CODE, originalFund);
                    getParent()->getField( this, BF::NullContainerId, CLASS_CODE, originalClass);
                    getParent()->getField( this, BF::NullContainerId, FUND_CLASS_KEY, originalKey);

                    //Get FundStatusDate
                    getParent()->setField( this, BF::NullContainerId, FUND_CODE, toFundCode.empty() ? fundCode:toFundCode);
                    getParent()->setField( this, BF::NullContainerId, CLASS_CODE, toClassCode.empty() ? classCode:toClassCode);
                    getParent()->getField( this, BF::NullContainerId, FUND_CLASS_KEY, newKey);

                    getParent()->setCurrentListItem( this, IFASTBP_PROC::FUND_DETAIL_LIST, newKey.upperCase());
                    getParent()->getField( this, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::FundStatusDate, asOfDate );
                    asOfDate.strip();

                    //Restore
                    getParent()->setField( this, BF::NullContainerId, FUND_CODE, originalFund);
                    getParent()->setField( this, BF::NullContainerId, CLASS_CODE, originalClass);
                    getParent()->setCurrentListItem( this, IFASTBP_PROC::FUND_DETAIL_LIST, originalKey);
                }

                if (asOfDate.empty()) // In case of blank FundStatusDate
                {
                    getParent()->getField(this, containerId, ifds::TradeDate, asOfDate, false);
                }

                DSTCommonFunctions::FormatDate(asOfDate);

                //Money In fund/class
                txtMsg.replace(txtMsg.find(fundTag), fundTag.length(), toFundCode.empty() ? fundCode:toFundCode);
                txtMsg.replace(txtMsg.find(classTag), classTag.length(), toClassCode.empty() ? classCode:toClassCode);
                txtMsg.replace(txtMsg.find(asOfDateTag), asOfDateTag.length(), asOfDate);
            }
        }
    }
}

//************************************************************************************
void TransactionHistoryDlg::DisplayCodeDesc( const BFContainerId& idList, const BFFieldId &idCode, const BFFieldId &idDesc, UINT FieldLabelId, int CodeType, bool bDisplayDash)
{
   //actually we don't care about DescId, because it is taken from DataDictionary
   //but this method shouldn't be called using different fields for code and description
   //if code comes from one field and description comes from another one  (this shouldn' happen anyway) then use DisplayCodeDesc01
   DString str1,str2;

   CString label;
   label.LoadString(FieldLabelId);

   getParent()->getField( this, idList, idCode, str1, false);
   str1.stripAll();
   DisplayThisItem(str1,CodeType);

   if( idCode == idDesc )
   {
      getParent()->getField( this, idList, idCode, str2, true);
   }
   else
   {
      getParent()->getField( this, idList, idDesc, str2, false);
   }
   str2.strip();

   fillDisplayValTag(idList, idCode, str1, str2);

   if( str1.empty() )
   {
      str1 = str2;
   }
   else
   {
      if( ( !str2.empty() ) && ( str1 != str2) )
      {
         if( bDisplayDash )
         {
            str1 += MINUS + str2;
         }
         else
         {
            str1 += I_(" ") + str2;
         }
      }
   }

   if( !str1.empty() )
   {
      int index=m_TransDetail.InsertItem(99999,label);
      m_TransDetail.SetItemText(index,1,str1.c_str());
      m_TransDetail.SetItemData(index,idCode.getId());
   }
}

//************************************************************************************
void TransactionHistoryDlg::DisplayCodeDesc01( const BFContainerId& idList, const BFFieldId &idCode, const BFFieldId &idDesc, UINT FieldLabelId, DString& dstrRes, int CodeType)
{
   DString str1=NULL_STRING ,str2=NULL_STRING;

   CString label;
   label.LoadString(FieldLabelId);

   getParent()->getField( this, idList, idCode, str1);
   str1.stripAll();
   DisplayThisItem(str1,CodeType);

   getParent()->getField( this, idList, idDesc, str2);
   str2.strip();

   if( str1.empty() )
   {
      str1 = str2;
   }
   else
   {
      if( !str2.empty() )
      {
         str1 += MINUS + str2;
      }
   }

   dstrRes = str1;
}

//************************************************************************************
void TransactionHistoryDlg::DisplayTaxRates( const BFContainerId& idList, 
                                             const BFFieldId &idCode, 
                                             const BFFieldId &idDesc, 
                                             UINT FieldLabelId )
{
   // Tax Rate Label
   CString cstrTaxRateLabel;
   cstrTaxRateLabel.LoadString( FieldLabelId );

   // Tax Rate Value
   DString dstrTaxRate;   
   getParent()->getField( this, idList, idCode, dstrTaxRate );
   dstrTaxRate.stripAll();

   if ( DisplayThisItem( dstrTaxRate, IS_NUMBER ) )
   {
		DString dstrOverrideTax;
        getParent()->getField( this, idList, ifds::OverrideTax, dstrOverrideTax);		

		// Tax Rate Type
        DString dstrDesc;
        getParent()->getField( this, idList, idDesc, dstrDesc, false);   

		if ( I_( "No" ) == dstrOverrideTax )         
		{
			if ( idList == IFASTBP_PROC::PENDING_LIST)
			{
				dstrTaxRate = I_( "Default" );
			}
			else if (idList == IFASTBP_PROC::TRANS_LIST)
			{
				if ( I_( "D" ) == dstrDesc.stripAll() )
				{
					dstrTaxRate += I_( "$" );
				}
				else if ( I_( "P" ) == dstrDesc.stripAll() )
				{
					dstrTaxRate += I_( "%" );
				}
			}
		}
        else if ( I_( "Yes" ) == dstrOverrideTax )
        {
            if ( I_( "D" ) == dstrDesc.stripAll() )
            {
                dstrTaxRate += I_( "$" );
            }
            else if ( I_( "P" ) == dstrDesc.stripAll() )
            {
                dstrTaxRate += I_( "%" );
            }
        }
   }

   int iIndex = m_TransDetail.InsertItem(99999, cstrTaxRateLabel);
   m_TransDetail.doSetItemText( iIndex, 1, dstrTaxRate.c_str(),idCode );
   m_TransDetail.SetItemData( iIndex, idCode.getId());
}

//************************************************************************************
void TransactionHistoryDlg::DisplayItem( const BFContainerId& idList, const BFFieldId &idField, UINT FieldLabelId, int ItemType)
{
   DString str;
   int index;

   getParent()->getField( this, idList, idField, str);

   // if it is a number and if it is empty, format it using mask
   DString tmp = str;
   tmp.strip();

   ReplaceYandN( str );

   bool bDisplay = true;
   if( idField == ifds::ValueDate || idField == ifds::ExDate )//probably this logic should apply to all the date values, not only for ValueDate; RK
   {
      DString copyStr(str);
      copyStr.stripAll().stripAll('/');
      if( copyStr.pos(I_("9999") ) >= 0 )
         bDisplay=false;
   }
   else if ( idField == ifds::OrigAmount )
   {
      if( str.strip() == I_("0.00" ) )
      {
         bDisplay=false;
      }
   }
   // Format Time - #### to ##:##
   if( ItemType == IS_TIME )
   {
      if( str.find(I_(":")) == -1 && str.length() == 4 )
      {
         DString dstrTemp;
         dstrTemp = str.left( 2 );
         dstrTemp += I_(":");
         dstrTemp += str.right( 2 );
         str = dstrTemp;
      }
   }
   // Format Time - ###### to ##:##:##
   if( ItemType == IS_TIME_HHMMSS )
   {
      if( str.find(I_(":")) == -1 && str.length() == 6 )
      {
         DString dstrTemp;
         dstrTemp = str.substr (0,2);
         dstrTemp += I_(":");
         dstrTemp += str.substr(2,2);
		 dstrTemp += I_(":");
		 dstrTemp += str.substr(4,2);
         str = dstrTemp;
      }
   }
   //For displaying Empty String as Not Applicable "N/A"
   if(REPLACE_BLANK_BY_NA == ItemType && 0 == str.length())
   {
     CString cstrNotAppl; 
     cstrNotAppl.LoadString(TXT_NOT_APPLICABLE_STRING);     
     str = cstrNotAppl;
     ItemType = IS_TEXT; 
   }

   if( bDisplay && DisplayThisItem( str, ItemType ) )
   {
// IN 371908 - FeePercent may be either Flat or Percent, no flag in Transaction History
/*    if( ( idField == ifds::FeePercent || idField == ifds::Fee || idField == ifds::FeeTo )
          && DSTCommonFunctions::convertToDouble( str ) != 0.0 )
      {
         str += I_(" %");
      }
*/
      CString label;
      label.LoadString(FieldLabelId);
      index=m_TransDetail.InsertItem(99999,label);
      m_TransDetail.doSetItemText(index,1,str.c_str(), idField );
      m_TransDetail.SetItemData(index,idField.getId());
   }
}

void TransactionHistoryDlg::DisplayFeeRate(bool bIsFee)
{
   DString dstrTemp;
   int index;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::Fee, dstrTemp);
   dstrTemp.strip();

   if( DisplayThisItem( dstrTemp, IS_NUMBER ) )
   {
      if( bIsFee )
      {
         dstrTemp = I_("$ ") + dstrTemp;
      }
      else
      {
         dstrTemp += I_(" %");
      }
      CString label;
      label.LoadString( TXT_PENDING_FEE_RATE );
      index=m_TransDetail.InsertItem(99999, label);
      m_TransDetail.doSetItemText(index, 1, dstrTemp.c_str(), ifds::Fee );
      m_TransDetail.SetItemData(index, ifds::Fee.getId());
   }
}

//************************************************************************************
bool TransactionHistoryDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{
   CWaitCursor wait;

   // Pending
   DString dstrTemp;
   getParameter( pPENDING, dstrTemp);
   dstrTemp.stripAll();
   m_bIsPending = (dstrTemp == Y);	

   DString szCommand(szOriginalCommand);
   //GetDlgItem(IDC_BTN_MODIFY)->EnableWindow( FALSE );

   int iItemNumber = 0;
   CString cstrDeductDetlFee, cstrModifyRebook; 
   if (m_bIsPending)
   {
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_LIST );
      cstrDeductDetlFee.LoadString(TXT_FEES);
      cstrModifyRebook.LoadString(TXT_MODIFY);

      GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::PENDING_LIST ) );
   }
   else
   {
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::TRANS_LIST );
      cstrDeductDetlFee.LoadString(TXT_DEDUCTIONS);
      cstrModifyRebook.LoadString(TXT_REBOOK);

      GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, IFASTBP_PROC::TRANS_LIST ) );
   }

   if( szCommand != I_("PendingTradesRefreshed") && szCommand != I_("FromSettlement") && szCommand  != I_("RefreshHistory") )
   {
      getParameter( pACCOUNTNUM, AccountNum );
      getParameter( pTRANSID, TransId );
      getParameter( pSHAREHOLDERNUM, ShareholderNum );
      getParameter( pFUNDCODE, FundCode ); 
      getParameter( pCLASSCODE, ClassCode ); 
      getParameter( pNUMENTRY, NumEntry ); 
      getParameter( pALLFUND, AllFundMode );
      getParameter( pTRANSTYPE, TransType);
      getParameter( pTRANSNUM, TransNum);
      getParameter( pTRADEDATE, TradeDate);
      getParameter( pENTITYID, EntityId ); 
      getParameter( pREQTRANSID, ReqTransid ); 
      getParameter( pINQUIRYONLY, InquiryOnly );
      getParameter( pPENDINGTRADE, PendingTrade);
      getParameter( DISABLEINVINFO, DisableInvInfo );
      getParameter( I_("DisableMsg"), DisableMsg );
      getParameter( I_("Reprint"), Reprint );
      getParameter( I_("TxnCancel"), TxnCancel );

      getParameter( pGROSSNETMETHOD, CrossPrcsGrossNetMethod );

      AccountNum.stripAll();
      FundCode.stripAll().upperCase();
      ClassCode.stripAll().upperCase();
      NumEntry.stripAll();
      AllFundMode.stripAll();

      GetDlgItem( IDC_BTN_MODIFY )->SetWindowText( cstrModifyRebook );
      GetDlgItem( IDC_BTN_MODIFY )->EnableWindow( iItemNumber > 0 );

      PendingFundCode     = FundCode;
      PendingClassCode    = ClassCode;
      PendingTransType    = TransType;
      PendingTransNum     = TransNum;
      PendingTradeDate    = TradeDate;
   }

   GetDlgItem( IDC_BTN_INVENTORY_SUMMARY )->EnableWindow( (DisableInvInfo == I_("Y")) && iItemNumber > 0 );
   GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( false );
   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->EnableWindow( iItemNumber > 0 );	
   GetDlgItem( IDC_BTN_DEDUCT_DETAIL )->SetWindowText( cstrDeductDetlFee );
   GetDlgItem( IDC_BTN_EXT_LINKS )->EnableWindow( false );
   GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( false );
   GetDlgItem( IDC_BTN_REPRINT )->EnableWindow( false );	
   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( iItemNumber > 0 );
   GetDlgItem( IDC_BTN_SAVINGS_DIRECTIVE )->EnableWindow( false );	
   GetDlgItem( IDC_BTN_DILUTION )->EnableWindow( false );	

   if( (szCommand == I_("PendingTradesRefreshed")) && ( !m_bIsPending ) )
      return(true);

   if( szCommand == I_("FromSettlement") )
      m_bFromSettlement = true;

   m_bFromRefresh = true;

   PopulateFundCom();

   OnSelendokCmbFund();
   if (szCommand  == I_("RefreshHistory") )
   {
      DString oldTransId;
      DString listKey;
      getParameter( I_("StartRebook"), rebook_);
      getParameter( I_("CurrenKey"), listKey);
      getParameter( I_("OldTransId"), oldTransId);
      getParameter (I_("Batch"), batch);

      oldTransId.stripAll();
      clearParameters();
      if (rebook_ != Y)
      {
         //rebook is done, and we need to refresh the 'pending trade' rb
         int iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PENDING_LIST );	
         GetDlgItem (IDC_RB_PENDING)->EnableWindow (iItemNumber > 0);
      }
      if( oldTransId != NULL_STRING )
      {
         bool bFind = false;
         DString transNum,transId,selectKey = NULL_STRING;
         const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::TRANS_LIST ));
         if( (*ty) != NULL_STRING )
         {
            do
            {
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, transId );
               transId.stripAll();
               if( transId == oldTransId )
               {
                     selectKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
                     break;
               }
            }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::TRANS_LIST ))) != NULL_STRING );
         }
         if( selectKey != NULL_STRING )
         {
            int iCount = m_lvReportView.GetItemCount();
            if( iCount > 0 )
            {  
               int i = 0;
               DString* ptrKey;
               while ( i < iCount )
               {
                  ptrKey = reinterpret_cast< DString* >( m_lvReportView.GetItemData( i ) );               
                  if( *ptrKey == selectKey )
                  {
                     bFind = true;  
                     break;
                  }            
                  ++i;
               }
               m_lvReportView.SetItemState( bFind? i:0, LVIS_FOCUSED | LVIS_SELECTED,
                     LVIS_FOCUSED | LVIS_SELECTED );

            }
            getParent()->setCurrentListItem(this, IFASTBP_PROC::TRANS_LIST,selectKey);
         }  
         else
         {
            dynamic_cast<AbstractProcess* >(getParent())->trySetCurrentListItem(this, IFASTBP_PROC::TRANS_LIST,listKey);
         }
         rebook_.strip().upperCase();
         if( rebook_ == Y  && bFind )
         {
            PostMessage( WM_COMMAND,IDC_BTN_MODIFY );
         }
      }
   }
   return(true);
}

//************************************************************************************
LRESULT TransactionHistoryDlg::OnUmCanReenter(WPARAM , LPARAM)
{
   m_bCanReenter = true;

   if( m_TransDetail.GetItemCount() )
   {
      WhichDlgShouldBeLaunched(m_TransDetail.GetItemData(0));
   }
   return(0);
}

//************************************************************************************
bool TransactionHistoryDlg::AreThereAllocationInThisPending()
{
   DString str,dstrTransType;
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, dstrTransType,false );
   dstrTransType.strip();
   if( dstrTransType == ALL_FUND_TRANSFER )
   {
      return(false);        
   }
   getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, str );
   str.stripAll();
   if( str.empty() )
   {
      return(true);
   }
   else
   {
      if( dstrTransType == TR || dstrTransType == TO || dstrTransType == EO || dstrTransType == XR )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::FundTo, str );
         str.stripAll();
         if( str.empty() )
         {
            return(true);
         }
      }
   }
   return(false);
}

//************************************************************************************
void TransactionHistoryDlg::OnBtnModify() 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnModify()") );

   CWaitCursor wait;

   POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();

   if (pos != NULL)
   {
      DString caller,
              accountNum (AccountNum),
			  batchUser;


      DString *listKey = 
         (DString*)m_lvReportView.GetItemData (m_lvReportView.GetNextSelectedItem (pos));
      try
      {
         const I_CHAR* cmd;
         bool bModel = isModal();
         //to force a reload if necessary
         if( m_bIsPending )
         {
            getParent()->setCurrentListItem (this, IFASTBP_PROC::PENDING_LIST, *listKey);
            setParameter (MFCAN_IP_PARAM::LIST_KEY, *listKey);
            setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum); 
            setParameter (MFCAN_IP_PARAM::CALLER, I_("ModifyPendingTrade") ); 
            SetMessageStatusBar (TXT_LOAD_TRADES);
            cmd = CMD_BPROC_TRADES;
         }
         else // Rebook
         {
            DString listKey;
            listKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
            if( listKey != NULL_STRING )
            {
               DString transNum,otherFunction,rebookExit;//,adjTransNum;
               CWaitCursor wait; 

               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum,     transNum );
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::OtherFunction, otherFunction ,false);
               otherFunction.strip();
               DString estateAlloc = otherFunction == I_("01")? Y:N;
               DString commRebate = otherFunction == I_("02")? Y:N;
               DString rebookExist,rebookCopy;
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::RebookExist,     rebookExist ,false);
               rebookExist.strip().upperCase();      
			   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::RebookCopy,     rebookCopy ,false);
               rebookCopy.strip().upperCase(); 



               if(isTransactionCancelled())
               {
                  cmd = CMD_BPROC_REBOOK;
                  setParameter( TRANS_REBOOK_PARAM::ACCOUNT_NUM, AccountNum );
                  setParameter( TRANS_REBOOK_PARAM::TRANS_NUM,   transNum );
                  setParameter( TRANS_REBOOK_PARAM::FUND_CODE,   FundCode );
                  setParameter( TRANS_REBOOK_PARAM::CLASS_CODE,  ClassCode );
                  setParameter( I_("Batch"), batch );

                  setParameter( TRANS_REBOOK_PARAM::ESTATE_ALLOC,      estateAlloc );
                  setParameter( TRANS_REBOOK_PARAM::COMMISSION_REBATE, commRebate );
                  setParameter( TRANS_REBOOK_PARAM::REBOOK_EXIST,      rebookExist );
				  setParameter( TRANS_REBOOK_PARAM::REBOOK_COPY,       rebookCopy );
               }
               else
               {
                  cmd = CMD_BPROC_REFUND;
                  setParameter( TRANS_REFUND_PARAM::ACCOUNT_NUM,       AccountNum );
                  setParameter( TRANS_REFUND_PARAM::TRANS_NUM,         transNum );
                  setParameter( TRANS_REFUND_PARAM::FUND_CODE,         FundCode );
                  setParameter( TRANS_REFUND_PARAM::CLASS_CODE,        ClassCode );
                  setParameter( I_("Batch"), batch );

                  setParameter( TRANS_REFUND_PARAM::ESTATE_ALLOC,      estateAlloc );
                  setParameter( TRANS_REFUND_PARAM::COMMISSION_REBATE, commRebate );
//                  setParameter( TRANS_REFUND_PARAM::REBOOK_EXIST,      rebookExist );
               }
               bModel = true;

            }
         }
         switch (invokeCommand ( getWorkSession(), 
                                 cmd, 
                                 PROC_NO_TYPE, 
                                 bModel, 
                                 NULL ))
         {
            case CMD_OK:
            case CMD_CANCEL:
            case CMD_MODELESS_INPROCESS:
               break;
            default:
               // Display error
               ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
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
   SetMessageStatusBar (NULL_STRING);
}

//************************************************************************************


bool TransactionHistoryDlg::isTransactionCancelled()
{
   bool retVal = false;
   
   DString strCancelled;
   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cancelled, strCancelled, false );
   retVal = strCancelled.strip().upperCase() == Y;
   
   return retVal;
}


void TransactionHistoryDlg::OnBtnAwd() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNAWD );

   CriteriaVector criteriaList;
   DString dstrNetworkID, dstrExtTransNum, dstrAWDObjectID;
   getParent()->getField( this, m_bIsPending ? IFASTBP_PROC::PENDING_LIST : IFASTBP_PROC::TRANS_LIST, 
      ifds::NetworkID, dstrNetworkID, false );
   getParent()->getField( this, m_bIsPending ? IFASTBP_PROC::PENDING_LIST : IFASTBP_PROC::TRANS_LIST, 
      ifds::ExtTransNum, dstrExtTransNum, false );
   if( dstrNetworkID == I_("AWD") )
   {
      int pos;
      pos = dstrExtTransNum.find(  I_CHAR('-') );
      if (pos != -1) 
      {        
         dstrAWDObjectID = dstrExtTransNum.substr(0, pos);
      }
   }

   if (m_AwdActive != AWD_SESSION) {

	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      if ( NULL != pDSTCWorkSession ) 
      {

		DString dstrAWDPortalURL;
		pDSTCWorkSession->getOption(ifds::AWDPortalURL, dstrAWDPortalURL, BF::HOST);
		if(!dstrAWDPortalURL.strip().empty())
		{
		  setParameter(MFCAN_IP_PARAM::CALLER, ALLOCATIONSPROC::TRANS_HIST);
		  setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum); 
		  // We would use TRANS_NUM param to pass EXternal Transaction Number to AWD History Browser process
		  setParameter(MFCAN_IP_PARAM::TRANS_NUM, dstrExtTransNum);

		  switch (invokeCommand (getParent(), CMD_BPROC_AWDHISTORY_BROWSER, PROC_NO_TYPE , true, NULL))
		  {
			  case CMD_OK:
			  case CMD_CANCEL:
			  case CMD_MODELESS_INPROCESS:
				  break;
			  default:
				  // Display error
				  ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
				  break;		
		  }
		}
		else
		{		
			MFAccount* pMFAccount = NULL;
			if ( pDSTCWorkSession->getMFAccount (getDataGroupId(), AccountNum, pMFAccount) <= WARNING && pMFAccount )
			{

				AWDHistoryWorkList* awdWorkList = NULL;
				if (dstrAWDObjectID!=NULL_STRING) {
				   awdWorkList = new AWDHistoryWorkList(*pMFAccount);
				   awdWorkList->init(((CDSTCView*)GetMainView())->lookupWork(AccountNum, dstrAWDObjectID));
				}
				pMFAccount->setAWDHistroyWorkList(awdWorkList);

				setParameter(MFCAN_IP_PARAM::CALLER, ALLOCATIONSPROC::TRANS_HIST);
				setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum); 
				setParameter(MFCAN_IP_PARAM::TRANS_NUM, TransNum); 

				switch (invokeCommand (getParent(), CMD_BPROC_AWDHISTORY, PROC_NO_TYPE , true, NULL))
				{
				case CMD_OK:
				case CMD_CANCEL:
				case CMD_MODELESS_INPROCESS:
				   break;
				default:
				   // Display error
				   ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
				   break;
				}

				if (awdWorkList!=NULL) {
				   delete awdWorkList;
				}
				pMFAccount->setAWDHistroyWorkList(NULL);
			}
		}
      }
      return;
   }

   DString dstrAwdSourcePtr = getSession()->getSessionData( I_("_AwdInterface_Ptr_") );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *)dstrAwdSourcePtr.asInteger();

   if( !pAwdInterface->isLoggedOn() )
   { // In case user is no longer logged into AWD
      m_AwdActive = NO_AWD;
      return;
   }

   if( !dstrAWDObjectID.empty() )
   {
      DSTCAWDSession* pSession = dynamic_cast<DSTCAWDSession* >(getSession() );
      if( pSession )
      {
         if( pSession->lookupAWDImageByObjectId( dstrAWDObjectID ) > WARNING )
         {
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
      }
   }
}

//************************************************************************************
void TransactionHistoryDlg::OnBtnSettlement() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSettlement" ) ); 

   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_SETTLEMENT );

   E_COMMANDRETURN eRtn = CMD_OK;
   try
   {
      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();

      if (pos != NULL)
      {
        DString strTransId;
        getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, strTransId );
        setParameter( pACCOUNTNUM, AccountNum );
        setParameter( pTRANSID, strTransId );
        setParameter( FROMSCR, TRANSACTION );

        bool bModal = isModal();
        eRtn = invokeCommand( getParent(), CMD_BPROC_SETTLEMENT, PROC_NO_TYPE,
                              bModal, NULL );
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


//************************************************************************************
void TransactionHistoryDlg::OnBtnSettlLocationInstr()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSettlLocationInstr" ) );

   CWaitCursor wait;
   try
   {
        POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	
        if( pos != NULL )
        {
            DString *dstrKey = (DString*)m_lvReportView.GetItemData( m_lvReportView.GetNextSelectedItem( pos ) );

            DString dstrPending, dstrFundCode, dstrClassCode;
            if ( !m_bIsPending )	
            {
                dstrPending = I_( "N" );
                getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,  dstrFundCode );
                dstrFundCode.stripAll().upperCase();
                getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, dstrClassCode );
                dstrClassCode.stripAll().upperCase();					
            }
            else
            {
                dstrPending = I_( "Y" );
            }

            setParameter( TRANS_SETTLEMENT_LOCATION::ACCOUNT,         AccountNum );
            setParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,     CLASSNAME );
            setParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY, dstrPending );
            setParameter( TRANS_SETTLEMENT_LOCATION::MAIN_LIST_KEY,   *dstrKey );
            setParameter (I_("Side"), I_("From"));


            switch( invokeCommand( getParent(), 
					 				        CMD_BPROC_SETTLEMENT_LOCATION_TRADE, 
									        PROC_NO_TYPE , 
									        true, 
									        NULL ) )
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
}


//************************************************************************************
void TransactionHistoryDlg::OnBtnDeductDetail()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDeductDetail" ) );

   CWaitCursor wait;   
   try
   {
       POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
      if( pos != NULL )
      {
        if (!getParent ()->send (this, !m_bIsPending ? I_("DeductDetail") : I_("Fees")))
        {
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
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
}

//************************************************************************************

bool TransactionHistoryDlg::isSelectionSpecified()
{
   if (AccountNum.empty())
      return false;
   if(m_bIsPending)
   {
      if ( PendingTransType.empty() || PendingTransNum.empty() || PendingTradeDate.empty() )
      return false;
   }//else transhistory
   else if (TransId.empty())
      return false;
   return true;
}

//************************************************************************************

void TransactionHistoryDlg::PrefixWithZero(DString& dstrAmount)
{
   if( dstrAmount.left( 1 ) == I_(".") || dstrAmount.left( 1 ) == I_(",") )
   {
      dstrAmount = I_("0") + dstrAmount;
   }
}

//************************************************************************************
void TransactionHistoryDlg::enableAuthorizationButton (const BFContainerId& idContainer)
{
	DString dstrEnableTradeAuthorization, dstrEnableTradeRestrictionFields;
	bool bEnable;
	
	getParent()->getField(this, idContainer, ifds::EnableTradeAuthorization, dstrEnableTradeAuthorization);
	getParent()->getField(this, idContainer, ifds::EnableTradeRestrictionFields, dstrEnableTradeRestrictionFields);
	
	bEnable = (dstrEnableTradeAuthorization == Y) || (dstrEnableTradeRestrictionFields == Y);

	GetDlgItem (IDC_BTN_AUTHORIZATION)->EnableWindow (bEnable);		

   if (FromScr == FROM_AWD && GetDlgItem(IDC_BTN_AUTHORIZATION)->IsWindowEnabled())
   {
	    PostMessage(WM_COMMAND,IDC_BTN_AUTHORIZATION);
		FromScr = NULL_STRING;
   }
}

//************************************************************************************
void TransactionHistoryDlg::enableSettlementLocInstr( const BFContainerId& idContainer, 
																	   const BFFieldId &idCodeAccountTo )
{
	bool blFromClearingAccount = false, 
		  blToClearingAccount   = false;

	DString dstrApplicableTransType = I_( "All Fund Transfer,Exchange,Exchange Out,Exchange In,Purchase,Redemption,Transfer,Transfer Out,Transfer In" );
    DString dstrTransType = NULL_STRING;
	getParent()->getField( this, idContainer, ifds::TransType,  dstrTransType );   

	//if ( dstrApplicableTransType.find( dstrTransType ) != DString::npos )
    if ( DSTCommonFunctions::codeInList( dstrTransType, dstrApplicableTransType ) )	
	{		
		DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		if ( NULL != pDSTCWorkSession )
		{						
			MFAccount *pMFAccount = NULL;				
			// Check Account From
			if ( 0 != AccountNum.stripAll().length() &&
				  pDSTCWorkSession->getMFAccount( getDataGroupId(), 
															 AccountNum, 
															 pMFAccount ) <= WARNING &&
				  NULL != pMFAccount ) 
			{									
				if ( pMFAccount->isClearingAcount( getDataGroupId() ) &&
					  pMFAccount->hasSettlementLocation( getDataGroupId() ) )
				{				
					DString dstrPayType;					
					getParent()->getField( this, idContainer, ifds::PayType2, dstrPayType );
					if ( ( I_( "Redemption" ) == dstrTransType || I_( "Purchase" ) == dstrTransType ) &&
						  I_( "Clearing" ) == dstrPayType.stripAll() )
                    {
						blFromClearingAccount = true;
                    }
					else if ( I_( "Redemption" ) != dstrTransType && I_( "Purchase" ) != dstrTransType )
                    {
						blFromClearingAccount = true;					
				}			
			}				
			}				
			if ( blFromClearingAccount )
				setParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, I_( "Y" ) );
			else
				setParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, I_( "N" ) );
		
			// Check Account To 			
			if ( dstrTransType != I_( "Purchase" ) && dstrTransType != I_( "Redemption" ) )
			{
				pMFAccount = NULL;
				DString dstrAccountTo;
				getParent()->getField(this, idContainer, idCodeAccountTo, dstrAccountTo );
				if ( 0 != dstrAccountTo.stripAll().length() &&
					  pDSTCWorkSession->getMFAccount( getDataGroupId(), 
																 dstrAccountTo, 
					   										 pMFAccount ) <= WARNING &&
					  NULL != pMFAccount ) 
				{
					if ( pMFAccount->isClearingAcount( getDataGroupId() ) &&
						  pMFAccount->hasSettlementLocation( getDataGroupId() ) )
					{					
						blToClearingAccount = true;
					}				
				}
			}
			
			if ( blToClearingAccount )
				setParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT, I_( "Y" ) );
			else
				setParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT, I_( "N" ) );
		}			
	}

	if ( blFromClearingAccount || blToClearingAccount )
	{
		GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( true );		
	}
	else
	{	
		GetDlgItem( IDC_BTN_SETT_LOC )->EnableWindow( false );		
	}
}

//************************************************************************************
void TransactionHistoryDlg::displayADLCharge( const DString &dstrTransType )
{
    // This function is called only for Pending, so TransType could be ED, PW, XR, TR, AFTR, AF91
    DString dstrADLApplicable, dstrADLTransTypeCodeList;
    dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::ADLevyFee,          dstrADLApplicable,        getDataGroupId(), false ) ;
    dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::ADLevyFeeTransType, dstrADLTransTypeCodeList, getDataGroupId(), false ) ;
    dstrADLTransTypeCodeList.strip().upperCase();

    if ( I_( "Y" ) == dstrADLApplicable.stripAll() &&
            dstrADLTransTypeCodeList.find( dstrTransType ) != DString::npos )
    {
        DisplayItem( IFASTBP_PROC::PENDING_LIST, ifds::ADLFeeCharge, TXT_PENDING_CHARGE_ADL_FEE );
    }
}

//******************************************************************************
void TransactionHistoryDlg::OnBtnInvSummary() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnInvSummary" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
      if( pos != NULL )
      {
         DString dstrFundCode, dstrClassCode ;
         CWaitCursor wait; 
         SetMessageStatusBar( TXT_LOAD_INVENTORY );
         if ( m_bIsPending )
         {
            getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxFundCode, dstrFundCode );
            getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::rxClassCode, dstrClassCode );
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode, dstrFundCode );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, dstrClassCode );
            if( dstrFundCode ==CASH )
            {
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrFund, dstrFundCode );
               getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TfrClass, dstrClassCode );
            }
         }
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();

         setParameter( INV_SUMMARY::ACCOUNT_NUM, AccountNum );
         setParameter( INV_SUMMARY::FUND_CODE, dstrFundCode );
         setParameter( INV_SUMMARY::CLASS_CODE, dstrClassCode );

         eRtn = invokeCommand( getParent(), CMD_BPROC_INVENTORY_SUMMARY, PROC_NO_TYPE, false, NULL );
         SetMessageStatusBar( NULL_STRING );
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
void TransactionHistoryDlg::OnBtnTransactionExternalLinks() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnTransactionExternalLinks" ) );

   CWaitCursor wait;   
   try
   {
      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
      if( pos != NULL )
      {
        if (!getParent ()->send( this, I_( "TransactionExternalLinks" ) ) )
        {
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
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
}

//******************************************************************************
void TransactionHistoryDlg::OnBtnInvClawbackInfo() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnInvClawbackInfo" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
      if( pos != NULL )
      {
        DString dstrTransId;
        CWaitCursor wait; 

        getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, dstrTransId );
      
        setParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER, AccountNum );
        setParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, ShareholderNum );
        setParameter( INV_DETL_DEDUCT::TRANS_ID, dstrTransId );

        eRtn = invokeCommand( getParent(), CMD_BPROC_INVENTORY_DETAIL_DEDUCTION, PROC_NO_TYPE, true, NULL );
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

void TransactionHistoryDlg::OnBtnInvestInfo()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnInvestInfo" ) );

    E_COMMANDRETURN eRtn = CMD_OK;
	DString transId;
    BFContainerId contId;
	
    if (m_bIsPending)
        contId = IFASTBP_PROC::PENDING_LIST;
    else
        contId = IFASTBP_PROC::TRANS_LIST;

	getParent()->getField(this, contId, ifds::TransId, transId, false);
	transId.stripAll();

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	DString dstrEntityName;
    dstWorkSession->getFirstSequenced01AccountholderEntityName(getDataGroupId(), AccountNum, dstrEntityName);

    CString cstrInvestInfoAcctNum,cstrName;
    cstrInvestInfoAcctNum.LoadString(TXT_INVEST_INFO_ACCT_NUM);
    cstrName.LoadString(TXT_ACCT_HOLDER_NAME);
    
	DString screenTitle = DString(cstrInvestInfoAcctNum) + AccountNum;
    screenTitle += DString(cstrName) + dstrEntityName;

    DString urlParamsIDI;
	addIDITagValue(urlParamsIDI, I_("AccountNum"), AccountNum);
	addIDITagValue(urlParamsIDI, I_("TransId"), transId);
	addIDITagValue(urlParamsIDI, I_("screen"), I_("AmountInventory"));
    addIDITagValue(urlParamsIDI, I_("from_screen"), I_("TransactionHistoryDlg"));
	setParameter (I_("UrlParams"), urlParamsIDI);
	setParameter (I_("BrowserTitle"), screenTitle );
	
    try
    {
        bool bModal = false;   // Default to modeless
        E_COMMANDRETURN eRtn;
        eRtn = invokeCommand (getParent(), CMD_BPROC_INVEST_INFO, PROC_NO_TYPE, true, NULL);
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
void TransactionHistoryDlg::displayTransDec(const DString& dstrDecimalTypeDesc)
{
   int index = m_TransDetail.InsertItem(99999, dstrDecimalTypeDesc.c_str());
   CString cstrYes;
   cstrYes.LoadString(TXT_YES_TXT);
   DString strValue = DString(cstrYes);
   m_TransDetail.SetItemText(index,1, strValue.c_str());
   m_TransDetail.SetItemData(index,-1);

}

//******************************************************************************
void TransactionHistoryDlg::OnBtnTrxnCancelation()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnTrxnCancelation" ) ); 

   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_TRANSCANCEL );

   E_COMMANDRETURN eRtn = CMD_OK;
      try
   {
      DString strTransNum,
         cashDivPaidAfter,
         transType, 
         tradeDate, 
         dstrIndc, 
         fundCode, 
         classCode, 
         dstrSWPSettleESGElig, 
         dstrSettleDate,
         dstrRecptIssued, 
         grantExists,
         trfResubmit,
         isAGrantTrade,
         dstrTransId,
         dstrSettleBatch;

      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum,         strTransNum,          false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CashDivPaidAfter, cashDivPaidAfter,     false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType,        transType,            false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate,        tradeDate,            false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,       fundCode,             false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode,      classCode,            false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SWPSettleESGElig, dstrSWPSettleESGElig, false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate,       dstrSettleDate,       false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::RecptIssued,      dstrRecptIssued,      false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Indc,             dstrIndc,             false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::GrantExists,      grantExists,          false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TrfResubmit,      trfResubmit,          false );
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::IsAGrantTrade,    isAGrantTrade,        false );
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TransId,          dstrTransId,          false );
      getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::SettleBatch,      dstrSettleBatch,          false );

      transType.strip().upperCase();
      cashDivPaidAfter.strip().upperCase();

      setParameter( pTRANSNUM,                        strTransNum );
      setParameter( FROMSCR,                          TRANSACTION );
      setParameter( TRANSCANCEL::ACCOUNT_NUM,         AccountNum );
      setParameter( TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter );
      setParameter( I_("TRANSTYPE"),                  transType );
      setParameter( TRANSCANCEL::TRADE_DATE,          tradeDate );
      setParameter( TRANSCANCEL::FUND,                fundCode );
      setParameter( TRANSCANCEL::CLASS,               classCode );
      setParameter( I_("SWPSETTLEESGELIG"),           dstrSWPSettleESGElig );
      setParameter( INDC,                             dstrIndc);

      setParameter( I_( "TransSettleDate" ), dstrSettleDate );
      setParameter( I_( "RecptIssued"),dstrRecptIssued);
      setParameter( I_( "GrantExists"), grantExists);
      setParameter( I_( "TrfResubmit"), trfResubmit);
      setParameter( I_( "IsAGrantTrade"), isAGrantTrade);
      setParameter( I_( "TransactionId"), dstrTransId);
      setParameter( I_( "SettleBatch"), dstrSettleBatch);

      bool bModal = isModal();
      eRtn = invokeCommand( getParent(), 
                            CMD_BPROC_TRANS_CANCEL, 
                            PROC_NO_TYPE, 
                            bModal, 
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
void TransactionHistoryDlg::OnBtnTrxnDilution()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDilution" ) ); 

   CWaitCursor wait;   
   SetMessageStatusBar( TXT_LOAD_DILUTION );	//Change to load dilution after get resource
   E_COMMANDRETURN eRtn = CMD_OK;

   try
   {
       POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
       if( pos != NULL )
       {
          DString dstrTransId, dstrTransNum, dstrTradeDate, dstrSettleDate, dstrTransType;
          getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId,    dstrTransId );
		  getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum,    dstrTransNum, false );
          getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate,  dstrTradeDate, false );
          getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::SettleDate, dstrSettleDate, false );
          dstrTransId.strip();

		  if( m_bIsPending )
		  {
			 getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransType, dstrTransType, false );
		  }
		  else {
			 getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransType, dstrTransType, false );
		  }

          setParameter( pTRANSID, dstrTransId );
		  setParameter( pTRANSNUM, dstrTransNum );
          setParameter( FROMSCR, TRANSACTION );
          setParameter( I_( "TransTradeDate" ),  dstrTradeDate );
          setParameter( I_( "TransSettleDate" ), dstrSettleDate );
		  setParameter(pTRANSTYPE,  dstrTransType.stripAll().upperCase() );

          DString dstrAllowDilution;
          getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::AllowModifyDilution, dstrAllowDilution, false );
          setParameter( I_("AllowModify"), dstrAllowDilution );

          eRtn = invokeCommand( getParent(), CMD_BPROC_DILUTION, PROC_NO_TYPE, isModal(), NULL );
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
void TransactionHistoryDlg::OnBtnReprint()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnReprint" ) ); 

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
      if( pos != NULL )
      {
        DString dstrTransId, dstrFund, dstrClass;
        CWaitCursor wait; 

        getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId,     dstrTransId );
        getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,  dstrFund );
        getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, dstrClass );

        setParameter( CONFIRM_REPRINT::ACCOUNTNUM, AccountNum );
        setParameter( CONFIRM_REPRINT::TRANSID,    dstrTransId );
        setParameter( CONFIRM_REPRINT::FUND,       dstrFund );
        setParameter( CONFIRM_REPRINT::CLASS,      dstrClass );

        eRtn = invokeCommand( getParent(),
                              CMD_BPROC_OPC_CONFIRM_REPRINT, 
                              PROC_NO_TYPE,
                              true,
                              NULL );
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
//*****************************************************************************
void TransactionHistoryDlg::OnBtnInternalLink()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnInternalLink" ) ); 
   try
   {

      E_COMMANDRETURN eRtn = CMD_CANCEL;
      DString listKey;
      listKey = getParent()->getCurrentListItemKey(this,IFASTBP_PROC::TRANS_LIST);
      if( listKey != NULL_STRING )
      {
         DString transNum;
           CWaitCursor wait; 
         getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, 
                     ifds::TransNum,     transNum );
         setParameter( TRANS_LINK_PARAM::ACCOUNT_NUM, AccountNum );
         setParameter( TRANS_LINK_PARAM::TRANS_NUM, transNum );
         bool bModal = true;
         E_COMMANDRETURN eRtn = CMD_OK;
//         SetMessageStatusBar( IDS_LOADING_INTERNAL_LINK );
         eRtn = invokeCommand( getParent(), 
                               CMD_BPROC_TRANS_LINK, 
                               PROC_NO_TYPE, 
                               bModal, 
                               NULL );
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
void TransactionHistoryDlg::OnBtnSavingsDirective()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSavingsDirective" ) ); 

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
      if( pos != NULL )
      {
            DString dstrTransId, dstrFund, dstrClass, dstrTradeDate,
                tisType, costType, tis, cost, eusdOverrideVersion;
            CWaitCursor wait; 

            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId,     dstrTransId, false );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,  dstrFund, false );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode, dstrClass, false );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate,   dstrTradeDate, false );


            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::CostType,    costType, false);
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TISType,     tisType, false );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TIS,         tis, false );
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::Cost,        cost, false);
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::EUSDOverrideVersion, eusdOverrideVersion, false);

            setParameter( SAVINGS_DIRECTIVE::ACCOUNTNUM, AccountNum);
            setParameter( SAVINGS_DIRECTIVE::TRANSID, dstrTransId );
            setParameter( SAVINGS_DIRECTIVE::FUND, dstrFund );
            setParameter( SAVINGS_DIRECTIVE::CLASS, dstrClass );
            setParameter( SAVINGS_DIRECTIVE::TIS, tis );
            setParameter( SAVINGS_DIRECTIVE::TIS_TYPE, tisType );
            setParameter( SAVINGS_DIRECTIVE::COST_TYPE, costType );
            setParameter( SAVINGS_DIRECTIVE::COST, cost );
            setParameter( SAVINGS_DIRECTIVE::VERSION, eusdOverrideVersion);
            setParameter( SAVINGS_DIRECTIVE::TRADEDATE, dstrTradeDate );

            eRtn = invokeCommand( getParent(),
                                         CMD_BPROC_SAVINGS_DIRECTIVE, 
                                         PROC_NO_TYPE,
                                         isModal (),
                                         NULL );
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
//************************************************************************************
void TransactionHistoryDlg::NSCCControlNumber (bool isPending)
{
    DString dstrNSCCCompliant;

    DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    dstWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false );

    if (dstrNSCCCompliant == I_("N"))
        return;

    CString label;
    label.LoadString(TXT_NSCC_CONTROL_NUMBER);
    int	index = m_TransDetail.InsertItem (99999, label);
    m_TransDetail.SetItemData(index,ifds::NSCCControlNumber.getId());

    DString dstrNSCCControlNumber;
    getParent()->getField( this, isPending ? IFASTBP_PROC::PENDING_LIST : IFASTBP_PROC::TRANS_LIST, ifds::NSCCControlNumber, dstrNSCCControlNumber ,false);
    dstrNSCCControlNumber.strip();

    if (dstrNSCCControlNumber.empty ())
        dstrNSCCControlNumber = NA;

    m_TransDetail.SetItemText(index,1, dstrNSCCControlNumber.c_str ());
}


//******************************************************************************
void TransactionHistoryDlg::OnBtnPaymentSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnPaymentSearch")); 

   CWaitCursor wait;   
   SetMessageStatusBar (TXT_LOAD_PAYMENT_SEARCH);

   try
   {
      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   

      if (pos != NULL)
      {
         DString transNum;
         getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, transNum);
         transNum.strip();

         DString urlParamsIDI;

         addIDITagValue (urlParamsIDI, I_("rangeStart"), I_("1"));
         addIDITagValue (urlParamsIDI, I_("rangeEnd"), I_("25"));
         addIDITagValue (urlParamsIDI, I_("searchType"), I_("TransNumber"));
         addIDITagValue (urlParamsIDI, I_("searchValue"), transNum);
         //IN2958740 - add tag to disable Details button On Pay Search if TransactionHist Dlg calls
         addIDITagValue (urlParamsIDI, I_("GUICaller"), I_("TransactionHistoryDlg")); 
		 addIDITagValue (urlParamsIDI, I_("screen"), I_("PaymentInformation"));                  
         
		 CString cstrPaySearch;
         cstrPaySearch.LoadString(TXT_PAYMNT_SEARCH);
		 setParameter( I_("BrowserTitle"), DString(cstrPaySearch) + AccountNum);
		 setParameter( I_("from_screen"), I_("TransactionHistoryDlg"));
         setParameter (I_("UrlParams"), urlParamsIDI);         
         
         switch (invokeCommand ( getParent(), 
                                 CMD_BPROC_PAYMENT_SEARCH, 
                                 PROC_NO_TYPE, 
                                 isModal(), 
                                 NULL))
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
void TransactionHistoryDlg::OnBtnPayInstruct ()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnPayInstruct" ) ); 

   CWaitCursor wait;   
   SetMessageStatusBar (TXT_LOAD_PAY_INSTRUCT);
   E_COMMANDRETURN eRtn = CMD_OK;

   try
   {
       POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();	   
       if (pos != NULL)
      {
         DString transNum,
            listKey;

         if (m_bIsPending)
         {
            getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, transNum);
            listKey = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::PENDING_LIST);
         }
         else
         {
            getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, transNum);
            listKey = getParent()->getCurrentListItemKey (this,IFASTBP_PROC::TRANS_LIST);
         }
         transNum.strip();

         setParameter (MFCAN_IP_PARAM::TRANS_NUM, transNum);
         setParameter (MFCAN_IP_PARAM::CALLER, m_bIsPending ? I_("PendingTransaction") : I_("Transaction"));
         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum);
         setParameter (MFCAN_IP_PARAM::LIST_KEY, listKey);

         eRtn = invokeCommand (getParent(), CMD_BPROC_TRADE_PAYMENT_INSTRUCTIONS, PROC_NO_TYPE, true, NULL);
         switch (eRtn)
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
void TransactionHistoryDlg::OnBtnHistory()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistory" ) ); 
   
   HISTORICAL_VECTOR historicalVector;
   DString dstrPendingRid, dstrKeyIDI(I_("")), dstrTransNum = TransNum;

   //getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::PendingRid, dstrPendingRid );
   //getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, dstrTransNum );
   
    if(dstrTransSeq.empty())
      dstrTransSeq = I_("0");
      
   addIDITagValue (dstrKeyIDI, I_("TransNum"), dstrTransNum);
   addIDITagValue (dstrKeyIDI, I_("TransSeq"), dstrTransSeq);
   
   HistoricalElement element( dstrPendingRid, I_("INTDTL"), dstrKeyIDI );
   historicalVector.push_back(element);
   DString dstrElementPtr = DString::asString((int)&historicalVector);
   setParameter(I_("TYPE"), I_("MULTI" ));
   setParameter(I_("HISTORICAL_VECTOR"), dstrElementPtr);
   setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum);
   E_COMMANDRETURN eRtn = invokeCommand (getParent(), 
         CMD_BPROC_HISTORICAL_INFO, PROC_NO_TYPE, false, NULL);
   switch (eRtn)
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

//******************************************************************************
void TransactionHistoryDlg::OnBtnAuthorization()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAuthorization" ) ); 
   
	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
		if( pos != NULL )
		{
			DString listKey;

			if (m_bIsPending)
			{
				listKey = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::PENDING_LIST);
			}
			else
			{
				listKey = getParent()->getCurrentListItemKey (this,IFASTBP_PROC::TRANS_LIST);
			}
         
			setParameter (PENDPROCRECORD_TYPE, m_bIsPending ? I_("Pend") : I_("Proc"));
		
			if (!getParent ()->send (this, I_("TradeAuthorization")))
			{
				// Display error
				ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
			}
			else 
			{
				DString okCancel;

				getParameter (OKCancel, okCancel);

				if (okCancel != I_("Cancel"))
				{
					if (!getParent ()->send (this, I_("RefreshHistory")))
					{
						// Display error
						ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
					}
				}
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
}
//******************************************************************************
void TransactionHistoryDlg::OnDblClickedSourceOfFundsChecked()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnDblClickedSourceOfFundsChecked" ) ); 
   
	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
		if( pos != NULL )
		{
			DString listKey;

			if (m_bIsPending)
			{
				listKey = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::PENDING_LIST);
			}
			else
			{
				listKey = getParent()->getCurrentListItemKey (this,IFASTBP_PROC::TRANS_LIST);
			}
         
			setParameter (PENDPROCRECORD_TYPE, m_bIsPending ? I_("Pend") : I_("Proc"));
		
			if (!getParent ()->send (this, I_("SourceofFundsChecked")))
			{
				// Display error
				ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
			}
			else 
			{
				DString okCancel;
				getParameter (OKCancel, okCancel);
				if (okCancel != I_("Cancel"))
				{
               if(m_bIsPending)//refersh pendign trades
               {
                setParameter( pPENDING,I_("Y")); 
                if(!doRefresh(this, I_("PendingTradesRefreshed")))
						 ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());// Display error
               }
				   else //refresh historical trades
					{
                   if(!getParent ()->send (this, I_("RefreshHistory")) )
						   ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());// Display error
					}
				}
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
}
//******************************************************************************
void TransactionHistoryDlg::OnBtnBatch()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBatch" ) ); 
   
	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
		if( pos != NULL )
		{
			DString listKey;

			if (!m_bIsPending)
			{		
				listKey = getParent()->getCurrentListItemKey (this,IFASTBP_PROC::TRANS_LIST);
			}

			setParameter (PENDPROCRECORD_TYPE, m_bIsPending ? I_("Pend") : I_("Proc"));

			if (!getParent ()->send (this, I_("Batch")))
			{
				// Display error
				ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
			}
			else 
			{
				DString okCancel;

				getParameter (OKCancel, okCancel);

				if (okCancel != I_("Cancel"))
				{
					if (!getParent ()->send (this, I_("RefreshHistory")))
					{
						// Display error
						ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
					}
				}
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
}

//******************************************************************************
void TransactionHistoryDlg::enableBatchButton (const BFContainerId& idContainer)
{
	bool bEnable = false;

	DString dstrSettled;
	DString dstrAutoBatch;

	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    
	if (pDSTCWorkSession)
	{
		pDSTCWorkSession->getOption (ifds::AutoBatch, dstrAutoBatch, getDataGroupId(), false );
	}
	
	if (idContainer == IFASTBP_PROC::TRANS_LIST && dstrAutoBatch.asInteger () == AUTO_BATCHING)
	{
		DString  dstrSettled;
		DString	 dstrSeqNum;
		
		getParent()->getField (this, idContainer, ifds::Settled,  dstrSettled, false);
		getParent()->getField( this, idContainer, ifds::SeqNum, dstrSeqNum, false );
  
		dstrSeqNum.stripAll().stripLeading('0');
      
		if (dstrSeqNum.empty() && dstrSettled == Y) 
		{
			bEnable = true;
		}
	}

	GetDlgItem (IDC_BTN_BATCH)->EnableWindow (bEnable);		
}

//******************************************************************************
void TransactionHistoryDlg::OnBtnMultiSettlInstr()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMultiSettlInstr" ) ); 
   
	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
      if( pos != NULL )
      {
         DString dstrTransNum;
         DString *dstrKey = (DString*)m_lvReportView.GetItemData( m_lvReportView.GetNextSelectedItem( pos ) );

         if( m_bIsPending )
         {
            getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, dstrTransNum, false);
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, dstrTransNum, false);
         }

         setParameter (PENDPROCRECORD_TYPE, m_bIsPending ? I_("Pend") : I_("Proc"));
         setParameter (pTRANSNUM, dstrTransNum);
         setParameter( I_("AccountNum"), AccountNum );
         setParameter( I_("Caller"),     CLASSNAME );
         setParameter( I_("TransListKey"),   *dstrKey );
            
		    switch( invokeCommand (getParent(), CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS,
								   PROC_NO_TYPE , true, NULL))
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
}

//******************************************************************************
void TransactionHistoryDlg::enableMultiSettlInstrButton (const BFContainerId& idContainer)
{
	bool bEnable = false;

	DString dstrSettleLocOpt;

	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    
	if (pDSTCWorkSession)
	{
		pDSTCWorkSession->getOption (ifds::SettleLocOpt, dstrSettleLocOpt, getDataGroupId(), false );
	}
	
	if (dstrSettleLocOpt.asInteger () == MULTI_SETTLE_INSTR)
	{
		DString dstrTransType;
		DString dstrPayType;

		getParent()->getField (this, idContainer, ifds::TransType,  dstrTransType, false);   
		getParent()->getField (this, idContainer, ifds::PayType2,  dstrPayType, false);   

		bool bPurchaseLike = dstrTransType == ED || dstrTransType == INSPECIES_ED || dstrTransType == HYBRID_ED || dstrTransType == INSPECIES_NONPRORATA_ED;  
		bool bRedemptionLike = dstrTransType == PW || dstrTransType == INSPECIES_PW || dstrTransType == HYBRID_PW ||dstrTransType == INSPECIES_NONPRORATA_PW;

		if (( bPurchaseLike || bRedemptionLike) && dstrPayType != CLEARING) 
		{
			bEnable = true;
		}
	}

	GetDlgItem (IDC_BTN_SETTL_LOCS)->EnableWindow (bEnable);		
}

//******************************************************************************
void TransactionHistoryDlg::OnBtnRESPHist ()
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnRESPHist")); 
   
   SetMessageStatusBar( TXT_LOAD_RESPTRANSACTIONS );
	
   try
	{
      POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();

      if (pos != NULL)
      {
         DString dstrTransId;
         DString dstrTradeDate;
         DString *dstrKey = (DString*)m_lvReportView.GetItemData( m_lvReportView.GetNextSelectedItem( pos ) );

         if (m_bIsPending)
         {
            getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::TransId, dstrTransId, false);
            getParent()->getField (this, IFASTBP_PROC::PENDING_LIST, ifds::TradeDate, dstrTradeDate, false);
         }
         else
         {
            getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, dstrTransId, false);
            getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate, dstrTradeDate, false);
         }

         setParameter(MFCAN_IP_PARAM::CALLER, ALLOCATIONSPROC::TRANS_HIST);
         setParameter (RESPTRANSACTIONSNAMES::ACCOUNT_NUMBER_FIELD, AccountNum);
         setParameter (I_("TransId"), dstrTransId);
         setParameter (I_("TradeDate"), dstrTradeDate);
         setParameter (RESPTRANSACTIONSNAMES::HISTORY_PENDING_FIELD, 
                       m_bIsPending ? RESPTRANSACTIONSNAMES::PENDING : RESPTRANSACTIONSNAMES::HISTORY);

         switch (invokeCommand( getParent(), CMD_BPROC_RESPTRANSACTIONS, 
                                PROC_NO_TYPE, isModal(), NULL ))
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
void TransactionHistoryDlg::enableRESPHistButton ()
{

   DString strTaxType;
   getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, strTaxType, false);
   strTaxType.strip().upperCase();

   GetDlgItem (IDC_BTN_RESP_HIST)->EnableWindow (strTaxType == I_("9") || strTaxType == I_("M"));
}

//************************************************************************************
void TransactionHistoryDlg::DisplayResponseRequiredValueInAttributeList(const BFContainerId& idContainer)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("DisplayResponseRequiredValurInAttributeList")); 

   DString dstrNetRespReqApplicable;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption( ifds::NetworkRespReqApplicable, dstrNetRespReqApplicable, getParent()->getDataGroupId(), false );

   if( dstrNetRespReqApplicable.strip().upperCase() == I_("Y") )
   {
      DisplayItem(idContainer, ifds::NetworkRespRequired, TXT_RESPONSE_REQUIRED_OPTION );
   }
}

//************************************************************************************
void TransactionHistoryDlg::enablePaymentButton (const BFContainerId& idContainer)
{
		MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, 
								CLASSNAME, 
								I_("enablePaymentButton"));
		bool bEnable = false;		
		DString dstrFundCode;
		DString dstrTransType,dstrRvCode,dstrConfIssued,dstrDepositType,dstrOrderType;
		bool bIsPurchase = false;

		DString dstrNonReceiptApplicable;

		DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		dstWorkSession->getOption( ifds::NonReceiptApplicable, dstrNonReceiptApplicable,
			getParent()->getDataGroupId(), false );

		if( dstrNonReceiptApplicable.strip().upperCase() == I_("Y") )
		{
			getParent()->getField (this, idContainer, ifds::rxFundCode,  dstrFundCode, false);
			getParent()->getField (this, idContainer,ifds::TransType,  dstrTransType, false);   
			getParent()->getField (this, idContainer,ifds::RvCode, dstrRvCode, false);
			getParent()->getField (this, idContainer,ifds::ConfIssued, dstrConfIssued, false);
			getParent()->getField (this, idContainer,ifds::DepositType,dstrDepositType, false);
			getParent()->getField (this, idContainer,ifds::OrderType,dstrOrderType, false);

			dstrTransType.strip ();
			dstrTransType.upperCase();			
			
			bIsPurchase = dstrTransType == ED ;
								
			if (bIsPurchase && isMoneyMarketFund(dstrFundCode)&& //if it is purchase on moneymkt fund.
				dstrOrderType == I_("N") &&		     // Enable only when the order type is direct.
				 (dstrRvCode ==I_("") || dstrRvCode==I_("08"))//current dated or back dated trade.	   
				   && dstrConfIssued != I_("X") /* not a cancelled trade */ && dstrDepositType != I_("2")/* Deposit type is PAC*/)
			{
				bEnable = true;
			}
	     }

		GetDlgItem (IDC_BTN_PAYMENT_INFO)->EnableWindow (bEnable);	

}

//************************************************************************************
void TransactionHistoryDlg::OnBtnPaymentInfoFlag()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnPaymentInfoFlag" ) ); 

 	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
		if( pos != NULL )
		{
			DString listKey;

			if (m_bIsPending)
			{
				listKey = getParent()->getCurrentListItemKey (this, IFASTBP_PROC::PENDING_LIST);
			}
			else
			{
				listKey = getParent()->getCurrentListItemKey (this,IFASTBP_PROC::TRANS_LIST);
			}       
			
			setParameter (PENDPROCRECORD_TYPE, m_bIsPending ? I_("Pend") : I_("Proc"));

			if (!getParent ()->send (this, I_("Payment")))
			{
				// Display error
				ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
			}
			else 
			{
				DString okCancel;

				getParameter (OKCancel, okCancel);

				if (okCancel != I_("Cancel"))
				{
					if (!getParent ()->send (this, I_("RefreshHistory")))
					{
						// Display error
						ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
					}
				}
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
}

bool TransactionHistoryDlg ::isMoneyMarketFund(const DString &fundCode)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "isMoneyMarketFund" ) );
	bool blIsMoneyMarketFund = false;
	DString settlePurDays;
				
	DSTCWorkSession *dstWorkSession = 
		dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		FundMasterList *pFundMasterList = NULL;
	
		if (dstWorkSession && 
		dstWorkSession->getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && 
		pFundMasterList)
		{			
			if(pFundMasterList->isMoneyMarketFund(fundCode))
			{
				FundMaster *pFundMaster = NULL;
				if ( pFundMasterList->getFundMaster (fundCode, BF::HOST, pFundMaster) &&
					pFundMaster)
				{
					pFundMaster->getField (ifds::SettlePurDays, settlePurDays, BF::HOST, false);
					if(I_("0") == settlePurDays )//(t+0)fund 
						blIsMoneyMarketFund = true;
				}
				
			}
		}	

	return blIsMoneyMarketFund;
}
//************************************************************************************
void TransactionHistoryDlg::enableShareLotButton()
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION,CLASSNAME, I_("enableShareLotButton"));
	
	DString dstrFundCode,dstrClassCode,dstrIWTEnable;		

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getOption( ifds::IWTEnable, dstrIWTEnable,getParent()->getDataGroupId(), false );

	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,  dstrFundCode, false);
	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode,  dstrClassCode, false);

	bool bEnable = dstWorkSession->isPerfFeeFund(dstrFundCode,dstrClassCode,getParent()->getDataGroupId()) 
												|| (dstrIWTEnable == I_("Y"));
	GetDlgItem (IDC_BTN_SHARELOT)->EnableWindow(bEnable);	
}
//************************************************************************************
void TransactionHistoryDlg::OnBtnShareLot()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnShareLot" ) ); 
	
	E_COMMANDRETURN eRtn = CMD_OK;
	DString dstrFundCode,dstrClassCode,dstrAsOfDate,dstrTransId,dstrLotType,dstrIWTEnable;
	
	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::rxFundCode,  dstrFundCode, false);
	dstrFundCode.stripAll();

	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::rxClassCode,  dstrClassCode, false);
	dstrClassCode.stripAll();

	getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TradeDate, dstrAsOfDate );
    dstrAsOfDate.stripAll();

	DString DisplayMaskFormat = GetConfigValueAsString (I_( "LocaleFormats" ), I_( "DisplayMasks" ), I_( "enUS-D" ));
	DisplayMaskFormat.stripAll();
	DisplayMaskFormat = DisplayMaskFormat.lowerCase ();

	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('/')); //Removing separator if any
	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('-')); //Removing separator if any
	
	DString AsOfDate;
	if (DisplayMaskFormat == I_("ddmmyyyy"))
	{
		dstrAsOfDate = dstrAsOfDate.stripAll(I_CHAR('/')); //Removing separator
		dstrAsOfDate = dstrAsOfDate.stripAll(I_CHAR('-')); //Removing separator

		AsOfDate =  dstrAsOfDate.substr ( 2, 2 ); //month
		AsOfDate += I_("/");
		AsOfDate += dstrAsOfDate.substr ( 0, 2 ); //day
		AsOfDate += I_("/");
		AsOfDate += dstrAsOfDate.substr ( 4, 4 ); //year
	}
	else
	{
		AsOfDate =  dstrAsOfDate;
	}

	getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, dstrTransId );
	dstrTransId.stripAll();

	DString dstrActiveOnly				= I_("No");
	DString dstrForSelectedTransaction  = I_("Yes");

	DString urlParamsIDI;
	addIDITagValue (urlParamsIDI, I_("AccountNum"), AccountNum);
	addIDITagValue (urlParamsIDI, I_("Fund"), dstrFundCode);
	addIDITagValue (urlParamsIDI, I_("Class"), dstrClassCode);
	addIDITagValue (urlParamsIDI, I_("AsOfDate"), AsOfDate);
	addIDITagValue (urlParamsIDI, I_("ActiveOnly"), dstrActiveOnly);
	addIDITagValue (urlParamsIDI, I_("TransId"), dstrTransId);
	addIDITagValue (urlParamsIDI, I_("ForSelectedTransaction"), dstrForSelectedTransaction);
	addIDITagValue (urlParamsIDI, I_("screen"), I_("SharelotSummary"));
	addIDITagValue (urlParamsIDI, I_("LotType"), I_(""));

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    
	DString dstrEntityName;
    dstWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(),AccountNum,dstrEntityName);

    CString cstrSharelotAcctNum,cstrName;
    cstrSharelotAcctNum.LoadString(TXT_SHARELOT_ACCT_NUM);
    cstrName.LoadString(TXT_ACCT_HOLDER_NAME);
    
	DString screenTitle = DString(cstrSharelotAcctNum) + AccountNum;
    screenTitle += DString(cstrName) + dstrEntityName;

	setParameter (I_("UrlParams"), urlParamsIDI);
	setParameter (I_("from_screen"), I_("TransactionHistoryDlg"));
	setParameter (I_("screen"), I_("SharelotSummary"));
	setParameter (I_("BrowserTitle"), screenTitle );

	eRtn = invokeCommand (getParent(), CMD_BPROC_SHARE_LOT_BROWSER, PROC_NO_TYPE, true, NULL);
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

//******************************************************************************
void TransactionHistoryDlg::OnBtnGuaranteeRules()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnGuaranteeRules" ) ); 
   
 	try
	{
		POSITION pos = m_lvReportView.GetFirstSelectedItemPosition();
		
		if( pos != NULL )
		{
			DString listKey,
			   dstrParamsIDI,
			   dstrTransNum,
			   dstrTransId;

			if (m_bIsPending)
			{
				getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransId, dstrTransId, false );
				getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, dstrTransNum, false );
			}
			else
			{
				getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, dstrTransId, false );
				getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, dstrTransNum, false );				
			}

			dstrTransId.stripAll();
			dstrTransNum.stripAll();
			
         CString cstrSEGGuaranteeRule,
            cstrAccountNumLabel,
            cstrTransNum,
            cstrTransID;
         cstrSEGGuaranteeRule.LoadString(TXT_SEG_GUARANTEE_RULE);
         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
         cstrTransID.LoadString(TXT_TRANS_ID);
         cstrTransNum.LoadString(TXT_TRANS_TRANSNUM);
			
         DString screenTitle = DString(cstrSEGGuaranteeRule);
         screenTitle += I_(",");
         screenTitle += DString(cstrAccountNumLabel) + AccountNum;
         screenTitle += I_(",");
         screenTitle += DString(cstrTransNum) + I_(": ") + dstrTransNum;
         screenTitle += DString(cstrTransID).strip() + I_(": ") + dstrTransId;
			
         addIDITagValue (dstrParamsIDI, I_("from_screen"), CLASSNAME);
         //addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), screenTitle);
         addIDITagValue (dstrParamsIDI, I_("screen"),I_("GuaranteeRule") );
         addIDITagValue (dstrParamsIDI, I_("AccountNum"), AccountNum);
         addIDITagValue (dstrParamsIDI, I_("TransID"), dstrTransId);
         addIDITagValue (dstrParamsIDI, I_("TransNum"), dstrTransNum);
         setParameter( I_("UrlParams"), dstrParamsIDI);
         setParameter( I_("BrowserTitle"), screenTitle);
         
         switch (invokeCommand( getParent(), 
                                CMD_BPROC_SEG_GUARANTEE_RULES, 
                                PROC_NO_TYPE, 
                                isModal(), 
                                NULL ))
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
}

//******************************************************************************
void TransactionHistoryDlg::enableRDSPNotionalActivityButton ()
{
	DString strTaxType;
	getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, strTaxType, false);
	strTaxType.strip().upperCase();

	bool bPermit = getParent()->hasReadPermission (UAF::RDSP_NOTIONAL_ACTIVITY);
	bool bShow = strTaxType == I_("RS") && bPermit;

	GetDlgItem (IDC_BTN_RESP_HIST)->ShowWindow (!bShow);
	GetDlgItem (IDC_BTN_RDSP_NOTIONAL_ACTIVITY)->ShowWindow (bShow);
	GetDlgItem (IDC_BTN_RDSP_NOTIONAL_ACTIVITY)->EnableWindow (bShow && !m_bIsPending);
}

//******************************************************************************
void TransactionHistoryDlg::OnBtnRDSPNotionalActivity()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnRDSPNotionalActivity" ) ); 

	DString transNum, urlParamsIDI;
	E_COMMANDRETURN eRtn = CMD_OK;

	getParent()->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, transNum);
	transNum.strip();

	SetMessageStatusBar (TXT_LOAD_RDSP_NOTIONAL_ACTIVITY);	

	setParameter( I_( "AccountNum" ), AccountNum );
	setParameter( I_( "from_screen" ), I_( "Account" ) );

	addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPNotionalActivity"));
	addIDITagValue (urlParamsIDI, I_("AccountNum"), AccountNum);
	addIDITagValue (urlParamsIDI, I_("TransNum"), transNum);
	
	setParameter (I_("UrlParams"), urlParamsIDI);

	CString cstrRDSP;
	cstrRDSP.LoadString(TXT_RDSP_NOTIONAL_ACTIVITY);
	setParameter (I_("BrowserTitle"), DString(cstrRDSP) + AccountNum);
	setParameter (I_("from_screen"), I_("TransactionHistoryDlg"));

	// invoke rdsp notional activity browser screen
	eRtn = invokeCommand (getParent(), CMD_BPROC_RDSP_NOTIONAL_ACTIVITY, PROC_NO_TYPE, true, NULL);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionHistoryDlg.cpp-arc  $
 * 
 *    Rev 1.401   Aug 10 2012 20:19:04   wp040133
 * ESS_P01999461_FN01_ARROW_Distribution Enhancement
 * Modifiying G1 G2 Display logic and Adding TaxCreditAmount to Screen for TransHistory
 * 
 *    Rev 1.400   Jul 27 2012 08:42:02   wp040132
 * P0199891 _FN01_Arrow_FAST_File
 * 
 *    Rev 1.399   Jul 26 2012 10:30:34   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.398   Jul 23 2012 16:55:44   wp040133
 * In 3030809  WO # : 804821 PET  #:P0181067 Right to Cancel flag needs to be diaplyed only for Purchase Like in TransHistory Dlg.
 * 
 * 
 *    Rev 1.397   Jul 11 2012 15:20:06   wp040039
 * Redoing the check in for incident # 2848558 .
 * 
 * Please ignore the previous check in.
 * 
 * PETP0183989-Money Market Non Receipt
 * WO# 799043 -Non receipt flag is not displayed for cancelled trade
 * 
 *    Rev 1.396   Jul 11 2012 15:02:04   wp040039
 * PETP0183989-Money Market Non Receipt
 * Incident # 2848558 WO# 799043 -Non receipt flag is not displayed for cancelled trade
 * 
 *    Rev 1.395   Jul 02 2012 19:12:10   wp040132
 * P0199883_FN01_Cancellation Rights - Right To Cancel
 * 
 *    Rev 1.394   Jun 18 2012 11:06:56   panatcha
 * IN2958740 - add tag to disable Details button On Pay Search if TransactionHist Dlg calls
 * 
 *    Rev 1.393   May 21 2012 11:48:40   dchatcha
 * IN#2912525 - TxnCancel Button to be enabled in Desktop for CASH ID's
 * 
 *    Rev 1.392   May 16 2012 09:12:48   wp040027
 * Sync up: In#2955963:'Valuation Date' field is blank on viewing the details from Fund Information scr
 * 
 *    Rev 1.391   May 07 2012 15:00:10   dchatcha
 * Synch up: IN#2912525 - TxnCancel Button to be enabled in Desktop for CASH ID's
 * 
 *    Rev 1.390   May 04 2012 11:40:40   dchatcha
 * Synch up: IN#2912525 - TxnCancel Button to be enabled in Desktop for CASH ID's
 * 
 *    Rev 1.389   Apr 27 2012 10:29:10   wp040027
 * Sync up: IN2934256: PF- P0188394 XML Parsing Error on clicking Sharelot info
 * 
 *    Rev 1.388   Mar 28 2012 11:38:10   dchatcha
 * Synch up: P0186484 FN05 Seg Trade Processing
 * 
 *    Rev 1.387   Mar 22 2012 15:48:44   dchatcha
 * Synch up: P0186479 FN01 - Allowable Transfer.
 * 
 *    Rev 1.386   Mar 21 2012 14:36:18   dchatcha
 * P0186479 FN01 - Allowable Transfer, refer to wrong container!
 * 
 *    Rev 1.385   Mar 21 2012 13:40:36   dchatcha
 * P0186479 FN01 - Allowable Transfer.
 * 
 *    Rev 1.384   Mar 16 2012 14:46:38   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.383   Mar 15 2012 12:30:20   wp040132
 * As per Winnie's suggestion, UrlParamter 'LotType' is passed as empty string. #IN 2873349 - Purchase Sharelot error in Desktop
 * 
 *    Rev 1.382   Mar 11 2012 15:43:52   jankovii
 * Commented out seg code for enable modify/cancle button.
 * 
 *    Rev 1.381   Mar 09 2012 18:06:38   dchatcha
 * P0186484 FN 05 - SEG Trade Processing.
 * 
 *    Rev 1.380   Mar 05 2012 12:39:30   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.379   Feb 28 2012 04:13:42   panatcha
 * P0188394 - iFast Performance Fee - Add screen tag "SharelotSummary" 
 * 
 *    Rev 1.378   Feb 13 2012 12:55:10   wp040132
 * Money Market Non Receipt - Incident 2835083 - Enabling payment button only for direct order purchases
 * 
 *    Rev 1.377   Jan 20 2012 14:14:48   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.376   Jan 19 2012 11:09:50   wp040027
 * P0188394_Performance Fees - Added 'screen' and 'BrowswerTitle' to launch Sharelot Screen
 * 
 *    Rev 1.375   Jan 18 2012 16:44:42   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.374   Dec 15 2011 21:07:46   wp040032
 * Incident 2775411 - Money Market NonReceipt
 * 
 *    Rev 1.373   Dec 08 2011 21:27:50   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.372   Nov 25 2011 16:02:34   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.371   Nov 21 2011 18:49:30   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.370   Nov 19 2011 01:40:10   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.369   Nov 08 2011 15:00:16   popescu
 * Fixed the flat/percent interpretation
 * 
 *    Rev 1.368   Aug 03 2011 11:19:54   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.367   Apr 05 2011 06:47:00   kitticha
 * PETP0181067_FN00_IN2460780_Empire Autobatch Development on Cancelled SP and DC trades.
 * 
 *    Rev 1.366   Mar 28 2011 10:50:26   jankovii
 * Sync up: IN 2475801 - Invalid split commission calculation
 * 
 *    Rev 1.365   Mar 10 2011 21:38:38   panatcha
 * IN2458590_WO599611 - Automation script failing due to Desktop Trans type naming error
 * 
 *    Rev 1.364   Feb 01 2011 18:48:12   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.363   Dec 09 2010 15:16:08   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.362   Oct 29 2010 06:39:58   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.361   Aug 11 2010 19:38:48   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.360   Aug 06 2010 14:07:50   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.359   Jun 08 2010 04:34:24   dchatcha
 * Synch up from 1.356.1.1 - IN#2128812 - PETP0165541 FN 01 - Double display code of GR Repay Reason.
 * 
 *    Rev 1.358   Jun 01 2010 23:50:56   dchatcha
 * Synch up from 1.356.1.0 : IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
 * 
 *    Rev 1.357   May 27 2010 05:37:58   kitticha
 * PETP0165541 FN02 QESI Phase2.
 * 
 *    Rev 1.356   May 13 2010 01:33:38   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.355   Apr 30 2010 05:58:30   dchatcha
 * PET0165541 FN01 QESI RESP Trading, display values even they are '0'
 * 
 *    Rev 1.354   Apr 30 2010 01:13:38   dchatcha
 * PET0165541 FN01 QESI RESP Trading, display new fields of view 54.
 * 
 *    Rev 1.353   Apr 15 2010 00:01:24   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.352   Dec 02 2009 03:08:44   dchatcha
 * P0166149 SSII iFAST Web Settlement Date Changes.
 * 
 *    Rev 1.351   Nov 24 2009 15:14:30   popescu
 * Incident 1925188 - ICT Authorization Box de-highlighted
 * 
 *    Rev 1.350   Aug 12 2009 12:06:18   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.349   Jul 17 2009 15:03:08   jankovii
 * IN 1724320 - ESG19 - ICT - rebooked ICT trade reported as CON 69 instead of CON6
 * 
 *    Rev 1.348   Jul 09 2009 13:20:46   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.347   May 28 2009 06:39:34   wutipong
 * IN1608629 - Aimprod RTS error : Disable the settlement button on the trans history dialog only when the dialog is open from settlement dialog. -- Sync Up
 * 
 *    Rev 1.346   May 27 2009 15:06:38   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.345   May 22 2009 13:37:32   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.344   May 22 2009 10:38:04   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.343   May 11 2009 12:01:24   wutipong
 * IN1608629 - AIM Prod RTS error : disable the Settlement Button on the Transaction History screen.
 *
 *    Rev 1.342   May 04 2009 10:26:48   jankovii
 * PET 159770 FN05 Auto Batching. 
 * 
 *    Rev 1.341   Mar 19 2009 14:21:22   jankovii
 * IN 1402399 - Incorrect tax rate displayed on the pending trade
 * 
 *    Rev 1.340   Mar 04 2009 14:13:26   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.339   Mar 04 2009 10:19:46   jankovii
 * PET0159508 FN03 ESG In Cash Transfer.
 * 
 *    Rev 1.338   Mar 04 2009 05:44:00   dchatcha
 * IN 1402399 - Incorrect tax rate displayed on the pending trade.
 * 
 *    Rev 1.337   Mar 03 2009 16:19:30   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.336   Mar 02 2009 10:02:38   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.335   Nov 25 2008 11:32:30   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.334   06 Oct 2008 13:21:00   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.333   Sep 15 2008 04:10:46   phiwponp
 * IN 1394896    Inconsistence of Historical screen title under pending trade - clean code - remove unnecessary comment
 * 
 *    Rev 1.332   Sep 15 2008 03:47:28   phiwponp
 * IN 1394896    Inconsistence of Historical screen title under pending trade - clean code
 * 
 *    Rev 1.331   Sep 10 2008 06:04:58   phiwponp
 * IN 1394896     - Inconsistence of Historical screen title under pending trade
 * 
 *    Rev 1.330   Aug 29 2008 09:51:50   daechach
 * in#1355618 - recode fix for 1259584 Gross\net
 * 
 *    Rev 1.329   05 Aug 2008 13:40:22   kovacsro
 * PET0095436_FN01 Blackrock Rounding - hide Original Amount whenever the value is 0.00
 * 
 *    Rev 1.328   30 Jul 2008 15:59:50   kovacsro
 * PET0095436_FN01 Blackrock Rounding
 * 
 *    Rev 1.327   Jun 04 2008 09:16:06   wongsakw
 * PETP0052400_FN01 Pending Trades by Fund Class Field Modifications Report -- Sync up
 * 
 *    Rev 1.326   03 Jun 2008 15:32:28   kovacsro
 * restored rev. 1.324
 * 
 *    Rev 1.324   May 07 2008 10:59:24   daechach
 * in#1268611 - DSK Pending and Transaction History Screens with "Gap".
 * 
 *    Rev 1.323   Apr 25 2008 08:08:42   daechach
 * in#1259584-R84 - Gross / Net display issue in desktop for pending trades
 * 
 *    Rev 1.322   Jan 29 2008 13:14:36   daechach
 * IN#1134569 - Cancel of Transfer out Trade not Allowed.
 * 
 *    Rev 1.321   Jan 18 2008 11:31:48   daechach
 * IN#1123784,1133269 - Gross/Net field not populated in desktop modify screen , Pending transaction on Desktop unavailable
 * 
 *    Rev 1.320   Dec 20 2007 16:30:12   wongsakw
 * PET2315 FN28 -- Audit an Tracking on Pending Trades -- Add ModDate and ModUser field to PendingTrade
 * 
 *    Rev 1.319   Dec 11 2007 18:05:28   wongsakw
 * PET2360 FN60 Automatically Cancel Contribution Reciept
 * 
 *    Rev 1.318   Dec 11 2007 14:41:38   smithdav
 * PET1200 FN01 - Dividend Processing
 * 
 *    Rev 1.317   Dec 07 2007 18:58:44   smithdav
 * PET1200 FN01 - Dividend Processing
 * 
 *    Rev 1.316   06 Dec 2007 15:20:34   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.315   Dec 06 2007 19:42:50   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.314   Nov 30 2007 18:24:34   daechach
 * PET5517 FN 97 - RRIF Net of Fees
 * 
 *    Rev 1.313   Oct 24 2007 15:01:06   jankovii
 * IN #1047594 - Fund Level Override not working for manual exchanges.
 * 
 *    Rev 1.312   Sep 16 2007 15:46:20   jankovii
 * IN #990336 - User is unable to process manual/adhoc MFR trades.
 * 
 *    Rev 1.311   May 07 2007 13:07:16   porteanm
 * Incident 867819 - Position on the right record when coming from TradeSearch.
 * 
 *    Rev 1.310   Mar 30 2007 14:10:34   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.308   Mar 14 2007 14:34:40   jankovii
 * PET 2292 FN01 - Switch Settlement.
 *  
 *    Rev 1.307   Mar 09 2007 10:15:46   ZHANGCEL
 * PET2292 FN02 - Added a String itme in Attribute box of Transaction History Screen
 * 
 *    Rev 1.306   Dec 06 2006 16:02:12   fengyong
 * Incident #700115 - fix payment search screen title.
 * 
 *    Rev 1.305   Nov 29 2006 09:38:40   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.304   Nov 21 2006 14:41:54   jankovii
 * PET 2252 FN01 Mgmt fee rebate.
 * 
 *    Rev 1.303   Nov 16 2006 11:28:40   popescu
 * PET 2252. FN01 - mgmt fee rebate
 * 
 *    Rev 1.302   Nov 08 2006 15:39:28   fengyong
 * Incident 752890 - Transaction history fund filter
 * 
 *    Rev 1.301   Oct 06 2006 10:09:46   fengyong
 * Incident 727548 - disable payment search screen for canada market
 * 
 *    Rev 1.300   Oct 05 2006 17:23:08   fengyong
 * Incident 727548 - disable payment search screen for canada market
 * 
 *    Rev 1.299   Oct 05 2006 13:41:16   fengyong
 * Incident 727548 - disable payment search screen for canada market
 * 
 *    Rev 1.298   Sep 27 2006 01:00:18   popescu
 * STP 2217/13 Fixes related to PayInstruct btn on TrxnHist/Pend
 * 
 *    Rev 1.297   Sep 21 2006 01:50:58   popescu
 * STP PET 2217/13
 * 
 *    Rev 1.296   Aug 29 2006 16:40:08   fengyong
 * PET2192 FN17 - Add transaction detail button to payment search screen
 * 
 *    Rev 1.294   Aug 23 2006 14:53:38   fengyong
 * temp check in for PET 2192
 * 
 *    Rev 1.293   Jun 16 2006 14:09:46   ZHANGCEL
 * Incident #617984 -- Fix the issue that ESGSettle does not display  when the value of field is "EX"
 * 
 *    Rev 1.292   Mar 21 2006 17:34:50   popescu
 * used mgmtco obj. by reference - prior to the change an extra call to vew 56 was made - caused perf. issues in env. with lots of funds.
 * 
 *    Rev 1.291   Mar 10 2006 14:46:30   porteanm
 * Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
 * 
 *    Rev 1.290   Mar 03 2006 09:30:30   fengyong
 * PET 2017 FN01 - Add field reconciled
 * 
 *    Rev 1.289   Mar 02 2006 17:35:30   ZHANGCEL
 * PET1334 - FN01 -- ESG Settlement enhancement
 * 
 *    Rev 1.288   Mar 02 2006 16:30:12   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.287   Feb 20 2006 11:53:40   ZHANGCEL
 * PET 1334 - FN1 -- Added new field ESGSettle in Grid 
 * 
 *    Rev 1.286   Feb 15 2006 10:47:28   ZHANGCEL
 * PET 1334 - FN1 -- ESG money movement enhancement
 * 
 *    Rev 1.284   Jan 20 2006 13:35:32   AGUILAAM
 * IN 424704 - sync-up from R67: get tradedate/settledate unformatted; error is not being raised due to incorrect date comparisons.
 * 
 *    Rev 1.283   Jan 19 2006 13:53:42   AGUILAAM
 * PET1295_FN01: addl enhancements - do not display MCH/SecRec fields if not supported by client
 * 
 *    Rev 1.282   Jan 12 2006 15:05:20   porteanm
 * Incident 517976 - Disable the Cancelllation button for Cash dividends.
 * 
 *    Rev 1.281   Jan 12 2006 13:48:00   AGUILAAM
 * PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
 * 
 *    Rev 1.280   Jan 10 2006 14:44:40   AGUILAAM
 * IN 513993 - disable EUSD button for reversal trades also
 * 
 *    Rev 1.279   Jan 09 2006 17:08:20   porteanm
 * Incident 424704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.278   Dec 20 2005 11:23:06   porteanm
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.277   Dec 16 2005 20:22:44   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.276   Dec 14 2005 09:45:52   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.275   Dec 14 2005 09:17:30   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.274   Dec 13 2005 19:32:42   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.273   Dec 09 2005 15:52:10   porteanm
 * PET 1228 FN01 - TIS and Cost will not be displayed here anymore for a processed transaction.
 * 
 *    Rev 1.272   Dec 06 2005 16:50:20   porteanm
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.271   Dec 06 2005 09:40:54   popescu
 * Incident# 444351 - subsequent fix for displaying the rebook param screen.
 * 
 *    Rev 1.270   Nov 30 2005 10:26:06   zhengcon
 * Incident #458619--Fixed problem of clicking EFT to account twice under transaction details screen
 * 
 *    Rev 1.269   Nov 29 2005 16:23:06   popescu
 * Incident# 462749 - display RevCodeDesc on the transaction list  attributes
 * 
 *    Rev 1.268   Nov 29 2005 15:24:36   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.267   Nov 12 2005 11:53:10   porteanm
 * PET 1286 FN01 - Bulk Cancellation.
 * 
 *    Rev 1.266   Oct 13 2005 15:34:10   AGUILAAM
 * IN 424819 - synch up from rel64, enable rebook button for both settled and unsettled trades
 * 
 *    Rev 1.265   Sep 23 2005 11:20:24   AGUILAAM
 * IN 402898 : sync-up from rel64, do not hide Rebook button 
 * 
 *    Rev 1.264   Sep 20 2005 12:53:34   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.263   Sep 19 2005 10:57:58   fengyong
 * #Incident 402113 - All fund mode loading problem
 * 
 *    Rev 1.262   Sep 15 2005 15:15:56   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.261   Sep 13 2005 10:25:20   yingbaol
 * INDC can be 1 and 4, maybe something else, now the security check only apply to INDC "1". According to winnie, Dividend with INDC 4 is backdated purchase which is generated by cycle. 
 * 
 *    Rev 1.260   Sep 08 2005 12:59:54   popescu
 * Incident# 398841 - activated rebook for rollovers
 * 
 *    Rev 1.259   Aug 29 2005 14:48:34   yingbaol
 * Incident 387057: restore the original logic and check transtype.
 * 
 *    Rev 1.258   Aug 26 2005 10:45:42   porteanm
 * Incident 389416 - Modify button for pending AW.
 * 
 *    Rev 1.257   Aug 23 2005 16:47:52   popescu
 * Incident 387057 - fixed user permissions on the trxn cancelation button
 * 
 *    Rev 1.256   Aug 23 2005 16:43:18   popescu
 * Incident 387057 - fixed user permissions on the trxn cancelation button
 * 
 *    Rev 1.255   Aug 12 2005 10:15:00   Yingbaol
 * Incident 378613: disable int links button when it is lauched with pending.
 * 
 *    Rev 1.254   Aug 09 2005 10:20:38   AGUILAAM
 * IN 371908 - FeePercent in transaction history may either be flat or percent; % sign is not always correct.
 * 
 *    Rev 1.253   Jul 29 2005 14:40:42   Yingbaol
 * PET1235,FN01: Open EI,EO,TI,TO for rebook
 * 
 *    Rev 1.252   Jul 21 2005 13:24:44   Yingbaol
 * PET1235,Fn01: disable Internal link for pending trade.
 * 
 *    Rev 1.251   Jul 20 2005 14:10:08   Yingbaol
 * incindent 325606, sync up version 239.1.3 
 * 
 *    Rev 1.250   Jul 20 2005 14:03:10   Yingbaol
 * PEt1235,FN01: fix refresh issue
 * 
 *    Rev 1.249   Jul 19 2005 11:42:00   porteanm
 * PET1171 EUSD 1B - TIS and Cost.
 * 
 *    Rev 1.248   Jul 14 2005 17:43:06   popescu
 * Incident 357000 - call inventory summary dialog modeless
 * 
 *    Rev 1.247   Jul 14 2005 17:34:14   Yingbaol
 * PET1235,FN01:transaction rebook
 * 
 *    Rev 1.246   Jul 12 2005 17:19:56   AGUILAAM
 * PET 1235: dilution
 * 
 *    Rev 1.245   Jul 12 2005 15:55:00   Yingbaol
 * PET1235: add security check and other conditions for launch rebook /cancel
 * 
 *    Rev 1.244   Jul 08 2005 17:54:26   AGUILAAM
 * IN 288176 : sync-up from rel63, display ChargeERSTTRFee for TO/EO
 * 
 *    Rev 1.243   Jul 08 2005 09:41:40   Yingbaol
 * PET1235,FN01:Transaction cancellation rebook
 *
 *    Rev 1.242   Jul 06 2005 12:26:34   porteanm
 * PET1171 EUSD 1B - TIS and Cost.
 *  
 *    Rev 1.241   Jun 29 2005 13:22:44   AGUILAAM
 * IN 2913010 : sync-up from rel63; moved SettleDate next to TradeDate
 * 
 *    Rev 1.240   Jun 24 2005 16:59:50   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.239   Jun 22 2005 17:52:46   AGUILAAM
 * IN 343484 - display DeliveryMethod on trades
 * 
 *    Rev 1.238   May 30 2005 18:00:12   porteanm
 * PET OPC Confirm Reprint - Set Reprint/TxnCancel parameters.
 * 
 *    Rev 1.237   May 30 2005 14:50:44   yingbaol
 * PET1203, FN01:Don't check transtype in generic control( since the transtype has been changed after cycle.
 * 
 *    Rev 1.236   May 25 2005 17:08:02   ZHANGCEL
 * Incident #317014 -- Disable <Modify> button when ModPerm is 3
 * 
 *    Rev 1.235   May 24 2005 13:06:48   porteanm
 * PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
 * 
 *    Rev 1.234   May 23 2005 22:09:58   georgeet
 * Incident 291301 - added new Settlement Date column in list box of Transaction History Dlg.
 * 
 *    Rev 1.233   May 20 2005 16:24:50   porteanm
 * PET OPC Confirm Reprint - Reprint button support.
 * 
 *    Rev 1.232   May 18 2005 09:06:34   yingbaol
 * PET1203,FN01: Commission Class A
 * 
 *    Rev 1.231   Apr 19 2005 13:52:42   hernando
 * Incident #292495 - Added OnBtnClicked for Message Button.  Sychronized with 1.223.1.3 exclusively.
 * 
 *    Rev 1.230   Apr 01 2005 14:59:22   porteanm
 * Incident 279375 - Clawback button for EO, RR.
 * 
 *    Rev 1.229   Mar 23 2005 17:04:38   porteanm
 * Incident # 237748 - Enabling/disabling buttons.
 * 
 *    Rev 1.228   Mar 08 2005 19:00:38   Fengyong
 * PET1190 FN04 - go back to previous version
 * 
 *    Rev 1.227   Mar 08 2005 15:46:30   Fengyong
 * PET1190 FN04 - make cancellation invoke model  
 * 
 *    Rev 1.226   Mar 04 2005 17:17:00   Fengyong
 * PET1190 FN04 - TransCancel Tempery check in for other coder
 * 
 *    Rev 1.225   Mar 03 2005 17:14:44   aguilaam
 * PET1171_FN01: EU Savings - others - display records for Tax Reports only
 * 
 *    Rev 1.224   Mar 03 2005 14:34:26   aguilaam
 * PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
 * 
 *    Rev 1.223   Mar 02 2005 16:09:04   aguilaam
 * PET1198_FN01: LSIF Reason Code enhancement (correction)
 * 
 *    Rev 1.222   Mar 02 2005 15:57:16   aguilaam
 * PET1198_FN01: LSIF Code enhancement 
 * 
 *    Rev 1.221   Feb 24 2005 11:49:18   hernando
 * PET1117 FN66-68 - Added setParameter for the Message Search Type.
 * 
 *    Rev 1.220   Feb 22 2005 16:32:50   hernando
 * PET1117 FN66-68 - Added DisableMsg parameter.  Disabled/Enabled Message Button appropriately.
 * 
 *    Rev 1.219   Feb 17 2005 13:16:18   aguilaam
 * PET1198_FN01: LSIF Reason Code enhancement. 
 * 
 *    Rev 1.218   Feb 04 2005 12:25:38   popescu
 * PET 1117/66, new fields to be displayed on the trans history screen, and their descriptions in the resources
 * 
 *    Rev 1.217   Jan 28 2005 17:32:16   hernando
 * PTS10038131 - Enable/Disable Inventory Summary Button appropriately on the Transaction History dialog.
 * 
 *    Rev 1.216   Jan 20 2005 16:03:06   hernando
 * PTS10037884 - Changed the Back End Load display.
 * 
 *    Rev 1.215   Jan 17 2005 18:29:40   hernando
 * PTS10037736 - Removed reference to AWDEVENT.  Clean up.
 * 
 *    Rev 1.214   Jan 07 2005 19:05:20   popescu
 * PTS 10037553, fixed issues with modifying pending trades 
 * 
 *    Rev 1.213   Dec 24 2004 09:55:56   popescu
 * PTS 10037200, modify button for reinvest purchase is not actvie
 * 
 *    Rev 1.212   Dec 22 2004 14:09:56   popescu
 * PTS 10037175, restored the display of PayMethod in conjunction with file processor, synch-up release 58.1.1
 * 
 *    Rev 1.211   Dec 21 2004 18:11:36   popescu
 * PET 1117/56, fixed call to pending trades details view 54 when dialog is launched.
 * 
 *    Rev 1.210   Dec 14 2004 18:03:12   hernando
 * PET910 - Display description from data dictionary for SuppressCode, Accountable, and SettledBy.
 * 
 *    Rev 1.209   Dec 13 2004 14:16:50   popescu
 * PET 1117/56, ChqSupCode-->SuppressCode, view 54
 * 
 *    Rev 1.208   Dec 10 2004 16:18:40   popescu
 * PET 1117/56 few fixes for settl instr and trans fee list refresh
 * 
 *    Rev 1.207   Dec 07 2004 21:20:52   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.206   Dec 07 2004 01:38:22   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.205   Dec 01 2004 12:03:16   hernando
 * PTS10036314 - Changed fields to use data dictionary instead of description fields from view.  Fields changed were PayType2, OrderSource, SettleSource, SettleType, SrcOfFund, and DepositType.  Synchronized with 1.200.1.1
 * 
 *    Rev 1.204   Nov 26 2004 10:39:56   popescu
 * PTS 10036185, display the pay method, regardless of the value of file processor, synch-up branch 1.200.1.0, release 58/58.1
 * 
 *    Rev 1.203   Nov 22 2004 13:10:04   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.202   Nov 07 2004 14:56:50   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.201   Nov 04 2004 10:48:42   VADEANUM
 * PET1117 FN21 - Settlement Instr, renamed from SettLoc to SettlementInstr
 * 
 *    Rev 1.200   Oct 29 2004 14:26:46   ZHANGCEL
 * PTS ticket 10034979 -- Display Federal and Provincial Exempt amount as long as there are not zero regardless the transtype.
 * 
 *    Rev 1.199   Oct 29 2004 12:31:34   VADEANUM
 * PET1117 FN21 - Backed-out - Settlement Instr, renamed from SettLoc to SettlementInstr
 * 
 *    Rev 1.198   Oct 14 2004 14:01:58   VADEANUM
 * PET1117 FN21 - Settlement Instr, renamed from SettLoc to SettlementInstr
 * 
 *    Rev 1.197   Sep 23 2004 12:22:50   HERNANDO
 * PET1094 FN08 - Added PopulateTransDetailsEqualizationAmt.  Changed checking of Transaction Types.  Clean up.
 * 
 *    Rev 1.196   Sep 20 2004 18:04:50   ZHANGCEL
 * 1. PET 1082 - FN2 : Add logic to not display Fed and Prov Tax Exempt amount when the value are 0
 * 2. Code clean up by grouping transtype
 * 
 *    Rev 1.195   Sep 20 2004 14:30:04   ZHANGCEL
 * PET 1082 FNrlc: Added two strings for the Transaction history dialog to display tax exempty amount
 * 
 *    Rev 1.194   Sep 20 2004 10:49:26   ZHANGCEL
 * PET1094_FN8: AdminFee related changes
 * 
 *    Rev 1.193   Sep 15 2004 10:19:34   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface - show Value Date for Purchase in both Pending and History.
 * 
 *    Rev 1.192   Sep 14 2004 16:52:24   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.191   Sep 07 2004 15:39:10   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.190   Aug 25 2004 15:27:16   HERNANDO
 * PTS10033333 - Allow double-clicking on Network ID / Ext Trans Num for AWD images for Transaction History. (Sync-up from 57)
 * 
 *    Rev 1.189   Aug 25 2004 14:22:18   ZHANGCEL
 * PET1082 -- Display TaxExemptAmt in Attribute field
 * 
 *    Rev 1.188   May 27 2004 12:24:40   popescu
 * PET 985, FN 01, LSIF Trade entry
 * 
 *    Rev 1.187   May 25 2004 17:23:28   AGUILAAM
 * PTS 10029944 - display equalization values even if 0 when Controls EqualizationSetup is active
 * 
 *    Rev 1.186   May 22 2004 15:49:56   HERNANDO
 * PET1017 FN02 - Allow double-clicking on ExtTransNum and Network ID to launch AWD look-up.
 * 
 *    Rev 1.185   May 19 2004 11:30:32   popescu
 * PET 985, FN 01, displayed LSIF Code
 * 
 *    Rev 1.184   May 19 2004 11:10:36   VADEANUM
 * PTS 10028913 - Reflection.
 * 
 *    Rev 1.183   May 18 2004 14:41:56   popescu
 * PET 985, FN 01, LSIF Trade Entry
 * 
 *    Rev 1.182   May 17 2004 11:51:00   HERNANDO
 * PET1017 FN02 - Disable the AWD History button if AWD Look-up criteria is not available.
 * 
 *    Rev 1.181   May 14 2004 14:44:12   HERNANDO
 * PET1046 FN01 - Added parameter to disable Inventory Information button.
 * 
 *    Rev 1.180   May 07 2004 15:30:24   ZHANGCEL
 * PTS10030031: Bug fix for not be able to enter Inventory summary screen from TransactionHistory Screen by pressing InvSummary button
 * 
 *    Rev 1.179   May 03 2004 11:57:22   HERNANDO
 * PET1017 FN02 - Revised the AWD Historical look-up implementation.
 * 
 *    Rev 1.178   Apr 07 2004 09:49:18   FENGYONG
 * PTS10028818, Pendinglist sorting
 * 
 *    Rev 1.177.1.0   Apr 07 2004 09:46:38   FENGYONG
 * PTS10028818, Pendinglist sorting
 * 
 *    Rev 1.177   Mar 18 2004 14:24:48   HERNANDO
 * PTS10028119 - Format DealTime.
 * 
 *    Rev 1.176   Mar 12 2004 11:49:08   HERNANDO
 * PTS10028119 - DealDate and DealTime will always be displayed for Pending transactions.
 * 
 *    Rev 1.175   Mar 02 2004 15:36:32   popescu
 * PTS10027082 - display the fee rate for non-split commission environments
 * 
 *    Rev 1.174   Feb 26 2004 17:20:32   ZHANGCEL
 * PET1001 - FN01 Change logic to enable and disable the <Inv Summary> button
 * 
 *    Rev 1.173   Feb 25 2004 14:53:04   ZHANGCEL
 * PET1001 - FN01: Disable and enable InvSummary button base on the rule
 * 
 *    Rev 1.172   Feb 23 2004 14:15:06   VADEANUM
 * PET859 FN23 - ADL - removed YesNoSet2 for 49.ADLLevyFee
 * 
 *    Rev 1.171   Feb 23 2004 13:51:32   HERNANDO
 * PTS10027082 - Removed 'Fee Rate' from Pending Exchanges/Transfers as per Adela's request.
 * 
 *    Rev 1.170   Feb 23 2004 13:43:04   ZHANGCEL
 * PET1001_FN01: add function to launch Inventory Summary screen
 * 
 *    Rev 1.169   Feb 16 2004 11:32:58   HERNANDO
 * PTS10027082 - Fee and FeeTo will display a % sign if the value is not zero.
 * 
 *    Rev 1.168   Feb 16 2004 10:58:36   ZHANGCEL
 * Sync up: PTS ticket 10026640: disable or enable Pending Trade Radio button base on the value of PendingTrade_4
 * 
 *    Rev 1.167   Feb 05 2004 10:21:50   VADEANUM
 * PET859 FN23 - ADL - Deductions and ADLFeeCharge on Transaction History
 * 
 *    Rev 1.166   Dec 23 2003 11:41:16   VADEANUM
 * PET892 FN1 - Trade Settlement Location support - Pay Type.
 * 
 *    Rev 1.165   Dec 10 2003 12:19:28   popescu
 * PTS 10024124, spcomm re-work
 * 
 *    Rev 1.164   Nov 26 2003 13:55:50   VADEANUM
 * PET892 FN1 - Trade Settlement Location.
 * 
 *    Rev 1.163   Nov 26 2003 12:51:34   AGUILAAM
 * PET859_FN17 - daily equalization; display CapitalAmount from view 22
 * 
 *    Rev 1.162   Nov 25 2003 15:13:34   VADEANUM
 * PET892 FN1 - Trade Settlement Location support - modified signature for enableSettlementLocInstr( )
 * 
 *    Rev 1.161   Nov 25 2003 12:10:20   VADEANUM
 * PET892 FN1 - Trade Settlement Location support - added enableSettlementLocInstr() and logic behind OnBtnSettlLocationInstr().
 * Also Chin's changes in PopulateTransDetails() and for PTS 10023779
 * 
 *    Rev 1.160   Nov 11 2003 14:09:22   VADEANUM
 * PTS 10023978
 * 
 *    Rev 1.159   Nov 11 2003 13:12:32   VADEANUM
 * PET892 FN1 - Trade Settlement Location support.
 * 
 *    Rev 1.158   Oct 28 2003 10:47:02   FENGYONG
 * handle all the direct pay type the same as EFT paytype
 * 
 *    Rev 1.157   Oct 19 2003 18:35:46   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.156   Oct 16 2003 12:38:32   FENGYONG
 * PTS 10017160 Sorting pending list in trasactionhistory
 * 
 *    Rev 1.155   Sep 29 2003 13:41:10   popescu
 * synch-up with 1.53.1 for 53.0.0.5
 * 
 *    Rev 1.154   Sep 26 2003 13:59:48   popescu
 * Fixed the occurence of wrong choices in the acctusage field for pending trade banking; this under PTS 10020130; 
 * 
 *    Rev 1.153   Sep 10 2003 16:49:02   HERNANDO
 * Sync'd up to 1.144.1.2; PTS 10020345.
 * 
 *    Rev 1.152   Sep 08 2003 16:18:36   FENGYONG
 * Add string "TXT_TRANS_ACCTLEVELTAX"
 * 
 *    Rev 1.151   Sep 01 2003 21:24:00   popescu
 * PET 809 FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.150   Aug 25 2003 18:18:38   HERNANDO
 * Ensure a zero leads a decimal in heading Amount.
 * 
 *    Rev 1.149   Aug 22 2003 13:56:40   HERNANDO
 * Changed the description display for many Pending fields to utilize Substitution Set descriptions.
 * 
 *    Rev 1.148   Aug 19 2003 16:09:22   HSUCHIN
 * added Borrowed Funds to details of pending/historical purchases.
 * 
 *    Rev 1.147   Aug 15 2003 14:33:36   FENGYONG
 * Add Override tax for PW type transaction
 * 
 *    Rev 1.146   Aug 01 2003 12:32:38   popescu
 * synch-up 52 to 53
 * 
 *    Rev 1.145   Jul 24 2003 11:31:26   VADEANUM
 * PET 809 F05 - ChargeWDFee support.
 * 
 *    Rev 1.144   Jun 26 2003 15:36:06   HERNANDO
 * Changed display so that 'Income Distribution' will not be displayed as 'IncomeDistribution'.
 * 
 *    Rev 1.143   May 23 2003 10:04:46   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.142   May 22 2003 14:14:38   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.141   May 13 2003 10:07:50   popescu
 * Split commission re-work
 * 
 *    Rev 1.140   May 05 2003 16:23:16   popescu
 * display the early redemption fee in the pending details view
 * 
 *    Rev 1.139   Apr 23 2003 10:12:26   ZHANGCEL
 * PTS ticket 10015809: display FeeRate for the Pending Redemption
 * 
 *    Rev 1.138   Apr 09 2003 11:57:52   HERNANDO
 * PTS 10015814 - Deduction details not displayed for Exchange Out - Historical Transactions.
 * 
 *    Rev 1.137   Apr 02 2003 11:47:06   popescu
 * added the chargeer/sttr fee field to the transaction history list, as well
 * 
 *    Rev 1.136   Mar 26 2003 15:50:44   popescu
 * Added the charge  er/sttr fee to the transaction histrory dialog
 * 
 *    Rev 1.135   Mar 21 2003 18:41:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.134   Mar 19 2003 09:58:34   popescu
 * Added the exchange out fee to the transaction history dialog for pending trades
 * 
 *    Rev 1.133   Mar 03 2003 12:02:06   KOVACSRO
 * If modal, invoke child processes in InquiryOnly mode.
 * 
 *    Rev 1.132   Mar 03 2003 09:50:14   KOVACSRO
 * 1. if selection was specified, fixed the logic to repeatedly download chunks of 25 records until the selection is found
 * 2. Added InquiryOnly parameter to open the screen in inquiry mode
 * 
 *    Rev 1.130   Jan 22 2003 09:04:34   sanchez
 * Display Swift fields.
 * 
 *    Rev 1.129   Jan 10 2003 10:49:20   KOVACSRO
 * PTS10012613 : For EFT and Cheque pay method, cheque info was not showing.
 * 
 *    Rev 1.128   Jan 03 2003 18:30:52   HERNANDO
 * Returned Automatic Withdrawl = "AW"; added TYPE_SWP for SWPs.
 * 
 *    Rev 1.127   Dec 20 2002 14:27:30   HERNANDO
 * Changed DisplayTaxRates.
 * 
 *    Rev 1.126   Nov 29 2002 10:27:22   KOVACSRO
 * rxTransType changes
 * 
 *    Rev 1.125   Nov 06 2002 10:32:56   YINGBAOL
 * sync. up release 49
 * 
 *    Rev 1.124   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.123   Oct 09 2002 16:39:14   HERNANDO
 * PTS 10009707 - Fix; uses new fields.
 * 
 *    Rev 1.122   Oct 07 2002 16:22:42   HERNANDO
 * PTS 10009707 Hack - Display '$' or '%' instead of using the substitution set; will be changed later for better design.
 * 
 *    Rev 1.121   Oct 03 2002 16:04:18   HERNANDO
 * PTS 10009707 Addition - Modified DisplayTaxRates to place description iff '$' in front, otherwise afterward.
 * 
 *    Rev 1.120   Oct 02 2002 16:29:42   HERNANDO
 * PTS 10009707 Additional change - Changed Fed/Prov Tax Rates for Pending Exchanges.
 * 
 *    Rev 1.119   Sep 30 2002 11:01:46   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.118   Sep 20 2002 16:42:46   HERNANDO
 * PTS 10009706 Enhancement.  According to Natalie Bradley - not to display the % after a Fee Rate if zero.
 * 
 *    Rev 1.117   Sep 17 2002 17:41:42   HERNANDO
 * PTS 10009708 - Always display Prov Tax Rate and Fed Tax Rate.
 * 
 *    Rev 1.116   Sep 16 2002 18:27:42   HERNANDO
 * PTS 10009813 - Multiple AWD Business Areas mapped to the same System ID will cause look-ups to ignore Business Area.
 * 
 *    Rev 1.115   Sep 06 2002 17:02:26   HERNANDO
 * PTS 10009705 - Will not display 'Fund Number To' if zero.
 * 
 *    Rev 1.114   Sep 04 2002 19:03:46   HERNANDO
 * PTS 10009706 / PTS 10009712 - Replaced 'Fee' with 'Fee Rate' and addded '%'.  Added '%' and '$' to values.  Added function DisplayFeeRate.  Display 'Cancelled' if Reversal for balance.
 * 
 *    Rev 1.113   Aug 29 2002 12:57:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.112   Aug 27 2002 17:38:18   HERNANDO
 * Allow Cheque Browsing for PayType 'X'.
 * 
 *    Rev 1.111   Aug 27 2002 15:10:28   HERNANDO
 * Switched Gross/Net - Good/Bad around in Pending Purchases.
 * 
 *    Rev 1.110   Aug 26 2002 17:50:12   HERNANDO
 * Transaction History - Bank Charge only applicable for redemption (PW or AW).
 * Pending Transactions - Bank Charge only applicable for redemption (PW).  Use Entered Fee only applicable to transfer in/out (TI,EI,TO,EO).
 * 
 *    Rev 1.109   Aug 26 2002 17:24:30   HERNANDO
 * Precautionary code - removed tabs from values referenced in the .ini tables for AWD.
 * 
 *    Rev 1.108   Aug 26 2002 15:56:42   HERNANDO
 * Added DisplayTaxRates fn.  Add calls to this function.
 * 
 *    Rev 1.107   Aug 23 2002 19:01:26   HERNANDO
 * Enhancement - Added FedTaxRate and ProvTaxRate with description to Attributes.  Will change later to use a different field for description.
 * 
 *    Rev 1.106   Aug 22 2002 16:37:46   HERNANDO
 * Enhancement - Added Reversal to Transaction History.  Modified column heading and display from Cancelled to Cancelled/Reversal.  Logic to display Cancelled or Reveral in Attributes iff 'Y'.
 * 
 *    Rev 1.105   Aug 20 2002 19:25:36   HERNANDO
 * Enhancement - Continued.   Changed attribute fields (order, display).
 * 
 *    Rev 1.104   Aug 20 2002 17:43:14   HERNANDO
 * Enhancement - Changed order of fields in attribute list.  Removed Order Batch and Settle Batch.
 * 
 *    Rev 1.103   Aug 19 2002 18:13:14   HERNANDO
 * Enhancement - Added 'Cancelled' to list box for Transaction History.
 * 
 *    Rev 1.102   Aug 09 2002 15:05:58   HERNANDO
 * PTS 10009355 - Added UseEnteredFee to PendingDetails Common.
 * 
 *    Rev 1.101   Aug 06 2002 14:04:22   HERNANDO
 * PTS 10009277 - Display fund number for Cash Distribution.
 * 
 *    Rev 1.100   Jul 31 2002 11:00:32   KOVACSRO
 * Stop the user from poping up bank screen if PayMethod is Cheque.
 * 
 *    Rev 1.99   Jul 30 2002 11:52:04   HERNANDO
 * Removed duplicate PayType2 from TransList Redemption details.
 * 
 *    Rev 1.98   Jul 26 2002 17:51:36   HERNANDO
 * PTS 10009202 - Replaced all TXT_TRANS_SETTLECURRENCY to TXT_PENDING_SETTLECURRENCY; from "Settle currency to "Settlement Currency"
 * 
 *    Rev 1.97   Jul 11 2002 16:50:20   KOVACSRO
 * Commented out userId check when modyfing a pending trade, because we use ModPerm field to enable/disable Modify button. If ModPerm is Y, user has permission to modify.
 * 
 *    Rev 1.96   Jul 05 2002 10:44:40   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.95   Jul 02 2002 11:36:54   KOVACSRO
 * Modify/Settlement buttons fixes.
 * 
 *    Rev 1.94   Jun 27 2002 11:50:50   HERNANDO
 * Added "Bank Charge" to details for Historical/Pending Transactions.
 * 
 *    Rev 1.93   Jun 25 2002 19:04:08   HERNANDO
 * Revised DisplayCodeDesc.  Fixed call using TransList and Field ProvSalesName to DisplayCodeDesc.
 * 
 *    Rev 1.92   Jun 15 2002 17:51:34   KOVACSRO
 * new BFData wants us to set formatted dates as parameters.
 * 
 *    Rev 1.91   14 Jun 2002 10:17:38   YINGZ
 * fix parameter key problem
 * 
 *    Rev 1.90   13 Jun 2002 16:44:00   YINGZ
 * dis settlement btn
 * 
 *    Rev 1.89   13 Jun 2002 16:21:02   YINGZ
 * show/hide
 * 
 *    Rev 1.88   13 Jun 2002 14:41:10   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.87   Jun 12 2002 17:44:02   KOVACSRO
 * 1. fixed ValueDate display.
 * 2. fixed Settlement button
 * 
 *    Rev 1.86   12 Jun 2002 16:32:30   YINGZ
 * add settlement btn on transhistory scr
 * 
 *    Rev 1.85   Jun 07 2002 17:55:46   KOVACSRO
 * PayMethod fixes
 * 
 *    Rev 1.84   31 May 2002 12:29:16   KOVACSRO
 * 1. syncup.
 * 2. added new fields to Details.
 * 
 *    Rev 1.83.1.1   May 28 2002 12:20:26   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.83.1.0   May 23 2002 10:42:00   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.83   Apr 18 2002 13:28:58   YINGBAOL
 * fix modify button
 * 
 *    Rev 1.82   Apr 16 2002 14:02:34   YINGBAOL
 * All Fund Transfer Type support
 * 
 *    Rev 1.81   Apr 10 2002 17:21:34   HERNANDO
 * PTS 10007127 - Added TXT_SETTLED; displays 'Settled' when SeqNum is zero and settled.
 * 
 *    Rev 1.80   04 Apr 2002 11:17:56   KOVACSRO
 * Modify/Rebook button fixes in refresh().
 * 
 *    Rev 1.79   Apr 01 2002 18:01:08   HERNANDO
 * Hide AWD History button for non-Lux.
 * 
 *    Rev 1.78   27 Mar 2002 20:01:28   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.77   Mar 19 2002 17:10:04   HERNANDO
 * Added 'Transfer Fund Number' and 'Fund Number To' for History/Pending Exchange/Transfer attributes.
 * 
 *    Rev 1.76   13 Mar 2002 14:28:30   WINNIE
 * change to uppercase for comparison
 * 
 *    Rev 1.75   08 Mar 2002 10:17:36   HSUCHIN
 * bug fix for DST Redemption not displaying correctly.
 * 
 *    Rev 1.74   26 Feb 2002 16:55:04   HSUCHIN
 * added hllapi entry for dsc redemption
 * 
 *    Rev 1.73   25 Feb 2002 12:14:22   KOVACSRO
 * MgmtFee modify and rebook.
 * 
 *    Rev 1.72   15 Feb 2002 11:35:04   KOVACSRO
 * 1. Added timer list control.
 * 2. Rebook changes.
 * 
 *    Rev 1.71   Jan 28 2002 11:28:14   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.70   03 Jan 2002 16:55:38   KOVACSRO
 * Bug fixed. Start with 'Modify' button disabled.
 * 
 *    Rev 1.69   31 Dec 2001 12:26:14   KOVACSRO
 * Some description fixes and some strip() versus stripAll() fixes.
 * 
 *    Rev 1.68   Dec 20 2001 13:45:48   HERNANDO
 * Added AWD-related conditions.
 * 
 *    Rev 1.67   19 Dec 2001 15:43:22   KOVACSRO
 * we can have multiple errors for Trade Date Lag.
 * 
 *    Rev 1.66   Dec 18 2001 16:29:18   HERNANDO
 * Fixed Group Share display; uses local TransType variable in fn.
 * 
 *    Rev 1.65   14 Dec 2001 17:03:24   KOVACSRO
 * Displaying the error mesage for trade date lag.
 * 
 *    Rev 1.64   14 Dec 2001 13:02:36   KOVACSRO
 * small change.
 * 
 *    Rev 1.63   Dec 13 2001 11:15:52   JANKAREN
 * Added Trade Date Lag
 * 
 *    Rev 1.62   11 Dec 2001 09:14:08   KOVACSRO
 * Our glass.
 * 
 *    Rev 1.61   Dec 10 2001 13:53:20   HERNANDO
 * Revised use of AwdInterface; clean-up.
 * 
 *    Rev 1.60   Nov 29 2001 14:46:20   HERNANDO
 * Barclay Dividends change for Lux.  Added fields - Grp1Shares, Grp2Shares, EqualFactor, EqualAmount, EqualAmtCurrency.
 * 
 *    Rev 1.59   14 Nov 2001 13:44:14   KOVACSRO
 * changed the parent for trading process. it is the worksession process now.
 * 
 *    Rev 1.58   Nov 13 2001 17:17:20   HERNANDO
 * Revised AwdInterface implementation.
 * 
 *    Rev 1.57   13 Nov 2001 10:46:34   KOVACSRO
 * more fix for EffectiveDate on Banking.
 * 
 *    Rev 1.56   09 Nov 2001 16:47:20   KOVACSRO
 * Bug fixed for not showing EffectiveDate on Banking screen.
 * 
 *    Rev 1.55   Nov 07 2001 17:58:44   ZHANGCEL
 * Haspermission changes
 * 
 *    Rev 1.54   Oct 17 2001 10:42:32   ZHANGCEL
 * Fixed the bug regarding duplicateing Acctable Entity and missing BackDatedReason
 * 
 *    Rev 1.53   Oct 10 2001 15:26:32   YINGBAOL
 * disable Modify button if it is history
 * 
 *    Rev 1.52   Oct 03 2001 15:46:48   ZHANGCEL
 * 1.Remove Hllapi from PendingTrade::Transfer Account, 2. only allow Transfer lunching the MatchTransfer screen.
 * 
 *    Rev 1.51   Sep 13 2001 17:26:04   ZHANGCEL
 * Added SettledType into PendingTrade detales
 * 
 *    Rev 1.50   Sep 07 2001 16:30:16   ZHANGCEL
 * Set parameter TransId for lunching MatchTransfer
 * 
 *    Rev 1.49   Aug 27 2001 15:39:00   ZHANGCEL
 * Remove the extra line that causes Wire Order Number shows up twice.
 * 
 *    Rev 1.48   Aug 16 2001 13:55:26   ZHANGCEL
 * Changed the logic for Attributes item "Tansfer Account"  in order to lunch a IFast screen instead of lunch Hllapi
 * 
 *    Rev 1.47   07 Aug 2001 13:36:28   YINGZ
 * fix key and modify problem
 * 
 *    Rev 1.46   Jul 20 2001 14:29:40   HERNANDO
 * Added AWD History Button.  Look-up based on Transaction Number, Account Number, and Business Area.
 * 
 *    Rev 1.45   Jul 20 2001 09:57:54   HUANGSHA
 * Enable the some common controls for MSDW, change the alignment of listctrl
 * 
 *    Rev 1.44   Jul 18 2001 12:21:54   ZHANGCEL
 * Bug fixed for modify pending trade button setting
 * 
 *    Rev 1.43   Jul 17 2001 14:57:54   ZHANGCEL
 * Fixed the bug for setting modify button to be disable or enable
 * 
 *    Rev 1.42   Jul 09 2001 11:48:00   ZHANGCEL
 * 1.Added pending trade modify permission check logic; 2.Fix for getField of DBR::SplitCom to Comfirmatted.
 * 
 *    Rev 1.41   Jul 04 2001 11:40:26   ZHANGCEL
 * Fixed the bug for browse pending trade bank
 * 
 *    Rev 1.40   Jun 20 2001 11:56:40   HERNANDO
 * Fix - Blank Fund Number for DisplayCashDiv.
 * 
 *    Rev 1.39   Jun 19 2001 16:22:26   ZHANGCEL
 * Fixed the bug in OnRbPending()
 * 
 *    Rev 1.38   Jun 16 2001 15:43:56   ZHANGCEL
 * Using string of string table instead of hard code for displaying message in pending trade modification
 * 
 *    Rev 1.37   14 Jun 2001 13:47:48   SMITHDAV
 * Remove references to UserSessionProcess.
 * 
 *    Rev 1.36   Jun 14 2001 13:40:20   ZHANGCEL
 * Change error message for Pending Trade Modifacation
 * 
 *    Rev 1.35   Jun 12 2001 10:30:58   ZHANGCEL
 * Change error message for Pending Trade Modification
 * 
 *    Rev 1.34   Jun 11 2001 17:11:36   ZHANGCEL
 * 1. Added logic for ExchInFee and ExchInFeeType; 2. Added logic for User_Id and BatchUser comparison befer modify a pending trade.
 * 
 *    Rev 1.33   05 Jun 2001 12:04:38   KOVACSRO
 * Sync up 1.29.2.7 (full sync up)
 * 
 *    Rev 1.32   Jun 04 2001 13:31:06   ZHANGCEL
 * Replaced "str.stripAll()" with "str.strip()".
 * 
 *    Rev 1.31   31 May 2001 15:23:50   KOVACSRO
 * Sync up SSB (1.29.17)
 * 
 *    Rev 1.30   03 May 2001 14:07:42   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.29   Apr 09 2001 16:07:16   YINGBAOL
 * distinguish pending and transactionb history
 * 
 *    Rev 1.28   Apr 05 2001 16:02:56   YINGBAOL
 * fix bug 
 * 
 *    Rev 1.27   Apr 03 2001 15:23:46   YINGBAOL
 * Pass BankTypoe to BankInstrProcess
 * 
 *    Rev 1.26   Apr 03 2001 12:20:46   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.25   Apr 03 2001 08:42:54   YINGBAOL
 * Launch BankInstrDlg
 * 
 *    Rev 1.24   Mar 29 2001 15:40:00   HERNANDO
 * Bank Inst. dlg will display if PayType is E or I
 * 
 *    Rev 1.23   Mar 29 2001 15:18:44   ZHANGCEL
 * Added logic for XR
 * 
 *    Rev 1.22   Mar 23 2001 12:33:04   HSUCHIN
 * passing list item key to transaction allocation dialog and minor bug fix
 * 
 *    Rev 1.21   Mar 23 2001 10:21:16   ZHANGCEL
 * bug fixed
 * 
 *    Rev 1.20   Mar 20 2001 12:54:34   HERNANDO
 * Removed display of TransTypeDesc; replaced w/TransType.
 * 
 *    Rev 1.19   Mar 19 2001 15:33:50   HERNANDO
 * SplitCommissions parameter chg. Transaction_Pending
 * 
 *    Rev 1.18   Mar 19 2001 14:13:32   HERNANDO
 * Changed setParameters for SplitCommissions.
 * 
 *    Rev 1.17   16 Mar 2001 16:57:16   KOVACSRO
 * Sending TransNum as a parameter, too.
 * 
 *    Rev 1.16   Mar 14 2001 14:43:24   HERNANDO
 * Added SplitCommission to details.
 * 
 *    Rev 1.15   Mar 05 2001 11:56:52   ZHANGCEL
 * Added new function OnBtnModify() for PendingTrade modification.
 * 
 *    Rev 1.14   Mar 01 2001 19:15:06   HERNANDO
 * Fix to DisplayCodeDesc; From Desc-Desc to Code-Desc or Code (iff Code==Desc)
 * 
 *    Rev 1.13   Feb 12 2001 16:32:36   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.12   Feb 07 2001 14:00:56   DINACORN
 * M3/C4 synchronization
 * 
 *    Rev 1.11   Jan 24 2001 13:02:28   KOVACSRO
 * Refresh PendingTrades when necessary.
 * 
 *    Rev 1.10   Dec 13 2000 10:58:18   FENGYONG
 * Add filed PayType2 and change #17 and #54 DataSet  from PayType to PayType2
 * 
 *    Rev 1.9   Nov 24 2000 17:33:26   ZHANGCEL
 * Change the list colum from Unit to Amount Type
 * 
 *    Rev 1.8   Oct 18 2000 14:02:16   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.7   Aug 25 2000 11:49:44   DINACORN
 * DisplayItem DBR::BackDatedReason and DBR::GBCD for TRANS_LIST
 * 
 *    Rev 1.6   Aug 08 2000 10:45:00   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.5   Jul 31 2000 16:49:50   HUDAVID
 * added baycom number into report listviewcontrol and other changes
 * 
 *    Rev 1.4   Jun 05 2000 10:01:36   HUANGSHA
 * pass the SettleCurrencyCode to PTAllocList
 * 
 *    Rev 1.3   Apr 05 2000 13:51:16   DT24433
 * changed to use hasPermission
 * 
 *    Rev 1.2   Apr 05 2000 13:49:28   YINGZ
 * code sync
 * 
 *    Rev 1.1   Apr 03 2000 09:50:54   YINGZ
 * code sync
 * 
 *    Rev 1.0   Feb 15 2000 11:01:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.64   Jan 27 2000 15:56:34   YINGZ
 * take out remarks link
 * 
 *    Rev 1.63   Jan 20 2000 14:47:10   YINGZ
 * change currencyname to currency
 * 
 *    Rev 1.62   Jan 19 2000 09:39:42   YINGZ
 * give bank accountnum when invoke
 * 
 *    Rev 1.61   Jan 18 2000 13:29:14   YINGZ
 * add pending banking
 * 
 *    Rev 1.60   Jan 18 2000 11:18:04   YINGZ
 * pass bank formatted trans type
 * 
 *    Rev 1.59   Jan 17 2000 15:22:08   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.58   Dec 22 1999 11:29:02   YINGBAOL
 * Hllapi Change Sync.
 * 
 *    Rev 1.57   Dec 15 1999 14:15:54   PRAGERYA
 * Setting allocations parameters modified
 * 
 *    Rev 1.56   Dec 14 1999 13:02:08   YINGZ
 * add remarks , enable allocation
 * 
 *    Rev 1.55   Dec 13 1999 14:40:54   PRAGERYA
 * Allocations - returned to the separate TransactionAllocations  process
 * 
 *    Rev 1.54   Dec 01 1999 14:33:18   PRAGERYA
 * Check-in for release
 * 
 *    Rev 1.53   Dec 01 1999 11:46:02   YINGZ
 * add transtype to bank
 * 
 *    Rev 1.52   Nov 18 1999 13:46:24   PRAGERYA
 * Allocations coding for Incr2
 * 
 *    Rev 1.51   Nov 11 1999 16:55:54   PRAGERYA
 * Transaction Allocations replaced by Allocations
 * 
 *    Rev 1.50   Nov 02 1999 15:27:28   YINGZ
 * add info to open bank dlg
 * 
 *    Rev 1.49   Nov 02 1999 12:32:04   YINGZ
 * add info to open bank dlg
 * 
 *    Rev 1.48   Oct 30 1999 14:43:58   YINGZ
 * restore focus thing at qa's request
 * 
 *    Rev 1.47   Oct 28 1999 14:17:50   YINGZ
 * bug fixing
 * 
 *    Rev 1.46   Oct 28 1999 09:35:42   YINGZ
 * for a clean Get from PVCS!
 * 
 *    Rev 1.45   Oct 27 1999 11:32:02   PRAGERYA
 * Fixes related to allocations
 * 
 *    Rev 1.44   Oct 11 1999 15:53:34   PRAGERYA
 * Bugs fixed
 * 
 *    Rev 1.43   Sep 27 1999 13:56:38   YINGZ
 * change the way the key is built
 * 
 *    Rev 1.42   Sep 27 1999 10:47:42   PRAGERYA
 * Allocations checked in for release; transaction allocations not debugged yet
 * 
 *    Rev 1.41   Sep 26 1999 18:29:32   VASILEAD
 * Added support for AllFunds mode in transactions screen
 * 
 *    Rev 1.40   Sep 24 1999 10:13:58   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.39   13 Sep 1999 13:53:02   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.38   Aug 31 1999 13:00:40   YINGZ
 * if fund is cash, do not launch fund dlg
 * 
 *    Rev 1.37   Aug 25 1999 11:48:28   DT24433
 * misc.
 * 
 *    Rev 1.36   Aug 24 1999 15:48:24   YINGZ
 * focus back to fund combo
 * 
 *    Rev 1.35   Aug 24 1999 13:01:14   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.34   Aug 23 1999 18:06:02   VASILEAD
 * Settled currency format
 * 
 *    Rev 1.33   Aug 20 1999 10:03:48   YINGZ
 * put checking to cancel trace and batch
 * 
 *    Rev 1.32   Aug 16 1999 15:25:06   YINGZ
 * yen process
 * 
 *    Rev 1.31   Aug 16 1999 14:00:48   YINGZ
 * take OverrideDSC off pending to make it the same as trand history
 * 
 *    Rev 1.30   Aug 06 1999 17:03:58   YINGZ
 * yen
 * 
 *    Rev 1.28   Aug 05 1999 12:09:42   YINGZ
 * Japanese yen
 * 
 *    Rev 1.27   Aug 04 1999 20:55:14   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.21   Jul 28 1999 10:56:32   YINGZ
 * allocation logic change
 * 
 *    Rev 1.20   Jul 27 1999 15:01:54   YINGZ
 * set trans type to null when call allocation in trans history
 * 
 *    Rev 1.19   Jul 27 1999 14:21:38   YINGZ
 * change to display wirs/direct, good/bad
 * 
 *    Rev 1.18   Jul 26 1999 17:08:22   YINGZ
 * change logic of allocation in pending
 * 
 *    Rev 1.17   Jul 23 1999 16:55:18   YINGZ
 * restore
 * 
 *    Rev 1.16   Jul 23 1999 14:45:24   YINGZ
 * ?
 * 
 *    Rev 1.15   Jul 23 1999 14:40:38   YINGZ
 * change cancel stuff
 * 
 *    Rev 1.14   Jul 23 1999 10:59:16   YINGZ
 * ?
 * 
 *    Rev 1.13   Jul 22 1999 15:00:06   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.12   Jul 20 1999 15:49:20   YINGZ
 * give a 0 to empty number
 * 
 *    Rev 1.11   Jul 20 1999 14:24:24   YINGZ
 * ?
 * 
 *    Rev 1.10   Jul 20 1999 11:19:38   VASILEAD
 * New conditions update
 * 
 *    Rev 1.9   Jul 19 1999 16:34:46   POPESCUS
 * Fixed user security access to the address book
 * 
 *    Rev 1.8   Jul 16 1999 14:33:38   YINGZ
 * add new fields
 * 
 *    Rev 1.7   Jul 16 1999 10:37:46   YINGZ
 * nothing
 * 
 *    Rev 1.6   Jul 15 1999 16:51:42   YINGZ
 * make changes in attributs at the request of ba
 * 
 *    Rev 1.4   Jul 09 1999 16:48:54   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.3   Jul 09 1999 16:34:48   YINGZ
 * restore allocation support
 * 
 *    Rev 1.2   Jul 09 1999 14:01:18   YINGZ
 * add trans id to attribute list upong the request of ba
 * 
 *    Rev 1.1   Jul 08 1999 10:06:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


