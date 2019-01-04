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
// ^FILE   : FeeParamList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Jan. 26, 2002
//
// ^CLASS    : FeeParamList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeparamlist.hpp"
#include "feeparam.hpp"
#include <ifastdataimpl\dse_dstc0194_req.hpp>
#include <ifastdataimpl\dse_dstc0194_vw.hpp>
#include <ifastdataimpl\dse_dstc0195_vw.hpp>
#include <ifastdataimpl\dse_dstc0195_req.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"
#include "fundcommgrouplist.hpp"
#include "errmsgruleslist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM;
   extern CLASS_IMPORT const DSTCRequest FEE_SCALE;
}

namespace  
{
   const I_CHAR * const CLASSNAME						= I_( "FeeParamList" );  
   const I_CHAR * ACCOUNT_NUMBER_FIELD					= I_( "AccountNum" );
   const I_CHAR * const IDI_CODE						= I_( "CODE" );  
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_( "18" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_( "180" );
   const I_CHAR * const ACCOUNT_LEVEL					= I_("ACCOUNT");
   const I_CHAR * const ERR_ALL_FUND_GROUP_REQUIRED		= I_( "360" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeLevel;
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_CODE_OVERLAPED;  
   extern const long ERR_DELETE_FEE_PARAMETER;
   extern const long ERR_COMM_GROUP_CODE_OVERLAPED;
   extern const long ERR_FUND_GROUP_NOT_EXIST_FOR_MANAGEMENT_FEE;
   extern const long ERR_FEE_CODE_COEXIST_NOT_ALLOWED;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FeeParamList::FeeParamList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _pAcctFeeScaleData( NULL )
, requestData194( NULL )
, requestData195( NULL )
, _pErrMsgRulesList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FeeParamList::~FeeParamList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete _pAcctFeeScaleData;
   delete requestData194;
   delete requestData195;
}

//*********************************************************************************
SEVERITY FeeParamList::initNew( const DString& AccountNum, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeParamList::init( const DString& AccountNum, 
                             const BFDataGroupId& idDataGroup,
                             bool bMore,
                             const DString& dstrTrack,
                             const DString& dstrPageName  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
// receive data from back end
   DString mgmtCoIdOut;

   if( bMore && doMoreRecordsExist() )
   {
      BFData* responseData =  new BFData(ifds::DSTC0194_VW);
      ReceiveData(DSTC_REQUEST::FEE_PARAM, *requestData194, *responseData, DSTCRequestor( getSecurity(),false ) );    
   }
   else
   {
      //scale or tire
      requestData195 =  new BFData(ifds::DSTC0195_REQ);
      _pAcctFeeScaleData = new BFData(ifds::DSTC0195_VW);
      requestData195->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData195->setElementValue( ifds::AccountNum, AccountNum );
      requestData195->setElementValue( ifds::Track, dstrTrack );
      requestData195->setElementValue( ifds::Activity, dstrPageName );
      requestData195->setElementValue( ifds::NextKey,     NULL_STRING );

	  //Precache all of the scales of the current account at the first init.
      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::FEE_SCALE, *requestData195, *_pAcctFeeScaleData,
                                                DSTCRequestor( getSecurity(), true ) )  > WARNING )
      {
         delete _pAcctFeeScaleData;
         _pAcctFeeScaleData = NULL;
         return(GETCURRENTHIGHESTSEVERITY());
      }

//Create CBO

      requestData194 = new BFData(ifds::DSTC0194_REQ);  
      requestData194->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData194->setElementValue( ifds::AccountNum, AccountNum );
      requestData194->setElementValue( ifds::Track, dstrTrack );
      requestData194->setElementValue( ifds::Activity, dstrPageName );
      requestData194->setElementValue( ifds::NextKey,     NULL_STRING );
      BFData* responseData = new BFData(ifds::DSTC0194_VW);
      ReceiveData(DSTC_REQUEST::FEE_PARAM, *requestData194, *responseData, DSTCRequestor( getSecurity(),false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY FeeParamList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString dstrAcctParamId = data.getElementValue( ifds::AcctFeeParamId );

   dstrAcctParamId.strip().stripLeading( I_CHAR( '0' ) );

   pObjOut =  new FeeParam( *this );
   ((FeeParam* )pObjOut )->init(data,_pAcctFeeScaleData, dstrAcctParamId);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeParamList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   FeeParam* pFeeParam = new FeeParam( *this );
   pFeeParam->init( idDataGroup  );
   pBase = pFeeParam;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeParamList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );


   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrFeeCode1, dstrFundCode1, dstrClassCode1, dstrCommGroupCode1, dstrEffectiveDate1,dstrStopDate1;
   DString dstrFeeCode2, dstrFundCode2, dstrClassCode2, dstrCommGroupCode2, dstrEffectiveDate2,dstrStopDate2;
   bool bNewFee18 = false;

   while( !iter.end() )
   {
    	BFAbstractCBO* cbo1 = iter.getObject();

		if ( !iter.isDummy() && cbo1->isNew() )
        {
			cbo1->getField(ifds::FeeCode,dstrFeeCode1,idDataGroup,false);
			cbo1->getField(ifds::FundCode,dstrFundCode1,idDataGroup,false);
			cbo1->getField(ifds::ClassCode,dstrClassCode1,idDataGroup,false);
			cbo1->getField(ifds::CommGroup,dstrCommGroupCode1,idDataGroup,false);
			cbo1->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false);
			cbo1->getField(ifds::StopDate,dstrStopDate1,idDataGroup,false);


			dstrFeeCode1.strip().upperCase();
			dstrFundCode1.strip().upperCase();
			dstrClassCode1.strip().upperCase();
			dstrEffectiveDate1.strip(); 
			dstrStopDate1.strip();
			dstrCommGroupCode1.strip().upperCase();

			if ( dstrFeeCode1 == FEE_CODE_MANAGEMENT_FEE )
			{
				bNewFee18 = true;
			}

			iter1.positionByKey( iter.getStringKey() );
			++iter1;
			for( iter1; !iter1.end(); ++iter1 )
			{
				BFAbstractCBO* cbo2 = iter1.getObject();
				if ( !iter1.isDummy() && cbo2->isNew() )
				{
					cbo2->getField(ifds::FeeCode,dstrFeeCode2,idDataGroup,false);
					cbo2->getField(ifds::FundCode,dstrFundCode2,idDataGroup,false);
					cbo2->getField(ifds::ClassCode,dstrClassCode2,idDataGroup,false);
					cbo2->getField(ifds::CommGroup,dstrCommGroupCode2,idDataGroup,false);
					cbo2->getField(ifds::EffectiveDate,dstrEffectiveDate2,idDataGroup,false);
					cbo2->getField(ifds::StopDate,dstrStopDate2,idDataGroup,false);

					dstrFeeCode2.strip().upperCase();
					dstrFundCode2.strip().upperCase();
					dstrClassCode2.strip().upperCase();
					dstrEffectiveDate2.strip(); 
					dstrStopDate2.strip();
					dstrCommGroupCode2.strip().upperCase();


					//Fee code 18 and 180 cannot be co-exists and effective under the same period at account level fee set up. 
					if ( ( dstrFeeCode1 == FEE_CODE_MANAGEMENT_FEE && dstrFeeCode2 == FEE_CODE_MANAGEMENT_DISCOUNT ) ||
						 ( dstrFeeCode1 == FEE_CODE_MANAGEMENT_DISCOUNT && dstrFeeCode2 == FEE_CODE_MANAGEMENT_FEE )	)
					{
						if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																	dstrEffectiveDate2, dstrStopDate2 ) )
							{
								ADDCONDITIONFROMFILE( CND::ERR_FEE_CODE_COEXIST_NOT_ALLOWED);
								return(GETCURRENTHIGHESTSEVERITY());
							}
					}
					//FeeCode Duplicate check for new records
					if(dstrCommGroupCode1 == NULL_STRING && dstrCommGroupCode2 == NULL_STRING )
					{
						if( dstrFeeCode1 == dstrFeeCode2 && dstrFundCode1 == dstrFundCode2 && 
							dstrClassCode1 == dstrClassCode2  )
						{
							if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																	   dstrEffectiveDate2, dstrStopDate2 ) )
							{
								DString strTemp;                 
								addIDITagValue( strTemp, IDI_CODE, dstrFeeCode1 +I_(" ") + dstrFundCode1 + I_(" ") + dstrClassCode2);         
								ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, strTemp);
								return(GETCURRENTHIGHESTSEVERITY());
							}
						}
					}
					else
					{
						 if (dstrCommGroupCode1 == dstrCommGroupCode2 && dstrFeeCode1 == dstrFeeCode2 )					 
						 {
							
							 if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																		dstrEffectiveDate2, dstrStopDate2 ) )
							{
								DString strTemp;                 
								addIDITagValue( strTemp, IDI_CODE, dstrFeeCode1 +I_(" ") + dstrCommGroupCode1 + I_(" ") + dstrCommGroupCode2);         
								ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, strTemp);
								return(GETCURRENTHIGHESTSEVERITY());
							}
						 }
					}
					
				}
			}
		}
  
	
	   dynamic_cast<FeeParam*>(iter.getObject() )->validateFeeScaleList( idDataGroup );

      ++iter;
   }

   DString dstrErrValue;
   getErrMsgValue( ERR_ALL_FUND_GROUP_REQUIRED, idDataGroup, dstrErrValue );

   if ( dstrErrValue == I_("E")  )
   {
		validateManagementFee( idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
// sort by FeeCode and EffectiveDate
void  FeeParamList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrBrokerCode,
		     dstrSortDate, 	
		     dstrFeeCode,	     
			  dstrFundCode,
			  dstrClassCode,			  
			  dstrCommGroup,
			  dstrAcctParamId;

   dstrBrokerCode =  data->getElementValue( I_( "BrokerCode" ) );
   dstrBrokerCode.upperCase().strip();   
	
	DString dstrEffectiveDate = data->getElementValue( I_( "EffectiveDate" ) );
   DSTCommonFunctions::convertToSortableDateInDec ( dstrEffectiveDate, dstrSortDate );
	
	dstrFeeCode = data->getElementValue( I_( "FeeCode" ) );
   dstrFeeCode.strip().stripLeading('0');
   dstrFeeCode.padLeft( 2, '0' );  

   dstrFundCode = data->getElementValue( I_( "FundCode" ) );
   dstrFundCode.strip();

	dstrClassCode = data->getElementValue( I_( "ClassCode" ) );   
	dstrClassCode.strip();
   
	dstrCommGroup = data->getElementValue( I_( "CommGroup" ) );
   dstrCommGroup.upperCase().strip();	
	
	dstrAcctParamId = data->getElementValue( ifds::AcctFeeParamId );
   dstrAcctParamId.strip().stripLeading( I_CHAR( '0' ) );
	
	strKey = dstrBrokerCode 
	       + dstrSortDate 
	   	   + dstrFeeCode.strip().upperCase()   
			 + dstrFundCode 
			 + dstrClassCode 
			 +	dstrCommGroup
			 + dstrAcctParamId;		
}
//************************************************************************************
// 
bool FeeParamList::canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

   // logic: if it is new, or if it is just created today, delete is allowed 
   DString strProcessDate,strCurBusDate;
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
   pObj->getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
   if( pObj->isNew() || 
       DSTCommonFunctions::CompareDates(strCurBusDate,strProcessDate ) == DSTCommonFunctions::EQUAL )
   {
      return(true);
   }
   ADDCONDITIONFROMFILE( CND::ERR_DELETE_FEE_PARAMETER );
   return(false);
}

