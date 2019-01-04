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
// ^FILE   : BFAwdInterface.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 2 Apr 97
//
// ----------------------------------------------------------
//
// ^CLASS    : BFAwdInterface
//
// ^MEMBER VARIABLES :
//
//    BFAwdBaseInterface *pBase - pointer to base interface.
//
// ^CODING COMMENTS  :  pBase is constructed as an inherited class of
//                      BFAwdBaseInterface.  A DLL supporting the inherited
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
#define BFAWDI_DLL

#include <srcprag.h>
#include "bfawdinterface.hpp"

#include <win32\bfinterfacemanager.hpp>
#include <conditionmanager.hpp>
#include <tracerclient.hpp>
#include "diawdcnd.h"
#include <base.h>

//******************************************************************************
//              Public Methods
//******************************************************************************

BFAwdInterface::BFAwdInterface()
: m_pBase( NULL ),
m_bValid( false )
{
   MAKEFRAMECONSTRUCTOR2( DIAWDI_CONDITION, I_("BFAwdInterface"),
                          I_("BFAwdInterface()") )

   try
   {
      BFInterfaceManager *pManager = BFInterfaceManager::getManager();
      m_pBase = pManager->newInterface();
      m_bValid = true;
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce )
      m_pBase = NULL;
   }
   catch( ... )
   {
      m_pBase = NULL;
   }

   if( NULL == m_pBase )
   {
      m_pBase = new BFAwdBaseInterface;
   }

   PROMOTECONDITIONS();
}


BFAwdInterface::~BFAwdInterface()
{
   TRACE_DESTRUCTOR( I_("BFAwdInterface") )
   delete m_pBase;
}

string_vector BFAwdInterface::getBusinessAreaList()
{
   return(m_pBase->getBusinessAreaList());
}

string_vector BFAwdInterface::getWorkTypeList( const DString & busarea )
{
   return(m_pBase->getWorkTypeList( busarea ));
}

string_vector BFAwdInterface::getCaseWorkTypeList( const DString & busarea )
{
   return(m_pBase->getCaseWorkTypeList( busarea ));
}

string_vector BFAwdInterface::getTransWorkTypeList( const DString & busarea )
{
   return(m_pBase->getTransWorkTypeList( busarea ));
}

string_vector BFAwdInterface::getSourceTypeList( const DString & busarea )
{
   return(m_pBase->getSourceTypeList( busarea ));
}

string_vector BFAwdInterface::getStatusList()
{
   return(m_pBase->getStatusList());
}

string_vector BFAwdInterface::getStatusList( const BFAwdKey *pKey )
{
   return(m_pBase->getStatusList( pKey ));
}

string_vector BFAwdInterface::getStatusList( const BFAwdKey *pKey, const DString &strBussArea, const DString &strWkType  )
{
   return(m_pBase->getStatusList( pKey, strBussArea, strWkType ));
}

string_vector BFAwdInterface::getQueueList( const QueueType type )
{
   return(m_pBase->getQueueList( type ));
}

BFDataObjMap& BFAwdInterface::getAwdFieldList()
{
   return(m_pBase->getAwdFieldList());
}

bool BFAwdInterface::lookupWork( const CriteriaVector &criteria )
{
   return(m_pBase->lookupWork( criteria ));
}

ResultVector BFAwdInterface::lookupWork( const CriteriaVector &criteria,
                                         bool &more,
                                         const unsigned long max )
{
   return(m_pBase->lookupWork( criteria, more, max ));
}

bool BFAwdInterface::lookupSource( const CriteriaVector &criteria )
{
   return(m_pBase->lookupSource( criteria ));
}

ResultVector BFAwdInterface::lookupSource( const CriteriaVector &criteria,
                                           bool &more,
                                           const unsigned long max )
{
   return(m_pBase->lookupSource( criteria, more, max ));
}

ResultVector BFAwdInterface::lookupMore( bool &more )
{
   return(m_pBase->lookupMore( more ));
}

bool BFAwdInterface::loadCSD( BFAwdData &awdData )
{
   return(m_pBase->loadCSD( awdData ));
}

bool BFAwdInterface::stopCSD( const BFAwdKey *pKey )
{
   return m_pBase->stopCSD( pKey );
}

bool BFAwdInterface::showAwdContainer( bool bShow )
{
   return m_pBase->showAwdContainer( bShow );
}

