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
 *    Copyright 1997, 1998, 1999, 2000 by DST Systems, Inc.
 */

//CP20021120/**
//CP20021120 *  @pkg DIAWDI
//CP20021120 */

#include <commonport.h>
#include <bfawdi\bfawddata.hpp>
#include <bfawdi\bfawdkey.hpp>
#include <bfawdi\bfawdlookupcriteria.hpp>
#include <bfawdi\bfawdsource.hpp>
#include <bfdata\bfdata.hpp>
#include <commontemplates.h>
#include <bfawdi\bfawdtemplates.hpp>

class BFAwdBaseInterface;

#undef BFAWDI_LINKAGE
#ifdef BFAWDI_DLL
   #define BFAWDI_LINKAGE CLASS_EXPORT
#else
   #define BFAWDI_LINKAGE CLASS_IMPORT
#endif


/**
 * Class for interaction with AWD
 *
 * This class provides an abstract interface for interacting with AWD.
 * The actual implementation for AWD interaction is located in a seperate
 * DLL which is loaded the first time an BFAwdInterface object is instatiated or
 * when one of the static methods is first called.
 */
class BFAWDI_LINKAGE BFAwdInterface
{
   // Public enums & typedefs
public:
   enum QueueType
   {
      ALL_QUEUES       = 'B',
      PERSONAL_QUEUES  = 'P',
      WORK_QUEUES      = 'Q'
   };

   // Constructors and Destructors
public:
   /**
    * Default constructor
    *
    * The first time an BFAwdInterface object is instantiated, an attempt
    * is made to load the DLL where the interface is implemented.  If the
    * interface DLL is not successfully loaded, the object will be in an
    * invalid state and no interaction with AWD will be permitted.
    */
   BFAwdInterface();

   /**
    * Default Destructor
    */
   virtual ~BFAwdInterface();

   // Public methods
public:

   /**
    * Call to determine if this object is successfully interfacing
    * with AWD.
    *
    * @return True if a interface with AWD has been established
    */
   bool isValid() const { return(m_bValid);}

   /**
    * Returns a string vector containing a list of business areas
    *
    * @return list of business areas
    *
    * @exception ConditionException
    */
   string_vector getBusinessAreaList();

   /**
    * Returns a string vector containing a list of work types based on
    * the business area passed in.
    *
    * @param busarea - business area
    *
    * @return list of work types
    *
    * @exception ConditionException
    */
   string_vector getWorkTypeList( const DString & busarea );

   /**
    * Returns a string vector containing a list of case work types based
    * on the  business area passed in.
    *
    * @param busarea - business area
    *
    * @return list of case work types
    *
    * @exception ConditionException
    */
   string_vector getCaseWorkTypeList( const DString & busarea );

   /**
    * Returns a string vector containing a list or transaction (work) work
    * types based on the business area passed in.
    *
    * @param busarea - business area
    *
    * @return list of transaction work types
    *
    * @exception ConditionException
    */
   string_vector getTransWorkTypeList( const DString & busarea );

   /**
    * Returns a string vector containing a list of source types
    *
    * @param busarea
    *
    * @return list of source types
    *
    * @exception ConditionException
    */
   string_vector getSourceTypeList( const DString & busarea );

   /**
    * Returns a string vector containing a list of status
    *
    * @return list of status
    *
    * @exception ConditionException
    */
   string_vector getStatusList();

   /**
    * Returns a list of status based on the current queue of a work object.
    * The default status will be the first one in the list.
    *
    * @param pKey - The key to the work object
    *
    * @return string_vector
    *
    * @exception ConditionException
    */
   string_vector getStatusList( const BFAwdKey *pKey );

   /**
    * Returns a list of status based on the current queue of a work object, BussArea and WorkType.
    * The list is filtered on the Queue, BussArea and WkType.
    *
    * @param pKey - The key to the work object
    *
	* @param strBussArea - The business area
	*
	* @param strWkType - The work type
	*
    * @return string_vector
    *
    * @exception ConditionException
    */
   string_vector getStatusList( const BFAwdKey *pKey, const DString &strBussArea, const DString &strWkType );


