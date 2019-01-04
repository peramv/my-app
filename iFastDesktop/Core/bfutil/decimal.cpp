#include "stdafx.h"
#include "srcprag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
//CP20030905#include <malloc.h>
#include <new.h>
#include <assert.h>

#include <bfutil\decimal.hpp>


const unsigned uDefaultDataBuffSize = 30;
const unsigned MAX_RESULT_STRING_SIZE = 128;


#define GET_FRACT_SEPARATOR (*(I_CHAR*)(localeconv()->decimal_point))
inline void I_CHARset( I_CHAR * str, I_CHAR val, int numReps )
{
   int i;
   for( i = 0; i < numReps; ++i )
   {
      str[ i ] = val;
   }
}

inline bool myIsDigit( I_CHAR c ) { return( c >= I_( '0' ) && c <= I_( '9' ) ); }

/*****************************  GLOBAL VARIABLES  ****************************/

static short asDigitProducts[10][10] = {
   // Multiplication table for all digit pairs
   //  0,  1,  2,  3,  4,  5,  6,  7,  8,  9
   {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  // 0
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9},  // 1
   {   0,  2,  4,  6,  8, 10, 12, 14, 16, 18},  // 2
   {   0,  3,  6,  9, 12, 15, 18, 21, 24, 27},  // 3
   {   0,  4,  8, 12, 16, 20, 24, 28, 32, 36},  // 4
   {   0,  5, 10, 15, 20, 25, 30, 35, 40, 45},  // 5
   {   0,  6, 12, 18, 24, 30, 36, 42, 48, 54},  // 6
   {   0,  7, 14, 21, 28, 35, 42, 49, 56, 63},  // 7
   {   0,  8, 16, 24, 32, 40, 48, 56, 64, 72},  // 8
   {   0,  9, 18, 27, 36, 45, 54, 63, 72, 81}   // 9
};





/*****************************************************************************/
/********************************  PUBLIC METHODS  ***************************/
/*****************************************************************************/


// Default Constructor
Decimal::Decimal() :
_sRsltLen( uDefaultDataBuffSize ),
_data( _sRsltLen )
{
}


// C String Constructor
Decimal::Decimal( const I_CHAR * pszStringNum )
{
   _init( pszStringNum );
}


Decimal::Decimal( I_CHAR * pszStringNum )
{
   _init( pszStringNum );
}


Decimal::Decimal( const DString * pszStringNum )
{
   _init( pszStringNum->c_str() );
}


Decimal::Decimal( DString * pszStringNum )
{
   _init( pszStringNum->c_str() );
}


Decimal::Decimal( const DString & pszStringNum )
{
   _init( pszStringNum.c_str() );
}


Decimal::Decimal( DString & pszStringNum )
{
   _init( pszStringNum.c_str() );
}


Decimal::Decimal( unsigned char num )
{
   _initUInt( num );
}


Decimal::Decimal( char num )
{
   _initInt( num );
}


Decimal::Decimal( unsigned short num )
{
   _initUInt( num );
}


Decimal::Decimal( short num )
{
   _initInt( num );
}


Decimal::Decimal( unsigned int num )
{
   _initUInt( num );
}


Decimal::Decimal( int num )
{
   _initInt( num );
}


Decimal::Decimal( unsigned long num )
{
   _initUInt( num );
}


Decimal::Decimal( long num )
{
   _initInt( num );
}


Decimal::Decimal( unsigned DIINT64 num )
{
   _initUInt( num );
}


Decimal::Decimal( DIINT64 num )
{
   _initInt( num );
}

#if 0
Decimal::Decimal( float num )
{
   _initDouble( num );
}


Decimal::Decimal( double num )
{
   _initDouble( num );
}
#endif

// Copy Constructor
Decimal::Decimal( const Decimal &copy ) 
: _sRsltLen( copy._sRsltLen )
, _data( copy._data )
, _scratch1( copy._scratch1 )
, _scratch2( copy._scratch2 )
, _P1( copy._P1 )
, _P2( copy._P2 )
, _Rslt( copy._Rslt )
{
}


// Destructor
Decimal::~Decimal()
{
//CP20030905   _heapmin();
}


const I_CHAR * Decimal::c_str() const
{
   return(_data.szBuffer);
}


// Retrieves C String from Decimal object
I_CHAR* Decimal::getString( I_CHAR* pszString, int nBuffSize ) const
{
   if( ! _data.szBuffer )
   {
      i_strcpy( pszString, I_( "" ) );
      return( pszString );
   }

   int nReqdBuffSize = i_strlen( _data.szBuffer ) + 1;

   if( nBuffSize < nReqdBuffSize )
   {
      I_CHAR     szSize[ 10 ];

      i_itot( nBuffSize, szSize, 10 );
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "Decimal::getString( I_CHAR* pszString, int " )
                        I_( "nBuffSize ) const" ),
                        DICORE_BUFFER_SIZE_TOO_SMALL,
                        szSize );
   }

   memcpy( pszString, _data.szBuffer, nReqdBuffSize * sizeof( I_CHAR ) );

   return( pszString );
}


// Returns absolute value of Decimal object
Decimal Decimal::abs() const
{
   Decimal absString( *this );

   I_CHAR* pszSign = NULL;

   pszSign = i_strchr( absString._data.szBuffer, I_( '-' ) );

   if( pszSign )
   {
      // Determine length of negative number including minus sign
      unsigned nStringLen = i_strlen( absString._data.szBuffer );

      // How far away is minus sign from beginning of string?
      unsigned nOffset = pszSign - absString._data.szBuffer;

      // Determine number of characters after minus sign
      unsigned nMoveCount = nStringLen - nOffset - 1;

      if( nMoveCount )
      {
         memmove( pszSign, pszSign + 1, nMoveCount * sizeof( I_CHAR ) );     // Shift trailing characters to left by 1
         absString._data.szBuffer[nStringLen - 1] = '\0'; // Make DStringA 1 character less in length
      }
   }

   return( absString );
}


// Assignment Operator
Decimal& Decimal::operator=( const Decimal &copy )
{
   _sRsltLen = copy._sRsltLen;

   _data = copy._data;
   _scratch1 = copy._scratch1;
   _scratch2 = copy._scratch2;
   _P1 = copy._P1;
   _P2 = copy._P2;

   return( *this );
}


// String Assignment
Decimal& Decimal::operator=( const I_CHAR * pszStringNum )
{
   _clearData();
   _init( pszStringNum );

   return( *this );
}


Decimal& Decimal::operator=( I_CHAR * pszStringNum )
{
   _clearData();
   _init( pszStringNum );

   return( *this );
}


Decimal& Decimal::operator=( const DString * pszStringNum )
{
   _clearData();
   _init( pszStringNum->c_str() );

   return( *this );
}


Decimal& Decimal::operator=( DString * pszStringNum )
{
   _clearData();
   _init( pszStringNum->c_str() );

   return( *this );
}


Decimal& Decimal::operator=( const DString & pszStringNum )
{
   _clearData();
   _init( pszStringNum.c_str() );

   return( *this );
}


Decimal& Decimal::operator=( DString & pszStringNum )
{
   _clearData();
   _init( pszStringNum.c_str() );

   return( *this );
}


Decimal& Decimal::operator=( char num )
{
   _clearData();
   _initInt( num );

   return( *this );
}


Decimal& Decimal::operator=( unsigned char num )
{
   _clearData();
   _initUInt( num );

   return( *this );
}


Decimal& Decimal::operator=( short num )
{
   _clearData();
   _initInt( num );

   return( *this );
}


Decimal& Decimal::operator=( unsigned short num )
{
   _clearData();
   _initUInt( num );

   return( *this );
}


Decimal& Decimal::operator=( int num )
{
   _clearData();
   _initInt( num );

   return( *this );
}


Decimal& Decimal::operator=( unsigned int num )
{
   _clearData();
   _initUInt( num );

   return( *this );
}


Decimal& Decimal::operator=( long num )
{
   _clearData();
   _initInt( num );

   return( *this );
}


Decimal& Decimal::operator=( unsigned long num )
{
   _clearData();
   _initUInt( num );

   return( *this );
}


Decimal& Decimal::operator=( DIINT64 num )
{
   _clearData();
   _initInt( num );

   return( *this );
}


Decimal& Decimal::operator=( unsigned DIINT64 num )
{
   _clearData();
   _initUInt( num );

   return( *this );
}

#if 0
Decimal& Decimal::operator=( float num )
{
   _clearData();
   _initDouble( num );

   return( *this );
}


Decimal& Decimal::operator=( double num )
{
   _clearData();
   _initDouble( num );

   return( *this );
}
#endif

