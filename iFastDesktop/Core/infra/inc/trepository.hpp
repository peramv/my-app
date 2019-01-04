#ifndef TREPOSITORY_HPP
#define TREPOSITORY_HPP

#  pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

/** The TRepository is a templatized class that provides an object
 * "brokerage" or repository service.  The user of this class must
 * pass in the type of the key and the type of the object being stored.
 *
 */

/* ISSUES :
 * 
 * What happens if the key of an object is changed?  Should this class
 * have a method 'bool changeKey( oldKey, newKey )'?
 */

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef DIPORT_H
   #include "diport.h"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif


template<class KeyType, class ObjectType>
class TRepository
{
   public:
      /**
       * Default constructor
       * 
       * @param KeyType
       * @param ObjectType
       */
      TRepository();

      /**
       * Destructor
       * 
       * @param KeyType
       * @param ObjectType
       */
      virtual ~TRepository();

      /**
       * Adds an object to the repository
       * 
       * @param key
       * @param pObject
       * @return 
       */
      bool addInstance( const KeyType& key, ObjectType * pObject );

      /**
       * Gets an instance of the object from the
       * repository corresponding to the key
       * 
       * @param key
       * @return 
       */
      ObjectType& getInstance( const KeyType& key );

      /**
       * Gets an instance of the object from the
       * repository corresponding to the key
       * 
       * @param key
       * @param object - (out)
       * @return 
       */
      bool getInstance( const KeyType & key, 
                        ObjectType & object );

      /**
       * Gets an instance of the object from the
       * repository corresponding to the key
       * 
       * @param key
       * @return 
       */
      ObjectType * getInstancePointer( const KeyType & key );

      /**
       * decrements the use counter for the object
       * and deletes it if so indicated
       * 
       * @param key
       * @param fKeepUnused
       *                   - indicates whether to deletes the object
       *                   if its use count reaches 0
       * @return 
       */
      bool deregister( const KeyType & key, 
                       bool fKeepUnused=false );

      /**
       * Indicates whether a key exists in the
       * repository
       * 
       * @param key
       * @return 
       */
      bool keyExists( const KeyType & key ) const;

      /**
       * Clears the list and adds keys from the
       * repository to the list, including
       * unused keys
       * 
       * @param keyList
       * @return 
       */
      bool getInstanceList( std::vector< KeyType > & keyList ) 
                                                           const;

      /**
       * Clears the map and adds keys and use counts
       * from the repository to the map, including
       * entries with unused keys
       * 
       * @param keyList
       * @return 
       */
      bool getInstanceList( std::map< KeyType,
                                      int,
                                std::less<KeyType > > & keyList )
                                                           const;

      /**
       * Deletes all entries with keycounts == 0
       * 
       * @return 
       */
      bool deleteAllUnused( void );

      /**
       * Deletes all objects in the repository and
       * clears the repository
       * 
       * @return 
       */
      bool deleteAll( void );

      /**
       * Tells whether the repository is empty.
       * 
       * @return 
       */
      bool isEmpty( void ) const;

      typedef struct
      {
         ObjectType     *pObj;
         unsigned long   ulCount;
      } OBJECT_INFO;


   private:
      TRepository( const TRepository<KeyType, ObjectType>& copy );

      TRepository<KeyType, ObjectType>&
      operator=( const TRepository<KeyType, ObjectType>& copy );

      typedef std::map< KeyType, OBJECT_INFO, std::less<KeyType> >
      OBJECT_MAP;

      typedef typename OBJECT_MAP::value_type OBJECT_MAP_TYPE;

      OBJECT_MAP m_objectMap;
      mutable MutexSemaphore m_mutex;
};




template<class KeyType, class ObjectType>
TRepository<KeyType,ObjectType>::TRepository()
{
}



template<class KeyType, class ObjectType>
TRepository<KeyType,ObjectType>::~TRepository()
{
   deleteAllUnused();
}



template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::
addInstance( const KeyType& key, ObjectType * pObject )
{
   CriticalSection crit( m_mutex );

   if ( keyExists( key ) )
      return false;

   std::pair< OBJECT_MAP::iterator, bool > objectPair;

   OBJECT_INFO object_info;

   object_info.pObj = pObject;
   object_info.ulCount = 1;

   // Attempt to insert into object map
   objectPair = m_objectMap.insert( OBJECT_MAP_TYPE( key, object_info ) );

   bool fSuccess;

   // Did insert into object map succeed?
   if ( objectPair.second == true )
   {
      fSuccess = true;
   }
   else
   {
      // insert into object map failed
      fSuccess = false;
   }

   return fSuccess;
}

