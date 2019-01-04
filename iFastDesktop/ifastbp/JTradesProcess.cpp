//******************************************************************************
//
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
// ^FILE   : JTradesProcess.cpp
// ^AUTHOR : Yong Mei Feng
// ^DATE   : November 2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JTradesProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

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
// ^FILE   : JTradesProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JTradesProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jtradesprocess.hpp"
#include "tradesprocessincludes.h"

//CBO's
#include <ifastcbo\agent.hpp>
#include <ifastcbo\acctcategorylist.hpp>
#include <ifastcbo\address.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\branch.hpp>
#include <ifastcbo\broker.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\splitcommissionlist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\tradefundalloc.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

//the gui process
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADES;
//bp processes
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PURCHASE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EXCHANGE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REDEMPTION;
#include <bfproc\concreteprocesscreator.hpp>
/*static ConcreteProcessCreator< JTradesProcess > processCreator1 (CMD_BPROC_PURCHASE) ;
static ConcreteProcessCreator< JTradesProcess > processCreator2 (CMD_BPROC_REDEMPTION);
static ConcreteProcessCreator< JTradesProcess > processCreator3 (CMD_BPROC_EXCHANGE);
*/

namespace
{
   const I_CHAR * const CLASSNAME = I_ ("JTradesProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
JTradesProcess::JTradesProcess ( GenericInterfaceContainer *pGIC, 
                                 GenericInterface *pGIParent, 
                                 const Command &rCommand
                               ) : AbstractProcess (pGIC, pGIParent, rCommand),
_rpChildGI (NULL),
_pTradesList (NULL),
_accountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

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
                  ACCOUNT,
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
                  ACCOUNT_TO,
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
//fund allocation list, parent the trades list
   addContainer ( IFASTBP_PROC::FUND_ALLOCATION, 
                  true,
                  IFASTBP_PROC::TRADES_LIST, 
                  true,
                  I_("FundAllocation")
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
   addFieldDetails ( IsAccountSetAndValid, 
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
   addFieldDetails ( ifds::Baycom, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::Valoren, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::CUSIP, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TDCC, 
                     IFASTBP_PROC::TRADES_LIST
   );

   //two side
   addFieldDetails ( ifds::AccountTo, 
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
   );
   addFieldDetails ( IsAccountSetAndValid, 
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
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::AmtType, 
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::GrossOrNet,
                     IFASTBP_PROC::TRADES_LIST
   );
//shareholder address
   addFieldDetails ( ifds::AddrCode,
                     IFASTBP_PROC::TRADES_LIST,
                     SUBCLASS_PROCESS
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
//bank fields
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
//the grid headings
   addFieldDetails ( ifds::TradeAttributesHeading,   
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::TradeAttributesFields, 
                     IFASTBP_PROC::TRADES_LIST
   );
//the attribute grid fields
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
                     IFASTBP_PROC::TRADES_LIST
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
   addFieldDetails ( ifds::AcqFeeOption,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
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
   addFieldDetails ( ifds::SuppressCode,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::RedCode,                 //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::LSIFCode,                //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );   
   addFieldDetails ( ifds::BankChrgs,               //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::FromCurrency,            //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::UseEnteredFee,           //in attributes grid
                     IFASTBP_PROC::TRADES_LIST
   );
   addFieldDetails ( ifds::ConfirmRequired,         //in attributes grid
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
   addFieldDetails ( AreTaxRatesAllowed, 
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
}

//******************************************************************************
JTradesProcess::~JTradesProcess()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   _rpChildGI = NULL;
//erase the map of conditions
   CONDITIONS_MAP::iterator mc_iter = 
         _conditionsMap.begin ();

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
}

//******************************************************************************
SEVERITY JTradesProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doInit")
                         );

   try
   {
      getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      _accountNum.strip();
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
E_COMMANDRETURN JTradesProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doProcess")
                         );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      rtn = invokeCommand ( this, 
                            CMD_GUI_TRADES, 
                            getProcessType(), 
                            isModal(),
                            &_rpChildGI
                          );
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
                        CND::BP_ERR_UNKNOWN_EXCEPTION
                     );
   }
   return rtn;
}

//******************************************************************************
SEVERITY JTradesProcess::deleteItemFromList ( const GenericInterface *rpGICaller,
                                              const BFContainerId& idList
                                            )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DELETEITEMFROMLIST
                          );
   removeCurrentTradeDataFromMaps ();
   return AbstractProcess::deleteItemFromList (rpGICaller, idList);
}

//******************************************************************************
void JTradesProcess::doGetField ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup, 
                                  DString &strValueOut,
                                  bool bFormatted
                                ) const
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField")
                         );

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

   strValueOut = NULL_STRING;
   if (idContainer == IFASTBP_PROC::TRADES_LIST)
   {
      BFAbstractCBO *rpPtr = const_cast<JTradesProcess*> (this)->
                             getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                          idDataGroup
                                        );
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
              idField == ifds::ToClass
            )
         {
            rpPtr->getField ( idField, 
                              strValueOut, 
                              idDataGroup, 
                              bFormatted
                            );
         }
         else if (idField == ifds::AddrCode)
         {
            rpPtr->getField ( idField, 
                              strValueOut, 
                              idDataGroup, 
                              false
                            );
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
               strValueOut = pTrade->isBankingNeeded (idDataGroup) ? I_("Y") : I_("N");
            }
         }
         else if (idField == AreAllocationsAllowed)
         {
            Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

            if (rpPtr)
            {
               strValueOut = pTrade->areAllocationsAllowed (idDataGroup) ? I_("Y") : I_("N");
            }
         }
         else if (idField == IsSplitCommissionAllowed)
         {
            Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

            if (rpPtr)
            {
               strValueOut = pTrade->isSplitCommissionAllowed (idDataGroup) ? I_("Y") : I_("N");
            }
         }
         else if (idField == AreTaxRatesAllowed)
         {
            Trade *pTrade = dynamic_cast <Trade*> (rpPtr);

            if (rpPtr)
            {
               strValueOut = pTrade->areTaxRatesAllowed (idDataGroup) ? I_("Y") : I_("N");
            }
         }
      }
   }
   else if ( idContainer == ACCOUNT ||
             idContainer == ACCOUNT_TO
           )
   {
      BFAbstractCBO *rpPtrMFAccount = const_cast<JTradesProcess*> (this)->
                                      getCBOItem ( idContainer, 
                                                   idDataGroup
                                                 );
      if (idField == ifds::HighestEntityRisk)
      {
         if (rpPtrMFAccount)
         {
            DString highestEntityRisk;

            rpPtrMFAccount->getField ( idField, 
                                       highestEntityRisk, 
                                       idDataGroup, 
                                       bFormatted
                                     );
            strValueOut = I_("N");
            if ( highestEntityRisk == I_("2") ||
                 highestEntityRisk == I_("3")
               )
            {
               strValueOut = I_("Y");
            }
         }
      }
      else if (idField == IsAccountSetAndValid)
      {
         strValueOut = const_cast<JTradesProcess*> (this)->
                        isAccountSetAndValid ( idContainer, 
                                               idDataGroup
                                             ) 
                                             ? I_("Y") : I_("N");
      }
   }
   else if ( idContainer == ADDRESS ||
             idContainer == SHAREHOLDER_ADDRESS
           )
   {
      if (idField == ifds::Name)
      {
         BFAbstractCBO *rpPtrMFAccount = const_cast<JTradesProcess*> (this)->
                                         getCBOItem ( ACCOUNT, 
                                                      idDataGroup
                                                    );
         if (rpPtrMFAccount)
         {
            DString accountNum;

            rpPtrMFAccount->getField ( ifds::AccountNum, 
                                       accountNum, 
                                       idDataGroup, 
                                       false
                                     );
            if (!accountNum.empty())
            {
               pDSTCWorkSession->
                  getFirstSequenced01AccountholderEntityName ( idDataGroup, 
                                                               accountNum, 
                                                               strValueOut 
                                                             );
            }
         }
      }
      else //for other address fields
      {
         BFAbstractCBO *rPtrAddress = const_cast<JTradesProcess*> (this)->
                                         getCBOItem ( idContainer, 
                                                      idDataGroup
                                                    );
         if (rPtrAddress)
         {
            rPtrAddress->getField ( idField, 
                                    strValueOut, 
                                    idDataGroup, 
                                    bFormatted
                                  );
         }
      }
   }
   else if (idContainer == ADDRESS_TO)
   {
      if (idField == ifds::Name)
      {
         BFAbstractCBO *rpPtrMFAccountTo = const_cast<JTradesProcess*> (this)->
                                           getCBOItem ( ACCOUNT_TO, 
                                                        idDataGroup
                                                      );
         if (rpPtrMFAccountTo)
         {
            DString accountTo;

            rpPtrMFAccountTo->getField (
                                        ifds::AccountNum, 
                                        accountTo, 
                                        idDataGroup, 
                                        false
                                       );
            if (!accountTo.empty())
            {
               pDSTCWorkSession->
                  getFirstSequenced01AccountholderEntityName ( idDataGroup, 
                                                               accountTo, 
                                                               strValueOut 
                                                             );
            }
         }         
      }
      else //for other address fields
      {
         BFAbstractCBO *rPtrAddress = const_cast<JTradesProcess*> (this)->
                                         getCBOItem ( idContainer, 
                                                      idDataGroup
                                                    );
         if (rPtrAddress)
         {
            rPtrAddress->getField ( idField, 
                                    strValueOut, 
                                    idDataGroup, 
                                    bFormatted
                                  );
         }
      }
   }
   else if ( idContainer == BROKER ||
             idContainer == BRANCH ||
             idContainer == AGENT
           )
   {
      BFAbstractCBO *rpPtrTrade = const_cast<JTradesProcess*> (this)->
                                    getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                               );
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
                                bFormatted
                               );
