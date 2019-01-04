#ifndef STDINCLUDE_H
#define STDINCLUDE_H

#  pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */


#ifndef COMMONPORT_H
   #include "commonport.h"
#endif   
#ifndef BASE_H
   #include "base.h"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif
#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#endif // STDINCLUDE_H


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
// $Log:   Y:/VCS/iFastAWD/inc/stdinclude.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:48   kovacsro
//Initial revision.
// 
//    Rev 1.4   28 Nov 2000 10:37:02   dt14177
// cleanup
// 
//    Rev 1.3   26 Feb 1999 15:06:24   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.2   18 Feb 1999 10:40:10   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:06:56   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:43:24   DMUM
// Check in for DICORE
//

