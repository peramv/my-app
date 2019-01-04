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
// ^FILE   : AllocationSplitProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AllocationSplitProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : This class decides what type of allocation dialog 
//                     should be launched(multi-fund or simple)
//
//******************************************************************************

#include "stdafx.h"
#include "allocationsplitprocess.hpp"
#include "allocationsplitprocessincludes.h"
#include "mfcaninterprocparam.hpp"


extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSACTION_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MULTI_FUND_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SIMPLE_ALLOCATION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AllocationSplitProcess > processCreator(CMD_BPROC_ALLOCATIONS);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("AllocationSplitProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AllocationSplitProcess::AllocationSplitProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
_dstrAcctNum(NULL_STRING),
_dstrCaller(NULL_STRING),
_dstrListKey(NULL_STRING),
_dstrSubListKey(NULL_STRING),
_dstrTransType(NULL_STRING),
_dstrTransNum(NULL_STRING),
_dstrAllocationType(NULL_STRING),
_dstrTradeDate(NULL_STRING),
_dstrSettleCurrency(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//******************************************************************************
AllocationSplitProcess::~AllocationSplitProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//************************************************************************************
SEVERITY AllocationSplitProcess::doInit()
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
E_COMMANDRETURN AllocationSplitProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      const I_CHAR* allocationProcessId = NULL;

      //here decide which allocation process to invoke
      if (isMultiAllocationPossible())
      {
         allocationProcessId = CMD_BPROC_MULTI_FUND_ALLOCATION;
      }
      else if ( _dstrCaller == I_("Trade") || 
                _dstrCaller == I_("Systematic") ||
                _dstrCaller == I_("Default") ||
                _dstrCaller == I_("SearchDefault"))
      {
         allocationProcessId = CMD_BPROC_SIMPLE_ALLOCATION;
      }
      else if ( _dstrCaller == I_("Pending") || 
                _dstrCaller == I_("TransHist"))
      {
         allocationProcessId = CMD_BPROC_TRANSACTION_ALLOCATIONS;
      }
      if (passParametersOn() <= WARNING)
      {
         assert (allocationProcessId); //blow here if command is null
         rtn = invokeCommand( getParent(), 
                              allocationProcessId, 
                              getProcessType(), 
                              isModal(), 
                              NULL);
         if (_dstrCaller != I_("SearchDefault"))
         {
            //this process, should die gracefully 
            rtn = CMD_OK;
         }
      }
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
bool AllocationSplitProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_BPROC_MULTI_FUND_ALLOCATION ||
      cmd.getKey() == CMD_BPROC_SIMPLE_ALLOCATION;
}

//******************************************************************************
SEVERITY AllocationSplitProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
   getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAcctNum);
   getParameter(MFCAN_IP_PARAM::LIST_KEY, _dstrListKey);
   getParameter(MFCAN_IP_PARAM::SUB_LIST_KEY, _dstrSubListKey);
   getParameter(MFCAN_IP_PARAM::TRANS_TYPE, _dstrTransType);
   getParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
   getParameter(MFCAN_IP_PARAM::TRADE_DATE, _dstrTradeDate);
   getParameter(I_("SettleCurrency"), _dstrSettleCurrency);
   getParameter(I_("Allocation Type"), _dstrAllocationType);   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllocationSplitProcess::passParametersOn()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("passParametersOn"));

   setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAcctNum);
   setParameter(MFCAN_IP_PARAM::LIST_KEY, _dstrListKey);
   setParameter(MFCAN_IP_PARAM::SUB_LIST_KEY, _dstrSubListKey);
   setParameter(MFCAN_IP_PARAM::TRANS_TYPE, _dstrTransType);
   setParameter(MFCAN_IP_PARAM::TRANS_NUM, _dstrTransNum);
   setParameter(MFCAN_IP_PARAM::TRADE_DATE, _dstrTradeDate);
   setParameter(I_("SettleCurrency"), _dstrSettleCurrency);
   setParameter(I_("Allocation Type"), _dstrAllocationType);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AllocationSplitProcess::isMultiAllocationPossible()
{
   //check the worksession options for the mutli transfer flag 
   //and split commission
   bool multiAlloc = false;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DString commissionType, 
      allowMultiFundTransfer = I_("Y");

   pDSTCWorkSession->getOption(ifds::CommissionType, commissionType, 
      BF::HOST, false);
   pDSTCWorkSession->getOption(ifds::AllowMultiFundTransfer, allowMultiFundTransfer, 
      BF::HOST, false);
   multiAlloc = commissionType == I_("0") && //not a split commission environment
      allowMultiFundTransfer == I_("Y"); //allow multi transfer environment
   multiAlloc &= _dstrTransType == TRADETYPE::TRANSFER || 
      _dstrTransType == TRADETYPE::TRANSFER_IN ||
      _dstrTransType == TRADETYPE::TRANSFER_OUT ||
      _dstrTransType == TRADETYPE::EXCHANGE ||
      _dstrTransType == TRADETYPE::EXCHANGE_IN ||
      _dstrTransType == TRADETYPE::EXCHANGE_OUT;
   return multiAlloc;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationSplitProcess.cpp-arc  $
// 
//    Rev 1.8   May 11 2006 16:16:04   popescu
// Incident #588425 -Process should die for any callers, but search
// 
//    Rev 1.7   May 04 2006 11:40:20   popescu
// Incident #588425 - if allocation is called from TransHist/Pending trades - process should die.
// 
//    Rev 1.6   Apr 11 2006 14:41:00   jankovii
// Incident #588425.No error message when search for Allocation/Acct when security is restricted.
// 
//    Rev 1.5   Nov 04 2003 11:39:56   popescu
// PTS 10023203, Transaction History allocation issues for multi fund allocation, desktop not sending a request for FROM records
// 
//    Rev 1.4   Sep 03 2003 17:15:46   popescu
// fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
// 
//    Rev 1.3   Sep 01 2003 21:21:00   popescu
// PET 809 FN 02, CIBC Multi fund enhancement
// 
//    Rev 1.2   Aug 17 2003 12:48:06   popescu
// fixed a commiting error with the allocations; also removed the process from GIC after invoking its children
// 
//    Rev 1.1   Aug 16 2003 11:19:12   popescu
// missed a parameter to pass on
// 
//    Rev 1.0   Aug 14 2003 15:50:38   popescu
// Initial revision.
// 
 *
 */
