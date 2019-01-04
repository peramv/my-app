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
#include "CacheAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("CacheAttribute");

   const DString TAG_NAME         = I_( "cache" );

   const DString NONE_VALUE = I_( "none" );
   const DString PUT_VALUE  = I_( "put" );
   const DString GET_VALUE  = I_( "get" );

   const CacheAttribute::Cache CACHE_DEFAULT = CacheAttribute::CACHE_NONE;
}

namespace CND
{
   extern const long ERR_INVALID_CACHE_ATTRIBUTE;
}

//******************************************************************************
CacheAttribute::CacheAttribute( xercesc::AttributeList &attributes )
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value == NONE_VALUE )
   {
      _cache = CACHE_NONE;
   }
   else if( value == PUT_VALUE )
   {
      _cache = CACHE_PUT;
   }
   else if( value == GET_VALUE )
   {
      _cache = CACHE_GET;
   }
   else if( value == NULL_STRING )
   {
      _cache = CACHE_DEFAULT;
   }
   else
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("VALUE"), value );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_CACHE_ATTRIBUTE, strIDI );
   }

}

CacheAttribute::CacheAttribute( Cache cache )
: _cache(cache)
{
}

//******************************************************************************
ElementAttribute *CacheAttribute::clone() const
{
   return(new CacheAttribute(*this));
}

//******************************************************************************
const DString &CacheAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &CacheAttribute::getValue() const
{
   switch( _cache )
   {
      
      case CACHE_PUT:
         return(PUT_VALUE);

      case CACHE_GET:
         return(GET_VALUE);

      default:
         return(NONE_VALUE);
   }
}

//******************************************************************************
bool CacheAttribute::hasDefaultValue() const
{
   return(_cache == CACHE_DEFAULT);
}
