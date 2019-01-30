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
// ^FILE   : TradesProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradesProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "confirmationprocessincludes.h"
#include "etrackheader.h"
#include "fillsearchcriteriaprocessincludes.h"
#include "rebookparamprocessincludes.h"
#include "rebookprocessincludes.h"
#include "searchprocessincludes.h"
#include "tradesprocess.hpp"
#include "tradesprocessincludes.h"
#include "tradesettlelocationsprocessincludes.h"
#include "respbeneficiaryallocationlistprocessincludes.h"


#include <bfproc\genericinterfacecontainer.hpp>
//CBO's
#include <ifastcbo\agent.hpp>
#include <ifastcbo\acctcategorylist.hpp>
#include <ifastcbo\address.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\aggregatedorder.hpp>
#include <ifastcbo\aggregatedorderlist.hpp>
#include <ifastcbo\branch.hpp>
#include <ifastcbo\broker.hpp>
#include <ifastcbo\dilutionalloclist.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\MatSweepInstr.hpp>
#include <ifastcbo\MatSweepInstrDetailsList.hpp>
#include <ifastcbo\funddetail.hpp>
#include <ifastcbo\manualforeigncapgainallocadjustment.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\splitcommission.hpp>
#include <ifastcbo\splitcommissionlist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\tradeacctalloc.hpp>
#include <ifastcbo\tradeacctalloclist.hpp>
#include <ifastcbo\tradefundalloc.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\tradepayinstruct.hpp>
#include <ifastcbo\tradepayinstructlist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <configmanager.hpp>
#include <ifastdataimpl\dse_dstc0441_vw.hpp>

//the gui process
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MANUAL_DIVIDEND;
//bp processes
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PURCHASE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EXCHANGE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REDEMPTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AGGREGATED_ORDER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator <TradesProcess> processCreator1 (CMD_BPROC_TRADES);
static ConcreteProcessCreator <TradesProcess> processCreator2 (CMD_BPROC_PURCHASE);
static ConcreteProcessCreator <TradesProcess> processCreator3 (CMD_BPROC_REDEMPTION);
static ConcreteProcessCreator <TradesProcess> processCreator4 (CMD_BPROC_EXCHANGE);

namespace
{
   const I_CHAR * const CLASSNAME      = I_ ("TradesProcess");
   const I_CHAR * const BATCH          = I_ ("Batch");
   const I_CHAR * const FC_TRANS_TYPE  = I_ ("FC");
   const DString EMPTY_STRING;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long ERR_NO_SLSREP_FOUND;
}

namespace CONFPROC
{
   const DString BATCH( I_("Batch") );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId FCFundRate;
   extern CLASS_IMPORT const BFDecimalFieldId FCFundToRate;
   extern CLASS_IMPORT const BFTextFieldId Cancelled;
   extern CLASS_IMPORT const BFTextFieldId Reversal;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramLenList;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramTypeList;
   extern CLASS_IMPORT const BFTextFieldId PSEProgramYearList;
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
   extern CLASS_IMPORT const BFTextFieldId Selected;
   extern CLASS_IMPORT const BFTextFieldId GIRedemOrder;
   extern CLASS_IMPORT const BFTextFieldId RightToCancel;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId SDRTExemptCode;
   extern CLASS_IMPORT const BFTextFieldId NegMoneyMktInt;
   extern CLASS_IMPORT const BFTextFieldId RoundCalcToCents;
   extern CLASS_IMPORT const BFTextFieldId PrcsSpDiv;
   extern CLASS_IMPORT const BFDecimalFieldId NumUnitEligDividends;
   extern CLASS_IMPORT const BFDecimalFieldId NumUnitDividends;
   extern CLASS_IMPORT const BFDecimalFieldId ReinvestmentRate;
   extern CLASS_IMPORT const BFDecimalFieldId DivRate;
   extern CLASS_IMPORT const BFTextFieldId HighRiskLevels;
   extern CLASS_IMPORT const BFTextFieldId RemarkAlertExists;
   extern CLASS_IMPORT const BFTextFieldId AlertMessageExists;
   extern CLASS_IMPORT const BFTextFieldId AlertViewed;
   extern CLASS_IMPORT const BFNumericFieldId AltFndIdntfr;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFTextFieldId FullMoneyOutIndc;
   extern CLASS_IMPORT const BFTextFieldId GateOverrideIndicator;
   extern CLASS_IMPORT const BFDateFieldId RDSPPaymtDate;
}

