//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : HypoTradeACB.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoTradeACB
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "hypotradeacb.hpp"
#include "trade.hpp"
#include <ifastdataimpl\dse_dstc0294_req.hpp>
#include <ifastdataimpl\dse_dstc0294_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "HypoTradeACB" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HYPO_TRADE_ACB;
}


//******************************************************************************
HypoTradeACB::HypoTradeACB( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
HypoTradeACB::~HypoTradeACB()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HypoTradeACB::init( const BFDataGroupId& idDataGroup, 
									  const DString& dstrTrack,
                             const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "init()" ) );
	 const BFFieldId bfField[] ={
		ifds::AccountNum,
		ifds::TradesTransType,
		ifds::FromFund,
		ifds::FromClass,
		ifds::ToFund,
		ifds::ToClass,
		ifds::EffectiveDate,
		ifds::Amount,
		ifds::AmtType,
		ifds::NullFieldId
		};	

   BFData queryData(ifds::DSTC0294_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
	int i = 0;
	DString dstrValue;
	BFAbstractCBO* pParent = getParent();
	if(pParent)
	{
		while(bfField[i] != ifds::NullFieldId)
		{
			
			pParent->getField(bfField[i],dstrValue, idDataGroup,false);
			queryData.setElementValue( bfField[i], dstrValue  ); 
			i++;
		}
	}
   SEVERITY sevRtn = SEVERE_ERROR;
   BFData *responseData = new BFData(ifds::DSTC0294_VW);

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::HYPO_TRADE_ACB, queryData,
	  *responseData, DSTCRequestor( getSecurity() ) )  > WARNING )
   {
      delete responseData;
      responseData = NULL;
   }
   else
   {
      attachDataObject( *responseData, true, true );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
SEVERITY HypoTradeACBInterface::getHypoTradeACB( Trade* pTrade, 
				 HypoTradeACB* &pAcb, const BFDataGroupId& idDataGroup,bool bInquiry )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getHypoTradeACBgetHypoTradeACB" ) );
	
	

   pAcb = dynamic_cast<HypoTradeACB *>( pTrade->getObject( I_( "HypoTradeACB" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pAcb )
   {
      if( bInquiry ) //make the view call
      {
         pAcb = new HypoTradeACB( *pTrade );
         pAcb->init( idDataGroup );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pAcb )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            //TODO:  Should be idWorkingDataGroup???
            pTrade->setObject( pAcb, I_( "HypoTradeACB" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup); 
         }
         else
         {
            delete pAcb;
            pAcb = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoTradeACB.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:44:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Jun 02 2004 16:02:54   YINGBAOL
// PTS10030671:Add amount type to view 294
// 
//    Rev 1.2   May 25 2004 10:05:46   YINGBAOL
// PET985: change view 294
// 
//    Rev 1.1   May 19 2004 17:39:34   YINGBAOL
// PET985: make hypo work
// 
//    Rev 1.0   Apr 26 2004 13:41:24   VADEANUM
// Initial revision.
//
