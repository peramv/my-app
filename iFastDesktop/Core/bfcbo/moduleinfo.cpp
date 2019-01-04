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
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/moduleinfo.cpp-arc  $", "$Revision:   1.3  $" )

#include <CommonPort.h>
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
/*
 * $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/moduleinfo.cpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:40:14   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   03 Jul 2001 16:23:24   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.1   03 May 2001 14:02:42   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.0   Feb 15 2000 10:57:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:02:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 * 
 *    Rev 1.0   Jul 07 1999 13:44:40   SMITHDAV
 * Original revision.
 * 
 */

