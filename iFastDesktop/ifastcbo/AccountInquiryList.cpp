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
// ^FILE   : AccountInquiryList.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 16/03/2001
//
// ^CLASS    : AccountInquiryList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "accountinquirylist.hpp"
#include <bfdata\bfdata.hpp>
#include <ifastdataimpl\dse_dstc0118_vw.hpp>
#include <ifastdataimpl\dse_dstc0118_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_INQUIRY;
}


namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AccountInquiryList" );
}

//******************************************************************************
AccountInquiryList::AccountInquiryList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
AccountInquiryList::~AccountInquiryList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountInquiryList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY AccountInquiryList::init( const DString& dstrBrokerCode, 
                                   const DString& dstrBranchCode, 
                                   const DString& dstrSalesRepCode,
                                   const DString& dstrAccountNum, 
                                   const DString& dstrSIN, 
                                   const DString& dstrShrNum,
                                   const DString& dstrAltAccount, 
                                   const DString& dstrLastName, 
                                   const DString& dstrFirstName,
                                   const DString& dstrCorpIndiv, 
                                   const DString& dstrInTrustJoint, 
                                   const DString& dstrIntermCode,
                                   const DString& dstrIntermAcct,
                                   const DString& dstrNextOrPrevious,
                                   const DString& dstrNextKey,
                                   const DString& dstrTrack,
                                   const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData( ifds::DSTC0118_REQ );

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::BrokerCode, dstrBrokerCode ); 
   queryData.setElementValue( ifds::BranchCode, dstrBranchCode ); 
   queryData.setElementValue( ifds::SalesRepCode, dstrSalesRepCode ); 
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum ); 
   queryData.setElementValue( ifds::SIN, dstrSIN );
   queryData.setElementValue( ifds::ShrNum, dstrShrNum );
   queryData.setElementValue( ifds::AltAccount, dstrAltAccount );
   queryData.setElementValue( ifds::LastName, dstrLastName );
   queryData.setElementValue( ifds::FirstName, dstrFirstName );
   queryData.setElementValue( ifds::CorpIndiv, dstrCorpIndiv );
   queryData.setElementValue( ifds::InTrustJoint, dstrInTrustJoint );
   queryData.setElementValue( ifds::NextOrPrevious, dstrNextOrPrevious );
   queryData.setElementValue( ifds::NextKey, dstrNextKey );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );   
   queryData.setElementValue( ifds::IntermCode, dstrIntermCode );   
   queryData.setElementValue( ifds::InterAccount, dstrIntermAcct );   

   ReceiveData( DSTC_REQUEST::ACCOUNT_INQUIRY, queryData, ifds::DSTC0118_VW, DSTCRequestor(getSecurity(), false, true ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   D:/scc/ifds/ifast/archives/ifastcbo/AccountInquiryList.cpp-arc  $
// 
//    Rev 1.6   Oct 09 2002 23:53:52   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:54:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:26:12   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   Nov 12 2001 14:51:52   VASILEAD
// Added search by iterm info
// 
//    Rev 1.2   03 May 2001 14:05:52   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   Mar 18 2001 18:18:12   VASILEAD
// Fixes for UAT release
 * 
 *    Rev 1.9   Dec 12 1999 16:25:58   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/