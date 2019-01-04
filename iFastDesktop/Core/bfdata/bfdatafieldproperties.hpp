#pragma once

#include <commonport.h>
#include <dstring.hpp>
#include <clientlocale.hpp>
#include <map>
#include <bfdata\bffieldid.hpp>
#include <bfdata\bfsubstitutionset.hpp>
#include <bfdata\bfmask.hpp>
#include <bfdata\bfdataexception.hpp>
#include <assert.h>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

BF_DECL_BASE_EXCEPTION( BFDataFieldPropertiesException );

// Function to choose a Default Value                                                             
typedef const DString& ( *PBF_DVF )( const ClientLocale& );
typedef DIINT64 ( *PBF_DIVF )( const ClientLocale& );
typedef double ( *PBF_DDVF )( const ClientLocale& );

// Function to choose a Field Label
typedef const DString& ( *PBF_FLF )( const ClientLocale& );

// Function choose a Substitution Set given a ClientLocale
// This function is specific to a SubstitutionSet
typedef const BFSubstitutionSet& ( *PBF_SSC )( const ClientLocale& );

// Function to choose a SubstitutionSet Chooser Function given a ClientLocale
// This function is specific to a field
typedef PBF_SSC( *PBF_SSCFC )( const ClientLocale& );



class BFDataFieldProperties;
typedef std::map< BFFieldId, BFDataFieldProperties* > BFDataFieldPropertiesMap;

enum BFDataFieldJustification
{
   None, Left, Centre, Right
};

class BFDATA_LINKAGE BFDataFieldProperties
{
public:
   enum Type
   {
      numeric, date, decimal, integer, bigdecimal, time, text, vartext
   };

   BFDataFieldProperties( enum Type eType,
                          const BFFieldId& idField,
                          int length,
                          int minLength,
                          int decimals,
                          PBF_MCF maskChooser,
                          PBF_DVF defValueFunc,
                          PBF_DIVF defValueIFunc,
                          PBF_DDVF defValueDFunc,
                          PBF_FLF labelFunc,
                          const DString& name,
                          bool bAllowNull,
                          BFDataFieldJustification eJustification,
                          PBF_SSCFC pSubSetChooser
                        )
   : eType_( eType )
   , length_( length )
   , decimals_( decimals )
   , maskChooser_( maskChooser )
   , bAllowNull_( bAllowNull )
   , eJustification_( eJustification )
   , pSubstSetChooser_( pSubSetChooser )
   , minLength_( minLength )
   , pDefValueFunc_( defValueFunc )
   , pDefValueIFunc_( defValueIFunc )
   , pDefValueDFunc_( defValueDFunc )
   , pLabelFunc_( labelFunc )
   {
      BFDataFieldPropertiesMap& propMap = getMap();
      propMap[ idField ] = this;
   }


   virtual ~BFDataFieldProperties(){}

   inline int getLength() const { return( length_ );}
   inline int getMinLength() const { return( minLength_ );}
   inline int getDecimals() const { return( decimals_ );}
   inline const BFMask* getMask( const ClientLocale& locale ) const { return( maskChooser_ != NULL ? &( maskChooser_( locale ) ) : NULL );}
   inline bool canBeNull() const { return( bAllowNull_ );}
   inline const BFSubstitutionSet* getSubstitutionSet( const ClientLocale& locale ) const 
   { 
      if( NULL == pSubstSetChooser_ ) return( NULL );
      PBF_SSC pFn = pSubstSetChooser_( locale );
      if( NULL != pFn )
      {
         return( &( pFn( locale ) ) );
      }
      return( NULL ); 
   }

   inline BFDataFieldJustification getJustification() const { return( eJustification_ );}

   inline const DString& getDefaultValue( const ClientLocale& locale ) const { assert( NULL != pDefValueFunc_ ); return( pDefValueFunc_( locale ) );}
   inline DIINT64 getDefaultIntValue( const ClientLocale& locale ) const { assert( NULL != pDefValueIFunc_ ); return( pDefValueIFunc_( locale ) );}
   inline double getDefaultDblValue( const ClientLocale& locale ) const { assert( NULL != pDefValueDFunc_ ); return( pDefValueDFunc_( locale ) );}

   inline const DString& getLabel( const ClientLocale& locale ) const { return( pLabelFunc_( locale ) );}

   inline bool isDate() const { return( eType_ == Type::date );}
   inline bool isTime() const { return( eType_ == Type::time );}
   inline bool isText() const { return( ( eType_ == Type::text ) || ( eType_ == Type::vartext ) );}
   inline bool isVarText() const { return( eType_ == Type::vartext );}
   inline bool isNumeric() const { 
      switch( eType_ )
      {
         case integer:
         case decimal:
         case numeric:
         case bigdecimal:
            return( true );
      }
      return( false );
   }
   inline bool isInteger() const { return(eType_ == integer || eType_ == numeric);}
   inline bool isDecimal() const { return(eType_ == decimal || eType_ == bigdecimal);}

   enum Type getType() const
   {
      return(eType_);
   }

   bool getAllSubstituteValues( DString &subValues,
                                const ClientLocale& locale,
                                bool bUsePropertiesOrder = false ) const;

   static const BFDataFieldProperties* get( const BFFieldId& id );

private:
   // properties of a field are:
   //   length
   //   decimals
   //   'type' is implicit in the derived class
   //       $     Money    (not used)
   //       %     Percent  (not used)
   //       1     ??       (not used)
   //       9     numeric        (can't have decimals)
   //       D     Date
   //       DN    Decimal Number
   //       I     Integer?       (can't have decimals)
   //       R     Repeat
   //       S     Old Signed Number
   //       T     Time
   //       V     View
   //       X     Text
   enum Type eType_;

   int length_;
   int decimals_;
   PBF_MCF maskChooser_;
   bool bAllowNull_;
   BFDataFieldJustification eJustification_;
   PBF_SSCFC pSubstSetChooser_;
   int minLength_;
   PBF_DVF pDefValueFunc_;
   PBF_DIVF pDefValueIFunc_;
   PBF_DDVF pDefValueDFunc_;
   PBF_FLF pLabelFunc_;

   static BFDataFieldPropertiesMap& getMap();
};

extern BFDATA_LINKAGE const BFDataFieldProperties s_VarText_FldProp;

