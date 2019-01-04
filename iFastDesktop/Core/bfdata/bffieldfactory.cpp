#include "stdafx.h"

#include "bffieldfactory.hpp"
#include "bfabstractfieldcreator.hpp"
#include "bfdatafield.hpp"


BFFieldFactory& BFFieldFactory::getInstance()
{
   static BFFieldFactory myFactory;
   return(myFactory);
}

BFDataField* BFFieldFactory::create( const BFFieldId& id )
{
   BFDataField* pDataField = NULL;
   std::map< BFFieldId, const BFAbstractFieldCreator* >::const_iterator it = mapCreators_.find( id );
   if( it != mapCreators_.end() )
   {
      const BFAbstractFieldCreator* pCreator = NULL;
      pCreator = (*it).second;
      pDataField = pCreator->create();
   }
   else
   {
      // field isn't in the creators map.  If the field is dynamic then just create then damned thing
      if( id.isDynamic() )
      {
         pDataField = new BFVarTextField( static_cast< const BFVarTextFieldId& >( id ) );
      }
   }

   assert( NULL != pDataField );
   return( pDataField );
}

void BFFieldFactory::registerCreator( const BFAbstractFieldCreator* pCreator )
{
   assert( NULL != pCreator );
   std::map< BFFieldId, const BFAbstractFieldCreator* >::iterator it = mapCreators_.find( pCreator->getId() );
   // can't register a creator twice!
   assert( it == mapCreators_.end() );
   mapCreators_[ pCreator->getId() ] = pCreator;
}


