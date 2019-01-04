#ifndef DATACOMPONENTPROPERTIES_HPP
#define DATACOMPONENTPROPERTIES_HPP

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

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif


DIDBRKR_LINKAGE SEVERITY readLine( i_istream & fCnd,
                                   DString & linebuf,
                                   unsigned long numToRead = -1,
                                   bool fBigEndian = FALSE );

/**
 * This class is part of a "Composite" pattern.
 *
 * @author DST Systems Inc
 */
class DIDBRKR_LINKAGE DataComponentProperties
{
public:
   // enum for property types
   //  eDCP = DataComponentProperties (invalid)
   //  eDP = DataProperites
   //  eDEP = DataElementProperties
   enum EPROPERTY_TYPE
   { eDCP, eDP, eDEP };

   virtual ~DataComponentProperties();

   /**
    * Tests if two DataComponentProperties objects are equal.
    *
    * @param properties - (in) reference to the
    *        DataComponentProperties object to compare against this
    *        DataComponentProperties object.
    * @return true if the two DataComponentProperties objects are equal.
    *
    */
   virtual bool operator== ( const DataComponentProperties &properties ) const;

   /**
    * Tests if two DataComponentProperties objects are not equal.
    *
    * @param properties - (in) reference to the
    *        DataComponentProperties object to compare against this
    *        DataComponentProperties object.
    * @return true if the two DataComponentProperties objects are not equal.
    *
    */
   virtual bool operator!=
                         ( const DataComponentProperties &properties ) const;

   /**
    * Pure virtual function for returning the default value of
    * DataComponent objects associated with this
    * DataComponentProperties object.
    *
    * @param pClientLocale - the locale/market/client combination for the
    *                   properties
    * @return the default value for DataComponent objects associated with this
    *         DataComponentProperties object.
    *
    */
   virtual const DString &getDefaultValue(
      const ClientLocale *pClientLocale = 0
      ) const = 0;

   /**
    * Pure virtual function that will format the value of a
    * string according to the formatting rules for this
    * DataComponentProperties object.
    *
    * @param valueString - (in/out) value to be formatted.  This parameter
    *        is filled with the formatted value on exit.
    * @param checkValidity - (in) boolean specifying if the input value should
    *        be checked to see if it's valid for this
    *        DataComponentProperties object.  Defaults to true.
    * @return true if the value was formatted
    *         successfully, false if it wasn't, and false if checkValidity
    *         is true and the input string was not in a valid format.
    *
    */
   virtual bool formatValue( DString &valueString,
                             bool checkValidity = true ) const = 0;

   /**
    * Returns the name of the DataComponentProperties object.
    *
    * @return the name of the object.
    *
    */
   virtual const DString &getName() const = 0;

   /**
    * Returns the id of the DataComponentProperties object.
    *
    * @return the id of the object.
    *
    */
   virtual unsigned long getId() const = 0;

   EPROPERTY_TYPE getType() const
   {
      return _eType;
   }

   /**
    * Set the id of this object.
    *
    * @param _lid
    */
   virtual void setId( unsigned long lId ) = 0;

   /**
    * Pure virtual function that gets the maximum length of a
    * DataComponent object associated with this
    * DataComponentProperties object, or any objects contained in
    * the DataComponent object.
    *
    * @return the maximum length as described above.
    *
    */
   virtual unsigned long getMaxLength() const = 0;

   /**
    * Pure virtual function that gets the maximum length of all
    * DataComponent object associated with this
    * DataComponentProperties object, or any objects contained in
    * the DataComponent object.  The values of all nested DataComponents are
    * summed for the return.
    *
    * @return the maximum length as described above.
    *
    */
   virtual unsigned long getTotalMaxLength() const = 0;

   /**
    * Determine if repeating is supported in this object.
    *
    * @return true if repeatable, false otherwise.
    */
   bool isRepeatable() const{ return _repeatable; };

   /**
    * Pure virtual function that checks if the value passed in is
    * valid for an object associated with this
    * DataComponentProperties object.
    *
    * @param valueString - (in) value to check for validity
    * @param pClientLocale - the locale/market/client combination for the
    *        properties
    * @return true if the input value is valid, false otherwise.
    *
    */
   virtual bool isValid( const DString &valueString,
                         const ClientLocale *pClientLocale = 0 ) const = 0;

   /**
    * Get the vector index of this object.
    *
    * @return the index
    */
   unsigned long getVectorIndex() const{ return _vectorIndex; };

   /**
    * Set the vector index of this object.
    *
    * @param newVectorIndex
    */
   void setVectorIndex( unsigned long newVectorIndex )
      { _vectorIndex = newVectorIndex; };

   /**
    * Set to identify whether this object came from a repository.
    * This controls the lifetime of this object.  If true, the
    * object should only be deleted by the repository. If false,
    * the object should be deleted when its associated
    * DataComponent is deleted.
    *
    * @param cameFrom - set to true by the PropertyRepository, false otherwise.
    */
   void setCameFromRepository( bool cameFrom )
                                          { _cameFromRepository = cameFrom; }

