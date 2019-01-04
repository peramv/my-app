#ifndef DATACOMPONENT_HPP
#define DATACOMPONENT_HPP

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

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class DIDBRKR_LINKAGE DataComponentProperties;
class DIDBRKR_LINKAGE DataElement;

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

/**
 * This abstract base class is the parent class for Data and DataElement.  It
 * stores a value and can be associated with a properties object.
 * 
 * The DataComponent, Data and DataElement classes make up a "composite"
 * pattern.  Data and DataElement are sub-classes of DataComponent, and a
 * DataComponent can contain objects of type DataComponent.  So, any Data or
 * DataElement object could contain Data or DataElement objects, or both.
 * 
 * @author DST Systems Inc
 */
class DIDBRKR_LINKAGE DataComponent
{
public:

   static const long REPEAT_INDEX_NOT_FOUND;

   /**
    * Creates a new DataComponent object identical to the one passed
    * in.
    * 
    * @param copy - DataComponent object to create the new one from.
    *
    */
   DataComponent( const DataComponent &copy );

   virtual ~DataComponent();

   /**
    * Assigns one DataComponent object to another.
    * 
    * @param copy - reference to a DataComponent object, whose
    *        attributes you want assigned to this DataComponent.
    * @return a reference to this DataComponent object.
    *
    */
   DataComponent &operator=( const DataComponent &copy );

   /**
    * Tests if two DataComponent objects are equal.
    * 
    * @param data - reference to the DataComponent object to
    *        compare against this DataComponent object.
    * @return true if the two DataComponent objects are
    *         equal.
    *
    */
   virtual bool operator== ( const DataComponent &data ) const;

   /**
    * Tests if two DataComponent objects are not equal.
    * 
    * @param data - reference to the DataComponent object to
    *        compare against this DataComponent object.
    * @return true if the two DataComponent objects are not equal.
    *
    */
   virtual bool operator!= ( const DataComponent &data ) const;

   /**
    * A DC will always return DataComponent::REPEAT_INDEX_NOT_FOUND.
    * 
    * @return 
    */
   virtual long findRepeatIndex( const DString &value ) const;

   /**
    * Find the maximum possible length of a return value for
    * this DataComponent.
    * 
    * @return the maximum lenth.
    */
   virtual unsigned long getMaxLength() const = 0;

   /**
    * Gets the properties object for this DataComponent.
    * 
    * @return a const pointer to the DataComponent's properties
    *         object.  If this DataComponent has no properties, a NULL
    *         pointer is returned.
    *
    */
   virtual const DataComponentProperties *getProperties()
                                               const{ return _dataProperties; };

   /**
    * If this DataComponent is repeatable, gets the number of
    * repeats in this DataComponent's repeat area.
    * 
    * @return the number of repeats.  If this DataComponent is not repeatable,
    *         zero is returned.
    *
    */
   virtual unsigned long getRepeatCount() const;

   /**
    * Gets the DataComponent's formatted value.
    *
    * @param valueOut - string reference to return value in
    *
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
    * 
    * @return the reference of the string passed in (with return value).
    *         This value is formatted according to the properties for this
    *         DataComponent.  If this object has no associated properties,
    *         no formatting is performed.
    *
    */
   virtual DString &getValue( DString &valueOut, unsigned long formatFlags = 0L,
                              const ClientLocale *pClientLocale = 0,
                              const DString &i18nFormat = NULL_STRING ) const = 0;

   /**
    * Gets the DataComponent's formatted value.
    *
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
    * 
    * @return a string containing the DataComponent's value.
    *         This value is formatted according to the properties for this
    *         DataComponent.  If this object has no associated properties,
    *         no formatting is performed.
    *
    */
   virtual DString getValue( unsigned long formatFlags = 0L,
                             const ClientLocale *pClientLocale = 0,
                             const DString &i18nFormat = NULL_STRING ) const = 0;

   /**
    * Virtual function that checks if this object's value or values
    * are all equal to their defaults.
    * 
    * @param pClientLocale - the locale/market/client to use to check for the
    *                   default data.
    * @return Returns a boolean, true if this object's value or values are
    *         all equal to their defaults.
    */
   virtual bool isDefault( const ClientLocale *pClientLocale = 0 ) const = 0;

