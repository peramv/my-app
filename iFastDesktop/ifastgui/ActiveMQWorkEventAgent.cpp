#include "stdafx.h"

#include "ActiveMQWorkEventAgent.h"

#include <ifastgui\resource.h>
#include "dstcview.h"
#include "mainfrm.h"
#include "mfdstc.h"

#include "ActiveMQWorkEvent.h"

#include <bfconmgr\BFConnectionManager.hpp>
#include <bfconmgr\BFHostConnectionManager.hpp>
#include <bfdbrkr\bfhost.hpp>

#include <ifastdbrkr\ActiveMQConnection.hpp>
#include <ifastdbrkr\ActiveMQConnectionFactory.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>

#include <json\config.h>
#include <json\json.h>
#include <rpc.h>

#include <activemq\core\ActiveMQConnectionFactory.h>
#include <cms\Connection.h>
#include <cms\Session.h>

#ifndef CONFIGMANAGER_HPP
#include <ConfigManager.hpp>
#endif
#ifndef CONFIGURATIONCONSTANTS_H
#include "ConfigurationConstants.h"
#endif

using namespace boost;

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;

namespace
{
// Trace literals
const I_CHAR* const CLASSNAME = I_("ActiveMQWorkEventAgent");
const I_CHAR* const ONMESSAGE = I_("onMessage");
}

static std::shared_ptr<cms::Connection> getSingleConnection() {

  auto bfConnectionFactory =
      dynamic_cast<ActiveMQConnectionFactory*>(BFConnectionManager::getInstance()
                                                   ->getHostConnectionManager(I_("RTSCAN"))
                                                   ->getConnectionFactory());

  return bfConnectionFactory->getSingleConnection();
}

ActiveMQWorkEventAgent::ActiveMQWorkEventAgent(const DString& dstrUserID, const DString& dstrTopic)
    : connection_(getSingleConnection()), session_(nullptr), subscriber_(nullptr), shutdownEvent_(true), outFields_()
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

  try
  {
    connect();
  }
  catch (cms::CMSException e)
  {
    MessageBoxA(HWND_DESKTOP, e.what(), "Error creating EventAgent", MB_OK);
  }
  catch (...)
  {
    MessageBoxA(HWND_DESKTOP, "", "Error creating EventAgent", MB_OK);
  }

  start();
}

ActiveMQWorkEventAgent::~ActiveMQWorkEventAgent(void)
{
  shutdownEvent_.set();  // signal the poller to shutdown
  disconnect();
}

void ActiveMQWorkEventAgent::run()
{
	std::unique_ptr<cms::Topic> topic( session_->createTopic(keepAliveTopic_.asA()) );

  Json::Value keepAliveRoot;
  keepAliveRoot["ReplyType"] = "loggedin";
  keepAliveRoot["DTopId"] = getDtopId().getImp();
  keepAliveRoot["ComputerName"] = getComputerName().getImp();
  keepAliveRoot["IFastUserName"] = getUserId().getImp();

  while (!shutdownEvent_.wait(15000))
  {
	  send(topic.get(), keepAliveRoot);
  }
}

void ActiveMQWorkEventAgent::connect()
{

  session_.reset(connection_->createSession(cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE));
  auto topic = session_->createTopic(workEventTopic_.asA());
  subscriber_.reset(session_->createConsumer(topic));

  subscriber_->setMessageListener(this);
}

void ActiveMQWorkEventAgent::disconnect()
{
  if (session_ != nullptr)
  {
    session_->close();
    session_ = nullptr;
  }
}

void ActiveMQWorkEventAgent::onMessage(const cms::Message* msg)
{
  MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, ONMESSAGE);

  std::shared_ptr<cms::Destination> replyTopic = nullptr;
  if (workEventReplyTopic_ == NULL_STRING)
  {
    const cms::Destination* replyDest = msg->getCMSReplyTo();
    if (replyDest != null)
    {
		replyTopic.reset(replyDest->clone());
    }
    else
    {
      shared_ptr<WorkEvent>();
    }
  }
  else
  {
    replyTopic.reset(session_->createTopic(workEventReplyTopic_.asA()));
  }

  try
  {
	  std::shared_ptr<cms::Message> msgCopy(msg->clone());
	  shared_ptr<WorkEvent> event = createWorkEvent(msgCopy, replyTopic);

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
    errorReply(replyTopic.get(), I_("FAILED_TO_POST_EVENT"), msg);
  }
}

