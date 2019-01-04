#ifndef DATAELEMENTPROPERTIES_HPP
#define DATAELEMENTPROPERTIES_HPP

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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DATACOMPONENTPROPERTIES_HPP
   #include "datacomponentproperties.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef MULTIKEYPOINTERMAPELEMENT_HPP
   #include "multikeypointermapelement.hpp"
#endif

#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
   #include <iostream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

// Forward references
class DataPropertiesImpl;
class JavaSimpleDateFormat;
class JavaDecimalFormat;

class DIDBRKR_LINKAGE DataElementProperties : public DataComponentProperties
{
public:
   enum ELEMENTTYPE { STRING, INTEGER, DECIMAL, BINARY, BOOLEAN, NO_TYPE,
                      I18N_DATE, I18N_TIME, I18N_DECIMAL, I18N_INTEGER,
                      I18N_PERCENT, I18N_CURRENCY };
   enum JUSTIFICATION { LEFT, RIGHT, CENTER, NO_JUSTIFICATION };
   // Same as in DataElement - these should be combined.
   enum { USE_SUBSTITUTES = 0x01, USE_MASK = 0x02, STRIP_LEADING = 0x04,
          STRIP_TRAILING = 0x08 };

   /**
    * Constructs a DataElementProperties object.
    *
    * @param id     - (in) identifying string of this object
    * @param clientLocale - the default locale/market/client of this object
    * @param defaultValue
    *                   - (in) contains the default value for
    *                   DataElement objects with this property.  Defaults to an empty
    *                   string.
    * @param repeatable - (in) specifies if DataElement objects with this
    *                   property can have repeat areas.  Defaults to false.
    * @param fixedRepeatSize
    *                   - (in) the length, in DataElements, of
    *                   the fixed repeat area.  Defaults to 0.
    * @param maxLength - (in) the maximum length that the value of a
    *                  DataElement object with this property can have.
    *                  Defaults to 1.
    * @param storedType - (in) enum specifying the type of the
    *                   DataElement object.  Can be STRING, INTEGER, DECIMAL, BINARY,
    *                   BOOLEAN or NO_TYPE.  Defaults to STRING.
    * @param minLength - (in) the minimum length that the value of a
    *                  DataElement object with this property can have.
    *                  Defaults to 0.
    * @param decimalPlace
    *                   - (in) the position of the decimal point in
    *                   the value.  Defaults to 0.  Applies to type DECIMAL.
    * @param fillCharacter
    *                   - (in) the character used to pad objects of type
    *                   STRING.  Defaults to ' ', a space.
    * @param filterType - (in) enum specifying how the object's value
    *                   will be filtered.  Defaults to STRING.
    * @param justification
    *                   - (in) enum specifying the justification
    *                   for objects of type STRING.  Can be LEFT, RIGHT, CENTER or
    *                   NO_JUSTIFICATION.  Defaults to LEFT.
    * @param mask   - (in) the mask used to format the DataElement
    *               object's value.  Defaults to an empty string.
    * @param hostMask - for the i18n types, the format of the data as it comes from
    *                 the host
    * @param translationString
    *                   - (in) string containing name & value
    *                   pairs that allow substitution of the DataElement's value.
    * @param fieldLabel - the label of the field, possibly used for display.
    * @param fAllowNull
    *                   - true if this field may be set to NULL
    *                   using the DataElement::setNull method
    * @param fDefaultValueIsNull
    *                   - true if the default value for this element is
    *                   NULL.
    */
   DataElementProperties( const DString  &id,
                          const ClientLocale &clientLocale =
                             ClientLocale::getDefaultClientLocale(),
                          const DString  &defaultValue = NULL_STRING,
                          bool           repeatable = false,
                          unsigned long  fixedRepeatSize = 0,
                          unsigned long  maxLength = 1,
                          ELEMENTTYPE    storedType = STRING,
                          unsigned long  minLength = 0,
                          unsigned long  decimalPlace = 0,
                          I_CHAR         fillCharacter = ' ',
                          ELEMENTTYPE    filterType = STRING,
                          JUSTIFICATION  justification = LEFT,
                          const DString  &mask = NULL_STRING,
                          const DString  &hostMask = NULL_STRING,
                          const DString  &translationString = NULL_STRING,
                          const DString  &fieldLabel = NULL_STRING,
                          bool fAllowNull = false,
                          bool fDefaultValueIsNull = false );

   /**
    * Constructs a DataElementProperties object.
    *
    * @param id     - (in) identifying string of this object
    * @param clientLocale - the default locale/market/client of this object
    * @param storedType - (in) enum specifying the type of the
    *                   DataElement object.  Can be STRING, INTEGER, DECIMAL, BINARY,
    *                   BOOLEAN or NO_TYPE.  Defaults to STRING.
    * @param mask   - (in) the mask used to format the DataElement
    *               object's value.  Defaults to an empty string.
    * @param hostMask - for the i18n types, the format of the data as it comes from
    *                 the host
    * @param subMap - the list of substitutions available
    * @param minLength - (in) the minimum length that the value of a
    *                  DataElement object with this property can have.
    *                  Defaults to 0.
    * @param decimalPlace
    *                   - (in) the position of the decimal point in
    *                   the value.  Defaults to 0.  Applies to type DECIMAL.
    * @param fieldLabel - the label of the field, possibly used for display.
    */
   DataElementProperties( const DString &id,
                          const ClientLocale &clientLocale =
                             ClientLocale::getDefaultClientLocale(),
                          ELEMENTTYPE   storedType = STRING,
                          const DString &mask = NULL_STRING,
                          const DString &hostMask = NULL_STRING,
                          const DString &subMap = NULL_STRING,
                          unsigned long minLength = 0,
                          unsigned long decimalPlace = 0,
                          const DString &fieldLabel = NULL_STRING );

