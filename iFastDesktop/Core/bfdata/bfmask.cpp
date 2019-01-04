#include "stdafx.h"
#include <clientlocale.hpp>
#include "bfmask.hpp"
#include <configmanager.hpp>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfguard.hpp>
#include <bfutil\localetraits.hpp>

namespace ifds
{
   // mask character constants
   const I_CHAR MASK_QUOTE              = I_('\'');
   const I_CHAR MASK_EXPONENT_SEPERATOR = I_('E');
   const I_CHAR MASK_REQUIRED_DIGIT     = I_('0');
   const I_CHAR MASK_NONREQUIRED_DIGIT  = I_('#');
   const I_CHAR MASK_NONREQUIRED_DIGIT2 = I_('9');
   const I_CHAR MASK_MINUS_SIGN         = I_('-');
   const I_CHAR MASK_GROUP_SEPERATOR    = I_(',');
   const I_CHAR MASK_DECIMAL_SEPERATOR  = I_('.');
   const I_CHAR MASK_TERMINAL_CHARACTER = I_('\0');
}

namespace ifds
{
   const unsigned int pure_integer_mask = 0x0001;
   const unsigned int integer_mask      = 0x0002;
   const unsigned int decimal_mask      = 0x0004;
}

/**********************************************************************/
BFMask::BFMask( const DString& mask )
: mask_( mask )
, prefix_()
, prefixSize_( 0 )
, integerMask_()
, integerMaskSize_( 0 )
, integerMaskDigits_( 0 )
, decimalMask_()
, decimalMaskSize_( 0 )
, hasDecimal_( false )
, suffix_()
, suffixSize_( 0 )
, flags_( 0 )
{
   parseMask( mask );
}

/**********************************************************************/
DString BFMask::format( DIINT64 value, const ClientLocale& rLocale ) const
{
   wchar_t szValue[ 256 ];
   _i64tow( value, szValue, 10 );
   return( format( szValue, rLocale ) );
}

/**********************************************************************/
DString BFMask::format( double value, const ClientLocale& rLocale ) const
{
   I_CHAR szValue[ 256 ];
   int cb = 0;
   if( decimalMaskSize_ == 0 )
   {
      cb = i_snprintf( szValue, sizeof( szValue ) / sizeof( szValue[0] ), I_( "%-.lf" ), value );
   }
   else
   {
      cb = i_snprintf( szValue, sizeof( szValue ) / sizeof( szValue[0] ), I_( "%-.*lf" ), decimalMaskSize_, value );
   }
   DString str( szValue );
   DString str2 = format( str, rLocale );
   return( str2 );
}

/**********************************************************************/
DString BFMask::format( const BigDecimal& value, const ClientLocale& rLocale ) const
{

   DString str;
   if( decimalMaskSize_ == 0 ) {
      str = value.asDString();
   } else {
      str = value.asDString(-decimalMaskSize_);
   }
   DString str2 = format( str, rLocale );
   return( str2 );
}

