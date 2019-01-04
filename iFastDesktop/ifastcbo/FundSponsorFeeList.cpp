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
// ^FILE   : FundSponsorFeeList.cpp
// ^AUTHOR : 
// ^DATE   : July. 26, 2004
//
// ^CLASS    : FundSponsorFeeList 
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
#include "FundSponsorFeeList.hpp"
#include "FundSponsorFee.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_LIST;
}


namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "FundSponsorFeeList" );  
   const I_CHAR * const IDI_CODE     = I_( "CODE");  
   const I_CHAR * const DEFAULT_DATE = I_( "01010001" );
   const I_CHAR * const YES			 = I_( "Y" );
   const I_CHAR * const NO			 = I_( "N" );
   const I_CHAR * const PERCENT		 = I_( "1" );

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
FundSponsorFeeList::FundSponsorFeeList( BFAbstractCBO &parent )
: FeeParamBaseList( parent )
, m_intNewKey( 1 )
, m_intKey( 512 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FundSponsorFeeList::~FundSponsorFeeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FundSponsorFeeList::init ( const DString &dstrFeeModelCode, 
                                    const DString &dstrFundSponsorCode, 
                                    const BFDataGroupId &idDataGroup, 
                                    const DString &dstrTrack,
                                    const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
	
   requestData230 = new BFData (ifds::DSTC0230_REQ);  
	requestData230->setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData230->setElementValue (ifds::Track, dstrTrack);
	requestData230->setElementValue (ifds::Activity, dstrPageName);
	requestData230->setElementValue (ifds::NextKey, NULL_STRING);

	requestData230->setElementValue (ifds::FeeModelCode, dstrFeeModelCode) ;
	requestData230->setElementValue (ifds::CommGroup, dstrFundSponsorCode);

   requestData230->setElementValue (ifds::DefaultFeeCode, YES);
   requestData230->setElementValue (ifds::SysFeeSearchType, I_("FeeModelFundClass"));
   requestData230->setElementValue (ifds::AsofDate, I_("12319999"));
   
   BFData* responseData = new BFData(ifds::DSTC0230_VW);
	
   ReceiveData ( DSTC_REQUEST::FEE_PARAM_SYSTEM_LIST, 
                 *requestData230, 
                 *responseData, 
                 DSTCRequestor (getSecurity(), true, false));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundSponsorFeeList::InitNew (const BFDataGroupId &idDataGroup)
{     
   //link FundSponsorFeeModel with the FndSpFeeModelID
   DString dstrFndSpFeeModelID;
   getParent()->getField (ifds::FndSpFeeModelID, dstrFndSpFeeModelID, idDataGroup, false);
}

//********************************************************************************
SEVERITY FundSponsorFeeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new FundSponsorFee( *this );
   ((FundSponsorFee* )pObjOut )->Init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FundSponsorFeeList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   FundSponsorFee* pFundSponsorFee = new FundSponsorFee( *this );
   pFundSponsorFee->InitNew( idDataGroup  );
   pBase = pFundSponsorFee;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FundSponsorFeeList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   FeeParamBaseList::doValidateAll(idDataGroup, lValidateGroup);

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void FundSponsorFeeList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   strKey = asString(m_intKey);

   m_intKey++;
}

//******************************************************************************
void FundSponsorFeeList::getStrKeyForNewItem(DString & strKey)
{
   strKey = asString(m_intNewKey);
   m_intNewKey++;
}

//******************************************************************************
SEVERITY FundSponsorFeeList::validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOverlapping" ) );   

   DString dstrFeeCode, dstrFeeType, dstrEffectiveDate, dstrStopDate;
   FundSponsorFee * pFundSponsorFee = dynamic_cast<FundSponsorFee *> (pCBO);
   pFundSponsorFee->getField(ifds::FeeCode, dstrFeeCode, idDataGroup,false );
   //pFundSponsorFee->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup,false );
   pFundSponsorFee->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup,false );
   pFundSponsorFee->getField(ifds::StopDate, dstrStopDate, idDataGroup,false );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   DString dstrEffectiveDate1, dstrStopDate1, dstrFeeCode1, dstrFeeType1;
   while( !iter.end() )
   {
      FundSponsorFee* pFundSponsorFee1 = dynamic_cast<FundSponsorFee* >(iter.getObject() );
      pFundSponsorFee1->getField(ifds::FeeCode,dstrFeeCode1,idDataGroup,false);
		//pFundSponsorFee1->getField(ifds::ParamFeeType,dstrFeeType1,idDataGroup,false);

		if( pFundSponsorFee1 && pFundSponsorFee1 != pFundSponsorFee &&
         dstrFeeCode1.strip().upperCase() == dstrFeeCode.strip().upperCase() /*&& 
         dstrFeeType1.strip().upperCase() == dstrFeeType.strip().upperCase()*/ )
		{
			pFundSponsorFee1->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false);
			pFundSponsorFee1->getField(ifds::StopDate,dstrStopDate1,idDataGroup,false);         

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
void FundSponsorFeeList::setFieldForAllRecords(const BFFieldId& idField, const DString value, const BFDataGroupId& idDataGroup)
{ 
      
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end())
   {            
      iter.getObject()->setField( idField, value, idDataGroup, false );
      ++iter;
   }            
      
   return;
}

