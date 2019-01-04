/**
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by International Financial
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2002 by International Financial Data Services Ltd.
 *
*******************************************************************************/
#include "stdafx.h"
#include "TraceFilenameAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("TraceFilenameAttribute");
   const DString TAG_NAME         = I_( "traceFilename" );
}

namespace CND
{
}

//******************************************************************************
TraceFilenameAttribute::TraceFilenameAttribute()
{
}


//******************************************************************************
TraceFilenameAttribute::TraceFilenameAttribute( xercesc::AttributeList &attributes )
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value != NULL_STRING )
   {
      _traceFilename = value.stripAll().upperCase();
   }
}

//******************************************************************************
ElementAttribute *TraceFilenameAttribute::clone() const
{
   return(new TraceFilenameAttribute(*this));
}

//******************************************************************************
const DString &TraceFilenameAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &TraceFilenameAttribute::getValue() const
{
   return(_traceFilename);
}

//******************************************************************************
void TraceFilenameAttribute::setValue( const DString& traceFilename )
{
   _traceFilename = traceFilename;
}

//******************************************************************************
bool TraceFilenameAttribute::hasDefaultValue() const
{
   return(_traceFilename == NULL_STRING);
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/xparser/TraceFilenameAttribute.cpp-arc  $
//
//   Rev 1.2   Mar 09 2004 11:01:36   PURDYECH
//PET910 - Xerces2 support.
// 
//    Rev 1.1   Oct 09 2002 17:43:24   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Sep 19 2002 15:23:54   IVESPAUL
// Initial revision.
//
