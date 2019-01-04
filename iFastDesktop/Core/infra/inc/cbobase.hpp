#ifndef CBOBASE_HPP
#define CBOBASE_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */ 

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef  INCLUDED_OSTREAM
#include <ostream>
#define  INCLUDED_OSTREAM
#endif


// Forward declarations
class CBOBaseImpl;
class Data;
class MathString;
class Updater;

/**@#-*/
using namespace std;
/**@#+*/

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/** 
 * A Base (CBO-Common Business Object) class for 
 * handling Common Business tasks.
 *
 * The CBOBase class contains methods which call the
 * corresponding method in CBOBaseImpl.  A CBOBase object contains
 * a pointer to a CBOBaseImpl object.
 * 
 * CBOBase is the interface class.
 * CBOBaseImpl is the implementation class.
 * 
 * The majority of the methods in CBOBase are known a pass-thru methods.
 * 
 * The CBOBaseImpl class contains methods
 * used for field management, object management and data broker interactions.
 * Any method that takes a strFieldTag as a parameter was not made virtual
 * because of the need to find the subclass id of the implementation class.
 * 
 * Also, the majority of these methods have been
 * overloaded in the common_inter_hpp.hpp module.
 * All of the method overloads in this file take
 * a FIELD enumeration as a parameter instead
 * of a string tag. The common_inter_hpp.hpp header
 * file should be included in all CBOBase derived
 * class header files.  The methods bodies found
 * in the common_inter_cpp.hpp file serve as pass-thru
 * methods to the corresponding methods in the
 * common_impl_cpp.hpp.
 * 
 * common_inter_cpp.hpp is the interface module
 * common_inter_cpp.hpp should be included at the bottom
 * of all CBOBase derived class source(.cpp) files.
 * 
 * common_impl_cpp.hpp is the implementation module
 * 
 * common_impl_hpp.hpp should be included in all
 * CBOBaseImpl derived class header files.
 * 
 * common_impl_cpp.hpp should be included in all
 * CBOBaseImpl derived class source(.cpp) files.
 * 
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * @see CBOBaseImpl
 * @see common_inter_hpp.hpp
 * @see common_inter_cpp.hpp
 * @see common_impl_hpp.hpp
 * @see common_impl_cpp.hpp
 */
class CBOBASE_LINKAGE CBOBase
{
   public:
      enum VALIDATION_MODE { IMMEDIATE,
                             POSTPONED };

      static const int INVALID_FIELD_ID;


   public:
      
      /** 
       * Apply the active field group if one exists.
       * Use this method if working with field
       * group processing e.g. setActiveGroup.
       * By applying the active field group, the current
       * field values(active group) are used to update
       * the original field values( official field group)
       * and all other existing field groups which are not
       * marked as the active field group.  Field values
       * are only replaced if the field value has changed
       * or the field is marked as updated.  The official
       * field group will always be used for updates. So
       * you must apply the active group before updating the
       * host if you want the current field changes to
       * take effect.
       * 
       * @return NO_CONDITION if successful
       * @see setActiveGroup
       * @see removeActiveGroup
       * @see doesGroupExist
       * @see getActiveGroup
       */
      SEVERITY applyActiveGroup();

      /** Constructor */
      CBOBase();

      /** Virtual Destructor */
      virtual ~CBOBase();

      /**
       * Take a "snapshot" of instanceFieldInfo for a potential rollback.
       * This method makes a full and complete copy of anything related
       * to instance fields.
       * Any previous checkpoint will be cleared.
       * 
       * @return true if successful / false if faliure
       * @see rollbackFieldsToCheckpoint()
       */
      bool checkpointFields( void );
     
      /**
       * A pure virtual method.  This method
       * is the interface for a virtual copy
       * operator.  The implementation for
       * this method can be found in 
       * common_inter_cpp.hpp.
       * 
       * @param pSrcObject A CBOBase pointer to be copied
       * @return true if sucessful / false if failure
       */
      virtual bool copy( CBOBase * pSrcObject ) = 0;

      /**
       * Determines if a checkpoint exists
       * @return true if successful / false if failure
       */
      bool doesCheckpointExist();

      /** 
       * Determines if a field exists
       * with the supplied tag in the instancefiedlinfo
       * 
       * @param strFieldTag
       *               Field Tag for an instance field
       *               A field tag is set up in the CLASS_FIELD_INFO
       *               of the derived class.
       * @return true if successful / false if failure
       * @see CLASS_FIELD_INFO
       */
      bool doesFieldTagExist( const DString& strFieldTag ) const;

      /**
       * Checks to see if the specified group exists
       * Use this method if working with group
       * processing e.g. setAcitveGroup, applyActiveGroup etc.
       * If the group exists, somebody must have
       * called setActiveGroup using the specified string
       * label.
       * 
       * @param strGroup A string label attached to a group
       * @return true if the group exists
       *         false if the group does not exist
       * @see setActiveGroup()
       * @see applyActiveGroup()
       * @see removeGroup()
       */
      bool doesGroupExist( const DString &strGroup ) const;
      
