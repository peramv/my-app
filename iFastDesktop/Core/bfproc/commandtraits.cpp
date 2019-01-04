#include "bpglobal.h"
#include "commandtraits.hpp"

CommandTraitsMap& CommandTraitsMap::getInstance() 
{
   static CommandTraitsMap myInstance;
   return( myInstance );
}

void CommandTraitsMap::add( const CommandTraits* pTraits )
{
   const_iterator it = find( pTraits->getName() );
   if( it == end() )
   {
      (*this)[ pTraits->getName() ] = pTraits;
   }
}

const CommandTraits* CommandTraitsMap::get( const DString& name )
{
   const CommandTraits* pTraits = NULL;
   const_iterator it = find( name );
   if( it != end() )
   {
      pTraits = (*it).second;
   }
   return( pTraits );
}

