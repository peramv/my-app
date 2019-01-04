/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

#ifndef PROPERTYREPOSITORY_HPP
   #include "propertyrepository.hpp"
#endif

namespace
{  // Depending on PropertyRepository set up to enable these flags to work
   //  cleanly without locking
   static bool bCaseFlagSet = false;
   static bool bCaseSensitive = false;
}

// This depends on PropertyRepository being set up first.
CaseInsensitiveCompare::CaseInsensitiveCompare()
{
   // Depending on PropertyRepository set up to enable these flags to work
   //  cleanly without locking.  PropertyRepository must be constructed before
   //  this method is used.
   if ( !bCaseFlagSet )
   {
      bCaseSensitive = PropertyRepository::isCaseSensitive();
      bCaseFlagSet = true;
   }
}


bool CaseInsensitiveCompare::operator() ( const DString& x,
                                          const DString& y ) const
{
   if ( bCaseSensitive )
   {
      return i_strcmp( x.c_str(), y.c_str() ) < 0;
   }
   else
   {
      return i_stricmp( x.c_str(), y.c_str() ) < 0;
   }
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/caseinsensitivecompare.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:16   kovacsro
// Initial revision.
//
//   Rev 1.2   May 21 2001 13:50:00   DT21858
//Now includes srcprag.h correctly
//
//   Rev 1.1   Mar 02 2001 14:13:00   dt24433
//Changed to cache case sensitivity flag for performance.
//
//   Rev 1.0   Jun 08 2000 10:29:12   dtwk
//
//