      /**
       * DEBUG method used to stream out all variables
       * in the instancefieldinfo( field names, field ids,
       * field flags, etc.)  
       * 
       * This method will also write out information 
       * on the current field group processing being used.
       * 
       * Also it will write out any contained object
       * information.
       * 
       * @param outStream A reference to a stream that will be filled
       *                  with the InstanceFieldInfo data.
       *                  
       *                  You can pass in cout if you want to dump to the
       *                  console
       * @see printValues
       */
      void dumpInstanceFieldInfo( i_ostream& outStream ) const;

      /**
       * Returns the string label value for the
       * currently active field group.
       * Use this method when working with field group
       * processing e.g. setActiveGroup, applyActiveGroup etc.
       * 
       * @param strGroup string reference to be filled with activeGroup name
       * @return NO_CONDITION if successful
       * @see doesGroupExist
       * @see setActiveGroup
       * @see applyActiveGroup
       * @see removeGroup
       */
      SEVERITY getActiveGroup(DString& strGroup) const;
      
      /**
       * This method should be implemented in a
       * derived class.
       * 
       * Use this method if you have a collection of
       * CBOs that you need to extract data from for updates
       * 
       * This method is used during the update process.
       * CBEBaseImpl will call this method after
       * calling the performIsValidForUpdateEdits method
       * and after calling the shouldUpdateBeBuilt method
       * when performing updates.  The method that calls
       * this method is the buildUpdate method
       * in CBEBaseImpl.
       * 
       * @param updater  The updater object being used for the current
       *                 update process.
       * @param strLabel The string label that has been registered
       *                 with CBEBaseImpl
       * @param viewData The data object that will be filled with data
       *                 used for the current update.  This data object
       *                 should be mapped to an updater view .req file.
       * @return NO_CONDITION if successful
       * @see CBEBaseImpl
       * @see _registerView
       * @see buildUpdate
       * @see getData
       */
      virtual SEVERITY getContainedDetailUpdates( const Updater& updater, 
                                                  const DString& strLabel, 
                                                  Data& viewData ) const;
      
      /**
       * Populate a provided data object from the
       * subclasses data objects(before images) and matching instance
       * field info field tags(after image) if requested.
       * 
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
      virtual SEVERITY getData( Data &data,
                                bool fAppendNewTags = false,
                                bool fUseDataObjectOnly = false ) const;

      /**
       * Default behavior for virtual getData that
       * populates the supplied data object.
       * 
       * This method is used during the update process.
       * CBEBaseImpl will call this method after
       * calling the performIsValidForUpdateEdits method
       * and after calling the shouldUpdateBeBuilt method
       * when performing updates.  The method that calls
       * this method is the buildUpdate method
       * in CBEBaseImpl.
       * 
       * The implementation of this method in the derived class
       * may want to get data from contained objects and
       * also set values that can be defaulted(values that
       * may not be in the instancefieldinfo).
       * 
       * @param strLabel A string value that has been registered with
       *                 CBEBaseImpl.  A derived class from CBEBaseImpl
       *                 will register the label by call _registerView
       *                 method. This label is an arbitrary name
       *                 that describes the data that will be updated
       *                 to the host.
       * @param data     The data object that will be filled with data
       *                 used for the current update.  This data object
       *                 should be mapped to an updater view .req file.
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
       * @see CBEBaseImpl
       * @see _registerView
       * @see buildUpdate
       * @see performIsValidForUpdateEdits
       * @see shouldUpdateBeBuilt
       * @see Data
       * @see setElementValue
       */
      virtual SEVERITY getData( const DString& strLabel,
                                Data& data,
                                bool fAppendNewTags = false,
                                bool fUseDataObjectOnly = false ) const;

      /**
       * Gets the instance field value if the fieldTag is found
       * Formatting of the value according to a specified mask
       * will occur upon request. The mask can be specified
       * in a Data object or in the CLASS_FIELD_INFO
       * of a derived class.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param fFormattedReturn
       *               A boolean value, if set to true, we will format
       *               the value using a field mask.  We will first check
       *               to see if a mask is supplied in the CLASS_FIELD_INFO
       *               if one does not exist we will try to format the
       *               string value using the Data object(before image) mask.
       *               It defaults to true.
       *               If it is false, no formatting will occur.
       * @return A string field value of the corresponding field tag
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      DString getField( const DString& strFieldTag, 
                        bool fFormattedReturn = true ) const;
      
      /**
       * Populates a string with the requested field's value if found.
       * Formatting of the value according to a specified mask
       * will occur upon request. The mask can be specified
       * in a Data object or in the CLASS_FIELD_INFO
       * of a derived class.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param strFieldValue
       *               The user supplied string to hold the field value
       * @param fFormattedReturn
       *               A boolean value, if set to true, we will format
       *               the value using a field mask.  We will first check
       *               to see if a mask is supplied in the CLASS_FIELD_INFO
       *               if one does not exist we will try to format the
       *               string value using the Data object(before image) mask.
       *               It defaults to true.
       *               If it is false, no formatting will occur.
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      SEVERITY getField( const DString& strFieldTag, 
                         DString& strFieldValue, 
                         bool fFormattedReturn = true ) const;
       
      /**
       * Populates a MathString with the requested field value
       * if fieldtag is found
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param mstrFieldValue
       *               The user supplied MathString to hold the field value
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see MathString
       * @see setField
       */
      virtual SEVERITY getField( const DString& strFieldTag, 
                                 MathString& mstrFieldValue ) const;

