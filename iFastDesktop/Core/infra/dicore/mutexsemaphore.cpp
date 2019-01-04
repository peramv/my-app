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
// ^FILE   : MutexSemaphore.cpp
// ^AUTHOR : Ted Koresko
// ^DATE   : 06/20/97
//
// ----------------------------------------------------------
//
// ^CLASS    : MutexSemaphore
//
// ^MEMBER VARIABLES :
//   ^^HEV/HANDLE _hsem - the handle to the semaphore
//   ^^MUTEXSEM_ENUMS _eState - tells whether to create/open the semaphore in
//      the set or posted state
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INCLUDED_STRSTREAM
#define INCLUDED_STRSTREAM
   #include <strstream>
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif
#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

MutexSemaphore::MutexSemaphore( unsigned long ulTimeout,
                                MUTEXSEM_ENUMS eState )
   HEADER_THROW2( ConditionException, exception ) :
   Semaphore( ulTimeout ), _eState( eState )
{
   create();
}


MutexSemaphore::MutexSemaphore( MUTEXSEM_ENUMS eState,
                                unsigned long ulTimeout )
   HEADER_THROW2( ConditionException, exception ) :
   Semaphore( ulTimeout ), _eState( eState )
{
   create();
}


MutexSemaphore::MutexSemaphore( const MutexSemaphore& orig )
   HEADER_THROW1( exception ) :
   Semaphore(orig.getName(), orig.getTimeout(), orig.getHandle())
{
   _eState = orig._eState;
}


MutexSemaphore::MutexSemaphore( const I_CHAR * pszName, bool fCreate,
                                unsigned long ulTimeout,
                                MUTEXSEM_ENUMS eState )
   HEADER_THROW2( ConditionException, exception ) :
   Semaphore( pszName, ulTimeout ), _eState( eState )
{
   Initialize(fCreate);    // in base class
}


MutexSemaphore::~MutexSemaphore() HEADER_THROW1( exception )
{
   close();
}


void MutexSemaphore::create() HEADER_THROW2( ConditionException, exception )
{
   unsigned long ulRc = CreateMutexSemaphore( GetName(),
                                              &_hsem,
                                              (INITIALLY_OWNED == _eState) );

   if (ulRc)
   {
      ThrowError( I_( "MutexSemaphore::create()" ),
                 DICORE_MUTEXSEM_CREATE_FAIL,
                 I_( "Create Mutex Semaphore Error " ),
                 ulRc);
   }
}


void MutexSemaphore::open() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = OpenMutexSemaphore(GetName(), &_hsem);

   if (ulRc)
   {
      ThrowError( I_( "MutexSemaphore::open()" ),
                 DICORE_MUTEXSEM_OPEN_FAIL,
                 I_( "Open Mutex Semaphore Error " ),
                 ulRc);
   }
}


void MutexSemaphore::close() HEADER_THROW
{
   CloseMutexSemaphore(_hsem);
}


void MutexSemaphore::post() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = PostMutexSemaphore(_hsem);

   if (ulRc)
   {
      ThrowError( I_( "MutexSemaphore::post()" ),
                 DICORE_MUTEXSEM_RELEASE_FAIL,
                 I_( "Release Mutex Semaphore Error " ),
                 ulRc);
   }
}


void MutexSemaphore::wait() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = WaitForMutexSemaphore(_hsem, getTimeout());

   if (ulRc)
   {
      ThrowError( I_( "MutexSemaphore::wait()" ),
                 DICORE_MUTEXSEM_WAIT_FAIL,
                 I_( "Wait for Mutex Semaphore Error " ),
                 ulRc);
   }
}


unsigned long MutexSemaphore::query()
   HEADER_THROW2( ConditionException, exception )
{
   PID      pid;
   TID      tid;
   return query(&pid, &tid);
}


unsigned long MutexSemaphore::query( PID *pPID, TID *pTID )
   HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulPostCount = 0;
   unsigned long  ulRc = QueryMutexSemaphore(_hsem, pPID, pTID, ulPostCount );

    if (ulRc != 0)
      ThrowError( I_( "MutexSemaphore::query()" ),
                  DICORE_MUTEXSEM_WAIT_FAIL,
                  I_( "Query Mutex Semaphore Error " ),
                  ulRc);
   return (ulPostCount);
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
// $Log:   Y:/VCS/iFastAWD/dicore/mutexsemaphore.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:20   kovacsro
// Initial revision.
// 
//    Rev 1.3   26 Feb 1999 15:06:08   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.2   24 Feb 1999 10:44:26   DT14177
// sync up with tracer
// 
//    Rev 1.1   Jan 28 1999 14:03:10   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:28   DMUM
//
//
//    Rev 1.11   Nov 09 1997 15:35:10   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.10   Jul 23 1997 11:48:26   DTWK
// Add tracing
//
//    Rev 1.9   Jul 07 1997 15:16:02   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.8   Jun 13 1997 13:20:18   DTWK
//
//
//


