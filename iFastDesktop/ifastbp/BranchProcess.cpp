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
// ^FILE   : BranchProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 12/15/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BranchProcess
//    This class manages the Branch information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "branchprocess.hpp"
#include "branchprocessincludes.h"
#include <ifastcbo\branchlist.hpp>
#include "mfcaninterprocparam.hpp"

//headers of the views
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BRANCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BRANCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BranchProcess > processCreator(CMD_BPROC_BRANCH);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("BranchProcess");
   const I_CHAR * const PERFORMSEARCH = I_("performSearch");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long ERR_BRANCH_LIST_EMPTY;
   extern const long BP_ERR_SEL_BROKER_FIRST;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
BranchProcess::BranchProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
_rpChildGI(0), 
_pBranchList(NULL),
_dstrCaller(NULL_STRING),
_dstrBrokerCode(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::BRANCH_LIST, true);
   addFieldDetails(ifds::BranchCode, IFASTBP_PROC::BRANCH_LIST);
   addFieldDetails(ifds::BranchName, IFASTBP_PROC::BRANCH_LIST);
   addFieldDetails(ifds::PayInstrComm, IFASTBP_PROC::BRANCH_LIST);
   addFieldDetails(ifds::PayInstrTrailer, IFASTBP_PROC::BRANCH_LIST);
}

//******************************************************************************
BranchProcess::~BranchProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pBranchList)
   {
      delete _pBranchList;
      _pBranchList = NULL;
   }
}

//******************************************************************************
SEVERITY BranchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
      getParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      if (_dstrBrokerCode.strip() != NULL_STRING)
      {
         _pBranchList = new BranchList(*getBFWorkSession());
         sevRtn = _pBranchList->init(_dstrBrokerCode, NULL_STRING);
         if (sevRtn <= WARNING)
         {
            BFObjIter branchListIter(*_pBranchList, getDataGroupId());
            if (branchListIter.getNumberOfItemsInList() > 0)
            {
               setContainer(IFASTBP_PROC::BRANCH_LIST, _pBranchList);
            }
            else
            {
               DString errorMesssage;

               addIDITagValue(errorMesssage, I_("broker"), _dstrBrokerCode);
               ADDCONDITIONFROMFILEIDI(CND::ERR_BRANCH_LIST_EMPTY, 
                  errorMesssage.c_str());
            }
         }
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::BP_ERR_SEL_BROKER_FIRST);
      }
   }
   catch (ConditionException &ce)
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
E_COMMANDRETURN BranchProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::CALLER, _dstrCaller);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
      rtn = invokeCommand(this, CMD_GUI_BRANCH, 
         getProcessType(), isModal(), &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool BranchProcess::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{
   return false;
}

//******************************************************************************
bool BranchProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_BRANCH;
}

//******************************************************************************
void BranchProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   if (bSuccessFlag)
   {
      DString dstrBranchCode;

      getField(rpGICaller, IFASTBP_PROC::BRANCH_LIST, 
         ifds::BranchCode, dstrBranchCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode);
   }
}

//******************************************************************************
SEVERITY BranchProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId& idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if (_pBranchList != NULL)
      {
         sevRtn = _pBranchList->getMore();
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return sevRtn;
}

//******************************************************************************
bool BranchProcess::doMoreRecordsExist(GenericInterface *rpGICaller, 
   const BFContainerId& idSearch)
{
   return (rpGICaller == NULL || _pBranchList == NULL) ? 
      false : _pBranchList->doMoreRecordsExist();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BranchProcess.cpp-arc  $
 * 
 *    Rev 1.16   Jul 10 2003 22:19:12   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.15   Mar 21 2003 17:36:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Mar 07 2003 11:56:14   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.13   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Sep 26 2002 11:42:38   KOVACSRO
 * PTS 10009880 : condition split bug fixed.
 * 
 *    Rev 1.11   Sep 04 2002 15:45:44   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.10   Aug 29 2002 16:42:46   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.9   Aug 29 2002 12:54:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   Jul 31 2002 16:14:42   HERNANDO
 * More button implementation.
 * 
 *    Rev 1.7   22 May 2002 18:24:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   27 Mar 2002 19:54:42   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.5   15 May 2001 15:38:40   YINGZ
 * data group id clean up
 * 
 *    Rev 1.4   03 May 2001 14:05:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   15 Dec 2000 12:43:20   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.2   Sep 28 2000 14:57:08   YINGZ
 * fix empty broker code bug
 * 
 *    Rev 1.1   Mar 06 2000 16:52:00   DT24433
 * removed substitutelist and unused headers
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Jan 14 2000 08:51:20   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.7   Jan 11 2000 08:41:36   POPESCUS
// fixes and validation
// 
//    Rev 1.6   Jan 07 2000 15:54:20   POPESCUS
// just checking in...
// 
//    Rev 1.5   Jan 06 2000 12:52:06   POPESCUS
// fixes for validation
// 
//    Rev 1.4   Dec 31 1999 13:15:52   POPESCUS
// validations, fixes and misc
// 
//    Rev 1.3   Dec 24 1999 14:18:00   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.2   Dec 22 1999 12:22:46   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.1   Dec 22 1999 11:44:28   ZHANGCEL
// for release
*/
