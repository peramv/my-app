#pragma once

#include <commonport.h>
#include <clientlocale.hpp>

#include <bfdata\bfdataid.hpp>


// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDataImpl;

// abstract factory to create BFDataImpl objects

class BFDATA_LINKAGE BFDataImplFactory
{
public:
   virtual BFDataImpl* createImplementer( const BFDataId& id ) const = 0;
};
