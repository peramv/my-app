#include "stdafx.h"
#define SRVBASE_DLL
#include "ConnectionJob.hpp"
#include <bfutil\BFException.hpp>
#include <xparser\XparserException.hpp>
#include <xparser\SaxStateManager.hpp>
#include "Server.hpp"
#include "BPSrvSocket.hpp"

#include <iostream>

#include <bfutil\BFExecutionContext.hpp>
#include <bfutil\txnstats.hpp>
#include <bfutil\bfhrtimer.hpp>

#include <xercesc/util/PlatformUtils.hpp>
#include <bfutil/BFIPBlast.hpp>

#include <bfutil/bfguard.hpp>

/*==========================================================================
 *------------------------------ Class Members -----------------------------
 *==========================================================================*/
BFCritSec ConnectionJob::s_csJobId_;
unsigned int ConnectionJob::s_idNextJob_ = 0;   
   
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ConnectionJob" );
   const I_CHAR * const RUN = I_( "run" );
}

ConnectionJob::ConnectionJob( BPSrvSocket *socket, Server *server, bool bTrace /*= false*/ ) 
: _clientSocket( socket )
, _server( server )
, bTrace_( bTrace )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

ConnectionJob::~ConnectionJob()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   //here we have to close the connection with the client
   delete _clientSocket;
}

void ConnectionJob::run()
{
   MAKEFRAMEAUTOPROMOTE2( CND::SRVBASE_CONDITION, CLASSNAME, RUN );
   unsigned long ulBytesRead = 0L;
   unsigned long ulBytesWritten = 0L;
   DStringA buffer;
   DString strIn;

   assignJobId();

   _server->incrementRequestCount();

   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information;
   ls << I_( "Processing Transaction " ) << getJobId() << bf::log::endlf;
//CP20040213   Removed this line because it can be *VERY* slow if the connecting socket is not
//CP20040213   'well-known' to us (i.e. if we have to search all over the internet for a name
//CP20040213   for the host).  As all we are doing is logging some information is seems excessive
//CP20040213   to get this information.
//CP20040213   ls << I_( " from ") << _clientSocket->getClientAddress() << I_( "." ) << bf::log::endl;

   BFHRTimer tRead;
   BFHRTimer tTxn;
   ulBytesRead = _clientSocket->read( buffer );
   tRead.stop();
   ls << I_( "Socket read took " ) << tRead.elapsed() << I_( "msecs." ) << bf::log::endlf;


   if( buffer.size() > 0 )
   {
      // BFExecutionContext::create will create a new one if
      // one does not exist.  If one exists the object
      // will be reset
      BFExecutionContext* pContext = BFExecutionContext::create();
      TxnStats* pTxnStats = TxnStats::get(); // this will create the TxnStats object and
                                             // attach it to the context automatically
      if( bTrace_ )
      {
         ls << bf::log::endl << I_( "request: [" ) << DString( buffer ) << I_( "]" ) << bf::log::endl << bf::log::endlf;
      }

      DString strOut;

      if( buffer[0] != '<' )
      {  // old style request
         ls << I_( "Invalid request header.  Only XML packets are supported." ) << bf::log::endl;
         ls << I_( "First character is " ) << buffer[0] << I_( ", expected <" ) << bf::log::endlf;
         assert( false );
      }
      else
      {  // XML request
         DStringA bufferOut;
         xp::SaxStateManager saxStateManager;

         BFIPBlast::getInstance()->writeBuffer( I_( "XMLRequest" ), buffer );

         saxStateManager.parse( buffer, bufferOut );
         BFHRTimer tWrite;
         _clientSocket->write( bufferOut.c_str(), bufferOut.size(), &ulBytesWritten );
         tWrite.stop();
         tTxn.stop();
         ls << I_( "Socket write took " ) << tWrite.elapsed() << I_( "msecs." ) << bf::log::endlf;

         if( bTrace_ )
         {
            ls << bf::log::endl << I_( "response: [" ) << DString(bufferOut) << I_( "]" ) << bf::log::endl << bf::log::endlf;
         }
      }

      // accumulate these transaction stats into the Server
      _server->cumeTxnStats( tTxn.elapsed(), pTxnStats );
   } 
   else 
   {
      ls << I_( "No data read from socket." ) << bf::log::endlf;
   }
   ls << I_( "Transaction " ) << getJobId() << I_( " completed in " ) << tTxn.elapsed() << I_( "msecs." ) << bf::log::endlf;
}

