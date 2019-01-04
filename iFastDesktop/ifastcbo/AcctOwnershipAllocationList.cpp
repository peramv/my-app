//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : AcctOwnershipAllocationList.cpp
// ^AUTHOR : 
// ^DATE   : Jul, 2012
//
// ^CLASS    : AcctOwnershipAllocationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0444_vw.hpp>
#include <ifastdataimpl\dse_dstc0444_req.hpp>
#include <ifastdataimpl\dse_dstc0444_vwrepeat_record.hpp>

#include "AcctOwnershipAllocation.hpp"
#include "AcctOwnershipAllocationList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_OWNERSHIP_ALLOCATION_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "AcctOwnershipAllocationList" );
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
AcctOwnershipAllocationList::AcctOwnershipAllocationList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, requestData444(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
AcctOwnershipAllocationList::~AcctOwnershipAllocationList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( requestData444 != NULL )
   {
      delete requestData444;
      requestData444 = NULL;
   }
}

//********************************************************************************
SEVERITY AcctOwnershipAllocationList::init(const DString& acctNum,
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   requestData444 = new BFData(ifds::DSTC0444_REQ);

   requestData444->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData444->setElementValue (ifds::AccountNum,acctNum);

   BFData* responseData = new BFData (ifds::DSTC0444_VW);
   ReceiveData( DSTC_REQUEST::ACCT_OWNERSHIP_ALLOCATION_INQUIRY,
                *requestData444, 
                *responseData, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctOwnershipAllocationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new AcctOwnershipAllocation( *this );
   ((AcctOwnershipAllocation*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctOwnershipAllocationList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::ACCT_OWNERSHIP_ALLOCATION_INQUIRY, 
                  *requestData444, 
                  ifds::DSTC0444_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctOwnershipAllocationList.cpp-arc  $
// 
//    Rev 1.0   Jul 24 2012 19:00:12   dchatcha
// Initial revision.
// 

