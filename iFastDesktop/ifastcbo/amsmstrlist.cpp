//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : AMSMstrList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov 7,2002
//
//********************************************************************************
#include "stdafx.h"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

#include "AmsMstrList.hpp"
#include "AmsMstrInfo.hpp"
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_MASTER_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME			= I_( "AmsMstrList" );
   const I_CHAR * const YES					= I_( "Y" );
   const I_CHAR * const NO						= I_( "N" );
   const I_CHAR * const AMSCODE				= I_( "AMSCode" );
   const I_CHAR * const EFFECTIVEDATE		= I_( "EffectiveDate" );
   const I_CHAR * const INQUIRYDATE			= I_( "InquiryDate" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_AMS_CODE_IN_USE;
   extern const long ERR_DUPLICATE_AMSCODE;
   extern const long ERR_AMS_CODE_SET_UP;
   extern const long ERR_AMS_CODE_RESTRICTED;

}

namespace ifds
{
	 extern CLASS_IMPORT const BFTextFieldId    AMSDupCheck;

}
//******************************************************************************

AMSMstrList::AMSMstrList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),_requestData(ifds::DSTC0179_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
AMSMstrList::~AMSMstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
	setDate.clear();
}  
//******************************************************************************

SEVERITY AMSMstrList::init(	const DString& dstrAmsType,
							const DString& dstrAmsCode,
							const DString& dstrEffectiveDate,
							const BFDataGroupId& idDataGroup,
							bool  bDupCheck /*= false*/,
							bool  ignoreDataNotFound /*= false*/,
							const DString& dstrTrack /* = I_("N")*/,
							const DString& dstrPageName /*= NULL_STRING */
						  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   _dstrAmsCode = dstrAmsCode;
   _dstrEffectiveDate = dstrEffectiveDate;
   DString strAMSType;	

   if(dstrAmsType == NULL_STRING )
	{
		getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, 
         strAMSType, idDataGroup, false);
		strAMSType.strip().upperCase();
		strAMSType += I_(',');
		int iPos =  strAMSType.find_first_of(I_(",") );
		_dstrAmsType = strAMSType.left(iPos);
	}
	else
	{	
		_dstrAmsType = dstrAmsType;
	}
   _requestData.setElementValue(ifds::NextKey, NULL_STRING);
   _requestData.setElementValue(ifds::Track, dstrTrack);
   _requestData.setElementValue(ifds::Activity, dstrPageName);
   _requestData.setElementValue(ifds::AMSCode, _dstrAmsCode);
   _requestData.setElementValue(ifds::AMSType, _dstrAmsType);
   _requestData.setElementValue(ifds::EffectiveDate, _dstrEffectiveDate);
 //  _requestData.setElementValue(ifds::ExactMatch, YES);
   _requestData.setElementValue(ifds::AMSDupCheck, bDupCheck?YES:NO);

	
   DString mgmtCoIdOut;

   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::AMS_MASTER_LIST, _requestData, ifds::DSTC0179_VW, 
      DSTCRequestor(getSecurity(), false, !ignoreDataNotFound) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSMstrList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::AMS_MASTER_LIST, _requestData, 
         ifds::DSTC0179_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AMSMstrList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY AMSMstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new AmsMstrInfo( *this );
   ((AmsMstrInfo*) pObjOut)->init( data);
   return(GETCURRENTHIGHESTSEVERITY());
}
//**************************************************************************************
SEVERITY AMSMstrList::doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new AmsMstrInfo( *this );
   ((AmsMstrInfo*) pObjOut)->initNew( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY AMSMstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   BFObjIter iter2( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrAMSCode1, dstrAMSCode2, dstrEffectiveDate1,dstrEffectiveDate2;
   DString dstrGFDate1, dstrGFDate2;
   	DString dstrDefaultDate;
	getWorkSession().getDateInHostFormat(dstrDefaultDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   while( !iter1.end() )
	{
	   BFAbstractCBO* cbo1 = iter1.getObject();
	   if ( !iter1.isDummy() )
	   {

			cbo1->getField(ifds::AMSCode,dstrAMSCode1,idDataGroup,false );
			cbo1->getField(ifds::EffectiveDate,dstrEffectiveDate1,idDataGroup,false );
			cbo1->getField(ifds::GrandFatheredDate,dstrGFDate1,idDataGroup,false );

			dstrAMSCode1.strip().upperCase();
			dstrEffectiveDate1.strip();
			iter2.positionByKey( iter1.getStringKey() );
			++iter2;
			for( iter2; !iter2.end(); ++iter2 )
			{
				BFAbstractCBO* cbo2 = iter2.getObject();
			    if ( !iter2.isDummy() )
				{
					cbo2->getField(ifds::AMSCode,dstrAMSCode2,idDataGroup,false );
					cbo2->getField(ifds::EffectiveDate,dstrEffectiveDate2,idDataGroup,false );
					cbo2->getField(ifds::GrandFatheredDate,dstrGFDate2,idDataGroup,false );
					dstrAMSCode2.strip().upperCase();
					dstrEffectiveDate2.strip();
					if ( DSTCommonFunctions::CompareDates(dstrGFDate1,dstrDefaultDate ) != DSTCommonFunctions::EQUAL ||
						 DSTCommonFunctions::CompareDates(dstrGFDate2,dstrDefaultDate ) != DSTCommonFunctions::EQUAL)
					{
						if( dstrAMSCode1 == dstrAMSCode2 && ( cbo1->isNew() || cbo2->isNew() ) )
						{
							DString strTemp;                 
							addIDITagValue( strTemp, I_("AMSCODE"), dstrAMSCode1);         
							ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_CODE_RESTRICTED, strTemp);
							return(GETCURRENTHIGHESTSEVERITY());			
						}	

					}
					else
					{
						if( dstrAMSCode1 == dstrAMSCode2 && DSTCommonFunctions::CompareDates(dstrEffectiveDate1,dstrEffectiveDate2 ) == DSTCommonFunctions::EQUAL )
						{
							DString strTemp;                 
							addIDITagValue( strTemp, I_("AMSCODE"), dstrAMSCode1);         
							ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_AMSCODE, strTemp);
							return(GETCURRENTHIGHESTSEVERITY());			
						}	
					}
				}
			}
	   }
	   ++iter1;
	}
   return(GETCURRENTHIGHESTSEVERITY());
}
//***************************************************************************************
bool AMSMstrList::canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

	AmsMstrInfo* pAmsMstrInfo = dynamic_cast<AmsMstrInfo* > (getObject(strKey, idDataGroup) );
	if( pAmsMstrInfo ){
		if(pAmsMstrInfo->isNew() ) return true; // if it is new we allow them to delete
		DString dstrInUse;
		pAmsMstrInfo->getField(ifds::AMSCodeInUse,dstrInUse,idDataGroup,false);
		dstrInUse.strip();
		if( dstrInUse == YES )
		{
			ADDCONDITIONFROMFILE( CND::ERR_AMS_CODE_IN_USE );		
			return false;
		}
	}
   return true;
}
//**********************************************************************************
void  AMSMstrList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrAMSCode, dstrEffectiveDate, dstrSortDate;
	if( data )
	{
		dstrAMSCode = data->getElementValue( I_( "AMSCode" ) );
		dstrAMSCode.strip().upperCase();
		dstrEffectiveDate = data ->getElementValue( I_("EffectiveDate"));
		dstrEffectiveDate.strip();
		DSTCommonFunctions::convertToSortableDateInDec ( dstrEffectiveDate, dstrSortDate );

		strKey = dstrAMSCode;
		strKey += dstrSortDate;

	}
	else 
	{
		BFCBO::getStrKey( strKey , NULL );
	}
}
//************************************************************************************
bool AMSMstrList::isAMSCodeValid(DString& dstrAMSType, DString& dstrAMSCode, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup,bool bValid0001)
{
	bool bValid = false;
	dstrAMSCode.strip();
	if( bValid0001 == false && dstrAMSCode ==  I_("0001") )
		return false;

	DString strKey, strEffectiveDate(dstrEffectiveDate), strAmsCode,strGFDate;
	strKey = dstrAMSCode;

	strKey += strEffectiveDate;

	if( dstrAMSCode != NULL_STRING )
	{	
		//dupcheck for amscode + effectivedate	
		BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
		if(iter.positionByKey( strKey ) )
		{
			bValid = true;	
		}
		else{
			bValid = isAmsCodeExistAtbackEnd(dstrAMSType,dstrAMSCode, strEffectiveDate, idDataGroup );	
		}
	
	}
	return bValid;
}
//********************************************************************************************
bool AMSMstrList::isAmsCodeExistAtbackEnd(const DString& dstrAMSType,const DString& dstrAmsCode, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAmsCodeExistAtbackEnd") );

	BFData requestData(ifds::DSTC0179_REQ);
	DString dstrTrack(NO);
	DString dstrPageName( NULL_STRING );
   requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   requestData.setElementValue( ifds::AMSCode, dstrAmsCode );
   requestData.setElementValue( ifds::AMSType, dstrAMSType );
   requestData.setElementValue( ifds::EffectiveDate, dstrEffectiveDate );
   requestData.setElementValue( ifds::AMSDupCheck, YES );

//	requestData.setElementValue( ifds::ExactMatch, YES );  
	
	DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   SEVERITY sevRtn = SEVERE_ERROR;
	DSTCRequestor requestor( getSecurity(), true, true );
	BFData receivedData(ifds::DSTC0179_VW);
	bool bExist = false;
// the following change is actually back end problem. When we pass RO, 
//	back end can return matching amscode with amstype RO

   BFData *response = new BFData(ifds::DSTC0179_VW);
	sevRtn = BFDataBroker::getInstance()->receive( DSTC_REQUEST::AMS_MASTER_LIST, requestData, *response, requestor );

   if( sevRtn > WARNING )
   {
      delete response;
      response = NULL;
   }
   else
   {
		DString retAMSType;
		response->getRepeat(0).getElementValue(ifds::AMSType,retAMSType );
		retAMSType.strip();
		if(dstrAMSType == retAMSType ){
				attachDataObject( *response, true, true );
				createObjectForEachRepeat( *response );

		}
		else {
			sevRtn = SEVERE_ERROR;
		}
   }

   if( sevRtn <= WARNING )	{
		bExist = true;
	}
	CLEARCONDITIONS();
	return bExist;
}

