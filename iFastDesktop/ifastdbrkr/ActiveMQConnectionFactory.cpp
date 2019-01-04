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
// ^FILE   :  BFConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 20
//
// ----------------------------------------------------------
#include "Winsock2.h"

#include <srcprag.h>

#include <bf/log/log.hpp>
#include <configmanager.hpp>
#include "ActiveMQConnection.hpp"
#include "ActiveMQConnectionFactory.hpp"
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <decaf/net/URI.h>
namespace
{
const I_CHAR *CLASSNAME = I_("ActiveMQConnectionFactory");
}

namespace ifds
{
const DString &getAppVersion();
}

cms::ConnectionFactory *ActiveMQConnectionFactory::createCMSConnectionFactory(
    const DString &brokerURLs, const DString &user, const DString &password)
{
  //const std::string uriStr = "failover:(" + brokerURLs.asA() + ")?maxReconnectAttempts=0&randomize=false";
  // Don't 'randomize' the broker selection: always pick the first one
  //   - CP 21Mar2018
  // const std::string uriStr = "failover:(" + brokerURLs.asA() + ")?maxReconnectAttempts=0&randomize=false";
  const std::string uriStr = brokerURLs.asA();
  const std::string userStr = user.asA();
  const std::string pwdStr = password.asA();

  return new activemq::core::ActiveMQConnectionFactory(uriStr, userStr, pwdStr);
}

ActiveMQConnectionFactory::ActiveMQConnectionFactory(
    const DString &brokerURLs, const DString &singleQueue, const DString &multiQueue,
    const DString &ldapQueue, const DString &awdQueue, const DString &user, const DString &password,
    int cMaxUses, int iTimeout, int iTimeToLive, const DString &dstrCswAcl)
    : brokerURLs_(brokerURLs),
      singleQueue_(singleQueue),
      multiQueue_(multiQueue),
      ldapQueue_(ldapQueue),
      awdQueue_(awdQueue),
      //cMaxUses_(cMaxUses),
      // Always set to -1 to permanently disable connection recycling
      // It's a silly thing to do for JMS - CP 21Mar2018
      cMaxUses_(-1),
      user_(user),
      password_(password),
      iTimeout_(iTimeout),
      iTimeToLive_(iTimeToLive),
      connFactory_(createCMSConnectionFactory(brokerURLs, user, password)),
      s_singleConnection_(nullptr),
      dstrCswAcl_(dstrCswAcl)
{
  if (dstrCswAcl_ == I_(""))
  {
    dstrCswAcl_ = I_("cswacl");
  }
}

ActiveMQConnectionFactory::~ActiveMQConnectionFactory() {}

BFConnection *ActiveMQConnectionFactory::createConnection(const DStringA &hostId)
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;

  if (!reuseConnection()) {
     ls << I_("Creating new ActiveMQConnection") << bf::log::endlf;
     return (new ActiveMQConnection(hostId, "ActiveMQConnection", connFactory_, singleQueue_,
                                    multiQueue_, ldapQueue_, awdQueue_, cMaxUses_, iTimeout_, iTimeToLive_,
                                    dstrCswAcl_));
  } else {
     ls << I_("Creating new ActiveMQConnection with single CMS Connection") << bf::log::endlf;
     return (new ActiveMQConnection(hostId, "ActiveMQConnection", getSingleConnection(), singleQueue_,
                                    multiQueue_, ldapQueue_, awdQueue_, cMaxUses_, iTimeout_, iTimeToLive_,
                                    dstrCswAcl_));
  }
}

void ActiveMQConnectionFactory::destroyConnection(BFConnection *connection)
{
  if (NULL == connection) return;

  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;
  ls << I_("Destroying ActiveMQConnection") << bf::log::endlf;

  ActiveMQConnection *smqConnection = dynamic_cast<ActiveMQConnection *>(connection);
  delete smqConnection;
}

void ActiveMQConnectionFactory::setTimeout(int iTimeout) { iTimeout_ = iTimeout; }

void ActiveMQConnectionFactory::setTimeToLive(int iTimeToLive) { iTimeToLive_ = iTimeToLive; }

bool ActiveMQConnectionFactory::reuseConnection()
{
  return (GetConfigValueAsBool(I_("RTSHost"), I_("UseSingleSonicConnection")));
}

std::shared_ptr<cms::Connection> ActiveMQConnectionFactory::getSingleConnection()
{
  bf::log::LogStream ls(bf::log::databroker);
  ls << bf::log::information;

  ls << I_("Using Single cms::ActiveMQConnection") << bf::log::endlf;

  if (s_singleConnection_ != nullptr)
  {
    return (s_singleConnection_);
  }
  static BFCritSec cs;
  BFGuard g(cs);
  if (s_singleConnection_ == nullptr)
  {
     ls << I_("Making Single cms::ActiveMQConnection") << bf::log::endlf;
	  s_singleConnection_.reset(connFactory_->createConnection());
    s_singleConnection_->start();
  }
  return (s_singleConnection_);
}

