#include "stdafx.h"

#include "SonicMQJob.hpp"
#include "SonicMQPortal.hpp"

#include <bfutil\txnstats.hpp>
#include <bfutil\bfhrtimer.hpp>
#include <xparser\executionresult.hpp>

   
namespace {
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SonicMQJob" );
   const I_CHAR * const RUN = I_( "run" );
}

SonicMQJob::SonicMQJob( SonicMQPortal* portal ) 
: SrvJob( portal )
, portal_( portal )
, connection_( null )
, session_( null )
, receiver_( null )
, message_( null )
{
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- creating job" ) << bf::log::endl;

   // create and start connection
   try { 

      ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- creating/starting connection" ) << bf::log::endl;
      connection_ = portal->getConnection();

      ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- creating session" ) << bf::log::endl;
      session_ = connection_->createQueueSession(jtrue,Session_CLIENT_ACKNOWLEDGE); // transacted session

	  if( session_ == null )
	  {
		  ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- null session" ) << bf::log::endl;
	  }
	  else
	  {
		  ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- session created" ) << bf::log::endl;

		  ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- create receiver" ) << bf::log::endl;
		  receiver_ = session_->createReceiver( session_->createQueue( createString(portal_->getInQueue().c_str()) ) );
	  }

   } catch ( ... ) {
	  ls << bf::log::information << I_( "SonicMQJob::SonicMQJob -- failed creating job" ) << bf::log::endl;
      if ( session_ != null ) { try { session_->close(); } catch (...) {} }
//      if ( connection_ != null ) { try { connection_->close(); } catch (...) {} }
      throw;
   }
}

SonicMQJob::~SonicMQJob() {
   if ( session_ != null ) {
      session_->close();
   }
//   if ( connection_ != null ) {
//      connection_->close();
//   }
}

bool SonicMQJob::receive( DWORD timeout ) {

   bf::log::LogStream ls( bf::log::server );

   if ( message_ != null ) {
      ls << bf::log::information << I_( "SonicMQJob::receive -- message alerady received." ) << bf::log::endl;
      return true;
   }

   if ( timeout <= 0 ) {
      message_ = receiver_->receiveNoWait();
   } else {
      message_ = receiver_->receive(timeout);
   }
   
   if ( message_ == null ) {
      return false;
   } else {
      return true;
   }

}

void SonicMQJob::readRequest( DStringA &buffer ) {
   buffer = ""; //initialize to empty
   bf::log::LogStream ls( bf::log::server );
   try
   {
      try {
         ls << bf::log::information;
         ls << I_( "-------------------------------------------------------------" ) << bf::log::endl;
         ls << I_( "Processing SonicMQ Transaction " ) << getJobId() << bf::log::endl;
         ls << I_( "   MessageID:     " ) << SonicMQPortal::JMSStringToDString(message_->getJMSMessageID()) << bf::log::endl;
         ls << I_( "   CorrelationID: " ) << SonicMQPortal::JMSStringToDString(message_->getJMSCorrelationID()) << bf::log::endl;
//         ls << I_( "   Reply Dest:    " ) << SonicMQPortal::JMSStringToDString(message_->getJMSReplyTo()->toString()) << bf::log::endl;
         ls << I_( "-------------------------------------------------------------" ) << bf::log::endlf;
      } catch (...) {
         //logging failed -- not fatal
      }

      TextMessageRef textMessage = TextMessageRef::cast(message_);
      // Read a single String from the message and print it
      // to the standard output.

      StringRef string(textMessage->getText());
      if (string != null) {
         buffer = string->toAscii()->getValue();
      }
   }
   catch(ClassCastExceptionRef e)
   {
      // handle error
      ls << bf::log::critical << I_( "SonicMQJob::readRequest failed -- Unsupported message type received " ) << message_->getType() << bf::log::endlf;
   }
   catch(ExceptionRef e)
   {
      // handle error
      ls << bf::log::critical << I_( "SonicMQ::readRequest failed [") << e->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
      ls.flush();
   }
   catch(...)
   {
      // handle error
      ls << bf::log::critical << I_( "SonicMQ::readRequest failed" ) << bf::log::endl;
      ls.flush();
   }
}

bool SonicMQJob::resultsHaveCriticalErrors( const xp::ExecutionResult &result ) {
   if ( !result.isSuccessful() ) {
      if ( result.getCriticalErrorCount() > 0 ) {
         return true;
      }
      const xp::ExecutionResult::BatchResultList &brList = result.getBatchResults();
      for ( xp::ExecutionResult::BatchResultList::const_iterator bi = brList.begin(); bi != brList.end(); ++bi ) {
         const xp::BatchResult &br = (*bi);
         if ( !br.isSuccessful() ) {
            if ( br.getCriticalErrorCount() > 0 ) {
               return true;
            }
            const xp::BatchResult::ProcessResultList &prList = br.getProcessResults();
            for ( xp::BatchResult::ProcessResultList::const_iterator pi = prList.begin(); pi != prList.end(); ++pi ) {
               const xp::ProcessResult &pr = (*pi);
               if ( !pr.isSuccessful() ) {
                  if ( pr.getCriticalErrorCount() > 0 ) {
                     return true;
                  }
               }
            }
         }
      }
   }
   return false;
}

