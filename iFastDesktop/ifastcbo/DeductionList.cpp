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
// ^FILE   : DeductionList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : DeductionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "deductionlist.hpp"
#include "deductiondetails.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "DeductionList" );
}

//
// Constructors
//
// ----------------------------------------------------------
//
// ^METHOD      : DeductionList::DeductionList
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
DeductionList::DeductionList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

// ----------------------------------------------------------
//
// ^METHOD      : DeductionList::~DeductionList
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
DeductionList::~DeductionList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


// ----------------------------------------------------------
//
// ^METHOD      : DeductionList::init
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

// ----------------------------------------------------------
//
// ^METHOD      : DeductionList::init
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ Data& InstData - assumes that the request is already set
//
// ^RETURNS     : SEVERITY -
//
// ^THROWS      : N/A
//
// ^EXAMPLE     : N/A
//
SEVERITY DeductionList::init( BFData& InstData, DString& currency )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _currency=currency;

   createObjectForEachRepeat( InstData );

   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY DeductionList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new DeductionDetails( *this );
   ((DeductionDetails*)pObjOut)->init( const_cast<BFData&>(data), _currency );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DeductionList.cpp-arc  $
 * 
 *    Rev 1.7   Nov 14 2004 14:30:22   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Oct 09 2002 23:54:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:55:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:26:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   03 May 2001 14:06:08   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Feb 16 2001 14:07:40   DINACORN
 * Add Revision Control Entries
 * 
 */