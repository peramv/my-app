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
//    Copyright 2005 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : AcctCutOffTimes.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "AcctCutOffTimes.hpp"
#include "AcctCutOffTimesList.hpp"
#include "mgmtco.hpp"
#include "FundGroupSubList.hpp"
#include "FundMasterList.hpp"
#include "FundDetailList.hpp"
#include "funddetail.hpp"

#include <ifastdataimpl\dse_dstc0348_vw.hpp>
#include <ifastdataimpl\dse_dstc0348_req.hpp>

namespace
{
	const I_CHAR * const CLASSNAME	= I_( "AcctCutOffTimes" );
	const I_CHAR * const NETSENDERLEVEL	= I_( "02" );    
}

namespace CND
{  
	extern const long ERR_INVALID_FUND_CLASS_CODES;
	extern const long ERR_INVALID_FUND_NUMBER;
}

namespace ifds
{  
	extern CLASS_IMPORT const BFTextFieldId CutOffLevel;
	extern CLASS_IMPORT const BFTextFieldId FundNumber;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   { ifds::CutOffTime,          BFCBO::NONE,		0 }, 
   { ifds::CutOffTimeType,      BFCBO::REQUIRED,    0 },
   { ifds::FundGroup,           BFCBO::NONE,	    0 }, 
   { ifds::FundNumber,          BFCBO::NONE,	    0 }, 
   { ifds::FundCode,            BFCBO::NONE,		0 }, 
   { ifds::ClassCode,           BFCBO::NONE,		0 }, 
   { ifds::TimeZoneCode,        BFCBO::NONE,        0 }, 
   { ifds::CutOffDays,          BFCBO::NONE,        0 }, 
   { ifds::CutOffLevel,         BFCBO::NONE,        0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

AcctCutOffTimes::AcctCutOffTimes( BFAbstractCBO &parent , const DString& cutOffLevel)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

	setFieldNoValidate( ifds::CutOffLevel, cutOffLevel, BF::HOST, false);
	initSubSets();
}

//******************************************************************************

AcctCutOffTimes::~AcctCutOffTimes()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY AcctCutOffTimes::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject(const_cast<BFData&>(data), false);  
	initSubSets();

	DString dstrFundCode, dstrClassCode;

	BFCBO::getField(ifds::FundCode, dstrFundCode, BF::HOST);
	BFCBO::getField(ifds::ClassCode, dstrClassCode, BF::HOST);

	if (!dstrFundCode.empty () && !dstrClassCode.empty ())
	{
		dstrFundCode.strip ().upperCase();
		dstrClassCode.strip ().upperCase();

		setFundByFundClass (BF::HOST, dstrFundCode, dstrClassCode);
	}

	setRequiredFields (BF::HOST);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AcctCutOffTimes::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void AcctCutOffTimes::initSubSets()
{
	FundGroupSubList *pFundGroupSubList = NULL;
	bool fundclassexist = false;
	if(getMgmtCo().getFundGroupSubList( pFundGroupSubList, I_("VALN") ) <= WARNING )
	{
		if (pFundGroupSubList)
		{
            dstrFundGroupList = pFundGroupSubList->getFundGroupSubList( I_("VALN") );
        
			if( !dstrFundGroupList.empty() )
			{
               setFieldAllSubstituteValues( ifds::FundGroup, BF::HOST, dstrFundGroupList );
            }
		}
	}
}

//******************************************************************************

void AcctCutOffTimes::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   setFieldNoValidate( ifds::CutOffTime, I_("00:00"), idDataGroup, false, false, true, false );
   setFieldNoValidate( ifds::CutOffDays, I_("0"), idDataGroup, false, false, true, false );
   initSubSets();
}

