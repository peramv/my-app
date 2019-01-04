// ************************************************************************
//
//  ^FILE:          Socket.cpp
//
//  ^AUTHOR:        Paul Dardeau
//
//  ^DATE:          02/28/96
//
//  ^DESCRIPTION:   This file implements the Socket class. The Socket
//                  class provides a C++ wrapper for the Berkley TCP/IP
//                  socket API.  The Socket class is derived from
//                  IPCChannel, an abstract class for generic inter-
//                  process communications.  This class uses TCP stream
//                  sockets.  This class is designed for cross-platform
//                  use.
//
//                  The class is designed to support only one client
//                  connection at a time.  It could be reworked to support
//                  multiple concurrent clients, but this starts adding
//                  a lot more platform specific code than what's already
//                  here.
//
//
//  ^NOTES:         Link to wsock32.lib on Win32
//
// ************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif
#ifndef INCLUDED_STDLIB_H
#define INCLUDED_STDLIB_H
#include <stdlib.h>
#endif
#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef SOCKET_HPP
   #include "socket.hpp"
#endif

#ifndef DIPORT2_HPP
   #include "diport2.h"
#endif


bool Socket::_fInitialized = FALSE;
const unsigned short Socket::_usLengthMsgSize = 10;



// Default constructor
Socket::Socket() :
_pszInputBuffer( NULL )
{
   // Default to local socket connection
   _fRemote  = FALSE;

   // Set default timeout to 3 seconds (parameter in milliseconds)
   setTimeOut( 3000 );

   // Only call initialization routine once
   if( ! Socket::_fInitialized )
   {
      if( InitSocket() == 0 )
         Socket::_fInitialized = TRUE;
      else
      {
         // error
      }
   }
}


// Constructor that creates server-side socket
Socket::Socket( unsigned short usServerPort, IPCChannel::IPCAction action ) :
_usServerPort( usServerPort ),
_pszInputBuffer( NULL )
{
   // Set default timeout to 3 seconds (parameter in milliseconds)
   setTimeOut( 3000 );

   if( ! Socket::_fInitialized )
   {
      if( InitSocket() == 0 )
         Socket::_fInitialized = TRUE;
      else
      {
         // error
      }
   }

   switch( action )
   {
      case OPEN:
         {
            if( ! open() )
#ifndef _NO_EXCEPTION_HANDLING_
               throw OSSocketOpenFailed();
#else
               ;
#endif
            break;
         }
      case CREATE:
         {
            if( ! create() )
#ifndef _NO_EXCEPTION_HANDLING_
               throw OSSocketCreateFailed();
#else
               ;
#endif
/*
         else
         {
            if ( ! listen() )
#ifndef _NO_EXCEPTION_HANDLING_
               throw OSSocketConnectFailed();
#else
               ;
#endif
         }
*/
            break;
         }
   }
}


// Constructor that creates client-side socket
Socket::Socket( const char *pszAddress, unsigned short usServerPort ) :
_usServerPort( usServerPort ),
_pszInputBuffer( NULL )
{
   strcpy( _szAddress, pszAddress );

   // Set default timeout to 3 seconds (parameter in milliseconds)
   setTimeOut( 3000 );

   if( ! Socket::_fInitialized )
   {
      if( InitSocket() == 0 )
         Socket::_fInitialized = TRUE;
      else
      {
         // error
      }
   }

   if( ! open() )
#ifndef _NO_EXCEPTION_HANDLING_
      throw OSSocketOpenFailed();
#else
      ;
#endif
}


Socket::~Socket()
{
   if( _pszInputBuffer )
   {
      delete [] _pszInputBuffer;
   }

   close();
}


