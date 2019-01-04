#include "stdafx.h"
#include <ifastbps/visionserver.hpp>
#include <bfutil/bfcritsec.hpp>
#include <bfutil/bfguard.hpp>
#include <bfutil/console.hpp>
#include <bf/log/log.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "VisionServer" );
   BFCritSec g_InstanceGuard;
}


VisionServer* VisionServer::getInstance()
{
   BFGuard g( g_InstanceGuard );
   return dynamic_cast< VisionServer* >( Server::getInstance() );
}

void VisionServer::killInstance()
{
   BFGuard g( g_InstanceGuard );
   VisionServer* pServer = dynamic_cast< VisionServer* >( Server::getInstance() );
   delete pServer;
   Server::setInstance( NULL );
}

VisionServer* VisionServer::createInstance( int port,
                                            int threadCount,
                                            int queueSize,
                                            bool bTrace /*= false */,
                                            int iTimeout /*=0*/ ) 
{
   BFGuard g( g_InstanceGuard );
   VisionServer* pServer = new VisionServer( port, threadCount, queueSize, bTrace, iTimeout );
   Server::setInstance( pServer );
   return( pServer );
}

//******************************************************************************
bool VisionServer::keyPressed( int c )
{
   bool bRc = true;
   switch( c )
   {
      case 'M':
         if( Console::getInstance()->getMode() == Console::MAIN ) {
            // the Console is currently in 'fancy mode'.  Flip it to 'message mode'
            // and start logging to console again (if in debug)
            Console::getInstance()->setMode( Console::MESSAGE );
            if( bLogToConsole_ ) {
               bf::log::theLog.restartTarget( I_( "console" ) );
            } else {
               bf::log::theLog.suspendTarget( I_( "console" ) );
            }
         } 
         else {
            // the Console is currently in 'message mode'.  Flip it to 'main mode'
            // and stop logging to console
            Console::getInstance()->setMode( Console::MAIN );
            bf::log::theLog.suspendTarget( I_( "console" ) );
         }
         break;
      case 'T':
         bLogToConsole_ = !bLogToConsole_;
         toggleConsoleTrace();
         bRc = Server::keyPressed(c);
         break;
      case 'X':
         bRc = Server::keyPressed(c);
         break;
      default:
         bRc = Server::keyPressed(c);
         break;
   }
   return( bRc );
}

//******************************************************************************
void VisionServer::toggleConsoleTrace()
{
   setTrace( !getTrace() );

   bf::log::LogStream ls( bf::log::service );
   ls << bf::log::critical;
   if( getTrace() )
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
bool VisionServer::isConsoleTraceOn() const
{
   return( getTrace() );
}

VisionServer::VisionServer( int port,
                            int threadCount, 
                            int queueSize, 
                            bool bTrace /*= false */,
                            int iTimeout /*=0*/ ) 
: Server( port, threadCount, queueSize, bTrace, iTimeout )
, bLogToConsole_( false )
, bNoisy_( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

VisionServer::~VisionServer()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/VisionServer.cpp-arc  $
// 
//    Rev 1.2   Feb 25 2004 11:05:30   PURDYECH
// Server::keyPressed() now returns a bool.
// 
//    Rev 1.1   Jan 22 2004 14:46:38   PURDYECH
// PET 910 - Added keyboard handling and trace suppression
// 
//    Rev 1.0   Aug 21 2003 11:02:06   PURDYECH
// Initial revision.
 // 
 //    Rev 1.33   Jul 29 2003 11:15:22   FENGYONG
 // add bTrace
 // 
 //    Rev 1.32   Jul 29 2003 10:48:08   FENGYONG
 // Add bTrace
 // 
 //    Rev 1.31   Feb 19 2003 15:18:30   SMITHDAV
 // Update VisionServer to have a sigleton interface and expected by the core classes.
 // 
 //    Rev 1.30   Oct 09 2002 23:56:30   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.29   22 May 2002 19:22:42   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.28   03 Oct 2001 15:10:16   SMITHDAV
 // Syncronization changes and Job Queue changes
 // 
 //    Rev 1.27   Dec 05 2000 16:00:20   VASILEAD
 // Launched Purchase service instead VerificationConf for Exchange
 // 
 //    Rev 1.26   Dec 04 2000 13:28:26   VASILEAD
 // Added FundToListService
 // 
 //    Rev 1.25   Nov 30 2000 10:02:48   FENGYONG
 // Add FundToList
 // 
 //    Rev 1.24   Nov 21 2000 10:19:22   VASILEAD
 // Added AllFundInfoService
 // 
 //    Rev 1.23   Nov 17 2000 14:41:46   FENGYONG
 // change pname for removeDE
 // 
 //    Rev 1.22   Nov 01 2000 10:36:50   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.21   Oct 27 2000 16:11:08   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.20   Oct 13 2000 10:01:42   FENGYONG
 // Add trading list
 // 
 //    Rev 1.18   Oct 03 2000 11:19:50   VASILEAD
 // Added NASU server support
 // 
 //    Rev 1.17   Sep 27 2000 11:33:18   YINGZ
 // add page ACCT_DTL0
 // 
 //    Rev 1.16   Sep 25 2000 15:43:14   YINGZ
 // clear internal logon logoff code
 // 
 //    Rev 1.15   Sep 19 2000 15:21:16   VASILEAD
 // Cleanup services, UserSeesionProcess and security object
 // 
 //    Rev 1.14   Sep 18 2000 14:17:28   YINGZ
 // move namespace around
 // 
 //    Rev 1.13   Sep 14 2000 11:58:26   YINGZ
 // change to create new service for each page request
 // 
 //    Rev 1.12   Sep 07 2000 12:01:22   FENGYONG
 // Add new service
 // 
 //    Rev 1.11   Aug 16 2000 12:04:34   YINGZ
 // support multi locale condition
 // 
 //    Rev 1.10   Aug 10 2000 19:34:54   FENGYONG
 // Add JEntityListProcess
 // 
 //    Rev 1.9   Aug 02 2000 16:20:46   VASILEAD
 // Added Maintenance Service
 // 
 //    Rev 1.8   Jul 25 2000 17:39:36   YINGZ
 // uncomment several lines for others
 // 
 //    Rev 1.7   Jul 25 2000 17:33:34   YINGZ
 // add internal logon off service
 // 
 //    Rev 1.6   Jul 21 2000 14:57:38   VASILEAD
 // Fixed VerificationConf
 // 
 //    Rev 1.5   Jul 20 2000 15:18:32   VASILEAD
 // Added VerificationConf service, process and CBO
 // 
 //    Rev 1.4   May 17 2000 11:05:32   POPESCUS
 // added mechanism to support levels of logging to the server
 // 
 //    Rev 1.3   May 08 2000 17:07:58   YINGZ
 // add RedCodeByTaxType service
 // 
 //    Rev 1.2   Apr 26 2000 13:48:42   YINGZ
 // change name for HYPOTHETICALRED
 // 
 //    Rev 1.1   Apr 25 2000 16:14:08   YINGZ
 // add new service
 // 
 //    Rev 1.0   Apr 04 2000 10:26:10   POPESCUS
 // Initial revision.
 * 
 * 
 */