/**********************************************************************/
DString BFMask::format( const DString &value, const ClientLocale& rLocale ) const
{
   const I_CHAR *pValue = value.c_str();

   bool negative = false;
   I_CHAR valueDigits[512];
   int valueDigitCount = 0;
   int valueDecimalPlace = 0;

   { // pre-parse value
      bool firstDigitFound = false;
      int trailingZeroCount = 0;

      enum
      {
         LEADING, 
         SIGN, 
         INTEGER, 
         DECIMAL, 
         TRAILING
      } parseStep = LEADING;

      while( *pValue != I_('\0') )
      {
         switch( parseStep )
         {
            case LEADING:  // trim leading spaces
               if( *pValue == I_(' ') )
               {
                  pValue++;
               }
               else
               {
                  parseStep = SIGN;
               }
               break;

            case SIGN:  // trim leading spaces and sign
               if( *pValue == I_('+') || *pValue == I_('-') )
               {
                  negative = ( *pValue == I_('-') );
                  pValue++;
               }
               else
               {
                  parseStep = INTEGER;
               }
               break;

            case INTEGER:
               if( i_isdigit( *pValue ) )
               {
                  if( *pValue == I_('0') )
                  {
                     if( firstDigitFound )
                     {
                        valueDigits[ valueDigitCount++ ] = *pValue;
                        valueDecimalPlace++;
                        trailingZeroCount++;
                     }
                  }
                  else
                  {
                     valueDigits[ valueDigitCount++ ] = *pValue;
                     valueDecimalPlace++;
                     trailingZeroCount = 0;
                     firstDigitFound = true;
                  }
                  pValue++;
               }
               else if( *pValue == I_('.') )
               {
                  pValue++;
                  parseStep = DECIMAL;
               }
               else
               {
                  parseStep = TRAILING;
               }
               break;

            case DECIMAL:
               if( i_isdigit( *pValue ) )
               {
                  if( *pValue == I_('0') )
                  {
                     if( firstDigitFound )
                     {
                        valueDigits[ valueDigitCount++ ] = *pValue;
                        trailingZeroCount++;
                     }
                     else
                     {
                        valueDecimalPlace--;
                     }
                  }
                  else
                  {
                     valueDigits[ valueDigitCount++ ] = *pValue;
                     trailingZeroCount = 0;
                     firstDigitFound = true;
                  }
                  pValue++;
               }
               else
               {
                  parseStep = TRAILING;
               }
               break;

            case TRAILING:
               if( *pValue != I_(' ') )
               {
                  BF_CE_THROW( InvalidCharacterException, I_( "BFMask::format" ) );
               }
         }

      }
      valueDigitCount -= trailingZeroCount;
      valueDigits[ valueDigitCount ] = I_('\0');

   }

   int valueOffset = integerMaskDigits_ - valueDecimalPlace - 1; // keeps the current current offset of value digits within mask ??confusing??
   if( valueOffset < 0 )
   {
      BF_CE_THROW( DigitOverflowException, I_( "BFMask::format" ) );
   }
   int valueDigitIndex = 0;

   I_CHAR buffer[256];
   int bufferIndex = 0;
   I_CHAR *pBuffer = buffer;

   const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( rLocale );

   // append prefix
   ::memcpy( &buffer[bufferIndex], prefix_, sizeof I_CHAR * prefixSize_ );
   bufferIndex += prefixSize_;

   // sign
   if( negative )
   {
      buffer[bufferIndex++] = I_('-');
   }

   // integer part
   bool firstDigitWritten = false;
   for( int integerMaskIndex = 0; integerMaskIndex < integerMaskSize_; integerMaskIndex++ )
   {
      switch( integerMask_[integerMaskIndex] )
      {
         case ifds::MASK_GROUP_SEPERATOR:
            if( firstDigitWritten )
            {
               buffer[bufferIndex++] = localeTraits.getGroupSeparator();
            }
            break;

         case ifds::MASK_NONREQUIRED_DIGIT:
         case ifds::MASK_NONREQUIRED_DIGIT2:
            if( valueOffset < 0 )
            {
               if( valueDigitIndex < valueDigitCount )
               {
                  buffer[bufferIndex++] = valueDigits[valueDigitIndex++];
                  firstDigitWritten = true;
               }
               else
               {
                  buffer[bufferIndex++] = I_('0');
               }
            }
            valueOffset--;
            break;

         case ifds::MASK_REQUIRED_DIGIT:
            if( valueOffset < 0 && valueDigitIndex < valueDigitCount )
            {
               buffer[bufferIndex++] = valueDigits[valueDigitIndex++];
            }
            else
            {
               buffer[bufferIndex++] = I_('0');
            }
            firstDigitWritten = true;
            valueOffset--;
            break;
      }
   }

   // decimal part
   if( hasDecimal_ )
   {
      bool decimalWritten = false;
      for( int decimalMaskIndex = 0; decimalMaskIndex < decimalMaskSize_; decimalMaskIndex++ )
      {

         if( valueOffset < 0 && valueDigitIndex < valueDigitCount )
         {
            if( ! decimalWritten )
            { // write decimal seperator only if required
               buffer[bufferIndex++] = localeTraits.getRadixSeparator();
               decimalWritten = true;
            }
            buffer[bufferIndex++] = valueDigits[valueDigitIndex++];
         }
         else
         {
            if( decimalMask_[decimalMaskIndex] == ifds::MASK_REQUIRED_DIGIT )
            { // write decimal seperator only if required
               if( ! decimalWritten )
               {
                  buffer[bufferIndex++] = localeTraits.getRadixSeparator();
                  decimalWritten = true;
               }
               buffer[bufferIndex++] = I_('0');
            }
         }
         valueOffset--;
      }
   }

   // exponent part
//   if ( hasExponent_ )
//   {
//      buffer[bufferIndex++] = localeExponentSeperator;
//      for ( int exponentIndex = 0; exponentIndex < exponentDigits_; exponentIndex++ )
//      {
//      }
//   }

   // append suffix
   ::memcpy( &buffer[bufferIndex], suffix_, sizeof I_CHAR * suffixSize_ );
   bufferIndex += suffixSize_;

   return(DString( buffer ,bufferIndex ));
}

