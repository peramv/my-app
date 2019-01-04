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
// ^FILE   : SplitCommissionsProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SplitCommissionsProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "splitcommissionsprocess.hpp"
#include "splitcommissionsprocessincludes.h"
//cbo level
#include <ifastcbo\accounttradeslist.hpp>
#include <ifastcbo\autoaccttransallocation.hpp>
#include <ifastcbo\autoaccttransallocationlist.hpp>
#include <ifastcbo\autotransallocation.hpp>
#include <ifastcbo\autotransallocationlist.hpp>
#include <ifastcbo\funddetail.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundtolist.hpp>
#include <ifastcbo\matchtransferlist.hpp>
#include <ifastcbo\matchtransferdetails.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\sysallocation.hpp>
#include <ifastcbo\sysallocationlist.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include <ifastcbo\splitcommission.hpp>
#include <ifastcbo\splitcommissionlist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\tradeacctalloc.hpp>
#include <ifastcbo\tradeacctalloclist.hpp>
#include <ifastcbo\tradefundalloc.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SPLITCOMMISSION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SplitCommissionsProcess > processCreator(CMD_BPROC_SPLITCOMMISSION);

namespace
{
    const DString EMPTY_STRING;

    const I_CHAR *CLASSNAME             = I_("SplitCommissionsProcess");
    const I_CHAR * const BACKENDLOAD    = I_("BEL");
    const I_CHAR * const FRONTENDLOAD   = I_("FEL");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace SPLITCOMM
{
   //params
   const I_CHAR * const ACCOUNT_NUM                     = I_("AccountNum");
   const I_CHAR * const CALLER                          = I_("Caller");

   //this param will contain the key the identifies top level objects, i.e. Trade
   const I_CHAR * const MAIN_LIST_KEY                   = I_("MainListKey");

   //this param will be used to set the selection on the current selection from the parent
   //alocation lists
   const I_CHAR * const ALLOCATION_LIST_KEY             = I_("AllocationListKey");
   const I_CHAR * const SPLIT_COMM_LIST_KEY             = I_("SplitCommListKey");
   const I_CHAR * const TRANSACTION_TYPE_DESC           = I_("TransactionTypeDescription");
   const I_CHAR * const TRANSACTION_NUMBER              = I_("TransactionNumber");
   const I_CHAR * const MATCH_TRANSACTION_ID            = I_("MatchTransactionId");

   //possible callers
   const I_CHAR * const MATCH_TRANSFER                  = I_("Match_Transfer");

   //const I_CHAR * const SYSTEMATIC                    = I_("Systematic");
   const I_CHAR * const SYSTEMATIC_ALLOCATION           = I_("Systematic_Allocation");
   const I_CHAR * const SYSTEMATIC_ATALLOCATION         = I_("Systematic_ATAllocation");
   const I_CHAR * const TRADE                           = I_("Trade");
   const I_CHAR * const TRADE_ALLOCATION                = I_("Trade_Allocation");
   const I_CHAR * const TRANSACTION_HISTORY             = I_("Transaction_History");
   const I_CHAR * const TRANSACTION_PENDING             = I_("Transaction_Pending");
   const I_CHAR * const TRANSACTION_HISTORY_ALLOCATION  = I_("Transaction_HAllocation");
   const I_CHAR * const TRANSACTION_PENDING_ALLOCATION  = I_("Transaction_PAllocation");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFDecimalFieldId Fee;
   extern CLASS_IMPORT const BFDecimalFieldId FeeTo;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId TfrAcct;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId ToFund;
   extern CLASS_IMPORT const BFTextFieldId ToClass;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId TfrFund;
   extern CLASS_IMPORT const BFTextFieldId TfrClass;
   extern CLASS_IMPORT const BFTextFieldId Allocation;
   extern CLASS_IMPORT const BFTextFieldId SplitCommissionDetailsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
}   

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT_2;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_2;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}
namespace FEES
{
   extern CLASS_IMPORT const I_CHAR * ACQUISITION;
   extern CLASS_IMPORT const I_CHAR * XFER_OUT;
   extern CLASS_IMPORT const I_CHAR * XFER_IN;
   extern CLASS_IMPORT const I_CHAR * REDEMPTION;
}

