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
#include "RootHandler.hpp"
#include "Process.hpp"
#include "ExecutionResult.hpp"
#include "TxnStatWriter.hpp"
#include <bfutil\TxnStats.hpp>
#include <bfproc\GenericInterfaceContainer.hpp>
#include <bfproc\InterProcessData.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("RootHandler");
}

namespace CND
{
   extern const long XP_UNKNOWN_EXCEPTION;
}

//******************************************************************************
RootHandler::RootHandler( const DString &elementName, xercesc::AttributeList &attributes )
: CacheEnabledElementHandler( elementName )
, _traceFilename( attributes )
, _writeStats( I_("writeStats"), attributes, false )
, _verboseConditions( I_("verboseConditions"), attributes, false )
, _fieldFormatting( I_("fieldFormatting"), attributes, true )
, _viewTimings( I_( "viewTimings" ), attributes, false )
, _parmList()
, _batchList()
{
   setWriteStats( _writeStats );
   setVerboseConditions( _verboseConditions );
   setFieldFormatting( _fieldFormatting );
}

//******************************************************************************
RootHandler::RootHandler( const DString &elementName )
: CacheEnabledElementHandler( elementName )
, _traceFilename()
, _writeStats( I_("writeStats"), false, false )
, _verboseConditions( I_("verboseConditions"), false, false )
, _fieldFormatting( I_("fieldFormatting"), true, true )
, _viewTimings( I_( "viewTimings" ), false, false )
, _parmList()
, _batchList()
{
   setWriteStats( _writeStats );
   setVerboseConditions( _verboseConditions );
   setFieldFormatting( _fieldFormatting );
}

//******************************************************************************
void RootHandler::execute( BFDocument &out, ExecutionResult &result )
{
   MAKEFRAMEAUTOPROMOTE2( CND::XPARSER_CONDITION, CLASSNAME, I_("execute") );

   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );
   TxnStatWriter statWriter( out, !writeStats() );

   if( _viewTimings )
   {
      TxnStats::get()->enable( true );
   }

   GenericInterfaceContainer gic;

   try
   {
      StatusWriter status( out, result );

      // set all parameters to the gic
      setUserSessionParms( gic );
      _parmList.executeAndCache( gic, out );
      gic.getInterProcessData().setParameter( I_("XML_API"), I_("Y") );

      // create the user session process and execute batches if successful
      UserSessionProcess usProcess( gic );
      if( !usProcess.commit() )
      {
         SEVERITY severity = ConditionManager::getInstance()->getMaxSeverity( MYFRAME(), TRUE );
         writeConditions(MYFRAME(), out, result);

         if( severity > WARNING || ( severity == WARNING && !ignoreWarnings() ) )
         {
            throw ElementFailure(this); // throw to batch level
         }
      }

      writeParms( usProcess.getProcessImpl(), out ); // write additional params to output document

      bool batchListSuccess = _batchList.execute( usProcess, out, result );

      logoff( usProcess.getProcessImpl() );

      if( batchListSuccess )
      {
         status.setSuccess();
      }
   }
   catch( ElementFailure & )
   {
   }
   catch( ConditionException &ce )
   {
      writeCondition( ce.getCondition(), out, result );
   }
   catch( ... )
   {
      writeCondition( Condition( CND::XPARSER_CONDITION,
                                 I_("RootHandler::execute"),
                                 CND::XP_UNKNOWN_EXCEPTION,
                                 CM_STRINGIFY( CND::XP_UNKNOWN_EXCEPTION ),
                                 __FILE__, __LINE__, FALSE,
                                 g_conditionManager.getPath() ), out, result );
   }

}

//******************************************************************************
void RootHandler::executeCondition( const Condition& condition, BFDocument &out, ExecutionResult &result )
{
   Writer writer( *this, out );
   StatusWriter status( out, result );
   writeCondition( condition, out, result );
}

//******************************************************************************
ElementAttributeList &RootHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( _writeStats );
   attributes.add( _verboseConditions );
   attributes.add( _fieldFormatting );
   attributes.add( _viewTimings );
   attributes.add( _traceFilename );

   return(attributes);
}

//******************************************************************************
void RootHandler::addHandler( ParmHandler *handler )
{
   _parmList.add(handler);
}

//******************************************************************************
void RootHandler::addHandler( BatchHandler *handler )
{
   _batchList.add(handler);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/xparser/RootHandler.cpp-arc  $
//
//   Rev 1.18   Sep 23 2009 01:23:56   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.17   Mar 16 2005 16:41:50   smithdav
//Add StatusWriter to the executeCondition method.
//
//   Rev 1.16   Jan 27 2005 15:49:30   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.15   May 14 2004 16:16:32   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.14   Mar 09 2004 11:01:22   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.13   Mar 05 2004 13:28:36   SMITHDAV
//Fix stupid class initialization bugs.
// 
//    Rev 1.12   Dec 18 2002 11:22:40   SMITHDAV
// Fixed Process initiation error problem.
// 
//    Rev 1.11   Oct 09 2002 17:43:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.10   Oct 08 2002 10:29:40   IVESPAUL
// Added 'Successful' element to both Batch and Package levels.
//
//    Rev 1.9   Sep 19 2002 09:28:40   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.8   Sep 12 2002 17:43:40   SMITHDAV
// Add error handling for logon...
//
//    Rev 1.7   Sep 03 2002 18:03:50   IVESPAUL
// Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//    Rev 1.6   Aug 14 2002 12:17:04   SMITHDAV
// Fix class attribute defaulting logic.
//
//    Rev 1.5   Aug 02 2002 17:13:40   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.4   07 Jun 2002 17:08:58   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.3   16 May 2002 11:55:46   SMITHDAV
// Process changes to add xp::WorkSessionProcess
// and xp::UserSessionProcess classes and make
// top level process modeless.
//
//    Rev 1.2   14 May 2002 16:43:00   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.1   01 May 2002 17:16:50   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.0   02 Apr 2002 13:50:08   SMITHDAV
// Initial revision.
 *
 */