namespace ALERT_MSG_OPENED_FROM
{
    extern CLASS_IMPORT I_CHAR * const TRADE;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TradesProcess::TradesProcess ( GenericInterfaceContainer *pGIC, 
                               GenericInterface *pGIParent, 
                               const Command &rCommand) : AbstractProcess (pGIC, pGIParent, rCommand),
_rpChildGI (NULL),
_pTradesList (NULL),
_isCancelHitOnVerifySearch (NULL_STRING),
_accountNum (NULL_STRING),
_aggregatedOrderTradeDate (NULL_STRING),
_currentBusinessDate (NULL_STRING),
_listKey (NULL_STRING),
_caller (NULL_STRING),
_track (NULL_STRING),
_activity (NULL_STRING),
_reset (NULL_STRING),
_rebookExist (NULL_STRING),
_transNum (NULL_STRING),
_pPendingTrades (NULL),
_pSplitCommissionList (NULL),
_bIsARollover (false),
_fromfund(NULL_STRING),
_fromclass(NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   assert (pDSTCWorkSession);
   pDSTCWorkSession->getOption ( ifds::CurrBusDate, 
                                 _currentBusinessDate, 
                                 BF::HOST, 
                                 false);
//add containers
//trade list container
   addContainer ( IFASTBP_PROC::TRADES_LIST, 
                  true,  //repeatable
                  BF::NullContainerId,
                  true,  //updatable
                  I_("Trade")
   );
   addContainer ( SHAREHOLDER_ADDRESS, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,  //not updatable
                  I_("ShareholderAddress")
   );   
   addContainer ( BROKER, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,  //not updatable
                  I_("Broker")
   );   
   addContainer ( BRANCH, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,  //not updatable
                  I_("Branch")
   );
   addContainer ( AGENT, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,  //not updatable
                  I_("Agent")
   );
   addContainer ( ACCOUNT, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true,   //updatable
                  I_("Account")
   );
   addContainer ( ACCOUNT_CATEGORY_LIST, 
                  true,  //repeatable
                  ACCOUNT,
                  false, //not updatable
                  I_("AccountCategoryList")
   );
   addContainer ( SHAREHOLDER, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,  //not updatable
                  I_("Shareholder")
   );
   addContainer ( ACCOUNT_HOLDINGS, 
                  true,  //repeatable
                  ACCOUNT,
                  false, //not updatable
                  I_("AccountHoldings")
   );
   addContainer ( ADDRESS, 
                  false, //non-repeatable
                  SHAREHOLDER,
                  false, //not updatable
                  I_("Address")
   );
   addContainer ( ACCOUNT_TO, 
                  false,  //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true,   //updatable
                  I_("AccountTo")
   );
   addContainer ( ACCOUNT_CATEGORY_LIST_TO, 
                  true,   //repeatable
                  ACCOUNT_TO,
                  false,  //non-updatable
                  I_("AccountCategoryListTo")
   );
   addContainer ( SHAREHOLDER_TO, 
                  false,   //non-repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false,   //not updatable
                  I_("ShareholderTo")
   );
   addContainer ( ACCOUNT_HOLDINGS_TO, 
                  true,  //repeatable
                  ACCOUNT_TO,
                  false, //not updatable
                  I_("AccountHoldingsTo")
   );
   addContainer ( ADDRESS_TO, 
                  false,  //non-repeatable
                  SHAREHOLDER_TO,
                  false,  //not updatable
                  I_("AddressTo")
   );
   if (isXMLAPIContext())
   {
      addContainer ( IFASTBP_PROC::ACCT_ALLOCATION, 
                     true,  //repeatable
                     IFASTBP_PROC::TRADES_LIST, 
                     false,  //not-updatable
                     I_("trade_account_allocation") 
      );
   }
//fund allocation list, parent the trades list
   addContainer ( IFASTBP_PROC::FUND_ALLOCATION, 
                  true,
                  IFASTBP_PROC::TRADES_LIST, 
                  true,
                  I_("trade_fund_allocation")
   );
//split commissions list, parent the fund allocation container
   addContainer ( IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
                  true, 
                  IFASTBP_PROC::FUND_ALLOCATION, 
                  true, 
                  I_("SplitCommission")
   );
//fund allocation list, parent the trades list
   addContainer ( TRANS_FEE_LIST, 
                  true,
                  IFASTBP_PROC::TRADES_LIST, 
                  true,
                  I_("TransFeeList")
   );
//fund allocation list, parent the trades list
   addContainer ( PENDING_TRADES_LIST, 
                  true, //repeatable
                  BF::NullContainerId,  //no parent (account/aggregate order can be its parent)
                  false, //non-updatable
                  I_("PendingTradeList") //the name is for API 
   );
   addContainer ( PENDING_TRADE, 
                  false, //repeatable
                  PENDING_TRADES_LIST,
                  false, //non-updatable
                  I_("PendingTrade")
   );
//aggregated order container
   addContainer ( AGGREGATED_ORDER, 
                  false, //repeatable
                  BF::NullContainerId,
                  false, //non-updatable
                  I_("AggregatedOrder")
   );

//dilution container
   addContainer ( DILUTION_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("DilutionList")
   );
//GIA Atributes fields
   addFieldDetails ( ifds::IntInvestType,
                     IFASTBP_PROC::TRADES_LIST
   );

   addFieldDetails ( ifds::IntCalcMthd,
                     IFASTBP_PROC::TRADES_LIST
   );

   addFieldDetails ( ifds::InvestTerm,
                     IFASTBP_PROC::TRADES_LIST
   );

   addFieldDetails ( ifds::IntCredFreq,
                     IFASTBP_PROC::TRADES_LIST
   );

//Maturity instructions container
   addContainer ( MAT_SWEEP_INSTRUCTIONS_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("Maturity Instructions")
   );

   //multiple settle loc container
   addContainer ( TRADE_MULTI_SETTLEMENT_LOC_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("DilutionList")
   );
//split payments constainer
   addContainer ( TRADE_PAY_INSTRUCT_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("TradePayInstructList")
   );
   
   //resp beneficiary alloc list container
   addContainer ( RESP_BENEF_ALLOC_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("RESPBeneficiaryAllocationList")
   );

   //resp transfer data container
   addContainer ( RESP_TRANSFER_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("RESPTransferList")
   );
   addContainer ( IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, 
                  true, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  false, //non-updatable
                  I_("GIInvestmentList")
   );
   addContainer (IFASTBP_PROC::ESTATE_ALLOCATION, 
                 true, //repeatable
                 IFASTBP_PROC::TRADES_LIST, 
                 false, //non-updatable
                 I_("EstateAllocation")
   );   
   addContainer ( RDSP_TRANSFER, 
                  false, //repeatable
                  IFASTBP_PROC::TRADES_LIST,
                  true, //non-updatable
                  I_("RDSPTransfer")
   );

//transaction type   
   addFieldDetails ( ifds::TradesTransType, 
                     IFASTBP_PROC::TRADES_LIST
   );
//batch,trace, trans num,
   addFieldDetails ( ifds::BatchName, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Trace, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TransNum, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GoodBad, 
                     IFASTBP_PROC::TRADES_LIST
   );
//fund, account
   //one side, from side
   addFieldDetails ( ifds::AccountNum, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::LinkedEntityId, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AltAccount, 
                     ACCOUNT,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::XrefNum, 
                     ACCOUNT,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsAccountSetAndValid, 
                     ACCOUNT,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsClearingAccount,
                     ACCOUNT,
                     SUBCLASS_PROCESS
   ); 
   addFieldDetails ( ifds::FromFund, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::FromClass, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::FromFundNumber, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundISIN, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundWKN,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundLFC,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CUSIP,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Baycom, 
                     IFASTBP_PROC::TRADES_LIST
   );
   //two side
   addFieldDetails ( ifds::AccountTo, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AltAccount, 
                     ACCOUNT_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::XrefNum, 
                     ACCOUNT_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsAccountSetAndValid, 
                     ACCOUNT_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsClearingAccount,
                     ACCOUNT_TO,
                     SUBCLASS_PROCESS
   );  
   addFieldDetails ( ifds::ToFund, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::ToClass, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::ToFundNumber, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundToISIN, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundToWKN, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundToLFC, 
                     IFASTBP_PROC::TRADES_LIST
   );
    addFieldDetails ( ifds::ToCUSIP, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ParticipantID, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundIDType, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundIDValue, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::MCHFileIndicator, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SecRecFileIndicator, 
                     IFASTBP_PROC::TRADES_LIST
   );

//units, value, balance
   addFieldDetails ( ifds::AccountBalance, 
                     ACCOUNT
   );
   addFieldDetails ( ifds::SettledUnits, 
                     ACCOUNT_HOLDINGS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SettledValue, 
                     ACCOUNT_HOLDINGS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AccountBalance, 
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::SettledUnits, 
                     ACCOUNT_HOLDINGS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SettledValue, 
                     ACCOUNT_HOLDINGS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Grp1Shares, 
                     ACCOUNT_HOLDINGS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Grp2Shares, 
                     ACCOUNT_HOLDINGS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Grp1Shares, 
                     ACCOUNT_HOLDINGS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Grp2Shares, 
                     ACCOUNT_HOLDINGS_TO,
                     SUBCLASS_PROCESS
   );
//dates
   addFieldDetails ( ifds::EffectiveDate, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SettleDate, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DepositDate,
                     IFASTBP_PROC::TRADES_LIST
   );

//order type/wire number
   addFieldDetails ( ifds::OrderType, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::WireOrdNum,
                     IFASTBP_PROC::TRADES_LIST
   );   
//amount, payment
   addFieldDetails ( ifds::Amount, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AmtType, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::GrossOrNet,
                     IFASTBP_PROC::TRADES_LIST
   );
//shareholder address
   addFieldDetails ( ifds::AddrCode,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
//G1 G2 user input for trade
   addFieldDetails ( ifds::G1Impact,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::G2Impact,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Name, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine1, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine2, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine3, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine4, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine5, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );   
   addFieldDetails ( ifds::PostalCode, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::CountryCode, 
                     SHAREHOLDER_ADDRESS,
                     SUBCLASS_PROCESS
   );   
//from address
   addFieldDetails ( ifds::Name, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine1, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine2, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine3, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine4, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine5, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::PostalCode, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::CountryCode, 
                     ADDRESS,
                     SUBCLASS_PROCESS
   );
//to address
   addFieldDetails ( ifds::Name, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine1, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine2, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine3, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine4, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::AddrLine5, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::PostalCode, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::CountryCode, 
                     ADDRESS_TO,
                     SUBCLASS_PROCESS
   );
//broker/branch/salesrep
   addFieldDetails ( ifds::Broker, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Branch, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SlsrepCode, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::BrokerName, 
                     BROKER,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::BranchName, 
                     BRANCH,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SlsrepName, 
                     AGENT,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ShouldAskForRep, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::CreateRep, 
                     IFASTBP_PROC::TRADES_LIST
   );
   
//from/to acct/shr info
   addFieldDetails ( ifds::ShrNum, 
                     SHAREHOLDER
   );
   addFieldDetails ( ifds::ShrNum, 
                     SHAREHOLDER_TO
   );
//cautions, from account
   addFieldDetails ( ifds::PendingTrade,
                     ACCOUNT
   );
   addFieldDetails ( ifds::Certificates,
                     ACCOUNT
   );
   addFieldDetails ( ifds::StopPurchase,
                     ACCOUNT
   );
   addFieldDetails ( ifds::StopRed,
                     ACCOUNT
   );
   addFieldDetails ( ifds::StopRedSettle,
                     ACCOUNT
   );
   addFieldDetails ( ifds::StopXferOut,
                     ACCOUNT
   );
   addFieldDetails ( ifds::StopXferIn,
                     ACCOUNT
   );
   addFieldDetails ( ifds::UnsettledTrn,
                     ACCOUNT
   );
   addFieldDetails ( ifds::Remarks,
                     SHAREHOLDER
   );
   addFieldDetails ( ifds::HighestEntityRisk,
                     ACCOUNT,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::DTAType,
                     ACCOUNT
   );   
   addFieldDetails ( ifds::AcctCategory,
                     ACCOUNT_CATEGORY_LIST
   );
   addFieldDetails ( ifds::NetworkID,
                     ACCOUNT
   ); 
   addFieldDetails ( ifds::ExistAssignee,
                     ACCOUNT
   ); 
   addFieldDetails ( ifds::GSTExempt,
                     ACCOUNT
   ); 
   addFieldDetails ( ifds::ApplyPST,
                     ACCOUNT
   ); 
   addFieldDetails ( ifds::AlertViewed,
                     BF::NullContainerId,
                     SUBCLASS_PROCESS
   ); 
   addFieldDetails ( ifds::RemarkAlertExists,
                     ACCOUNT,
                     SUBCLASS_PROCESS
   ); 
   addFieldDetails ( ifds::AlertMessageExists,
                     ACCOUNT,
                     SUBCLASS_PROCESS
   ); 
//cautions, to account
   addFieldDetails ( ifds::PendingTrade,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::Certificates,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::StopPurchase,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::StopRed,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::StopRedSettle,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::StopXferOut,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::StopXferIn,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::UnsettledTrn,
                     ACCOUNT_TO
   );
   addFieldDetails ( ifds::Remarks,
                     SHAREHOLDER_TO
   );
   addFieldDetails ( ifds::HighestEntityRisk,
                     ACCOUNT_TO,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::DTAType,
                     ACCOUNT_TO
   );   
   addFieldDetails ( ifds::AcctCategory,
                     ACCOUNT_CATEGORY_LIST_TO
   );
   addFieldDetails ( ifds::NetworkID,
                     ACCOUNT_TO
   ); 
   addFieldDetails ( ifds::ExistAssignee,
                     ACCOUNT_TO
   ); 
   addFieldDetails ( ifds::GSTExempt,
                     ACCOUNT_TO
   ); 
   addFieldDetails ( ifds::ApplyPST,
                     ACCOUNT_TO
   ); 
//tax rates
   addFieldDetails ( ifds::FedRate, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ProvRate, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TransRatePUDFed, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TransRatePUDProv, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OverrideTax, 
                     IFASTBP_PROC::TRADES_LIST
   );
// remarks
   addFieldDetails ( ifds::Remarks1,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Remarks2,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Remarks3,
                     IFASTBP_PROC::TRADES_LIST
   );
//API fields
   addFieldDetails ( ifds::NetworkID,               //in attributes grid, as well
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::ExtTransNum,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::SendRefNum,              //in attributes grid, as well
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::PartRefNum,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::MasterRefNum,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::ExternalPrice,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::ExternalSettleDate,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::ExternalSettleAmt,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::FundCurrency,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ExternalInstitution,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RefundAmtOpt,
                     IFASTBP_PROC::TRADES_LIST
   );

   addFieldDetails ( ifds::AltFndIdntfr,
                     BF::NullContainerId,
                     SUBCLASS_PROCESS
   ); 
   if (isXMLAPIContext()) //API fee fields
   {
      addFieldDetails ( ifds::Fee,
                        IFASTBP_PROC::TRADES_LIST,
                        SUBCLASS_PROCESS
      );
      addFieldDetails ( ifds::FlatPercent,
                        IFASTBP_PROC::TRADES_LIST,
                        SUBCLASS_PROCESS
      );
      addFieldDetails ( ifds::ToFlatPercent,
                        IFASTBP_PROC::TRADES_LIST,
                        SUBCLASS_PROCESS
      );

      addFieldDetails ( ifds::TrxnFee,
                        IFASTBP_PROC::TRADES_LIST,
                        SUBCLASS_PROCESS
      );
   }
//bank fields
   addFieldDetails ( ifds::BankIdType,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::InstName,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::BankIdValue,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::BankAcctName,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::BankAcctNum,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettleDateOverriden, //set when user changes the settlement date
                     IFASTBP_PROC::TRADES_LIST
   );   
   addFieldDetails ( ifds::ValueDateOverriden, //set when user changes the value date
                     IFASTBP_PROC::TRADES_LIST
   );   
//the grid headings
   addFieldDetails ( ifds::TradeAttributesHeading,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TradeAttributesFields, 
                     IFASTBP_PROC::TRADES_LIST
   );
//the attribute grid fields
   addFieldDetails ( ifds::PayInstrOption,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TradesPayType,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PayMethod,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ACHProcessor,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DepositType,             //in attributes grid
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::SettleCurrency,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ExchRate,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Accountable,             //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::BackDatedReason,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettleNetwork,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DilutionLinkNum,         
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AcqFeeOption,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::DiscountRate,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FundBrokerCode,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AggregateOption,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AggOrdAdjustNum,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DealDate,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettleInDate,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DealTime,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CashDate,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );  
   addFieldDetails ( ifds::ValueDate,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DepId,                   //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ProvSales,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SrcOfFund,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SrcOfAccount,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettledBy,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OrderSource,             //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettleSource,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SettleType,              //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ExpGNSettle,             //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RecptIssued,             //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CertRequired,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::InitPurch,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::BorrowedFunds,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::MFPayment,              //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SuppressCode,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DeliveryMethod,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RedCode,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::LSIFCode,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );   
   addFieldDetails ( ifds::BankChrgs,              //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FromCurrency,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::UseEnteredFee,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ConfirmRequired,        //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OtherConfirmType,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CloneAcctAMS,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AssocTransId,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RESPReportHRDC,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GRRepayReason,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GRRepayReasonCommon,    //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GRRepayReasonQESI,      //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GRRepayReasonRDSP,      //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OCRdmYear,              //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Tainted,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RESPContrDetlTaxYear,   //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AssistedContrAmt,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::NetworkRespRequired,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PFCrystalisation,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PaymentInfo,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PendTrdContract,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ValuationDt,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GuaranteesOverride,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   //IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
   addFieldDetails ( ifds::EAPCESGPaid,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST                  
   );
   addFieldDetails ( ifds::RedemOrder,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST                  
   );
   addFieldDetails ( ifds::GIRedemOrder,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST                  
   );
   addFieldDetails ( ifds::RightToCancel,          //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RDRAdvice,       //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SDRTExemptCode,          //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PSDAdvice,
					 IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails( ifds::PymtRoutingMthd,
					IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails( ifds::EventReceiptDate,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::EventReceiptTime,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails(  ifds::SourceOfTrade,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ChannelOfTrade,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Platform,					 //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::DeliveryNetwork,				   //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CrossSysAcctNum,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AggregationType,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::SourceofFundsChecked,    //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Deconversion,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OrderRouting,            //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TradeInDate,            //in attributes grid
					 IFASTBP_PROC::TRADES_LIST,
					 SUBCLASS_PROCESS
					 );
   addFieldDetails ( ifds::ValuationInDt,          //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
					 );
   addFieldDetails ( ifds::PricingCode,          //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
					 );
   addFieldDetails ( ifds::PriceInCode,          //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
					 );
   addFieldDetails ( ifds::FullMoneyOutIndc,	 //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
				   );
   addFieldDetails ( ifds::GateOverrideIndicator,          //in attributes grid
					 IFASTBP_PROC::TRADES_LIST
					 );
   addFieldDetails( ifds::RDSPPaymtDate,         //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
//calculated fields
   addFieldDetails ( IsBankingNeeded, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsShareholderAddressNeeded, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsCancelHitOnVerifySearch, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( AreAllocationsAllowed, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsSplitCommissionAllowed, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( AcqFeeType, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( AreTaxRatesAllowed, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsEUSDApplicable, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsFundInScope, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsFundLookedThru, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
//fund allocations list
   addFieldDetails ( ifds::AllocAmount, 
                     IFASTBP_PROC::FUND_ALLOCATION
   );
   addFieldDetails ( ifds::FundCode, 
                     IFASTBP_PROC::FUND_ALLOCATION
   );
   addFieldDetails ( ifds::ClassCode, 
                     IFASTBP_PROC::FUND_ALLOCATION
   );
   addFieldDetails ( ifds::AllocAmtType, 
                     IFASTBP_PROC::FUND_ALLOCATION
   );
   addFieldDetails ( ifds::AllocPercentage, 
                     IFASTBP_PROC::FUND_ALLOCATION
   );
//split commmissions list
   addFieldDetails ( ifds::CommEntTypeDesc, 
                     IFASTBP_PROC::SPLIT_COMMISSION_LIST
   );
   addFieldDetails ( ifds::CommEntName, 
                     IFASTBP_PROC::SPLIT_COMMISSION_LIST
   );
   addFieldDetails ( ifds::CommRate, 
                     IFASTBP_PROC::SPLIT_COMMISSION_LIST
   );
   addFieldDetails ( ifds::CommPrcnt, 
                     IFASTBP_PROC::SPLIT_COMMISSION_LIST
   );
   addFieldDetails ( ifds::CommAmount, 
                     IFASTBP_PROC::SPLIT_COMMISSION_LIST
   );
//transaction fees list and grid
   addFieldDetails ( ifds::TransFeeCode, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::FeeType, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::FeeCharge, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::FeeRate, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::TradeFeeOption, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::Currency, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( ifds::ChargeOption, 
                     TRANS_FEE_LIST
   );
   addFieldDetails ( IsChargeFee, 
                     TRANS_FEE_LIST,
                     SUBCLASS_PROCESS
   );
//settle location fields
   addFieldDetails ( ifds::FrSettlLocCode,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ToSettlLocCode,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FrClearingMethod,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ToClearingMethod,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FrSettlInstrCode,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ToSettlInstrCode,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FrDeliveryTo,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ToDeliveryTo,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( IsSettleLocAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );  
   addFieldDetails ( AreMultipleSettleLocAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );

   addFieldDetails ( AreRESPBenefAllocationsAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );

   addFieldDetails ( IsRESPTransferAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsPSEEAPAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsMaturityInstrAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsGIAAttribAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsGIInvestmentListApplicable,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsEstateAllocationListApplicable,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( RefreshRESPBenefAllocation,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( RefreshRESPTransfers,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsAssociationToOriginalContribAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );   
   addFieldDetails ( Reset,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );  
   addFieldDetails ( ifds::PurchaseTotal,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );  
   addFieldDetails ( ifds::TransModPerm,
                     IFASTBP_PROC::TRADES_LIST
   );  
   addFieldDetails ( ifds::ForceVerify,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( ifds::ROAAmount,
                     IFASTBP_PROC::TRADES_LIST 
   );
   addFieldDetails ( IsDilutionAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( isCASHSettleESGElig,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsRebook,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsRefund,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::Accountable,
                     DILUTION_LIST
   );
   addFieldDetails ( ifds::AllocPercent,
                     DILUTION_LIST
   );
   addFieldDetails ( ifds::RespDate,
                     DILUTION_LIST
   );
   addFieldDetails ( ifds::BackDatedReason,
                     DILUTION_LIST
   );

   addFieldDetails ( ifds::BillingToEntity,
                     DILUTION_LIST
   );
   addFieldDetails ( ifds::AssociatedAcctNum,
                     DILUTION_LIST
   );
   // multi settle loc
   addFieldDetails ( ifds::SettleLocCode,
                     TRADE_MULTI_SETTLEMENT_LOC_LIST
   );

   addFieldDetails ( ifds::TransClrSettlAmt,
                     TRADE_MULTI_SETTLEMENT_LOC_LIST
   );
   addFieldDetails ( ifds::InFavourOf,
                     TRADE_MULTI_SETTLEMENT_LOC_LIST
   );
   // maturity instr:
   addFieldDetails ( ifds::MatInstrLevel,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );

   addFieldDetails ( ifds::MatSwpInstructionType,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );
   addFieldDetails ( ifds::Fund,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );

   addFieldDetails ( ifds::Class,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );
    addFieldDetails ( ifds::SplitType,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );
	  addFieldDetails ( ifds::EffectiveDate,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );
	    addFieldDetails ( ifds::CashSweepBal,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );
    addFieldDetails ( ifds::SelectedAmt,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );

   addFieldDetails ( ifds::GoodBad,
                     MAT_SWEEP_INSTRUCTIONS_LIST
   );

   // resp transfer:
   addFieldDetails ( ifds::RecordLevel,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::RESPBenefIDFrom,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::TaxJuris,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::BenefEffectiveDate,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::Relation,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::RESPAllocPrcnt,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::BenefDofB,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::GrantRequest,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::Tainted,
                     RESP_TRANSFER_LIST
   );
   addFieldDetails ( ifds::TaintEndDate,
                     RESP_TRANSFER_LIST
   );

   addFieldDetails ( ifds::HistNonTrustYear,
                     RESP_TRANSFER_LIST
   );

  
   // resp benef allocaiton list: 
  addFieldDetails ( ifds::RESPBenefId,
                     RESP_BENEF_ALLOC_LIST
   );

   addFieldDetails ( ifds::RESPAllocAmt,
                     RESP_BENEF_ALLOC_LIST
   );
   
   addFieldDetails ( ifds::RESPAllocPrcnt,
                     RESP_BENEF_ALLOC_LIST
   );

   addFieldDetails ( ifds::BenefDofB,
                     RESP_BENEF_ALLOC_LIST
   );
   
   addFieldDetails ( ifds::HRDCRelateCode,
                     RESP_BENEF_ALLOC_LIST
   );

   addFieldDetails ( ifds::TaxJuris,
                     RESP_BENEF_ALLOC_LIST
   );
    
   addFieldDetails ( ifds::EffectiveDate,
                     RESP_BENEF_ALLOC_LIST
   );

   addFieldDetails ( ifds::AllocEntityType,
                     RESP_BENEF_ALLOC_LIST
   );
   
   addFieldDetails ( ifds::AllocEntityTypeSeq,
                     RESP_BENEF_ALLOC_LIST
   );

//pse-eap
   addFieldDetails ( ifds::PSEProgramLenList,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PSEProgramTypeList,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::PSEProgramYearList,
                     IFASTBP_PROC::TRADES_LIST
   );

// eusd phase II
   addFieldDetails ( ifds::OverrideTIS,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TIS,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::OverrideCost,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Cost,
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ESGSettle,
                     IFASTBP_PROC::TRADES_LIST
   );
//STP - payment processing
   addFieldDetails ( ArePayInstructAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ifds::PaymentFor,
                     TRADE_PAY_INSTRUCT_LIST
   );
   addFieldDetails ( ifds::PayType,
                     TRADE_PAY_INSTRUCT_LIST
   );
   addFieldDetails ( ifds::PayMethod,
                     TRADE_PAY_INSTRUCT_LIST
   );
   addFieldDetails ( ifds::ConsolType,
                     TRADE_PAY_INSTRUCT_LIST
   );
   addFieldDetails ( ifds::ACHProcessor,
                     TRADE_PAY_INSTRUCT_LIST
   );
   addFieldDetails ( ifds::AllocPercent,
                     TRADE_PAY_INSTRUCT_LIST
   );
//account cloning
   addFieldDetails ( IsAccountCloningAllowed,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( ClonedAcountNum,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );   
   
//Fund's Unit Precision
   addFieldDetails ( AmountDecimalDigit,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS);

   addFieldDetails ( ifds::FCFundRate, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS);

   addFieldDetails ( ifds::FCFundToRate, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS);

   addFieldDetails( ifds::IsInvSelected,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::InvHisNumber,      IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::InvHisDepDate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::InvHisMatDate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::InvHisIntRate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::Principal,         IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::InvHisCurMktVal,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::ValueAtMaturity,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::SelInvAmtType,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::SelInvAmount,      IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::PrincRedeemed,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::AccruedInterest,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::AdminFee,          IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::MVA,               IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
   addFieldDetails( ifds::AmountNet,         IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);


   addFieldDetails( ifds::BenefEntityID,      IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefName,          IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefPrcnt,         IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefAmount,        IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefUnits,         IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefAddrLevel,     IFASTBP_PROC::ESTATE_ALLOCATION);
   addFieldDetails( ifds::BenefAddrCode,      IFASTBP_PROC::ESTATE_ALLOCATION);

   addFieldDetails(ifds::NegMoneyMktInt,       IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::RoundCalcToCents,     IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::PrcsSpDiv,            IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::NumUnitEligDividends, IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::NumUnitDividends,     IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::ReinvestmentRate,     IFASTBP_PROC::TRADES_LIST);
   addFieldDetails(ifds::DivRate,              IFASTBP_PROC::TRADES_LIST);
   //G1G2Applicable
   addFieldDetails ( isG1G2Applicable, IFASTBP_PROC::TRADES_LIST, SUBCLASS_PROCESS );

   addFieldDetails ( RefreshRDSPTransfers, IFASTBP_PROC::TRADES_LIST, SUBCLASS_PROCESS);
   addFieldDetails ( IsRDSPTransferAllowed, IFASTBP_PROC::TRADES_LIST, SUBCLASS_PROCESS);

   addFieldDetails(ifds::TaxType, ACCOUNT);    

   addFieldDetails ( ifds::CashDateOverriden,  IFASTBP_PROC::TRADES_LIST); //set when user changes the Cash date

}

//******************************************************************************
TradesProcess::~TradesProcess()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   _rpChildGI = NULL;
//erase the map of conditions
   CONDITIONS_MAP::iterator mc_iter = _conditionsMap.begin ();

   while (mc_iter != _conditionsMap.end())
   {
      CONDITIONVECTOR *pSearchConditions = 
            (*mc_iter).second;

      if (pSearchConditions) //erase conditions
      {
         CONDITIONVECTOR::iterator v_iter = 
               pSearchConditions->begin();

         while (v_iter != pSearchConditions->end())
         {
            delete *v_iter;
            v_iter = pSearchConditions->erase (v_iter);
         }
         delete pSearchConditions;
         pSearchConditions = NULL;        
      }
      mc_iter = _conditionsMap.erase (mc_iter);
   }
//erase the map of values
   VALUES_MAP::iterator mv_iter = 
         _valuesMap.begin ();

   while (mv_iter != _valuesMap.end())
   {
      mv_iter = _valuesMap.erase (mv_iter);
   }
   if (_pPendingTrades)
   {
      delete _pPendingTrades;
      _pPendingTrades = NULL;
   }
   if (_pSplitCommissionList)
   {
      delete _pSplitCommissionList;
      _pSplitCommissionList = NULL;
   }
}

//******************************************************************************
SEVERITY TradesProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   try
   {
      const BFDataGroupId &idDataGroup = getDataGroupId ();
      DSTCWorkSession* pDSTCWorkSession = 
            dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

      processParameters ();
      if (!isXMLAPIContext())
      {
         if ( _caller == I_("ModifyPendingTrade") || 
            ( _caller == I_("Rebook") && _sameAccountTransType == I_("Y")) ||
              _caller == I_("Refund"))
         {
            //use the the account that comes in
            modifyTrade (this, _accountNum); 
         }
         else if (_caller == I_("ModifyPendingTradesWithLoss"))
         {
            PendingTradeList *pPendingTradeList = 
                  dynamic_cast <PendingTradeList*> (getCBOList (PENDING_TRADES_LIST, idDataGroup));

            if (pPendingTradeList)
            {
               BFObjIter iter ( *pPendingTradeList, 
                                 idDataGroup, 
                                 true, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
               while (!iter.end())
               {
                  PendingTradeDetails *pPendingTradeDetails = 
                        dynamic_cast <PendingTradeDetails*> (iter.getObject());
                  DString accountNum;
                  
                  pPendingTradeDetails->getField (ifds::rxAcctNum, accountNum, idDataGroup);
                  setContainer (PENDING_TRADE, pPendingTradeDetails);
                  modifyTrade (this, accountNum, true); //refresh is required
                  ++iter;
               }
            }
         }
         else if (_caller == I_("FromAWD"))
         {
            DString transType,
               amount,
               amtType,
			   wireOrdNum;

            getParameter (I_("TradesTransType"), transType);
            getParameter (I_("Amount"), amount);
            getParameter (I_("AmtType"), amtType);
            getParameter (I_("WireOrdNum"), wireOrdNum);
            _pTradesList = 
               dynamic_cast <WorksessionTradesList*> (getCBOList ( IFASTBP_PROC::TRADES_LIST, 
                                                                     idDataGroup));
            assert (_pTradesList);
            _pTradesList->setField ( ifds::TradesTransType, 
                                     transType, 
                                     idDataGroup, 
                                     false, 
                                     false); // don't notify
            if (!_accountNum .empty ())
            {
               _pTradesList->setField ( ifds::AccountNum, 
                                        _accountNum, 
                                        idDataGroup, 
                                        false, 
                                        false); // don't notify

			   if (amount.empty ())
			   {
					amount = I_("0");
			   }
               _pTradesList->setField ( ifds::Amount, 
                                        amount, 
                                        idDataGroup, 
                                        false, 
                                        false); // don't notify
               _pTradesList->setField ( ifds::AmtType, 
                                        amtType, 
                                        idDataGroup, 
                                        false, 
                                        false); // don't notify

			   if (transType != TRADETYPE::EXCHANGE)
			   {
					_pTradesList->setField ( ifds::WireOrdNum, 
											wireOrdNum, 
											idDataGroup, 
											false, 
											false); // don't notify

					if (!wireOrdNum.empty ())
					{
						_pTradesList->setField ( ifds::OrderType, 
							                     I_("Y"), 
								                 idDataGroup, 
									             false, 
										         false); // don't notify
					}
			   }

               _pTradesList->setField ( ifds::FieldAssignment, 
                                        I_("FromAWD"), 
                                        idDataGroup, 
                                        false, 
                                        false); // don't notify
            }
         }
      }
      else  //api context
      {
         DString modify;

         getParameter (I_("TransType"), modify);
         if (!modify.empty())
         {
            _caller = I_("ModifyPendingTrade");
         }
         else
         {
            DString transType;

            getParameter (I_("TradesTransType"), transType);
            _pTradesList = 
               dynamic_cast <WorksessionTradesList*> (getCBOList ( IFASTBP_PROC::TRADES_LIST, 
                                                                   idDataGroup));
            assert (_pTradesList);
            _pTradesList->setField ( ifds::TradesTransType, 
                                     transType, 
                                     idDataGroup, 
                                     false, 
                                     false); // don't notify
            if (_accountNum != NULL_STRING)
            {
               _pTradesList->setField ( ifds::AccountNum, 
                                        _accountNum, 
                                        idDataGroup, 
                                        false, 
                                        false); // don't notify
            }
            else
            {
				  //search account by altaccount or XRefAccount
				  DString _altAccount, _xRefAccount, firstValue, searchUsing;
				  BFContainerId UsingContainer;

              getParameter (I_("AltAccount"), _altAccount);
				  getParameter (I_("xRefAccount"), _xRefAccount);
				  if (_xRefAccount.strip() != NULL_STRING)
				  {
					  UsingContainer = SEARCH_X_REF_NUM;
					  firstValue = _xRefAccount;
					  searchUsing = SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER;
				  }
				  else if (_altAccount.strip() != NULL_STRING)
				  {
					  UsingContainer = SEARCH_ALT_ACCOUNT;
					  firstValue = _altAccount;
					  searchUsing = SEARCHACCOUNTUSING::ALT_ACCOUNT_AND_BROKER_CODE;
				  }

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

              if (searchUsing == SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER)
              {
                 setParameter ( I_("ExactSearch"), I_("Y") ); //exact search for search by other reference num
              }              

				  performSearch (this, UsingContainer, SEARCH_START);
			  }

            DString payType;
            
            getParameter (I_("TradesPayType"), payType);			  
			  _pTradesList->setField ( ifds::TradesPayType, 
                                    payType, 
				         					idDataGroup, 
                                    false, 
                                    false); // don't notify
			  
			  _pTradesList->setField ( ifds::FieldAssignment, 
                                    I_("API"), 
                                    idDataGroup, 
                                    false, 
                                    false); // don't notify

         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN TradesProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doProcess"));
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      setParameter (MFCAN_IP_PARAM::CALLER, _caller);

      if (!isXMLAPIContext())
      {
         rtn = invokeCommand ( this, 
                               _caller == I_("ManualDividend") ? CMD_GUI_MANUAL_DIVIDEND : CMD_GUI_TRADES,
                               getProcessType(), 
                               isModal(),
                               &_rpChildGI);
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, 
                       DOPROCESS, 
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
SEVERITY TradesProcess::deleteItemFromList ( const GenericInterface *rpGICaller,
                                             const BFContainerId& idList)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DELETEITEMFROMLIST);

   if (idList == IFASTBP_PROC::TRADES_LIST)
   {
      removeCurrentTradeDataFromMaps();
   }
   return AbstractProcess::deleteItemFromList (rpGICaller, idList);
}

//******************************************************************************
void TradesProcess::doGetField ( const GenericInterface *rpGICaller,
                                 const BFContainerId &idContainer,
                                 const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup, 
                                 DString &strValueOut,
                                 bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField"));

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

   strValueOut = NULL_STRING;
   if (idContainer == IFASTBP_PROC::TRADES_LIST)
   {
      DString tradeKey = const_cast<TradesProcess*> (this)->
                           getCurrentListItemKey ( this,
                                                   IFASTBP_PROC::TRADES_LIST);
      if ( !tradeKey.empty() && 
           tradeKey.find (I_("DuplicateTradeCheck_")) == DString::npos) //this case is for reset/cancel
      {
         BFAbstractCBO *rpPtr = const_cast<TradesProcess*> (this)->
                              getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                           idDataGroup);
         if (rpPtr)
         {
            if ( idField == ifds::AccountNum || 
                 idField == ifds::AccountTo ||
                 idField == ifds::Broker ||
                 idField == ifds::Branch ||
                 idField == ifds::SlsrepCode ||
                 idField == ifds::EffectiveDate ||
                 idField == ifds::FromFund ||
                 idField == ifds::FromClass ||
                 idField == ifds::ToFund ||
                 idField == ifds::ToClass ||
                 idField == ifds::RedCode ||
                 idField == ifds::DepositType ||
                 idField == ifds::Amount ||
                 idField == ifds::AmtType ||
                 idField == ifds::AcqFeeOption ||
				 idField == ifds::TradeInDate)
            {
               rpPtr->getField ( idField, 
                                 strValueOut, 
                                 idDataGroup, 
                                 bFormatted);
            }
            else if (idField == ifds::AddrCode)
            {
               rpPtr->getField ( idField, 
                                 strValueOut, 
                                 idDataGroup, 
                                 false);
            }
            else if (idField == IsShareholderAddressNeeded)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isShareholderAddressNeeded (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsBankingNeeded)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isBankingNeeded (idDataGroup) && 
                                !pTrade->arePayInstructAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == ShouldAskForRep)
            {

               Broker *rpPtrBroker = dynamic_cast <Broker*> ( const_cast<TradesProcess*> (this)->
                                                                  getCBOItem (BROKER, idDataGroup));
               DString slsrepCode;

               rpPtr->getField (ifds::SlsrepCode, slsrepCode, idDataGroup, false);
               if (rpPtrBroker)
               {
                  strValueOut = 
                     !slsrepCode.empty() &&
                     rpPtr->getErrorState (ifds::Broker, idDataGroup) <= WARNING &&
                     rpPtr->getErrorState (ifds::Branch, idDataGroup) <= WARNING &&
                     rpPtr->getErrorState (ifds::SlsrepCode, idDataGroup) > WARNING && 
                     !rpPtrBroker->isHouseBroker (idDataGroup) ? I_("Y") : I_("N");
               }
               if (strValueOut == I_("Y")) 
               {                     
                  CONDITIONVECTOR conditions;
                  
                  if (rpPtr->getErrors (ifds::SlsrepCode, idDataGroup, conditions) > WARNING)
                  {
                     CONDITIONVECTOR::iterator iter = conditions.begin();
         
                     while (iter != conditions.end())
                     {
                        if ((**iter).getCode() == CND::ERR_NO_SLSREP_FOUND)
                        {
                           //if sales rep is not found, we can ask whether it should be created
                           break;
                        }
                        else
                        {
                           //other type of errors should not be used to create a new sales rep
                           strValueOut = I_("N");
                        }
                        ++iter;
                     }
                  }
               }            
            }
            else if (idField == IsCancelHitOnVerifySearch)
            {
               strValueOut = _isCancelHitOnVerifySearch;
            }
            else if (idField == Reset)
            {
               strValueOut = _reset;
            }            
            else if (idField == AreAllocationsAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->areAllocationsAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsSplitCommissionAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isSplitCommissionAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
			else if (idField == AcqFeeType)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
				  SplitCommissionList *pSplitCommissionList = NULL;

                  if (pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup, false) &&
					  pSplitCommissionList)
				  {
					  pSplitCommissionList->getField (ifds::FeeType, strValueOut, idDataGroup);
				  }
               }
            }
            else if (idField == AreTaxRatesAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->areTaxRatesAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsSettleLocAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isSettleLocAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == AreMultipleSettleLocAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->areMultipleSettleLocAllowed  (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == AreRESPBenefAllocationsAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->areRESPBenefAllocationsAllowed  (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsRESPTransferAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isRESPTransferAllowed  (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsPSEEAPAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isPSEEAPAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsAssociationToOriginalContribAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isAssociationToOriginalContribAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsGIAAttribAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isGIAAttribAllowed(idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if(idField == IsGIInvestmentListApplicable)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isGIInvestmentListApplicable(idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if(idField == IsEstateAllocationListApplicable)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isEstateAllocationListApplicable(idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if(idField == isG1G2Applicable)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isG1G2ApplicableTrade(idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsMaturityInstrAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isMaturityInstrAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == ifds::PurchaseTotal)
            {
               assert (_pTradesList);
               if (_pTradesList)
               {
                  _pTradesList->getField (ifds::PurchaseTotal, strValueOut, idDataGroup, false);
               }
            }
            else if (idField == ifds::Fee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  pTransFee->getField (ifds::FeeRate, strValueOut, idDataGroup, bFormatted);
               }
            }
            else if (idField == ifds::FlatPercent)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  DString feeType;

                  pTransFee->getField (ifds::FeeType, feeType, idDataGroup, true);
                  if (feeType == I_("0")) //flat
                  {
                     strValueOut = I_("Y");
                  }
                  else if (feeType == I_("1")) //percent
                  {
                     strValueOut = I_("N");
                  }
               }
            }
            else if (idField == ifds::TrxnFee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::TrxnFee) <= WARNING && 
                    pTransFee)
               {
                  pTransFee->getField (ifds::FeeRate, strValueOut, idDataGroup, bFormatted);
               }
            }
            else if (idField == IsDilutionAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isDilutionAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsRebook)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isRebook () ? I_("Y") : I_("N");
               }
            }
			else if (idField == IsRefund) 
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isRefund () ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsEUSDApplicable)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isEUSDApplicable (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsFundInScope)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isFundInScope (idDataGroup) ? I_("Y") : I_("N");               
               } 
            } 
            else if (idField == IsFundLookedThru)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isFundLookedThru (idDataGroup) ? I_("Y") : I_("N");
               }
            } 
            else if (idField == ArePayInstructAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->arePayInstructAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == IsAccountCloningAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isAccountCloningAllowed (idDataGroup) ? I_("Y") : I_("N");
               }
            }
            else if (idField == ClonedAcountNum)
            {
               if (const_cast<TradesProcess*> (this)->isAccountSetAndValid (ACCOUNT, idDataGroup))
               {
                  pDSTCWorkSession->getHostAccountNum (_accountNum, strValueOut);
               }
            }
			else if (idField == IsRDSPTransferAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isRDSPTransferAllowed  (idDataGroup) ? I_("Y") : I_("N");
               }
            }

            else if (idField == AmountDecimalDigit)
            {
               DString dstrAmtType;
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);
               pTrade->getField(ifds::AmtType, dstrAmtType, idDataGroup, false);

               //If Amount Type = Unit, use fund units precision.
               if(dstrAmtType == I_("U")) //use fund's unit precision
               {
                  DString dstrFund, dstrClass;

                  pTrade->getField(ifds::FromFund, dstrFund, idDataGroup, false);
                  pTrade->getField(ifds::FromClass, dstrClass, idDataGroup, false);
                  
                  FundDetail *pFundDetail = NULL;
                  pDSTCWorkSession->getFundDetail (dstrFund, dstrClass, BF::HOST, pFundDetail);

                  DString dstrUnitsPrecision;
				  bool bAcctUnitsPrecision = false;

				  if (pTrade->getAcctUnitsPrecision (dstrUnitsPrecision, idDataGroup) <= WARNING && !dstrUnitsPrecision.empty())
				  {					  
					  bAcctUnitsPrecision = true;
				  }

				  if(pFundDetail && !bAcctUnitsPrecision)
				  {
					  pFundDetail->getField(ifds::UnitsPrecision, dstrUnitsPrecision, getDataGroupId(), false);
				  }

				  strValueOut = dstrUnitsPrecision;
               }
               //Else, use settlement currency's precision.
               else 
               {
                  DString settleCurrency;
                  int iNumDec = 0;
                  pTrade->getField (ifds::SettleCurrency, settleCurrency, idDataGroup, false);
                  settleCurrency.strip ();
                  iNumDec = CurrencyClass::getPrecision(*pDSTCWorkSession, settleCurrency);
                  strValueOut = DString::asString(iNumDec);
               }
            }
            else if ( idField == ifds::FCFundRate ||
                      idField == ifds::FCFundToRate )
            {
               BFFieldId idFundField  = ifds::NullFieldId;
               BFFieldId idClassField = ifds::NullFieldId;

               if (idField == ifds::FCFundRate)
               {
                  idFundField  = ifds::FromFund;
                  idClassField = ifds::FromClass;
               }
               else
               {
                  idFundField  = ifds::FromFund;
                  idClassField = ifds::FromClass;
               }

               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);
               DString fundCode, classCode, tradeDate;
               pTrade->getField(idFundField, fundCode, idDataGroup, false);
               pTrade->getField(idClassField, classCode, idDataGroup, false);
               pTrade->getField(ifds::EffectiveDate, tradeDate, idDataGroup, false);
               
               ManualForeignCapGainAllocAdjustment* pManualForeignCapGainAllocAdjustment = 
                  dynamic_cast<ManualForeignCapGainAllocAdjustment*>(pTrade);
               
               if(pManualForeignCapGainAllocAdjustment)
               {
                  double dUnitPrice = 
                     pManualForeignCapGainAllocAdjustment->getFCUnitPrice( fundCode, 
                                                                           classCode, 
                                                                           tradeDate, 
                                                                           tradeDate, 
                                                                           idDataGroup );

                  char szNumBuffer[200];
                  sprintf( szNumBuffer,"%f",dUnitPrice );
                  strValueOut = szNumBuffer;
               }
               else
               {
                  strValueOut = NULL_STRING;
               }
            }
            else if (idField == isCASHSettleESGElig)
            {
                DString dstrTradesTransType;
                Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

                pTrade->getField(ifds::TradesTransType, dstrTradesTransType, idDataGroup, false);

                if (DSTCommonFunctions::codeInList(dstrTradesTransType, TRADETYPE::POST_ADJUSTMENT_LIST))
                {
                    strValueOut = pTrade->isCASHSettleESGElig(idDataGroup) ? I_("Y") : I_("N");
                }
            }
			else if (idField == IsRDSPTransferAllowed)
            {
               Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

               if (pTrade)
               {
                  strValueOut = pTrade->isRDSPTransferAllowed  (idDataGroup) ? I_("Y") : I_("N");
               }
            }
         }
      }
   }
   else if ( idContainer == ACCOUNT ||
             idContainer == ACCOUNT_TO)
   {
      BFAbstractCBO *rpPtrMFAccount = const_cast<TradesProcess*> (this)->
                                      getCBOItem ( idContainer, 
                                                   idDataGroup);
      if ( idField == ifds::AltAccount ||
           idField == ifds::XrefNum)
      {
         BFAbstractCBO *rpPtrTrade = const_cast<TradesProcess*> (this)->
                                         getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                      idDataGroup);
         if (!const_cast<TradesProcess*> (this)->
               isAccountSetAndValid (idContainer, idDataGroup))
         {
            DString tradeKey = const_cast<TradesProcess*> (this)->
                               getCurrentListItemKey ( this,
                                                       IFASTBP_PROC::TRADES_LIST);
            if (tradeKey != NULL_STRING)
            {
               TKey tKey (tradeKey, idContainer, idField, idDataGroup);
               VALUES_MAP::const_iterator m_iter = _valuesMap.find (tKey);

               if (m_iter != _valuesMap.end())
               {
                  strValueOut = (*m_iter).second;
               }
            }
         }
         else
         {
            rpPtrMFAccount->getField ( idField, 
                                       strValueOut, 
                                       idDataGroup, 
                                       bFormatted);
         }
      } //idField == AltAccount || idField == XrefNum
      else if (idField == ifds::HighestEntityRisk)
      {
         strValueOut = I_("N");
         if (rpPtrMFAccount)
         {
            DString highestEntityRisk;

            rpPtrMFAccount->getField ( idField, 
                                       highestEntityRisk, 
                                       idDataGroup, 
                                       bFormatted);
            DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession()); 
            DString  dstrHighRiskLevels, dstrhighestEntityRiskCode;
            rpPtrMFAccount->getField ( idField, 
                                       dstrhighestEntityRiskCode, 
                                       idDataGroup, 
                                       false);
            if( dstWorkSession && 
                dstWorkSession->getOption( ifds::HighRiskLevels, dstrHighRiskLevels, idDataGroup ) <= WARNING )
            {
               if(DSTCommonFunctions::codeInList(dstrhighestEntityRiskCode, dstrHighRiskLevels ) )
               { 
                 if(bFormatted)  
                    strValueOut = highestEntityRisk;
                 else
                    strValueOut = I_("Y");
               }
            }   
         }
      }
      else if (idField == IsAccountSetAndValid)
      {
         strValueOut = const_cast<TradesProcess*> (this)->
                        isAccountSetAndValid ( idContainer, 
                                               idDataGroup) ? I_("Y") : I_("N");
      }
      else if (idField == IsClearingAccount)
      {
         strValueOut = I_("N");
         if (rpPtrMFAccount)
         {
            MFAccount *pMFAccount = dynamic_cast <MFAccount*> (rpPtrMFAccount);
            strValueOut = pMFAccount->isClearingAcount (idDataGroup) &&
                          pMFAccount->hasSettlementLocation (idDataGroup) ? I_("Y") : I_("N");
         }
      }
      else if (idField == ifds::RemarkAlertExists)
      {
          MFAccount *pMFAccount = dynamic_cast <MFAccount*> (rpPtrMFAccount);

          if (pMFAccount)
          {
              strValueOut = pMFAccount->isRemarkAlertExists(ALERT_MSG_OPENED_FROM::TRADE, getDataGroupId()) ? I_("Y"):I_("N");
          }
      }
      else if (idField == ifds::AlertMessageExists)
      {
          MFAccount *pMFAccount = dynamic_cast <MFAccount*> (rpPtrMFAccount);

          if (pMFAccount)
          {
              strValueOut = pMFAccount->isAlertMessageExists(ALERT_MSG_OPENED_FROM::TRADE, getDataGroupId()) ? I_("Y"):I_("N");
          }
      }
   }
   else if ( idContainer == ADDRESS ||
             idContainer == SHAREHOLDER_ADDRESS)
   {
      if (idField == ifds::Name)
      {
         if (idContainer == SHAREHOLDER_ADDRESS)
		   {
			   BFAbstractCBO *rPtrAddress_ = 
                  const_cast<TradesProcess*> (this)->getCBOItem (idContainer, idDataGroup);

            if (rPtrAddress_)
            {
	            DString name_;

               rPtrAddress_->getField ( ifds::Name1,
                                        name_,
							                   idDataGroup,
                                        bFormatted);
               strValueOut += name_;
               rPtrAddress_->getField ( ifds::Name2,
                                        name_,
							                   idDataGroup,
                                        bFormatted);
               strValueOut += name_.empty() ? name_ : DString (I_("\r\n")) + name_;
            }
		  } //if SHAREHOLDER_ADDRESS
		  if (idContainer == ADDRESS || strValueOut == NULL_STRING)
		  {
				BFAbstractCBO *rpPtrMFAccount = const_cast<TradesProcess*> (this)->
												getCBOItem (ACCOUNT, idDataGroup);
				if (rpPtrMFAccount)
				{
					DString accountNum;

					rpPtrMFAccount->getField (ifds::AccountNum, accountNum, idDataGroup, false);
					if (!accountNum.empty())
					{
					   pDSTCWorkSession->
                        getFirstSequenced01AccountholderEntityName (idDataGroup, accountNum, strValueOut);
					}
				}
         }
      }
      else //for other address fields
      {
         BFAbstractCBO *rPtrAddress = const_cast<TradesProcess*> (this)->
                                         getCBOItem ( idContainer, 
                                                      idDataGroup);
         if (rPtrAddress)
         {
            rPtrAddress->getField ( idField, 
                                    strValueOut, 
                                    idDataGroup, 
                                    bFormatted);
         }
      }
   }
   else if (idContainer == ADDRESS_TO)
   {
      if (idField == ifds::Name)
      {
         BFAbstractCBO *rpPtrMFAccountTo = const_cast<TradesProcess*> (this)->
                                           getCBOItem ( ACCOUNT_TO, 
                                                        idDataGroup);
         if (rpPtrMFAccountTo)
         {
            DString accountTo;

            rpPtrMFAccountTo->getField ( ifds::AccountNum, 
                                         accountTo, 
                                         idDataGroup, 
                                         false);
            if (!accountTo.empty())
            {
               pDSTCWorkSession->
                  getFirstSequenced01AccountholderEntityName ( idDataGroup, 
                                                               accountTo, 
                                                               strValueOut);
            }
         }         
      }
      else //for other address fields
      {
         BFAbstractCBO *rPtrAddress = const_cast<TradesProcess*> (this)->
                                         getCBOItem ( idContainer, 
                                                      idDataGroup);
         if (rPtrAddress)
         {
            rPtrAddress->getField ( idField, 
                                    strValueOut, 
                                    idDataGroup, 
                                    bFormatted);
         }
      }
   }
   else if ( idContainer == BROKER ||
             idContainer == BRANCH ||
             idContainer == AGENT)
   {
      BFAbstractCBO *rpPtrTrade = const_cast<TradesProcess*> (this)->
                                    getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup);
      if (rpPtrTrade)
      {
         BFFieldId codeFieldId = ifds::NullFieldId;

         if (idField == ifds::BrokerName)
         {
            codeFieldId = ifds::Broker;
         }
         else if (idField == ifds::BranchName)
         {
            codeFieldId = ifds::Branch;
         }
         else if (idField == ifds::SlsrepName)
         {
            codeFieldId = ifds::SlsrepCode;
         }

         DString codeFieldValue;
         
         rpPtrTrade->getField ( codeFieldId, 
                                codeFieldValue, 
                                idDataGroup, 
                                bFormatted);
//broker/branch/slsrepcode fields are valid and not empty, get the name
         if ( !codeFieldValue.empty() && 
              rpPtrTrade->getErrorState (codeFieldId, idDataGroup) <= WARNING)
         {
            BFAbstractCBO *rpPtr = const_cast<TradesProcess*> (this)->
                                       getCBOItem ( idContainer, 
                                                    idDataGroup);
            if (rpPtr)
            {
               rpPtr->getField ( idField, 
                                 strValueOut, 
                                 idDataGroup, 
                                 bFormatted);
            }
         }
      }
   }
   else if ( (idContainer == ACCOUNT_HOLDINGS ||idContainer == ACCOUNT_HOLDINGS_TO) &&
             (idField == ifds::SettledUnits || idField == ifds::SettledValue ||
              ifds::Grp1Shares == idField|| ifds::Grp2Shares == idField))
   {
      BFFieldId fundCodeFieldId, 
         classCodeFieldId;

      if (idContainer == ACCOUNT_HOLDINGS)
      {
         fundCodeFieldId = ifds::FromFund;
         classCodeFieldId = ifds::FromClass;
      }
      else if (idContainer == ACCOUNT_HOLDINGS_TO)
      {
         fundCodeFieldId = ifds::ToFund;
         classCodeFieldId = ifds::ToClass;
      }

      BFAbstractCBO *rpPtrTrade = const_cast<TradesProcess*> (this)->
                                      getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                   idDataGroup);
      if (rpPtrTrade)
      {
         if ( rpPtrTrade->getErrorState (fundCodeFieldId, idDataGroup) <= WARNING &&
              rpPtrTrade->getErrorState (classCodeFieldId, idDataGroup) <= WARNING)
         {
            DString fundCode, 
               classCode;

            rpPtrTrade->getField ( fundCodeFieldId,
                                   fundCode,
                                   idDataGroup,
                                   false);
            rpPtrTrade->getField ( classCodeFieldId,
                                   classCode,
                                   idDataGroup,
                                   false);
            if (!fundCode.empty() && !classCode.empty())
            {
               MFAccountHoldingList *pHoldings = 
                     dynamic_cast <MFAccountHoldingList*> 
                        (const_cast<TradesProcess*> (this)->
                                 getCBOList ( idContainer, 
                                              idDataGroup));
               if (pHoldings)
               {
                  BFObjIter iter ( *pHoldings, 
                                    idDataGroup, 
                                    true, 
                                    BFObjIter::ITERTYPE::NON_DELETED);

                  //walk the list, match the fund and class, 
                  //and retrive the settled value/units

                  BFData matchCriteria;

                  matchCriteria.setElementValue (ifds::rxFundCode, fundCode, true);
                  matchCriteria.setElementValue (ifds::rxClassCode, classCode, true);
                  iter.positionOnNextMatch (matchCriteria, idDataGroup);
                  if (!iter.end())
                  {
                     iter.getObject()->getField ( idField, 
                                                  strValueOut, 
                                                  idDataGroup, 
                                                  bFormatted);
                  }
               }
            }
         }
      }
   }
   else if ( idContainer == TRANS_FEE_LIST && 
             idField == IsChargeFee)
   {
      TransFee *rpPtrTransFee = dynamic_cast <TransFee*> 
                        ( const_cast<TradesProcess*> (this)->
                                getCBOItem ( TRANS_FEE_LIST, 
                                             idDataGroup));
      if (rpPtrTransFee)
      {
         strValueOut = rpPtrTransFee->isChargeFee (idDataGroup) ? I_("Y") : I_("N");
      }
   }
   else if (idContainer == BF::NullContainerId && idField == ifds::AlertViewed)
   {
       BFAbstractCBO *rpPtrMFAccount = const_cast<TradesProcess*>(this)->getCBOItem(ACCOUNT, idDataGroup);
       MFAccount *pMFAccount = dynamic_cast<MFAccount*>(rpPtrMFAccount);

       if (pMFAccount)
       {
           strValueOut = pMFAccount->getAlertViewedFlag() ? I_("Y"):I_("N");
       }
   }
   else if (idContainer == BF::NullContainerId && idField == ifds::AltFndIdntfr)
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
      DString dstrAltFndIdntfr;
      pDSTCWorkSession->getOption(ifds::AltFndIdntfr, dstrAltFndIdntfr, BF::HOST, false);
      
      strValueOut = dstrAltFndIdntfr == I_("") || dstrAltFndIdntfr == I_("0") ? I_("0") : dstrAltFndIdntfr;
   }
}

//******************************************************************************
SEVERITY TradesProcess::doSetField ( const GenericInterface *rpGICaller, 
                                     const BFContainerId &idContainer, 
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup, 
                                     const DString &strValue, 
                                     bool bFormatted) 
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doSetField"));

   if (idContainer == IFASTBP_PROC::TRADES_LIST)
   {
      if ( idField == ifds::AccountNum ||
           idField == ifds::AccountTo ||
           idField == ifds::AddrCode ||
           idField == ifds::Broker ||
           idField == ifds::Branch ||
           idField == ifds::SlsrepCode ||
           idField == ifds::EffectiveDate ||
           idField == ifds::FromFund ||
           idField == ifds::FromClass ||
           idField == ifds::ToFund ||
           idField == ifds::ToClass ||
           idField == ifds::RedCode ||
           idField == ifds::DepositType ||
           idField == ifds::Amount ||
           idField == ifds::AmtType ||
           idField == ifds::AcqFeeOption ||
           idField == ifds::Fee ||
           idField == ifds::FlatPercent ||
           idField == ifds::TrxnFee  ||
		   idField == ifds::TradeInDate)
      {
         BFAbstractCBO *rpPtr = getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                             idDataGroup);
         if (rpPtr)
         {
            if (idField == ifds::AccountNum)
            {
               DString tradeKey = getCurrentListItemKey ( this,
                                                          IFASTBP_PROC::TRADES_LIST),
                  oldAccountNum;
               
               rpPtr->getField (ifds::AccountNum, oldAccountNum, idDataGroup, false);
               oldAccountNum.stripLeading ('0').strip();

               if (oldAccountNum != strValue)
               {
                  CONDITIONVECTOR *pSearchConditions = NULL;

                  if (tradeKey != NULL_STRING)
                  {
                     removeConditions (TKey (tradeKey, idContainer, idField, idDataGroup));
                  }
               }
               setContainer (ACCOUNT, NULL);
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               rpPtr->setField ( idField, 
                                 strValue, 
                                 idDataGroup, 
                                 bFormatted, 
                                 false); // don't notify
               setAccountSearchFieldFromAccount (ACCOUNT, ifds::AltAccount);
               setAccountSearchFieldFromAccount (ACCOUNT, ifds::XrefNum);
               if (isAccountSetAndValid (ACCOUNT, idDataGroup))
               {
                  addTrade (rpGICaller);
               }
            }
            //set the containers to null, in first place and then perform the 
            //set field
            if (idField == ifds::AccountTo)
            {
               setContainer (ACCOUNT_TO, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (RESP_TRANSFER_LIST, NULL);
               rpPtr->setField ( idField, 
                                 strValue, 
                                 idDataGroup, 
                                 bFormatted, 
                                 false); //do not notify
               setAccountSearchFieldFromAccount (ACCOUNT_TO, ifds::AltAccount);
               setAccountSearchFieldFromAccount (ACCOUNT_TO, ifds::XrefNum);
			   setContainer (RDSP_TRANSFER, NULL);
            }
            else if (idField == ifds::AddrCode)
            {
               setContainer (SHAREHOLDER_ADDRESS, NULL);
            }
            else if (idField == ifds::Broker)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (BROKER, NULL);
               setContainer (BRANCH, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
            }
            else if (idField == ifds::Branch)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (BRANCH, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
            }
            else if (idField == ifds::SlsrepCode)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (AGENT, NULL);
               setContainer (BRANCH, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
            }
			else if (idField == ifds::EffectiveDate || idField == ifds::TradeInDate)
            {
               if (isXMLAPIContext())
               {
		            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, getDataGroupId()));
	               DString dstrClient = ConfigManager::getClientName();

                  if (pTrade && dstrClient.upperCase().find(I_("GFS")) != DString::npos)
	               {
		               pTrade->checkBackdatedTrade (false);
	               }
               }
               if (!isAccountSetAndValid (ACCOUNT, idDataGroup))
               {
                  DString tradeKey = getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);
                  
                  CONDITIONVECTOR *pSearchConditions = NULL;

                  if (tradeKey != NULL_STRING)
                  {
                     removeConditions (TKey (tradeKey, idContainer, ifds::AccountNum, idDataGroup));
                  }
               }
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (ACCOUNT_HOLDINGS, NULL);
               setContainer (ACCOUNT_HOLDINGS_TO, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (DILUTION_LIST, NULL);
            }
            else if (idField == ifds::TradesPayType)
            {
               setContainer (TRADE_MULTI_SETTLEMENT_LOC_LIST, NULL);
            }
            else if ( idField == ifds::FromFund ||
                      idField == ifds::FromClass)
            {
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (ACCOUNT_HOLDINGS, NULL);
               if (isOneSideTrade ())
               {
                  setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
                  setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               }
               setContainer (MAT_SWEEP_INSTRUCTIONS_LIST, NULL);
            }
            else if ( idField == ifds::ToFund ||
                      idField == ifds::ToClass)
            {
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (ACCOUNT_HOLDINGS_TO, NULL);
               if (!isOneSideTrade())
               {
                  setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
                  setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               }
            }
            else if (idField == ifds::RedCode)
            {
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (RESP_TRANSFER_LIST, NULL);
               setContainer (RESP_BENEF_ALLOC_LIST, NULL);
               setContainer (IFASTBP_PROC::ESTATE_ALLOCATION, NULL);
			   setContainer (RDSP_TRANSFER, NULL);
            }
            else if (idField == ifds::DepositType)
            {
               setContainer (TRANS_FEE_LIST, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (RESP_BENEF_ALLOC_LIST, NULL);
               setContainer (RESP_TRANSFER_LIST, NULL);
			   setContainer (RDSP_TRANSFER, NULL);
            }
            else if (idField == ifds::AcqFeeOption)
            {
               setContainer (TRANS_FEE_LIST, NULL);
            }
            else if (idField == ifds::Amount)
            {
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (IFASTBP_PROC::ESTATE_ALLOCATION, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
            }
            else if (idField == ifds::AmtType)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (TRANS_FEE_LIST, NULL);
            }
            else if (idField == ifds::Fee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  pTransFee->setField ( ifds::FeeRate, 
                                        strValue, 
                                        idDataGroup, 
                                        bFormatted, 
                                        true);
               }
            }
            else if (idField == ifds::FlatPercent)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  DString feeType;

                  if (strValue == I_("Y")) //flat
                  {
                     feeType = I_("0");
                  }
                  else if (strValue == I_("N")) //percent
                  {
                     feeType = I_("1");
                  }
                  pTransFee->setField ( ifds::FeeType, 
                                        feeType, 
                                        idDataGroup, 
                                        bFormatted,
                                        true);
               }
            }
            else if (idField == ifds::TrxnFee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::TrxnFee) <= WARNING && 
                    pTransFee)
               {
                  pTransFee->setField ( ifds::FeeRate, 
                                        strValue, 
                                        idDataGroup, 
                                        bFormatted, 
                                        true);
               }
            }
            if ( idField != ifds::AccountNum && //alreay took care of the account num
                 idField != ifds::AccountTo &&  //alreay took care of the account to
                 idField != ifds::FlatPercent &&  //alreay took care of the fee and flat percent
                 idField != ifds::Fee &&
                 idField != ifds::TrxnFee)    //alreay took care of the trxn fee percent
            {
               rpPtr->setField ( idField, 
                                 strValue, 
                                 idDataGroup, 
                                 bFormatted, 
                                 true); //notify
            }
         }
      }
      else if (idField == IsCancelHitOnVerifySearch)
      {
         _isCancelHitOnVerifySearch = strValue;
      }
      else if (idField == Reset) //a reset was orderd by the dialog
      {
         _reset = strValue;
         if (strValue == I_("Y"))
         {
            DString tradeKey = const_cast<TradesProcess*> (this)->
                              getCurrentListItemKey ( this,
                                                      IFASTBP_PROC::TRADES_LIST);
            if (!tradeKey.empty())
            {
               removeCurrentTradeDataFromMaps();
               //no need for the current trade anymore,
               //erase the object from the container (WorkSessionTradeList)

               DString tradeNewKey;
               
               assert (_pTradesList);
               if (_pTradesList)
               {
                  BFObjIter iter (*_pTradesList, idDataGroup);

                  iter.positionByKey (tradeKey);
                  if (!iter.end ())
                  {
                     iter.removeObjectFromMap (true);
                  }
  
                  BFAbstractCBO *pNewTrade = _pTradesList->getObject ( tradeNewKey, //should be passed in as null_string
                                                                       idDataGroup);

                  assert (pNewTrade);
               }
               if (!isXMLAPIContext())
               {
                  setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeNewKey); 
                  if (_rpChildGI && isValidModelessInterface (_rpChildGI))
                  {
                     //call the dialog and tell it to refresh the transactions list
                     //and set the current list item on the new trade
	                  _rpChildGI->send (this, I_("RefreshTradesList"));
                  }
                  else //use the caller if the dlg is launched 'modal', _rpChildGI not valid or null
                  {
                     assert (rpGICaller);
                     if (rpGICaller)
                     {
                        const_cast <GenericInterface*>(rpGICaller)->send (this, I_("RefreshTradesList"));
                     }
                  }
               }
            }
            //reset the reset flag
            _reset = NULL_STRING;
         }
      }
      else if (idField == RefreshRESPBenefAllocation)
      {
         setContainer (RESP_BENEF_ALLOC_LIST, NULL);
      }
      else if (idField == RefreshRESPTransfers)
      {
         setContainer (RESP_TRANSFER_LIST, NULL);
      }
	  else if (idField == RefreshRDSPTransfers)
      {
         setContainer (RDSP_TRANSFER, NULL);
      }
      
      if(idField == ifds::AmtType || 
         idField == ifds::FromFund || 
         idField == ifds::FromClass )
      {
         setContainer (IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, NULL);
         setContainer (IFASTBP_PROC::ESTATE_ALLOCATION, NULL);
         //Trade *pTrade = dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, idDataGroup));
         //if (pTrade)
         //{
         //   DString strInvestKey = I_("GIInvestmentDetailsList");
         //   BFObjIter iterGIInvest ( *pTrade, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED);
         //   iterGIInvest.positionByKey(strInvestKey);
         //   if (!iterGIInvest.end())
         //   {
         //      iterGIInvest.removeObjectFromMap (true);
         //   }
         //}
      }

   }
   else if ( ( idContainer == ACCOUNT || 
               idContainer == ACCOUNT_TO) &&
             ( idField == ifds::AltAccount ||
               idField == ifds::XrefNum))
   {
      DString tradeKey = const_cast<TradesProcess*> (this)->
                         getCurrentListItemKey ( this,
                                                 IFASTBP_PROC::TRADES_LIST);
      if (tradeKey != NULL_STRING)
      {
         TKey tKey (tradeKey, idContainer, idField, idDataGroup);
         VALUES_MAP::iterator m_iter = _valuesMap.find (tKey);

         if ( const_cast<TradesProcess*> (this)->isAccountSetAndValid ( idContainer, 
                                                                        idDataGroup) &&
               m_iter != _valuesMap.end() && //value exists
              (*m_iter).second != strValue //we have a change in value
            )
         {
//set the counterpart acccount num field to null string
            setField ( this, 
                       IFASTBP_PROC::TRADES_LIST,
                       idContainer == ACCOUNT ? ifds::AccountNum : ifds::AccountTo,
                       NULL_STRING,
                       false);
         }
         if (m_iter != _valuesMap.end())
         {
            //save the value
            (*m_iter).second = strValue;
         }
         else
         {
            _valuesMap.insert (std::make_pair (tKey, strValue));
         }
      }
   }
   else if (idContainer == BF::NullContainerId && idField == ifds::AlertViewed)
   {
       BFAbstractCBO *rpPtrMFAccount = const_cast<TradesProcess*>(this)->getCBOItem(ACCOUNT, idDataGroup);
       MFAccount *pMFAccount = dynamic_cast<MFAccount*>(rpPtrMFAccount);

       if (pMFAccount)
       {
           pMFAccount->setAlertViewedFlag(strValue == I_("Y"));
       }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradesProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                      const BFContainerId &idContainer,
                                      const BFFieldId &idField,
                                      const BFDataGroupId &idDataGroup,
                                      CONDITIONVECTOR &conditions) const
{  
   SEVERITY sevRtn = NO_CONDITION;

   if ( idContainer == ACCOUNT ||
        idContainer == ACCOUNT_TO)         
   {
      DString tradeKey = const_cast<TradesProcess*> (this)->
                         getCurrentListItemKey ( this,
                                                 IFASTBP_PROC::TRADES_LIST);
      if (tradeKey != NULL_STRING)
      {
        TKey tKey (tradeKey, idContainer, idField, idDataGroup);

         if (idField == ifds::AltAccount || idField == ifds::XrefNum)
         {
            if ( const_cast<TradesProcess*> (this)->
                    isAccountSetAndValid (idContainer, idDataGroup)) //no point to keep condtions on account's fields
            {
                const_cast<TradesProcess*> (this)->removeConditions (tKey);
            }
         }
         CONDITIONS_MAP::const_iterator m_iter = _conditionsMap.find (tKey);
         if (m_iter != _conditionsMap.end())
         {
            CONDITIONVECTOR *pSearchConditions = (*m_iter).second;

            if (pSearchConditions)
            {
               CONDITIONVECTOR::iterator v_iter = 
                     pSearchConditions->begin();
   
               while (v_iter != pSearchConditions->end())
               {
                  Condition *c = 
                        new Condition (**v_iter);
                  
                  //get the max severity
                  sevRtn = c->getSeverity() > sevRtn ? c->getSeverity() : sevRtn;
                  conditions.push_back (c);
                  ++v_iter;
               }
            }
         }
      }
   }
   else if (idContainer == IFASTBP_PROC::TRADES_LIST) //for the rest of subclass-ed edit fields
   {
      if ( idField == ifds::AccountNum ||
           idField == ifds::AccountTo ||
           idField == ifds::AddrCode ||
           idField == ifds::Broker ||
           idField == ifds::Branch ||
           idField == ifds::SlsrepCode ||
           idField == ifds::EffectiveDate ||
           idField == ifds::FromFund ||
           idField == ifds::FromClass ||
           idField == ifds::ToFund ||
           idField == ifds::ToClass ||
           idField == ifds::RedCode ||
           idField == ifds::DepositType ||
           idField == ifds::Amount ||
           idField == ifds::AmtType ||
           idField == ifds::AcqFeeOption ||
           idField == ifds::Fee ||
           idField == ifds::FlatPercent ||
           idField == ifds::TrxnFee  ||
		   idField == ifds::TradeInDate)
      {
         BFAbstractCBO *rpPtr = const_cast<TradesProcess*> (this)->
                                getCBOItem ( idContainer, 
                                             idDataGroup);
         if (rpPtr)
         {
            if (idField == ifds::Fee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  sevRtn = pTransFee->getErrors ( ifds::FeeRate, 
                                                  idDataGroup, 
                                                  conditions);
               }
            }
            else if (idField == ifds::FlatPercent)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  sevRtn = pTransFee->getErrors ( ifds::FeeType, 
                                                  idDataGroup, 
                                                  conditions);
               }
            }
            if (idField == ifds::TrxnFee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::TrxnFee) <= WARNING && 
                    pTransFee)
               {
                  sevRtn = pTransFee->getErrors ( ifds::FeeRate, 
                                                  idDataGroup, 
                                                  conditions);
               }
            }
            else
            {
               sevRtn = rpPtr->getErrors ( idField, 
                                           idDataGroup, 
                                           conditions);
            }
         }
