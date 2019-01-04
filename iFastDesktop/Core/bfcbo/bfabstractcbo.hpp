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
// ^FILE   : BFAbstractCBO.hpp
// ^AUTHOR : Glen McNabb (he named the class)
// ^DATE   : May 1999
//
// ^CLASS    : BFAbstractCBO
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#pragma warning( disable : 4503 4786 )  

#include <SrcPrag.h>
#include <assert.h>
#include <bfcbo\BFObservable.hpp>
#include <commonport.h>
#include <Condition.hpp>
#include <Frame.hpp>
#include <DString.hpp>
#include <bfcbo\BFProperties.hpp>
#include <bfcbo\BFObjectKey.hpp>
#include <map>
#include <vector>
#include <bfutil\BFEvent.hpp>
#include <bfutil\BFCritSec.hpp>
#include <bfcbo\bfdatagroupid.hpp>

// forward declarations
class BFSession;
class BFObserver;
class BFObservable;
class BFRequest;
class BFRequestor;
class BFHost;
class BFFieldId;
class BFConstObjIter;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

#include <iostream>

/**
 * This is the base class for all CBOs ( business objects )
 * 
 * It is doing basic functionality like basic view calls, datagroup management
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/07/1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFAbstractCBO
{
public:
   friend class BFObjIter;
   friend class BFConstObjIter;
   friend class BFCBO;
/**
 * Represents the different validation modes posible for a CBO.
 *
 * <pre>
 *@@ These are the valid validation modes:
 *@@   IMMEDIATE             - Immediate = immediately validated
 *@@   POSTPONED             - Postponed = validated only on validateAll(...)
 * </pre>
 */
   enum VALIDATION_MODE
   {
      IMMEDIATE,    
      POSTPONED 
   };

   BFAbstractCBO( BFAbstractCBO *parent, VALIDATION_MODE validationMode=IMMEDIATE )
   : parent_( parent )
   , validationMode_( validationMode )
   , _hasNonBFHOSTsetObjects( false )
   {
   }
   BFAbstractCBO( VALIDATION_MODE validationMode=IMMEDIATE )
   : parent_( NULL )
   , validationMode_( validationMode )
   , _hasNonBFHOSTsetObjects( false )
   {
   }

   enum
   {
      NONE = 0x0000
   };

   enum FIELD_STATE_FLAGS
   {
      READ_ONLY            = 0x0001,
      F_REQUIRED           = 0x0002,
      UPDATED              = 0x0004,
      VALID                = 0x0008,
      INIT_TO_DEFAULT      = 0x0020,
      CALCULATED_FIELD     = 0x0800,
      IMMEDIATE_VALIDATION = 0x1000
   };

   enum OBJECT_STATE_FLAGS
   {
      O_REQUIRED           = 0x0002,
      NO_BASE_DELETE       = 0x0040,
      NOT_ON_HOST          = 0x0080,
      LIST_INVALID         = 0x0100,
      LIST_OBJECT          = 0x0200,
      NON_DUMMY            = 0x0400,
   };

   /**
    * Used to set the non Dummy flag
   */
   virtual void setNonDummyFlag( ) = 0; // { _lBFStatus |= NON_DUMMY;};
   /**
    * Used to clear the non Dummy flag
   */
   virtual bool getNonDummyFlag( ) const = 0; // { return(_lBFStatus & NON_DUMMY ) != 0;}
   /**
    * returns the updated state of a CBO based only on his fields
   */
   virtual bool hasUpdatedFields( const BFDataGroupId& idDataGroup = BF::HOST ) const = 0;

   /**
    * returns the maximum severity set on the last validation of this CBO, from the point of view of dataGroup lDataGroupId
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   virtual SEVERITY getMaxValidationSeverityForObject( const BFDataGroupId& idDataGroup = BF::HOST ) const = 0;
   /**
    * returns the maximum severity set on the last validation of the contained CBOs of this one, from the point of view of dataGroup lDataGroupId
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   virtual SEVERITY getMaxValidationSeverityForChildren( const BFDataGroupId& idDataGroup = BF::HOST ) const = 0;
   /**
    * returns the maximum severity set on the last validation of this CBO and contained ones, from the point of view of dataGroup lDataGroupId
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   virtual SEVERITY getMaxValidationSeverityForObjectAndChildren( const BFDataGroupId& idDataGroup = BF::HOST ) const = 0;

   /**
    * refreshes a CBO 
    * @param bNewObject       - it tells to the object if it is a new element in the calling container
   */
   virtual SEVERITY refresh( bool bNewObject = false ) = 0;

   /**
    * returns in lCndVector all object level errors from inside this CBO
    * @param idDataGroup       - the data group identifier for which we want to get the errors
    * @param lCndVector         - CONDITIONVECTOR reference where we want the errors to be stored
    * @param lValidateGroup     - validation group mask 
    * @param inclSubObj do we want to get errors from contained objects too
   */
   virtual SEVERITY getNonFieldErrors( const BFDataGroupId& idDataGroup, 
                                       CONDITIONVECTOR & lCndVector, 
                                       long lValidateGroup = 0, 
                                       bool inclSubObj = true ) = 0;
   /**
    * clears out the value filed in a field 
    * @param idField           - the field identifier for the field that we want cleared out
    * @param idDataGroup     - the data group identifier for which we want to clear out the field 
   */
   virtual SEVERITY clearField( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;
   /**
    * returns in lFieldIdVector all fields that are making this cross edit
    * @param idField          - the field identifier for the cross edit for we want to obtain fields that are part of
    * @param lFieldIdVector   - the vector where we should put the founded fields
   */
   virtual void getCrossEditFields( const BFFieldId& idField,  std::vector<BFFieldId> & lFieldIdVector ) = 0;

   /**
    * sets the VALID flag for all fields for lDataGroupId dataGroup
    * @param idDataGroup     - the data group identifier for which we want to set the flags
   */ 
   virtual void setAllFieldsValid( const BFDataGroupId& idDataGroup ) = 0;

   /**
    * clear out the UPDATED flag for all fields for lDataGroupId dataGroup. It can work recusively into contained objects
    * @param idDataGroup     - the data group identifier for which we want to clear the flag
    * @param inclSubObj       - do we want to do the operation recursivelly
   */ 
   virtual void clearUpdatedFlags( const BFDataGroupId& idDataGroup, bool inclSubObj = false ) = 0;

   /**
    * get the Observable object for this idField, dataGroupId combination. If it doesn't find one it will create it 
    * @param idField          - the field identifier for which we want to retrieve the BFObservable object
    * @param idDataGroup     - the data group identifier for which we want to retrieve the BFObservable object
    * @param eEventCateg      - are we interested in field notifications ( FIELD_NOTIFICATIONS ) or not
    * @param eEventId ???
   */
   virtual BFObservable * getObservable( const BFFieldId& idField, 
                                         const BFDataGroupId& idDataGroup, 
                                         E_EVENT_GROUP eEventCateg, 
                                         E_EVENT eEventId ) const = 0;

   /**
    * registers an observer object for this idField, dataGroupId combination. 
    * @param idField          - the field identifier for which we want to set the BFObserver object
    * @param idDataGroup     - the data group identifier for which we want to set the BFObserver object
    * @param pObserver        - pointer to the BFObserver object that we want to be set
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventId the event identifier
   */ 
   virtual bool registerObserver( const BFFieldId& idField, 
                                  const BFDataGroupId& idDataGroup, 
                                  BFObserver * pObserver, 
                                  E_EVENT_GROUP eEventCateg, 
                                  E_EVENT eEventId ) const = 0;
   /**
    * deregisters the pObserver observer object for this idField, dataGroupId combination.
    * 
    * @param idField   the field identifier for which we want to remove the BFObserver object
    * @param idDataGroup
    *                  the data group identifier for which we want to remove the BFObserver object
    * @param pObserver pointer to the BFObserver object that we want to be removed
    * @param eEventCateg
    *                  the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS )
    * @param eEventId  the event identifier
    * 
    * @return 
    */
   virtual bool deleteObserver( const BFFieldId& idField, const BFDataGroupId& idDataGroup, BFObserver * pObserver, E_EVENT_GROUP eEventCateg, E_EVENT eEventId ) = 0; //{ return false;};

   /**
    * deregisters all observers registered for this idField, dataGroupId combination.
    * 
    * @param idField  - the field identifier for which we want to remove the BFObserver objects
    * @param idDataGroup
    *                 - the data group identifier for which we want to remove the BFObserver objects
    * @param eEventCateg
    *                 - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS )
    * @param eEventId - the event identifier
    */
   virtual void deleteObservers( const BFFieldId& idField, 
                                 const BFDataGroupId& idDataGroup, 
                                 E_EVENT_GROUP eEventCateg, 
                                 E_EVENT eEventId )= 0;
   /**
    * not used
   */ 
   virtual void deleteAllObservers( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0; 
   /**
    * notifies all observers registered for this idField, dataGroupId combination. 
    * @param idField         - the field identifier for which we want to notify the BFObserver object
    * @param idDataGroup     - the data group identifier for which we want to notify the BFObserver object
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventId the event identifier
    * @param hint             - the hint string that we want to pass in 
   */ 
   virtual void notifyObservers( const BFFieldId& idField, const BFDataGroupId& idDataGroup, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString & hint ) = 0;

   /**
    * returns the object that owns this one
   */ 
   const BFAbstractCBO *getParent() const { return(parent_);}
   BFAbstractCBO *getParent() { return(parent_);}

   /**
    * returns the ultimate parent object of this one
   */ 
   virtual const BFAbstractCBO * getTopLevelAncestor() const = 0;
   virtual BFAbstractCBO * getTopLevelAncestor() = 0;

   virtual bool isSession() const = 0;
   /**
    * returns this objects session
   */ 
   virtual const BFSession &getSession() const = 0; 
   virtual BFSession &getSession() = 0; 

   /**
    * validates and commits the object from this dataGroup perspective
    * @param idDataGroup - which data group that we want to validate and commit
   */ 
   virtual SEVERITY commitAndValidateDataGroup( const BFDataGroupId& idDataGroup ) = 0;
   /**
    * deletes the dummy items for added whith dataGroup
    * @param idDataGroup - the identifier of the data group whose dummy items we want to remove
    * @param inclSubObj     - do we want to do the operation recursively into the contained objects
   */ 
   virtual SEVERITY deleteNonUpdatedAddedElements( const BFDataGroupId& idDataGroup, bool inclSubObj = true ) = 0; 
   /**
    * returns the initial string key for this object. 
   */ 
   virtual const DString * getInitialStrKey() { return(NULL);}

   /**
    * returns true if the object contains other objects than dummy ones from the dataGroup's perspective
    * @param idDataGroup - the identifier of the data group that we want to know if it has non dummy items
   */ 
   virtual bool hasNonDummyEntries( const BFDataGroupId& idDataGroup ) const = 0;

   /**
    * returns true if this object has an entry in the field map for this idField
    * @param idField - the field id which we are looking for into the _fieldMap
   */
   virtual bool existsFieldInfo( const BFFieldId& idField ) = 0;
   /**
    * returns the parent dataGroup of the group lDataGroupId 
    * @param idDataGroup - the identifier of the data group for which we are looking for the parent
   */
   virtual const BFDataGroupId& getParentDataGroup( const BFDataGroupId& idDataGroup ) = 0; 

   /**
    * returns the default stringKey for new items.It is made by '999' plus an integer sequential number padded left with '0' to 7 positions
    * @param strKey - DString reference where we want to store the key
   */
   virtual void getStrKeyForNewItem( DString & strKey ) = 0; // { strKey = I_( "999" ) + DString::asString( _iNextKey++ ).padLeft( 7, '0' ); }

   /**
    * returns true if the lParentDataGroup is an ancestor for lDataGroupId
    * @param lParentDataGroup - the identifier of the supposedly parent data group 
    * @param idDataGroup     - the identifier of the supposedly child data group 
   */
   virtual bool isParentDataGroup( const BFDataGroupId& idParentDataGroup, const BFDataGroupId& idDataGroup ) const = 0;
   /**
    * returns true if the lContainerDataGroup is an ancestor for lDataGroupId
    * @param lContainerDataGroup - the identifier of the supposedly container data group 
    * @param idDataGroup        - the identifier of the supposedly contained data group 
   */
   virtual bool isContainedDataGroup( const BFDataGroupId& idContainerDataGroup, const BFDataGroupId& idDataGroup ) const = 0;


   /**
    * Destructor
   */
   virtual ~BFAbstractCBO() {};

   /**
    * returns true if the flag lFlag is turned on
   * @param lFlag    - long value where we are looking for the flags
   * @param nValues  - mask saying which flags are we carring for
   */

   /**
    * gets the field value from ldataGroupId's perspective
    * @param idField        - the field identifier to be get
    * @param strValue       - the DString reference where we want to store the value
    * @param idDataGroup   - the data group identifier with which we want to do the get
    * @param formattedReturn  - do we want to format the returned value
   */
   virtual void getField( const BFFieldId& idField, 
                          DString & strValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const = 0;

   /**
    * gets the field's initial value 
    * @param idField       - the identifier of the field to be get
    * @param strValue       - the where to the string we want to the value to be stored 
    * @param formattedReturn  - do we want to format the returned value
   */
   virtual bool getFieldBeforeImage( const BFFieldId& idField, 
                                     DString & strValue, 
                                     bool formattedReturn = false ) const = 0;

   /**
    * returns true if an object is new list element
   */
   virtual bool isNew( ) const = 0; //{ return(_lBFStatus & NOT_ON_HOST) != 0;};

   /**
    * does the initialisation with default values of fields inside a CBO
    * @param idDataGroup - the identifier of the data group for which we want to do the initialisation
   */
   virtual void initWithDefaultValues( const BFDataGroupId& idDataGroup ) = 0;

   virtual void doSetObject( const BFObjectKey & objKey, BFAbstractCBO * pObject){};
   /**
    * sets an object as a new list element
   */
   virtual void setObjectNew( ) = 0; // {_lBFStatus |= NOT_ON_HOST;}

   /**
    * returns true if an object is list type CBO
   */
   virtual bool isList( ) const = 0; //{ return(_lBFStatus & LIST_OBJECT) != 0;};

   /**
    * sets the object as a list
   */
   virtual void setObjectAsList( ) = 0; //{ _lBFStatus |= LIST_OBJECT;};

   /**
    * sets the list as invalid
   */
   virtual void setListInvalid( ) = 0; //{ _lBFStatus |= LIST_INVALID;};

   /**
    * retrieves a contained CBO based on the key
    * @param strKey        - the string key with which we want to retrieve the object
    * @param idDataGroup  - the data group identifier with which we want to retrieve the object
    * @param type          - the type with which we want to retrieve the object
    * @param activity      - the activity with which we want to retrieve the object
   */
   virtual BFAbstractCBO* getObject( const DString & strKey, 
                                     const BFDataGroupId& idDataGroup,
                                     BF_OBJ_TYPE type = OBJ_TYPE_NONE, 
                                     BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE) const = 0;
   /**
    * retrieves a contained CBO based on the key, if it doesn't find a match it will create one.
    * @param strKey        - the string key with which we want to retrieve the object
    * @param idDataGroup  - the data group identifier with which we want to retrieve the object
    * @param type          - the type with which we want to retrieve the object
    * @param activity      - the activity with which we want to retrieve the object
   */
   virtual BFAbstractCBO* getObject( DString & strKey, 
                                     const BFDataGroupId& idDataGroup,
                                     BF_OBJ_TYPE type = OBJ_TYPE_NONE, 
                                     BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE) const = 0;

//CP20030219   /**
//CP20030219    * returns the update level of this CBO
//CP20030219   */
//CP20030219   //TODO What is updateLevel?
//CP20030219   virtual long getUpdateLevel() const = 0;
//CP20030219
//CP20030219   /**
//CP20030219    * returns the update level of this CBO seen from the perspective of lDataGroupId dataGroup
//CP20030219    * @param idDataGroup  - the data group identifier for which we want to retrieve the update level 
//CP20030219   */
//CP20030219   virtual long getUpdateLevel( const BFDataGroupId& idDataGroup ) = 0;
//CP20030219   /**
//CP20030219    * sets the update level of this CBO seen from the perspective of lDataGroupId dataGroup
//CP20030219    * @param idDataGroup  - the data group identifier for which we want to set the update level 
//CP20030219    * @param lUpdateLevel  - the new update level that we want to set in 
//CP20030219   */
//CP20030219   virtual void setUpdateLevel( const BFDataGroupId& idDataGroup, long lUpdateLevel ) = 0;
   /**
    * sets the validation mode of this CBO
    * @param lValidMode  - the new validation mode that we want to use
   */
   void setObjectValidationMode( VALIDATION_MODE lValidMode ) { validationMode_ = lValidMode;};
   VALIDATION_MODE getObjectValidationMode() const { return(validationMode_);}


   /**
   * void function which blocks until the data requested has been received.  Used in conjuntion with AsyncReceiveData for special cases where
   * direct Data object operations are performed.
   * 
   */

   virtual bool dataReady () = 0;

   /**
    * Returns the moreRecordsAvailable property set by ReceiveData on the last call. 
    * The property is true prior to the first call.
    *
    * @return false if there are no more reecords to be recieved be ReceiveData.
   */
   virtual bool doMoreRecordsExist() = 0; // { return _moreRecordsAvailable; }

   /**
    * sets the field value for the lDataGroupId dataGroup, the input field value can be formatd or not, and it 
    * can or not notify the registered observers
    * @param idField       - the identifier of the field to be set
    * @param strValue      - the value to be set in
    * @param idDataGroup  - the identifier of the data group which will be used
    * @param lFormatted    - strValue is formated or not
    * @param lSideEffect   - do we want to have the registered observers notified about the change
    * @param bCheckCurrentValue   - do we want to call getField in order to compare existing value with the new one
   */
   virtual SEVERITY setField( const BFFieldId& idField,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true) = 0;

   /**
    * does the validation for the field idField and dataGroup  lDataGroupId
    * @param idField      - the identifier of the field to be validated
    * @param strValue      - the value to be validated
    * @param idDataGroup  - the identifier of the data group in which the validation should be made
   */
   virtual SEVERITY validateField( const BFFieldId& idField, 
                                   const DString& strValue, 
                                   const BFDataGroupId& idDataGroup ) = 0;

   /**
    * does the validation for the CBO
    * @param idDataGroup  - the identifier of the data group in which the validation should be made
    * @param lValidateGroup  - the validation group for which the validation is to be made
   */
   virtual SEVERITY validateAll( const BFDataGroupId& idDataGroup, long lValidateGroup = 0 ) = 0;

   /**
    * returns true if the CBO is updated
    * @param inclSubObj - do ve want to look into contained objects ?
   */
   virtual bool isUpdated( bool inclSubObj = true ) const = 0;
   /**
    * returns true if the CBO is updated from the lDataGroupId's perspective
    * @param idDataGroup  - the identifier of the data group in respect to which ve are looking for updates
    * @param inclSubObj - do ve want to look into contained objects ?
   */
   virtual bool isUpdatedForDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj = true ) const = 0;

   /**
    * returns true if the CBO has updates in another group than BF::HOST
   */
   virtual bool hasNonHostUpdates( ) const = 0;

   /**
    * returns true if the CBO has BF::HOST dataGroup updates 
    * @param inclSubObj  - do ve want to look into contained objects ?
   */
   virtual bool hasHostUpdates( bool inclSubObj = true ) const = 0;

   /**
    * returns true if the CBO has updates that should be sent to the dataBase
    * @param inclSubObj  - do ve want to look into contained objects ?
   */
   virtual bool hasTransactionUpdates( bool inclSubObj = true ) const = 0;

   /**
    * removes the containment of the object set with strKey from the idDataGroup's view perspective
    * 
    * @param strKey the string portion of the key of the object that we want to delete
    * @param idDataGroup
    *               the identifier of the data group with which we want to do the deletion
    * @param bRemoveFromMap
    *               true if the object should be physically deleted
    * @param bForce true if the object should be forced out regardless of overrides to isDeleteAllowed
    * 
    * @return Highest Condition severity on this thread's Condition stack.
    */
   virtual SEVERITY deleteObject( const DString & strKey, 
                                  const BFDataGroupId& idDataGroup,
                                  bool bRemoveFromMap = false,
                                  bool bForce = false ) = 0;

   /**
    * commits all the changes made by lDataGroupId dataGroup into the parent dataGroup, contained dataGroups are discarded 
    * @param idDataGroup - the identifier of the data group which we want to commit
   */
   virtual SEVERITY commitDataGroup( const BFDataGroupId& idDataGroup ) = 0;

   /**
    * resets the content of the CBO. It's state will be that that was initialized from the host for existing objects and 
    * that one in which it was after creation for new objects
    * @param idDataGroup - the identifier of the data group which we want to reset
    * @param inclSubObj - do we want to reset the contained objects too ?
   */
   virtual SEVERITY reset( const BFDataGroupId& idDataGroup, bool inclSubObj = true ) = 0;
   /**
    * rollsBack all changes made by this dataGroup. The contained dataGroups are discarded
    * @param idDataGroup - the identifier of the data group which we want to rollback
    * @param inclSubObj - do we want to rollback the contained objects too ?
   */
   virtual SEVERITY rollbackDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj = true ) = 0;

   /**
    * returns the max severity from the last validation of the field idField in dataGroup lDataGroupId
    * @param idField      - the identifier of the field for which we want to find out the error state
    * @param idDataGroup - the identifier of the data group which we want to find out the error state
   */
   virtual SEVERITY          getErrorState( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) const = 0;
   /**
    * fills into cndVec returns the errors from the last validation of the field idField in dataGroup lDataGroupId
    * @param idField      - the identifier of the field for which we want to find out the errors
    * @param idDataGroup - the identifier of the data group which we want to find out the errors
    * @param cndVec       - the CONDITIONVECTOR where we want to put the errors
   */
   virtual SEVERITY          getErrors    ( const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR & cndVec ) const = 0;
   /**
    * returns the max severity from the last validation of the CBO in dataGroup lDataGroupId
    * @param idDataGroup - the identifier of the data group which we want to find out the error state
   */
   virtual SEVERITY          getErrorState( const BFDataGroupId& idDataGroup ) const = 0;
   /**
    * returns a CONDITIONVECTOR with the errors from the last validation of the CBO in dataGroup lDataGroupId
    * @param idDataGroup - the identifier of the data group which we want to find out the errors
   */
   virtual CONDITIONVECTOR * getErrors    ( const BFDataGroupId& idDataGroup ) const = 0;
   /**
    * fills into cndVec returns the errors from the last validation of the CBO in dataGroup lDataGroupId
    * 
    * @param idDataGroup
    *                 the identifier of the data group which we want to find out
    *                 the errors.
    * @param cndVec   the CONDITIONVECTOR where we want to put the errors
    * @param bRecurse true if contained objects should be checked also.
    *                 Defaults to false.
    * @return 
    */
   virtual SEVERITY getAllErrors ( const BFDataGroupId& idDataGroup, 
                                   CONDITIONVECTOR & cndVec, 
                                   bool bRecurse = false ) const = 0;

   /**
    * sets the substitution set associated with this field using the ones that are stored in strValues.
    * This operation is done with dataGroup lDataGroupId
    * @param idField      - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param strValues     - the string containing the new substitution set
   */
   virtual void setFieldAllSubstituteValues( const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup, 
                                             const DString &strValues ) = 0;
   /**
    * sets the substitution set associated with this field using the ones that are linked to the
    * useFieldId field. This operation is done with dataGroup lDataGroupId
    * @param idField       - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param useFieldId    - the identifier of the field whose associated substitution set we want to set into this one
   */
   virtual void setFieldAllSubstituteValues( const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup, 
                                             const BFFieldId& useFieldId ) = 0;
   /**
    * sets the substitution set associated with this field using the ones that are linked to the
    * useFieldId field. This operation is done with data group lDataGroupId
    * @param idField       - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param useFieldId    - the identifier of the field whose associated substitution set we want to set into this one
   */
   virtual void setFieldSubstituteValues( const BFFieldId& idField, 
                                          const BFDataGroupId& idDataGroup, 
                                          const BFFieldId& useFieldId ) = 0;

   /**
    * sets the ReadOnly flag of idField field. This operation is done with dataGroup lDataGroupId
    * @param idField       - the identifier of the field for which we want to set the ReadOnly flag 
    * @param idDataGroup  - the identifier of the data group for which we want to set the ReadOnly flag
    * @param readonly      - the new value of the ReadOnly flag 
   */
   virtual void setFieldReadOnly( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool readonly ) = 0;

   /**
    * sets the required flag of idField field. This operation is done with dataGroup lDataGroupId
    * @param idField       - the identifier of the field for which we want to set the required flag 
    * @param idDataGroup  - the identifier of the data group for which we want to set the required flag
    * @param required      - the new value of the required flag 
   */
   virtual void setFieldRequired( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool required ) = 0;

   /**
    * returns true if dataGroup ldataGroupId exists in _dataGroupMap
    * @param idDataGroup  - the identifier of the data group which we want to see if it is registered with this CBO
   */
   virtual bool dataGroupExist  ( const BFDataGroupId& idDataGroup ) const = 0; // { return _dataGroupMap.find( lDataGroupId ) != _dataGroupMap.end(); }

   /**
    * retrieves the BFProperties object associated with this idField, lDataGroupId combination
    * @param idField       - the identifier of the field for which we want to retrieve the properties
    * @param idDataGroup  - the identifier of the data group for which we want to retrieve the properties
   */
   virtual BFProperties* getFieldProperties( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;

   virtual void getTrackActivity(DString& strTrack,DString& strActivity) const { strTrack = I_("N"); strActivity = NULL_STRING;}

   virtual void formatField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup ) const = 0;
   virtual void unformatField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup ) const = 0;

   virtual bool hasFieldsUpdateForGroup( long lGroup ) const = 0;

