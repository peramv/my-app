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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MFDSTCSetup.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 03/01/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MFDSTCSetup
//    This is a utility class used to set up initial singletons appropriately.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#ifndef MFDSTCSETUP_HPP
#include "MFDSTCSetup.hpp"
#endif
#ifndef BFCONNECTIONMANAGER_HPP
#include <bfconmgr\BFConnectionManager.hpp>
#endif
#ifndef DSTCSETUPTHREAD_HPP
#include <ifastdbrkr\DSTCSetupThread.hpp>
#endif
#ifndef COMMANDDISPATCHER_HPP
#include <bfproc\CommandDispatcher.hpp>
#endif
#ifndef CONFIGMANAGER_HPP
#include <ConfigManager.hpp>
#endif
#ifndef CONFIGURATIONCONSTANTS_H
#include "ConfigurationConstants.h"
#endif
#ifndef DSTCREQUESTOR_HPP
#include <ifastdbrkr\DSTCRequestor.hpp>
#endif
#ifndef DSTCHOST_HPP
#include <ifastdbrkr\DSTCHost.hpp>
#endif
#ifndef GENERICINTERFACE_HPP
#include <bfproc\GenericInterface.hpp>
#endif
#ifndef GENERICINTERFACECONTAINER_HPP
#include <bfproc\GenericInterfaceContainer.hpp>
#endif
#ifndef PROCESSMANAGER_HPP
#include <bfproc\ProcessManager.hpp>
#endif
#ifndef VMPRIVATECONNECTIONFACTORY_HPP
#include <bfconmgr\VmPrivateConnectionFactory.hpp>
#endif
#ifndef WINDOWMANAGER_HPP
#include <uibase\WindowManager.hpp>
#endif
#ifndef BFDATABROKER_HPP
#include <bfdbrkr\BFDataBroker.hpp>
#endif
#ifndef _CSISESSION_H__INCLUDED_
#include <ifastcsi\CsiSession.h>
#endif
#ifndef SONICCONNECTIONFACTORY_HPP
#include <ifastdbrkr\SonicConnectionFactory.hpp>
#endif

#include <ifastdbrkr\ActiveMQConnectionFactory.hpp>
#include <ifastdbrkr\ifastdbrkr.hpp>
#include <ifsupp/ExceptionReport.hpp>
#include <ifsupp/ifsuppext.hpp>

namespace
{
	// Trace literals
	const I_CHAR *CLASSNAME     = I_( "MFDSTCSetup" );

	const I_CHAR *INIT = I_( "init" );
	const int MAX_CONNECTIONS = 20;
}

ProcessManager *MFDSTCSetup::s_rpProcessMgr = NULL;
DSTCSetupThread MFDSTCSetup::dstcSetupThread;
//******************************************************************************
//              Class Methods
//******************************************************************************

//******************************************************************************

