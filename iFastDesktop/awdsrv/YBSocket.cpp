//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : YBSocket.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : YBSocket
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#include "stdafx.h"
#include "ybsocket.hpp"
#include "logging.h"

namespace 
{   
   const char * const CLASSNAME                    =  "YBSocket";
}

YBSocket::YBSocket()
{
   LOGGINGWITHTIMESTAMP(  CLASSNAME );
   uStatus = SOCKET_STATE::OK;
}

YBSocket::~YBSocket(void)
{
   if( conSocket_ )
   {
      closesocket(conSocket_);
   }
}

//********************************************************************************
std::string YBSocket::convertIntToString(int iNum)
{
   std::string str;
   char szValue[32];
//   memset(szValue,'',sizeof (szValue) );  
   itoa(iNum,szValue,10);
   str=szValue;
   return str;
}


//************************************************************
bool YBSocket::init(const char* address, unsigned short port)
{
   std::string message= "  connect address at:  ";
   bInitialized_ = false;
   ::memset( (void *) &svrAddress_, 0, sizeof( svrAddress_ ) );
   strcpy(svrAddress_,address);
   std::string strAdd;
   strAdd.append( svrAddress_ );
   message += strAdd;
   message += "   port:";
   message += convertIntToString( port );
   message += "\n";
   LOGGING( message );
   serverPort_ = port;
   initSocket();
   if ( bInitialized_ )
   {
      return connectServer();
   }
   return false;
}
//*************************************************************
// Create socket
//
void YBSocket::initSocket()
{
   if( ! bInitialized_ )
   {
      WORD wVersionRequested = MAKEWORD( 2, 0 );
      WSADATA wsaData;

      int err = ::WSAStartup( wVersionRequested, &wsaData );

      if( err != 0 )
      {
         // error
         uStatus |= SOCKET_STATE::INIT_ERROR;
         LOGGING( "initSocket failed\n" );
         bInitialized_ =  false;
      }
      else
      {
         LOGGING( "initSocket successful\n" );
         bInitialized_ = true;
      }
   }
}
//*******************************************************************
//
//
bool YBSocket::connectServer()
{
   if(  bInitialized_ )
   {

      LPHOSTENT lpHostEntry;

      lpHostEntry = ::gethostbyname( svrAddress_ );

      conSocket_ = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

      if( conSocket_ == INVALID_SOCKET )
      {
         uStatus |= SOCKET_STATE::CREATE_ERROR;
         LOGGING("connectServer, create socket failed\n" );
         return(false);
      }
      struct sockaddr_in serverAddr;
      ::memset( (void *) &serverAddr, 0, sizeof( serverAddr ) );

      serverAddr.sin_family = AF_INET;
      serverAddr.sin_port = ::htons( serverPort_ );
      unsigned long ulAddress = ::inet_addr( lpHostEntry->h_name );

	   serverAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
      short sRc;
      sRc = ::connect( conSocket_, (struct sockaddr *) &serverAddr,
                    sizeof( serverAddr ) );
      if( sRc < 0 )
      {
         uStatus |= SOCKET_STATE::CONNECT_ERROR;
         LOGGING("connectServer, connection failed\n" );
         return(false);
      }
   }
   LOGGINGWITHTIMESTAMP( "connectServer, successfully connected!!\n" );
   return true;
}
//**********************************************************************
//
//
bool YBSocket::readWrite(const char* strIn,std::string& strOut,unsigned int uLength  )
{

   // send the data    
   LOGGING("YBSocket: sending....\n" );
   int nRet = ::send(conSocket_,	// Connected socket
			   strIn,					// Data buffer
			   uLength,			// Length of data
			   0);						// Flags
   if (nRet == SOCKET_ERROR)
   {
      uStatus |= SOCKET_STATE::SEND_ERROR;
      LOGGING("YBSocket: sending error,close socket \n" );
      ::closesocket(conSocket_);
	   return false;
   }
   LOGGING( "YBSocket: receiving.... \n" );

   strOut = "";
  unsigned long ulRecvByte;
  do
   { 
      ::memset( (void *) &cOutbuf, 0, sizeof( cOutbuf ) );
      ulRecvByte = ::recv(conSocket_,				// Connected socket
				            cOutbuf,					// Receive buffer
				            sizeof(cOutbuf),			// Size of receive buffer
				            0);						// Flags
	   if (ulRecvByte == SOCKET_ERROR)
	   {
         uStatus |= SOCKET_STATE::RECEIVE_ERROR;
         LOGGING( "YBSocket: receive error!!!\n" );		
		   return false;
	   }
      cOutbuf[ulRecvByte] = '\0';
      strOut.append( cOutbuf );
   }  while( cOutbuf[ulRecvByte - 1] != '\0' );
   LOGGINGWITHTIMESTAMP( "YBSocket: received.... \n" );
   LOGGING( strOut );
   return true;
}
//*************************************************************************
unsigned int YBSocket::getSocketStatus()
{
   if( uStatus != SOCKET_STATE::OK )
   {
      if( uStatus & SOCKET_STATE::CONNECT_ERROR )
      {
         LOGGINGWITHTIMESTAMP( "YBSocket Connection error.... \n" );      
      }
      if( uStatus & SOCKET_STATE::INIT_ERROR )
      {
         LOGGINGWITHTIMESTAMP( "YBSocket initialization error.... \n" );      
      }
      if( uStatus & SOCKET_STATE::CREATE_ERROR )
      {
         LOGGINGWITHTIMESTAMP( "YBSocket creation error.... \n" );      
      }
      if( uStatus & SOCKET_STATE::RECEIVE_ERROR )
      {
         LOGGINGWITHTIMESTAMP( "YBSocket receiving error.... \n" );      
      }
      if( uStatus & SOCKET_STATE::SEND_ERROR )
      {
         LOGGINGWITHTIMESTAMP( "YBSocket sending error.... \n" );      
      }   
   }
   return uStatus;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/YBSocket.cpp-arc  $
// 
//    Rev 1.1   Nov 08 2005 14:18:02   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 15:02:42   yingbaol
// Initial revision.
 * 
 *

 */






