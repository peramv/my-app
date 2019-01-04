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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FeeModelSetupList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FeeModelSetupList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeModelSetuplist.hpp"
#include <ifastdataimpl\dse_dstc0449_req.hpp>
#include <ifastdataimpl\dse_dstc0449_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeModelSetupList" );  
   const I_CHAR * IDISCALE = I_( "SCALE" );

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_MODEL_SETUP;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FeeModelSetupList::FeeModelSetupList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*********************************************************************************
FeeModelSetupList::~FeeModelSetupList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeModelSetupList:: init(const DString& dstrTrack, const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( DString&" ) );

	DString mgmtCoIdOut;
	BFData requestData(ifds::DSTC0449_REQ);  
	requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
	BFData* responseData = new BFData(ifds::DSTC0449_VW);
	ReceiveData(DSTC_REQUEST::FEE_MODEL_SETUP, requestData, ifds::DSTC0449_VW, DSTCRequestor( getSecurity(),true) );
		
	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
void FeeModelSetupList::getFeeModelSetup(BFAbstractCBO* &pFeeModelSetup, DString& dstrFeeModelType)
{
   DString currFeeModelType;
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::FeeModelType, currFeeModelType, BF::HOST, false );
		if(dstrFeeModelType == currFeeModelType.stripAll())
         pFeeModelSetup = iter.getObject();
      ++iter;
   }
}

//***********************************************************************************
void FeeModelSetupList::getAvailableFeeModelTypes(DString& dstrAvailableFeeModelTypes)
{
   dstrAvailableFeeModelTypes = I_("");
   boolean first = true;

   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrFeeModelType;
      iter.getObject()->getField( ifds::FeeModelType, dstrFeeModelType, BF::HOST, false );
		if(dstrFeeModelType != I_(""))
      {
         if(!first)
         {
            dstrAvailableFeeModelTypes += I_(",");
         }
         else
         {
            first = false;
         }
         dstrAvailableFeeModelTypes += dstrFeeModelType;

      }
      ++iter;
   }
}
////**********************************************************************************
//SEVERITY FeeModelSetupList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
//{
//   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject") );
//   pObjOut =  new FeeModelSetup( *this );
//   ((FeeModelSetup*) pObjOut)->init( data, bDefault_);
//	return(GETCURRENTHIGHESTSEVERITY());
//}