bool MFDSTCSetup::init( BOOL bDirectConnect, DString& errorMessage)
{
	// Start singletons
	BFFieldId::setOptions( BFFieldId::allowDynamic );
	CommandDispatcher *rpDispatch = CommandDispatcher::getInstance();
	s_rpProcessMgr = new ProcessManager();
	//WindowManager *rpWindowMgr = WindowManager::getInstance();
	BFDataBroker::getInstance( );

	// Register sub-dispatchers
	rpDispatch->registerDispatcher( s_rpProcessMgr, BUSINESS_PROCESS_TYPE );
	//rpDispatch->registerDispatcher( rpWindowMgr, GUI_TYPE );

	ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );

	// register a HostConnectionManager for RTSCAN
	Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::RTSHost );
	DString dstrVmHostName =  I_("RTSCAN");
	//      DString dstrVmHostName = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::VMHostName );
	DSTCHost::setPrimaryHost( dstrVmHostName );

	int iRecycleInterval = -1;
	int iPersist = cfgPath.getValueAsInt( I_("PersistentConnections") );
	if( 0 != iPersist ) {
		iPersist = 1;
		iRecycleInterval = cfgPath.getValueAsInt( I_("RecycleInterval") );
		if( 0 == iRecycleInterval ) {
			iRecycleInterval = -1;
		}
	}

  ifastdbrkr::MessageServiceConfig smqConfig;

  smqConfig.brokerURLs = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQBrokerURLs);
  smqConfig.singleQueue = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQSingleQueue);
  smqConfig.multiQueue = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQMultiQueue);
  smqConfig.ldapQueue = cfgPath.getValueAsString(I_("SMQLDAPQueue"));
  smqConfig.awdQueue = cfgPath.getValueAsString(I_("SMQAWDQueue"));
  smqConfig.user = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQUser);
  smqConfig.password = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQPassword);
	DString cswAcl     = cfgPath.getValueAsString( I_("cswacl") );

  auto dstrSmqTimeout = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQWaitTimeout);
  auto dstrSmqMaxConnections = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::SMQMaxConnections);

  smqConfig.iTimeout = dstrSmqTimeout.convertToULong();
  if (!smqConfig.iTimeout)
  {
    smqConfig.iTimeout = 120;
  }

  smqConfig.iMaxConnections = dstrSmqMaxConnections.convertToULong();
  if (!smqConfig.iMaxConnections)
  {
    smqConfig.iMaxConnections = MAX_CONNECTIONS;
  }

  ifastdbrkr::MessageServiceConfig amqConfig;
  amqConfig.brokerURLs = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQBrokerURLs);
  amqConfig.singleQueue = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQSingleQueue);
  amqConfig.multiQueue = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQMultiQueue);
  amqConfig.ldapQueue = cfgPath.getValueAsString(I_("AMQLDAPQueue"));
  amqConfig.awdQueue = cfgPath.getValueAsString(I_("AMQAWDQueue"));
  amqConfig.user = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQUser);
  amqConfig.password = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQPassword);

  auto dstrAmqTimeout = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQWaitTimeout);
  auto dstrAmqTimeToLive = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQTimeToLive);
  auto dstrAmqMaxConnections = cfgPath.getValueAsString(CONFIGURATION_CONSTANTS::AMQMaxConnections);

  if (amqConfig.brokerURLs.empty()) amqConfig.brokerURLs = I_("failover:(") + smqConfig.brokerURLs + I_(")?maxReconnectAttempts=0&randomize=false");
  if (amqConfig.singleQueue.empty()) amqConfig.singleQueue = I_("Q.ZTS.SingleRequest");
  if (amqConfig.multiQueue.empty()) amqConfig.multiQueue = I_("Q.ZTS.MultiRequest");
  if (amqConfig.ldapQueue.empty()) amqConfig.ldapQueue = I_("Q.Authenticate");
  if (amqConfig.awdQueue.empty()) amqConfig.awdQueue = I_("Q.ZTS.AwdIntRequest");
  if (amqConfig.user.empty()) amqConfig.user = smqConfig.user;
  if (amqConfig.password.empty()) amqConfig.password = smqConfig.password;
  if (dstrAmqTimeout.empty()) dstrAmqTimeout = dstrSmqTimeout;

  amqConfig.iTimeout = dstrAmqTimeout.convertToULong();
  if (!amqConfig.iTimeout) amqConfig.iTimeout = 120;

  amqConfig.iTimeToLive = dstrAmqTimeToLive.convertToULong();
  if (!amqConfig.iTimeToLive) amqConfig.iTimeToLive = amqConfig.iTimeout;

  amqConfig.iMaxConnections = dstrAmqTimeout.convertToULong();
  if (!amqConfig.iMaxConnections) amqConfig.iMaxConnections = MAX_CONNECTIONS;

  iPersist = 1;

  if(tryMessageService(smqConfig, amqConfig, errorMessage) == false){
	  return false;
  }

  BFConnectionFactory *connectionFactory = nullptr;
  int iMaxConnections = 5;
  switch (ifastdbrkr::getMessageService())
  {
    case ifastdbrkr::MessageService::ActiveMQ:
      connectionFactory = new ActiveMQConnectionFactory(
          amqConfig.brokerURLs, amqConfig.singleQueue, amqConfig.multiQueue, amqConfig.ldapQueue,
          amqConfig.awdQueue, amqConfig.user, amqConfig.password, iRecycleInterval,
          amqConfig.iTimeout, amqConfig.iTimeToLive, cswAcl);
	  iMaxConnections=amqConfig.iMaxConnections;
      break;

    case ifastdbrkr::MessageService::SonicMQ:
      connectionFactory = new SonicConnectionFactory(
          smqConfig.brokerURLs, smqConfig.singleQueue, smqConfig.multiQueue, smqConfig.ldapQueue,
          smqConfig.awdQueue, smqConfig.user, smqConfig.password, iRecycleInterval,
          smqConfig.iTimeout, cswAcl);
	  iMaxConnections=smqConfig.iMaxConnections;
      break;
  }

  BFConnectionManager::getInstance()->createHostConnectionManager(
      dstrVmHostName, connectionFactory, iMaxConnections, true, /* always persistent connection */
      1);

	dstcSetupThread.start();
  return true;
}

