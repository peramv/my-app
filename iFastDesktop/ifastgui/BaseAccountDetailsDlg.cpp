//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services Inc.
//
//******************************************************************************
//
// ^FILE   : BaseAccountDetailsDlg.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 03/12/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : BaseAccountDetailsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the System/MGMT selection dialog
//
//******************************************************************************

#include "stdafx.h"
#pragma warning( disable : 4503)  

#include "mfdstc.h"
#include "baseaccountdetailsdlg.h"

#include <configmanager.hpp>
#include "dstcview.h"
#include <idistring.hpp>
#include "mainfrm.h"
#include "discardmsgdlg.h"

#include <bfawdi\bfawdinterface.hpp>
#include <bfcbo\bfproperties.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\bpsessiontags.h>
#include <bfsessn\bfcpsession.hpp>
#include <bfutil\bfdate.hpp>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\awdhistoryworklist.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\entity.hpp>

#include <ifastdbrkr\dstcsecurity.hpp>

#include <ifastbp\accdetailsprocessincludes.h>
#include <ifastbp\accinfoprocessincludes.h>
#include <ifastbp\accountcontractprocessincludes.h>
#include <ifastbp\accountreviewprocessincludes.h>
#include <ifastbp\acctsettlementinstrprocess.hpp>
#include <ifastbp\allocationsprocessincludes.h>
#include <ifastbp\amsmstprocessincludes.h>
#include <ifastbp\aspensionplanprocessincludes.h>
#include <ifastbp\chequeprocessincludes.h>
#include <ifastbp\contractinfoprocessincludes.h>
#include <ifastbp\entityprocessincludes.h>
#include <ifastbp\esopinfoprocessincludes.h>
#include <ifastbp\estatementprocessincludes.h>
#include <ifastbp\foreigncontentworksheetprocessincludes.h>
#include <ifastbp\fundsponsorfeemodelprocessinclude.h>
#include <ifastbp\guaranteeinfoprocessincludes.h>
#include <ifastbp\hyporedprocessincludes.h>
#include <ifastbp\investmenthistoryprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\nasuprocessincludes.h>
#include <ifastbp\pensioninfoprocessincludes.h>
#include <ifastbp\respinfoprocessincludes.h>
#include <ifastbp\resptransactionsprocessincludes.h>
#include <ifastbp\rrif_lif_lrif_infoprocessincludes.h>
#include <ifastbp\shareholderprocessincludes.h>
#include <ifastbp\shrfundbrokerprocessincludes.h>
#include <ifastbp\shrfundsponsoragreementprocessincludes.h>
#include <ifastbp\taxexemptauthorizationprocessincludes.h>
#include <ifastbp\ytdcontributionprocessincludes.h>

#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include <uibase\dstcfuncs.h>


#include <assert.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCRUALS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CHEQUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACB;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_MARKET_VALUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RRIF_LIF_LRIF_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHAREHOLDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCINFO;
// extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_ACCOUNT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FREEUNIT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GUARANTEEINFO_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACTINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESPINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESPTRANSACTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ESOPINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_YTD_CONTRIBUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AS_PENSION_PLAN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAMETER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MATSWP_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_SPLITCOMM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CERTICATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REMARKS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_NASU;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_COA;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CERTIFICATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNTREVIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PENSION_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ESTATEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ESTATEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMSACCTLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HYPO_RED;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FAMILY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_CONTRACT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_CATEGORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DIRECT_TRADING;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAX_EXEMPT_AUTHORIZATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FUND_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CLONE_ACCOUNT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CLONE_ACCOUNT_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_CLASS_LIMITATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DOT_AND_ADDENDUM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_LIF_GAIN_LOSS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CHEQUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TFSA_CONTRIBUTION_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_ACCOUNT_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_NOTIONAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_ACCOUNT_TERMINATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ZERO_GRANT_REPAYMENT; 
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INTERFACE_FILE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRAILER_FEE_SETUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GOVT_FILING_AMENDMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTMENT_HISTORY_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_COMMITMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FOREIGN_TAX_REVIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_VALUE_VARIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_REGIS_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_IDENTIFIER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AWDHISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AWDHISTORY_BROWSER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENT_REG_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_GROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PRIVATE_WEALTH_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAX_SLIPS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_GROUPING_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS2;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_NOTIONAL_ACTIVITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALERT_MESSAGES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_ROUNDING_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_DELETION_REVIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_ACCT_INFO_REV;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_ACCOUNT_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_NOTIONAL_ACTIVITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_NOTIONAL_BALANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS;

namespace
{
   // trace literals
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const ADDRESS_CODE         = I_( "AddressCode" );
   const I_CHAR * const ALL_FUND_MODE        = I_( "AllFundMode" );
   const I_CHAR * const CLASSNAME            = I_( "BaseAccountDetailsDlg" );
   const I_CHAR * const CLASS_CODE           = I_( "ClassCode" );
   const I_CHAR * const DEFAULT              = I_( "Default" );
   const I_CHAR * const EMPTY_STRING         = I_( "" );
   const I_CHAR * const ENTITY_ID_PARAM      = I_( "EntityID" );
   const I_CHAR * const EO                   = I_( "EO" );
   const I_CHAR * const FIRST_CHAR_K         = I_( "K" );
   const I_CHAR * const FUND_CODE            = I_( "FundCode" );
   const I_CHAR * const IN_ACCT_NUM_FIELD    = I_( "InAcctNum" );
   const I_CHAR * const KEY                  = I_( "Key" );
   const I_CHAR * const LV_ACCOUNTDETAILS    = I_( "AccountDetails" );
   const I_CHAR * const LV_ENTITYDETAILS     = I_( "EntityDetails" );
   const I_CHAR * const LV_ENTITYIDS         = I_( "EntityIDs" );
   const I_CHAR * const LV_FUNDSDETAILS      = I_( "FundDetails" );
   const I_CHAR * const LV_HISTORYDETAILS    = I_( "HistoryDetails" );
   const I_CHAR * const LV_PENDINGDETAILS    = I_( "PendingDetails" );
   const I_CHAR * const NAME                 = I_( "Name" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const PENDING              = I_( "Pending" );
   const I_CHAR * const SHAREHOLDER_NUM      = I_( "ShareholderNum" );
   const I_CHAR * const SPACE_STRING         = I_( " " );
   const I_CHAR * const STRING_U             = I_( "U" );
   const I_CHAR * const TO                   = I_( "TO" );
   const I_CHAR * const TR                   = I_( "TR" );
   const I_CHAR * const XR                   = I_( "XR" );
   const I_CHAR * const TRADE_DATE_FIELD     = I_( "TradeDate" );
   const I_CHAR * const TRANS_ID_FIELD       = I_( "TransId" );
   const I_CHAR * const TRANS_NUMBER_FIELD   = I_( "TransNum" );
   const I_CHAR * const TRANS_TYPE_FIELD     = I_( "TransType" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const Y_STRING             = I_( "Y" );
   const I_CHAR * const ONBTNAWD             = I_( "OnBtnAwd" );
   const I_CHAR * const FROMSCR              = I_( "FromScr" );
   const I_CHAR * const DETAILS              = I_( "Details" );
   const I_CHAR * const P_STRING             = I_( "P" );
   const I_CHAR * const DOT                  = I_( "DT" );
   const I_CHAR * const ADDENDUM             = I_( "AD" );
   const I_CHAR * const DOT_AND_ADDENDUM     = I_( "DA" );
   const I_CHAR * const ACCTCOA              = I_( "AcctCOA" );
   const I_CHAR * const CALLER               = I_( "Caller" );
   const I_CHAR * const UNCLAIMED_STAGE_CODES_LIST  = I_( "S1,S2,S3,S4" ); //P0178584_FN01_NewPopUpMSG - remove not used 'S5'
   const I_CHAR * const UNCLAIMED_STAGE             = I_( "S1,S2,S3,S4" );
   const I_CHAR * const RESP_TAX_TYPES              = I_( "9,M" );
   const I_CHAR * const TFSA_TAX_TYPES              = I_( "V" );
   const I_CHAR * const CHQ_STATUS_VALUE            = I_( "Status" );
   const I_CHAR * const REPORTED_REMITTED_STATUS    = I_( "14,15" );
   const I_CHAR * const ENTITY_LEVEL         = I_("02");
   const I_CHAR * const ENTITY_CATEGORY      = I_("4");
   const I_CHAR * const INSTR_TYPE           = I_( "InstrType" );
   const I_CHAR * const CASH_SWEEP_INSTR     = I_("SWP");
   const I_CHAR * const MATURITY_INSTR       = I_("MAT");

   //P0178584_FN01_NewPopUpMSG
   const I_CHAR * const STLD_CHQ = I_("Stale Dated Cheque");
   const I_CHAR * const RMTD_CHQ = I_("Remitted Cheque");
   const I_CHAR * const RET_MAIL = I_("Return Mail");
   //End - P0178584_FN01_NewPopUpMSG
   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_AWD_LOOKUP_ERROR;
   extern const long GUI_AWD_EXCEPTION;
}

namespace IDTYPE
{
   extern const I_CHAR * const DRIVER_LICENSE      = I_( "01" );
   extern const I_CHAR * const PASSPORT            = I_( "02" );
   extern const I_CHAR * const BIRTH_CERTIFICATE   = I_( "03" );
   extern const I_CHAR * const CREDIT_CARD         = I_( "04" );
   extern const I_CHAR * const NATIONAL_ID         = I_( "05" );
   extern const I_CHAR * const SOCIAL_SEC_INS_CARD = I_( "06" );
   extern const I_CHAR * const OTHER               = I_( "99" );
}

namespace ACCTINFO
{
   const I_CHAR * const SHAREHOLDER_NUMBER_PMT  = I_( "ShareholderNumber" );
   const I_CHAR * const EMPTY_TRANSACTION       = I_( "TransactionListEmpty" );
   const I_CHAR * const EMPTY_PENDING           = I_( "PendingListEmpty" );
}

namespace DBSUBS
{
   extern const long LV_AcctListHeadingSet ;
   extern const long LV_AccDetailsEntityListHeading ;
};

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccDetailsEntityListHeading;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsFundsListHeading;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsFundsCGListHeading;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsTransHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsPendingHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId MultiAcctEachShrNum;
   extern CLASS_IMPORT const BFTextFieldId PlanType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId GSTExempt;
   extern CLASS_IMPORT const BFTextFieldId DTAType;
   extern CLASS_IMPORT const BFTextFieldId RegisteredTaxTypes;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId ActiveOnly;
   extern CLASS_IMPORT const BFTextFieldId BackWithholdTax;
   extern CLASS_IMPORT const BFTextFieldId HoldDivPymt;

   extern CLASS_IMPORT const BFTextFieldId SettlementRuleExist;
   extern CLASS_IMPORT const BFTextFieldId EligExtTrfGainLoss;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeGuardOn;
   extern CLASS_IMPORT const BFDateFieldId NextMFRProcessDate;
   extern CLASS_IMPORT const BFTextFieldId IsMFRAccount;

   //P0178584_FN01_NewPopUpMSG
   extern CLASS_IMPORT const BFTextFieldId StaleChqStage;
   ///End - P0178584_FN01_NewPopUpMSG

   extern CLASS_IMPORT const BFTextFieldId Name1;
   extern CLASS_IMPORT const BFTextFieldId TINExists;
   extern CLASS_IMPORT const BFTextFieldId TerritoryCode;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFDateFieldId InitialDate;
   extern CLASS_IMPORT const BFTextFieldId AcctFeeModelAssociated;
   extern CLASS_IMPORT const BFTextFieldId IsTrlFeeAcctLevelApp;
   extern CLASS_IMPORT const BFTextFieldId AcctRegulatoryExist;
   extern CLASS_IMPORT const BFTextFieldId PendingFATCASrch;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeExist;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory;
   extern CLASS_IMPORT const BFTextFieldId TaxFormsAppl;
   extern CLASS_IMPORT const BFTextFieldId RemarkAlertExists;
   extern CLASS_IMPORT const BFTextFieldId AlertMessageExists;
   extern CLASS_IMPORT const BFTextFieldId AlertViewed;
   extern CLASS_IMPORT const BFTextFieldId AcctOpenCloseDates;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsFundsCFHeadingSet;
}

namespace AWD
{  
   extern const I_CHAR *Account_Num;
   extern const I_CHAR *Business_Area;
   extern const I_CHAR *System_ID;
   extern const I_CHAR *LookupOrder;
   extern const I_CHAR *Ascending;
   extern const I_CHAR *Descending;
}

namespace SessionTags
{
   extern const I_CHAR *SESSION;
   extern const I_CHAR *MGMCO;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
   extern CLASS_IMPORT I_CHAR * const SETTLE_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CONTENT;
   extern CLASS_IMPORT I_CHAR * const SHR_FUND_SPONSOR_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const TAX_EXEMPT_AUTHORIZATION;
   extern CLASS_IMPORT I_CHAR * const SHR_FUND_BROKER;
   extern CLASS_IMPORT I_CHAR * const ACCT_LVL_CUT_OFF_TIME;
   extern CLASS_IMPORT I_CHAR * const CLONE_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_TRADING_OVERRIDES;
   extern CLASS_IMPORT I_CHAR * const AFFLUENT;
   extern CLASS_IMPORT I_CHAR * const ACCT_LEVEL_SETTLEMENT_RULE;
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZATION_INFO;
   extern CLASS_IMPORT I_CHAR * const TFSA_CONTRIBUTION_INFO;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_STATIC_DATA_VERIFY;
   extern CLASS_IMPORT I_CHAR * const RESP_NOTIONAL_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const RESP_ACCOUNT_INFROMATION;
   extern CLASS_IMPORT I_CHAR * const RESP_INFO;
   extern CLASS_IMPORT I_CHAR * const RESP_ACCOUNT_TERMINATION;
   extern CLASS_IMPORT I_CHAR * const RESP_ZERO_GRANT;
   extern CLASS_IMPORT I_CHAR * const RESP_INTERFACE_FILE;
   extern CLASS_IMPORT I_CHAR * const ACCT_GUARNT_GUARD_OPTN;
   extern CLASS_IMPORT I_CHAR * const VALUE_VARIATION;
   extern CLASS_IMPORT I_CHAR * const ACCT_FEE_MODEL_ASSOCIATION;
   extern CLASS_IMPORT I_CHAR * const ACCT_REGIS_MAINT;
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_GROUPING;
   extern CLASS_IMPORT I_CHAR * const PRIVATE_WEALTH_INFO;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_GROUPING_INFO;
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANTS;
   extern CLASS_IMPORT I_CHAR * const RESP_NOTIONAL_ACTIVITY;
   extern CLASS_IMPORT I_CHAR * const RESP_NOTIONAL_BALANCE;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANT_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const REG_PLAN_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ACCT_ROUNDING_RULE;
   extern CLASS_IMPORT I_CHAR * const ACCT_DELETION_REVIEW;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT ;
}
namespace BANKENTITY
{
   I_CHAR * const SHAREHOLDER = I_("10");
   I_CHAR * const  ACCOUNT  = I_("14");
}
namespace ADDRLIT
{
   const I_CHAR * const RETMAIL_TAB = I_("ReturnMailTab");
}

namespace ACCOUNT_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const PRIVATE_WEALTH_OPT_OUT;
}

namespace ALERT_MSG_PARAM
{
    extern CLASS_IMPORT I_CHAR * const ACCOUNT_NUM;
    extern CLASS_IMPORT I_CHAR * const FROM_SCREEN;
    extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_NUM;
}

namespace ALERT_MSG_OPENED_FROM
{
    extern CLASS_IMPORT I_CHAR * const ACCT_DETL;
}

//******************************************************************************
// Public methods
//******************************************************************************

BaseAccountDetailsDlg::BaseAccountDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( BaseAccountDetailsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_AwdActive( NO_AWD )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   lastFocus = 0;
   lastFocusFunds = 0;
   lastFocusEntitiesIds = 0;
   lastFocusEntities = 0;
   lastFocusTransactions = 0;
   lastFocusKanaAddr = 0;
   lastFocusKanjiAddr = 0;
   TranPendingState = 1;
   m_hAccel = NULL;

   flgTabPressed = false;
   //{{AFX_DATA_INIT(BaseAccountDetailsDlg)
   m_rbEntities = -1;
   m_rbTransacHist = -1;
   //}}AFX_DATA_INIT
}

BaseAccountDetailsDlg::~BaseAccountDetailsDlg()
{
   // reset the position so that other dlgs can position correctly
   DetailDlgRect.left = -1;
   DetailDlgRect.top = -1;
   DetailDlgRect.right = -1;
   DetailDlgRect.bottom = -1;
}
//******************************************************************************

void BaseAccountDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BaseAccountDetailsDlg)
   DDX_Control(pDX, IDC_ALL_FUNDS, m_ckbAllFunds);
   DDX_Control(pDX, IDC_LV_KANJI_ADDR, m_lvKanjiAddr);
   DDX_Control(pDX, IDC_CMB_ADDR_SEL, m_cmbAddrSel);
   DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
   DDX_Control(pDX, IDC_BTN_ADMIN_DATES, m_btnAdminDates);
   DDX_Control(pDX, IDC_LB_OPTIONS, m_lbOptions);
   DDX_Control(pDX, IDC_LB_CAUTIONS, m_lbCautions);
   DDX_Control(pDX, IDC_LB_ATTRIB, m_lbAttributes);
   DDX_Control(pDX, IDC_LV_KANA_ADDR, m_lvKanaAddr);
   DDX_Control(pDX, IDC_LV_ENTITIES_IDS, m_lvEntitiesIds);
   DDX_Control(pDX, IDC_LV_HISTORY_TRADES, m_lvTransactions);
   DDX_Control(pDX, IDC_LV_FUNDS, m_lvFunds);
   DDX_Control(pDX, IDC_LV_ENTITIES, m_lvEntities);
   DDX_Control(pDX, IDC_LV_ACCOUNTS, m_lvAccounts);
   DDX_Radio(pDX, IDC_RB_ENTITIES, m_rbEntities);
   DDX_Radio(pDX, IDC_RB_TRANS_HISTORY, m_rbTransacHist);
   DDX_Control(pDX, IDC_ACTIVE_FUNDS_ONLY, m_ckbActiveFunds);

   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(BaseAccountDetailsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BaseAccountDetailsDlg)
ON_BN_CLICKED(IDC_RB_ENTITIES, OnRbEntities)
ON_BN_CLICKED(IDC_RB_SHAREHOLDER_ADDRESSES, OnRbShareholderAddresses)
ON_LBN_DBLCLK(IDC_LB_ATTRIB, OnDblclkLbAttrib)
ON_NOTIFY(NM_DBLCLK, IDC_LV_HISTORY_TRADES, OnDblclkLvHistoryTrades)
ON_LBN_DBLCLK(IDC_LB_OPTIONS, OnDblclkLbOptions)
ON_BN_CLICKED(IDC_RB_TRANS_HISTORY, OnRbTransHistory)
ON_BN_CLICKED(IDC_RB_PENDING_TRADES, OnRbPendingTrades)
ON_LBN_DBLCLK(IDC_LB_CAUTIONS, OnDblclkLbCautions)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ENTITIES, OnDblclkLvEntities)
ON_BN_CLICKED(IDC_BTN_ADMIN_DATES, OnBtnAdminDates)
ON_LBN_SETFOCUS(IDC_LB_ATTRIB, OnSetfocusLbAttrib)
ON_LBN_SETFOCUS(IDC_LB_CAUTIONS, OnSetfocusLbCautions)
ON_LBN_SETFOCUS(IDC_LB_OPTIONS, OnSetfocusLbOptions)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_ENTITIES_IDS, OnSetfocusLvEntitiesIds)
ON_LBN_KILLFOCUS(IDC_LB_ATTRIB, OnKillfocusLbAttrib)
ON_LBN_KILLFOCUS(IDC_LB_CAUTIONS, OnKillfocusLbCautions)
ON_LBN_KILLFOCUS(IDC_LB_OPTIONS, OnKillfocusLbOptions)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_ACCOUNTS, OnSetfocusLvAccounts)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_ENTITIES, OnSetfocusLvEntities)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_FUNDS, OnSetfocusLvFunds)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_HISTORY_TRADES, OnSetfocusLvHistoryTrades)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_KANA_ADDR, OnSetfocusLvKanaAddr)
ON_NOTIFY(NM_SETFOCUS, IDC_LV_KANJI_ADDR, OnSetfocusLvKanjiAddr)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_ENTITIES, OnKillfocusLvEntities)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_HISTORY_TRADES, OnKillfocusLvHistoryTrades)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_ENTITIES_IDS, OnKillfocusLvEntitiesIds)
ON_COMMAND(ID_ACCEL_ACCOUNTS, OnAccelAccounts)
ON_COMMAND(ID_ACCEL_FUND, OnAccelFund)
ON_COMMAND(ID_ACCEL_CAUTIONS, OnAccelCautions)
ON_COMMAND(ID_ACCEL_OPTIONS, OnAccelOptions)
ON_COMMAND(ID_ACCEL_ATTRIBUTES, OnAccelAttributes)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_KANA_ADDR, OnKillfocusLvKanaAddr)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_KANJI_ADDR, OnKillfocusLvKanjiAddr)
ON_CBN_SELCHANGE(IDC_CMB_ADDR_SEL, OnSelchangeCmbAddrSel)
ON_NOTIFY(NM_DBLCLK, IDC_LV_KANA_ADDR, OnDblclkLvKanaAddr)
ON_NOTIFY(NM_DBLCLK, IDC_LV_KANJI_ADDR, OnDblclkLvKanjiAddr)
ON_WM_MOVE()
ON_LBN_SELCHANGE(IDC_LB_ATTRIB, OnSelchangeLbAttrib)
ON_LBN_SELCHANGE(IDC_LB_CAUTIONS, OnSelchangeLbCautions)
ON_LBN_SELCHANGE(IDC_LB_OPTIONS, OnSelchangeLbOptions)
ON_BN_CLICKED(IDC_BTN_NEW_ACCOUNT, OnBtnNewAccount)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAddCOA)
ON_BN_CLICKED(IDC_ALL_FUNDS, OnAllFunds)
ON_BN_CLICKED(IDC_BTN_AWD, OnBtnAwd)
ON_NOTIFY(NM_CLICK, IDC_LV_ACCOUNTS, OnClickLvAccounts)
ON_NOTIFY(NM_KILLFOCUS, IDC_LV_FUNDS, OnKillfocusLvFunds)
ON_BN_CLICKED(IDC_ACTIVE_FUNDS_ONLY, OnActiveFunds)
ON_BN_CLICKED(IDC_BTN_CLONE_ACCOUNT, OnBtnCloneAcct)
ON_BN_CLICKED(IDC_BTN_FOF, OnBtnFundOfFunds)
ON_BN_CLICKED(IDC_BTN_ALERT_MESSAGES, OnBtnAlertMessage)


//}}AFX_MSG_MAP
ON_MESSAGE(WM_VIEWITEMSELECTED, OnListViewItemChanged)
ON_MESSAGE(UM_OPENALERTMESSAGEDLG,OnOpenAlertMessageBox)

END_MESSAGE_MAP()

//******************************************************************************
// Protected methods
//******************************************************************************

BOOL BaseAccountDetailsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnInitDialog" ) );
   CWaitCursor wait;
   BaseMainDlg::OnInitDialog();

   DString AccountNumber, EntityIdLoc, dstrShowCGMktVal, dstrAcctOpenCloseDateFlag;

   // TODO: Add extra initialization here
   LVCOLUMN lvColumn;
   lvColumn.mask = LVCF_FMT;
   lvColumn.fmt = LVCFMT_RIGHT;
   CString lvColumns;


   m_lvAccounts.Init(this, ifds::AccListHeading /*DBSUBS::LV_AcctListHeadingSet*/, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, CLASSNAME, LV_ACCOUNTDETAILS);

   m_lvEntities.Init(this, ifds::AccDetailsEntityListHeading /*DBSUBS::LV_AccDetailsEntityHeadingSet*/, IFASTBP_PROC::ENTITY_LIST, CLASSNAME, LV_ENTITYDETAILS);

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession*>(getParent()->getBFWorkSession());
   BFFieldId fundHeading = ifds::AccDetailsFundsListHeading;
   if (dstWorkSession->getOption(ifds::ShowCGMktVal, dstrShowCGMktVal, getParent()->getDataGroupId()) <= WARNING &&
       dstrShowCGMktVal.stripAll().upperCase() == YES)
   {
       fundHeading = ifds::AccDetailsFundsCGListHeading;
   }
   else if (dstWorkSession->getOption(ifds::AcctOpenCloseDates, dstrAcctOpenCloseDateFlag, getParent()->getDataGroupId()) <= WARNING &&
       dstrAcctOpenCloseDateFlag == YES)
   {
	   fundHeading = ifds::AccDetailsFundsCFHeadingSet;
   }
   m_lvFunds.Init(this, fundHeading, IFASTBP_PROC::FUNDS_LIST, CLASSNAME, LV_FUNDSDETAILS);

   m_lvTransactions.Init(this, ifds::AccDetailsTransHeadingSet /*DBSUBS::LV_AccDetailsTransHeadingSet*/, IFASTBP_PROC::TRANSACTIONS_LIST, CLASSNAME, LV_HISTORYDETAILS);

   m_lvEntitiesIds.InsertColumn( 0, ( LPCTSTR ) lvColumns , LVCFMT_LEFT, 132 );
   m_lvEntitiesIds.InsertColumn( 1, ( LPCTSTR ) lvColumns , LVCFMT_RIGHT, 172 );
   m_lvEntitiesIds.LoadSettings( CLASSNAME, LV_ENTITYIDS );

   // ying
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      m_lvKanjiAddr.InsertColumn( 0, ( LPCTSTR ) lvColumns , LVCFMT_LEFT, 280 );
   }

   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
   pRadioButton->SetCheck( 1 );

   if( !m_hAccel )
   {
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_DETAILS ) );
   }

   //enableing the details button

   ((CDSTCView*)GetMainView())->enableDetailsButton( true );
/*  This logic has been moved to ::OnPostInitDialog
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   DString dstrMultiAcctEachShrNum;
   if ( dstWorkSession->getOption( ifds::MultiAcctEachShrNum, dstrMultiAcctEachShrNum, getParent()->getDataGroupId() ) <= WARNING )
   {
      if ( dstrMultiAcctEachShrNum.strip() == STRING_YES )
         GetDlgItem( IDC_BTN_NEW_ACCOUNT)->EnableWindow( true );
      else
         GetDlgItem( IDC_BTN_NEW_ACCOUNT)->EnableWindow( false );


   }*/

   
   DString dstrHasFOF;
   getParent()->getField( this, BF::NullContainerId, ACCDETLIT::HAS_FOF, dstrHasFOF, false );
   if ( dstrHasFOF.strip() == YES )
      GetDlgItem(IDC_BTN_FOF)->ShowWindow( SW_SHOW );
   else
      GetDlgItem(IDC_BTN_FOF)->ShowWindow( SW_HIDE );

   MoveDialog( GUIPOS_DESKTOPBOTTOM, 0 );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void BaseAccountDetailsDlg::MoveDlg ()
{
   MoveDialog( GUIPOS_TOP, 0 );
   MoveDialog( GUIPOS_DESKTOPLEFT, 0 );
}

//******************************************************************************


void BaseAccountDetailsDlg::SetTransHeading()
{
   m_lvTransactions.DeleteAllColumns();
   m_lvTransactions.Init(this, ifds::AccDetailsTransHeadingSet /*DBSUBS::LV_AccDetailsTransHeadingSet*/, IFASTBP_PROC::TRANSACTIONS_LIST, CLASSNAME, LV_HISTORYDETAILS);
}

//******************************************************************************

void BaseAccountDetailsDlg::SetPendingHeading()
{
   m_lvTransactions.DeleteAllColumns();
   m_lvTransactions.Init(this, ifds::AccDetailsPendingHeadingSet /*DBSUBS::LV_AccDetailsTransHeadingSet*/, IFASTBP_PROC::PENDING_TRADES_LIST, CLASSNAME, LV_HISTORYDETAILS);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   SetMessageStatusBar( TXT_LOAD_DETAILS );
   CWaitCursor wait;

   SetUserAccesFunctionCode(UAF::ACCOUNT_DETAIL);

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   DString dstrMultiAcctEachShrNum;
   if( dstWorkSession->getOption( ifds::MultiAcctEachShrNum, dstrMultiAcctEachShrNum, idDataGroup, false ) <= WARNING )
   {
      DString dstrAcctNumCtrl;
      dstWorkSession->getOption( ifds::AcctNumCtrl, dstrAcctNumCtrl, idDataGroup );
      dstrAcctNumCtrl.strip().upperCase();
      // The add new account button is enabled when multiple share holder account flag is turned on (Yes)
      // and when the AcctNumCtrl <> P (use Shareholder as Primary Key)
      if( ( dstrMultiAcctEachShrNum.strip().upperCase() == Y_STRING ) && ( dstrAcctNumCtrl != P_STRING ) )
         //GetDlgItem( IDC_BTN_NEW_ACCOUNT)->EnableWindow( true );
         // Check user permission.
         addBtnAddForPermissionCheck(IDC_BTN_NEW_ACCOUNT);
      else
         GetDlgItem( IDC_BTN_NEW_ACCOUNT)->EnableWindow( false );

/*
      if ( dstrMultiAcctEachShrNum.strip().upperCase() == Y_STRING )
         addBtnAddForPermissionCheck(IDC_BTN_NEW_ACCOUNT);*/
   }

   fillAccountList();
   //if ( m_lvAccounts.GetItemCount() )
   //m_lvAccounts.SetSelection( 0 );

   DString str, str1, AccNum;
   const DString *keyAccNum;
   getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST ); 
   getParent()->getField( this, ACCDETLIT::ACCOUNT_NUMBER_CODE, AccNum );
   AccNum.strip();
   AccNum.stripLeading( '0' );
   //displayTitle();

   DString dstrAltAccountParam, dstrBrokerCodeParam;
   getParent()->getField( this, ACCDETLIT::ALT_ACCOUNT_NUMBER_CODE, dstrAltAccountParam );
   getParent()->getField( this, ACCDETLIT::BROKER_CODE, dstrBrokerCodeParam );
   dstrAltAccountParam.stripAll();
   dstrAltAccountParam.stripLeading( '0' );
   dstrBrokerCodeParam.stripAll();
   dstrBrokerCodeParam.stripLeading( '0' );

   int i = 0;
   bool bSelectionFound = false;
   do
   {
      //Set focus to the selected AltAccount and BrokerCode
      if( dstrAltAccountParam != I_("") && dstrBrokerCodeParam != I_("") )
      {
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AltAccount, str );
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BrokerCode, str1 );
         str.strip();
         str.stripLeading( '0' );
         str1.strip();
         str1.stripLeading( '0' );
         if( str.upperCase() == dstrAltAccountParam.upperCase() && 
            str1 == dstrBrokerCodeParam )
         {
            if( m_lvAccounts.GetItemCount()>i )
            {
               m_lvAccounts.SetSelection( i );
               bSelectionFound = true;
            }
            break;
         }
      }
      else
      {
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, str );
         str.strip();
         str.stripLeading( '0' );
         if( str == AccNum )
         {
            if( m_lvAccounts.GetItemCount()>i )
            {
               m_lvAccounts.SetSelection( i );
               bSelectionFound = true;
            }
            break;
         }
      }
      i++;
   }
   while( *(keyAccNum = &(getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST )) ) != EMPTY_STRING );
   if( !bSelectionFound )
   {
      if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST ) != NULL_STRING )//;reposition the container on the first item 
         m_lvAccounts.SetSelection( 0 );
   }

   fillCautionsList();

   fillOptionsList();

   fillAttributesList();

   if( m_lbCautions.GetCount() > 0 )
   {
      m_lbCautions.GetText( 0, lastFocusCautions );
   }
   if( m_lbOptions.GetCount() > 0 )
   {
      m_lbOptions.GetText( 0, lastFocusOptions );
   }
   if( m_lbAttributes.GetCount() > 0 )
   {
      m_lbAttributes.GetText( 0, lastFocusAttributes );
   }

   DString EntityId;
   const DString *keyEntity;
   getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_LIST ); 
   getParent()->getField( this, ACCDETLIT::ENTITY_ID_NUMBER, EntityId );
   EntityId.strip();
   EntityId.stripLeading( '0' );

   i = 0;
   do
   {
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, str );
      str.strip();
      str.stripLeading( '0' );
      if( str == EntityId )
      {
         if( m_lvEntities.GetItemCount()>i )
            m_lvEntities.SetSelection( i );
         break;
      }
      i++;
   }
   while( *(keyEntity = &(getParent()->getNextListItemKey( this, IFASTBP_PROC::ENTITY_LIST )) ) != EMPTY_STRING );

   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
   CButton *pRadioButton2 = static_cast < CButton* > ( GetDlgItem( IDC_RB_PENDING_TRADES ) );
   int iCheck = pRadioButton->GetCheck( );
   //int nrListItems = //getParent()->getNumberOfItemsInList( this, ACCDETLIT::PENDING_TRADES_LIST);
   DString strPendingTrades;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PendingTrade, strPendingTrades, false);
   if( iCheck == 1 && strPendingTrades.strip() != I_("Y") )
      pRadioButton2->EnableWindow( false );

   fillCallerInfo();

   // Set AWD Button
   DString  dstrUsingAwd( NULL_STRING );
   getGlobal( USER_GLOBAL, ifds::Using_AWD, dstrUsingAwd );

   if (dstrUsingAwd == I_("1")) 
   {
      m_AwdActive = AWD_SESSION;
   } 
   else if(((CDSTCView*)GetMainView())->isWorkAgentRunning()) 
   {
      m_AwdActive = AWD_PORTAL;
   }
   else
   {
      m_AwdActive = NO_AWD;
   }

   if (m_AwdActive == NO_AWD)
   {
       GetDlgItem( IDC_BTN_AWD )->EnableWindow( false );
   }
   else
   {
       GetDlgItem( IDC_BTN_AWD )->EnableWindow( true );
   }

   GetDlgItem( IDC_BTN_CLONE_ACCOUNT )->EnableWindow( hasReadPermission (UAF::CLONE_ACCOUNT));

   ShowWindow( SW_SHOW );
   SetMessageStatusBar( NULL_STRING );

   /* P0178584_FN01_NewPopUpMSG: 
    * Alert user if the account has Stale Dated/Remitted Cheque/Return mail
    */
   //openSTDChqAndRETMailAlertBox(); 
   //openIWTNonTaxableAlertBox(); //IN2766093 - IWT TIN Warning Message

   openAlertMsgAndRemarkScreen();
}

//******************************************************************************
void BaseAccountDetailsDlg::OnBtnAlertMessage()
{
    openAlertMessageScreen();
}

//******************************************************************************
void BaseAccountDetailsDlg::openAlertMsgAndRemarkScreen()
{
    DString dstrRemarkAlertExists, dstrAlertMessageExists, dstrAlertViewed;
    getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::RemarkAlertExists, dstrRemarkAlertExists, false);
    getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AlertMessageExists, dstrAlertMessageExists, false);
    getParent()->getField(this, BF::NullContainerId, ifds::AlertViewed, dstrAlertViewed, false);

    GetDlgItem(IDC_BTN_ALERT_MESSAGES)->EnableWindow(dstrAlertMessageExists == YES);

    if (dstrAlertViewed != YES && dstrAlertMessageExists == YES)
    {
        getParent()->setField(this, BF::NullContainerId, ifds::AlertViewed, YES, false);
        openAlertMessageScreen();

        if (dstrRemarkAlertExists == YES)
        {
            openRemarkScreen();
        }
    }
}

