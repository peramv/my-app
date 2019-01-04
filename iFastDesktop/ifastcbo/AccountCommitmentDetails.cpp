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
// ^FILE   : AccountCommitmentDetails.cpp
//
// ^CLASS    : AccountCommitmentDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountcommitmentdetails.hpp"
#include "accountcommitmentactivitylist.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0433_vw.hpp>
#include <ifastdataimpl\dse_dstc0433_req.hpp>

#include <bfutil\bfdate.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_INQUIRY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ExpectedAmt;
   extern CLASS_IMPORT const BFDecimalFieldId BonusPercentage;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountCommitmentDetails" );
   const I_CHAR * const ACCOUNT_COMMITMENT_ACTIVITY_LIST = I_( "AccountCommitmentActivityList" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::AcctCommitMstrUUID,        BFCBO::READ_ONLY,      0}, 
   {ifds::ExpectedAmt,               BFCBO::READ_ONLY,      0}, 
   {ifds::BonusPercentage,           BFCBO::READ_ONLY,      0}, 
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
// Constructors
//******************************************************************************

AccountCommitmentDetails::AccountCommitmentDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

   AccountCommitmentActivityList*  pAccountCommitmentActivityList = new AccountCommitmentActivityList(*this);
   setObject(pAccountCommitmentActivityList, ACCOUNT_COMMITMENT_ACTIVITY_LIST);
}

//******************************************************************************

AccountCommitmentDetails::~AccountCommitmentDetails( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

SEVERITY AccountCommitmentDetails::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   clearUpdatedFlags( BF::HOST );

	return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY AccountCommitmentDetails::getAccountCommitmentActivityList(AccountCommitmentActivityList *&pAccountCommitmentActivityList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountCommitmentActivityList" ) );
   pAccountCommitmentActivityList = dynamic_cast<AccountCommitmentActivityList*>(getObject(ACCOUNT_COMMITMENT_ACTIVITY_LIST, BF::HOST));

	return GETCURRENTHIGHESTSEVERITY();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentDetails.cpp-arc  $
// 
//    Rev 1.2   Mar 08 2012 09:56:12   if991250
// Account Commitment
// 
//    Rev 1.1   Feb 22 2012 16:57:12   if991250
// Account Commitment
// 
//    Rev 1.0   Feb 17 2012 10:22:42   if991250
// Initial revision.
 *
 */