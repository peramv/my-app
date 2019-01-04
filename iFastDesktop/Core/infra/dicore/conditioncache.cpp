//**********************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Systems, Inc.
//
//**********************************************************************
//
// ^FILE   : conditioncache.cpp
// ^AUTHOR : David Sample
// ^DATE   : 12/11/2001
//
// ----------------------------------------------------------
//
// ^CLASS    : ConditionCache
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//**********************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CONDITIONCACHE_HPP
   #include "conditioncache.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

namespace
{
   //
   // The s_lock is used to guard all access to s_instance.
   //
   CriticalSectionLock s_lock;
}

ConditionCache * ConditionCache::s_instance = NULL;

bool CacheKeyLess::operator()( ConditionCacheKey x, ConditionCacheKey y ) const
{
   bool less = false;

   if ( x.m_code < y.m_code )
   {
      less = true;
   }
   else if ( x.m_code == y.m_code )
   {
      if ( x.m_clientLocale < y.m_clientLocale )
      {
         less = true;
      }
      else if ( x.m_clientLocale == y.m_clientLocale )
      {
         if ( x.m_component.upperCase() < y.m_component.upperCase() )
         {
            less = true;
         }
      }
   }

   return( less );
}

ConditionCache * ConditionCache::getInstance( )
{
   if ( s_instance )
   {
      return s_instance;
   }

   Guard crit( &s_lock );

   if ( s_instance )
   {
      return s_instance;
   }

   // Get the cache size from configuration or use hardcoded default.
   ConfigManager * configManager = ConfigManager::getManager( I_("DICORE") );
   Configuration configuration = configManager->retrieveConfig( I_("Condition") );
   long cacheSize = configuration.getValueAsLong( I_("CacheSize") );

   if ( cacheSize < 100 )
   {
     cacheSize = 100;
   }

   // Create instance.
   s_instance = new ConditionCache( cacheSize );

   return s_instance;
}

void ConditionCache::deregister( void * pObj )
{
   delete s_instance;
   s_instance = NULL;
}

ConditionCache::ConditionCache( long capacity ) :
m_capacity( capacity )
{
   m_head = new ConditionCacheNode( );
   m_head->m_next = m_head;
   m_head->m_prev = m_head;

   m_register.registerSingleton( deregister, this );
}

ConditionCache::~ConditionCache()
{
   clear();
   delete m_head;
}

const ConditionCacheData * ConditionCache::get( const ConditionCacheKey & key )
{
   ConditionCacheData * data = NULL;

   ConditionCacheMap::const_iterator iter = m_map.find( key );
   if ( iter != m_map.end() )
   {
      ConditionCacheNode * node = ( *iter ).second;
      removeNode( node );
      insertNode( node );
      data = node->m_data;
   }

   return( data );
}

void ConditionCache::put( const ConditionCacheKey & key,
                          const ConditionCacheData & data )
{
   ConditionCacheNode * node = NULL;

   ConditionCacheMap::const_iterator iter = m_map.find( key );
   if ( iter != m_map.end() )
   {
      node = ( *iter ).second;
      *node->m_data = data;

      removeNode( node );
   }
   else
   {
      if ( m_map.size() >= (unsigned long)m_capacity )
      {
         ConditionCacheNode * lru = m_head->m_prev;
         if ( lru != m_head )
         {
            remove( lru );
         }
      }

      node = new ConditionCacheNode();
      node->m_key = new ConditionCacheKey( key );
      node->m_data = new ConditionCacheData( data );

      m_map.insert( ConditionCacheMap::value_type( key, node ) );
   }

   insertNode( node );
}

long ConditionCache::capacity( )
{
   return( m_capacity );
}

void ConditionCache::insertNode( ConditionCacheNode * node )
{
   ConditionCacheNode * next = m_head->m_next;

   m_head->m_next = node;
   next->m_prev = node;
   node->m_next = next;
   node->m_prev = m_head;
}

void ConditionCache::removeNode( ConditionCacheNode * node )
{
   node->m_prev->m_next = node->m_next;
   node->m_next->m_prev = node->m_prev;
}

void ConditionCache::remove( ConditionCacheNode * node )
{
   removeNode( node );
   m_map.erase( *node->m_key );
   delete node;
}

void ConditionCache::remove( const ConditionCacheKey & key )
{
   ConditionCacheMap::iterator iter = m_map.find( key );
   if ( iter != m_map.end() )
   {
      remove( ( *iter ).second );
   }
}

void ConditionCache::clear( )
{
   for ( ConditionCacheMap::iterator iter = m_map.begin();
         iter != m_map.end();
         ++iter )
   {
      delete ( *iter ).second;
   }

   m_map.clear();

   m_head->m_next = NULL;
   m_head->m_prev = NULL;
}


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//

