#include "stdafx.h"

#include "SonicWorkEventAgent.h"
#include "SonicWorkEvent.h"

#include <bfcbo\bfworksession.hpp>
#include <bfconmgr\BFConnectionManager.hpp>
#include <bfdbrkr\bfhost.hpp>

#include <ifastdbrkr\SonicConnection.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>

#include "dstcview.h"
#include "mainfrm.h"
#include "mfdstc.h"

#include <json\config.h>
#include <json\json.h>
#include <rpc.h>

#ifndef CONFIGMANAGER_HPP
#include <ConfigManager.hpp>
#endif
#ifndef CONFIGURATIONCONSTANTS_H
#include "ConfigurationConstants.h"
#endif

using namespace progress::message::jclient;
using namespace boost;

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;

namespace
{
// Trace literals
const I_CHAR* const CLASSNAME = I_("SonicWorkEventAgent");
const I_CHAR* const ONMESSAGE = I_("onMessage");
}

static DString asDString(StringRef s)
{
  WStringRef wStr = s->toWide();
  std::wstring w;
  w.append((const I_CHAR*)wStr, wStr->length());
  return (DString(w));
}

static DStringA asDStringA(StringRef s)
{
  AStringRef aStr = s->toAscii();
  std::string a;
  a.append((const char*)aStr, aStr->length());
  return (DStringA(a));
}

SonicWorkEventAgent::SonicWorkEventAgent(const DString& dstrUserID, const DString& dstrTopic)
    : connection_(null), session_(null), subscriber_(null), shutdownEvent_(true), outFields_()
{
  workEventTopic_ = dstrTopic;

  ConfigManager* pDSTCMgr = ConfigManager::getManager(CONFIGURATION_CONSTANTS::MFDSTC);
  Configuration cfgPath = pDSTCMgr->retrieveConfig(CONFIGURATION_CONSTANTS::RTSHost);

  DString pushWorkEventTopicPrefix =
      cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQWorkEventTopicPrefix);
  if (pushWorkEventTopicPrefix == NULL_STRING)
  {
    pushWorkEventTopicPrefix = workEventTopic_;
  }

  DString dstrUserIDLower(dstrUserID);
  dstrUserIDLower.lowerCase();
  workEventTopic_ = pushWorkEventTopicPrefix.append(dstrUserIDLower);
  workEventReplyTopic_ = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQWorkEventReplyTopic);

  keepAliveTopic_ = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQWorkAgentKeepAliveTopic);
  if (keepAliveTopic_ == NULL_STRING)
  {
    keepAliveTopic_ = I_("IAMALIVE");
  }

  DString smqBrokerURLs = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQBrokerURLs);
  DString smqUser = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQUser);
  DString smqPassword = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQPassword);

  connFactory_ = createTopicConnectionFactory(null, createString(smqUser.c_str()),
                                              createString(smqPassword.c_str()));
  connFactory_->setConnectionURLs(createString(smqBrokerURLs.c_str()));
  connFactory_->setFaultTolerant(jtrue);

  try
  {
    connect();
  }
  catch (JMSExceptionRef e)
  {
    MessageBoxA(HWND_DESKTOP, asDStringA(e->toString()).c_str(), "Error creating EventAgent",
                MB_OK);
  }
  catch (...)
  {
    MessageBoxA(HWND_DESKTOP, "", "Error creating EventAgent", MB_OK);
  }

  start();
}

SonicWorkEventAgent::~SonicWorkEventAgent(void)
{
  shutdownEvent_.set();  // signal the poller to shutdown
  disconnect();
}

void SonicWorkEventAgent::run()
{
  TopicRef topic = session_->createTopic(createString(keepAliveTopic_.c_str()));

  Json::Value keepAliveRoot;
  keepAliveRoot["ReplyType"] = "loggedin";
  keepAliveRoot["DTopId"] = getDtopId().getImp();
  keepAliveRoot["ComputerName"] = getComputerName().getImp();
  keepAliveRoot["IFastUserName"] = getUserId().getImp();

  while (!shutdownEvent_.wait(15000))
  {
    send(topic, keepAliveRoot);
  }
}

void SonicWorkEventAgent::connect()
{
  connection_ = connFactory_->createTopicConnection();
  connection_->start();

  session_ = connection_->createTopicSession(jfalse, Session_AUTO_ACKNOWLEDGE);
  TopicRef topic = session_->createTopic(createString(workEventTopic_.c_str()));
  subscriber_ = session_->createSubscriber(topic);
  //      subscriber_ = session_->createSubscriber( topic, createString("smithd_1234"));
  subscriber_->setMessageListenerObj(this);
}

void SonicWorkEventAgent::disconnect()
{
  if (session_ != null)
  {
    session_->close();
    session_ = null;
  }
  if (connection_ != null)
  {
    connection_->close();
    connection_ = null;
  }
}

void SonicWorkEventAgent::onMessage(MessageRef msg)
{
  MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, ONMESSAGE);

  TopicRef replyTopic = null;
  if (workEventReplyTopic_ == NULL_STRING)
  {
    DestinationRef replyDest = msg->getJMSReplyTo();
    if (replyDest != null && replyDest->instanceof (Topic::type()))
    {
      replyTopic = TopicRef::cast(replyDest);
    }
    else
    {
      shared_ptr<WorkEvent>();
    }
  }
  else
  {
    replyTopic = session_->createTopic(createString(workEventReplyTopic_.c_str()));
  }

  try
  {
    shared_ptr<WorkEvent> event = createWorkEvent(msg, replyTopic);

    if (event)
    {
      CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
      if (pMainFrm)
      {
        CDSTCView* pDSTCView = (CDSTCView*)pMainFrm->GetActiveView();
        if (pDSTCView)
        {
          pDSTCView->PostWorkEventMessage(event);
        }
      }
    }
  }
  catch (...)
  {
    MessageBoxA(HWND_DESKTOP, "", "Error processing Work Event message.", MB_OK);
    errorReply(replyTopic, I_("FAILED_TO_POST_EVENT"), msg);
  }
}