//broker/branch/slsrepcode fields are valid and not empty, get the name
         if ( !codeFieldValue.empty() && 
              rpPtrTrade->getErrorState (codeFieldId, idDataGroup) <= WARNING
            )
         {
            BFAbstractCBO *rpPtr = const_cast<JTradesProcess*> (this)->
                                       getCBOItem ( idContainer, 
                                                    idDataGroup
                                                  );
            if (rpPtr)
            {
               rpPtr->getField ( idField, 
                                 strValueOut, 
                                 idDataGroup, 
                                 bFormatted
                               );
            }
         }
      }
   }
   else if ( (idContainer == ACCOUNT_HOLDINGS ||idContainer == ACCOUNT_HOLDINGS_TO) &&
             (idField == ifds::SettledUnits || idField == ifds::SettledValue)
           )
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

      BFAbstractCBO *rpPtrTrade = const_cast<JTradesProcess*> (this)->
                                      getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                   idDataGroup
                                                 );
      if (rpPtrTrade)
      {
         if (
              rpPtrTrade->getErrorState (fundCodeFieldId, idDataGroup) <= WARNING &&
              rpPtrTrade->getErrorState (classCodeFieldId, idDataGroup) <= WARNING
            )
         {
            MFAccountHoldingList *pHoldings = 
                  dynamic_cast <MFAccountHoldingList*> 
                     (
                        const_cast<JTradesProcess*> (this)->
                              getCBOList ( idContainer, 
                                           idDataGroup
                                         )
                     );
            DString fundCode, 
               classCode;

            rpPtrTrade->getField ( fundCodeFieldId,
                                   fundCode,
                                   idDataGroup,
                                   false
                                 );
            rpPtrTrade->getField ( classCodeFieldId,
                                   classCode,
                                   idDataGroup,
                                   false
                                 );
            if (pHoldings)
            {
               BFObjIter iter ( *pHoldings, 
                                idDataGroup, 
                                true, 
                                BFObjIter::ITERTYPE::NON_DELETED
                              );

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
                                               bFormatted
                                             );
               }
            }
         }
      }
   }
   else if ( idContainer == TRANS_FEE_LIST && 
             idField == IsChargeFee
           )
   {
      TransFee *rpPtrTransFee = dynamic_cast <TransFee*> 
                        ( const_cast<JTradesProcess*> (this)->
                                getCBOItem ( TRANS_FEE_LIST, 
                                             idDataGroup
                                           )
                        );
      if (rpPtrTransFee)
      {
         strValueOut = rpPtrTransFee->isChargeFee (idDataGroup) ? I_("Y") : I_("N");
      }
   }
}

