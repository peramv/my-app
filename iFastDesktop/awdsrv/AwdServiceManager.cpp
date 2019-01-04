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
// ^FILE   : AwdServiceManager.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 28, 2005
//
// ^CLASS    : AwdServiceManager
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AwdServiceManager.hpp"
#include "AWDBPConfig.hpp"
#include "BPResult.hpp"
#include "AwdLobData.hpp"
#include "awdbase.hpp"
#include "YBSocket.hpp"
#include "AwdServiceFactory.hpp"
#include <xercesc\util\PlatformUtils.hpp>
#include "StringHelp.hpp"

//HMODULE hModule = NULL;
AwdServiceManager *AwdServiceManager::_pInstance = NULL;

namespace ServiceName
{
   extern char * const MailingService;                    
   extern char * const FundGroupMailingService;           
};
//******************************************************************************
void AwdServiceManager::killInstance()
{
   delete _pInstance;
   _pInstance = NULL;
}

//******************************************************************************
AwdServiceManager *AwdServiceManager::getInstance()
{
   if( _pInstance == NULL )
   {
      _pInstance = new AwdServiceManager();
      
   }      
   return(_pInstance);
}

//******************************************************************************
AwdServiceManager::AwdServiceManager()
{
  _pAWDBPConfig = NULL;
  _pServiceFactory = NULL;
  _pSocket = NULL;
  xercesc::XMLPlatformUtils::Initialize();
  _hDTMAWDX = LoadLibrary( "dtmawdx.dll" );


}
//******************************************************************************
AwdServiceManager::~AwdServiceManager()
{
   delete _pAWDBPConfig;  
   delete _pServiceFactory;
   delete _pSocket;
   _pAWDBPConfig = NULL;
   _pServiceFactory = NULL;
   _pSocket = NULL;
   xercesc::XMLPlatformUtils::Terminate();
   FreeLibrary( _hDTMAWDX );
   _hDTMAWDX = NULL;
}

//******************************************************************************
AWDBPConfig* AwdServiceManager::getConfig()
{
   if( !_pAWDBPConfig )
   {
      _pAWDBPConfig =  new AWDBPConfig();
      if( _pAWDBPConfig )
      {
         _pAWDBPConfig->init();
      }
      assert( _pAWDBPConfig != NULL );
   }
   return _pAWDBPConfig;
}
//*******************************************************************************
bool AwdServiceManager::requestService(AwdLobData& lobData,BPResult& result )
{
   std::string dstrFundGroup = lobData.getLobFieldValue(getConfig()->getFundGroup() );
   dstrFundGroup = StringHelp::strip( dstrFundGroup );
   AwdBase* pService = NULL;
   if( dstrFundGroup != "" )
   {
      pService = getServiceFactory()->getService( ServiceName::FundGroupMailingService );
   }
   else
   {
      pService = getServiceFactory()->getService( ServiceName::MailingService );   
   }
   if( pService )
   {
      YBSocket* pSocket = getSocket();
      if( pSocket && (pSocket->getSocketStatus() == YBSocket::OK ) )
      {
         return ( pService->requestService( lobData, result,getSocket() ) );        
      }
   }
   return false;
}
//*********************************************************************************
AwdServiceFactory* AwdServiceManager::getServiceFactory()
{
   if( !_pServiceFactory )
   {
     _pServiceFactory =  new AwdServiceFactory();
      assert( _pServiceFactory != NULL );
   }
   return _pServiceFactory;
}
//***********************************************************************************
YBSocket* AwdServiceManager::getSocket()
{
   if( _pSocket )  // BP Server does not support continuely reuse the same socket
   {
      delete _pSocket;
     _pSocket = NULL; 
   }
   if( !_pSocket )
   {
      _pSocket = new YBSocket();
      if( _pSocket )
      {
         std::string address = getConfig()->getIPAddress( );
         std::string port = getConfig()->getPortNum( );
         _pSocket->init(address.c_str(),atoi(port.c_str() ) );      
      }
   }
   return _pSocket;
}
//************************************************************************************
void* AwdServiceManager::getFunctionAddress( std::string function )
{
   void* ptr;
   if( _hDTMAWDX )
    {
       ptr = GetProcAddress(_hDTMAWDX, function.c_str() );
    }
    return ptr;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdServiceManager.cpp-arc  $
// 
//    Rev 1.3   Nov 15 2005 16:10:32   yingbaol
// PET1332,FN09: BP Server does not support reuse socket.
// 
//    Rev 1.2   Nov 14 2005 11:40:00   yingbaol
// PET1332,FN09:fix issue
// 
//    Rev 1.1   Nov 08 2005 14:17:00   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 14:54:28   yingbaol
// Initial revision.
 * 
 *

 */





