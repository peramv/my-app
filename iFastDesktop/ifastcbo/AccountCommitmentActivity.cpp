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
// ^FILE   : AccountCommitmentActivity.cpp
//
// ^CLASS    : AccountCommitmentActivity
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AccountCommitmentActivity.hpp"
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
   const I_CHAR * const CLASSNAME = I_( "AccountCommitmentActivity" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::AcctCommitMstrUUID,        BFCBO::READ_ONLY,      0}, 
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
// Constructors
//******************************************************************************

AccountCommitmentActivity::AccountCommitmentActivity( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

}

//******************************************************************************

AccountCommitmentActivity::~AccountCommitmentActivity( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

SEVERITY AccountCommitmentActivity::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   clearUpdatedFlags( BF::HOST );

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentActivity.cpp-arc  $
// 
//    Rev 1.1   Feb 22 2012 16:56:22   if991250
// Account Commitment
// 
//    Rev 1.0   Feb 17 2012 10:22:12   if991250
// Initial revision.
 *
 */