//******************************************************************
// The method assume that user has already called init2 with ExactMatch =  false.
// it can be used by other screens except AMSGlobal Screen
//
void AMSMstrList::getFieldByAMSCode(const DString& dstrAMSType,const DString& dstrAMSCode, const DString& dstrEffectiveDate, 
					const BFFieldId& idField,DString& strValue,const BFDataGroupId& idDataGroup,bool bFormat ) 
{

	DString strAMSCode( dstrAMSCode ), strKey, strCurBusDate, strEffectiveDate(dstrEffectiveDate) ;
	strAMSCode.strip().upperCase();

	AmsMstrInfo* pAmsMstrInfo = NULL;
   getAMSMstrInfo (dstrAMSType, strAMSCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );


/*	
	
	strKey = strAMSCode;
	if ( strEffectiveDate.empty() )
	{
	   getWorkSession().getDateInHostFormat(strEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, BF::HOST);   
	}

	strKey += strEffectiveDate;
	strValue = NULL_STRING;
	AmsMstrInfo* pAmsMstrInfo = dynamic_cast<AmsMstrInfo* > (getObject(strKey, idDataGroup) );
	if( !pAmsMstrInfo )
    {
		if(isAmsCodeExistAtbackEnd(dstrAMSType,strAMSCode,strEffectiveDate, idDataGroup) )
			pAmsMstrInfo = dynamic_cast<AmsMstrInfo* > (getObject(strKey, idDataGroup) );
	}
*/
	if(pAmsMstrInfo )
    {
      pAmsMstrInfo->getField(idField, strValue, idDataGroup, bFormat );
  
    }
}
//******************************************************************
//  EffectiveDate can not be blank. 
//  bExactMatch is true, view returns single AMS master record, which matches the input parameter 
//  bExactMatch is false, view returns sigle AMS mster record, which is effective as of input EffectiveDate


