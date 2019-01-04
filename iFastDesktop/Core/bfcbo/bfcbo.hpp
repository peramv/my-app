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
// ^FILE   : BFCBO.hpp
// ^AUTHOR : Mike Metzger (Replaces old BFCBO, ListBase, CBEBase)
// ^DATE   : May 1999
//
// ^CLASS    : BFCBO
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#pragma warning( disable : 4503)  

#include <SrcPrag.h>
#include <assert.h>
#include <bfcbo\BFObservable.hpp>
#include <commonport.h>
#include <bfcbo\bfabstractcbo.hpp>
#include <Condition.hpp>
#include <Frame.hpp>
#include <DString.hpp>
#include <bfcbo\BFProperties.hpp>
#include <bfdbrkr\AsyncRequestListener.hpp>
#include <bfcbo\BFObjectKey.hpp>
#include <map>
#include <vector>
#include <bfdata\bfdata.hpp>
#include <bfutil/bfstringfunctions.hpp>
#include <bfutil/elementattribute.hpp>

#include <bfutil\BFEvent.hpp>
#include <bfutil\BFCritSec.hpp>

// forward declarations
class BFObjIter;
class BFSecurity;
class BFSession;
class BFObserver;
class BFObservable;
class BFRequest;
class BFRequestor;
class BFHost;
class AsyncRequestor;
class HostTransactionContainer;

class BasicDocument;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

#include <iostream>

/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * write raw data to the ostream object.
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #norawdata
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl rawdata( i_ostream &_strm );
/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * not write raw data to the ostream object.
 * <p>This setting is <b>persistent</b>.  All subsequent BFCBO operations
 * to the ostream object will write raw data.
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #rawdata
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl norawdata( i_ostream &_strm );
/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * write all fields to the ostream object.
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #noallfields
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl allfields( i_ostream &_strm );
/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * write only classFieldInfo (and not generic fields) to the ostream 
 * object.
 * <p>This setting is <b>persistent</b>.  All subsequent BFCBO operations
 * to the ostream object will write all fields.
 *
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #allfields
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl noallfields( i_ostream &_strm );
/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * write their contained objects (those defined with setObject) 
 * to the ostream object.
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #norecurse_objects
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl recurse_objects( i_ostream &_strm );
/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * not write their contained objects (those defined with setObject) 
 * to the ostream object.
 * <p>This setting is <b>persistent</b>.  All subsequent BFCBO operations
 * to the ostream object will recurse their objects
 *
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #recurse_objects
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl norecurse_objects( i_ostream &_strm );

/**
 * used in ostream calls.  Causes subsequent BFCBO objects to 
 * be written to the ostream object as though norecurse_objects, noallfields,
 * and norawdata were called.
 * 
 * @param _strm  the ostream object being written to
 * @return the ostream object being written to
 * @see #norecurse_objects
 * @see #noallfields
 * @see #norawdata
 * @see BFCBO
 * @see i_ostream
 */
BFBASE_LINKAGE i_ostream& __cdecl resetbfbaseio( i_ostream &_strm );

//namespace BF
//{
//   static const long HOST = 0;
//}

/**
 * This is the base class for all CBOs ( business objects )
 * 
 * It is doing basic functionality like basic view calls, datagroup management
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 11/07/1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFCBO : public BFAbstractCBO, AsyncRequestListener
{
public:


   BFCBO( BFAbstractCBO *parent, BFAbstractCBO::VALIDATION_MODE validationMode=IMMEDIATE );
   BFCBO( BFAbstractCBO::VALIDATION_MODE validationMode=IMMEDIATE );


/**
 * Represents the different object/field related state flags.
 *
 * <pre><dir>
 *@@ These are the valid validation modes:
 *@@   NONE                   - none                    = nothing
 *@@   READ_ONLY              - read_only               = field is readOnly
 *@@   REQUIRED               - required                = field/object is required
 *@@   UPDATED                - updated                 = field is updated
 *@@   VALID                  - valid                   = field is valid
 *@@   PRIVATE_USE            - private_use             = field is used internally only, any getField will return an empty string
 *@@   INIT_TO_DEFAULT        - init_to_default         = field should be filled in with default values
 *@@   NO_BASE_DELETE         - no_base_delete          = object is not owned, it should not be destroyed on rollBack/commit/delete
 *@@   NOT_ON_HOST            - not_on_host             = object is new created in memory, it doesn't exist on the backend
 *@@   LIST_INVALID           - list_invalid            = validated only on validateAll(...)
 *@@   LIST_OBJECT            - list_object             = the object is a list, it can contain dummy items
 *@@   NON_DUMMY              - non_dummy               = the object is not dummy
 *@@   CALCULATED_FIELD       - calculated_field        = the field is calculated, it doesn't exist on the backend
 *@@   IMMEDIATE_VALIDATION   - immediate_validation    = used for crossedits, they will be validated immediatelly when all contained fields are valid
 * </pre></dir>
 */
   enum STATE_FLAGS 
   {
      NONE                  = 0x0000,
      READ_ONLY             = 0x0001,
      REQUIRED              = 0x0002,
      UPDATED               = 0x0004,
      VALID                 = 0x0008,
      PRIVATE_USE           = 0x0010,
      INIT_TO_DEFAULT       = 0x0020, //not used
      NO_BASE_DELETE        = 0x0040,
      NOT_ON_HOST           = 0x0080,
      LIST_INVALID          = 0x0100,
      LIST_OBJECT           = 0x0200,
      NON_DUMMY             = 0x0400,
      CALCULATED_FIELD      = 0x0800,
      IMMEDIATE_VALIDATION  = 0x1000,
      APPEND_VALUE_TO_SUBST = 0x2000,
   };

   typedef enum 
   {
      DEFAULT,
      DELETE_ON_DTOR,
      NO_DELETE_ON_DTOR
   } OBJ_DELETE;


/**
 * Used to represent a field entry inside the CBO
 *
 */
   class CLASS_FIELD_INFO 
   {
   public:
//      CLASS_FIELD_INFO( const BFFieldId& fieldId, long stateFlags, long groupFlags )
//      : m_fieldId( fieldId )
//      , m_lStateFlags( stateFlags )
//      , m_lGroupFlags( groupFlags )
//      {
//      }

      const BFFieldId& getFieldId() const { return m_fieldId; }
      long getStateFlags() const { return m_lStateFlags; }
      long getGroupFlags() const { return m_lGroupFlags; }
      /**
       * contains the unique field Identifier for this entry
       */
      const BFFieldId m_fieldId;
      /**
       * contains the field state flags
       */
      long          m_lStateFlags;
      /**
       * contains the field group flags
       */
      long          m_lGroupFlags;
   };


