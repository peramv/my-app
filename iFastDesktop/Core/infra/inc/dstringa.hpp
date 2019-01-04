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
 * FILE: dstringa.hpp
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

#ifndef DSTRING_HPP
/**@#-*/  // forward declarations
class DString;
class DStringA;
/**@#+*/
   #include <dstring.hpp>
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include <stringfunctions.hpp>
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
 * a wrapper class for std::string that guarantees 
 * that the string will be ASCII even when DString
 * isn't
 * 
 * DString MUST NOT have any non-static data members
 * 
 */
class DICORE_LINKAGE DStringA /*: public A_STRING*/
{
   // All methods are public and there are no members
public:
   typedef A_STRING::size_type       size_type;
   typedef A_STRING::reference       reference;
   typedef A_STRING::const_reference const_reference;

   /**
    * conversion from A_STRING
    * 
    * @param a_string
    */
   DStringA( const A_STRING &a_string )
   : imp( ( char * )a_string.c_str() )
   // Invoke .c_str() to force reference
   // counting off for multithreading 
   // support
   {
   }

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param al
    */
   DStringA( const std::allocator< char > & al = std::allocator< char >() )
   : imp( al )
   {
   }

   /**
    * constructor
    * 
    * conversion from DString
    * 
    * @param dstring_in
    */
   DStringA( const DString &dstring_in );

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
   DStringA( const A_STRING & rhs,
             std::allocator< char >::size_type pos,
             std::allocator< char >::size_type n,
             const std::allocator< char > & al = std::allocator< char >() )
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
   DStringA( const char *s,
             std::allocator< char >::size_type n,
             const std::allocator< char > & al = std::allocator< char >() )
   : imp( ( NULL == s ) ? "" : s, n, al )
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
   DStringA( const char *s,
             const std::allocator< char > & al = std::allocator< char >() )
   : imp( ( NULL == s ) ? "" : s, al )
   {
   }

#ifdef DST_UNICODE
   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param i_s
    * @param al
    */
   DStringA( const I_CHAR *i_s,
             const std::allocator< I_CHAR > & al = std::allocator< I_CHAR >()
           );
#endif

   /**
    * constructor
    * 
    * overloaded support for string parent class
    * 
    * @param n
    * @param c
    * @param al
    */
   DStringA( std::allocator< char >::size_type n,
             char c,
             const std::allocator< char > & al = std::allocator< char >() )
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
   DStringA( A_STRING::const_iterator first,
             A_STRING::const_iterator last,
             const std::allocator< char > & al = std::allocator< char >() )
   : imp( first, last, al )
   {
   }

   /**
    * copy constructor
    * 
    * @param orig
    */
   DStringA( const DStringA &orig ) :
   imp( orig.c_str() )
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
   DStringA & operator=( const DStringA & orig )
                       // Invoke .c_str() to force reference
                       // counting off for multithreading 
                       // support
   {
      this->assign( ( ( char * )orig.c_str() ) );
      return(*this);
   }

   /**
    * assignment operator from an I_CHAR
    * 
    * @param in_char
    * @return 
    */
   const DStringA & operator=( const I_CHAR in_char )
   {
#pragma warning( push )
#pragma warning( disable:4244 )
      imp.operator=(in_char);
#pragma warning( pop )
      return(*this);
   }

   /**
    * Convert a string to an unsigned long. 
    * Uses strtoul().
    * 
    * @return 
    */
   unsigned long convertToULong() const
   {
      return(::convertToULong( *this ));
   }

   /**
    * Tests all chars in a string to see if they are 
    * all digits.  Uses isdigit().
    * 
    * @return 
    */
   bool isAllDigits() const
   {
      return(::isAllDigits( *this ));
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
      return(::isDecimal( *this ));
   }

