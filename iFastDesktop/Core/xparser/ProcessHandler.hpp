#pragma once

#include <xparser\elementhandler.hpp>
#include <xparser\processactionattribute.hpp>
#include <xparser\parmhandler.hpp>
#include <xparser\cbohandler.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
    #define XPARSER_LINKAGE CLASS_EXPORT
#else
    #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{

   class Process;
   class UserSessionProcess;
   class WorkSessionProcess;
   class ProcessResult;
   class BatchResult;

   //******************************************************************************
   class ProcessHandlerList : public ElementHandlerList<class ProcessHandler *>
   {
   public:
      void execute( UserSessionProcess &usProcess, BFDocument &out, BatchResult &result );
      void execute( Process &parentProcess, RADocument &out, ProcessResult &result );
      void writeCommitData( WorkSessionProcess &wsProcess, RADocument &out );
   };

   //******************************************************************************
   class XPARSER_LINKAGE ProcessHandler : public ElementHandler
   {
   public:
      ProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

      void execute( UserSessionProcess &usProcess, BFDocument &out, ProcessResult &result );
      void execute( Process &parentProcess, RADocument &out, ProcessResult &result );
      void writeCommitData( WorkSessionProcess &wsProcess, RADocument &out );

      ProcessAction getAction() const { return _action; }

      virtual void addHandler( ParmHandler *handler );
      virtual void addHandler( CBOHandler *handler );
      virtual void addHandler( ProcessHandler *handler );

      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   protected:
       // override for processes not requiring a work session ( top level process handlers only )
      virtual bool requiresWorkSession() { return true; }

       // override to set additional work session parms ( top level process handlers only where requiresWorkSession() returns true )
      virtual void setWorkSessionParms( AbstractProcess *process ) {}

       // override to set additional process parms
      virtual void setProcessParms( AbstractProcess *process ) {}

       // override to get interm process output parms
      virtual void getProcessParms( AbstractProcess *process ) {}

       // override to write final process output parms
      virtual void writeCommitParms( AbstractProcess *wsProcess, BFDocument &out ) {}

       // override to write additional process conditions. 
       //    any added error conditions will not affect process status ( errors should usually not be added )
      virtual void writeCommitConditions( AbstractProcess *wsProcess, BFDocument &out, ProcessResult &result ) {}
   private:
      void executeRaw( Process &parentProcess, RADocument &out, ProcessResult &result );

      const ProcessActionAttribute _action;

      ParmHandlerList _parmList;
      CBOHandlerList _cboList;
      ProcessHandlerList _processList;
      RADocument::Position _docPos;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ProcessHandler.hpp-arc  $
//
//   Rev 1.18   Apr 26 2005 11:38:26   smithdav
//Fix bug in which a process initialization warning is not being displayed.
//
//   Rev 1.17   Apr 22 2005 17:24:28   smithdav
//Replaced writeAdditionalCondtions overried with writeCommitConditions which is called only after commit of the top level process.
//
//   Rev 1.15   Apr 12 2005 12:35:58   smithdav
//Added new overrodable method called writeAdditionalConditions.
//
//   Rev 1.14   Mar 17 2005 13:39:26   popescu
//Fix bug in which errors were being reported for successful processes.
//
//   Rev 1.13   Jan 27 2005 15:49:28   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.12   May 14 2004 16:16:04   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.11   May 10 2004 13:57:22   SMITHDAV
//Add support for user session level processes -  no work session!!
//
//   Rev 1.10   Mar 09 2004 11:01:14   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.9   Mar 02 2004 10:56:34   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.8   Oct 09 2002 17:43:20   PURDYECH
//New PVCS Database
//
//   Rev 1.7   Sep 19 2002 09:28:56   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.6   Aug 02 2002 17:13:46   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.5   Jul 04 2002 15:22:42   SMITHDAV
//Class default handling and minor interface changes.
//
//   Rev 1.4   Jul 03 2002 10:53:16   SMITHDAV
//Add over-ridable method getProcessParams() to get process output parameters.
//
//   Rev 1.3   16 May 2002 11:55:50   SMITHDAV
//Process changes to add xp::WorkSessionProcess
//and xp::UserSessionProcess classes and make
//top level process modeless.
//
//   Rev 1.2   14 May 2002 16:44:12   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.1   01 May 2002 17:16:54   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.0   02 Apr 2002 13:47:46   SMITHDAV
//Initial revision.
 *
 */

