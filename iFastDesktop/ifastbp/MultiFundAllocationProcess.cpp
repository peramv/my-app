//******************************************************************************
//
// COPYRIGHT:
//
//    Th* comput;
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MultiFundAllocationProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MultiFundAllocationProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : Support for the MultiFundAllocationDialog
//
//******************************************************************************

#include "stdafx.h"
#include "multifundallocationprocess.hpp"
#include "multifundallocationprocessincludes.h"
#include "mfcaninterprocparam.hpp"
//cbo level
#include <ifastcbo\funddetail.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\tradeacctalloc.hpp>
#include <ifastcbo\tradeacctalloclist.hpp>
#include <ifastcbo\tradefromfundalloclist.hpp>
#include <ifastcbo\tradefundalloc.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MULTI_FUND_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MULTI_FUND_ALLOCATION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MultiFundAllocationProcess > processCreator(CMD_BPROC_MULTI_FUND_ALLOCATION);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("MultiFundAllocationProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
MultiFundAllocationProcess::MultiFundAllocationProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_dstrCaller(NULL_STRING),
_dstrAcctNum(NULL_STRING),
_dstrListKey(NULL_STRING),
_dstrTransType(NULL_STRING),
_pMFAccount(NULL),
_pTradeFromFundAllocList(NULL),
_pTradeToFundAllocList(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   //this is the container for the trade 'from' fund list
   addContainer(IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, true, 
      BF::NullContainerId, true);
   //this is the container for the trade 'to' fund list
   addContainer(IFASTBP_PROC::FUND_ALLOCATION_LIST, true, BF::NullContainerId, true, 
      I_("TradeToFundAllocList"));
   //the list fields for 'from' alloc list
   addFieldDetails(ifds::ToFundNumber, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmount, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocPercentage, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmtType, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::FullTransfer, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllowFullTransfer, 
      IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(TotalAmount, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(TotalPercent, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   
   //the list fields for 'to' alloc list
   addFieldDetails(ifds::ToFundNumber, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmount, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(ifds::AllocPercentage, IFASTBP_PROC::FUND_ALLOCATION_LIST);
   addFieldDetails(TotalAmount, IFASTBP_PROC::FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails(TotalPercent, IFASTBP_PROC::FUND_ALLOCATION_LIST, SUBCLASS_PROCESS);
   //local helpers containers
   addContainer(TRADE_P, false);
   addContainer(TRADE_H, false);
   addContainer(TRADE, false);
   addFieldDetails(ifds::TradesTransType, TRADE);
   addContainer(ACCOUNT_FROM, false);
   addFieldDetails(ifds::AccountNum, ACCOUNT_FROM);
   addFieldDetails(ifds::AcctType, ACCOUNT_FROM);
   addFieldDetails(ifds::TaxType, ACCOUNT_FROM);
   addContainer(ACCOUNT_TO, false);
   addFieldDetails(ifds::AccountNum, ACCOUNT_TO);
   addFieldDetails(ifds::AcctType, ACCOUNT_TO);
   addFieldDetails(ifds::TaxType, ACCOUNT_TO);
}

//******************************************************************************
MultiFundAllocationProcess::~MultiFundAllocationProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
}

//************************************************************************************
SEVERITY MultiFundAllocationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();
   }
   catch (ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MultiFundAllocationProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();

   getParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
   getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAcctNum);
   getParameter(MFCAN_IP_PARAM::TRANS_TYPE, _dstrTransType);
   getParameter(MFCAN_IP_PARAM::LIST_KEY, _dstrListKey);
   //in case of caller 'Trade' and transaction type Transfer the
   //account sent over is the account to;
   if (_dstrAcctNum != NULL_STRING)
   {
      //retrieve the mf account pointer
      pDSTCWorkSession->getMFAccount(idDataGroup, _dstrAcctNum, 
         _pMFAccount, I_("N"), NULL_STRING, true, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN MultiFundAllocationProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
      rtn = invokeCommand(this, CMD_GUI_MULTI_FUND_ALLOCATION, 
         getProcessType(), isModal(), &_rpChildGI);
   }
   catch (ConditionException &ce)
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
   return rtn;
}

//******************************************************************************
void MultiFundAllocationProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted) const
{
   strValueOut = NULL_STRING;
   if (idContainer == IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST)
   {
      if (_pTradeFromFundAllocList)
      {
         if (idField == TotalAmount)
         {
            DString allowFullTransfer;

            _pTradeFromFundAllocList->getField (ifds::AllowFullTransfer, 
               allowFullTransfer, idDataGroup, false);
            if (allowFullTransfer == I_("Y"))
            {
               _pTradeFromFundAllocList->getEstimatedTotalAmount (strValueOut, 
                  idDataGroup, bFormatted);
            }
            else 
            {
               _pTradeFromFundAllocList->getTotalAmount (strValueOut, 
                  idDataGroup, bFormatted);
            }
         }
         else if (idField == TotalPercent)
         {
            _pTradeFromFundAllocList->getTotalPercentage (strValueOut, 
               idDataGroup, bFormatted);
         }
         else if (idField == ifds::AllowFullTransfer)
         {
            _pTradeFromFundAllocList->getField (ifds::AllowFullTransfer, 
               strValueOut, idDataGroup, false);
         }
      }
   } 
   else if (idContainer == IFASTBP_PROC::FUND_ALLOCATION_LIST)
   {
      if (idField == TotalAmount)
      {
         _pTradeToFundAllocList->getTotalAmount (strValueOut, 
            idDataGroup, bFormatted);
      }
      else if (idField == TotalPercent)
      {
         _pTradeToFundAllocList->getTotalPercentage (strValueOut, 
            idDataGroup, bFormatted);
      }
   }
}

//******************************************************************************
SEVERITY MultiFundAllocationProcess::doValidateAll(BFAbstractCBO *rpWSD, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pTradeFromFundAllocList)
   {
      _pTradeFromFundAllocList->validateAll(idDataGroup);
   }
   if (_pTradeToFundAllocList)
   {
      _pTradeToFundAllocList->validateAll(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MultiFundAllocationProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

      if (processParameters() <= WARNING)
      {
         //also reset containers,
         setContainer(ACCOUNT_FROM, NULL);
         setContainer(ACCOUNT_TO, NULL);
         setContainer(TRADE, NULL);
         setContainer(TRADE_P, NULL);
         setContainer(TRADE_H, NULL);
         setContainer(IFASTBP_PROC::FUND_ALLOCATION_LIST, NULL);
         setContainer(IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, NULL);
         setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
         if (isValidModelessInterface(_rpChildGI))
         {  // Only if child still exists
            bRtn = _rpChildGI->refresh(this, NULL);
            bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
void MultiFundAllocationProcess::doPostOk(GenericInterface *rpGICaller, 
   bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
   const BFDataGroupId& idDataGroup = getDataGroupId();

   if (bSuccessFlag)
   {
      if (_pTradeFromFundAllocList)
      {
         if (_dstrCaller == I_("Trade"))
         {
            DString fromFund (NULL_STRING), 
               fromClass (NULL_STRING),
               fullTransfer (NULL_STRING),
               amount (NULL_STRING);
            //get the current trade
            Trade* pTrade = 
               dynamic_cast<Trade*>(getCBOItem(TRADE, idDataGroup));
            //check whether the trade from fund alloc has more then one
            //element, if yes set the from fund and class to NULL_STRING
            if (pTrade)
            {
               if (getNumberOfItemsInList(this, 
                  IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST) == 1)
               {
                  BFAbstractCBO *pBFCBO = 
                     getCBOItem(IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, idDataGroup);

                  if (pBFCBO)
                  {
                     pBFCBO->getField (ifds::FundCode, fromFund, idDataGroup, false);
                     pBFCBO->getField (ifds::ClassCode, fromClass, idDataGroup, false);
                     pBFCBO->getField (ifds::FullTransfer, fullTransfer, idDataGroup, false);
                     pBFCBO->getField (ifds::AllocAmount, amount, idDataGroup, false);
                  }
                  if (fromFund != NULL_STRING && fromClass != NULL_STRING)
                  {
                     //remove the from list, here, do not send dummy to the back-end
                     setContainer (IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, NULL);
                     BFObjIter iter (*pTrade, idDataGroup);

                     iter.positionByKey (I_("FromFundAllocationList"));
                     if (!iter.end())
                     {
                        iter.removeObjectFromMap (true);
                        _pTradeFromFundAllocList = NULL;
                     }
                  }
               }
               pTrade->setField(ifds::FromFund, fromFund, idDataGroup.getParent(), 
                  false, false, false);
               pTrade->setField(ifds::FromClass, fromClass, idDataGroup.getParent(), 
                  false, false, false);
               pTrade->setField(ifds::FullTransfer, fullTransfer, idDataGroup.getParent(), 
                  false, false, false);
               if (fullTransfer == I_("N"))
               {
                  pTrade->setField (ifds::Amount, amount, idDataGroup.getParent(), 
                     false, false, false);
               }
            }
         }
      }
   }
}

//******************************************************************************
bool MultiFundAllocationProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_MULTI_FUND_ALLOCATION;
}

//******************************************************************************
void *MultiFundAllocationProcess::getPtrForContainer(const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   void *ptr = NULL;

   try
   {
      if (IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST == idContainer ||
         IFASTBP_PROC::FUND_ALLOCATION_LIST == idContainer)
      {
         if (_dstrCaller == I_("Trade"))
         {
            Trade* pTrade = 
               dynamic_cast<Trade*>(getCBOItem(TRADE, idDataGroup));

            if (pTrade)
            {
               if (IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST == idContainer)
               {
                  pTrade->getFromFundAllocationList(_pTradeFromFundAllocList, 
                     idDataGroup);
                  ptr = _pTradeFromFundAllocList;
               }
               else if (IFASTBP_PROC::FUND_ALLOCATION_LIST == idContainer)
               {
                  //get the transaction account allocation list
                  TradeAcctAllocList *pAcctAllocList = NULL;
   
                  if (pTrade->getAccountAllocationList (pAcctAllocList, 
                     idDataGroup, true) <= WARNING)
                  {
                     TradeAcctAlloc *pAcctAlloc = NULL;

                     //here, used the current account, this is the To account,
                     //which in case of an exchange is the same with the From account
                     if (pAcctAllocList->getAccountAllocation (_dstrAcctNum, 
                        pAcctAlloc, idDataGroup) <= WARNING)
                     {
                        if (pAcctAlloc)
                        {
                           if (pAcctAlloc->getFundAllocationList(
                              _pTradeToFundAllocList, idDataGroup) <= WARNING)
                           {
                              ptr = _pTradeToFundAllocList;
                           }
                        }
                     }
                  }
               }
            }
         }
         else if (_dstrCaller == I_("Pending"))
         {
            PendingTradeDetails* pPendingTradeDetails = 
               dynamic_cast<PendingTradeDetails*>(getCBOItem(TRADE_P, idDataGroup));

            if (pPendingTradeDetails)
            {
               if (IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST == idContainer)
               {
                  pPendingTradeDetails->getFromFundAllocationList (
                     _pTradeFromFundAllocList, idDataGroup);
                  ptr = _pTradeFromFundAllocList;
               }
               else if (IFASTBP_PROC::FUND_ALLOCATION_LIST == idContainer)
               {
                  //get the transaction account allocation list
                  TradeAcctAllocList *pAcctAllocList = NULL;
   
                  if (pPendingTradeDetails->getAccountAllocationList (pAcctAllocList, 
                     idDataGroup, _dstrAcctNum) <= WARNING)
                  {
                     TradeAcctAlloc *pAcctAlloc = NULL;
                     DString accountNum (_dstrAcctNum);

                     if (_dstrTransType == TRADETYPE::TRANSFER)
                     {
                        pPendingTradeDetails->getField (ifds::AccountTo, 
                           accountNum, idDataGroup, false);
                     }
                     if (pAcctAllocList->getAccountAllocation (accountNum, 
                        pAcctAlloc, idDataGroup) <= WARNING)
                     {
                        if (pAcctAlloc)
                        {
                           pAcctAlloc->getFundAllocationList(
                              _pTradeToFundAllocList, idDataGroup);
                           ptr = _pTradeToFundAllocList;
                        }
                     }
                  }
               }
            }
         }
         else if (_dstrCaller == I_("TransHist"))
         {
            TransactionDetails* pTransactionDetails = 
               dynamic_cast<TransactionDetails*>(getCBOItem(TRADE_H, idDataGroup));

            if (pTransactionDetails)
            {
               if (IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST == idContainer)
               {
                  pTransactionDetails->getFromFundAllocationList (_pTradeFromFundAllocList, 
                     idDataGroup);
                  ptr = _pTradeFromFundAllocList;
               }
               else if (IFASTBP_PROC::FUND_ALLOCATION_LIST == idContainer)
               {
                  DString dstrTransType, dstrAcctNum, dstrAllocAcctNum;
   
                  dstrAcctNum = dstrAllocAcctNum = _dstrAcctNum;
                  pTransactionDetails->getField(ifds::TransType, 
                     dstrTransType, idDataGroup);
                  if (dstrTransType == TRADETYPE::TRANSFER || 
                     dstrTransType == TRADETYPE::TRANSFER_OUT)
                  {
                     pTransactionDetails->getField(ifds::TfrAcct, 
                        dstrAcctNum, idDataGroup, false);
                  }
                  else if (dstrTransType == TRADETYPE::TRANSFER_IN)
                  {
                     DString allocation;

                     pTransactionDetails->getField(ifds::Allocation, 
                        allocation, idDataGroup, false);
                     if (allocation == I_("Y"))
                     {
                        pTransactionDetails->getField(ifds::TfrAcct, 
                           dstrAllocAcctNum, idDataGroup, false);
                     }
                  }
                  //get the transaction account allocation list
                  TradeAcctAllocList *pAcctAllocList = NULL;
   
                  if (pTransactionDetails->getAccountAllocationList (pAcctAllocList, 
                     idDataGroup, dstrAllocAcctNum) <= WARNING)
                  {
                     TradeAcctAlloc *pAcctAlloc = NULL;

                     if (pAcctAllocList->getAccountAllocation(dstrAcctNum, 
                        pAcctAlloc, idDataGroup) <= WARNING)
                     {
                        if (pAcctAlloc)
                        {
                           pAcctAlloc->getFundAllocationList(
                              _pTradeToFundAllocList, idDataGroup);
                           ptr = _pTradeToFundAllocList;
                        }
                     }
                  }
               }
            }
         }
      }
      else if (TRADE_P == idContainer)
      {
         //get the associated pending trades list
         PendingTradeList *pPendingTradeList = NULL;

         if (_pMFAccount->getPendingTradesList(pPendingTradeList, 
            idDataGroup) <= WARNING)
         {
            if (pPendingTradeList)
            {
               BFObjIter iter(*pPendingTradeList, idDataGroup, false, 
                  BFObjIter::ITERTYPE::NON_DELETED);

               if (iter.positionByKey(_dstrListKey))
               {
                  ptr = dynamic_cast<PendingTradeDetails*>(iter.getObject());
               }
            }
         }
      }
      else if (TRADE_H == idContainer)
      {
         TransactionList *pTransactionList = NULL;

         _pMFAccount->getLastActiveTransactionHistoryList(pTransactionList, 
            idDataGroup);
         if (pTransactionList)
         {
            BFObjIter iter(*pTransactionList, idDataGroup, false, 
               BFObjIter::ITERTYPE::NON_DELETED);

            if (iter.positionByKey(_dstrListKey))
            {
               ptr = dynamic_cast<TransactionDetails*>(iter.getObject());
            }
         }
      }
      else if (TRADE == idContainer)
      {
         WorksessionTradesList *pTradesList = NULL;

         if (pDSTCWorkSession->getTradesList(pTradesList, 
            idDataGroup) <= WARNING)
         {
            BFObjIter iter(*pTradesList, idDataGroup, false, 
               BFObjIter::ITERTYPE::NON_DELETED);

            if (iter.positionByKey(_dstrListKey))
            {
               ptr = dynamic_cast<Trade*>(iter.getObject());
            }
         }
      }
      else if (ACCOUNT_FROM == idContainer)
      {
         if (_dstrCaller == I_("Trade") && 
            _dstrTransType == TRADETYPE::TRANSFER) //we have to figure out the account 'From'
         {
            Trade* pTrade = 
               dynamic_cast<Trade*>(getCBOItem (TRADE, idDataGroup));
            if (pTrade)
            {
               MFAccount *pMFAccount = NULL;
               DString dstrAcctFrom;

               pTrade->getField (ifds::AccountNum, dstrAcctFrom, idDataGroup, false);
               //retrieve the mf account pointer
               if (pDSTCWorkSession->getMFAccount (idDataGroup, dstrAcctFrom, 
                  pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING)
               {
                  ptr = pMFAccount;
               }
            }
         }
         else if (_dstrCaller == I_("TransHist") && 
            _dstrTransType == TRADETYPE::TRANSFER_IN)
         {
            TransactionDetails* pTransactionDetails = 
               dynamic_cast<TransactionDetails*>(getCBOItem(TRADE_H, idDataGroup));

            if (pTransactionDetails)
            {
               if (pTransactionDetails)
               {
                  MFAccount *pMFAccount = NULL;
                  DString dstrAcctFrom;

                  pTransactionDetails->getField (ifds::TfrAcct, 
                     dstrAcctFrom, idDataGroup, false);
                  //retrieve the mf account pointer
                  if (pDSTCWorkSession->getMFAccount(idDataGroup, dstrAcctFrom, 
                     pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING)
                  {
                     ptr = pMFAccount;
                  }
               }
            }
         }
         else
         {
            ptr = _pMFAccount;
         }
      }
      else if (ACCOUNT_TO == idContainer)
      {         
         if (_dstrCaller == I_("Pending") && 
            _dstrTransType == TRADETYPE::TRANSFER) //we have to figure out the account 'To'
         {
            PendingTradeDetails* pPendingTradeDetails = 
               dynamic_cast<PendingTradeDetails*>(getCBOItem(TRADE_P, idDataGroup));

            if (pPendingTradeDetails)
            {
               MFAccount *pMFAccount = NULL;
               DString dstrAcctTo (NULL_STRING);

               pPendingTradeDetails->getField (ifds::AccountTo, 
                  dstrAcctTo, idDataGroup, false);
               //retrieve the mf account pointer
               if (pDSTCWorkSession->getMFAccount (idDataGroup, dstrAcctTo,
                  pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING)
               {
                  ptr = pMFAccount;
               }
            }
         }
         else if (_dstrCaller == I_("TransHist") && 
            _dstrTransType == TRADETYPE::TRANSFER_OUT)
         {
            TransactionDetails* pTransactionDetails = 
               dynamic_cast<TransactionDetails*> (getCBOItem(TRADE_H, idDataGroup));

            if (pTransactionDetails)
            {
               MFAccount *pMFAccount = NULL;
               DString dstrAcctTo (NULL_STRING);

               pTransactionDetails->getField (ifds::TfrAcct, 
                  dstrAcctTo, idDataGroup, false);
               //retrieve the mf account pointer
               if (pDSTCWorkSession->getMFAccount(idDataGroup, dstrAcctTo,
                  pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING)
               {
                  ptr = pMFAccount;
               }
            }
         }
         else
         {
            ptr = _pMFAccount;
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
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MultiFundAllocationProcess.cpp-arc  $
// 
//    Rev 1.9   Feb 18 2004 18:34:14   popescu
// PTS 10026471, Copy the value of the Amount from the Multi-Fun Allocation screen to the Trading screen, in case of a one-to multi transfer/exchange.
// 
//    Rev 1.8   Jan 19 2004 17:42:58   popescu
// PTS 10026204, 
// Preserve the state of the Full Transfer flag
// 
//    Rev 1.7   Nov 04 2003 11:40:26   popescu
// PTS 10023203, Transaction History allocation issues for multi fund allocation, desktop not sending a request for FROM records
// 
//    Rev 1.6   Oct 28 2003 12:40:26   popescu
// PTS 10023292, display issues of decimal fields
// 
//    Rev 1.5   Oct 03 2003 11:44:46   popescu
// Removed commented out code to get the to fund allocation list .
// 
//    Rev 1.4   Sep 12 2003 10:43:58   popescu
// PET809, FN02 CIBC multi fund transfer
// Moved the cross objects validation between FromFundList and ToFundList from the process layer to the CBO layer, and since the Trade object owns both lists, the most logical place to put the validation seemed to be doValidateAll method of the Trade object
// 
//    Rev 1.3   Sep 05 2003 18:29:12   popescu
// PET809_FN02, fixex
// 
//    Rev 1.2   Sep 03 2003 10:09:20   popescu
// quick fix for release
// 
//    Rev 1.1   Sep 01 2003 21:21:12   popescu
// PET 809 FN 02, CIBC Multi fund enhancement
// 
//    Rev 1.0   Aug 14 2003 15:48:12   popescu
// Initial revision.
// 
 *
 */
