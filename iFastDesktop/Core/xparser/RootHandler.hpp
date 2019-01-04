#pragma once

#include <xparser\cacheenabledelementhandler.hpp>
#include <xparser\parmhandler.hpp>
#include <xparser\batchhandler.hpp>
#include <xparser\tracefilenameattribute.hpp>
#include <bfutil\elementwriter.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{
   class ExecutionResult;

   //******************************************************************************
   class XPARSER_LINKAGE RootHandler : public CacheEnabledElementHandler
   {
   public:
      RootHandler( const DString &elementName, xercesc::AttributeList &attributes );
      RootHandler( const DString &elementName );

      void execute( BFDocument &out, ExecutionResult &result );
      void executeCondition( const Condition& condition, BFDocument &out, ExecutionResult &result );

      virtual void addHandler( ParmHandler *handler );
      virtual void addHandler( BatchHandler *handler );

      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   protected:
      // override to set additional user session parms
      virtual void setUserSessionParms( GenericInterfaceContainer& gic ) {}

      // override to write additional output parms
      virtual void writeParms( AbstractProcess *userSessionProcess, BFDocument &out ) {}

      // override to provide logoff implementation
      virtual void logoff( AbstractProcess *userSessionProcess ) {}

      TraceFilenameAttribute _traceFilename;

   private:
      const BooleanAttribute _writeStats;
      const BooleanAttribute _verboseConditions;
      const BooleanAttribute _fieldFormatting;
      const BooleanAttribute _viewTimings;

      ParmHandlerList _parmList;
      BatchHandlerList _batchList;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/RootHandler.hpp-arc  $
//
//   Rev 1.10   Jan 27 2005 15:49:32   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.9   May 14 2004 16:16:36   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.8   Mar 09 2004 11:01:22   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.7   Mar 02 2004 10:56:38   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.6   Oct 09 2002 17:43:20   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Sep 19 2002 09:28:56   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.4   Sep 03 2002 18:03:52   IVESPAUL
//Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//   Rev 1.3   Aug 02 2002 17:13:46   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.2   07 Jun 2002 17:09:02   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.1   14 May 2002 16:44:14   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:46   SMITHDAV
//Initial revision.
 *
 */