//******************************************************************************
void FundSponsorFeeList::setFieldValidflag(const BFFieldId& idField, const BFDataGroupId& idDataGroup, const bool valid )
{
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end())
   {  
      FundSponsorFee* pFee = dynamic_cast<FundSponsorFee* >( iter.getObject() );
      pFee->setFieldValid (idField, idDataGroup, valid);
      ++iter;
   }
      
   return;
}
//******************************************************************************
void FundSponsorFeeList::setStopDateForAllRecords(const BFDataGroupId& idDataGroup)
{ 
      
   DString dstrFeeCode;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end())
   {
      FundSponsorFee* pFee = dynamic_cast<FundSponsorFee* >( iter.getObject() );
		if( pFee )
		{
		    pFee->stampCurBusinessDateToStopDate( idDataGroup );
		}
		++iter;
   }               
}

//******************************************************************************
bool FundSponsorFeeList::Not100PercentDiscount(const BFDataGroupId& idDataGroup)
{     
   bool havePercentDiscount = false, Not100Discount = false;
   
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end())
   {
        FundSponsorFee* pFee = dynamic_cast<FundSponsorFee* >( iter.getObject() );
		if( pFee )
		{
			DString dstrFeeCode, dstrFeeType, dstrRate;
		    pFee->getField(ifds::FeeCode, dstrFeeCode, idDataGroup,false );
			if( dstrFeeCode == I_("110") || dstrFeeCode == I_("111") )
			{
				pFee->getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
				dstrFeeType.strip().upperCase();
				pFee->getField(ifds::Rate,dstrRate,idDataGroup );
				double dRate =  DSTCommonFunctions::convertToDouble( dstrRate );
				if( dstrFeeType == PERCENT ) 
				{
					havePercentDiscount = true;
					if( fabs( 100.0 - dRate ) > .0000000001 )
					{
						Not100Discount = true;
						break;
					}
				}
			}
		}
		++iter;
   }  
   return !havePercentDiscount || Not100Discount ;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorFeeList.cpp-arc  $
// 
//    Rev 1.15   Jul 13 2005 17:38:26   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.14   Apr 07 2005 14:45:32   Fengyong
// incident 246230 - Add break after find Not100Discount
// 
//    Rev 1.13   Mar 16 2005 11:52:10   Fengyong
// Incident #246230 - remove warning for bonimax + transaction and discount (100%) + transaction
// 
//    Rev 1.12   Nov 14 2004 14:43:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Nov 02 2004 11:01:36   FENGYONG
// PTS10035274 - Validation between ModelOption and FeeCode
// 
//    Rev 1.10   Oct 21 2004 17:23:42   YINGBAOL
// PTS10034903: change logic for stamp current business date to stop date.
// 
//    Rev 1.9   Oct 21 2004 10:16:44   FENGYONG
// PTS10034903 - remove Fee Type from error message
// 
//    Rev 1.8   Oct 18 2004 09:54:44   FENGYONG
// PTS10034779 - Fee type should not be included as unique key for fee set up.
// 
//    Rev 1.7   Sep 29 2004 09:33:48   FENGYONG
// PET1117FN5 - change after Ess walk through
// 
//    Rev 1.6   Sep 15 2004 15:45:02   FENGYONG
// duplicate not case sensitive
// 
//    Rev 1.5   Sep 15 2004 12:21:22   FENGYONG
// ReceiveAll
// 
//    Rev 1.4   Sep 10 2004 15:52:00   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.3   Sep 02 2004 12:30:58   FENGYONG
// Add Conditions for PET1117 FN5
// 
//    Rev 1.2   Aug 31 2004 17:30:56   FENGYONG
// change Field names
// 
//    Rev 1.1   Aug 10 2004 11:24:34   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:20   FENGYONG
// Initial Revision
// 
*/
