#pragma once

#include <dstring.hpp>
#include <clientlocale.hpp>
#include <configmanager.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bfutil
{
   class BFUTIL_LINKAGE LocaleTraits
   {
   public:
      LocaleTraits( const ClientLocale& rLocale, bool forDisp = false );
   
      I_CHAR getGroupSeparator() const { return(groupSeparator_);}
      I_CHAR getRadixSeparator() const { return(radixSeparator_);}
      I_CHAR getNegativeSign() const { return negativeSign_; }
      unsigned int getGroupDigits() const { return cGroupDigits_; }
   
      static const LocaleTraits& get( const ClientLocale& rLocale, bool forDisp = false );
   private:
      LocaleTraits( const LocaleTraits& );               // not implemented
      LocaleTraits& operator=( const LocaleTraits& );    // not implemented
   
      I_CHAR groupSeparator_;
      I_CHAR radixSeparator_;
      I_CHAR negativeSign_;
      unsigned int cGroupDigits_;
   };
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/localetraits.hpp-arc  $
//
//   Rev 1.2   Jun 30 2005 16:57:14   Fengyong
//PET1250 FN02 - European numeric enhancement
//
//   Rev 1.1   Apr 11 2003 17:54:44   PURDYECH
//First real working version in bfutil.
//
//   Rev 1.0   Apr 10 2003 11:27:00   PURDYECH
//Initial Revision
//