//************************************************************************************
//Once user set up an active Fee Code 18 for pinnacle, system need to ensure active record 
//must exists for all fund group that are available in the Fund Group List.

SEVERITY FeeParamList::validateManagementFee( const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateManagementFee" ) );

	DString dstrFeeCode, dstrFundGroup, dstrCodeList, dstrCode, dstrDes, dstrStopDate; 
	int iCodePos;

	bool bFeeCode18 = false;
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	while ( !iter1.end() )
	{
    			BFAbstractCBO* cbo = iter1.getObject();

				if ( !iter1.isDummy() )
				{
					cbo->getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);

					cbo->getField(ifds::CommGroup,dstrFundGroup,idDataGroup,false);
				 
					if (dstrFeeCode == FEE_CODE_MANAGEMENT_FEE && dynamic_cast<FeeParam*>( cbo )->isActiveRecord( idDataGroup ) )
					{				
						if( dstrFundGroup.strip() != NULL_STRING )
						{
							bFeeCode18 = true;
							break;
						}
					}
				}
				++iter1;	
	
	
	}
	if ( !bFeeCode18 )
	{
	  return NO_CONDITION;
	}

	getFundGroupListByFeeCode( FEE_CODE_MANAGEMENT_FEE, dstrCodeList, BF::HOST);
    
	if( dstrCodeList != NULL_STRING )
		dstrCodeList += I_(";");
	else
		return NO_CONDITION;

	int iPos =  dstrCodeList.find_first_of(I_(";") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(";") );
		if( iPos == DString::npos ) break;
		dstrDes = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		iCodePos = dstrDes.find_first_of(I_("=") );
		if ( iCodePos != DString::npos )
		{
			dstrCode = dstrDes.left(iCodePos);
			BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			bool bFound = false;

		   while( !iter.end() )
		   {
    			BFAbstractCBO* cbo = iter.getObject();

				if ( !iter.isDummy() )
				{
					cbo->getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);

					cbo->getField(ifds::CommGroup,dstrFundGroup,idDataGroup,false);
				 
					if (dstrFeeCode == FEE_CODE_MANAGEMENT_FEE && dstrFundGroup == dstrCode && dynamic_cast<FeeParam*>( cbo )->isActiveRecord( idDataGroup ) )
					{
						bFound = true;
						break;
					}
				}
				++iter;
		   }
			if ( !bFound )
			{
				DString strTemp;                 
				addIDITagValue( strTemp, IDI_CODE, dstrCode);         

				ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_GROUP_NOT_EXIST_FOR_MANAGEMENT_FEE, strTemp);
				return(GETCURRENTHIGHESTSEVERITY());

			}
			
		}
	}	

    return(GETCURRENTHIGHESTSEVERITY());
	
}