void ConnectionJob::assignJobId() 
{
   BFGuard g( s_csJobId_ );
   idJob_ = ++s_idNextJob_;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/ConnectionJob.cpp-arc  $
//
//   Rev 1.31   Mar 10 2004 12:53:36   PURDYECH
//PET910 - Improved logging.
//
//   Rev 1.30   Mar 09 2004 10:58:58   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.29   Feb 13 2004 11:05:50   PURDYECH
//Removed logging of connection IP address.
//
//   Rev 1.28   Nov 17 2003 19:10:34   PURDYECH
//Accumulate transaction stats upon completion of job (used for auto-tuning in Server)
//
//   Rev 1.27   Aug 14 2003 14:17:12   PURDYECH
//Services are no longer supported.
//
//   Rev 1.26   Aug 12 2003 10:07:54   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.25   May 02 2003 15:44:08   PURDYECH
//Use BPSrvSocket::getClientName and log this information for each request.
 * 
 *    Rev 1.24   Nov 14 2002 18:14:06   PURDYECH
 * Support Console tracing externally
 * 
 *    Rev 1.23   Oct 09 2002 17:42:24   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.22   Jul 02 2002 14:24:04   ROSIORUC
 * Added i_cout for XML output
 * 
 *    Rev 1.21   07 Jun 2002 10:55:30   SMITHDAV
 * Sync-up with Chris' changes.
 * 
 *    Rev 1.20   14 May 2002 16:42:38   SMITHDAV
 * put xparser code namespace xp.
 * 
 *    Rev 1.19   10 May 2002 13:02:24   SMITHDAV
 * Remove some txnstat calls for xml. ( restore later ).
 * 
 *    Rev 1.18   02 Apr 2002 13:44:44   SMITHDAV
 * Change the way XML processing is handled.
 * 
 *    Rev 1.17   03 Oct 2001 15:09:50   SMITHDAV
 * Syncronization changes and Job Queue changes
 * 
 *    Rev 1.16   06 Sep 2001 20:48:50   PURDYECH
 * Added code to write IPBlast scripts.
 * 
 *    Rev 1.15   Aug 29 2001 10:32:02   IVESPAUL
 * Show requests before Service/XML has run.
 *
 *    Rev 1.14   Aug 28 2001 10:40:38   FENGYONG
 * add xparserException
 *
 *    Rev 1.13   Aug 24 2001 16:15:26   FENGYONG
 * write back some information to ecomm when throw cnd happen
 *
 *    Rev 1.12   24 Jul 2001 19:59:26   PURDYECH
 * Integrated with BFExecutionContext.
 *
 *    Rev 1.11   17 Jul 2001 11:05:02   PURDYECH
 * Use new upgraded TxnStats class
 *
 *    Rev 1.10   Jun 27 2001 20:07:08   PURDYECH
 * Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
 *
 *    Rev 1.9   18 Jun 2001 11:13:14   PURDYECH
 * Added LogFileOnly method to Logger
 * Removed publicly available class variables from Logger
 * Tuned synchronization so it happens only when needed.
 *
 *    Rev 1.8   17 Jun 2001 16:18:30   PURDYECH
 * More fixes for EFAN_REL_12.0 integration with Infrastructure Release 1.9
 *
 *    Rev 1.7   Jun 15 2001 19:43:46   PURDYECH
 * Infrastructure 1.9 integration
 *
 *    Rev 1.6   Nov 15 2000 14:13:24   DT24433
 * changes for batchhandler
 *
 *    Rev 1.5   Sep 14 2000 11:55:54   YINGZ
 * change to create one service for each request
 *
 *    Rev 1.4   Aug 23 2000 10:59:30   DT24433
 * Moved job related logic to this class (removed Connection class
 *
 *    Rev 1.3   Jun 06 2000 10:47:38   POPESCUS
 * cleaned up the code to support only one threading model
 *
 *    Rev 1.2   May 23 2000 10:31:36   POPESCUS
 * fixed listening to one port mechanism
 *
 *    Rev 1.1   Feb 16 2000 13:03:36   POPESCUS
 * Initial revision
 *
 *
 */