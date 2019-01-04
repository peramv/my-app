#include "stdafx.h"
#include <bfutil\bfifds.hpp>

#include "bfdatafield.hpp"
#include "bfdatafieldfactory.hpp"
#include "bfabstractdatafieldformatter.hpp"
#include <boost\smart_ptr.hpp>
#include <math.h>

#include <bfutil\bfdate.hpp>

BFDataFieldFactory* BFDataField::s_pFactory_ = NULL;

void BFDataField::setFactory( BFDataFieldFactory* pFactory )
{
//   delete s_pFactory_;
   s_pFactory_ = pFactory;
}

BFDataFieldFactory* BFDataField::getFactory( void )
{
   return(s_pFactory_);
}

BFAbstractDataFieldFormatter* BFAbstractTextField::s_pFormatter_ = NULL;
BFAbstractDataFieldFormatter* BFAbstractNumericField::s_pFormatter_ = NULL;
BFAbstractDataFieldFormatter* BFTimeField::s_pFormatter_ = NULL;
BFAbstractDataFieldFormatter* BFDateField::s_pFormatter_ = NULL;

bool BFAbstractTextField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   return( i_strcmp( getValue( rLocale ), prop_->getDefaultValue( rLocale ).c_str() ) == 0 );
}

BFVarTextField::BFVarTextField( const BFVarTextFieldId& id )
: BFAbstractTextField( &s_VarText_FldProp )
, id_( id )
{}

BFDataField::~BFDataField()
{
}

