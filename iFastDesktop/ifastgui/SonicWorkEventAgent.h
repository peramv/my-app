#pragma once
#include "workeventagent.h"

#include <ifastgui\resource.h>
#include <progress/message/jclient/package.h>
#include ".\workevent.h"

#include <boost\scoped_ptr.hpp>
#include <boost\shared_ptr.hpp>

class SonicWorkEventAgent : public WorkEventAgent,
                            public BFThread,
                            progress::message::jclient::MessageListener,
                            progress::message::jclient::ExceptionListener
{
public:
  SonicWorkEventAgent(const DString& dstrUserID, const DString& dstrTopic);
  ~SonicWorkEventAgent(void);

  virtual void onMessage(progress::message::jclient::MessageRef msg) override;
  virtual void onException(progress::message::jclient::JMSExceptionRef ex) override;

  virtual const Json::Value& getOutFields(const DSTCSecurity* pSecurity,
                                          const DString& companyid) override;

  void errorReply(TopicRef replyTopic, const DString& dstrError, MessageRef origMsg);

  void send(TopicRef replyTopic, Json::Value& jsonRoot, MessageRef origMsg);
  void send(TopicRef topic, Json::Value& jsonRoot);
  void sendNewWork(Json::Value& jsonRoot);

  static const Json::Value callService(const DSTCSecurity* pSecurity, Json::Value &request, const DString& companyid);
 protected:
  virtual void run();

 private:
  void connect();
  void disconnect();

  boost::shared_ptr<WorkEvent> createWorkEvent(MessageRef message, TopicRef replyTopic);

  progress::message::jclient::TopicConnectionFactoryRef connFactory_;
  progress::message::jclient::TopicConnectionRef connection_;
  progress::message::jclient::TopicSessionRef session_;
  progress::message::jclient::TopicSubscriberRef subscriber_;
  progress::message::jclient::TopicSubscriberRef publisher_;

  DString workEventTopic_;
  DString workEventReplyTopic_;
  DString keepAliveTopic_;

  Json::Value outFields_;
  BFEvent shutdownEvent_;
};
