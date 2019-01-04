//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFConstObjIter.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : May 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFConstObjIter
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF iFAST/core/bfcbo/bfconstobjiter.cpp-arc  $", "$Revision:   1.9  $" )

#include <srcprag.h>
#include "bfconstobjiter.hpp"
#include <condition.hpp>
#include <conditionmanager.hpp>
#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafielditer.hpp>
#include <assert.h>

#include <bfcbo/bfcbo.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BFConstObjIter" );
}

namespace CND
{
   extern const I_CHAR *BFBASE_CONDITION;
}

//***************************************************************************************************
BFConstObjIter::BFConstObjIter( const BFAbstractCBO& bfObj, const BFDataGroupId& idDataGroup, bool matchSubstrings, enum BFConstObjIter::ITERTYPE type, bool initializeStrKeyMap, bool forceUseStrKeyMap )
: pDataFilter_( NULL )
, bKeyFiltered_( false )
, bPrefixKeyFilter_( false )
, _pContainer( &bfObj )
, idDataGroup_( idDataGroup )
, _iterType( type )
, _currContainer( HOST_CONTAINER )
, _critType( OBJ_TYPE_NONE )
, _critActivity( OBJ_ACTIVITY_NONE )
, _lastObjType( OBJ_TYPE_NONE )
, _lastOnEnd( false )
, _critMatchSubstrings(matchSubstrings)
, bUseStrKeyMap_( false )
, _needRefresh( true )
, bInitialized_( false )
, bIsVersionable_( true )
{
   EXECHISTI( I_( "BFConstObjIter( const BFAbstractCBO &, const BFDataGroupId &, bool, enum BFConstObjIter:: ITERTYPE, bool, bool )" ) );

   bIsVersionable_ = dynamic_cast< const BFCBO* >( _pContainer )->isVersionable();

   bfObj.registerObserver( ifds::NullFieldId, idDataGroup_, this, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE );

   if( _pContainer->hasNonHostData() || forceUseStrKeyMap || 
       ( idDataGroup_ != BF::HOST && dynamic_cast< const BFCBO* >( _pContainer )->isVersionable() ) )
   {
      bUseStrKeyMap_ = true;
   }
   else
   {
      bUseStrKeyMap_ = false;
   }

   if( !isVersionable() ) {
      begin();
   } 
   else if( initializeStrKeyMap || !useStrKeyMap() )
   {
      //set iter to begin and position to first match
      if( useStrKeyMap() )
      {
         refreshStrKeyMap();
      }
      else
      {
         _currIter = _pContainer->_objectMap.begin();
      }

      repositionIterator();
      _needRefresh = false;
   }
   bInitialized_ = true;
}

//***************************************************************************************************
BFConstObjIter::~BFConstObjIter()
{
//   EXECHIST2( I_("BFConstObjIter"), I_( "~BFConstObjIter(  )" ) );

   _strKeyMap.clear();
}


//***************************************************************************************************
void BFConstObjIter::refreshStrKeyMap()
{
//   EXECHISTI( I_( "refreshStrKeyMap(  )" ) );
   if( !isVersionable() ) return;

   // These next two lines replace creating the StrKeyEntry within the while loop.
   //  This is related to a perfomance issue and saves approx. 2% of application time.
   StrKeyEntry lStrKeyEntry( NULL_STRING, 0 );
   lStrKeyEntry._str.reserve( 60 );
   _strKeyMap.clear();
   _currIter = _pContainer->_objectMap.begin();
   while( _currIter != _pContainer->_objectMap.end() )
   {
      const BFObjectKey & currBFOKey = (*_currIter).first;
      if( currBFOKey.getDataGroupId() == idDataGroup_ || _pContainer->isParentDataGroup( currBFOKey.getDataGroupId(), idDataGroup_ ) )
      {
         lStrKeyEntry._str = currBFOKey.getStringKey();
         lStrKeyEntry._objType = currBFOKey.getType();
         _strKeyMapIter = _strKeyMap.find( lStrKeyEntry );
         if( _strKeyMapIter == _strKeyMap.end() )
         {
            _strKeyMap.insert( STR_KEY_MAP::value_type( lStrKeyEntry, _currIter ));
         }
         else if( _pContainer->isParentDataGroup( (*(*_strKeyMapIter).second).first.getDataGroupId(), currBFOKey.getDataGroupId() ) )
         {
            _strKeyMap.erase( _strKeyMapIter );
            _strKeyMap.insert(STR_KEY_MAP::value_type( lStrKeyEntry, _currIter));
         }
      }
      ++_currIter;
   }
   _strKeyMapIter = _strKeyMap.begin();
}

