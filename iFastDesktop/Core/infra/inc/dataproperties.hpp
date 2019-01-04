#ifndef DATAPROPERTIES_HPP
#define DATAPROPERTIES_HPP

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

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
   #include <vector>
#endif 

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif
   
#ifndef DATA_HPP
   #include "data.hpp"
#endif 
#ifndef DATACOMPONENTPROPERTIES_HPP
   #include "datacomponentproperties.hpp"
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class DIDBRKR_LINKAGE DataPropertiesImpl;
class PropertyRepository;

class DIDBRKR_LINKAGE DataProperties : public DataComponentProperties
{
public:
   enum EReturn
   {
      SUCCESS,
      NOT_FOUND,
      FAILURE
   };
   /**
    * Creates a DataProperties object.
    * 
    * @param id     - (in) identifier for this DataProperties object.  If
    *               it doesn't contain "Repeat_Record", then it is assumed to be a
    *               file name.
    * @param clientLocale - while kept to keep the interface from changing, this
    *        parameter is ignored
    * @param repeatable - (in) specifies if the DataProperties object is
    *                   repeatable.  Defaults to false.
    * @param repeatSizeComponentName
    *                   - obsolete
    * @param fixedRepeatSize
    *                   - obsolete
    */
   DataProperties( const DString &id = NULL_STRING,
                   const ClientLocale &clientLocale =
                      ClientLocale::getDefaultClientLocale(),
                   bool repeatable = false,
                   const DString &repeatSizeComponentName = NULL_STRING,
                   unsigned long fixedRepeatSize = 0);

   /**
    * Creates a DataProperties object.
    * 
    * @param id - (in) data dictionary identifier for this DataProperties object
    * @param clientLocale - while kept to keep the interface from changing, this
    *        parameter is ignored
    * @param repeatable - (in) specifies if the DataProperties object is
    *        repeatable.  Defaults to false.
    * @param repeatSizeComponentName - obsolete
    * @param fixedRepeatSize - obsolete
    * @return Returns a DataProperties object.
    *
    */
   DataProperties( long id,
                   const ClientLocale &clientLocale =
                      ClientLocale::getDefaultClientLocale(),
                   bool repeatable = false,
                   const DString &repeatSizeComponentName = NULL_STRING,
                   unsigned long fixedRepeatSize = 0);

   /**
    * Creates a new DataProperties object identical to the one
    * passed in.
    * 
    * @param copy - (in) the original
    * @return Returns a new DataProperties object.
    *
    */
   DataProperties( const DataProperties &copy );

   /**
    * Create a DataProperties wrapper for a given DataPropertiesImpl
    * 
    * @param dpi
    */
   DataProperties( DataPropertiesImpl *dpi );

   virtual ~DataProperties();

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)
   PVOID operator new (size_t nBytes);
   VOID operator delete (PVOID pv);
