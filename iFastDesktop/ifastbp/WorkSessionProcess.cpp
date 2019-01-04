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
// ^FILE   : WorkSessionProcess.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/14/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : WorkSessionProcess
//    This class sets the interface for business process subclasses.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "worksessionprocess.hpp"
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfsessn\bfcpsession.hpp>

#include "usersessionprocessincludes.h"
#include <ifastawd\DSTCAWDSession.hpp>


#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< WorkSessionProcess > processCreator( CMD_BPROC_WORK_SESSION                  );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "WorkSessionProcess" );
   const I_CHAR * const SESSIONPTR = I_( "SessionPtr" );
}


namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_COULD_NOT_GET_SUBSESSION;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319WorkSessionProcess::WorkSessionProcess()
WorkSessionProcess::WorkSessionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _dstcWorkSession(NULL) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

WorkSessionProcess::~WorkSessionProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( NULL != _dstcWorkSession )
   {
      _dstcWorkSession->cleanupWorkSession();      
      getBFSession()->getUserSession().freeSession( _dstcWorkSession );
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY WorkSessionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   GenericInterface* rpUserSession = getGIContainer()->findGI( getBFSession(), CMD_BPROC_USER_SESSION );

   if( NULL == rpUserSession )
   {
      assert(0);
      // TODO add a condition.
      return(SEVERE_ERROR);
   }

   try
   {
      DString mgmtCoId;
      rpUserSession->getField( this, SYSTMGMTS, mgmtCoId );

      DSTCUserSession &dstcUserSession = dynamic_cast<DSTCUserSession &>(getBFSession()->getUserSession());
      _dstcWorkSession = &dstcUserSession.createWorkSession( mgmtCoId );

      setWorkSession( _dstcWorkSession, this );          // Save internally
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************

bool WorkSessionProcess::doModelessChildComplete( const Command &cmd )
{  // One of our many children have completed - here we don't care and don't end
   return(false);
}

//******************************************************************************

E_COMMANDRETURN WorkSessionProcess::doProcess()
{  
   TRACE_METHOD( CLASSNAME, DOPROCESS );
   
   BFCPSession* rpParentSession = getParent()->getSession();
   if( NULL != rpParentSession )
   {
      DString dstrSessionPtr = getParent()->getSession()->getSessionData( SESSIONPTR );
      if( dstrSessionPtr.empty() )
      {
		 DSTCAWDSession  *rpSession = new DSTCAWDSession( rpParentSession );
		 rpSession->init( _dstcWorkSession ); 
		  //BFCPSession *rpSession = getParent()->getSession()->createSubSession();
         dstrSessionPtr = asString( (int) rpSession );
         getParent()->getSession()->setSessionData( SESSIONPTR, dstrSessionPtr);
      }
	  else {	  
	  		 DSTCAWDSession  *rpSession = (DSTCAWDSession *) dstrSessionPtr.asInteger();
			 rpSession->associateDSTCWorkSession( _dstcWorkSession, true );
	  }
      BFCPSession *rpSession = (BFCPSession *) dstrSessionPtr.asInteger();
      setSession( rpSession, false );
   }

   return(CMD_MODELESS_INPROCESS);  // We are in process.  Only the user can end
   //  by closing app.
}

//******************************************************************************

SEVERITY WorkSessionProcess::ok2( GenericInterface *rpGI )
{  // User is done with this work session
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );

   getBFWorkSession()->cleanupWorkSession();

   // Free our children
   getGIContainer()->destroyChildren( this );

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************

bool WorkSessionProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage) 
{
   DString dstrMessage( szMessage );
   if( dstrMessage == I_("Session") )
   {
      // End Subsession
///YB      DString dstrSessionPtr = getParent()->getSession()->getSessionData( SESSIONPTR );
//YB      if( !dstrSessionPtr.empty() )
//YB      {
//YB         getParent()->getSession()->endSubSession( getSession() );
//YB         getParent()->getSession()->setSessionData( SESSIONPTR, NULL_STRING);
//YB      }
//YB      setSession( NULL, false );

      // Create Subsession
//YB      BFCPSession *rpSession = getParent()->getSession()->createSubSession();
//YB      dstrSessionPtr = asString( (int) rpSession );
//YB      getParent()->getSession()->setSessionData( SESSIONPTR, dstrSessionPtr);
//YB      setSession( rpSession, false );

      return(true);
   }
   return(false);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/WorkSessionProcess.cpp-arc  $
 * 
 *    Rev 1.36   Jan 05 2005 12:02:18   hernando
 * PTS10036549 - Possibly fix a rare error in production -- current business area not correct when setting the AWD object.  This is related to PTS10035445.
 * 
 *    Rev 1.35   Jan 12 2004 14:38:50   YINGBAOL
 * PET 987: Change AWDSession
 * 
 *    Rev 1.34   Mar 21 2003 17:50:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.33   Oct 09 2002 23:53:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.32   Aug 29 2002 16:45:20   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.31   Aug 29 2002 12:54:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.30   May 28 2002 12:18:04   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.29   22 May 2002 18:25:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.28   08 Apr 2002 15:12:00   SMITHDAV
 * Check existance of parent session in doProcess() before using it.
 * 
 *    Rev 1.27   Apr 03 2002 18:42:32   HERNANDO
 * Changed use of Subsession.  Added doSend to end/create Subsession.
 * 
 *    Rev 1.26   27 Mar 2002 19:56:26   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.25   Mar 20 2002 17:32:26   HERNANDO
 * Temporary Fix - Create empty AWD Work Object on ok2.
 * 
 *    Rev 1.24   13 Mar 2002 18:22:12   SMITHDAV
 * Check the existance of a "Session" for the process before using it.
 * 
 *    Rev 1.23   Mar 07 2002 17:10:32   HERNANDO
 * Clean up - attempt to create AWDInterface if dstrAwdSourcePtr not empty.
 * 
 *    Rev 1.22   Mar 07 2002 14:56:10   HERNANDO
 * Clear the AWD Container in Ok2.
 * 
 *    Rev 1.21   Mar 07 2002 11:57:34   HERNANDO
 * Removed the subsession.
 * 
 *    Rev 1.20   Feb 25 2002 18:54:24   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.19   Oct 17 2001 15:10:40   FENGYONG
 * fix system gone when company id not correct 
 * 
 *    Rev 1.18   15 Oct 2001 12:03:46   KOVACSRO
 * It's not necessary to refresh user acces list when creating a new worksession.
 * 
 *    Rev 1.17   27 Aug 2001 16:03:14   SMITHDAV
 * catch exceptions and handle in doInit().
 * 
 *    Rev 1.16   11 Jul 2001 12:20:44   SMITHDAV
 * Fix Global Session cleanup problems.
 * 
 *    Rev 1.15   09 Jul 2001 15:25:06   SMITHDAV
 * Mgmt company refresh related changes.
 * 
 *    Rev 1.14   15 Jun 2001 13:59:00   HSUCHIN
 * bug fix on destructor
 * 
 *    Rev 1.13   14 Jun 2001 12:00:14   SMITHDAV
 * Fixed worksession cleanup problems.
 * 
 *    Rev 1.12   03 May 2001 14:05:48   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   15 Dec 2000 12:43:58   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.10   Oct 05 2000 13:59:24   HERNANDO
 * Create new subsession upon killing a subsession.
 * 
 *    Rev 1.9   Sep 28 2000 18:17:48   HERNANDO
 * Fixed bug - dangling pointer after subsession killed
 * 
 *    Rev 1.8   Sep 26 2000 11:21:32   VASILEAD
 * Check if there is any master Session created
 * 
 *    Rev 1.7   Sep 25 2000 15:40:24   VASILEAD
 * Got back to the original implementation of doProcess()
 * 
 *    Rev 1.6   Sep 19 2000 15:20:42   VASILEAD
 * Cleanup services, UserSeesionProcess and security object
 * 
 *    Rev 1.5   Apr 15 2000 15:04:24   BUZILA
 * if we are destroying WorkSessionDetails we are not able to find the user session for lists that are at MgmtCo level
 * Ex: FundGroupList
 * 
 *    Rev 1.4   Apr 13 2000 08:59:28   BUZILA
 * we want to cleanup the WSDetails repository on ok and destroy it on WSproc destructor
 * 
 *    Rev 1.3   Apr 12 2000 08:20:06   BUZILA
 * calling BFSessionManager::removeWorkSession( ) instead of BFSessionManager::cleanupWorkSession( ) in ok2() in order to destroy the workSessionDetails object
 * 
 *    Rev 1.2   Apr 04 2000 17:58:00   DT24433
 * changed to use getGIContainer
 * 
 *    Rev 1.1   Mar 21 2000 10:39:00   DT24433
 * changed to set worksessionid during doInit so it's available to GenericInterfaceContainer
 * 
 *    Rev 1.0   Feb 15 2000 10:59:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 14 2000 14:43:26   HSUCHIN
 * sync up with cdn for security and mgmt co quick change
 * 
 *    Rev 1.7   Dec 10 1999 10:25:28   HSUCHIN
 * bug fix
 * 
 *    Rev 1.6   Dec 05 1999 18:58:18   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.5   Oct 29 1999 14:50:10   DT24433
 * changed doOk to ok2
 * 
 *    Rev 1.4   Aug 04 1999 12:27:32   DT24433
 * Updated for field details changes
 * 
 *    Rev 1.3   Jul 20 1999 11:14:20   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 13 1999 17:22:34   HSUCHIN
 * changed procedure ok to not end all subsession
 * 
 *    Rev 1.1   Jul 08 1999 10:02:18   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