      /**
       * Gets an object's key. A CBO may have a unique
       * string key as an identifier.  A good usage of
       * this key value is in a collection or
       * repository of CBOs.  Use this method after
       * a call to setKey has occurred.
       * 
       * @return A string value of the string key associated with
       *         a CBO.
       * @see setKey
       */
      DString getKey( void ) const;

      /**
       * Static method used to get the value of the updating flag
       * This method is used in conjunction with group field
       * processing.
       * 
       * @return true if we are currently in the middle of
       *         performing the update proces
       *         
       *         false if no update is occurring
       * @see setStaticUpdatingFlag
       */
      static bool getStaticUpdatingFlag();
      
      /**
       * Get the integer value of the update level.
       * The update level is used as a hit counter.
       * The update level is initialized at zero
       * upon object instantiation.
       * As a method is called that updates a CBO
       * the update level will be incremented.
       * The update level gets incremented when the
       * following CBOBase methods are called:
       * _authorizedSetObject
       * setObject
       * refresh
       * applyActiveGroup
       * 
       * Note: setField does not increment the update level
       * 
       * @return A integer value of the update level
       * @see _authorizedSetObject
       * @see setObject
       * @see refresh
       * @see applyActiveGroup
       */
      int getUpdateLevel() const;
      
      /**
       * Return an object's validation mode IMMEDIATE or POSTPONED.
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * If the validation mode is immediate, error conditions
       * will be returned immediately from a call to setField.
       * 
       * If the validation mode is postponed, all conditions will
       * be ignored at the time of a setField call.
       * This means the user intends to collect all conditions
       * at a later time by making a call to the validateAll()
       * method.
       * The methods that check for validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @return An enumeration of the validation mode of the object
       *         (0 = IMMEDIATE or 1 = POSTPONED)
       * @see VALIDATION_MODE
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       */
      VALIDATION_MODE getValidationMode( void ) const;
      
      /**
       * Checks to see if an instance field is marked with INST_FLD_READ_ONLY.
       * If a instance field is marked as INST_FLD_READ_ONLY
       * then the field cannot be set from the user interface
       * without generating a "field read only" error message.
       * A read only field can be set by using one of the _authorizedSet
       * methods from within a derived class.
       * 
       * Fields can initially start out with INST_FLD_READ_ONLY marked
       * based on the field entry in the CLASS_FIELD_INFO.
       * (Use CLASS_FLD_READ_ONLY in the CLASS_FIELD_INFO field entry.
       * 
       * The INST_FLD_READ_ONLY flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_READ_ONLY
       *         false if field is not marked as INST_FLD_READ_ONLY
       * @see CLASS_FIELD_INFO
       * @see FIELD_FLAG
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldReadOnly( const DString& strFieldTag ) const;
            
      /**
       * Checks to see if field has been updated
       * (determined by checking the INST_FLD_UPDATED field flag ).
       * 
       * If an instance field is marked as INST_FLD_UPDATED
       * then the field has been changed from it's original value.
       * 
       * Fields initially start out with the INST_FLD_UPDATED
       * flag turned off.
       * 
       * The methods that will cause this flag to get turn on
       * are:
       * 
       * setField <-- only if all validations pass or in postponed validation mode
       * applyActiveGroup
       * 
       * The INST_FLD_UPDATED flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_UPDATED
       *         false if field is not marked as INST_FLD_UPDATED
       * @see setField
       * @see applyActiveGroup
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldUpdated( const DString& strFieldTag ) const;

      /**
       * Determines if a goup of items (objects & fields),
       * denoted by ulGroupFlag, is valid
       * Spins through all fields and containd objects of the current
       * subclass and checks the INST_FLD_VALIDATED and
       * the INST_OBJ_VALIDATED flags for each one
       * If each field and object has it's validated flag
       * turn on then the group of items(objects & fields)
       * is valid.
       * 
       * Group bit flags are defined in the CLASS_FIELD_INFO
       * and in the CLASS_OBJECT_INFO
       * 
       * @param ulGroupFlag
       *               a bit flag that specifies which group of items
       *               (fields & objects )
       * @return true if all items (fields & objects)
       *         in group are valid
       *         
       *         false if not valid
       * @see CLASS_FIELD_INFO
       * @see CLASS_OBJECT_INFO
       * @see setFieldGroupFlag
       * @see clearFieldGroupFlag
       * @see isFieldGroupFlagSet
       */
      virtual bool isGroupValid( unsigned long ulGroupFlag ) const;
      
