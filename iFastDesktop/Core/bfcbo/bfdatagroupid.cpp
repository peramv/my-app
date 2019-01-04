#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/bfdatagroupid.cpp-arc  $", "$Revision:   1.8  $" )
#define NOMINMAX
#include <srcprag.h>
#include <commonport.h>
#include <windows.h>
#include <limits>
#include <assert.h>

#include "bfdatagroupid.hpp"
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfguard.hpp>

#include <map>

typedef std::map< BFDataGroupId, BFDataGroupId > BFDATAGROUPID_PARENT_MAP;
static BFDATAGROUPID_PARENT_MAP s_mapDataGroupIdParents;
static BFCritSec s_csDataGroupIdParents;


namespace BF
{
   extern BFBASE_LINKAGE const BFDataGroupId NullDataGroupId( -1, BFDataGroupId::getNoParentInstance() );
   extern BFBASE_LINKAGE const BFDataGroupId HOST( 0, BF::NullDataGroupId );
}

const BFDataGroupId& BFDataGroupId::getNoParentInstance()
{
   static BFDataGroupId noParentInstance;
   return noParentInstance;
}

#pragma warning( disable: 4355 )
BFDataGroupId::BFDataGroupId()
: id_( -2 )
//CP20030429, pParent_( this )
{}
#pragma warning( default: 4355 )

BFDataGroupId::BFDataGroupId( long l, const BFDataGroupId& rParent )
: id_( l )
{
   setParent( &rParent );
}

long BFDataGroupId::idNext_ = 0;

const BFDataGroupId& BFDataGroupId::getParent() const 
{
   // in the old days this was ...
//CP20030429   return( *pParent_ );
   // now, it's ...
   BFGuard g( s_csDataGroupIdParents );
   BFDATAGROUPID_PARENT_MAP::iterator it = s_mapDataGroupIdParents.find( *this );
   if( it != s_mapDataGroupIdParents.end() ) {
      return( (*it).second );
   }
   return( BF::NullDataGroupId );
}


long BFDataGroupId::getNextDataGroupId()
{
   static BFCritSec cs;
   BFGuard g( cs );
   return(++idNext_);
}

bool BFDataGroupId::isAncestorOf( const BFDataGroupId& idDataGroup ) const
{
   if( idDataGroup == *this )
   {
      return( true );
   }
   else if( idDataGroup == BF::NullDataGroupId )
   {
      return( false );
   }
   return( isAncestorOf( idDataGroup.getParent() ) );
}

void BFDataGroupId::setParent( const BFDataGroupId* pParent ) const
{
//CP20030429   assert( this != pParent );
//CP20030429   assert( NULL != pParent );
   BFGuard g( s_csDataGroupIdParents );
   BFDATAGROUPID_PARENT_MAP::iterator it = s_mapDataGroupIdParents.find( *this );
   if( it == s_mapDataGroupIdParents.end() ) 
   {
      s_mapDataGroupIdParents.insert( std::make_pair( (*this), *pParent ) );
   }
   else
   {
      if( NULL != pParent )
      {
         s_mapDataGroupIdParents[ *this ] = *pParent;
      }
      else
      {
         s_mapDataGroupIdParents.erase( it );
      }
   }
//CP20030429   pParent_ = pParent;
}
