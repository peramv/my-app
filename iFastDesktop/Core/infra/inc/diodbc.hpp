#ifndef DIODBC_HPP
#define DIODBC_HPP

#pragma message( "including "__FILE__ )

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
// ^FILE   : diodbc.hpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 27 Jan 1999
//
// ^CLASS  : CSQLColumn
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#undef DIODBC_LINKAGE
#ifdef DIODBC_DLL
   #define DIODBC_LINKAGE CLASS_EXPORT
#else
   #define DIODBC_LINKAGE CLASS_IMPORT
#endif

namespace Odbc
{
   enum Type
   {
      sqlUnknown,
      sqlChar,
      sqlInteger,
      sqlSmallint,
      sqlReal,
      sqlDouble,
      sqlDefault
   };
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
// $Log:   Y:/VCS/iFastAWD/inc/diodbc.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:12   kovacsro
//Initial revision.
// 
//    Rev 1.1   Apr 19 1999 12:59:12   DTWK
// Move headers from DISESSION to INC to avoid breaking 1.6 and 1.7 compiles
//
//    Rev 1.0   Apr 16 1999 17:50:30   DMUM
//
//
//    Rev 1.0.1.0   Mar 30 1999 14:29:42   DMUM
// Sync Up with latest 1.6.x
//
//    Rev 1.0   Feb 08 1999 10:51:40   DMUM
//
//
//

#endif // DIODBC_HPP