      /**
       * This method compares two implementation pointers
       * to see if they are the same.  A CBOBase object
       * contains a pointer to a CBOBaseImpl object.
       * 
       * @param rCompareCBO
       *               The CBOBase object to compare
       * @return true if the implementation pointers are the same
       *         false if the implementation pointers ar different
       */
      bool isImplSame( const CBOBase &rCompareCBO ) const;
      
      /**
       * This method will check to see if a pointer to
       * a CBOBaseImpl object exists.
       * 
       * @return true if CBOBase contains a CBOBaseImpl pointer
       *         false if the CBOBaseImpl pointer is null
       */
      bool isInitialized( void ) const;
      
      /**
       * Checks a flag to see if field group processing
       * is turned on for an instance of a CBO
       * 
       * @return true if field group processing is enabled
       *         false if field group processing is disabled
       * @see setGroupEnabledStatus
       * @see setActiveGroup
       * @see applyActiveGroup
       * @see removeGroup
       */
      bool isObjectGroupEnabled() const;
      
      /**
       * Checks to see if a field of type FLAG has a value
       * of 0 or N
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if the field value is a 0 or N
       *         false if the field value is a 1 or Y
       * @see isOn
       */      
      bool isOff( const DString &strFieldTag) const;

      /**
       * Checks to see if a field of type FLAG has a value
       * of 1 or Y
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if the field value is a 1 or Y
       *         false if the field value is a 0 or N
       * @see isOff
       */
      bool isOn( const DString &strFieldTag) const;
      
      /**
       * This method is usually called by CBEBaseImpl
       * at the start of the update proccess.  CBEBaseImpl
       * must call this method to see if there are any updates
       * to apply to the host.  If there are no updates to
       * apply then he will not continue to build any
       * transactions.
       * 
       * It determines if the object has been updated by
       * performing the following steps.
       * 
       * 1.  Spin through the instancefieldinfo
       * checking if the INST_FLD_UPDATED flag is on
       * for any field.
       * 
       * 2.  Spin through the instanceobjectinfo
       * checking if the INST_OBJ_UPDATED or the
       * INST_OBJ_DELETED flag is on for any object.
       * 
       * 3.  Call the isUpdated method on any contained
       * object(s) if the pointer(s) exist.
       * 
       * @return true if the object or contained objects
       *         have been updated
       *         false if the objects or contained objects
       *         have not been updated
       * @see setField
       * @see setObject
       * @see deleteObject
       * @see CBEBaseImpl
       */
      bool isUpdated( void ) const;

      /**
       * A pure virtual method.  This method
       * is the interface for a virtual copy
       * constructor.  The implementation for
       * this method can be found in 
       * common_inter_cpp.hpp.
       * 
       * @return A CBOBase pointer
       *         null if failure
       */
      virtual CBOBase * makeCopy( void ) const = 0;
      
      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is an interface for modeling
       * one instance of a CBOBaseImpl derived
       * class after another instance of a
       * CBO implementation class
       * 
       * This method is currently not implemented
       * anywhere and will probably be depricated.
       * 
       * @param pCopy  A pointer to an instance of a CBOBaseImpl
       *               derived class
       * @return NO_CONDITION if successful
       */
      SEVERITY modelFrom( const CBOBase *pCopy );

      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If an event(CBE) is removed from an
       * EventUpdateOrder notification can be sent
       * to any contained CBOs associated with the
       * event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnUpdate
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      SEVERITY notifyOnBackout();

      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * is committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @see notifyOnUpdate
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      void notifyOnCommit();

      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * has been collected in an Updater object
       * but not committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      SEVERITY notifyOnUpdate();
      
      /** Assignment Operator */
      CBOBase& operator=( const CBOBase& copyCBOBase );
      
