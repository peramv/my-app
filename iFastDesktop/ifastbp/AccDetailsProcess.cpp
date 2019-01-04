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
//******************************************************************************
//
// ^FILE   : AccountDetailsProcess.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 03/11/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountDetailsProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accdetailsprocess.hpp"
#include "accdetailsprocessincludes.h"

#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include <ifastcbo\AcctCategoryList.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\coanavig.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entityidslist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\funddetail.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\amsmstrlist.hpp>
#include <ifastcbo\AcctGuaranteeGuardOptList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHAREHOLDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COA;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountDetailsProcess > processCreator( CMD_BPROC_ACC_DETAILS );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCDETLIT  //stands for account details literals
{
   const I_CHAR * const ENTITY_ID_FIELD         = I_( "EntityId" );
   const I_CHAR * const ACCOUNT_NUMBER_FIELD    = I_( "AccountNum" );
   const I_CHAR * const PHONE_NUM_FIELD         = I_( "PhoneNum" );
   const I_CHAR * const ALT_ACCOUNT_NUM_FIELD   = I_( "AltAccountNum" );
   const I_CHAR * const BROKER_CODE_FIELD       = I_( "BrokerCode" );

}

namespace CRCY
{
   extern CLASS_IMPORT I_CHAR * const CANADIAN_DOLLAR;
   extern CLASS_IMPORT I_CHAR * const EURO_DOLLAR;
   extern CLASS_IMPORT I_CHAR * const IRISH_POUNDS;
   extern CLASS_IMPORT I_CHAR * const LUXEMBOURG_FRANC;
   extern CLASS_IMPORT I_CHAR * const POTUGUESE_ESCUDO;
   extern CLASS_IMPORT I_CHAR * const USD;
   extern CLASS_IMPORT I_CHAR * const JAPANESE_YEN;
}

namespace ACCOUNT_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const PRIVATE;
   extern CLASS_IMPORT I_CHAR * const SWIFT_PAYMENT_METHOD;
   extern CLASS_IMPORT I_CHAR * const DEBIT_SWIFT_PAYMENT_METHOD;
}

namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_AND_ACCOUNT_LEVEL ;
}
namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "AccountDetailsProcess" );

   const I_CHAR * const Y                          = I_( "Y" );
   const I_CHAR * const N                          = I_( "N" );
   const I_CHAR * const INPUT_ACC_NUM_FIELD        = I_( "InputAcctNum" );
   const I_CHAR * const INPUT_SHR_NUM_FIELD        = I_( "InputShrNum" );
   const I_CHAR * const NUM_ENTRY_FIELD            = I_( "NumEntry" );
   const I_CHAR * const CASH_STRING                = I_( "CASH" );
   const DString EMPTY_STRING;
   const int NUMBER_OF_DISPLAYED_TRADES            = 3;
   const I_CHAR * const COMMA                      = I_( "," );
   const I_CHAR * const SPACE_STRING               = I_( " " );
   const I_CHAR * const ESOP_PARTICIPATION         = I_( "E" );
   const I_CHAR * const ESOP_INVESTMENT            = I_( "D" );
   const I_CHAR * const THREE_STRING               = I_( "3" );
   //account categories
   const I_CHAR * const LOAN                       = I_( "01" );
   const I_CHAR * const MARGIN                     = I_( "02" );
   const I_CHAR * const CHEQUE_PRIVILEGE           = I_( "03" );
   const I_CHAR * const WRAP                       = I_( "04" );
   //taxtype
   const I_CHAR * const TFSA_TAX_TYPES             = I_( "V" );
}

//user access function codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const DEMOGRAPHICS;
   extern CLASS_IMPORT I_CHAR * const REMARKS;
   extern CLASS_IMPORT I_CHAR * const SHR_FAMILY;
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTOMATIC_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const INTEREST_ACCRUAL;
   extern CLASS_IMPORT I_CHAR * const ACB;
   extern CLASS_IMPORT I_CHAR * const CHEQUE;
   extern CLASS_IMPORT I_CHAR * const HISTORICAL_MARKET_VALUE;

   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_ALLOC_INFO;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_GUARANTEE;
   extern CLASS_IMPORT I_CHAR * const RESP_INFO;
   extern CLASS_IMPORT I_CHAR * const RESP_ACCOUNT_INFROMATION;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const AS_PENSION_PLAN;
   extern CLASS_IMPORT I_CHAR * const ACCT_SPLIT_COMM;
   extern CLASS_IMPORT I_CHAR * const YTD;
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER;
   extern CLASS_IMPORT I_CHAR * const HYPOTHETICAL_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTREVIEW;
   extern CLASS_IMPORT I_CHAR * const PENSION_INFO;
   extern CLASS_IMPORT I_CHAR * const ESTATEMENT;
   extern CLASS_IMPORT I_CHAR * const SHR_FAMILY;
   extern CLASS_IMPORT I_CHAR * const PROTECTED_FUND_ACCT_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const ACCT_LEVEL_SETTLEMENT_RULE;
   extern CLASS_IMPORT I_CHAR * const LIF_GAIN_LOSS;
   extern CLASS_IMPORT I_CHAR * const DOC_LIST;
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZATION_INFO;
   extern CLASS_IMPORT I_CHAR * const ACCTLVL_TRAILERFEE_SETUP;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT;
}

namespace DBSUBS
{
   extern CLASS_IMPORT const long LV_AcctListHeadingSet ;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccDetailsEntityListHeading;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsFundsListHeading;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsTransHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AccDetailsPendingHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId ResClient;
   extern CLASS_IMPORT const BFTextFieldId RES2Client;
   extern CLASS_IMPORT const BFTextFieldId BirthdateAge;
   extern CLASS_IMPORT const BFDecimalFieldId OfferPrice;
   extern CLASS_IMPORT const BFTextFieldId AddrStatus;
   extern CLASS_IMPORT const BFTextFieldId FamilyCodeExist;
   extern CLASS_IMPORT const BFTextFieldId AcctCategoryExist;
   extern CLASS_IMPORT const BFTextFieldId DTAType;
   extern CLASS_IMPORT const BFTextFieldId ShrFndSpAgrExists;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId ShrFndBrkExist;
   extern CLASS_IMPORT const BFTextFieldId AcctCutOffTimeExists;
   extern CLASS_IMPORT const BFTextFieldId ActiveOnly;
   extern CLASS_IMPORT const BFTextFieldId AssocFund;
   extern CLASS_IMPORT const BFTextFieldId AssocClass;
   extern CLASS_IMPORT const BFTextFieldId SettlementRuleExist;
   extern CLASS_IMPORT const BFTextFieldId EligExtTrfGainLoss;
   extern CLASS_IMPORT const BFTextFieldId RetMailReasonCode;
   extern CLASS_IMPORT const BFTextFieldId CatValue;
   extern CLASS_IMPORT const BFTextFieldId IARuleSetup;
   extern CLASS_IMPORT const BFTextFieldId PendingFATCASrch;
   extern CLASS_IMPORT const BFTextFieldId EntRegDetlExist;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeExist;
   extern CLASS_IMPORT const BFTextFieldId TaxFormsAppl;
   extern CLASS_IMPORT const BFDecimalFieldId GuarMktValue;
   
   //P0178584_FN01_NewPopUpMSG
   extern CLASS_IMPORT const BFTextFieldId StaleChqStage;
   //End - P0178584_FN01_NewPopUpMSG
   extern CLASS_IMPORT const BFTextFieldId TINExists;
   extern CLASS_IMPORT const BFTextFieldId BankingLevel;
   extern CLASS_IMPORT const BFTextFieldId AlertViewed;
   extern CLASS_IMPORT const BFTextFieldId RemarkAlertExists;
   extern CLASS_IMPORT const BFTextFieldId AlertMessageExists;

   //P0268205_FATCA/CRS Extraction
   extern CLASS_IMPORT const BFTextFieldId IsRegExtrAcct;
}

