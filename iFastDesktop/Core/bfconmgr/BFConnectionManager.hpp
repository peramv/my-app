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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFConnectionManager.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : BFConnectionManager
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION :
//    This class provides an singleton for managing connections.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>

#include <map>

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFHostConnectionManager;
class BFConnectionFactory;
class BFConnection;
class BFConnectionMonitor;

class BFCONMGR_LINKAGE BFConnectionManager
{
public:

   static BFConnectionManager *getInstance( void );
   static void killInstance( void );

   BFConnection *getConnection(const DStringA &hostId);
   void freeConnection(BFConnection *connection);

   void createHostConnectionManager(const DStringA &hostId, BFConnectionFactory *connectionFactory, int maxConnections=0, bool persistentConnections=false, int minConnections=0);
   void destroyHostConnectionManager(const DStringA &hostId);

   void setConnectionMonitor(BFConnectionMonitor *connectionMonitor);
   const BFConnectionMonitor *getConnectionMonitor() const;

   bool recycle(const DStringA &hostId);

   unsigned int hostCount( void );

   bool ok( const DStringA &hostId );

   BFHostConnectionManager *getHostConnectionManager(const DStringA &hostId);
private:
   BFConnectionManager();
   ~BFConnectionManager();

   static BFConnectionManager *_pInstance;

   typedef std::map< DStringA, BFHostConnectionManager* >  HOST_CONNECTION_MGR_MAP;
   typedef HOST_CONNECTION_MGR_MAP::iterator               HOST_CONNECTION_MGR_MAP_ITER;
   typedef HOST_CONNECTION_MGR_MAP::value_type             HOST_CONNECTION_MGR_MAP_VALUE_TYPE;

   HOST_CONNECTION_MGR_MAP _hostManagerMap;

   BFConnectionMonitor *_connectionMonitor;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfconmgr/BFConnectionManager.hpp-arc  $
//
//   Rev 1.10   Feb 06 2009 14:59:48   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.9   Oct 09 2002 17:40:18   PURDYECH
//New PVCS Database
//
//   Rev 1.8   22 Mar 2002 15:11:32   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.7   Mar 04 2002 12:30:48   IVESPAUL
//Handle dead AS/400 listeners for both ChangeHostMode and initial startup + 
//Logging changes.
//
//   Rev 1.6   Oct 22 2001 17:17:32   HUDAVID
//Connection Recycle code.
//
//   Rev 1.5   03 May 2001 14:03:20   SMITHDAV
//Session management restructuring.
//
//   Rev 1.4   04 Dec 2000 11:38:20   SMITHDAV
//Add console connection monitoring support.
//
//   Rev 1.3   23 Oct 2000 20:13:16   SMITHDAV
//Change linkage to support new library BFConMfg.
//
//   Rev 1.2   May 02 2000 17:25:50   DT24433
//changed to use Infra CriticalSection
//
//   Rev 1.1   Apr 28 2000 19:20:18   SMITHDAV
//Added monitor support.
//
//   Rev 1.0   Apr 14 2000 14:10:04   SMITHDAV
//Initial revision.
*/