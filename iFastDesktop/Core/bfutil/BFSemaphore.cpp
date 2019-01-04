#include "stdafx.h"

#include "BFSemaphore.hpp"
#include "BFexception.hpp"

BFSemaphore::BFSemaphore( int nInitialCount, int nMaximumCount, const char* name )
{
   _handle = ::CreateSemaphore( NULL, nInitialCount, nMaximumCount, name );

   if( _handle == NULL )
      throw BFException();
}

BFSemaphore::BFSemaphore( const char* name )
{
   _handle = ::OpenSemaphore( SEMAPHORE_ALL_ACCESS, FALSE, name );

   if( _handle == NULL )
      throw BFException();
}

BFSemaphore::~BFSemaphore()
{
}

void BFSemaphore::release( long lReleaseCount, long *plPreviousCount )
{
   long lPreviousCount = 0;

   if( !::ReleaseSemaphore( _handle, lReleaseCount, &lPreviousCount ) )
      throw BFException();

   if( plPreviousCount )
   {
      *plPreviousCount = lPreviousCount;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/DSTCProjects/BusinessComponents/BFUtil/BFSemaphore.cpp-arc  $
// 
//    Rev 1.2   May 28 2002 12:15:56   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   03 Oct 2001 15:09:56   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.0   Jun 28 2001 09:48:04   PURDYECH
// Initial revision.
// 
//    Rev 1.0   Jun 26 2001 12:01:04   PURDYECH
// Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:46   POPESCUS
 * Initial revision
 * 
 * 
 */