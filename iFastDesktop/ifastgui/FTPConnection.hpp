#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 International Financial
//
//
//******************************************************************************
//
// ^FILE   :  FTPConnection.hpp
// ^AUTHOR :  
// ^DATE   :  
//
//******************************************************************************

#include <win32\platform.h>

class CFtpConnection;
class CInternetFile;
class CInternetSession;

class FTPConnection
{
public:
   FTPConnection( const DString& connectionName, const DString& hostAddress, int port, const DString& userId = NULL_STRING, const DString& pwd=NULL_STRING );
   ~FTPConnection();
   void ReadFile( const DString& dstrFile, DString& dstrOutFile );     
   bool isConnected() const { return _connected; }

private:
   void freeResponse();
   void connect(const DString& hostAddress, int port, const DString& userId, const DString& pwd);
   void disconnect();

   bool _connected;   
   CInternetSession* _pCInternetSession;
   CFtpConnection *_pCFtpConnection;
   CInternetFile *_pCInternetFile;
   DString _connectionName;   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FTPConnection.hpp-arc  $
//
//   Rev 1.1   Apr 25 2003 12:28:44   PURDYECH
//Fixed some memory leaks
//
//   Rev 1.0   Dec 08 2002 22:16:20   HSUCHIN
//Initial Revision
//
*/