//******************************************************************************
SEVERITY JTradesProcess::doSetField ( const GenericInterface *rpGICaller, 
                                      const BFContainerId &idContainer, 
                                      const BFFieldId &idField,
                                      const BFDataGroupId &idDataGroup, 
                                      const DString &strValue, 
                                      bool bFormatted
                                    ) 
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doSetField")
                         );

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
           idField == ifds::ToClass
         )
      {
         BFAbstractCBO *rpPtr = getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                             idDataGroup
                                           );
         if (rpPtr)
         {
            if (idField == ifds::AccountNum)
            {
               DString tradeKey = getCurrentListItemKey ( this,
                                                          IFASTBP_PROC::TRADES_LIST
                                                        );
               CONDITIONVECTOR *pSearchConditions = NULL;

               if (tradeKey != NULL_STRING)
               {
                  TKey tKey (tradeKey, idContainer, idField, idDataGroup);
                  CONDITIONS_MAP::iterator m_iter = _conditionsMap.find (tKey);

                  if (m_iter != _conditionsMap.end())
                  {
                     pSearchConditions = (*m_iter).second;
                     if (pSearchConditions) //erase old conditions
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
                     _conditionsMap.erase (m_iter);
                  }
               }
            }
            rpPtr->setField ( idField, 
                              strValue, 
                              idDataGroup, 
                              bFormatted, 
                              false
                            );
            if (idField == ifds::AccountNum)
            {
               setContainer (ACCOUNT, NULL);
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               if (isAccountSetAndValid (ACCOUNT, idDataGroup))
               {
                  addTrade (rpGICaller);
               }
            }
            else if (idField == ifds::AccountTo)
            {
               setContainer (ACCOUNT_TO, NULL);
               setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
            }
            else if (idField == ifds::AddrCode)
            {
               setContainer (SHAREHOLDER_ADDRESS, NULL);
            }
            else if (idField == ifds::Broker)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (BROKER, NULL);
            }
            else if (idField == ifds::Branch)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (BRANCH, NULL);
            }
            else if (idField == ifds::SlsrepCode)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (AGENT, NULL);
            }
            else if (idField == ifds::EffectiveDate)
            {
               setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               setContainer (ACCOUNT_HOLDINGS, NULL);
               setContainer (ACCOUNT_HOLDINGS_TO, NULL);
            }
            else if ( idField == ifds::FromFund ||
                      idField == ifds::FromClass
                    )
            {
               if (isOneSideTrade ())
               {
                  setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
                  setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               }
            }
            else if ( idField == ifds::ToFund ||
                      idField == ifds::ToClass
                    )
            {
               if (!isOneSideTrade())
               {
                  setContainer (IFASTBP_PROC::FUND_ALLOCATION, NULL);
                  setContainer (IFASTBP_PROC::SPLIT_COMMISSION_LIST, NULL);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY JTradesProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                       const BFContainerId &idContainer,
                                       const BFFieldId &idField,
                                       const BFDataGroupId &idDataGroup,
                                       CONDITIONVECTOR &conditions 
                                      ) const
{  
   SEVERITY sevRtn = NO_CONDITION;

   if (idContainer == IFASTBP_PROC::TRADES_LIST) //for the rest of subclass-ed edit fields
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
           idField == ifds::ToClass
         )
      {
         BFAbstractCBO *rpPtr = const_cast<JTradesProcess*> (this)->
                                getCBOItem ( idContainer, 
                                             idDataGroup
                                           );
         if (rpPtr)
         {
            sevRtn = rpPtr->getErrors (
                                       idField, 
                                       idDataGroup, 
                                       conditions
                                      );
         }
//see, whether the conditions map has anything for the account num
         if (idField == ifds::AccountNum) 
         {
            DString tradeKey = const_cast<JTradesProcess*> (this)->
                               getCurrentListItemKey ( this,
                                                       IFASTBP_PROC::TRADES_LIST
                                                     );
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
const BFProperties *JTradesProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                           const BFContainerId &idContainer, 
                                                           const BFFieldId &idField, 
                                                           const BFDataGroupId &idDataGroup
                                                         )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DOGETFIELDATTRIBUTES
                         );
   const BFProperties *pBFProperties = NULL;

   BFAbstractCBO *rpPtr = getCBOItem ( idContainer, 
                                       idDataGroup
                                     );
   if (rpPtr)
   {
      pBFProperties = rpPtr->getFieldProperties ( idField, 
                                                  idDataGroup
                                                );
   }
   return pBFProperties;
}

