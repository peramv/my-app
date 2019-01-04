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
// ^FILE   : MgmtCoRefreshProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MgmtCoRefreshProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtcorefreshprocess.hpp"
#include "mgmtcorefreshprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MGMT_CO_REFRESH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MgmtCoRefreshProcess > processCreator( CMD_BPROC_MGMT_CO_REFRESH );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "InterestAccrualProcess" );
   const I_CHAR * const COMPANY_ID = I_( "CompanyId" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319MgmtCoRefreshProcess::MgmtCoRefreshProcess()
MgmtCoRefreshProcess::MgmtCoRefreshProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _dstrCompanyId()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
MgmtCoRefreshProcess::~MgmtCoRefreshProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY MgmtCoRefreshProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParameter( COMPANY_ID, _dstrCompanyId );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN MgmtCoRefreshProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_MODELESS_INPROCESS;

   try
   {
      DSTCGlobalSession &globalSession = dynamic_cast<DSTCGlobalSession &>(getBFSession()->getGlobalSession());

      if( globalSession.refreshMgmtCo( _dstrCompanyId ) >WARNING )
         rtn = CMD_FAILURE;
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
      rtn = CMD_FAILURE;
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MgmtCoRefreshProcess.cpp-arc  $
// 
//    Rev 1.9   Mar 21 2003 17:45:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Mar 09 2003 15:56:20   PURDYECH
// Small fixes around DataGroupIds and ContainerIds.
// 
//    Rev 1.7   Oct 09 2002 23:53:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:45:08   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:24:50   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   27 Mar 2002 19:55:30   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.2   14 Aug 2001 15:04:26   SMITHDAV
// Fix error handling.
// 
//    Rev 1.1   27 Jul 2001 14:38:04   SMITHDAV
// Fix Refresh.
// 
//    Rev 1.0   09 Jul 2001 15:27:28   SMITHDAV
// Initial revision.
 */
