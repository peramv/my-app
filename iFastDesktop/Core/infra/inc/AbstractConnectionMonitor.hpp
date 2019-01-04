#pragma message( "including "__FILE__ )

#ifndef ABSTRACTCONNECTIONMONITOR_HPP
#define ABSTRACTCONNECTIONMONITOR_HPP

/**
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

#ifndef PLATFORM_H
   #include "platform.h"
#endif
#ifndef BASECONNECTIONMONITOR_HPP
   #include "baseconnectionmonitor.hpp"
#endif
#ifndef INFRAEVENT_HPP
   #include "infraevent.hpp"
#endif
#ifndef INFRATHREAD_HPP
   #include "infrathread.hpp"
#endif

#ifndef INCLUDED_MAP
   #include <map>
   #define INCLUDED_MAP
#endif

class BaseHostConnectionManager;
class BaseHostConnectionMonitor;

/**
 * Abstract Connection Monitor class
 *
 * Class is the parent for most connection monitor classes.  It provides the
 * common functions needed to monitor the status of the connection manager.
 */
class DIVIEW_LINKAGE AbstractConnectionMonitor : public InfraThread, virtual public BaseConnectionMonitor
{
public:
   AbstractConnectionMonitor( const int refreshRate = 1000 );
   virtual ~AbstractConnectionMonitor( );

   virtual void registerHostConnectionManager( const BaseHostConnectionManager * hostConnectionManager );
   virtual void unregisterHostConnectionManager( const BaseHostConnectionManager * hostConnectionManager );

   virtual BaseHostConnectionMonitor * createHostConnectionMonitor( const BaseHostConnectionManager * hostConnectionManager ) = 0;
   virtual bool refresh( BaseHostConnectionMonitor * hostConnectionMonitor );
   virtual void update( );

protected:
   virtual void run( );

private:

   const int _refreshRate;
   InfraEvent _shutdownEvent;

   typedef std::map<const BaseHostConnectionManager *, BaseHostConnectionMonitor *> HostConnectionMonitorMap;
   typedef std::map<const BaseHostConnectionManager *, BaseHostConnectionMonitor *>::iterator HostConnectionMonitorIterator;

   HostConnectionMonitorMap _hostConnMonMap;
};

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
// $Log:   Y:/VCS/iFastAWD/inc/AbstractConnectionMonitor.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:40   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:40   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 15:51:46   DT11159
// 
//
//

#endif
