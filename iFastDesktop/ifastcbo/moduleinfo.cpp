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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/moduleinfo.cpp-arc  $
 * 
 *    Rev 1.3   Nov 14 2004 14:50:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.2   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   22 May 2002 18:29:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:02:34   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 * 
 *    Rev 1.0   Jul 07 1999 13:49:40   SMITHDAV
 * Original revision.
 *
 */
