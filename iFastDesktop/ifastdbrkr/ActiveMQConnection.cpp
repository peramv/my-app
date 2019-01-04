//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  ActiveMQConnection.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  April 2000
//
// ----------------------------------------------------------
#include "ActiveMQConnection.hpp"

#include <srcprag.h>

#include <bf/log/log.hpp>
#include <bfdata/bfdata.hpp>
#include <bfdbrkr/bfviewtimelog.hpp>
#include <bfutil/bfhrtimer.hpp>
#include <conditionmanager.hpp>
//#include "base64.h"
#include <configmanager.hpp>
#include <ifastdbrkr/SonicFrameworkError.hpp>
#include <ifastdbrkr/dstcsecurity.hpp>
#include <ifastdbrkr/ifastdbrkr.hpp>
#include <map>
#include <sstream>
#include <vector>
#include <activemq/core/ActiveMQConnectionFactory.h>

namespace ifds
{
const DString& getAppVersion();
}

#include <assert.h>

namespace
{
extern const I_CHAR* CLASSNAME = I_("ActiveMQConnection");
}

static const char* getDelimiter()
{
  static unsigned char szDelim[2] = {0xfe, 0x00};
  
  return ((const char*)szDelim);
}

static std::string UTF8toISO8859_1(const char* in)
{
  std::string out;
  if (in == nullptr) return out;

  unsigned int codepoint;
  while (*in != 0)
  {
    unsigned char ch = static_cast<unsigned char>(*in);
    if (ch <= 0x7f)
      codepoint = ch;
    else if (ch <= 0xbf)
      codepoint = (codepoint << 6) | (ch & 0x3f);
    else if (ch <= 0xdf)
      codepoint = ch & 0x1f;
    else if (ch <= 0xef)
      codepoint = ch & 0x0f;
    else
      codepoint = ch & 0x07;
    ++in;
    if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
    {
      if (codepoint <= 255)
      {
        out.append(1, static_cast<char>(codepoint));
      }
      else
      {
        // do whatever you want for out-of-bounds characters
      }
    }
  }
  return out;
}

namespace CND
{
extern const I_CHAR* IFASTDBRKR_CONDITION;
//   extern const long ERR_SMQ_SOCKET_INITIALIZATION_FAILED;
extern const long ERR_SMQ_CONNECT_FAILED;
extern const long ERR_SMQ_MESSAGE_SEND_FAILED;
extern const long ERR_SMQ_MESSAGE_RECEIVE_FAILED;
extern const long ERR_SMQ_UNKNOWN_MESSAGE_TYPE;
extern const long ERR_SMQ_SONICMQ_ERROR;
extern const long ERR_INVALID_PERSIST_REQUEST;
extern const long ERR_VIEW_TIMEOUT;
}

static DString LogCMSException(unsigned long l, cms::CMSException& e)
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  DString msg = e.getMessage();
  ls << I_("CMSException detected at line ") << l << I_(".  Msg=") << msg.c_str() << bf::log::endlf;
  return (msg);
}

static std::string getLocalHost()
{
  char szHostName[256];
  memset(szHostName, 0, 256);
  gethostname(szHostName, 256);
  return (szHostName);
}

static std::string getLocalIP()
{
  WSADATA wsaData;
  struct hostent* pHostEnt;
  struct sockaddr_in tmpSockAddr;  // placeholder for the ip address

  // Not needed if it is already taken care by some other part of the application
  WSAStartup(MAKEWORD(2, 0), &wsaData);

  //   char hostname[25];
  //   strcpy(hostname,"Test Computer Name")
  // This will retrieve the ip details and put it into pHostEnt structure
  char szHostName[256];
  gethostname(szHostName, sizeof(szHostName) / sizeof(szHostName[0]));
  pHostEnt = gethostbyname(szHostName);

  if (nullptr == pHostEnt)
  {
    return ("");
  }

  memcpy(&tmpSockAddr.sin_addr, pHostEnt->h_addr, pHostEnt->h_length);

  char szIP[17];
  strcpy(szIP, inet_ntoa(tmpSockAddr.sin_addr));
  return (szIP);
}

static DStringA getNextPersistHandle()
{
  static BFCritSec cs;
  BFGuard g(cs);
  static long s_PersistRequestId = 0;
  char szBuf[16];
  sprintf(szBuf, "%05d0000000000", ++s_PersistRequestId);
  return (DStringA(szBuf));
}

// static std::string s_JMS_ActiveMQMQ_preserveUndelivered = "JMS_ActiveMQMQ_preserveUndelivered";
// static std::string s_JMS_ActiveMQMQ_notifyUndelivered   = "JMS_ActiveMQMQ_notifyUndelivered";
static const auto s_IFAST_ORIGIN_USER = "IFAST_ORIGIN_USER";
static std::string s_IFAST_ORIGIN_COMPUTER = "IFAST_ORIGIN_COMPUTER";
static std::string s_IFAST_ORIGIN_IP = "IFAST_ORIGIN_IP";
static std::string s_IFAST_SLOT_NAME = "IFAST_SLOT_NAME";
static std::string s_IFAST_ZTS_REPLYTO = "IFAST_ZTS_REPLYTO";
static std::string s_IFAST_SESSION_ID = "IFAST_SESSION_TOKEN";
static std::string s_IFAST_COMPANY_ID = "IFAST_ZTS_COMPANY_ID";
static std::string s_IFAST_USER_ID = "IFAST_ZTS_USER_ID";
static std::string s_IFAST_VIEW_NAME = "IFAST_ZTS_VIEW_NAME";
static std::string s_IFAST_VERSION = "IFAST_VERSION";
static std::string s_IFAST_TRACK_ID = "IFAST_TRACK_ID";
static std::string s_IFAST_NUM_BATCH = "IFAST_NUM_BATCH";
// static std::string s_IFAST_SESSION_TOKEN             = "IFAST_SESSION_TOKEN";
static std::string s_IFAST_ORIGIN_APPLICATION = "IFAST_ORIGIN_APPLICATION";
static std::string s_IFAST_DESKTOP_CONFIG_PATH = "IFAST_DESKTOP_CONFIG_PATH";

