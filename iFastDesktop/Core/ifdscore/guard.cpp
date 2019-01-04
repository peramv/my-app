#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef Lock_HPP
   #include "Lock.hpp"
#endif

Guard::Guard( Lock *lock ) : m_lock( lock )
{
   if( m_lock )
   {
      m_lock->lock();
   }
}


Guard::~Guard()
{
   if( m_lock )
   {
      m_lock->unlock();
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/guard.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:02   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:16   SMITHDAV
// Initial revision.
//
//   Rev 1.0   May 18 2001 12:44:58   DT21858
//Initial Check In
// 
//