//***************************************************************************************************
bool BFConstObjIter::begin( BF_OBJ_TYPE type, BF_OBJ_ACTIVITY activity, DString strKey)
{
//   EXECHISTI( I_( "begin( BF_OBJ_TYPE, BF_OBJ_ACTIVITY, DString )" ) );
   if( !isVersionable() ) {
      _critStringKey = strKey;
      if( strKey == I_("") ) {
         _currIter = _pContainer->_objectMap.begin();
      } else {
         return( repositionIterator() );
      }
      _lastOnEnd = ( _currIter == _pContainer->_objectMap.end() );
      return( true );
   }

   _critType        =  type;
   _critActivity    =  activity;
   _critStringKey   =  strKey;
   _currIter        = _pContainer->_objectMap.begin();
   if( useStrKeyMap() )
      _strKeyMapIter   = _strKeyMap.begin() ;

   if( _needRefresh )
   {
      if( useStrKeyMap() )
      {
         refreshStrKeyMap();
      }
      _needRefresh = false;
   }

   return(repositionIterator());
}

//***************************************************************************************************
bool BFConstObjIter::repositionIterator( )
{
//   EXECHISTI( I_( "repositionIterator(  )" ) );
   if( !isVersionable() ) {
     // looking in a non-versionable list ... assume that we just want to do a string match.
     const BFObjectKey key( _critStringKey );

     _currIter = _pContainer->_objectMap.find( key );

     if( _pContainer->_objectMap.end() != _currIter ) {
        const BFObjectKey& rKey = (*_currIter).first;
        _lastStringKey = rKey.getStringKey();
//         _lastObjType   = rKey.getType();
        _lastOnEnd     = false;
        return(true);
     } else {
        _currIter  = _pContainer->_objectMap.end();
        _lastOnEnd = true;
        return( false );
     }
  }

//CP20041209   bool bIsVersionable = dynamic_cast< const BFCBO* >( _pContainer )->isVersionable();
//CP20041209   if( false == bIsVersionable ) {
//CP20041209      // looking in a non-versionable list ... assume that we just want to do a string match
//CP20041209      const BFObjectKey key( _critStringKey );
//CP20041209      if( bInitialized_ ) {
//CP20041209         _currIter = _pContainer->_objectMap.find( key );
//CP20041209      } else {
//CP20041209         _currIter = _pContainer->_objectMap.begin();
//CP20041209      }
//CP20041209
//CP20041209      if( _pContainer->_objectMap.end() != _currIter ) {
//CP20041209         const BFObjectKey& rKey = (*_currIter).first;
//CP20041209         _lastStringKey = rKey.getStringKey();
//CP20041209         _lastObjType   = rKey.getType();
//CP20041209         _lastOnEnd     = false;
//CP20041209         return(true);
//CP20041209      } else {
//CP20041209         _currIter  = _pContainer->_objectMap.end();
//CP20041209         _lastOnEnd = true;
//CP20041209         return( false );
//CP20041209      }
//CP20041209   }

   while( useStrKeyMap() ? _strKeyMapIter != _strKeyMap.end() : _currIter != _pContainer->_objectMap.end() )
   {
      if( useStrKeyMap() )
      {
         _currIter = (*_strKeyMapIter).second;
      }

      const BFObjectKey& rObjKey = (*_currIter).first;
      if( _critStringKey != NULL_STRING        && _critMatchSubstrings && ( rObjKey.getStringKey().find(_critStringKey) == DString::npos) ||
          _critStringKey != NULL_STRING        && !_critMatchSubstrings && !( rObjKey.getStringKey() == _critStringKey) ||
          _critActivity  != OBJ_ACTIVITY_NONE  && rObjKey.getActivity() != _critActivity            ||
          _critType      != OBJ_TYPE_NONE      && rObjKey.getType()     != _critType                ||
          _iterType      == NON_DELETED        && rObjKey.getActivity() == OBJ_ACTIVITY_DELETED     ||
          _iterType      == ADDED              && rObjKey.getActivity() != OBJ_ACTIVITY_ADDED       ||
          _iterType      == DELETED            && rObjKey.getActivity() != OBJ_ACTIVITY_DELETED     ||   
          pDataFilter_ && !checkDataFilter()              ||
          bKeyFiltered_  && !checkKeyFilter()             
        )

         if( useStrKeyMap() )
         {
            ++_strKeyMapIter;
         }
         else
         {
            ++_currIter;
         }
      else
      {
         _lastStringKey = rObjKey.getStringKey();
         _lastObjType   = rObjKey.getType();
         _lastOnEnd     = false;
         return(true);
      }
   }
   _currIter  = _pContainer->_objectMap.end();
   _lastOnEnd = true;
   return(false);

}

