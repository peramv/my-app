#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif


CriticalSectionLock::CriticalSectionLock()
{
   ::InitializeCriticalSection( &m_lock );
}


CriticalSectionLock::~CriticalSectionLock()
{
   ::DeleteCriticalSection( &m_lock );
}


void CriticalSectionLock::lock()
{
   ::EnterCriticalSection( &m_lock );
}


void CriticalSectionLock::unlock()
{
   ::LeaveCriticalSection( &m_lock );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/DSTCProjects/3rdParty/infra/dicore/criticalsectionlock.cpp-arc  $
// 
//    Rev 1.0   Jul 05 2002 10:14:02   SMITHDAV
// Initial revision.
//
//   Rev 1.0   May 18 2001 12:44:54   DT21858
//Initial Check In
// 
//

