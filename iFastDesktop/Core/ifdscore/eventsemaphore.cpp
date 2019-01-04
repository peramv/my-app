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
// ^FILE   : EventSemaphore.cpp
// ^AUTHOR : Ted Koresko
// ^DATE   : 06/20/97
//
// ----------------------------------------------------------
//
// ^CLASS    : EventSemaphore
//
// ^MEMBER VARIABLES :
//   ^^HEV/HANDLE _hsem - the handle to the semaphore
//   ^^EVENTSEM_ENUMS _eState - tells whether to create/open the semaphore in
//      the set or posted state
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef EVENTSEMAPHORE_HPP
   #include "eventsemaphore.hpp"
#endif
#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

EventSemaphore::EventSemaphore( unsigned long ulTimeout,
                                EVENTSEM_ENUMS eState )
HEADER_THROW2( ConditionException, exception ) :
Semaphore( ulTimeout ), _eState( eState )
{
   create();
}


EventSemaphore::EventSemaphore( EVENTSEM_ENUMS eState,
                                unsigned long ulTimeout )
HEADER_THROW2( ConditionException, exception ) :
Semaphore( ulTimeout ), _eState( eState )
{
   create();
}


EventSemaphore::EventSemaphore( const EventSemaphore& orig )
HEADER_THROW1( exception ) :
Semaphore(orig.getName(), orig.getTimeout(), orig.getHandle())
{
   _eState = orig._eState;
}


EventSemaphore::EventSemaphore( const I_CHAR * pszName, bool fCreate,
                                unsigned long ulTimeout,
                                EVENTSEM_ENUMS eState )
HEADER_THROW2( ConditionException, exception ) :
Semaphore( pszName, ulTimeout ),
_eState( eState )
{
   Initialize(fCreate);    // in base class
}


EventSemaphore::~EventSemaphore() HEADER_THROW1( exception )
{
   close();
}


void EventSemaphore::create() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = CreateEventSemaphore( GetName(),
                                               &_hsem,
                                               (INITIALLY_POSTED == _eState) );

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::create()" ),
                  DICORE_EVENTSEM_CREATE_FAIL,
                  I_( "Create Event Semaphore Error " ),
                  ulRc);
   }
}


void EventSemaphore::open() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = OpenEventSemaphore( GetName(),
                                             &_hsem,
                                             (INITIALLY_POSTED == _eState) );

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::open()" ),
                  DICORE_EVENTSEM_OPEN_FAIL,
                  I_( "Open Event Semaphore Error " ),
                  ulRc);
   }
}


void EventSemaphore::close() HEADER_THROW
{
   CloseEventSemaphore(_hsem);
}


void EventSemaphore::post() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = PostEventSemaphore(_hsem);

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::open()" ),
                  DICORE_EVENTSEM_OPEN_FAIL,
                  I_( "Open Event Semaphore Error " ),
                  ulRc);
   }
}


void EventSemaphore::wait() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulRc = WaitForEventSemaphore(_hsem, getTimeout());

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::wait()" ),
                  DICORE_EVENTSEM_WAIT_FAIL,
                  I_( "Wait for Event Semaphore Error " ),
                  ulRc);
   }
}


unsigned long EventSemaphore::query() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulPostCount = 0;
   unsigned long  ulRc = QueryEventSemaphore(_hsem, ulPostCount);

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::query()" ),
                  DICORE_EVENTSEM_SET_FAIL,
                  I_( "Query Event Semaphore Error " ),
                  ulRc);
   }

   return(ulRc);
}


void EventSemaphore::reset() HEADER_THROW2( ConditionException, exception )
{
   unsigned long  ulPostCount = 0;
   unsigned long  ulRc = ResetEventSemaphore(_hsem, ulPostCount);

   if( ulRc )
   {
      ThrowError( I_( "EventSemaphore::reset()" ),
                  DICORE_EVENTSEM_RESET_FAIL,
                  I_( "Reset Event Semaphore Error " ),
                  ulRc);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/eventsemaphore.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:00   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:08   SMITHDAV
// Initial revision.
// 
//    Rev 1.4   Mar 24 2000 12:25:24   DMUM
// Since Semaphores are being used more as static members,
// they should not have any tracing.
//
//    Rev 1.3   26 Feb 1999 15:05:54   DT14177
// Integrate DIBASE and DICONFIG into DICORE
//
//    Rev 1.2   24 Feb 1999 10:44:12   DT14177
// sync up with tracer
//
//    Rev 1.1   Jan 28 1999 14:02:54   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:12   DMUM
//
//
//    Rev 1.11   Nov 09 1997 15:35:06   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.10   Jul 23 1997 11:48:14   DTWK
// Add tracing
//
//    Rev 1.9   Jul 07 1997 15:15:58   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.8   Jun 13 1997 13:20:10   DTWK
//
//
//

