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
#include <bfdata\bffieldid.hpp>
#include <bfcbo\bfdatagroupid.hpp>

// Forward reference
class AbstractProcess;
class BFBase;

/**
  * This class contains the details for a substitute list.
  *
  * @author Jerry Leenerts
  * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/02/99</dd></dl>
  * @version 0.1
  */
class SubstituteListDetails : public AbstractListDetails
{
public:
   // We may want to change to direct access to substitutes instead of via
   //  fields or allow for both.
   /**
    * Constructor
    * 
    * @param idField The field id of associated field for substitutes, also
    *                used as the list id.
    * @param name name to return when getName() method is called.
    */
   SubstituteListDetails( AbstractProcess*,
                          const BFFieldId &idField, 
                          const DString &name = NULL_STRING );

   virtual ~SubstituteListDetails();

   /**
     * Override of base class which only throws exception if called.
     * @return a reference pointer to the list.
     */
   void *getContainer();
   /**
     * Get the current key.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a const reference to the key.
     */
   virtual const DString &getCurrentKey( const BFDataGroupId& idDataGroup );
   /**
     * Get the field for the current item.
     * An exception will be thrown if the list, item, or field are invalid
     * @param idField - ID of field to get.
     * @param bFormatted - true = get formatted value, false = get raw value.
     * @param strValueOut - A string reference where the field value will be
     * returned.
     * @param idDataGroup - Group to use for commit/rollback processing.
     */
   virtual void getField( const BFFieldId &idField,
                          bool bFormatted,
                          DString &strValueOut,
                          const BFDataGroupId& idDataGroup );
   /**
     * Override of base class which only throws exception if called.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return a reference pointer to the item.
     */
   void *getItem( const BFDataGroupId& idDataGroup );
   /**
     * Get the first key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool getFirstKey( const DString **rpStr,
                             const BFDataGroupId& idDataGroup );
   /**
     * Get the next key and make that the current item.
     * @param rpStr - pointer to const String pointer for returned key value.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool getNextKey( const DString **rpStr,
                            const BFDataGroupId& idDataGroup );
   /**
     * Method to get the number of items in the list.
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return an int with the number of items in the list
     */
   virtual int getNumberOfItemsInList( const BFDataGroupId& idDataGroup );
   /**
     * Method to load substitutes from CBO's / datadicitonary
     * @return boold - true = success, false = failure with conditions
     */
   bool loadSubstitutes( );
   /**
     * Method to set the list to the item which matches the specified key.
     * @param strKey - key to match
     * @param idDataGroup - Group to use for commit/rollback processing.
     * @return bool - true = item changed.
     */
   virtual bool setCurrentKey( const DString &strKey,
                               const BFDataGroupId& idDataGroup );
   /**
    * Method to set the list to the item which matches the specified key.
    * If the item doesn't exist current Item is cleared.
    * 
    * @param strKey   key to match
    * @param idDataGroup Group to use for commit/rollback processing.
    * 
    * @return bool - true = item changed.
    */
   virtual bool trySetCurrentKey( const DString &strKey,
                                  const BFDataGroupId& idDataGroup );
   /**
    * Override of method to set the field for the current item. Not implemented
    * for this class - an exception will be thrown if used.
    * 
    * @param idField    ID of field to get.
    * @param bFormatted true = get formatted value, false = get raw value.
    * @param strValue   A string reference of value to set.
    * @param idDataGroup   Group to use for commit/rollback processing.
    * 
    * @return SEVERITY.
    */
   virtual SEVERITY setField( const BFFieldId &idField,
                              bool bFormatted,
                              const DString &strValue,
                              const BFDataGroupId& idDataGroup );

protected:
   /**
    * Use lazy initialization to load substitutes.  Determine if the
    * substitutes have been loaded and load if necessary.
    * 
    * @param idDataGroup Group to use for commit/rollback processing.
    */
   void checkSubstitutes( const BFDataGroupId& idDataGroup = BF::HOST );
private:

   struct ITEM
   {
      DString code;
      DString description;
   };
   typedef std::vector< ITEM * > SUBSTITUTECONTAINER;

   bool _bItemValid;   // This is used because we can't always compare to end
   int _currentIndex;
   const DString *_rpStrCurrentKey;  // Key associated with current index
   SUBSTITUTECONTAINER _substitutes;
   BFFieldId _Substitute_Code;
   BFFieldId _Substitute_Description;

   void clear();
   int findIndexByKey( const DString &strKey, 
                       const BFDataGroupId& idDataGroup = BF::HOST );
   int getCurrentIndex() { return(_currentIndex);}
   const DString* setCurrentIndex( int idx, 
                                   const BFDataGroupId& idDataGroup = BF::HOST );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/SubstituteListDetails.hpp-arc  $
 * 
 *    Rev 1.14   Jan 06 2003 16:44:16   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.13   Nov 27 2002 15:04:56   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.12   Oct 09 2002 17:41:00   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.11   Sep 03 2002 11:08:46   PURDYECH
 * Further BFFieldId fixes
 * 
 *    Rev 1.10   Aug 29 2002 12:51:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   05 Jun 2002 13:55:16   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.8   22 May 2002 18:09:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   22 Mar 2002 15:12:08   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.6   May 08 2001 11:05:30   FENGYONG
 * Add name for API
 * 
 *    Rev 1.5   Nov 08 2000 20:01:40   DT24433
 * added list name support
 * 
 *    Rev 1.4   Aug 15 2000 14:00:42   YINGZ
 * multi locale support
 * 
 *    Rev 1.3   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Mar 08 2000 11:36:06   DT24433
 * removed dependency on ddinclude file
 * 
 *    Rev 1.1   Feb 15 2000 18:55:02   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Oct 28 1999 13:48:26   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.6   Aug 11 1999 14:03:18   DT24433
 * key string returned is now unique
 * 
 *    Rev 1.5   Aug 11 1999 11:00:20   DT24433
 * changed key from index to host code
 * 
 *    Rev 1.4   Aug 06 1999 11:17:58   DT24433
 * support change item detection
 * 
 *    Rev 1.3   Aug 03 1999 14:55:30   DT24433
 * container changes
 * 
 *    Rev 1.2   Jul 21 1999 11:11:38   VASILEAD
 * Fix by Jerry
 * 
 *    Rev 1.1   Jul 08 1999 10:03:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
