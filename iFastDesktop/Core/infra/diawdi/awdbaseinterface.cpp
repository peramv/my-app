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
// ^FILE   : AwdBaseInterface.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 31 Mar 97
//
// ----------------------------------------------------------
//
// ^CLASS    : AwdBaseInterface
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DIAWDI_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef AWDBASEINTERFACE_HPP
   #include "awdbaseinterface.hpp"
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

const I_CHAR *AwdBaseInterface::getGroup()
{
   return I_("#AIG");
}

AwdBaseInterface::AwdBaseInterface()
{
   ; // Do Nothing
}

AwdBaseInterface::~AwdBaseInterface()
{
   ; // Do Nothing
}

string_vector AwdBaseInterface::getBusinessAreaList()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getBusinessAreaList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getBusinessAreaList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getCaseWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getCaseWorkTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getTransWorkTypeList( const DString & busarea )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getTransWorkTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getSourceTypeList( const DString & busarea )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getSourceTypeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getStatusList()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getStatusList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getStatusList( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getStatusList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getStatusList( const AwdKey *pKey, const DString &strBussArea, const DString &strWkType )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getStatusList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

string_vector AwdBaseInterface::getQueueList( const char type )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getQueueList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;

   return dummy;
}

data_obj_map & AwdBaseInterface::getAwdFieldList()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAwdFieldList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return m_dummy_map;
}

bool AwdBaseInterface::lookupWork( const CriteriaVector &criteria )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lookupWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false;
}

ResultVector AwdBaseInterface::lookupWork( const CriteriaVector &criteria,
                                                 bool &more,
                                           const unsigned long max )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lookupWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return dummy;
}

bool AwdBaseInterface::lookupSource( const CriteriaVector &criteria )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lookupWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false;
}

ResultVector AwdBaseInterface::lookupSource( const CriteriaVector &criteria,
                                                   bool &more,
                                             const unsigned long max )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lookupWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return dummy;
}

ResultVector AwdBaseInterface::lookupMore( bool &more )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lookupMoreWorkS()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   ResultVector dummy;

   return dummy;
}

