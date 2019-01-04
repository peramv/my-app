#pragma once

#pragma warning( disable : 4996 )

#include <commonport.h>
#include <dstring.hpp>
#include <bigdecimal.hpp>
#include <clientlocale.hpp>

#include <bfdata\bffieldid.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bfabstractdatafieldformatter.hpp>

#include <assert.h>
#include <math.h>
#include <bfutil\bfdate.hpp>
#include <bfutil\clientlocalecontext.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

#ifdef _DEBUG
BFDATA_LINKAGE I_CHAR* quickCopy( wchar_t* target, const wchar_t* source, size_t count, wchar_t wchPad );
BFDATA_LINKAGE char* quickCopy( char* target, const wchar_t* source, size_t count, char chPad );
BFDATA_LINKAGE I_CHAR* quickCopy( wchar_t* target, const char* source, size_t count, wchar_t wchPad );
#else
static inline I_CHAR* quickCopy( wchar_t* target, const wchar_t* source, size_t count, wchar_t wchPad )
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

static inline char* quickCopy( char* target, const wchar_t* source, size_t count, char chPad )
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

static inline I_CHAR* quickCopy( wchar_t* target, const char* source, size_t count, wchar_t wchPad )
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

class BFCBO;
class BFDataFieldFactory;

/*==========================================================================
 *------------------------------- BFDataField ------------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFDataField
{
public:
   friend class BFCBO;
   friend class BFData;

   enum StateFlagValues
   {
      Updated = 0x0001,
      Required = 0x0002,
      Valid = 0x0004,      // set if field is valid
      Validated = 0x0008,  // set if field requires validation ... this indicates if Valid can be trusted
      ReadOnly = 0x0010,   // set if updates not allowed
   };

   BFDataField( const BFDataFieldProperties* prop )
   : prop_( prop )
   , dwOptions_( 0 )
   {}
   BFDataField( const BFDataField& rhs ) 
   : prop_( rhs.prop_ )
   , dwOptions_( rhs.dwOptions_ )
   { *this = rhs;}
   BFDataField& operator=( const BFDataField& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      return( *this );
   }

   virtual ~BFDataField();

   virtual const BFFieldId& getId() const = 0;
   inline const BFDataFieldProperties* getProperties() const { return(prop_);}

   // bFormat - retrieve the value as a formatted string
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const = 0;
   // bFormat - retrieve the value as a formatted string
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const = 0;
   // bFormat - v is a formatted string
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale ) = 0;

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd ) = 0;
   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const = 0;

   virtual bool isDefault( const ClientLocale& rLocale ) const = 0;
   virtual void reset() = 0;

   virtual BFDataField* clone() = 0;



   virtual BFAbstractDataFieldFormatter* getFormatter() const = 0;

   virtual DString getAsText( const ClientLocale& rLocale ) const;
   virtual DIINT64 getAsInteger( const ClientLocale& rLocale ) const;
   virtual double getAsDouble( const ClientLocale& rLocale ) const;
   virtual BFDate getAsDate( const ClientLocale& rLocale ) const;
   virtual DString getAsTime( const ClientLocale& rLocale ) const;
   virtual BigDecimal getAsBigDecimal( const ClientLocale& rLocale ) const;

protected:
   const BFDataFieldProperties*  prop_;
   DWORD dwOptions_;

   enum bitflags
   {
      initialized = 0x01, nullity = 0x02
   };
   bool isValued() const { return(dwOptions_ & initialized);}
   void setValued() { dwOptions_ |= initialized;}
   void clearValued() { dwOptions_ &= ~initialized;}

   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const = 0;

// Implementation Factory stuff
public:
   static void setFactory( BFDataFieldFactory* pFactory );
   static BFDataFieldFactory* getFactory( void );
private:
   static BFDataFieldFactory* s_pFactory_;

public:
   static bool formatValue( const BFFieldId& idField, 
                            DString& value,
                            bool bValidate = true,
                            unsigned long flags = 0 );

   static bool unformatValue( const BFFieldId& idField,
                              DString& value,
                              bool bValidate = true );



   enum
   {
      USE_SUBSTITUTES = 0x01, USE_MASK = 0x02, STRIP_LEADING = 0x04,
      STRIP_TRAILING = 0x08
   };

};


#ifndef _DEBUG
#endif

/*==========================================================================
 *--------------------------- BFAbstractTextField --------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFAbstractTextField : public BFDataField
{
public:
   explicit BFAbstractTextField( const BFDataFieldProperties* prop )
   : BFDataField( prop ) {}
   BFAbstractTextField( const BFAbstractTextField& rhs )
   : BFDataField( rhs ) {}
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const
   {
      const I_CHAR* pszValue = getValue( rLocale );
      size_t cb = i_strlen( pszValue );
      quickCopy( pBuffer, pszValue, cb, 0x00 );
      size_t cbProp = prop_->getLength();
      for( ; cb < cbProp; ++cb )
      {
         pBuffer[ cb ] = I_( ' ' );
      }
      pBuffer += cbProp;
      return( true );
   }

   virtual DString getAsText( const ClientLocale& rLocale ) const
   {
      return( DString( getValue( rLocale ) ) );
   }

public:
   virtual BFAbstractDataFieldFormatter* getFormatter() const { return(s_pFormatter_);}
   static void setFormatter( BFAbstractDataFieldFormatter* pFormatter ) { s_pFormatter_ = pFormatter;}
protected:
   static BFAbstractDataFieldFormatter* s_pFormatter_;
};

/*==========================================================================
 *----------------------------- BFVarTextField -----------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFVarTextField : public BFAbstractTextField
{
public:
   explicit BFVarTextField( const BFVarTextFieldId& id );

   virtual const BFFieldId& getId() const { return id_; }

   // bFormat - retrieve the value as a formatted string
   virtual DString get(bool bFormat, const ClientLocale &rLocale, const BFMask *pMask) const
   {
      return value_;
   }
   // bFormat - retrieve the value as a formatted string
   virtual DString& get(DString &s, bool bFormat, const ClientLocale &rLocale, const BFMask *pMask) const
   {
      s = value_;
      return( s );
   }
   // bFormat - v is a formatted string
   virtual void set(const DString &v, bool bFormat, const ClientLocale &rLocale)
   {
      setValued();
      value_ = v;
   }

   virtual bool setFromBuffer(const I_CHAR *&pBuffer, const I_CHAR *const pEnd)
   {
      // we can't set this from the buffer as we don't know how much to copy!
      return( false );
   }
   virtual void reset()
   {
      clearValued();
   }
   virtual BFDataField* clone()
   {
      BFVarTextField* p = new BFVarTextField( id_ );
      p->dwOptions_ = dwOptions_;
      p->value_ = value_;
      return( p );
   }

   // special VarText only member functions
   const DString& getVarText() const { return value_; }


protected:
   virtual const I_CHAR* getValue(const ClientLocale &rLocale) const
   {
      return value_.c_str();
   }
protected:
   const BFVarTextFieldId&  id_;
   DString value_;
};

/*==========================================================================
 *----------------------------- BFTextField<_L> ----------------------------
 *==========================================================================*/
