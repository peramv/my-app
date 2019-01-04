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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DstcFuncs.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 6/11/97
//
// -----------------------------------------------------------------------------
//
//
//******************************************************************************
#define WIN32UIBASE_DLL

#include "stdafx.h"

#ifndef CONFIGMANAGER_HPP
   #include <configmanager.hpp>
#endif

#ifndef DSTCFUNCS_H
   #include "DstcFuncs.h"
#endif
namespace CND
{
}


//******************************************************************************

DString &stripComplete(
                      DString &strOut
                      )
{
   strOut.stripAll();
   stripLeading( strOut, '0' );
   return(strOut);
}

//******************************************************************************

int setOleDateFromHost(
                      COleDateTime &dateOut,
                      DString &strHost,
                      DString Type
                      )
{
   strHost.stripTrailing();
   if( strHost != NULL_STRING )
   {
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                             I_( "HostMasks" ), Type );

      // Defaults
      if( mask.empty() )
      {
         if( Type == I_("T") )
         {
            mask = I_("HH:mm");
         }
      }

      if( Type == I_("D") )
      {
         int d,M,y,i;
         DString tmp;
         i=mask.find(I_("MM"));
         tmp.assign( strHost, i,2 );
         M=tmp.asInteger();
         i=mask.find(I_("dd"));
         tmp.assign( strHost, i,2 );
         d=tmp.asInteger();
         i=mask.find(I_("yyyy"));
         tmp.assign( strHost, i,4 );
         y=tmp.asInteger();

         return(dateOut.SetDate( y, M, d ));
      }
      else if( Type == I_("T") )
      {
         int H, m, s, i;
         DString tmp;
         i=mask.find(I_("HH"));
         tmp.assign( strHost, i,2 );
         H=tmp.asInteger();
         i=mask.find(I_("mm"));
         tmp.assign( strHost, i,2 );
         m=tmp.asInteger();
         s = 0;

         return(dateOut.SetTime( H, m, s ));
      }
      else
      {
        return 0;
      }
   }
   else
   {
	   dateOut = COleDateTime::GetCurrentTime();
	   // silly semantics of this function ... we must return 1 if the
	   // date was successfully set, so this is the result...
	   return( dateOut.GetStatus() != COleDateTime::valid );
//.NET      return(dateOut=COleDateTime::GetCurrentTime());
//      return dateOut.SetDate( 9999, 12, 31 );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DstcFuncs.cpp-arc  $
//
//   Rev 1.6   Jul 11 2005 13:46:08   hernando
//PET1250 FN01 - Added default Time mask.
//
//   Rev 1.5   Jul 06 2005 13:58:22   hernando
//PET1250 FN01 - Added support for time.
//
//   Rev 1.4   Nov 14 2004 15:02:10   purdyech
//PET910 - .NET Conversion
 * 
 *    Rev 1.3   Oct 09 2002 17:42:40   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Sep 20 2002 15:19:24   SMITHDAV
 * Remove unused function.
 * 
 *    Rev 1.1   Sep 10 2002 14:34:32   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Jan 17 2000 15:22:06   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.6   Jan 05 2000 14:40:58   YINGBAOL
 * fix
 * 
 *    Rev 1.5   Dec 21 1999 14:37:02   YINGBAOL
 * add change hllapi screen
 * 
 *    Rev 1.4   Nov 17 1999 16:56:12   YINGZ
 * change setOleDateFromHost to use real mask
 * 
 *    Rev 1.3   Sep 01 1999 11:49:48   DT24433
 * added setOleDateFromHost
 * 
 *    Rev 1.2   Jul 20 1999 11:18:40   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:04:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