bool AwdBaseInterface::loadCSD( AwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::loadCSD()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::stopCSD( const AwdKey* pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::stopCSD()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::showAwdContainer( bool bShow )
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("AwdBaseInterface::showAwdContainer( bool bHide )") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::getAllChildren( const AwdKey* pKey,
                                       AwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAllChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::getImmediateChildren( const AwdKey* pKey,
                                             AwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAllChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::showAwdServiceWindow( const AwdKey *pKey,
                                             const DString &serviceName,
                                             bool bShow )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::showAwdServiceWindow()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::hasActiveService( const AwdKey *pKey,
                                         const DString &serviceName )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::hasActiveService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::openAwdContainer()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::openAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::locateAwdContainer( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::locateAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::isLocked( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::isLocked()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::insertItemInContainer( const AwdKey *pKey, bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::insertItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::insertItemInContainer( const AwdKey *pKey,
                                              const AwdKey *pParent,
                                              bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::insertItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::isItemInContainer( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::isItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::selectItemInContainer( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::selectItemInContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::closeAwdContainer()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::closeAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::clearAwdContainer()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::clearAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::expandContainerItemDown( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::clearAwdContainer()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::createAwdTransaction( AwdData &awdData, bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::createAwdWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::createAwdSource( const AwdData &awdData,
                                        const AwdSource::ObjectFormat format,
                                        const DString &strFile,
                                        AwdSource **ppSource,
                                        bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::createAwdSource()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::createAwdCase( AwdData &awdData, bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::createAwdCase()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::createRelationship( const AwdKey *pParent,
                                           const AwdKey *pChild )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::createRelationship()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::lockAwdObject( const AwdKey *pKey, bool lock )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::lockAwdObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::hasCaseForParent( const AwdKey *pKey, AwdKey **ppParent )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::hasCaseForParent()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::hasSourceForChild( const AwdKey *pKey, AwdKey **ppChild )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::hasSourceForChild()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::hasChildren( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::hasChildren()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::addComment( const AwdKey *pKey,
                                   const DString &comment )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::addComment()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::beginListenCreateObjects()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::beginListenCreateObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

AwdKeyVector AwdBaseInterface::endListenCreateObjects()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::endListenCreateObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   AwdKeyVector dummy;
   return dummy; // Do Nothing
}

AwdKey * AwdBaseInterface::newAwdKey( const DString &createDateTime,
                                      const DString &recordCode,
                                      const DString &createNode )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::newAwdKey()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return NULL; // Do Nothing
}

bool AwdBaseInterface::retrieveData( const AwdKey *pKey, AwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::retrieveData()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::retrieveDataLite( const AwdKey *pKey, AwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::retrieveDataLite()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::retrieveSource( const AwdKey *pKey,
                                       AwdSource **ppSource )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::retrieveSource()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::startService( const AwdKey *pKey,
                                     const DString &strServiceName )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::startService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::stopService( const AwdKey *pKey,
                                    const DString &strServiceName )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::stopService()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::updateAwdObject( AwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::updateAwdObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::getAwdWork( AwdData &awdData )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAwdWork()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::getAwdWorkObjects( AwdKeyVector &awdKeyVector )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getAwdWorkObjects()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

bool AwdBaseInterface::doubleClickContainerItem( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("AwdBaseInterface::doubleClickContainerItem()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

AwdKey * AwdBaseInterface::getCurrentContainerSelection()
{
   MAKEFRAME( DIAWDI_CONDITION,
              I_("AwdBaseInterface::getCurrentContainerSelection()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return NULL; // Do Nothing
}

DString AwdBaseInterface::getQueue( const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getQueue()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_queue( I_("__NO_Q__") );

   return no_queue;
}

bool AwdBaseInterface::setQueue( const AwdKey *pKey, const DString &queue )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::setQueue()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false; // Do Nothing
}

DString AwdBaseInterface::getOperatorID()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_id( I_("_NO_ID_") );

   return no_id;
}

unsigned long AwdBaseInterface::getCountry()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return 0;
}

DString AwdBaseInterface::getWorkstationID()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getOperatorID()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_id( I_("_NO_ID_") );

   return no_id;
}

DString AwdBaseInterface::getServerDateTime()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getServerDateTime()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   DString no_dateTime( I_("") );

   return no_dateTime;
}



string_vector AwdBaseInterface::getSuspendCodeList()
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::getSuspendCodeList()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   string_vector dummy;
   return dummy;
}



bool AwdBaseInterface::suspendWorkObject( const AwdKey *pKey,
                                          const DString &activateDateTime,
                                          const DString &suspendCode )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::suspendWorkObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false;
}

bool AwdBaseInterface::unSuspendWorkObject(const AwdKey *pKey )
{
   MAKEFRAME( DIAWDI_CONDITION, I_("AwdBaseInterface::unSuspendWorkObject()") );
   ADDCONDITIONFROMBASE( VIRTUAL_BASE_METHOD_NOT_SUPPORTED );

   return false;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************




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
// $Log:   Y:/VCS/iFastAWD/diawdi/awdbaseinterface.cpp-arc  $
// 
//    Rev 1.1   30 Jan 2008 14:20:46   kovacsro
// IN#1118094 - added an overloaded getStatusList method, in order to filter on queue, bussArea and wkType
// 
//    Rev 1.0   28 Jan 2008 13:18:14   kovacsro
// Initial revision.
// 
//    Rev 1.15   Oct 16 2001 15:03:40   dt21858
// Added stopCSD()
// Added selectItemInContainer()
//
//    Rev 1.14   Aug 23 2001 16:53:34   DT21858
// - Added overloaded method for insertItemInContainer().
//
//    Rev 1.13   Aug 13 2001 13:57:36   DT21858
// Added getImmediateChildren()
//
//    Rev 1.12   Aug 06 2001 15:56:56   DT21858
// - Sync up eith 1.7.2.10 branch (comments included below)
// - Added getWorkstationID(), getCountry() and implemented getQueueList()
//
//
//    Rev 1.11   Jun 04 2001 15:00:40   DT21858
// Sync-up with Infra 1.7
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