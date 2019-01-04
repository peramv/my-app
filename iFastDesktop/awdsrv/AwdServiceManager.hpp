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
// ^FILE   : AwdServiceManager.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    :AwdServiceManager
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once


class AWDBPConfig;
class AwdLobData;
class BPResult;
class AwdServiceFactory;
class YBSocket;
class  AwdServiceManager
{
public:
   static AwdServiceManager* getInstance();
   static void killInstance();
   AWDBPConfig* getConfig();
   bool requestService(AwdLobData& lobData,BPResult& result );
   void* getFunctionAddress(std::string function );
private:
   AwdServiceManager( );
   ~AwdServiceManager(); 
   AwdServiceFactory* getServiceFactory();
   YBSocket* getSocket();
private:
   static AwdServiceManager* _pInstance;
   AWDBPConfig*   _pAWDBPConfig;
   AwdServiceFactory* _pServiceFactory;
   YBSocket*     _pSocket;
   HINSTANCE     _hDTMAWDX;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdServiceManager.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:17:02   yingbaol
//PET1332,FN09: Remove DString and Infra structure
//
//   Rev 1.0   Oct 31 2005 14:54:36   yingbaol
//Initial revision.
 * 
 *

 */