static std::string s_OriginUser = getenv("USERNAME");
static std::string s_OriginIP = getLocalIP();
static std::string s_OriginComputer = getLocalHost();
static std::string s_OriginApplication = "DTOP";

static DStringA s_OEInvocationTime = "IFAST_METRIC_OE_INVOCATION";
static DStringA s_ViewTime = "IFAST_ZTS_VIEWTIME";
static DStringA s_PreViewTime = "IFAST_ZTS_PREVIEWTIME";
static DStringA s_PostViewTime = "IFAST_ZTS_POSTVIEWTIME";
static DStringA s_ESB_In = "IFAST_TS_ENTRY";
static DStringA s_ESB_Out = "IFAST_TS_EXIT";

namespace ifds
{
extern CLASS_IMPORT const BFTextFieldId SessionId;
extern CLASS_IMPORT const BFTextFieldId User_Id;
extern CLASS_IMPORT const BFTextFieldId LanguageCode;
extern CLASS_IMPORT const BFTextFieldId CompanyId;
}

class ConnectionLogInfo
{
 public:
  ConnectionLogInfo(const DStringA& viewName)
      : viewName_(viewName),
        msgId_(""),
        sendTime_(0),
        receiveTime_(0),
        unitOfWorkTime_(0),
        networkTime_(0),
        oeInvocationTime_(0),
        preViewTime_(0),
        viewTime_(0),
        postViewTime_(0)
  {
    GetSystemTime(&timeStamp_);
  }

  void setMsgId(const DStringA& msgId) { msgId_ = msgId; }
  const DStringA& getMsgid() const { return msgId_; }

  void setSendTime(unsigned long v) { sendTime_ = v; }
  unsigned long getSendTime() const { return sendTime_; }

  void setReceiveTime(unsigned long v) { receiveTime_ = v; }
  unsigned long getReceiveTime() const { return receiveTime_; }

  void setUnitOfWorkTime(unsigned long v) { unitOfWorkTime_ = v; }
  unsigned long getUnitOfWorkTime() const { return unitOfWorkTime_; }

  void setNetworkTime(unsigned long v) { networkTime_ = v; }
  unsigned long getNetworkTime() const { return networkTime_; }

  unsigned long getOEInvocationTime() const { return oeInvocationTime_; }

  void setOEInvocationTime(unsigned long v) { oeInvocationTime_ = v; }

  void setPreViewTime(unsigned long v) { preViewTime_ = v; }
  unsigned long getPreViewTime() const { return preViewTime_; }

  void setViewTime(unsigned long v) { viewTime_ = v; }
  unsigned long getViewTime() const { return viewTime_; }

  void setPostViewTime(unsigned long v) { postViewTime_ = v; }
  unsigned long getPostViewTime() const { return postViewTime_; }

  void log()
  {
    BFViewTimeLog::getInstance().log(viewName_, msgId_, sendTime_, receiveTime_, unitOfWorkTime_,
                                     networkTime_, oeInvocationTime_, viewTime_, preViewTime_,
                                     postViewTime_);
  }

  void log(const char* pszNote)
  {
    BFViewTimeLog::getInstance().log(viewName_, msgId_, sendTime_, receiveTime_, unitOfWorkTime_,
                                     networkTime_, oeInvocationTime_, viewTime_, preViewTime_,
                                     postViewTime_, pszNote);
  }

 private:
  const DStringA viewName_;
  DStringA msgId_;
  unsigned long sendTime_;
  unsigned long receiveTime_;
  unsigned long unitOfWorkTime_;
  unsigned long networkTime_;
  unsigned long oeInvocationTime_;
  unsigned long viewTime_;
  unsigned long preViewTime_;
  unsigned long postViewTime_;
  SYSTEMTIME timeStamp_;  //
};

static long getNextCorrID()
{
  static BFCritSec s_CorrID;
  static long nextCorrID = 0;
  BFGuard g(s_CorrID);
  return (++nextCorrID);
}

typedef std::vector<DStringA> REQUEST_VECTOR;
typedef REQUEST_VECTOR::iterator REQUEST_VECTOR_ITER;
typedef std::map<DStringA, REQUEST_VECTOR*> MAP_PERSIST_REQUESTS;
typedef MAP_PERSIST_REQUESTS::iterator MAP_PERSIST_REQUESTS_ITER;

static MAP_PERSIST_REQUESTS s_mapPersistentRequests;

static void deletePersistentRequests(const DStringA& key)
{
  MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find(key);
  if (it != s_mapPersistentRequests.end())
  {
    REQUEST_VECTOR* p = (*it).second;
    delete p;
    s_mapPersistentRequests.erase(it);
  }
}

typedef std::set<ActiveMQConnection*> CONNECTION_SET;
typedef CONNECTION_SET::iterator CONNECTION_SET_ITER;
static CONNECTION_SET s_setConnections;
static BFCritSec s_csSet;

ActiveMQConnection::DETAILS_VECTOR ActiveMQConnection::getDetails()
{
  DETAILS_VECTOR v;
  CONNECTION_SET_ITER i;
  for (i = s_setConnections.begin(); i != s_setConnections.end(); ++i)
  {
    ActiveMQConnection* p = *i;
    ActiveMQConnection::Details s;
    s.p_ = p;
    s.cUses_ = p->cUses_;
    s.iTimeout_ = p->iTimeout_;
	s.iTimeToLive_ = p->iTimeToLive_;
    s.cRecycles_ = p->cRecycles_;
    cms::TemporaryQueue* t = p->tempQueue_.get();
    s.tQueue_ = DStringA(t->getQueueName());
    v.push_back(s);
  }

  return v;
}

// Keep a simple map of the existing connections

