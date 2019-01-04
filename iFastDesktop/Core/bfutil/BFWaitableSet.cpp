#include "stdafx.h"

#include "BFWaitableSet.hpp"
#include "BFKernel.hpp"
#include "BFException.hpp"

BFWaitableSet::BFWaitableSet( BFKernel* waitObjects[], int objectCount ) :
_objectCount( objectCount ),
_waitObjects( new BFKernel*[objectCount] ),
_waitObjectsHandles( new HANDLE[objectCount] )
{
   for( int i=0; i<_objectCount; i++ )
      _waitObjects[i] = waitObjects[i];
}

BFWaitableSet::~BFWaitableSet()
{
   delete[] _waitObjectsHandles;
   delete[] _waitObjects;
}

bool BFWaitableSet::wait( BFKernel *&waitObjectResult, DWORD timeout /*= INFINITE*/ )
{
   // reinit handles
   for( int i=0; i<_objectCount; i++ )
      _waitObjectsHandles[i] = _waitObjects[i]->_handle;

   DWORD result = ::WaitForMultipleObjects( _objectCount, _waitObjectsHandles, FALSE, timeout );

   if( result == WAIT_FAILED )
      throw BFException();

   if( result == WAIT_TIMEOUT )
      return(false);

   DWORD wo0 = WAIT_OBJECT_0;
   if( result >= WAIT_OBJECT_0 && result < (WAIT_OBJECT_0 + _objectCount) )
      waitObjectResult = _waitObjects[ result - WAIT_OBJECT_0 ];
   else
      waitObjectResult = _waitObjects[ result - WAIT_ABANDONED_0 ];

   return(true);
}

bool BFWaitableSet::waitAll( DWORD timeout /*= INFINITE*/ )
{
   // reinit handles
   for( int i=0; i<_objectCount; i++ )
      _waitObjectsHandles[i] = _waitObjects[i]->_handle;

   DWORD result = ::WaitForMultipleObjects( _objectCount, _waitObjectsHandles, TRUE, timeout );

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
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFWaitableSet.cpp-arc  $
// 
//    Rev 1.4   Oct 09 2002 17:41:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   May 28 2002 12:15:58   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.2   22 May 2002 17:56:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   03 Oct 2001 15:09:58   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.0   Jun 28 2001 09:48:06   PURDYECH
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