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
// ^FILE   : AwdInterface.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 2 Apr 97
//
// ----------------------------------------------------------
//
// ^CLASS    : AwdInterface
//
// ^MEMBER VARIABLES :
//
//    AwdBaseInterface *pBase - pointer to base interface.
//
// ^CODING COMMENTS  :  pBase is constructed as an inherited class of
//                      AwdBaseInterface.  A DLL supporting the inherited
//                      class is dynamically loaded at run-time and must
//                      export a function called "fnObjectFactory()"
//
//                      fnObjectFactory() should constuct the inherited class
//                      and return it as a pointer to the base class.
//
//                      InterfaceManager is responsible for managing the
//                      run-time loaded DLL.
//
//******************************************************************************
#define DIAWDI_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef AWDINTERFACE_HPP
   #include "awdinterface.hpp"
#endif
#ifndef INTERFACEMANAGER_HPP
   #include "interfacemanager.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

AwdInterface::AwdInterface()
   : m_pBase( NULL ),
     m_bValid( false )
{
   MAKEFRAMECONSTRUCTOR2( DIAWDI_CONDITION, I_("AwdInterface"),
                          I_("AwdInterface()") )

   try
   {
      InterfaceManager *pManager = InterfaceManager::getManager();
      m_pBase = pManager->newInterface();
      m_bValid = true;
   }
   catch ( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce )
      m_pBase = NULL;
   }
   catch ( ... )
   {
      m_pBase = NULL;
   }

   if ( NULL == m_pBase )
   {
      m_pBase = new AwdBaseInterface;
   }

   PROMOTECONDITIONS();
}


AwdInterface::~AwdInterface()
{
   TRACE_DESTRUCTOR( I_("AwdInterface") )
   delete m_pBase;
}

string_vector AwdInterface::getBusinessAreaList()
{
   return m_pBase->getBusinessAreaList();
}

string_vector AwdInterface::getWorkTypeList( const DString & busarea )
{
   return m_pBase->getWorkTypeList( busarea );
}

string_vector AwdInterface::getCaseWorkTypeList( const DString & busarea )
{
   return m_pBase->getCaseWorkTypeList( busarea );
}

string_vector AwdInterface::getTransWorkTypeList( const DString & busarea )
{
   return m_pBase->getTransWorkTypeList( busarea );
}

string_vector AwdInterface::getSourceTypeList( const DString & busarea )
{
   return m_pBase->getSourceTypeList( busarea );
}

string_vector AwdInterface::getStatusList()
{
   return m_pBase->getStatusList();
}

string_vector AwdInterface::getStatusList( const AwdKey *pKey )
{
   return m_pBase->getStatusList( pKey );
}

string_vector AwdInterface::getStatusList( const AwdKey *pKey, const DString &strBussArea, const DString &strWkType )
{
	return m_pBase->getStatusList( pKey, strBussArea, strWkType );
}

string_vector AwdInterface::getQueueList( const QueueType type )
{
   return m_pBase->getQueueList( type );
}

data_obj_map & AwdInterface::getAwdFieldList()
{
   return m_pBase->getAwdFieldList();
}

bool AwdInterface::lookupWork( const CriteriaVector &criteria )
{
   return m_pBase->lookupWork( criteria );
}

ResultVector AwdInterface::lookupWork( const CriteriaVector &criteria,
                                             bool &more,
                                       const unsigned long max )
{
   return m_pBase->lookupWork( criteria, more, max );
}

bool AwdInterface::lookupSource( const CriteriaVector &criteria )
{
   return m_pBase->lookupSource( criteria );
}

ResultVector AwdInterface::lookupSource( const CriteriaVector &criteria,
                                               bool &more,
                                         const unsigned long max )
{
   return m_pBase->lookupSource( criteria, more, max );
}

ResultVector AwdInterface::lookupMore( bool &more )
{
   return m_pBase->lookupMore( more );
}

