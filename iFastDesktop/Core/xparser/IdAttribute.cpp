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
#include "IdAttribute.hpp"
#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("IdAttribute");
   const DString TAG_NAME         = I_( "id" );
}

//******************************************************************************
IdAttribute::IdAttribute( xercesc::AttributeList &attributes )
: _id( valueOf( TAG_NAME, attributes ) )
{
}

IdAttribute::IdAttribute( const DString &id )
: _id(id)
{
}

//******************************************************************************
ElementAttribute *IdAttribute::clone() const
{
   return(new IdAttribute(*this));
}

//******************************************************************************
const DString &IdAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &IdAttribute::getValue() const
{
   return(_id);
}

//******************************************************************************
bool IdAttribute::hasDefaultValue() const
{
   return(false);
}
