#pragma once

#include <map>
#include <dstring.hpp>

class GenericInterfaceContainer;
class GenericInterface;
class Command;
class AbstractProcessCreator;


// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

class BPBASE_LINKAGE BFProcessFactory
{
public:
   static BFProcessFactory& getInstance();

   GenericInterface* create( GenericInterfaceContainer* pGIC, 
                             GenericInterface* pGIParent,
                             const Command& rCommand );

   void registerCreator( const AbstractProcessCreator* );

private:
   BFProcessFactory() {}
   BFProcessFactory( const BFProcessFactory& rhs );

   std::map< DString, const AbstractProcessCreator* > mapCreators_;
};
