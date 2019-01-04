/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "CacheEnabledElementHandler.hpp"

using namespace xp;

//******************************************************************************
CacheEnabledElementHandler::CacheEnabledElementHandler( ElementHandler *parentHandler, 
                                                        const DString &elementName,
                                                        ClassAttribute::ElementClass elementClass ) :
ElementHandler( parentHandler, elementName, elementClass ),
_cache(),
_nextCachingHandler( parentHandler->_cachingHandler )
{
   _cachingHandler = this;
}

//******************************************************************************
CacheEnabledElementHandler::CacheEnabledElementHandler( const DString &elementName ) :
ElementHandler( elementName ),
_cache(),
_nextCachingHandler( NULL )
{
   _cachingHandler = this;
}

//******************************************************************************
void CacheEnabledElementHandler::setToCache( const DString &name, const DString &text )
{
   _cache.erase( name );
   _cache.insert( CacheItem(name, text) );
}

//******************************************************************************
const DString &CacheEnabledElementHandler::getFromCache( const DString &name ) const
{

   static const DString returnOnNotFound = NULL_STRING;

   Cache::const_iterator iterator = _cache.find( name );
   if( iterator == _cache.end() )
   {
      if( NULL == _nextCachingHandler )
      {
         return(returnOnNotFound);
      }
      // look for a higher level cache.
      return(_nextCachingHandler->getFromCache( name ));
   }

   return(*iterator).second;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/CacheEnabledElementHandler.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:43:08   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   Aug 14 2002 12:17:04   SMITHDAV
// Fix class attribute defaulting logic.
// 
//    Rev 1.1   14 May 2002 16:42:52   SMITHDAV
// put xparser code namespace xp.
// 
//    Rev 1.0   02 Apr 2002 13:50:00   SMITHDAV
// Initial revision.
 * 
 */