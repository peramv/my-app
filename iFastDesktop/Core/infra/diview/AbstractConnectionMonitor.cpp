/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

/**
 *   Author:  David Sample
 *
 *   Class:   AbstractConnectionMonitor.cpp
 *
 *   @@@Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "SrcPrag.h"
#endif
#ifndef ABSTRACTCONNECTIONMONITOR_HPP
   #include "AbstractConnectionMonitor.hpp"
#endif
#ifndef BASEHOSTCONNECTIONMANAGER_HPP
   #include "BaseHostConnectionManager.hpp"
#endif
#ifndef BASEHOSTCONNECTIONMONITOR_HPP
   #include "BaseHostConnectionMonitor.hpp"
#endif

AbstractConnectionMonitor::AbstractConnectionMonitor(const int refreshRate)
:  InfraThread(),
   _refreshRate(refreshRate),
   _shutdownEvent(true),
   _hostConnMonMap()
{
   start();
}

AbstractConnectionMonitor::~AbstractConnectionMonitor()
{

   _shutdownEvent.set(); // signal the poller to shutdown
   wait(INFINITE); // wait for the poller to shutdown

   HostConnectionMonitorIterator iterator = _hostConnMonMap.begin();

   for ( iterator = _hostConnMonMap.begin(); iterator != _hostConnMonMap.end(); iterator++)
      delete (*iterator).second;  // delete the monitors

   _hostConnMonMap.clear();

}

void
AbstractConnectionMonitor::registerHostConnectionManager(const BaseHostConnectionManager *hostConnectionManager)
{
   HostConnectionMonitorIterator iterator = _hostConnMonMap.find( hostConnectionManager );

   if ( _hostConnMonMap.end() == iterator )
   {
      HostConnectionMonitorMap::value_type value(hostConnectionManager, createHostConnectionMonitor(hostConnectionManager));
      _hostConnMonMap.insert( value );
   }
}

void
AbstractConnectionMonitor::unregisterHostConnectionManager(const BaseHostConnectionManager *hostConnectionManager)
{
   HostConnectionMonitorIterator iterator = _hostConnMonMap.find( hostConnectionManager );

   if ( _hostConnMonMap.end() != iterator )
   {
      delete (*iterator).second;  // delete the monitors
      _hostConnMonMap.erase(iterator);
   }
}

bool
AbstractConnectionMonitor::refresh(BaseHostConnectionMonitor *hostConnectionMonitor)
{
   return hostConnectionMonitor->refresh();
}

void
AbstractConnectionMonitor::update()
{
}

void
AbstractConnectionMonitor::run()
{
   while ( WAIT_TIMEOUT == _shutdownEvent.wait(_refreshRate) )
   {

      bool changed = false;
      HostConnectionMonitorIterator iterator = _hostConnMonMap.begin();

      for ( iterator; iterator!=_hostConnMonMap.end(); iterator++)
      {
         if ( refresh( (*iterator).second ) )
            changed = true;
      }

      if ( changed )
         update();
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
// $Log:   Y:/VCS/iFastAWD/diview/AbstractConnectionMonitor.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:48   kovacsro
// Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:26   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 11:39:48   DT11159
// 
//
//
