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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorization.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : TaxExemptAuthorization
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "taxexemptauthorization.hpp"
#include "taxexemptauthorizationlist.hpp"
#include <bfutil\bfdate.hpp>
#include "accountentityxref.hpp"
#include "dstcommonfunction.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmasterlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0301_vw.hpp>
#include <ifastdataimpl\dse_dstc0301_req.hpp>
#include <ifastdataimpl\dse_dstc0302_vw.hpp>

namespace
{
   const I_CHAR * const BLANK_SUBSTITUTION             = I_( " = ;");  // substitution with only one element with tag = value = " " 
   const I_CHAR * const CLASSNAME                      = I_( "TaxExemptAuthorization" );
   const I_CHAR * const CANADA_JURISLIST  = I_("0001,0002,0003,0004,0005,0006,0007,0008,0009,0010,0011,0012,0013,0015,0100,9999");
   const I_CHAR * const NR301_NO = I_("NRNO");
   const I_CHAR * const NR301 = I_("NR");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId CurrSysDate;
   extern CLASS_IMPORT const BFDecimalFieldId ExemptAmtRemain;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId BackWithholdTax;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId IDExemptionReasonCode;
   extern CLASS_IMPORT const BFTextFieldId TaxExemptJurisdictionXEdit;
}

namespace CND
{  // Conditions used
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_INVALID_NEGATIVE_AMOUNT;
   extern const long ERR_FIELD_VAL_REQUIRED_PLS_ENTER;
   extern const long ERR_STOPDATE_NOT_VALID;
   extern const long WARN_STOPDATE_NOT_VALID;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND;
   extern const long WARN_INVALID_WKN_NUMBER;
   extern const long WARN_INVALID_ISIN_NUMBER;
   extern const long ERR_EXEMPT_TYPE_NOT_VALID_FOR_TAX_JURISDICTION;
   extern const long ERR_EXEMPT_TYPE_NOT_VALID_FOR_ACCOUNT_TYPE_AND_DESIGNATION;
   extern const long ERR_NOT_IWT_TAX_JURIS;
   extern const long ERR_CANNOT_ADD_CANADIAN_JURIDICTION_TO_NR301;
   extern const long ERR_START_DATE_AFTER_SYSTEM_DATE;
   extern const long ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
   extern const long ERR_W8_W9_CANNOT_CREATE_MANUALLY;
   extern const long ERR_EXEMPT_SCOPE_NOT_VALID_FOR_TAX_JURISDICTION;
   extern const long ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS;
}

namespace IFASTERR 
{
	extern CLASS_IMPORT I_CHAR * const TAX_EXEMPT_AUTH_STOPDATE_NOT_VALID;
}

namespace
{
   const DString TAX_EXEMPT_TYPE_FEDERAL = I_("Fed");
   const DString TAX_EXEMPT_TYPE_PROVINCIAL = I_("Prov");
   const DString TAX_EXEMPT_TYPE_NON_RESIDENT = I_("NR");
   const DString TAX_EXEMPT_TYPE_NON_RESIDENT_NO = I_("NRNO");
   const DString TAX_EXEMPT_TYPE_INTEREST_DISTRIBUTION = I_("INTR");
   const DString TAX_EXEMPT_TYPE_W8_EXEMPT_FORM = I_("W8");
   const DString TAX_EXEMPT_TYPE_W9_REQUEST_FOR_TIN = I_("W9");

   const DString EXEMPT_SCOPE_FULL = I_("1");
   const DString EXEMPT_SCOPE_PARTIAL = I_("2");
   const DString EXEMPT_SCOPE_RATE_OVERRIDE = I_("3");

