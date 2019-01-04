#pragma once

/** 
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

/**@pkg DICORE */    

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef SYMBOLS_H
   #include <symbols.h>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class represents a configuration value.
 *
 * This value may either be a DString or an integer.  Internally, the value is
 * stored as a DString.
 */
class DICORE_LINKAGE ConfigValue
{
   // Constructors & destructor
public:
   /**
    * Copy Constructor.
    *
    * @param copy - The ConfigValue object to copy.
    */
   ConfigValue( const ConfigValue &copy );

   /**
    * Constructor with initialization by DString.
    *
    * @param ConfigValue - The DString object to use for initialization.
    */
   ConfigValue( const DString &ConfigValue = NULL_STRING );

   /**
    * Constructor with initialization by int.
    *
    * @param ConfigValue - The int to use for initialization.
    */
   ConfigValue( const int ConfigValue );

   /**
    * Destructor.
    */
   virtual ~ConfigValue();

   // Public methods
public:
   /**
    * Used to access the configuraiton value as a DString.
    *
    * @return The value as a DString.
    */
   DString asString() const;

   /**
    * Used to access the configuraiton value as an int.
    *
    * @return The value as an int.
    */
   int asInt() const;

   /**
    * Used to access the configuraiton value as a long.
    *
    * @return The value as a long.
    */
   long asLong() const;

   /**
    * Used to access the configuraiton value as a double.
    *
    * @return The value as a double.
    */
   double asDouble() const;

   /**
    * Comparison operator.  Used to determine if the two ConfigValue
    * objects are equal
    *
    * @param compare - The ConfigValue object to compare with.
    *
    * @return True if the values are equal.
    */
   bool operator ==( const ConfigValue &compare ) const;

   /**
    * Comparison operator.  Used to determine if the two ConfigValue
    * objects are not equal
    *
    * @param compare - The ConfigValue object to compare with.
    *
    * @return True if the values are not equal.
    */
   bool operator !=( const ConfigValue &compare ) const;

   /**
    * Used to determine if the value is null (has no value).
    *
    * @return True if the value is null.
    */
   bool isNull() const;

   /**
    * Used to set or change the value.
    *
    * @param value  The new value.
    */
   void set( const DString &value );

   /**
    * Used to set or change the value.
    *
    * @param value  The new value.
    */
   void set( const int value );

   /**
    * Assignment operator.
    *
    * @param copy   - The ConfigValue object to copy.
    *
    * @return Reference to self.
    */
   ConfigValue &operator =( const ConfigValue &copy );

   // Private members
private:
   DString _value;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/configvalue.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:52   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:44   SMITHDAV
//Initial revision.
// 
//    Rev 1.6   23 Oct 2000 14:29:30   dt14177
// cleanup
// 
//    Rev 1.5   Apr 24 2000 10:38:38   DMUM
//  
//
//    Rev 1.4   22 Feb 1999 11:46:52   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.3   18 Feb 1999 10:38:56   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:05:48   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:18   DMUM
// Check in for DICORE
//
//    Rev 1.3   Nov 10 1997 12:59:26   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.2   10 Jul 1997 13:06:00   dmum
// Default constructor not needed
//
//    Rev 1.1   24 Jun 1997 13:46:36   dmum
//
//
//    Rev 1.0   02 Jun 1997 12:26:18   dmum
//
//
//

