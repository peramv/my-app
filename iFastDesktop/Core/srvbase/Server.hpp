#pragma once

#include <bfutil\bfevent.hpp>
#include <bfutil\bfcritsec.hpp>

#include <map>

class SrvPortal;

// Import/Export resolution
#undef SRVBASE_LINKAGE
#ifdef SRVBASE_DLL
   #define SRVBASE_LINKAGE CLASS_EXPORT
#else
   #define SRVBASE_LINKAGE CLASS_IMPORT
#endif

class SRVBASE_LINKAGE Server
{
public:
   virtual ~Server();

   void postExit();
   void postRestart();

   virtual bool keyPressed( int c );

   bool getTrace() const { 
      return bTrace_; 
   }

   bool setTrace( bool bTrace ) { 
      bool bOrig = bTrace_; 
      bTrace_ = bTrace; 
      return( bOrig); 
   }

   int run();

   void putPortal( SrvPortal *portal ); 
   SrvPortal *getPortal( const DString& name ); 

   void toggleConsoleTrace();
   bool isConsoleTraceOn() const;

   static Server* getInstance();
   static void killInstance();

protected:
   int waitForShutdown();
   static void setInstance( Server* srv );

private:
   Server();
   void postShutdown( int code );

   BFEvent _shutdownEvent;
   int _shutdownCode;

   BFCritSec csClose_;

   bool bTrace_;
   bool bLogToConsole_;

   typedef std::map<DString, SrvPortal*> PORTAL_MAP;
   PORTAL_MAP portals_;
   BFCritSec portalsGuard_;

   static Server* s_pInstance;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/Server.hpp-arc  $
//
//   Rev 1.24   Jan 27 2005 15:39:36   smithdav
//Major server rework to support "pluggable" server portals.
//
//   Rev 1.23   Feb 23 2004 11:21:54   PURDYECH
//Server::keyPressed now returns a bool.  The base function interprets 'X' and returns false, otherwise it returns true.  The Server::waitForShutdown() no longer interprets 'X' before calling keyPressed() ... it allows the default keyPressed() function to interpret the value thus giving an override first crack at the 'Exit' instruction.
//
//   Rev 1.22   Jan 22 2004 08:34:24   PURDYECH
//PET910 - Added parameter to ctor to allow a timeout value to be propagated to the BPSrvSocket objects
//
//   Rev 1.21   Nov 17 2003 19:12:04   PURDYECH
//Added two new virtual functions: cumeTxnStats and optimizeThreadPool.  Both of them default to no action.
//
//   Rev 1.20   Aug 14 2003 14:17:02   PURDYECH
//Services are no longer supported.
//XData/CData are no longer supported or needed.
//
//   Rev 1.19   Aug 12 2003 10:07:50   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.18   May 01 2003 10:52:40   PURDYECH
//Added critical section to guard the close() method.
 * 
 *    Rev 1.17   Nov 14 2002 18:14:54   PURDYECH
 * Class is a singleton so remove static methods and force clients to use the getInstance() method to access all methods.
 * 
 *    Rev 1.16   Oct 09 2002 17:42:26   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.15   22 Mar 2002 15:05:32   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.14   11 Oct 2001 17:46:54   SMITHDAV
 * Add event based server shutdown support.
 * 
 *    Rev 1.13   03 Oct 2001 15:09:52   SMITHDAV
 * Syncronization changes and Job Queue changes
 * 
 *    Rev 1.12   14 Sep 2001 20:53:08   PURDYECH
 * Allow minimum number of connections to be specified as construction argument.
 * 
 *    Rev 1.11   Jun 27 2001 20:07:18   PURDYECH
 * Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
 * 
 *    Rev 1.10   17 Jun 2001 17:40:20   PURDYECH
 * A few more changes for EFAN_REL_12.0 integration with Infrastructure Release 1.9
 * 
 *    Rev 1.9   Feb 27 2001 14:36:40   FENGYONG
 * Add refresh flag
 * 
 *    Rev 1.8   06 Dec 2000 16:24:22   SMITHDAV
 * Tweak monitors, and add thread pool monitor
 * 
 *    Rev 1.7   Sep 14 2000 11:56:56   YINGZ
 * change GEtService to virtual
 * 
 *    Rev 1.6   Jun 27 2000 11:39:14   POPESCUS
 * simplified the connection model, took out AbstractConnectionManager
 * 
 *    Rev 1.5   Jun 06 2000 10:47:42   POPESCUS
 * cleaned up the code to support only one threading model
 * 
 *    Rev 1.4   May 23 2000 10:31:46   POPESCUS
 * fixed listening to one port mechanism
 * 
 *    Rev 1.3   May 17 2000 11:05:14   POPESCUS
 * added mechanism to support levels of logging to the server
 * 
 *    Rev 1.2   Apr 04 2000 10:22:42   POPESCUS
 * fixes for the server sync-up
 * 
 *    Rev 1.1   Feb 16 2000 13:03:38   POPESCUS
 * Initial revision
 * 
 * 
 */