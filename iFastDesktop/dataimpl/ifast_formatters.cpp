#include "stdafx.h"

#include <srcprag.h>
#include <commonport.h>
#include <bfdata\bfabstractdatafieldformatter.hpp>
#include <bfdata\bfdatafield.hpp>
#include <bfutil\bfdate.hpp>
#include <configmanager.hpp>
#include <bfutil\localetraits.hpp>

#include <bfutil\bfguard.hpp>
#include <bfutil\bfcritsec.hpp>

inline static bool isBlank( const I_CHAR* psz )
{
   for( ; *psz != 0x00; ++psz )
   {
      if( !i_isspace( *psz ) )
      {
         return( false );
      }
   }
   return( true );
}

class MFCAN_DateFieldFormatter : public BFAbstractDataFieldFormatter
{
public:
   MFCAN_DateFieldFormatter()
   {
      BFDateField::setFormatter( this );
   }
   virtual bool format( DString&, double, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, DIINT64, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, const BigDecimal&, const BFDataFieldProperties*, const ClientLocale&)  { assert( 0 ); return( false );}
   virtual bool format( DString& strTarget, const I_CHAR* pszSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      // convert unformatted date into formatted date
      if( i_strlen( pszSource ) != 8 )
      {
         strTarget = I_( "" );
         return( false );
      }

      BFDate d( pszSource, getHostMask() );
      if( d.isNull() )
      {
         strTarget = pszSource;
         return( false );
      }
      strTarget = d.get( getDisplayMask( locale ) );

      return(true);
   }
   virtual bool unformat( double&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( DIINT64&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( BigDecimal&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale&) { assert( 0 ); return( false );}
   virtual bool unformat( I_CHAR* pszTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      BFDate d( pszSource, getDisplayMask( locale ) );
      if( d.isNull() )
      {
         i_strncpy( pszTarget, pszSource, 10 );
         pszTarget[ 10 ] = 0x00;
      }
      else
      {
         i_strcpy( pszTarget, d.get( getHostMask() ).c_str() );
      }

      return(true);
   }
   static BFDate::DATE_FORMAT getHostMask();
   static BFDate::DATE_FORMAT getDisplayMask( const ClientLocale& locale );
private:
   static BFCritSec s_cs_;
   static BFDate::DATE_FORMAT s_eHostMask_;
   static BFDate::DATE_FORMAT s_eDisplayMask_;
};

BFCritSec MFCAN_DateFieldFormatter::s_cs_;
BFDate::DATE_FORMAT MFCAN_DateFieldFormatter::s_eHostMask_ = BFDate::DF_NULL;
BFDate::DATE_FORMAT MFCAN_DateFieldFormatter::s_eDisplayMask_ = BFDate::DF_NULL;

BFDate::DATE_FORMAT MFCAN_DateFieldFormatter::getHostMask()
{
   if( BFDate::DF_NULL != s_eHostMask_ )
   {
      return( s_eHostMask_ );
   }

   BFGuard g( s_cs_ );

   DString dstrMask = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "HostMasks" ), I_( "D" ) );
   if( dstrMask.empty() )
   {
      dstrMask = I_( "MMddyyyy" );
   }
   s_eHostMask_ = BFDate::inferMaskFormat( dstrMask );

   return( s_eHostMask_ );
}

BFDate::DATE_FORMAT MFCAN_DateFieldFormatter::getDisplayMask( const ClientLocale& locale )
{
   if( BFDate::DF_NULL != s_eDisplayMask_ )
   {
      return( s_eDisplayMask_ );
   }

   BFGuard g( s_cs_ );

   DString dstrMask = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "DisplayMasks" ), locale.getLocale() + I_( "-D" ) );
   if( dstrMask.empty() )
   {
      dstrMask = I_( "dd/MM/yyyy" );
   }
   s_eDisplayMask_ = BFDate::inferMaskFormat( dstrMask );

   return( s_eDisplayMask_ );
}

static MFCAN_DateFieldFormatter dateFormatter;



