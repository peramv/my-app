#ifndef AWDBASEINTERFACE_HPP
#define AWDBASEINTERFACE_HPP

#pragma message( "including "__FILE__ )

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
// ^FILE   : AwdBaseInterface.hpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 31 Mar 97
//
// ^CLASS  : AwdBaseInterface
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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef AWDDATA_HPP
   #include "awddata.hpp"
#endif
#ifndef AWDLOOKUPCRITERIA_HPP
   #include "awdlookupcriteria.hpp"
#endif
#ifndef AWDSOURCE_HPP
   #include "awdsource.hpp"
#endif
#ifndef DATA_HPP
   #include "data.hpp"
#endif
#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif
#ifndef AWDTEMPLATES_HPP
   #include "awdtemplates.hpp"
#endif

#undef DIAWDI_LINKAGE
#ifdef DIAWDI_DLL
   #define DIAWDI_LINKAGE CLASS_EXPORT
#else
   #define DIAWDI_LINKAGE CLASS_IMPORT
#endif

class AwdKey;

/**
 * Class used for implementing the bridge pattern for AwdInterface.  An
 * implementation class will inherit from this class.
 *
 * @see AwdInterface
 */
class DIAWDI_LINKAGE AwdBaseInterface
{
   // Define group for singltons
   public:
      static const I_CHAR *getGroup();

   // Constructor & Destructor
   public:
      AwdBaseInterface();
      virtual ~AwdBaseInterface();

   // Public methods
   public:
      virtual string_vector getBusinessAreaList();

      virtual string_vector getWorkTypeList( const DString &busarea );

      virtual string_vector getCaseWorkTypeList( const DString &busarea );

      virtual string_vector getTransWorkTypeList( const DString &busarea );

      virtual string_vector getSourceTypeList( const DString & busarea );

      virtual string_vector getStatusList();

      virtual string_vector getStatusList( const AwdKey *pKey );

	  virtual string_vector getStatusList( const AwdKey *pKey, const DString &strBussArea, const DString &strWkType );

      virtual string_vector getQueueList( const char type );

      virtual data_obj_map & getAwdFieldList();

      virtual bool lookupWork( const CriteriaVector &criteria );

      virtual ResultVector lookupWork( const CriteriaVector &criteria,
                                             bool &more,
                                       const unsigned long max );

      virtual bool lookupSource( const CriteriaVector &criteria );

      virtual ResultVector lookupSource( const CriteriaVector &criteria,
                                               bool &more,
                                         const unsigned long max );

      virtual ResultVector lookupMore( bool &more );

      virtual bool loadCSD( AwdData &awdData );

      virtual bool stopCSD( const AwdKey *pKey );

      virtual bool showAwdContainer( bool bShow );

      virtual bool hasActiveService( const AwdKey *pKey,
                                     const DString &serviceName );

      virtual bool getAllChildren( const AwdKey* pKey,
                                   AwdKeyVector &awdKeyVector );

      virtual bool getImmediateChildren( const AwdKey* pKey,
                                         AwdKeyVector &awdKeyVector );

      virtual bool showAwdServiceWindow( const AwdKey *pKey,
                                         const DString &serviceName,
                                         bool bShow );

      virtual bool openAwdContainer();

      virtual bool locateAwdContainer( const AwdKey *pKey );

      virtual bool isLocked( const AwdKey *pKey );

      virtual bool insertItemInContainer( const AwdKey *pKey, bool lock );

      virtual bool insertItemInContainer( const AwdKey *pKey,
                                          const AwdKey *pParent,
                                          bool lock );

      virtual bool isItemInContainer( const AwdKey *pKey );

      virtual bool selectItemInContainer( const AwdKey *pKey );

      virtual bool closeAwdContainer();

      virtual bool clearAwdContainer();

      virtual bool expandContainerItemDown( const AwdKey *pKey );

      virtual bool createAwdTransaction( AwdData &awdData, bool lock );

      virtual bool createAwdCase( AwdData &awdData, bool lock );

      virtual bool createAwdSource( const AwdData &awdData,
                                    const AwdSource::ObjectFormat format,
                                    const DString &strFile,
                                    AwdSource **ppSource,
                                    bool lock );

      virtual bool createRelationship( const AwdKey *pParent,
                                       const AwdKey *pChild );

      virtual bool lockAwdObject( const AwdKey *pKey, bool lock );

      virtual bool hasCaseForParent( const AwdKey *pKey, AwdKey **ppParent );

      virtual bool hasSourceForChild( const AwdKey *pKey, AwdKey **ppChild );

      virtual bool hasChildren( const AwdKey *pKey );

      virtual bool addComment( const AwdKey *pKey, const DString &comment );

      virtual bool beginListenCreateObjects();

      virtual AwdKeyVector endListenCreateObjects();

      virtual AwdKey * newAwdKey( const DString &createDateTime,
                                  const DString &recordCode,
                                  const DString &createNode );

      virtual bool retrieveData( const AwdKey *pKey, AwdData &awdData );

      virtual bool retrieveDataLite( const AwdKey *pKey, AwdData &awdData );

      virtual bool retrieveSource( const AwdKey *pKey, AwdSource **ppSource );

      virtual bool startService( const AwdKey *pKey,
                                 const DString &strServiceName );

      virtual bool stopService( const AwdKey *pKey,
                                const DString &strServiceName );

      virtual bool updateAwdObject( AwdData &awdData );

      virtual bool getAwdWork( AwdData &awdData );

      virtual bool getAwdWorkObjects( AwdKeyVector &awdKeyVector );

      virtual bool doubleClickContainerItem( const AwdKey *pKey );

      virtual AwdKey * getCurrentContainerSelection();

      virtual DString getQueue( const AwdKey *pKey );

      virtual bool setQueue( const AwdKey *pKey, const DString &queue );

      virtual DString getOperatorID();

      virtual unsigned long getCountry();

      virtual DString getWorkstationID();

      virtual DString getServerDateTime();

      virtual string_vector getSuspendCodeList();

      virtual bool suspendWorkObject( const AwdKey *pKey,
                                      const DString &activateDateTime,
                                      const DString &suspendCode );

      virtual bool unSuspendWorkObject( const AwdKey *pKey );

   private:
      data_obj_map m_dummy_map;
};



//************************************************************************
//              Revision Control Entries
//************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/inc/awdbaseinterface.hpp-arc  $
//
//   Rev 1.1   30 Jan 2008 14:20:52   kovacsro
//IN#1118094 - added an overloaded getStatusList method, in order to filter on queue, bussArea and wkType
//
//   Rev 1.0   28 Jan 2008 13:29:44   kovacsro
//Initial revision.
// 
//    Rev 1.16   Oct 16 2001 15:04:52   dt21858
// Added stopCSD()
// Added selectItemInContainer()
//
//    Rev 1.15   Aug 23 2001 16:54:00   DT21858
// - Added overloaded method for insertItemInContainer().
//
//    Rev 1.14   Aug 13 2001 13:59:18   DT21858
// Added getImmediateChildren()
//
//    Rev 1.13   Aug 06 2001 15:59:26   DT21858
// - Sync up eith 1.7.2.10 branch (comments included below)
// - Added getWorkstationID(), getCountry() and implemented getQueueList()
//
//
//    Rev 1.12   Jun 04 2001 15:01:02   DT21858
// Sync-up with Infra 1.7
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
// Added lookupSource() and fixed AwdTemplates
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

#endif // AWDBASEINTERFACE_HPP
