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
#include <bfproc\AbstractProcessConstants.h>
#include <bfproc\bfcontainerid.hpp>
#include <bfcbo\bfdatagroupid.hpp>

// Forward reference
class AbstractProcess;
class BFFieldId;

/**
  * This class contains the details for a generic list.  These structures
  * are currently stored in a vector since the expected number of lists is quite
  * small - typically < 5.  Note that list internals might get
  * updated dynamically, if the list is nested within another list.
  * The list details are currently maintained only
  * by list ID so multiple accesses into the list by different callers is not
  * really supported.  The caller's GI pointer could be used to differentiate
  * this, but it was decided to wait and support it if needed.  Adding this
  * support should be transparent to the user.
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
class AbstractListDetails
{
public:
   const static DString _strEmpty;   // Used only to return an empty string reference
   friend AbstractProcess;
   /**
     * Constructor
     */
   AbstractListDetails( const BFContainerId& idContainer,
                        const BFContainerId& idParentContainer,
                        bool bRepeatable,
                        bool bUpdatable,
                        const DString &name );
   virtual ~AbstractListDetails();

   /**
     * Add a new item to the list.  This method should be overridden if the list
     * supports it.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns a const DString reference of key added.
     */
   virtual const DString &addItem( const BFDataGroupId& idDataGroup );
   /**
     * Method to commit changes for the container.  This commits the CBO changes
     * to the parent group.
     * This must be implemented by derived class, if required.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns highest SEVERITY, check conditions
     */
   virtual SEVERITY commit( const BFDataGroupId& idDataGroup );
   /**
     * Deletes the current item.
     * This method should be overridden if the list supports it.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns highest severity encountered, check conditions
     */
   virtual SEVERITY deleteItem( const BFDataGroupId& idDataGroup );
   /**
     * Get the pointer to the container object.  An exception will be thrown if
     * the pointer is NULL or has not been initialized since construction.
     * @returns a reference pointer to the container object.
     */
   void *getContainer();
   /**
     * Get the container id.
     * @returns an integer id.
     */
   const BFContainerId& getContainerID() const
   {
      return(idContainer_);
   }
   /**
     * Abstract method to get the current key.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns a const reference to the key.
     */
   virtual const DString &getCurrentKey( const BFDataGroupId& idDataGroup ) = 0;
   /**
     * Abstract method to get the field for the current item.
     * An exception will be thrown if the list, item, or field are invalid
     * @param fieldID - ID of field to get.
     * @param bFormatted - true = get formatted value, false = get raw value.
     * @param strValueOut - A string reference where the field value will be
     * returned.
     * @param idDataGroup - Group to use for commit/rollback processing.
     */
   virtual void getField( const BFFieldId &fieldID,
                          bool bFormatted,
                          DString &strValueOut,
                          const BFDataGroupId& idDataGroup ) = 0;
   /**
     * Abstract method to get the first key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns bool - true = item changed.
     */
   virtual bool getFirstKey( const DString **rpStr, const BFDataGroupId& idDataGroup ) = 0;
   /**
     * Use this method to get the current item if the container is repeatable, or the
     * container itself if not repeatable.
     * An exception will be thrown if the pointer has not been set.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns a reference pointer to the container object.
     */
   virtual void *getItem( const BFDataGroupId& idDataGroup, const DString* pKey = NULL );
   /**
     * Return the name of the container.
     * @returns string name of the container.
     */
   const DString &getName()
   {
      return(_name);
   }
   /**
     * Abstract method to get the next key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns bool - true = item changed.
     */
   virtual bool getNextKey(
                          const DString **rpStr,
                          const BFDataGroupId& idDataGroup
                          ) = 0;
   /**
     * Abstract method to get the number of items in the container.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns an int with the number of items in the container
     */
   virtual int getNumberOfItemsInList(
                                     const BFDataGroupId& idDataGroup
                                     ) = 0;
   /**
     * Get the parent container id.
     * @returns an integer id.
     */
   const BFContainerId& getParentContainerID() const
   {
      return( idParentContainer_ );
   }
   /**
     * Determine if the container is valid (has been set).
     * @returns true if the pointer is valid, false otherwise.
     */
   bool isContainerValid()
   {
      return(_rpContainer != NULL);
   }
   /**
     * Determine if the current item in the list is new (never saved).
     * @param idDataGroup - Data group to use for CBO processing.
     * @returns true if new, false otherwise.
     */
   virtual bool isNewItem(
                         const BFDataGroupId& idDataGroup
                         );
   /**
     * Determine if the container is repeatable, meaning that list operations are valid
     * @returns true if the container is repeatable, false otherwise.
     */
   bool isRepeatable()
   {
      return(_bRepeatable);
   }
   /**
     * Determine if the container is updatable allowing set/add/delete operations.
     * @returns true if the container is updatable, false otherwise.
     */
   bool isUpdatable()
   {
      return(_bUpdatable);
   }
   /**
     * Determines if the container has children.
     * @returns true if the container has children, false otherwise.
     */
   bool hasChildren()
   {
      return(_bHasChildren);
   }
   /**
     * Method to reset (rollback) the container.  This must be implemented by
     * derived class, if required.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @param bCurrentItem - true = reset current item only, false = reset whole
     * container.  This must be false if container doesn't support items.
     * @returns highest SEVERITY, check conditions
     */
   virtual SEVERITY reset(
                         const BFDataGroupId& idDataGroup,
                         bool bCurrentItem
                         );
   /**
     * Method to resetCurrentItem,
    * Note, this function does different thing then reset(idDataGroup, true)
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns highest SEVERITY, check conditions
     */
   virtual SEVERITY resetCurrentItem(
                                    const BFDataGroupId& idDataGroup
                                    );
   /**
     * Method to set the list to the item which matches the specified key.
     * @param strKey - key to match
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns bool - true = item changed.
     */
   virtual bool setCurrentKey(
                             const DString &strKey,
                             const BFDataGroupId& idDataGroup
                             ) = 0;
   /**
     * Method to set the list to the item which matches the specified key.
     * If the item doesn't exist current Item is cleared.
     * @param strKey - key to match
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @returns bool - true = item changed.
     */
   virtual bool trySetCurrentKey(
                                const DString &strKey,
                                const BFDataGroupId& idDataGroup
                                ) = 0;
   /** Method to set a pointer to a container object which subclasses
     * will use.
     * @param rpContainer - reference pointer to container to set
     * @returns bool - true = change occurred, false = no change (pointer same)
     */
   virtual bool setContainer( void *rpContainer );
   /**
     * Abstract method to set the field for the current item.
     * An exception will be thrown if the list, item, or field are invalid
     * @param fieldID - ID of field to get.
     * @param bFormatted - true = get formatted value, false = get raw value.
     * @param strValue - A string reference of value to set.
     * @param idDataGroup - Group to use for rollback processing.
     * @returns SEVERITY.
     */
   virtual SEVERITY setField( const BFFieldId &fieldID, bool bFormatted, const DString &strValue, const BFDataGroupId& idDataGroup ) = 0;
   /** Use this method to indicate that the container has children.
     */
   void setHasChild()
   {
      _bHasChildren = true;
   }
   /**
     * Determine if the current item in the list is dummy
     * @param idDataGroup - Data group to use for CBO processing.
     * @returns true if dummy, false otherwise.
     */
   virtual bool isDummyCurrentItem(
                                  const BFDataGroupId& idDataGroup
                                  );
