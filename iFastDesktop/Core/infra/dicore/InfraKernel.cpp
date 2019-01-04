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

#ifndef INFRAKERNEL_HPP
   #include "infrakernel.hpp"
#endif

InfraKernel::InfraKernel()
{
   _handle = NULL;
   _dwStatus = ERROR_INVALID_HANDLE;
}

InfraKernel::~InfraKernel()
{
   if( hasValidHandle() )
   {
      ::CloseHandle( _handle );
      _handle = NULL;
   }
}

DWORD InfraKernel::status()
{
   return _dwStatus;
}

HANDLE InfraKernel::getHandle() const
{
   return _handle;
}

DWORD InfraKernel::wait( DWORD dwMilliseconds )
{
   return ::WaitForSingleObject( _handle, dwMilliseconds );
}

bool InfraKernel::hasValidHandle()
{
   return _handle != NULL && _handle != INVALID_HANDLE_VALUE;
}

InfraKernel::operator HANDLE() const
{
   return getHandle();
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraKernel.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:58   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:20:14   DT11159
// 
//
//
