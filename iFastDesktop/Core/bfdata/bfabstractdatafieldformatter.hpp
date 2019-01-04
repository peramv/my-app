#pragma once

#include <srcprag.h>
#include <commonport.h>

#include <dstring.hpp>
#include <clientlocale.hpp>
#include <bfdata\bfdatafieldproperties.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDATA_LINKAGE BFAbstractDataFieldFormatter
{
public:
   virtual bool format( DString& strTarget, const I_CHAR* pszSource, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool format( DString& strTarget, DIINT64 source, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool format( DString& strTarget, double source, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool format( DString& strTarget, const BigDecimal& source, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool unformat( I_CHAR* pszTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool unformat( double& dblTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool unformat( DIINT64& i64Target, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
   virtual bool unformat( BigDecimal& bigdTarget, const I_CHAR* pszSource, size_t cChars, const BFDataFieldProperties* props, const ClientLocale& locale ) = 0;
};