#endif

   /**
    * Tests if two DataProperties objects are equal.
    * 
    * @param properties - (in) reference to the DataProperties
    *        object to compare against this DataProperties object.
    * @return true if the two DataProperties objects are equal.
    *
    */
   virtual bool operator==( const DataProperties &properties ) const;

   /**
    * Tests if two DataProperties objects are not equal.
    * 
    * @param properties - (in) reference to the DataProperties
    *        object to compare against this DataProperties object.
    * @return  true if the two DataProperties objects are not equal.
    *
    */
   virtual bool operator!=( const DataProperties &properties ) const
                                             { return !(*this == properties); };

   /**
    * Recalculate the indexes for accessing the properties in
    * the sequence defined in the data dicitonary (properties
    * order)
    * 
    * @param dataCompProps
    *               - the properties to index
    */
   void assignVectorIndexes( DataComponentProperties &dataCompProps );
   
   /**
    * Checks if the specified DataElementProperty exists on this
    * DataProperties object.
    * 
    * @param propertyName - (in) contains the name of the
    *        element to search for.
    * @return true if the specified element exists, false otherwise.
    *
    */
   bool exists( const DString &propertyName ) const;

   /**
    * Checks if the specified DataElementProperty exists on this
    * DataProperties object.
    * 
    * @param id - (in) the data dictionary id of the element to search for.
    * @return true if the specified element exists, false otherwise.
    *
    */
   bool exists( long id ) const;

   /**
    * Not implemented.
    * 
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    * 
    * @param valueString
    *               -
    * @param checkValidity
    *               -
    * @return 
    */
   virtual bool formatValue( DString &valueString,
                             bool checkValidity = true ) const;
   
   typedef std::vector< DataComponentProperties * > DCPPtrVectorType;

   /**
    * Find a property inside a vector of properties.
    * 
    * @param propVector - a vector of DCP pointers
    * @param propPtr - a pointer to the DCP to find.
    * @return an interator pointing to the located property, or
    *         propVector::end() if not found
    */
   DCPPtrVectorType::iterator findPropertyInVector(
                                          DCPPtrVectorType &propVector,
                                          DataComponentProperties *propPtr ) const;

   /**
    * Not implemented.
    * 
    * @param pClientLocale - the desired locale/market/client for the 
    *        return data
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    * 
    */
   virtual const DString &getDefaultValue(
      const ClientLocale *pClientLocale = 0
      ) const;

   /**
    * Returns the Id for specified name
    *
    * @param name
    * @return id or 0xFFFFFFFF for not found
    */
   unsigned long getFieldIdFromName( const DString &name ) const;

   /**
    * Gets the name of the file used to create this DataProperties
    * object.  If the object came from the Property Repository 
    * (data dictionary), the return will be the data set name.
    * 
    * @return the file/data set name.
    */
   DString getFileName() const;

   /**
    * Get the length of the non-repeatable area in bytes.
    *
    * @return byte count
    */
   unsigned long getFixedByteLength() const;

   /**
    * Returns the id of the DataComponentProperties object.
    * 
    * @return the id of the object.
    *
    */
   virtual unsigned long getId() const;

   /**
    * Gets the maximum length of the elements of this DataProperties
    * object.
    * 
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    * 
    * @return the maximum length of the elements.
    *
    */
   virtual unsigned long getMaxLength() const;

   /**
    * Returns the name of the DataComponentProperties object.
    * 
    * @return the name of the object.
    *
    */
   const DString &getName() const;

   /**
    * Gets the specified property for this DataProperties object.
    * 
    * @param propertyName - (in) contains the name of the
    *        property to get.
    * @return a const reference to a DataComponentProperties object,
    *         which can then be typecast to a DataProperties or
    *         DataElementProperties object.
    * @exception ConditionException& - if the requested property does not exist
    *
    */
   const DataComponentProperties &getProperty(
                                         const DString &propertyName ) const;

   /**
    * Gets the property at the index in this DataProperties object.
    * 
    * @param index - (in) contains the index in the
    *        DataProperties object's property map.
    * @return a const reference to a DataComponentProperties object,
    *         which can then be typecast to a DataProperties or
    *         DataElementProperties object.
    * @exception ConditionException& - if the index is out of range.
    *
    */
   const DataComponentProperties& getProperty( unsigned long index ) const;

   const DataComponentProperties& getPropertyByFieldIndex( long id ) const;

   // repeat field counts as one
   /**
    * Gets the number of properties in this DataProperties object.
    * 
    * @return Returns an unsigned long, containing how many DataProperties
    *         and DataElementProperties objects are contained in this
    *         DataProperties object.
    *
    */
   unsigned long getPropertyCount() const;

   /**
    * Get a vector of fields that are currently redefining the field,
    * oldName.
    * 
    * @param oldName - a field that is currently setup to be redefinable
    * @param vecRedefines
    *                - this will be filled with the fields that redefine oldName.
    *                If oldName is not redefinable, this vector will be empty.
    */
   void getRedefines( const DString &oldName, string_vector &vecRedefines );

   /**
    * Get the maximum amount of storage required to
    * hold the contents of this object (if it was
    * streamed into a buffer, for example)
    * 
    * @return the maximum size.
    */
   virtual unsigned long getTotalMaxLength() const;

   /**
    * Return the toal number of lines required to display the
    * properties.  This is usually greater than the total number
    * of properties due to formatting and nesting of properties.
    * 
    * @return the total number of lines needed (for this format).
    */
   long getTotalNumberOfLines() const;

   /**
    * Return the total number of properties, including those nested
    * in repeatable areas.
    * 
    * @return the count.
    */
   long getTotalNumberOfProperties() const;

   /**
    * Get the index of the property from it's name in this
    * data set.
    * 
    * @param _name  - the name of the item
    * @return - the 0-based index into the properties
    */
   long getVectorIndexFromName( const DString &_name ) const;

   /**
    * Checks if the name and value pairs in the input string are
    * valid for this DataProperties object.
    * 
    *  ^SEE ALSO    : overridden from DataComponentProperties.
    * 
    * @param valueString - (in) contains name and value pairs.
    * @param pClientLocale - the desired locale/market/client for the 
    *        data
    * @return Returns a bool, true if the value for each name in the input
    *         string is valid, false if the value is not valid, and false if
    *         one of the names in the string is not a valid property name.
    *
    */
   virtual bool isValid( const DString &valueString,
                         const ClientLocale *pClientLocale = 0 ) const;

   /**
    * Stream out the properties in a readable / debug format
    * 
    * @param stream - the stream to receive the data
    * @param counter - ignored
    * @param lineNum - this will be set with the number of lines returned
    * @param viewName - this should be set to the view id
    * @param propName - ignored
    */
   void streamOutComponents( i_ostream &stream, unsigned long &counter,
                             unsigned long &lineNum, const DString &viewName,
                             const DString &propName );

