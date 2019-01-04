
/* 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/**
 *   Class: MathString
 *  
 *
 *       Private Member Variables: 
 *
 *     PARAMETER_INFO _P1 - when an operation must be performed on two
 *     MathString objects, this contains a "normalized" form of the "this"
 *     MathString object.
 *     PARAMETER_INFO _P2 - when an operation must be performed on two
 *     MathString objects, this contains a "normalized" form of the second
 *     MathString object (passed to the "this" object as a parameter).
 *     PARAMETER_INFO _Rslt - when an operation must be performed on two
 *     MathString objects, this contains a "normalized" form of the result.
 *     BUFFER _data - contains the ASCIIZ string value of the MathString
 *     BUFFER _scratch1 - scratch buffer used in operators *,/, and % for
 *     holding partial quotients.
 *     BUFFER _scratch2 - scratch buffer used in operator* for holding parial
 *     quotients.
 *
 *  CODING COMMENTS  : Currently, this class is limited to 127 digits.  The
 *     temporary variables that cause this limit these could be removed, but
 *     do we really need a to work with numbers with more than 127 digits?
 *     127 digits can be a BIG number, or a ultra-high-precision number.
 *
 *     Whenever a mathmatical operation or comparison between two MathStrings
 *     is required, both numbers are "normalized".  First the numbers are placed
 *     into _parameter_info structures, then they are padded.  The smaller
 *     number is padded with 0's until it is the same size as the larger.
 *                      
 */

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#pragma warning( disable: 4018 )

#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif
#ifndef INCLUDED_STDLIB_H
#define INCLUDED_STDLIB_H
#include <stdlib.h>
#endif
#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif
#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H
#include <ctype.h>
#endif
#ifndef INCLUDED_MALLOC_H
#define INCLUDED_MALLOC_H
#include <malloc.h>
#endif
#ifndef INCLUDED_NEW_H
#define INCLUDED_NEW_H
#include <new.h>
#endif

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#ifndef MATHSTRING_HPP
   #include "mathstring.hpp"
#endif


const unsigned uDefaultDataBuffSize = 20;
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
MathString::MathString() :
_sRsltLen( uDefaultDataBuffSize ),
_data( _sRsltLen )
{
   TRACE_CONSTRUCTOR( I_( "MathString" ),
                      I_( "MathString()" ) )
}


// C String Constructor
MathString::MathString( const I_CHAR * pszStringNum )
{
   _init( pszStringNum );
}


MathString::MathString( I_CHAR * pszStringNum )
{
   _init( pszStringNum );
}


MathString::MathString( const DString * pszStringNum )
{
   _init( pszStringNum->c_str() );
}


MathString::MathString( DString * pszStringNum )
{
   _init( pszStringNum->c_str() );
}


MathString::MathString( const DString & pszStringNum )
{
   _init( pszStringNum.c_str() );
}


MathString::MathString( DString & pszStringNum )
{
   _init( pszStringNum.c_str() );
}


MathString::MathString( unsigned char num )
{
   _initUInt( num );
}


MathString::MathString( char num )
{
   _initInt( num );
}


MathString::MathString( unsigned short num )
{
   _initUInt( num );
}


MathString::MathString( short num )
{
   _initInt( num );
}


MathString::MathString( unsigned int num )
{
   _initUInt( num );
}


MathString::MathString( int num )
{
   _initInt( num );
}


MathString::MathString( unsigned long num )
{
   _initUInt( num );
}


MathString::MathString( long num )
{
   _initInt( num );
}


MathString::MathString( unsigned DIINT64 num )
{
   _initUInt( num );
}


MathString::MathString( DIINT64 num )
{
   _initInt( num );
}


MathString::MathString( float num )
{
   _initDouble( num );
}


MathString::MathString( double num )
{
   _initDouble( num );
}


// Copy Constructor
MathString::MathString( const MathString &copy ) :
_sRsltLen( copy._sRsltLen ),
_data( copy._data ),
_scratch1( copy._scratch1 ),
_scratch2( copy._scratch2 ),
_P1( copy._P1 ),
_P2( copy._P2 ),
_Rslt( copy._Rslt )
{
   TRACE_CONSTRUCTOR( I_( "MathString" ),
                      I_( "MathString( const MathString &copy )" ) )
}


// Destructor
MathString::~MathString()
{
   TRACE_DESTRUCTOR( I_( "MathString" ) )
   _heapmin();
}


const I_CHAR * MathString::c_str() const
{
   return(_data.szBuffer);
}