      /**
       * Determine if an object is in a "valid" state.
       * Contained(aggregate) objects are also checked.
       * 
       * This function will check ALL fields and objects
       * adding conditions for each invalid item.
       * NO ATTEMPT to validate "invalid" items is performed.
       * (See validate() for this functionality)
       * 
       * This method looks at each field of the current
       * object and each field of any contained objects
       * to check the INST_FLD_VALIDATED flag. If the
       * individual field's INST_FLD_VALIDATED flag is
       * turned on, then a error condition message will
       * not be generated.  If the indiviual field's
       * INST_FLD_VALIDATED flag is turned off, then
       * an error condition message will be generated
       * and added to a list of conditions.
       * 
       * @return NO_CONDITION if all fields have been validated
       *         SEVERE_ERROR if any one field has not been validated
       * @see validateAll
       * @see validate
       */      
      virtual SEVERITY performIsValidEdits( void ) const;
      
      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is used during the update process.
       * CBEBaseImpl will call this method as one of
       * the first steps in performing updates. This
       * method is called after the shouldUpdateBeBuilt
       * method is called.  The method that calls this
       * method is the buildUpdate method in CBEBaseImpl.
       * 
       * The implementation of this method in the derived class
       * should atleast make a call to validateAll or validate
       * to make sure all of the business data is valid for the
       * update in progress.
       * 
       * If the update should be built, and the business
       * objects pass all validations, then a call to the
       * getData method will be made next.
       * 
       * @param strLabel A string value that has been registered with
       *                 CBEBaseImpl.  A derived class from CBEBaseImpl
       *                 will register the label by call _registerView
       *                 method. This label is an arbitrary name
       *                 that describes the data that will be updated
       *                 to the host.
       * @return NO_CONDITION if successful
       * @see CBEBaseImpl
       * @see _registerView
       * @see buildUpdate
       * @see shouldUpdateBeBuilt
       * @see getData
       * @see validate
       * @see validateAll
       */
      virtual SEVERITY performIsValidForUpdateEdits( const DString& strLabel ) const;

      /**
       * DEBUG method used to write out the intance field name
       * and the current instance field value(only) for the entire
       * instancefieldinfo
       * 
       * @param stream A reference to a stream that will be filled
       *               with the InstanceFieldInfo data.
       *               
       *               You can pass in cout if you want to dump to the
       *               console
       * @see dumpInstanceFieldInfo
       */
      virtual void printValues( i_ostream& stream ) const;
      
      /**
       * A method to be called to increment the updateLevel
       * of the current object.
       * 
       * This method is usually overridden in the derived
       * class to implement code that will grab the latest
       * data for the instancefieldinfo.  The refresh is
       * usually called after updates to the host have
       * occurred.
       * 
       * @return NO_CONDITION if successful
       * @see getUpdateLevel
       */      
      virtual SEVERITY refresh( void );

      /**
       * Removes the specifed group from the field
       * group processing list.
       * Use this method if working with field group
       * processing e.g. setAcitveGroup, applyActiveGroup etc.
       * If the group exists, somebody must have
       * called setActiveGroup using the specified string
       * label.
       * 
       * This method calls the deleteGroup method.
       * 
       * @param strGroup A string label attached to a field group
       * @return NO_CONDITION if successful
       * @see setActiveGroup
       * @see getActiveGroup
       * @see applyActiveGroup
       * @see doesGroupExist
       * @see deleteGroup
       */      
      SEVERITY removeGroup(const DString& strGroup);

      /**
       * Resets the specified field to its default value(if one exists)
       * and resets its corresponding object state flags to
       * the original values.
       * 
       * The reset is based on the values contained in
       * the CLASS_FIELD_INFO.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true for successs
       *         false for failure
       * @see CLASS_FIELD_INFO
       * @see setField
       * @see getField
       */
      bool resetField( const DString &strFieldTag);
      
      /**
       * Resets all fields to their default values(if they exist)
       * and resets their corresponding field state flags to
       * the original values.  All group flags will be cleared.
       * 
       * 
       * The reset is based on the values contained in
       * the CLASS_FIELD_INFO.
       * 
       * @return true for successs
       *         false for failure
       * @see CLASS_FIELD_INFO
       */
      virtual bool resetInstanceFieldInfo( void );
      
      /**
       * Rollback the instancefieldinfo to the previous "snapshot"
       * taken by calling the checkpointFields method.
       * This removes the current instancefieldinfo
       * from existance.
       * 
       * @return true for successs
       *         false for failure
       * @see checkpointFields
       */
      bool rollbackFieldsToCheckpoint( void );
      
      /**
       * Use this method if you want to start working
       * with field group processing e.g. applyActiveGroup.
       * 
       * Field group processing allows you to create labeled
       * "snap shots" of the instancefieldinfo and store them
       * off for the ability of performing a targeted
       * rollback later in processing. The word "group"
       * in field group processing is a misnomer.  You
       * cannot snapshot a group of fields( e.g 5 fields out
       * of 10). You can only snap shot the entire instancefieldinfo
       * (e.g all 10 fields).
       * 
       * @param strGroup A string label to be attached to a field group
       * @return true for successs
       *         false for failure
       * @see removeActiveGroup
       * @see getActiveGroup
       * @see applyActiveGroup
       * @see doesGroupExist
       */
      bool setActiveGroup(const DString& strGroup);
      
