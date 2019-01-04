#include "stdafx.h"
#include "socketjob.hpp"
#include "bpsrvsocket.hpp"
#include "socketportal.hpp"

SocketJob::SocketJob( BPSrvSocket *socket, SocketPortal *portal ) 
: SrvJob( portal )
, clientSocket_( socket )
, portal_( portal )
{
}

SocketJob::~SocketJob() {
}

void SocketJob::readRequest( DStringA &buffer ) {
   unsigned long ulBytesRead = clientSocket_->read( buffer );
}

void SocketJob::writeResponse( const DStringA &buffer, const xp::ExecutionResult &result ) {
   unsigned long ulBytesWritten = 0L;
   clientSocket_->write( buffer.c_str(), buffer.size(), &ulBytesWritten );
}
