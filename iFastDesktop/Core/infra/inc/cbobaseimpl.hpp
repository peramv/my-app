#ifndef CBOBASEIMPL_HPP
#define CBOBASEIMPL_HPP

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

#ifndef  INCLUDED_MAP
#include <map>
#define  INCLUDED_MAP
#endif

#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VECTOR
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef  COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CBOINSTANCEFIELDINFO_HPP
#include "cboinstancefieldinfo.hpp"
#endif

#ifndef CBOINSTANCEOBJECTINFO_HPP
#include "cboinstanceobjectinfo.hpp"
#endif

#ifndef  OSTREAM
#include <ostream>
#endif

#ifndef  COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

/**@#-*/
using namespace std;
/**@#+*/


// forward declarations
class CBOBase;
class MathString;
class Updater;
class Data;

// FLG_NONE definition
const unsigned long FLG_NONE = 0x0000;

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * A base (CBO-Common Business Object) class for
 * handling common business tasks.
 * 
 * The CBOBaseImpl class contains methods
 * used for field management, object management
 * and data broker interactions
 * 
 * Any method that takes a strFieldTag(unless a subclass id is specified)
 * as a parameter was not made virtual
 * because of the need to find the subclass id of the implementation class.
 * 
 * Also, the majority of these methods have been
 * overloaded or overridden in the common_impl_hpp.hpp module.
 * All of the method overloads in this file take
 * a FIELD enumeration as a parameter instead
 * of a string tag. The methods bodies found
 * in the common_impl_cpp.hpp file serve as pass-thru
 * methods for figuring out the subclass id.
 * 
 * common_inter_cpp.hpp is the interface module
 * common_impl_cpp.hpp is the implementation module
 * 
 * common_impl_hpp.hpp should be included in all
 * CBOBaseImpl derived class header files.
 * 
 * common_impl_cpp.hpp should be included in all
 * CBOBaseImpl derived class source(.cpp) files.
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * @see CBOBase
 * @see common_impl_hpp.hpp
 * @see common_impl_cpp.hpp
 */
class CBOBASE_LINKAGE CBOBaseImpl // : public Observer, public Subject
{
   public:
      enum VALIDATION_MODE { IMMEDIATE,
                             POSTPONED };


      enum DATA_TYPE { ALPHANUMERIC,
                       INTEGER,
                       DECIMAL,
                       DOLLAR_AMOUNT,
                       NUMBER_SHARES,
                       FLAG,
                       PERCENT };

      enum FIELD_ID { INVALID_FIELD_ID = -1 };
      enum SUBCLASS { SUBCLASS_ID = -1 };

      // Class-level field flags
      enum CLASS_FIELD_TYPE { CLASS_FLD_NONE        = 0x0000,
                              CLASS_FLD_READ_ONLY   = 0x0001,
                              CLASS_FLD_REQUIRED    = 0x0002,
                              CLASS_FLD_CROSS_FIELD = 0x0004  };


      // Class-level object flags
      enum CLASS_OBJECT_TYPE { CLASS_OBJ_NONE                  = 0x0000,
                               CLASS_OBJ_READ_ONLY             = 0x0001,
                               CLASS_OBJ_REQUIRED              = 0x0002,
                               CLASS_OBJ_NO_BASE_DELETE        = 0x0004,
                               CLASS_OBJ_COPY_ONLY             = 0x0008,
                               CLASS_OBJ_PRIVATE_USE           = 0x0010,
                               CLASS_OBJ_PTR_ACCESS_ONLY       = 0x0020,
                               CLASS_OBJ_ALLOW_DELETE_OBJECT   = 0x0040  };


      // Instance-level field flags that can vary among fields and among
      // object instances
      enum FIELD_FLAG { INST_FLD_VALIDATED,
                        INST_FLD_INITIALIZED,
                        INST_FLD_UPDATED,
                        INST_FLD_REQUIRED,
                        INST_FLD_READ_ONLY,
                        INST_FLD_TA2000_ORIGIN,
                        INST_FLD_CROSS_FIELD,
                        MAX_FIELD_FLAGS };

      // Instance-level object flags that can vary among object instances
      enum OBJECT_FLAG { INST_OBJ_VALIDATED,
                         INST_OBJ_INITIALIZED,
                         INST_OBJ_UPDATED,
                         INST_OBJ_READ_ONLY,
                         INST_OBJ_TA2000_ORIGIN,
                         INST_OBJ_COPY_ONLY,
                         INST_OBJ_REQUIRED,
                         INST_OBJ_PRIVATE_USE,
                         INST_OBJ_NO_BASE_DELETE,
                         INST_OBJ_PTR_ACCESS_ONLY,
                         INST_OBJ_ALLOW_DELETE_OBJECT,
                         INST_OBJ_DELETED,
                         MAX_OBJECT_FLAGS };



      typedef struct
      {
         int             nFieldId;           // Unique numeric field identifier
         const I_CHAR *  pcszTag;            // Unique DString field identifier
         const I_CHAR *  pcszName;           // Field name
         int             nMaxLength;         // Maximum length of field value
         unsigned long   ulFlags;            // Bit flags
         unsigned long   ulGroupFlags;       // Group bit flags
         DATA_TYPE       dataType;           // What kind of data is the field?
         const I_CHAR *  pcszDefault;        // Default value
         const I_CHAR *  pcszMask;           // Field Mask
         const I_CHAR *  pcszValidValues;    // Valid values
      } CLASS_FIELD_INFO;



      typedef struct
      {
         int             nObjectId;          // Unique numeric object identifier
         const I_CHAR *  pcszClassName;      // Name of class
         unsigned long   ulFlags;            // Bit flags
         unsigned long   ulGroupFlags;       // Group bit flags
      } CLASS_OBJECT_INFO;

   // Public methods
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

      /** Virtual Destructor */
      virtual ~CBOBaseImpl();

      /**
       * Take a "snapshot" of instanceFieldInfo for a potential rollback.
       * This method makes a full and complete copy of anything related to instance fields.
       * Any previous checkpoint will be cleared.
       * 
       * @return true if successful / false if failure
       * @see rollbackFieldsToCheckpoint()
       */
      bool checkpointFields();
      
      /**
       * Deletes a contained object that has been registered
       * with CBOBase.
       * Use this method after a call to the setObject
       * or _authorizedSetObject methods have been called.
       * This method calls a notifyOnDeleteObject() method
       * which must be overridden by the derived class.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return NO_CONDITION if successful
       * @see CLASS_OBJECT_INFO
       * @see notifyOnDeleteObject
       * @see setObject
       * @see getObject
       * @see doesObjectExist
       */
      SEVERITY deleteObject( unsigned short usSubclassId,
                             int nObjectId );
      
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
       * processing e.g. setActiveGroup, applyActiveGroup etc.
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
       * Determines if CBOBase is responsible for deleteing
       * the aggregate object.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return true if successful / false if failure
       * @see CLASS_OBJECT_INFO
       * @see setObject
       * @see deleteObject
       * @see getObject
       * @see doesObjectExist
       */
      bool doesOwnObject( unsigned short usSubclassId,
                          int nObjectId ) const;

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
      void dumpInstanceFieldInfo( i_ostream &outStream ) const;
      
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
       * Provides a const CBOBase pointer if allowed by object flags
       * If the Contained CBO is marked as INST_OBJ_PRIVATE_USE
       * in the class object info then this method cannot
       * be used to retrieve the object. You must use one
       * of the other available getObject methods.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return const CBOBase
       * @see CLASS_OBJECT_INFO
       * @see getObject
       * @see setObject
       * @see doesObjectExist
       */
      virtual const CBOBase * getConstObject( unsigned short usSubclassId,
                                              int nObjectId ) const;

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
      virtual SEVERITY getContainedDetailUpdates( const Updater& updater, const DString& strLabel, Data& viewData ) const;

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
       * Populates a string with the requested field's value if found.
       * Formatting of the value according to a specified mask
       * will occur upon request. The mask can be specified
       * in a Data object or in the CLASS_FIELD_INFO
       * of a derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param str      The user supplied string to hold the field value
       * @param formattedReturn
       *                 A boolean value, if set to true, we will format
       *                 the value using a field mask.  We will first check
       *                 to see if a mask is supplied in the CLASS_FIELD_INFO
       *                 if one does not exist we will try to format the
       *                 string value using the Data object(before image) mask.
       *                 It defaults to false.
       *                 If it is false, no formatting will occur.
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      virtual SEVERITY getField( unsigned short usSubclassId,
                             int nFieldId,
                             DString& str,
                             bool formattedReturn = false ) const;

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
       *               It defaults to false.
       *               If it is false, no formatting will occur.
       * @return A string field value of the corresponding field tag
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      virtual DString getField( const DString& strFieldTag,
                               bool fFormattedReturn = false ) const;

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
       *               It defaults to false.
       *               If it is false, no formatting will occur.
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      virtual SEVERITY getField( const DString& strFieldTag,
                             DString& strFieldValue,
                             bool fFormattedReturn = false ) const;