//******************************************************************************
bool JTradesProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                          const BFContainerId &idContainer,
                                          const BFFieldId &idField,
                                          const BFDataGroupId &idDataGroup,
                                          BFObserver &rpObserver
                                        ) 
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
           idField == ifds::ToClass
         )
      {
         BFAbstractCBO *rpPtr = getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                             idDataGroup
                                           );
         if (rpPtr)
         {
            bRegistered = rpPtr->registerObserver ( idField, 
                                                    idDataGroup, 
                                                    &rpObserver, 
                                                    FIELD_NOTIFICATIONS, 
                                                    E_EVENT_ALL
                                                  );
         }
      }
   }
   return bRegistered;
}

//******************************************************************************
bool JTradesProcess::doSend ( GenericInterface *rpGICaller, 
                              const I_CHAR *szMessage
                            )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doSend")
                          );
   DString message (szMessage);

   if (message == I_("RefreshBatch"))
   {
      Trade *pTrade = 
         dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                              getDataGroupId()
                                            )
                                );
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
bool JTradesProcess::doModelessChildComplete (const Command &cmd)
{
// End when GUI ends
   return (cmd.getKey() == CMD_GUI_TRADES);
}

//******************************************************************************
bool JTradesProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doModelessSetFocus")
                         );

   bool bRtn = false;
   return bRtn;
}