      /**
       * Use this method so that a contained(aggregate) CBO
       * can know about it's container CBO( the CBO
       * that contains it as an aggregate ).
       * 
       * @param pContainer A CBOBase pointer that represents the parent object
       *                   of this child object
       */
      void setContainer( CBOBase* pContainer );
      
      /**
       * Populate an instancefieldinfo with the data
       * contained in the provided Data object.
       * This method will try to match each field tag in
       * the Data object with each field tag in
       * the instancefieldinfo.  For each match, the
       * value will get set into the instancefieldinfo.
       * If a field tag is not found, then the value
       * will be ignored.
       * 
       * If the Data object is recognized as containing
       * data that has come from TA2000, then no validations
       * will occur on the data as it is set into the
       * instancefieldinfo.
       * 
       * If the data is not from TA2000, then the data will
       * be validated accordingly.
       * 
       * This method works down the inheritance hierarchy.
       * It start with subclass 0 then goes to 1, 2 etc.
       * (e.g first derivation(0), second derivation(1), third
       * derivation(2) etc. )
       * 
       * CBOBaseImpl as a subclass id of -1
       * 
       * @param data   A Data object that contains business data that may
       *               or may not be from TA2000
       * @return NO_CONDITION if successful
       * @see Data
       * @see getData
       * @see _authorizedSet
       */
      virtual SEVERITY setData( const Data &data );
      
      /**
       * Sets the specified instance field with the
       * supplied string value. This method will call
       * another setField overload to actually perform
       * the validations and storage. It needs to figure
       * out the subclass id we are currently working with
       * first.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value that will be validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see validate
       * @see resetField
       */
      SEVERITY setField( const DString& strFieldTag,
                         const DString& strValue );

      /**
       * Sets the specified instance field with the
       * supplied MathString value.
       * 
       * This method will convert the MathString value to a
       * string and then call another setField overload to
       * actually perform the validations and storage.
       * It needs to figure out the subclass id we are
       * currently working with first.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param mstrFieldValue
       *               A MathString value that will be converted to a
       *               string value, validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see validate
       * @see resetField
       */
      SEVERITY setField( const DString& strFieldTag,
                         const MathString& mstrFieldValue );
      
      /**
       * A static method used to set the updating flag
       * for field group processing. This method is called
       * from the updateNoCommit method in the
       * EventUpdateOrder class. The updating flag
       * is used by the CBOBaseImplStaticVerifier class.
       * If the flag is set to true, then an update is
       * currently being processed. Therefore, in a CBO
       * that is using field group processing, we want to
       * make sure that any methods which access the
       * instancefieldinfo during the update process use
       * the "official field group" instead of the active
       * group for processing. This ensures that we are
       * always using business data that has been applied
       * to the "official field group" for updates.
       * 
       * @param fUpdating true if updates are currently in progress
       *                  false if the update process has finished
       * @see CBOBaseImplStaticVerifier
       * @see EventUpdateOrder
       * @see setActiveGroup
       * @see applyActiveGroup
       * @see removeGroup
       * @see doesGroupExist
       */
      static void setStaticUpdatingFlag(const bool& fUpdating);
      
      /**
       * Set the object's validation mode to IMMEDIATE or POSTPONED
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * 
       * If an objects's validation mode is set to IMMEDIATE,
       * then any "set" method that is called on this object
       * will generate a condition and return it immediately
       * to the user if the data being set is invalid.
       * 
       * If an objects's validation mode is set to POSTPONED,
       * then any data can be set into the object whether the
       * data is invalid or not.  The validateAll method or
       * the validate method should be called at a later
       * time to kick off any validations needed. The
       * only field validations performed by CBOBaseImpl
       * are the read only and required checks.
       * 
       * The methods that check the validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @param validationMode
       *               An enumeration stating which mode is needed for
       *               this object.  Valid values are IMMEDIATE or POSTPONED
       * @see VALIDATION_MODE
       * @see getValidationMode
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       * @see validateAll
       * @see validate
       */
      void setValidationMode( VALIDATION_MODE validationMode );
      
      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is used during the update process.
       * CBEBaseImpl will call this method before
       * calling the performIsValidForUpdateEdits method
       * when performing updates.  The method that calls
       * this method is the buildUpdate method
       * in CBEBaseImpl.
       * 
       * The implementation of this method in the derived class
       * may want to check specific field values to see if the
       * data should be gathered for an update.  If the
       * update should be built, then a call to the
       * performIsValidForUpdateEdits method will be made
       * next.
       * 
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
       * @see _registerView
       * @see buildUpdate
       * @see performIsValidForUpdateEdits
       * @see getData
       */
      virtual bool shouldUpdateBeBuilt( const DString& strLabel ) const;
      
