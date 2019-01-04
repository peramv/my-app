#pragma once

#include <commonport.h>
#include <bfdata\bfdataid.hpp>
#include <bfdata\bffieldid.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDataImpl;

/**
 * Abstract base class used to determine if a specific field is in 
 * the predefined set of fields for a specific data set.
 * 
 * @author Chris Purdye
 * @see "The Complete Timbuk3 Users Reference"
 */
class BFDATA_LINKAGE BFDataFieldExists
{
public:
   /**
    * Determine if the specified BFFieldId exists in the predefined set of 
    * fields for the specified BFDataId.
    * 
    * @param idData  The predefined field set.
    * @param idField The field
    * 
    * @return true if idField is in the predefined fieldset for idData.
    */
   virtual bool exists( const BFDataId& idData, const BFFieldId& idField ) const = 0;
};