static void addConnection(ActiveMQConnection* p)
{
  BFGuard g(s_csSet);
  s_setConnections.insert(p);
}

static void removeConnection(ActiveMQConnection* p)
{
  CONNECTION_SET_ITER i = s_setConnections.find(p);
  if (i != s_setConnections.end())
  {
    s_setConnections.erase(p);
  }
}

int ActiveMQConnection::s_deliveryMode_ = cms::DeliveryMode::NON_PERSISTENT;

static BFCritSec s_csDeliveryMode;
int ActiveMQConnection::getDefaultDeliveryMode()
{
  BFGuard g(s_csDeliveryMode);
  return (s_deliveryMode_);
}

int ActiveMQConnection::setDefaultDeliveryMode(int newValue)
{
  BFGuard g(s_csDeliveryMode);
  int oldValue = s_deliveryMode_;
  s_deliveryMode_ = newValue;
  return (oldValue);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ActiveMQConnection::ActiveMQConnection(const DStringA& hostId, const DStringA& connectionName,
                                       std::shared_ptr<cms::ConnectionFactory> connFactory,
                                       const DStringA& singleQueue, const DStringA& multiQueue,
                                       const DStringA& ldapQueue, const DStringA& awdQueue,
                                       int cMaxUses, int iTimeout, int iTimeToLive, const DString& dstrCswAcl)
    : idHost_(hostId),
      connFactory_(connFactory),
      singleConnection_(nullptr),
      singleQueue_(singleQueue),
      multiQueue_(multiQueue),
      ldapQueue_(ldapQueue),
      awdQueue_(awdQueue),
      nameConnection_(connectionName),
      description_(hostId + ":" + connectionName),
      bRecycleRequired_(false),
      cMaxUses_(cMaxUses),
      cUses_(0),
      cRecycles_(0),
      iTimeout_(0 == iTimeout ? 60 : iTimeout),
      iTimeToLive_(iTimeToLive),
      connection_(nullptr),
      session_(nullptr),
      singleSender_(nullptr),
      multiSender_(nullptr),
      ldapSender_(nullptr),
      awdSender_(nullptr),
      receiver_(nullptr),
      tempQueue_(nullptr),
      dstrCswAcl_(dstrCswAcl){TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING)}

ActiveMQConnection::ActiveMQConnection(const DStringA& hostId, const DStringA& connectionName,
                                       std::shared_ptr<cms::Connection> singleConnection,
                                       const DStringA& singleQueue, const DStringA& multiQueue,
                                       const DStringA& ldapQueue, const DStringA& awdQueue,
                                       int cMaxUses, int iTimeout, int iTimeToLive, const DString& dstrCswAcl)
    : idHost_(hostId),
      connFactory_(nullptr),
      singleConnection_(singleConnection),
      singleQueue_(singleQueue),
      multiQueue_(multiQueue),
      ldapQueue_(ldapQueue),
      awdQueue_(awdQueue),
      nameConnection_(connectionName),
      description_(hostId + ":" + connectionName),
      bRecycleRequired_(false),
      cMaxUses_(cMaxUses),
      cUses_(0),
      cRecycles_(0),
      iTimeout_(0 == iTimeout ? 60 : iTimeout),
      iTimeToLive_(iTimeToLive),
      connection_(nullptr),
      session_(nullptr),
      singleSender_(nullptr),
      multiSender_(nullptr),
      ldapSender_(nullptr),
      awdSender_(nullptr),
      receiver_(nullptr),
      tempQueue_(nullptr),
      dstrCswAcl_(dstrCswAcl){TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING)}

ActiveMQConnection::~ActiveMQConnection()
{
  removeConnection(this);
  try
  {
    disconnect();
  }
  catch (...)
  {
  }
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void ActiveMQConnection::connect()
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  BFHRTimer tConnect;

  try
  {
    try
    {
      if (connFactory_ != nullptr)
      {
        connection_.reset(connFactory_->createConnection());
        connection_->start();
        session_.reset(connection_->createSession(cms::Session::AUTO_ACKNOWLEDGE));
      }
      else
      {
        session_.reset(singleConnection_->createSession(cms::Session::AUTO_ACKNOWLEDGE));
      }
      singleSender_.reset(session_->createProducer(session_->createQueue(singleQueue_.c_str())));
      multiSender_.reset();
      ldapSender_.reset();
      awdSender_.reset();
      tempQueue_.reset(session_->createTemporaryQueue());
      receiver_.reset(session_->createConsumer(tempQueue_.get()));
    }
    catch (ConditionException)
    {
      throw;
    }
    catch (cms::CMSException e)
    {
      DString idi;
      addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
      THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("connect"),
                        CND::ERR_SMQ_SONICMQ_ERROR, idi);
    }
    catch (...)
    {
      THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("connect"),
                     CND::ERR_SMQ_MESSAGE_SEND_FAILED);
    }
  }
  catch (...)
  {
    ls << bf::log::information << I_("ActiveMQConnection::connect -- failed creating job")
       << bf::log::endl;
    if (tempQueue_ != nullptr)
    {
      try
      {
        tempQueue_->destroy();
      }
      catch (...)
      {
      }
	  tempQueue_.reset();
    }
    if (session_ != nullptr)
    {
      try
      {
        session_->close();
      }
      catch (...)
      {
      }
      session_.reset();
    }
    if (connFactory_ != nullptr && connection_ != nullptr)
    {
      try
      {
        connection_->close();
      }
      catch (...)
      {
      }
	  connection_.reset();
    }
    THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("connect"),
                   CND::ERR_SMQ_CONNECT_FAILED);
  }

  cUses_ = 0;
}