   /**
    * Returns a string vector containing a list of queues.
    * The parameter passed in selects what list of queues to return.
    *
    * @param type - Queue type.  Defaults to ALL_QUEUES.
    * @return list of queues
    *
    * @exception ConditionException
    */
   string_vector getQueueList( const QueueType type = ALL_QUEUES );

   /**
    * Returns the AWD data dictionary in the form of a map of Data objects
    *
    * @return reference to the data dictionary
    *
    * @exception ConditionException
    */
   BFDataObjMap & getAwdFieldList();

   /**
    * This method performs an AWD lookup.
    *
    * This method will invoke a single lookup results container based on
    * the criteria passed in.  If the lookup results container is already
    * up, an additional one will not be created for the new criteria.
    * The old one will first be closed.
    *
    * @param criteria - A vector of search criteria
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool lookupWork( const CriteriaVector &criteria );

   /**
    * This method performs an AWD lookup.
    *
    * This will return a vector of AwdLookupResult objects based on the
    * criteria passed in.  The results are generated by a lookup in the
    * AWD database.  If a zero is passed in for the 'max', the number of
    * result objects will be equal to or less than the maximum results for
    * a single reuest to the AWD database and the bool 'more' passed in
    * will be set to true if there are more results that meet the criteria
    * on the AWD server.  If a non-zero value is passed as 'max' then the
    * number of result objects will be equal to or less than 'max'.
    * If 'max' is greater then the number of results the AWD server will
    * return in a single request, then multiple requests will be made if
    * necessary.
    *
    * @see CriteriaVector.
    *
    * @param criteria - criteria
    * @param more - will indicate if there are more results to be retreived
    * @param max - the max number of results to return
    *
    * @return list of lookup results
    *
    * @exception ConditionException
    */
   ResultVector lookupWork( const CriteriaVector &criteria,
                            bool &more,
                            const unsigned long max = 0 );

   /**
    * This method is the same as lookupWork except it searches for
    * source objects instead of work objects
    *
    * @param criteria - A vector of search criteria
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool lookupSource( const CriteriaVector &criteria );

   /**
    * This method is the same as lookupWork except it searches for
    * source objects instead of work objects
    *
    * @param criteria - criteria
    * @param more - will indicate if there are more results to be retreived
    * @param max - the max number of results to return
    *
    * @return list of lookup results
    *
    * @exception ConditionException
    */
   ResultVector lookupSource( const CriteriaVector &criteria,
                              bool &more,
                              const unsigned long max = 0 );

   /**
    * Used to retrieve more results.
    *
    * If a call to lookupWork indicated there were more results, this method
    * will return the additional result object and indicate if there are
    * still more results to be retrieved.
    *
    * @param more - indicates if there are still more results to retrive
    *
    * @return list of lookup results
    *
    * @exception ConditionException
    */
   ResultVector lookupMore( bool &more );

   /**
    * Used to bring up a CSD
    *
    * This will invoke a CSD for the awd object indicated by the BFAwdData.
    * If the object already exists on the AWD server, the CSD will represent
    * it.
    *
    * @param awdData - AWD object to view in a CSD
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool loadCSD( BFAwdData &awdData );

      /**
       * Used to close a CSD
       *
       * This will close a CSD for the awd object indicated by the AwdKey, if
       * one was opened with the loadCSD() method.
       *
       * @param pKey - A key to the AWD object with a CSD to close.
       *
       * @return True if successful.
       *
       * @exception ConditionException
       */
      bool stopCSD( const BFAwdKey *pKey );

      /**
       * Used to show or hide the AWD container opened though the AwdInterface.
       *
       * @param bHide - True to show the container, false to hide it.
       *
       * @return True if successfull.
       */
      bool showAwdContainer( bool bHide );

      /**
       * Determines if the AWD object passed in is currently running the
       * designated service and returns the result.
       *
       * @param pKey - A key to the AWD object to examine.
       * @param serviceName - The service to look up.
       *
       * @return True if the serivce is running for the AWD object.
       */
      bool hasActiveService( const BFAwdKey *pKey,
                             const DString &serviceName );

