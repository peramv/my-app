#include "stdafx.h"

#include "bfkernel.hpp"
#include "bfexception.hpp"

BFKernel::BFKernel()
{
   _handle = NULL;
}

BFKernel::~BFKernel()
{
   if( _handle == NULL )
   {
      ::CloseHandle( _handle );
      _handle = NULL;
   }
}

bool BFKernel::wait( DWORD timeout /* = INFINITE */ )
{
   DWORD result = ::WaitForSingleObject( _handle, timeout );

   if( result == WAIT_FAILED )
      throw BFException();

   if( result == WAIT_TIMEOUT )
      return(false);

   return(true);

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFKernel.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:41:16   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   May 28 2002 12:15:56   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   03 Oct 2001 15:09:56   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.0   Jun 28 2001 09:48:02   PURDYECH
// Initial revision.
// 
//    Rev 1.0   Jun 26 2001 12:01:00   PURDYECH
// Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:46   POPESCUS
 * Initial revision
 * 
 * 
 */