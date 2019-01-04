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

#include <commonport.h>
#include <bfproc\abstractlistdetails.hpp>
#include <bfcbo\bfobserver.hpp>
#include <bfcbo\bfdatagroupid.hpp>

// Forward reference
class AbstractProcess;
class BFAbstractCBO;
class BFObjIter;

#ifdef _NEW_BFContainerId_MODEL_
class BFContainerId;
#endif

/**
  * This class contains the details for an updateable list.  These structures
  * are currently stored in a vector since the expected number of lists is quite
  * small - typically < 5.  Note that the pointers and current key might get
  * updated dynamically, if the list is nested within another list.
  * The updateable list details are currently maintained only
  * by list ID so multiple accesses into the list by different callers is not
  * really supported.  The caller's GI pointer could be used to differentiate
  * this, but it was decided to wait and support it if needed.  Adding this
  * support should be transparent to the user.
  *
  * While this class isn't completely tied to CBO's, some additional work might
  * be required to support a non-CBO or non-UpdateableList type of list.
  *
  * When defining a static array of these structures in your subclass, set the
  * _listID of the last item to 0 to note the end of the array.  For all lists,
  * the list id should be > 0 and < 10000.  Effort should be made to avoid
  * conflicts across CBO's - this would make sure that there are no conflicts
  * when relaying field access processing to a parent process.
  *
  * @author Jerry Leenerts
  * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/02/99</dd></dl>
  * @version 0.1
  */
class ListDetails : public AbstractListDetails, public BFObserver
{
public:
   /**
     * Constructor
     */
   ListDetails( AbstractProcess *rpParent,
                const BFContainerId& idList,
                const BFContainerId& idParentList,
                bool bRepeatable,
                bool bUpdatable,
                const DString &name );
   virtual ~ListDetails();

   /**
     * Get the current key.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a const reference to the key.
     */
   virtual const DString& getCurrentKey( const BFDataGroupId& idDataGroup );
   /**
     * Add a new item to the list.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a const DString reference of key added.
     */
   virtual const DString& addItem( const BFDataGroupId& idDataGroup );
   /**
     * Method to commit changes for the container.  This commits the CBO changes
     * to the parent group.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return highest SEVERITY, check conditions
     */
   virtual SEVERITY commit( const BFDataGroupId& idDataGroup );
   /**
     * Deletes the current item.  The associated iterator will be set to
     * the beginning.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return highest severity encountered, check conditions
     */
   virtual SEVERITY deleteItem( const BFDataGroupId& idDataGroup );
   /**
    * Get the field for the current item.  Should never be called for this class
    * An exception will be thrown if the list, item, or field are invalid
    * 
    * @param fieldID    ID of field to get.
    * @param bFormatted true = get formatted value, false = get raw value.
    * @param strValueOut
    *                   A string reference where the field value will be
    *                   returned.
    * @param idDataGroup   Group to use for commit/rollback processing.
    */
   virtual void getField( const BFFieldId &fieldID,
                          bool bFormatted,
                          DString &strValueOut,
                          const BFDataGroupId& idDataGroup );
   /**
     * Get the current item pointer.  An exception will be thrown if the pointer
     * is NULL or has not been initialized since construction.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a reference pointer to the item.
     */
   virtual void *getItem( const BFDataGroupId& idDataGroup, const DString* pKey = NULL ); 
   /**
     * Get the first key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool getFirstKey( const DString **rpStr, const BFDataGroupId& idDataGroup );
   /**
     * Get the list pointer.  An exception will be thrown if the pointer is
     * NULL or has not been initialized since construction.
     * @return a reference pointer to the list.
     */
   BFAbstractCBO *getContainer();
   /**
     * Get the next key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool getNextKey( const DString **rpStr, const BFDataGroupId& idDataGroup );
   /**
     * Method to get the number of items in the list.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return an int with the number of items in the list
     */
   virtual int getNumberOfItemsInList( const BFDataGroupId& idDataGroup );
   /**
     * Determine if the current item in the list is new (never saved).
     * @param idDataGroup - Data group to use for CBO processing.
     * @return true if new, false otherwise.
     */
   virtual bool isNewItem( const BFDataGroupId& idDataGroup );
   /**
     * Called by CBO we are observing.
     */
   virtual void onNotify( E_EVENT_GROUP eEventGroup, E_EVENT eEventId, const DString &hint );
   /**
     * Method to reset (rollback) the container or item.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @param bCurrentItem - true = reset current item only, false = reset 
     * whole container.
     * @return highest SEVERITY, check conditions
     */
   virtual SEVERITY reset( const BFDataGroupId& idDataGroup, bool bCurrentItem );
   /**
     * Method to resetCurrentItem,
    * Note, this function does different thing then reset(idDataGroup, true)
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return highest SEVERITY, check conditions
     */
   virtual SEVERITY resetCurrentItem( const BFDataGroupId& idDataGroup );
   /**
     * Method to set the list to the item which matches the specified key.
     * @param strKey - key to match
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool setCurrentKey( const DString &strKey, const BFDataGroupId& idDataGroup );
   /**
    * Method to set the list to the item which matches the specified key.
    * If the item doesn't exist current Item is cleared.
    * 
    * @param strKey   key to match
    * @param idDataGroup Group to use for commit/rollback processing.
    * 
    * @return bool - true = item changed.
    */
   virtual bool trySetCurrentKey( const DString &strKey, const BFDataGroupId& idDataGroup );