//see, whether the conditions map has anything for the account num
         if (idField == ifds::AccountNum)
         {
            DString tradeKey = const_cast<TradesProcess*> (this)->
                               getCurrentListItemKey ( this,
                                                       IFASTBP_PROC::TRADES_LIST);
            if (tradeKey != NULL_STRING)
            {
               TKey tKey (tradeKey, idContainer, idField, idDataGroup);
               CONDITIONS_MAP::const_iterator mc_it = 
                     _conditionsMap.find (tKey);

               if (mc_it != _conditionsMap.end())
               {
                  CONDITIONVECTOR *pAccountNumConditions = 
                     (*mc_it).second;

                  if (pAccountNumConditions)
                  {
                     CONDITIONVECTOR::iterator v_it =
                           pAccountNumConditions->begin();

                     while (v_it != pAccountNumConditions->end())
                     {
                        conditions.push_back (*v_it);
                        //get the max severity
                        sevRtn = (*v_it)->getSeverity() > sevRtn ? (*v_it)->getSeverity() : sevRtn;
                        ++v_it;
                     }
                  }
               }
            }
         }
      }
   }
   return sevRtn;   
}

//******************************************************************************
const BFProperties *TradesProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                          const BFContainerId &idContainer, 
                                                          const BFFieldId &idField, 
                                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DOGETFIELDATTRIBUTES);
   const BFProperties *pBFProperties = NULL;

   if ( idContainer == ACCOUNT ||
        idContainer == ACCOUNT_TO)
   {
      if ( idField == ifds::AltAccount ||
           idField == ifds::XrefNum)
      {
         BFAbstractCBO *rpPtrTrade = getCBOItem (IFASTBP_PROC::TRADES_LIST, idDataGroup);
//the properties of AltAccount/XrefNum fields should be similar with the AccountNum counterpart field in Trade
         if (rpPtrTrade)
         {
            pBFProperties = rpPtrTrade->
               getFieldProperties ( idContainer == ACCOUNT ? ifds::AccountNum : ifds::AccountTo,
                                    idDataGroup);
         }
      }
   }
   else if ( idContainer == IFASTBP_PROC::TRADES_LIST &&
             (idField == ifds::Fee || idField == ifds::FlatPercent))
   {
      TransFee *pTransFee = NULL;

      if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
           pTransFee)
      {
         if (idField == ifds::Fee)
         {
            pBFProperties = pTransFee->getFieldProperties ( ifds::FeeRate, 
                                                            idDataGroup);
         }
         else if (idField == ifds::FlatPercent)
         {
            pBFProperties = pTransFee->getFieldProperties ( ifds::FeeType, 
                                                            idDataGroup);
         }
      }
   }
   else if ( idContainer == IFASTBP_PROC::TRADES_LIST &&
             idField == ifds::TrxnFee)
   {
      TransFee *pTransFee = NULL;

      if ( findCorrespondingTransFee (pTransFee, ifds::TrxnFee) <= WARNING && 
           pTransFee)
      {
         pBFProperties = pTransFee->getFieldProperties ( ifds::FeeRate, 
                                                         idDataGroup);
      }
   }
   else //for the rest of the subclass-ed fields
   {
      BFAbstractCBO *rpPtr = getCBOItem ( idContainer, 
                                          idDataGroup);
      if (rpPtr)
      {
         pBFProperties = rpPtr->getFieldProperties ( idField, 
                                                     idDataGroup);
      }
   }
   return pBFProperties;
}