// Adds two Decimal Objects and returns Sum
Decimal Decimal::operator+( const Decimal& add2 )
{
   I_CHAR  *szSwap;          // Used to swap strings for difference
   short sIdx1,            // Loop variable
   sIdx2;            // Loop variable
   short sTemp;
   bool fRsltFloat;
   bool fRsltSign;
   short sRsltIDig;
   short sRsltFDig;
   Decimal resultString( ( MAX_RESULT_STRING_SIZE * 2 + 1 ) * sizeof( I_CHAR ) );
   I_CHAR  *pszResult = NULL;
   short pszResultSize = 0;


   if( add2.isZero() )
   {
      resultString = *this;
      return( resultString );
   }

   if( this->isZero() )
   {
      return( add2 );
   }

   /*************************/
   /**  Study the numbers  **/
   /*************************/
   _studyNumbers( add2._data.szBuffer );

   fRsltFloat = _P1.fFloat || _P2.fFloat;

   // Determine maximum result length
   // sRsltIDig = max( _P1.sIDig, _P2.sIDig ) + 1;
   if( _P1.sIDig > _P2.sIDig )
      sRsltIDig = _P1.sIDig + 1;
   else
      sRsltIDig = _P2.sIDig + 1;

   // sRsltFDig = max( _P1.sFDig, _P2.sFDig );
   if( _P1.sFDig > _P2.sFDig )
      sRsltFDig = _P1.sFDig;
   else
      sRsltFDig = _P2.sFDig;

   sTemp = sRsltIDig + sRsltFDig;            // Length of total DStringA


   // Allocate a result buffer, now that we know how long it could be.
   pszResultSize = sTemp + 1;
   if( MAX_RESULT_STRING_SIZE < pszResultSize )
      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_( "Decimal::getString( I_CHAR* pszString, int " )
                        I_( "nBuffSize ) const" ),
                        DICORE_BUFFER_SIZE_TOO_SMALL,
                        asString( pszResultSize ).c_str() );
   pszResult = new I_CHAR [ pszResultSize ];

   if( !pszResult )
   {
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "Decimal::operator+( const Decimal& " )
                     I_( "add2 )" ),
                     BASE_ALLOC_FAIL );
   }


   // Make a string of 0's for padding
   int i;
   for( i = 0; i < sTemp; ++i )
   {
      resultString._data.szBuffer[ i ] = I_( '0' );
   }
   resultString._data.szBuffer[sTemp] = 0;             // Null terminate

   // Line strings up in work strings
   // Fractional portion
   memmove( &_P1.szWork[sRsltIDig], _P1.szFrac, ( _P1.sFDig + 1 ) * sizeof( I_CHAR ) );
   // Add 0 padding to end
   i_strncpy( &_P1.szWork[sRsltIDig + _P1.sFDig],
              resultString._data.szBuffer,
              ( sRsltFDig - _P1.sFDig ) /* sizeof( I_CHAR )*/ );
   // Integer portion
   memmove( &_P1.szWork[sRsltIDig - _P1.sIDig], _P1.szWork, _P1.sIDig * sizeof( I_CHAR ) );
   // Add 0 padding to start
   i_strncpy( _P1.szWork, resultString._data.szBuffer, ( sRsltIDig - _P1.sIDig ) /* sizeof( I_CHAR )*/ );
   _P1.szWork[sTemp] = 0;                 // Null terminate

   // Fractional portion
   memmove( &_P2.szWork[sRsltIDig], _P2.szFrac, ( _P2.sFDig + 1 ) * sizeof( I_CHAR ) );
   // Add 0 padding to end
   i_strncpy( &_P2.szWork[sRsltIDig + _P2.sFDig],
              resultString._data.szBuffer,
              ( sRsltFDig - _P2.sFDig ) /* sizeof( I_CHAR )*/ );
   // Integer portion
   memmove( &_P2.szWork[sRsltIDig - _P2.sIDig], _P2.szWork, _P2.sIDig * sizeof( I_CHAR ) );
   // Add 0 padding to start
   i_strncpy( _P2.szWork, resultString._data.szBuffer, ( sRsltIDig - _P2.sIDig ) /* sizeof( I_CHAR )*/ );
   _P2.szWork[sTemp] = 0;



   if( ! ( _P1.fSign ^ _P2.fSign ) )
   {                                // Matching signs - add numbers
      fRsltSign = _P1.fSign;          // Sign won't change
      _addStrings( _P1.szWork, _P2.szWork, pszResult );

   } // end if matching signs
   else
   { // Signs are different.  Result is difference with sign of larger

      // Sign of result will match sign of larger value
      // Result is <larger> - <smaller>
      if( ( sTemp = i_strcmp( _P1.szWork, _P2.szWork ) ) >= 0 )
      {
         if( sTemp > 0 )
            fRsltSign = _P1.fSign;    // _P1 > _P2
         else if( sTemp == 0 )
         {
            /************************************************/
            /**  Numbers are equal and have opposite sign  **/
            /**  This means that the result will be 0 and  **/
            /**  we can stop right here.                   **/
            /************************************************/

            if( fRsltFloat )
               i_strcpy( resultString._data.szBuffer, I_( "0.0" ) );
            else
               i_strcpy( resultString._data.szBuffer, I_( "0" ) );

            delete [] pszResult;
            return( resultString );
         } // end if equal and opposite values
      }
      else
      {
         fRsltSign = _P2.fSign;          // _P2 > _P1
         szSwap = _P1.szWork;             // Swap so _P1 is always larger value
         _P1.szWork = _P2.szWork;
         _P2.szWork = szSwap;
         if( fRsltFloat )
         {
            szSwap = _P1.szFrac;
            _P1.szFrac = _P2.szFrac;
            _P2.szFrac = szSwap;
         }
      }

      _diffStrings( _P1.szWork, _P2.szWork, pszResult );

   } // end if different signs


   if( isZero( pszResult ) )
   {
      delete [] pszResult;
      return(Decimal( I_( "0.0" ) ));
   }


   /***************************/
   /**  Assemble the result  **/
   /***************************/
   sIdx1 = 0;
   sIdx2 = 0;
   short sBytes = 0;

   if( ! fRsltSign )
      resultString._data.szBuffer[sIdx1++] = I_( '-' );

   if( pszResult[sIdx2] == I_( '0' ) )
   {
      sBytes = sRsltIDig - 1;
      //assert( pszResultSize >= (
      i_strncpy( &resultString._data.szBuffer[sIdx1],
                 &pszResult[++sIdx2],
                 sBytes /* sizeof( I_CHAR )*/ );
      sIdx1 += sBytes;
      sIdx2 += sBytes;
      resultString._data.szBuffer[sIdx1] = '\0';     // Terminate
   }
   else
   {
      i_strncpy( &resultString._data.szBuffer[sIdx1],
                 &pszResult[sIdx2],
                 sRsltIDig /* sizeof( I_CHAR )*/ );
      sIdx1 += sRsltIDig;
      sIdx2 += sRsltIDig;
      resultString._data.szBuffer[sIdx1] = '\0';
   }

   // Do we have something past the decimal point?
   if( sRsltFDig )
   {
      I_CHAR c = GET_FRACT_SEPARATOR;
      resultString._data.szBuffer[sIdx1++] = GET_FRACT_SEPARATOR;
      resultString._data.szBuffer[sIdx1] = '\0';
      i_strcat( &resultString._data.szBuffer[sIdx1],
                &pszResult[sIdx2] );
   }


   resultString._stripOffLeadingZeros();

   delete [] pszResult;
   return( resultString );
}   // operator+


