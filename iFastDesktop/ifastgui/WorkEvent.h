#pragma once

#include <ifastgui\resource.h>
#include <json\config.h>
#include <json\json.h>
#include <progress/message/jclient/package.h>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfsemaphore.hpp>
#include <bfutil\bfthread.hpp>

#include<map>

class WorkEventAgent;
class BFData;

class WorkEvent
{
public:
	 WorkEvent(const Json::Value& eventRoot) {eventRoot_ = eventRoot;}
	 WorkEvent(const WorkEvent& event){eventRoot_ = event.eventRoot_;}
  virtual void startInProcess() = 0;
  virtual void replyUpdate(const std::pair<Json::Value, Json::Value>& data) = 0;
  virtual void replyReady() = 0;
  virtual void replyInProcess() = 0;
  virtual void replyDone() = 0;
  virtual void replyError(const DString& dstrError) = 0;
  virtual WorkEvent* clone() = 0;


  const Json::Value& getEventRoot() { return eventRoot_; }

protected:
	void setEventRoot(const Json::Value& eventRoot) { eventRoot_ = eventRoot; }

private:
   Json::Value eventRoot_;
};
