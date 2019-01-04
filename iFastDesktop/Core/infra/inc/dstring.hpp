#pragma once

#pragma warning( disable : 4996 )

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

/**
 * FILE: dstring.hpp
 *
 * DESCRIPTION :
 *    Supplemental functions to augment the string class from
 *    the Standard C++ library
 *
 */

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef DSTRINGA_HPP
/**@#-*/  // forward declarations
class DString;
class DStringA;
/**@#+*/
   #include <dstringa.hpp>
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include <stringfunctions.hpp>
#endif

#ifndef SYMBOLS_H
   #include <symbols.h>
#endif

#include <assert.h>

// standard linkage-specifier macro
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * a wrapper class for std::string; may be UNICODE;
 * provides the stringfunctions interface.
 * 
 * DString MUST NOT have any non-static data members
 * 
 * @see stringfunctions.hpp
 */
class DICORE_LINKAGE DString /*: public I_STRING*/
{
   // All methods are public and there are no members
public:
   typedef I_STRING::size_type       size_type;
   typedef I_STRING::reference       reference;
   typedef I_STRING::const_reference const_reference;


   /**
    * conversion from I_STRING
    * 
    * @param i_string
    */
   DString( const I_STRING & i_string )
   : imp( ( ( I_CHAR * )i_string.c_str() ) )
   // Invoke .c_str() to force reference
   // counting off for multithreading 
   // support
   {
   }

