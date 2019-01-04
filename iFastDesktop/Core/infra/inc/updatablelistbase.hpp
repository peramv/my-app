#ifndef UPDATABLELISTBASE_HPP
#define UPDATABLELISTBASE_HPP

#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */ 


// Forward declare classes used in implementation
class UpdatableListBaseImpl;
class updListItem;
class CBOBase;

#ifndef INCLUDED_MAP
#include <map>
#define INCLUDED_MAP
#endif

#ifndef  CBOBASE_HPP
#include "cbobase.hpp"
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITION_HPP
#include "condition.hpp"
#endif

#ifndef LISTITERATOR_HPP
#include "listiterator.hpp"
#endif

#ifndef LISTBASE_HPP
#include "listbase.hpp"
#endif

// Typedef for UpdatableListBase iterator
typedef map< DString, 
             updListItem *,
             less<DString> >::const_iterator UPDLIST_ITER;

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * UpdatableListBase is a base class used for
 * updating lists of items(repeats). For each read-only Data object(repeat)
 * there should be a corresponding CBOBase derived object if an
 * update needs to occur for the Data object in question.
 * 
 * UpdatableListBase derives from ListBase
 * and thus inherits the read-only list functionality.
 * UpdatableListBase has a corresponding implementation class
 * called UpdatableListBaseImpl. The UpdatableListBaseImpl methods
 * contain the actual implementation for each method in
 * UpdatableListBase.
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * Derive a class from UpdatableListBase if you need to
 * represent a business list used for updates.(e.g. AccountList)
 * 
 * An instance of an UpdatableListBaseImpl class
 * will contain a map of pointers to updListItems.
 * Each updListItem will contain a Data object(before
 * image) and potentially a CBOBase derived
 * object(After image) if an update is needed.
 * The Data object is an individual repeat from the
 * list of repeats contained in the ListBaseImpl
 * parent class.
 * 
 * UpdatablelistbaseImpl manages the list of updListItems
 * by keeping items ordered by unique string keys and by
 * marking each item with the following activity types:
 * NONE,
 * ITEM_UPDATED,
 * ITEM_ADDED,
 * ITEM_DELETED
 * 
 * UpdatableListBase offers an interface in the form of
 * setObject and getOject methods that take string keys
 * or iterators as parameters. A string key
 * should be in the format of an IDI string, example:
 * Fund_Code=0000001;Account_Number=00000054961;
 * The string key will be used for searching through
 * a list of CBO and Data objects.
 * 
 * An UpdatableListBase derived object can be
 * used to instantiate a CBEBase derived class
 * to perform updates.
 * 
 * UpdatableListBase rollback capability :
 * The UpdatableListBaseImpl class allows you to roll the list & activity back
 * to a set checkpoint
 * Using the methods setCheckpointForRollBack(const string&)  &
 * rollBackListToCheckpoint(const string&)
 * 
 * Notes on using the rollback capability
 * 
 * 1)  After executing a rollback, the List will own the pointers to the
 *     objects in the restored list;
 * 
 * 2)  After a successful rollback the checkpoint for that strLabel is lost.
 * 
 * 3)  Multiple rollback points are supported.  If a strLabel is reused,
 *     the previous one is removed and the new checkpoint for the strLabel
 *     will be in effect.
 * 
 * 4)  If a string Label does not exist the list will throw an exception
 *     bool method  doesCheckpointExist(const string&) is provided for
 *     programmer protection
 * 
 * @see ListBase
 * @see CBOBase
 * @see CBEBase
 */
class CBOBASE_LINKAGE UpdatableListBase : public ListBase
{
public:

   /**
    * This method should not be used.
    * It is not fully implemented
    * and will be removed in future
    * versions of UpdatableListBaseImpl.
    * 
    * It's original intent was to
    * fill the list with CBO objects
    * that are instantiated from the
    * Data objects that are contained in the list.
    * 
    * @return NO_CONDITION if succesful
    * @see constructCBOFromDataObject
    */
   SEVERITY constructCBOForAllDataItems();

   /**
    * Use this method when trying to mark an
    * item as deleted so that a delete transaction
    * will occur on the host.  Or, use this method
    * to clear out an item from the UpdatableListBaseImpl
    * collection that is marked as ITEM_ADDED.
    * 
    * This method does the following:
    * 
    * 1. It will first check to see if the key is
    * in the UpdatableListBaseImpl collection.
    * If not found, the list of
    * Data objects(contained in ListBaseImpl)
    * will be searched also.  If the
    * key is found in the Data object list then
    * a new item will be added to the UpdatableListImpl
    * collection and marked with the ITEM_DELETED flag.
    * 
    * 2.  If the search key is found in the
    * UpdatableListBaseImpl collection, then the ACTIVITY
    * flag will be checked. If the ITEM_ADDED flag
    * is on for the found item then that item will be
    * removed from the collection.  If the item is
    * not marked with ITEM_ADDED then the ACTIVITY flag
    * will changed to ITEM_DELETED. Removal of the item
    * will not be performed.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return NO_CONDITION if successful
    *         SEVERE_ERROR if the string key value is not
    *         found in the list.
    * @see setObject
    * @see getObject
    * @see ACTIVITY
    */
   virtual SEVERITY deleteObject( const DString& strKey );

   /**
    * Use this method when working with the rollback
    * functionality provided by UpdatableListBase.
    * This method will search the collection of
    * checkpoints to see if one exists for the
    * requested string label value.
    * 
    * @param strLabel A unique string label used to reference the checkpoint
    * @return true if the labeled checkpoint exists
    *         false if the labeled checkpoint does not exist
    * @see setCheckpointForRollBack
    * @see rollBackListToCheckpoint
    */
   bool doesCheckpointExist(const DString& strLabel );

