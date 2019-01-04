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
// ^FILE   :  BFAbstractConnectionMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef BFABSTRACTCONNECTIONMONITOR_HPP
   #include "BFAbstractConnectionMonitor.hpp"
#endif
#ifndef BFHOSTCONNECTIONMANAGER_HPP
   #include "BFHostConnectionManager.hpp"
#endif
#ifndef BFHOSTCONNECTIONMONITOR_HPP
   #include "BFHostConnectionMonitor.hpp"
#endif
#include <bfutil\BFGuard.hpp>

BFAbstractConnectionMonitor::BFAbstractConnectionMonitor(const int refreshRate)
:  BFThread(),
_refreshRate(refreshRate),
_shutdownEvent(true),
_hostConnMonMap(),
_hostConnMonCritSec()
{
   start();
}

BFAbstractConnectionMonitor::~BFAbstractConnectionMonitor()
{

   _shutdownEvent.set(); // signal the poller to shutdown
   wait(INFINITE); // wait for the poller to shutdown

   BFGuard guard(_hostConnMonCritSec);
   HostConnectionMonitorIterator iterator = _hostConnMonMap.begin();

   for( iterator = _hostConnMonMap.begin(); iterator != _hostConnMonMap.end(); iterator++ )
      delete (*iterator).second;  // delete the monitors

   _hostConnMonMap.clear();

}

void 
BFAbstractConnectionMonitor::registerHostConnectionManager(const BFHostConnectionManager *hostConnectionManager)
{
   BFGuard guard(_hostConnMonCritSec);

   HostConnectionMonitorIterator iterator = _hostConnMonMap.find( hostConnectionManager );

   if( _hostConnMonMap.end() == iterator )
   {
      HostConnectionMonitorMap::value_type value(hostConnectionManager, createHostConnectionMonitor(hostConnectionManager));
      _hostConnMonMap.insert( value );
   }
}

void 
BFAbstractConnectionMonitor::unregisterHostConnectionManager(const BFHostConnectionManager *hostConnectionManager)
{
   BFGuard guard(_hostConnMonCritSec);
   HostConnectionMonitorIterator iterator = _hostConnMonMap.find( hostConnectionManager );

   if( _hostConnMonMap.end() != iterator )
   {
      delete (*iterator).second;  // delete the monitors
      _hostConnMonMap.erase(iterator);
   }
}

bool
BFAbstractConnectionMonitor::refresh(BFHostConnectionMonitor *hostConnectionMonitor)
{
   return(hostConnectionMonitor->refresh());
}

void
BFAbstractConnectionMonitor::update()
{
}

void
BFAbstractConnectionMonitor::run()
{
   while( !_shutdownEvent.wait(_refreshRate) )
   {

      BFGuard guard(_hostConnMonCritSec);

      HostConnectionMonitorIterator iterator = _hostConnMonMap.begin();

      bool changed = false;
      for( iterator; iterator!=_hostConnMonMap.end(); iterator++ )
      {
         if( refresh( (*iterator).second ) )
            changed = true;
      }

      if( changed )
         update();
   }
}