protected:
   /**
     * Get the container pointer (whether it is NULL or not).
     * @returns a reference pointer to the container.
     */
   void *getContainerPtrRaw()
   {
      return(_rpContainer);
   }
   /**
     * Abstract method to filter the container based on stringKey
     * filter is a string made by sub strings separated by ";"
     * @param filter      - string containing the filter
     * @return success
     */
   virtual bool setKeyFilter(
                            const DString& filter
                            );
   /**
     * Abstract method to retrieve the stringKey filtering 
     * filter is a string made by sub strings separated by ";"
     * @param filter      - reference to a string in which the filter will be stored 
     */
   virtual void getKeyFilter(
                            DString& filter
                            );
   /**
     * Abstract method to remove the stringKey filtering 
     */
   virtual void clearKeyFilter();
   /**
     * Abstract method to filter the container based on data content
     * filter condition is a string made form subconditions like 
     * fieldId=fieldValue, separated by ";"
     * @param filter      - string containing the filter
     * @return success
     */
   virtual bool setDataFilter(
                             const DString& filter
                             );
   /**
     * Abstract method to retrieve the  data content filtering 
     * filter condition is a string made form subconditions like 
     * fieldId=fieldValue, separated by ";"
     * @param filter      - reference to a string in which the filter will be stored 
     */
   virtual void getDataFilter(
                             DString& filter
                             );
   /**
     * Abstract method to clear out data content filtering 
     */
   virtual void clearDataFilter();

private:
   bool _bHasChildren;
   bool _bRepeatable;
   bool _bUpdatable;
   const BFContainerId idContainer_;
   const BFContainerId idParentContainer_;
   void *_rpContainer;
   DString _name;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/AbstractListDetails.hpp-arc  $
//
//   Rev 1.13   May 24 2003 14:55:44   PURDYECH
//Add facility to get item by key without altering "current" item
 * 
 *    Rev 1.12   Jan 06 2003 16:43:02   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.11   Nov 27 2002 15:04:16   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.10   Oct 09 2002 17:40:48   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.9   Aug 29 2002 12:51:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   05 Jun 2002 13:55:16   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.7   22 Mar 2002 15:11:18   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.6   26 Jul 2001 13:43:16   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.5   Dec 13 2000 13:20:06   KOVACSRO
 * Added a method to check if current item is dummy.
 * 
 *    Rev 1.4   Nov 08 2000 19:56:46   DT24433
 * added list name support
 * 
 *    Rev 1.3   Aug 02 2000 15:31:34   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Mar 23 2000 16:23:46   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.9   Dec 08 1999 16:17:18   DT24433
 * added isNewItem
 * 
 *    Rev 1.8   Dec 07 1999 10:39:10   DT24433
 * use abstractprocessconstants.h
 * 
 *    Rev 1.7   Nov 22 1999 18:00:34   DT24433
 * performance improvements
 * 
 *    Rev 1.6   Oct 28 1999 16:48:34   DT24433
 * added commit method
 * 
 *    Rev 1.5   Oct 28 1999 13:48:24   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.4   Aug 06 1999 10:12:18   DT24433
 * support change item detection
 * 
 *    Rev 1.3   Aug 05 1999 15:12:08   DT24433
 * added bool return to setContainer
 * 
 *    Rev 1.2   Aug 03 1999 14:42:50   DT24433
 * container changes
 * 
 *    Rev 1.1   Jul 08 1999 10:03:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

