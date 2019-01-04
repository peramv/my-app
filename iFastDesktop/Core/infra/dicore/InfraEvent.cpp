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

#ifndef INFRAEVENT_HPP
   #include "InfraEvent.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif

InfraEvent::InfraEvent( bool bManualReset, bool bInitialState, const char* name,
   LPSECURITY_ATTRIBUTES lpSecurityAttrib )
{
   _handle = ::CreateEvent( lpSecurityAttrib, bManualReset, bInitialState, name );
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

InfraEvent::InfraEvent( const char* name, bool bInheritHandle, DWORD dwDesiredAccess )
{
   _handle = ::OpenEvent( dwDesiredAccess, bInheritHandle, name );
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

InfraEvent::~InfraEvent()
{
}

void InfraEvent::set()
{
   if( !::SetEvent( _handle ) )
      throw InfraException();
}

void InfraEvent::reset()
{
   if( !::ResetEvent( _handle ) )
      throw InfraException();
}

void InfraEvent::pulse()
{
   if( !::PulseEvent( _handle ) )
      throw InfraException();
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraEvent.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:54   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:24   DT11159
// 
//
//
