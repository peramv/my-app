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
// ^FILE   : BFObservable.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObservable
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <map>
#include <bfcbo\bfobserver.hpp>


#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class DString;

/**
 * This class implements an observable object
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> December, 1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFObservable  
{
public:
   /**
    * gets the observable id
    */
   long getId();
   /**
    * notifies the observers registered with this object
    * @param eEventCateg   - the category of events for which the notification should be done
    * @param eEventId      - the events for which the notification should be done
    * @param hint          - string containing a hint that will be sent to the observers
    */
   void notifyObservers(  E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString & hint );

   /**
    * constructor
    */
   BFObservable();
   /**
    * destructor
    */
   virtual ~BFObservable();
private:
   static long nextId;
   long _observableID;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFObservable.hpp-arc  $
 * 
 *    Rev 1.4   Oct 09 2002 17:40:06   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.3   22 Mar 2002 15:11:40   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   03 May 2001 14:03:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Jul 21 2000 17:09:40   BUZILA
 * documentation added
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
// 
//    Rev 1.4   Jan 19 2000 10:12:04   BUZILA
// refresh stuf
// 
//    Rev 1.3   Jan 04 2000 12:16:22   BUZILA
// changes...
// 
//    Rev 1.2   Dec 21 1999 18:14:48   BUZILA
// notification changes
// 
//    Rev 1.1   Dec 21 1999 12:42:22   BUZILA
// few changes
 * 
 */