   /**
    * Checks if the DataComponent is a DataElement.
    * 
    * @return true if the DataComponent is a DataElement,
    *         false otherwise.
    *
    */
   virtual bool isElement() const{ return false; };

   /**
    * Virtual function that sets this object's value or values to
    * their default values.
    * 
    * @param pClientLocale - the locale/market/client combination for the 
    *                   properties
    */
   virtual void resetValue( const ClientLocale *pClientLocale = 0 ) = 0;

   /**
    * Sets the DataComponent's value to the input parameter.
    * 
    * @param value - (in) contains the new value
    * @param checkValidity -
    *                   (in) if true, the incoming value is checked to see
    *                   if it is valid for this DataComponent
    * @param pClientLocale - the locale/market/client combination for the 
    *                   properties
    * @param displayFormat -
    *                   for i18n components, specifies whether the incoming value is
    *                   in a display format or host format.
    * @param i18nFormat - for i18n components, specifies the format of the incoming
    *                   value
    * @return true if the value was successfully set,
    *         false otherwise.  Will also return a false if checkValidity is
    *         true, and the incoming value is not valid for this
    *         DataComponent.
    */
   virtual bool setValue( const DString &value, bool checkValidity = true,
                          const ClientLocale *pClientLocale = 0,
                          bool displayFormat = true,
                          const DString &i18nFormat = NULL_STRING ) = 0;

   /**
    * Get the id for this object.
    * 
    * @param _lid   - this will be set with the data dictionary id for this object.
    *               
    * @return the id.
    */
   virtual unsigned long getId() const;

protected:
   unsigned long _id;

   DataComponentProperties *_dataProperties;

   DataComponent     *_pBase;

   /**
    * Create a DataComponent instance.
    * 
    * @param value  - the initial value for the DC
    * @param properties - the properties for the DC
    * @param checkValidity
    *                   - true if the properties should be used to validate the
    *                   passed-in value
    * @param _pBase - a pointer to a base DC object
    * @param clientLocale - the default locale/market/client combination for the
    *                   properties
    */
   DataComponent( const DString &value = NULL_STRING,
                  DataComponentProperties *properties = 0,
                  bool checkValidity = true,
                  DataComponent *_pBase = 0,
                  const ClientLocale &clientLocale =
                     ClientLocale::getDefaultClientLocale() );

   /**
    * Create a DataComponent instance.
    * 
    * @param _pBase - a pointer to a base DC object
    * @param value  - the initial value for the DC
    * @param properties - the properties for the DC
    * @param checkValidity
    *                   - true if the properties should be used to validate the
    *                   passed-in value
    * @param clientLocale - the default locale/market/client combination for the 
    *                   properties
    */
   DataComponent( DataComponent *_pBase,
                  const DString &value = NULL_STRING,
                  DataComponentProperties *properties = 0,
                  bool checkValidity = true,
                  const ClientLocale &clientLocale =
                     ClientLocale::getDefaultClientLocale() );

   /**
    * Returns a pointer to the "base" DataComponent
    * 
    * @return DataComponent *
    *
    */
   DataComponent * _getBase();

   /**
    * Returns a const pointer to the "base" DataComponent
    * 
    * @return const DataComponent *
    *
    */
   const DataComponent * _getBaseConst() const;