// Retrieves C String from MathString object
I_CHAR* MathString::getString( I_CHAR* pszString, int nBuffSize ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "getString( I_CHAR* pszString, int nBuffSize )" ) )
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
                        I_( "MathString::getString( I_CHAR* pszString, int " )
                        I_( "nBuffSize ) const" ),
                        DICORE_BUFFER_SIZE_TOO_SMALL,
                        szSize );
   }

   memcpy( pszString, _data.szBuffer, nReqdBuffSize * sizeof( I_CHAR ) );

   return( pszString );
}


// Returns absolute value of MathString object
MathString MathString::abs() const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "abs()" ) )
   MathString absString( *this );

   I_CHAR* pszSign = NULL;

   pszSign = i_strchr( absString._data.szBuffer, '-' );

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
MathString& MathString::operator=( const MathString &copy )
{
   TRACE_METHOD( I_( "MathString" ),  
                 I_( "operator=( const MathString &copy )" ) )

   _sRsltLen = copy._sRsltLen;

   _data = copy._data;
   _scratch1 = copy._scratch1;
   _scratch2 = copy._scratch2;
   _P1 = copy._P1;
   _P2 = copy._P2;

   return( *this );
}


// String Assignment
MathString& MathString::operator=( const I_CHAR * pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( const I_CHAR * pszStringNum )" ) )

   _clearData();
   _init( pszStringNum );

   return( *this );
}


MathString& MathString::operator=( I_CHAR * pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( I_CHAR * pszStringNum )" ) )

   _clearData();
   _init( pszStringNum );

   return( *this );
}


MathString& MathString::operator=( const DString * pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( const DString * pszStringNum )" ) )

   _clearData();
   _init( pszStringNum->c_str() );

   return( *this );
}


MathString& MathString::operator=( DString * pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( DString * pszStringNum )" ) )

   _clearData();
   _init( pszStringNum->c_str() );

   return( *this );
}


MathString& MathString::operator=( const DString & pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( const DString & pszStringNum )" ) )

   _clearData();
   _init( pszStringNum.c_str() );

   return( *this );
}


MathString& MathString::operator=( DString & pszStringNum )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( DString & pszStringNum )" ) )

   _clearData();
   _init( pszStringNum.c_str() );

   return( *this );
}


MathString& MathString::operator=( char num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( char num )" ) )

   _clearData();
   _initInt( num );

   return( *this );
}


MathString& MathString::operator=( unsigned char num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( unsigned char num )" ) )

   _clearData();
   _initUInt( num );

   return( *this );
}


MathString& MathString::operator=( short num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( short num )" ) )

   _clearData();
   _initInt( num );

   return( *this );
}


MathString& MathString::operator=( unsigned short num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( unsigned short num )" ) )

   _clearData();
   _initUInt( num );

   return( *this );
}


MathString& MathString::operator=( int num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( int num )" ) )

   _clearData();
   _initInt( num );

   return( *this );
}


MathString& MathString::operator=( unsigned int num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( unsigned int num )" ) )

   _clearData();
   _initUInt( num );

   return( *this );
}


MathString& MathString::operator=( long num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( long num )" ) )

   _clearData();
   _initInt( num );

   return( *this );
}


MathString& MathString::operator=( unsigned long num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( unsigned long num )" ) )

   _clearData();
   _initUInt( num );

   return( *this );
}


MathString& MathString::operator=( DIINT64 num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( DIINT64 num )" ) )

   _clearData();
   _initInt( num );

   return( *this );
}


MathString& MathString::operator=( unsigned DIINT64 num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( unsigned DIINT64 num )" ) )

   _clearData();
   _initUInt( num );

   return( *this );
}


MathString& MathString::operator=( float num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( float num )" ) )

   _clearData();
   _initDouble( num );

   return( *this );
}


MathString& MathString::operator=( double num )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator=( double num )" ) )

   _clearData();
   _initDouble( num );

   return( *this );
}


// Adds two MathString Objects and returns Sum
MathString MathString::operator+( const MathString& add2 )
{
   TRACE_METHOD( I_( "MathString" ), 
                 I_( "operator+( const MathString& add2 )" ) )
   I_CHAR  *szSwap;          // Used to swap strings for difference
   short sIdx1,            // Loop variable
   sIdx2;            // Loop variable
   short sTemp;
   bool fRsltFloat;
   bool fRsltSign;
   short sRsltIDig;
   short sRsltFDig;
   MathString resultString( ( MAX_RESULT_STRING_SIZE * 2 + 1 ) * sizeof( I_CHAR ) );
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
                        I_( "MathString::getString( I_CHAR* pszString, int " )
                        I_( "nBuffSize ) const" ),
                        DICORE_BUFFER_SIZE_TOO_SMALL,
                        asString( pszResultSize ).c_str() );
   pszResult = new I_CHAR [ pszResultSize ];

   if( !pszResult )
   {
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "MathString::operator+( const MathString& " )
                     I_( "add2 )" ),
                     BASE_ALLOC_FAIL );
   }


   // Make a string of 0's for padding
   int i;
   for( i = 0; i < sTemp; ++i )
   {
      resultString._data.szBuffer[ i ] = '0';
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
      return(MathString( I_( "0.0" ) ));
   }


   /***************************/
   /**  Assemble the result  **/
   /***************************/
   sIdx1 = 0;
   sIdx2 = 0;
   short sBytes = 0;

   if( ! fRsltSign )
      resultString._data.szBuffer[sIdx1++] = '-';

   if( pszResult[sIdx2] == '0' )
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