SEVERITY AMSMstrList::init2(	const DString& dstrAmsType, const DString& dstrAmsCode, 
					bool bExactMatch, const DString& dstrEffectiveDate,const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init - ExactMatch") );

   _dstrAmsCode = dstrAmsCode;
   _dstrAmsType = dstrAmsType;
   _dstrEffectiveDate = dstrEffectiveDate;
   _requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::AMSCode, _dstrAmsCode );
   _requestData.setElementValue( ifds::AMSType, _dstrAmsType );
   _requestData.setElementValue( ifds::EffectiveDate, _dstrEffectiveDate );


	DString dstrKey = dstrAmsType + dstrAmsCode + dstrEffectiveDate;
	setDate.insert( dstrKey );


   if (bExactMatch)
      _requestData.setElementValue( ifds::AMSDupCheck, YES, false, false );  
   else
      _requestData.setElementValue( ifds::AMSDupCheck, NO, false, false );  
   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData(DSTC_REQUEST::AMS_MASTER_LIST, _requestData, ifds::DSTC0179_VW, DSTCRequestor(getSecurity(), false,false) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//********************************************************************************************
void AMSMstrList::AddCopy(
							DString &orgKey, 
							DString &destKey, 
							const BFDataGroupId& idDataGroup
						 )
{
   AmsMstrInfo *pOrgAmsMstrInfo = NULL, *pDestAmsMstrInfo = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == orgKey )
      {
         pOrgAmsMstrInfo = dynamic_cast< AmsMstrInfo * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestAmsMstrInfo = dynamic_cast< AmsMstrInfo * >( Iter.getObject( ) );
      }
   }

   assert ( pOrgAmsMstrInfo && pDestAmsMstrInfo );

   pDestAmsMstrInfo->ModelAMS(pOrgAmsMstrInfo, idDataGroup);
}

