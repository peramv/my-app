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
// ^FILE   : BFAwdBaseInterface.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 31 Mar 97
//
// ----------------------------------------------------------
//
// ^CLASS    : BFAwdBaseInterface
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define BFAWDI_DLL

#include <srcprag.h>
#include "bfawdbaseinterface.hpp"
#include <conditionmanager.hpp>
#include <tracerclient.hpp>
#include "diawdcnd.h"
#include <base.h>

//******************************************************************************
//              Public Methods
//******************************************************************************

const I_CHAR *BFAwdBaseInterface::getGroup()
{
   return(I_("#AIG"));
}

BFAwdBaseInterface::BFAwdBaseInterface()
{
   ; // Do Nothing
}

BFAwdBaseInterface::~BFAwdBaseInterface()
{
   ; // Do Nothing
}

string_vector BFAwdBaseInterface::getBusinessAreaList()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getBusinessAreaList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getBusinessAreaList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getCaseWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getCaseWorkTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getTransWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getTransWorkTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getSourceTypeList( const DString & busarea )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getSourceTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getStatusList()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getStatusList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getStatusList( const BFAwdKey *pKey )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getStatusList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getStatusList( const BFAwdKey *pKey, const DString &strBussArea, const DString &strWkType  )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getStatusList(const BFAwdKey *,const DString &,const DString &)") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

string_vector BFAwdBaseInterface::getQueueList( const char type )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getQueueList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return(dummy);
}

BFDataObjMap& BFAwdBaseInterface::getAwdFieldList()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getAwdFieldList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(m_dummy_map);
}

bool BFAwdBaseInterface::lookupWork( const CriteriaVector &criteria )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lookupWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false);
}

ResultVector BFAwdBaseInterface::lookupWork( const CriteriaVector &criteria,
                                             bool &more,
                                             const unsigned long max )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lookupWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return(dummy);
}

bool BFAwdBaseInterface::lookupSource( const CriteriaVector &criteria )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lookupWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false);
}

ResultVector BFAwdBaseInterface::lookupSource( const CriteriaVector &criteria,
                                               bool &more,
                                               const unsigned long max )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lookupWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return(dummy);
}

ResultVector BFAwdBaseInterface::lookupMore( bool &more )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lookupMoreWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return(dummy);
}