      /**
       * Populates a MathString with the requested field if found.
       * Converts the string value to a MathString value behind
       * the scenes.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param mstrFieldValue
       *                 The user supplied MathString to hold the field value
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see MathString
       * @see setField
       */
      virtual SEVERITY getField( unsigned short usSubclassId,
                             int nFieldId,
                             MathString& mstrFieldValue ) const;

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
       * Gets the field name(description) for the requested instance field.
       * The field name(description) is defined in the
       * CLASS_FIELD_INFO of the derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return A string value of the field name(description)
       * @see CLASS_FIELD_INFO
       */
      DString getFieldName( unsigned short usSubclassId,
                           int nFieldId ) const;

      /**
       * Gets the unique string field identifier for the requested instance field.
       * The unique string field identifier is defined in the
       * CLASS_FIELD_INFO of the derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return A string value of the unique string field identifier
       * @see CLASS_FIELD_INFO
       */
      DString getFieldTag( unsigned short usSubclassId,
                          int nFieldId ) const;

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
      virtual DString getKey( void ) const;

      /**
       * Gets the maximum length of an instance field.
       * The maximum length of a field is defined in the
       * CLASS_FIELD_INFO of a derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return An integer value of the max field length
       * @see CLASS_FIELD_INFO
       */
      virtual int getMaxLength( unsigned short usSubclassId,
                                int nFieldId ) const;

      /**
       * Provides a CBOBase pointer if allowed by object flags
       * If the Contained CBO is marked as one or more of the following
       * INST_OBJ_PRIVATE_USE
       * INST_OBJ_COPY_ONLY
       * in the CLASS_OBJECT_INFO then this method cannot
       * be used to retrieve the object. You must use one
       * of the other available getObject methods.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return A CBOBase * if successful
       *         A NULL pointer if failure
       *         A NULL pointer if object does not exist
       * @see CLASS_OBJECT_INFO
       * @see setObject
       * @see deleteObject
       * @see doesOwnObject
       * @see doesObjectExist
       */
      virtual CBOBase * getObject( unsigned short usSubclassId,
                                   int nObjectId );

      /**
       * Provide a full copy of the requested object to the supplied object
       * if object flags allow it and if the supplied object is of a correct type.
       * If the Contained CBO is marked as one or more of the following
       * INST_OBJ_PRIVATE_USE
       * INST_OBJ_PTR_ACCESS_ONLY
       * in the CLASS_OBJECT_INFO then this method cannot
       * be used to retrieve the object. You must use one
       * of the other available getObject methods.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param cboObject The CBO to hold a full copy of the requested object
       * @return NO_CONDITION if successful
       * @see CLASS_OBJECT_INFO
       * @see setObject
       * @see deleteObject
       * @see doesOwnObject
       * @see doesObjectExist
       */
      virtual SEVERITY getObject( unsigned short usSubclassId,
                          int nObjectId,
                          CBOBase& cboObject );

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
       * Checks to see if a FIELD_FLAG is set(on) for the
       * specified field in the specified subclass.
       * 
       * Field flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * Field flags can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param fieldFlag A FIELD_FLAG enumeration value to check if off or on
       * @param nFieldId  A unique numeric indentifier for the registered field
       *                  used to index into the instancefieldinfo.
       *                  The indentifier for a field is set up in
       *                  the CLASS_FIELD_INFO.
       * @return true if the specified FIELD_FLAG is on
       *         false if the specified FIELD_FLAG is off
       * @see FIELD_FLAG
       * @see CLASS_FIELD_INFO
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see _switchAllFieldFlags
       * @see _setAllFieldFlags
       * @see _clearAllFieldFlags
       * @see resetField
       * @see resetInstanceFieldInfo
       */
      bool isFieldFlagSet( unsigned short usSubclassId,
                           FIELD_FLAG fieldFlag,
                           int nFieldId ) const;

      /**
       * Checks to see if a field group flag is set(on) for the
       * specified subclass.
       * 
       * Field group flags are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param ulGroupFlag
       *               a bit flag that specifies which group field flag
       *               to check
       * @return true if the field group flag is on
       *         false if the field group flag is off
       * @see CLASS_FIELD_INFO
       * @see setFieldGroupFlag
       * @see clear FieldGroupFlag
       * @see isGroupValid
       */
      bool isFieldGroupFlagSet( unsigned short usSubclassId,
                           unsigned long ulGroupFlag ) const;

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
      bool isFieldReadOnly(const DString& strFieldTag) const;

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
      bool isFieldUpdated(const DString& strFieldTag) const;

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
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return 
       * @see setField
       * @see applyActiveGroup
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldUpdated( unsigned short usSubclassId,
                           int nFieldId ) const;

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
       * Checks to see if a OBJECT_FLAG is set(on) for the
       * specified object in the specified subclass.
       * 
       * Object flags for a specific contained object are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * Object flags can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param objectFlag An OBJECT_FLAG enumeration value to check if off or on
       * @param nObjectId  A unique numeric indentifier for the registered contained CBO
       *                   used to index into the instanceobjectinfo.
       *                   The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                   of the derived class.
       * @return true if the specified OBJECT_FLAG is on
       *         false if the specified OBJECT_FLAG is off
       * @see OBJECT_FLAG
       * @see CLASS_OBJECT_INFO
       * @see setObjectFlag
       * @see clearObjectFlag
       * @see _switchAllObjectFlags
       * @see _setAllObjectFlags
       * @see resetInstanceObjectInfo
       */
      bool isObjectFlagSet( unsigned short usSubclassId,
                             OBJECT_FLAG objectFlag,
                             int nObjectId ) const;

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
       * Checks to see if an object group flag is set(on) for the
       * specified subclass.
       * 
       * Object group flags are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param ulGroupFlag
       *               a bit flag that specifies which group field flag
       * @return true if the object group flag is on
       *         false if the object group flag is off
       * @see CLASS_OBJECT_INFO
       * @see isGroupValid
       * @see setObjectGroupFlag
       * @see clearObjectGroupFlag
       */
      bool isObjectGroupFlagSet( unsigned short usSubclassId,
                                  unsigned long ulGroupFlag ) const;

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
      bool isOff(const DString& strFieldTag ) const;

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
      bool isOn( const DString& strFieldTag ) const;

      /**
       * This method should be used by classes derived from
       * CBOBaseImpl only.
       * 
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
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_READ_ONLY
       *         false if field is not marked as INST_FLD_READ_ONLY
       * @see isFieldReadOnly
       */
      virtual bool isReadOnly( unsigned short usSubclassId,
                               int nFieldId ) const;

      /**
       * This method should be used by classes derived from
       * CBOBaseImpl only.
       * 
       * Checks to see if an instance field is marked with INST_FLD_REQUIRED.
       * If a instance field is marked as INST_FLD_REQUIRED
       * then the field must be set with a value.
       * If a required field does not have a value
       * when the validateAll method is called, a
       * "field required" error message will be generated.
       * 
       * Fields can initially start out with INST_FLD_REQUIRED marked
       * based on the field entry in the CLASS_FIELD_INFO.
       * (Use CLASS_FLD_REQUIRED in the CLASS_FIELD_INFO field entry.
       * 
       * The INST_FLD_REQUIRED flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_REQUIRED
       *         false if field is not marked as INST_FLD_REQUIRED
       * @see CLASS_FIELD_INFO
       * @see FIELD_FLAG
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      virtual bool isRequired( unsigned short usSubclassId,
                               int nFieldId ) const;

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
      virtual bool isUpdated( void ) const;

      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is called by isValidType which in turn
       * is called by  setObject and _authorizedSetObject
       * to make sure the passed in object is of the
       * type specfied in the CLASS_OBJECT_INFO for the
       * specfied object id.
       * 
       * A derived class should implement this method
       * using a switch statement cased on the object id.
       * 
       * Within the derived class implementation, for each
       * case, the pointer to the CBO should be
       * dynamically casted to the specified type. If the
       * dynanmic cast fails, then the caller did not pass
       * in a CBO of the specfied type based on the object id.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param pObject   A pointer to a CBOBase derived object
       * @return true if the passed in CBO is of the correct type
       *         based on the object id
       *         false if the passed in  CBO is not of the correct type
       *         based on the object id
       * @see isValidType
       * @see setObject
       * @see _authorizedSetObject
       */
      virtual bool isValidContainedObjectDerivation( unsigned short usSubclassId,
                                                     int nObjectId,
                                                     CBOBase * pObject ) const;