//******************************************************************************
void BaseAccountDetailsDlg::openAlertMessageScreen()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("openAlertMessageScreen"));

    try
    {
        E_COMMANDRETURN eRtn = CMD_CANCEL;

        DString dstrAccountNum, dstrShrNum;
        getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, dstrAccountNum); 
        getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ShrNum, dstrShrNum);

        setParameter(ALERT_MSG_PARAM::ACCOUNT_NUM, dstrAccountNum);
        setParameter(ALERT_MSG_PARAM::SHAREHOLDER_NUM, dstrShrNum );
        setParameter(ALERT_MSG_PARAM::FROM_SCREEN, ALERT_MSG_OPENED_FROM::ACCT_DETL);

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
//P0178584_FN01_NewPopUpMSG
void BaseAccountDetailsDlg::openSTDChqAndRETMailAlertBox()
{
   TRACE_METHOD( CLASSNAME, I_( "openSTDChqAndRETMailAlertBox" ) );

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   DString strRetMailOrStlDtChqAlert = I_( "N" );
   DString strMarket = DSTCommonFunctions::getMarket();

   if( ( strMarket == MARKET_IDS::CANADA )                        && 
      ( dstWorkSession->getOption( ifds::RetMailOrStlDtChqAlert, 
                                   strRetMailOrStlDtChqAlert, 
                                   idDataGroup, 
                                   false ) <= WARNING )           &&
      ( strRetMailOrStlDtChqAlert == I_( "Y" ))
      )
   {

      /* Note: Currently this part only checks if the account has ReturnedMail/Stale/Remitted cheque.
      If in the future more specific msg is/are required, some code here may have to be modified.
      since, for example, StaleChqStageList contains list of stage.
      */
      long int i = 0;
      DString strIsAcctRunCuratorFile(NULL_STRING),
         strHasAcctBeenUnFrozen(NULL_STRING),
         strStaleChqExists(NULL_STRING),
         strStaleChqStage(NULL_STRING),
         strRemittedChqExists(NULL_STRING),
         strRemittedChqStage(NULL_STRING),
         strRtnMailStage(NULL_STRING);

      getParent()->getField( this, ifds::IsAcctRunCuratorFile, strIsAcctRunCuratorFile, false );
      getParent()->getField( this, ifds::HasAcctBeenUnFrozen, strHasAcctBeenUnFrozen, false );
      getParent()->getField( this, ifds::StaleChqExists, strStaleChqExists, false );
      getParent()->getField( this, ifds::StaleChqStageList, strStaleChqStage, false ); 
      getParent()->getField( this, ifds::RemittedChqExists, strRemittedChqExists, false );
      getParent()->getField( this, ifds::RemittedChqStageList, strRemittedChqStage, false );
      getParent()->getField( this, ifds::RtnMailStageList, strRtnMailStage, false );
      strIsAcctRunCuratorFile.stripAll().upperCase();
      strHasAcctBeenUnFrozen.stripAll().upperCase();
      strStaleChqExists.stripAll().upperCase();
      strStaleChqStage.stripAll().upperCase();
      strRemittedChqExists.stripAll().upperCase();
      strRemittedChqStage.stripAll().upperCase();
      strRtnMailStage.stripAll().upperCase();

      //msg to pop up
      if( strRtnMailStage == NULL_STRING )//stale cheque
      {
         if( strHasAcctBeenUnFrozen == I_("N") &&
            strStaleChqExists == I_("Y") &&
            strStaleChqStage != NULL_STRING)
         {//R1.0.2, R1.1, R1.2, R4.1, R5.0
            i = 1;
         }
      }
      else if(strRtnMailStage != NULL_STRING) // return mail+
      {   //filter unknown stage
         if(DSTCommonFunctions::codeInList( strRtnMailStage, UNCLAIMED_STAGE_CODES_LIST))
         { //Note: Return Mail case is supposed to have only one stage sent for an account
            if(strHasAcctBeenUnFrozen == I_("N") )
            { 
               if (strStaleChqStage == NULL_STRING &&
                  strRemittedChqStage == NULL_STRING)
               { 
                  if(strIsAcctRunCuratorFile == I_("N"))
                  {//R2.1, R2.2
                     i = 3; 
                  }
                  else
                  {
                     // Run in curator file and unclaimed
                     if(strRtnMailStage == I_("S3"))
                     {
                        // R2.0
                        i = 2;
                     }
                  }
               }
               else if (strStaleChqExists == I_("Y") && //stale chq
                  strStaleChqStage != NULL_STRING  &&
                  strRemittedChqExists != I_("Y")) //IN2593683
               { // R3.0, R3.3
                  i = 4;
               }
               else if(strIsAcctRunCuratorFile == I_("Y") && 
                  strRtnMailStage == I_("S3") &&
                  strRemittedChqExists == I_("Y") && //remitted chq
                  strRemittedChqStage != NULL_STRING)
               {// R3.1
                  i = 5;
               }
            }
         }
      }

      PostMessage( UM_OPENALERTMESSAGEDLG, 0, i );

   }

}
// End - P0178584_FN01_NewPopUpMSG

//******************************************************************************
void BaseAccountDetailsDlg::openIWTNonTaxableAlertBox()
{
   TRACE_METHOD( CLASSNAME, I_( "openIWTNonTaxibleAlertBox" ) );

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   if ( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG && dstcWorkSession->isIWTClient( getDataGroupId() ))
   {
      DString accountNum;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum );
      accountNum.strip();
      accountNum.stripLeading( '0' );

      MFAccount* pMFAccount = NULL;
      if ( dstcWorkSession->getMFAccount (getDataGroupId(), accountNum, pMFAccount) <= WARNING &&
           pMFAccount )
      {
         // For non Taxable account, display TIN number warning if there is no TIN number.
         if( pMFAccount->isIWTNonTaxable( getDataGroupId() ) )
         {
            DString dstrIsTinExists;
            getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TINExists, dstrIsTinExists, false );

            if( dstrIsTinExists != I_("Y") )
            {
               PostMessage( UM_OPENALERTMESSAGEDLG, 0, 10 );
            }
         }
      }
   }
}

//******************************************************************************
SEVERITY BaseAccountDetailsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_( "doInit" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
void BaseAccountDetailsDlg::PostCancel( bool /*bCancelStatus*/ ) 
{
   // TODO: Add extra cleanup here

   TRACE_METHOD( CLASSNAME, I_( "Cancel" ) );

   m_lvAccounts.SaveSettings( CLASSNAME, LV_ACCOUNTDETAILS );
   m_lvEntities.SaveSettings( CLASSNAME, LV_ENTITYDETAILS );
   m_lvEntitiesIds.SaveSettings( CLASSNAME, LV_ENTITYIDS );                //Aug 3, 1999
   m_lvFunds.SaveSettings( CLASSNAME, LV_FUNDSDETAILS );
   if( TranPendingState == 1 )
      m_lvTransactions.SaveSettings( CLASSNAME, LV_HISTORYDETAILS );
   else
      m_lvTransactions.SaveSettings( CLASSNAME, LV_PENDINGDETAILS );

   //disable button details on the main screen
   ((CDSTCView*)GetMainView())->enableDetailsButton( false );
   ((CDSTCView*)GetMainView())->enableRemarksButton( false );
}

//******************************************************************************
void BaseAccountDetailsDlg::OnRbEntities() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbEntities" ) );
   // TODO: Add your control notification handler code here

   ListViewControl *pEntitiesListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_ENTITIES ) );
   ListViewControl *pKanjiListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_KANJI_ADDR ) );
   ListViewControl *pKanaListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_KANA_ADDR ) );
   CComboBox *pAddrComboBox = static_cast < CComboBox* > ( GetDlgItem( IDC_CMB_ADDR_SEL ) );

   pEntitiesListView->ShowWindow( SW_SHOW );
   pKanjiListView->ShowWindow( SW_HIDE );
   pKanaListView->ShowWindow( SW_HIDE );   
   pAddrComboBox->ShowWindow( SW_HIDE );

   m_lbOptions.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
}

//******************************************************************************
void BaseAccountDetailsDlg::OnRbShareholderAddresses() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbShareholderAddress" ) );
   // TODO: Add your control notification handler code here
   SetMessageStatusBar( TXT_LOAD_DETAILS );
   CWaitCursor wait;

   ListViewControl *pEntitiesListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_ENTITIES ) );
   ListViewControl *pKanjiListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_KANJI_ADDR ) );
   ListViewControl *pKanaListView = static_cast < ListViewControl* > ( GetDlgItem( IDC_LV_KANA_ADDR ) );
   CComboBox *pAddrComboBox = static_cast < CComboBox* > ( GetDlgItem( IDC_CMB_ADDR_SEL ) );

   pEntitiesListView->ShowWindow( SW_HIDE );
   pKanjiListView->ShowWindow( SW_SHOW );
   pKanaListView->ShowWindow( SW_SHOW );   
   pAddrComboBox->ShowWindow( SW_SHOW );

   fillAddressSelectList();
   pAddrComboBox->SetCurSel( 0 );
   fillShrAddressList();
   m_lbOptions.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   m_lvKanaAddr.SetSelection( lastFocusKanaAddr, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void BaseAccountDetailsDlg::fillAccountInfo() 
{
   TRACE_METHOD( CLASSNAME, I_( "fillAccountInfo" ) );

   DString str, temp, strBranchCode;

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BeneficialOwner, str );
   str.strip();

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BrokerName, str );
   str.strip();
   SetDlgItemText( IDC_TXT_DEALER_NAME, str.c_str() );
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BrokerCode, temp );
   temp.strip();
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BranchName, str );
   str.strip();
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BranchCode, strBranchCode );
   strBranchCode.strip();

   CString slash;
   slash.LoadString( TXT_SLASH );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      temp += ( LPCTSTR )slash + strBranchCode;
   else if( strMarket == MARKET_IDS::JAPAN )
      temp += ( LPCTSTR )slash + str;

   SetDlgItemText( IDC_TXT_DEALER_NUM, temp.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::SlsrepName, str );
   str.strip();
   SetDlgItemText( IDC_TXT_REP_NAME, str.c_str() );
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::Slsrep, temp );
   temp.strip();
   SetDlgItemText( IDC_TXT_REP_NUMBER, temp.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BranchName, str );
   str.strip();
   SetDlgItemText( IDC_TXT_BRANCH_NAME, str.c_str() );
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::BranchCode, temp );
   temp.strip();
   SetDlgItemText( IDC_TXT_BRANCH_NUMBER, temp.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AltAccount, str );
   str.strip();
   SetDlgItemText( IDC_TXT_ALT_ACC_NUMBER, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::EffectiveDate, str );
   str.strip();
   SetDlgItemText( IDC_TXT_EFFECTIVE_DATE, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::DateOfReg, str );
   str.strip();
   SetDlgItemText( IDC_TXT_REGIST_DATE, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::SlsrepAltName, str );
   str.strip();
   SetDlgItemText( IDC_TXT_ALT_REP_NAME, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::InterCode, str );
   str.strip();
   SetDlgItemText( IDC_TXT_INTERMEDIARYCODE, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AcctGroup, str );
   str.strip();
   SetDlgItemText( IDC_TXT_GROUPCODE, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AcctGroupName, str );
   str.strip();
   SetDlgItemText( IDC_TXT_GROUPNAME, str.c_str() );

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::InterAccount, str );
   str.strip();
   SetDlgItemText( IDC_TXT_INTERMEDIARY_ACCNUM, str.c_str() );
}

//******************************************************************************
void BaseAccountDetailsDlg::fillAccountList() 
{
   TRACE_METHOD( CLASSNAME, I_( "fillAccountList" ) );
   m_lvAccounts.PopulateList();
}

//******************************************************************************
bool BaseAccountDetailsDlg::BuildAge( const DString& birthDate, const DString& currDate, const DString& mask, DString& years, DString& months ) 
{
   int mo1, mo2, yr1, yr2, rez_mo;
   DString date1, date2, rez;
   bool flgBadDate = false;

   if( birthDate == NULL_STRING )
   {
      years = NULL_STRING;
      months = NULL_STRING;
      return(true);
   }
   int month_pos = mask.find( I_( "MM" ) );
   int year_pos = mask.find( I_( "yyyy" ) );
   if( DString::npos != month_pos && DString::npos != year_pos )
   {
      date1.assign( birthDate, month_pos, 2);
      date2.assign( currDate, month_pos, 2);
      mo1 = convertToULong( date1 );
      mo2 = convertToULong( date2 );
      if( mo1 == 0 || mo2 == 0 )
         flgBadDate = true;
      rez_mo = mo2 - mo1;
      if( rez_mo < 0 )
         convertIntToString( 12 - ( mo1 - mo2 ), months );
      else
         convertIntToString( mo2 - mo1, months );

      date1.assign( birthDate, year_pos, 4);
      date2.assign( currDate, year_pos, 4);
      yr1 = convertToULong( date1 );
      yr2 = convertToULong( date2 );
      if( yr1 == 0 || yr2 == 0 )
         flgBadDate = true;
      if( rez_mo < 0 )
         convertIntToString( yr2 - yr1 - 1, years );
      else
         convertIntToString( yr2 - yr1, years );
   }
   else if( DString::npos != mask.find( I_( "##" ) ) ) //this case should never be true anymore
   {
      date1.assign( birthDate, 0, 2);
      date2.assign( currDate, 0, 2);
      mo1 = convertToULong( date1 );
      mo2 = convertToULong( date2 );
      if( mo1 == 0 || mo2 == 0 )
         flgBadDate = true;
      rez_mo = mo2 - mo1;
      if( rez_mo < 0 )
         convertIntToString( 12 - ( mo1 - mo2 ), months );
      else
         convertIntToString( mo2 - mo1, months );

      date1.assign( birthDate, 6, 4);
      date2.assign( currDate, 6, 4);
      yr1 = convertToULong( date1 );
      yr2 = convertToULong( date2 );
      if( yr1 == 0 || yr2 == 0 )
         flgBadDate = true;
      if( rez_mo < 0 )
         convertIntToString( yr2 - yr1 - 1, years );
      else
         convertIntToString( yr2 - yr1, years );
   }
   else
      flgBadDate = true;
   return(flgBadDate);
}

//******************************************************************************
void BaseAccountDetailsDlg::fillEntitiesIdsList() 
{
   TRACE_METHOD( CLASSNAME, I_( "fillEntitiesIdsList" ) );

   m_lvEntitiesIds.DeleteAllItems();

   DString str, temp;

   if( getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_LIST ) != EMPTY_STRING )
   {
      getDisplayName( IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, str, false);
      SetDlgItemText( IDC_GRP_ENTITY, str.c_str() );
   }

   DString AsofDate;
   BFDate d( BFDate::today() );
   AsofDate = d.get( BFDate::DF_FSUS );

   DString date1, date2, date_mo, date_yr, rez;
   bool flgBadDate = false;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::DofBirth, str );
   str.strip();
   DString mask = DSTCommonFunctions::getMask( ifds::DofBirth );

   date1.assign( str);
   date2.assign( AsofDate );

   flgBadDate = BuildAge( date1, date2, mask, date_yr, date_mo );
   if( !flgBadDate )
   {
      CString dump, yrs, comma, mnths;
      dump.LoadString( TXT_BIRTHDATE_AGE );
      yrs.LoadString( TXT_YEARS );
      mnths.LoadString( TXT_MONTHS );
      comma.LoadString( TXT_COMMA );
      temp = ( LPCTSTR ) dump;
      rez = str + SPACE_STRING + SPACE_STRING + SPACE_STRING + 
            date_yr + SPACE_STRING + ( LPCTSTR ) yrs + ( LPCTSTR ) comma + date_mo + SPACE_STRING + ( LPCTSTR ) mnths;      
      SetDlgItemText( IDC_TXT_BITHDATE_AGE, rez.c_str() );
   }

   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_IDS_LIST ) == EMPTY_STRING )
      return;

   int i = 0;
   CString strDesc;                 //Aug 4, 1999
   do
   {
      getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, str );
      str.strip();
      getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, temp );
      temp.strip();

      int idx = m_lvEntitiesIds.InsertItem( i++, str.c_str() );

      m_lvEntitiesIds.SetItemText( idx, 1, temp.c_str() );
   }
   while( getParent()->getNextListItemKey( this, IFASTBP_PROC::ENTITY_IDS_LIST ) != EMPTY_STRING );

}

//******************************************************************************
void BaseAccountDetailsDlg::fillEntitiesList() 
{
   TRACE_METHOD( CLASSNAME, I_( "fillEntitiesList" ) );

   m_lvEntities.PopulateList();
   /*int index = m_lvEntities.GetNextSelection( );
   if ( index != -1 )
   {
      DString* key = (DString*)m_lvEntities.GetItemData( index );
      getParent()->setCurrentListItem( this, ACCDETLIT::ENTITY_IDS_LIST, *key );*/
   fillEntitiesIdsList();
   //} else
   //{
   //throw exception : no selection
   //}
}

//******************************************************************************
void BaseAccountDetailsDlg::fillFundList( ) 
{
   TRACE_METHOD( CLASSNAME, I_( "fillFundList" ) );

   DString str, temp, fundCode;
   int i = 0;

   //m_lvFunds.DeleteAllItems();

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_ACTIVE_FUNDS_ONLY ) );

   DString dstrSuppressInactiveFunds;

   if( dstWorkSession->getOption( ifds::SuppressInactiveFunds, dstrSuppressInactiveFunds, idDataGroup, false ) <= WARNING )
   {
      int suppressInactiveFunds = dstrSuppressInactiveFunds.asInteger();

      if (suppressInactiveFunds == 1 ) // default to allfunds, user cannot change
      {
         pRadioButton->SetCheck( 0 );
         m_ckbActiveFunds.EnableWindow( false );
         getParent()->setField(this, ifds::ActiveOnly, I_("N"),false);		

      }
      else if (suppressInactiveFunds == 2 )  // default to active funds only, user cannot change
      {
         pRadioButton->SetCheck( 1 );
         m_ckbActiveFunds.EnableWindow( false );
         getParent()->setField(this, ifds::ActiveOnly, I_("Y"),false);		
      }

      else if (suppressInactiveFunds == 3 )  // default to all funds, user can choose to display only active funds
      {
         pRadioButton->SetCheck( 0 );
         m_ckbActiveFunds.EnableWindow( true );
         getParent()->setField(this, ifds::ActiveOnly, I_("N"),false);						
      }

      else if (suppressInactiveFunds == 4 ) // default to active funds only, user can choose to display both active/inactive funds
      {
         pRadioButton->SetCheck( 1 );
         m_ckbActiveFunds.EnableWindow( true );
         getParent()->setField(this, ifds::ActiveOnly, I_("Y"),false);						
      }

   }

   m_lvFunds.PopulateList();

}

//******************************************************************************
void BaseAccountDetailsDlg::fillTransactionsList( ) 
{
   TRACE_METHOD( CLASSNAME, I_( "fillTransactionsList" ) );

   DString str, temp, str1;
   int i = 0;
   int state = m_ckbAllFunds.GetCheck();
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
   int iCheck = pRadioButton->GetCheck( );
   if( iCheck != 1 )
      return;

   m_lvTransactions.DeleteAllItems();

   if( m_lvFunds.GetItemCount() == 0 )
   {
      SetDlgItemText( IDC_CURRENT_FUND, ( LPCTSTR ) EMPTY_STRING );
      return;
   }
   int index = m_lvFunds.GetNextSelection( );
   if(index == -1) return;
   DString *keyFund = (DString*)m_lvFunds.GetItemData( index );
   getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *keyFund );
   m_lvTransactions.PopulateList();

}

//******************************************************************************
void BaseAccountDetailsDlg::fillPendingTradesList( ) 
{
   TRACE_METHOD( CLASSNAME, I_( "fillPendingTradesList" ) );

   DString str, temp;
   int i = 0;
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
   int iCheck = pRadioButton->GetCheck( );
   if( iCheck == 1 )
      return;
   //m_lvTransactions.DeleteAllItems();
   m_lvTransactions.PopulateList();
}

//******************************************************************************
void BaseAccountDetailsDlg::fillShrAddressList() 
{
   TRACE_METHOD( CLASSNAME, I_( "fillShrAddressList" ) );
}

//******************************************************************************
void BaseAccountDetailsDlg::setGlobalInformation( ) 
{
     DString str, first_name, last_name, name, home_phone, lastAcctNumber;

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, lastAcctNumber );
   setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, lastAcctNumber);
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ShrNum, str );
   setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, str);

   getParent()->getField( this, ACCDETLIT::PHONE_NUMBER, home_phone );
   setGlobal( WORK_GLOBAL, ifds::CallerPhoneNumber, home_phone);

   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_LIST ) == EMPTY_STRING )
      return;
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::JAPAN )
      getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, true );
   else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, false );
   setGlobal( WORK_GLOBAL, ifds::CallerName, name);

   DSTCUserSession &dstcUserSession = dynamic_cast<DSTCUserSession &>(getBFSession()->getUserSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();

   dstcUserSession.setStopNFU (idDataGroup, lastAcctNumber);
}