bool AwdInterface::loadCSD( AwdData &awdData )
{
   return m_pBase->loadCSD( awdData );
}

bool AwdInterface::stopCSD( const AwdKey *pKey )
{
   return m_pBase->stopCSD( pKey );
}

bool AwdInterface::showAwdContainer( bool bShow )
{
   return m_pBase->showAwdContainer( bShow );
}

bool AwdInterface::hasActiveService( const AwdKey *pKey,
                                     const DString &serviceName )
{
   return m_pBase->hasActiveService( pKey, serviceName );
}

bool AwdInterface::getAllChildren( const AwdKey* pKey,
                                   AwdKeyVector &awdKeyVector )
{
   return m_pBase->getAllChildren( pKey, awdKeyVector );
}

bool AwdInterface::getImmediateChildren( const AwdKey* pKey,
                                         AwdKeyVector &awdKeyVector )
{
   return m_pBase->getImmediateChildren( pKey, awdKeyVector );
}

bool AwdInterface::showAwdServiceWindow( const AwdKey *pKey,
                                         const DString &serviceName,
                                         bool bShow )
{
   return m_pBase->showAwdServiceWindow( pKey,
                                        serviceName,
                                        bShow );
}

bool AwdInterface::openAwdContainer()
{
   return m_pBase->openAwdContainer();
}

bool AwdInterface::locateAwdContainer( const AwdKey *pKey )
{
   return m_pBase->locateAwdContainer( pKey );
}

bool AwdInterface::isLocked( const AwdKey *pKey )
{
   return m_pBase->isLocked( pKey );
}

bool AwdInterface::insertItemInContainer( const AwdKey *pKey, bool lock )
{
   return m_pBase->insertItemInContainer( pKey, lock );
}

bool AwdInterface::insertItemInContainer( const AwdKey *pKey,
                                          const AwdKey *pParent,
                                          bool lock )
{
   return m_pBase->insertItemInContainer( pKey, pParent, lock );
}

bool AwdInterface::isItemInContainer( const AwdKey *pKey )
{
   return m_pBase->isItemInContainer( pKey );
}

bool AwdInterface::selectItemInContainer( const AwdKey *pKey )
{
   return m_pBase->selectItemInContainer( pKey );
}

bool AwdInterface::closeAwdContainer()
{
   return m_pBase->closeAwdContainer();
}

bool AwdInterface::clearAwdContainer()
{
   return m_pBase->clearAwdContainer();
}

bool AwdInterface::expandContainerItemDown( const AwdKey *pKey )
{
   return m_pBase->expandContainerItemDown( pKey );
}

bool AwdInterface::createAwdTransaction( AwdData &awdData, bool lock )
{
   return m_pBase->createAwdTransaction( awdData, lock );
}

bool AwdInterface::createAwdCase( AwdData &awdData, bool lock )
{
   return m_pBase->createAwdCase( awdData, lock );
}

bool AwdInterface::createAwdSource( const AwdData &awdData,
                                    const AwdSource::ObjectFormat format,
                                    const DString &strFile,
                                    AwdSource **ppSource,
                                    bool lock )
{
   return m_pBase->createAwdSource( awdData, format, strFile, ppSource, lock );
}

bool AwdInterface::createRelationship( const AwdKey *pParent,
                                       const AwdKey *pChild )
{
   return m_pBase->createRelationship( pParent, pChild );
}

bool AwdInterface::lockAwdObject( const AwdKey *pKey, bool lock )
{
   return m_pBase->lockAwdObject( pKey, lock );
}

bool AwdInterface::hasCaseForParent( const AwdKey *pKey, AwdKey **ppParent )
{
   return m_pBase->hasCaseForParent( pKey, ppParent );
}

bool AwdInterface::hasSourceForChild( const AwdKey *pKey, AwdKey **ppChild )
{
   return m_pBase->hasSourceForChild( pKey, ppChild );
}

