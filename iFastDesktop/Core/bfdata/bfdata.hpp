#pragma once

#include <commonport.h>

#include <bfdata\bfdataexception.hpp>

#include <dstring.hpp>
#include <clientlocale.hpp>

#include <bfdata\bffieldid.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bfsubstitutionset.hpp>

#include <bfdata\bfdataid.hpp>
#include <bfdata\bfdataimplfactory.hpp>
#include <bfdata\bfdataimpl.hpp>
#include <bfdata\bfdatafield.hpp>
#include <bfdata\bfdatafieldexists.hpp>
#include <map>
#include <vector>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

#define DEFAULT_REPEAT_RECORD I_("Repeat_Record")

class BFDATA_LINKAGE BFData
{

public:
   /**
    * default ctor
    */
   BFData();
   /**
    * Construct a new BFData object given a valid BFDataId identifier
    * 
    * @param id     The identity of the new BFData object.
    */
   BFData( const BFDataId& id );
   /**
    * dtor
    */
   ~BFData();

   BFData( const BFData& rhs );

   friend class BFDataFieldIter;
   friend class BFConstDataFieldIter;

   /**
    * Describes how a field is to be appended to a BFData object.
    */
   enum EAPPEND_MODE
   {
      NO_APPEND,
      APPEND,
      APPEND_FROM_PROPERTIES
   };

   /**
    * Returns the repeat BFData object at the specified 0-based index.
    * 
    * @param index  The 0-based index of the repeat to get.
    * 
    * @return a reference to the repeat BFData object at the specified index.
    */
   BFData& operator[]( unsigned int index );

   /**
    * Assigns one BFData object to another.
    * 
    * @param rhs    original
    * 
    * @return reference to this BFData object.
    */
   BFData &operator= ( const BFData &rhs );

   /**
    * Adds a BFData object to the repeat area of this BFData object.
    * 
    * @param newRepeat reference to the new BFData object.  A copy of this object is made
    *                  and stored in the repeat area.
    * 
    * @return true if the BFData object was successfully added to the repeat area, false otherwise.
    */
   bool addRepeat( const BFData &newRepeat );

   /**
    * Checks if the field specified in the parameter
    * componentName exists this BFData object.
    * 
    * @param componentName
    *               - (in) contains the name of the field to check for.
    * 
    * @return true if the specified field exists, false if it doesn't.
    */
   bool exists( const DString &componentName ) const;

   /**
    * Checks if the field specified in the parameter idField exists in 
    * this BFData object.
    * 
    * @param id     the data dictionary id of the field.
    * 
    * @return true if the specified field exists, false if it doesn't.
    */
   bool exists( const BFFieldId& idField ) const;

   /**
    * class method to determine if a specified field exists is in 
    * the predefined field list of a specific BFDataImpl-derived class.
    * 
    * @param idData  id of the BFData view list
    * @param idField id of the field to check for existence
    * 
    * @return true if the specified field is in the specified BFDataImpl-derived class
    */
   static bool exists( const BFDataId& idData, const BFFieldId& idField );

   /**
    * Create an IDI string of name=value pairs for each field in the
    * this BFData object.
    * 
    * @param idiString  a reference to the DString in which the output IDI string will be written.
    * @param insertEOLs if true then EOLs are appended to each each name=value pair in the output string.
    * @param usePropertiesOrder
    *                   no effect.
    * @param flags      Use to control the appearance of the value part of the name=value
    *                   pairs in idiString.  Either value BFDataField::USE_SUBSTITUTES or
    *                   BFDataField::USE_MASKS can be specified.
    */
   void getAllValues( DString &idiString, 
                      bool insertEOLs = false,
                      bool usePropertiesOrder = false,
                      unsigned long flags = 0L ) const;