   /**
    * Stream out the contents of an UpdatableListBase.
    * This method will output the following:
    *  
    *  1. string key values in the UpdatableListBaseImpl collection
    *  2. whether or  not a Data object exists for an item in the list
    *  3. whether or not a  CBO exists for an item in the list
    *  4. the current activity for all items in the list
    *  5. whether or not the list owns(will delete in dtor )
    *     a CBO contained in the list
    * 
    * @param outStream A stream that will be filled with the contents of a list.
    *                  cout can be passed in if dumping to the console.
    */
   void dumpList( i_ostream& outStream ) const;

   /**
    * Use this method to get a pointer to a CBOBase derived
    * object that contains an instance of an UpdatableListBase
    * derived class
    * 
    * @return A pointer to a CBOBase object
    * @see setContainer
    */
   CBOBase * getContainer();

   /**
    * Populate a provided Data object with data
    * collected from a Data object contained
    * by ListBaseImpl or from a CBO contained by
    * UpdatableListBaseImpl.  If the string key
    * value is not found in the UpdatableListBaseImpl
    * collection then a search will be performed
    * on the ListBaseImpl Data object list.
    * 
    * This method will figure out the iterator to
    * work with and then call the getData overload
    * that takes an iterator to get the data from
    * a CBO in the list.
    * 
    * If a CBO does not exist, then the data will
    * be extracted from a Data object contained
    * by ListBaseImpl
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @param data   A user provided data object to hold retrieved data
    * @param fAppendNewTags
    *               A boolean value that, if set to true, means we
    *               want to append any field tags we use for a
    *               Data setElementValue() method call that do not
    *               currently exist in the Data object we are trying
    *               to populate. It defaults to false.
    *               If it is false the setElementValue method calls
    *               will fail if the field tag cannot be found in
    *               the Data object.
    * @param fUseDataObjectOnly
    *               This is a boolean value that, if set to true, we
    *               only want to gather data from the before image
    *               Data object. We do not want to grab any values
    *               from the instance field info. It defaults to false.
    *               If it is false, we will first get values from
    *               the before image Data object and then get values
    *               from the instance field info.
    * @return NO_CONDITION if successful
    * @see Data
    * @see setElementValue
    */
   virtual SEVERITY getData( const DString & strKey, 
                             Data & data, 
                             bool fAppendNewTags = false, 
                             bool fUseDataObjectOnly = false );

   /**
    * Populate a provided Data object with data
    * collected from a Data object contained
    * by ListBaseImpl or from a CBO contained by
    * UpdatableListBaseImpl.
    * 
    * This method will use the iterator to
    * get to a CBO in the list. This method
    * will assert if the iterator passed in
    * is equal to iter.end()
    * 
    * 
    * If a CBO does not exist, then the data will
    * be extracted from a Data object contained
    * by ListBaseImpl.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @param data   A user provided data object to hold retrieved data
    * @param fAppendNewTags
    *               A boolean value that, if set to true, means we
    *               want to append any field tags we use for a
    *               Data setElementValue() method call that do not
    *               currently exist in the Data object we are trying
    *               to populate. It defaults to false.
    *               If it is false the setElementValue method calls
    *               will fail if the field tag cannot be found in
    *               the Data object.
    * @param fUseDataObjectOnly
    *               This is a boolean value that, if set to true, we
    *               only want to gather data from the before image
    *               Data object. We do not want to grab any values
    *               from the instance field info. It defaults to false.
    *               If it is false, we will first get values from
    *               the before image Data object and then get values
    *               from the instance field info.
    * @return NO_CONDITION if successful
    * @see Data
    * @see setElementValue
    */
   virtual SEVERITY getData( UPDLIST_ITER iter, 
                             Data & data, 
                             bool fAppendNewTags = false, 
                             bool fUseDataObjectOnly = false );

   /**
    * This method should be implemented in a derived
    * class if planning to use this list with
    * a CBEBase derived object.
    * 
    * This method is used during the update process.
    * CBEBaseImpl will call this method after
    * calling the performIsValidForUpdateEdits method
    * and after calling the shouldUpdateBeBuilt method
    * when performing updates.  The method that calls
    * this method is the buildUpdates method
    * in CBEBaseImpl.
    * 
    * The implementation of this method in the derived class
    * may want to perform special processing based on
    * the different ACTIVITY flags for each item in
    * the list.
    * 
    * @param iter     a UPDLIST_ITER iterator that should point to a
    *                 position in the collection of CBO/Data objects.
    * @param strLabel A string value that has been registered with
    *                 CBEBaseImpl.  A derived class from CBEBaseImpl
    *                 will register the label by call _registerView
    *                 method. This label is an arbitrary name
    *                 that describes the data that will be updated
    *                 to the host.
    * @param data     A user provided data object to hold retrieved data
    * @param fAppendNewTags
    *                 A boolean value that, if set to true, means we
    *                 want to append any field tags we use for a
    *                 Data setElementValue() method call that do not
    *                 currently exist in the Data object we are trying
    *                 to populate. It defaults to false.
    *                 If it is false the setElementValue method calls
    *                 will fail if the field tag cannot be found in
    *                 the Data object.
    * @param fUseDataObjectOnly
    *                 This is a boolean value that, if set to true, we
    *                 only want to gather data from the before image
    *                 Data object. We do not want to grab any values
    *                 from the instance field info. It defaults to false.
    *                 If it is false, we will first get values from
    *                 the before image Data object and then get values
    *                 from the instance field info.
    * @return NO_CONDITION if successful
    * @see Data
    * @see setElementValue
    * @see CBEBaseImpl
    */
   virtual SEVERITY getData( UPDLIST_ITER & iter,
                             const DString & strLabel,
                             Data & data,
                             bool fAppendNewTags = false,
                             bool fUseDataObjectOnly = false ) const;
    
