#pragma once
#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#undef BFSESSN_LINKAGE
#ifdef BFSESSN_DLL
   #define BFSESSN_LINKAGE CLASS_EXPORT
#else
   #define BFSESSN_LINKAGE CLASS_IMPORT
#endif

namespace CND_DISESSN
{
   extern BFSESSN_LINKAGE const I_CHAR * DISESSN_CONDITION;


   extern BFSESSN_LINKAGE const long DISESSN_AWD_NOT_LOGGED_ON;
   extern BFSESSN_LINKAGE const long DISESSN_CHILD_NOT_REMOVED;
   extern BFSESSN_LINKAGE const long DISESSN_DEFAULT_LABEL_USED;
   extern BFSESSN_LINKAGE const long DISESSN_UNDEFINED_AWD_PARAMETER;
   extern BFSESSN_LINKAGE const long DISESSN_AWD_WORK_CREATED;
   extern BFSESSN_LINKAGE const long DIODBC_ERROR;
   extern BFSESSN_LINKAGE const long DIODBC_INFO;
   extern BFSESSN_LINKAGE const long DIODBC_CONNECT_ERROR;
}

using namespace CND_DISESSN;

