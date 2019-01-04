//////////////////////////////////////////////////////////////////////
#pragma once
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\bfconnection.hpp>

#define APP_MESSAGE_SIZE 128L

extern "C"
{
#include <win32\vm.h>
#include <win32\vmdll.h>
#include <win32\vmdst.h>
}

class VmPrivateConnection : public BFConnection  
{
public:
   VmPrivateConnection( const DStringA &hostId, const DStringA &connectionName );
   virtual ~VmPrivateConnection();

   virtual void send(const DStringA &viewName, const DStringA &request);
   virtual const DStringA &getResponse();

   virtual const DStringA &getHostId() const;
   virtual const DStringA &getDescription() const;

   virtual bool isStale() const;

   const DStringA &getName() const;


private:
   void connect();
   void freeResponse();
   void disconnect();

   const DStringA _hostId;
   const DStringA _connectionName;
   const DStringA _description;

   bool _connected;

   HANDLE _eventHandle;
   char _appName[9];
   char _semName[12];

   char _errMsg[APP_MESSAGE_SIZE];

   VMPRIV _vmPrivate;

   DStringA *_response;

};