   /**
    * Retrieves the pointer to Data object
    * at the specified location in the collection
    * of CBO/Data objects.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return A pointer to a Data object
    */
   const Data *getDataItemPtr( const UPDLIST_ITER &iter ) const;

   /**
    * The key that is constructed from the
    * Data object should be a unique value for each
    * Data object contained by ListBaseImpl.  The
    * key should be built in the IDI string format. example:
    * Fund_Code=0000001;Account_Number=00000054961;
    * 
    * A derived class would do the following:
    * <pre><dir>
    * 
    * SEVERITY AccountListImpl::getDataObjectKey( Data& dataItem, string& strKey )
    * {
    *    TRACE_METHOD( "AccountListImpl", "getDataObjectKey( Data&, string& )" );
    * 
    *    //build the IDI string for the unique key
    *    strKey = "Account_Number=";
    *    strKey += dataItem.getElementValue( "Account_Number" );
    *    strKey += ";";
    *    strKey += "Social_Security_Number=";
    *    strKey += dataItem.getElementValue( "Social_Security_Number" );
    *    strKey += ";";
    * 
    *    return NO_CONDITION;
    * }
    * </pre></dir>
    * 
    * @param listBaseDataObject
    *               Data object to extract the key out of
    * @param strKey A string to be populated with the Data objects key
    * @return NO_CONDITION if successful
    * @see Data
    */
   virtual SEVERITY getDataObjectKey( Data & listBaseDataObject, 
                                      DString & strKey );

   /**
    * Populates a string with the requested field's value if found.
    * Formatting of the value according to a specified mask
    * will occur upon request. The mask can be specified
    * in a Data object or in the CLASS_FIELD_INFO
    * of a contained CBO.
    * 
    * This method will first check for an existing CBO
    * at the iterator position, if a CBO does not exist
    * then the corresponding Data object will be queried
    * for the requested field value.
    * 
    * @param iter       A UPDLIST_ITER iterator that should point to a
    *                   position in the collection of CBO/Data objects.
    * @param strField   A unique string tag indentifier for the registered field
    *                   used to index into a contained CBO's instancefieldinfo.
    *                   The string tag indentifier for a field is set up in
    *                   the CLASS_FIELD_INFO of a contained CBO
    *                   or in a .vw file for a contained Data object.
    * @param strOut     The user supplied string to hold the field value
    * @param fFormatted A boolean value, if set to true, we will format
    *                   the value using a field mask.  We will first check
    *                   to see if a mask is supplied in the CLASS_FIELD_INFO
    *                   of a contained CBO. If one does not exist we will try to format the
    *                   string value using the Data object(before image) mask.
    *                   We will also use any substitution values specified
    *                   in the .vw file.
    *                   It defaults to false.
    *                   
    *                   If it is false, no formatting or substitutions will occur.
    * @return NO_CONDITION if successful
    * @see CLASS_FIELD_INFO
    * @see CBOBaseImpl
    * @see setField
    * @see Data
    */
   SEVERITY getField( UPDLIST_ITER iter, 
                      const DString & strField, 
                      DString & strOut,
                      bool fFormatted = true ) const;

   /**
    * Retrieve the iterator pointing to the postition of
    * the updListItem(CBO/Data) associated with the passed string
    * key.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return a UPDLIST_ITER iterator that should point to a
    *         position in the collection of CBO/Data objects.
    * @see getIterBegin
    * @see getIterEnd
    */
   UPDLIST_ITER getIter(const DString& strKey);

   /**
    * Retrieve the iterator pointing to the beginning of
    * the collection of CBO/Data objects.
    * 
    * @return a UPDLIST_ITER iterator that should point to the
    *         beginning of the collection of CBO/Data objects.
    * @see getIterEnd
    * @see getIter
    */
   UPDLIST_ITER getIterBegin();

   /**
    * Retrieve the iterator pointing to the end of
    * the collection of CBO/Data objects.
    * 
    * @return a UPDLIST_ITER iterator that should point to the end
    *         of the collection of CBO/Data objects.
    * @see getIterBegin
    * @see getIter
    */
   UPDLIST_ITER getIterEnd();

   /**
    * Get the unique string key value for the
    * passes in iterator position.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return A unique string key value used for searching
    *         the collection of CBO/Data objects. This key
    *         will be in the format of an IDI string, example:
    *         Fund_Code=0000001;Account_Number=00000054961;
    * @see getIter
    */
   DString getKey( UPDLIST_ITER iter );

   /**
    * Retrieve the position in the list that matches
    * the specified string tag-value pairs. This method
    * makes a call to the getField method to retrieve
    * the values to comapre.
    * 
    * @param IDIString A collection of field-value pairs to search for
    *                  in the contained CBO or Data object.
    *                  This parm should be in the format of an IDI string,
    *                  Example:
    *                  Fund_Code=0000001;Account_Number=00000054961;
    * @param iter      a UPDLIST_ITER iterator that should point to a
    *                  position in the collection of CBO/Data objects.
    *                  This parm allow you to specfiy a starting position.
    * @return a UPDLIST_ITER iterator that should point to a
    *         position in the collection of CBO/Data objects.
    *         return iter.end() if not found
    */
   UPDLIST_ITER getMatchingPositionFrom( const DString & IDIString,
                                      UPDLIST_ITER& iter ) const;

   /**
    * Creates a unique key base on a sequential integer
    * value that is incremented every time this method
    * is called.
    * 
    * The key is built as follows:
    * 
    * "NEW" + "1" --> first time called
    *    return value would be "NEW1"
    * "NEW" + "2" --> second time called
    *    return value would be "NEW2"
    * "NEW" + "3" --> third time called
    *    return value would be "NEW3"
    *    
    * This method is used when adding new
    * CBOs to the list that do not have 
    * before images. This type of update
    * would be considered as an ADD( The item
    * in the list would be marked as ITEM_ADDED).   
    * 
    * @param strKey A string variable to be filled with
    *               a unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               will be in the format of "NEW1", "NEW2", "NEW3", etc,
    *               
    * @return true if successful
    * @see getKey
    * @see getIter
    * @see setObject
    */
   bool getNextKey(DString &strKey);

