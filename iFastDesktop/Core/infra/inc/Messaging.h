#ifndef MESSAGING_H
#define MESSAGING_H

#ifdef __aix__
typedef int crid_t;
typedef int class_id_t;
#endif

#include "commonport.h"
#include <stdio.h>

#include <string>
#include <vector>
#include <map>

typedef std::vector< std::string > STRING_LIST;

#undef DIMESSAGE_LINKAGE
#ifdef _WIN32
#ifdef DIMESSAGE_DLL
   #define DIMESSAGE_LINKAGE CLASS_EXPORT
#else
   #define DIMESSAGE_LINKAGE CLASS_IMPORT
#endif
#else
#define DIMESSAGE_LINKAGE
#endif

#endif


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//



