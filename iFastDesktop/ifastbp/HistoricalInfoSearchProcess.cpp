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
// ^FILE   : HistoricalInfoSearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Feb 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalInfoSearchProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ifastcbo\HistoricalInfoSearchCriteria.hpp"
#include "HistoricalInfoSearchProcess.hpp"
#include "HistoricalInfoSearchProcessincludes.hpp"
#include <bfproc\genericinterfacecontainer.hpp>

extern const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern const I_CHAR* CMD_GUI_HISTORICAL_INFO_SRCH;
extern const I_CHAR* CMD_BPROC_HISTORICAL_INFO_SRCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalInfoSearchProcess > processCreator(CMD_BPROC_HISTORICAL_INFO_SRCH);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "HistoricalInfoSearchProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HistoricalInfoSearchProcess::HistoricalInfoSearchProcess() 
HistoricalInfoSearchProcess::HistoricalInfoSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
, _pHistoricalInfoSearchCriteria(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   //updatable list
   addContainer(IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, false, BF::NullContainerId, true);
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::FundName, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::BrokerCode, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::BrokerName, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::SalesRepCode, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::SalesRepName, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::BranchCode, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::BranchName, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::FundGroup, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
   addFieldDetails(ifds::HistoricalSearchInfo, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA);
}

//******************************************************************************
HistoricalInfoSearchProcess::~HistoricalInfoSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
   if (_pHistoricalInfoSearchCriteria != NULL)
   {
      delete _pHistoricalInfoSearchCriteria;
   }
}  

//************************************************************************************
SEVERITY HistoricalInfoSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *dstcWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      _pHistoricalInfoSearchCriteria = new HistoricalInfoSearchCriteria(*dstcWorkSession);
      if( _pHistoricalInfoSearchCriteria->init(getDataGroupId()) <= WARNING )
      {
         setContainer(IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, _pHistoricalInfoSearchCriteria);
      }
   }
   catch( ConditionException& ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN HistoricalInfoSearchProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand(this, CMD_GUI_HISTORICAL_INFO_SRCH, 
            PROC_NO_TYPE, isModal(), &_rpChildGI);
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
bool HistoricalInfoSearchProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_HISTORICAL_INFO_SRCH);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoSearchProcess.cpp-arc  $
// 
//    Rev 1.4   Mar 21 2003 17:41:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Mar 09 2003 15:55:38   PURDYECH
// Small fixes around DataGroupIds and ContainerIds.
// 
//    Rev 1.2   Mar 05 2003 11:22:42   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.1   Feb 11 2003 14:40:56   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.0   Feb 06 2003 11:53:48   popescu
// Initial revision.
// 
 */