   /**
    * Override of method to set the field for the current item. Not implemented
    * for this class - an exception will be thrown if used.
    * 
    * @param fieldID    ID of field to get.
    * @param bFormatted true = get formatted value, false = get raw value.
    * @param strValue   A string reference of value to set.
    * @param idDataGroup   Data group to use for CBO processing.
    * 
    * @return SEVERITY.
    */
   virtual SEVERITY setField( const BFFieldId &fieldID,
                              bool bFormatted,
                              const DString &strValue,
                              const BFDataGroupId& idDataGroup );
//CP20030219   /** Method used to find and set current update level for container.
//CP20030219     * @param idDataGroup - Data group to use for CBO processing.
//CP20030219     */
//CP20030219   void setUpdateLevel( const BFDataGroupId& idDataGroup );
   /**
     * Determine if the current item in the list is dummy
     * @param idDataGroup - Data group to use for CBO processing.
     * @return true if dummy, false otherwise.
     */
   virtual bool isDummyCurrentItem( const BFDataGroupId& idDataGroup ); 
protected:
   /**
     * Get the current item iterator.  An exception will be thrown if the
     * pointer is NULL or has not been initialized since construction.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a reference pointer to the item.
     */
   const BFObjIter &getItemIterator( const BFDataGroupId& idDataGroup );
   /** Method to set a pointer to a container object which subclasses
     * will use.
     * @param rpContainer - reference pointer to container to set
     * @return bool - true = change occurred, false = no change (pointer same)
     */
   virtual bool setContainer( void *rpContainer );
   /**
     * Method to filter the container based on stringKey
     * filter is a string made by sub strings separated by ";"
     * @param filter      - string containing the filter
     * @return success
     */
   bool setKeyFilter( const DString& filter );
   /**
     * Method to retrieve the stringKey filtering 
     * filter is a string made by sub strings separated by ";"
     * @param filter      - reference to a string in which the filter will be stored 
     */
   void getKeyFilter( DString& filter );
   /**
     * Method to remove the stringKey filtering 
     */
   void clearKeyFilter( );
   /**
     * Method to filter the container based on data content
     * filter condition is a string made form subconditions like 
     * fieldId=fieldValue, separated by ";"
     * @param filter      - string containing the filter
     * @return success
     */
   bool setDataFilter( const DString& filter ); 
   /**
     * Method to retrieve the  data content filtering 
     * filter condition is a string made form subconditions like 
     * fieldId=fieldValue, separated by ";"
     * @param filter      - reference to a string in which the filter will be stored 
     */
   void getDataFilter( DString& filter );
   /**
     * Method to clear out data content filtering 
     */
   void clearDataFilter( );


private:
   typedef std::map< BFDataGroupId, BFObjIter *, std::less< BFDataGroupId > > ITERS;
#if _MSC_VER >= 1300
   typedef std::map< BFDataGroupId, BFObjIter *, std::less< BFDataGroupId > >::const_iterator LIST_CONST_ITER;
#else
   typedef std::map< BFDataGroupId, BFObjIter *, std::less< BFDataGroupId > >::iterator LIST_CONST_ITER;
#endif
   AbstractProcess *_rpParent;
   ITERS _iters;
//CP20030219   long _lContainerUpdateLevel;

