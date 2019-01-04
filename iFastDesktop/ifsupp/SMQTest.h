#pragma once
#include "MessageServiceTest.h"
#include <dstring.hpp>
#include <progress/message/jclient/package.h>

class SMQTest : public MessageServiceTest
{
public:
   SMQTest(void);
   ~SMQTest(void);

public:
   virtual bool doSingleQTest( DString& message ) override;
   virtual bool doMultiQTest( DString& message ) override;
   virtual bool doAuthQTest( DString& message ) override;
   virtual bool doAwdQTest( DString& message ) override;
   virtual bool doHeartbeatTest( DString& message ) override;

private:
   void parseBrokerURL(
      DString& hostPrimary,
      int& portPrimary,
      DString& hostBackup,
      int& portBackup);
  virtual bool createConnectionFactory(DString& message) override;
  virtual bool createConnection(DString& message) override ;
  virtual bool createSession(DString& message) override;

private:
   progress::message::jclient::QueueConnectionFactoryRef connFactory_;
   progress::message::jclient::QueueConnectionRef connection_;
   progress::message::jclient::QueueSessionRef session_;
   progress::message::jclient::QueueSenderRef singleSender_;
   progress::message::jclient::QueueSenderRef multiSender_;
   progress::message::jclient::QueueSenderRef authSender_;
   progress::message::jclient::QueueSenderRef awdSender_;
   progress::message::jclient::QueueReceiverRef receiver_;
   progress::message::jclient::TemporaryQueueRef tempQueue_;

};
