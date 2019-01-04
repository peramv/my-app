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

/**@pkg DICORE */

#define DICORE_DLL

#ifndef INFRACRITSEC_HPP
   #include "InfraCritSec.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "InfraException.hpp"
#endif
#ifndef INFRAMUTEX_HPP
   #include "InfraMutex.hpp"
#endif

InfraCritSec::InfraCritSec( bool autoLock /*=true*/ ) :
   _autoLock( autoLock ), _mutex( NULL )
{
   ::InitializeCriticalSection( &_lpCriticalSection );
   if( autoLock )
   {
      ::EnterCriticalSection( &_lpCriticalSection );
   }
}

InfraCritSec::InfraCritSec( InfraMutex* mutex, bool autoLock /*=true*/ ) :
   _autoLock( autoLock )
{
   _mutex = mutex;
   if( _autoLock )
   {
      DWORD dwMutexWait = _mutex->wait( INFINITE );

      if( dwMutexWait == WAIT_TIMEOUT || dwMutexWait == WAIT_FAILED )
         throw InfraException();
   }
}

InfraCritSec::~InfraCritSec()
{
   if( _mutex == NULL && _autoLock )
   {
      ::LeaveCriticalSection( &_lpCriticalSection );
   }
   if( _mutex == NULL )
   {
      ::DeleteCriticalSection( &_lpCriticalSection );
   }
   if( _mutex != NULL && _autoLock )
   {
      _mutex->release();
   }
}

void InfraCritSec::enter()
{
   if( _mutex == NULL  && !_autoLock )
   {
      ::EnterCriticalSection( &_lpCriticalSection );
   }
   else if( _mutex != NULL && !_autoLock )
   {
      DWORD dwMutexWait = _mutex->wait( INFINITE );

      if( dwMutexWait == WAIT_TIMEOUT || dwMutexWait == WAIT_FAILED )
         throw InfraException();
   }
}

void InfraCritSec::leave()
{
   if( _mutex == NULL  && !_autoLock )
   {
      ::LeaveCriticalSection( &_lpCriticalSection );
   }
   else if( _mutex != NULL && !_autoLock )
   {
      _mutex->release();
   }
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraCritSec.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:52   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:20   DT11159
// 
//
//
