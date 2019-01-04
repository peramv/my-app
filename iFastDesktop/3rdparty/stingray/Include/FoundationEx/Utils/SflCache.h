
// Source code modify by original from:
/***************************************************************************
 *   Copyright (C) 2004-2006 by Patrick Audley                             *
 *   paudley@blackcat.ca                                                   *
 *   http://blackcat.ca                                                    *
 *                                                                         *
 ***************************************************************************/
#if !defined __SFLCACHE__H__
#define __SFLCACHE__H__

// Includes
#include "StingrayExportDefs.h"
#include <map>
#include <list>
#include <vector>
#include <stdlib.h>

#pragma warning(disable: 4100)

namespace sflex
{

#define SFLEX_CACHE_DEFAULT_MAX 10

template <class T>
struct CountFunction 
{
		unsigned long operator()(const T &x) { return 1; }
};

template<class KeyType, class ValueType, class SizeFunction = CountFunction<ValueType> > 
class Cache
{
	public:
		class Entry
		{
		public:
			Entry() : _weight(0), _int(0), _text(_T(""))
			{
			}
			//std::pair<KeyType, ValueType>	_pair;
			KeyType							_key;
			ValueType						_value;
			UINT							_weight;
			int								_int;
			CString							_text;
		};

		//typedef std::pair< KeyType, ValueType> Entry;				// And entry of Key and Value.
		typedef std::list< Entry > List;							// Main Cache Storage.
		typedef typename List::iterator ListIter;					// Main Cache Iterator.
		typedef typename List::reverse_iterator RevListIter;		// Min Reverse Cache Iterator.
		typedef typename List::const_iterator ListConstIter;        // Main cache iterator (const).
		typedef std::vector< KeyType > KeyList;						// Vector of all keys.
		typedef std::vector< ValueType > ValueList;					// Vector of all values.
		typedef typename KeyList::iterator KeyListIter;				// Main cache iterator.
		typedef typename KeyList::const_iterator KeyListConstIter;	// Main cache iterator (const).
		typedef std::map< KeyType, ListIter > Map;					// Index typedef.
		//typedef std::pair< KeyType, ListIter > Pair;				// Pair of Map elements.
		typedef typename Map::iterator MapIter;			            // Index iterator.
		typedef typename Map::const_iterator MapConstIter;          // Index iterator (const).

	protected:
		List _lstCache;             // Main cache storage
		Map _mapIndex;              // Cache storage index
		unsigned long m_max_cache_size;	// Maximum abstract size of the cache
		unsigned long m_curr_cache_size;	// Current abstract size of the cache
		bool          m_bDeleteValuePtrs;


	public:
		Cache()
		{
			m_max_cache_size = SFLEX_CACHE_DEFAULT_MAX;
			m_curr_cache_size = 0;
			m_bDeleteValuePtrs = false;
		}
		// Constructor for a cache that holds m_max_cache_size items.
		Cache(unsigned long _size) :
			m_max_cache_size(_size)
		{
			m_curr_cache_size = 0; // Initialize to starting point of zero.
			m_bDeleteValuePtrs = false;
		}

		virtual ~Cache() 
		{
			// Clean up the list cache and the index map.
			Clear(); 
		}

		inline void EnableDeleteValuePtrs()
		{
			m_bDeleteValuePtrs = true;
		}

		inline const unsigned long GetCurrentSize(void) const 
		{ 
			return m_curr_cache_size; 
		}

		inline const unsigned long GetMaxSize(void) const 
		{ 
			return m_max_cache_size; 
		}

		inline void SetMaxSize(const unsigned long _size)
		{
			m_max_cache_size = _size;
		}

		inline void Clear(void) 
		{
			// MUTEX

			if(m_bDeleteValuePtrs)
			{
				for(ListIter lIter = _lstCache.begin(); lIter != _lstCache.end(); lIter++)
				{
					// Delete pointer. 
				//	delete (lIter->second);
				}
			}

			// Clear all content.
			_lstCache.clear();
			_mapIndex.clear();

			// Reset the cache size.
			m_curr_cache_size = 0;
		};