   /**
    * Return the number of items in the list that have the ACTIVITY Flag = ITEM_ADDED
    * 
    * @return An integer value of the number items in the list
    *         that are marked with ACTIVITY set to ITEM_ADDED
    * @see ACTIVITY
    */
   int getNumberOfObjectsActivityTypeADDED( )const;

   /**
    * Return the number of items in the list that have the ACTIVITY Flag = ITEM_DELETED
    * 
    * @return An integer value of the number items in the list
    *         that are marked with ACTIVITY set to ITEM_DELETED
    * @see ACTIVITY
    */
   int getNumberOfObjectsActivityTypeDELETED( )const;

   /**
    * Return the number of items in the list that have the ACTIVITY Flag = NONE
    * 
    * @return An integer value of the number items in the list
    *         that are marked with ACTIVITY set to NONE
    * @see ACTIVITY
    */
   int getNumberOfObjectsActivityTypeNONE( )const;

   /**
    * Return the number of items in the list that have the ACTIVITY Flag = ITEM_UPDATED
    * 
    * @return An integer value of the number items in the list
    *         that are marked with ACTIVITY set to ITEM_UPDATED
    * @see ACTIVITY
    */
   int getNumberOfObjectsActivityTypeUPDATED( )const;

   /**
    * Return the number of CBO objects in the list
    * (not Data objects).
    * 
    * The number of CBOs can equate to the number
    * of updates to the host that would occur.
    * 
    * @return An integer value of the number of CBOs contained
    *         in the list.
    */
   int getNumberOfObjectsInList();

   /**
    * Retrieve a pointer to the CBOBase object
    * found at the passed in iterator position in
    * the collection of CBO/Data objects.
    * 
    * @param iter      a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return A pointer to a CBOBase object.
    * @see setObject
    * @see deleteObject
    */
   CBOBase * getObject(UPDLIST_ITER iter);

   /**
    * Retrieve a full copy of the CBOBase object
    * found at the passed in iterator position in
    * the collection of CBO/Data objects.
    * 
    * @param iter       a UPDLIST_ITER iterator that should point to a
    *                position in the collection of CBO/Data objects.
    * @param rObject A CBOBase variable to be filled with a full copy
    *                of the requested CBO
    * @return NO_CONDITION if successful
    * @see setObject
    * @see deleteObject
    */
   SEVERITY  getObject(UPDLIST_ITER iter, CBOBase &rObject );

   /**
    * Retrieve a pointer to the CBOBase object
    * found at the passed in iterator position in
    * the collection of CBO/Data objects.
    * 
    * This method finds the iterator base on the passed-in
    * string key value and then calls the overloaded
    * getObject method that takes an iterator.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return A pointer to a CBOBase object.
    * @see setObject
    * @see deleteObject
    */
   virtual CBOBase * getObject( const DString strKey );

   /**
    * Retrieve a full copy of the CBOBase object
    * found at the passed in iterator position in
    * the collection of CBO/Data objects.
    * 
    * This method finds the iterator base on the passed-in
    * string key value and then calls the overloaded
    * getObject method that takes an iterator.
    * 
    * @param strKey  A unique string key value used for searching
    *                the collection of CBO/Data objects. This key
    *                should be in the format of an IDI string, example:
    *                Fund_Code=0000001;Account_Number=00000054961;
    * @param rObject A CBOBase variable to be filled with a full copy
    *                of the requested CBO
    * @return NO_CONDITION if successful
    * @see setObject
    * @see deleteObject
    */
   virtual SEVERITY getObject( const DString strKey, 
                               CBOBase & rObject );
   
   /**
    * Retrieve the update level associated with an
    * instance of an UpdatableListBaseImpl derived object.
    * 
    * Use this method as a means of notification for
    * changes that have occurred on the current 
    * instance of a derived class.
    * 
    * For example, an instance of an UpdatableListBase
    * derived class may be passed around and 
    * changed by different dialogs in a GUI application.
    * DialogA would get the current update level
    * and then call a DialogB method which may also
    * change the instance and increment the update level.
    * After calling a DialogB method the DialogA code
    * would check the update level to see if something
    * has changed and then do some special processing
    * accordingly.
    * 
    * @return A long value indicating the update level for the current
    *         instance
    * @see setUpdateLevel
    * @see incrementUpdateLevel
    */
   long getUpdateLevel() const;

   /**
    * Use this method to see if a Data object exists at
    * the specified position.  The specified position
    * could have the following:
    * 
    *  1. a Data object and a CBO
    *  2. a Data object only
    *  3. a CBO only
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if a Data object exists at the specified position
    *         false if a Data object does not exist at the specified
    *         position.
    */
   bool hasData( const UPDLIST_ITER &iter ) const;

   /**
    * Use this method to see if a CBO exists at
    * the specified position.  The specified position
    * could have the following:
    *  
    *  1. a Data object and a CBO
    *  2. a Data object only
    *  3. a CBO only
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if a CBO exists at the specified position
    *         false if a CBO does not exist at the specified
    *         position.
    * @see hasData
    */
   bool hasObject( const UPDLIST_ITER &iter ) const;

   /**
    * This method sets a pointer access flag to true or false.
    * If true is passed in, then the getObject
    * method that returns a CBOBase * can be
    * called on the current instance.
    * If false is passed in, then only the getObject
    * methods that return a full copy of the CBO
    * can be used for the current instance.
    * 
    * @param fAllowConstPointerAccess
    *               This boolean variable will default to false.
    * @return NO_CONDTION if successful
    * @see getObject
    */
   SEVERITY init( bool fAllowConstPointerAccess = false );