//***************************************************************************************************
bool BFConstObjIter::operator++()
{
//   EXECHISTI( I_( "++(  )" ) );
   checkIterator();
   if( !isVersionable() ) {
      ++_currIter;
      _lastOnEnd = ( _currIter == _pContainer->_objectMap.end() );
      return( !_lastOnEnd );
   } else if( useStrKeyMap() ) {
      ++_strKeyMapIter;
   } else {
      ++_currIter;
   }
//CP20041209   if( useStrKeyMap() )
//CP20041209      ++_strKeyMapIter;
//CP20041209   else
//CP20041209      ++_currIter;
//CP20041209
   return(repositionIterator());
}

//***************************************************************************************************
bool BFConstObjIter::positionByKey( const DString &strKey, BF_OBJ_TYPE lObjType )
{
//   EXECHISTI( I_( "positionByKey( const DString &, BF_OBJ_TYPE )" ) );
   DString      oldKey      = _critStringKey;
   BF_OBJ_TYPE  oldObjType  = _critType;
   _critStringKey = strKey;
   _critType      = lObjType;

   if( useStrKeyMap() )
   {
      _strKeyMapIter = _strKeyMap.begin();
   }
   else
   {
      _currIter = _pContainer->_objectMap.begin();
   }

   bool retVal = repositionIterator();
   _critStringKey = oldKey;
   _critType      = oldObjType;
   return(retVal);
}


//******************************************************************************
BFAbstractCBO * BFConstObjIter:: addNewObject( DString & strKey )
{
//   EXECHISTI( I_( "addNewObject( DString & )" ) );
   if( strKey != NULL_STRING )
      strKey = NULL_STRING;

   BFAbstractCBO * retVal = _pContainer->getObject( strKey, idDataGroup_, _critType, OBJ_ACTIVITY_ADDED );

   _currIter = _pContainer->_objectMap.find( BFObjectKey( strKey, idDataGroup_, OBJ_ACTIVITY_ADDED, _critType) );

   if( useStrKeyMap() )
   {
      _strKeyMapIter = _strKeyMap.insert( STR_KEY_MAP::value_type( StrKeyEntry( strKey, _critType ), _currIter ) ).first;
   }

   repositionIterator();

   return(retVal);

}


//***************************************************************************************************
void BFConstObjIter::positionOnNextMatch( const BFData &matchCriteria, const BFDataGroupId& idDataGroup )
{
//   EXECHISTI( I_( "positionOnNextMatch( const BFData &, const BFDataGroupId & )" ) );
   assert( isVersionable() );
   while( useStrKeyMap() ? _strKeyMapIter != _strKeyMap.end() : _currIter != _pContainer->_objectMap.end() )
   {
      repositionIterator();
      DString strValue;
      DString strOut;
      BFConstDataFieldIter dIter( matchCriteria );
      bool fAllMatch = true;

      for( ; dIter; ++dIter )
      {
         const BFFieldId &idTag = dIter().getId();
         matchCriteria.getElementValue( idTag, strValue ); 
         (*_currIter).second->getInstance()->getField( idTag, strOut, idDataGroup );

         strOut.strip().upperCase();
         strValue.strip().upperCase();
         if( strOut != strValue )
         {
            fAllMatch = false;
            break;
         }
      }
      if( fAllMatch )
      {
         return;
      }

      if( useStrKeyMap() )
      {
         ++_strKeyMapIter;
      }
      else
      {
         ++_currIter;
      }
   }  
   if( _strKeyMapIter != _strKeyMap.end() )
      _currIter = _pContainer->_objectMap.end();
}

