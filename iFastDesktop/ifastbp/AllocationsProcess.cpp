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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AllocationsProcess.cpp
// ^AUTHOR : 
// ^DATE   : 09/18/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AllocationsProcess
//    This class manages the allocations information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "allocationsprocess.hpp"
#include "allocationsprocessincludes.h"

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\tradeacctalloc.hpp>
#include <ifastcbo\tradeacctalloclist.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\rriffundalloclist.hpp>
#include <ifastcbo\rrif_lif_lrif_info.hpp>
#include <ifastcbo\rrif_lif_lrif_infolist.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\sysallocationlist.hpp>
#include <ifastcbo\autotransallocationlist.hpp>
#include <ifastcbo\autoaccttransallocation.hpp>
#include <ifastcbo\autoaccttransallocationlist.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\shralloctypelist.hpp>
#include <ifastcbo\shralloctype.hpp>
#include <ifastcbo\acctalloclist.hpp>
#include <ifastcbo\acctalloc.hpp>
#include <ifastcbo\fundalloclist.hpp>
#include <ifastcbo\defacctalloclist.hpp>
#include <ifastcbo\defacctalloc.hpp>
#include <ifastcbo\deffundalloclist.hpp>
#include <ifastcbo\TradeFundAlloc.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SIMPLE_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SIMPLE_ALLOCATION;
#include <bfproc\concreteprocesscreator.hpp>
//static ConcreteProcessCreator< AllocationsProcess > processCreator( CMD_BPROC_ALLOCATIONS );
static ConcreteProcessCreator< AllocationsProcess > processCreator( CMD_BPROC_SIMPLE_ALLOCATION );

namespace
{
   // Trace literals
   const I_CHAR* const CLASSNAME   = I_( "AllocationsProcess" );
   const I_CHAR* const YES         = I_( "Y" );
   const I_CHAR* const NO          = I_( "N" );

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundToISIN;
   extern CLASS_IMPORT const BFTextFieldId FundToWKN;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId AllocationsAllowed;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId LV_DefaultAllocFundHeading2;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;   
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AllocationsProcess::AllocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pSystematicList( 0 )
, _rpChildGI( 0 )
, _pTradesList(0)
, _pAtAcctTransList(0)
, _pAtFundTransList(0)
, _pSysAllocationList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,                      false );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO,                    false );

   addContainer( IFASTBP_PROC::SHR_ALLOCATIONS_LIST,               true,  BF::NullContainerId,                 true, I_("shareholder_allocation") );
   addContainer( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST,              true,  IFASTBP_PROC::SHR_ALLOCATIONS_LIST,  true, I_("account_allocation") );
   addContainer( IFASTBP_PROC::FUND_ALLOCATIONS_LIST,              true,  IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, true, I_("fund_allocation") ); 

   addContainer( IFASTBP_PROC::SYSTEMATIC_LIST,                    true,  BF::NullContainerId,                 false );
   addContainer( IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST,        true,  IFASTBP_PROC::SYSTEMATIC_LIST,       true );
   addContainer( IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO, false, IFASTBP_PROC::SYSTEMATIC_LIST,       true );

   addContainer( IFASTBP_PROC::AT_SYSTEMATIC_CBO,                  false);
   addContainer( IFASTBP_PROC::AT_ACCT_TRANS_LIST_AS_CBO,          false, IFASTBP_PROC::SYSTEMATIC_LIST,       true );

   addContainer( IFASTBP_PROC::AT_ACCT_TRANS_LIST,                 true,  IFASTBP_PROC::AT_SYSTEMATIC_CBO,     true);
   addContainer( IFASTBP_PROC::AT_FUND_TRANS_LIST,                 true,  IFASTBP_PROC::AT_ACCT_TRANS_LIST,    true);

   //Canadian Market Only 