		inline bool Exists(const KeyType &key) const 
		{
			// MUTEX
			// Can we find the key?
			return _mapIndex.find(key) != _mapIndex.end();
		}

		// Removes a KeyType/ValueType pair from the cache.
		inline void Remove(const KeyType &key) const 
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return;
			}
			_ImplRemove(mapIter);
		}

		// Touches a key in the cache, thus tagging it the most recently used (head).
		inline void Touch(const KeyType &key) 
		{
			_ImplTouch( key );
		}

		// Fetches a pointer to the cache data (KeyType).
		inline ValueType* FetchValue(const KeyType &key, bool bTouch = true) 
		{
			// Can we find the key?
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return NULL;
			}
			if(bTouch) 
			{
				_ImplTouch(key);
			}
			return &(mapIter->second->_value);
		}

		inline ValueType Fetch(const KeyType &key, bool bTouch = true) 
		{
			// Can we find the key?
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return ValueType();
			}
			ValueType tmp = mapIter->second->_value;
			if(bTouch)
			{
				_ImplTouch(key);
			}
			return tmp;
		}

		inline bool Fetch(const KeyType &key, ValueType &value, bool bTouch = true)
		{
			// Can we find the key?
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			if(bTouch)
			{
				_ImplTouch(key);
			}
			//value = mapIter->second->second;
			value = mapIter->second->_value;
			return true;
		}

		inline bool SetWeight(const KeyType& key, const UINT uiWeight)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			mapIter->second->_weight = uiWeight;
			return true;
		}

		inline bool GetWeight(const KeyType& key, UINT& uiWeight)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			uiWeight = mapIter->second->_weight;
			return true;
		}

		inline bool SetInt(const KeyType& key, const int iInt)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			mapIter->second->_int = iInt;
			return true;
		}

		inline bool GetInt(const KeyType& key, int& iInt)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			iInt = mapIter->second->_int;
			return true;
		}

		inline bool SetText(const KeyType& key, const CString strText)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			mapIter->second->_text = strText;
			return true;
		}

		inline bool GetText(const KeyType& key, CString& strText)
		{
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				return false;
			}
			strText = mapIter->second->_text;
			return true;
		}

		// Inserts KeyType/ValueType pair in to the cache and removes any entries greater than
		// the m_max_cache_size. First checks the key and touches it, if it already exists. 
		inline void Insert(const KeyType &key, const ValueType &data, UINT weight = 0, int special_int = 0, CString special_text = _T("")) 
		{
			// MUTEX
			// Touch the key and move to desired position. If it exists, then replace the content.
			MapIter mapIter = _ImplTouch(key, weight);

			if(mapIter == _mapIndex.end())
			{
				// Could not find the key and touch it, so insert it as new.
				_ImplInsert(key, data, weight, special_int, special_text);
			}
		}

		inline const KeyList GetAllKeys(void) 
		{
			// MUTEX 
			// Create a new list with all the keys.
			KeyList retKeyList;
			for(ListConstIter lstIter = _lstCache.begin(); lstIter != _lstCache.end(); lstIter++)
			{
				retKeyList.push_back(lstIter->_key);
			}
			return retKeyList;
		}

		inline const ValueList GetAllValues(void)
		{
			// MUTEX
			ValueList retValueList;
			for(ListConstIter lstIter = _lstCache.begin(); lstIter != _lstCache.end(); lstIter++)
			{
				retValueList.push_back(lstIter->_value);
			}
			return retValueList;
		}

		inline const List GetList()
		{
			List retList;
			for(ListIter lstIter = _lstCache.begin(); lstIter != _lstCache.end(); lstIter++)
			{
				retList.push_back((*lstIter));
			}
			return retList;
		}

		inline ValueType HeadValue()
		{
			// Get a direct reference to the front list element.
			Entry lstEntry = _lstCache.front();
			ValueType val = lstEntry._value;
			return val;
		}

		inline KeyType HeadKey()
		{
			Entry lstEntry = _lstCache.front();
			KeyType key = lstEntry._key;
			return key;
		}

		inline ValueType TailValue()
		{
			Entry lstEntry = _lstCache.back();
			//ValueType val = lstEntry.second;
			ValueType val = lstEntry._value;
			return val;
		}

		inline KeyType TailKey()
		{
			Entry lstEntry = _lstCache.back();
			KeyType key = lstEntry._key;
			return key;
		}

	protected:
		virtual MapIter _ImplTouch(const KeyType& key, UINT weight = 0) 
		{
			// For LRU Cache, we move the most recent item to the begining of the list.
			MapIter mapIter = _mapIndex.find(key);
			if(mapIter == _mapIndex.end())
			{
				// Cound not find the key.
				return mapIter;
			}
			if(weight > 0)
			{
				mapIter->second->_weight = weight;
			}else
			{
				// Increase the weight by 1. 
				mapIter->second->_weight++;
			}

			// Compare weights.
			Entry front = _lstCache.front();

			// Calculate Weight Percentages.
			double pctFront = (double)(((double)front._weight) / (double)GetMaxSize()) * (double)100.0;
			double pctIter  = (double)(((double)mapIter->second->_weight) / (double)GetMaxSize()) * (double)100.0;

			if(pctIter > pctFront)
			{
				// Move the found node to the head of the list.
				_lstCache.splice(_lstCache.begin(), _lstCache, mapIter->second);
			}
			return mapIter;
		}

		virtual void _ImplRemove(const MapIter& mapIter) 
		{
			m_curr_cache_size -= SizeFunction()(mapIter->second->_value);
			// Clean up.
			if(m_bDeleteValuePtrs)
			{
			//	delete mapIter->second->second;
			}
			// Remove from cache.
			_lstCache.erase(mapIter->second);
			_mapIndex.erase(mapIter);
			// mapIter is no longer usable after this.
		}

		virtual void _ImplRemove(const KeyType& key) 
		{
			MapIter mapIter = _mapIndex.find(key);
			_ImplRemove(mapIter);
		}

		virtual void _ImplInsert(const KeyType& key, const ValueType& value, const UINT weight, int special_int = 0, CString special_text = _T(""))
		{
			// Now, insert at the head of the list.
			Entry entry;
			entry._key = key;
			entry._value = value;
			entry._int = special_int;
			entry._text = special_text;
			if(weight > 0)
			{
				entry._weight = weight;
			}else
			{
				// Increment the weight.
				entry._weight += 1;
			}
			_lstCache.push_front(entry);
			ListIter lstIter = _lstCache.begin();

			// Store the index.
			_mapIndex.insert(std::make_pair(key, lstIter));
			m_curr_cache_size += SizeFunction()(value);

			// Remove elements that exceed the max size.
			while(m_curr_cache_size > m_max_cache_size) 
			{
				// Remove the last element.
				lstIter = _lstCache.end();
				--lstIter;
				_ImplRemove(lstIter->_key);
			}
		}
};

