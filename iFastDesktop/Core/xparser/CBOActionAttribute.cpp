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
#include "CBOActionAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("CBOActionAttribute");

   const DString TAG_NAME         = I_( "action" );

   const DString QUERY_VALUE      = I_( "query" );
   const DString ADD_VALUE        = I_( "add" );
   const DString UPDATE_VALUE     = I_( "update" );
   const DString DELETE_VALUE     = I_( "delete" );
   const DString REPLACE_VALUE    = I_( "replace" );
   const DString PROPERTIES_VALUE = I_( "properties" );

   const CBOAction CBO_ACTION_DEFAULT = CBO_ACTION_QUERY;
}

namespace CND
{
   extern const long ERR_INVALID_CBO_ACTION_ATTRIBUTE;
}

//******************************************************************************
CBOActionAttribute::CBOActionAttribute( xercesc::AttributeList &attributes )
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value == QUERY_VALUE )
      _action = CBO_ACTION_QUERY;

   else if( value == ADD_VALUE )
      _action = CBO_ACTION_ADD;

   else if( value == UPDATE_VALUE )
      _action = CBO_ACTION_UPDATE;

   else if( value == DELETE_VALUE )
      _action = CBO_ACTION_DELETE;

   else if( value == REPLACE_VALUE )
      _action = CBO_ACTION_REPLACE;

   else if( value == PROPERTIES_VALUE )
      _action = CBO_ACTION_PROPERTIES;

   else if( value == NULL_STRING )
      _action = CBO_ACTION_DEFAULT;

   else
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("VALUE"), value );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_CBO_ACTION_ATTRIBUTE, strIDI );
   }

}

CBOActionAttribute::CBOActionAttribute( CBOAction action )
: _action(action)
{
}

//******************************************************************************
ElementAttribute *CBOActionAttribute::clone() const
{
   return(new CBOActionAttribute(*this));
}

//******************************************************************************
const DString &CBOActionAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &CBOActionAttribute::getValue() const
{
   switch( _action )
   {
      
      case CBO_ACTION_QUERY:
         return(QUERY_VALUE);

      case CBO_ACTION_ADD:
         return(ADD_VALUE);

      case CBO_ACTION_UPDATE:
         return(UPDATE_VALUE);

      case CBO_ACTION_DELETE:
         return(DELETE_VALUE);

      case CBO_ACTION_REPLACE:
         return(REPLACE_VALUE);

      case CBO_ACTION_PROPERTIES:
         return(PROPERTIES_VALUE);

      default:
         assert(0); // internally inconsistant
         return(QUERY_VALUE);

   }
}

//******************************************************************************
bool CBOActionAttribute::hasDefaultValue() const
{
   return(_action == CBO_ACTION_DEFAULT);
}
