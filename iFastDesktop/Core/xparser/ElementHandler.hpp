#pragma once

#include <list>
#include <bfutil\elementwriter.hpp>
#include <xparser\classattribute.hpp>
#include <xercesc/sax/attributelist.hpp>

class BFData;
class BFFieldId;
class GenericInterfaceContainer;
class AbstractProcess;
class BFContainerId;
enum E_PROCESSTYPE;

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{

   class CacheEnabledElementHandler;
   class ParmHandler;
   class BatchHandler;
   class ProcessHandler;
   class CBOHandler;
   class KeyHandler;
   class FieldHandler;
   class ExecResult;

   //******************************************************************************
   class XPARSER_LINKAGE ElementHandler : public ElementInterface
   {
   public:
      ElementHandler( ElementHandler *parentHandler,
                      const DString &elementName,
                      ClassAttribute::ElementClass elementClass );


      ElementHandler( const DString &elementName );

      virtual ~ElementHandler();

      ElementHandler *createChildHandler( const DString &name, xercesc::AttributeList &attributes );

      virtual const DString &getName() const { return(_elementName);}
      virtual const DString &getText() const { static DString ns(I_("")); return(ns);}
      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const { return(attributes);}

      ElementHandler *getParent() const { return(_parentHandler);}
      const ClassAttribute &getElementClass() const { return(_elementClass);}

      bool ignoreWarnings() const
      {
         return(_bIgnoreWarnings);
      }

      bool writeStats() const
      {
         return(_bWriteStats);
      }

      bool verboseConditions() const
      {
         return(_bVerboseConditions);
      }

      virtual void appendText( const XMLCh * const chars, const unsigned int length ) {}

   protected:

      void setIgnoreWarnings( bool value )
      {
         _bIgnoreWarnings = value;
      }

	  void setRetry( bool value )
      {
         _retry = value;
		 bfutil::setRetry( value );
      }

      void setWriteStats( bool value )
      {
         _bWriteStats = value;
      }

      void setVerboseConditions( bool value )
      {
         _bVerboseConditions = value;
      }

      void setFieldFormatting( bool value )
      {
         _bFieldFormatting = value;
      }

      // override to add handlers
      virtual void addHandler( ParmHandler *handler );
      virtual void addHandler( BatchHandler *handler );
      virtual void addHandler( ProcessHandler *handler );
      virtual void addHandler( CBOHandler *handler );
      virtual void addHandler( KeyHandler *handler );
      virtual void addHandler( FieldHandler *handler );

      //******************************************************************************
      class Writer : ElementWriter
      {
      public:
         Writer( const ElementHandler& handler, BFDocument &out );
         ~Writer();

      private:
         const ElementHandler& handler_;
      };

      //******************************************************************************
      class StatusWriter
      {
      public:
         StatusWriter( BFDocument &out, ExecResult &result );
         ~StatusWriter();

         void setSuccess() { success_ = true;}
      private:
         BFDocument& out_;
         ExecResult &result_;
         bool success_;
      };

      void writeParm( const DString &name, const DString& value, BFDocument &out );
      void writeField( const DString &name, const DString& value, BFDocument &out );
      void writeField( const BFFieldId &id, AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
      void writeField( const BFData& data, const BFFieldId &id, AbstractProcess *process, BFDocument &out );

      void writeHighestSeverity( SEVERITY severity, BFDocument &out );
      void writeCondition( const Condition& condition, BFDocument &out, ExecResult &result );
      void writeConditions( Frame *frame, BFDocument &out, ExecResult &result );
      void writeConditions( const CONDITIONVECTOR& cv, BFDocument &out, ExecResult &result );

      void cachePut( const DString &text );
      void cachePut( const DString &name, const DString &text );
      const DString &cacheGet() const;
      const DString &cacheGet( const DString &name ) const;

   private:
      ElementHandler *_parentHandler; // parent handler
      CacheEnabledElementHandler *_cachingHandler; // caching ancestor handler

      const DString _elementName;
      const ClassAttribute _elementClass;

      bool _bIgnoreWarnings;
      bool _bWriteStats;
      bool _bVerboseConditions;
      bool _bFieldFormatting;
	  bool _retry;

      friend Writer;
      friend CacheEnabledElementHandler;

   };

   //******************************************************************************
   template<class _Eh> class ElementHandlerList : public std::list<_Eh>
   {
   public:
      virtual ~ElementHandlerList()
      {
         while( begin() != end() )
         {
            delete (*begin());
            pop_front();
         }
      }

      void add( _Eh handler )
      {
         assert( handler != NULL );
         push_back( handler );
      }
   };

   //******************************************************************************
   class ElementFailure
   {
   public:
      ElementFailure( ElementHandler *handler ) : _handler( handler ) {}
      const ElementHandler *getHandler() { return(_handler);}

   private:
      const ElementHandler *_handler;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ElementHandler.hpp-arc  $
//
//   Rev 1.21   Nov 10 2005 17:59:44   FENGYONG
//Incident 386579 - Add attribute to API batch level
//
//   Rev 1.20   Feb 01 2005 14:59:44   smithdav
//Minor ExecutionResult fixes and tweeks. 
//
//   Rev 1.19   Jan 27 2005 15:48:38   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.18   Mar 09 2004 11:00:46   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.17   Mar 05 2004 13:28:26   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.16   Mar 02 2004 10:56:22   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.15   Jan 06 2003 17:00:38   PURDYECH
//Sync back to Dave's changes for Process Initiation
//
//   Rev 1.13.1.0   Dec 18 2002 11:23:10   SMITHDAV
//Fixed Process initiation error problem.
//
//   Rev 1.13   Oct 09 2002 17:43:14   PURDYECH
//New PVCS Database
//
//   Rev 1.12   Sep 23 2002 19:20:46   IVESPAUL
//Added 'Successful' Element.
//
//   Rev 1.11   Sep 19 2002 09:28:52   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.10   Sep 03 2002 18:03:52   IVESPAUL
//Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//   Rev 1.9   Aug 29 2002 12:57:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   Aug 14 2002 12:17:06   SMITHDAV
//Fix class attribute defaulting logic.
//
//   Rev 1.7   Aug 02 2002 17:13:44   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.6   07 Jun 2002 17:09:00   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.5   07 Jun 2002 10:55:30   SMITHDAV
//Sync-up with Chris' changes.
//
//   Rev 1.4   16 May 2002 11:55:50   SMITHDAV
//Process changes to add xp::WorkSessionProcess
//and xp::UserSessionProcess classes and make
//top level process modeless.
//
//   Rev 1.3   14 May 2002 16:44:08   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.2   01 May 2002 17:16:52   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.1   30 Apr 2002 11:55:12   SMITHDAV
//Add support for field writing and sub-class field writing.
//
//   Rev 1.0   02 Apr 2002 13:47:44   SMITHDAV
//Initial revision.
 *
 */