namespace ALERT_MSG_OPENED_FROM
{
    extern CLASS_IMPORT I_CHAR * const ACCT_DETL;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AccountDetailsProcess::AccountDetailsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_searchCode (NULL_STRING),
_pAccountEntityXref(NULL),
_pIterAccountEntityXrefOut (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   flg_entity_finished = false;
   _pFundDetailList = NULL;
   _strCurrentFundCode = NULL_STRING;
   _strCurrentClassCode = NULL_STRING;

   addContainer( IFASTBP_PROC::ACCOUNT_DETAILS_LIST, true );
   addContainer( IFASTBP_PROC::ENTITY_LIST,          true,     IFASTBP_PROC::ACCOUNT_DETAILS_LIST);
   addContainer( IFASTBP_PROC::ENTITY_IDS_LIST,      true,     IFASTBP_PROC::ENTITY_LIST);
   addContainer( IFASTBP_PROC::FUNDS_LIST,           true,     IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addContainer( IFASTBP_PROC::TRANSACTIONS_LIST,    true,     IFASTBP_PROC::FUNDS_LIST);
   addContainer( IFASTBP_PROC::FUNDS_DETAILS_LIST,   true );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO,      false,    IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addContainer( IFASTBP_PROC::ADDRESS_LIST,         true,     IFASTBP_PROC::SHAREHOLDER_CBO );
   addContainer( IFASTBP_PROC::PENDING_TRADES_LIST,  true,     IFASTBP_PROC::ACCOUNT_DETAILS_LIST );

   addFieldDetails( ifds::BeneficialOwner,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BrokerName,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BranchName,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SlsrepName,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BrokerCode,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BranchCode,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Slsrep,                              IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AccountNum,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::TaxType,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST/* , SUBCLASS_PROCESS*/);
   addFieldDetails( ifds::DTAType,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopRedSettle,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AcctType,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::XrefNum,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AcctStatus,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST/*, SUBCLASS_PROCESS*/);
   addFieldDetails( ifds::TaxTypeSchedule,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AccountBalance,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::CurrencyName,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Currency,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::AltAccount,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::DateOfReg,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ShrNum,                              IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::SlsrepAltName,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PlanType,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   //for Admin Dates
   addFieldDetails( ifds::ModDate,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ModUser,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ProcessDate,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Username,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   //End admin dates
   addFieldDetails( ifds::AcctGroup,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctGroupName,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::InterCode,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::InterAccount,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctDesignation,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::RegistrationInfo,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::FeeModelCode,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::FundLimitOvrdExist,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HasGIAHolding,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
   addFieldDetails( ifds::RegisteredTransfers,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::FeeWaived,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SupEmpConf,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SupConf,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Employee,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Unseizable,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::InTrustFor,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopFCrebal,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctCommExists,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::GSTExempt,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ApplyPST,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BankChrgs,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ConsolidEFT,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PensionJurisExists,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstSettleDate,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ProtContractExists,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctCategoryExist,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CategMargin,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CategLoan,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CategChqPriv,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CategWrap,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UseBrokerMF,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ActiveOnly,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::NetworkID,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsGWOContractExist,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctGuarGuardExists,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::NextMFRProcessDate,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsMFRAccount,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Name1,                               IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PendingFATCASrch,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AccountGroupExist,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PrivateWealthAcct,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PrivateWealthOptOut,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   
   addFieldDetails( ifds::IdType,                              IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdTypeDesc,                          IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdValue,                             IFASTBP_PROC::ENTITY_IDS_LIST );

   addFieldDetails( ifds::SIN,                                 IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS );
   addFieldDetails( ifds::DofBirth,                            IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstName,                           IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS  );
   addFieldDetails( ifds::LastName,                            IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS  );
   addFieldDetails( ifds::EntityType,                          IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthFirstName,                      IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS );
   addFieldDetails( ifds::BirthLastName,                       IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntityId,                            IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthdateAge,                        IFASTBP_PROC::ENTITY_LIST,          SUBCLASS_PROCESS );

   addFieldDetails( ifds::rxFundCode,                          IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::rxClassCode,                         IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::Baycom,                              IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::FundNAV,                             IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::SettledUnits,                        IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::SettledValue,                        IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::Currency,                            IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::GuarMktValue,                        IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::FOFFund,                             IFASTBP_PROC::FUNDS_LIST,           SUBCLASS_PROCESS );
   addFieldDetails( ifds::rxOpenDate,                          IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::rxCloseDate,                         IFASTBP_PROC::FUNDS_LIST );

   addFieldDetails( ifds::OfferPrice,                          IFASTBP_PROC::TRANSACTIONS_LIST,    SUBCLASS_PROCESS );

   addFieldDetails( ifds::rxFundCode,                          IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::rxClassCode,                         IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::TransId,                             IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::TradeDate,                           IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::TransType,                           IFASTBP_PROC::TRANSACTIONS_LIST );

   addFieldDetails( ifds::TransNum,                            IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::UnitPrice,                           IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::Units,                               IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::GrossAmt,                            IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::Settled,                             IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::Cancelled,                           IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::Reversal,                            IFASTBP_PROC::TRANSACTIONS_LIST );

   addFieldDetails( ifds::UnitBalance,                         IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::TfrFund,                             IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::TfrClass,                            IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::Baycom,                              IFASTBP_PROC::TRANSACTIONS_LIST );
   addFieldDetails( ifds::SeqNum,                              IFASTBP_PROC::TRANSACTIONS_LIST );

   addFieldDetails( ifds::rxFundCode,                          IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::rxClassCode,                         IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::Baycom,                              IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::TradeDate,                           IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::TransTypeDesc,                       IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::TransNum,                            IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::AmountType,                          IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::AmountTypeDesc,                      IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::Amount,                              IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::TransType,                           IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::WireOrdNum,                          IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::GrossNetMethod,                      IFASTBP_PROC::PENDING_TRADES_LIST );
   addFieldDetails( ifds::FundTo,                              IFASTBP_PROC::PENDING_TRADES_LIST );

   addFieldDetails( ifds::AddrCode,                            IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrStatus,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::Name1,                               IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::Name2,                               IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine1,                           IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine2,                           IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine3,                           IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine4,                           IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine5,                           IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::kAddrLine1,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::kAddrLine2,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::kAddrLine3,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::kAddrLine4,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::kAddrLine5,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::PostalCode,                          IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::CountryCode,                         IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::CountryName,                         IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::EffectiveDate,                       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::StopDate,                            IFASTBP_PROC::ADDRESS_LIST );

   addFieldDetails( ifds::PendingTrade,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Remarks,                             IFASTBP_PROC::SHAREHOLDER_CBO,      SUBCLASS_PROCESS );	
   addFieldDetails( ifds::ShrFndSpAgrExists,                   IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ShrFndBrkExist,                      IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::AcctIdentifierExist,				   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS ); 

   addFieldDetails( ifds::AcctCutOffTimeExists,                IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::Certificates,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopPurchase,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopAMSRebalancing,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopRed,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopXferOut,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopXferIn,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StopNFU,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BankingInstr,                        IFASTBP_PROC::SHAREHOLDER_CBO,      SUBCLASS_PROCESS );
   addFieldDetails( ifds::SystemTrsfr,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PAC,                                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SWP,                                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctAlloc,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UnsettledTrn,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SavePlanExist,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ESoPEligible,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ExistBeneficiary,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SettleLocExist,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClearingID,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TerritoryCode,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClearingFirm,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HighestEntityRisk,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HoldDivPymt,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   
   addFieldDetails( ifds::CashSweepExists,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MatIntExists,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // Early Redemption fee
   addFieldDetails( ifds::ChargeERFee,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ChargeSTTRFee,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // Add Shareholder family
   addFieldDetails( ifds::FamilyCodeExist,                     IFASTBP_PROC::SHAREHOLDER_CBO,      SUBCLASS_PROCESS );

   // Add pay fee options 
   addFieldDetails( ifds::MgmtFeePayOption,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SocialCode,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::LinkMFR,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   //MF fields:
   addFieldDetails( ifds::Affluent,                            IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MgmtFeeId,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MgmFeeType,                          IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MgmtFeeRbtId,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::MgmtFeeRbtType,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::InvoiceModelID,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);

   addFieldDetails( ifds::EligExtTrfGainLoss,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);

   // DOT field
   addFieldDetails( ifds::DOTAdnd,                             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);

   // Add Assignee
   addFieldDetails( ifds::ExistAssignee,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // Acct level settlement rule 
   addFieldDetails( ifds::SettlementRuleExist,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // AML fields
   addFieldDetails( ifds::StopReason,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::AdditionalStopReason,              IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::TypeOfInvestor,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::InvestingOnBehalf,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ComplianceCode,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::DocListExists,                     IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);

   //for attributes, to check the user access permissions
   addFieldDetails( ACCDETLIT::ACB_ATTR,                       BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ADDRESS_BOOK_ATTR,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ENTITY_ATTR,                    BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::INTEREST_ACCRUED_ATTR,          BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::CHEQUE_ATTR,                    BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::HIST_MKT_VALUE_ATTR,            BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::DEMOGRAPHICS_ATTR,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::DISTRIBUTION_ATTR,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::FEE_PARAMETER_ATTR,             BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ACCT_TRAILER_FEE,               BF::NullContainerId,                SUBCLASS_PROCESS );

   addFieldDetails( ACCDETLIT::RIF_LIF_LRIF_INFO,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::RIF_LIF_LRIF_ALLOC_INFO,        BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::CONTRACT_ATTR,                  BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::GUARANTEE_ATTR,                 BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::RESPINFO_ATTR,                  BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::RESP_TRANSACTIONS_ATTR,         BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::YTD_CONTRIBUTION_ATTR,          BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::AS_PENSION_ATTR,                BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::HYPOTHETICAL_REDEMPTION_ATTR,   BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ACCOUNTREVIEW,                  BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::PENSION_INFO_ATTR,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ESTATEMENT_ATTR,                BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::HAS_ACCT_OWNERSHIP_RECORD,      BF::NullContainerId,                SUBCLASS_PROCESS );

   addFieldDetails( ifds::ElongName1,                          IFASTBP_PROC::FUNDS_DETAILS_LIST );

   addFieldDetails( ACCDETLIT::FUND_CURRENCY,                  BF::NullContainerId,                SUBCLASS_PROCESS, I_( "Currency" ) );

   addFieldDetails( ACCDETLIT::ENTITY_ID_NUMBER,               BF::NullContainerId,                SUBCLASS_PROCESS, I_( "EntityIdNumber" ) );
   addFieldDetails( ACCDETLIT::ACCOUNT_NUMBER_CODE,            BF::NullContainerId,                SUBCLASS_PROCESS, I_( "AccountNumber" ) );
   addFieldDetails( ACCDETLIT::PHONE_NUMBER,                   BF::NullContainerId,                SUBCLASS_PROCESS, I_( "PhoneNum" ) );
   addFieldDetails( ACCDETLIT::AMOUNT_UNITS,                   BF::NullContainerId,                SUBCLASS_PROCESS, I_( "Units" ) );
   addFieldDetails( ACCDETLIT::ALT_ACCOUNT_NUMBER_CODE,        BF::NullContainerId,                SUBCLASS_PROCESS, I_( "AltAccountNumber" ) );
   addFieldDetails( ACCDETLIT::BROKER_CODE,                    BF::NullContainerId,                SUBCLASS_PROCESS, I_( "BrokerCode" ) );
   addFieldDetails( ACCDETLIT::NEW_ACCOUNT_NUMBER,             BF::NullContainerId,                SUBCLASS_PROCESS, I_( "NewAccountNumber" ) );
   addFieldDetails( ACCDETLIT::INITIAL_ENTITY_ID,              BF::NullContainerId,                SUBCLASS_PROCESS, I_( "InitialEntityId" ) );
   addFieldDetails( ACCDETLIT::FULL_TRANS_LIST,                BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::AMS_OPTION,                     BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::ACCTCATEGORY_DESC,              BF::NullContainerId,                SUBCLASS_PROCESS );
   addFieldDetails( ACCDETLIT::FEEMODEL_ATTR,                  BF::NullContainerId,                SUBCLASS_PROCESS );

   addFieldDetails( ACCDETLIT::HAS_FOF,                        BF::NullContainerId,                SUBCLASS_PROCESS );

   addFieldDetails( ACCDETLIT::ACCT_SETTLE_RULE,               BF::NullContainerId,                SUBCLASS_PROCESS );   

   //P0178584_FN01_NewPopUpMSG
   // unclaimed property 
   addFieldDetails( ifds::StaleChqStage,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsAcctRunCuratorFile,                IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HasAcctBeenUnFrozen,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StaleChqExists,                      IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::StaleChqStageList,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RemittedChqExists,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RemittedChqStageList,                IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RtnMailStageList,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   //End - P0178584_FN01_NewPopUpMSG
   
   // investor authorization
   addFieldDetails( ifds::IARuleSetup,                         IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntityUnverifiedExist,               IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // government filing and amendment
   addFieldDetails( ifds::GovAmendmentExist,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   // Multi Manager Subscription and Direct Debit Payment
   addFieldDetails( ifds::ConsolTypeED,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::ExemptPeriod,                        IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TINExists,                           IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   //P0186486_FN03 - RRIF Annuities
   addFieldDetails( ifds::LifeAnnuityExist,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::CommitmentStatus,                   IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   addFieldDetails( ifds::StopAdjDate,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST , SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctFeeModelAssociated,              IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AcctRegulatoryExist,                IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntRegDetlExist,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AdvisorFeeExist,                    IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TaxFormsAppl,                       IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AlertViewed,                        BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RemarkAlertExists,                  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AlertMessageExists,                 IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctDelState,						  IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS );

   //P0268205 FATCA/CRS Extraction
   addFieldDetails( ifds::IsRegExtrAcct,					  IFASTBP_PROC::ACCOUNT_DETAILS_LIST);

   // Fiera Account Categorization
   addFieldDetails( ifds::InvestorClassification,             IFASTBP_PROC::ACCOUNT_DETAILS_LIST, SUBCLASS_PROCESS);
}

//******************************************************************************
AccountDetailsProcess::~AccountDetailsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pIterAccountEntityXrefOut)
   {
      delete _pIterAccountEntityXrefOut;
      _pIterAccountEntityXrefOut = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AccountDetailsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString strTempAcctNum, 
         strTempEntityIdPos, 
         strTempSearchCode;
	  
      getParameter (ACCDETLIT::ACCOUNT_NUMBER_FIELD, strTempAcctNum);
      if( !strTempAcctNum.strip().stripLeading( '0' ).empty() )
      {
		  AccountNumber = strTempAcctNum;
      }
      getParameter (ACCDETLIT::ENTITY_ID_FIELD, strTempEntityIdPos);
      if( !strTempEntityIdPos.strip().stripLeading( '0' ).empty() )
      {
	      EntityIdPos = strTempEntityIdPos;
      }
      getParameter (ACCDETLIT::PHONE_NUM_FIELD, HomePhone);
      getParameter (ACCDETLIT::ALT_ACCOUNT_NUM_FIELD, _dstrAltAccountParam);
      getParameter (ACCDETLIT::BROKER_CODE_FIELD, _dstrBrokerCodeParam);

      getParameter (ENTSRCHLIT::SEARCH_CODE, strTempSearchCode);
      if( !strTempSearchCode.strip().empty() )
      {
	      _searchCode = strTempSearchCode;
      }

      //save the entity which came in
      _initialEntityId = EntityIdPos;
      EntityId = EntityIdPos;
      _newAccountNumber = AccountNumber;
   }
   catch ( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch ( ... )
   {
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN AccountDetailsProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_ACCOUNT_DETAILS, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
const DString& AccountDetailsProcess::getFirstListItemKey ( const GenericInterface *rpGICaller, 
                                                            const BFContainerId& idList)
{  
   TRACE_METHOD (CLASSNAME, GETFIRSTLISTITEMKEY);

   DString key;
   
   try
   {      
      if (idList == IFASTBP_PROC::ACCOUNT_DETAILS_LIST)
      {
         AbstractProcess::getFirstListItemKey (rpGICaller, idList);
         if (_pIterAccountEntityXrefOut)
         {
            delete _pIterAccountEntityXrefOut;
            _pIterAccountEntityXrefOut = NULL;
         }
         if (_pIterAccountEntityXrefOut == NULL)
         {
            _pIterAccountEntityXrefOut = new BFObjIter (*_pAccountEntityXref,
                                                         getDataGroupId(), 
                                                         true, 
                                                         BFObjIter::ITERTYPE::NON_DELETED);
         }
         
         DString searchKey;
         
         if (_searchCode == SEARCHACCOUNTUSING::CIF || 
             _searchCode == SEARCHACCOUNTUSING::HOUSEHOLD)
         {
            AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
         }
         else
         {
            //use the entity id to search for items in the xref object
            AccountEntityXref::buildPartialKeyForEntityId (searchKey, EntityIdPos);
         }
         
         _pIterAccountEntityXrefOut->begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

         while (!_pIterAccountEntityXrefOut->end())
         {
            key = _pIterAccountEntityXrefOut->getStringKey ();
            
            DString entityType;
            
            AccountEntityXref::getValueForTag (key, I_("EntityType"), entityType);
            if (entityType != I_("01"))  //filter by account owners...
            {
               ++(*_pIterAccountEntityXrefOut);
               continue;
            }
            else
            {
               AbstractProcess::setCurrentListItem (rpGICaller, 
                                                    idList, 
                                                    _pIterAccountEntityXrefOut->getStringKey());
               return _pIterAccountEntityXrefOut->getStringKey();
            }
         }
         return EMPTY_STRING;      
      }
      else if (idList == IFASTBP_PROC::ENTITY_LIST)
      {
         AbstractProcess::getFirstListItemKey (rpGICaller, idList);

         BFObjIter iterAccountEntityXrefOut (*_pAccountEntityXref, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED, false, true );

         DString searchKey;
         DString acctListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
         DString accNum;
         AccountEntityXref::getValueForTag( acctListCurrentItemKey, ACCDETLIT::ACCOUNT_NUMBER_FIELD, accNum );
         AccountEntityXref::buildPartialKeyForAccount( searchKey, accNum );
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         DString key = iterAccountEntityXrefOut.getStringKey();
         AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
         return(iterAccountEntityXrefOut.getStringKey());
      }
      else if( idList == IFASTBP_PROC::TRANSACTIONS_LIST && !flagAllFunds )
      {
         AbstractProcess::getFirstListItemKey( rpGICaller, idList );

         BFObjIter iterTransactionsList(*_pTransactionsList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );

         if( !iterTransactionsList.end() )
         {
            DString strValue;
            //must have a vw file for now for iteration purposes 

            DString fundListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::FUNDS_LIST );
            DString strFundCode, strClassCode;


            BFObjIter iter(const_cast<MFAccountHoldingList &>(*_pMFAccountHoldingList ), getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );

            if( iter.positionByKey( fundListCurrentItemKey ) )
            {
               ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxFundCode,  strFundCode,  getDataGroupId() );
               ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxClassCode, strClassCode, getDataGroupId() );
            }
            else
            {
               strFundCode  = NULL_STRING;
               strClassCode = NULL_STRING;
            }

            DString componentName;
            BFData data2;

            data2.setElementValue( ifds::rxFundCode, strFundCode, true, NULL );
            data2.setElementValue( ifds::rxClassCode, strClassCode, true, NULL );

            DString key1, key2;
            iterTransactionsList.positionOnNextMatch( data2, getDataGroupId() );
            if( !iterTransactionsList.end() )
               key1 = iterTransactionsList.getStringKey();

            BFData data3;

            iterTransactionsList.begin();

            data3.setElementValue( ifds::TfrFund, strFundCode, true, NULL );
            data3.setElementValue( ifds::TfrClass, strClassCode, true, NULL );
            data3.setElementValue( ifds::rxFundCode, CASH_STRING, true, NULL );

            iterTransactionsList.positionOnNextMatch( data3, getDataGroupId() );
            if( !iterTransactionsList.end() )
               key2 = iterTransactionsList.getStringKey();

            if( key1 == NULL_STRING && key2 == NULL_STRING )
               return(_strEmpty);
            else if( key2 == NULL_STRING )
               key = key1;
            else if( key1 == NULL_STRING )
               key = key2;
            else
            {
               key = key1;
               DString strKey1, strKey2;
               strKey1 = key1.word(0);
               strKey2 = key2.word(0);

               if( convertToULong( strKey1 ) > convertToULong( strKey2 ) )
                  key = key2;
            }

            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            iterTransactionsList.positionByKey( key );
            return(iterTransactionsList.getStringKey());
         }
      }
      else if( idList == IFASTBP_PROC::PENDING_TRADES_LIST )
      {
         nNoOfPendingTrades = 1;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return AbstractProcess::getFirstListItemKey (rpGICaller, idList);
}

static const DString dstrNullString( NULL_STRING );

//******************************************************************************
const DString& AccountDetailsProcess::getNextListItemKey ( const GenericInterface *rpGICaller, 
                                                           const BFContainerId& idList)
{  
   TRACE_METHOD (CLASSNAME, GETNEXTLISTITEMKEY);

   try
   {
      DString key;

      if (idList == IFASTBP_PROC::ACCOUNT_DETAILS_LIST)
      {
         if (_pIterAccountEntityXrefOut)
         {
            if (!(++(*_pIterAccountEntityXrefOut)))
                  return EMPTY_STRING;
            while (!_pIterAccountEntityXrefOut->end())
            {
               key = _pIterAccountEntityXrefOut->getStringKey ();
               
               DString entityType,
                  entityId;
               
               AccountEntityXref::getValueForTag (key, I_("EntityType"), entityType);
               AccountEntityXref::getValueForTag (key, I_("EntityId"), entityId);
               if (entityType != I_("01") ||
                  (_searchCode != SEARCHACCOUNTUSING::CIF && _searchCode != SEARCHACCOUNTUSING::HOUSEHOLD &&
                    entityId != EntityIdPos))  //filter by account owners, and eliminate the joint ones...
               {
                  ++(*_pIterAccountEntityXrefOut);
                  continue;
               }
               else
               {
                  AbstractProcess::setCurrentListItem ( rpGICaller, 
                                                        idList, 
                                                       _pIterAccountEntityXrefOut->getStringKey());
                  return _pIterAccountEntityXrefOut->getStringKey ();
               }
            }
         }
         return EMPTY_STRING;
      }
      if (idList == IFASTBP_PROC::ENTITY_LIST)
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         DString acctListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ACCOUNT_DETAILS_LIST );
         DString acctNum;
         AccountEntityXref::getValueForTag( acctListCurrentItemKey, ACCDETLIT::ACCOUNT_NUMBER_FIELD, acctNum );
         AccountEntityXref::buildPartialKeyForAccount( searchKey, acctNum );
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

         DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
         if( !++iterAccountEntityXrefOut )
            return(EMPTY_STRING);

         DString key = iterAccountEntityXrefOut.getStringKey();
         AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
         return(iterAccountEntityXrefOut.getStringKey());
      }
      else if( idList == IFASTBP_PROC::TRANSACTIONS_LIST && !flagAllFunds )
      {
         BFObjIter iterTransactionsList(*_pTransactionsList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
         if( !iterTransactionsList.end() )
         {

            const DString& strListItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::TRANSACTIONS_LIST );
            iterTransactionsList.positionByKey( strListItemKey );
            ++iterTransactionsList;

            if( iterTransactionsList.end() )
               return(_strEmpty);

            DString fundListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::FUNDS_LIST );
            DString strFundCode, strClassCode;

            BFObjIter iter(const_cast<MFAccountHoldingList &>(*_pMFAccountHoldingList ), getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );

            if( iter.positionByKey( fundListCurrentItemKey ) )
            {
               ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxFundCode,  strFundCode,  getDataGroupId(), false);
               ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxClassCode, strClassCode, getDataGroupId(), false);
            }
            else
            {
               strFundCode  = NULL_STRING;
               strClassCode = NULL_STRING;
            }

            DString strValue;
            //must have a vw file for now for iteration purposes 
            DString componentName ;
            BFData data2;

            data2.setElementValue( ifds::rxFundCode, strFundCode, true, NULL );
            data2.setElementValue( ifds::rxClassCode, strClassCode, true, NULL );

            DString key1, key2;
            iterTransactionsList.positionOnNextMatch( data2, getDataGroupId() );
            if( !iterTransactionsList.end() )
               key1 = iterTransactionsList.getStringKey();

            BFData data3;

            iterTransactionsList.positionByKey( strListItemKey );
            ++iterTransactionsList;

            data3.setElementValue( ifds::TfrFund, strFundCode, true, NULL );
            data3.setElementValue( ifds::TfrClass, strClassCode, true, NULL );
            data3.setElementValue( ifds::rxFundCode, CASH_STRING, true, NULL );

            iterTransactionsList.positionOnNextMatch( data3, getDataGroupId() );
            if( !iterTransactionsList.end() )
               key2 = iterTransactionsList.getStringKey();


            if( key1 == NULL_STRING && key2 == NULL_STRING )
               return(_strEmpty);
            else if( key2 == NULL_STRING )
               key = key1;
            else if( key1 == NULL_STRING )
               key = key2;
            else
            {
               key = key1;
               DString strKey1, strKey2;
               strKey1 = key1.word(0);
               strKey2 = key2.word(0);

               if( convertToULong( strKey1 ) > convertToULong( strKey2 ) )
                  key = key2;
            }

            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            iterTransactionsList.positionByKey( key );
            return(iterTransactionsList.getStringKey());
         }
      }
      else if( idList == IFASTBP_PROC::PENDING_TRADES_LIST )
      {
         nNoOfPendingTrades++;
         if( nNoOfPendingTrades > NUMBER_OF_DISPLAYED_TRADES )
            return(dstrNullString);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return AbstractProcess::getNextListItemKey (rpGICaller, idList);
}

//******************************************************************************
void AccountDetailsProcess::setCurrentListItem( const GenericInterface *rpGICaller,
                                                const BFContainerId& idList,
                                                const DString& strListItemKey)
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );
   BFDataGroupId idDataGroup = getDataGroupId();

   AbstractProcess::setCurrentListItem (rpGICaller, idList, strListItemKey);
   if (IFASTBP_PROC::ACCOUNT_DETAILS_LIST == idList)
   {
      DString key (strListItemKey);

      AccountEntityXref::getValueForTag (key, 
         ACCDETLIT::ACCOUNT_NUMBER_FIELD, _newAccountNumber);
//do we really want to always start with this flag set to false???
      flagAllFunds = false;

//refresh the account number on the address list, get the shareholder      
      BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::ACCOUNT_DETAILS_LIST, idDataGroup);
      if (rpPtr)
      {
         DSTCWorkSession * pDSTCWorkSession = 
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         DString shrNum;
         Shareholder *pShareholder = NULL;

		 rpPtr->getField (ifds::ShrNum, shrNum, BF::HOST, false);        
         if (pDSTCWorkSession->getShareholder(idDataGroup, shrNum, pShareholder) <= WARNING &&
            pShareholder)
         {
            AddressList *pAddressList = NULL;
   
            if (pShareholder->getAddressList (pAddressList, idDataGroup) <= WARNING &&
               pAddressList)
            {
               _newAccountNumber.stripLeading ('0');
               pAddressList->setField (
                  ifds::AccountNum, 
                  _newAccountNumber, 
                  BF::HOST, //so everybody gets the value of the account number
                  false);
            }
         }
      }
   }
   else if (IFASTBP_PROC::FUNDS_LIST == idList)
   {
	   BFObjIter iter (const_cast<MFAccountHoldingList &>(*_pMFAccountHoldingList ), BF::HOST, 
         false, BFObjIter::ITERTYPE::NON_DELETED );

      if (iter.positionByKey (strListItemKey))
      {
         ( ( BFCBO* ) (iter.getObject()))->getField (ifds::rxFundCode, 
            _strCurrentFundCode,  idDataGroup);
         ( ( BFCBO* ) (iter.getObject()))->getField (ifds::rxClassCode, 
            _strCurrentClassCode, idDataGroup);
      }
      else
      {
         _strCurrentFundCode = NULL_STRING;
         _strCurrentClassCode = NULL_STRING;
      }
   }
   else if( idList == IFASTBP_PROC::PENDING_TRADES_LIST )
   {
         MFAccount* pMFAccount = NULL;
         PendingTradeList* pPendingTradesList = NULL;

         if( const_cast < AccountDetailsProcess *> ( this )->getCurrentMFAccount( pMFAccount, idDataGroup) <= WARNING && 
            pMFAccount != NULL )
         {
            if( pMFAccount->getPendingTradesList( pPendingTradesList, idDataGroup, NUMBER_OF_DISPLAYED_TRADES ) <= WARNING &&
               pPendingTradesList != NULL )
            {
               pPendingTradesList->getItem( strListItemKey, BF::HOST );
            }
         }
   }

   return;
}

//******************************************************************************
SEVERITY AccountDetailsProcess::doSetField( const GenericInterface *rpGICaller,
                                            const BFContainerId& idContainer,
                                            const BFFieldId& idField,
                                            const BFDataGroupId& idDataGroup,
                                            const DString& strValue,
                                            bool bFormatted)
{  // If we try to set a field this should be overridden

   if( idField  ==  ifds::BirthdateAge )
      assert(0);//this field is calculated;never set it!

   else if( idField  ==  ACCDETLIT::FULL_TRANS_LIST )
   {
      DString strCopyOfValue(strValue);
      if( strCopyOfValue.strip() == I_("Y") )
         flagAllFunds = true;
      else
         flagAllFunds = false;
      //reset the container 
      setContainer(IFASTBP_PROC::TRANSACTIONS_LIST, NULL);

   }

   else if (idField == ifds::ActiveOnly)
   {
      DString strAccNum;
      getField(rpGICaller, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, strAccNum, false);
      MFAccount *pMFAccount = NULL;

      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId(), strAccNum, pMFAccount );
      if (pMFAccount)
      {
         pMFAccount->setField( idField, strValue, getDataGroupId(), bFormatted );
         BFObjIter iter (*pMFAccount, idDataGroup);

         iter.positionByKey (I_("MFAccountHoldingList"));
         if (!iter.end ())
         {
            iter.removeObjectFromMap (true);
            setContainer (IFASTBP_PROC::FUNDS_LIST, NULL);
         }
      }
   }
   else if (idField == ifds::AlertViewed)
   {
       DString strAccNum;
       getField(rpGICaller, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, strAccNum, false);
       MFAccount *pMFAccount = NULL;

       dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId(), strAccNum, pMFAccount );
       if (pMFAccount)
       {
           pMFAccount->setAlertViewedFlag(strValue == Y);
       }
   }

   return(NO_CONDITION);
}

//******************************************************************************

void AccountDetailsProcess::doGetField(const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       DString &strValueOut,
                                       bool bFormatted ) const 
{
   SEVERITY sevRtn=NO_CONDITION;

   // Make non const pointer for calls to non-const methods
   AccountDetailsProcess *rpNonConstThis = const_cast < AccountDetailsProcess *> ( this );

   if( idContainer == IFASTBP_PROC::ACCOUNT_DETAILS_LIST )
   {
      DString acctListCurrentItemKey = rpNonConstThis->getCurrentListItemKey( rpGICaller, idContainer ); 
      DString accNum;
      AccountEntityXref::getValueForTag( acctListCurrentItemKey, ACCDETLIT::ACCOUNT_NUMBER_FIELD, accNum );

      MFAccount *pMFAccount;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId(), accNum, pMFAccount );

      if (pMFAccount)
      {
         pMFAccount->getField( idField, strValueOut, getDataGroupId(), bFormatted );

         // COA
         if( idField == ifds::PAC )
         {
            if( !hasReadPermission( UAF::PAC ) )
               strValueOut = N;
         }
         else if( idField == ifds::SWP )
         {
            if( !hasReadPermission( UAF::SWP ) )
               strValueOut = N;
         }
         else if( idField == ifds::SystemTrsfr )
         {
            if( !hasReadPermission( UAF::AUTOMATIC_TRANSFER ) )
               strValueOut = N;
         }
         else if( idField == ifds::AcctAlloc )
         {
            if( !hasReadPermission( UAF::DEFAULT_ALLOCATION ) )
               strValueOut = N;
         }
         else if( idField == ifds::ESoPEligible )
         {
            //for now disable esop
            strValueOut = N;
         }
         else if( idField == ifds::AcctCommExists )
         {
            DString dstrAcctCommExists;
            pMFAccount->getField ( ifds::AcctCommExists, dstrAcctCommExists, getDataGroupId(), false );

            if( dstrAcctCommExists == Y )
               strValueOut = hasReadPermission( UAF::ACCT_SPLIT_COMM ) ? Y : N;
         }

         else if( idField == ifds::ExistBeneficiary )
         {
            DString dstrExistBeneficiary;
            pMFAccount->getField ( ifds::ExistBeneficiary, dstrExistBeneficiary, getDataGroupId(), false );
            if( dstrExistBeneficiary == Y )
               strValueOut = hasReadPermission( UAF::ENTITY_MAINTANENCE ) ? Y : N;
            else
               strValueOut = N;
         }

         else if( idField == ifds::ExistAssignee )
         {
            DString dstrExistAssignee;
            pMFAccount->getField ( ifds::ExistAssignee, dstrExistAssignee, getDataGroupId(), false );
            if( dstrExistAssignee == Y )
               strValueOut = Y;
            else
               strValueOut = N;
         }
         else if( idField == ifds::AcctCategoryExist )
         {
            if( !hasReadPermission(UAF::ACCT_CATEGORY) && !hasReadPermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT))
               strValueOut = N;
         }
         else if( idField == ifds::DocListExists )
         {
            if( !hasReadPermission ( UAF::DOC_LIST ) )
               strValueOut = N;
         }
         else if( idField == ifds::CategMargin )
         {
            strValueOut = N;
            DString strAccCategExist;
            (const_cast < AccountDetailsProcess *> ( this ))->getField(
                                                                     rpGICaller, idContainer, ifds::AcctCategoryExist, strAccCategExist, false);
            if( strAccCategExist.strip().upperCase()==Y && hasReadPermission ( UAF::ACCT_CATEGORY ) )
            {
               if( pMFAccount->isCategoryExist( getDataGroupId(), MARGIN) )
                  strValueOut = Y;
            }
         }
         else if( idField == ifds::CategLoan )
         {
            strValueOut = N;
            DString strAccCategExist;
            (const_cast < AccountDetailsProcess *> ( this ))->getField(
                                                                     rpGICaller, idContainer, ifds::AcctCategoryExist, strAccCategExist, false);
            if( strAccCategExist.strip().upperCase()==Y && hasReadPermission ( UAF::ACCT_CATEGORY ) )
            {
               if( pMFAccount->isCategoryExist( getDataGroupId(), LOAN) )
                  strValueOut = Y;
            }
         }
         else if( idField == ifds::CategChqPriv )
         {
            strValueOut = N;
            DString strAccCategExist;
            (const_cast < AccountDetailsProcess *> ( this ))->getField(
                                                                     rpGICaller, idContainer, ifds::AcctCategoryExist, strAccCategExist, false);
            if( strAccCategExist.strip().upperCase()==Y && hasReadPermission ( UAF::ACCT_CATEGORY ) )
            {
               if( pMFAccount->isCategoryExist( getDataGroupId(), CHEQUE_PRIVILEGE) )
                  strValueOut = Y;
            }
         }
         else if( idField == ifds::CategWrap )
         {
            strValueOut = N;
            DString strAccCategExist;
            (const_cast < AccountDetailsProcess *> ( this ))->getField(
                                                                     rpGICaller, idContainer, ifds::AcctCategoryExist, strAccCategExist, false);
            if( strAccCategExist.strip().upperCase()==Y && hasReadPermission ( UAF::ACCT_CATEGORY ) )
            {
               if( pMFAccount->isCategoryExist( getDataGroupId(), WRAP) )
                  strValueOut = Y;
            }
         }
         else if ( idField == ifds::SettlementRuleExist )
         {
            strValueOut = ( pMFAccount->isSettlementRuleExist( getDataGroupId() ) == true)?
                I_( "Y" ):I_( "N" );
         }
         else if ( idField == ifds::EligExtTrfGainLoss )
         {
            strValueOut = I_("N");
            DString strLIFGainLossEligible;
            pMFAccount->isLIFGainLossEligible( getDataGroupId(), strLIFGainLossEligible );
            if( strLIFGainLossEligible.strip() == I_( "Y" ) &&
                hasReadPermission( UAF::LIF_GAIN_LOSS ) )
            {
               strValueOut = I_("Y");
            }
         }
         else if ( idField == ifds::IARuleSetup )
         {
            strValueOut = I_("N");
            DString strIARuleSetup;
            pMFAccount->getField( ifds::IARuleSetup, strIARuleSetup, getDataGroupId(), false );
            if( strIARuleSetup.strip().upperCase() == I_( "Y" ) && hasReadPermission( UAF::INVESTOR_AUTHORIZATION_INFO ) )
            {
               strValueOut = I_("Y");
            }
         }
         else if ( idField == ifds::PendingTrade )
         {
            strValueOut = I_("N");
            pMFAccount->getField (ifds::PendingTrade, strValueOut, getDataGroupId(), false);
         }
         else if ( idField == ifds::Name1)
         {
            DString strTaxType;
            strValueOut = I_("");
            pMFAccount->getField (ifds::TaxType, strTaxType, getDataGroupId(), false);
            strTaxType.strip().upperCase();
            
            if( strTaxType == TFSA_TAX_TYPES )
            {
               DString strName1;
               BFAbstractCBO *rpPtr = (const_cast < AccountDetailsProcess *> ( this ))->getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup );
               rpPtr->getField( ifds::Name1, strName1, idDataGroup, false );
               
               strValueOut = strName1;
            }
         }
         else if(idField ==  ifds::TINExists)
         {
            strValueOut = I_("N");

            if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isIWTClient (idDataGroup))
            {
               DString globalAccountNum, 
                  entityIdSeq1;

               getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, globalAccountNum);
                //IN2766093 WO720791 - IWT TIN Validation
               if(globalAccountNum == I_("0"))//First time searching ACCOUNT
               { 
                  globalAccountNum = _newAccountNumber; //current acct
               }

               if (_pAccountEntityXref &&
                  _pAccountEntityXref->GetEntityIdForAccountOwnerSequence1 (globalAccountNum, idDataGroup, entityIdSeq1))
               {
                  Entity *pEntity (NULL);
                  if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity (idDataGroup, entityIdSeq1, pEntity) <= WARNING && 
                     pEntity)
                  {
                     strValueOut = pEntity->hasIDSByType (I_("08"), idDataGroup) ? I_("Y") : I_("N");
                  }
               }
            }         
         }
         else if (idField == ifds::RemarkAlertExists)
         {
             strValueOut = pMFAccount->isRemarkAlertExists(ALERT_MSG_OPENED_FROM::ACCT_DETL, idDataGroup) ? Y:N;
         }
         else if (idField == ifds::AlertMessageExists)
         {
             strValueOut = pMFAccount->isAlertMessageExists(ALERT_MSG_OPENED_FROM::ACCT_DETL, idDataGroup) ? Y:N;
         }
      }
   }
   else if( idContainer == IFASTBP_PROC::ENTITY_LIST )
   {
      if( idField == ifds::BirthLastName || idField == ifds::BirthFirstName || idField == ifds::DofBirth || idField == ifds::SIN ||
          idField == ifds::LastName || idField == ifds::FirstName || idField  ==  ifds::BirthdateAge )
      {
         DString entityId;
         BFAbstractCBO *rpPtr = (const_cast < AccountDetailsProcess *> ( this ))->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         rpPtr->getField( ifds::EntityId, entityId, idDataGroup );
         entityId.stripLeading( '0' );

         if( entityId != NULL_STRING )
         {
            Entity *pEntity;
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );
            if( idField  ==  ifds::BirthdateAge )
            {
               strValueOut = NULL_STRING;
               DString strYears, strMths,strYearString, strMonthsString;
               if( pEntity->getEntityAge(strYears, strMths, idDataGroup) )
               {
                  if( _rpChildGI->send(const_cast<AccountDetailsProcess *>(this), I_("GetYearMonthStrings")) )
                  {
                     getParameter(I_("YEARS"), strYearString);
                     getParameter(I_("MONTHS"), strMonthsString);
                     pEntity->getField( ifds::DofBirth, strValueOut, idDataGroup, bFormatted );
                     strValueOut += SPACE_STRING 
                                    + strYears + SPACE_STRING + strYearString + COMMA
                                    + strMths + SPACE_STRING + strMonthsString;
                  }
               }
            }
            else
               pEntity->getField( idField, strValueOut, idDataGroup, bFormatted );
            strValueOut.strip();
         }
      }
   }
   else if( idContainer == IFASTBP_PROC::TRANSACTIONS_LIST )
   {
      if( idField == ifds::OfferPrice )
      {
         DString dstrtransType;
         BFAbstractCBO *rpPtr = (const_cast < AccountDetailsProcess *> ( this ))->getCBOItem( IFASTBP_PROC::TRANSACTIONS_LIST, idDataGroup );
         rpPtr->getField( ifds::TransType, dstrtransType, idDataGroup );

         if( dstrtransType != I_( "ED" ) )
            strValueOut = I_( "" );
         else
         {
            rpPtr->getField( ifds::OfferPrice, strValueOut, idDataGroup, true );
         }
         strValueOut.strip();
      }
   }
   else if( idContainer == IFASTBP_PROC::FUNDS_LIST )
   {
      if( idField == ifds::FOFFund )
      {
         strValueOut = N;
         FundDetailList *pFundDetailList = NULL;
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if ( dstcWorkSession->getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList )
         {

            if ( pFundDetailList->isFOFFund( _strCurrentFundCode, _strCurrentClassCode, idDataGroup ) ) {
               DString dstrCurrentBusinessDate;
               dstcWorkSession->getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );
               AMSMstrList* pAMSMstrList;
               dstcWorkSession->getAMSMstrList( pAMSMstrList, I_("FOF"), NULL, dstrCurrentBusinessDate, idDataGroup );
               if ( pAMSMstrList != NULL ) {
                  BFObjIter iter( *pAMSMstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
                  while( !iter.end() )
                  {
                     BFAbstractCBO *pAMSMstr = iter.getObject();
                     DString dstrAssocFund, dstrAssocClass;
                     pAMSMstr->getField( ifds::AssocFund,  dstrAssocFund,  idDataGroup, false );
                     pAMSMstr->getField( ifds::AssocClass, dstrAssocClass, idDataGroup, false );
                     if ( dstrAssocFund.strip() == _strCurrentFundCode && dstrAssocClass.strip() == _strCurrentClassCode  )
                     {
                        strValueOut = Y;
                        break;
                     }
                     ++iter;
                  }
               }
            }
         }
      }
   }
   else if( idField == ACCDETLIT::FUND_CURRENCY )
   {
      DString fundListCurrentItemKey = strValueOut;
      DString strFundCode, strClassCode;
      BFObjIter iter(const_cast<MFAccountHoldingList &>(*_pMFAccountHoldingList ), getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );

      if( iter.positionByKey( fundListCurrentItemKey ) )
      {
         ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxFundCode,  strFundCode,  getDataGroupId());
         ( ( BFCBO* ) (iter.getObject()))->getField(ifds::rxClassCode, strClassCode, getDataGroupId());
      }
      else
      {
         strFundCode  = NULL_STRING;
         strClassCode = NULL_STRING;
      }

      FundDetailList* pFundDetailList = NULL;
      AccountDetailsProcess * pThis = const_cast<AccountDetailsProcess*>(this);
      if( pThis->getFundDetailList( pFundDetailList )<=WARNING )
      {
         FundDetail *pFundDetail = NULL;
         if( pFundDetailList->getFundDetail( strFundCode, strClassCode, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::Currency, strValueOut, BF::HOST, true );
         }
      }
   }
   else if( idField == ACCDETLIT::HAS_FOF )
   {
      strValueOut = N;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      DString dstrCurrentBusinessDate;
      dstcWorkSession->getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );
      AMSMstrList* pAMSMstrList;
      dstcWorkSession->getAMSMstrList( pAMSMstrList, I_("FOF"), NULL, dstrCurrentBusinessDate, idDataGroup );
      if ( pAMSMstrList != NULL ) {
         BFObjIter iter( *pAMSMstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         if ( !iter.end() )
         {
            strValueOut = Y;
         }
      }
   }
   else if( idField == ACCDETLIT::ENTITY_ID_NUMBER )
   {
      strValueOut = EntityId;
      strValueOut.strip();
   }
   else if( idField == ACCDETLIT::ACCOUNT_NUMBER_CODE )
   {
      strValueOut = AccountNumber;
      strValueOut.strip();
      strValueOut.stripLeading( '0' );
   }
   else if( idField == ACCDETLIT::PHONE_NUMBER )
   {
      strValueOut = HomePhone;
      strValueOut.strip();
   }
   else if( idField == ACCDETLIT::ALT_ACCOUNT_NUMBER_CODE )
   {
      strValueOut = _dstrAltAccountParam;
      strValueOut.strip();
   }
   else if( idField == ACCDETLIT::BROKER_CODE )
   {
      strValueOut = _dstrBrokerCodeParam;
      strValueOut.strip();
   }

   else if( idField == ACCDETLIT::AMOUNT_UNITS || idField == ACCDETLIT::AMOUNT_DOLLARS )
   {
      DString strAmount;

      BFObjIter iter(const_cast<PendingTradeList &>(*_pPendingTradesList ), getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );

      if( iter.positionByKey( strValueOut ) )
         iter.getObject()->getField(ifds::Amount, strAmount, getDataGroupId(), false);
      else
         strAmount = NULL_STRING;

      BFData dd( ifds::DSTC0053_VWRepeat_Record);
      dd.setElementValue( ifds::Amount, strAmount, false, false );

      if( idField == ACCDETLIT::AMOUNT_UNITS )
      {
         strValueOut = dd.getElementValue( ifds::Amount, BFDataField::USE_MASK, I_( "#,###,###,###,###.0000" ) );
      }
      else
      {
         strValueOut = strAmount;
      }
   }
   //COA
   else if( idField == ifds::BankingInstr )
   {
     
     DString dstrBankingLevel,dstrValue;     
     DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
     dstcWorkSession->getOption(ifds::BankingLevel, dstrBankingLevel, getParent()->getDataGroupId(), false);
     if(BANKINGLEVEL::SHAREHOLDER_AND_ACCOUNT_LEVEL == dstrBankingLevel || 
        BANKINGLEVEL::ACCOUNT_LEVEL == dstrBankingLevel && _pCOANavig)
     {
        MFAccount *pMFAccount = NULL;
        if( (_newAccountNumber != NULL_STRING) && 
            (dstcWorkSession->getMFAccount( BF::HOST, _newAccountNumber, pMFAccount ) <= WARNING) && pMFAccount )
        {
          COANavig *pCOANavg = NULL;
          if( pMFAccount->getAccountLevelCOA(pCOANavg, _newAccountNumber, idDataGroup) <= WARNING &&
              pCOANavg && hasReadPermission( UAF::BANKING_INSTRUCTION ))
          {
              pCOANavg->getField(ifds::BankingInstr, strValueOut, idDataGroup);
          }
        }
     }
     else
        getCOAFieldWithInquiryPermission( rpGICaller, IFASTBP_PROC::SHAREHOLDER_CBO, idField, UAF::BANKING_INSTRUCTION, strValueOut );
   }
   else if( idField == ifds::Remarks )
   {
      getCOAFieldWithInquiryPermission( rpGICaller, IFASTBP_PROC::SHAREHOLDER_CBO, idField, UAF::REMARKS, strValueOut );
   }
   //attributes
   else if( idField == ACCDETLIT::ACB_ATTR )
   {
      strValueOut = hasReadPermission( UAF::ACB ) ? Y : N;
   }
   else if( idField == ACCDETLIT::ADDRESS_BOOK_ATTR )
   {
      strValueOut = hasReadPermission( UAF::ADDRESS_BOOK ) ? Y : N;
   }
   else if( idField ==  ACCDETLIT::RIF_LIF_LRIF_INFO )
   {
      DString dstrTaxType=NULL_STRING;
	  DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      getMFAcctField( rpGICaller, ifds::TaxType, dstrTaxType, false);
      dstrTaxType.strip().upperCase();

      // RIF plan type and not external RRIF (taxtype == 5)
      strValueOut = hasReadPermission( UAF::RIF_LIF_LRIF_INFO ) &&
                    (dstcWorkSession->isIntRIFPlan (dstrTaxType)) ? Y : N;
   }
   else if( idField ==  ACCDETLIT::RIF_LIF_LRIF_ALLOC_INFO )
   {
      DString dstrTaxType=NULL_STRING;
  	  DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      getMFAcctField( rpGICaller, ifds::TaxType, dstrTaxType, false);
      dstrTaxType.strip().upperCase();

      strValueOut = hasReadPermission( UAF::RIF_LIF_LRIF_ALLOC_INFO ) &&
                    (dstcWorkSession->isIntRIFPlan (dstrTaxType))
                    ? Y : N;
   }
   else if( idField == ACCDETLIT::ENTITY_ATTR )
   {
      strValueOut = hasReadPermission( UAF::ENTITY_MAINTANENCE ) ? Y : N;
   }
   else if( idField == ACCDETLIT::INTEREST_ACCRUED_ATTR )
   {
      strValueOut = hasReadPermission( UAF::INTEREST_ACCRUAL ) ? Y : N;
   }
   else if( idField == ACCDETLIT::CHEQUE_ATTR )
   {
      strValueOut = hasReadPermission( UAF::CHEQUE ) ? Y : N;
   }
   else if( idField == ACCDETLIT::HIST_MKT_VALUE_ATTR )
   {
      strValueOut = hasReadPermission( UAF::HISTORICAL_MARKET_VALUE ) ? Y : N;
   }
   else if( idField == ACCDETLIT::DEMOGRAPHICS_ATTR )
   {
      strValueOut = hasReadPermission( UAF::DEMOGRAPHICS ) ? Y : N;
   }
   else if( idField == ACCDETLIT::DISTRIBUTION_ATTR )
   {
      strValueOut = hasReadPermission( UAF::DISTRIBUTION ) ? Y : N;
   }
   else if( idField == ACCDETLIT::FEE_PARAMETER_ATTR )
   {
      strValueOut = hasReadPermission( UAF::FEE_PARAMETER ) ? Y : N;
   }
   else if( idField == ACCDETLIT::ACCT_TRAILER_FEE )
   {
	  DString dstrTrailerFeeArch;
  	  DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      dstcWorkSession->getOption(ifds::TrailerFeeArch, dstrTrailerFeeArch, getParent()->getDataGroupId(), false);
      dstrTrailerFeeArch.strip ();

      strValueOut = hasReadPermission( UAF::ACCTLVL_TRAILERFEE_SETUP ) && dstrTrailerFeeArch == Y ? Y : N;
   }
   else if( idField == ifds::SettleLocExist )
   {
      strValueOut = hasReadPermission( UAF::SETTLE_LOCATION_ACCT_LVL ) ? Y : N;
   }
   else if( idField == ACCDETLIT::CONTRACT_ATTR )
   {
      sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::CotClient, strValueOut, idDataGroup );
      strValueOut = ( strValueOut == Y && ( hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT ) 
                                            || hasReadPermission( UAF::SEG_FUND_CONTRACT ) ) )? Y : N;
   }
   else if( idField == ACCDETLIT::GUARANTEE_ATTR )
   {
      sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::SegClient, strValueOut, idDataGroup );
      strValueOut = (strValueOut == Y && (  hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT ) 
                                            || hasReadPermission( UAF::SEG_FUND_GUARANTEE ) ) )? Y : N;
   }
    else if( idField == ACCDETLIT::RESPINFO_ATTR )
   {
      DString dstrTaxType( NULL_STRING);
      
      strValueOut = N;
      getMFAcctField (rpGICaller, ifds::TaxType, dstrTaxType, false);
      dstrTaxType.strip().upperCase();

      if (dstrTaxType == I_( "9" ) || dstrTaxType == I_( "M" ))
      {
         DString resClient,
            res2Client;

         dynamic_cast <DSTCWorkSession*> (getBFWorkSession())->getOption (ifds::ResClient, resClient, idDataGroup, false);
         dynamic_cast <DSTCWorkSession*> (getBFWorkSession())->getOption (ifds::RES2Client, res2Client, idDataGroup, false);
         strValueOut = (resClient  == Y && hasReadPermission (UAF::RESP_INFO)) || 
                       (res2Client == Y && hasReadPermission (UAF::RESP_ACCOUNT_INFROMATION)) ? Y : N;
      }
   }
   else if( idField == ACCDETLIT::RESP_TRANSACTIONS_ATTR )
   {
      DString dstrTaxType=NULL_STRING;
      getMFAcctField( rpGICaller, ifds::TaxType, dstrTaxType, false);
      dstrTaxType.strip().upperCase();
      bool respAcct = dstrTaxType == I_( "9" ) || dstrTaxType == I_( "M" );

      if( respAcct )
      {
         sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::ResClient, strValueOut, idDataGroup );
      }
      else
      {
         strValueOut = N;
      }
   }
   else if( idField == ACCDETLIT::NEW_ACCOUNT_NUMBER )
   {
      DString globalAccountNum, entityIdSeq1;

      getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, globalAccountNum );
      if( _pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( globalAccountNum, 
                                                                    idDataGroup, entityIdSeq1 ) <= WARNING )
      {
         AccountEntityXref::buildKey( strValueOut, globalAccountNum, I_( "01" ), I_("1"), entityIdSeq1 );
      }
   }
   else if( idField == ACCDETLIT::INITIAL_ENTITY_ID )
   {
      strValueOut = _initialEntityId;
   }
   else if( idField == ACCDETLIT::YTD_CONTRIBUTION_ATTR )
   {
      DString dstrTaxType=NULL_STRING;
      getMFAcctField( rpGICaller, ifds::TaxType, dstrTaxType, false);
      dstrTaxType.strip().upperCase();
      if( dstrTaxType == I_( "1" ) || //RRSP
		  dstrTaxType == I_( "C" ) || //LIRA
		  dstrTaxType == I_( "U" ) || //Locked In RSP
		  dstrTaxType == I_( "CR" ) || //RLSP
		  dstrTaxType == I_( "2" ) || //RRIF
		  dstrTaxType == I_( "B" ) || //LIF
		  dstrTaxType == I_( "L" ) || //LRIF
		  dstrTaxType == I_( "R" ) || //PRIF
		  dstrTaxType == I_( "BR" )) //RLIF
      {
         strValueOut = hasReadPermission( UAF::YTD ) ? Y : N;
      }
      else
      {
         strValueOut = N;
      }
   }
   else if( idField == ACCDETLIT::AS_PENSION_ATTR )
   {
      strValueOut = hasReadPermission( UAF::AS_PENSION_PLAN ) ? Y : N;
   }
   else if( idField == ACCDETLIT::FULL_TRANS_LIST )
   {
      strValueOut = flagAllFunds ? Y : N;
   }
   else if( idField == ACCDETLIT::HYPOTHETICAL_REDEMPTION_ATTR )
   {
      strValueOut = hasReadPermission( UAF::HYPOTHETICAL_REDEMPTION ) ? Y : N;
   }
   else if( idField == ACCDETLIT::ACCOUNTREVIEW )
   {
      DString dstrReviewDateFlag;
      DSTCWorkSession* dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCoOptions *pMgmtCoOptions = dstWorkSession->getMgmtCoOptions();
      if( pMgmtCoOptions )
      {
         pMgmtCoOptions->getField( ifds::ReviewDateFlag, dstrReviewDateFlag, idDataGroup, false );
      }
      strValueOut = ((dstrReviewDateFlag == Y) && hasReadPermission( UAF::ACCOUNTREVIEW )) ? Y : N;
   }
   else if( idField == ACCDETLIT::PENSION_INFO_ATTR )
   {
      strValueOut = hasReadPermission ( UAF::PENSION_INFO ) ? Y : N;
   }
   else if( idField == ACCDETLIT::ESTATEMENT_ATTR )
   {
      strValueOut = hasReadPermission ( UAF::ESTATEMENT ) ? Y : N;
   }
   else if( idField == ACCDETLIT::AMS_OPTION )
   {
      getMFAcctField (rpGICaller, ifds::AcctAMSExist, strValueOut, false);
//    DString dstrAMSCode, dstrAMSROCode;
//    getMFAcctField( rpGICaller, ifds::AMSCode, dstrAMSCode, false);
//    getMFAcctField( rpGICaller, ifds::AMSROCode, dstrAMSROCode, false);
//    strValueOut = ( !dstrAMSCode.empty() || !dstrAMSROCode.empty() ) ? Y : N;
   }
   else if( idField == ifds::FamilyCodeExist )
   {
      getCOAFieldWithInquiryPermission( rpGICaller, IFASTBP_PROC::SHAREHOLDER_CBO, idField, UAF::SHR_FAMILY, strValueOut );
   }
   else if( idField == ifds::ProtContractExists )
   {
      if( !hasReadPermission ( UAF::PROTECTED_FUND_ACCT_CONTRACT ) )
         strValueOut = N;
   }
   else if (idField == ACCDETLIT::ACCTCATEGORY_DESC)
   {
      strValueOut = NULL_STRING;
      MFAccount* pMFAccount (NULL);
      AcctCategoryList* pAcctCategoryList (NULL);

      if (const_cast < AccountDetailsProcess *> ( this )->getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING)
      {
         if ( pMFAccount->getAcctCategoryList (pAcctCategoryList, idDataGroup, true, true) <= WARNING &&
              pAcctCategoryList)
         {
            BFObjIter iter1(const_cast<AcctCategoryList &>(*pAcctCategoryList), getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
            while (!iter1.end())
            {
               DString acctCategory,
                  acctCategoryCode;

               iter1.getObject()->getField (ifds::AcctCategory, acctCategory, idDataGroup, true);
               iter1.getObject()->getField (ifds::AcctCategory, acctCategoryCode, idDataGroup, false);
               if (!strValueOut.empty())
               {
                  strValueOut += I_(";");
               }
               if (acctCategoryCode == ACCOUNT_CATEGORY::PRIVATE)
               {
                  DString pendingPrivate;
                     
                  pMFAccount->getField (ifds::PendingPrivate, pendingPrivate, idDataGroup, false);
                  if (pendingPrivate == I_("Y"))
                  {
                     acctCategory = I_("Pending ") + acctCategory; //not very good to hardcode...deal with it later
                  }
               }
               if (acctCategoryCode == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD || 
                   acctCategoryCode == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD )
               {
                  DString acctValue;
                  iter1.getObject()->getField (ifds::CatValue, acctValue, idDataGroup, true);
                  if (!acctValue.strip().empty())
                  {
                     acctCategory += I_("/") + acctValue;
                  }
               }

               strValueOut += acctCategory;
               ++iter1;
            }
         }
      }
   }
   else if( idField == ACCDETLIT::FEEMODEL_ATTR )
   {
      strValueOut = hasReadPermission ( UAF::ACCOUNT_FEE_MODEL ) ? Y : N;
   }
   else if( idField == ACCDETLIT::ACCT_SETTLE_RULE )
   {
      strValueOut = hasReadPermission ( UAF::ACCT_LEVEL_SETTLEMENT_RULE ) ? Y : N;
   }
   else if( idField == ACCDETLIT::HAS_ACCT_OWNERSHIP_RECORD )
   {
      strValueOut = N;
      MFAccount* pMFAccount (NULL);

      if (const_cast < AccountDetailsProcess *> ( this )->getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING &&
          pMFAccount )
      {
         strValueOut = pMFAccount->hasAcctOwnershipAllocationRecord( BF::HOST ) ?
                       Y : N;
      }
   }
   else if (idField == ifds::AlertViewed)
   {
       MFAccount* pMFAccount = NULL;
       if (const_cast < AccountDetailsProcess *> ( this )->getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING &&
           pMFAccount )
       {
           strValueOut = pMFAccount->getAlertViewedFlag() ? I_("Y"):I_("N");
       }
   }
   else
   {
      strValueOut = NULL_STRING;
   }
}

