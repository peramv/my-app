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

#include <commonport.h>
//#include <string.h>
//#include <stdio.h>

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
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfawdi/moduleinfo.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:39:58   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:10   SMITHDAV
// Initial revision.
// 
//    Rev 1.1   Jan 28 1999 13:53:02   DMUM
// Checkin for VCPP 6.0
// 
//
//    Rev 1.0   29 Jul 1998 20:28:42   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.0   Mar 30 1998 13:48:40   dmum
//
//

