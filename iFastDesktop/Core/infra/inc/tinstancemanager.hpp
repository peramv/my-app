#ifndef TINSTANCEMANAGER_HPP
#define TINSTANCEMANAGER_HPP

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

/**  This template class will manage instances of ObjectType
 *   in a map by associating them with keys of type KeyType.
 *
 *   The only requirement is that ObjectType can be constructed
 *   with a single parameter of KeyType.
 */

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif
#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

template<class KeyType, class ObjectType>
class TInstanceManager
{
   public:
      /**
       * Default constructor
       * 
       * @param KeyType
       * @param ObjectType
       */
      TInstanceManager();

      /**
       * Destructor
       * 
       * @param KeyType
       * @param ObjectType
       */
      virtual ~TInstanceManager();

      /**
       * getInstance() will search for the given key.
       * If found, the associated instance will be
       * returned.  If not found, a new ObjectType
       * will be dynamically created with the
       * key as a parameter and then inserted into
       * a map, associating it with the key.
       *
       * NOTE:
       * Class ObjectType must have a constructor that accepts an 
       * object of class KeyType as a parameter.
       * 
       * @param key
       * @return 
       */
      ObjectType * getInstance( const KeyType & key );

      /**
       * getInstance() will search for the given key.
       * If found, the associated instance will be
       * returned; otherwise, a NULL is returned.
       * 
       * @param key
       * @return 
       */
      ObjectType * findInstance( const KeyType & key );

      /**
       * addInstance() will search for the given key.
       * If NOT found, the associated instance will
       * be added; otherwise, false is returned.
       * 
       * @param key
       * @param pInstance
       * @return 
       */
      bool addInstance( const KeyType & key,
                        ObjectType * pInstance );

      /**
       * removeInstance() will search for the given key.
       * If found, the associated instance will be
       * erased from its map.  The associated
       * instance pointer is returned to the 
       * application so its memory can be deleted.
       * 
       * @param key
       * @return 
       */
      ObjectType * removeInstance ( const KeyType & key );

      /**
       * Returns the size of the object instance.
       * 
       * @return 
       */
      size_t size();

   private:
      typedef std::map< KeyType, ObjectType *,
                        std::less<KeyType> > instance_map;
      typedef typename instance_map::value_type instance_type;
      typedef typename instance_map::iterator instance_iterator;

      instance_map _instances;
};


template<class KeyType, class ObjectType>
TInstanceManager<KeyType, ObjectType>::TInstanceManager()
{
}

template<class KeyType, class ObjectType>
TInstanceManager<KeyType, ObjectType>::~TInstanceManager()
{
   // Destuctor, iterate through all instances and delete them
   instance_iterator instance_ptr = _instances.begin();

   for ( ; instance_ptr != _instances.end(); ++instance_ptr )
   {
      delete ( *instance_ptr ).second;
   }
}

template<class KeyType, class ObjectType>
ObjectType *TInstanceManager<KeyType, ObjectType>::
getInstance( const KeyType &key )
{
   ObjectType *instance;

   // Look for 'key' in the map
   instance_iterator instance_ptr = _instances.find( key );

   if ( instance_ptr == _instances.end() )
   {
      // Not found, create a new ObjectType passing 'key as a parameter
      instance = new ObjectType( key );

      if ( ! instance )
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "TInstanceManager::getInstance()" ),
                        BASE_ALLOC_FAIL );
      }

      // Insert the new instance into the map.
      _instances.insert( instance_type( key, instance ) );
   }
   else
   {
      instance = ( *instance_ptr ).second;
   }

   return instance;
}

template<class KeyType, class ObjectType>
ObjectType *TInstanceManager<KeyType, ObjectType>::
findInstance( const KeyType &key )
{
   ObjectType *instance = NULL;

   // Look for 'key' in the map
   instance_iterator instance_ptr = _instances.find( key );

   if ( instance_ptr != _instances.end() )
   {
      instance = ( *instance_ptr ).second;
   }

   return instance;
}

template<class KeyType, class ObjectType>
bool TInstanceManager<KeyType, ObjectType>::
addInstance( const KeyType &key, ObjectType *pInstance )
{
   bool added = false;

   // Look for 'key' in the map
   instance_iterator instance_ptr = _instances.find( key );

   if ( instance_ptr == _instances.end() )
   {
      _instances.insert( instance_type( key, pInstance ) );
      added = true;
   }

   return added;
}

template<class KeyType, class ObjectType>
ObjectType * TInstanceManager<KeyType, ObjectType>::
removeInstance( const KeyType &key )
{
   ObjectType *instance = NULL;

   // Look for 'key' in the map
   instance_iterator instance_ptr = _instances.find( key );

   if ( instance_ptr != _instances.end() )
   {
      instance = ( *instance_ptr ).second;
      _instances.erase( instance_ptr );
   }

   return instance;
}

template<class KeyType, class ObjectType>
size_t TInstanceManager<KeyType, ObjectType>::
size()
{
   return _instances.size();
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
// $Log:   Y:/VCS/iFastAWD/inc/tinstancemanager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:08   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2000 14:51:00   dt14177
// cleanup
// 
//    Rev 1.6   26 Feb 1999 15:06:26   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.5   24 Feb 1999 10:45:30   DT14177
// sync up with tracer
// 
//    Rev 1.4   18 Feb 1999 10:40:16   DT14177
// UNICODE
// 
//    Rev 1.3   Jan 28 1999 14:07:08   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:43:36   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 22 1998 09:46:28   DMUM
// Removed Tracing
//
//    Rev 1.0   29 Jul 1998 20:38:14   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.6   Jul 13 1998 16:59:54   dmum
// Fixed Bug with addInstance
//
//    Rev 1.5   Jul 13 1998 12:20:42   dmum
// Added findInstance() and addInstance()
//
//    Rev 1.4   Jul 11 1998 16:12:54   dmum
// Renamed deleteInstance to removeInstance
//
//    Rev 1.3   Nov 10 1997 13:01:20   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.2   24 Jul 1997 10:03:04   dmum
// Added tracing
//
//    Rev 1.1   13 Jun 1997 12:25:10   dmum
// Added condition
//
//    Rev 1.0   30 May 1997 15:57:58   dmum
//
//
//
#endif // TINSTANCEMANAGER_HPP