bool BFAwdInterface::hasActiveService( const BFAwdKey *pKey,
                                     const DString &serviceName )
{
   return m_pBase->hasActiveService( pKey, serviceName );
}

bool BFAwdInterface::getAllChildren( const BFAwdKey* pKey,
                                   BFAwdKeyVector &awdKeyVector )
{
   return m_pBase->getAllChildren( pKey, awdKeyVector );
}

bool BFAwdInterface::getImmediateChildren( const BFAwdKey* pKey,
                                         BFAwdKeyVector &awdKeyVector )
{
   return m_pBase->getImmediateChildren( pKey, awdKeyVector );
}

bool BFAwdInterface::showAwdServiceWindow( const BFAwdKey *pKey,
                                         const DString &serviceName,
                                         bool bShow )
{
   return m_pBase->showAwdServiceWindow( pKey,
                                        serviceName,
                                        bShow );
}

bool BFAwdInterface::openAwdContainer()
{
   return(m_pBase->openAwdContainer());
}

bool BFAwdInterface::locateAwdContainer( const BFAwdKey *pKey )
{
   return m_pBase->locateAwdContainer( pKey );
}

bool BFAwdInterface::isLocked( const BFAwdKey *pKey )
{
   return m_pBase->isLocked( pKey );
}

bool BFAwdInterface::insertItemInContainer( const BFAwdKey *pKey, bool lock )
{
   return(m_pBase->insertItemInContainer( pKey, lock ));
}

bool BFAwdInterface::insertItemInContainer( const BFAwdKey *pKey,
                                          const BFAwdKey *pParent,
                                          bool lock )
{
   return m_pBase->insertItemInContainer( pKey, pParent, lock );
}

bool BFAwdInterface::isItemInContainer( const BFAwdKey *pKey )
{
   return(m_pBase->isItemInContainer( pKey ));
}

bool BFAwdInterface::selectItemInContainer( const BFAwdKey *pKey )
{
   return m_pBase->selectItemInContainer( pKey );
}

bool BFAwdInterface::closeAwdContainer()
{
   return(m_pBase->closeAwdContainer());
}

bool BFAwdInterface::clearAwdContainer()
{
   return(m_pBase->clearAwdContainer());
}

bool BFAwdInterface::expandContainerItemDown( const BFAwdKey *pKey )
{
   return(m_pBase->expandContainerItemDown( pKey ));
}

bool BFAwdInterface::createAwdTransaction( BFAwdData &awdData, bool lock )
{
   return(m_pBase->createAwdTransaction( awdData, lock ));
}

bool BFAwdInterface::createAwdCase( BFAwdData &awdData, bool lock )
{
   return(m_pBase->createAwdCase( awdData, lock ));
}

bool BFAwdInterface::createAwdSource( const BFAwdData &awdData,
                                      const BFAwdSource::ObjectFormat format,
                                      const DString &strFile,
                                      BFAwdSource **ppSource,
                                      bool lock )
{
   return(m_pBase->createAwdSource( awdData, format, strFile, ppSource, lock ));
}

bool BFAwdInterface::createRelationship( const BFAwdKey *pParent,
                                         const BFAwdKey *pChild )
{
   return(m_pBase->createRelationship( pParent, pChild ));
}

bool BFAwdInterface::lockAwdObject( const BFAwdKey *pKey, bool lock )
{
   return(m_pBase->lockAwdObject( pKey, lock ));
}

bool BFAwdInterface::hasCaseForParent( const BFAwdKey *pKey, BFAwdKey **ppParent )
{
   return(m_pBase->hasCaseForParent( pKey, ppParent ));
}

bool BFAwdInterface::hasChildren( const BFAwdKey *pKey )
{
   return m_pBase->hasChildren( pKey );
}

bool BFAwdInterface::hasSourceForChild( const BFAwdKey *pKey, BFAwdKey **ppChild )
{
   return(m_pBase->hasSourceForChild( pKey, ppChild ));
}

bool BFAwdInterface::addComment( const BFAwdKey *pKey, const DString &comment )
{
   return(m_pBase->addComment( pKey, comment ));
}

bool BFAwdInterface::beginListenCreateObjects()
{
   return(m_pBase->beginListenCreateObjects());
}