//******************************************************************************
void BaseAccountDetailsDlg::OnDblclkLbAttrib() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLbAttrib" ) );

   CWaitCursor wait;
   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString strShrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   CListBox *pAttributesListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_ATTRIB ) );
   int itemSelected = pAttributesListBox->GetCurSel();
   if( itemSelected == LB_ERR )
      return;
   CString selectedStr, classificationStr, chequeInformation, strACB, distrOptions, demographicsStr, histMktValStr;
   CString distributionStr, allocationsStr, shareholderStr, historicalAccInfoStr, accInfoStr, entityStr, addressStr, freeUnitsStr;
   CString respInfoStr, respTransactionsStr,riflifStr, ytdContributionStr, hypoRedemption, cstrForeignContent;
   CString cstrAccountReview, cstrPensionInfo, cstrLIFGainLoss, cstrTFSAContributionInfo, cstrRESPNotionalInfo, cstrRESPNotionalBalanceInfo, cstrRESPAcctTermination;
   CString cstrRESPZeroGrant, cstrRESPInterfaceFile, cstrAccountForeignTaxReview;
   CString cstrValueVariation, cstrRESPGrantInfo, cstrRESPNotionalActivity, cstrRESPGrantInfo2;
   CString rdspAcctInfoStr, rdspNotionalActivityStr, rdspNotionalBalStr, rdspInterfaceTransStr;

   pAttributesListBox->GetText( itemSelected, selectedStr );
   classificationStr.LoadString( ROW_DETAILS_ATTRIBUTES_INT_ACCRUED );  
   chequeInformation.LoadString( ROW_DETAILS_ATTRIBUTES_CHEQUE_INFORMATION ); 
   strACB.LoadString( ROW_DETAILS_ATTRIBUTES_ACB );
   distrOptions.LoadString( ROW_DETAILS_ATTRIBUTES_DISTR_OPTIONS );  
   demographicsStr.LoadString( ROW_DETAILS_ATTRIBUTES_DEMOGRAPHICS );   
   histMktValStr.LoadString( ROW_DETAILS_ATTRIBUTES_HIST_MKT_VALUE );
   shareholderStr.LoadString( ROW_DETAILS_ATTRIBUTES_SHAREHOLDER );
   riflifStr.LoadString(ROW_RRIF_LIF_INFO );

   historicalAccInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_HISTORICAL_ACCOUNT_INFORMATION );
   accInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNT_INFORMATION );
   entityStr.LoadString( ROW_DETAILS_ATTRIBUTES_ENTITY );
   addressStr.LoadString( ROW_DETAILS_ATTRIBUTES_ADDR_BOOK_MAIL_ASSIGN );
   freeUnitsStr.LoadString( ROW_DETAILS_ATTRIBUTES_FREE_UNITS );
   respInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_RESPINFO );
   respTransactionsStr.LoadString( ROW_DETAILS_ATTRIBUTES_RESPTRANSACTIONS );
   ytdContributionStr.LoadString ( ROW_DETAILS_ATTRIBUTES_YTDCONTRIBUTIONS );
   hypoRedemption.LoadString( ROW_DETAILS_ATTRIBUTE_HYPOTHETICAL_REDEMPTION );		
   cstrForeignContent.LoadString( ROW_DETAILS_ATTRIBUTES_FOREIGN_CONTENT_WORKSHEET );	
   cstrAccountReview.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNTREVIEW );
   cstrPensionInfo.LoadString( ROW_DETAILS_ATTRIBUTES_PENSION_INFO );   
   cstrTFSAContributionInfo.LoadString( ROW_DETAILS_TFSA_CONTRIBUTION_INFO );  
   cstrRESPNotionalInfo.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL );
   cstrRESPNotionalBalanceInfo.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL_BALANCE );
   cstrRESPAcctTermination.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_ACCOUNT_TERMINATION );
   cstrRESPZeroGrant.LoadString( ROW_DETAILS_ATTRIBUTES_ZERO_GRANT_REPAYMENT );
   cstrRESPInterfaceFile.LoadString( ROW_DETAILS_ATTRIBUTES_INTERFACE_FILE );
   cstrRESPGrantInfo.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_GRANT_INFO );
   cstrRESPGrantInfo2.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_GRANT_INFO2 );
   cstrRESPNotionalActivity.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL_ACTIVITY );
   cstrAccountForeignTaxReview.LoadString( ROW_DETAILS_ATTRIBUTES_FOREIGN_TAX_REVIEW );
   cstrValueVariation.LoadString(ROW_DETAILS_VALUE_VARIATION);
   // For the specifical use of the Canada market
   CString guaranteeInfoStr, 
      contractInfoStr,
      cstrTaxExemptAuthorization;

   //Tax Exemption Authroization
   cstrTaxExemptAuthorization.LoadString(ROW_DETAILS_ATTRIBUTES_TAX_EXEMPT_AUTHORIZATION);

   rdspAcctInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_ACCOUNT_INFORMATION );
   rdspNotionalActivityStr.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_NOTIONAL_ACTIVITY );
   rdspNotionalBalStr.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_NOTIONAL_BALANCE );
   rdspInterfaceTransStr.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_INTERFACE_TRANSACTIONS );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      guaranteeInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_GUARANTEE );
      contractInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_CONTRACT );
      cstrLIFGainLoss.LoadString( ROW_LIF_GAIN_LOSS );	  
      DString strTaxTypeDesc;
      getParent()->getField( this, ifds::TaxType, strTaxTypeDesc, true );         
      cstrLIFGainLoss = strTaxTypeDesc.c_str() + CString(" ") + cstrLIFGainLoss;
   }

   CString esopStr;
   esopStr.LoadString(ROW_DETAILS_ATTRIBUTES_ESOPINFO);

   CString asPensionPlanStr;
   DString dstrTaxType;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, dstrTaxType, false );
   dstrTaxType.strip();

   if( dstrTaxType == I_( "P" ) )
   {
      asPensionPlanStr.LoadString( ROW_DETAILS_ATTRIBUTES_AS_PENSION );
   }

   CString cstrManagementFee; 
   cstrManagementFee.LoadString( ROW_DETAILS_ATTRIBUTES_MANAGEMENT_FEE );

   CString attrEStatement;
   attrEStatement.LoadString( ROW_DETAILS_ATTRIBUTES_ESTATEMENT );

   CString attrFeeModel;
   attrFeeModel.LoadString( ROW_DETAILS_ATTRIBUTES_FEE_MODEL );

   CString cstrTrailerFee;
   cstrTrailerFee.LoadString( ROW_DETAILS_ATTRIBUTES_TRAILERFEE_SETUP );

   CString cstrInvestmentHistoryList;
   cstrInvestmentHistoryList.LoadString ( ROW_DETAILS_ATTRIBUTES_INVESTMENT_HISTORY );

   CString cstrAccountCommitment;
   cstrAccountCommitment.LoadString (ROW_DETAILS_ATTRIBUTES_ACCOUNT_COMMITMENT);

   CString cstrTaxSlips;
   cstrTaxSlips.LoadString(ROW_DETAILS_TAX_SLIPS);

   CString cstrRegExtrAcct;
   cstrRegExtrAcct.LoadString(ROW_DETAILS_ATTRIBUTES_REG_ACCT_INFO_REV);

   bool bModal = false;   // Default to modeless
   E_COMMANDRETURN eRtn = CMD_OK;

   try
   {
      if( selectedStr == classificationStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_INTEREST_ACCRUED );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCRUALS, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == chequeInformation )
      {
         setParameter( CHQPROC::ACCOUNT_NUM_VALUE, strAcctNum );
         setParameter( CHQPROC::IGNOREDNF, I_( "Y" ) );
         setParameter( CHQ_STATUS_VALUE, I_( "ALL" ) );

         SetMessageStatusBar( TXT_LOAD_CHEQUE_INFORMATION );
         eRtn = invokeCommand( getParent(), CMD_BPROC_CHEQUE, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == strACB )
      {
         int transIndex = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
         if( transIndex == -1 )
         {
            setParameter( FUND_CODE, NULL_STRING );
            setParameter( CLASS_CODE, NULL_STRING );
            setParameter( ACCOUNT_NUM, strAcctNum );
            SetMessageStatusBar( TXT_LOAD_ACB );
            eRtn = invokeCommand( getParent(), CMD_BPROC_ACB, PROC_NO_TYPE, bModal, NULL );
            SetMessageStatusBar( NULL_STRING );
            return;
         }
         DString* key = (DString*)m_lvFunds.GetItemData( transIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key );
         DString str;

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, str );
         str.strip();
         setParameter( FUND_CODE, str );

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxClassCode, str );
         str.strip();
         setParameter( CLASS_CODE, str );

         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_ACB );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACB, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == distrOptions )
      {
         int transIndex = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
         if( transIndex == -1 )
         {
            setParameter( FUND_CODE, NULL_STRING );
            setParameter( CLASS_CODE, NULL_STRING );
            setParameter( ACCOUNT_NUM, strAcctNum );
            SetMessageStatusBar( TXT_LOAD_DISTRIBUTION );
            eRtn = invokeCommand( getParent(), CMD_BPROC_DISTRIBUTION, PROC_NO_TYPE, bModal, NULL );
            SetMessageStatusBar( NULL_STRING );
            return;
         }
         DString* key = (DString*)m_lvFunds.GetItemData( transIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key );
         DString str;

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, str );
         str.strip().upperCase();
         setParameter( FUND_CODE, str );

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxClassCode, str );
         str.strip().upperCase();
         setParameter( CLASS_CODE, str );

         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_DISTRIBUTION );
         eRtn = invokeCommand( getParent(), CMD_BPROC_DISTRIBUTION, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == demographicsStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_DEMOGRAPHICS );
         eRtn = invokeCommand( getParent(), CMD_BPROC_DEMOGRAPHICS, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == histMktValStr )
      {
         int transIndex = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
         if( transIndex == -1 )
         {
            setParameter( FUND_CODE, NULL_STRING );
            setParameter( CLASS_CODE, NULL_STRING );
            setParameter( ACCOUNT_NUM, strAcctNum );
            SetMessageStatusBar( TXT_LOAD_HISTORICAL_MARKET_VALUE );
            eRtn = invokeCommand( getParent(), CMD_BPROC_HISTORICAL_MARKET_VALUE, PROC_NO_TYPE, bModal, NULL );
            SetMessageStatusBar( NULL_STRING );
            return;
         }
         DString* key = (DString*)m_lvFunds.GetItemData( transIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key );
         DString str;

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, str );
         str.strip();
         setParameter( FUND_CODE, str );

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxClassCode, str );
         str.strip();
         setParameter( CLASS_CODE, str );

         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_HISTORICAL_MARKET_VALUE );
         eRtn = invokeCommand( getParent(), CMD_BPROC_HISTORICAL_MARKET_VALUE, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == addressStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         setParameter( SHAREHOLDER_NUM,strShrNum);
         SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == entityStr )
      {
         int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
         if( entityIndex == -1 )// There is no account selected
            return;
         DString *key = ( DString* ) m_lvEntities.GetItemData( entityIndex );

         setParameter( KEY, *key );
         setParameter( ACCOUNT_NUM, strAcctNum );

         SetMessageStatusBar( TXT_LOAD_ENTITY );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }

      else if( selectedStr == riflifStr )
      {
         DString str;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, str );
         str.stripAll();
         setParameter( RRIF_LIF_LRIF::LAST_NAME_FIELD, str);

         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, str );
         str.stripAll();
         setParameter( RRIF_LIF_LRIF::FIRST_NAME_FIELD, str);

         setParameter( RRIF_LIF_LRIF::ACCOUNT_NUMBER_FIELD, strAcctNum );
         setParameter( RRIF_LIF_LRIF::SHAREHOLDER_FIELD, strShrNum);

         SetMessageStatusBar( TXT_LOAD_RIF_LIF );
         eRtn = invokeCommand( getParent(), CMD_BPROC_RRIF_LIF_LRIF_INFO, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }

      else if( selectedStr == shareholderStr )
      {
         setParameter( SHAREHOLDER_NUM, strShrNum );

         //not a NASU process
         setParameter( NASULIT::CREATING_SHAREHOLDER, NO );
         setParameter( NASULIT::CREATING_ACCOUNT, NO );
         SetMessageStatusBar( TXT_LOAD_SHAREHOLDER );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SHAREHOLDER, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == accInfoStr )
      {
         setParameter( SHAREHOLDER_NUM, strShrNum );
         setParameter( ACCINFOPROC::ACCOUNT_NUM, strAcctNum );
         //not a NASU flow, here is a maintenance
         setParameter( NASULIT::CREATING_ACCOUNT, NO );
         setParameter( NASULIT::CREATING_SHAREHOLDER, NO );
         SetMessageStatusBar( TXT_LOAD_ACCOUNT_INFORMATION );

         //xyz add following lines for maintenance an exist account
         //int numPendListItems = getParent()->getNumberOfItemsInList( this, ACCDETLIT::PENDING_TRADES_LIST);
         DString strPendingTrades;
         getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PendingTrade, strPendingTrades, false);
         if( strPendingTrades.strip() != I_("Y") )
            setParameter( ACCTINFO::EMPTY_PENDING, YES );
         else
            setParameter( ACCTINFO::EMPTY_PENDING, NO );

         int numTranListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::TRANSACTIONS_LIST);
         if( numTranListItems == 0 )
            setParameter( ACCTINFO::EMPTY_TRANSACTION, YES );
         else
            setParameter( ACCTINFO::EMPTY_TRANSACTION, NO );

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCINFO, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( /*( selectedStr == shareholderStr ) || */( selectedStr == historicalAccInfoStr ) /*|| 
               ( selectedStr == accInfoStr )*/ )
      {
         DString str;
         int accountIndex = m_lvAccounts.GetNextItem( -1, LVNI_SELECTED );
         if( accountIndex == -1 )// There is no account selected
            return;
         DString* key = (DString*)m_lvAccounts.GetItemData( accountIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, *key );
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, str );
         str.strip();
         str.stripLeading( '0' );
         DString name;

         setParameter( ACCOUNT_NUM, strAcctNum );

         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::JAPAN )
            getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, true );
         else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, false );
         setParameter( NAME, name);
         setParameter( I_("TYPE"), I_("ACCT") );
         SetMessageStatusBar( TXT_LOAD_HISTORICAL_ACCOUNT );
         eRtn = invokeCommand( getParent(), CMD_BPROC_HISTORICAL_INFO /*CMD_BPROC_HISTORICAL_ACCOUNT*/, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }

      else if( selectedStr == freeUnitsStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_FREE_UNITS );
         eRtn = invokeCommand( getParent(), CMD_BPROC_FREEUNIT, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if (selectedStr == guaranteeInfoStr)
      {
         SetMessageStatusBar( TXT_LOAD_GUARANTEE );

         DString urlParamsIDI;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("GuaranteeInformation"));        

         DString dstrEntityName;

         CString cstrGuaranteeInfo,
            cstrInfoShr,
            cstrAccountNumLabel;
         cstrGuaranteeInfo.LoadString(TXT_ACCOUNT_GUARANTEE);
         cstrInfoShr.LoadString(TXT_SHRHLDR_INFO);
         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
            getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                                       strAcctNum,dstrEntityName);

		 DString strLastName(I_("")), strFirstName(I_("")), strName(I_(""));
		 int nPos = 0;

		 if (dstrEntityName != NULL_STRING && !dstrEntityName.strip().empty())
		 {						 
			 if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
			 {
				 strName = dstrEntityName;				 
			 }
			 else 
			 {
				 nPos = dstrEntityName.pos( I_(";") );
				 strLastName = dstrEntityName.substr(0, nPos);
				 strFirstName = dstrEntityName.substr(nPos+1, dstrEntityName.length());	
				 strName = strLastName + I_( " " ) + strFirstName;
			 }
		 }

		 addIDITagValue (urlParamsIDI, I_("EntityName"), strName.strip());	

		 setParameter (I_("UrlParams"), urlParamsIDI);	

         DString strBrowserTitle(cstrGuaranteeInfo);
         strBrowserTitle += cstrInfoShr;
         strBrowserTitle += strShrNum;
         strBrowserTitle += cstrAccountNumLabel;
         strBrowserTitle += strAcctNum;
         strBrowserTitle += I_(" ");
         strBrowserTitle += dstrEntityName;

         setParameter( I_("BrowserTitle"), strBrowserTitle);

         // inovke the guarantee info
         E_COMMANDRETURN eRtn = 
            invokeCommand (getParent(), CMD_BPROC_GUARANTEEINFO_BROWSER, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if (selectedStr == contractInfoStr)
      {
         setParameter( CONTRACT::SHAREHOLD_NUMBER, strShrNum);
         setParameter( CONTRACT::ACCOUNT_NUMBER, strAcctNum );

         // If The Transaction List is empty,  the Guarantee button of ContractInfoDlg should be disable.
         DString strTransIdEmpty;
         if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::TRANSACTIONS_LIST ) == EMPTY_STRING )
            strTransIdEmpty = I_("Y");
         else
            strTransIdEmpty = I_("N");
         setParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );

         SetMessageStatusBar( TXT_LOAD_CONTRACT );
         eRtn = invokeCommand( getParent(), CMD_BPROC_CONTRACTINFO, 
                               PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == respInfoStr )
      {
         SetMessageStatusBar (TXT_LOAD_RESPINFO);
         if (getParent()->hasReadPermission( UAF::RESP_ACCOUNT_INFROMATION ))
         {
            DString urlParamsIDI;
            E_COMMANDRETURN eRtn = CMD_OK;

            setParameter( I_( "AccountNum" ), strAcctNum );
            setParameter( I_( "from_screen" ), I_( "Account" ) );

            addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
            addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPAccountInfo"));

            setParameter (I_("UrlParams"), urlParamsIDI);

            CString cstrRESP;
            cstrRESP.LoadString(TXT_RESP_ACCT_INFO);
            setParameter (I_("BrowserTitle"), DString(cstrRESP) + strAcctNum);
            setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

            // inovke new resp account info browser screen.
            eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_ACCOUNT_INFO, PROC_NO_TYPE, true, NULL);		 
         }
         else if (getParent()->hasReadPermission (UAF::RESP_INFO))
         {
            DString str;

            getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, str );
            str.stripAll();
            setParameter( RESPINFONAMES::LAST_NAME_FIELD, str);

            getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, str );
            str.stripAll();
            setParameter( RESPINFONAMES::FIRST_NAME_FIELD, str);

            setParameter( RESPINFONAMES::ACCOUNT_NUMBER_FIELD, strAcctNum );
            setParameter( RESPINFONAMES::SHAREHOLDER_FIELD, strShrNum);

            eRtn = invokeCommand (getParent(), CMD_BPROC_RESPINFO, PROC_NO_TYPE, bModal, NULL);
         }
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == respTransactionsStr )
      {
         DString str;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, str );
         str.stripAll();
         setParameter( RESPTRANSACTIONSNAMES::LAST_NAME_FIELD, str);

         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, str );
         str.stripAll();
         setParameter( RESPTRANSACTIONSNAMES::FIRST_NAME_FIELD, str);

         setParameter( RESPTRANSACTIONSNAMES::ACCOUNT_NUMBER_FIELD, strAcctNum );
         setParameter( RESPTRANSACTIONSNAMES::HISTORY_PENDING_FIELD, RESPTRANSACTIONSNAMES::HISTORY );
         setParameter( RESPTRANSACTIONSNAMES::SHAREHOLDER_FIELD, strShrNum);

         SetMessageStatusBar( TXT_LOAD_RESPTRANSACTIONS );
         eRtn = invokeCommand( getParent(), CMD_BPROC_RESPTRANSACTIONS, 
                               PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == esopStr )
      {
         setParameter( ESOP::ACCOUNT_NUMBER, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_ESOP_INFO);
         //eRtn = invokeCommand( getParent(), CMD_BPROC_ESOPINFO, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == ytdContributionStr )
      {
         setParameter( YTD::ACCOUNT_NUM, strAcctNum );
         setParameter( YTD::SHR_NUM, strShrNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_YTD_CONTRIBUTION, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar ( NULL_STRING );
      }
      else if( selectedStr == asPensionPlanStr )
      {

         SetMessageStatusBar( TXT_LOAD_AS_PENSION );
         setParameter( ASPENSIONPLANLIT::ACCOUNT_NUM, strAcctNum );
         setParameter( ASPENSIONPLANLIT::SHAREHOLDER_NUM, strShrNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_AS_PENSION_PLAN, 
                               PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrManagementFee )
      {
         SetMessageStatusBar( TXT_LOAD_FEE_PARAM );
         setParameter( ASPENSIONPLANLIT::ACCOUNT_NUM, strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_FEE_PARAMETER, 
                               PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );       
      }
      else if( selectedStr == hypoRedemption )
      {
         SetMessageStatusBar( TXT_LOAD_HYPO_REDEMP );
         setParameter( HYPO_RED::ACCOUNT_NUMBER, strAcctNum );
         DString strFirstSettleDate;
         getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::FirstSettleDate, strFirstSettleDate, false);
         if (!strFirstSettleDate.strip().empty())
         {
            eRtn = invokeCommand( getParent(), CMD_BPROC_HYPO_RED, 
               PROC_NO_TYPE, false, NULL );
         }
         else
         {
            //show error wrong amount
            CString strError;
            strError.LoadString(TXT_NO_HOLDINGS);
            AfxMessageBox(strError, MB_OK | MB_ICONSTOP);
         }
         SetMessageStatusBar( NULL_STRING );
      }
      else if ( selectedStr == cstrForeignContent )
      {
         SetMessageStatusBar( TXT_LOAD_FOREIGN_CONTENT_WORKSHEET );
         setParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     strAcctNum );
         setParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, strShrNum );
         eRtn = invokeCommand( getParent(), 
                               CMD_BPROC_FOREIGN_CONTENT_WORKSHEET, 
                               PROC_NO_TYPE, 
                               bModal, 
                               NULL 
                              );

         SetMessageStatusBar( NULL_STRING ); 
      }
      else if( selectedStr == cstrAccountReview )
      {
         SetMessageStatusBar( TXT_LOAD_ACCOUNTREVIEW );

         setParameter( ACCOUNTREVIEWLITERALS::ACCOUNT_NUM,        strAcctNum );
         setParameter( ACCOUNTREVIEWLITERALS::SHAREHOLDER_NUMBER, strShrNum );	

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCOUNTREVIEW, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );      
      }
      else if( selectedStr == cstrTaxExemptAuthorization )
      {
         SetMessageStatusBar( TXT_LOAD_TAX_EXEMPT_AUTHORIZATION );
         setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_TAX_EXEMPT_AUTHORIZATION, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );      
      }
      else if( selectedStr == cstrPensionInfo )
      {
         SetMessageStatusBar( TXT_LOAD_PENSION_INFO );
         setParameter( PENSION_INFO::ACCOUNT_NUM, strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_PENSION_INFO, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );      
      }
      else if( selectedStr == attrEStatement )
      {
         SetMessageStatusBar( TXT_LOAD_ESTATEMENT );
         setParameter( I_("ACCOUNT_NUM_PARAM"), strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ESTATEMENT, PROC_NO_TYPE, bModal, NULL );
         //eRtn = invokeCommand( getParent(), CMD_GUI_ESTATEMENT, PROC_NO_TYPE, bModal, NULL );

         SetMessageStatusBar( NULL_STRING );      
      }
      else if( selectedStr == attrEStatement )
      {
         SetMessageStatusBar( TXT_LOAD_ESTATEMENT );
         setParameter( I_("ACCOUNT_NUM_PARAM"), strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ESTATEMENT, PROC_NO_TYPE, bModal, NULL );
         //eRtn = invokeCommand( getParent(), CMD_GUI_ESTATEMENT, PROC_NO_TYPE, bModal, NULL );

         SetMessageStatusBar( NULL_STRING );      
      }
      else if( selectedStr == attrFeeModel )
      {
         SetMessageStatusBar( TXT_LOAD_FUND_SPONSOR_FEE_MODEL );
         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDSPONSOR_FEE_MODEL, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrLIFGainLoss )
      {
         DString urlParamsIDI, dstrTaxType;
         E_COMMANDRETURN eRtn = CMD_OK;

         SetMessageStatusBar( TXT_LOAD_LIF_GAIN_LOSS );
         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
         addIDITagValue (urlParamsIDI, I_("screen"), I_("LIFGainLoss")); //DesktopWeb conversion

         setParameter (I_("UrlParams"), urlParamsIDI);
         getParent()->getField(this, ifds::TaxType, dstrTaxType, true );
         dstrTaxType.strip();
         CString cstrGnLoss;
         cstrGnLoss.LoadString(TXT_GAIN_LOSS_ACCTNUM);
         setParameter (I_("BrowserTitle"), dstrTaxType+DString(cstrGnLoss) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_LIF_GAIN_LOSS, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrTFSAContributionInfo)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         SetMessageStatusBar( TXT_LOAD_LIF_GAIN_LOSS );
         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("TFSAContribInfo"));

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrTFSAMsg;

         cstrTFSAMsg.LoadString(TXT_TFSA_CONTR_WITHDRAW_INFO);
         setParameter (I_("BrowserTitle"), DString(cstrTFSAMsg) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_TFSA_CONTRIBUTION_INFO, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
	  else if( selectedStr == cstrRESPNotionalInfo)
	  {
		  DString urlParamsIDI;
		  E_COMMANDRETURN eRtn = CMD_OK;

		  CString cstrRESPInfo;
		  cstrRESPInfo.LoadString(TXT_RESP_NOT_INFO);

		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPNotional")); //DesktopWeb conversion

		  setParameter( I_("AccountNum" ), strAcctNum );
		  setParameter (I_("UrlParams"), urlParamsIDI);
		  setParameter (I_("BrowserTitle"), DString(cstrRESPInfo) + strAcctNum);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

		  eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_NOTIONAL_INFO, PROC_NO_TYPE, true, NULL); 
		  SetMessageStatusBar( NULL_STRING );
	  }
	  else if( selectedStr == cstrRESPNotionalBalanceInfo)
	  {
		  DString urlParamsIDI;
		  E_COMMANDRETURN eRtn = CMD_OK;

		  CString cstrRESPInfo;
		  cstrRESPInfo.LoadString(TXT_RESP_NOT_INFO);
		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPNotionalBalance")); //DesktopWeb conversion

		  setParameter( I_("AccountNum" ), strAcctNum );
		  setParameter (I_("UrlParams"), urlParamsIDI);
		  setParameter (I_("BrowserTitle"), DString(cstrRESPInfo) + strAcctNum);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

		  eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO, PROC_NO_TYPE, true, NULL);
		  SetMessageStatusBar( NULL_STRING );
	  }
      else if( selectedStr == cstrRESPAcctTermination) 
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPAcctTermInfo"));

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrRESPTerm;
         cstrRESPTerm.LoadString(TXT_RESP_TERMINATION_ENTRIES);
         setParameter (I_("BrowserTitle"), DString(cstrRESPTerm) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_ACCOUNT_TERMINATION, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }  
      else if( selectedStr == cstrRESPZeroGrant)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPZeroRpymt")); //DesktopWeb conversion

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrRESPZrPay;
         cstrRESPZrPay.LoadString(TXT_RESP_ZERO_GRANT_PAYMNT);
         setParameter (I_("BrowserTitle"), DString(cstrRESPZrPay) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_ZERO_GRANT_REPAYMENT, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrRESPInterfaceFile)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPInterfaceFile"));
         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrIntFile;
         cstrIntFile.LoadString(TXT_INRFACE_FILE);
         setParameter (I_("BrowserTitle"), DString(cstrIntFile) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_INTERFACE_FILE, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrTrailerFee)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"),I_("TrailerFeeSetup") );

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrFeeSet;
         cstrFeeSet.LoadString(TXT_TRAILER_FEE_SETUP);
         setParameter (I_("BrowserTitle"), DString(cstrFeeSet) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_TRAILER_FEE_SETUP, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
      else if(selectedStr == cstrInvestmentHistoryList)
      {
         setParameter( I_( "AccountNum" ), strAcctNum );

         eRtn = invokeCommand( getParent(), CMD_BPROC_INVESTMENT_HISTORY_LIST, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if(selectedStr == cstrAccountCommitment)
      {
         setParameter( I_( "AccountNum" ), strAcctNum );

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCOUNT_COMMITMENT, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if (selectedStr == cstrAccountForeignTaxReview)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"),I_("AcctGovFile") );

         setParameter (I_("UrlParams"), urlParamsIDI);

         CString cstrForeignTaxReview, cstrAcctnum;
         cstrForeignTaxReview.LoadString(ROW_DETAILS_ATTRIBUTES_FOREIGN_TAX_REVIEW);
         cstrAcctnum.LoadString(TXT_ACCOUNT_NUM);

         setParameter (I_("BrowserTitle"), DString(cstrForeignTaxReview) + DString(cstrAcctnum) + strAcctNum);

         eRtn = invokeCommand( getParent(), CMD_BPROC_FOREIGN_TAX_REVIEW, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );         
      }
      else if(selectedStr == cstrValueVariation)
      {
         getParent()->setParameter (I_("AccountNum"), strAcctNum);

         eRtn = invokeCommand( getParent(), CMD_BPROC_VALUE_VARIATION, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING ); 
      }
      else if (selectedStr == cstrTaxSlips)
      {
          DString urlParamsIDI, dstrDisplayName;
          E_COMMANDRETURN eRtn = CMD_OK;

          setParameter( I_( "AccountNum" ), strAcctNum );
          setParameter( I_( "from_screen" ), I_( "Account" ) );

          addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
          addIDITagValue (urlParamsIDI, I_("screen"),I_("TaxForms") );

          setParameter (I_("UrlParams"), urlParamsIDI);

          CString cstrAcctnum, cstrShareholderStr;
          cstrAcctnum.LoadString(IDS_TXT_ACCT_NUM);
          cstrShareholderStr.LoadString(IDS_TXT_SHR_NUM);
          dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), 
                                                                                                          strAcctNum, 
                                                                                                          dstrDisplayName);

          setParameter (I_("BrowserTitle"), DString(cstrTaxSlips) + I_(": ") +
                                            GetCaptionShareNumTxt() + I_(" ") + strShrNum + I_("; ") + 
                                            GetCaptionAcctNumTxt() + I_(" ") + strAcctNum + I_("; ") + 
                                            dstrDisplayName);

          eRtn = invokeCommand(getParent(), CMD_BPROC_TAX_SLIPS, PROC_NO_TYPE, bModal, NULL);
          SetMessageStatusBar(NULL_STRING);   
      }
	  else if( selectedStr == cstrRESPGrantInfo)
	  {
		  DString urlParamsIDI;
		  E_COMMANDRETURN eRtn = CMD_OK;

		  DString entityId, last_name, first_name, dstrEntityName;
		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo")); //DesktopWeb conversion

		  MFAccount *pMFAccount;
		  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

		  if( dstcWorkSession->getMFAccount( getDataGroupId(), strAcctNum, pMFAccount ) <= WARNING && pMFAccount)
		  {
			  AccountEntityXref *pAccountEntityXref = NULL;
			  if (dstcWorkSession->getAccountEntityXref (getDataGroupId(), pAccountEntityXref) <= WARNING && pAccountEntityXref)
			  {
				  ENTITIES_VECTOR respBeneficiaryEntities;
				  pAccountEntityXref->getRESPBeneficiaryEntities (respBeneficiaryEntities, strAcctNum, getDataGroupId());

				  for (ENTITIES_VECTOR::size_type i = 0; i < respBeneficiaryEntities.size(); ++i)
				  {
					  entityId = respBeneficiaryEntities [i];
					  Entity *pEntity = NULL;
					  if  (dstcWorkSession->getEntity (getDataGroupId(), entityId, pEntity) <= WARNING && pEntity)
					  {
						  pEntity->getField( ifds::EntityId, entityId, getDataGroupId(), false );
						  if (!entityId.empty())
						  {
							  addIDITagValue (urlParamsIDI, I_("RESPBenefID"), entityId);
							  pEntity->getField( ifds::LastName, last_name, getDataGroupId(), false );
							  pEntity->getField( ifds::FirstName, first_name, getDataGroupId(), false );
							  dstrEntityName = last_name.strip() + I_( ";" ) + first_name.strip();
							  break;
						  }
					  }
				  }
			  }
		  }

		  CString cstrRESPGrantInfo;
		  cstrRESPGrantInfo.LoadString(TXT_GRNT_INFO_SCREEN);
		  DString screenTitle (DString(cstrRESPGrantInfo) + strAcctNum + I_(" ") + dstrEntityName);

		  setParameter( I_("AccountNum"), strAcctNum );
		  setParameter (I_("UrlParams"), urlParamsIDI);
		  setParameter (I_("BrowserTitle"), screenTitle);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

		  eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_GRANTS, PROC_NO_TYPE, true, NULL);
		  SetMessageStatusBar( NULL_STRING );
	  }
	  else if( selectedStr == cstrRESPGrantInfo2)
	  {
		  DString urlParamsIDI;
		  E_COMMANDRETURN eRtn = CMD_OK;
		  
		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo2")); //DesktopWeb conversion
		  addIDITagValue (urlParamsIDI, I_("RESPBenefID"), I_(" "));

		  CString cstrRESPGrantInfo;
		  cstrRESPGrantInfo.LoadString(TXT_GRNT_INFO_SCREEN);
		  DString screenTitle (DString(cstrRESPGrantInfo) + strAcctNum);

		  setParameter( I_("AccountNum"), strAcctNum );
		  setParameter (I_("UrlParams"), urlParamsIDI);
		  setParameter (I_("BrowserTitle"), screenTitle);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

		  eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_GRANTS2, PROC_NO_TYPE, true, NULL);
		  SetMessageStatusBar( NULL_STRING );
      }
	  else if( selectedStr == cstrRESPNotionalActivity)
      {
         DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

         CString cstrRESPNotlActivity;
         cstrRESPNotlActivity.LoadString(TXT_RESP_NOTIONAL_ACTIVITY);

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPNotionalActivity")); //DesktopWeb conversion

		 setParameter( I_("AccountNum" ), strAcctNum );
         setParameter (I_("UrlParams"), urlParamsIDI);
         setParameter (I_("BrowserTitle"), DString(cstrRESPNotlActivity) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_NOTIONAL_ACTIVITY, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );
      }
	  else if( selectedStr == cstrRegExtrAcct)
	  {
		 DString urlParamsIDI;
         E_COMMANDRETURN eRtn = CMD_OK;

		 CString cstrRegAcctInfoRev;
		 cstrRegAcctInfoRev.LoadString(TXT_REG_ACCT_INFO_REV_TITLE);

		 addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		 addIDITagValue (urlParamsIDI, I_("screen"), I_("RegAcctInfoRev"));

		 setParameter( I_("AccountNum" ), strAcctNum );
         setParameter (I_("UrlParams"), urlParamsIDI);
         setParameter (I_("BrowserTitle"), DString(cstrRegAcctInfoRev));
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_REG_ACCT_INFO_REV, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar( NULL_STRING );

	  }
	  else if( selectedStr == rdspAcctInfoStr )
      {
         SetMessageStatusBar (TXT_LOAD_RDSP_INFO);
         //if (getParent()->hasReadPermission( UAF::RDSP_ACCOUNT_INFORMATION ))
         //{
            DString urlParamsIDI;
            E_COMMANDRETURN eRtn = CMD_OK;

            setParameter( I_( "AccountNum" ), strAcctNum );
            setParameter( I_( "from_screen" ), I_( "Account" ) );

            addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
            addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPAccountInfo"));

            setParameter (I_("UrlParams"), urlParamsIDI);

            CString cstrRDSP;
            cstrRDSP.LoadString(TXT_RDSP_ACCT_INFO);
            setParameter (I_("BrowserTitle"), DString(cstrRDSP) + strAcctNum);
            setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

            // invoke rdsp account info browser screen
            eRtn = invokeCommand (getParent(), CMD_BPROC_RDSP_ACCOUNT_INFO, PROC_NO_TYPE, true, NULL);		 
         //}
	  }
	  else if( selectedStr == rdspNotionalActivityStr )
      {
         SetMessageStatusBar (TXT_LOAD_RDSP_NOTIONAL_ACTIVITY);
         //if (getParent()->hasReadPermission( UAF::RDSP_NOTIONAL_ACTIVITY ))
         //{
            DString urlParamsIDI;
            E_COMMANDRETURN eRtn = CMD_OK;

            setParameter( I_( "AccountNum" ), strAcctNum );
			setParameter( I_( "TransNum" ), I_( " " ) );
            setParameter( I_( "from_screen" ), I_( "Account" ) );

            addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
			addIDITagValue (urlParamsIDI, I_("TransNum"), I_(" "));
            addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPNotionalActivity"));

            setParameter (I_("UrlParams"), urlParamsIDI);

            CString cstrRDSP;
            cstrRDSP.LoadString(TXT_RDSP_NOTIONAL_ACTIVITY);
            setParameter (I_("BrowserTitle"), DString(cstrRDSP) + strAcctNum);
            setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

            // invoke rdsp notional activity browser screen
            eRtn = invokeCommand (getParent(), CMD_BPROC_RDSP_NOTIONAL_ACTIVITY, PROC_NO_TYPE, true, NULL);	
         //}
	  }	
	  else if( selectedStr == rdspNotionalBalStr )
      {
         SetMessageStatusBar (TXT_LOAD_RDSP_NOTIONAL_BAL);
         //if (getParent()->hasReadPermission( UAF::RDSP_NOTIONAL_BALANCE ))
         //{
            DString urlParamsIDI;
            E_COMMANDRETURN eRtn = CMD_OK;

            setParameter( I_( "AccountNum" ), strAcctNum );
            setParameter( I_( "from_screen" ), I_( "Account" ) );

            addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
            addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPNotionalBalance"));

            setParameter (I_("UrlParams"), urlParamsIDI);

            CString cstrRDSP;
            cstrRDSP.LoadString(TXT_RDSP_NOTIONAL_BAL);
            setParameter (I_("BrowserTitle"), DString(cstrRDSP) + strAcctNum);
            setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

            // invoke rdsp notional balance browser screen
            eRtn = invokeCommand (getParent(), CMD_BPROC_RDSP_NOTIONAL_BALANCE, PROC_NO_TYPE, true, NULL);		 
         //}
	  }
	  else if( selectedStr == rdspInterfaceTransStr )
	  {
		  SetMessageStatusBar (TXT_LOAD_RDSP_INTERFACE_TRANSACTIONS);
		  //if (getParent()->hasReadPermission( UAF::RDSP_INTERFACE_TRANSACTIONS ))
		  //{
		  DString urlParamsIDI;
		  E_COMMANDRETURN eRtn = CMD_OK;

		  setParameter( I_( "AccountNum" ), strAcctNum );
		  setParameter( I_( "from_screen" ), I_( "Account" ) );

		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPInterfaceTransactions"));

		  setParameter (I_("UrlParams"), urlParamsIDI);

		  CString cstrRDSP;
		  cstrRDSP.LoadString(TXT_RDSP_INTERFACE_TRANSACTIONS);
		  setParameter (I_("BrowserTitle"), DString(cstrRDSP) + strAcctNum);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

		  // invoke rdsp notional balance browser screen
		  eRtn = invokeCommand (getParent(), CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS, PROC_NO_TYPE, true, NULL);		 
		  //}
	  }
	  else
		  return;

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

//******************************************************************************
void BaseAccountDetailsDlg::OnDblclkLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRdblclkLvHistoryTrades" ) );

   CWaitCursor wait;
   int accountIndex = m_lvAccounts.GetNextItem( -1, LVNI_SELECTED );
   if( accountIndex == -1 )// There is no account selected
      return;

   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString shrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   int transIndex = m_lvTransactions.GetNextItem( -1, LVNI_SELECTED );
   if( transIndex != -1 )
   {
      setParameter( ACCOUNT_NUM, strAcctNum );
      setParameter( SHAREHOLDER_NUM, shrNum );
      DString transId;
      int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
      if( entityIndex == -1 )// There is no entity selected
         return;
      DString *key1 = ( DString* ) m_lvEntities.GetItemData( entityIndex );
      getParent()->setCurrentListItem( this, IFASTBP_PROC::ENTITY_LIST, *key1 );
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, transId );
      setParameter( ENTITY_ID_PARAM, transId );

      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
      int iCheck = pRadioButton->GetCheck( );
      if( iCheck == 1 )
      {
         setParameter( PENDING, NO );
         DString* key = (DString*)m_lvTransactions.GetItemData( transIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::TRANSACTIONS_LIST, *key );
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::TransId, transId );
         transId.stripLeading( '0' );
         setParameter( TRANS_ID_FIELD, transId );

         int state = m_ckbAllFunds.GetCheck();
         DString strAllFundMode;
         if( state == 1 )
            strAllFundMode = YES ;
         else
            strAllFundMode = NO ;

         setParameter( ALL_FUND_MODE, strAllFundMode );

         int fundIndex = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
         key = (DString*)m_lvFunds.GetItemData( fundIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key );
         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, transId );
         transId.strip();
         setParameter( FUND_CODE, transId );

         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxClassCode, transId );
         transId.strip();
         setParameter( CLASS_CODE, transId );
         SetMessageStatusBar( TXT_LOAD_TRANSACTION_HISTORY );
      }
      else
      {
         setParameter( PENDING, YES );
         transIndex = m_lvTransactions.GetNextItem( -1, LVNI_SELECTED );
         DString* key = (DString*)m_lvTransactions.GetItemData( transIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::PENDING_TRADES_LIST, *key );
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::TradeDate, transId );
         transId.strip();
         setParameter( TRADE_DATE_FIELD, transId );
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::TransType, transId );
         transId.strip();
         setParameter( TRANS_TYPE_FIELD, transId );
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::TransNum, transId );
         transId.stripLeading( '0' );
         setParameter( TRANS_NUMBER_FIELD, transId );
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxFundCode, transId );
         transId.strip();
         setParameter( FUND_CODE, transId );
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxClassCode, transId );
         transId.strip();
         setParameter( CLASS_CODE, transId );
         SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );

      }

      try
      {
         bool bModal = false;   // Default to modeless
         E_COMMANDRETURN eRtn = CMD_OK;
         eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, bModal, NULL );
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
   }
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnDblclkLbOptions() 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnDblclkLbOptions" ) );

   CWaitCursor wait;
   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      //AfxMessageBox( I_( "Please select an account" ) );
      return;
   }

   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString strShrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   CListBox *pAttributesListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_OPTIONS ) );
   int itemSelected = pAttributesListBox->GetCurSel();
   if( itemSelected == LB_ERR )
      return;
   CString selectedStr, systematicsStr, bankInstr, allocationsStr, swpStr, systTransfStr, systSavingPlan, cstrAcctCutOffTime,
           acctSplitComm, cstrAMS, cstrFamily, cstrProtContract, strBenef, cstrAcctCategory, cstrAcctSettleLoc, cstrFundSponsorAgreement, cstrFundBroker, cstrFundLimitation,
           cstrAcctDocList, cstrAccountStaticDataVerify, cashSweepInstr, maturityInstr, cstrAcctAssociate, accountIdentifierStr;

   pAttributesListBox->GetText( itemSelected, selectedStr );
   accountIdentifierStr.LoadString( ID_STR_ACCOUNT_IDENTIFIER );
   systematicsStr.LoadString( ROW_DETAILS_OPTIONS_PAC ); 
   systSavingPlan.LoadString( ROW_DETAILS_OPTIONS_SAVING_PLAN );  
   swpStr.LoadString( ROW_DETAILS_OPTIONS_SWP );   
   bankInstr.LoadString( ROW_DETAILS_OPTIONS_BANKING );  
   allocationsStr.LoadString( ROW_DETAILS_OPTIONS_ALLOCATIONS );
   systTransfStr.LoadString( ROW_DETAILS_OPTIONS_SYSTEMATIC_TRANSFER );
   acctSplitComm.LoadString ( ROW_DETAILS_OPTIONS_COMMISSIONABLE_REPS );
   cstrAMS.LoadString( ROW_DETAILS_OPTIONS_AMS );
   cstrFamily.LoadString( ROW_DETAILS_OPTIONS_SHR_FAMILY  );
   cstrProtContract.LoadString ( ROW_DETAILS_OPTIONS_PROT_CONTRACTS );
   strBenef.LoadString( ROW_DETAILS_OPTIONS_BENEF );
   cstrAcctCategory.LoadString ( ROW_DETAILS_OPTIONS_ACCT_CATEGORY );
   cstrAcctSettleLoc.LoadString( TXT_SETTLEMENT_LOCATION );
   cstrFundSponsorAgreement.LoadString( ROW_DETAILS_OPTIONS_SHR_FUND_SPONSOR_AGREEMENT );
   cstrFundBroker.LoadString( ROW_DETAILS_OPTIONS_SHR_FUND_BROKER );
   cstrAcctCutOffTime.LoadString( TXT_ACCT_CUT_OFF_TIME );
   cstrFundLimitation.LoadString( TXT_FUND_CLASS_LIMITATION );
   cstrAcctDocList.LoadString( TXT_ACCT_DOC_LIST );
   cstrAccountStaticDataVerify.LoadString( ROW_TXT_ACCT_STATIC_DATA_VERIFY);
   cstrAcctAssociate.LoadString( ROW_DETAILS_OPTIONS_FEE_MODEL_ASSOCIATION );

   CString cstrSettlementRule;
   cstrSettlementRule.LoadString ( ROW_DETAILS_SETTLEMENT_RULE );

   CString cstrInvestorAuthorization;
   cstrInvestorAuthorization.LoadString ( ROW_DETAILS_INVESTOR_AUTHORIZATION );

   CString cstrAcctGuaranteeGuardOption;
   cstrAcctGuaranteeGuardOption.LoadString ( ROW_DETAILS_OPTIONS_ACCT_GUARNT_GUARD_OPTN );

   CString cstrGovtFilingAmendment;
   cstrGovtFilingAmendment.LoadString ( ROW_DETAILS_OPTIONS_RESP_GOVT_FILING_AMENDMENT );

   CString cstrInvestmentHistoryList;
   cstrInvestmentHistoryList.LoadString ( ROW_DETAILS_ATTRIBUTES_INVESTMENT_HISTORY );

   cashSweepInstr.LoadString( ROW_DETAILS_OPTIONS_CASHSWEEP );  
   maturityInstr.LoadString( ROW_DETAILS_OPTIONS_MATURITY ); 
   
   CString cstrAcctOwnershipAlloc;
   cstrAcctOwnershipAlloc.LoadString(ROW_DETAILS_OPTION_ACCT_OWNERSHIP_ALLOC);

   CString cstrAccountRegulatoryDetails;
   cstrAccountRegulatoryDetails.LoadString (ROW_DETAILS_ACCOUNT_REGULATORY_DETAILS);
   
   CString cstrEntityRegulatoryDetails;
   cstrEntityRegulatoryDetails.LoadString (TXT_ENT_REG_DETL);

   CString cstrAccountGroup;
   cstrAccountGroup.LoadString (TXT_ACCOUNT_GROUP_TITLE);

   CString cstrPWEnrollment;
   cstrPWEnrollment.LoadString (TXT_PRIVATE_WEALTH_INFO_TITLE);

   CString cstrAccountGroupingInfo;
   cstrAccountGroupingInfo.LoadString(TXT_ACCOUNT_GROUPING_INFO_TITLE);
   
   CString cstrRegPlanTransfer;
   cstrRegPlanTransfer.LoadString( TXT_REGISTERED_PLAN_TRANSFER_TITLE );

   CString cstrAcctRoundingRule;
   cstrAcctRoundingRule.LoadString( TXT_ACCT_ROUNDING_RULE );

   CString cstrAcctDelReview;
   cstrAcctDelReview.LoadString( TXT_ACCT_DEL_REVIEW );

   bool bModal = false;   // Default to modeless
   E_COMMANDRETURN eRtn = CMD_OK;

   try
   {
      if( selectedStr == systematicsStr || selectedStr == swpStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         if( selectedStr == systematicsStr )
            setParameter( I_("TransType"), I_("P"));
         else
            setParameter( I_("TransType"), I_("S")); 
         SetMessageStatusBar( TXT_LOAD_SYSTEMATIC_TRANSFER );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SYSTEMATIC, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == bankInstr )
      {
         SetMessageStatusBar (TXT_LOAD_BANKING);

         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum);
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
         DString dstrDefaultBankingLevel;
         if(dstWorkSession)
            dstWorkSession->getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel, getParent()->getDataGroupId(), false);
         dstrDefaultBankingLevel = dstrDefaultBankingLevel == BANKENTITY::ACCOUNT ? BANKTYPE::ACCOUNT :BANKTYPE::SHAREHOLDER;
         setParameter (MFCAN_IP_PARAM::BANK_TYPE, dstrDefaultBankingLevel);
         eRtn = invokeCommand (getParent(), CMD_BPROC_BANK_INSTRUCTIONS, 
            PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
	  else if (selectedStr == cashSweepInstr)
	  {
         setParameter( CALLER, ACCTCOA );
         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum);
         setParameter (INSTR_TYPE, CASH_SWEEP_INSTR);
         setParameter (MFCAN_IP_PARAM::RESET, I_("Y"));		

         eRtn = invokeCommand (getParent(), CMD_BPROC_MATSWP_INSTRUCTIONS, 
         PROC_NO_TYPE, bModal, NULL);

         SetMessageStatusBar (NULL_STRING);
	  }
	  else if (selectedStr == maturityInstr)
	  {
        setParameter( CALLER, ACCTCOA );
        setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum);
        setParameter (INSTR_TYPE, MATURITY_INSTR);

        eRtn = invokeCommand (getParent(), CMD_BPROC_MATSWP_INSTRUCTIONS, 
                              PROC_NO_TYPE, bModal, NULL);
	  }
      else if( selectedStr == allocationsStr )
      {
         setParameter( ALLOCATIONSPROC::ACCOUNT_NUM, strAcctNum );
         setParameter( ALLOCATIONSPROC::ALLOCATION_TYPE, 
                       ALLOCATIONSPROC::SHAREHOLDER_DEFAULT );
         setParameter(MFCAN_IP_PARAM::CALLER, I_("Default"));
         SetMessageStatusBar( TXT_LOAD_DEFAULT_ALLOCATION );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ALLOCATIONS, PROC_NO_TYPE, 
                               bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == systTransfStr )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );   
         setParameter( I_("TransType"), I_("AT")); 

         SetMessageStatusBar( TXT_LOAD_SYSTEMATIC_TRANSFER );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SYSTEMATIC, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == systSavingPlan )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );   
         setParameter( I_("TransType"), I_("V")); 

         SetMessageStatusBar( TXT_LOAD_SAVING_PLAN );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SYSTEMATIC, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == acctSplitComm )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_COMMISSIONABLE_REPS );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCT_SPLITCOMM, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrAMS )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_AMS );
         eRtn = invokeCommand( getParent(), CMD_BPROC_AMSACCTLVL, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }

      else if( selectedStr == strBenef )
      {
         int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
         if( entityIndex == -1 )// There is no account selected
            return;
         DString *key = ( DString* ) m_lvEntities.GetItemData( entityIndex );

         setParameter( KEY, *key );
         setParameter( ACCOUNT_NUM, strAcctNum );

         SetMessageStatusBar( TXT_LOAD_ENTITY );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }

      else if( selectedStr == cstrFamily )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         setParameter( SHAREHOLDER_NUM, strShrNum );
         SetMessageStatusBar( TXT_LOAD_SHR_FAMILY );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SHR_FAMILY, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if ( selectedStr == cstrProtContract )
      {
         setParameter( ACC_CONTRACT::ACCOUNT_NUM, strAcctNum );         
         SetMessageStatusBar( TXT_LOAD_PROT_CONTRACT );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCOUNT_CONTRACT, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrAcctCategory )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_ACCT_CATEGORY );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCT_CATEGORY, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrAcctDocList )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_ACCT_DOC_LIST );
         eRtn = invokeCommand( getParent(), CMD_BPROC_REG_DOCUMENT_LIST, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrAcctSettleLoc )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_SETTLELOC_ACCTLVL );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrFundSponsorAgreement )
      {
         setParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     strAcctNum );
         setParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, strShrNum );
         SetMessageStatusBar( TXT_LOAD_SHR_FUND_SPONSOR_AGREEMENT );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrFundBroker )
      {
         setParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     strAcctNum );
         setParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, strShrNum );
         SetMessageStatusBar( TXT_LOAD_SHR_FUND_BROKER );
         eRtn = invokeCommand( getParent(), CMD_BPROC_SHR_FUND_BROKER, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrAcctCutOffTime )
      {
         setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum );
         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == cstrFundLimitation)
      {
         DString urlParamsIDI;

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
         addIDITagValue (urlParamsIDI, I_("screen"), I_("OvrdLimit") );

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrFundLmt;
         cstrFundLmt.LoadString(TXT_FUND_LIMITATION);
         setParameter (I_("BrowserTitle"), DString(cstrFundLmt) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_FUND_CLASS_LIMITATION, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if ( selectedStr == cstrSettlementRule )
      {
         SetMessageStatusBar( TXT_LOAD_ACCT_SETTLEMENT_RULE );
         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if ( selectedStr == cstrInvestorAuthorization )
      {
        SetMessageStatusBar( TXT_LOAD_INVESTOR_AUTHORIZATION );
        setParameter( I_( "AccountNum" ), strAcctNum );
        setParameter( I_( "from_screen" ), I_( "Account" ) );

        eRtn = invokeCommand( getParent(), 
                              CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION, 
                              PROC_NO_TYPE, 
                              bModal, 
                              NULL );

        SetMessageStatusBar( NULL_STRING );

      }
      else if (selectedStr == cstrAccountStaticDataVerify)
      {
         SetMessageStatusBar (TXT_LOAD_ACCOUNT_STATIC_DATA_VERIFY);

         DString urlParamsIDI;

         CString cstrStat;
         cstrStat.LoadString(TXT_VERIFY_STATIC_DATA);

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("AcctStDataVerify"));//Uttam
         addIDITagValue (urlParamsIDI, I_("from_screen"), I_("AccountDetailsDlg"));
         addIDITagValue (urlParamsIDI, I_("BrowserTitle"), cstrStat);

         setParameter (I_("UrlParams"), urlParamsIDI);

         setParameter (I_("BrowserTitle"), DString(cstrStat) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if(selectedStr ==  cstrAcctGuaranteeGuardOption)
      {
         SetMessageStatusBar (TXT_LOAD_ACCT_GUARNT_GUARD_OPTN);

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         eRtn = invokeCommand( getParent(), 
                               CMD_BPROC_ACCT_GUARNT_GUARD_OPTN, 
                               PROC_NO_TYPE, 
                               bModal, 
                               NULL );

         SetMessageStatusBar( NULL_STRING );
      }
      else if ( selectedStr == cstrGovtFilingAmendment)
      {
         DString urlParamsIDI,
            taxType;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter( I_( "from_screen" ), I_( "Account" ) );

         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, taxType, false );
         taxType.strip().upperCase();

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"),I_("GovtAmendment") );

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrGovFill;
         cstrGovFill.LoadString(TXT_GOV_FILING_AND_AMENDMENT);
         setParameter (I_("BrowserTitle"), DString(cstrGovFill) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_GOVT_FILING_AMENDMENT, PROC_NO_TYPE, true, NULL);
      }
      else if(selectedStr == cstrAcctOwnershipAlloc)
      {
         DString strHasAcctOwnerShipRecord;
         getParent()->getField( this, ACCDETLIT::HAS_ACCT_OWNERSHIP_RECORD, strHasAcctOwnerShipRecord, false );
         strHasAcctOwnerShipRecord.strip().upperCase();

         if(strHasAcctOwnerShipRecord == I_("Y"))
         {
            DString urlParamsIDI;

            SetMessageStatusBar( TXT_LOADING_ACCT_OWNERSHIP_ALLOC );
            setParameter( I_( "AccountNum" ), strAcctNum );

            addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
            addIDITagValue (urlParamsIDI, I_("screen"),I_("AcctTaxAlloc") );

            setParameter (I_("UrlParams"), urlParamsIDI);
            CString cstrActTaxAllocTitle, cstrAcctNumTxt;
            cstrAcctNumTxt.LoadString(TXT_ACCT_NUM_TXT);
            cstrActTaxAllocTitle.LoadString(TXT_ACCT_OWNERSHIP_ALLOC_TITLE);
            DString strBrowserTitle = DString(cstrActTaxAllocTitle) + I_(" ") + 
                                      DString(cstrAcctNumTxt) + strAcctNum;            
            setParameter (I_("BrowserTitle"), strBrowserTitle );
            setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

            eRtn = invokeCommand (getParent(), CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION, PROC_NO_TYPE, bModal, NULL);
            SetMessageStatusBar (NULL_STRING);
         }
      }
      else if(selectedStr == cstrAcctAssociate)
      {
         DString urlParamsIDI;

         SetMessageStatusBar( TXT_LOAD_FEE_MODEL_ASSOCIATION );
         setParameter( I_( "AccountNum" ), strAcctNum );

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("AcctAssociate") );
         addIDITagValue (urlParamsIDI, I_("from_screen"), I_("AccountDetailsDlg"));

         setParameter (I_("UrlParams"), urlParamsIDI);
         CString cstrActFeeModelAssociateTitle, cstrAcctNumTxt;
         cstrAcctNumTxt.LoadString(TXT_ACCT_NUM_TXT);
         cstrActFeeModelAssociateTitle.LoadString(TXT_FEE_MODEL_ASSOCIATION_TITLE);
         DString strBrowserTitle = DString(cstrActFeeModelAssociateTitle) + I_(" ") + 
            DString(cstrAcctNumTxt) + strAcctNum;
         setParameter (I_("BrowserTitle"), strBrowserTitle );
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         eRtn = invokeCommand (getParent(), CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if (selectedStr == accountIdentifierStr)
      {
         DString urlParamsIDI;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("AccountIdentifier"));

         setParameter (I_("UrlParams"), urlParamsIDI);

         DString dstrEntityName;

         CString cstrGuaranteeInfo,
            cstrInfoShr,
            cstrAccountNumLabel,
			cstrAccountHolderName;
         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
		 cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), strAcctNum,dstrEntityName);

		 accountIdentifierStr += ":";
         DString strBrowserTitle(accountIdentifierStr);
         strBrowserTitle += cstrAccountNumLabel;
         strBrowserTitle += strAcctNum;
         strBrowserTitle += I_(" ");
		 strBrowserTitle += cstrAccountHolderName;
         strBrowserTitle += dstrEntityName;

         setParameter( I_("BrowserTitle"), strBrowserTitle);

         E_COMMANDRETURN eRtn = invokeCommand (getParent(), CMD_BPROC_ACCT_IDENTIFIER, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
	  else if (selectedStr == cstrAccountRegulatoryDetails)
	  {
		  setParameter(I_("AccountNum"), strAcctNum);

		  eRtn = invokeCommand(getParent(), CMD_BPROC_ACCT_REGIS_MAINT, PROC_NO_TYPE, bModal, NULL);
		  SetMessageStatusBar( NULL_STRING ); 
	  }
      else if (selectedStr == cstrEntityRegulatoryDetails)
      {
         setParameter(I_("AccountNum"), strAcctNum);
         setParameter( CALLER, I_("COA") );

         eRtn = invokeCommand(getParent(), CMD_BPROC_ENT_REG_MAINT, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar(NULL_STRING); 
      }
      else if (selectedStr == cstrAccountGroup)
      {
         DString urlParamsIDI;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("AccountGroup"));

         setParameter (I_("UrlParams"), urlParamsIDI);

         DString dstrEntityName;

         CString cstrInfoShr,
            cstrAccountNumLabel,
            cstrAccountHolderName;
         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
         cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), strAcctNum,dstrEntityName);

         cstrAccountGroup += ":";
         DString strBrowserTitle(cstrAccountGroup);
         strBrowserTitle += cstrAccountNumLabel;
         strBrowserTitle += strAcctNum;
         strBrowserTitle += I_(" ");
         strBrowserTitle += cstrAccountHolderName;
         strBrowserTitle += dstrEntityName;

         setParameter( I_("BrowserTitle"), strBrowserTitle);

         E_COMMANDRETURN eRtn = invokeCommand (getParent(), CMD_BPROC_ACCOUNT_GROUP, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if (selectedStr == cstrPWEnrollment)
      {
         DString urlParamsIDI;

         setParameter( I_( "AccountNum" ), strAcctNum );
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("screen"), I_("PWInfo"));

         setParameter (I_("UrlParams"), urlParamsIDI);

         DString dstrEntityName;

         CString cstrInfoShr,
            cstrAccountNumLabel,
            cstrAccountHolderName;
         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
         cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), strAcctNum,dstrEntityName);

         cstrPWEnrollment += ":";
         DString strBrowserTitle(cstrPWEnrollment);
         strBrowserTitle += cstrAccountNumLabel;
         strBrowserTitle += strAcctNum;
         strBrowserTitle += I_(" ");
         strBrowserTitle += cstrAccountHolderName;
         strBrowserTitle += dstrEntityName;

         setParameter( I_("BrowserTitle"), strBrowserTitle);

         E_COMMANDRETURN eRtn = invokeCommand (getParent(), CMD_BPROC_PRIVATE_WEALTH_INFO, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if (selectedStr == cstrAccountGroupingInfo)
      {
         DString urlParamsIDI;

         setParameter(I_("AccountNum"), strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));

         addIDITagValue(urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue(urlParamsIDI, I_("screen"), I_("GroupingInformation"));

         setParameter (I_("UrlParams"), urlParamsIDI);

         DString dstrEntityName;
         CString cstrInfoShr, cstrAccountNumLabel, cstrAccountHolderName;

         cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
         cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), strAcctNum,dstrEntityName);

         cstrAccountGroupingInfo += ":";
         DString strBrowserTitle(cstrAccountGroupingInfo);
         strBrowserTitle += cstrAccountNumLabel;
         strBrowserTitle += strAcctNum;
         strBrowserTitle += I_(" ");
         strBrowserTitle += cstrAccountHolderName;
         strBrowserTitle += dstrEntityName;

         setParameter( I_("BrowserTitle"), strBrowserTitle);

         E_COMMANDRETURN eRtn = invokeCommand (getParent(), CMD_BPROC_ACCOUNT_GROUPING_INFO, PROC_NO_TYPE, true, NULL);
         SetMessageStatusBar (NULL_STRING);
      }
      else if (selectedStr == cstrRegPlanTransfer)
      {
         setParameter(I_("AccountNum"), strAcctNum);
         
         eRtn = invokeCommand(getParent(), CMD_BPROC_REG_PLAN_TRANSFER, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar( NULL_STRING ); 
      }
	  else if (selectedStr == cstrAcctRoundingRule)
      {
         setParameter(I_("AccountNum"), strAcctNum);
         
         eRtn = invokeCommand(getParent(), CMD_BPROC_ACCT_ROUNDING_RULE, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar( NULL_STRING ); 
      }
	  else if (selectedStr == cstrAcctDelReview)
	  {         
		  DString urlParamsIDI;
		  CString cstrBrowserTitle;
		  
		  cstrBrowserTitle.LoadString (TXT_ACCT_DELETION_REVIEW);	   
		  cstrBrowserTitle += I_(" ");

		  addIDITagValue (urlParamsIDI, I_("screen"), I_("AcctDelReview"));
		  addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);		  		  
		  
		  DString strBrowserTitle(cstrBrowserTitle);		  	  
		  strBrowserTitle += strAcctNum;

		  setParameter (I_("UrlParams"), urlParamsIDI);
		  setParameter (I_("AccountNum"), strAcctNum);		  
		  setParameter (I_("BrowserTitle"), strBrowserTitle);
		  setParameter (I_("from_screen"), I_("AccountDetailsDlg"));
		  
		  eRtn = invokeCommand(getParent(), CMD_BPROC_ACCT_DELETION_REVIEW, PROC_NO_TYPE, bModal, NULL);
		  SetMessageStatusBar( NULL_STRING ); 
	  }
	 
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

//******************************************************************************
void BaseAccountDetailsDlg::OnRbTransHistory() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbTransHistory" ) );
   // TODO: Add your control notification handler code here
   CWaitCursor wait;

   m_ckbAllFunds.EnableWindow( true );
   RbTransHistory();

}

