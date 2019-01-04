#ifndef INFRACRITSEC_HPP
#define INFRACRITSEC_HPP

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

//Forward declaration
#ifndef INFRAMUTEX_HPP
   class InfraMutex;
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

class DICORE_LINKAGE InfraCritSec
{
public:
   //creates a InfraCritSec object
   //by default, when created, the objects enter the critical section
   InfraCritSec( bool autoLock = true );
   //CS using a mutex, by default lock immediate
   InfraCritSec( InfraMutex* mutex, bool autoLock = true );
   virtual ~InfraCritSec();
   //enters the critical section
   void enter();
   //leaves the critical section
   void leave();
private:
   bool _autoLock;
   InfraMutex* _mutex;
   CRITICAL_SECTION _lpCriticalSection;
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraCritSec.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:42   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:18   DT11159
// 
//
//

#endif