//******************************************************************************
bool BFConstObjIter::isBegin()
{
   if( !isVersionable() ) {
      return( _currIter == _pContainer->_objectMap.begin() );
   }

   checkIterator();
   BFConstObjIter locIter( *this );

   locIter.begin(_critType, _critActivity, _critStringKey);
   return(locIter.samePosition(_currIter));
};

//******************************************************************************
bool BFConstObjIter::samePosition(BFAbstractCBO::OBJECT_MAP_CONST_ITER& objIter ) const
{
   return(_currIter == objIter);
}
//******************************************************************************
int BFConstObjIter::getNumberOfItemsInList()
{
   checkIterator();

   BFConstObjIter locIter( *this );

   locIter.begin(_critType, _critActivity, _critStringKey);
   int _count = 0;

   while( !locIter.end() )
   {
      ++_count;
      ++locIter;
   };
   return(_count);
}
//******************************************************************************
bool BFConstObjIter::end()
{
   if( !isVersionable() ) {
      return( _currIter == _pContainer->_objectMap.end() );
   }

   checkIterator();
   if( useStrKeyMap() )
   {
      return(_strKeyMapIter == _strKeyMap.end());
   }
   else
   {
      return(_currIter == _pContainer->_objectMap.end());
   }
}

//******************************************************************************
bool BFConstObjIter::isDummy()
{
   if( _pContainer && _pContainer->isDummy( _currIter ) )
   {
      return(true);
   }
   else
   {
      return(false);
   }
}

//******************************************************************************
bool BFConstObjIter::hasHostUpdates( bool inclSubObj )
{
//   EXECHISTI( I_( "hasHostUpdates( bool )" ) );
   bool retVal = false;
   if( ! end() )
   {
      const BFObjectKey & rObjKey = (*_currIter).first;
      if( ( rObjKey.getActivity() == OBJ_ACTIVITY_DELETED || rObjKey.getActivity() == OBJ_ACTIVITY_ADDED ) && 
          rObjKey.getDataGroupId() == BF::HOST  ||
          (*_currIter).second && 
          (*_currIter).second->getInstance() && 
          (*_currIter).second->getInstance()->hasHostUpdates( inclSubObj ) )
      {
         retVal = true;
      }
   }
   return(retVal);
}

//******************************************************************************
bool BFConstObjIter::hasTransactionUpdates( bool inclSubObj )
{
   bool retVal = false;
   if( ! end() )
   {
      const BFObjectKey & rObjKey = (*_currIter).first;
      if( ( rObjKey.getActivity() == OBJ_ACTIVITY_DELETED || rObjKey.getActivity() == OBJ_ACTIVITY_ADDED ) && 
          rObjKey.getDataGroupId() == BF::HOST  ||
          (*_currIter).second && 
          (*_currIter).second->getInstance() && 
          (*_currIter).second->getInstance()->hasTransactionUpdates( inclSubObj ) )
      {
         retVal = true;
      }
   }
   return(retVal);
}

//******************************************************************************
void BFConstObjIter::onNotify( E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString &hint )
{
   if( _pContainer->_hasNonBFHOSTsetObjects )
   {
      if( !useStrKeyMap() )
      {
         refreshStrKeyMap();
      }
      bUseStrKeyMap_ = true;
   }

   if( eEventId ==  E_EVENT_CBO_OBJITER_UPDATE && useStrKeyMap() )
   {
      _needRefresh = true;
   }
}

//******************************************************************************
void BFConstObjIter::checkIterator()
{
   if( _needRefresh && useStrKeyMap() )
   {
      refreshStrKeyMap();

      if( _lastOnEnd )
      {
         _currIter = _pContainer->_objectMap.end();
         if( useStrKeyMap() )
         {
            _strKeyMapIter = _strKeyMap.end();
         }
      }
      else
      {
         DString oldKey = _critStringKey;
         BF_OBJ_TYPE oldObjType = _critType;
         _critStringKey = _lastStringKey;
         _critType      = _lastObjType ;

         _strKeyMapIter = _strKeyMap.begin();
         repositionIterator();

         _critStringKey = oldKey;
         _critType      = oldObjType;
      };
      _needRefresh = false;
   };
};