/*
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
      addContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,  true, BF::NullContainerId,                   true );
      addContainer( IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, true, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true );
   }
*/
  
   addContainer ( IFASTBP_PROC::MFACCOUNT_LIST,
                  true);

   addContainer ( IFASTBP_PROC::TRADES_LIST,                   
                  true, 
                  BF::NullContainerId,
                  false);      //SetAsDefault will be changed, set the field as subclassed
   addContainer ( IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, 
                  true, 
                  IFASTBP_PROC::TRADES_LIST,
                  true);      //to keep AccountAllocationList
   addContainer ( IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST,    
                  true, 
                  IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, 
                  true);

   addFieldDetails( ifds::TransType,        IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::SHR_ALLOCATIONS_LIST );


   addFieldDetails( ifds::AllocPercentage,  IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   addFieldDetails( ifds::TotPercentage,    IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);//Total percentage
   addFieldDetails( ifds::FundGroup,        IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );


   addFieldDetails( ifds::ToFundNumber,     IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::FundCode,         IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::ClassCode,        IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AllocPercentage,  IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::TotPercentage,    IFASTBP_PROC::FUND_ALLOCATIONS_LIST, SUBCLASS_PROCESS);//Total percentage
   addFieldDetails( ifds::SplitComm,        IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
   addFieldDetails( ifds::FELComm,          IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails( ifds::FELCommType,      IFASTBP_PROC::FUND_ALLOCATIONS_LIST);

   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::MFACCOUNT_LIST );
   addFieldDetails( ifds::TaxType,          IFASTBP_PROC::MFACCOUNT_LIST );

   addFieldDetails( ifds::TransType,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Amount,           IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctCurrency, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AmountType,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PACSWPId,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::StatusCode,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SetAsDefault,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransNum,         IFASTBP_PROC::SYSTEMATIC_LIST );


   //SystematicAllocation List
   addFieldDetails( ifds::ToFundNumber,     IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::FundCode,         IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::ClassCode,        IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::Percentage,       IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AllocAmount,      IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::PACSWPId,         IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::AllocAccountNum,  IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );
   addFieldDetails( ifds::SplitComm,        IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST );

   addFieldDetails( ifds::ReplaceAsDefault, IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO );

 /*  //RRIF_LIF_LRIF_INFO_LIST
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
      addFieldDetails( ifds::PlanType,        IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::RIFId,           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::RRIFAmount,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::EffectiveFrom,   IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::SetAsDefault,    IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::AccountNum,      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
      addFieldDetails( ifds::GoodBad,         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );

      //RRIF-LIF-LRIF Allocation List
      addFieldDetails( ifds::ToFundNumber,    IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::FundCode,        IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::ClassCode,       IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::AllocPercentage, IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::TotPercentage,   IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, SUBCLASS_PROCESS);//Total percentage
      addFieldDetails( ifds::TotAmount,       IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, SUBCLASS_PROCESS);//Total amount
      addFieldDetails( ifds::AllocAmount,     IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::Baycom,          IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
      addFieldDetails( ifds::SplitComm,       IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST );
   }
*/
  //Account
   addFieldDetails( ifds::AccountNum,         IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType,            IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Currency,           IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AMSCode,            IFASTBP_PROC::MFACCOUNT_CBO );

   //Shareholder
   addFieldDetails( ifds::ShrNum,             IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupCode,          IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Name1,              IFASTBP_PROC::SHAREHOLDER_CBO );

   //Group fund list
   addFieldDetails( ifds::AllocTaxType,       BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::AllocationType,     BF::NullContainerId,                         SUBCLASS_PROCESS );

   //for transaction allocations
   addFieldDetails( ifds::PendingOrTransHist, BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::TransCode,          BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::TransNum,           BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::TradeDate,          BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::SettleCurrency,     BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::TransactionAmount,  BF::NullContainerId,                         SUBCLASS_PROCESS );
   addFieldDetails( ifds::SystematicKey,      BF::NullContainerId,                         SUBCLASS_PROCESS );

   //Trade List
   addFieldDetails( ifds::TradesTransType,    IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::AccountNum,         IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::AccountTo,          IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::EffectiveDate,      IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::Amount,             IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::AmtType,            IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::SettleCurrency,     IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::SetAsDefault,       IFASTBP_PROC::TRADES_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::GoodBad,            IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::TransNum,           IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::AllocationsAllowed, IFASTBP_PROC::TRADES_LIST, SUBCLASS_PROCESS );


   //Trade Account Allocation List
   addFieldDetails( ifds::AccountNum,         IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST );
   addFieldDetails( ifds::TaxType,            IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AllocPercentage,    IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST );
   addFieldDetails( ifds::AcctType,           IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Name,               IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::XrefNum,            IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AltAccount,         IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotPercentage,      IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::TotAmount,          IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, SUBCLASS_PROCESS );   

   //Trade Fund Allocation List
   addFieldDetails( ifds::FundCode,           IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::ClassCode,          IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::AllocPercentage,    IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::AllocAmount,        IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::ToFundNumber,       IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::Baycom,             IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );//???
   addFieldDetails( ifds::SplitComm,          IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST,   SUBCLASS_PROCESS);
   addFieldDetails( ifds::TotPercentage,      IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST,   SUBCLASS_PROCESS);//Total percentage
   addFieldDetails( ifds::TotAmount,          IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST,   SUBCLASS_PROCESS);//Total amount
   addFieldDetails( ifds::TransNum,           IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::FeeType,           IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );
   addFieldDetails( ifds::FeeRate,           IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST );

   // automatic transfer account level alloaction
   addFieldDetails( ifds::FundCode,           IFASTBP_PROC::AT_ACCT_TRANS_LIST );
   addFieldDetails( ifds::ClassCode,          IFASTBP_PROC::AT_ACCT_TRANS_LIST );
   addFieldDetails( ifds::Percentage,         IFASTBP_PROC::AT_ACCT_TRANS_LIST );
   addFieldDetails( ifds::AllocAmount,        IFASTBP_PROC::AT_ACCT_TRANS_LIST );
   addFieldDetails( ifds::AllocAccountNum,    IFASTBP_PROC::AT_ACCT_TRANS_LIST );

   addFieldDetails( ifds::ReplaceAsDefault,   IFASTBP_PROC::AT_ACCT_TRANS_LIST_AS_CBO );

   addFieldDetails( ifds::EffectiveDate,      IFASTBP_PROC::AT_SYSTEMATIC_CBO );

   // automatic transfer fund level alloaction
   addFieldDetails( ifds::FundCode,           IFASTBP_PROC::AT_FUND_TRANS_LIST );
   addFieldDetails( ifds::ClassCode,          IFASTBP_PROC::AT_FUND_TRANS_LIST );
   addFieldDetails( ifds::Percentage,         IFASTBP_PROC::AT_FUND_TRANS_LIST );
   addFieldDetails( ifds::AllocAmount,        IFASTBP_PROC::AT_FUND_TRANS_LIST );
   addFieldDetails( ifds::ToFundNumber,       IFASTBP_PROC::AT_FUND_TRANS_LIST );
   addFieldDetails( ifds::SplitComm,          IFASTBP_PROC::AT_FUND_TRANS_LIST );
}

//******************************************************************************

AllocationsProcess::~AllocationsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AllocationsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      //Allocation Screen invoking source
      getParameter(ALLOCATIONSPROC::ALLOCATION_TYPE, _dstrAllocationType);
      getParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
      getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAccountNum);
      getParameter(MFCAN_IP_PARAM::TRANS_TYPE, _strTransType);
      getParameter(MFCAN_IP_PARAM::SUB_LIST_KEY, _strAllocationListKey);

      _dstrAccountNum.strip().stripLeading('0');
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MFAccount *pMFAccount = NULL;

      if( dstcWorkSession->getMFAccount( getDataGroupId(), _dstrAccountNum,
         pMFAccount, I_("N"), NULL_STRING, true, true) > WARNING)
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      //get the selected item key if allocation lauched from Systematic, Trade...
      if( _dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME       ||
          _dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER  ||
          _dstrAllocationType == ALLOCATIONSPROC::TRADE_ONE_TIME            ||
          _dstrAllocationType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME)
      {
         //borrow this varible name for Trade Allocation also
         getParameter(MFCAN_IP_PARAM::LIST_KEY, _mainListKey);
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY AllocationsProcess::resetContainers()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "resetContainers" ) );

   _pMFAccount = NULL;
   _pSystematicList = NULL;
   _pShareholder = NULL;
   _pTradesList = NULL;
   //_pShrAllocationsList= NULL;

   //_pAccountAllocationList = NULL;
   //_pFundAllocationList = NULL;
   //_pDefAcctAllocList = NULL;
   //_pDefFundAllocList= NULL;
   _pAtAcctTransList = NULL;
   _pAtFundTransList = NULL;
   _pSysAllocationList = NULL;

   setContainer( IFASTBP_PROC::MFACCOUNT_CBO, NULL );
   setContainer( IFASTBP_PROC::SYSTEMATIC_LIST, NULL );
   setContainer( IFASTBP_PROC::SHAREHOLDER_CBO, NULL );
   setContainer( IFASTBP_PROC::TRADES_LIST, NULL );
   setContainer( IFASTBP_PROC::MFACCOUNT_LIST, NULL );
   setContainer( IFASTBP_PROC::SHR_ALLOCATIONS_LIST, NULL );
   setContainer( IFASTBP_PROC::AT_SYSTEMATIC_CBO, NULL );
 //  setContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, NULL );
  // setContainer( IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, NULL );
   /*setContainer( ALLOCATIONSPROC::GROUP_FUND_LIST, NULL );
   setContainer( ALLOCATIONSPROC::FUND_DETAIL_LIST, NULL );*/


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void AllocationsProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer, 
                                   const BFFieldId& idField, 
                                   const BFDataGroupId& idDataGroup, 
                                   DString &strValueOut, 
                                   bool bFormatted
                                   ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( idContainer == IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST )
   {
      if( (idField == ifds::TaxType) || (idField == ifds::AcctType) || (idField == ifds::Name) || (idField == ifds::XrefNum) || (idField == ifds::AltAccount) )
      {
         DString strAccountNum;
         const_cast< AllocationsProcess * >( this )->getField( rpGICaller, 
                                                               IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, 
                                                               ifds::AccountNum, strAccountNum );
         strAccountNum.strip().stripLeading('0');
         MFAccount *pMFAccount;
         if( strAccountNum != NULL_STRING )
         {
            dstcWorkSession->getMFAccount( getDataGroupId( ), strAccountNum, pMFAccount );
            if( pMFAccount )
            {
               if( idField == ifds::Name )
                  //get first sequenced01account holder name
                  dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, strAccountNum, strValueOut );
               else
                  pMFAccount->getField( idField, strValueOut, getDataGroupId(), bFormatted );
            }
         }
      }
      else
         assert( idField == ifds::TotPercentage || idField == ifds::TotAmount);
      strValueOut.strip();
   }

   if( idContainer == IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST )
   {
      if( idField == ifds::SplitComm )
      {
         TradeFundAllocList* pAllocList = dynamic_cast<TradeFundAllocList*>
                                          ((const_cast< AllocationsProcess * >( this ))->getCBOList(idContainer, idDataGroup));
         if( pAllocList )
            pAllocList->GetSplitCommFlag ( idDataGroup, strValueOut );
         else
            strValueOut = I_("N");
      }
   }


   if( idField == ifds::AllocTaxType )
   {
      DString strAccountNum;
      getParameter( ALLOCATIONSPROC::ACCOUNT_NUM, strAccountNum );
      const_cast< AllocationsProcess * >( this )->getField( rpGICaller, 
                                                            IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, 
                                                            ifds::AccountNum, strAccountNum );
      strAccountNum.strip();

      MFAccount *pMFAccount;
      dstcWorkSession->getMFAccount( getDataGroupId( ), strAccountNum, pMFAccount );
      pMFAccount->getField( ifds::TaxType, strValueOut, BF::HOST, bFormatted );
   }
   else if( idField == ifds::AllocationType )
      strValueOut = _dstrAllocationType;
   else if( idField == ifds::PendingOrTransHist )
      strValueOut = _dstrPendingOrTransHist;
   else if( idField == ifds::TransCode )
      strValueOut = _dstrTransCode;
   else if( idField == ifds::TransNum )
      strValueOut = _dstrTransNum;
   else if( idField == ifds::TradeDate )
      strValueOut = _dstrTradeDate;
   else if( idField == ifds::SettleCurrency )
      strValueOut = _dstrSettleCurrency;
   else if( idField == ifds::TransactionAmount )
      strValueOut = _dstrTransactionAmount;
   else if( idField == ifds::SystematicKey )
      strValueOut = _mainListKey;
   else if( idField == ifds::TotPercentage )
   {
      strValueOut = NULL_STRING;
      assert(idContainer == IFASTBP_PROC::FUND_ALLOCATIONS_LIST ||
             idContainer == IFASTBP_PROC::ACCT_ALLOCATIONS_LIST || 
             idContainer == IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST || 
             idContainer == IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST //|| 
            /* idContainer == IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST*/ );
      AbstractAllocList* pAllocList = dynamic_cast<AbstractAllocList*>
                                      ((const_cast< AllocationsProcess * >( this ))->getCBOList(idContainer, idDataGroup));
      if( pAllocList )
         pAllocList->getTotalPercentage(strValueOut, idDataGroup, bFormatted);
      strValueOut.strip();
   }
   else if( idField == ifds::TotAmount )
   {
      strValueOut = NULL_STRING;
      assert(idContainer == IFASTBP_PROC::FUND_ALLOCATIONS_LIST ||
             idContainer == IFASTBP_PROC::ACCT_ALLOCATIONS_LIST || 
             idContainer == IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST || 
             idContainer == IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST //|| 
             /*idContainer == IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST*/ );
      AbstractAllocList* pAllocList = dynamic_cast<AbstractAllocList*>
                                      ((const_cast< AllocationsProcess * >( this ))->getCBOList(idContainer, idDataGroup));
      if( pAllocList )
         pAllocList->getTotalAmount(strValueOut, idDataGroup, bFormatted);
      strValueOut.strip();
   }
   else if( (idField == ifds::TotPercentage) || (idField == ifds::Amount) || (idField == ifds::AllocAccountNum) ||
            (idField == ifds::TaxType) || (idField == ifds::AcctType) || (idField == ifds::Name) || 
            (idField == ifds::XrefNum) || (idField == ifds::AltAccount) || (idField == ifds::Percentage) ||
            (idField == ifds::AcctPrcnt) )
   {

   }
   else if (idField == ifds::AllocationsAllowed)
   {
      Trade *pTrade = dynamic_cast <Trade*> 
         ( (const_cast< AllocationsProcess * >( this ))->getCBOItem (IFASTBP_PROC::TRADES_LIST, idDataGroup));

      if (pTrade)
      {
         strValueOut = pTrade->areAllocationsAllowed (idDataGroup) ? I_("Y") : I_("N");
      }
   }
}