//******************************************************************************
bool AccountDetailsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;

   if( rpGICaller->getCommand().getKey() == CMD_GUI_ACCOUNT_DETAILS )
   {  //reset the containers
      setContainer (IFASTBP_PROC::ENTITY_LIST, NULL);
      setContainer (IFASTBP_PROC::ACCOUNT_DETAILS_LIST, NULL);
   }
   return bRtn;
}

//******************************************************************************
bool AccountDetailsProcess::doModelessChildComplete( const Command &cmd )
{
   if( cmd.getKey() == CMD_GUI_ACCOUNT_DETAILS )
      return true ;            // All done, ready to be self destructed
   else
   {
      setParameter( I_( "CloseChild" ), Y );
      if( cmd.getKey() == CMD_BPROC_ENTITY  || 
          cmd.getKey() == CMD_BPROC_ADDRESSES ||
          cmd.getKey() == CMD_BPROC_ACCINFO)
      {
         setContainer (IFASTBP_PROC::ENTITY_LIST, NULL);
         setContainer (IFASTBP_PROC::ACCOUNT_DETAILS_LIST, NULL);
      }
      _rpChildGI->refresh (this, cmd.getKey().c_str());
      return false;
   }
}

//******************************************************************************
void AccountDetailsProcess::getCOAFieldWithInquiryPermission( const GenericInterface *rpGICaller,
                                                              const BFContainerId& idList, 
                                                              const BFFieldId& idField, 
                                                              const I_CHAR* userAccessFunctionCode, 
                                                              DString& strValue ) const
{
   // Make non const pointer for calls to non-const methods
   AccountDetailsProcess *rpNonConstThis = const_cast < AccountDetailsProcess *> ( this );

   //look first into the user access permision list
   if( !hasReadPermission( userAccessFunctionCode ) )
   {
      strValue = N;
   }
   else
   {
      BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( idList, getDataGroupId() );
      //get the actual value of the field based on the COA transaction (from the CBO)
      rpPtr ->getField( idField, strValue, getDataGroupId() );
   }
}

