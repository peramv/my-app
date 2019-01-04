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
//    Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SegTrxValidationList.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : SegTrxValidationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SegTrxValidation.hpp"
#include "Trade.hpp"
#include "TradeFundAllocList.hpp"
#include "TradeFundAlloc.hpp"

#include <ifastdataimpl\dse_dstc0414_req.hpp>
#include <ifastdataimpl\dse_dstc0414_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0414_vw.hpp>
#include <ifastdataimpl\dse_dstc0414_vwrepeat_record.hpp>

#include "SegTrxValidationList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEG_COT_TRX_VALIDATION_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "SegTrxValidationList" );
}

namespace ifds
{
   
}

namespace CND
{
}

//const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
//{
//   // Field DD Id,                     State Flags,          Group Flags 
//
//};

//static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
SegTrxValidationList::SegTrxValidationList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //registerMemberData( NUM_FIELDS,
   //                    (const CLASS_FIELD_INFO *)&classFieldInfo,
   //                    0,
   //                    NULL );

   setObjectAsList( );
}

//******************************************************************************
SegTrxValidationList::~SegTrxValidationList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY SegTrxValidationList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );


   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SegTrxValidationList::init( const DString& strAccountNum,
									 const DString& strFund,
									 const DString& strClass,
									 const DString& strAccountTo,
									 const DString& strFundTo,
									 const DString& strClassTo,
									 const DString& strTransType,
									 const DString& strRedCode,
									 const DString& strTradeAmount,
									 const DString& strDeff,
									 const DString& strSettleDate,
									 const DString& strPUD,
									 const DString& strTransNum,
									 const BFDataGroupId& idDataGroup,
									 const DString& strTrack,
									 const DString& strPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0414_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, strTrack);
   requestData.setElementValue (ifds::Activity, strPageName);
   requestData.setElementValue (ifds::AccountNum, strAccountNum);
   requestData.setElementValue (ifds::Fund, strFund);
   requestData.setElementValue (ifds::Class, strClass);
   requestData.setElementValue (ifds::AccountTo, strAccountTo);
   requestData.setElementValue (ifds::FundTo, strFundTo);
   requestData.setElementValue (ifds::ClassTo, strClassTo);
   requestData.setElementValue (ifds::TransType, strTransType);
   requestData.setElementValue (ifds::RedCode, strRedCode);
   requestData.setElementValue (ifds::TradeAmount, strTradeAmount);
   requestData.setElementValue (ifds::Deff, strDeff);
   requestData.setElementValue (ifds::SettleDate, strSettleDate);
   requestData.setElementValue (ifds::PUD, strPUD);
   requestData.setElementValue (ifds::TransNum, strTransNum);
   requestData.setElementValue (ifds::RepeatCount, I_("0"));   // default

   DString dstRepeats = I_("0");
   // get trade allocation list
   Trade *pTrade = dynamic_cast < Trade *> (getParent());
   TradeFundAllocList *pFundAllocationList = NULL;

   if ( pTrade->getFundAllocationList (pFundAllocationList, idDataGroup, false) <= WARNING &&
		pFundAllocationList)
   {
      DString dstrAllocFundCode, dstrAllocClassCode,
	          dstrAllocPercentage, dstrAllocAmount;

      BFObjIter iter (*pFundAllocationList, idDataGroup);
      iter.begin();       
	  while (!iter.end())
	  {
	     TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (iter.getObject());

		 if (pTradeFundAlloc)
		 {
		    pTradeFundAlloc->getField(ifds::FundCode, dstrAllocFundCode, idDataGroup, false);
			pTradeFundAlloc->getField(ifds::ClassCode, dstrAllocClassCode, idDataGroup, false);
			pTradeFundAlloc->getField(ifds::AllocPercentage, dstrAllocPercentage, idDataGroup, false);
			pTradeFundAlloc->getField(ifds::AllocAmount, dstrAllocAmount, idDataGroup, false);
			
			// create repeat request record
			BFData repeat(ifds::DSTC0414_REQRepeat_Record);
			repeat.setElementValue(ifds::AllocFundToCode, dstrAllocFundCode);
			repeat.setElementValue(ifds::AllocClassToCode, dstrAllocClassCode);
			repeat.setElementValue(ifds::AllocPercentage, dstrAllocPercentage);
			repeat.setElementValue(ifds::AllocAmount, dstrAllocAmount);

			requestData.addRepeat(repeat);
		 }
		 ++iter;
	  }
		
	  dstRepeats = DString::asString( requestData.getRepeatCount() );
	  requestData.setElementValue(ifds::RepeatCount, dstRepeats);

   }

   ReceiveData(DSTC_REQUEST::SEG_COT_TRX_VALIDATION_INQUIRY, requestData, 
               ifds::DSTC0414_VW, DSTCRequestor(getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SegTrxValidationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new SegTrxValidation( *this );
   ((SegTrxValidation*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SegTrxValidationList::doCreateNewObject (BFCBO *& pBase, 
                                                       DString &strKey, 
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SegTrxValidationList.cpp-arc  $
// 
//    Rev 1.2   Sep 22 2010 04:51:08   kitticha
// PETP0173756 FN02 Don't Bust the Rules - few changes.
// 
//    Rev 1.1   Sep 21 2010 06:42:12   kitticha
// PETP0173756 FN02 Don't Bust the Rules - few changes.
// 
//    Rev 1.0   Sep 17 2010 03:56:08   kitticha
// Initial revision.
// 
//
