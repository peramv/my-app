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
// ^FILE   : ProtectedFundProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ProtectedFundProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ProtectedFundProcess.hpp"
#include "ProtectedFundProcessincludes.hpp"
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PROTECTED_FUND;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PROTECTED_FUND;
static ConcreteProcessCreator< ProtectedFundProcess > processCreator( CMD_BPROC_PROTECTED_FUND );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ProtectedFundProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const PFF;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ProtectedFundProcess::ProtectedFundProcess() 
ProtectedFundProcess::ProtectedFundProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
, _pProtectedFundList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //updatable list
   addContainer(IFASTBP_PROC::PROTECTED_FUND_LIST, true, BF::NullContainerId, true);

   addFieldDetails(ifds::ProtectedFundRId, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::EffectiveDate, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::StopDate, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::InsurCode, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::InsurCost, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ContractGapType, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ResetsAllowed, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::MaturityYears, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ModDate, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ModUser, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::Username, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::ProcessDate, IFASTBP_PROC::PROTECTED_FUND_LIST);
   addFieldDetails(ifds::FundNumber, IFASTBP_PROC::PROTECTED_FUND_LIST);
}

//******************************************************************************
ProtectedFundProcess::~ProtectedFundProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   //do not delete the list here since it belongs to the worksession
   _rpChildGI = NULL;
}

//************************************************************************************
SEVERITY ProtectedFundProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( dstcWorkSession->getProtectedFundList(_pProtectedFundList) <= WARNING )
      {
         setContainer( IFASTBP_PROC::PROTECTED_FUND_LIST, _pProtectedFundList );
      }
   }
   catch( ConditionException& ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN ProtectedFundProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_PROTECTED_FUND, 
            PROC_NO_TYPE, isModal(), &_rpChildGI );
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
bool ProtectedFundProcess::setCommitDataGroupAsHost()
{
   return(true);
}


//******************************************************************************
SEVERITY ProtectedFundProcess::getHistoricalParameters(const BFContainerId& idContainer, 
   BFFieldId &recordIdField, DString& tableId, DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );
   
   if (idContainer == IFASTBP_PROC::PROTECTED_FUND_LIST)
   {
      recordIdField = ifds::ProtectedFundRId;
      tableId = AUDITTYPE::PFF;
      dstrKeys = NULL_STRING;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ProtectedFundProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_PROTECTED_FUND );
}

//******************************************************************************

SEVERITY ProtectedFundProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProtectedFundProcess.cpp-arc  $
// 
//    Rev 1.9   Mar 10 2004 13:18:56   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.8   Aug 18 2003 16:10:12   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.7   Mar 21 2003 17:46:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 09 2003 15:56:24   PURDYECH
// Small fixes around DataGroupIds and ContainerIds.
// 
//    Rev 1.5   Mar 05 2003 11:22:48   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.4   Jan 28 2003 13:15:52   popescu
// Historical Info feature implementation
// 
//    Rev 1.3   Jan 22 2003 15:52:34   popescu
// Fixes related with not being able to commit the changes to backend if the dialog ProtectedFundDialog is modal
// 
//    Rev 1.2   Jan 20 2003 15:43:26   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
//    Rev 1.1   Jan 10 2003 10:08:28   popescu
// Process skeltons, for now
// 
//    Rev 1.0   Jan 09 2003 16:10:40   popescu
// Initial revision.
 * 
 *
 */