//******************************************************************************
void *AccountDetailsProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY sevRtn1 = NO_CONDITION;

   try
   {
      if (IFASTBP_PROC::ACCOUNT_DETAILS_LIST == idContainer)
      {
         _pAccountEntityXref = NULL;
         if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getAccountEntityXref (BF::HOST, _pAccountEntityXref) <= WARNING)
         {
            if (_searchCode == SEARCHACCOUNTUSING::CIF || 
                _searchCode == SEARCHACCOUNTUSING::HOUSEHOLD)
            {
               //if this comes from search by CIF send the last param Y to the back-end
               sevRtn = _pAccountEntityXref->PopulateWhereUsed (EntityIdPos, I_("01"), I_("N"), NULL_STRING, I_("Y"));
            }
            else
            {
               //Incident# 530756
               //we only want the account owners...this was anyhow filtered thru the getfirstkey, getnextkey,
               //but it frezees DSK if lots of where used records are attached to 'entityIdPos'
               sevRtn = _pAccountEntityXref->PopulateWhereUsed (EntityIdPos, I_("01"));
            }
            if (sevRtn <= WARNING)
               ptr = _pAccountEntityXref;
         }
      }
      else if( IFASTBP_PROC::ENTITY_LIST == idContainer )
      {
         {
            _pAccountEntityXref = NULL;
            sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getAccountEntityXref( BF::HOST, _pAccountEntityXref );
            if( WARNING >= sevRtn )
            {
               if( _newAccountNumber.empty() )
                  ptr = _pAccountEntityXref;
               else
               {
                  if( _pAccountEntityXref->PopulateAccountOwner(idDataGroup, NULL_STRING, _newAccountNumber) <= WARNING )
                     ptr = _pAccountEntityXref;
               }         
            }
         }
      }
      else if( IFASTBP_PROC::ENTITY_IDS_LIST == idContainer )
      {
         {
            _pEntityIdsList = NULL;
            Entity *pEntity;
            AccountEntityXrefObject *pAccEntObj = NULL;
            SEVERITY sevRtn = SEVERE_ERROR;
            DString entityId;
            pAccEntObj = dynamic_cast<AccountEntityXrefObject*>(getCBOItem(IFASTBP_PROC::ENTITY_LIST, idDataGroup));
            if( pAccEntObj )
               pAccEntObj->getField(ifds::EntityId, entityId, idDataGroup, false);
            if( !entityId.empty() )
               sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( BF::HOST, entityId, pEntity );
            if( sevRtn <= WARNING && pEntity )
               pEntity->getEntityIdsList( _pEntityIdsList, getDataGroupId() );
            if( _pEntityIdsList )
               ptr = _pEntityIdsList;
         }
      }
      else if( IFASTBP_PROC::FUNDS_LIST == idContainer )
      {
         MFAccount* pMFAccount;
         _pMFAccountHoldingList=NULL;
         if( getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING )
            if( pMFAccount->getAccountHoldingList(_pMFAccountHoldingList, idDataGroup) <= WARNING )
               ptr = _pMFAccountHoldingList;
      }
      else if( IFASTBP_PROC::TRANSACTIONS_LIST == idContainer )
      {
         MFAccount* pMFAccount;

         if( getCurrentMFAccount(pMFAccount, getDataGroupId())<=WARNING )
         {
            if( flagAllFunds )
            {
               _pAllTransactionsListForOneAccount = NULL;
               pMFAccount->getTransactionsList( _pAllTransactionsListForOneAccount, getDataGroupId(), true );
               if( _pAllTransactionsListForOneAccount )
                  ptr = _pAllTransactionsListForOneAccount;
            }
            else
            {
               _pTransactionsList = NULL;
               //start with an empty list; later on, add holdings as requested by the user
               pMFAccount->getTransactionsList( _pTransactionsList, getDataGroupId(), false, true, true );
               if( _strCurrentFundCode != NULL_STRING && _strCurrentClassCode != NULL_STRING )
               {
                  DString allFunds( I_( "N" ) ),numEntry( THREE_STRING );
                  if( _pTransactionsList )
                     if( _pTransactionsList->anotherAccount(_newAccountNumber, _strCurrentFundCode, _strCurrentClassCode, numEntry, allFunds) <= WARNING )
                        ptr = _pTransactionsList;
               }
               else
               {
                  if( _pTransactionsList )
                     ptr = _pTransactionsList;
               }
            }
         }
      }
      else if( IFASTBP_PROC::PENDING_TRADES_LIST == idContainer )
      {
         MFAccount* pMFAccount;
         _pPendingTradesList = NULL;
         if( getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING )
            if( pMFAccount->getPendingTradesList( _pPendingTradesList, idDataGroup, NUMBER_OF_DISPLAYED_TRADES ) <= WARNING )
               ptr = _pPendingTradesList;
      }
      else if( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         MFAccount* pMFAccount;
         _pShareholder = NULL;
         _dstrShrNum = NULL_STRING;
         if( getCurrentMFAccount(pMFAccount, idDataGroup) <= WARNING )
         {
            pMFAccount->getField(ifds::ShrNum, _dstrShrNum, idDataGroup);
            if( !_dstrShrNum.strip().empty() )
            {
               if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getShareholder(idDataGroup, _dstrShrNum, _pShareholder ) <= WARNING )
                  ptr = _pShareholder;
            }
         }
      }
      else if( IFASTBP_PROC::ADDRESS_LIST == idContainer )
      {
         _pAddressList = NULL;
         _pShareholder = dynamic_cast<Shareholder*>(getCBOItem(IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup));
         if( _pShareholder )
            _pShareholder->getAddressList( _pAddressList, getDataGroupId() );
         if( _pAddressList )
            ptr = _pAddressList;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
// If severity > warning, throw error ??
   return(ptr);
}