DString BFDataField::getAsText( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

DIINT64 BFDataField::getAsInteger( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

double BFDataField::getAsDouble( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

BigDecimal BFDataField::getAsBigDecimal( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

BFDate BFDataField::getAsDate( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

DString BFDataField::getAsTime( const ClientLocale& rLocale ) const
{
   throw I_( "Not implemented" );
}

bool BFDataField::formatValue( const BFFieldId& idField,
                               DString& value,
                               bool bValidate,
                               unsigned long flags )
{
   if( false == idField.isDynamic() )
   {
      boost::scoped_ptr<BFDataField> field( getFactory()->createField( idField ) );
      const ClientLocale& rLocale = ClientLocaleContext::get();
      field->set( value, false, rLocale );
      field->get( value, true, rLocale, NULL );
   }
   return( true );
}

bool BFDataField::unformatValue( const BFFieldId& idField,
                                 DString& value,
                                 bool bValidate )
{
   if( false == idField.isDynamic() )
   {
      boost::scoped_ptr<BFDataField> field( getFactory()->createField( idField ) );
      const ClientLocale& rLocale = ClientLocaleContext::get();
      field->set( value, true, rLocale );
      field->get( value, false, rLocale, NULL );
   }
   return( true );

}

I_CHAR* BFAbstractNumericField::toStr( I_CHAR* psz, int cb, double dbl ) const
{
   int cDecimals = prop_->getDecimals();

   if( prop_->isDecimal() )
   {
      if( cDecimals == 0 )
      {
         double intPart, floatPart;
         floatPart = modf( dbl, &intPart );
         if( floatPart == 0.0 )
         {
            // no decimals for field, and no decimals in value, so no decimals at all
            i_snprintf( psz, cb, I_( "%-I64d" ), (DIINT64)dbl );
            psz[cb] = 0x00;
         }
         else
         {
            // let return a floating point number with loads'o'precision
            i_snprintf( psz, cb, I_("%-lf" ), dbl );
            psz[cb] = 0x00;
         }
      }
      else
      {
         // decimals, left justified
         i_snprintf( psz, cb, I_( "%-.*lf" ), cDecimals, dbl );
         psz[cb] = 0x00;
      }
   }
   else
   {
      // no decimals, left justified
      i_snprintf( psz, cb, I_( "%-I64d" ), (DIINT64)dbl );
      psz[ cb ] = 0x00;
   }
   return( psz );
}

I_CHAR* BFAbstractNumericField::toStr( I_CHAR* psz, int cb, const BigDecimal& bigd ) const
{
   int cDecimals = prop_->getDecimals();
   DString str;

   if( prop_->isDecimal() ) {
      if( cDecimals == 0 ) {
         str = bigd.asDString();
      } else {
         str = bigd.asDString(-cDecimals);
      }
   } else {
      str = bigd.asDString(0);
   }
   i_strcpy(psz, str.c_str());
   return( psz );
}

I_CHAR* BFAbstractNumericField::toStr( I_CHAR* psz, int cb, DIINT64 i64 ) const
{
   _i64tow( i64, psz, 10 );
   return( psz );
}

#ifdef _DEBUG
I_CHAR* quickCopy( wchar_t* target, const wchar_t* source, size_t count, wchar_t wchPad )
{
   for( ; *source != 0x00 && count > 0; --count, ++source, ++target )
   {
      *target = *source;
   }
   if( wchPad != 0x00 )
   {
      for( ; count > 0; --count, ++target )
      {
         (*target) = wchPad;
      }
   }
   *target = 0x00;
   return( target );
}

char* quickCopy( char* target, const wchar_t* source, size_t count, char chPad )
{
   for( ; *source != 0x00 && count > 0; --count, ++source, ++target )
   {
#pragma warning( push )
#pragma warning( disable: 4244 )
      *target = *source;
#pragma warning( pop )
   }
   if( chPad != 0x00 )
   {
      for( ; count > 0; --count, ++target )
      {
         (*target) = chPad;
      }
   }
   *target = 0x00;
   return( target );
}

I_CHAR* quickCopy( wchar_t* target, const char* source, size_t count, wchar_t wchPad )
{
   for( ; *source != 0x00 && count > 0; --count, ++source, ++target )
   {
      *target = *source;
   }
   if( wchPad != 0x00 )
   {
      for( ; count > 0; --count, ++target )
      {
         (*target) = wchPad;
      }
   }
   *target = 0x00;
   return( target );
}
#endif


bool BFAbstractNumericField::getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const
{
   size_t cbProp = prop_->getLength();
   pBuffer += cbProp;
   return( true );
}

BFIntegerField::BFIntegerField( const BFIntegerFieldId& id,
                                const BFDataFieldProperties* prop )
: BFAbstractNumericField( prop )
, id_( id )
{ 
}

BFIntegerField::BFIntegerField( const BFIntegerField& rhs ) 
: BFAbstractNumericField( rhs )
, id_( rhs.id_ )
{ *this = rhs;}
BFIntegerField& BFIntegerField::operator=( const BFIntegerField& rhs )
{
   prop_ = rhs.prop_;
   dwOptions_ = rhs.dwOptions_;
   value_ = rhs.value_;
   return( *this );
}
BFIntegerField::~BFIntegerField() {}

const BFFieldId& BFIntegerField::getId() const { return(id_);};
DString BFIntegerField::get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask ) return( pMask->format( value, rLocale ) );
      assert( NULL != s_pFormatter_ );
      DString target;
      s_pFormatter_->format( target, value, prop_, rLocale );
      return( target );
   }
   else
   {
      I_CHAR szValue[ 33 ];
      return( DString( toStr( szValue, prop_->getLength(), value ) ) );
   }
}

DString& BFIntegerField::get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( s = pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      s_pFormatter_->format( s, value, prop_, rLocale );
   }
   else
   {
      I_CHAR szValue[ 33 ];
      s = toStr( szValue, prop_->getLength(), value );
   }
   return(s); 
}

void BFIntegerField::set( const DString& v, bool bFormat, const ClientLocale& rLocale )
{ 
   assert( NULL != s_pFormatter_ );
   setValued();
   s_pFormatter_->unformat( value_, v.c_str(), prop_->getLength(), prop_, rLocale );
}

bool BFIntegerField::setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
{
   assert( false );     // unsupported for FAST
   return( false );
}

void BFIntegerField::reset()
{
   clearValued();
}

BFDataField* BFIntegerField::clone()
{
   BFIntegerField* p = new BFIntegerField( id_, prop_ );
   p->dwOptions_ = dwOptions_;
   if( p->isValued() )
   {
      p->value_ = value_;
   }
   return( p );
}

bool BFIntegerField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   return( value_ == prop_->getDefaultIntValue( rLocale ) );
}



DString BFIntegerField::getAsText( const ClientLocale& rLocale ) const
{
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   I_CHAR szValue[ 35 ];
   unsigned int cb = prop_->getLength();
   cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
   return( DString( toStr( szValue, cb-1, value ) ) );
}

DIINT64 BFIntegerField::getAsInteger( const ClientLocale& rLocale ) const
{
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   return(value);
}

double BFIntegerField::getAsDouble( const ClientLocale& rLocale ) const
{
   double value = !isValued() ? (double)prop_->getDefaultIntValue( rLocale ) : (double)value_;
   return( value );
}