//--------------------------------------------------------------//
// The Lease Recently Used Cache will continue to grow with     //
// data pairs until the m_max_cache_size has been reached, at    //
// which point, the least recently used (bottom) item will      //
// will be removed from the list upon insertion.                //
//--------------------------------------------------------------//
template<class KeyType, class ValueType, class SizeFunction = CountFunction<ValueType> >
class LRUCache : public Cache<KeyType, ValueType, SizeFunction>
{
public:
	LRUCache()
	{
		Cache(SFLEX_CACHE_DEFAULT_MAX);
	}
	LRUCache(unsigned long _size) : Cache(_size)
	{
	}
	virtual ~LRUCache()
	{
		Clear();
	}

	inline KeyType MostRecentlyUsedKey()
	{
		return HeadKey();
	}

	inline ValueType MostRecentlyUsedValue()
	{
		return HeadValue();
	}

	inline KeyType LeastRecentlyUsedKey()
	{
		return TailKey();
	}

	inline ValueType LeastRecentlyUsedValue()
	{
		return TailValue();
	}
};

//--------------------------------------------------------------//
// The Most Recently Used Cache will continue to grow with      //
// data pairs until the m_max_cache_size has been reached, at    //
// which point, the most recently used (bottom) item will       //
// will be removed from the list upon insertion.                //
//--------------------------------------------------------------//
template<class KeyType, class ValueType, class SizeFunction = CountFunction<ValueType> >
class MRUCache : public Cache<KeyType, ValueType, SizeFunction>
{
public:
	MRUCache()
	{
		Cache(SFLEX_CACHE_DEFAULT_MAX);
	}
	MRUCache(unsigned long _size) : Cache(_size)
	{
	}
	virtual ~MRUCache()
	{
		Clear();
	}