//******************************************************************************
void BaseAccountDetailsDlg::OnRbPendingTrades() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbPendingTrades " ) );
   // TODO: Add your control notification handler code here
   CWaitCursor wait;

   m_ckbAllFunds.EnableWindow( false );
   RbPendingTrades();

}

//******************************************************************************
void BaseAccountDetailsDlg::OnDblclkLbCautions() 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnDblclkLbCautions" ) );

   CWaitCursor wait;
   DString strMarket = DSTCommonFunctions::getMarket();

   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString strShrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   CListBox *pCautionsListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_CAUTIONS ) );
   int itemSelected = pCautionsListBox->GetCurSel();
   if( itemSelected == LB_ERR )
      return;
   CString selectedStr, certificatesStr, pendingTrade, remarksStr, stopAMSRebalancing;
   CString stopPurchaseStr, stopRedeemStr, stopTransOutStr, stopTransInStr;
   CString unsettledTranStr, stopForeignContent, stopRedemptionSettlement, holdDivPymtStr;
   CString dot, addendum, dotAndAddendum;

   pCautionsListBox->GetText( itemSelected, selectedStr );
   certificatesStr.LoadString( ROW_DETAILS_CAUTIONS_CERTIFICATES_ISSUED ); 
   pendingTrade.LoadString( ROW_DETAILS_CAUTIONS_PENDING_TRADE ); 
   remarksStr.LoadString( ROW_DETAILS_CAUTIONS_REMARKS );   
   stopPurchaseStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_PURCHASE ); 
   stopRedeemStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_REDEEM );  
   stopTransOutStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_OUT );   
   stopTransInStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_IN );  
   unsettledTranStr.LoadString( ROW_DETAILS_CAUTIONS_UNSETTLED_TRANSACTION ); 
   stopAMSRebalancing.LoadString( IDS_STP_AMSREBALANCING );
   stopAMSRebalancing.TrimLeft();
   stopForeignContent.LoadString( IDS_STP_FRREB );
   stopForeignContent.TrimLeft();
   stopRedemptionSettlement.LoadString( IDS_STOP_REDEEMPTION_SETTLE );
   stopRedemptionSettlement.TrimLeft();
   holdDivPymtStr.LoadString( ROW_DETAILS_CAUTIONS_HOLD_DIV_PAYMENT );
   dotAndAddendum.LoadString (ROW_DETAILS_CAUTIONS_DOTADND);
   dot.LoadString (ROW_DETAILS_CAUTIONS_DOT);
   addendum.LoadString (ROW_DETAILS_CAUTIONS_ADND);

   DString strDTATypeSubstList;
   const BFProperties * pBFProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::DTAType );
   pBFProp->getAllSubstituteValues(strDTATypeSubstList);

   DString strStaleChqStageSubstList;
   const BFProperties * pBFPropStaleChqStage = 
      getParent()->getFieldAttributes(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::StaleChqStage );

   pBFPropStaleChqStage->getAllSubstituteValues(strStaleChqStageSubstList);

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn = CMD_OK;

      if( selectedStr == certificatesStr )
      {
         setParameter( IN_ACCT_NUM_FIELD, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_CERTIFICATES );
         eRtn = invokeCommand( getParent(), CMD_BPROC_CERTIFICATE, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == pendingTrade )
      {
         int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
         if( entityIndex == -1 )// There is no account selected
            return;
         DString transId;
         DString *key1 = ( DString* ) m_lvEntities.GetItemData( entityIndex );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::ENTITY_LIST, *key1 );
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, transId );
         setParameter( ENTITY_ID_PARAM, transId );

         setParameter( ACCOUNT_NUM, strAcctNum );
         setParameter( PENDING, YES );
         SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );
         eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if( selectedStr == remarksStr )
      {
         openRemarkScreen();
      }
      else if( selectedStr == unsettledTranStr )
      {
         SetMessageStatusBar( TXT_LOAD_SETTLEMENT );
         setParameter( ACCOUNT_NUM, strAcctNum );
         setParameter( FROMSCR, DETAILS );

         bool bModal = false;// Default to modeless
         eRtn = invokeCommand( getParent(), CMD_BPROC_SETTLEMENT, PROC_NO_TYPE, 
                               bModal, NULL );


         SetMessageStatusBar( NULL_STRING );
         return;
         /*

           int transIndex = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
           if ( transIndex == -1 )
           {
              setParameter( FUND_CODE, NULL_STRING );
              setParameter( CLASS_CODE, NULL_STRING );
              setParameter( ACCOUNT_NUM, strAcctNum );
              SetMessageStatusBar( TXT_LOAD_TRANSACTION_HISTORY );
              eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, bModal, NULL );
  
          SetMessageStatusBar( TXT_LOAD_SETTLEMENT );
          setParameter( ACCOUNT_NUM, strAcctNum );
  
          bool bModal = false;// Default to modeless
          eRtn = invokeCommand( getParent(), CMD_BPROC_SETTLEMENT, PROC_NO_TYPE, 
                                                                 bModal, NULL );
  
  
              SetMessageStatusBar( NULL_STRING );
              return;
           }
           DString* key = (DString*)m_lvFunds.GetItemData( transIndex );
           getParent()->setCurrentListItem( this, ACCDETLIT::FUNDS_LIST, *key );
           DString str;
  
           getParent()->getField( this, ACCDETLIT::FUNDS_LIST, ifds::rxFundCode, str );
           str.strip();
           setParameter( FUND_CODE, str );
  
           getParent()->getField( this, ACCDETLIT::FUNDS_LIST, ifds::rxClassCode, str );
           str.strip();
           setParameter( CLASS_CODE, str );
  
           int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
           if ( entityIndex == -1 )// There is no account selected
              return;
           DString transId;
           DString *key1 = ( DString* ) m_lvEntities.GetItemData( entityIndex );
           getParent()->setCurrentListItem( this, ACCDETLIT::ENTITY_LIST, *key1 );
           getParent()->getField( this, ACCDETLIT::ENTITY_LIST, ifds::EntityId, transId );
           setParameter( ENTITY_ID_PARAM, transId );
  
           setParameter( ACCOUNT_NUM, strAcctNum );
           setParameter( PENDING, NO );
           SetMessageStatusBar( TXT_LOAD_TRANSACTION_HISTORY );
           eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, bModal, NULL );
           SetMessageStatusBar( NULL_STRING );
       */
      }
      else if( ( selectedStr == stopPurchaseStr ) || ( selectedStr == stopRedeemStr ) || 
               ( selectedStr == stopTransOutStr ) || ( selectedStr == stopTransInStr ) ||
               ( selectedStr == stopAMSRebalancing ) || ( selectedStr == stopForeignContent ) ||
               ( selectedStr == stopRedemptionSettlement ) || ( selectedStr == holdDivPymtStr ) )
      {
         OnBtnAddCOA();
      }
      else if( strDTATypeSubstList.find( selectedStr ) != DString::npos )
      {
         setParameter( ACCOUNT_NUM, strAcctNum );
         SetMessageStatusBar( TXT_LOAD_DTA );
         eRtn = invokeCommand( getParent(), CMD_BPROC_DIRECT_TRADING, PROC_NO_TYPE, bModal, NULL );
         SetMessageStatusBar( NULL_STRING );
      }
      else if ( selectedStr == dotAndAddendum ||
                selectedStr == dot ||
                selectedStr == addendum)
      {
         DString urlParamsIDI;

         getParent()->getField (this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, strAcctNum);
         setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum);

         addIDITagValue (urlParamsIDI, I_("AccountNum"), strAcctNum);
         addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
		 addIDITagValue (urlParamsIDI, I_("screen"), I_("DOTAndAddendum"));

		 CString cstrDOT;
		 cstrDOT.LoadString(TXT_DOT_AND_ADDENDUM);
         setParameter (I_("BrowserTitle"), DString(cstrDOT) + strAcctNum);
         setParameter (I_("from_screen"), I_("AccountDetailsDlg"));
         setParameter (I_("UrlParams"), urlParamsIDI);

         eRtn = invokeCommand (getParent(), CMD_BPROC_DOT_AND_ADDENDUM, PROC_NO_TYPE, bModal, NULL);
         SetMessageStatusBar (NULL_STRING);
      }

	  //P0178584_FN01_NewPopUpMSG
	  int nPos = selectedStr.Find('-');
	  DString strSelectedStatus(NULL_STRING);

	  strSelectedStatus = selectedStr.Left(nPos).TrimRight();

	  if(strSelectedStatus != NULL_STRING)
	  {
		  // return mail
		  if(strSelectedStatus == RET_MAIL)
		  {
			  setParameter( ACCOUNT_NUM, strAcctNum );
			  setParameter( SHAREHOLDER_NUM,strShrNum);
			  setParameter( ADDRLIT::RETMAIL_TAB, I_("Y"));
			  SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );
			  eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_NO_TYPE, bModal, NULL );
			  SetMessageStatusBar( NULL_STRING );
		  }
		  // stale cheque 
		  else if (strSelectedStatus == STLD_CHQ)
		  {
			  setParameter( ACCOUNT_NUM, strAcctNum );
			  setParameter( CHQ_STATUS_VALUE, I_( "STLD" ) );
			  SetMessageStatusBar( TXT_LOAD_CHEQUE_INFORMATION );
			  eRtn = invokeCommand( getParent(), CMD_BPROC_CHEQUE, PROC_NO_TYPE, bModal, NULL );
			  SetMessageStatusBar( NULL_STRING );
		  }
		  //Remitted cheque
		  else if (strSelectedStatus == RMTD_CHQ)
		  {
			  setParameter( ACCOUNT_NUM, strAcctNum );
			  setParameter( CHQ_STATUS_VALUE, I_( "RMTD" ) );
			  SetMessageStatusBar( TXT_LOAD_CHEQUE_INFORMATION );
			  eRtn = invokeCommand( getParent(), CMD_BPROC_CHEQUE, PROC_NO_TYPE, bModal, NULL );
			  SetMessageStatusBar( NULL_STRING );

		  }
	  }
	 // End - P0178584_FN01_NewPopUpMSG
     
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

//******************************************************************************
void BaseAccountDetailsDlg::OnDblclkLvEntities(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvEntitiesTrades" ) );

   int accountIndex = m_lvAccounts.GetNextItem( -1, LVNI_SELECTED );
   if( accountIndex == -1 )// There is no account selected
      return;
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );

   int entityIndex = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
   if( entityIndex == -1 )// There is no account selected
      return;

   //check security on the Account Entity
   DString security;

   getParent()->getField( this, ACCDETLIT::ENTITY_ATTR, security, false );
   security.strip();
   if( security != Y_STRING )
   {
      //the user doesn't have access to the entity screen
      return;
   }
   DString *key = ( DString* ) m_lvEntities.GetItemData( entityIndex );

   setParameter( KEY, *key );
   setParameter( ACCOUNT_NUM, strAcctNum );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn = CMD_OK;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY()/*GETHIGHESTSEVERITY()*/ );
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
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSelchangeCmbAddrSel() 
{
   // TODO: Add your control notification handler code here
   fillShrAddressList();

}

//******************************************************************************

void BaseAccountDetailsDlg::OnBtnAdminDates() 
{
   // TODO: Add your control notification handler code here
   BtnAdminDates();

}

//******************************************************************************

bool BaseAccountDetailsDlg::doModelessSetFocus( GenericInterface * rpGICaller )
{
   BaseDlg::doModelessSetFocus( rpGICaller );

/*   DString flg, flg1,dstrRefreshPendingTrades;
   getParameter( I_( "CloseEntity" ), flg );
   getParameter( I_( "CloseChild" ), flg1 );

   if( flg == YES )
   {
      int sel = m_lvAccounts.GetNextSelection( -1 );
      m_lvAccounts.PopulateList();      
      if( sel >= m_lvAccounts.GetItemCount() )
         sel--;
      m_lvAccounts.SetSelection( sel );
   }
   else if( flg1 == YES )
   {
      fillCautionsList();
      fillOptionsList();
      fillAttributesList();
   }
*/
   return(true);
}

//******************************************************************************

bool BaseAccountDetailsDlg::doRefresh ( GenericInterface * rpGICaller,
                                        const I_CHAR * szOriginalCommand)
{  
   DString closeChild;

//read the param before modelessSetFocus, 'cause the params are cleared
   getParameter( I_( "CloseChild" ), closeChild );

   getParent()->modelessSetFocus( this );
   
   DString dstrAlertMessageExists;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AlertMessageExists, dstrAlertMessageExists, false);
   GetDlgItem(IDC_BTN_ALERT_MESSAGES)->EnableWindow(dstrAlertMessageExists == YES);

   if (closeChild == YES)
   {
      int sel = m_lvAccounts.GetNextSelection( -1 );
      
      m_lvAccounts.PopulateList();      
      if( sel >= m_lvAccounts.GetItemCount() )
      {
         sel--;
      }
      m_lvAccounts.SetSelection( sel );
      fillCautionsList();
      fillOptionsList();
      fillAttributesList();
   }

   //modelessSetFocus( NULL );

   DString szCommand(szOriginalCommand);

   if (szCommand == I_("NewTradesAdded"))
   {
      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_PENDING_TRADES ) );
      if( pRadioButton && !pRadioButton->IsWindowEnabled() )
      {
         pRadioButton->EnableWindow();
         fillCautionsList();
      }
      else if( pRadioButton && (pRadioButton->GetCheck()) == 1 )
      {
         RbPendingTrades();
      }
      //new default bank might have been added
      fillOptionsList();
   }
   else if( szCommand == I_("FromSettlement") )
   {
      int sel = m_lvAccounts.GetNextSelection( -1 );

      m_lvAccounts.PopulateList();      
      if ( sel >= m_lvAccounts.GetItemCount() )
         sel--;
      m_lvAccounts.SetSelection( sel );
      fillFundList( );
      fillEntitiesList();
      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
      if ( pRadioButton && !pRadioButton->IsWindowEnabled() )
      {
         pRadioButton->EnableWindow();
         fillCautionsList();
      } else if ( pRadioButton && (pRadioButton->GetCheck()) == 1 )
      {
         RbTransHistory();
      }
      fillOptionsList();		
   }
   else if (szCommand == I_("FromdoSend"))
   {
      DString newAccKey, 
         key;
      int count = 0;
      getParent()->getField( this, ACCDETLIT::NEW_ACCOUNT_NUMBER, newAccKey );
      for( key = getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
         key != NULL_STRING && key != newAccKey;
         key = getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST ), count++ )
         ;//empty body
      if( count < m_lvAccounts.GetItemCount() )
      {
         m_lvAccounts.SetSelection( count );
      }
      else
      {
         m_lvAccounts.SetSelection( 0 );
      }

      fillFundList( );
      fillEntitiesList();
      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TRANS_HISTORY ) );
      if ( pRadioButton && !pRadioButton->IsWindowEnabled() )
      {
         pRadioButton->EnableWindow();
         fillCautionsList();
      } 
      else if ( pRadioButton && (pRadioButton->GetCheck()) == 1 )
      {
         RbTransHistory();
      }
      fillOptionsList();
   }
   else if (szCommand == I_("AfterCloneOnTradeEntry"))
   {
      int sel = m_lvAccounts.GetNextSelection (-1);
      fillAccountList ();
      if (sel >= 0)
      {
         m_lvAccounts.SetSelection (sel);
      }
   }
   else if (szCommand == I_("RefreshAccount"))
   {
      int sel = m_lvAccounts.GetNextSelection( -1 );
      
      m_lvAccounts.PopulateList();      
      if( sel >= m_lvAccounts.GetItemCount() )
      {
         sel--;
      }
      m_lvAccounts.SetSelection( sel );
      fillCautionsList();
      fillOptionsList();
      fillAttributesList();
   }

   return true;
}

//******************************************************************************