//******************************************************************************
SplitCommissionsProcess::SplitCommissionsProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand) : AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_pMFAccount(NULL),
_pSplitCommissionList(NULL),
_pFundAllocationList(NULL), 
_pTransactionList(NULL),
_pSysAllocationList(NULL),
_pAutoTransAllocationList(NULL),
_pMatchTransferList(NULL),
_pTrade(NULL),
_pSystematic(NULL),
_dstrAccountNum(NULL_STRING),
_dstrMainListKey(NULL_STRING),
_dstrCaller(NULL_STRING),
_dstrTransactionNumber(NULL_STRING),
_dstrTransactionTypeDesc(NULL_STRING),
_dstrMatchTransactionId(NULL_STRING),
_dstrCurrentKeyInParentList(NULL_STRING),
_dstrAllocationListKey(NULL_STRING),
_dstrSplitCommListKey (NULL_STRING)
{
   //this is the container for the match transfer list
   addContainer(IFASTBP_PROC::MATCH_TRANSFER_LIST, true, BF::NullContainerId, false, 
      I_("Match_Transfer_List"));
   //this is the container for the systematic allocation list
   addContainer(IFASTBP_PROC::SYS_ALLOCATION_LIST, true, BF::NullContainerId, false, 
      I_("Systematic_Allocation"));
   //this is the container for the systematic auto transfer allocation list
   addContainer(IFASTBP_PROC::SYS_ATALLOCATION_LIST, true, BF::NullContainerId, false, 
      I_("Systematic_AutoTransfer_Allocation"));
   //this is the container for the transaction history list
   addContainer(IFASTBP_PROC::TRANSACTION_HISTORY_LIST, true, BF::NullContainerId, false, 
      I_("Transaction_Hist"));
   //this is the container for TradeFundAllocationList
   addContainer(IFASTBP_PROC::FUND_ALLOCATION_LIST, true, BF::NullContainerId, false, 
      I_("Trade_Fund_Alloc"));
   //this is the container the split commission list
   addContainer(IFASTBP_PROC::SPLIT_COMMISSION_LIST, true, BF::NullContainerId, true, 
      I_("Split_Commission"));

   addSubstituteList(ifds::SplitCommissionDetailsHeadingSet);

   //the match transfer list fields
   addFieldDetails(ifds::rxFundCode, IFASTBP_PROC::MATCH_TRANSFER_LIST);
   addFieldDetails(ifds::rxClassCode, IFASTBP_PROC::MATCH_TRANSFER_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::MATCH_TRANSFER_LIST, SUBCLASS_PROCESS);
   //addFieldDetails(ifds::Amount, IFASTBP_PROC::MATCH_TRANSFER_LIST);      
   addFieldDetails(ifds::GrossAmt, IFASTBP_PROC::MATCH_TRANSFER_LIST);
   //addFieldDetails(ifds::NetAmt, IFASTBP_PROC::MATCH_TRANSFER_LIST);
   addFieldDetails(ifds::SettleCurrency, IFASTBP_PROC::MATCH_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::SplitComm, IFASTBP_PROC::MATCH_TRANSFER_LIST);
   addFieldDetails(TOTAL_PERCENT, IFASTBP_PROC::MATCH_TRANSFER_LIST, SUBCLASS_PROCESS, I_("Percent"));

   //the systematic allocation list fields
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::SYS_ALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::SYS_ALLOCATION_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::SYS_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::Percentage, IFASTBP_PROC::SYS_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmount, IFASTBP_PROC::SYS_ALLOCATION_LIST);
   addFieldDetails(ifds::SettleCurrency, IFASTBP_PROC::SYS_ALLOCATION_LIST);
   addFieldDetails(ifds::SplitComm, IFASTBP_PROC::SYS_ALLOCATION_LIST);         
   addFieldDetails(TOTAL_PERCENT, IFASTBP_PROC::SYS_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(TOTAL_AMOUNT, IFASTBP_PROC::SYS_ALLOCATION_LIST, SUBCLASS_PROCESS);

   //the autotransfer allocation list fields
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::SYS_ATALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::SYS_ATALLOCATION_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::SYS_ATALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::Percentage, IFASTBP_PROC::SYS_ATALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmount, IFASTBP_PROC::SYS_ATALLOCATION_LIST);
   addFieldDetails(ifds::SettleCurrency, IFASTBP_PROC::SYS_ATALLOCATION_LIST);
   addFieldDetails(ifds::SplitComm, IFASTBP_PROC::SYS_ATALLOCATION_LIST);         
   addFieldDetails(TOTAL_PERCENT, IFASTBP_PROC::SYS_ATALLOCATION_LIST, SUBCLASS_PROCESS) ;
   addFieldDetails(TOTAL_AMOUNT, IFASTBP_PROC::SYS_ATALLOCATION_LIST, SUBCLASS_PROCESS);

   //the transaction history list fields
   addFieldDetails(ifds::rxFundCode, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);
   addFieldDetails(ifds::rxClassCode, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, SUBCLASS_PROCESS);
   //addFieldDetails(ifds::Amount, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);      
   addFieldDetails(ifds::GrossAmt, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);
   //addFieldDetails(ifds::NetAmt, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);
   addFieldDetails(ifds::SettleCurrency, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::SplitComm, IFASTBP_PROC::TRANSACTION_HISTORY_LIST);
   addFieldDetails(TOTAL_PERCENT, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, SUBCLASS_PROCESS, I_("Percent"));

   //the trade fund allocation fields
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocPercentage, IFASTBP_PROC::FUND_ALLOCATION_LIST) ;
   addFieldDetails(ifds::AllocAmount, IFASTBP_PROC::FUND_ALLOCATION_LIST);      
   addFieldDetails(ifds::SettleCurrency, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::SplitComm, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(TOTAL_AMOUNT, IFASTBP_PROC::FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(TOTAL_PERCENT, IFASTBP_PROC::FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);

   //the split commission list fields   
   addFieldDetails(ifds::CommEntType, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommEntTypeDesc, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommEntCode, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommPrcnt, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommAmount, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::Currency, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::TradesPayType, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::Fixed, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::GrossOrNet, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::BrokerCode, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::BranchCode, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::SlsrepCode, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommEntName, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::BrokerName, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::BranchName, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::SlsrepName, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   addFieldDetails(ifds::CommRate, IFASTBP_PROC::SPLIT_COMMISSION_LIST);
   //calculated fields
   addFieldDetails(SPLIT_RATE_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(SPLIT_PERCENT_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(SPLIT_AMOUNT_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(RENUNCIATION_AMOUNT, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   addFieldDetails (FEE_TYPE, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   addFieldDetails (ifds::RDRAdvice, IFASTBP_PROC::SPLIT_COMMISSION_LIST, SUBCLASS_PROCESS);
   
}

//******************************************************************************
SplitCommissionsProcess::~SplitCommissionsProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
}

//******************************************************************************
SEVERITY SplitCommissionsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   getParameter(SPLITCOMM::ACCOUNT_NUM, _dstrAccountNum);
   _dstrAccountNum.strip().stripLeading('0');
   getParameter(SPLITCOMM::CALLER, _dstrCaller);
   getParameter(SPLITCOMM::MAIN_LIST_KEY, _dstrMainListKey);
   getParameter(SPLITCOMM::TRANSACTION_NUMBER, _dstrTransactionNumber);
   getParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, _dstrTransactionTypeDesc);
   getParameter(SPLITCOMM::MATCH_TRANSACTION_ID, _dstrMatchTransactionId);
   getParameter(SPLITCOMM::ALLOCATION_LIST_KEY, _dstrAllocationListKey);
   getParameter(SPLITCOMM::SPLIT_COMM_LIST_KEY, _dstrSplitCommListKey);
   getParameter(I_("FeeType"), _dstrFeeType);

   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   //make sure that we get a valid account
   return pDSTCWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, _pMFAccount);
}

//******************************************************************************
E_COMMANDRETURN SplitCommissionsProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if(isXMLAPIContext())
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         //the account should be available already
         //assert(_pMFAccount);
         setParameter(SPLITCOMM::CALLER, _dstrCaller);
         setParameter(SPLITCOMM::TRANSACTION_NUMBER, _dstrTransactionNumber);
         setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, _dstrTransactionTypeDesc);
         setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, _dstrAllocationListKey);
         setParameter(SPLITCOMM::SPLIT_COMM_LIST_KEY, _dstrSplitCommListKey);
		 setParameter(I_("FeeType"), _dstrFeeType);

         rtn = invokeCommand( this, 
                              CMD_GUI_SPLITCOMMISSION, getProcessType(), 
                              true, 
                              &_rpChildGI
                            );
      }
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(rtn);
}