BFDecimalField::BFDecimalField( const BFDecimalFieldId& id,
                                const BFDataFieldProperties* prop )

: BFAbstractNumericField( prop )
, id_( id )
{ 
}
BFDecimalField::BFDecimalField( const BFDecimalField& rhs ) 
: BFAbstractNumericField( rhs )
, id_( rhs.id_ )
{ *this = rhs;}
BFDecimalField& BFDecimalField::operator=( const BFDecimalField& rhs )
{
   prop_ = rhs.prop_;
   dwOptions_ = rhs.dwOptions_;
   value_ = rhs.value_;
   return( *this );
}
BFDecimalField::~BFDecimalField() {}

const BFFieldId& BFDecimalField::getId() const { return(id_);};
DString BFDecimalField::get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   double value = !isValued() ? prop_->getDefaultDblValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      DString target;
      s_pFormatter_->format( target, value, prop_, rLocale );
      return( target );
   }
   else
   {
      I_CHAR szValue[ 35 ];
      unsigned int cb = prop_->getLength();
      cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
      return( DString( toStr( szValue, cb-1, value ) ) );
   }
}

DString& BFDecimalField::get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   double value = !isValued() ? prop_->getDefaultDblValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( s = pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      s_pFormatter_->format( s, value, prop_, rLocale );
   }
   else
   {
      I_CHAR szValue[ 35 ];
      unsigned int cb = prop_->getLength();
      cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
      s = toStr( szValue, cb-1, value );
   }
   return(s); 
}

void BFDecimalField::set( const DString& v, bool bFormat, const ClientLocale& rLocale )
{ 
   assert( NULL != s_pFormatter_ );
   setValued();
   s_pFormatter_->unformat( value_, v.c_str(), prop_->getLength(), prop_, rLocale );
}

bool BFDecimalField::setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
{
   assert( false ); // not supported for FAST 
   return( false );
}

void BFDecimalField::reset()
{
   clearValued();
}

BFDataField* BFDecimalField::clone()
{
   BFDecimalField* p = new BFDecimalField( id_, prop_ );
   p->dwOptions_ = dwOptions_;
   if( p->isValued() )
   {
      p->value_ = value_;
   }
   return( p );
}

bool BFDecimalField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   double value = prop_->getDefaultDblValue( rLocale );
   return( value_ == value );
}


DString BFDecimalField::getAsText( const ClientLocale& rLocale ) const
{
   double value = !isValued() ? prop_->getDefaultDblValue( rLocale ) : value_;
   I_CHAR szValue[ 35 ];
   unsigned int cb = prop_->getLength();
   cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
   return( DString( toStr( szValue, cb-1, value ) ) );
}

double BFDecimalField::getAsDouble( const ClientLocale& rLocale ) const
{
   double value = !isValued() ? prop_->getDefaultDblValue( rLocale ) : value_;
   return(value);
}

BFNumericField::BFNumericField( const BFNumericFieldId& id,
                                const BFDataFieldProperties* prop )
: BFAbstractNumericField( prop )
, id_( id )
{ 
}
BFNumericField::BFNumericField( const BFNumericField& rhs ) 
: BFAbstractNumericField( rhs )
, id_( rhs.id_ )
{ *this = rhs;}
BFNumericField& BFNumericField::operator=( const BFNumericField& rhs )
{
   prop_ = rhs.prop_;
   dwOptions_ = rhs.dwOptions_;
   value_ = rhs.value_;
   return( *this );
}
BFNumericField::~BFNumericField() {}

const BFFieldId& BFNumericField::getId() const { return(id_);};
DString BFNumericField::get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      DString target;
      s_pFormatter_->format( target, value, prop_, rLocale );
      return( target );
   }
   else
   {
      I_CHAR szValue[ 33 ];
      return( DString( toStr( szValue, prop_->getLength(), value ) ) );
   }
}

DString& BFNumericField::get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( s = pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      s_pFormatter_->format( s, value, prop_, rLocale );
   }
   else
   {
      I_CHAR szValue[ 33 ];
      s = toStr( szValue, prop_->getLength(), value );
   }
   return(s); 
}
void BFNumericField::set( const DString& v, bool bFormat, const ClientLocale& rLocale )
{ 
   assert( NULL != s_pFormatter_ );
   setValued();
   s_pFormatter_->unformat( value_, v.c_str(), prop_->getLength(), prop_, rLocale );
}

