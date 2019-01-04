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
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ModuleInfo.cpp
// ^AUTHOR : Terry Erickson
// ^DATE   : 03-98
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^DESCRIPTION : This unit will generate information about this
//                module's build date and possible others at a later time
//
//******************************************************************************
#include <DString.hpp>

#include "commonport.h"
#include <string.h>
#include <stdio.h>

extern "C" long EXPORTWIN fnGetModuleInfo( char *buffer, unsigned long bufSize )
{
   const char *date = __DATE__;
   const char *time = __TIME__;
   const char *format = "Date: %s Time: %s";

   //Check to make sure buffer is large enough
   if ( ( strlen( date ) + strlen( time ) + strlen( format ) ) > ( bufSize - 1 ) )
   {
      return -1;          //Return error
   }

   //Format the buffer that was passed to us
   sprintf( buffer, format, date, time );

   long buildType = 0;     //Local compile

   #ifdef BSV_BUILD        //Build server compile
      buildType = 1;
   #endif
   #ifdef LMG_BUILD        //Library management compile
      buildType = 2;
   #endif

   return buildType;
}

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
// $Log:   Y:/VCS/iFastAWD/didbrkr/moduleinfo.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:30   kovacsro
// Initial revision.
// 
//    Rev 1.2   Jan 28 1999 14:04:02   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 15:43:24   DMUM
//
//
//    Rev 1.0   Mar 30 1998 13:55:30   dmum
//
//