   /**
    * Determine if the item at the specified position
    * in the list has the ACTIVITY Flag = ITEM_ADDED.
    * 
    * @param iter      a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if ITEM_ADDED is on for the specified list item
    *         false if ITEM_ADDED is off for the specified list item
    * @see ACTIVITY
    * @see isUpdated
    * @see isDeleted
    */
   bool     isAdded(UPDLIST_ITER iter);

   /**
    * Determine if the item at the specified position
    * in the list has the ACTIVITY Flag = ITEM_DELETED.
    * 
    * @param iter      a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if ITEM_DELETED is on for the specified list item
    *         false if ITEM_DELETED is off for the specified list item
    * @see ACTIVITY
    * @see isAdded
    * @see isUpdated
    */
   bool     isDeleted(UPDLIST_ITER iter);

   /**
    * Takes the specified CBOBase pointer and searches
    * for it in the CBO/Data object list. This
    * method trys to find a match base on 
    * the pointer address.
    * 
    * @param pCBOBase A pointer to a CBOBase derived object
    * @return true if the specfied CBO is in the list
    *         false if the specfied CBO is not in the list
    * @see setObject
    * @see getObject
    */
   bool     isObjectInList( CBOBase *pCBOBase ) const;

   /**
    * See if an object is in the CBO/Data object list
    * and if the current instance of UpdatableListBaseImpl
    * will delete the pointer on destruction.
    * 
    * Ownership of the CBO pointer can be
    * specified in a call to the setObject method.
    * If you tell an UpdatableListBaseImpl instance
    * to own the CBO, then the CBO pointer will get
    * deleted upon destruction of the
    * UpdatableListBaseImpl instance.
    * 
    * @param pCBOBase A pointer to a CBOBase derived object
    * @return true if the specified CBO is in the list and is
    *         owned(will be deleted) by UpdatableListImpl
    *         
    *         false if the specified CBO is in the list
    *         but is not owned(will not be deleted) by
    *         UpdatableListImpl
    * @see setObject
    */
   bool     isObjectOwned( CBOBase *pCBOBase ) const;

   /**
    * Find if anything in the list has been changed
    * If all items in the CBO/Data object list are
    * marked with the ACTIVITY flag of NONE, then no
    * changes have occured to the current instance of an
    * UpdatableListBaseImpl.
    * 
    * This method is used during the update process.
    * CBEBaseImpl will call this method to see
    * if any updated data needs to be gathered and
    * sent to the host.  If isUpdated returns true
    * CBEBaseImpl will then call the following methods:
    * 
    * performIsValidForUpdateEdits
    * shouldUpdateBeBuilt
    * getData
    *   
    * The method that calls
    * this method is the isUpdated method
    * in CBEBaseImpl.
    * 
    * 
    * Methods that change the activity are as follows:
    * setObject
    * deleteObject
    * removeActivity
    * removeObjectAndActivity
    * addObjectFlag
    * clearList
    * 
    * @return true if an item in the CBO/Data object list is
    *         marked with the one of following ACTIVITY flags:
    *         ITEM_ADDED
    *         ITEM_DELETED
    *         ITEM_UPDATED
    *         
    *         
    *         false if all items in the CBO/Data object list are
    *         marked with the ACTIVITY flag of NONE
    * @see setObject
    * @see deleteObject
    * @see removeActivity
    * @see removeObjectAndActivity
    * @see addObjectFlag
    * @see clearList
    * @see performIsValidForUpdateEdits
    * @see shouldUpdateBeBuilt
    * @see getData
    */
   bool isUpdated() const;
   
   /**
    * Determine if the item at the specified position
    * in the list has the ACTIVITY Flag = ITEM_UPDATED.
    * 
    * A call to the setObject method will turn the
    * ITEM_UPDATED flag on if there is an existing
    * Data object in the CBO/Data object list.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if ITEM_UPDATED is on for the specified list item
    *         false if ITEM_UPDATED is off for the specified list item
    * @see ACTIVITY
    * @see isAdded
    * @see isDeleted
    * @see setObject
    */
   bool     isUpdated(UPDLIST_ITER iter);

   /**
    * Sets the UpdatableListBaseImpl to delete the
    * CBOBase pointer associated with a list item
    * when the UpdatableListBaseImpl instance
    * is destructed.
    * 
    * Ownership of the CBO pointer can be
    * specified in a call to the setObject method.
    * If you tell an UpdatableListBaseImpl instance
    * to own the CBO, then the CBO pointer will get
    * deleted upon destruction of the
    * UpdatableListBaseImpl instance.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if successful
    * @see makeUnowned
    * @see setObject
    */
   bool makeOwned( UPDLIST_ITER& iter );

   /**
    * Sets the UpdatableListBaseImpl to delete the
    * CBOBase pointer associated with a list item
    * when the UpdatableListBaseImpl instance
    * is destructed.
    * 
    * Ownership of the CBO pointer can be
    * specified in a call to the setObject method.
    * If you tell an UpdatableListBaseImpl instance
    * to own the CBO, then the CBO pointer will get
    * deleted upon destruction of the
    * UpdatableListBaseImpl instance.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return true if successful
    * @see makeUnowned
    * @see setObject
    */
   bool makeOwned( const DString& strKey );

   /**
    * Sets the UpdatableListBaseImpl to not delete the
    * CBOBase pointer associated with a list item
    * when the UpdatableListBaseImpl instance
    * is destructed.
    * 
    * Ownership of the CBO pointer can be
    * specified in a call to the setObject method.
    * If you tell an UpdatableListBaseImpl instance
    * to own the CBO, then the CBO pointer will get
    * deleted upon destruction of the
    * UpdatableListBaseImpl instance.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if successful
    * @see makeOwned
    * @see setObject
    */
   bool makeUnowned( UPDLIST_ITER& iter );

