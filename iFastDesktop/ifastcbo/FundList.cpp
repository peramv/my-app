#define IFASTCBO_DLL

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
// ^FILE   : FundList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 25/03/99
//
// ^CLASS    : FundList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundlist.hpp"
#include <ifastcbo\FundPrices.hpp>
#include <ifastdataimpl\dse_dstc0023_req.hpp>
#include <ifastdataimpl\dse_dstc0023_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_INFO;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundList" );
}

//******************************************************************************
FundList::FundList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   requestData =  new BFData(ifds::DSTC0023_REQ); 
}


//******************************************************************************
FundList::~FundList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( requestData )
   {
      delete requestData; requestData = NULL;
   }
}

//******************************************************************************

SEVERITY FundList::init( DString& dstFundCode,
                         DString& dstClassCode,
                         DString& dstFromDate, 
                         DString& dstToDate, 
                         DString& dstPrevDatePressed, 
                         DString& dstNextDatePressed,
                         const DString& dstrTrack,
                         const DString& dstrPageName,
						 const DString& dstGetLastIDRate,
                         const DString& dstrGetTransType,
                         const DString& dstrGetNextAvailRate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString dstNextKey = NULL_STRING;

   DString mgmtCoIdOut;
   requestData->setElementValue( ifds::CompanyId,         getMgmtCoId( mgmtCoIdOut ) );
   requestData->setElementValue( ifds::FundCode,          dstFundCode        ); 
   requestData->setElementValue( ifds::ClassCode,         dstClassCode       );
   requestData->setElementValue( ifds::FromDate,          dstFromDate,       false, false );
   requestData->setElementValue( ifds::ToDate,            dstToDate,         false, false );
   requestData->setElementValue( ifds::PrevDatePressed,   dstPrevDatePressed );
   requestData->setElementValue( ifds::NextDatePressed,   dstNextDatePressed );
   requestData->setElementValue( ifds::NextKey,           dstNextKey         );
   requestData->setElementValue( ifds::Track, dstrTrack );
   requestData->setElementValue( ifds::Activity, dstrPageName );
   requestData->setElementValue( ifds::GetLastIDRate, dstGetLastIDRate );
   requestData->setElementValue( ifds::GetTransType, dstrGetTransType);
   requestData->setElementValue( ifds::GetNextAvailRate, dstrGetNextAvailRate);

   ReceiveData(DSTC_REQUEST::FUND_INFO, *requestData, ifds::DSTC0023_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FundList::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );

   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
      requestData->setElementValue( ifds::NextKey, NULL_STRING ); 

   };

   // Set Search Fund Type
   DString dstrFundCode, dstrFundWKN, dstrFundISIN, dstrCUSIP;
   requestData->getElementValue( ifds::FundCode, dstrFundCode );
   requestData->getElementValue( ifds::FundWKN, dstrFundWKN );
   requestData->getElementValue( ifds::FundISIN, dstrFundISIN );
   requestData->getElementValue( ifds::CUSIP, dstrCUSIP );
   setParameter( I_("SearchFundType"), NULL_STRING );
   if( !dstrFundWKN.strip().empty() )
      setParameter( I_("SearchFundType"), I_("WKN") );
   if( !dstrFundISIN.strip().empty() )
      setParameter( I_("SearchFundType"), I_("ISIN") );
   if( !dstrFundCode.strip().empty() )
      setParameter( I_("SearchFundType"), I_("FUND") );
   if( !dstrCUSIP.strip().empty() )
	  setParameter( I_("SearchFundType"),I_("CUSIP") );

   const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
   ReceiveData(DSTC_REQUEST::FUND_INFO, *requestData, ifds::DSTC0023_VW, DSTCRequestor( getSecurity(), false ) );
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void FundList::setParameter( const DString& elementName, const DString& value )
{
   TRACE_METHOD( CLASSNAME, I_( "setParameter" ) );

   requestData->setElementValue( elementName, value, false, false );
}

//******************************************************************************

SEVERITY FundList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FundPrices *pFundPrices = new FundPrices( *this );
   pBase = pFundPrices;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY FundList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new FundPrices ( *this );
   dynamic_cast< FundPrices * >( pObjOut )->init( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundList.cpp-arc  $
 * 
 *    Rev 1.13   Nov 14 2004 14:42:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Sep 09 2004 11:40:58   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.11   Mar 21 2003 18:11:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:55:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:06:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:04:52   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Jan 12 2001 13:39:00   ZHANGCEL
 * sourse code clean up
 * 
 *    Rev 1.4   Dec 17 2000 20:23:28   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 11:30:52   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Nov 29 2000 14:33:20   VASILEAD
 * Fixed toDate bug
 * 
 *    Rev 1.1   Nov 02 2000 13:23:20   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 05 2000 20:10:48   BUZILA
 * adding list flag
 * 
 *    Rev 1.7   Dec 12 1999 16:25:24   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/