void BaseAccountDetailsDlg::PostNcDestroy()
{
   BaseMainDlg::PostNcDestroy();
   AfxGetMainWnd()->SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLbAttrib() 
{
   // TODO: Add your control notification handler code here
   SetfocusLbAttrib();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLbCautions() 
{
   // TODO: Add your control notification handler code here
   SetfocusLbCautions();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLbOptions() 
{
   // TODO: Add your control notification handler code here
   SetfocusLbOptions();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   SetfocusLvEntitiesIds( pNMHDR,  pResult);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLbAttrib() 
{
   // TODO: Add your control notification handler code here

   int idx = m_lbAttributes.GetCurSel( );
   if( idx != LB_ERR )
      m_lbAttributes.GetText( idx, lastFocusAttributes );
   SetMessageStatusBar( NULL_STRING );
}

//***********************************************F*******************************

void BaseAccountDetailsDlg::OnKillfocusLbCautions() 
{
   // TODO: Add your control notification handler code here

   int idx = m_lbCautions.GetCurSel( );
   if( idx != LB_ERR )
      m_lbCautions.GetText( idx, lastFocusCautions );
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLbOptions() 
{
   // TODO: Add your control notification handler code here

   int idx = m_lbOptions.GetCurSel( );
   if( idx != LB_ERR )
      m_lbOptions.GetText( idx, lastFocusOptions );
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvAccounts(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   SetfocusLvAccounts( pNMHDR,  pResult);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   SetfocusLvEntities( pNMHDR,  pResult) ;

}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   SetfocusLvFunds( pNMHDR,  pResult) ;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   SetfocusLvHistoryTrades( pNMHDR,  pResult);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   lastFocus = IDC_LV_KANA_ADDR;
   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );
   int idx = m_lvKanaAddr.GetNextItem( -1, LVNI_SELECTED );
   if( idx == -1 )
      m_lvKanaAddr.SetSelection( lastFocusKanaAddr );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSetfocusLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   lastFocus = IDC_LV_KANJI_ADDR;
   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   int idx = m_lvKanjiAddr.GetNextItem( -1, LVNI_SELECTED );
   if( idx == -1 )
      m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   int idx = m_lvEntities.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      lastFocusEntities = idx;
   }
   *pResult = 0;
}

//******************************************************************************
//P0178584_FN01_NewPopUpMSG
UINT BaseAccountDetailsDlg::getMailStageInfo(const DString& strValue)
{
   if (strValue == I_("S1"))
   {
      return IDS_STAGE_INITIAL_NOTIFICATION;
   }
   else if (strValue == I_("S2"))
   {
      return IDS_STAGE_RESEARCH;
   }
   else if(strValue == I_("S3"))
   {
      return IDS_STAGE_UNCLAIMED;
   }
   else if (strValue == I_("S4"))
   {
      return IDS_STAGE_BELOW_THRESHOLD;
   }
   else 
   {
      return -1;
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::fillChgMailInfoToCautionList(const DString& strValue, const DString &strType, CListBox*& pCautionsListBox, int &index)
{
   if (DSTCommonFunctions::codeInList( strValue, UNCLAIMED_STAGE_CODES_LIST) )
   {
      DString dstrStage(NULL_STRING);
      CString strStage(NULL_STRING);

      strStage.LoadString(getMailStageInfo(strValue));
      dstrStage = I_(" - ") + strStage;

      if (strType == RET_MAIL) //return mail
      {		
         dstrStage = RET_MAIL + dstrStage;
         pCautionsListBox->InsertString( index++, dstrStage.c_str() );
      }
      else if (strType == STLD_CHQ) //stale cheque
      {
         dstrStage = STLD_CHQ + dstrStage;
         pCautionsListBox->InsertString( index++, dstrStage.c_str() );
      }
      else if(strType == RMTD_CHQ) //remitted cheque
      {
         dstrStage = RMTD_CHQ + dstrStage;
         pCautionsListBox->InsertString( index++, dstrStage.c_str() );
      }
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::displayMailInfoCaution(const DString& strValue, const DString &strType, CListBox*& pCautionsListBox, int &index)
{
   if(strValue != NULL_STRING)
   {
      DString dstrList = strValue;

      do
      {
         DString::size_type pos = 0;

         DString dstrStage_;

         EXTRACT_VALUE(dstrList, dstrStage_)

         if (DSTCommonFunctions::codeInList( dstrStage_, UNCLAIMED_STAGE_CODES_LIST) ) //found the stage
         {
            fillChgMailInfoToCautionList(dstrStage_, strType,pCautionsListBox, index);			
         }
         CHOP_STRING (dstrList)
      }
      while (dstrList != NULL_STRING);

   }
}

//******************************************************************************
void BaseAccountDetailsDlg::fillCautionsList()
{
   DString str;
   int i = 0;
   CListBox *pCautionsListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_CAUTIONS ) );
   CString lbStrings;
   DString strString,
      taxType;

   pCautionsListBox->ResetContent();

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, taxType, false );
   taxType.strip().upperCase();

   if( taxType == TFSA_TAX_TYPES )
   {
      DString strTFSAEndDate, strTFSAEndDateTxt;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ExemptPeriod, strTFSAEndDate, false );

      lbStrings.LoadString( ROW_DETAILS_CAUTION_TXT_TFSA_ENDDATE );

      if (!strTFSAEndDate.empty() && 
         (DSTCommonFunctions::CompareDates (strTFSAEndDate, I_("12319999")) != DSTCommonFunctions::EQUAL))
      {
         DSTCommonFunctions::FormatDate(strTFSAEndDate);
         lbStrings = lbStrings + strTFSAEndDate.c_str();
         pCautionsListBox->InsertString( i++, lbStrings );
      }
   }   
   
  //P0186486_FN03 - RRIF Annuities: view 4 will validate on tax type instead
   {
      DString isLifeAnnuity;

      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::LifeAnnuityExist, isLifeAnnuity, false );
      isLifeAnnuity.strip().upperCase();

      if(isLifeAnnuity == Y_STRING)
      {
         lbStrings.LoadString( ROW_DETAILS_CAUTION_TXT_LIFE_ANNUITY );
         pCautionsListBox->InsertString( i++, lbStrings );
      }
      
   }

   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   {
      DString stopAdjDate;
      
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::StopAdjDate, stopAdjDate, false );
      stopAdjDate.strip().upperCase();
      
      if (!stopAdjDate.empty() && 
         (DSTCommonFunctions::CompareDates (stopAdjDate, I_("12319999")) != DSTCommonFunctions::EQUAL))
      {        
         DString dstrLbl;
         lbStrings.LoadString( ROW_DETAILS_CAUTION_TXT_ACCT_STOP_ADJDATE );
         DSTCommonFunctions::FormatDate(stopAdjDate);
         dstrLbl = I_(" : ") + stopAdjDate;
         lbStrings += dstrLbl.c_str ();
         pCautionsListBox->InsertString( i++, lbStrings);
      }
   }

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
     //P0178584_FN01_NewPopUpMSG
      DString strStageList(NULL_STRING), strStageExist(NULL_STRING);
      // return mail
      getParent()->getField( this, ifds::RtnMailStageList, strStageList, false ); //get code
      strStageList.stripAll().upperCase();
      displayMailInfoCaution(strStageList, RET_MAIL, pCautionsListBox, i);

      // stale cheque
      strStageList = NULL_STRING;
      strStageExist = NULL_STRING;
      getParent()->getField( this, ifds::StaleChqExists, strStageExist, false );
      strStageExist.stripAll().upperCase();

      if(strStageExist == I_("Y"))
      {
         getParent()->getField( this, ifds::StaleChqStageList, strStageList, false );
         strStageList.stripAll().upperCase();
         displayMailInfoCaution(strStageList, STLD_CHQ, pCautionsListBox, i);
      }

      // remitted cheque
      strStageList = NULL_STRING;
      strStageExist = NULL_STRING;
      getParent()->getField( this, ifds::RemittedChqExists, strStageExist, false );
      strStageExist.stripAll().upperCase();

      if(strStageExist == I_("Y"))
      {
         getParent()->getField( this, ifds::RemittedChqStageList, strStageList, false );
         strStageList.stripAll().upperCase();
         displayMailInfoCaution(strStageList, RMTD_CHQ, pCautionsListBox, i);
      }
      //End - P0178584_FN01_NewPopUpMSG 


      // account status
      DString strUnclmAcctStatus;
      DString strUnclmAcctStatusFmt;
      getParent()->getField( this, ifds::AcctStatus, strUnclmAcctStatus, false );

      if (DSTCommonFunctions::codeInList( strUnclmAcctStatus, REPORTED_REMITTED_STATUS) )
      {
         getParent()->getField( this, ifds::AcctStatus, strUnclmAcctStatusFmt, true );
         pCautionsListBox->InsertString( i++, strUnclmAcctStatusFmt.c_str() );
      }
   }

   // Account category
   getParent()->getField( this, ACCDETLIT::ACCTCATEGORY_DESC, str, false );
  
   bool bFoundPrivateWealthOptOut = false;

   DString strPrivateWealthOptOut(ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT);
   BFDataField::formatValue( ifds::AcctCategory, strPrivateWealthOptOut );
   strPrivateWealthOptOut.strip();

   if( !str.empty() )
   {
      DString dstrList, dstrAcctCatDesc;
      dstrList = str;
      
      int pos = 0;

      do 
      {
         pos = dstrList.find(  I_CHAR(';') );  // index into string
         if (pos != -1) 
         {        
            dstrAcctCatDesc = dstrList.substr(0, pos);  // get acct category description
            dstrList = dstrList.substr(pos+1);   // advance list
         }
         else
         {
            dstrAcctCatDesc = dstrList;
            dstrList = NULL_STRING;
         }

         pCautionsListBox->InsertString( i++, dstrAcctCatDesc.c_str() );

         if (strPrivateWealthOptOut == dstrAcctCatDesc.strip())
         {
            bFoundPrivateWealthOptOut = true;
         }

      } while(dstrList.length());
   }

   getParent()->getField (this, ifds::PrivateWealthOptOut, str, false);
   str.strip().strip().upperCase();
   if (str == Y_STRING && bFoundPrivateWealthOptOut == false)
   {
      pCautionsListBox->InsertString( i++, strPrivateWealthOptOut.c_str() );
   }

   getParent()->getField( this, ifds::PendingTrade, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_PENDING_TRADE );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   //Remarks button should always be enabled (for an account)
   ((CDSTCView*)GetMainView())->enableRemarksButton( true );

   getParent()->getField( this, ifds::Remarks, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_REMARKS );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::Certificates, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_CERTIFICATES_ISSUED );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopPurchase, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_STOP_PURCHASE );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopRed, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_STOP_REDEEM );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopXferOut, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_OUT );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopXferIn, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_IN );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopNFU, str, false );
   if(str ==  Y_STRING) 
   {
      lbStrings.LoadString( IDS_STOP_NFU );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings);
   }

   getParent()->getField( this, ifds::StopAMSRebalancing, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_STP_AMSREBALANCING );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::HoldDivPymt, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_HOLD_DIV_PAYMENT );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   bool bPermit = getParent()->hasReadPermission( UAF::SETTLE_ACCOUNT ) ;

   getParent()->getField( this, ifds::UnsettledTrn, str, false );
   if( str == Y_STRING && bPermit )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_UNSETTLED_TRANSACTION );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::FeeWaived, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_FEE_FEEWVD );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::SupEmpConf, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_SPR_EMPCNF );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::SupConf, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_SPR_CONFIRM );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::Unseizable, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_MSC_UNSZBL );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::StopFCrebal, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( IDS_STP_FRREB );
      lbStrings.TrimLeft();
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   //rule: display bank charges if it is not zero
   getParent()->getField( this, ifds::BankChrgs, str, false );
   if( !str.strip().empty() && str != I_("0") )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_BANK_CHARGES );
      pCautionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, ifds::ConsolidEFT, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_CONSOLID_EFT );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   /*
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::CategMargin, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_MARGIN );
      pCautionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::CategLoan, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_LOAN );
      pCautionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::CategChqPriv, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_CHQ_PRIVILEGE );
      pCautionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::CategWrap, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_WRAP );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   */

   // Use Broker MF
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::UseBrokerMF, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_BROKER_FEES );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   // Early redemption
   getParent()->getField( this, ifds::ChargeERFee, str, false );
   if( str == Y_STRING ) {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_EARLY_REDEMTION_FEE );
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   // Short term transfer fee
   getParent()->getField( this, ifds::ChargeSTTRFee, str, false );
   if( str == Y_STRING ) {
      lbStrings.LoadString( ROW_DETAILS_CAUTIONS_SHORT_TERM_TRFER);
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   //DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {

      getParent()->getField( this, ifds::GSTExempt, str, false );
      if( str == Y_STRING )
      {
         lbStrings.LoadString( IDS_GST_EXEMPT );
         lbStrings.TrimLeft();
         pCautionsListBox->InsertString( i++, lbStrings );
      }
      getParent()->getField( this, ifds::ApplyPST, str, false );
      if( str == Y_STRING )
      {
         lbStrings.LoadString( IDS_PST_EXEMPT );
         lbStrings.TrimLeft();
         pCautionsListBox->InsertString( i++, lbStrings );
      }

      /*getParent()->getField( this, ifds::SocialCode, str, false );
      if ( str == I_( "WR" ) ){
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_WRAP );
         pCautionsListBox->InsertString( i++, lbStrings );
      }*/

      // Add from string table to cautions list box
      getParent()->getField( this, ifds::MgmtFeePayOption, str, false );
      if ( ( str != I_("0") ) && ( str != NULL_STRING ) ) {
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_MGMT_FEE_PAY_OPTN );
         pCautionsListBox->InsertString( i++, lbStrings );
      }

      getParent()->getField( this, ifds::ExistAssignee, str, false );
      if( str == Y_STRING ) {
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_EXIST_ASSIGNEE );
         pCautionsListBox->InsertString( i++, lbStrings );
      }

      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
         ifds::TaxTypeSchedule, str, false );
      if( str == I_("01") ) 
      {
         DString strTaxTypeDesc;
         getParent()->getField( this, ifds::TaxType, strTaxTypeDesc, true );
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_OLD_LIF );
         lbStrings = strTaxTypeDesc.c_str() + lbStrings;
         pCautionsListBox->InsertString( i++, lbStrings );
      }
   }
   else if ( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      DString dstrStopSettle;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
         ifds::StopRedSettle, dstrStopSettle, false );
      dstrStopSettle.strip().upperCase();
      if( dstrStopSettle == YES )
      {
         lbStrings.LoadString( IDS_STOP_REDEEMPTION_SETTLE );
         lbStrings.TrimLeft();
         pCautionsListBox->InsertString( i++, lbStrings );
      }
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::DTAType, str, true );
   if( str != NULL_STRING && getParent()->hasReadPermission( UAF::DIRECT_TRADING_AGREEMENT) )
   {
      MFAccount *pMFAccount;
      DString accountNum;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum );
      accountNum.strip();
      accountNum.stripLeading( '0' );

      if( dstcWorkSession->getMFAccount( getDataGroupId(), accountNum, pMFAccount ) <= WARNING )
      {
         if( pMFAccount->isAcctDTAEligible( getParent()->getDataGroupId() ) )
         {
            lbStrings = str.asA().c_str();
            pCautionsListBox->InsertString( i++, lbStrings );
         }
      }
   }

   // Clearing ID
   getParent()->getField( this, ifds::ClearingID, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   //TerritoryCode
   getParent()->getField( this, ifds::TerritoryCode, str, true );
   if( !str.empty() ) 
   {
      lbStrings.LoadString( IDS_TERRITORY_CODE );
      strString = lbStrings;
      str = strString.stripLeading( ' ' ) + I_(" - ") + str;
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   // Clearing Firm
   DString dstrNSCCCompliant;

   if( dstcWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false ) <= WARNING )
   {
      if( dstrNSCCCompliant == YES )
      {
         getParent()->getField( this, ifds::ClearingFirm, str, true );
         if( !str.strip().empty() ) 
         {
            lbStrings.LoadString( IDS_MSC_CLEARINGFIRM );
            strString = lbStrings;
            str = strString.stripLeading( ' ' ) + I_(" - ") + str;
            pCautionsListBox->InsertString( i++, str.c_str() );
         }
      }
   }

   // Social Code
   getParent()->getField( this, ifds::SocialCode, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   DString affluentCode;
   
   getParent()->getField( this, ifds::Affluent, affluentCode, false );
   getParent()->getField( this, ifds::Affluent, str, true );
   if( !str.empty() && affluentCode.upperCase() != I_("O") && hasReadPermission (UAF::ACCOUNT_DETAIL) ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   DString linkMFR;

   getParent()->getField( this, ifds::LinkMFR, linkMFR, false );
   linkMFR.upperCase();
   getParent()->getField( this, ifds::LinkMFR, str, true );
   if( !str.empty() && linkMFR == I_("Y")) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   //DOT and Addendum
   getParent()->getField( this, ifds::DOTAdnd, str, false);
   if(!str.empty ()) 
   {
      if (str == DOT)
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_DOT );
      else if (str == ADDENDUM)
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_ADND);
      else if (str == DOT_AND_ADDENDUM)
         lbStrings.LoadString( ROW_DETAILS_CAUTIONS_DOTADND);

      pCautionsListBox->InsertString( i++, lbStrings );
   }

   // AML data
   getParent()->getField( this, ifds::TypeOfInvestor, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   getParent()->getField( this, ifds::InvestingOnBehalf, str, true );
   if( !str.empty() &&  (str == YES || str == I_("1"))) 
   {
      lbStrings.LoadString( IDS_INVONBEHALF );
      strString = lbStrings;
      str = strString.stripLeading( ' ');
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   getParent()->getField( this, ifds::ComplianceCode, str, true );
   if( !str.empty() ) 
   {
      lbStrings.LoadString( IDS_TXT_COMP_CODE );
      strString = lbStrings;
      str = strString.stripLeading( ' ') + I_(" " ) + str;

      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   // 
   //Management Fee
   getParent()->getField( this, ifds::MgmtFeeId, str, true );
   if( !str.empty() ) 
   {
      lbStrings.LoadString( TXT_MGMT_FEE_ID );
      lbStrings = lbStrings + " " + str.c_str();

      pCautionsListBox->InsertString( i++, lbStrings);
   }

   getParent()->getField( this, ifds::MgmFeeType, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   getParent()->getField( this, ifds::MgmtFeeRbtId, str, true );
   if( !str.empty() ) 
   {
      lbStrings.LoadString( TXT_MGMT_FEE_RBT_ID );
      lbStrings = lbStrings + " " + str.c_str(); 	

      pCautionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::MgmtFeeRbtType, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }

   getParent()->getField( this, ifds::InvoiceModelID, str, true );
   if( !str.empty() ) 
   {
      lbStrings.LoadString( TXT_INVOICE_ID );
      lbStrings = lbStrings + " " + str.c_str(); 	
      pCautionsListBox->InsertString( i++, lbStrings );
   }

   // Highest Entity Risk Level
   DString dstrHighestEntityRisk, dstrHighRiskLevels, dstrDisplayCode;
   getParent()->getField( this, ifds::HighestEntityRisk, dstrHighestEntityRisk, false );
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
   if( dstWorkSession && 
       (dstWorkSession->getOption( ifds::HighRiskLevels, dstrHighRiskLevels, getParent()->getDataGroupId() ) <= WARNING ) &&
       (dstWorkSession->getOption( ifds::HighRiskDispMode, dstrDisplayCode, getParent()->getDataGroupId() ) <= WARNING) )
   {
      if(DSTCommonFunctions::codeInList(dstrHighestEntityRisk, dstrHighRiskLevels ))
      {
        lbStrings.LoadString( TXT_HIGH_RISK );
        if( I_("1") == dstrDisplayCode )
        {
          DString dstrHighRiskCode;
          getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::HighestEntityRisk, dstrHighRiskCode, true );
          dstrHighRiskCode =  I_(" -") + dstrHighRiskCode;
          lbStrings.Append(dstrHighRiskCode.c_str());
        }
        pCautionsListBox->InsertString( i++, lbStrings );
      }
   }

   //NetworkID: display NetworkID if it is set with a value
   getParent()->getField( this, ifds::NetworkID, str, true );
   if( !str.strip().empty() )
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }
   
   DString dstrNextMFRProcessDate, dstrIsMFRAccount;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::NextMFRProcessDate, dstrNextMFRProcessDate, false );
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::IsMFRAccount, dstrIsMFRAccount, false );
   dstrIsMFRAccount.strip().upperCase();

   if( dstrIsMFRAccount == YES )
   {

      DSTCommonFunctions::FormatDate(dstrNextMFRProcessDate);

      lbStrings.LoadString( TXT_MFR_NEXT_PROC_DATE );
      lbStrings = lbStrings + " " + dstrNextMFRProcessDate.c_str(); 	

      pCautionsListBox->InsertString( i++, lbStrings );
   }

   if( dstcWorkSession->isIWTClient( getDataGroupId() ) )
   {
      DString accountNum;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum );
      accountNum.strip();
      accountNum.stripLeading( '0' );

      MFAccount* pMFAccount = NULL;
      if ( dstcWorkSession->getMFAccount (getDataGroupId(), accountNum, pMFAccount) <= WARNING &&
           pMFAccount )
      {
         // For Non-Taxable account, display TIN number warning if there is no TIN number.
         if( pMFAccount->isIWTNonTaxable( getDataGroupId() ) )
         {
            DString dstrIsTinExists;
            getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TINExists, dstrIsTinExists, false );

            if( dstrIsTinExists != I_("Y") )
            {
               lbStrings.LoadString( TXT_TIN_NOT_EXISTS );
               pCautionsListBox->InsertString( i++, lbStrings );
            }
         }
      }
   }
   
   getParent()->getField(this, ifds::AdvisorFeeExist, str, true);
   if (str.stripAll().upperCase() == YES) 
   {
       lbStrings.LoadString(TXT_ADVISOR_FEE);
       pCautionsListBox->InsertString(i++, lbStrings);
   }

   // indicia search pending review
   DString pendingFATCASrch;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PendingFATCASrch, pendingFATCASrch,false );
   pendingFATCASrch.strip().upperCase();

   if(pendingFATCASrch == I_("Y"))
   {
      lbStrings.LoadString( TXT_INDICIA_PENDING );
      pCautionsListBox->InsertString( i++, lbStrings );
   }
   
   // Investor Classification
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::InvestorClassification, str, true );
   if( !str.empty() ) 
   {
      pCautionsListBox->InsertString( i++, str.c_str() );
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::fillOptionsList()
{
   DString str;
   int i = 0;
   CListBox *pOptionsListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_OPTIONS ) );
   CString lbStrings;

   pOptionsListBox->ResetContent();

   getParent()->getField( this, ifds::BankingInstr, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_BANKING );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::CashSweepExists, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_CASHSWEEP );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::MatIntExists, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_MATURITY );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
   
   getParent()->getField( this, ifds::SystemTrsfr, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_SYSTEMATIC_TRANSFER );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::PAC, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_PAC );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::SWP, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_SWP );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::AMS_OPTION, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_AMS );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::SavePlanExist, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_SAVING_PLAN );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ifds::AcctAlloc, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_ALLOCATIONS  );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ExistBeneficiary, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_BENEF );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, ifds::FamilyCodeExist, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_SHR_FAMILY );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, ifds::ProtContractExists, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_PROT_CONTRACTS );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
   getParent()->getField( this, ifds::AcctCategoryExist, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_ACCT_CATEGORY );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
   
   getParent()->getField( this, ifds::DocListExists, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_ACCT_DOC_LIST );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
// Incorrect business logic
   DString dstrCommissionType;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
   if( dstWorkSession->getOption( ifds::CommissionType, dstrCommissionType, getParent()->getDataGroupId() ) <= WARNING )
   {
      if( dstrCommissionType == I_("2") )
      {
         getParent()->getField( this, ifds::AcctCommExists, str, false );      
         if( str == Y_STRING )
         {
            lbStrings.LoadString ( ROW_DETAILS_OPTIONS_COMMISSIONABLE_REPS );
            pOptionsListBox->InsertString( i++, lbStrings );
         } /*else 
         {     
            ((CDSTCView*)GetMainView())->enableTradeButton( false );
         }*/
      }
   }

   // Settlement Location at Account Level
   DString dstrClearingID;
   getParent()->getField( this, ifds::SettleLocExist, str, false );
   getParent()->getField( this, ifds::ClearingID, dstrClearingID, false );
   if( str == Y_STRING && !dstrClearingID.empty() )
   {
      lbStrings.LoadString( TXT_SETTLEMENT_LOCATION );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   // Shareholder Fund Sponsor Agreement
   bool blFundSponsorAgreement = hasReadPermission( UAF::SHR_FUND_SPONSOR_AGREEMENT );
   DString dstrShrFndSpExists;
   getParent()->getField( this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::ShrFndSpAgrExists, dstrShrFndSpExists, false );	
   if ( blFundSponsorAgreement &&
      I_( "Y" ) == dstrShrFndSpExists.strip().upperCase() )
   {
      lbStrings.LoadString ( ROW_DETAILS_OPTIONS_SHR_FUND_SPONSOR_AGREEMENT );
      pOptionsListBox->InsertString ( i++, lbStrings );
   }

   // Shareholder Fund Broker	
   bool blShrFndBrk = hasReadPermission( UAF::SHR_FUND_BROKER );
   DString dstrShrFndBrkExist;
   getParent()->getField( this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::ShrFndBrkExist, dstrShrFndBrkExist, false);	
   if ( blShrFndBrk &&
      I_( "Y" ) == dstrShrFndBrkExist.strip().upperCase() )
   {
      lbStrings.LoadString ( ROW_DETAILS_OPTIONS_SHR_FUND_BROKER );
      pOptionsListBox->InsertString ( i++, lbStrings );
   }

   // Acct Cut Off Time
   DString dstrExist;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AcctCutOffTimeExists, dstrExist, false );
   if ( hasReadPermission( UAF::ACCT_LVL_CUT_OFF_TIME ) && I_( "Y" ) == dstrExist.strip().upperCase() )
   {
      lbStrings.LoadString ( TXT_ACCT_CUT_OFF_TIME );
      pOptionsListBox->InsertString ( i++, lbStrings );
   }

   DString dstrFundLimitOvrdExist;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::FundLimitOvrdExist, dstrFundLimitOvrdExist, false );
   if( hasReadPermission(  UAF::ACCOUNT_TRADING_OVERRIDES ) && dstrFundLimitOvrdExist == Y_STRING )
   {
      lbStrings.LoadString( TXT_FUND_CLASS_LIMITATION  );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   // Account level settlement rule
   DString dstrIsAcctLevelSettlementRuleExist;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, 
       ifds::SettlementRuleExist,dstrIsAcctLevelSettlementRuleExist, false );
   if( hasReadPermission(  UAF::ACCT_LEVEL_SETTLEMENT_RULE ) && dstrIsAcctLevelSettlementRuleExist == Y_STRING )
   {
       lbStrings.LoadString( ROW_DETAILS_SETTLEMENT_RULE  );
       pOptionsListBox->InsertString( i++, lbStrings );
   }

   // Investor Authorization
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      DString strIARuleSetup;
      getParent()->getField( this, 
                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
                             ifds::IARuleSetup, 
                             strIARuleSetup, 
                             false );

      strIARuleSetup.strip().upperCase();

      DString dstrDirDepsBnkApplicable;
      dstWorkSession->getOption (ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, 
                                 getParent()->getDataGroupId(),
                                 false );
      dstrDirDepsBnkApplicable.strip().upperCase();

      if (strIARuleSetup == I_("Y") && dstrDirDepsBnkApplicable == I_("Y"))
      {
         DString strIARuleSetupFmt = I_("Investor Authorization");
         pOptionsListBox->InsertString( i++, strIARuleSetupFmt.c_str() );
      }

      DString dstrTaxType, dstrGovAmendmentExist;
      getParent()->getField(this, ifds::TaxType, dstrTaxType, false);

      getParent()->getField (this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::GovAmendmentExist, dstrGovAmendmentExist, false );
      dstrGovAmendmentExist.strip().upperCase();
      bool bPermit = dstrGovAmendmentExist == I_("Y") ? true : false;

      if ( bPermit &&
           ( DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES) || 
             dstrTaxType == TFSA_TAX_TYPES ))
      {
         lbStrings.LoadString( ROW_DETAILS_OPTIONS_RESP_GOVT_FILING_AMENDMENT );
         pOptionsListBox->InsertString( i++, lbStrings );
      }

   }


   bool bVerificationEnabled = false;
   dstWorkSession->isVerificationEnabled (getParent()->getDataGroupId(), 
                                          ENTITY_CATEGORY, 
                                          ENTITY_LEVEL, 
                                          bVerificationEnabled );

   //account static data verification
   if (hasReadPermission (UAF::ACCOUNT_STATIC_DATA_VERIFY) && bVerificationEnabled )
   {
      lbStrings.LoadString (ROW_DETAILS_ACCOUNT_STATIC_DATA_VERIFY);
      pOptionsListBox->InsertString (i++, lbStrings);
   }

   DString dstrSegClient, dstrCotClient, dstrGuaranteeGuardOn;

   dstWorkSession->getOption ( ifds::SegClient, dstrSegClient, getDataGroupId(), false );
   dstWorkSession->getOption ( ifds::CotClient, dstrCotClient, getDataGroupId(), false );
   dstWorkSession->getOption ( ifds::GuaranteeGuardOn, dstrGuaranteeGuardOn, getDataGroupId(), false );
   dstrSegClient.strip().upperCase();
   dstrCotClient.strip().upperCase();
   dstrGuaranteeGuardOn.strip().upperCase();
      
   if( dstrSegClient == YES && dstrCotClient == YES && dstrGuaranteeGuardOn == YES )
   {
      DString dstrAcctGuarGuardExists;
      getParent()->getField( this, 
                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
                             ifds::AcctGuarGuardExists, 
                             dstrAcctGuarGuardExists, 
                             false );
      dstrAcctGuarGuardExists.strip().upperCase();

      if(dstrAcctGuarGuardExists == YES)
      {
         lbStrings.LoadString (ROW_DETAILS_OPTIONS_ACCT_GUARNT_GUARD_OPTN);
         pOptionsListBox->InsertString( i++, lbStrings );
      }
   }

   getParent()->getField( this, ACCDETLIT::HAS_ACCT_OWNERSHIP_RECORD, str, false );
   str.strip().upperCase();

   if(str == I_("Y"))
   {
      lbStrings.LoadString(ROW_DETAILS_OPTION_ACCT_OWNERSHIP_ALLOC);
      pOptionsListBox->InsertString( i++, lbStrings );   
   }

   // Account level Fee Model Association
   DString dstrIsAcctAssociateExist;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, 
       ifds::AcctFeeModelAssociated,dstrIsAcctAssociateExist, false );
   if( hasReadPermission(  UAF::ACCT_FEE_MODEL_ASSOCIATION ) && dstrIsAcctAssociateExist == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_OPTIONS_FEE_MODEL_ASSOCIATION  );
	  pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AcctIdentifierExist, str, false );
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ID_STR_ACCOUNT_IDENTIFIER );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   // Account Regulatory Details
   DString dstrAcctRegulatoryExist;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, 
       ifds::AcctRegulatoryExist, dstrAcctRegulatoryExist, false);
   if(hasReadPermission(UAF::ACCT_REGIS_MAINT) && dstrAcctRegulatoryExist == Y_STRING)
   {
	   lbStrings.LoadString(TXT_ACCT_REG_DETAILS);
	   pOptionsListBox->InsertString(i++, lbStrings);
   }

   // Entity Regulatory Details
   DString dstrEntRegDetlExist;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::EntRegDetlExist, dstrEntRegDetlExist, false);
   dstrEntRegDetlExist.stripAll().upperCase();

   if (hasReadPermission(UAF::ENTITY_REGULATORY_MAINT) && (dstrEntRegDetlExist == I_("1") || dstrEntRegDetlExist == I_("2")))
   {
	   lbStrings.LoadString(TXT_ENT_REG_DETL);
	   pOptionsListBox->InsertString(i++, lbStrings);
   }

   DString dstrAccountGroupExist;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountGroupExist, dstrAccountGroupExist, false );
   dstrAccountGroupExist.strip().upperCase();
   if( dstrAccountGroupExist == Y_STRING )
   {
      lbStrings.LoadString( TXT_ACCOUNT_GROUP_TITLE );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PrivateWealthAcct, str, false );
   str.strip().upperCase();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( TXT_PRIVATE_WEALTH_INFO_TITLE );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::RegisteredTransfers, str, false );
   str.strip().upperCase();
   if(hasReadPermission(UAF::REG_PLAN_TRANSFER) && str == Y_STRING )
   {
      lbStrings.LoadString( TXT_REGISTERED_PLAN_TRANSFER_TITLE);
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   if (hasReadPermission(UAF::ACCOUNT_GROUPING_INFO) && (dstrIsAcctAssociateExist == Y_STRING || dstrAccountGroupExist == Y_STRING))
   {
      lbStrings.LoadString( TXT_ACCOUNT_GROUPING_INFO_TITLE );
      pOptionsListBox->InsertString( i++, lbStrings );
   }

   // Account level rounding rule  
   DString dstrAccountNum, dstrAcctLevelRoundingRuleExists;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, dstrAccountNum);
   dstrAccountNum.strip();
   dstrAccountNum.stripLeading('0');

   MFAccount* pMFAccount = NULL;
   if (dstWorkSession->getMFAccount(getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
	   if ( hasReadPermission( UAF::ACCT_ROUNDING_RULE ) && pMFAccount->hasAcctRoundingRule( getDataGroupId()) )
	   {
		   lbStrings.LoadString( TXT_ACCT_ROUNDING_RULE  );
		   pOptionsListBox->InsertString( i++, lbStrings );
	   }
   }

   getParent()->getField( this, ifds::AcctDelState, str, false ); 
   str.strip();
   if( str == Y_STRING && hasReadPermission( UAF::ACCT_DELETION_REVIEW ) )
   {
      lbStrings.LoadString( TXT_ACCT_DEL_REVIEW );
      pOptionsListBox->InsertString( i++, lbStrings );
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::fillAttributesList()
{
   DString str;
   int i = 0;
    bool bPermit = false;
   CListBox *pAttributesListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_ATTRIB ) );
   CString lbStrings;

   pAttributesListBox->ResetContent();

   getParent()->getField( this, ACCDETLIT::ACB_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString (ROW_DETAILS_ATTRIBUTES_ACB);
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_SHAREHOLDER );
   pAttributesListBox->InsertString( i++, lbStrings );

   getParent()->getField( this, ACCDETLIT::ADDRESS_BOOK_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ADDR_BOOK_MAIL_ASSIGN );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::FEE_PARAMETER_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_MANAGEMENT_FEE );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::ACCT_TRAILER_FEE, str, false );
   str.strip();
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   DString IsTrlFeeAcctLevelApp;
   dstWorkSession->getOption(ifds::IsTrlFeeAcctLevelApp, IsTrlFeeAcctLevelApp, getParent()->getDataGroupId(), false);
   if( str == Y_STRING && IsTrlFeeAcctLevelApp.upperCase() == Y_STRING)
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_TRAILERFEE_SETUP );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::ENTITY_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
     lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ENTITY );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::INTEREST_ACCRUED_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_INT_ACCRUED );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNT_INFORMATION );
   pAttributesListBox->InsertString( i++, lbStrings );

   getParent()->getField( this, ACCDETLIT::DEMOGRAPHICS_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_DEMOGRAPHICS );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::CHEQUE_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_CHEQUE_INFORMATION );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::HIST_MKT_VALUE_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_HIST_MKT_VALUE );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::DISTRIBUTION_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_DISTR_OPTIONS );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   loadRRIFString();

   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_HISTORICAL_ACCOUNT_INFORMATION );
   pAttributesListBox->InsertString( i++, lbStrings );

    //getParent()->getField( this, ACCDETLIT::ACCOUNT_DETAILS_LIST, ifds::ESoPEligible, str, false );
    //str.strip();
    //if( str == Y_STRING )
    //{
    //    lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ESOPINFO );
    //    pAttributesListBox->InsertString( i++, lbStrings );
    //}

   DString dstrTaxType;

   getParent()->getField(this, ifds::TaxType, dstrTaxType, false);

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      getParent()->getField( this, ACCDETLIT::CONTRACT_ATTR, str, false );
      str.strip();
      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_CONTRACT );
         pAttributesListBox->InsertString( i++, lbStrings );
      }

      getParent()->getField( this, ACCDETLIT::GUARANTEE_ATTR, str, false );
      str.strip();
      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_GUARANTEE );
         pAttributesListBox->InsertString( i++, lbStrings );
      }

      getParent()->getField( this, ACCDETLIT::RESPINFO_ATTR, str, false );
      str.strip();
      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESPINFO );
         pAttributesListBox->InsertString( i++, lbStrings );
      }

      getParent()->getField( this, ACCDETLIT::RESP_TRANSACTIONS_ATTR, str, false );
      str.strip();
      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESPTRANSACTIONS );
         pAttributesListBox->InsertString( i++, lbStrings );
      }

	 bPermit = getParent()->hasReadPermission( UAF::RESP_NOTIONAL_INFORMATION ) ;

	 if ( bPermit && 
         DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL );
         pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = getParent()->hasReadPermission( UAF::RESP_NOTIONAL_BALANCE ) ;

	 if ( bPermit &&
         DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
		 lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL_BALANCE );
         pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = getParent()->hasReadPermission( UAF::RESP_NOTIONAL_ACTIVITY ) ;

	 if ( bPermit && 
		  DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
		 lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_NOTIONAL_ACTIVITY );
		 pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = getParent()->hasReadPermission( UAF::RESP_ACCOUNT_TERMINATION ) ;

	 if ( bPermit &&
		   DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_ACCOUNT_TERMINATION );
         pAttributesListBox->InsertString( i++, lbStrings );
	 }

 	 bPermit = getParent()->hasReadPermission( UAF::RESP_ZERO_GRANT ) ;

	 if ( bPermit &&
		   DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ZERO_GRANT_REPAYMENT );
         pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = (getParent()->hasReadPermission( UAF::RESP_BENEFICIARY ) && getParent()->hasReadPermission( UAF::RESP_GRANTS ));

	 if ( bPermit && 
		 DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
		 lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_GRANT_INFO );
		 pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = (getParent()->hasReadPermission( UAF::RESP_BENEFICIARY ) && getParent()->hasReadPermission( UAF::RESP_GRANT_INFORMATION ));

	 if ( bPermit && 
		 DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
		 lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RESP_GRANT_INFO2 );
		 pAttributesListBox->InsertString( i++, lbStrings );
	 }

	 bPermit = getParent()->hasReadPermission( UAF::RESP_INTERFACE_FILE ) ;

	 if ( bPermit && 
         DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
	 {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_INTERFACE_FILE );
         pAttributesListBox->InsertString( i++, lbStrings );
	 }
      // YTD Contributions

      getParent()->getField( this, ACCDETLIT::YTD_CONTRIBUTION_ATTR, str, false );
      str.strip();
      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_YTDCONTRIBUTIONS );
         pAttributesListBox->InsertString( i++, lbStrings );
      }
   }

   // Tax Exempt Authorization
   DString dstrRegisteredTaxTypes, dstrEUSDParticip, backupWithholdingTax;
   
   dstWorkSession->getOption(ifds::RegisteredTaxTypes, dstrRegisteredTaxTypes, getParent()->getDataGroupId(), false);
   dstWorkSession->getOption(ifds::EUSDParticip, dstrEUSDParticip, getParent()->getDataGroupId(), false);
   dstrTaxType.strip().upperCase();
   dstWorkSession->getOption(ifds::BackWithholdTax, backupWithholdingTax, getParent()->getDataGroupId(), false);
   backupWithholdingTax.strip().upperCase();
   
   if (hasReadPermission(UAF::TAX_EXEMPT_AUTHORIZATION) && 
      ( DSTCommonFunctions::codeInList (dstrTaxType, dstrRegisteredTaxTypes) || 
        dstrEUSDParticip == YES ||
        backupWithholdingTax == YES))
   {
      lbStrings.LoadString (ROW_DETAILS_ATTRIBUTES_TAX_EXEMPT_AUTHORIZATION);
      pAttributesListBox->InsertString (i++, lbStrings);
   }

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, dstrTaxType, false );
   dstrTaxType.strip();

   if( dstrTaxType == I_( "P" ) )
   {
      getParent()->getField( this, ACCDETLIT::AS_PENSION_ATTR, str, false );
      str.strip();

      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_AS_PENSION );
         pAttributesListBox->InsertString( i++, lbStrings );
      }
   }

   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_FREE_UNITS );
   pAttributesListBox->InsertString( i++, lbStrings );

   getParent()->getField ( this, ACCDETLIT::HYPOTHETICAL_REDEMPTION_ATTR , str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString ( ROW_DETAILS_ATTRIBUTE_HYPOTHETICAL_REDEMPTION );
      pAttributesListBox->InsertString ( i++, lbStrings );
   }

   /*DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());*/
   DString dstrForeignContent(NULL_STRING);
   dstWorkSession->getOption( ifds::ForeignContent, dstrForeignContent, getParent()->getDataGroupId(), false ); 
   bool bAccessForeignCont = dstrForeignContent.strip().upperCase() == YES && hasReadPermission( UAF::FOREIGN_CONTENT );
   if ( bAccessForeignCont )
   {
      lbStrings.LoadString ( ROW_DETAILS_ATTRIBUTES_FOREIGN_CONTENT_WORKSHEET );
      pAttributesListBox->InsertString ( i++, lbStrings );
   }

   // Account Review
   getParent()->getField( this, ACCDETLIT::ACCOUNTREVIEW, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNTREVIEW );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   if( dstWorkSession->isLIFLike (dstrTaxType) || dstWorkSession->isLIRALike (dstrTaxType) || 
       dstrTaxType == I_( "L" ))
   {
//      getParent()->getField( this, ACCDETLIT::PENSION_INFO_ATTR, str, false );
//      str.strip();
//      if( str == Y_STRING )
      {
         lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_PENSION_INFO );
         pAttributesListBox->InsertString( i++, lbStrings );
      }
   }

   //
   // eStatement Permission
   //
   // At the moment, using the Registry setting to decide if to permit the feature
   // R48, a system feature will be added for the permission
   //
   //DString estmtPerm = GetConfigValueAsString(I_("LocaleFormats"), I_("eStatement"), I_("Permission"));
   DString estmtPerm;
   getParent()->getField( this, ACCDETLIT::ESTATEMENT_ATTR, estmtPerm, false );
   estmtPerm.strip().upperCase();
   if( estmtPerm == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_ESTATEMENT );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   getParent()->getField( this, ACCDETLIT::FEEMODEL_ATTR, str, false );
   str.strip();
   if( str == Y_STRING )
   {
      lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_FEE_MODEL );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   if( strMarket == MARKET_IDS::CANADA )
   {
      //load LIF Gain/Loss if applicable	  
      DString strEligible;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::EligExtTrfGainLoss, strEligible, false );
      if( strEligible.strip() == I_("Y") )
      {
         lbStrings.LoadString( ROW_LIF_GAIN_LOSS );
         DString strTaxTypeDesc;
         getParent()->getField( this, ifds::TaxType, strTaxTypeDesc, true );
         lbStrings = strTaxTypeDesc.c_str() + CString(" ") + lbStrings;
         pAttributesListBox->InsertString( i++, lbStrings );
      }
   }

   DString dstrTFSATaxList;
   dstWorkSession->getOption (ifds::TFSATaxList, dstrTFSATaxList, getParent()->getDataGroupId());
   bPermit = getParent()->hasReadPermission( UAF::TFSA_CONTRIBUTION_INFO ) ;


   if (DSTCommonFunctions::codeInList (dstrTFSATaxList, dstrTaxType) && bPermit)
   {
      lbStrings.LoadString( ROW_DETAILS_TFSA_CONTRIBUTION_INFO );
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   DString dstrAccountNum;
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, dstrAccountNum);
   dstrAccountNum.strip();
   dstrAccountNum.stripLeading('0');

   MFAccount* pMFAccount = NULL;
   if (dstWorkSession->getMFAccount(getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
		if ( pMFAccount->hasGIAHolding( getDataGroupId()) )
		{
			lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_INVESTMENT_HISTORY );
			pAttributesListBox->InsertString( i++, lbStrings );
		}
   }

   getParent()->getField( this, ifds::CommitmentStatus, str, false );
   str.strip();
   if( str.length() != 0)
   {
      lbStrings.LoadString(ROW_DETAILS_ATTRIBUTES_ACCOUNT_COMMITMENT);
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   DString dstrFATCAApplicable;
   dstWorkSession->getOption (ifds::FATCAApplicable, dstrFATCAApplicable, getParent()->getDataGroupId(), false);
   //bPermit = getParent()->hasReadPermission( UAF::TFSA_CONTRIBUTION_INFO ) ;
   dstrFATCAApplicable.strip().upperCase();
   //if( dstrFATCAApplicable == I_("Y"))
   {
      lbStrings.LoadString(ROW_DETAILS_ATTRIBUTES_FOREIGN_TAX_REVIEW);
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   DString dstrInitialDate;
   pMFAccount->getField(ifds::InitialDate, dstrInitialDate, getParent()->getDataGroupId());
   if(hasReadPermission(UAF::VALUE_VARIATION) && !dstrInitialDate.empty() && dstrInitialDate != I_("31129999"))
   {
      lbStrings.LoadString(ROW_DETAILS_VALUE_VARIATION);
      pAttributesListBox->InsertString( i++, lbStrings );
   }

   DString dstrTaxFormsAppl;
   pMFAccount->getField(ifds::TaxFormsAppl, dstrTaxFormsAppl, getParent()->getDataGroupId());
   if (dstrTaxFormsAppl.stripAll().upperCase() == YES)
   {
       lbStrings.LoadString(ROW_DETAILS_TAX_SLIPS);
       pAttributesListBox->InsertString(i++, lbStrings);
   }

   DString dstrIsRegExtrAcct;
   pMFAccount->getField(ifds::IsRegExtrAcct, dstrIsRegExtrAcct, getParent()->getDataGroupId());
   if (dstrIsRegExtrAcct.stripAll().upperCase() == YES)
   {
	   lbStrings.LoadString(ROW_DETAILS_ATTRIBUTES_REG_ACCT_INFO_REV);
	   pAttributesListBox->InsertString(i++, lbStrings);
   }

   if ( dstrTaxType == I_("RS"))
   {
	   //bPermit = getParent()->hasReadPermission( UAF::RDSP_ACCOUNT_INFORMATION ) ;

	   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_ACCOUNT_INFORMATION );
	   pAttributesListBox->InsertString( i++, lbStrings );

	   //bPermit = getParent()->hasReadPermission( UAF::RDSP_INTERFACE_TRANSACTIONS ) ;

	   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_INTERFACE_TRANSACTIONS );
	   pAttributesListBox->InsertString( i++, lbStrings );

	   //bPermit = getParent()->hasReadPermission( UAF::RDSP_NOTIONAL_ACTIVITY ) ;

	   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_NOTIONAL_ACTIVITY );
	   pAttributesListBox->InsertString( i++, lbStrings );

	   //bPermit = getParent()->hasReadPermission( UAF::RDSP_NOTIONAL_BALANCE ) ;

	   lbStrings.LoadString( ROW_DETAILS_ATTRIBUTES_RDSP_NOTIONAL_BALANCE );
	   pAttributesListBox->InsertString( i++, lbStrings );
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::OnKillfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   int idx = m_lvTransactions.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      m_lvTransactions.SetSelection( lastFocusTransactions, false );
      lastFocusTransactions = idx;
   }
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   int idx = m_lvEntitiesIds.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      m_lvEntitiesIds.SetSelection( lastFocusTransactions, false );
      lastFocusEntitiesIds = idx;
   }
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::displayTitle()
{
   DString AccNum;

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, AccNum );
   AccNum.strip();
   AccNum.stripLeading( '0' );
   DString dstrEntityName;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), AccNum, dstrEntityName, true );

   CString strName, strSemicol;
   strName.LoadString( COL_VERIFYS_NAME );
   strSemicol.LoadString( IDS_LBL_SEMICOL );

   DString dstrTitle = AccNum + SPACE_STRING + ( LPCTSTR ) strName + ( LPCTSTR ) strSemicol + SPACE_STRING + dstrEntityName;

   SetAccount( dstrTitle);
   SetAccountCaption();
}