//******************************************************************************
void AccountDetailsProcess::getMFAcctField( const GenericInterface *rpGICaller,
                                            const BFFieldId& idField,
                                            DString &strValueOut,
                                            bool bFormatted) const
{
   // Make non const pointer for calls to non-const methods
   AccountDetailsProcess *rpNonConstThis = const_cast < AccountDetailsProcess *> ( this );

   MFAccount *pMFAccount;
   if( rpNonConstThis->getCurrentMFAccount(pMFAccount, getDataGroupId() ) <= WARNING )
      pMFAccount->getField( idField, strValueOut, getDataGroupId(), bFormatted );
}

//******************************************************************************
bool AccountDetailsProcess::doRefresh( GenericInterface *rpGICaller,
                                       const I_CHAR *szOriginalCommand)
{
   bool bRtn = true;
   DString dstrRefreshPendingTrades;
   if( rpGICaller->getCommand().getKey() == CMD_BPROC_TRADES )//new trades were created
   {

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *pMFAcc;
      DString strAccNum;
      getField(rpGICaller, IFASTBP_PROC::ACCOUNT_DETAILS_LIST, ifds::AccountNum, strAccNum, false);
      if( (strAccNum != NULL_STRING) && (dstcWorkSession->getMFAccount( BF::HOST, strAccNum, pMFAcc ) <= WARNING) )
      {
         if( pMFAcc->getPendingTradesList( _pPendingTradesList, getDataGroupId(), NUMBER_OF_DISPLAYED_TRADES ) <= WARNING )
         {
            setContainer( IFASTBP_PROC::PENDING_TRADES_LIST, NULL );
            setContainer( IFASTBP_PROC::PENDING_TRADES_LIST, _pPendingTradesList );
         }
      }
      bRtn = _rpChildGI->refresh( this, I_("NewTradesAdded") );
   }
   else if( rpGICaller->getCommand().getKey() == CMD_BPROC_ACCINFO || rpGICaller->getCommand().getKey() == CMD_BPROC_SHAREHOLDER )
   {
      //account or shareholder updated; need to refresh the current AccountEntityXrefObject
      AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>
                                                          (getCBOItem(IFASTBP_PROC::ACCOUNT_DETAILS_LIST, getDataGroupId()));
      if( pAccountEntityXrefObject )
         pAccountEntityXrefObject->PopulateWhereUsedForAccount(getDataGroupId());
      setParameter( I_( "CloseChild" ), Y );
      bRtn = _rpChildGI->refresh( this, NULL );
   }
   else if( rpGICaller->getCommand().getKey() == CMD_BPROC_SETTLEMENT )
   {
      setContainer( IFASTBP_PROC::TRANSACTIONS_LIST, NULL );
      setContainer( IFASTBP_PROC::FUNDS_LIST, NULL );
      setContainer( IFASTBP_PROC::ENTITY_LIST, NULL ); 
      bRtn = _rpChildGI->refresh( this, I_("FromSettlement") ); 
   }
   else if( rpGICaller->getCommand().getKey() == CMD_BPROC_ADDRESSES )
   {
      MFAccount* pMFAccount = NULL;
      Shareholder* pShareholder = NULL;

      DString strShrNum;

      if( getCurrentMFAccount(pMFAccount, getDataGroupId()) <= WARNING )
      {
         pMFAccount->getField(ifds::ShrNum, strShrNum, getDataGroupId());
         if( !strShrNum.strip().empty() )
         {
            if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getShareholder(getDataGroupId(), strShrNum, pShareholder ) 
               <= WARNING )
            {
               AccountMailingList* pAccountMailingList;
               pShareholder->refreshMe(true);
               pShareholder->getAccountMailingList (pAccountMailingList,getDataGroupId(),true );
            }
         }
      }

      setParameter( I_( "CloseChild" ), Y );
      bRtn = _rpChildGI->refresh( this, NULL );
   }
   else if(rpGICaller->getCommand().getKey() == CMD_BPROC_COA)
   {
       //refersh the Account level COA
       DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
       MFAccount *pMFAccount = NULL;
       if( (_newAccountNumber != NULL_STRING) && 
           (dstcWorkSession->getMFAccount( BF::HOST, _newAccountNumber, pMFAccount ) <= WARNING) && pMFAccount )
        {
          COANavig *pCOANavg = NULL;
          pMFAccount->getAccountLevelCOA(pCOANavg, _newAccountNumber, getDataGroupId() , true);
        }
   }
   else
   {
      setParameter( I_( "CloseChild" ), Y );
      bRtn = _rpChildGI->refresh( this, NULL );
   }

   return(bRtn & AbstractProcess::doRefresh( rpGICaller, szOriginalCommand ));
}

