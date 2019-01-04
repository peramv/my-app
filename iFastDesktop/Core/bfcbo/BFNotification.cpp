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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFNotification.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : January 2000
//
// ----------------------------------------------------------
//
// ^CLASS : BFNotification
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/BFNotification.cpp-arc  $", "$Revision:   1.8  $" )

#include <srcprag.h>
#include <windows.h>
#include "bfnotification.hpp"
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfguard.hpp>
#include <vector>

namespace
{
   // The use of this lock in the code has not been optimized - just put in for
   //  safety.
   BFCritSec g_cs;
}

//CP20040225BFNotification* BFNotification::_pInstance = NULL;

//******************************************************************************
BFNotification::BFNotification()
{

}

//******************************************************************************
BFNotification::~BFNotification()
{

}

//******************************************************************************
BFNotification * BFNotification::getInstance( void )
{
   static BFNotification instance;
   return(&instance);
}

//******************************************************************************
void BFNotification::killInstance()
{
}

//******************************************************************************
void BFNotification::registerObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, BFObserver *pObserver )
{
   BFNotifKey  key( lObservableId, eEventCateg, eEventId);

   bool bFound = false;
   std::pair< NOTIFICATION_MMAP::iterator, NOTIFICATION_MMAP::iterator> iterPair;

   BFGuard cs( g_cs );  
   iterPair = _notifMap.equal_range( key );

   NOTIFICATION_MMAP::iterator it = iterPair.first;

   while( it != iterPair.second )
   {
      if( (*it).second == pObserver )
      {
         bFound = true;
         break;
      }
      else
      {
         ++it;
      }
   }
   if( !bFound )
   {
      _notifMap.insert( NOTIFICATION_MMAP::value_type( key, pObserver));
   }
}

//*******************************************************************************
void BFNotification::deregisterObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, BFObserver *pObserver )
{
   BFGuard cs( g_cs );
   NOTIFICATION_MMAP::iterator it      = _notifMap.lower_bound( BFNotifKey( lObservableId, eEventCateg,     E_EVENT_ALL ) );
   NOTIFICATION_MMAP::iterator itEnd   = _notifMap.upper_bound( BFNotifKey( lObservableId, (E_EVENT_GROUP )(eEventCateg + 1), E_EVENT_ALL ) );

   while( it != itEnd )
   {
      if( ( (*it).first.m_eEventId == eEventId || eEventId == E_EVENT_ALL ) && (*it ).second == pObserver )
         it = _notifMap.erase( it );
      else
         ++it;
   }
}

//******************************************************************************
void BFNotification::notifyObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString & hint )
{
   BFNotifKey key( lObservableId, eEventCateg, E_EVENT_ALL );

   BFGuard cs( g_cs );

   std::set< BFObserver* > setObs;

   while( true )
   {
      NOTIFICATION_MMAP::iterator it = _notifMap.lower_bound( key );;
      NOTIFICATION_MMAP::iterator itEnd = _notifMap.end();

      for( ; itEnd != it; ++it ) 
      {
         if( (*it ).first.m_lObservableId == lObservableId && (*it ).first.m_eEventCateg  == eEventCateg ) 
         {
            BFObserver* pObserver = (*it).second;
            if( setObs.end() != setObs.find( pObserver ) ) {
               // we've notified this observer already ... go to the next one
               continue;
            }
            const BFNotifKey& notifyKey = (*it).first;
            if( (!eEventId || !notifyKey.m_eEventId || notifyKey.m_eEventId == eEventId ) && pObserver )
            {
               pObserver->onNotify( eEventCateg, eEventId, hint );
               setObs.insert( pObserver );
               break;
            }
         }
      }

      if( itEnd == it ) {
         // we've actually gone all the way through the map and not found anything
         break;
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFNotification.cpp-arc  $
//
//   Rev 1.8   Mar 10 2004 12:56:56   PURDYECH
//PET910 - Improved guarding of code in BFNotification map.
//
//   Rev 1.7   Feb 26 2004 13:26:14   PURDYECH
//PET910 - Restructured to address some stability issues.
 * 
 *    Rev 1.6   Oct 09 2002 17:40:04   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   22 May 2002 17:54:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   03 Jul 2001 16:22:18   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.3   03 May 2001 14:02:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Apr 20 2000 15:38:36   DT24433
 * synchronized use of singleton map
 * 
 *    Rev 1.1   Apr 19 2000 10:20:00   BUZILA
 * fix
 * 
 *    Rev 1.0   Feb 15 2000 10:57:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Jan 19 2000 17:32:14   BUZILA
// fix
// 
//    Rev 1.0   Jan 19 2000 10:12:42   BUZILA
// Initial revision.
//
// 
*/

