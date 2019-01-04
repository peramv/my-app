#pragma once
#include <dstring.hpp>

class MessageServiceTest
{
 public:
  MessageServiceTest()
      : dstrBrokerURL_(I_("")),
        dstrSingleQ_(I_("")),
        dstrMultiQ_(I_("")),
        dstrAuthQ_(I_("")),
        dstrAwdQ_(I_("")),
        dstrSMQUser_(I_("")),
        dstrSMQPassword_(I_("")),
        dstrUserNS_(I_("")),
        waitTimeout_(0)
  {
  }

  virtual bool doTelnetTest(DString& message);
  virtual bool doConnectionTest(DString& message);
  virtual bool doSingleQTest(DString& message) = 0;
  virtual bool doMultiQTest(DString& message) = 0;
  virtual bool doAuthQTest(DString& message) = 0;
  virtual bool doAwdQTest(DString& message) = 0;
  virtual bool doHeartbeatTest(DString& message) = 0;
  virtual long checkPort(const DString& strHost, unsigned short nPort, DString& strError);
private: 
	  virtual bool createConnectionFactory(DString& message) = 0;
  virtual bool createConnection(DString& message) = 0 ;
  virtual bool createSession(DString& message) = 0;
 public:
  const DString& getBrokerURL() { return dstrBrokerURL_; }
  MessageServiceTest& setBrokerURL(const DString& v)
  {
    dstrBrokerURL_ = v;
    return *this;
  }
  const DString& getSingleQ() { return dstrSingleQ_; }
  MessageServiceTest& setSingleQ(const DString& v)
  {
    dstrSingleQ_ = v;
    return *this;
  }
  const DString& getMultiQ() { return dstrMultiQ_; }
  MessageServiceTest& setMultiQ(const DString& v)
  {
    dstrMultiQ_ = v;
    return *this;
  }
  const DString& getAuthQ() { return dstrAuthQ_; }
  MessageServiceTest& setAuthQ(const DString& v)
  {
    dstrAuthQ_ = v;
    return *this;
  }
  const DString& getAwdQ() { return dstrAwdQ_; }
  MessageServiceTest& setAwdQ(const DString& v)
  {
    dstrAwdQ_ = v;
    return *this;
  }
  const DString& getSMQUser() { return dstrSMQUser_; }
  MessageServiceTest& setSMQUser(const DString& v)
  {
    dstrSMQUser_ = v;
    return *this;
  }
  const DString& getSMQPassword() { return dstrSMQPassword_; }
  MessageServiceTest& setSMQPassword(const DString& v)
  {
    dstrSMQPassword_ = v;
    return *this;
  }
  const DString& getUserNS() { return dstrUserNS_; }
  MessageServiceTest& setUserNS(const DString& v)
  {
    dstrUserNS_ = v;
    return *this;
  }
  int getWaitTimeout() { return waitTimeout_; }
  MessageServiceTest& setWaitTimeout(int v)
  {
    waitTimeout_ = v;
    return *this;
  }
protected:
	virtual void parseBrokerURL(DString& hostPrimary, int& portPrimary, DString& hostBackup, int& portBackup) = 0;

 private:
  DString dstrBrokerURL_;
  DString dstrSingleQ_;
  DString dstrMultiQ_;
  DString dstrAuthQ_;
  DString dstrAwdQ_;
  DString dstrSMQUser_;
  DString dstrSMQPassword_;
  DString dstrUserNS_;
  int waitTimeout_;
};