      /**
       * This method is called by setObject and _authorizedSetObject
       * to make sure the passed in object is of the
       * type specfied in the CLASS_OBJECT_INFO for the
       * specfied object id.  This method calls the
       * isValidContainedObjectDerivation method which
       * should be implemented in the derived class.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param pObject   A pointer to a CBOBase derived object
       * @return true if the passed in CBO is of the correct type
       *         based on the object id
       *         false if the passed in  CBO is not of the correct type
       *         based on the object id
       * @see isValidContainedObjectDerivation
       * @see setObject
       * @see _authorizedSetObject
       */
      bool isValidType( unsigned short usSubclassId,
                        int nObjectId,
                        CBOBase * pObject ) const;

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
      virtual SEVERITY modelFrom( const CBOBaseImpl *pCopy );

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
      virtual SEVERITY notifyOnBackout();

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
      virtual void notifyOnCommit();
      
      /**
       * This method should be implemented in a
       * derived class.
       * 
       * This method is called by the
       * deleteObject method.  This method gives the
       * derived object a last chance to grab information
       * out of a contained object that is in the process
       * of being deleted.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return NO_CONDITION if successful
       * @see deleteObject
       * @see setObject
       * @see getObject
       * @see doesObjectExist
       */
      virtual SEVERITY notifyOnDeleteObject( unsigned short usSubclassId,
                                             int nObjectId );

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
      virtual SEVERITY notifyOnUpdate();

      /** Assignment Operator */
      CBOBaseImpl& operator=( const CBOBaseImpl& copy );

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
       * This method should only be called from a derived
       * class.
       * 
       * Resets the specified field to its default value(if one exists)
       * and resets its corresponding object state flags to
       * the original values.
       * 
       * The reset is based on the values contained in
       * the CLASS_FIELD_INFO.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return true for successs
       *         false for failure
       * @see CLASS_FIELD_INFO
       * @see setField
       * @see getField
       */
      bool resetField( unsigned short usSubclassId,
                       int nFieldId );

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
       * Resets all objects to their orginal state
       * and resets their corresponding object state flags to
       * the original values.  All group flags will be cleared.
       * 
       * 
       * The reset is based on the values contained in
       * the CLASS_OBJECT_INFO.
       * 
       * @return true for successs
       *         false for failure
       * @see CLASS_OBJECT_INFO
       */
      virtual bool resetInstanceObjectInfo( void );

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
      bool rollbackFieldsToCheckpoint();

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
       * the instnacefieldinfo.  For each match, the
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
       * Sets the specified instance field with the supplied string value.
       * This method will call a validator if it exists in
       * the derived class.  This method will not return
       * conditions if the object is set to postponed
       * validation mode.  If setField fails the value
       * will not be accepted and not stored in the instancefieldinfo.
       * Any previous value will remain in storage.
       * 
       * 
       * The reasons why this method could fail are:
       * 
       * 1. The instance field is marked as INST_FLD_READ_ONLY
       * 
       * 2. The instance field is marked as INST_FLD_REQUIRED
       * and a null value or spaces was passed in
       * 
       * 3. The maximum length is exceeded for instance field
       * 
       * 4. The type of the passed-in value is not valid with
       * the instancefieldinfo type. e.g. an alpha value cannot
       * set into a numeric typed field.
       * 
       * 5. The field does not pass business validations as
       * specified in the derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value that will be validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see resetField
       * @see validate
       */
      virtual SEVERITY setField( unsigned short usSubclassId,
                                 int nFieldId,
                                 const DString& strValue );

      /**
       * Sets the specified instance field with the
       * supplied MathString value. This method
       * will convert the MathString to a string
       * and call another setField overload to
       * actually perform the validations and storage.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param mstrFieldValue
       *                 A MathString value that will be converted to a
       *                 string value, validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see validate
       * @see resetField
       */
      virtual SEVERITY setField( unsigned short usSubclassId,
                                 int nFieldId,
                                 const MathString& mstrFieldValue );

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
       * Sets a pointer to the interface class.
       * A CBOBaseImpl derived class may need know
       * about it's CBOBase derived(interface) class.
       * 
       * @param pInterface A CBOBase pointer that represents the interface class
       *                   to the current implementation class
       * @param fDeleteOnDestruction
       *                   A boolean value that tells CBOBaseImpl to delete
       *                   the interface pointer if true
       *                   CBOBaseImpl will not delete the pointer if false.
       */
      void setInterfacePointer( CBOBase* pInterface, bool fDeleteOnDestruction );

      /**
       * Sets an object's key. A CBO may have a unique
       * string key as an identifier.  A good usage of
       * this key value is in a collection or
       * repository of CBOs.
       * 
       * @param strKey A unique string value that will be associated with
       *               the current CBO.
       * @see getKey
       */
      virtual void setKey( const DString& strKey );

      /**
       * Sets the supplied CBOBase pointer into the
       * instanceobjectinfo to create an aggregate
       * relationship by making a full copy
       * of the object. The default behavior is that
       * CBOBaseImpl owns the copy of the CBO and thus
       * will delete it on destruction.
       * 
       * You can tell CBOBaseImpl not to delete it by
       * turning the CLASS_OBJ_NO_BASE_DELETE flag
       * on in the CLASS_FIELD_INFO.
       * 
       * The INST_OBJ_NO_BASE_DELETE flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * This method will call the validateAll method
       * and the validateObject method
       * 
       * This method will also call the isValidType method
       * to make sure the type of the CBOBase pointer matches
       * the corresponding type as specified by object id.
       * 
       * The type can be found in the CLASS_OBJECT_INFO
       * of the derived class.
       * 
       * This method will also increment the _updateLevel.
       * 
       * The reason why this method could fail are:
       * 
       * 1.  The object flag INST_OBJ_PTR_ACCESS_ONLY is turned on
       * for the object.
       * 
       * 2.  The object flag INST_OBJ_READ_ONLY is turned on
       * for the object.
       * 
       * 3.  The object flag INST_OBJ_PRIVATE_USE is turned on
       * for the object.
       * 
       * 4.  The object flag INST_OBJ_REQUIRED is turned on
       * for the object and the CBOBase pointer passed in is null.
       * 
       * 5.  The call to isValidType failed
       * 
       * 6.  The copy process fails. This method makes a full
       * copy of the passed in CBO.
       * 
       * 7.  The object is not in a valid state according to
       * the specfied business rules in the derived class
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param pObject   A CBOBase pointer that will be validated and stored
       * @param fDeleteOnFailure
       *                  A boolean value that, if true, tells CBOBaseImpl to delete
       *                  the CBOBase pointer if the setObject call fails.
       *                  
       *                  CBOBaseImpl will not delete the pointer if false.
       *                  
       *                  This flag defaults to false.
       * @return NO_CONDITION if successful
       * @see CLASS_OBJECT_INFO
       * @see getObject
       * @see deleteObject
       * @see doesObjectExist
       * @see doesOwnObject
       */
      virtual SEVERITY setObject( unsigned short usSubclassId,
                                  int nObjectId,
                                  CBOBase * pObject,
                                  bool fDeleteOnFailure = false );

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
       * The implementation of this method in the dirived class
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
      virtual SEVERITY validate( void );

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
      SEVERITY validate( const Data& data );