      /**
       * Returns a list of child AWD objects <I>and</I> grandchildren to the
       * AWD object passed in as a vector of AwdKeys.  The calling method is
       * responsible for deleting each AwdKey in the list when they are no
       * longer needed.
       *
       * @param pKey - The parent AWD object.
       * @param awdKeyVector - An AwdKey vector to hold the children found for
       *                       the parent.
       *
       * @return True if successfull.
       */
      bool getAllChildren( const BFAwdKey* pKey,
                           BFAwdKeyVector &awdKeyVector );

      /**
       * Returns a list of child AWD objects <I>without</I> grandchildren to
       * the AWD object passed in as a vector of AwdKeys.  The calling method
       * is responsible for deleting each AwdKey in the list when they are no
       * longer needed.
       *
       * @param pKey - The parent AWD object.
       * @param awdKeyVector - An AwdKey vector to hold the children found for
       *                       the parent.
       *
       * @return True if successfull.
       */
      bool getImmediateChildren( const BFAwdKey* pKey,
                                 BFAwdKeyVector &awdKeyVector );

      /**
       * Shows or hides the service window of an AWD objcet.  If the service
       * is active for the ADW object, then this method will show or hide the
       * service window.
       *
       * @param pKey - The AWD object running a service.
       * @param serviceName - The name of the service to show or hide.
       * @param bShow  - true to show the window, false to hide it.
       *
       * @return True if successful.
       */
      bool showAwdServiceWindow( const BFAwdKey *pKey,
                                 const DString &serviceName,
                                 bool bShow );
   /**
    * Opens an AWD container
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool openAwdContainer();

      /**
       * Locates the AWD container containing the AWD object passed in.  This
       * method will return false if a container is already open.  If no
       * container is already open and a container is found, the found
       * container will be used as the interface container and will be
       * considered open.
       *
       * @param pKey - The AWD object used to find a container.
       *
       * @return True if successful, otherwise false.
       */
      virtual bool locateAwdContainer( const BFAwdKey *pKey );

      /**
       * Returns true if the key passed in is valid and it references an AWD
       * object that is locked.
       *
       * @param pKey - The key of the AWD object to check.
       *
       * @return True if the object is locked.
       */
      bool isLocked( const BFAwdKey *pKey );
   /**
    * Inserts an AWD object into the container if it has already been opened.
    *
    * @param pKey - The key to the AWD object to insert
    * @param lock ???
    *
    * @return bool - true if successful
    *
    * @exception ConditionException
    */
   bool insertItemInContainer( const BFAwdKey *pKey, bool lock = false );

      /**
       * Inserts the AWD object idetified by pKey into the container as a child
       * of the AWD object idetified by pParent, if the container has already
       * been opened.
       *
       * @param pKey - The key to the AWD object to insert.
       * @param pParent - The key to the parent AWD object.
       *
       * @return True if successful.
       *
       * @exception ConditionException
       */
      bool insertItemInContainer( const BFAwdKey *pKey,
                                  const BFAwdKey *pParent,
                                  bool lock );

   /**
    * Returns true if the AWD object represted by the key appears in the
    * container invoked by openAwdContainer()
    *
    * @param pKey - The key to the AWD object to look for
    *
    * @return true if appears in container
    *
    *
    * @exception ConditionException
    */
   bool isItemInContainer( const BFAwdKey *pKey );
   bool selectItemInContainer( const BFAwdKey *pKey );

   /**
    * Closes an AWD contaienr
    *
    * @return true if succesfull
    *
    * @exception ConditionException
    */
   bool closeAwdContainer();

   /**
    * Removes all object in the container.
    *
    * @return true if successful.
    *
    * @exception ConditionException
    */
   bool clearAwdContainer();

   /**
    * Tells the container to expand the awd object showing all its
    * descendents.
    *
    * @param pKey - The key to the AWD object to expand
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool expandContainerItemDown( const BFAwdKey *pKey );

   /**
    * Creates an AWD Transaction (work) object on the AWD server based on
    * the BFAwdData object passed in.
    *
    * @param awdData - Transaction (work) to be created
    * @param lock - Whether or not to lock the transaction when created
    *
    * @return true if sucessfull
    *
    * @exception ConditionException
    */
   bool createAwdTransaction( BFAwdData &awdData, bool lock );

