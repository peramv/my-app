#pragma once

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
// ^FILE   : BFAwdBaseInterface.hpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 31 Mar 97
//
// ^CLASS  : BFAwdBaseInterface
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//    Refer to "AwdInterface.hpp" for a description of public member functions
//
//******************************************************************************

#include <commonport.h>
#include <bfawdi\bfawddata.hpp>
#include <bfawdi\bfawdlookupcriteria.hpp>
#include <bfawdi\bfawdsource.hpp>
#include <bfdata\bfdata.hpp>
#include <commontemplates.h>
#include <bfawdi\bfawdtemplates.hpp>

#undef BFAWDI_LINKAGE
#ifdef BFAWDI_DLL
   #define BFAWDI_LINKAGE CLASS_EXPORT
#else
   #define BFAWDI_LINKAGE CLASS_IMPORT
#endif

class BFAwdKey;

/**
 * Class used for implementing the bridge pattern for BFAwdInterface.  An
 * implementation class will inherit from this class.
 *
 * @see BFAwdInterface
 */
class BFAWDI_LINKAGE BFAwdBaseInterface
{
   // Define group for singltons
public:
   static const I_CHAR *getGroup();

   // Constructor & Destructor
public:
   BFAwdBaseInterface();
   virtual ~BFAwdBaseInterface();

   // Public methods
public:
   virtual string_vector getBusinessAreaList();

   virtual string_vector getWorkTypeList( const DString &busarea );

   virtual string_vector getCaseWorkTypeList( const DString &busarea );

   virtual string_vector getTransWorkTypeList( const DString &busarea );

   virtual string_vector getSourceTypeList( const DString & busarea );

   virtual string_vector getStatusList();

   virtual string_vector getStatusList( const BFAwdKey *pKey );

   virtual string_vector getStatusList( const BFAwdKey *pKey, const DString &strBussArea, const DString &strWkType );

   virtual string_vector getQueueList( const char type );

   virtual BFDataObjMap& getAwdFieldList();

   virtual bool lookupWork( const CriteriaVector &criteria );

   virtual ResultVector lookupWork( const CriteriaVector &criteria,
                                    bool &more,
                                    const unsigned long max );

   virtual bool lookupSource( const CriteriaVector &criteria );

   virtual ResultVector lookupSource( const CriteriaVector &criteria,
                                      bool &more,
                                      const unsigned long max );

   virtual ResultVector lookupMore( bool &more );

   virtual bool loadCSD( BFAwdData &awdData );

   virtual bool stopCSD( const BFAwdKey *pKey );

   virtual bool showAwdContainer( bool bShow );

   virtual bool hasActiveService( const BFAwdKey *pKey,
                                  const DString &serviceName );

   virtual bool getAllChildren( const BFAwdKey* pKey,
                             BFAwdKeyVector &awdKeyVector );

   virtual bool getImmediateChildren( const BFAwdKey* pKey,
                                   BFAwdKeyVector &awdKeyVector );

   virtual bool showAwdServiceWindow( const BFAwdKey *pKey,
                                   const DString &serviceName,
                                   bool bShow );

   virtual bool openAwdContainer();

   virtual bool locateAwdContainer( const BFAwdKey *pKey );

   virtual bool isLocked( const BFAwdKey *pKey );

   virtual bool insertItemInContainer( const BFAwdKey *pKey, bool lock );

   virtual bool insertItemInContainer( const BFAwdKey *pKey,
                                       const BFAwdKey *pParent,
                                       bool lock );

   virtual bool isItemInContainer( const BFAwdKey *pKey );

   virtual bool selectItemInContainer( const BFAwdKey *pKey );

   virtual bool closeAwdContainer();

   virtual bool clearAwdContainer();

   virtual bool expandContainerItemDown( const BFAwdKey *pKey );

   virtual bool createAwdTransaction( BFAwdData &awdData, bool lock );

   virtual bool createAwdCase( BFAwdData &awdData, bool lock );

   virtual bool createAwdSource( const BFAwdData &awdData,
                                 const BFAwdSource::ObjectFormat format,
                                 const DString &strFile,
                                 BFAwdSource **ppSource,
                                 bool lock );

   virtual bool createRelationship( const BFAwdKey *pParent,
                                    const BFAwdKey *pChild );

   virtual bool lockAwdObject( const BFAwdKey *pKey, bool lock );

   virtual bool hasCaseForParent( const BFAwdKey *pKey, BFAwdKey **ppParent );

   virtual bool hasSourceForChild( const BFAwdKey *pKey, BFAwdKey **ppChild );

   virtual bool hasChildren( const BFAwdKey *pKey );

   virtual bool addComment( const BFAwdKey *pKey, const DString &comment );

