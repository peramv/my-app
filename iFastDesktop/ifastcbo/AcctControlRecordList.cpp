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
//    Copyright 2010 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctControlRecordList.cpp
// ^AUTHOR : 
// ^DATE   : Dec 2010
//
// ^CLASS    : AcctControlRecordList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctControlRecordList.hpp"
#include "AcctControlRecord.hpp"

#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctControlRecordList" );
}

namespace ifds
{
}

namespace CND
{
   extern const long ERR_ACCT_CONTROL_EXISTS;
}

//******************************************************************************
AcctControlRecordList::AcctControlRecordList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, m_requestData( ifds::DSTC0386_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}

//******************************************************************************
AcctControlRecordList::~AcctControlRecordList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctControlRecordList::init( const DString &strAccountNumber,
									  const BFDataGroupId& idDataGroup,
									  const DString &strEffectiveDate,
									  const DString &strStopDate,
									  const DString &strInquiryType,
                                      const DString &strRuleType,
                                      const DString &strFundCode,
                                      const DString &strClassCode,
                                      const DString &strTrack,
                                      const DString &strPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _accountNum = strAccountNumber;

   BFData responseData(ifds::DSTC0386_VW);

   // Set request fields
   //m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, strTrack );
   m_requestData.setElementValue( ifds::Activity, strPageName );
   m_requestData.setElementValue( ifds::AccountNum, strAccountNumber );
   m_requestData.setElementValue( ifds::FundCode, strFundCode );
   m_requestData.setElementValue( ifds::ClassCode, strClassCode );
   m_requestData.setElementValue( ifds::RuleType, strRuleType ); // always 30  
   m_requestData.setElementValue( ifds::InquiryType, strInquiryType );
   m_requestData.setElementValue( ifds::EffectiveDate, strEffectiveDate );
   m_requestData.setElementValue( ifds::StopDate, strStopDate );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData( DSTC_REQUEST::ACCT_CONTROL_INQUIRY, m_requestData, ifds::DSTC0386_VW, DSTCRequestor(getSecurity()) );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctControlRecordList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new AcctControlRecord( *this );
   ((AcctControlRecord*) pObjOut )->init( data );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctControlRecordList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::ACCT_CONTROL_INQUIRY, m_requestData, ifds::DSTC0386_VW, DSTCRequestor(getSecurity()) );
   }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctControlRecordList.cpp-arc  $
// 
//    Rev 1.0   Jan 31 2011 14:08:26   dchatcha
// Initial revision.
// 