//******************************************************************************
bool TradesProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                         const BFContainerId &idContainer,
                                         const BFFieldId &idField,
                                         const BFDataGroupId &idDataGroup,
                                         BFObserver &rpObserver) 
{   
   bool bRegistered = false;

   if (idContainer == IFASTBP_PROC::TRADES_LIST)
   {
      if ( idField == ifds::AccountNum ||
           idField == ifds::AccountTo ||
           idField == ifds::AddrCode ||
           idField == ifds::Broker ||
           idField == ifds::Branch ||
           idField == ifds::SlsrepCode ||
           idField == ifds::EffectiveDate ||
           idField == ifds::FromFund ||
           idField == ifds::FromClass ||
           idField == ifds::ToFund ||
           idField == ifds::ToClass ||
           idField == ifds::RedCode ||
           idField == ifds::DepositType ||
           idField == ifds::Amount ||
           idField == ifds::AmtType ||
           idField == ifds::AcqFeeOption ||
           idField == ifds::Fee ||
           idField == ifds::FlatPercent ||
           idField == ifds::TrxnFee ||
		   idField == ifds::TradeInDate)
      {
         BFAbstractCBO *rpPtr = getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                             idDataGroup);
         if (rpPtr)
         {
            if (idField == ifds::Fee || idField == ifds::FlatPercent)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::Fee) <= WARNING && 
                    pTransFee)
               {
                  if (idField == ifds::Fee)
                  {
                     bRegistered = pTransFee->registerObserver ( ifds::FeeRate, 
                                                                 idDataGroup, 
                                                                 &rpObserver, 
                                                                 FIELD_NOTIFICATIONS, 
                                                                 E_EVENT_ALL);
                  }
                  else if (idField == ifds::FlatPercent)
                  {
                     bRegistered = pTransFee->registerObserver ( ifds::FeeType, 
                                                                 idDataGroup, 
                                                                 &rpObserver, 
                                                                 FIELD_NOTIFICATIONS, 
                                                                 E_EVENT_ALL);
                  }
               }
            }
            if (idField == ifds::TrxnFee)
            {
               TransFee *pTransFee = NULL;

               if ( findCorrespondingTransFee (pTransFee, ifds::TrxnFee) <= WARNING && 
                    pTransFee)
               {
                  bRegistered = pTransFee->registerObserver ( ifds::FeeRate, 
                                                              idDataGroup, 
                                                              &rpObserver, 
                                                              FIELD_NOTIFICATIONS, 
                                                              E_EVENT_ALL);
               }
            }
            else
            {
               bRegistered = rpPtr->registerObserver ( idField, 
                                                       idDataGroup, 
                                                       &rpObserver, 
                                                       FIELD_NOTIFICATIONS, 
                                                       E_EVENT_ALL);
            }
         }
      }
   }
   return bRegistered;
}