//******************************************************************************
BFAbstractCBO* BFConstObjIter::getObject() 
{
   checkIterator();
   return(*_currIter).second->getInstance();
}

//******************************************************************************
bool BFConstObjIter::setKeyFilter( const DString & dstFilter, bool bStartOfKey )
{
   DString ldstFilter( dstFilter );
   DString::size_type  pos = 0;
   DString filterExpr = NULL_STRING;
   vKeyFilter_.clear();
   bKeyFiltered_ = false;
   bPrefixKeyFilter_ = bStartOfKey;

   while( ldstFilter != NULL_STRING )
   {
      pos = ldstFilter.find( I_(";") );
      filterExpr = ldstFilter.substr(0, pos );

      if( pos != DString::npos )
      {
         ldstFilter = ldstFilter.substr( pos + 1 );
      }
      else
      {
         ldstFilter = NULL_STRING;
      }

      vKeyFilter_.push_back( filterExpr );
      if( !bKeyFiltered_ )
      {
         bKeyFiltered_ = true;
      }
      if( !bStartOfKey )
      {
         break;
      }
   };

   repositionIterator( );
   return(true);
}

//******************************************************************************
bool BFConstObjIter::getKeyFilter( DString & dstFilter ) const
{
   dstFilter = NULL_STRING;
   if( bKeyFiltered_ )
   {
      int vectorSize = vKeyFilter_.size();
      for( int i = 0; i < vectorSize; i++ )
      {
         dstFilter += vKeyFilter_[i] + I_(";");
      }
   };
   bPrefixKeyFilter_ = false;
   return(true);

}

//******************************************************************************
bool BFConstObjIter::clearKeyFilter( )
{
   vKeyFilter_.clear();
   bKeyFiltered_ = false;
   return(true);
}

//******************************************************************************
bool BFConstObjIter::setDataFilter( const DString & dstFilter )
{

   bool rtnVal = false;
   if( !pDataFilter_ )
      pDataFilter_ = new BFDataFilter();

   if( pDataFilter_ )
      rtnVal = pDataFilter_->setFilter( dstFilter );

   if( !rtnVal )
   {
      delete pDataFilter_;
      pDataFilter_ = NULL;
   };

   repositionIterator( );
   return(rtnVal);
}

//******************************************************************************
bool BFConstObjIter::getDataFilter( DString & dstFilter ) const
{
   dstFilter = NULL_STRING;

   if( pDataFilter_ )
      pDataFilter_->getFilter( dstFilter );

   return(true);
}

//******************************************************************************
bool BFConstObjIter::clearDataFilter( )
{
   if( pDataFilter_ )
      delete pDataFilter_;
   pDataFilter_ = NULL;

   return(true);
}

//******************************************************************************
bool BFConstObjIter::checkDataFilter() const
{
   if( pDataFilter_ )
      return(pDataFilter_->isVisible( (*_currIter).second->getInstance(), idDataGroup_ ));

   return(true);
}

