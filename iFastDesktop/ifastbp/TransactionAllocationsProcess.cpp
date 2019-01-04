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
// ^FILE   : TransactionAllocationsProcess.cpp
// ^AUTHOR : 
// ^DATE   : 09/26/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransactionAllocationsProcess
//    This class manages the allocations information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "transactionallocationsprocess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\tradeacctalloc.hpp>
#include <ifastcbo\tradeacctalloclist.hpp>
#include "transactionallocationsprocessincludes.h"
#include <ifastcbo\tradefundalloc.hpp>
#include <ifastcbo\tradefundalloclist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastdataimpl\dse_dstc0060_vw.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANSACTION_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSACTION_ALLOCATIONS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransactionAllocationsProcess > processCreator(CMD_BPROC_TRANSACTION_ALLOCATIONS      );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("TransactionAllocationsProcess");   
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId Substitute_Description;
   extern CLASS_IMPORT const BFNumericFieldId TfrAcct;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT_2;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN_2;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

TransactionAllocationsProcess::TransactionAllocationsProcess(
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
_pMFAccount(0), 
_pAccountAllocationList(0), 
_rpChildGI(0)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addSubstituteList(ifds::AllocationUsage);
   addSubstituteList(ifds::TaxType);
   //addSubstituteList(DBR::Currency);
   addSubstituteList(ifds::TransType);
   addSubstituteList(ifds::LV_AccountAllocation);
   addSubstituteList(ifds::LV_FundAllocation);

   addContainer(IFASTBP_PROC::MFACCOUNT_CBO, false);
   addContainer(IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, true);
   addContainer(IFASTBP_PROC::FUND_ALLOCATIONS_LIST, true, 
                 IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST);
   addFieldDetails(ifds::TransType, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::TradeDate, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AllocationUsage, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AccountNum, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST);
   addFieldDetails(ifds::TaxType, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AcctPrcnt, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST);
   addFieldDetails(ifds::TransactionAmount, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::SettleCurrency, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::SplitComm, 
                    IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST);
   addFieldDetails(ifds::FundCode, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::ClassCode, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::AllocPercentage, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::AllocAmount, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::ToFundNumber, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::SplitComm, 
                    IFASTBP_PROC::FUND_ALLOCATIONS_LIST);
   addFieldDetails(ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails(ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails(ifds::TransNum, BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************

TransactionAllocationsProcess::~TransactionAllocationsProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);

   delete _pAccountAllocationList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY TransactionAllocationsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAccountNum);
      getParameter(MFCAN_IP_PARAM::CALLER, _dstrPendingOrTransHist);
      getParameter(MFCAN_IP_PARAM::TRANS_TYPE, _dstrTransCode);
      getParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
      getParameter(MFCAN_IP_PARAM::TRADE_DATE, _dstrTradeDate);
      getParameter(TRANSACTION_ALLOCATIONSPROC::SETTLE_CURRENCY, _dstrSettleCurrency);
      getParameter(MFCAN_IP_PARAM::LIST_KEY, _dstrPendingListKey);

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, _pMFAccount);
      //register CBO with base
      setContainer (IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount);
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TransactionAllocationsProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD);

   if (idField == ifds::TransNum)
      strValueOut = _dstrTransNum;

   if(idContainer == IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST)
   {
      if (idField == ifds::AllocationUsage)
      {
         const_cast< TransactionAllocationsProcess * >(this)->
         getField (rpGICaller, BFContainerId (ifds::AllocationUsage.getId()), 
         ifds::Substitute_Description, strValueOut); 
      }
      else if (idField == ifds::TransType)
      {
         const_cast< TransactionAllocationsProcess * >(this)->
         setCurrentListItem(rpGICaller, BFContainerId(ifds::TransType.getId()), _dstrTransCode);
         const_cast< TransactionAllocationsProcess * >(this)->
            getField (rpGICaller, BFContainerId(ifds::TransType.getId()), 
            ifds::Substitute_Description, strValueOut);   
      }
      else if(idField == ifds::TaxType)
      {
         const_cast< TransactionAllocationsProcess * >(this)->
         getField(rpGICaller, IFASTBP_PROC::MFACCOUNT_CBO, 
                   ifds::TaxType, strValueOut);
         strValueOut.strip();    
      }
      else if (idField == ifds::TradeDate)
         strValueOut = _dstrTradeDate;
      else if (idField == ifds::SettleCurrency)
         strValueOut = _dstrSettleCurrency;
      else if (idField == ifds::TransactionAmount)
      {
         TradeAcctAlloc *pTradeAcctAlloc = dynamic_cast <TradeAcctAlloc *> (
            const_cast< TransactionAllocationsProcess * >(this)->getCBOItem(
            IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, idDataGroup));
         if(pTradeAcctAlloc)
         {
            // We will let the AbstractAllocList calculate the Allocation total for us.
            TradeFundAllocList *pTradeFundAllocList ;
            pTradeAcctAlloc->getFundAllocationList(pTradeFundAllocList, idDataGroup);
            pTradeFundAllocList->getTotalAmount (strValueOut, idDataGroup);
         }
         else
         {
            //should always have a pointer to Account Allocation.
            assert (0);
         }        
      }
   }
   /*else if(idContainer == TRANSACTION_ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST)
   {
     if(idField == DBR::ToFundNumber)
     {
       DString dstrFundCode, dstrClassCode;
       const_cast< TransactionAllocationsProcess * >(this)->getField(rpGICaller, 
         TRANSACTION_ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST, 
         DBR::AllocFundToCode, dstrFundCode, false);
       const_cast< TransactionAllocationsProcess * >(this)->getField(rpGICaller, 
         TRANSACTION_ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST, 
         DBR::AllocClassToCode, dstrClassCode, false);
          DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
       dstcWorkSession->GetFundNumber (dstrFundCode, dstrClassCode, strValueOut);        
     }
   }*/
}