//******************************************************************************

BOOL BaseAccountDetailsDlg::PreTranslateMessage(MSG* pMsg) 
{
   // TODO: Add your specialized code here and/or call the base class

   if( pMsg->message == WM_KEYDOWN && pMsg->wParam == 9 )
      flgTabPressed = true;
   BOOL   IsTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      IsTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !IsTranslated )
   {
      // pass message down the chain
      IsTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }
   return( IsTranslated );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAccelAccounts() 
{
   // TODO: Add your command handler code here

   m_lvAccounts.SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAccelFund() 
{
   // TODO: Add your command handler code here

   m_lvFunds.SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::fillCallerInfo()
{
   if( GetMainView() )
   {
      DString home_phone;
      DString entityDescr;
      DString name;
      BFDate d( BFDate::today() );
      DString timeOfCall = d.get( BFDate::DF_FSUS );
      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, false );
      else if( strMarket == MARKET_IDS::JAPAN )
         getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, true );

      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityDescr );
      getParent()->getField( this, ACCDETLIT::PHONE_NUMBER, home_phone );
      ((CDSTCView*)GetMainView())->setCallerName( name.c_str() );
      ((CDSTCView*)GetMainView())->setCallerPhoneNum( home_phone.c_str() );
      ((CDSTCView*)GetMainView())->setCallerRelationship( entityDescr.c_str() );
      ((CDSTCView*)GetMainView())->setCallerTimeOfCall( timeOfCall.c_str() );
   }
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAccelCautions() 
{
   // TODO: Add your command handler code here

   flgTabPressed = true;
   m_lbCautions.SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAccelOptions() 
{
   // TODO: Add your command handler code here

   flgTabPressed = true;
   m_lbOptions.SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAccelAttributes() 
{
   // TODO: Add your command handler code here

   flgTabPressed = true;
   m_lbAttributes.SetFocus();
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   int idx = m_lvKanaAddr.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      lastFocusKanaAddr = idx;
   }
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnKillfocusLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   int idx = m_lvKanjiAddr.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      lastFocusKanjiAddr = idx;
   }
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnDblclkLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvKanaAddr" ) );

   E_COMMANDRETURN eRtn = CMD_OK;

   //check security on the Shareholder addresses
   DString security;

   getParent()->getField( this, ACCDETLIT::ADDRESS_BOOK_ATTR, security, false );
   security.strip();
   if( security != Y_STRING )
   {
      //the user doesn't have access to the entity screen
      return;
   }
   CWaitCursor wait;
   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString strShrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   int addrIndex = m_lvKanaAddr.GetNextSelection( );
   if( addrIndex == -1 )// There is no account selected
   {
      return;
   }

   DString code;
   CString temp;
   int index = m_cmbAddrSel.GetCurSel();
   if( index == CB_ERR )
      code = NULL_STRING;
   else
   {
      m_cmbAddrSel.GetLBText( index, temp );
      code.assign( ( LPCTSTR ) temp, 0, 2 );
      code.insert( 0, FIRST_CHAR_K );
   }
   setParameter( ADDRESS_CODE, code );
   setParameter( SHAREHOLDER_NUM,strShrNum);

   setParameter( ACCOUNT_NUM, strAcctNum );
   SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );
   eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_NO_TYPE, false, NULL );
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

   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnDblclkLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvKanjiAddr" ) );

   E_COMMANDRETURN eRtn = CMD_OK;

   //check security on the Shareholder addresses
   DString security;

   getParent()->getField( this, ACCDETLIT::ADDRESS_BOOK_ATTR, security, false );
   security.strip();
   if( security != Y_STRING )
   {
      //the user doesn't have access to the entity screen
      return;
   }
   CWaitCursor wait;
   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   DString strShrNum = m_lvAccounts.GetItemString( accountIndex, I_( "ShrNum" ) );

   int addrIndex = m_lvKanjiAddr.GetNextSelection( );
   if( addrIndex == -1 )// There is no account selected
   {
      return;
   }

   DString code;
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) != EMPTY_STRING )
      {
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, code );
         code.strip();
      }
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      CString temp;
      int index = m_cmbAddrSel.GetCurSel();
      if( index == CB_ERR )
         code = NULL_STRING;
      else
      {
         m_cmbAddrSel.GetLBText( index, temp );
         code.assign( ( LPCTSTR ) temp, 0, 2 );
      }
   }
   setParameter( SHAREHOLDER_NUM,strShrNum);

   setParameter( ADDRESS_CODE, code );
   setParameter( ACCOUNT_NUM, strAcctNum );
   SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );
   eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_NO_TYPE, false, NULL );
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

   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::OnMove(int x, int y) 
{
   BaseMainDlg::OnMove(x, y);

   WINDOWPLACEMENT tmp;
   GetWindowPlacement( &tmp );
   DetailDlgRect=tmp.rcNormalPosition;
}

//******************************************************************************

bool BaseAccountDetailsDlg::AreThereAllocationInThisPending()
{
   DString str,strTransType;

   getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::TransType, strTransType,false );
   strTransType.strip();
   if( strTransType == I_("AFTR") ) return(false);
   getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxFundCode, str );
   str.stripAll();
   if( str == NULL_STRING )
      return(true);
   else
   {
      if( strTransType == XR || strTransType == TR || strTransType == TO || strTransType == EO )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::FundTo, str );
         str.stripAll();
         if( str==NULL_STRING )
            return(true);
      }
   }

   return(false);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnBtnNewAccount() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnNewAccount" ) );
   CWaitCursor wait;
   if( !canAddNewAccountOrClose() ) return;

   E_COMMANDRETURN eRtn = CMD_OK;
   int accountIndex = m_lvAccounts.GetNextSelection( );
   if( accountIndex == -1 )// There is no account selected
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }

   DString strShrNum, entityId, modelAccountNum;

   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ShrNum, strShrNum );
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, modelAccountNum );
   getParent()->getField( this, BF::NullContainerId, ACCDETLIT::INITIAL_ENTITY_ID, entityId );
   getParent()->setParameter( ACCINFOPROC::SHAREHOLDER_NUM, strShrNum );
   getParent()->setParameter( ACCINFOPROC::MODEL_ACCOUNT_NUM, modelAccountNum );
   getParent()->setParameter( ACCINFOPROC::ENTITY_ID, entityId );
   getParent()->setParameter( NASULIT::CREATING_ACCOUNT, YES );
   getParent()->setParameter( NASULIT::CREATING_SHAREHOLDER, NO );
   getParent()->setParameter( ENTPROC::MODEL_ACCOUNT_NUM, modelAccountNum );

   wait.Restore();
   eRtn = invokeCommand( getParent(), CMD_BPROC_NASU, PROC_NO_TYPE, true, NULL );
   wait.Restore();

   MSG msg;
   bool flg_refresh = true;

   PeekMessage( &msg, GetMainView()->m_hWnd, 0, 0, PM_NOREMOVE );
   if( msg.message == WM_COMMAND && msg.wParam == IDC_BTN_END ) {
      flg_refresh = false;
   }
#if 0
   //put it back
   GetMainView()->PostMessage( msg.message, msg.wParam, msg.lParam );
#endif
   SetMessageStatusBar( NULL_STRING );
   switch( eRtn )
   {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
         { 
            if( flg_refresh )
            {
               DString newAccKey, key;
               int count = 0;

               getParent()->modelessSetFocus( this );
               fillAccountList();
               getParent()->getField( this, ACCDETLIT::NEW_ACCOUNT_NUMBER, newAccKey );
               for( key = getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
                  key != NULL_STRING && key != newAccKey;
                  key = getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST ), count++ )
                  ;//empty body
               if( count < m_lvAccounts.GetItemCount() )
               {
                  m_lvAccounts.SetSelection( count );
               }
               else
               {
                  m_lvAccounts.SetSelection( 0 );
               }
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

//******************************************************************************

void BaseAccountDetailsDlg::OnBtnAwd() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNAWD );

   if( m_AwdActive == AWD_SESSION  && !BFAwdInterface::isLoggedOn() )
   {  // In case user is no longer logged into AWD
      m_AwdActive = NO_AWD;
   }

   if( !m_lvAccounts.GetItemCount() )
   {
      return;
   }

   int iAccountIndex = m_lvAccounts.GetNextSelection();
   if( iAccountIndex == -1 )
   {
      return;
   }

   if (m_AwdActive != AWD_SESSION) {
      
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   
      DString strAcctNum = m_lvAccounts.GetItemString( iAccountIndex, I_( "AccountNum" ) );

	  DString dstrAWDPortalURL;
	  dstcWorkSession->getOption(ifds::AWDPortalURL, dstrAWDPortalURL, BF::HOST);
	  if(!dstrAWDPortalURL.strip().empty())
	  {
		  setParameter (CALLER, I_("AccountDetails"));
		  setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, strAcctNum );

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
		  if ( dstcWorkSession->getMFAccount (getDataGroupId(), strAcctNum, pMFAccount) <= WARNING && pMFAccount )
		  {
         
			 AWDHistoryWorkList* awdWorkList = new AWDHistoryWorkList(*pMFAccount);
			 awdWorkList->init(((CDSTCView*)GetMainView())->lookupWork(strAcctNum));
			 pMFAccount->setAWDHistroyWorkList(awdWorkList);

			 setParameter( CALLER, I_("AccountDetails") );
			 setParameter( ACCOUNT_NUM, strAcctNum );
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
      return;

   }

   DString dstrAwdSourcePtr = getSession()->getSessionData( I_("_AwdInterface_Ptr_") );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *)dstrAwdSourcePtr.asInteger();

   DString strAcctNum = m_lvAccounts.GetItemString( iAccountIndex, I_( "AccountNum" ) );

   ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgWorkTable = pConfigManager->retrieveConfig( SessionTags::WORK_TABLE );

   // Set Business Area
   DString dstrCompanyId( NULL_STRING );
   DString dstrBusinessArea( NULL_STRING );

   // Get Company ID
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getMgmtCo().getField(ifds::CompanyId, dstrCompanyId, BF::HOST );

   // Iterate AWD Business Area list in MGMCO to find matching ID
   short nFound = 0;
   if( !dstrCompanyId.empty() )
   {
      Configuration cfgMGMCOTable = pConfigManager->retrieveConfig( SessionTags::MGMCO );

      DString dstrTempSystemID( NULL_STRING );
      Configuration::iterator iter = cfgMGMCOTable.begin();
      while( iter != cfgMGMCOTable.end() )
      {
         dstrTempSystemID = ( *iter ).getValueAsString();
         dstrTempSystemID.strip().stripAll( I_CHAR('\t') );

         if( dstrTempSystemID == dstrCompanyId )
         {
            ++nFound;
            dstrBusinessArea = ( *iter ).getKey();
            dstrBusinessArea.strip().stripAll( I_CHAR('\t') );
            //break;
         }
         ++iter;
      }
      if( nFound > 1 )
      {
         dstrBusinessArea = NULL_STRING;
      }
   }

   CriteriaVector criteriaList;

   // Add Business_Area (UNIT=) Criteria
   BFAwdLookupCriteria criteriaBusinessArea( cfgWorkTable.getValueAsString( AWD::Business_Area ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, dstrBusinessArea );
   if( !dstrBusinessArea.empty() && !cfgWorkTable.getValueAsString( AWD::Business_Area ).stripAll( I_CHAR('\t') ).empty() )
   {
      criteriaList.push_back( criteriaBusinessArea );
   }

   // Add Account Number (ACCT=) Criteria
   BFAwdLookupCriteria criteria1( cfgWorkTable.getValueAsString( AWD::Account_Num ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, strAcctNum );
   criteriaList.push_back( criteria1 );

   //Add the lookup order for CRDA in
   DString lookupOrder = cfgWorkTable.getValueAsString( AWD::LookupOrder ).stripAll( I_CHAR('\t') );

   if (!lookupOrder.empty())
   {
      BFAwdLookupCriteria::Order iLookupOrder = BFAwdLookupCriteria::Order::NO_ORDER;
      
      if (lookupOrder == AWD::Ascending)
      {
         iLookupOrder = BFAwdLookupCriteria::Order::ASCENDING;
      }
      else if (lookupOrder == AWD::Descending)
      {
         iLookupOrder = BFAwdLookupCriteria::Order::DESCENDING;
      }
      
      BFAwdLookupCriteria criteriaLookupOrder ( I_("CRDA"), iLookupOrder);
      criteriaList.push_back( criteriaLookupOrder );
   }

   // Add System ID (SYST=) Criteria; 
   if ( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
   {
      BFAwdLookupCriteria criteriaSystemID( cfgWorkTable.getValueAsString( AWD::System_ID ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, I_( "MAS" ) );
      criteriaList.push_back( criteriaSystemID );
   }
   if ( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
      BFAwdLookupCriteria criteriaSystemID( cfgWorkTable.getValueAsString( AWD::System_ID ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, I_( "COR" ) );	
      criteriaList.push_back( criteriaSystemID );
   }
   try
   {
      if( !pAwdInterface->lookupWork( criteriaList ) )
      {
         DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_LOOKUP_ERROR );
      }
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_EXCEPTION );
   }
}

//******************************************************************************

void BaseAccountDetailsDlg::OnBtnAddCOA() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAddCOA" ) );
   E_COMMANDRETURN eRtn = CMD_OK;

   int accountIndex = m_lvAccounts.GetNextSelection( );
   DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );
   setParameter( ACCOUNT_NUM, strAcctNum );
   SetMessageStatusBar( TXT_LOAD_CAUTIONS_OPTIONS_ATTRIBUTES );
   eRtn = invokeCommand( getParent(), CMD_BPROC_COA, PROC_NO_TYPE, true, NULL );

   SetMessageStatusBar( NULL_STRING );

   switch( eRtn )
   {
      case CMD_OK:
         {
            int sel = m_lvAccounts.GetNextSelection( -1 );

            m_lvAccounts.PopulateList();      
            if( sel >= m_lvAccounts.GetItemCount() )
               sel--;
            m_lvAccounts.SetSelection( sel );
            doRefresh( this, I_( "" ) );
            break;
         }
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
         break;
      default:
         // Display error
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         break;
   };
}

/******************************************************************************

void BaseAccountDetailsDlg::OnItemchangedLvAccounts(NMHDR* pNMHDR, LRESULT* pResult) 
{
   TRACE_METHOD( CLASSNAME, I_( "OnItemchangedLvAccounts" ) );
   SetMessageStatusBar( TXT_LOAD_DETAILS );

   CWaitCursor wait;
   ItemchangedLvAccounts( pNMHDR, pResult );
   SetMessageStatusBar( NULL_STRING );

}*/

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLvAccounts(NMHDR *pNMHDR, LRESULT *pResult)
{
   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );

   m_lvKanjiAddr.SetSelection( lastFocusKanjiAddr, false );



   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::ItemchangedLvAccounts( int index )
{



}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLvEntities( NMHDR *pNMHDR, LRESULT *pResult )
{
   lastFocus = IDC_LV_ENTITIES;
   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLvFunds(NMHDR *pNMHDR, LRESULT *pResult)
{

   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLbAttrib()
{
   lastFocus = IDC_LB_ATTRIB;
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   int caretIndex = m_lbAttributes.GetCaretIndex();
   int idx = m_lbAttributes.GetCurSel( );

   if( idx == LB_ERR && flgTabPressed )
   {
      if( m_lbAttributes.SelectString( -1, lastFocusAttributes ) == LB_ERR && m_lbAttributes.GetCount() != 0 )
         m_lbAttributes.SetCurSel( 0 );
      int newidx = m_lbAttributes.GetCurSel( );
      CString selectedStr;
      if( newidx != LB_ERR )
         m_lbAttributes.GetText( newidx, selectedStr );
      SetStatusBarMessage( selectedStr, 2 );
   }
   flgTabPressed = false;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLbCautions()
{

   lastFocus = IDC_LB_CAUTIONS;
   m_lbAttributes.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   int idx = m_lbCautions.GetCurSel( );
   if( idx == LB_ERR && flgTabPressed )
   {
      if( m_lbCautions.SelectString( -1, lastFocusCautions ) == LB_ERR && m_lbCautions.GetCount() != 0 )
         m_lbCautions.SetCurSel( 0 );
      int newidx = m_lbCautions.GetCurSel( );
      CString selectedStr;
      if( newidx != LB_ERR )
         m_lbCautions.GetText( newidx, selectedStr );
      SetStatusBarMessage( selectedStr, 0 );
   }
   flgTabPressed = false;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLbOptions()
{

   lastFocus = IDC_LB_OPTIONS;
   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   int idx = m_lbOptions.GetCurSel( );

   if( idx == LB_ERR && flgTabPressed )
   {
      if( m_lbOptions.SelectString( -1, lastFocusOptions ) == LB_ERR && m_lbOptions.GetCount() != 0 )
         m_lbOptions.SetCurSel( 0 );
      int newidx = m_lbOptions.GetCurSel( );
      CString selectedStr;
      if( newidx != LB_ERR )
         m_lbOptions.GetText( newidx, selectedStr );
      SetStatusBarMessage( selectedStr, 1 );
   }
   flgTabPressed = false;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLvHistoryTrades(NMHDR *pNMHDR, LRESULT *pResult)
{

   lastFocus = IDC_LV_HISTORY_TRADES;
   m_lbAttributes.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );

	m_lvFunds.SetSelection(lastFocusFunds);
	m_lvEntities.SetSelection(lastFocusEntities);

   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   int idx = m_lvTransactions.GetNextItem( -1, LVNI_SELECTED );
   if( idx == -1 )
      m_lvTransactions.SetSelection( lastFocusTransactions );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::SetfocusLvEntitiesIds(NMHDR *pNMHDR, LRESULT *pResult)
{

   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   int idx = m_lvEntitiesIds.GetNextItem( -1, LVNI_SELECTED );
   if( idx == -1 )
      m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds );
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::RbTransHistory()
{
   if( TranPendingState == 0 )
      m_lvTransactions.SaveSettings( CLASSNAME, LV_PENDINGDETAILS );
   int index = m_lvFunds.GetNextSelection( );
   int state = m_ckbAllFunds.GetCheck();
   if( index != -1 && state != 1 )
   {
      DString* key = (DString*)m_lvFunds.GetItemData( index );
      getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key ); 

      DString temp;
      getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, temp, false );
      SetDlgItemText( IDC_CURRENT_FUND, temp.c_str() );
   }

   // m_lvTransactions.DeleteAllItems();
   //m_lvTransactions.DeleteAllColumns();
   if( TranPendingState == 0 )
      m_lvTransactions.LoadSettings( CLASSNAME, LV_HISTORYDETAILS );
   SetTransHeading();
   fillTransactionsList( );
   TranPendingState = 1;
   m_lbOptions.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
}

//******************************************************************************

void BaseAccountDetailsDlg::RbPendingTrades()
{
   if( TranPendingState == 1 )
      m_lvTransactions.SaveSettings( CLASSNAME, LV_HISTORYDETAILS );

   CString allFunds;
   allFunds.LoadString( TXT_ALL );
   SetDlgItemText( IDC_CURRENT_FUND, ( LPCTSTR ) allFunds );

   m_lvTransactions.DeleteAllItems();
   m_lvTransactions.DeleteAllColumns();
   if( TranPendingState == 1 )
      m_lvTransactions.LoadSettings( CLASSNAME, LV_PENDINGDETAILS );
   SetPendingHeading();
   fillPendingTradesList();
   TranPendingState = 0;
   m_lbOptions.SetCurSel( -1 );
   m_lbCautions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
}

//******************************************************************************

void BaseAccountDetailsDlg::BtnAdminDates()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("BtnAdminDates" ) );

   m_lbCautions.SetCurSel( -1 );
   m_lbOptions.SetCurSel( -1 );
   m_lbAttributes.SetCurSel( -1 );
   m_lvTransactions.SetSelection( lastFocusTransactions, false );
   m_lvEntitiesIds.SetSelection( lastFocusEntitiesIds, false );
   ShowAdminDates( IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSelchangeLbAttrib() 
{
   // TODO: Add your control notification handler code here

   int ind = m_lbAttributes.GetCurSel( );
   if( ind == LB_ERR )
      return;

   CString selectedStr;
   m_lbAttributes.GetText( ind, selectedStr );
   SetMessageStatusBar( NULL_STRING );
   SetStatusBarMessage( selectedStr, 2 );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSelchangeLbCautions() 
{
   // TODO: Add your control notification handler code here

   int ind = m_lbCautions.GetCurSel( );
   if( ind == LB_ERR )
      return;

   CString selectedStr;
   m_lbCautions.GetText( ind, selectedStr );
   SetMessageStatusBar( NULL_STRING );
   SetStatusBarMessage( selectedStr ,0 );
}

//******************************************************************************

void BaseAccountDetailsDlg::OnSelchangeLbOptions() 
{
   // TODO: Add your control notification handler code here

   int ind = m_lbOptions.GetCurSel( );
   if( ind == LB_ERR )
      return;

   CString selectedStr;
   m_lbOptions.GetText( ind, selectedStr );
   SetMessageStatusBar( NULL_STRING );
   SetStatusBarMessage( selectedStr, 1 );
}

//******************************************************************************
void BaseAccountDetailsDlg::SetStatusBarMessage( CString& selStr, int code )
{
   CString systematicsStr, bankInstr, allocationsStr, swpStr, systTransfStr,riflifStr;

   CString classificationStr, chequeInformation, strACB, distrOptions, demographicsStr, histMktValStr;
   CString distributionStr, shareholderStr, historicalAccInfoStr, accInfoStr, entityStr, addressStr, DemographicsStr;

   CString certificatesStr, pendingTrade, remarksStr;
   CString stopPurchaseStr, stopRedeemStr, stopTransOutStr, stopTransInStr, unsettledTranStr, freeUnitsStr;
   CString respTransactionsStr, respInfoStr, acctSplitComm, hypoRedemption, cstrForeignContent;
   CString cstrAccountReview, cstrPensionInfo, cstrAMS, cstrManagementFee, cstrTFSAContributionInfo;
   CString cstrStopAMSRebalancing, cstrAcctSettleLoc, cstrFundSponsorAgreement, cstrFundBroker, holdDivPymtStr;

   CString attrEStatement, cstrProtContract, cstrTrailerFee;
   CString cashSweepInstr, maturityInstr;
   
   attrEStatement.LoadString( ROW_DETAILS_ATTRIBUTES_ESTATEMENT );

   cstrAcctSettleLoc.LoadString( TXT_SETTLEMENT_LOCATION );
	cstrFundSponsorAgreement.LoadString( TXT_LOAD_SHR_FUND_SPONSOR_AGREEMENT );
	cstrFundBroker.LoadString( TXT_LOAD_SHR_FUND_BROKER );
   systematicsStr.LoadString( ROW_DETAILS_OPTIONS_PAC ); 
   swpStr.LoadString( ROW_DETAILS_OPTIONS_SWP );   
   bankInstr.LoadString( ROW_DETAILS_OPTIONS_BANKING );  
   allocationsStr.LoadString( ROW_DETAILS_OPTIONS_ALLOCATIONS );
   systTransfStr.LoadString( ROW_DETAILS_OPTIONS_SYSTEMATIC_TRANSFER );
   acctSplitComm.LoadString (ROW_DETAILS_OPTIONS_COMMISSIONABLE_REPS);
   cstrAMS.LoadString( ROW_DETAILS_OPTIONS_AMS );
   cstrProtContract.LoadString ( ROW_DETAILS_OPTIONS_PROT_CONTRACTS );

   classificationStr.LoadString( ROW_DETAILS_ATTRIBUTES_INT_ACCRUED );  
   chequeInformation.LoadString( ROW_DETAILS_ATTRIBUTES_CHEQUE_INFORMATION ); 
   strACB.LoadString( ROW_DETAILS_ATTRIBUTES_ACB ); 
   distrOptions.LoadString( ROW_DETAILS_ATTRIBUTES_DISTR_OPTIONS );  
   DemographicsStr.LoadString( ROW_DETAILS_ATTRIBUTES_DEMOGRAPHICS );   
   histMktValStr.LoadString( ROW_DETAILS_ATTRIBUTES_HIST_MKT_VALUE );
   shareholderStr.LoadString( ROW_DETAILS_ATTRIBUTES_SHAREHOLDER );
   riflifStr.LoadString(ROW_RRIF_LIF_INFO);

   historicalAccInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_HISTORICAL_ACCOUNT_INFORMATION );
   accInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNT_INFORMATION );
   entityStr.LoadString( ROW_DETAILS_ATTRIBUTES_ENTITY );
   addressStr.LoadString( ROW_DETAILS_ATTRIBUTES_ADDR_BOOK_MAIL_ASSIGN );
   freeUnitsStr.LoadString( ROW_DETAILS_ATTRIBUTES_FREE_UNITS );

   certificatesStr.LoadString( ROW_DETAILS_CAUTIONS_CERTIFICATES_ISSUED ); 
   pendingTrade.LoadString( ROW_DETAILS_CAUTIONS_PENDING_TRADE ); 
   remarksStr.LoadString( ROW_DETAILS_CAUTIONS_REMARKS );   
   stopPurchaseStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_PURCHASE ); 
   stopRedeemStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_REDEEM );  
   stopTransOutStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_OUT );   
   stopTransInStr.LoadString( ROW_DETAILS_CAUTIONS_STOP_TRANS_IN );  
   unsettledTranStr.LoadString( ROW_DETAILS_CAUTIONS_UNSETTLED_TRANSACTION ); 
   respInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_RESPINFO );
   respTransactionsStr.LoadString( ROW_DETAILS_ATTRIBUTES_RESPTRANSACTIONS );
   hypoRedemption.LoadString ( ROW_DETAILS_ATTRIBUTE_HYPOTHETICAL_REDEMPTION );
   holdDivPymtStr.LoadString( ROW_DETAILS_CAUTIONS_HOLD_DIV_PAYMENT );
	cstrForeignContent.LoadString( ROW_DETAILS_ATTRIBUTES_FOREIGN_CONTENT_WORKSHEET );
   cstrAccountReview.LoadString( ROW_DETAILS_ATTRIBUTES_ACCOUNTREVIEW );
   cstrPensionInfo.LoadString( ROW_DETAILS_ATTRIBUTES_PENSION_INFO );
   cstrManagementFee.LoadString( ROW_DETAILS_ATTRIBUTES_MANAGEMENT_FEE );
   cstrStopAMSRebalancing.LoadString( IDS_STP_AMSREBALANCING );
   cstrStopAMSRebalancing.TrimLeft();
   cstrTFSAContributionInfo.LoadString ( ROW_DETAILS_TFSA_CONTRIBUTION_INFO );  
   cstrTrailerFee.LoadString( ROW_DETAILS_ATTRIBUTES_TRAILERFEE_SETUP );

   cashSweepInstr.LoadString( ROW_DETAILS_OPTIONS_CASHSWEEP );  
   maturityInstr.LoadString( ROW_DETAILS_OPTIONS_MATURITY );  


   CString guaranteeInfoStr,
      contractInfoStr, 
      cstrTaxExemptAuthorization;

   //Tax Exempt Authorization
   cstrTaxExemptAuthorization.LoadString(ROW_DETAILS_ATTRIBUTES_TAX_EXEMPT_AUTHORIZATION);

   // For the specifical use of the Canada market

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA ) 
   {
      guaranteeInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_GUARANTEE );
      contractInfoStr.LoadString( ROW_DETAILS_ATTRIBUTES_CONTRACT );
   }
   
   DString dstrTaxType;
   CString asPensionPlanStr;
   /*DString dstrTaxType;*/
   getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, dstrTaxType, false );
   dstrTaxType.strip();

   if( dstrTaxType == I_( "P" ) )
   {
      asPensionPlanStr.LoadString( ROW_DETAILS_ATTRIBUTES_AS_PENSION );
   }

   CString YTDStr, ESOPStr;
   YTDStr.LoadString(ROW_DETAILS_ATTRIBUTES_YTDCONTRIBUTIONS);
   ESOPStr.LoadString(ROW_DETAILS_ATTRIBUTES_ESOPINFO);

   // Shareholder family
   CString sharholderGuiFamilyStr, cstrAcctCateg;
   sharholderGuiFamilyStr.LoadString( ROW_DETAILS_OPTIONS_SHR_FAMILY );
   cstrAcctCateg.LoadString( ROW_DETAILS_OPTIONS_ACCT_CATEGORY );

   CString cstrGovtFilingAmendment;
   cstrGovtFilingAmendment.LoadString ( ROW_DETAILS_OPTIONS_RESP_GOVT_FILING_AMENDMENT );

   switch( code )
   {
      case 0: //Cautions
         if( selStr == certificatesStr )
            SetMessageStatusBar( TXT_BROWSE_CERTIFICATE );
         else if( selStr == pendingTrade )
            SetMessageStatusBar( TXT_BROWSE_TRANSACTIONS_SCREEN );
         else if( selStr == remarksStr )
            SetMessageStatusBar( TXT_BROWSE_REMARKS_SCREEN );
         else if( selStr == stopPurchaseStr )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == stopRedeemStr )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == stopTransOutStr )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == stopTransInStr )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == cstrStopAMSRebalancing )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == unsettledTranStr )
            SetMessageStatusBar( TXT_BROWSE_TRANSACTIONS_SCREEN );
         break;
      case 1: //Options
         if( selStr == systematicsStr )
            SetMessageStatusBar( TXT_BROWSE_SYSTEMATICS_SCREEN );
         else if( selStr == swpStr )
            SetMessageStatusBar( TXT_BROWSE_SYSTEMATICS_SCREEN );
         else if( selStr == bankInstr )
            SetMessageStatusBar( TXT_BROWSE_BANK );
         else if( selStr == allocationsStr )
            SetMessageStatusBar( TXT_BROWSE_ALLOCATION );
         else if( selStr == systTransfStr )
            SetMessageStatusBar( TXT_BROWSE_AUTO_TRANSF );
         else if( selStr == acctSplitComm )
            SetMessageStatusBar( TXT_BROWSE_COMMISSIONABLE_REPS );
         else if( selStr == cstrAMS )
            SetMessageStatusBar( TXT_BROWSE_AMS );
         else if( selStr == sharholderGuiFamilyStr)
            SetMessageStatusBar( TXT_SHR_GUI_SHR_FAMILY );         
         else if ( selStr == cstrProtContract )
            SetMessageStatusBar( TXT_BROWSE_PROT_CONTRACT );
         else if ( selStr == cstrAcctCateg )
            SetMessageStatusBar( TXT_BROWSE_ACCT_CATEGORY );
         else if ( selStr == cstrAcctSettleLoc )
            SetMessageStatusBar( TXT_SETTLEMENT_LOCATION );
         else if ( selStr == cstrFundSponsorAgreement )
            SetMessageStatusBar( TXT_LOAD_SHR_FUND_SPONSOR_AGREEMENT );
         else if ( selStr == cstrFundBroker )
            SetMessageStatusBar( TXT_LOAD_SHR_FUND_BROKER );
         else if ( selStr == cstrGovtFilingAmendment )
            SetMessageStatusBar( TXT_LOAD_RESP_GOVT_FILING_AMENDMENT );
         break;
      case 2: //Attributes
         if( selStr == classificationStr )
            SetMessageStatusBar( TXT_BROWSE_INTEREST_ACCR_SCREEN );
         else if( selStr == chequeInformation )
            SetMessageStatusBar( TXT_BROWSE_CHEQUE );
         else if( selStr == strACB )
            SetMessageStatusBar( TXT_BROWSE_ACB_SCREEN );
         else if( selStr == distrOptions )
            SetMessageStatusBar( TXT_BROWSE_DISTRIBUTIONS_SCREEN );
         else if( selStr == DemographicsStr )
            SetMessageStatusBar( TXT_BROWSE_DEMOGRAPHICS_SCREEN );
         else if( selStr == histMktValStr )
            SetMessageStatusBar( TXT_BROWSE_HIS_MARKET_V );
         else if( selStr == shareholderStr )
            SetMessageStatusBar( TXT_BROWSE_BASIC_SHAREHOLDER );
         else if( selStr == historicalAccInfoStr )
            SetMessageStatusBar( TXT_BROWSE_HISTORICAL_ACC_INFO );
         else if( selStr == accInfoStr )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNT_INFO );
         else if( selStr == entityStr )
            SetMessageStatusBar( TXT_BROWSE_ENTITY_SCREEN );
         else if( selStr == addressStr )
            SetMessageStatusBar( TXT_BROWSE_ADDRESS_BOOK );
         else if( selStr == freeUnitsStr )
            SetMessageStatusBar( TXT_BROWSE_FREE_UNITS );
         else if( selStr == guaranteeInfoStr )
            SetMessageStatusBar( TXT_BROWSE_GUARANTEE );
         else if( selStr == contractInfoStr )
            SetMessageStatusBar( TXT_BROWSE_CONTRACT );
         else if( selStr == respInfoStr )
            SetMessageStatusBar( TXT_BROWSE_RESPINFO );
         else if( selStr == respTransactionsStr )
            SetMessageStatusBar( TXT_BROWSE_RESPTRANSACTIONS );
         else if( selStr == asPensionPlanStr )
            SetMessageStatusBar( TXT_BROWSE_AS_PENSION );
         else if( selStr == YTDStr )
            SetMessageStatusBar( TXT_BROWSE_YTD );
         else if( selStr == ESOPStr )
            SetMessageStatusBar( TXT_BROWSE_ESOP );
         else if( selStr == hypoRedemption )
            SetMessageStatusBar( TXT_BROWSE_HYPO_REDEMPTION );
			else if ( selStr == cstrForeignContent )
				SetMessageStatusBar( TXT_BROWSE_FOREIGN_CONTENT_WORKSHEET );
         else if( selStr == cstrAccountReview )
            SetMessageStatusBar( TXT_BROWSE_ACCOUNTREVIEW );
         else if( selStr == cstrPensionInfo )
            SetMessageStatusBar( TXT_BROWSE_PENSION_INFO );
         else if( selStr == attrEStatement )
            SetMessageStatusBar( TXT_BROWSE_ESTATEMENT );
			else if( selStr == cstrTaxExemptAuthorization )
            SetMessageStatusBar( TXT_BROWSE_TAXEXEMPT );
			else if( selStr == cstrManagementFee )
			SetMessageStatusBar( TXT_BROWSE_ACCOUNT_LEVEL_FEE );
			else if (selStr == cstrTFSAContributionInfo )
			SetMessageStatusBar( TXT_BROWSE_TFSA);
         break;

      default:
         return;
   }
}

//******************************************************************************