private:
   friend Data;
   friend PropertyRepository;
   friend DataPropertiesImpl;

   friend i_istream &operator>> ( i_istream &stream,
                                DataProperties &properties );

   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< ( i_ostream &stream,
                                          const DataProperties &properties );

   friend i_istream &operator>> ( i_istream &stream,
                                DataPropertiesImpl &propertiesImpl );
   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< ( i_ostream &stream,
                                  const DataPropertiesImpl &propertiesImpl );
   friend EXPORTWIN i_istream & EXPORTOS2 operator>> ( i_istream &stream,
                                                     Data &data );
   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< ( i_ostream &stream,
                                                     const Data &data );

   bool _fUsingRepository;
   DataPropertiesImpl *_pImpl;
   
   DataProperties &operator= ( const DataProperties &copy );

   typedef std::vector< DataComponentProperties * > DCPPtrVectorType;

   DCPPtrVectorType getImplVector() const;
   const DString &getPropertyElementName( unsigned long index ) const;

//   long getOffset( unsigned long ulId ) const;

   /**
    * Gets the value of an element from a raw host buffer area.
    * 
    * @param id     - (in) the data dictionary id of the field to get.
    * @param strOut - this will be filled with the value of the
    *                   element.
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
    * @return enum SUCCESS or NOT_FOUND if field not in data dictionary.  All
    *    other errors should throw.
    * @exception ConditionException&
    *                   ConditionException& out of memory
    *                   ConditionException& invalid format string passed in
    */
   EReturn getValueFromBuffer(
      long id,
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
   EReturn getValueFromBuffer(
      long id,
      unsigned char *binBuff,
      const unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;
   /**
    * Set the id of this object.
    * 
    * @param _lid
    */
   virtual void setId( unsigned long lId );

   void setUsingRepository( bool fUsingRepository )
   {
      _fUsingRepository = fUsingRepository;
   }

   /**
    * Set the field value in the specified buffer to the specified value.
    *
    * @param id - (in) contains the field id.
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
    * @return SUCCESS if found, NOT_FOUND if field not in data dictionary or
    *    FAILURE if the assignment was unsuccessful.
    */
   EReturn setValueInBuffer(
      long id,
      const DString &valueIn,
      unsigned char *rpDataBuffer,
      const ClientLocale *rpClientLocale,
      bool displayFormat,
      const DString &i18nFormat
      ) const;

   /**
    * Set the binary field value to the specified value.
    *
    * @param id - (in) contains the field id.
    * @param binBuff - (in) contains the value to set.
    * @param rpDataBuffer - Buffer that the field is based off of.
    * @param buffLength - length of buffer input
    * @param returnLength - length of input actually copied
    * @return SUCCESS if found, NOT_FOUND if field not in data dictionary or
    *    FAILURE if the assignment was unsuccessful.
    */
   EReturn setValueInBuffer(
      long id,
      unsigned char *binBuff,
      unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;

   /**
    * Set the field value in the specified buffer to the specified value. This
    *  method should only be used to set values directly from host.
    *
    * @param id - (in) contains the field id.
    * @param value - (in/out) contains the value to set.  Will have actual value
    *  stored upon return.
    * @param rpDataBuffer - Buffer that the field is based off of.
    * @return SUCCESS if found, NOT_FOUND if field not in data dictionary or
    *    FAILURE if the assignment was unsuccessful.
    */
   EReturn setValueInBufferFromHost(
      long id,
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
    * @param id - (in) contains the field id.
    * @param value - (in) contains the value to set.
    * @param rpDataBuffer - Buffer that the field is based off of.
    */
   void unauthorizedSetValueInBuffer(
      long id,
      const DString &valueIn,
      unsigned char *rpDataBuffer
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
// $Log:   Y:/VCS/iFastAWD/inc/dataproperties.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:56   kovacsro
//Initial revision.
// 
//    Rev 1.25   May 18 2001 15:30:32   dt24433
// Bin field support.  Added setValueInBufferFromHost.
// 
//    Rev 1.24   Mar 22 2001 16:27:48   dt24433
//  
// 
//    Rev 1.23   Mar 09 2001 11:23:56   dt24433
// Changed getPropertyElementName to return const DString &
// 
//    Rev 1.22   Mar 02 2001 14:09:32   dt24433
// Added support for get/set values directly from/to data object's buffer.
// getId was split to getId and getName as appropriate.
// getFixedLength was changed to getFixedByteLength because it will now always return length in bytes to properly support Binary fields.
// getDefaultValue changed to return const DString & instead of DString
// 
//    Rev 1.21   Jan 22 2001 12:02:44   dt24433
// Added getFixedByteLength.  getFixedLength will not work with binary data.
// 
//    Rev 1.20   Nov 22 2000 07:01:28   dt17817
// Reduce runtime memory requirements of Data objects
// 
//    Rev 1.19   May 31 2000 09:31:38   dtwk
// Change locale string to ClientLocale object
// 
//    Rev 1.18   Jan 16 2000 14:08:22   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.17   Dec 19 1999 09:28:36   dtwk
// Convert comments to JavaDoc format
// 
//    Rev 1.16   Dec 09 1999 09:13:44   dtwk
// Change boolean to bool in DataProperties::setUsingRepository
// 
//    Rev 1.15   Nov 29 1999 07:29:32   dtwk
// Add support for redefines
// 
//    Rev 1.14   Oct 06 1999 13:51:28   DCYK
// Add support for redefines.
// 
// 
//    Rev 1.13   Oct 04 1999 15:25:54   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
// 
// 
//    Rev 1.12   Sep 02 1999 13:13:10   DCYK
// Add addLocale function, to add a locale on
// an existing properties object.
// 
// 
//    Rev 1.11   Aug 20 1999 15:36:40   DCYK
// Added locale parameter to isValid, added isI18NValid function.
// 
// 
//    Rev 1.10   May 18 1999 09:41:22   DCYK
// Fix problems with index numbers.
// 
// 
//    Rev 1.9   May 14 1999 11:32:10   DTWK
// Add ability to access Data using Group/Field Id's
// 
//    Rev 1.8   May 11 1999 10:43:34   DTWK
// Fix build
// 
//    Rev 1.7   May 05 1999 13:11:50   DCYK
// Change getVectorIndex calls to
// getVectorIndexFromName to allow
// re-use of element properties.
// 
// 
//    Rev 1.6   Apr 20 1999 16:48:58   DCYK
// Changes for Repository and I18N.
// 
// 
//    Rev 1.5   Mar 05 1999 10:21:52   DCYK
// Changes for I18N.
// 
// 
//    Rev 1.4   Feb 11 1999 15:03:00   DCYK
// Add support for binary elements.
// 
// 
//    Rev 1.3   Jan 28 1999 14:06:02   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.2   Dec 09 1998 13:40:38   DMUM
// Check in for DICORE
// 
//    Rev 1.1   Sep 14 1998 11:32:06   dcyk
// Updated header file documentation.
// 
// 
//    Rev 1.0   29 Jul 1998 20:36:58   DT14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.20   Nov 10 1997 15:00:10   dcyk
//  
// 
//    Rev 1.19   23 Sep 1997 16:28:44   dcyk
// Add support for vector indices, so Data objects
// can store elements in a vector, not a map.
// 
// 
//    Rev 1.18   07 Aug 1997 15:07:42   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
// 
// 
//    Rev 1.17   24 Jul 1997 09:29:02   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
// 
// 
//    Rev 1.16   08 Jul 1997 09:14:42   dcyk
// Added STL casting operators and RTTI.
// 
// 
//    Rev 1.15   13 Jun 1997 16:18:56   dcyk
//  
// 
//    Rev 1.14   Jun 08 1997 18:47:40   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
// 
//    Rev 1.13   05 Jun 1997 18:06:08   dcyk
// Added new parameter to friend function
// declaration of Data::getAllValues.
// 
// 
//    Rev 1.12   May 29 1997 09:53:06   dcyk
// Added support for substitute values
// and masking.
// 
// 
//    Rev 1.11   May 06 1997 10:16:14   dcyk
// Cleaned up documentation & comments.
// 
// 
//    Rev 1.10   May 01 1997 08:40:44   dcyk
// Moved isValid functionality to the
// DataPropertiesImpl class.
// 
// Added documentation.
// 
// 
//    Rev 1.9   Apr 11 1997 08:57:46   dcyk
//  
// 
//    Rev 1.8   Mar 25 1997 15:59:52   dcyk
// Added:  formatValue, getMaxLength,
// getDefaultValue, getFileName,
// getProperty( ulong index ).
// 
// Removed:  default constructor.
// 
// Modify to use DataPropertiesImpl for
// implementation.
// 
// 
//    Rev 1.7   Feb 11 1997 14:36:30   dcyk
// Added support for Rogue Wave's STL.
// 
// 
//    Rev 1.6   Jan 19 1997 12:54:32   DRUS
//  
// 
//    Rev 1.5   Jan 16 1997 08:09:34   dcyk
// Added _fileName as a private data member.
// 
//    Rev 1.4   Jan 10 1997 08:38:24   DRUS
// Added support for repeat records, including a constructor
// which accepts repeat information.
// 
//    Rev 1.3   Dec 31 1996 13:35:22   DRUS
// Added the default constructor and the isValid() method to allow strings
// to be validated against the contained properties.
// 
//    Rev 1.2   Nov 21 1996 14:37:08   DRUS
// Fixed PVCS comment syntax errors (again).
//
//    Rev 1.1   Nov 20 1996 17:07:14   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:18   DRUS
//
//
//

#endif // DataProperties_h