      /**
       * Attempts to validate an individual instance field value.
       * This method is implemented in the
       * common_impl_cpp.hpp.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param bValidatorCallOnly
       *                 This method may be called from validateField
       *                 for cross field validation, so we do not want
       *                 to perform our normal individual field validate()
       *                 method, we only want to call the validator defined
       *                 in the derived class to perform the cross-field
       *                 validation.
       *                 
       * @return NO_CONDITION if successful
       */
      virtual SEVERITY validate( unsigned short usSubclassId,
                                 int nFieldId, bool bValidatorCallOnly=false );

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
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The string value to be validated
       * @param fRemoveFormat
       *                 A boolean value, if true CBOBaseImpl
       *                 will un-format the string value
       *                 according to any available masking values.
       *                 If false, the format will remain
       * @return NO_CONDITION if successful
       * @see setField
       * @see getField
       */
      virtual SEVERITY validate( unsigned short usSubclassId,
                                int nFieldId,
                                const DString& strValue,
                                bool fRemoveFormat = true );

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

      /**
       * Attempts to validate a contained object.
       * 
       * Call this method to explicitly kick off a
       * validator for the specified contained object.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return NO_CONDTION if successful
       * @see setObject
       * @see getObject
       * @see doesObjectExist
       * @see isObjectFlagSet
       */
      virtual SEVERITY validateObject( unsigned short usSubclassId,
                                       int nObjectId );

      /**
       * Attempts to validate the supplied object.
       * CBOBaseImpl does not provide for object
       * rollback functionality only field level rollbacks.
       * Therefore, use this method to see if it will
       * be a valid object to set.
       * 
       * Possibly call setObject after calling this method.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param pObject   A pointer to a CBOBase object to be validated
       * @return NO_CONDTION if successful
       * @see setObject
       * @see getObject
       * @see doesObjectExist
       * @see isObjectFlagSet
       */
      virtual SEVERITY validateObject( unsigned short usSubclassId,
                                       int nObjectId,
                                       const CBOBase * pObject );                           

      
   // Protected methods
   protected: 
      
      /**
       * Use this method to set(turn on ) a flag for
       * all fields associated with the specified group
       * flag.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param ulGroupFlag
       *                  A bit flag specifying which group flag to look for
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn on
       * @return true if successful
       *         fals if failure
       * @see FIELD_FLAG
       * @see removeFieldFlagByGroup
       */
      bool addFieldFlagByGroup(unsigned short usSubclassId,
                             unsigned long  ulGroupFlag,
                             FIELD_FLAG     fieldFlag );

      /**
       * This method can be called only from derived classes.
       * 
       * Retrieves a CBOBase pointer regardless of the
       * ClassObjectInfo flags that are set(on). If one
       * exists.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return A null pointer if the specified object does not exist.
       * @see getObject
       * @see _authorizedSetObject
       * @see setObject
       */
      virtual CBOBase * _authorizedGetObject( unsigned short usSubclassId,
                                             int nObjectId );

      /**
       * This method can be called only from derived classes.
       * 
       * This method works the same as setField, but
       * does not perform any validations.
       * The assumption with this method is
       * that you know what you are doing by
       * using this method instead of setField.
       * i.e. you are setting in a valid value
       * that does not need to be validated.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value to be stored in the
       *                 instancefieldinfo
       * @return NO_CONDITION if successful
       * @see setField
       */
      SEVERITY _authorizedSet( unsigned short usSubclassId,
                               int nFieldId,
                               const DString& strValue );
      
      /**
       * This method can be called only from derived classes.
       * 
       * This method works the same as the setField
       * that takes a MathString, but
       * does not perform any validations.
       * The assumption with this method is
       * that you know what you are doing by
       * using this method instead of setField.
       * i.e. you are setting in a valid value
       * that does not need to be validated.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nFieldId  A unique numeric indentifier for the registered field
       *                  used to index into the instancefieldinfo.
       *                  The indentifier for a field is set up in
       *                  the CLASS_FIELD_INFO.
       * @param mstrValue A MathString value that will be
       *                  converted to a string value and stored
       *                  in the instancefielinfo
       * @return 
       * @see setField
       */
      SEVERITY _authorizedSet( unsigned short usSubclassId,
                               int nFieldId,
                               const MathString& mstrValue );

      /**
       * This method can be called only from derived classes.
       * 
       * This method works the same as setData, but
       * does not perform any validations.
       * The assumption with this method is
       * that you know what you are doing by
       * using this method instead of setData.
       * i.e. you are setting in a valid values
       * that do not need to be validated.
       * 
       * @param data   A data object containing the data
       *               that will be moved into the
       *               instancefieldinfo
       * @return An integer value for the number of fields
       *         that were successfully set
       * @see setData
       */
      unsigned long _authorizedSet( const Data& data );

      /**
       * This method can be called only from derived classes.
       * 
       * This method works the same as setObject, but
       * does not perform any validations.
       * The assumption with this method is
       * that you know what you are doing by
       * using this method instead of setObject.
       * i.e. you are setting in a valid object
       * that does not need to be validated.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @param pObject   A CBOBase pointer to be stored as a
       *                  contained object in the
       *                  instanceobjectinfo
       * @param fDeleteOnFailure
       *                  A boolean value that, if true, tells CBOBaseImpl
       *                  to delete the passed in object if
       *                  the set fails. It defaults to false.
       *                  
       *                  CBOBaseImpl will not delete the pointer if false.
       * @return 
       * @see setObject
       * @see _authorizedGetObject
       */
      virtual SEVERITY _authorizedSetObject( unsigned short usSubclassId,
                                            int nObjectId,
                                            CBOBase * pObject,
                                            bool fDeleteOnFailure );

      /**
       * Constructor
       * 
       * With this ctor you can set the object's
       * validation mode to IMMEDIATE or POSTPONED
       * 
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
       *               An enumeration to specify which validation mode
       *               an instance will have. The enumeration defaults
       *               to IMMEDIATE.
       * @see VALIDATION_MODE
       * @see setValidationMode
       * @see getValidationMode
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       */
      CBOBaseImpl( VALIDATION_MODE validationMode=IMMEDIATE );

      /** Copy Constructor */
      CBOBaseImpl( const CBOBaseImpl &copy );

      /**
       * Turns the specified FIELD_FLAG off for
       * all fields in the instancefieldinfo
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn off
       * @see _setAllFieldFlags
       */
      void _clearAllFieldFlags( unsigned short usSubclassId,
                                FIELD_FLAG   fieldFlag );

      /**
       * Turns the specified OBJECT_FLAG off for
       * all fields in the instanceobjectinfo
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param objectFlag A enumeration specifying which OBJECT_FLAG to
       *                   turn off
       * @see _setAllObjectFlags
       */
      void _clearAllObjectFlags( unsigned short usSubclassId,
                                 OBJECT_FLAG  objectFlag );

      /**
       * Turns the specified FIELD_FLAG off for
       * an individual field in the instancefieldinfo
       * 
       * Field flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nFieldID  A unique numeric indentifier for the registered field
       *                  used to index into the instancefieldinfo.
       *                  The indentifier for a field is set up in
       *                  the CLASS_FIELD_INFO.
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn off
       * @return true for success
       *         false for failure
       * @see setFieldFlag
       */
      bool clearFieldFlag(unsigned short usSubclassId,
                           int nFieldID,
                           FIELD_FLAG  fieldFlag );

      /**
       * Turns off the specified field group flag for
       * an individual field in the instancefieldinfo.
       * 
       * Field group flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usFieldGroupFlag
       *               a bit flag that specifies which group field flag
       *               to turn off
       * @return true for success
       *         false for failure
       * @see setFieldGroupFlag
       * @see isFieldGroupFlagSet
       * @see getFieldGroupFlag
       */
      bool clearFieldGroupFlag( unsigned short usSubclassId,
                                unsigned long usFieldGroupFlag );
      
      /**
       * Turns the specified OBJECT_FLAG off for
       * an individual object in the instanceobjectinfo
       * 
       * Object flags for a specific field are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param nObjectID  A unique numeric indentifier for the registered contained CBO
       *                   used to index into the instanceobjectinfo.
       *                   The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                   of the derived class.
       * @param objectFlag A enumeration specifying which OBJECT_FLAG to
       *                   turn off
       * @return true for success
       *         false for failure
       * @see setObjectFlag
       * @see isObjectFlagSet
       */
      bool clearObjectFlag(unsigned short usSubclassId,
                           int nObjectID,
                           OBJECT_FLAG objectFlag );