   /**
    * Fill a pre-allocated I_CHAR buffer with the contents of the BFData
    * object.  The values of the BFDataFields will be raw (i.e. formatted
    * for the Host).
    * 
    * @param pBuffer  A pointer to a user allocated array of I_CHARs.  It is the responsibility of
    *                 the application to free any allocated memory.
    * @param cbBuffer The size of pBuffer, in bytes (not I_CHARs).
    * @param rLocale  A reference to the current ClientLocale object.
    * 
    * @return count of bytes actually copied to the pBuffer.
    */
   unsigned long getAsUnsignedCharBuffer( I_CHAR* pBuffer, 
                                          unsigned long cbBuffer, 
                                          const ClientLocale& rLocale ) const;

   /**
    * Set the fields of this object from a character buffer.  The buffer
    * is formatted such that the individual fields are contiguous and the
    * whole buffer is terminated with a NULL character.
    * 
    * @param pBuffer   pointer to the buffer to use to set the fields of the BFData object.
    * @param cbBuffer  Count of characters in pBuffer.  Use -1 if pBuffer is to be treated as a NULL terminated string.
    * @param cchFixed  Count of characters in the fixed view.
    * @param cRepeats  Number of repeats.
    * @param cchRepeat Count of characters in an instance of the repeat view.
    * 
    * @return The total number of I_CHARs which were copied from pBuffer.
    */
   unsigned long setFromCharBuffer( const I_CHAR* pBuffer, 
                                    long cchBuffer,
                                    unsigned long cchFixed,
                                    unsigned long cRepeats,
                                    unsigned long cchRepeat );

   /**
    * Gets the first repeat BFData object if the object has repeats and
    * the specified id corresponds to the expected repeat object.
    * 
    * @param id     the data dictionary id of the BFData repeat object to get.
    * 
    * @return a const reference to a Data object.
    * @exception BFDataRepeatNotFoundException&
    *                   there is no repeat of the specified id
    * @see getRepeat
    * @deprecated This method is superceded by getRepeat()
    */
   const BFData &getData( unsigned long id ) const;

   /**
    * Gets the BFDataElementProperties for the specified field.
    * 
    * @param id     id of field.
    * 
    * @return a const pointer to a BFDataElementProperties object.  NULL will be
    *         returned if field does not exist.
    */
   const BFDataFieldProperties *getElementProperties( const BFFieldId& id ) const;

   /**
    * Gets the BFDataElementProperties for the specified field.
    * 
    * @param name   name of field.
    * 
    * @return a const pointer to a BFDataElementProperties object.  NULL will be
    *         returned if field does not exist.
    */
   const BFDataFieldProperties *getElementProperties( const DString &name ) const;


   /**
    * Gets the value of a field in the BFData object.
    * 
    * @param id         the data dictionary id of the field.
    * @param outputValue
    *                   a DString to fill with the field's value.
    * @param formatFlags
    *                   flags for specifying if the masked or substituted value should be retrieved.
    *                   Use a combination of BFDataField::USE_MASKS and BFDataField::USE_SUBSTITUTES.
    *                   Use 0 to get raw values.
    * @param i18nFormat Pass in a custom mask string.
    * 
    * @return a reference to a DString containing the value
    *         of the specified element (the one that was passed in).
    */
   DString &getElementValue( const BFFieldId& id,
                             DString &outputValue,
                             unsigned long formatFlags = 0L,
                             const DString &i18nFormat = EMPTY_STRING ) const;