// Create socket
bool Socket::create()
{
   _fServer = TRUE;

   _serverSocket = socket( AF_INET, SOCK_STREAM, 0 );

   if( _serverSocket < 0 )
   {
      return(FALSE);
   }

   int val_to_set = 1;

   int ret = setsockopt( _serverSocket,
                         SOL_SOCKET,
                         SO_REUSEADDR,
                         (char *) &val_to_set,
                         sizeof( val_to_set ) );

   _serverAddr.sin_family = AF_INET;
   _serverAddr.sin_port = htons( _usServerPort );
   _serverAddr.sin_addr.s_addr = INADDR_ANY;

   short sRc;
   sRc = bind( _serverSocket, (struct sockaddr *) &_serverAddr,
               sizeof( _serverAddr ) );

   if( sRc < 0 )
   {
      return(FALSE);
   }
   else
      return(TRUE);
}


// Open server socket
bool Socket::open()
{
   _fServer = FALSE;

   _connectionSocket = socket( AF_INET, SOCK_STREAM, 0 );

   if( _connectionSocket == INVALID_SOCKET )
   {
      return(FALSE);
   }

   memset( (void *) &_serverAddr, 0, sizeof( _serverAddr ) );

   _serverAddr.sin_family = AF_INET;
   _serverAddr.sin_port = htons( _usServerPort );
   _serverAddr.sin_addr.s_addr = inet_addr( _szAddress );

   short sRc;
   sRc = connect( _connectionSocket, (struct sockaddr *) &_serverAddr,
                  sizeof( _serverAddr ) );
   if( sRc < 0 )
   {
      return(FALSE);
   }
   else
      return(TRUE);
}



const char * Socket::read( unsigned long * pulBytesRead )
{
   unsigned long total_bytes_rcvd;
   unsigned long bytes;
   unsigned long length;
   char * pBuffer;
   char szMsgLength[ Socket::_usLengthMsgSize + 1 ];

   memset( szMsgLength, 0, Socket::_usLengthMsgSize + 1 );

   // Get the length of the message
   total_bytes_rcvd = 0;
   do
   {
      pBuffer = (char *) szMsgLength + total_bytes_rcvd;
      bytes = recv( _connectionSocket,
                    pBuffer,
                    Socket::_usLengthMsgSize - total_bytes_rcvd,
                    0 );

      if( bytes < 0 )
      {
         return(NULL);
      }

      total_bytes_rcvd += bytes;
   } while( total_bytes_rcvd < Socket::_usLengthMsgSize );


   // convert the ASCII representation of the length into binary form
   length = atol( szMsgLength );

   _pszInputBuffer = new char[ length + 1 ];


   // get the message data
   total_bytes_rcvd = 0;
   do
   {
      pBuffer = _pszInputBuffer + total_bytes_rcvd;
      bytes = recv( _connectionSocket,
                    pBuffer,
                    length - total_bytes_rcvd,
                    0 );

      if( bytes < 0 )
      {
         return(NULL);
      }

      total_bytes_rcvd += bytes;
   } while( total_bytes_rcvd < length );

   _pszInputBuffer[length] = '\0';

   *pulBytesRead = total_bytes_rcvd;

   return(_pszInputBuffer);
}



// Read from socket
bool Socket::read( char * pszInBuf, unsigned long ulInBufSize,
                   unsigned long * pulBytesRead )
{
   unsigned long total_bytes_rcvd;
   unsigned long bytes;
   unsigned long length;
   char * pBuffer;
   char szMsgLength[ Socket::_usLengthMsgSize + 1 ];

   memset( szMsgLength, 0, Socket::_usLengthMsgSize + 1 );

   // Get the length of the message
   total_bytes_rcvd = 0;
   do
   {
      pBuffer = (char *) szMsgLength + total_bytes_rcvd;
      bytes = recv( _connectionSocket,
                    pBuffer,
                    Socket::_usLengthMsgSize - total_bytes_rcvd,
                    0 );

      if( bytes < 0 )
      {
         return(FALSE);
      }

      total_bytes_rcvd += bytes;
   } while( total_bytes_rcvd < Socket::_usLengthMsgSize );


   // convert the ASCII representation of the length into binary form
   length = atol( szMsgLength );


   // get the message data
   total_bytes_rcvd = 0;
   do
   {
      pBuffer = pszInBuf + total_bytes_rcvd;
      bytes = recv( _connectionSocket,
                    pBuffer,
                    length - total_bytes_rcvd,
                    0 );

      if( bytes < 0 )
      {
         return(FALSE);
      }

      total_bytes_rcvd += bytes;
   } while( total_bytes_rcvd < length );

   pszInBuf[length] = '\0';

   *pulBytesRead = total_bytes_rcvd;

   return(TRUE);
}


