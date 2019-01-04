#ifndef INFRAEVENT_HPP
#define INFRAEVENT_HPP

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

class DICORE_LINKAGE InfraEvent : public InfraKernel
{
public:
   //creates a InfraEvent object
   //the status must be checked after using this constructor
   //by default this is a auto reset event, initially non-signaled
   InfraEvent( bool bManualReset = FALSE, bool bInitialState = FALSE, const char* name = NULL,
            LPSECURITY_ATTRIBUTES lpSecurityAttrib = NULL );
   //opens an existing InfraEvent
   //the status must be checked after using this constructor
   InfraEvent( const char* name, bool bInheritHandle = FALSE, DWORD dwDesiredAccess = EVENT_ALL_ACCESS );
   virtual ~InfraEvent();
   //sets the state of this event object to be signaled
   //any number of waiting threads, or threads that subsequently begin wait operations for
   //this event object by calling one of the wait functions,
   //can be released while the object's state is signaled
   void set();
   //sets the state of this event object to nonsignaled
   //this nonsignaled state blocks the execution of any threads that
   //have specified the event object in a call to one of the wait functions
   void reset();
   //provides a single operation that sets (to signaled) the state of this
   //event object and then resets it (to nonsignaled) after releasing
   //the appropriate number of waiting threads
   void pulse();
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraEvent.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:46   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:22   DT11159
// 
//
//

#endif
