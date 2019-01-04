#ifndef INFRAMUTEX_HPP
#define INFRAMUTEX_HPP

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

class DICORE_LINKAGE InfraMutex : public InfraKernel
{
public:
   //creates a InfraMutex object
   //the status must be checked after using this constructor
   InfraMutex( bool bInitialOwner = false, const char* name = NULL,
            LPSECURITY_ATTRIBUTES lpSecurityAttrib = NULL );
   //opens an existing InfraMutex
   //the status must be checked after using this constructor
   InfraMutex( const char* name, bool bInheritHandle = FALSE, DWORD dwDesiredAccess = MUTEX_ALL_ACCESS );
   virtual ~InfraMutex();
   //releases ownership of this mutex object
   void release();
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraMutex.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:50   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:30   DT11159
// 
//
//

#endif