   /**
    * Creates an AWD case object on the AWD server based on the BFAwdData
    * object passed in.
    *
    * @param awdData - Case to be created
    * @param lock - Whether or not to lock the case when it is created
    *
    * @return true if sucessfull
    *
    * @exception ConditionException
    */
   bool createAwdCase( BFAwdData &awdData, bool lock );

   /**
    * This method creates an AWD Source object.
    *
    * The AWD Source object is created using the values passed in with the
    * BFAwdData object and the file passed in as the image.  If ppSource is
    * not NULL, it will point to an BFAwdSource object if the AWD Source was
    * successfully created.  The caller of this method will then be
    * responsible for deleting the BFAwdSource object.
    *
    * @param awdData -  Values to pass to AWD
    * @param format - Object (image) format
    * @param strFile - Image to be used for the source
    * @param ppSource - Pointer to and BFAwdSource pointer
    * @param lock - Whether to create with lock or not
    *
    * @return true if successful.
    * @exception ConditionException
    *
    * @exception ConditionException
    */
   bool createAwdSource( const BFAwdData &awdData,
                         const BFAwdSource::ObjectFormat format,
                         const DString &strFile,
                         BFAwdSource **ppSource,
                         bool lock );

   /**
    * Established a parent / child relationship between two AWD objects.
    *
    * @param pParent - The key to the AWD object to be the parent
    * @param pChild - The key to the AWD object to be the child.
    *
    * @return true if successful.
    *
    * @exception ConditionException
    */
   bool createRelationship( const BFAwdKey *pParent,
                            const BFAwdKey *pChild );

   /**
    * Locks or unlocks an AWD Object on the AWD server.
    *
    * @param pKey - The key to the AWD object to lock or unlock
    * @param lock - Set to true to lock / false to unlock
    *
    * @return bool - true if succesfull
    *
    * @exception ConditionException
    */
   bool lockAwdObject( const BFAwdKey *pKey, bool lock );

   /**
    * Determines if an AWD object has a parent case
    *
    * Returns true if the AWD Object represented by the key has a parent
    * that is a case.  If a parent is a case, a "new" pointer to the
    * parent's key will be returned.
    *
    * <b>Note:</b> The calling method is responsible for deleting ppParent
    *
    * @param pKey - The key to the AWD object to check
    * @param ppParent - The key to the parent
    *
    * @return bool - true if parent is a case
    *
    * @exception ConditionException
    */
   bool hasCaseForParent( const BFAwdKey *pKey, BFAwdKey **ppParent );

   /**
    * Determines if the AWD object has a child source.
    *
    * Returns true if the AWD Object represented by the key has a child that
    * is a source.  If a child is a source, a "new" pointer to the child's
    * key will be returned.
    *
    * <b>Note:</b> The calling method is responsible for deleting ppChild
    *
    * @param pKey - The key to the AWD object to check
    * @param ppChild - The key to the child
    *
    * @return bool - True if a child is a source
    *
    * @exception ConditionException
    */
   bool hasSourceForChild( const BFAwdKey *pKey, BFAwdKey **ppChild );
   bool hasChildren( const BFAwdKey *pKey );


   /**
    * Adds a comment to an AWD object already existing on the AWD server
    *
    * @param pKey - The key to the AWD object to receive the comment
    * @param &comment - The comment to add
    *
    * @return bool - true if sucessfull
    *
    * @exception ConditionException
    */
   bool addComment( const BFAwdKey *pKey, const DString &comment );

   /**
    * Listens for the creation of AWD objects.
    *
    * Starts an AWD listener and 'listens' for when AWD objects are created.
    * All objects that are created outside this interface are accumalated.
    * To get the list of accumalated objects call the method
    * endListenCreateObjects().
    *
    * <b>Note:</b> If the listener has already been started, this method
    * will take no action and return false.
    *
    * @return bool - true of the listener was started.
    *
    * @exception ConditionException
    */
   bool beginListenCreateObjects();

