#include "stdafx.h"
#include "socketportal.hpp"
#include "socketjob.hpp"
#include "server.hpp"
#include "bpsrvsocket.hpp"
#include <bfutil\bfjobqueue.hpp>


SocketPortal::SocketPortal( const DString &name, int port, int threadCount, int queueSize, int iTimeout )
: SrvPortal( name, new BFInternalJobQueue( queueSize ), threadCount )
, serverSocket_( new ServerSocket( port, iTimeout ) )
, port_( port )
{
}

SocketPortal::~SocketPortal() {
}

bool SocketPortal::run( BFThreadPool * const threadPool ) {

   BPSrvSocket *clientSocket = serverSocket_->accept();

   if( clientSocket == NULL ) {
      return false;  // socket closed ???  -- may need extended error handling
   }

   threadPool->postJob( new SocketJob( clientSocket, this ) );
   return true;
}

void SocketPortal::close() {
   serverSocket_->close();
   delete serverSocket_;
   serverSocket_ = NULL;

   SrvPortal::close();
}

#define DESC_SZ 128
DString SocketPortal::getDescription() {
   I_CHAR desc[DESC_SZ];
   i_sprintf(desc, DESC_SZ, I_("TCP - port: %d"), port_);
   desc[DESC_SZ-1]='\0';
   return desc;
}

DStringA SocketPortal::getDescriptionA() {
   char desc[DESC_SZ];
   _snprintf(desc, DESC_SZ, "TCP - port: %d", port_);
   desc[DESC_SZ-1]='\0';
   return desc;
}
