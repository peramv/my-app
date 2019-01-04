#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
// ^FILE   : BFObserver.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObserver
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <set>

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif


/**
 * This enum contains event groups
 *
 * <pre>
 *@@   FIELD_NOTIFICATIONS     - field type notifications
 *@@   NON_FIELD_NOTIFICATIONS - non field type notifications
 * </pre>
 */
enum E_EVENT_GROUP
{
   FIELD_NOTIFICATIONS     = 1,
   NON_FIELD_NOTIFICATIONS 
};

/**
 * This enum contains event types
 *
 * <pre>
 *@@   E_EVENT_ALL                - wildcard. can be any type of event
 *@@   E_EVENT_PROPERTY_CHANGE    - this event ocurs when the properties of a field are changed
 *@@   E_EVENT_VALUE_CHANGE       - this event ocurs when the value of a field is changed
 *@@   E_EVENT_STATE_CHANGE       - this event ocurs when the state of a field is changed
 *@@   E_EVENT_CBO_DESTROYED      - this event ocurs when a CBO gets destroyed
 *@@   E_EVENT_CBO_OBJITER_UPDATE - this event ocurs when the iterator should be refreshed
 * </pre>
 */
enum E_EVENT
{
   E_EVENT_ALL = 0,
   E_EVENT_PROPERTY_CHANGE,
   E_EVENT_VALUE_CHANGE,
   E_EVENT_STATE_CHANGE,
   E_EVENT_CBO_DESTROYED,
   E_EVENT_CBO_OBJITER_UPDATE
};

class DString;

/**
 * This class implements key used in observer observable registration. This registration is done through 
 * BFNotification object
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> December, 1999 </dd></dl>
 * @version 0.1
 */
struct BFNotifKey
{
   /**
    * constructor
    * @param lObservableId - the identifier of the observable object the registration is made for
    * @param eEventCateg   - the category of events for which the registration is done
    * @param eEventId      - the events for which the registration is done
    */
   BFNotifKey( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId) : 
   m_lObservableId( lObservableId ), m_eEventCateg( eEventCateg ), m_eEventId( eEventId ){};
   /**
    * the identifier of the observable object that is involved in this entry
    */
   long           m_lObservableId;
   /**
    * what event category the registration is made for
    */
   E_EVENT_GROUP  m_eEventCateg;
   /**
    * what event the registration is made for
    */
   E_EVENT        m_eEventId;
};


/**
 * This class implements the odering used in BFNotifKey
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> December, 1999 </dd></dl>
 * @version 0.1
 */
struct less_BFNotifKey
{
   /**
    * the operator() that is used for ordering
    */
   bool operator() ( const BFNotifKey &a, const BFNotifKey &b ) const
   {
      if( a.m_lObservableId != b.m_lObservableId )
      {
         return(a.m_lObservableId < b.m_lObservableId);
      }
      if( a.m_eEventCateg != b.m_eEventCateg )
      {
         return(a.m_eEventCateg < b.m_eEventCateg);
      }
      if( a.m_eEventId != b.m_eEventId )
      {
         return(a.m_eEventId < b.m_eEventId);
      }
      return(false);
   }
};

/**
 * This class implements an observer object. It can be registered with an observable for some events, 
 * and it will be notified when that events are occuring
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> December, 1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFObserver  
{
public:

   /**
     * registers this as an observer for the observable object with identifier lObservableId
     * @param lObservableId - the identifier of the observable object, this be registered with
     * @param eEventCateg   - the category of events for which the registration takes place
     * @param eEventId      - the events for which the registration takes place
     */
   void registerObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId );
   /**
     * deregisters this as an observer for the observable lObservableId 
     * @param lObservableId - the identifier of the observable object, this should be deregistered with
     * @param eEventCateg   - the category of events for which the deregistration takes place
     * @param eEventId      - the events for which the deregistration takes place
     */
   void deRegisterObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId );
   /**
     * deregisters this as an observer for all observable objects whith which it was registered
     */
   void deRegisterObserver( );

   /**
    * constructor
    */
   BFObserver();
   /**
    * destructor
    */
   virtual ~BFObserver();

   /**
    * pure virtual function. Should be overwriten by all observer classes in order to do special 
    * processing on notification
    * @param eEventCateg - the category of events for which the notification is done
    * @param eEventId    - the event for which the notification is done
    * @param hint        - the hint passed to the observer
    */
   virtual void onNotify(
                        E_EVENT_GROUP eEventCateg,
                        E_EVENT eEventId,
                        const DString &hint
                        ) {}

   /**
    * set of observables the observer is registered with
    */
   typedef std::set < BFNotifKey, less_BFNotifKey > OBS_SET;

   /**
    * variable holding the set of observables the observer is registered with
    */
   OBS_SET _obsSet;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFObserver.hpp-arc  $
//
//   Rev 1.7   Mar 29 2005 10:17:44   purdyech
//Magic 270964 - Gave an empty implementation for onNotify() to prevent a pure virtual function call from occuring when a class which is derived from BFObserver is being destroyed.
 * 
 *    Rev 1.6   Nov 27 2002 15:02:24   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.5   Oct 09 2002 17:40:08   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   22 Mar 2002 15:11:40   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.3   03 May 2001 14:03:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Jul 21 2000 17:09:40   BUZILA
 * documentation added
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 31 2000 13:05:50   BUZILA
// changes
// 
//    Rev 1.4   Jan 19 2000 10:12:04   BUZILA
// refresh stuf
// 
//    Rev 1.3   Jan 12 2000 11:51:30   BUZILA
// added NON_FIELD_NOTIFICATIONS group and E_EVENT_CBO_DESTROYED event
// 
//    Rev 1.2   Dec 21 1999 15:51:20   DT24433
// minor tweaks
// 
//    Rev 1.1   Dec 21 1999 12:42:22   BUZILA
// few changes
 * 
 */
