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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransHistoryProcess.cpp
// ^AUTHOR :  Zijian Ying
// ^DATE   : 03/20/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransHistoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "transhistoryprocess.hpp"
#include "transhistoryprocessincludes.h"

#include <ifastcbo\deductionlist.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionexternallinkslist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\transdecimalslist.hpp>
#include <ifastcbo\transactionupdate.hpp>


#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANS_HISTORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANSACTION_EXTERNAL_LINKS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_AUTHORIZATION; 
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BATCH; 
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PAYMENT_INFO_FLAG;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransHistoryProcess > processCreator( CMD_BPROC_TRANS_HISTORY );
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT;

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TransHistoryProcess" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );

   const I_CHAR *pALLFUND               = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM            = I_( "AccountNum" );
   const I_CHAR *pTRANSID               = I_( "TransId" );
   const I_CHAR *pSHAREHOLDERNUM        = I_( "ShareholderNum" );
   const I_CHAR *pFUNDCODE              = I_( "FundCode" );
   const I_CHAR *pCLASSCODE             = I_( "ClassCode" );
   const I_CHAR *pNUMENTRY              = I_( "NumEntry" );
   const I_CHAR *pPENDING               = I_( "Pending" );
   const I_CHAR *pTRANSTYPE             = I_( "TransType" );
   const I_CHAR *pTRANSNUM              = I_( "TransNum" );
   const I_CHAR *pTRADEDATE             = I_( "TradeDate" );
   const I_CHAR *pENTITYID              = I_( "EntityID" );
   const I_CHAR *pREQTRANSID            = I_( "ReqTransid" );
   const I_CHAR *pINQUIRYONLY           = I_( "InquiryOnly" );
   const I_CHAR *pWIREORDER             = I_( "WireOrdNum" );

   //the value of maxRepeatCount for view No. 53 - if back end modifies it, have to change here
   const int MAX_REPEAT_COUNT           = 25;

   const I_CHAR *BEL                   = I_( "BEL" );
   const I_CHAR *pPENDINGTRADE         = I_( "PendingTrade" );
   const I_CHAR *DISABLEINVINFO        = I_( "DisableInvInfo" );
   const I_CHAR *STARTREBOOK           = I_( "StartRebook" );
   const I_CHAR *TXNLEVELSEC           = I_( "TxnLevelSec" );
   const I_CHAR *pGROSSNETMETHOD       = I_( "GrossNetMethod" );
   const I_CHAR *pPENDPROCRECORD_TYPE  = I_( "PendProcRecordType" );
   const I_CHAR *pOKCancel	           = I_( "OkCancel" );
   const I_CHAR * const CLIENT                     = I_( "1" );
   const I_CHAR * const INDC90                     = I_( "90" );
   const I_CHAR * const INDC                       = I_( "INDC" );
   const I_CHAR * const BLOCK                      = I_( "B" );
   const I_CHAR * const NO                         = I_( "N" );
   const I_CHAR * const PW                         = I_( "PW" );  // Hybrid Redemption
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ValidDateLag;
   extern CLASS_IMPORT const BFTextFieldId TransHistDeductDetailHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId TransactionExtLinksHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId Cancellation;
   extern CLASS_IMPORT const BFTextFieldId SWPSettleESGElig;
   extern CLASS_IMPORT const BFTextFieldId PayInstrOption;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId LinkedEntityName;
   extern CLASS_IMPORT const BFTextFieldId PendProcRecordType;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFDateFieldId ExpectedSettleDate;
   extern CLASS_IMPORT const BFDateFieldId CancelGrant;
   extern CLASS_IMPORT const BFTextFieldId IsCancelModSEGTradeAllowed;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId SDRTExemptCode;
   extern CLASS_IMPORT const BFTextFieldId PymtRoutingMthd;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId ToTDCC;
   extern CLASS_IMPORT const BFTextFieldId ToValoren;
   extern CLASS_IMPORT const BFTextFieldId TradeRestriction;
   extern CLASS_IMPORT const BFTextFieldId TradeRestrictionReason;
   extern CLASS_IMPORT const BFTextFieldId IsEPATrade;
   extern CLASS_IMPORT const BFTextFieldId EnableTradeAuthorization;
   extern CLASS_IMPORT const BFTextFieldId EnableTradeRestrictionFields;
   extern CLASS_IMPORT const BFTextFieldId SourceOfTrade;
   extern CLASS_IMPORT const BFTextFieldId ChannelOfTrade;
   extern CLASS_IMPORT const BFTextFieldId Platform;
   extern CLASS_IMPORT const BFNumericFieldId CrossSysAcctNum;
   extern CLASS_IMPORT const BFTextFieldId AggregationType;
   extern CLASS_IMPORT const BFTextFieldId ExternalInstitution;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFTextFieldId OrderRouting;
   extern CLASS_IMPORT const BFTextFieldId OrigGrossNet;
   extern CLASS_IMPORT const BFTextFieldId PricingCode;
   extern CLASS_IMPORT const BFTextFieldId ComponentSplit;   
   extern CLASS_IMPORT const BFTextFieldId PriceInCode;
   extern CLASS_IMPORT const BFTextFieldId FullMoneyOutIndc;
   extern CLASS_IMPORT const BFTextFieldId GateOverrideIndicator;
   extern CLASS_IMPORT const BFDateFieldId RDSPPaymtDate;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const DSC_REDEMPTION;
}

namespace MFCAN_IP_PARAM
{
    extern const I_CHAR * const CALLER;
    extern const I_CHAR * const EXTERNAL_TRANS_NUM;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319TransHistoryProcess::TransHistoryProcess() : 
TransHistoryProcess::TransHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, //   _pPendingTradeList( NULL),
//   _pDeductionList (NULL),
_pTransHistoryList( NULL ),
_rpChildGI( NULL ),
_pTransactionExternalLinksList( NULL ),
_CallPendigTradeDetails (I_("Y")),
_pTransDecimalsList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::TRANS_LIST,         true );
   addContainer( IFASTBP_PROC::DEDUCTION_LIST,     true );
   addContainer( IFASTBP_PROC::FUND_MASTER_LIST,   true );
   addContainer( IFASTBP_PROC::FUND_DETAIL_LIST,   true );
   addContainer( IFASTBP_PROC::FUND_LIST,          true );
   addContainer( IFASTBP_PROC::PENDING_LIST,       true );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,      false);
   addContainer( IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST, true );
   addContainer( IFASTBP_PROC::TRANS_FEE_LIST,     true, IFASTBP_PROC::PENDING_LIST,   false );
   addContainer( IFASTBP_PROC::TRANS_DECIMALS,     true, IFASTBP_PROC::TRANS_LIST,     false );
   addContainer( IFASTBP_PROC::TRANSACTION_UPDATE, false,BF::NullContainerId, true,  I_("TransactionUpdate") );

// from list vw 17
   addFieldDetails( ifds::TransId,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransType,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransTypeDesc,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleDate,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ModDate,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Settled,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::GrossAmt,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NetAmt,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::UnitPrice,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Units,               IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::UnitBalance,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Cancelled,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Reversal,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PayType2,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PayTypeDesc,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderBatch,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderTrace,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderUser,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelBatch,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelTrace,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CancelUser,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleBatch,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleTrace,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleUser,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::VerifiedBy,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrAcct,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrFund,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TfrClass,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OfferPrice,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::LSIFCode,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::HRDCRespPending,     IFASTBP_PROC::TRANS_LIST );

// from cbo vw22
   addFieldDetails( ifds::OrderType,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NSCCControlNumber,   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::WireOrdNum,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BrokerCode,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BranchCode,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SalesRepCode,        IFASTBP_PROC::TRANS_LIST );
