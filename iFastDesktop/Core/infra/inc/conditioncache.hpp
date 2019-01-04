#ifndef CONDITIONCACHE_HPP
#define CONDITIONCACHE_HPP

/**
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

#pragma message( "including "__FILE__ )

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


class DICORE_LINKAGE ConditionCacheKey
{
   friend class CacheKeyLess;

public:
   ConditionCacheKey( const DString & component,
                      long code,
                      const ClientLocale & clientLocale ) :
   m_component( component ),
   m_code( code ),
   m_clientLocale( clientLocale )
   {
   }

   virtual ~ConditionCacheKey( )
   {
   }

private:
   DString       m_component;
   long          m_code;
   ClientLocale  m_clientLocale;
};

class DICORE_LINKAGE ConditionCacheData
{
public:
   ConditionCacheData( ) : m_severity( NO_CONDITION )
   {
   }

   virtual ~ConditionCacheData( )
   {
   }

//   ConditionCacheData & operator=( const ConditionCacheData & copy )
//   {
//      if ( this == &copy )
//      {
//         return *this;
//      }
//
//      m_severity = copy.m_severity;
//      m_name = copy.m_name;
//      m_message = copy.m_message;
//      m_correction = copy.m_correction;
//
//      return *this;
//   }
//
   SEVERITY getSeverity( ) const
   {
      return m_severity;
   }

   void setSeverity( SEVERITY severity )
   {
      m_severity = severity;
   }

   const DString & getName( ) const
   {
      return m_name;
   }

   void setName( const DString & name )
   {
      m_name = name;
   }

   const DString & getMessage( ) const
   {
      return m_message;
   }

   void setMessage( const DString & message )
   {
      m_message = message;
   }

   const DString & getCorrection( ) const
   {
      return m_correction;
   }

   void setCorrection( const DString & correction )
   {
      m_correction = correction;
   }

private:
   SEVERITY             m_severity;       // Severity of Condition
   DString              m_name;           // Name of this Condition
   DString              m_message;        // User message
   DString              m_correction;     // Correctional instructions
};

class DICORE_LINKAGE CacheKeyLess
{
public:
   bool operator()( ConditionCacheKey x, ConditionCacheKey y ) const;
};

class DICORE_LINKAGE ConditionCache
{
   class DICORE_LINKAGE ConditionCacheNode
   {
   public:
      ConditionCacheNode( ) :
      m_prev( NULL ),
      m_next( NULL ),
      m_key( NULL ),
      m_data( NULL )
      {
      }

      virtual ~ConditionCacheNode( )
      {
         delete m_key;
         delete m_data;
      }

   public:
      ConditionCacheNode *  m_prev;           // Pointer to previous node in chain.
      ConditionCacheNode *  m_next;           // Pointer to next node in chain.

      ConditionCacheKey  *  m_key;            // Cache key.
      ConditionCacheData *  m_data;           // Cache data.
   };

public:
   /**
    * Gets a pointer to an instance of the ConditionCache.
    * This function must be called before the
    * ConditionCache can be used in any way.
    *
    * @return pointer to ConditionCache.
    */
   static ConditionCache * getInstance();

   typedef std::map< ConditionCacheKey, ConditionCacheNode * , CacheKeyLess >
   ConditionCacheMap;

   /**
    * Get the specified condition data from the cache.
    *
    * @param key - key to cache.
    * @return condition cache data if found, else NULL.
    */
   const ConditionCacheData * get( const ConditionCacheKey & key );

   /**
    * Put the specified condition data into the cache under the specified key.
    * If the key is already in the cache, the data will replace the data in the
    * cache.
    *
    * @param key - key to cache.
    * @param data - data to store.
    */
   void put( const ConditionCacheKey & key, const ConditionCacheData & data );

   long capacity( );

private:
   /**
    * Create a ConditionCache of a specified size.
    *
    * @param capacity - size of cache.
    */
   ConditionCache( long capacity );

   virtual ~ConditionCache( );

   static void deregister( void * pObj );
   static void killInstance( void );

   /**
    * Insert a node after the head of the linked list.
    *
    * @param node - node to insert.
    */
   void insertNode( ConditionCacheNode * node );

   /**
    * Remove a node from the linked list.
    *
    * @param node - node to remove.
    */
   void removeNode( ConditionCacheNode * node );

   /**
    * Remove (and delete ) a node from the cache.
    *
    * @param node - node to remove.
    */
   void remove( ConditionCacheNode * node );

   /**
    * Remove (and delete ) a node from the cache.
    *
    * @param key - key of node to remove.
    */
   void remove( const ConditionCacheKey & key );

   /**
    * Remove (and delete ) all nodes from the cache.
    */
   void clear( );

   /**
    * Maximum number of nodes in the cache.
    */
   long m_capacity;

   /**
    * Map of the nodes.
    */
   ConditionCacheMap     m_map;

   /**
    * Head of a doubly linked list of the nodes.
    */
   ConditionCacheNode *  m_head;

   /**
    * Pointer to the singleton instance of ConditionCache.
    */
   static ConditionCache * s_instance;

   /**
    * Used to delete the ConditionCache singleton.
    */
   SingletonRegister m_register;
};

#endif 

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
