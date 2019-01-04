#pragma once

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef IPCCHANNEL_HPP
   #include <ipcchannel.hpp>
#endif

#ifdef __OS2__
   #include <types.h>
#endif

#ifdef __unix__
   #include <netinet/in.h>
   #include <sys/socket.h>
#else
// #include <netinet\in.h>
// #include <sys\socket.h>
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

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * The Socket class provides a C++ wrapper for the Berkley TCP/IP
 * socket API.  The Socket class is derived from
 * IPCChannel, an abstract class for generic inter-
 * process communications.  This class uses TCP stream
 * sockets.  This class is designed for cross-platform
 * use.
 *
 * The class is designed to support only one client
 * connection at a time.  It could be reworked to support
 * multiple concurrent clients, but this starts adding
 * a lot more platform specific code than what's already
 * here.
 */
class DICORE_LINKAGE Socket : public IPCChannel
{
public:
   /**
    * constructor
    */
   Socket();
   /**
    * constructor that creates a server-side socket
    */
   Socket( unsigned short usServerPort,
           IPCChannel::IPCAction action );
   /**
    * constructor that creates a client-side socket
    */
   Socket( const char * pszAddress,
           unsigned short usServerPort );

   /**
    * destructor
    */
   virtual ~Socket();
   /**
    * create a socket
    * 
    * @return 
    */
   virtual bool create();
   /**
    * open a server socket
    * 
    * @return 
    */
   virtual bool open();

   /**
    * read bytes from a socket
    * 
    * @param pulBytesRead
    *               - no. of bytes to read
    * @return pointer to the bytes read
    */
   virtual const char * read( unsigned long * pulBytesRead );
   /**
    * read bytes from a socket
    * 
    * @param pszInBuf - where to put the bytes
    * @param ulInBufSize
    *                 - buffer size
    * @param pulBytesRead
    *                 - (out) no. of bytes read
    * @return 
    */
   virtual bool read( char * pszInBuf,
                      unsigned long ulInBufSize,
                      unsigned long * pulBytesRead );
   /**
    * write bytes to a socket
    * 
    * @param pszOutBuf - where to put the bytes
    * @param ulOutBufSize
    *                 - buffer size
    * @param pulBytesWritten
    *                 - (out) no. of bytes written
    * @return 
    */
   virtual bool write( const char * pszOutBuf,
                       unsigned long ulOutBufSize,
                       unsigned long * pulBytesWritten );
   /**
    * read from and write bytes to a socket (one transaction)
    * 
    * @param pszOutBuf - where to put the bytes
    * @param ulOutBufSize
    *                 - buffer size
    * @param pulBytesRead
    *                 - (out) no. of bytes read
    * @return 
    */
   virtual const char * transact( const char * pszOutBuf,
                                  unsigned long ulOutBufSize,
                                  unsigned long * pulBytesRead );
   /**
    * read from and write bytes to a socket (one transaction)
    * 
    * @param pszOutBuf - where to put the bytes
    * @param ulOutBufSize
    *                  - buffer size
    * @param pszInBuf  - pointer to the buffer to read into
    * @param ulInBufSize
    *                  - size of the input buffer
    * @param pulBytesRead
    *                  - (out) no. of bytes read
    * @return 
    */
   virtual bool transact( const char * pszOutBuf,
                          unsigned long ulOutBufSize,
                          char * pszInBuf,
                          unsigned long ulInBufSize,
                          unsigned long * pulBytesRead );

   /**
    * Open socket, perform transaction, 
    * and then close socket
    * 
    * @param pszServerPort
    *                  port on the other end
    * @param pszOutBuf - where to put the bytes
    * @param ulOutBufSize
    *                  - output buffer size
    * @param pszInBuf  - pointer to the buffer to read into
    * @param ulInBufSize
    *                  - size of the input buffer
    * @param pulBytesRead
    *                  - (out) no. of bytes read
    * @return 
    */
   virtual bool call( const char * pszServerPort,
                      const char * pszOutBuf,
                      unsigned long ulOutBufSize,
                      char * pszInBuf,
                      unsigned long ulInBufSize,
                      unsigned long * pulBytesRead );

   /**
    * Place the server process into listening 
    * state
    * 
    * @return 
    */
   virtual bool listen();
   /**
    * close the socket
    * 
    * @return 
    */
   virtual bool close();


private:
   // Disallow the copy constructor & copy operators
   Socket( const Socket& copy );
   Socket& operator=( const Socket& copy );


private:
   static bool _fInitialized;
   static const unsigned short _usLengthMsgSize;
   bool _fRemote;
   bool _fServer;
   unsigned long _ulPipeOutBufSize;
   unsigned long _ulPipeInBufSize;
   unsigned short _usServerPort;
   struct sockaddr_in _serverAddr;
   struct sockaddr_in _clientAddr;
   int _serverSocket;
   int _connectionSocket;
   char _szAddress[16];
   char * _pszInputBuffer;
};


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/socket.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:16   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:12   SMITHDAV
//Initial revision.
// 
//    Rev 1.4   27 Nov 2000 16:18:12   dt14177
// cleanup
// 