bool BFNumericField::getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const
{

   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;

   // must convert value back to that funky COBOL stuff
   // TODO: deal with negative numbers
   I_CHAR szBuffer[ 33 ];
   _i64tow( value, szBuffer, 10 );

   int cDigits = prop_->getLength();
   int cBuffer = i_strlen( szBuffer );
   assert( cBuffer <= cDigits );

   int iBuffer = 0;
   for( iBuffer = 0; iBuffer < ( cDigits - cBuffer ); ++iBuffer )
   {
      *( pBuffer + iBuffer ) = I_( '0' );
   }
   i_strcpy( pBuffer + iBuffer, szBuffer );

   pBuffer += prop_->getLength();
   return( true );
}

bool BFNumericField::setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
{
   setValued();
   value_ = 0;
   int cb = prop_->getLength();
   if( ( pBuffer + cb ) > pEnd )
   {
      return( false );
   }
   // there are _L characters in the number
   for( int i = 0; i < cb; ++i )
   {
      value_ = ( value_ * 10 ) + ( pBuffer[ i ] - I_( '0' ) );
   }
   pBuffer += cb;
   return( true );
}

void BFNumericField::reset()
{
   clearValued();
}

BFDataField* BFNumericField::clone()
{
   BFNumericField* p = new BFNumericField( id_, prop_ );
   p->dwOptions_ = dwOptions_;
   if( p->isValued() )
   {
      p->value_ = value_;
   }
   return( p );
}

bool BFNumericField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   DIINT64 value = prop_->getDefaultIntValue( rLocale );
   return( value_ == value );
}


DString BFNumericField::getAsText( const ClientLocale& rLocale ) const
{
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   I_CHAR szValue[ 35 ];
   unsigned int cb = prop_->getLength();
   cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
   return( DString( toStr( szValue, cb-1, value ) ) );
}

DIINT64 BFNumericField::getAsInteger( const ClientLocale& rLocale ) const
{
   DIINT64 value = !isValued() ? prop_->getDefaultIntValue( rLocale ) : value_;
   return(value);
}

double BFNumericField::getAsDouble( const ClientLocale& rLocale ) const
{
   double value = !isValued() ? (double)prop_->getDefaultIntValue( rLocale ) : (double)value_;
   return( value );
}

BigDecimal BFNumericField::getAsBigDecimal( const ClientLocale& rLocale ) const
{
   BigDecimal value = !isValued() ? prop_->getDefaultValue( rLocale ) : BigDecimal((_int32)value_);
   return(value);
}

BFBigDecimalField::BFBigDecimalField( const BFBigDecimalFieldId& id,
                                      const BFDataFieldProperties* prop )

: BFAbstractNumericField( prop )
, id_( id )
{ 
}
BFBigDecimalField::BFBigDecimalField( const BFBigDecimalField& rhs ) 
: BFAbstractNumericField( rhs )
, id_( rhs.id_ )
{ *this = rhs;}
BFBigDecimalField& BFBigDecimalField::operator=( const BFBigDecimalField& rhs )
{
   prop_ = rhs.prop_;
   dwOptions_ = rhs.dwOptions_;
   value_ = rhs.value_;
   return( *this );
}
BFBigDecimalField::~BFBigDecimalField() {}

const BFFieldId& BFBigDecimalField::getId() const { return(id_);};
DString BFBigDecimalField::get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   BigDecimal value = !isValued() ? prop_->getDefaultValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      DString target;
      s_pFormatter_->format( target, value, prop_, rLocale );
      return( target );
   }
   else
   {
      I_CHAR szValue[ 35 ];
      unsigned int cb = prop_->getLength();
      cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
      return( DString( toStr( szValue, cb-1, value ) ) );
   }
}

DString& BFBigDecimalField::get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   BigDecimal value = !isValued() ? prop_->getDefaultValue( rLocale ) : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( s = pMask->format( value, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      s_pFormatter_->format( s, value, prop_, rLocale );
   }
   else
   {
      I_CHAR szValue[ 35 ];
      unsigned int cb = prop_->getLength();
      cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
      s = toStr( szValue, cb-1, value );
   }
   return(s); 
}

void BFBigDecimalField::set( const DString& v, bool bFormat, const ClientLocale& rLocale )
{ 
   assert( NULL != s_pFormatter_ );
   setValued();
   s_pFormatter_->unformat( value_, v.c_str(), prop_->getLength(), prop_, rLocale );
}

bool BFBigDecimalField::setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
{
   assert( false ); // not supported for FAST 
   return( false );
}