bool AwdInterface::hasChildren( const AwdKey *pKey )
{
   return m_pBase->hasChildren( pKey );
}

bool AwdInterface::addComment( const AwdKey *pKey, const DString &comment )
{
   return m_pBase->addComment( pKey, comment );
}

bool AwdInterface::beginListenCreateObjects()
{
   return m_pBase->beginListenCreateObjects();
}

AwdKeyVector AwdInterface::endListenCreateObjects()
{
   return m_pBase->endListenCreateObjects();
}

AwdKey * AwdInterface::newAwdKey( const DString &createDateTime,
                                  const DString &recordCode,
                                  const DString &createNode )
{
   return m_pBase->newAwdKey( createDateTime, recordCode, createNode );
}

bool AwdInterface::retrieveData( const AwdKey *pKey, AwdData &awdData )
{
   return m_pBase->retrieveData( pKey, awdData );
}

bool AwdInterface::retrieveDataLite( const AwdKey *pKey,
                                     AwdData &awdData )
{
   return m_pBase->retrieveDataLite( pKey, awdData );
}

bool AwdInterface::retrieveSource( const AwdKey *pKey,
                                   AwdSource **ppSource )
{
   return m_pBase->retrieveSource( pKey, ppSource );
}

bool AwdInterface::startService( const AwdKey *pKey,
                                 const DString &strServiceName )
{
   return m_pBase->startService( pKey, strServiceName );
}

bool AwdInterface::stopService( const AwdKey *pKey,
                                const DString &strServiceName )
{
   return m_pBase->stopService( pKey, strServiceName );
}

bool AwdInterface::updateAwdObject( AwdData &awdData )
{
   return m_pBase->updateAwdObject( awdData );
}

bool AwdInterface::getAwdWork( AwdData &awdData )
{
   return m_pBase->getAwdWork( awdData );
}

bool AwdInterface::getAwdWorkObjects( AwdKeyVector &awdKeyVector )
{
   return m_pBase->getAwdWorkObjects( awdKeyVector );
}

bool AwdInterface::doubleClickContainerItem( const AwdKey *pKey )
{
   return m_pBase->doubleClickContainerItem( pKey );
}

AwdKey * AwdInterface::getCurrentContainerSelection()
{
   return m_pBase->getCurrentContainerSelection();
}

DString AwdInterface::getQueue( const AwdKey *pKey )
{
   return m_pBase->getQueue( pKey );
}

bool AwdInterface::setQueue( const AwdKey *pKey, const DString &queue )
{
   return m_pBase->setQueue( pKey, queue );
}

DString AwdInterface::getOperatorID()
{
   return m_pBase->getOperatorID();
}

unsigned long AwdInterface::getCountry()
{
   return m_pBase->getCountry();
}

DString AwdInterface::getWorkstationID()
{
   return m_pBase->getWorkstationID();
}

DString AwdInterface::getServerDateTime()
{
   return m_pBase->getServerDateTime();
}

string_vector AwdInterface::getSuspendCodeList()
{
   return m_pBase->getSuspendCodeList();
}

bool AwdInterface::suspendWorkObject( const AwdKey *pKey,
                                      const DString &activateDateTime,
                                      const DString &suspendCode )
{
   return m_pBase->suspendWorkObject( pKey, activateDateTime, suspendCode );
}

bool AwdInterface::unSuspendWorkObject( const AwdKey *pKey )
{
   return m_pBase->unSuspendWorkObject( pKey );
}

bool AwdInterface::isLoggedOn()
{
   InterfaceManager *pManager = InterfaceManager::getManager();
   return pManager->isLoggedOn();
}

long AwdInterface::logon( const DString &operatorID,
                          const DString &password,
                          const DString &newPassword )
{
   InterfaceManager *pManager = InterfaceManager::getManager();
   return pManager->logon( operatorID, password, newPassword );
}