      /**
       * This method validates a collection of values.
       * Each value will be validated individually.
       * No cross validation will be performed.
       * The values will not be stored in the
       * instancefieldinfo.
       * 
       * This method works as an alternative to
       * using rollback functionality, since
       * CBOBaseImpl does not allow you to checkpoint
       * or field group process a group(subset) of fields.
       * 
       * For example, use this method if you want to set
       * a group of fields(e.g. 5 fields out of 10 total
       * in the instancefieldinfo ) only if all values
       * are valid (i.e. all or nothing sets, if one
       * set would fail, don't set any of the fields at all).
       * 
       * If the call to validate is successful then you
       * would probably follow this call with multiple
       * setField calls or a setData call.
       * 
       * @param data   A Data object that holds the values to be validated
       * @return NO_CONDITION if successful
       * @see setField
       * @see setData
       * @see Data
       */
      SEVERITY validate( const Data& data ) const;
      
      /**
       * Attempts to validate the supplied string value.
       * This method validates a single value.
       * The value will not be stored in the
       * instancefieldinfo.
       * 
       * This method works as an alternative to
       * using rollback functionality, since
       * CBOBaseImpl does not allow you to checkpoint
       * one individual field.
       * 
       * If the call to validate is successful then you
       * would probably follow this call with a call
       * to setField.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A potential value for and instance field. The
       *                 value to be validated.
       * @return NO_CONDITION if successful
       */
      SEVERITY validate( const DString& strFieldTag,
                         const DString& strValue );

      /**
       * Attempts to validate the supplied MathString value.
       * This method validates a single value.
       * The value will not be stored in the
       * instancefieldinfo.
       * 
       * This method works as an alternative to
       * using rollback functionality, since
       * CBOBaseImpl does not allow you to checkpoint
       * one individual field.
       * 
       * If the call to validate is successful then you
       * would probably follow this call with a call
       * to setField.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param mstrFieldValue
       *               A potential value for and instance field. The
       *               value to be validated.  The MathString value
       *               will be converted to a string value.
       * @return NO_CONDITION if successful
       * @see MathString
       */
      SEVERITY validate( const DString& strFieldTag,
                         const MathString& mstrFieldValue );
    
      /**
       * Attempt to validate the entire object and
       * return a severity designating the state of
       * this object.
       * 
       * Contained(aggregate) objects are also validated.
       * 
       * This method will check ALL fields and objects
       * adding conditions for each invalid item.
       * If an item (field or object) is not in a
       * valid state, an attempt to validate it will occur.
       * 
       * This method will be called by the CBOBase
       * validateAll method or it can be called directly
       * from a derived class.
       * 
       * @return NO_CONDITION if successful
       * @see performIsValidForUpdateEdits
       * @see setValidationMode
       * @see setField
       * @see setObject
       * @see _authorizedSetObject
       */
      virtual SEVERITY validateAll( void );

      /**
       * This method is used to cross-validate two or more
       * fields.  It will kick off a cross-field validator
       * that is defined in the derived class.
       * 
       * Call this method after setting values for
       * a related group of fields.
       * 
       * Or let validateAll/validate kick off the
       * cross-field validator for you.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return NO_CONDTION if successful
       * @see setField
       * @see setData
       */
      SEVERITY validateField( const DString& strFieldTag );


   protected:
      enum PROTECTED_CREATION
      {
         PROTECTED_CREATE
      };


   protected:
      CBOBase( PROTECTED_CREATION protected_creation );



   protected:
      CBOBaseImpl * _pImpl;


