#pragma once

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

#include <win32\commonport1.h>
#include <bfdata\bfdataexception.hpp>
#include <bigdecimal.hpp>

BF_DECL_BASE_CE_EXCEPTION( BFMaskException );
BF_DECL_CE_EXCEPTION( InvalidCharacterException, BFMaskException );
BF_DECL_CE_EXCEPTION( DigitOverflowException, BFMaskException );
BF_DECL_CE_EXCEPTION( UnsupportedLocaleException, BFMaskException );
BF_DECL_CE_EXCEPTION( InvalidMaskException, BFMaskException );

class BFDATA_LINKAGE BFMask
{
public:
   BFMask( const DString& mask );

   const DString& getMask() const { return(mask_);}

   DString format( DIINT64 value, const ClientLocale& rLocale ) const;
   DString format( double value, const ClientLocale& rLocale ) const;
   DString format( const BigDecimal &value, const ClientLocale& rLocale ) const;
   DString format( const DString &value, const ClientLocale& rLocale ) const;
   void parse( double& parsed, const DString &value, const ClientLocale& rLocale ) const;
   void parse( DIINT64& parsed, const DString &value, const ClientLocale& rLocale ) const;
   void parse( BigDecimal& parsed, const DString &value, const ClientLocale& rLocale ) const;
   DString parse( const DString &value, const ClientLocale& rLocale ) const;

private:
   void parseMask( const DString &mask );

   DString mask_;

   I_CHAR prefix_[64];
   I_STRING::size_type prefixSize_;

   I_CHAR integerMask_[64];
   I_STRING::size_type integerMaskSize_;
   I_STRING::size_type integerMaskDigits_;

   I_CHAR decimalMask_[64];
   I_STRING::size_type decimalMaskSize_;
   bool hasDecimal_;

   I_CHAR suffix_[64];
   I_STRING::size_type suffixSize_;

   unsigned int flags_;
};

// pointer to a Mask Chooser Function
typedef const BFMask& ( *PBF_MCF )( const ClientLocale& );