//******************************************************************************
bool BFConstObjIter::checkKeyFilter() const
{
   if( bKeyFiltered_ )
   {
      DString lFilter = NULL_STRING;
      int vectorSize = vKeyFilter_.size();
      for( int i = 0; i < vectorSize; i++ )
      {
         if( !bPrefixKeyFilter_ )
         {
            if( (*_currIter).first.getStringKey().find( vKeyFilter_[i] ) == 0 )
               return(true);
            else
               return(false);
         }
         else if( (*_currIter).first.getStringKey().find( vKeyFilter_[i] ) == DString::npos )
            return(false);
      }
   };
   return(true);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/bfconstobjiter.cpp-arc  $
//
//   Rev 1.9   Feb 20 2009 14:47:54   purdyech
//ZTS Revision 6
//
//   Rev 1.8   Dec 09 2004 12:16:58   purdyech
//PET910 - Non-versionable CBO optimization fixes
//
//   Rev 1.7   Nov 14 2004 16:49:28   PURDYECH
//PET910 - NonVersionable optimization for list iteration
//
//   Rev 1.6   Oct 22 2004 08:53:58   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.5   Aug 12 2004 10:03:32   PURDYECH
//PTS10032768 - Avoid use of StringKeyMaps in nonVersionable CBOs.
// 
//    Rev 1.4   Jan 06 2003 16:40:18   PURDYECH
// BFDataGroupId changeover
// 
//    Rev 1.3   Nov 12 2002 11:59:16   PURDYECH
// Completely define initialization list.
// 
//    Rev 1.2   Oct 25 2002 15:06:04   SMITHDAV
// Remove CP comments.
// 
//    Rev 1.1   Oct 09 2002 17:40:02   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Aug 29 2002 13:30:44   PURDYECH
// Initial revision.
 * 
 *    Rev 1.19   05 Jun 2002 14:10:18   SMITHDAV
 * Fix bug in isBegin() and getNumberOfItemsInList()
 * 
 *    Rev 1.18   22 May 2002 17:54:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   22 Mar 2002 15:13:58   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.16   Feb 27 2002 20:45:08   PURDYECH
 * Changed getObject to return BFAbstractCBO*& like it used to.  I'm not happy about doing this, but it's needful as many programs seem to take advantage of this backdoor entry into the Object Map.
 * 
 *    Rev 1.15   Feb 25 2002 18:50:48   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.14   03 Jul 2001 16:22:18   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.13   Jun 26 2001 19:01:28   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 * 
 *    Rev 1.12   18 Jun 2001 14:29:18   YINGZ
 * fix removeObjectFromMap 
 * 
 *    Rev 1.11   03 May 2001 14:02:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   03 Apr 2001 14:17:40   BUZILAMI
 * removeObjectFromMap fix
 * 
 *    Rev 1.9   02 Apr 2001 10:15:12   BUZILAMI
 * added doDeleteObject and   the  _hasNonBFHOSTsetObjects flag
 * 
 *    Rev 1.8.1.0   30 Mar 2001 16:33:00   BUZILAMI
 * added doDeleteObject and   the  _hasNonBFHOSTsetObjects flag
 * 
 *    Rev 1.8   Jul 21 2000 17:10:56   BUZILA
 * documentation added
 * 
 *    Rev 1.7   Jun 02 2000 14:04:38   BUZILA
 * ...
 * 
 *    Rev 1.6   May 16 2000 11:09:52   BUZILA
 * fix DeleteObject
 * 
 *    Rev 1.5   May 15 2000 15:55:04   DT24433
 * performance tuning in refreshStrKeyMap
 * 
 *    Rev 1.4   May 11 2000 16:19:56   BUZILA
 * forcing refresh on deletes
 * 
 *    Rev 1.3   Apr 13 2000 10:40:22   BUZILA
 * data Filtering issues
 * 
 *    Rev 1.2   Apr 03 2000 08:59:50   BUZILA
 * Added start of key condition in filtering
 * 
 *    Rev 1.1   Mar 23 2000 16:23:44   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.0   Feb 15 2000 10:57:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.25   Feb 04 2000 14:58:04   BUZILA
 * fix
 * 
 *    Rev 1.24   Feb 03 2000 10:12:40   BUZILA
 * added CALCULATED_FIELD flag and hasTransactionUpdates method
 * 
 *    Rev 1.23   Feb 02 2000 10:33:48   BUZILA
 * we should not send transactions for uncommited data
 * 
 *    Rev 1.22   Feb 01 2000 13:07:32   BUZILA
 * fixes
 * 
 *    Rev 1.21   Jan 31 2000 13:05:46   BUZILA
 * changes
 * 
 *    Rev 1.20   Jan 26 2000 12:11:06   BUZILA
 * changed StrMap and added isDummy()
 * 
 *    Rev 1.19   Jan 18 2000 18:37:42   VASILEAD
 * added one parameter to removeObjectFromMap
 * 
 *    Rev 1.18   Jan 06 2000 13:34:42   BUZILA
 * added getGroupFlags method
 * 
 *    Rev 1.17   Jan 04 2000 12:16:22   BUZILA
 * changes...
 * 
 *    Rev 1.16   Dec 21 1999 12:45:58   BUZILA
 * Validate Field changes
 * 
 *    Rev 1.15   Dec 19 1999 16:55:14   BUZILA
 * added revision area
 * 
 */