   DString _keyFilter;
   DString _dataFilter;

   void assureContainerValid();
   void assureItemValid( const BFDataGroupId& idDataGroup );
   void assureRepeatable( const BFDataGroupId& idDataGroup );
   void assureUpdatable();
   void deleteIters();
   BFObjIter *getIter( const BFDataGroupId& idDataGroup ) const;
   BFObjIter *getIterRaw( const BFDataGroupId& idDataGroup ) const;
   /**
     * Determine if the item pointer is valid.  Assumes the container is valid.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return true if the pointer is valid, false otherwise.
     */
   bool isItemValid( const BFDataGroupId& idDataGroup ); 
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/ListDetails.hpp-arc  $
//
//   Rev 1.16   Oct 22 2004 08:58:26   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.15   May 24 2003 14:56:06   PURDYECH
//Add facility to get item by key without altering "current" item
 * 
 *    Rev 1.14   Feb 26 2003 09:43:42   PURDYECH
 * Remove updateLevel 
 * 
 *    Rev 1.13   Jan 06 2003 16:44:06   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.12   Nov 27 2002 15:04:50   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.11   Oct 09 2002 17:40:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.10   Aug 29 2002 12:51:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   05 Jun 2002 13:55:16   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.8   22 Mar 2002 15:12:00   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.7   Feb 25 2002 18:52:30   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.6   26 Jul 2001 13:43:16   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.5   Dec 13 2000 13:19:10   KOVACSRO
 * Added a method to check if current item is dummy.
 * 
 *    Rev 1.4   Nov 08 2000 19:56:46   DT24433
 * added list name support
 * 
 *    Rev 1.3   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Mar 23 2000 16:23:46   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.1   Feb 15 2000 18:55:02   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Jan 12 2000 18:58:08   DT24433
 * added observer for CBO destruction
 * 
 *    Rev 1.10   Dec 09 1999 11:19:06   DT24433
 * started work on saving/checking updatelevel
 * 
 *    Rev 1.9   Dec 08 1999 16:20:44   DT24433
 * added isNewItem
 * 
 *    Rev 1.8   Nov 22 1999 18:02:00   DT24433
 * performance improvements
 * 
 *    Rev 1.7   Nov 15 1999 13:20:30   DT24433
 * fixed addItem problem
 * 
 *    Rev 1.6   Oct 28 1999 16:48:34   DT24433
 * added commit method
 * 
 *    Rev 1.5   Oct 28 1999 12:49:42   DT24433
 * add/delete/reset & group processing
 * 
 *    Rev 1.4   Aug 06 1999 10:14:42   DT24433
 * support change item detection
 * 
 *    Rev 1.3   Aug 05 1999 15:14:50   DT24433
 * altered functionality
 * 
 *    Rev 1.2   Aug 03 1999 14:47:28   DT24433
 * container changes
 * 
 *    Rev 1.1   Jul 08 1999 10:03:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