/**********************************************************************/
void BFMask::parse( DIINT64& parsed, const DString &value, const ClientLocale& rLocale ) const
{
   DString result( parse( value, rLocale ) );
   parsed = _wtoi64( result.c_str() );
}

/**********************************************************************/
void BFMask::parse( double& parsed, const DString &value, const ClientLocale& rLocale ) const
{
   DString result( parse( value, rLocale ) );
   I_CHAR* pEnd = NULL;
   parsed = wcstod( result.c_str(), &pEnd );
}

/**********************************************************************/
void BFMask::parse( BigDecimal& parsed, const DString &value, const ClientLocale& rLocale ) const
{
   parsed = parse( value, rLocale );
}

/**********************************************************************/
DString BFMask::parse( const DString &value, const ClientLocale& rLocale ) const
{
   if( flags_ & ifds::pure_integer_mask )
   {
      return( value );
   }

   const I_CHAR *pValue = value.c_str();
   const I_CHAR *pValueEnd = pValue + value.size();


   if( value.size() >= prefixSize_ )
   {
      if( 0 == ::memcmp( pValue, prefix_, sizeof I_CHAR * prefixSize_ ) )
      {
         // exact match on prefix... skip.
         pValue += prefixSize_;
      }

      if( value.size() >= prefixSize_ + suffixSize_ &&
          0 == ::memcmp( ( pValueEnd - suffixSize_ ) , suffix_, sizeof I_CHAR * suffixSize_ ) )
      {
         // exact match on suffix... skip.
         pValueEnd -= suffixSize_;
      }
   }

   I_CHAR parsedValue[512];
   int parsedValueSize = 0;
   int parsedValueSizeAtLastDigit = 0;
   bool firstDigitFound = false;

   const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( rLocale );

   enum
   {
      PREFIX, 
      INTEGER, 
      DECIMAL, 
      SUFFIX
   } parseStep = PREFIX;


   while( pValue < pValueEnd &&  parseStep != SUFFIX )
   {
      switch( parseStep )
      {
         case PREFIX:
            if( i_isdigit( *pValue ) )
            {
               parseStep = INTEGER;
            }
            else
            {
               switch( *pValue )
               {
                  case I_('-'):
                     parsedValue[ parsedValueSize++ ] = I_('-');
                  case I_('+'):
                     parseStep = INTEGER;
                     break;
               }
               if( localeTraits.getRadixSeparator() == *pValue )
               {
                  // this is the case of a value being .01
                  firstDigitFound = true;
                  parsedValue[ parsedValueSize++ ] = I_( '0' );
                  parsedValue[ parsedValueSize++ ] = I_( '.' );
                  parseStep = DECIMAL;
                  pValue++;
                  break;
               }
               pValue++;
            }
            break;

         case INTEGER:
            if( i_isdigit( *pValue ) )
            {
               if( *pValue != I_('0') || firstDigitFound )
               {
                  parsedValue[ parsedValueSize++ ] = *pValue;
                  parsedValueSizeAtLastDigit = parsedValueSize;
                  firstDigitFound = true;
               }
               pValue++;
            }
            else if( *pValue == localeTraits.getGroupSeparator() )
            {
               pValue++;
            }
            else if( *pValue == localeTraits.getRadixSeparator() )
            {
               if( !firstDigitFound )
               {
                  parsedValue[ parsedValueSize++ ] = I_('0');
                  parsedValueSizeAtLastDigit = 1;
               }
               parsedValue[ parsedValueSize++ ] = I_('.');
               pValue++;
               parseStep = DECIMAL;
            }
            else
            {
               if( !firstDigitFound )
               {
                  parsedValue[ parsedValueSize++ ] = I_('0');
                  parsedValueSizeAtLastDigit = 1;
               }
               parseStep = SUFFIX;
            }
            break;

         case DECIMAL:
            if( i_isdigit( *pValue ) )
            {
               parsedValue[ parsedValueSize++ ] = *pValue;
               if( *pValue != I_('0') )
               {
                  parsedValueSizeAtLastDigit = parsedValueSize;
               }
               pValue++;
            }
            else
            {
               parseStep = SUFFIX;
            }
            break;

      }
   }

   if( parsedValueSizeAtLastDigit == 0 )
   {
      return(I_("0"));
   }
   return(DString( parsedValue ,parsedValueSizeAtLastDigit ));
}


