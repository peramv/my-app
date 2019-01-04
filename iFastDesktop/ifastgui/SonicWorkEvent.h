#pragma once
#include "workevent.h"

class SonicWorkEventAgent;

class SonicWorkEvent : public WorkEvent, public BFThread
{
 public:
  SonicWorkEvent(MessageRef eventMsg, const Json::Value& root, TopicRef replyDest,
                 SonicWorkEventAgent* agent);
  SonicWorkEvent(const SonicWorkEvent& copy);
  ~SonicWorkEvent(void);

  virtual void startInProcess() override;
  virtual void replyUpdate(const std::pair<Json::Value, Json::Value>& data) override;
  virtual void replyReady() override;
  virtual void replyInProcess() override;
  virtual void replyDone() override;
  virtual void replyError(const DString& dstrError) override;
  virtual WorkEvent* clone(){ return new SonicWorkEvent(*this); }

  const TopicRef getReplyTopic() { return replyTopic_; }
 

 protected:
  virtual void run();

 private:
  Json::Value createReply(const char* const type);

  MessageRef eventMsg_;
  
  TopicRef replyTopic_;
  SonicWorkEventAgent* agent_;

  mutable BFSemaphore semInProcess_;
  mutable BFEvent evStopInProcess_;
  mutable BFCritSec csSendReply_;
};