BFAwdKeyVector BFAwdInterface::endListenCreateObjects()
{
   return(m_pBase->endListenCreateObjects());
}

BFAwdKey * BFAwdInterface::newAwdKey( const DString &createDateTime,
                                      const DString &recordCode,
                                      const DString &createNode )
{
   return(m_pBase->newAwdKey( createDateTime, recordCode, createNode ));
}

bool BFAwdInterface::retrieveData( const BFAwdKey *pKey, BFAwdData &awdData )
{
   return(m_pBase->retrieveData( pKey, awdData ));
}

bool BFAwdInterface::retrieveDataLite( const BFAwdKey *pKey,
                                     BFAwdData &awdData )
{
   return m_pBase->retrieveDataLite( pKey, awdData );
}

bool BFAwdInterface::retrieveSource( const BFAwdKey *pKey,
                                     BFAwdSource **ppSource )
{
   return(m_pBase->retrieveSource( pKey, ppSource ));
}

bool BFAwdInterface::startService( const BFAwdKey *pKey,
                                   const DString &strServiceName )
{
   return(m_pBase->startService( pKey, strServiceName ));
}

bool BFAwdInterface::stopService( const BFAwdKey *pKey,
                                  const DString &strServiceName )
{
   return(m_pBase->stopService( pKey, strServiceName ));
}

bool BFAwdInterface::updateAwdObject( BFAwdData &awdData )
{
   return(m_pBase->updateAwdObject( awdData ));
}

bool BFAwdInterface::getAwdWork( BFAwdData &awdData )
{
   return(m_pBase->getAwdWork( awdData ));
}

bool BFAwdInterface::getAwdWorkObjects( BFAwdKeyVector &awdKeyVector )
{
   return(m_pBase->getAwdWorkObjects( awdKeyVector ));
}

bool BFAwdInterface::doubleClickContainerItem( const BFAwdKey *pKey )
{
   return m_pBase->doubleClickContainerItem( pKey );
}

BFAwdKey * BFAwdInterface::getCurrentContainerSelection()
{
   return m_pBase->getCurrentContainerSelection();
}

DString BFAwdInterface::getQueue( const BFAwdKey *pKey )
{
   return(m_pBase->getQueue( pKey ));
}

bool BFAwdInterface::setQueue( const BFAwdKey *pKey, const DString &queue )
{
   return(m_pBase->setQueue( pKey, queue ));
}

DString BFAwdInterface::getOperatorID()
{
   return(m_pBase->getOperatorID());
}

unsigned long BFAwdInterface::getCountry()
{
   return m_pBase->getCountry();
}

DString BFAwdInterface::getWorkstationID()
{
   return m_pBase->getWorkstationID();
}

DString BFAwdInterface::getServerDateTime()
{
   return(m_pBase->getServerDateTime());
}

string_vector BFAwdInterface::getSuspendCodeList()
{
   return m_pBase->getSuspendCodeList();
}

bool BFAwdInterface::suspendWorkObject( const BFAwdKey *pKey,
                                        const DString &activateDateTime,
                                        const DString &suspendCode )
{
   return(m_pBase->suspendWorkObject( pKey, activateDateTime,suspendCode ));
}

bool BFAwdInterface::unSuspendWorkObject( const BFAwdKey *pKey )
{
   return(m_pBase->unSuspendWorkObject( pKey ));
}

bool BFAwdInterface::isLoggedOn()
{
   BFInterfaceManager *pManager = BFInterfaceManager::getManager();
   return(pManager->isLoggedOn());
}

long BFAwdInterface::logon( const DString &operatorID,
                            const DString &password,
                            const DString &newPassword )
{
   BFInterfaceManager *pManager = BFInterfaceManager::getManager();
   return(pManager->logon( operatorID, password, newPassword ));
}

long BFAwdInterface::logoff()
{
   BFInterfaceManager *pManager = BFInterfaceManager::getManager();
   return(pManager->logoff());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfawdi/bfawdinterface.cpp-arc  $
//
//   Rev 1.3   01 Feb 2008 08:55:16   kovacsro
//IN#1118094&1114586 - added an overloaded getStatusList method to filter the results on the queue, busArea and wkType
//
//   Rev 1.2   Apr 20 2004 10:47:18   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.1   Oct 09 2002 17:39:52   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:08   SMITHDAV
// Initial revision.
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

