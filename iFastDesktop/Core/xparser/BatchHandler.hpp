#pragma once

#include <xparser\cacheenabledelementhandler.hpp>
#include <xparser\idattribute.hpp>
#include <xparser\booleanattribute.hpp>
#include <xparser\parmhandler.hpp>
#include <xparser\processhandler.hpp>

namespace xp
{
   class UserSessionProcess;
   class ExecutionResult;
   class BatchResult;

   //******************************************************************************
   class BatchHandlerList : public ElementHandlerList<class BatchHandler *>
   {
   public:
      bool execute( UserSessionProcess &usProcess, BFDocument &out, ExecutionResult &result );
   };

   //******************************************************************************
   class BatchHandler : public CacheEnabledElementHandler
   {
   public:
      BatchHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

      bool execute( UserSessionProcess &usProcess, BFDocument &out, BatchResult &result );

      virtual void addHandler( ParmHandler *handler );
      virtual void addHandler( ProcessHandler *handler );

      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   private:

      const IdAttribute _id;
      const BooleanAttribute _ignoreWarnings;
      const BooleanAttribute _timing;
	  const BooleanAttribute _retry;

      ParmHandlerList _parmList;
      ProcessHandlerList _processList;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/BatchHandler.hpp-arc  $
//
//   Rev 1.14   Nov 10 2005 17:58:26   FENGYONG
//Incident 386579 - Add attribute to API batch level
//
//   Rev 1.13   Feb 01 2005 14:59:40   smithdav
//Minor ExecutionResult fixes and tweeks. 
//
//   Rev 1.12   Jan 27 2005 15:47:48   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.11   May 14 2004 16:15:24   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.10   Mar 09 2004 10:59:16   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.9   Mar 02 2004 10:56:04   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.8   Oct 09 2002 17:43:06   PURDYECH
//New PVCS Database
//
//   Rev 1.7   Oct 08 2002 10:29:22   IVESPAUL
//Added 'Successful' element to both Batch and Package levels.
//
//   Rev 1.6   Sep 19 2002 09:28:48   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.5   Aug 02 2002 17:13:42   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.4   16 May 2002 11:55:46   SMITHDAV
//Process changes to add xp::WorkSessionProcess
//and xp::UserSessionProcess classes and make
//top level process modeless.
//
//   Rev 1.3   14 May 2002 16:44:06   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.2   01 May 2002 17:16:50   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.1   02 Apr 2002 12:57:30   SMITHDAV
//Change the way XML processing is handled.
//
//   Rev 1.0   Nov 08 2000 13:22:06   YINGZ
//Initial revision.
 *
 */

