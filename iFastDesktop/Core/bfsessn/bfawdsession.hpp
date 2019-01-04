#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#include <commonport.h>
#include <bfsessn\bfcpsession.hpp>
#include <bfdata\bfdata.hpp>
#include <condition.hpp>
#include <commontemplates.h>

#undef BFSESSN_LINKAGE
#ifdef BFSESSN_DLL
   #define BFSESSN_LINKAGE CLASS_EXPORT
#else
   #define BFSESSN_LINKAGE CLASS_IMPORT
#endif

class BFAwdKey;
class BFAwdData;
class BFAwdInterface;
class Configuration;
class ConfigManager;

/**
 * This class manages AWD interaction for BFCPSession.  Where a BFCPSession object
 * represents a span of time, this class does the work of creating and updating
 * AWD work for those events identified as AWD events.  This class also
 * provides additional methods for an application to use for AWD iteraction,
 * using the same configuration values defined for BFCPSession.
 */
class BFSESSN_LINKAGE BFAwdSession
{
   // Public data structures
public:
   typedef struct _BFAwdWorkEvent
   {
      bool         related;
      BFAwdKey      *key;
      string_map  *itemList;
   } BFAwdWorkEvent;

   typedef std::vector<BFAwdWorkEvent> awd_event_list;
   typedef awd_event_list::iterator awd_event_iterator;

   // Constructor and destructor are private
private:

   /**
    * Constructor.  Only for use by a BFCPSession object.
    *
    * @param pSession - Owning BFCPSession object
    *
    * @param pManager - Configuration values
    *
    * @param master - Whether or not the owning BFCPSession object is a
    *                 master BFCPSession object.
    */
   BFAwdSession( BFCPSession *pSession, ConfigManager *pManager, bool master );

   /**
    * Destructor.  Only to be used by a BFCPSession object.
    */
   virtual ~BFAwdSession();

   // Public methods
public:
   /**
    * Determines whether this BFAwdSession object has an BFAwdInterface object.
    *
    * @return True if an AWD interface is present.
    */
   bool hasAwdInterface() const { return(NULL != m_pAwd);}

   /**
    * Determines whenther an event will generate AWD work.
    *
    * @param event - Unique event identifier
    *
    * @return True if the event passed in will generate AWD work.
    */
   bool isAwdDefined( const DString &event );

   /**
    * Tells this object to retrieve the next piece of AWD work from
    * the AWD Process Queue.
    *
    * @return True if successfull.
    */
   bool getAwdWork();

   /**
    * Sets the AWD work to be processed.
    *
    * @param pWork - AWD work to be processed
    *
    * @param reset - If true, cleans up all associated items related to the
    *                previous work.  If false, simply changes which AWD
    *                work to use.
    *
    * @return True if successfull.
    */
   bool setProcessWork( BFAwdData *pWork, bool reset = true );

   /**
    * Returns the AWD work that was set by either getAwdWork or
    * setProcessWork for processing.  Otherwise returns NULL.
    *
    * @return AWD work being processed.
    */
   const BFAwdData * getProcessWork() const { return(m_pAwdWork);};

   /**
    * Returns true if the AWD work to be processed has been updated.
    *
    * @return bool
    */
   bool isProcessWorkUpdated() const { return(m_processWorkUpdated);};

   /**
    * Returns the default values for creating AWD work based on the event
    * identifier.
    *
    * @param event - Unique event identifier (which has AWD work defined).
    * @param busarea - Returns the AWD Business Area
    * @param worktype - Returns the AWD Work Type.
    * @param status - Returns the AWD Status.
    * @param process - Set to true to get the Processed Status.  Set to
    *                  false to get the Indexed status.
    */
   void getCreateDefaults( const DString &event,
                           DString &busarea,
                           DString &worktype,
                           DString &status,
                           bool    process = true );