//******************************************************************************
SEVERITY AccountDetailsProcess::getCurrentMFAccount(MFAccount*& pMFAccount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getCurrentMFAccount") );

   SEVERITY sevRtn = SEVERE_ERROR;
   pMFAccount = NULL;
   if( !_newAccountNumber.strip().empty() )
      sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount(idDataGroup, _newAccountNumber, pMFAccount);
   if( !pMFAccount )
      sevRtn = CRITICAL_ERROR;
   return(sevRtn);
}

//******************************************************************************
SEVERITY AccountDetailsProcess::getFundDetailList(FundDetailList*& pFundDetailList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getFundDetailList") );
   pFundDetailList = NULL;
   if( _pFundDetailList )
      pFundDetailList = _pFundDetailList;
   else
   {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getMgmtCo().getFundDetailList( _pFundDetailList )<=WARNING )
         pFundDetailList = _pFundDetailList;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
const BFProperties *AccountDetailsProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                               const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetFieldAttributes") );

   //if( _bPermMultiContract )
   // {
   const BFProperties * pBFProp = NULL;

   if( idField == ifds::DTAType           || 
       idField == ifds::UnclmRetMailStage ||
       idField == ifds::StaleChqStage 
     )
   {
      AccountDetailsProcess *rpNonConstThis = const_cast < AccountDetailsProcess *> ( this );
      DString acctListCurrentItemKey = rpNonConstThis->getCurrentListItemKey( rpGICaller, idContainer ); 
      DString accNum;
      AccountEntityXref::getValueForTag( acctListCurrentItemKey, ACCDETLIT::ACCOUNT_NUMBER_FIELD, accNum );

      MFAccount *pMFAccount;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId(), accNum, pMFAccount );

      if( pMFAccount )
      {
         pBFProp = pMFAccount->getFieldProperties(idField, idDataGroup);
      }

   }
   return(pBFProp);
   // }
   // else
   // return;  
}