MathString MathString::operator/( const MathString& divString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator/( const MathString& divString )" ) )

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
                     I_( "MathString::operator/( const MathString& " )
                     I_( "divString )" ),
                     DICORE_DIVIDE_BY_ZERO )
   }

   if( this->isZero() )
   {                       // Zero / <n> = 0, just set and exit
      return( MathString( I_( "0" ) ) );
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
      _P1.szFrac[_P1.sFDig++] = '0';
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
                        I_( "MathString::operator/( const MathString& " )
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
                        I_( "MathString::operator/( const MathString& " )
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

   for( sIdx1 = 0; _P1.szWork[sIdx1] == '0'; ++sIdx1 )
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
   szPQuot[0] = '0';                // Always need 1 leading 0
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
            if( MathString::isZero( szPQuot ) )
               break;               // We're all done dividing

            szPQuot[sQuot++] = '0'; // Add a zero
         }
         szPQuot[sQuot] = 0;        // Keep null terminated

         // Compare numbers (keep result so can use twice)
         sTemp = _compareStrings( _P2.szWork, szPQuot );

         if( fLive && sTemp > 0 )  // Still not enough to get a digit
         {
            // If wouldn't be a leading 0
            szResult[sRslt++] = '0';   // Add a 0 to result
            _ASSERTE( sRslt < maxResultBufSize );
            szResult[sRslt] = 0;       // Keep null terminated
         }
      } while( sTemp > 0 );


      // Make divisor same length as PQuot
      if( sQuot < sP2Len )
      {
         memmove( &szPQuot[ sP2Len - sQuot ], szPQuot, ( sQuot + 1 ) * sizeof( I_CHAR ) );
         I_CHARset( szPQuot, '0', sP2Len - sQuot );
         sQuot += sP2Len - sQuot;
      }

      _ASSERTE( sQuot >= sP2Len );
      I_CHARset( _Rslt.szWork, '0', sQuot ); // Make divisor same length as PQuot
      i_strcpy( &_Rslt.szWork[sQuot - sP2Len], _P2.szWork );

      sTemp = '0';                  // Track subtractions
      while( _compareStrings( szPQuot, _P2.szWork ) >= 0 )
      {                             // While partial quotient >= divisor
         _diffStrings( szPQuot, _Rslt.szWork, szPQuot );
         ++sTemp;                   // Count reps
      }


      szResult[sRslt++] = (I_CHAR) sTemp;   // Save new digit
      _ASSERTE( sRslt < maxResultBufSize );
      szResult[sRslt] = 0;                // Keep null terminated
      fLive = true;                 // Result contains live chars

      while( szPQuot[1] == '0' )   // Strip off all but one leading zero
         i_strcpy( &szPQuot[1], &szPQuot[2] );
      sQuot = i_strlen( szPQuot );

      if( MathString::isZero( szPQuot ) && sIdx1 >= sP1Len )
         break;         // Zero quotient and used all digits of dividend

   } // end while still dividing

   return(MathString( szResult ));
}


MathString MathString::frac() const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "frac()" ) )
   I_CHAR *szFrac;

   MathString fracString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFrac = i_strchr( fracString._data.szBuffer, GET_FRACT_SEPARATOR ) ) != NULL )
   {
      return(MathString( szFrac ));
   }
   else
   {
      return(MathString( I_( "" ) ));
   }
}


MathString MathString::integer() const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "integer()" ) )
   I_CHAR *szFrac;

   MathString intString( *this );

   I_CHAR c = GET_FRACT_SEPARATOR;
   if( ( szFrac = i_strchr( intString._data.szBuffer,  GET_FRACT_SEPARATOR ) ) != NULL )
   {
      *szFrac = '\0';               // Chop off the fractional part
   }
   return( intString );
}