   DataElementProperties( unsigned long  fieldId,
                          const DString  &fieldName,
                          const DString  &fieldType,
                          const DString  &hostMask,
                          unsigned long  maxLength,
                          unsigned long  minLength,
                          unsigned long  decimalPlace,
                          bool           fAllowNull );

   virtual ~DataElementProperties();

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)
       PVOID operator new (size_t nBytes);
       VOID operator delete (PVOID pv);
#endif

   /**
    * Formats a string according to this DataElementProperties
    * object.
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param valueString - (in/out) contains the value to be
    *        formatted.  Filled with the formatted value on return.
    * @param checkValidity - (in) specifies if the value should be checked
    *        for validity before formatting it.  Defaults to true.
    * @return false if the format of the input value is
    *         not valid for the DataElementProperties type, true otherwise.
    *
    */
   virtual bool formatValue( DString &valueString,
                             bool checkValidity = true ) const;

   /**
    * Applies the DataElementProperties object's mask to the input
    * string.  If the object does not have a mask, the string is not
    * changed.
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
    * For percentages, use a mask like "%%.%".  When using a
    * percentage mask, the DataElement's value is shifted two
    * decimal places to the left, then the mask is applied.  So, if
    * the mask is "%%.%", and the DataElement is defined as being
    * 3 digits, with 2 to the right of the decimal, and the value is
    * 0.83, then a call to getValue, requesting the masked value,
    * would return "83.0".  If the mask was "%%", the same call
    * would return "83".
    *
    * The above formatting does not apply to the i18n components.
    * The mask format options for those types are identical to the
    * Java SimpleDateFormat and JavaDecimalFormat classes.
    * Additional information on those classes may be found in Sun's
    * Java Development Kit documentation.
    *
    * @param valueString - (in/out) contains the string that the mask will
    *        be applied to.  This string will be changed to the masked
    *        value on exit.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @param i18nFormat - for the i18n types, a custom format for the
    *        return data.
    * @return valueString after the mask has been applied.
    *
    */
   DString &formatUsingMask( DString &valueString,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = EMPTY_STRING ) const;

   // Retrieve basic information...
   /**
    * Returns the maximum allowable length for a DataElement of this
    * DataElementProperties.
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @return Returns an unsigned long, the maximum allowable length for a
    *         DataElement associated with this DataElementProperties.
    *
    */
   virtual unsigned long getMaxLength() const
                       { return _items.maxLength; }

   /**
    * Get the maximum amount of storage required to
    * hold the contents of this object (if it was
    * streamed into a buffer, for example)
    *
    * @return the maximum size.
    */
   virtual unsigned long getTotalMaxLength() const
                       { return _items.maxLength; }

   /**
    * Returns the minimum allowable length for a DataElement of this
    * DataElementProperties.
    *
    * @return Returns an unsigned long, the minimum allowable length for a
    *         DataElement associated with this DataElementProperties.
    *
    */
   unsigned long getMinLength(
      const ClientLocale& cloc = ClientLocale::getDefaultClientLocale() ) const;

   /**
    * Returns whetuer NULL (using DataElementProperties::setNull) is valid for
    * elements associated with this DataElementProperties.
    *
    * @return true if NULL is allowed, false otherwise
    *
    */
   bool getAllowNull(
      const ClientLocale& cloc = ClientLocale::getDefaultClientLocale() ) const;

   /**
    * Returns the index of the decimal point in this
    * DataElementProperties object.
    *
    * @return Returns an unsigned long, the position of the decimal point.
    *
    */
   unsigned long getDecimalPlace() const
   {
       return _items.decimalPlace;
   }

   /**
    * Returns the character used to fill or pad in DataElement
    * objects associated with this DataElementProperties.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return Returns a char containing the pad or fill character.
    *
    */
   I_CHAR getFillCharacter(
      const ClientLocale *pClientLocale = 0 
      ) const;

   /**
    * Returns the type used to filter the values of DataElement
    * objects associated with this DataElementProperties.
    *
    * @return Returns an ELEMENTTYPE enum, that is the type used to filter,
    *         which can be STRING, INTEGER, DECIMAL, BINARY, BOOLEAN or
    *         NO_TYPE.
    *
    */
   enum ELEMENTTYPE  getFilterType() const
   {
      return _items.filterType;
   }

   /**
    * Returns the justification of DataElement objects associated
    * with this DataElementProperties.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return a JUSTIFICATION enum, which can be LEFT, RIGHT,
    *         CENTER, or NO_JUSTIFICATION.
    */
   enum JUSTIFICATION getJustification(
      const ClientLocale *pClientLocale = 0 
      ) const;

   /**
    * Returns whether the default value of DataElement objects associated
    * with this DataElementProperties is NULL_VALUE
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return true if NULL_VALUE is the default, false otherwise
    */
   bool getDefaultValueIsNull(
      const ClientLocale *pClientLocale = 0 
      ) const;

   /**
    * Returns the mask used to format the values of DataElement
    * objects associated with this DataElementProperties.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return the mask used to format the values.
    *
    */
   DString getMask( const ClientLocale *pClientLocale = 0 ) const;

   ELEMENTTYPE getTypeFromString( const DString &fieldType );
   JUSTIFICATION getJustificationFromChar( I_CHAR chJust );

   /**
    * For i18n types, returns the mask used to format the values of DataElement
    * objects associated with this DataElementProperties when dealing with a
    * host.
    *
    * @return the mask used to format the values.
    *
    */
   DString getHostMask() const;

   /**
    * Checks if rounding is enabled for this DataElementProperties.
    *
    * @return  true if rounding is enabled, false otherwise.
    *
    */
   bool getRounding() const
   {
      return _items.rounding;
   }

   /**
    * Returns the stored type of the DataElementProperties object.
    *
    * @return Returns an enum ELEMENTTYPE.
    *
    */
   enum ELEMENTTYPE getStoredType() const
   {
      return _items.storedType;
   }

   /**
    * Gets the flag that forces DataElements to only
    * accept values that are in their substitution maps.
    *
    * @return true if only substitutions may be set, false otherwise.
    */
   bool getForceMatching() const
   {
      return _items.forceMatching;
   }

   /**
    * Return a string with all of the keys from this DataElement's
    * substitutions.  The keys are data that the host understands.
    *
    * @param keyValues - this will be set with all of the keys.
    * @param separateWithEOLs
    *                  - true if the keys in keyValues should be separated with EOL
    *                  chars, false if semicolons should be used.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @param usePropertiesOrder
    *                  - true if the keys in the return string should be in the same
    *                  order as specified in the properties file (or the sequence order
    *                  in the data dicitonary).
    * @return true if substitutions exist, false otherwise
    */
   bool getAllKeys( DString &keyValues, bool separateWithEOLs = false,
                    const ClientLocale *pClientLocale = 0,
                    bool usePropertiesOrder = false );

   /**
    * Fills the input string with the substitutes (that is, the "y", or display
    * data of the x=y pairs) from this
    * DataElementProperties object's substitution list.
    *
    * @param subValues - (out) filled with the "y" of the x=y pairs from the
    *        substitution list.
    * @param separateWithEOLs -
    *                  - true if the substitutes in return string should be
    *                  separated with EOL chars, false if semicolons should be
    *                  used.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @param usePropertiesOrder
    *                  - true if the keys in the return string should be in the same
    *                  order as specified in the properties file (or the sequence order
    *                  in the data dicitonary).
    * @return true if this DataElementProperties object has a substitution
    *         list, false otherwise.
    *
    */
   bool getAllSubstitutes( DString &subValues,
                           bool separateWithEOLs = false,
                           const ClientLocale *pClientLocale = 0,
                           bool usePropertiesOrder = false );

   /**
    * Fills the input string with the x=y pairs from this
    * DataElementProperties object's substitution list.
    *
    * @param subValues - (out) filled with the x=y pairs from the
    *        substitution list.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return true if this DataElementProperties object has a substitution
    *         list, false otherwise.
    *
    */
   bool getAllSubstituteValues( DString &subValues,
                                const ClientLocale *pClientLocale = 0,
                                bool usePropertiesOrder = false );

   /**
    * Gets the default value for this DataElementProperties object.
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        return data.
    * @return const reference to default value of the DataElementProperties.
    *
    */
   virtual const DString &getDefaultValue(
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * For i18n date types, return the object that performs the locale-
    * specific formatting for display.
    *
    * @param clientLocale - the desired locale/market/client for the
    *        formatter
    * @return the formatting object
    */
   JavaSimpleDateFormat * getDateDisplayFormatter(
      const ClientLocale &clientLocale  ) const;

   /**
    * For i18n date types, return the object that performs the locale-
    * specific formatting for dealing with the host.
    *
    * @return the formatting object
    */
   JavaSimpleDateFormat * getDateHostFormatter() const;

   /**
    * Get the label for the DataElement.  This maps to the
    * locale-specific label on fields in the data dictionary.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        data
    * @return reference to the label
    */
   const DString &getFieldLabel(
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * For i18n numeric types, return the object that performs the locale-
    * specific formatting for display.
    *
    * @param clientLocale - the desired locale/market/client for the
    *        formatter
    * @return the formatting object
    */
   JavaDecimalFormat * getNumberDisplayFormatter(
      const ClientLocale &clientLocale ) const;

   /**
    * For i18n numeric types, return the object that performs the locale-
    * specific formatting for dealing with the host.
    *
    * @param locale - the locale of the desired formatter
    * @return the formatting object
    */
   JavaDecimalFormat * getNumberHostFormatter() const;

   /**
    * Gets the first matching key from the substitution list for the
    * given value.  If this DataElementProperties object does not
    * have a substitution list, the input value is returned.
    *
    * @param value - (in) the value to search for in the substitution
    *        list.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data
    * @return the key for the input value, or the
    *         input value if this DataElementProperties object doesn't have
    *         a substitution list.
    *
    */
   DString getKeyFromValue( const DString &value,
                            const ClientLocale *pClientLocale = 0 ) const;

   /**
    * If this DataElementProperties object has a substitution map
    * with x=y values, this function returns the "y" for a given
    * "x".  If this DataElementProperties object does not have a
    * substitution map, then "x" is returned.
    *
    * @param subValue - (in) the value to search for in the
    *                 substitution map. This would be valid host data.
    * @param pClientLocale - the desired locale/market/client for the
    *        return data
    * @return the substituted value (i.e. display data) for the given subValue.
    */
   DString getSubstituteValue( const DString &subValue,
                               const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Returns the id of the DataComponentProperties object.
    *
    * @return the id of the object.
    *
    */
   virtual unsigned long getId() const { return _ulongId; };

   /**
    * Returns the id of the DataComponentProperties object.
    *
    * @return the id of the object.
    *
    */
   const DString &getName() const { return _name; };

   /**
    * Set the id of this object.
    *
    * @param _lid
    */
   virtual void setId( unsigned long lId ){ _ulongId = lId; };

   /**
    * Checks if this DataElementProperties object has a mask.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        mask
    * @return true if this object has a mask, false otherwise.
    *
    */
   bool hasMask( const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Checks if this DataElementProperties object has a host mask.
    *
    * @return true if this object has a mask, false otherwise.
    *
    */
   bool hasHostMask();

   /**
    * Checks if this DataElementProperties object has a substitution
    * list.
    *
    * @param pClientLocale - the desired locale/market/client for the
    *        substitutes
    * @return true if this object has a substitution list, false otherwise.
    *
    */
   bool hasSubstitutes( const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Checks if the given value is a valid value for this
    * DataElementProperties object.
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param valueString - (in) contains the value to check.
    * @param pClientLocale - the desired locale/market/client for the
    *        data
    * @return true if the given value is valid for this
    *         DataElementProperties object, false otherwise.
    *
    */
   virtual bool isValid( const DString &valueString,
                         const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Checks if the given value is a valid value for the host
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param valueString - (in) contains the value to check.
    * @return true if the given value is valid for this
    *         DataElementProperties object, false otherwise.
    *
    */
   virtual bool isValidForHost( const DString &valueString ) const;

   /**
    * Checks if the input key is a valid key in this
    * DataElementProperties object's substitution list.
    *
    * @param key - (in) the key to search for.
    * @param pClientLocale - the desired locale/market/client for the
    *        data
    * @return true if the input key is a key in the substitution list,
    *         false if it isn't, and false if this object doesn't have a
    *         substitution list.
    *
    */
   bool isValidKey( const DString &key,
      const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Checks if the input value is a valid value in this
    * DataElementProperties object's substitution list.
    *
    * @param value - (in) the value to search for.
    * @param pClientLocale - the desired locale/market/client for the
    *        data
    * @return true if the input value is a value in the substitution list,
    *         false if it isn't, and false if this object doesn't have a
    *         substitution list.
    *
    */
   bool isValidValue( const DString &value,
                      const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Takes a native value and converts it to a formatted value.
    * Converts a value from what comes from a ViewManager call,
    * into something that makes sense to the user.
    *
    * @param nativeValue - (in/out) on entry contains the native value,
    *        on exit is set to the equivalent formatted value.
    *
    */
   void mapToFormattedValue( DString &nativeValue ) const;

   /**
    * Takes a formatted value and converts it to a native value.
    *
    * @param formattedValue - (in/out) on entry contains the formatted
    *        value, on exit is set to the equivalent native value.
    *
    */
   void mapToNativeValue( DString &formattedValue ) const;

   /**
    * Takes a masked value and removes mask characters from it, IF
    * the mask characters are in their correct positions.  If they
    * are not, the mask characters are left in.
    *
    * @param maskedValue - (in/out) the value that may or may not contain
    *        mask characters.
    * @param pClientLocale - the desired locale/market/client for the
    *        data
    * @param i18nFormat - for the i18n types, a custom format for the data
    * @return The input maskedValue with proper mask characters
    *         removed.
    *
    */
   DString &removeMaskFromValue( DString &maskedValue,
                                 const ClientLocale *pClientLocale = 0,
                                 const DString &i18nFormat = EMPTY_STRING ) const;
   typedef
      std::map< DString, DString, CaseInsensitiveCompare > SubstitutionMap;
   typedef std::vector< DString > SubStringVectorType;

   /**
    * Turns on or off the ability to force values passed into a
    * DataElement object's setValue function to match the keys and
    * values in this DataElementProperties object's substitution
    * list.
    *
    * @param forceMatching - (in) specifies if the forced matching should be
    *        turned on or off.
    *
    */
   void setForceMatching( bool forceMatching );

   /**
    * Add a locale entry (actually a base/client/market entry) for the field.
    * The items here are part of the field and are overrideable, but not
    * language specific.
    *
    * @param clientLocale
    *               - the client/market/language for the items (langauge is
    *               ignored)
    * @param locFieldMinLength
    *               - the minimum length of the field for this ClientLocale
    * @param fAllowNull
    *               - true if this field may be set to
    *               DataElementProperties::NULL_VALUE
    *               using the DataElement::setNull method
    * @return true if successfully added
    */
   bool addBaseLocale( const ClientLocale &clientLocale,
                       unsigned long locFieldMinLength,
                       bool fAllowNull );

   /**
    * Add a locale entry (actually a base/client/market entry) for the field.
    * The items here are part of the field and are overrideable, and are
    * also language specific.
    *
    * @param clientLocale
    *                - the client/market/language for the items
    * @param locFillChar
    *                - the fill character for this field in the specified
    *                ClientLocale
    * @param locJust - the justification (LEFT/RIGHT) for this field in the
    *                specified ClientLocale
    * @param locDefaultValue
    *                - the default value for this field in the specified
    *                ClientLocale
    * @param locFieldLabel
    *                - the label for this field in the specified
    *                ClientLocale
    * @param fDefaultValueIsNull
    *                - true if the default value for this element is
    *                NULL
    * @return true if successfully added
    */
   bool addFieldLocale( const ClientLocale &clientLocale, I_CHAR locFillChar,
                        enum JUSTIFICATION locJust,
                        const DString &locDefaultValue,
                        const DString &locFieldLabel,
                        bool fDefaultValueIsNull );
   bool addFieldLocale( const ClientLocale &clientLocale,
                        I_CHAR locFillChar,
                        I_CHAR locJustChar,
                        const DString &locDefaultValue,
                        const DString &locFieldLabel,
                        bool fDefaultValueIsNull );

   /**
    * Add a locale entry (actually a base/client/market entry) for the mask for
    * this field.
    * The mask item here is overrideable, and is also language specific.
    *
    * @param clientLocale
    *                - the client/market/language for the items
    * @param locMask - the mask for this field in this ClientLocale
    * @return true if successfully added
    */
   bool addMaskLocale( const ClientLocale &clientLocale,
                       const DString &locMask );

   /**
    * Add a locale entry (actually a base/client/market entry) for the
    * substitution set forthis field.
    * The substitution items here is overrideable, and are also language
    * specific.
    *
    * @param clientLocale
    *               - the client/market/language for the items
    * @param locSubString
    *               - the idi string of key=value pairs
    * @return true if successfully added
    */
   bool addSubsLocale( const ClientLocale &clientLocale,
                       const DString &locSubString );
   /**
    * Check to see if a DEP has a locale for the "field" items - those fields
    * that are overrideable by clients and markets, and are also language
    * specific (except for masks and substitutions)
    * For this check, the exact ClientLocale (market/client/language) is
    *  checked.
    *
    * @param clientLocale - the desired locale/market/client for the
    *        data
    * @param checkRepository
    *               - if true, check to see if the data dictionary has any locale
    *               iformation for the specified locale
    * @return true if found, false otherwise
    */
   bool hasFieldLocale( const ClientLocale &clientLocale,
                        bool checkRepository = false );
   /**
    * Load the DEP's info for the specified locale from the
    * repository (data dictionary).
    *
    * @param clientLocale
    *               - the desired locale/market/client to load
    * @return true if successful, false otherwise
    */
   bool getLocale( const ClientLocale &clientLocale );

private:
   friend DataPropertiesImpl;
   static const DString EMPTY_STRING;
   mutable CriticalSectionLock m_itemsLock;
   DString _name;
   unsigned long _ulongId;

   // These are part of base only
   typedef struct _ITEMS
   {
      enum ELEMENTTYPE storedType;

      // Formatting characteristics...
      unsigned long maxLength;

      // Formatting characteristics specific for stored strings (inherit?)...
      unsigned long decimalPlace;
      enum ELEMENTTYPE filterType;
      bool rounding;
      bool  forceMatching;

   } Items;

   // These are part of base and market/client, but not lang
   class BaseAndMarketItems
   {
   public:

      // Formatting characteristics...
      unsigned long minLength;
      bool fAllowNull;

      BaseAndMarketItems() :
         minLength( 0 ), fAllowNull( false )
      {
      }
   };


   // These are part of base, lang-specific, client and market
   class MaskAndOverrides
   {
   public:

      DString mask;

      // Used by Date(D), InternationalDecimal(DN), Currency($), and
      // Percent(%) TYPES.
      JavaSimpleDateFormat *pDateDisplayFormatter;
      JavaDecimalFormat *pNumberDisplayFormatter;

      MaskAndOverrides() :
         mask( I_( "" ) ), pDateDisplayFormatter( 0 ),
         pNumberDisplayFormatter( 0 )
      {
      }

      ~MaskAndOverrides();
   };

   // These are part of base, lang-specific, client and market
   class SubsAndOverrides
   {
   public:

      SubstitutionMap substitutionMap;
      SubStringVectorType substitutionVector;


      SubsAndOverrides() :
         substitutionMap(), substitutionVector()
      {
      }
      ~SubsAndOverrides()
      {
      }
   };

   // These are part of base, lang-specific, client and market
   class FieldAndOverrides
   {
   public:

      I_CHAR fillCharacter;
      enum JUSTIFICATION justification;
      DString defaultValue;
      DString fieldLabel;
      bool fDefaultValueIsNull;

      FieldAndOverrides() :
         fillCharacter( ' ' ), justification( LEFT ), defaultValue( I_( "" ) ),
         fieldLabel( I_( "" ) ), fDefaultValueIsNull( false )
      {
      }

      ~FieldAndOverrides()
      {
      }
   };

   // Host mask is always in the enUS locale and is not overridable in markets,
   // so we put it here
   mutable DString m_dstrHostMask;
   mutable JavaSimpleDateFormat *pDateHostFormatter;
   mutable JavaDecimalFormat *pNumberHostFormatter;

   typedef std::multimap<
      ClientLocale, MaskAndOverrides *,
      ClientLocale_multimap_compare > MaskAndOverridesMapType;
   MaskAndOverridesMapType m_mapMaskItems; //@@@DDS
   MaskAndOverridesMapType::const_iterator findMask( const ClientLocale & clientLocale ) const;

   typedef std::multimap<
      ClientLocale, SubsAndOverrides *,
      ClientLocale_multimap_compare > SubsAndOverridesMapType;
   SubsAndOverridesMapType m_mapSubsItems; //@@@DDS
   SubsAndOverridesMapType::const_iterator findSubs( const ClientLocale & clientLocale ) const;

   typedef std::multimap<
      ClientLocale, FieldAndOverrides *,
      ClientLocale_multimap_compare > FieldAndOverridesMapType;
   FieldAndOverridesMapType m_mapFieldItems; //@@@DDS

   void fillSubstitutionMapFromString( const DString &subString,
                                       SubstitutionMap &subMap,
                                       SubStringVectorType &subVector );
   FieldAndOverridesMapType::const_iterator findField( const ClientLocale & clientLocale ) const;

   void _formatDateTime(
      DString &valueString,
      const ClientLocale &clientLocale,
      MaskAndOverrides *rpItems,
      const DString &i18nFormat 
      ) const;
   void _formatDecimal(
      DString &valueString,
      const ClientLocale &clientLocale,
      const MaskAndOverrides *rpItems
      ) const;
   void _formatInteger(
      DString &valueString,
      const ClientLocale &clientLocale,
      const MaskAndOverrides *rpItems
      ) const;
   void _formatNewNumber(
      DString &valueString,
      const ClientLocale &clientLocale,
      MaskAndOverrides *rpItems,
      const DString &i18nFormat 
      ) const;
   void _formatString(
      DString &valueString,
      const ClientLocale &clientLocale,
      const MaskAndOverrides *rpItems
      ) const;
   // Will potentially change valueString even if fail
   bool _formatValue(
      DString &valueString,
      bool checkValidity 
      ) const;
   bool getCfgHostMask( ELEMENTTYPE type, DString &mask ) const;

   bool getCfgDisplayMask( ELEMENTTYPE type, const ClientLocale &clientLocale,
                           DString &mask );

   JavaSimpleDateFormat *_getDateDisplayFormatter(
      MaskAndOverrides *rpItems,
      const ClientLocale &clientLocale
      ) const;
   JavaDecimalFormat *_getNumberDisplayFormatter(
      MaskAndOverrides *rpItems,
      const ClientLocale &clientLocale
      ) const;

   DataElementProperties::FieldAndOverrides *DataElementProperties::getFieldItems(
      const ClientLocale *pClientLocale
      ) const;

   DataElementProperties::MaskAndOverrides *DataElementProperties::getMaskItems(
      const ClientLocale &clientLocale ) const;

   DataElementProperties::SubsAndOverrides *DataElementProperties::getSubsItems(
      const ClientLocale *pClientLocale ) const;

   /**
    * Formats string passed in according to format flags and associated masks
    *  and substitutes.
    * 
    * @param strOut - (in/out) contains raw data on input and formatted data 
    *  upon completion.
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
    * @returns reference to string passed in
    * @exception ConditionException&
    *                   ConditionException& out of memory
    *                   ConditionException& invalid format string passed in
    */
   DString &getFormattedValue(
      DString &strOut,
      unsigned long formatFlags,
      const ClientLocale *rpClientLocale,
      const DString &i18nFormat
      ) const;

   /**
    * Gets the value of an element from a raw host buffer area.
    * 
    * @param strOut - this will be filled with the value of the element.
    * @param rpDataBuffer - data buffer area to get field from.
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
    * @returns reference to string passed in
    * @exception ConditionException&
    *                   ConditionException& out of memory
    *                   ConditionException& invalid format string passed in
    */
   DString &getValueFromBuffer(
      DString &strOut,
      const unsigned char *rpDataBuffer,
      unsigned long formatFlags,
      const ClientLocale *rpClientLocale,
      const DString &i18nFormat
      ) const;

   /**
    * Gets the value of a binary element from a raw host buffer area.  The max
    *  length moved is the lesser of the buffer length and the element length.
    * 
    * @param id     - (in) the data dictionary id of the field to get.
    * @param binBuff - this will be filled with the value of the
    *                   element.
    * @param rpDataBuffer - data buffer area to get field from.
    * @param buffLength - (in) length of buffer passed in.
    * @param returnedLength - (out) length of data moved in to buffer
    * @return enum SUCCESS or NOT_FOUND if field not in data dictionary.  All
    *    other errors should throw.
    * @exception ConditionException&
    *                   ConditionException& out of memory
    */
   void getValueFromBuffer(
      unsigned char *binBuff,
      const unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;
   /**
    * Checks if the given value is a valid value for this
    * DataElementProperties object that is an i18n type.
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param valueString - (in) contains the value to check.
    * @param rpClientLocale - the desired locale/market/client for the
    *        data
    * @return true if the given value is valid for this
    *         DataElementProperties object, false otherwise.
    *
    */
   bool _isI18NValid(
      const DString &valueString,
      const ClientLocale &rpClientLocale 
      ) const;

   /**
    * Checks if the given value is a valid value for the host
    *
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    *
    * @param valueString - (in) contains the value to check.
    * @return true if the given value is valid for this
    *         DataElementProperties object, false otherwise.
    *
    */
   bool _isI18NValidForHost(
      const DString &valueString
      ) const;

   DataElementProperties &operator=( const DataElementProperties &copy );

   friend i_istream &operator>> ( i_istream &stream,
                                DataElementProperties &properties );

   friend i_ostream &operator<< ( i_ostream &stream,
                                const DataElementProperties &properties );

   // For these the Client Locale's language will always be "enUS".
   typedef std::map<
      ClientLocale, MultiKeyPointerMapElement< BaseAndMarketItems >,
      std::less< ClientLocale > > BAMItemsMapType;
   BAMItemsMapType m_mapBaseAndMarketItems; //@@@DDS
   BAMItemsMapType::const_iterator findBaseAndMarket( const ClientLocale & clientLocale ) const;

   Items _items;

   const BaseAndMarketItems * _getBAMItems( const ClientLocale& cloc ) const;

   bool m_hasMasks;
   bool m_hasSubstitutes;
   Configuration *_cfgDisplayMasks;
   Configuration *_cfgHostMasks;

   void _setDecimalFormatSymbols( JavaDecimalFormat& formatter,
                                  const DString& dstrLocale ) const;
   /**
    * Set the field value in the specified buffer to the specified value.
    *
    * @param value - (in) contains the value to set.
    * @param rpDataBuffer - Buffer that the field is based off of.
    * @param rpClientLocale - the locale/market/client of the passed in value
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
    */
   bool setValueInBuffer(
      const DString &valueIn,
      unsigned char *rpDataBuffer,
      const ClientLocale *rpClientLocale,
      bool displayFormat,
      const DString &i18nFormat
      ) const;

   /**
    * Set the binary field value to the specified value.
    *
    * @param binBuff - (in) contains the value to set.
    * @param rpDataBuffer - Buffer that the field is based off of.
    * @param buffLength - length of buffer input
    * @param returnLength - length of input actually copied
    * @return true if successful.
    */
   bool setValueInBuffer(
      unsigned char *binBuff,
      unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;

   /**
    * Set the field value in the specified buffer to the specified value.  This
    *  should only be called to pass in values directly from host.
    *
    * @param value - (in/out) contains the value to set.  Will have actual value
    *  stored upon return.
    * @param rpDataBuffer - Buffer that the field is based off of.
    * @return true if the assignment was successful,
    *         or false if the assignment was unsuccessful
    */
   bool setValueInBufferFromHost(
      DString &valueIn,
      unsigned char *rpDataBuffer
      ) const;

   /**
    * !!! This method may not be permanent and may be removed in future versions
    * !!! of Infra.  If invalid data is set in, the user must be aware that
    * !!! there may be undetermined and undesired side effects in other methods.
    *
    * Sets the specified element exactly to the passed-in value with truncation
    * if necessary.
    *
    * @param value - (in) contains the value to set.
    * @param rpDataBuffer - Buffer that the field is based off of.
    */
   void unauthorizedSetValueInBuffer(
      const DString &valueIn,
      unsigned char *rpDataBuffer
      ) const;

   void _unformatDateTime(
      DString &valueString,
      const ClientLocale &rpClientLocale,
      MaskAndOverrides *rpItems,
      const DString &i18nFormat
      ) const;

   void _unformatNewNumber(
      DString &valueString,
      const ClientLocale &rpClientLocale,
      MaskAndOverrides *rpItems,
      const DString &i18nFormat
      ) const;

   void _unformatOldTypes(
      DString &valueString,
      const ClientLocale &rpClientLocale,
      const MaskAndOverrides *rpItems
      ) const;
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
// $Log:   Y:/VCS/iFastAWD/inc/dataelementproperties.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:54   kovacsro
//Initial revision.
// 
//    Rev 1.44   Jun 29 2001 12:38:42   DT11159
// Simplified addSubsLocale method.
// 
//    Rev 1.43   May 18 2001 15:29:16   dt24433
// Added setValueInBufferFromHost.
// Formatting support.
// Changes for Guard\CriticalSectionLock.
// 
//    Rev 1.42   Mar 29 2001 13:05:24   dt24433
// Made isi18NValid and isi18NValidForHost private.
// 
//    Rev 1.41   Mar 26 2001 16:12:14   dt24433
// Added getFormattedValue method.
// 
//    Rev 1.40   Mar 24 2001 13:54:22   dt24433
// Changed 3 maps to multi-maps to provide more efficient lookup for market/client information.
// Keyed by ClientLocale, but using locale only comparison with additional logic provided in find
// methods.
// 
//    Rev 1.39   Mar 22 2001 16:29:30   dt24433
// Implemented unauthorizedSetElementValue.
// Fixed I18N_INTEGER default.
// Made isI18Valid and isI18ValidForHost const.
// 
//    Rev 1.38   Mar 21 2001 11:38:28   dt24433
// Fixed so header file does not force inclusion of ICU libraries for users.
// 
//    Rev 1.37   Mar 02 2001 14:48:00   dt24433
// Added support for get/set of field values directly to/from the data object's buffer.
// Made several methods const.
// getFieldLabel and getDefaultValue now return const DString & instead of DString.
// getId has been split into getId and getName as appropriate.
// removed/consolidated code due to always loading all locales for an element up front.
// Implemented quick flags for hasMask and hasSubstitute for performance.
// Use mutex instead of SWMR lock.
// 
//    Rev 1.36   Jan 19 2001 16:58:46   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.35   Jan 08 2001 15:18:40   dt24433
// Changed some pointer parms to references.
//
//    Rev 1.34   Jan 04 2001 16:48:10   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.33   Nov 22 2000 07:01:24   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.32   Oct 10 2000 08:51:48   dt17817
// Add ability to override default formatting for a locale based on registry input
//
//    Rev 1.31   Sep 05 2000 06:05:50   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.30   Aug 24 2000 11:53:34   dtwk
// Update comments
//
//    Rev 1.29   Aug 24 2000 07:17:40   dtwk
// Add in more support for clients and markets
//
//    Rev 1.28   Aug 09 2000 08:35:24   dtwk
// Add in support for clients and markets
//
//    Rev 1.27   Jun 08 2000 11:50:50   dtwk
// Add support for case-insensitivity
//
//    Rev 1.26   Jun 05 2000 07:44:14   dtwk
// Fix thread-safety of i18n types
//
//    Rev 1.25   May 31 2000 09:31:34   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.24   Apr 11 2000 13:36:48   dtwk
// Synch up with ICU class changes
//
//    Rev 1.23   Apr 10 2000 11:48:18   dtwk
// Updates for thread-safety
//
//    Rev 1.22   Jan 16 2000 14:08:16   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.21   Dec 19 1999 09:28:30   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.20   Oct 06 1999 11:34:24   DCYK
// Add support for redefines.
//
//
//    Rev 1.19   Oct 04 1999 15:25:50   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.18   Oct 04 1999 10:23:46   DCYK
// Threading fixes.
//
//
//    Rev 1.17   Sep 03 1999 15:28:56   dtwk
// Add constructor and destructor to _I18NItems to plug memory leaks when making standalone
// DEP object instances
//
//    Rev 1.16   Aug 20 1999 15:36:38   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.15   Aug 12 1999 09:45:56   DCYK
// Add ability to get substitution values in properties order or alphabetical order.
//
//
//    Rev 1.14   Aug 06 1999 14:22:38   DCYK
// Performance improvements.
//
//
//    Rev 1.13   Aug 05 1999 16:38:32   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.12   Jul 28 1999 14:20:10   DCYK
// Performance improvements.
//
//
//    Rev 1.11   Jun 06 1999 13:25:28   DTWK
//
//
//    Rev 1.10   May 25 1999 09:40:12   DTWK
// Add I18N_INTEGER and I18N_TIME types
//
//    Rev 1.9   May 24 1999 10:31:06   DTWK
// Add internationalized formatting for new date and number types using JNI
//
//    Rev 1.8   May 06 1999 16:44:52   DCYK
//
//
//    Rev 1.7   Apr 20 1999 16:48:56   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.6   Mar 05 1999 10:21:06   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Feb 11 1999 15:02:32   DCYK
// Add support for binary elements.
//
//
//    Rev 1.4   Jan 28 1999 14:06:00   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:36   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 14 1998 11:32:22   dcyk
// Updated header file documentation.
//
//
//    Rev 1.0   29 Jul 1998 20:36:56   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.17   Nov 10 1997 15:00:08   dcyk
//
//
//    Rev 1.16   07 Aug 1997 15:07:28   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.15   05 Aug 1997 13:56:48   dcyk
// Added documentation of the new
// percentage mask for formatUsingMask.
//
//
//    Rev 1.14   24 Jul 1997 09:42:06   dcyk
// Switched to UINT, ULONG, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.13   08 Jul 1997 09:13:46   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.12   13 Jun 1997 16:18:52   dcyk
//
//
//    Rev 1.11   May 29 1997 09:52:46   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.10   May 06 1997 10:15:58   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.9   May 01 1997 08:40:14   dcyk
// Added documentation.
//
//
//    Rev 1.8   Apr 11 1997 08:57:44   dcyk
//
//
//    Rev 1.7   Apr 04 1997 09:51:56   dcyk
//
//
//    Rev 1.6   Mar 25 1997 15:53:28   dcyk
// Removed friend declarations of DataProperties
// and DataElement.
//
// Made items struct private.
//
// Added mapToNativeValue & mapToFormattedValue.
//
// Added getDefaultValue that returns a string.
//
//
//    Rev 1.5   Feb 11 1997 14:35:14   dcyk
// Added support for Rogue Wave's STL.
// Added support for rounding.
//
//
//    Rev 1.4   Jan 19 1997 12:54:28   DRUS
//
//
//    Rev 1.3   Dec 31 1996 13:32:58   DRUS
// Made the class exportable.  Added getStoredType() to provide access
// to the actual native type.  Added isValid() to allow strings to be checked
// for validity against the settings of the class.
//
//    Rev 1.2   Nov 21 1996 14:37:06   DRUS
// Fixed PVCS comment syntax errors (again).
//
//    Rev 1.1   Nov 20 1996 17:07:14   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:16   DRUS
//
//
//

#endif // DataElementProperties_hpp

