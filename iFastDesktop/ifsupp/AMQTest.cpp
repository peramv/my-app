#include "stdafx.h"

#include "AMQTest.h"

#include <cms/CMSException.h>
#include <decaf/net/URI.h>
#include <decaf/util/StringTokenizer.h>
#include <decaf/lang/String.h>
#include <bfutil\bfhrtimer.hpp>
#include <ifastdbrkr\ActiveMQConnectionFactory.hpp>

AMQTest::AMQTest(void)
    : MessageServiceTest(),
      connFactory_(nullptr),
      connection_(nullptr),
      session_(nullptr),
      singleSender_(nullptr),
      multiSender_(nullptr),
      authSender_(nullptr),
      awdSender_(nullptr),
      receiver_(nullptr),
      tempQueue_(nullptr)
{
}

AMQTest::~AMQTest(void)
{
  if (session_ != nullptr)
  {
    try
    {
      session_->close();
    }
    catch (...)
    {
    }
    session_ = nullptr;
  }
  if (connection_ != nullptr)
  {
    try
    {
      connection_->close();
    }
    catch (...)
    {
    }
    connection_ = nullptr;
  }
}

bool AMQTest::doSingleQTest(DString& message)
{
  bool bRc = true;
  try
  {
    singleSender_ = session_->createProducer(session_->createQueue(DStringA(getSingleQ()).c_str()));
  }
  catch (cms::CMSException e)
  {
    message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::doMultiQTest(DString& message)
{
  bool bRc = true;
  try
  {
    multiSender_ = session_->createProducer(session_->createQueue(DStringA(getMultiQ()).c_str()));
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::doAuthQTest(DString& message)
{
  bool bRc = true;
  try
  {
    authSender_ = session_->createProducer(session_->createQueue(DStringA(getAuthQ()).c_str()));
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::doAwdQTest(DString& message)
{
  bool bRc = true;
  try
  {
    awdSender_ = session_->createProducer(session_->createQueue(DStringA(getAwdQ()).c_str()));
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::doHeartbeatTest(DString& message) { return (true); }

void AMQTest::parseBrokerURL(DString& hostPrimary, int& portPrimary, DString& hostBackup,
                             int& portBackup)
{
  hostPrimary = I_("");
  portPrimary = 0;
  hostBackup = I_("");
  portBackup = 0;

  decaf::lang::String brokerURL(DStringA(getBrokerURL()).c_str());

  if (brokerURL.startsWith("failover:(")) {
	  brokerURL = brokerURL.substring(10, brokerURL.findFirstOf(")"));
  }

  decaf::util::StringTokenizer tokenizer(brokerURL.c_str(), ",");
  if (!tokenizer.hasMoreTokens()) return;

  decaf::net::URI primary(tokenizer.nextToken());
  hostPrimary = DString(DStringA(primary.getHost().c_str()));
  portPrimary = primary.getPort();

  if (!tokenizer.hasMoreTokens()) return;

  decaf::net::URI backup(tokenizer.nextToken());
  hostBackup = DString(DStringA(backup.getHost().c_str()));
  portBackup = backup.getPort();
}

bool AMQTest::createConnectionFactory(DString& message)
{
  bool bRc = true;
  try
  {
	  connFactory_ = ActiveMQConnectionFactory::createCMSConnectionFactory(getBrokerURL().asA());
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::createConnection(DString& message)
{
  bool bRc = true;
  try
  {
    connection_ = connFactory_->createConnection(DStringA(getSMQUser()).c_str(),
                                                 DStringA(getSMQPassword()).c_str());
    connection_->start();
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}

bool AMQTest::createSession(DString& message)
{
  bool bRc = true;
  try
  {
    session_ = connection_->createSession(cms::Session::AUTO_ACKNOWLEDGE);
  }
  catch (cms::CMSException e)
  {
    message = message = e.getMessage();
    bRc = false;
  }
  return (bRc);
}