// Write to socket
bool Socket::write( const char * pszOutBuf,
                    unsigned long ulOutBufSize,
                    unsigned long * pulBytesWritten )
{
   short sRc;
   unsigned long length = ulOutBufSize;
   char szMsgLength[ Socket::_usLengthMsgSize + 1 ];

   memset( szMsgLength, 0, Socket::_usLengthMsgSize );

   sprintf( szMsgLength, "%ld", ulOutBufSize );

   sRc = send( _connectionSocket, szMsgLength, Socket::_usLengthMsgSize, 0 );
   if( sRc < 0 )
   {
      *pulBytesWritten = 0;
      return(FALSE);
   }

   sRc = send( _connectionSocket, pszOutBuf, ulOutBufSize, 0 );
   if( sRc < 0 )
   {
      *pulBytesWritten = 0;
      return(FALSE);
   }

   *pulBytesWritten = ulOutBufSize;
   return(TRUE);
}



const char * Socket::transact( const char * pszOutBuf,
                               unsigned long ulOutBufSize,
                               unsigned long * pulBytesRead )
{
   unsigned long ulBytesWritten = 0;

   if( ! write( pszOutBuf,
                ulOutBufSize,
                &ulBytesWritten ) )
   {
      return(NULL);
   }

   return(read( pulBytesRead ));
}



// Perform transaction( write & then read ) with socket
bool Socket::transact( const char * pszOutBuf,
                       unsigned long ulOutBufSize,
                       char * pszInBuf,
                       unsigned long ulInBufSize,
                       unsigned long * pulBytesRead )
{
   unsigned long ulBytesWritten;

   if( ! write( pszOutBuf, ulOutBufSize, &ulBytesWritten ) )
      return(FALSE);

   if( ! read( pszInBuf, ulInBufSize, pulBytesRead ) )
      ; //   return FALSE;
   else
      return(TRUE);

   return(FALSE);
}


// Open socket, perform transaction, and then close socket
bool Socket::call( const char * pszServerPort,
                   const char * pszOutBuf,
                   unsigned long ulOutBufSize,
                   char * pszInBuf,
                   unsigned long ulInBufSize,
                   unsigned long * pulBytesRead )
{
   // unsigned short usServerPort;
   // _usServerPort = usServerPort;

   if( ! open() )
      return(FALSE);

   unsigned long ulBytesWritten;

   if( ! write( pszOutBuf, ulOutBufSize, &ulBytesWritten ) )
      return(FALSE);

   if( ! read( pszInBuf, ulInBufSize, pulBytesRead ) )
      return(FALSE);

   if( ! close() )
      return(FALSE);

   return(TRUE);
}


// Place the server process into listening state
bool Socket::listen()
{

   /*  listen  */
   if( ::listen( _serverSocket, 1 ) != 0 )
   {
      return(FALSE);
   }

   int nNameLen = sizeof( _clientAddr );

   _connectionSocket = accept( _serverSocket,
                               (struct sockaddr *) &_clientAddr,
                               &nNameLen );

   if( _connectionSocket < 0 )
   {
      return(FALSE);
   }

   return(TRUE);
}


// Close the socket
bool Socket::close()
{
   CloseSocket(_connectionSocket);
   return(_fServer ? (CloseSocket(_serverSocket) >= 0) : TRUE);
}
