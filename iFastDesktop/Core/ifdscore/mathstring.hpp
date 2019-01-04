#pragma once

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

/**@pkg DICORE */

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif
#ifndef COMMONPORT_H
   #include <commonport.h>
#endif
#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif
#ifndef TRACERCLIENT_HPP
   #include <tracerclient.hpp>
#endif
#ifndef BASE_H
   #include <base.h>
#endif
#ifndef DICORE_H
   #include <dicore.h>
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * The MathString class is a C++ version of ASCII Math, a C
 * library for string-based math developed by Steve Van Dyke for
 * use in IWS.  It is a class that supports high precision
 * floating point math.
 *
 * Currently, this class is limited to 127 digits.  The
 * temporary variables that cause this limit could be removed,
 * but do we really need a to work with numbers with more than
 * 127 digits? 127 digits can be a _BIG_ integer, or an ultra-
 * high-precision decimal, or both.
 *
 * The MathString class has been tested on both Windows NT 3.51
 * and OS/2 Warp. The class should be easily portable to other
 * platforms (even EBCDIC) since the '0' through '9'
 * representations are contiguous in most collating sequences.
 */

class DICORE_LINKAGE MathString
{
public:
   /**
    * Default constructor
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    */
   MathString();

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   MathString( I_CHAR * pszStringNum );

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   MathString( const I_CHAR * pszStringNum );

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   explicit MathString( const DString & pszStringNum );

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   explicit MathString( DString & pszStringNum );

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   explicit MathString( const DString * pszStringNum );