/**********************************************************************/
void BFMask::parseMask( const DString &mask )
{

   const I_CHAR *pMask = mask.c_str();

   bool inQuote =  false;
   bool inRequiredIntegerDigits = false;
   bool inRequiredDecimalDigits = true;

   if( mask.find( I_( "9" ) ) != mask.npos )
   {
      inQuote = false;     // breakpoint target!
   }

   enum
   {
      PREFIX, 
      INTEGER, 
      DECIMAL, 
      SUFFIX
   } parseStep = PREFIX;

   while( *pMask != I_('\0') )
   {
      switch( parseStep )
      {
         case PREFIX:
            if( inQuote )
            {
               if( *pMask == ifds::MASK_QUOTE )
               {
                  // exit quote
                  inQuote = false;
                  pMask++;
               }
            }
            else
            {
               switch( *pMask )
               {
                  case ifds::MASK_QUOTE:
                     pMask++;
                     if( *pMask == ifds::MASK_QUOTE )
                     {
                        // two consecutive quote case
                        prefix_[prefixSize_++] = *pMask ;
                        pMask++;
                        break;
                     }
                     else
                     {
                        // enter quote
                        inQuote = true;
                     }
                     break;

                  case ifds::MASK_NONREQUIRED_DIGIT:
                  case ifds::MASK_NONREQUIRED_DIGIT2:
                  case ifds::MASK_REQUIRED_DIGIT:
                  case ifds::MASK_DECIMAL_SEPERATOR:
                     parseStep = INTEGER;
                     break;

                  default:
                     prefix_[prefixSize_++] = *pMask ;
                     pMask++;
                     break;

               }
            }
            break;

         case INTEGER:
            switch( *pMask )
            {
               case ifds::MASK_NONREQUIRED_DIGIT:
               case ifds::MASK_NONREQUIRED_DIGIT2:
                  if( inRequiredIntegerDigits )
                  {
                     assert(0);
                     BF_CE_THROW( InvalidMaskException, I_( "BFMask::parseMask()" ) );
                  }
                  if( ( flags_ & ifds::integer_mask ) != ifds::integer_mask )
                  {
                     flags_ |= ifds::pure_integer_mask;
                  }
                  integerMaskDigits_++;
                  integerMask_[integerMaskSize_++] = *pMask ;
                  pMask++;
                  break;
               case ifds::MASK_REQUIRED_DIGIT:
                  integerMaskDigits_++;
                  inRequiredIntegerDigits = true;
                  integerMask_[integerMaskSize_++] = *pMask ;
                  pMask++;
                  break;
               case ifds::MASK_GROUP_SEPERATOR:
                  flags_ &= ~ifds::pure_integer_mask;
                  flags_ |= ifds::integer_mask;
                  integerMask_[integerMaskSize_++] = *pMask ;
                  pMask++;
                  break;

               case ifds::MASK_DECIMAL_SEPERATOR:
                  flags_ &= ~ifds::pure_integer_mask;
                  flags_ |= ifds::integer_mask;
                  hasDecimal_ = true;
                  pMask++;
               default:
                  flags_ &= !ifds::pure_integer_mask;
                  parseStep = DECIMAL;
                  break;

            }
            break;

         case DECIMAL:
            flags_ |= ifds::decimal_mask;
            switch( *pMask )
            {
               
               case ifds::MASK_NONREQUIRED_DIGIT:
               case ifds::MASK_NONREQUIRED_DIGIT2:
                  inRequiredDecimalDigits = false;
                  decimalMask_[decimalMaskSize_++] = *pMask ;
                  pMask++;
                  break;
               case ifds::MASK_REQUIRED_DIGIT:
                  if( !inRequiredDecimalDigits )
                  {
                     assert(0);
                     BF_CE_THROW( InvalidMaskException, I_( "BFMask::parseMask" ) );
                  }
                  decimalMask_[decimalMaskSize_++] = *pMask ;
                  pMask++;
                  break;

               case ifds::MASK_EXPONENT_SEPERATOR:
                  assert(0); // unsupported 
                  BF_CE_THROW( InvalidMaskException, I_( "BFMask::parseMask" ) );
                  break; 
               default:
                  parseStep = SUFFIX;
                  break;

            }
            break;

         case SUFFIX:
            if( inQuote )
            {
               if( *pMask == ifds::MASK_QUOTE )
               {
                  // exit quote
                  inQuote = false;
                  pMask++;
               }
            }
            else
            {
               if( *pMask == ifds::MASK_QUOTE )
               {
                  pMask++;
                  if( *pMask == ifds::MASK_QUOTE )
                  {
                     // two consecutive quote case
                     suffix_[suffixSize_++] = *pMask ;
                     pMask++;
                     break;
                  }
                  else
                  {
                     // enter quote
                     inQuote = true;
                  }
               }
               else
               {
                  suffix_[suffixSize_++] = *pMask ;
                  pMask++;
               }
            }
            break;

      }

   }

}

