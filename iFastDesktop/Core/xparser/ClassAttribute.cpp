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
#include "ClassAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("ClassAttribute");

   const DString TAG_NAME      = I_( "class" );

   const DString ROOT_VALUE    = I_( "root" );
   const DString BATCH_VALUE   = I_( "batch" );
   const DString PROCESS_VALUE = I_( "process" );
   const DString CBO_VALUE     = I_( "cbo" );
   const DString PARM_VALUE    = I_( "parm" );
   const DString KEY_VALUE     = I_( "key" );
   const DString FIELD_VALUE   = I_( "field" );
}

namespace CND
{
   extern const long ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED;
   extern const long ERR_INVALID_ELEMENT_CLASS_ATTRIBUTE;
}

//******************************************************************************
ClassAttribute::ClassAttribute()
: _defaultValue( ROOT )
, _elementClass( ROOT )
{
}

//******************************************************************************
ClassAttribute::ClassAttribute( xercesc::AttributeList &attributes, ElementClass parentClass )
: _defaultValue( (parentClass==CBO||parentClass==KEY)?FIELD:PARM )
, _elementClass( _defaultValue )
{
   init( attributes );
}


//******************************************************************************
ClassAttribute::ClassAttribute( ElementClass elementClass, ElementClass parentClass )
: _defaultValue( (parentClass==CBO||parentClass==KEY)?FIELD:PARM )
, _elementClass( elementClass )
{
}

//******************************************************************************

void ClassAttribute::init( xercesc::AttributeList &attributes )
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value == ROOT_VALUE )
   {
      _elementClass = ROOT;
   }
   else if( value == BATCH_VALUE )
   {
      _elementClass = BATCH;
   }
   else if( value == PROCESS_VALUE )
   {
      _elementClass = PROCESS;
   }
   else if( value == CBO_VALUE )
   {
      _elementClass = CBO;
   }
   else if( value == PARM_VALUE )
   {
      _elementClass = PARM;
   }
   else if( value == KEY_VALUE )
   {
      _elementClass = KEY;
   }
   else if( value == FIELD_VALUE )
   {
      _elementClass = FIELD;
   }
   else if( value == NULL_STRING )
   {
      _elementClass = _defaultValue;
//      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED );
   }
   else
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("VALUE"), value );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_ELEMENT_CLASS_ATTRIBUTE, strIDI );
   }
}

//******************************************************************************
ElementAttribute *ClassAttribute::clone() const
{
   return(new ClassAttribute(*this));
}

//******************************************************************************
const DString &ClassAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &ClassAttribute::getValue() const
{
   switch( _elementClass )
   {
      
      case ROOT:
         return(ROOT_VALUE);

      case BATCH:
         return(BATCH_VALUE);

      case PROCESS:
         return(PROCESS_VALUE);

      case CBO:
         return(CBO_VALUE);

      case PARM:
         return(PARM_VALUE);

      case KEY:
         return(KEY_VALUE);

      case FIELD:
         return(FIELD_VALUE);

      default:
         assert(0); // internally inconsistant
         return(FIELD_VALUE);

   }
}

//******************************************************************************
bool ClassAttribute::hasDefaultValue() const
{
   return(_elementClass == _defaultValue);
}