// Determines modulus of two MathString Objects
MathString MathString::operator%( const MathString& modString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator%( const MathString& modString )" ) )

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
                     I_( "MathString::operator%( const MathString& " )
                     I_( "modString )" ),
                     DICORE_DIVIDE_BY_ZERO );
   }

   if( isZero( _data.szBuffer ) )
   {                       // Zero % <n> = 0, just set and exit
      return( MathString( I_( "0" ) ) );
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
      return( MathString( I_( "0" ) ) );
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
      _P1.szFrac[_P1.sFDig++] = '0';
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
                        I_( "MathString::operator%( const MathString& " )
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
                        I_( "MathString::operator%( const MathString& " )
                        I_( "modString )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   sIdx1 = 0;                       // Reset for 'divide'
   szPQuot[0] = '0';                // Always need one leading zero
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
         I_CHARset( _Rslt.szWork, '0', sQuot ); // Make divisor same length as PQuot
         i_strcpy( &_Rslt.szWork[sQuot - sP2Len], _P2.szWork );

         while( _compareStrings( szPQuot, _P2.szWork ) >= 0 )
         {                             // While partial quotient >= divisor
            _diffStrings( szPQuot, _Rslt.szWork, szPQuot );
         }
      }

      while( szPQuot[1] == '0' )   // Strip off all but one leading zero
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
      szResult[sIdx2++] = '-';      // Add sign

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

      while( szResult[sIdx1] == '0' && szResult[sIdx1 - 1] != GET_FRACT_SEPARATOR )
      {                             // Allow <n>.0
         szResult[sIdx1--] = 0;     // Chop off trailing zero
      } // end while have trailing zeros
   }

   return(MathString( szResult ));
}       // operator %


MathString MathString::operator*( const MathString& multString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator*( const MathString& multString )" ) )

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
      return( MathString( I_( "0" ) ) );
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
                        I_( "MathString::operator*( const MathString& " )
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
                        I_( "MathString::operator*( const MathString& " )
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
                        I_( "MathString::operator*( const MathString& " )
                        I_( "multString )" ),
                        BASE_ALLOC_FAIL );
      }
   }
   szTemp = _scratch2.szBuffer;    // Associate szTemp with Scratch Buffer 2


   I_CHARset( _Rslt.szWork, '0', _sRsltLen );
   _Rslt.szWork[_sRsltLen] = 0;         // Null terminate
   sTemp = _P2.sIDig + _P2.sFDig;       // Length of _P2


   szPProd[_sRsltLen] = 0;         // Null terminate


   for( sIdx1 = sTemp - 1, sIdx2 = 1; sIdx1 >= 0; --sIdx1, ++sIdx2 )
   {                                // Work from right to left
      // Make 0 fill string for partial product
      I_CHARset( szPProd, '0', _sRsltLen );

      // By adjusting position of rightmost I_CHAR we add trailing 0's
      _multString( _P1.szWork, _P2.szWork[sIdx1], szPProd, _sRsltLen - sIdx2 );

      // Add partial product to result
      _addStrings( szPProd, _Rslt.szWork, szTemp );
      i_strcpy( _Rslt.szWork, szTemp );
   } // end for all digits in _P2


   /***************************/
   /**  Assemble the result  **/
   /***************************/

   if( _Rslt.szWork[0] == '0' )
   {
      for( sIdx1 = 0;
         sIdx1 < _Rslt.sIDig && _Rslt.szWork[sIdx1] == '0';
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
      szResult[sIdx2++] = '-';      // Add sign
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

      while( szResult[sIdx1] == '0' && szResult[sIdx1 - 1] != GET_FRACT_SEPARATOR )
      {                             // Allow <n>.0
         szResult[sIdx1--] = 0;     // Chop off trailing zero
      } // end while have trailing zeros
   }


   return(MathString( szResult ));
}    // operator*


MathString MathString::changeSign() const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "changeSign()" ) )
   if( i_strchr( _data.szBuffer, '-' ) )
   {
      // If number is negative, just take the absolute value
      return( this->abs() );
   }
   else
   {
      MathString negString( *this );

      negString._stripOffLeadingZeros();

      int nStringLen = i_strlen( negString._data.szBuffer );

      if( nStringLen == (negString._data.nBuffSize-1) )    // out of buffer space, reallocate
      {
         // Make copy with larger buffer and put in negative sign
         MathString tempCopy( negString._data.nBuffSize + 1 );
         tempCopy._data.szBuffer[0] = '-';
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
         negString._data.szBuffer[0] = '-';

         return( negString );
      }
   }
}


