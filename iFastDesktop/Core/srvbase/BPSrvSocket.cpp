// ************************************************************************
//
//  ^FILE:          BPSrvSocket.cpp
//
//  ^AUTHOR:        Paul Dardeau
//
//  ^DATE:          02/28/96
//
//  ^DESCRIPTION:   This file implements the Socket class. The BPSrvSocket
//                  class provides a C++ wrapper for the Berkley TCP/IP
//                  BPSrvSocket API.  The BPSrvSocket class is derived from
//                  IPCChannel, an abstract class for generic inter-
//                  process communications.  This class uses TCP stream
//                  sockets.
//
//  ^REVISIONS:     12/01/97 - Changed _EXCEPTION_HANDLING_ to
//                             _NO_EXCEPTION_HANDLING_.  This switches the
//                             default mode of operation to support
//                             exceptions unless otherwise specified.
//
//CP20030807//                         _DEBUGGING_
//                         _EXCEPTION_HANDLING_
//
//  ^NOTES:         Link to wsock32.lib on Win32
//
// ************************************************************************

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __unix__
   #include <unistd.h>
#endif
#include <dstring.hpp>
#include "BPSrvSocket.hpp"
#include <iostream>
#include <bf/log/logstream.hpp>
#include <bfutil\bfhrtimer.hpp>

const int ONEKB = 1024;

namespace 
{
   static void closeSocket( int nSocket )
   {
#ifdef _WIN32
      ::closesocket( nSocket );
#endif
#ifdef __unix__
      ::close( nSocket );
#endif
   }
}

/*==========================================================================
 *------------------------------ ServerSocket ------------------------------
 *==========================================================================*/
ServerSocket::ServerSocket( unsigned short usServerPort, int iTimeout /*=0*/ ) 
: serverSocket_( 0 )
, usServerPort_( usServerPort )
, iTimeout_( iTimeout )
{
   BPSrvSocket::initSockets();

   if( ! create() )
   {
      throw OSSocketCreateFailed();
   }

   if( ! listen() )
   {
      throw OSSocketCreateFailed();
   }
}


ServerSocket::~ServerSocket()
{
}


// Create socket
bool ServerSocket::create()
{
   serverSocket_ = ::socket( AF_INET, SOCK_STREAM, 0 );

   if( serverSocket_ < 0 )
   {
      return(false);
   }

   int val_to_set = 1;

   int ret = ::setsockopt( serverSocket_,
                           SOL_SOCKET,
                           SO_REUSEADDR,
                           (char *) &val_to_set,
                           sizeof( val_to_set ) );

   serverAddr_.sin_family = AF_INET;
   serverAddr_.sin_port = ::htons( usServerPort_ );
   serverAddr_.sin_addr.s_addr = INADDR_ANY;

   short sRc;
   sRc = ::bind( serverSocket_, (struct sockaddr *) &serverAddr_,
                 sizeof( serverAddr_ ) );

   if( sRc < 0 )
   {
      return(false);
   }
   else
   {
      return(true);
   }
}


bool ServerSocket::listen()
{
   if( ::listen( serverSocket_, SOMAXCONN ) != 0 )
   {
      return(false);
   }

   return(true);
}


void ServerSocket::close()
{
   closeSocket( serverSocket_ );
}

BPSrvSocket * ServerSocket::accept()
{
   struct sockaddr_in clientAddr;

   int nNameLen = sizeof( clientAddr );

   int connectionSocket = ::accept( serverSocket_,
                                    (struct sockaddr *) &clientAddr,
                                    &nNameLen );
   if( connectionSocket < 0 )
   {
      return(NULL);
   }

   return( new BPSrvSocket( connectionSocket, iTimeout_ ) );
}

/*==========================================================================
 *------------------------------- BPSrvSocket ------------------------------
 *==========================================================================*/

bool BPSrvSocket::s_bInitialized_ = false;
const unsigned short BPSrvSocket::s_usLengthMsgSize_ = 10;

void BPSrvSocket::initSockets()
{
#ifdef _WIN32
   if( ! BPSrvSocket::s_bInitialized_ )
   {
      WORD wVersionRequested = MAKEWORD( 2, 0 );
      WSADATA wsaData;

      int err = ::WSAStartup( wVersionRequested, &wsaData );

      if( err != 0 )
      {
         // error
      }
      else
      {
         s_bInitialized_ = true;
      }
   }
#endif
}

BPSrvSocket::BPSrvSocket( int nConnectionSocket, int iTimeout ) 
: usServerPort_( 0 )
, connectionSocket_( nConnectionSocket )
, iTimeout_( iTimeout )
{
   initSockets();
}


// Constructor that creates client-side socket
BPSrvSocket::BPSrvSocket( const char *pszAddress, 
                          unsigned short usServerPort,
                          int iTimeout ) 