/**
 * Used to represent a object entry inside the CBO
 */
   typedef struct
   {
      /**
       * contains the unique name that identifies the object
       */
      I_CHAR *      m_strName;
      /**
       * contains the field state flags
       */
      long          m_lStateFlags;
      /**
       * contains the field group flags
       */
      long          m_lGroupFlags;
   } CLASS_OBJECT_INFO;


   /**
    * Used to set the non Dummy flag
   */
   void setNonDummyFlag( ){ _lBFStatus |= NON_DUMMY;}
   /**
    * Used to clear the non Dummy flag
   */
   bool getNonDummyFlag( ) const { return(_lBFStatus & NON_DUMMY ) != 0;}
   /**
    * returns the updated state of a CBO based only on his fields
   */
   bool hasUpdatedFields( const BFDataGroupId& idDataGroup = BF::HOST ) const;

   /**
    * returns the maximum severity set on the last validation of this CBO, from the point of view of dataGroup idDataGroup
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   SEVERITY getMaxValidationSeverityForObject( const BFDataGroupId& idDataGroup = BF::HOST ) const;
   /**
    * returns the maximum severity set on the last validation of the contained CBOs of this one, from the point of view of dataGroup idDataGroup
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   SEVERITY getMaxValidationSeverityForChildren( const BFDataGroupId& idDataGroup = BF::HOST ) const;
   /**
    * returns the maximum severity set on the last validation of this CBO and contained ones, from the point of view of dataGroup idDataGroup
    * @param idDataGroup       - the data group identifier for which we want to get the errors
   */
   SEVERITY getMaxValidationSeverityForObjectAndChildren( const BFDataGroupId& idDataGroup = BF::HOST ) const;

   /**
    * refreshes a CBO 
    * @param bNewObject       - it tells to the object if it is a new element in the calling container
   */
   virtual SEVERITY refresh( bool bNewObject = false );

   /**
    * returns in lCndVector all object level errors from inside this CBO
    * @param idDataGroup       - the data group identifier for which we want to get the errors
    * @param lCndVector         - CONDITIONVECTOR reference where we want the errors to be stored
    * @param lValidateGroup     - validation group mask 
    * @param lValidateGroup     - do we want to get errors from contained objects to 
   */
   SEVERITY getNonFieldErrors( const BFDataGroupId& idDataGroup, 
                               CONDITIONVECTOR & lCndVector, 
                               long lValidateGroup = 0, 
                               bool inclSubObj = true );
   /**
    * clears out the value filed in a field 
    * @param fieldId          - the field identifier for the field that we want cleared out
    * @param idDataGroup     - the data group identifier for which we want to clear out the field 
   */
   SEVERITY clearField( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   /**
    * returns in lFieldIdVector all fields that are making this cross edit
    * @param fieldId          - the field identifier for the cross edit for we want to obtain fields that are part of
    * @param lFieldIdVector   - the vector where we should put the founded fields
   */
   void getCrossEditFields( const BFFieldId &fieldId,  std::vector<BFFieldId> & lFieldIdVector );
   /**
    * sets the PRIVATE_USE flag for this field, all subsecvent getFields ion this field will return an empty string
    * @param fieldId          - the field identifier for the field for we want to set the flag
    * @param idDataGroup     - the data group identifier for which we want to set the flag
    * @param bFlag            - the flag value that should be set in
   */
   void setNotApplicable( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool bFlag );
   /**
    * resets the PRIVATE_USE flag for this field, the field value becames again visible from exterior
    * @param fieldId          - the field identifier for the field for we want to get the flag
    * @param idDataGroup     - the data group identifier for which we want to get the flag
   */ 
   bool getNotApplicable( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );

   /**
    * sets the VALID flag for all fields for idDataGroup dataGroup
    * @param idDataGroup     - the data group identifier for which we want to set the flags
   */ 
   void setAllFieldsValid(const BFDataGroupId& idDataGroup);

   /**
    * clear out the UPDATED flag for all fields for idDataGroup dataGroup. It can work recusively into contained objects
    * @param idDataGroup     - the data group identifier for which we want to clear the flag
    * @param inclSubObj       - do we want to do the operation recursivelly
   */ 
   void clearUpdatedFlags( const BFDataGroupId& idDataGroup, bool inclSubObj = false );

   /**
    * get the Observable object for this fieldId, dataGroupId combination. If it doesn't find one it will create it 
    * @param fieldId          - the field identifier for which we want to retrieve the BFObservable object
    * @param idDataGroup     - the data group identifier for which we want to retrieve the BFObservable object
    * @param eEventCateg      - are we interested in field notifications ( FIELD_NOTIFICATIONS ) or not
   */
   BFObservable * getObservable( const BFFieldId &fieldId, 
                                 const BFDataGroupId& idDataGroup, 
                                 E_EVENT_GROUP eEventCateg, 
                                 E_EVENT eEventId ) const;

   /**
    * registers an observer object for this fieldId, dataGroupId combination. 
    * @param fieldId          - the field identifier for which we want to set the BFObserver object
    * @param idDataGroup     - the data group identifier for which we want to set the BFObserver object
    * @param pObserver        - pointer to the BFObserver object that we want to be set
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventCateg      - the event identifier
   */ 
   bool registerObserver( const BFFieldId &fieldId, 
                          const BFDataGroupId& idDataGroup, 
                          BFObserver * pObserver, 
                          E_EVENT_GROUP eEventCateg, 
                          E_EVENT eEventId ) const;
   /**
    * deregisters the pObserver observer object for this fieldId, dataGroupId combination. 
    * @param fieldId         - the field identifier for which we want to remove the BFObserver object
    * @param idDataGroup     - the data group identifier for which we want to remove the BFObserver object
    * @param pObserver        - pointer to the BFObserver object that we want to be removed
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventCateg      - the event identifier
   */ 
   bool deleteObserver( const BFFieldId &ieldId, 
                        const BFDataGroupId& idDataGroup, 
                        BFObserver * pObserver, 
                        E_EVENT_GROUP eEventCateg, 
                        E_EVENT eEventId ){ return(false);}

   /**
    * deregisters all observers registered for this fieldId, dataGroupId combination. 
    * @param fieldId          - the field identifier for which we want to remove the BFObserver objects
    * @param idDataGroup     - the data group identifier for which we want to remove the BFObserver objects
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventCateg      - the event identifier
   */ 
   void deleteObservers( const BFFieldId &ieldId, 
                         const BFDataGroupId& idDataGroup, 
                         E_EVENT_GROUP eEventCateg, 
                         E_EVENT eEventId ){}
   /**
    * not used
   */ 
   void deleteAllObservers( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup ){}
   /**
    * notifies all observers registered for this fieldId, dataGroupId combination. 
    * @param fieldId          - the field identifier for which we want to notify the BFObserver object
    * @param idDataGroup     - the data group identifier for which we want to notify the BFObserver object
    * @param eEventCateg      - the type of notification ( FIELD_NOTIFICATIONS, NON_FIELD_NOTIFICATIONS ) 
    * @param eEventCateg      - the event identifier
    * @param hint             - the hint string that we want to pass in 
   */ 
   void notifyObservers( const BFFieldId &fieldId, 
                         const BFDataGroupId& idDataGroup, 
                         E_EVENT_GROUP eEventCateg, 
                         E_EVENT eEventId, 
                         const DString & hint );

   /**
    * returns the object that owns this one
   */ 
   // KLUDGE KLUDGE KLUDGE ... these redirect the call to BFAbstractCBO and assert if the parent is not a BFCBO
   const BFCBO *getParent() const; 
   BFCBO *getParent(); 

   /**
    * returns the ultimate parent object of this one
   */ 
   const BFAbstractCBO * getTopLevelAncestor() const;
   BFAbstractCBO * getTopLevelAncestor();

   virtual bool isSession() const;
   /**
    * returns this objects session
   */ 
   virtual const BFSession &getSession() const = 0; 
   virtual BFSession &getSession() = 0; 

   /**
    * validates and commits the object from this dataGroup perspective
    * @param idDataGroup - which data group that we want to validate and commit
   */ 
   SEVERITY commitAndValidateDataGroup( const BFDataGroupId& idDataGroup );
   /**
    * deletes the dummy items for added whith dataGroup
    * @param idDataGroup - the identifier of the data group whose dummy items we want to remove
    * @param inclSubObj     - do we want to do the operation recursively into the contained objects
   */ 
   SEVERITY deleteNonUpdatedAddedElements( const BFDataGroupId& idDataGroup, bool inclSubObj = true );
   /**
    * returns the initial string key for this object. 
   */ 
   virtual const DString * getInitialStrKey()  { return(NULL);}

   /**
    * returns true if the object contains other objects than dummy ones from the dataGroup's perspective
    * @param idDataGroup - the identifier of the data group that we want to know if it has non dummy items
   */ 
   bool hasNonDummyEntries( const BFDataGroupId& idDataGroup ) const;

   /**
    * returns true if this object has an entry in the field map for this fieldId
    * @param fieldId - the field id which we are looking for into the _fieldMap
   */
   bool existsFieldInfo( const BFFieldId &fieldId );
   /**
    * returns the parent dataGroup of the group idDataGroup 
    * @param idDataGroup - the identifier of the data group for which we are looking for the parent
   */
   const BFDataGroupId& getParentDataGroup( const BFDataGroupId& idDataGroup );

   /**
    * returns the default stringKey for new items.It is made by '999' plus an integer sequential number padded left with '0' to 7 positions
    * @param strKey - DString reference where we want to store the key
   */
   virtual void getStrKeyForNewItem( DString & strKey )
   {
      strKey = I_( "999" ) + DString::asString( _iNextKey++ ).padLeft( 7, '0' );
   }

   /**
    * returns true if the lParentDataGroup is an ancestor for idDataGroup
    * @param lParentDataGroup - the identifier of the supposedly parent data group 
    * @param idDataGroup     - the identifier of the supposedly child data group 
   */
   bool isParentDataGroup( const BFDataGroupId& idParentDataGroup, const BFDataGroupId& idDataGroup ) const;
   /**
    * returns true if the lContainerDataGroup is an ancestor for idDataGroup
    * @param idContainerDataGroup - the identifier of the supposedly container data group 
    * @param idDataGroup        - the identifier of the supposedly contained data group 
   */
   bool isContainedDataGroup( const BFDataGroupId& idContainerDataGroup, const BFDataGroupId& idDataGroup ) const;
   /**
    * creates and returns a new list item object
    * @param objKey - reference to the key with which the object will be set. The key is filled in by the method
   */
   BFCBO *getNewListItem( BFObjectKey &objKey );

   /** 
    * returns true if the async data retrieval is done
    */
   bool isAsyncRetrieveDone ();

   /**
    * Destructor
   */
   virtual ~BFCBO();

   /**
    * returns true if the flag lFlag is turned on
   * @param lFlag    - long value where we are looking for the flags
   * @param nValues  - mask saying which flags are we carring for
   */
   bool flagsAreOn(  long lFlag, long nValues ) const
   {
      return(lFlag & nValues) != 0;
   }

   /**
    * fills in the field values into the data object, from idDataGroup's perspective
    * @param data           - The data object where we want the values stored
    * @param idDataGroup   - The data group ID 
    * @param fAppendNewTags - do we want to add new tags
    * @param fUseDataObjectOnly - do we want to use only the data object
   */
   virtual SEVERITY getData( BFData &data, 
                             const BFDataGroupId& idDataGroup, 
                             bool fAppendNewTags = false, 
                             bool fUseDataObjectOnly = false );

   /**
    * gets the field value from idDataGroup's perspective
    * @param fieldId       - the field identifier to be get
    * @param strValue       - the DString reference where we want to store the value
    * @param idDataGroup   - the data group identifier with which we want to do the get
    * @param formattedReturn  - do we want to format the returned value
   */
   virtual void getField( const BFFieldId &fieldId, 
                          DString & strValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const;

   /**
    * gets the field's initial value 
    * @param fieldId        - the identifier of the field to be get
    * @param strValue       - the where to the string we want to the value to be stored 
    * @param formattedReturn  - do we want to format the returned value
   */
   virtual bool getFieldBeforeImage( const BFFieldId &fieldId, DString & strValue, bool formattedReturn = false ) const;

   /**
    * gets the key for an object
    * @param objKey       - a reference to BFObjectKey. That is where the key should be stored
    * @param data         - pointer to a data object from which we can take data in oreder to compute the key 
    * @param newObject    - we are looking for a key for a new list element or not
   */
   void getKey( BFObjectKey &objKey, const BFData *data = NULL, bool newObject = false );

   /**
    * gets the string part of the key for an object
    * @param strKey       - a reference to a string in which we will return the string key. 
    * @param data         - pointer to a data object from which we can take data in oreder to compute the key 
   */
   virtual void getStrKey( DString &strKey, const BFData *data = NULL )
   {
      strKey = DString::asString( _iNextKey++ ).padLeft( 10, '0' );;
   }


   /**
    * sets a dataGroup containment relation into the CBO. lParentDataGroupId will be the parent of idDataGroup 
    * @param idParentDataGroup - the identifier of the parent data group
    * @param idDataGroup       - the identifier of the child data group
   */
   void setGroup ( const BFDataGroupId& idParentDataGroup, const BFDataGroupId& idDataGroup );

   /**
    * returns true if an object is new list element
   */
   bool isNew( ) const { return(_lBFStatus & NOT_ON_HOST) != 0;}

   /**
    * Determine if this CBO can have versionable fields (i.e. those with a 
    * BFDataGroupId which is *not* BF::HOST).
    * 
    * @return true if this CBO can have versionable fields, otherwise false
    */
   bool isVersionable() const { return bVersionable_; }
   void setVersionable( bool bVersionable ) { bVersionable_ = bVersionable; }

   /**
    * does the initialisation with default values of fields inside a CBO
    * @param idDataGroup - the identifier of the data group for which we want to do the initialisation
   */
   void initWithDefaultValues( const BFDataGroupId& idDataGroup );

   /**
    * sets an object as a new list element
   */
   void setObjectNew( )
   {
      _lBFStatus |= NOT_ON_HOST;
   }

   /**
    * returns true if an object is list type CBO
   */
   bool isList( ) const { return(_lBFStatus & LIST_OBJECT) != 0;}

   /**
    * sets the object as a list
   */
   void setObjectAsList( ) { _lBFStatus |= LIST_OBJECT;}

   /**
    * sets the list as invalid
   */
   void setListInvalid( ) { _lBFStatus |= LIST_INVALID;}

   /**
    * retrieves a contained CBO based on the key
    * @param strKey        - the string key with which we want to retrieve the object
    * @param idDataGroup  - the data group identifier with which we want to retrieve the object
    * @param type          - the type with which we want to retrieve the object
    * @param activity      - the activity with which we want to retrieve the object
   */
   BFAbstractCBO* getObject( const DString& strKey, 
                             const BFDataGroupId& idDataGroup,
                             BF_OBJ_TYPE type = OBJ_TYPE_NONE, 
                             BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE) const;
   /**
    * retrieves a contained CBO based on the key, if it doesn't find a match it will create one.
    * @param strKey        - the string key with which we want to retrieve the object
    * @param idDataGroup  - the data group identifier with which we want to retrieve the object
    * @param type          - the type with which we want to retrieve the object
    * @param activity      - the activity with which we want to retrieve the object
   */
   BFAbstractCBO* getObject( DString& strKey, 
                             const BFDataGroupId& idDataGroup,
                             BF_OBJ_TYPE type = OBJ_TYPE_NONE, 
                             BF_OBJ_ACTIVITY activity = OBJ_ACTIVITY_NONE) const;


   /**
    * sets a containment relation beween the current CBO and the one that is passed as parameter, using the key objKey
    * 
    * @param objKey  the key with which we want to set the object
    * @param pObject the object that we want to set in
    * @param eBaseDelete
    *                indicates if pObject should be deleted when this object
    *                is destroyed.  This may have the value DELETE_ON_DTOR, in
    *                which case pObject will be deleted when this object is
    *                destroyed (or when setObject causes the contained object for
    *                the key to be replaced), NO_DELETE_ON_DTOR, in which
    *                case the pObject will never be destroyed by this object,
    *                or DEFAULT, in which case the value of the existing object
    *                will be used (in the case of replacement or copying) or
    *                DELETE_ON_DTOR (in the case of insertion).
    * @return 
    */
   bool setObject( const BFObjectKey &objKey, BFAbstractCBO* pObject, OBJ_DELETE eBaseDelete = DEFAULT );

   /**
    * sets a containment relation beween the current CBO and the one that is passed as parameter, using a key made by strKey, activity, idDataGroup
    * type, subType, categ parameters
    * 
    * @param pObject  the object that we want to set in
    * @param strKey   the string key with which we want to set the object
    * @param activity
    * @param idDataGroup
    *                 the data group identifier with which we want to set the object
    * @param type     the type with which we want to set the object
    * @param subType
    * @param categ    the category with which we want to set the object
    * @param eBaseDelete
    *                 indicates if pObject should be deleted when this object
    *                 is destroyed.  This may have the value DELETE_ON_DTOR, in
    *                 which case pObject will be deleted when this object is
    *                 destroyed (or when setObject causes the contained object for
    *                 the key to be replaced), NO_DELETE_ON_DTOR, in which
    *                 case the pObject will never be destroyed by this object,
    *                 or DEFAULT, in which case the value of the existing object
    *                 will be used (in the case of replacement or copying) or
    *                 DELETE_ON_DTOR (in the case of insertion).
    * @return 
    */
   bool setObject( BFAbstractCBO*  pObject, 
                   const DString & strKey,
                   BF_OBJ_ACTIVITY activity       = OBJ_ACTIVITY_NONE,
                   const BFDataGroupId& idDataGroup = BF::HOST,
                   BF_OBJ_TYPE     type           = OBJ_TYPE_NONE, 
                   OBJ_DELETE      eBaseDelete    = DEFAULT );

   /**
    * Change the key of an entry in the object map.
    * 
    * @param keyOrig The original key to find
    * @param keyNew  The new key to set the object to
    * 
    * @return true if the object was found and reset
    */
   bool resetObjectKey( const BFObjectKey& keyOrig, const BFObjectKey& keyNew );

   /**
    * does the view call for initialising a CBO and creates a repeat CBO for each repeat from the view's response.
    * 
    * @param request   - reference of BFRequest type to a constant request definition
    * @param queryData - reference to at data object that contains the request data
    * @param receivedData
    *                  - reference to at data object that will be filled with the response data
    * @param requestor - reference of BFRequestor type to a requestor that will do all the work.
    * @param bInsertLast
    *                  - true if we want that the response data file to be inserted at the end of the vector
    * @return NO_CONDITION if data was retrieved.
    */
   virtual SEVERITY ReceiveData( const BFRequest &request,
                                 BFData &queryData,
                                 BFData &receivedData,
                                 BFRequestor &requestor,
                                 bool bInsertLast = false );

   /**
    * does the view call for initialising a CBO and creates a repeat CBO for each repeat from the view's response.
    * in this case the response data  object is allocated by this method and is cleaned up if a condition > WARNING occurs.
    * 
    * @param request   - reference of BFRequest type to a constant request definition
    * @param queryData - reference to at data object that contains the request data
    * @param responseDataSetId
    *                  - data set id of the response to be recieved
    * @param requestor - reference of BFRequestor type to a requestor that will do all the work.
    * @param bInsertLast
    *                  - true if we want that the response data file to be inserted at the end of the vector
    * @return NO_CONDITION if data was retrieved.
    */
   virtual SEVERITY ReceiveData( const BFRequest &request,
                                 BFData &queryData,
                                 long responseDataSetId,
                                 BFRequestor &requestor,
                                 bool bInsertLast = false );

   /**
    * initiates the view call for initialising a CBO asyncronously.
    * 
    * @param request   - reference of BFRequest type to a constant request definition
    * @param queryData - reference to at data object that contains the request data
    * @param receivedData
    *                  - reference to at data object that will be filled with the response data
    * @param requestor - reference of BFRequestor type to a requestor that will do all the work.
    */
   void AsyncReceiveData( const BFRequest &request,
                          BFData &queryData,
                          BFData &receivedData,
                          BFRequestor &requestor,
                          int callBackOption = 0);

   /**
    * initiates the view call for initialising a CBO asyncronously.
    * in this case the response data  object is allocated by this method.
    * 
    * @param request   - reference of BFRequest type to a constant request definition
    * @param queryData - reference to at data object that contains the request data
    * @param responseDataSetId
    *                  - data set id of the response to be recieved
    * @param requestor - reference of BFRequestor type to a requestor that will do all the work.
    */
   void AsyncReceiveData( const BFRequest &request,
                          BFData &queryData,
                          long responseDataSetId,
                          BFRequestor &requestor,
                          int callBackOption = 0);

   /**
    * implements the abstract interface of AsyncRequestListener -- called by AsyncRequestor when a response is returned.
    * 
    * @param severity      - the severity of the condition or NO_CONDITION
    * @param condition     - host condition for the request or NULL if no condition
    * @param receivedData  - data object containing the response data
    * @param moreAvailable - true if there are more records to be retrieved.
    */
   virtual void notifyResponse( SEVERITY severity, 
                                const Condition *condition, 
                                BFData *receivedData, 
                                bool moreAvailable, 
                                int callBackOption = 0);

   /**
   * virtual function called by notifyResponse which can be overrided to manipulate the returning data.
   * 
   * @param severity      - the severity of the condition or NO_CONDITION
   * @param condition     - host condition for the request or NULL if no condition
   * @param receivedData  - data object containing the response data
   * @param moreAvailable - true if there are more records to be retrieved.
   */

   virtual void donotifyResponse ( SEVERITY severity, 
                                   const Condition *condition, 
                                   BFData *receivedData, 
                                   bool moreAvailable,
                                   int callBackOption = 0 );

   /**
   * void function which blocks until the data requested has been received.  Used in conjuntion with AsyncReceiveData for special cases where
   * direct Data object operations are performed.
   * 
   */

   bool dataReady ();

   /**
    * Returns the moreRecordsAvailable property set by ReceiveData on the last call. 
    * The property is true prior to the first call.
    *
    * @return false if there are no more reecords to be recieved be ReceiveData.
   */
   bool doMoreRecordsExist()
   {
      return(_moreRecordsAvailable);
   }

   /**
    * stores the values contained in the data object into the CBO's fields for idDataGroup dataGroup
    * @param data          - the data object where the data is taken from.
    * @param idDataGroup  - the data group with which the data is set in 
   */
   virtual SEVERITY setData( const BFData &data, const BFDataGroupId& idDataGroup );

   /**
    * sets the field value for the idDataGroup dataGroup, the input field value can be formatd or not, and it 
    * can or not notify the registered observers
    * @param fieldId       - the identifier of the field to be set
    * @param strValue      - the value to be set in
    * @param idDataGroup  - the identifier of the data group which will be used
    * @param lFormatted    - strValue is formated or not
    * @param lSideEffect   - do we want to have the registered observers notified about the change
    * @param bCheckCurrentValue   - do we want to call getField in order to compare existing value with the new one
   */
   virtual SEVERITY setField( const BFFieldId &fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);

   /**
    * does the validation for the field lFieldId and dataGroup  idDataGroup
    * @param fieldId       - the identifier of the field to be validated
    * @param strValue      - the value to be validated
    * @param idDataGroup  - the identifier of the data group in which the validation should be made
   */
   SEVERITY validateField( const BFFieldId &fieldId, const DString& strValue, const BFDataGroupId& idDataGroup );

   /** 
     * for the purpose to force a designated field validation in the inquire mode
     * @param fieldId      - the identifier of the field to be validated
     * param idDataGroup  - the identifier of the data group in which the validation should be made
    */
   SEVERITY revalidateField( const BFFieldId &fieldId,const BFDataGroupId& idDataGroup );

   /**
    * does the validation for the CBO
    * @param idDataGroup  - the identifier of the data group in which the validation should be made
    * @param lValidateGroup  - the validation group for which the validation is to be made
   */
   SEVERITY validateAll( const BFDataGroupId& idDataGroup, long lValidateGroup = 0 );

   /**
    * returns true if the CBO is updated
    * @param inclSubObj - do ve want to look into contained objects ?
   */
   bool isUpdated( bool inclSubObj = true ) const;
   /**
    * returns true if the CBO is updated from the idDataGroup's perspective
    * @param idDataGroup  - the identifier of the data group in respect to which ve are looking for updates
    * @param inclSubObj - do ve want to look into contained objects ?
   */
   bool isUpdatedForDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj = true ) const;

   /**
    * returns true if the CBO has updates in another group than BF::HOST
   */
   bool hasNonHostUpdates( ) const;

   /**
    * returns true if the CBO has BF::HOST dataGroup updates 
    * @param inclSubObj  - do ve want to look into contained objects ?
   */
   bool hasHostUpdates( bool inclSubObj = true ) const;

   /**
    * returns true if the CBO has updates that should be sent to the dataBase
    * @param inclSubObj  - do ve want to look into contained objects ?
   */
   bool hasTransactionUpdates( bool inclSubObj = true ) const;

   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< ( i_ostream &stream,
                                                       const BFCBO &base );
   friend BFObjIter;
   friend HostTransactionContainer;

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
   SEVERITY deleteObject( const DString & strKey, const BFDataGroupId& idDataGroup, bool bRemoveFromMap = false, bool bForce = false );

   /**
    * commits all the changes made by idDataGroup dataGroup into the parent dataGroup, contained dataGroups are discarded 
    * @param idDataGroup - the identifier of the data group which we want to commit
   */
   SEVERITY commitDataGroup( const BFDataGroupId& idDataGroup );

   /**
    * resets the content of the CBO. It's state will be that that was initialized from the host for existing objects and 
    * that one in which it was after creation for new objects
    * @param idDataGroup - the identifier of the data group which we want to reset
    * @param inclSubObj - do we want to reset the contained objects too ?
   */
   SEVERITY reset( const BFDataGroupId& idDataGroup, bool inclSubObj = true );
   /**
    * rollsBack all changes made by this dataGroup. The contained dataGroups are discarded
    * @param idDataGroup - the identifier of the data group which we want to rollback
    * @param inclSubObj - do we want to rollback the contained objects too ?
   */
   SEVERITY rollbackDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj = true );

   /**
    * returns the max severity from the last validation of the field fieldId in dataGroup idDataGroup
    * @param fieldId      - the identifier of the field for which we want to find out the error state
    * @param idDataGroup - the identifier of the data group which we want to find out the error state
   */
   SEVERITY          getErrorState( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup ) const;
   /**
    * fills into cndVec returns the errors from the last validation of the field fieldId in dataGroup idDataGroup
    * @param fieldId     - the identifier of the field for which we want to find out the errors
    * @param idDataGroup - the identifier of the data group which we want to find out the errors
    * @param cndVec       - the CONDITIONVECTOR where we want to put the errors
   */
   SEVERITY          getErrors    ( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, CONDITIONVECTOR & cndVec ) const;
   /**
    * returns the max severity from the last validation of the CBO in dataGroup idDataGroup
    * @param idDataGroup - the identifier of the data group which we want to find out the error state
   */
   SEVERITY          getErrorState( const BFDataGroupId& idDataGroup ) const;
   /**
    * returns a CONDITIONVECTOR with the errors from the last validation of the CBO in dataGroup idDataGroup
    * @param idDataGroup - the identifier of the data group which we want to find out the errors
   */
   CONDITIONVECTOR * getErrors    ( const BFDataGroupId& idDataGroup ) const;
   /**
    * fills into cndVec returns the errors from the last validation of the CBO in dataGroup idDataGroup
    * 
    * @param idDataGroup
    *                 the identifier of the data group which we want to find out
    *                 the errors.
    * @param cndVec   the CONDITIONVECTOR where we want to put the errors
    * @param bRecurse true if contained objects should be checked also.
    *                 Defaults to false.
    * @return 
    */
   SEVERITY getAllErrors ( const BFDataGroupId& idDataGroup, 
                           CONDITIONVECTOR & cndVec, 
                           bool bRecurse = false ) const;

   /**
    * sets the substitution set associated with this field using the ones that are stored in strValues.
    * This operation is done with dataGroup idDataGroup
    * @param fieldId      - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param strValues     - the string containing the new substitution set
   */
   void setFieldAllSubstituteValues( const BFFieldId &fieldId, 
                                     const BFDataGroupId& idDataGroup, 
                                     const DString &strValues );
   /**
    * sets the substitution set associated with this field using the ones that are linked to the
    * useFieldId field. This operation is done with dataGroup idDataGroup
    * @param fieldId       - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param useFieldId    - the identifier of the field whose associated substitution set we want to set into this one
   */
   void setFieldAllSubstituteValues( const BFFieldId &fieldId, 
                                     const BFDataGroupId& idDataGroup, 
                                     const BFFieldId &useFieldId );
   /**
    * sets the substitution set associated with this field using the ones that are linked to the
    * useFieldId field. This operation is done with data group idDataGroup
    * @param fieldId       - the identifier of the field for which we want to set the substitution set
    * @param idDataGroup  - the identifier of the data group for which we want to set the substitution set
    * @param useFieldId    - the identifier of the field whose associated substitution set we want to set into this one
   */
   void setFieldSubstituteValues( const BFFieldId &fieldId, 
                                  const BFDataGroupId& idDataGroup, 
                                  const BFFieldId &useFieldId );

   /**
    * sets the ReadOnly flag of fieldId field. This operation is done with dataGroup idDataGroup
    * @param fieldId       - the identifier of the field for which we want to set the ReadOnly flag 
    * @param idDataGroup  - the identifier of the data group for which we want to set the ReadOnly flag
    * @param readonly      - the new value of the ReadOnly flag 
   */
   void setFieldReadOnly( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool readonly );
   void setFieldUpdated( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bUpdated );
   void setFieldValid( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bValid );

   /**
    * sets the required flag of fieldId field. This operation is done with dataGroup idDataGroup
    * @param fieldId       - the identifier of the field for which we want to set the required flag 
    * @param idDataGroup  - the identifier of the data group for which we want to set the required flag
    * @param requried      - the new value of the required flag 
   */
   void setFieldRequired( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool required );

   /**
    * returns true if dataGroup idDataGroup exists in _dataGroupMap
    * @param idDataGroup  - the identifier of the data group which we want to see if it is registered with this CBO
   */
   bool dataGroupExist  ( const BFDataGroupId& idDataGroup ) const  
   {   
      return(_dataGroupMap.find( idDataGroup ) != _dataGroupMap.end());
   }

   /**
    * retrieves the BFProperties object associated with this lFieldId, idDataGroup combination
    * @param lFieldId      - the identifier of the field for which we want to retrieve the properties
    * @param idDataGroup  - the identifier of the data group for which we want to retrieve the properties
   */
   BFProperties *    getFieldProperties( const BFFieldId &FieldId, const BFDataGroupId& idDataGroup );

   virtual void getTrackActivity(DString& strTrack,DString& strActivity) const {
      strTrack = I_("N");
      strActivity = NULL_STRING;
   }

   void formatField( const BFFieldId &fieldId, DString & strValue, const BFDataGroupId& idDataGroup ) const;
   void unformatField( const BFFieldId &fieldId, DString & strValue, const BFDataGroupId& idDataGroup ) const;

   enum OStream_Flags 
   {
      _rawdata = 0x0001,
      _recurse_objects = 0x0002,
      _allfields = 0x0004
   };


   bool dumpAllFieldsToFile(const DString &dstrFileName, const BFCBO &pbfbase);
   bool hasFieldsUpdateForGroup( long lGroup ) const;

   static void allowThreads( bool bAllow );
   static bool areThreadsAllowed();
   SEVERITY getRequestMaxSeverity() const {return(m_RequestSeverity);}

   DString serialize( const BFDataGroupId& idDataGroup, bool bIncludeType = false ) const;