   /**
    * Sets the DataComponent's value to the input parameter.
    * 
    * @param value - (in) contains the new value
    * @param checkValidity - (in) if true, the incoming value is checked to see
    *        if it is valid for this DataComponent
    * @param pClientLocale - the locale/market/client combination for the 
    *        properties
    * @param displayFormat -
    *                   for i18n components, specifies whether the incoming value is
    *                   in a display format or host format.
    * @param i18nFormat - for i18n components, specifies the format of the incoming
    * @return true if the value was successfully set,
    *         false otherwise.  Will also return a false if checkValidity is
    *         true, and the incoming value is not valid for this
    *         DataComponent.
    *
    */
   virtual bool _setValue( const DString &value, bool checkValidity,
                           const ClientLocale *pClientLocale = 0,
                           bool displayFormat = true,
                           const DString &i18nFormat = NULL_STRING );

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
// $Log:   Y:/VCS/iFastAWD/inc/datacomponent.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:50   kovacsro
//Initial revision.
// 
//    Rev 1.17   Mar 02 2001 14:18:00   dt24433
// Changed getId to no longer take unsigned long reference parameter.
// 
//    Rev 1.16   Jan 10 2001 11:05:10   dt24433
//  
// 
//    Rev 1.15   Nov 22 2000 07:01:12   dt17817
// Reduce runtime memory requirements of Data objects
// 
//    Rev 1.14   Sep 05 2000 06:05:42   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
// 
// 
//    Rev 1.13   May 31 2000 09:31:22   dtwk
// Change locale string to ClientLocale object
// 
//    Rev 1.12   Jan 16 2000 14:08:06   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.11   Dec 19 1999 09:28:22   dtwk
// Convert comments to JavaDoc format
// 
//    Rev 1.10   Jun 29 1999 09:46:18   DCYK
// Added setLocale methods.
// 
// 
//    Rev 1.9   Jun 18 1999 09:36:10   DCYK
// Add ID's for dynamically created elements.
// 
// 
//    Rev 1.8   Jun 06 1999 13:25:20   DTWK
//  
// 
//    Rev 1.7   May 24 1999 10:30:54   DTWK
// Add internationalized formatting for new date and number types using JNI
//
//    Rev 1.6   Apr 20 1999 16:48:52   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.5   Mar 05 1999 10:20:56   DCYK
// Changes for I18N.
//
//
//    Rev 1.4   Feb 11 1999 15:01:38   DCYK
// Add support for binary elements.
//
//
//    Rev 1.3   Jan 28 1999 14:05:54   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:26   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 14 1998 11:33:08   dcyk
// Updated header file documentation.
//
//
//    Rev 1.0   29 Jul 1998 20:36:48   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.21   Jul 22 1998 10:13:08   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.20   Jul 08 1998 10:04:28   dcyk
// Performance improvements.
//
//
//    Rev 1.19   Nov 10 1997 15:00:02   dcyk
//
//
//    Rev 1.18   08 Sep 1997 14:22:46   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.17   07 Aug 1997 15:06:50   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.16   24 Jul 1997 09:26:42   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.15   08 Jul 1997 09:11:36   dcyk
// Added STL casting operators and RTTI.
// _repeatValues is not used, but left in.
// Added const REPEAT_INDEX_NOT_FOUND
//
//
//    Rev 1.14   13 Jun 1997 16:18:46   dcyk
//
//
//    Rev 1.13   Jun 08 1997 18:47:36   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.12   05 Jun 1997 17:58:50   dcyk
// Added default parameter to getValue.
// Made findRepeatIndex return a -1,
// an error.  This function should not be called.
//
//
//    Rev 1.11   May 06 1997 10:15:08   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.10   May 01 1997 08:37:38   dcyk
// Added documentation.
//
//    Rev 1.9   Apr 11 1997 08:57:36   dcyk
//
//
//    Rev 1.8   Apr 04 1997 09:51:52   dcyk
//
//
//    Rev 1.7   Mar 25 1997 15:47:28   dcyk
// Removed:  isPropertyChanged,
// isPropertyDefined.
//
// Made isDefault and resetValue pure virtual.
//
//
//    Rev 1.6   Feb 11 1997 14:31:30   dcyk
// Added support for Rogue Wave's STL.
//
//
//    Rev 1.5   Jan 19 1997 12:54:24   DRUS
//
//
//    Rev 1.4   Jan 10 1997 08:47:16   DRUS
// Implemented getRepeatCount and removed unneeded
// methods which are available through other classes to
// get, set, and reset values and to determine if repeatable.
//
//    Rev 1.3   Dec 31 1996 13:29:58   DRUS
// Made class exportable.  Added isElement method to
// identify the derived class.
//
//    Rev 1.2   Nov 21 1996 14:37:04   DRUS
// Fixed PVCS comment syntax errors (again).
//
//    Rev 1.1   Nov 20 1996 17:07:12   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:10   DRUS
//
//
//

#endif // DataComponent_hpp