//******************************************************************************
SEVERITY AllocationsProcess::doSetField( const GenericInterface *rpGICaller, 
                                         const BFContainerId &idContainer, 
                                         const BFFieldId &idField, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString &strValue, 
                                         bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("doSetField"));

   if (idField == ifds::AllocationType)
   {
      _dstrAllocationType = strValue;
   }
   else if (idContainer == IFASTBP_PROC::TRADES_LIST)
   {
      if (idField == ifds::SetAsDefault)
      {
         DString tradeKey = getCurrentListItemKey (this, IFASTBP_PROC::TRADES_LIST);

         if (tradeKey != NULL_STRING)
         {
            BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::TRADES_LIST, idDataGroup);
            if (rpPtr)
            {
               rpPtr->setField (idField, strValue, idDataGroup, bFormatted); 
            }
         }         
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllocationsProcess::doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                                          const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const
{
   SEVERITY sevRtn = NO_CONDITION;
   sevRtn = AbstractProcess::doGetErrors( rpGICaller, idContainer, idField, idDataGroup, conditions );

   return(sevRtn);
}
//******************************************************************************

const BFProperties *AllocationsProcess::doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   const BFProperties * pBFProp = NULL;

   return(pBFProp);
}
//******************************************************************************

E_COMMANDRETURN AllocationsProcess::doProcess()
{  
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {
         setParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
         setParameter(MFCAN_IP_PARAM::TRANS_TYPE, _strTransType);
         setParameter(MFCAN_IP_PARAM::LIST_KEY, _strAllocationListKey);
         rtn = invokeCommand(this, CMD_GUI_SIMPLE_ALLOCATION,
            getProcessType(), isModal(), &_rpChildGI);         
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
   }
   catch( ConditionException &ce )
   {
      MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

void *AllocationsProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   assert(dstcWorkSession);
   try
   {
      if( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST == idContainer )
      {
         { 
            ShrAllocType *pShrAllocation = dynamic_cast< ShrAllocType * >( getCBOItem( IFASTBP_PROC::SHR_ALLOCATIONS_LIST, idDataGroup ) );          
            assert( pShrAllocation );

            DefAcctAllocList* pDefAcctAllocList = NULL;
            pShrAllocation->getAccountAllocationList( pDefAcctAllocList, idDataGroup );
            assert( pDefAcctAllocList );
            ptr = pDefAcctAllocList;
         }
      }
      else if( IFASTBP_PROC::FUND_ALLOCATIONS_LIST == idContainer )
      {
         {
            AcctAlloc *pAcctAllocation = dynamic_cast< AcctAlloc * >(
                                                                    getCBOItem( IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, idDataGroup ) );
            assert( pAcctAllocation );
            DefFundAllocList* pDefFundAllocList = NULL;
            pAcctAllocation->getFundAllocationList( pDefFundAllocList, idDataGroup );
            assert( pDefFundAllocList );
            ptr = pDefFundAllocList;
         }
      }
      else if( IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST == idContainer
               || IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO == idContainer )
      {
         {
            Systematic *pSystematic = dynamic_cast< Systematic * >( getCBOItem(
                                                                              IFASTBP_PROC::SYSTEMATIC_LIST, idDataGroup ) );
            if( !pSystematic )
               assert( 0 );
            pSystematic->getSysAllocationList( _pSysAllocationList );
            if( !_pSysAllocationList )
               assert( 0 );
            ptr = _pSysAllocationList;
         }

      }
      else if( IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST == idContainer )
      {
         BFObjIter iter (*_pTradesList, idDataGroup);

         iter.positionByKey (_mainListKey);
         if( !iter.end())            
         {
            Trade* pTrade = dynamic_cast <Trade*>(iter.getObject());
            if (pTrade)
            {
               TradeAcctAllocList* pTradeAcctAllocList;
               pTrade->getAccountAllocationList (pTradeAcctAllocList, idDataGroup);
               ptr = pTradeAcctAllocList;
            }
         }
      }
      else if( IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST == idContainer )
      {
         TradeAcctAlloc *pAccountAllocation = 
               dynamic_cast<TradeAcctAlloc *> (getCBOItem(IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, idDataGroup));
         if( pAccountAllocation )
         {
            TradeFundAllocList *pTradeFundAllocList;
            pAccountAllocation->getFundAllocationList(pTradeFundAllocList, idDataGroup);
            ptr = pTradeFundAllocList;
         }
      }
 /*     else if( IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST == idContainer )
      {
         {
            RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info *>
                                                      (getCBOItem(IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup));
            if( pRRIF_LIF_LRIF_Info )
            {
               RRIFFundAllocList *pRRIFFundAllocList = NULL;
               pRRIF_LIF_LRIF_Info->getRRIF_LIF_LRIF_AllocList(pRRIFFundAllocList, idDataGroup );
               ptr = pRRIFFundAllocList;
            }
         }
      }
		*/
      else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         {
            if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount )<=WARNING )
               ptr = _pMFAccount;
         }
      }
      else if( IFASTBP_PROC::SYSTEMATIC_LIST == idContainer )
      {
         {
            assert(_dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME ||  _dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER);
            _pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
            if( _pMFAccount )
            {
               if( _pMFAccount->getSystematicList(_pSystematicList, idDataGroup)<=WARNING )
                  ptr = _pSystematicList;
            }
         }
      }
      else if( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         {
            _pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
            if( _pMFAccount )
            {
               DString dstrShareholderNum;
               _pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
               dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
               if( dstcWorkSession->getShareholder( idDataGroup, dstrShareholderNum, _pShareholder )<=WARNING )
                  ptr = _pShareholder;
            }
         }
      }
      else if( IFASTBP_PROC::TRADES_LIST == idContainer )
      {
         {
            assert(_dstrAllocationType == ALLOCATIONSPROC::TRADE_ONE_TIME);
            if( dstcWorkSession->getTradesList(_pTradesList, idDataGroup) <= WARNING )
               ptr = _pTradesList;
         }
      }
      else if( IFASTBP_PROC::MFACCOUNT_LIST == idContainer )
      {
         {
            MFAccountList *pMFAccountList;
            _pShareholder =  dynamic_cast<Shareholder *>(getCBOItem(IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup));
            if( _pShareholder && _pShareholder->getMFAccountList( pMFAccountList, idDataGroup )<=WARNING )
               ptr = pMFAccountList;
         }
      }
      else if( IFASTBP_PROC::SHR_ALLOCATIONS_LIST == idContainer )
      {
         {
            ShrAllocTypeList *pShrAllocationsList = NULL;
            _pShareholder =  dynamic_cast<Shareholder *>(getCBOItem(IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup));
            if( _pShareholder && _pShareholder->getAllocationList(pShrAllocationsList, idDataGroup )<=WARNING )
               ptr = pShrAllocationsList;
         }
      }
      else if( IFASTBP_PROC::AT_SYSTEMATIC_CBO == idContainer )
      {
         {
            assert(_dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER);
            _pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
            if( _pMFAccount )
            {
               if( _pMFAccount->getSystematicList(_pSystematicList, idDataGroup)<=WARNING && _pSystematicList )
               {
                  BFObjIter iterSys( *_pSystematicList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
                  iterSys.positionByKey(_mainListKey);
                  if( !iterSys.end() )
                  {
                     Systematic *pSystematic = dynamic_cast< Systematic * >( iterSys.getObject() );
                     ptr = pSystematic;
                  }
               }
            }
         }
      }
      else if( IFASTBP_PROC::AT_ACCT_TRANS_LIST == idContainer
               || IFASTBP_PROC::AT_ACCT_TRANS_LIST_AS_CBO == idContainer )
      {
         {
            assert(_dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER);
            Systematic *pSystematic = dynamic_cast<Systematic *>(getCBOItem(IFASTBP_PROC::AT_SYSTEMATIC_CBO, idDataGroup));
            if( pSystematic )
               pSystematic->getAtAcctAllocationList(_pAtAcctTransList);
            ptr = _pAtAcctTransList;
         }
      }
      else if( IFASTBP_PROC::AT_FUND_TRANS_LIST == idContainer )
      {
         {
            assert(_dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER);
            AutoAcctTransAllocation* pAcctTransAllocation = dynamic_cast<AutoAcctTransAllocation *>(getCBOItem(IFASTBP_PROC::AT_ACCT_TRANS_LIST, idDataGroup));
            if( pAcctTransAllocation )
            {
               pAcctTransAllocation->getAtAllocationList(_pAtFundTransList);
               ptr = _pAtFundTransList;
            }
         }
      }
      else if( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST == idContainer )
      {
         {
            assert( _dstrAllocationType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME )  ; 
            DString dstrTaxType;
            _pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
            if( _pMFAccount )
            {
               _pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
               dstrTaxType.strip().upperCase();
               bool bIsRif = dstrTaxType == I_( "B" ) || dstrTaxType == I_( "L" ) || 
                             dstrTaxType == I_( "R" ) ||  dstrTaxType == I_( "2" );
               if( bIsRif )
               {
                  if( _pMFAccount->getRRIF_LIF_LRIF_InfoList(_pRRIF_LIF_LRIF_InfoList,idDataGroup)<=WARNING )
                     ptr = _pRRIF_LIF_LRIF_InfoList;
               }
            }
         }

      }
      else
      {
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
// If severity > warning, throw error ??
   return(ptr);
}

//******************************************************************************

void AllocationsProcess::setCurrentListItem( const GenericInterface *rpGICaller,
                                             const BFContainerId& idList, const DString& dstrListItemKey )
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );

   //DString dstrKey( dstrListItemKey );
   AbstractProcess::setCurrentListItem( rpGICaller, idList, dstrListItemKey );

   try
   {
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
   return;
}