#ifdef _DEBUG
public:
   bool dump( const char* pszFileName );
   bool dumpTree( const char* pszFileName );

private:
   bool privDump( FILE* pFile, bool bRecurse );
   bool privDumpFields( FILE* pFile );
#endif

protected:

   void cleanBFPropertyRepository();

   virtual bool needsRefresh( const BFDataGroupId& idDataGroup ) const 
   {
      return( hasUpdatedFields( idDataGroup ) );
   }
   /**
    * returns true if the object is being changed - non-recursive
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   bool isObjectDirty (const BFDataGroupId &idDataGroup);

   /**
    * returns true if the field exists in the field map
    * @param fieldId      - the identifier of the field which we want to find if exists in the field map
   */
   bool fieldExists( const BFFieldId &fieldId ) const;
   /**
    * returns the data object that is set int _dataXrefMap with the dstKey key
    * @param dstKey - the key whith which the data object was set in
   */
   BFData * getDataObject( const DString & dstKey );
   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup ){}

   /**
    * virtual function. Should be overwritten in order to avoid the deletion of the object
    * @param strKey        - the string part of the key of the object that we want to find out if it can be deleted
    * @param idDataGroup  - the identifier of the data group with which we want to find out if the object can be deleted
   */
   virtual bool canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
   {
      return(true);
   }
   /**
    * virtual function. Should be overwritten in order to do special processing on deletion
    * @param strKey        - the string part of the key of the object that we want deleted
    * @param idDataGroup  - the identifier of the data group with which we want the object deleted
   */
   virtual SEVERITY doDeleteObject ( const DString & strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed ) { return(NO_CONDITION);}

   /**
    * virtual function. Should be overwritten in order to do CBO level validation
    * @param idDataGroup   - the identifier of the data group with which we want the object validated
    * @param lValidateGroup - the validation group for which we want to validate
   */
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ){ return(NO_CONDITION);}
   /**
    * virtual function. Should be overwritten in order to do CBO level validation
    * @param idDataGroup   - the identifier of the data group with which we want the object validated
   */
   virtual SEVERITY doPreValidateAll( const BFDataGroupId& idDataGroup ){ return(NO_CONDITION);}

   /**
    * clears out the _fieldMap's content. everything that is in dataGroup different than BF::HOST 
    * will be deleted. BF::HOST content will be filled in with NULL pointers
   */
   void clearFieldMap();
   /**
    * virtual function. Should be overwritten in order to have special processing on clearFieldMap
   */
   virtual SEVERITY doPreClearFields(){ return(NO_CONDITION);}

   /**
    * virtual function. Called in refresh processing. Should be overwritten in order to special processing in refresh 
    * when CBOs are reinitialized
   */
   virtual SEVERITY reInit(){ return(NO_CONDITION);}

   /**
    * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
    * filled in into the CBO
    * @param fieldId      - the identifier of the field to be set
    * @param strValue      - the value to be set
    * @param idDataGroup  - the identifier of the data group with which the field should be set
    * @param bFormatted    - strValue is formatted or not
   */
   virtual SEVERITY doPreSetField( const BFFieldId &fieldId, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted ){ return(NO_CONDITION);}
   /**
    * initializes the fields that are marked as INIT_TO_DEFAULT.
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   SEVERITY initDefaults( const BFDataGroupId& idDataGroup );

   bool checkFieldStateFlag( const BFFieldId &ieldId, const BFDataGroupId& idDataGroup, long f );

   /**
    * returns the group flags associated with fieldId, idDataGroup combination
    * @param fieldId     - the identifier of the field for which the group flags should be retrieved 
    * @param idDataGroup - the identifier of the data group for which the group flags should be retrieved 
   */
   long getFieldGroupFlags( const BFFieldId &ieldId, const BFDataGroupId& idDataGroup );
   /**
    * sets the group flags associated with fieldId, idDataGroup combination
    * @param fieldId      - the identifier of the field for which the group flags should be set
    * @param idDataGroup - the identifier of the data group for which the group flags should be set
   */
   void setFieldGroupFlags( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, long lFlags );

   /**
    * virtual function. Should be overwritten in order to support short list/long list concept.
    * If on get field the field is not found in the _fieldMap and in the data object we have an opotunity
    * to do an aditional view cll in order to populate it.
    * @param fieldId      - the identifier of the field which we want to be populated 
    * @param strValue     - string reference where the value of the field should be filed in 
    * @param formattedReturn - do we want the strValue to be formated?
   */
   virtual void doPopulateField( const BFFieldId &fieldId, DString & strValue, bool formattedReturn ){}
   /**
    * does crossEdit processing. It takes all crossEdits in which the field is part and if 
    * they have the IMMEDIATE_VALIDATION flag turned on and all fields that are part of it are valid
    * it tries to validate ti.
    * @param fieldId     - the identifier of the cross edit that we want to be processed 
    * @param idDataGroup - the identifier of the data group with which the cross edit processing should be done
   */
   SEVERITY processCrossEdits( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );

   /**
    * clears out the VALID flag for all the cross edits in which fieldId is part, for the dataGroup idDataGroup
    * @param fieldId      - the identifier of the field for which we want to invalidate the cross edits 
    * @param idDataGroup - the identifier of the data group for which we want to invalidate the cross edits 
   */
   void setCrossEditInvalid( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   /**
    * adds a new crossEdtId fieldId relation.
    * @param crossEdtId   - the identifier of the cross edit to which the field should be added 
    * @param fieldId      - the identifier of the field which we want to add to the cross edit 
   */
   void addCrossEdit(const BFFieldId &crossEdtId, const BFFieldId &fieldId);
   /**
    * returns an BFObjIter on this object with dataGroup idDataGroup
    * @param idDataGroup    - the identifier of the data group for which we want to get an iterator
    * @param matchSubStrings - do we want the iterator to return objects for which the strKey constraint matches substrings of the actual key
   */
   BFObjIter& getObjectIter( const BFDataGroupId& idDataGroup = BF::HOST, bool matchSubStrings = false );

   /**
    * virtual function. Should be overwritten in order to do special processing on new list element creation
    * @param pBase         - here will be filled in the new object
    * @param strKey        - here will be filled in string key
    * @param idDataGroup  - the identifier of the data group with which we want to add a new object
   */
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
   {
      //updatable lists should overwrite this  
      assert( 0 ); 
      return(SEVERE_ERROR);
   }


   /**
    * Multiple data objs can be attached to a CBO (regardless of place in 
    * inheritance heirarchy). The getField methods will traverse the data objects
    * first to last until the field is found or end. The default behavior is to add
    * to the end of the container.  If "bInsertLast=false", the item will be added
    * to the front (checked first).
    * @param data         - data object to be attached
    * @param bBaseDelete  - do we want that the object to take ownership of the data object and to delete it on destruction
    * @param bInsertLast  - do we want that the data object to be inserted last into the _vecData vector
    * @param dstKey       - the key with which we want to add the data object into the _dataXrefMap map
   */
   DString attachDataObject( BFData &data,
                             bool bBaseDelete,
                             bool bInsertLast = true,
                             const DString & dstKey = NULL_STRING );  
   /**
    * clears out from lFlags the bits that are on in nValues
    * @param lFlag   - long where the flags should be cleared out
    * @param nValues - long that keeps the flags that we want to clear out
   */
   void clearFlags(  long &lFlag, 
                     long nValues )
   {
      lFlag &= ~nValues;
   }

   /**
    * it takes in a data object and creates a CBO repeat for all repeats from it.
    *@param data - the data object from which we are taking data from
   */
   SEVERITY createObjectForEachRepeat( const BFData &data );

   /**
    * virtual function. It should be overwriten in order to do special processing on object creation
    * ( in lists when we are adding an existing element )
    * @param data    - the data object from which we are taking data from
    * @param pObjOut - here we are returning the new object
 
   */
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   /**
    * virtual function. It should be overwriten in order to do field validation. It is called by
    * validateField
    * @param fieldId      - the identifier of the field for which we are doing the validation
    * @param strValue     - the value of the field on which the validation is based on
    * @param idDataGroup - the identifier of the data group for which we are doing the validation
   */
   virtual SEVERITY doValidateField( const BFFieldId &fieldId,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup )
   { 
      return(NO_CONDITION); 
   }
   /**
    * clear out the _dataXrefMap and _vecData
   */
   void eraseDataObjectContainers();
   /**
    * clear out _objectMap
   */
   void eraseObjectContainer();
   /**
    * clear out _iteratorsVec
   */
   void eraseIteratorsVector();
   /**
    * adds entries into _fieldMap from pClassFieldInfo array and into _objectMap from pClassObjectInfo array
    * @param lNumberFields    - how many fields do we want to register
    * @param pClassFieldInfo  - array of the fields to be registered
    * @param lNumberObjects   - how many objects do we want to register
    * @param pClassObjectInfo - array of the objects to be registered
   */
   bool registerMemberData( long  lNumberFields,
                            const CLASS_FIELD_INFO * pClassFieldInfo,
                            long  lNumberObjects,
                            const CLASS_OBJECT_INFO * pClassObjectInfo );
   /**
    * sets the values from the data object into the CBO without validation. Data is supposed to be valid
    * @param data          - data object where the data is taken from
    * @param idDataGroup  - the identifier of the data group that is used in setting the data
    * @param bValid        - flag indicating the new value of the VALID flag for the fields that are set 
   */
   SEVERITY setDataNoValidate( const BFData& data, const BFDataGroupId& idDataGroup, bool bValid = false );

   /**
    * sets the field value without validation. It is supposed to be valid
    * @param fieldId      - the identifier of the field which we want to set in
    * @param strValue     - the value that we want to set in
    * @param idDataGroup - the identifier of the data group that is used in setting the field
    * @param lFormatted   - is the value that is set in formatted
    * @param lValid       - flag indicating the new value of the VALID flag for this field
    * @param lSideEffect  - do we want to notify to the registered observers about the field change 
   */
   SEVERITY setFieldNoValidate( const BFFieldId &fieldId,
                                const DString& strValue,
                                const BFDataGroupId& idDataGroup,
                                bool  lFormatted = true, 
                                bool  lValid     = true,
                                bool  lSideEffect = false,
                                bool  bApplyRelChanges = true);

   /**
    * sets the object flags for the object entry whose key matches objKey
    * @param objKey      - the key of the object whose flags we  want to change
    * @param lStateFlags - the new value for the state flags
    * @param lGroupFlags - the new value for the group flags
   */
   virtual void setObjectFlags( const BFObjectKey & objKey, long& lStateFlags , long& lGroupFlags );


   /**
    * Set the NO_BASE_DELETE flag for a contained object to on or off
    * 
    * @param objKey    the object key of the contained object to work with
    * @param bNoDelete true if NO_BASE_DELETE should be set on
    */
   void setNoBaseDelete( const BFObjectKey &objKey, bool bNoDelete );

   /**
    * returns the contained object whose key matches objKey
    * @param objKey          - the key of the object which we want to be found
    * @param lookIntoParents - should we look into the parent data groups
   */
   BFAbstractCBO* findObject( const BFObjectKey &objKey, bool lookIntoParents = true ) const;
   /**
    * clears out the error vector attached to the fieldId idDataGroup combination
    * @param fieldId      - the identifier of the field whose errors we want to be cleared out
    * @param idDataGroup  - the identifier of the data group for which we are clearing out the field's errors
   */
   void clearFieldErrors( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   /**
    * sets the UPDATED flag associated with the fieldId idDataGroup combination
    * @param fieldId      - the identifier of the field whose errors we want the UPDATED flag to be changed
    * @param idDataGroup  - the identifier of the data group for which we want the UPDATED flag to be changed
    * @param bValue        - the new UPDATED flag value
   */
   void setUpdatedFlag( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool bValue );
   /**
    * sets the VALID flag associated with the fieldId idDataGroup combination
    * @param fieldId      - the identifier of the field whose errors we want the VALID flag to be changed
    * @param idDataGroup  - the identifier of the data group for which we want the VALID flag to be changed
    * @param bValue        - the new VALID flag value
   */
   void setValidFlag( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool bValue );
   /**
    * return the value of the VALID flag associated with the fieldId idDataGroup combination
    * @param fieldId       - the identifier of the field that we want to see if is walid 
    * @param idDataGroup  - the identifier of the data group for which we want to see if the field is walid 
   */
   bool isFieldValid( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   /**
    * return the value of the UPDATED flag associated with the fieldId idDataGroup combination
    * @param fieldId       - the identifier of the field that we want to see if is updated
    * @param idDataGroup  - the identifier of the data group for which we want to see if the field is updated
   */
   bool isFieldUpdated( const BFFieldId &ieldId, const BFDataGroupId& idDataGroup );
   bool isFieldRequired( const BFFieldId &ieldId, const BFDataGroupId& idDataGroup );
   bool isFieldReadOnly( const BFFieldId &ieldId, const BFDataGroupId& idDataGroup );
   /**
    * virtual function. It should be overwritten in order to have special processing in a setField after the validation succeeds on in 
    * setFieldNoValidate after the value is stored in the CBO
    * @param fieldId       - the identifier of the field for which we want to apply the related changes
    * @param idDataGroup  - the identifier of the data group for which we want to apply the related field changes
   */
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &fieldId,
                                           const BFDataGroupId& idDataGroup )
   {
      return(NO_CONDITION);
   }

   /**
    * virtual function. It should be overwritten in order to have special processing the commiting process of a 
    * dataGroup
    * @param idDataGroup  - the identifier of the data group that should be commited
   */
   virtual void doCommitDataGroup( const BFDataGroupId& idDataGroup ){} //has to be owerwriten in order to do precommit processing
   /**
    * virtual function. It should be overwritten in order to have special processing the reset process of a 
    * dataGroup
    * @param idDataGroup  - the identifier of the data group that should be reset
   */
   virtual void doReset          ( const BFDataGroupId& idDataGroup ){}//has to be owerwriten in order to have custom reset functionality

   virtual bool doFormatField( const BFFieldId &fieldId, DString & strValue, const BFDataGroupId& idDataGroup ) const { return(false);}

   virtual bool doUnformatField( const BFFieldId &fieldId, DString & strValue, const BFDataGroupId& idDataGroup ) const { return(false);}

   void getFieldConditionVector( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, CONDITIONVECTOR*& pCondVect );
   void setFieldConditionVector( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, CONDITIONVECTOR* pCondVect );


   /**
    * Specify the name of the CBO to write out during CBO serialization.  The
    * candidate name is passed in.
    * 
    * @param dstrCBOName
    *               The candidate name of the CBO.  This is the class name of the CBO.
    * 
    * @return The name of the CBO to write to the output.
    */
   virtual DString serializeCBOName( const DString& dstrCBOName ) const;

   /**
    * Specify the name of the field to write out during CBO serialization.
    * The candidate name is passed in.
    * 
    * @param dstrFieldName
    *               The candidate name of the field.  This is the name of the field as
    *               specified when it was added to the CBO.  If the field is static then
    *               that is name in the data dictionary.  If the field is dynamic then it
    *               is the name which was specified when the FieldId was created.
    * 
    * @return The name of the field to write to the output.
    */
   virtual DString serializeFieldName( const DString& dstrFieldName ) const;

   /**
    * Specify the value of the field to write out during CBO serialization.
    * The candidate value is passed in.
    * 
    * @param idField   The DataDictionary id of the field.
    * @param dstrValue THe candidate value of the field.
    * 
    * @return The value of the field to write to the output.
    */
   virtual DString serializeFieldValue( const BFFieldId& idField, const DString& dstrValue ) const;

protected:
   bool _moreRecordsAvailable; // more records avaialble from the host.

private:
   BFCBO( const BFCBO &copy );
   BFCBO& operator=( const BFCBO& copy );

   void setFieldInvalid ( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   void clearDataGroupErrors( const BFDataGroupId& idDataGroup );

   void serializeCBO( BasicDocument& doc, const BFDataGroupId& idDataGroup, bool bIncludeType ) const;
   void serializeFields( BasicDocument& doc, const BFDataGroupId& idDataGroup, bool bIncludeType ) const;
   void serializeField( BasicDocument& doc, const BFFieldId& idField, const DString& dstrValue, bool bIncludeType ) const;

   typedef std::map< BFFieldId, DString > FieldValuePairsMap;
   void getAllFields( FieldValuePairsMap& fvp, const BFDataGroupId& idDataGroup ) const;

   class FieldInfo;
   class GROUP_INFO;

   typedef struct
   {
      BFData* m_pData;             // Ptr to data obj
      bool m_bBaseDelete;       // if true, base will delete on destruction
   } DATA_XREF_INFO;

   class BFFieldKey 
   {
   public:
      BFFieldKey( const BFDataGroupId& idDataGroup, const BFFieldId &idField ) 
      : idDataGroup_( idDataGroup )
      , idField_( idField ){}

      const BFDataGroupId& getDataGroupId() const { return idDataGroup_; }
      const BFFieldId& getFieldId() const { return idField_; }

   private: 
      const BFDataGroupId idDataGroup_;
      const BFFieldId idField_;
   };

   struct less_BFFieldKey
   {
      bool operator() ( const BFFieldKey &a, const BFFieldKey &b ) const
      {
         if ( a.getDataGroupId() != b.getDataGroupId() )
         {
            return(a.getDataGroupId() < b.getDataGroupId() );
         }
         if ( a.getFieldId() != b.getFieldId() )
         {
            return(a.getFieldId() < b.getFieldId() );
         }
         return(false);
      }
   };

   //typedefs for containers  
   typedef std::map< BFFieldKey, FieldInfo *, less_BFFieldKey >      FIELD_MAP;
   typedef FIELD_MAP::iterator                                       FIELD_MAP_ITER;
#if _MSC_VER >= 1300
   typedef FIELD_MAP::const_iterator                                 FIELD_MAP_CONST_ITER;
#else
   typedef FIELD_MAP::iterator                                       FIELD_MAP_CONST_ITER;
#endif
   typedef FIELD_MAP::value_type                                     FIELD_MAP_VALUE_TYPE;

   typedef std::map< BFFieldId, BFProperties *, std::less<BFFieldId> > BF_PROPERTIES_MAP;
   typedef BF_PROPERTIES_MAP::iterator                               BF_PROPERTIES_MAP_ITER;
#if _MSC_VER >= 1300
   typedef BF_PROPERTIES_MAP::const_iterator                         BF_PROPERTIES_MAP_CONST_ITER;
#else
   typedef BF_PROPERTIES_MAP::iterator                               BF_PROPERTIES_MAP_CONST_ITER;
#endif
   typedef BF_PROPERTIES_MAP::value_type                             BF_PROPERTIES_MAP_VALUE_TYPE;

   class BFPropertyRepository
   {
   public:      
      BFProperties * get( const BFFieldId &fieldId, const BFFieldId &basedOnField = ifds::NullFieldId );
      ~BFPropertyRepository();
      void clean();
   private:
      BF_PROPERTIES_MAP m_map;
      BFCritSec csPropertyMap_;
   };

   typedef std::map< DString, DATA_XREF_INFO * >                     DATA_XREF_MAP;
   typedef DATA_XREF_MAP::iterator                                   DATA_XREF_MAP_ITER;
#if _MSC_VER >= 1300
   typedef DATA_XREF_MAP::const_iterator                             DATA_XREF_MAP_CONST_ITER;
#else
   typedef DATA_XREF_MAP::iterator                                   DATA_XREF_MAP_CONST_ITER;
#endif
   typedef DATA_XREF_MAP::value_type                                 DATA_XREF_MAP_VALUE_TYPE;

   typedef std::map< BFDataGroupId, GROUP_INFO *, std::less<BFDataGroupId> > METAGROUP_MAP;
   typedef METAGROUP_MAP::iterator                                   METAGROUP_MAP_ITER;
#if _MSC_VER >= 1300
   typedef METAGROUP_MAP::const_iterator                             METAGROUP_MAP_CONST_ITER;
#else
   typedef METAGROUP_MAP::iterator                                   METAGROUP_MAP_CONST_ITER;
#endif
   typedef METAGROUP_MAP::value_type                                 METAGROUP_MAP_VALUE_TYPE;



   typedef std::vector<BFData *>                                     DATA_VECTOR;
   typedef DATA_VECTOR::iterator                                     DATA_VECTOR_ITER;
#if _MSC_VER >= 1300
   typedef DATA_VECTOR::const_iterator                               DATA_VECTOR_CONST_ITER;
#else
   typedef DATA_VECTOR::iterator                                     DATA_VECTOR_CONST_ITER;
#endif

   typedef std::vector<BFObjIter *>                                  ITERATORS_VECTOR;
   typedef ITERATORS_VECTOR::iterator                                ITERATORS_VECTOR_ITER;
#if _MSC_VER >= 1300
   typedef ITERATORS_VECTOR::const_iterator                          ITERATORS_VECTOR_CONST_ITER;
#else
   typedef ITERATORS_VECTOR::iterator                                ITERATORS_VECTOR_CONST_ITER;
#endif

   typedef std::multimap< BFFieldId, BFFieldId, std::less<BFFieldId> >  CROSS_EDIT_MAP;
   typedef CROSS_EDIT_MAP::iterator                                     CROSS_EDIT_MAP_ITER;
#if _MSC_VER >= 1300
   typedef CROSS_EDIT_MAP::const_iterator                               CROSS_EDIT_MAP_CONST_ITER;
#else
   typedef CROSS_EDIT_MAP::iterator                                     CROSS_EDIT_MAP_CONST_ITER;
#endif
   typedef CROSS_EDIT_MAP::value_type                                   CROSS_EDIT_MAP_VALUE_TYPE;

   SEVERITY eraseDataGroupFields( const BFDataGroupId& idDataGroup );
   SEVERITY eraseOrphanGroups();

   FieldInfo*      getFieldInfoPointer( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup, bool useParentGroups = true ) const;
   FieldInfo*      prepareFieldInfoPointer( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );
   BFProperties*   prepareFieldProperties( const BFFieldId &fieldId, const BFDataGroupId& idDataGroup );

   bool deleteObject( OBJECT_MAP_ITER & iter, const BFDataGroupId& idDataGroup, bool bRemoveFromMap = false, bool bForce = false )
   { return( BFAbstractCBO::deleteObject( iter, idDataGroup, bRemoveFromMap, bForce ) ); }

   void findDataGroup( METAGROUP_MAP_CONST_ITER & iter, const BFDataGroupId& idDataGroup ) const;

   virtual bool isDummy( const OBJECT_MAP_CONST_ITER & iter ) const;
   void addBFCondition() const;


   FIELD_MAP            _fieldMap;

   DATA_VECTOR          _vecData;
   DATA_XREF_MAP        _dataXrefMap;


   ITERATORS_VECTOR     _iteratorsVec;

   METAGROUP_MAP        _dataGroupMap;

   CROSS_EDIT_MAP       m_crossEditGroupToFieldMap;// pairs CrossEdtId, FieldId 
   CROSS_EDIT_MAP       m_crossEditFieldToGroupMap;// pairs FieldId,    CrossEdtId

   BFObservable *       _BFObservable;
   long                 _lBFStatus;

   int                  _iNextKey;
   int                  _dataMapKey;
   SEVERITY             _objLastValidationError;
   SEVERITY             _objChildrenLastValidationError;

   static BFPropertyRepository          m_bfProprRepository;

   static      bool s_bAllowThreads;
   AsyncRequestor *_asyncRequestor;
   bool _asyncRetrieveDone;

protected:
   class BFCBOEvent
   {
   public:
      BFCBOEvent( bool bManualReset = false, bool bInitialState = false );
      ~BFCBOEvent();
      void wait( DWORD dwMilliseconds );
      void reset();
      void set();
   private:
      BFEvent* _pEvent;
   };

   class BFCBOTypeAttribute : public ElementAttribute
   {
   public:
      BFCBOTypeAttribute( const BFDataFieldProperties* pProp );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

   private:
      DString _type;

   };

   
private:
   mutable BFCBOEvent _receivingData;
   Condition *_lastrequestCondition;
   mutable BFCritSec _baseLock;
   mutable bool _setCondition;
   SEVERITY m_RequestSeverity;

   mutable bool bInDoPopulateField_;

   bool bVersionable_;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/bfcbo.hpp-arc  $
//
//   Rev 1.30   May 29 2012 11:26:52   if991250
//support for cleaning the BFPropertyRepository on language change
//
//   Rev 1.29   Nov 11 2009 09:55:28   popescu
//Static Data project  - added isObjectDirty
//
//   Rev 1.28   05 May 2009 10:07:28   popescu
//Added support for drop down comboxes. The value typed in is appended to the subst set.
//
//   Rev 1.27   24 Jul 2008 12:03:48   popescu
//Incident  1190617 - added flag/method that notifies when an asynch retrieve call is done
//
//   Rev 1.26   Oct 22 2004 08:53:52   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.25   Mar 05 2004 13:27:26   SMITHDAV
//Make changes to support new ElementWriter semantics.
//
//   Rev 1.24   Feb 03 2004 08:53:20   PURDYECH
//Added isVersionable() and setVersionable() to allow a CBO to be marked as non-updateable.
//
//   Rev 1.23   Oct 01 2003 16:52:28   PURDYECH
//Added public member function resetObjectKey.
//
//   Rev 1.22   Sep 09 2003 14:31:48   PURDYECH
//Added needsRefresh virtual function to allow a CBO to indicate if it needs to be refreshed.
//
//   Rev 1.21   May 08 2003 15:31:50   PURDYECH
//Added ability to force a delete of a contained object.
//
//   Rev 1.20   May 01 2003 10:48:14   PURDYECH
//Made BFCBOEvent an inner class of BFCBO.
//Added dump() functions for debugging
//
//   Rev 1.19   Apr 30 2003 09:05:52   PURDYECH
//Sync 1.18.1.1 back to trunk
//
//   Rev 1.18.1.1   Apr 15 2003 14:00:54   PURDYECH
//Documentation fixes.  Signature changes.
//
//   Rev 1.18.1.0   Apr 11 2003 18:04:06   PURDYECH
//temp serialize fixes for KOVACSRO.
//
//   Rev 1.18   Mar 14 2003 08:52:16   PURDYECH
//Added serialize() support for FAST.  It was all there idea!
//Also, fixed a memory leak in reset() (thanks to KOVACSRO)
//
//   Rev 1.17   Mar 12 2003 09:03:28   PURDYECH
//Added isFieldRequired and isFieldValid.
//Added setFieldValid
//Restored get/setFieldGroupFlags
//
//   Rev 1.16   Feb 26 2003 09:41:26   PURDYECH
//Remove updateLevel 
//
//   Rev 1.15   Feb 07 2003 10:45:22   PURDYECH
//Added setFieldUpdated.
//Removed obsolete methods.
//
//   Rev 1.14   Jan 14 2003 11:03:10   PURDYECH
//DataGroupid parentage knowledge
//
//   Rev 1.13   Jan 06 2003 16:40:14   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.10   Nov 14 2002 10:48:54   SMITHDAV
//Sync-up from old source database.
//
//   Rev 1.9   Oct 09 2002 17:40:00   PURDYECH
//New PVCS Database
//
//   Rev 1.8   Sep 17 2002 10:56:16   SMITHDAV
//Remove unused functions.
//
//   Rev 1.7   Sep 03 2002 15:12:06   PURDYECH
//Typo correction.
//
//   Rev 1.6   Sep 03 2002 15:11:06   PURDYECH
//BF_PROPERTIES_MAP now keyed by BFFieldId
//
//   Rev 1.5   Sep 03 2002 11:43:46   PURDYECH
//Merge back to trunk
//
//   Rev 1.4.1.0   Aug 30 2002 17:12:28   SMITHDAV
//Fix iner structs to store BFFieldId copies instead of references.
//
//   Rev 1.4   Aug 29 2002 12:51:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   May 24 2002 11:36:22   PURDYECH
//Changed signature of doPreSetField to include the original formatted state and the ClientLocale
//
//   Rev 1.2   22 May 2002 18:08:44   PURDYECH
//BFData Implementation
//
//   Rev 1.1   22 Mar 2002 15:11:30   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
 * 
 *    Rev 1.48   Feb 28 2002 11:59:48   PURDYECH
 * some lost changes for BFData Phase 1 were reincorporated.
 * 
 *    Rev 1.47   Feb 27 2002 20:42:58   PURDYECH
 * BFAbstractCBO::_hasNonBFHostSetObjects was hidden by BFCBO::_hasNonBFHostSetObjects
 * 
 *    Rev 1.46   Feb 25 2002 18:52:24   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.45   08 Feb 2002 17:05:44   KOVACSRO
 * Added getRequestMaxSeverity().
 *
 *    Rev 1.44   15 Oct 2001 10:59:16   KOVACSRO
 * Added a new param. for setField : bCheckCurrentValue
 * 
 *    Rev 1.43   04 Jul 2001 16:42:50   YINGZ
 * user reset for reset function
 * 
 *    Rev 1.42   Jun 27 2001 20:07:40   PURDYECH
 * Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
 * 
 *    Rev 1.41   Jun 26 2001 19:01:42   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 * 
 *    Rev 1.40   07 Jun 2001 13:15:18   YINGZ
 * add doRollbackDataGroup
 * 
 *    Rev 1.39   11 May 2001 15:37:14   SMITHDAV
 * Sync-up 1.36.1.2
 * 
 *    Rev 1.38   03 May 2001 14:03:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.37   30 Mar 2001 16:35:08   BUZILAMI
 * added doDeleteObject and   the  _hasNonBFHOSTsetObjects flag
 * 
 *    Rev 1.36.1.0   30 Mar 2001 16:34:00   BUZILAMI
 * added doDeleteObject and   the  _hasNonBFHOSTsetObjects flag
 * 
 *    Rev 1.36   Feb 27 2001 12:23:02   PURDYECH
 * Added extra parameter, eBaseDelete, to setObject to allow contained object to *not* be deleted on destruction of containing object.
 * 
 *    Rev 1.35   Jan 31 2001 16:09:36   YINGBAOL
 * add getTrackActivity() method;
 * 
 *    Rev 1.34   Jan 29 2001 12:15:30   HSUCHIN
 * changed Async stuff to support cbo overrides and a couple bug fixes
 * 
 *    Rev 1.33   Jan 17 2001 12:26:52   KOVACSRO
 * Added param bRemoveFromMap to deleteObject().
 * 
 *    Rev 1.32   Jan 17 2001 11:50:04   HSUCHIN
 * changed getField, getObject, Observer etc. to support async request
 * 
 *    Rev 1.31   11 Jan 2001 13:45:58   SMITHDAV
 * Changed signature if AsyncRequestListener::notifyResponse.
 * 
 *    Rev 1.30   11 Jan 2001 12:27:52   SMITHDAV
 * Add support for async requests.
 * 
 *    Rev 1.29   Jan 09 2001 13:17:52   YINGZ
 * delete setValidationMode since it is not needed anymore
 * 
 *    Rev 1.28   Dec 20 2000 14:40:52   YINGZ
 * add setValidationMode for xml
 * 
 *    Rev 1.27   15 Nov 2000 15:27:24   SMITHDAV
 * Added another ReceiveData method to handle responese data creaton and destruction.
 * 
 *    Rev 1.26   10 Nov 2000 09:46:06   PURDYECH
 * Added setNoBaseDelete method
 * 
 *    Rev 1.25   Nov 07 2000 17:31:36   YINGBAOL
 * make _moreRecordsAvailable as protected
 * 
 *    Rev 1.24   Nov 07 2000 16:35:02   VASILEAD
 * Added protected method setClientLocale
 * 
 *    Rev 1.23   30 Oct 2000 11:13:50   SMITHDAV
 * Added protected method doMoreRecordsExist(). Also removed lNoDataCondition parameter from new ReceiveData method.
 * 
 *    Rev 1.22   26 Oct 2000 17:21:54   PURDYECH
 * Changed ReceiveData to accept the "no data" condition to check for (and pop) after data is received.
 * Added code in validateField to ensure that a field with a SubstitutionList has a value from that set.
 * 
 *    Rev 1.21   23 Oct 2000 23:09:54   SMITHDAV
 * Added new ReceivedData overload to work with new BFDataBroker.  Old ReceivedData will be removed when all CBO's are changed to fade this out.
 * 
 *    Rev 1.20   Oct 19 2000 16:19:00   YINGBAOL
 * add hasFieldsUpdateForGroup method
 * 
 *    Rev 1.19   Oct 12 2000 16:39:10   VASILEAD
 * Fixed multiclient locale bugs
 * 
 *    Rev 1.18   Sep 28 2000 14:52:24   YINGBAOL
 * add setFieldConditionVector() and getFieldConditionVector()
 * 
 *    Rev 1.17   Sep 11 2000 14:58:54   VADEANUM
 * Added method dumpAllFieldsToFile(...)
 * 
 *    Rev 1.16   Sep 08 2000 11:24:52   PETOLESC
 * Added methods to help performing validation outside the doValidateField() method.
 * 
 *    Rev 1.15   18 Aug 2000 15:50:28   PURDYECH
 * Added ostream manipulators specifically for BFCBO.
 * 
 *    Rev 1.14   16 Aug 2000 11:51:34   PURDYECH
 * Added bRecurse parameter to getAllErrors.  This defaults to false.  When true it causes all contained objects to be searched also.
 * 
 *    Rev 1.13   08 Aug 2000 10:36:02   PURDYECH
 * Changed reference to ostream to i_ostream.  
 * Made sure that all strings were enclosed by the I_() macro.
 * 
 *    Rev 1.12   03 Aug 2000 18:56:44   MCNABBGL
 * took const off get field
 * 
 *    Rev 1.11   Aug 03 2000 16:41:22   BUZILA
 * locale stuff
 * 
 *    Rev 1.10   Jul 27 2000 17:38:28   BUZILA
 * ClientLocale changes
 * 
 *    Rev 1.9   Jul 21 2000 17:09:36   BUZILA
 * documentation added
 * 
 *    Rev 1.8   May 25 2000 14:06:26   BUZILA
 * added fieldExists function
 * 
 *    Rev 1.7   May 11 2000 16:23:28   BUZILA
 * reorganized static members: m_bfProprRepository;
 * m_globalMetaGroupMap; in order to facilitate synchronization
 * 
 *    Rev 1.6   May 02 2000 14:10:18   BUZILA
 * added key for attachDataObject
 * 
 *    Rev 1.5   Apr 28 2000 18:18:34   BUZILA
 * M3
 * 
 *    Rev 1.4   Apr 07 2000 08:51:28   BUZILA
 * changes setData, setDataNoValidate, setObjectValidationMode
 * 
 *    Rev 1.3   Apr 06 2000 16:39:34   BUZILA
 * added IMMEDIATE_VALIDATION field state flag
 * 
 *    Rev 1.2   Mar 30 2000 09:50:28   BUZILA
 * - introduction of objKey parameter in BFCBO:: ::setObjectFlags
 * - change in crossEdits  validation ( is done when after a setField on a contained one and all  of them are valid )
 * 
 *    Rev 1.1   Mar 02 2000 14:28:48   BUZILA
 * added doInitWithDefaultValues method
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.73   Feb 03 2000 10:12:58   BUZILA
 * added CALCULATED_FIELD flag and hasTransactionUpdates method
 * 
 *    Rev 1.72   Feb 02 2000 14:00:12   BUZILA
 * default dataGroup for BFCBO::getObject taken out
 * 
 *    Rev 1.71   Feb 02 2000 10:33:50   BUZILA
 * we should not send transactions for uncommited data
 * 
 *    Rev 1.70   Feb 01 2000 14:36:16   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.69   Feb 01 2000 13:07:34   BUZILA
 * fixes
 * 
 *    Rev 1.68   Jan 31 2000 13:05:48   BUZILA
 * changes
 * 
 *    Rev 1.67   Jan 23 2000 19:48:46   VASILEAD
 * ?
 * 
 *    Rev 1.66   Jan 23 2000 18:40:58   POPESCUS
 * clearUpdatedFlags should take the datagroupid and misc 
 * 
 *    Rev 1.65   Jan 22 2000 15:18:00   BUZILA
 * added setUpdatedFlag and setValidFlag methods,moved clearFieldErrors to protected section
 * 
 *    Rev 1.64   Jan 21 2000 14:42:22   BUZILA
 * changes related to dummy items
 * 
 *    Rev 1.63   Jan 19 2000 14:07:36   BUZILA
 * changed getMaxValidationSeverityFor*() to be per DataGroup
 * 
 *    Rev 1.62   Jan 19 2000 10:12:02   BUZILA
 * refresh stuf
 * 
 *    Rev 1.61   Jan 16 2000 17:22:08   BUZILA
 * vadid state flags & refresh processing
 * 
 *    Rev 1.60   Jan 13 2000 12:28:40   BUZILA
 * changes in validation mechanism
 * 
 *    Rev 1.59   Jan 12 2000 11:50:18   BUZILA
 * added support for container notification 
 * 
 *    Rev 1.58   Jan 11 2000 15:26:02   BUZILA
 * getNonFieldErrors should return SEVERITY
 * 
 *    Rev 1.57   Jan 10 2000 17:42:56   BUZILA
 * -made BFCBO::registerObserver to return a bool that states if the registration has succeded. 
 * -getFieldProperties returns NULL if the field wasn't registered in CLASS_FIELD_INFO
 * 
 *    Rev 1.56   Jan 08 2000 08:39:56   BUZILA
 * added an option to validateField in order to add validation errors to the conditions container
 * 
 *    Rev 1.55   Jan 07 2000 17:09:32   BUZILA
 * fixes
 * 
 *    Rev 1.54   Jan 06 2000 13:40:08   BUZILA
 * added getNonFieldErrors method
 * 
 *    Rev 1.53   Jan 05 2000 20:12:44   BUZILA
 * fixed, additions...
 * 
 *    Rev 1.52   Jan 04 2000 14:56:16   BUZILA
 * fixes
 * 
 *    Rev 1.51   Jan 04 2000 12:16:22   BUZILA
 * changes...
 * 
 *    Rev 1.50   Dec 22 1999 17:31:12   BUZILA
 * notification for field and properties changes
 * 
 *    Rev 1.49   Dec 21 1999 18:14:46   BUZILA
 * notification changes
 * 
 *    Rev 1.48   Dec 21 1999 12:45:58   BUZILA
 * Validate Field changes
 * 
 *    Rev 1.47   Dec 20 1999 11:06:46   BUZILA
 * added getTopLevelAncestor() method
 * 
 *    Rev 1.46   Dec 19 1999 16:53:32   BUZILA
 * added revision area
 * 
 * 
 */


