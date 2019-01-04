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
// ^FILE   : YBSocket.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 30, 2005
//
// ^CLASS    :YBSocket
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once
 #include <string>

class  YBSocket
{
public:
   YBSocket( );
   ~YBSocket(void);
   bool readWrite( const char* strIn, std::string& strOut, unsigned int uLength  );
   bool init( const char* address, unsigned short port );
   unsigned int  getSocketStatus();
 
   enum SOCKET_STATE 
   {
      OK                      = 0x0000,
      CREATE_ERROR            = 0x0001,
      INIT_ERROR              = 0x0002,
      CONNECT_ERROR           = 0x0004,
      SEND_ERROR              = 0x0008,
      RECEIVE_ERROR           = 0x0010
   };
private:
   void initSocket();
   bool connectServer(); 
   std::string convertIntToString(int iNum);
private:
   char svrAddress_[16];
   unsigned short serverPort_;
   bool bInitialized_;
   SOCKET	conSocket_;
   char cOutbuf[256];
   unsigned int uStatus;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/YBSocket.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:18:04   yingbaol
//PET1332,FN09: Remove DString and Infra structure
//
//   Rev 1.0   Oct 31 2005 15:02:52   yingbaol
//Initial revision.
 * 
 *

 */









