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
// ^FILE   : BFNotification.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : January 2000
//
// ----------------------------------------------------------
//
// ^CLASS : BFNotification
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <bfcbo\bfobserver.hpp>
#include <map>

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class DString;

/**
 * This class manages the notification mecanism
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> January, 2000 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFNotification  
{
public:
   /**
     * registers an observer for the observable object with identifier lObservableId
     * @param lObservableId - the identifier of the observable object, the observer should be registered with
     * @param eEventCateg   - the category of events for which the registration takes place
     * @param eEventId      - the events for which the registration takes place
     * @param pObserver     - pointer to the observer object that should be registered
     */
   void registerObserver  ( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, BFObserver *pObserver );
   /**
     * deregisters an observer observable relation
     * @param lObservableId - the identifier of the observable object, the observer should be deregistered with
     * @param eEventCateg   - the category of events for which the deregistration takes place
     * @param eEventId      - the events for which the deregistration takes place
     * @param pObserver     - pointer to the observer object that should be deregistered
     */
   void deregisterObserver( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, BFObserver *pObserver );
   /**
     * notifies the observers  registered with lObservableId observable object
     * @param lObservableId - the identifier of the observable object whose registered objects should be notified
     * @param eEventCateg   - the category of events for which the notification should be done
     * @param eEventId      - the events for which the notification should be done
     * @param hint          - string containing a hint that will be sent to the observers
     */
   void notifyObserver    ( long lObservableId, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString& hint );
   /**
     * constructor
     */
   BFNotification();
   /**
     * destructor
     */
   virtual ~BFNotification();

   /**
    * singleton getInstance method. Returns the existing instance, or if it doesn't exist it creates one and returns it 
    */
   static BFNotification* getInstance( void );
   /**
    * destroys the instance.
    */
   static void killInstance( void );
private :

   typedef std::multimap< BFNotifKey, BFObserver*, less_BFNotifKey >    NOTIFICATION_MMAP;

//CP20040225   static BFNotification* _pInstance;
//CP20040225
   NOTIFICATION_MMAP _notifMap;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFNotification.hpp-arc  $
//
//   Rev 1.6   Feb 26 2004 13:26:02   PURDYECH
//PET910 - Restructured to address some stability issues.
 * 
 *    Rev 1.5   Oct 09 2002 17:40:04   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.4   22 Mar 2002 15:11:38   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.3   03 May 2001 14:03:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Jul 21 2000 17:09:38   BUZILA
 * documentation added
 * 
 *    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 19 2000 10:13:24   BUZILA
// Initial revision.
// 
//
*/