//******************************************************************************
void ActiveMQConnection::disconnect()
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  BFHRTimer tClose;

  if (tempQueue_ != nullptr)
  {
    try
    {
      tempQueue_->destroy();
    }
    catch (...)
    {
    }
    tempQueue_.reset();
  }
  if (session_ != nullptr)
  {
    try
    {
      session_->close();
    }
    catch (...)
    {
    }
    session_.reset();
  }
  if (connFactory_ != nullptr)
  {
    if (connection_ != nullptr)
    {
      try
      {
        connection_->close();
      }
      catch (...)
      {
      }
      connection_.reset();
    }
  }

  // free the response buffer
  freeResponse();

  cUses_ = -1;
}

bool ActiveMQConnection::recycle()
{
  try
  {
    bf::log::LogStream ls(bf::log::databroker);
    ls << bf::log::information;

    ++cRecycles_;
    disconnect();
    connect();
    bRecycleRequired_ = false;
  }
  catch (ConditionException&)
  {
  }
  return (1 == (session_ != nullptr));
}

const DStringA NullPersistHandle("000000000000000");

void ActiveMQConnection::createResponse(const DStringA& viewName, const DStringA& persistHandle)
{
  // B0007300073000020000x000000000000001FY
  // ^    ^    ^    ^    ^    ^    ^    ^
  dstrResponse_ = "B";
  dstrResponse_ += viewName.substr(7);
  dstrResponse_ += viewName.substr(7);
  dstrResponse_ += "00002";
  dstrResponse_ += persistHandle;
  dstrResponse_ += "00001";

  dstrResponse_ += getDelimiter();

  dstrResponse_ += "FY";
}

void ActiveMQConnection::putRequestLDAP(const DStringA& request, bool bCanRecycle,
                                        DSTCSecurity* pDSTCSecurity)
{
  // does this need to be recycled?
  if (-1 != cMaxUses_ && ++cUses_ > cMaxUses_)
  {
    recycle();
  }
  try
  {
    if (ldapSender_ == nullptr)
    {
      ldapSender_.reset(session_->createProducer(session_->createQueue(ldapQueue_.c_str())));
    }
  }
  catch (ConditionException)
  {
    throw;
  }
  catch (cms::CMSException e)
  {
    setRecycleRequired();
    DString idi;
    addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
    THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestLDAP"),
                      CND::ERR_SMQ_SONICMQ_ERROR, idi);
  }
  catch (...)
  {
    THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestLDAP"),
                   CND::ERR_SMQ_MESSAGE_SEND_FAILED);
  }
  putRequest(ldapSender_.get(), request, bCanRecycle, nullptr, pDSTCSecurity);
}

void ActiveMQConnection::putRequestAWD(const DStringA& request, bool bCanRecycle,
                                       const DString& companyId, DSTCSecurity* pDSTCSecurity)
{
  if (session_ == nullptr)
  {
    connect();
    addConnection(this);
  }

  // does this need to be recycled?
  if (-1 != cMaxUses_ && ++cUses_ > cMaxUses_)
  {
    recycle();
  }
  try
  {
    if (awdSender_ == nullptr)
    {
      awdSender_.reset( session_->createProducer(session_->createQueue((awdQueue_.c_str()))) );
    }
  }
  catch (ConditionException)
  {
    throw;
  }
  catch (cms::CMSException e)
  {
    setRecycleRequired();
    DString idi;
    addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
    THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestAWD"),
                      CND::ERR_SMQ_SONICMQ_ERROR, idi);
  }
  catch (...)
  {
    THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequestAWD"),
                   CND::ERR_SMQ_MESSAGE_SEND_FAILED);
  }
  putRequest(awdSender_.get(), request, bCanRecycle, companyId, pDSTCSecurity);
}

