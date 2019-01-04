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
//    Copyright 2002 by International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeParamConfig.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Feb.28, 2003
//
// ^CLASS    : FeeParamConfig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeparamConfig.hpp"
#include "feeparamConfigList.hpp"
#include "mgmtco.hpp"
#include "TranslationTable.hpp"
#include <ifastdataimpl\dse_dstc0253_vw.hpp>
#include <ifastdataimpl\dse_dstc0253_req.hpp>



namespace  
{
   const I_CHAR * const CLASSNAME						= I_( "FeeParamConfig" );
   const I_CHAR * const YES								= I_("Y");
	const I_CHAR * const ACCOUNT_LEVEL				= I_("ACCOUNT");
   const I_CHAR * const SYSTEM_LEVEL				= I_("SYSTEM");
   const I_CHAR * const NO_HIGHER_LEVEL_VALID				= I_("NOHIGHERLEVELVALID");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AllowOverrideType;
   extern CLASS_IMPORT const BFTextFieldId HowPaid;
   extern CLASS_IMPORT const BFTextFieldId BasedOn;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFTextFieldId FundGroupType;
   extern CLASS_IMPORT const BFTextFieldId FreqMinMaxApp;
   extern CLASS_IMPORT const BFTextFieldId AppliedMethod;

}



//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FeeCode,                  BFCBO::NONE,                 0 }, 
   { ifds::ShGroupApplicable,        BFCBO::NONE,                 0 }, 
   { ifds::BrokerApplicable,		  BFCBO::NONE,                 0 }, 
   { ifds::BranchApplicable,		  BFCBO::NONE,                 0 }, 
   { ifds::SalesrepApplicable,       BFCBO::NONE,                 0 }, 
   { ifds::FundGroupType,            BFCBO::NONE,                 0 }, 
   { ifds::FundClassApplicable,      BFCBO::NONE,                 0 }, 
   { ifds::FromFundClassApplicable,  BFCBO::NONE,                 0 }, 
   { ifds::FeeTypeList,              BFCBO::NONE,				   0 }, 
   { ifds::BaseOnList,               BFCBO::NONE,				   0 }, 
   { ifds::HowPaidList,              BFCBO::NONE,				   0 }, 
   { ifds::MinMaxFreqList,           BFCBO::NONE,				   0 },
   { ifds::OverrideList,             BFCBO::NONE,                 0 }, 
   { ifds::OnPWApplicable,			  BFCBO::NONE,                 0 }, 
   { ifds::OnFWApplicable,			  BFCBO::NONE,                 0 }, 
   { ifds::FeeSetupLevel,			  BFCBO::NONE,                 0 }, 
   { ifds::FamilyCodeApplicable,	  BFCBO::NONE,                 0 }, 
   { ifds::FeeLevel,				  BFCBO::NONE,                 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeParamConfig::FeeParamConfig( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),bValidHighLevel(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}
//------------------------------------------------------------------------
FeeParamConfig::~FeeParamConfig()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//----------------------------------------------------------------------------------
SEVERITY FeeParamConfig::init(const BFData& data)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  
	DString dstrValidateHighLevel = data.getElementValue(I_("FeeLevel"));
	dstrValidateHighLevel.strip().upperCase();
	int n = dstrValidateHighLevel.find_first_of(I_(','));
	if( n!= DString::npos )
	{
		DString dstrLevel = dstrValidateHighLevel.substr( 0, n );
		dstrValidateHighLevel.erase( 0, n + 1);
		if( dstrLevel == ACCOUNT_LEVEL && dstrValidateHighLevel == NO_HIGHER_LEVEL_VALID )
		{
		
			const_cast<BFData& >(data).setElementValue( ifds::FeeLevel,dstrLevel );
			bValidHighLevel =  false;  //
		}
	}	
	attachDataObject(const_cast<BFData&>(data), false);  


   return(GETCURRENTHIGHESTSEVERITY());
}

//----------------------------------------------------------------------------------
bool FeeParamConfig::isShareholderGroupApplicable()
{
	DString dstrShGroupApplicable;
    getField( ifds::ShGroupApplicable, dstrShGroupApplicable, BF::HOST, false );
	return (dstrShGroupApplicable.strip().upperCase() == YES);
}