   /**
    * Sets the UpdatableListBaseImpl to not delete the
    * CBOBase pointer associated with a list item
    * when the UpdatableListBaseImpl instance
    * is destructed.
    * 
    * Ownership of the CBO pointer can be
    * specified in a call to the setObject method.
    * If you tell an UpdatableListBaseImpl instance
    * to own the CBO, then the CBO pointer will get
    * deleted upon destruction of the
    * UpdatableListBaseImpl instance.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return true if successful
    * @see makeOwned
    * @see setObject
    */
   bool makeUnowned( const DString& strKey );

   /**
    * This method should be implemented in a derived 
    * class.  This method should allow you to 
    * copy or use any information contained in a
    * pre-existing instance of a UpdatableListBaseImpl.  
    * 
    * @param pCopy  A pointer to an UpdatableListBaseImpl object
    * @return NO_CONDITION if successful
    */
   SEVERITY modelFrom( const UpdatableListBase *pCopy );

   /**
    * This method should be implemented in a derived
    * class from UpdatableListBaseImpl.
    * 
    * This method is used during the update process.
    * CBEBaseImpl will call this method as one of
    * the first steps in performing updates.  The
    * method that calls this method is the buildUpdate
    * method in CBEBaseImpl.
    * 
    * The implementation of this method in the derived class
    * should atleast make a call to validateAll 
    * to make sure all of the business data is valid for the
    * CBO contained at the specified location.
    * 
    * @param iter     a UPDLIST_ITER iterator that should point to a
    *                 position in the collection of CBO/Data objects.
    * @param strLabel A string value that has been registered with
    *                 CBEBaseImpl.  A derived class from CBEBaseImpl
    *                 will register the label by calling the _registerView
    *                 method. This label is an arbitrary name
    *                 that describes the data that will be updated
    *                 to the host.
    * @return NO_CONDITION if successful
    * @see CBEBaseImpl
    * @see registerView
    * @see buildUpdate
    * @see shouldUpdateBeBuilt
    * @see getData
    */
   virtual SEVERITY performIsValidForUpdateEdits( UPDLIST_ITER &
                                                            iter,
                                const DString & strLabel ) const;

   /**
    * This method spins through the read-only list
    * of Data objects contained in ListBaseImpl and
    * creates a new list of Data objects contained
    * by UpdatableListBaseImpl. The new list
    * of Data objects is considered to be a list
    * of "before images". Any CBO that is set in
    * to the list for the corresponding Data object
    * will be known as the "after image".
    * 
    * This method will call the getDataObjectKey
    * method which should be implemented in the derived
    * class.  The string key value that is returned will
    * be the unique key that is used for storing off
    * each individual Data object.  If a Data object
    * with the same key already exists, then the previous
    * Data object will be overlayed with the new one.
    * 
    * If the getDataObjectKey implementation in a
    * derived class does not build a key. The key
    * will be defaulted to an integer value.
    * 
    * For each Data object that is added to the list,
    * the following default values will be used:
    * 
    * 1.  The corresponding CBO pointer will default to null.
    * 2.  The delete CBO instance flag will default to false
    *     Meaning:  UpdatableListBaseImpl will not delete any
    *     contained CBOs upon destruction by default
    * 3.  The corresponding ACTIVITY flag will default to NONE
    * 4.  Any miscellaneous flags will be turned off
    * 
    * A derived class should call this method from
    * the implementation of an init method.  The
    * derived classs is required to call the
    * setViewData method before calling this method.
    * 
    * @return NO_CONDITION if successful
    * @see ListBaseImpl
    * @see setViewData
    * @see getDataObjectKey
    */
   SEVERITY populateListWithDataObjects( );

   /**
    * Populates the CBO/Data object list contained
    * in UpdatableListBaseImpl using a pair of
    * ListIterators. A ListIterator acts like
    * an STL iterator. A user of this method should
    * be able to pass iter(begin) and iter(end) as
    * a pair of ListIterators if desired.
    * 
    * This method spins through a range of read-only
    * Data objects contained in ListBaseImpl and
    * creates a new list of Data objects contained
    * by UpdatableListBaseImpl. The new list
    * of Data objects is considered to be a list
    * of "before images". Any CBO that is set in
    * to the list for the corresponding Data object
    * will be known as the "after image".
    * 
    * This method will call the getDataObjectKey
    * method which should be implemented in the derived
    * class.  The string key value that is returned will
    * be the unique key that is used for storing off
    * each individual Data object.  If a Data object
    * with the same key already exists, then the previous
    * Data object will be overlayed with the new one.
    * 
    * If the getDataObjectKey implementation in a
    * derived class does not build a key. The key
    * will be defaulted to an integer value.
    * 
    * 
    * For each Data object that is added to the list,
    * the following default values will be used:
    * 
    * 1.  The corresponding CBO pointer will default to null.
    * 2.  The delete CBO instance flag will default to false
    *     Meaning:  UpdatableListBaseImpl will not delete any
    *     contained CBOs upon destruction by default
    * 3.  The corresponding ACTIVITY flag will default to NONE
    * 4.  Any miscellaneous flags will be turned off
    * 
    * A derived class can  call this method instead
    * of the overloaded populateListWithDataObjects
    * method from the implementation of an init method.
    * The derived classs is required to call the
    * setViewData method before calling this method.
    * 
    * @param myPair
    * @return NO_CONDITION if successful
    * @see ListBaseImpl
    * @see setViewData
    * @see getDataObjectKey
    */
   SEVERITY populateListWithDataObjects( const pair<ListIterator,
                                         ListIterator>myPair );