protected:

   /**
    * returns true if the field exists in the field map
    * @param idField      - the identifier of the field which we want to find if exists in the field map
   */
   virtual bool fieldExists( const BFFieldId& idField ) const = 0;
   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup ) = 0;

   /**
    * virtual function. Should be overwritten in order to avoid the deletion of the object
    * @param strKey        - the string part of the key of the object that we want to find out if it can be deleted
    * @param idDataGroup  - the identifier of the data group with which we want to find out if the object can be deleted
   */
   virtual bool canDeleteObject    ( const DString & strKey, const BFDataGroupId& idDataGroup ) = 0;
   /**
    * virtual function. Should be overwritten in order to do special processing on deletion
    * @param strKey        - the string part of the key of the object that we want deleted
    * @param idDataGroup  - the identifier of the data group with which we want the object deleted
    * @param bIsObjectDestroyed true: the object is being deleted.  false: the object is being marked as deleted.
   */
   virtual SEVERITY doDeleteObject ( const DString & strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed ) = 0;

   /**
    * virtual function. Should be overwritten in order to do CBO level validation
    * @param idDataGroup   - the identifier of the data group with which we want the object validated
    * @param lValidateGroup - the validation group for which we want to validate
   */
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) = 0;
   /**
    * virtual function. Should be overwritten in order to do CBO level validation
    * @param idDataGroup   - the identifier of the data group with which we want the object validated
   */
   virtual SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup ) = 0;

   /**
    * clears out the _fieldMap's content. everything that is in dataGroup different than BF::HOST 
    * will be deleted. BF::HOST content will be filled in with NULL pointers
   */
   virtual void clearFieldMap() = 0;
   /**
    * virtual function. Should be overwritten in order to have special processing on clearFieldMap
   */
   virtual SEVERITY doPreClearFields() = 0; // { return NO_CONDITION;}

   /**
    * virtual function. Called in refresh processing. Should be overwritten in order to special processing in refresh 
    * when CBOs are reinitialized
   */
   virtual SEVERITY reInit() { return(NO_CONDITION);}

   /**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param idField      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
   */
   virtual SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup ){ return(NO_CONDITION);};
   /**
    * initializes the fields that are marked as INIT_TO_DEFAULT.
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   virtual SEVERITY initDefaults( const BFDataGroupId& idDataGroup ) = 0;

   /**
    * clear out _objectMap
   */
   virtual void eraseObjectContainer() = 0;
   /**
    * virtual function. Should be overwritten in order to support short list/long list concept.
    * If on get field the field is not found in the _fieldMap and in the data object we have an opotunity
    * to do an aditional view cll in order to populate it.
    * @param idField     - the identifier of the field which we want to be populated 
    * @param strValue     - string reference where the value of the field should be filed in 
    * @param formattedReturn - do we want the strValue to be formated?
   */

   virtual void doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn ) {};
   /**
    * does crossEdit processing. It takes all crossEdits in which the field is part and if 
    * they have the IMMEDIATE_VALIDATION flag turned on and all fields that are part of it are valid
    * it tries to validate ti.
    * @param idField     - the identifier of the cross edit that we want to be processed 
    * @param idDataGroup - the identifier of the data group with which the cross edit processing should be done
   */
   virtual SEVERITY processCrossEdits( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;

   /**
    * clears out the VALID flag for all the cross edits in which idField is part, for the dataGroup lDataGroupId
    * @param idField      - the identifier of the field for which we want to invalidate the cross edits 
    * @param idDataGroup - the identifier of the data group for which we want to invalidate the cross edits 
   */
   virtual void setCrossEditInvalid(const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;
   /**
    * adds a new crossEdtId idField relation.
    * @param crossEdtId   - the identifier of the cross edit to which the field should be added 
    * @param idField      - the identifier of the field which we want to add to the cross edit 
   */
   virtual void addCrossEdit(const BFFieldId& crossEdtId, const BFFieldId& idField) = 0;
   /**
    * virtual function. It should be overwriten in order to do field validation. It is called by
    * validateField
    * @param idField      - the identifier of the field for which we are doing the validation
    * @param strValue     - the value of the field on which the validation is based on
    * @param idDataGroup - the identifier of the data group for which we are doing the validation
   */
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup ) { return(NO_CONDITION);}

   /**
    * sets the field value without validation. It is supposed to be valid
    * @param idField      - the identifier of the field which we want to set in
    * @param strValue     - the value that we want to set in
    * @param idDataGroup - the identifier of the data group that is used in setting the field
    * @param lFormatted   - is the value that is set in formatted
    * @param lValid       - flag indicating the new value of the VALID flag for this field
    * @param lSideEffect  - do we want to notify to the registered observers about the field change 
    * @param bApplyRelChanges call doApplyRelatedChanges
   */
   virtual SEVERITY setFieldNoValidate( const BFFieldId& idField,
                                        const DString& strValue,
                                        const BFDataGroupId& idDataGroup,
                                        bool  lFormatted = true, 
                                        bool  lValid     = true,
                                        bool  lSideEffect = false,
                                        bool  bApplyRelChanges = true) = 0;

   /**
    * clears out the error vector attached to the idField lDataGroupId combination
    * @param idField      - the identifier of the field whose errors we want to be cleared out
    * @param idDataGroup  - the identifier of the data group for which we are clearing out the field's errors
   */
   void clearFieldErrors( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   /**
    * return the value of the VALID flag associated with the idField lDataGroupId combination
    * @param idField       - the identifier of the field that we want to see if is walid 
    * @param idDataGroup  - the identifier of the data group for which we want to see if the field is walid 
   */
   virtual bool isFieldValid( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;
   /**
    * return the value of the UPDATED flag associated with the idField lDataGroupId combination
    * @param idField      - the identifier of the field that we want to see if is updated
    * @param idDataGroup  - the identifier of the data group for which we want to see if the field is updated
   */
   virtual bool isFieldUpdated( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) = 0;

   /**
    * virtual function. It should be overwritten in order to have special processing in a setField after the validation succeeds on in 
    * setFieldNoValidate after the value is stored in the CBO
    * @param idField       - the identifier of the field for which we want to apply the related changes
    * @param idDataGroup  - the identifier of the data group for which we want to apply the related field changes
   */
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) { return(NO_CONDITION);}

   /**
    * virtual function. It should be overwritten in order to have special processing the commiting process of a 
    * dataGroup
    * @param idDataGroup  - the identifier of the data group that should be commited
   */
   virtual void doCommitDataGroup( const BFDataGroupId& idDataGroup ) {} //has to be owerwriten in order to do precommit processing

   /**
    * virtual function. It should be overwritten in order to have special processing the reset process of a 
    * dataGroup
    * @param idDataGroup  - the identifier of the data group that should be reset
   */
   virtual void doReset( const BFDataGroupId& idDataGroup ){};//has to be owerwriten in order to have custom reset functionality

   virtual bool doFormatField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup ) const { return(false);}

   virtual bool doUnformatField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup ) const { return(false);}

