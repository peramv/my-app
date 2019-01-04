// Server.cpp
//
#include "stdafx.h"
#include "server.hpp"
#include "srvportal.hpp"

#include <bfutil\Console.hpp>
#include <bfutil\bfwaitableset.hpp>
#include <bfutil\bfguard.hpp>
#include <bf\log\log.hpp>

#include <iomanip>
#include <sstream>


namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "Server" );
}

Server* Server::s_pInstance = NULL;

Server* Server::getInstance() {
   if ( s_pInstance == NULL ) {
      s_pInstance =  new Server();
   }
   return( s_pInstance );
}

void Server::setInstance( Server* srv ) {
   assert( s_pInstance != NULL );
   s_pInstance =  srv;

}

void Server::killInstance() {
   if ( s_pInstance != NULL ) {
      delete s_pInstance;
      s_pInstance = NULL;
   }
}

Server::Server() 
: _shutdownEvent( true )      //manual reset event, initially non-signaled
, _shutdownCode(0)
, bTrace_( false )
, bLogToConsole_( false )
, portals_()
, portalsGuard_()
{
}

Server::~Server() {
   BFGuard g(portalsGuard_);
   PORTAL_MAP::iterator iter = portals_.begin();
   while ( iter!=portals_.end() ) {
      (*iter).second->close();
      delete (*iter).second;
      iter = portals_.erase(iter);
   }
}

void Server::postExit() {
   postShutdown( 0 );
}

void Server::postRestart() {
   postShutdown( 255 );
}

void Server::postShutdown( int code ) {
   BFGuard closeGuard( csClose_ ); // one poster at a time

   if( _shutdownEvent.wait(0) )
      return; // already posted

   _shutdownCode = code;
   _shutdownEvent.set();
}

void Server::putPortal( SrvPortal *portal ) {
   if ( portal != NULL ) {
      BFGuard g(portalsGuard_);

      const DString &name = portal->getName();
      PORTAL_MAP::iterator iter = portals_.find( name );
      if ( iter != portals_.end() ) {
         delete (*iter).second;
         portals_.erase(iter);
      }

      portals_.insert( PORTAL_MAP::value_type(name, portal) );
   }
}

SrvPortal *Server::getPortal( const DString& name ) {
   BFGuard g(portalsGuard_);
   PORTAL_MAP::iterator iter = portals_.find( name );

   if ( iter != portals_.end() ) {
      return (*iter).second;
   }
   return NULL;
}

int Server::run() {
   {
      BFGuard g(portalsGuard_);
      PORTAL_MAP::iterator iter = portals_.begin();
      while ( iter!=portals_.end() ) {
         (*iter).second->start();
         ++iter;
      }
   }

   return waitForShutdown();
}

int Server::waitForShutdown() {

   Console::getInstance()->setMode(Console::MAIN);

   ConsoleInput &consoleInput = Console::getInstance()->getConsoleInput();
   BFKernel* _waitObjects[] = { &consoleInput, &_shutdownEvent};
   BFWaitableSet waitSet( _waitObjects, 2 );

   bool bContinue = true;
   while( bContinue ) {
      BFKernel *waitResult = NULL;
      waitSet.wait( waitResult );

      if( *waitResult == _shutdownEvent ) {
         break;
      }

      int c = toupper(consoleInput.getChar());

      if( c != -1 ) {
         bContinue = keyPressed( c );
      }
   }

   Console::getInstance()->setMode(Console::MESSAGE);
   return(_shutdownCode);
}

bool Server::keyPressed( int c ) {
   bool bRc = true;
   switch( c )
   {
      case 'M':
         if( Console::getInstance()->getMode() == Console::MAIN ) {
            // the Console is currently in 'fancy mode'.  Flip it to 'message mode'
            // and start logging to console again (if in debug)
            Console::getInstance()->setMode( Console::MESSAGE );
         } 
         else {
            // the Console is currently in 'message mode'.  Flip it to 'main mode'
            // and stop logging to console
            Console::getInstance()->setMode( Console::MAIN );
         }
         break;
      case 'T':
         toggleConsoleTrace();
         break;
      case 'X':
         _shutdownCode = 0;
         bRc = false;
         break;
      default:
         break;
   }
   return( bRc );
}

//******************************************************************************
void Server::toggleConsoleTrace()
{
   bLogToConsole_ = !bLogToConsole_;

   bf::log::LogStream ls( bf::log::service );
   ls << bf::log::critical;
   if( bLogToConsole_ )
   {
      bf::log::theLog.restartTarget( I_( "console" ) );
      ls << I_( "++ ConsoleTrace switched on..." ) << bf::log::endlf;
   }
   else
   {
      ls << I_( "++ ConsoleTrace switched off." ) << bf::log::endlf;
      bf::log::theLog.suspendTarget( I_( "console" ) );
   }
}