: usServerPort_( usServerPort )
, connectionSocket_( -1 )
, iTimeout_( iTimeout )
{
   initSockets();

   strcpy( szAddress_, pszAddress );

   if( ! open() )
#ifndef _NO_EXCEPTION_HANDLING_
      throw OSSocketOpenFailed();
#else
      ;
#endif
}


BPSrvSocket::~BPSrvSocket()
{
   close();
}


DString BPSrvSocket::getClientAddress() const 
{
   struct sockaddr_in clientAddr;
   int cbClientAddr = sizeof( clientAddr );
   if( ::getpeername( connectionSocket_, (struct sockaddr*)&clientAddr, &cbClientAddr ) == 0 ) 
   {
      char szAddress[ 160 ];
      ::_snprintf( szAddress, sizeof( szAddress ), "%u.%u.%u.%u",
                   clientAddr.sin_addr.S_un.S_un_b.s_b1,
                   clientAddr.sin_addr.S_un.S_un_b.s_b2,
                   clientAddr.sin_addr.S_un.S_un_b.s_b3,
                   clientAddr.sin_addr.S_un.S_un_b.s_b4 );

      HOSTENT* pHostEnt;
      if( ( pHostEnt = ::gethostbyaddr( (const char*)&clientAddr.sin_addr.S_un, 4, PF_INET ) ) != NULL )
      {
         size_t cbAddress = strlen( szAddress );
         ::_snprintf( szAddress + cbAddress, sizeof( szAddress ) - cbAddress, " (%s)", pHostEnt->h_name );
      }
      return( DString(DStringA(szAddress)) );
   }
   return( I_("") );
}

// Open server socket
bool BPSrvSocket::open()
{
   connectionSocket_ = ::socket( AF_INET, SOCK_STREAM, 0 );

   if( connectionSocket_ == INVALID_SOCKET )
   {
      return(false);
   }

   ::memset( (void *) &serverAddr_, 0, sizeof( serverAddr_ ) );

   serverAddr_.sin_family = AF_INET;
   serverAddr_.sin_port = ::htons( usServerPort_ );
   serverAddr_.sin_addr.s_addr = ::inet_addr( szAddress_ );

   short sRc;
   sRc = ::connect( connectionSocket_, (struct sockaddr *) &serverAddr_,
                    sizeof( serverAddr_ ) );
   if( sRc < 0 )
   {
      return(false);
   }
   else
      return(true);
}

unsigned long BPSrvSocket::read( DStringA &rtnStr )
{
   unsigned long ulBytesRead = 0;
   unsigned long ulTotalBytesRead = 0;
   unsigned long ulLength = ONEKB;
   char  pBuffer[ONEKB + 1];

   rtnStr = "";   // Make sure start empty  
   do
   {  // get the message data - stream terminator should be NULL ('\0')
      if( !waitForData( iTimeout_ ) ) {
         return( SOCKET_ERROR );
      }
      ulBytesRead = ::recv( connectionSocket_, pBuffer, ulLength, 0 );
      if( ulBytesRead == SOCKET_ERROR )
      {
         return(ulBytesRead);
      }
      else if( ulBytesRead == 0 )
      {  // since we expect a NULL stream terminator (detected at end of loop) 
         //  this should mean socket was closed.
         return(ulBytesRead);
      }

      pBuffer[ulBytesRead] = '\0';
      rtnStr.append( pBuffer );
      ulTotalBytesRead += ulBytesRead;
      // Not sure how we should be handling international text here - should we expect UNICODE
      //  and double null terminator?
   }  while( pBuffer[ulBytesRead - 1] != '\0' );

   return(ulTotalBytesRead);
}

unsigned long BPSrvSocket::read( DString &rtnStr )
{  // Would need different implementation if expected UNICODE input
   DStringA buffer;
   unsigned long ulTotalBytesRead = read( buffer );
   rtnStr = buffer;
   return(ulTotalBytesRead);
}

// Write to socket
bool BPSrvSocket::write( const char * pszOutBuf,
                         unsigned long ulOutBufSize,
                         unsigned long * pulBytesWritten )
{
   //write to socket in 1kb chunks
   short sRc;
   *pulBytesWritten = 0;

#ifdef _DEBUG
   BFHRTimer t;
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "Starting transmission..." ) << bf::log::endlf;
#endif
   do
   {
      char szMsgLength[ s_usLengthMsgSize_ + 1 ];
      unsigned long length = ulOutBufSize > ONEKB ? ONEKB : ulOutBufSize;

      ulOutBufSize -= length;
      ::memset( szMsgLength, 0, s_usLengthMsgSize_ );
      ::_snprintf( szMsgLength, sizeof( szMsgLength ), "%ld", length );

      char onekbBuffer[ ONEKB ];

      ::memcpy( onekbBuffer, pszOutBuf, length );
      sRc = ::send( connectionSocket_, pszOutBuf, length, 0 );
      if( sRc < 0 )
      {
         *pulBytesWritten = 0;
         return(false);
      }
      pszOutBuf += length;
      *pulBytesWritten += length;
   } while( ulOutBufSize );
   char charnull = 0x0000;
   sRc = ::send( connectionSocket_, &charnull, 1, 0 );

