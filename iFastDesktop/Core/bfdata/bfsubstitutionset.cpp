#include "stdafx.h"
#include "bfsubstitutionset.hpp"

BFSubstitutionSet::BFSubstitutionSet( const I_CHAR** aKeys, const I_CHAR** aValues )
: pmKeys_( new KeyMap )
, pmValues_( new ValueMap )
, pvKeys_( new KeyVector )
{
   for( ; 
      *aKeys != 0x00 && **aKeys != 0x00 && *aValues != 0x00 && **aValues != 0x00; 
      ++aKeys, ++aValues )
   {
      (*pmKeys_)[ DString(*aKeys) ] = DString(*aValues);
      (*pmValues_)[ DString(*aValues) ] = DString(*aKeys);
      pvKeys_->push_back( DString(*aKeys) );
   }
   initIDI( idiString_, false );
   initIDI( idiStringOrdered_, true );

}

BFSubstitutionSet::BFSubstitutionSet( const BFSubstitutionSet& src, const std::vector< DString >& vecKeys )
: pmKeys_( new KeyMap )
, pmValues_( new ValueMap )
, pvKeys_( new KeyVector )
{
   KeyVector::const_iterator iterRestrict;
   KeyVector::const_iterator iterRestrictEnd = vecKeys.end();

   KeyMap::const_iterator iterKeys;

   for( iterRestrict =  vecKeys.begin(); 
      iterRestrict != iterRestrictEnd;
      ++iterRestrict )
   {
      pvKeys_->push_back( *iterRestrict );

      iterKeys = src.pmKeys_->find( *iterRestrict );
      if( iterKeys == src.pmKeys_->end() )
      {
         BF_THROW( BFSubstitutionException );
      }
      (*pmKeys_)[ (*iterKeys).first ] = (*iterKeys).second;
      (*pmValues_)[ (*iterKeys).second ] = (*iterKeys).first;
   }
   initIDI( idiString_, false );
   initIDI( idiStringOrdered_, true );
}

BFSubstitutionSet::BFSubstitutionSet( const BFSubstitutionSet& rhs )
: pmKeys_( new KeyMap )
, pmValues_( new ValueMap )
, pvKeys_( new KeyVector )
{
   *this = rhs;
}

BFSubstitutionSet::~BFSubstitutionSet()
{
   pmKeys_->erase( pmKeys_->begin(), pmKeys_->end() );
   delete pmKeys_;
   pmValues_->erase( pmValues_->begin(), pmValues_->end() );
   delete pmValues_;
   pvKeys_->erase( pvKeys_->begin(), pvKeys_->end() );
   delete pvKeys_;
}

BFSubstitutionSet& BFSubstitutionSet::operator=( const BFSubstitutionSet& rhs )
{
   std::copy( rhs.pmKeys_->begin(), rhs.pmKeys_->end(), std::inserter( *pmKeys_, pmKeys_->end() ) );
   std::copy( rhs.pmValues_->begin(), rhs.pmValues_->end(), std::inserter( *pmValues_, pmValues_->end() ) );
   std::copy( rhs.pvKeys_->begin(), rhs.pvKeys_->end(), std::back_inserter( *pvKeys_ ) );

   idiString_ = I_( "" );
   initIDI( idiString_, false );
   idiStringOrdered_ = I_( "" );
   initIDI( idiStringOrdered_, true );
   return( *this );
}

std::vector< DString >& 
BFSubstitutionSet::getKeys( std::vector< DString >& vecKeys ) const
{
   KeyVector::const_iterator iter;
   for( iter = pvKeys_->begin(); iter != pvKeys_->end(); ++iter )
   {
      vecKeys.push_back( (*iter) );
   }
   return( vecKeys );
}

std::vector< DString >& 
BFSubstitutionSet::getValues( std::vector< DString >& vecValues ) const
{
   KeyVector::const_iterator iter;
   for( iter = pvKeys_->begin(); iter != pvKeys_->end(); ++iter )
   {
      KeyMap::iterator itKey = pmKeys_->find( *iter );
      if( itKey == pmKeys_->end() )
      {
         BF_THROW( BFSubstitutionException );
      }
      vecValues.push_back( (*itKey).second );
   }
   return( vecValues );
}