bool BFAwdBaseInterface::loadCSD( BFAwdData &awdData )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::loadCSD()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::stopCSD( const BFAwdKey* pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::stopCSD()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::showAwdContainer( bool bShow )
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("BFAwdBaseInterface::showAwdContainer( bool bHide )") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::getAllChildren( const BFAwdKey* pKey,
                                       BFAwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::getAllChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::getImmediateChildren( const BFAwdKey* pKey,
                                             BFAwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAllChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::showAwdServiceWindow( const BFAwdKey *pKey,
                                             const DString &serviceName,
                                             bool bShow )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::showAwdServiceWindow()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::hasActiveService( const BFAwdKey *pKey,
                                         const DString &serviceName )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::hasActiveService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::openAwdContainer()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::openAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::locateAwdContainer( const BFAwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::locateAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::isLocked( const BFAwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::isLocked()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::insertItemInContainer( const BFAwdKey *pKey, bool lock )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::insertItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::insertItemInContainer( const BFAwdKey *pKey,
                                              const BFAwdKey *pParent,
                                              bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::insertItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::isItemInContainer( const BFAwdKey *pKey )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::isItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::closeAwdContainer()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::closeAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::selectItemInContainer( const BFAwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::selectItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::clearAwdContainer()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::clearAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::expandContainerItemDown( const BFAwdKey *pKey )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::clearAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::createAwdTransaction( BFAwdData &awdData, bool lock )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::createAwdWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::createAwdSource( const BFAwdData &awdData,
                                          const BFAwdSource::ObjectFormat format,
                                          const DString &strFile,
                                          BFAwdSource **ppSource,
                                          bool lock )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::createAwdSource()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::createAwdCase( BFAwdData &awdData, bool lock )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::createAwdCase()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::createRelationship( const BFAwdKey *pParent,
                                             const BFAwdKey *pChild )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::createRelationship()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::lockAwdObject( const BFAwdKey *pKey, bool lock )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::lockAwdObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::hasCaseForParent( const BFAwdKey *pKey, BFAwdKey **ppParent )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::hasCaseForParent()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::hasSourceForChild( const BFAwdKey *pKey, BFAwdKey **ppChild )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::hasSourceForChild()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::hasChildren( const BFAwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::hasChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::addComment( const BFAwdKey *pKey,
                                     const DString &comment )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::addComment()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::beginListenCreateObjects()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::beginListenCreateObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

BFAwdKeyVector BFAwdBaseInterface::endListenCreateObjects()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::endListenCreateObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   BFAwdKeyVector dummy;
   return(dummy); // Do Nothing
}

BFAwdKey * BFAwdBaseInterface::newAwdKey( const DString &createDateTime,
                                          const DString &recordCode,
                                          const DString &createNode )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::newAwdKey()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(NULL); // Do Nothing
}

bool BFAwdBaseInterface::retrieveData( const BFAwdKey *pKey, BFAwdData &awdData )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::retrieveData()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::retrieveDataLite( const BFAwdKey *pKey, BFAwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::retrieveDataLite()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool BFAwdBaseInterface::retrieveSource( const BFAwdKey *pKey,
                                         BFAwdSource **ppSource )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::retrieveSource()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::startService( const BFAwdKey *pKey,
                                       const DString &strServiceName )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::startService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::stopService( const BFAwdKey *pKey,
                                      const DString &strServiceName )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::stopService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::updateAwdObject( BFAwdData &awdData )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::updateAwdObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::getAwdWork( BFAwdData &awdData )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getAwdWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::getAwdWorkObjects( BFAwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getAwdWorkObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

bool BFAwdBaseInterface::doubleClickContainerItem( const BFAwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("BFAwdBaseInterface::doubleClickContainerItem()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

BFAwdKey * BFAwdBaseInterface::getCurrentContainerSelection()
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("BFAwdBaseInterface::getCurrentContainerSelection()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return NULL; // Do Nothing
}

DString BFAwdBaseInterface::getQueue( const BFAwdKey *pKey )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getQueue()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_queue( I_("__NO_Q__") );

   return(no_queue);
}

bool BFAwdBaseInterface::setQueue( const BFAwdKey *pKey, const DString &queue )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::setQueue()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false); // Do Nothing
}

DString BFAwdBaseInterface::getOperatorID()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_id( I_("_NO_ID_") );

   return(no_id);
}


unsigned long BFAwdBaseInterface::getCountry()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return 0;
}

DString BFAwdBaseInterface::getWorkstationID()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_id( I_("_NO_ID_") );

   return no_id;
}

DString BFAwdBaseInterface::getServerDateTime()
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::getServerDateTime()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_dateTime( I_("") );

   return(no_dateTime);
}



string_vector BFAwdBaseInterface::getSuspendCodeList()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("BFAwdBaseInterface::getSuspendCodeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;
   return dummy;
}

bool BFAwdBaseInterface::suspendWorkObject( const BFAwdKey *pKey,
                                            const DString &activateDateTime,
                                            const DString &suspendCode )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::suspendWorkObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false);
}

bool BFAwdBaseInterface::unSuspendWorkObject(const BFAwdKey *pKey )
{
   MAKEFRAME( DICORE_CONDITION, I_("BFAwdBaseInterface::unSuspendWorkObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return(false);
}


//******************************************************************************
//              Protected Methods
//******************************************************************************




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfawdi/bfawdbaseinterface.cpp-arc  $
//
//   Rev 1.4   01 Feb 2008 08:55:22   kovacsro
//IN#1118094&1114586 - added an overloaded getStatusList method to filter the results on the queue, busArea and wkType
//
//   Rev 1.3   Apr 20 2004 10:46:36   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.2   Mar 20 2003 15:05:30   PURDYECH
// MAKEFRAME was using an incompatible error module.
// 
//    Rev 1.1   Oct 09 2002 17:39:52   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:10:56   SMITHDAV
// Initial revision.
// 
//    Rev 1.10   Feb 07 2001 09:14:38   dt21858
// Sync up with 1.7
//
//    Rev 1.9   Mar 24 2000 12:30:52   DMUM
// Shortened literal for getGroup()
//
//    Rev 1.8   Sep 30 1999 09:20:24   DMUM
// Started using SingletonBase
//
//    Rev 1.7   Aug 26 1999 12:58:36   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.5   Apr 09 1999 13:48:56   DMUM
// Sync up with 1.6.x
//
//    Rev 1.3.1.0   Mar 31 1999 13:19:16   DMUM
//
//
//    Rev 1.0.1.5   Feb 19 1999 07:48:14   DMUM
// Added lookupSource()
//
//    Rev 1.0.1.4   Feb 08 1999 15:18:00   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0.1.3   Jan 20 1999 16:40:10   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.2   Dec 11 1998 10:13:32   DMUM
// Added loadCSD()
//
//    Rev 1.0.1.1   Oct 01 1998 11:51:06   DMUM
//
//
//    Rev 1.2   Oct 01 1998 11:35:16   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.1   Sep 11 1998 11:58:18   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.0   29 Jul 1998 20:28:52   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.14   Mar 16 1998 15:46:58   dmum
// Added isItemInContainer method
//
//    Rev 1.13   Jan 19 1998 13:47:56   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.12   Dec 30 1997 11:18:36   dmum
// Added new methods
//
//    Rev 1.11   Dec 16 1997 11:25:44   dmum
// New Methods
//
//    Rev 1.10   10 Nov 1997 15:23:00   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.9   02 Sep 1997 15:04:22   dmum
// Added new method getAwdFieldList()
//
//    Rev 1.8   24 Jul 1997 10:07:44   dmum
// Added tracing
//
//    Rev 1.7   01 Jul 1997 09:50:46   dmum
// Added method to return a valid list of queues
//
//    Rev 1.6   27 Jun 1997 14:38:38   dmum
// Renamed createAwdWork to createAwdTransaction
//
//    Rev 1.5   13 Jun 1997 14:48:30   dmum
// Added condition
//
//    Rev 1.4   May 22 1997 10:02:56   dmum
// Expanded functionality
//
//    Rev 1.3   May 08 1997 16:12:54   dmum
// Added methods to get and set the queue
//
//    Rev 1.2   May 05 1997 10:51:48   dmum
// Added method to return operator id
//
//    Rev 1.1   Apr 25 1997 11:20:52   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:18:36   dmum
//
//
//