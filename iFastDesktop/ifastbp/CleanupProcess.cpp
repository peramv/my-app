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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CleanupProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 23/06/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CleanupProcess
//    This class does the cleanup of the singletons
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "cleanupprocess.hpp"
#include <bfcbo\bfnotification.hpp>
#include <ifastdbrkr\dstchost.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CLEANUP;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< CleanupProcess > processCreator( CMD_BPROC_CLEANUP );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "CleanupProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319CleanupProcess::CleanupProcess()
CleanupProcess::CleanupProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

CleanupProcess::~CleanupProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY CleanupProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

E_COMMANDRETURN CleanupProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      DString logoutMessage;
      //make sure that we would log off
      getBFSession()->getUserSession().logoff( DSTCHost::getPrimaryHost(), logoutMessage );

      BFNotification::killInstance();
      rtn = CMD_OK;
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CleanupProcess.cpp-arc  $
 * 
 *    Rev 1.12   27 Sep 2007 14:16:28   kovacsro
 * restored rev 1.9 (moved the active batch logic into a new process)
 * 
 *    Rev 1.9   Mar 21 2003 17:37:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 16:44:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.6   Aug 29 2002 12:54:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:24:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   27 Mar 2002 19:54:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   03 May 2001 14:05:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   06 Feb 2001 11:48:24   SMITHDAV
 * Removed unused code and depenencies
 * 
 *    Rev 1.1   15 Dec 2000 12:43:22   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 19 2000 10:12:00   BUZILA
 * refresh stuf
 * 
 *    Rev 1.7   Dec 12 1999 17:48:02   POPESCUS
 * cleaned-up the dstcdatabroker
 * 
 *    Rev 1.6   Oct 28 1999 18:06:42   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.5   Oct 18 1999 11:37:30   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.4   Aug 20 1999 17:57:26   POPESCUS
 * Added logout message
 * 
 *    Rev 1.3   Aug 17 1999 16:19:42   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.2   Jul 20 1999 11:13:58   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

