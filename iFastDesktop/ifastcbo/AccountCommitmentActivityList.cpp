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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountCommitmentActivityList.cpp
//
// ^CLASS    : AccountCommitmentActivityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountcommitmentactivitylist.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0433_vw.hpp>
#include <ifastdataimpl\dse_dstc0433_req.hpp>

#include <bfutil\bfdate.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_INQUIRY;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountCommitmentActivityList" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::AcctCommitMstrUUID,        BFCBO::READ_ONLY,      0}, 
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
// Constructors
//******************************************************************************

AccountCommitmentActivityList::AccountCommitmentActivityList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

}

//******************************************************************************

AccountCommitmentActivityList::~AccountCommitmentActivityList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentActivityList.cpp-arc  $
// 
//    Rev 1.1   Feb 27 2012 15:33:52   if991250
// NASU, Commitment Id
// 
//    Rev 1.0   Feb 17 2012 10:22:28   if991250
// Initial revision.
 * 
 *
 */