   /**
    * Tells this object to create an AWD case.  A case will only be created
    * if one does not alreday exist and if the configuration information
    * indicates that a case should be used.  If a case already exists, then
    * no new case will be created.  If updateExisting is true, then an
    * existing case will be updated.
    *
    * @param datum - BFData object holding values to pass along to the case.
    * @param updateExisting - If true, will update an existing case.
    *
    * @return True if a case was created or updated.
    *
    * @exception ConditionException
    */
   bool createAwdCase( const BFData &datum, bool updateExisting = false );

   /**
    * Creates an AWD transaction translating data from 'datum' into
    * AWD lob fields.
    *
    * @param datum - Application data to send to AWD
    * @param awdData - Used to pass in the AWD create values: Business Area,
    *                  Work Type, and Status.  If the AWD object is
    *                  successfully created, then awdData object will
    *                  represent an AWD work object on the AWD server.
    *
    * @return bool - true if successful
    */
   bool createAwdTransaction( const BFData &datum, BFAwdData &awdData );

   /**
    * Will cause all AWD transactions (work) created by this interface to be
    * updated with the data passed in.
    *
    * @param datum - Application data to be translated and used for update.
    *
    * @return True if successfull.
    */
   bool updateTransactions( const BFData &datum );

   /**
    * Invokes a CSD.  If awdData represents an AWD object on the AWD server
    * then that object will be displayed in the CSD.  If not, then AWD
    * create values must be present and a CSD will be displayed that may
    * create an AWD object on the AWD server.
    *
    * @param awdData - AWD object to be displayed in a CSD.
    *
    * @return True if successful.
    */
   bool loadAwdCsd( BFAwdData &awdData );

   /**
    * Returns the current AWD case object being used to relate with
    * AWD transaction objects.  If there is no case, then a NULL is
    * returned.
    *
    * @return Pointer to the BFAwdKey of an AWD case object.
    */
   const BFAwdKey *getAwdCase() const { return(m_pCase);};

   /**
    * Returns a list of AWD work (case and transactions) created by this
    * BFAwdSession object.
    *
    * @return awd_event_list - a list of AWD work.
    */
   const awd_event_list &getAwdEventList() const { return(m_eventList);};

   /**
    * The method will copy the data elements from the source data object
    * to the destination data object, converting the tags from Application
    * tags to AWD tags where applicable.
    *
    * @param source - Source data object
    * @param dest - Destination data object.
    *
    * @return unsinged long - number of tags converted.
    */
   unsigned long convertToAwdTags( const BFData &source, BFData &dest );

   /**
    * Used to determin if a BFCPSession event has created or updated
    * an AWD object.
    *
    * @return True if an AWD object was created or updated as the result
    *         of a BFCPSession event.
    */
   bool getEventRecorded() const { return(m_eventRecorded);}

   // Private methods
private:
   void getExportTable( Configuration &exportTable );

   bool awdEvent( const DString        &awdWork,
                  const Configuration &eventCfg,
                  const BFDataPtrMap& data,
                  bool bLocked = true );
   //CP20040224 Added bLocked at urging of YingBao Li.  Non-standard change to DST code

   void relateWorkToCase( bool relateProcessWork );
   void deleteAwdList();

   void preProcess( const Configuration &eventCfg,
                    const BFDataPtrMap& data,
                    BFAwdData       &awdData,
                    bool           isCase = false );

   void postProcess( BFAwdData &awdData, bool addToList = false );
   void checkDisplayCsd( const Configuration &config, BFAwdData &awdData );
   void setEventRecorded( bool recorded );

   // Private structs
private:
   typedef struct _BFAwdDataItem
   {
      bool related;
      BFAwdData *pData;
   } BFAwdDataItem;

   typedef std::vector<BFAwdDataItem> BFAwdDataVector;

   // Private members
private:
   typedef awd_event_list::reverse_iterator awd_event_reverse_iterator;

   friend class BFCPSession;

