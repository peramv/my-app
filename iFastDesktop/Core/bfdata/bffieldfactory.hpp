#pragma once

#pragma warning( disable: 4786 )

#include <map>
#include <bfdata\bffieldid.hpp>

class BFDataField;
class BFAbstractFieldCreator;


// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFFieldFactory
{
public:
   static BFFieldFactory& getInstance();

   BFDataField* create( const BFFieldId& id );
   void registerCreator( const BFAbstractFieldCreator* );

private:
   BFFieldFactory() {}
   BFFieldFactory( const BFFieldFactory& rhs );

   std::map< BFFieldId, const BFAbstractFieldCreator* > mapCreators_;
};