//************************************************************************************
SEVERITY FeeParamList::getFundGroupListByFeeCode(const DString dstrFeeCode, DString &dstrList, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundGroupListByFeeCode" ) );

	dstrList = NULL_STRING;
	FeeParamConfig *pFeeParamConfig = NULL;

	if ( getFeeParamConfigByFeeCode( dstrFeeCode, pFeeParamConfig, idDataGroup ) <= WARNING )
	{
		if ( pFeeParamConfig )
		{
			//For CommGroup, call getFundGroupType from FeeParamConfig, and the value will be used as
			//input parameter for view 229 (FundCommGroupList)
			DString dstrGroupType = NULL_STRING;
			DString dstrSubList = NULL_STRING;
			pFeeParamConfig->getFundGroupType(dstrGroupType);
			if (dstrGroupType != NULL_STRING) 
			{
				FundCommGroupList* pFundCommGroupListP = NULL;
				if(getMgmtCo().getFundCommGroupList( dstrGroupType,pFundCommGroupListP ) <= WARNING )
				{
					pFundCommGroupListP->getCommGroupSubstitute(dstrSubList, false);
				}
			}
			dstrList = dstrSubList;
		}
		
	}

	CLEARCONDITIONSFRAMECURRENT(); 
	return NO_CONDITION;
}