//******************************************************************************
bool TradesProcess::doSend ( GenericInterface *rpGICaller, 
                             const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   DString message (szMessage);
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                          getDataGroupId()));

   if (message == I_("RefreshBatch"))
   {
      if (pTrade)
      {
          //only if we have a valid account
         if (isAccountSetAndValid (ACCOUNT, getDataGroupId()))
         {
            pTrade->refreshBatch (getDataGroupId());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
const DString& TradesProcess::getFirstListItemKey ( const GenericInterface *rpGICaller, 
                                                    const BFContainerId &idList)
{
   TRACE_METHOD (CLASSNAME, GETFIRSTLISTITEMKEY);

   if (idList == IFASTBP_PROC::TRADES_LIST)
   {
      AbstractProcess::getFirstListItemKey (rpGICaller, idList);
      BFObjIter iterTradesList ( *_pTradesList, 
                                 getDataGroupId(), 
                                 false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);

      while (!iterTradesList.end())
      {
         DString strKey = iterTradesList.getStringKey ();
         
         if (strKey.find (I_("DuplicateTradeCheck_")) != DString::npos)
         {
            ++iterTradesList;
         }
         else
         {
            AbstractProcess::setCurrentListItem (rpGICaller, idList, strKey);
            return iterTradesList.getStringKey ();
         }
      }
      return EMPTY_STRING;
   }
   return AbstractProcess::getFirstListItemKey (rpGICaller, idList);
}

//******************************************************************************
const DString& TradesProcess::getNextListItemKey ( const GenericInterface *rpGICaller, 
                                                   const BFContainerId &idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );
   if (idList == IFASTBP_PROC::TRADES_LIST)
   {
      DString strKey = AbstractProcess::getCurrentListItemKey (rpGICaller, idList);
      BFObjIter iterTradesList ( *_pTradesList, 
                                 getDataGroupId(), 
                                 false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
      if (iterTradesList.positionByKey (strKey))
      {
         ++iterTradesList; //move iterator
         while (!iterTradesList.end())
         {
            strKey = iterTradesList.getStringKey ();
            if (strKey.find (I_("DuplicateTradeCheck_")) != DString::npos)
            {
               ++iterTradesList;
            }
            else
            {
               AbstractProcess::setCurrentListItem (rpGICaller, idList, strKey);
               return iterTradesList.getStringKey ();
            }
         }
      }
      return EMPTY_STRING;
   }
   return AbstractProcess::getNextListItemKey (rpGICaller, idList);
}

//******************************************************************************
void TradesProcess::setCurrentListItem ( const GenericInterface *rpGICaller,
                                         const BFContainerId &idList,
                                         const BFData *pKeyInfo)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, SETCURRENTLISTITEM); 

   bool bCallBase = true;

   if (idList == IFASTBP_PROC::TRADES_LIST)
   {
      _listKey = pKeyInfo->getElementValue (ifds::TransNum);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::FromFund);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::FromClass);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::ToFund);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::ToClass);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::TransType);
      _listKey.strip();
      _listKey += I_("  ");
      _listKey += pKeyInfo->getElementValue (ifds::TradeDate);
      _listKey.strip();
      if (_caller == I_("ModifyPendingTrade"))
      {
         if (modifyTrade (rpGICaller, _accountNum) <= WARNING)
         {
            DString searchKey,
               strSelectionKey,
               transNum = pKeyInfo->getElementValue (ifds::TransNum);

            WorksessionTradesList::buildKey (_accountNum, transNum, searchKey);
            assert (_pTradesList);
            BFObjIter iter ( *_pTradesList, 
                             getDataGroupId(), 
                             true, //match substrings
                             BFObjIter::ITERTYPE::NON_DELETED);
            if (iter.positionByKey (searchKey))
            {
               strSelectionKey = iter.getStringKey();
            }
            assert (!strSelectionKey.empty());
            AbstractProcess::setCurrentListItem (rpGICaller, idList, strSelectionKey);
            bCallBase = false;
         }         
      }
   }
   if (bCallBase)
   {
      AbstractProcess::setCurrentListItem (rpGICaller, idList, pKeyInfo);
   }
}

//******************************************************************************
bool TradesProcess::doModelessChildComplete (const Command &cmd)
{
// End when GUI ends
   return cmd.getKey() == CMD_GUI_TRADES || cmd.getKey() == CMD_GUI_MANUAL_DIVIDEND;
}

//******************************************************************************
bool TradesProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doModelessSetFocus"));

   bool bRtn = false;
   try
   {
      assert (_rpChildGI && isValidModelessInterface (_rpChildGI));

      if (processParameters () <= WARNING)
      {
//also reset all containers,
         setContainer (IFASTBP_PROC::TRADES_LIST, NULL);
         setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
         setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
         setContainer (ACCOUNT, NULL);
         setContainer (ACCOUNT_TO, NULL);
         setContainer (SHAREHOLDER, NULL);
         setContainer (SHAREHOLDER_TO, NULL);
         setContainer (ADDRESS, NULL);
         setContainer (ADDRESS_TO, NULL);
         setContainer (ACCOUNT_CATEGORY_LIST, NULL);
         setContainer (ACCOUNT_CATEGORY_LIST_TO, NULL);
         setContainer (BROKER, NULL);
         setContainer (BRANCH, NULL);
         setContainer (AGENT, NULL);
         setContainer (ACCOUNT_HOLDINGS, NULL);
         setContainer (ACCOUNT_HOLDINGS_TO, NULL);
         setContainer (SHAREHOLDER_ADDRESS, NULL);
         setContainer (TRANS_FEE_LIST, NULL);
         setContainer (PENDING_TRADES_LIST, NULL);
         setContainer (PENDING_TRADE, NULL);
         setContainer (AGGREGATED_ORDER, NULL);
         if (isValidModelessInterface (_rpChildGI))
         {  // Only if child still exists
            if (_caller == I_("ModifyPendingTrade"))
            {
               //use the the account that comes in
               modifyTrade (this, _accountNum); 
            }
            else
            {
               bRtn = _rpChildGI->refresh (this, I_("Refresh"));
            }
            bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, DOMODELESSSETFOCUS,
                       CND::BP_ERR_UNKNOWN_EXCEPTION
                     );
   }
   return bRtn;
}

//**********************************************************************
void *TradesProcess::getPtrForContainer ( const BFContainerId &idContainer, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer"));
   
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   void *ptr = NULL;

   try
   {
      if (idContainer == IFASTBP_PROC::TRADES_LIST)
      {
         if (pDSTCWorkSession->getTradesList ( _pTradesList, 
                                               idDataGroup,
                                               true,
                                               _track,     //for API
                                               _activity) <= WARNING) //for API
         {
            _pTradesList->setManualTrades (_caller == I_("ManualDividend"));
            ptr = _pTradesList;
         }
      }
      else if(IFASTBP_PROC::ESTATE_ALLOCATION == idContainer)
      {
         Trade *pTrade = dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADES_LIST, idDataGroup));
         EstateAllocationList* pEstateAllocationList = NULL;
         pTrade->getEstateAllocationList ( pEstateAllocationList, idDataGroup);
         if(pEstateAllocationList)
            ptr = pEstateAllocationList;
      }      
      else if (idContainer == SHAREHOLDER_ADDRESS)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));
         if (pTrade)
         {
            DString addrCode,
               effectiveDate;

            pTrade->getField ( ifds::AddrCode, 
                               addrCode, 
                               idDataGroup, 
                               false);
            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false);
            if (!addrCode.empty())
            {
               Shareholder *pShareholder = 
                  dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER,
                                                            idDataGroup));
               if (pShareholder)
               {
                  AddressList *pAddressList = NULL;

                  if ( pShareholder->getAddressList ( pAddressList, 
                                                      idDataGroup) <= WARNING &&
                       pAddressList)
                  {
                     MFAccount *pMFAccount = 
                        dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                                idDataGroup));
                     if (pMFAccount)
                     {
                        DString accountNum;

                        pMFAccount->getField ( ifds::AccountNum, 
                                               accountNum, 
                                               idDataGroup, 
                                               false);
                        pAddressList->setField ( ifds::AccountNum, 
                                                 accountNum, 
                                                 idDataGroup, 
                                                 false);

                        Address *pAddress = NULL;

                        pAddressList->getAddress ( pAddress, 
                                                   addrCode, 
                                                   effectiveDate, 
                                                   idDataGroup);
                        if (pAddress)
                        {
                           ptr = pAddress;
                        }
                     }
                  }
               }
            }
         }
      }
      else if (idContainer == BROKER)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));
         if (pTrade)
         {
            Broker *pBroker = NULL;

            if ( pTrade->getBroker ( pBroker, 
                                    idDataGroup) <= WARNING &&
                 pBroker)
            {
               ptr = pBroker;
            }
         }
      }
      else if (idContainer == BRANCH)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));
         if (pTrade)
         {
            Branch *pBranch = NULL;

            if ( pTrade->getBranch ( pBranch, 
                                     idDataGroup) <= WARNING &&
                 pBranch)
            {
               ptr = pBranch;
            }
         }
      }
      else if (idContainer == AGENT)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));
         if (pTrade)
         {
            Agent *pAgent= NULL;

            if ( pTrade->getAgent ( pAgent, 
                                    idDataGroup) <= WARNING &&
                 pAgent)
            {
               ptr = pAgent;
            }
         }
      }
      else if (idContainer == ACCOUNT)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            DString accountNum;

            pTrade->getField ( ifds::AccountNum, 
                               accountNum, 
                               idDataGroup, 
                               false);
            accountNum.stripLeading ('0');
            if (!accountNum.empty())
            {
               MFAccount *pMFAccount = NULL;

               if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                                     accountNum, 
                                                     pMFAccount) <= WARNING &&
                    pMFAccount)
               {
                  ptr = pMFAccount;
                  setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, accountNum );
               }
            }
         }
      }
      else if (idContainer == ACCOUNT_HOLDINGS)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup));
         if (pTrade)
         {
            MFAccountHoldingList *pMFAccountHoldings = NULL;
            DString fundCode, 
               classCode;


            pTrade->getField (ifds::FromFund, fundCode, idDataGroup, false);
            pTrade->getField (ifds::FromClass, classCode, idDataGroup, false);
            if ( pTrade->getAccountHoldings ( pMFAccountHoldings,
                                              idDataGroup,
                                              fundCode,
                                              classCode) <= WARNING &&
                 pMFAccountHoldings)
            {
               ptr = pMFAccountHoldings;
            }
         }
      }
      else if (idContainer == ACCOUNT_CATEGORY_LIST)
      {
         MFAccount *pMFAccount = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                    idDataGroup));
         if (pMFAccount)
         {
            AcctCategoryList *pAcctCategoryList = NULL;

            if ( pMFAccount->getAcctCategoryList ( pAcctCategoryList, 
                                                  idDataGroup) <= WARNING &&
                 pAcctCategoryList)
            {
               ptr = pAcctCategoryList;
            }
         }
      }
      else if (idContainer == SHAREHOLDER)
      {
         MFAccount *pMFAccount = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                    idDataGroup));
         if (pMFAccount)
         {
            DString shrNum;

            pMFAccount->getField ( ifds::ShrNum, 
                                   shrNum, 
                                   idDataGroup, 
                                   false);
            shrNum.stripLeading ('0');
            if (!shrNum.empty())
            {
               Shareholder *pShareholder = NULL;

               if ( pDSTCWorkSession->getShareholder ( idDataGroup, 
                                                       shrNum, 
                                                       pShareholder) <= WARNING &&
                    pShareholder)
               {
                  ptr = pShareholder;
               }
            }
         }
      }
      else if (idContainer == ADDRESS)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup));
         if (pTrade)
         {
            DString effectiveDate;

            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false);

            Shareholder *pShareholder = 
               dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER,
                                                         idDataGroup));
            if (pShareholder)
            {
               AddressList *pAddressList = NULL;

               if ( pShareholder->getAddressList ( pAddressList, 
                                                  idDataGroup) <= WARNING &&
                    pAddressList)
               {
                  MFAccount *pMFAccount = 
                     dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                             idDataGroup));
                  if (pMFAccount)
                  {
                     DString accountNum;

                     pMFAccount->getField ( ifds::AccountNum, 
                                            accountNum, 
                                            idDataGroup, 
                                            false);
                     pAddressList->setField ( ifds::AccountNum, 
                                              accountNum, 
                                              idDataGroup, 
                                              false);

                     Address *pAddress = NULL;

                     pAddressList->getAddress ( pAddress, 
                                                I_("01"), 
                                                effectiveDate, 
                                                idDataGroup);
                     if (pAddress)
                     {
                        ptr = pAddress;
                     }
                  }
               }
            }
         }
      }
      else if (idContainer == ACCOUNT_TO)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup));
         if (pTrade)
         {
            DString accountTo;

            pTrade->getField ( ifds::AccountTo, 
                               accountTo, 
                               idDataGroup, 
                               false);
            accountTo.stripLeading ('0');
            if (!accountTo.empty())
            {
               MFAccount *pMFAccountTo = NULL;

               if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                                    accountTo, 
                                                    pMFAccountTo) <= WARNING &&
                    pMFAccountTo)
               {
                  ptr = pMFAccountTo;
               }
            }
         }
      }
      else if (idContainer == ACCOUNT_HOLDINGS_TO)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup));
         if (pTrade)
         {
            MFAccountHoldingList *pMFAccountToHoldings = NULL;
            DString toFund, 
               toClass;


            pTrade->getField (ifds::ToFund, toFund, idDataGroup, false);
            pTrade->getField (ifds::ToClass, toClass, idDataGroup, false);
            if ( pTrade->getAccountToHoldings ( pMFAccountToHoldings,
                                                idDataGroup,
                                                toFund,
                                                toClass) <= WARNING &&
                 pMFAccountToHoldings)
            {
               ptr = pMFAccountToHoldings;
            }
         }
      }
      else if (idContainer == ACCOUNT_CATEGORY_LIST_TO)
      {
         MFAccount *pMFAccountTo = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                    idDataGroup));
         if (pMFAccountTo)
         {
            AcctCategoryList *pAcctCategoryListTo = NULL;

            if ( pMFAccountTo->getAcctCategoryList ( pAcctCategoryListTo, 
                                                     idDataGroup) <= WARNING &&
                 pAcctCategoryListTo)
            {
               ptr = pAcctCategoryListTo;
            }
         }
      }
      else if (idContainer == SHAREHOLDER_TO)
      {
         MFAccount *pMFAccountTo = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                    idDataGroup));
         if (pMFAccountTo)
         {
            DString shrNumTo;

            pMFAccountTo->getField ( ifds::ShrNum, 
                                     shrNumTo, 
                                     idDataGroup, 
                                     false);
            shrNumTo.stripLeading ('0');
            if (!shrNumTo.empty())
            {
               Shareholder *pShareholderTo = NULL;

               if ( pDSTCWorkSession->getShareholder ( idDataGroup, 
                                                       shrNumTo, 
                                                       pShareholderTo) <= WARNING &&
                    pShareholderTo)
               {
                  ptr = pShareholderTo;
               }
            }
         }
      }
      else if (idContainer == ADDRESS_TO)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup));
         if (pTrade)
         {
            DString effectiveDate;

            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false);

            Shareholder *pShareholderTo = 
               dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER_TO,
                                                         idDataGroup));
            if (pShareholderTo)
            {
               AddressList *pAddressListTo = NULL;

               if ( pShareholderTo->getAddressList ( pAddressListTo, 
                                                     idDataGroup) <= WARNING &&
                    pAddressListTo)
               {
                  MFAccount *pMFAccountTo = 
                     dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                             idDataGroup));
                  if (pMFAccountTo)
                  {
                     DString accountTo;

                     pMFAccountTo->getField ( ifds::AccountTo, 
                                              accountTo, 
                                              idDataGroup, 
                                              false);
                     pAddressListTo->setField ( ifds::AccountNum, 
                                                accountTo, 
                                                idDataGroup, 
                                                false);

                     Address *pAddressTo = NULL;

                     pAddressListTo->getAddress ( pAddressTo, 
                                                  I_("01"), 
                                                  effectiveDate, 
                                                  idDataGroup);
                     if (pAddressTo)
                     {
                        ptr = pAddressTo;
                     }
                  }
               }
            }
         }
      }
      else if (idContainer == IFASTBP_PROC::FUND_ALLOCATION)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            TradeFundAllocList *pTradeFundAllocList = NULL;

            if ( pTrade->getFundAllocationList ( pTradeFundAllocList, 
                                                 idDataGroup) <= WARNING &&
                 pTradeFundAllocList)
            {
               ptr = pTradeFundAllocList;
            }
         }
      }
      else if (idContainer == IFASTBP_PROC::ACCT_ALLOCATION)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            TradeAcctAllocList *pAccountAllocationList = NULL;

            if ( pTrade->getAccountAllocationList ( pAccountAllocationList, 
                                                    idDataGroup) <= WARNING &&
                 pAccountAllocationList)            
            {
               ptr = pAccountAllocationList;
            }
         }
      }
      else if (idContainer == IFASTBP_PROC::SPLIT_COMMISSION_LIST)
      {
         TradeFundAlloc *pTradeFundAlloc = 
            dynamic_cast <TradeFundAlloc*> ( getCBOItem ( IFASTBP_PROC::FUND_ALLOCATION, 
                                                          idDataGroup));

         if (pTradeFundAlloc)
         {
            SplitCommissionList *pSplitCommissionList = NULL;

            if (pTradeFundAlloc->getSplitCommissionList ( pSplitCommissionList, 
                                                          idDataGroup) <= WARNING)
                 
            {
               if (!pSplitCommissionList)
               {
                  if (!_pSplitCommissionList)
                  {
                     //init a new dummy/empty list, since release 63 - incident 317213/332227
                     _pSplitCommissionList = new SplitCommissionList (*pDSTCWorkSession);
                  }
                  pSplitCommissionList = _pSplitCommissionList;
               }
               ptr = pSplitCommissionList;
            }
         }
      }
      else if (idContainer == TRANS_FEE_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            TransFeeList *pTransFeeList = NULL;

            if ( pTrade->getTransFeeList ( pTransFeeList, 
                                           idDataGroup) <= WARNING &&
                 pTransFeeList)
            {
               ptr = pTransFeeList;
            }
         }
      }
      else if (idContainer == PENDING_TRADES_LIST)
      {
//get the associated pending trades list
         bool bPtr = false;

         if (_caller == I_("ModifyPendingTrade"))
         {
            PendingTradeList *pPendingTradeList = NULL;
            //always on the account from
            MFAccount *pMFAccount = 
               dynamic_cast <MFAccount*> (getCBOItem (ACCOUNT, idDataGroup));

            if ( pMFAccount &&
                 pMFAccount->getPendingTradesList (pPendingTradeList, idDataGroup) <= WARNING &&
                 pPendingTradeList)
            {
               ptr = pPendingTradeList;
            }
         }
         else if (_caller == I_("ModifyPendingTradesWithLoss"))
         {
            if (_pPendingTrades)
            {
               delete _pPendingTrades;
               _pPendingTrades = NULL;
            }

            AggregatedOrder *pAggregatedOrder = 
               dynamic_cast <AggregatedOrder*> (getCBOItem (AGGREGATED_ORDER, idDataGroup));

            _pPendingTrades = new PendingTradeList (*pDSTCWorkSession);
            if ( pAggregatedOrder &&
                 pAggregatedOrder->getAggregatedOrderPendingTrades ( _pPendingTrades, 
                                                                     _aggregatedOrderTradeDate,
                                                                     idDataGroup) <= WARNING &&
                 _pPendingTrades)
            {
               ptr = _pPendingTrades;
            }
         }
         else if (_caller == I_("Rebook") || _caller == I_("Refund"))
         {
            if (_pPendingTrades)
            {
               delete _pPendingTrades;
               _pPendingTrades = NULL;
            }
            _pPendingTrades = new PendingTradeList (*pDSTCWorkSession);
            if (_pPendingTrades->initSearch( I_("Transnum"),
                                             _accountNum,
                                             _transNum,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             NULL_STRING,
                                             I_("Y")) <= WARNING)
            {
               ptr = _pPendingTrades;
               BFObjIter iter ( *_pPendingTrades, 
                                 idDataGroup, 
                                 false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);

               int noOfItemsinList = iter.getNumberOfItemsInList();

//               assert (noOfItemsinList != 0); //we have to have data all the time

               if (noOfItemsinList == 1)
               {
                  _listKey = iter.getStringKey();
               }
               else if (noOfItemsinList >= 1) 
               {
                  //rollovers - 2 records are returned; a rollover is composed of a PW and ED; PW is the main transaction
                  // mgmt_fee - can be multiple records, need to select the exact trade thru fund/class
                  while (!iter.end ())
                  {
                     DString transType;

                     iter.getObject () ->getField (ifds::TransType, transType, idDataGroup);

                     if (transType == TRADETYPE::REDEMPTION)
                     {
                        _listKey = iter.getStringKey();
                        _bIsARollover = true;
                        break;
                     }
                     else if (transType == TRADETYPE::MGMT_FEE)
                     {
                        DString fundCode, classCode;

                        iter.getObject () ->getField (ifds::rxFundCode, fundCode, idDataGroup);
                        iter.getObject () ->getField (ifds::rxClassCode, classCode, idDataGroup);

                        if (fundCode == _fromfund && classCode == _fromclass)
                        {
                           _listKey = iter.getStringKey();
                           break;
                        }
                     }
                     ++iter;
                  }
               }
            }
         }
      }
      else if (idContainer == PENDING_TRADE)
      {
         PendingTradeList *pPendingTradeList = 
               dynamic_cast <PendingTradeList*> (getCBOList (PENDING_TRADES_LIST, idDataGroup));

         if (pPendingTradeList)
         {
            BFObjIter iter ( *pPendingTradeList, 
                              idDataGroup, 
                              false, 
                              BFObjIter::ITERTYPE::NON_DELETED);

            if (!_listKey.empty() && iter.positionByKey (_listKey))
            {
               if (isXMLAPIContext() || _caller == I_("Rebook") || _caller == I_("Refund"))
               {
                  pPendingTradeList->getItem ( _listKey, 
                                               idDataGroup, 
                                               I_("N"), //do not ignore active batch
                                               _caller == I_("Rebook") || _caller == I_("Refund")  ? I_("Y") : I_("N"));
               }
               ptr = dynamic_cast <PendingTradeDetails*> (iter.getObject());
            }
         }
      }
      else if (idContainer == AGGREGATED_ORDER)
      {
         //in this case the _listKey is the one in aggregated orders list
         AggregatedOrderList *pAggregatedOrderList = NULL;
         if ( pDSTCWorkSession->
                getAggregatedOrderList ( NULL_STRING,        //from date
                                         NULL_STRING,        //to date
                                         NULL_STRING,        //status
                                         NULL_STRING,        //broker code
                                         NULL_STRING,        //fund code
                                         NULL_STRING,        //agg order number
                                         NULL_STRING,        //routing ref number
                                         NULL_STRING,        //search type
                                         pAggregatedOrderList,
                                         idDataGroup,
                                         _track,
                                         _activity,
                                         false) <= WARNING  && //do not want to create the list...               
             pAggregatedOrderList)
         {
            BFObjIter iter ( *pAggregatedOrderList, 
                              idDataGroup, 
                              false, 
                              BFObjIter::ITERTYPE::NON_DELETED);

            if (!_listKey.empty() && iter.positionByKey (_listKey))
            {
               ptr = dynamic_cast <AggregatedOrder*> (iter.getObject());
            }
         }
      }
      else if (idContainer == DILUTION_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            DilutionAllocList *pDilutionAllocList = NULL;

            if ( pTrade->getDilutionAllocList ( pDilutionAllocList, 
                                                idDataGroup) <= WARNING &&
                 pDilutionAllocList)
            {
               ptr = pDilutionAllocList;
            }
         }
      }
      else if (idContainer == MAT_SWEEP_INSTRUCTIONS_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            MatSweepInstrList *pMaturityInstrList = NULL;
            
			   if ( pTrade->getMaturityInstrList (pMaturityInstrList, idDataGroup) <= WARNING &&
                  pMaturityInstrList)
            {
               ptr = pMaturityInstrList;
            }
         }
      }
      else if (idContainer == TRADE_MULTI_SETTLEMENT_LOC_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            TradeSettlementLocationsList *pTradeSettlementLocationsList = NULL;

            if (pTrade->getSettlementLocsList (pTradeSettlementLocationsList,idDataGroup) <= WARNING &&
                pTradeSettlementLocationsList)
            {
               ptr = pTradeSettlementLocationsList;
            }
         }
      }
      else if (idContainer == RESP_BENEF_ALLOC_LIST)
      {
         Trade *pTrade = dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, idDataGroup));

         if (pTrade)
         {
            RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = NULL;

            if (pTrade->getRESPBenefAllocationList (pRESPBeneficiaryAllocationList,idDataGroup) <= WARNING &&
                pRESPBeneficiaryAllocationList)
            {
               ptr = pRESPBeneficiaryAllocationList;
            }
         }
      }
      else if (idContainer == RESP_TRANSFER_LIST)
      {
         Trade *pTrade = dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, idDataGroup));

         if (pTrade)
         {
            RESPTransferList *pRESPTransferList = NULL;

            if ( pTrade->getRESPTransferList (pRESPTransferList, idDataGroup) <= WARNING &&
                 pRESPTransferList)
            {
               ptr = pRESPTransferList;
            }
         }
      }
      else if (idContainer == TRADE_PAY_INSTRUCT_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup));

         if (pTrade)
         {
            TradePayInstructList *pTradePayInstructList = NULL;

            if ( pTrade->getTradePayInstructList ( pTradePayInstructList, 
                                                   idDataGroup) <= WARNING &&
                 pTradePayInstructList)
            {
               ptr = pTradePayInstructList;
            }
         }
      }
      else if(idContainer == IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST)
      {
         Trade *pTrade = 
               dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADES_LIST, idDataGroup));
         if( pTrade)
         {
            GIInvestmentDetailsList *pGIInvestmentDetailsList = NULL;
            pTrade->getGIInvestmentDetails(pGIInvestmentDetailsList, idDataGroup);
            ptr = pGIInvestmentDetailsList;
         }
      }
	  else if (idContainer == RDSP_TRANSFER)
      {
         Trade *pTrade = dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, idDataGroup));

         if (pTrade)
         {
            RDSPTransfer *pRDSPTransfer = NULL;

            if ( pTrade->getRDSPTransfer (pRDSPTransfer, idDataGroup) <= WARNING &&	pRDSPTransfer)
            {
               ptr = pRDSPTransfer;
            }
         }
      }	   
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, 
                       DOINIT,
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
SEVERITY TradesProcess::performSearch ( GenericInterface *rpGICaller,
                                        const BFContainerId &idSearch,
                                        E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("performSearch"));