//**********************************************************************
void *JTradesProcess::getPtrForContainer ( const BFContainerId &idContainer, 
                                           const BFDataGroupId &idDataGroup
                                         )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer")
                         );
   
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   void *ptr = NULL;

   try
   {
      if (idContainer == IFASTBP_PROC::TRADES_LIST)
      {
         if (pDSTCWorkSession->getTradesList ( _pTradesList, 
                                                getDataGroupId(), 
                                                true
                                             ) <= WARNING
            )
         {
            ptr = _pTradesList;
         }
      }
      else if (idContainer == SHAREHOLDER_ADDRESS)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            DString addrCode,
               effectiveDate;

            pTrade->getField ( ifds::AddrCode, 
                               addrCode, 
                               idDataGroup, 
                               false
                             );
            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false
                             );
            if (!addrCode.empty())
            {
               Shareholder *pShareholder = 
                  dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER,
                                                            idDataGroup
                                                          )
                                              );
               if (pShareholder)
               {
                  AddressList *pAddressList = NULL;

                  if (pShareholder->getAddressList ( pAddressList, 
                                                     idDataGroup
                                                   ) <= WARNING &&
                                                pAddressList
                     )
                  {
                     MFAccount *pMFAccount = 
                        dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                                idDataGroup
                                                              )
                                                  );
                     if (pMFAccount)
                     {
                        DString accountNum;

                        pMFAccount->getField ( ifds::AccountNum, 
                                               accountNum, 
                                               idDataGroup, 
                                               false
                                             );                        
                        pAddressList->setField ( ifds::AccountNum, 
                                                 accountNum, 
                                                 idDataGroup, 
                                                 false
                                               );

                        Address *pAddress = NULL;

                        pAddressList->getAddress ( pAddress, 
                                                   addrCode, 
                                                   effectiveDate, 
                                                   idDataGroup
                                                 );
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
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            Broker *pBroker = NULL;

            if ( pTrade->getBroker ( pBroker, 
                                    idDataGroup
                                   ) <= WARNING &&
                 pBroker
               )
            {
               ptr = pBroker;
            }
         }
      }
      else if (idContainer == BRANCH)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            Branch *pBranch = NULL;

            if ( pTrade->getBranch ( pBranch, 
                                     idDataGroup
                                   ) <= WARNING &&
                 pBranch
               )
            {
               ptr = pBranch;
            }
         }
      }
      else if (idContainer == AGENT)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                              )
                                   );
         if (pTrade)
         {
            Agent *pAgent= NULL;

            if ( pTrade->getAgent ( pAgent, 
                                    idDataGroup
                                  ) <= WARNING &&
                 pAgent
               )
            {
               ptr = pAgent;
            }
         }
      }
      else if (idContainer == ACCOUNT)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                              )
                                   );
         if (pTrade)
         {
            DString accountNum;

            pTrade->getField ( ifds::AccountNum, 
                               accountNum, 
                               idDataGroup, 
                               false
                             );
            accountNum.stripLeading ('0');
            if (!accountNum.empty())
            {
               MFAccount *pMFAccount = NULL;

               if (pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                                    accountNum, 
                                                    pMFAccount
                                                  ) <= WARNING &&
                                             pMFAccount
                  )
               {
                  ptr = pMFAccount;
               }
            }
         }
      }
      else if (idContainer == ACCOUNT_HOLDINGS)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            MFAccountHoldingList *pMFAccountHoldings = NULL;

            if (pTrade->getAccountHoldings ( pMFAccountHoldings,
                                             idDataGroup
                                           ) <= WARNING &&
                                       pMFAccountHoldings
               )
            {
               ptr = pMFAccountHoldings;
            }
         }
      }
      else if (idContainer == ACCOUNT_CATEGORY_LIST)
      {
         MFAccount *pMFAccount = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                    idDataGroup
                                                  )
                                      );
         if (pMFAccount)
         {
            AcctCategoryList *pAcctCategoryList = NULL;

            if (pMFAccount->getAcctCategoryList ( pAcctCategoryList, 
                                                  idDataGroup
                                                ) <= WARNING &&
                                             pAcctCategoryList
               )
            {
               ptr = pAcctCategoryList;
            }
         }
      }
      else if (idContainer == SHAREHOLDER)
      {
         MFAccount *pMFAccount = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                    idDataGroup
                                                  )
                                      );
         if (pMFAccount)
         {
            DString shrNum;

            pMFAccount->getField ( ifds::ShrNum, 
                                   shrNum, 
                                   idDataGroup, 
                                   false
                                 );
            shrNum.stripLeading ('0');
            if (!shrNum.empty())
            {
               Shareholder *pShareholder = NULL;

               if (pDSTCWorkSession->getShareholder ( idDataGroup, 
                                                      shrNum, 
                                                      pShareholder
                                                    ) <= WARNING &&
                                                pShareholder
                  )
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
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            DString effectiveDate;

            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false
                             );

            Shareholder *pShareholder = 
               dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER,
                                                         idDataGroup
                                                       )
                                           );
            if (pShareholder)
            {
               AddressList *pAddressList = NULL;

               if (pShareholder->getAddressList ( pAddressList, 
                                                  idDataGroup
                                                ) <= WARNING &&
                                             pAddressList
                  )
               {
                  MFAccount *pMFAccount = 
                     dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT, 
                                                             idDataGroup
                                                           )
                                               );
                  if (pMFAccount)
                  {
                     DString accountNum;

                     pMFAccount->getField ( ifds::AccountNum, 
                                            accountNum, 
                                            idDataGroup, 
                                            false
                                          );                        
                     pAddressList->setField ( ifds::AccountNum, 
                                              accountNum, 
                                              idDataGroup, 
                                              false
                                            );

                     Address *pAddress = NULL;

                     pAddressList->getAddress ( pAddress, 
                                                I_("01"), 
                                                effectiveDate, 
                                                idDataGroup
                                              );
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
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            DString accountTo;

            pTrade->getField ( ifds::AccountTo, 
                               accountTo, 
                               idDataGroup, 
                               false
                             );
            accountTo.stripLeading ('0');
            if (!accountTo.empty())
            {
               MFAccount *pMFAccountTo = NULL;

               if (pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                                    accountTo, 
                                                    pMFAccountTo
                                                  ) <= WARNING &&
                                                pMFAccountTo
                  )
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
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            MFAccountHoldingList *pMFAccountToHoldings = NULL;

            if (pTrade->getAccountToHoldings ( pMFAccountToHoldings,
                                               idDataGroup
                                             ) <= WARNING &&
                                       pMFAccountToHoldings
               )
            {
               ptr = pMFAccountToHoldings;
            }
         }
      }
      else if (idContainer == ACCOUNT_CATEGORY_LIST_TO)
      {
         MFAccount *pMFAccountTo = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                    idDataGroup
                                                  )
                                      );
         if (pMFAccountTo)
         {
            AcctCategoryList *pAcctCategoryListTo = NULL;

            if (pMFAccountTo->getAcctCategoryList ( pAcctCategoryListTo, 
                                                    idDataGroup
                                                  ) <= WARNING &&
                                             pAcctCategoryListTo
               )
            {
               ptr = pAcctCategoryListTo;
            }
         }
      }
      else if (idContainer == SHAREHOLDER_TO)
      {
         MFAccount *pMFAccountTo = 
            dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                    idDataGroup
                                                  )
                                      );
         if (pMFAccountTo)
         {
            DString shrNumTo;

            pMFAccountTo->getField ( ifds::ShrNum, 
                                     shrNumTo, 
                                     idDataGroup, 
                                     false
                                   );
            shrNumTo.stripLeading ('0');
            if (!shrNumTo.empty())
            {
               Shareholder *pShareholderTo = NULL;

               if (pDSTCWorkSession->getShareholder ( idDataGroup, 
                                                      shrNumTo, 
                                                      pShareholderTo
                                                    ) <= WARNING &&
                                                pShareholderTo
                  )
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
                                                 idDataGroup
                                               )
                                   );
         if (pTrade)
         {
            DString effectiveDate;

            pTrade->getField ( ifds::EffectiveDate, 
                               effectiveDate, 
                               idDataGroup, 
                               false
                             );

            Shareholder *pShareholderTo = 
               dynamic_cast <Shareholder*> (getCBOItem ( SHAREHOLDER_TO,
                                                         idDataGroup
                                                       )
                                           );
            if (pShareholderTo)
            {
               AddressList *pAddressListTo = NULL;

               if (pShareholderTo->getAddressList ( pAddressListTo, 
                                                    idDataGroup
                                                  ) <= WARNING &&
                                                pAddressListTo
                  )
               {
                  MFAccount *pMFAccountTo = 
                     dynamic_cast <MFAccount*> (getCBOItem ( ACCOUNT_TO, 
                                                             idDataGroup
                                                           )
                                               );
                  if (pMFAccountTo)
                  {
                     DString accountTo;

                     pMFAccountTo->getField ( ifds::AccountTo, 
                                              accountTo, 
                                              idDataGroup, 
                                              false
                                            );                        
                     pAddressListTo->setField ( ifds::AccountNum, 
                                                accountTo, 
                                                idDataGroup, 
                                                false
                                              );

                     Address *pAddressTo = NULL;

                     pAddressListTo->getAddress ( pAddressTo, 
                                                  I_("01"), 
                                                  effectiveDate, 
                                                  idDataGroup
                                                );
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
                                                  idDataGroup
                                                )
                                   );

         if (pTrade)
         {
            TradeFundAllocList *pTradeFundAllocList = NULL;

            if ( pTrade->getFundAllocationList ( pTradeFundAllocList, 
                                                 idDataGroup
                                               ) <= WARNING &&
                 pTradeFundAllocList
               )
            {
               ptr = pTradeFundAllocList;
            }
         }
      }
      else if (idContainer == IFASTBP_PROC::SPLIT_COMMISSION_LIST)
      {
         TradeFundAlloc *pTradeFundAlloc = 
            dynamic_cast <TradeFundAlloc*> ( getCBOItem ( IFASTBP_PROC::FUND_ALLOCATION, 
                                                          idDataGroup
                                                        )
                                           );

         if (pTradeFundAlloc)
         {
            SplitCommissionList *pSplitCommissionList = NULL;

            if ( pTradeFundAlloc->getSplitCommissionList ( pSplitCommissionList, 
                                                           idDataGroup
                                                         ) <= WARNING &&
                 pSplitCommissionList
               )
            {
               ptr = pSplitCommissionList;
            }
         }
      }
      else if (idContainer == TRANS_FEE_LIST)
      {
         Trade *pTrade = 
            dynamic_cast <Trade*> ( getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                  idDataGroup
                                                )
                                   );

         if (pTrade)
         {
            TransFeeList *pTransFeeList = NULL;

            if ( pTrade->getTransFeeList ( pTransFeeList, 
                                           idDataGroup
                                         ) <= WARNING &&
                 pTransFeeList
               )
            {
               ptr = pTransFeeList;
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
                       CND::BP_ERR_UNKNOWN_EXCEPTION
                     );
   }
   return ptr;
}