   /**
    * Get a BFDataField from this object.
    * 
    * @param id     the id of the field to get.
    * 
    * @return A reference to the BFDataField object which corresponds to the specified field.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   BFDataField& getElement( const BFFieldId& id );

   /**
    * Get a BFDataField from this object.
    * 
    * @param id     the id of the field to get.
    * 
    * @return A const reference to the BFDataField object which corresponds to the specified field.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   const BFDataField& getElement( const BFFieldId& id ) const;


   /**
    * Gets the value of a field in the BFData object.
    * 
    * @param name       The name of the field to get.
    * @param formatFlags
    *                   flags for specifying if the masked or substituted value should be retrieved.
    *                   Use a combination of BFDataField::USE_MASKS and BFDataField::USE_SUBSTITUTES.
    *                   Use 0 to get raw values.
    * @param i18nFormat Pass in a custom mask string.
    * 
    * @return a DString containing the value of the specified element.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   DString getElementValue( const DString &name, 
                            unsigned long formatFlags = 0L,
                            const DString &i18nFormat = EMPTY_STRING ) const;


   /**
    * Gets the value of a field in the BFData object.
    * 
    * @param name       The name of the field to get.
    * @param outputValue
    *                   a DString to fill with the field's value.
    * @param formatFlags
    *                   flags for specifying if the masked or substituted value should be retrieved.
    *                   Use a combination of BFDataField::USE_MASKS and BFDataField::USE_SUBSTITUTES.
    *                   Use 0 to get raw values.
    * @param i18nFormat Pass in a custom mask string.
    * 
    * @return a reference to a DString containing the value
    *         of the specified element (the one that was passed in).
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   DString& getElementValue(
                           const DString &name,
                           DString &outputValue,
                           unsigned long formatFlags = 0L,
                           const DString &i18nFormat = EMPTY_STRING 
                           ) const;



   /**
    * Gets the value of a field in the BFData object.
    * 
    * @param id         the id of the field to get.
    * @param formatFlags
    *                   flags for specifying if the masked or substituted value should be retrieved.
    *                   Use a combination of BFDataField::USE_MASKS and BFDataField::USE_SUBSTITUTES.
    *                   Use 0 to get raw values.
    * @param i18nFormat Pass in a custom mask string.
    * 
    * @return a DString containing the value of the specified element.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   DString getElementValue( const BFFieldId& id, 
                            unsigned long formatFlags = 0L,
                            const DString &i18nFormat = EMPTY_STRING ) const;

   /**
    * Get the BFFieldId object associated with the specified name.
    * 
    * @param name   name to search for
    * 
    * @return a reference to the BFFieldId object.
    * @exception BFFieldIdUnknownException&
    *                   the specified field is not in this BFData object
    */
   const BFFieldId& getFieldIdFromName( const DString &name ) const;

   /**
    * Returns the field name for the specified field.
    * 
    * @param id     The field in question.  If the field is not in this BFData object
    *               then an exception is thrown.
    * 
    * @return reference to the field's name .
    * @exception BFFieldIdUnknownException&
    *                   the specified field is not in this BFData object
    */
   const DString& getFieldNameFromId( const BFFieldId& id ) const;

   /**
    * Return a copy of the BFDataId object which identifies this BFData object.
    * 
    * @return a copy the BFDataId object which identifies this BFData object.
    */
   BFDataId getId() const;

   /**
    * Get the length of the largest possible field from
    * this BFData object.
    * 
    * @return the length, in characters, of the largest field in this BFData object.
    *         Any extra fields are considered.
    */
   unsigned long getMaxLength() const;

   /**
    * Returns the name of this BFData object.
    * 
    * @return a string containing the properties name.
    */
   const DString &getName() const;

   /**
    * Gets the BFData object at the specified index in the repeat
    * area.
    * 
    * @param repeatIndex
    *               specifies the 0-based index of the BFData object in the repeat area to return.
    * 
    * @return a const reference to the BFData object at the specified index in the repeat area.
    * @exception ConditionException&
    *                   the Data object has no repeats, or if
    *                   the specified index is greater than the number of repeats, or
    *                   the index is less than zero.
    * @exception BFDataRepeatNotFoundException&
    *                   the index specified is out-of-range.
    */
   const BFData& getRepeat( unsigned long repeatIndex ) const;

   /**
    * Get the BFDataId object which identifies the defined repeat object for this
    * BFData object.  There do not have to be any actual repeat objects in this
    * BFData object for the BFDataId object to be returned.
    * 
    * @return The BFDataId object.  If this BFData object has no defined repeat object 
    *         then ifds::NullDataId is returned.
    */
   const BFDataId& getRepeatId() const;

   /**
    * Returns the number of repeat BFData objects.
    * 
    * @return an unsigned long containing the number of repeat records in this BFData object.
    *         This method will return 0 if this BFData object does not support repeats.
    */
   unsigned long getRepeatCount() const;

