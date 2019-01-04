#pragma once

#ifdef WIN32
   #include <windows.h>
   #include <process.h>

   #include <commonPort.h>

#endif

#ifdef __OS2__
   #include <types.h>
#endif

#ifdef __unix__
   #include <netinet/in.h>
   #include <sys/socket.h>
#else
#endif

#ifndef _NO_EXCEPTION_HANDLING_
class OSSocketCreateFailed
{
};
class OSSocketOpenFailed
{
};
class OSSocketConnectFailed
{
};
#endif

class BPSrvSocket;

class ServerSocket
{
public:
   ServerSocket( unsigned short usServerPort, int iTimeout = 0 );
   ~ServerSocket();
   BPSrvSocket * accept();
   void close();

private:
   bool create();
   bool listen();
   ServerSocket( const ServerSocket& copy );
   ServerSocket& operator=( const ServerSocket& copy );

private:
   int serverSocket_;
   unsigned short usServerPort_;
   int iTimeout_;
   struct sockaddr_in serverAddr_;
};



class CLASS_EXPORT BPSrvSocket
{
   friend class ServerSocket;

public:
   BPSrvSocket( const char * pszAddress,
                unsigned short usServerPort,
                int iTimeout );

   virtual ~BPSrvSocket();

   virtual unsigned long read( DString &buffer );
   virtual unsigned long read( DStringA &buffer );
   virtual bool write( const char * pszOutBuf,
                       unsigned long ulOutBufSize,
                       unsigned long * pulBytesWritten );
   virtual bool close();
   virtual bool closeConnection();

   DString getClientAddress() const;

   unsigned short getServerPort() const
   {
      return(serverAddr_.sin_port);
   };
private:
   BPSrvSocket( int nConnectionSocket, int iTimeout );
   bool open();

   bool waitForData( int iTimeOut ) const;

   // Disallow the copy constructor & copy operators
   BPSrvSocket( const BPSrvSocket& copy );
   BPSrvSocket& operator=( const BPSrvSocket& copy );

   static void initSockets();


private:
   static bool s_bInitialized_;
   static const unsigned short s_usLengthMsgSize_;
   struct sockaddr_in serverAddr_;
   unsigned short usServerPort_;
   int connectionSocket_;
   int iTimeout_;
   char szAddress_[16];
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/BPSrvSocket.hpp-arc  $
//
//   Rev 1.4   Jan 22 2004 08:33:14   PURDYECH
//PET910 - Added code to harden sockets against peer resets.  Also allow sockets to timeout on read requests so that the read() function won't hang if the peer takes to long to write.
//
//   Rev 1.3   May 02 2003 15:43:32   PURDYECH
//Added getClientName() to return the name of the attached client system.
//
//   Rev 1.2   Oct 09 2002 17:42:24   PURDYECH
//New PVCS Database
//
//   Rev 1.1   Jul 05 2002 11:43:52   PURDYECH
//Infrastructure Fixup ... no more ICU!
//
//   Rev 1.0   Jun 28 2001 13:27:48   PURDYECH
//Initial revision.
 * 
 *    Rev 1.5   Nov 15 2000 14:16:40   DT24433
 * interface changes
 * 
 *    Rev 1.4   Aug 03 2000 14:52:10   DT24433
 * removed old read methods replacing with new method that accepts DStringA &
 * 
 */

