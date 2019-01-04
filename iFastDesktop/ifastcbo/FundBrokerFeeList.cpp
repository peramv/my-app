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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerFeeList.cpp
// ^AUTHOR : 
// ^DATE   : July. 26, 2004
//
// ^CLASS    : FundBrokerFeeList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "feeparamsyslist.hpp"
#include "FundBrokerFeeList.hpp"
#include "FundBrokerFee.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_LIST;
}


namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "FundBrokerFeeList" );  
   const I_CHAR * const IDI_CODE     = I_("CODE");  
   const I_CHAR * const DEFAULT_DATE = I_( "01010001" );
   const I_CHAR * const YES			 = I_( "Y" );
   const I_CHAR * const NO			 = I_( "N" );

}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeCodeDateCross;
   extern CLASS_IMPORT const BFDateFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeSet;
   
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId FndSpFeeModelID;

}

namespace CND
{
   extern const long ERR_FEE_CODE_OVERLAPED;  
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FundBrokerFeeList::FundBrokerFeeList( BFAbstractCBO &parent )
: FeeParamBaseList( parent )
, requestData230 ( NULL )
, m_intNewKey( 1 )
, m_intKey( 512 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FundBrokerFeeList::~FundBrokerFeeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( requestData230 != NULL )
   {
	   delete requestData230;
   }
}

//*********************************************************************************
SEVERITY FundBrokerFeeList::init( const DString& dstrFundBrokerCode,  
                                  const BFDataGroupId& idDataGroup, const DString& dstrTrack,
                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
	requestData230 = new BFData(ifds::DSTC0230_REQ);  
	requestData230->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData230->setElementValue( ifds::Track, dstrTrack );
	requestData230->setElementValue( ifds::Activity, dstrPageName );
	requestData230->setElementValue( ifds::NextKey,     NULL_STRING );
	
	requestData230->setElementValue( ifds::CommGroup, dstrFundBrokerCode );

   requestData230->setElementValue( ifds::DefaultFeeCode, YES );
   requestData230->setElementValue( ifds::SysFeeSearchType, I_("CommGroupOnly") );   

	BFData* responseData = new BFData(ifds::DSTC0230_VW);
	ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_LIST, *requestData230, *responseData, DSTCRequestor( getSecurity(),false,false ) );


   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY FundBrokerFeeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new FundBrokerFee( *this );
   ((FundBrokerFee* )pObjOut )->Init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FundBrokerFeeList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   FundBrokerFee* pFundBrokerFee = new FundBrokerFee( *this );
   pFundBrokerFee->InitNew( idDataGroup  );
   pBase = pFundBrokerFee;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FundBrokerFeeList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   FeeParamBaseList::doValidateAll(idDataGroup, lValidateGroup);

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void FundBrokerFeeList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   strKey = asString(m_intKey);

   m_intKey++;
}

//******************************************************************************
void FundBrokerFeeList::getStrKeyForNewItem(DString & strKey)
{
   strKey = asString(m_intNewKey);
   m_intNewKey++;
}
//******************************************************************************
SEVERITY FundBrokerFeeList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
	   BFData* responseData = new BFData(ifds::DSTC0230_VW);
	   ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_LIST, *requestData230, *responseData, DSTCRequestor( getSecurity(),false,false ) );
    }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY FundBrokerFeeList::validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOverlapping" ) );   

   DString dstrFeeCode, dstrFeeType, dstrEffectiveDate, dstrStopDate;
   FundBrokerFee * pFundBrokerFee = dynamic_cast<FundBrokerFee *> (pCBO);
   pFundBrokerFee->getField(ifds::FeeCode, dstrFeeCode, idDataGroup,false );
   //pFundBrokerFee->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup,false );
   pFundBrokerFee->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup,false );
   pFundBrokerFee->getField(ifds::StopDate, dstrStopDate, idDataGroup,false );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   DString dstrEffectiveDate1, dstrStopDate1, dstrFeeCode1, dstrFeeType1;
   while( !iter.end() )
   {
      FundBrokerFee* pFundBrokerFee1 = dynamic_cast<FundBrokerFee* >(iter.getObject() );
      pFundBrokerFee1->getField(ifds::FeeCode,dstrFeeCode1,idDataGroup,false);
		//pFundBrokerFee1->getField(ifds::ParamFeeType,dstrFeeType1,idDataGroup,false);

		if( pFundBrokerFee1 && pFundBrokerFee1 != pFundBrokerFee &&
         dstrFeeCode1.strip().upperCase() == dstrFeeCode.strip().upperCase()  )
		{
			pFundBrokerFee1->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false);
			pFundBrokerFee1->getField(ifds::StopDate,dstrStopDate1,idDataGroup,false);         

         if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
													      dstrEffectiveDate, dstrStopDate ) )
         {
            //FeeCode XXXX and ParamFeeType YYYY is overlapping for the date range DDDD  to DDDD   
            DString dstrTemp;                 
			   addIDITagValue( dstrTemp, IDI_CODE, dstrFeeCode +I_(" ") );         
			   ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, dstrTemp );
         }
      }
      
      ++iter;
   }
   
   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************
void FundBrokerFeeList::InitNew(const BFDataGroupId& idDataGroup)
{  
   return;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerFeeList.cpp-arc  $
// 
//    Rev 1.3   Nov 24 2004 16:49:52   Fengyong
// receive 25 record each time
// 
//    Rev 1.2   Nov 23 2004 17:25:16   Fengyong
// PET1117FN54 - adjustment after first day intergretion test
// 
//    Rev 1.1   Nov 14 2004 14:41:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 02 2004 16:01:08   FENGYONG
// Initial revision.
// 
*/
