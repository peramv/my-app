#pragma once
//******************************************************************************
//
//  These tags are used in the session.ini file.  It is very important
//  that any information that session will send to AWD or to a log file
//  must have a #define here so that the tag may be consistant with
//  what it shall be in the session.ini file.
//
//******************************************************************************

#include <commonport.h>

#undef BFSESSN_LINKAGE
#ifdef BFSESSN_DLL
   #define BFSESSN_LINKAGE CLASS_EXPORT
#else
   #define BFSESSN_LINKAGE CLASS_IMPORT
#endif

namespace SessionTags
{
   // Tags
   extern BFSESSN_LINKAGE const I_CHAR * AWD_COMMENT;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_EVENT;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_ID;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_PROPAGATE;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_PWORK;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_WORK;
   extern BFSESSN_LINKAGE const I_CHAR * BEGIN_TIME;
   extern BFSESSN_LINKAGE const I_CHAR * BUSINESS_AREA;
   extern BFSESSN_LINKAGE const I_CHAR * CALL_END;
   extern BFSESSN_LINKAGE const I_CHAR * CALL_START;
   extern BFSESSN_LINKAGE const I_CHAR * CONFIG;
   extern BFSESSN_LINKAGE const I_CHAR * CREATE_CASE;
   extern BFSESSN_LINKAGE const I_CHAR * CREATE_WORK;
   extern BFSESSN_LINKAGE const I_CHAR * DEFAULT;
   extern BFSESSN_LINKAGE const I_CHAR * DISPLAY_CSD;
   extern BFSESSN_LINKAGE const I_CHAR * END_TIME;
   extern BFSESSN_LINKAGE const I_CHAR * EVENT_ID;
   extern BFSESSN_LINKAGE const I_CHAR * EVENT_TIME;
   extern BFSESSN_LINKAGE const I_CHAR * HLLAPI;
   extern BFSESSN_LINKAGE const I_CHAR * ISTATUS;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_EVENT;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_ITEM;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_PASSWORD;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_PITEM;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_SOURCE;
   extern BFSESSN_LINKAGE const I_CHAR * LOG_USER;
   extern BFSESSN_LINKAGE const I_CHAR * MESSAGE;
   extern BFSESSN_LINKAGE const I_CHAR * NEW_BEGIN_TIME;
   extern BFSESSN_LINKAGE const I_CHAR * NO_WORK;
   extern BFSESSN_LINKAGE const I_CHAR * ORIGINATION;
   extern BFSESSN_LINKAGE const I_CHAR * ORIG_PAPER;
   extern BFSESSN_LINKAGE const I_CHAR * ORIG_PHONE;
   extern BFSESSN_LINKAGE const I_CHAR * PRIMARY;
   extern BFSESSN_LINKAGE const I_CHAR * PSTATUS;
   extern BFSESSN_LINKAGE const I_CHAR * QUEU;
   extern BFSESSN_LINKAGE const I_CHAR * STATUS;
   extern BFSESSN_LINKAGE const I_CHAR * STATUS_TYPE;
   extern BFSESSN_LINKAGE const I_CHAR * TA2K_ID;
   extern BFSESSN_LINKAGE const I_CHAR * TABLE;
   extern BFSESSN_LINKAGE const I_CHAR * UPDATE_WORK;
   extern BFSESSN_LINKAGE const I_CHAR * WORK_TYPE;

   // These are Configuration objects
   extern BFSESSN_LINKAGE const I_CHAR * AWD_CASE;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_PCASE;
   extern BFSESSN_LINKAGE const I_CHAR * CASE_TABLE;
   extern BFSESSN_LINKAGE const I_CHAR * EVENT_LOG;
   extern BFSESSN_LINKAGE const I_CHAR * EVENT_LOGGING;
   extern BFSESSN_LINKAGE const I_CHAR * EXPORT_TABLE;
   extern BFSESSN_LINKAGE const I_CHAR * HLLAPI_EVENT;
   extern BFSESSN_LINKAGE const I_CHAR * NOT_PROCESSED;
   extern BFSESSN_LINKAGE const I_CHAR * ROAD_TABLE;
   extern BFSESSN_LINKAGE const I_CHAR * USE_AWD;
   extern BFSESSN_LINKAGE const I_CHAR * USE_AWD_PORTAL;
   extern BFSESSN_LINKAGE const I_CHAR * WORK_TABLE;
   extern BFSESSN_LINKAGE const I_CHAR * USE_CALL_CENTRE;


   // These are the Configuration IDI name values
   extern BFSESSN_LINKAGE const I_CHAR * WORK_OBJECT_DETAILS;
   extern BFSESSN_LINKAGE const I_CHAR * AWD_ERROR;
}

