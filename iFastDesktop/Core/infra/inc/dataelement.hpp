#ifndef DATAELEMENT_HPP
#define DATAELEMENT_HPP

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

/**@pkg DIDBRKR */

#pragma message( "including "__FILE__ )


#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
   #include <iostream>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef DATACOMPONENT_HPP
   #include "datacomponent.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class JavaDate;
class JavaNumber;

class DIDBRKR_LINKAGE DataElementProperties;

class DIDBRKR_LINKAGE DataElement : public DataComponent
{
   /**
    * Used with the "allow null" and "default value is null" properties
    * in conjunction with streaming the DataElement
    */
   static const I_CHAR NULL_VALUE;

public:
   enum { USE_SUBSTITUTES = 0x01, USE_MASK = 0x02, STRIP_LEADING = 0x04,
          STRIP_TRAILING = 0x08 };

   /**
    * Constructs a DataElement object.
    *
    * @param value  - (in) value to assign to this DataElement object.
    *               Defaults to an empty string.
    * @param properties - (in) pointer to the properties
    *                   object for this DataElement.  Defaults to a NULL pointer.
    * @param buffer - (in) pointer to an array of characters, used when
    *               streaming a value into the DataElement.  Defaults to a NULL
    *               pointer.
    * @param initElement
    *                   - (in) if true, the newly created DataElement object's
    *                   value will be initialized to the default value.  Defaults to
    *                   false.
    * @param clientLocale - the locale/market/client for the value of this
    *               object instance
    */
   DataElement( const DString &value = NULL_STRING,
                DataElementProperties *properties = 0,
                bool initElement = true,
                const ClientLocale &clientLocale =
                     ClientLocale::getDefaultClientLocale() );

   /**
    * Constructs a DataElement object.
    *
    * @param value  - (in) value to assign to this DataElement object.
    *               Defaults to an empty string.
    * @param name - (in) the name of the element
    * @param pBase - pointer to a "base" DataComponent object
    */
   DataElement( const DString &value, const DString &name,
                DataComponent *pBase );

   virtual ~DataElement();

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)
          PVOID operator new (size_t nBytes);
          VOID operator delete (PVOID pv);
#endif

   /**
    * Assigns one DataElement object to another.
    *
    * @param copy - (in) reference to a DataElement object, whose
    *        attributes you want assigned to this DataElement.
    * @return a reference to this DataElement object.
    * @exception ConditionException& if one of the DataElement objects has
    *            properties and the other one doesn't, or if both have
    *            properties but the properties are not equal.
    *
    */
   DataElement &operator=( const DataElement &copy );

   // Streams values in\out of native format...
   friend EXPORTWIN std::istream & EXPORTOS2 operator>> ( std::istream &stream,
                                                     DataElement &element );
   friend EXPORTWIN std::ostream & EXPORTOS2 operator<< ( std::ostream &stream,
                                                const DataElement &element );

   /**
    * Tests if two DataElement objects are equal.
    *
    * @param element - (in) reference to the DataElement object
    *        to compare against this DataElement object.
    * @return true if the two DataElement objects are
    *         equal.  If false, then the _value's of the DataElement objects
    *         are not equal, or one object has DataElementProperties
    *         associated with it and the other does not, or that both
    *         objects have properties and the properties are not equal.
    *
    */
   bool operator== ( const DataElement &element ) const;

   /**
    * Tests if two DataElement objects are not equal.
    *
    * @param element - (in) reference to the DataElement object
    *        to compare against this DataElement object.
    * @return true if the two DataElement objects are not
    *         equal.
    *
    */
   bool operator!= ( const DataElement &element ) const
                                             { return !(*this == element); };

   /**
    * Fill the DataElement instance with binary data.
    *
    * @param buffer - a pointer to the binary data to be copied and stored
    */
