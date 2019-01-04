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
// ^FILE   : AccountCommitmentDetailsList.cpp
//
// ^CLASS    : AccountCommitmentDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountcommitmentdetailslist.hpp"
#include "accountcommitmentdetails.hpp"
#include "accountcommitmentactivitylist.hpp"
#include "accountcommitmentactivity.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0433_vw.hpp>
#include <ifastdataimpl\dse_dstc0433_req.hpp>

#include <bfutil\bfdate.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_INQUIRY;
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_DETAIL_ACTIVITY_INQUIRY;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountCommitmentDetailsList" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::AcctCommitMstrUUID,        BFCBO::READ_ONLY,      0}, 
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
// Constructors
//******************************************************************************

AccountCommitmentDetailsList::AccountCommitmentDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

}

//******************************************************************************

AccountCommitmentDetailsList::~AccountCommitmentDetailsList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountCommitmentDetailsList::init(const DString& dstrAcctCommitMstrUUID)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

   //this->dstrAcctNum. = dstrAcctNum;

	BFData requestData (ifds::DSTC0433_REQ);
   DString mgmtCoIdOut;	
	requestData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   requestData.setElementValue (ifds::AcctCommitMstrUUID, dstrAcctCommitMstrUUID);
	
	ReceiveData (DSTC_REQUEST::ACCT_COMMIT_DETAIL_ACTIVITY_INQUIRY, requestData, ifds::DSTC0433_VW, DSTCRequestor (getSecurity(), true));



   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountCommitmentDetailsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,CLASSNAME, I_( "doCreateObject( const BFData &, BFCBO *& )" ) );
   DString dstrRecType = data.getElementValue(ifds::RecType);
   dstrRecType.strip();

   if(I_("S") == dstrRecType)
   {
      pObjOut = new AccountCommitmentDetails( *this );
      ((AccountCommitmentDetails*) pObjOut)->init( data );
   }
   else if (I_("D") == dstrRecType)
   {
      pObjOut = NULL;
      DString dstAcctCommitDetlUUID = data.getElementValue(ifds::AcctCommitDetlUUID);
      dstAcctCommitDetlUUID.strip();

      AccountCommitmentDetails* pAccountCommitmentDetails = (AccountCommitmentDetails*)getObject(dstAcctCommitDetlUUID, BF::HOST);
      if(pAccountCommitmentDetails != NULL)
      {
         AccountCommitmentActivityList* pAccountCommitmentActivityList = NULL;
         pAccountCommitmentDetails->getAccountCommitmentActivityList(pAccountCommitmentActivityList);
         if(pAccountCommitmentDetails != NULL)
         {
            AccountCommitmentActivity* pAccountCommitmentActivity = new AccountCommitmentActivity( *this );
            pAccountCommitmentActivity->init( data );
            DString strAcctCommitActivityUUID = data.getElementValue(ifds::AcctCommitActivityUUID);
            if(strAcctCommitActivityUUID != NULL_STRING)
               strAcctCommitActivityUUID.strip();

            pAccountCommitmentActivityList->setObject(strAcctCommitActivityUUID, pAccountCommitmentActivity);
         }
      }
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

void AccountCommitmentDetailsList::getStrKey( DString &strKey, const BFData *data)
{
   strKey = data->getElementValue(ifds::AcctCommitDetlUUID);
   if(NULL_STRING != strKey)
      strKey.strip();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentDetailsList.cpp-arc  $
// 
//    Rev 1.2   Feb 27 2012 15:34:02   if991250
// NASU, Commitment Id
// 
//    Rev 1.1   Feb 22 2012 16:57:32   if991250
// Account Commitment
// 
//    Rev 1.0   Feb 17 2012 10:22:54   if991250
// Initial revision.
// 
//    Rev 1.0   Feb 14 2012 13:26:12   if991250
// Initial revision.
 * 
 *
 */