   /**
    * conversion from DStringA
    * 
    * @param dstringa_in
    */
   DString( const DStringA &dstringa_in );

#ifdef DST_UNICODE
   /**
    * conversion constructor
    * 
    * @param a_string_in
    */
   DString( const A_STRING &a_string_in );
#else
   /**
    * unicode constructor
    * 
    * @param unicode
    */
   DString( const U_STRING & unicode )
   : imp( NULL_STRING )
   {
      unsigned length = unicode.length();
      char * save = new char[ length + 1 ];
      unsigned i = 0;
      for(i = 0; i < length; ++i )
      {
         save[ i ] = ( char ) unicode[ i ];
      }

      save[ i ] = '\0';
      *this = save;
      delete save;
   }
#endif

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param al
    */
   DString( const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( al )
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param rhs
    * @param pos
    * @param n
    * @param al
    */
   DString( const I_STRING & rhs,
            std::allocator< I_CHAR >::size_type pos,
            std::allocator< I_CHAR >::size_type n,
            const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( rhs, pos, n, al )
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param s
    * @param n
    * @param al
    */
   DString( const I_CHAR * s,
            std::allocator< I_CHAR >::size_type n,
            const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( ( NULL == s ) ? I_( "" ) : s, n, al )
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param s
    * @param al
    */
   DString( const I_CHAR * s,
            const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( ( NULL == s ) ? I_( "" ) : s, al )
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param n
    * @param c
    * @param al
    */
   DString( std::allocator< I_CHAR >::size_type n,
            I_CHAR c,
            const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( n, c, al )
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param first
    * @param last
    * @param al
    */
   DString( I_STRING::const_iterator first,
            I_STRING::const_iterator last,
            const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
          )
   : imp( first, last, al )
   {
   }

   /**
    * copy constructor
    * 
    * @param orig
    */
   DString( const DString &orig ) 
   : imp( orig.imp.c_str() )
   // Invoke .c_str() to force reference
   // counting off for multithreading 
   // support
   {
   }

   /**
    * assignment operator
    * 
    * @param orig
    * @return 
    */
   DString & operator=( const DString & orig )
                      // Invoke .c_str() to force reference
                      // counting off for multithreading 
                      // support
   {
      this->imp.assign( ( ( I_CHAR * )orig.imp.c_str() ) );
      return(*this);
   }

#ifdef DST_UNICODE
   /**
    * assignment operator with conversion
    * 
    * @param ascii
    * @return 
    */
   const DString & operator= ( const A_STRING & ascii )
   {
      asciistringToUnicodestring( ascii, ( I_STRING & ) *this );
      return(*this);
   }
#endif

   /**
    * assignment operator with conversion
    * 
    * @param in_char
    * @return 
    */
   const DString & operator= ( const I_CHAR * in_char )
   {
      imp.operator=(in_char);
      return(*this);
   }

   /**
    * assignment operator
    * 
    * @param in_char
    * @return 
    */
   const DString & operator= ( const I_CHAR in_char )
   {
      imp.operator=(in_char);
      return(*this);
   }

#ifdef DST_UNICODE
   /**
    * strips the lead byte from each UNICODE byte pair
    * to generate an ASCII string
    * 
    * @return
    */
   const A_STRING asA() const;
#else
   /**
    * returns *this
    * 
    * @return
    */
   const A_STRING & asA() const
   {
      return(*this);
   }
#endif

   /**
    * Convert a string to an unsigned long.
    * Uses strtoul().
    * 
    * @return 
    */
   unsigned long convertToULong() const
   {
       return(::convertToULong( this->imp ));
   }

   /**
    * Tests all chars in a string to see if they are
    * all digits.  Uses isdigit().
    * 
    * @return 
    */
   bool isAllDigits() const
   {
      return(::isAllDigits( this->imp ));
   }

   /**
    * Tests the string to see if it is a decimal value.
    * Uses isdigit().  The first char can be a digit, '.',
    * '+', '-', or a space.  All other chars must be
    * digits or a '.'.  There is only one '.' allowed.
    * This will also return true on integers.
    * 
    * @return 
    */
   bool isDecimal() const
   {
      return(::isDecimal( this->imp ));
   }

   /**
    * Lowercases all chars in a string.  Chars other than
    * 'A' - 'Z' are unaffected.
    * 
    * @return 
    */
   DString & lowerCase()
   {
      ::lowerCase( this->imp );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Pads a string on the left out to a certain number of
    * characters with any pad character.  If the string
    * is longer than padLength, it will be unchanged.
    * 
    * @param padLength
    * @param padChar
    * @return 
    */
   DString & padLeft( unsigned long padLength, 
                      I_CHAR padChar = ' ' )
   {
      ::padLeft( this->imp, padLength, padChar );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Pads a string on the right out to a certain number
    * of characters with any pad character.  If the
    * string is longer than padLength, then it will be
    * unchanged.
    * 
    * @param padLength
    * @param padChar
    * @return 
    */
   DString & padRight( unsigned long padLength, I_CHAR padChar = ' ' )
   {
      ::padRight(this->imp, padLength, padChar);
      return(static_cast< DString& >(*this));
   }

   /**
    * Strips all occurrences of stripChar on the left and
    * right ends of the string.
    * 
    * @param stripChar
    * @return 
    */
   DString & strip( I_CHAR stripChar = ' ' )
   {
      ::strip( this->imp, stripChar );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Strips all occurrences of a character from the
    * string.
    * 
    * @param stripChar
    * @return 
    */
   DString & stripAll( I_CHAR stripChar = ' ' )
   {
      ::stripAll( this->imp, stripChar );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Strips all occurrences of stripChar on the left end
    * of the string.
    * 
    * @param stripChar
    * @return 
    */
   DString & stripLeading( I_CHAR stripChar = ' ' )
   {
      ::stripLeading( this->imp, stripChar );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Strips all occurrences of stripChar on the right end
    * of the string.
    * 
    * @param stripChar
    * @return 
    */
   DString & stripTrailing( I_CHAR stripChar = ' ' )
   {
      ::stripTrailing( this->imp, stripChar );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Upper case the string.  Chars not in 'a' - 'z' range
    * are unaffected.
    * 
    * @return 
    */
   DString & upperCase()
   {
      ::upperCase( this->imp );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Adds two strings that represent numbers.  Whole
    * numbers only.
    * 
    * This is obsolescent, as it has been replaced by
    * MathString.
    * 
    * @param secondValue
    * @return 
    */
   DString addTwoStrings( const I_STRING & secondValue )
   {
      return(static_cast< DString >( ::addTwoStrings( this->imp, 
                                                      secondValue ) ));
   }

   /**
    * Get an integer representation of the string.  Uses
    * wtoi().
    * 
    * @return 
    */
   int asInteger() const
   {
      return(::asInteger( this->imp ));
   }

   /**
    * Test a string to see if it contains only
    * characters in aMask.
    * 
    * @param aMask
    * @return 
    */
   bool stringHasOnly( const I_STRING & aMask ) const
   {
      return(::stringHasOnly( this->imp, aMask ));
   }

   /**
    * Get a string representation of an int. Uses itow().
    * 
    * @param nValue
    * @return 
    */
   static DString asString( int nValue );

   /**
    * Assigns a string representation of an int. Uses
    * itow().
    * 
    * @param nValue
    */
   void convertIntToString( int nValue )
   {
      ::convertIntToString( nValue, this->imp );
   }

   /**
    * Formats a string according to a mask.
    * 
    * For monetary formats, use a mask like "$$$,$$$.9999".
    * This mask will take a number with 5 or fewer digits to
    * the left of the decimal place, format them with the comma
    * where appropriate, and pre-pend a dollar sign before the
    * first digit.  If the number had 6 digits to the left of
    * the decimal, no dollar sign would be pre-pended, because
    * all 6 of the dollar sign positions are taken up by
    * digits.  This mask would also format the number with 4
    * digits to the right of the decimal point, filling any
    * extra positions with zeros.
    * 
    * For non-monetary numbers, use a mask like "999,999.9999".
    * This mask would produce almost the same format as the one
    * above, but there would be no dollar signs added.
    * 
    * For regular characters, use
    * "XXXX-XX-XX", where the "X"s are your characters.
    * 
    * @param mask
    * @return 
    */
   DString & formatStringUsingMask( const I_STRING &mask )
   {
      ::formatStringUsingMask(this->imp, mask);
      return(static_cast< DString& >( *this ));
   }

   /**
    * Removes the mask characters from a string.  It will only
    * remove mask characters if they are in the proper
    * position,according to the mask passed in.  So, a string
    * like "$102.3",with a mask of "$$$,$$$.9999", would be
    * changed to "102.3".  However, a string like "$1,2345.67"
    * with the same mask, would not be changed, because the
    * mask characters in the string are not in the right
    * places.
    * 
    * @param mask
    * @return 
    */
   DString & removeMaskFromString( const I_STRING &mask )
   {
      ::removeMaskFromString(this->imp, mask);
      return(static_cast< DString& >( *this ));
   }

   /**
    * appends the text representation of an integer to
    * the current string
    * 
    * @param iInt
    * @return 
    */
   DString& appendInt( int iInt )
   {
      ::appendInt( this->imp, iInt );
      return(static_cast< DString& >( *this ));
   }

   /**
    * appends the text representation of an unsigned long
    * to the current string
    * 
    * @param ulNum
    * @return 
    */
   DString& appendULong( unsigned long ulNum )
   {
      ::appendULong( this->imp, ulNum );
      return(static_cast< DString& >( *this ));
   }

   /**
    * appends the text representation of a long
    * to the current string
    * 
    * @param lNum
    * @return 
    */
   DString& appendLong( long lNum )
   {
      ::appendLong( this->imp, lNum );
      return(static_cast< DString& >( *this ));
   }

   /**
    * Searches a string for the first location of a
    * specified character.
    * 
    * @param ch
    * @return 
    */
   int pos( I_CHAR ch )
   {
      return(::pos( ch, this->imp ));
   }

   /**
    * Searches a string for the first location of a
    * specified substring.
    * 
    * @param strSubString
    * @return 
    */
   int pos( const I_STRING& strSubString )
   {
      return(::pos( strSubString, this->imp ));
   }

   /**
    * Extracts the specified space-delimited word
    * from a string.  usWordNum is 0-based index.
    * 
    * @param usWordNum
    * @return 
    */
   DString word( unsigned short usWordNum )
   {
      return(static_cast< DString >( ::word( this->imp, usWordNum ) ));
   }

   /**
    * Determines the number of space-delimited words
    * in a string.
    * 
    * @return 
    */
   unsigned short words()
   {
      return(::words( this->imp ));
   }

   /**
    * Extracts a substring from the left of a string.
    * 
    * @param usLength
    * @return 
    */
   DString left( unsigned short usLength )
   {
      return(static_cast< DString >( ::left( this->imp, usLength ) ));
   }

   /**
    * Reverses a string.
    * 
    * @return 
    */
   DString reverse()
   {
      return(static_cast< DString >( ::reverse( this->imp ) ));
   }

   /**
    * Extracts a substring from the right of a string.
    * 
    * @param usLength
    * @return 
    */
   DString right( unsigned short usLength )
   {
       return(static_cast< DString >( ::right( this->imp, usLength ) ));
   }

   /**
    * Splits language/country/variant from one string into separate
    * strings. Note: This is not designed to be used with a "display
    * string" for a locale - just use input like in the examples
    * below. It will strip spaces, and will locate the language
    * versus the country based on case. The variant is just whatever
    * is left. This function performs no checks as to whether the
    * lang/country/variant it returns are valid (other than they are
    * valid chars in the correct case)
    * 
    * EXAMPLE : "enUSVar" -> "en", "US", "Var"
    *           "USenVar" -> "en", "US", "Var"
    *           " US en Var  " -> "en", "US", "Var"
    *           " US en   " -> "en", "US", ""
    * 
    * @param language
    * @param country
    * @param variant
    * @return 
    */
   bool parseLocale( DString &language, DString &country,
                     DString &variant ) const
   {
       return(::parseLocale( this->imp, language.imp, country.imp, variant.imp ));
   }


   /**
    * performs a string comparison where case is ignored.
    * 
    * This method uses Microsoft-specific _stricmp()
    * (ASCII) or _wcsicmp() (UNICODE)
    * 
    * @param parm
    * @return   0 - equal
    *         < 0 - this less than parm
    *         > 0 - this greater than parm
    */
   inline int stricmp( const DString & parm ) const
   {
      // if the compile blows up we probably need to implement our
      //   own _stricmp() for ASCII or _wcsicmp() for Unicode
       return(::i_stricmp( this->imp.c_str(), parm.imp.c_str() )); 
   }

















   friend inline DString operator+ (const DString& lhs, const DString& rhs) 
   {
      return DString (lhs.imp + rhs.imp);
   }
   friend inline DString operator+ (const I_CHAR* lhs, const DString& rhs) 
   {
      assert (lhs);
      return DString (lhs + rhs.imp);
   }
   friend inline DString operator+ (I_CHAR lhs, const DString& rhs) 
   {
      return DString (lhs + rhs.imp);
   }
   friend inline DString operator+ (const DString& lhs, const I_CHAR* rhs) 
   {
      assert (rhs);
      return DString (lhs.imp + rhs);
   }
   friend inline DString operator+ (const DString& lhs, I_CHAR rhs) 
   {
      return DString (lhs.imp +  rhs);
   }

   friend inline bool operator== (const DString& lhs, const DString& rhs) { return lhs.imp == rhs.imp; }
   friend inline bool operator== (const I_CHAR* lhs, const DString& rhs) 
   {
      assert (lhs);
      return lhs == rhs.imp;
   }
   friend inline bool operator== (const DString& lhs, const I_CHAR* rhs) 
   {
      assert (rhs);
      return lhs.imp == rhs;
   }
   friend inline bool operator<  (const DString& lhs, const DString& rhs) { return lhs.imp < rhs.imp; }
   friend inline bool operator<  (const DString& lhs, const I_CHAR* rhs) 
   {
      assert (rhs);
      return lhs.imp < rhs;
   }
   friend inline bool operator<  (const I_CHAR* lhs, const DString& rhs) 
   {
      assert (lhs);
      return lhs < rhs.imp;
   }


   friend inline bool operator!= (const DString& lhs, const DString& rhs) { return !(lhs == rhs); }
   friend inline bool operator!= (const I_CHAR* lhs,   const DString& rhs) { return !(lhs == rhs); }
   friend inline bool operator!= (const DString& lhs, const I_CHAR* rhs)   { return !(lhs == rhs); }
   friend inline bool operator>  (const DString& lhs, const DString& rhs) { return rhs < lhs; }
   friend inline bool operator>  (const DString& lhs, const I_CHAR* rhs)   { return rhs < lhs; }
   friend inline bool operator>  (const I_CHAR* lhs,   const DString& rhs) { return rhs < lhs; }
   friend inline bool operator<= (const DString& lhs, const DString& rhs) { return !(rhs < lhs); }
   friend inline bool operator<= (const DString& lhs, const I_CHAR* rhs)   { return !(rhs < lhs); }
   friend inline bool operator<= (const I_CHAR* lhs,   const DString& rhs) { return !(rhs < lhs); }
   friend inline bool operator>= (const DString& lhs, const DString& rhs) { return !(lhs < rhs); }
   friend inline bool operator>= (const DString& lhs, const I_CHAR* rhs)   { return !(lhs < rhs); }
   friend inline bool operator>= (const I_CHAR* lhs,   const DString& rhs) { return !(lhs < rhs); }

   DString& operator+= (const DString& str) { imp += (str.imp); return *this; }
   DString& operator+= (const I_CHAR* s)     { assert (s); imp += (s); return *this; }
   DString& operator+= (I_CHAR c)            { imp += (c); return *this; }

   friend inline std::basic_ostream<I_CHAR, I_STRING::traits_type>&
   operator<< (std::basic_ostream<I_CHAR, I_STRING::traits_type>& os, const DString& str) 
   {
      return os << str.imp;
   }

   reference       operator[] (size_type pos)       { return imp[pos]; }
   const_reference operator[] (size_type pos) const { return imp[pos]; }
   reference       at (size_type n)                 { return imp.at (n); }
   const_reference at (size_type n) const           { return imp.at (n); }



   size_type find (const DString& str, size_type pos = 0) const
                              { return imp.find (str.imp, pos); }
   size_type find (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.find (s, pos, n); }
   size_type find (const I_CHAR* s, size_type pos = 0) const
                              { assert (s); return imp.find (s, pos); }
   size_type find (I_CHAR c, size_type pos = 0) const
                              { return imp.find (c, pos); }

   size_type rfind (const DString& str, size_type pos = npos) const
                              { return imp.rfind (str.imp, pos); }
   size_type rfind (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.rfind (s, pos, n); }
   size_type rfind (const I_CHAR* s, size_type pos = npos) const
                              { assert (s); return imp.rfind (s, pos); }
   size_type rfind (I_CHAR c, size_type pos = npos) const
                              { return imp.rfind (c, pos); }

   size_type find_first_of (const DString& str, size_type pos = 0) const
                              { return imp.find_first_of (str.imp, pos); }
   size_type find_first_of (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_first_of (s, pos, n); }
   size_type find_first_of (const I_CHAR* s, size_type pos = 0) const
                              { assert (s); return imp.find_first_of (s, pos); }
   size_type find_first_of (I_CHAR c, size_type pos = 0) const
                              { return imp.find_first_of (c, pos); }

   size_type find_last_of (const DString& str, size_type pos = npos) const
                              { return imp.find_last_of (str.imp, pos); }
   size_type find_last_of (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_last_of (s, pos, n); }
   size_type find_last_of (const I_CHAR* s, size_type pos = npos) const
                              { assert (s); return imp.find_last_of (s, pos); }
   size_type find_last_of (I_CHAR c, size_type pos = npos) const
                              { return imp.find_last_of (c, pos); }

   size_type find_first_not_of (const DString& str, size_type pos = 0) const
                              { return imp.find_first_not_of (str.imp, pos); }
   size_type find_first_not_of (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_first_not_of (s, pos, n); }
   size_type find_first_not_of (const I_CHAR* s, size_type pos = 0) const
                              { assert (s); return imp.find_first_not_of (s, pos); }
   size_type find_first_not_of (I_CHAR c, size_type pos = 0) const
                              { return imp.find_first_not_of (c, pos); }

   size_type find_last_not_of (const DString& str, size_type pos = npos) const
                              { return imp.find_last_not_of (str.imp, pos); }
   size_type find_last_not_of (const I_CHAR* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_last_not_of (s, pos, n); }
   size_type find_last_not_of (const I_CHAR* s, size_type pos = npos) const
                              { assert (s); return imp.find_last_not_of (s, pos); }
   size_type find_last_not_of (I_CHAR c, size_type pos = npos) const
                              { return imp.find_last_not_of (c, pos); }

   const I_CHAR* c_str() const { return imp.c_str(); } 
   const I_CHAR* data() const  { return imp.data(); }

   size_type size() const             { return imp.size(); }
   size_type length() const           { return imp.length(); }
   size_type capacity() const         { return imp.capacity(); }
   void reserve (size_type n = 0)     { imp.reserve (n); }
   bool empty() const                 { return imp.empty(); }

   size_type copy (I_CHAR* s, size_type n, size_type pos = 0) const
                              { assert (s); return imp.copy (s, n, pos); }

   int compare (const DString& str) const
                              { return imp.compare (str.imp); }
   int compare (size_type pos1, size_type n1, const DString& str) const
                              { return imp.compare (pos1, n1, str.imp); }
   int compare (size_type pos1, size_type n1, const DString& str, size_type pos2, size_type n2) const
                              { return imp.compare (pos1, n1, str.imp, pos2, n2); }
   int compare (const I_CHAR* s) const
                              { assert (s); return imp.compare (s); }
   int compare (size_type pos1, size_type n1, const I_CHAR* s, size_type n2 = npos) const
                              { assert (s); return imp.compare (pos1, n1, s, n2); }

   DString& erase (size_type pos = 0, size_type n = npos)
                              { imp.erase (pos, n); return *this; }

   DString& append (const DString& str)     { imp.append (str.imp); return *this; }
   DString& append (const DString& str, size_type pos, size_type n) { imp.append (str.imp, pos, n); return *this; }
   DString& append (const I_CHAR* s, size_type n) { assert (s); imp.append (s, n); return *this; }
   DString& append (const I_CHAR* s)              { assert (s); imp.append (s); return *this; }
   DString& append (size_type n, I_CHAR c)        { imp.append (n, c); return *this; }

   DString& assign (const DString& str)   { imp.assign (str.imp); return *this; }
   DString& assign (const DString& str, size_type pos, size_type n)
                              { imp.assign (str.imp, pos, n); return *this; }
   DString& assign (const I_CHAR* s, size_type n) { assert (s); imp.assign (s, n); return *this; }
   DString& assign (const I_CHAR* s)              { assert (s); imp.assign (s); return *this; }
   DString& assign (size_type n, I_CHAR c)        { imp.assign (n, c); return *this; }

   DString& insert (size_type pos1, const DString& str)
                              { imp.insert (pos1, str.imp); return *this; }
   DString& insert (size_type pos1, const DString& str, size_type pos2, size_type n)
                              { imp.insert (pos1, str.imp, pos2, n); return *this; }
   DString& insert (size_type pos, const I_CHAR* s, size_type n)
                              { assert (s); imp.insert (pos, s, n); return *this; }
   DString& insert (size_type pos, const I_CHAR* s)
                              { assert (s); imp.insert (pos, s); return *this; }
   DString& insert (size_type pos, size_type n, I_CHAR c)
                              { imp.insert (pos, n, c); return *this; }

   enum { npos = size_type (-1) };

   DString substr (size_type pos = 0, size_type n = npos) const  
   {
      if (pos <= size()) 
      { 
         size_type rlen = n < size()-pos ? n : size()-pos;
         return DString (c_str() + pos, rlen);
      } 
      else 
      {
         throw std::out_of_range("DString::substr");
      }
   }

   DString& replace (size_type pos1, size_type n1, const DString& str)
                              { imp.replace (pos1, n1, str.imp); return *this; }
   DString& replace (size_type pos1, size_type n1, const DString& str, size_type pos2, size_type n2)
                              { imp.replace (pos1, n1, str.imp, pos2, n2); return *this; }
   DString& replace (size_type pos, size_type n1, const I_CHAR* s, size_type n2)
                              { assert (s); imp.replace (pos, n1, s, n2); return *this; }
   DString& replace (size_type pos, size_type n1, const I_CHAR* s)
                              { assert (s); imp.replace (pos, n1, s); return *this; }
   DString& replace (size_type pos, size_type n1, size_type n2, I_CHAR c)
                              { imp.replace (pos, n1, n2, c); return *this; }








   inline const I_STRING& getImp() const
   {
       return imp;
   }

   inline I_STRING& getImp() 
   {
       return imp;
   }

  private:
    #pragma warning(push)
    #pragma warning(disable: 4251)
    I_STRING imp;
    #pragma warning(pop)
};


/**
 * assigns an ascii string to a DString
 * 
 * @param ascii
 * @param dstring
 */
void DStringAToDString( const DStringA & ascii, DString & dstring );


/**
 * assigns a DString to an ascii string
 * 
 * @param dstring
 * @param ascii
 */
void DStringToDStringA( const DString & dstring, DStringA & ascii );


#ifdef DST_UNICODE

/**
 * assigns a DString to an ascii string
 * 
 * @param dstring
 * @param ascii
 */
inline void DStringToAsciistring( const DString & dstring, A_STRING & ascii )
{
   unicodestringToAsciistring( ( const I_STRING & )dstring, ascii );
}

/**
 * assigns an ascii string to a DString
 * 
 * @param ascii
 * @param dstring
 */
inline void asciistringToDString( A_STRING & ascii, DString & dstring )
{
	I_STRING localCopy(dstring.getImp());
	asciistringToUnicodestring( ascii, localCopy );
	dstring = localCopy;
}

/**
 * assigns an ascii string to a I_STRING
 * 
 * @param ascii
 * @param dstring
 */
inline void asciistringToI_STRING( A_STRING & ascii, I_STRING & istring )
{
   asciistringToUnicodestring( ascii, istring );
}


#else

/**
 * assigns a DString to an ascii string
 * 
 * @param dstring
 * @param ascii
 */
inline void DStringToAsciistring( const DString & dstring, A_STRING & ascii )
{
   ascii = dstring;
}

/**
 * assigns an ascii string to a DString
 * 
 * @param ascii
 * @param dstring
 */
inline void asciistringToDString( A_STRING & ascii, DString & dstring )
{
   dstring = ascii;
}

/**
 * assigns an ascii string to a I_STRING
 * 
 * @param ascii
 * @param dstring
 */
inline void asciistringToI_STRING( A_STRING & ascii, I_STRING & istring )
{
   istring = ascii;
}

#endif



////////////////////////////////////////////////////////////////////////////////
//              Revision Control Entries
////////////////////////////////////////////////////////////////////////////////
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/dstring.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:58   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:54   SMITHDAV
//Initial revision.
// 
//    Rev 1.17   Apr 11 2000 11:00:36   DT14177
// remove jni
// 
//    Rev 1.16   Jan 11 2000 17:13:16   DT14177
// fixed checkin comments
// 
//    Rev 1.15   Jan 11 2000 17:07:44   DT14177
// changed comments and removed #ifdef WIN32 guards
// 
//    Rev 1.14   Jan 11 2000 14:17:48   DT14177
// added javadoc comments and non-WIN32 #error directive
// 
//    Rev 1.13   Jan 11 2000 11:31:30   DT14177
// Added ignore-case comparison method
// 
//    Rev 1.12   Jan 02 2000 01:24:40   dtwk
// Add an operator= for I_CHAR
// 
//    Rev 1.11   Dec 31 1999 22:27:50   DT14177
// added javadoc comments
// 
//    Rev 1.10   Oct 05 1999 17:45:48   dtwk
// Force copies to not be reference counted in order to
// increase thread safety
// 
//    Rev 1.9   May 24 1999 10:37:46   DTWK
// Add method to parse a string into locale, country, and variant
//
//    Rev 1.8   May 03 1999 12:29:32   DTWK
// Add method allocjstring()
//
//    Rev 1.7   Apr 21 1999 09:01:08   DMUM
// asA() now returns A_STRING in place of DStringA
//
//    Rev 1.6   Apr 15 1999 11:45:00   DMUM
// String development/enhancement
//
