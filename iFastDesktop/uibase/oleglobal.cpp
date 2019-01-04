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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : OleGlobal.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 21 Apr 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : OleGlobal
//
// ^MEMBER VARIABLES :
//
//      static InstanceManager  _instanceManager    - Manages the singleton
//      EventSemaphore         *_searchScreenReady  - Semaphore to let OLE
//                                                    objects know when the
//                                                    Search screen is ready
//      CWnd                   *_searchDialog       - Pointer to the search
//                                                    screen to post messages
//                                                    with
//      string                  _id                 - Id of the singleton
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define WIN32UIBASE_DLL

#include "stdafx.h"

#ifndef OLEGLOBAL_HPP
   #include "OleGlobal.hpp"
#endif
#ifndef EVENTSEMAPHORE_HPP
   #include <EventSemaphore.hpp>
#endif

#ifndef INCLUDED_AFXMT_H
#define INCLUDED_AFXMT_H
#include <afxmt.h>
#endif

namespace
{
   const I_CHAR *OLE_GLOBAL = I_( "OLE_GLOBAL" );

   CCriticalSection criticalSection;       // Used to make sure only one thread
                                           // at a time can call getInstance()
}

namespace CND
{
}
//******************************************************************************
//              Public Methods
//******************************************************************************

OleGlobal *OleGlobal::getInstance()
{
   // Make sure only one thread is accessing this method at one time
   CSingleLock singleLock( &criticalSection );
   singleLock.Lock();

   // Get the singleton
   OleGlobal *pInstance = _instanceManager.getInstance( OLE_GLOBAL );
   return(pInstance);
}

void OleGlobal::setSearchScreenReady( CWnd *searchDialog )
{
   // Make sure only one thread is accessing this method at one time
   CSingleLock singleLock( &criticalSection );
   singleLock.Lock();

   // Remember the Search Screen
   _searchDialog = searchDialog;
   // Let any OLE object know the Search Screen is ready for messages.
   _searchScreenReady->post();
}

void OleGlobal::waitForSearchScreen()
{
   _searchScreenReady->wait();
}

bool OleGlobal::postMessageToSearchScreen( UINT msg, WPARAM wparam, LPARAM lparam )
{
   // Make sure only one thread is accessing this method at one time
   CSingleLock singleLock( &criticalSection );
   singleLock.Lock();

   bool success = false;

   // Only post the message if we have a pointer to the search screen
   if( _searchDialog )
   {
      success = _searchDialog->PostMessage( msg, wparam, lparam ) != FALSE;
   }

   return(success);
}

bool OleGlobal::sendMessageToSearchScreen( UINT msg, WPARAM wparam, LPARAM lparam )
{
   // Make sure only one thread is accessing this method at one time
   CSingleLock singleLock( &criticalSection );
   singleLock.Lock();

   bool success = false;

   // Only send the message if we have a pointer to the search screen
   if( _searchDialog )
   {
      success = _searchDialog->SendMessage( msg, wparam, lparam ) != FALSE;
   }

   return(success);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

OleGlobal::OleGlobal( const DString &id )
: _id( id )
{
   _searchDialog = NULL;
   _searchScreenReady = new EventSemaphore;
}

OleGlobal::~OleGlobal()
{
   delete _searchScreenReady;
}

//******************************************************************************
//              Static member objects
//******************************************************************************

OleGlobal::InstanceManager OleGlobal::_instanceManager;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/oleglobal.cpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Sep 10 2002 14:34:42   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.1   Feb 25 2002 18:58:08   PURDYECH
 * Removed annoying compiler warnings.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:42   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
