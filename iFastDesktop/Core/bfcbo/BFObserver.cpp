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
// ^FILE   : BFObserver.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObserver
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFObserver.cpp-arc  $", "$Revision:   1.3  $" )

#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif

#ifndef BFOBSERVER_HPP
   #include "BFObserver.hpp"
#endif

#ifndef BFNOTIFICATION_HPP
   #include "BFNotification.hpp"
#endif

//******************************************************************************
BFObserver::BFObserver()
{
}

//******************************************************************************
BFObserver::~BFObserver()
{
   deRegisterObserver();
}

//******************************************************************************
void BFObserver::deRegisterObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId )
{
   BFNotification * bfNotif = BFNotification::getInstance();

   BFNotifKey key( lObservableId, eEventCateg, eEventId);
   OBS_SET::iterator iter = _obsSet.find( key );
   while( iter != _obsSet.end() && (*iter).m_lObservableId == lObservableId && 
          (*iter).m_eEventCateg == eEventCateg &&  (eEventId == E_EVENT_ALL || (*iter).m_eEventId == eEventId ) )
   {
      bfNotif->deregisterObserver( (*iter).m_lObservableId, (*iter).m_eEventCateg, (*iter).m_eEventId, this );
      iter = _obsSet.erase( iter );
   }
};
//******************************************************************************
void BFObserver::deRegisterObserver( )
{
   BFNotification * bfNotif = BFNotification::getInstance();
   OBS_SET::iterator iter = _obsSet.begin();
   while( iter != _obsSet.end() )
   {
      bfNotif->deregisterObserver( (*iter).m_lObservableId, (*iter).m_eEventCateg, (*iter).m_eEventId, this );
      iter = _obsSet.erase( iter );
   }
};
//******************************************************************************
void BFObserver::registerObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId )
{
   BFNotification::getInstance()->registerObserver( lObservableId, eEventCateg, eEventId, this );
   BFNotifKey key( lObservableId, eEventCateg, eEventId);

   OBS_SET::iterator iter = _obsSet.find( key );
   if( iter == _obsSet.end() )
      _obsSet.insert( key );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFObserver.cpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:40:08   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   03 Jul 2001 16:22:20   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.1   03 May 2001 14:02:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.0   Feb 15 2000 10:57:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Jan 19 2000 10:12:02   BUZILA
// refresh stuf
// 
//    Rev 1.1   Dec 21 1999 12:39:12   BUZILA
// changes
 * 
 */