   const DString REASON_CODE_EXEMPTION_CERTIFICATE = I_("01");
   const DString REASON_CODE_THIRD_PARTY_PA = I_("02");
   const DString REASON_CODE_GOOD_STANDING = I_("03");
   const DString REASON_CODE_NON_RESIDENT = I_("04");
   const DString REASON_CODE_CORPORATE = I_("05");
   const DString INTEREST_DISTRIBUTION_REASON_SET = I_("04,05");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,    Group Flags 
   {ifds::EffectiveDate,      BFCBO::REQUIRED,  0 }, 
   {ifds::StopDate,           BFCBO::REQUIRED,  0 }, 
   {ifds::TaxExType,          BFCBO::REQUIRED,  0 }, 
   {ifds::TaxJurisCode,       BFCBO::REQUIRED,  0 }, 
   {ifds::ExemptAmtOrig,      BFCBO::REQUIRED,  0 }, 
   {ifds::ExemptAmtRemain,    BFCBO::NONE,      0 },
   {ifds::AccountNum,         BFCBO::NONE,      0 },
   {ifds::EntityId,           BFCBO::NONE,      0 },
   {ifds::CertNumber,         BFCBO::NONE,      0 },
   {ifds::ExemptionScope,     BFCBO::NONE,      0 },
   {ifds::ExemptionReasonCode,BFCBO::NONE,		0 },
   {ifds::FundNumber,         BFCBO::NONE,      0 },
   {ifds::FundCode,           BFCBO::NONE,      0 },
   {ifds::ClassCode,          BFCBO::NONE,      0 },
   {ifds::FundName,           BFCBO::NONE,      0 },
   {ifds::FundWKN,            BFCBO::NONE,      0 },
   {ifds::FundISIN,           BFCBO::NONE,      0 },
   {ifds::EffectiveStopDate,  BFCBO::NONE,      0 },
   {ifds::TaxExemptJurisdictionXEdit, BFCBO::IMMEDIATE_VALIDATION, 0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
TaxExemptAuthorization::TaxExemptAuthorization (BFAbstractCBO &parent) :
MFCanBFCbo (parent),
_eusdParticip (NULL_STRING),
_backupWithholdingTax (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   getWorkSession().getOption (ifds::EUSDParticip, _eusdParticip, BF::HOST, false);
   getWorkSession().getOption (ifds::BackWithholdTax, _backupWithholdingTax, BF::HOST, false);
   addCrossEdit (ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit (ifds::EffectiveStopDate, ifds::StopDate);

   addCrossEdit (ifds::TaxExemptJurisdictionXEdit, ifds::TaxJurisCode);
   addCrossEdit (ifds::TaxExemptJurisdictionXEdit, ifds::ExemptionScope);
}

//****************************************************************************
TaxExemptAuthorization::~TaxExemptAuthorization()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY TaxExemptAuthorization::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   DString dstrExemptAmtOrig, 
      dstrExemptAmountUsed, 
      dstrExemptReasonCode, 
      dstrExemptionScope,
	  dstrTaxExType;

   getField (ifds::ExemptAmtOrig, dstrExemptAmtOrig, BF::HOST);
   getField (ifds::ExemptAmountUsed, dstrExemptAmountUsed, BF::HOST);
   getField (ifds::ExemptionReasonCode, dstrExemptReasonCode, BF::HOST);
   getField (ifds::ExemptionScope, dstrExemptionScope, BF::HOST);
   getField (ifds::TaxExType, dstrTaxExType, BF::HOST);

   double dec_ExemptAmtOrig = DSTCommonFunctions::convertToDouble (dstrExemptAmtOrig);
   double dec_ExemptAmountUsed = DSTCommonFunctions::convertToDouble (dstrExemptAmountUsed);

   setFieldReadOnly (ifds::TaxExType, BF::HOST, true);
   setFieldReadOnly (ifds::EffectiveDate, BF::HOST, true);

   if ( (dstrTaxExType == I_("NR")) || (dec_ExemptAmountUsed != 0) )
   {
      setFieldReadOnly (ifds::TaxJurisCode, BF::HOST, true);
   }
   if (dstrExemptReasonCode == I_("02"))
   {
      setFieldReadOnly (ifds::CertNumber, BF::HOST, true);
   }
   //if TaxType is NR301, ExemptAmt and RemainExemptAmt is grayed out
   if (dstrTaxExType == I_("NR"))
   {
		setFieldReadOnly (ifds::ExemptAmtRemain, BF::HOST, true);
		setFieldReadOnly (ifds::ExemptAmtOrig, BF::HOST, true);
   }
   if (dstrExemptionScope == I_("1"))
   {
      setFieldReadOnly (ifds::ExemptAmtRemain, BF::HOST, true);  
      setFieldReadOnly(ifds::ExemptAmtOrig, BF::HOST, true);
   }

   commonInit(BF::HOST);
   setFieldReadOnly(ifds::EntityId, BF::HOST, true);

   DString taxExTypeSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::TaxExType, BF::HOST);

   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (taxExTypeSubstList);

      taxExTypeSubstList = removeItemFromSubtList (taxExTypeSubstList, 
                                                   TAX_EXEMPT_TYPE_W8_EXEMPT_FORM);
      taxExTypeSubstList = removeItemFromSubtList (taxExTypeSubstList, 
                                                   TAX_EXEMPT_TYPE_W9_REQUEST_FOR_TIN);
      setFieldAllSubstituteValues (ifds::TaxExType, 
                                   BF::HOST, 
                                   taxExTypeSubstList);
   }

   //IN2956851 - disable controls relates NR301 
   bool b_Enable = dstrTaxExType == I_("NR");
   setFieldReadOnly   (ifds::ExemptionScope, BF::HOST, b_Enable); 
   setFieldReadOnly   (ifds::ExemptionReasonCode, BF::HOST, b_Enable);

   if(dstrTaxExType == NR301_NO){
		setFieldReadOnly   (ifds::TaxJurisCode, BF::HOST, true); 
		setFieldReadOnly   (ifds::ExemptionScope, BF::HOST, true); 
		setFieldReadOnly   (ifds::ExemptAmtRemain, BF::HOST, true); 
		setFieldReadOnly   (ifds::ExemptAmtOrig, BF::HOST, true); 
		setFieldReadOnly   (ifds::TaxExType, BF::HOST, true);
	    setFieldReadOnly   (ifds::EffectiveDate, BF::HOST, true);
		setFieldReadOnly   (ifds::ExemptionReasonCode, BF::HOST, true);
   }

  if( dstrTaxExType  == TAX_EXEMPT_TYPE_INTEREST_DISTRIBUTION)
  {
	setFieldReadOnly (ifds::ExemptionScope, BF::HOST, DSTCommonFunctions::codeInList(dstrExemptReasonCode,
													  INTEREST_DISTRIBUTION_REASON_SET));
	setFieldSubstituteValues( ifds::ExemptionReasonCode , BF::HOST,ifds::IDExemptionReasonCode);
  }
  setFieldRequired (ifds::ExemptionReasonCode,BF::HOST,(dstrTaxExType == TAX_EXEMPT_TYPE_INTEREST_DISTRIBUTION) );
  setFieldValid(ifds::ExemptionReasonCode,BF::HOST ,false);
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY TaxExemptAuthorization::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ));
   
   commonInit (idDataGroup);

   /*if(DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA){
		DString interTaxExType = removeItemFromSubtList(ifds::TaxExType, NR301, idDataGroup);
		interTaxExType = removeItemFromSubtList(interTaxExType, NR301_NO);

		setFieldAllSubstituteValues (ifds::TaxExType, idDataGroup, interTaxExType);
   }*/

   DString taxExTypeSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::TaxExType, idDataGroup);

   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (taxExTypeSubstList);

      taxExTypeSubstList = removeItemFromSubtList (taxExTypeSubstList, 
                                                   TAX_EXEMPT_TYPE_W8_EXEMPT_FORM);
      taxExTypeSubstList = removeItemFromSubtList (taxExTypeSubstList, 
                                                   TAX_EXEMPT_TYPE_W9_REQUEST_FOR_TIN);
      setFieldAllSubstituteValues (ifds::TaxExType, 
                                   idDataGroup, 
                                   taxExTypeSubstList);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void TaxExemptAuthorization::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   DString curBusDate,
      stopDate;
   getWorkSession ().getOption ( ifds::CurrBusDate, 
                                 curBusDate, 
                                 BF::HOST, 
                                 false);
   setFieldNoValidate (ifds::EffectiveDate, curBusDate, idDataGroup, false, true, true, false);
   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true);
}