	inline KeyType MostRecentlyUsedKey()
	{
		return TailKey();
	}

	inline ValueType MostRecentlyUsedValue()
	{
		return TailValue();
	}

	inline KeyType LeastRecentlyUsedKey()
	{
		return HeadKey();
	}

	inline ValueType LeastRecentlyUsedValue()
	{
		return HeadValue();
	}

protected:
	virtual MapIter _ImplTouch(const KeyType &key) 
	{
		// For MRU we move to the end of the list.
		MapIter mapIter = _mapIndex.find(key);
		if(mapIter == _mapIndex.end())
		{
			return mapIter;
		}
		// Move the found node to the head of the list.
		_lstCache.splice(_lstCache.end(), _lstCache, mapIter->second);
		return mapIter;
	}

	virtual void _ImplInsert(const KeyType& key, const ValueType& value)
	{
		// Now, insert at the tail of the list.
		_lstCache.push_back(std::make_pair(key, value));
		// Note, to actually access the last element without going over, we prefix with --.
		ListIter lstIter = --_lstCache.end();

		// Store the index.
		_mapIndex.insert(std::make_pair(key, lstIter));
		m_curr_cache_size += SizeFunction()(value);

		// Remove elements that exceed the max size.
		while(m_curr_cache_size > m_max_cache_size) 
		{
			// Remove the last element.
			lstIter = _lstCache.end();
			--lstIter;
			_ImplRemove( lstIter->first );
		}
	}
};

//--------------------------------------------------------------//
// The Randomly Used Cache will continue to grow with           //
// data pairs until the m_max_cache_size has been reached, at    //
// which point, a random it will be removed from the list upon  //
// insertion.                                                   //
//--------------------------------------------------------------//
template<class KeyType, class ValueType, class SizeFunction = CountFunction<ValueType> >
class RandomCache : public Cache<KeyType, ValueType, SizeFunction>
{
public:
	RandomCache()
	{
		Cache(SFLEX_CACHE_DEFAULT_MAX);
	}
	RandomCache(unsigned long _size) : Cache(_size)
	{
	}
	virtual ~RandomCache()
	{
		Clear();
	}

	KeyType LastRandomlyUsedKey()
	{
		unsigned int i = 0;
		ListIter lstIter = _lstCache.begin();
		for(ListConstIter lstIter = _lstCache.begin(); (lstIter != _lstCache.end()) && (i <= _curr_rand_pos); lstIter++)
		{
			i++;
		}
		//return lstIter->first;
		return lstIter->_key;
	}

	ValueType LastRandomlyUsedValue()
	{
		unsigned int i = 0;
		ListIter lstIter = _lstCache.begin();
		for(ListConstIter lstIter = _lstCache.begin(); (lstIter != _lstCache.end()) && (i <= _curr_rand_pos); lstIter++)
		{
			i++;
		}
		//return lstIter->second;
		return lstIter->_value;
	}

protected:
	unsigned int _curr_rand_pos;
	ListConstIter _lstIterRand;

	virtual MapIter _ImplTouch(const KeyType &key) 
	{
		// For MRU we move to the end of the list.
		MapIter mapIter = _mapIndex.find(key);
		if(mapIter == _mapIndex.end())
		{
			return mapIter;
		}
		// Find a random value and position.
		_curr_rand_pos = rand() % m_curr_cache_size;
		unsigned int i = 0;
		ListConstIter lstIter = _lstCache.begin();
		for(ListConstIter lstIter = _lstCache.begin(); (lstIter != _lstCache.end()) && (i <= _curr_rand_pos); lstIter++)
		{
			i++;
		}
		// Save the position for use in Insert.
		_lstIterRand = lstIter;
		// Move the found node to the head of the list.
		_lstCache.splice(lstIter, _lstCache, mapIter->second);
		return mapIter;
	}
};

} // namespace sflex


#endif // __SFLCACHE__H__
