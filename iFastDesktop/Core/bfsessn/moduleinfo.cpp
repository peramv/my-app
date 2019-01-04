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
#include "win32/stdafx.h"

#include <string.h>
#include <stdio.h>

extern "C" long EXPORTWIN fnGetModuleInfo( char *buffer, unsigned long bufSize )
{
   const char *date = __DATE__;
   const char *time = __TIME__;
   const char *format = "Date: %s Time: %s";

   //Check to make sure buffer is large enough
   if( ( strlen( date ) + strlen( time ) + strlen( format ) ) > ( bufSize - 1 ) )
   {
      return(-1);          //Return error
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

   return(buildType);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/moduleinfo.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 08:58:46   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:04   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:14   SMITHDAV
// Initial revision.
// 
//    Rev 1.1   Jan 28 1999 14:04:08   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:33:16   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.0   Mar 30 1998 14:03:24   dmum
//
//