class MFCAN_TextFieldFormatter : public BFAbstractDataFieldFormatter
{
public:
   MFCAN_TextFieldFormatter()
   {
      BFAbstractTextField::setFormatter( this );
   }
   virtual bool format( DString&, double, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, DIINT64, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, const BigDecimal&, const BFDataFieldProperties*, const ClientLocale&)  { assert( 0 ); return( false );}
   virtual bool format( DString& strTarget, const I_CHAR* pszSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      bool bRc = true;
      if( NULL != props->getSubstitutionSet( locale ) )
      {
         try
         {
            if( isBlank( pszSource ) )
            {
               strTarget = "";
               return( true );
            }
            strTarget = props->getSubstitutionSet( locale )->getValue( pszSource );
            return( true );
         }
         catch( BFSubstitutionException& )
         {
            bRc = false;
         }
      }
      strTarget = pszSource;
      return(bRc);
   }
   virtual bool unformat( double&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( DIINT64&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( BigDecimal&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale&) { assert( 0 ); return( false );}
   virtual bool unformat( I_CHAR* pszTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      if( NULL != props->getSubstitutionSet( locale ) )
      {
         try
         {
            if( isBlank( pszSource ) )
            {
               *pszTarget = 0x00;
               return( true );
            }
            const I_CHAR* target = props->getSubstitutionSet( locale )->getKey( pszSource );
            assert( NULL != target );
            quickCopy( pszTarget, target, cChars, I_( ' ' ) );
            return( true );

         }
         catch( BFSubstitutionException& )
         {
            return( false );
         }
      }
      quickCopy( pszTarget, pszSource, cChars, I_( ' ' ) );
      return( true );
   }
};
static MFCAN_TextFieldFormatter textFormatter;

class MFCAN_NumericFieldFormatter : public BFAbstractDataFieldFormatter
{
public:
   MFCAN_NumericFieldFormatter()
   {
      BFAbstractNumericField::setFormatter( this );
   }
   virtual bool format( DString& strTarget, double dblSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      const BFMask* pMask = props->getMask( locale );
      if( NULL != pMask )
      {
         strTarget = pMask->format( dblSource, locale );
      }
      else
      {
         if( dblSource == 0.0 )
         {
            strTarget = I_( "" );
         }
         else
         {
            I_CHAR szValue[ 256 ];
            szValue[ props->getLength() ] = 0x00;
            int cDecimals = props->getDecimals();
            i_snprintf( szValue, sizeof( szValue ) / sizeof( szValue[0] ) - 1, I_( "%-.*lf" ), cDecimals, dblSource );
            szValue[ 255 ] = 0x00;
            strTarget = szValue;
         }
      }
      return(true);
   }

   virtual bool format( DString& strTarget, const BigDecimal& bigdSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      const BFMask* pMask = props->getMask( locale );
      if( NULL != pMask )
      {
         strTarget = pMask->format( bigdSource, locale );
      }
      else
      {
         if( bigdSource == "0.0" )
         {
            strTarget = I_( "" );
         }
         else
         {
            int cDecimals = props->getDecimals();
            if( cDecimals == 0 ) {
               strTarget = bigdSource.asDString();
            } else {
               strTarget = bigdSource.asDString(-cDecimals);
            }
         }
      }
      return(true);
   }

   virtual bool format( DString& strTarget, DIINT64 i64Source, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      const BFMask* pMask = props->getMask( locale );
      if( NULL != pMask )
      {
         strTarget = pMask->format( i64Source, locale );
      }
      else
      {
         if( i64Source == 0 )
         {
            strTarget = I_( "" );
         }
         else
         {
            I_CHAR szValue[ 34 ];
            _i64tow( i64Source, szValue, 10 );
            strTarget = szValue;
         }
      }
      return(true);
   }

   virtual bool format( DString& strTarget, const I_CHAR* pszSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   { assert( 0 ); return( false );}

   virtual bool unformat( double& dblTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      bool bFormatted = true;

      const bfutil::LocaleTraits& rTraits = bfutil::LocaleTraits::get( locale );
      I_CHAR chThousand = rTraits.getGroupSeparator();
      I_CHAR chDecimal = rTraits.getRadixSeparator();
      I_CHAR chNegative = rTraits.getNegativeSign();

      // look for embedded thousandSeparators between first digit and decimal point

      const I_CHAR* pszFirstDigit = pszSource;
      for( ; *pszFirstDigit != 0x00 && !i_isdigit( *pszFirstDigit ); ++pszFirstDigit );
//CP20030421      const I_CHAR* pszFirstDigit = i_strstr( pszSource, I_( "0123456789" ) );
      if( NULL != pszFirstDigit )
      {
         const I_CHAR* pszDecimal = i_strchr( pszSource, chDecimal );
         if( NULL != pszDecimal && pszDecimal < pszFirstDigit )
         {
            // there is a decimal point and it precedes the first digit so pszSource is not formatted (e.g. .878 )
            bFormatted = false;
         }
         else
         {
            const I_CHAR* pszThousand = i_strchr( pszFirstDigit, chThousand );
            if( NULL != pszThousand )
            {
               // we found a thousand separator
               // if it is between the first digit and the decimal point then we are formatted
               if( NULL != pszDecimal && ( pszFirstDigit < pszThousand ) && ( pszDecimal > pszThousand ) )
               {
                  bFormatted = true;
               }
               else
               {
                  bFormatted = false;
               }
            }
            else
            {
               // there is no thousands separator, so pszSource is not formatted
               bFormatted = false;
            }
         }
      }


      const BFMask* pMask = props->getMask( locale );
      if( bFormatted && ( NULL != pMask ) )
      {
         pMask->parse( dblTarget, pszSource, locale );
      }
      else
      {
         // remove all of the non-numeric characters
         I_CHAR szValue[256];
         int iValue = 0;
         for( ; ( iValue < ( sizeof( szValue ) / sizeof( szValue[0] ) ) ) && *pszSource != 0x00; ++pszSource )
         {
            if( ( i_isdigit( *pszSource) ) || 
                ( *pszSource == chDecimal ) || 
                ( *pszSource == chNegative )
              )
            {
               szValue[ iValue++ ] = *pszSource;
            }
         }
         szValue[ iValue ] = 0x00;

         // and convert to double

         I_CHAR* pEnd = NULL;
         dblTarget = wcstod( szValue, &pEnd );
      }
      return( true );
   }

   virtual bool unformat( BigDecimal& bigdTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      bool bFormatted = true;

      const bfutil::LocaleTraits& rTraits = bfutil::LocaleTraits::get( locale );
      I_CHAR chThousand = rTraits.getGroupSeparator();
      I_CHAR chDecimal = rTraits.getRadixSeparator();
      I_CHAR chNegative = rTraits.getNegativeSign();

      // look for embedded thousandSeparators between first digit and decimal point

      const I_CHAR* pszFirstDigit = pszSource;
      for( ; *pszFirstDigit != 0x00 && !i_isdigit( *pszFirstDigit ); ++pszFirstDigit );
//CP20030421      const I_CHAR* pszFirstDigit = i_strstr( pszSource, I_( "0123456789" ) );
      if( NULL != pszFirstDigit )
      {
         const I_CHAR* pszDecimal = i_strchr( pszSource, chDecimal );
         if( NULL != pszDecimal && pszDecimal < pszFirstDigit )
         {
            // there is a decimal point and it precedes the first digit so pszSource is not formatted (e.g. .878 )
            bFormatted = false;
         }
         else
         {
            const I_CHAR* pszThousand = i_strchr( pszFirstDigit, chThousand );
            if( NULL != pszThousand )
            {
               // we found a thousand separator
               // if it is between the first digit and the decimal point then we are formatted
               if( NULL != pszDecimal && ( pszFirstDigit < pszThousand ) && ( pszDecimal > pszThousand ) )
               {
                  bFormatted = true;
               }
               else
               {
                  bFormatted = false;
               }
            }
            else
            {
               // there is no thousands separator, so pszSource is not formatted
               bFormatted = false;
            }
         }
      }


      const BFMask* pMask = props->getMask( locale );
      if( bFormatted && ( NULL != pMask ) )
      {
         pMask->parse( bigdTarget, pszSource, locale );
      }
      else
      {
         // remove all of the non-numeric characters
         I_CHAR szValue[256];
         int iValue = 0;
         for( ; ( iValue < ( sizeof( szValue ) / sizeof( szValue[0] ) ) ) && *pszSource != 0x00; ++pszSource )
         {
            if( ( i_isdigit( *pszSource) ) || 
                ( *pszSource == chDecimal ) || 
                ( *pszSource == chNegative )
              )
            {
               szValue[ iValue++ ] = *pszSource;
            }
         }
         szValue[ iValue ] = 0x00;

         // and convert to big decimal
         bigdTarget = DString(szValue);
      }
      return( true );
   }

   virtual bool unformat( DIINT64& i64Target, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      bool bFormatted = false;

      const bfutil::LocaleTraits& rTraits = bfutil::LocaleTraits::get( locale );
      I_CHAR chThousand = rTraits.getGroupSeparator();
      I_CHAR chDecimal = rTraits.getRadixSeparator();
      I_CHAR chNegative = rTraits.getNegativeSign();

      // look for embedded thousandSeparators between first digit and last digit (or end )
      const I_CHAR* pszFirstDigit = pszSource;
      for( ; *pszFirstDigit != 0x00 && !i_isdigit( *pszFirstDigit ); ++pszFirstDigit );
//CP20030421      const I_CHAR* pszFirstDigit = i_strstr( pszSource, I_( "0123456789" ) );
      if( NULL != pszFirstDigit )
      {
         const I_CHAR* pszThousand = i_strchr( pszFirstDigit, chThousand );
         if( NULL != pszThousand )
         {
            // we found a thousand separator
            bFormatted = true;
         }
         else
         {
            // there is no thousands separator, so pszSource is not formatted
            bFormatted = false;
         }
      }

      const BFMask* pMask = props->getMask( locale );
      if( bFormatted && ( NULL != pMask ) )
      {
         // it's FAST, so there's no fancy funny characters.  Remove extraneous formatting
         pMask->parse( i64Target, pszSource, locale );
      }
      else
      {
         // remove all of the ',' and spaces
         I_CHAR szValue[34];
         int iValue = 0;
         for( ; ( iValue < ( sizeof( szValue ) / sizeof( szValue[0] ) ) ) && *pszSource != 0x00; ++pszSource )
         {
            if( ( i_isdigit( *pszSource) ) || 
                ( *pszSource == chNegative )
              )
            {
               szValue[ iValue++ ] = *pszSource;
            }
         }
         szValue[ iValue ] = 0x00;

         // and convert to int64

         I_CHAR* pEnd = NULL;
         i64Target = _wtoi64( szValue );
      }
      return( true );
   }

   virtual bool unformat( I_CHAR* pszTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   { assert( 0 ); return( false );}
};

static MFCAN_NumericFieldFormatter numericFormatter;


class MFCAN_TimeFieldFormatter : public BFAbstractDataFieldFormatter
{
public:
   MFCAN_TimeFieldFormatter()
   {
      BFTimeField::setFormatter( this );
   }
   virtual bool format( DString&, double, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, DIINT64, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool format( DString&, const BigDecimal&, const BFDataFieldProperties*, const ClientLocale&)  { assert( 0 ); return( false );}
   virtual bool format( DString& strTarget, const I_CHAR* pszSource, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      strTarget = pszSource;
      return(true);
   }
   virtual bool unformat( double&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( DIINT64&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale& ) { assert( 0 ); return( false );}
   virtual bool unformat( BigDecimal&, const I_CHAR*, size_t, const BFDataFieldProperties*, const ClientLocale&) { assert( 0 ); return( false );}
   virtual bool unformat( I_CHAR* pszTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale )
   {
      quickCopy( pszTarget, pszSource, cChars, 0x00 );
      return(true);
   }
};
static MFCAN_TimeFieldFormatter timeFormatter;


