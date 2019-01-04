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
   if ( m_lock )
   {
      m_lock->lock();
   }
}


Guard::~Guard()
{
   if ( m_lock )
   {
      m_lock->unlock();
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
// $Log:   Y:/VCS/iFastAWD/dicore/guard.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:48   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 12:44:58   DT21858
//Initial Check In
// 
//