Decimal Decimal::operator/( const Decimal& divString )
{

   I_CHAR  *szPQuot;         // Partial Quotient buffer (points to Scratch Buffer 1)
   I_CHAR  szPad[ 4 ];         // Padding DStringA
   bool  fLive;            // Result now has live characters
   short sP1Len,           // Length of _P1
   sP2Len;           // Length of _P2
   short sPadLen;          // Length of pad DStringA
   short sRslt,            // Current length of result
   sQuot;            // Current length of quotient
   short sIdx1;            // Loop variable
   short sTemp;
   static unsigned maxResultBufSize = MAX_RESULT_STRING_SIZE + 1;
   I_CHAR  szResult[ MAX_RESULT_STRING_SIZE + 1 ];


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   if( divString.isZero() )
   {                       // Attempted division by zero
      THROWFROMFILE( DICORE_CONDITION,
                     I_( "Decimal::operator/( const Decimal& " )
                     I_( "divString )" ),
                     DICORE_DIVIDE_BY_ZERO )
   }

   if( this->isZero() )
   {                       // Zero / <n> = 0, just set and exit
      return( Decimal( I_( "0" ) ) );
   }

   _studyNumbers( divString._data.szBuffer );


   i_strcpy( &_P1.szWork[_P1.sIDig], _P1.szFrac );   // Want number as single DStringA
   i_strcpy( &_P2.szWork[_P2.sIDig], _P2.szFrac );
   _P1.szFrac = &_P1.szWork[_P1.sIDig];            // Re-point DStringA ptr
   _P2.szFrac = &_P2.szWork[_P2.sIDig];

   _Rslt.fFloat = _P1.fFloat || _P2.fFloat;

   if( _P2.sFDig )
   {
      _P1.sIDig += _P2.sFDig;        // Adjust length
   }

   sP1Len = _P1.sIDig + _P1.sFDig;   // Total length
   sP2Len = _P2.sIDig + _P2.sFDig;   // Total length

   for( sIdx1 = 0; sIdx1 < _P2.sFDig; ++sIdx1 )
   {                       // Adjust for Divisor's decimal point
      _P1.szFrac[_P1.sFDig++] = I_( '0' );
   }
   _P1.szFrac[_P1.sFDig] = 0;  // Re-Null terminate operator


   // Use Scratch Buffer 1 for storing partial quotients
   // Is scratch buffer 1 (if any) large enough?
   if( _scratch1.nBuffSize < ( 2 * _sRsltLen + 4 ) * sizeof( I_CHAR ) )
   {
      // Do we have a current Scratch 1 buffer?
      if( _scratch1.szBuffer )
      {
         // Free current Scratch 1 buffer
         delete [] _scratch1.szBuffer;
      }

      _scratch1.nBuffSize = ( 2 * _sRsltLen + 4 ) * sizeof( I_CHAR );
      _scratch1.szBuffer = new I_CHAR[_scratch1.nBuffSize];
      if( !_scratch1.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator/( const Decimal& " )
                        I_( "divString )" ),
                        BASE_ALLOC_FAIL )
      }
   }
   szPQuot = _scratch1.szBuffer;     // Associate szPQuot with Scratch buffer 1


   // Is our current _Rslt buffer (if any) large enough?
   if( _Rslt.nBuffSize < ( 2 * _sRsltLen + 4 ) )
   {
      // Do we have a current _Rslt buffer?
      if( _Rslt.nBuffSize > 0 )
      {
         // Free current _Rslt buffer
         delete [] _Rslt.szWork;
      }

      _Rslt.nBuffSize = 2 * _sRsltLen + 4;
      _Rslt.szWork = new I_CHAR[_Rslt.nBuffSize];
      if( !_Rslt.szWork )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator/( const Decimal& " )
                        I_( "divString )" ),
                        BASE_ALLOC_FAIL )
      }
   }


   fLive = false;                   // Result not yet live
   // Init result
   if( _P1.fSign ^ _P2.fSign )     // Different signs, negative result
   {
      i_strcpy( szResult, I_( "-" ) );      // Assign sign to result
      sRslt = 1;                    // Length of result DStringA
   }
   else
   {
      szResult[0] = 0;
      sRslt = 0;                    // Length of result DStringA
   }

   i_strcpy( szPad, I_( "0.0" ) );           // Initial pad DStringA
   sPadLen = 3;

   for( sIdx1 = 0; _P1.szWork[sIdx1] == I_( '0' ); ++sIdx1 )
   {                                // Seek to first active digit
      if( sIdx1 >= _P1.sIDig )
      {
         i_strcat( szResult, szPad ); // right of DP
         sRslt += sPadLen;          // Track length
         assert( sRslt < maxResultBufSize );
         szPad[1] = 0;              // Make sure is now just "0";
         sPadLen = 1;
         fLive = true;              // Result has live chars in it
      }
   }
   szPQuot[0] = I_( '0' );                // Always need 1 leading 0
   sQuot = 1;


   while( sRslt < _sRsltLen )
   {
      do
      {                             // While divisor > partial quotient
         if( sIdx1 == _P1.sIDig )
         {                          // If hit decimal pt
            if( fLive )            // If we already have live chars
            {
               I_CHAR c = GET_FRACT_SEPARATOR;
               szResult[sRslt++] = GET_FRACT_SEPARATOR;   // Time for decimal pt
               assert( sRslt < maxResultBufSize );
               szResult[sRslt] = 0;       // Keep null terminated
            }
            else
            {
               i_strcat( szResult, I_( "0." ) );
               sRslt += 2;
               assert( sRslt < maxResultBufSize );
               fLive = true;
            }
            _P1.sIDig = -1;     // Set to trip just once
         } // end if hit decimal pt

         if( sIdx1 < sP1Len )
         {                          // If still have digits
            szPQuot[sQuot++] = _P1.szWork[sIdx1++];   // move digit to PQ
         }
         else
         {
            // If we've used all digits and have a zero partial quotient
            if( Decimal::isZero( szPQuot ) )
               break;               // We're all done dividing

            szPQuot[sQuot++] = I_( '0' ); // Add a zero
         }
         szPQuot[sQuot] = 0;        // Keep null terminated

         // Compare numbers (keep result so can use twice)
         sTemp = _compareStrings( _P2.szWork, szPQuot );

         if( fLive && sTemp > 0 )  // Still not enough to get a digit
         {
            // If wouldn't be a leading 0
            szResult[sRslt++] = I_( '0' );   // Add a 0 to result
            _ASSERTE( sRslt < maxResultBufSize );
            szResult[sRslt] = 0;       // Keep null terminated
         }
      } while( sTemp > 0 );


      // Make divisor same length as PQuot
      if( sQuot < sP2Len )
      {
         memmove( &szPQuot[ sP2Len - sQuot ], szPQuot, ( sQuot + 1 ) * sizeof( I_CHAR ) );
         I_CHARset( szPQuot, I_( '0' ), sP2Len - sQuot );
         sQuot += sP2Len - sQuot;
      }

      _ASSERTE( sQuot >= sP2Len );
      I_CHARset( _Rslt.szWork, I_( '0' ), sQuot ); // Make divisor same length as PQuot
      i_strcpy( &_Rslt.szWork[sQuot - sP2Len], _P2.szWork );

      sTemp = I_( '0' );                  // Track subtractions
      while( _compareStrings( szPQuot, _P2.szWork ) >= 0 )
      {                             // While partial quotient >= divisor
         _diffStrings( szPQuot, _Rslt.szWork, szPQuot );
         ++sTemp;                   // Count reps
      }


      szResult[sRslt++] = (I_CHAR) sTemp;   // Save new digit
      _ASSERTE( sRslt < maxResultBufSize );
      szResult[sRslt] = 0;                // Keep null terminated
      fLive = true;                 // Result contains live chars

      while( szPQuot[1] == I_( '0' ) )   // Strip off all but one leading zero
         i_strcpy( &szPQuot[1], &szPQuot[2] );
      sQuot = i_strlen( szPQuot );

      if( Decimal::isZero( szPQuot ) && sIdx1 >= sP1Len )
         break;         // Zero quotient and used all digits of dividend

   } // end while still dividing

   return(Decimal( szResult ));
}


Decimal Decimal::frac() const
{
   I_CHAR *szFrac;

   Decimal fracString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFrac = i_strchr( fracString._data.szBuffer, GET_FRACT_SEPARATOR ) ) != NULL )
   {
      return(Decimal( szFrac ));
   }
   else
   {
      return(Decimal( I_( "" ) ));
   }
}


Decimal Decimal::integer() const
{
   I_CHAR *szFrac;

   Decimal intString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFrac = i_strchr( intString._data.szBuffer,  GET_FRACT_SEPARATOR ) ) != NULL )
   {
      *szFrac = '\0';               // Chop off the fractional part
   }
   return( intString );
}


