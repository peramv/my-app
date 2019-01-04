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
#define DICORE_DLL

#pragma warning( disable: 4018 )

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H
#include <ctype.h>
#endif
#ifndef INCLUDED_STDLIB_H
#define INCLUDED_STDLIB_H
#include <stdlib.h>
#endif

#ifndef INCLUDED_STRINGFUNCTIONS
#define INCLUDED_STRINGFUNCTIONS
#include "stringfunctions.hpp"
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
#include "dstringa.hpp"
#endif

static I_CHAR szDigits[] = I_( "0123456789" );
static char szAllDigits[] = "0123456789";

#define MAX_STRING_SIZE 17


unsigned long convertToULong( const I_STRING & aString )
{
   return(i_strtoul( aString.c_str(), (I_CHAR **)NULL, 10 ));
}


bool isAllDigits( const I_STRING &aString )
{
   return( i_strspn( aString.c_str(), szDigits ) ==
           i_strlen( aString.c_str() ) );
}


bool isDecimal( const I_STRING & aString )
{
   const unsigned int strLength = aString.length();

   // If we have a legnth of zero, then the string is not decimal.
   if( 0 == strLength )
   {
      // We are modeling after the constructor for BigDecimal and an empty
      // string is not a decimal number. - DMUM
      return(false);
   }

   // Do locale-dependent initialization.
   I_CHAR DECIMAL_POINT;
   I_CHAR DIGIT_SEPARATOR;
   I_CHAR NEGATIVE_SIGN;
   char GROUPING;

   struct lconv * plc = localeconv();

   DIGIT_SEPARATOR = *( plc->mon_thousands_sep );
   DECIMAL_POINT = *( plc->mon_decimal_point );
   NEGATIVE_SIGN = *( plc->negative_sign );
   GROUPING = *( plc->mon_grouping );

   // is this the 'C' locale; if so, use English characters
   if( '\0' == DIGIT_SEPARATOR )
   {
      DIGIT_SEPARATOR = ',';
      DECIMAL_POINT = '.';
      NEGATIVE_SIGN = '-';
      GROUPING = 3;
   }

   // Find a decimal point
   unsigned int decPtPos = aString.find( DECIMAL_POINT );
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
      if( firstChar == NEGATIVE_SIGN )
      {
         hasSign = true;

         // Make sure we meet the minimum length
         isDecimal = ( hasDecimal ? (unsigned)2 : (unsigned)1 ) < strLength;
      }
      // No sign, check for decimal point
      else if( firstChar == DECIMAL_POINT )
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
      // Make sure everthing to the right is a digit.
      for( int index = decPtPos + 1; index < strLength; ++index )
      {
         if( 0 == i_isdigit( aString[ index ] ) )
         {
            return(false);
         }
      }
   }
   else
   {
      decPtPos = strLength;
   }

   // We only need to see if a separator is present at this point
   bool hasSeparator = false;

   if( ( CHAR_MAX != GROUPING ) && ( '\0' != DIGIT_SEPARATOR ) )
   {
      hasSeparator = I_STRING::npos != aString.find( DIGIT_SEPARATOR );
   }

   // Check integer part.
   int currentPos = decPtPos - 1;   // Start one position to the left
   const int endPos = hasSign ? 0 : -1;

   while( isDecimal && endPos < currentPos )
   {
      // If we have a separator and we are at a separator position then
      // make sure the curent position is a separator
      if( hasSeparator && ( ( decPtPos - currentPos ) == ( 1 + GROUPING ) ) )
      {
         isDecimal = aString[ currentPos ] == DIGIT_SEPARATOR;
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


I_STRING &lowerCase( I_STRING &aString )
{
   I_CHAR * pszStr = new I_CHAR[ aString.length() + 1 ];

   i_strcpy( pszStr, aString.c_str() );

   i_strlwr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}


I_STRING &padLeft( I_STRING &aString, unsigned long padLength, I_CHAR padChar )
{
   int nStringLen = aString.length();

   if( nStringLen >= padLength )
      return(aString);

   int nPadChars = padLength - nStringLen;

   aString.insert( aString.begin(), nPadChars, padChar );
   return(aString);
}


I_STRING &padRight( I_STRING &aString, unsigned long padLength, I_CHAR padChar )
{
   int nStringLen = aString.length();

   if( nStringLen >= padLength )
      return(aString);

   int nPadChars = padLength - nStringLen;

   aString.append( nPadChars, padChar );
   return(aString);
}


I_STRING &strip( I_STRING &aString, I_CHAR stripChar )
{
   return(stripLeading( stripTrailing( aString, stripChar ), stripChar ));
}


I_STRING &stripAll( I_STRING &aString, I_CHAR stripChar )
{
   int nStringLen = aString.length();

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
   I_CHAR * pszStr = new I_CHAR[ aString.length() + 1 ];

   i_strcpy( pszStr, aString.c_str() );

   i_strupr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}


I_STRING addTwoStrings( const I_STRING &firstValue, const I_STRING &secondValue )
{
   I_STRING::size_type firstLength, secondLength, counter;
   int carryValue, value1, value2, newValue;
   I_STRING newValueString, returnVal, adjustedFirstValue, adjustedSecondValue;
   I_CHAR abuff[3], bbuff[3];

   firstLength = firstValue.length();
   secondLength = secondValue.length();
   carryValue = 0;
   adjustedFirstValue = firstValue;
   adjustedSecondValue = secondValue;

   if( firstLength > secondLength )
   {
      padLeft( adjustedSecondValue, firstLength, '0' );
   }
   else
   {
      padLeft( adjustedFirstValue, secondLength, '0' );
   }

   firstLength = adjustedFirstValue.length();
   secondLength = adjustedSecondValue.length();

   for( counter = 1; counter <= firstLength; ++counter )
   {
      i_sprintf( bbuff, I_( "%c" ), adjustedFirstValue[ firstLength - counter ] );
      value1 = i_ttoi( bbuff );
      i_sprintf( bbuff, I_( "%c" ), adjustedSecondValue[ secondLength - counter ] );
      value2 = i_ttoi( bbuff );

      newValue = value1 + value2 + carryValue;
      if( newValue > 9 )
      {
         carryValue = 1;
         i_sprintf( abuff, I_( "%d" ), newValue - 10 );
      }
      else
      {
         carryValue = 0;
         i_sprintf( abuff, I_( "%d" ), newValue );
      }
      newValueString = abuff;
      returnVal = newValueString + returnVal;
   }
   if( carryValue > 0 )
   {
      i_sprintf( abuff, I_( "%d" ), carryValue );
      newValueString = abuff;
      returnVal = newValueString + returnVal;
   }

   return(returnVal);
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
   I_CHAR szValue[ MAX_STRING_SIZE + 10 ];
   return(I_STRING( i_i64tot( nValue, szValue, 10 ) )); //convert double to DStringA
}


I_STRING floatAsString( double nValue )
{
   char szValue[ MAX_STRING_SIZE + 1 ];
   I_STRING saveString;
   _gcvt( nValue, MAX_STRING_SIZE, szValue );
#ifdef DST_UNICODE
   asciistringToUnicodestring( szValue, saveString );
#else
   saveString = szValue;
#endif
   return(saveString); //convert int to DStringA
}


void convertIntToString( int nValue, I_STRING & dest )
{
   I_CHAR szValue[ MAX_STRING_SIZE + 1 ];

   dest = I_STRING( i_itot( nValue, szValue, 10 ) ); //convert int to DStringA
}


I_STRING & formatStringUsingMask( I_STRING &valueString, const I_STRING &mask )
{
   I_STRING newValue( mask.length(), ' ' ),
   maskVals( I_( "A9#XZ$%" ) );
   long  valDecimalPosition = 0, maskDecimalPosition = 0, srcOffset = 0,
   targetOffset = 0, maskOffset = 0, maskValsLen = 0, valLen = 0,
   maskLen = 0;
   I_CHAR thisMaskChar;
   bool isNegative = false;

   I_CHAR fractSepSymbolStr[ 2 ]; // get fractional separator symbol from locale
   I_CHAR currencySymbolStr[ 2 ]; // get currency symbol from locale
   struct lconv * lc = localeconv( );
   fractSepSymbolStr[ 0 ] = lc->decimal_point[ 0 ];
   fractSepSymbolStr[ 1 ] = '\0';
   currencySymbolStr[ 0 ] = lc->currency_symbol[ 0 ];
   currencySymbolStr[ 1 ] = '\0';

   maskLen = mask.length();
   maskValsLen = maskVals.length();

   if( maskLen > 0 )
   {
      if( ( ( I_STRING::npos != mask.find( I_( "$" ) )) ||
            ( I_STRING::npos != mask.find( I_( "9" ) )) ||
            ( I_STRING::npos != mask.find( I_( "%" )))) &&
          I_STRING::npos != mask.find( I_( "." ) ) )
      {
         strip( valueString );
         if( I_STRING::npos == mask.find_first_not_of( I_( "%." ) ) )
         {
            stripAll( valueString, '%' );
            // Yeah, it's a mess.  So what?

            // vintage Chris...

            if( I_STRING::npos == valueString.find( fractSepSymbolStr ) )
            {
               valueString += fractSepSymbolStr;
            }
            I_STRING strippedMask( mask );
            strip( strippedMask );
            if( valueString.length() < strippedMask.length() )
            {
               long beforeDec = strippedMask.find( I_( "." ) );
               long afterDec = strippedMask.length() - ( beforeDec + 1 );
               long valueBeforeDec = valueString.find( fractSepSymbolStr );
               long valueAfterDec = valueString.length() - ( valueBeforeDec + 1 );
               if( valueBeforeDec < beforeDec )
               {
                  padLeft( valueString, ( valueString.length() + ( beforeDec - valueBeforeDec )), '0' );
               }
               if( valueAfterDec < afterDec )
               {
                  padRight( valueString, ( valueString.length() + ( afterDec - valueAfterDec )), '0' );
               }
            }
            long newLen = valueString.length();
            long decPlace = valueString.find( fractSepSymbolStr );
            long afterDecimal = newLen - ( decPlace - 1 );
            if( afterDecimal < 2 )
            {
               padRight( valueString, ( 2 - afterDecimal ), '0' );
            }
            valueString.insert( decPlace + 3, fractSepSymbolStr );
            valueString.erase( decPlace, 1 );
         }
         if( I_STRING::npos != valueString.find( I_( "-" )) )
         {
            isNegative = true;
            valueString = valueString.substr( 1 );
         }

         long oldDecPlace = valueString.find( fractSepSymbolStr );
         if( I_STRING::npos != oldDecPlace )
         {
            stripLeading( valueString, '0' );
            if( valueString.find( fractSepSymbolStr ) == 0 )
            {
               valueString = I_( "0" ) + valueString;
            }
         }

         valLen = valueString.length();
         if( I_STRING::npos == ( maskOffset = mask.find( I_( "." ))) )
         {
            maskOffset = maskLen - 1;
         }

         targetOffset = maskOffset;

         if( I_STRING::npos != ( srcOffset = valueString.find( fractSepSymbolStr )) )
         {
            valDecimalPosition = srcOffset--;
         }
         else
         {
            srcOffset = valDecimalPosition = valLen - 1;
         }

         maskDecimalPosition = maskOffset;

         while( maskOffset >= 0 )
         {
            thisMaskChar = mask[ maskOffset ];
            if( I_STRING::npos != maskVals.find( thisMaskChar ) )
            {
               if( srcOffset >= 0 )
               {
                  newValue[ targetOffset-- ] = valueString[ srcOffset-- ];
               }
               else
               {
                  switch( thisMaskChar )
                  {
                     case '$' :
                        newValue[ targetOffset-- ] = currencySymbolStr[ 0 ];
                        maskOffset = 0;
                        break;

                     case '.' :
                        newValue[ targetOffset-- ] = fractSepSymbolStr[ 0 ];
                        break;

                     case 'Z':
                        newValue[ targetOffset-- ] = '0';
                        break;

                     default:
                        newValue[ targetOffset-- ] = ' ';
                        break;
                  } // switch
               } // if - else
            }
            else
            {
               if( srcOffset >= 0 )
               {
                  if( '-' != valueString[ srcOffset ] )
                  {
                     newValue[ targetOffset-- ] = thisMaskChar;
                  }
                  else if( '.' == thisMaskChar )
                  {
                     newValue[ targetOffset-- ] = fractSepSymbolStr[ 0 ];
                  }
                  else if( ',' == thisMaskChar )
                  {
                     switch( mask[ maskOffset + 1 ] )
                     {
                        case '$':
                           newValue[ targetOffset-- ] = currencySymbolStr[ 0 ];
                           maskOffset = 0;
                           break;

                        case 'Z':
                           // we have to special case locale-dependent characters fractSepSymbolStr and currencySymbolStr
                           I_CHAR replaceChar;
                           switch( thisMaskChar )
                           {
                              case '$':
                                 replaceChar = currencySymbolStr[ 0 ];
                                 break;
                              case '.':
                                 replaceChar = fractSepSymbolStr[ 0 ];
                                 break;
                              default:
                                 replaceChar =  thisMaskChar;
                                 break;
                           }
                           newValue[ targetOffset-- ] = replaceChar;
                           break;

                        default:
                           newValue[ targetOffset-- ] = ' ';
                           break;
                     } // switch
                  } // if-else
               }
            } // if ( DStringA::npos != maskVals.find( thisMaskChar ))
            maskOffset--;
         }
         maskOffset = targetOffset = ( maskDecimalPosition + 1 );
         srcOffset = ( valDecimalPosition + 1 );

         while( maskOffset < maskLen )
         {
            thisMaskChar = mask[ maskOffset ];
            if( I_STRING::npos != maskVals.find( thisMaskChar ) )
            {
               if( srcOffset < valLen )
               {
                  newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
               }
               else
               {
                  newValue[ targetOffset++ ] = '0';
               }
            }
            else
            {
               newValue[ targetOffset++ ] = thisMaskChar;
            }
            ++maskOffset;
         } // while

         if( isNegative )
         {
            unsigned long firstNonSpace = newValue.find_first_not_of( ' ' );
            if( 0 == firstNonSpace )
            {
               newValue = I_( "-" ) + newValue;
            }
            else
            {
               newValue[ firstNonSpace - 1 ] = '-';
            }
         }
         valueString = newValue;
      }
      else
      {
         valLen = valueString.length();
         while( maskOffset < maskLen )
         {
            if( I_STRING::npos != maskVals.find( mask[ maskOffset ] ) )
            {
               if( srcOffset < valLen )
               {
                  newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
               }
               else
               {
                  newValue[ targetOffset++ ] = ' ';
               }
            }
            else
            {
               newValue[ targetOffset++ ] = mask[ maskOffset ];
            }
            ++maskOffset;
         }
         valueString = newValue;
      }
   }
   return(valueString);
}


I_STRING &removeMaskFromString( I_STRING &maskedValue, const I_STRING &mask )
{
   long valLength = maskedValue.length();
   long maskLength = mask.length();
   I_STRING targetValue( maskLength + 1, ' ' ), maskVals( I_( "A9#XZ$%" ) );
   I_CHAR fractSepSymbolStr[ 2 ]; // get fractional separator symbol from locale
   I_CHAR currencySymbolStr[ 2 ]; // get currency symbol from locale
   setlocale( LC_ALL, NULL );
   struct lconv * lc = localeconv( );
   fractSepSymbolStr[ 0 ] = lc->decimal_point[ 0 ];
   fractSepSymbolStr[ 1 ] = '\0';
   currencySymbolStr[ 0 ] = lc->currency_symbol[ 0 ];
   currencySymbolStr[ 1 ] = '\0';

   if( ( I_STRING::npos != mask.find( I_( "$" ) ) || I_STRING::npos != mask.find( I_( "9" ) ) ||
         I_STRING::npos != mask.find( I_( "%" ) ) ) && ( I_STRING::npos != mask.find( I_( "." ))) )
   {
      I_STRING thisMask( mask );
      if( I_STRING::npos != thisMask.find_first_not_of( I_( "%." )) )
      {
         if( I_STRING::npos == thisMask.find( I_( "." )) )
         {
            stripTrailing( thisMask );
            thisMask = thisMask + I_( "." );
            maskLength = thisMask.length();
            targetValue += I_( " " );
         }
         if( I_STRING::npos == maskedValue.find( fractSepSymbolStr ) )
         {
            stripTrailing( maskedValue );
            maskedValue = maskedValue + fractSepSymbolStr;
            valLength = maskedValue.length();
         }
         long srcDecPos = maskedValue.find( fractSepSymbolStr );
         long maskDecPos = thisMask.find( I_( "." ) );
         long srcOffset = srcDecPos;
         long maskOffset = maskDecPos;
         bool hasDec = ( srcOffset >= 0 || maskOffset >= 0 );
         long targetOffset = maskOffset;

         if( hasDec )
         {
            while( srcOffset >= 0 && maskOffset >= 0 )
            {
               I_CHAR maskedAtOffset = maskedValue[ srcOffset ];
               if( isdigit( maskedAtOffset ) )
               {
                  targetValue[ targetOffset-- ] = maskedAtOffset;
               }
               else
               {
                  if( maskedAtOffset != thisMask[ maskOffset ] )
                  {
                     if( maskedAtOffset != fractSepSymbolStr[ 0 ] ||
                         maskOffset == 0 ||
                         thisMask[ maskOffset - 1 ] != '$' )
                     {
                        targetValue[ targetOffset-- ] = maskedAtOffset;
                     }
                  }
               }
               srcOffset--;
               maskOffset--;
            }
         }
         srcOffset = srcDecPos + 1;
         maskOffset = targetOffset = ( maskDecPos + 1 );
         if( hasDec )
         {
            // TO DO:
            targetValue[ targetOffset++ ] = '.'; // get fractional separator symbol from locale
         }
         while( srcOffset < valLength && maskOffset < maskLength
                && targetOffset < ( maskLength + 1 ) )
         {
            I_CHAR maskedAtOffset = maskedValue[ srcOffset ];
            if( isdigit( maskedAtOffset ) ||
                ( maskedAtOffset != thisMask[ maskOffset ] ) )
            {
               targetValue[ targetOffset++ ] = maskedAtOffset;
            }
            ++srcOffset;
            ++maskOffset;
         }
      }
      else
      {
         stripAll( maskedValue, '%' );
         targetValue = maskedValue;
      }
      strip( targetValue );
   }
   else
   {
      long srcOffset = 0;
      long maskOffset = 0;
      long targetOffset = 0;
      while( srcOffset < valLength && maskOffset < maskLength )
      {
         I_CHAR maskedAtOffset = maskedValue[ srcOffset ];
         I_CHAR maskChar = mask[ maskOffset ];
         if( ( maskChar == '9' && isdigit( maskedAtOffset ) ) ||
             (( maskChar == 'X' || maskChar == 'A' || maskChar == 'Z' ) &&
              !isdigit( maskedAtOffset )) ||
             maskedAtOffset != maskChar )
         {
            targetValue[ targetOffset++ ] = maskedAtOffset;
         }
         ++srcOffset;
         ++maskOffset;
      }
      strip( targetValue );
   }
   maskedValue = targetValue;
   return(maskedValue);
}


I_STRING& appendInt( I_STRING &aString, int iInt )
{
   I_CHAR szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_itot( iInt, szValue, 10 ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}


I_STRING& appendULong( I_STRING &aString, unsigned long ulNum )
{
   I_CHAR szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_sprintf( szValue, I_( "%lu" ), ulNum ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}


I_STRING& appendLong( I_STRING &aString, long lNum )
{
   I_CHAR szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   i_sprintf( szValue, I_( "%ld" ), lNum ); //convert int DStringA
   return(aString += szValue); //return the DStringA contents
}


int pos( I_CHAR ch, const I_STRING& aString )
{
   I_STRING::size_type nStartChar = aString.find( ch );

   if( I_STRING::npos == nStartChar )
      return(-1);
   else
      return(nStartChar);
}


int pos( const I_STRING& strSubString, const I_STRING& strFullString )
{
   I_STRING::size_type nStartSubString = strFullString.find( strSubString );

   if( I_STRING::npos == nStartSubString )
      return(-1);
   else
      return(nStartSubString);
}


I_STRING makeIstringRepeatChar( I_CHAR ch, unsigned short usNumChars )
{
   return(I_STRING( usNumChars, ch ));
}


void copyChars( I_STRING & dest, I_CHAR ch, unsigned short usNumChars )
{
   dest = I_STRING( usNumChars, ch );
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

   while( word( aString, usWordNum++ ).length() > 0 );

   return(--usWordNum);
}


I_STRING left( const I_STRING& aString, unsigned short usLength )
{
   // If the length of the string is less than the desired length
   // pad the string on the right with spaces
   if( aString.length() < usLength )
   {
      I_STRING strNewString( aString );
      padLeft( strNewString, usLength, ' ' );
      return(strNewString);
   }
   else if( aString.length() == usLength )
      return(aString);
   else
   {
      return(aString.substr( 0, usLength ));
   }
}


I_STRING reverse( const I_STRING& aString )
{
   I_STRING strReversed;

   int nStringLength = aString.length();

   for( int i = nStringLength - 1; i >= 0; --i )
   {
      strReversed += aString[i];
   }

   return(strReversed);
}


I_STRING right( const I_STRING& aString, unsigned short usLength )
{
   return(reverse( left( reverse( aString ), usLength ) ));
}


DICORE_LINKAGE bool parseLocale( const I_STRING& locale,
                                 I_STRING& language,
                                 I_STRING& country,
                                 I_STRING& variant )
{
   language = I_( "" );
   country = I_( "" );
   variant = I_( "" );

   if( locale.length() < 2 )
   {
      return(false);
   }

   I_STRING localeTemp( locale.c_str() );
   strip( localeTemp );

   I_STRING unknownTemp = localeTemp.substr( 0, 2 );

   if( i_islower( unknownTemp[ 0 ] ) && i_islower( unknownTemp[ 0 ] ) )
   {
      // It's a language
      language = unknownTemp;
   }
   else if( i_isupper( unknownTemp[ 0 ] ) && i_isupper( unknownTemp[ 0 ] ) )
   {
      // It's a country
      country = unknownTemp;
   }
   else
   {
      // Who knows - it's not a country or a language
      return(false);
   }

   localeTemp = localeTemp.substr( 2, localeTemp.length() - 2 );
   strip( localeTemp );

   if( localeTemp.length() < 2 )
   {
      // Not enough left in the string to make a lang/country
      return(false);
   }

   unknownTemp = localeTemp.substr( 0, 2 );

   if( language.length() > 0 )
   {
      // If we got a language before, then this must be the country
      if( i_isupper( unknownTemp[ 0 ] ) && i_isupper( unknownTemp[ 0 ] ) )
      {
         country = unknownTemp;
      }
      else
      {
         return(false);
      }
   }
   else
   {
      // If we got a country before, then this must be the language
      if( i_islower( unknownTemp[ 0 ] ) && i_islower( unknownTemp[ 0 ] ) )
      {
         // It's a language
         language = unknownTemp;
      }
      else
      {
         return(false);
      }
   }

   variant = localeTemp.substr( 2, localeTemp.length() - 2 );
   strip( variant );

   return(true);
}


#ifdef DST_UNICODE

// This section is for internal, non-Unicode string support

unsigned long convertToULong( const DStringA & aString )
{
   return(strtoul( aString.c_str(), (char **)NULL, 10 ));
}


bool isAllDigits( const DStringA &aString )
{
   return( strspn( aString.c_str(), szAllDigits ) ==
           strlen( aString.c_str() ) );
}


bool isDecimal( const DStringA & aString )
{
   const unsigned int strLength = aString.length();

   // If we have a legnth of zero, then the string is not decimal.
   if( 0 == strLength )
   {
      // We are modeling after the constructor for BigDecimal and an empty
      // string is not a decimal number. - DMUM
      return(false);
   }

   // Do locale-dependent initialization.
   I_CHAR DECIMAL_POINT;
   I_CHAR DIGIT_SEPARATOR;
   I_CHAR NEGATIVE_SIGN;
   char GROUPING;

   struct lconv * plc = localeconv();

   DIGIT_SEPARATOR = *( plc->mon_thousands_sep );
   DECIMAL_POINT = *( plc->mon_decimal_point );
   NEGATIVE_SIGN = *( plc->negative_sign );
   GROUPING = *( plc->mon_grouping );

   // is this the 'C' locale; if so, use English characters
   if( '\0' == DIGIT_SEPARATOR )
   {
      DIGIT_SEPARATOR = ',';
      DECIMAL_POINT = '.';
      NEGATIVE_SIGN = '-';
      GROUPING = 3;
   }

   // Find a decimal point
#pragma warning( push )
#pragma warning( disable:4244 )
   unsigned int decPtPos = aString.find( DECIMAL_POINT );
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
      if( firstChar == NEGATIVE_SIGN )
      {
         hasSign = true;

         // Make sure we meet the minimum length
         isDecimal = ( hasDecimal ? 2 : 1 ) < strLength;
      }
      // No sign, check for decimal point
      else if( firstChar == DECIMAL_POINT )
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
      // Make sure everthing to the right is a digit.
      for( int index = decPtPos + 1; index < strLength; ++index )
      {
         if( 0 == i_isdigit( aString[ index ] ) )
         {
            return(false);
         }
      }
   }
   else
   {
      decPtPos = strLength;
   }

   // We only need to see if a separator is present at this point
   bool hasSeparator = false;

   if( ( CHAR_MAX != GROUPING ) && ( I_('\0') != DIGIT_SEPARATOR ) )
   {
#pragma warning( push )
#pragma warning( disable:4244 )
      hasSeparator = I_STRING::npos != aString.find( DIGIT_SEPARATOR );
#pragma warning( pop )
   }

   // Check integer part.
   int currentPos = decPtPos - 1;   // Start one position to the left
   const int endPos = hasSign ? 0 : -1;

   while( isDecimal && endPos < currentPos )
   {
      // If we have a separator and we are at a separator position then
      // make sure the curent position is a separator
      if( hasSeparator && ( ( decPtPos - currentPos ) == ( 1 + GROUPING ) ) )
      {
         isDecimal = aString[ currentPos ] == DIGIT_SEPARATOR;
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
   char * pszStr = new char[ aString.length() + 1 ];

   strcpy( pszStr, aString.c_str() );

   _strlwr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}


DStringA &padLeft( DStringA &aString, unsigned long padLength, char padChar )
{
   int nStringLen = aString.length();

   if( nStringLen >= padLength )
      return(aString);

   int nPadChars = padLength - nStringLen;

   char * pszPadded = new char[ padLength + 1 ];
   memset( pszPadded, padChar, nPadChars );
   pszPadded[ nPadChars ] = '\0';

   strcat( pszPadded, aString.c_str() );

   aString = pszPadded;

   delete [] pszPadded;

   return(aString);
}


DStringA &padRight( DStringA &aString, unsigned long padLength, char padChar )
{
   int nStringLen = aString.length();

   if( nStringLen >= padLength )
      return(aString);

   int nPadChars = padLength - nStringLen;

   char * pszPadded = new char[ padLength + 1 ];

   strcpy( pszPadded, aString.c_str() );
   memset( pszPadded + nStringLen, padChar, nPadChars );
   pszPadded[ padLength ] = '\0';

   aString = pszPadded;

   delete [] pszPadded;

   return(aString);
}



DStringA &strip( DStringA &aString, char stripChar )
{
   return(stripLeading( stripTrailing( aString, stripChar ), stripChar ));
}


DStringA &stripAll( DStringA &aString, char stripChar )
{
   int nStringLen = aString.length();

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
   int nStringLen = aString.length();

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
   int nStringLen = aString.length();

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
   char * pszStr = new char[ aString.length() + 1 ];

   strcpy( pszStr, aString.c_str() );

   _strupr( pszStr );

   aString = pszStr;

   delete [] pszStr;

   return(aString);
}


DStringA addTwoStrings( const DStringA &firstValue, const DStringA &secondValue )
{
   DStringA::size_type firstLength, secondLength, counter;
   int carryValue, value1, value2, newValue;
   DStringA newValueString, returnVal, adjustedFirstValue, adjustedSecondValue;
   char abuff[3], bbuff[3];

   firstLength = firstValue.length();
   secondLength = secondValue.length();
   carryValue = 0;
   adjustedFirstValue = firstValue;
   adjustedSecondValue = secondValue;

   if( firstLength > secondLength )
   {
      padLeft( adjustedSecondValue, firstLength, '0' );
   }
   else
   {
      padLeft( adjustedFirstValue, secondLength, '0' );
   }

   firstLength = adjustedFirstValue.length();
   secondLength = adjustedSecondValue.length();

   for( counter = 1; counter <= firstLength; ++counter )
   {
      sprintf( bbuff, "%c", adjustedFirstValue[ firstLength - counter ] );
      value1 = atoi( bbuff );
      sprintf( bbuff, "%c", adjustedSecondValue[ secondLength - counter ] );
      value2 = atoi( bbuff );

      newValue = value1 + value2 + carryValue;
      if( newValue > 9 )
      {
         carryValue = 1;
         sprintf( abuff, "%d", newValue - 10 );
      }
      else
      {
         carryValue = 0;
         sprintf( abuff, "%d", newValue );
      }
      newValueString = abuff;
      returnVal = newValueString + returnVal;
   }
   if( carryValue > 0 )
   {
      sprintf( abuff, "%d", carryValue );
      newValueString = abuff;
      returnVal = newValueString + returnVal;
   }

   return(returnVal);
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
   char szValue[ MAX_STRING_SIZE + 1 ];
   // don't need to memset
   //memset( szValue, 0, 30 * sizeof( char ) ); // clear memory
   return(DStringA( _itoa( nValue, szValue, 10 ) )); //convert int to DStringA
}


void convertIntToString( int nValue, DStringA & dest )
{
   char szValue[ MAX_STRING_SIZE + 1 ];

   dest = DStringA( _itoa( nValue, szValue, 10 ) ); //convert int to DStringA
}


DStringA & formatStringUsingMask( DStringA &valueString, const DStringA &mask )
{
   DStringA newValue( mask.length(), ' ' ),
   maskVals( "A9#XZ$%" );
   long  valDecimalPosition = 0, maskDecimalPosition = 0, srcOffset = 0,
   targetOffset = 0, maskOffset = 0, maskValsLen = 0, valLen = 0,
   maskLen = 0;
   char thisMaskChar;
   bool isNegative = false;

   char fractSepSymbolStr[ 2 ]; // get fractional separator symbol from locale
   char currencySymbolStr[ 2 ]; // get currency symbol from locale
   struct lconv * lc = localeconv( );
   fractSepSymbolStr[ 0 ] = lc->decimal_point[ 0 ];
   fractSepSymbolStr[ 1 ] = '\0';
   currencySymbolStr[ 0 ] = lc->currency_symbol[ 0 ];
   currencySymbolStr[ 1 ] = '\0';

   maskLen = mask.length();
   maskValsLen = maskVals.length();

   if( maskLen > 0 )
   {
      if( ( ( DStringA::npos != mask.find( "$" )) ||
            ( DStringA::npos != mask.find( "9" )) ||
            ( DStringA::npos != mask.find( "%"))) &&
          DStringA::npos != mask.find( "." ) )
      {
         strip( valueString );
         if( DStringA::npos == mask.find_first_not_of( "%." ) )
         {
            stripAll( valueString, '%' );
            // Yeah, it's a mess.  So what?

            // vintage Chris...

            if( DStringA::npos == valueString.find( fractSepSymbolStr ) )
            {
               valueString += fractSepSymbolStr;
            }
            DStringA strippedMask( mask );
            strip( strippedMask );
            if( valueString.length() < strippedMask.length() )
            {
               long beforeDec = strippedMask.find( "." );
               long afterDec = strippedMask.length() - ( beforeDec + 1 );
               long valueBeforeDec = valueString.find( fractSepSymbolStr );
               long valueAfterDec = valueString.length() - ( valueBeforeDec + 1 );
               if( valueBeforeDec < beforeDec )
               {
                  padLeft( valueString, ( valueString.length() + ( beforeDec - valueBeforeDec )), '0' );
               }
               if( valueAfterDec < afterDec )
               {
                  padRight( valueString, ( valueString.length() + ( afterDec - valueAfterDec )), '0' );
               }
            }
            long newLen = valueString.length();
            long decPlace = valueString.find( fractSepSymbolStr );
            long afterDecimal = newLen - ( decPlace - 1 );
            if( afterDecimal < 2 )
            {
               padRight( valueString, ( 2 - afterDecimal ), '0' );
            }
            valueString.insert( decPlace + 3, fractSepSymbolStr );
            valueString.erase( decPlace, 1 );
         }
         if( DStringA::npos != valueString.find( "-") )
         {
            isNegative = true;
            valueString = valueString.substr( 1 );
         }

         long oldDecPlace = valueString.find( fractSepSymbolStr );
         if( DStringA::npos != oldDecPlace )
         {
            stripLeading( valueString, '0' );
            if( valueString.find( fractSepSymbolStr ) == 0 )
            {
               valueString = "0" + valueString;
            }
         }

         valLen = valueString.length();
         if( DStringA::npos == ( maskOffset = mask.find( ".")) )
         {
            maskOffset = maskLen - 1;
         }

         targetOffset = maskOffset;

         if( DStringA::npos != ( srcOffset = valueString.find( fractSepSymbolStr )) )
         {
            valDecimalPosition = srcOffset--;
         }
         else
         {
            srcOffset = valDecimalPosition = valLen - 1;
         }

         maskDecimalPosition = maskOffset;

         while( maskOffset >= 0 )
         {
            thisMaskChar = mask[ maskOffset ];
            if( DStringA::npos != maskVals.find( thisMaskChar ) )
            {
               if( srcOffset >= 0 )
               {
                  newValue[ targetOffset-- ] = valueString[ srcOffset-- ];
               }
               else
               {
                  switch( thisMaskChar )
                  {
                     case '$' :
                        newValue[ targetOffset-- ] = currencySymbolStr[ 0 ];
                        maskOffset = 0;
                        break;

                     case '.' :
                        newValue[ targetOffset-- ] = fractSepSymbolStr[ 0 ];
                        break;

                     case 'Z':
                        newValue[ targetOffset-- ] = '0';
                        break;

                     default:
                        newValue[ targetOffset-- ] = ' ';
                        break;
                  } // switch
               } // if - else
            }
            else
            {
               if( srcOffset >= 0 )
               {
                  if( '-' != valueString[ srcOffset ] )
                  {
                     newValue[ targetOffset-- ] = thisMaskChar;
                  }
                  else if( '.' == thisMaskChar )
                  {
                     newValue[ targetOffset-- ] = fractSepSymbolStr[ 0 ];
                  }
                  else if( ',' == thisMaskChar )
                  {
                     switch( mask[ maskOffset + 1 ] )
                     {
                        case '$':
                           newValue[ targetOffset-- ] = currencySymbolStr[ 0 ];
                           maskOffset = 0;
                           break;

                        case 'Z':
                           // we have to special case locale-dependent characters fractSepSymbolStr and currencySymbolStr
                           char replaceChar;
                           switch( thisMaskChar )
                           {
                              case '$':
                                 replaceChar = currencySymbolStr[ 0 ];
                                 break;
                              case '.':
                                 replaceChar = fractSepSymbolStr[ 0 ];
                                 break;
                              default:
                                 replaceChar =  thisMaskChar;
                                 break;
                           }
                           newValue[ targetOffset-- ] = replaceChar;
                           break;

                        default:
                           newValue[ targetOffset-- ] = ' ';
                           break;
                     } // switch
                  } // if-else
               }
            } // if ( DStringA::npos != maskVals.find( thisMaskChar ))
            maskOffset--;
         }
         maskOffset = targetOffset = ( maskDecimalPosition + 1 );
         srcOffset = ( valDecimalPosition + 1 );

         while( maskOffset < maskLen )
         {
            thisMaskChar = mask[ maskOffset ];
            if( DStringA::npos != maskVals.find( thisMaskChar ) )
            {
               if( srcOffset < valLen )
               {
                  newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
               }
               else
               {
                  newValue[ targetOffset++ ] = '0';
               }
            }
            else
            {
               newValue[ targetOffset++ ] = thisMaskChar;
            }
            ++maskOffset;
         } // while

         if( isNegative )
         {
            unsigned long firstNonSpace = newValue.find_first_not_of( ' ' );
            if( 0 == firstNonSpace )
            {
               newValue = "-" + newValue;
            }
            else
            {
               newValue[ firstNonSpace - 1 ] = '-';
            }
         }
         valueString = newValue;
      }
      else
      {
         valLen = valueString.length();
         while( maskOffset < maskLen )
         {
            if( DStringA::npos != maskVals.find( mask[ maskOffset ] ) )
            {
               if( srcOffset < valLen )
               {
                  newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
               }
               else
               {
                  newValue[ targetOffset++ ] = ' ';
               }
            }
            else
            {
               newValue[ targetOffset++ ] = mask[ maskOffset ];
            }
            ++maskOffset;
         }
         valueString = newValue;
      }
   }
   return(valueString);
}


DStringA &removeMaskFromString( DStringA &maskedValue, const DStringA &mask )
{
   long valLength = maskedValue.length();
   long maskLength = mask.length();
   DStringA targetValue( maskLength + 1, ' ' ), maskVals( "A9#XZ$%" );
   char fractSepSymbolStr[ 2 ]; // get fractional separator symbol from locale
   char currencySymbolStr[ 2 ]; // get currency symbol from locale
   setlocale( LC_ALL, NULL );
   struct lconv * lc = localeconv( );
   fractSepSymbolStr[ 0 ] = lc->decimal_point[ 0 ];
   fractSepSymbolStr[ 1 ] = '\0';
   currencySymbolStr[ 0 ] = lc->currency_symbol[ 0 ];
   currencySymbolStr[ 1 ] = '\0';

   if( ( DStringA::npos != mask.find( "$" ) || DStringA::npos != mask.find( "9" ) ||
         DStringA::npos != mask.find( "%" ) ) && ( DStringA::npos != mask.find( ".")) )
   {
      DStringA thisMask( mask );
      if( DStringA::npos != thisMask.find_first_not_of( "%.") )
      {
         if( DStringA::npos == thisMask.find( ".") )
         {
            stripTrailing( thisMask );
            thisMask = thisMask + ".";
            maskLength = thisMask.length();
            targetValue += " ";
         }
         if( DStringA::npos == maskedValue.find( fractSepSymbolStr ) )
         {
            stripTrailing( maskedValue );
            maskedValue = maskedValue + fractSepSymbolStr;
            valLength = maskedValue.length();
         }
         long srcDecPos = maskedValue.find( fractSepSymbolStr );
         long maskDecPos = thisMask.find( "." );
         long srcOffset = srcDecPos;
         long maskOffset = maskDecPos;
         bool hasDec = ( srcOffset >= 0 || maskOffset >= 0 );
         long targetOffset = maskOffset;

         if( hasDec )
         {
            while( srcOffset >= 0 && maskOffset >= 0 )
            {
               char maskedAtOffset = maskedValue[ srcOffset ];
               if( isdigit( maskedAtOffset ) )
               {
                  targetValue[ targetOffset-- ] = maskedAtOffset;
               }
               else
               {
                  if( maskedAtOffset != thisMask[ maskOffset ] )
                  {
                     if( maskedAtOffset != fractSepSymbolStr[ 0 ] ||
                         maskOffset == 0 ||
                         thisMask[ maskOffset - 1 ] != '$' )
                     {
                        targetValue[ targetOffset-- ] = maskedAtOffset;
                     }
                  }
               }
               srcOffset--;
               maskOffset--;
            }
         }
         srcOffset = srcDecPos + 1;
         maskOffset = targetOffset = ( maskDecPos + 1 );
         if( hasDec )
         {
            // TO DO:
            targetValue[ targetOffset++ ] = '.'; // get fractional separator symbol from locale
         }
         while( srcOffset < valLength && maskOffset < maskLength
                && targetOffset < ( maskLength + 1 ) )
         {
            char maskedAtOffset = maskedValue[ srcOffset ];
            if( isdigit( maskedAtOffset ) ||
                ( maskedAtOffset != thisMask[ maskOffset ] ) )
            {
               targetValue[ targetOffset++ ] = maskedAtOffset;
            }
            ++srcOffset;
            ++maskOffset;
         }
      }
      else
      {
         stripAll( maskedValue, '%' );
         targetValue = maskedValue;
      }
      strip( targetValue );
   }
   else
   {
      long srcOffset = 0;
      long maskOffset = 0;
      long targetOffset = 0;
      while( srcOffset < valLength && maskOffset < maskLength )
      {
         char maskedAtOffset = maskedValue[ srcOffset ];
         char maskChar = mask[ maskOffset ];
         if( ( maskChar == '9' && isdigit( maskedAtOffset ) ) ||
             (( maskChar == 'X' || maskChar == 'A' || maskChar == 'Z' ) &&
              !isdigit( maskedAtOffset )) ||
             maskedAtOffset != maskChar )
         {
            targetValue[ targetOffset++ ] = maskedAtOffset;
         }
         ++srcOffset;
         ++maskOffset;
      }
      strip( targetValue );
   }
   maskedValue = targetValue;
   return(maskedValue);
}


DStringA& appendInt( DStringA &aString, int iInt )
{
   char szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   _itoa( iInt, szValue, 10 ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}


DStringA& appendULong( DStringA &aString, unsigned long ulNum )
{
   char szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   sprintf( szValue, "%lu", ulNum ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}


DStringA& appendLong( DStringA &aString, long lNum )
{
   char szValue[ MAX_STRING_SIZE + 1 ];
//   memset( szValue, 0, 30 ); // clear memory
   sprintf( szValue, "%ld", lNum ); //convert int DStringA
   aString += DStringA( szValue );
   return(aString); //return the DStringA contents
}


int pos( char ch, const DStringA& aString )
{
   DStringA::size_type nStartChar = aString.find( ch );

   if( DStringA::npos == nStartChar )
      return(-1);
   else
      return(nStartChar);
}


int pos( const DStringA& strSubString, const DStringA& strFullString )
{
   DStringA::size_type nStartSubString = strFullString.find( strSubString );

   if( DStringA::npos == nStartSubString )
      return(-1);
   else
      return(nStartSubString);
}


DStringA copies( char ch, unsigned short usNumChars )
{
   return(DStringA( usNumChars, ch ));
}


void copyChars( DStringA & dest, char ch, unsigned short usNumChars )
{
   dest = DStringA( usNumChars, ch );
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

   while( word( aString, usWordNum++ ).length() > 0 );

   return(--usWordNum);
}


DStringA left( const DStringA& aString, unsigned short usLength )
{
   // If the length of the string is less than the desired length
   // pad the string on the right with spaces
   if( aString.length() < usLength )
   {
      DStringA strNewString( aString );
      padLeft( strNewString, usLength, ' ' );
      return(strNewString);
   }
   else if( aString.length() == usLength )
      return(aString);
   else
   {
      return(aString.substr( 0, usLength ));
   }
}


DStringA reverse( const DStringA& aString )
{
   DStringA strReversed;

   int nStringLength = aString.length();

   for( int i = nStringLength - 1; i >= 0; --i )
   {
      strReversed += aString[i];
   }

   return(strReversed);
}


DStringA right( const DStringA& aString, unsigned short usLength )
{
   return(reverse( left( reverse( aString ), usLength ) ));
}


DICORE_LINKAGE bool parseLocale( const DStringA& locale,
                                 DStringA& language,
                                 DStringA& country,
                                 DStringA& variant )
{
   language = I_( "" );
   country = I_( "" );
   variant = I_( "" );

   if( locale.length() < 2 )
   {
      return(false);
   }

   DStringA localeTemp( locale.c_str() );
   strip( localeTemp );

   DStringA unknownTemp = localeTemp.substr( 0, 2 );

   if( i_islower( unknownTemp[ 0 ] ) && i_islower( unknownTemp[ 0 ] ) )
   {
      // It's a language
      language = unknownTemp;
   }
   else if( i_isupper( unknownTemp[ 0 ] ) && i_isupper( unknownTemp[ 0 ] ) )
   {
      // It's a country
      country = unknownTemp;
   }
   else
   {
      // Who knows - it's not a country or a language
      return(false);
   }

   localeTemp = localeTemp.substr( 2, localeTemp.length() - 2 );
   strip( localeTemp );

   if( localeTemp.length() < 2 )
   {
      // Not enough left in the string to make a lang/country
      return(false);
   }

   unknownTemp = localeTemp.substr( 0, 2 );

   if( language.length() > 0 )
   {
      // If we got a language before, then this must be the country
      if( i_isupper( unknownTemp[ 0 ] ) && i_isupper( unknownTemp[ 0 ] ) )
      {
         country = unknownTemp;
      }
      else
      {
         return(false);
      }
   }
   else
   {
      // If we got a country before, then this must be the language
      if( i_islower( unknownTemp[ 0 ] ) && i_islower( unknownTemp[ 0 ] ) )
      {
         // It's a language
         language = unknownTemp;
      }
      else
      {
         return(false);
      }
   }

   variant = localeTemp.substr( 2, localeTemp.length() - 2 );
   strip( variant );

   return(true);
}

DString &strip( DString &aString, char stripChar )
{
   return(stripLeading( stripTrailing( aString, stripChar ), stripChar ));
}

DString &stripAll( DString &aString, char stripChar )
{
   stripAll(aString.getImp(), stripChar);
   return(aString);
}

DString &stripLeading( DString &aString, char stripChar )
{
   stripLeading(aString.getImp(), stripChar);
   return(aString);
}

DString &stripTrailing( DString &aString, char stripChar )
{
   stripTrailing(aString.getImp(), stripChar);
   return(aString);
}

DString& appendULong( DString &aString, unsigned long ulNum )
{
   appendULong(aString.getImp(), ulNum);
   return(aString); 
}

DString &padLeft( DString &aString, unsigned long padLength, char padChar )
{
   padLeft(aString.getImp(), padLength, padChar);
   return(aString);
}

DString &padRight( DString &aString, unsigned long padLength, char padChar )
{
   padRight(aString.getImp(), padLength, padChar);
   return(aString);
}

void convertIntToString( int nValue, DString & dest )
{
    convertIntToString( nValue, dest.getImp() );
}

DString &removeMaskFromString( DString &maskedValue, const DString &mask )
{
   removeMaskFromString(maskedValue.getImp(), mask.getImp());
   return(maskedValue);
}

DString & formatStringUsingMask( DString &valueString, const DString &mask )
{
   formatStringUsingMask(valueString.getImp(), mask.getImp());
   return(valueString);
}

#endif


/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/stringfunctions.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 09:04:28   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:42:16   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:28   SMITHDAV
// Initial revision.
// 
//    Rev 1.20   Mar 16 2001 14:31:02   dt24433
// Changed padRight, padLeft, stripLeading, stripTrailing to use
// basic_string methods for implementation.  Much simpler, and pad 
// methods are now much faster.
// 
//    Rev 1.19   Jul 06 2000 14:46:14   DMUM
// isDecimal() now behaves more like Big Decimal
//
//    Rev 1.18   Jun 28 2000 18:05:46   DT14177
// fixed some ASCII build problems
//
//    Rev 1.17   Jun 26 2000 17:09:20   DT14177
// added constructors and assignment operators to MathString
//
//    Rev 1.16   Jun 09 2000 15:40:10   DMUM
// Sync up with 1.7
//
//    Rev 1.15   Apr 11 2000 15:10:00   DT14177
// fixed the Unicode build
//
//    Rev 1.14   Mar 17 2000 10:18:40   dtwk
// Fix UNICODE build
//
//    Rev 1.13   Mar 16 2000 12:31:00   DT14177
// removed criticalSection
//
//    Rev 1.12   Mar 14 2000 16:49:22   DT14177
// locale-specific data is now retrieved every time
//
//    Rev 1.11   Mar 14 2000 14:18:02   DT14177
// enhanced isDecimal() to support comma-separators
//
//    Rev 1.10   Sep 07 1999 17:37:04   dtwk
// Fix for stripTrailing on a string of only blanks
//
//    Rev 1.9   Jul 13 1999 14:14:22   dtwk
// Fix stripTrailing function that returns a DString too
//
//    Rev 1.8   Jul 13 1999 12:10:48   dtwk
// Trap in stripTrailing if the string consists of only the char to be stripped
//
//    Rev 1.7   May 24 1999 10:40:16   DTWK
// Add method to parse a locale string into its components (lang, country, variant)
//
//    Rev 1.6   May 03 1999 15:02:50   DT14177
// changed to get the decimal point from the locale.
//
//    Rev 1.5   May 03 1999 12:39:16   DTWK
// words() used to return the correct value + 1
//
//    Rev 1.4   18 Feb 1999 10:38:36   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:24   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:40   DMUM
//
//
//    Rev 1.28   Jul 16 1998 11:54:50   dmum
// Check-in for Paul Dardeau
//
//    Rev 1.25   Jul 06 1998 11:35:30   DTWK
// Fix carryValue in AddTwoStrings()
//
//    Rev 1.24   Jun 16 1998 17:16:42   DTWK
// Add in DPQD's changes for faster runtime speed
//
//    Rev 1.23   May 21 1998 16:18:12   dcyk
// Fix problem with formatStringUsingMask,
// where the mask has % and the value
// doesn't have a decimal point.
//
//
//    Rev 1.22   Apr 24 1998 10:27:04   dcyk
// Fix bug in masking routines, for signed
// values with masks that don't have decimals.
//
//
//    Rev 1.21   Nov 09 1997 15:35:20   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.20   Aug 28 1997 09:58:32   DTWK
// Add some REXX-like functions for DPQD
//
//    Rev 1.19   05 Aug 1997 15:54:16   dcyk
// Added support for the percentage mask.
//
//
//    Rev 1.18   24 Jul 1997 17:18:56   dcyk
// Fixed removeMaskFromString, so it
// doesn't think "9"s are part of the mask &
// should be removed.
//
//
//    Rev 1.17   Jul 23 1997 11:37:36   DTWK
// Add functions appendUlong() et al.
//
//    Rev 1.16   10 Jul 1997 15:41:32   dcyk
// Fixed the masking functions.
//
//
//    Rev 1.15   13 Jun 1997 11:33:50   dcyk
// Fixed problem in formatStringUsingMask.
//
//
//    Rev 1.14   12 Jun 1997 12:52:56   dcyk
// Added formatStringUsingMask and
// removeMaskFromString.
//
//
//    Rev 1.13   Jun 11 1997 17:10:28   DTWK
// Update with more recent version from DPQD
//
//    Rev 1.12   Apr 11 1997 09:13:02   dcyk
// Improve performance.
//
//
//    Rev 1.11   Mar 26 1997 17:07:26   dlkt
// Added asString mehtod that takes in an
// interger and converts it to a string.
//
//    Rev 1.10   Feb 21 1997 12:16:22   dcyk
// Modified isDecimal so the string
// "7.5" is ok, as is " 7.5" and "-7.5".
//
//
//    Rev 1.9   Feb 19 1997 16:34:30   dlkt
// Added stringHasOnly function.
//
//    Rev 1.8   Jan 28 1997 16:46:56   DPQD
// Corrected revision comments for Rev 1.6 and Rev 1.7
//
//    Rev 1.7   Jan 28 1997 16:42:04   DPQD
// Fixed bug in 'isDecimal' regarding improper detection of
// multiple decimal points with one of them being the
// first character.
//
//    Rev 1.6   Jan 28 1997 15:07:44   DPQD
// Fixed compile error as part of Rev 1.5 change
//
//    Rev 1.5   Jan 28 1997 15:04:16   DPQD
// Added the function 'asInteger'
//
//    Rev 1.4   Jan 28 1997 08:44:22   dcyk
// Added "addTwoStrings" function, which
// arithmetically adds two strings, and
// returns the value in a third string.
//
//
//    Rev 1.3   Dec 31 1996 13:21:32   DRUS
// Added the functions isAllDigits, isDecimal, lowerCase, stripAll, and
// upperCase.  Renamed the function atoul to convertToULong.
//
//    Rev 1.2   Nov 21 1996 14:40:00   DRUS
// Fixed syntax error in comments generated by PVCS (attempt two).
//
//
//    Rev 1.1   Nov 20 1996 17:11:36   DRUS
// Fixed syntax error in comments generated by PVCS.
//
//    Rev 1.0   Nov 20 1996 11:07:46   DRUS
//
//
*/


// i18n

