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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  VmConnection.cpp
// ^AUTHOR :  Glen McNabb
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\bfrecordconnection.hpp>

#define APP_MESSAGE_SIZE 128L
#define VIEW_TIMEOUT  30000L // 30 second time out...

extern "C"
{
#include <win32\vm.h>
#include <win32\vmdll.h>
#include <win32\vmdst.h>
}

class EventSemaphore;
class Data;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE VmConnection : public BFRecordConnection
{
public:
   VmConnection( const DStringA &hostId, const DStringA &connectionName );
   virtual ~VmConnection();

   virtual void putRequest( const DStringA &viewName, const DStringA &request, bool bRecycleOnReceive, const BFData* pQuery = NULL, BFSecurity* pSecurity = NULL );
   virtual const DStringA &getResponse();

   virtual const DStringA &getHostId() const;
   virtual const DStringA &getDescription() const;
   virtual bool isStale() const;

   const unsigned long getViewReturnCode();
   const DStringA &getName() const;
   static bool shutdownAll();

private:
   void connect();
   void disconnect();

   const DStringA _hostId;
   const DStringA _connectionName;
   const DStringA _description;
   unsigned long _ulReturnCode;
   DString _dstrSemName;
   bool _connected;
   EventSemaphore * _pEventSemaphore;

   HANDLE _eventHandle;
   char _appName[9];
   char _semName[12];

   char _errMsg[APP_MESSAGE_SIZE];

   char* _pszResponseBuffer;

   VMREQ _vmRequest;
   VMGR_RESPONSE_HEADER _headerInfo;

   DStringA _dstraResponse;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfconmgr/VmConnection.hpp-arc  $
//
//   Rev 1.10   Oct 21 2009 10:40:06   purdyech
//LDAP Authorization Support
//
//   Rev 1.9   Mar 27 2009 10:11:12   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.8   Jan 27 2004 16:04:24   PURDYECH
//putRequest signature changed (see BFRecordConnection.hpp)
//
//   Rev 1.7   Jan 27 2003 15:23:40   PURDYECH
//BFConnection changes
//
//   Rev 1.6   Oct 09 2002 17:40:22   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Aug 29 2002 12:51:20   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.4   22 Mar 2002 15:12:12   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   Jul 10 2001 14:41:54   IVESPAUL
//30 second view timeout.
//
//   Rev 1.2   Jun 18 2001 10:23:42   IVESPAUL
//AdminCompany objects now contain twin FastHost objects.
//
//   Rev 1.1   May 22 2001 13:49:20   MCNABBGL
//server monitoring functionality, explicit server registration with connection manager, fastrequestor modifications
//