// Determines modulus of two Decimal Objects
Decimal Decimal::operator%( const Decimal& modString )
{

   I_CHAR  *szPQuot;         // Partial Quotient buffer (points to Scratch Buffer 1)
   short sP1Len,           // Length of _P1
   sP2Len;           // Length of _P2
   short sQuot;            // Current length of quotient
   short sIdx1,            // Loop variables
   sIdx2;
   short sTemp;
   I_CHAR  szResult[ MAX_RESULT_STRING_SIZE + 1 ];


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   if( isZero( modString._data.szBuffer ) )
   {                       // Attempted division by zero
      THROWFROMFILE( DICORE_CONDITION,
                     I_( "Decimal::operator%( const Decimal& " )
                     I_( "modString )" ),
                     DICORE_DIVIDE_BY_ZERO );
   }

   if( isZero( _data.szBuffer ) )
   {                       // Zero % <n> = 0, just set and exit
      return( Decimal( I_( "0" ) ) );
   }

   // If abs(_P1) <= abs(_P2), we already know the answer
   sTemp = _compareStrings( this->abs()._data.szBuffer,
                            modString.abs()._data.szBuffer );
   if( sTemp < 0 )
   {  // abs(_P1) < abs(_P2), result is _P1
      return(*this);
   }
   else if( sTemp == 0 )
   {  // _P1 == _P2, result is always 0
      return( Decimal( I_( "0" ) ) );
   }

   // _P1 > _P2, need to do the math

   _studyNumbers( modString._data.szBuffer );

   i_strcpy( &_P1.szWork[_P1.sIDig], _P1.szFrac );   // Want number as single DStringA
   i_strcpy( &_P2.szWork[_P2.sIDig], _P2.szFrac );
   _P1.szFrac = &_P1.szWork[_P1.sIDig];            // Re-point DStringA ptr
   _P2.szFrac = &_P2.szWork[_P2.sIDig];

   _Rslt.fFloat = _P1.fFloat;         // Result can be float if _P1 is float
   _Rslt.fSign  = _P1.fSign;          // Sign tracks sign of _P1

   if( _P2.sFDig )
   {
      _P1.sIDig += _P2.sFDig;         // Adjust length
   }

   sP1Len = _P1.sIDig + _P1.sFDig;    // Total length
   sP2Len = _P2.sIDig + _P2.sFDig;    // Total length

   for( sIdx1 = 0; sIdx1 < _P2.sFDig; ++sIdx1 )
   {                       // Adjust for Divisor's decimal point
      _P1.szFrac[_P1.sFDig++] = I_( '0' );
   }
   _P1.szFrac[_P1.sFDig] = 0;  // Re-Null terminate operator


   // Use Scratch Buffer 1 for storing partial quotients
   // Is scratch buffer 1 (if any) large enough?
   if( _scratch1.nBuffSize < ( sP1Len + 4 ) * sizeof( I_CHAR ) )
   {
      // Do we have a current Scratch 1 buffer?
      if( _scratch1.szBuffer )
      {
         // Free current Scratch 1 buffer
         delete [] _scratch1.szBuffer;
      }

      _scratch1.nBuffSize = ( sP1Len + 4 ) * sizeof( I_CHAR );
      _scratch1.szBuffer = new I_CHAR[_scratch1.nBuffSize];
      if( !_scratch1.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator%( const Decimal& " )
                        I_( "modString )" ),
                        BASE_ALLOC_FAIL );
      }
   }
   szPQuot = _scratch1.szBuffer;     // Associate szPQuot with Scratch buffer 1


   // Is our current _Rslt buffer (if any) large enough?
   if( _Rslt.nBuffSize < ( sP1Len + 4 ) )
   {
      // Do we currently have a _Rslt buffer?
      if( _Rslt.nBuffSize > 0 )
      {
         // We do have a _Rslt buffer, we need to free it
         delete [] _Rslt.szWork;
      }

      _Rslt.nBuffSize = sP1Len + 4;
      _Rslt.szWork = new I_CHAR[_Rslt.nBuffSize];
      if( !_Rslt.szWork )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator%( const Decimal& " )
                        I_( "modString )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   sIdx1 = 0;                       // Reset for 'divide'
   szPQuot[0] = I_( '0' );                // Always need one leading zero
   sQuot = 1;

   while( sIdx1 < _P1.sIDig )
   {
      do
      {                             // While divisor > partial quotient
         if( sIdx1 == _P1.sIDig )
         {                          // If hit decimal pt
            break;                  // We're done
         } // end if hit decimal pt

         szPQuot[sQuot++] = _P1.szWork[sIdx1++];   // move digit to PQ
         szPQuot[sQuot] = 0;        // Keep null terminated

         // Compare numbers (keep result so can use twice)
         sTemp = _compareStrings( _P2.szWork, szPQuot );
      } while( sTemp > 0 );

      if( sQuot >= sP2Len )
      {
         I_CHARset( _Rslt.szWork, I_( '0' ), sQuot ); // Make divisor same length as PQuot
         i_strcpy( &_Rslt.szWork[sQuot - sP2Len], _P2.szWork );

         while( _compareStrings( szPQuot, _P2.szWork ) >= 0 )
         {                             // While partial quotient >= divisor
            _diffStrings( szPQuot, _Rslt.szWork, szPQuot );
         }
      }

      while( szPQuot[1] == I_( '0' ) )   // Strip off all but one leading zero
         i_strcpy( &szPQuot[1], &szPQuot[2] );
      sQuot = i_strlen( szPQuot );

   } // end while still dividing

   /***************************/
   /**  Assemble the result  **/
   /***************************/
   i_strcpy( szPQuot, &szPQuot[1] );  // Strip off the leading zero
   sIdx1 = 0;
   sIdx2 = 0;
   if( !_Rslt.fSign )               // Negative result
      szResult[sIdx2++] = I_( '-' );      // Add sign

   // Set to de-adjust result
   _Rslt.sIDig = i_strlen( szPQuot ) - _P2.sFDig;

   for( ; sIdx1 < _Rslt.sIDig; ++sIdx1 )
   {
      szResult[sIdx2++] = szPQuot[sIdx1];
   }
   szResult[sIdx2] = 0;             // Add on null terminator

   if( szPQuot[sIdx1] )            // If any characters left
   {
      I_CHAR c = GET_FRACT_SEPARATOR;
      szResult[sIdx2++] = GET_FRACT_SEPARATOR;      // Add decimal point
      // Add fractional portion
      i_strcpy( &szResult[sIdx2], &szPQuot[sIdx1] );

      sIdx1 = i_strlen( szResult );   // Check for trailing 0's
      --sIdx1;

      while( szResult[sIdx1] == I_( '0' ) && szResult[sIdx1 - 1] != GET_FRACT_SEPARATOR )
      {                             // Allow <n>.0
         szResult[sIdx1--] = 0;     // Chop off trailing zero
      } // end while have trailing zeros
   }

   return(Decimal( szResult ));
}       // operator %


Decimal Decimal::operator*( const Decimal& multString )
{

   I_CHAR  *szPProd;         // Partial product buffer (Points to Scratch Buff 1)
   I_CHAR  *szTemp;          // Points to Scratch Buffer 2
   I_CHAR  *szSwap;          // Used to swap strings for speed
   short sIdx1,            // Loop variable
   sIdx2;            // Loop variable
   short sTemp;
   I_CHAR  szResult[ MAX_RESULT_STRING_SIZE + 1 ];


   /*************************/
   /**  Study the numbers  **/
   /*************************/

   if( this->isZero() || multString.isZero() )
   {                       // Zero * <n> = 0, just set and exit
      return( Decimal( I_( "0" ) ) );
   }

   _studyNumbers( multString._data.szBuffer );

   i_strcpy( &_P1.szWork[_P1.sIDig], _P1.szFrac );   // Want number as single DStringA
   i_strcpy( &_P2.szWork[_P2.sIDig], _P2.szFrac );
   _P1.szFrac = &_P1.szWork[_P1.sIDig];            // Re-point DStringA ptr
   _P2.szFrac = &_P2.szWork[_P2.sIDig];

   _Rslt.fFloat = _P1.fFloat || _P2.fFloat;

   if( i_strlen( _P1.szWork ) < i_strlen( _P2.szWork ) )
   {                       // String 1 is shorter, swap strings
      szSwap  = _P1.szWork;   // Swap DStringA ptrs
      _P1.szWork = _P2.szWork;
      _P2.szWork = szSwap;

      sIdx1   = _P1.sIDig;   // Swap associated items
      _P1.sIDig = _P2.sIDig;
      _P2.sIDig = sIdx1;

      sIdx1   = _P1.sFDig;
      _P1.sFDig = _P2.sFDig;
      _P2.sFDig = sIdx1;

      // Don't have to swap signs since we just check for difference
   }


   _Rslt.sIDig = _P1.sIDig + _P2.sIDig;  // Maximum result length
   _Rslt.sFDig = _P1.sFDig + _P2.sFDig;

   _sRsltLen = _Rslt.sIDig + _Rslt.sFDig + 1;   // Length of total result


   // Is our current _Rslt buffer (if any) large enough?
   if( _Rslt.nBuffSize < ( _sRsltLen + 2 ) )
   {
      // Do we currently have a _Rslt buffer?
      if( _Rslt.nBuffSize > 0 )
      {
         // We do have a _Rslt buffer, we need to free it
         delete [] _Rslt.szWork;
      }

      _Rslt.nBuffSize = _sRsltLen + 2;
      _Rslt.szWork = new I_CHAR[_Rslt.nBuffSize];
      if( !_Rslt.szWork )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator*( const Decimal& " )
                        I_( "multString )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   // szPProd points to Scratch Buffer 1
   // Is scratch buffer 1 (if any) large enough?
   if( _scratch1.nBuffSize < ( _sRsltLen + 2 ) * sizeof( I_CHAR ) )
   {
      // Do we currently have a Scratch 1 buffer?
      if( _scratch1.szBuffer )
      {
         // We do, we need to free it
         delete [] _scratch1.szBuffer;
      }

      _scratch1.nBuffSize = ( _sRsltLen + 2 ) * sizeof( I_CHAR );
      _scratch1.szBuffer = new I_CHAR[_scratch1.nBuffSize];
      if( !_scratch1.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator*( const Decimal& " )
                        I_( "multString )" ),
                        BASE_ALLOC_FAIL );
      }
   }
   szPProd = _scratch1.szBuffer;   // Associate szPProd with Scratch Buffer 1


   // szTemp points to Scratch Buffer 2
   // Is scratch buffer 2 (if any) large enough?
   if( _scratch2.nBuffSize < ( _sRsltLen + 2 ) )
   {
      // Do we currently have a Scratch 2 buffer?
      if( _scratch2.nBuffSize > 0 )
      {
         // We do, we need to free it
         delete [] _scratch2.szBuffer;
      }

      _scratch2.nBuffSize = _sRsltLen + 2;
      _scratch2.szBuffer = new I_CHAR[_scratch2.nBuffSize];
      if( !_scratch2.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::operator*( const Decimal& " )
                        I_( "multString )" ),
                        BASE_ALLOC_FAIL );
      }
   }
   szTemp = _scratch2.szBuffer;    // Associate szTemp with Scratch Buffer 2


   I_CHARset( _Rslt.szWork, I_( '0' ), _sRsltLen );
   _Rslt.szWork[_sRsltLen] = 0;         // Null terminate
   sTemp = _P2.sIDig + _P2.sFDig;       // Length of _P2


   szPProd[_sRsltLen] = 0;         // Null terminate


   for( sIdx1 = sTemp - 1, sIdx2 = 1; sIdx1 >= 0; --sIdx1, ++sIdx2 )
   {                                // Work from right to left
      // Make 0 fill string for partial product
      I_CHARset( szPProd, I_( '0' ), _sRsltLen );

      // By adjusting position of rightmost I_CHAR we add trailing 0's
      _multString( _P1.szWork, _P2.szWork[sIdx1], szPProd, _sRsltLen - sIdx2 );

      // Add partial product to result
      _addStrings( szPProd, _Rslt.szWork, szTemp );
      i_strcpy( _Rslt.szWork, szTemp );
   } // end for all digits in _P2


   /***************************/
   /**  Assemble the result  **/
   /***************************/

   if( _Rslt.szWork[0] == I_( '0' ) )
   {
      for( sIdx1 = 0;
         sIdx1 < _Rslt.sIDig && _Rslt.szWork[sIdx1] == I_( '0' );
         ++sIdx1 )
      {
         ;        // Seek to active start of number
      }
   }
   else
      sIdx1 = 0;

   sIdx2 = 0;
   if( _P1.fSign ^ _P2.fSign )     // Different signs, negative result
   {
      szResult[sIdx2++] = I_( '-' );      // Add sign
   }

   for( ; sIdx1 <= _Rslt.sIDig; ++sIdx1 )
   {
      szResult[sIdx2++] = _Rslt.szWork[sIdx1];
   }
   szResult[sIdx2] = 0;             // Add on null terminator

   if( _Rslt.fFloat )
   {
      I_CHAR c = GET_FRACT_SEPARATOR;
      szResult[sIdx2++] = GET_FRACT_SEPARATOR;      // Add decimal point
      // Add fractional portion
      i_strcpy( &szResult[sIdx2], &_Rslt.szWork[sIdx1] );

      sIdx1 = i_strlen( szResult );   // Check for trailing 0's
      --sIdx1;

      while( szResult[sIdx1] == I_( '0' ) && szResult[sIdx1 - 1] != GET_FRACT_SEPARATOR )
      {                             // Allow <n>.0
         szResult[sIdx1--] = 0;     // Chop off trailing zero
      } // end while have trailing zeros
   }


   return(Decimal( szResult ));
}    // operator*


Decimal Decimal::changeSign() const
{
   if( i_strchr( _data.szBuffer, I_( '-' ) ) )
   {
      // If number is negative, just take the absolute value
      return( this->abs() );
   }
   else
   {
      Decimal negString( *this );

      negString._stripOffLeadingZeros();

      int nStringLen = i_strlen( negString._data.szBuffer );

      if( nStringLen == (negString._data.nBuffSize-1) )    // out of buffer space, reallocate
      {
         // Make copy with larger buffer and put in negative sign
         Decimal tempCopy( negString._data.nBuffSize + 1 );
         tempCopy._data.szBuffer[0] = I_( '-' );
         i_strcpy( &tempCopy._data.szBuffer[1], negString._data.szBuffer );

         return( tempCopy );
      }
      else      // have enough buffer space
      {
         // shift all characters to right by 1 (including terminating NULL)
         memmove( &negString._data.szBuffer[1],
                  &negString._data.szBuffer[0],
                  ( nStringLen + 1 ) * sizeof( I_CHAR ) );

         // add negative sign in front of shifted characters
         negString._data.szBuffer[0] = I_( '-' );

         return( negString );
      }
   }
}


Decimal Decimal::round( short sRndAfter=0 ) const
{
   I_CHAR  *szFPart;      // Fractional portion
   short sIdx;
   short sDig1;

   Decimal roundString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFPart = i_strchr( roundString._data.szBuffer, GET_FRACT_SEPARATOR ) ) != NULL )
   {                    // If DStringA has a decimal point
      if( i_strlen( szFPart ) > sRndAfter )
      {                 // If it has enough characters after the decimal pt
         if( szFPart[sRndAfter + 1] > '4' )
         {              // If need to round up
            sIdx = &szFPart[sRndAfter] - roundString._data.szBuffer;   // Offset from start
            if( sRndAfter == 0 )
               --sIdx;        // Skip the '.'
            sDig1 = ( roundString._data.szBuffer[sIdx] & 0x0F ) + 1;     // Round digit up
            roundString._data.szBuffer[sIdx] = (I_CHAR) ( sDig1 % 10 ) + I_( '0' ); // Save rounded digit
            while( sDig1 > 9 && sIdx > 0 )
            {                 // While rounding works to left
               --sIdx;                                   // Move left one digit
               if( myIsDigit( roundString._data.szBuffer[sIdx] ) )
               {                             // Skip past '.'
                  sDig1 = ( roundString._data.szBuffer[sIdx] & 0x0F ) + 1;  // Round digit up
                  roundString._data.szBuffer[sIdx] = (I_CHAR) ( sDig1 % 10 ) + I_( '0' ); // Save
               }
            } // end while rounding moves left


            /***********************************/
            /**  Check for rounding overflow  **/
            /***********************************/

            if( sIdx == 0 && sDig1 > 9 )
            {
               szFPart[sRndAfter + 1] = 0; // Chop number at rounding pt

               /******************************************/
               /**  Make a space and put a leading '1'  **/
               /******************************************/

               memmove( &roundString._data.szBuffer[1],
                        roundString._data.szBuffer,
                        i_strlen( roundString._data.szBuffer ) * sizeof( I_CHAR ) + 1 );
               roundString._data.szBuffer[0] = '1';

               /***********************************************/
               /**  Since we've handled the overflow, don't  **/
               /**  tell them about it.                      **/
               /***********************************************/

               return( roundString );
            }
         } // end if need to round up
         szFPart[sRndAfter + 1] = 0; // Chop number at rounding pt
      } // end if DStringA is long enough to round
   } // end if DStringA has anything to round

   return( roundString );
}


Decimal Decimal::trunc( short sTrncAfter=0 ) const
{
   I_CHAR  *szFPart;      // Fractional portion

   Decimal truncString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFPart = i_strchr( truncString._data.szBuffer, GET_FRACT_SEPARATOR ) ) != NULL )
   {                    // If DStringA has a decimal point
      if( i_strlen( szFPart ) > sTrncAfter )
      {                 // If it has enough characters after the decimal pt
         szFPart[sTrncAfter + 1] = '\0'; // Chop after last desired digit
      } // end if DStringA is long enough to truncate
   } // end if DStringA has anything to truncate

   return( truncString );
}


// Determines whether Decimal Object is equivalent to "0"
bool Decimal::isZero() const
{
//CP20030905   short sIdx;
//CP20030905
//CP20030905   for( sIdx = i_strlen( _data.szBuffer ); sIdx >= 0; --sIdx )
//CP20030905   {        // Working right to left gets strlen() once only
//CP20030905      if( _data.szBuffer[sIdx] >= '1' && _data.szBuffer[sIdx] <= I_( '9' ) )
//CP20030905         return( false );        // String is not a zero
//CP20030905   }
//CP20030905
//CP20030905   return( true );              // No '1' - '9' found, must be zero.
   
   for( const I_CHAR* pszBuffer = _data.szBuffer; 0x00 != *pszBuffer; ++pszBuffer ) 
   {
      if( *pszBuffer >= I_('1') && *pszBuffer <= I_( '9' ) ) {
         return( false );
      }
   }
   return( true );
}


bool Decimal::isZero( I_CHAR * pszString )
{
//CP20030905   short sIdx;
//CP20030905
//CP20030905   for( sIdx = i_strlen( pszString ); sIdx >= 0; --sIdx )
//CP20030905   {
//CP20030905      // Working right to left gets strlen() once only
//CP20030905      if( pszString[sIdx] >= '1' && pszString[sIdx] <= I_( '9' ) )
//CP20030905         return( false );
//CP20030905   }
//CP20030905
//CP20030905   return( true );              // No '1' - '9' found, must be zero.
   for( ; 0x00 != *pszString; ++pszString ) 
   {
      if( *pszString >= I_('1') && *pszString <= I_( '9' ) ) {
         return( false );
      }
   }
   return( true );

}


/*****************************************************************************/
/****************************  PRIVATE METHODS  ******************************/
/*****************************************************************************/



/**
 * This function adds two formatted strings.  The 
 * strings MUST be of equal length, normalized 
 * (implied '.' at same offset), and must consist of 
 * only characters '0' - '9'.
 * 
 * @param szParam1
 * @param szParam2
 * @param szResult
 */
void Decimal::_addStrings( const I_CHAR * szParam1,
                              const I_CHAR * szParam2,
                              I_CHAR * szResult )
{
   short sDig1,            // Digit from _P1
   sDig2,            // Digit from _P2
   sDig3;            // Digit for result
   short sCarry;           // Current carry
   short sIdx1;            // Loop variable
   short sTemp;

   sCarry = 0;                   // Clear the carry
   sTemp = i_strlen( szParam1 );   // Length of result

   szResult[sTemp] = '\0';   // Null terminate result
   for( sIdx1 = ( sTemp - 1 ); sIdx1 > 0; --sIdx1 )
   {  // Add digits from right to left
      sDig1 = ( szParam1[sIdx1] & 0x0F );
      sDig2 = ( szParam2[sIdx1] & 0x0F );
      sDig3 = sDig1 + sDig2 + sCarry;
      szResult[sIdx1] = (I_CHAR) ( ( sDig3 % 10 ) + I_( '0' ) ); // save digit
      sCarry = sDig3 / 10;       // Get actual carry
   }
   szResult[sIdx1] = (I_CHAR) ( ( sCarry % 10 ) + I_( '0' ) );
}



/**
 * Compares two Decimal Objects
 * 
 *             Compares the strings as numbers.
 *             The strings must be all numeric ( '0' - '9' only ), with no
 *                decimal point or sign.
 * 
 * ^THROWS      :
 *   ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
 * 
 * @param cmpString - the other number
 * @return  -1 if 'this' is < cmpString
 *           0 if 'this' == cmpString
 *          +1 if 'this' is > cmpString
 */
short Decimal::_compareString( const Decimal& cmpString ) const
{
   PARAMETER_INFO      p1;
   PARAMETER_INFO      p2;

   _studyNumbers( _data.szBuffer, cmpString._data.szBuffer, p1, p2 );

   int   iIntSize = p1.sIDig > p2.sIDig ? p1.sIDig : p2.sIDig;
   int   iFracSize = p1.sFDig > p2.sFDig ? p1.sFDig : p2.sFDig;
   int   iNewStringLen = iIntSize + iFracSize;

   I_CHAR     *psz1 = new I_CHAR [ iNewStringLen + 1 ];
   if( !psz1 )
   {
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "Decimal::_compareString( const Decimal&" )
                     I_( " cmpString )" ),
                     BASE_ALLOC_FAIL );
   }

   if( p2.sIDig > p1.sIDig )
   {
      I_CHARset( psz1, I_( '0' ), p2.sIDig - p1.sIDig );
      memcpy( psz1 + p2.sIDig - p1.sIDig, p1.szWork, p1.sIDig * sizeof( I_CHAR ) );
   }
   else
   {
      memcpy( psz1, p1.szWork, p1.sIDig * sizeof( I_CHAR ) );
   }

   memcpy( psz1 + iIntSize, p1.szFrac, p1.sFDig * sizeof( I_CHAR ) );
   if( p2.sFDig > p1.sFDig )
   {
      I_CHARset( psz1 + p1.sFDig + iIntSize, I_( '0' ), p2.sFDig - p1.sFDig );
   }

   psz1[ iNewStringLen ] = 0;

   I_CHAR     *psz2 = new I_CHAR [ iNewStringLen + 1] ;
   if( !psz2 )
   {
      delete [] psz1;
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "Decimal::_compareString( const Decimal&" )
                     I_( " cmpString )" ),
                     BASE_ALLOC_FAIL );
   }

   if( p1.sIDig > p2.sIDig )
   {
      I_CHARset( psz2, I_( '0' ), p1.sIDig - p2.sIDig );
      memcpy( psz2 + p1.sIDig - p2.sIDig, p2.szWork, p2.sIDig * sizeof( I_CHAR ) );
   }
   else
   {
      memcpy( psz2, p2.szWork, p2.sIDig * sizeof( I_CHAR ) );
   }

   memcpy( psz2 + iIntSize, p2.szFrac, p2.sFDig * sizeof( I_CHAR ) );
   if( p1.sFDig > p2.sFDig )
   {
      I_CHARset( psz2 + p2.sFDig + iIntSize, I_( '0' ), p1.sFDig - p2.sFDig );
   }

   psz2[ iNewStringLen ] = 0;

   if( isZero( psz1 ) && isZero( psz2 ) )
   {
      delete [] psz1;
      delete [] psz2;
      return(0);
   }

   if( p1.fSign != p2.fSign )
   {
      delete [] psz1;
      delete [] psz2;

      if( p1.fSign )
      {
         return(1);
      }
      else
      {
         return(-1);
      }
   }

   short       sTempRet = _compareStrings( psz1, psz2 );

   // At this point, if one is negative, then they both are.  The number
   // that _compareStrings() reports to be smaller is actually the larger.
   if( !p1.fSign )
   {
      sTempRet = -sTempRet;
   }

   delete [] psz1;
   delete [] psz2;

   return(sTempRet);
}     // CompareString