//******************************************************************************

bool AllocationsProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_SIMPLE_ALLOCATION );
}

//******************************************************************************

bool AllocationsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      DString dstrNewAccountNum;
      getParameter( ALLOCATIONSPROC::ACCOUNT_NUM, dstrNewAccountNum );
      if( dstrNewAccountNum.strip().stripLeading('0') != _dstrAccountNum )
      {
         _dstrAccountNum = dstrNewAccountNum;
         resetContainers();

         if( isValidModelessInterface( _rpChildGI ) )
         {  // Only if child still exists
            if( !_rpChildGI->refresh( this, NULL ) )
               return(false);
         }
      }
      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         return(_rpChildGI->modelessSetFocus( rpGICaller ));
      }
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(false);
}

//******************************************************************************

bool AllocationsProcess::doRefresh( GenericInterface *rpGICaller,
                                    const I_CHAR* szOriginalCommand )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOREFRESH );

   resetContainers();

   return(AbstractProcess::doRefresh( rpGICaller, szOriginalCommand ));
}

//******************************************************************************

bool AllocationsProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOOK );

   ShrAllocTypeList* pAllocList = dynamic_cast<ShrAllocTypeList*>(
                                                                 getCBOList(IFASTBP_PROC::SHR_ALLOCATIONS_LIST, getDataGroupId()));
   if( pAllocList )
      pAllocList->setAcctAllocFlags(getDataGroupId());
   return(true);
}