MathString MathString::round( short sRndAfter=0 ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "round( short sRndAfter=0 )" ) )
   I_CHAR  *szFPart;      // Fractional portion
   short sIdx;
   short sDig1;

   MathString roundString( *this );

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
            roundString._data.szBuffer[sIdx] = (I_CHAR) ( sDig1 % 10 ) + '0'; // Save rounded digit
            while( sDig1 > 9 && sIdx > 0 )
            {                 // While rounding works to left
               --sIdx;                                   // Move left one digit
               if( i_isdigit( roundString._data.szBuffer[sIdx] ) )
               {                             // Skip past '.'
                  sDig1 = ( roundString._data.szBuffer[sIdx] & 0x0F ) + 1;  // Round digit up
                  roundString._data.szBuffer[sIdx] = (I_CHAR) ( sDig1 % 10 ) + '0'; // Save
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


MathString MathString::trunc( short sTrncAfter=0 ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "trunc( short sTrncAfter=0 )" ) )
   I_CHAR  *szFPart;      // Fractional portion

   MathString truncString( *this );

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


// Determines whether MathString Object is equivalent to "0"
bool MathString::isZero() const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "isZero()" ) )
   short sIdx;

   for( sIdx = i_strlen( _data.szBuffer ); sIdx >= 0; --sIdx )
   {        // Working right to left gets strlen() once only
      if( _data.szBuffer[sIdx] >= '1' && _data.szBuffer[sIdx] <= '9' )
         return( false );        // String is not a zero
   }

   return( true );              // No '1' - '9' found, must be zero.
}


bool MathString::isZero( I_CHAR * pszString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "isZero( I_CHAR * pszString )" ) )
   short sIdx;

   for( sIdx = i_strlen( pszString ); sIdx >= 0; --sIdx )
   {
      // Working right to left gets strlen() once only
      if( pszString[sIdx] >= '1' && pszString[sIdx] <= '9' )
         return( false );
   }

   return( true );              // No '1' - '9' found, must be zero.

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
void MathString::_addStrings( const I_CHAR * szParam1,
                              const I_CHAR * szParam2,
                              I_CHAR * szResult )
{
//   TRACE_METHOD( "MathString", "_addStrings( const I_CHAR * szParam1, const I_CHAR"
//                    " * szParam2, I_CHAR * szResult )" )
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
      szResult[sIdx1] = (I_CHAR) ( ( sDig3 % 10 ) + '0' ); // save digit
      sCarry = sDig3 / 10;       // Get actual carry
   }
   szResult[sIdx1] = (I_CHAR) ( ( sCarry % 10 ) + '0' );
}



