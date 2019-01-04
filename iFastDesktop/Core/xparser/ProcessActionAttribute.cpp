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
#include "ProcessActionAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{

   const I_CHAR * const CLASSNAME  = I_("ProcessActionAttribute");

   const DString TAG_NAME         = I_( "action" );

   const DString VALIDATE_ONLY_VALUE = I_( "validateOnly" );
   const DString SUBMIT_VALUE        = I_( "submit" );

   const ProcessAction PROC_ACTION_DEFAULT = PROC_ACTION_SUBMIT;
}

namespace CND
{
   extern const long ERR_INVALID_PROCESS_ACTION_ATTRIBUTE;
}

//******************************************************************************
ProcessActionAttribute::ProcessActionAttribute( xercesc::AttributeList &attributes )
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value == VALIDATE_ONLY_VALUE )
      _action = PROC_ACTION_VALIDATE_ONLY;

   else if( value == SUBMIT_VALUE )
      _action = PROC_ACTION_SUBMIT;

   else if( value == NULL_STRING )
      _action = PROC_ACTION_DEFAULT;

   else
   {
      DString strIDI;
      addIDITagValue( strIDI, I_("VALUE"), value );

      THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_PROCESS_ACTION_ATTRIBUTE, strIDI );
   }

}

ProcessActionAttribute::ProcessActionAttribute( ProcessAction action )
: _action(action)
{
}

//******************************************************************************
ElementAttribute *ProcessActionAttribute::clone() const
{
   return(new ProcessActionAttribute(*this));
}

//******************************************************************************
const DString &ProcessActionAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &ProcessActionAttribute::getValue() const
{
   switch( _action )
   {
      
      case PROC_ACTION_VALIDATE_ONLY:
         return(VALIDATE_ONLY_VALUE);

      case PROC_ACTION_SUBMIT:
         return(SUBMIT_VALUE);

      default:
         assert(0); // internally inconsistant
         return(SUBMIT_VALUE);

   }
}

//******************************************************************************
bool ProcessActionAttribute::hasDefaultValue() const
{
   return(_action == PROC_ACTION_DEFAULT);
}