   /**
    * Constructor.  The string that this accepts should be of the
    * form: "123.456" or "-123.456".  Leading 0's and all spaces
    * will be stripped from the string.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszStringNum - a string representation of a number
    *
    */
   explicit MathString( DString * pszStringNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( int pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( unsigned int pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( long pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( unsigned long pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( short pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( unsigned short pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( char pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( unsigned char pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( DIINT64 pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( unsigned DIINT64 pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( float pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit MathString( double pszNum );

   /**
    * Copy constructor
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param copy
    *
    */
   MathString( const MathString &copy );

   /**
    * destructor
    */
   ~MathString();

   /**
    * Get a char pointer to the string.  This method is
    * useful for filling string objects.
    * 
    * 
    * @return  - a pointer to the string's internal
    *         data buffer.
    *
    */
   const I_CHAR * c_str() const;

   /**
    * Retrieves C String from MathString object
    * 
    *    ^^ConditionException - DICORE_BUFFER_SIZE_TOO_SMALL, if the output buffer
    *       is too small.
    * 
    * 
    * @param - Output buffer.  This should be at least stringLength() + 1
    *        bytes long.
    * @param  -  Output buffer size.
    * @return - The output buffer.
    *
    */
   I_CHAR* getString( I_CHAR * string, int size ) const;

   /**
    * Get the length of the internal string.
    * 
    * @return - the length of the string
    */
   unsigned stringLength( void ) const;



   // Standard Math Operators


   /**
    * Adds two MathString Objects and returns Sum.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   MathString operator+( const MathString& parm );

   /**
    * Subtracts two MathString Objects and returns Difference
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   MathString operator-( const MathString& parm );

   /**
    * Multiply two MathString Objects and returns result
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * @param parm
    * @return - the result
    *
    */
   MathString operator*( const MathString& parm );

   /**
    * Divide two MathString Objects and return result
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   MathString operator/( const MathString& parm );

   /**
    * Modulus
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   MathString operator%( const MathString& parm );


   // Standard Math Operation with Assignment Operators


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString& -
    * @return MathString& - the result
    *
    */
   const MathString& operator+=( const MathString& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString& -
    * @return MathString& - the result
    *
    */
   const MathString& operator-=( const MathString& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString& -
    * @return MathString& - the result
    *
    */
   const MathString& operator*=( const MathString& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param ^^ const MathString& -
    * @return MathString& - the result
    *
    */
   const MathString& operator/=( const MathString& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param ^^ const MathString& -
    * @return MathString& - the result
    *
    */
   const MathString& operator%=( const MathString& parm );

   // Prefix Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString& - the result
    *
    */
   MathString& operator++( void );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString& - the result
    *
    */
   MathString& operator--( void );


   // Postfix Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ int nDummy -
    * @return MathString - the result
    *
    */
   MathString operator++( int nDummy );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ int nDummy
    * @return MathString - the result
    *
    */
   MathString operator--( int nDummy );


   // Assignment Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &copy
    * @return MathString& - the result
    *
    */
   MathString& operator=( const MathString &copy );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( const I_CHAR * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( I_CHAR * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( const DString * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( DString * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( const DString & pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return MathString& - the result
    *
    */
   MathString& operator=( DString & pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( char num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( unsigned char num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( short num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( unsigned short num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( int num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( unsigned int num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( long num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( unsigned long num );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( DIINT64 num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return MathString& - the result
    *
    */
   MathString& operator=( unsigned DIINT64 num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( float num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return MathString& - the result
    *
    */
   MathString& operator=( double num );


   // Derivation Methods

   /**
    * Get the fractional amount of a MathString
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString - the result. "" if there is no fraction.
    *
    */
   MathString frac( void )    const;

   /**
    * Get the number without the integer.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString - the result.
    *
    */
   MathString integer( void ) const;

   /**
    * Round the string after the decimal place.  If the decimal
    * place parameter is greater than
    * the number of decimal places in the string, then the string
    * will remain unchanged.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    *  ^EXAMPLE     :
    *     Round a dollar amount to the nearest penny:
    *        MathString        m1( "1000.50523" );
    *        m1.round( 2 );  // Result is "1000.51"
    * 
    * @param ^^ short - The number of decimal places to keep.
    * @return MathString - the result
    *
    */
   MathString round( short numPlaces )  const;

   /**
    * Truncate the string after the decimal point.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ short - The number of decimal places to keep.
    * @return MathString - the result
    *
    */
   MathString trunc( short numPlaces )  const;

   /**
    * Absolute value
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString - the result
    *
    */
   MathString abs( void )     const;

   /**
    * Flip the sign of a number.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return MathString - the result
    *
    */
   MathString changeSign( void )  const;


   // Test Methods

   /**
    * Test the number to see if it is nonnegative.
    * 
    * 
    * @param ^^ void -
    * @return bool - true if number is >= 0, false otherwise
    *
    */
   bool isPlus( void )  const;

   /**
    * Test the number to see if it < 0.
    * 
    * 
    * @param ^^ void -
    * @return bool - true if number is < 0, false otherwise.
    *
    */
   bool isMinus( void ) const;

   /**
    * Determines whether the MathString Object is equivalent to "0"
    * 
    * 
    * @param ^^ void -
    * @return bool - true if equivalent to 0, false otherwise
    *
    */
   bool isZero( void )  const;

   /**
    * Determines whether the string is equivalent to "0"
    * 
    * 
    * @param ^^ char * pszString -
    * @return bool - true if equivalent to 0, false otherwise
    *
    */
   static bool isZero( I_CHAR * pszString );


   // Comparison Operators

   /**
    * Check two MathStrings to see if they are the same
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool - true if they are equivalent, false otherwise.
    *
    */
   bool operator==( const MathString &compare ) const;

   /**
    * Check two MathStrings to see if they are different
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool - true if they are not equivalent, false otherwise.
    *
    */
   bool operator!=( const MathString &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool -
    *
    */
   bool operator<=( const MathString &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool -
    *
    */
   bool operator< ( const MathString &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool -
    *
    */
   bool operator>=( const MathString &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return bool -
    *
    */
   bool operator> ( const MathString &compare ) const;


   // Comparison Methods

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return const MathString& -
    *
    */
   const MathString& maximum( const MathString &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const MathString &compare -
    * @return const MathString& -
    *
    */
   const MathString& minimum( const MathString &compare ) const;




private:

   void _addStrings( const I_CHAR * szParam1,
                     const I_CHAR * szParam2,
                     I_CHAR * szResult );

   short _compareString( const MathString& ) const;
   short _compareStrings( const I_CHAR * szParam1,
                          const I_CHAR * szParam2 ) const;

   void _diffStrings( const I_CHAR * szParam1,
                      const I_CHAR * szParam2,
                      I_CHAR * szResult );

   void _init( const I_CHAR * );

   void _initInt( DIINT64 );

   void _initUInt( unsigned DIINT64 );

   void _initDouble( double );

   void _multString( const I_CHAR * szParam1,
                     I_CHAR   chParam2,
                     I_CHAR * szResult,
                     short  sStartOffs );

   void _studyNumbers( void );
   void _studyNumbers( const I_CHAR * );

   MathString& _stripOffLeadingZeros( void );
   void _stripSpaces( void );
   void _clearData( void );


private:
   short    _sRsltLen;


   //************************************************************************
   //
   // ^CLASS    : _parameter_info
   //
   // ^CLASS DESCRIPTION : A "normalized" representation of a string number.
   //
   // ^EXAMPLE : A string "123.45" would be represented by
   //    szWork - "123\n45\n"
   //    szFrac - "45\n" - note that szFrac actually points into szWork,
   //       after the first "\n".  szFrac does not allocate any storage,
   //       but just points into szWork's allocated storage.
   //    sIDig - 3
   //    sFDig - 2
   //    fFloat - true
   //    fSign - true
   //
   //************************************************************************
   struct _parameter_info
   {
      unsigned nBuffSize;              // size of szWork buffer
      I_CHAR     *szWork;                // Work std::string
      I_CHAR     *szFrac;                // Fractional portion
      short    sIDig;                  // # of integer digits
      short    sFDig;                  // # of fraction digits
      bool     fFloat;                 // Float value flag
      bool     fSign;                  // Sign flag (false == '-')

      _parameter_info() :
      nBuffSize( 0 ),
      szWork( NULL ),
      szFrac( NULL ),
      sIDig( 0 ),
      sFDig( 0 )
      {
      }

      _parameter_info( const _parameter_info& copy ) :
      nBuffSize( copy.nBuffSize ),
      szWork( NULL ),
      szFrac( NULL ),
      sIDig( copy.sIDig ),
      sFDig( copy.sFDig )
      {
         if( copy.szWork )
         {
            szWork = new I_CHAR[ nBuffSize ];
            if( !szWork )
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_( "_parameter_info( const " )
                              I_( "_parameter_info& copy )" ),
                              BASE_ALLOC_FAIL )
            }
            i_strcpy( szWork, copy.szWork );

            if( copy.szFrac )
               szFrac = szWork + ( copy.szFrac - copy.szWork );
         }
      }


      ~_parameter_info()
      {
         if( szWork )
            delete [] szWork;
      }


      _parameter_info& operator=( const _parameter_info& copy )
      {
         if( &copy == this )
            return(*this);

         sIDig = copy.sIDig;
         sFDig = copy.sFDig;

         if( nBuffSize < copy.nBuffSize )
         {
            delete [] szWork;
            nBuffSize = copy.nBuffSize;
            szWork = new I_CHAR[nBuffSize];
            if( !szWork )
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_( "_parameter_info& operator=( " )
                              I_( "const _parameter_info& copy )" ),
                              BASE_ALLOC_FAIL )
            }
         }

         if( copy.szWork )
         {
            i_strcpy( szWork, copy.szWork );

            if( copy.szFrac )
               szFrac = szWork + ( copy.szFrac - copy.szWork );
         }

         return(*this);
      }
   };

   //************************************************************************
   //
   // ^CLASS    : _buffer
   //
   // ^CLASS DESCRIPTION : A simple buffer class used to make dynamic
   //    memory allocations a bit cleaner.
   //
   //************************************************************************
   struct _buffer
   {
      I_CHAR     * szBuffer;
      unsigned   nBuffSize;


      struct _buffer() :
      szBuffer( NULL ),
      nBuffSize( 0 )
      {
      }


      _buffer( const _buffer& copy ) :
      nBuffSize( copy.nBuffSize ),
      szBuffer( NULL )
      {
         if( copy.szBuffer )
         {
            szBuffer = new I_CHAR[ nBuffSize ];
            if( !szBuffer )
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_( "_buffer( const _buffer& copy )" ),
                              BASE_ALLOC_FAIL )
            }
            i_strcpy( szBuffer, copy.szBuffer );
         }
      }


      _buffer( unsigned buffSize ) :
      szBuffer( NULL ),
      nBuffSize( buffSize )
      {
         szBuffer = new I_CHAR[ nBuffSize ];
         if( !szBuffer )
         {
            THROWFROMBASE( DICORE_CONDITION,
                           I_( "_buffer( unsigned buffSize )" ),
                           BASE_ALLOC_FAIL );
         }
         i_strcpy( szBuffer, I_( "0" ) );
      }


      ~_buffer()
      {
         if( szBuffer )
            delete [] szBuffer;
      }


      _buffer& operator=( const _buffer& copy )
      {
         if( &copy == this )
            return(*this);

         if( nBuffSize < copy.nBuffSize )
         {
            delete [] szBuffer;
            nBuffSize = copy.nBuffSize;
            szBuffer = new I_CHAR[nBuffSize];
            if( !szBuffer )
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_( "_buffer& operator=( const " )
                              I_( "_buffer& copy )" ),
                              BASE_ALLOC_FAIL );
            }
         }

         if( copy.szBuffer )
            i_strcpy( szBuffer, copy.szBuffer );

         return(*this);
      }
   };

   typedef struct _parameter_info PARAMETER_INFO;
   typedef struct _buffer BUFFER;

   void _studyNumbers( const I_CHAR *psz1, const I_CHAR *psz2,
                       PARAMETER_INFO &p1, PARAMETER_INFO &p2 ) const;

   PARAMETER_INFO _P1, _P2, _Rslt;      // Parameter info blocks
   BUFFER _data, _scratch1, _scratch2;

};



inline unsigned MathString::stringLength( void ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "stringLength( void )" ) )
   if( ! _data.szBuffer )
      return(0);
   else
      return(i_strlen( _data.szBuffer ));
}


inline bool MathString::isMinus( void ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "isMinus( void )" ) )
   return( i_strchr( _data.szBuffer, '-' ) != NULL ? true : false );
}


inline bool MathString::isPlus( void ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "isPlus( void )" ) )
   return( i_strchr( _data.szBuffer, '-' ) != NULL ? false : true );
}


inline const MathString& MathString::maximum( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "maximum( const MathString &compare )" ) )
   return( _compareString( compare ) < 0 ? compare : *this );
}


inline const MathString& MathString::minimum( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "minimum( const MathString &compare )" ) )
   return( _compareString( compare ) > 0 ? compare : *this );
}


inline bool MathString::operator==( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator==( const MathString &compare )" ) )
   return( _compareString( compare ) == 0 ? true : false );
}


inline bool MathString::operator!=( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator!=( const MathString &compare )" ) )
   return( _compareString( compare ) != 0 ? true : false );
}


inline bool MathString::operator<=( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator<=( const MathString &compare )" ) )
   return( _compareString( compare ) > 0 ? false : true );
}


inline bool MathString::operator<( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator<( const MathString &compare )" ) )
   return( _compareString( compare ) < 0 ? true : false );
}


inline bool MathString::operator>=( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator>=( const MathString &compare )" ) )
   return( _compareString( compare ) < 0 ? false : true );
}


inline bool MathString::operator>( const MathString &compare ) const
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator>( const MathString &compare )" ) )
   return( _compareString( compare ) > 0 ? true : false );
}


// Subtracts two MathString Objects and returns Difference
inline MathString MathString::operator-( const MathString &subString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator-( const MathString &subString )" ) )
   return( *this + subString.changeSign() );    // Return result from Add
}     // operator-


inline const MathString& MathString::operator+=( const MathString &addString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator+=( const MathString &addString )" ) )
   MathString that( *this );
   return( *this = ( that + addString ) );
}


inline const MathString& MathString::operator-=( const MathString &subString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator-=( const MathString &subString )" ) )
   MathString that( *this );
   return( *this = ( that - subString ) );
}


inline const MathString& MathString::operator*=( const MathString &multString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator*=( const MathString &multString )" ) )
   MathString that( *this );
   return( *this = ( that * multString ) );
}


inline const MathString& MathString::operator/=( const MathString &divString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator/=( const MathString &divString )" ) )
   MathString that( *this );
   return( *this = ( that / divString ) );
}


inline const MathString& MathString::operator%=( const MathString &modString )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator%=( const MathString &modString )" ) )
   MathString that( *this );
   return( *this = ( that % modString ) );
}


// Prefix increment operator
inline MathString& MathString::operator++()
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator++()" ) )
   MathString oneString( I_( "1" ) );
   *this += oneString;
   return( *this );
}


// Postfix increment operator
inline MathString MathString::operator++( int nDummy )
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator++( int nDummy )" ) )
   MathString tempString( *this );
   MathString oneString( I_( "1" ) );

   *this += oneString;
   return(tempString);
}


// Prefix decrement operator
inline MathString& MathString::operator--()
{
   TRACE_METHOD( I_( "MathString" ),
                 I_( "operator--()" ) )
   MathString oneString( I_( "1" ) );
   return( *this = ( *this - oneString ) );
}


// Postfix decrement operator
inline MathString MathString::operator--( int nDummy )
{
   TRACE_METHOD( I_( "MathString" ), 
                 I_( "operator--( int nDummy )" ) )
   MathString tempString( *this );
   MathString oneString( I_( "1" ) );

   *this -= oneString;
   return( tempString );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/mathstring.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:10   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:00   SMITHDAV
//Initial revision.
// 
//    Rev 1.9   27 Oct 2000 15:30:22   dt14177
// cleanup
// 
//    Rev 1.8   Jun 30 2000 11:09:02   DT14177
// removed "explicit" from the  I_CHAR * constructors
// 
//    Rev 1.7   Jun 26 2000 17:09:24   DT14177
// added constructors and assignment operators to MathString
// 
//    Rev 1.6   Jan 03 2000 16:57:48   DT14177
// added javadoc comments
// 
//    Rev 1.5   26 Feb 1999 15:06:22   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.4   24 Feb 1999 10:45:20   DT14177
// sync up with tracer
// 
//    Rev 1.3   18 Feb 1999 10:39:56   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:40   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:42:10   DMUM
// Check in for DICORE
// 
//    Rev 1.7   Jul 02 1998 11:36:02   DTWK
// Change c_str() to be a const method
//
//    Rev 1.6   Apr 26 1998 15:01:26   DTWK
// Remove method return types from calls to TRACE_METHOD
//
//    Rev 1.5   Nov 09 1997 15:34:42   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.4   Jul 24 1997 08:50:50   DTWK
// Add tracing, c_str(), fix operator/ memory overwrites.
//
//    Rev 1.3   Jul 07 1997 15:12:02   DTWK
//
//
//    Rev 1.2   Jun 16 1997 15:35:54   DTWK
// Add support for Condition class
//
//    Rev 1.1   Jun 11 1997 16:07:36   DTWK
// Update with more recent version from DPQD
//
//