// addFieldDetails( DBR::TfrAcct, IFASTBP_PROC::TRANS_LIST );
// addFieldDetails( DBR::TfrFund, IFASTBP_PROC::TRANS_LIST );
// addFieldDetails( DBR::TfrClass, IFASTBP_PROC::TRANS_LIST );
   //addFieldDetails( ifds::GrossNetMethod,      IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::GrossOrNet,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DepositType,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DepositTypeDesc,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RedCode,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RedCodeDesc,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RvCode,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RvCodeDesc,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PartFull,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PrevUnitBal,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Commission,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::HoldBackAmt,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::HoldBackRate,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OverrideDSCDesc,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OverrideAmt,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SharesElig,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PartnerShip,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ProvSales,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DepositDate,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CashDate,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DealDate,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DealTime,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SetGrossAmt,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SetNetAmt,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleCurrency,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExchRate,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ConfIssued,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RecptIssued,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SrcOfFund,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SrcOfFundDesc,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SrcOfAccount,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderSource,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderSrcDesc,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleSource,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleSrcDesc,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleType,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettleTypeDesc,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettledBy,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SettledByDesc,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ChqSupCode,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ChqSupCodeDesc,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ConfirmReq,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CertRequired,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OnStmt,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RoundFlag,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SeqNum,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Accountable,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AcctableDesc,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BrokerName,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BranchName,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SlsrepName,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SlsrepAltName,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Remarks1,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Remarks2,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Remarks3,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ProcessDate,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Allocation,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Initial,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::GroupCode,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BackDatedReason,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::GBCD,                IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FeePercent,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PostUnsettled,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Indc,                IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExpSetlGN,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DepositId,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SplitComm,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransferTransId,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Grp1Shares,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Grp2Shares,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::G1Impact,            IFASTBP_PROC::TRANS_LIST );//anne
   addFieldDetails( ifds::G2Impact,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::EqualFactor,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::EqualAmount,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::EqualAmtCurrency,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ValueDate,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ACHProcessor,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PayMethod,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BankChrgs,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FedRate,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OverrideTax,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AcctLevelTax,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransRatePUDFed,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ProvRate,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TransRatePUDProv,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ChargeWDFee,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ChargeERSTTRFee,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CapitalAmount,       IFASTBP_PROC::TRANS_LIST );
   //addFieldDetails( ifds::TaxExemptAmt,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExistExternalId,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ProvTaxExemptAmt,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FedTaxExemptAmt,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DeliveryMethod,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CashDivPaidAfter,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AdjTransNum,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RebookExist,         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExDate,              IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RoundFlagDesc,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrigAmount,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NetworkRespRequired, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PFCrystalisation,    IFASTBP_PROC::TRANS_LIST );
   // P0205924.FN01
   addFieldDetails( ifds::DealerFee,           IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::FundCompFee,         IFASTBP_PROC::TRANS_LIST);

   addFieldDetails( ifds::TradeRestriction,    IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::TradeRestrictionReason, IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::IsEPATrade,          IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::EnableTradeAuthorization,          IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::EnableTradeRestrictionFields,      IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( AMT_INV_APPL,      IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS);

//PE 1117
   addFieldDetails( ifds::FundWKN,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FundISIN,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FundLFC,             IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::GrossAmtSettleCurr,  IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NetAmtInSettleCurr,  IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AcqDiscountRate,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AcqFeeOption,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FrSettlInstrCode,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ToSettlInstrCode,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FundBrokerCode,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AggregateOption,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::BrkSettlDate,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OtherConfirmType,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExternalPrice,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExternalSettleDate,  IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ExternalSettleAmt,   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Cancellation,        IFASTBP_PROC::TRANS_LIST );
   // ROA enhancement
   addFieldDetails( ifds::CommissionAmnt,      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::NonCommissionAmnt,   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ROAAmount,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OtherFunction,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( HAS_RIGHT_TO_CANCEL_FUND_LIMIT_RULE, IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS, I_( "LimitRule" ) );

   // Swift new fields
   addFieldDetails(ifds::NetworkID,                        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::ExtTransNum,                      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SendRefNum,                       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::PartRefNum,                       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::MasterRefNum,                     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SendLinkRefNum,                   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::LinkedEntityName,                 IFASTBP_PROC::TRANS_LIST );

   addFieldDetails(ifds::MsgExists,                        IFASTBP_PROC::TRANS_LIST );  // PET1117 FN66-68

   addFieldDetails(ifds::AllowModifyDilution,              IFASTBP_PROC::TRANS_LIST );   
   addFieldDetails(ifds::StcPendTrdAuthorization,          IFASTBP_PROC::TRANS_LIST );   
   addFieldDetails(ifds::PaymentInfo,                      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::PendTrdContract,                  IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::ValuationDt,                      IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::IsCancelModSEGTradeAllowed,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::GuaranteesOverride,               IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::BidPrice,                         IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::ExternalInstitution,              IFASTBP_PROC::TRANS_LIST );

   addFieldDetails( ifds::RDRAdvice,                       IFASTBP_PROC::TRANS_LIST );

   addFieldDetails( ifds::RefundTradeExists,               IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RefundAmtOpt,                    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RebookCopy,                      IFASTBP_PROC::TRANS_LIST );

   // transaction update
   addFieldDetails(ifds::StcPendTrdAuthorization,          IFASTBP_PROC::TRANSACTION_UPDATE );   
   addFieldDetails(ifds::TransId,                          IFASTBP_PROC::TRANSACTION_UPDATE );   
   addFieldDetails(ifds::TransNum,                         IFASTBP_PROC::TRANSACTION_UPDATE );   
   addFieldDetails(ifds::PendProcRecordType,               IFASTBP_PROC::TRANSACTION_UPDATE );  
   addFieldDetails(ifds::SettleBatch,                      IFASTBP_PROC::TRANSACTION_UPDATE );
   addFieldDetails(ifds::PaymentInfo,                      IFASTBP_PROC::TRANSACTION_UPDATE );
   addFieldDetails(ifds::TradeRestriction,                 IFASTBP_PROC::TRANSACTION_UPDATE );
   addFieldDetails(ifds::TradeRestrictionReason,           IFASTBP_PROC::TRANSACTION_UPDATE );
   addFieldDetails(ifds::SourceofFundsChecked,             IFASTBP_PROC::TRANSACTION_UPDATE );

   addFieldDetails(ifds::DeductCode,                       IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::DeductDesc,                       IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::DeductAmt,                        IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::DeductCategory,                   IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::FeeRate,                          IFASTBP_PROC::DEDUCTION_LIST );
   addFieldDetails(ifds::TransHistDeductDetailHeadingSet,  IFASTBP_PROC::DEDUCTION_LIST );

   addFieldDetails( ifds::ExternalIdType,                  IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST );
   addFieldDetails( ifds::ExternalId,                      IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST );
   addFieldDetails( ifds::TransactionExtLinksHeadingSet,   IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST );

   addFieldDetails( ifds::ElongName1,      IFASTBP_PROC::FUND_MASTER_LIST );
   addFieldDetails( ifds::FundCode,        IFASTBP_PROC::FUND_MASTER_LIST );
   addFieldDetails( ifds::FundCategory,    IFASTBP_PROC::FUND_MASTER_LIST );
   addFieldDetails( ifds::FundConfirm,     IFASTBP_PROC::FUND_MASTER_LIST );

   addFieldDetails( ifds::Currency,        IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::LoadType,        IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::FundStatusDate,  IFASTBP_PROC::FUND_DETAIL_LIST );

   addFieldDetails( ifds::rxFundCode,      IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::rxClassCode,     IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::BorrowedFunds,   IFASTBP_PROC::TRANS_LIST );

   // list, vw 53
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleDate,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleInDate,        IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransType,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransTypeDesc,       IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AccountTo,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AcctToName,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundTo,              IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ClassToCode,         IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AmountType,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AmountTypeDesc,      IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GrossNetMethod,      IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderType,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::NSCCControlNumber,   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::WireOrdNum,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchUser,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchName,           IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BatchTrace,          IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GoodBad,             IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Indc,                IFASTBP_PROC::PENDING_LIST );
   
   // cbo, vw 54
   addFieldDetails( ifds::Broker, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Branch, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleCurrName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Fee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FeeTo, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FlatPercent, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FeeCurrency, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BELFee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AdminFeeAmt, IFASTBP_PROC::PENDING_LIST );
// addFieldDetails( DBR::OverrideDSC, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideDSCDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideAmt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OverrideTax, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FedRate, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::TransRatePUDFed, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProvRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransRatePUDProv, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::ProvSales, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProvSalesName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RedCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RedCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PaymentInfo, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Payment, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayType2, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AddrCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AddrLine, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SuppressCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ChqSupCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderSource, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OrderSrcDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleSource, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleSrcDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfFund, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfFundDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SrcOfAccount, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleTypeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExpGNSettle, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettledBy, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettledByDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RoundFlag, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RoundFlagDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CreditFreq, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CreditFreqDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExtraCommission, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CertRequired, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CertIssued, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ConfirmRequired, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OnStmt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RecptIssued, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExclMFCSSettle, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GuaranteeDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MaturityDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::InterestRate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepId, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks1, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks2, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Remarks3, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RejCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RejCodeDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Accountable, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AcctableDesc, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DepositDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TimeStamp, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PendingRid, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SplitComm, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DealDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DealTime, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchInFee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchInFlatPercent, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchOutFee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExchOutFlatPrcnt, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::LSIFCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TransSeq, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::NetworkRespRequired, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PFCrystalisation, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PendTrdContract, IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::ValuationDt,IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RightToCancel,IFASTBP_PROC::PENDING_LIST );  
   addFieldDetails( ifds::SDRTExemptCode,IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::PymtRoutingMthd, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PSDAdvice,IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::EventReceiptDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::EventReceiptTime, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Valoren  , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CUSIP	   , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::TDCC	   , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ToValoren, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ToCUSIP  , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ToTDCC   , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SourceOfTrade   , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ChannelOfTrade  , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::Platform		  , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DeliveryNetwork , IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CrossSysAcctNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AggregationType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SourceofFundsChecked, IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::Allocation, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CashDate,        IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::CashDateOverriden, IFASTBP_PROC::PENDING_LIST );

//PET 1117
   addFieldDetails( ifds::AltAccount, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RefNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundWKN, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundISIN, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundToWKN, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundToISIN, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundLFC, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundToLFC, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AcqFeeOption, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SettleDateOverriden, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FrSettlInstrCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ToSettlInstrCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::FundBrokerCode, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::AggregateOption, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BrkSettlDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::OtherConfirmType, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExternalPrice, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExternalSettleDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExternalSettleAmt, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::ChargeWDFee,     IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ChargeERSTTRFee, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ADLFeeCharge, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::TransModPerm, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ValueDate, IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::ACHProcessor, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayMethod, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BankChrgs, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::UseEnteredFee, IFASTBP_PROC::PENDING_LIST );
   //addFieldDetails( ifds::UnitRoundMethod, IFASTBP_PROC::PENDING_LIST );//Blackrock unit rounding project

   // Swift new fields
   addFieldDetails( ifds::NetworkID,        IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExtTransNum,      IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::SendRefNum,       IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PartRefNum,       IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MasterRefNum,     IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::BorrowedFunds,    IFASTBP_PROC::PENDING_LIST );
//ROA enhancement
   addFieldDetails( ifds::ROAAmount, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DeliveryMethod, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::AdjTransNum, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExistExternalId,   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MsgExists, IFASTBP_PROC::PENDING_LIST ); // PET1117 FN66-68
   addFieldDetails( ifds::TransId, IFASTBP_PROC::PENDING_LIST ); // PET1235 - dilution
   addFieldDetails( ifds::PayInstructExists, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::PayInstrOption, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::MFPayment, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::ModDate, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::LinkedEntityName, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails(ifds::StcPendTrdAuthorization, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::IsCancelModSEGTradeAllowed, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::GuaranteesOverride, IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::RDRAdvice, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::ExternalInstitution,IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( AMOUNT_UNITS, BF::NullContainerId, SUBCLASS_PROCESS, I_( "Units" ) );
   addFieldDetails( AMOUNT_DOLLARS, BF::NullContainerId, SUBCLASS_PROCESS, I_( "Amount" ) );
   addFieldDetails( CallPendigTradeDetails, BF::NullContainerId, SUBCLASS_PROCESS, I_("CallPendigTradeDetails") );

   addFieldDetails( FUND_CODE, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( CLASS_CODE, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( FUND_CLASS_KEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( USER_ID, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( DSC_REDEMP_ACCESS, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( IS_FUND_BEL, BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::ValidDateLag, IFASTBP_PROC::PENDING_LIST , SUBCLASS_PROCESS);

   addFieldDetails( ifds::EnableTradeAuthorization,          IFASTBP_PROC::PENDING_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::EnableTradeRestrictionFields,      IFASTBP_PROC::PENDING_LIST, SUBCLASS_PROCESS);
   addFieldDetails( AMT_INV_APPL,                            IFASTBP_PROC::PENDING_LIST, SUBCLASS_PROCESS);

   addFieldDetails(ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails(ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO);


   addFieldDetails( ifds::TransFeeCode, IFASTBP_PROC::TRANS_FEE_LIST);
   addFieldDetails( ifds::FeeType, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::FeeRate, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::FeeCharge, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::ChargeOption, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::TradeFeeOption, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::OrigFeeType, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( ifds::OrigFeeRate, IFASTBP_PROC::TRANS_FEE_LIST );
   addFieldDetails( IsChargeTransFee, IFASTBP_PROC::TRANS_FEE_LIST, SUBCLASS_PROCESS );

   // view 330
   addFieldDetails( ifds::DecimalType,         IFASTBP_PROC::TRANS_DECIMALS);
   addFieldDetails( ifds::DecimalTypeDesc,     IFASTBP_PROC::TRANS_DECIMALS);
   addFieldDetails( ifds::DecimalValue,        IFASTBP_PROC::TRANS_DECIMALS);
   addFieldDetails( ifds::Currency,            IFASTBP_PROC::TRANS_DECIMALS);
   addFieldDetails( ifds::ROATransType,        BF::NullContainerId ,  SUBCLASS_PROCESS);

   // eusd
   addFieldDetails( ifds::OverrideTIS,         IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::TIS,                 IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::OverrideCost,        IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::Cost,                IFASTBP_PROC::PENDING_LIST);
   addFieldDetails( ifds::ESGSettle,           IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::TISType,             IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::CostType,            IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::TIS,                 IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::Cost,                IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::EUSDOverrideVersion, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RightToCancel,	   IFASTBP_PROC::TRANS_LIST );  
   addFieldDetails( ifds::SDRTExemptCode,	   IFASTBP_PROC::TRANS_LIST );  
   addFieldDetails( ifds::TaxCreditAmt,		   IFASTBP_PROC::TRANS_LIST );  
   addFieldDetails( ifds::PymtRoutingMthd,	   IFASTBP_PROC::TRANS_LIST);
   addFieldDetails( ifds::PSDAdvice,	       IFASTBP_PROC::TRANS_LIST ); 
   addFieldDetails( ifds::EventReceiptDate, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::EventReceiptTime, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Valoren  ,		IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CUSIP	   , 		IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::TDCC	   ,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ToValoren,		IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ToCUSIP  , 		IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ToTDCC   ,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SourceOfTrade   , IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::ChannelOfTrade  , IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Platform		  , IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::DeliveryNetwork , IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::CrossSysAcctNum, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::AggregationType, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::SourceofFundsChecked, IFASTBP_PROC::TRANS_LIST );
   // trade suppress
   addFieldDetails(ifds::MCHFileIndicator,     IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::SecRecFileIndicator,  IFASTBP_PROC::PENDING_LIST );

   addFieldDetails(ifds::MCHFileTransHist,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SecRecFileTransHist,  IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::ESGSettle,            IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SWPSettleESGElig,     IFASTBP_PROC::TRANS_LIST, SUBCLASS_PROCESS );
   addFieldDetails(ifds::Reconciled,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::PayReconExists,       IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::PayInstructExists,    IFASTBP_PROC::TRANS_LIST );
   //addFieldDetails( ifds:: UnitRoundMethod,    IFASTBP_PROC::TRANS_LIST );//Blackrock unit rounding project

   addFieldDetails(ifds::ExpectedSettleDate,   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::GrantExists,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::TrfResubmit,          IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::IsAGrantTrade,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::TaxJuris,             IFASTBP_PROC::TRANS_LIST );


   // RESP - QESI Trade Entry
   addFieldDetails(ifds::AssocTransId,         IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::GRRepayReason,        IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::RESPReportHRDC,       IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::RESPContrDetlTaxYear, IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::Tainted,              IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::OCRdmYear,            IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::AssistedContrAmt,     IFASTBP_PROC::PENDING_LIST );

   addFieldDetails(ifds::SettleNetwork,		   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SettleNetwork,		   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::Verified,		       IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::VerifiedBy,		   IFASTBP_PROC::PENDING_LIST );

   //g1Impact and G2 Impact
   addFieldDetails( ifds::G1Impact,            IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::G2Impact,            IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RefundAmtOpt,        IFASTBP_PROC::PENDING_LIST );

   addFieldDetails( ifds::Deconversion,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::Deconversion,        IFASTBP_PROC::PENDING_LIST ); 

   addFieldDetails( ifds::OrderRouting,        IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::OrderRouting,        IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::OrigGrossNet,        IFASTBP_PROC::TRANS_LIST );

   addFieldDetails( ifds::TradeInDate,		   IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::ValuationInDt,       IFASTBP_PROC::PENDING_LIST ); 

   addFieldDetails( ifds::TradeInDate,		   IFASTBP_PROC::TRANS_LIST ); 
   addFieldDetails( ifds::ValuationInDt,       IFASTBP_PROC::TRANS_LIST ); 

   addFieldDetails( ifds::PricingCode,         IFASTBP_PROC::PENDING_LIST ); 

   addFieldDetails( ifds::PricingCode,		   IFASTBP_PROC::TRANS_LIST ); 
   addFieldDetails( ifds::ComponentSplit,           IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::DilutionLinkNum,	   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::DilutionLinkNum,	   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails(ifds::FSRVLinkNum,		   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::FSRVLinkNum,		   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::DistSplitType,		   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::PriceInCode,         IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::PriceInCode,		   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FullMoneyOutIndc,	   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::FullMoneyOutIndc,	   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::GateOverrideIndicator, IFASTBP_PROC::PENDING_LIST ); 
   addFieldDetails( ifds::GateOverrideIndicator, IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RDSPPaymtDate,	   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails( ifds::RDSPPaymtDate,	   IFASTBP_PROC::PENDING_LIST );
   addFieldDetails( ifds::RefundNAV,				   IFASTBP_PROC::TRANS_LIST );
}

//******************************************************************************

TransHistoryProcess::~TransHistoryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( NULL != _pTransactionExternalLinksList )
   {
      delete _pTransactionExternalLinksList;
      _pTransactionExternalLinksList = NULL;
   }

   if ( NULL != _pTransDecimalsList )
   {
      delete _pTransDecimalsList;
      _pTransDecimalsList = NULL;
   }

//   delete _pTransHistoryList;
   _pTransHistoryList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool TransHistoryProcess::doGetData(
                                   GenericInterface * ,
                                   BFData * 
                                   ) const
{
   if( _Pending != Y )
   {
      _pTransHistoryList->getMore();
   }
   else
   {
      PendingTradeList * pPendingTradeList = NULL;
      if( const_cast<TransHistoryProcess*>(this)->getPendingTradeList(pPendingTradeList) <= WARNING )
         pPendingTradeList->getMore();
   }

   return(true);
}

//******************************************************************************

void TransHistoryProcess::doGetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{
   if( idField == AMOUNT_UNITS || idField == AMOUNT_DOLLARS )
   {
      DString tmp;

      PendingTradeList * pPendingTradeList = NULL;
      if( const_cast<TransHistoryProcess*>(this)->getPendingTradeList(pPendingTradeList) > WARNING )
         return;

      BFObjIter iter(*pPendingTradeList, BF::HOST);

      if( iter.positionByKey( strValueOut ) )
         iter.getObject()->getField(ifds::Amount, tmp, BF::HOST, false);
      else
         tmp = NULL_STRING;

//      pPendingTradeList->getField( strValueOut, DBR::Amount, tmp, BF::HOST, false );
      BFData dd( ifds::DSTC0053_VWRepeat_Record);

      dd.setElementValue( ifds::Amount, tmp, false, false );

      if( idField == AMOUNT_UNITS )
      {
         strValueOut = dd.getElementValue( ifds::Amount, BFDataField::USE_MASK, I_( "#,###,###,###,##0.0000" ) );
      }
      else
      {
         strValueOut = dd.getElementValue( ifds::Amount, BFDataField::USE_MASK, I_( "#,###,###,###,##0.00" ) );
      }
   }
   else if (CallPendigTradeDetails == idField)
   {
      strValueOut = _CallPendigTradeDetails;
   }
   else if (IFASTBP_PROC::TRANS_FEE_LIST == idContainer)
   {
      if (idField == IsChargeTransFee)
      {
         TransFee *rpPtrTransFee = dynamic_cast <TransFee*> 
                           ( const_cast<TransHistoryProcess*> (this)->
                                 getCBOItem ( IFASTBP_PROC::TRANS_FEE_LIST, 
                                              idDataGroup
                                             )
                           );
         if (rpPtrTransFee)
         {
            strValueOut = rpPtrTransFee->isChargeFee (idDataGroup) ? I_("Y") : I_("N");
         }
      }
   }
   else if( idField == FUND_CLASS_KEY )
   {
      BFData data;

      data.setElementValue( ifds::FundCode, tmpFund, true, NULL );
      data.setElementValue( ifds::ClassCode, tmpClass, true, NULL );

      _pFundDetailList->getStrKey( strValueOut, &data );
   }
   else if( idField == USER_ID )
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      strValueOut = dynamic_cast<const DSTCSecurity *>(
                                                      pDSTCWorkSession->getSecurity(DSTCHost::getPrimaryHost()))->getUserId();
   }
   else if( idField == ifds::ValidDateLag )
   {
      TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
      PendingTradeDetails* pDetails = dynamic_cast<PendingTradeDetails*>(pThis->getCBOItem(IFASTBP_PROC::PENDING_LIST, idDataGroup));

      if( pDetails )
      {
         if( pDetails->isValidDateLag(idDataGroup) )
            strValueOut = Y;
         else
            strValueOut = N;
      }
   }

   else if( idField == ifds::SWPSettleESGElig )
   {
      TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
      TransactionDetails* pTransaction = dynamic_cast<TransactionDetails*>(pThis->getCBOItem(IFASTBP_PROC::TRANS_LIST, idDataGroup));

      if ( NULL != pTransaction )
      {
        if ( pTransaction->isSWPSettleESGElig( idDataGroup ))
            strValueOut = Y;
        else
            strValueOut = N;
      }
   }

   else if( idField == DSC_REDEMP_ACCESS )
   {
      if( hasReadPermission( UAF::DSC_REDEMPTION ) )
      {
         DString dstrBEL;
         const_cast <TransHistoryProcess*> (this)->getField(rpGICaller, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::LoadType, dstrBEL, false);
         strValueOut = ( dstrBEL == BEL )?Y:N;         
      }
      else
         strValueOut = N;
   }
   else if( idField == IS_FUND_BEL )
   {
      // Similar to DSC_REDEMP_ACCESS but without the UAF check.
      DString dstrBEL;
      const_cast <TransHistoryProcess*> (this)->getField(rpGICaller, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::LoadType, dstrBEL, false);
      strValueOut = ( dstrBEL == BEL )? Y : N;         
   }
   else if( idField == ifds::ROATransType  )
   {
      DSTCWorkSession* pWorkSession =  dynamic_cast<DSTCWorkSession *>(getBFWorkSession() );
      if( pWorkSession )
      {
         pWorkSession->getOption( idField, strValueOut, idDataGroup,bFormatted );
      }
   }
   else if (idField == ifds::EnableTradeAuthorization)
   {
	   bool bEnable = false;

	   DString dstrTransType;
	   DString dstrIndc;
	   DString dstrAcctDesignation;
	   DString dstrSettleType;
	   DString dstrSettled = N;
	   DString dstrOrderType;

	   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	   if (pDSTCWorkSession)
	   {
		   MFAccount *pMFAccount = NULL;

		   if (pDSTCWorkSession->getMFAccount(getDataGroupId(), _AccountNum, pMFAccount) <= WARNING && pMFAccount) 
		   {
			   pMFAccount->getField (ifds::AcctDesignation,  dstrAcctDesignation, getDataGroupId());       
		   }
	   }

	   const_cast <TransHistoryProcess*> (this)->getField (rpGICaller, idContainer, ifds::TransType,  dstrTransType, false);   
	   const_cast <TransHistoryProcess*> (this)->getField (rpGICaller, idContainer, ifds::SettleType,  dstrSettleType, false);   
	   const_cast <TransHistoryProcess*> (this)->getField (rpGICaller, idContainer, ifds::Indc,  dstrIndc, false);
	   const_cast <TransHistoryProcess*> (this)->getField (rpGICaller, idContainer, ifds::OrderType, dstrOrderType ,false);

	   if (idContainer == IFASTBP_PROC::TRANS_LIST)
		   const_cast <TransHistoryProcess*> (this)->getField (this, idContainer, ifds::Settled,  dstrSettled, false);


	   dstrTransType.strip ();
	   dstrTransType.upperCase();
	   dstrSettleType.strip ();
	   dstrIndc.strip ();

	   bool bIsRedemption = dstrTransType == PW || dstrTransType == I_("PWIC");

	   if (dstrSettled == N && dstrOrderType == Y)
	   {
		   if ((bIsRedemption && dstrIndc == INDC90) ||
			   (bIsRedemption && dstrAcctDesignation == CLIENT && dstrSettleType == BLOCK ))
		   {
			   bEnable = true;
		   }
	   }

	   strValueOut = bEnable ? Y:N;
   }
   else if (idField == ifds::EnableTradeRestrictionFields)
   { 
	   // "Restriction" and "Restriction Reason" on TradeAuthorizationDlg are only enabled for History view.
	   if (idContainer == IFASTBP_PROC::TRANS_LIST)
	   {
		   DString dstrIsEPATrade;

		   const_cast <TransHistoryProcess*> (this)->getField (this, IFASTBP_PROC::TRANS_LIST, ifds::IsEPATrade,  dstrIsEPATrade, false);
		   strValueOut = dstrIsEPATrade;
	   }
	   else
	   {
		   strValueOut = N;
	   }
   }
   else if (idField == AMT_INV_APPL)
   { 
       TransHistoryProcess *pThis = const_cast<TransHistoryProcess*>(this);
       strValueOut = N;

	   if (idContainer == IFASTBP_PROC::TRANS_LIST)
	   {
		   TransactionDetails* pTransaction = dynamic_cast<TransactionDetails*>(pThis->getCBOItem(IFASTBP_PROC::TRANS_LIST, idDataGroup));

           if (pTransaction)
           {
               strValueOut = pTransaction->amountInventoryAppl(idDataGroup) ? Y:N;
           }
	   }
       else if (idContainer == IFASTBP_PROC::PENDING_LIST)
	   {
           PendingTradeDetails* pPendingTrade = dynamic_cast<PendingTradeDetails*>(pThis->getCBOItem(IFASTBP_PROC::PENDING_LIST, idDataGroup));

           if (pPendingTrade)
           {
               strValueOut = pPendingTrade->amountInventoryAppl(idDataGroup) ? Y:N;
           }
	   }
   }
   else if (idField == HAS_RIGHT_TO_CANCEL_FUND_LIMIT_RULE && IFASTBP_PROC::TRANS_LIST == idContainer)
   { 
      TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
      TransactionDetails* pTransaction = dynamic_cast<TransactionDetails*>(pThis->getCBOItem(IFASTBP_PROC::TRANS_LIST, idDataGroup));

      if(pTransaction && pTransaction->bIsRightToCancelRuleEnabled(idDataGroup)) 
         strValueOut = Y;
      else 
         strValueOut = N;
   }
}

//******************************************************************************

SEVERITY TransHistoryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( pACCOUNTNUM, _AccountNum );
      getParameter( pFUNDCODE, _FundCode );
      getParameter( pCLASSCODE, _ClassCode );
      getParameter( pNUMENTRY, _NumEntry );
      getParameter( pALLFUND, _AllFundMode );
      getParameter( pTRANSID, _TransId );
      getParameter( pSHAREHOLDERNUM, _ShareholderNum);
      getParameter( pPENDING, _Pending);
      getParameter( pTRANSTYPE, _TransType);
      getParameter( pTRANSNUM, _TransNum);
      getParameter( pTRADEDATE, _TradeDate);
      getParameter( pENTITYID, _EntityId ); 
      getParameter( pREQTRANSID, _ReqTransId );
      getParameter( pINQUIRYONLY, _InquiryOnly );
      getParameter( DISABLEINVINFO, _dstrDisableInvInfo );
      getParameter( I_("DisableMsg"), DisableMsg );
      getParameter( MFCAN_IP_PARAM::EXTERNAL_TRANS_NUM, _ExtTransNum );
      getParameter( I_("Reprint"), Reprint  );
      getParameter (I_("TxnCancel"), TxnCancel );
      getParameter (I_("CalledFrom"), CallFrom );
      getParameter (I_("FromSettlementScreen"), dstrFromSettlementScreen);
	  getParameter ( I_("WireOrdNum"), _dstrWireOrder );
      
	  _AccountNum.stripAll();
      _FundCode.stripAll().upperCase();
      _ClassCode.stripAll().upperCase();
      _NumEntry.stripAll();
      _AllFundMode.stripAll();

      if( ( _AllFundMode == Y ) || (_FundCode == NULL_STRING || _ClassCode == NULL_STRING) )
      {
         _AllFundMode = Y;
      }
      else
      {
         _AllFundMode = N;
      }

      if( _ReqTransId != NULL_STRING )
         _AllFundMode = N;

      _TransId.stripAll();
      _ShareholderNum.stripAll();
      _Pending.stripAll();
      _TransNum.stripAll();
      _TransType.stripAll();
      _TradeDate.stripAll();

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();
      FundMasterList *_pFundMasterList = NULL;
      sevRtn = mgmtCoOut.getFundMasterList( _pFundMasterList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_MASTER_LIST, _pFundMasterList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      _pFundDetailList = NULL;
      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      MFAccount *mfAccount = NULL;
      dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );
	  
	  if (mfAccount == NULL)
	 	return(GETCURRENTHIGHESTSEVERITY());
	  
	  MFAccountHoldingList *pMFAccountHoldingList = NULL;
	  sevRtn = mfAccount->getAccountHoldingList( pMFAccountHoldingList, getDataGroupId() );
	  if( WARNING >= sevRtn )
	  {
		//setContainer( IFASTBP_PROC::FUND_LIST, pMFAccountHoldingList );
	  }
	  else
	  {
	 	return(GETCURRENTHIGHESTSEVERITY());
	  }

	 //DString dstrShrNum;
	 //mfAccount->getField(ifds::ShrNum, dstrShrNum, BF::HOST);
	 //setContainer(IFASTBP_PROC::MFACCOUNT_CBO, mfAccount);
	 mfAccount->getField(ifds::PendingTrade, _dstrPendingTrade, BF::HOST);

	 // Check Transaction Number
	 if( !_ExtTransNum.empty() && !DisableMsg.empty() )
	 {
		_Pending = mfAccount->IsTransactionPending( _ExtTransNum ) ? I_("Y") : I_("N");
	 }
	setGlobal(WORK_GLOBAL, ifds::LastActiveAccountNum, _AccountNum );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool TransHistoryProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_TRANS_HISTORY );
}

//******************************************************************************

bool TransHistoryProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;
   bool lNeedSearchAgain = false;
   DString AccountNum, FundCode, ClassCode,NumEntry,AllFundMode;
   DString TransId,ShareholderNum,Pending,TransType,TransNum,TradeDate,EntityId;

   getParameter( pACCOUNTNUM, AccountNum );
   getParameter( pFUNDCODE, FundCode );
   getParameter( pCLASSCODE, ClassCode );
   getParameter( pNUMENTRY, NumEntry );
   getParameter( pALLFUND, AllFundMode );

   getParameter( pTRANSID, TransId );
   getParameter( pSHAREHOLDERNUM, ShareholderNum);
   getParameter( pPENDING, Pending);
   getParameter( pTRANSTYPE, TransType);
   getParameter( pTRANSNUM, TransNum);
   getParameter( pTRADEDATE, TradeDate);
   getParameter( pENTITYID, EntityId ); 
   getParameter( pINQUIRYONLY, _InquiryOnly );
   getParameter( I_("DisableMsg"), DisableMsg );
   getParameter( MFCAN_IP_PARAM::EXTERNAL_TRANS_NUM, _ExtTransNum );
   getParameter( I_("Reprint"), Reprint  );
   getParameter( I_("TxnCancel"), TxnCancel );

   FundCode.upperCase();
   ClassCode.upperCase();

   if( AccountNum != _AccountNum )
   {
      _AccountNum = AccountNum;
      lNeedSearchAgain = true;
   }

   if( FundCode != _FundCode )
   {
      _FundCode = FundCode;
      lNeedSearchAgain = true;
   }

   if( ClassCode != _ClassCode )
   {
      _ClassCode = ClassCode;
      lNeedSearchAgain = true;
   }

   if( NumEntry != _NumEntry )
   {
      _NumEntry = NumEntry;
      lNeedSearchAgain = true;
   }

   if( AllFundMode != _AllFundMode )
   {
      _AllFundMode = AllFundMode;
      lNeedSearchAgain = true;
   }

   if( TransId != _TransId )
   {
      _TransId = TransId;
      lNeedSearchAgain = true;
   }

   if( ShareholderNum != _ShareholderNum )
   {
      _ShareholderNum = ShareholderNum;
      lNeedSearchAgain = true;
   }

   if( Pending != _Pending )
   {
      _Pending = Pending;
      lNeedSearchAgain = true;
   }

   if( TransType != _TransType )
   {
      _TransType = TransType;
      lNeedSearchAgain = true;
   }

   if( TransNum != _TransNum )
   {
      _TransNum = TransNum;
      lNeedSearchAgain = true;
   }

   if( TradeDate != _TradeDate )
   {
      _TradeDate = TradeDate;
      lNeedSearchAgain = true;
   }

   if( EntityId != _EntityId )
   {
      _EntityId = EntityId;
      lNeedSearchAgain = true;
   }

   if( _AllFundMode == Y || _FundCode == NULL_STRING || _ClassCode == NULL_STRING )
   {
      _AllFundMode = Y;
   }
   else
   {
      _AllFundMode = N;
   }

   if( lNeedSearchAgain )
   {
      setParameter( pACCOUNTNUM, _AccountNum );
      setParameter( pFUNDCODE, _FundCode );
      setParameter( pCLASSCODE, _ClassCode );
      setParameter( pNUMENTRY, _NumEntry );
      setParameter( pALLFUND, _AllFundMode );

      setParameter( pTRANSID, _TransId );
      setParameter( pSHAREHOLDERNUM, _ShareholderNum );
      setParameter( pPENDING, _Pending );
      setParameter( pTRANSTYPE, _TransType );
      setParameter( pTRANSNUM, _TransNum );
      setParameter( pTRADEDATE, _TradeDate );
      setParameter( pENTITYID, _EntityId ); 
      setParameter( pREQTRANSID, _ReqTransId );
      setParameter( pPENDINGTRADE, _dstrPendingTrade);
      setParameter( I_("DisableMsg"), DisableMsg );
      setParameter( MFCAN_IP_PARAM::EXTERNAL_TRANS_NUM, _ExtTransNum );
      setParameter( I_("Reprint"), Reprint  );
      setParameter( I_("TxnCancel"), TxnCancel );

      performSearch( this, BF::AllContainerIds, SEARCH_START );
   }

   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   MFAccount *mfAccount = NULL;
   dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );

   DString dstrShrNum;
   mfAccount->getField(ifds::ShrNum, dstrShrNum, BF::HOST);
   //setContainer(IFASTBP_PROC::MFACCOUNT_CBO, mfAccount);   

   return(bRtn);
}

//******************************************************************************
bool TransHistoryProcess::doSend ( GenericInterface* rpGICaller, 
                                   const I_CHAR * szMessage)
{
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doSend"));

   bool bRtn = false;

   try
   {
      if ( DString (szMessage) == I_("DeductDetail") ||
           DString (szMessage) == I_("Fees")
         )
      {
         if ( DString (szMessage) == I_("Fees"))
         {
            setContainer (IFASTBP_PROC::TRANS_FEE_LIST, NULL);
         }
         setParameter (MFCAN_IP_PARAM::CALLER, szMessage);
         setParameter (pTRANSNUM, _TransNum);

         E_COMMANDRETURN rtn = invokeCommand ( this, 
                                               CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL, 
                                               PROC_NO_TYPE, 
                                               true, 
                                               NULL );

         bRtn = rtn == CMD_OK || 
                rtn == CMD_CANCEL || 
                rtn == CMD_MODELESS_INPROCESS;
      }
      else if( DString( szMessage ) == I_( "TransactionExternalLinks" ) )
      {
         DString dstrTransNum;
         if ( _Pending == Y )
         {
            TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
            PendingTradeDetails* pDetails = 
               dynamic_cast<PendingTradeDetails*>(pThis->getCBOItem(IFASTBP_PROC::PENDING_LIST, getDataGroupId() ) );
            if ( NULL != pDetails )
               pDetails->getField( ifds::TransNum, dstrTransNum, getDataGroupId(), false );
         }
         else
         {
            BFAbstractCBO *pTransaction = 
               dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::TRANS_LIST, getDataGroupId()) );
            if ( NULL != pTransaction )
               pTransaction->getField( ifds::TransNum, dstrTransNum, getDataGroupId() );
         }

         setParameter( pTRANSNUM,       dstrTransNum);
         setParameter( pACCOUNTNUM,     _AccountNum );
         setParameter( pSHAREHOLDERNUM, _ShareholderNum );
         
         E_COMMANDRETURN rtn = invokeCommand( this, 
                                              CMD_GUI_TRANSACTION_EXTERNAL_LINKS, 
                                              PROC_NO_TYPE, 
                                              true, 
                                              NULL );

         bRtn = rtn == CMD_OK || 
                rtn == CMD_CANCEL || 
                rtn == CMD_MODELESS_INPROCESS;
      }
      else if( DString( szMessage ) == I_( "RefreshHistory" ) )
      {
         DString transId;
         getField(this,IFASTBP_PROC::TRANS_LIST,ifds::TransId,transId,false);
         setParameter( I_("OldTransId"), transId);
         const DString listKey = getCurrentListItemKey(this, IFASTBP_PROC::TRANS_LIST);
         setParameter( I_("CurrenKey"), listKey);
         setContainer(IFASTBP_PROC::TRANS_LIST, NULL);   
         PendingTradeList* pPendingList = NULL;
         getPendingTradeList(pPendingList, MAX_REPEAT_COUNT,true );
         setContainer( IFASTBP_PROC::PENDING_LIST, pPendingList );
         if( isValidModelessInterface( _rpChildGI ) )
         {
            bRtn = _rpChildGI->refresh( this, I_("RefreshHistory") );
            bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
         }
         return true;
      }
      else if( DString( szMessage ) == I_( "RefreshAndRebook" ) )
      {
         setParameter( STARTREBOOK,Y );
         return doSend ( rpGICaller, I_( "RefreshHistory" ) );
      }
      else if (DString (szMessage) == I_("TradeAuthorization") ||
		       DString (szMessage) == I_("Batch")||
			   DString (szMessage) == I_("Payment") ||
               I_("SourceofFundsChecked") == DString (szMessage) )
      {
		 E_COMMANDRETURN rtn;

         getParameter (pPENDPROCRECORD_TYPE, _PendProcRecordType);
		 setParameter (pPENDPROCRECORD_TYPE, _PendProcRecordType);
		 setParameter (pACCOUNTNUM, _AccountNum);

		 if (DString (szMessage) == I_("Batch"))
			 _caller = I_("Batch");

		 else if(DString (szMessage) == I_("TradeAuthorization"))
			 _caller = I_("TradeAuthorization");
		
		 else if(DString (szMessage) == I_("Payment"))
			 _caller = I_("Payment");

		 else if(DString (szMessage) == I_("SourceofFundsChecked"))
			 _caller = I_("SourceofFundsChecked");

 		 setContainer (IFASTBP_PROC::TRANSACTION_UPDATE, NULL);

		 if (DString (szMessage) == I_("TradeAuthorization"))
		 {
			rtn = invokeCommand (this, CMD_GUI_TRADE_AUTHORIZATION, PROC_NO_TYPE, true, NULL );
		 }
         else if ( I_("SourceofFundsChecked") ==  DString (szMessage) )
		 {
			rtn = invokeCommand (this, CMD_GUI_TRADE_SOURCE_OF_FUNDS_CHECKED, PROC_NO_TYPE, true, NULL );
		 }
		 else if (DString (szMessage) == I_("Batch"))
		 {
            rtn = invokeCommand (this, CMD_GUI_BATCH, PROC_NO_TYPE, true, NULL );
		 }
		 else if (DString (szMessage) == I_("Payment"))
		 {
            rtn = invokeCommand (this, CMD_GUI_PAYMENT_INFO_FLAG, PROC_NO_TYPE, true, NULL );
		 }

		 if (rtn == CMD_CANCEL)
			setParameter (pOKCancel, I_("Cancel"));

         bRtn = rtn == CMD_OK || 
                rtn == CMD_CANCEL || 
                rtn == CMD_MODELESS_INPROCESS;
      }
   }
   catch (ConditionException &ce)
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch ( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return bRtn;
}

//******************************************************************************

bool TransHistoryProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                              const BFContainerId& idContainer )
{
   if( _Pending != Y )
   {
      return( _pTransHistoryList->doMoreRecordsExist() );
   }
   else
   {
      PendingTradeList * pPendingTradeList = NULL;
      if( getPendingTradeList(pPendingTradeList) > WARNING )
      {
         return(false);//rather throw the error here?
      }
      return( pPendingTradeList->doMoreRecordsExist() );
   }
}

//******************************************************************************

E_COMMANDRETURN TransHistoryProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( pACCOUNTNUM, _AccountNum );
      setParameter( pFUNDCODE, _FundCode );
      setParameter( pCLASSCODE, _ClassCode );
      setParameter( pNUMENTRY, _NumEntry );
      setParameter( pALLFUND, _AllFundMode );
      setParameter( pTRANSID, _TransId );
      setParameter( pSHAREHOLDERNUM, _ShareholderNum );
      setParameter( pPENDING, _Pending );
      setParameter( pTRANSTYPE, _TransType );
      setParameter( pTRANSNUM, _TransNum );
      setParameter( pTRADEDATE, _TradeDate );
      setParameter( pENTITYID, _EntityId ); 
      setParameter( pREQTRANSID, _ReqTransId );
      setParameter( pINQUIRYONLY, _InquiryOnly );
      setParameter( pPENDINGTRADE, _dstrPendingTrade);
      setParameter( DISABLEINVINFO, _dstrDisableInvInfo );
      setParameter( I_("DisableMsg"), DisableMsg );
      setParameter( MFCAN_IP_PARAM::EXTERNAL_TRANS_NUM, _ExtTransNum );
      setParameter( I_("Reprint"), Reprint  );
      setParameter( I_("TxnCancel"), TxnCancel );
      setParameter( I_("CalledFrom"), CallFrom );
      setParameter (I_("FromSettlementScreen"), dstrFromSettlementScreen);

      rtn = invokeCommand( this, CMD_GUI_TRANS_HISTORY, PROC_NO_TYPE, isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

bool TransHistoryProcess::doRefresh( GenericInterface *rpGICaller, 
                                     const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   bool bRtn = true;
   setContainer( IFASTBP_PROC::PENDING_LIST, NULL );
   if( rpGICaller->getCommand().getKey() == CMD_BPROC_TRADES )//new trades were created
   {
      setParameter( pPENDING, _Pending );
      bRtn = _rpChildGI->refresh( this, I_("PendingTradesRefreshed") );
   }
   else if( rpGICaller->getCommand().getKey() == CMD_BPROC_SETTLEMENT ) // trade has been settled
   {
      setContainer( IFASTBP_PROC::TRANS_LIST, NULL );
      bRtn = _rpChildGI->refresh( this, I_("FromSettlement") );
   }

   return(bRtn);
}

//******************************************************************************

SEVERITY TransHistoryProcess::doSetField(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted
                                        )
{
   if( BF::NullContainerId == idContainer )
   {
      if( idField == FUND_CODE )
      {
         tmpFund=strValue;
      }
      else if( idField == CLASS_CODE )
      {
         tmpClass=strValue;
      }
      else if (CallPendigTradeDetails == idField)
      {
         _CallPendigTradeDetails = strValue;
      }
   }

   return(NO_CONDITION);
}

//******************************************************************************

void TransHistoryProcess::setCurrentListItem(
                                            const GenericInterface *rpGICaller,
                                            const BFContainerId& idList,
                                            const DString& strListItemKey
                                            )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );

   if( idList == IFASTBP_PROC::TRANS_LIST )
   {
      TransactionDetails *tmp =_pTransHistoryList->getItem( strListItemKey,
                                                            BF::HOST );
      if( tmp )
      {
         setContainer( IFASTBP_PROC::DEDUCTION_LIST, tmp->getDeductionList() );

         if ( NULL != _pTransactionExternalLinksList )
         {
            delete _pTransactionExternalLinksList;
            _pTransactionExternalLinksList = NULL;
            setContainer( IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST, NULL );
         }

         if ( NULL != _pTransDecimalsList )
         {
            delete _pTransDecimalsList;
            _pTransDecimalsList = NULL;
            setContainer( IFASTBP_PROC::TRANS_DECIMALS, NULL );
         }
      }
   }

   if( idList == IFASTBP_PROC::PENDING_LIST )
   {
      PendingTradeList * pPendingTradeList = NULL;
      if( getPendingTradeList(pPendingTradeList) > WARNING )
         return;
      if (_CallPendigTradeDetails == I_("Y"))
      {
         pPendingTradeList->getItem( strListItemKey, BF::HOST );
      }

      if ( NULL != _pTransactionExternalLinksList )
      {
         delete _pTransactionExternalLinksList;
         _pTransactionExternalLinksList = NULL;
         setContainer( IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST, NULL );
      }
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

SEVERITY TransHistoryProcess::performSearch( GenericInterface *rpGI, 
                                             const BFContainerId& idSearch, 
                                             E_SEARCHACTION  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter ( pACCOUNTNUM, _AccountNum );
      getParameter ( pFUNDCODE, _FundCode );
      getParameter ( pCLASSCODE, _ClassCode );
      getParameter ( pNUMENTRY, _NumEntry );
      getParameter ( pALLFUND, _AllFundMode );
      getParameter ( pTRANSID, _TransId );
      getParameter ( pSHAREHOLDERNUM, _ShareholderNum );
      getParameter ( pPENDING, _Pending );
      getParameter ( pTRANSTYPE, _TransType );
      getParameter ( pTRANSNUM, _TransNum );
      getParameter ( pTRADEDATE, _TradeDate );
      getParameter ( pENTITYID, _EntityId ); 

      bool b = CallFrom == I_("BrowserLaunch");

      if (!b)
        getParameter ( pREQTRANSID, _ReqTransId );

      _FundCode = _FundCode.upperCase();
      _ClassCode = _ClassCode.upperCase();

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *mfAccount = NULL;
      
      dstcWorkSession->getMFAccount (getDataGroupId(), _AccountNum, mfAccount);
      MFAccountHoldingList *pMFAccountHoldingList = NULL;
      sevRtn = mfAccount->getAccountHoldingList( pMFAccountHoldingList, getDataGroupId() );

      if (WARNING >= sevRtn)
      {
         //setContainer( IFASTBP_PROC::FUND_LIST, pMFAccountHoldingList );
      }
      else
      {
         return GETCURRENTHIGHESTSEVERITY();
      }

      if (_Pending == Y)
      {
         setContainer (IFASTBP_PROC::PENDING_LIST, NULL);
      }
      else
      {
         sevRtn = mfAccount->getTransactionHistoryList( _pTransHistoryList, 
                                                        _FundCode, 
                                                        _ClassCode, 
                                                        _NumEntry, 
                                                        _AllFundMode, 
                                                        _ReqTransId, 
                                                        getDataGroupId(), 
                                                        true, 
                                                        DisableMsg.empty() ? NULL_STRING : _ExtTransNum, 
                                                        false, 
                                                        CallFrom == I_("BrowserLaunch") ? _TransNum : NULL_STRING,
														_dstrWireOrder);

         if (WARNING >= sevRtn)
         {
            setContainer (IFASTBP_PROC::TRANS_LIST, _pTransHistoryList);
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void *TransHistoryProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if (IFASTBP_PROC::PENDING_LIST == idContainer)
      {
         {
            PendingTradeList * pPendingTradeList = NULL;
            int nNumEntry = _NumEntry.asInteger();
            if( getPendingTradeList(pPendingTradeList, MAX_REPEAT_COUNT) <= WARNING)
               ptr = pPendingTradeList;
         }
      }
      else if( IFASTBP_PROC::TRANS_LIST == idContainer )
      {
         {
            MFAccount *mfAccount = NULL;
            if ( dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount ) <= WARNING &&
                 mfAccount)
            {
               DString startRebook;
               getParameter (STARTREBOOK, startRebook);
//Incident# 445112 && 444351 - if rebook is started - get the entire list of trans history
               mfAccount->getTransactionHistoryList (_pTransHistoryList , _FundCode, _ClassCode, _NumEntry, _AllFundMode, _ReqTransId, getDataGroupId(), true, DisableMsg.empty() ? NULL_STRING : _ExtTransNum, startRebook == Y);
               ptr = _pTransHistoryList;
            }
         }
      }
	  else if (IFASTBP_PROC::TRANSACTION_UPDATE == idContainer)
	  {
		 TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
		 TransactionUpdate* pTransactionUpdate = NULL;
		 DString dstrEnableTradeAuthorization;

		  if (_PendProcRecordType == I_("Proc"))
		  {
				TransactionDetails* pTransaction = dynamic_cast<TransactionDetails*>(pThis->getCBOItem(IFASTBP_PROC::TRANS_LIST, idDataGroup));
				getField(this, IFASTBP_PROC::TRANS_LIST, ifds::EnableTradeAuthorization, dstrEnableTradeAuthorization, false);

				if (pTransaction)
				{
					pTransaction->getTransactionUpdate (pTransactionUpdate, _PendProcRecordType, _caller, dstrEnableTradeAuthorization, getDataGroupId());
				
					ptr = pTransactionUpdate;
				}
		  }
		  else
		  {
				PendingTradeDetails* pDetails = dynamic_cast<PendingTradeDetails*>(pThis->getCBOItem(IFASTBP_PROC::PENDING_LIST, idDataGroup));
				getField(this, IFASTBP_PROC::PENDING_LIST, ifds::EnableTradeAuthorization, dstrEnableTradeAuthorization, false);

				if (pDetails)
				{
					pDetails->getTransactionUpdate (pTransactionUpdate, _PendProcRecordType, _caller, dstrEnableTradeAuthorization, getDataGroupId());
				
					ptr = pTransactionUpdate;
				}
		  }
	  }
      else if( IFASTBP_PROC::FUND_LIST == idContainer )
      {
         {
            MFAccount *mfAccount = NULL;
            MFAccountHoldingList *pMFAccountHoldingList = NULL;
            dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );
            if( mfAccount->getAccountHoldingList( pMFAccountHoldingList, getDataGroupId() ) <= WARNING )
               ptr = pMFAccountHoldingList;
         }
      }
      else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         {
            MFAccount *mfAccount = NULL;
            dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );
            ptr = mfAccount;
         }
      }
      else if( IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST == idContainer )
      {
         DString dstrTransNum,
                 dstrTransId;
         if ( _Pending == Y )
         {
            TransHistoryProcess* pThis = const_cast<TransHistoryProcess*>(this);
            PendingTradeDetails* pDetails = 
               dynamic_cast<PendingTradeDetails*>(pThis->getCBOItem(IFASTBP_PROC::PENDING_LIST, idDataGroup));
            if ( NULL != pDetails )
            {
               pDetails->getField( ifds::TransNum, dstrTransNum, idDataGroup, false );                              
               // We don't have TransId for a Pending Trade returned by either 53 or 54.
            }
         }
         else
         {
            BFAbstractCBO *pTransaction = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::TRANS_LIST, getDataGroupId()) );
            if ( NULL != pTransaction )
            {
               pTransaction->getField( ifds::TransNum, dstrTransNum, idDataGroup );               
               pTransaction->getField( ifds::TransId,  dstrTransId,  idDataGroup );               
            }
         }
         if ( NULL == _pTransactionExternalLinksList )
         {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if ( NULL != dstcWorkSession )
            {
               _pTransactionExternalLinksList = new TransactionExternalLinksList( *dstcWorkSession );         
            }
         
            if ( NULL != _pTransactionExternalLinksList &&
                 _pTransactionExternalLinksList->init( dstrTransNum, dstrTransId, idDataGroup ) <= WARNING )
            {
               ptr = _pTransactionExternalLinksList;
            }
         }
         else
            ptr = _pTransactionExternalLinksList;
      }
      else if (IFASTBP_PROC::TRANS_FEE_LIST == idContainer)
      {
         PendingTradeDetails *pDetails = 
               dynamic_cast<PendingTradeDetails*> (getCBOItem(IFASTBP_PROC::PENDING_LIST, idDataGroup));
         if (NULL != pDetails)
         {
            TransFeeList *pTransFeeList = NULL;
            if ( pDetails->getTransFeeList ( pTransFeeList, 
                                             idDataGroup
                                            ) <= WARNING && 
                pTransFeeList
               )
            {
               ptr = pTransFeeList;
            }
         }
      }
      
      else if (IFASTBP_PROC::TRANS_DECIMALS == idContainer)
      {        
         
         DString dstrTransId;
         BFAbstractCBO *pTransaction = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::TRANS_LIST, getDataGroupId()) );
         if ( NULL != pTransaction )
            pTransaction->getField( ifds::TransId,  dstrTransId,  idDataGroup );      

         if ( NULL == _pTransDecimalsList )
         {
               _pTransDecimalsList = new TransDecimalsList( *dstcWorkSession );         
            
               if  ( _pTransDecimalsList->init( dstrTransId, idDataGroup ) <= WARNING 
                     && _pTransDecimalsList != NULL  )
                  ptr = _pTransDecimalsList;
         }
         else
            ptr = _pTransDecimalsList;

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
   return(ptr);
}
//******************************************************************************