protected:

   class OBJECT_INFO    
   {
   public:
      OBJECT_INFO()
      : flagsState_( 0 )
      , flagsGroup_( 0 )
      , pInstance_( NULL )
      , bOwnInstance_( false )
      {}

      OBJECT_INFO( const OBJECT_INFO& rhs )
      {
         *this = rhs;
      }

      OBJECT_INFO& operator=( const OBJECT_INFO& rhs )
      {
         if( this != &rhs )
         {
            flagsGroup_ = rhs.flagsGroup_;
            flagsState_ = rhs.flagsState_;
            pInstance_ = rhs.pInstance_;
            bOwnInstance_ = false;
         }
         return( *this );
      }

      inline long getGroupFlags() const { return( flagsGroup_ );}
      inline void setGroupFlags( long f ) { flagsGroup_ = f; }

      inline long getStateFlags() const { return( flagsState_ );}
      inline void setStateFlags( long f ) { flagsState_ = f; }
      inline void setStateFlag( long f ) { flagsState_ |= f; }
      inline void clearStateFlag( long f ) { flagsState_ &= ~f; }

      inline BFAbstractCBO* getInstance() const { return( pInstance_ ); }
      inline void setInstance( BFAbstractCBO* pInstance ) { pInstance_ = pInstance; }

      inline bool ownsInstance() const { return bOwnInstance_; }
      inline void setOwnInstance( bool b ) { bOwnInstance_ = b; }

      // <HACK>
      // </HACK>

   private:  
      long              flagsState_;   // Bit flags that represent current state (FIELD_FLAGS)
      long              flagsGroup_;   // Group bit flags
      BFAbstractCBO*    pInstance_;    // Object pointer
      bool              bOwnInstance_; // Owns m_pInstance
   };


   typedef std::map< BFObjectKey, OBJECT_INFO *, less_BFObjectKey >  OBJECT_MAP;
   typedef OBJECT_MAP::iterator                                      OBJECT_MAP_ITER;