//************************************************************************************
SEVERITY FeeParamList::getFeeParamConfigByFeeCode(const DString dstrFeeCode, FeeParamConfig *&pFeeParamConfig, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeParamConfigByFeeCode" ) );

	DString dstrFeeCodeComp, dstrLevel;
	FeeParamConfigList*	pFeeParamConfigList = NULL;
	pFeeParamConfig = NULL;

	if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
	{
		if (pFeeParamConfigList)
		{
			BFObjIter iter( *pFeeParamConfigList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			
			//look for account level first, if not exist, use default level
			for (;!iter.end();++iter)
			{

				(iter.getObject() )->getField(ifds::FeeCode, dstrFeeCodeComp, idDataGroup,false);
				(iter.getObject() )->getField(ifds::FeeLevel, dstrLevel, idDataGroup,false );

				if (dstrFeeCodeComp != dstrFeeCode)
				{
					continue;
				}
				else
				{
					if ( dstrLevel.upperCase() == ACCOUNT_LEVEL )
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
						break;
					}
					else
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
					}
				}
			}
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
void FeeParamList::getErrMsgValue( DString dstrErrNum,       
								  const BFDataGroupId& idDataGroup, 
								  DString& dstrErrValue 
								)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsgValue" ) );
   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {	   
      _pErrMsgRulesList->getEWIValue( dstrErrNum, idDataGroup, dstrErrValue);
   }

}
//*******************************************************************************************
// The method does 3 checks:
//  1. check if the CBO has been deleted and has not been sent to iFast
//  2. check if the record is overlapping with existing record
//  3. Check if fee code1 with other fee code2 
//
//
//
bool FeeParamList::FindDeletedOverlapRecord(const FeeParam* pFeeParam,const BFDataGroupId& idDataGroup,
												  const DString& dstrExClFeeCode, BFObjIter::ITERTYPE itertype )
{

	bool bExist = false;

	DString dstrFeeCode,dstrFeeCode1,dstrFundCode,dstrFundCode1,dstrCommGroupCode,dstrCommGroupCode1,
		dstrEffectiveDate,dstrEffectiveDate1,dstrAcctNum,dstrAcctNum1,dstrStopDate,dstrStopDate1,
		dstrBrokerCode,dstrBrokerCode1, dstrClassCode,dstrClassCode1;

	
	if( dstrExClFeeCode == NULL_STRING )  // check if exclude fee code record has been deleted.
	{
  		pFeeParam->getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
	}
	else
	{
		dstrFeeCode = dstrExClFeeCode;	
	}
	pFeeParam->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
	pFeeParam->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
	pFeeParam->getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
	pFeeParam->getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);
	pFeeParam->getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
	pFeeParam->getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);
   dstrFeeCode.strip();
	dstrFundCode.strip().upperCase();
	dstrClassCode.strip().upperCase();
	dstrCommGroupCode.strip();
	dstrEffectiveDate.strip();
	dstrStopDate.strip();
	dstrBrokerCode.strip();
	
	
	BFObjIter iter1( *this, idDataGroup, false, itertype );
	while( !iter1.end() )
	{

		FeeParam* pFeeHost = dynamic_cast<FeeParam* >(iter1.getObject() );
		if( pFeeHost != pFeeParam && pFeeHost )
		{
			pFeeHost->getField(ifds::FeeCode,dstrFeeCode1,idDataGroup,false);
			pFeeHost->getField(ifds::FundCode,dstrFundCode1,idDataGroup,false);
			pFeeHost->getField(ifds::ClassCode,dstrClassCode1,idDataGroup,false);
			pFeeHost->getField(ifds::CommGroup,dstrCommGroupCode1,idDataGroup,false);
			pFeeHost->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false);
			pFeeHost->getField(ifds::StopDate,dstrStopDate1,idDataGroup,false);
			pFeeHost->getField(ifds::BrokerCode,dstrBrokerCode1,idDataGroup,false);
			dstrFeeCode1.strip();
			dstrFundCode1.strip().upperCase();
			dstrClassCode1.strip().upperCase();
			dstrCommGroupCode1.strip();
			dstrEffectiveDate1.strip();
			dstrStopDate1.strip();
			dstrBrokerCode1.strip();
			if( dstrExClFeeCode != NULL_STRING && dstrFeeCode1==dstrFeeCode )
			{
				if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																	   dstrEffectiveDate, dstrStopDate ) )


				{
					bExist = true; // find a deleted record.
					break;
				}								
			}
			if(dstrFeeCode1==dstrFeeCode && dstrFundCode1==dstrFundCode &&
				dstrClassCode1==dstrClassCode && dstrCommGroupCode1==dstrCommGroupCode &&
				dstrBrokerCode1==dstrBrokerCode && dstrBrokerCode1==dstrBrokerCode  )
			{
				if( DSTCommonFunctions::dateRangesOverlap( dstrEffectiveDate1, dstrStopDate1,
																	   dstrEffectiveDate, dstrStopDate ) )


				{
					bExist = true; // find a deleted record.
					break;
				}		
			}			
		}
		++iter1;
	}
	return bExist;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamList.cpp-arc  $