#ifdef _DEBUG
   ls << I_( "Wrote " ) << *pulBytesWritten << I_(" bytes in ") << t.elapsed() << I_(" ms." ) << bf::log::endlf;
#endif

   if( sRc < 0 )
   {
      *pulBytesWritten = 0;
      return(false);
   }

   return(true);
}


// Close the socket
bool BPSrvSocket::close()
{
   closeConnection();

   return(true);
}


bool BPSrvSocket::closeConnection()
{
   // Per John Boardman, we don't need to call shutdown.  The shutdown +
   //  recv recommended in VS Help was blocking for long periods on recv
   //  in at least some cases.
   closeSocket( connectionSocket_ );
   return(true);
}

/**
 * FUNCTION:  waitForData
 *
 * PARAMETERS:
 *    ipSocket      - The socket to check
 *    iTimeOut      - seconds to wait for data
 *
 * ABSTRACT:
 *    BLOCKS waiting for data on a socket.
 *    When data arrives on a socket this
 *    function un-blocks and returns true
 *    or false.  Upon true the calling function
 *    is able to read. If the select call times
 *    out then false is returned.
 *
 *    If timeout is 0 then this function blocks
 *    indefinatly, if it is negative then it
 *    waits a single microseond, otherwise it
 *    blocks waiting for iTimeOut seconds.
 *
 * RETURNS:
 *    TRUE  (1) if socket has data waiting
 *    FALSE (0) if socket is invalid
 *
*/
bool BPSrvSocket::waitForData( int iTimeOut ) const
{
   bool blResult = false; // return code
   int rcSelect = 0; // return code from select()

   if( connectionSocket_ > 0 )
   {
      /**
       * Set up select fs_set structure with a timout
       * seconds
      */

      fd_set read_fds;
      struct timeval TimeOut;

      FD_ZERO( &read_fds );

      // this line gives a warning but removing it will
      // stop it working.
      FD_SET( connectionSocket_, &read_fds );

      /**
       * If the timeout is a negative then
       * wait only a microsecond
      */

      if( iTimeOut < 0 )
      {
         TimeOut.tv_sec  = 0;
         TimeOut.tv_usec = 1;
      }

      /**
       * Otherwise set the timeout in seconds
      */

      else
      {
         TimeOut.tv_sec  = iTimeOut;
         TimeOut.tv_usec = 0;
      }

      /**
       * Block waiting for data on ipSocket. If iTimeOut is zero
       * then block indefinatily, otherwise block for iTimeOut
       * seconds.
      */
      if( iTimeOut == 0 )
      {
         rcSelect = select( FD_SETSIZE, &read_fds, NULL, NULL, NULL );
      }
      else
      {
         rcSelect = select( FD_SETSIZE, &read_fds, NULL, NULL, &TimeOut );
      }

      /**
       * Fetch the descriptor
      */
      if( rcSelect != SOCKET_ERROR && rcSelect != 0 )
      {
         /**
          * If we have data on ipSocket
         */

         if( FD_ISSET( connectionSocket_, &read_fds) )
         {
            blResult = true;
         }
      }
   }

   /**
    * Return result - file descriptor
   */

   return(blResult);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/BPSrvSocket.cpp-arc  $
//
//   Rev 1.8   Jan 22 2004 08:33:00   PURDYECH
//PET910 - Added code to harden sockets against peer resets.  Also allow sockets to timeout on read requests so that the read() function won't hang if the peer takes to long to write.
//
//   Rev 1.7   Aug 12 2003 10:07:54   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.6   May 05 2003 10:21:24   PURDYECH
//Fixed some comments
//
//   Rev 1.5   May 05 2003 10:20:48   PURDYECH
//Removed some superfluous code.
//
//   Rev 1.4   May 02 2003 15:43:10   PURDYECH
//Added getClientName() to return the name of the attached client system.
// 
//    Rev 1.3   Jan 06 2003 16:45:12   PURDYECH
// Added some more debugging information.
// 
//    Rev 1.2   Oct 09 2002 17:42:24   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Oct 02 2001 14:53:22   FENGYONG
// Ram's change send 0 byte to socket at the end of a transaction
// 
//    Rev 1.0   Jun 28 2001 13:27:48   PURDYECH
// Initial revision.
 * 
 *    Rev 1.10   Nov 15 2000 14:13:26   DT24433
 * interface changes
 * 
 *    Rev 1.9   Sep 01 2000 09:59:26   DT24433
 * changed close method
 * 
 *    Rev 1.8   Aug 13 2000 15:42:42   YINGZ
 * fix read problem
 * 
 *    Rev 1.7   Aug 03 2000 14:50:40   DT24433
 * removed old read methods replacing with new method that accepts DStringA &
 * 
 */
