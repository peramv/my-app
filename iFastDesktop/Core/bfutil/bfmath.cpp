#include "stdafx.h"
#include "bfmath.hpp"
#include <math.h>
#include <stdio.h>

namespace bfutil
{
   double roundUp( double v, int cRequiredPrecision, int cMaxPrecision )
   {
      assert( cRequiredPrecision <= cMaxPrecision );
      bool bIsNegative = false;
   
      if( v < 0.0 )
      {
         bIsNegative = true;
         v *= -1.0;
      }

//CP20021127      // due to floating point inconsistencies we will increase the precision
//CP20021127      // of the number by 1.  
//CP20021127      cMaxPrecision++;
      double _pow = pow( 10.0, (double)cRequiredPrecision );
      double intPart;
      double fracPart;
      fracPart = modf( v, &intPart );
      fracPart *= _pow;
   
      double fracPartReqd;
      double intPartReqd;
      fracPartReqd = modf( fracPart, &intPartReqd );
   
      double fracPartMax;
      double intPartMax;
   
      fracPartReqd *= pow( 10.0, cMaxPrecision - cRequiredPrecision );
      fracPartMax = modf( fracPartReqd, &intPartMax );
   
      if( intPartMax >= 1.0 ) intPartReqd += 1.0;
   
      v = intPart + ( intPartReqd / _pow );
      if( bIsNegative )
      {
         v *= -1.0;
      }
   
      return( v );
   }

   double roundDown( double v, int cRequiredPrecision, int cMaxPrecision )
   {
      assert( cRequiredPrecision <= cMaxPrecision );
      bool bIsNegative = false;
   
      if( v < 0.0 )
      {
         bIsNegative = true;
         v *= -1.0;
      }
   
      // make the number into a string
      char szNum[ 33 ];
      sprintf( szNum, "%0.*lf", cMaxPrecision, v );
      char* pDecimal = strchr( szNum, '.' );
      if( NULL == pDecimal )
      {
         throw("NaN");
      }
      *(pDecimal + cRequiredPrecision + 1 ) = 0x00;
   
      char* pEnd = NULL;
      v = strtod( szNum, &pEnd );
      if( 0x00 != *pEnd )
      {
         throw("NaN");
      }
      if( bIsNegative )
      {
         v *= -1.0;
      }
   
      return( v );
   }
   
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfmath.cpp-arc  $
// 
//    Rev 1.1   Nov 27 2002 13:08:06   PURDYECH
// Remove some fudging around very precise numbers.
// 
//    Rev 1.0   Nov 27 2002 11:38:12   PURDYECH
// Initial revision.
//
