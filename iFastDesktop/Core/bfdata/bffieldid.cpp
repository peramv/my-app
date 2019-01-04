#include "stdafx.h"
#include "bffieldid.hpp"
#include <limits>

#include <boost/thread/recursive_mutex.hpp>
#include <bfutil/bfguard.hpp>
#include <bfutil/bfcritsec.hpp>

static BFCritSec s_cs;                   
unsigned long s_fOpt = 0;

const unsigned long BFFieldId::allowDynamic = 0x00000001;

void BFFieldId::setOptions( unsigned long fOpt )
{
   BFGuard g(s_cs);
   s_fOpt = fOpt;
}

unsigned long BFFieldId::getOptions()
{
   BFGuard g(s_cs);
   return( s_fOpt );
}

bool dynamicFieldsAllowed()
{
   return( ( s_fOpt & BFFieldId::allowDynamic ) == BFFieldId::allowDynamic );
}
 
/**
 * Each instance of BFFieldId has a numeric ID which is assigned from
 * the DataDictionary (for 'normal' BFFieldId objects) or from the
 * FieldId creator function (for 'dynamic' BFFieldId objects).  The
 * value of s_iBeginDynFieldId defines the 'cutoff' point at which
 * a created field is no longer considered a 'normal' field.
 */
static const long s_iBeginDynFieldId = 100 * 1000000;

extern const BFVarTextFieldId idVarTextField( s_iBeginDynFieldId , I_("GenericVarText") );

namespace {

   typedef std::map< DString, const BFFieldId* > NameToIdMap;
   NameToIdMap& getFieldNameIdXRefMap()
   {
      static NameToIdMap xRefMap;
      return( xRefMap );
   }
   NameToIdMap& getDynFieldNameIdXRefMap()
   {
      static NameToIdMap xRefMap;
      return( xRefMap );
   }
   
   typedef std::map< long, DString > IdToNameMap;
   IdToNameMap& getFieldIdNameXRefMap()
   {
      static IdToNameMap xRefMap;
      return( xRefMap );
   }
   IdToNameMap& getDynFieldIdNameXRefMap()
   {
      static IdToNameMap xRefMap;
      return( xRefMap );
   }

   boost::recursive_mutex& getMutexDynIdMaps()
   {
      static boost::recursive_mutex m;
      return( m );
   }

   const BFFieldId& createDynFieldId( const DString& name )
   {
      static long idDynField = s_iBeginDynFieldId;
      BFVarTextFieldId* pF = new BFVarTextFieldId( ++idDynField, name.c_str() );
      return( *pF );
   }
}

BFFieldId::BFFieldId( long idField,
                      const I_CHAR * name )
: id_( idField )
#ifdef _DEBUG
, name_( const_cast< I_CHAR* >( name ) )
#endif
{
   if( false == isDynamic() )
   {
      DString fld( name );
      NameToIdMap& nameXRefMap = getFieldNameIdXRefMap(); 
      nameXRefMap.insert( NameToIdMap::value_type( fld, this ) );

      IdToNameMap& idXRefMap = getFieldIdNameXRefMap();
      idXRefMap.insert( IdToNameMap::value_type( id_, fld ) );
   }
   else
   {
#ifdef _DEBUG
      name_ = new I_CHAR[ i_strlen( name ) + 1 ];
      i_strcpy( name_, name );
#endif
      DString fld( name );
      boost::recursive_mutex::scoped_lock l( getMutexDynIdMaps() );
      NameToIdMap& nameXRefMap = getDynFieldNameIdXRefMap(); 
      nameXRefMap.insert( NameToIdMap::value_type( fld, this ) );

      IdToNameMap& idXRefMap = getDynFieldIdNameXRefMap();
      idXRefMap.insert( IdToNameMap::value_type( id_, fld ) );
   }
}

BFFieldId::~BFFieldId()
{
#ifdef _DEBUG
   if( isDynamic() )
   {
      delete[] name_;
   }
#endif
}

BFFieldId& BFFieldId::operator=( const BFFieldId& rhs )
{ 
   id_ = rhs.id_;
#ifdef _DEBUG
   if( rhs.isDynamic() )
   {
      name_ = new I_CHAR[ i_strlen( rhs.name_ ) + 1 ];
      i_strcpy( name_, rhs.name_ );
   }
   else
   {
      name_ = rhs.name_;
   }
#endif
   return( *this );
}

bool BFFieldId::isDynamic() const 
{
   return( s_iBeginDynFieldId < id_ &&
           std::numeric_limits< long >::max() != id_ );
}

const DString& BFFieldId::getName() const
{
   return( getName( getId() ) );
}

