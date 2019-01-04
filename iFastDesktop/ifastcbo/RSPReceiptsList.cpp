//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : RSPReceiptList.cpp
// ^AUTHOR : 
// ^DATE   : 01/08/2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RSPReceiptList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0174_req.hpp>
#include <ifastdataimpl\dse_dstc0174_vw.hpp>
#include "mgmtco.hpp"
#include "rspreceipts.hpp"
#include "rspreceiptslist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RSP_RECEIPT_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RSPReceiptsList" );
}

//******************************************************************************
// Constructor
//******************************************************************************
RSPReceiptsList::RSPReceiptsList( BFAbstractCBO &parent ) :
MFCanBFCbo( parent ),
_requestData(ifds::DSTC0174_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
RSPReceiptsList::~RSPReceiptsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Initialization of the request object and makes a View call 174.  The request
// data object is kept for potential later use of retrieve more RSPReceipts.
// @param   const DString& dstrAccountNum - Account Number (Required)
// @param   const DString& dstrTaxYear - Tax Year (Required)
// @param   const DString& dstrTrack - Track value (Not required)
// @param   const DString& dstrPageName - Page Name (Not required)
//******************************************************************************
SEVERITY RSPReceiptsList::init( const DString& dstrAccountNum,
                                const DString& dstrTaxYear,
                                const DString& dstrTrack,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;   
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::TaxYear, dstrTaxYear );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   ReceiveData(DSTC_REQUEST::RSP_RECEIPT_LIST, _requestData, ifds::DSTC0174_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// Creates a RSPReceipts CBO based on the data from the view transaction.
// Returns the RSPReceipts CBO to be added to the RSPReceiptsList
// @param   const Data& data - Data from view call 173.
// @param   BFBase *&pObjOut - BFBase pointer to RSPReceipts CBO
//********************************************************************************
SEVERITY RSPReceiptsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new RSPReceipts ( *this );
   dynamic_cast< RSPReceipts * >( pObjOut )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Method to retrieve more data for the current RSPReceipts List.  _requestData
// should contain the nextKey for the next set of data.
//******************************************************************************
SEVERITY RSPReceiptsList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::RSP_RECEIPT_LIST, _requestData, ifds::DSTC0174_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPReceiptsList.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:53:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Oct 09 2002 23:54:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:56:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:29:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   20 Aug 2001 14:07:54   HSUCHIN
// added comments
// 
//    Rev 1.1   18 Aug 2001 09:26:04   HSUCHIN
// implemented get More
// 
//    Rev 1.0   01 Aug 2001 14:28:26   HSUCHIN
// Initial revision.
*/