      /**
       * Turns off the specified object group flag for
       * an individual object in the instanceobjectinfo.
       * 
       * Object group flags for a specific object are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usObjectGroupFlag
       *               a bit flag that specifies which group object flag
       *               to turn off
       * @return true for success
       *         false for failure
       * @see setObjectGroupFlag
       * @see isObjectGroupFlagSet
       */
      bool clearObjectGroupFlag( unsigned short usSubclassId,
                                 unsigned long usObjectGroupFlag );
      
      /**
       * Determines if the specified object is contained
       * within this object.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectID A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return true if the specified object exists as a
       *         contained object
       *         false if the object does not exist
       * @see setObject
       * @see getObject
       * @see _authorizedSetObject
       * @see _authorizedGetObject
       */
      bool doesObjectExist( unsigned short usSubclassId,
                            int nObjectID ) const;
      
      /**
       * Formats a string value from the matching
       * Data object field mask.
       * 
       * This method calls the formatStringUsingMask
       * method in the StringFunctions module.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param strToUnformat
       *               A string value to format
       * @see StringFunctions.hpp
       * @see formatStringUsingMask
       * @see unformatStringFromDataObjects
       */
      void formatStringFromDataObjects( const DString& strFieldTag, DString& strToUnformat ) const;

      /**
       * Formats a string value from the matching
       * Data object field mask.
       * 
       * This method calls the overloaded
       * formatStringFromDataObjects
       * which in turn calls the
       * formatStringUsingMask
       * method in the StringFunctions module.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strToFormat
       *                 A string value to format
       * @see StringFunctions.hpp
       * @see formatStringUsingMask
       * @see formatStringFromDataObjects
       */
      void formatStringFromDataObjects( unsigned short usSubclassId,
                                        int nFieldId,
                                        DString& strToFormat ) const;

      /**
       * Gets a pointer to the Data object(before image)
       * attached to a CBO
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @return A Data object pointer
       *         A null Data object pointer if one does not exist
       * @see setDataObjectPointer
       */
      Data * getDataObjectPointer( unsigned short usSubclassId ) const;

      /**
       * Gets a string value for the specified field
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return A const string reference to a value
       *         in the instancefieldinfo
       * @see getField
       */
      virtual const DString& _getField( unsigned short usSubclassId,
                                       int nFieldId ) const;

      /**
       * Retrieves a field group flag for the specified
       * group flag
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usFieldGroupFlag
       *               a bit flag that specifies which group field flag
       *               to get
       * @see setFieldGroupFlag
       * @see isFieldGroupFlagSet
       * @see clearFieldGroupFlag
       */
      void getFieldGroupFlag( unsigned short usSubclassId,
                              unsigned long &usFieldGroupFlag ) const;

      /**
       * This method returns an instance field id for the
       * provided field tag.
       * 
       * If a matching tag is found return the field index
       * else
       * return INVALID_FIELD_ID (-1).
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return A unique numeric indentifier for the registered field
       *         used to index into the instancefieldinfo.
       *         The indentifier for a field is set up in
       *         the CLASS_FIELD_INFO.
       */
      int _getFieldID( unsigned short usSubclassId,
                       const DString& strFieldTag ) const;

      /**
       * Retrieves an object group flag for the
       * specified object group flag
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usObjectGroupFlag
       *               a bit flag that specifies which group object flag
       *               to get
       * @see setObjectGroupFlag
       * @see clearObjectGroupFlag
       * @see isObjectGroupFlagSet
       */
      void getObjectGroupFlag( unsigned short usSubclassId,
                               unsigned long &usObjectGroupFlag ) const;

      /**
       * Checks to see if a contained(aggregate) object
       * has been marked as INST_OBJ_DELETED
       * 
       * A call to the deleteObject method will
       * turn this OBJECT_FLAG on.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nObjectId A unique numeric indentifier for the registered contained CBO
       *                  used to index into the instanceobjectinfo.
       *                  The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                  of the derived class.
       * @return true if the contained object has been deleted
       *         false if the contained object still exists
       * @see deleteObject
       * @see setObject
       * @see getObject
       */
      bool isObjectDeleted( unsigned short usSubclassId,
                            int nObjectId ) const;

      /**
       * Checks to see if a field of type FLAG has a value
       * of 0 or N
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return true if the field value is a 0 or N
       *         false if the field value is a 1 or Y
       */
      bool isOff( unsigned short usSubclassId, int nFieldId ) const;

      /**
       * Checks to see if a field of type FLAG has a value
       * of 1 or Y
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @return true if the field value is a 1 or Y
       *         false if the field value is a 0 or N
       */
      bool isOn( unsigned short usSubclassId, int nFieldId ) const;

      /**
       * Determines if a supplied value is the same as an instance field
       * value for the specified field
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The string value to be compared to the instancefieldinfo
       *                 string value
       * @return true if the passed in value is the same as the
       *         the matching instancefieldinfo value
       *         
       *         false if the values are different
       */
      bool isSameValue( unsigned short usSubclassId, int nFieldId, const DString& strValue ) const;

      /**
       * Reformats the passed in value based on the
       * boolean value.
       * 
       * This method is called from a validate method.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strUnformatValue
       *                 The string value to be formatted
       * @param fRemoveFormat
       *                 A boolean value that says to unformat the value
       *                 if true
       *                 
       *                 if false do not unformat the value
       * @see validate
       */
      void reFormatValue( unsigned short usSubclassId,
                          int nFieldId,
                          DString& strUnformatValue,
                          bool fRemoveFormat ) const;

      /**
       * Register the CLASS_FIELD_INFO and CLASS_OBJECT_INFO
       * that is defined in a derived class with CBOBaseImpl
       * 
       * This method should be called from the constructor
       * in a derived class.
       * 
       * This is how CBOBaseImpl can know about the
       * CLASS_FIELD_INFO and CLASS_OBJECT_INFO for
       * each specific subclass.
       * 
       * 
       * 
       *  @param usSubclassId - index into the correct subclass
       *  @param nNumberFields - enum value of numbers of fields
       *  @param pClassFieldInfo - pointer to a subclasses CLASS_FIELD_INFO
       *  @param nNumberObjects - enum value of number of contained objects
       *  @param pClassObjectInfo - pointer to a subclasses CLASS_OBJECT_INFO
       *  @returns true if sucessfull
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param nNumberFields
       *               A integer value specifying the number of fields
       *               contained in the CLASS_FIELD_INFO.
       * @param pClassFieldInfo
       *               A pointer to the CLASS_FIELD_INFO
       * @param nNumberObjects
       *               A integer value specifying the number of objects
       *               contained in the CLASS_OBJECT_INFO.
       * @param pClassObjectInfo
       *               A pointer to the CLASS_OBJECT_INFO.
       * @return true if successful
       *         false if failure
       * @see CLASS_FIELD_INFO
       * @see CLASS_OBJECT_INFO
       */
      bool _registerSubclass( unsigned short usSubclassId,
                              int nNumberFields,
                              const CLASS_FIELD_INFO * pClassFieldInfo,
                              int nNumberObjects,
                              const CLASS_OBJECT_INFO * pClassObjectInfo );
      
      /**
       * Turns the specified FIELD_FLAG off for
       * an individual field in the instancefieldinfo
       * that is associated with a field group based
       * on a field group flag.
       * 
       * Field flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * Field group flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param ulGroupFlag
       *                  a bit flag that specifies which group field flag
       *                  to turn off
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn off
       * @return true for success
       *         false for failure
       * @see FIELD_FLAG
       * @see addFieldFlagByGroup
       */
      bool removeFieldFlagByGroup(unsigned short usSubclassId,
                                  unsigned long  ulGroupFlag,
                                  FIELD_FLAG  fieldFlag );

      /**
       * Turns the specified FIELD_FLAG on for
       * all fields in the instancefieldinfo
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn on
       * @see _clearAllFieldFlags
       */
      void _setAllFieldFlags( unsigned short usSubclassId,
                              FIELD_FLAG     fieldFlag );

      /**
       * Turns the specified OBJECT_FLAG on for
       * all fields in the instanceobjectinfo
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param objectFlag A enumeration specifying which OBJECT_FLAG to
       *                   turn on
       * @see _clearAllObjectFlags
       */
      void _setAllObjectFlags( unsigned short usSubclassId,
                               OBJECT_FLAG    objectFlag );

