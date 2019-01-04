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
//                module's build date and possibly others at a later time
//
//******************************************************************************

// If you are not road.exe then you probably want to remove the following line
#include "stdafx.h"

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

// If you are not road.exe then you probably want to add in the following lines
//#include <string.h>
//#include <stdio.h>

extern "C" long fnGetModuleInfo( char *buffer, unsigned long bufSize )
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
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ModuleInfo.cpp-arc  $
 * 
 *    Rev 1.2   May 26 2003 15:32:00   PURDYECH
 * fnGetModuleInfo should no longer be exported.  This export causes a .lib file to be generated for this executable!
 * 
 *    Rev 1.1   Oct 09 2002 23:55:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

