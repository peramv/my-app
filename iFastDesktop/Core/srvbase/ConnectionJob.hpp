#pragma once
#include <bfutil/bfjob.hpp>
#include <bfutil/bfhrtimer.hpp>
#include <bfutil/bfguard.hpp>

//Forward declarations
class BPSrvSocket;
class Server;

//this class keeps pointers to a client socket opened 
//by the server and the service needed to be provided;
//it closes the client socket when the job is deleted
class ConnectionJob : public BFJob
{
public:
   ConnectionJob( BPSrvSocket *socket, Server *server, bool bTrace = false );
   virtual ~ConnectionJob();

   virtual void run();

   const BFHRTimer& getStartTime() const { return(acceptStartTime_);}

   unsigned int getJobId() const { return idJob_; }

private:
   BPSrvSocket *_clientSocket;
   Server *_server;
   bool bTrace_;

   unsigned int idJob_;
   void assignJobId();
   static BFCritSec s_csJobId_;
   static unsigned int s_idNextJob_;

   BFHRTimer acceptStartTime_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/ConnectionJob.hpp-arc  $
//
//   Rev 1.10   Aug 12 2003 10:07:52   PURDYECH
//Added new logging method (bf::log::...)
 * 
 *    Rev 1.9   Nov 14 2002 18:14:08   PURDYECH
 * Support Console tracing externally
 * 
 *    Rev 1.8   Oct 09 2002 17:42:26   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.7   22 May 2002 17:49:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 Oct 2001 15:09:52   SMITHDAV
 * Syncronization changes and Job Queue changes
 * 
 *    Rev 1.5   Jun 27 2001 20:07:10   PURDYECH
 * Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
 * 
 *    Rev 1.4   Aug 23 2000 11:00:40   DT24433
 * Moved job related logic to this class (removed Connection class
 * 
 *    Rev 1.3   Jun 06 2000 10:47:40   POPESCUS
 * cleaned up the code to support only one threading model
 * 
 *    Rev 1.2   May 23 2000 10:31:38   POPESCUS
 * fixed listening to one port mechanism
 * 
 *    Rev 1.1   Feb 16 2000 13:03:36   POPESCUS
 * Initial revision
 * 
 * 
 */