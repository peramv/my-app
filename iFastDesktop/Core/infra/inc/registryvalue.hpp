#ifndef REGISTRYVALUE_HPP
#define REGISTRYVALUE_HPP

#  pragma message( "including "__FILE__ )

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
   #include "dstringa.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class represents a value in the system registry.
 */
class DICORE_LINKAGE RegistryValue
{
   // Public typedefs & enums
   public:
      enum RegistryValueType { 
         NONE, 
         STRING, 
         DWORD };

   // Constructors & Destructor
   public:

      /**
       * Constructor
       */
      RegistryValue();
      
      /**
       * Constructor
       */
      RegistryValue( const RegistryValue & copy );
      
      /**
       * Constructor
       */
      RegistryValue( const DStringA & name );
      
      /**
       * Constructor
       */
      RegistryValue( const DStringA & name, 
                     const DStringA & value );
      
      /**
       * Constructor
       */
      RegistryValue( const DStringA &name, 
                     const unsigned long & value );
      
      /**
       * Destructor
       */
      virtual ~RegistryValue();

   // Methods
   public:
      /**
       * Getter for the name
       * 
       * @return 
       */
      const DStringA & getName() const;
      
      /**
       * Getter for the type
       * 
       * @return 
       */
      RegistryValueType getType() const;

      /**
       * Setter for the name
       * 
       * @param name
       * @return 
       */
      RegistryValue & setName( const DStringA &name );

      /**
       * Getter for _ulValue
       * 
       * @return 
       */
      unsigned long getAsDWORD() const;
      
      /**
       * Getter for _strValue
       * 
       * @return 
       */
      DStringA getAsString() const;

      /**
       * Setter for the value
       * 
       * @param value
       */
      void set( const DStringA & value );

      /**
       * Setter for the value
       * 
       * @param value
       */
      void set( const unsigned long & value );

      /**
       * 
       * @return true, if the name is empty and the type == NONE
       */
      bool isNull()
      { 
         return( _name.empty() && ( _type == NONE ) ); 
      }

      /**
       * Assignment operator
       * 
       * @param copy
       * @return 
       */
      RegistryValue & operator=( const RegistryValue & copy );

   // Attributes
   private:

      RegistryValueType  _type;
      unsigned long      _ulValue;
      DStringA           _strValue;
      DStringA           _name;
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
// $Log:   Y:/VCS/iFastAWD/inc/registryvalue.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:32   kovacsro
//Initial revision.
// 
//    Rev 1.8   30 Oct 2000 16:54:08   dt14177
// cleanup
// 
//    Rev 1.7   Nov 19 1999 14:49:22   DMUM
// made the get...() methods const
//
//    Rev 1.6   Feb 22 1999 13:20:16   DMUM
//
//
//    Rev 1.4   Feb 22 1999 07:34:38   DMUM
// Re-added Linkage macros
//
//    Rev 1.3   Feb 22 1999 07:29:20   DMUM
// Making registry classes public again in 1700
//
//    Rev 1.2   18 Feb 1999 10:38:50   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:38   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:53:04   DMUM
//
//
//    Rev 1.3   10 Nov 1997 15:01:34   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.2   20 Jun 1997 07:44:36   dmum
// Documentation
//
//    Rev 1.1   09 Jun 1997 13:08:12   dmum
// Documented methods
//
//    Rev 1.0   May 22 1997 15:35:36   dmum
//
//
//

#endif // REGISTRYVALUE_HPP
