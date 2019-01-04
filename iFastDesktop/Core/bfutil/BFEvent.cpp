#include "stdafx.h"

#include "BFEvent.hpp"
#include "bfexception.hpp"

BFEvent::BFEvent( bool bManualReset, bool bInitialState, const char* name )
{
   _handle = ::CreateEvent( NULL, bManualReset?TRUE:FALSE, bInitialState?TRUE:FALSE, name );
   if( _handle == NULL )
      throw BFException();
}

BFEvent::BFEvent( const char* name )
{
   _handle = ::OpenEvent( EVENT_ALL_ACCESS, FALSE, name );
   if( _handle == NULL )
      throw BFException();
}

BFEvent::~BFEvent()
{
}

void BFEvent::set()
{
   if( !::SetEvent( _handle ) )
      throw BFException();
}

void BFEvent::reset()
{
   if( !::ResetEvent( _handle ) )
      throw BFException();
}

void BFEvent::pulse()
{
   if( !::PulseEvent( _handle ) )
      throw BFException();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/DSTCProjects/BusinessComponents/BFUtil/BFEvent.cpp-arc  $
// 
//    Rev 1.2   May 28 2002 12:15:52   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   03 Oct 2001 15:09:54   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.0   Jun 28 2001 09:48:00   PURDYECH
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