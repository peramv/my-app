//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : DailyTransactionsFee.cpp
//    ^AUTHOR : Monica Vadeanu
//    ^DATE   : Jan, 2004
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : DailyTransactionsFee
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "dailytransactionsfee.hpp"
#include "dailytransactionsfeelist.hpp"
#include "dstcommonfunction.hpp"
#include "FundDetail.hpp"
#include "FundDetailList.hpp"
#include "fundmaster.hpp"
#include "FundMasterList.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0284_vwrepeat_record.hpp>

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("DailyTransactionsFee");
   const I_CHAR *PERCENT    = I_("1");   
   const I_CHAR *CLASS_HURDLE_RATE  = I_("201"); 
   const I_CHAR *CLASS_FUND_CAT_PF  = I_("08");  
   const I_CHAR *DEFAULT_VALUE     = I_("01"); 
   const long CLASS_EFFECTIVE_HURDLE_RATE = 201;
}

// Conditions 
namespace CND
{  
	extern const long ERR_INVALID_FUND_CLASS_CODES;		
	extern const long ERR_VALUE_BETWEEN_0_AND_100;
	extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;		
	extern const long ERR_DATE_EARLIER_THAN_CURRENT_BUS_DAY;
	extern const long ERR_ADL_FEE_PERCENTAGE_FOR_DEFAULT_RECORD;
    extern const long ERR_FEECODE_NOT_VALID_FOR_NON_PF_FUNDS;
   extern const long ERR_VALUE_NOT_EQUAL_100_PER;
}

// fields
namespace ifds
{
   //field ids used   
	extern CLASS_IMPORT const BFTextFieldId DTFSearchFeeCode;	   
	extern CLASS_IMPORT const BFTextFieldId FundName;
	extern CLASS_IMPORT const BFTextFieldId ElongName1;   
   extern CLASS_IMPORT const BFTextFieldId DuplicateCheck;
   extern CLASS_IMPORT const BFTextFieldId DuplicateExist;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
	extern CLASS_IMPORT const BFTextFieldId DTFRecordType;	
	extern CLASS_IMPORT const BFTextFieldId CompoundDate;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId RecTypeEffDateXEdit;
	extern CLASS_IMPORT const BFTextFieldId IsProcessed;
	extern CLASS_IMPORT const BFTextFieldId FeeType;
    extern CLASS_IMPORT const BFTextFieldId FundSubCat;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              //  Field DD Id,        State Flags,            Group Flags 
	{ifds::RecordType,          BFCBO::REQUIRED,             0 }, 
	{ifds::FeeCode,             BFCBO::REQUIRED,             0 }, 
	{ifds::FundCode,            BFCBO::REQUIRED,             0 }, 
	{ifds::ClassCode,           BFCBO::REQUIRED,             0 }, 
	{ifds::FundName,            BFCBO::NONE,                 0 }, 
	{ifds::EffectiveDate,       BFCBO::REQUIRED,             0 }, 
	{ifds::StopDate,            BFCBO::REQUIRED,             0 }, 
	{ifds::FeeRate,             BFCBO::REQUIRED,             0 }, 
	{ifds::FeeType,             BFCBO::NONE,                 0 }, 
	//cross edits	
	{ifds::FundClass,           BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ifds::CompoundDate,        BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ifds::RecTypeEffDateXEdit, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
DailyTransactionsFee::DailyTransactionsFee(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
  
   addCrossEdit( ifds::FundClass,           ifds::FundCode );
   addCrossEdit( ifds::FundClass,           ifds::ClassCode );

	addCrossEdit( ifds::CompoundDate,        ifds::EffectiveDate );
	addCrossEdit( ifds::CompoundDate,        ifds::StopDate );

	addCrossEdit( ifds::RecTypeEffDateXEdit, ifds::RecordType );
	addCrossEdit( ifds::RecTypeEffDateXEdit, ifds::EffectiveDate );	
}

//******************************************************************************
DailyTransactionsFee::~DailyTransactionsFee()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY DailyTransactionsFee::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);