void BaseAccountDetailsDlg::OnAllFunds() 
{
   // TODO: Add your control notification handler code here
   SetMessageStatusBar( TXT_LOAD_DETAILS );

   CWaitCursor wait;
   int state = m_ckbAllFunds.GetCheck();
   if( state == 1 )
   {
      CString allFunds;
      allFunds.LoadString( TXT_ALL );
      SetDlgItemText( IDC_CURRENT_FUND, ( LPCTSTR ) allFunds );
   }
   else
   {
      int index = m_lvFunds.GetNextSelection( );
      if( index != -1 )
      {
         DString* key = (DString*)m_lvFunds.GetItemData( index );
         getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key ); 

         DString temp;
         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, temp, false );

         SetDlgItemText( IDC_CURRENT_FUND, temp.c_str() );
      }
   }

   if( state == 1 )
      //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "All" ) );
      getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("Y"),false);
   else
   {
      //getParent()->setCurrentListItem( this, ACCDETLIT::TRANSACTIONS_LIST, I_( "FundMode" ) ); // The key doesn't matter, this is used to set the right transaction list ptr
      getParent()->setField(this, ACCDETLIT::FULL_TRANS_LIST, I_("N"),false);
   }
   fillTransactionsList();
   SetMessageStatusBar( NULL_STRING );

}

//******************************************************************************

bool BaseAccountDetailsDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{

   DString strMarket = DSTCommonFunctions::getMarket();

   if( lSubstituteId == ifds::AccDetailsEntityListHeading.getId() )
   {
      if( ColumnKey == I_( "FirstName" ) )
      {
         DString temp1, temp2;

         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, temp1 );
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, temp2 );

         if( strMarket == MARKET_IDS::JAPAN )
            getDisplayName( IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, strOut, true );
         else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            getDisplayName( IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, strOut, false );

         return(true);
      }
      else if( ColumnKey == I_( "BirthFirstName" ) )
      {
         DString temp1, temp2;

         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, temp1 );
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthLastName, temp2 );

         if( strMarket == MARKET_IDS::JAPAN )
            getDisplayName( IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, ifds::BirthLastName, strOut, true );
         else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            getDisplayName( IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, ifds::BirthLastName, strOut, false );

         return(true);
      }
   }
   else if( lSubstituteId == ifds::AccDetailsTransHeadingSet.getId() )
   {
      DString str, str1;
      if( ColumnKey == I_( "rxFundCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         CString strTab;
         strTab.LoadString( TXT_CASH );
         DString dump( ( LPCTSTR ) strTab );
         dump.upperCase();
         if( str == I_( "CASH" ) || str == NULL_STRING )
         {
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::TfrFund, str );
            str.stripAll().upperCase();
         }
         strOut = str;

         return(true);
      }
      else if( ColumnKey == I_( "rxClassCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         CString strTab;
         strTab.LoadString( TXT_CASH );
         DString dump( ( LPCTSTR ) strTab );
         dump.upperCase();
         if( str == I_( "CASH" ) || str == NULL_STRING )
         {
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::TfrClass, str );
            str.stripAll().upperCase();
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxClassCode, str );
            str.stripAll().upperCase();
         }

         strOut = str;

         return(true);
      }

      else if( ColumnKey == I_( "Baycom" ) )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxFundCode, dstrFundCode );
         dstrFundCode.stripAll().upperCase();
         if( dstrFundCode != I_( "CASH" ) && dstrFundCode != NULL_STRING )
         {
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxClassCode, dstrClassCode );
            dstrClassCode.strip().upperCase();
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, strOut );
            return(true);
         }
         else
         {
            DString dstrTfrFund, dstrTfrClass;
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::TfrFund, dstrTfrFund );
            dstrTfrFund.stripAll().upperCase();
            getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::TfrClass, dstrTfrClass );
            dstrTfrClass.stripAll().upperCase();
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrTfrFund, dstrTfrClass, strOut );
            return(true);
         }
      }

      else if( ColumnKey == I_( "UnitBalance" ) )
      {
         CString strTab;
         DString dstrFundCode, dstrSettled, dstrCancelled, dstrReversal, dstrSeqNum, str;
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::rxFundCode, dstrFundCode );
         dstrFundCode.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::Settled, dstrSettled, false );
         dstrSettled.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::Cancelled, dstrCancelled, false );
         dstrCancelled.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::Reversal, dstrReversal, false );
         dstrReversal.stripAll().upperCase();

         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::SeqNum, dstrSeqNum, false );
         dstrSeqNum.stripAll().stripLeading('0');
         // Default UnitBalance
         getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::UnitBalance, str );
         str.stripAll();

         if( dstrFundCode == I_("CASH") )
         {
            strTab.LoadString( TXT_CASH );
            str = ( LPCTSTR ) strTab;
         }
         else
         {
            if( dstrSeqNum.empty() )
            {
               if( dstrCancelled == YES || dstrReversal == YES )
               {
                  strTab.LoadString( TXT_CANCELED );
               }
               else if( dstrSettled == YES )
               {
                  strTab.LoadString( TXT_SETTLED );
               }
               else
               {
                  strTab.LoadString( TXT_UNSETTLED );
               }
               str = ( LPCTSTR ) strTab;
            }
            else
            {
               getParent()->getField( this, IFASTBP_PROC::TRANSACTIONS_LIST, ifds::UnitBalance, str );
            }

         }
         strOut = str;

         return(true);
      }
   }
   else if( lSubstituteId == ifds::AccDetailsPendingHeadingSet.getId() )
   {
      DString str;
      if( ColumnKey == I_( "Units" ) || ColumnKey == I_( "Amount" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::AmountType, str );
         str.strip();

         const DString *key = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::PENDING_TRADES_LIST );

         if( str == STRING_U )
         {
            str = *key;
            getParent()->getField( this, ACCDETLIT::AMOUNT_UNITS, str );
            str.strip();
            if( ColumnKey == I_( "Units" ) )
               strOut = str;
            else
               strOut = EMPTY_STRING;
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::Amount, str );
            str.strip();
            if( ColumnKey == I_( "Units" ) )
               strOut = EMPTY_STRING;
            else
               strOut = str;
         }

         return(true);
      }
      else if( ColumnKey == I_( "rxFundCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();

         if( str == NULL_STRING && AreThereAllocationInThisPending() )
         {
            CString tmp;
            tmp.LoadString(TXT_SEE_ALLOCATION);
            strOut.assign( tmp );
         }
         else
            strOut = str;

         return(true);
      }
      else if( ColumnKey == I_( "rxClassCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxClassCode, str );
         str.stripAll().upperCase();
         strOut = str;

         return(true);
      }
      else if( ColumnKey == I_( "Baycom" ) )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxFundCode, dstrFundCode );
         dstrFundCode.stripAll().upperCase();
         if( dstrFundCode != NULL_STRING )
         {
            getParent()->getField( this, IFASTBP_PROC::PENDING_TRADES_LIST, ifds::rxClassCode, dstrClassCode );
            dstrClassCode.strip().upperCase();
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, strOut );
            return(true);
         }
      }
   }
   else if( lSubstituteId == ifds::AccDetailsFundsListHeading.getId() || lSubstituteId == ifds::AccDetailsFundsCGListHeading.getId())
   {
      if( ColumnKey == I_( "Currency" ) )
      {
         DString str;
         const DString *key;

         if( *( key = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FUNDS_LIST ) ) != EMPTY_STRING )
         {
            str = *key;
            getParent()->getField( this, ACCDETLIT::FUND_CURRENCY, str );
            str.strip();
            strOut = str;
         }

         return(true);
      }

      else if( ColumnKey == I_( "Baycom" ) )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strOut );
         return(true);
      }
   }

   return(false);
}

//******************************************************************************

void BaseAccountDetailsDlg::OnClickLvAccounts(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: Add your control notification handler code here
   //loadRRIFString();
   *pResult = 0;
}

//******************************************************************************

void BaseAccountDetailsDlg::loadRRIFString()
{
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      CListBox *pAttributesListBox = static_cast < CListBox* > ( GetDlgItem( IDC_LB_ATTRIB ) );
      CString lbStrings;
      lbStrings.LoadString( ROW_RRIF_LIF_INFO );

      DString dstrTaxType, dstrPlanType, dstrInfo, dstrAlloc ;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::TaxType, dstrTaxType, false );
      dstrTaxType.stripAll();

      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::PlanType, dstrPlanType );
      dstrPlanType.stripAll().upperCase();

      getParent()->getField( this, ACCDETLIT::RIF_LIF_LRIF_INFO, dstrInfo, false );
      dstrInfo.strip();

      getParent()->getField( this, ACCDETLIT::RIF_LIF_LRIF_ALLOC_INFO, dstrAlloc, false );
      dstrAlloc.strip();

      int idx = 0;
      if( ( dstrInfo == Y_STRING ) && ( dstrAlloc == Y_STRING) && 
          ( dstrPlanType == I_("RIF") ) && ( dstrTaxType != I_( "5" ) ) )
      {
         idx = pAttributesListBox->FindString( -1, lbStrings ) ;
         if( idx <= 0 )
            idx = pAttributesListBox->AddString( lbStrings);
      }
      else
      {
         idx = pAttributesListBox->FindString( -1, lbStrings ) ;
         if( idx > 0 )
            pAttributesListBox->DeleteString( idx );
      }	  
   }
}

//******************************************************************************

bool BaseAccountDetailsDlg::doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage )
{
   DString dstrMessage = szMessage;
   bool retVal = false;
   if( dstrMessage == I_("GetYearMonthStrings") )
   {
      CString strYearString, strMonthsString;
      strYearString.LoadString(TXT_YEARS);
      strMonthsString.LoadString(TXT_MONTHS);
      setParameter(I_("YEARS"), DString(strYearString));
      setParameter(I_("MONTHS"), DString(strMonthsString));
      retVal = true;
   }
   return(retVal);
}

//******************************************************************************
bool BaseAccountDetailsDlg::canAddNewAccountOrClose( )
{
   if( getParent()->workSessionHasUpdates() )
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);
      if( discardDlg.DoModal() == IDCANCEL )
         return(false);
   }
   // close all child screens
   GenericInterfaceContainer *pGIContainer = getGIContainer();
   pGIContainer->destroyGUIChildren( this );

   return(true);
}

//******************************************************************************
BOOL BaseAccountDetailsDlg::DestroyWindow() 
{
   if( canAddNewAccountOrClose() )
      return(BaseMainDlg::DestroyWindow());
   else
      return(FALSE);
}
//******************************************************************************
LRESULT BaseAccountDetailsDlg::OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier)
{
   TRACE_METHOD( CLASSNAME, I_( "OnListViewItemChanged" ) );

   POSITION pos = NULL;
   int nCurrentSelection = -1;
   if( ListIdentifier == IDC_LV_ACCOUNTS )
   {
      pos = m_lvAccounts.GetFirstSelectedItemPosition();
      if( pos )
         nCurrentSelection = m_lvAccounts.GetNextSelectedItem(pos);
      if( nCurrentSelection != (int)PreviousSelection )
         return(0);
      CWaitCursor wait;
      SetMessageStatusBar( TXT_LOAD_DETAILS );
      ItemchangedLvAccounts( nCurrentSelection );
      SetMessageStatusBar( NULL_STRING );
   }
   else if( ListIdentifier == IDC_LV_ENTITIES )
   {
      pos = m_lvEntities.GetFirstSelectedItemPosition();
      if( pos )
         nCurrentSelection = m_lvEntities.GetNextSelectedItem(pos);
      if( nCurrentSelection != (int)PreviousSelection )
         return(0);
      CWaitCursor wait;
      SetMessageStatusBar( TXT_LOAD_DETAILS );  
      DString* key = (DString*)m_lvEntities.GetItemData( nCurrentSelection );
      getParent()->setCurrentListItem( this, IFASTBP_PROC::ENTITY_LIST, *key );
      fillEntitiesIdsList( );
      SetMessageStatusBar( NULL_STRING );
   }
   else if( ListIdentifier == IDC_LV_FUNDS )
   {
      pos = m_lvFunds.GetFirstSelectedItemPosition();
      if( pos )
         nCurrentSelection = m_lvFunds.GetNextSelectedItem(pos);
      if( nCurrentSelection != (int)PreviousSelection )
         return(0);
      CWaitCursor wait;
      SetMessageStatusBar( TXT_LOAD_DETAILS );  

      int state = m_ckbAllFunds.GetCheck();

      DString* key = (DString*)m_lvFunds.GetItemData( nCurrentSelection );

      getParent()->setCurrentListItem( this, IFASTBP_PROC::FUNDS_LIST, *key ); 

      CButton *pRadioButton2 = static_cast < CButton* > ( GetDlgItem( IDC_RB_PENDING_TRADES ) );
      int iCheck = pRadioButton2->GetCheck( );
      DString temp;
      getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::rxFundCode, temp, false );
      if( iCheck == 1 || state == 1 )
      {
         CString allFunds;
         allFunds.LoadString( TXT_ALL );
         SetDlgItemText( IDC_CURRENT_FUND, ( LPCTSTR ) allFunds );
      }
      else
         SetDlgItemText( IDC_CURRENT_FUND, temp.c_str() );

      if( state != 1 )
         fillTransactionsList( );
      SetMessageStatusBar( NULL_STRING );

      DString dstrFOFFund;
      getParent()->getField( this, IFASTBP_PROC::FUNDS_LIST, ifds::FOFFund, dstrFOFFund, false );
      if ( dstrFOFFund.strip() == YES )
         GetDlgItem(IDC_BTN_FOF)->EnableWindow( true );
      else
         GetDlgItem(IDC_BTN_FOF)->EnableWindow( false );


   }
   return(0);
}

//******************************************************************************
void BaseAccountDetailsDlg::OnOK()
{ 
   if( GetFocus() )
   {
      long currFocus;
      currFocus = GetFocus()->GetDlgCtrlID();
      if( currFocus == IDC_LB_CAUTIONS )
         OnDblclkLbCautions();
      else if( currFocus == IDC_LB_ATTRIB )
         OnDblclkLbAttrib();
      else if( currFocus == IDC_LB_OPTIONS )
         OnDblclkLbOptions();

   }
//   BaseMainDlg::DestroyWindow();
}

//******************************************************************************
void BaseAccountDetailsDlg::OnKillfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult) 
{
  // TODO: Add your control notification handler code here

   int idx = m_lvFunds.GetNextItem( -1, LVNI_SELECTED );
   if( idx != -1 )
   {
      lastFocusFunds = idx;
   }
   *pResult = 0;
}

//******************************************************************************
void BaseAccountDetailsDlg::OnActiveFunds()
{

   int state = m_ckbActiveFunds.GetCheck();

	DString strActiveOnly;

	if( state == 1 )
      strActiveOnly = YES ;
   else
      strActiveOnly = NO ;
	
   getParent()->setField(this, ifds::ActiveOnly, strActiveOnly, false);

	m_lvFunds.PopulateList();
   
	SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void BaseAccountDetailsDlg::OnBtnCloneAcct ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnCloneAcct "));
   
   CWaitCursor wait;   
   E_COMMANDRETURN eRtn = CMD_OK;
   DString accountNum, 
      lastName, 
      firstName;
   
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, lastName);
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, firstName);
   getParent()->getField (this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum);
   setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   CString cstrCloneAcctNum,cstrName;
   cstrCloneAcctNum.LoadString(TXT_CLONE_ACCT_ACCT_NUM);
   DString screenTitle = DString(cstrCloneAcctNum) + accountNum;
   cstrName.LoadString(TXT_NAME_TXT);
   screenTitle += DString(cstrName) + lastName + I_(";") + firstName;

   DString urlParamsIDI;

   addIDITagValue (urlParamsIDI, I_("AccountNum"), accountNum);
   addIDITagValue (urlParamsIDI, I_("screen"), I_("CloneAccount"));
   setParameter (I_("UrlParams"), urlParamsIDI);
   setParameter( I_("BrowserTitle"), screenTitle );
   setParameter (I_("from_screen"), I_("AccountDetailsDlg"));
   SetMessageStatusBar (TXT_CLONE_ACCOUNT);

   eRtn = invokeCommand (getParent(), CMD_BPROC_CLONE_ACCOUNT_BROWSER, PROC_NO_TYPE, true, NULL);
   wait.Restore();
   
   bool flg_refresh = false;
//only steel the message if the process got executed
   if (eRtn == CMD_OK || eRtn == CMD_MODELESS_INPROCESS)
   {
      MSG msg;
      PeekMessage (&msg, GetMainView()->m_hWnd, UM_ENDCURRENTSESSION , UM_ENDCURRENTSESSION , PM_NOREMOVE);
      flg_refresh = !(msg.message == UM_ENDCURRENTSESSION && msg.wParam == IDC_BTN_END);
#if 0
   //put it back
      GetMainView()->PostMessage (msg.message, msg.wParam, msg.lParam);
#endif
   }

   SetMessageStatusBar (NULL_STRING);
   switch (eRtn)
   {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
         { 
            if (flg_refresh)
            {
               DString newAccKey, 
                  key;
               int count = 0;

               getParent()->modelessSetFocus (this);
               fillAccountList ();
               getParent()->getField (this, ACCDETLIT::NEW_ACCOUNT_NUMBER, newAccKey);
               for( key = getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
                    !key.empty() && key != newAccKey;
                    key = getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST ), count++ )
                  ;//empty body
               if (count < m_lvAccounts.GetItemCount())
               {
                  m_lvAccounts.SetSelection (count);
//open-up the RRIF screen if this is a new account 
	               MFAccount *pMFAccount (NULL);
	               DString accountNum,
                     shrNum;
	               getParent()->getField (this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, accountNum);
                  getParent()->getField (this, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::ShrNum, shrNum);
	               accountNum.strip();
	               accountNum.stripLeading ('0');
	               DSTCWorkSession *dstcWorkSession = 
                        dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	               if ( dstcWorkSession->getMFAccount (getDataGroupId(), accountNum, pMFAccount) <= WARNING &&
                       pMFAccount)
	               {
                     if (pMFAccount->isRRIFAccount (getDataGroupId()))
                     {
                        DString lastName,
                           firstName;

                        getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, lastName);
                        getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, firstName);
                        setParameter (RRIF_LIF_LRIF::LAST_NAME_FIELD, lastName);
                        setParameter (RRIF_LIF_LRIF::FIRST_NAME_FIELD, firstName);
                        setParameter (RRIF_LIF_LRIF::ACCOUNT_NUMBER_FIELD, accountNum);
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
               else
               {
                  m_lvAccounts.SetSelection (0);
               }
            }
            break;
         }
      case CMD_CANCEL:
         break;
      default:
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
         break;
   }
}

//******************************************************************************
void BaseAccountDetailsDlg::OnBtnFundOfFunds ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnFundOfFunds"));
   
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      // Pass transaction type (ie. RO, RB) to handle F4
      setParameter( AMS_Para::FROM_SCR, AMS_Para::AMS_DETAIL );
      setParameter( AMS_Para::AMS_CODE, NULL_STRING );
      setParameter( AMS_Para::AMS_TYPE, I_("FOF") );

      eRtn = invokeCommand( getParent(), CMD_BPROC_AMS_GLOBAL, PROC_SUPPORT, true, NULL );
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
LRESULT BaseAccountDetailsDlg::OnOpenAlertMessageBox( WPARAM wWordParam, LPARAM lLongParam )
{
   TRACE_METHOD( CLASSNAME, I_( "OnOpenAlertMessageBox" ) );

   CString cstrUnclaimedAlertRetMail;
   CString cstrUnclaimedAlertStlChq;
   CString cstrUncliamedAlertBoth;
   //P0178584_FN01_NewPopUpMSG
   CString cstrUnclaimedAlertRmtChq;
   CString cstrUnclaimedAlertUnclmStatus;
   CString cstrUnclaimedAlertRmtChqNote;
   // IWT
   CString cstrTinNotExists;   

   cstrUnclaimedAlertRmtChq.LoadString(IDS_UNCLAIMED_ALERT_REMITTED_CHQ);
   cstrUnclaimedAlertUnclmStatus.LoadString(IDS_UNCLAIMED_ALERT_UNCLAIMED_STATUS);
   cstrUnclaimedAlertRmtChqNote.LoadString(IDS_UNCLAIMED_ALERT_REMITTED_CHQ_NOTE);
   //End - P0178584_FN01_NewPopUpMSG
   cstrUnclaimedAlertRetMail.LoadString( IDS_UNCLAIMED_ALERT_RETMAIL );
   cstrUnclaimedAlertStlChq.LoadString( IDS_UNCLAIMED_ALERT_STLCHQ );
   cstrUncliamedAlertBoth.LoadString( IDS_UNCLAIMED_ALERT_BOTH ); 

   cstrTinNotExists.LoadString(TXT_TIN_NOT_EXISTS);

   if ( lLongParam )
   {
      CString cstrAlertMessage;

      switch ( lLongParam )
      {
		 //P0178584_FN01_NewPopUpMSG
		 case 1: //R1.0.2, R1.1, R1.2, R4.1, R5.0
			 {
				cstrAlertMessage = cstrUnclaimedAlertStlChq ;
			 }
		     break;
		 case 2: //R2.0
			 {
				cstrAlertMessage = cstrUnclaimedAlertUnclmStatus;
			 }
		     break;
		 case 3: //R2.1, R2.2
			 {
				cstrAlertMessage = cstrUnclaimedAlertRetMail;
			 }
		     break;
		 case 4: // R3.0, R3.3
			 {
				cstrAlertMessage = cstrUncliamedAlertBoth;
			 }
		     break;
		 case 5:
			 {
				cstrAlertMessage = cstrUnclaimedAlertRmtChq + _T("\r\n") + cstrUnclaimedAlertRmtChqNote ;
			 }
		     break;
		  //End - P0178584_FN01_NewPopUpMSG
		 /* 
           case 10 for IWT Non Taxable account, using 10 because to reserve 
           6-9 for unclaimed for future case.       
         */
		 case 10:
			 {
				cstrAlertMessage = cstrTinNotExists ;
			 }
           break;
         default:
            {
               cstrAlertMessage = CString( "Test" );
            }
            break;
      }

      AfxMessageBox( cstrAlertMessage.GetBuffer(), MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );
   }

   return(0);
}