long AwdInterface::logoff()
{
   InterfaceManager *pManager = InterfaceManager::getManager();
   return pManager->logoff();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/diawdi/awdinterface.cpp-arc  $
// 
//    Rev 1.1   30 Jan 2008 14:20:50   kovacsro
// IN#1118094 - added an overloaded getStatusList method, in order to filter on queue, bussArea and wkType
// 
//    Rev 1.0   28 Jan 2008 13:18:16   kovacsro
// Initial revision.
// 
//    Rev 1.15   Oct 16 2001 15:03:44   dt21858
// Added stopCSD()
// Added selectItemInContainer()
//
//    Rev 1.14   Aug 23 2001 16:53:38   DT21858
// - Added overloaded method for insertItemInContainer().
//
//    Rev 1.13   Aug 13 2001 13:57:40   DT21858
// Added getImmediateChildren()
//
//    Rev 1.12   Aug 06 2001 15:57:02   DT21858
// - Sync up eith 1.7.2.10 branch (comments included below)
// - Added getWorkstationID(), getCountry() and implemented getQueueList()
//
//
//    Rev 1.11   Jun 04 2001 15:00:44   DT21858
// Sync-up with Infra 1.7
//
//    Rev 1.10   Feb 07 2001 09:14:42   dt21858
// Sync up with 1.7
//
//    Rev 1.9   Aug 27 1999 08:31:54   DMUM
// Constructor no longer throws exceptions
//
//    Rev 1.8   Aug 26 1999 12:58:40   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.7   Apr 09 1999 13:48:58   DMUM
// Sync up with 1.6.x
//
//    Rev 1.5.1.0   Mar 31 1999 13:19:20   DMUM
//
//
//    Rev 1.0.1.5   Feb 19 1999 07:48:30   DMUM
// Added lookupSource()
//
//    Rev 1.0.1.4   Feb 08 1999 15:16:52   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0.1.3   Jan 20 1999 16:40:36   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.2   Dec 11 1998 10:13:08   DMUM
// Added loadCSD()
//
//    Rev 1.0.1.1   Oct 01 1998 11:50:48   DMUM
//
//
//    Rev 1.2   Oct 01 1998 11:34:44   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.1   Sep 11 1998 11:57:34   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.0   29 Jul 1998 20:28:36   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.16   Mar 16 1998 15:46:32   dmum
// Added isItemInContainer method
//
//    Rev 1.15   Jan 19 1998 13:47:22   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.14   Dec 30 1997 11:24:46   dmum
// Added new methods
//
//    Rev 1.13   Dec 16 1997 11:29:46   dmum
// Added methods
//
//    Rev 1.12   10 Nov 1997 15:22:02   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.11   20 Sep 1997 11:55:24   dmum
// Now uses InterfaceManager to manage which AWD client to interface with
//
//    Rev 1.10   02 Sep 1997 15:39:16   dmum
// Now will determine which AWD version (2.2.3 or 2.3) to use.
//
//    Rev 1.9   24 Jul 1997 10:08:52   dmum
// Added tracing
//
//    Rev 1.8   01 Jul 1997 09:49:02   dmum
// Added method to return a valid list of queues
//
//    Rev 1.7   27 Jun 1997 14:37:18   dmum
// Renamed createAwdWork to createAwdTransaction
//
//    Rev 1.6   25 Jun 1997 08:38:52   dmum
// Added documentation
//
//    Rev 1.5   13 Jun 1997 17:23:24   dmum
// Added condition
//
//    Rev 1.4   May 27 1997 10:49:54   dmum
// Enhanced functionality
//
//    Rev 1.3   May 08 1997 16:10:04   dmum
// Added methods to get and set the queue
//
//    Rev 1.2   May 05 1997 11:39:46   dmum
// Added method to get operator id
//
//    Rev 1.1   Apr 25 1997 11:20:20   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:16:52   dmum
//
//
//

