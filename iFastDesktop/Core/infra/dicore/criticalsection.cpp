#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif


CriticalSection::CriticalSection() :
   m_pmsem( 0 ), m_pswmr( 0 ), m_swmrMode( CriticalSection::SWMR_READ )
{
}


CriticalSection::CriticalSection( MutexSemaphore &mutex ) :
   m_pmsem( &mutex ), m_pswmr( 0 ), m_swmrMode( CriticalSection::SWMR_READ )
{
   if ( m_pmsem )
   {
      m_pmsem->wait();
   }
}


CriticalSection::CriticalSection( MutexSemaphore *pMutex ) :
   m_pmsem( pMutex ), m_pswmr( 0 ), m_swmrMode( CriticalSection::SWMR_READ )
{
   if ( m_pmsem )
   {
      m_pmsem->wait();
   }
}


CriticalSection::CriticalSection( SWMRResourceLock &swmr, 
                                  SWMR_MODE swmrMode ) :
   m_pmsem( 0 ), m_pswmr( &swmr ), m_swmrMode( swmrMode )
{
   if ( m_pswmr )
   {
      if ( SWMR_READ == m_swmrMode )
      {
         m_pswmr->acquireForRead();
      }
      else
      {
         m_pswmr->acquireForWrite();
      }
   }
}


CriticalSection::~CriticalSection()
{
   if ( m_pmsem )
   {
      m_pmsem->post();
   }
   else if ( m_pswmr )
   {
      if ( SWMR_READ == m_swmrMode )
      {
         m_pswmr->releaseFromRead();
      }
      else
      {
         m_pswmr->releaseFromWrite();
      }
   }
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
// $Log:   Y:/VCS/iFastAWD/dicore/criticalsection.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:30   kovacsro
// Initial revision.
// 
//    Rev 1.2   Jun 05 2000 07:54:34   dtwk
// Add support for "delayed" waiting
// 
//    Rev 1.1   Apr 03 2000 15:57:38   dtwk
// Add in SWMRResourceLock support
// 
//    Rev 1.0   Jun 28 1999 11:19:26   DTWK
//  
//
//