      /**
       * Associates CBO with a pointer to a
       * Data object(before image).
       * 
       * After a call to this method, CBOBaseImpl
       * will own the Data object pointer and
       * will therefore take care of deleting
       * the object upon destruction
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param pData  A pointer to a Data object(before image)
       * @return true if success
       *         false if failure
       * @see getDataObjectPointer
       */
      bool setDataObjectPointer( unsigned short usSubclassId, Data * pData );
      
      /**
       * Turns the specified FIELD_FLAG on for
       * an individual field in the instancefieldinfo
       * 
       * Field flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param nFieldID  A unique numeric indentifier for the registered field
       *                  used to index into the instancefieldinfo.
       *                  The indentifier for a field is set up in
       *                  the CLASS_FIELD_INFO.
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn on
       * @return true for success
       *         false for failure
       * @see FIELD_FLAG
       * @see CLASS_FIELD_INFO
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool setFieldFlag(unsigned short usSubclassId,
                        int nFieldID,
                        FIELD_FLAG     fieldFlag );

      /**
       * Turns on the specified field group flag for
       * an individual field in the instancefieldinfo.
       * 
       * Field group flags for a specific field are
       * set up in the CLASS_FIELD_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usFieldGroupFlag
       *               a bit flag that specifies which group field flag
       *               to turn on
       * @return true for success
       *         false for failure
       * @see CLASS_FIELD_INFO
       * @see clearFieldGroupFlag
       * @see isFieldGroupFlagSet
       * @see isGroupValid
       */
      bool setFieldGroupFlag( unsigned short usSubclassId,
                              unsigned long usFieldGroupFlag );

      /**
       * Call this method to turn on or off
       * field group processing for an instance of a CBO
       * 
       * @param fGroupEnabled
       *               true to enable field group processing
       *               false to disable field group processing
       * @see isObjectGroupEnabled
       * @see setActiveGroup
       * @see applyActiveGroup
       * @see removeGroup
       * @see deleteGroup
       * @see doesGroupExist
       */
      void setGroupEnabledStatus(bool fGroupEnabled);


      /**
       * Turns the specified OBJECT_FLAG on for
       * an individual object in the instanceobjectinfo
       * 
       * Object flags for a specific field are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param nObjectID  A unique numeric indentifier for the registered contained CBO
       *                   used to index into the instanceobjectinfo.
       *                   The unique numeric identifier is set up in the CLASS_OBJECT_INFO
       *                   of the derived class.
       * @param objectFlag
       * @return true for success
       *         false for failure
       * @see OBJECT_FLAG
       * @see CLASS_OBJECT_INFO
       * @see clearObjectFlag
       * @see isObjectFlagSet
       */
      bool setObjectFlag(unsigned short usSubclassId,
                        int nObjectID,
                        OBJECT_FLAG objectFlag );

      /**
       * Turns on the specified object group flag for
       * an individual object in the instanceobjectinfo.
       * 
       * Object group flags for a specific object are
       * set up in the CLASS_OBJECT_INFO for a derived class.
       * 
       * @param usSubclassId
       *               An index used for selecting the correct
       *               subclass(derivation) we are working with.
       * @param usObjectGroupFlag
       * @return true for success
       *         false for failure
       * @see CLASS_OBJECT_INFO
       * @see clearObjectGroupFlag
       * @see isObjectGroupFlagSet
       * @see isGroupValid
       */
      bool setObjectGroupFlag( unsigned short usSubclassId,
                               unsigned long usObjectGroupFlag );

      /**
       * Unformats a string value using the matching
       * Data object field mask.
       * 
       * This method calls the removeMaskFromString
       * method in the StringFunctions module.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param strToUnformat
       *               The string value to unformat
       * @see StringFunctions.hpp
       * @see removeMaskFromString
       * @see formatStringFromDataObjects
       */
      void unformatStringFromDataObjects( const DString& strFieldTag, DString& strToUnformat ) const;

      /**
       * Formats a string value using the matching
       * Data object field mask.
       * 
       * This method calls the overloaded
       * unformatStringFromDataObjects
       * which in turn calls the
       * removeMaskFromString
       * method in the StringFunctions module.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strToUnformat
       *                 The string value to unformat
       * @see StringFunctions.hpp
       * @see removeMaskFromString
       * @see formatStringFromDataObjects
       */
      void unformatStringFromDataObjects( unsigned short usSubclassId,
                                          int nFieldId,
                                          DString& strToUnformat ) const;
                                              
       /**
       * Validates the specified value against a
       * set of pre-defined values for an instance field
       * 
       * The valid values can be defined in the
       * CLASS_FIELD_INFO of a derived class using
       * the following tags:
       * 
       * Valid_Values=
       * Min=
       * Max=
       * 
       * Here are some examples of usage
       * for in the CLASS_FIELD_INFO:
       * 
       * "Valid_Values=Y|N"
       * "Valid_Values=A|B|C"
       * "Min=100"
       * "Max=500"
       * "Min=100 Max=500"
       * 
       * This method is called by a validate method
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The string value to be validated
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see validate
       */
      SEVERITY validateFieldWithValidValues( unsigned short usSubclassId,
                                             int nFieldId,
                                             const DString& strValue);

      /**
       * Checks the value against the read only or
       * required attributes of an instance field
       * 
       * This method is call by a setField method
       * and a validate method.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The string value to be validated
       * @return NO_CONDITION if successful
       * @see setField
       * @see validate
       */
      SEVERITY validateReadOnlyRequired( unsigned short usSubclassId,
                                         int nFieldId,
                                         const DString& strValue,
                                         bool bNoReadOnlyCheck = false );


		/**
		 * Check if the field is crossfield. 
		 * 
		 * This method return SEVERE_ERROR if call is made to validate() method 
		 * to validate field crossfield
		 *
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
		 *
		 * @return NO_CONDITION if field is not crossfield
		 * 
		 * @see validate
		 * @see validateField
		 */
		SEVERITY	validateIfCrossField( unsigned short usSubclassId,
												  int nFieldId );

	
	// Protected data structures and definitions
   protected:
      CBOBase                    *_pInterface;//Used so the impl knows about the interfce
      CBOBase                    *_pContainer;//Used so contained object can know about his container
      
      //Generic map for Data objects
      typedef map< DString, Data*, less<DString> > DATA_MAP;
      typedef DATA_MAP::value_type DATA_MAP_TYPE;
      DATA_MAP                    _mapDataObjects;
      

   // Private methods
   private: 
      
       /**
        * This method changes the passed in string value
        * to an N or Y if it is one of the recognized
        * flag values.
        * 
        * y and 1 will be converted to Y
        * n and 0 will be converted to N
        * 
        * @param strNewValue
        *               The string flag value to be converted
        * @return true if successful
        *         false if failure
        * @see isFlagValue
        */
      bool convertToFlagValue( DString &strNewValue );

      /**
       * This method is called by removeGroup method.
       * 
       * Removes the specifed group from the field
       * group processing list.
       * 
       * Use this method if working with field group
       * processing e.g. setActiveGroup, applyActiveGroup etc.
       * If the group exists, somebody must have
       * called setActiveGroup using the specified string
       * label.
       * 
       * @param strGroup A string label attached to a field group
       * @return NO_CONDITION if successful
       * @see removeGroup
       */
      SEVERITY deleteGroup(const DString& strGroup);
      
      bool _fObjectGroupEnabled;
      
      /**
       * Get the name of a FIELD_FLAG and
       * return it in a string
       * 
       * The dumpInstanceFieldInfo method
       * calls this method.
       * 
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn off or on for all fields
       * @param strFieldFlagName
       *                  The string to fill up with the FIELD_FLAG name
       * @see dumpInstanceFieldInfo
       */
      void getFieldFlagName( FIELD_FLAG fieldFlag, DString& strFieldFlagName ) const;

      /**
       * This method returns an instance field id and the
       * corresponding subclass id for the provided field tag.
       * If a matching tag is found return the field index
       * and the subclass id index else
       * return INVALID_FIELD_ID (-1).
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @param pusSubclass
       *               The variable to hold the subclass id that is found
       * @return A unique numeric indentifier for the registered field
       *         used to index into the instancefieldinfo.
       *         The indentifier for a field is set up in
       *         the CLASS_FIELD_INFO.
       */
      int _getFieldID( const DString& strFieldTag,
                       unsigned short * pusSubclass ) const;

