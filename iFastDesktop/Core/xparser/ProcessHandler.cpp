/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "ProcessHandler.hpp"
#include "Process.hpp"
#include "ClassAttribute.hpp"
#include "TxnStatWriter.hpp"
#include "ExecutionResult.hpp"

#include <bfproc\AbstractProcess.hpp>
#include <bfproc\GenericInterfaceContainer.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("ProcessHandler");
}

namespace CND
{
   extern const long XP_UNKNOWN_EXCEPTION;
}

//******************************************************************************
ProcessHandler::ProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes )
: ElementHandler( parentHandler, elementName, ClassAttribute::PROCESS )
, _action( attributes )
, _parmList()
, _cboList()
, _processList()
, _docPos()
{
}

//******************************************************************************
// top level process execution
void ProcessHandler::execute( xp::UserSessionProcess &usProcess, BFDocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );
   StatusWriter status(out, result);

   try
   {
      if ( requiresWorkSession() ) {
         // create work session
         setWorkSessionParms( usProcess.getProcessImpl() );
         WorkSessionProcess wsProcess( usProcess );

         RADocument subDoc( out ); // random access document will write to 'out' automatically
         executeRaw( wsProcess, subDoc, result );
         writeCommitConditions( wsProcess.getProcessImpl(), subDoc, result );
         writeCommitData( wsProcess, subDoc );
         wsProcess.commit();
         status.setSuccess();
      } else {
         RADocument subDoc( out ); // random access document will write to 'out' automatically
         executeRaw( usProcess, subDoc, result );
         status.setSuccess();
      }
   } // make sure all exception are handled here
   catch( ElementFailure &ef )
   {
      throw ef; // pass through to batch level
   }
   catch( ConditionException &ce )
   {
      writeCondition( ce.getCondition(), out, result );
      throw ElementFailure(this); // throw to batch level
   }
   catch( CONDITIONVECTOR &cv )
   {

      CONDITIONVECTOR::iterator iter = cv.begin();
      while ( iter != cv.end() ) {
         Condition *cnd = (*iter);
         cnd->prepareMessage( ClientLocaleContext::get() );
         writeCondition( *cnd, out, result );
         delete cnd;
         iter = cv.erase(iter);
      }

      throw ElementFailure(this); // throw to batch level
   }
   catch( ... )
   {
      writeCondition( Condition( CND::XPARSER_CONDITION,
                                 I_("ProcessHandler::execute"),
                                 CND::XP_UNKNOWN_EXCEPTION,
                                 CM_STRINGIFY( CND::XP_UNKNOWN_EXCEPTION ),
                                 __FILE__, __LINE__, FALSE,
                                 g_conditionManager.getPath() ), out, result );
      // write an error
      throw ElementFailure(this); // throw to batch level
   }

}

//******************************************************************************
// sub-process execution
void ProcessHandler::execute( Process &parentProcess, RADocument &out, ProcessResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );
   StatusWriter status(out, result);

   try
   {
      executeRaw( parentProcess, out, result );
      status.setSuccess();
   }
   catch( ConditionException &ce )
   {
      writeCondition( ce.getCondition(), out, result );
      throw ElementFailure(this); // throw to batch level
   } // let all other exceptions be handled by top level process.

}

//******************************************************************************
void ProcessHandler::executeRaw( Process &parentProcess, RADocument &out, ProcessResult &result )
{
   MAKEFRAME2( CND::XPARSER_CONDITION, CLASSNAME, I_("executeRaw") );

   // set all parameters
   setProcessParms( parentProcess.getProcessImpl() );
   _parmList.execute( parentProcess.getGIContainer(), out );

   // create process
   Process process( parentProcess,
                    getName(),
                    ignoreWarnings(),
                    _action == PROC_ACTION_VALIDATE_ONLY );
   PROMOTECONDITIONS();

   // execute sub-processes
   _cboList.execute( process.getProcessImpl(), out, result );
   _processList.execute( process, out, result );

   getProcessParms( process.getProcessImpl() );

   bool blProcessSuccess =  requiresWorkSession() ? process.commit()
                                                  : true;
   PROMOTECONDITIONS();

   SEVERITY severity = ConditionManager::getInstance()->getMaxSeverity( MYFRAME(), TRUE );
   writeConditions(MYFRAME(), out, result);

   if( blProcessSuccess == false ) 
   {
      if( severity > WARNING || ( severity == WARNING && !ignoreWarnings() ) ) 
      {
         throw ElementFailure(this); // throw to batch level
      }
   }

   _docPos =  out.tellPosition(); // store the current doc position

}

//******************************************************************************
void ProcessHandler::writeCommitData( WorkSessionProcess &wsProcess, RADocument &out )
{
   out.seekPosition( _docPos ); // restore doc position
   writeCommitParms( wsProcess.getProcessImpl(), out );

   _cboList.writeCommitData( wsProcess, out );
   _processList.writeCommitData( wsProcess, out );
}

