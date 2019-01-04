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
// ^FILE   : TaxRatesList.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/13/99
//
// ^CLASS    : TaxRatesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0112_vw.hpp>
#include <ifastdataimpl\dse_dstc0112_req.hpp>
#include "taxrates.hpp"
#include "taxrateslist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TAXRATES;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "TaxRatesList" );
}

//******************************************************************************
TaxRatesList::TaxRatesList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), 
_requestData( ifds::DSTC0112_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************
TaxRatesList::~TaxRatesList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TaxRatesList::init( const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData(DSTC_REQUEST::TAXRATES, _requestData, ifds::DSTC0112_VW, DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TaxRatesList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      return(ReceiveData(DSTC_REQUEST::TAXRATES, _requestData, ifds::DSTC0112_VW, DSTCRequestor( getSecurity(), false ) ));
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY TaxRatesList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new TaxRates( *this );
   ((TaxRates*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxRatesList.cpp-arc  $
 * 
 *    Rev 1.12   Nov 14 2004 14:57:06   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:26:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:55:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:30:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:07:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Feb 14 2001 10:21:46   HSUCHIN
 * async request and code cleanup
 * 
 *    Rev 1.5   Jan 18 2001 16:09:58   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:24:36   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 14:47:52   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Dec 04 2000 15:06:48   OLTEANCR
 * added "doCreateObject(..)"; new data brokering
 * 
 *    Rev 1.1   Mar 22 2000 09:02:48   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.0   Dec 29 1999 17:26:16   PETOLESC
// Initial revision.
 * 
 *
 */