//----------------------------------------------------------------------------------
bool FeeParamConfig::isBrokerApplicable()
{
	DString dstrBrokerApplicable;
    getField( ifds::BrokerApplicable, dstrBrokerApplicable, BF::HOST, false );
	return (dstrBrokerApplicable.strip().upperCase() == YES);


}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isBranchApplicable()
{
	DString dstrBranchApplicable;
    getField( ifds::BranchApplicable, dstrBranchApplicable, BF::HOST, false );
	return (dstrBranchApplicable.strip().upperCase() == YES);

}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isSalesRepApplicable()
{
	DString dstrSalesrepApplicable;
    getField( ifds::SalesrepApplicable, dstrSalesrepApplicable, BF::HOST, false );
	return (dstrSalesrepApplicable.strip().upperCase() == YES);

}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isFundClassApplicable()
{
	DString dstrFundClassApplicable;
    getField( ifds::FundClassApplicable, dstrFundClassApplicable, BF::HOST, false );
	return (dstrFundClassApplicable.strip().upperCase() == YES);

}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isFromFundClassApplicable()
{
	DString dstrFromFundApplicable;
    getField( ifds::FromFundClassApplicable, dstrFromFundApplicable, BF::HOST, false );
	return (dstrFromFundApplicable.strip().upperCase() == YES);

}

//----------------------------------------------------------------------------------
bool FeeParamConfig::isOnPWApplicable()
{
	DString dstrOnPWApplicable;
    getField( ifds::OnPWApplicable, dstrOnPWApplicable, BF::HOST, false );
	return (dstrOnPWApplicable.strip().upperCase() == YES);

}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isOnFWApplicable()
{
	DString dstrOnFWApplicable;
    getField( ifds::OnFWApplicable, dstrOnFWApplicable, BF::HOST, false );
	return (dstrOnFWApplicable.strip().upperCase() == YES);

}
//----------------------------------------------------------------------------------
bool FeeParamConfig::isFamilyCodeApplicable()
{
	DString dstrFamilyApplicable;
    getField( ifds::FamilyCodeApplicable, dstrFamilyApplicable, BF::HOST, false );
	return (dstrFamilyApplicable.strip().upperCase() == YES);

}

//----------------------------------------------------------------------------------
void FeeParamConfig::getFundGroupType(DString &dstrGroupType)
{
	DString dstrFundGroupType;
	getField( ifds::FundGroupType, dstrFundGroupType, BF::HOST, false );
	dstrGroupType = dstrFundGroupType.strip().upperCase();

}
//----------------------------------------------------------------------------------
void FeeParamConfig::getFeeTypeList(DString &dstrFeeTypeList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrFeeTypeList = NULL_STRING;

	getField(ifds::FeeTypeList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::ParamFeeType, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::ParamFeeType,dstrDes,true);
		dstrFeeTypeList += dstrCode+I_("=") + dstrDes + I_(";");
	}	

}

//----------------------------------------------------------------------------------
void FeeParamConfig::getBaseOnList(DString &dstrBaseOnList)
{
	DString dstrGroupCode(NULL_STRING);
	
	dstrBaseOnList = NULL_STRING;

	getField(ifds::BaseOnList,dstrGroupCode,BF::HOST,false);	
	if ( dstrGroupCode.strip() != NULL_STRING)
	{
		dstrGroupCode.upperCase();	
      TranslationTable* pTranslationTable = NULL;
      getMgmtCo().getTranslationTable( dstrGroupCode, pTranslationTable );
      if( pTranslationTable )
      {
         pTranslationTable->getSubstitutionListByCodeAndDescription( dstrBaseOnList );
      }
	}
}

//----------------------------------------------------------------------------------
void FeeParamConfig::getHowPaidList(DString &dstrHowPaidList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrHowPaidList = NULL_STRING;

	getField(ifds::HowPaidList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::HowPaid, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		if (dstrCode == NULL_STRING) continue;
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::HowPaid,dstrDes,true);
		dstrHowPaidList += dstrCode+I_("=") + dstrDes + I_(";");
	}	


}

//----------------------------------------------------------------------------------
void FeeParamConfig::getFundNamesList(DString &dstrFundList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrFundList = NULL_STRING;

	getField(ifds::FundList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::FundList, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		if (dstrCode == NULL_STRING) continue;
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::FundList,dstrDes,true);
		dstrFundList += dstrCode+I_("=") + dstrDes + I_(";");
	}	


}
//----------------------------------------------------------------------------------
void FeeParamConfig::getMinMaxFrqList(DString &dstrMinMaxFrqList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrMinMaxFrqList = NULL_STRING;

	getField(ifds::MinMaxFreqList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::FreqMinMaxApp, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::FreqMinMaxApp,dstrDes,true);
		dstrMinMaxFrqList += dstrCode+I_("=") + dstrDes + I_(";");
	}	

}
//----------------------------------------------------------------------------------
void FeeParamConfig::getOverrideList(DString &dstrOverridsList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrOverridsList = NULL_STRING;

	getField(ifds::OverrideList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::AllowOverrideType, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::AllowOverrideType,dstrDes,true);
		dstrOverridsList += dstrCode+I_("=") + dstrDes + I_(";");
	}	
}

