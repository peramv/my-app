#pragma once
#include "workeventagent.h"

#include <cms\ConnectionFactory.h>
#include <cms\MessageListener.h>
#include <cms\ExceptionListener.h>
#include <cms\Session.h>
#include <cms\Destination.h>
#include ".\workevent.h"

#include <boost\scoped_ptr.hpp>
#include <boost\shared_ptr.hpp>

class ActiveMQWorkEventAgent : public WorkEventAgent,
                            public BFThread,
                            cms::MessageListener,
                            cms::ExceptionListener
{
public:
  ActiveMQWorkEventAgent(const DString& dstrUserID, const DString& dstrTopic);
  ~ActiveMQWorkEventAgent(void);

  virtual void onMessage(const cms::Message* message) override;
  virtual void onException(const cms::CMSException& ex) override;

  virtual const Json::Value& getOutFields(const DSTCSecurity* pSecurity,
                                          const DString& companyid) override;

  void errorReply(const cms::Destination* replyTopic, const DString& dstrError, const cms::Message* origMsg);

  void send(const cms::Destination* replyTopic, Json::Value& jsonRoot, const cms::Message* origMsg);
  void send(const cms::Destination* topic, Json::Value& jsonRoot);
  void sendNewWork(Json::Value& jsonRoot);

  static const Json::Value callService(const DSTCSecurity* pSecurity, Json::Value &request, const DString& companyid);

 protected:
  virtual void run();

 private:
  void connect();
  void disconnect();

  boost::shared_ptr<WorkEvent> createWorkEvent(std::shared_ptr<cms::Message> message, std::shared_ptr<cms::Destination> replyTopic);

  std::shared_ptr<cms::Connection> connection_;
  std::unique_ptr<cms::Session> session_;
  std::unique_ptr<cms::MessageConsumer> subscriber_;

  DString workEventTopic_;
  DString workEventReplyTopic_;
  DString keepAliveTopic_;

  Json::Value outFields_;
  BFEvent shutdownEvent_;
};
