#ifndef DATAPROPERTIESIMPL_HPP
#define DATAPROPERTIESIMPL_HPP

#  pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DIDBRKR */

#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
   #include <iostream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
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

#ifndef TREPOSITORY_HPP
   #include "trepository.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

/**@#-*/
//forward declarations
class DIDBRKR_LINKAGE DataComponentProperties;
class DIDBRKR_LINKAGE PropertyRepository;
/**@#+*/

/**
 * The DataPropertiesImpl class is the implementation part of the
 * DataProperties class.  This class contains most of the member
 * variables and functionality that the DataProperties class
 * provides an interface for.
 *
 * Objects of this class define the properties for their
 * associated Data objects.  Currently, DataPropertiesImpl objects
 * can only be "filled" with DataElementProperties objects by
 * streaming in the information from a view definition file.
 *
 * When the repository is being used, there should be only one
 * instance of the DataPropertiesImpl class for each "id", which
 * for now is either the name of a view definition file, or a name
 * built from a view definition file name and the text
 * "Repeat_Record".
*/

class DIDBRKR_LINKAGE DataPropertiesImpl
{

public:

   typedef std::vector< DataComponentProperties * > DCPPtrVectorType;

   /**
    * Default constructor
    */
   DataPropertiesImpl();

   /**
    * Constructor
    *
    * @param id
    * @param isRepeatable
    */
   DataPropertiesImpl(
      const DString &id,
      bool isRepeatable = false );

   /**
    * Constructor
    *
    * @param propsId
    * @param isRepeatable
    * @param propsVector
    */
   DataPropertiesImpl( const DString &propsId,
                       bool isRepeatable,
                       const DCPPtrVectorType &propsVector );

   /**
    * Copy constructor
    *
    * @param copy
    */
   DataPropertiesImpl( const DataPropertiesImpl &copy );

   /**
    * Destructor
    */
   virtual ~DataPropertiesImpl();

   /**
    * Gets a pointer to an instance of a DataPropertiesImpl object
    * created with the specified id.
    *
    * @param id
    * @param isRepeatable
    * @returns DataPropertiesImpl object
    */
   static DataPropertiesImpl *DataPropertiesImpl::getInstancePointer(
      unsigned long id,
      const ClientLocale &clientLocale,
      bool isRepeatable );
   /**
    * Gets a pointer to an instance of a
    * DataPropertiesImpl object
    * created with the specified name.
    *
    * @param name
    * @param isRepeatable
    * @return
    */
   static DataPropertiesImpl * getInstancePointer(
      const DString &name,
      const ClientLocale &clientLocale,
      bool isRepeatable = false );

   /**
    * Assigns vector indexes to all the repeats
    *
    * @param dataCompProps
    */
   void assignVectorIndexes(
                       DataComponentProperties & dataCompProps );

   /**
    * Dumps the property pointers and indices
    * for the components to std::out; no recursion,
    * so it only does it for elements
    */
   void dumpPIMap() const;

   /**
    * Is there a property in the object with
    * the name of the parameter?
    *
    * @param propertyName
    * @return
    */
   bool   exists( const DString & propertyName ) const;

   /**
    * Is there a property in the object with
    * the id of the parameter?
    *
    * @param id
    * @return
    */
   bool   exists( long id ) const;

   /**
    * Returns the Id for specified name
    *
    * @param name
    * @return id or 0xFFFFFFFF for not found
    */
   unsigned long getFieldIdFromName( const DString &name ) const;

/**
    * Returns the filename of the persistent
    * location of the object
    *
    * @return
    */
   DString getFileName() const
      { return _fileName.c_str(); };

   /**
    * Returns the length of the non-repeatable area in bytes.
    *
    * @return
    */
   unsigned long getFixedByteLength() const;

   /**
    * Returns the Id
    *
    * @return
    */
   virtual unsigned long getId() const
      { return _ulongId; };

   /**
    * Returns the length of the longest field in
    * the object
    *
    * @return
    */
   virtual unsigned long getMaxLength();

   /**
    * Returns the name of the object.
    *
    * @return
    */
   const DString &getName() const
   { return _id; };

   /**
    * Returns the property associated with the name
    *
    * @param propertyNameKey
    *
    * @return
    */
   const DataComponentProperties & getProperty(
                         const DString & propertyNameKey ) const;

   /**
    * Returns the property associated with the index
    *
    * @param index
    *
    * @return
    */
   const DataComponentProperties & getProperty(
                                     unsigned long index ) const;

   /**
    * Searches the property map and returns
    * the property associated with the id
    *
    * @param id
    *
    * @return
    */
   const DataComponentProperties & getPropertyByFieldIndex(
                                                 long id ) const;

   /**
    * Returns the number of properties
    *
    * @return
    */
   unsigned long getPropertyCount() const
      { return _propertyCount; };