//******************************************************************************
void AllocationsProcess::doPostOk ( GenericInterface *rpGICaller, 
                                    bool bSuccessFlag
                                  )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
   const BFDataGroupId& idDataGroup = getDataGroupId();

   if (bSuccessFlag)
   {
      if (_dstrAllocationType == ALLOCATIONSPROC::TRADE_ONE_TIME)
      {
         TradeAcctAlloc* pAccountAllocation = 
            dynamic_cast<TradeAcctAlloc *> (getCBOItem(IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, idDataGroup));

         if (pAccountAllocation)
         {
            TradeFundAllocList *pTradeFundAllocList;
            pAccountAllocation->getFundAllocationList (pTradeFundAllocList, idDataGroup);
            if (pTradeFundAllocList)
            {
               BFObjIter iter (*_pTradesList, idDataGroup);

               iter.positionByKey (_mainListKey);
               
               if (!iter.end())
               {
                  Trade* pTrade = dynamic_cast <Trade*>(iter.getObject());
                  DString transType;

                  pTrade->getField (ifds::TradesTransType, transType, idDataGroup, false);
                  if (pTrade)
                  {
                     BFObjIter iter1 (*pTradeFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

                     DString fundCode,
                        classCode;
                     BFDataGroupId pidDataGroup = idDataGroup.getParent();

                     if (iter1.getNumberOfItemsInList () == 1)
                     {
                        iter1.getObject()->getField (ifds::FundCode, fundCode, idDataGroup, false);
                        iter1.getObject()->getField (ifds::ClassCode, classCode, idDataGroup, false);
                     }
                     if (transType == I_("TR") || transType == I_("XR"))
                     {
                        pTrade->setField (ifds::ToFund, fundCode, pidDataGroup, false, false);
                        pTrade->setField (ifds::ToClass, classCode, pidDataGroup, false, false);
                        if (fundCode.empty() && classCode.empty()) //allocated, blank out other fund fields
                        {
                           pTrade->setField (ifds::ToFundNumber, I_(""), pidDataGroup, false, true);
                           pTrade->setField (ifds::FundToISIN, I_(""), pidDataGroup, false, true);
                           pTrade->setField (ifds::FundToWKN, I_(""), pidDataGroup, false, true);
                        }
                     }
                     else
                     {
                        pTrade->setField (ifds::FromFund, fundCode, pidDataGroup, false, false);
                        pTrade->setField (ifds::FromClass, classCode, pidDataGroup, false, false);
                        if (fundCode.empty() && classCode.empty()) //allocated, blank out other fund fields
                        {
                           pTrade->setField (ifds::FromFundNumber, I_(""), pidDataGroup, false, true);
                           pTrade->setField (ifds::FundISIN, I_(""), pidDataGroup, false, true);
                           pTrade->setField (ifds::FundWKN, I_(""), pidDataGroup, false, true);
                        }
                     }
                     //notify the trans fee list of the change
                     TransFeeList *pTransFeeList = NULL;

                     if ( pTrade->getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING &&
                          pTransFeeList)
                     {
                        pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
                     }
                     
                     DString multiCurrency;

                     DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                     dstcWorkSession->getOption ( ifds::MultiCurrency, 
                                                  multiCurrency, 
                                                  BF::HOST,
                                                  false);
                     if (multiCurrency == I_("N"))
                     {
                        DString fundCode,
                           classCode;

                        if (pTradeFundAllocList)
                        {
                           DString currency;

                           pTradeFundAllocList->getAllocCurrency (currency, idDataGroup);

                           if (pTrade)
                           {
                              //set the settlement currency
                              pTrade->setField (ifds::SettleCurrency, currency, pidDataGroup, false, true);
                           }
                        }
                     }
                     pTrade->setField (ifds::IsAllocationChanged, NULL_STRING, pidDataGroup, false, true, false);
                  } //pTrade
               }
            }
         }         
      }
   }
}