   virtual bool beginListenCreateObjects();

   virtual BFAwdKeyVector endListenCreateObjects();

   virtual BFAwdKey * newAwdKey( const DString &createDateTime,
                                 const DString &recordCode,
                                 const DString &createNode );

   virtual bool retrieveData( const BFAwdKey *pKey, BFAwdData &awdData );

   virtual bool retrieveDataLite( const BFAwdKey *pKey, BFAwdData &awdData );

   virtual bool retrieveSource( const BFAwdKey *pKey, BFAwdSource **ppSource );

   virtual bool startService( const BFAwdKey *pKey,
                              const DString &strServiceName );

   virtual bool stopService( const BFAwdKey *pKey,
                             const DString &strServiceName );

   virtual bool updateAwdObject( BFAwdData &awdData );

   virtual bool getAwdWork( BFAwdData &awdData );

   virtual bool getAwdWorkObjects( BFAwdKeyVector &awdKeyVector );

   virtual bool doubleClickContainerItem( const BFAwdKey *pKey );

   virtual BFAwdKey * getCurrentContainerSelection();

   virtual DString getQueue( const BFAwdKey *pKey );

   virtual bool setQueue( const BFAwdKey *pKey, const DString &queue );

   virtual DString getOperatorID();

   virtual unsigned long getCountry();

   virtual DString getWorkstationID();

   virtual DString getServerDateTime();

   virtual string_vector getSuspendCodeList();

   virtual bool suspendWorkObject( const BFAwdKey *pKey,
                                   const DString &activateDateTime,
                                   const DString& suspendCode );

   virtual bool unSuspendWorkObject( const BFAwdKey *pKey );

private:
   BFDataObjMap m_dummy_map;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfawdi/bfawdbaseinterface.hpp-arc  $
//
//   Rev 1.3   01 Feb 2008 08:55:08   kovacsro
//IN#1118094&1114586 - added an overloaded getStatusList method to filter the results on the queue, busArea and wkType
//
//   Rev 1.2   Apr 20 2004 10:46:58   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
//
//   Rev 1.1   Oct 09 2002 17:39:52   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:18   SMITHDAV
//Initial revision.
// 
//    Rev 1.11   Feb 07 2001 09:14:44   dt21858
// Sync up with 1.7
//
//    Rev 1.10   Apr 24 2000 10:52:18   DMUM
// Comments to JavaDoc
//
//    Rev 1.9   Sep 30 1999 09:20:32   DMUM
// Started using SingletonBase
//
//    Rev 1.8   Aug 26 1999 12:58:46   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.7   Apr 09 1999 13:26:14   DMUM
// Sync up with 1.6.x
//
//    Rev 1.5.1.0   Mar 31 1999 13:14:46   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.5   Feb 19 1999 07:47:28   DMUM
// Added lookupSource() and fixed BFAwdTemplates
//
//    Rev 1.0.1.4   Feb 08 1999 15:16:10   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0.1.3   Jan 20 1999 16:39:08   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.2   Dec 11 1998 10:22:46   DMUM
// Added loadCSD()
//
//    Rev 1.0.1.1   Oct 01 1998 11:49:58   DMUM
//
//
//    Rev 1.2   Oct 01 1998 11:35:28   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.1   Sep 11 1998 11:58:32   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.0   29 Jul 1998 20:36:02   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.14   Mar 16 1998 15:46:48   dmum
// Added isItemInContainer method
//
//    Rev 1.13   Jan 19 1998 13:48:08   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.12   Dec 30 1997 11:19:14   dmum
// Added new methods
//
//    Rev 1.11   Dec 16 1997 11:26:50   dmum
// Added methods
//
//    Rev 1.10   10 Nov 1997 15:01:24   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.9   02 Sep 1997 15:04:00   dmum
// Added new method getAwdFieldList()
//
//    Rev 1.8   01 Jul 1997 09:48:14   dmum
// Added method to return a valid list of queues
//
//    Rev 1.7   27 Jun 1997 14:21:20   dmum
// Renamed createAwdWork to createAwdTransaction.
//
//
//    Rev 1.6   24 Jun 1997 12:40:56   dmum
// Added documentation
//
//    Rev 1.5   13 Jun 1997 19:08:08   dmum
// Added condition
//
//    Rev 1.4   May 22 1997 10:02:12   dmum
// Expanded functionality
//
//    Rev 1.3   May 08 1997 16:08:32   dmum
// Added methods to get and set the queue
//
//    Rev 1.2   May 05 1997 10:40:42   dmum
// Added method to return operator id
//
//    Rev 1.1   Apr 25 1997 11:21:22   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:20:00   dmum
//
//
//

