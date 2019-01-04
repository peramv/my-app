#pragma once
#include "workevent.h"

class ActiveMQWorkEventAgent;

namespace cms
{
class Message;
class Topic;
class Destination;
}

class ActiveMQWorkEvent : public WorkEvent, public BFThread
{
 public:
  ActiveMQWorkEvent(std::shared_ptr<cms::Message> eventMsg, const Json::Value& root,
                    std::shared_ptr<cms::Destination> replyDest, ActiveMQWorkEventAgent* agent);
  ActiveMQWorkEvent(const ActiveMQWorkEvent& copy);
  ~ActiveMQWorkEvent(void);

  virtual void startInProcess() override;
  virtual void replyUpdate(const std::pair<Json::Value, Json::Value>& data) override;
  virtual void replyReady() override;
  virtual void replyInProcess() override;
  virtual void replyDone() override;
  virtual void replyError(const DString& dstrError) override;
  virtual WorkEvent* clone() { return new ActiveMQWorkEvent(*this); }

  const cms::Destination* getReplyTopic() { return replyTopic_.get(); }

 protected:
  virtual void run();

 private:
  Json::Value createReply(const char* const type);

  std::shared_ptr<cms::Message> eventMsg_;
  std::shared_ptr<cms::Destination> replyTopic_;

  ActiveMQWorkEventAgent* agent_;

  mutable BFSemaphore semInProcess_;
  mutable BFEvent evStopInProcess_;
  mutable BFCritSec csSendReply_;
};
