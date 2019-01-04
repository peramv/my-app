#pragma once

#include <srvbase\srvportal.hpp>
#include <bf\log\logstream.hpp>
#include <bfutil\bfthreadpool.hpp>
#include <bfutil\bfcritsec.hpp>

#include <map>

#include <java/lang/package.h>
#include <progress/message/jclient/package.h>

struct SonicMQRouting {
   SonicMQRouting( const DString inActType, 
                   const DString &outActType, 
                   const DString &outMsgType, 
                   const DString &replyTo ) 
   : inActivityType(inActType)
   , outActivityType(outActType)
   , replyToQueue(replyTo)
   , lookupActivityType(NULL_STRING)
   , lookupMessageType(NULL_STRING)
   , lookupReplyToQueue(NULL_STRING)
   {}

   SonicMQRouting( const DString inActType, 
                   const DString &outActType, 
                   const DString &outMsgType, 
                   const DString &replyTo,
                   const DString &luActType,
                   const DString &luMsgType,
                   const DString &luReplyTo ) 
   : inActivityType(inActType)
   , outActivityType(outActType)
   , outMessageType(outMsgType)
   , replyToQueue(replyTo)
   , lookupActivityType(luActType)
   , lookupMessageType(luMsgType)
   , lookupReplyToQueue(luReplyTo)
   {}

   const DString inActivityType;
   const DString outActivityType;
   const DString outMessageType;
   const DString replyToQueue;

   const DString lookupActivityType;
   const DString lookupMessageType;
   const DString lookupReplyToQueue;
};

class SonicMQConnection : public progress::message::jclient::ExceptionListener {
public:
   SonicMQConnection( progress::message::jclient::QueueConnectionFactoryRef connection, 
                      const DString userId, const DString password );
   ~SonicMQConnection();

   progress::message::jclient::QueueConnectionRef get() {
      return connection_;
   }

   virtual void onException( JMSExceptionRef exc );

private:
   BFCritSec lock_; 
   progress::message::jclient::QueueConnectionRef connection_;
};


class SonicMQPortal : public SrvPortal
{
public:
   static DString JMSStringToDString( java::lang::StringRef jmsString );

   SonicMQPortal( const DString &name, const DString &broker, 
                  const DString&inQueue, const DString &outQueue, const DString &errQueue,
                  const DString& userId, const DString& password,
                  long threadPoolSize, bool criticalErrorHandlingOn );

   virtual ~SonicMQPortal();

   virtual void close();

   virtual DString getDescription();
   virtual DStringA getDescriptionA();

   const DString &getBroker() const {
      return broker_;
   }

   const DString &getInQueue() const {
      return inQueue_;
   }

   const DString &getOutQueue() const {
      return outQueue_;
   }

   const DString &getErrQueue() const {
      return errQueue_;
   }

   bool isCriticalErrorHandlingOn() const {
      return criticalErrorHandlingOn_;
   }

   void addRouting( const SonicMQRouting &routing );
   const SonicMQRouting *getRouting( const DString& name ) const;

   void disconnect();
   progress::message::jclient::QueueConnectionRef reconnect();
   progress::message::jclient::QueueConnectionRef getConnection();

protected:
   virtual bool run( BFThreadPool *const threadPool );

private:
   const DString broker_;
   const DString inQueue_;
   const DString outQueue_;
   const DString errQueue_;
   const DString userId_; 
   const DString password_;
   const bool criticalErrorHandlingOn_;

   progress::message::jclient::QueueConnectionFactoryRef connFactory_;

   mutable BFEvent evShutdown_;

   typedef std::map<DString, SonicMQRouting> RoutingMap; 
   RoutingMap routings_;

   typedef std::map<DWORD, SonicMQConnection*> SonicMQConnectionMap;
   SonicMQConnectionMap _smqConnections;
   BFCritSec _smqConnectionsLock; 

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/SonicMQPortal.hpp-arc  $
//
//   Rev 1.7   Mar 29 2006 16:39:38   smithdav
//Change Sonic connectgion logic to create a dedicated connection per thead, and attampt a re-connect if failures occur.
//
//   Rev 1.6   Apr 15 2005 15:21:50   smithdav
//Made Guard changes in session code.
//
//   Rev 1.5   Apr 10 2005 16:07:34   smithdav
//Add configuration property to allow "critical error handling" in the SonicMQ portal to be turned off( on by default ).
//
//   Rev 1.4   Feb 18 2005 13:29:06   smithdav
//Add support for routing transactions with critical errors to an "error queue"
//
//   Rev 1.3   Feb 18 2005 11:37:46   smithdav
//Fix bug. Copy string parameters instead of storing references.
//
//   Rev 1.2   Feb 04 2005 21:02:24   smithdav
//Add support for configurable SonicMQ routings. Was hard coded.
//
//   Rev 1.1   Feb 04 2005 12:30:48   smithdav
//Add lookup properties to routings.
//
//   Rev 1.0   Jan 27 2005 16:35:56   smithdav
//Initial revision.
//
//   Rev 1.0   Sep 10 2004 17:11:18   SMITHDAV
//Initial revision.
 * 
 */