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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BrokerAMS.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : BrokerAMS
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "BrokerAMS.hpp"
#include "BrokerAMSList.hpp"
#include "AMSmstrlist.hpp"
#include "AmsMstrInfo.hpp"

#include "AmsFundAllocList.hpp"
#include <ifastdataimpl\dse_dstc0250_vw.hpp>
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

namespace CND
{  
	extern const long	ERR_DUPLICATE_AMSCODE;
	extern const long	ERR_INVALID_AMSCODE;
	extern const long	ERR_AMS_GRAND_FATHER_DATED;
	extern const long	ERR_AMS_CODE_FOR_BROKER_IS_FUTURE_DATED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId AMSType;
   extern CLASS_IMPORT const BFTextFieldId EnglishShortName;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "BrokerAMS" );
   const I_CHAR * const AMSFUNDALLOCATIONLIST = I_("AmsFundAllocList");
   const I_CHAR * const BAD = I_("N");
   const I_CHAR * CODE_AMSTYPE_REBALANCING = I_("RB");
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   //{ ifds::BrokerCode, BFCBO::NONE, 0 }, 
   //{ ifds::rxAMSCode,       BFCBO::NONE, 0 }, 
   { ifds::AMSCode,		 BFCBO::REQUIRED, 0 },
   { ifds::AMSName,         BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,   BFCBO::REQUIRED, 0 }, 
   { ifds::BrokerAMSVer,    BFCBO::NONE, 0 }, 
   { ifds::BrokerAMSRId,    BFCBO::NONE, 0 }, 
   { ifds::ProcessDate,	 BFCBO::NONE, 0 }, 
   { ifds::Username,		 BFCBO::NONE, 0 },
   { ifds::ModDate,		 BFCBO::NONE, 0 },
   { ifds::ModUser,		 BFCBO::NONE, 0 },
   { ifds::GoodBad,		 BFCBO::REQUIRED, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

//******************************************************************************
BrokerAMS::BrokerAMS( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, pBrokerAMSList( NULL )
{

   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       (const CLASS_OBJECT_INFO *)0 );
}

//******************************************************************************
BrokerAMS::~BrokerAMS()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY BrokerAMS::doValidateField( const BFFieldId& idField,
                                   const DString& strValue,
                                   const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;
   if(idField == ifds::AMSCode )
   {
	   svrn = validateAMSCode(strValue,idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMS::setField(const BFFieldId& idField, const DString& dstrValue,
                         const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));
   
   BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);

   if(idField == ifds::AMSName)
   {
		setUpdatedFlag( ifds::AMSName, idDataGroup, false );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY  BrokerAMS::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreSetField" ) );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY BrokerAMS::init( BrokerAMSList* brokeramsList, const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   pBrokerAMSList = brokeramsList;
   attachDataObject(const_cast<BFData&>(InstData), false, true );  

   DString dstrStatus = InstData.getElementValue( ifds::GoodBad );
   if( dstrStatus == BAD )
   {
      setFieldReadOnly( ifds::AMSCode, BF::HOST, true );
      setFieldReadOnly( ifds::EffectiveDate, BF::HOST, true );
      //setFieldReadOnly( ifds::GoodBad, BF::HOST, true );
   }

   clearUpdatedFlags( BF::HOST, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMS::init( BrokerAMSList* brokeramsList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,long)" ) );
   pBrokerAMSList = brokeramsList;	

   DString dstrCurDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurDate, idDataGroup ,false );
   setFieldNoValidate( ifds::EffectiveDate, dstrCurDate, idDataGroup, false );
   
   setDefault();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMS::setDefault()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefault" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void BrokerAMS::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreValidateAll" ) );
   if (isNew())
	{
		setFieldNoValidate( ifds::GoodBad, I_("Y"), idDataGroup, false );
		setFieldReadOnly( ifds::GoodBad, idDataGroup, true );
	}
   return;
}