   /**
    * Takes a BFData object as a parameter, and sets the values of the
    * elements of the input BFData object to the values of the
    * corresponding elements in the this Data object.  Any
    * elements of the input BFData object that don't have
    * corresponding elements in this Data object, are not set.
    * 
    * @param data - (in/out) a reference to the input BFData object.  If the
    *        elements in the input BFData object already have values, they
    *        will be overwritten by corresponding values in this BFData
    *        object.
    * @return a boolean specifying whether all of the elements in
    *         the input BFData object were found in this BFData object.
    *
    */
   bool getSelectedValues( BFData &data );

   /**
    * Get the maximum amount of storage required to
    * hold the contents of this object (if it was
    * streamed into a buffer, for example)
    * 
    * @return the maximum size in bytes.
    */
   unsigned long getTotalMaxByteLength() const;



   /**
    * Checks if value of specified field is the default value.
    * 
    * @param id - id of field to check
    * 
    * @return true if the field's value is the default value.
    *
    */
   bool isDefault( const BFFieldId& id ) const;

   /**
    * Checks if value of specified field is the default value.
    * 
    * @param name - name of field to check
    * 
    * @return true if the field's value is the default value.
    *
    */
   bool isDefault( const DString &name ) const;


   /**
    * Checks if all of the fields in this BFData object have
    * their default values.  This method does not check the values in
    * contained repeat BFData objects.
    * 
    * @return true if all of the fields have their default values, false if they don't.
    */
   bool isDefault( ) const;

   /**
    * Removes all records from the repeat area.
    * 
    */
   void removeAllRepeats();

   /**
    * Removes a BFData object from the repeat area of this BFData
    * object.
    * 
    * @param removeAt 0-based index of the BFData object to remove from the repeat area.
    * 
    * @return true if the BFData object was successfully removed from the repeat area, 
    *         false if the index was out of range.
    */
   bool removeRepeat( unsigned long removeAt );


   /**
    * Resets all of the BFData fields in this BFData object to
    * their default values.
    * 
    * deletes all string fields, extra fields, and repeats.
    */
   void reset();

   /**
    * Resets all of the fields in this BFData object to
    * their default values.
    */
   void resetValue();