/**
 * Compares the strings as numbers.  The strings must 
 * be all numeric ( '0' - '9' only ), with no decimal 
 * point or sign.
 * 
 * @param szParam1 - the first number
 * @param szParam2 - the second number
 * @return -1 if 'this' is < cmpString
 *          0 if 'this' == cmpString
 *         +1 if 'this' is > cmpString
 */
short Decimal::_compareStrings( const I_CHAR* pszParam1, 
                                const I_CHAR* pszParam2 ) const
{
   bool  fDone;         // Loop flag
//CP20030905   unsigned short sP1Int;        // Offset of first live digit / length of number
//CP20030905   unsigned short sP2Int;
//CP20030905   unsigned short sIdx1;         // String indexes
//CP20030905   unsigned short sIdx2;
   


   for( ; *pszParam1 == I_( '0' ); ++pszParam1 )
      ;        // Find first live character

   for( ; *pszParam2 == I_( '0' ); ++pszParam2 )
      ;        // Find first live character

//CP20030904   sIdx1 = i_strlen( szParam1 ) - sP1Int;       // Get # of live digits
   unsigned short cbParam1 = i_strlen( pszParam1 );       // Get # of live digits
   unsigned short cbParam2 = i_strlen( pszParam2 );
   if( cbParam1 != cbParam2 )
   {                 // One has more live digits, must be !=
      if( cbParam1 > cbParam2 )
         return( 1 );      // _P1 > _P2
      else
         return( -1 );     // _P1 < _P2
   }

//CP20030905   sIdx1 = sP1Int;   // Start with first live I_CHAR
//CP20030905   sIdx2 = sP2Int;
//CP20030905   sP1Int = i_strlen( szParam1 );
//CP20030905   sP2Int = i_strlen( szParam2 );

   fDone = false;
   while( !fDone )
   {
//CP20030904      if( szParam1[sIdx1] != szParam2[sIdx2] )
//CP20030904      {
//CP20030904         if( szParam1[sIdx1] > szParam2[sIdx2] )
//CP20030904            return( 1 );        // _P1 > _P2
//CP20030904         else
//CP20030904            return( -1 );       // _P1 < _P2
//CP20030904      }
//CP20030905      if( szParam1[sIdx1] > szParam2[sIdx2] ) {
      if( *pszParam1 > *pszParam2 ) {
         return( 1 );   // _P1 > _P2
      } 
      else if( *pszParam1 < *pszParam2 ) {
         return( -1 );  // _P1 < _P2
      }
//CP20030905      ++sIdx1;                   // advance to next digit
      ++pszParam1;                   // advance to next digit
//CP20030905      ++sIdx2;
      ++pszParam2;

      if( 0x00 == *pszParam1 || *pszParam2 == 0x00 )
         fDone = true;     // Hit end of integer portion
   } // end while checking integer portion

   return( 0 );     // Strings must be equal numbers
}