//******************************************************************************
SEVERITY BrokerAMS:: doPreValidateAll( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreValidateAll" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMS:: getAMSFundAllocList( AmsFundAllocList *&pAmsFundAllocList,
				const BFDataGroupId& idDataGroup,bool bCreate /*= true*/,bool bDelExist /* false */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSFundAllocList") );
   pAmsFundAllocList = NULL;

   pAmsFundAllocList = dynamic_cast<AmsFundAllocList*>(getObject( AMSFUNDALLOCATIONLIST, idDataGroup ) );
   DString strAMSCode,dstrCurDate;
   getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
	strAMSCode.strip().upperCase();
   getWorkSession().getDateInHostFormat(dstrCurDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
		idDataGroup);   
  if( bDelExist )
  {
	  pAmsFundAllocList = NULL;
  	  setObject( pAmsFundAllocList, AMSFUNDALLOCATIONLIST, OBJ_ACTIVITY_NONE, idDataGroup );	//just inquiry  
  }	
  if(strAMSCode!=NULL_STRING && !pAmsFundAllocList && bCreate)
   {
		AMSMstrList  mAMSMstrList(*this);
		AmsMstrInfo* pAMSMstrInfo = NULL;
		DString dstrEffectiveDate;
		getField( ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false );
		mAMSMstrList.getAMSMstrInfo ( CODE_AMSTYPE_REBALANCING,strAMSCode, dstrEffectiveDate,pAMSMstrInfo,idDataGroup );
		if( pAMSMstrInfo ){
			pAMSMstrInfo->getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);
		}
	  	  
		pAmsFundAllocList = new AmsFundAllocList( *this );
	   pAmsFundAllocList->setField(ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false);
	   pAmsFundAllocList->setField(ifds::AMSCode, strAMSCode, BF::HOST, false);
	   pAmsFundAllocList->setField(ifds::AMSType, CODE_AMSTYPE_REBALANCING, BF::HOST, false);
	   if( pAmsFundAllocList->initExisting() <= WARNING )
			 setObject( pAmsFundAllocList, AMSFUNDALLOCATIONLIST, OBJ_ACTIVITY_NONE, idDataGroup );	//just inquiry
	   else
	   {
			 delete pAmsFundAllocList;
			 pAmsFundAllocList = NULL;
	   }

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerAMS::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;  

   if( idField == ifds::AMSCode )
   {
      DString strAMSCode, strAmsName;
      getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
      strAMSCode.upperCase();

	   if(strAMSCode != NULL_STRING )
	   {
			AMSMstrList  mAMSMstrList(*this);
			AmsMstrInfo* pAMSMstrInfo = NULL;
			DString dstrCurDate;
			getField( ifds::EffectiveDate,dstrCurDate,idDataGroup,false );
 			mAMSMstrList.getAMSMstrInfo ( CODE_AMSTYPE_REBALANCING,strAMSCode, dstrCurDate,pAMSMstrInfo,idDataGroup );
			if( pAMSMstrInfo ){
				pAMSMstrInfo->getField( ifds::EnglishShortName, strAmsName, idDataGroup, false );
				setField(ifds::AMSName, strAmsName, idDataGroup, false, false);
			}
	   }
   }
	else if ( idField ==  ifds::EffectiveDate )  // when user change effective date we should mark AMSCode as invalid
	{
		setFieldUpdated( ifds::AMSCode, idDataGroup, true );
		setFieldValid( ifds::AMSCode, idDataGroup, false );	
	}
   return(GETCURRENTHIGHESTSEVERITY());
};

