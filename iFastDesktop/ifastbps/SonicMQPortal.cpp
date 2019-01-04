#include "stdafx.h"

#include "SonicMQPortal.hpp"
#include "SonicMQJobQueue.hpp"
#include "SonicMQJob.hpp"

#include <bfutil\BFException.hpp>
#include <bfutil\Console.hpp>
#include <bfutil\bfguard.hpp>

#include <sstream>
#include <iomanip>

#include <bf/log/log.hpp>

using namespace progress::message::jclient;

SonicMQConnection::SonicMQConnection( progress::message::jclient::QueueConnectionFactoryRef connFactory, 
                                      const DString userId, const DString password ) {

   BFGuard guard( lock_ );
   connection_ = connFactory->createQueueConnection( createString(userId.c_str()), 
                                                                        createString(password.c_str()) );
   connection_->setExceptionListenerObj(this);
   connection_->start();
}

SonicMQConnection::~SonicMQConnection() {
   BFGuard guard( lock_ );
   try { connection_->close(); } catch (...) {}
}

void SonicMQConnection::onException( JMSExceptionRef exc ) {
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::critical << I_( "SonicMQPortal: SonicMQ Connection exception [") 
                           << exc->getMessage()->toWide()->getValue() << I_("]" ) << bf::log::endl;
   throw exc;
}

// Disable warning about using "this" in member-initialization list.
#pragma warning( push )
#pragma warning( disable : 4355 )
SonicMQPortal::SonicMQPortal( const DString &name, const DString &broker, 
                              const DString &inQueue, const DString &outQueue, const DString &errQueue, 
                              const DString& userId, const DString& password,
                              long threadPoolSize, bool criticalErrorHandlingOn ) 
: SrvPortal( name, new SonicMQJobQueue( this ), threadPoolSize )
, broker_( broker )
, inQueue_( inQueue )
, outQueue_( outQueue )
, errQueue_( errQueue )
, userId_( userId )
, password_( password )
, criticalErrorHandlingOn_( criticalErrorHandlingOn )
, connFactory_( null )
, evShutdown_( true, false )
{
   connFactory_ = createQueueConnectionFactory( createString(broker_.c_str()) );
}
#pragma warning( pop )


SonicMQPortal::~SonicMQPortal() 
{
}

bool SonicMQPortal::run( BFThreadPool *const threadPool ) {
   if ( evShutdown_.wait( 2000 ) ) {
      return false;
   }
   return true;
}

void SonicMQPortal::close()
{
   evShutdown_.set();
   SrvPortal::close();
   bf::log::theLog << bf::log::information << I_( "SonicMQPortal exited..." ) << bf::log::endlf;
}

DString SonicMQPortal::JMSStringToDString( StringRef jmsString ) {
   if ( jmsString == null ) {
      return I_("<null>");
   }

   try {
#ifdef DST_UNICODE
      return jmsString->toWide()->getValue();
#else
      return jmsString->toAscii()->getValue();
#endif
   } catch( ... ) {
      return I_("<error>");
   }

}

#define DESC_SZ 128
DString SonicMQPortal::getDescription() {
   I_CHAR desc[DESC_SZ];
   i_sprintf(desc, DESC_SZ, I_("SonicMQ - broker: %s"), broker_.c_str());
   desc[DESC_SZ-1]='\0';
   return desc;
}

DStringA SonicMQPortal::getDescriptionA() {
   char desc[DESC_SZ];
   _snprintf(desc, DESC_SZ, "SonicMQ - broker: %s", broker_.asA().c_str());
   desc[DESC_SZ-1]='\0';
   return desc;
}

void SonicMQPortal::addRouting( const SonicMQRouting &routing ) {
   std::pair<RoutingMap::iterator, bool> result = routings_.insert(RoutingMap::value_type(routing.inActivityType, routing));
   if ( !result.second ) {
      // do something or just forget ???
   }
}

const SonicMQRouting *SonicMQPortal::getRouting( const DString& name )const
{
   RoutingMap::const_iterator iter = routings_.find( name );
   if ( iter != routings_.end() ) {
      return &(*iter).second;
   }
   return NULL;
}

QueueConnectionRef SonicMQPortal::reconnect() {
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQPortal::reconnect called" ) << bf::log::endl;

   BFGuard guard( _smqConnectionsLock );
   DWORD thId = GetCurrentThreadId();
   SonicMQConnectionMap::iterator iter = _smqConnections.find( thId );
   if( iter != _smqConnections.end() ) {
      delete (*iter).second;
      _smqConnections.erase(iter);
   }

   SonicMQConnection* connection = new SonicMQConnection(connFactory_, userId_, password_);
   _smqConnections.insert(SonicMQConnectionMap::value_type(thId, connection));
   return connection->get();

}

void SonicMQPortal::disconnect() {
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQPortal::disconnect called" ) << bf::log::endl;

   BFGuard guard( _smqConnectionsLock );
   DWORD thId = GetCurrentThreadId();
   SonicMQConnectionMap::iterator iter = _smqConnections.find( thId );
   if( iter != _smqConnections.end() ) {
      delete (*iter).second;
      _smqConnections.erase(iter);
   }

}

QueueConnectionRef SonicMQPortal::getConnection() {
   bf::log::LogStream ls( bf::log::server );
   ls << bf::log::information << I_( "SonicMQPortal::getConnection called" ) << bf::log::endl;

   BFGuard guard( _smqConnectionsLock );
   DWORD thId = GetCurrentThreadId();
   SonicMQConnectionMap::const_iterator iter = _smqConnections.find( thId );
   if ( iter == _smqConnections.end() ) {
      SonicMQConnection* connection = new SonicMQConnection(connFactory_, userId_, password_);
      _smqConnections.insert(SonicMQConnectionMap::value_type(thId, connection));
      return connection->get();
   }

   return (*iter).second->get();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/SonicMQPortal.cpp-arc  $
// 
//    Rev 1.6   Oct 05 2009 07:51:06   purdyech
// Get rid of warning message
// 
//    Rev 1.5   Mar 29 2006 16:41:04   smithdav
// Change Sonic connectgion logic to create a dedicated connection per thead, and attampt a re-connect if failures occur.
// 
//    Rev 1.4   Apr 10 2005 16:07:36   smithdav
// Add configuration property to allow "critical error handling" in the SonicMQ portal to be turned off( on by default ).
// 
//    Rev 1.3   Feb 18 2005 13:29:04   smithdav
// Add support for routing transactions with critical errors to an "error queue"
// 
//    Rev 1.2   Feb 04 2005 21:02:26   smithdav
// Add support for configurable SonicMQ routings. Was hard coded.
// 
//    Rev 1.1   Feb 04 2005 12:31:00   smithdav
// Add lookup properties to routings.
// 
//    Rev 1.0   Jan 27 2005 16:35:54   smithdav
// Initial revision.
// 
*/