#ifndef INFRAWAITABLESET_HPP
#define INFRAWAITABLESET_HPP

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

//this is a helper class used to
//wait on multiple infrakernel objects
//it wraps the ::WaitForMultipleObjects method
//the maximum number of objects that a thread can wait on
//is defined by the constant: MAXIMUM_WAIT_OBJECTS
//  class BPSRVMT_LINKAGE InfraWaitableSet
class DICORE_LINKAGE InfraWaitableSet
{
public:
   InfraWaitableSet();
   ~InfraWaitableSet();
   bool addHandle( HANDLE handle );
   const int getCount();
   //the function returns when one of the following occurs:
   // - either any one or all of the specified objects are in the signaled state.
   // - the time-out interval elapses
   // if waitForAll is :
   //    - true, the function returns when the state of all objects in the _handles array is signaled
   //    - false, the return value indicates the object whose state caused the function to return
   DWORD wait( BOOL waitForAll, DWORD dwMilliSeconds );
   //this method will shrink the set of the handles we wait on, by substituting the
   //handle that signaled with the last elemene in the array
   //the method returns false if there are no more handles to wait on
   //usually this method should be used in conjunction with the wait method, setting
   //the waitForAll param to false
   bool shrinkSet( DWORD ndxHandleThatSignaled );
private:
   HANDLE  _handles[ MAXIMUM_WAIT_OBJECTS ];
   int     _handlesCount;
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraWaitableSet.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:56   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:46   DT11159
// 
//
//

#endif
