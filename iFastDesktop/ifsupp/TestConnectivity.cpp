#pragma warning(disable : 4001) /* Single-line comment */

#include "stdafx.h"
//#include <afxdllx.h>
#include <DString.hpp>
#include <bfconmgr/BFConnectionManager.hpp>
#include <bfconmgr/PooledHostConnectionManager.hpp>
#include <configmanager.hpp>
#include <ifastdbrkr/ActiveMQConnection.hpp>
#include <ifastdbrkr/ActiveMQConnectionFactory.hpp>
#include <ifastdbrkr/SonicConnection.hpp>
#include <ifastdbrkr/SonicConnectionFactory.hpp>
#include <ifastdbrkr\ifastdbrkr.hpp>
#include <map>
#include <typeinfo>
#include "AMQTest.h"
#include "SMQTest.h"
#include "SonicConnectionTest.h"
#include "TestConnectivity.h"
#include "ifsupp.h"
#include "ifsuppext.hpp"

bool ifsupp::testConnectivity(const ifastdbrkr::MessageService& service, const ifastdbrkr::MessageServiceConfig& config , DString& errorString)
{
  DString vmHostName =
      GetConfigValueAsString(ConfigManager::getApplication(), I_("RTSHost"), I_("VMHostName"));
  BFConnectionManager* pConMgr = BFConnectionManager::getInstance();
  int lMinConnections;
  int lMaxConnections;
  int lCountConnections;
  int lInUseConnections;
  int lCountFailures;

  std::unique_ptr<MessageServiceTest> smqTest = createTest(service, config);
  bool retVal = false;

  DString message;
  if (!smqTest->doTelnetTest(message) || !smqTest->doConnectionTest(message) ||
      !smqTest->doSingleQTest(message) || !smqTest->doMultiQTest(message) ||
      !smqTest->doAuthQTest(message))
  {
    errorString = message;
    return retVal;
  };

  retVal = true;
  return retVal;
}

bool ifsupp::testAWDConnectivity(DString& errorString)
{
  ifastdbrkr::MessageService service = ifastdbrkr::getMessageService();
  ifastdbrkr::MessageServiceConfig config;

  DString vmHostName =
      GetConfigValueAsString(ConfigManager::getApplication(), I_("RTSHost"), I_("VMHostName"));
  BFConnectionManager* pConMgr = BFConnectionManager::getInstance();
  int lMinConnections;
  int lMaxConnections;
  int lCountConnections;
  int lInUseConnections;
  int lCountFailures;

  DString dstrLDAPNS;
  try
  {
    if (NULL != pConMgr)
    {
      PooledHostConnectionManager* pHostConMgr =
          dynamic_cast<PooledHostConnectionManager*>(pConMgr->getHostConnectionManager(vmHostName));
      if (NULL != pHostConMgr)
      {
        lMinConnections = pHostConMgr->getMinConnections();
        lMaxConnections = pHostConMgr->getMaxConnections();
        lCountConnections = pHostConMgr->getConnectionCount();
        lInUseConnections = pHostConMgr->getConnectionsInUse();
        lCountFailures = pHostConMgr->getConnectionFailures();

        switch (service)
        {
          case ifastdbrkr::MessageService::SonicMQ:
          {
            auto* pFactory =
                dynamic_cast<SonicConnectionFactory*>(pHostConMgr->getConnectionFactory());
            if (NULL != pFactory)
            {
              config.brokerURLs = pFactory->getBrokerURLs();
              config.user = pFactory->getUser();
              config.singleQueue = pFactory->getSingleQueue();
              config.multiQueue = pFactory->getMultiQueue();
              config.ldapQueue = pFactory->getLDAPQueue();
              config.awdQueue = pFactory->getAwdQueue();

              config.password = pFactory->getPassword();

              dstrLDAPNS = GetConfigValueAsString(I_("RTSHost"), I_("LDAPUserNS"));
            }
          }
          break;

          case ifastdbrkr::MessageService::ActiveMQ:
          {
            auto* pFactory =
                dynamic_cast<ActiveMQConnectionFactory*>(pHostConMgr->getConnectionFactory());
            if (NULL != pFactory)
            {
              config.brokerURLs = pFactory->getBrokerURLs();
              config.user = pFactory->getUser();
              config.singleQueue = pFactory->getSingleQueue();
              config.multiQueue = pFactory->getMultiQueue();
              config.ldapQueue = pFactory->getLDAPQueue();
              config.awdQueue = pFactory->getAwdQueue();

              config.password = pFactory->getPassword();

              dstrLDAPNS = GetConfigValueAsString(I_("RTSHost"), I_("LDAPUserNS"));
            }
          }
          break;

          default:
            assert(false);
        }
      }
    }
  }
  catch (std::bad_cast)
  {
  }

  auto smqTest = createTest(service, config);
  bool retVal = false;

  DString message;
  if (!smqTest->doConnectionTest(message) || !smqTest->doAwdQTest(message))
  {
    errorString = message;
    return retVal;
  };

  retVal = true;
  return retVal;
}

std::unique_ptr<MessageServiceTest> ifsupp::createTest(const ifastdbrkr::MessageService& service,
                                                       const ifastdbrkr::MessageServiceConfig& config)
{
  std::unique_ptr<MessageServiceTest> smqTest;
  switch (service)
  {
    case ifastdbrkr::MessageService::SonicMQ:
      smqTest = std::unique_ptr<SMQTest>(new SMQTest);
      break;

    case ifastdbrkr::MessageService::ActiveMQ:
      smqTest = std::unique_ptr<AMQTest>(new AMQTest);
      break;
  }

  smqTest->setBrokerURL(config.brokerURLs);
  smqTest->setSMQUser(config.user);
  smqTest->setSMQPassword(config.password);
  smqTest->setSingleQ(config.singleQueue);
  smqTest->setMultiQ(config.multiQueue);
  smqTest->setAuthQ(config.ldapQueue);
  smqTest->setAwdQ(config.awdQueue);

  return smqTest;
}