shared_ptr<WorkEvent> ActiveMQWorkEventAgent::createWorkEvent(std::shared_ptr<cms::Message> msg,
                                                              std::shared_ptr<cms::Destination> replyTopic)
{
	auto textMsg = dynamic_cast<const cms::TextMessage*>(msg.get());
  if (!textMsg)
  {
	  errorReply(replyTopic.get(), I_("INVALID_MSG_TYPE"), msg.get());
    return shared_ptr<WorkEvent>();
  }

  auto uStr = textMsg->getText();

  Json::Value jsonRoot;
  Json::Reader jsonReader;
  bool parsedSuccess = jsonReader.parse(uStr, jsonRoot, false);

  if (!parsedSuccess)
  {
	  errorReply(replyTopic.get(), I_("FAILED_TO_PARSE"), msg.get());
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

  return shared_ptr<WorkEvent>(new ActiveMQWorkEvent(msg, jsonRoot, replyTopic, this));
}

void ActiveMQWorkEventAgent::onException(const cms::CMSException& ex) {}

void ActiveMQWorkEventAgent::errorReply(const cms::Destination* topic, const DString& dstrError,
                                        const cms::Message* origMsg)
{
  Json::Value replyRoot;
  replyRoot["ReplyType"] = "error";
  replyRoot["ErrorCode"] = dstrError.asA();
  send(topic, replyRoot, origMsg);
}

static auto IFDS_PREFIX = "IFAST_";

void ActiveMQWorkEventAgent::send(const cms::Destination* topic, Json::Value& jsonRoot,
                                  const cms::Message* origMsg)
{
  jsonRoot["DTopId"] = getDtopId().getImp();
  jsonRoot["ComputerName"] = getComputerName().getImp();
  try
  {
	std::unique_ptr<cms::MessageProducer> publisher(session_->createProducer(topic));
    publisher->setDeliveryMode(DeliveryMode_NON_PERSISTENT);

    cms::TextMessage* message = session_->createTextMessage();
    if (origMsg != null)
    {
      message->setCMSReplyTo(origMsg->getCMSReplyTo());
      auto corrId = origMsg->getCMSCorrelationID();
      if (corrId != null)
      {
        message->setCMSCorrelationID(corrId);
      }
      auto propNames = origMsg->getPropertyNames();

      for (auto name : propNames)
      {
        if (name.find(IFDS_PREFIX) == 0)
        {
          switch (origMsg->getPropertyValueType(name))
          {
            case cms::Message::ValueType::BOOLEAN_TYPE:
              message->setBooleanProperty(name, origMsg->getBooleanProperty(name));
              break;

            case cms::Message::ValueType::BYTE_TYPE:
              message->setByteProperty(name, origMsg->getByteProperty(name));
              break;

            case cms::Message::ValueType::INTEGER_TYPE:
              message->setIntProperty(name, origMsg->getIntProperty(name));
              break;

            case cms::Message::ValueType::LONG_TYPE:
              message->setLongProperty(name, origMsg->getLongProperty(name));
              break;

            case cms::Message::ValueType::DOUBLE_TYPE:
              message->setDoubleProperty(name, origMsg->getDoubleProperty(name));
              break;

            case cms::Message::ValueType::FLOAT_TYPE:
              message->setFloatProperty(name, origMsg->getFloatProperty(name));
              break;

            case cms::Message::ValueType::STRING_TYPE:
              message->setStringProperty(name, origMsg->getStringProperty(name));
              break;
          }
        }
      }
    }

    Json::FastWriter jsonWriter;
    auto replyStr = jsonWriter.write(jsonRoot);
    message->setText(replyStr);
    publisher->send(message);
  }
  catch (cms::CMSException e)
  {
    MessageBoxA(HWND_DESKTOP, e.what(), "Error sending event response.", MB_OK);
  }
  catch (...)
  {
    MessageBoxA(HWND_DESKTOP, "", "Error sending event response.", MB_OK);
  }
}

void ActiveMQWorkEventAgent::send(const cms::Destination* topic, Json::Value& jsonRoot)
{
  send(topic, jsonRoot, null);
}

const Json::Value& ActiveMQWorkEventAgent::getOutFields(const DSTCSecurity* pSecurity,
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

const Json::Value ActiveMQWorkEventAgent::callService(const DSTCSecurity* pSecurity,
                                                      Json::Value& request,
                                                      const DString& dstrCompanyId)
{
  CWaitCursor cursor;
  auto connection = dynamic_cast<ActiveMQConnection*>(
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
