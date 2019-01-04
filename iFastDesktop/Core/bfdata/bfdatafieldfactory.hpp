#pragma once

#include <commonport.h>
#include <clientlocale.hpp>

#include <bfdata\bffieldid.hpp>


// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDataField;

// abstract factory to create BFDataImpl objects

class BFDATA_LINKAGE BFDataFieldFactory
{
public:
   virtual BFDataField* createField( const BFFieldId id ) const = 0;
};