/**
 * Compares two MathString Objects
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
short MathString::_compareString( const MathString& cmpString ) const
{
//   TRACE_METHOD( "MathString", "_compareString( const MathString& cmpString )" )
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
                     I_( "MathString::_compareString( const MathString&" )
                     I_( " cmpString )" ),
                     BASE_ALLOC_FAIL );
   }

   if( p2.sIDig > p1.sIDig )
   {
      I_CHARset( psz1, '0', p2.sIDig - p1.sIDig );
      memcpy( psz1 + p2.sIDig - p1.sIDig, p1.szWork, p1.sIDig * sizeof( I_CHAR ) );
   }
   else
   {
      memcpy( psz1, p1.szWork, p1.sIDig * sizeof( I_CHAR ) );
   }

   memcpy( psz1 + iIntSize, p1.szFrac, p1.sFDig * sizeof( I_CHAR ) );
   if( p2.sFDig > p1.sFDig )
   {
      I_CHARset( psz1 + p1.sFDig + iIntSize, '0', p2.sFDig - p1.sFDig );
   }

   psz1[ iNewStringLen ] = 0;

   I_CHAR     *psz2 = new I_CHAR [ iNewStringLen + 1] ;
   if( !psz2 )
   {
      delete [] psz1;
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "MathString::_compareString( const MathString&" )
                     I_( " cmpString )" ),
                     BASE_ALLOC_FAIL );
   }

   if( p1.sIDig > p2.sIDig )
   {
      I_CHARset( psz2, '0', p1.sIDig - p2.sIDig );
      memcpy( psz2 + p1.sIDig - p2.sIDig, p2.szWork, p2.sIDig * sizeof( I_CHAR ) );
   }
   else
   {
      memcpy( psz2, p2.szWork, p2.sIDig * sizeof( I_CHAR ) );
   }

   memcpy( psz2 + iIntSize, p2.szFrac, p2.sFDig * sizeof( I_CHAR ) );
   if( p1.sFDig > p2.sFDig )
   {
      I_CHARset( psz2 + p2.sFDig + iIntSize, '0', p1.sFDig - p2.sFDig );
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
short MathString::_compareStrings( const I_CHAR * szParam1, 
                                   const I_CHAR * szParam2 ) const
{
//   TRACE_METHOD( "MathString", "_compareStrings( const I_CHAR * szParam1, "
//                    "const I_CHAR * szParam2 )" )
   bool  fDone;         // Loop flag
   short sP1Int,        // Offset of first live digit / length of number
   sP2Int;
   short sIdx1,         // String indexes
   sIdx2;


   for( sP1Int = 0; szParam1[ sP1Int ] == '0'; ++sP1Int )
      ;        // Find first live character

   for( sP2Int = 0; szParam2[ sP2Int ] == '0'; ++sP2Int )
      ;        // Find first live character

   sIdx1 = i_strlen( szParam1 ) - sP1Int;       // Get # of live digits
   sIdx2 = i_strlen( szParam2 ) - sP2Int;
   if( sIdx1 != sIdx2 )
   {                 // One has more live digits, must be !=
      if( sIdx1 > sIdx2 )
         return( 1 );      // _P1 > _P2
      else
         return( -1 );     // _P1 < _P2
   }

   sIdx1 = sP1Int;   // Start with first live I_CHAR
   sIdx2 = sP2Int;
   sP1Int = i_strlen( szParam1 );
   sP2Int = i_strlen( szParam2 );

   fDone = false;
   while( !fDone )
   {
      if( szParam1[sIdx1] != szParam2[sIdx2] )
      {
         if( szParam1[sIdx1] > szParam2[sIdx2] )
            return( 1 );        // _P1 > _P2
         else
            return( -1 );       // _P1 < _P2
      }
      ++sIdx1;                   // advance to next digit
      ++sIdx2;

      if( sIdx1 == sP1Int || sIdx2 == sP2Int )
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
void MathString::_diffStrings( const I_CHAR * szParam1,
                               const I_CHAR * szParam2,
                               I_CHAR * szResult )
{
//   TRACE_METHOD( "MathString", "_diffStrings( const I_CHAR * szParam1, const I_CHAR"
//                    " * szParam2, I_CHAR * szResult )" )
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
   {  // Work digits from right to left
      sDig1 = ( szParam1[sIdx1] & 0x0F );
      sDig2 = ( szParam2[sIdx1] & 0x0F );
      sDig1 -= sCarry;        // Perform any required 'borrow'
      if( sDig1 < sDig2 )
      {
         sDig1 += 10;         // Set up 'borrow'
         sDig3 = sDig1 - sDig2;
         sCarry = 1;          // Flag 'borrow' from next digit
      }
      else
      {
         sDig3 = sDig1 - sDig2;
         sCarry = 0;          // Done 'borrowing'
      }
      szResult[sIdx1] = (I_CHAR) ( sDig3 + '0' ); // save result digit
   }
   szResult[sIdx1] = (I_CHAR) ( ( sCarry % 10 ) + '0' );
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
void MathString::_multString( const I_CHAR * szParam1,
                              I_CHAR   chParam2,
                              I_CHAR * szResult,
                              short  sStartOffs )
{
//   TRACE_METHOD( "MathString", "_multString( const I_CHAR * szParam1, I_CHAR "
//                    "chParam2, I_CHAR * szResult, short  sStartOffs )" )
   short sDig1,            // Digit from _P1
   sDig2,            // Digit from _P2
   sDig3;            // Digit for result
   short sCarry;           // Current carry
   short sIdx1;            // Loop variable
   short sTemp;

   sCarry = 0;                   // Clear the carry
   sDig1  = chParam2 - '0';      // Convert to binary
   sTemp = i_strlen( szParam1 );   // Length of result

   for( sIdx1 = ( sTemp - 1 ); sIdx1 >= 0; --sIdx1 )
   {  // Work digits from right to left
      sDig2 = ( szParam1[sIdx1] & 0x0F );
      sDig3 = asDigitProducts[sDig1][sDig2]; // Product of digits
      sDig3 += sCarry;           // Add in carry from previous digits
      sCarry = sDig3 / 10;       // Carry to next digit

      szResult[sStartOffs--] = (I_CHAR) ( ( sDig3 % 10 )+ '0' );
   }
   szResult[sStartOffs] = (I_CHAR) ( ( sCarry % 10 ) + '0' );
}


/**
 * Strips the leading zeros and spaces from the string
 * used to create the MathString.
 * 
 * @return 
 */
