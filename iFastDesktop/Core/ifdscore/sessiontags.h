#ifndef SESSIONTAGS_H
#define SESSIONTAGS_H


//******************************************************************************
//
//  These tags are used in the session.ini file.  It is very important
//  that any information that session will send to AWD or to a log file
//  must have a #define here so that the tag may be consistant with
//  what it shall be in the session.ini file.
//
//******************************************************************************

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#undef DISESSN_LINKAGE
#ifdef DISESSN_DLL
   #define DISESSN_LINKAGE CLASS_EXPORT
#else
   #define DISESSN_LINKAGE CLASS_IMPORT
#endif

namespace SessionTags
{
   // Tags
   extern DISESSN_LINKAGE const I_CHAR * AWD_COMMENT;
   extern DISESSN_LINKAGE const I_CHAR * AWD_EVENT;
   extern DISESSN_LINKAGE const I_CHAR * AWD_ID;
   extern DISESSN_LINKAGE const I_CHAR * AWD_PROPAGATE;
   extern DISESSN_LINKAGE const I_CHAR * AWD_PWORK;
   extern DISESSN_LINKAGE const I_CHAR * AWD_WORK;
   extern DISESSN_LINKAGE const I_CHAR * BEGIN_TIME;
   extern DISESSN_LINKAGE const I_CHAR * BUSINESS_AREA;
   extern DISESSN_LINKAGE const I_CHAR * CALL_END;
   extern DISESSN_LINKAGE const I_CHAR * CALL_START;
   extern DISESSN_LINKAGE const I_CHAR * CONFIG;
   extern DISESSN_LINKAGE const I_CHAR * CREATE_CASE;
   extern DISESSN_LINKAGE const I_CHAR * CREATE_WORK;
   extern DISESSN_LINKAGE const I_CHAR * DEFAULT;
   extern DISESSN_LINKAGE const I_CHAR * DISPLAY_CSD;
   extern DISESSN_LINKAGE const I_CHAR * END_TIME;
   extern DISESSN_LINKAGE const I_CHAR * EVENT_ID;
   extern DISESSN_LINKAGE const I_CHAR * EVENT_TIME;
   extern DISESSN_LINKAGE const I_CHAR * HLLAPI;
   extern DISESSN_LINKAGE const I_CHAR * ISTATUS;
   extern DISESSN_LINKAGE const I_CHAR * LOG_EVENT;
   extern DISESSN_LINKAGE const I_CHAR * LOG_ITEM;
   extern DISESSN_LINKAGE const I_CHAR * LOG_PASSWORD;
   extern DISESSN_LINKAGE const I_CHAR * LOG_PITEM;
   extern DISESSN_LINKAGE const I_CHAR * LOG_SOURCE;
   extern DISESSN_LINKAGE const I_CHAR * LOG_USER;
   extern DISESSN_LINKAGE const I_CHAR * MESSAGE;
   extern DISESSN_LINKAGE const I_CHAR * NEW_BEGIN_TIME;
   extern DISESSN_LINKAGE const I_CHAR * NO_WORK;
   extern DISESSN_LINKAGE const I_CHAR * ORIGINATION;
   extern DISESSN_LINKAGE const I_CHAR * ORIG_PAPER;
   extern DISESSN_LINKAGE const I_CHAR * ORIG_PHONE;
   extern DISESSN_LINKAGE const I_CHAR * PRIMARY;
   extern DISESSN_LINKAGE const I_CHAR * PSTATUS;
   extern DISESSN_LINKAGE const I_CHAR * QUEU;
   extern DISESSN_LINKAGE const I_CHAR * STATUS;
   extern DISESSN_LINKAGE const I_CHAR * STATUS_TYPE;
   extern DISESSN_LINKAGE const I_CHAR * TA2K_ID;
   extern DISESSN_LINKAGE const I_CHAR * TABLE;
   extern DISESSN_LINKAGE const I_CHAR * UPDATE_WORK;
   extern DISESSN_LINKAGE const I_CHAR * WORK_TYPE;

   // These are Configuration objects
   extern DISESSN_LINKAGE const I_CHAR * AWD_CASE;
   extern DISESSN_LINKAGE const I_CHAR * AWD_PCASE;
   extern DISESSN_LINKAGE const I_CHAR * CASE_TABLE;
   extern DISESSN_LINKAGE const I_CHAR * EVENT_LOG;
   extern DISESSN_LINKAGE const I_CHAR * EVENT_LOGGING;
   extern DISESSN_LINKAGE const I_CHAR * EXPORT_TABLE;
   extern DISESSN_LINKAGE const I_CHAR * HLLAPI_EVENT;
   extern DISESSN_LINKAGE const I_CHAR * NOT_PROCESSED;
   extern DISESSN_LINKAGE const I_CHAR * ROAD_TABLE;
   extern DISESSN_LINKAGE const I_CHAR * USE_AWD;
   extern DISESSN_LINKAGE const I_CHAR * USE_AWD_PORTAL;
   extern DISESSN_LINKAGE const I_CHAR * WORK_TABLE;
   extern DISESSN_LINKAGE const I_CHAR * USE_CALL_CENTRE;


   // These are the Configuration IDI name values
   extern DISESSN_LINKAGE const I_CHAR * WORK_OBJECT_DETAILS;
   extern DISESSN_LINKAGE const I_CHAR * AWD_ERROR;
}

#endif // SESSIONTAGS_H
