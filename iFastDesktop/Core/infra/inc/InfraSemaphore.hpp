#ifndef INFRASEMAPHORE_HPP
#define INFRASEMAPHORE_HPP

#pragma message( "including "__FILE__ )

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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef PLATFORM_H
   #include "platform.h"
#endif

#ifndef INFRAKERNEL_HPP
   #include "infrakernel.hpp"
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE InfraSemaphore : public InfraKernel
{
public:
   //creates a InfraSemaphore object
   //the status must be checked after using this constructor
   InfraSemaphore( int nInitialCount, int nMaximumCount, const char* name = NULL,
                LPSECURITY_ATTRIBUTES lpSecurityAttrib = NULL );
   //opens an existing InfraSemaphore
   //the status must be checked after using this constructor
   InfraSemaphore( const char* name, bool bInheritHandle = FALSE, DWORD dwDesiredAccess = SEMAPHORE_ALL_ACCESS );
   virtual ~InfraSemaphore();
   //increases the count of this semaphore object by the specified amount
   void  release( long lReleaseCount, long *plPreviousCount = NULL );
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraSemaphore.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:52   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:34   DT11159
// 
//
//

#endif
