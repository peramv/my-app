
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef SWMRRESOURCELOCK_HPP
   #include "swmrresourcelock.hpp"
#endif


SWMRResourceLock::SWMRResourceLock() :
m_iNumWritingLocks( 0 ), m_enumStatus( SWMRResourceLock::SWMR_NONE )
{
}


void SWMRResourceLock::acquireForRead()
{
   bool fGo = false;

   DWORD dwCurrentThread = DSTGetCurrentThreadId();

   while( !fGo )
   {
      m_mutexStatus.wait();

      if( SWMRResourceLock::SWMR_WRITING == m_enumStatus )
      {
         // The thread already has it locked for writing, and it's just
         // locking it for reading too
         if( m_dwCurrentWritingThread == dwCurrentThread )
         {
            fGo = true;
            _incrementThreadReadCount( dwCurrentThread );
            m_mutexStatus.post();
         }
         else
         {
            m_mutexStatus.post();
            m_eventStatusChanged.wait();
         }
      }
      else if( SWMRResourceLock::SWMR_NONE == m_enumStatus )
      {
         m_enumStatus = SWMRResourceLock::SWMR_READING;
         m_eventStatusChanged.post();
         m_eventStatusChanged.reset();
         m_mutexStatus.post();
      }
      else
      {
         fGo = true;
         _incrementThreadReadCount( dwCurrentThread );
         m_mutexStatus.post();
      }
   }
}


void SWMRResourceLock::acquireForWrite()
{
   bool fGo = false;

   DWORD dwCurrentThread = DSTGetCurrentThreadId();

   while( !fGo )
   {
      m_mutexStatus.wait();

      if( SWMRResourceLock::SWMR_READING == m_enumStatus )
      {
         if( _onlyThreadReading( dwCurrentThread ) )
         {
            m_iNumWritingLocks += 1;
            fGo = true;
            m_enumStatus = SWMRResourceLock::SWMR_WRITING;
            m_dwCurrentWritingThread = DSTGetCurrentThreadId();
            m_mutexStatus.post();
         }
         else
         {
            m_mutexStatus.post();
            m_eventStatusChanged.wait();
         }
      }
      else if( SWMRResourceLock::SWMR_WRITING == m_enumStatus )
      {
         if( m_dwCurrentWritingThread == dwCurrentThread )
         {
            m_iNumWritingLocks += 1;
            fGo = true;
            m_mutexStatus.post();
         }
         else
         {
            m_mutexStatus.post();
            m_eventStatusChanged.wait();
         }
      }
      else // if ( SWMRResourceLock::SWMR_NONE == m_enumStatus )
      {
         fGo = true;
         m_iNumWritingLocks += 1;
         m_enumStatus = SWMRResourceLock::SWMR_WRITING;
         m_dwCurrentWritingThread = DSTGetCurrentThreadId();
         m_mutexStatus.post();
      }
   }
}


void SWMRResourceLock::releaseFromRead()
{
   m_mutexStatus.wait();

   _decrementThreadReadCount( DSTGetCurrentThreadId() );

   if( 0 == m_mapReadingThreads.size() )
   {
      if( m_enumStatus == SWMRResourceLock::SWMR_READING )
      {
         m_enumStatus = SWMRResourceLock::SWMR_NONE;
         m_eventStatusChanged.post();
         m_eventStatusChanged.reset();
      }
   }

   m_mutexStatus.post();
}


void SWMRResourceLock::releaseFromWrite()
{
   m_mutexStatus.wait();

   m_iNumWritingLocks -= 1;

   if( 0 == m_iNumWritingLocks )
   {
      if( 0 == m_mapReadingThreads.size() )
      {
         // There's no recursive calls to lock the resource for reads by this
         // thread.  We can exit normally.
         m_enumStatus = SWMRResourceLock::SWMR_NONE;
         m_eventStatusChanged.post();
         m_eventStatusChanged.reset();
      }
      else
      {
         // We have a few recursive calls on the thread to lock the resource for
         // reads. Transfer the control of the resource to read mode.
         m_enumStatus = SWMRResourceLock::SWMR_READING;

         // Also, wake up any additional threads that are waiting to read
         m_eventStatusChanged.post();
         m_eventStatusChanged.reset();
      }
   }

   m_mutexStatus.post();
}


void SWMRResourceLock::_incrementThreadReadCount( DWORD dwCurrentThread )
{
   READER_COUNT_MAP::iterator iter = 
   m_mapReadingThreads.find( dwCurrentThread );

   if( m_mapReadingThreads.end() == iter )
   {
      m_mapReadingThreads[ dwCurrentThread ] = 1;
   }
   else
   {
      m_mapReadingThreads[ dwCurrentThread ] =
      m_mapReadingThreads[ dwCurrentThread ] + 1;
   }
}


void SWMRResourceLock::_decrementThreadReadCount( DWORD dwCurrentThread )
{
   READER_COUNT_MAP::iterator iter = 
   m_mapReadingThreads.find( dwCurrentThread );

   if( m_mapReadingThreads.end() != iter )
   {
      DWORD dwCount = m_mapReadingThreads[ dwCurrentThread ] - 1;
      if( 0 == dwCount )
      {
         m_mapReadingThreads.erase( iter );
      }
      else
      {
         m_mapReadingThreads[ dwCurrentThread ] = dwCount;
      }
   }
}


bool SWMRResourceLock::_onlyThreadReading( DWORD dwCurrentThread )
{
   if( 1 != m_mapReadingThreads.size() )
   {
      return(false);
   }

   if( m_mapReadingThreads.end() ==
       m_mapReadingThreads.find( dwCurrentThread ) )
   {
      return(false);
   }

   return(true);
}


/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/swmrresourcelock.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:28   SMITHDAV
// Initial revision.
//
//   Rev 1.2   Apr 10 2000 11:49:54   dtwk
//Add support for recursive calls
//
//   Rev 1.1   Apr 04 2000 07:11:02   dtwk
//Change enum values due to conflict with DIAWD23
//
//   Rev 1.0   Apr 03 2000 15:59:50   dtwk
// 
// 
*/