void ActiveMQConnection::putRequest(cms::MessageProducer* sender, const DStringA& request,
                                    bool bCanRecycle, const DString& companyId,
                                    DSTCSecurity* pDSTCSecurity)
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  ls << I_("ActiveMQConnection::putRequest  Request to send LDAP/AWD") << bf::log::endlf;
  bf::log::LogStream lsTrace(bf::log::databroker);
  lsTrace << bf::log::ltrace;

  freeResponse();
  dstrResponse_ = "";

  cms::TextMessage* reqMessage;
  try
  {
    reqMessage = session_->createTextMessage();
  }
  catch (ConditionException)
  {
    throw;
  }
  catch (cms::CMSException e)
  {
    setRecycleRequired();
    DString idi;
    addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
    THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                      CND::ERR_SMQ_SONICMQ_ERROR, idi);
  }
  catch (...)
  {
    THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                   CND::ERR_SMQ_MESSAGE_SEND_FAILED);
  }

  // Logging out the content of the messages would violate compliance rules.
  //   CP 20101203
  // lsTrace << DString(request) << bf::log::endlf;

  reqMessage->setText(request.c_str());
  //   reqMessage->setBooleanProperty( s_JMS_ActiveMQMQ_preserveUndelivered, jfalse);
  //   reqMessage->setBooleanProperty( s_JMS_ActiveMQMQ_notifyUndelivered, jfalse);
  reqMessage->setStringProperty(s_IFAST_ZTS_REPLYTO, tempQueue_->getQueueName());
  reqMessage->setStringProperty(s_IFAST_ORIGIN_USER, s_OriginUser);
  reqMessage->setStringProperty(s_IFAST_ORIGIN_COMPUTER, s_OriginComputer);
  reqMessage->setStringProperty(s_IFAST_ORIGIN_IP, s_OriginIP);
  reqMessage->setStringProperty(s_IFAST_VERSION, ifds::getAppVersion().asA().c_str());
  reqMessage->setStringProperty(s_IFAST_ORIGIN_APPLICATION, s_OriginApplication);
 
  reqMessage->setStringProperty(s_IFAST_DESKTOP_CONFIG_PATH, 
	                            GetConfigValueAsString( I_("MFDSTC"), 
								                        I_("SiteXML" ), 
														I_("file" )).asA().c_str());

  if (companyId != NULL_STRING)
  {
    reqMessage->setStringProperty(s_IFAST_SLOT_NAME, companyId.asA().c_str());
    reqMessage->setStringProperty(s_IFAST_COMPANY_ID, companyId.asA().c_str());
  }

  if (nullptr != pDSTCSecurity)
  {
    DString sessionId = I_("");
    sessionId = pDSTCSecurity->getSessionId();
    sessionId.stripTrailing();
    reqMessage->setStringProperty(s_IFAST_SESSION_ID, sessionId.asA().c_str());
  }

  cms::MessageConsumer* receiver = nullptr;
  try
  {
    std::ostringstream oss;
    oss << std::hex << getNextCorrID();
    std::string corrID = oss.str();
    reqMessage->setCMSReplyTo(tempQueue_.get());

    reqMessage->setCMSCorrelationID(corrID);

    BFHRTimer tSend, tUOW;
    sender->send(reqMessage, getDefaultDeliveryMode(), 4, iTimeToLive_ * 1000);
    ++cUses_;

    DStringA msgId = reqMessage->getCMSMessageID();
    DString dstrMsgId = msgId;
    //      cli.setMsgId( dstrMsgId );
    // cli.setSendTime( tSend.elapsed() );
    ls << I_("Message ") << dstrMsgId << I_(" sent for view LDAP/AWD.") << bf::log::endlf;

    BFHRTimer tCreateRecv;
    lsTrace << I_("Receiver created in ") << tCreateRecv.elapsed() << I_(" ms.") << bf::log::endl;

    BFHRTimer tRecv;
    try
    {
      lsTrace << I_("ActiveMQConnection::putRequest().  About to receive for ") << dstrMsgId
              << bf::log::endlf;
      tRecv.reset();
      cms::Message* respMessage = nullptr;
//      unsigned long timeout = iTimeout_ * 1000;
      while (1)
      {
        respMessage =
            (iTimeout_ == 0L) ? receiver_->receive() : receiver_->receive(iTimeout_ * 1000);
        if (respMessage != nullptr)
        {
          std::string respCorrID = respMessage->getCMSCorrelationID();
          if (respCorrID != corrID)
          {
            continue;
          }
          // reset SessionID from IFAST_SESSION_ID property
          if (respMessage->propertyExists(s_IFAST_SESSION_ID))
          {
            DString sessionId = respMessage->getStringProperty(s_IFAST_SESSION_ID);
            ls << I_("New Session ID: ") << sessionId << bf::log::endlf;
            pDSTCSecurity->setSessionId(sessionId);
          }
        }
        break;
      }
      lsTrace << I_("ActiveMQConnection::putRequest().  Received ") << dstrMsgId << bf::log::endlf;
      cms::TextMessage* textMsg = dynamic_cast<cms::TextMessage*>(respMessage);
      if (textMsg != nullptr)
      {
        std::string rStr = textMsg->getText();
        if (rStr.length() == 0)
        {
          // It's XML ... it's an error!
          //                  ls << I_("TextMessage ") << dstrTrackId << I_(" [") << aStr->length()
          //                  << I_("] ") << DString(DStringA(rStr.c_str())) << bf::log::endlf;
          SonicFrameworkError sfwe(rStr, getDelimiter());
          dstrResponse_ = sfwe.getErrorMessage();
          dstrResponse_ += getDelimiter();
          dstrResponse_ += "F";
          //                  dstrResponse_ += DStringA(dstrTrackId);
        }
        else
        {
          std::string rStrDecoded = rStr;
          // Logging out the content of the messages would violate compliance rules.
          //   CP 20101203
          // lsTrace << I_("TextMessage ") << I_(" [") << rStrDecoded.length() << I_("] ") <<
          // DString(DStringA(rStrDecoded.c_str())) << bf::log::endlf;
          lsTrace << I_("TextMessage ") << I_(" [") << rStrDecoded.length() << I_("] ")
                  << bf::log::endlf;
          dstrResponse_ = rStrDecoded;
        }
      }
    }
    catch (ConditionException)
    {
      // cli.log("ConditionException");
      throw;
    }
    catch (cms::CMSException e)
    {
      setRecycleRequired();
      DString idi;
      addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
      THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                        CND::ERR_SMQ_SONICMQ_ERROR, idi);
    }
    catch (...)
    {
      THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                     CND::ERR_SMQ_MESSAGE_SEND_FAILED);
    }
  }
  catch (ConditionException)
  {
    throw;
  }
  catch (cms::CMSException e)
  {
    setRecycleRequired();
    DString idi;
    addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
    THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                      CND::ERR_SMQ_SONICMQ_ERROR, idi);
  }
  catch (...)
  {
    THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                   CND::ERR_SMQ_MESSAGE_SEND_FAILED);
  }
}

