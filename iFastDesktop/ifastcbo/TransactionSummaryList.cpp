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
// ^FILE   : TransactionSummaryList.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 11/03/2001
//
// ^CLASS    : TransactionSummaryList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "transactionsummarylist.hpp"
#include <ifastdataimpl\dse_dstc0117_vw.hpp>
#include <ifastdataimpl\dse_dstc0117_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_SUMMARY;
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_NUMBER;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "TransactionSummaryList" );
}

//******************************************************************************
TransactionSummaryList::TransactionSummaryList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _queryData(ifds::DSTC0117_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
TransactionSummaryList::~TransactionSummaryList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TransactionSummaryList::init( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY TransactionSummaryList::init( DString& AccountNum, const DString& Baycom,
                                       const DString& FromDate, const DString& ToDate,
                                       const DString& NextOrPrevious, const DString& SortOrder,
                                       const DString& FundCode, const DString& NextKey,
                                       const DString& dstrTrack,const DString& dstrPageName
                                     )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString mgmtCoIdOut;
   _queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );      
   _queryData.setElementValue( ifds::AccountNum, AccountNum ); 
   _queryData.setElementValue( ifds::FromDate, FromDate );
   _queryData.setElementValue( ifds::ToDate, ToDate );
   _queryData.setElementValue( ifds::NextOrPrevious, NextOrPrevious );
   _queryData.setElementValue( ifds::SortOrder, SortOrder );
   if( FundCode != NULL_STRING )
      _queryData.setElementValue( ifds::SrchFundCode, FundCode );
   _queryData.setElementValue( ifds::NextKey, NextKey );
   _queryData.setElementValue( ifds::Track, dstrTrack );
   _queryData.setElementValue( ifds::Activity, dstrPageName );
   _queryData.setElementValue( ifds::Baycom, Baycom );

   ReceiveData( DSTC_REQUEST::TRANSACTION_SUMMARY, _queryData, ifds::DSTC0117_VW, DSTCRequestor(getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionSummaryList.cpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:58:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 21 2003 18:27:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:55:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:56:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:30:10   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   Apr 26 2002 10:41:40   FENGYONG
// Add Baycom as a request field
// 
//    Rev 1.4   Sep 21 2001 10:34:50   VASILEAD
// Modified a field name FundCode to SrchFundCode
// 
//    Rev 1.3   11 May 2001 13:01:16   HSUCHIN
// Session management restructuring
// 
//    Rev 1.2   Apr 27 2001 13:44:50   VASILEAD
// Added FundCode
// 
//    Rev 1.1   Mar 18 2001 18:18:14   VASILEAD
// Fixes for UAT release
 * 
 *    Rev 1.9   Dec 12 1999 16:25:58   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/