template<class KeyType, class ObjectType>
ObjectType& TRepository<KeyType,ObjectType>::getInstance( const KeyType& key )
{
   CriticalSection crit( m_mutex );
   bool fSuccess;

   OBJECT_MAP::iterator p = m_objectMap.find( key );

   if ( p != m_objectMap.end() )
   {
      fSuccess = true;

      ((*p).second.ulCount)++;
   }
   else
      fSuccess = false;

   return *( (*p).second.pObj );
}

template<class KeyType, class ObjectType>
ObjectType * TRepository<KeyType,ObjectType>::
getInstancePointer( const KeyType& key )
{
   CriticalSection crit( m_mutex );

   OBJECT_MAP::iterator p = m_objectMap.find( key );

   if ( p != m_objectMap.end() )
   {

         ((*p).second.ulCount)++;
      }

   return (*p).second.pObj;
}


template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::
getInstance( const KeyType& key, ObjectType& object )
{
   CriticalSection crit( m_mutex );
   bool fSuccess = false;

   OBJECT_MAP::iterator p = m_objectMap.find( key );

   if ( p != m_objectMap.end() )
   {
      fSuccess = true;
      object = *( (*p).second.pObj );

         ((*p).second.ulCount)++;
      }

   return fSuccess;
}

template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::
deregister( const KeyType& key, bool fKeepUnused )
{
   CriticalSection crit( m_mutex );
   bool fSuccess = false;

   OBJECT_MAP::iterator p = m_objectMap.find( key );

   if ( p != m_objectMap.end() )
   {
      fSuccess = true;

         // Decrement use count
         ((*p).second.ulCount)--;


         // Did use count drop to zero?
      if ( (*p).second.ulCount == 0 )
      {
         if ( ! fKeepUnused )
         {
            // Delete object
            delete (*p).second.pObj;

            // Delete key from object map
            m_objectMap.erase( p );
         }
      }
   }

   return fSuccess;
}

template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::keyExists( const KeyType& key ) const
{
   CriticalSection crit( m_mutex );
   OBJECT_MAP::const_iterator p = m_objectMap.find( key );

   bool exists = ( p != m_objectMap.end() );

   return exists;
}

template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::
getInstanceList( std::vector<KeyType>& keyList ) const
{
   CriticalSection crit( m_mutex );
   OBJECT_MAP::const_iterator p = m_objectMap.begin();
   OBJECT_MAP::const_iterator stop = m_objectMap.end();

   bool success = ( p != stop );

   if ( success )
   {
            keyList.clear();

      for( ; p != stop; ++p )
      {
         keyList.push_back( (*p).first );
      }
   }

   return success;
}

template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::deleteAllUnused( void )
{
   CriticalSection crit( m_mutex );
   bool fSuccess = true;

   OBJECT_MAP::iterator       p = m_objectMap.begin();
   OBJECT_MAP::iterator objStop = m_objectMap.end();
   OBJECT_MAP::iterator       q = p;


   while ( p != objStop )
   {
      if ( (*p).second.ulCount == 0 )
      {
         // delete object
         delete (*p).second.pObj;

         // delete key from object map
         q = p;
         q++;
         m_objectMap.erase( p );
         p = q;
      }
      else
         p++;
      }

   return fSuccess;
}



template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::deleteAll( void )
{
   CriticalSection crit( m_mutex );
   bool fSuccess = true;

   OBJECT_MAP::iterator       p = m_objectMap.begin();
   OBJECT_MAP::iterator objStop = m_objectMap.end();


   for( ; p != objStop; p++ )
   {
      // delete object
      delete (*p).second.pObj;
   }
   m_objectMap.erase( m_objectMap.begin(), m_objectMap.end() );

   return fSuccess;
}


template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::
getInstanceList( std::map<KeyType, int, std::less<KeyType> >& keyMap ) const
{
   CriticalSection crit( m_mutex );
   OBJECT_MAP::const_iterator p = m_objectMap.begin();
   OBJECT_MAP::const_iterator stop = m_objectMap.end();

   // If we have no items, just get out!
   bool success = p != stop;

   if ( success )
   {
      // Prep our map
      keyMap.clear();

   // For each item, create a map entry with the associated count
   for( ; p != stop; ++p )
   {
         keyMap[(*p).first] = (*p).second.ulCount;
      }
   }

   return success;
}

template<class KeyType, class ObjectType>
bool TRepository<KeyType,ObjectType>::isEmpty( void ) const
{
   CriticalSection crit( m_mutex );
   bool empty = m_objectMap.begin() == m_objectMap.end();
   return empty;
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
// $Log:   Y:/VCS/iFastAWD/inc/trepository.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:12   kovacsro
//Initial revision.
// 
//    Rev 1.5   28 Nov 2000 16:09:44   dt14177
// cleanup
// 
//    Rev 1.4   Jul 19 2000 15:55:06   DT14177
// removed GetConnectionId calls
// 

#endif // Macro inclusion guard
