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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFObjIter.hpp
// ^AUTHOR : Mike Metzger
// ^DATE   : May 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObjIter
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//
//******************************************************************************

#include <bfcbo\bfabstractcbo.hpp>
#include <bfcbo\bfdatafilter.hpp>
#include <bfcbo\bfobserver.hpp>
#include <bfdata\bfdata.hpp>
#include <condition.hpp>

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This implements an iterator for CBOs( classes derived from BFAbstractCBO)
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/07/1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFObjIter : public BFObserver
{
public:
   /**
    * sets the key filter criteria
    * @param dstFilter     - IDI string containins the criteria
    * @param bStartOfKey   - do we want to force the matching from the start of strKey
    */
   bool setKeyFilter( const DString & dstFilter, bool bStartOfKey = false);
   /**
    * gets the key filter criteria
    * @param dstFilter     - IDI string containins the criteria
    */
   bool getKeyFilter( DString & dstFilter );
   /**
    * clears out the key filter 
    */
   bool clearKeyFilter( );

   /**
    * sets the data filter criteria
    * @param dstFilter     - IDI string containins the criteria
    */
   bool setDataFilter( const DString & dstFilter );
   /**
    * gets the data filter criteria
    * @param dstFilter     - IDI string containins the criteria
    */
   bool getDataFilter( DString & dstFilter );
   /**
    * clears out the data filter 
    */
   bool clearDataFilter( );

   /**
    * retruns true if the object has BF::HOST updates
    * @param inclSubObj - do we want to look into contained objects
    */
   bool hasHostUpdates( bool inclSubObj = true );
   /**
    * retruns true if the object has updates that should be sent to the database
    * @param inclSubObj - do we want to look into contained objects
    */
   bool hasTransactionUpdates( bool inclSubObj = true );

   /**
    * retruns true if the object which the iterator is currently pointing on is dummy
    */
   bool isDummy();

   /**
    * retruns true if objIter points to the same _objMap entry
    * @param objIter - the iterator to be compared with
    */
   bool samePosition( BFAbstractCBO::OBJECT_MAP_CONST_ITER& objIter ) const;

   /**
    * physically removes the object on which the iterator is currently pointing on
    * 
    * @param bDeleteObjectInstance
    *               true if we want to destroy the object instance
    * @param bForce true if the object should be forced out regardless of overrides to BFCBO::isDeleteAllowed()
    * 
    * @return 
    */
   SEVERITY removeObjectFromMap( bool bDeleteObjectInstance = true, bool bForce = false );

   /**
    * Deletes the object on which the iterator is currently pointing on
    * 
    * @return 
    */
   SEVERITY deleteObject();

   /**
    * creates a new object and adds it to the container
    * @param strKey - the strKey for the newly created item
    */
   BFAbstractCBO * addNewObject( DString & strKey );

   /**
    * implementation of the Observer::onNotify. It is responsable for refreshing the strKeyMap
    * @param eEventCateg   - what event category the notification is about
    * @param eEventId      - what event the notification is about
    * @param hint          - the hint that is passed in
    */
   void onNotify( E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString &hint );

   /**
    * This enum contains traversal types 
    * <pre>
    *@@ NON_DELETED - displays only non deleted items
    *@@ DELETED     - displays only deleted items
    *@@ ADDED       - displays only added items
    *@@ ALL         - displays all items
    * </pre>
    */
   enum ITERTYPE
   {
      NON_DELETED,
      DELETED,
      ADDED,
      ALL
   };

   /*
    * This enum contains container types 
    * <pre>
    *@@ HOST_CONTAINER    - host container ( obsolete )
    *@@ INTERIM_CONTAINER - interim container ( obsolete )
    * </pre>
    */

   enum CONTAINER
   {
      HOST_CONTAINER,
      INTERIM_CONTAINER
   };

   //contructor positions iter on first applicable item
   /**
    * constructor takes a CBO reference, a data group and some constraints and constructs an iterator on that CBO for idDataGroup data group
    * @param bfObj           - the object on which we want to iterate on 
    * @param idDataGroup    - the data group identifier that we want to use for iteration
    * @param matchSubstrings - do we want substrings of the strKey matches
    * @param type            - the data group identifier for which we want to get the errors
    * @param initializeStrKeyMap - do we want to force the initialisation of strKeyMap
    * @param forceUseStrKeyMap   - do we want to force the use of strKeyMap
    */
   BFObjIter( BFAbstractCBO &bfObj, 
              const BFDataGroupId& idDataGroup, 
              bool matchSubstrings = false, 
              ITERTYPE type = ALL, 
              bool initializeStrKeyMap = true, 
              bool forceUseStrKeyMap = false );

   /**
    * destructor
    */
   ~BFObjIter();

   /**
    * advance the iterator
    */
   bool operator++();

   /**
    * Decrease the iterator
    */
   bool operator--();

   /**
    * sets the iter back to the beginning (default state upon construction)
    * @param type       - what object types do we want to see. If it is OBJ_TYPE_NONE we are seeing all of them.
    * @param activity   - what object activity do we want to see. If it is OBJ_ACTIVITY_NONE we are seeing all of them.
    * @param strKey  - what object strKey do we want to see. If it is NULL_STRING we are seeing all of them.
    */
   bool begin( BF_OBJ_TYPE type = OBJ_TYPE_NONE, 
               BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE, 
               DString strKey = NULL_STRING );

   /**
    * returns true if the iterator is at the begining of the container
    */
   bool isBegin();

   /**
    * returns true if the iterator is at the end of the container
    */
   bool end();

   /**
    * refreshes the itereator if it is needed
    */
   void checkIterator();

   /**
    * return a pointer to the object that the iterator is currently pointing on
    */
   // WTF? Used to return BFAbstractCBO*&.  Why?  Why would we let the app code change the object in the map directly?
   BFAbstractCBO* getObject();

   /**
    * returns the group flags for the object that the iterator is currently pointing on
    */
   const long getGroupFlags() const
   {
      return(*_currIter).second->getGroupFlags();
   }

   // Return a const ref for the key to the current object
   /**
    * returns the key for the object which the iterator is currently pointing on
    */
   const BFObjectKey & getKey() const
   {
      return(*_currIter).first;
   }

   /**
    * returns the strKey for the object which the iterator is currently pointing on
    */
   const DString & getStringKey() const
   {
      return(*_currIter).first.getStringKey();
   }

   /**
    * returns how many items the list actually contains
    */
   int getNumberOfItemsInList();

   //position iterator by key
   /**
    * tries to position the itereator on an item based on strKey and lObjType constraints
    * @param strKey   - the strKey that we are looking for
    * @param lObjType - what type of object we are looking for. If it is XCHG_TYPE_NONE we don't care about the object type
    */
   bool positionByKey( const DString &strKey, BF_OBJ_TYPE lObjType = OBJ_TYPE_NONE );
   /**
    * repositions the itereator based on the criteria that is stored in the iterator
    */
   bool repositionIterator( );

   /**
    * repositions on the itereator based on the criteria passed into matchCriteria, and data group idDataGroup
    * @param matchCriteria  - data object containing the criteria to be met
    * @param idDataGroup   - data group in which we are doing the search
    */
   void positionOnNextMatch( const BFData &matchCriteria, const BFDataGroupId& idDataGroup );

   /**
    get the last object in the list **/
  const BFAbstractCBO* getLastObject(DString& dstrKey);

private:
   /**
    * returns true if the data filter criteria is met
    */
   bool checkDataFilter();
   /**
    * returns true if the key filter criteria is met
    */
   bool checkKeyFilter();

   typedef std::vector< DString > KEY_FILTER_VECTOR;

   void refreshStrKeyMap();
   bool positionUsingKey(DString lStrKey);
   BFObjIter();
//DS  BFObjIter( const BFObjIter &copy );
//DS  BFObjIter& operator=( const BFObjIter &copy );

   struct StrKeyEntry
   {
      DString _str;
      long    _objType;
      StrKeyEntry( DString lStr, long lObjType ) : _str( lStr ), _objType( lObjType ){};
   };
   struct less_StrKeyEntry
   {
      bool operator() ( const StrKeyEntry &a, const StrKeyEntry &b ) const
      {
         if( a._str != b._str )
         {
            return(a._str < b._str);
         }
         if( a._objType != b._objType )
         {
            return(a._objType < b._objType);
         }
         return(false);
      }
   };

   typedef std::map< StrKeyEntry, BFAbstractCBO::OBJECT_MAP_ITER, less_StrKeyEntry > STR_KEY_MAP;

   BFDataFilter *  pDataFilter_;

   KEY_FILTER_VECTOR  vKeyFilter_;
   bool bKeyFiltered_;
   bool bPrefixKeyFilter_;

   STR_KEY_MAP                _strKeyMap;
   STR_KEY_MAP::iterator      _strKeyMapIter;
   BFAbstractCBO*             _pContainer; 
   const BFDataGroupId idDataGroup_;
   ITERTYPE                   _iterType;
   CONTAINER                  _currContainer;
   BFAbstractCBO::OBJECT_MAP_ITER _currIter;

   BF_OBJ_TYPE                _critType;
   BF_OBJ_ACTIVITY            _critActivity;
   DString                    _critStringKey;

   DString                    _lastStringKey;
   BF_OBJ_TYPE                _lastObjType;
   bool                       _lastOnEnd;

   bool                       _critMatchSubstrings;
   bool                       bUseStrKeyMap_;
   bool                       _needRefresh;

   bool bInitialized_;
   bool bIsVersionable_;


   inline bool useStrKeyMap() const { return(bUseStrKeyMap_);}
   inline bool isVersionable() const { return(bIsVersionable_);}

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/bfobjiter.hpp-arc  $
//
//   Rev 1.18   Dec 09 2004 12:16:56   purdyech
//PET910 - Non-versionable CBO optimization fixes
//
//   Rev 1.17   Oct 22 2004 08:54:16   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.16   May 08 2003 15:32:06   PURDYECH
//Added ability to force a delete of a contained object.
 * 
 *    Rev 1.15   Jan 06 2003 16:41:16   PURDYECH
 * BFDataGroupId changeover
 * 
 *    Rev 1.14   Nov 27 2002 15:02:14   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.13   Oct 25 2002 15:06:02   SMITHDAV
 * Remove CP comments.
 * 
 *    Rev 1.12   Oct 09 2002 17:40:06   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.11   Aug 29 2002 12:51:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   05 Jun 2002 14:08:14   SMITHDAV
 * Make copyable and remove unused definitions.
 * 
 *    Rev 1.9   22 May 2002 18:08:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   22 Mar 2002 15:11:40   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.7   Feb 27 2002 20:45:06   PURDYECH
 * Changed getObject to return BFAbstractCBO*& like it used to.  I'm not happy about doing this, but it's needful as many programs seem to take advantage of this backdoor entry into the Object Map.
 * 
 *    Rev 1.6   Feb 25 2002 18:52:26   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.5   03 May 2001 14:03:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Jul 21 2000 17:09:40   BUZILA
 * documentation added
 * 
 *    Rev 1.3   Apr 13 2000 10:40:22   BUZILA
 * data Filtering issues
 * 
 *    Rev 1.2   Apr 03 2000 08:59:50   BUZILA
 * Added start of key condition in filtering
 * 
 *    Rev 1.1   Mar 23 2000 16:23:46   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.19   Feb 03 2000 10:13:00   BUZILA
 * added CALCULATED_FIELD flag and hasTransactionUpdates method
 * 
 *    Rev 1.18   Feb 02 2000 10:33:50   BUZILA
 * we should not send transactions for uncommited data
 * 
 *    Rev 1.17   Jan 31 2000 13:05:46   BUZILA
 * changes
 * 
 *    Rev 1.16   Jan 26 2000 12:10:30   BUZILA
 * changed StrMap and added isDummy()
 * 
 *    Rev 1.15   Jan 18 2000 18:37:44   VASILEAD
 * added one parameter to removeObjectFromMap
 * 
 *    Rev 1.14   Jan 06 2000 13:35:16   BUZILA
 * added getGroupFlags method
 * 
 *    Rev 1.13   Dec 21 1999 12:46:00   BUZILA
 * Validate Field changes
 * 
 *    Rev 1.12   Dec 19 1999 16:55:16   BUZILA
 * added revision area
 * 
 */


