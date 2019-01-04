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
#include "BooleanAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("BooleanAttribute");

   const DString TRUE_VALUE  = I_( "yes" );
   const DString FALSE_VALUE = I_( "no" );
}

namespace CND
{
   extern const long ERR_INVALID_BOOLEAN_ATTRIBUTE;
}

//******************************************************************************
BooleanAttribute::BooleanAttribute( const DString &tagName, xercesc::AttributeList &attributes, bool defaultValue )
: _tagName( tagName ),
_defaultValue( defaultValue )
{

   DString value = valueOf( tagName, attributes );

   if( value == TRUE_VALUE )
      _boolValue = true;

   else if( value == FALSE_VALUE )
      _boolValue = false;

   else if( value == NULL_STRING )
      _boolValue = defaultValue;

   else
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("VALUE"), value );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_BOOLEAN_ATTRIBUTE, strIDI );
   }

}

BooleanAttribute::BooleanAttribute( const DString &tagName, bool boolValue, bool defaultValue )
: _tagName( tagName ),
_boolValue( boolValue ),
_defaultValue( defaultValue )
{
}

//******************************************************************************
ElementAttribute *BooleanAttribute::clone() const
{
   return(new BooleanAttribute(*this));
}

//******************************************************************************
const DString &BooleanAttribute::getTagName() const
{
   return(_tagName);
}

//******************************************************************************
const DString &BooleanAttribute::getValue() const
{
   if( _boolValue )
      return(TRUE_VALUE);
   else
      return(FALSE_VALUE);
}

//******************************************************************************
bool BooleanAttribute::hasDefaultValue() const
{
   return(_boolValue == _defaultValue);
}
