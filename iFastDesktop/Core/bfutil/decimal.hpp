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

/**@pkg BFUTIL */

#include <string>
#include <commonport.h>
#include <conditionmanager.hpp>
#include <base.h>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

/**
 * The Decimal class is a C++ version of ASCII Math, a C
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
 * The Decimal class has been tested on both Windows NT 3.51
 * and OS/2 Warp. The class should be easily portable to other
 * platforms (even EBCDIC) since the '0' through '9'
 * representations are contiguous in most collating sequences.
 */

class BFUTIL_LINKAGE Decimal
{
public:
   /**
    * Default constructor
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    */
   Decimal();

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
   Decimal( I_CHAR * pszStringNum );

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
   Decimal( const I_CHAR * pszStringNum );

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
   explicit Decimal( const DString & pszStringNum );

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
   explicit Decimal( DString & pszStringNum );

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
   explicit Decimal( const DString * pszStringNum );

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
   explicit Decimal( DString * pszStringNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( int pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( unsigned int pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( long pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( unsigned long pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( short pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( unsigned short pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( char pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( unsigned char pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( DIINT64 pszNum );

   /**
    * Constructor.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param pszNum
    *
    */
   explicit Decimal( unsigned DIINT64 pszNum );

   /**
    * Copy constructor
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param copy
    *
    */
   Decimal( const Decimal &copy );

   /**
    * destructor
    */
   ~Decimal();

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
    * Retrieves C String from Decimal object
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
    * Adds two Decimal Objects and returns Sum.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   Decimal operator+( const Decimal& parm );

   /**
    * Subtracts two Decimal Objects and returns Difference
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   Decimal operator-( const Decimal& parm );

   /**
    * Multiply two Decimal Objects and returns result
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * @param parm
    * @return - the result
    *
    */
   Decimal operator*( const Decimal& parm );

   /**
    * Divide two Decimal Objects and return result
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param parm
    * @return - the result
    *
    */
   Decimal operator/( const Decimal& parm );

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
   Decimal operator%( const Decimal& parm );


   // Standard Math Operation with Assignment Operators


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal& -
    * @return Decimal& - the result
    *
    */
   const Decimal& operator+=( const Decimal& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal& -
    * @return Decimal& - the result
    *
    */
   const Decimal& operator-=( const Decimal& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal& -
    * @return Decimal& - the result
    *
    */
   const Decimal& operator*=( const Decimal& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param ^^ const Decimal& -
    * @return Decimal& - the result
    *
    */
   const Decimal& operator/=( const Decimal& parm );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    *    ^^ConditionException - DICORE_DIVIDE_BY_ZERO, if parameter is zero.
    * 
    * 
    * @param ^^ const Decimal& -
    * @return Decimal& - the result
    *
    */
   const Decimal& operator%=( const Decimal& parm );

   // Prefix Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal& - the result
    *
    */
   Decimal& operator++( void );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal& - the result
    *
    */
   Decimal& operator--( void );


   // Postfix Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ int nDummy -
    * @return Decimal - the result
    *
    */
   Decimal operator++( int nDummy );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ int nDummy
    * @return Decimal - the result
    *
    */
   Decimal operator--( int nDummy );


   // Assignment Operators

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &copy
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( const Decimal &copy );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( const I_CHAR * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( I_CHAR * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( const DString * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( DString * pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( const DString & pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const char * pszStringNum -
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( DString & pszStringNum );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( char num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( unsigned char num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( short num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( unsigned short num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( int num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( unsigned int num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( long num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^  num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( unsigned long num );

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( DIINT64 num );


   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ num
    * @return Decimal& - the result
    *
    */
   Decimal& operator=( unsigned DIINT64 num );



   // Derivation Methods

   /**
    * Get the fractional amount of a Decimal
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal - the result. "" if there is no fraction.
    *
    */
   Decimal frac( void )    const;

   /**
    * Get the number without the integer.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal - the result.
    *
    */
   Decimal integer( void ) const;

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
    *        Decimal        m1( "1000.50523" );
    *        m1.round( 2 );  // Result is "1000.51"
    * 
    * @param ^^ short - The number of decimal places to keep.
    * @return Decimal - the result
    *
    */
   Decimal round( short numPlaces )  const;

   /**
    * Truncate the string after the decimal point.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ short - The number of decimal places to keep.
    * @return Decimal - the result
    *
    */
   Decimal trunc( short numPlaces )  const;

   /**
    * Absolute value
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal - the result
    *
    */
   Decimal abs( void )     const;

   /**
    * Flip the sign of a number.
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ void -
    * @return Decimal - the result
    *
    */
   Decimal changeSign( void )  const;


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
    * Determines whether the Decimal Object is equivalent to "0"
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
    * Check two Decimals to see if they are the same
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool - true if they are equivalent, false otherwise.
    *
    */
   bool operator==( const Decimal &compare ) const;

   /**
    * Check two Decimals to see if they are different
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool - true if they are not equivalent, false otherwise.
    *
    */
   bool operator!=( const Decimal &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool -
    *
    */
   bool operator<=( const Decimal &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool -
    *
    */
   bool operator< ( const Decimal &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool -
    *
    */
   bool operator>=( const Decimal &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return bool -
    *
    */
   bool operator> ( const Decimal &compare ) const;


   // Comparison Methods

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return const Decimal& -
    *
    */
   const Decimal& maximum( const Decimal &compare ) const;

   /**
    * 
    *    ^^ConditionException - BASE_ALLOC_FAIL, if alloc fails.
    * 
    * 
    * @param ^^ const Decimal &compare -
    * @return const Decimal& -
    *
    */
   const Decimal& minimum( const Decimal &compare ) const;




private:

   void _addStrings( const I_CHAR * szParam1,
                     const I_CHAR * szParam2,
                     I_CHAR * szResult );

   short _compareString( const Decimal& ) const;
   short _compareStrings( const I_CHAR * szParam1,
                          const I_CHAR * szParam2 ) const;

   void _diffStrings( const I_CHAR * szParam1,
                      const I_CHAR * szParam2,
                      I_CHAR * szResult );

   void _init( const I_CHAR * );

   void _initInt( DIINT64 );

   void _initUInt( unsigned DIINT64 );

//CP20030905   void _initDouble( double );

   void _multString( const I_CHAR * szParam1,
                     I_CHAR   chParam2,
                     I_CHAR * szResult,
                     short  sStartOffs );

   void _studyNumbers( void );
   void _studyNumbers( const I_CHAR * );

   Decimal& _stripOffLeadingZeros( void );
   void _stripSpaces( void );
   void _clearData( void );

private:
   explicit Decimal( float pszNum );      // no implementation ... we don't allow construction from float because they are inherently inaccurate
   explicit Decimal( double pszNum );     // no implementation ... we don't allow construction from double because they are inherently inaccurate
   Decimal& operator=( float num );       // no implementation ... we don't allow assignment from float because they are inherently inaccurate
   Decimal& operator=( double num );      // no implementation ... we don't allow assignment from double because they are inherently inaccurate

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



inline unsigned Decimal::stringLength( void ) const
{
   if( ! _data.szBuffer )
      return(0);
   else
      return(i_strlen( _data.szBuffer ));
}


inline bool Decimal::isMinus( void ) const
{
   return( i_strchr( _data.szBuffer, '-' ) != NULL ? true : false );
}


inline bool Decimal::isPlus( void ) const
{
   return( i_strchr( _data.szBuffer, '-' ) != NULL ? false : true );
}


inline const Decimal& Decimal::maximum( const Decimal &compare ) const
{
   return( _compareString( compare ) < 0 ? compare : *this );
}


inline const Decimal& Decimal::minimum( const Decimal &compare ) const
{
   return( _compareString( compare ) > 0 ? compare : *this );
}


inline bool Decimal::operator==( const Decimal &compare ) const
{
   return( _compareString( compare ) == 0 ? true : false );
}


inline bool Decimal::operator!=( const Decimal &compare ) const
{
   return( _compareString( compare ) != 0 ? true : false );
}


inline bool Decimal::operator<=( const Decimal &compare ) const
{
   return( _compareString( compare ) > 0 ? false : true );
}


inline bool Decimal::operator<( const Decimal &compare ) const
{
   return( _compareString( compare ) < 0 ? true : false );
}


inline bool Decimal::operator>=( const Decimal &compare ) const
{
   return( _compareString( compare ) < 0 ? false : true );
}


inline bool Decimal::operator>( const Decimal &compare ) const
{
   return( _compareString( compare ) > 0 ? true : false );
}


// Subtracts two Decimal Objects and returns Difference
inline Decimal Decimal::operator-( const Decimal &subString )
{
   return( *this + subString.changeSign() );    // Return result from Add
}     // operator-


inline const Decimal& Decimal::operator+=( const Decimal &addString )
{
   Decimal that( *this );
   return( *this = ( that + addString ) );
}


inline const Decimal& Decimal::operator-=( const Decimal &subString )
{
   Decimal that( *this );
   return( *this = ( that - subString ) );
}


inline const Decimal& Decimal::operator*=( const Decimal &multString )
{
   Decimal that( *this );
   return( *this = ( that * multString ) );
}


inline const Decimal& Decimal::operator/=( const Decimal &divString )
{
   Decimal that( *this );
   return( *this = ( that / divString ) );
}


inline const Decimal& Decimal::operator%=( const Decimal &modString )
{
   Decimal that( *this );
   return( *this = ( that % modString ) );
}


// Prefix increment operator
inline Decimal& Decimal::operator++()
{
   Decimal oneString( I_( "1" ) );
   *this += oneString;
   return( *this );
}


// Postfix increment operator
inline Decimal Decimal::operator++( int nDummy )
{
   Decimal tempString( *this );
   Decimal oneString( I_( "1" ) );

   *this += oneString;
   return(tempString);
}


// Prefix decrement operator
inline Decimal& Decimal::operator--()
{
   Decimal oneString( I_( "1" ) );
   return( *this = ( *this - oneString ) );
}


// Postfix decrement operator
inline Decimal Decimal::operator--( int nDummy )
{
   Decimal tempString( *this );
   Decimal oneString( I_( "1" ) );

   *this -= oneString;
   return( tempString );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/decimal.hpp-arc  $
//
//   Rev 1.1   Sep 10 2003 10:44:16   PURDYECH
//Change to a derivative of MathString
//