      /**
       * Check to see if the passed in string
       * value is a flag value.
       * The following values are considered flag
       * values:
       * Y
       * y
       * N
       * n
       * 0
       * 1
       * 
       * @param strNewValue
       *               The string value to be checked
       * @return true if the string value is one of the flag values
       *         fals if the string values is not one of the flag
       *         values
       * @see convertToFlagValue
       */
      bool isFlagValue( const DString& strNewValue ) const;

		/**
       * Sets the specified instance field with the supplied string value.
       * This method will call a validator if it exists in
       * the derived class.  This method will not return
       * conditions if the object is set to postponed
       * validation mode.  If setField fails the value
       * will not be accepted and not stored in the instancefieldinfo.
       * Any previous value will remain in storage.
       * Note: This method is same as setField except it will not call
		 * the reFormatValue method to format the value.
       * 
       * The reasons why this method could fail are:
       * 
       * 1. The instance field is marked as INST_FLD_READ_ONLY
       * 
       * 2. The instance field is marked as INST_FLD_REQUIRED
       * and a null value or spaces was passed in
       * 
       * 3. The maximum length is exceeded for instance field
       * 
       * 4. The type of the passed-in value is not valid with
       * the instancefieldinfo type. e.g. an alpha value cannot
       * set into a numeric typed field.
       * 
       * 5. The field does not pass business validations as
       * specified in the derived class.
       * 
       * @param usSubclassId
       *                 An index used for selecting the correct
       *                 subclass(derivation) we are working with.
       * @param nFieldId A unique numeric indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value that will be validated and stored
       * @return NO_CONDITION if successful
		 * @see setField
       * @see getField
       * @see resetField
       * @see validate
       */
      virtual SEVERITY setFieldNoFormat( unsigned short usSubclassId,
                                 int nFieldId,
                                 const DString& strValue );

		/**
       * Turn the specified FIELD_FLAG on or off
       * for all fields in the instancefieldinfo
       * based on the boolean value passed in.
       * 
       * @param usSubclassId
       *                  An index used for selecting the correct
       *                  subclass(derivation) we are working with.
       * @param fieldFlag A enumeration specifying which FIELD_FLAG to
       *                  turn off or on for all fields
       * @param fIsFlagOn true = set all flags(on)
       *                  false = clear all flags(off)
       * @see FIELD_FLAG
       * @see _setAllFieldFlags
       * @see _clearAllFieldFlags
       */
      void _switchAllFieldFlags( unsigned short usSubclassId,
                                 FIELD_FLAG     fieldFlag,
                                 bool           fIsFlagOn );

      /**
       * Turn the specified OBJECT_FLAG on or off
       * for all objects in the instanceobjectinfo
       * based on the boolean value passed in.
       * 
       * @param usSubclassId
       *                   An index used for selecting the correct
       *                   subclass(derivation) we are working with.
       * @param objectFlag A enumeration specifying which OBJECT_FLAG to
       *                   turn off or on for all objects
       * @param fIsFlagOn  true = set all flags(on)
       *                   false = clear all flags(off)
       * @see OBJECT_FLAG
       * @see _setAllObjectFlags
       * @see _clearAllObjectFlags
       */
      void _switchAllObjectFlags( unsigned short usSubclassId,
                                  OBJECT_FLAG    objectFlag,
                                  bool           fIsFlagOn );




   // Private data structures and definitions
   private:
      typedef map< DString, int, less<DString> > TAG_MAP;
      typedef TAG_MAP::value_type TAG_MAP_TYPE;
      typedef vector< Data * >::iterator  DATA_ITER;

      vector< int >                       _vecNumberFields;
      vector< CBOInstanceFieldInfo * >    _vecInstanceFieldInfo;
      vector< CBOInstanceFieldInfo * >    _vecInstanceFieldInfoCheckpoint;
      vector< const CLASS_FIELD_INFO * >  _vecClassFieldInfo;
      vector< TAG_MAP >                   _vecTagMap;
      vector< Data * >                    _vecDataPointer;
      vector< int >                       _vecNumberObjects;
      vector< CBOInstanceObjectInfo * >   _vecInstanceObject;
      vector< const CLASS_OBJECT_INFO * > _vecClassObjectInfo;
      unsigned short                      _usNumberSubclasses;
      VALIDATION_MODE                     _validationMode;
      DString                              _strKey;
      static const I_CHAR *                 NUMBER_SHARES_DEFAULT_MASK;
      static const I_CHAR *                 DOLLAR_AMOUNT_DEFAULT_MASK;
      bool                                _fDeleteInterface;

