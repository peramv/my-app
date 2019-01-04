#include "stdafx.h"

#include "ActiveMQWorkEvent.h"

#include <json\config.h>
#include <json\json.h>

//#include <bfdata\bfdata.hpp>
//#include <bfdata\bfdatafielditer.hpp>
#include <bfutil\bfguard.hpp>
#include "ActiveMQWorkEventAgent.h"

ActiveMQWorkEvent::ActiveMQWorkEvent(std::shared_ptr<cms::Message> eventMsg, const Json::Value& eventRoot,
                               std::shared_ptr<cms::Destination> replyTopic, ActiveMQWorkEventAgent* agent)
    : BFThread(),
	  WorkEvent(eventRoot),
      eventMsg_(eventMsg),
      replyTopic_(replyTopic),
      agent_(agent),
      semInProcess_(1, 1),
      evStopInProcess_(),
      csSendReply_()
{
	
}

ActiveMQWorkEvent::ActiveMQWorkEvent(const ActiveMQWorkEvent& copy)
    : BFThread(),
	  WorkEvent(copy),
      eventMsg_(copy.eventMsg_),
      replyTopic_(copy.replyTopic_),
      agent_(copy.agent_),
      semInProcess_(1, 1),
      evStopInProcess_(),
      csSendReply_()
{
	
}

ActiveMQWorkEvent::~ActiveMQWorkEvent(void)
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  semInProcess_.wait(0);
}

void ActiveMQWorkEvent::replyError(const DString& dstrError)
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  agent_->errorReply(replyTopic_.get(), dstrError, eventMsg_.get());
}

void ActiveMQWorkEvent::startInProcess()
{
  if (semInProcess_.wait(0))
  {
    start();
  }
}

void ActiveMQWorkEvent::run()
{
  Json::Value replyRoot = createReply("in_process");
  do
  {
    BFGuard g(csSendReply_);
    agent_->send(replyTopic_.get(), replyRoot, eventMsg_.get());
  } while (!evStopInProcess_.wait(10000));
  semInProcess_.release(1);
}

void ActiveMQWorkEvent::replyUpdate(const std::pair<Json::Value, Json::Value>& data)
{
  BFGuard g(csSendReply_);
  Json::Value replyRoot = createReply("update");
  replyRoot["OutFields"] = data.first;
  replyRoot["Comments"] = data.second;
  agent_->send(replyTopic_.get(), replyRoot, eventMsg_.get());
}

void ActiveMQWorkEvent::replyDone()
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  agent_->send(replyTopic_.get(), createReply("done"), eventMsg_.get());
}

void ActiveMQWorkEvent::replyReady()
{
  BFGuard g(csSendReply_);
  agent_->send(replyTopic_.get(), createReply("ready"), eventMsg_.get());
}

void ActiveMQWorkEvent::replyInProcess()
{
  BFGuard g(csSendReply_);
  agent_->send(replyTopic_.get(), createReply("in_process"), eventMsg_.get());
}

Json::Value ActiveMQWorkEvent::createReply(const char* const type)
{
  Json::Value replyRoot;
  replyRoot["ReplyType"] = type;
  replyRoot["Opaque"] = getEventRoot()["Opaque"];
  return replyRoot;
}