// 
//    Rev 1.30   May 25 2011 08:50:58   wutipong
// IN2457300 - MFR setup Acct Level - Error Message
// 
//    Rev 1.29   Nov 22 2004 16:53:26   yingbaol
// PTS10035806: check FundGroup != NULL_STRING
// 
//    Rev 1.28   Nov 22 2004 16:48:10   yingbaol
// PTS10035806:sync. up version 1.25.1.0
// 
//    Rev 1.27   Nov 14 2004 14:40:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.26   Nov 04 2004 17:37:34   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.25   Jul 19 2004 10:24:54   YINGBAOL
// PTS10032356: force user to set up all fund group for management fee.
// 
//    Rev 1.24   Mar 18 2004 10:45:16   YINGBAOL
// PTS10021889: add FindDeletedOverlapRecord(...) method.
// 
//    Rev 1.23   Aug 22 2003 16:07:40   linmay
// modified doValidateAll for CIBC
// 
//    Rev 1.22   Jun 26 2003 10:30:46   linmay
// modified doValidateAll for Pinnacle Flat Fee
// 
//    Rev 1.21   Jun 20 2003 16:59:24   linmay
// fix bug
// 
//    Rev 1.20   Jun 20 2003 16:24:46   linmay
// added for flatFee
// 
//    Rev 1.19   Apr 09 2003 10:55:20   VADEANUM
// PTS# 10015557 Sort Records by date in descending order.
// 
//    Rev 1.18   Apr 01 2003 15:47:32   PURDYECH
// Sync back to trunk
// 
//    Rev 1.17   Mar 21 2003 18:09:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Mar 10 2003 14:47:22   linmay
// modified doValidateAll
// 
//    Rev 1.15   Feb 21 2003 14:37:32   YINGBAOL
// fix validateall
// 
//    Rev 1.14   Jan 03 2003 19:43:06   YINGBAOL
// change FundGroup to CommGroup
// 
//    Rev 1.13   Jan 03 2003 16:25:34   linmay
// rename CommGroupCode to FundGroup
// 
//    Rev 1.12   Jan 03 2003 14:46:44   linmay
// modified doValidateAll
// 
//    Rev 1.11   Jan 02 2003 15:22:56   linmay
// modified getStrKey(), doValidateAll
// 
//    Rev 1.10   Oct 09 2002 23:54:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Aug 29 2002 12:55:50   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   22 May 2002 18:28:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   Mar 19 2002 16:51:26   YINGBAOL
// take off check status in validate all
// 
//    Rev 1.6   Mar 08 2002 10:11:42   YINGBAOL
// samll fix
// 
//    Rev 1.5   Mar 05 2002 14:07:08   YINGBAOL
// check status in validateall
// 
//    Rev 1.4   Feb 28 2002 12:47:24   YINGBAOL
// sort list
// 
//    Rev 1.3   Feb 26 2002 11:34:58   YINGBAOL
// samll fix
// 
//    Rev 1.2   Feb 25 2002 18:55:42   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.1   Feb 22 2002 14:18:44   YINGBAOL
// more function added
// 
//    Rev 1.0   Feb 01 2002 15:16:14   YINGBAOL
// Initial revision.
 * 

*/