/**
 * This function gets the difference between two 
 * formatted strings.  The strings MUST  be of equal 
 * length, normalized (implied '.' at same offset), 
 * and must consist of only the characters '0' - '9'.
 * 
 * @param szParam1 - first number
 * @param szParam2 - second number
 * @param szResult
 */
void Decimal::_diffStrings( const I_CHAR * szParam1,
                               const I_CHAR * szParam2,
                               I_CHAR * szResult )
{
//CP20030904   short sDig1,            // Digit from _P1
//CP20030904   sDig2,            // Digit from _P2
//CP20030904   sDig3;            // Digit for result
   unsigned short sCarry;           // Current carry
   unsigned short sIdx1;            // Loop variable
   unsigned short sTemp;

   sCarry = 0;                   // Clear the carry
   sTemp = i_strlen( szParam1 );   // Length of result

   szResult[sTemp] = '\0';   // Null terminate result
   for( sIdx1 = ( sTemp - 1 ); sIdx1 > 0; --sIdx1 )
   {  // Work digits from right to left
      unsigned short sDig1 = ( szParam1[sIdx1] & 0x0F );
      unsigned short sDig2 = ( szParam2[sIdx1] & 0x0F );
      unsigned short sDig3;
      sDig1 -= sCarry;        // Perform any required 'borrow'
      if( sDig1 < sDig2 )
      {
//CP20030904         sDig1 += 10;         // Set up 'borrow'
         sDig3 = 10 + sDig1 - sDig2;
         sCarry = 1;          // Flag 'borrow' from next digit
      }
      else
      {
         sDig3 = sDig1 - sDig2;
         sCarry = 0;          // Done 'borrowing'
      }
      szResult[sIdx1] = (I_CHAR) ( sDig3 + I_( '0' ) ); // save result digit
   }
   szResult[sIdx1] = (I_CHAR) ( ( sCarry % 10 ) + I_( '0' ) );
}