// Commenting out to see if any projects use.  8)  03/01/2001
//   void assignUnsignedCharBuffer( I_UCHAR *inBuffer );

   /**
    * Returns a list of the x=y pairs from the substitution list.
    *
    * @param subValues - (out) string that will be filled with the x=y pairs
    * @param pClientLocale - the locale/market/client of the substitution values
    * @return true if the DataElement has a substitution
    *         list, false otherwise.
    */
   bool getAllSubstituteValues( DString &subValues,
                                const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Get a copy of the binary data stored in this object.
    *
    * @param valBuffer a pointer to a buffer that will receive the data.
    * @param valBufferLength
    *                  the size of the buffer in bytes.
    * @param returnedLength
    *                  after the method is complete, this will be set with the number
    *                  of bytes returned.
    * @return true if successful, false otherwise (if this instance holds no
    *         binary data).
    */
   bool getBinaryValue( unsigned char *valBuffer,
                        unsigned long valBufferLength,
                        unsigned long &returnedLength ) const;

   /**
    * Checks if this DataElement is forcing the values passed in to
    * it's setValue function to match one of the values in the
    * substitution list.
    *
    * @return true if force matching is turned on for
    *         this DataElement.
    *
    */
   bool getForceMatching() const;


   /**
    * Get the length of the largest possible field from
    * this DataElemnt object.
    *
    * @return the length
    */
   virtual unsigned long getMaxLength() const;

   /**
    * Returns the un-substituted and un-masked value for this
    * DataElement object.
    *
    * @return the unmodified value of this DataElement.
    *
    */
   const DString getUnmodifiedValue() const;

   /**
    * If this DataElement has a substitution map with x=y values,
    * this function returns the "y" for a given "x".  If this
    * DataElement does not have a substitution map, then "x" is
    * returned.
    *
    * @param subValue - (in) the value to search for in the
    *        substitution map.
    * @param pClientLocale the locale/market/client of the substitution values
    * @return the substituted value for the given subValue.
    *
    */
   DString getSubstituteValue( const DString &subValue,
                               const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Gets the boolean representation of the DataElement object's
    * value.
    *
    * @param value - (out) variable that will be set to the DataElement
    *        object's value.
    * @return true if the DataElement is of type boolean, false otherwise.
    *
    */
   bool getValueAsBool( bool &value ) const;

   /**
    * Gets the double representation of the DataElement object's
    * value.
    *
    * @param value - (out) variable that will be set to the DataElement
    *        object's value.
    * @return true if the DataElement is of type decimal, false otherwise.
    *
    */
   bool getValueAsDouble( double &value ) const;

   /**
    * Gets the unsigned long representation of the DataElement
    * object's value.
    *
    * @param value - (out) variable that will be set to the
    *        DataElement object's value.
    * @return true if the DataElement is of type integer, false otherwise.
    *
    */
   bool getValueAsULong( unsigned long &value ) const;

   /**
    * Gets the unsigned long representation of the DataElement
    * object's value.
    *
    * @param value - (out) variable that will be set to the
    *        DataElement object's value.
    * @return true if the DataElement is of type Date (i18n), false otherwise.
    *
    */
   bool getValueAsDate( JavaDate &value ) const;

   /**
    * Gets the unsigned long representation of the DataElement
    * object's value.
    *
    * @param value - (out) variable that will be set to the
    *        DataElement object's value.
    * @return true if the DataElement is of type Number (i18n), false otherwise.
    *
    */
   bool getValueAsNumber( JavaNumber &value ) const;

   /**
    * Gets the string representation of the DataElement
    * object's value.
    *
    * For elements with masks, the following rules apply:
    *
    * For monetary formats, use a mask like "$$$,$$$.9999".  This
    * mask will take a number with 5 or fewer digits to the left of
    * the decimal place, format them with the comma where
    * appropriate, and pre-pend a dollar sign before the first
    * digit.  If the number had 6 digits to the left of the decimal,
    * no dollar sign would be pre-pended, because all 6 of the
    * dollar sign positions are taken up by digits.  This mask would
    * also format the number with 4 digits to the right of the
    * decimal point, filling any extra positions with zeros.
    *
    * For non-monetary numbers, use a mask like "999,999.9999".
    * This mask would produce almost the same format as the one
    * above, but there would be no dollar signs added.
    *
    * For regular characters, use
    * "XXXX-XX-XX", where the "X"s are your characters.
    *
    * The above formatting does not apply to the i18n components.
    * The mask format options for those types are identical to the
    * Java SimpleDateFormat and JavaDecimalFormat classes.
    * Additional information on those classes may be found in Sun's
    * Java Development Kit documentation.
    *
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @param valueOut - reference of string to return value in.
    * @param formatFlags
    *                   - (in) values defined on DataElement that
    *                   specify whether to get the masked or substituted value of this
    *                   DataElement.  Valid values are DataElement::USE_SUBSTITUTES
    *                   and DataElement::USE_MASK.
    * @param pClientLocale - the desired locale/market/client for the return data.
    * @param i18nFormat - for the i18n types, a custom format for the return data.
    * @return reference to string passed in with value of element.
    */
   virtual DString &getValue( DString &valueOut, unsigned long formatFlags = 0L,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = NULL_STRING ) const;

   /**
    * Gets the string representation of the DataElement
    * object's value.
    *
    * For elements with masks, the following rules apply:
    *
    * For monetary formats, use a mask like "$$$,$$$.9999".  This
    * mask will take a number with 5 or fewer digits to the left of
    * the decimal place, format them with the comma where
    * appropriate, and pre-pend a dollar sign before the first
    * digit.  If the number had 6 digits to the left of the decimal,
    * no dollar sign would be pre-pended, because all 6 of the
    * dollar sign positions are taken up by digits.  This mask would
    * also format the number with 4 digits to the right of the
    * decimal point, filling any extra positions with zeros.
    *
    * For non-monetary numbers, use a mask like "999,999.9999".
    * This mask would produce almost the same format as the one
    * above, but there would be no dollar signs added.
    *
    * For regular characters, use
    * "XXXX-XX-XX", where the "X"s are your characters.
    *
    * The above formatting does not apply to the i18n components.
    * The mask format options for those types are identical to the
    * Java SimpleDateFormat and JavaDecimalFormat classes.
    * Additional information on those classes may be found in Sun's
    * Java Development Kit documentation.
    *
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @param formatFlags
    *                   - (in) values defined on DataElement that
    *                   specify whether to get the masked or substituted value of this
    *                   DataElement.  Valid values are DataElement::USE_SUBSTITUTES
    *                   and DataElement::USE_MASK.
    * @param pClientLocale - the desired locale/market/client for the return data.
    * @param i18nFormat - for the i18n types, a custom format for the return data.
    * @return the value of the DataElement.
    */
   virtual DString getValue( unsigned long formatFlags = 0L,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = NULL_STRING ) const;

   /**
    * Checks if the value of this DataElement is equal to it's
    * default value.
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @param pClientLocale - the locale/market/client of the data
    * @return true if the value is equal to the default false otherwise.
    */
   virtual bool isDefault( const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Returns true because the object is a DataElement, not a Data.
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @return true.
    *
    */
   virtual bool isElement() const{ return true; };

   /**
    * Resets the DataElement object's value to it's default.
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @param pClientLocale - the locale/market/client for the default value
    */
   virtual void resetValue( const ClientLocale *pClientLocale = 0 );

   /**
    * Fill the DataElement instance with binary data.
    *
    * @param valBuffer - a pointer to the binary data to be copied and stored
    * @param valBufferLength
    *                  - the size of the buffer in characters. This should never be larger
    *                  than the maximum size specified by the DataElementProperties
    *                  for this element
    * @param returnedLength
    *                  - this will be set with the number of chars stored
    * @return true if the data was set, false if the DataElement is not binary.
    */
   bool setBinaryValue( unsigned char *valBuffer,
                        unsigned long valBufferLength,
                        unsigned long &returnedLength );

   /**
    * Turns on or off the flag to make this DataElement force values
    * passed to it's setValue function to match the values in it's
    * substitution list.
    *
    * @param forceMatching - (in) specifies if forced matching should be turned
    *        on or off.
    *
    */
   void setForceMatching( bool forceMatching );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    * @param value  - (in) contains the value to set the DataElement
    *               object's value to.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or the DataElement
    *         was not of type boolean.
    */
   bool setValue( bool value );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or the DataElement
    *         was not of type decimal.
    *
    */
   bool setValue( double value );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or the DataElement
    *         was not of type integer.
    *
    */
   bool setValue( unsigned long value );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or the DataElement
    *         was not of type Date (i18n).
    *
    */
   bool setValue( JavaDate &value );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or the DataElement
    *         was not of type Number (i18n).
    *
    */
   bool setValue( JavaNumber &value );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    *  ^SEE ALSO    : Overridden from DataComponent
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @param checkValidity - (in) specifies if the parameter "value" should be
    *        checked for validity before assigning it.  Defaults to true.
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param pClientLocale - the locale/market/client of the passed in value
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or if
    *         checkValidity was true and the value was not in a valid
    *         format.
    *
    */
   virtual bool setValue( const DString &value, bool checkValidity = true,
                          const ClientLocale *pClientLocale = 0,
                          bool displayFormat = true,
                          const DString &i18nFormat = NULL_STRING );

   /**
    * Get the id of this object.
    *
    * @return the id of this object
    */
   unsigned long getId() const;

   /**
    * Get the label for the DataElement.  This maps to the
    * locale-specific label on fields in the data dictionary.
    *
    * @param pClientLocale - the locale/market/client for the desinred label
    * @return reference to the label
    */
   const DString &getLabel(
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * Get the name of this object.
    *
    * @return the name.
    */
   const DString &getName() const;

   /**
    * Sets the value to NULL or nonNULL.  This value may be retrieved by
    * calls to getNull(). Note that NULL does not mean (void * 0). This is
    * more analagous to the null value in a database.  When set, if this
    * element is streamed out, the value streamed out will be
    * DataElement::NULL_VALUE ('\a'), padded with spaces.
    *
    * @param fNull - true for NULL, false otherwise.
    * @return false if this DataElement does not have the "allow null" property
    *         flag set in the DataDictionary
    */
   bool setNull( bool fNull );

   /**
    * Returns whether this element has been set to null.
    *
    * @return true if null, false otherwise,
    */
   bool getNull()
   {
      return m_fValueIsNull;
   }

private:
   DataElement( const DString &value,
                DataComponent *pBase,
                DataElementProperties *properties,
                bool initElement,
                const ClientLocale &clientLocale );

   DataElement( const DataElement &copy );

   /**
    * Called by constructors to perform initial initialization.
    * the parameter value.
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to.
    * @param properties - (in) the DE's properties
    * @param pClientLocale - the locale/market/client of the element
    *
    */
   void _initElement( const DString &value,DataElementProperties *properties,
                      bool initElement,
                      const ClientLocale *pClientLocale = 0 );

   /**
    * Set the id of this object.
    *
    * @param newId - the new id
    */
   void _setId( unsigned long newId );

   void _setName( const DString &newName );

   /**
    * Set the DataElement object's value to the value specified in
    * the parameter value.
    *
    * @param value - (in) contains the value to set the DataElement
    *        object's value to. Defaults to a NULL pointer.
    * @param checkValidity - (in) specifies if the parameter "value" should be
    *        checked for validity before assigning it.  Defaults to true.
    * @param pClientLocale - the locale/market/client of the passed in value
    * @param displayFormat
    *                   - for the DataElement types that are for i18n, specify
    *                   that the format of the value parameter is in "display"
    *                   format. If false, the format of value is assumed to be
    *                   "host" format.
    * @param i18nFormat - for i18n DataElement types, if the value being set is
    *                   in a custom format, specify that format here.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful or if
    *         checkValidity was true and the value was not in a valid
    *         format.
    *
    */
   virtual bool _setValue( const DString &value, bool checkValidity,
                           const ClientLocale *pClientLocale = 0,
                           bool displayFormat = true,
                           const DString &i18nFormat = NULL_STRING );

   DString _strValue;
   DString _strName;
   I_CHAR *_maskedValue;
   unsigned char *_binaryBuffer;
   unsigned long _binaryBufferLength;
   bool m_fValueIsNull;

   // Friend added so that Data can initialize a DE's base pointer when
   // constructed.
   friend class Data;
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
// $Log:   Y:/VCS/iFastAWD/inc/dataelement.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:52   kovacsro
//Initial revision.
// 
//    Rev 1.25   Mar 22 2001 14:46:42   dt24433
// Changed binary buffer parm from I_UCHAR * to unsigned char *
// 
//    Rev 1.24   Mar 02 2001 14:44:38   dt24433
// Only stream in/out by char to properly support binary fields.
// getLabel returns const DString reference instead of DString.
// getId has been split into getId and getName as appropriate.
// Removed code supporting sync up with Data objects data buffer as DataElements are no longer used this way.
// 
//    Rev 1.23   Jan 22 2001 12:09:22   dt24433
// Removed _cValue, _value and replaced with DString _strValue.
// 
//    Rev 1.22   Jan 10 2001 11:05:14   dt24433
//  
// 
//    Rev 1.21   Jan 04 2001 16:48:06   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.20   Nov 22 2000 07:01:20   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.19   Sep 05 2000 06:05:46   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.18   May 31 2000 09:31:30   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.17   Jan 16 2000 14:08:12   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.16   Dec 19 1999 09:28:28   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.15   Oct 06 1999 11:30:06   DCYK
// Add support for redefines.
//
//
//    Rev 1.14   Oct 04 1999 15:26:10   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.13   Jun 29 1999 09:46:22   DCYK
// Added setLocale methods.
//
//
//    Rev 1.12   Jun 18 1999 09:36:14   DCYK
// Add ID's for dynamically created elements.
//
//
//    Rev 1.11   Jun 14 1999 09:55:58   DCYK
// Use javalocale object for default locales.
//
//
//    Rev 1.10   Jun 06 1999 13:25:24   DTWK
//
//
//    Rev 1.9   May 26 1999 17:19:54   DCYK
// Add support for getting and setting numerical id's.
//
//
//    Rev 1.8   May 24 1999 10:31:00   DTWK
// Add internationalized formatting for new date and number types using JNI
//
//    Rev 1.7   Apr 20 1999 16:48:54   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.6   Mar 05 1999 10:21:02   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Feb 11 1999 15:02:16   DCYK
// Add support for binary elements.
//
//
//    Rev 1.4   Jan 28 1999 14:05:58   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:32   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 14 1998 11:32:36   dcyk
// Updated header file documentation.
//
//
//    Rev 1.0   29 Jul 1998 20:36:54   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.22   Nov 10 1997 15:00:06   dcyk
//
//
//    Rev 1.21   08 Sep 1997 14:24:48   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.20   05 Sep 1997 11:24:58   dcyk
// Don't create the _maskedValue unless
// the element has a mask.
//
//
//    Rev 1.19   07 Aug 1997 15:07:14   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.18   24 Jul 1997 09:28:12   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.17   08 Jul 1997 09:13:00   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.16   13 Jun 1997 16:18:50   dcyk
//
//
//    Rev 1.15   Jun 08 1997 18:47:38   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.14   05 Jun 1997 18:00:54   dcyk
// Changed overloads of getValue to
// getValueAsULong, getValueAsBool, etc.
// Added default parameter to getValue,
// formatting flags that are enum's defined on
// DataElement.
//
//
//    Rev 1.13   May 29 1997 09:52:26   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.12   May 06 1997 10:15:38   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.11   May 01 1997 08:38:38   dcyk
// Removed repeat handling stuff.
//
// Added documentation.
//
//
//    Rev 1.10   Apr 11 1997 08:57:42   dcyk
//
//
//    Rev 1.9   Apr 04 1997 09:51:54   dcyk
//
//
//    Rev 1.8   Mar 25 1997 15:51:40   dcyk
// Added:  getValue that returns a string,
// isDefault.
//
// Made copy constructor private.
//
// Use pointer to buffer when streaming in.
//
//
//    Rev 1.7   Feb 11 1997 14:34:12   dcyk
// Added support for Rogue Wave's STL.
//
//
//    Rev 1.6   Jan 19 1997 12:54:26   DRUS
//
//
//    Rev 1.5   Jan 15 1997 13:32:38   dcyk
// Added setValue method that pads
// the values to their proper lengths.
//
//    Rev 1.4   Jan 10 1997 08:54:40   DRUS
// Added support for repeat records and added the
// methods findRepeatIndex() and getRepeatElement().
//
//    Rev 1.3   Dec 31 1996 13:37:46   DRUS
// Made streaming operators exportable.  Added isElement() to identify
// the type of any object as Data or DataElement.  Added mapping functions.
//
//    Rev 1.2   Nov 21 1996 14:37:06   DRUS
// Fixed PVCS comment syntax errors (again).
//
//    Rev 1.1   Nov 20 1996 17:07:14   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:14   DRUS
//
//
//

#endif // DataElement_h