//----------------------------------------------------------------------------------
void FeeParamConfig::getAppliedMethodList(DString &dstrAppliedMethodList)
{
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrAppliedMethodList = NULL_STRING;

	getField(ifds::AppliedMethodList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::AppliedMethod, BF::HOST);

    if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::AppliedMethod,dstrDes,true);
		dstrAppliedMethodList += dstrCode+I_("=") + dstrDes + I_(";");
	}	

}

//----------------------------------------------------------------------------------
bool FeeParamConfig::allowNegativeRate()
{
	DString dstrFeeCode;
    getField(ifds::FeeCode, dstrFeeCode, BF::HOST, false);

    return dstrFeeCode.stripAll() == I_("133"); // CPI Rate
}

//----------------------------------------------------------------------------------
bool FeeParamConfig::isEnvLvlFee() // Environment level fee -> CommGroupCode, fund and class are blank.
{
	DString dstrFeeCode;
    getField(ifds::FeeCode, dstrFeeCode, BF::HOST, false);

    return dstrFeeCode.stripAll() == I_("133"); // CPI Rate
}

//----------------------------------------------------------------------------------
bool FeeParamConfig::isAppliedMethodApplicable()
{
	DString dstrAppliedMethodApplicable;
   getField( ifds::AppliedMethodList, dstrAppliedMethodApplicable, BF::HOST, false );
	return (!dstrAppliedMethodApplicable.strip().empty() );

}

void FeeParamConfig::getChargeOptionList(DString &dstrChargeOptionList)
{
/*
	DString dstrCode,dstrDes, dstrCodeList ;
	dstrCodeList = NULL_STRING;
	dstrChargeOptionList = NULL_STRING;

	getField(ifds::ChargeOptionList,dstrCodeList,BF::HOST,false);
	BFProperties * pBFP = getFieldProperties(ifds::AllowChargeOptionType, BF::HOST);

   if( dstrCodeList != NULL_STRING )
      dstrCodeList += I_(",");

    int iPos =  dstrCodeList.find_first_of(I_(",") );
    while( iPos != DString::npos )
    {
		iPos =  dstrCodeList.find_first_of(I_(",") );
		if( iPos == DString::npos ) break;
		dstrCode = dstrCodeList.left(iPos);
		dstrCodeList = dstrCodeList.right(dstrCodeList.length() - iPos  - 1);
		dstrDes = dstrCode;
		pBFP->formatValue(ifds::AllowChargeOptionType,dstrDes,true);
		dstrChargeOptionList += dstrCode+I_("=") + dstrDes + I_(";");
	}	
*/
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamConfig.cpp-arc  $
// 
//    Rev 1.15   Oct 23 2009 10:44:00   jankovii
// IN 1873069 - R95 P0164824 Based On Field on shows 0 and 1 in the Fee Parameter Screen.
// 
//    Rev 1.14   Sep 01 2006 11:29:28   jankovii
// PET 2236 FN02 - Grandfathering Units for Trailer Purposes.
// 
//    Rev 1.13   Nov 01 2005 09:17:32   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
// 
//    Rev 1.12   Oct 25 2005 13:34:12   AGUILAAM
// PET1243_FN01_ABN AMRO Funds Trailer Fee Processing; additional enhancements (System Level Fee-Parms screen)
// 
//    Rev 1.11   Nov 14 2004 14:40:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Aug 10 2004 11:24:10   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.9   Jan 19 2004 11:30:08   YINGBAOL
// PTS26088: Add isValidateSysLevelApplicable and related logic
// 
//    Rev 1.8   Oct 14 2003 15:33:12   HERNANDO
// Replaced DocumentTypeOverrideList with TranslationTable.
// 
//    Rev 1.7   Aug 30 2003 16:06:46   YINGBAOL
// AMS Fee Calculation enhancement
// 
//    Rev 1.6   Jun 20 2003 16:23:26   linmay
// added FeeLevel field
// 
//    Rev 1.5   Jun 05 2003 11:07:38   linmay
// PTS Ticket#10017812
// 
//    Rev 1.4   May 07 2003 11:39:24   linmay
// modified getBasedOnlist()
// 
//    Rev 1.3   Mar 21 2003 19:00:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2.1.0   Mar 19 2003 17:13:22   linmay
// modified getHowPaidList()
// 
//    Rev 1.2   Mar 18 2003 18:00:26   linmay
// added familyCodeApplicable, etc.
// 
//    Rev 1.1   Mar 10 2003 14:45:42   linmay
// created
// 
//    Rev 1.0   Mar 06 2003 13:54:06   linmay
// Initial Revision
// 
*/
