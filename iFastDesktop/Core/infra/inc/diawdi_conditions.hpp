//Computer Generated Condition File for Module: diawdi


#ifndef DIAWDI_CONDITIONS
#define DIAWDI_CONDITIONS


#pragma message("including "__FILE__ )
#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#undef DIAWDI_LINKAGE
#ifdef DIAWDI_DLL
#define DIAWDI_LINKAGE CLASS_EXPORT
#else
#define DIAWDI_LINKAGE CLASS_IMPORT
#endif

namespace CND_DIAWDI
{
   extern DIAWDI_LINKAGE const I_CHAR * DIAWDI_CONDITION;


   extern DIAWDI_LINKAGE const long DIAWDI_INVALID_DATE_TIME_PASSED;
   extern DIAWDI_LINKAGE const long DIAWDI_LOAD_MODULE_FAIL;
   extern DIAWDI_LINKAGE const long DIAWDI_LOAD_PROC_FAIL;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_INVALID_PASSWORD;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_USER_ALREADY_LOGGED_ON;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_PASSWORD_EXPIRED;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_INVALID_OPID;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_USER_DISABLED;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_INVALID_NEW_PASSWORD;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_OTHER_ERROR;
   extern DIAWDI_LINKAGE const long DIAWDI_LOGON_NO_ERROR;
}

using namespace CND_DIAWDI;

#endif
