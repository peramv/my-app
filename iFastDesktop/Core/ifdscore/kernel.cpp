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

#ifndef KERNEL_HPP
   #include "kernel.hpp"
#endif

Kernel::Kernel()
{
   _handle = NULL;
   _dwStatus = ERROR_INVALID_HANDLE;
}

Kernel::~Kernel()
{
   if( hasValidHandle() )
   {
      ::CloseHandle( _handle );
      _handle = NULL;
   }
}

DWORD Kernel::status()
{
   return(_dwStatus);
}

HANDLE Kernel::getHandle() const
{
   return(_handle);
}

DWORD Kernel::wait( DWORD dwMilliseconds )
{
   return(::WaitForSingleObject( _handle, dwMilliseconds ));
}

bool Kernel::hasValidHandle()
{
   return(_handle != NULL && _handle != INVALID_HANDLE_VALUE);
}

Kernel::operator HANDLE() const
{
   return(getHandle());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/kernel.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:08   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:20   SMITHDAV
// Initial revision.
//
//   Rev 1.1   May 20 2001 09:47:02   DT11159
//Removed StdAfx.h and used platform.h instead.
//