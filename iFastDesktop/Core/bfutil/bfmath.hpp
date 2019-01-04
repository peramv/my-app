#pragma once

#include <srcprag.h>
#include <commonport.h>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bfutil
{
   /**
    * Round a value away from 0.  This causes positive numbers to (potentially) increase
    * in value and negative numbers to (potentially) decrease in value.
    * 
    * @param v      The value to round
    * @param cRequiredPrecision
    *               The number of decimal places to round to
    * @param cMaxPrecision
    *               The maximum precision of the value v
    * 
    * @return The rounded value
    */
   BFUTIL_LINKAGE double roundUp( double v, int cRequiredPrecision, int cMaxPrecision );

   /**
    * Round a value toward 0.  This causes positive numbers to (potentially) decrease
    * in value and negative numbers to (potentially) increase in value.
    * 
    * @param v      The value to round
    * @param cRequiredPrecision
    *               The number of decimal places to round to
    * @param cMaxPrecision
    *               The maximum precision of the value v
    * 
    * @return The rounded value
    */
   BFUTIL_LINKAGE double roundDown( double v, int cRequiredPrecision, int cMaxPrecision );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfmath.hpp-arc  $
//
//   Rev 1.0   Nov 27 2002 11:38:10   PURDYECH
//Initial revision.
//
