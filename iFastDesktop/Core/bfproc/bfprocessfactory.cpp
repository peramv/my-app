#include <srcprag.h>
#include <commonport.h>
#include <assert.h>

#include "bfprocessfactory.hpp"
#include "abstractprocesscreator.hpp"
#include "command.hpp"
#include "genericinterface.hpp"
#include "genericinterfacecontainer.hpp"

BFProcessFactory& BFProcessFactory::getInstance()
{
   static BFProcessFactory myFactory;
   return(myFactory);
}

GenericInterface* BFProcessFactory::create( GenericInterfaceContainer* pGIC, 
                                            GenericInterface* pGIParent,
                                            const Command& rCommand )
{
   GenericInterface* pGI = NULL;
   std::map< DString, const AbstractProcessCreator* >::const_iterator it = mapCreators_.find( rCommand.getName() );
   if( it != mapCreators_.end() )
   {
      const AbstractProcessCreator* pCreator = NULL;
      pCreator = (*it).second;
      pGI = pCreator->create( pGIC, pGIParent, rCommand );
   }
   assert( NULL != pGI );
   return( pGI );
}

void BFProcessFactory::registerCreator( const AbstractProcessCreator* pCreator )
{
   assert( NULL != pCreator );
   std::map< DString, const AbstractProcessCreator* >::iterator it = mapCreators_.find( pCreator->getName() );
   // can't register a creator twice!
   assert( it == mapCreators_.end() );
   mapCreators_[ pCreator->getName() ] = pCreator;
}
