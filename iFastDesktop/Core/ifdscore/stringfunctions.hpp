#pragma once

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

/*
 * FILE: stringfunctions.hpp
 *
 * DESCRIPTION :
 *    Supplemental functions to augment the string class from
 *    the Standard C++ library.  Wrapped by DString and 
 *    DStringA.  Not published.
 *
 */


#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif


// standard linkage-specifier macro
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

DICORE_LINKAGE unsigned long convertToULong( const I_STRING &aString );

DICORE_LINKAGE bool isAllDigits( const I_STRING &aString );

DICORE_LINKAGE bool isDecimal( const I_STRING &aString );

DICORE_LINKAGE I_STRING & lowerCase( I_STRING &aString );

DICORE_LINKAGE I_STRING & padLeft( I_STRING &aString,
                                   unsigned long padLength,
                                   I_CHAR padChar = ' ' );

DICORE_LINKAGE I_STRING & padRight( I_STRING &aString,
                                    unsigned long padLength,
                                    I_CHAR padChar = ' ' );

DICORE_LINKAGE I_STRING & strip( I_STRING &aString,
                                 I_CHAR stripChar = ' ' );


DICORE_LINKAGE I_STRING & stripAll( I_STRING &aString,
                                    I_CHAR stripChar = ' ' );


DICORE_LINKAGE I_STRING & stripLeading( I_STRING &aString,
                                        I_CHAR stripChar = ' ' );


DICORE_LINKAGE I_STRING & stripTrailing( I_STRING &aString,
                                         I_CHAR stripChar = ' ' );

DICORE_LINKAGE I_STRING & upperCase( I_STRING &aString );

DICORE_LINKAGE I_STRING addTwoStrings( const I_STRING &firstValue,
                                       const I_STRING &secondValue );

DICORE_LINKAGE int asInteger( const I_STRING &aString );

DICORE_LINKAGE bool stringHasOnly( const I_STRING& aString,
                                   const I_STRING& aMask );

DICORE_LINKAGE I_STRING asString( DIINT64 nValue );

DICORE_LINKAGE I_STRING floatAsString( double nValue );

DICORE_LINKAGE void convertIntToString( int nValue, I_STRING & dest );

DICORE_LINKAGE I_STRING & formatStringUsingMask(
                                               I_STRING &valueString,
                                               const I_STRING &mask );

DICORE_LINKAGE I_STRING & removeMaskFromString( I_STRING &maskedValue,
                                                const I_STRING &mask );

DICORE_LINKAGE I_STRING& appendInt( I_STRING &aString, int iInt );

DICORE_LINKAGE I_STRING& appendULong( I_STRING &aString,
                                      unsigned long ulNum );

DICORE_LINKAGE I_STRING& appendLong( I_STRING &aString, long lNum );

DICORE_LINKAGE int pos( I_CHAR ch, const I_STRING& aString );

DICORE_LINKAGE int pos( const I_STRING& strSubString,
                        const I_STRING& strFullString );

DICORE_LINKAGE I_STRING makeIstringRepeatChar( I_CHAR ch,
                                               unsigned short usNumChars );

DICORE_LINKAGE void copyChars( I_STRING & dest,
                               I_CHAR ch,
                               unsigned short usNumChars );

DICORE_LINKAGE I_STRING word( const I_STRING& aString,
                              unsigned short usWordNum );

DICORE_LINKAGE unsigned short words( const I_STRING& aString );

DICORE_LINKAGE I_STRING left( const I_STRING& aString,
                              unsigned short usLength );

DICORE_LINKAGE I_STRING reverse( const I_STRING& aString );

DICORE_LINKAGE I_STRING right( const I_STRING& aString,
                               unsigned short usLength );

DICORE_LINKAGE bool parseLocale( const I_STRING& locale,
                                 I_STRING& language,
                                 I_STRING& country,
                                 I_STRING& variant );

#ifdef DST_UNICODE

class DStringA;

DICORE_LINKAGE unsigned long convertToULong( const DStringA &aString );

DICORE_LINKAGE bool isAllDigits( const DStringA &aString );

DICORE_LINKAGE bool isDecimal( const DStringA &aString );

DICORE_LINKAGE DStringA & lowerCase( DStringA &aString );

DICORE_LINKAGE DStringA & padLeft( DStringA &aString,
                                   unsigned long padLength,
                                   char padChar = ' ' );

DICORE_LINKAGE DStringA & padRight( DStringA &aString,
                                    unsigned long padLength,
                                    char padChar = ' ' );

DICORE_LINKAGE DStringA & strip( DStringA &aString,
                                 char stripChar = ' ' );


DICORE_LINKAGE DStringA & stripAll( DStringA &aString,
                                    char stripChar = ' ' );


DICORE_LINKAGE DStringA & stripLeading( DStringA &aString,
                                        char stripChar = ' ' );


DICORE_LINKAGE DStringA & stripTrailing( DStringA &aString,
                                         char stripChar = ' ' );

DICORE_LINKAGE DStringA & upperCase( DStringA &aString );

DICORE_LINKAGE DStringA addTwoStrings( const DStringA &firstValue,
                                       const DStringA &secondValue );

DICORE_LINKAGE int asInteger( const DStringA &aString );

DICORE_LINKAGE bool stringHasOnly( const DStringA& aString,
                                   const DStringA& aMask );

DICORE_LINKAGE DStringA asAsciiString( int nValue );

DICORE_LINKAGE void convertIntToString( int nValue, DStringA & dest );