//******************************************************************************
void SplitCommissionsProcess::doGetField ( const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer, 
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup, 
                                           DString &strValueOut,
                                           bool bFormatted
                                         ) const
{
   //the name of the fund fields for the majority of containers
   BFFieldId idFundCode = ifds::FundCode;
   BFFieldId idClassCode = ifds::ClassCode;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   strValueOut = NULL_STRING;
   if (idContainer == IFASTBP_PROC::SPLIT_COMMISSION_LIST)
   {
      if(_pSplitCommissionList)
      {
         if (idField == SPLIT_RATE_TOTAL)
         {
            _pSplitCommissionList->getSplitTotalRate(strValueOut, idDataGroup);
         }
         else if (idField == SPLIT_PERCENT_TOTAL)
         {
            _pSplitCommissionList->getSplitTotalPercent(strValueOut, idDataGroup);
         }
         else if (idField == SPLIT_AMOUNT_TOTAL)
         {
            _pSplitCommissionList->getSplitTotalAmount(strValueOut, idDataGroup);
         }
         else if (idField == RENUNCIATION_AMOUNT)
         {
            _pSplitCommissionList->getRenunciationAmount(strValueOut, idDataGroup);
         }
		 else if (idField == FEE_TYPE)
         {
			 _pSplitCommissionList->getField (ifds::FeeType, strValueOut, idDataGroup);
         }
		 else if (idField == ifds::RDRAdvice)
         {
			 _pSplitCommissionList->getField (ifds::RDRAdvice, strValueOut, idDataGroup);
         }
      }
   } 
   else if (idContainer == IFASTBP_PROC::FUND_ALLOCATION_LIST)
   {
      if (_pFundAllocationList)
      {
         if (idField == TOTAL_PERCENT)
         {
            _pFundAllocationList->getTotalPercentage(strValueOut, idDataGroup, bFormatted);
         }
         else if(idField == TOTAL_AMOUNT)
         {
            _pFundAllocationList->getTotalAmount(strValueOut, idDataGroup, bFormatted);
         }      
      }
   }
   else if (idContainer == IFASTBP_PROC::SYS_ALLOCATION_LIST)
   {
      if (_pSysAllocationList)
      {
         if (idField == TOTAL_PERCENT)
         {
            _pSysAllocationList->getTotal(ifds::Percentage, strValueOut, idDataGroup);
         }
         else if(idField == TOTAL_AMOUNT)
         {
            _pSysAllocationList->getTotal(ifds::AllocAmount, strValueOut, idDataGroup);
         }      
      }
   }
   else if (idContainer == IFASTBP_PROC::SYS_ATALLOCATION_LIST)
   {
      if (_pAutoTransAllocationList)
      {
         if (idField == TOTAL_PERCENT)
         {
            _pAutoTransAllocationList->getTotal(ifds::Percentage, strValueOut, idDataGroup);
         }
         else if(idField == TOTAL_AMOUNT)
         {
            _pAutoTransAllocationList->getTotal(ifds::AllocAmount, strValueOut, idDataGroup);
         }      
      }
   }
   //lucky match of the names of the fields for these two lists (!!)
   else if (idContainer == IFASTBP_PROC::TRANSACTION_HISTORY_LIST || 
      idContainer == IFASTBP_PROC::MATCH_TRANSFER_LIST)
   {
      //the name of the fund fields for this container
      idFundCode = ifds::rxFundCode;
      idClassCode = ifds::rxClassCode;
      if (idField == TOTAL_PERCENT)
      {
         strValueOut = DSTCommonFunctions::doubleToDString(ifds::Percentage, 100.0);
      } 
      else if (idField == ifds::SettleCurrency)
      {
         DString dstrFundCode, dstrClassCode;
         FundDetailList *pFundDetailList = NULL;

         const_cast <SplitCommissionsProcess*> (this)->getField(rpGICaller, 
            idContainer, idFundCode, dstrFundCode, false);
         const_cast <SplitCommissionsProcess*> (this)->getField(rpGICaller, 
            idContainer, idClassCode, dstrClassCode, false);
         pDSTCWorkSession->getMgmtCo().getFundDetailList(pFundDetailList);
         if (pFundDetailList)
         {
            pFundDetailList->getField(dstrFundCode, dstrClassCode, 
               ifds::Currency, strValueOut, idDataGroup, bFormatted);
         }
      }
   }
   if (idField == ifds::Baycom) //get the fund number
   {
      DString dstrFundCode, dstrClassCode;

      const_cast <SplitCommissionsProcess*> (this)->getField(rpGICaller, idContainer, 
         idFundCode, dstrFundCode, false);
      const_cast <SplitCommissionsProcess*> (this)->getField(rpGICaller, idContainer, 
         idClassCode, dstrClassCode, false);
      //get the fund number
      pDSTCWorkSession->GetFundNumber(dstrFundCode, dstrClassCode, strValueOut);
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool SplitCommissionsProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_SPLITCOMMISSION;
}

//******************************************************************************
const DString& SplitCommissionsProcess::getFirstListItemKey(
   const GenericInterface *rpGICaller, 
   const BFContainerId& idList)
{  
   TRACE_METHOD(CLASSNAME, GETFIRSTLISTITEMKEY);

   //we want the same item (only one) for Transaction History Split Commission
   if (idList == IFASTBP_PROC::TRANSACTION_HISTORY_LIST)
   {
      AbstractProcess::setCurrentListItem(rpGICaller, idList, _dstrMainListKey);
      return(_dstrMainListKey);
   } 
   return(AbstractProcess::getFirstListItemKey(rpGICaller, idList));
}

//******************************************************************************
const DString& SplitCommissionsProcess::getNextListItemKey(
   const GenericInterface *rpGICaller,
   const BFContainerId& idList)
{
   //we only want one item for Transaction History Split Commission
   if (idList == IFASTBP_PROC::TRANSACTION_HISTORY_LIST)
   {
      return(EMPTY_STRING);
   }
   return(AbstractProcess::getNextListItemKey(rpGICaller, idList));
}

//******************************************************************************
void SplitCommissionsProcess::setCurrentListItem(
   const GenericInterface *rpGICaller, const BFContainerId& idList,
   const DString& strListItemKey)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM);
   
   //if we are not in the split commision list, we need to determine the current
   //split commission list parent object; also get the split commission list 
   //only when the key in the transaction lists changes
   //i.e. the user changes the selection 
   if (_dstrCurrentKeyInParentList != strListItemKey)
   {
      _dstrCurrentKeyInParentList = strListItemKey;
      if (idList == IFASTBP_PROC::FUND_ALLOCATION_LIST)
      {
         TradeFundAlloc* pTradeFundAlloc = NULL;

         setSplitCommissionListPtr(pTradeFundAlloc, _pFundAllocationList, strListItemKey);
      }
      else if (idList == IFASTBP_PROC::TRANSACTION_HISTORY_LIST)
      {
         const BFDataGroupId& idDataGroup = getDataGroupId();
         DString dstrAccountNum, dstrFundCode, dstrClassCode, dstrTransType;
         
         
         if (!_pFundAllocationList)
         {
            getPtrForContainer(IFASTBP_PROC::FUND_ALLOCATION_LIST, idDataGroup);
         }

         BFObjIter iter(*_pTransactionList, idDataGroup, false, 
            BFObjIter::ITERTYPE::NON_DELETED);

         if (iter.positionByKey(strListItemKey))
         {
            TransactionDetails *pTransactionDetails = 
               dynamic_cast<TransactionDetails*>(iter.getObject());

            if (pTransactionDetails  && _pFundAllocationList  )
            {
               pTransactionDetails->getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
               pTransactionDetails->getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);

               BFData matchCriteria;

               matchCriteria.setElementValue(ifds::AccountNum, _dstrAccountNum, true);
               matchCriteria.setElementValue(ifds::FundCode, dstrFundCode, true);
               matchCriteria.setElementValue(ifds::ClassCode, dstrClassCode, true);
   
               BFObjIter iter(*_pFundAllocationList, idDataGroup, true);

               iter.positionOnNextMatch(matchCriteria, idDataGroup);
               if (!iter.end())
               {
                  TradeFundAlloc* pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(iter.getObject());

                  if (pTradeFundAlloc)
                  {
                     pTradeFundAlloc->getSplitCommissionList(_pSplitCommissionList, idDataGroup);
                  }
               }
            }
         }
      }
      else if (idList == IFASTBP_PROC::MATCH_TRANSFER_LIST)
      {
         MatchTransferDetails* pMatchTransferDetails = NULL;

         setSplitCommissionListPtr(pMatchTransferDetails, _pMatchTransferList, strListItemKey);
      }
      else if (idList == IFASTBP_PROC::SYS_ALLOCATION_LIST)
      {
         SysAllocation *pSysAllocation = NULL;

         setSplitCommissionListPtr(pSysAllocation, _pSysAllocationList, strListItemKey);
      }
      else if (idList == IFASTBP_PROC::SYS_ATALLOCATION_LIST)
      {
         AutoTransAllocation *pAutoTransAllocation = NULL;

         setSplitCommissionListPtr(pAutoTransAllocation, _pAutoTransAllocationList, strListItemKey);
      }
      if (_pSplitCommissionList)
      {
         //sets the split commission container
         setContainer(IFASTBP_PROC::SPLIT_COMMISSION_LIST, _pSplitCommissionList);
      }
   }
   
   AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);
}

