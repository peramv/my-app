#pragma once
#include <srvbase\srvportal.hpp>

// Import/Export resolution
#undef SRVBASE_LINKAGE
#ifdef SRVBASE_DLL
   #define SRVBASE_LINKAGE CLASS_EXPORT
#else
   #define SRVBASE_LINKAGE CLASS_IMPORT
#endif

class ServerSocket;

class SRVBASE_LINKAGE SocketPortal : public SrvPortal
{
public:
   SocketPortal( const DString &name, int port, int threadCount, int queueSize, int iTimeout );
   virtual ~SocketPortal();

   virtual void close();

   int getPort() const { 
      return(port_);
   }

   virtual DString getDescription();
   virtual DStringA getDescriptionA();

protected:
   virtual bool run( BFThreadPool *const threadPool );

private:
   ServerSocket *serverSocket_;
   const int port_;
};