/**
 * This method multiplies the string by the passed 
 * digit.  The result buffer must be at least one 
 * character longer than the string.  The starting 
 * offset is the offset of the RIGHTMOST character in 
 * the result.  This is to allow for 0 padding on
 * digits after the rightmost digit.
 * 
 * @param szParam1    - First string                    
 * @param chParam2    - Digit to multiply by            
 * @param szResult    - Result buffer                   
 * @param sStartOffs  - Starting offset in result buffer
 */
void Decimal::_multString( const I_CHAR * szParam1,
                              I_CHAR   chParam2,
                              I_CHAR * szResult,
                              short  sStartOffs )
{
   short sDig1,            // Digit from _P1
   sDig2,            // Digit from _P2
   sDig3;            // Digit for result
   short sCarry;           // Current carry
   short sIdx1;            // Loop variable
   short sTemp;

   sCarry = 0;                   // Clear the carry
   sDig1  = chParam2 - I_( '0' );      // Convert to binary
   sTemp = i_strlen( szParam1 );   // Length of result

   for( sIdx1 = ( sTemp - 1 ); sIdx1 >= 0; --sIdx1 )
   {  // Work digits from right to left
      sDig2 = ( szParam1[sIdx1] & 0x0F );
      sDig3 = asDigitProducts[sDig1][sDig2]; // Product of digits
      sDig3 += sCarry;           // Add in carry from previous digits
      sCarry = sDig3 / 10;       // Carry to next digit

      szResult[sStartOffs--] = (I_CHAR) ( ( sDig3 % 10 ) + I_( '0' ) );
   }
   szResult[sStartOffs] = (I_CHAR) ( ( sCarry % 10 ) + I_( '0' ) );
}


/**
 * Strips the leading zeros and spaces from the string
 * used to create the Decimal.
 * 
 * @return 
 */
Decimal& Decimal::_stripOffLeadingZeros()
{
   bool  fLeadingSign = false;
   short sStringLen = 0;
   short sIdx = 0;
   short sLeadingZeros = 0;
   short sMoveCount = 0;

   sStringLen = i_strlen( _data.szBuffer );

   if( ( I_( '+' ) == _data.szBuffer[0] ) || ( I_( '-' ) == _data.szBuffer[0] ) )
   {
      fLeadingSign = true;
      sIdx = 1;
   }

   for( int i = sIdx; i < sStringLen; ++i )
   {
      if( ( I_( '0' ) == _data.szBuffer[i] ) || ( I_( ' ' ) == _data.szBuffer[i] ) )
         ++sLeadingZeros;
      else
         break;
   }

   if( fLeadingSign )
   {
      sMoveCount = sStringLen - sLeadingZeros;
      if( sMoveCount )
         memmove( &_data.szBuffer[sIdx],
                  &_data.szBuffer[sLeadingZeros + 1],
                  sMoveCount * sizeof( I_CHAR ) );
      else
         i_strcpy( _data.szBuffer, I_( "0" ) );
   }
   else
   {
      sMoveCount = sStringLen - sLeadingZeros + 1;
      if( sMoveCount )
         memmove( &_data.szBuffer[0],
                  &_data.szBuffer[sLeadingZeros],
                  sMoveCount * sizeof( I_CHAR ) );
      else
         i_strcpy( _data.szBuffer, I_( "0" ) );
   }

   if( !_data.szBuffer[ 0 ] )
   {
      i_strcpy( _data.szBuffer, I_( "0" ) ) ;
   }

   return( *this );
}


/**
 * Strip all spaces from the internal representation
 * of Decimal.
 */
void Decimal::_stripSpaces()
{
   unsigned short sStringLen;
   unsigned short sIdx;
   unsigned short sNewIdx;

   if( !_data.szBuffer ||
       NULL == i_strchr( _data.szBuffer, I_( ' ' ) ) ) {
      return;
   }

   sStringLen = i_strlen( _data.szBuffer );

   for( sIdx = 0, sNewIdx = 0; sIdx <= sStringLen; ++sIdx )
   {
      if( I_( ' ' ) != _data.szBuffer[sIdx] ) 
      {
         if( sIdx != sNewIdx ) {
            _data.szBuffer[ sNewIdx ] = _data.szBuffer[ sIdx ];
         }
         ++sNewIdx;
      }
   }
}


/**
 * Sets up internal data structure, _P1, for later
 * math operations.
 * 
 * THROWS ConditionException - BASE_ALLOC_FAIL, if alloc fails.
 */