void SonicMQJob::writeResponse( const DStringA &buffer, const xp::ExecutionResult &result ) {

   try {

      if ( portal_->isCriticalErrorHandlingOn() && resultsHaveCriticalErrors( result ) ) {
         bf::log::LogStream ls( bf::log::server );
         ls << bf::log::information;
         try {
            ls << I_( "SonicMQ::writeResponse - response has critical errors." ) << bf::log::endl;
         } catch (...) {
            //logging failed -- not fatal
         }

         QueueRef queueSend = null;
         QueueSenderRef sender = null;

         ls << I_( "SonicMQJob::writeResponse() createQueue at " ) << __LINE__ << bf::log::endlf;
         queueSend = session_->createQueue( createString( portal_->getErrQueue().c_str() ) );

         ls << I_( "SonicMQJob::writeResponse() createSender at " ) << __LINE__ << bf::log::endlf;
         sender = session_->createSender(queueSend);

         // set the JMSReplyTo to the JMSDestination -- for now not used
         // message_->setJMSReplyTo( message_->getJMSDestination() );

         sender->send(message_, DeliveryMode_PERSISTENT, Message_DEFAULT_PRIORITY, 0L);
         session_->commit();

         try {
            ls << I_( "-------------------------------------------------------------" ) << bf::log::endl;
            ls << I_( "SonicMQ Request forwarded to error queue" ) << bf::log::endl;
            ls << I_( "   MessageID:     " ) << SonicMQPortal::JMSStringToDString(message_->getJMSMessageID()) << bf::log::endl;
            ls << I_( "   CorrelationID: " ) << SonicMQPortal::JMSStringToDString(message_->getJMSCorrelationID()) << bf::log::endl;
            ls << I_( "-------------------------------------------------------------" ) << bf::log::endlf;
            ls.flush();
         } catch (...) {
            //logging failed -- not fatal
         }

      } else {

         // static user property names
         static StringRef s_nmServiceName    = createString(L"ServiceName");
         static StringRef s_nmNetworkId      = createString(L"NetworkID");
         static StringRef s_nmProcessId      = createString(L"ProcessID");
         static StringRef s_nmActivityId     = createString(L"ActivityID");
         static StringRef s_nmProcessType    = createString(L"ProcessType");
         static StringRef s_nmActivityType   = createString(L"ActivityType");
         static StringRef s_nmMsgType        = createString(L"MsgType");
         static StringRef s_nmCompanyCode    = createString(L"CompanyCode");
         static StringRef s_nmDateStamp      = createString(L"DateStamp");
         static StringRef s_nmTimeStamp      = createString(L"TimeStamp");
         static StringRef s_nmActivityStatus = createString(L"ActivityStatus");

         static StringRef s_nmLookupActivityType = createString(L"LookupActivityType");
         static StringRef s_nmLookupMsgType      = createString(L"LookupMsgType");
         static StringRef s_nmLookupReplyTo      = createString(L"LookupReplyTo");

         static StringRef outpropActivityStatus = createString(L"S0010");
         static StringRef outpropServiceName = createString(L"AUDIT");

         bf::log::LogStream ls( bf::log::server );
         ls << bf::log::information;

         TextMessageRef outMsg = session_->createTextMessage(createString(buffer.c_str()));

         // pass through properties
         outMsg->setJMSCorrelationID( message_->getJMSCorrelationID() );
         outMsg->setStringProperty( s_nmNetworkId, message_->getStringProperty(s_nmNetworkId) );
         outMsg->setStringProperty( s_nmProcessId, message_->getStringProperty(s_nmProcessId) );
         outMsg->setStringProperty( s_nmCompanyCode, message_->getStringProperty(s_nmCompanyCode) );

         // fixed properties
         outMsg->setStringProperty( s_nmServiceName, outpropServiceName );
         outMsg->setStringProperty( s_nmActivityStatus, outpropActivityStatus );

         // timestamp properties

         // routing properties
         StringRef inpropActivityType = message_->getStringProperty(s_nmActivityType);
         if ( inpropActivityType != null ) {
            const SonicMQRouting *routing = portal_->getRouting( inpropActivityType->toWide()->getValue() );
            if ( routing != NULL ) {
               outMsg->setStringProperty( s_nmActivityType, createString(routing->outActivityType.c_str()) );
               outMsg->setStringProperty( s_nmMsgType, createString(routing->outMessageType.c_str()) );
               // set the replyto
               bf::log::LogStream ls( bf::log::server );
               ls << bf::log::information;
               ls << I_( "SonicMQJob::writeResponse() createQueue at " ) << __LINE__ << bf::log::endlf;
               QueueRef queueReplyTo = session_->createQueue (createString(routing->replyToQueue.c_str()));
               outMsg->setJMSReplyTo( queueReplyTo );
               // add lookup properties
               if ( routing->lookupReplyToQueue != NULL_STRING ) {
                  outMsg->setStringProperty( s_nmLookupActivityType, createString(routing->lookupActivityType.c_str()) );
                  outMsg->setStringProperty( s_nmLookupMsgType,      createString(routing->lookupMessageType.c_str()) );
                  outMsg->setStringProperty( s_nmLookupReplyTo,      createString(routing->lookupReplyToQueue.c_str()) );
               }
            }
         }

         QueueRef queueSend = null;
         QueueSenderRef sender = null;

         // use the JMSReplyTo property if set otherwise use the configured out queue
         queueSend = QueueRef::cast(message_->getJMSReplyTo());
         if ( queueSend == null ) {
            ls << I_( "SonicMQJob::writeResponse() createQueue at " ) << __LINE__ << bf::log::endlf;
            queueSend = session_->createQueue (createString(portal_->getOutQueue().c_str()));
         }

         ls << I_( "SonicMQJob::writeResponse() createSender at " ) << __LINE__ << bf::log::endlf;
         sender = session_->createSender(queueSend);

         // Send the message. Queues usually are used for PERSISTENT messages.
         sender->send(outMsg, DeliveryMode_PERSISTENT, Message_DEFAULT_PRIORITY, 0L);
         session_->commit();

         try {
            ls << I_( "-------------------------------------------------------------" ) << bf::log::endl;
            ls << I_( "SonicMQ Response sent" ) << bf::log::endl;
            ls << I_( "   MessageID:     " ) << SonicMQPortal::JMSStringToDString(outMsg->getJMSMessageID()) << bf::log::endl;
            ls << I_( "   CorrelationID: " ) << SonicMQPortal::JMSStringToDString(outMsg->getJMSCorrelationID()) << bf::log::endl;
            ls << I_( "-------------------------------------------------------------" ) << bf::log::endlf;
            ls.flush();
         } catch (...) {
            //logging failed -- not fatal
         }
      }
   } catch(ExceptionRef e) {
      // cannot send - do not ack - duplicates may occur on adds (i.e. trade may have been processed
      bf::log::LogStream ls( bf::log::server );

      session_->rollback();

      ls << bf::log::critical << I_( "SonicMQ::writeResponse failed [") 
                              << e->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
      ls << bf::log::critical << I_( "    -  message transaction rolled back!!" ) << bf::log::endl;
      ls.flush();
   }
   catch(...) 
   {
      // cannot send - do not ack - duplicates may occur on adds (i.e. trade may have been processed
      bf::log::LogStream ls( bf::log::server );

      session_->rollback();

      ls << bf::log::critical << I_( "SonicMQ::writeResponse failed -  message transaction rolled back!!" ) << bf::log::endl;
      ls.flush();
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/SonicMQJob.cpp-arc  $
// 
//    Rev 1.11   May 10 2006 12:23:54   fengyong
// Add more logs
// 
//    Rev 1.10   Mar 29 2006 16:41:06   smithdav
// Change Sonic connectgion logic to create a dedicated connection per thead, and attampt a re-connect if failures occur.
// 
//    Rev 1.9   Mar 16 2006 11:23:10   smithdav
// Scoped the SonicMQ locks larger  to take into account receives, sends and commits. They may not be thread safe and may be causing threads to block in these functions.
// 
//    Rev 1.8   Jul 20 2005 14:44:20   purdyech
// Logging improvements
// 
//    Rev 1.7   Apr 15 2005 15:21:06   smithdav
// Made Guard changes in session code.
// 
//    Rev 1.6   Apr 10 2005 16:07:40   smithdav
// Add configuration property to allow "critical error handling" in the SonicMQ portal to be turned off( on by default ).
// 
//    Rev 1.5   Mar 04 2005 14:49:56   smithdav
// Add additional logging.
// 
//    Rev 1.4   Feb 18 2005 13:29:02   smithdav
// Add support for routing transactions with critical errors to an "error queue"
// 
//    Rev 1.3   Feb 04 2005 21:01:00   smithdav
// Fix roolback bug and add rollback logging.
// 
//    Rev 1.2   Feb 04 2005 12:31:02   smithdav
// Add lookup properties to routings.
// 
//    Rev 1.1   Feb 03 2005 13:32:02   smithdav
// Add critical error rollback.
// 
//    Rev 1.0   Jan 27 2005 16:35:46   smithdav
// Initial revision.
 *
 *
 */