//******************************************************************************
void *SplitCommissionsProcess::getPtrForContainer ( const BFContainerId& idContainer, 
                                                    const BFDataGroupId& idDataGroup
                                                  )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer")
                         );
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::FUND_ALLOCATION_LIST == idContainer)
      {
         if ( _dstrCaller == SPLITCOMM::TRADE || 
              _dstrCaller == SPLITCOMM::TRADE_ALLOCATION
            )
         {
            WorksessionTradesList *pTradesList = NULL;
            if (pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING)
            {
            
               BFObjIter iter (*pTradesList, idDataGroup);

               iter.positionByKey (_dstrMainListKey);
               if (!iter.end())            
               {
                  _pTrade = dynamic_cast <Trade*> (iter.getObject());
                  if (_pTrade)
                  {
                     //retrieve the fund allocation list for the account
                     TradeFundAllocList *pFundAllocationList = NULL;
                     //do not create the account allocations if is not necessary, flag set to false
                     _pTrade->getFundAllocationList (_pFundAllocationList, idDataGroup, false);
                     ptr = _pFundAllocationList;
                  }
               }
            }
         }
         else if ( _dstrCaller == SPLITCOMM::TRANSACTION_PENDING || 
                   _dstrCaller == SPLITCOMM::TRANSACTION_PENDING_ALLOCATION
                 )
         {
            //get the associated pending trades list
            PendingTradeList *pPendingTradeList = NULL;
            
            if (_pMFAccount->getPendingTradesList (pPendingTradeList, idDataGroup) <= WARNING)
            {
               if (pPendingTradeList)
               {
                  PendingTradeDetails *pPendingTradeDetails = NULL;

                  setTradeFundAllocListPtr (pPendingTradeDetails, pPendingTradeList);
                  ptr = _pFundAllocationList;
               }
            }
         }
         else if ( _dstrCaller == SPLITCOMM::TRANSACTION_HISTORY || 
                   _dstrCaller == SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION
                 )
         {
            _pMFAccount->getLastActiveTransactionHistoryList ( _pTransactionList, idDataGroup);
            if (_pTransactionList)
            {
               TransactionDetails* pTransactionDetails = NULL;

               setTradeFundAllocListPtr (pTransactionDetails, _pTransactionList);
               ptr = _pFundAllocationList;
            }
         }
      }
      else if (IFASTBP_PROC::TRANSACTION_HISTORY_LIST == idContainer)
      {
         //get the associated transaction history list
         _pMFAccount->getLastActiveTransactionHistoryList(_pTransactionList, idDataGroup);
         if (_pTransactionList) //also get the trade fund alloc list
         {
            ptr = _pTransactionList;
         }
      }
      else if (IFASTBP_PROC::MATCH_TRANSFER_LIST == idContainer)
      {
         //get the associated match transfer list
         if ( _pMFAccount->getMatchTransferList ( _pMatchTransferList, 
                                                 _dstrMatchTransactionId, 
                                                 idDataGroup
                                                ) <= WARNING &&
              _pMatchTransferList
            )
         {
            ptr = _pMatchTransferList;
         }
      }
      else if (IFASTBP_PROC::SYS_ALLOCATION_LIST == idContainer)
      {
         SystematicList *pSystematicList = NULL;
         
         if (_pMFAccount->getSystematicList (pSystematicList, idDataGroup) <= WARNING)
         {
            BFObjIter iterSystematicList ( *pSystematicList, 
                                           idDataGroup, 
                                           false, 
                                           BFObjIter::ITERTYPE::NON_DELETED
                                         );

            if (iterSystematicList.positionByKey (_dstrMainListKey))
            {
               _pSystematic = dynamic_cast <Systematic*>(iterSystematicList.getObject());

               if (_pSystematic)
               {
//little 'peace of mind' test
                  DString dstrTransType;

                  _pSystematic->getField (ifds::TransType, dstrTransType, idDataGroup, false);
                  //the systematic type should be different then 'AT'
                  assert (dstrTransType != TRADETYPE::AUTO_TRANSFER);

                  _pSystematic->getSysAllocationList (_pSysAllocationList);
                  ptr = _pSysAllocationList;
               }
            }
         }
      }
      else if (IFASTBP_PROC::SYS_ATALLOCATION_LIST == idContainer)
      {
         SystematicList *pSystematicList = NULL;
         
         if (_pMFAccount->getSystematicList (pSystematicList, idDataGroup) <= WARNING)
         {
            BFObjIter iterSystematicList ( *pSystematicList, 
                                           idDataGroup, 
                                           false, 
                                           BFObjIter::ITERTYPE::NON_DELETED
                                         );

            if (iterSystematicList.positionByKey(_dstrMainListKey))
            {
               _pSystematic = dynamic_cast <Systematic*> (iterSystematicList.getObject());

               if (_pSystematic)
               {
                  DString dstrTransType;

                  //little 'peace of mind' test
                  _pSystematic->getField (ifds::TransType, dstrTransType, idDataGroup, false);
                  //the systematic type should be 'AT'
                  assert (dstrTransType == TRADETYPE::AUTO_TRANSFER);

                  AutoAcctTransAllocationList *pAutoAcctTransAllocationList = NULL;

                  //assumming there is only one item in the AutoAcctTransAllocationList...
                  //we support, in this case, only 100% account allocation
                  if (_pSystematic->getAtAcctAllocationList(pAutoAcctTransAllocationList) <= WARNING)
                  {
                     BFObjIter iterAutoAcctTransAllocationList(
                        *pAutoAcctTransAllocationList, idDataGroup, false, 
                        BFObjIter::ITERTYPE::NON_DELETED);

                     if (!iterAutoAcctTransAllocationList.end())
                     {
                        AutoAcctTransAllocation* pAutoAcctTransAllocation = 
                              dynamic_cast<AutoAcctTransAllocation*>(
                              iterAutoAcctTransAllocationList.getObject());
                        
                        if (pAutoAcctTransAllocation)
                        {
                           pAutoAcctTransAllocation->getAtAllocationList(_pAutoTransAllocationList);
                           ptr = _pAutoTransAllocationList;
                        }
                     }
                  }
               }
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
      assert(0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, 
                       I_("getPtrForContainer"),
                       CND::BP_ERR_UNKNOWN_EXCEPTION
                     );
   }
   return ptr;
}

//******************************************************************************
SEVERITY SplitCommissionsProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                                  const BFDataGroupId& idDataGroup
                                                )
{
   return _pSplitCommissionList ? _pSplitCommissionList->validateAll(idDataGroup) : NO_CONDITION;
}