//******************************************************************************
SEVERITY AllocationsProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOVALIDATEALL );

   ShrAllocTypeList* pAllocList = dynamic_cast<ShrAllocTypeList*>(
                                                                 getCBOList(IFASTBP_PROC::SHR_ALLOCATIONS_LIST, idDataGroup));
   if( pAllocList )
      pAllocList->validateAll( idDataGroup );
   if( _dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER )
   {

      _pAtAcctTransList->validateAll(idDataGroup);
      BFObjIter  iterAtAcct(*_pAtAcctTransList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iterAtAcct.end() )
      {
         AutoAcctTransAllocation* pATAcctTransAlloc = dynamic_cast<AutoAcctTransAllocation* >( iterAtAcct.getObject() );
         AutoTransAllocationList* pATTransAllocLst;
         pATAcctTransAlloc->getAtAllocationList(pATTransAllocLst);
         pATTransAllocLst->validateAll(idDataGroup);
         ++iterAtAcct;
      }

   }
   else if( _dstrAllocationType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
   {
      BFObjIter iterSys( *_pSystematicList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iterSys.end() )
      {
         Systematic *pSystematic = dynamic_cast< Systematic * >( iterSys.getObject() );
         if( pSystematic )
         {
            DString dstrStatus;
			pSystematic->getField(ifds::StatusCode, dstrStatus, idDataGroup, false);
			if( dstrStatus == I_( "Y" )   ) 
			{ 
				SysAllocationList *pSysAllocationList = NULL;
				pSystematic->getSysAllocationList( pSysAllocationList );
				if( pSysAllocationList )
					pSysAllocationList->validateAll( idDataGroup );
			}
         }
         ++iterSys;
      }
   }
   else if (_dstrAllocationType == ALLOCATIONSPROC::TRADE_ONE_TIME)
   {
      assert(_pTradesList);
      BFObjIter iter (*_pTradesList, idDataGroup);

      iter.positionByKey (_mainListKey);
      if (!iter.end())            
      {
         Trade* pTrade = dynamic_cast <Trade*>(iter.getObject());
         if (pTrade)
         {
            TradeAcctAllocList* pTradeAcctAllocList;
            if ( pTrade->getAccountAllocationList ( pTradeAcctAllocList, 
                                                    idDataGroup
                                                  ) <= WARNING &&
                 pTradeAcctAllocList
               )
            {
               pTradeAcctAllocList->validateAll (idDataGroup);
            }
         }
      }
   }
/*   else if( _dstrAllocationType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME )
   {

      BFObjIter iter(*_pRRIF_LIF_LRIF_InfoList, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info * >( iter.getObject() );
         DString dstrStatus;

         pRRIF_LIF_LRIF_Info->getField(ifds::GoodBad, dstrStatus, idDataGroup, false);
         if( dstrStatus == I_("Y") )
         {
            RRIFFundAllocList *_pRRIF_LIF_LRIF_AllocList = NULL;
            pRRIF_LIF_LRIF_Info->getRRIF_LIF_LRIF_AllocList(_pRRIF_LIF_LRIF_AllocList, idDataGroup, false );
            if( _pRRIF_LIF_LRIF_AllocList )
               _pRRIF_LIF_LRIF_AllocList->validateAll( idDataGroup );
         }
         ++iter;
      }

   }
*/

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AllocationsProcess::deleteItemFromList(const GenericInterface *rpGICaller, const BFContainerId& idList) 
{
   if( IFASTBP_PROC::AT_ACCT_TRANS_LIST == idList )
   {
      {
         const DString *pFundLevelKey = &(getFirstListItemKey(rpGICaller, IFASTBP_PROC::AT_FUND_TRANS_LIST));
         while( *pFundLevelKey != NULL_STRING )
         {
            deleteItemFromList(rpGICaller, IFASTBP_PROC::AT_FUND_TRANS_LIST );
            pFundLevelKey = &(getCurrentListItemKey(rpGICaller, IFASTBP_PROC::AT_FUND_TRANS_LIST));
         }    

      }
   }
   return(AbstractProcess::deleteItemFromList( rpGICaller, idList ));
}

bool AllocationsProcess::hasFrontEndLoadCommission()
{
   bool retVal = false;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   TradeFundAlloc *pTradeFundAlloc = 
               dynamic_cast<TradeFundAlloc*> (getCBOItem(IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST , idDataGroup));
   if(pTradeFundAlloc)
   {
      retVal = pTradeFundAlloc->hasPurchExchgFrontEndLoadCommission(getDataGroupId());
   }
   return retVal;
}


//******************************************************************************
//              Private Methods
//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationsProcess.cpp-arc  $
 * 
 *    Rev 1.93   Apr 16 2012 23:17:06   popescu
 * 2901148 - Gurantee Flag Override
 * 
 *    Rev 1.92   May 05 2010 16:58:42   popescu
 * RESP / QESI Gap validation on bene alloc was triggered for transfers..
 * 
 *    Rev 1.91   16 Dec 2008 09:33:50   kovacsro
 * PET22486 - FN03 - RESP Grant Commission - code review
 * 
 *    Rev 1.90   Dec 11 2008 09:24:54   sopitwek
 * PET22486 - FN03 - RESP Grant Commission
 * 
 *    Rev 1.89   Nov 17 2005 14:30:36   porteanm
 * Incident 452849 - Don't validate allocations for an inactive Systematic.
 * 
 *    Rev 1.88   Nov 17 2005 14:08:22   porteanm
 * Incident 452849 - Don't validate allocations for an inactive Systematic.
 * 
 *    Rev 1.87   Oct 11 2005 15:53:38   popescu
 * Incident #424950 - fixed crash for allocations, when user cancels the screen out for full exchanges; removed the 'updatable' flag for worksessiontradeslist container, this will not trigger a reset - which caused the crash; field 'SetAsDefault' has been subclassed; it's an updatable trade field on the one-time-trade allocations screen
 * 
 *    Rev 1.86   May 16 2005 10:44:54   popescu
 * PET 1117/08, the iterator on the allocation list should not count the deleted objects; when a pending trade gets modified and user  deletes the allocations (to 100%) the fund fields remained not populated.
 * 
 *    Rev 1.85   Jan 19 2005 16:41:06   popescu
 * PTS 10038121, fixed display of acquisition fee for allocated trades
 * 
 *    Rev 1.84   Jan 12 2005 15:43:44   popescu
 * PTS 10037793, set the fund fields without triggering 'doApplyRelated' changes if no change in value
 * 
 *    Rev 1.83   Dec 08 2004 21:07:40   popescu
 * PET 1117/06, fixes
 * 
 *    Rev 1.82   Nov 30 2004 20:09:36   popescu
 * PET 1117/06
 * 
 *    Rev 1.81   Nov 07 2004 14:05:32   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.80   Sep 03 2003 17:16:02   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.79   Sep 01 2003 21:21:08   popescu
 * PET 809 FN 02, CIBC Multi fund enhancement
 * 
 *    Rev 1.78   Aug 17 2003 12:46:30   popescu
 * set the selection on the allocation list based on the alocation item selected in Trade dialog
 * 
 *    Rev 1.77   Aug 15 2003 15:21:40   HSUCHIN
 * sync up with 1.75.1.0
 * 
 *    Rev 1.76   Aug 15 2003 15:15:32   HSUCHIN
 * added AMSCode to field details
 * 
 *    Rev 1.75   Jun 09 2003 14:52:00   YINGBAOL
 * remove RRIF allocation for allocation screen
 * 
 *    Rev 1.74   May 27 2003 18:28:52   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.73   Apr 02 2003 14:03:08   PURDYECH
 * Cleaned up obsolete code.
 * 
 *    Rev 1.72   Mar 21 2003 17:35:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.71   Jan 23 2003 16:57:50   KOVACSRO
 * Fixed validation for account number (it was not working for NASU since version 1.68)
 * 
 *    Rev 1.70   Jan 12 2003 18:30:48   KOVACSRO
 * Added FundGroup to Account allocation container
 * 
 *    Rev 1.69   Dec 06 2002 10:56:02   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.68   Nov 29 2002 15:45:38   ZHANGCEL
 * Synced up to 1.67
 * 
 *    Rev 1.67   Oct 09 2002 23:53:02   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.66   Sep 04 2002 13:44:54   KOVACSRO
 * Fixed RRIFAmount display.
 * 
 *    Rev 1.65   Aug 29 2002 16:42:34   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.64   Aug 29 2002 12:54:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.63   Aug 19 2002 15:25:24   KOVACSRO
 * bug fixed in doValidateAll for RRIF allocations.
 * 
 *    Rev 1.62   Aug 06 2002 09:58:06   KOVACSRO
 * Release 48. Converted RRIF allocations.
 * 
 *    Rev 1.61   Jul 29 2002 16:30:10   YINGBAOL
 * make Allocation not updateable
 * 
 *    Rev 1.60   Jul 18 2002 17:18:46   KOVACSRO
 * getting/setting the transaction type.
 * 
 *    Rev 1.59   Jun 03 2002 16:55:16   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.58   22 May 2002 22:22:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.57   08 May 2002 16:43:58   KOVACSRO
 * More implementation for new allocation design.
 * 
 *    Rev 1.56   29 Apr 2002 16:12:06   KOVACSRO
 * new trade allocations.
 * 
 *    Rev 1.55   22 Apr 2002 17:04:30   KOVACSRO
 * some code cleanup.
 * 
 *    Rev 1.54   22 Apr 2002 10:01:18   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.53   27 Mar 2002 19:54:34   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.52   05 Mar 2002 11:48:40   KOVACSRO
 * Added AllocationsAllowed field.
 * 
 *    Rev 1.51   25 Feb 2002 17:02:20   KOVACSRO
 * check AccountAllocationList pointer if NULL.
 * 
 *    Rev 1.50   Dec 14 2001 10:07:28   FENGYONG
 * Add api support
 * 
 *    Rev 1.49   Oct 16 2001 11:43:30   YINGBAOL
 * fix crash due to NULL Pointer
 * 
 *    Rev 1.48   15 Jun 2001 11:40:32   KOVACSRO
 * checking No of items in list before calling getCBOItem.
 * 
 *    Rev 1.47   13 Jun 2001 09:50:20   KOVACSRO
 * Added dummy field TRADE_ALLOC_AMOUNT.
 * 
 *    Rev 1.46   15 May 2001 15:38:18   YINGZ
 * data group id clean up
 * 
 *    Rev 1.45   11 May 2001 16:33:34   YINGZ
 * code sync up
 * 
 *    Rev 1.44   Apr 16 2001 10:54:54   YINGBAOL
 * check status
 * 
 *    Rev 1.43   08 Apr 2001 09:06:58   HSUCHIN
 * changed splitcomm flag to subclass_process for One-time trade.  Fixed bug when there is no Fund Allocation.
 * 
 *    Rev 1.42   03 Apr 2001 20:07:44   HSUCHIN
 * added splitcomm and transnum to field details
 * 
 *    Rev 1.41   01 Apr 2001 12:49:22   HSUCHIN
 * added transnum to the Systematic List
 * 
 *    Rev 1.40   Mar 30 2001 16:49:44   ZHANGCEL
 * Added TransNum in TradeList
 * 
 *    Rev 1.39   Mar 29 2001 15:38:10   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.38   16 Mar 2001 16:42:06   KOVACSRO
 * Field name changes (AccountAllocation)
 * 
 *    Rev 1.37   15 Mar 2001 10:57:36   KOVACSRO
 * Added some fields; modified doValidateAll to work for AccountAllocations.
 * 
 *    Rev 1.36   10 Mar 2001 17:11:40   KOVACSRO
 * Modified for Trade Account Allocations.
 * 
 *    Rev 1.35   01 Mar 2001 16:46:10   KOVACSRO
 * Added a new container TRADE_ACCOUNT_ALLOCATION_LIST
 * 
 *    Rev 1.34   27 Feb 2001 10:31:16   KOVACSRO
 * Modified to work with AccountAllocationList (not working for Transfer, yet)
 * 
 *    Rev 1.33   22 Feb 2001 14:38:48   KOVACSRO
 * Changed TradeAllocation into FundAllocation.
 * 
 *    Rev 1.32   Feb 12 2001 14:52:28   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.31   Feb 06 2001 14:51:38   KOVACSRO
 * Changed TradesList into WorksessionTradesList.
 * 
 *    Rev 1.30   Jan 08 2001 10:13:58   ZHANGCEL
 * Synchronized to C2/C3: getData using idDataGroup rather than BR::Host: fix NASU flow problem
 * 
 *    Rev 1.29   Jan 05 2001 13:00:16   DINACORN
 * Modified setContainers() method
 * 
 *    Rev 1.28   15 Dec 2000 12:43:20   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.27   Nov 09 2000 16:26:34   ZHANGCEL
 * Added AccountNum field in Syatematic list
 * 
 *    Rev 1.26   Nov 02 2000 14:11:30   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.25   Oct 27 2000 17:35:48   HUANGSHA
 * change the Datagroup of getting allocation list
 * 
 *    Rev 1.24   Oct 18 2000 11:58:40   YINGBAOL
 * fix RRIF ALLOCATION crash
 * 
 *    Rev 1.23   Oct 17 2000 15:00:24   YINGBAOL
 * add validate all  logic for RIF_LIF
 * 
 *    Rev 1.22   Sep 29 2000 13:26:02   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.21   Sep 13 2000 17:02:36   ZHANGCEL
 * Added code for RRIF_LIF_LRIF_Alloc stuffs
 * 
 *    Rev 1.20   Sep 06 2000 09:48:08   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.19   Sep 01 2000 14:38:00   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.18   Aug 28 2000 09:57:54   ZHANGCEL
 * Fund Number problems
 * 
 *    Rev 1.17   Aug 11 2000 14:14:08   PETOLESC
 * Added FundCodeNumber field.
 * 
 *    Rev 1.16   Aug 02 2000 15:31:58   BUZILA
 * "locale" changes
 * 
 *    Rev 1.15   Jun 27 2000 10:41:38   HUANGSHA
 * Bug fix
 * 
 *    Rev 1.14   Jun 14 2000 15:20:56   YINGZ
 * force default allocation update when open/refresh dlg
 * 
 *    Rev 1.13   May 31 2000 17:38:22   HUANGSHA
 * TradeAlloclist ValidateAll only apply for the selected account number
 * 
 *    Rev 1.12   May 19 2000 17:12:40   HUANGSHA
 * Removed the Market Conditions for AT
 * 
 *    Rev 1.11   May 17 2000 14:59:52   YINGBAOL
 * check tax type for RIFLIF Allocation
 * 
 *    Rev 1.10   May 02 2000 10:01:48   HUANGSHA
 * check for testing
 * 
 *    Rev 1.9   May 01 2000 09:42:16   YINGBAOL
 * Automatic transfer allocation added
 * 
 *    Rev 1.8   Apr 17 2000 19:08:46   HUANGSHA
 * changed setcontainer param for TradeAllocationList
 * 
 *    Rev 1.7   Apr 17 2000 17:19:06   HUANGSHA
 * check in
 * 
 *    Rev 1.6   Apr 17 2000 14:45:24   HUANGSHA
 * Added the routine SetCurrentListItem
 * 
 *    Rev 1.5   Apr 14 2000 18:16:02   HUANGSHA
 * checked in for testing
 * 
 *    Rev 1.4   Apr 10 2000 12:30:32   HUANGSHA
 * Added TradeAllocations processing routines
 * 
 *    Rev 1.3   Mar 24 2000 10:34:54   DT24433
 * removed commented substitute lists and unused header, also changed doModelessSetFocus to only send refresh to child if data change
 * 
 *    Rev 1.2   Mar 23 2000 17:41:26   YINGBAOL
 * change
 * 
 *    Rev 1.1   Mar 20 2000 16:39:32   HSUCHIN
 * check in for Yingbao
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.34   Feb 03 2000 12:01:52   PRAGERYA
// Some fixes
// 
//    Rev 1.33   Feb 01 2000 13:02:16   PRAGERYA
// For Winnie
// 
//    Rev 1.32   Jan 31 2000 12:05:46   PRAGERYA
// For Release
// 
//    Rev 1.31   Jan 27 2000 12:13:00   PRAGERYA
// Some fixes
// 
//    Rev 1.30   Jan 26 2000 19:41:44   PRAGERYA
// For release
// 
//    Rev 1.29   Jan 24 2000 18:11:16   PRAGERYA
// Fixes
// 
//    Rev 1.28   Jan 21 2000 13:02:24   PRAGERYA
// Latest fixes
// 
//    Rev 1.27   Jan 18 2000 18:09:52   PRAGERYA
// For release
// 
//    Rev 1.26   Jan 14 2000 17:56:54   PRAGERYA
// Bug fix
// 
//    Rev 1.25   Jan 14 2000 16:22:28   PRAGERYA
// For Jerry
// 
//    Rev 1.24   Jan 13 2000 14:15:36   PRAGERYA
// Bug fixes
// 
//    Rev 1.23   Jan 11 2000 18:01:00   PRAGERYA
// Bugs fixed
// 
//    Rev 1.22   Jan 10 2000 09:48:20   PRAGERYA
// Again...
// 
//    Rev 1.21   Jan 09 2000 16:39:10   PRAGERYA
// Made compilable!
// 
//    Rev 1.20   Dec 24 1999 17:07:48   PRAGERYA
// For internal release
// 
//    Rev 1.19   Dec 22 1999 11:20:14   PRAGERYA
// For Jerry
// 
//    Rev 1.18   Dec 13 1999 12:17:50   PRAGERYA
// Yet another check-in for Jerry
// 
//    Rev 1.17   Dec 09 1999 10:50:46   PRAGERYA
// Another check-in for Jerry
// 
//    Rev 1.16   Dec 07 1999 11:42:12   PRAGERYA
// Check in for Jerry
// 
//    Rev 1.15   Dec 01 1999 14:33:42   PRAGERYA
// Check-in for release
// 
//    Rev 1.14   Nov 25 1999 15:32:08   PRAGERYA
// c
// 
//    Rev 1.13   Nov 18 1999 16:55:10   PRAGERYA
// This is the version developed on the premises that (1) Total amount is updatable, and (2) Pending transaction allocations are updatable. 
// According to Mike Metzger's clarifications, both of these assumtions are wrong. Pending transactions are not updatable just like Transaction History ones. Total Amount is also not updatable. If it is zero, the Fund Amount edit box should be disabled, and the value in it set to zero.
// 
//    Rev 1.12   Nov 18 1999 13:47:30   PRAGERYA
// Coding for Allocations, Incr2
// 
//    Rev 1.11   Nov 15 1999 15:56:58   PRAGERYA
// Incr2 partial functionality
// 
//    Rev 1.10   Nov 01 1999 18:17:08   DT24433
// removed doOk/doCancel
 * 
 *
 */
