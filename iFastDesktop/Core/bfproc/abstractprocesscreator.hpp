#pragma once

#include <dstring.hpp>
class GenericInterface;

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

class BPBASE_LINKAGE AbstractProcessCreator
{
public:
   AbstractProcessCreator( const DString& name )
   : name_( name )
   {}
   virtual ~AbstractProcessCreator() {}

   const DString& getName() const { return(name_);}

   virtual GenericInterface* create( GenericInterfaceContainer* pGIC, 
                                     GenericInterface* pGIParent,
                                     const Command& rCommand ) const = 0;

private:
   AbstractProcessCreator( const AbstractProcessCreator& rhs );
   DString     name_;         // string to identify this creator object
};



