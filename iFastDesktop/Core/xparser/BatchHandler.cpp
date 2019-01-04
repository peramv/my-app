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
#include "BatchHandler.hpp"
#include "TxnStatWriter.hpp"
#include "ExecutionResult.hpp"

using namespace xp;

//******************************************************************************
BatchHandler::BatchHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
CacheEnabledElementHandler( parentHandler, elementName, ClassAttribute::BATCH ),
_id( attributes ),
_ignoreWarnings( I_("ignoreWarnings"), attributes, false ),
_timing( I_( "timing" ), attributes, false ),
_retry ( I_( "retry" ), attributes, true),
_processList()
{
   setIgnoreWarnings( _ignoreWarnings );
   setRetry( _retry );
}

//******************************************************************************
bool BatchHandler::execute( UserSessionProcess &usProcess, BFDocument &out, BatchResult &result )
{
   Writer writer( *this, out );
   ElementTimeWriter timeWriter( out, !writeStats() );

   try
   {
      StatusWriter status( out, result );
      _parmList.executeAndCache( out );
      _processList.execute( usProcess, out, result );
      status.setSuccess();
      return( true );
   }
   catch( ElementFailure & )
   {
   }
   catch( ... )
   {
      // should be caught by top level process
      assert(0);
   }

   return( false );
}

//******************************************************************************
void BatchHandler::addHandler( ParmHandler *handler )
{
   _parmList.add( handler );
}

//******************************************************************************
void BatchHandler::addHandler( ProcessHandler *handler )
{
   _processList.add( handler );
}

//******************************************************************************
ElementAttributeList &BatchHandler::getAttributes( ElementAttributeList &attributes ) const
{
   attributes.add( _id );
   attributes.add( _ignoreWarnings );
   attributes.add( _timing );
   attributes.add( _retry );
   
   return(attributes);
}

//******************************************************************************
bool BatchHandlerList::execute( UserSessionProcess &usProcess, BFDocument &out, ExecutionResult &result )
{
   bool successful = true; // assume all ok to start with

   iterator i = begin();
   while( i != end() )
   {
      // and all the result flags to together...
      successful = (*i)->execute( usProcess, out, result.createBatchResult() ) && successful;
      i++;
   }

   return( successful );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/BatchHandler.cpp-arc  $
//
//   Rev 1.21   Nov 10 2005 18:01:16   FENGYONG
//Incident 386579 - Add attribute to API batch level
//
//   Rev 1.20   Feb 01 2005 14:59:46   smithdav
//Minor ExecutionResult fixes and tweeks. 
//
//   Rev 1.19   Jan 27 2005 15:49:40   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.18   May 14 2004 16:15:12   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.17   Mar 09 2004 10:59:14   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.16   Mar 05 2004 13:28:16   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.15   Jan 21 2004 11:07:16   SMITHDAV
//Fix bug that prevented batches being processed if previous batches have failed.
// 
//    Rev 1.14   Oct 09 2002 17:43:06   PURDYECH
// New PVCS Database
// 
//    Rev 1.13   Oct 08 2002 10:29:16   IVESPAUL
// Added 'Successful' element to both Batch and Package levels.
//
//    Rev 1.12   Sep 19 2002 09:28:28   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.11   Aug 02 2002 17:13:38   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.10   07 Jun 2002 17:08:56   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.9   16 May 2002 11:55:44   SMITHDAV
// Process changes to add xp::WorkSessionProcess
// and xp::UserSessionProcess classes and make
// top level process modeless.
//
//    Rev 1.8   14 May 2002 16:42:52   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.7   01 May 2002 17:16:46   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.6   02 Apr 2002 12:58:08   SMITHDAV
// Change the way XML processing is handled.
//
//    Rev 1.5   24 Jul 2001 20:08:08   PURDYECH
// Support the SaxStateManagerFactory to create the SaxStateManager
//
//    Rev 1.4   Feb 09 2001 14:13:24   YINGZ
// add dstxparser project
//
//    Rev 1.3   Dec 18 2000 15:15:22   YINGZ
// add temp support to show purchase return values
//
//    Rev 1.2   Dec 08 2000 13:50:04   YINGZ
// performance
//
//    Rev 1.1   Dec 07 2000 13:31:24   YINGZ
// check in for check out 8))
//
//    Rev 1.0   Nov 08 2000 13:18:44   YINGZ
// Initial revision.
 *
 */