   /**
    * Stops the listener and returns a vector of AWD keys representing AWD
    * objects created outside of this interface.
    *
    * <b>Note:</b> This method can only be called on the BFAwdInterface
    * object that was used to call beginListenCreateObjects()
    *
    * @return list of AWD keys
    *
    * @exception ConditionException
    */
   BFAwdKeyVector endListenCreateObjects();

   /**
    * Used to create an BFAwdKey object
    *
    * Creates a new BFAwdKey object using the three elements that define
    * the primary index (key) for an AWD object on the AWD server.
    * Regardless if the AWD object exists, an BFAwdKey object will be "new"ed
    * up.  Call the method BFAwdKey::isKey() to determine whether this method
    * was successful.
    *
    * <b>Note:</b> The caller of this function is responsible for deleting the
    * BFAwdKey object returned.
    *
    * @param createDateTime - The date / time the AWD object was created.
    * @param recordCode - The record code: 'C' for case, 'T' for transaction,
    *                     'O' for source.
    * @param createNode - The node used when the AWD object was created.
    *
    * @return a new BFAwdKey object.
    *
    * @exception ConditionException
    */
   BFAwdKey * newAwdKey( const DString &createDateTime,
                         const DString &recordCode,
                         const DString &createNode );

   /**
    * Used to retrieve LOB data.
    *
    * Retreives the LOB data for the AWD object represented by the key
    * passed in, and populates the BFAwdData object.  If successful, this
    * method will make a copy of the BFAwdKey passed in that will used to set
    * into the BFAwdData object.
    *
    * @param pKey - The key to the AWD object to be retrieved
    * @param awdData - The BFAwdData object to be populated.
    *
    * @return bool - true if successful.
    *
    * @exception ConditionException
    */
   bool retrieveData( const BFAwdKey *pKey, BFAwdData &awdData );

      /**
       * Used to retrieve LOB data.
       *
       * Retreives the LOB data for the AWD object represented by the key
       * passed in, and populates the AwdData object.  If successful, this
       * method will make a copy of the AwdKey passed in that will used to set
       * into the AwdData object.
       *
       * @param pKey - The key to the AWD object to be retrieved.
       * @param awdData - The AwdData object to be populated.
       *
       * @return True if successful.
       *
       * @exception ConditionException
       */
      bool retrieveDataLite( const BFAwdKey *pKey, BFAwdData &awdData );

   /**
    * Used to retrieve an image and LOB data for an AWD source object.
    *
    * Retrieves an AWD Source object including all its LOB data for the AWD
    * object represented by thekey passed in.  An BFAwdSource object will be
    * dynamically instantiated and returned in ppSource.  The caller of this
    * method is responsible for deleting the BFAwdSource object when it is no
    * longer needed.
    *
    * @param pKey - The key to the AWD source object to be retrieved.
    * @param ppSource - The BFAwdSource object that was retrieved.
    *
    * @return bool - true if successful.
    *
    * @exception ConditionException
    */
   bool retrieveSource( const BFAwdKey *pKey, BFAwdSource **ppSource );

   /**
    * Starts an AWD service for the AWD object represented by the key.
    *
    * @param pKey - The key for the AWD object
    * @param strServiceName - Service to start.
    *
    * @return bool - true if sucessfull
    *
    * @exception ConditionException
    */
   bool startService( const BFAwdKey *pKey,
                      const DString &strServiceName );

   /**
    * Stops an AWD service for the AWD object represented by the key.
    *
    * @param pKey - The key for the AWD object
    * @param strServiceName - Service to stop.
    *
    * @return true if sucessfull
    *
    * @exception ConditionException
    */
   bool stopService( const BFAwdKey *pKey,
                     const DString &strServiceName );

   /**
    * Used to update an AWD object.
    *
    * Updates an AWD object on the AWD server with the values stored in the
    * BFAwdData object.  The BFAwdKey member of the BFAwdData object must be valid.
    *
    * @param awdData - represents the awd object and the values to update
    *
    * @return true if successful.
    *
    * @exception ConditionException
    */
   bool updateAwdObject( BFAwdData &awdData );