   /**
    * Returns the total length of the object
    *
    * @return
    */
   virtual unsigned long getTotalMaxLength();

   /**
    * Returns the total number of lines
    *
    * @return
    */
   long getTotalNumberOfLines() const;

   /**
    * Returns the total number of properties
    *
    * @return
    */
   long getTotalNumberOfProperties() const;

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
    * @return true if successful, false if field not found.  All other errors 
    *         should throw.
    * @exception ConditionException&
    *                   ConditionException& out of memory
    *                   ConditionException& invalid format string passed in
    */
   DataProperties::EReturn getValueFromBuffer(
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
   DataProperties::EReturn getValueFromBuffer(
      long id,
      unsigned char *binBuff,
      const unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;
   /**
    * Searches the property map for the name
    *
    * @param name
    * @return index or -1 for not found
    */
   long getVectorIndexFromName( const DString &name ) const;

   /**
    * Tells whether the property is repeatable
    */
   bool isRepeatable(){ return _isRepeatable; };

   /**
    * Determines if the value is valid within
    * the ClientLocale
    *
    * @param valueString
    * @param pClientLocale
    * @return
    */
   virtual bool isValid( const DString & valueString,
                         const ClientLocale * pClientLocale = 0 )
                                                           const;
   /**
    * Sets the value of an element in a raw host buffer area.
    * 
    * @param id     - (in) the data dictionary id of the field to get.
    * @param strIn  - value to set.
    * @param rpDataBuffer - data buffer area to get field from.
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
   DataProperties::EReturn setValueInBuffer(
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
   DataProperties::EReturn setValueInBuffer(
      long id,
      unsigned char *binBuff,
      unsigned char *rpDataBuffer,
      unsigned long buffLength,
      unsigned long &returnedLength
      ) const;

   /**
    * Sets the value of an element in a raw host buffer area.  This should only 
    *  be used for values directly from host.
    * 
    * @param id     - (in) the data dictionary id of the field to get.
    * @param strIn  - (in/out) value to set.  Will contain actual value stored
    *  upon return.
    * @param rpDataBuffer - data buffer area to get field from.
    * @return SUCCESS if found, NOT_FOUND if field not in data dictionary or
    *    FAILURE if the assignment was unsuccessful.
    */
   DataProperties::EReturn setValueInBufferFromHost(
      long id,
      DString &valueIn,
      unsigned char *rpDataBuffer
      ) const;

   /**
    * Streams out all the subcomponents as text,
    * including all properties
    *
    * @param stream   - where the output goes
    * @param counter  - not used
    * @param lineNum  - starting property
    * @param viewName - name of the view
    * @param propName - property name
    */
   void streamOutComponents( i_ostream & stream,
                             unsigned long & counter,
                             unsigned long & lineNum,
                             const DString & viewName,
                             const DString & propName );

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

   /**
    * Sets the Id
    *
    * @param lId
    */
   virtual void setId( unsigned long lId ){ _ulongId = lId; };

   /**
    * Searches the vector for the component property
    *
    * @param propVector - property vector to search
    * @param propPtr    - the key
    * @return - an iterator which points at the property
    */
   DCPPtrVectorType::iterator findPropertyInVector(
                                   DCPPtrVectorType & propVector,
                       DataComponentProperties * propPtr ) const;

   /**
    * Copies component properties from the
    * redefine map beginning with the oldName
    * property until the end
    *
    * @param oldName - the key for where the copy begins
    * @param vecRedefines
    *                - (out) the vector containing the
    *                redefines
    */
   void getRedefines( const DString & oldName,
                      string_vector & vecRedefines );

   /**
    * Searches the index map for the Id
    *
    * @param ulId
    * @return - the offset
    */
//   long getOffset( unsigned long ulId ) const;

   friend i_istream & operator>> ( i_istream & stream,
                           DataPropertiesImpl & propertiesImpl );

   friend EXPORTWIN i_ostream & EXPORTOS2 operator<< (
                                              i_ostream & stream,
                     const DataPropertiesImpl & propertiesImpl );

   friend const DString &DataProperties::getPropertyElementName(
                                     unsigned long index ) const;

private:
   typedef struct PropertyInfo
   {
      DataComponentProperties *pProperties;
      long lIndex;
      long lOffset;

      PropertyInfo() :
         pProperties( NULL ),
         lIndex( -1L ),
         lOffset( 0 )
      {
      }

      PropertyInfo( DataComponentProperties * properties,
                    long index ) :
         pProperties( properties ),
         lIndex( index ),
         lOffset( 0 )
      {
      }

      PropertyInfo( const PropertyInfo& propertyInfo ) :
         pProperties( propertyInfo.pProperties ),
         lIndex( propertyInfo.lIndex ),
         lOffset( propertyInfo.lOffset )
      {
      }

      ~PropertyInfo()
      {
         if ( ! pProperties->cameFromRepository() )
         {
            delete pProperties;
         }
         pProperties = NULL;
      }
   } PROPERTY_INFO;

   typedef std::map< DString, PROPERTY_INFO *, CaseInsensitiveCompare > DCPPtrMapType;
   typedef std::map< long, PROPERTY_INFO *, std::less< long > > DCPPtrMapIndexType;

   DString _fileName;
   DString _id;
   unsigned long _ulongId;
   mutable unsigned long _ulCalcFixedLength;
   mutable unsigned long _ulCalcFixedByteLength;
   bool _isRepeatable;
   unsigned long _maxLength;
   unsigned long _propertyCount;
   DCPPtrMapType    _propertyMap;
   DCPPtrVectorType _propertyOrder;
   DCPPtrMapIndexType _propertyIndex;
   typedef std::map< DString, string_vector, std::less< DString > >
                                                                RedefineMapType;
   RedefineMapType m_redefineMap;

   void _calculateOffsets();
   const DString &getPropertyElementName( unsigned long index ) const;
   const PropertyInfo *_getPropertyInfoForDEP( long id ) const;
   static void getPath( DString& pathString );
   void _recalculateVectorIndexes();
   bool _redefineProperties( const DString &dstrField,
                             DataPropertiesImpl *pDPIAdd );
   bool _redefineProperties( const DString &dstrField );
   void _replaceVectorSubSequence( string_vector &vecMain,
                                   string_vector &vecRemove,
                                   string_vector &vecAdd );
   void _updateRedefineMap( const DString &dstrField,
                            DataPropertiesImpl *pDPIAdd );

   friend DCPPtrVectorType DataProperties::getImplVector() const;
   friend class PropertyRepository;
   friend void Data::_setRedefine( const DString &oldName,
                                   const DString &newName );
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/datapropertiesimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:21:26   kovacsro
//Initial revision.
// 
//    Rev 1.27   May 18 2001 15:06:42   dt24433
// Updated signatures for binary support and added
// setValueInBufferFromHost.
// 
//    Rev 1.26   Mar 22 2001 16:32:42   dt24433
//  
// 
//    Rev 1.25   Mar 09 2001 11:24:44   dt24433
//  
// 
//    Rev 1.24   Mar 02 2001 14:08:40   dt24433
//  
// 
//    Rev 1.23   Jan 22 2001 12:01:50   dt24433
//  
// 
//    Rev 1.22   Jan 19 2001 17:11:54   DT11159
// oops
//
//    Rev 1.21   Jan 19 2001 16:53:00   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.20   Jan 04 2001 16:46:56   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.19   13 Dec 2000 17:11:08   dt14177
// Cleanup and documentation
//
//    Rev 1.18   Nov 22 2000 07:05:10   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.17   Jun 08 2000 11:49:52   dtwk
// Add support for case-insensitivity
//
//    Rev 1.16   May 31 2000 09:33:10   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.15   Apr 10 2000 11:47:28   dtwk
// Updates for thread-safety
//
//    Rev 1.14   Nov 29 1999 07:31:48   dtwk
// Add support for redefines
//
//    Rev 1.13   Oct 06 1999 11:35:42   DCYK
// Add support for redefines.
//
//
//    Rev 1.12   Oct 04 1999 15:25:20   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.11   Sep 02 1999 13:12:48   DCYK
// Add addLocale function, to add a locale on
// an existing properties object.
//
//
//    Rev 1.10   Aug 20 1999 15:37:16   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.9   May 28 1999 14:53:40   DCYK
// Fix so Data objects return numerical id.
//
//
//    Rev 1.8   May 14 1999 11:29:46   DTWK
// Add ability to access Data through Repository Group/Field Id's
//
//    Rev 1.7   May 06 1999 16:44:06   DCYK
//
//
//    Rev 1.6   May 05 1999 13:11:36   DCYK
// Change getVectorIndex calls to
// getVectorIndexFromName to allow
// re-use of element properties.
//
//
//    Rev 1.5   Apr 20 1999 16:49:38   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.4   Mar 05 1999 10:25:44   DCYK
// Changes for I18N.
//
//
//    Rev 1.3   Feb 11 1999 15:03:22   DCYK
// Add support for binary elements.
//
//
//    Rev 1.2   Jan 28 1999 14:03:58   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Sep 14 1998 11:31:50   dcyk
// Updated header file documentation.
//
//
//    Rev 1.0   29 Jul 1998 20:31:04   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.6   Jul 08 1998 10:04:58   dcyk
// Performance improvements.
//
//
//    Rev 1.5   Nov 10 1997 14:47:06   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.4   23 Sep 1997 16:29:42   dcyk
// Add support for vector indices, so Data objects
// can store elements in a vector, not a map.
//
//
//    Rev 1.3   07 Aug 1997 15:05:54   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.2   24 Jul 1997 09:29:56   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//

#endif // DATAPROPERTIESIMPL_HPP
