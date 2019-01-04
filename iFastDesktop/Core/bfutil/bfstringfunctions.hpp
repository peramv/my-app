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


#include <commonport.h>
#include <string>
#include <dstring.hpp>

// standard linkage-specifier macro
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bfutil
{

BFUTIL_LINKAGE unsigned long convertToULong( const I_STRING &aString );

BFUTIL_LINKAGE bool isAllDigits( const I_STRING &aString );

BFUTIL_LINKAGE bool isDecimal( const I_STRING &aString );

BFUTIL_LINKAGE I_STRING & lowerCase( I_STRING &aString );

BFUTIL_LINKAGE I_STRING & padLeft( I_STRING &aString,
                                   unsigned long padLength,
                                   I_CHAR padChar = I_(' ') );

BFUTIL_LINKAGE I_STRING & padRight( I_STRING &aString,
                                    unsigned long padLength,
                                    I_CHAR padChar = I_(' ') );

BFUTIL_LINKAGE I_STRING & strip( I_STRING &aString,
                                 I_CHAR stripChar = I_(' ') );


BFUTIL_LINKAGE I_STRING & stripAll( I_STRING &aString,
                                    I_CHAR stripChar = I_(' ') );


BFUTIL_LINKAGE I_STRING & stripLeading( I_STRING &aString,
                                        I_CHAR stripChar = I_(' ') );


BFUTIL_LINKAGE I_STRING & stripTrailing( I_STRING &aString,
                                         I_CHAR stripChar = I_(' ') );

BFUTIL_LINKAGE I_STRING & upperCase( I_STRING &aString );

BFUTIL_LINKAGE int asInteger( const I_STRING &aString );

BFUTIL_LINKAGE bool stringHasOnly( const I_STRING& aString,
                                   const I_STRING& aMask );

BFUTIL_LINKAGE I_STRING asString( DIINT64 nValue );

BFUTIL_LINKAGE I_STRING floatAsString( double nValue );

BFUTIL_LINKAGE void convertIntToString( int nValue, I_STRING & dest );


BFUTIL_LINKAGE I_STRING& appendInt( I_STRING &aString, int iInt );

BFUTIL_LINKAGE I_STRING& appendULong( I_STRING &aString,
                                      unsigned long ulNum );

BFUTIL_LINKAGE I_STRING& appendLong( I_STRING &aString, long lNum );


BFUTIL_LINKAGE I_STRING word( const I_STRING& aString,
                              unsigned short usWordNum );

BFUTIL_LINKAGE unsigned short words( const I_STRING& aString );

BFUTIL_LINKAGE I_STRING left( const I_STRING& aString,
                              I_STRING::size_type cch );

BFUTIL_LINKAGE I_STRING reverse( const I_STRING& aString );

BFUTIL_LINKAGE I_STRING right( const I_STRING& aString,
                               I_STRING::size_type cch );


#ifdef DST_UNICODE

BFUTIL_LINKAGE unsigned long convertToULong( const DStringA &aString );

BFUTIL_LINKAGE bool isAllDigits( const DStringA &aString );

BFUTIL_LINKAGE bool isDecimal( const DStringA &aString );

BFUTIL_LINKAGE DStringA & lowerCase( DStringA &aString );

BFUTIL_LINKAGE DStringA & padLeft( DStringA &aString,
                                   unsigned long padLength,
                                   char padChar = ' ' );

BFUTIL_LINKAGE DStringA & padRight( DStringA &aString,
                                    unsigned long padLength,
                                    char padChar = ' ' );

BFUTIL_LINKAGE DStringA & strip( DStringA &aString,
                                 char stripChar = ' ' );


BFUTIL_LINKAGE DStringA & stripAll( DStringA &aString,
                                    char stripChar = ' ' );


BFUTIL_LINKAGE DStringA & stripLeading( DStringA &aString,
                                        char stripChar = ' ' );


BFUTIL_LINKAGE DStringA & stripTrailing( DStringA &aString,
                                         char stripChar = ' ' );

BFUTIL_LINKAGE DStringA & upperCase( DStringA &aString );


BFUTIL_LINKAGE int asInteger( const DStringA &aString );

BFUTIL_LINKAGE bool stringHasOnly( const DStringA& aString,
                                   const DStringA& aMask );

BFUTIL_LINKAGE DStringA asAsciiString( int nValue );

BFUTIL_LINKAGE void convertIntToString( int nValue, DStringA & dest );


BFUTIL_LINKAGE DStringA& appendInt( DStringA &aString, int iInt );

BFUTIL_LINKAGE DStringA& appendULong( DStringA &aString,
                                      unsigned long ulNum );

BFUTIL_LINKAGE DStringA& appendLong( DStringA &aString, long lNum );



BFUTIL_LINKAGE DStringA word( const DStringA& aString,
                              unsigned short usWordNum );

BFUTIL_LINKAGE unsigned short words( const DStringA& aString );

BFUTIL_LINKAGE DStringA left( const DStringA& aString,
                              I_STRING::size_type cch );

BFUTIL_LINKAGE DStringA reverse( const DStringA& aString );

BFUTIL_LINKAGE DStringA right( const DStringA& aString,
                               DStringA::size_type cch );


#include <dstringa.hpp>

#endif

}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfstringfunctions.hpp-arc  $
//
//   Rev 1.1   Oct 22 2004 08:59:58   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.0   Apr 11 2003 17:57:02   PURDYECH
//Initial revision.
//
