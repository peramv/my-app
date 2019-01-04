//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : InterProcessData.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 2/10/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InterProcessData
//    This class manages inter process parameters and "globals".
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "interprocessdata.hpp"
#include <idistring.hpp>

#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "InterProcessData" );

   const I_CHAR * const CLEARGLOBALS = I_( "clearGlobals" );
   const I_CHAR * const CLEARPARAMETERS = I_( "clearParameters" );
   const I_CHAR * const GETGLOBAL = I_( "getGlobal" );
   const I_CHAR * const GETPARAMETER = I_( "getParameter" );
   const I_CHAR * const SETPARAMETER = I_( "setParameter" );
   const I_CHAR * const SETGLOBAL = I_( "setGlobal" );

   // Literals
   const I_CHAR * const FIELD = I_( "FIELD" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_SETFIELD_FAILED;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

InterProcessData::InterProcessData()
{
}

//******************************************************************************
void InterProcessData::clearParameters()
{
   TRACE_METHOD( CLASSNAME, CLEARPARAMETERS );

   mapParms_.erase( mapParms_.begin(), mapParms_.end() );
}

//******************************************************************************

void InterProcessData::getParameter( const DString &strTag, DString &strValueOut ) const
{
   ParmMap::const_iterator itParms = mapParms_.find( strTag );
   if( itParms != mapParms_.end() )
   {
      strValueOut = (*itParms).second;
      return;
   }
   else
   {
      strValueOut = NULL_STRING;
   }
   return;
}

//******************************************************************************
void InterProcessData::setParameter( const DString &strTag, const DString &strValue )
{  // Set, allowing append

   DString t( strValue );
   t.stripTrailing();
   mapParms_[ strTag ] = t;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/InterProcessData.cpp-arc  $
//
//   Rev 1.9   May 14 2004 16:13:22   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.8   May 10 2004 15:08:56   SMITHDAV
//Move work-session level "global data" to the BFWorksession from InterProcessData.
 * 
 *    Rev 1.7   Jan 06 2003 16:44:00   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 17:40:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Aug 29 2002 14:05:24   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.4   Aug 29 2002 12:51:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   Jun 17 2002 11:36:24   PURDYECH
 * Back parameters with a map'o'DStrings instead of a BFData object.  This ensures that a value which is set in with setParameter will not be transmogrified by formatting during the setElementValue/getElementValue logic.
 * 
 *    Rev 1.2   Jun 06 2002 17:18:32   PURDYECH
 * Use the .reset method of BFData to reset the parameters
 * 
 *    Rev 1.1   Mar 08 2000 11:37:40   DT24433
 * let creator determine datasets to use
 * 
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Nov 10 1999 11:47:12   DT24433
 * split USER & WORK globals
 * 
 *    Rev 1.4   Jul 20 1999 11:14:08   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 09 1999 16:04:56   HSUCHIN
 * fixed log
 * 
 *    Rev 1.2   Jul 09 1999 15:33:36   VASILEAD
 * Bug fixes
*/ 