   DString recordType (viewData.getElementValue (ifds::RecordType)), 
			  feeCode (viewData.getElementValue (ifds::FeeCode)),
           fundCode (viewData.getElementValue (ifds::FundCode)),
           classCode (viewData.getElementValue (ifds::ClassCode)),
           effectiveDate (viewData.getElementValue (ifds::EffectiveDate));

   recordType.stripAll().upperCase();
   feeCode.stripAll().upperCase();
   fundCode.stripAll().upperCase();
   classCode.stripAll().upperCase(); 
   effectiveDate.stripAll().upperCase();

   commonInit( recordType, 
					feeCode, 
					fundCode, 
					classCode, 
					effectiveDate, 
					BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::init( const DString &dstrRecordType, 
												 const DString &dstrFeeCode, 
												 const DString &dstrFundCode,
												 const DString &dstrClassCode, 
												 const DString &dstrEffectiveDate, 
												 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString recordType (dstrRecordType), 
			  feeCode (dstrFeeCode),
			  fundCode (dstrFundCode), 
			  classCode (dstrClassCode),
           effectiveDate (dstrEffectiveDate);

   recordType.stripAll().upperCase();
   feeCode.stripAll().upperCase();
   fundCode.stripAll().upperCase();
   classCode.stripAll().upperCase(); 
   effectiveDate.stripAll().upperCase();

   setFieldNoValidate(ifds::RecordType,    recordType,    idDataGroup, false, false, true, true);
   setFieldNoValidate(ifds::FeeCode,       feeCode,       idDataGroup, false, false, true, true);
   setFieldNoValidate(ifds::FundCode,      fundCode,      idDataGroup, false, false, true, true);
   setFieldNoValidate(ifds::ClassCode,     classCode,     idDataGroup, false, false, true, true);
   setFieldNoValidate(ifds::EffectiveDate, effectiveDate, idDataGroup, false, false, true, true);
   
	commonInit( recordType, 
					feeCode, 
					fundCode, 
					classCode, 
					effectiveDate, 
					idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::commonInit( const DString &dstrRecordType, 
														 const DString &dstrFeeCode, 
														 const DString &dstrFundCode,
													    const DString &dstrClassCode, 
														 const DString &dstrEffectiveDate, 
														 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	setFieldSubstituteValues( ifds::RecordType, idDataGroup, ifds::DTFRecordType );
	setFieldSubstituteValues( ifds::FeeCode,    idDataGroup, ifds::DTFSearchFeeCode );

	DString feeTypeSubstList;

	BFProperties *pBFProperties = getFieldProperties (ifds::FeeType, idDataGroup);
   
	pBFProperties->getAllSubstituteValues (feeTypeSubstList);

	feeTypeSubstList = removeItemFromSubtList (feeTypeSubstList, I_("2"));   
	feeTypeSubstList = removeItemFromSubtList (feeTypeSubstList, I_("3"));   
 
    setFieldAllSubstituteValues (ifds::FeeType, idDataGroup, feeTypeSubstList);

   //the values of the key should be made read only, if not a new object,   
	setFieldReadOnly( ifds::RecordType,    idDataGroup, idDataGroup == BF::HOST );
   setFieldReadOnly( ifds::FeeCode,       idDataGroup, idDataGroup == BF::HOST );			
	setFieldReadOnly( ifds::FundCode,      idDataGroup, idDataGroup == BF::HOST );
   setFieldReadOnly( ifds::ClassCode,     idDataGroup, idDataGroup == BF::HOST );	
   
   // If the fee is processed, only FeeRate is editable.
   DString dstrIsProcessed;
   getField(ifds::IsProcessed, dstrIsProcessed, idDataGroup);
   if ( !isNew() && dstrIsProcessed == I_("Y") )
   {
      setFieldReadOnly( ifds::EffectiveDate, idDataGroup, true );
      setFieldReadOnly( ifds::StopDate, idDataGroup, true);
   }		
		   
	setValidFlag( ifds::RecordType,   idDataGroup, idDataGroup == BF::HOST );  
	setUpdatedFlag( ifds::RecordType, idDataGroup, !(idDataGroup == BF::HOST) );

	setValidFlag( ifds::FundCode,   idDataGroup, idDataGroup == BF::HOST );  
	setUpdatedFlag( ifds::FundCode, idDataGroup, !(idDataGroup == BF::HOST) );

	setValidFlag( ifds::ClassCode,   idDataGroup, idDataGroup == BF::HOST );  
	setUpdatedFlag( ifds::ClassCode, idDataGroup, !(idDataGroup == BF::HOST) );

	setValidFlag( ifds::EffectiveDate,   idDataGroup, idDataGroup == BF::HOST );  
	setUpdatedFlag( ifds::EffectiveDate, idDataGroup, !(idDataGroup == BF::HOST) );
	
	setFundName (idDataGroup);

//some inits that are to be done for host datagroup
   if ( idDataGroup != BF::HOST )
   {
      setEffectiveDate( idDataGroup );		
	}

	setStopDate( idDataGroup );

	setFeeRate( idDataGroup );	
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void DailyTransactionsFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{   	
	setEffectiveDate( idDataGroup );	
	setStopDate( idDataGroup );

	setFieldNoValidate( ifds::FeeType, PERCENT, idDataGroup, true);
}

//******************************************************************************
void DailyTransactionsFee::doReset (const BFDataGroupId &idDataGroup)
{
   if( isNew() )
   {
      init( NULL_STRING, NULL_STRING, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup );
   }
}

//******************************************************************************
SEVERITY DailyTransactionsFee::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if ( idField == ifds::RecTypeEffDateXEdit )
	{
		setStopDate( idDataGroup );			
	}	
   else if (idField == ifds::FundClass)
   {
      setFundName (idDataGroup);
   }
   else if (idField == ifds::FeeType)
   {
	   setFieldNoValidate (ifds::FeeRate, NULL_STRING, idDataGroup,true, true, true, true);
   }
   else if ( ifds::FeeCode == idField )
   {
       DString dstrFeeCode;
       getField(ifds::FeeCode, dstrFeeCode, idDataGroup);
       if(CLASS_HURDLE_RATE ==   dstrFeeCode)
       {
         setFieldNoValidate(ifds::RecordType, DEFAULT_VALUE, idDataGroup, false);
       }
       setFieldReadOnly(ifds::RecordType, idDataGroup , CLASS_HURDLE_RATE ==   dstrFeeCode);
       setFieldNoValidate( ifds::FeeRate, NULL_STRING, idDataGroup, false, true, false, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::doValidateField( const BFFieldId &idField, 
																const DString &strValue, 
																const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   
	if (idField == ifds::FundCode)
   {
		validateFundCode( strValue, idDataGroup );
   }
   else if (idField == ifds::ClassCode)
   {
		validateClassCode( strValue, idDataGroup );
   }
	else if ( idField == ifds::EffectiveDate || idField == ifds::StopDate )
	{
		validateDateAgainstCurrBusDate( strValue, idDataGroup );
	}	
	else if ( idField == ifds::CompoundDate )
	{
		DString dstrRecordType;
		getField( ifds::RecordType, dstrRecordType, idDataGroup );
		if ( I_( "01" ) == dstrRecordType.stripAll() )
			validateEffectiveStopDate( idDataGroup );
	}	
	else if ( idField == ifds:: FeeRate )
	{
		validateFeeRate( strValue, idDataGroup );
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::setFundName( const BFDataGroupId &idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundName"));

   bool blFundNameSet = false;
	DString dstrFundCode, dstrClassCode;
	
   getField (ifds::FundCode,  dstrFundCode,  idDataGroup, false);
   getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);

   if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
   {
		//set field fund name....  		
		FundMasterList *pFundMasterList = NULL;
		if ( getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING &&
			  NULL != pFundMasterList )
		{
			FundMaster *pFundMaster = NULL;
			if ( pFundMasterList->getFundMaster( dstrFundCode, BF::HOST, pFundMaster ) &&
				  NULL != pFundMaster )
			{
				DString dstrFundName;
				pFundMaster->getField( ifds::ElongName1, dstrFundName, BF::HOST );
				
				if ( !dstrFundName.empty() )
				{
					setField( ifds::FundName, dstrFundName, idDataGroup );
					blFundNameSet = true;
				}
			}
		}
   }

	if ( false == blFundNameSet )
		setField( ifds::FundName, I_( "" ), idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::setEffectiveDate( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setEffectiveDate"));

	DString dstrCurrBusDate;
	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

	setFieldNoValidate( ifds::EffectiveDate, dstrCurrBusDate, idDataGroup );

	return GETCURRENTHIGHESTSEVERITY ();
}

//sets the default stop date
//******************************************************************************
SEVERITY DailyTransactionsFee::setStopDate9999( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setStopDate9999"));
   
	DString dstrStopDate;
   getField (ifds::StopDate, dstrStopDate, idDataGroup, false);

   if (dstrStopDate.stripAll () == NULL_STRING)
   {
      getWorkSession ().getDateInHostFormat(dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup );
      setFieldNoValidate (ifds::StopDate, dstrStopDate, idDataGroup, false, true, true);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::setStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setStopDate9999"));
   
	DString dstrRecordType, dstrEffectiveDate;
	getField( ifds::RecordType,    dstrRecordType,    idDataGroup );
	getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );

	// If 'Daily', then Stop Date should be defaulted to Effective Date
	if ( I_( "02" ) == dstrRecordType.stripAll() )
	{
		setFieldNoValidate( ifds::StopDate, dstrEffectiveDate, idDataGroup, false, false, true, true);	
		setFieldReadOnly( ifds::StopDate, idDataGroup, true );
	}
	else if ( I_( "01" ) == dstrRecordType.stripAll() )   // Default
   {
		setStopDate9999 (idDataGroup);
		setFieldReadOnly( ifds::StopDate, idDataGroup, false );
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::setFeeRate( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ( "setFeeRate" ) );

   // As per Backdate ADL fee mini enhancement, FeeRate field should be always modifiable.
   // This function is kept just for further modification.
   
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::doValidateAll( const BFDataGroupId &idDataGroup, 
															 long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	DailyTransactionsFeeList *pDailyTransactionsFeeList = dynamic_cast<DailyTransactionsFeeList*>( getParent( ) );      
	if ( NULL != pDailyTransactionsFeeList && hasNonHostUpdates( ) )
	{	
		DString dstrRecordType, dstrFeeRate;
		getField( ifds::RecordType, dstrRecordType, idDataGroup, false );
		getField( ifds::FeeRate,    dstrFeeRate,    idDataGroup );
		double dblPercent = DSTCommonFunctions::convertToDouble( dstrFeeRate );

		// 0 Percent can be entered waiving the fee for the effective date and it should only be allowed if 
		// Fund/Class has a default fee rate
		if ( dblPercent == 0 && I_( "02" ) == dstrRecordType.stripAll() )
		{
			//check if Default rate exists			
			pDailyTransactionsFeeList->checkDefaultExists( this, idDataGroup );
		}


		DString dstrOrigRecordType, 
			     dstrOrigFeeCode, 
				  dstrOrigFundCode, 
				  dstrOrigClassCode, 
				  dstrOrigEffectiveDate, 
				  dstrOrigStopDate;
		getFieldBeforeImage( ifds::RecordType,    dstrOrigRecordType );
      getFieldBeforeImage( ifds::FeeCode,       dstrOrigFeeCode );
      getFieldBeforeImage( ifds::FundCode,      dstrOrigFundCode );
      getFieldBeforeImage( ifds::ClassCode,     dstrOrigClassCode );
      getFieldBeforeImage( ifds::EffectiveDate, dstrOrigEffectiveDate );
		getFieldBeforeImage( ifds::StopDate,      dstrOrigStopDate );

		DString dstrFeeCode, 
				  dstrFundCode, 
				  dstrClassCode, 
				  dstrEffectiveDate,
				  dstrStopDate;				  		
      getField( ifds::FeeCode,       dstrFeeCode,       idDataGroup, false);
      getField( ifds::FundCode,      dstrFundCode,      idDataGroup, false);
      getField( ifds::ClassCode,     dstrClassCode,     idDataGroup, false);
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);		
		getField( ifds::StopDate,      dstrStopDate,      idDataGroup, false);		

		//check duplicate if any of the key components has been modified 
		// or if it's a new record
		if ( isNew() || 
			  ( dstrOrigRecordType.stripAll()    != dstrRecordType.stripAll() ||
			    dstrOrigFeeCode.stripAll()       != dstrFeeCode.stripAll() ||
				 dstrOrigFundCode.stripAll()      != dstrFundCode.stripAll() ||
				 dstrOrigClassCode.stripAll()     != dstrClassCode.stripAll() ||
				 dstrOrigEffectiveDate.stripAll() != dstrEffectiveDate.stripAll() ||
				 dstrOrigStopDate.stripAll()      != dstrStopDate.stripAll() ) )
		{
			DString dstrRecId;
			if ( !isNew() )
			{
				getField( ifds::DailyFeeRid, dstrRecId, idDataGroup );				
			}

			pDailyTransactionsFeeList->checkDuplicate( dstrRecId, this, idDataGroup ); 
		}
     validateFeeCodeForClassEffHuddleRate( idDataGroup);
	}   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateFundCode( const DString &dstrFundCode, 
																 const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCode") );

	FundMasterList *pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING && pFundMasterList != NULL )
   {
      if( pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) == false )
		{
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
			setField( ifds::FundName, I_( "" ), idDataGroup );
		}
   }
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateClassCode( const DString &dstrClassCode, 
																  const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode"));

	bool blValidFundClassCode = false;

	DString dstrClass = DString ( dstrClassCode );
   dstrClass.strip().upperCase();

	DString dstrFundCode;
	getField( ifds::FundCode, dstrFundCode, idDataGroup );

	if ( !dstrFundCode.stripAll().empty() && !dstrClass.empty() )
	{
		FundDetailList *pFundDetailList = NULL;
		if ( getMgmtCo().getFundDetailList( pFundDetailList ) <= WARNING &&
			  NULL != pFundDetailList )
		{
			FundDetail *pFundDetail = NULL;
			if ( pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) &&
				  NULL != pFundDetail )
			{
				blValidFundClassCode = true;
			}
		}
	}
	
	if( false == blValidFundClassCode )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
		setField( ifds::FundName, I_( "" ), idDataGroup );
   }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateEffectiveStopDate( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveStopDate"));

	DString dstrEffectiveDate, dstrStopDate;
	getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
	getField( ifds::StopDate,      dstrStopDate,      idDataGroup );

	if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
	{
		// Effective Date must precede Stop Date.
		ADDCONDITIONFROMFILE( CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE );
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateDateAgainstCurrBusDate( const DString &dstrDate, 
																				   const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDateAgainstCurrBusDate"));
	// As per Backdate ADL fee mini enhancement, EffectiveDate can any date (including backdate & future date).
   	// This function is kept just for further modification.

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateFeeRate( const DString &dstrFeeRate, 
															   const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFeePecentage"));

	DString dstrFeeType, dstrFeeCode;
	
	getField( ifds::FeeType, dstrFeeType, idDataGroup, false );
	getField(ifds::FeeCode, dstrFeeCode, idDataGroup); 

	if (dstrFeeType != 	PERCENT)
		return GETCURRENTHIGHESTSEVERITY();

	DString dstrPercentage( dstrFeeRate );
    dstrPercentage.strip();   

   double dblPercent = DSTCommonFunctions::convertToDouble( dstrPercentage );

   switch(dstrFeeCode.convertToULong())
   {
      case CLASS_EFFECTIVE_HURDLE_RATE:
          {
            if( dblPercent < -100 || dblPercent > 100  )
                ADDCONDITIONFROMFILE( CND::ERR_VALUE_NOT_EQUAL_100_PER );	
          }
          break;
       default:
          {
            if( dblPercent < 0 || dblPercent > 100  )
                ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );	
          }
          break;
   }
	if ( 0 == dblPercent )
	{
		DString dstrRecordType;				  
		getField( ifds::RecordType,    dstrRecordType,    idDataGroup, false );
		if ( I_( "01" ) == dstrRecordType.strip().upperCase() )
		{
			if( dstrFeeCode == CLASS_HURDLE_RATE )
			{
				setFieldRequired(ifds::FeeRate, idDataGroup, false);
			}
			else
			{
				ADDCONDITIONFROMFILE( CND::ERR_ADL_FEE_PERCENTAGE_FOR_DEFAULT_RECORD );
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFee::validateFeeCodeForClassEffHuddleRate( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFeePecentage"));
   DString dstrFeeCode ;
   getField(ifds::FeeCode, dstrFeeCode, idDataGroup);
   
   if(CLASS_HURDLE_RATE ==   dstrFeeCode)
   {
     DString dstrFund, dstrClass;
     getField( ifds::FundCode, dstrFund, idDataGroup );
     getField( ifds::ClassCode, dstrClass, idDataGroup );
     if(validateFundCode(dstrFund, idDataGroup) <= WARNING &&  
        validateClassCode(dstrClass, idDataGroup) <= WARNING )
       {
        FundDetail *pFundDetail = NULL;
        if ( getWorkSession ().getFundDetail (dstrFund, dstrClass, idDataGroup, pFundDetail) && 
             pFundDetail)
        {
          DString dstrFundSubCat ;
          pFundDetail->getField (ifds::FundSubCat, dstrFundSubCat, idDataGroup, false);
           if(!DSTCommonFunctions::codeInList(CLASS_FUND_CAT_PF , dstrFundSubCat ))
               ADDCONDITIONFROMFILE( CND::ERR_FEECODE_NOT_VALID_FOR_NON_PF_FUNDS);
         }
       }     
   } 
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFee.cpp-arc  $
// 
//    Rev 1.12   Jul 16 2010 15:50:40   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.11   Jul 14 2010 13:36:56   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.10   Oct 21 2009 21:55:34   wutipong
// P0147733 FN14_ Modifying and Backdating ADL fees in iFAST
// 
//    Rev 1.9   Nov 14 2004 14:30:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 05 2004 14:45:14   VADEANUM
// PET859 FN23 - ADL - fix for Effective Date validation.
// 
//    Rev 1.7   Mar 05 2004 13:57:50   VADEANUM
// PET859 FN23 - ADL - Added  ERR_ADL_FEE_PERCENTAGE_FOR_DEFAULT_RECORD
// 
//    Rev 1.6   Feb 25 2004 15:48:18   VADEANUM
// PET859 FN23 - ADl - separated duplicate check from default existance check.
// 
//    Rev 1.5   Feb 25 2004 13:58:02   VADEANUM
// PET859 FN23 - ADL - Layout change for 284, modified signature of DailyTransactionsFeesList::init().
// 
//    Rev 1.4   Feb 23 2004 10:32:34   VADEANUM
// PEt 859 FN23 - ADL - Finalized Duplicate Check.
// 
//    Rev 1.3   Feb 13 2004 14:04:12   VADEANUM
// PET859 FN23 - ADL - Additional FeeRate and Dates validations.
// 
//    Rev 1.2   Feb 12 2004 14:00:16   VADEANUM
// PET859 FN23 - ADL - replaced FeePercent with FeeRate for correct display mask, removed DTFKey, StopDate validation, cleanup.
// 
//    Rev 1.1   Feb 10 2004 16:51:46   VADEANUM
// PET 859 FN23 - ADL - first working version.
// 
//    Rev 1.0   Jan 28 2004 14:06:54   popescu
// Initial revision.
// 

 */