void Decimal::_studyNumbers( void )
{
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   _P1.fSign = ( i_strchr( _data.szBuffer, I_( '-' ) ) == NULL );
   I_CHAR c = GET_FRACT_SEPARATOR;
   _P1.fFloat = ( i_strchr( _data.szBuffer, GET_FRACT_SEPARATOR ) != NULL ); // See if has decimal pt

   sTemp = i_strlen( _data.szBuffer ) + 4;

   if( _P1.nBuffSize < sTemp )          // Need larger _P1 buffer?
   {
      if( _P1.nBuffSize )
         delete [] _P1.szWork;

      _P1.nBuffSize = sTemp;

      _P1.szWork = new I_CHAR[_P1.nBuffSize];
      if( !_P1.szWork )
      {
         _P1.nBuffSize = 0;
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::_studyNumbers( void )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, _P1.sIDig = 0;
      _data.szBuffer[sIdx1] && _data.szBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( myIsDigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szWork[_P1.sIDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szWork[_P1.sIDig] = 0;   // Null terminate integer section
   _P1.szFrac = &_P1.szWork[_P1.sIDig + 1];
   for( _P1.sFDig = 0; _data.szBuffer[sIdx1]; ++sIdx1 )
   {
      if( myIsDigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szFrac[_P1.sFDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szFrac[_P1.sFDig] = 0;  // Null terminate fractional section
}


/**
 * Takes two strings that represent numbers and
 * "normalizes" them.
 * 
 * - the first number
 * - the second number
 * - the first number "normalized"
 * - the second number "normalized"
 * 
 * THROWS ConditionException - BASE_ALLOC_FAIL, if alloc fails.
 * 
 * @param psz1
 * @param psz2
 * @param p1
 * @param p2
 */
void Decimal::_studyNumbers( const I_CHAR *psz1, 
                                const I_CHAR *psz2,
                                PARAMETER_INFO &p1, 
                                PARAMETER_INFO &p2 ) const
{
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   p1.fSign = ( i_strchr( psz1, I_( '-' ) ) == NULL );
   p2.fSign = ( i_strchr( psz2, I_( '-' ) ) == NULL );
   I_CHAR c = GET_FRACT_SEPARATOR;
   p1.fFloat = ( i_strchr( psz1, GET_FRACT_SEPARATOR ) != NULL ); // See if has decimal pt
   p2.fFloat = ( i_strchr( psz2, GET_FRACT_SEPARATOR ) != NULL );

   sTemp = i_strlen( psz1 ) + i_strlen( psz2 ) + 4;

   if( p1.nBuffSize < sTemp )          // Need larger p1 buffer?
   {
      if( p1.nBuffSize )
         delete [] p1.szWork;

      p1.nBuffSize = sTemp;

      p1.szWork = new I_CHAR[p1.nBuffSize];
      if( !p1.szWork )
      {
         p1.nBuffSize = 0;
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::_studyNumbers( const I_CHAR * " )
                        I_( "psz1, const I_CHAR *psz2, BUFFER &p1, " )
                        I_( "BUFFER &p2 ) const" ),
                        BASE_ALLOC_FAIL );
      }
   }

   if( p2.nBuffSize < sTemp )
   {
      if( p2.nBuffSize )
         delete [] p2.szWork;

      p2.nBuffSize = sTemp;

      p2.szWork = new I_CHAR[p2.nBuffSize];
      if( !p2.szWork )
      {
         p1.nBuffSize = 0;
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::_studyNumbers( const I_CHAR *" )
                        I_( " psz1, const I_CHAR *psz2, BUFFER &p1, " )
                        I_( "BUFFER &p2 ) const" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, p1.sIDig = 0;
      psz1[sIdx1] && psz1[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( myIsDigit( psz1[sIdx1] ) )
      {
         p1.szWork[p1.sIDig++] = psz1[sIdx1];
      }
   }
   p1.szWork[p1.sIDig] = 0;   // Null terminate integer section
   p1.szFrac = &p1.szWork[p1.sIDig + 1];
   for( p1.sFDig = 0; psz1[sIdx1]; ++sIdx1 )
   {
      if( myIsDigit( psz1[sIdx1] ) )
      {
         p1.szFrac[p1.sFDig++] = psz1[sIdx1];
      }
   }
   p1.szFrac[p1.sFDig] = 0;  // Null terminate fractional section

   for( sIdx1 = 0, p2.sIDig = 0;
      psz2[sIdx1] && psz2[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( myIsDigit( psz2[sIdx1] ) )
      {
         p2.szWork[p2.sIDig++] = psz2[sIdx1];
      }
   }
   p2.szWork[p2.sIDig] = 0;   // Null terminate integer section
   p2.szFrac = &p2.szWork[p2.sIDig + 1];
   for( p2.sFDig = 0; psz2[sIdx1]; ++sIdx1 )
   {
      if( myIsDigit( psz2[sIdx1] ) )
      {
         p2.szFrac[p2.sFDig++] = psz2[sIdx1];
      }
   }
   p2.szFrac[p2.sFDig] = 0;  // Null terminate fractional section
}


/**
 * Sets up _P1 and _P2 as "normalized" representations
 * of string numbers in preparation for math 
 * operations.
 * 
 * - the number represented in _P2.  The "this" 
 * _data.szBuffer will be represented by _P1.
 * 
 * THROWS ConditionException - BASE_ALLOC_FAIL, if alloc fails.
 * 
 * @param pcszBuffer
 */
void Decimal::_studyNumbers( const I_CHAR * pcszBuffer )
{
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   _P1.fSign = ( i_strchr( _data.szBuffer, I_( '-' ) ) == NULL );
   _P2.fSign = ( i_strchr( pcszBuffer, I_( '-' ) ) == NULL );
   I_CHAR c = GET_FRACT_SEPARATOR;
   _P1.fFloat = ( i_strchr( _data.szBuffer, GET_FRACT_SEPARATOR ) != NULL ); // See if has decimal pt
   _P2.fFloat = ( i_strchr( pcszBuffer, GET_FRACT_SEPARATOR ) != NULL );

   sTemp = i_strlen( _data.szBuffer ) + i_strlen( pcszBuffer ) + 4;

   if( _P1.nBuffSize < sTemp )          // Need larger _P1 buffer?
   {
      if( _P1.nBuffSize )
         delete [] _P1.szWork;

      _P1.nBuffSize = sTemp;

      _P1.szWork = new I_CHAR[_P1.nBuffSize];
      if( !_P1.szWork )
      {
         _P1.nBuffSize = 0;
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::_studyNumbers( const I_CHAR * " )
                        I_( "pcszBuffer )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   if( _P2.nBuffSize < sTemp )
   {
      if( _P2.nBuffSize )
         delete [] _P2.szWork;

      _P2.nBuffSize = sTemp;

      _P2.szWork = new I_CHAR[_P2.nBuffSize];
      if( !_P2.szWork )
      {
         _P1.nBuffSize = 0;
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::_studyNumbers( const I_CHAR * " )
                        I_( "pcszBuffer )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, _P1.sIDig = 0;
      _data.szBuffer[sIdx1] && _data.szBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( myIsDigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szWork[_P1.sIDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szWork[_P1.sIDig] = 0;   // Null terminate integer section
   _P1.szFrac = &_P1.szWork[_P1.sIDig + 1];
   for( _P1.sFDig = 0; _data.szBuffer[sIdx1]; ++sIdx1 )
   {
      if( myIsDigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szFrac[_P1.sFDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szFrac[_P1.sFDig] = 0;  // Null terminate fractional section

   for( sIdx1 = 0, _P2.sIDig = 0;
      pcszBuffer[sIdx1] && pcszBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( myIsDigit( pcszBuffer[sIdx1] ) )
      {
         _P2.szWork[_P2.sIDig++] = pcszBuffer[sIdx1];
      }
   }
   _P2.szWork[_P2.sIDig] = 0;   // Null terminate integer section
   _P2.szFrac = &_P2.szWork[_P2.sIDig + 1];
   for( _P2.sFDig = 0; pcszBuffer[sIdx1]; ++sIdx1 )
   {
      if( myIsDigit( pcszBuffer[sIdx1] ) )
      {
         _P2.szFrac[_P2.sFDig++] = pcszBuffer[sIdx1];
      }
   }
   _P2.szFrac[_P2.sFDig] = 0;  // Null terminate fractional section

}


void Decimal::_initInt( DIINT64 num )
{
   _init( ::asString( num ).c_str() );
}


void Decimal::_initUInt( unsigned DIINT64 num )
{
   _init( ::asString( num ).c_str() );
}


//CP20030905void Decimal::_initDouble( double num )
//CP20030905{
//CP20030905   _init( ::floatAsString( num ).c_str() );
//CP20030905}


void Decimal::_init( const I_CHAR * pszStringNum )
{
   int nStringLen;

   if( pszStringNum )
      nStringLen = i_strlen( pszStringNum );

   _sRsltLen = nStringLen  > uDefaultDataBuffSize ? nStringLen :
               uDefaultDataBuffSize;

   if( nStringLen )
   {
      _data.nBuffSize = nStringLen + 4;

      if( _data.nBuffSize < _sRsltLen )
         _data.nBuffSize = _sRsltLen;
      _data.szBuffer = new I_CHAR[_data.nBuffSize];

      if( !_data.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::Decimal( const I_CHAR * " )
                        I_( "pszStringNum )" ),
                        BASE_ALLOC_FAIL );
      }

      memcpy( _data.szBuffer, pszStringNum, ( nStringLen + 1 ) * sizeof( I_CHAR ) );
   }
   else
   {
      _data.nBuffSize = _sRsltLen;
      _data.szBuffer = new I_CHAR[_data.nBuffSize];
      if( !_data.szBuffer )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "Decimal::Decimal( const I_CHAR * " )
                        I_( "pszStringNum )" ),
                        BASE_ALLOC_FAIL );
      }
      i_strcpy( _data.szBuffer, I_( "0" ) );
   }

   _stripSpaces();
   _stripOffLeadingZeros();
   _studyNumbers();
}


void Decimal::_clearData( void )
{
   if( _data.szBuffer && _data.nBuffSize )
   {
      delete [] _data.szBuffer;
      _data.szBuffer = NULL;
      _data.nBuffSize = 0;
   }
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/decimal.cpp-arc  $
// 
//    Rev 1.1   Sep 10 2003 10:44:10   PURDYECH
// Change to a derivative of MathString
//