const DString& BFFieldId::getName( long id )
{
   IdToNameMap::iterator it = getFieldIdNameXRefMap().find( id );
   if( getFieldIdNameXRefMap().end() == it )
   {
      if( dynamicFieldsAllowed() ) {
         boost::recursive_mutex::scoped_lock l( getMutexDynIdMaps() );
         IdToNameMap::iterator itDyn = getDynFieldIdNameXRefMap().find( id );
         if( getDynFieldIdNameXRefMap().end() == itDyn ) 
         {
            DString idi;
            addIDITagValue( idi, I_( "NAME" ), DString::asString( id ) );
            BF_CE_THROW_IDI( BFFieldIdUnknownException, I_( "BFFieldId::getName( long id )" ), idi );
         }
         return( (*itDyn).second );
      }
      DString idi;
      addIDITagValue( idi, I_( "NAME" ), DString::asString( id ) );
      BF_CE_THROW_IDI( BFFieldIdUnknownException, I_( "BFFieldId::getName( long id )" ), idi );
   }
   return( (*it).second );
}

const BFFieldId& BFFieldId::getId( const DString& name )
{
   NameToIdMap::iterator it = getFieldNameIdXRefMap().find( name );
   if( it == getFieldNameIdXRefMap().end() )
   {
      if( dynamicFieldsAllowed() ) {
         boost::recursive_mutex::scoped_lock l( getMutexDynIdMaps() );
         // check the dynamic fields
         NameToIdMap::iterator itDyn = getDynFieldNameIdXRefMap().find( name );
         if( getDynFieldNameIdXRefMap().end() == itDyn )
         {
            // don't throw!  Add field to dyn map
            return( createDynFieldId( name ) );
         }
         return( *((*itDyn).second) );
      }
      DString idi;
      addIDITagValue( idi, I_( "NAME" ), name );
      BF_CE_THROW_IDI( BFFieldIdUnknownException, I_( "BFFieldId::getId( const DString& name )" ), idi );
   }
   return( *((*it).second) );
}

const BFFieldId* BFFieldId::_getId( const DString& name )
{
   NameToIdMap::iterator it = getFieldNameIdXRefMap().find( name );
   if( it == getFieldNameIdXRefMap().end() )
   {
      if( dynamicFieldsAllowed() ) {
         boost::recursive_mutex::scoped_lock l( getMutexDynIdMaps() );
         NameToIdMap::iterator itDyn = getDynFieldNameIdXRefMap().find( name );
         if( getDynFieldNameIdXRefMap().end() == itDyn )
         {
            return( &createDynFieldId( name ) );
         }
         return( ((*itDyn).second) );
      }
      return( NULL );
   }
   return( ((*it).second) );
}

const BFFieldId* BFFieldId::_getStaticId( const DString& name )
{
   NameToIdMap::iterator it = getFieldNameIdXRefMap().find( name );
   if( it == getFieldNameIdXRefMap().end() )
   {
      return( NULL );
   }
   return( ((*it).second) );
}

const BFFieldId* BFFieldId::_getDynamicId( const DString& name )
{
   if( dynamicFieldsAllowed() ) {
      boost::recursive_mutex::scoped_lock l( getMutexDynIdMaps() );
      NameToIdMap::iterator itDyn = getDynFieldNameIdXRefMap().find( name );
      if( getDynFieldNameIdXRefMap().end() == itDyn )
      {
         return( &createDynFieldId( name ) );
      }
      return( ((*itDyn).second) );
   }
   return( NULL );
}

const BFFieldId operator+( const BFFieldId& lhs, const BFFieldId& rhs )
{
   BF_THROW( BFFieldIdOpException );
}

const BFFieldId operator+( long lhs, const BFFieldId& rhs )
{
   BF_THROW( BFFieldIdOpException );
}

const BFFieldId operator+( const BFFieldId& lhs, long rhs )
{
   BF_THROW( BFFieldIdOpException );
}

BFNullFieldId::BFNullFieldId( long idField, const I_CHAR* name )
: BFFieldId( idField, name )
{
   if( getId() != 0 )
   {
      throw "not a valid id for NullFieldId";
   }
}

BFDummyFieldId::BFDummyFieldId( long idField )
: BFFieldId( idField, NULL )
{
   if( getId() < 0 || getId() > 999999 )
   {
      throw "not a valid id for a DummyFieldId";
   }
}

namespace ifds
{
   extern BFDATA_LINKAGE const BFNullFieldId NullFieldId( 0, I_( "NullFieldId" ) );
   extern BFDATA_LINKAGE const BFFieldId MaxFieldId( std::numeric_limits< long >::max(), I_( "MaxFieldId" ) );
}