   private:
      CBOBase( const CBOBase& copy );

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
// $Log:   Y:/VCS/iFastAWD/inc/cbobase.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:12   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:41:38   dt14177
// fixed linkage define
// 
//    Rev 1.6   Dec 26 2000 15:35:54   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
//    Rev 1.5   Sep 05 2000 09:38:38   DT29758
// added bool method doesCheckPointExist
// 
//    Rev 1.4   Dec 31 1999 06:27:38   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.2   Nov 23 1999 11:04:26   DT29758
// added ccdoc style comments and minor code
// organization
// 
//    Rev 1.0.1.1   Oct 05 1999 15:55:54   DT29758
// added validate method that validates a 
// Data object
// 
//    Rev 1.0.1.0   Aug 04 1999 17:30:52   DT22388
// Added two new validate() methods
// 
// SEVERITY validate( const string& strFieldTag,
//                                        const string& strValue );
// 
// SEVERITY validate( const string& strFieldTag,
//                                         const MathString& mstrFieldValue );
// and added a 'using $ParentClass$::validate;'
// so that the validate() method that takes
// an enum works with two or more
// derivations from CBOBase.
// 
//    Rev 1.0   Jun 21 1999 17:07:04   DT22388
//  
// 
//    Rev 1.8   May 05 1999 19:36:44   DT22388
// For tracker ticket #8020
// Added the _pContainer and the setContainer()
// method so that a derived class can know
// about his container object.
// 
//    Rev 1.7   Mar 15 1999 14:00:42   DT22388
// Added back the changes made for removing
// any base method that takes an int as a parm
// (i.e. setField() and getField()).
// The previous revision was a rollback of
// these changes. A rollback was peformed
// since the GUI code was not ready for our
// changes.
//
//    Rev 1.6   Mar 05 1999 16:37:40   DT22388
// Rolled back changes to the previous version
// to add back in getField() methods that take
// an int.
//
//    Rev 1.5   Mar 04 1999 17:17:08   DT22388
// Removed method calls to TRACE_METHOD
// and removed pure virtual methods that
// were taking an int as a parameter. The usage
// of an int would not work for CBOs with more
// than one subclass.  Also
// added two new validateObject() methods.
// 
// 
// 
// 
//    Rev 1.4   Jan 14 1999 12:50:36   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.3   Jan 07 1999 09:20:40   DMAL
// added three methods for the 3.4.0.0 code sync
// up, notifiyonbackout, notifyonupdate, 
// notifyoncommit.
//
//    Rev 1.2   Sep 24 1998 13:03:42   dt22388
// Added the key word virtual to the
// getContainedDetailUpdates() method
//
//    Rev 1.0   29 Jul 1998 23:58:10   dt14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.30   Jun 02 1998 16:31:24   djoo
// Added virtual keyword to refresh method.
//
//    Rev 1.29   May 15 1998 10:07:48   djoo
// Enhanced documentation.
//
//    Rev 1.28   May 14 1998 10:15:48   djoo
// Added method doesGroupExist.
//
//    Rev 1.27   Apr 14 1998 11:15:18   djoo
// Added method isImplSame.
//
//    Rev 1.26   Apr 08 1998 14:54:20   djoo
// Added method isInitialized.
//
//    Rev 1.25   Apr 06 1998 15:53:52   djoo
// Removed virtual from modelFrom method.
//
//    Rev 1.24   Apr 06 1998 15:46:50   djoo
// Added method modelFrom.
//
//    Rev 1.23   Mar 27 1998 11:03:32   djoo
// Added isOn and isOff methods.
//
//    Rev 1.22   Mar 24 1998 13:13:38   djoo
// Added first resetField method.
//
//    Rev 1.21   Mar 03 1998 12:19:00   djoo
// Renamed method refreshCBOsByLabel to refresh.
//
//    Rev 1.20   Feb 19 1998 11:09:38   djoo
// Added method isFieldReadOnly.
//
//    Rev 1.19   Feb 09 1998 12:13:24   djoo
// Added method refreshCBOsByLabel.
//
//    Rev 1.18   Jan 17 1998 11:30:30   djoo
// Comment changes.
//
//    Rev 1.17   Jan 09 1998 16:08:58   djoo
// Added method dumpInstanceFieldInfo.
//
//    Rev 1.16   Jan 09 1998 13:50:02   djoo
// Added method getUpdateLevel.
//
//    Rev 1.15   Dec 19 1997 14:38:24   djoo
// Added methods getStaticUpdatingFlag, setStaticUpdatingFlag, getActiveGroup, setActiveGroup,
// applyActiveGroup, getActiveGroup, removeGroup and isObjectGroupEnabled.
//
//    Rev 1.14   Dec 09 1997 08:42:20   djoo
// Added method isFieldUpdated.
//
//    Rev 1.13   Dec 05 1997 08:40:40   djoo
// Added checkpointFields & rollbackFieldsToCheckpoint.
//
//    Rev 1.12   Nov 20 1997 13:48:22   djoo
// Added method validateField.
//
//    Rev 1.11   Nov 11 1997 10:49:50   djoo
// Defaulted formattedReturn flag on getFields to true.
//
//    Rev 1.10   Nov 11 1997 08:24:18   djoo
// Added Redundant Include Guards, import/export protection and field formatting.
//
//    Rev 1.9   Sep 02 1997 16:06:22   djoo
// Intermediate Check-in for CBO8. (Condition Manager enhancements)
//
//    Rev 1.8   Aug 26 1997 13:17:58   djoo
// Forget #include "ConditionManager.hpp"
//
//    Rev 1.7   Aug 26 1997 12:50:18   djoo
// Initial SEVERITY enhancements.
//
//    Rev 1.6   16 Aug 1997 12:01:34   dmal
//
//
//    Rev 1.4   Jul 10 1997 17:58:14   DPQD
// Moved EOF marker past preprocessor directive line.
//
//    Rev 1.3   Jul 10 1997 15:46:10   DPQD
// Added new methods to support MathString.  New methods isValid
// and resetInstanceFieldInfo.
//
// Removed ErrorList.
//
//
//
//    Rev 1.2   24 Jun 1997 14:49:34   dmal
// Changed isValidUpdate to isValidForUpdate
// also removed the if statement on setElementvalue
// in getData.  DJBH.
//
//


#endif

