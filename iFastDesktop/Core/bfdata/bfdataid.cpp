#include "stdafx.h"
#include "bfdataid.hpp"

namespace ifds
{
   extern BFDATA_LINKAGE const BFDataId NullDataId( 0, I_( "NullDataId" ) );
}

BFDataId::BFDataId( long idData,
                    const I_CHAR * name )
: id_( idData )
{
   // insert ourself into the Name/FieldID lookup map
   std::map< DString, const BFDataId* >& nameXRefMap = getDataNameIdXRefMap(); 
   DString fld = name;
   nameXRefMap.insert( std::map< DString, const BFDataId* >::value_type( fld, this ) );

   std::map< long, DString >& idXRefMap = getDataIdNameXRefMap();
   idXRefMap.insert( std::map< long, DString >::value_type( id_, fld ) );
}

std::map< DString, const BFDataId* >& BFDataId::getDataNameIdXRefMap()
{
   static std::map< DString, const BFDataId* > xRefMap;
   return( xRefMap );
}

std::map< long, DString >& BFDataId::getDataIdNameXRefMap()
{
   static std::map< long, DString > xRefMap;
   return( xRefMap );
}

const DString& BFDataId::getName() const
{
   return( getName( getId() ) );
}

const DString& BFDataId::getName( long id )
{
   std::map< long, DString >::iterator iter = getDataIdNameXRefMap().find( id );
   if( iter == getDataIdNameXRefMap().end() )
   {
      BF_THROW( BFDataIdUnknownException );
   }
   return( (*iter).second );
}

const BFDataId& BFDataId::getId( const DString& name )
{
   std::map< DString, const BFDataId* >::iterator iter = getDataNameIdXRefMap().find( name );
   if( iter == getDataNameIdXRefMap().end() )
   {
      BF_THROW( BFDataIdUnknownException );
   }
   return( *((*iter).second) );
}

const BFDataId operator+( const BFDataId& lhs, const BFDataId& rhs )
{
   BF_THROW( BFDataIdOpException );
}

const BFDataId operator+( long lhs, const BFDataId& rhs )
{
   BF_THROW( BFDataIdOpException );
}

const BFDataId operator+( const BFDataId& lhs, long rhs )
{
   BF_THROW( BFDataIdOpException );
}



