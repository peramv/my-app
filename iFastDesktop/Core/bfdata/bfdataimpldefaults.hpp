#pragma once

#include <commonport.h>
#include <clientlocale.hpp>

#include <bfdata\bfdataimpl.hpp>


// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDataImpl;

class BFDATA_LINKAGE BFDataImplDefaults
{
public:
   virtual unsigned long getDefaultMarket() const = 0;
   virtual unsigned long getDefaultClient() const = 0;
   virtual const DString& getDefaultLocale() const = 0;     // in enUS form
};