//find out, which container/field is triggering the search
   BFFieldId idField = ifds::NullFieldId;
   BFContainerId idContainer = BF::NullContainerId;

   if ( idSearch == SEARCH_ALT_ACCOUNT ||
        idSearch == SEARCH_ALT_ACCOUNT_FROM)
   {
      idField = ifds::AltAccount;
      idContainer = ACCOUNT;
   }
   else if ( idSearch == SEARCH_X_REF_NUM ||
             idSearch == SEARCH_X_REF_NUM_FROM)
   {
      idField = ifds::XrefNum;
      idContainer = ACCOUNT;
   }
   else if (idSearch == SEARCH_ALT_ACCOUNT_TO)
   {
      idField = ifds::AltAccount;
      idContainer = ACCOUNT_TO;
   }
   else if (idSearch == SEARCH_X_REF_NUM_TO)
   {
      idField = ifds::XrefNum;
      idContainer = ACCOUNT_TO;
   }

//erase the old conditions if any, attached to the search field
   DString tradeKey = getCurrentListItemKey ( this,
                                              IFASTBP_PROC::TRADES_LIST);
   CONDITIONVECTOR *pSearchConditions = NULL;

   if (tradeKey != NULL_STRING)
   {
      removeConditions (TKey (tradeKey, idContainer, idField, getDataGroupId()));
   }

   try
   {
      setParameter (I_("ShowSameEntityMultipleTimes"), I_("Y"));
      switch (invokeCommand ( getParent(),
                              CMD_BPROC_SEARCH, 
                              PROC_NO_TYPE,
                              true,
                              NULL))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            DString accountNum;

            getParameter ( I_("AccountNum"), 
                           accountNum);            
            BFFieldId accountFieldId = ifds::NullFieldId;

            if ( idSearch == SEARCH_ALT_ACCOUNT_TO ||
                 idSearch == SEARCH_X_REF_NUM_TO)
            {
               accountFieldId = ifds::AccountTo;
            }
            else if ( idSearch == SEARCH_ALT_ACCOUNT ||
                      idSearch == SEARCH_ALT_ACCOUNT_FROM ||
                      idSearch == SEARCH_X_REF_NUM ||
                      idSearch == SEARCH_X_REF_NUM_FROM)
            {
               accountFieldId = ifds::AccountNum;
            }
            if (!accountNum.empty())
            {
               if (isXMLAPIContext())
               {
                  if (_pTradesList)
                  {
                     _pTradesList->setField ( accountFieldId, 
                                              accountNum, 
                                              getDataGroupId (), 
                                              false, 
                                              false); // don't notify
                  }
               }
               else
               {
                  setField ( rpGICaller, //use caller - instead of 'this' searches for rebooks should work, as well - 438721
                             IFASTBP_PROC::TRADES_LIST,
                             accountFieldId,
                             accountNum,
                             false);
               }
            }
//clear the search criteria
            if ( !isXMLAPIContext() && 
                 !isAccountSetAndValid (idContainer, getDataGroupId ()))
            {
               setField ( this, 
                          idContainer,
                          idField,
                          NULL_STRING,
                          false);
            }
            else
            {
               ;
            }
            break;
         }
         case CMD_CANCEL:
         {
            if (!isAccountSetAndValid (idContainer, getDataGroupId()))
            {
//clear the search criteria
               setField ( this, 
                          idContainer,
                          idField,
                          NULL_STRING,
                          false);
            }
            setField ( this, 
                       IFASTBP_PROC::TRADES_LIST,
                       IsCancelHitOnVerifySearch,
                       I_("Y"),
                       false);
         
            break;
         }
         default:
         {
            if (GETCURRENTHIGHESTSEVERITY () > WARNING)
            {
// save the vector of errors
               pSearchConditions = 
                     new CONDITIONVECTOR;
// add conditions to the conditions vector
               int count = CURRENTCONDITIONCOUNT();

               for (int i = 0; i < count; i++)
               {
                  Condition *c = 
                        new Condition (*GETCURRENTCONDITION (i));

                  pSearchConditions->push_back (c);
               }
               _conditionsMap.insert (std::make_pair ( TKey ( tradeKey, 
                                                              idContainer, 
                                                              idField,
                                                              getDataGroupId()), 
                                                       pSearchConditions));
            }
            break;
         }
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, 
                       I_("PERFORMSEARCH"), 
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY TradesProcess::addTrade (const GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("addTrade"));
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DString tradeCurrentKey =
               getCurrentListItemKey (rpGICaller, IFASTBP_PROC::TRADES_LIST),
         tradeNewKey;
   Trade *pCurrentTrade = 
      dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                          idDataGroup));
   assert (_pTradesList);
   if (pCurrentTrade)
   {
      DString transType,
         accountNum,
         effectiveDate;

      pCurrentTrade->getField ( ifds::TradesTransType, 
                                transType, 
                                idDataGroup, 
                                false);
/*      if (_caller == I_("ManualDividend")) //override for manual dividends
      {
         transType = TRADETYPE::DIVIDEND;
      }*/
      pCurrentTrade->getField ( ifds::AccountNum, 
                                accountNum, 
                                idDataGroup, 
                                false);
      pCurrentTrade->getField ( ifds::EffectiveDate, 
                                effectiveDate, 
                                idDataGroup, 
                                false);
      _pTradesList->setField ( ifds::TradesTransType, 
                               transType, 
                               idDataGroup, 
                               false);
      _pTradesList->setField ( ifds::AccountNum, 
                               accountNum, 
                               idDataGroup, 
                               false);
      if (effectiveDate != _currentBusinessDate) //user has change it? 
      {
         _pTradesList->setField ( ifds::EffectiveDate, 
                                  effectiveDate, 
                                  idDataGroup, 
                                  false);
      }
      BFAbstractCBO *pNewTrade = _pTradesList->
                                          getObject ( tradeNewKey, //should be passed in as null_string
                                                      idDataGroup);
      if (pNewTrade)
      {
//use our funky condition map to save the errors
         //do we have conditions on the current frame ?
         //if yes, push them in the map
         if (GETCURRENTHIGHESTSEVERITY () > WARNING)
         {
            //find out if there is an associated conditions vector 
            //for the account number fields, for the current trade
            TKey tKey ( tradeCurrentKey, 
                        IFASTBP_PROC::TRADES_LIST,
                        ifds::AccountNum,
                        idDataGroup);
         
            CONDITIONS_MAP::iterator mc_iter = 
                  _conditionsMap.find (tKey);
            CONDITIONVECTOR *pAccountConditions = NULL;

            if (mc_iter != _conditionsMap.end())
            {
               pAccountConditions = (*mc_iter).second;
            }
            else  //not found, make a new entry
            {
               pAccountConditions = new CONDITIONVECTOR;
               _conditionsMap.insert (std::make_pair ( tKey,
                                                       pAccountConditions));
            }

            int count = CURRENTCONDITIONCOUNT();

            for (int i = 0; i < count; i++)
            {
               Condition *c = new Condition (*GETCURRENTCONDITION (i));

               pAccountConditions->push_back (c);
            }

            //no need for the new trade anymore,
            //erase the object from the container (WorkSessionTradeList)

            BFObjIter iter (*_pTradesList, idDataGroup);

            iter.positionByKey (tradeNewKey);
            if (!iter.end ())
            {
               iter.removeObjectFromMap (true);
            }
         }
//new trade came in without errors, replace the current trade with the new one
         else 
         {
            removeCurrentTradeDataFromMaps();
            //no need for the current trade anymore,
            //erase the object from the container (WorkSessionTradeList)

            BFObjIter iter (*_pTradesList, idDataGroup);

            iter.positionByKey (tradeCurrentKey);
            if (!iter.end ())
            {
               iter.removeObjectFromMap (true);
            }
            //set the trade object to be updated,
            dynamic_cast <Trade*> (pNewTrade)->makeDirty (idDataGroup);
            if (isXMLAPIContext())
            {
               //for all API trades
               dynamic_cast <Trade*> (pNewTrade)->setField (ifds::ForceVerify, I_("Y"), idDataGroup, false);
            }
//for rebook of trades for different account num/trans type
            if ( _caller == I_("Rebook") && 
                 _sameAccountTransType == I_("N") && 
                 !_transNum.empty())
            {
               dynamic_cast <Trade*> (pNewTrade)->setField (ifds::AdjTransNum, _transNum, idDataGroup, false);
            }
            //reset the trades list container,
            //to have the iterators regenerated
            setContainer (IFASTBP_PROC::TRADES_LIST, NULL);
            if (!isXMLAPIContext())
            {
               if (_rpChildGI && isValidModelessInterface (_rpChildGI))
               {
                  //call the dialog and tell it to refresh the transactions list
                  //and set the current list item on the new trade
                  setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeNewKey);
                  _rpChildGI->send (this, I_("RefreshTradesList"));
               }
               else //use the caller if the dlg is launched 'modal', _rpChildGI not valid or null
               {
                  assert (rpGICaller);
                  if (rpGICaller)
                  {
                     const_cast <GenericInterface*>(rpGICaller)->send (this, I_("RefreshTradesList"));
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY TradesProcess::modifyTrade ( const GenericInterface *rpGICaller, 
                                      const DString &accountNum,
                                      bool bReqRefresh /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("modifyTrade"));
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   DString accountNum_ (accountNum);

   accountNum_.stripLeading ('0').strip();
   if (!accountNum_.empty())
   {
      MFAccount *pMFAccount = NULL;

      if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                            accountNum_, 
                                            pMFAccount) <= WARNING &&
           pMFAccount)
      {
         setContainer (ACCOUNT, pMFAccount);

//check if we have and data in the pending trade list - regardless whether for pending or reebook.
         PendingTradeList *pPendingTradeList = 
               dynamic_cast <PendingTradeList*> (getCBOList (PENDING_TRADES_LIST, idDataGroup));

         bool bIsRebook = _caller == I_("Rebook");
         bool bIsRefund = _caller == I_("Refund");
         if (pPendingTradeList)
         {
            BFObjIter iter ( *pPendingTradeList, 
                              idDataGroup, 
                              false, 
                              BFObjIter::ITERTYPE::NON_DELETED);


            // existing logic, trade has its history from inter-hist
            if (iter.getNumberOfItemsInList() > 0)
            {
               PendingTradeDetails *pPendingTrade = 
                     dynamic_cast <PendingTradeDetails*> ( getCBOItem ( PENDING_TRADE, 
                                                                        idDataGroup));

               if (pPendingTrade)
               {
                  if (!_pTradesList)
                  {
                     _pTradesList = 
                        dynamic_cast <WorksessionTradesList*> (getCBOList ( IFASTBP_PROC::TRADES_LIST, 
                                                                           idDataGroup));
                     assert (_pTradesList);
                  }

                  DString searchKey,
                     strSelectionKey,
                     transNum;

                  pPendingTrade->getField (ifds::TransNum, transNum, idDataGroup);
                  WorksessionTradesList::buildKey (accountNum, transNum, searchKey);
                  BFObjIter iter ( *_pTradesList, 
                                    idDataGroup, 
                                    true, //match substrings
                                    BFObjIter::ITERTYPE::NON_DELETED);
                  if (!iter.positionByKey (searchKey)) //modify trades that were not modified yet
                  {

                     _pTradesList->fromPending2Trade ( pPendingTrade, 
                                                      idDataGroup, 
                                                      bReqRefresh, 
                                                      strSelectionKey,
                                                      _sameAccountTransType == I_("Y"),
                                                      bIsRebook,
                                                      bIsRebook && _rebookExist == I_("Y"),
                                                      bIsRebook && _bIsARollover,
                                                      _batch, bIsRefund);
                  }
                  else
                  {
                     strSelectionKey = iter.getStringKey();
                  }
                  //position ourselves on the trade that requested to be modified
                  if (!strSelectionKey.empty())
                  {
                     if (!isXMLAPIContext() && isValidModelessInterface (_rpChildGI))
                     {
                        setParameter (MFCAN_IP_PARAM::LIST_KEY, strSelectionKey); 
                        _rpChildGI->send (this, I_("RefreshTradesList"));
                     }
                  }
               }
            }
            else if (bIsRebook || bIsRefund)
            {
               // IN#1595165 :: need additional logic, 
               // if there is no information in inter-hist then look for
               // information from trans-detl here
               TransactionList* pTransactionList = new TransactionList (*pDSTCWorkSession);
               
               if (pTransactionList->initSearch (I_("Transnum"),
                                                 _accountNum,
                                                 _transNum,
                                                 NULL_STRING, 
                                                 NULL_STRING, 
                                                 NULL_STRING, 
                                                 NULL_STRING,
                                                 NULL_STRING, 
                                                 NULL_STRING,
                                                 NULL_STRING, 
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING,
                                                 NULL_STRING) <= WARNING)
               {
                  BFObjIter iter ( *pTransactionList, 
                                    idDataGroup, 
                                    false, 
                                    BFObjIter::ITERTYPE::NON_DELETED);

                  if (iter.getNumberOfItemsInList() >= 1)
                  {
                     TransactionDetails *pHistroryTrade (NULL);
                     
                     while (!iter.end())
                     {
                        DString strCancelled,
                              strReversal;

                        // look for original trade which its 'Canceled' is 'Y'
                        iter.getObject()->getField(ifds::Cancelled, strCancelled, idDataGroup,false);
                        iter.getObject()->getField(ifds::Reversal, strReversal, idDataGroup,false);
                        if (strCancelled == I_("Y") && strReversal == I_("N") || bIsRefund) // do we need to check the fund class ?
                        {
                           pHistroryTrade = 
                              dynamic_cast <TransactionDetails*> (iter.getObject());
                           break;
                        }
                        ++iter;
                     }
                     if (pHistroryTrade)
                     {
                        if (!_pTradesList)
                        {
                           _pTradesList = 
                              dynamic_cast <WorksessionTradesList*> (getCBOList ( IFASTBP_PROC::TRADES_LIST, 
                                                                                 idDataGroup));
                           assert (_pTradesList);
                        }
                        DString searchKey,
                              strSelectionKey,
                              transNum,
                              transID;

                        pHistroryTrade->getField (ifds::TransNum, transNum, idDataGroup);
                        pHistroryTrade->getField (ifds::TransId, transID, idDataGroup);
                        pHistroryTrade->getDetails (transID);

                        WorksessionTradesList::buildKey (accountNum, transNum, searchKey);
                        
                        _pTradesList->fromHistory2Trade ( pHistroryTrade, 
                                                          idDataGroup, 
                                                          bReqRefresh, 
                                                          strSelectionKey,
                                                          _sameAccountTransType == I_("Y"),
                                                          bIsRebook,
                                                          _rebookExist == I_("Y"),
                                                          _bIsARollover,
                                                          _batch,
                                                          bIsRefund);
                        if (!strSelectionKey.empty())
                        {
                           if (!isXMLAPIContext() && isValidModelessInterface (_rpChildGI))
                           {
                              setParameter (MFCAN_IP_PARAM::LIST_KEY, strSelectionKey); 
                              _rpChildGI->send (this, I_("RefreshTradesList"));
                           }
                        }
                     }
                  }
               }
               delete pTransactionList;
               pTransactionList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void TradesProcess::doPostOk (GenericInterface *rpGICaller, bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

   if (bSuccessFlag)
   {
      DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if (_caller == I_("ModifyPendingTradesWithLoss")) //find the aggregated order process
      {
         AggregatedOrder *pAggregatedOrder = 
            dynamic_cast <AggregatedOrder*> (getCBOItem (AGGREGATED_ORDER, getDataGroupId ()));
         if( pAggregatedOrder )
         {
            BFObjIter iter (*pAggregatedOrder, getDataGroupId ());
            iter.positionByKey (I_("TradeSearchCriteria"));
            if (!iter.end ())
            {
               iter.removeObjectFromMap (true);
            }
         }

         GenericInterface* pGIAggregatedOrderProcess = 
            getGIContainer()->findGI (pDSTCWorkSession, CMD_BPROC_AGGREGATED_ORDER);

         if (pGIAggregatedOrderProcess)
         {
            pGIAggregatedOrderProcess->refresh (rpGICaller, I_("RefreshPendingTradeList"));
         }
      }
   }
}

//******************************************************************************
bool TradesProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOOK);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   assert (_pTradesList);
   DString dstrBatchNum = NULL_STRING;

   if (_pTradesList)
   {
      BFObjIter bfIter (*_pTradesList, idDataGroup);
//few things should be done in here...
      for (bfIter.begin(); !bfIter.end(); ++bfIter)
      {
         Trade *pTrade = dynamic_cast <Trade*> (bfIter.getObject());

         if (pTrade)
         {
            pTrade->copyFeeValuesForCycleProcessing (idDataGroup);
            //blow the pending trades list for all the accounts, 
            //a new call to 'getPendingTradesList' will refresh the pending trades
            //if (_caller == I_("ModifyPendingTrade")) 
            {
               DString accountNum;

               if (dstrBatchNum == NULL_STRING)
               {
                  pTrade->getField (ifds::BatchName, dstrBatchNum, idDataGroup, false);
                  dstrBatchNum.strip();
               }

               pTrade->getField (ifds::AccountNum, accountNum, idDataGroup, false);
               accountNum.stripLeading ('0').strip();

               if (!accountNum.empty())
               {
                  MFAccount *pMFAccount = NULL;

                  if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                                        accountNum, 
                                                        pMFAccount) <= WARNING &&
                       pMFAccount)
                  {
                     BFObjIter iterAcct (*pMFAccount, idDataGroup);

                     if (iterAcct.positionByKey (I_("PendingTradeList")))
                     {
                        iterAcct.removeObjectFromMap (true);
                     }
                     if (_caller == I_("Rebook"))
                     {
                        //quite a hack for now...Incident#434072, rebook it's done as a flow always in HOST
                        pMFAccount->setField (ifds::PendingTrade, I_("Y"), BF::HOST, false);
                     }
                     //this account has pending trade(s)
                     pMFAccount->setField (ifds::PendingTrade, I_("Y"), idDataGroup, false);
                  }
               }
            }
         }
      }
//Incident#279170, Kludge to fix Aberdeen cycle issue, 
//Cycle SHOULD be fixed not to bomb when commissions percentages are set, 
//even if the rates are zero;
//This fix will haunt me for a long time... (SP-Apr,5th,2005)

//do we have split commissions?
      DString isSplitCommissionAllowed;

      getField (this, IsSplitCommissionAllowed, isSplitCommissionAllowed, false);
      if (isSplitCommissionAllowed == I_("Y"))
      {
         BFObjIter iterTrade (*_pTradesList, idDataGroup);

//get the current trade...
         while (!iterTrade.end())
         {
            Trade *pTrade = dynamic_cast <Trade*> (iterTrade.getObject());
//get account allocation...
            if (pTrade)
            {
               TradeAcctAllocList *pTradeAcctAllocList =  NULL;
               if ( pTrade->getAccountAllocationList ( pTradeAcctAllocList, 
                                                       idDataGroup, 
                                                       false) <= WARNING &&
                    pTradeAcctAllocList)
               {
      //get fund allocation
                  BFObjIter iterActAlloc (*pTradeAcctAllocList, idDataGroup);

                  while (!iterActAlloc.end())
                  {
                     TradeAcctAlloc *pTradeAcctAlloc =  
                           dynamic_cast <TradeAcctAlloc*> (iterActAlloc.getObject());

                     if (pTradeAcctAlloc)
                     {
                        BFObjIter iterTradeFundAllocList (*pTradeAcctAlloc, idDataGroup);

                        if (iterTradeFundAllocList.positionByKey (FUNDALLOCATIONLIST))
                        {
                           TradeFundAllocList *pTradeFundAllocList = 
                              dynamic_cast <TradeFundAllocList*> (iterTradeFundAllocList.getObject());

                           if (pTradeFundAllocList)
                           {
                              BFObjIter iterFundAlloc (*pTradeFundAllocList, idDataGroup);
                           
                              while (!iterFundAlloc.end())
                              {
                                 TradeFundAlloc *pTradeFundAlloc = 
                                       dynamic_cast <TradeFundAlloc *> (iterFundAlloc.getObject());
                                 if (pTradeFundAlloc)
                                 {
                                    BFObjIter iterSplitCommission (*pTradeFundAlloc, idDataGroup);

                                    if (iterSplitCommission.positionByKey (I_("SplitCommissionList")))
                                    {
                                       SplitCommissionList *pSplitCommissionList = 
                                             dynamic_cast <SplitCommissionList*> (iterSplitCommission.getObject());
                                       bool bZeroOutPercentages = !!pSplitCommissionList;

                                       if (pSplitCommissionList)
                                       {
            //walk the split commission list and see whether all comm rates are zero
                                          BFObjIter iterSplit (*pSplitCommissionList , idDataGroup);
                                          while (!iterSplit.end())
                                          {
                                             DString commRate; 
                                             
                                             iterSplit.getObject()->getField (ifds::CommRate, commRate, idDataGroup);
                                             double dec_comm_rate = DSTCommonFunctions::convertToDouble (commRate);
                                             if (dec_comm_rate != 0)
                                             {
                                                bZeroOutPercentages = false; //no need to zero out the percentages
                                                break;
                                             }
                                             ++iterSplit;
                                          }
                                       }

									   /*

									   Problem  seems to occur when the commission rate (override) is modified (via Desktop) from 0 to non-zero value after it had previously been saved.
									   Fix for change CHG0056345

									   */ 


                                       /*if (bZeroOutPercentages) //walk the list again and zero out the percentage field
                                       {
                                          BFObjIter iterSplit (*pSplitCommissionList, idDataGroup);

                                          while (!iterSplit.end())
                                          {
                                             iterSplit.getObject()->setField (ifds::CommPrcnt, I_("0.0"), idDataGroup);
                                             ++iterSplit;
                                          }
                                       }*/
                                       }
                                    }
                                 ++iterFundAlloc;
                              } //!iterFundAlloc.end ()
                           } //pTradeFundAllocList
                        }//iterTradeFundAllocList.positionByKey
                     }//pTradeAcctAlloc
                     ++iterActAlloc;
                  } //!iterActAlloc.end ()
               } //pTradeAcctAllocList
            } //pTrade
            ++iterTrade;
         } //!iterTrade.end()
      } //isSplitCommissionAllowed
   } //pTradesList

   if( _caller == I_("ModifyPendingTradesWithLoss") )
   {
      setParameter( CONFPROC::PARM_CALLED_FROM, I_("ModifyPendingTradesWithLoss") );
   }
   else
   {
      setParameter( CONFPROC::PARM_CALLED_FROM, I_("GeneralTradesProcess") );
   }
   setParameter( CONFPROC::BATCH, dstrBatchNum);

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
bool TradesProcess::doCancel (GenericInterface *rpGICaller)
{
   return true;
}

//******************************************************************************
bool TradesProcess::isAccountSetAndValid ( const BFContainerId &accountContainerId, 
                                           const BFDataGroupId &idDataGroup)
{
   BFAbstractCBO *rpPtrMFAccount = const_cast<TradesProcess*> (this)->
                                   getCBOItem ( accountContainerId, 
                                                idDataGroup);
   BFAbstractCBO *rpPtrTrade = const_cast<TradesProcess*> (this)->
                                   getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup);
   SEVERITY accountNumSeverity = NO_CONDITION;
   assert (_pTradesList);
   DString tradeKey = const_cast<TradesProcess*> (this)->
                        getCurrentListItemKey ( this,
                                                IFASTBP_PROC::TRADES_LIST);
   if (accountContainerId == ACCOUNT)
   {
      if (tradeKey != NULL_STRING)
      {
         TKey tKey (tradeKey, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, idDataGroup);
         CONDITIONS_MAP::iterator m_iter = _conditionsMap.find (tKey);

         if (m_iter != _conditionsMap.end())
         {
            CONDITIONVECTOR *pSearchConditions = (*m_iter).second;

            if (pSearchConditions)
            {
               CONDITIONVECTOR::iterator v_iter = pSearchConditions->begin();

               while (v_iter != pSearchConditions->end())
               {
                  Condition *c = new Condition (**v_iter);
               
   //get the max severity
                  accountNumSeverity = 
                     c->getSeverity() > accountNumSeverity ? c->getSeverity() : accountNumSeverity;
                  ++v_iter;
               }
            }
         }
      }
   }
   
   bool bIsAccountSetAndValid = false;

   if ( rpPtrMFAccount && 
        rpPtrTrade &&
        accountNumSeverity <= WARNING)
   {
      bool bIsTradeAdded = _pTradesList->isTradeAdded (tradeKey, idDataGroup);

      if (accountContainerId == ACCOUNT)
      {
         bIsAccountSetAndValid = bIsTradeAdded || rpPtrTrade->getErrorState (ifds::AccountNum, idDataGroup) <= WARNING;
      }
      else if (accountContainerId == ACCOUNT_TO)
      {
         bIsAccountSetAndValid =  bIsTradeAdded && rpPtrTrade->getErrorState (ifds::AccountTo, idDataGroup) <= WARNING;
      }
   }
   return bIsAccountSetAndValid;
}

//******************************************************************************
void TradesProcess::removeConditions (const TKey &tKey)
{
    CONDITIONS_MAP::iterator m_iter = _conditionsMap.find (tKey);

    if (m_iter != _conditionsMap.end())
    {
        CONDITIONVECTOR *pSearchConditions = (*m_iter).second;
        if (pSearchConditions) //erase old conditions
        {
            CONDITIONVECTOR::iterator v_iter = pSearchConditions->begin();

            while (v_iter != pSearchConditions->end())
            {
                delete *v_iter;
                v_iter = pSearchConditions->erase (v_iter);
            }
            delete pSearchConditions;
            pSearchConditions = NULL;
        }
        _conditionsMap.erase (m_iter);
    }
}

//******************************************************************************
void TradesProcess::setAccountSearchFieldFromAccount ( const BFContainerId &idContainer, 
                                                       const BFFieldId &idField)
{
    BFDataGroupId idDataGroup = getDataGroupId();

    if (isAccountSetAndValid (idContainer, idDataGroup))
    {
        BFAbstractCBO *rpPtrMFAccount = getCBOItem ( idContainer, 
                                                     idDataGroup);
        BFAbstractCBO *rpPtrTrade = getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup);
        
        DString tradeKey =  getCurrentListItemKey ( this,
                                                    IFASTBP_PROC::TRADES_LIST);
        if (tradeKey != NULL_STRING && rpPtrMFAccount)
        {            
            TKey tKey (tradeKey, idContainer, idField, idDataGroup);
            DString fieldValue;
            
            rpPtrMFAccount->getField (idField, fieldValue, idDataGroup, false);
            VALUES_MAP::iterator m_iter = _valuesMap.find (tKey);

            if (m_iter != _valuesMap.end())
            {
                (*m_iter).second = fieldValue;
            }
            else //not found
            {
                _valuesMap.insert (std::make_pair (tKey, fieldValue));
            }
        }
    }
}

//******************************************************************************
void TradesProcess::removeCurrentTradeDataFromMaps()
{
   //remove the current trade info from the funky maps
   DString tradeKey = const_cast<TradesProcess*> (this)->
                      getCurrentListItemKey ( this,
                                              IFASTBP_PROC::TRADES_LIST);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   //the conditions map   
   CONDITIONS_MAP::iterator mc_it =
      _conditionsMap.begin();

   while (mc_it != _conditionsMap.end())
   {
      if (
          (*mc_it).first._tradeKey == tradeKey &&
          (*mc_it).first._idDataGroup == idDataGroup
         )
      {
         CONDITIONVECTOR *pConditions = (*mc_it).second;

         if (pConditions)
         {
            CONDITIONVECTOR::iterator v_it =
                  pConditions->begin();

            while (v_it != pConditions->end())
            {
               delete *v_it;
               v_it = pConditions->erase (v_it);
            }
         }
         mc_it = _conditionsMap.erase (mc_it);
      }
      else
      {
         ++mc_it;
      }
   }
   //the values map
   VALUES_MAP::iterator mv_it = _valuesMap.begin();

   while (mv_it != _valuesMap.end())
   {
      if ( (*mv_it).first._tradeKey == tradeKey &&
           (*mv_it).first._idDataGroup == idDataGroup
         )
      {
         mv_it = _valuesMap.erase (mv_it);
      }
      else
      {
         ++mv_it;
      }
   }
}

//******************************************************************
bool TradesProcess::isOneSideTrade ()
{
   DString transType;

   getField (this, ifds::TradesTransType, transType, false);
   return DSTCommonFunctions::codeInList (transType, TRADETYPE::ONE_SIDE_TRADE);
}

//******************************************************************************
SEVERITY TradesProcess::processParameters ()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("processParameters"));

   getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
   _accountNum.strip();
   getParameter (MFCAN_IP_PARAM::LIST_KEY, _listKey);
   _listKey.strip();
   getParameter (MFCAN_IP_PARAM::CALLER, _caller);
   _caller.strip();
   getParameter (MFCAN_IP_PARAM::TRADE_DATE, _aggregatedOrderTradeDate);
   _aggregatedOrderTradeDate.strip();
//API specific parameters
   getParameter (ETRACK::TRACK, _track);
   _track.strip();
   if (_track.empty())
   {
      _track = I_("N");
   }
   getParameter (ETRACK::ACTIVITY, _activity);
//rebook parameters
   getParameter (TRANS_REBOOK_PARAM::TRANS_NUM, _transNum);
   getParameter (TRANS_REBOOK_PARAM::REBOOK_EXIST, _rebookExist);
   getParameter (TRANS_REBOOK_PARAM::FUND_CODE, _fromfund);
   getParameter (TRANS_REBOOK_PARAM::CLASS_CODE, _fromclass);
   getParameter (REBOOK::SAMEACCOUNTTRANSTYPE, _sameAccountTransType);
   getParameter (BATCH, _batch);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradesProcess::findCorrespondingTransFee (TransFee *&pTransFee,
                                                   const BFFieldId &idField) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("findCorrespondingTransFee"));

   DString transType,
      feeCode;
	DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

   const_cast <TradesProcess*> (this)->getField (this, ifds::TradesTransType, transType, false);
   if (idField == ifds::Fee)
   {
      if (transType == TRADETYPE::PURCHASE)
      {
         feeCode = FEES::ACQUISITION;
      }
      else if (transType == TRADETYPE::REDEMPTION)
      {
         feeCode = FEES::REDEMPTION;
      }
      else if ( !SplitCommission::isTypeZERO (*pDSTCWorkSession) &&
               (transType == TRADETYPE::TRANSFER || transType == TRADETYPE::EXCHANGE))
      {
         feeCode = FEES::XFER_OUT;
      }
      else if ( SplitCommission::isTypeZERO (*pDSTCWorkSession) &&
               (transType == TRADETYPE::TRANSFER || transType == TRADETYPE::EXCHANGE))
      {
         feeCode = FEES::EXCHANGE;
      }
   }
   else if (idField == ifds::TrxnFee)
   {
      if (transType == TRADETYPE::PURCHASE)
      {
         feeCode = FEES::PURCHASE_TRXN;
      }
      else if (transType == TRADETYPE::REDEMPTION)
      {
         feeCode = FEES::REDEMPTION_TRXN;
      }
   }
   
   TransFeeList *pTransFeeList = 
         dynamic_cast <TransFeeList*> (const_cast <TradesProcess*> (this)->
                                          getCBOList (TRANS_FEE_LIST, getDataGroupId()));

   if (pTransFeeList)
   {
      pTransFeeList->getTransFee (feeCode, pTransFee, getDataGroupId());
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradesProcess.cpp-arc  $
 * 
 *    Rev 1.343   Jul 27 2012 08:17:08   wp040132
 * P0199891 _FN01_Arrow_FAST_File
 * 
 *    Rev 1.342   Jul 26 2012 10:34:40   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.341   25 Jul 2012 17:47:00   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.340   Jul 02 2012 19:07:34   wp040132
 * P0199883_FN01_Cancellation Rights - Right To Cancel
 * 
 *    Rev 1.339   Apr 17 2012 11:01:06   if991250
 * Showing Principat instead of InvHisPrincipal in Trade, GIInvest
 * 
 *    Rev 1.338   Apr 11 2012 11:07:16   dchatcha
 * IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
 * 
 *    Rev 1.337   Apr 10 2012 16:43:28   if991250
 * Money Out
 * 
 *    Rev 1.336   Apr 03 2012 16:58:56   popescu
 * Incident 2889047 - Missing GIA Trade Entry Validation
 * 
 *    Rev 1.335   Mar 29 2012 23:17:38   dchatcha
 * IN#2901157 - Issues on SEG Trade Processing
 * 
 *    Rev 1.334   Mar 20 2012 16:40:56   if991250
 * IN 2885623 - GI Money Oout
 * 
 *    Rev 1.333   Mar 08 2012 09:57:04   if991250
 * GI Money Out
 * 
 *    Rev 1.332   Mar 05 2012 11:37:34   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.331   Jan 23 2012 12:06:40   jankovii
 * Sync up: IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
 * 
 *    Rev 1.330   Jan 20 2012 14:43:34   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.329   Jan 06 2012 13:38:22   if991250
 * IA money out
 * 
 *    Rev 1.328   Jan 05 2012 12:57:30   if991250
 * return null (for now) for teh MAT_SWEEP_INSTRUCTIONS_LIST
 * 
 *    Rev 1.327   Nov 27 2011 19:39:34   popescu
 * INA Commission Work
 * 
 *    Rev 1.326   Nov 09 2011 04:01:22   panatcha
 * P0186477_FN03_10D - GIA Money In
 * 
 *    Rev 1.325   Nov 01 2011 15:34:54   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.324   Oct 31 2011 17:11:00   popescu
 * P0186477/FN 03 - GIA Trading - Money In - added two new tabs to trade dlg
 * 
 *    Rev 1.323   Oct 18 2011 00:44:26   popescu
 * GIA Trading prep-work
 * 
 *    Rev 1.322   Oct 14 2011 12:22:32   panatcha
 * IN2689391 - [update] change field to EAPCESGPaid
 * 
 *    Rev 1.320   Aug 03 2011 11:33:42   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.319   Jun 28 2011 10:02:16   panatcha
 * P0184541_FN01_InvescoQESItrans
 * 
 *    Rev 1.318   Mar 22 2011 15:09:24   jankovii
 * IN 2470490 - Desktop - Redemption Error Message
 * 
 *    Rev 1.317   Mar 10 2011 14:33:54   jankovii
 * IN 2458927 - P0181943 - SWIFT XML - Split Commission Exchanges
 * 
 *    Rev 1.316   Mar 03 2011 16:08:04   jankovii
 * PET181943 FN01 - XMLPhase 2
 * 
 *    Rev 1.315   Nov 22 2010 13:19:36   jankovii
 * PET 175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.314   Jun 11 2010 06:09:56   kitticha
 * PETP0165541 FN02 IN#2123752 - PSE Fix.
 * 
 *    Rev 1.313   Jun 04 2010 03:54:40   kitticha
 * IN#2123752 - Additional logic and validation for PSE.
 * 
 *    Rev 1.312   May 27 2010 05:19:52   kitticha
 * PETP0165541 FN02 QESI Phase2.
 * 
 *    Rev 1.311   May 12 2010 07:55:12   popescu
 * RESP - Added TaxYear and related validation
 * 
 *    Rev 1.310   May 06 2010 23:34:52   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.309   Apr 30 2010 16:39:08   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.308   Apr 29 2010 23:20:54   popescu
 * RES-QESI Trading - PSE/EAP work
 * 
 *    Rev 1.307   Apr 27 2010 16:31:48   popescu
 * RESP-QESI Added two new fields in the attribute grid
 * 
 *    Rev 1.306   Apr 21 2010 01:20:24   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.305   Apr 20 2010 10:07:50   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading PSE/EAP
 * 
 *    Rev 1.304   Apr 20 2010 09:43:06   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.303   Apr 14 2010 23:55:52   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.302   Apr 14 2010 09:52:42   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.301   Mar 25 2010 13:48:12   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.300   Mar 23 2010 10:06:20   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.299   Mar 22 2010 15:12:52   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.298   Mar 08 2010 13:24:28   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.297   Dec 24 2009 04:16:16   dchatcha
 * IN#1862560 - R95 - Pending Trade does not show when hitting refresh at processing time. rework for problem found only all fund transfer.
 * 
 *    Rev 1.296   Dec 02 2009 14:56:24   popescu
 * Prepare the terrain for incident 1780456, which will go in release 98 
 * 
 *    Rev 1.295   Nov 16 2009 13:53:30   popescu
 * Incident 1891982 - rebook
 * 
 *    Rev 1.294   Nov 09 2009 15:28:22   popescu
 * Incident 1891982 - fix popping-up the trade screen when modifying a trade
 * 
 *    Rev 1.293   Sep 30 2009 06:55:12   dchatcha
 * IN# 1595165 - Rebooking functionality where contr rcpt was issued not working properly.
 * 
 *    Rev 1.292   Sep 21 2009 16:00:20   popescu
 * Added support for launching the Trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file
 * 
 *    Rev 1.291   Aug 17 2009 08:26:54   dchatcha
 * IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
 * 
 *    Rev 1.290   Aug 11 2009 13:45:42   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.289   27 Jul 2009 15:12:54   popescu
 * Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
 * 
 *    Rev 1.288   May 27 2009 15:14:20   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.287   Mar 18 2009 03:49:26   wutipong
 * IN#1358908 - AIG unit rounding issue -- more fix
 * 
 *    Rev 1.286   Mar 11 2009 17:46:04   wutipong
 * IN1358908 AIG Unit Rounding Issue -- restrict user to enter decimal longer than fund unit precision to amount field, if amount type is Units.
 * 
 *    Rev 1.285   06 Oct 2008 13:16:12   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.284   Aug 07 2008 19:29:12   wongsakw
 * IN1355608 - fund class values not displayed - needs to be broadened.
 * 
 *    Rev 1.283   17 Jul 2008 14:19:48   kovacsro
 * PET5517 FN60C Cancellation of Contribution Receipts - Rebooking 
 * 
 *    Rev 1.282   17 Jul 2008 11:02:42   kovacsro
 * PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
 * 
 *    Rev 1.279   Apr 04 2008 09:25:42   wongsakw
 * IN#1235050 Change the way retrieving Fund Settled Units & Fund Market Value fields.
 * 
 *    Rev 1.278   Jan 22 2008 15:43:04   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.277   17 Sep 2007 16:11:52   popescu
 * Incidetn# 956765 - moved delivery to to the main tradesdlg.cpp
 * 
 *    Rev 1.276   Sep 06 2007 17:19:02   popescu
 * GAP 18 - added manual management fee rebate to manual dividend screen
 * 
 *    Rev 1.275   Aug 30 2007 15:17:30   jankovii
 * PET 2360 FN11 - Dilution.
 * 
 *    Rev 1.274   Aug 10 2007 14:12:04   jankovii
 * PET 2360 FN14&FN19 - Management Fee.
 * 
 *    Rev 1.273   Aug 07 2007 15:40:14   jankovii
 * Gaps 14&19 PET2360 - MF.
 * 
 *    Rev 1.272   12 Jul 2007 17:10:00   popescu
 * AIM GAP 2 AMS - added an extra field to trading CloneAcctAMS - used in AllTransfer to copy AMS to the to acct.
 * 
 *    Rev 1.271   Mar 30 2007 13:58:02   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.269   Mar 14 2007 14:48:02   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.268   Nov 08 2006 17:01:54   popescu
 * PET 2281/FN 01 - Copy account functionality -TA
 * 
 *    Rev 1.267   Sep 07 2006 21:37:48   popescu
 * STP 2192/02
 * 
 *    Rev 1.266   Aug 29 2006 18:21:56   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.264   Jul 07 2006 14:51:44   fengyong
 * Incident #659311 - Add flag check client name
 * 
 *    Rev 1.263   Apr 12 2006 11:25:46   fengyong
 * Incident 593732 - update account number to AWD after trade entry.
 * 
 *    Rev 1.262   Mar 10 2006 09:20:12   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params - more work
 * 
 *    Rev 1.261   Mar 06 2006 11:03:40   popescu
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.260   Feb 21 2006 10:33:04   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.259   Feb 20 2006 13:04:28   ZHANGCEL
 * PET 1334 - FN1 -- Added new Field for the ESG Settlement enhancement
 * 
 *    Rev 1.258   Feb 07 2006 11:29:42   AGUILAAM
 * IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
 * 
 *    Rev 1.257   Jan 23 2006 14:07:22   zhengcon
 * Incident #521273 -- Auto Clone - Integration  - Add new LOB (Batch) field to confirmation
 * 
 *    Rev 1.256   Jan 12 2006 13:48:20   AGUILAAM
 * PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
 * 
 *    Rev 1.255   Dec 21 2005 11:10:22   popescu
 * Incident# 433232 - prevent a call to view 20 if fund/class are empty
 * 
 *    Rev 1.254   Nov 30 2005 13:50:58   AGUILAAM
 * PET 1228 FN 02 - EUSD Phase 2
 * 
 *    Rev 1.253   Nov 29 2005 15:23:26   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.252   Nov 28 2005 17:48:28   popescu
 * Incident: 438721 - fixed. search using alt acct/xref num for rebooks.
 * 
 *    Rev 1.251   Nov 26 2005 17:48:54   popescu
 * Incident: 438721fixed. rebook for diff. acct/diff. trans type
 * 
 *    Rev 1.250   Nov 25 2005 11:17:58   popescu
 * Incident# 462038 - BPServer has been changed to perform an exact search by other reference number.
 * 
 *    Rev 1.249   Nov 17 2005 18:43:48   popescu
 * Incident# 458387 - CCB 2023 - fix the search by other ref/alt acct - code got broken in v.1.241 - re-synch for 66. 
 *
 *    Rev 1.248   Nov 10 2005 11:02:52   popescu
 * Incident# 450556 - if rebook and AWD enabled ExtTransNum has to be updated
 * 
 *    Rev 1.247   Nov 01 2005 19:00:52   popescu
 * Incident# 438721 - fixed internal crash during reset during rebook. 
 * 
 *    Rev 1.246   Oct 26 2005 16:02:28   popescu
 * Incident# 434072 - Pending Trade message - shows in 'Caution' box after a rebook
 * 
 *    Rev 1.245   Sep 08 2005 12:59:06   popescu
 * Incident# 398841 - activated rebook for rollovers
 * 
 *    Rev 1.244   Aug 29 2005 10:42:32   popescu
 * Incident 390388 - wire order number should be blanked out for multiple rebooks
 * 
 *    Rev 1.243   Aug 26 2005 10:53:10   popescu
 * Incident 388267 - set the adjtransnum for rebook of trades for different acct num/transtype
 * 
 *    Rev 1.242   Aug 17 2005 11:45:36   popescu
 * PET 1235/01 rebook and cancelation - cleaned the code, 
 * 
 *    Rev 1.241   Aug 12 2005 15:23:22   Yingbaol
 * PET1235,FN01: take couple of line out for rebook.
 * 
 *    Rev 1.240   Jul 15 2005 09:26:46   Yingbaol
 * PET1235,FN01: pass parameters 
 * 
 *    Rev 1.239   Jul 11 2005 11:06:24   AGUILAAM
 * PET1235: dilution, part of rebook/cancellation
 * 
 *    Rev 1.238   Jul 08 2005 09:38:10   Yingbaol
 * PET1235,FN01:cancellation rebook
 * 
 *    Rev 1.237   Jun 16 2005 19:00:46   popescu
 * Incident# 323484 - added Delivery Method field to attribute box on the trade entry screen
 * 
 *    Rev 1.236   Jun 13 2005 18:46:08   popescu
 * Incident # 332227 - fixed trade entry crash  for allocated orders with composed of funds with and/or without split commissions.
 * 
 *    Rev 1.235   Jun 13 2005 15:45:46   Fengyong
 * #Incident 328345 - Disable end button in confirmation screen if coming from modify pending trade with loss
 * 
 *    Rev 1.234   Jun 03 2005 19:40:52   popescu
 * Fixed trade entry crash
 * 
 *    Rev 1.233   Jun 01 2005 13:32:52   popescu
 * fixed small comp error
 * 
 *    Rev 1.232   May 30 2005 23:07:02   popescu
 * Incident # 301110 - reversed the old fix; updated the effective date on the trade entry screen for new trades only if user changes the default value of it. Otherwise is up to view 127 to determine the correct date. - synch-up 61/62
 * 
 *    Rev 1.231   May 30 2005 23:02:02   popescu
 * Incident# 317930 - fixed TradeDate display issue for aggregated orders- backed old fix out - sunch-up 61/62
 * 
 *    Rev 1.230   May 27 2005 17:14:42   Fengyong
 * #Incident 317930 - syncup, Add function CopyFromParent
 * 
 *    Rev 1.229   May 27 2005 10:53:18   popescu
 * Incident # 319459 - fixed the Manual Dividend reset issue - also used TradesProcess for manual dividends; 
 * 
 *    Rev 1.228   May 25 2005 13:55:38   popescu
 * Incident# 315850 - fixed freezing issue with Desktop when user resets a Redemption
 * 
 *    Rev 1.227   May 18 2005 09:05:28   yingbaol
 * PET1203,FN01 Commission Class A enhancement
 * 
 *    Rev 1.226   May 05 2005 16:39:36   Fengyong
 * #Incident 248320 - Condition rate modification not update in pending trade list correctly.
 * 
 *    Rev 1.225   Apr 14 2005 11:07:06   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.224   Apr 07 2005 12:22:24   popescu
 * Incident #278545, open-up effective date field on trade entry screen
 * 
 *    Rev 1.223   Apr 05 2005 16:33:10   popescu
 * Incident# 279170, fixed the Aberdeen cycle issue, by zeroing out the comm percentages if the acquisition fee - split rates are 0 - synch-up from release 60.0.0 - branch 1.221.1.0
 * 
 *    Rev 1.222   Mar 31 2005 12:13:42   popescu
 * Incident# 260162, used Name1 and Name2 to build the correct  name for address 02, ... 
 * 
 *    Rev 1.221   Mar 24 2005 10:40:06   popescu
 * Incident # 260181, split commissions not applicable for ED's with deposittypes 9,10,18
 * 
 *    Rev 1.220   Mar 17 2005 18:43:16   popescu
 * Incident# 262704, fixed sales rep validation and Sales rep does not exist ...messsage, synch-up from release 59
 * 
 *    Rev 1.219   Mar 17 2005 16:56:12   popescu
 * Incident# 268097, added ForceVerify field to the processing layer
 * 
 *    Rev 1.218   Mar 15 2005 17:51:16   Fengyong
 * Incident #262042 Sync Up - Trade Default
 * 
 *    Rev 1.217   Mar 09 2005 17:28:32   winnie
 * PET 260162 : Display name from the address if it is available for the address box; otherwise display the account owner name
 * 
 *    Rev 1.216   Mar 04 2005 14:16:22   popescu
 * Incident 248320, refresh the pending trades list for the current aggregated order, synch-up from Rel_59.0.5
 * 
 *    Rev 1.215   Mar 03 2005 11:04:26   popescu
 * Incident # 256776, fixed flickering of trading screen when user presses F3, synch-up from release 59.0.5
 * 
 *    Rev 1.214   Feb 18 2005 16:57:30   popescu
 * Incident #237786, fixed refresh data flickering issue, synch-up from Release 59.0.4
 * 
 *    Rev 1.213   Feb 15 2005 14:13:52   popescu
 * 244581, when modifying a pending trade apply the permission mode (TransModPerm) down onto TransFeeList only once, first time when the list is created, synch-up from Rel_59.0.3, branch 1.203.1.4
 * 
 *    Rev 1.212   Feb 03 2005 13:30:58   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.211   Feb 02 2005 14:35:08   popescu
 * Incident 234725, sybch-up from release 59.0.2, branch 1.203.1.3
 * 
 *    Rev 1.210   Feb 02 2005 13:57:40   Fengyong
 * PET1117 FN66  - API SWIFT/Investro/Pwld Search by AltAccount number and other Reference Number
 * 
 *    Rev 1.209   Feb 01 2005 11:44:48   popescu
 * PET 1117/66/67/68, API validations for SWIFT/Investro/Pwld
 * 
 *    Rev 1.208   Jan 31 2005 14:46:34   popescu
 * PTS 10038434, fix the fees read only properties based on the mod perm value of a pending trade , Rel_59 synch-up, from 1.203.1.2
 * 
 *    Rev 1.207   Jan 29 2005 19:27:32   popescu
 * PET 1117. 66. added fields API
 * 
 *    Rev 1.206   Jan 28 2005 16:27:22   popescu
 * PTS 10038434, synch-up from rel 59, branch 1.203.1.1
 * 
 *    Rev 1.205   Jan 28 2005 13:44:44   popescu
 * PTS 10038381, synch-up from release 59.0.1
 * 
 *    Rev 1.204   Jan 24 2005 17:44:04   popescu
 * PET 1117/68, SWIFT, Pwld enhancement
 * 
 *    Rev 1.203   Jan 23 2005 13:56:14   popescu
 * PTS 10037346, made exchange available for the user
 * 
 *    Rev 1.202   Jan 21 2005 15:29:58   popescu
 * PET 1117/06, API pending trade mods
 * 
 *    Rev 1.201   Jan 14 2005 14:40:38   Fengyong
 * PET1117 FN06 - API acq fee override
 * 
 *    Rev 1.200   Jan 14 2005 13:49:28   Fengyong
 * PET1117/06, API AcctAlloation
 * 
 *    Rev 1.199   Jan 13 2005 17:36:20   popescu
 * PET 1117/06, API further changes
 * 
 *    Rev 1.198   Jan 11 2005 16:34:20   Fengyong
 * PET1117/06 - Trade processing - put back babel API fields
 * 
 *    Rev 1.197   Jan 10 2005 17:06:34   popescu
 * PTS 10032024, synch-up from JTradesProcess.cpp, v 1.51
 * 
 *    Rev 1.196   Jan 07 2005 19:04:58   popescu
 * PTS 10037553, fixed issues with modifying pending trades 
 * 
 *    Rev 1.195   Jan 06 2005 13:56:48   popescu
 * PTS 10037503, trade object set to be dirty immediate after being created
 * 
 *    Rev 1.194   Dec 31 2004 14:13:32   Fengyong
 * PET1117FN06 - Checkin for modifypending trade api
 * 
 *    Rev 1.193   Dec 30 2004 09:44:26   Fengyong
 * PET1117FN06 - check in for purchase API 
 * 
 *    Rev 1.192   Dec 21 2004 16:10:38   popescu
 * PTS 10037153, removed pending trades list after user succesfully modifies a pending trade
 * 
 *    Rev 1.191   Dec 16 2004 19:06:30   popescu
 * PET 1117/06, fixes for the case were account nums are invalid, or becomming invalid due to a change in Trade's context. Also, fixes for the order of keys when adding new trade
 * 
 *    Rev 1.190   Dec 11 2004 11:47:10   popescu
 * PET 1117/56 more fixes, pending trade mods
 * 
 *    Rev 1.189   Dec 09 2004 22:30:44   popescu
 * PET 11717/06, fees and mod pending trades
 * 
 *    Rev 1.188   Dec 08 2004 22:07:54   popescu
 * PET 1117/06, more fees
 * 
 *    Rev 1.187   Dec 08 2004 17:49:44   popescu
 * PET 1117/56, modify an aggregated order's pending trades list
 * 
 *    Rev 1.186   Dec 07 2004 13:45:32   Fengyong
 * PET1117FN56 - API testing adjustment
 * 
 *    Rev 1.185   Dec 07 2004 02:45:04   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.184   Dec 07 2004 01:37:18   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.183   Dec 06 2004 17:20:14   popescu
 * PET 1117/06, added the process ids for API to TradesProcess, removed them from JTradesProcess
 * 
 *    Rev 1.182   Dec 02 2004 20:59:00   popescu
 * PET 1117/06, more fee fixes
 * 
 *    Rev 1.181   Dec 02 2004 18:22:36   popescu
 * PET 1117/06/56, trades processing/fees processing
 * 
 *    Rev 1.180   Dec 01 2004 19:50:14   popescu
 * PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
 * 
 *    Rev 1.179   Nov 30 2004 20:09:44   popescu
 * PET 1117/06
 * 
 *    Rev 1.178   Nov 30 2004 07:53:10   popescu
 * PET 1117/06, made purchase total and OnBtnHistory active once again
 * 
 *    Rev 1.177   Nov 29 2004 20:29:58   popescu
 * PET 1117/06/56 fees/trades processing
 * 
 *    Rev 1.176   Nov 25 2004 14:58:30   popescu
 * PET 1117/06, settle locations
 * 
 *    Rev 1.175   Nov 24 2004 21:34:30   popescu
 * PET 1117/06/56. trade processing, settle location
 * 
 *    Rev 1.174   Nov 22 2004 13:08:46   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.173   Nov 15 2004 13:21:02   popescu
 * PET 1117/06, .NET synch changes
 * 
 *    Rev 1.172   Nov 09 2004 19:23:30   popescu
 * PET 1117/06, trade processing
 * 
 *    Rev 1.171   Nov 09 2004 16:48:44   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.170   Nov 07 2004 14:06:24   popescu
 * PET 1117/06, synch changes
// 
//    Rev 1.8   Nov 04 2004 17:36:40   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.7   Nov 02 2004 19:18:52   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.6   Oct 28 2004 18:23:32   popescu
// PET 1117/06
// 
//    Rev 1.5   Oct 27 2004 11:26:28   popescu
// PET 1117/06
// 
//    Rev 1.4   Oct 22 2004 19:58:32   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.3   Oct 21 2004 06:28:34   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.2   Oct 01 2004 19:25:14   popescu
// PET 1117/06, SSB Germany Trade processing
// 
//    Rev 1.1   Sep 23 2004 16:00:36   popescu
// PET 1117/06 - Trade processing work in progress...
// 
//    Rev 1.0   Aug 13 2004 18:55:54   popescu
// Initial revision.
 * 
// 
*/
//******************************************************************************