void BFBigDecimalField::reset()
{
   clearValued();
}

BFDataField* BFBigDecimalField::clone()
{
   BFBigDecimalField* p = new BFBigDecimalField( id_, prop_ );
   p->dwOptions_ = dwOptions_;
   if( p->isValued() )
   {
      p->value_ = value_;
   }
   return( p );
}

bool BFBigDecimalField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   BigDecimal value = prop_->getDefaultValue( rLocale );
   return( value_ == value );
}


DString BFBigDecimalField::getAsText( const ClientLocale& rLocale ) const
{
   BigDecimal value = !isValued() ? prop_->getDefaultValue( rLocale ) : value_;
   I_CHAR szValue[ 35 ];
   unsigned int cb = prop_->getLength();
   cb = std::min( sizeof( szValue ) / sizeof( szValue[0] ), cb );
   return( DString( toStr( szValue, cb-1, value ) ) );
}

BigDecimal BFBigDecimalField::getAsBigDecimal( const ClientLocale& rLocale ) const
{
   BigDecimal value = !isValued() ? prop_->getDefaultValue( rLocale ) : value_;
   return(value);
}

/*==========================================================================
 *----------------------- BFDateField Implementation -----------------------
 *==========================================================================*/
BFDateField::BFDateField( const BFDateFieldId& id,
                          const BFDataFieldProperties* prop )
: BFDataField( prop )
, id_( id )
{ 
}
BFDateField::BFDateField( const BFDateField& rhs ) 
: BFDataField( rhs )
, id_( rhs.id_ )
{ *this = rhs;}
BFDateField& BFDateField::operator=( const BFDateField& rhs )
{
   prop_ = rhs.prop_;
   dwOptions_ = rhs.dwOptions_;
   if( isValued() )
   {
      i_strcpy( value_, rhs.value_ ); 
   }
   return( *this );
}
BFDateField::~BFDateField() {}

const BFFieldId& BFDateField::getId() const { return(id_);};
DString BFDateField::get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( pMask->format( pszValue, rLocale ) );
      }
      assert( NULL != s_pFormatter_ );
      DString target;
      s_pFormatter_->format( target, pszValue, prop_, rLocale );
      return( target );
   }
   return(DString( pszValue )); 
}
DString& BFDateField::get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
{ 
   const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
   if( bFormat )
   {
      if( NULL != pMask )
      {
         return( s = pMask->format( pszValue, rLocale ) ) ;
      }
      assert( NULL != s_pFormatter_ );
      s_pFormatter_->format( s, pszValue, prop_, rLocale );
   }
   else
   {
      s = pszValue; 
   }
   return(s); 
}


void BFDateField::set( const DString& v, bool bFormat, const ClientLocale& rLocale )
{ 
   // for DateFields we will always run through the unformatter ... it is smart enough to leave formatted values alone
   assert( NULL != s_pFormatter_ );
   setValued();
   s_pFormatter_->unformat( value_, v.c_str(), 10, prop_, rLocale );
}

bool BFDateField::getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const
{

   const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
   size_t cb = i_strlen( pszValue );
   quickCopy( pBuffer, pszValue, cb, 0x00 );
   size_t cbProp = prop_->getLength();
   for( ; cb < prop_->getLength(); ++cb )
   {
      pBuffer[ cb ] = I_( ' ' );
   }
   pBuffer += cbProp;
   return( true );
}

bool BFDateField::setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
{
   if( ( pBuffer + 10 ) > pEnd )
   {
      return( false );
   }
   setValued();
   value_[10] = 0;
   quickCopy( value_, pBuffer, 10, 0x00 );
   pBuffer += 10;
   return( true );
}

void BFDateField::reset()
{
   clearValued();
}

BFDataField* BFDateField::clone()
{
   BFDateField* p = new BFDateField( id_, prop_ );
   p->dwOptions_ = dwOptions_;
   if( p->isValued() )
   {
      i_strcpy( p->value_, value_ );
   }
   return( p );
}

bool BFDateField::isDefault( const ClientLocale& rLocale ) const
{
   if( !isValued() )
   {
      return( true );
   }
   return( i_strcmp( value_, prop_->getDefaultValue( rLocale ).c_str() ) == 0 );
}


BFAbstractDataFieldFormatter* BFDateField::getFormatter() const { return(s_pFormatter_);}
void BFDateField::setFormatter( BFAbstractDataFieldFormatter* pFormatter ) { s_pFormatter_ = pFormatter;}



