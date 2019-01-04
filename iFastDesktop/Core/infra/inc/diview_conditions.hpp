//Computer Generated Condition File for Module: diview


#ifndef DIVIEW_CONDITIONS
#define DIVIEW_CONDITIONS


#pragma message("including "__FILE__ )
#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
#define DIVIEW_LINKAGE CLASS_EXPORT
#else
#define DIVIEW_LINKAGE CLASS_IMPORT
#endif

namespace CND_DIVIEW
{
   extern DIVIEW_LINKAGE const I_CHAR * DIVIEW_CONDITION;


   extern DIVIEW_LINKAGE const long ERR_HOST_CONNECTION_MGR_NOT_FOUND;
   extern DIVIEW_LINKAGE const long ERR_CONNECT_APP_FAIL;
   extern DIVIEW_LINKAGE const long ERR_APP_REQUEST_FAIL;
   extern DIVIEW_LINKAGE const long ERR_APP_REQUEST_PRIV_FAIL;
   extern DIVIEW_LINKAGE const long ERR_NOTIFY_SEM_FAIL;
   extern DIVIEW_LINKAGE const long ERR_NOTIFY_WIN_FAIL;
   extern DIVIEW_LINKAGE const long ERR_CREATE_EVENT_FAIL;
   extern DIVIEW_LINKAGE const long ERR_WAIT_EVENT_FAIL;
   extern DIVIEW_LINKAGE const long ERR_READ_RESPONSE_FAIL;
   extern DIVIEW_LINKAGE const long ERR_EXTRACT_RESP_FAIL;
   extern DIVIEW_LINKAGE const long ERR_VIEWMGR_REQUEST_FAIL;
   extern DIVIEW_LINKAGE const long ERR_DISCONNECT_FAIL;
   extern DIVIEW_LINKAGE const long ERR_CONNECTION_TIMEOUT;
   extern DIVIEW_LINKAGE const long ERR_NON_RESERVED_CONNECTION_TIMEOUT;
   extern DIVIEW_LINKAGE const long ERR_RESERVATION_TIMEOUT;
}

using namespace CND_DIVIEW;

#endif