//****************************************************************************************
SEVERITY BrokerAMS::validateAMSCode(const DString& strValue,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSCode") );
   DString strAmsCode(strValue);
	strAmsCode.strip().upperCase();

	AMSMstrList mAMSMstrList( *this );
	DString dstrCurDate = NULL;
	AmsMstrInfo* pAMSMstrInfo = NULL;
	getField( ifds::EffectiveDate,dstrCurDate,idDataGroup,false );
	mAMSMstrList.getAMSMstrInfo ( CODE_AMSTYPE_REBALANCING,strAmsCode, dstrCurDate,pAMSMstrInfo,idDataGroup );	
	if( pAMSMstrInfo ){
		if( pAMSMstrInfo->isGrandFatherDateStamped(idDataGroup ) )
		{
		 //add condition here.
			ADDCONDITIONFROMFILE( CND::ERR_AMS_GRAND_FATHER_DATED );

		}
	}
	else
	{
		ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMSCODE );	
		return  GETCURRENTHIGHESTSEVERITY();	
	
	}
	bool bExist = (dynamic_cast<BrokerAMSList*>(getParent()) )->isAMSCodeValid(strAmsCode, idDataGroup,true );
    if( bExist )
	{
      DString strTemp;                 
      addIDITagValue( strTemp, I_("AMSCODE"), strAmsCode);         
      ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_AMSCODE, strTemp );	
		return  GETCURRENTHIGHESTSEVERITY();
	}


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BrokerAMS::validateBrokerAMSDeff( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerAMSDeff") );

	DString dstrBrokerCode;
	getParent()->getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup );

	DString dstrAMSCode, dstrDate;
   getField( ifds::AMSCode,       dstrAMSCode, idDataGroup, false );
   getField( ifds::EffectiveDate, dstrDate,    idDataGroup, false );
   
   DString dstrCurrBusDate;
	if( getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ) <= WARNING )
	{	
		DSTCommonFunctions::DATE_ORDER dateOrder = DSTCommonFunctions::CompareDates( dstrDate, dstrCurrBusDate );
      if ( !(dateOrder == DSTCommonFunctions::FIRST_EARLIER || dateOrder == DSTCommonFunctions::EQUAL) )
		{
			// BrokerAMS Effective Date is in the future			
			DString dstrIDITagValue;
			addIDITagValue( dstrIDITagValue, I_( "BROKER_CODE") , dstrBrokerCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_CODE_FOR_BROKER_IS_FUTURE_DATED, dstrIDITagValue );
		}
   }	

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerAMS.cpp-arc  $
// 
//    Rev 1.21   Nov 14 2004 14:29:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.20   Nov 25 2003 16:19:20   YINGBAOL
// PTS24345 
// 
//    Rev 1.19   Nov 20 2003 17:10:40   ZHANGCEL
// PTS 10023667:Added logic for 1) to allow user to switch the status between bad and good as long as the record is not a new one;2)not allow user to switch the status to 'Bad' for new record.
// 
//    Rev 1.18   Nov 05 2003 11:36:26   VADEANUM
// PTS 10023031 - Unable to assign pre-existing AMS model to account AMS - Added validateBrokerAMSDeff()
// 
//    Rev 1.17   Aug 20 2003 15:38:02   YINGBAOL
// take AMSName from English short name from AMSMstr List
// 
//    Rev 1.16   Aug 19 2003 14:25:24   YINGBAOL
// add condition for grandfather dated
// 
//    Rev 1.15   Aug 08 2003 10:25:24   YINGBAOL
// Change AMSMstrlist and fix some other ossues
// 
//    Rev 1.14   Jul 23 2003 11:01:58   linmay
// modified for cibc
// 
//    Rev 1.13   Jun 19 2003 13:34:12   HERNANDO
// PTS 10018460 - Name was displaying AMS Code.  Name now displays Name/Description.
// 
//    Rev 1.12   Jun 19 2003 11:30:36   HERNANDO
// PTS 10018460 - Fixed Name display.
// 
//    Rev 1.11   Jun 17 2003 11:54:08   HSUCHIN
// PTS 10018381 - bug fix with error message.
// 
//    Rev 1.10   Apr 21 2003 09:45:52   YINGBAOL
// change getFieldByAMSCode sync.
// 
//    Rev 1.9   Apr 16 2003 11:32:04   FENGYONG
// Add more button
// 
//    Rev 1.8   Apr 04 2003 10:25:26   FENGYONG
// AMSType must be RB for fundallocation call
// 
//    Rev 1.7   Apr 03 2003 10:08:00   FENGYONG
// Add effectivedate validation
// 
//    Rev 1.6   Mar 27 2003 11:15:00   FENGYONG
// When status is bad set record readonly
// 
//    Rev 1.5   Mar 25 2003 11:21:52   FENGYONG
// sync up with branch
// 
//    Rev 1.4   Mar 21 2003 18:01:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Mar 14 2003 15:33:24   FENGYONG
// set updatestatus for AMSName
// 
//    Rev 1.2   Mar 13 2003 18:31:26   FENGYONG
// Add validation duplicate check
// 
//    Rev 1.1   Mar 07 2003 16:45:44   FENGYONG
// groupid fix
// 
//    Rev 1.0   Mar 03 2003 16:33:42   FENGYONG
// Initial revision.
 * 
 */