//******************************************************************************
void ProcessHandler::addHandler( ParmHandler *handler )
{
   _parmList.add( handler );
}

//******************************************************************************
void ProcessHandler::addHandler( CBOHandler *handler )
{
   _cboList.add( handler );
}

//******************************************************************************
void ProcessHandler::addHandler( ProcessHandler *handler )
{
   _processList.add( handler );
}

//******************************************************************************
ElementAttributeList &ProcessHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( getElementClass() );
   attributes.add( _action );
   return(attributes);
}

//******************************************************************************
void ProcessHandlerList::execute( xp::UserSessionProcess &usProcess, BFDocument &out, BatchResult &result )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->execute( usProcess, out, result.createProcessResult((*i)->getAction()));
      i++;
   }
}

//******************************************************************************
void ProcessHandlerList::execute( Process &parentProcess, RADocument &out, ProcessResult &result )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->execute( parentProcess, out, result );
      i++;
   }
}

//******************************************************************************
void ProcessHandlerList::writeCommitData( WorkSessionProcess &wsProcess, RADocument &out )
{
   iterator i = begin();
   while( i != end() )
   {
      (*i)->writeCommitData( wsProcess, out );
      i++;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/xparser/ProcessHandler.cpp-arc  $
//
//   Rev 1.32   Sep 23 2009 01:24:50   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.31   Apr 27 2005 13:02:26   smithdav
//Fix bug in which CONDITIONVECTOR is thrown with pointers to conditions that are destroyed before they are caught.
//
//   Rev 1.30   Apr 26 2005 11:38:18   smithdav
//Fix bug in which a process initialization warning is not being displayed.
//
//   Rev 1.29   Apr 22 2005 17:23:26   smithdav
//Replaced writeAdditionalCondtions overried with writeCommitConditions which is called only after commit of the top level process.
//
//   Rev 1.27   Apr 12 2005 12:36:14   smithdav
//Added new overrodable method called writeAdditionalConditions.
//
//   Rev 1.26   Mar 18 2005 10:18:30   smithdav
//Fix call to executeCommit.
//
//   Rev 1.25   Mar 17 2005 13:39:42   popescu
//Fix bug in which errors were being reported for successful processes.
//
//   Rev 1.24   Mar 08 2005 08:21:16   smithdav
//Modify code so that the "Successful" element under the process is after all conditions.
//
//   Rev 1.23   Jan 27 2005 15:49:26   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.22   May 14 2004 16:15:50   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.21   May 10 2004 13:56:58   SMITHDAV
//Add support for user session level processes -  no work session!!
//
//   Rev 1.20   Mar 09 2004 11:01:12   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.19   Mar 05 2004 13:28:34   SMITHDAV
//Fix stupid class initialization bugs.
// 
//    Rev 1.18   Jan 14 2003 11:05:30   PURDYECH
// DataGroupid parentage knowledge
// 
//    Rev 1.17   Dec 18 2002 11:23:34   SMITHDAV
// Fixed Process initiation error problem.
// 
//    Rev 1.16   Oct 09 2002 17:43:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.15   Oct 03 2002 18:42:54   IVESPAUL
// Added code to support validateOnly process action.
//
//    Rev 1.14   Sep 25 2002 09:21:22   IVESPAUL
// Write out all conditions not just > WARNING.
//
//    Rev 1.13   Sep 23 2002 19:20:46   IVESPAUL
// Added 'Successful' Element.
//
//    Rev 1.12   Sep 23 2002 18:29:18   SMITHDAV
// Process HighestSeverity changes.
//
//    Rev 1.11   Sep 19 2002 09:28:38   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.10   Aug 30 2002 09:39:32   SMITHDAV
// Remove unneeded header include.
//
//    Rev 1.9   Aug 06 2002 12:00:32   SMITHDAV
// Handle commit conditions.
//
//    Rev 1.8   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.7   Jul 29 2002 14:13:12   SMITHDAV
// Initialize processes with "ignoreWarningOnOk2" state when appropriate.
//
//    Rev 1.6   Jul 04 2002 15:22:40   SMITHDAV
// Class default handling and minor interface changes.
//
//    Rev 1.5   Jul 03 2002 10:53:16   SMITHDAV
// Add over-ridable method getProcessParams() to get process output parameters.
//
//    Rev 1.4   07 Jun 2002 17:08:58   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.3   16 May 2002 11:55:46   SMITHDAV
// Process changes to add xp::WorkSessionProcess
// and xp::UserSessionProcess classes and make
// top level process modeless.
//
//    Rev 1.2   14 May 2002 16:42:58   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.1   01 May 2002 17:16:50   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.0   02 Apr 2002 13:50:06   SMITHDAV
// Initial revision.
 *
 */