//******************************************************************************
SEVERITY JTradesProcess::addTrade (const GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("addTrade ")
                          );
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DString tradeCurrentKey =
               getCurrentListItemKey (rpGICaller, IFASTBP_PROC::TRADES_LIST),
         tradeNewKey;
   Trade *pCurrentTrade = 
      dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                           idDataGroup
                                         )
                             );

   if (_pTradesList && pCurrentTrade)
   {
      DString transType,
         accountNum;

      pCurrentTrade->getField ( ifds::TradesTransType, 
                                transType, 
                                idDataGroup, 
                                false
                              );
      pCurrentTrade->getField ( ifds::AccountNum, 
                                accountNum, 
                                idDataGroup, 
                                false
                              );
      _pTradesList->setField ( ifds::TradesTransType, 
                               transType, 
                               idDataGroup, 
                               false
                             );
      _pTradesList->setField ( ifds::AccountNum, 
                               accountNum, 
                               idDataGroup, 
                               false
                             );
      BFAbstractCBO *pNewTrade = _pTradesList->
                                          getObject ( tradeNewKey, //should be passed in as null_string
                                                      idDataGroup
                                                    );
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
                        idDataGroup
                      );
         
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
                                                       pAccountConditions
                                                     )
                                     );
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
            //reset the trades list container,
            //to have the iterators regenerated
            setContainer (IFASTBP_PROC::TRADES_LIST, NULL);
            //call the dialog and tell it to refresh the transactions list
            //and set the current list item on the new trade
            setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeNewKey); 
            _rpChildGI->send (this, I_("RefreshTransactionsList"));
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