MathString& MathString::_stripOffLeadingZeros()
{
//   TRACE_METHOD( "MathString", "_stripOffLeadingZeros()" )
   bool  fLeadingSign = false;
   short sStringLen = 0;
   short sIdx = 0;
   short sLeadingZeros = 0;
   short sMoveCount = 0;

   sStringLen = i_strlen( _data.szBuffer );

   if( ( '+' == _data.szBuffer[0] ) || ( '-' == _data.szBuffer[0] ) )
   {
      fLeadingSign = true;
      sIdx = 1;
   }

   for( int i = sIdx; i < sStringLen; i++ )
   {
      if( ( '0' == _data.szBuffer[i] ) || ( ' ' == _data.szBuffer[i] ) )
         sLeadingZeros++;
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
 * of Mathstring.
 */
void MathString::_stripSpaces()
{
   TRACE_METHOD( I_( "MathString" ), 
                 I_( "_stripSpaces()" ) )
   short sStringLen;
   short sIdx;
   short sNewIdx;

   if( !_data.szBuffer )
      return;

   sStringLen = i_strlen( _data.szBuffer );

   for( sIdx = 0, sNewIdx = 0; sIdx <= sStringLen; sIdx++ )
   {
      if( ' ' != _data.szBuffer[ sIdx ] )
      {
         _data.szBuffer[ sNewIdx ] = _data.szBuffer[ sIdx ];
         sNewIdx++;
      }
   }
}


/**
 * Sets up internal data structure, _P1, for later
 * math operations.
 * 
 * THROWS ConditionException - BASE_ALLOC_FAIL, if alloc fails.
 */
void MathString::_studyNumbers( void )
{
//   TRACE_METHOD( "MathString", "_studyNumbers( void )" )
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   _P1.fSign = ( i_strchr( _data.szBuffer, '-' ) == NULL );
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
                        I_( "MathString::_studyNumbers( void )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, _P1.sIDig = 0;
      _data.szBuffer[sIdx1] && _data.szBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( i_isdigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szWork[_P1.sIDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szWork[_P1.sIDig] = 0;   // Null terminate integer section
   _P1.szFrac = &_P1.szWork[_P1.sIDig + 1];
   for( _P1.sFDig = 0; _data.szBuffer[sIdx1]; ++sIdx1 )
   {
      if( i_isdigit( _data.szBuffer[sIdx1] ) )
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
void MathString::_studyNumbers( const I_CHAR *psz1, 
                                const I_CHAR *psz2,
                                PARAMETER_INFO &p1, 
                                PARAMETER_INFO &p2 ) const
{
//   TRACE_METHOD( "MathString", "_studyNumbers( const I_CHAR *psz1, const I_CHAR"
//                    " *psz2, PARAMETER_INFO &p1, PARAMETER_INFO &p2 )" )
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   p1.fSign = ( i_strchr( psz1, '-' ) == NULL );
   p2.fSign = ( i_strchr( psz2, '-' ) == NULL );
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
                        I_( "MathString::_studyNumbers( const I_CHAR * " )
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
                        I_( "MathString::_studyNumbers( const I_CHAR *" )
                        I_( " psz1, const I_CHAR *psz2, BUFFER &p1, " )
                        I_( "BUFFER &p2 ) const" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, p1.sIDig = 0;
      psz1[sIdx1] && psz1[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( i_isdigit( psz1[sIdx1] ) )
      {
         p1.szWork[p1.sIDig++] = psz1[sIdx1];
      }
   }
   p1.szWork[p1.sIDig] = 0;   // Null terminate integer section
   p1.szFrac = &p1.szWork[p1.sIDig + 1];
   for( p1.sFDig = 0; psz1[sIdx1]; ++sIdx1 )
   {
      if( i_isdigit( psz1[sIdx1] ) )
      {
         p1.szFrac[p1.sFDig++] = psz1[sIdx1];
      }
   }
   p1.szFrac[p1.sFDig] = 0;  // Null terminate fractional section

   for( sIdx1 = 0, p2.sIDig = 0;
      psz2[sIdx1] && psz2[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( i_isdigit( psz2[sIdx1] ) )
      {
         p2.szWork[p2.sIDig++] = psz2[sIdx1];
      }
   }
   p2.szWork[p2.sIDig] = 0;   // Null terminate integer section
   p2.szFrac = &p2.szWork[p2.sIDig + 1];
   for( p2.sFDig = 0; psz2[sIdx1]; ++sIdx1 )
   {
      if( i_isdigit( psz2[sIdx1] ) )
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
void MathString::_studyNumbers( const I_CHAR * pcszBuffer )
{
//   TRACE_METHOD( "MathString", "_studyNumbers( const I_CHAR * pcszBuffer )" )
   short    sTemp;                  // Temp int
   short    sIdx1;                  // Loop var


   /*************************/
   /**  Study the numbers  **/
   /*************************/
   _P1.fSign = ( i_strchr( _data.szBuffer, '-' ) == NULL );
   _P2.fSign = ( i_strchr( pcszBuffer, '-' ) == NULL );
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
                        I_( "MathString::_studyNumbers( const I_CHAR * " )
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
                        I_( "MathString::_studyNumbers( const I_CHAR * " )
                        I_( "pcszBuffer )" ),
                        BASE_ALLOC_FAIL );
      }
   }

   for( sIdx1 = 0, _P1.sIDig = 0;
      _data.szBuffer[sIdx1] && _data.szBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( i_isdigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szWork[_P1.sIDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szWork[_P1.sIDig] = 0;   // Null terminate integer section
   _P1.szFrac = &_P1.szWork[_P1.sIDig + 1];
   for( _P1.sFDig = 0; _data.szBuffer[sIdx1]; ++sIdx1 )
   {
      if( i_isdigit( _data.szBuffer[sIdx1] ) )
      {
         _P1.szFrac[_P1.sFDig++] = _data.szBuffer[sIdx1];
      }
   }
   _P1.szFrac[_P1.sFDig] = 0;  // Null terminate fractional section

   for( sIdx1 = 0, _P2.sIDig = 0;
      pcszBuffer[sIdx1] && pcszBuffer[sIdx1] != GET_FRACT_SEPARATOR;
      ++sIdx1 )
   {
      if( i_isdigit( pcszBuffer[sIdx1] ) )
      {
         _P2.szWork[_P2.sIDig++] = pcszBuffer[sIdx1];
      }
   }
   _P2.szWork[_P2.sIDig] = 0;   // Null terminate integer section
   _P2.szFrac = &_P2.szWork[_P2.sIDig + 1];
   for( _P2.sFDig = 0; pcszBuffer[sIdx1]; ++sIdx1 )
   {
      if( i_isdigit( pcszBuffer[sIdx1] ) )
      {
         _P2.szFrac[_P2.sFDig++] = pcszBuffer[sIdx1];
      }
   }
   _P2.szFrac[_P2.sFDig] = 0;  // Null terminate fractional section

}


void MathString::_initInt( DIINT64 num )
{
   _init( ::asString( num ).c_str() );
}


void MathString::_initUInt( unsigned DIINT64 num )
{
   _init( ::asString( num ).c_str() );
}


void MathString::_initDouble( double num )
{
   _init( ::floatAsString( num ).c_str() );
}


void MathString::_init( const I_CHAR * pszStringNum )
{
   TRACE_CONSTRUCTOR( I_( "MathString" ), 
                      I_( "MathString( const I_CHAR * pszStringNum )" ) )
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
                        I_( "MathString::MathString( const I_CHAR * " )
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
                        I_( "MathString::MathString( const I_CHAR * " )
                        I_( "pszStringNum )" ),
                        BASE_ALLOC_FAIL );
      }
      i_strcpy( _data.szBuffer, I_( "0" ) );
   }

   _stripSpaces();
   _stripOffLeadingZeros();
   _studyNumbers();
}


void MathString::_clearData( void )
{
   if( _data.szBuffer && _data.nBuffSize )
   {
      delete [] _data.szBuffer;
      _data.szBuffer = NULL;
      _data.nBuffSize = 0;
   }
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/mathstring.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 09:03:54   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:42:08   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:22   SMITHDAV
// Initial revision.
// 
//    Rev 1.11   21 Mar 2001 13:15:34   DT14177
// fixed operator/ buffer overflow
// 
//    Rev 1.10   Aug 23 2000 10:42:02   DT14177
// quotient too large (x10) when dividend < 0.1
// 
//    Rev 1.9   Jul 10 2000 09:59:08   dtwk
// Some memory was not being initialized correctly in release mode
// 
//    Rev 1.8   Jun 26 2000 17:09:14   DT14177
// added constructors and assignment operators to MathString
// 
//    Rev 1.7   Feb 10 2000 09:50:10   DT14177
// Fixed a rounding bug
// 
//    Rev 1.6   Jan 03 2000 16:57:46   DT14177
// added javadoc comments
// 
//    Rev 1.5   26 Feb 1999 15:06:04   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.4   25 Feb 1999 14:05:12   DT14177
// Changed IDI string substitution macros to end in IDI.
// 
//    Rev 1.3   24 Feb 1999 10:44:24   DT14177
// sync up with tracer
// 
//    Rev 1.2   18 Feb 1999 10:38:20   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:03:06   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:24   DMUM
//  
// 
//    Rev 1.1   Aug 19 1998 16:14:40   DTWK
// Fix problem where "0" * "100" would return "" instead of "0".
//
//    Rev 1.0   29 Jul 1998 20:32:16   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.7   Jul 02 1998 11:36:46   DTWK
// Change c_str() to be a const method
//
//    Rev 1.6   Nov 09 1997 15:35:56   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.5   Jul 24 1997 08:51:28   DTWK
// Add tracing, c_str(), fix operator/ memory overwrites.
//
//    Rev 1.3   Jul 07 1997 15:20:54   DTWK
// Numerous fixes for DSSD.
//
//    Rev 1.2   Jun 16 1997 15:32:02   DTWK
// Add support for Condition class.
//
//    Rev 1.1   Jun 11 1997 16:08:10   DTWK
// Update with more recent version from DPQD
//
//


