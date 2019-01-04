#ifndef KERNEL_HPP
#define KERNEL_HPP

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

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

//base class for the MT objects in this DLL
class DICORE_LINKAGE InfraKernel
{
protected:
   //Constructor
   InfraKernel();
public:
   //makes this an abstract class
   virtual ~InfraKernel() = 0;
   //Reads the internal status of the object
   DWORD status();
   //Gets the internal handle
   HANDLE getHandle() const;
   //Waits on the current infrakernel object
   DWORD wait( DWORD dwMilliSeconds );
   //checks if the current handle is valid
   bool hasValidHandle();
   //another way to get the internal handle
   operator HANDLE() const;
protected:
   HANDLE   _handle;
   DWORD    _dwStatus;
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraKernel.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:48   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:30:22   DT11159
// 
//
//

#endif