SEVERITY TransHistoryProcess::getPendingTradeList(PendingTradeList *& pPendingTradeList, int nNumEntry /*= -1*/,bool bRefresh )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPendingTradeList") );
   SEVERITY sevRtn = SEVERE_ERROR;
   pPendingTradeList = NULL;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount *mfAccount = NULL;
   sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );
   if( sevRtn < WARNING )
      mfAccount->getPendingTradesList(pPendingTradeList, getDataGroupId(), nNumEntry, DisableMsg.empty() ? NULL_STRING : _ExtTransNum,bRefresh );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransHistoryProcess.cpp-arc  $
 * 
 *    Rev 1.146   Aug 10 2012 20:03:48   wp040133
 * ESS_P01999461_FN01_ARROW_Distribution Enhancement
 * Adding TaxCreditAmt to History Screen
 * 
 *    Rev 1.145   Jul 27 2012 08:15:40   wp040132
 * P0199891 _FN01_Arrow_FAST_File
 * 
 *    Rev 1.144   Jul 26 2012 10:35:26   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.143   Jul 02 2012 19:08:52   wp040132
 * P0199883_FN01_Cancellation Rights - Right To Cancel
 * 
 *    Rev 1.142   Mar 20 2012 17:10:54   dchatcha
 * P0186479 FN01 - Allowable Transfer.
 * 
 *    Rev 1.141   Mar 05 2012 11:38:58   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.140   Jan 20 2012 14:47:38   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.139   Dec 08 2011 21:43:10   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.138   Aug 03 2011 11:34:38   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.137   Dec 09 2010 15:00:34   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.136   Jun 01 2010 23:47:20   dchatcha
 * Synch up from  1.134.1.0 : IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
 * 
 *    Rev 1.135   May 27 2010 05:19:04   kitticha
 * PETP0165541 FN02 QESI Phase2.
 * 
 *    Rev 1.134   Apr 30 2010 01:15:26   dchatcha
 * PET0165541 FN01 QESI RESP Trading, display new fields of view 54.
 * 
 *    Rev 1.133   Apr 14 2010 23:57:18   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.132   Mar 29 2010 16:35:58   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.131   Dec 02 2009 03:11:14   dchatcha
 * P0166149 SSII iFAST Web Settlement Date Changes.
 * 
 *    Rev 1.130   Nov 10 2009 03:19:10   dchatcha
 * IN#1809321 - iFast/Desktop Confirmation window (remark) after modification, fix compile error.
 * 
 *    Rev 1.129   Nov 03 2009 21:27:34   wutipong
 * IN#1809321 - iFast/Desktop Confirmation window (remark) after modification
 * 
 *    Rev 1.128   May 28 2009 06:37:24   wutipong
 * IN1608629 - Aimprod RTS error : Disable the settlement button on the trans history dialog only when the dialog is open from settlement dialog. -- Sync Up
 * 
 *    Rev 1.127   May 22 2009 16:02:04   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.126   May 22 2009 10:26:36   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.125   Mar 04 2009 14:12:20   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.124   Mar 02 2009 09:55:46   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.123   Nov 25 2008 11:10:58   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.122   06 Oct 2008 13:16:18   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.121   Sep 12 2008 15:51:32   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.120   Aug 29 2008 09:52:54   daechach
 * in#1355618 - recode fix for 1259584 Gross\net
 * 
 *    Rev 1.119   30 Jul 2008 16:00:10   kovacsro
 * PET0095436_FN01 Blackrock Rounding
 * 
 *    Rev 1.118   23 Jul 2008 11:26:24   kovacsro
 * 1. synch up 1.115.1.0
 * 2. PET0095436_FN01_Rounding (commented out code)
 * 
 *    Rev 1.117   03 Jun 2008 15:27:10   kovacsro
 * restored rev. 1.115
 * 
 *    Rev 1.115   Apr 25 2008 08:05:44   daechach
 * in#1259584-R84 - Gross / Net display issue in desktop for pending trades
 * 
 *    Rev 1.114   Jan 18 2008 11:33:38   daechach
 * IN#1123784,1133269 - Gross/Net field not populated in desktop modify screen , Pending transaction on Desktop unavailable
 * 
 *    Rev 1.113   Dec 20 2007 16:33:22   wongsakw
 * PET2315 FN28 -- Audit an Tracking on Pending Trades -- Add ModDate and ModUser field to PendingTrade
 * 
 *    Rev 1.112   Dec 06 2007 19:41:32   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.111   Nov 30 2007 18:29:16   daechach
 * PET5517 FN 97 - RRIF Net of Fees
 * 
 *    Rev 1.110   Sep 16 2007 15:38:16   jankovii
 * IN #990336 - User is unable to process manual/adhoc MFR trades.
 * 
 *    Rev 1.109   Aug 16 2007 10:39:28   jankovii
 * Sync up for inicidnet 954084.
 * 
 *    Rev 1.108   Aug 10 2007 14:11:50   jankovii
 * PET 2360 FN14&FN19 - Management Fee.
 * 
 *    Rev 1.107   Mar 30 2007 13:58:56   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.105   Mar 16 2007 11:31:12   popescu
 * Incident# 838989 - removed the 'receive all = true' parameter; 
 * 
 *    Rev 1.104   Mar 14 2007 14:42:30   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.103   Mar 09 2007 10:17:00   ZHANGCEL
 * PET2292 FN02 - Added SendLinkRefNum in TRANS_LIST
 * 
 *    Rev 1.102   Nov 27 2006 18:30:10   popescu
 * Incident 761906 - Desktop will correctly display the entire transaction history list, while switching between Pending and Trans History mode on the Transaction Hostory Dialog.
 * Same fix applies if user switches between funds using the Fund/All Funds combo dialog.
 * 
 *    Rev 1.101   Nov 16 2006 13:27:50   fengyong
 * Incident 752890 - Transaction history fund filter
 * 
 *    Rev 1.100   Oct 13 2006 17:50:12   fengyong
 * Add transnumber search
 * 
 *    Rev 1.99   Sep 21 2006 01:50:20   popescu
 * STP PET 2217/13
 * 
 *    Rev 1.98   Aug 29 2006 16:41:26   fengyong
 * PET2192 FN17 - Add from screen parameter
 * 
 *    Rev 1.97   Mar 03 2006 09:24:06   fengyong
 * PET2017 FN01 - Add field reconciled
 * 
 *    Rev 1.96   Mar 02 2006 17:32:26   ZHANGCEL
 * PET1334 - FN01 -- ESG Settlement enhancement
 * 
 *    Rev 1.95   Mar 02 2006 16:25:38   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.94   Feb 15 2006 10:46:32   ZHANGCEL
 * PET 1334 - FN1 -- ESG money movement enhancement
 * 
 *    Rev 1.93   Jan 12 2006 13:48:18   AGUILAAM
 * PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
 * 
 *    Rev 1.92   Dec 13 2005 19:22:30   porteanm
 * Incident 421704 - gap - TranshistDilutionAlloc update support.
 * 
 *    Rev 1.91   Dec 06 2005 09:36:20   popescu
 * Incident# 444351 - subsequent fix for displaying the rebook param screen.
 * 
 *    Rev 1.90   Nov 29 2005 15:23:30   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.89   Nov 06 2005 12:36:44   popescu
 * Incident# 444351 - rebook flow does not show if the transhistory has more then 25 records 
 * 
 *    Rev 1.88   Sep 20 2005 12:52:48   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.87   Jul 20 2005 14:02:30   Yingbaol
 * PET1235,FN01:fix refresh issue
 * 
 *    Rev 1.86   Jul 15 2005 09:26:52   Yingbaol
 * PET1235,FN01: pass parameters 
 * 
 *    Rev 1.85   Jul 12 2005 17:19:20   AGUILAAM
 * PET 1235: dilution
 * 
 *    Rev 1.84   Jul 12 2005 15:56:44   Yingbaol
 * PET1235,FN01: add taxType to account cbo
 * 
 *    Rev 1.83   Jul 08 2005 09:38:38   Yingbaol
 * PET1235,FN01:cancellation rebook
 * 
 *    Rev 1.82   Jul 06 2005 12:25:58   porteanm
 * PET1171 EUSD 1B - TIS and Cost.
 * 
 *    Rev 1.81   Jul 06 2005 10:16:06   Yingbaol
 * PET1235:FN01, rebook cancellation
 * 
 *    Rev 1.80   Jun 22 2005 17:52:30   AGUILAAM
 * IN 343484 - display DeliveryMethod on trades
 * 
 *    Rev 1.79   Jun 22 2005 11:26:12   popescu
 * PET 1117/08 - fixed pending trades refresh issue
 * 
 *    Rev 1.78   May 30 2005 18:01:30   porteanm
 * PET OPC Confirm Reprint - Set Reprint/TxnCancel parameters.
 * 
 *    Rev 1.77   May 24 2005 12:52:04   porteanm
 * PET OPC Confirm Reprint - Added FundConfirm to container.
 * 
 *    Rev 1.76   May 18 2005 09:05:36   yingbaol
 * PET1203,FN01 Commission Class A enhancement
 * 
 *    Rev 1.75   Apr 21 2005 16:35:16   hernando
 * Incident #278666 - Switched TransNum to ExtTransNum.  Incident #279078 - Switched parameters; PendingTrade to Pending.  Added Ext Trans Num to MFAccount calls for Pending Trade List and Transaction History.  Synchronized with 1.72.1.0-1.72.1.2
 * 
 *    Rev 1.74   Mar 04 2005 17:09:44   Fengyong
 * PET1190 FN04 - TransCancel Tempery check in for other coder
 * 
 *    Rev 1.73   Mar 03 2005 14:33:10   aguilaam
 * PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
 * 
 *    Rev 1.72   Feb 22 2005 16:28:06   hernando
 * PET1117 FN66-68 - Added field details for MsgExist for Pending and Trans List.  Added DisableMsg parameter.
 * 
 *    Rev 1.71   Feb 17 2005 13:15:18   aguilaam
 * PET1198_FN01: LSIF Reason Code enhancement. 
 * 
 *    Rev 1.70   Feb 03 2005 13:10:46   popescu
 * PET 1117/66, new fields for view 22/54
 * 
 *    Rev 1.69   Jan 20 2005 15:54:58   hernando
 * PTS10037884 - Change the display of Back End Load.
 * 
 *    Rev 1.68   Dec 21 2004 18:11:22   popescu
 * PET 1117/56, fixed call to pending trades details view 54 when dialog is launched.
 * 
 *    Rev 1.67   Dec 13 2004 14:16:48   popescu
 * PET 1117/56, ChqSupCode-->SuppressCode, view 54
 * 
 *    Rev 1.66   Dec 11 2004 11:47:20   popescu
 * PET 1117/56 more fixes, pending trade mods
 * 
 *    Rev 1.65   Dec 10 2004 16:18:32   popescu
 * PET 1117/56 few fixes for settl instr and trans fee list refresh
 * 
 *    Rev 1.64   Dec 09 2004 12:37:30   popescu
 * PET 1117/56, more fees work /pending trade
 * 
 *    Rev 1.63   Dec 07 2004 21:20:12   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.62   Dec 07 2004 01:37:22   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.61   Nov 22 2004 13:08:50   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.60   Sep 22 2004 14:09:18   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.59   Sep 20 2004 10:53:12   ZHANGCEL
 * PET1082 -- Add two new fields for the New Quebec withholding tax enhancement
 * 
 *    Rev 1.58   Sep 16 2004 09:41:20   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.57   Sep 07 2004 15:33:04   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.56   Aug 26 2004 15:26:00   ZHANGCEL
 * PET 1082 -- Add a new field for the TaxExemptAmt
 * 
 *    Rev 1.55   Jun 14 2004 15:52:00   ZHANGCEL
 * PTS ticket 10031296 : Bug fix for the empty pointer by some chance occuring and causing crash.
 * 
 *    Rev 1.54   May 18 2004 14:23:00   popescu
 * PET 995, FN 01, LSIF Trade entry
 * 
 *    Rev 1.53   May 18 2004 11:32:08   HERNANDO
 * PET1046 FN01 - Added disableInvInfo parameter.
 * 
 *    Rev 1.52   Feb 16 2004 11:00:42   ZHANGCEL
 * Sync up: PTS 10026640 : added a paramer for the pending trade checking
 * 
 *    Rev 1.51   Feb 05 2004 10:25:48   VADEANUM
 * PET859 FN23 - ADL - Deductions and ADLFeeCharge.
 * 
 *    Rev 1.51   Feb 04 2004 17:05:52   VADEANUM
 * PET 859 FN23 - ADL - Deductions Details and ADLFeeCharge.
 * 
 *    Rev 1.50   Dec 10 2003 12:19:20   popescu
 * PTS 10024124, spcomm re-work
 * 
 *    Rev 1.49   Nov 26 2003 14:00:00   VADEANUM
 * PET859_FN17 - daily equalization; addFieldDetails for CapitalAmount in TRANS_LIST - for Amelia
 * 
 *    Rev 1.48   Sep 16 2003 13:41:28   HSUCHIN
 * bug fix - BorrowFund fields is not on the FUND_LIST but on the TRANS_LIST
 * 
 *    Rev 1.47   Sep 08 2003 16:15:30   FENGYONG
 * Add field AcctLevelTax
 * 
 *    Rev 1.46   Aug 19 2003 16:09:28   HSUCHIN
 * added Borrowed Funds to details of pending/historical purchases.
 * 
 *    Rev 1.45   Aug 15 2003 14:19:48   FENGYONG
 * Add Field Override tax
 * 
 *    Rev 1.44   Jul 23 2003 14:37:06   VADEANUM
 * PET 809 F05 - Charge WD Fee support.
 * 
 *    Rev 1.43   Apr 02 2003 11:46:34   popescu
 * added the chargeer/sttr fee field to the transaction list, as well
 * 
 *    Rev 1.42   Mar 26 2003 15:50:36   popescu
 * Added the charge  er/sttr fee to the transaction histrory dialog
 * 
 *    Rev 1.41   Mar 21 2003 17:49:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.40   Mar 19 2003 09:58:30   popescu
 * Added the exchange out fee to the transaction history dialog for pending trades
 * 
 *    Rev 1.39   Mar 04 2003 11:08:10   KOVACSRO
 * commented out useless code in doInit (this will pop-up the screen a little bit faster for trade search)
 * 
 *    Rev 1.38   Mar 03 2003 09:40:48   KOVACSRO
 * Added new parameter "InquiryOnly"
 * 
 *    Rev 1.37   Jan 22 2003 09:02:40   sanchez
 * Connect the transaction history/pending trades dialog fields to the CBO
 * 
 *    Rev 1.36   Dec 02 2002 16:08:52   YINGBAOL
 * put some code back 
 * 
 *    Rev 1.35   Nov 06 2002 10:34:36   YINGBAOL
 * Sync. up release 49
 * 
 *    Rev 1.34   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.33   Oct 09 2002 16:39:42   HERNANDO
 * PTS 10009707 Fix; uses new fields.
 * 
 *    Rev 1.32   Aug 29 2002 16:45:20   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.31   Aug 29 2002 12:54:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.30   Aug 26 2002 11:30:20   HERNANDO
 * Added FedRate, FedRatePUD, ProvRate, and ProvRatePUD to IFASTBP_PROC::TRANS_LIST.
 * 
 *    Rev 1.29   Aug 09 2002 14:58:12   HERNANDO
 * PTS 10009355 - Added UseEnteredFee to IFASTBP_PROC::PENDING_LIST.
 * 
 *    Rev 1.28   Jun 27 2002 11:52:10   HERNANDO
 * Added BankChrgs field details to IFASTBP_PROC::TRANS_LIST and IFASTBP_PROC::PENDING_LIST.
 * 
 *    Rev 1.27   14 Jun 2002 10:17:48   YINGZ
 * fix parameter key problem
 * 
 *    Rev 1.26   13 Jun 2002 14:40:56   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.25   May 30 2002 11:08:30   KOVACSRO
 * Added PayMethod, ACHProcessor and ValueDate
 * 
 *    Rev 1.24   22 May 2002 18:25:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.23   27 Mar 2002 19:56:18   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.22   26 Feb 2002 16:53:22   HSUCHIN
 * added dsc redemption permission check
 * 
 *    Rev 1.21   Dec 13 2001 11:14:42   JANKAREN
 * Added Trade Date Lag 
 * 
 *    Rev 1.20   Nov 29 2001 17:04:46   HERNANDO
 * Added Barclays Dividends fields.
 * 
 *    Rev 1.19   Oct 17 2001 10:39:22   ZHANGCEL
 * Added BackDatedReason in IFASTBP_PROC::PENDING_LIST
 * 
 *    Rev 1.18   Aug 16 2001 13:28:28   ZHANGCEL
 * Added a new field: TransferTransId
 * 
 *    Rev 1.17   08 Aug 2001 14:26:36   HSUCHIN
 * use MFAccount to store the TransactionHistoryList for sub dialog usage
 * 
 *    Rev 1.16   Jul 09 2001 11:45:42   ZHANGCEL
 * Added a new field ModPerm
 * 
 *    Rev 1.15   Jun 11 2001 16:58:26   ZHANGCEL
 * Added logic for getting USER_ID.
 * 
 *    Rev 1.14   08 Jun 2001 15:12:20   KOVACSRO
 * Reseting Pending List container after a new search (bug fixed)
 * 
 *    Rev 1.13   Jun 08 2001 13:07:04   ZHANGCEL
 * Added two new fields: ExchInFee and ExchInFlatPercent Constructor.
 * 
 *    Rev 1.12   11 May 2001 16:33:38   YINGZ
 * code sync up
 * 
 *    Rev 1.11   03 May 2001 14:05:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Mar 12 2001 10:26:48   JANKAREN
 * Add AddFieldDetails(DBR::OfferPrice)
 * 
 *    Rev 1.9   Mar 06 2001 14:21:52   HERNANDO
 * Added addFieldDetails (DBR::SplitComm) from VW22 and VW54.
 * 
 *    Rev 1.8   Jan 30 2001 13:38:46   OLTEANCR
 * no change
 * 
 *    Rev 1.7   Jan 24 2001 12:59:46   KOVACSRO
 * getting PendingTradesList from MFAccount, rather than create a new list, also doing the refresh...
 * 
 *    Rev 1.6   15 Dec 2000 12:43:56   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Dec 13 2000 10:57:52   FENGYONG
 * Add filed PayType2 and change #17 and #54 DataSet  from PayType to PayType2
 * 
 *    Rev 1.4   Aug 25 2000 11:49:16   DINACORN
 * addFieldDetails DBR::BackDatedReason and DBR::GBCD for IFASTBP_PROC::TRANS_LIST
 * 
 *    Rev 1.3   Aug 08 2000 10:42:34   VADEANUM
 * Title Screen Standards
 * 
 *    Rev 1.2   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Jun 13 2000 18:06:20   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.24   Jan 20 2000 14:46:54   YINGZ
 * change currencyname to currency
 * 
 *    Rev 1.23   Jan 08 2000 14:33:02   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.22   Jan 06 2000 09:58:10   POPESCUS
 * cleanup code and remove some unused methods
 * 
 *    Rev 1.21   Dec 07 1999 14:20:26   YINGZ
 * add group to doset/get fiels
 * 
 *    Rev 1.20   Nov 02 1999 15:18:28   DT24433
 * removed doOk/doCancel and changed to use default locale instead of getting locale and passing it in
 * 
 *    Rev 1.19   Oct 29 1999 11:30:20   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.18   Oct 28 1999 12:40:42   PRAGERYA
 * Fixes for allocations
 * 
 *    Rev 1.17   Oct 11 1999 15:48:10   PRAGERYA
 * Allocation, Initial and GroupCode fields added
 * 
 *    Rev 1.16   Sep 27 1999 13:55:36   YINGZ
 * add dosetfield
 * 
 *    Rev 1.15   Sep 26 1999 18:29:24   VASILEAD
 * Added support for AllFunds mode in transactions screen
 * 
 *    Rev 1.14   Sep 14 1999 11:44:50   BUZILA
 * BFBase changes
 * 
 *    Rev 1.13   Aug 31 1999 16:56:16   DT24433
 * misc. cleanup
 * 
 *    Rev 1.12   Aug 31 1999 12:21:46   DT24433
 * changed dogetfield parms
 * 
 *    Rev 1.11   Aug 25 1999 11:44:02   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.10   Aug 24 1999 15:44:58   YINGZ
 * Format issue
 * 
 *    Rev 1.9   Aug 04 1999 20:55:20   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.6   Jul 22 1999 15:06:42   YINGZ
 * ?
 * 
 *    Rev 1.5   Jul 22 1999 14:59:46   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.4   Jul 20 1999 14:25:32   YINGZ
 * fund list should also be refreshed
 * 
 *    Rev 1.3   Jul 20 1999 11:14:16   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 16 1999 14:34:08   YINGZ
 * add new fields
 * 
 *    Rev 1.1   Jul 08 1999 10:02:14   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
