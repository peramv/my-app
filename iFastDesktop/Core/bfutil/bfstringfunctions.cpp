//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : StringFunctions.cpp
// ^AUTHOR : Paul Dardeau
// ^DATE   : 11/20/96
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "bfstringfunctions.hpp"
#include "localetraits.hpp"

#include <ctype.h>
#include <stdlib.h>


namespace bfutil
{

static I_CHAR szDigits[] = I_( "0123456789" );
static char szAllDigits[] = "0123456789";

static const int s_maxStringSize = 17;

unsigned long convertToULong( const I_STRING & aString )
{
   return(i_strtoul( aString.c_str(), (I_CHAR **)NULL, 10 ));
}


bool isAllDigits( const I_STRING &aString )
{
   const I_CHAR* psz = aString.c_str();
   for( ; *psz != 0x00; ++psz )
   {
      if( !i_isdigit( *psz ) )
      {
         return( false );
      }
   }
   return( true );
}


bool isDecimal( const I_STRING& aString )
{
   I_STRING::size_type strLength = aString.size();

   // If we have a legnth of zero, then the string is not decimal.
   if( 0 == strLength )
   {
      // We are modeling after the constructor for BigDecimal and an empty
      // string is not a decimal number. - DMUM
      return(false);
   }

   // Do locale-dependent initialization.
   const bfutil::LocaleTraits& rTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
   I_CHAR chNegative = rTraits.getNegativeSign();
   I_CHAR chRadix = rTraits.getRadixSeparator();
   I_CHAR chGrouping = rTraits.getGroupSeparator();
   unsigned int cGroupingDigits = rTraits.getGroupDigits();

   // Find a decimal point
   unsigned int decPtPos = aString.find( chRadix );
   bool hasDecimal = I_STRING::npos != decPtPos;

   // Validate the first character
   bool bIsDecimal = true;
   bool hasSign = false;
   I_CHAR firstChar = aString[ 0 ];

   bIsDecimal = 0 != i_isdigit( firstChar );

   // If the first character is not a digit, make sure it is valid.
   if( ! bIsDecimal )
   {
      // Check for negative sign
      if( firstChar == chNegative )
      {
         hasSign = true;

         // Make sure we meet the minimum length
         bIsDecimal = ( hasDecimal ? 2 : 1 ) < strLength;
      }
      // No sign, check for decimal point
      else if( firstChar == chRadix )
      {
         // Make sure we meet the minimum length
         bIsDecimal = 1 < strLength;
      }

      // If we've failed, then go ahead and return the failure.
      if( ! bIsDecimal )
      {
         return(false);
      }
   }

   // If we have a decimal point, validate it.
   if( hasDecimal )
   {
      // Make sure everthing to the right is a digit or the scientific notation indicator.
      enum phase { decimals, e, sign, exp } ePhase = decimals;
      for( int index = decPtPos + 1; index < strLength; ++index )
      {
         switch( ePhase )
         {
            case decimals:
               if( !i_isdigit( aString[ index ] ) ) {
                  ePhase = e;
               } else {
                  continue;
               }
               // fallthrough is intentional!
            case e:
               if( I_( 'e' ) != aString[ index ] &&
                   I_( 'E' ) != aString[ index ] ) {
                  return( false );
               } else { 
                  ePhase = sign;
               }
               break;
            case sign:
               if( I_('+') != aString[index] &&
                   I_('-') != aString[index] )
               {
                  return( false );
               }
               ePhase = exp;
               break;
            case exp:
               if( !i_isdigit( aString[ index ] ) ) {
                  return( false );
               }
               break;
            default:
               assert( 0 );
         }
      }
   }
   else
   {
      decPtPos = strLength;
   }

   // We only need to see if a separator is present at this point
   bool hasSeparator = false;

   if( ( CHAR_MAX != cGroupingDigits ) && ( '\0' != chGrouping ) )
   {
      hasSeparator = I_STRING::npos != aString.find( chGrouping );
   }

   // Check integer part.
   int currentPos = decPtPos - 1;   // Start one position to the left
   const int endPos = hasSign ? 0 : -1;

   while( bIsDecimal && endPos < currentPos )
   {
      // If we have a separator and we are at a separator position then
      // make sure the curent position is a separator
      if( hasSeparator && ( ( decPtPos - currentPos ) == ( 1 + cGroupingDigits ) ) )
      {
         bIsDecimal = aString[ currentPos ] == chGrouping;
         decPtPos = currentPos;
      }
      else
      {
         bIsDecimal = 0 != i_isdigit( aString[ currentPos ] );
      }

      // Go one character to the left.
      --currentPos;
   }

   return(bIsDecimal);
}


I_STRING &lowerCase( I_STRING &aString )
{
   I_CHAR * pszStr = new I_CHAR[ aString.size() + 1 ];
   i_strcpy( pszStr, aString.c_str() );
   i_strlwr( pszStr );
   aString = pszStr;
   delete [] pszStr;
   return(aString);
}


I_STRING &padLeft( I_STRING &aString, I_STRING::size_type cch, I_CHAR padChar )
{
   I_STRING::size_type nStringLen = aString.size();

   if( nStringLen >= cch )
      return(aString);

   I_STRING::size_type nPadChars = cch - nStringLen;

   aString.insert( aString.begin(), nPadChars, padChar );
   return(aString);
}


I_STRING &padRight( I_STRING &aString, I_STRING::size_type cch, I_CHAR padChar )
{
   I_STRING::size_type nStringLen = aString.size();

   if( nStringLen >= cch )
      return(aString);

   I_STRING::size_type nPadChars = cch - nStringLen;

   aString.append( nPadChars, padChar );
   return(aString);
}


I_STRING &strip( I_STRING &aString, I_CHAR stripChar )
{
   return( bfutil::stripLeading( bfutil::stripTrailing( aString, stripChar ), stripChar ));
}


I_STRING &stripAll( I_STRING &aString, I_CHAR stripChar )
{
   I_STRING::size_type nStringLen = aString.size();

   // If string is empty, just return it
   if( nStringLen == 0 )
      return(aString);

   I_CHAR * pszStripChar = NULL;

   // If we don't have any occurrences of the character to strip
   // we can just return
   if( ( pszStripChar =
         const_cast< I_CHAR * >( i_strchr( aString.c_str(),
                                           stripChar ) ) ) == NULL )
   {
      return(aString);
   }


   const I_CHAR * pszOriginal = aString.c_str();
   I_CHAR * pszStripped = new I_CHAR[ nStringLen + 1 ];
   I_CHAR * pszWorking = pszStripped;
   const I_CHAR * pszNonStripChar = NULL;
   pszStripped[ 0 ] = '\0';

   // find the first character to be stripped
   pszStripChar = const_cast< I_CHAR * >( i_strchr( pszOriginal, stripChar ) );
   int nCopyChars;

   if( pszStripChar != pszOriginal )
   {
      nCopyChars = pszStripChar - pszOriginal;

      memcpy( pszWorking, pszOriginal, nCopyChars * sizeof( I_CHAR ) );
      pszWorking += nCopyChars;
      *pszWorking = '\0';
   }


   while( pszStripChar != NULL )
   {
      // advance to the next non-strip character
      while( *pszStripChar == stripChar )
      {
         ++pszStripChar;
      }

      // if we reached the end of the string we need to bail out
      if( ( pszStripChar == NULL ) || ( i_strlen( pszStripChar ) == 0 ) )
      {
         break;
      }

      pszNonStripChar = pszStripChar;

      // advance to the next strip character
      pszStripChar = const_cast< I_CHAR * >( i_strchr( pszNonStripChar, stripChar ) );

      // any strip characters found?
      if( pszStripChar == NULL )
      {
         i_strcat( pszWorking, pszNonStripChar );
         continue;
      }

      nCopyChars = pszStripChar - pszNonStripChar;

      memcpy( pszWorking, pszNonStripChar, nCopyChars * sizeof( I_CHAR ) );
      pszWorking += nCopyChars;
      *pszWorking = '\0';
   }

   aString = pszStripped;

   delete [] pszStripped;

   return(aString);
}


I_STRING &stripLeading( I_STRING &aString, I_CHAR stripChar )
{
   // This is faster than find_first_not_of
   int stripLen = 0;
   int strLen = aString.size();
   if( strLen == 0 )
   {
      return(aString);
   }
   while( stripLen < strLen && aString[ stripLen ] == stripChar )
   {
      stripLen++;
   }
   if( stripLen != I_STRING::npos )
   {
      aString.erase( 0, stripLen );
   }
   return(aString);
}


I_STRING &stripTrailing( I_STRING &aString, I_CHAR stripChar )
{
   // This is faster than find_last_not_of
   int stripPos = aString.size();
   if( stripPos == 0 )
   {
      return(aString);
   }

   while( --stripPos >= 0 && aString[ stripPos ] == stripChar )
   {
   }
   aString.erase( stripPos + 1 );
   return(aString);
}


I_STRING &upperCase( I_STRING &aString )
{
   I_CHAR * pszStr = new I_CHAR[ aString.size() + 1 ];
   i_strcpy( pszStr, aString.c_str() );
   i_strupr( pszStr );
   aString = pszStr;
   delete [] pszStr;
   return(aString);
}




int asInteger( const I_STRING &aString )
{
   return(i_ttoi( aString.c_str() ));
}


bool stringHasOnly( const I_STRING &aString, const I_STRING &aMask )
{
   return( i_strspn( aString.c_str(), aMask.c_str() ) ==
           i_strlen( aString.c_str() ) );
}


I_STRING asString( DIINT64 nValue )
{
   I_CHAR szValue[ s_maxStringSize + 10 ];
   return(I_STRING( i_i64tot( nValue, szValue, 10 ) )); //convert big integer to DString
}


I_STRING floatAsString( double nValue )
{
   char szValue[ s_maxStringSize + 1 ];
   I_STRING saveString;
   _gcvt( nValue, s_maxStringSize, szValue );
#ifdef DST_UNICODE
   asciistringToUnicodestring( szValue, saveString );
#else
   saveString = szValue;
#endif
   return(saveString); //convert int to DStringA
}


void convertIntToString( int nValue, I_STRING & dest )
{
   I_CHAR szValue[ s_maxStringSize + 1 ];

   dest = I_STRING( i_itot( nValue, szValue, 10 ) ); //convert int to DStringA
}




I_STRING& appendInt( I_STRING &aString, int iInt )
{
   I_CHAR szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_itot( iInt, szValue, 10 ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}


I_STRING& appendULong( I_STRING &aString, unsigned long ulNum )
{
   I_CHAR szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_sprintf( szValue, I_( "%lu" ), ulNum ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}


I_STRING& appendLong( I_STRING &aString, long lNum )
{
   I_CHAR szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_sprintf( szValue, I_( "%ld" ), lNum ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}





I_STRING word( const I_STRING & aString, unsigned short usWordNum )
{
   I_STRING::size_type nStartPos = 0;
   I_STRING::size_type nEndPos = 0;

   for( unsigned short usWord = 0; usWord <= usWordNum; ++usWord )
   {
      // find the next non-blank character
      nStartPos = aString.find_first_not_of( ' ', nEndPos );

      if( I_STRING::npos == nStartPos )
         return(I_STRING( I_( "" ) ));

      // find the next blank character
      nEndPos = aString.find( ' ', nStartPos );

      if( I_STRING::npos == nEndPos && usWord < usWordNum )
         return(I_STRING( I_( "" ) ));
   }

   return(aString.substr( nStartPos, nEndPos - nStartPos ));
}


unsigned short words( const I_STRING & aString )
{
   unsigned short usWordNum = 0;

   while( word( aString, usWordNum++ ).size() > 0 );

   return(--usWordNum);
}


I_STRING left( const I_STRING& aString, I_STRING::size_type cch )
{
   // If the length of the string is less than the desired length
   // pad the string on the right with spaces
   if( aString.size() < cch )
   {
      I_STRING strNewString( aString );
      padLeft( strNewString, cch, ' ' );
      return(strNewString);
   }
   else if( aString.size() == cch )
      return(aString);
   else
   {
      return(aString.substr( 0, cch ));
   }
}


I_STRING reverse( const I_STRING& aString )
{
   I_STRING strReversed;

   I_STRING::size_type nStringLength = aString.size();

   for( int i = nStringLength - 1; i >= 0; --i )
   {
      strReversed += aString[i];
   }

   return(strReversed);
}


I_STRING right( const I_STRING& aString, I_STRING::size_type cch )
{
   I_STRING::size_type l = aString.size();
   if( l <= cch )
   {
      return( aString );
   }
   return( I_STRING( aString.c_str() + ( l - cch ) ) );
}



#ifdef DST_UNICODE

// This section is for internal, non-Unicode string support

unsigned long convertToULong( const DStringA & aString )
{
   return( strtoul( aString.c_str(), (char **)NULL, 10 ) );
}


bool isAllDigits( const DStringA &aString )
{
   return( strspn( aString.c_str(), szAllDigits ) == strlen( aString.c_str() ) );
}


bool isDecimal( const DStringA & aString )
{
   DStringA::size_type strLength = aString.size();

   // If we have a legnth of zero, then the string is not decimal.
   if( 0 == strLength )
   {
      // We are modeling after the constructor for BigDecimal and an empty
      // string is not a decimal number. - DMUM
      return(false);
   }

   // Do locale-dependent initialization.
   const bfutil::LocaleTraits& rTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
   I_CHAR chNegative = rTraits.getNegativeSign();
   I_CHAR chRadix = rTraits.getRadixSeparator();
   I_CHAR chGrouping = rTraits.getGroupSeparator();
   unsigned int cGroupingDigits = rTraits.getGroupDigits();

   // Find a decimal point
#pragma warning( push )
#pragma warning( disable: 4244 )
   unsigned int decPtPos = aString.find( chRadix );
#pragma warning( pop )
   bool hasDecimal = I_STRING::npos != decPtPos;

   // Validate the first character
   bool isDecimal = true;
   bool hasSign = false;
   I_CHAR firstChar = aString[ 0 ];

   isDecimal = 0 != i_isdigit( firstChar );

   // If the first character is not a digit, make sure it is valid.
   if( ! isDecimal )
   {
      // Check for negative sign
      if( firstChar == chNegative )
      {
         hasSign = true;

         // Make sure we meet the minimum length
         isDecimal = ( hasDecimal ? 2 : 1 ) < strLength;
      }
      // No sign, check for decimal point
      else if( firstChar == chRadix )
      {
         // Make sure we meet the minimum length
         isDecimal = 1 < strLength;
      }

      // If we've failed, then go ahead and return the failure.
      if( ! isDecimal )
      {
         return(false);
      }
   }

   // If we have a decimal point, validate it.
   if( hasDecimal )
   {
      enum phase { decimals, e, sign, exp } ePhase = decimals;
      for( int index = decPtPos + 1; index < strLength; ++index )
      {
         switch( ePhase )
         {
            case decimals:
               if( !i_isdigit( aString[ index ] ) ) {
                  ePhase = e;
               } else {
                  continue;
               }
               // fallthrough is intentional!
            case e:
               if( I_( 'e' ) != aString[ index ] &&
                   I_( 'E' ) != aString[ index ] ) {
                  return( false );
               } else { 
                  ePhase = sign;
               }
               break;
            case sign:
               if( I_('+') != aString[index] &&
                   I_('-') != aString[index] )
               {
                  return( false );
               }
               ePhase = exp;
               break;
            case exp:
               if( !i_isdigit( aString[ index ] ) ) {
                  return( false );
               }
               break;
            default:
               assert( 0 );
         }
      }
   }
   else
   {
      decPtPos = strLength;
   }

   // We only need to see if a separator is present at this point
   bool hasSeparator = false;

   if( ( CHAR_MAX != cGroupingDigits ) && ( '\0' != chGrouping ) )
   {
#pragma warning( push )
#pragma warning( disable: 4244 )
      hasSeparator = I_STRING::npos != aString.find( chGrouping );
#pragma warning( pop )
   }

   // Check integer part.
   int currentPos = decPtPos - 1;   // Start one position to the left
   const int endPos = hasSign ? 0 : -1;

   while( isDecimal && endPos < currentPos )
   {
      // If we have a separator and we are at a separator position then
      // make sure the curent position is a separator
      if( hasSeparator && ( ( decPtPos - currentPos ) == ( 1 + cGroupingDigits ) ) )
      {
         isDecimal = aString[ currentPos ] == chGrouping;
         decPtPos = currentPos;
      }
      else
      {
         isDecimal = 0 != i_isdigit( aString[ currentPos ] );
      }

      // Go one character to the left.
      --currentPos;
   }

   return(isDecimal);
}


DStringA &lowerCase( DStringA &aString )
{
   char * pszStr = new char[ aString.size() + 1 ];

   strcpy( pszStr, aString.c_str() );

   strlwr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}


DStringA &padLeft( DStringA &aString, DStringA::size_type cch, char padChar )
{
   DStringA::size_type nStringLen = aString.size();

   if( nStringLen >= cch )
      return(aString);

   DStringA::size_type nPadChars = cch - nStringLen;

   char * pszPadded = new char[ cch + 1 ];
   memset( pszPadded, padChar, nPadChars );
   pszPadded[ nPadChars ] = '\0';
   strcat( pszPadded, aString.c_str() );
   aString = pszPadded;
   delete [] pszPadded;

   return(aString);
}


DStringA &padRight( DStringA &aString, DStringA::size_type cch, char padChar )
{
   DStringA::size_type nStringLen = aString.size();

   if( nStringLen >= cch )
      return(aString);

   DStringA::size_type nPadChars = cch - nStringLen;

   char * pszPadded = new char[ cch + 1 ];

   strcpy( pszPadded, aString.c_str() );
   memset( pszPadded + nStringLen, padChar, nPadChars );
   pszPadded[ cch ] = '\0';

   aString = pszPadded;

   delete [] pszPadded;

   return(aString);
}



DStringA &strip( DStringA &aString, char stripChar )
{
   return( bfutil::stripLeading( bfutil::stripTrailing( aString, stripChar ), stripChar ));
}


DStringA &stripAll( DStringA &aString, char stripChar )
{
   DStringA::size_type nStringLen = aString.size();

   // If string is empty, just return it
   if( nStringLen == 0 )
      return(aString);

   const char * pszStripChar = NULL;

   // If we don't have any occurrences of the character to strip
   // we can just return
   if( ( pszStripChar = strchr( aString.c_str(), stripChar ) ) == NULL )
   {
      return(aString);
   }


   const char * pszOriginal = aString.c_str();
   char * pszStripped = new char[ nStringLen + 1 ];
   char * pszWorking = pszStripped;
   const char * pszNonStripChar = NULL;
   pszStripped[ 0 ] = '\0';

   // find the first character to be stripped
   pszStripChar = strchr( pszOriginal, stripChar );
   int nCopyChars;

   if( pszStripChar != pszOriginal )
   {
      nCopyChars = pszStripChar - pszOriginal;

      memcpy( pszWorking, pszOriginal, nCopyChars );
      pszWorking += nCopyChars;
      *pszWorking = '\0';
   }


   while( pszStripChar != NULL )
   {
      // advance to the next non-strip character
      while( *pszStripChar == stripChar )
      {
         ++pszStripChar;
      }

      // if we reached the end of the string we need to bail out
      if( ( pszStripChar == NULL ) || ( strlen( pszStripChar ) == 0 ) )
      {
         break;
      }

      pszNonStripChar = pszStripChar;

      // advance to the next strip character
      pszStripChar = strchr( pszNonStripChar, stripChar );

      // any strip characters found?
      if( pszStripChar == NULL )
      {
         strcat( pszWorking, pszNonStripChar );
         continue;
      }

      nCopyChars = pszStripChar - pszNonStripChar;

      memcpy( pszWorking, pszNonStripChar, nCopyChars );
      pszWorking += nCopyChars;
      *pszWorking = '\0';
   }

   aString = pszStripped;

   delete [] pszStripped;

   return(aString);
}


DStringA &stripLeading( DStringA &aString, char stripChar )
{
   DStringA::size_type nStringLen = aString.size();

   // If string is empty, just return it
   if( nStringLen == 0 )
      return(aString);

   int nLeadingStripChars = 0;
   const char * pszOrig = aString.c_str();

   while( pszOrig[ nLeadingStripChars ] == stripChar )
   {
      ++nLeadingStripChars;
   }

   // Any leading characters to strip?
   if( nLeadingStripChars > 0 )
   {
      // Do all of the characters need to be stripped?
      if( nLeadingStripChars == nStringLen )
      {
         aString = "";
      }
      else
      {
         // not all of the characters are being stripped
         int nNewLengthWithNull = nStringLen - nLeadingStripChars + 1;

         char szTmp[30];

         char * pszStripped = &szTmp[0];
         bool fBufferAllocated = false;

         if( nNewLengthWithNull > 30 )
         {
            pszStripped = new char[ nNewLengthWithNull ];
            fBufferAllocated = true;
         }
         memcpy( pszStripped,
                 pszOrig + nLeadingStripChars,
                 nNewLengthWithNull );
         aString = pszStripped;
         if( fBufferAllocated )
         {
            delete [] pszStripped;
         }
      }
   }
   return(aString);
}


DStringA &stripTrailing( DStringA &aString, char stripChar )
{
   DStringA::size_type nStringLen = aString.size();

   // If string is empty, just return it
   if( nStringLen == 0 )
      return(aString);

   const char * pszOrig = aString.c_str();
   int nNewLength = nStringLen - 1;   // start at last character before NULL

   // Find out how many trailing characters we have
   while( ( 0 <= nNewLength ) && ( pszOrig[nNewLength] == stripChar ) )
   {
      --nNewLength;
   }


   ++nNewLength;


   // Did we not have any characters to strip?
   if( nNewLength == nStringLen )
   {
      return(aString);
   }

   char szTmp[30];

   char * pszWork = &szTmp[0];
   bool fBufferAllocated = false;

   if( nNewLength > 29 )
   {
      pszWork = new char[ nNewLength + 1 ];
      fBufferAllocated = true;
   }

   // copy all characters except the trailing ones to strip
   memcpy( pszWork, pszOrig, nNewLength );
   pszWork[ nNewLength ] = '\0';

   aString = pszWork;

   if( fBufferAllocated )
   {
      delete [] pszWork;
   }

   return(aString);
}


DStringA &upperCase( DStringA &aString )
{
   char * pszStr = new char[ aString.size() + 1 ];

   strcpy( pszStr, aString.c_str() );

   strupr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}




int asInteger( const DStringA &aString )
{
   return(atoi( aString.c_str() ));
}


bool stringHasOnly( const DStringA &aString, const DStringA &aMask )
{
   return( strspn( aString.c_str(), aMask.c_str() ) ==
           strlen( aString.c_str() ) );
}


// should we be returning a string on the stack instead of allocating it?
// this has the potential to be a performance bottleneck
DStringA asAsciiString( int nValue )
{
   char szValue[ s_maxStringSize + 1 ];
   // don't need to memset
   //memset( szValue, 0, 30 * sizeof( char ) ); // clear memory
   return(DStringA( itoa( nValue, szValue, 10 ) )); //convert int to DStringA
}


void convertIntToString( int nValue, DStringA & dest )
{
   char szValue[ s_maxStringSize + 1 ];

   dest = DStringA( itoa( nValue, szValue, 10 ) ); //convert int to DStringA
}




DStringA& appendInt( DStringA &aString, int iInt )
{
   char szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   itoa( iInt, szValue, 10 ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}


DStringA& appendULong( DStringA &aString, unsigned long ulNum )
{
   char szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   sprintf( szValue, "%lu", ulNum ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}


DStringA& appendLong( DStringA &aString, long lNum )
{
   char szValue[ s_maxStringSize + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   sprintf( szValue, "%ld", lNum ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}








DStringA word( const DStringA & aString, unsigned short usWordNum )
{
   DStringA::size_type nStartPos = 0;
   DStringA::size_type nEndPos = 0;

   for( unsigned short usWord = 0; usWord <= usWordNum; ++usWord )
   {
      // find the next non-blank character
      nStartPos = aString.find_first_not_of( ' ', nEndPos );

      if( DStringA::npos == nStartPos )
         return(DStringA( "" ));

      // find the next blank character
      nEndPos = aString.find( ' ', nStartPos );

      if( DStringA::npos == nEndPos && usWord < usWordNum )
         return(DStringA( "" ));
   }

   return(aString.substr( nStartPos, nEndPos - nStartPos ));
}


unsigned short words( const DStringA & aString )
{
   unsigned short usWordNum = 0;

   while( bfutil::word( aString, usWordNum++ ).size() > 0 );

   return(--usWordNum);
}


DStringA left( const DStringA& aString, DStringA::size_type cch )
{
   // If the length of the string is less than the desired length
   // pad the string on the right with spaces
   if( aString.size() < cch )
   {
      DStringA strNewString( aString );
      padLeft( strNewString, cch, ' ' );
      return(strNewString);
   }
   else if( aString.size() == cch )
      return(aString);
   else
   {
      return(aString.substr( 0, cch ));
   }
}


DStringA reverse( const DStringA& aString )
{
   DStringA strReversed;

   DStringA::size_type nStringLength = aString.size();

   for( DStringA::size_type i = nStringLength - 1; i >= 0; --i )
   {
      strReversed += aString[i];
   }

   return(strReversed);
}


DStringA right( const DString& aString, DStringA::size_type cch )
{
   DStringA::size_type l = aString.size();
   if( l <= cch )
   {
      return( aString );
   }
   return( DStringA( aString.c_str() + ( l - cch ) ) );
}


#endif

}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfstringfunctions.cpp-arc  $
//
//   Rev 1.1   Oct 22 2004 08:59:56   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.0   Apr 11 2003 17:56:56   PURDYECH
// Initial revision.
//
