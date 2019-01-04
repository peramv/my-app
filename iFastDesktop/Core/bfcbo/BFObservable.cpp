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
// ^FILE   : BFObservable.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObservable
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFObservable.cpp-arc  $", "$Revision:   1.5  $" )

#include <srcprag.h>
#include <windows.h>
#include "bfobservable.hpp"
#include "bfobserver.hpp"
#include "bfnotification.hpp"
#include <bfutil\bfguard.hpp>
#include <bfutil\bfcritsec.hpp>

namespace
{
   BFCritSec g_lock;
}

long BFObservable::nextId = 1;

//******************************************************************************
BFObservable::BFObservable()
{
   BFGuard cs( g_lock );
   _observableID = nextId++;
}

//******************************************************************************
BFObservable::~BFObservable()
{
}

//******************************************************************************
void BFObservable::notifyObservers( E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString & hint )
{
   BFNotification::getInstance()->notifyObserver( _observableID, eEventCateg, eEventId, hint );
}

//******************************************************************************
long BFObservable::getId()
{
   return(_observableID);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFObservable.cpp-arc  $
 * 
 *    Rev 1.5   Oct 09 2002 17:40:06   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   22 May 2002 17:54:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   03 Jul 2001 16:22:18   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.2   03 May 2001 14:02:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Apr 20 2000 13:09:00   DT24433
 * added lock for static variable
 * 
 *    Rev 1.0   Feb 15 2000 10:57:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.4   Jan 19 2000 10:12:00   BUZILA
// refresh stuf
// 
//    Rev 1.3   Jan 04 2000 12:16:20   BUZILA
// changes...
// 
//    Rev 1.2   Dec 21 1999 18:14:40   BUZILA
// notification changes
// 
//    Rev 1.1   Dec 21 1999 12:38:34   BUZILA
// changes
 * 
 */