//******************************************************************************
bool Server::isConsoleTraceOn() const
{
   return( getTrace() );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/Server.cpp-arc  $
//
//   Rev 1.33   Mar 29 2006 13:21:58   smithdav
//Added SrvPortal close logic and call from Server. This fixes a destruction bug in which the concrete protal class is partially destroyed before it's thread pool is closed.
//
//   Rev 1.32   Mar 08 2005 08:22:18   smithdav
//Fix minor bug which turns tracing off when toggling display modes.
//
//   Rev 1.31   Jan 27 2005 15:39:38   smithdav
//Major server rework to support "pluggable" server portals.
//
//   Rev 1.30   Feb 23 2004 11:21:52   PURDYECH
//Server::keyPressed now returns a bool.  The base function interprets 'X' and returns false, otherwise it returns true.  The Server::waitForShutdown() no longer interprets 'X' before calling keyPressed() ... it allows the default keyPressed() function to interpret the value thus giving an override first crack at the 'Exit' instruction.
//
//   Rev 1.29   Jan 22 2004 08:34:14   PURDYECH
//PET910 - Added parameter to ctor to allow a timeout value to be propagated to the BPSrvSocket objects
//
//   Rev 1.28   Nov 17 2003 19:11:24   PURDYECH
//Optimize the threadpool before posting a new job
//
//   Rev 1.27   Aug 14 2003 14:16:58   PURDYECH
//Services are no longer supported.
//XData/CData are no longer supported or needed.
//
//   Rev 1.26   Aug 12 2003 10:07:50   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.25   May 02 2003 15:46:38   PURDYECH
//Changed some thread naming logic for debugging.
//
//   Rev 1.24   May 01 2003 10:53:08   PURDYECH
//Use new critical section to guard close() method.
//Added thread naming code.
 * 
 *    Rev 1.23   Feb 07 2003 14:42:46   PURDYECH
 * No need to affect thread priority.
 * 
 *    Rev 1.22   Nov 14 2002 18:14:48   PURDYECH
 * Class is a singleton so remove static methods and force clients to use the getInstance() method to access all methods.
 * 
 *    Rev 1.21   Oct 09 2002 17:42:26   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.20   22 May 2002 17:49:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.19   11 Oct 2001 17:46:54   SMITHDAV
 * Add event based server shutdown support.
 * 
 *    Rev 1.18   03 Oct 2001 15:09:52   SMITHDAV
 * Syncronization changes and Job Queue changes
 * 
 *    Rev 1.17   14 Sep 2001 20:51:40   PURDYECH
 * Added support for specifying minimum number of connections.
 * 
 *    Rev 1.16   Jun 27 2001 20:07:12   PURDYECH
 * Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
 * 
 *    Rev 1.15   18 Jun 2001 11:13:14   PURDYECH
 * Added LogFileOnly method to Logger
 * Removed publicly available class variables from Logger
 * Tuned synchronization so it happens only when needed.
 * 
 *    Rev 1.14   Feb 27 2001 14:36:16   FENGYONG
 * Add refresh flag
 * 
 *    Rev 1.13   06 Dec 2000 16:24:20   SMITHDAV
 * Tweak monitors, and add thread pool monitor
 * 
 *    Rev 1.12   Jun 27 2000 11:39:08   POPESCUS
 * simplified the connection model, took out AbstractConnectionManager
 * 
 *    Rev 1.11   Jun 06 2000 10:47:40   POPESCUS
 * cleaned up the code to support only one threading model
 * 
 *    Rev 1.10   May 26 2000 16:07:24   POPESCUS
 * fixes related to growing the size of the socket queue 
 * 
 *    Rev 1.9   May 23 2000 10:31:42   POPESCUS
 * fixed listening to one port mechanism
 * 
 *    Rev 1.8   May 17 2000 11:05:12   POPESCUS
 * added mechanism to support levels of logging to the server
 * 
 *    Rev 1.7   May 12 2000 16:20:40   YINGZ
 * increase mac connection num
 * 
 *    Rev 1.6   May 11 2000 14:02:20   SMITHDAV
 * Remove further references to BFConnectionManager.
 * 
 *    Rev 1.5   May 11 2000 11:35:28   SMITHDAV
 * Removed ConnectionManager configuration -- done at project level now.
 * 
 *    Rev 1.4   May 10 2000 18:05:34   SMITHDAV
 * Update on call to VMPrivateConnectionFactory constructor to specify connection name prefix.
 * 
 *    Rev 1.3   May 02 2000 17:59:16   SMITHDAV
 * Add Connection Manager Initialization
 * 
 *    Rev 1.2   Apr 04 2000 10:22:42   POPESCUS
 * fixes for the server sync-up
 * 
 *    Rev 1.1   Feb 16 2000 13:03:40   POPESCUS
 * Initial revision
 * 
 * 
 */