      // Group additions
      typedef map< DString, vector< CBOInstanceFieldInfo* >*, less<DString> > MAP_GROUPS;
      typedef vector< CBOInstanceFieldInfo* > VEC_IFO;
      MAP_GROUPS _mapGroups;
      static bool                         _fUpdateOccurring;
      DString                              _strCurrentGroup;
      long                                _iUpdateLevel;

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
// $Log:   Y:/VCS/iFastAWD/inc/cbobaseimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:14   kovacsro
//Initial revision.
// 
//    Rev 1.13   28 Nov 2001 12:41:44   dt14177
// fixed linkage define
// 
//    Rev 1.12   Nov 01 2001 14:54:22   dt39990
// Added validateIfCrossField() method to 
// check if the field is crossfield. 
// This method was added to make sure that 
// field crossfield should call validateField() 
// method instead of validate() method to 
// validate the field 
// 
//    Rev 1.10   Jan 26 2001 10:04:40   dt39990
// Added CLASS_FLD_CROSS_FIELD and 
// INST_FLD_CROSS_FIELD for cross field test
// 
// Added boolean variable to the 
// validateReadOnlyRequired method 
// for specifying not to perform the read 
// only check
// 
// Removed the _validate() method. It was
// duplicating effort for no reason. 
// 
//    Rev 1.9   Dec 26 2000 15:37:18   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
//    Rev 1.8   30 Nov 2000 09:58:00   dt14177
// cleanup
// 
//    Rev 1.7   Sep 05 2000 09:38:44   DT29758
// added bool method doesCheckPointExist
// 
//    Rev 1.6   Jul 18 2000 13:12:58   DT22388
// synch-up changes with infra 1.7
// 
//    Rev 1.5   Dec 31 1999 06:27:42   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.3   Dec 06 1999 10:11:10   DT29758
// added additional ccdoc comments
// 
//    Rev 1.2   Nov 23 1999 11:04:30   DT29758
// added ccdoc style comments and minor code
// organization
// 
//    Rev 1.0.1.5   Oct 05 1999 15:56:50   DT29758
// added validate method that validates a 
// Data object
// 
//    Rev 1.0.1.4   Sep 14 1999 14:13:50   DT22388
// Added new method validateReadOnlyRequired()
// Added a validate() method override so
// that the setField() and validate() method
// that takes a value can take a separate
// path from a validateAll() method call.
// The validate method that takes a value
// now calls the validateReadOnlyRequired().
// 
// 
// 
//    Rev 1.0.1.3   Aug 31 1999 15:18:14   DT22388
// Fixed the validate() method to handle
// a bool bValidatorCallOnly so that a call
// from validateField() will only kick off the
// associated validator() method in the
// derived class and not the CBOBaseImpl
// validate().  The validateField() is concerned
// with cross-field validations only. 
// 
//    Rev 1.0.1.2   Aug 04 1999 17:30:56   DT22388
// Added two new validate() methods
// 
// SEVERITY validate( const DString& strFieldTag,
//                                        const DString& strValue );
// 
// SEVERITY validate( const DString& strFieldTag,
//                                         const MathString& mstrFieldValue );
// and added a 'using $ParentClass$::validate;'
// so that the validate() method that takes
// an enum works with two or more
// derivations from CBOBase.
// 
//    Rev 1.0.1.1   Aug 02 1999 10:47:18   DT22388
// Made the _validate() method protected
// and added subclassid as a parameter.
// 
//    Rev 1.0.1.0   Jul 30 1999 13:32:14   DT22388
// Added a new method reFormatValue()
// Added a new method _validate()
// Added new code to the validate() method
// These new methods are needed as
// a part of fixing the issues with the 
// validate() method.
// The validate() method was not behaving
// exactly like the setField in the validation
// process.
// 
//    Rev 1.0   Jun 21 1999 17:07:08   DT22388
//  
// 
//    Rev 1.8   May 05 1999 19:36:48   DT22388
// For tracker ticket #8020
// Added the _pContainer and the setContainer()
// method so that a derived class can know
// about his container object.
// 
//    Rev 1.7   Mar 08 1999 14:42:04   DT22388
// Added a new method isSameValue()
// for tracker ticket #6467.
// 
//    Rev 1.6   Feb 23 1999 17:05:02   DT21815
// Made getConstObject method const.
// 
//    Rev 1.5   Jan 14 1999 12:50:18   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.4   Jan 07 1999 09:20:42   DMAL
// added three methods for the 3.4.0.0 code sync
// up, notifiyonbackout, notifyonupdate, 
// notifyoncommit.
//
//    Rev 1.3   Oct 27 1998 14:36:20   DT22388
// Removed a #include of CBOBase.hpp
// and added a forward declare of CBOBase.
// Added a new _registerSubclass() method.
// Added a new flag _fUsingNewRegisterSubclass.
//
//
//    Rev 1.2   Sep 24 1998 13:03:44   dt22388
// Added the key word virtual to the
// getContainedDetailUpdates() method
//
//    Rev 1.0   29 Jul 1998 23:58:10   dt14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.44   Jul 13 1998 10:34:06   djoo
// Added PERCENT data type.  Modified one validate
// signature to keep PERCENTs from being "unformatted'
// twice during setFields.
//
//    Rev 1.43   Jul 11 1998 11:44:40   djoo
// Made doesObjectExist a const method.
//
//    Rev 1.42   Jul 10 1998 16:12:18   djoo
// Added method doesObjectExist.
//
//    Rev 1.41   Jun 24 1998 17:57:42   DT21815
// Added new methods to support turning on/off all
// flags for fields and objects.
//
//    Rev 1.40   May 28 1998 15:19:52   djoo
// Added object flag INST_OBJ_DELETED.
// Added method isObjectDeleted.
//
//    Rev 1.39   May 27 1998 10:45:38   djoo
// Added 1 class object flag and 1 instance object
// flag.  Added methods notifyOnDeleteObject and
// deleteObject.
//
//    Rev 1.38   May 14 1998 10:15:50   djoo
// Added method doesGroupExist.
//
//    Rev 1.37   Apr 10 1998 12:18:50   djoo
// Added methods unformatStringFromDataObjects
// and formatStringFromDataObjects.  Added support
// to provide DString substitution values thru CBOs.
//
//    Rev 1.36   Apr 08 1998 14:53:48   djoo
// Removed method isInitialized.
// Now implemented in CBOBase
//
//    Rev 1.35   Apr 06 1998 15:47:44   djoo
// Added method modelFrom.
//
//    Rev 1.34   Apr 03 1998 12:16:42   djoo
// Added object flags CLASS_OBJ_PTR_ACCESS_ONLY
// and INST_OBJ_PTR_ACCESS_ONLY.
//
//    Rev 1.33   Mar 27 1998 11:03:34   djoo
// Added isOn and isOff methods.
//
//    Rev 1.32   Mar 26 1998 07:46:18   DMGM
// Added isOn and isOff methods
//
//    Rev 1.31   Mar 24 1998 13:14:16   djoo
// Moved resetField methods to the public section.
//
//    Rev 1.30   Mar 05 1998 13:12:30   djoo
// Added method resetInstanceObjectInfo.
//
//    Rev 1.29   Mar 03 1998 13:24:34   djoo
// Modified signature to setGroupEnabledStatus.
//
//    Rev 1.28   Mar 03 1998 12:17:44   djoo
// Removed methods getLastRefreshCount and setLastRefreshCount.
// Renamed method refreshCBOsByLabel to refresh.
//
//    Rev 1.27   Feb 27 1998 13:19:58   djoo
// Added methods setObjectFlag and clearObjectFlag.
//
//    Rev 1.26   Feb 19 1998 11:09:40   djoo
// Added method isFieldReadOnly.
//
//    Rev 1.25   Feb 09 1998 12:14:32   djoo
// Added overload isFieldUpdated.
// Added method refreshCBOsByLabel.
// Added Group Flag methods for objects and fields.
//
//    Rev 1.24   Jan 24 1998 10:22:06   djoo
// Removed flags for authorizedSet methods to control
// whether the UPDATED flags were turned on.
//
//    Rev 1.23   Jan 17 1998 11:31:42   djoo
// Modified object flags CLASS_OBJ_BASE_DELETE and
// INST_OBJ_BASE_DELETE to CLASS_OBJ_NO_BASE_DELETE and
// INST_OBJ_NO_BASE_DELETE.  They were named incorrectly
// according to there use.
//
//    Rev 1.22   Jan 09 1998 16:11:32   djoo
// Made dumpInstanceFieldInfo and getFieldFlagName const.
// Made dumpInstanceFieldInfo public.
//
//    Rev 1.21   Jan 09 1998 14:02:22   djoo
// Added support for update levels.  Added public method getUpdateLevel.
// Added protected/private methods dumpInstanceFieldInfo and getFieldFlagname.
//
//    Rev 1.20   Jan 06 1998 15:08:42   djoo
// Removed static member from common_impl_*.hpp files
// and moved it to CBOBaseImpl.hpp as const.
//
//    Rev 1.19   Dec 19 1997 15:00:34   djoo
// Added public methods setStaticUpdatingFlag, getStaticUpdatingFlag, setActiveGroup, getActiveGroup,
// applyActiveGroup, getActiveGroup, removeGroup and isObjectGroupEnabled.  Added private/protected
// methods deleteGroup, setGroupEnabledStatus, setFieldFlag, clearFieldFlag.    Added support data members.
//
//
//    Rev 1.18   Dec 09 1997 08:44:52   djoo
// Added method isFieldUpdated.  Added bSetFieldUpdatedFlag to all _authorizedSet methods.  This flag controls the setting of the INST_FLD_UPDATED flag for instance fields affected by the method.
//
//    Rev 1.17   Dec 05 1997 08:42:18   djoo
// Added methods checkpointFields, rollbackFieldsToCheckpoint, isFieldGroupFlagSet, isObjectGroupFlagSet.
// Added group flag support for aggregate objects.  Modified validateField methods.  Added data map to be used by derived classes to hold various data objects.
//
//    Rev 1.16   Nov 21 1997 10:32:04   djoo
// Removed const from all getObject methods and getConstObject method.
//
//    Rev 1.15   Nov 21 1997 08:03:40   djoo
// Changed methods getObject and getDataObjectPointer to const.
//
//    Rev 1.14   Nov 20 1997 13:50:46   djoo
// Added methods validateField, setInterfacePointer.  Enhanced getObject method. Fixed bug in setDataObjectPointer for deleting data objects.
//
//    Rev 1.13   Nov 12 1997 09:30:12   djoo
// Modified signature for _registerSubclass.
//
//    Rev 1.12   Nov 11 1997 11:03:38   djoo
// Added redundant include guards, import/export protection, flag data type, get/set object, field formatting, field valid values, add/remove field flags by group, reset field.
//
//    Rev 1.11   Sep 24 1997 16:07:16   djoo
// Added data object vector iterator typedef.
//
//    Rev 1.10   Sep 02 1997 16:06:24   djoo
// Intermediate Check-in for CBO8. (Condition Manager enhancements)
//
//    Rev 1.9   Aug 26 1997 12:50:18   djoo
// Initial SEVERITY enhancements.
//
//    Rev 1.8   16 Aug 1997 12:01:36   dmal
//
//
//    Rev 1.7   Jul 21 1997 15:59:48   DPQD
// Added new method "isInitialized" to determine if
// the "init" method has been called.
//
//    Rev 1.6   Jul 16 1997 15:52:58   DPQD
// Added field mask to Class Field Info structure.
// Added static variables to hold default masks for
// NUMBER_SHARES and DOLLAR_AMOUNT data types.
//
//    Rev 1.4   Jul 10 1997 16:04:36   DPQD
// Removed ErrorList.
//
// Added new methods.
//
// Moved some methods from proteced to private.
//
//    Rev 1.3   28 Jun 1997 11:43:20   dmal
// removed several methods from the private area.  DJBH
//
//

#endif