/*
//******************************************************************************
SEVERITY JTradesProcess::doValidateAll ( BFAbstractCBO *rpWSD,
                                         const BFDataGroupId &idDataGroup
                                      )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll")
                          );
//for now
   if (!_pTradesList)
   {
      _pTradesList->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
*/

//******************************************************************************
bool JTradesProcess::doOk (GenericInterface *rpGICaller)
{
   return true;
}

//******************************************************************************
bool JTradesProcess::doCancel (GenericInterface *rpGICaller)
{
   return true;
}

//******************************************************************************
bool JTradesProcess::isAccountSetAndValid ( const BFContainerId &accountContainerId, 
                                            const BFDataGroupId &idDataGroup
                                          )
{
   BFAbstractCBO *rpPtrMFAccount = const_cast<JTradesProcess*> (this)->
                                   getCBOItem ( accountContainerId, 
                                                idDataGroup
                                              );
   BFAbstractCBO *rpPtrTrade = const_cast<JTradesProcess*> (this)->
                                   getCBOItem ( IFASTBP_PROC::TRADES_LIST, 
                                                idDataGroup
                                              );
   SEVERITY accountNumSeverity = NO_CONDITION;
   
   if (accountContainerId == ACCOUNT)
   {
      DString tradeKey = const_cast<JTradesProcess*> (this)->
                         getCurrentListItemKey ( this,
                                                 IFASTBP_PROC::TRADES_LIST
                                               );
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
   return rpPtrMFAccount && 
          rpPtrTrade &&
          rpPtrTrade->getErrorState ( accountContainerId == ACCOUNT ? ifds::AccountNum : ifds::AccountTo, 
                                      idDataGroup
                                    ) <= WARNING &&
          accountNumSeverity <= WARNING;
}

//******************************************************************************
void JTradesProcess::removeCurrentTradeDataFromMaps()
{
   //remove the current trade info from the funky maps
   DString tradeKey = const_cast<JTradesProcess*> (this)->
                      getCurrentListItemKey ( this,
                                              IFASTBP_PROC::TRADES_LIST
                                            );
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
}

//******************************************************************
bool JTradesProcess::isOneSideTrade ()
{
   DString transType;

   getField (this, ifds::TradesTransType, transType, false);
   return DSTCommonFunctions::codeInList (transType, TRADETYPE::ONE_SIDE_TRADE);
}

//******************************************************************************
bool JTradesProcess::setCommitDataGroupAsHost()
{
   return true;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JTradesProcess.cpp-arc  $
// 
//    Rev 1.56   Dec 06 2004 17:20:08   popescu
// PET 1117/06, added the process ids for API to TradesProcess, removed them from JTradesProcess
// 
//    Rev 1.55   Nov 22 2004 13:08:42   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.54   Nov 14 2004 14:22:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.53   Nov 07 2004 17:02:36   popescu
// PET 1117/56 change the id of the process
// 
//    Rev 1.52   Nov 07 2004 14:06:18   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.51   Sep 27 2004 10:31:20   ZHANGCEL
// PTS 10032024: Set ForceVerify to "Yes" in order to process an API trade.
// 
//    Rev 1.50   Sep 27 2004 10:26:16   ZHANGCEL
// PET1094_FN8 -- AdminFee enhancement
// 
//    Rev 1.49   Jun 18 2004 10:28:58   FENGYONG
// PTS 10031311, syncup with desktop trading key fix for eproduct.
// 
//    Rev 1.48   May 20 2004 14:16:44   popescu
// PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
// 
//    Rev 1.47   May 09 2004 20:09:08   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.46   May 06 2004 18:37:06   popescu
// PET 985, fn01, Trade Entry LSIF
// 
//    Rev 1.45   Mar 29 2004 14:54:04   FENGYONG
// PTS 10028616, ACHProcessor feature
// 
//    Rev 1.44   Feb 10 2004 15:06:22   FENGYONG
// PTS 10026949 - API modify pending trade
// 
//    Rev 1.43   Jan 13 2004 16:06:36   popescu
// PET 910, System Integration Testing, Rel_55.0.0.2
// Fix involved allows back dated trades when modifying a pending trade; issue occurred due to a previous fix where the WorkSessionTradesList is now retrieved using an 'idDataGroup' not equal with BF::HOST.
// 
//    Rev 1.42   Dec 12 2003 16:52:58   FENGYONG
// Add fields
// 
//    Rev 1.41   Oct 17 2003 14:40:56   FENGYONG
// Add comment for datalag checking
// 
//    Rev 1.40   May 27 2003 18:29:02   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.39   May 22 2003 14:11:38   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.38   Apr 09 2003 10:19:32   FENGYONG
// follow the CBO change , change Slsrep to SlsrepCode
// 
//    Rev 1.37   Mar 21 2003 17:44:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.36   Mar 11 2003 14:03:12   PURDYECH
// Fixed up Condition declarations to eliminate linker warnings.
// 
//    Rev 1.35   Feb 18 2003 10:37:08   FENGYONG
// change for api trade allocation
// 
//    Rev 1.34   Feb 12 2003 11:16:04   FENGYONG
// Add SWIFT fields
// 
//    Rev 1.33   Dec 12 2002 11:12:36   FENGYONG
// add transtype tradedate to key
// 
//    Rev 1.32   Oct 09 2002 23:53:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.31   Oct 08 2002 16:57:50   FENGYONG
// fix condition problem
// 
//    Rev 1.30   Sep 03 2002 14:32:22   FENGYONG
// check 181 in dook
// 
//    Rev 1.29   Aug 29 2002 17:07:28   SMITHDAV
// ClientLocale and Field interface changes.
// 
//    Rev 1.28   Aug 29 2002 15:29:46   FENGYONG
// temp checkin
// 
//    Rev 1.27   Aug 23 2002 16:20:20   FENGYONG
// Add check cut off time for pending trade
// 
//    Rev 1.26   Aug 19 2002 15:23:04   FENGYONG
// add setcurrentlistItem function
// 
//    Rev 1.25   Aug 13 2002 10:37:18   KOVACSRO
// RELEASE 48. Fixed spelling.
// 
//    Rev 1.24   Aug 07 2002 11:23:38   FENGYONG
// fix for ignorewarning 
// 
//    Rev 1.23   22 May 2002 18:24:38   PURDYECH
// BFData Implementation
// 
//    Rev 1.22   08 May 2002 16:45:04   KOVACSRO
// Changed AllocFundToCode into FundCode and AllocClassToCode into ClassCode
// 
//    Rev 1.21   29 Apr 2002 16:13:08   KOVACSRO
// allocation related modifications.
// 
//    Rev 1.20   27 Mar 2002 19:55:16   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.19   Feb 22 2002 13:48:04   FENGYONG
// remove cnd throw
// 
//    Rev 1.18   19 Feb 2002 18:23:38   KOVACSRO
// reset AccountAllocation container every time AccountTo is entered.
// 
//    Rev 1.17   Feb 13 2002 16:31:36   FENGYONG
// Add valid account number flag
// 
//    Rev 1.16   Feb 12 2002 10:48:42   FENGYONG
// Add cnd
// 
//    Rev 1.15   Feb 04 2002 13:40:54   FENGYONG
// Add condition and add init accountallocation callls
// 
//    Rev 1.14   31 Dec 2001 12:30:50   KOVACSRO
// bug fix for deleting a trade.
// 
//    Rev 1.13   29 Oct 2001 11:14:36   SMITHDAV
// hasPermission() changes.
// 
//    Rev 1.12   29 Oct 2001 10:22:00   KOVACSRO
// Assign a value for Trade::ProvSales, not to call view 69 anymore.
// 
//    Rev 1.11   18 Oct 2001 14:43:04   KOVACSRO
// Added some logic not to call view 64 and 134 (if ExchRate is set by eCom)
// 
//    Rev 1.10   15 Oct 2001 11:59:04   KOVACSRO
// small change.
// 
//    Rev 1.9   04 Oct 2001 14:59:56   KOVACSRO
// Added SettledFieldsInitialized in order to clarify if these fields were set by eCom.
// 
//    Rev 1.8   03 Oct 2001 15:19:24   KOVACSRO
// Bug fix. If eCom or API sends empty values for settled/unsettled fields, don't set these fields in Trade, MFAccount.
// 
//    Rev 1.7   Aug 27 2001 14:08:48   FENGYONG
// Add UnsettledValue
// 
//    Rev 1.6   Aug 15 2001 12:48:54   FENGYONG
// setfield by true with unformat decimal will lead a memery overload
// 
//    Rev 1.5   10 Aug 2001 13:37:32   KOVACSRO
// Getting SettledValue, SettledUnits, UnsettledUnits as parameters.
// 
//    Rev 1.4   08 Aug 2001 17:06:16   KOVACSRO
// Added UnsettledUnits.
// 
//    Rev 1.3   05 Aug 2001 19:20:04   KOVACSRO
// Added conditions if AccountNum and TrasType are invalid.
// 
//    Rev 1.2   04 Aug 2001 17:37:30   KOVACSRO
// Create an Exchange both for Excahnge and Transfer codes.
// 
//    Rev 1.1   04 Aug 2001 12:47:12   KOVACSRO
// Added FeeCurrency field.
// 
//    Rev 1.0   26 Jul 2001 15:55:24   KOVACSRO
// Initial revision.
 * 
 
// 
*/
//******************************************************************************