//*****************************************************************************
bool AccountDetailsProcess::doSend( GenericInterface *rpGICaller,
                                    const I_CHAR *szMessage) 
{
   DString dstrTag(szMessage);
   if( dstrTag == I_("Lantch AccountDetail") )
   {
      //reset key;
      getParameter( ACCDETLIT::ACCOUNT_NUMBER_FIELD, _newAccountNumber );
      _newAccountNumber.stripLeading( '0' );
      setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _newAccountNumber );

      _rpChildGI->refresh( this, I_("FromdoSend") );
      return(true);
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccDetailsProcess.cpp-arc  $
 * 
 *    Rev 1.197   Aug 10 2012 12:04:10   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.196   Aug 09 2012 14:15:30   dchatcha
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.195   Jul 24 2012 19:11:58   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.194   May 14 2012 04:19:42   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.193   Feb 22 2012 04:52:20   panatcha
 * IN2831230 - Fund limitation update not displaying in option window box
 * 
 *    Rev 1.192   Feb 17 2012 10:04:00   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.191   Feb 16 2012 17:17:46   if991250
 * added commitmentStatus
 * 
 *    Rev 1.190   Feb 13 2012 04:17:30   panatcha
 * P0186486_FN03 - RRIF Annuities
 * 
 *    Rev 1.189   Feb 08 2012 20:40:38   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.188   Jan 19 2012 12:08:48   wp040132
 * Minerva Territory Code changes..
 * 
 *    Rev 1.187   Jan 17 2012 00:31:40   panatcha
 * IN2766093 WO720791 - IWT TIN Validation
 * 
 *    Rev 1.186   Dec 08 2011 14:13:34   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.185   Dec 01 2011 18:04:04   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.184   Nov 28 2011 09:51:38   popescu
 * Synch-up ...2740236 - TIN Validation
 * 
 *    Rev 1.183   Oct 27 2011 07:54:30   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.182   Oct 27 2011 07:27:26   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.181   Oct 21 2011 07:41:48   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.180   Jul 18 2011 20:17:36   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.179   Jul 11 2011 07:36:44   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test.
 * 
 *    Rev 1.178   Jun 29 2011 09:22:34   kitticha
 * PETP0186040 FN01 - MFR Run Date and Calculation Logic.
 * 
 *    Rev 1.177   Jan 31 2011 18:28:32   dchatcha
 * Synch up: P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.176   Jan 19 2011 03:32:54   panatcha
 * Update according to Code Review for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.175   Jan 14 2011 04:40:36   panatcha
 * P0178584_FN01 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.174   Dec 28 2010 00:18:52   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.173   Dec 17 2010 04:21:58   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.172   Nov 10 2010 04:01:26   dchatcha
 * PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
 * 
 *    Rev 1.171   Oct 29 2010 07:18:08   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.170   Oct 29 2010 06:20:36   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.169   Sep 30 2010 10:01:48   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.168   Sep 17 2010 07:24:30   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.167   Apr 09 2010 21:45:44   popescu
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.166   Nov 20 2009 11:42:06   popescu
 * Static Data - entity verify names -linked the web screen
 * 
 *    Rev 1.165   Oct 20 2009 09:41:28   dchatcha
 * IN# 1862560 - R95 - Pending Trade does not show when hitting refresh at processing time.
 * 
 *    Rev 1.164   Jul 09 2009 13:43:40   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.163   Jun 15 2009 00:14:08   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.162   Jun 09 2009 05:26:26   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.161   07 May 2009 18:28:44   popescu
 * Incident 1669561 - entity added through desktop causes an error message
 * 
 *    Rev 1.160   07 May 2009 11:19:12   popescu
 * Incident 1667442 - duplicate accounts displayed in Desktop
 * 
 *    Rev 1.159   27 Mar 2009 16:15:50   kovacsro
 * IN#1338938 - Pershing accounts freezing on iFAST Desktop
 * 
 *    Rev 1.158   25 Mar 2009 14:44:08   kovacsro
 * IN#1625479 - iFAST LUX Desktop Freezes for Pershing Accounts (using BF::HOST as datagroup, whenever possible, reduced the time for Details to pop-up 10 times - from 40 mins to 4 mins) - medium risk code change
 * 
 *    Rev 1.157   24 Mar 2009 11:45:08   popescu
 * Incident 1510492 - removed two fields from subclassing since their are available in vew 61 instead of 4 - this change will save calls to vews 4,69, 43 and 90 for each item in the where used list
 * 
 *    Rev 1.156   10 Mar 2009 16:16:00   sibuhatm
 * The Swift Payment Method issue is fixed in this file.
 * The incident is #IN1585115. The Account Value for the Swift Payment Method is integrated. The Slash issue is resolved.
 * 
 *    Rev 1.155   Jan 12 2009 11:13:08   jankovii
 * IN 1549377 Estate and Death of Notification acct category can only be added by the system
 * 
 *    Rev 1.154   18 Dec 2008 09:45:14   kovacsro
 * IN#1281980 - display the current active address (instead of the most recent)
 * 
 *    Rev 1.153   Dec 16 2008 10:48:56   jankovii
 * Sync up: IN 1511831 - Unclaimed Property -  Stop NFU should appear on Caution Box
 * 
 *    Rev 1.152   Nov 25 2008 11:09:30   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.151   Oct 07 2008 05:57:44   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box) - rework some logic.
 * 
 *    Rev 1.150   Oct 06 2008 07:28:48   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box)
 * 
 *    Rev 1.149   29 Sep 2008 14:00:16   popescu
 * Incident 1425273  - fixes the double display of accounts on the Acc details screen 
 * 
 *    Rev 1.148   Sep 29 2008 07:56:00   wongsakw
 * PET5517 FN71 Unclaimed Property - Return Mail
 * 
 *    Rev 1.147   Sep 22 2008 08:44:46   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.146   Sep 18 2008 16:03:46   jankovii
 * Sync up: IN 1403772 Acc status didn't change to Death after enter death date, etc.
 * 
 *    Rev 1.145   Sep 17 2008 07:11:58   daechach
 * PET0128026 - KYC Phase 2 - Fix crashing after close child screen.
 * 
 *    Rev 1.144   Sep 16 2008 22:42:40   daechach
 * Restore rev. 1.142
 * 
 *    Rev 1.143   Sep 15 2008 07:08:08   daechach
 * PET0128026 - KYC Phase 2 - Fix crashing after close Demographics screen.
 * 
 *    Rev 1.142   Aug 29 2008 09:54:40   daechach
 * in#1355618 - recode fix for 1259584 Gross\net
 * 
 *    Rev 1.141   28 Jul 2008 14:39:00   popescu
 * Incident 1338938 - fixed compile issue
 * 
 *    Rev 1.140   28 Jul 2008 14:26:04   popescu
 * Incident 1338938  - Pershing accounts freezing on iFAST Desktop - removed the code that walks the account xref list and filters it due to the fact the list is being filtered at the view level. the uneccessary iteration would cause Desktop to perform poorly for large broker accounts
 * 
 *    Rev 1.139   Jul 16 2008 10:21:08   jankovii
 * PET 59888 - AML Enhancemement.
 * 
 *    Rev 1.138   05 May 2008 14:50:32   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.137   18 Apr 2008 16:07:18   kovacsro
 * PET2255-FN47 New LIF
 * 
 *    Rev 1.136   Mar 11 2008 19:05:06   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.135   Feb 22 2008 10:13:12   jankovii
 * PET 5517 FN80B -DOT and Addendum.
 * 
 *    Rev 1.134   Feb 20 2008 12:45:02   jankovii
 * PET 5517 FN80B -DOT and Addendum.
 * 
 *    Rev 1.133   Dec 06 2007 19:40:38   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.132   Sep 21 2007 17:58:58   smithdav
 * PET 2360 FN02 - Launch Global AMS screen from AcctDetails for FOF funds.
 * 
 *    Rev 1.131   Sep 18 2007 11:01:18   jankovii
 * IN #1007214 - To show MFR, MF and Invoice model codes.
 * 
 *    Rev 1.130   10 Sep 2007 16:29:34   popescu
 * GAP 2 - 2360 - when search by CIF return all the accounts display all acct owners regardless of the entity sequence
 * 
 *    Rev 1.129   Sep 07 2007 14:15:16   smithdav
 * IN 978610 - add logic to look t the AcctAMSExist flag on the account ro COA display.
 * 
 *    Rev 1.128   28 Aug 2007 16:54:40   popescu
 * Added LinkMFR to caution box
 * 
 *    Rev 1.127   27 Aug 2007 17:08:32   popescu
 * GAP 2 - 2360 - when search by CIF return all the accounts where entities share the same number, and display them.
 * 
 *    Rev 1.126   22 Aug 2007 13:37:06   popescu
 * GAP 6 - search by CIF should return all the entities linked by CIF
 * 
 *    Rev 1.125   Aug 16 2007 10:50:18   kovacsro
 * PET2388FN01 - Swift Payment Method Id
 * 
 *    Rev 1.124   Aug 10 2007 14:12:26   jankovii
 * PET 2360 FN14&FN19 - Management Fee.
 * 
 *    Rev 1.123   Aug 03 2007 11:27:36   smithdav
 * Fix AMS option.
 * 
 *    Rev 1.122   27 Jun 2007 23:58:04   popescu
 * PET 2236 - Gap 50 - Private act
 * 
 *    Rev 1.121   Nov 22 2006 14:02:28   fengyong
 * Incident #764972 - Add reference to FundLimitation from account option box
 * 
 *    Rev 1.120   Jul 04 2006 13:35:50   ZHANGCEL
 * PET2145 FN01 -- Add logic for displaying "Assignee"
 * 
 *    Rev 1.119   Feb 23 2006 11:59:42   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.118   Feb 21 2006 10:27:28   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.117   Feb 01 2006 18:13:34   popescu
 * Incident# 530756 - call view 61 - where used for entity type '01' to display the list of accounts on the account details screen
 * 
 *    Rev 1.116   Nov 30 2005 09:34:00   popescu
 * Incindent# 463650 - a dummy where used record was erroneous sent to back-end
 * 
 *    Rev 1.115   Sep 01 2005 13:19:30   AGUILAAM
 * PET1250_FN07_Fund Merge: support display of active only or all  holdings based on generic control
 * 
 *    Rev 1.114   Jul 06 2005 10:49:28   hernando
 * PET1250 FN01 - Added AcctCutOffTimeExists.
 * 
 *    Rev 1.113   Jun 08 2005 09:42:28   popescu
 * Incident# 328726 - do not create read fields off null pointers - check acct category for null
 * 
 *    Rev 1.112   May 20 2005 11:28:48   georgeet
 * Incident 291298 - Group information are missing from the Account Detail screen.  Added field details for AcctGroup and AcctGroupName fields.
 * 
 *    Rev 1.111   Nov 29 2004 13:13:34   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.110   Nov 17 2004 15:02:54   PURDYECH
 * PET910 - .NET Conversion:  Fixed compiler warning messages.
 * 
 *    Rev 1.109   Nov 11 2004 16:16:18   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.108   Sep 07 2004 10:58:44   FENGYONG
 * uncomment UAF checking after view code ready
 * 
 *    Rev 1.107   Aug 31 2004 17:32:14   FENGYONG
 * change field name
 * 
 *    Rev 1.106   Aug 11 2004 18:39:44   FENGYONG
 * PET 1117 FN05 Syncup after get files resource 
 * 
 *    Rev 1.105   Aug 11 2004 11:58:16   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.104   Jul 29 2004 14:04:14   YINGBAOL
 * PET1124:Add Stop redemption settlement field.
 * 
 *    Rev 1.103   Jul 26 2004 13:51:08   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.102   May 25 2004 22:38:46   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.101   May 25 2004 20:31:56   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.100   May 11 2004 14:26:06   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 * 
 *    Rev 1.99   May 04 2004 20:40:30   HERNANDO
 * PET1027 FN02 - Added HighestEntityRisk.
 * 
 *    Rev 1.98   Apr 05 2004 17:35:30   FENGYONG
 * PET944FN01, release 56.1 NSCC Broker
 * 
 *    Rev 1.97   Nov 27 2003 10:41:10   HERNANDO
 * PET892 FN1 - Added Settlement Location.
 * 
 *    Rev 1.96   Oct 23 2003 17:47:58   FENGYONG
 * Add field DTAType and getFieldAttribute
 * 
 *    Rev 1.95   Oct 16 2003 12:04:50   FENGYONG
 * PET809 FN08 Direct trading enhancement
 * 
 *    Rev 1.94   Sep 10 2003 14:10:32   HERNANDO
 * Sync'd up with 1.91.1.0; PTS 10015486.
 * 
 *    Rev 1.93   Jun 30 2003 10:28:00   HERNANDO
 * Changed AddrStatus to BFTextFieldId.
 * 
 *    Rev 1.92   Jun 04 2003 11:30:02   HERNANDO
 * Added StopAMSRebalancing Field Details.
 * 
 *    Rev 1.91   Apr 02 2003 12:19:02   PURDYECH
 * Code cleanup
 * 
 *    Rev 1.90   Mar 21 2003 17:33:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.89   Mar 14 2003 08:34:50   sanchez
 * Added Fields ChargeSTTRFee and ChargeERFee
 * 
 *    Rev 1.88   Feb 28 2003 14:22:16   PURDYECH
 * Removed unintentional fallthrough in getPtrForContainer
 * 
 *    Rev 1.87   Feb 19 2003 12:36:32   KOVACSRO
 * Tuning for Account category (don't call view 245 if not necessary)
 * 
 *    Rev 1.86   Jan 26 2003 15:27:20   KOVACSRO
 * Added Margin, Loan, ChqPriv, Wrap caution fields.
 * 
 *    Rev 1.85   Jan 25 2003 16:52:42   KOVACSRO
 * Added Account Category
 * 
 *    Rev 1.84   Jan 23 2003 15:54:00   ZHANGCEL
 * Code sync up to 1.77.1.0
 * 
 *    Rev 1.83   Jan 21 2003 13:43:26   HSUCHIN
 * added security to protected contracts
 * 
 *    Rev 1.82   Jan 20 2003 17:21:08   HSUCHIN
 * added account contract process
 * 
 *    Rev 1.81   Jan 15 2003 12:04:50   KOVACSRO
 * Commented out ESOP.
 * 
 *    Rev 1.80   Jan 13 2003 17:54:18   sanchez
 * Shareholder family changes
 * 
 *    Rev 1.79   Jan 12 2003 17:04:22   sanchez
 * shareholder family
 * 
 *    Rev 1.78   Jan 08 2003 12:20:34   sanchez
 * Target Asset Mix implementation.  Added check for AMSROCode.
 * 
 *    Rev 1.77   Jan 03 2003 18:52:52   HSUCHIN
 * added social code to container
 * 
 *    Rev 1.76   Dec 30 2002 10:22:50   sanchez
 *   - Added MgmtFeePayOptionSet the field details
 * 
 *    Rev 1.75   Dec 06 2002 10:55:46   YINGBAOL
 * PRIF enhancement
 * 
 *    Rev 1.74   Nov 19 2002 14:30:44   KOVACSRO
 * Added FirstSettleDate field.
 * 
 *    Rev 1.73   Nov 19 2002 14:24:08   HERNANDO
 * Removed AMS_DETAILS UAF.
 * 
 *    Rev 1.72   Nov 06 2002 14:35:34   HERNANDO
 * Added AMS Option.
 * 
 *    Rev 1.71   Nov 06 2002 10:35:38   YINGBAOL
 * Sync. up changes in release 49
 * 
 *    Rev 1.70   Oct 09 2002 23:52:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.69   Sep 11 2002 16:31:08   WINNIE
 * Add reveral field to fix the crash due to changes made in BaseAcctDetailDlg.cpp
 * 
 *    Rev 1.68   09 Sep 2002 15:16:18   HUANGSHA
 * added doGetField of eStatement Permission
 * 
 *    Rev 1.67   Aug 29 2002 16:42:30   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.66   Aug 29 2002 12:54:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.65   Aug 08 2002 15:08:26   HSUCHIN
 * added field detail pensionjurisexists
 * 
 *    Rev 1.64   Jul 08 2002 15:50:12   ZHANGCEL
 * Added a field : SeqNum to sove the problem of displaying "0.0000" instead of "Settled" underneath the Banance column
 * 
 *    Rev 1.63   Jun 14 2002 17:30:16   ZHANGCEL
 * Changed the logic in the getField() for lunching RIF_LIF_LRIF_Info screen
 * 
 *    Rev 1.62   07 Jun 2002 18:40:46   HERNANDO
 * Checks ReviewDateFlag for Account Review.
 * 
 *    Rev 1.61   Jun 02 2002 18:25:34   HSUCHIN
 * added pension info
 * 
 *    Rev 1.60   31 May 2002 13:28:42   HERNANDO
 * Added Account Review.
 * 
 *    Rev 1.59   May 30 2002 11:00:22   KOVACSRO
 * Added BankCharges and ConsolidateEFT
 * 
 *    Rev 1.58   22 May 2002 18:23:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.57   May 03 2002 11:25:18   YINGBAOL
 * add FundTo to PENDING_TRADES_LIST----PTS 10008082
 * 
 *    Rev 1.56   27 Mar 2002 19:54:24   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.55   Mar 19 2002 09:48:28   YINGBAOL
 * Add AppyPST
 * 
 *    Rev 1.54   26 Feb 2002 16:53:10   HSUCHIN
 * added hypothetical redemption permission check
 * 
 *    Rev 1.53   Feb 19 2002 14:08:24   YINGBAOL
 * add Feeparameter
 * 
 *    Rev 1.52   15 Feb 2002 14:25:48   KOVACSRO
 * code clean up
 * 
 *    Rev 1.51   11 Feb 2002 16:40:38   KOVACSRO
 * syncup - Showing the active registration address rather than the first one in the list.
 * 
 *    Rev 1.50   Feb 04 2002 15:43:28   JANKAREN
 * Added GSTExempt
 * 
 *    Rev 1.49   27 Dec 2001 13:51:46   KOVACSRO
 * refreshing ACCOUNT DETAILS List when AccInfo or ShareholderDetails is closed.
 * 
 *    Rev 1.48   03 Dec 2001 13:00:58   KOVACSRO
 * bug fixed.
 * 
 *    Rev 1.47   28 Nov 2001 14:33:38   KOVACSRO
 * Tunning:
 * 1. Changed the way AccountEntity is populated (lazy init)
 * 2. Getting some fields from view 61, rather than view 4.
 * 
 *    Rev 1.46   23 Nov 2001 11:26:20   KOVACSRO
 * bug fixed in getFirst and NextListItemKey.
 * 
 *    Rev 1.45   20 Nov 2001 16:45:24   KOVACSRO
 * Lazy init for TransactionList (only when a fund/class' transactions are needed, we'll call view 17)
 * 
 *    Rev 1.44   19 Nov 2001 11:20:36   KOVACSRO
 * re-designed for lazy init.
 * 
 *    Rev 1.43   26 Oct 2001 11:07:38   SMITHDAV
 * hasPermission changes
 * 
 *    Rev 1.42   24 Oct 2001 11:46:20   HSUCHIN
 * undo last changes for YTD
 * 
 *    Rev 1.41   22 Oct 2001 13:09:32   HSUCHIN
 * change YTD attribute to be displayed for TaxType 1,3,4,C,H
 * 
 *    Rev 1.40   Sep 18 2001 08:37:52   JANKAREN
 * Added permission for As Pension Plan
 * 
 *    Rev 1.39   13 Sep 2001 17:55:16   HSUCHIN
 * added security check for Account Level split commission
 * 
 *    Rev 1.38   03 Sep 2001 13:24:32   HSUCHIN
 * added new fielddetails AcctCommExists
 * 
 *    Rev 1.37   Aug 23 2001 12:37:34   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.36   18 Aug 2001 09:27:26   HSUCHIN
 * added YTD and Foreign content rebalancing
 * 
 *    Rev 1.35   16 Aug 2001 10:09:06   KOVACSRO
 * Added ESoP screen.
 * 
 *    Rev 1.34   Aug 09 2001 15:13:48   HUANGSHA
 * Added field Currency
 * 
 *    Rev 1.33   Jul 31 2001 09:39:20   YINGBAOL
 * fix RESP display issue
 * 
 *    Rev 1.32   Jul 29 2001 15:06:18   YINGBAOL
 * fix currency display issue
 * 
 *    Rev 1.31   Jul 16 2001 19:08:36   OLTEANCR
 * added access to multicontract screen
 * 
 *    Rev 1.30   14 Jun 2001 11:58:02   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.29   05 Jun 2001 16:06:00   YINGZ
 * for others to compile
 * 
 *    Rev 1.28   Jun 04 2001 10:23:36   ZHANGCEL
 * Fixed the bug regarding "RESP Account Information" Showing up in the Attribute column.
 * 
 *    Rev 1.27   15 May 2001 15:37:40   YINGZ
 * data group id clean up
 * 
 *    Rev 1.26   03 May 2001 14:05:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.25   Apr 03 2001 09:40:56   JANKAREN
 * Bug fix
 * 
 *    Rev 1.24   Mar 12 2001 10:25:46   JANKAREN
 * Add AddFieldDetails(DBR::OfferPrice)
 * 
 *    Rev 1.23   Feb 23 2001 13:48:32   YINGBAOL
 * use FieldCode instead of Desc. M3 sync.
 * 
 *    Rev 1.22   21 Feb 2001 18:12:26   KOVACSRO
 * Implemented Birthdate/Age
 * 
 *    Rev 1.21   Feb 07 2001 13:48:16   KOVACSRO
 * quick fix.
 * 
 *    Rev 1.20   Feb 05 2001 10:49:38   JANKAREN
 * Sync up C2/C3 - add BirthdateAge
 * 
 *    Rev 1.19   30 Jan 2001 15:16:44   PURDYECH
 * Created a static const DString object at file scope to be returned from getNextListItemKey when a NULL return is required.
 * 
 *    Rev 1.18   Jan 24 2001 13:04:44   KOVACSRO
 * modifications in refresh().
 * 
 *    Rev 1.17   Jan 17 2001 10:27:54   KOVACSRO
 * Added REFRESH_PENDING_TRADES param. and modified doRefresh(); Show max. 3 pending trades, even if there are more...
 * 
 *    Rev 1.16   Jan 08 2001 10:11:24   ZHANGCEL
 * Synchronized to C2/C3: Fixed permission check bug for PAC,SEP,AT,DEFAULT; deal with RRIF and TaxType, PlanType stuffs
 * 
 *    Rev 1.15   15 Dec 2000 12:43:16   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.14   Nov 29 2000 14:52:54   ZHANGCEL
 * Removed two ShareHolder fields: Name1 and Namew
 * 
 *    Rev 1.13   Nov 28 2000 16:55:22   ZHANGCEL
 * added two shareHolder fields: Name1 and Name2 into the SHAREHOLDER_CBO
 * 
 *    Rev 1.12   Oct 26 2000 12:25:52   KOVACSRO
 * Implemented 'doRefresh'
 * 
 *    Rev 1.11   Oct 05 2000 13:20:22   YINGBAOL
 * check PlanType instead of TaxType for RRIF
 * 
 *    Rev 1.10   Aug 02 2000 15:31:54   BUZILA
 * "locale" changes
 * 
 *    Rev 1.9   Jul 28 2000 16:39:30   ZHANGCEL
 * Added Baycom for C2 fund number stuffs
 * 
 *    Rev 1.8   Jul 19 2000 10:47:22   WINNIE
 * Filter Contract, RESP, Gurantee Attribute on account defail screen according to the taxtype, system features and permission
 * 
 *    Rev 1.7   Apr 14 2000 09:49:44   ZHANGCEL
 * Change doGetField
 * 
 *    Rev 1.6   Apr 04 2000 16:43:30   DT24433
 * changed to use GI's hasPermission
 * 
 *    Rev 1.5   Mar 21 2000 11:34:00   YINGBAOL
 * adde RRIF LIF Dialog
 * 
 *    Rev 1.4   Mar 13 2000 15:29:20   DT24433
 * misc. changes
 * 
 *    Rev 1.3   Mar 09 2000 14:30:52   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.2   Mar 07 2000 15:15:26   DT24433
 * removed substitute lists, changed getReadOnlyGroupID calls to getGroupID
 * 
 *    Rev 1.1   Feb 28 2000 15:31:06   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.69   Feb 08 2000 10:32:48   POPESCUS
 * fix for refreshing the acct
 * 
 *    Rev 1.68   Feb 02 2000 18:09:26   BUZILA
 * changes
 * 
 *    Rev 1.67   Feb 02 2000 16:03:14   VASILEAD
 * Moved PopulateAccountOwner at AccDetailsProcess
 * 
 *    Rev 1.66   Jan 28 2000 15:08:06   VASILEAD
 * Fixed diplaying Kana addresses
 * 
 *    Rev 1.65   Jan 23 2000 21:12:26   POPESCUS
 * Refresh fix
 * 
 *    Rev 1.64   Jan 22 2000 15:21:56   POPESCUS
 * fix in refresh and reset the containers
 * 
 *    Rev 1.63   Jan 21 2000 17:49:14   VASILEAD
 * Refresh stuff
 * 
 *    Rev 1.62   Jan 12 2000 08:57:26   POPESCUS
 * changes related to cloning an account and fixing some validation, adding subst sets
 * 
 *    Rev 1.61   Jan 08 2000 14:32:52   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.60   Jan 06 2000 09:57:54   POPESCUS
 * cleanup code and remove some unused methods
 * 
 *    Rev 1.59   Dec 29 1999 18:11:12   BUZILA
 * changed COA flags
 * 
 *    Rev 1.58   Dec 24 1999 10:31:02   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.57   Dec 23 1999 11:29:02   POPESCUS
 * NASU process and the new confirmation model
 * 
 *    Rev 1.56   Dec 21 1999 10:40:24   VASILEAD
 * Added Entity list iteration based on the string keys and not on the ObjectKey
 * 
 *    Rev 1.55   Dec 10 1999 11:58:32   VASILEAD
 * Added refresh support
 * 
 *    Rev 1.54   Dec 09 1999 13:09:22   POPESCUS
 * set the account num to the new accountentityXref object when is new
 * 
 *    Rev 1.53   Dec 08 1999 14:00:20   POPESCUS
 *  the entity ids list is now a child list of entity being set in the object map
 * 
 *    Rev 1.52   Dec 06 1999 16:35:00   VASILEAD
 * Biult the keys at the CBO level
 * 
 *    Rev 1.51   Dec 01 1999 19:54:22   VASILEAD
 * Stuff
 * 
 *    Rev 1.50   Dec 01 1999 14:55:18   VASILEAD
 * Fixed bug on deleting entities
 * 
 *    Rev 1.49   Nov 30 1999 18:24:44   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.48   Nov 29 1999 15:21:36   VASILEAD
 * Reset the iters when you do refresh
 * 
 *    Rev 1.47   Nov 29 1999 09:53:48   VASILEAD
 * Added business/edits for Entity screen
 * 
 *    Rev 1.46   Nov 25 1999 15:54:08   VASILEAD
 * Added new conditions
 * 
 *    Rev 1.45   Nov 25 1999 11:41:56   POPESCUS
 * Cleaned up the code a bit 
 * 
 *    Rev 1.44   Nov 21 1999 14:53:46   VASILEAD
 * added NON_DE:ETED to the list iterators.
 * 
 *    Rev 1.43   Nov 21 1999 13:34:36   VASILEAD
 * added new features
 * 
 *    Rev 1.42   Nov 18 1999 16:12:54   YINGBAOL
 * split view 43 sysnc
 * 
 *    Rev 1.41   Nov 13 1999 16:13:46   VASILEAD
 * ??
 * 
 *    Rev 1.40   Nov 13 1999 16:07:18   VASILEAD
 * ?
 * 
 *    Rev 1.39   Nov 11 1999 17:53:58   VASILEAD
 * Changed to the new AccountEntityXref list
 * 
 *    Rev 1.38   Nov 10 1999 11:21:18   VASILEAD
 * Defined GETVALUEFORTAG
 * 
 *    Rev 1.37   Nov 09 1999 16:53:38   VASILEAD
 * Changed to AccountEntityXref
 * 
 *    Rev 1.36   Nov 02 1999 16:02:54   PRAGERYA
 * getPtrForContainer parameter list changed
 * 
 *    Rev 1.35   Nov 02 1999 10:44:32   YINGBAOL
 * fix
 * 
 *    Rev 1.34   Nov 02 1999 10:27:10   YINGBAOL
 * sync selection
 * 
 *    Rev 1.33   Nov 01 1999 14:05:22   YINGBAOL
 * modify flag
 * 
 *    Rev 1.32   Nov 01 1999 14:02:08   YINGBAOL
 * Move AddressList from MFAccount to Shareholder
 * 
 *    Rev 1.31   Oct 28 1999 17:14:46   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.30   Oct 24 1999 16:26:54   VASILEAD
 * Sync up with M2
 * 
 *    Rev 1.29   Oct 05 1999 09:46:54   HUANGSHA
 * Set focus on the selected entity if search for the AltAccount + BrokerCode
 * 
 *    Rev 1.28   Sep 30 1999 13:32:52   VASILEAD
 * Added fields in the process
 * 
 *    Rev 1.27   Sep 28 1999 14:14:34   VASILEAD
 * Corrected some issues regarding the Currency field
 * 
 *    Rev 1.26   Sep 26 1999 18:29:24   VASILEAD
 * Added support for AllFunds mode in transactions screen
 * 
 *    Rev 1.25   Sep 23 1999 17:15:14   VASILEAD
 * Defined InterCode and InterAccount fields
 * 
 *    Rev 1.24   Sep 21 1999 14:20:22   VASILEAD
 * Added functionality for All funds check box in Details screen
 * 
 *    Rev 1.23   Sep 20 1999 11:28:58   VASILEAD
 * Changes to implement C1 requirements
 * 
 *    Rev 1.22   Sep 17 1999 07:12:18   DT24433
 * changed for new parm to getGroupID and now using getGroupID
 * 
 *    Rev 1.21   Sep 16 1999 09:14:22   YINGZ
 * test substitution list
 * 
 *    Rev 1.20   Sep 14 1999 14:17:06   PRAGERYA
 * BankingInstr
 * 
 *    Rev 1.19   Sep 14 1999 14:16:04   PRAGERYA
 * New field
 * 
 *    Rev 1.18   Sep 14 1999 11:47:16   BUZILA
 * BFBase changes
 * 
 *    Rev 1.17   Sep 03 1999 14:34:50   YINGZ
 * add listview 
 * 
 *    Rev 1.16   Sep 01 1999 16:34:34   DT24433
 * removed dead code
 * 
 *    Rev 1.15   Aug 31 1999 10:55:56   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.14   Aug 26 1999 09:51:20   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.13   Aug 20 1999 11:21:22   DT24433
 * finished removing FieldDetails array
 * 
 *    Rev 1.12   Aug 10 1999 10:51:10   DT24433
 * change to addFieldDetails and addContainer
 * 
 *    Rev 1.11   Aug 05 1999 14:39:00   VASILEAD
 * Add multicurrency support
 * 
 *    Rev 1.10   Aug 04 1999 20:55:16   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.9   Jul 27 1999 16:29:26   VASILEAD
 * When a child dialog is killed the focus goes to parent
 * 
 *    Rev 1.8   Jul 22 1999 17:31:54   VASILEAD
 * Fixed two different mask support for Amount field
 * 
 *    Rev 1.7   Jul 20 1999 11:13:30   VASILEAD
 * New conditions update
 * 
 *    Rev 1.6   Jul 19 1999 12:45:54   VASILEAD
 * double mask for Amount field
 * 
 *    Rev 1.5   Jul 16 1999 17:31:54   VASILEAD
 * blah blah
 * 
 *    Rev 1.4   Jul 16 1999 13:02:58   VASILEAD
 * Double mask for the Amount field
 * 
 *    Rev 1.3   Jul 14 1999 16:44:08   VASILEAD
 * Implemeted two different masks for the same field
 * 
 *    Rev 1.2   Jul 09 1999 15:33:34   VASILEAD
 * Bug fixes
 * 
 *    Rev 1.1   Jul 08 1999 10:01:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
