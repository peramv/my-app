#pragma once

class BFDataField;
#include <bfdata\bffieldid.hpp>
#include <bfdata\bfdatafieldproperties.hpp>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDATA_LINKAGE BFAbstractFieldCreator
{
public:
   BFAbstractFieldCreator( const BFFieldId& id, const BFDataFieldProperties& props )
   : id_( id )
   , props_( props )
   {}
   virtual ~BFAbstractFieldCreator() {}

   inline const BFFieldId& getId() const { return(id_);}
   inline const BFDataFieldProperties& getProps() const { return(props_);}
   virtual BFDataField* create() const = 0;

private:
   BFAbstractFieldCreator( const BFAbstractFieldCreator& rhs );
   BFFieldId   id_;         // BFFieldId to identify this creator object
   const BFDataFieldProperties& props_;
};