   /**
    * This method will retrieve the next AWD work to be processed.
    *
    * @param awdData - an empty data object to be populated with the
    *                  AWD work objcet retrieved.
    *
    * @return true if successful
    */
   bool getAwdWork( BFAwdData &awdData );

   /**
    * Makes a list of AWD work (case and transaction) objects currently in
    * the AWD container, dynamically allocates an BFAwdKey object for each
    * work object, and adds them to vector passed in.  Source objects are
    * not included in the list.  The vector must be <i>empty</i> when passed
    * in.  <b>The caller of this method is responsible for iterating through
    * the vector and deleting each BFAwdKey object added by this method.</b>
    *
    * @param awdKeyVector - vector to hold the collection of BFAwdKey objects.
    *
    * @return true if successful.
    */
   bool getAwdWorkObjects( BFAwdKeyVector &awdKeyVector );

      /**
       * Will double click the item in the container represented by the AwdKey
       * passed in.  This will envoke any auto-flags for the work.
       *
       * @param pKey - The AWD object to be "double clicked."
       *
       * @return True if the item was successfully double clicked.
       */
      bool doubleClickContainerItem( const BFAwdKey *pKey );

      /**
       * Returns an AwdKey representing the item in the container that is
       * currently selected.  If no item is selected, a NULL is returned.
       * <B>NOTE:</B> If an AwdKey is returned, the party that called this
       * method is responsible for <I>deleting</I> the object.
       *
       * @return A pointer to an AwdKey representing the item selected in the
       *         AWD container.
       */
      BFAwdKey * getCurrentContainerSelection();

   /**
    * Gets the current Queue for an AWD object.
    *
    * @param pKey - The key to the AWD object.
    *
    * @return the current queue
    *
    * @exception ConditionException
    */
   DString getQueue( const BFAwdKey *pKey );

   /**
    * Sets the Queue for an AWD object represented by the key passed in.
    *
    * @param pKey - The key to the AWD object to affect.
    * @param queue - The new queue
    *
    * @return bool - true if sucessfull
    *
    * @exception ConditionException
    */
   bool setQueue( const BFAwdKey *pKey, const DString &queue );

   /**
    * Returns the ID of the operator signed on to AWD.
    *
    * @return the operator ID
    *
    * @exception ConditionException
    */
   DString getOperatorID();

      /**
       * Returns the three digit code that indicating the language preference
       * of the user.
       *
       * @return The operator's three digit country code.
       */
      unsigned long getCountry();

      /**
       * Returns the eight-character identifier that uniquely identifies the
       * AWD ViewStation to the AWD host.
       *
       * @return An eight-character identifier that uniquely identifies the
       *         AWD ViewStation to the AWD host.
       */
      DString getWorkstationID();

   /**
    * Gets the current date and time from the AWD server.
    * The format is "CCYY-MM-DD-HH.MM.SS.DDDDDD"
    *
    * @return time/date stamp
    *
    * @exception ConditionException
    */
   DString getServerDateTime();

      /**
       * Returns a list of valid suspend codes for suspending an AWD
       * work object.
       *
       * @return The list of valid suspend codes.
       */
      string_vector getSuspendCodeList();

   /**
    * The method is used to suspend an AWD work object.  The
    * date/time passed in specifies when the suspend will end.
    *
    * @param pKey - The key to the work to be suspended.
    * @param activateDateTime - The date and time the suspend should end.
    *
    * @return true if successful
    *
    * @exception ConditionException
    */
   bool suspendWorkObject( const BFAwdKey *pKey,
                           const DString &activateDateTime,
                              const DString &suspendCode = I_("") );

   /**
    * Call this method to unsuspend an AWD work object.
    *
    * @param pKey - The AWD key of the work to be unsuspended.
    *
    * @return true if successful.
    */
   bool unSuspendWorkObject( const BFAwdKey *pKey );

   /**
    * Returns true if the user is logged on to AWD
    *
    * @return true if logged on
    *
    * @exception ConditionException
    */
   static bool isLoggedOn();