//********************************************************************************************
SEVERITY TaxExemptAuthorization::doValidateField(  const BFFieldId& idField,
                                                   const DString& strValue,
                                                   const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   if (idField == ifds::EffectiveStopDate)  //cross edit
   {
      DString effectiveDate, 
         stopDate;
		 
      getField (ifds::StopDate, stopDate, idDataGroup, false);
      getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
	  
      if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
   }
   else if (idField == ifds::StopDate)
   {
      DString dstrExemptReasonCode;

      getField (ifds::ExemptionReasonCode, dstrExemptReasonCode, idDataGroup);

      if ( DSTCommonFunctions::codeInList (dstrExemptReasonCode, I_("01,03")) && 
          (DSTCommonFunctions::CompareDates (strValue, I_("12319999")) == DSTCommonFunctions::EQUAL ||
           strValue.empty()))
      {
		  getErrMsg(IFASTERR::TAX_EXEMPT_AUTH_STOPDATE_NOT_VALID,
			  CND::ERR_STOPDATE_NOT_VALID,
			  CND::WARN_STOPDATE_NOT_VALID,
			  idDataGroup);
      }
   }
   else if (idField == ifds::ExemptAmtOrig)
   {
      validateExemptAmtOrig (strValue, idDataGroup);
   }
   else if (idField == ifds::TaxJurisCode)
   {
      if ( strValue == I_("0000"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_FIELD_VAL_REQUIRED_PLS_ENTER);
      }
      
	  DString dstrTaxExType;
      getField(ifds::TaxExType, dstrTaxExType, idDataGroup, false);
      dstrTaxExType.strip().upperCase();

      if(dstrTaxExType == I_("NR"))
	  {
		//if TaxType is NR301 and Jurisdiction is not same as shareholder Tax Jurisdiction
		validateJurisFromShrInfo ( idDataGroup );
	  }
   }
   else if (idField == ifds::FundNumber)
   {
      validateFundNumber (idDataGroup);
   }
   else if (idField == ifds::FundCode)
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
   else if (idField == ifds::FundWKN)
   {
      DString dstrFundWKN;

      getField(ifds::FundWKN, dstrFundWKN, idDataGroup);
      dstrFundWKN.strip ().upperCase ();
      validateFundWKN (idDataGroup, dstrFundWKN);
   }
   else if (idField == ifds::FundISIN)
   {
      DString dstrFundISIN;

      getField(ifds::FundISIN, dstrFundISIN, idDataGroup);
      dstrFundISIN.strip ().upperCase ();
      validateFundISIN (idDataGroup, dstrFundISIN);
   }
   else if (idField == ifds::EffectiveDate)
   {
	   DString dstrTaxExType;
       getField (ifds::TaxExType, dstrTaxExType, idDataGroup, false);
       dstrTaxExType.strip().upperCase();

	  if (dstrTaxExType == I_("NR"))
	  {
		  DString dstrEffectiveDate, dstrStopDate;
		  getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

		  DString dstrCurrentDate;
		  getWorkSession().getOption(ifds::CurrSysDate, dstrCurrentDate, BF::HOST, false);
          if (DSTCommonFunctions::CompareDates (dstrCurrentDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
          {
			 //Start date is greater than the system date
			 ADDCONDITIONFROMFILE (CND::ERR_START_DATE_AFTER_SYSTEM_DATE);
          }
	  }
   }
   else if (idField == ifds::TaxExType)
   {
      validateTaxExType (strValue, idDataGroup);
   }
   else if (idField == ifds::TaxExemptJurisdictionXEdit)
   {
	   DString dstrTaxJurisCode, dstrExemptionScope, dstrTaxExType;
	   getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
	   getField(ifds::ExemptionScope, dstrExemptionScope, idDataGroup);
	   getField(ifds::TaxExType, dstrTaxExType, idDataGroup);

      if(dstrExemptionScope == EXEMPT_SCOPE_RATE_OVERRIDE &&
		   dstrTaxJurisCode != I_("0247")) //Jamica
	   {
		   ADDCONDITIONFROMFILE(CND::ERR_EXEMPT_SCOPE_NOT_VALID_FOR_TAX_JURISDICTION);
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TaxExemptAuthorization:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   /* 
	  Validate there is full exemption scope in list or not.    
	  If there is full exemption scope, it's not allowed to have any exemption scope in same level.
   */
   DString dstrTaxExType, dstrTaxJurisCode, dstrEntityId, dstrFundCode, 
	   dstrClassCode, dstrExemptionScope, dstrStartDate, dstrEndDate;   
   
   getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
   getField(ifds::StopDate, dstrEndDate, idDataGroup);
   getField(ifds::TaxExType, dstrTaxExType, idDataGroup);
   getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
   getField(ifds::EntityId, dstrEntityId, idDataGroup);
   getField(ifds::FundCode, dstrFundCode, idDataGroup);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup);
   getField(ifds::ExemptionScope, dstrExemptionScope, idDataGroup);
   dstrEntityId.stripLeading('0');   
	
   TaxExemptAuthorizationList * pTaxExemptAuthorizationList = NULL;
   pTaxExemptAuthorizationList = dynamic_cast<TaxExemptAuthorizationList*> (getParent());

   if (dstrExemptionScope != I_("1") && dstrEntityId == NULL_STRING)  // If it is not Full, then check if there is full in the same model.
   {
	   if( pTaxExemptAuthorizationList->hasFullExemptScope(dstrTaxExType, dstrTaxJurisCode, dstrEntityId, dstrFundCode,
		   dstrClassCode, dstrStartDate, dstrEndDate, idDataGroup) )
	   {		   
		   ADDCONDITIONFROMFILE( CND::ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS );
		   return(GETCURRENTHIGHESTSEVERITY());
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************
SEVERITY TaxExemptAuthorization::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::TaxExType)
   {
      DString taxExType;
      getField (ifds::TaxExType, taxExType, idDataGroup);

      setFieldNoValidate (ifds::ExemptionReasonCode, NULL_STRING , idDataGroup, false, true, true, true);
      setFieldNoValidate (ifds::ExemptionScope, NULL_STRING, idDataGroup, false, true, true, true);
      setFieldReadOnly(ifds::TaxJurisCode, idDataGroup, false);
      setFieldValid(ifds::TaxJurisCode, idDataGroup, false);

	   if( taxExType == TAX_EXEMPT_TYPE_NON_RESIDENT )
	   {
		   setFieldNoValidate (ifds::ExemptAmtOrig, I_("0"), idDataGroup, false, true, true);
		   setFieldReadOnly   (ifds::ExemptAmtOrig, idDataGroup, true);
		   setFieldNoValidate (ifds::ExemptAmtRemain, I_("0"), idDataGroup, false, true, true, false);
		   setFieldReadOnly   (ifds::ExemptAmtRemain, idDataGroup, true);

		   DString dstrCurrentDate;
		   getWorkSession().getOption(ifds::CurrSysDate, dstrCurrentDate, BF::HOST, false);
		   setFieldNoValidate (ifds::EffectiveDate, dstrCurrentDate, idDataGroup, false, true, true, false);

		   DString dstrOutDate;
		   getDefaultStopDate (dstrCurrentDate, dstrOutDate );
   	   setFieldNoValidate (ifds::StopDate, dstrOutDate, idDataGroup, false, true, true, false);

		   setFieldValid(ifds::TaxJurisCode, idDataGroup, false);
		
		   setFieldReadOnly   (ifds::ExemptionScope, idDataGroup, true);
		   setFieldNoValidate (ifds::ExemptionScope, EXEMPT_SCOPE_FULL , idDataGroup, false, true, true, true);
		   
		   setFieldSubstituteValues( ifds::ExemptionReasonCode , idDataGroup,ifds::ExemptionReasonCode);
	   }
	   else if( taxExType == TAX_EXEMPT_TYPE_NON_RESIDENT_NO )
	   {
		   setFieldNoValidate (ifds::ExemptAmtOrig, I_("0"), idDataGroup, false, true, true);
		   setFieldReadOnly   (ifds::ExemptAmtOrig, idDataGroup, true);
		   setFieldNoValidate (ifds::ExemptAmtRemain, I_("0"), idDataGroup, false, true, true, false);
		   setFieldReadOnly   (ifds::ExemptAmtRemain, idDataGroup, true);

		   DString dstrCurrentBusDate;
		   getWorkSession().getOption(ifds::CurrBusDate, dstrCurrentBusDate, BF::HOST, false);
		   setFieldNoValidate (ifds::EffectiveDate, dstrCurrentBusDate, idDataGroup, false, true, true, false);

   	       setFieldNoValidate (ifds::StopDate, I_("12319999"), idDataGroup, false, true, true, false);

			// TaxJuris and Exempt Scope are not requried for NR301 NO.
		   setFieldNoValidate (ifds::TaxJurisCode, NULL_STRING, idDataGroup, false, true, true);
		   setFieldNoValidate (ifds::ExemptionScope, NULL_STRING, idDataGroup, false, true, true);

		   setFieldRequired(ifds::TaxJurisCode, idDataGroup, false);
		   setFieldSubstituteValues( ifds::ExemptionReasonCode , idDataGroup,ifds::ExemptionReasonCode);
	   }
      else if (taxExType == TAX_EXEMPT_TYPE_W9_REQUEST_FOR_TIN || taxExType == TAX_EXEMPT_TYPE_W8_EXEMPT_FORM )
      {
         setFieldNoValidate (ifds::ExemptionReasonCode, REASON_CODE_GOOD_STANDING, idDataGroup, false, true, true, true); //good standing
         setFieldNoValidate (ifds::ExemptionScope, EXEMPT_SCOPE_FULL, idDataGroup, false, true, true);
         setFieldNoValidate (ifds::TaxJurisCode, I_("0130"), idDataGroup, false, true, true); //
	  }
	  else if(taxExType == TAX_EXEMPT_TYPE_INTEREST_DISTRIBUTION)
	  {
		   setFieldSubstituteValues( ifds::ExemptionReasonCode , idDataGroup,ifds::IDExemptionReasonCode);
		   setFieldNoValidate (ifds::TaxJurisCode, I_("0140"), idDataGroup, false, true);   //0140=United Kingdom
		   //setFieldReadOnly(ifds::TaxJurisCode, idDataGroup, true);
		   //setFieldRequired (ifds::TaxJurisCode, idDataGroup, false);     
		   setFieldNoValidate (ifds::ExemptionScope, EXEMPT_SCOPE_FULL, idDataGroup, false, true, true, true);
		   setFieldReadOnly   (ifds::ExemptionScope, idDataGroup, true);
	  }
      else
      {
         // The existing set the field to be true, the validation does not get validated when modifying.
         // The field should be set to be invalid to kick the validation in.
         setFieldNoValidate (ifds::ExemptionReasonCode, NULL_STRING, idDataGroup, false, false, true, true); 
		 	setFieldReadOnly (ifds::ExemptAmtOrig, idDataGroup, false);
		 	setFieldReadOnly (ifds::ExemptAmtRemain, idDataGroup, false);

		 	//IN2956851 - disable controls relates NR301 		
		 	setFieldReadOnly   (ifds::ExemptionScope, idDataGroup, false); 
		 	setFieldReadOnly   (ifds::ExemptionReasonCode, idDataGroup, false);
		 	//IDExemption related changes
		 	setFieldSubstituteValues( ifds::ExemptionReasonCode , idDataGroup,ifds::ExemptionReasonCode);
		 	setFieldNoValidate (ifds::TaxJurisCode, I_("0000"), idDataGroup, false, true);
		 	setFieldRequired(ifds::TaxJurisCode, idDataGroup, true);	
      }  
      setFieldRequired (ifds::ExemptionReasonCode,idDataGroup,(taxExType == TAX_EXEMPT_TYPE_INTEREST_DISTRIBUTION) );     
	  setFieldValid(ifds::ExemptionReasonCode,idDataGroup,false);
      setFieldValid(ifds::TaxJurisCode, idDataGroup, false);
    }
   else if (idField == ifds::ExemptAmtOrig)
   {
      double dec_ExemptAmtRemain = getExemptAmtRemain(idDataGroup);

      DString dstrExemptAmtRemain = DSTCommonFunctions::doubleToDString (ifds::ExemptAmtRemain, dec_ExemptAmtRemain);
      setFieldNoValidate (ifds::ExemptAmtRemain, dstrExemptAmtRemain, idDataGroup, false, true, true);
   }
   else if (idField == ifds::ExemptionScope)
   {
      DString dstrExemptScope;
      getField (ifds::ExemptionScope, dstrExemptScope, idDataGroup);

	   DString taxExType;
      getField (ifds::TaxExType, taxExType, idDataGroup);

	   if( taxExType == TAX_EXEMPT_TYPE_NON_RESIDENT ) //Fix for IN 2956851 - Greying out Exempt and Remain Exempt Amount for NR301
	   {
		   setFieldNoValidate (ifds::ExemptAmtOrig, I_("0"), idDataGroup, false, true, true);
		   setFieldReadOnly   (ifds::ExemptAmtOrig, idDataGroup, true);

		   setFieldNoValidate (ifds::ExemptAmtRemain, I_("0"), idDataGroup, false, true, true, false);
		   setFieldReadOnly   (ifds::ExemptAmtRemain, idDataGroup, true);
	   }
	   else //else condition - retaining the original behavior
	   {
		   if (dstrExemptScope == EXEMPT_SCOPE_FULL)
		   {
			   setFieldNoValidate (ifds::ExemptAmtRemain, I_("0"), idDataGroup, false, true, true, false);
			   setFieldReadOnly (ifds::ExemptAmtRemain, idDataGroup, true); 
			   setFieldNoValidate (ifds::ExemptAmtOrig, I_("0"), idDataGroup, false, true, true);
			   setFieldReadOnly (ifds::ExemptAmtOrig, idDataGroup, true);
		   }
         else if(dstrExemptScope == EXEMPT_SCOPE_PARTIAL)
		   {
			   setFieldReadOnly (ifds::ExemptAmtRemain, idDataGroup, false); 
			   setFieldRequired (ifds::ExemptAmtOrig, idDataGroup, true);
			   setFieldReadOnly (ifds::ExemptAmtOrig, idDataGroup, false);
			   setValidFlag (ifds::ExemptAmtOrig, idDataGroup, false);
		   }
		   else if(dstrExemptScope == EXEMPT_SCOPE_RATE_OVERRIDE)
		   {
			   setFieldNoValidate (ifds::ExemptAmtRemain, I_("0"), idDataGroup, false, true, true, false);
			   setFieldReadOnly   (ifds::ExemptAmtRemain, idDataGroup, true); 
			   setFieldRequired (ifds::ExemptAmtOrig, idDataGroup, true);
			   setFieldReadOnly (ifds::ExemptAmtOrig, idDataGroup, false);
			   setValidFlag (ifds::ExemptAmtOrig, idDataGroup, false);
		   }
	   }
   }
   else if (idField == ifds::FundNumber)
   {
      DString dstrFundNumber;

      getField(ifds::FundNumber, dstrFundNumber, idDataGroup);
      setFundByFundNumber (idDataGroup, dstrFundNumber);
   }
   else if (idField == ifds::FundCode || idField == ifds::ClassCode)
   {
      DString dstrFundCode, dstrClassCode;

      getField(ifds::FundCode, dstrFundCode, idDataGroup);
      getField(ifds::ClassCode, dstrClassCode, idDataGroup);
      setFundByFundClass (idDataGroup, dstrFundCode, dstrClassCode);
   }
   else if (idField == ifds::FundWKN)
   {
      DString dstrFundWKN;

      getField(ifds::FundWKN, dstrFundWKN, idDataGroup);
      setFundByWKN (idDataGroup, dstrFundWKN);
   }
   else if (idField == ifds::FundISIN)
   {
      DString dstrFundISIN;

      getField(ifds::FundISIN, dstrFundISIN, idDataGroup);
      setFundByISIN (idDataGroup, dstrFundISIN);
   }
   else if (idField == ifds::EffectiveDate)
   {
	   DString dstrOutDate, dstrEffectiveDate, dstrTaxExType;
	   getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
	   getField (ifds::TaxExType, dstrTaxExType, idDataGroup);

	   if (dstrTaxExType != TAX_EXEMPT_TYPE_NON_RESIDENT_NO)
	   {
		   getDefaultStopDate (dstrEffectiveDate, dstrOutDate );
		   setFieldNoValidate (ifds::StopDate, dstrOutDate, idDataGroup, false, true, true, false);
	   }
   }
   else if (idField == ifds::ExemptionReasonCode) 
   {
	   setFieldValid(ifds::StopDate, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY TaxExemptAuthorization::validateExemptAmtOrig ( const DString& strValue, 
                                                         const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateExemptAmtOrig" ) );

   DString dstrExemptScope;

   getField (ifds::ExemptionScope, dstrExemptScope, idDataGroup);
   bool isFullExemptScope = dstrExemptScope == I_("1");  

   if (!isFullExemptScope) // don't validate as values are already set to 0.
   {
      double dec_ExemptAmtOrig = DSTCommonFunctions::convertToDouble( strValue );

      if (dec_ExemptAmtOrig <= 0)
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_NEGATIVE_AMOUNT);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
double TaxExemptAuthorization::getExemptAmtRemain (const BFDataGroupId& idDataGroup)
{
   DString dstrExemptAmtOrig, 
   dstrExemptAmountUsed;

   getField (ifds::ExemptAmtOrig, dstrExemptAmtOrig, idDataGroup);
   getField (ifds::ExemptAmountUsed, dstrExemptAmountUsed, idDataGroup);
   double dec_ExemptAmtOrig = DSTCommonFunctions::convertToDouble( dstrExemptAmtOrig );
   double dec_ExemptAmountUsed = DSTCommonFunctions::convertToDouble( dstrExemptAmountUsed );
   double dec_ExemptAmtRemain = dec_ExemptAmtOrig - dec_ExemptAmountUsed;
   return dec_ExemptAmtRemain;
}

//******************************************************************************
SEVERITY TaxExemptAuthorization::commonInit(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit") );
	setAcctOwnerEntityList(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TaxExemptAuthorization::relatedChangesForEUSD (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("relatedChangesForEUSD") );
	
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TaxExemptAuthorization::setAcctOwnerEntityList (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAcctOwnerEntityList") );

	DString AcctOwnerEntitySubList;
   MFAccount * pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent());

   if (pMFAccount)
   {
      pMFAccount->getEntitySubstSet(idDataGroup,AcctOwnerEntitySubList, I_("01"), false);
      	   
      setFieldAllSubstituteValues (ifds::EntityId, idDataGroup, AcctOwnerEntitySubList);
	   setValidFlag (ifds::EntityId, idDataGroup, false);    
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TaxExemptAuthorization::doReset (const BFDataGroupId &idDataGroup)
{
   DString dstrExemptionScope;

   getField (ifds::ExemptionScope, dstrExemptionScope, BF::HOST, false);

   if (dstrExemptionScope == EXEMPT_SCOPE_FULL)
   {
      setFieldReadOnly (ifds::ExemptAmtOrig, BF::HOST, true);
   }
}

//**********************************************************************************
SEVERITY TaxExemptAuthorization::validateTaxExType (const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTaxExType"));

   if ((strValue == TAX_EXEMPT_TYPE_W9_REQUEST_FOR_TIN || 
      strValue == TAX_EXEMPT_TYPE_W8_EXEMPT_FORM ) && 
      isNew())
   {
	   ADDCONDITIONFROMFILE(CND::ERR_W8_W9_CANNOT_CREATE_MANUALLY);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY TaxExemptAuthorization::validateFundNumber (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundNumber") );

   FundDetail *pFundDetail = NULL;
   FundDetailList *pFundDetailList = NULL;

   if (getWorkSession().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      DString dstrFundNumber;

      getField (ifds::FundNumber, dstrFundNumber, idDataGroup);
      dstrFundNumber.strip ().upperCase ();

      pFundDetail = pFundDetailList->getFundDetailByFundNumber (dstrFundNumber);

      if (!dstrFundNumber.empty () && pFundDetail == NULL)
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_NUMBER);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY TaxExemptAuthorization::validateFundCode (const BFDataGroupId &idDataGroup, const DString &dstrFundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

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

//****************************************************************************** 
SEVERITY TaxExemptAuthorization::validateClassCode (const BFDataGroupId &idDataGroup, const DString &dstrClassCode)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode"));

   bool bValidFundClassCode = false;
   DString dstrFundCode;

   getField (ifds::FundCode, dstrFundCode, idDataGroup);
   dstrFundCode.strip ().upperCase ();

   if (!dstrFundCode.stripAll ().empty() || !dstrClassCode.empty ())
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
      setField( ifds::FundName, I_( "" ), idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//************************************************************************************************************
SEVERITY TaxExemptAuthorization::validateFundWKN(const BFDataGroupId &idDataGroup, const DString &dstrFundWKN )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundWKN" ) );

   FundDetail* pFundDetail = NULL;
   FundDetailList* pFundDetailList = NULL;

   if (dstrFundWKN.empty ())
   return GETCURRENTHIGHESTSEVERITY();

   if (getWorkSession().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      pFundDetail = pFundDetailList->getFundDetailByWKN(dstrFundWKN);

      if (pFundDetail == NULL)
      {
         ADDCONDITIONFROMFILE (CND::WARN_INVALID_WKN_NUMBER);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TaxExemptAuthorization::validateFundISIN( const BFDataGroupId &idDataGroup, const DString &dstrFundISIN )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundISIN" ) );

   FundDetail* pFundDetail = NULL;
   FundDetailList* pFundDetailList = NULL;

   if (dstrFundISIN.empty ())
   return GETCURRENTHIGHESTSEVERITY();

   if (getWorkSession().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      pFundDetail = pFundDetailList->getFundDetailByISIN(dstrFundISIN);

      if (pFundDetail == NULL)
      {
         ADDCONDITIONFROMFILE (CND::WARN_INVALID_ISIN_NUMBER);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TaxExemptAuthorization::setFundByFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByClass" ) );

   FundDetailList* pFundDetailList = NULL;

   if (getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      FundDetail* pFundDetail = pFundDetailList->getFundDetailByFundNumber (dstrFundNumber);

      if (pFundDetail != NULL)
      {
         DString dstrFundCode, dstrClassCode, dstrFundName, dstrFundWKN, dstrFundISIN;
         FundMasterList *pFundMasterList;

         pFundDetail->getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
         pFundDetail->getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);
         pFundDetail->getField (ifds::FundWKN, dstrFundWKN, idDataGroup, false);
         pFundDetail->getField (ifds::FundISIN, dstrFundISIN, idDataGroup, false);

         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
         {
            pFundMasterList->getFundName (dstrFundCode, dstrFundName);
         }

         //set fields to cbo
         setFieldNoValidate (ifds::FundCode, dstrFundCode, idDataGroup, false, true, true, false );
         setFieldNoValidate (ifds::ClassCode, dstrClassCode, idDataGroup, false, true, true, false);
         setFieldNoValidate (ifds::FundName, dstrFundName, idDataGroup, false,true, true, false); 
         setFieldNoValidate (ifds::FundWKN, dstrFundWKN, idDataGroup, false,true, true, false); 
         setFieldNoValidate (ifds::FundISIN, dstrFundISIN, idDataGroup, false,true, true, false); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TaxExemptAuthorization::setFundByFundClass( const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode  )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByClass" ) );

   if (!dstrFundCode.empty () && !dstrClassCode.empty ())
   {
      DString dstrFundNumber, dstrFundName, dstrFundWKN, dstrFundISIN;
      FundMasterList *pFundMasterList;

      getWorkSession().GetFundNumber(dstrFundCode, dstrClassCode, dstrFundNumber);
      getWorkSession().GetISINNumber(dstrFundCode, dstrClassCode, dstrFundISIN);
      getWorkSession().GetWKNNumber(dstrFundCode, dstrClassCode, dstrFundWKN);

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
      {
         pFundMasterList->getFundName (dstrFundCode, dstrFundName);
      }

      //set fields to cbo
      setFieldNoValidate( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false);
      setFieldNoValidate( ifds::FundName, dstrFundName, idDataGroup, false,true, true, false); 
      setFieldNoValidate( ifds::FundWKN, dstrFundWKN, idDataGroup, false,true, true, false); 
      setFieldNoValidate( ifds::FundISIN, dstrFundISIN, idDataGroup, false,true, true, false); 
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TaxExemptAuthorization::setFundByWKN( const BFDataGroupId &idDataGroup, const DString &dstrFundWKN )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByWKN" ) );

   FundDetail* pFundDetail = NULL;
   FundDetailList* pFundDetailList = NULL;

   if (getWorkSession().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      pFundDetail = pFundDetailList->getFundDetailByWKN(dstrFundWKN);

      if (pFundDetail != NULL)
      {
         DString dstrFundNumber, dstrFundName, dstrClassCode, dstrFundCode, dstrFundISIN;
         FundMasterList *pFundMasterList;

         pFundDetail->getField (ifds::FundNumber, dstrFundNumber, idDataGroup, false);
         pFundDetail->getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
         pFundDetail->getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);
         pFundDetail->getField (ifds::FundISIN, dstrFundISIN, idDataGroup, false);

         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
         {
            pFundMasterList->getFundName (dstrFundCode, dstrFundName);
         }

         //set fields to cbo
         setFieldNoValidate( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false);
         setFieldNoValidate( ifds::FundCode, dstrFundCode, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::FundName, dstrFundName, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::ClassCode, dstrClassCode, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::FundISIN, dstrFundISIN, idDataGroup, false,true, true, false); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TaxExemptAuthorization::setFundByISIN( const BFDataGroupId &idDataGroup, const DString &dstrFundISIN)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByISIN" ) );

   FundDetail* pFundDetail = NULL;
   FundDetailList* pFundDetailList = NULL;

   if (getWorkSession().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      pFundDetail = pFundDetailList->getFundDetailByISIN (dstrFundISIN);

      if (pFundDetail != NULL)
      {
         DString dstrFundNumber, dstrFundName, dstrClassCode, dstrFundCode, dstrFundWKN;
         FundMasterList *pFundMasterList;

         pFundDetail->getField (ifds::FundNumber, dstrFundNumber, idDataGroup, false);
         pFundDetail->getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
         pFundDetail->getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);
         pFundDetail->getField (ifds::FundWKN, dstrFundWKN, idDataGroup, false);

         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
         {
            pFundMasterList->getFundName (dstrFundCode, dstrFundName);
         }

         //set fields to cbo
         setFieldNoValidate(ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false);
         setFieldNoValidate( ifds::FundCode, dstrFundCode, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::FundName, dstrFundName, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::ClassCode, dstrClassCode, idDataGroup, false,true, true, false); 
         setFieldNoValidate( ifds::FundWKN, dstrFundWKN, idDataGroup, false,true, true, false); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************

void TaxExemptAuthorization::getDefaultStopDate( DString& dstrInDate, DString& dstrOutDate )
{
   DString dstrConfiguration(I_("HostMasks")), dstrKey(I_("D"));
   dstrOutDate = GetConfigValueAsString( I_("LocaleFormats"), dstrConfiguration, dstrKey );

   //int iMonth = dstrOutDate.find( I_( "MM" ) );
   //int iDay   = dstrOutDate.find( I_( "dd" ) );
   int iYear  = dstrOutDate.find( I_( "yyyy" ) );

   int iCurYear, iAddYear = 03;
   if( DString::npos != iYear )
   {
		DString dstrDate;
		dstrDate.assign( dstrInDate, iYear, 4);

		iCurYear = convertToULong( dstrDate );
		iCurYear = iCurYear + iAddYear; //Add 03 Years

		DString dstrYears;
		convertIntToString( iCurYear, dstrYears );

		DString dstrMonth ( I_("12") ), //Last month of the year
				dstrDay   ( I_("31") );	//Last day of the year

		dstrOutDate.replace( dstrOutDate.find( I_("yyyy") ), 4, dstrYears );
		dstrOutDate.replace( dstrOutDate.find ( I_("MM") ), 2, dstrMonth );
		dstrOutDate.replace( dstrOutDate.find ( I_("dd") ), 2, dstrDay );

   }// if( DString::npos != iYear )
}
//************************************************************
SEVERITY TaxExemptAuthorization::validateJurisFromShrInfo(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateJurisFromShrInfo" ) );

	DString dstrJurisCode;
	getField(ifds::TaxJurisCode, dstrJurisCode, idDataGroup, false);

	//if TaxType is NR301 and Jurisdiction is Canada then error.
	if (DSTCommonFunctions::codeInList (dstrJurisCode, CANADA_JURISLIST))
	{
		ADDCONDITIONFROMFILE (CND::ERR_CANNOT_ADD_CANADIAN_JURIDICTION_TO_NR301);
		return GETCURRENTHIGHESTSEVERITY();
	}

	DString dstrAccountNum;
	getParent()->getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup);

	MFAccount *pMFAccount (NULL);
	if ( !dstrAccountNum.empty() && 
		  getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
	{
		DString dstrShrNum;
		pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup);

		Shareholder *pShareholder = NULL;
		if (!dstrShrNum.empty () && getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING)
		{   
			DString dstrShrTaxJuris;
			pShareholder->getField ( ifds::TaxJurisCode, dstrShrTaxJuris, idDataGroup );
			dstrShrTaxJuris.strip();

			if ( !dstrShrTaxJuris.empty() && (dstrJurisCode != dstrShrTaxJuris) )
			{
				DString dstrStartDate,dstrShrEffectiveDate;
				pShareholder->getField ( ifds::EffectiveDate, dstrShrEffectiveDate, idDataGroup );
				getField(ifds::EffectiveDate, dstrStartDate, idDataGroup, false);

				if ( DSTCommonFunctions::CompareDates (dstrShrEffectiveDate, dstrStartDate) == DSTCommonFunctions::FIRST_EARLIER ||
					 DSTCommonFunctions::CompareDates (dstrShrEffectiveDate, dstrStartDate) == DSTCommonFunctions::EQUAL )
				{
					//Display this error message only if the start date is greater than or equal to the effective date
					ADDCONDITIONFROMFILE (CND::ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION);
				}
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxExemptAuthorization.cpp-arc  $
// 
//    Rev 1.34   Aug 17 2012 16:40:30   wp040133
// ESS_P01999461_FN01_Distribution Enhancement
// Tax Exempt Authorization Change redesign work..
// Implementing review comments
// 
//    Rev 1.33   Aug 16 2012 19:13:18   wp040133
// ESS_P01999461_FN01_Distribution Enhancement
// Tax Exempt Authorization Change redesign work..Removed the 
// logic added as part of 1.32 and moved it to a new function doApplyRelatedChangesforIDExemptType()
// 
//    Rev 1.32   Aug 10 2012 19:58:08   wp040133
// ESS_P01999461_FN01_ARROW_Distribution Enhancement
// Making the chnages to the Tax Exempt Autorization Behaviour for UKCorporate and UK Non Redisident Reason Code selection.
// 
//    Rev 1.31   Aug 01 2012 07:23:10   panatcha
// IN2956851 - disable control related to NR301exempt type
// 
//    Rev 1.30   Jul 27 2012 07:23:46   panatcha
// IN2956851 - disable control related to NR301exempt type
// 
//    Rev 1.29   May 22 2012 14:31:58   wp040100
// IN 2956851 - 
// 1. Exempt Amount and Remain Exempt Amount has been reset for NR301
// 2. Exempt Amount and Remain Exempt Amount would be greyed out for NR301
// (earlier only when exempt scope is full Exempt Amount and Remain Amount was greyed out, now irrespective of exempt scope we are greying out Exempt Amount and Remain Exempt Amount)
// 
//    Rev 1.28   May 18 2012 17:07:04   wp040100
// IN 2956851 - Exempt Amount and Remain Amount has been reset for NR301
// 
//    Rev 1.27   Apr 24 2012 16:14:02   wp040100
// IN # 2927658 - Added 0015 code which comes under Canadian Jurisdiction.
// 
//    Rev 1.26   Feb 28 2012 10:57:34   wp040100
// IN 738538 - P0194640 FN02 - Non-Resident Withholding Tax - code review comments.
// 
//    Rev 1.25   Feb 24 2012 12:34:56   wp040100
// IN 738538 - P0194640 FN02 - Non-Resident Withholding Tax - Bug Fix
// 
//    Rev 1.24   Feb 16 2012 17:57:16   wp040143
// P0194640 FN02 - Non-Resident Withholding Tax
// 
//    Rev 1.23   Feb 13 2012 18:08:30   wp040100
// P0194640 FN02 - Non-Resident Withholding Tax - Jurisdiction validation changes
// 
//    Rev 1.22   Feb 07 2012 22:25:06   wp040100
// P0194640 FN02 - Non-Resident Withholding Tax
// 
//    Rev 1.21   Nov 22 2011 03:53:00   kitticha
// PETP0188150 FN01 IN2740213 - Reason code validation.
// 
//    Rev 1.20   Oct 21 2011 09:48:34   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.19   Jul 30 2009 19:28:28   dchatcha
// IN#1708647 - There is no option for W8 on the Exempt Authorization Screen.
// 
//    Rev 1.18   Nov 15 2006 16:57:02   popescu
// Incident# 750524 - track the receipt of W9 forms
// 
//    Rev 1.17   Apr 13 2006 11:49:30   jankovii
// Fixed required fields for option 01, and 02.
// 
//    Rev 1.16   Jan 12 2006 15:18:26   jankovii
// Incident #517863 - Validation for acct owner will be gone in Exempt Authorization screen.
// 
//    Rev 1.15   Jan 04 2006 16:50:28   popescu
// Incident# 510611 - restored version 1.13
// 
//    Rev 1.14   Jan 04 2006 16:20:50   jankovii
// Incident #510701- EUSD Exempt Authorization wrong error message
// 
//    Rev 1.11   Jan 04 2006 10:53:30   jankovii
// Incident #510611 - EUSD Exempt Authorization screen fields default
// 
//    Rev 1.10   Dec 09 2005 16:14:16   jankovii
// PET1228_FN01_EU Savings Directive Phase Two.
// 
//    Rev 1.9   Nov 28 2005 09:46:20   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
// 
//    Rev 1.8   Apr 28 2005 15:07:20   georgeet
// Incident 299136 WO 32814: Cert Number must be validated when switching between different Reason Codes.
// 
//    Rev 1.7   Apr 28 2005 11:32:28   georgeet
// Incident 295743 WO 32814: Gap missed in EBS.  Jurisdiction field is a mandatory field for EUSD.
// 
//    Rev 1.6   Apr 21 2005 13:32:42   ZHANGCEL
// Incident #293920 -- All of the entity should show up on the list for Join Account
// 
//    Rev 1.5   Apr 21 2005 10:20:06   ZHANGCEL
// Incident #292340 -- Added AccountNum into CLASS_FIELD_INFO
// 
//    Rev 1.4   Mar 04 2005 16:32:32   georgeet
// PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
// 
//    Rev 1.3   Dec 08 2004 15:43:32   zhangcel
// PET910 - NET Conversion
// 
//    Rev 1.2   Nov 14 2004 14:56:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 20 2004 10:38:50   ZHANGCEL
// PET1082-FNrlc --  AdminFee enhancement
// 
//    Rev 1.0   Aug 06 2004 17:45:48   ZHANGCEL
// Initial revision.
 
 */