//******************************************************************************

void MFDSTCSetup::exit()
{
	dstcSetupThread.wait( INFINITE );
	CommandDispatcher *rpDispatch = CommandDispatcher::getInstance();
	WindowManager *rpWindowMgr = WindowManager::getInstance();

	// Deregister factories
	//   rpWindowMgr->deregisterFactory();
	//   s_rpProcessMgr->deregisterFactory();

	// Try to deregister managers from command dispatcher
	rpDispatch->deregisterDispatcher( rpWindowMgr );
	rpDispatch->deregisterDispatcher( s_rpProcessMgr );

	// Remove all singletons
	//   WindowFactory::killInstance();
	//   ProcessFactory::killInstance();

	WindowManager::killInstance();
	delete s_rpProcessMgr;
	s_rpProcessMgr = NULL;

	CommandDispatcher::killInstance();
	//   GenericInterfaceContainer::killAllInstances();

	BFConnectionManager::killInstance();
	BFDataBroker::killInstance();

  ifastdbrkr::shutdown();
}

bool MFDSTCSetup::tryMessageService(const ifastdbrkr::MessageServiceConfig &smqConfig,
                                    const ifastdbrkr::MessageServiceConfig &amqConfig,
                                    DString &errorMessage)
{
  DString testMessage;
  bool testResult = false;

  auto service = ifastdbrkr::getMessageService();
  DString currentMessage;
   testResult = ifsupp::testConnectivity(service, 
	  (service == ifastdbrkr::MessageService::ActiveMQ ? amqConfig : smqConfig), currentMessage);
  if (testResult == false)
  {
    DString servicestr =
        service == ifastdbrkr::MessageService::SonicMQ ? I_("SonicMQ") :
        service == ifastdbrkr::MessageService::ActiveMQ ? I_("ActiveMQ") : 
		I_("");

    testMessage = testMessage + servicestr + I_(" Error - ") + currentMessage + I_("\n");

	service = ifastdbrkr::cycleMessageService();
    testResult = ifsupp::testConnectivity(service, 
	  (service == ifastdbrkr::MessageService::ActiveMQ ? amqConfig : smqConfig), currentMessage);
  }

  if (testResult == false)
  {
    DString servicestr =
        service == ifastdbrkr::MessageService::SonicMQ ? I_("SonicMQ") : 
		service == ifastdbrkr::MessageService::ActiveMQ ? I_("ActiveMQ") : 
		I_("");

    testMessage = testMessage + servicestr + I_(" Error - ") + currentMessage + I_("\n");

    errorMessage = testMessage;
  }

  return testResult;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MFDSTCSetup.cpp-arc  $
*
*    Rev 1.29   Dec 22 2011 14:56:38   if991250
* IA French resources/substitutions
*
*    Rev 1.28   Dec 05 2011 09:00:56   purdyech
* ControlTextRewriter Logic
*
*    Rev 1.27   Aug 03 2009 23:19:04   purdyech
* LDAP Integration Pieces
*
*    Rev 1.26   Jun 05 2009 08:50:52   purdyech
* Fixed names of SonicSingle and SonicMulti queues in configuration.
* SonicErrorMessages are now handled appropriately.
*
*    Rev 1.25   May 25 2009 08:49:18   purdyech
* Include CswAcl as configurable value
*
*    Rev 1.24   May 01 2009 09:29:10   purdyech
* Pass customized cswacl parameter to SonicConnectionFactory
*
*    Rev 1.23   Feb 20 2009 14:57:46   purdyech
* ZTS Revision 6
*
*    Rev 1.22   Feb 06 2009 14:55:14   purdyech
* Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
*
*    Rev 1.21   Aug 15 2008 08:40:22   purdyech
* All SonicConnections are persistent regardless of what the registry/config says.
*
*    Rev 1.20   Jun 17 2008 16:00:28   smithdav
* Add SonicConnection support
*
*    Rev 1.19   Mar 12 2007 12:12:00   purdyech
* Added RTSHost/PersistentConnections and RTSHost/RecycleInterval configuration values.
*
*    Rev 1.18   Mar 08 2007 18:32:36   PURDYECH
* Added support for persistent connections.
*
*    Rev 1.17   Apr 16 2004 13:24:26   YINGBAOL
* PTS10029204:put dynamic create fieldId features back for desktop(core code changed).
*
*    Rev 1.16   Jan 23 2004 09:17:46   PURDYECH
* PET910 - RTSSocketConnectionFactory interface changed for core release iFAST_2.14.0
*
*    Rev 1.15   Jun 09 2003 15:58:26   SMITHDAV
* Changes related to Attachmate EXTRA integration
*
*    Rev 1.14   Oct 09 2002 23:55:48   PURDYECH
* PVCS Database Conversion
*
*    Rev 1.13   Sep 20 2002 15:23:26   SMITHDAV
* Changes to support multiple Csi configurations for mutliple instances of desktops.
*
*    Rev 1.12   27 Mar 2002 20:01:18   PURDYECH
* Process/WindowFactory overhaul
*
*    Rev 1.11   11 Oct 2001 18:22:18   SMITHDAV
* Changed ProcessManager form singleton to static.
*
*    Rev 1.10   Sep 24 2001 10:43:48   YINGBAOL
* introduce BFDBrKr.lib--- fix memory leak
*
*    Rev 1.9   09 Jul 2001 16:13:54   HSUCHIN
* thread bug fix
*
*    Rev 1.8   06 Jul 2001 14:07:12   HSUCHIN
* call DSTCSetupThread to preload data properties
*
*    Rev 1.7   03 May 2001 14:07:38   SMITHDAV
* Session management restructuring.
*
*    Rev 1.6   Mar 27 2001 11:55:22   YINGZ
* fix memory leak
*
*    Rev 1.5   Feb 12 2001 15:55:18   HSUCHIN
* changed init method to use direct RTS connection or Vm based on command line input.  Direct RTS connection is the default
*
*    Rev 1.4   May 10 2000 18:05:36   SMITHDAV
* Update on call to VMPrivateConnectionFactory constructor to specify connection name prefix.
*
*    Rev 1.3   May 02 2000 10:03:06   SMITHDAV
* Add initialization for connection manager.
*
*    Rev 1.2   Apr 04 2000 14:37:00   DT24433
* changed for GIC userid change
*
*    Rev 1.1   Mar 01 2000 19:23:22   DT24433
* added factories
*
*    Rev 1.0   Mar 01 2000 12:15:40   MCNABBGL
* Initial revision.
*
*/