//******************************************************************************
void BaseAccountDetailsDlg::openRemarkScreen()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("openRemarkScreen"));
   
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      
      int accountIndex = m_lvAccounts.GetNextSelection( );
      DString name;
      DString strMarket = DSTCommonFunctions::getMarket();
      DString strAcctNum = m_lvAccounts.GetItemString( accountIndex, I_( "AccountNum" ) );

      if( strMarket == MARKET_IDS::JAPAN )
          getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, true );
      else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
          getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, name, false );
      setParameter( NAME, name);
      setParameter( ACCOUNT_NUM, strAcctNum );
      setParameter(I_("ORG_CMDID"), CMD_BPROC_REMARKS );
      SetMessageStatusBar( TXT_LOAD_REMARKS );

      eRtn = invokeCommand( getParent(), CMD_BPROC_REMARKS, PROC_NO_TYPE, false, NULL );

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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAccountDetailsDlg.cpp-arc  $
 * 
 *    Rev 1.316   Jul 25 2012 23:59:50   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation, bring logic that fixed by Win back, due to misunderstanding.
 * 
 *    Rev 1.315   Jul 24 2012 19:15:08   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.314   Jul 23 2012 22:36:24   dchatcha
 * P0179630 FN01 FATCA Project - Foriegn Tax Review.
 * 
 *    Rev 1.313   Jul 06 2012 18:18:52   wp040240
 * IN 2938135 - Desktop/Web screens - to be converted to new Java/Script library 
 * 
 *    Rev 1.312   Jul 03 2012 08:33:04   wichian
 * IN#2867502 - Lanuch the fund limitation screen as a model screen instead of modeless
 * 
 *    Rev 1.311   Jul 02 2012 12:34:36   wutipong
 * IN2972829 - TFSA accounts - Government Filing and Amendment
 * 
 *    Rev 1.310   May 14 2012 04:34:52   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.309   Apr 27 2012 21:35:32   wp040132
 * IN 2924964 - R12.3 P0191291.FN01.R03 - Account Details Screen in iFAST Displays MRC Code
 * 
 *    Rev 1.308   Apr 03 2012 22:54:56   panatcha
 * IN2766093 - IWT TIN Warning Message
 * 
 *    Rev 1.307   Feb 21 2012 17:15:38   if991250
 * Mat Sweep Instructions - reset on modless set focus and init
 * 
 *    Rev 1.306   Feb 17 2012 10:38:12   panatcha
 * P0186486_FN03 - RRIF Annuities - Remove checking TaxType
 * 
 *    Rev 1.305   Feb 17 2012 10:05:04   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.304   Feb 16 2012 17:19:32   if991250
 * Account Commitment
 * 
 *    Rev 1.303   Feb 13 2012 04:28:06   panatcha
 * P0186486_FN03 - RRIF Annuities
 * 
 *    Rev 1.302   Feb 08 2012 20:58:54   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.301   Feb 08 2012 04:51:42   panatcha
 * DesktopWeb conversion
 * 
 *    Rev 1.300   Feb 02 2012 00:34:54   dchatcha
 * IN# 2799812 - Contract issues, change the way on working with master contract CBO
 * 
 *    Rev 1.299   Feb 01 2012 13:29:18   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues. Fix crashing on no portfolio required environment.
 * 
 *    Rev 1.298   Jan 26 2012 06:16:46   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.297   Jan 26 2012 01:11:04   dchatcha
 * Synch up: IN# 2810924 - Fix Screen Parameters
 * 
 *    Rev 1.296   Jan 25 2012 08:54:46   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.295   Jan 19 2012 12:13:26   wp040132
 * Minerva ISF Code changes..
 * 
 *    Rev 1.294   Jan 11 2012 10:53:38   jankovii
 * IN 2806063 -  Cash Sweep Configuration
 * 
 *    Rev 1.293   Dec 19 2011 23:58:30   popescu
 * DSK French - last changes for 12.2
 * 
 *    Rev 1.292   Dec 13 2011 12:07:08   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.291   Dec 12 2011 12:00:46   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.290   Dec 08 2011 14:22:12   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.289   Dec 01 2011 19:05:56   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.288   Nov 25 2011 15:55:48   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.287   Nov 21 2011 18:38:10   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.286   Nov 19 2011 01:21:28   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.285   Nov 17 2011 14:17:54   popescu
 * INA - called Guarante Info Browser screen
 * 
 *    Rev 1.284   Nov 15 2011 12:17:44   popescu
 * Fix annoying compile warning.
 * 
 *    Rev 1.283   Nov 15 2011 19:28:24   dchatcha
 * Desktop French changes, build error
 * 
 *    Rev 1.282   Nov 14 2011 13:05:12   popescu
 * Desktop French changes
 * 
 *    Rev 1.281   Nov 14 2011 10:00:58   wp040100
 * P0186477/FN03 - GIA - Added GI Investments History under Attributes
 * 
 *    Rev 1.280   Oct 28 2011 22:25:14   dchatcha
 * P0181953 FN01 - TFSA Amendment - revise account refreshing logic.
 * 
 *    Rev 1.279   Oct 28 2011 07:07:36   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.278   Oct 25 2011 15:50:12   dchatcha
 * IN# 2646991 - P0181953- Amendment not generated when  using clone functionality.
 * 
 *    Rev 1.277   Oct 21 2011 07:31:38   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.276   Sep 27 2011 11:21:50   kitticha
 * PETP0186040 FN01 IN2661710 - MFR Run Date should be displayed.
 * 
 *    Rev 1.275   Sep 16 2011 12:11:42   dchatcha
 * P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
 * 
 *    Rev 1.274   Aug 08 2011 01:04:40   panatcha
 * IN2593683 - Incorrect pop-up msg
 * 
 *    Rev 1.273   Jul 21 2011 16:23:44   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.272   Jul 18 2011 20:15:34   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.271   Jul 11 2011 07:43:26   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test.
 * 
 *    Rev 1.270   Jul 07 2011 18:49:50   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.269   Jun 29 2011 09:25:44   kitticha
 * PETP0186040 FN01 - MFR Run Date and Calculation Logic.
 * 
 *    Rev 1.268   Jun 23 2011 04:51:42   kitticha
 * PETP0178584_FN01_IN2567560_Incorrect Pop Up Messages.
 * 
 *    Rev 1.267   Jan 31 2011 17:56:14   popescu
 * P0179308 FN01 - Synch-up from pre 11.3 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.266   Jan 20 2011 04:20:08   panatcha
 * Correct Remitted caution label: P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.265   Jan 20 2011 02:58:12   panatcha
 * Update new fn: for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.264   Jan 19 2011 03:38:54   panatcha
 * Update according to Code Review for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.263   Jan 18 2011 06:31:00   panatcha
 * Update R2&R3: P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.262   Jan 16 2011 23:57:00   panatcha
 * update: P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.260   Dec 28 2010 00:20:56   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.259   Nov 26 2010 15:19:20   popescu
 * PET0165541 FN03 - QESI Phase3 - fixed overlapping of the confirmation when a transaction error pops-up
 * 
 *    Rev 1.258   Nov 22 2010 13:41:04   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.257   Nov 16 2010 02:26:58   dchatcha
 * PET0165541 FN03 - QESI Phase3. missing parameter for calling screen.
 * 
 *    Rev 1.256   Oct 29 2010 07:08:02   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.255   Sep 30 2010 10:04:56   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.254   Sep 17 2010 06:30:38   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.253   Jul 05 2010 14:55:40   popescu
 * PET165541_FN09_QESI Phase 2 - removed the isQESI method the implementation of it is empty
 * 
 *    Rev 1.252   Jun 17 2010 11:34:16   jankovii
 * PET165541_FN09_QESI Phase 2
 * 
 *    Rev 1.251   Jun 15 2010 11:27:18   jankovii
 * PET165541_FN09_QESI Phase 2
 * 
 *    Rev 1.250   Apr 22 2010 21:41:32   popescu
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.249   Apr 09 2010 21:45:58   popescu
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.248   Feb 12 2010 14:45:48   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.247   Jan 29 2010 11:58:04   popescu
 * Incident 1995449 - Desktop awd history lookup results
 * 
 *    Rev 1.246   Jan 28 2010 17:05:48   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.245   Jan 22 2010 04:02:02   dchatcha
 * IN# 1982775 - Verify Static Data Screen (Entity Name)
 * 
 *    Rev 1.244   Nov 20 2009 11:42:26   popescu
 * Static Data - entity verify names -linked the web screen
 * 
 *    Rev 1.243   Jul 23 2009 10:57:42   jankovii
 * PET 0164646 FN01 - TFSA phase 3.
 * 
 *    Rev 1.242   Jul 09 2009 13:11:10   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.241   Mar 12 2009 13:20:02   jankovii
 * PET 142007 FN04 - TFSA.
 * 
 *    Rev 1.240   Mar 11 2009 10:43:04   jankovii
 * PET 142007 FN04 - TFSA.
 * 
 *    Rev 1.239   Mar 09 2009 10:29:14   jankovii
 * PET 142007 FN04 - TFSA.
 * 
 *    Rev 1.238   Dec 17 2008 11:54:54   wongsakw
 * Sync Up - IN1522599 Unclaimed Property - Stale Dated Cheque stage in cautions box.
 * 
 *    Rev 1.237   Dec 16 2008 10:50:04   jankovii
 * Sync up: IN 1511831 - Unclaimed Property -  View Stop NFU should appear on Caution Box
 * 
 *    Rev 1.236   Nov 28 2008 14:01:18   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.235   Nov 28 2008 13:49:16   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.234   Nov 25 2008 11:30:50   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.233   Nov 06 2008 14:44:28   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.232   Nov 06 2008 02:42:50   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.231   31 Oct 2008 14:11:04   popescu
 * Fix compile issue related to changes on the unclaimed property screens
 * 
 *    Rev 1.230   Oct 31 2008 16:04:02   wongsakw
 * IN1453089 Changes on the Unclaimed property screens
 * 
 *    Rev 1.229   Oct 07 2008 05:55:30   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box) rework for some logic.
 * 
 *    Rev 1.228   Oct 06 2008 07:22:22   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box)
 * 
 *    Rev 1.227   Oct 03 2008 04:54:28   wongsakw
 * IN1425185 User can't access Address/Mailing Screen on Desktop Re89 SHOWSTOPPER - change the way getting account object
 * 
 *    Rev 1.226   Oct 01 2008 03:19:14   wongsakw
 * IN1425185 - User can't access Address/Mailing Screen on Desktop Re89 SHOWSTOPPER
 * 
 *    Rev 1.225   Sep 22 2008 14:34:34   jankovii
 * Sync up: IN 1421441 - When Invest on Behlaf 3rd party is set to Yes desktop does not disp
 * 
 *    Rev 1.224   Sep 22 2008 08:46:12   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.223   Sep 15 2008 11:33:04   jankovii
 * IN 1411467 - On Desktop all accounts are showing these 2 values under the “Cautions Section”
 * 
 *    Rev 1.222   Jul 23 2008 16:27:20   jankovii
 * PET 59888 AML Enhancement.
 * 
 *    Rev 1.221   Jul 23 2008 13:18:02   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.220   06 May 2008 09:58:06   kovacsro
 * PET2255-FN47 New LIF - prepend the tax type to 'Gain/Loss'
 * 
 *    Rev 1.219   05 May 2008 14:51:16   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.218   18 Apr 2008 16:07:28   kovacsro
 * PET2255-FN47 New LIF
 * 
 *    Rev 1.217   Mar 11 2008 19:56:04   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.216   Mar 04 2008 09:47:50   jankovii
 * IN 1158658 - values in cautions box.
 * 
 *    Rev 1.215   Mar 04 2008 09:39:44   jankovii
 * IN 1158658 - values in cautions box.
 * 
 *    Rev 1.214   Feb 22 2008 10:48:08   jankovii
 * PET 5517 FN80B -DOT and Addendum.
 * 
 *    Rev 1.213   Feb 20 2008 16:29:02   jankovii
 * PET 5517 FN80B -DOT and Addendum.
 * 
 *    Rev 1.212   Feb 20 2008 12:46:56   jankovii
 * PET 5517 FN80B -DOT and Addendum.
 * 
 *    Rev 1.211   07 Jan 2008 13:54:24   kovacsro
 * IN#1065012 - check in for Winnie (read ACCT_DETAIL rather than AFFLUENT for inquiry permission)
 * 
 *    Rev 1.210   Dec 07 2007 17:40:18   smithdav
 * PET2400 FN01 - Dividend Processing
 * 
 *    Rev 1.209   06 Dec 2007 15:20:14   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.208   Dec 06 2007 19:41:58   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.207   13 Nov 2007 16:37:22   kovacsro
 * Affluent field now controlled by the AFFLUENT security band
 * 
 *    Rev 1.206   Oct 08 2007 12:17:44   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.205   Sep 21 2007 17:58:38   smithdav
 * PET 2360 FN02 - Launch Global AMS screen from AcctDetails for FOF funds.
 * 
 *    Rev 1.204   Sep 18 2007 11:01:56   jankovii
 * IN #1007214 - To show MFR, MF and Invoice model codes.
 * 
 *    Rev 1.203   28 Aug 2007 14:21:34   popescu
 * Added LINKMFR to the caution box
 * 
 *    Rev 1.202   16 Aug 2007 12:51:18   popescu
 * Incident# 977474 - access id shhould not be created by the user
 * 
 *    Rev 1.201   Aug 10 2007 14:10:08   jankovii
 * PET 2360 FN14&FN19 - Management Fee.
 * 
 *    Rev 1.200   Aug 07 2007 10:12:52   jankovii
 * Gaps 14 & 19 PET 2360 - MFR.
 * 
 *    Rev 1.199   Jun 18 2007 14:55:40   purdyech
 * Magic 825366 - Changed PeekMessage to PM_NOREMOVE to fix AWD "Freeze".
 * 
 *    Rev 1.198   Mar 13 2007 15:53:00   popescu
 * Incident# 831808 - fix the CloneAccount freeze.
 * 
 *    Rev 1.197   Mar 13 2007 15:35:38   popescu
 * Incident# 831808 - fix the CloneAccount freeze.
 * 
 *    Rev 1.196   Feb 27 2007 21:15:32   popescu
 * Incident#  831221 - backed the code of Web Account Clone feature for CDN market
 * 
 *    Rev 1.195   Dec 20 2006 15:27:32   fengyong
 * PET2282 FN01 - Modify after walkthrough, chnage screen title.
 * 
 *    Rev 1.194   Dec 19 2006 16:56:36   fengyong
 * PET2282 FN01 - Add Clone Account web page
 * 
 *    Rev 1.193   Dec 06 2006 14:56:54   fengyong
 * Incident #763433 - refresh account detail after ok on fund limitation page
 * 
 *    Rev 1.192   Nov 22 2006 13:59:52   fengyong
 * Incident #764972 - Add reference to FundLimitation from account option box
 * 
 *    Rev 1.191   Nov 15 2006 16:57:08   popescu
 * Incident# 750524 - track the receipt of W9 forms
 * 
 *    Rev 1.190   Nov 10 2006 18:23:44   popescu
 * PET 2881/01 - added the UAF permissions
 * 
 *    Rev 1.189   Nov 10 2006 18:07:44   popescu
 * PET 2281/FN 01
 * 
 *    Rev 1.188   Nov 08 2006 17:29:58   popescu
 * PET 2281/FN 01- copy account for TA 
 * 
 *    Rev 1.187   Jul 04 2006 12:03:36   ZHANGCEL
 * PET 2145 FN01 - Add "Assignee" in Cautions Box
 * 
 *    Rev 1.186   Jun 08 2006 17:31:40   fengyong
 * Add parameter for BrowserLaunch
 * 
 *    Rev 1.185   Feb 23 2006 11:36:58   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default: remove method GetSubstitutionDescFromCode
 * 
 *    Rev 1.184   Feb 21 2006 10:37:26   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.183   Jan 12 2006 15:20:16   popescu
 * Incindent# 494405 - refresh the display of the address information if user changes the broker/branch/slsrep on the account information screen, and the account is either nominee or intermediary
 * 
 *    Rev 1.182   Dec 12 2005 09:48:52   zhengcon
 * Incident #452850 -- fixed problem: AWD History button in Desktop doesn't display all the business area trans
 * 
 *    Rev 1.181   Oct 25 2005 17:02:12   popescu
 * Incident 437014, system id is a mandatory field in AWD look up
 * 
 *    Rev 1.180   Sep 15 2005 12:57:42   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.179   Sep 01 2005 13:19:58   AGUILAAM
 * PET1250_FN07_Fund Merge: support display of active only or all  holdings based on generic control
 * 
 *    Rev 1.178   Aug 26 2005 11:09:50   fengyong
 * Incident 378383 - Alt+O then refresh on new traded confirm can not back to account detail screen.
 * 
 *    Rev 1.177   Jul 06 2005 13:48:44   hernando
 * PET1250 FN01 - Added Acct Cut Off Times to list box.
 * 
 *    Rev 1.176   May 20 2005 11:30:58   georgeet
 * Incident 291298 - Group information are missing from the Account Detail screen.  Added fields AcctGroup and AcctGroupName to the Dlg.
 * 
 *    Rev 1.175   Mar 17 2005 14:12:54   aguilaam
 * IN_234826: display shrnum, acctnum, entity owner name on acctreview screen
 * 
 *    Rev 1.174   Mar 04 2005 16:35:02   georgeet
 * PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
 * 
 *    Rev 1.173   Feb 23 2005 15:47:00   porteanm
 * Incident 249072 /WO 21216 - Stop flags attributes should launch COA when dblclkd.
 *
 *    Rev 1.172   Jan 17 2005 18:24:14   hernando
 * PTS10037736 - Removed reference to AWDEVENT.
 * 
 *    Rev 1.171   Dec 03 2004 10:58:00   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.170   Nov 11 2004 16:30:04   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.169   Oct 18 2004 12:57:58   HERNANDO
 * PTS10034836 - Recovered Pension Information invocation.
 * 
 *    Rev 1.168   Oct 13 2004 16:18:00   VADEANUM
 * PET1117 FN21 - Renamed from SettleLoc to SettlementInstr
 * 
 *    Rev 1.167   Sep 16 2004 11:31:04   ZHANGCEL
 * PET1082 -- Add readpermission check for the Tax Exempty Authorization.
 * 
 *    Rev 1.166   Aug 31 2004 17:25:18   FENGYONG
 * PET1117 FN05 - Client Fee Enhancement
 * 
 *    Rev 1.165   Aug 11 2004 12:05:40   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.164   Aug 06 2004 18:09:20   ZHANGCEL
 * PET 1082 FNrlc - Tax Exempt Authorization support
 * 
 *    Rev 1.163   Jul 30 2004 16:38:14   YINGBAOL
 * PET1124:Add Stop redemption settlement flag
 * 
 *    Rev 1.162   Jul 28 2004 15:02:24   ZHANGCEL
 * PET1082 FNrlc -- New Quebec withholding Tax
 * 
 *    Rev 1.161   Jul 26 2004 13:52:08   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.160   May 26 2004 18:16:04   YINGBAOL
 * PET985: Add read permission check for foreign content.
 * 
 *    Rev 1.159   May 11 2004 14:24:16   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 * 
 *    Rev 1.158   Apr 23 2004 17:33:42   HERNANDO
 * PET1027 FN02 - Added 'High Risk' text to Cautions.
 * 
 *    Rev 1.157   Apr 21 2004 15:43:10   VADEANUM
 * PET985 FN01 - LSIF - work in progress.
 * 
 *    Rev 1.156   Apr 16 2004 09:54:06   FENGYONG
 * PET944 FN01 - NSCC Broker
 * 
 *    Rev 1.155   Apr 08 2004 17:23:58   FENGYONG
 * PET944 FN01 REL56.1 NSCC BROKER
 * 
 *    Rev 1.154   Apr 07 2004 18:40:32   FENGYONG
 * PET944FN01 Rel56.1 NSCC Broker
 * 
 *    Rev 1.153   Apr 05 2004 17:37:44   FENGYONG
 * PET944FN01 release 56.1 NSCC Broker
 * 
 *    Rev 1.152   Mar 08 2004 11:27:44   HERNANDO
 * PTS10026849 - Changed format flag for retrieving MultiAcctEachShrNum.
 * 
 *    Rev 1.151   Mar 04 2004 11:10:48   HERNANDO
 * PET965 FN11 - Switched Historical Account to Historical Info.
 * 
 *    Rev 1.150   Jan 12 2004 13:31:50   HERNANDO
 * PET892 FN1 - Changed 'Clearing ID' display to Clearing ID Code value for Winnie.
 * 
 *    Rev 1.149   Nov 27 2003 10:36:26   HERNANDO
 * PET892 FN1 - Added Settlement Location.
 * 
 *    Rev 1.148   Nov 05 2003 15:57:28   VADEANUM
 * PTS 10023398 syncup - Upper Alt Account Nbr in comparison to set the right key on accounts list
 * 
 *    Rev 1.147   Oct 23 2003 18:02:00   FENGYONG
 * PET809 FN08 Direct trading enhancement
 * 
 *    Rev 1.146   Oct 19 2003 18:35:42   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.145   Oct 16 2003 12:34:50   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.144   Sep 10 2003 15:35:54   HERNANDO
 * Sync'd up to 1.140.1.0 / 1.137.1.1; PTS 10015486.
 * 
 *    Rev 1.143   Sep 03 2003 17:16:04   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.142   Jun 04 2003 11:31:24   HERNANDO
 * Added 'Stop AMS Rebalancing' to Cautions list.
 * 
 *    Rev 1.141   May 22 2003 14:13:46   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.140   Mar 21 2003 18:33:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.139   Mar 14 2003 08:55:28   sanchez
 * Changes for ChargeSTTRFee and ChargeERFee
 * 
 *    Rev 1.138   Feb 26 2003 11:17:30   linmay
 * modified  setStatusBarMessage() for PTS 10012767
 * 
 *    Rev 1.137   Jan 26 2003 15:25:16   KOVACSRO
 * Added new cautions, acct. category related.
 * 
 *    Rev 1.136   Jan 25 2003 17:05:36   KOVACSRO
 * Added AccountCategory
 * 
 *    Rev 1.135   Jan 23 2003 15:53:12   ZHANGCEL
 * Code Sync up with 1.129.1
 * 
 *    Rev 1.134   Jan 20 2003 17:21:12   HSUCHIN
 * added account contract process
 * 
 *    Rev 1.133   Jan 17 2003 14:12:40   KOVACSRO
 * Removed WRAP from cautions.
 * 
 *    Rev 1.132   Jan 15 2003 16:54:28   sanchez
 * Account number for shareholder family
 * 
 *    Rev 1.131   Jan 15 2003 12:04:22   KOVACSRO
 * Commented out ESOP.
 * 
 *    Rev 1.130   Jan 13 2003 18:04:32   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.129   Jan 03 2003 18:53:12   HSUCHIN
 * added WRAP to Cautions when social code is WR
 * 
 *    Rev 1.128   Dec 30 2002 09:56:36   sanchez
 * On fillCaptionsList() add  ROW_DETAILS_CAUTIONS_MGMT_FEE_PAY_OPTN string to the cautions list
 * 
 *    Rev 1.127   Nov 19 2002 14:51:58   HERNANDO
 * Undid changes for PTS 10009814.
 * 
 *    Rev 1.126   Nov 19 2002 14:31:36   KOVACSRO
 * new Hypo redemptions.
 * 
 *    Rev 1.125   Nov 06 2002 16:55:02   HERNANDO
 * Rename.
 * 
 *    Rev 1.124   Nov 06 2002 14:51:26   HERNANDO
 * Added AMS Option.
 * 
 *    Rev 1.123   Nov 06 2002 10:31:34   YINGBAOL
 * sync. up version 1.122 in release 49
 * 
 *    Rev 1.122   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.121   Oct 09 2002 18:34:32   HERNANDO
 * PTS 10009712 - Fixed inconsistency of Balance display between iFAST and iFAST/Desktop.
 * 
 *    Rev 1.120   Oct 07 2002 15:28:38   HERNANDO
 * PTS 10009712 Fix - Displays 'Cancelled' if reversal; consistent with Transaction History Dialog now.
 * 
 *    Rev 1.119   Sep 30 2002 11:01:36   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.118   Sep 26 2002 16:55:02   KOVACSRO
 * After the enhancement introduced by PTS 10009878 (user can add a default bank when submitting a trade), have to refresh options.
 * 
 *    Rev 1.117   Sep 17 2002 15:14:36   HERNANDO
 * PTS 10009813 - Multiple AWD Business Areas mapped to the same System ID will cause look-ups to ignore Business Area.
 * PTS 10009814 - Removed 'COR' from Transfer Agency code.
 * 
 *    Rev 1.116   09 Sep 2002 15:18:04   HUANGSHA
 * check the permission of estatement through view64(73)
 * 
 *    Rev 1.115   Sep 04 2002 18:42:46   HERNANDO
 * PTS 10009712 - Display 'Cancelled' if reversal for balance.
 * 
 *    Rev 1.114   Aug 29 2002 12:57:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.113   Aug 26 2002 17:23:58   HERNANDO
 * Precautionary code - removed tabs from values referenced in the .ini tables for AWD.
 * 
 *    Rev 1.112   Aug 16 2002 13:51:24   YINGBAOL
 * check permission for Setttlement
 * 
 *    Rev 1.111   Aug 12 2002 14:31:52   KOVACSRO
 * PTS 10009105 : refresh latest shareholder number.
 * 
 *    Rev 1.110   Aug 06 2002 14:05:48   HERNANDO
 * PTS 10009277 - Display fund number for Cash Distribution.  Display 'Cash' instead of 'Settled' for Balance.
 * 
 *    Rev 1.109   31 Jul 2002 09:40:48   HUANGSHA
 * Added attribute to launch the Estatement Dialog, based on the permission
 * 
 *    Rev 1.108   Jul 19 2002 11:44:14   HSUCHIN
 * added check to AcctNumCtrl to enable/disable Add new account button
 * 
 *    Rev 1.107   Jul 08 2002 15:51:18   ZHANGCEL
 * Added logic to sove the problem of displaying "0.0000" instead of "Settled" underneath the Banance column
 * 
 *    Rev 1.106   Jul 05 2002 17:50:18   HERNANDO
 * PTS 10008762 - Revised UnitBalance display of TransHistory list.
 * 
 *    Rev 1.105   Jul 05 2002 17:07:38   HSUCHIN
 * bug fix for deactivating trading button from search dialog
 * 
 *    Rev 1.104   Jul 05 2002 11:49:40   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 * 
 *    Rev 1.103   Jun 26 2002 13:46:26   HERNANDO
 * Include Pension Info Attribute if TaxType is one of { B, C, L }.
 * 
 *    Rev 1.102   13 Jun 2002 10:15:24   YINGZ
 * support settlement in caution
 * 
 *    Rev 1.101   Jun 04 2002 11:15:58   ZHANGCEL
 * Added a new function: OnOk() to sove the problem of <Enter> key
 * 
 *    Rev 1.100   Jun 02 2002 17:56:02   HSUCHIN
 * added pension info
 * 
 *    Rev 1.99   31 May 2002 13:27:14   HERNANDO
 * Added Account Review.
 * 
 *    Rev 1.98   May 30 2002 11:00:48   KOVACSRO
 * Added BankCharges and ConsolidateEFT
 * 
 *    Rev 1.97   May 28 2002 12:19:48   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.96   May 08 2002 14:36:30   YINGBAOL
 * PTS10008141
 * 
 *    Rev 1.95   06 May 2002 11:20:18   KOVACSRO
 * AreThereAllocationsInThisPending changes. PTS 10008103.
 * 
 *    Rev 1.94   May 03 2002 10:12:02   YINGBAOL
 * small change
 * 
 *    Rev 1.93   Apr 26 2002 10:19:26   YINGBAOL
 * Fix multiaccount RRIF refresh issue---PTS10007965
 * 
 *    Rev 1.92   Apr 23 2002 09:57:40   YINGBAOL
 * Take DeleteAllItems out(Base classs already handle them) and fix AllFundTransfer display for pending trade.  
 * 
 *    Rev 1.91   27 Mar 2002 20:00:58   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.90   Mar 19 2002 09:31:02   YINGBAOL
 * add applyPST
 * 
 *    Rev 1.89   26 Feb 2002 16:55:58   HSUCHIN
 * added entry point for hypothetical redemption
 * 
 *    Rev 1.88   21 Feb 2002 15:50:48   HSUCHIN
 * changed interest accruals with accruals
 * 
 *    Rev 1.87   Feb 19 2002 14:07:58   YINGBAOL
 * Add FeeParameter 
 * 
 *    Rev 1.86   Feb 11 2002 17:19:54   HERNANDO
 * Changed DiscardMsgDlg call.
 * 
 *    Rev 1.85   04 Feb 2002 15:25:50   KOVACSRO
 * Timer List Control changes.
 * 
 *    Rev 1.84   Dec 31 2001 14:33:36   YINGBAOL
 * pass shareholder number to account info screen
 * 
 *    Rev 1.83   Dec 20 2001 13:38:34   HERNANDO
 * Added AWD-related conditions.
 * 
 *    Rev 1.82   Dec 07 2001 17:56:24   HERNANDO
 * Revised use of AwdInterface; removed local instance.
 * 
 *    Rev 1.81   03 Dec 2001 13:02:02   KOVACSRO
 * Lazy init for shareholder address.
 * 
 *    Rev 1.80   28 Nov 2001 14:34:36   KOVACSRO
 * minor change (tunning).
 * 
 *    Rev 1.79   20 Nov 2001 16:46:38   KOVACSRO
 * more tunning and some status bar messages.
 * 
 *    Rev 1.78   19 Nov 2001 11:24:50   KOVACSRO
 * some tunning
 * 
 *    Rev 1.77   Nov 12 2001 17:02:34   HERNANDO
 * Uses pointer to AwdInterface.
 * 
 *    Rev 1.76   09 Nov 2001 16:58:04   KOVACSRO
 * wait cursor implementation for 'NewAccount' (minor change)
 * 
 *    Rev 1.75   07 Nov 2001 11:50:46   KOVACSRO
 * Fixed YTD bug.
 * 
 *    Rev 1.74   24 Sep 2001 11:01:30   HSUCHIN
 * added logic to disable trade button when account split commission is not defined for commission type 2
 * 
 *    Rev 1.73   Sep 18 2001 08:47:38   JANKAREN
 * Changed logic for As Pension Plan to base on taxtype
 * 
 *    Rev 1.72   Sep 12 2001 11:16:54   ZHANGCEL
 * Added paramter: MODEL_ACCOUNT_NUM
 * 
 *    Rev 1.71   03 Sep 2001 13:18:22   HSUCHIN
 * Acct Split Comm now performs check before displaying
 * 
 *    Rev 1.70   29 Aug 2001 16:13:24   HSUCHIN
 * added account level split, no security check yet
 * 
 *    Rev 1.69   Aug 23 2001 16:21:20   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.68   23 Aug 2001 15:54:58   WINNIE
 * remove browse button
 * 
 *    Rev 1.67   18 Aug 2001 09:25:42   HSUCHIN
 * added YTD to attributes
 * 
 *    Rev 1.66   16 Aug 2001 10:08:28   KOVACSRO
 * Added ESoP attribute.
 * 
 *    Rev 1.65   10 Aug 2001 16:21:12   HSUCHIN
 * code cleanup
 * 
 *    Rev 1.64   10 Aug 2001 15:53:56   HSUCHIN
 * no change, beautify source
 * 
 *    Rev 1.63   Aug 09 2001 15:44:02   HUANGSHA
 * remove the hardcoded string
 * 
 *    Rev 1.62   Jul 20 2001 15:22:28   HERNANDO
 * Clean up - Removed m_btnAWD.
 * 
 *    Rev 1.61   Jun 15 2001 17:45:54   HERNANDO
 * Added AWD History for Luxembourg.
 * 
 *    Rev 1.60   14 Jun 2001 12:03:56   SMITHDAV
 * Remove references to UserAccessProcess.
 * 
 *    Rev 1.59   Jun 12 2001 10:48:06   DINACORN
 * Sync SSB 1.49.1.2
 * 
 *    Rev 1.58   Jun 12 2001 10:05:58   DINACORN
 * Sync SSB 1.49.1.0
 * 
 *    Rev 1.57   Jun 11 2001 15:50:48   HERNANDO
 * Removed literal.
 * 
 *    Rev 1.56   Jun 11 2001 14:55:04   OLTEANCR
 * changed IDS_SEMICOL to IDS_LBL_SEMICOL
 * 
 *    Rev 1.55   Jun 11 2001 14:52:26   OLTEANCR
 * fixed screen label transl.
 * 
 *    Rev 1.54   Jun 11 2001 13:33:40   OLTEANCR
 * fixed screen label translation
 * 
 *    Rev 1.53   11 Jun 2001 10:17:42   YINGZ
 * support saving plan
 * 
 *    Rev 1.52   05 Jun 2001 16:06:46   YINGZ
 * for others to compile
 * 
 *    Rev 1.51   May 28 2001 12:54:08   OLTEANCR
 * unchanged
 * 
 *    Rev 1.50   03 May 2001 14:07:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.49   Mar 30 2001 17:59:06   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.48   Mar 27 2001 14:28:00   YINGZ
 * add checking when user want to add new acct or close     screen
 * 
 *    Rev 1.47   09 Mar 2001 18:05:14   BUZILAMI
 * launching the new BankInstructions
 * 
 *    Rev 1.46   Feb 22 2001 17:05:08   HERNANDO
 * Added System_ID and Business_Area to AWD History.
 * 
 *    Rev 1.45   21 Feb 2001 18:15:18   KOVACSRO
 * Added doSend
 * 
 *    Rev 1.44   Feb 12 2001 14:52:16   YINGBAOL
 * retrieve market from databroker instead of registry
 * 
 *    Rev 1.43   Feb 01 2001 11:34:44   JANKAREN
 * Sync up with C2/C3 - Add FeeWaived, SupEmpConf, SupConf and Unseizable to CautionList
 * 
 *    Rev 1.42   Jan 26 2001 17:53:26   ZHANGCEL
 * Synchronization to C2/C3: Fixed the bug regarding the RRIF_LIF_LRIF lable showing up
 * 
 *    Rev 1.41   Jan 24 2001 13:06:58   KOVACSRO
 * moved some code from doModellesSetFocus() in doRefresh();
 * 
 *    Rev 1.40   Jan 16 2001 13:54:32   KOVACSRO
 * Added some PendingTrades refresh stuff.
 * 
 *    Rev 1.39   Dec 19 2000 11:03:02   ZHANGCEL
 * Added function OnClickLvAccounts() in order to add  or delete  RRIF_LIF_LRIF item in the Attribution list corresbondingly
 * 
 *    Rev 1.38   Dec 07 2000 18:01:30   KOVACSRO
 * Added some extra logic for permission check.
 * 
 *    Rev 1.37   Dec 05 2000 14:26:34   WINNIE
 * enable COA buttom
 * 
 *    Rev 1.36   Dec 01 2000 14:41:54   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.35   Dec 01 2000 10:46:12   ZHANGCEL
 * Modify DisplyTitle()
 * 
 *    Rev 1.34   Nov 28 2000 16:56:48   ZHANGCEL
 * Added entity name in the title bar
 * 
 *    Rev 1.33   Nov 16 2000 16:32:32   HERNANDO
 * Displays messages based on AWD Exception or return value.
 * 
 *    Rev 1.32   Nov 08 2000 16:57:02   ZHANGCEL
 * Added logic for enable or disable < New Account> button base on MultiAcctEachShrNum
 * 
 *    Rev 1.31   Nov 03 2000 11:49:22   KOVACSRO
 * Bug fixed (OnPostInitDialog was positioning wrong the main container)
 * 
 *    Rev 1.30   Nov 03 2000 11:15:04   DINACORN
 * Remove the logic for Change/Browse button in AccountDetails screen
 * 
 *    Rev 1.29   Oct 25 2000 12:24:04   KOVACSRO
 * Enabled Remarks button on the main screen, whenever an account is active.
 * 
 *    Rev 1.28   Oct 20 2000 13:53:52   ZHANGCEL
 * Fix the bug that cause the crashing when user clicks the PendingTrad Radio Button
 * 
 *    Rev 1.26   Oct 19 2000 16:44:02   KOVACSRO
 * Dealer number / Branch shows BranchCode for Canada.
 * 
 *    Rev 1.25   Sep 22 2000 15:30:40   HERNANDO
 * Modified parameter value for Demographics Dialog.
 * 
 *    Rev 1.24   Jul 28 2000 16:47:26   ZHANGCEL
 * Added code for Fund number of C2
 * 
 *    Rev 1.23   Jul 19 2000 10:47:50   WINNIE
 * Filter Contract, RESP, Gurantee Attribute on account defail screen according to the taxtype, system features and permission
 * 
 *    Rev 1.22   Jul 18 2000 13:48:18   PETOLESC
 * Modified title bar for the RRIF dialog.
 * 
 *    Rev 1.21   Jul 07 2000 13:42:18   ZHANGCEL
 * Changed for launching FreeUnitDlg
 * 
 *    Rev 1.20   Jun 29 2000 13:09:38   HERNANDO
 * Set AWD Button on init
 * 
 *    Rev 1.19   Jun 28 2000 14:02:34   HERNANDO
 * Implemented 'AWD History' Button on Details Dialog
 * 
 *    Rev 1.18   Jun 27 2000 11:05:14   HUANGSHA
 * tab order fix
 * 
 *    Rev 1.17   Jun 12 2000 17:09:14   YINGBAOL
 * automatic transfer comes back
 * 
 *    Rev 1.16   Jun 05 2000 11:21:52   YINGBAOL
 * temperally remove AT by HLLAPI
 * 
 *    Rev 1.15   Jun 03 2000 16:16:16   BUZILA
 * fix assert for launching Pending trades for accounts without transactions 
 * 
 *    Rev 1.14   May 12 2000 17:53:00   ZHANGCEL
 * Remove some parameters for ContractInfo
 * 
 *    Rev 1.13   Apr 17 2000 15:07:34   ZHANGCEL
 * Changed getField  parameter for DofBirth
 * 
 *    Rev 1.12   Apr 14 2000 14:14:36   YINGBAOL
 * Automatic Transfer screen is launched instead of HLLAPI
 * 
 *    Rev 1.11   Apr 11 2000 11:24:48   ZHANGCEL
 * Add parameter for DofBirth
 * 
 *    Rev 1.10   Apr 05 2000 10:27:50   DT24433
 * removed unused headers
 * 
 *    Rev 1.9   Mar 22 2000 12:56:32   BUZILA
 * Grid changes
 * 
 *    Rev 1.8   Mar 22 2000 11:21:06   PETOLESC
 * Small corrections.
 * 
 *    Rev 1.7   Mar 22 2000 11:14:42   PETOLESC
 * Uncommented RESP.
 * 
 *    Rev 1.6   Mar 21 2000 11:32:44   YINGBAOL
 * added RRIF LIF Info Dialoge
 * 
 *    Rev 1.5   Mar 17 2000 16:42:38   PETOLESC
 * Added RESP dialogs. Here commented, to allow compilation.
 * 
 *    Rev 1.4   Mar 09 2000 15:21:22   ZHANGCEL
 * Bug Fixed
 * 
 *    Rev 1.3   Mar 09 2000 15:13:50   ZHANGCEL
 * Added ContractInfoDlg and GuaranteeInfoDlg stuffs
 * 
 *    Rev 1.2   Mar 03 2000 16:24:16   HSUCHIN
 * merged with latest SIT fixes from old database
 * 
 *    Rev 1.1   Feb 28 2000 15:31:12   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.69   Feb 09 2000 12:09:50   HUANGSHA
// added TransType param for invoking the systematic screen
// 
//    Rev 1.68   Jan 31 2000 17:17:20   VASILEAD
// Took out Free units
// 
//    Rev 1.67   Jan 26 2000 10:14:10   POPESCUS
// quick fix
// 
//    Rev 1.66   Jan 25 2000 19:20:42   VASILEAD
// Refresh stuff
// 
//    Rev 1.65   Jan 25 2000 13:56:54   POPESCUS
// added a break
// 
//    Rev 1.64   Jan 25 2000 11:39:18   BUZILA
// double click on STOPs has to launch COA
// 
//    Rev 1.63   Jan 23 2000 21:12:28   POPESCUS
// Refresh fix
// 
//    Rev 1.62   Jan 23 2000 16:58:28   POPESCUS
// fixed the bug that freezes the app after errors in trxns and updated remarks in confirmation
// 
//    Rev 1.61   Jan 22 2000 15:22:18   POPESCUS
// fix in refresh
// 
//    Rev 1.60   Jan 21 2000 17:49:40   VASILEAD
// Refresh stuff
// 
//    Rev 1.59   Jan 17 2000 15:22:04   YINGBAOL
// hllapi change sync
// 
//    Rev 1.58   Jan 12 2000 09:08:18   POPESCUS
// changes related to cloning an account and fixing some validation, adding subst sets
// 
//    Rev 1.57   Jan 09 2000 16:42:56   PRAGERYA
// Made compilable!
// 
//    Rev 1.56   Jan 05 2000 12:07:58   YINGZ
// get rid of confirmation dlg
// 
//    Rev 1.55   Dec 24 1999 15:18:28   VASILEAD
// Fixed transactions
// 
//    Rev 1.54   Dec 24 1999 10:29:58   VASILEAD
// Fixed NASU flow
// 
//    Rev 1.53   Dec 23 1999 11:29:18   POPESCUS
// NASU process and the new confirmation model
// 
//    Rev 1.52   Dec 22 1999 11:27:40   YINGBAOL
// hllapi change sync.
// 
//    Rev 1.51   12 Dec 1999 12:41:52   HSUCHIN
// changed setGlobal to check for market when setting the caller name
// 
//    Rev 1.50   Dec 10 1999 18:12:12   BUZILA
// changed to launch COA modally
// 
//    Rev 1.49   Dec 10 1999 11:58:44   VASILEAD
// Added refresh support
// 
//    Rev 1.48   Dec 09 1999 16:05:46   ZHANGCEL
// Add codes for setting parameters for AcctInfo
// 
//    Rev 1.47   Dec 03 1999 18:23:12   ZHANGCEL
// add logic for NewAccount
// 
//    Rev 1.45   Dec 01 1999 19:54:30   VASILEAD
// Stuff
// 
//    Rev 1.44   Dec 01 1999 14:55:32   VASILEAD
// Fixed bug on deleting entities
// 
//    Rev 1.43   Dec 01 1999 09:24:10   VASILEAD
// NASU fixes
// 
//    Rev 1.42   Nov 30 1999 18:25:02   POPESCUS
// changes related to the NASU flow
// 
//    Rev 1.41   Nov 29 1999 09:53:58   VASILEAD
// Added business/edits for Entity screen
// 
//    Rev 1.40   Nov 24 1999 10:09:40   POPESCUS
// 
//    Rev 1.39   Nov 23 1999 18:05:48   POPESCUS
// NASU flow
// 
//    Rev 1.38   Nov 23 1999 17:24:44   PRAGERYA
// Minor change
// 
//    Rev 1.37   Nov 22 1999 18:19:46   VASILEAD
// changed the way IDS are populated
// 
//    Rev 1.36   Nov 20 1999 13:14:40   VASILEAD
// Worked on entity - account relationship
// 
//    Rev 1.35   Nov 15 1999 12:04:18   ZHANGCEL
// add code for launching DemoGraphicsDlg
// 
//    Rev 1.34   Nov 12 1999 12:34:44   YINGZ
// add info to open bank dlg
// 
//    Rev 1.33   Nov 11 1999 16:55:06   PRAGERYA
// new parameter for allocations process added
// 
//    Rev 1.32   Nov 10 1999 13:46:24   VASILEAD
// Changed USER_GLOBALS to WORK_GLOBALS
// 
//    Rev 1.31   Nov 10 1999 11:18:04   HSUCHIN
// added name to be passed to the remarks process
// 
//    Rev 1.30   Nov 07 1999 16:02:42   HSUCHIN
// added access to gui historical account information
// 
//    Rev 1.29   Nov 03 1999 11:59:04   VASILEAD
// Fixed the security access to Address screen
// 
//    Rev 1.28   Nov 02 1999 13:44:32   YINGBAOL
// Pass shareholder number to Address Process
// 
//    Rev 1.27   Oct 30 1999 15:08:52   HSUCHIN
// Added Historical Account
// 
//    Rev 1.26   Oct 27 1999 14:58:16   POPESCUS
// Fix related to the change in the dstcdatabroker
// 
//    Rev 1.25   Oct 26 1999 10:15:22   VASILEAD
// M2 syncup
// 
//    Rev 1.24   Oct 25 1999 11:29:10   VASILEAD
// Syncup with M2
// 
//    Rev 1.21   Oct 15 1999 11:08:02   POPESCUS
// Fixed compiling issues related to the new infra-1900
// 
//    Rev 1.20   Oct 05 1999 09:45:30   HUANGSHA
// Set focus on the selected entity of AltAccount + BrokerCode
// 
//    Rev 1.19   Sep 28 1999 14:14:36   VASILEAD
// Corrected some issues regarding the Currency field
// 
//    Rev 1.18   Sep 27 1999 11:21:16   VASILEAD
// Changed the order in FirstName , LastName
// 
//    Rev 1.17   Sep 26 1999 18:29:26   VASILEAD
// Added support for AllFunds mode in transactions screen
// 
//    Rev 1.16   Sep 25 1999 15:37:58   BUZILA
// Fix SHAREHOLDER_NUM in ShareHolder launch
// 
//    Rev 1.15   Sep 24 1999 10:13:54   PRAGERYA
// "Milestone" check in
// 
//    Rev 1.14   Sep 23 1999 14:27:10   VASILEAD
// Set the EntityId parameter for Demographics process
// 
//    Rev 1.13   Sep 23 1999 14:09:40   PRAGERYA
// New Allocations process
// 
//    Rev 1.12   Sep 21 1999 18:17:36   VASILEAD
// Added FreeUnits support
// 
//    Rev 1.11   Sep 21 1999 14:20:34   VASILEAD
// Added functionality for All funds check box in Details screen
// 
//    Rev 1.10   Sep 20 1999 11:29:06   VASILEAD
// Changes to implement C1 requirements
// 
//    Rev 1.9   Sep 16 1999 16:52:56   VASILEAD
// Update Details dialog
// 
//    Rev 1.8   Sep 16 1999 11:42:20   VASILEAD
// BankAcctNum -> BankingInstr
// 
//    Rev 1.7   Sep 16 1999 09:15:08   YINGZ
// test substitution list
// 
//    Rev 1.6   Sep 14 1999 14:48:54   YINGZ
// ?
// 
//    Rev 1.5   Sep 14 1999 14:41:44   YINGZ
// changes for listview ctrl
// 
//    Rev 1.4   14 Sep 1999 13:37:46   HUANGSHA
// No change
// 
//    Rev 1.3   14 Sep 1999 10:16:32   HUANGSHA
// Fixed merge errors
// 
//    Rev 1.2   13 Sep 1999 13:52:32   HUANGSHA
// Synchronize with M1's changes
// 
//    Rev 1.1   Sep 03 1999 16:55:32   YINGZ
// base for details dlg
 * 
 *    Rev 1.34   Aug 31 1999 15:56:28   PRAGERYA
 * Shareholder  and AccInfo dialogs
 * 
 *    Rev 1.33   Aug 26 1999 16:11:38   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.32   Aug 19 1999 12:38:26   PRAGERYA
 * Enhancing ShareholderInfo and AccountInfo implementations
 * 
 *    Rev 1.31   Aug 11 1999 16:24:10   BUZILA
 * fix new account launch
 * 
 *    Rev 1.30   Aug 10 1999 09:49:22   DT24433
 * changed getfieldforcurrentlistitem to getfield
 * 
 *    Rev 1.29   Aug 09 1999 17:10:10   BUZILA
 * added COA call methods
 * 
 *    Rev 1.28   Aug 09 1999 16:00:36   VASILEAD
 * fixed a bug in transaction list
 * 
 *    Rev 1.27   Aug 09 1999 15:29:08   VASILEAD
 * bug fixed
 * 
 *    Rev 1.26   Aug 08 1999 19:33:54   PRAGERYA
 * All in!
 * 
 *    Rev 1.25   04 Aug 1999 16:24:56   HUANGSHA
 * Save/Load Column Size in/From the Registry, using String Table for loading the ID description instead of the returned contents from DB
 * 
 *    Rev 1.24   Jul 30 1999 17:27:56   PRAGERYA
 * Invoking Shareholder dialog
 * 
 *    Rev 1.23   Jul 28 1999 18:31:54   PRAGERYA
 * Shareholder
 * 
 *    Rev 1.22   Jul 28 1999 17:07:54   VASILEAD
 * Correct focus on list boxes
 * 
 *    Rev 1.21   Jul 28 1999 13:35:12   VASILEAD
 * Add See allocations support for pending trades
 * 
 *    Rev 1.20   Jul 28 1999 11:29:38   YINGZ
 * align dlg in the screen bottom
 * 
 *    Rev 1.19   Jul 28 1999 10:41:56   YINGZ
 * allow cascade for all dlg
 * 
 *    Rev 1.18   Jul 27 1999 16:39:30   VASILEAD
 * Add address code support for selection in address book dialog
 * 
 *    Rev 1.17   Jul 26 1999 09:08:52   VASILEAD
 * Chage list box to combo box for address selection
 * 
 *    Rev 1.16   Jul 23 1999 15:05:30   VASILEAD
 * changed the selection address form ListBox to ComboBox
 * 
 *    Rev 1.15   Jul 22 1999 17:32:36   VASILEAD
 * Fixed two different mask support for Amount field
 * 
 *    Rev 1.14   Jul 20 1999 18:18:38   VASILEAD
 * Set focus and hot key for Kana and Kanji address lists
 * 
 *    Rev 1.13   Jul 20 1999 16:43:38   VASILEAD
 * Modified hllapi point Systematic Transfer to go to Automatic Transfer Info in character base system
 * 
 *    Rev 1.12   Jul 20 1999 13:36:44   POPESCUS
 * Set tot ignore data not found when checks are to be displayed
 * 
 *    Rev 1.11   Jul 20 1999 11:18:12   VASILEAD
 * New conditions update
 * 
 *    Rev 1.10   Jul 19 1999 11:53:34   POPESCUS
 * Do not show the Entity screen if the user doesn't have access to it and it double-clicks on the entity list
 * 
 *    Rev 1.9   Jul 16 1999 17:31:56   VASILEAD
 * blah blah
 * 
 *    Rev 1.8   Jul 16 1999 13:09:12   VASILEAD
 * Double mask for Amount filed
 * 
 *    Rev 1.7   Jul 14 1999 17:22:24   HSUCHIN
 * bug fix for global info
 * 
 *    Rev 1.6   Jul 14 1999 10:03:28   POPESCUS
 * Fixed AccDetails to accomodate Jerry's fix
 * 
 *    Rev 1.5   Jul 13 1999 17:22:52   HSUCHIN
 * add code to put caller info into global fields
 * 
 *    Rev 1.3   Jul 09 1999 15:33:36   VASILEAD
 * Bug fixes
 * 
 *    Rev 1.2   Jul 08 1999 10:58:42   VASILEAD
 * Put in the new java function for retriving the current date  formatting with the current locale
 * 
 *    Rev 1.1   Jul 08 1999 10:04:30   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