//******************************************************************************
void ActiveMQConnection::putRequest(const DStringA& oViewName, const DStringA& request,
                                    bool bCanRecycle, const BFData* pQuery, BFSecurity* pSecurity)
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  ls << I_("ActiveMQConnection::putRequest  Request to send ") << DString(oViewName)
     << bf::log::endlf;
  bf::log::LogStream lsTrace(bf::log::databroker);
  //   lsTrace << bf::log::ltrace;

  DStringA viewName(oViewName);
  DSTCSecurity* pDSTCSecurity = nullptr;
  if (nullptr != pSecurity)
  {
    try
    {
      pDSTCSecurity = dynamic_cast<DSTCSecurity*>(pSecurity);
    }
    catch (const std::bad_cast& e)
    {
      ls << I_("Security object is not DSTCSecurity: ") << DString(DStringA(e.what()))
         << bf::log::endl;
    }
  }

  if (session_ == nullptr)
  {
    connect();
    addConnection(this);
  }

  if (viewName == "LDAP")
  {
    putRequestLDAP(request, bCanRecycle, pDSTCSecurity);
    return;
  }

  if (viewName == "AWD")
  {
    putRequestAWD(request, bCanRecycle, NULL_STRING, pDSTCSecurity);
    return;
  }

  int retryCount = 0;
  bool retry = false;
  do
  {
    retry = false;
    cms::MessageProducer* pSender = singleSender_.get();

    if (viewName == "CFXTRAN00073")
    {
      DStringA persistRequest;
      DStringA persistHandle = getNextPersistHandle();
      REQUEST_VECTOR* pRV = nullptr;
      pRV = new REQUEST_VECTOR;
      s_mapPersistentRequests[persistHandle] = pRV;
      persistRequest = request.substr(0, 27);
      persistRequest += persistHandle;
      persistRequest += request.substr(42);
      pRV->push_back(persistRequest);
      createResponse(viewName, persistHandle);
      return;
    }
    DStringA persistHandle = "";
    persistHandle = request.substr(27, 15);
    if (persistHandle != NullPersistHandle)
    {
      REQUEST_VECTOR* pRV = nullptr;
      MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find(persistHandle);
      if (it == s_mapPersistentRequests.end())
      {
        THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                       CND::ERR_INVALID_PERSIST_REQUEST);
      }
      else
      {
        pRV = (*it).second;
      }
      pRV->push_back(request);
      if (viewName != "CFXTRAN00074" && viewName != "CFXTRAN10074")
      {
        // if not commit or rollback then create a response and return
        createResponse(viewName, persistHandle);
        ++cUses_;
        return;
      }
    }

    ConnectionLogInfo cli(viewName);

    // does this need to be recycled?
    if (-1 != cMaxUses_ && ++cUses_ > cMaxUses_)
    {
      recycle();
    }
    freeResponse();
    dstrResponse_ = "";

    cms::TextMessage* reqMessage;
    try
    {
      reqMessage = session_->createTextMessage();
    }
    catch (ConditionException)
    {
      throw;
    }
    catch (cms::CMSException e)
    {
      setRecycleRequired();
      DString idi;
      addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
      THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                        CND::ERR_SMQ_SONICMQ_ERROR, idi);
    }
    catch (...)
    {
      THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                     CND::ERR_SMQ_MESSAGE_SEND_FAILED);
    }
    if (viewName != "CFXTRAN00074" && viewName != "CFXTRAN10074")
    {
      DStringA reqLog = request;
      if (viewName == "CFLOGON00001")
      {
        // don't log password for Logon View.  Password is field 2.
        // Find delim character
        char chDelim = reqLog.at(48);
        size_t begin = 50;
        begin = reqLog.find_first_of(chDelim, begin);
        if (std::string::npos != begin)
        {
          begin += 2;  // go past delimiter and unknown flag
          size_t end = reqLog.find_first_of(chDelim, begin);
          reqLog.replace(begin, end - begin, "**********");
        }
      }
      else if (viewName == "CFXTRAN00039")
      {
        // must replace fields 4 and 5 with stars
        char chDelim = reqLog.at(48);
        size_t begin = 0;
        int iField = 1;
        for (int iField = 1; iField < 6 && std::string::npos != begin; ++iField)
        {
          begin = reqLog.find_first_of(chDelim, ++begin);
          if (std::string::npos != begin)
          {
            if (4 == iField || 5 == iField)
            {
              begin += 2;  // go past delimiter and unknown flag
              size_t end = reqLog.find_first_of(chDelim, begin);
              reqLog.replace(begin, end - begin, "**********");
            }
          }
        }
      }
      // Logging out the content of the messages would violate compliance rules.
      //   CP 20101203
      // lsTrace << DString(reqLog) << bf::log::endlf;
      reqMessage->setText(request.c_str());
    }
    else
    {
      if (viewName == "CFXTRAN10074")
      {
        // rollback!
        deletePersistentRequests(persistHandle);
        createResponse("CFXTRAN00074", persistHandle);
        ls << I_("Rollback for ") << DString(persistHandle) << bf::log::endlf;
        ++cUses_;
        return;
      }
      // must be a commit!
      std::stringstream s;
      s << "<?xml version=\"1.0\"?>"
        << "<SuperView xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
        << "<Nasu>";
      MAP_PERSIST_REQUESTS_ITER it = s_mapPersistentRequests.find(persistHandle);
      if (it != s_mapPersistentRequests.end())
      {
        REQUEST_VECTOR* p = (*it).second;
        int cSeq = 1;
        for (REQUEST_VECTOR_ITER vit = p->begin(); vit != p->end(); ++vit, ++cSeq)
        {
          const DStringA& r = *vit;

          // Logging out the content of the messages would violate compliance rules.
          //   CP 20101203
          // lsTrace << DString(r) << bf::log::endlf;
          std::string str = r.c_str();
          // XML escape str
          size_t begin = 0;
          while (std::string::npos != (begin = str.find_first_of("&", begin)))
          {
            str.replace(begin++, 1, "&amp;");
          }
          begin = 0;
          while (std::string::npos != (begin = str.find_first_of("<", begin)))
          {
            str.replace(begin++, 1, "&lt;");
          }
          begin = 0;
          while (std::string::npos != (begin = str.find_first_of(">", begin)))
          {
            str.replace(begin++, 1, "&gt;");
          }
          s << "<Views>";
          s << "<Seq>" << cSeq << "</Seq>";
          s << "<RawData>" << str << "</RawData>";
          s << "</Views>";
        }
      }
      s << "</Nasu>"
        << "</SuperView>";
      long len = s.str().length();
      const std::string& myStr = s.str();
      const char* pszReq = myStr.c_str();
      DString dx = DStringA(pszReq);
      lsTrace << I_("[") << len << I_(" bytes] ") << dx << bf::log::endlf;
      reqMessage->setText(pszReq);

      if (multiSender_ == nullptr)
      {
        multiSender_.reset(session_->createProducer(session_->createQueue(multiQueue_.c_str())));
      }
      pSender = multiSender_.get();
      deletePersistentRequests(persistHandle);
    }

    //   reqMessage->setBooleanProperty( s_JMS_ActiveMQMQ_preserveUndelivered, jfalse);
    //   reqMessage->setBooleanProperty( s_JMS_ActiveMQMQ_notifyUndelivered, jfalse);
    reqMessage->setStringProperty(s_IFAST_ZTS_REPLYTO, tempQueue_->getQueueName());
    reqMessage->setStringProperty(s_IFAST_ORIGIN_USER, s_OriginUser);
    reqMessage->setStringProperty(s_IFAST_ORIGIN_COMPUTER, s_OriginComputer);
    reqMessage->setStringProperty(s_IFAST_ORIGIN_IP, s_OriginIP);
    reqMessage->setStringProperty(s_IFAST_VERSION, ifds::getAppVersion().asA().c_str());
    reqMessage->setStringProperty(s_IFAST_VIEW_NAME, viewName.c_str());
    reqMessage->setStringProperty(s_IFAST_ORIGIN_APPLICATION, s_OriginApplication);

    DStringA strBatch = ifastdbrkr::getBatchSize(viewName);
    if (strBatch.size() > 0)
    {
      reqMessage->setStringProperty(s_IFAST_NUM_BATCH, strBatch.c_str());
    }

    DString companyId = dstrCswAcl_;
    if (viewName != "CFLOGON00001" && viewName != "CFLOGOFF00002" && viewName != "CFXTRAN00039")
    {
      if (pQuery->exists(ifds::CompanyId))
      {
        companyId = pQuery->getElementValue(ifds::CompanyId);
        companyId.stripTrailing();
      }
    }
    reqMessage->setStringProperty(s_IFAST_SLOT_NAME, companyId.asA().c_str());
    reqMessage->setStringProperty(s_IFAST_COMPANY_ID, companyId.asA().c_str());
    DString sessionId = I_("");
    if (nullptr != pDSTCSecurity)
    {
      sessionId = pDSTCSecurity->getSessionId();
      sessionId.stripTrailing();
    }
    reqMessage->setStringProperty(s_IFAST_SESSION_ID, sessionId.asA().c_str());
    //   reqMessage->setStringProperty(s_IFAST_SESSION_TOKEN, createString(sessionId.c_str()));

    DString userId;
    if (pQuery->exists(ifds::User_Id))
    {
      userId = pQuery->getElementValue(ifds::User_Id);
      userId.stripTrailing();
    }
    reqMessage->setStringProperty(s_IFAST_USER_ID, userId.asA().c_str());
    cms::MessageConsumer* receiver = nullptr;

    try
    {
      std::ostringstream oss;
      oss << std::hex << getNextCorrID();
      std::string corrID = oss.str();

	  reqMessage->setCMSReplyTo(tempQueue_.get());

      reqMessage->setCMSCorrelationID(corrID);

      BFHRTimer tSend, tUOW;
      pSender->send(reqMessage, getDefaultDeliveryMode(), 4, iTimeToLive_ * 1000);
      ++cUses_;

      DString dstrMsgId = reqMessage->getCMSMessageID();
      cli.setMsgId(dstrMsgId);
      cli.setSendTime(tSend.elapsed());
      ls << I_("Message ") << dstrMsgId << I_(" sent for view ") << viewName << I_(".")
         << bf::log::endlf;

      BFHRTimer tCreateRecv;
      lsTrace << I_("Receiver created in ") << tCreateRecv.elapsed() << I_(" ms.") << bf::log::endl;

      BFHRTimer tRecv;
      try
      {
        lsTrace << I_("ActiveMQConnection::putRequest().  About to receive for ") << dstrMsgId
                << bf::log::endlf;
        tRecv.reset();
        cms::Message* respMessage = nullptr;
//        unsigned long timeout = iTimeout_ * 1000;
        while (1)
        {
          respMessage =
              (iTimeout_ == 0L) ? receiver_->receive() : receiver_->receive(iTimeout_ * 1000);
          if (respMessage != nullptr)
          {
            std::string respCorrID = respMessage->getCMSCorrelationID();
            if (respCorrID != corrID)
            {
              continue;
            }
            if (respMessage->propertyExists(s_IFAST_SESSION_ID))
            {
              DString sessionId = respMessage->getStringProperty(s_IFAST_SESSION_ID);
              ls << I_("New Session ID: ") << sessionId << bf::log::endlf;
              if (nullptr != pDSTCSecurity)
              {
                pDSTCSecurity->setSessionId(sessionId);
              }
            }
          }
          break;
        }
        lsTrace << I_("ActiveMQConnection::putRequest().  Received ") << dstrMsgId
                << bf::log::endlf;
        if (respMessage != nullptr)
        {
          DString dstrTrackId;
          tRecv.stop();
          tUOW.stop();
          cli.setReceiveTime(tRecv.elapsed());
          cli.setUnitOfWorkTime(tUOW.elapsed());

          lsTrace << I_("ActiveMQConnection::putRequest, UOW for ") << dstrMsgId << I_(" was ")
                  << tUOW.elapsed() << I_("ms.") << bf::log::endlf;

          if (respMessage->propertyExists(s_OEInvocationTime.c_str()))
          {
            cli.setOEInvocationTime(respMessage->getLongProperty(s_OEInvocationTime.c_str()) /
                                    1000000);
          }
          // determine value of "VIEWTIME" parameter
          if (respMessage->propertyExists(s_ViewTime.c_str()))
          {
            cli.setViewTime(respMessage->getIntProperty(s_ViewTime.c_str()));
          }
          if (respMessage->propertyExists(s_PreViewTime.c_str()))
          {
            cli.setPreViewTime(respMessage->getIntProperty(s_PreViewTime.c_str()));
          }
          if (respMessage->propertyExists(s_PostViewTime.c_str()))
          {
            cli.setPostViewTime(respMessage->getIntProperty(s_PostViewTime.c_str()));
          }
          if (respMessage->propertyExists(s_ESB_In.c_str()) &&
              respMessage->propertyExists(s_ESB_Out.c_str()))
          {
            long esb_in_ms = static_cast<long>(respMessage->getLongProperty(s_ESB_In.c_str()));
            long esb_out_ms = static_cast<long>(respMessage->getLongProperty(s_ESB_Out.c_str()));
            cli.setNetworkTime(esb_out_ms - esb_in_ms);
          }

          if (respMessage->propertyExists(s_IFAST_TRACK_ID))
          {
            dstrTrackId = respMessage->getStringProperty(s_IFAST_TRACK_ID);
          }

          cms::BytesMessage* bytesMsg = dynamic_cast<cms::BytesMessage*>(respMessage);
          if (bytesMsg != nullptr)
          {
            unsigned char* msgBytes = bytesMsg->getBodyBytes();
            std::string str(msgBytes, msgBytes + sizeof msgBytes / sizeof msgBytes[0]);
            ;
            delete[] msgBytes;
            // Logging out the content of the messages would violate compliance rules.
            //   CP 20101203
            // lsTrace << I_("BytesMessage ") << dstrTrackId << I_(" [") << str.length() << I_("] ")
            // << DString(DStringA(str.c_str())) << bf::log::endlf;
            lsTrace << I_("BytesMessage ") << dstrTrackId << I_(" [") << str.length() << I_("] ")
                    << bf::log::endlf;
            dstrResponse_ = str;
          }
          else
          {
            cms::TextMessage* textMsg = dynamic_cast<cms::TextMessage*>(respMessage);
            if (textMsg != nullptr)
            {
              std::string rStr = textMsg->getText();
              if (rStr.length() == 0 || I_('<') == rStr.at(0))
              {
                // It's XML ... it's an error!
                ls << I_("TextMessage ") << dstrTrackId << I_(" [") << rStr.length() << I_("] ")
                   << DString(DStringA(rStr.c_str())) << bf::log::endlf;
                SonicFrameworkError sfwe(rStr, getDelimiter());
                dstrResponse_ = sfwe.getErrorMessage();
                dstrResponse_ += getDelimiter();
                dstrResponse_ += "F";
                dstrResponse_ += DStringA(dstrTrackId);
              }
              else
              {
                std::string rStrDecoded = UTF8toISO8859_1(rStr.c_str());
                // Logging out the content of the messages would violate compliance rules.
                //   CP 20101203
                // lsTrace << I_("TextMessage ") << dstrTrackId << I_(" [") << rStrDecoded.length()
                // << I_("] ") << DString(DStringA(rStrDecoded.c_str())) << bf::log::endlf;
                lsTrace << I_("TextMessage ") << dstrTrackId << I_(" [") << rStrDecoded.length()
                        << I_("] ") << bf::log::endlf;
                dstrResponse_ = rStrDecoded;
              }
            }
            else
            {
              ls << I_("Response to ") << dstrTrackId
                 << I_(" received, but it's not of type TextMessage or ByteMessage");
              // It's a funny type like Multi-part or XML.
              // Fortunately, we can treat if like a Text message and get the underlying error out
              // of the message
              cms::TextMessage* textMsg = dynamic_cast<cms::TextMessage*>(respMessage);
              std::string rStr = textMsg->getText();
              if (0 == rStr.length() || I_('<') == rStr.at(0))
              {
                // It's XML ... it's an error!
                SonicFrameworkError sfwe(rStr, getDelimiter());
                dstrResponse_ = sfwe.getErrorMessage();
                dstrResponse_ += getDelimiter();
                dstrResponse_ += "F";
                dstrResponse_ += DStringA(dstrTrackId);
              }
              else
              {
                // It's not XML so throw an error to the framework.
                cli.log("Unknown Message Received");
                THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                               CND::ERR_SMQ_UNKNOWN_MESSAGE_TYPE);
              }
            }
          }
        }
        else
        {
          cli.log("View Timeout");
          DString strIdi;
          addIDITagValue(strIdi, I_("VIEWNAME"), DString(viewName));
          DString timeout;
          timeout.convertIntToString(iTimeout_);
          addIDITagValue(strIdi, I_("TIMEOUT"), timeout);

          THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                            CND::ERR_VIEW_TIMEOUT, strIdi);
        }
      }
      catch (ConditionException)
      {
        cli.setReceiveTime(tRecv.elapsed());
        cli.log("ConditionException");
        throw;
      }
      catch (cms::CMSException e)
      {
        setRecycleRequired();
        DString idi;
        addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
        THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                          CND::ERR_SMQ_SONICMQ_ERROR, idi);
      }
      catch (...)
      {
        cli.setReceiveTime(tRecv.elapsed());
        cli.log("Generic Exception");
        THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                       CND::ERR_SMQ_MESSAGE_RECEIVE_FAILED);
      }
    }
    catch (ConditionException)
    {
      cli.log("ConditionException");
      throw;
    }
    catch (cms::CMSException e)
    {
      if (retryCount == 0)
      {
        recycle();
        ++retryCount;
        retry = true;
      }
      else
      {
        setRecycleRequired();
        DString idi;
        addIDITagValue(idi, I_("ERROR"), LogCMSException(__LINE__, e));
        THROWFROMFILEIDI2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                          CND::ERR_SMQ_SONICMQ_ERROR, idi);
      }
    }
    catch (...)
    {
      cli.log("catch all");
      THROWFROMFILE2(CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("putRequest"),
                     CND::ERR_SMQ_MESSAGE_SEND_FAILED);
    }
    cli.log();

  } while (retry);
}

//******************************************************************************
void ActiveMQConnection::freeResponse() {}

const DStringA& ActiveMQConnection::getHostId() const { return (idHost_); }

const DStringA& ActiveMQConnection::getDescription() const { return (description_); }

#pragma warning(push)
#pragma warning(disable : 4800)
bool ActiveMQConnection::isStale() const { return (static_cast<bool>(session_ == nullptr)); }
#pragma warning(pop)

void ActiveMQConnection::makeStale() { recycle(); }

const DStringA& ActiveMQConnection::getResponse() { return (dstrResponse_); }
