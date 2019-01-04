#include "stdafx.h"
#include "srvjob.hpp"
#include "srvportal.hpp"
#include "server.hpp"


#include <bfutil\bfguard.hpp>
#include <bfutil\txnstats.hpp>
#include <bfutil\bfhrtimer.hpp>
#include <bfutil\BFIPBlast.hpp>

#include <xparser\ExecutionResult.hpp>
//#include <xparser\XparserException.hpp>
#include <xparser\SaxStateManager.hpp>

#include <bf\log\log.hpp>

BFCritSec SrvJob::s_csJobId_;
unsigned int SrvJob::s_idNextJob_ = 0;   

unsigned int SrvJob::getNextJobId() {
   BFGuard g( s_csJobId_ );
   return (++s_idNextJob_);
}


SrvJob::SrvJob( SrvPortal* portal ) 
: portal_( portal )
, bTrace_( Server::getInstance()->getTrace() )
, idJob_( getNextJobId() )
, acceptStartTime_()
{
}

SrvJob::~SrvJob() {
}

void SrvJob::run() {

   portal_->incrementRequestCount();
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "Processing Transaction " ) << getJobId() << bf::log::endlf;

   DStringA bufferIn;
   DStringA bufferOut;

   BFHRTimer tRead;
   BFHRTimer tTxn;
   readRequest( bufferIn );
   tRead.stop();

   ls << I_( "Request read took " ) << tRead.elapsed() << I_( "msecs." ) << bf::log::endlf;

   if( bufferIn.size() > 0 )
   {
      // BFExecutionContext::create will create a new one if
      // one does not exist.  If one exists the object
      // will be reset
      BFExecutionContext* pContext = BFExecutionContext::create();
      TxnStats* pTxnStats = TxnStats::get(); // this will create the TxnStats object and
                                             // attach it to the context automatically
      if( bTrace_ )
      {
         ls << bf::log::endl << I_( "request: [" ) << DString( bufferIn ) << I_( "]" ) << bf::log::endl << bf::log::endlf;
      }

      xp::SaxStateManager saxStateManager;

      BFIPBlast::getInstance()->writeBuffer( I_( "XMLRequest" ), bufferIn );

      xp::ExecutionResult execResult;
      saxStateManager.parse( bufferIn, bufferOut, execResult );

      BFHRTimer tWrite;
      writeResponse( bufferOut, execResult );
      tWrite.stop();
      tTxn.stop();

      ls << I_( "Response write took " ) << tWrite.elapsed() << I_( "msecs." ) << bf::log::endlf;

      if( bTrace_ )
      {
         ls << bf::log::endl << I_( "response: [" ) << DString(bufferOut) << I_( "]" ) << bf::log::endl << bf::log::endlf;
      }

      // accumulate these transaction stats into the Server
      portal_->cumeTxnStats( tTxn.elapsed(), pTxnStats );
   } 
   else 
   {
      ls << I_( "No data read from socket." ) << bf::log::endlf;
   }
   ls << I_( "Transaction " ) << getJobId() << I_( " completed in " ) << tTxn.elapsed() << I_( "msecs." ) << bf::log::endlf;

}