#if _MSC_VER >= 1300
   typedef OBJECT_MAP::const_iterator                                OBJECT_MAP_CONST_ITER;
#else
   typedef OBJECT_MAP::iterator                                      OBJECT_MAP_CONST_ITER;
#endif
   typedef OBJECT_MAP::value_type                                    OBJECT_MAP_VALUE_TYPE;

protected:
   bool deleteObject( OBJECT_MAP_ITER & iter, const BFDataGroupId& idDataGroup, bool bRemoveFromMap = false, bool bForce = false );

private:
   BFAbstractCBO( const BFAbstractCBO &copy );
   BFAbstractCBO& operator=( const BFAbstractCBO& copy );

   VALIDATION_MODE         validationMode_;
   BFAbstractCBO * const   parent_;


   OBJECT_MAP           _objectMap;

private:
   virtual bool isDummy( const OBJECT_MAP_CONST_ITER & iter ) const = 0;

protected:
   /**
    * returns true if the flag lFlag is turned on
   * @param lFlag    - long value where we are looking for the flags
   * @param nValues  - mask saying which flags are we carring for
   */
   bool flagsAreOn(  long lFlag, long nValues ) const
   {
      return(lFlag & nValues) != 0;
   }



protected:
   bool _hasNonBFHOSTsetObjects;

   bool hasNonHostData() const { return(_hasNonBFHOSTsetObjects);}
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfcbo/bfabstractcbo.hpp-arc  $
//
//   Rev 1.10   Oct 22 2004 08:53:26   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.9   May 08 2003 15:31:40   PURDYECH
//Added ability to force a delete of a contained object.
//
//   Rev 1.8   Feb 26 2003 09:41:10   PURDYECH
//Remove updateLevel 
//
//   Rev 1.7   Jan 06 2003 16:40:02   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.6   Nov 27 2002 15:02:50   PURDYECH
//Documentation Changes
//
//   Rev 1.5   Oct 09 2002 17:40:00   PURDYECH
//New PVCS Database
//
//   Rev 1.4   Aug 30 2002 18:17:14   SMITHDAV
//One more field id fix.
//
//   Rev 1.3   Aug 29 2002 12:51:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:08:44   PURDYECH
//BFData Implementation
//
//   Rev 1.1   22 Mar 2002 15:11:22   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   Feb 25 2002 19:18:00   PURDYECH
//Initial revision.
//
