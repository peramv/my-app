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
// ^FILE   : SalesRepProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 12/15/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SalesRepProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "salesrepprocess.hpp"
#include "salesrepprocessincludes.h"
#include <ifastcbo\agentlist.hpp>
#include "mfcaninterprocparam.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("SalesRepProcess");
   const I_CHAR * const PERFORMSEARCH = I_("performSearch");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long ERR_AGENT_LIST_EMPTY;
   extern const long BP_ERR_SEL_BROKER_BRANCH_FIRST;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SLSREP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SLSREP;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SalesRepProcess > processCreator(CMD_BPROC_SLSREP);

//******************************************************************************
//              Public Methods
//******************************************************************************
SalesRepProcess::SalesRepProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand)
, _rpChildGI(NULL),
_pAgentList(NULL),
_dstrBrokerCode(NULL_STRING),
_dstrBranchCode(NULL_STRING),
_dstrCaller(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::AGENT_LIST, true);

   addFieldDetails(ifds::Slsrep, IFASTBP_PROC::AGENT_LIST);
   addFieldDetails(ifds::SlsrepName, IFASTBP_PROC::AGENT_LIST);
   addFieldDetails(ifds::SlsrepAltName, IFASTBP_PROC::AGENT_LIST);
   addFieldDetails(ifds::BranchCode, IFASTBP_PROC::AGENT_LIST);
   addFieldDetails(ifds::PayInstrComm, IFASTBP_PROC::AGENT_LIST);
   addFieldDetails(ifds::PayInstrTrailer, IFASTBP_PROC::AGENT_LIST);
}

//******************************************************************************
SalesRepProcess::~SalesRepProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);

   if (_pAgentList != NULL)
   {
      delete _pAgentList;
      _pAgentList = NULL;
   }
}

//******************************************************************************
bool SalesRepProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_SLSREP);
}

//******************************************************************************
SEVERITY SalesRepProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, DOINIT);
   try
   {
      getParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      getParameter(MFCAN_IP_PARAM::BRANCH_CODE, _dstrBranchCode);
      getParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);

      if (_dstrBrokerCode.strip() != NULL_STRING 
         /*&& _dstrBranchCode.strip() != NULL_STRING */)
      {
         _pAgentList = new AgentList(*getBFWorkSession());
         if (_pAgentList->init(_dstrBrokerCode, 
            _dstrBranchCode, NULL_STRING) <= WARNING)
         {
            BFObjIter agentListIter(*_pAgentList, getDataGroupId());        
            
            if (!agentListIter.end())
            {
               setContainer(IFASTBP_PROC::AGENT_LIST, _pAgentList);
            }
            else
            {
               DString errorMesssage;            
               addIDITagValue(errorMesssage, I_("broker"), _dstrBrokerCode);
               addIDITagValue(errorMesssage, I_("branch"), _dstrBranchCode);
               ADDCONDITIONFROMFILEIDI(CND::ERR_AGENT_LIST_EMPTY, errorMesssage.c_str());
            }
         }
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::BP_ERR_SEL_BROKER_BRANCH_FIRST);
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN SalesRepProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, _dstrBranchCode);
      setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
      rtn = invokeCommand(this, CMD_GUI_SLSREP, 
         getProcessType(), isModal(), &_rpChildGI);
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

   return rtn;
}

//******************************************************************************
void SalesRepProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   if (bSuccessFlag)
   {
      DString agentCode,
         branchCode;

      getField(rpGICaller, IFASTBP_PROC::AGENT_LIST, 
         ifds::Slsrep, agentCode);
      getField(rpGICaller, IFASTBP_PROC::AGENT_LIST, 
         ifds::BranchCode, branchCode);
      setParameter(I_("AgentCode"), agentCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
      setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, agentCode);
   }
}

//******************************************************************************
bool SalesRepProcess::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{
   return false;
}

//******************************************************************************
SEVERITY SalesRepProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId& idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if (_pAgentList != NULL)
      {
         sevRtn = _pAgentList->getMore();
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return sevRtn;
}

//******************************************************************************
bool SalesRepProcess::doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch)
{
   return (rpGICaller == NULL || _pAgentList == NULL) ? 
      false : _pAgentList->doMoreRecordsExist();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SalesRepProcess.cpp-arc  $
 * 
 *    Rev 1.18   Jul 10 2003 22:20:36   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.17   Mar 21 2003 17:47:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Mar 09 2003 15:56:36   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.15   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Sep 26 2002 11:43:18   KOVACSRO
 * PTS 10009880 : condition split bug fixed.
 * 
 *    Rev 1.13   Sep 04 2002 15:45:46   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.12   Aug 29 2002 16:45:14   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.11   Aug 29 2002 12:54:38   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:25:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   27 Mar 2002 19:55:38   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.8   18 Oct 2001 13:59:32   HSUCHIN
 * minor enhancement to the way the agent list is added to the container
 * 
 *    Rev 1.7   16 Oct 2001 11:20:24   HSUCHIN
 * Implemented GetMore functionality
 * 
 *    Rev 1.6   15 May 2001 15:38:54   YINGZ
 * data group id clean up
 * 
 *    Rev 1.5   03 May 2001 14:05:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   15 Dec 2000 12:43:48   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Oct 18 2000 14:52:06   WINNIE
 * If salesRepByBranch is inactive, system should allow branch be blank and populate the value from AgentList CBO
 * 
 *    Rev 1.2   Sep 28 2000 14:57:26   YINGZ
 * fix empty borker and branch bug
 * 
 *    Rev 1.1   Mar 28 2000 15:44:52   DT24433
 * removed commented line & minor changes
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 14 2000 08:51:20   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.5   Jan 07 2000 15:54:22   POPESCUS
// just checking in...
// 
//    Rev 1.4   Dec 31 1999 13:15:54   POPESCUS
// validations, fixes and misc
// 
//    Rev 1.3   Dec 24 1999 14:18:02   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.2   Dec 22 1999 12:22:54   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.1   Dec 22 1999 11:44:42   ZHANGCEL
// for release
*/