//******************************************************************************
void SplitCommissionsProcess::doPostOk (GenericInterface *rpGICaller, bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

   if (bSuccessFlag)
   {
      if (_pSplitCommissionList)
      {
         const BFDataGroupId& idDataGroup = getDataGroupId();

         if ( _dstrCaller == SPLITCOMM::TRADE || 
              _dstrCaller == SPLITCOMM::TRADE_ALLOCATION)
         {
            //modify the Fee field in the corresponding Trade
            if (_pTrade)
            {
               DString splitTotalRate,
                  transType, 
                  fundCode, 
                  classCode,
                  fromFundCode,
                  fromClassCode;

               _pSplitCommissionList->getSplitTotalRate(splitTotalRate, idDataGroup);         
               _pTrade->getField (ifds::TradesTransType, transType, idDataGroup);
               transType.strip().upperCase();
               if ( transType == TRADETYPE::TRANSFER ||
                    transType == TRADETYPE::EXCHANGE)
               {
                  _pTrade->getField (ifds::ToFund, fundCode, idDataGroup.getParent(), false);
                  _pTrade->getField (ifds::ToClass, classCode, idDataGroup.getParent(), false);
                  _pTrade->getField (ifds::FromFund, fromFundCode,idDataGroup.getParent(), false);
                  _pTrade->getField (ifds::FromClass, fromClassCode, idDataGroup.getParent(), false);
               }
               else
               {
                  _pTrade->getField (ifds::FromFund, fundCode, idDataGroup.getParent(), false);
                  _pTrade->getField (ifds::FromClass, classCode, idDataGroup.getParent(), false);
               }

               // only assign the total commission back to trade if it 
               // is a single fund allocation and
               // the fund/class is not a Back End Load fund
               // if we deal with new money in a transfer/exchange 
               // then assign the fee back to FeeTo

               FundDetailList *pFundDetailList = NULL;
               DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               bool bNewMoney = false;
               
               if ( pDSTCWorkSession->getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING &&
                    pFundDetailList &&
                    !fundCode.empty() &&
                    !classCode.empty())
               {               
                  DString loadType;

                  pFundDetailList->getField ( fundCode, classCode, ifds::LoadType, 
                                              loadType, BF::HOST, false);
                  loadType.strip().upperCase();

                  if ( !fromFundCode.empty() && 
                       !fromClassCode.empty())
                  {                  
                     FundToList fundToList (*pFundDetailList);
                     
                     bNewMoney =  fundToList.isBuySell ( fromFundCode, 
                                                         fromClassCode, 
                                                         fundCode, 
                                                         classCode);
                  }

                  TransFeeList *pTransFeeList = NULL;

                  if ( _pTrade->getTransFeeList (pTransFeeList, idDataGroup.getParent(), false) <= WARNING &&
                        pTransFeeList)
                  {
                     DString feeCode;
                     
                     if (bNewMoney)
                     {
                        //_pTrade->setField (ifds::FeeTo, splitTotalRate, idDataGroup.getParent(), true, true);
                        feeCode = FEES::XFER_IN;
                     }
                     else if (
                        (transType == TRADETYPE::TRANSFER || transType == TRADETYPE::EXCHANGE) ||  
                        (transType == TRADETYPE::PURCHASE && loadType != BACKENDLOAD) ||
                        (transType == TRADETYPE::REDEMPTION && loadType != FRONTENDLOAD && 
                        SplitCommission::isTypeONE(*pDSTCWorkSession)))
                     {
                        //_pTrade->setField (ifds::Fee, splitTotalRate, idDataGroup.getParent(), true, true);
                        if (transType == TRADETYPE::PURCHASE)
                        {
                           feeCode = FEES::ACQUISITION;
                        }
                        else if (transType == TRADETYPE::REDEMPTION)
                        {
                           feeCode == FEES::REDEMPTION;
                        }
                        else if ( transType == TRADETYPE::TRANSFER || 
                                  transType == TRADETYPE::EXCHANGE)
                        {
                           feeCode = FEES::XFER_OUT;
                        }
                     }
                     if (!feeCode.empty())
                     {
                        TransFee *pTransFee = NULL;

                        if ( pTransFeeList->getTransFee ( feeCode, 
                                                          pTransFee, 
                                                          idDataGroup.getParent()) <= WARNING &&
                              pTransFee)
                        {
                           if (!SplitCommission::isTypeTWO (*pDSTCWorkSession))
                           {
                              pTransFee->setField ( ifds::FeeRate, 
                                                   splitTotalRate, 
                                                   idDataGroup.getParent(), 
                                                   true, 
                                                   true);
                           }
                        }
                     }
                  }
               }
            }
         } 
         else if ( _dstrCaller == SPLITCOMM::SYSTEMATIC_ALLOCATION )
         {
            //modify the Fee field in the corresponding Systematic
            if (_pSystematic)
            {
               DString splitTotalRate;

               _pSplitCommissionList->getSplitTotalRate(splitTotalRate, idDataGroup);
               _pSystematic->setField(ifds::Fee, splitTotalRate, idDataGroup.getParent(), true, true);
            }
         }
      }
   }
}