template <int _L>
class BFTextField : public BFAbstractTextField
{
public:
   BFTextField( const BFTextFieldId& id,
                const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField( const BFTextField<_L>& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField<_L>& operator=( const BFTextField<_L>& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), _L, prop_, rLocale );
      }
      else
      {
         value_[ _L ] = 0x00;
         quickCopy( value_, v.c_str(), _L, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + _L ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[_L] = 0;
      quickCopy( value_, pBuffer, _L, 0x00 );
      pBuffer += _L;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField<_L>* p = new BFTextField<_L>( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }


protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[_L + 1];
};

/*==========================================================================
 *----------------------------- BFTextField_60 -----------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTextField_60 : public BFAbstractTextField
{
public:
   BFTextField_60( const BFTextFieldId& id,
                   const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField_60( const BFTextField_60& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField_60& operator=( const BFTextField_60& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField_60() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 60, prop_, rLocale );
      }
      else
      {
         value_[ 60 ] = 0x00;
         quickCopy( value_, v.c_str(), 60, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + 60 ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[60] = 0;
      quickCopy( value_, pBuffer, 60, 0x00 );
      pBuffer += 60;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField_60* p = new BFTextField_60( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }


protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[61];
};

/*==========================================================================
 *----------------------------- BFTextField_10 -----------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTextField_10 : public BFAbstractTextField
{
public:
   BFTextField_10( const BFTextFieldId& id,
                   const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField_10( const BFTextField_10& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField_10& operator=( const BFTextField_10& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField_10() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 10, prop_, rLocale );
      }
      else
      {
         value_[ 10 ] = 0x00;
         quickCopy( value_, v.c_str(), 10, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
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

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField_10* p = new BFTextField_10( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }


protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[11];
};

/*==========================================================================
 *----------------------------- BFTextField_6 ------------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTextField_6 : public BFAbstractTextField
{
public:
   BFTextField_6( const BFTextFieldId& id,
                  const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField_6( const BFTextField_6& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField_6& operator=( const BFTextField_6& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField_6() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 6, prop_, rLocale );
      }
      else
      {
         value_[ 6 ] = 0x00;
         quickCopy( value_, v.c_str(), 6, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + 6 ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[6] = 0;
      quickCopy( value_, pBuffer, 6, 0x00 );
      pBuffer += 6;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField_6* p = new BFTextField_6( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }


protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[7];
};

/*==========================================================================
 *----------------------------- BFTextField_2 ------------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTextField_2 : public BFAbstractTextField
{
public:
   BFTextField_2( const BFTextFieldId& id,
                  const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField_2( const BFTextField_2& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField_2& operator=( const BFTextField_2& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField_2() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 2, prop_, rLocale );
      }
      else
      {
         value_[ 2 ] = 0x00;
         quickCopy( value_, v.c_str(), 2, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + 2 ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[2] = 0;
      quickCopy( value_, pBuffer, 2, 0x00 );
      pBuffer += 2;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField_2* p = new BFTextField_2( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }

protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[3];
};

/*==========================================================================
 *------------------------------ BFTextField_1 -----------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTextField_1 : public BFAbstractTextField
{
public:
   BFTextField_1( const BFTextFieldId& id,
                  const BFDataFieldProperties* prop )
   : BFAbstractTextField( prop )
   , id_( id )
   { 
   }
   BFTextField_1( const BFTextField_1& rhs ) 
   : BFAbstractTextField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}
   BFTextField_1& operator=( const BFTextField_1& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }
   virtual ~BFTextField_1() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
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
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 1, prop_, rLocale );
      }
      else
      {
         value_[ 1 ] = 0x00;
         quickCopy( value_, v.c_str(), 1, I_(' ') ); 
      }
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + 1 ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[0] = *pBuffer;
      value_[1] = 0;
      pBuffer++;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTextField_1* p = new BFTextField_1( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }



protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

protected:
   const BFTextFieldId&  id_;
   I_CHAR value_[2];
};

/*==========================================================================
 *------------------------- BFAbstractNumericField -------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFAbstractNumericField : public BFDataField
{
public:
   explicit BFAbstractNumericField( const BFDataFieldProperties* prop )
   : BFDataField( prop ) 
   {}
   BFAbstractNumericField( const BFAbstractNumericField& rhs )
   : BFDataField( rhs )
   {}


   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const;
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const { assert( 0 ); return( NULL );}


public:
   virtual BFAbstractDataFieldFormatter* getFormatter() const { return(s_pFormatter_);}
   static void setFormatter( BFAbstractDataFieldFormatter* pFormatter ) { s_pFormatter_ = pFormatter;}
protected:
   static BFAbstractDataFieldFormatter* s_pFormatter_;

protected:
   I_CHAR* toStr( I_CHAR* psz, int cb, double dbl ) const;
   I_CHAR* toStr( I_CHAR* psz, int cb, DIINT64 i64 ) const;
   I_CHAR* toStr( I_CHAR* psz, int cb, const BigDecimal& bigd ) const;
};

/*==========================================================================
 *--------------------------- BFIntegerField<_L> ---------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFIntegerField : public BFAbstractNumericField
{
public:
   BFIntegerField( const BFIntegerFieldId& id,
                   const BFDataFieldProperties* prop );
   BFIntegerField( const BFIntegerField& rhs ) ;
   BFIntegerField& operator=( const BFIntegerField& rhs );
   virtual ~BFIntegerField();
   virtual const BFFieldId& getId() const;
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const ;
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const ;
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale );
   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd );
   virtual void reset();
   virtual BFDataField* clone();
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual DString getAsText( const ClientLocale& rLocale ) const;
   virtual DIINT64 getAsInteger( const ClientLocale& rLocale ) const;
   virtual double getAsDouble( const ClientLocale& rLocale ) const;

private:
   const BFIntegerFieldId&  id_;
   DIINT64  value_;
};

/*==========================================================================
 *--------------------------- BFDecimalField ---------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFDecimalField : public BFAbstractNumericField
{
public:
   BFDecimalField( const BFDecimalFieldId& id,
                   const BFDataFieldProperties* prop );
   BFDecimalField( const BFDecimalField& rhs );
   BFDecimalField& operator=( const BFDecimalField& rhs );
   virtual ~BFDecimalField();
   virtual const BFFieldId& getId() const;
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale );
   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd );
   virtual void reset();
   virtual BFDataField* clone();
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual DString getAsText( const ClientLocale& rLocale ) const;
   virtual double getAsDouble( const ClientLocale& rLocale ) const;

private:
   const BFDecimalFieldId&  id_;
   double value_;
};

/*==========================================================================
 *--------------------------- BFNumericField ---------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFNumericField : public BFAbstractNumericField
{
public:
   BFNumericField( const BFNumericFieldId& id,
                   const BFDataFieldProperties* prop );
   BFNumericField( const BFNumericField& rhs );
   BFNumericField& operator=( const BFNumericField& rhs );
   virtual ~BFNumericField();
   virtual const BFFieldId& getId() const;
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale );
   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const;
   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd );
   virtual void reset();
   virtual BFDataField* clone();
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual DString getAsText( const ClientLocale& rLocale ) const;
   virtual DIINT64 getAsInteger( const ClientLocale& rLocale ) const;
   virtual double getAsDouble( const ClientLocale& rLocale ) const;
   virtual BigDecimal getAsBigDecimal( const ClientLocale& rLocale ) const;

private:
   const BFNumericFieldId&  id_;
   DIINT64   value_;
};

/*==========================================================================
 *--------------------------- BFBigDecimalField ---------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFBigDecimalField : public BFAbstractNumericField
{
public:
   BFBigDecimalField( const BFBigDecimalFieldId& id,
                      const BFDataFieldProperties* prop );
   BFBigDecimalField( const BFBigDecimalField& rhs );
   BFBigDecimalField& operator=( const BFBigDecimalField& rhs );
   virtual ~BFBigDecimalField();
   virtual const BFFieldId& getId() const;
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale );
   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd );
   virtual void reset();
   virtual BFDataField* clone();
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual DString getAsText( const ClientLocale& rLocale ) const;
   virtual BigDecimal getAsBigDecimal( const ClientLocale& rLocale ) const;

private:
   const BFBigDecimalFieldId&  id_;
   BigDecimal value_;
};

/*==========================================================================
 *------------------------------- BFDateField ------------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFDateField : public BFDataField
{
public:
   BFDateField( const BFDateFieldId& id,
                const BFDataFieldProperties* prop );
   BFDateField( const BFDateField& rhs );
   BFDateField& operator=( const BFDateField& rhs );
   virtual ~BFDateField();
   virtual const BFFieldId& getId() const;
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const;
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale );
   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const;
   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd );
   virtual void reset();
   virtual BFDataField* clone();
   virtual bool isDefault( const ClientLocale& rLocale ) const;

   virtual DString getAsText( const ClientLocale& rLocale ) const
   {
      return( DString( getValue( rLocale ) ) );
   }
   virtual BFDate getAsDate( const ClientLocale& rLocale ) const
   {
      return( BFDate( getValue( rLocale ), BFDate::DF_DDATE_DEPRECATED ) );
   }

public:
   virtual BFAbstractDataFieldFormatter* getFormatter() const;
   static void setFormatter( BFAbstractDataFieldFormatter* pFormatter );
protected:
   static BFAbstractDataFieldFormatter* s_pFormatter_;

protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

private:
   const BFDateFieldId& id_;
   I_CHAR value_[11];     // 'native mode' is ISO (ccyy-mm-dd)
};

/*==========================================================================
 *------------------------------- BFTimeField ------------------------------
 *==========================================================================*/
class BFDATA_LINKAGE BFTimeField : public BFDataField
{
public:
   BFTimeField( const BFTimeFieldId& id,
                const BFDataFieldProperties* prop )
   : BFDataField( prop )
   , id_( id )
   { 
   }

   BFTimeField( const BFTimeField& rhs ) 
   : BFDataField( rhs )
   , id_( rhs.id_ )
   { *this = rhs;}

   BFTimeField& operator=( const BFTimeField& rhs )
   {
      prop_ = rhs.prop_;
      dwOptions_ = rhs.dwOptions_;
      if( isValued() )
      {
         i_strcpy( value_, rhs.value_ );
      }
      return( *this );
   }

   virtual ~BFTimeField() {}

   virtual const BFFieldId& getId() const { return(id_);};
   virtual DString get( bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask ) return( pMask->format( pszValue, rLocale ) );
         assert( NULL != s_pFormatter_ );
         DString target;
         s_pFormatter_->format( target, pszValue, prop_, rLocale );
         return( target );
      }
      return(DString( pszValue ));}
   virtual DString& get( DString& s, bool bFormat, const ClientLocale& rLocale, const BFMask* pMask ) const 
   { 
      const I_CHAR* pszValue = !isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_;
      if( bFormat )
      {
         if( NULL != pMask )
         {
            return( s = pMask->format( pszValue, rLocale ) );
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
   virtual void set( const DString& v, bool bFormat, const ClientLocale& rLocale )
   { 
      setValued();
      if( bFormat )
      {
         assert( NULL != s_pFormatter_ );
         s_pFormatter_->unformat( value_, v.c_str(), 5, prop_, rLocale );
      }
      else
      {
         value_[ 5 ] = 0x00;
         quickCopy( value_, v.c_str(), 5, 0x00 ); 
      }
   }

   virtual bool getToBuffer( I_CHAR*& pBuffer, const ClientLocale& rLocale ) const
   {

      size_t cb = i_strlen( value_ );

      quickCopy( pBuffer, value_, cb, 0x00 );
      size_t cbProp = prop_->getLength();
      for( ; cb < (size_t) prop_->getLength(); ++cb )
      {
         pBuffer[ cb ] = I_( ' ' );
      }
      pBuffer += cbProp;
      return( true );
   }

   virtual bool setFromBuffer( const I_CHAR*& pBuffer, const I_CHAR* const pEnd )
   {
      if( ( pBuffer + 5 ) > pEnd )
      {
         return( false );
      }
      setValued();
      value_[5] = 0;
      quickCopy( value_, pBuffer, 5, 0x00 );
      pBuffer += 5;
      return( true );
   }

   virtual void reset()
   {
      clearValued();
   }

   virtual BFDataField* clone()
   {
      BFTimeField* p = new BFTimeField( id_, prop_ );
      p->dwOptions_ = dwOptions_;
      if( isValued() )
      {
         i_strcpy( p->value_, value_ );
      }
      return( p );
   }

   virtual bool isDefault( const ClientLocale& rLocale ) const
   {
      if( !isValued() )
      {
         return( true );
      }
      return( i_strcmp( value_, prop_->getDefaultValue( rLocale ).c_str() ) == 0 );
   }


   virtual DString getAsText( const ClientLocale& rLocale ) const
   {
      return( DString( getValue( rLocale ) ) );
   }
   virtual DString getAsTime( const ClientLocale& rLocale ) const
   {
      return( DString( getValue( rLocale ) ) );
   }


protected:
   virtual const I_CHAR* getValue( const ClientLocale& rLocale ) const 
   { return(!isValued() ? prop_->getDefaultValue( rLocale ).c_str() : value_);}

public:
   virtual BFAbstractDataFieldFormatter* getFormatter() const { return(s_pFormatter_);}
   static void setFormatter( BFAbstractDataFieldFormatter* pFormatter ) { s_pFormatter_ = pFormatter;}
protected:
   static BFAbstractDataFieldFormatter* s_pFormatter_;

private:
   const BFTimeFieldId& id_;
   I_CHAR value_[6];     // 'native mode' is ISO (hh:mm)
};