shared_ptr<WorkEvent> SonicWorkEventAgent::createWorkEvent(MessageRef msg, TopicRef replyTopic)
{
  if (!msg->instanceof (TextMessage::type()))
  {
    errorReply(replyTopic, I_("INVALID_MSG_TYPE"), msg);
    shared_ptr<WorkEvent>();
  }

  TextMessageRef textMsg = TextMessageRef::cast(msg);
  UTF8StringRef uStr = textMsg->getText()->toUTF8();

  Json::Value jsonRoot;
  Json::Reader jsonReader;
  bool parsedSuccess =
      jsonReader.parse(reinterpret_cast<const char*>(uStr->getValue()), jsonRoot, false);

  if (!parsedSuccess)
  {
    errorReply(replyTopic, I_("FAILED_TO_PARSE"), msg);
    return shared_ptr<WorkEvent>();
  }

  if (!jsonRoot["DTopId"].isNull() && jsonRoot["DTopId"].isConvertibleTo(Json::stringValue))
  {
    DStringA reqDTopId = jsonRoot["DTopId"].asString();
    if (reqDTopId != getDtopId())
    {
      // not for us.  exit quietly
      return shared_ptr<WorkEvent>();
    }
  }

  return shared_ptr<WorkEvent>(new SonicWorkEvent(msg, jsonRoot, replyTopic, this));
}

void SonicWorkEventAgent::onException(JMSExceptionRef ex) {}

void SonicWorkEventAgent::errorReply(TopicRef topic, const DString& dstrError, MessageRef origMsg)
{
  Json::Value replyRoot;
  replyRoot["ReplyType"] = "error";
  replyRoot["ErrorCode"] = dstrError.asA();
  send(topic, replyRoot, origMsg);
}

static StringRef IFDS_PREFIX = createString("IFAST_");

void SonicWorkEventAgent::send(TopicRef topic, Json::Value& jsonRoot, MessageRef origMsg)
{
  jsonRoot["DTopId"] = getDtopId().getImp();
  jsonRoot["ComputerName"] = getComputerName().getImp();
  try
  {
    TopicPublisherRef publisher = session_->createPublisher(topic);
    publisher->setDeliveryMode(DeliveryMode_NON_PERSISTENT);

    TextMessageRef message = session_->createTextMessage();
    if (origMsg != null)
    {
      message->setJMSReplyTo(origMsg->getJMSReplyTo());
      StringRef corrId = origMsg->getJMSCorrelationID();
      if (corrId != null)
      {
        message->setJMSCorrelationID(corrId);
      }
      EnumerationRef propNames = origMsg->getPropertyNames();
      while (propNames->hasMoreElements())
      {
        StringRef propName = StringRef::cast(propNames->nextElement());
        if (propName->startsWith(IFDS_PREFIX))
        {
          message->setObjectProperty(propName, origMsg->getObjectProperty(propName));
        }
      }
    }

    Json::FastWriter jsonWriter;
    StringRef replyStr = createString(
        reinterpret_cast<const unsigned char*>(jsonWriter.write(jsonRoot).c_str()), "UTF-8");
    message->setText(replyStr);
    publisher->publish(message);
  }
  catch (JMSExceptionRef e)
  {
    MessageBoxA(HWND_DESKTOP, asDStringA(e->toString()).c_str(), "Error sending event response.",
                MB_OK);
  }
  catch (...)
  {
    MessageBoxA(HWND_DESKTOP, "", "Error sending event response.", MB_OK);
  }
}

void SonicWorkEventAgent::send(TopicRef topic, Json::Value& jsonRoot)
{
  send(topic, jsonRoot, null);
}

const Json::Value& SonicWorkEventAgent::getOutFields(const DSTCSecurity* pSecurity,
                                                     const DString& dstrCompanyId)
{
  if (!outFields_)
  {
    Json::Value request;
    request["RequestType"] = "GetOutFields";

    Json::Value response = callService(pSecurity, request, dstrCompanyId);

    if (response.isObject() && response.isMember("OutFields"))
    {
      outFields_ = response["OutFields"];
    }
  }
  return outFields_;
}

const Json::Value SonicWorkEventAgent::callService(const DSTCSecurity* pSecurity,
                                                   Json::Value& request,
                                                   const DString& dstrCompanyId)
{
  CWaitCursor cursor;
  SonicConnection* connection = dynamic_cast<SonicConnection*>(
      BFConnectionManager::getInstance()->getConnection(pSecurity->getHost()->getId()));

  request["DTopId"] = getDtopId().getImp();
  request["ComputerName"] = getComputerName().getImp();
  request["IFastUserName"] = getUserId().getImp();

  Json::FastWriter jsonWriter;
  DStringA dstrRequst = jsonWriter.write(request).c_str();

  connection->putRequestAWD(dstrRequst, TRUE, dstrCompanyId, const_cast<DSTCSecurity*>(pSecurity));

  Json::Value response;
  Json::Reader jsonReader;
  DStringA dstrResponse = connection->getResponse();
  bool parsedSuccess = jsonReader.parse(dstrResponse.getImp(), response, false);

  if (!parsedSuccess)
  {
    return Json::Value();  // return null
  }

  return response;
}