const DString& 
BFSubstitutionSet::getKey( const DString& strValue ) const
{
   DString dstrValue( strValue );
   dstrValue.stripTrailing();
   ValueMap::iterator iter = pmValues_->find( dstrValue );
   if( iter == pmValues_->end() )
   {
      return(strValue);
   }
   return( (*iter).second );
}

const I_CHAR*
BFSubstitutionSet::getKey( const I_CHAR* pszValue ) const
{
   DString dstrValue( pszValue );
   dstrValue.stripTrailing();
   ValueMap::iterator iter = pmValues_->find( dstrValue );
   if( iter == pmValues_->end() )
   {
      return(pszValue);
   }
   return( ( (*iter).second ).c_str() );
}

const DString& 
BFSubstitutionSet::getValue( const DString& strKey ) const
{
   DString dstrKey = strKey;
   dstrKey.stripTrailing();
   KeyMap::iterator iter = pmKeys_->find( dstrKey );
   if( iter == pmKeys_->end() )
   {
      return(strKey);
   }
   return( (*iter).second );
}

const I_CHAR* 
BFSubstitutionSet::getValue( const I_CHAR* pszKey ) const
{
   DString dstrKey( pszKey );
   dstrKey.stripTrailing();
   KeyMap::iterator iter = pmKeys_->find( dstrKey );
   if( iter == pmKeys_->end() )
   {
      return(pszKey);
   }
   return( ( (*iter).second ).c_str() );
}

bool 
BFSubstitutionSet::isKey( const DString& strKey ) const
{
   DString dstrKey = strKey;
   dstrKey.stripTrailing();
   KeyMap::iterator iter = pmKeys_->find( dstrKey );
   if( iter != pmKeys_->end() )
   {
      return( true );
   }
   return( false );
}

bool 
BFSubstitutionSet::isValue( const DString& strValue ) const
{
   DString dstrValue = strValue;
   dstrValue.stripTrailing();
   ValueMap::iterator iter = pmValues_->find( dstrValue );
   if( iter != pmValues_->end() )
   {
      return( true );
   }
   return( false );
}

DString& BFSubstitutionSet::getAsIDI( DString& idiString, bool bUsePropertiesOrder ) const
{
   if( true == bUsePropertiesOrder )
   {
      idiString = idiStringOrdered_;
   }
   else
   {
      idiString = idiString_;
   }
   return( idiString );
}

DString& BFSubstitutionSet::initIDI( DString& idiString, bool bUsePropertiesOrder )
{
   idiString = I_( "" );
   if( bUsePropertiesOrder )
   {
      KeyVector::const_iterator itKey;
      KeyVector::const_iterator itKeyEnd = pvKeys_->end();
      for( itKey = pvKeys_->begin(); itKey != itKeyEnd; ++itKey )
      {
         KeyMap::const_iterator itKeyMap = pmKeys_->find( *itKey );
         if( itKeyMap == pmKeys_->end() )
         {
            BF_THROW( BFSubstitutionException ); 
         }
         idiString += (*itKeyMap).first;
         idiString += I_( '=' );
         idiString += (*itKeyMap).second;
         idiString += I_( ';' );
      }
   }
   else
   {
      KeyMap::const_iterator itKeyMap;
      KeyMap::const_iterator itKeyMapEnd = pmKeys_->end();
      for( itKeyMap = pmKeys_->begin(); itKeyMap != itKeyMapEnd; ++itKeyMap )
      {
         idiString += (*itKeyMap).first;
         idiString += I_( '=' );
         idiString += (*itKeyMap).second;
         idiString += I_( ';' );
      }
   }
   return( idiString );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfdata/bfsubstitutionset.cpp-arc  $
// 
//    Rev 1.6   Mar 11 2003 10:13:24   PURDYECH
// Added precompiled header
// 
//    Rev 1.5   Sep 18 2002 14:23:10   PURDYECH
// Make substitution keys case insensitive
// 
//    Rev 1.4   Aug 29 2002 12:49:10   PURDYECH
// ClientLocale corrections
// 
//    Rev 1.3   Jun 21 2002 10:15:56   WINNIE
// CP - Ignore trailing spaces when matching values/key.
// 
//    Rev 1.2   Jun 11 2002 12:04:02   PURDYECH
// Added a const I_CHAR* version of getKey and getValue
// 
//    Rev 1.1   22 May 2002 17:55:48   PURDYECH
// BFData Implementation
//
