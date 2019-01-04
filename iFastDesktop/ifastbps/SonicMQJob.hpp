#pragma once
#include <srvbase/srvjob.hpp>

#include <progress/message/jclient/package.h>

class SonicMQPortal;

class SonicMQJob : public SrvJob
{
public:
   SonicMQJob( SonicMQPortal* portal );
   virtual ~SonicMQJob();

   bool SonicMQJob::receive( DWORD timeout );
protected:
   virtual void readRequest( DStringA &buffer );
   virtual void writeResponse( const DStringA &buffer, const xp::ExecutionResult &result );

private:
   static bool resultsHaveCriticalErrors( const xp::ExecutionResult &result );
   SonicMQPortal* portal_;

   progress::message::jclient::QueueConnectionRef connection_;
   progress::message::jclient::QueueSessionRef session_;
   progress::message::jclient::QueueReceiverRef receiver_;
   progress::message::jclient::MessageRef message_;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/SonicMQJob.hpp-arc  $
//
//   Rev 1.2   Mar 29 2006 16:40:58   smithdav
//Change Sonic connectgion logic to create a dedicated connection per thead, and attampt a re-connect if failures occur.
//
//   Rev 1.1   Feb 03 2005 13:32:12   smithdav
//Add critical error rollback.
//
//   Rev 1.0   Jan 27 2005 16:35:46   smithdav
//Initial revision.
//
//   Rev 1.0   Sep 10 2004 17:11:22   SMITHDAV
//Initial revision.
 * 
 */