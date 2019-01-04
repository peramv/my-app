#include "stdafx.h"

#include "SonicWorkEvent.h"

#include <json\config.h>
#include <json\json.h>

#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafielditer.hpp>
#include <bfutil\bfguard.hpp>
#include "SonicWorkEventAgent.h"

SonicWorkEvent::SonicWorkEvent(MessageRef eventMsg, const Json::Value& eventRoot,
                               TopicRef replyTopic, SonicWorkEventAgent* agent)
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

SonicWorkEvent::SonicWorkEvent(const SonicWorkEvent& copy)
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

SonicWorkEvent::~SonicWorkEvent(void)
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  semInProcess_.wait(0);
}

void SonicWorkEvent::replyError(const DString& dstrError)
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  agent_->errorReply(replyTopic_, dstrError, eventMsg_);
}

void SonicWorkEvent::startInProcess()
{
  if (semInProcess_.wait(0))
  {
    start();
  }
}

void SonicWorkEvent::run()
{
  Json::Value replyRoot = createReply("in_process");
  do
  {
    BFGuard g(csSendReply_);
    agent_->send(replyTopic_, replyRoot, eventMsg_);
  } while (!evStopInProcess_.wait(10000));
  semInProcess_.release(1);
}

void SonicWorkEvent::replyUpdate(const std::pair<Json::Value, Json::Value>& data)
{
  BFGuard g(csSendReply_);
  Json::Value replyRoot = createReply("update");
  replyRoot["OutFields"] = data.first;
  replyRoot["Comments"] = data.second;
  agent_->send(replyTopic_, replyRoot, eventMsg_);
}

void SonicWorkEvent::replyDone()
{
  BFGuard g(csSendReply_);
  evStopInProcess_.set();
  agent_->send(replyTopic_, createReply("done"), eventMsg_);
}

void SonicWorkEvent::replyReady()
{
  BFGuard g(csSendReply_);
  agent_->send(replyTopic_, createReply("ready"), eventMsg_);
}

void SonicWorkEvent::replyInProcess()
{
  BFGuard g(csSendReply_);
  agent_->send(replyTopic_, createReply("in_process"), eventMsg_);
}

Json::Value SonicWorkEvent::createReply(const char* const type)
{
  Json::Value replyRoot;
  replyRoot["ReplyType"] = type;
  replyRoot["Opaque"] = getEventRoot()["Opaque"];
  return replyRoot;
}
