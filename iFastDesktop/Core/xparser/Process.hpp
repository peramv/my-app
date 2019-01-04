#pragma once

class GenericInterfaceContainer;
class AbstractProcess;

namespace xp
{
   class UserSessionProcess;
   class WorkSessionProcess;

   class Process
   {
   public:
      Process( Process &parentProcess, const DString &processName, bool ignoreWarnings, bool validateOnly );
      ~Process();

      const AbstractProcess* getProcessImpl() const { return(_processImpl);}
      AbstractProcess *getProcessImpl() { return(_processImpl);}

      bool commit();
      SEVERITY getHighestSeverity();
      bool isValidateOnly() const { return bValidateOnly_; }

      const GenericInterfaceContainer& getGIContainer() const;
      GenericInterfaceContainer& getGIContainer();

   protected:
      Process( Process &parentProcess, const DString &commandName );
      Process( GenericInterfaceContainer& gic, const DString &commandName );

   private:
      Process( const Process &copy ); // not implemented

      AbstractProcess *createProcess( Process &parentProcess,
                                      const DString &commandName,
                                      bool bModal,
                                      bool ignoreWarnings );

      AbstractProcess *createProcess( GenericInterfaceContainer* gic,
                                      AbstractProcess *parentProcess,
                                      const DString &commandName,
                                      bool bModal,
                                      bool ignoreWarnings );

      AbstractProcess *_processImpl;
      bool _isSessionProcess;
      bool bValidateOnly_;
   };

   class UserSessionProcess : public Process
   {
   public:
      UserSessionProcess( GenericInterfaceContainer& gic );
   };

   class WorkSessionProcess : public Process
   {
   public:
      WorkSessionProcess( UserSessionProcess &usProcess );
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/Process.hpp-arc  $
//
//   Rev 1.9   May 14 2004 16:15:48   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.8   May 26 2003 14:24:38   PURDYECH
//When in 'validate only' we now use ValidationControl BFExecutionContext stuff.
//
//   Rev 1.7   Oct 09 2002 17:43:18   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Oct 03 2002 18:42:54   IVESPAUL
//Added code to support validateOnly process action.
//
//   Rev 1.5   Sep 23 2002 18:29:18   SMITHDAV
//Process HighestSeverity changes.
//
//   Rev 1.4   Aug 06 2002 12:00:32   SMITHDAV
//Handle commit conditions.
//
//   Rev 1.3   Jul 29 2002 14:13:12   SMITHDAV
//Initialize processes with "ignoreWarningOnOk2" state when appropriate.
//
//   Rev 1.2   16 May 2002 11:55:44   SMITHDAV
//Process changes to add xp::WorkSessionProcess
//and xp::UserSessionProcess classes and make
//top level process modeless.
//
//   Rev 1.1   14 May 2002 16:42:58   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:50:06   SMITHDAV
//Initial revision.
 *
 */