//******************************************************************************
SEVERITY AcctCutOffTimes::setFundByFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByFundNumber" ) );

	FundDetailList* pFundDetailList = NULL;

	if (getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
	{
		FundDetail* pFundDetail = pFundDetailList->getFundDetailByFundNumber (dstrFundNumber);

		if (pFundDetail != NULL)
		{
			DString dstrFundCode, dstrClassCode;

			pFundDetail->getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
			pFundDetail->getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);
						
			//set fields to cbo
			setFieldNoValidate(ifds::FundCode, dstrFundCode, idDataGroup, false, true, true, false );
			setFieldNoValidate(ifds::ClassCode, dstrClassCode, idDataGroup, false, true, true, false);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY AcctCutOffTimes::setFundByFundClass( const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode  )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByFundClass" ) );

	if (!dstrFundCode.empty () && !dstrClassCode.empty ())
	{
		DString dstrFundNumber;

		getWorkSession().GetFundNumber(dstrFundCode, dstrClassCode, dstrFundNumber);
		
		//set field to cbo
		setFieldNoValidate(ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY AcctCutOffTimes::validateFundCode (const BFDataGroupId &idDataGroup, const DString &dstrFundCode)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCode"));

	bool bValidFundCode = false;

	if (!dstrFundCode.empty() )
	{
		FundMasterList *pFundMasterList;
			
		getMgmtCo().getFundMasterList (pFundMasterList);

		if( pFundMasterList != NULL && !dstrFundCode.empty() )
		{
			if( pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) == false )
			{
				ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
			}
		}
	}		

	return GETCURRENTHIGHESTSEVERITY ();
}
//**********************************************************************************
SEVERITY AcctCutOffTimes::validateFundNumber(const BFDataGroupId& idDataGroup)
{
	MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundNumber") );

	FundDetail* pFundDetail = NULL;
	FundDetailList* pFundDetailList = NULL;

	if (getWorkSession().getMgmtCo().getFundDetailList( pFundDetailList ) <= WARNING)
	{
		DString dstrFundNumber;

		getField (ifds::FundNumber, dstrFundNumber, idDataGroup);
		dstrFundNumber.strip ().upperCase ();

		pFundDetail = pFundDetailList->getFundDetailByFundNumber (dstrFundNumber);

		if (!dstrFundNumber.empty () && pFundDetail == NULL)
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_NUMBER);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************** 
SEVERITY AcctCutOffTimes::validateClassCode (const BFDataGroupId &idDataGroup, const DString &dstrClassCode)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode"));

	bool bValidFundClassCode = false;
	DString dstrFundCode;

	getField (ifds::FundCode, dstrFundCode, idDataGroup);
	dstrFundCode.strip ().upperCase ();

	if (!dstrFundCode.stripAll ().empty() && !dstrClassCode.empty ())
	{
		FundDetailList *pFundDetailList = NULL;

		if (getMgmtCo().getFundDetailList( pFundDetailList ) <= WARNING && pFundDetailList != NULL)
		{
			FundDetail *pFundDetail = NULL;
			if (pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail != NULL)
				bValidFundClassCode = true;
		}
	}

	if (!bValidFundClassCode)
	{
		ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}
//********************************************************************************************
SEVERITY AcctCutOffTimes::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if (idField == ifds::FundGroup)
	{     
		DString dstrFundGroup;
		getField (ifds::FundGroup, dstrFundGroup, idDataGroup);
		
		if (!dstrFundGroup.empty ())
		{
			// blank out fund number/fund/class.
			setFieldNoValidate( ifds::FundCode, I_( "" ), idDataGroup, false, false, true, false);			
			setFieldNoValidate( ifds::FundNumber, I_( "" ), idDataGroup, false, false, true, false);			
			setFieldNoValidate( ifds::ClassCode, I_( "" ), idDataGroup, false, false, true, false);		
		}
	}
	else if (idField == ifds::FundCode || idField == ifds::ClassCode)
	{
		DString		dstrFundCode, dstrFundNumber, dstrClassCode;

		getField (ifds::FundCode, dstrFundCode, idDataGroup);
		getField (ifds::ClassCode, dstrClassCode, idDataGroup);
		setFundByFundClass (idDataGroup, dstrFundCode, dstrClassCode);
		// blank out fund group
		setFieldNoValidate (ifds::FundGroup, I_( "" ), idDataGroup, false, false, true, false); 

	}
	else if (idField == ifds::FundNumber)
	{
		DString dstrFundNumber;
   			
		getField(ifds::FundNumber, dstrFundNumber, idDataGroup);
		setFundByFundNumber (idDataGroup, dstrFundNumber);
		// blank out fund group 
		setFieldNoValidate (ifds::FundGroup, I_( "" ), idDataGroup, false, false, true, false); 
	}
 
	setRequiredFields (idDataGroup);

   	return GETCURRENTHIGHESTSEVERITY();

}
//********************************************************************************************
void AcctCutOffTimes::setRequiredFields (const BFDataGroupId& idDataGroup)
{
	DString		dstrFundGroup, dstrCutOffLevel;
	DString		dstrFundCode, dstrClassCode;

	getField (ifds::FundCode, dstrFundCode, idDataGroup);
	getField (ifds::ClassCode, dstrClassCode, idDataGroup);
	getField (ifds::FundGroup, dstrFundGroup, idDataGroup);

	bool bRequired = false;

	if (dstrFundGroup.empty () && dstrFundCode.empty () && dstrClassCode.empty ())
	{
		bRequired = true;
	}

	setFieldRequired(ifds::FundGroup, idDataGroup, bRequired);
	setValidFlag(ifds::FundGroup, idDataGroup, !bRequired);

	getField (ifds::CutOffLevel, dstrCutOffLevel, idDataGroup);

	setFieldRequired(ifds::FundCode, idDataGroup, bRequired);
	setValidFlag(ifds::FundCode, idDataGroup, !bRequired);
	setFieldRequired(ifds::ClassCode, idDataGroup, bRequired);
	setValidFlag(ifds::ClassCode, idDataGroup, !bRequired);

    setFieldAllSubstituteValues( ifds::FundGroup, idDataGroup, dstrFundGroupList );
}
//********************************************************************************************

SEVERITY AcctCutOffTimes::doValidateField( const BFFieldId& idField,
                                           const DString& strValue,
                                           const BFDataGroupId& idDataGroup )

{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
	
	if (idField == ifds::FundCode)
	{
		DString dstrFundCode;
		getField (ifds::FundCode, dstrFundCode, idDataGroup);

		dstrFundCode.strip ().upperCase ();
		validateFundCode (idDataGroup, dstrFundCode);
	}
	else if (idField == ifds::ClassCode)
	{
 	   	DString dstrClassCode;
		getField (ifds::ClassCode, dstrClassCode, idDataGroup);

		dstrClassCode.strip ().upperCase ();
		validateClassCode (idDataGroup, dstrClassCode);
	}
	else if (idField == ifds::FundNumber)
	{
		validateFundNumber (idDataGroup);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}
//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCutOffTimes.cpp-arc  $
// 
//    Rev 1.2   Jul 26 2006 14:52:52   jankovii
// PET 2192 FN02 - Dealings Sender Cut Off Time.
// 
//    Rev 1.1   Jul 21 2006 14:06:52   jankovii
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.0   Jul 05 2005 17:16:44   hernando
// Initial revision.