   /**
    * Lowercases all chars in a string.  Chars other than
    * 'A' - 'Z' are unaffected.
    * 
    * @return 
    */
   DStringA & lowerCase()
   {
      return(static_cast<DStringA&>( ::lowerCase( *this ) ));
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
   DStringA & padLeft( unsigned long padLength, 
                       char padChar = ' ' )
   {
      return(static_cast<DStringA&>(::padLeft( *this, 
                                               padLength, 
                                               padChar) ));
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
   DStringA & padRight( unsigned long padLength,
                        char padChar = ' ' )
   {
      return(static_cast<DStringA&>(::padRight( *this, 
                                                padLength, 
                                                padChar) ));
   }

   /**
    * Strips all occurrences of stripChar on the left and
    * right ends of the string.
    * 
    * @param stripChar
    * @return 
    */
   DStringA & strip( char stripChar = ' ' )
   {
      return(static_cast<DStringA&>( ::strip( *this, stripChar ) ));
   }

   /**
    * Strips all occurrences of a character from the
    * string.
    * 
    * @param stripChar
    * @return 
    */
   DStringA & stripAll( char stripChar = ' ' )
   {
      return(static_cast<DStringA&>( ::stripAll( *this, stripChar ) ));
   }

   /**
    * Strips all occurrences of stripChar on the left end 
    * of the string.
    * 
    * @param stripChar
    * @return 
    */
   DStringA & stripLeading( char stripChar = ' ' )
   {
      return(static_cast<DStringA&>( ::stripLeading( *this, stripChar ) ));
   }

   /**
    * Strips all occurrences of stripChar on the right end 
    * of the string.
    * 
    * @param stripChar
    * @return 
    */
   DStringA & stripTrailing( char stripChar = ' ' )
   {
      return(static_cast<DStringA&>( ::stripTrailing( *this, stripChar ) ));
   }

   /**
    * Upper case the string.  Chars not in 'a' - 'z' range
    * are unaffected.
    * 
    * @return 
    */
   DStringA & upperCase()
   {
      return(static_cast<DStringA&>( ::upperCase( *this ) ));
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
   DStringA addTwoStrings( const A_STRING &secondValue )
   {
      return(static_cast<DStringA>( ::addTwoStrings( *this, secondValue ) ));
   }

   /**
    * Get an integer representation of the string.  Uses
    * atoi().
    * 
    * @return 
    */
   int asInteger() const
   {
      return(::asInteger( *this ));
   }

   /**
    * Test a string to see if it contains only 
    * characters in aMask.
    * 
    * @param aMask
    * @return 
    */
   bool stringHasOnly( const A_STRING& aMask ) const
   {
      return(::stringHasOnly( *this, aMask ));
   }

   /**
    * Get a string representation of an int. Uses itoa().
    * 
    * @param nValue
    * @return 
    */
   static DStringA asString( int nValue );

   /**
    * Assigns a string representation of an int. Uses 
    * itoa().
    * 
    * @param nValue
    */
   void convertIntToString( int nValue )
   {
      ::convertIntToString( nValue, *this );
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
   DStringA & formatStringUsingMask( const A_STRING &mask )
   {
      return(static_cast<DStringA&>( ::formatStringUsingMask(*this, mask) ));
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
   DStringA & removeMaskFromString( const A_STRING &mask )
   {
      return(static_cast<DStringA&>( ::removeMaskFromString( *this, mask ) ));
   }

   /**
    * appends the text representation of an integer to
    * the current string
    * 
    * @param iInt
    * @return 
    */
   DStringA& appendInt( int iInt )
   {
      return(static_cast<DStringA&>( ::appendInt( *this, iInt ) ));
   }

   /**
    * appends the text representation of an unsigned long
    * to the current string
    * 
    * @param ulNum
    * @return 
    */
   DStringA& appendULong( unsigned long ulNum )
   {
      return(static_cast<DStringA&>( ::appendULong( *this, ulNum ) ));
   }

   /**
    * appends the text representation of a long
    * to the current string
    * 
    * @param lNum
    * @return 
    */
   DStringA& appendLong( long lNum )
   {
      return(static_cast<DStringA&>( ::appendLong( *this, lNum ) ));
   }

   /**
    * Searches a string for the first location of a
    * specified character.
    * 
    * @param ch
    * @return 
    */
   int pos( char ch )
   {
      return(::pos( ch, *this ));
   }

   /**
    * Searches a string for the first location of a
    * specified substring.
    * 
    * @param strSubString
    * @return 
    */
   int pos( const A_STRING& strSubString )
   {
      return(::pos( strSubString, *this ));
   }

   /**
    * Extracts the specified space-delimited word
    * from a string.  usWordNum is 0-based index.
    * 
    * @param usWordNum
    * @return 
    */
   DStringA word( unsigned short usWordNum )
   {
      return(static_cast<DStringA>( ::word( *this, usWordNum ) ));
   }

   /**
    * Determines the number of space-delimited words
    * in a string.
    * 
    * @return 
    */
   unsigned short words()
   {
      return(::words( *this ));
   }

   /**
    * Extracts a substring from the left of a string.
    * 
    * @param usLength
    * @return 
    */
   DStringA left( unsigned short usLength )
   {
      return(static_cast<DStringA>( ::left( *this, usLength ) ));
   }

   /**
    * Reverses a string.
    * 
    * @return 
    */
   DStringA reverse()
   {
      return(static_cast<DStringA>( ::reverse( *this ) ));
   }

   /**
    * Extracts a substring from the right of a string.
    * 
    * @param usLength
    * @return 
    */
   DStringA right( unsigned short usLength )
   {
      return(static_cast<DStringA>( ::right( *this, usLength ) ));
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
   bool parseLocale( DStringA &language, DStringA &country,
                     DStringA &variant ) const
   {
      return(::parseLocale( *this, language, country, variant ));
   }


   /**
    * performs a string comparison where case is ignored.
    * 
    * This method uses Microsoft-specific _stricmp()
    * 
    * @param parm
    * @return   0 - equal
    *         < 0 - this less than parm
    *         > 0 - this greater than parm
    */
   inline int stricmp( const DStringA & parm )
   {
      // if the compile blows up we probably need to implement our
      //   own _stricmp() for ASCII
      return(::_stricmp( this->c_str(), parm.c_str() ));
   }


   friend inline DStringA operator+ (const DStringA& lhs, const DStringA& rhs) 
   {
      return DStringA (lhs.imp + rhs.imp);
   }
   friend inline DStringA operator+ (const char* lhs, const DStringA& rhs) 
   {
      assert (lhs);
      return DStringA (lhs + rhs.imp);
   }
   friend inline DStringA operator+ (char lhs, const DStringA& rhs) 
   {
      return DStringA (lhs + rhs.imp);
   }
   friend inline DStringA operator+ (const DStringA& lhs, const char* rhs) 
   {
      assert (rhs);
      return DStringA (lhs.imp + rhs);
   }
   friend inline DStringA operator+ (const DStringA& lhs, char rhs) 
   {
      return DStringA (lhs.imp +  rhs);
   }

   friend inline bool operator== (const DStringA& lhs, const DStringA& rhs) { return lhs.imp == rhs.imp; }
   friend inline bool operator== (const char* lhs, const DStringA& rhs) 
   {
      assert (lhs);
      return lhs == rhs.imp;
   }
   friend inline bool operator== (const DStringA& lhs, const char* rhs) 
   {
      assert (rhs);
      return lhs.imp == rhs;
   }
   friend inline bool operator<  (const DStringA& lhs, const DStringA& rhs) { return lhs.imp < rhs.imp; }
   friend inline bool operator<  (const DStringA& lhs, const char* rhs) 
   {
      assert (rhs);
      return lhs.imp < rhs;
   }
   friend inline bool operator<  (const char* lhs, const DStringA& rhs) 
   {
      assert (lhs);
      return lhs < rhs.imp;
   }


   friend inline bool operator!= (const DStringA& lhs, const DStringA& rhs) { return !(lhs == rhs); }
   friend inline bool operator!= (const char* lhs,   const DStringA& rhs) { return !(lhs == rhs); }
   friend inline bool operator!= (const DStringA& lhs, const char* rhs)   { return !(lhs == rhs); }
   friend inline bool operator>  (const DStringA& lhs, const DStringA& rhs) { return rhs < lhs; }
   friend inline bool operator>  (const DStringA& lhs, const char* rhs)   { return rhs < lhs; }
   friend inline bool operator>  (const char* lhs,   const DStringA& rhs) { return rhs < lhs; }
   friend inline bool operator<= (const DStringA& lhs, const DStringA& rhs) { return !(rhs < lhs); }
   friend inline bool operator<= (const DStringA& lhs, const char* rhs)   { return !(rhs < lhs); }
   friend inline bool operator<= (const char* lhs,   const DStringA& rhs) { return !(rhs < lhs); }
   friend inline bool operator>= (const DStringA& lhs, const DStringA& rhs) { return !(lhs < rhs); }
   friend inline bool operator>= (const DStringA& lhs, const char* rhs)   { return !(lhs < rhs); }
   friend inline bool operator>= (const char* lhs,   const DStringA& rhs) { return !(lhs < rhs); }

   DStringA& operator+= (const DStringA& str) { imp += (str.imp); return *this; }
   DStringA& operator+= (const char* s)     { assert (s); imp += (s); return *this; }
   DStringA& operator+= (char c)            { imp += (c); return *this; }

   friend inline std::basic_ostream<char, A_STRING::traits_type>&
   operator<< (std::basic_ostream<char, A_STRING::traits_type>& os, const DStringA& str) 
   {
      return os << str.imp;
   }

   reference       operator[] (size_type pos)       { return imp[pos]; }
   const_reference operator[] (size_type pos) const { return imp[pos]; }
   reference       at (size_type n)                 { return imp.at (n); }
   const_reference at (size_type n) const           { return imp.at (n); }



   size_type find (const DStringA& str, size_type pos = 0) const
                              { return imp.find (str.imp, pos); }
   size_type find (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.find (s, pos, n); }
   size_type find (const char* s, size_type pos = 0) const
                              { assert (s); return imp.find (s, pos); }
   size_type find (char c, size_type pos = 0) const
                              { return imp.find (c, pos); }

   size_type rfind (const DStringA& str, size_type pos = npos) const
                              { return imp.rfind (str.imp, pos); }
   size_type rfind (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.rfind (s, pos, n); }
   size_type rfind (const char* s, size_type pos = npos) const
                              { assert (s); return imp.rfind (s, pos); }
   size_type rfind (char c, size_type pos = npos) const
                              { return imp.rfind (c, pos); }

   size_type find_first_of (const DStringA& str, size_type pos = 0) const
                              { return imp.find_first_of (str.imp, pos); }
   size_type find_first_of (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_first_of (s, pos, n); }
   size_type find_first_of (const char* s, size_type pos = 0) const
                              { assert (s); return imp.find_first_of (s, pos); }
   size_type find_first_of (char c, size_type pos = 0) const
                              { return imp.find_first_of (c, pos); }

   size_type find_last_of (const DStringA& str, size_type pos = npos) const
                              { return imp.find_last_of (str.imp, pos); }
   size_type find_last_of (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_last_of (s, pos, n); }
   size_type find_last_of (const char* s, size_type pos = npos) const
                              { assert (s); return imp.find_last_of (s, pos); }
   size_type find_last_of (char c, size_type pos = npos) const
                              { return imp.find_last_of (c, pos); }

   size_type find_first_not_of (const DStringA& str, size_type pos = 0) const
                              { return imp.find_first_not_of (str.imp, pos); }
   size_type find_first_not_of (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_first_not_of (s, pos, n); }
   size_type find_first_not_of (const char* s, size_type pos = 0) const
                              { assert (s); return imp.find_first_not_of (s, pos); }
   size_type find_first_not_of (char c, size_type pos = 0) const
                              { return imp.find_first_not_of (c, pos); }

   size_type find_last_not_of (const DStringA& str, size_type pos = npos) const
                              { return imp.find_last_not_of (str.imp, pos); }
   size_type find_last_not_of (const char* s, size_type pos, size_type n) const
                              { assert (s); return imp.find_last_not_of (s, pos, n); }
   size_type find_last_not_of (const char* s, size_type pos = npos) const
                              { assert (s); return imp.find_last_not_of (s, pos); }
   size_type find_last_not_of (char c, size_type pos = npos) const
                              { return imp.find_last_not_of (c, pos); }

   const char* c_str() const { return imp.c_str(); } 
   const char* data() const  { return imp.data(); }

   size_type size() const             { return imp.size(); }
   size_type length() const           { return imp.length(); }
   size_type capacity() const         { return imp.capacity(); }
   void reserve (size_type n = 0)     { imp.reserve (n); }
   bool empty() const                 { return imp.empty(); }

   size_type copy (char* s, size_type n, size_type pos = 0) const
                              { assert (s); return imp.copy (s, n, pos); }

   int compare (const DStringA& str) const
                              { return imp.compare (str.imp); }
   int compare (size_type pos1, size_type n1, const DStringA& str) const
                              { return imp.compare (pos1, n1, str.imp); }
   int compare (size_type pos1, size_type n1, const DStringA& str, size_type pos2, size_type n2) const
                              { return imp.compare (pos1, n1, str.imp, pos2, n2); }
   int compare (const char* s) const
                              { assert (s); return imp.compare (s); }
   int compare (size_type pos1, size_type n1, const char* s, size_type n2 = npos) const
                              { assert (s); return imp.compare (pos1, n1, s, n2); }

   DStringA& erase (size_type pos = 0, size_type n = npos)
                              { imp.erase (pos, n); return *this; }

   DStringA& append (const DStringA& str)     { imp.append (str.imp); return *this; }
   DStringA& append (const DStringA& str, size_type pos, size_type n) { imp.append (str.imp, pos, n); return *this; }
   DStringA& append (const char* s, size_type n) { assert (s); imp.append (s, n); return *this; }
   DStringA& append (const char* s)              { assert (s); imp.append (s); return *this; }
   DStringA& append (size_type n, char c)        { imp.append (n, c); return *this; }

   DStringA& assign (const DStringA& str)   { imp.assign (str.imp); return *this; }
   DStringA& assign (const DStringA& str, size_type pos, size_type n)
                              { imp.assign (str.imp, pos, n); return *this; }
   DStringA& assign (const char* s, size_type n) { assert (s); imp.assign (s, n); return *this; }
   DStringA& assign (const char* s)              { assert (s); imp.assign (s); return *this; }
   DStringA& assign (size_type n, char c)        { imp.assign (n, c); return *this; }

   DStringA& insert (size_type pos1, const DStringA& str)
                              { imp.insert (pos1, str.imp); return *this; }
   DStringA& insert (size_type pos1, const DStringA& str, size_type pos2, size_type n)
                              { imp.insert (pos1, str.imp, pos2, n); return *this; }
   DStringA& insert (size_type pos, const char* s, size_type n)
                              { assert (s); imp.insert (pos, s, n); return *this; }
   DStringA& insert (size_type pos, const char* s)
                              { assert (s); imp.insert (pos, s); return *this; }
   DStringA& insert (size_type pos, size_type n, char c)
                              { imp.insert (pos, n, c); return *this; }


   enum { npos = size_type (-1) };

   DStringA substr (size_type pos = 0, size_type n = npos) const  
   {
      if (pos <= size()) 
      { 
         size_type rlen = n < size()-pos ? n : size()-pos;
         return DStringA (c_str() + pos, rlen);
      } 
      else 
      {
         throw std::out_of_range("DStringA::substr");
      }
   }

   DStringA& replace (size_type pos1, size_type n1, const DStringA& str)
                              { imp.replace (pos1, n1, str.imp); return *this; }
   DStringA& replace (size_type pos1, size_type n1, const DStringA& str, size_type pos2, size_type n2)
                              { imp.replace (pos1, n1, str.imp, pos2, n2); return *this; }
   DStringA& replace (size_type pos, size_type n1, const char* s, size_type n2)
                              { assert (s); imp.replace (pos, n1, s, n2); return *this; }
   DStringA& replace (size_type pos, size_type n1, const char* s)
                              { assert (s); imp.replace (pos, n1, s); return *this; }
   DStringA& replace (size_type pos, size_type n1, size_type n2, char c)
                              { imp.replace (pos, n1, n2, c); return *this; }



   inline A_STRING getImp() const
   {
       return imp;
   }

  private:
    #pragma warning(push)
    #pragma warning(disable: 4251)
    A_STRING imp;
    #pragma warning(pop)
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/dstringa.hpp-arc  $
//
//   Rev 1.2   Oct 22 2004 09:03:14   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.1   Oct 09 2002 17:42:00   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:54   SMITHDAV
//Initial revision.
// 
//    Rev 1.15   Apr 11 2000 11:00:40   DT14177
// remove jni
// 
//    Rev 1.14   Jan 11 2000 17:13:20   DT14177
// fixed checkin comments
// 
//    Rev 1.13   Jan 11 2000 17:07:48   DT14177
// changed comments and removed #ifdef WIN32 guards
// 
//    Rev 1.12   Jan 11 2000 14:17:50   DT14177
// added javadoc comments and non-WIN32 #error directive
// 
//    Rev 1.11   Jan 11 2000 11:31:32   DT14177
// Added ignore-case comparison method
// 
//    Rev 1.10   Dec 31 1999 22:27:52   DT14177
// added javadoc comments
// 
//    Rev 1.9   Oct 05 1999 17:45:50   dtwk
// Force copies to not be reference counted in order to
// increase thread safety
// 
//    Rev 1.8   May 24 1999 10:37:50   DTWK
// Add method to parse a string into locale, country, and variant
//
//    Rev 1.7   May 03 1999 12:29:34   DTWK
// Add method allocjstring()
//
//    Rev 1.6   Apr 15 1999 11:45:02   DMUM
// String development/enhancement
//

