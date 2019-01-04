//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : ConfirmationList.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Nov 21, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ConfirmationList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "confirmationlist.hpp"
#include "confirmation.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ConfirmationList" );
}

ConfirmationList::ConfirmationList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

ConfirmationList::~ConfirmationList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

SEVERITY ConfirmationList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY ConfirmationList::doCreateNewObject( BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new Confirmation( *this );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY ConfirmationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new Confirmation( *this );
   ( ( Confirmation* ) ( pObjOut ) )->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ConfirmationList.cpp-arc  $
 * 
 *    Rev 1.7   Nov 14 2004 14:29:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Mar 21 2003 18:01:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:55:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:26:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   03 May 2001 14:06:06   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Dec 17 2000 20:22:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Dec 12 1999 16:25:14   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/