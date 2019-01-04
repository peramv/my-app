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
// ^FILE   : AggregatedOrderList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : AggregatedOrderList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AggregatedOrder.hpp"
#include "AggregatedOrderlist.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0323_vw.hpp>
#include <ifastdataimpl\dse_dstc0323_req.hpp>

#include <bfutil\bfdate.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AGGREGATED_ORDER_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AggregatedOrderList" );
	const I_CHAR * const YES										= I_( "Y" );
	const I_CHAR * const NO											= I_( "N" );
}

namespace TRID
{
   extern const I_CHAR* AggregatedOrder;

}

namespace CND
{ // Conditions used 
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId Recalculate;
}

//******************************************************************************
void AggregatedOrderList::buildKey ( const DString &omnibusID,
                                     DString &strKey)
{
   DString _omnibusID (omnibusID);

   _omnibusID.strip().stripLeading ('0');
   strKey = I_("OmnibusID=") + _omnibusID;
}

//******************************************************************************
// Constructors
//******************************************************************************

AggregatedOrderList::AggregatedOrderList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();   
}


//******************************************************************************
AggregatedOrderList::~AggregatedOrderList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
    if (_pRequestData)
      delete _pRequestData;
}

//******************************************************************************
SEVERITY AggregatedOrderList::init( const DString& dstrFromDate, 
                                    const DString& dstrToDate,
                                    const DString& dstrStatus,
                                    const DString& dstrBrokerCode,
                                    const DString& dstrFundCode,
                                    const DString& dstrAggrOrderNum,
                                    const DString& dstrRoutingRefNum,
                                    const DString& dstrSearchType,
                                    /*const BFDataGroupId& idDataGroup,*/
                                    const DString& dstrTrack,
                                    const DString& dstrPageName, 
                                    const DString& dstrFundBrkKvNum ,
                                    const DString& dstrFundIDType,
                                    const DString& dstrFundIDValue,
                                    const DString& dstrAmountType,
                                    const DString& dstrAmount,
                                    const DString& dstrTransType)                              
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   
   DString mgmtCoIdOut;
	_pResponseData = new BFData(ifds::DSTC0323_VW);
	_pRequestData = new BFData(ifds::DSTC0323_REQ);
	_pRequestData->setElementValue( ifds::FromDate, dstrFromDate );
	_pRequestData->setElementValue( ifds::ToDate, dstrToDate );
	_pRequestData->setElementValue( ifds::rxOrdStatus, dstrStatus );
	_pRequestData->setElementValue( ifds::FundBroker, dstrBrokerCode );
	_pRequestData->setElementValue( ifds::FundCode, dstrFundCode );
	_pRequestData->setElementValue( ifds::OmnibusID, dstrAggrOrderNum );
	_pRequestData->setElementValue( ifds::RoutingRef, dstrRoutingRefNum );
	_pRequestData->setElementValue( ifds::SearchType, dstrSearchType );
	_pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );       
	_pRequestData->setElementValue( ifds::Track, dstrTrack );
	_pRequestData->setElementValue( ifds::Activity, dstrPageName );
	_pRequestData->setElementValue( ifds::FundBrkKVNum, dstrFundBrkKvNum );
	_pRequestData->setElementValue( ifds::FundIDType, dstrFundIDType );
	_pRequestData->setElementValue( ifds::FundIDValue, dstrFundIDValue );
	_pRequestData->setElementValue( ifds::AmountType, dstrAmountType );
	_pRequestData->setElementValue( ifds::Amount, dstrAmount );
	_pRequestData->setElementValue( ifds::TransType, dstrTransType );
   ReceiveData ( DSTC_REQUEST::AGGREGATED_ORDER_LIST, 
                 *_pRequestData,
                 *_pResponseData, 
                 DSTCRequestor (getSecurity(), false, true ) );
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AggregatedOrderList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   AggregatedOrder *pAggregatedOrder = new AggregatedOrder ( *this );
   pObjOut = pAggregatedOrder;

   pAggregatedOrder->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
void AggregatedOrderList::getStrKey (DString &strKey, const BFData *data /*= NULL*/)
{
   if (data)
   {
      DString omnibusID;

      omnibusID = data->getElementValue (ifds::OmnibusID);
      buildKey (omnibusID, strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey);
   }
}

//*********************************************************************************
bool AggregatedOrderList::allowEnableOk (const BFDataGroupId& idDataGroup)
{
   DString dstrRecalculate;
	bool ret = true;
	BFAbstractCBO *pBFCBO;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      if( pBFCBO )
      {
         pBFCBO->getField(ifds::Recalculate, dstrRecalculate, idDataGroup);
			if	( dstrRecalculate.strip().upperCase() == YES  )
			{			
				ret = false;
				break;
			}
		}
      ++iter;
	}
	return ret;
}
//******************************************************************************
SEVERITY AggregatedOrderList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

  				
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrderList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
	if (doMoreRecordsExist())
   {
		ReceiveData ( DSTC_REQUEST::AGGREGATED_ORDER_LIST, 
                    *_pRequestData, 
                    ifds::DSTC0323_VW, 
                    DSTCRequestor (getSecurity(), false ));
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AggregatedOrderList.cpp-arc  $
// 
//    Rev 1.8   Feb 24 2005 17:25:06   ZHANGCEL
// Magic #246980 -- Synch up from 1.4.1.2
// 
//    Rev 1.7   Feb 10 2005 11:36:44   zhangcel
// PTS 10038581 -- Synch-up from 1.4.1.1
// 
//    Rev 1.6   Jan 28 2005 13:45:02   popescu
// PTS 10038381, synch-up from release 59.0.1
// 
//    Rev 1.5   Jan 26 2005 11:01:28   yingbaol
// PET1117 FN67 enhance Aggregate order for API
// 
//    Rev 1.4   Dec 07 2004 09:56:32   zhangcel
// PET 1117 - FN 08 -- More code pupolated
// 
//    Rev 1.3   Nov 19 2004 15:20:44   zhangcel
// PET 1117 FN 8 -- Bug fix for the aggregated lower case problem
// 
//    Rev 1.2   Nov 19 2004 15:17:20   zhangcel
// PET1117 FN08 -- Bug fix for the Aggregated_order list
// 
//    Rev 1.0   Nov 18 2004 13:57:00   zhangcel
// Initial revision.
 * 
 */