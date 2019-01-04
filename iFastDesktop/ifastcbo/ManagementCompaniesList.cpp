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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ManagementCompaniesList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/03/99
//
// ^CLASS    : ManagementCompaniesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "managementcompanieslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME    = I_( "ManagementCompaniesList" );
}

//
// Constructors
//
// ----------------------------------------------------------
//
// ^METHOD      : ManagementCompaniesList::ManagementCompaniesList
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : N/A
//
// ^EXAMPLE     : N/A
//
ManagementCompaniesList::ManagementCompaniesList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _signonData( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

// ----------------------------------------------------------
//
// ^METHOD      : ManagementCompaniesList::~ManagementCompaniesList
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ void -
//
// ^RETURNS     : none
//
// ^THROWS      : N/A
//
// ^EXAMPLE     : N/A
//
ManagementCompaniesList::~ManagementCompaniesList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete _signonData;
}


// ----------------------------------------------------------
//
// ^METHOD      : ManagementCompaniesList::init
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : SEVERITY -
//
// ^THROWS      : N/A
//
// ^EXAMPLE     : N/A
//
SEVERITY ManagementCompaniesList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "init(  )" ) );

   //a copy of the signon data is needed to create the list of the management companies
   //the pointer to the data object is allocated when the copy is made
   //the pointer of the signon data will be deleted when the list is destroyed
   getSecurity()->copySignonData( _signonData );
   createObjectForEachRepeat( *_signonData );
   return( GETCURRENTHIGHESTSEVERITY() );
}

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManagementCompaniesList.cpp-arc  $
 * 
 *    Rev 1.6   Nov 14 2004 14:49:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.5   Oct 09 2002 23:54:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:56:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:28:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   03 May 2001 14:06:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Dec 17 2000 20:24:02   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 11:00:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Jan 05 2000 20:10:58   BUZILA
 * adding list flag
 * 
 *    Rev 1.3   Jul 20 1999 11:17:18   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 08 1999 13:31:02   YINGZ
 * add #include "data.hpp"
 * to avoid imcomplete deletion warning which could cause problem
 * 
 */
