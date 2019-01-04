#ifndef DATA_HPP
#define DATA_HPP

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

/**@pkg DIDBRKR */        // TAG DIRECTIVE FOR HTML PACKAGING - REPLACE THE COMPONENT NAME (ALL CAPS)

#pragma message( "including "__FILE__ )

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

#ifndef DATACOMPONENT_HPP
   #include "datacomponent.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef INCLUDED_ISTREAM
#define INCLUDED_ISTREAM
   #include <istream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_OSTREAM
#define INCLUDED_OSTREAM
   #include <ostream>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
   #include <vector>
#endif

#define DEFAULT_REPEAT_RECORD I_("Repeat_Record")

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class DIDBRKR_LINKAGE DataProperties;
class DIDBRKR_LINKAGE DataElementProperties;
class DIDBRKR_LINKAGE PropertyRepository;
class ClientLocale;


/**
 * A Data object is a set of attribute-value pairs.  Data encapsulates the
 * actual stored format, offset, fill characters, etc. of attributes.
 *
 * Users of the Data object only need to know the names of the attributes, and
 * their valid formats.  Data will return an error if a value being set has an
 * invalid format.  It will also return an error if an invalid format is
 * requested.
 *
 * Data's identifier is a either a long int or a string ID that corresponds to
 * an external description of a Data instance’s contents.  When Data is
 * instantiated, the ID is used to retrieve the Data description.  A data
 * description contains the Data instance's attribute names, types, etc.
 *
 * These descriptions are locale dependent and may be setup to be different for
 * different locales.
 *
 * --- Repeat Records ---
 *
 * To access a Data object's repeat records, you must first get the object's
 * "Repeat_Record" ( use Data::DEFAULT_REPEAT_RECORD ) object.  Then, you use
 * that object to access the repeats.  Here is an example:
 *
 *   Data mySignon( "signon2.vw" );
 *   string fundName;
 *   ...
 *   fundName = mySignon.getData( Data::DEFAULT_REPEAT_RECORD ).getRepeat(1).
 *                                        getElementValue( "Authview_Fdname1" );
 *
 * @author DST Systems Inc
 */


class DIDBRKR_LINKAGE Data : public DataComponent
{
   // Streams in\out of native formats (view buffer, file, etc.)...
   friend EXPORTWIN std::istream & EXPORTOS2 operator>> ( std::istream &stream,
                                                       Data &data );
   friend EXPORTWIN std::ostream & EXPORTOS2 operator<< ( std::ostream &stream,
                                                       const Data &data );
   friend class DataIter;
   friend class DataPropertiesImpl;
   #ifdef DST_UNICODE
   // These methods are only here for backward compatibility for DSTC and are
   //  deprecated because they will not work correctly for binary data types
   friend EXPORTWIN i_istream & EXPORTOS2 operator>> ( i_istream &stream, Data &data );
   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< ( i_ostream &stream, const Data &data );
   #endif

public:
   // Used to control the append mode for setElementValue method
   enum EAPPEND_MODE
   {
      NO_APPEND,
      APPEND,
      APPEND_FROM_PROPERTIES
   };

   /**
    * Creates a "propertyless" data object.  This behaves
    * essentially like a map of strings.
    */
   Data();

   /**
    * Creates a new Data object identical to the one passed in.
    *
    * @param copy - (in) Data object to create the new one from.
    * @exception ConditionException& out of memory
    */
   Data( const Data &copy );

   /**
    * Constructor for Data objects.
    *
    * @param propertiesId
    *                  - (in) name of the DataProperties object
    *                  that contains the properties for this Data object.
    * @param idiString - (in) contains name and value pairs for the
    *                  attributes of this Data object.  Defaults to empty string.
    * @param appendNew - (in) if true, any attributes in the idiString that are
    *                  not in the Data object, will be appended as new DataElement
    *                  objects.  Defaults to false.
    * @param ignoreOnNoAppend
    *                  - (in) if false, and appendNew is false, and
    *                  there are attributes in the idiString that are
    *                  not already in the Data object, an exception will
    *                  be thrown.  Defaults to true.
    * @param clientLocale - the locale/market/client combination for the
    *                  properties
    * @exception ConditionException&
    *                   if some of the values in idiString are
    *                   not valid for their attributes, or if the above
    *                   ignoreOnNoAppend condition is met.
    *                   ConditionException& out of memory
    */
   Data( const DString &propertiesId, const DString &idiString = EMPTY_STRING,
         bool appendNew = false, bool ignoreOnNoAppend = true,
         const ClientLocale &clientLocale =
            ClientLocale::getDefaultClientLocale() );

   /**
    * Constructor for Data objects.
    *
    * @param lId    - (in) name of the DataProperties object that
    *               contains the properties for this Data object.
    * @param idiString - (in) contains name and value pairs for the
    *                  attributes of this Data object.  Defaults to empty string.
    * @param appendNew - (in) if true, any attributes in the idiString that are
    *                  not in the Data object, will be appended as new DataElement
    *                  objects.  Defaults to false.
    * @param ignoreOnNoAppend
    *                  - (in) if false, and appendNew is false, and
    *                  there are attributes in the idiString that are
    *                  not already in the Data object, an exception will
    *                  be thrown.  Defaults to true.
    * @param clientLocale - the locale/market/client combination for the
    *                  properties
    * @exception ConditionException&
    *                   if some of the values in idiString are
    *                   not valid for their attributes, or if the above
    *                   ignoreOnNoAppend condition is met.
    *                   ConditionException& out of memory
    */
   Data( unsigned long lId, const DString &idiString = EMPTY_STRING,
         bool appendNew = false, bool ignoreOnNoAppend = true,
         const ClientLocale &clientLocale =
            ClientLocale::getDefaultClientLocale() );

   virtual ~Data();

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)
          PVOID operator new (size_t nBytes);
          VOID operator delete (PVOID pv);
