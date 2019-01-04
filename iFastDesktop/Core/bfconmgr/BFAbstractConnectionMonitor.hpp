#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif

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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFAbstractConnectionMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2000
//
// ^CLASS    : BFAbstractConnectionMonitor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class is an abstract BFConnectionManager derivative that implements basic 
//    management for most simple monitors.
//    
//
//******************************************************************************
#include <win32\platform.h>
#include <bfconmgr\bfconnectionmonitor.hpp>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfthread.hpp>
#include <map>

class BFHostConnectionManager;
class BFHostConnectionMonitor;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFAbstractConnectionMonitor  : public BFThread, virtual public BFConnectionMonitor
{
public:
   BFAbstractConnectionMonitor(const int refreshRate=1000);
   virtual ~BFAbstractConnectionMonitor();

   virtual void registerHostConnectionManager(const BFHostConnectionManager *hostConnectionManager);
   virtual void unregisterHostConnectionManager(const BFHostConnectionManager *hostConnectionManager);

   virtual BFHostConnectionMonitor *createHostConnectionMonitor(const BFHostConnectionManager *hostConnectionManager) = 0;
   virtual bool refresh(BFHostConnectionMonitor *hostConnectionMonitor);
   virtual void update();

protected:
   virtual void run();

private:

   const int _refreshRate;
   BFEvent _shutdownEvent;

   typedef std::map<const BFHostConnectionManager *, BFHostConnectionMonitor *> HostConnectionMonitorMap;
   typedef std::map<const BFHostConnectionManager *, BFHostConnectionMonitor *>::iterator HostConnectionMonitorIterator;

   HostConnectionMonitorMap _hostConnMonMap;
   BFCritSec _hostConnMonCritSec; 
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/BFAbstractConnectionMonitor.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:40:16   PURDYECH
//New PVCS Database
//
//   Rev 1.3   22 Mar 2002 15:11:24   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   03 Oct 2001 15:09:58   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.1   Jun 27 2001 20:07:40   PURDYECH
//Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//   Rev 1.0   17 Jun 2001 11:31:48   PURDYECH
//Initial revision.
//
//   Rev 1.1   06 Dec 2000 11:47:44   SMITHDAV
//Update monitoring console; Added DataBroker monitor.
//
//   Rev 1.0   04 Dec 2000 11:51:40   SMITHDAV
//Initial revision.
// 
*/