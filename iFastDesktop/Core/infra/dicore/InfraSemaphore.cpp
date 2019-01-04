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

#define DICORE_DLL

#ifndef INFRASEMAPHORE_HPP
   #include "InfraSemaphore.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif

InfraSemaphore::InfraSemaphore( int nInitialCount, int nMaximumCount, const char* name,
   LPSECURITY_ATTRIBUTES lpSecurityAttrib )
{
   _handle = ::CreateSemaphore( lpSecurityAttrib, nInitialCount, nMaximumCount, name );
   if( hasValidHandle() )
   {
      if( name )
      {
         _dwStatus = GetLastError();
      }
      else
      {
         _dwStatus = NO_ERROR;
      }
   }
   else
   {
      _dwStatus = GetLastError();
      throw InfraException();
   }
}

InfraSemaphore::InfraSemaphore( const char* name, bool bInheritHandle, DWORD dwDesiredAccess )
{
   _handle = ::OpenSemaphore( dwDesiredAccess, bInheritHandle, name );
   if( hasValidHandle() )
   {
      _dwStatus = NO_ERROR;
   }
   else
   {
      _dwStatus = GetLastError();
      throw InfraException();
   }
}

InfraSemaphore::~InfraSemaphore()
{
}

void InfraSemaphore::release( long lReleaseCount, long *plPreviousCount )
{
   long lPreviousCount = 0;

   if( !::ReleaseSemaphore( _handle, lReleaseCount, &lPreviousCount ) )
      throw InfraException();
   if( plPreviousCount )
   {
      *plPreviousCount = lPreviousCount;
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraSemaphore.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:02   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:34   DT11159
// 
//
//
