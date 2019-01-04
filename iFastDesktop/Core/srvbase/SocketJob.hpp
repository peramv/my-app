#pragma once
#include <srvbase\srvjob.hpp>

class BPSrvSocket;
class SocketPortal;

class SocketJob : public SrvJob
{
public:
   SocketJob( BPSrvSocket *socket, SocketPortal *portal );
   virtual ~SocketJob();

protected:
   virtual void readRequest( DStringA &buffer );
   virtual void writeResponse( const DStringA &buffer, const xp::ExecutionResult &result );

private:
   BPSrvSocket *clientSocket_;
   SocketPortal *portal_;
};