   /**
    * This method should be implemented in a derived
    * class.
    * 
    * This method is usually overridden in the derived
    * class to implement code that will grab the latest
    * data for the list.  The refresh is
    * usually called after updates to the host have
    * occurred.
    * 
    * A refresh method could call the derived class
    * init method or make a view call.
    * 
    * @return NO_CONDITION if successful
    */
   virtual SEVERITY refresh( void );

   /**
    * Resets the ACTIVITY flag for a specified item to
    * NONE.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return true if successful
    * @see ACTIVITY
    */
   bool removeActivity(UPDLIST_ITER iter);

   /**
    * Resets the ACTIVITY flag for a specified item to
    * NONE.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return true if successful
    * @see ACTIVITY
    */
   bool removeActivity( const DString& strKey );

   /**
    * Removes all CBO pointers from the CBO/Data object
    * list. And resets the ACTIVITY flag for all items to
    * NONE. This method will delete the CBO pointer if
    * the current UpdatableListBaseImpl instance owns
    * the pointer.
    * 
    * @return NO_CONDITION if successful
    * @see ACTIVITY
    * @see setObject
    * @see removeObjectAndActivity
    * @see removeActivity
    */
   virtual SEVERITY removeAllObjectsAndActivity();

   /**
    * Removes a CBO pointer at the specified position
    * from the CBO/Data object list. And resets the
    * ACTIVITY flag for the specified item to
    * NONE. This method will delete the CBO pointer if
    * the current UpdatableListBaseImpl instance owns
    * the pointer.
    * 
    * @param iter   a UPDLIST_ITER iterator that should point to a
    *               position in the collection of CBO/Data objects.
    * @return NO_CONDITION if successful
    * @see ACTIVITY
    */
   virtual SEVERITY removeObjectAndActivity(UPDLIST_ITER iter);

   /**
    * Removes a CBO pointer at the specified position
    * from the CBO/Data object list. And resets the
    * ACTIVITY flag for the specified item to
    * NONE. This method will delete the CBO pointer if
    * the current UpdatableListBaseImpl instance owns
    * the pointer.
    * 
    * @param strKey A unique string key value used for searching
    *               the collection of CBO/Data objects. This key
    *               should be in the format of an IDI string, example:
    *               Fund_Code=0000001;Account_Number=00000054961;
    * @return NO_CONDITION if successful
    * @see ACTIVITY
    */
   virtual SEVERITY removeObjectAndActivity( 
                                        const DString & strKey );

   /**
    * Use this method when working with the rollback
    * functionality provided by UpdatableListBase.
    * 
    * This method will rollback the list to the
    * previously labeled snapshot and will restore
    * the previous ACTIVITY flag.
    * 
    *  Notes on using the rollback capability
    *  
    * 1.  After executing a rollback, the List will own the pointers to the
    *      objects in the restored list;
    *  
    * 2.  After a successful rollback the checkpoint for that strLabel is lost.
    *  
    * 3.  Multiple rollback points are supported.  If a strLabel is reused,
    *      the previous one is removed and the new checkpoint for the strLabel
    *      will be in effect.
    * 
    * 4.  If a string Label does not exist the list will throw an exception
    *      bool method  doesCheckpointExist(const string&) is provided for programmer protection
    * 
    * @param strLabel A unique string label used to reference the checkpoint
    * @return NO_CONDITION if successful
    * @see setCheckpointForRollBack
    * @see doesCheckpointExist
    */
   SEVERITY rollBackListToCheckpoint(const DString& strLabel );

   /**
    * Use this method when working with the rollback
    * functionality provided by UpdatableListBase.
    * 
    * This method takes a "snapshot" of the current list
    * and stores a copy of it with the specified label.
    * The current ACTIVITY flags will be maintained with the
    * current CBO pointers in the list.
    * 
    * The string label can be used when calling
    * the rollBackListToCheckPoint method.
    * 
    * @param strLabel A unique string label used to reference the checkpoint
    * @return NO_CONDITION if successful
    * @see rollBackListToCheckpoint
    * @see doesCheckpointExist
    */
   SEVERITY setCheckpointForRollBack( const DString& strLabel );

   /**
    * Use this method to know about the CBO that contains
    * the current instance of an UpdatableListBaseImpl
    * derived object.
    * 
    * In a CBOBaseImpl derived object, after calling
    * the init method of an UpdatableListBase derived
    * class, you can take the CBOBase derived object
    * pointer and set it into UpdatableListBaseImpl
    * using this method.
    * 
    * @param pContainer A pointer to a CBOBase derived object that contains
    *                   an instance of an UpdatableListBase derived class.
    * @see getContainer
    */
   void setContainer( CBOBase* pContainer );

   /**
    * Sets the provided CBOBase derived object pointer
    * into the CBO/Data object list.  This method
    * uses the string key to find the matching before
    * image Data object if one exists.  The string key
    * value should be in an IDI string format.
    * 
    * The default behavior is that UpdatableListBaseImpl
    * will not delete the pointer upon destruction.
    * 
    * If a CBO pointer already exists for the specified
    * string key, then the existing CBO pointer will
    * be over-written.  UpdatableListBaseImpl will delete
    * the CBO pointer if he owns it.
    * 
    * The corresponding ACTIVITY flag will be either
    * set to ITEM_ADDED or ITEM_UPDATED.
    * 
    * ITEM_ADDED is set if the before image Data object
    * does not exist in the CBO/Data object list.
    * 
    * ITEM_UPDATED is set if the before image Data object
    * does exist in the CBO/Data object list.
    * 
    * This method will also increment the updatelevel value
    * as a notification mechanism.
    * 
    * This method will also call the listHasBeenModified
    * method to notify the derived object that something
    * has changed.
    * 
    * @param strKey   A unique string key value used for searching
    *                 the collection of CBO/Data objects. This key
    *                 should be in the format of an IDI string, example:
    *                 Fund_Code=0000001;Account_Number=00000054961;
    * @param pCBOBase A pointer to a CBOBase derived object
    * @param fListOwnsObject
    *                 If set to true, the current instance of
    *                 UpdatableListBaseImpl will delete the CBO pointer
    *                 upon destruction of the instance.
    *                 
    *                 This variable defaults to false.
    *                 
    *                 If set to false the instance of UpdatableListBaseImpl
    *                 will not delete the CBO pointer.
    * @return NO_CONDITION if successful
    * @see getObject
    * @see deleteObject
    * @see removeObjectAndActivity
    * @see removeAllObjectsAndActivity
    * @see incrementUpdateLevel
    * @see listHasBeenModified
    */
   virtual SEVERITY setObject( DString & strKey, 
                               CBOBase * pCBOBase, 
                            const bool fListOwnsObject = false );

