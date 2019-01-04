#pragma message( "including "__FILE__ )

#ifndef BASEHOSTCONNECTIONMONITOR_HPP
#define BASEHOSTCONNECTIONMONITOR_HPP

/**
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

#ifndef PLATFORM_H
   #include "platform.h"
#endif

class BaseHostConnectionManager;

// Import/Export resolution
#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif

/**
 * Base Host Connection Monitor class
 *
 * Class is the parent for all host connection monitor classes.  It provides the
 * common functions needed to monitor the status of a host connection manager.
 */
class DIVIEW_LINKAGE BaseHostConnectionMonitor
{
public:
   virtual bool refresh( ) = 0;
};

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
// $Log:   Y:/VCS/iFastAWD/inc/BaseHostConnectionMonitor.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:04   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:26   DT11159
// 
//
//

#endif
