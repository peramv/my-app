#include "stdafx.h"

#include "BFMutex.hpp"
#include "BFexception.hpp"

BFMutex::BFMutex( bool bInitialOwner /*=false*/, const char* name /*=NULL*/ )
{
   _handle = ::CreateMutex( NULL, bInitialOwner?TRUE:FALSE, name );

   if( _handle == NULL )
      throw BFException();
}

BFMutex::BFMutex( const char* name )
{
   _handle = ::OpenMutex( MUTEX_ALL_ACCESS, FALSE, name );

   if( _handle == NULL )
      throw BFException();
}

BFMutex::~BFMutex()
{
}

void BFMutex::release()
{
   if( !::ReleaseMutex( _handle ) )
      throw BFException();

}

void BFMutex::leave()
{
   release();
}


void BFMutex::enter()
{
   wait();
}

bool BFMutex::tryEnter()
{
   return(wait( 0 ));
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFMutex.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:41:18   PURDYECH
// New PVCS Database
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
//    Rev 1.0   Jun 26 2001 12:01:02   PURDYECH
// Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:46   POPESCUS
 * Initial revision
 * 
 * 
 */