DICORE_LINKAGE DStringA & formatStringUsingMask(
                                               DStringA &valueString,
                                               const DStringA &mask );

DICORE_LINKAGE DStringA & removeMaskFromString(
                                              DStringA &maskedValue,
                                              const DStringA &mask );

DICORE_LINKAGE DStringA& appendInt( DStringA &aString, int iInt );

DICORE_LINKAGE DStringA& appendULong( DStringA &aString,
                                      unsigned long ulNum );

DICORE_LINKAGE DStringA& appendLong( DStringA &aString, long lNum );

DICORE_LINKAGE int pos( char ch, const DStringA& aString );

DICORE_LINKAGE int pos( const DStringA& strSubString,
                        const DStringA& strFullString );

DICORE_LINKAGE DStringA copies( char ch, unsigned short usNumChars );

DICORE_LINKAGE void copyChars( DStringA & dest,
                               char ch,
                               unsigned short usNumChars );

DICORE_LINKAGE DStringA word( const DStringA& aString,
                              unsigned short usWordNum );

DICORE_LINKAGE unsigned short words( const DStringA& aString );

DICORE_LINKAGE DStringA left( const DStringA& aString,
                              unsigned short usLength );

DICORE_LINKAGE DStringA reverse( const DStringA& aString );

DICORE_LINKAGE DStringA right( const DStringA& aString,
                               unsigned short usLength );

DICORE_LINKAGE bool parseLocale( const DStringA& locale,
                                 DStringA& language,
                                 DStringA& country,
                                 DStringA& variant );

#ifndef DSTRING_HPP
    #include <dstring.hpp>
#endif


DICORE_LINKAGE DString & strip( DString &aString,
                                 char stripChar = ' ' );


DICORE_LINKAGE DString & stripAll( DString &aString,
                                    char stripChar = ' ' );

DICORE_LINKAGE DString & stripLeading( DString &aString,
                                         char stripChar = ' ' );

DICORE_LINKAGE DString & stripTrailing( DString &aString,
                                         char stripChar = ' ' );

DICORE_LINKAGE DString& appendULong( DString &aString,
                                      unsigned long ulNum );

DICORE_LINKAGE DString & padLeft( DString &aString,
                                   unsigned long padLength,
                                   char padChar = ' ' );

DICORE_LINKAGE DString & padRight( DString &aString,
                                    unsigned long padLength,
                                    char padChar = ' ' );

DICORE_LINKAGE void convertIntToString( int nValue, DString & dest );

DICORE_LINKAGE DString & removeMaskFromString(
                                              DString &maskedValue,
                                              const DString &mask );

DICORE_LINKAGE DString & formatStringUsingMask(
                                               DString &valueString,
                                               const DString &mask );

   #ifndef DSTRINGA_HPP
      #include <dstringa.hpp>
   #endif

#endif

/*******************************************************************************
//              Revision Control Entries
//#*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/stringfunctions.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:18   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:14   SMITHDAV
//Initial revision.
// 
//    Rev 1.9   Jun 26 2000 17:09:26   DT14177
// added constructors and assignment operators to MathString
// 
//    Rev 1.8   Dec 31 1999 22:27:56   DT14177
// added javadoc comments
// 
//    Rev 1.7   May 24 1999 10:37:56   DTWK
// Add method to parse a string into locale, country, and variant
//
//    Rev 1.6   Apr 15 1999 11:45:04   DMUM
// String development/enhancement
//
//    Rev 1.5   18 Feb 1999 10:40:12   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:06:58   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:43:26   DMUM
// Check in for DICORE
//
//    Rev 1.13   Nov 09 1997 15:34:50   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.12   Aug 28 1997 09:57:36   DTWK
// Add REXX-like functions for DPQD
//
//    Rev 1.11   Jul 23 1997 11:35:50   DTWK
// Add functions appendULong() et al.
//
//    Rev 1.10   12 Jun 1997 12:53:34   dcyk
// Added formatStringUsingMask and
// removeMaskFromString.
//
//
//    Rev 1.9   Jun 11 1997 16:14:56   DTWK
// Add comments.
// stripTrailing would not strip functions that had ONLY the char to strip.
//
//    Rev 1.8   Mar 26 1997 17:05:36   dlkt
// Added asString method that converts an
// integer to a string.
//
//    Rev 1.7   Feb 19 1997 16:35:14   dlkt
// Added stringHasOnly function.
//
//    Rev 1.6   Feb 11 1997 13:22:44   DTWK
// Use RogueWave Standard C++ Library/
// Split CLogSll to DIVIEW and DIOS/ change
// SCLXTNSN to DISCLXTN
//
//    Rev 1.5   Jan 28 1997 12:46:28   DPQD
// Added prototype for the 'asInteger' method.
//
//    Rev 1.4   Jan 28 1997 08:42:36   dcyk
// Added "addTwoStrings" function, which
// arithmetically adds two strings, and returns
// a third string.
//
//
//    Rev 1.3   Dec 31 1996 13:21:30   DRUS
// Added the functions isAllDigits, isDecimal, lowerCase, stripAll, and
// upperCase.  Renamed the function atoul to convertToULong.
//
//    Rev 1.2   Nov 21 1996 14:37:10   DRUS
//
//
//    Rev 1.1   Nov 20 1996 17:07:16   DRUS
//
//
//    Rev 1.0   Nov 20 1996 11:05:38   DRUS
//
//
*/