//********************************************************************************************
//check if it is Grand Father Stamped
bool AMSMstrList::isAMSCodeEnd(
								 DString& dstrAMSType
							   , DString& dstrAMSCode
							   , const DString& dstrEffectiveDate
							   , const BFDataGroupId& idDataGroup
							   )
{
	bool bEnd = false;
	DString dstrAmsCodeComp, dstrGFStamped;
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter.end() )
	{
    	BFAbstractCBO* cbo1 = iter.getObject();
		iter.getObject()->getField( ifds::AMSCode, dstrAmsCodeComp, idDataGroup, false );
		if ( dstrAmsCodeComp.strip().upperCase() == dstrAMSCode )
		{
			iter.getObject()->getField( ifds::GrandFatherStamped, dstrGFStamped, idDataGroup, false );
			if ( dstrGFStamped == YES )
			{
				bEnd = true;
				break;
			}
		}
		++iter;

	}
	return bEnd;
}
//********************************************************************************************
// the effective date has to be in host format
//
void AMSMstrList::getAMSMstrInfo ( const DString& dstrAMSType,
                                   const DString& dstrAMSCode, 
                                   const DString& dstrInquiryDate,
                                   AmsMstrInfo*& pAMSMstrInfo, 
                                   const BFDataGroupId &idDataGroup)
{
   pAMSMstrInfo = NULL;

   AmsMstrInfo *pTempAmsMstrInfo (NULL);
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED); 
	
   bool bFind (false);
	DString strAMSCode (dstrAMSCode);
	strAMSCode.strip().upperCase();
   DString dstrCurAMSCode, 
      dstrCurDate,
      amsType;
   
   while (!iter.end()) 
   {
      pTempAmsMstrInfo = dynamic_cast <AmsMstrInfo*>(iter.getObject());
      pTempAmsMstrInfo->getField ( ifds::AMSCode, dstrCurAMSCode, idDataGroup );
      pTempAmsMstrInfo->getField ( ifds::EffectiveDate, dstrCurDate, idDataGroup,false );
      pTempAmsMstrInfo->getField ( ifds::AMSType, amsType, idDataGroup,false );
		dstrCurAMSCode.strip().upperCase();
      if (  dstrCurAMSCode == strAMSCode &&
            amsType == dstrAMSType &&
            DSTCommonFunctions::CompareDates ( dstrCurDate,dstrInquiryDate  ) != DSTCommonFunctions::SECOND_EARLIER) 
		{ 
			bFind = true;
         break;
      }
      ++iter;
   } 
	DString dstrKey = dstrAMSType + dstrAMSCode + dstrInquiryDate;
	if ( setDate.find( dstrKey ) == setDate.end() && !bFind  )
	{
		init2( dstrAMSType, dstrAMSCode, false,dstrInquiryDate );			
		getAMSMstrInfo(dstrAMSType,dstrAMSCode,dstrInquiryDate,pAMSMstrInfo, idDataGroup );

	}
	if (bFind)
	{
		pAMSMstrInfo = pTempAmsMstrInfo;
	}
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/amsmstrlist.cpp-arc  $
// 
//    Rev 1.24   Jun 22 2007 14:19:56   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.23   10 Apr 2007 15:31:54   popescu
// Incident 753673 - fixed the AMS object lookup - introduced ams type in the look-up citeria
// 
//    Rev 1.22   Oct 03 2003 15:45:20   linmay
// PTS Ticket #10022449, modified doValidateAll()
// 
//    Rev 1.21   Sep 18 2003 10:19:10   linmay
// PTS Ticket #10021902,
// modified getStrKey()
// 
//    Rev 1.20   Aug 27 2003 13:55:12   linmay
// added condition ERR_AMS_CODE_RESTRICTED;
// 
//    Rev 1.19   Aug 26 2003 14:39:16   linmay
// modified doValidateAll()
// 
//    Rev 1.18   Aug 11 2003 17:22:52   YINGBAOL
// fix getAMSMstrInfo
// 
//    Rev 1.17   Aug 09 2003 12:29:30   YINGBAOL
// change getAMSMstrInfo 
// 
//    Rev 1.16   Jul 25 2003 17:05:50   HSUCHIN
// added support for limit override checks such as stop purchase, stop PAC etc. etc.
// 
//    Rev 1.15   Jul 25 2003 14:20:12   linmay
// modified doValidateAll
// 
//    Rev 1.14   Jul 23 2003 10:59:38   linmay
// modified for cibc
// 
//    Rev 1.13   Jul 18 2003 11:30:36   linmay
// modified for CIBC AMS
// 
//    Rev 1.12   May 27 2003 16:37:46   popescu
// NASU flow AMS :data not found issue fix and removed some memory leaks 
// 
//    Rev 1.11   May 16 2003 18:26:52   YINGBAOL
// promot data not found error message
// 
//    Rev 1.10   Apr 21 2003 09:45:04   YINGBAOL
// view side return us record even if AMSType does not match, the change will fix the issue.
// 
//    Rev 1.9   Apr 15 2003 10:43:56   linmay
// Sync up with 1.7.1.1
// 
//    Rev 1.8   Mar 21 2003 17:59:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Jan 22 2003 17:33:42   YINGBAOL
// change return value
// 
//    Rev 1.6   Jan 15 2003 17:34:08   KOVACSRO
// Added init2
// 
//    Rev 1.5   Jan 08 2003 16:26:18   sanchez
// Change for rebalancing mix:New function getFieldByAMSCode()
// 
//    Rev 1.4   Jan 02 2003 15:16:28   linmay
// modified init(), initnew(), ValidateFundAlloc(), DoApplyRelatedChanges()
// 
//    Rev 1.3   Dec 27 2002 11:33:48   linmay
// modified init function, added AMSType
// 
//    Rev 1.2   Nov 27 2002 11:50:22   YINGBAOL
// added getStrKey 
// 
//    Rev 1.1   Nov 19 2002 13:30:54   YINGBAOL
// added business rules
// 
//    Rev 1.0   Nov 13 2002 10:00:14   YINGBAOL
// Initial Revision
// 

//