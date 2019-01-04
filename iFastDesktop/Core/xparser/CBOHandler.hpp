#pragma once

#include <xparser\elementhandler.hpp>
#include <xparser\cboactionattribute.hpp>
#include <xparser\recordcountattribute.hpp>
#include <xparser\fieldhandler.hpp>
#include <xparser\keyhandler.hpp>
#include <bfproc\bfcontainerid.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
    #define XPARSER_LINKAGE CLASS_EXPORT
#else
    #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{
   class WorkSessionProcess;
   class ProcessResult;

   //******************************************************************************
   class CBOHandlerList : public ElementHandlerList<class CBOHandler *>
   {
   public:
      void execute( AbstractProcess *process, RADocument &out, ProcessResult &result );
      void writeCommitData( WorkSessionProcess &wsProcess, RADocument &out );
   };

   //******************************************************************************
   class XPARSER_LINKAGE CBOHandler : public ElementHandler
   {
   public:
      CBOHandler( ElementHandler *parentHandler,
                  const DString &elementName,
                  xercesc::AttributeList &attributes,
                  bool bFieldFormatting = false );

      void execute( AbstractProcess *process, RADocument &out, ProcessResult &result );
      void writeCommitData( WorkSessionProcess &wsProcess, RADocument &out );

      virtual void addHandler( KeyHandler *handler );
      virtual void addHandler( FieldHandler *handler );
      virtual void addHandler( CBOHandler *handler );

      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   protected:

      virtual SEVERITY doValidate( xp::CBOAction action,
                                   AbstractProcess *process,
                                   const BFContainerId& idContainer ) { return NO_CONDITION; }

      virtual void writeFields( xp::CBOAction action,
                                AbstractProcess *process,
                                const BFContainerId& idContainer,
                                BFDocument &out) { }

      virtual void writeCommitFields( xp::CBOAction action,
                                      AbstractProcess *process,
                                      BFDocument &out ) { }

   private:
      void executeQuery( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeQueryAll( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeCurrentQueryItem( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeAdd( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeUpdate( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeDelete( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeDeleteAll( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );
      void executeReplace( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );

      bool executeKeyLookup( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out );

      void validate( AbstractProcess *process, const BFContainerId& idContainer, RADocument &out, ProcessResult &result );

      const CBOActionAttribute _action;
      const RecordCountAttribute _recordCount;
      const BooleanAttribute _echoFields;

      KeyHandler *_keyHandler;
      FieldHandlerList _fieldList;
      CBOHandlerList _cboList;
      RADocument::Position _docPos;

      bool _bFieldFormatting;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/CBOHandler.hpp-arc  $
//
//   Rev 1.13   Apr 26 2005 11:34:16   smithdav
//Add boolean attribute to "echo" request fields in the response.
//
//   Rev 1.12   Jan 27 2005 15:48:16   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.11   May 14 2004 16:15:32   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.10   Mar 09 2004 11:00:28   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.9   Mar 02 2004 10:56:08   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.8   Jan 06 2003 16:47:24   PURDYECH
//BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 17:43:10   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Sep 19 2002 09:28:50   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.5   Sep 18 2002 13:08:20   IVESPAUL
//Support for EMPTY/NULL containers from the process layer and
//support for formatting CBO fields when fetching all fields from a CBO/Container.
//
//   Rev 1.4   Aug 02 2002 17:13:42   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.3   14 May 2002 16:44:08   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.2   01 May 2002 17:16:50   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.1   30 Apr 2002 11:55:12   SMITHDAV
//Add support for field writing and sub-class field writing.
//
//   Rev 1.0   02 Apr 2002 13:47:42   SMITHDAV
//Initial revision.
 *
 */