//******************************************************************************
template <class _X> 
   void SplitCommissionsProcess::setTradeFundAllocListPtr(const _X*, BFCBO* pMainList)
{
   const BFDataGroupId& idDataGroup = getDataGroupId();
   BFObjIter iter(*pMainList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   if (iter.positionByKey(_dstrMainListKey))
   {
      _X* pMainListTypeDetails = dynamic_cast<_X*>(iter.getObject());

      if (pMainListTypeDetails)
      {
         DString dstrTransType, 
            acctNum,
            allocAcctNum; 
         
         //init these with the member account
         acctNum = allocAcctNum = _dstrAccountNum;
         //find out which account to use, based on the transaction type
         pMainListTypeDetails->getField(ifds::TransType, dstrTransType, idDataGroup, false);

         if ( _dstrCaller == SPLITCOMM::TRANSACTION_HISTORY || 
              _dstrCaller == SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION
            )
         {
            DString allocation;

            pMainListTypeDetails->getField(ifds::Allocation, allocation, idDataGroup, false);
            if ( dstrTransType == TRADETYPE::TRANSFER_IN || 
                 DSTCommonFunctions::codeInList(dstrTransType,TRADETYPE::TRANSFER_IN_2)
               )
            {
               if (allocation == I_("Y"))
               {
                  pMainListTypeDetails->getField(ifds::TfrAcct, allocAcctNum, idDataGroup, false);
               }
            }
            else if ( dstrTransType == TRADETYPE::TRANSFER_OUT ||
                      dstrTransType == TRADETYPE::TRANSFER     ||
                      DSTCommonFunctions::codeInList(dstrTransType,TRADETYPE::TRANSFER_OUT_2)
                     )
            {
               pMainListTypeDetails->getField(ifds::TfrAcct, acctNum, idDataGroup, false);
            }
         } 
         else if (dstrTransType == TRADETYPE::TRANSFER)
         {
            pMainListTypeDetails->getField(ifds::AccountTo, acctNum, idDataGroup, false);
            if (_dstrCaller == SPLITCOMM::TRADE || 
               _dstrCaller == SPLITCOMM::TRADE_ALLOCATION)
            {
               allocAcctNum = acctNum;
            }
         }
         //get the transaction account allocation list
         TradeAcctAllocList *pAccountAllocationList = NULL;
         
         if (pMainListTypeDetails->getAccountAllocationList (pAccountAllocationList, 
            idDataGroup, allocAcctNum) <= WARNING)
         {
            TradeAcctAlloc * pAccountAllocation = NULL;

            //here, used the current account
            if (pAccountAllocationList->getAccountAllocation(acctNum, 
               pAccountAllocation, idDataGroup) <= WARNING)
            {
               if (pAccountAllocation)
               {
                  pAccountAllocation->getFundAllocationList(_pFundAllocationList, idDataGroup);
               }
            }
         }
      }
   }
}

//******************************************************************************
template <class _X> 
   void SplitCommissionsProcess::setSplitCommissionListPtr(const _X*, BFCBO* pParentList, 
      const DString& strListItemKey)
{
   const BFDataGroupId& idDataGroup = getDataGroupId();
   BFObjIter iter(*pParentList, idDataGroup);

   DString key = iter.getStringKey();

   if (iter.positionByKey(strListItemKey))
   {
      _X *pParent = dynamic_cast<_X*>(iter.getObject());

      if (pParent)
      {
         pParent->getSplitCommissionList(_pSplitCommissionList, idDataGroup);
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SplitCommissionsProcess.cpp-arc  $
// 
//    Rev 1.80   Jul 26 2012 10:33:08   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.79   Feb 16 2012 16:26:02   popescu
// 2849584 - For pending trade for FEL funds ,  fee value is not getting assigned correctly.
// 
//    Rev 1.78   Mar 04 2011 12:03:46   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.77   Jan 29 2008 13:21:54   daechach
// IN#1134569 - Cancel of Transfer out Trade not Allowed.
// 
//    Rev 1.76   Apr 08 2005 15:39:12   aguilaam
// IN 260178 - corrected assignment of fee for auto transfer
// 
//    Rev 1.75   Jan 12 2005 18:50:56   popescu
// PTS 10037339, allowed user to set Redemption Fee up
// 
//    Rev 1.74   Dec 01 2004 19:50:08   popescu
// PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
// 
//    Rev 1.73   Nov 27 2004 21:21:08   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.72   Nov 19 2004 11:13:00   yingbaol
// PET1117: tunning changes
// 
//    Rev 1.71   Nov 17 2004 15:19:02   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.70   Nov 07 2004 14:06:22   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.69   Nov 04 2004 17:36:36   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.68   Jan 21 2004 18:11:50   popescu
// PTS 10026237,
// For allocated purchases the acquisition fee should be zero and split commissions default values are displayed as they are returned by view 158.
// Also, if no repeated record is returned by 158 set the IFee to the Fee field value of the fixed section of view 158 and follow the same validation rules, as if split commissions would exist.
// 
//    Rev 1.67   Dec 17 2003 10:46:36   popescu
// PTS 10024124, split comm re-work
// 
//    Rev 1.66   Dec 16 2003 12:42:22   popescu
// PTS 10024124
// 
//    Rev 1.65   Dec 11 2003 14:08:12   popescu
// PTS 10024124, split comm-rework
// 
//    Rev 1.64   Oct 28 2003 16:23:38   popescu
// PTS 10020344, the default 100% alloc has been created using the wrong from account in case of a transfer
// 
//    Rev 1.63   Oct 15 2003 11:28:40   popescu
// PTS 10022849, wrong account number has been used to fetch the allocation list in case of pending transfer
// 
//    Rev 1.62   Sep 17 2003 15:24:46   popescu
// PTS 10020344, fix this as it failed in regression 
// 
//    Rev 1.61   Sep 04 2003 11:37:42   popescu
// in doPostOk, check whether the bSuccessFlag is set to true and then assign the Fee valud to either Trade or Systematic
// 
//    Rev 1.60   Sep 02 2003 15:10:54   popescu
// PTS 10021022, zero should not be assigned to the 'Fee' field in case of a back-end load fund, since this creates lots of complication. The Fee should be zero by default and set at the Trade level
// 
//    Rev 1.59   Aug 19 2003 11:50:36   popescu
// PTS 10018428 and PTS 10018433
// although explanations have been provided and action items have been added for the view team, further testing for these two tickets revealed an issue related to setting the transaction sequence for an allocated transaction details. The sequence has been correctly set to the TradeFundAlloc object
// 
//    Rev 1.58   Aug 18 2003 19:37:22   popescu
// PTS 100020184, correctly build the account allocations for transaction history details
// 
//    Rev 1.57   Jul 30 2003 11:17:02   popescu
// PTS 10017677, partial fix
// 
//    Rev 1.56   May 16 2003 17:22:46   popescu
// move the ownership of split commission at the trade fund alloc level
// 
//    Rev 1.55   May 15 2003 15:03:08   popescu
// fixes for a crash in PendingTrades, split comm
// 
//    Rev 1.54   May 15 2003 11:38:52   popescu
// Fix system crash in TransactioAllocationDialog with split commission
// 
//    Rev 1.53   May 14 2003 11:15:28   popescu
// added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
// 
//    Rev 1.52   May 13 2003 20:03:42   popescu
// Commented out the assertion when split commission is null
// 
//    Rev 1.51   May 13 2003 10:04:54   popescu
// Split commission re-work
// 
//    Rev 1.50   May 01 2003 11:11:20   sanchez
// For Transaction History inquiry add up the CommAmount from SplitCommission view call and use that as the total amount. (PTS#10016258)
// 
//    Rev 1.49   Apr 14 2003 16:27:22   popescu
// PTS 10011081- split commision amount is being calculated by the view side
// 
//    Rev 1.48   Apr 05 2003 16:10:56   popescu
// Moved setting the Fee field inTrade & Systematic into the SplitCommisionProcess
// 
//    Rev 1.47   Apr 04 2003 15:58:54   popescu
// split commsion work for Systematic
// 
//    Rev 1.46   Mar 21 2003 17:48:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.45   Nov 29 2002 10:20:44   KOVACSRO
// rxTransType changes
// 
//    Rev 1.44   Oct 09 2002 23:53:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.43   Aug 29 2002 16:45:16   SMITHDAV
// Condition split.
// 
//    Rev 1.42   Aug 29 2002 12:54:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.41   Aug 12 2002 12:14:22   HSUCHIN
// bug fix PTS - 10008923 .   Amount in split list grid not calculated properly before.
// 
//    Rev 1.40   Jun 03 2002 16:55:34   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.39   Jun 03 2002 11:16:14   HSUCHIN
// sync up with 1.34.1.1
// 
//    Rev 1.38   24 May 2002 15:41:54   KOVACSRO
// fixed an old bug for transaction allocations.
// 
//    Rev 1.37   22 May 2002 18:25:04   PURDYECH
// BFData Implementation
// 
//    Rev 1.36   08 May 2002 16:46:02   KOVACSRO
// A bug fix for account allocation key.
// 
//    Rev 1.35   29 Apr 2002 16:14:00   KOVACSRO
// new trade allocations.
// 
//    Rev 1.34   27 Mar 2002 19:55:42   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.33   Feb 25 2002 18:54:24   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.32   08 Feb 2002 10:37:20   HSUCHIN
// added support for inquiry mode for trade and other dialogs
// 
//    Rev 1.31   07 Oct 2001 16:30:26   HSUCHIN
// undo last changes
// 
//    Rev 1.29   13 Sep 2001 17:50:18   HSUCHIN
// added logic for manuseg to drive split commission by percent rather than rate
// 
//    Rev 1.28   Aug 16 2001 13:22:06   ZHANGCEL
// Added logic for lunch SplitCommission from MatchTransferDlg
// 
//    Rev 1.27   08 Aug 2001 17:52:54   HSUCHIN
// bug fix for Transaction History inconsistency
// 
//    Rev 1.26   08 Aug 2001 14:26:02   HSUCHIN
// bug fix to use MFAccount's getTransactionHistoryList to retrieve Historical List rather than getTransactionList
// 
//    Rev 1.25   28 May 2001 10:09:22   KOVACSRO
// Syncup SSB (1.21.1.2)
// 
//    Rev 1.24   25 May 2001 13:39:02   KOVACSRO
// Syncup SSB (1.21.1.0)
// 
//    Rev 1.23   25 May 2001 10:03:20   KOVACSRO
// Sync up SSB (1.21.1.0)
// 
//    Rev 1.22   11 May 2001 16:33:38   YINGZ
// code sync up
// 
//    Rev 1.21   May 03 2001 15:32:14   HERNANDO
// Added Parameters.
// 
//    Rev 1.20   May 02 2001 15:04:30   YINGZ
// null pointer fix
// 
//    Rev 1.19   30 Apr 2001 16:14:32   HSUCHIN
// Fix Total Amount Calculation
// 
//    Rev 1.18   27 Apr 2001 14:33:18   HSUCHIN
// changed commAmount to be SUBCLASS_PROCESS
// 
//    Rev 1.17   16 Apr 2001 14:08:20   HSUCHIN
// Set SplitCommission dlg to be inquiry mode when accessed from Transaction History
// 
//    Rev 1.16   14 Apr 2001 16:02:46   HSUCHIN
// transaction history bug fix and trade hook up
// 
//    Rev 1.15   03 Apr 2001 20:08:54   HSUCHIN
// added trade allocation split commission hook up
// 
//    Rev 1.14   01 Apr 2001 09:50:32   HSUCHIN
// added ATSysAllocation hook up (doesn't work yet)
// 
//    Rev 1.13   Mar 22 2001 18:29:58   HERNANDO
// Revised parameters; added SplitByRate Parameter.
// 
//    Rev 1.12   Mar 22 2001 17:46:14   HERNANDO
// Quick fix; display Total Percent instead of Total Rate
// 
//    Rev 1.11   Mar 22 2001 16:20:54   HSUCHIN
// bug fix for split comm from transaction history
// 
//    Rev 1.10   Mar 22 2001 15:46:00   HSUCHIN
// added splitcomm details to transaction history
// 
//    Rev 1.9   Mar 22 2001 14:13:40   HSUCHIN
// added transaction allocations hook up
// 
//    Rev 1.8   Mar 21 2001 13:30:14   HSUCHIN
// more improvements and bug fix
// 
//    Rev 1.7   Mar 20 2001 15:41:26   HSUCHIN
// some code clean up
// 
//    Rev 1.6   Mar 19 2001 15:04:00   HSUCHIN
// additional processing and validation
// 
//    Rev 1.5   Mar 18 2001 17:51:44   HSUCHIN
// check in for winnie
// 
//    Rev 1.4   Mar 18 2001 11:52:06   HSUCHIN
// additioanl features and support
// 
//    Rev 1.3   Mar 13 2001 09:11:46   HSUCHIN
// checked in for Zijian
// 
//    Rev 1.2   Mar 09 2001 13:11:16   HSUCHIN
// bug fix and check in for inquiry test
// 
//    Rev 1.1   Mar 08 2001 15:25:58   HSUCHIN
// check in for Ulli
*/