//******************************************************************************
E_COMMANDRETURN TransactionAllocationsProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::CALLER, _dstrPendingOrTransHist);
      setParameter (MFCAN_IP_PARAM::LIST_KEY, _dstrPendingListKey);
      rtn = invokeCommand(this, CMD_GUI_TRANSACTION_ALLOCATIONS, 
                           getProcessType(), isModal(), &_rpChildGI);
   }
   catch(ConditionException &ce)
   {
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
bool TransactionAllocationsProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_TRANSACTION_ALLOCATIONS);
}

//******************************************************************************
bool TransactionAllocationsProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      /*getParameter(TRANSACTION_ALLOCATIONSPROC::ACCOUNT_NUM, 
         _dstrAccountNum);
      getParameter(TRANSACTION_ALLOCATIONSPROC::TRANS_NUM, 
         _dstrTransNum) ;
      getParameter(TRANSACTION_ALLOCATIONSPROC::PENDING_LIST_CURKEY, 
         _dstrPendingListKey);
      getParameter(TRANSACTION_ALLOCATIONSPROC::PENDING_OR_TRANS_HIST, 
                    _dstrPendingOrTransHist);
      getParameter(TRANSACTION_ALLOCATIONSPROC::TRANS_CODE, 
         _dstrTransCode);
      getParameter(TRANSACTION_ALLOCATIONSPROC::TRADE_DATE, 
         _dstrTradeDate);
      getParameter(TRANSACTION_ALLOCATIONSPROC::SETTLE_CURRENCY, 
         _dstrSettleCurrency);
      getParameter(TRANSACTION_ALLOCATIONSPROC::TRANSACTION_AMOUNT, 
         _dstrTransactionAmount);*/
      getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAccountNum);
      getParameter(MFCAN_IP_PARAM::CALLER, _dstrPendingOrTransHist);
      getParameter(MFCAN_IP_PARAM::TRANS_TYPE, _dstrTransCode);
      getParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
      getParameter(MFCAN_IP_PARAM::TRADE_DATE, _dstrTradeDate);
      getParameter(TRANSACTION_ALLOCATIONSPROC::SETTLE_CURRENCY, 
         _dstrSettleCurrency);
      getParameter(MFCAN_IP_PARAM::LIST_KEY, _dstrPendingListKey);
      if (isValidModelessInterface(_rpChildGI))
      {  // Only if child still exists
         setContainer(IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, NULL);
         setContainer(IFASTBP_PROC::FUND_ALLOCATIONS_LIST, NULL);
         setParameter(MFCAN_IP_PARAM::CALLER, 
            _dstrPendingOrTransHist);
         setParameter(MFCAN_IP_PARAM::LIST_KEY, 
            _dstrPendingListKey);
         bRtn = _rpChildGI->refresh(this, I_("ReloadParams"));
         bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
      }
   }
   catch(ConditionException &ce)
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
void *TransactionAllocationsProcess::getPtrForContainer(const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      if(IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST == idContainer)
      {
         {  
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            MFAccount* mfAccount;
            dstcWorkSession->getMFAccount(idDataGroup, _dstrAccountNum, mfAccount);

            if(_dstrPendingOrTransHist == TRANSACTION_ALLOCATIONSPROC::TRANSHIST)
            {
               TransactionList *_pTransactionList;
               mfAccount->getLastActiveTransactionHistoryList(_pTransactionList, idDataGroup);
               if(_pTransactionList)
               {
                  BFObjIter iter(const_cast<TransactionList &>(*_pTransactionList), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                  if(iter.positionByKey (_dstrPendingListKey))
                  {
                     TransactionDetails *pTransactionDetails = static_cast <TransactionDetails *>(iter.getObject());
                     TradeAcctAllocList* pAccountAllocationList;

                     DString transType;
                     
                     pTransactionDetails->getField(ifds::TransType, transType, idDataGroup, false);
                     if ( transType == TRADETYPE::TRANSFER_IN || 
                         DSTCommonFunctions::codeInList(transType,TRADETYPE::TRANSFER_IN_2)
                        )
                     {
                        DString accountNum;

                        pTransactionDetails->getField(ifds::TfrAcct, accountNum, idDataGroup);
                        sevRtn = pTransactionDetails->getAccountAllocationList(pAccountAllocationList, 
                           idDataGroup, accountNum);
                     }
                     else
                     {
                        sevRtn = pTransactionDetails->getAccountAllocationList(pAccountAllocationList, idDataGroup, _dstrAccountNum);
                     }
                     if(sevRtn <= WARNING)
                     {
                        return(pAccountAllocationList);
//CP20030319                           break;
                     }
                  }
               }
            }
            else
            {
               PendingTradeList *_pPendingTradesList;
               sevRtn = mfAccount->getPendingTradesList(_pPendingTradesList, idDataGroup);
               if(WARNING >= sevRtn)
               {
                  BFObjIter iter(const_cast<PendingTradeList &>(*_pPendingTradesList), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                  if(iter.positionByKey (_dstrPendingListKey))
                  {
                     PendingTradeDetails *pPendingTradeDetails = static_cast <PendingTradeDetails *>(iter.getObject());
                     TradeAcctAllocList* pAccountAllocationList;
                     sevRtn = pPendingTradeDetails->getAccountAllocationList(pAccountAllocationList, idDataGroup, _dstrAccountNum);
                     if(sevRtn <= WARNING)
                     {
                        return(pAccountAllocationList);
//CP20030319                           break;
                     }
                  }
               }
            }
         }
//CP20030319            break;
//CP20030319         case TRANSACTION_ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST:
      }
      else if(IFASTBP_PROC::FUND_ALLOCATIONS_LIST == idContainer)
      {
         {
            TradeAcctAlloc *pAccountAllocation = NULL;
            if(getNumberOfItemsInList(this, IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST))
               pAccountAllocation = dynamic_cast< TradeAcctAlloc * >(
                                                                    getCBOItem(IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST, idDataGroup));
            if(pAccountAllocation)
            {
               TradeFundAllocList *pFundAllocationList ;
               pAccountAllocation->getFundAllocationList(pFundAllocationList, idDataGroup);
               ptr = pFundAllocationList;
            }
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch(ConditionException &)
   {
      throw;
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
// TODO  If severity > warning, throw error returned from above
   return(ptr);
}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionAllocationsProcess.cpp-arc  $
 * 
 *    Rev 1.29   Jan 29 2008 13:23:08   daechach
 * IN#1134569 - Cancel of Transfer out Trade not Allowed.
 * 
 *    Rev 1.28   Sep 01 2003 21:21:14   popescu
 * PET 809 FN 02, CIBC Multi fund enhancement
 * 
 *    Rev 1.27   Aug 20 2003 17:48:48   popescu
 * Refresh on the dialog did not work,this is not part of a PTS but impacts the inquiry of split commission
 * 
 *    Rev 1.26   Aug 18 2003 19:36:36   popescu
 * PTS 10020184, if transfer in the account allocation should be build based on the TfrAcct value
 * 
 *    Rev 1.25   May 15 2003 11:39:10   popescu
 * Fix system crash in TransactioAllocationDialog with split commission
 * 
 *    Rev 1.24   Apr 03 2003 14:29:32   PURDYECH
 * Missed some ctor initializations during DataGroupId conversion due to 'interesting' initializer list formatting.
 * 
 *    Rev 1.23   Mar 21 2003 17:49:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.22   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.21   Sep 30 2002 11:01:06   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.20   Sep 25 2002 15:42:08   KOVACSRO
 * PTS 10009965 : fixed crash
 * 
 *    Rev 1.19   Aug 29 2002 16:45:18   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.18   Aug 29 2002 12:54:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.17   Aug 23 2002 10:07:30   HSUCHIN
 * bug fix to account level list where the total amount was not calculated properly.
 * 
 *    Rev 1.16   22 May 2002 18:25:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.15   02 May 2002 15:16:40   KOVACSRO
 * small change.
 * 
 *    Rev 1.14   29 Apr 2002 16:16:06   KOVACSRO
 * new trade allocations.
 * 
 *    Rev 1.13   27 Mar 2002 19:55:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.12   08 Aug 2001 14:26:02   HSUCHIN
 * bug fix to use MFAccount's getTransactionHistoryList to retrieve Historical List rather than getTransactionList
 * 
 *    Rev 1.11   03 May 2001 14:05:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Mar 23 2001 12:34:30   HSUCHIN
 * changed to use the list key from transaction history
 * 
 *    Rev 1.9   Mar 22 2001 14:12:48   HSUCHIN
 * hook up to split commission
 * 
 *    Rev 1.8   Mar 21 2001 14:08:32   FENGYONG
 * change back to previous version
 * 
 *    Rev 1.6   Mar 18 2001 12:19:50   YINGZ
 * make it work with new account/fund level allocation structure
 * 
 *    Rev 1.5   Mar 18 2001 11:08:16   YINGZ
 * change field names
 * 
 *    Rev 1.4   15 Dec 2000 12:43:56   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 05 2000 09:57:44   HUANGSHA
 * Fixed the Amount Formating
 * 
 *    Rev 1.1   Jun 02 2000 13:20:48   HUANGSHA
 * save in SettleCurreny in PTAllocList
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Dec 24 1999 17:11:48   PRAGERYA
// For internal release
// 
//    Rev 1.5   Dec 01 1999 14:33:44   PRAGERYA
// Check-in for release
// 
//    Rev 1.4   Nov 18 1999 13:47:32   PRAGERYA
// Coding for Allocations, Incr2
// 
//    Rev 1.3   Nov 02 1999 16:30:20   DT24433
// removed doOk/doCancel
 * 
 *
 */