   /**
    * Set the update level associated with an
    * instance of an UpdatableListBaseImpl derived object.
    * 
    * Use this method as a means of notification for
    * changes that have occurred on the current
    * instance of a derived class.
    * 
    * For example, an instance of an UpdatableListBase
    * derived class may be passed around and
    * changed by different dialogs in a GUI application.
    * DialogA would get the current update level
    * and then call a DialogB method which may also
    * change the instance and increment the update level.
    * After calling a DialogB method the DialogA code
    * would check the update level to see if something
    * has changed and then do some special processing
    * accordingly.
    * 
    * @param lNewUpdateLevel
    *               A long value indicating the new update level for the current
    *               instance
    * @see getUpdateLevel
    * @see incrementUpdateLevel
    */
   void setUpdateLevel( long lNewUpdateLevel );

   /**
    * This method should be implemented in a derived
    * class.
    * 
    * This method is used during the update process.
    * CBEBaseImpl will call this method before
    * calling the performIsValidForUpdateEdits method
    * when performing updates.  The method that calls
    * this method is the buildUpdate method
    * in CBEBaseImpl.
    * 
    * The implementation of this method in the derived class
    * may want to check specific field values for
    * an contained CBO to see if the
    * data should be gathered for an update.  If the
    * update should be built, then a call to the
    * performIsValidForUpdateEdits method will be
    * made next.
    * 
    * @param iter     a UPDLIST_ITER iterator that should point to a
    *                 position in the collection of CBO/Data objects.
    * @param strLabel A string value that has been registered with
    *                 CBEBaseImpl.  A derived class from CBEBaseImpl
    *                 will register the label by call _registerView
    *                 method. This label is an arbitrary name
    *                 that describes the data that will be updated
    *                 to the host.
    * @return true if the data should be gathered for the
    *         current label we are working with. The
    *         getData method will be called.
    *         
    *         false if the data should not be gathered.
    *         The getData method will not be called.
    * @see CBEBaseImpl
    * @see registerView
    * @see buildUpdate
    * @see performIsValidForUpdateEdits
    * @see getData
    */
   virtual bool shouldUpdateBeBuilt( UPDLIST_ITER & iter, 
                                     const DString & strLabel ) 
                                                           const;

   /** Constructor */   
   UpdatableListBase();

   /** virtual destructor */
   ~UpdatableListBase();


protected:

   /**
    * Method used to make a FULL Copy of an UpdatableListBase 
    * 
    * @return Deep Copy of an UpdatableListBase
    */
   virtual UpdatableListBase * makeCopy( 
                                   const UpdatableListBase & copy,
                                  UpdatableListBase * pDeepCopy );

   UpdatableListBase::UpdatableListBase( PROTECTED_CREATION 
                                            protected_creation );

   UpdatableListBase( const UpdatableListBase &copy );
   UpdatableListBase & operator=( const UpdatableListBase &copy );

   bool _fCreatedImpl;

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
// $Log:   Y:/VCS/iFastAWD/inc/updatablelistbase.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:12   kovacsro
//Initial revision.
// 
//    Rev 1.13   28 Nov 2001 12:42:16   dt14177
// fixed linkage define
// 
//    Rev 1.12   May 23 2001 17:43:02   DT39990
// Added getContainer() method
// 
//    Rev 1.11   Dec 27 2000 16:10:56   dt39990
// Added more documentation and
// organized methods in alphabetical listing
// 
// 
// 
//    Rev 1.10   28 Nov 2000 16:41:48   dt14177
// cleanup
// 
//    Rev 1.9   Aug 23 2000 08:54:20   DT29758
// added method makeCopy()  for derived classes
// to use as a deep copy constructor
// 
//    Rev 1.8   May 02 2000 12:03:24   DT29758
// Added rollback functionality
//  inserted 3 methods
//     setCheckpointforRollback
//    rollListToCheckpoint
//     doesCheckpointExist
// 
//    Rev 1.7   Mar 02 2000 11:32:24   DT29758
// Added methods for counting number of
// objects with activity set to a type
// 
//    Rev 1.4   Dec 31 1999 06:27:52   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.2   Dec 02 1999 16:03:48   DT29758
// added ccdoc style comments and minor code
// clean up
// 
// 
//    Rev 1.1   Nov 11 1999 16:32:50   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:16:00   DT22388
//  
// 
//    Rev 1.3   Jan 28 1999 14:43:34   DT22388
// Added new functionality for using
// updateablelists with events.  An event
// can now have either a default CBO or
// an updateablelist but not both.  Added
// new methods:
//     shouldUpdateBeBuilt()
//     performIsValidForUpdateEdits()
//     getData()
//    refresh()
//    getKey()
// 
// 
// 
//    Rev 1.2   Jan 14 1999 12:30:58   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.1   Jul 30 1998 14:17:08   djoo
// Added methods removeAllObjectsAndActivity, 
// isObjectInList and isObjectOwned.
// 
#endif // UPDATABLELISTBASE_HPP
