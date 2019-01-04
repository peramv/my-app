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
#include "SeverityAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("SeverityAttribute");

   const DString TAG_NAME      = I_( "severity" );

   const DString NO_SEVERITY_VALUE    = I_("noSeverity");
   const DString NO_CONDITION_VALUE   = I_("noCondition");
   const DString TRACE_ONLY_VALUE     = I_("traceOnly");
   const DString INFORMATION_VALUE    = I_("information");
   const DString WARNING_VALUE        = I_("warning");
   const DString SEVERE_ERROR_VALUE   = I_("severeError");
   const DString CRITICAL_ERROR_VALUE = I_("criticalError");
}

SeverityAttribute::SeverityAttribute( SEVERITY severity )
: _severity(severity)
{
}

//******************************************************************************
ElementAttribute *SeverityAttribute::clone() const
{
   return(new SeverityAttribute(*this));
}

//******************************************************************************
const DString &SeverityAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &SeverityAttribute::getValue() const
{
   switch( _severity )
   {
      
      case NO_SEVERITY:
         return(NO_SEVERITY_VALUE);

      case NO_CONDITION:
         return(NO_CONDITION_VALUE);

      case TRACE_ONLY:
         return(TRACE_ONLY_VALUE);

      case INFORMATIONAL:
         return(INFORMATION_VALUE);

      case WARNING:
         return(WARNING_VALUE);

      case SEVERE_ERROR:
         return(SEVERE_ERROR_VALUE);

      case CRITICAL_ERROR:
         return(CRITICAL_ERROR_VALUE);

      default:
         assert(0); // internally inconsistant
         return(NO_CONDITION_VALUE);

   }
}

//******************************************************************************
bool SeverityAttribute::hasDefaultValue() const
{
   return(false);
}