   /**
    * Logs the operator onto AWD
    *
    * @param operatorID - ID of the operator
    * @param password - The operator's password
    * @param newPassword - A new password if the operator is changing it.
    *
    * @return logon return code.
    *
    * @exception ConditionException
    */
   static long logon( const DString &operatorID,
                      const DString &password,
                      const DString &newPassword );

   /**
    * Logs the user off from AWD
    *
    * @return long - Logoff return code.
    *
    * @exception ConditionException
    */
   static long logoff();

   // Private members
private:
   BFAwdBaseInterface *m_pBase;
   bool m_bValid;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfawdi/bfawdinterface.hpp-arc  $
//
//   Rev 1.4   01 Feb 2008 08:54:26   kovacsro
//IN#1118094&1114586 - added an overloaded getStatusList method to filter the results on the queue, busArea and wkType
//
//   Rev 1.3   Apr 20 2004 10:47:22   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
//
//   Rev 1.2   Nov 27 2002 14:51:30   PURDYECH
//Documentation Cleanup
//
//   Rev 1.1   Oct 09 2002 17:39:54   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:18   SMITHDAV
//Initial revision.
// 
//    Rev 1.14   Feb 07 2001 09:14:48   dt21858
// Sync up with 1.7
//
//    Rev 1.13   Apr 24 2000 10:52:22   DMUM
//
//
//    Rev 1.12   Apr 18 2000 12:59:08   DMUM
// Fixed HTML in comment block
//
//    Rev 1.11   Jan 06 2000 14:05:58   DMUM
// Changed comments to Java Doc style
//
//    Rev 1.10   Aug 27 1999 08:31:56   DMUM
// Constructor no longer throws exceptions
//
//    Rev 1.9   Aug 26 1999 12:58:50   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.8   May 18 1999 08:50:10   DMUM
//
//
//    Rev 1.7   Apr 09 1999 13:26:16   DMUM
// Sync up with 1.6.x
//
//    Rev 1.5.1.0   Mar 31 1999 13:14:50   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.6   Feb 19 1999 07:47:30   DMUM
// Added lookupSource() and fixed AwdTemplates
//
//    Rev 1.0.1.5   Feb 09 1999 09:55:08   DMUM
// Updated documentation
//
//    Rev 1.0.1.4   Feb 08 1999 15:16:12   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0.1.3   Jan 20 1999 16:39:12   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.2   Dec 11 1998 10:22:48   DMUM
// Added loadCSD()
//
//    Rev 1.0.1.1   Oct 01 1998 11:50:08   DMUM
//
//
//    Rev 1.2   Oct 01 1998 11:34:56   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.1   Sep 11 1998 11:57:56   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.0   29 Jul 1998 20:36:08   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.14   Mar 16 1998 15:46:22   dmum
// Added isItemInContainer method
//
//    Rev 1.13   Jan 19 1998 13:47:38   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.12   Dec 30 1997 11:26:22   dmum
// Added new methods
//
//    Rev 1.11   Dec 16 1997 11:30:10   dmum
// Added methods
//
//    Rev 1.10   10 Nov 1997 15:01:28   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.9   20 Sep 1997 11:54:46   dmum
// removed awdType (it is now in BFInterfaceManager)
//
//    Rev 1.8   02 Sep 1997 15:38:22   dmum
// Now supports the data dictionary and returns it in the method getAwdFieldList()
//
//    Rev 1.7   01 Jul 1997 09:47:54   dmum
// Added method to return a valid list of queues
//
//    Rev 1.6   27 Jun 1997 14:37:58   dmum
// Renamed createAwdWork to createAwdTransaction
//
//    Rev 1.5   13 Jun 1997 17:41:20   dmum
// Added condition and documented methods
//
//    Rev 1.4   May 27 1997 10:49:30   dmum
// Enhanced functionality
//
//    Rev 1.3   May 08 1997 16:10:40   dmum
// Added methods to get and set the queue
//
//    Rev 1.2   May 05 1997 11:39:26   dmum
// Added method to get operator id
//
//    Rev 1.1   Apr 25 1997 11:21:24   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:20:02   dmum
//
//
//
