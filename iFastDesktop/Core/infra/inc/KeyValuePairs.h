#ifndef KEYVALUEPAIRS_H
#define KEYVALUEPAIRS_H

#include "Messaging.h"

#include <map>
#include <exception>

namespace MessagingFramework
{

class DIMESSAGE_LINKAGE InvalidKeyException : public exception
{
   public:
      InvalidKeyException( const std::string& strKey );

   private:
      std::string m_strKey;
};

}


namespace MessagingFramework
{

/**
 * The KeyValuePairs class provides functionality to store and manipulate
 * a collection of key/value pairs.
 *
 * @author: Paul Dardeau
 *
 * Sample Usage:
 * <pre>
 * KeyValuePairs kvpMovieDetails;
 *
 * kvpSample.addPair( "movie_name", "Thunderball" );
 * kvpSample.addPair( "movie_series", "James Bond - 007" );
 * kvpSample.addPair( "main_actor", "Sean Connery" );
 *
 * // does it have a "main_actor" key?
 * if( kvpSample.hasKey( "main_actor" ) )
 * {
 *    const string& strMainActor = kvpSample.getValue( "main_actor" );
 * }
 *
 * // iterate through all the key/value pairs
 * STRING_LIST lstKeys;
 * kvpSample.getKeys( lstKeys );
 *
 * STRING_LIST::const_iterator it = lstKeys.beging();
 * const STRING_LIST::const_iterator itEnd = lstKeys.end();
 *
 * for( ; it != itEnd; ++it )
 * {
 *    const string& strKey = (*it);
 *    const string& strValue = kvpSample.getValue( strKey );
 *
 *    printf( "key='%s', value='%s'\n", strKey.c_str(), strValue.c_str() );
 * }
 * </pre>
 * 
 */
class DIMESSAGE_LINKAGE KeyValuePairs
{
   public:
      /**
       * Default constructor
       */
      KeyValuePairs();


      /**
       * Copy constructor
       */
      KeyValuePairs( const KeyValuePairs& copy );


      /**
       * Destructor
       */
      ~KeyValuePairs();


      /**
       * Assignment operator
       */
      KeyValuePairs& operator=( const KeyValuePairs& copy );


      /**
       * Retrieves a list of the keys in the collection.
       *
       * @param vecKeys - a STRING_LIST object passed by reference that will
       * be populated with keys.
       */
      void getKeys( STRING_LIST& vecKeys ) const;


      /**
       * Determines whether the specified key exists within the collection.
       *
       * @param strKey - the key to test
       *
       * @return boolean indicating whether the specified key is in the collection.
       */
      bool hasKey( const std::string& strKey ) const;


      /**
       * Retrieves the value associated with the specified key.
       *
       * @param strKey - the key whose value is to be retrieved
       *
       * @return the value associated with the specified key
       */
      const std::string& getValue( const std::string& strKey ) const;


      /**
       * Adds a new key/value pair to the collection.  If the key is already
       * contained in the collection, it's value will be updated with the
       * value specified in the argument list.
       *
       * @param strKey - the new key to add
       * @param strValue - the value associated with the key
       */
      void addPair( const std::string& strKey, const std::string& strValue );


      /**
       * Removes a pair from the collection.
       *
       * @param strKey - the key whose pair will be removed from the collection.
       */
      void removePair( const std::string& strKey );


      /**
       * Removes <b>ALL</b> key/value pairs.
       */
      void clear();


   private:
      typedef std::map< std::string, std::string > MAP_STRING_TO_STRING;
      MAP_STRING_TO_STRING m_mapKeyValues;
};

}

#endif


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