   /**
    * Determine if this object was created by the PropertyRepository.
    *
    * @return true if the instance's lifetime will be controlled by the
    *         PropertyRepository, false otherwise.
    */
   bool cameFromRepository(){ return _cameFromRepository; }

protected:
   bool _cameFromRepository;
   bool _repeatable;
   unsigned long _vectorIndex;
   EPROPERTY_TYPE _eType;

   // throw on fail to match id...
   /**
    * Constructor for a DataComponentProperties object.  Called only
    * by subclass constructors.
    *
    * @param id - (in) id for this DataComponentProperties object.
    *        Defaults to empty.
    * @param repeatable - (in) specifies if objects associated with this
    *        DataComponentProperties object are repeatable.  Defaults to
    *        false.
    * @param fixedRepeatSize - (in) specifies the size of the fixed
    *        repeat area for objects associated with this
    *        DataComponentProperties object.  Defaults to zero.
    *
    */
   DataComponentProperties( const DString &id = NULL_STRING,
                            bool repeatable = false,
                            EPROPERTY_TYPE eType = eDCP );

   /**
    * Creates a new DataComponentProperties object identical to the
    * one passed in.
    *
    * @param copy - (in) DataComponentProperties object to create the new one from.
    *
    */
   DataComponentProperties( const DataComponentProperties &copy );

   /**
    * Assigns one DataComponentProperties object to another.
    *
    * @param copy - (in) reference to a
    *        DataComponentProperties object, whose values and attributes
    *        you want assigned to this DataComponentProperties object.
    * @return Returns a reference to this DataComponentProperties object.
    *
    */
   DataComponentProperties &operator= ( const DataComponentProperties &copy );

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
// $Log:   Y:/VCS/iFastAWD/inc/datacomponentproperties.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:52   kovacsro
//Initial revision.
// 
//    Rev 1.19   Mar 02 2001 14:15:14   dt24433
// Added support for getType (used instead of dynamic casting & RTTI).
// Split getId into getId and getName as appropriate.
// 
//    Rev 1.18   Jan 19 2001 17:06:50   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.17   Nov 22 2000 07:01:16   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.16   Sep 27 2000 13:30:58   dt17817
// Remove ClientLocale from DataCompoentProperties
//
//    Rev 1.15   May 31 2000 09:31:26   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.14   Jan 16 2000 14:08:10   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.13   Dec 19 1999 09:28:24   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.12   Nov 29 1999 07:29:28   dtwk
// Add support for redefines
//
//    Rev 1.11   Oct 04 1999 15:25:46   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.10   Oct 04 1999 10:23:42   DCYK
// Threading fixes.
//
//
//    Rev 1.9   Aug 20 1999 15:36:34   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.8   May 26 1999 17:19:52   DCYK
// Add support for getting and setting numerical id's.
//
//
//    Rev 1.7   May 06 1999 16:44:50   DCYK
// Fixes for repository.
//
//
//    Rev 1.6   Apr 20 1999 16:48:52   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.5   Mar 05 1999 10:21:00   DCYK
// Changes for I18N.
//
//
//    Rev 1.4   Feb 11 1999 15:02:06   DCYK
// Add support for binary elements.
//
//
//    Rev 1.3   Jan 28 1999 14:05:56   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:40:30   DMUM
// Check in for DICORE
//
//    Rev 1.19   Nov 10 1997 15:00:04   dcyk
//
//
//    Rev 1.18   23 Sep 1997 16:27:32   dcyk
// Added vectorIndex member, to support
// Data objects storing elements in a vector,
// not a map.
//
//
//    Rev 1.17   08 Sep 1997 14:24:30   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.16   07 Aug 1997 15:07:02   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.15   24 Jul 1997 09:27:28   dcyk
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.14   08 Jul 1997 09:12:24   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.13   13 Jun 1997 16:18:48   dcyk
//
//
//    Rev 1.12   Jun 08 1997 18:47:38   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.11   May 06 1997 10:15:24   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.10   May 01 1997 08:38:18   dcyk
// Added documentation.
//
//
//    Rev 1.9   Apr 11 1997 08:57:40   dcyk
//
//
//    Rev 1.8   Apr 04 1997 09:06:00   dcyk
// Minor performance improvement by
// in-lining getId().
//
//
//    Rev 1.7   Mar 25 1997 15:50:04   dcyk
// Removed setId.
//
// Made getDefaultValue, formatValue,
// getMaxLength pure virtual.
//
//
//    Rev 1.6   Feb 11 1997 14:32:52   dcyk
// Added support for Rogue Wave's STL.
//
//
//    Rev 1.5   Jan 19 1997 12:50:52   DRUS
// Added == and != operators.
//
//    Rev 1.4   Jan 15 1997 17:27:08   dcyk
// Changed the "_id" member variable so it
// is just an ID, and not the file name.
//
//    Rev 1.3   Jan 06 1997 15:59:32   DRUS
// Added virtual method isValid().
//
//    Rev 1.2   Nov 21 1996 14:37:04   DRUS
// Fixed PVCS comment syntax errors (again).
//
//    Rev 1.1   Nov 20 1996 17:07:12   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:12   DRUS
//
//

#endif // DataComponentProperties_h


