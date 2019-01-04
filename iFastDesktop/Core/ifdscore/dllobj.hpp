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

// ^CLASS DESCRIPTION : A wrapper that simplifies loading and finding functions
//                      within DLL's
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ----------------------------------------------------------
// ^METHOD      : DllObj
//
// ^DESCRIPTION : constructor, loads the dll you specify.
//
// ^PARAMETERS  : const string& strModule - the name of the module to load.
//
// ^RETURNS     : none
//
// ^THROWS      : exception (from the internal string instances)
//                ConditionException (DIBASE_DLL_LOAD_FAIL if the load call
//                   fails)
//
// ----------------------------------------------------------
//
// ^METHOD      : ~DllObj
//
// ^DESCRIPTION : Destructor. Unloads the DLL
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
// ^METHOD      : findFunction
//
// ^DESCRIPTION : returns a pointer to a specified function in the dll.
//
// ^PARAMETERS  : const string& strFunc - the name of the module to load.
//
// ^RETURNS     : void * - a pointer to the requested function
//
// ^THROWS      : exception (from the internal string instances)
//                ConditionException(DIBASE_FUNCTION_LOAD_FAIL if the load call
//                   fails)
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//******************************************************************************

#ifndef INCLUDED_UTILITY
#define INCLUDED_UTILITY
#include <utility>
#endif

#ifndef DIPORT2_H
   #include <diport2.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

/**
 * A wrapper class that simplifies loading and finding functions
 * within DLL's
*/

class DICORE_LINKAGE DllObj
{

// functions
public:

   /**
    * Constructor
    */
   DllObj( const DString & strModule ) 
   HEADER_THROW2( ConditionException, exception);

   /**
    * Copy Constructor
    */
   DllObj( const DllObj & orig ) HEADER_THROW1(exception);

   /**
    * Destructor
    */
   virtual ~DllObj() HEADER_THROW1(exception);

   /**
    * Returns a pointer to a specified function in the dll
    */
   virtual void * findFunction( const DString & strFunc ) 
   HEADER_THROW2(ConditionException, exception);

// data
private:
   HINSTANCE               _hmod;
   DString                  _strModule;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/dllobj.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:58   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:52   SMITHDAV
//Initial revision.
// 
//    Rev 1.5   23 Oct 2000 17:33:30   dt14177
// cleanup
// 
//    Rev 1.4   24 Feb 1999 10:44:52   DT14177
// sync up with tracer
// 
//    Rev 1.3   18 Feb 1999 10:39:46   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:24   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:41:56   DMUM
// Check in for DICORE
//
//    Rev 1.6   Nov 09 1997 15:34:36   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.5   Jul 07 1997 15:11:56   DTWK
//
//
//    Rev 1.4   Jun 13 1997 13:25:22   DTWK
// Add support for Condition class
//
//