   BFCPSession    *m_pSession;
   const BFAwdKey   *m_pCase;
   BFAwdKey         *m_pProcessCase;
   BFAwdData        *m_pAwdWork;
   BFData            m_caseCollector;
   awd_event_list  m_eventList;
   ConfigManager  *m_sessionCfgMgr;
   bool            m_masterSession;
   bool            m_hasCaseForParent;
   bool            m_processWorkUpdated;
   bool            m_lastEventPropagated;
   bool            m_callTimeSet;
   bool            m_caseOnMultiple;
   bool            m_caseOnMultipleP;
   int             m_workCount;
   BFAwdInterface   *m_pAwd;
   BFAwdData        *m_pCaseData;
   bool            m_haveListener;
   BFAwdDataVector   m_csdList;
   BFAwdKey         *m_pProcessSource;
   bool            m_linkSource;
   bool            m_eventRecorded;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/bfawdsession.hpp-arc  $
//
//   Rev 1.3   Feb 24 2004 09:04:18   PURDYECH
//Add bLocked flag.  Non-standard extension to DST code.
//
//   Rev 1.2   Nov 27 2002 15:04:58   PURDYECH
//Documentation Changes
//
//   Rev 1.1   Oct 09 2002 17:41:02   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:20   SMITHDAV
//Initial revision.
// 
//    Rev 1.11   23 Oct 2000 11:56:22   dt14177
// cleanup
// 
//    Rev 1.10   Apr 17 2000 09:35:18   DMUM
// Comments to JavaDoc 
//
//    Rev 1.9   Aug 30 1999 16:22:58   DMUM
// The constructor for BFCPSession no longer throws
//
//    Rev 1.8   May 18 1999 08:50:16   DMUM
//
//
//    Rev 1.7   Apr 09 1999 13:26:22   DMUM
// Sync up with 1.6.x
//
//    Rev 1.5.1.0   Mar 31 1999 13:14:56   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.2.1.6   Feb 26 1999 08:49:50   DMUM
// Development for TA2000 NT 3.4
//
//    Rev 1.2.1.5   Feb 09 1999 10:54:26   DMUM
// Updated documentation
//
//    Rev 1.2.1.4   Feb 08 1999 15:11:18   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.2.1.3   Jan 20 1999 16:39:14   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.2.1.2   Dec 30 1998 13:02:54   DMUM
// Fixes ticket 6053 and has enhancement for Kemper
// (which are also required for 3.4)
//
//    Rev 1.2.1.1   Oct 14 1998 10:23:00   DMUM
// Now when case creates, links to all existing work
//
//    Rev 1.2.1.0   Oct 13 1998 12:39:42   DMUM
// Added create case on multiple work objects
//
//    Rev 1.2   Aug 14 1998 13:50:54   DMUM
// Tuning
//
//    Rev 1.1   Aug 13 1998 12:05:00   DMUM
// Tunning
//
//    Rev 1.9   Jul 23 1998 10:28:52   dmum
// Added method convertToAwdTags()
//
//    Rev 1.8   Jul 16 1998 11:47:48   dmum
// More developement
//
//    Rev 1.7   Jul 07 1998 06:24:32   dmum
// Condensed four methods into two
//
//    Rev 1.6   Jul 06 1998 15:47:20   dmum
// added new createAwdCase method override
//
//    Rev 1.5   May 22 1998 14:00:30   dmum
// Fixes ticket #2864.  Also fixes issue of sending data to a Case.
//
//    Rev 1.4   Apr 28 1998 08:46:32   dmum
// Added member variable m_lastEventPropagated
//
//    Rev 1.3   Mar 16 1998 15:39:12   dmum
// Fixed problems
// Tracker 2034, 2035, 2036
//
//    Rev 1.2   Jan 30 1998 14:00:28   dmum
// Fixed bug to allow multiple updates of the process work
//
//    Rev 1.1   Jan 19 1998 15:46:00   dmum
// Added member m_pProcessCase
//
//    Rev 1.0   Dec 30 1997 12:42:10   dmum
//
//
//

