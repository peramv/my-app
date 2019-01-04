#include "stdafx.h"
#include ".\sonicmqjobqueue.hpp"
#include ".\sonicmqjob.hpp"
#include ".\sonicmqportal.hpp"

#include <bfutil\bfguard.hpp>

SonicMQJobQueue::SonicMQJobQueue( SonicMQPortal *portal ) 
: portal_( portal )
, _closedEvent( true )           //manual reset event, initially non-signaled
{
}

SonicMQJobQueue::~SonicMQJobQueue() {
}

bool SonicMQJobQueue::popJob( BFJob *&job, DWORD timeout /*= INFINITE*/ ) {

   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQJobQueue::popJob called" ) << bf::log::endl;

   job = NULL;

   // check close event --  and exit if closed
   if( isClosed() ) {
      ls << bf::log::information << I_( "SonicMQJobQueue::popJob - close detected." ) << bf::log::endl;
      portal_->disconnect();
      return false; 
   }

   while (true) {
      SonicMQJob *sonicJob = NULL;
      try {
         ls << bf::log::information << I_( "SonicMQJobQueue::popJob - creating job." ) << bf::log::endl;
         sonicJob = new SonicMQJob( portal_ );
         ls << bf::log::information << I_( "SonicMQJobQueue::popJob - job created." ) << bf::log::endl;

         try {
            ls << bf::log::information << I_( "SonicMQJobQueue::popJob -- waiting for message" ) << bf::log::endl;
            DWORD t0 = GetTickCount();
            while ( true ) {

               if( isClosed() ) {
				  // closed -- exit thread.
                  ls << bf::log::information << I_( "SonicMQJobQueue::popJob - close detected." ) << bf::log::endl;
				  delete sonicJob;
				  portal_->disconnect();
				  return false;
               }

               DWORD remTime = t0 + timeout - GetTickCount();
               if ( sonicJob->receive( remTime>5000 ? 5000 : (remTime>0 ? remTime : 0) ) ) {
                  DWORD recTime = GetTickCount() - t0; 
                  ls << bf::log::information << I_( "SonicMQJobQueue::popJob - message received in " ) << recTime << I_(" seconds.")<< bf::log::endl;
                  job = sonicJob;
                  return true;
               }

               if ( remTime <= 0 ) {
				  // timed-out -- exit thread.
                  ls << bf::log::information << I_( "SonicMQJobQueue::popJob - timed-out." ) << bf::log::endl;
				  delete sonicJob;
				  portal_->disconnect();
				  return false;
               }

			   if( (t0 - GetTickCount()) > 120000 )
			   {
				   ls << bf::log::information << I_( "SonicMQJobQueue::popJob - timed-out. will Retry" ) << bf::log::endl;
				   break;
			   }
            }
            
            
         } catch(ExceptionRef e) {
            ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- SonicMQ Receive message failed [") 
                                    << e->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
         } catch ( ... ) {
            ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- unknown error waiting for message" ) << bf::log::endl;
         }
      } catch(ExceptionRef e) {
         ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- SonicMQ error creating new job. [") 
                                 << e->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
      } catch ( ... ) {
         ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- unknown error creating new job." ) << bf::log::endl;
      }

      delete sonicJob;
      sonicJob = NULL;

      // there was an error try again.
      try {
         ls << bf::log::information << I_( "SonicMQJobQueue::popJob - reconnecting to SonicMQ." ) << bf::log::endl;
         portal_->reconnect();
      } catch(ExceptionRef e) {
         ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- SonicMQ error reconnecting to SonicMQ. [") 
                                 << e->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
         portal_->disconnect();
         return false;
      } catch ( ... ) {
         ls << bf::log::critical << I_( "SonicMQJobQueue::popJob -- unknown error reconnecting to SonicMQ." ) << bf::log::endl;
         portal_->disconnect();
         return false;
      }

   }

}

void SonicMQJobQueue::close() {
   BFGuard closeGuard( _closeCritSec ); // one closer at a time

   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQJobQueue::close called." ) << bf::log::endl;
   if( isClosed() ) {
      return; // already closed
   }

   ls << bf::log::information << I_( "SonicMQJobQueue::close -- signaling." ) << bf::log::endl;
   _closedEvent.set();

}

bool SonicMQJobQueue::isClosed() {
   return(_closedEvent.wait(0));
}