#endif

   /**
    * Returns the repeat Data object at the specified index.
    *
    * @param index - (in) specifies which repeat to get.
    * @return a reference to the Data object at the specified index
    *         in the repeat area.
    * @exception ConditionException& if the Data object has no repeats, or if
    *            the specified index is out of range.
    *            ConditionException& out of memory
    *
    */
   Data& operator[]( unsigned int index );

   /**
    * Assigns one Data object to another.
    *
    * @param copy   original
    * @return
    * @exception ConditionException& if the properties for the two Data
    *                objects don't match, or if one object has properties and
    *                the other doesn't.
    *            ConditionException& out of memory
    *
    */
   Data &operator= ( const Data &copy );

   /**
    * Tests if two Data objects are equal.
    *
    * @param data - (in) reference to the Data object to compare against
    *        this data object.
    * @return a boolean, true if the two Data objects are equal,
    *         false if the two object are not equal, and false if the
    *         properties for the two objects are not equal.
    *
    */
   bool operator== ( const Data &data ) const;

   /**
    * Tests if two Data objects are not equal.
    *
    *
    * @param data - (in) reference to the Data object to compare against
    *        this data object.
    * @return a boolean, true if the two Data objects are not equal.
    *
    */
   bool operator!= ( const Data &data ) const { return !(*this == data); };

   // These are DataComponent operations instead of Data so that either can
   // be accessed with the same operations

   /**
    * Adds a Data object to the repeat area of this Data object.
    *
    * @param copyData - (in) the Data object to create a copy of and
    *        insert into the repeat area.
    * @return a boolean:  true if the Data object was successfully
    *         added to the repeat area, false otherwise.
    * @exception ConditionException& out of memory
    *
    */
   bool addRepeat( const Data &newRepeat );

   /**
    * Adds all of the Data objects in the repeat area of the
    * input Data object to the repeat area of this Data object.
    *
    * @param data - (in) the Data object to get the repeat data from
    * @param overwriteFixedArea - (in) if true, then the fixed area of the
    *        "this" object is overwritten with the fixed area from the
    *        input data object "data".  Defaults to false.
    * @return true if the Data objects were added to the
    *         repeat area, false otherwise, or false if ignoreFixedArea is
    *         false and the values of the elements in the fixed area are not
    *         equal for the two objects.
    * @exception ConditionException& one or both of the Data objects do not
    *            have repeat areas
    *
    */
   bool appendRepeatData( const Data &data,  bool overwriteFixedArea = false );

   /**
    * Takes the repeat records from the input parameter
    * data object and moves them to the *this object, appending them to any
    * repeats already present. The repeatable areas are moved using pointer
    * assignment for low overhead.
    *
    * Note that after this method is called, the input
    * data object will have an empty repeat area.
    *
    * Both the *this object and the input parameter must
    * be repeatable objects with the same properties.
    *
    * @param data   - The data object that has the repeat records
    *               to move.
    * @return true if successful, false if source data object had no repeats
    *         to copy.
    * @exception ConditionException&
    *                   one or both of the Data objects do not
    *                   have repeat areas
    *            ConditionException&
    *                   the data objects do not have the same properties
    */
   bool moveRepeatData( Data &data );

   /**
    * Checks if the component specified in the parameter
    * componentName exists in the _dataMap of this Data object.
    *
    * @param componentName - (in) contains the name of the component
    *        to check for.
    * @return a boolean:  true if the specified component exists,
    *         false if it doesn't.
    *
    */
   bool exists( const DString &componentName ) const;

   /**
    * Checks if the component specified in the parameter
    * componentName exists in the _dataMap of this Data object.
    *
    * @param id - (in) the data dictionary id of the component
    * @return a boolean:  true if the specified component exists,
    *         false if it doesn't.
    *
    */
   bool exists( unsigned long id ) const;

   /**
    * Searches the Data object's repeats for the first repeat
    * record whose element values match those in the IDIKeysValue
    * parameter.
    *
    *  ^EXAMPLE : const Data &repeatData =
    *                                  dataWithRepeats.getData("Repeat_Record");
    *             long index = repeatData.findRepeatIndex("name=value;");
    *
    *  ^SEE ALSO : Overridden from DataComponent
    *
    * @param IDIKeysValue - (in) contains the name and value pairs to
    *        search for.
    * @param startIndex - (in) the index to start the search at.  Defaults to
    *        zero.
    * @return a signed long that is the index of the found repeat
    *         in the repeat area.  If no repeat is found that matches the
    *         name and value pairs in IDIKeysValue, -1L is returned.
    *
    */
   virtual long findRepeatIndex( const DString &IDIKeysValue,
                                 unsigned long startIndex = 0L ) const;

   /**
    * Fills up the parameter idiString with the name and value
    * pairs for all of the elements in the _dataMap of this Data
    * object.
    *
    * @param idiString - (out) gets filled up with the name and value pairs
    * @param insertEOLs - (in) specifies if there should be an end-of-line
    *        marker added after each name-value pair in idiString
    * @param usePropertiesOrder - (in) specifies the name-value pairs be added
    *        to the idiString in the order in which they
    *        appear in the properties list
    * @param flags - (in) set of flags for specifying if the retrieved
    *        values are substituted or masked.  Substituted values refer to
    *        elements in the properties file that have "0=No;1=Yes"
    *        substitution maps defined.  Masked values refer to elements in
    *        the properties file that have "DSTMASK=$$$,$$$,$$$.9999" masks
    *        defined.  The flags are DataElement::USE_SUBSTITUTES and
    *        DataElement::USE_MASK.
    * @param pClientLocale - the locale/market/client combination for the
    *        properties
    *
    */
   void getAllValues( DString &idiString, bool insertEOLs = false,
                      bool usePropertiesOrder = false,
                      unsigned long flags = 0L,
                      const ClientLocale *plientLocale = 0 ) const;

   /**
    * @param buffer - the buffer that will receive the data.
    * @param buffLength - the size of the buffer in bytes.
    * @return true if succeeded, false for failure.
    */
   bool getAsUnsignedCharBuffer( char *buffer,
                                 unsigned long buffLength ) const;

   /**
    * Gets the Data or DataElement object specified in the parameter
    * componentName.  Only works for appended elements.
    *
    * @param componentName - (in) contains the name of the component
    *        to get.  This string must contain the name of a component of
    *        the Data object.
    * @return a const reference to a DataComponent object.
    * @exception ConditionException& the component specified in componentName
    *            is not a component of this Data object.
    *
    */
   const DataComponent &getComponent( const DString &componentName ) const;

   /**
    * Gets the Data or DataElement object specified in the parameter
    * componentName.  Only works for appended elements
    *
    * @param id - (in) the data dictionary id of the component
    *        to get.
    * @return a const reference to a DataComponent object.
    * @exception ConditionException& the component specified in componentName
    *            is not a component of this Data object.
    *
    */
   const DataComponent &getComponent( unsigned long id ) const;

   /**
    * Returns the number of components in the _dataMap of this Data
    * object. Repeat area field counts as one.
    *
    * @return an unsigned long set to the number of components
    *         in the _dataMap of this Data object.
    *
    */
   unsigned long getComponentCount() const;

   /**
    * Gets the Data object specified in the parameter componentName
    * from the _dataMap of this Data object.
    *
    * @param componentName - (in) contains the name of the Data object
    *        to get.  This string must contain the name of a component of
    *        the Data object.
    * @return a const reference to a Data object.
    * @exception ConditionException& the component specified in componentName
    *            is not a Data component of this Data object.
    */
   const Data &getData( const DString &componentName ) const;

   /**
    * Gets the Data object specified in the parameter componentName
    * from the _dataMap of this Data object.
    *
    * @param id - (in) the data dictionary id of the Data object
    *        to get.
    * @return a const reference to a Data object.
    * @exception ConditionException& the component specified in componentName
    *            is not a Data component of this Data object.
    */
   const Data &getData( unsigned long id ) const;


   /**
    * Gets the DataProperties of this Data object.  Need to check for NULL on
    *  return since not required.
    *
    * @return a const pointer to a DataProperties object or NULL if none exists.
    */
   const DataProperties *getDataProperties() const;

   /**
    * Get the label for the DataElement.  This maps to the
    * locale-specific label on fields in the data dictionary.  This is the
    * preferred version for efficiency
    *
    * @param id - id of element
    * @param pClientLocale - the locale/client/market for the desired label
    * @return reference to the label
    */
   const DString &getElementLabel(
      unsigned long id,
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * Get the label for the DataElement.  This maps to the
    * locale-specific label on fields in the data dictionary.
    *
    * @param name - a string containing the desired component name
    * @param pClientLocale - the locale/client/market for the desinred label
    * @return reference to the label
    */
   const DString &getElementLabel(
      const DString &name,
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * Gets the DataElementProperties for the specified field.
    *
    * @param id - (in) id of field.
    * @return a const pointer to a DataElementProperties object.  NULL will be
    *  returned if field exists but doesn't have associated properties.
    * @exception ConditionException& field not found.
    */
   const DataElementProperties *getElementProperties(
      unsigned long id
      ) const;

   /**
    * Gets the DataElementProperties for the specified field.
    *
    * @param name - (in) name of field.
    * @return a const pointer to a DataElementProperties object.  NULL will be
    *  returned if field exists but doesn't have associated properties.
    * @exception ConditionException& field not found.
    */
   const DataElementProperties *getElementProperties(
      const DString &name
      ) const;

   /**
    * Gets the value of an element of the Data object.
    *
    * @param id     - (in) the data dictionary id of the DataElement object to get.
    * @param outputValue
    *                   - this will be filled with the value of the
    *                   element.
    * @param formatFlags
    *                   - (in) set of flags for specifying if the retrieved
    *                   values are substituted or masked.  Substituted values refer to
    *                   elements in the properties file that have "0=No;1=Yes"
    *                   substitution maps defined.  Masked values refer to elements in
    *                   the properties file that have "DSTMASK=$$$,$$$,$$$.9999" masks
    *                   defined.  The flags are DataElement::USE_SUBSTITUTES and
    *                   DataElement::USE_MASK.
    * @param pClientLocale - the locale/market/client combination for the
    *                   properties
    * @param i18nFormat - for i18n fields, this may be used to pass a
    *                   custom display format string
    * @return a const reference to a string containing the value
    *         of the specified element (the one that was passed in).
    * @exception ConditionException&
    *                   there is no element in the _dataMap of
    *                   this Data object with the name specified in elementName.
    *                   ConditionException& out of memory
    *                   ConditionException& invalid format string passed in
    */
   DString &getElementValue(
      unsigned long id,
      DString &outputValue,
      unsigned long formatFlags = 0L,
      const ClientLocale *pClientLocale = 0,
      const DString &i18nFormat = EMPTY_STRING
      ) const;

   /**
    * Gets the value of an element of the Data object.
    *
    * @param componentName
    *                   - (in) contains the name of the
    *                   element to return the value of.
    * @param formatFlags
    *                   - (in) set of flags for specifying if the retrieved
    *                   values are substituted or masked.  Substituted values refer to
    *                   elements in the properties file that have "0=No;1=Yes"
    *                   substitution maps defined.  Masked values refer to elements in
    *                   the properties file that have "DSTMASK=$$$,$$$,$$$.9999" masks
    *                   defined.  The flags are DataElement::USE_SUBSTITUTES and
    *                   DataElement::USE_MASK.
    * @param pClientLocale - the locale/market/client combination for the
    *                   properties
    * @param i18nFormat - for i18n fields, this may be used to pass a
    *                   custom display format string
    * @return a const reference to a string containing the value
    *         of the specified element.
    * @exception ConditionException&
    *                   there is no element in the _dataMap of
    *                   this Data object with the name specified in elementName.
    *            ConditionException& out of memory
    *            ConditionException& invalid format string passed in
    */
   DString getElementValue(
      const DString &name,
      unsigned long formatFlags = 0L,
      const ClientLocale *pClientLocale = 0,
      const DString &i18nFormat = EMPTY_STRING
      ) const;

   /**
    * Gets the value of an element of the Data object.
    *
    * @param componentName
    *                   - (in) contains the name of the
    *                   element to return the value of.
    * @param outputValue
    *                   - this will be filled with the value of the
    *                   element.
    * @param formatFlags
    *                   - (in) set of flags for specifying if the retrieved
    *                   values are substituted or masked.  Substituted values refer to
    *                   elements in the properties file that have "0=No;1=Yes"
    *                   substitution maps defined.  Masked values refer to elements in
    *                   the properties file that have "DSTMASK=$$$,$$$,$$$.9999" masks
    *                   defined.  The flags are DataElement::USE_SUBSTITUTES and
    *                   DataElement::USE_MASK.
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   format the returned data
    * @param i18nFormat - for i18n fields, this may be used to pass a
    *                   custom display format string
    * @return a const reference to a string containing the value
    *         of the specified element.
    * @exception ConditionException&
    *                   there is no element in the _dataMap of
    *                   this Data object with the name specified in elementName.
    *            ConditionException& out of memory
    *            ConditionException& invalid format string passed in
    */
   DString& getElementValue(
      const DString &name,
      DString &outputValue,
      unsigned long formatFlags = 0L,
      const ClientLocale *pClientLocale = 0,
      const DString &i18nFormat = EMPTY_STRING
      ) const;

   /**
    * Get the binary value of the element.
    *
    * @param id - (in) id of the element to get the value.
    * @param binBuff - the buffer to recive a copy of the data.
    * @param buffLength - the size of the buffer in bytes.
    * @param returnedLength
    *                   - after the method executes, this will contian
    *                   the number of bytes returned
    * @return true if successful, false otherwise
    */
   bool getElementValue(
      unsigned long id,
      unsigned char *binBuff,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;

   /**
    * Get the binary value of the element.  (Call's id version)
    *
    * @param name - (in) name of the element to get the value.
    * @param binBuff - the buffer to recive a copy of the data.
    * @param buffLength - the size of the buffer in bytes.
    * @param returnedLength
    *                   - after the method executes, this will contian
    *                   the number of bytes returned
    * @return true if successful, false otherwise
    */
   bool getElementValue(
      const DString &name,
      unsigned char *binBuff,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;

   /**
    * Gets the value of an element of the Data object.
    *
    * @param id - (in) the data dictionary id of the DataElement object to get.
    * @param formatFlags
    *                   - (in) set of flags for specifying if the retrieved
    *                   values are substituted or masked.  Substituted values refer to
    *                   elements in the properties file that have "0=No;1=Yes"
    *                   substitution maps defined.  Masked values refer to elements in
    *                   the properties file that have "DSTMASK=$$$,$$$,$$$.9999" masks
    *                   defined.  The flags are DataElement::USE_SUBSTITUTES and
    *                   DataElement::USE_MASK.
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   format the returned data
    * @param i18nFormat - for i18n fields, this may be used to pass a
    *                   custom display format string
    * @return a const reference to a string containing the value
    *         of the specified element.
    * @exception ConditionException& element not found
    *            ConditionException& out of memory
    *            ConditionException& invalid format string passed in
    */
   DString getElementValue( unsigned long id, unsigned long formatFlags = 0L,
                            const ClientLocale *pClientLocale = 0,
                            const DString &i18nFormat = EMPTY_STRING ) const;

   /**
    * Returns the associated id of the name passed in, looking in both data properties
    *  and the append map.
    *
    * @param name - name to search for
    *
    * @return the id - ULONG_MAX if not found
    */
   unsigned long getFieldIdFromName( const DString &name ) const;

   /**
    * Returns the associated name of the id passed in, looking in both data properties
    *  and the append map.
    *
    * @param name - id to search for
    *
    * @return reference to name or throw exception if not found
    */
   const DString &getFieldNameFromId( unsigned long id ) const;
   /**
    * Returns the data dictionary id of the data object.
    *
    * @return the id (the same value as _lid)
    */
   unsigned long getId() const;

   /**
    * Get the current locale for this component.
    *
    * @return the locale.
    */
   const ClientLocale& getLocale() const
   {
      return m_pLocale ? *m_pLocale : ClientLocale::getDefaultClientLocale();
   }

   /**
    * Get the length of the largest possible field from
    * this data object.
    *
    * @return the length
    */
   virtual unsigned long getMaxLength() const;

   /**
    * Returns the properties name of the Data object.
    *
    * @return a string containing the properties name.
    *
    */
   const DString &getName() const;

   /**
    * Gets the Data object at the specified index in the repeat
    * area.
    *
    * @param repeatIndex - (in) specifies the index of the Data
    *        object in the repeat area to return.
    * @return a const reference to the Data object at the specified
    *         index in the repeat area.
    * @exception ConditionException& the Data object has no repeats, or if
    *            the specified index is greater than the number of repeats, or
    *            the index is less than zero.
    *
    */
   const Data &getRepeat( unsigned long repeatIndex ) const;

   /**
    * Returns the number of repeat records.
    *
    * This should be called on the data object that is
    * returned from a call to
    * Data::getData( DEFAULT_REPEAT_RECORD ).
    *
    * @return an unsigned long containing the number of repeat
    *         records on the Data object.
    */
   virtual unsigned long getRepeatCount() const;

   /**
    * Takes a Data object as a parameter, and sets the values of the
    * elements of the input Data object to the values of the
    * corresponding elements in the this Data object.  Any
    * elements of the input Data object that don't have
    * corresponding elements in this Data object, are not set.
    *
    * @param data - (in/out) a reference to the input Data object.  If the
    *        elements in the input Data object already have values, they
    *        will be overwritten by corresponding values in this Data
    *        object.
    * @return a boolean specifying whether all of the elements in
    *         the input Data object were found in this Data object.
    *
    */
   bool getSelectedValues( Data &data );

   /**
    * Get the maximum amount of storage required to
    * hold the contents of this object (if it was
    * streamed into a buffer, for example)
    *
    * @return the maximum size in bytes.
    */
   unsigned long getTotalMaxByteLength() const;

   /**
    * This method is part of Data's polymorhic
    * interface. On Data objects, it will return a
    * string containing one space.
    *
    * @param valueOut - reference of string to put return value in.
    * @param formatFlags
    *                   - ignored in Data objects
    * @param pClientLocale - ignored in Data objects
    * @param i18nFormat - ignored in Data objects
    * @return reference of string passed in (with return value)
    */
   virtual DString &getValue( DString &valueOut, unsigned long formatFlags = 0L,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = EMPTY_STRING ) const;

   /**
    * This method is part of Data's polymorhic
    * interface. On Data objects, it will return a
    * string containing one space.
    *
    * @param formatFlags
    *                   - ignored in Data objects
    * @param pClientLocale - ignored in Data objects
    * @param i18nFormat - ignored in Data objects
    * @return the string " ".
    */
   virtual DString getValue( unsigned long formatFlags = 0L,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = EMPTY_STRING ) const;

   /**
    * Checks if value of specified field is the default value.
    *
    * @param id - id of field to check
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   check the data
    *
    * @return true if the field's value is the default value.
    *
    */
   bool isDefault(
      unsigned long id,
      const ClientLocale *rpClientLocale = 0
      ) const;

   /**
    * Checks if value of specified field is the default value.
    *
    * @param name - name of field to check
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   check the data
    *
    * @return true if the field's value is the default value.
    *
    */
   bool isDefault(
      const DString &name,
      const ClientLocale *rpClientLocale = 0
      ) const;

   /**
    * Checks if all of the Data Elements in this Data object have
    * their default values - does not check nested repeats or data sets or
    * appended elements.
    *
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   check the data
    *  ^SEE ALSO : Overridden from DataComponent
    *
    * @return true if all of the elements have their
    *         default values, false if they don't.
    *
    */
   virtual bool isDefault( const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Removes all records from the repeat area.
    *
    */
   void removeAllRepeats();

   /**
    * Removes a Data object from the repeat area of this Data
    * object.
    *
    * @param removeAt - (in) the index of the Data object to remove
    *        from the repeat area.
    * @return true if the Data object was successfully
    *         removed from the repeat area, false if the index was out of
    *         range.
    *
    */
   bool removeRepeat( unsigned long removeAt );

   /**
    * Resets all of the Data Elements in this Data object to
    * their default values.
    *
    * @param pClientLocale - the locale/market/client combination to be used to
    *                   format the data
    *  ^SEE ALSO : Overridden from DataComponent
    *
    */
   virtual void resetValue( const ClientLocale *pClientLocale = 0 );

   /**
    * Resets the specified Data Element to it's default value.
    *
    * @param id - (in) contains the id of the field to reset.
    * @param pClientLocale - the locale/market/client that has the desired
    *                   default value
    * @exception ConditionException&
    *                   the specified field does not exist.
    */
    void resetElementValue(
       unsigned long id,
       const ClientLocale *pClientLocale = 0
       );

   /**
    * Resets the specified Data Element to it's default value.
    *
    * @param componentName
    *               - (in) contains the name of the element to
    *               reset.
    * @param pClientLocale - the locale/market/client that has the desired
    *                   default value
    * @exception ConditionException&
    *                   the specified element does not exist.
    */
    void resetElementValue(
       const DString &componentName,
       const ClientLocale *pClientLocale = 0
       );

   /**
    * Turns on or off the flag that forces DataElements to only
    * accept values that are in their substitution maps.
    *
    * @param forceMatching - (in) specifies if force matching should be on or
    *        off.
    *
    */
   void setForceMatching( bool forceMatching );

   /**
    * Sets the specified DataElement to the passed-in value.  Preferred version
    *  for efficiency.
    *
    * @param id - (in) the data dictionary id of the element.
    * @param value  - (in) contains the value.
    * @param eAppend - (in) NO_APPEND = error if field doesn't exist
    *                       APPEND = add element, no search of data dictionary
    *                          properties is performed.
    *                       APPEND_FROM_PROPERTIES = add element with properties
    *                          from data dictionary.
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param pClientLocale - the locale/market/client combination that describes
    *                   the format of the passed in data
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    */
   bool setElementValue( unsigned long id,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool displayFormat = true,
                         const ClientLocale *pClientLocale = 0,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Sets the specified DataElement to the passed-in value.  Preferred version
    *  for efficiency.
    *
    * @param name - (in) the data dictionary name of the element.
    * @param value  - (in) contains the value.
    * @param eAppend - (in) NO_APPEND = error if field doesn't exist
    *                       APPEND = add element, no search of data dictionary
    *                          properties is performed.
    *                       APPEND_FROM_PROPERTIES = add element with properties
    *                          from data dictionary.
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param pClientLocale - the locale/market/client combination that describes
    *                   the format of the passed in data
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the element's value was set, false otherwise.
    *         If APPEND or APPEND_FROM_PROPERTIES is passed in, true also
    *         indicates successful append.
    */
   bool setElementValue( const DString &name,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool displayFormat = true,
                         const ClientLocale *pClientLocale = 0,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Sets the specified DataElement to the passed-in value.  Preferred version
    *  for efficiency.
    *
    * @param id - (in) the data dictionary id of the element.
    * @param value  - (in) contains the value.
    * @param appendNew - (in) specifies that, if elementName doesn't exist, to
    *                  create a default element and append it to this Data object.
    *                  Defaults to false.  true on this flag equates to APPEND above.
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param pClientLocale - the locale/market/client combination that describes
    *                   the format of the passed in data
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the element's value was set,
    *         true if the element was not found and appendNew is true,
    *         false otherwise.
    */
   bool setElementValue( unsigned long id,
                         const DString &value ,
                         bool appendNew = false,
                         bool displayFormat = true,
                         const ClientLocale *pClientLocale = 0,
                         const DString &i18nFormat = EMPTY_STRING);

   /**
    * Sets the specified DataElement to the passed-in value.
    *
    * @param elementName
    *                   - (in) contains the name of the element to
    *                   set.
    * @param value  - (in) contains the value.
    * @param appendNew - (in) specifies that, if elementName doesn't exist, to
    *                  create a default element and append it to this Data object.
    *                  Defaults to false.
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param pClientLocale - the locale/market/client combination that describes
    *                   the format of the passed in data
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the element's value was set,
    *         true if the element was not found and appendNew is true,
    *         false otherwise.
    */
   bool setElementValue( const DString &elementName,
                         const DString &value ,
                         bool appendNew = false,
                         bool displayFormat = true,
                         const ClientLocale *pClientLocale = 0,
                         const DString &i18nFormat = EMPTY_STRING );

   /**
    * Set the specified DataElement to the passed-in value.
    *
    * @param id - the name of the element to be set
    * @param eleBuffer - the buffer with the data
    * @param buffLen - the length of the buffer
    * @param returnedLength - length actually copied internally.
    * @return true if the element's value was set, false otherwise
    */
   bool setElementValue(
      unsigned long id,
      unsigned char *binBuff,
      unsigned long buffLength,
      unsigned long &returnedLength
      );

   /**
    * Set the specified DataElement to the passed-in value.
    *
    * @param name - the name of the element to be set
    * @param eleBuffer - the buffer with the data
    * @param buffLen - the length of the buffer
    * @return true if the element's value was set, false otherwise
    */
   bool setElementValue(
      const DString &name,
      unsigned char *binBuff,
      unsigned long buffLength );

   /**
    * Sets the specified DataElement to the passed-in value.  This should only
    *  be used to set values directly from host as checks are by-passed.
    *
    * @param id - (in) the data dictionary id of the element.
    * @param value  - (in/out) contains the value.  This value will be actual
    *  value stored upon return.
    * @return true if the element's value was set
    *         false otherwise.
    */
   bool setElementValueFromHost( unsigned long id, DString &value);

   /**
    * Set the default locale for this Data object instance.
    *
    * @param clientLocale - the locale/market/client combination that is the
    *                   default format of the data
    */
   virtual void setLocale( const ClientLocale& clientLocale );

   /**
    * Sets the repeat count.  This call will reserve room in the
    * repeat storage.
    *
    * @param repeatCount - (in) the new repeat count.
    *
    */
   void setRepeatCount( unsigned long repeatCount );

   /**
    * Sets the repeat count.  This call will reserve room in the
    * repeat storage.
    *
    * @param repeatCount - (in) the new repeat count
    *
    */
   void setRepeatCount( const DString &repeatCount );

   /**
    * This method is part of Data's polymorhic
    * interface. On Data objects, it will return false.
    *
    * @return false.
    */
   virtual bool setValue( const DString &value, bool checkValidity = true,
                          const ClientLocale *pClientLocale = 0,
                          bool displayFormat = true,
                          const DString &i18nFormat = EMPTY_STRING );

   /**
    * Sets the values of the elements in the Data object according
    * to the element-value pairs in the idiString.  If appendNew
    * is true, then if the idiString contains any element names
    * that aren't part of the Data object, they will be created.
    * If ignoreOnNoAppend is false, the function will return false
    * if any of the elements in the idiString does not already exist
    * and the element was not appended.
    *
    * @param idiString - (in) contains element-value pairs.
    * @param appendNew - (in) specifies that if elements in the idiString
    *                  don't exist in the Data object, create them.
    * @param ignoreOnNoAppend
    *                  - (in) specifies that, if one of the
    *                  elements in the idiString doesn't exist, and appendNew is
    *                  false, the function should return false.  If set to false, and
    *                  appendNew is false, new elements will not be added, and the
    *                  function will return true.
    * @param pClientLocale - the locale/market/client of the input data
    * @return true if all of the elements had their
    *         values set, or if they didn't exist and they were appended,
    *         or if they didn't exist and ignoreOnNoAppend was set to true.
    * @exception ConditionException&
    *                   out of memory
    */
   bool setValues( const DString &idiString, bool appendNew = false,
                   bool ignoreOnNoAppend = true,
                   const ClientLocale *pClientLocale = 0 );

   /**
    * Sets the values of the elements in this Data object according
    * to the element-value pairs in the input Data object.  If
    * appendNew is true, then if the input Data object contains any
    * element names that aren't part of this Data object, they will
    * be created.  If ignoreOnNoAppend is false, the function will
    * return false if any of the elements in the input Data object
    * do not already exist and the element was not appended.
    *
    * @param data - (in) contains element-value pairs.
    * @param appendNew - (in) specifies if elements in the input data object
    *        don't exist in the Data object, create them.
    * @param ignoreOnNoAppend - (in) specifies that, if one of the elements in
    *        the input data object doesn't exist, and appendNew is false,
    *        the function should return false.  If set to false, and
    *        appendNew is false, new elements will not be added, and the
    *        function will return true.
    * @return true if all of the elements had their
    *         values set, or if they didn't exist and they were appended,
    *         or if they didn't exist and ignoreOnNoAppend was set to true.
    *
    */
   bool setValues( const Data &data, bool appendNew = false,
                   bool ignoreOnNoAppend = true );

   /**
    * @param buffer - the buffer that contains the data.
    * @param buffLength - the size of the buffer in bytes.
    * @return true if succeeded, false for failure.
    */
   bool setAsUnsignedCharBuffer( const char *buffer,
                                 unsigned long buffLength );
   /**
    * Append a copy of the specified DataElement onto this
    * Data object instance.  The DataElements properties must
    * be in the data dictionary.
    *
    * @param dataEl - the source DataElement
    * @exception ConditionException& out of memory
    */
   void addElement( DataElement &dataEl );

   /**
    * If this Data object's properties are setup in the data
    * dictionary with redefinable fields, this method will change
    * the properties of one field for another set of fields.
    *
    * @param oldId  - the id of the field in this Data object that will be
    *               redefined.  This parameter is always the ORIGINAL field, and
    *               never one of the redefining DataSets.
    * @param newId  - the id of the DataSet that will redifine the field
    *               (oldId).
    * @exception ConditionException& if the Data object instance has no
    *               redefinable fields.
    *            ConditionException& if newId is not setup in the data
    *               dictionary to redefine oldId.
    */
   void setRedefine( unsigned long oldId, unsigned long newId );

   typedef std::map< DString, unsigned long, CaseInsensitiveCompare >
                                                             FieldNameMap;
   typedef std::vector< DataComponent* > ComponentPtrVector;

   typedef std::map< unsigned long, DataComponent*, std::less< unsigned long > >
                                                        ComponentPtrIndexMap;

   typedef std::vector< Data* > RepeatPtrVector;

   /**
    * Use to iterate over a Data object instance's repeat records.
    */
   typedef RepeatPtrVector::const_iterator const_repeat_iterator;

   /**
    * Use to iterate over a Data object instance's repeat records.
    */
   typedef RepeatPtrVector::iterator repeat_iterator;


   /**
    * Get an iterator set to the beginning of the data object's
    * repeat records.
    *
    * @return an iterator set to the start of the repeat records.
    */
   const_repeat_iterator repeatBegin() const;

   /**
    * Get an iterator set to the beginning of the data object's
    * repeat records.
    *
    * @return an iterator set to the start of the repeat records.
    */
   repeat_iterator repeatBegin();

   /**
    * Get an iterator set past the end of the data object's
    * repeat records.
    *
    * @return an iterator set beyond the last  record.
    */
   const_repeat_iterator repeatEnd() const;

   /**
    * Get an iterator set past the end of the data object's
    * repeat records.
    *
    * @return an iterator set beyond the last  record.
    */
   repeat_iterator repeatEnd();

   /**
    * !!! This method may not be permanent and may be removed in future versions
    * !!! of Infra.  If invalid data is set in, the user must be aware that
    * !!! there may be undetermined and undesired side effects in other methods.
    *
    * Sets the specified field exactly to the passed-in value with truncation if
    *  necessary.  This method only works for property based fields.
    *
    * @param id - (in) the data dictionary id of the element.
    * @param value  - (in) contains the value.
    * @exception ConditionException& field not found
    */
   void unauthorizedSetElementValue(
      unsigned long id,
      const DString &value
      );

   /**
    * !!! This method may not be permanent and may be removed in future versions
    * !!! of Infra.  If invalid data is set in, the user must be aware that
    * !!! there may be undetermined and undesired side effects in other methods.
    *
    * Sets the specified element exactly to the passed-in value with truncation
    * if necessary.  This method only works for property based fields.
    *
    * @param name - (in) the name of the element.
    * @param value  - (in) contains the value.
    * @exception ConditionException& field not found
    */
   void unauthorizedSetElementValue(
      const DString &name,
      const DString &value
      );

protected:
   I_CHAR *getDataBuffer() const
   {
      return _pDataBuffer;
   }

private:
   friend class DataIter;
   enum GET_DE_INIT
   {
      INIT_FROM_BUFFER,
      INIT_BUFFER_TO_DEFAULT,
      NO_INIT
   };

   static const DString EMPTY_STRING;

   FieldNameMap *_fieldNameMap;
   mutable ComponentPtrIndexMap *_dataIndexMap;
   ClientLocale *m_pLocale;
   RepeatPtrVector *_repeatData;
   I_CHAR *_pDataBuffer;
   unsigned long m_nextId;

   Data( DataProperties *properties );

   Data( DataComponent *pBase );

   Data( const Data &copy, DataComponent *pBase );

   Data( const DString &propertiesId, const DString &idiString,
         bool appendNew, bool ignoreOnNoAppend,
         DataComponent *pBase,
         const ClientLocale* pClientLocale = 0 );

   void _addElementToMaps( DataElement *newDE );
   void _addRedefinedElement( DataComponentProperties &replaceDCP,
                               ComponentPtrVector &tempVector,
                               std::istringstream &valueStream,
                               PropertyRepository *pPropRep );
   void _appendRepeat( Data *pData );
   void _deleteDataIndexMapContents();
   DataComponent* _getDataElement( unsigned long lElement,
                                   GET_DE_INIT eInit ) const;
   // Index = 0 to ( num properies - 1 )
   DataComponent* _getDataElementByIndex( long lIndex,
                                          GET_DE_INIT eInit ) const;
   unsigned long _getNextId();
   void _initialize( DataProperties *properties, bool initElements = true );
   Data *_removeRepeat( long lIndex );
   void _setId( unsigned long newId );
   void _setRedefine( const DString &oldName, const DString &newName );

   class DataStream;
   class BufferStream;
   class InStream;
   class OutStream;

   bool _writeToStream( DataStream& strm ) const;
   bool _readFromStream( DataStream& strm );
};

typedef std::map<DString, const Data *, std::less<DString> > data_ptr_map;
typedef data_ptr_map::value_type data_ptr_type;
typedef data_ptr_map::const_iterator data_ptr_map_const_iterator;
typedef data_ptr_map::iterator data_ptr_map_iterator;

typedef std::map<DString, Data, std::less<DString> > data_obj_map;
typedef data_obj_map::value_type data_obj_type;
typedef data_obj_map::const_iterator data_obj_map_const_iterator;
typedef data_obj_map::iterator data_obj_map_iterator;


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
// $Log:   Y:/VCS/iFastAWD/inc/data.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:50   kovacsro
//Initial revision.
// 
//    Rev 1.36   Aug 03 2001 13:43:18   DT11159
// Added setAsUnsignedCharBuffer( ) method.
//
//    Rev 1.35   May 18 2001 15:25:34   dt24433
// Updated binary element support and added setElementFromHost.
//
//    Rev 1.34   Mar 22 2001 16:27:44   dt24433
// Implemented unauthorizedSetElementValue.
//
//
//    Rev 1.33   Mar 21 2001 11:36:26   dt24433
// Removed public methd getDataElement.
// Add getElementProperties, getFieldNameFromId, and isDefault.
//
//    Rev 1.32   Mar 02 2001 14:41:06   dt24433
// Changed use of DataMap to FieldNameMap - only dataIndexMap will have DataComponent pointers now.
// Factored code so by Name versions of methods typically call by Id methods.
// Removed code supporting DataElements to/from properties.
// DataElements are no longer used or supported for property based elements for memory/performance reasons.
//
//    Rev 1.31   Jan 22 2001 12:08:36   dt24433
// Using static const EMPTY_STRING as default for const DString & parameters to limit DString construction.
//
//    Rev 1.30   Jan 19 2001 17:01:46   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.28   Nov 22 2000 07:01:08   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.27   Sep 05 2000 06:05:38   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.26   Jun 08 2000 11:50:46   dtwk
// Add support for case-insensitivity
//
//    Rev 1.25   May 31 2000 09:31:18   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.24   Jan 16 2000 14:08:00   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.23   Jan 10 2000 11:02:02   dtwk
// Add a getElementValue method that will return a
// reference to a passed in string rather than a newly
// allocated string
//
//    Rev 1.22   Jan 07 2000 14:57:32   dtwk
// New and improved - with 20% more comments!
//
//    Rev 1.21   Dec 19 1999 09:28:16   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.20   Dec 16 1999 11:40:20   dtwk
// Add moveRepeatData method
//
//    Rev 1.19   Nov 29 1999 07:29:26   dtwk
// Add support for redefines
//
//    Rev 1.18   Oct 06 1999 11:29:58   DCYK
// Add support for redefines.
//
//
//    Rev 1.17   Jul 28 1999 14:20:04   DCYK
// Performance improvements.
//
//
//    Rev 1.16   Jun 29 1999 09:46:12   DCYK
// Added setLocale methods.
//
//
//    Rev 1.15   Jun 18 1999 09:36:06   DCYK
// Add ID's for dynamically created elements.
//
//
//    Rev 1.14   Jun 06 1999 13:25:18   DTWK
// Spiff up I18N formatting
//
//    Rev 1.13   May 26 1999 17:19:50   DCYK
// Add support for getting and setting numerical id's.
//
//
//    Rev 1.12   May 26 1999 16:10:04   DCYK
// Add ability to pass in strings to getElementValue.
//
//    Rev 1.11   May 24 1999 15:16:20   DTWK
// Re-const some more methods
//
//    Rev 1.10   May 24 1999 13:00:08   DTWK
// Make some methods const again
//
//    Rev 1.9   May 24 1999 10:30:48   DTWK
// Add internationalized formatting for new date and number types using JNI
//
//    Rev 1.8   May 14 1999 11:32:06   DTWK
// Add ability to access Data using Group/Field Id's
//
//    Rev 1.7   Apr 20 1999 16:48:50   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.6   Mar 05 1999 10:20:50   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Feb 11 1999 15:01:24   DCYK
// Add support for binary elements.
//
//
//    Rev 1.4   Jan 28 1999 14:05:50   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:22   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 14 1998 11:33:18   dcyk
// Updated header file documentation.
//
//
//    Rev 1.0   29 Jul 1998 20:36:44   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.28   Jul 08 1998 10:04:28   dcyk
// Performance improvements.
//
//
//    Rev 1.27   Feb 20 1998 15:28:08   dcyk
// Added getId() function.
//
//
//    Rev 1.26   Nov 10 1997 15:00:00   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.25   23 Sep 1997 16:25:58   dcyk
// Store dataElements in a vector, not a map.
// This eliminates a string for every element.
//
//
//    Rev 1.24   09 Sep 1997 16:34:24   dcyk
// Reduce memory footprint.
//
//
//    Rev 1.23   08 Sep 1997 14:22:28   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.22   07 Aug 1997 15:06:38   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.21   24 Jul 1997 09:26:00   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.20   08 Jul 1997 09:10:08   dcyk
// Added STL casting operators and RTTI.
// getAllValues now takes the DataElement
// flags USE_MASK & USE_SUBSTITUTES
//
//
//    Rev 1.19   13 Jun 1997 16:18:40   dcyk
// Added conditions, conditionExceptions &
// tracing.  Added repeat iterators.  Fixed
// some masking problems.
//
//
//    Rev 1.18   Jun 08 1997 18:47:32   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.17   05 Jun 1997 17:53:32   dcyk
// Added default parameter to getValue.
// Added mask & substitute parameters
// to getElementValue & getAllValues.
//
//
//    Rev 1.16   May 29 1997 09:52:08   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.15   May 09 1997 16:43:42   dcyk
// Improved standards compliance.
//
// Added private functions deleteDataMapContents
// and deleteRepeatDataContents.
//
//
//    Rev 1.14   May 06 1997 10:14:56   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.13   May 01 1997 08:36:40   dcyk
// Added addRepeat, removeRepeat and
// appendRepeatData.
//
// Added documentation.
//
//
//    Rev 1.12   Apr 11 1997 08:57:34   dcyk
// Improve performance.
//
//
//    Rev 1.11   Apr 04 1997 09:51:50   dcyk
// Added documentation and
// improved performance.
//
//
//    Rev 1.10   Mar 25 1997 15:46:12   dcyk
// Added:  array[] operators for repeats,
// getData & getDataElement instead of getComponent,
// isDefault.
//
// Removed:  findRepeat, setValue.
//
// Changed:  getAllRawValues to getAllValues,
// getValue(string) to getElementValue(string),
// resetValue(string) to resetElementValue(string),
// setValue(string,string,bool) to setElementValue(string,string,bool).
//
//
//    Rev 1.9   Feb 24 1997 13:52:28   dcyk
// Added third parameter to getAllRawValues,
// a boolean "usePropertiesOrder", defaults to
// false.  If true, fills up the idi string in the order
// that the data components are in the Data
// Properties object.  If false, fills up the idi
// string alphabetically.
//
//
//    Rev 1.8   Feb 11 1997 14:29:24   dcyk
// Added support for Rogue Wave's STL.
// Removed parameter from getValue.
//
//
//    Rev 1.7   Jan 28 1997 11:39:58   dcyk
// Added an appendNew flag to SetValue.
// Defaults to false.
//
//
//    Rev 1.6   Jan 27 1997 14:07:34   DRUS
// Added an option to getAllRawValues to insert EOL characters
// between each attribute-value pair (for debugging).
//
//    Rev 1.5   Jan 19 1997 12:54:20   DRUS
// Added == and != operators.
//
//    Rev 1.4   Jan 17 1997 17:29:58   DRUS
// Added setValues method which will copy values from another
// Data object.  Also removed buffer data members.
//
//    Rev 1.3   Jan 10 1997 08:57:04   DRUS
// Added support for repeat records.  Added the method findRepeat().
//
//    Rev 1.2   Nov 21 1996 14:37:02   DRUS
// Fixed comment block syntax errors generated by PVCS (again).
//
//    Rev 1.1   Nov 20 1996 17:07:08   DRUS
// Fixed comment block syntax errors generated by PVCS.
//
//    Rev 1.0   Nov 19 1996 10:03:06   DRUS
//
//
//

#endif // Data_hpp
