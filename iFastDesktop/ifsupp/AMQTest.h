#pragma once
#include <MessageServiceTest.h>
#include <cms/Connection.h>
#include <cms/ConnectionFactory.h>
#include <cms/MessageProducer.h>
#include <cms/Session.h>
#include <cms/TemporaryQueue.h>
#include <dstring.hpp>

class AMQTest : public MessageServiceTest
{
 public:
  AMQTest(void);
  ~AMQTest(void);

 public:
  virtual bool doSingleQTest(DString& message) override;
  virtual bool doMultiQTest(DString& message) override;
  virtual bool doAuthQTest(DString& message) override;
  virtual bool doAwdQTest(DString& message) override;
  virtual bool doHeartbeatTest(DString& message) override;

 private:
  void parseBrokerURL(DString& hostPrimary, int& portPrimary, DString& hostBackup, int& portBackup);
  virtual bool createConnectionFactory(DString& message) override;
  virtual bool createConnection(DString& message) override ;
  virtual bool createSession(DString& message) override;

 private:
  cms::ConnectionFactory* connFactory_;
  cms::Connection* connection_;
  cms::Session* session_;
  cms::MessageProducer* singleSender_;
  cms::MessageProducer* multiSender_;
  cms::MessageProducer* authSender_;
  cms::MessageProducer* awdSender_;
  cms::MessageConsumer* receiver_;
  cms::TemporaryQueue* tempQueue_;
};