   /**
    * Resets the specified field to its default value.
    * 
    * @param id - contains the id of the field to reset.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   void resetElementValue( const BFFieldId& id );

   /**
    * Resets the specified Data Element to it's default value.
    * 
    * @param componentName
    *               - contains the name of the field to reset.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   void resetElementValue( const DString &componentName );

   /**
    * Sets the specified field to the passed-in value.  Preferred version
    *  for efficiency.
    * 
    * @param id         the data dictionary id of the field.
    * @param value      the value.
    * @param eAppend    Specifies how the field should be appended.<br>
    *                   <ul>
    *                   <li>NO_APPEND: error if field doesn't exist
    *                   <li>APPEND: add element, no search of data dictionary properties is performed.
    *                   </ul>
    * @param bReserved  ignored.
    * @param i18nFormat A custom mask string to remove.
    * 
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    */
   bool setElementValue( const BFFieldId& id,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool bReserved = true,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Set the field which corresponds to the specified BFDataField object.
    * The field must already exist in this BFData object.
    * 
    * @param fld    A reference to a BFDataField object.  The field in this BFData object
    *               which corresponds to this field will be given the new value.
    * 
    * @return true if the field was found and its value was set.  false if
    *         the field was not found.
    */
   bool setElementValue( const BFDataField& fld )
   {
      BFDataField* pDF = _getElement( fld.getId() );
      if( NULL != pDF )
      {
         *pDF = fld;
         return( true );
      }
      return( false );
   }

   /**
    * Sets the specified field to the passed-in value.  Preferred version
    *  for efficiency.
    * 
    * @param name       the data dictionary name of the field.
    * @param value      the value.
    * @param eAppend    Specifies how the field should be appended.<br>
    *                   <ul>
    *                   <li>NO_APPEND: error if field doesn't exist
    *                   <li>APPEND: add element, no search of data dictionary properties is performed.
    *                   </ul>
    * @param bReserved  ignored.
    * @param i18nFormat A custom mask string to remove.
    * 
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    *         Sets the specified DataElement to the passed-in value.  Preferred version
    *         for efficiency.
    */
   bool setElementValue( const DString &name,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool bReserved = true,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Sets the specified field to the passed-in value.  Preferred version
    *  for efficiency.
    * 
    * @param id         the data dictionary id of the field.
    * @param value      the value.
    * @param bAppendNew true if the field should be appended if it does not exist in this BFData object.
    * @param bReserved  ignored.
    * @param i18nFormat A custom mask string to remove.
    * 
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    */
   bool setElementValue( const BFFieldId& id,
                         const DString &value ,
                         bool bAppendNew = false,
                         bool bReserved = true,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Sets the specified field to the passed-in value.  Preferred version
    *  for efficiency.
    * 
    * @param name       the data dictionary name of the field.
    * @param value      the value.
    * @param bAppendNew true if the field should be appended if it does not exist in this BFData object.
    * @param bReserved  ignored.
    * @param i18nFormat A custom mask string to remove.
    * 
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    */
   bool setElementValue( const DString& name,
                         const DString& value ,
                         bool bAppendNew = false,
                         bool bReserved = true,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Set the default locale for this BFData object.
    * 
    * @deprecated BFData objects no longer store their ClientLocale object.  Use ClientLocaleContext::get()
    *             to retrieve the current ClientLocale for the thread.
    */
   void setLocale( ) { return;}

   /**
    * Sets the repeat count.  This call will reserve room in the repeat storage.
    * 
    * @param repeatCount - (in) the new repeat count.
    *
    */
   void setRepeatCount( unsigned long repeatCount );

   /**
    * Sets the values of the elements in this BFData object according
    * to the name=value pairs in the idiString.
    * 
    * @param idiString contains element-value pairs.
    * @param appendNew specifies that if field in the idiString don't exist in this BFData object, create them.
    * @param ignoreOnNoAppend
    *                  specifies that, if one of the elements in the idiString doesn't exist,
    *                  and appendNew is false, the function should return false.  If set to false,
    *                  and appendNew is false, new elements will not be added, and the
    *                  function will return true.
    * 
    * @return true if all of the fields had their values set, or if they didn't 
    *         exist and they were appended, or if they didn't exist and ignoreOnNoAppend
    *         was set to true.
    */
   bool setValues( const DString &idiString, bool appendNew = false, bool ignoreOnNoAppend = true );

   /**
    * Sets the values of the elements in this BFData object according
    * to the fields in another BFData object.
    * 
    * @param data      The BFData object to use as a source for field values.  Only pre-defined fields are considered.
    * @param appendNew specifies that if field in the idiString don't exist in this BFData object, create them.
    * @param ignoreOnNoAppend
    *                  specifies that, if one of the fields in the idiString doesn't exist,
    *                  and appendNew is false, the function should return false.  If set to false,
    *                  and appendNew is false, new elements will not be added, and the
    *                  function will return true.
    * 
    * @return true if all of the fields had their values set, or if they didn't
    *         exist and they were appended, or if they didn't exist and ignoreOnNoAppend
    *         was set to true.
    */
   bool setValues( const BFData &data, bool appendNew = false, bool ignoreOnNoAppend = true );

   /**
    * Add a copy of the specified field onto this BFData object.
    * 
    * @param dataEl - the source field.
    */
   void addElement( BFDataField &dataEl );


   /**
    * Add a field to this BFData object using a field id and a string value.
    * 
    * @param id     The field id to add
    * @param value  the value of the field to add
    * @param bDisplayFormat
    *               true if value is currently in display format.
    */
   void addElement( const BFFieldId& id, const DString& value, bool bDisplayFormat );

   /**
    * Get the number of pre-defined fields in this BFData object.
    * 
    * @return The number of pre-defined fields.
    */
   unsigned int getFieldCount() const;

   /**
    * Get a field using a 0-based index.
    * 
    * @param idx    The 0-based index of the pre-defined field to retrieve.
    * 
    * @return A const reference to the BFDataField object.
    * @exception BFDataFieldNotFoundException&
    *                   the specified field is not in this BFData object
    */
   const BFDataField& getElementByIndex( unsigned int idx ) const;

   /**
    * Copy all fields from this BFData object to the specified BFData object.
    * 
    * @param pTarget The BFData object to copy this BFData object's fields to.
    */
   void commit( BFData* pTarget );

   /**
    * A map of fields which are not defined in the Data Dictionary.
    */
   typedef std::map< BFFieldId, BFDataField* > ExtraFieldsMap;
   typedef std::map< BFFieldId, BFDataField* >::iterator ExtraFieldsMap_Iter;
#if _MSC_VER >= 1300
   typedef std::map< BFFieldId, BFDataField* >::const_iterator ExtraFieldsMap_Const_Iter;
#else
   typedef std::map< BFFieldId, BFDataField* >::iterator ExtraFieldsMap_Const_Iter;
#endif

   /**
    * A map of 'fields' which have no Data Dictionary entry.  
    * 
    * @deprecated Non-data dictionary fields will not be supported with release 3.0 
    *             of the Core components.
    */
//CP20030312   typedef std::map< DString, DString > ExtraStringFieldsMap;
//CP20030312   typedef std::map< DString, DString >::iterator ExtraStringFieldsMap_Iter;
//CP20030312#if _MSC_VER >= 1300
//CP20030312   typedef std::map< DString, DString >::const_iterator ExtraStringFieldsMap_Const_Iter;
//CP20030312#else
//CP20030312   typedef std::map< DString, DString >::iterator ExtraStringFieldsMap_Const_Iter;
//CP20030312#endif

   /**
    * The repeat objects which belong to this BFData object.
    */
   typedef std::vector< BFData* > RepeatVector;
   typedef std::vector< BFData* >::iterator RepeatVector_Iter;
#if _MSC_VER >= 1300
   typedef std::vector< BFData* >::const_iterator RepeatVector_Const_Iter;
#else
   typedef std::vector< BFData* >::iterator RepeatVector_Const_Iter;
#endif

private:
   /**
    * Get a pointer to the BFDataField object corresponding to the BFFieldId object.
    * 
    * @param id     The field id to retrieve.
    * 
    * @return A pointer to the BFDataField object.  NULL if not found.
    */
   BFDataField* _getElement( const BFFieldId& id );

   /**
    * Get a pointer to the BFDataField object corresponding to the BFFieldId object.
    * 
    * @param id     The field id to retrieve.
    * 
    * @return A const pointer to the BFDataField object.  NULL if not found.
    */
   const BFDataField* _getElement( const BFFieldId& id ) const;

   /**
    * Get a pointer to the BFDataField object corresponding to the 0-based index.
    * 
    * @param idx    The 0-based index of the pre-defined field to retrieve.
    * 
    * @return A pointer to the BFDataField object.  NULL if not found.
    */
   BFDataField* _getElementByIndex( unsigned int idx ); 

   /**
    * Get a pointer to the BFDataField object corresponding to the 0-based index.
    * 
    * @param idx    The 0-based index of the pre-defined field to retrieve.
    * 
    * @return A pointer to the BFDataField object.  NULL if not found.
    */
   const BFDataField* _getElementByIndex( unsigned int idx ) const;

   /**
    * Remove the extra fields from this BFData object.
    */
   void removeExtraFields();

//CP20030312   /**
//CP20030312    * Remove the extra non-property fields from this BFData object.
//CP20030312    */
//CP20030312   void removeExtraStringFields();

   static const DString EMPTY_STRING;

private:
   /**
    * Pointer to the generated implementation object for this BFData object.
    */
   BFDataImpl*             pImpl_;

           /**
            * The fields which were added to this BFData object.  These fields 
            * have valid BFFieldId objects associated with them so they have
            * Data Dictionary properties.
            */
   mutable ExtraFieldsMap*         pExtraFields_;

//CP20030312           /**
//CP20030312            * The fields which added to this BFData object which do not have Data
//CP20030312            * Dictionary properties.
//CP20030312            */
//CP20030312   mutable ExtraStringFieldsMap*   pExtraStringFields_;

           /**
            * The BFData repeats associated with this BFData object.
            */
   mutable RepeatVector*           pRepeats_;

   RepeatVector& getRepeatVector() const 
   {
      if( NULL == pRepeats_ )
      {
         pRepeats_ = new RepeatVector();
      }
      return( *pRepeats_ );
   }

   ExtraFieldsMap& getExtraFieldsMap() const
   { 
      if( NULL == pExtraFields_ )
      {
         pExtraFields_ = new ExtraFieldsMap();
      }
      return( *pExtraFields_ );
   }

//CP20030312   ExtraStringFieldsMap& getExtraStringFieldsMap() const
//CP20030312   { 
//CP20030312      if( NULL == pExtraStringFields_ )
//CP20030312      {
//CP20030312         pExtraStringFields_ = new ExtraStringFieldsMap();
//CP20030312      }
//CP20030312      return( *pExtraStringFields_ );
//CP20030312   }

// Implementation Factory stuff
public:
   static void setImplFactory( BFDataImplFactory* pImplFactory );
   static BFDataImplFactory* getImplFactory( void );
private:
   static BFDataImplFactory* s_pImplFactory_;

// Field Exists stuff
public:
   static void setExistsObject( BFDataFieldExists* pExistsClass );
   static BFDataFieldExists* getExistsObject( void );
private:
   static BFDataFieldExists* s_pExists_;

public:
   static unsigned long getDefaultMarket();
   static unsigned long getDefaultClient();
   static const DString& getDefaultLocale();     // in enUS form


private:
   class DataStream;
   class BufferStream;
   class InStream;
   class OutStream;

};

typedef std::map<DString, const BFData *, std::less<DString> > BFDataPtrMap;
typedef BFDataPtrMap::iterator BFDataPtrMap_Iterator;
#if _MSC_VER >= 1300
typedef BFDataPtrMap::const_iterator BFDataPtrMap_Const_Iter;
#else
typedef BFDataPtrMap::iterator BFDataPtrMap_Const_Iter;
#endif

typedef std::map<DString, BFData, std::less<DString> > BFDataObjMap;
typedef BFDataObjMap::iterator BFDataObjMap_Iterator;
#if _MSC_VER >= 1300
typedef BFDataObjMap::const_iterator BFDataObjMap_Const_Iter;
#else
typedef BFDataObjMap::iterator BFDataObjMap_Const_Iter;
#endif




//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfdata/bfdata.hpp-arc  $
//
//   Rev 1.12   Mar 14 2003 08:36:54   PURDYECH
//Added support for variable length fields and dynamic fieldIds.
//Removed 'extra string fiields' support as dynamic fieldIds allows arbitrary fields to be added to the 'extra fields'
//Fixed some parameter names (cosmetic)
//
//   Rev 1.11   Feb 13 2003 09:48:36   PURDYECH
//Documentation changes for doxygen
//
//   Rev 1.10   Oct 30 2002 15:19:30   PURDYECH
//new signature for setCharFromBuffer().
//
//   Rev 1.9   Oct 09 2002 17:40:26   PURDYECH
//New PVCS Database
//
//   Rev 1.8   Aug 29 2002 12:51:02   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.7   Jun 07 2002 15:29:42   PURDYECH
//Make BFConstDataFieldIter a friend
//
//   Rev 1.6   Jun 06 2002 17:15:28   PURDYECH
//added reset/remove methods to clean up object during assignment.
//
//   Rev 1.5   Jun 05 2002 14:41:06   ROSIORUC
//CP - Fixed the "fixes" to the FAST stream handling
//
//   Rev 1.4   May 30 2002 12:10:48   PURDYECH
//Fixed a problem with BFData::getAsUnsignedCharBuffer
//
//   Rev 1.3   May 28 2002 12:17:18   PURDYECH
//BFData Implementation - Phase II
//
