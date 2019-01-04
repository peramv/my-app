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

#ifndef INFRAMUTEX_HPP
   #include "InfraMutex.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif

InfraMutex::InfraMutex( bool bInitialOwner /*=false*/, const char* name /*=NULL*/,
   LPSECURITY_ATTRIBUTES lpSecurityAttrib /*=NULL*/ )
{
   _handle = ::CreateMutex( lpSecurityAttrib, bInitialOwner, name );
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

InfraMutex::InfraMutex( const char* name, bool bInheritHandle /*=false*/,
                  DWORD dwDesiredAccess /*=MUTEX_ALL_ACCESS*/ )
{
   _handle = ::OpenMutex( dwDesiredAccess, bInheritHandle, name );
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

InfraMutex::~InfraMutex()
{
}

void InfraMutex::release()
{
   if( !::ReleaseMutex( _handle ) )
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraMutex.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:00   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:30   DT11159
// 
//
//
