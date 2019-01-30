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
// ^FILE   : Entity.cpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : 
//
// ^CLASS    : Entity
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "accountcommitment.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "acctcutofftimeslist.hpp"
#include "acctentityvalidation.hpp"
#include "addressentitylist.hpp"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "demographics.hpp"
#include "documenttypeoverridelist.hpp"
#include "entity.hpp"
#include "entityidslist.hpp"
#include "entityids.hpp"
#include "errmsgruleslist.hpp"
#include "entityregdetailslist.hpp"
#include "EntityRegJurisDetailsList.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "WhereUsedList.hpp"
#include "MFAccountList.hpp"
#include "RegDocumentList.hpp"
#include "residency.hpp"
#include "rrif_lif_lrif_info.hpp"
#include "rrif_lif_lrif_infolist.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "translationtable.hpp"
#include "worksessionentitylist.hpp"
#include "EntityRiskList.hpp"

#include <ifastdataimpl\dse_dstc0051_req.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0417_req.hpp>
#include <ifastdataimpl\dse_dstc0417_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_mandatory_field.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_country_of_exposure_is_required.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_country_of_exposure_is_required.h>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_IDS;
   extern CLASS_IMPORT const DSTCRequest SEARCH;
   extern CLASS_IMPORT const DSTCRequest ENTITY_SEARCHID_VALIDATION_INQUIRY;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const NATIONALITY_IS_NOT_POPULATED;        // Error # to entity nationlity field
   extern CLASS_IMPORT I_CHAR * const BENEFICIARY_GENDER_MISSING;
   extern CLASS_IMPORT I_CHAR * const MISSING_NEQ;
   extern CLASS_IMPORT I_CHAR * const LOAN_TYPE_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_LOAN_TYPE;
   extern CLASS_IMPORT I_CHAR * const LOAN_NUM_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_LOAN_NUM;
   extern CLASS_IMPORT I_CHAR * const LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const LOAN_TYPE_FOR_ESCROW;
   extern CLASS_IMPORT I_CHAR * const LOAN_NUM_FOR_ACCTHOLDER;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern CLASS_IMPORT I_CHAR * const TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const ENTITY_CATEGORY_IS_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const DIFFERENT_REG_AGENT;
   extern CLASS_IMPORT I_CHAR * const ID_NUMBER_IS_REQUIRED_FOR_INDIVIDUAL;
   extern CLASS_IMPORT I_CHAR * const EMPLOYER_NUMBER_IS_REQUIRED_FOR_CORPORATE;
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURID;
   extern CLASS_IMPORT I_CHAR * const GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern CLASS_IMPORT I_CHAR * const RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern CLASS_IMPORT I_CHAR * const TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern CLASS_IMPORT I_CHAR * const ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION;
   extern CLASS_IMPORT I_CHAR * const COUNTRY_OF_EXPOSURE_IS_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const ANNUITANT_DOFBIRTH_IS_CHANGING;
   extern CLASS_IMPORT I_CHAR * const RDSP_BENEFICIARY_NON_RESIDENT;
   extern CLASS_IMPORT I_CHAR * const EMAIL_PHONE_CANNOT_BE_BLANK;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                     = I_( "Entity" );
   const I_CHAR * const EntityIdsListDesc             = I_( "EntityIdsList" );
   const I_CHAR * const AddressEntityListDesc         = I_( "AddressEntityList" );
   const I_CHAR * const GROUPCODE_EMPLOYEE_CLASS      = I_( "EA" );
   const I_CHAR * const GROUPCODE_RISK_LEVEL          = I_( "RK" );
   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );
   const I_CHAR * const SORTED_BY_LAST_NAME           = I_( "LN" );
   const I_CHAR * const NOMINEE_OWNER                 = I_( "21" );
   const I_CHAR * const REG_DOCUMENT_LIST             = I_( "RegDocumentList" );
   const I_CHAR * const DEMOGRAPHICS_LIST             = I_( "DemographicsList" );
   const I_CHAR * const DEATHCLAIM                    = I_( "1" );
   const I_CHAR * const DEFAULT_DATE                  = I_( "12319999");
   const I_CHAR * const CLEARING_PLATFORM             = I_( "58" ); //MT535/MT536
   const I_CHAR * const CLEARING_PLATFORM_ID_TYPE     = I_( "18" ); //MT535/MT536

   const I_CHAR * const WHERE_USED_FUND_BROKER        = I_( "01" );
   const I_CHAR * const WHERE_USED_ACCOUNT            = I_( "02" );
   const I_CHAR * const WHERE_USED_ENTITY_ALONE       = I_( "03" );
   const I_CHAR * const WHERE_USED_FUND               = I_( "04" );
   const I_CHAR * const WHERE_USED_REGISTRATION_AGENT =I_( "14" );

   const I_CHAR * const RESP_BENEFICIARY              = I_( "50" );
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE      = I_( "9" );
   const I_CHAR * const FAMILY_RESP_TAX_TYPE          = I_( "M" );
   const I_CHAR * const TFSA_TAX_TYPE                 = I_( "V" );
   const I_CHAR * const RRSP_TAX_TYPE                 = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE                 = I_( "2" ); 
   const I_CHAR * const HRDC_RELATECODE_UNCLE         = I_( "3" );
   const I_CHAR * const HRDC_RELATECODE_NOT_RELATED   = I_( "5" );
   const I_CHAR * const HRDC_RELATECODE_OTHER         = I_( "6" );
   const I_CHAR * const ACCOUNT_OWNER                 = I_( "01" );
   const I_CHAR * const ANNUITANT					  = I_( "05" );
   const I_CHAR * const SUCCESSOR_ANNUITANT           = I_( "15" );
   const I_CHAR * const DECEASED_ANNUITANT            = I_( "16" );
   const I_CHAR * const FORMER_SPOUSE                 = I_( "57" );
   const I_CHAR * const UNASSIGNED_COUNTRY            = I_( "0000" );
   const I_CHAR * const EXTERNAL_PRODUCT_PROVIDER     = I_( "22" );
   const I_CHAR * const CLIENT                        = I_( "03" );
   const I_CHAR * const ESCROW_ENTITY                 = I_( "11" );
   const I_CHAR * const ESTATE_OF_DECEASED            = I_( "68" );
   const I_CHAR * const NATIONAL_ID                   = I_( "05" );
   const I_CHAR * const PASSPORT                      = I_( "02" );
   const I_CHAR * const INDIVIDUAL_ACCOUNT_TYPE_LIST  = I_( "0,1,2" );
   const I_CHAR * const RESP_TAX_TYPES                = I_( "9,M" );
   const I_CHAR * const RELATED_PARTY                 = I_( "71" );
   const I_CHAR * const APPLICABLE_TO_ALL             = I_( "*" );
   const I_CHAR * const COMPLY_RULES_SET              = I_( "RW" );
   const I_CHAR * const POLITICALLY_EXPOSED_PERSON    = I_( "3" );
   const I_CHAR * const LEAD_ACCOUNT_MANAGER_ENTITY_TYPE   = I_( "76" );
   const I_CHAR * const ACCOUNT_MANAGER_ENTITY_TYPE        = I_( "77" );
   const I_CHAR * const TAX_FILE_NUMBER               = I_( "46" );
   const I_CHAR * const AUSTRALIAN_BUSINESS_NUMBER    = I_( "47" );
   const I_CHAR * const RDSP_TAX_TYPE				  = I_( "RS" );
   const I_CHAR * const RDSP_BENEFICIARY			  = I_( "79" );
   const I_CHAR * const RDSP_PCG					  = I_( "80" );
   const I_CHAR * const ENTITYSEARCH_CATEGORY            = I_("4");
   const I_CHAR * const ENTITYSEARCH_LEVEL               = I_("02");
   const I_CHAR * const UNVERIFIED                       = I_("02");
   const I_CHAR * const VERIFIED                         = I_("01");
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_ADD_ENTITY_DEATH_DATE;
   extern const long ERR_EARLY_DEATH_DATE;
   extern const long ERR_FUTURE_BIRTHDATE;
   extern const long ERR_FUTURE_DEATHDATE;
   extern const long ERR_DEATH_NOTIF_NO_DEATH_DATE;
   extern const long ERR_DEATH_NOTIF_BEFORE_DEATH_DATE;
   extern const long ERR_EFFECTIVE_DATE_MUST_BE_ENTERED;
   extern const long ERR_LANGUAGE_MUST_BE_ENTERED;
   extern const long ERR_BIRTHNAME_REQUIRED;
   extern const long ERR_FUTURE_DEATH_NOTIFY;
   extern const long ERR_INVALID_SIN;
   extern const long ERR_WARN_SIN_IS_MISSING;
   extern const long ERR_ENTITY_NATIONALITY_BLANK;
   extern const long WARN_ENTITY_NATIONALITY_BLANK;
   extern const long ERR_DATE_OF_BIRTH_REQUIRED;
   extern const long WARN_DATE_OF_BIRTH_EMPTY;
   extern const long ERR_OCCUPATION_REQUIRED;
   extern const long WARN_OCCUPATION_EMPTY;
   extern const long ERR_ENTITY_MAY_USED_BY_OTHER_PLACES;
   extern const long ERR_NS_DUPLICATE_BICCODE;
   extern const long WARN_NS_DUPLICATE_BICCODE;
   extern const long WARN_INVALID_PHONE_FAX_NUMBER;
   extern const long WARN_INVALID_AREA_CODE;
   extern const long WARN_EMPTY_AREA_CODE_PHONE_NUMBER;
   extern const long ERR_NOMINEE_ENTITY_INUSE;
   extern const long WARN_DEATH_CLAIM_UPDATE;
   extern const long ERR_DEATHCLAIM_DOC_BLANK;
   extern const long ERR_CLEARING_PLATFORM_MUST_BE_CORPORATE;
   extern const long ERR_CLEARING_PLATFORM_ID_TYPE_REQUIRED;
   extern const long ERR_CLEARING_PLATFORM_ID_VALUE_REQUIRED;
   extern const long ERR_BACKDATED_ENTITY_TAX_JURISDICTION_NOT_ALLOWED_FOR_RESP;
   extern const long ERR_SIN_DUPLIATE_WITH_OTHER_ACCOUNT_ENTITY;
   extern const long ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100;
   extern const long ERR_TAX_JURIS_INVALID;
   extern const long ERR_GENDER_REQUIRED_FOR_ENTITY_TYPE;
   extern const long ERR_LANGUAGE_MUST_BE_ENTERED;
   extern const long ERR_DOB_RESP_BENEF_REQUIRED;
   extern const long WARN_GENDER_REQUIRED_FOR_ENTITY_TYPE;
   extern const long WARN_DOB_RESP_BENEF_REQUIRED;
   extern const long ERR_MISSING_NEQ;
   extern const long WARN_MISSING_NEQ;
   extern const long WARN_TFSA_DECEASED_ANNUITANT_DOD_UPDATED;
   extern const long WARN_TFSA_UPDATE_EFFECTIVE_DATE_REQUIRED;
   extern const long ERR_LOAN_TYPE_MANDATORY;
   extern const long WARN_LOAN_TYPE_MANDATORY;
   extern const long ERR_DUPLICATE_LOAN_TYPE;
   extern const long WARN_DUPLICATE_LOAN_TYPE;
   extern const long ERR_LOAN_NUM_MANDATORY;
   extern const long WARN_LOAN_NUM_MANDATORY;
   extern const long ERR_DUPLICATE_LOAN_NUM;
   extern const long WARN_DUPLICATE_LOAN_NUM;
   extern const long ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern const long WARN_LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern const long WARN_TAX_ID_NUMBER_NOT_PROVIDED;
   extern const long ERR_LOAN_TYPE_FOR_ESCROW;
   extern const long WARN_LOAN_TYPE_FOR_ESCROW;
   extern const long ERR_LOAN_NUM_FOR_ACCTHOLDER;
   extern const long WARN_LOAN_NUM_FOR_ACCTHOLDER;
   extern const long ERR_NATIONAL_ID_REQUIRED_FOR_TAX_TYPE;
   extern const long ERR_NATIONAL_ID_OR_PASSPORT_REQUIRED_FOR_TAX_TYPE;
   extern const long ERR_BENE_OVER_AGE_OF_15;
   extern const long ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long ERR_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long WARN_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long ERR_ENTITY_CATEGORY_IS_REQUIRED;
   extern const long WARN_ENTITY_CATEGORY_IS_REQUIRED; 
   extern const long ERR_DIFFERENT_REG_AGENT;
   extern const long WARN_DIFFERENT_REG_AGENT;
   extern const long ERR_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY;
   extern const long WARN_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY;
   extern const long ERR_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long WARN_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY;
   extern const long ERR_DEFF_CANNOT_LESS_THAN_INIT_DEFF;
   extern const long ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER;
   extern const long ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION;
   extern const long ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_NON_RESIDENT_TAX_JURID;
   extern const long WARN_NON_RESIDENT_TAX_JURID;
   extern const long WARN_ENSURE_PAC_IS_ALLOWED;
   extern const long ERR_ONLY_RESP_CAN_HAVE_CORPORATE_AS_ACCOUNTHOLDER;
   extern const long ERR_PCG_REQURIED_FOR_COPORATE_RESP_ACCT_HOLDER;
   extern const long ERR_TAX_JURIS_EMPTY;
   extern const long WARN_TAX_JURIS_CHANGED_ENSURE_RRIF_IS_FOLLOWED_NEW_TAX;
   extern const long WARN_TAX_JURIS_CHANGED_EFFECTIVE_DATE_SAME;
   extern const long ERR_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT;
   extern const long WARN_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT;
   //extern const long WARN_REVIEW_SAGES_APPLICATION_DUE_TO_TAX_JURISDICTION_CHANGES;
   extern const long ERR_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern const long WARN_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern const long ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern const long WARN_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern const long ERR_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern const long WARN_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern const long ERR_EMAIL_IS_MISSING;
   extern const long ERR_FIRST_NAME_IS_MISSING;
   extern const long ERR_ACCOUNT_MANAGER_ID_MANDATORY;
   extern const long ERR_HIGHEST_RISK_LVL_IS_REQUIRED;
   extern const long WARN_HIGHEST_RISK_LVL_IS_REQUIRED;
   extern const long ERR_FIELD_VAL_REQUIRED_PLS_ENTER;
   extern const long ERR_INVALID_HIGHEST_RISK_LEVEL;
   extern const long WARN_INVALID_HIGHEST_RISK_LEVEL;
   extern const long ERR_ANNUITANT_DOFBIRTH_IS_CHANGING;
   extern const long WARN_ANNUITANT_DOFBIRTH_IS_CHANGING;
   extern const long ERR_RDSP_BENEFICIARY_NON_RESIDENT;
   extern const long WARN_RDSP_BENEFICIARY_NON_RESIDENT;
   extern const long ERR_DEATHDATE_UPDATION_DISABLED;
   extern const long ERR_DEATHDATE_NOTIFICATION_UPDATION_DISABLED;
   extern const long WARN_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK;
   extern const long ERR_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFNumericFieldId SpouseEntityID;
   extern CLASS_IMPORT const BFTextFieldId NAME_LENGTH;
   extern CLASS_IMPORT const BFTextFieldId SalutationSetField;
   extern CLASS_IMPORT const BFTextFieldId EntityRiskLevel;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId EUSDTaxOption;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFDateFieldId TaxJurisDeff;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId DefEUSDOption;
   extern CLASS_IMPORT const BFTextFieldId DeathClaimDocExist;
   extern CLASS_IMPORT const BFTextFieldId TFSALastAmendTaxYear;
   extern CLASS_IMPORT const BFTextFieldId LanguageDefault;
   extern CLASS_IMPORT const BFTextFieldId FATCAFFI;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFNumericFieldId OrigAccountNum;
   extern CLASS_IMPORT const BFTextFieldId RecipientType;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveFrom;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId CurrentSelectedEntityType;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClassForFATCA;
   extern CLASS_IMPORT const BFTextFieldId CurrentEntRegAcctNum;
   extern CLASS_IMPORT const BFTextFieldId TOExistAfterPreElectReset;
   extern CLASS_IMPORT const BFTextFieldId RiskApplEntity;
   extern CLASS_IMPORT const BFTextFieldId RiskApplEntitySeq;
   extern CLASS_IMPORT const BFTextFieldId RiskForAcctHldrRsk;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
   extern CLASS_IMPORT const BFTextFieldId RiskApplEntity;
   extern CLASS_IMPORT const BFTextFieldId RiskApplEntitySeq;
   extern CLASS_IMPORT const BFTextFieldId RiskForAcctHldrRsk;
   extern CLASS_IMPORT const BFTextFieldId RiskLevel;
   extern CLASS_IMPORT const BFTextFieldId MiscCode;
   extern CLASS_IMPORT const BFTextFieldId VerifyStatDetails;
}

namespace ENTITY_CATEGORY
{
   extern const I_CHAR * const NOT_APPICABLE;
   extern const I_CHAR * const INDIVIDUAL;
   extern const I_CHAR * const CORPORATE;
   extern const I_CHAR * const TRUST;
}

namespace IDS
{
   extern const I_CHAR * const SIN;
   extern const I_CHAR * const TAX_ID_NUMBER;
   extern const I_CHAR * const BUSINESS_NUMBER;
   extern const I_CHAR * const CLEARING_PLATFORM;
   extern const I_CHAR * const BIC_CODE;
   extern const I_CHAR * const TRUST_ACCOUNT_NUMBER;
   extern const I_CHAR * const EMPLOYER_NUMBER;
   extern const I_CHAR * const ACCOUNT_MANAGER_UNIQUE_ID;
}

namespace ACCOUNT_TYPE
{
   extern const I_CHAR * const CORPORATE = I_("4");
}

namespace COMPLY_RULE
{
   extern CLASS_IMPORT const DString AcctRegistration; 
   extern CLASS_EXPORT const DString DeathClaim ;
   extern CLASS_EXPORT const DString TaxCompliant;
   extern CLASS_EXPORT const DString AccountholderRisk;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::EntityId,                 BFCBO::REQUIRED,              0},
   {ifds::LastName,                 BFCBO::REQUIRED,              0},
   {ifds::FirstName,                BFCBO::NONE,                  0}, 
   {ifds::Salutation,               BFCBO::NONE,                  0}, 
   {ifds::BirthLastName,            BFCBO::NONE,                  0}, 
   {ifds::BirthFirstName,           BFCBO::NONE,                  0}, 
   {ifds::DofBirth,                 BFCBO::NONE,                  0}, 
   {ifds::BirthPlace,               BFCBO::NONE,                  0}, 
   {ifds::CountryOfBirth,           BFCBO::NONE,                  0}, 
   {ifds::RiskLevel,                BFCBO::NONE,                  0}, 
   {ifds::Gender,                   BFCBO::NONE,                  0}, 
   {ifds::SIN,                      BFCBO::NONE,                  0}, 
   {ifds::Language,                 BFCBO::NONE,                  0}, 
   {ifds::LanguageCode,             BFCBO::REQUIRED,              0},
   {ifds::Nationality,              BFCBO::NONE,                  0},
   {ifds::HomePhone,                BFCBO::NONE,                  0}, 
   {ifds::BusinessPhone,            BFCBO::NONE,                  0}, 
   {ifds::BusinessExt,              BFCBO::NONE,                  0}, 
   {ifds::BusinessFax,              BFCBO::NONE,                  0}, 
   {ifds::Telex,                    BFCBO::NONE,                  0}, 
   {ifds::Email,                    BFCBO::NONE,                  0}, 
   {ifds::ContactName,              BFCBO::NONE,                  0}, 
   {ifds::DofDeath,                 BFCBO::NONE,                  0}, 
   {ifds::DofDeathNotice,           BFCBO::NONE,                  0}, 
   {ifds::EffectiveDate,            BFCBO::NONE,                  0}, 
   {ifds::HomeFax,                  BFCBO::NONE,                  0}, 
   {ifds::OccupationCode,           BFCBO::NONE,                  0}, 
   {ifds::OccupationDesc,           BFCBO::NONE,                  0}, 
   {ifds::ProcessDate,              BFCBO::NONE,                  0}, 
   {ifds::EntityIdentityVer,        BFCBO::REQUIRED,              0},
   {ifds::EntityIdentityRid,        BFCBO::REQUIRED,              0},
   {ifds::CompoundDate,             BFCBO::NONE,                  0}, 
   {ifds::HomePhoneArea,            BFCBO::NONE,                  0}, 
   {ifds::BusinessPhoneArea,        BFCBO::NONE,                  0}, 
   {ifds::HomeFaxArea,              BFCBO::NONE,                  0}, 
   {ifds::BusFaxArea,               BFCBO::NONE,                  0}, 
   {ifds::EmployeeClass,            BFCBO::NONE,                  0}, 
   {ifds::OtherOccupation,          BFCBO::NONE,                  0}, 
   {ifds::SpouseEntityID,           BFCBO::NONE,                  0},
   {ifds::TaxJuris,                 BFCBO::NONE,                  0},
   {ifds::EUSDTaxOption,            BFCBO::NONE,                  0},
   //{ifds::FATCAFFI,                 BFCBO::NONE,                  0},
   {ifds::UpdShrTaxJuris,           BFCBO::NONE,                  0},
   {ifds::TaxJurisDeff,             BFCBO::NONE,                  0},
   {ifds::WhereUse,                 BFCBO::NONE,                  0},
   {ifds::IdType,                   BFCBO::NONE,                  0},
   {ifds::IdValue,                  BFCBO::NONE,                  0},
   {ifds::NAME_LENGTH,              BFCBO::CALCULATED_FIELD,      0},
   {ifds::Email2,                   BFCBO::NONE,                  0},
   {ifds::SecondPhoneNum,           BFCBO::NONE,                  0},
   {ifds::SecondPhoneNumExt,        BFCBO::NONE,                  0},
   {ifds::LanguageDefault,          BFCBO::NONE,                  0},
   {ifds::CountryOfExposure,        BFCBO::NONE,                  0},
   {ifds::CurrentSelectedEntityType,BFCBO::NOT_ON_HOST,           0},
   {ifds::CurrentEntRegAcctNum,     BFCBO::NOT_ON_HOST,           0},
   {ifds::VerifyStatDetails,        BFCBO::NONE,                  0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,       Group Flags 
//   { I_("EntityIdsList"),      BFBase::REQUIRED,  0 },
   { I_("EntityIdsList"),      BFCBO::NONE,  0},
   { I_("AddressEntityList"),  BFCBO::NONE,  0},
   { I_("WhereUsedList"),      BFCBO::NONE,  0},
};

static const int NUM_OBJECTS = sizeof (classObjectInfo) / sizeof (BFCBO::CLASS_OBJECT_INFO);

bool Entity::bUsedByEntityAlone = false;

namespace IDS
{
   extern const I_CHAR * const BIC_CODE;
   extern const I_CHAR * const LOAN_TYPE;
   extern const I_CHAR * const LOAN_NUMBER;
   extern const I_CHAR * const NATIONAL_ID;
   extern const I_CHAR * const PASSPORT;
}

namespace TAX_TYPES
{
   const I_CHAR * const OA   = I_(  "OA" );
   const I_CHAR * const SA   = I_(  "SA" );
   const I_CHAR * const SRS   = I_( "SR" );
}

//******************************************************************************
Entity::Entity (BFAbstractCBO &parent) : MFCanBFCbo (parent),
_pResponseData (NULL),
_bIsDirty (false),
_pErrMsgRulesList (NULL),
_bRefresh (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo);
   addCrossEdit (ifds::CompoundDate, ifds::DofBirth);
   addCrossEdit (ifds::CompoundDate, ifds::DofDeath);   
}

//******************************************************************************
Entity::~Entity ()
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (_pResponseData)
   {
      delete _pResponseData;
      _pResponseData = NULL;
   }
}

//this init is used in mfcommonbusinessmanager to set the worksessionid on the object
//******************************************************************************
SEVERITY Entity::init (const DString& entityId, 
                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _entityId = entityId;
   setObjectNew( );
   setFieldNoValidate (ifds::EntityId, entityId, idDataGroup, true);
   setFieldNoValidate (ifds::EntityId, entityId, BF::HOST, true);

   //load the entity object with default values taken from the datadictionary
   DString dstrOption, dstrCurrBusDate;
   getWorkSession ().getOption (ifds::BirthNameMand, dstrOption, idDataGroup);  
   if (dstrOption.strip ().upperCase () == I_("Y"))
   {
      setFieldRequired (ifds::BirthLastName, idDataGroup, true);
   }
   initializeSubstitutionList (ifds::RiskLevel, GROUPCODE_RISK_LEVEL, idDataGroup);
   initWithDefaultValues (idDataGroup);
   initializeSubstitutionList (ifds::EmployeeClass, GROUPCODE_EMPLOYEE_CLASS, idDataGroup);
   clearUpdatedFlags (idDataGroup);   
   setFieldNoValidate (ifds::UpdShrTaxJuris, NO, idDataGroup);

   if (_pErrMsgRulesList == NULL)
   {
      SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList (_pErrMsgRulesList);
   }
   if (_pErrMsgRulesList)
   {
      DString strErrValue;

      _pErrMsgRulesList->getEWIValue (IFASTERR::NATIONALITY_IS_NOT_POPULATED, idDataGroup, strErrValue);

      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::Nationality, idDataGroup, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("385"), idDataGroup, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::DofBirth, idDataGroup, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("386"), idDataGroup, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::OccupationCode, idDataGroup, false);
      }
   }
   doApplyRelatedChanges (ifds::EmployeeClass, idDataGroup);
   setFieldSubstituteValues (ifds::Salutation, idDataGroup, ifds::SalutationSetField);
   initVerifyStatus (idDataGroup, isNew());
   _bInit = false;

   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
// this data represents account-entity relationship (view50 result)
SEVERITY Entity::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //attachDataObject (const_cast<Data&> (data), false, true);
   _entityId = data.getElementValue (ifds::EntityId, BFDataField::USE_MASK);
   _entityId.strip ();
   _entityType = data.getElementValue (ifds::EntityType);
   _entityType.strip ();
   
   initializeSubstitutionList (ifds::EmployeeClass, GROUPCODE_EMPLOYEE_CLASS, BF::HOST);
   initializeSubstitutionList (ifds::RiskLevel, GROUPCODE_RISK_LEVEL, BF::HOST);

   if (!_entityId.empty ())
   {
      setFieldNoValidate (ifds::EntityId, _entityId, BF::HOST, true);
      clearUpdatedFlags (BF::HOST);
   }
   setFieldNoValidate (ifds::UpdShrTaxJuris, NO, BF::HOST);


   // the code below is against our basic rules
   // I wonder how it was working? I don't have time to clean the code like this.
   // Yingbao, Feb 16,2005

   if (_pErrMsgRulesList == NULL)
   {
      SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList (_pErrMsgRulesList);
   }
   if (_pErrMsgRulesList)
   {
      DString strErrValue;

      _pErrMsgRulesList->getEWIValue (IFASTERR::NATIONALITY_IS_NOT_POPULATED, BF::HOST, strErrValue);

      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::Nationality, BF::HOST, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("385"), BF::HOST, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::DofBirth, BF::HOST, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("386"), BF::HOST, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::OccupationCode, BF::HOST, false);
      }
   }
   //init (strEntityNum);
   doApplyRelatedChanges (ifds::EmployeeClass, BF::HOST);
   setFieldSubstituteValues (ifds::Salutation, BF::HOST, ifds::SalutationSetField); 
   initVerifyStatus (BF::HOST, false);
   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::init (const DString& strEntityNum) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init (int)"));
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      BFData queryData (ifds::DSTC0051_REQ);
      BFData *response = new BFData (ifds::DSTC0051_VW);

      DString mgmtCoIdOut;
      queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      queryData.setElementValue (ifds::EntityId, strEntityNum); 

      if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::ENTITY_IDS, 
         queryData, *response, DSTCRequestor (getSecurity ())) <= WARNING)
      {
         _entityId = strEntityNum; //set the EntityId for the current entity
         setFieldNoValidate (ifds::EntityId, _entityId, BF::HOST, true);

         EntityIdsList* pEntityIdsList = new EntityIdsList (*this);
         attachDataObject (*response, true, false);
         if (_entityType.empty())
         {
            AccountEntityXref *pAEXref (NULL);
            
            if (getWorkSession ().getAccountEntityXref (BF::HOST, pAEXref) <= WARNING)
            {
               DString searchKey;
               BFObjIter iter (*pAEXref, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED);

               AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
               //make an attempt to find the type
               if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
               {
                  iter.positionByKey (searchKey);
                  if (!iter.end())
                  {
                     iter.getObject()->getField (ifds::EntityType, _entityType, BF::HOST, false);
                  }
               }
            }
         }
         pEntityIdsList->init (*response, _entityId, _entityType);
         setObject (pEntityIdsList, EntityIdsListDesc, OBJ_ACTIVITY_NONE, BF::HOST); 
         setSINToEntity (BF::HOST);
      }
      else
      {
         delete response;
      }
   }
   catch(...)
   {
      assert(0);
   }

   initializeSubstitutionList (ifds::EmployeeClass, GROUPCODE_EMPLOYEE_CLASS, BF::HOST);
   initializeSubstitutionList (ifds::RiskLevel, GROUPCODE_RISK_LEVEL, BF::HOST);

   doApplyRelatedChanges (ifds::EmployeeClass, BF::HOST);
   setFieldSubstituteValues (ifds::Salutation, BF::HOST, ifds::SalutationSetField);
   clearUpdatedFlags (BF::HOST);
   setAllFieldsReadOnlyforAccountRelated( BF::HOST );
   setAllSubstituteValuesForTaxOption( BF::HOST );
   setFieldNoValidate (ifds::UpdShrTaxJuris, NO, BF::HOST);
   DString status;
   getField(ifds::GoodBad,status, BF::HOST,false );
   status.strip().upperCase();
   if (status == I_("N"))
   {
      setFieldReadOnly( ifds::EntityId,          BF::HOST, true );
      setFieldReadOnly( ifds::LastName,          BF::HOST, true );
      setFieldReadOnly( ifds::FirstName,         BF::HOST, true );
      setFieldReadOnly( ifds::Salutation,        BF::HOST, true );
      setFieldReadOnly( ifds::BirthLastName,     BF::HOST, true );
      setFieldReadOnly( ifds::BirthFirstName,    BF::HOST, true );
      setFieldReadOnly( ifds::DofBirth,          BF::HOST, true );
      setFieldReadOnly( ifds::BirthPlace,        BF::HOST, true );
      setFieldReadOnly( ifds::CountryOfBirth,    BF::HOST, true );
      setFieldReadOnly( ifds::RiskLevel,         BF::HOST, true );
      setFieldReadOnly( ifds::Gender,            BF::HOST, true );
      setFieldReadOnly( ifds::SIN,               BF::HOST, true );
      setFieldReadOnly( ifds::Language,          BF::HOST, true );
      setFieldReadOnly( ifds::LanguageCode,      BF::HOST, true );
      setFieldReadOnly( ifds::Nationality,       BF::HOST, true );
      setFieldReadOnly( ifds::HomePhone,         BF::HOST, true );
      setFieldReadOnly( ifds::BusinessPhone,     BF::HOST, true );
      setFieldReadOnly( ifds::BusinessExt,       BF::HOST, true );
      setFieldReadOnly( ifds::BusinessFax,       BF::HOST, true );
      setFieldReadOnly( ifds::Telex,             BF::HOST, true );
      setFieldReadOnly( ifds::Email,             BF::HOST, true );
      setFieldReadOnly( ifds::ContactName,       BF::HOST, true );
      setFieldReadOnly( ifds::DofDeath,          BF::HOST, true );
      setFieldReadOnly( ifds::DofDeathNotice,    BF::HOST, true );
      setFieldReadOnly( ifds::EffectiveDate,     BF::HOST, true );
      setFieldReadOnly( ifds::HomeFax,           BF::HOST, true );
      setFieldReadOnly( ifds::OccupationCode,    BF::HOST, true );
      setFieldReadOnly( ifds::OccupationDesc,    BF::HOST, true );
      setFieldReadOnly( ifds::ProcessDate,       BF::HOST, true );
      setFieldReadOnly( ifds::EntityIdentityVer, BF::HOST, true );
      setFieldReadOnly( ifds::EntityIdentityRid, BF::HOST, true );
      setFieldReadOnly( ifds::CompoundDate,      BF::HOST, true );
      setFieldReadOnly( ifds::HomePhoneArea,     BF::HOST, true );
      setFieldReadOnly( ifds::BusinessPhoneArea, BF::HOST, true );
      setFieldReadOnly( ifds::HomeFaxArea,       BF::HOST, true );
      setFieldReadOnly( ifds::BusFaxArea,        BF::HOST, true );
      setFieldReadOnly( ifds::EmployeeClass,     BF::HOST, true );
      setFieldReadOnly( ifds::OtherOccupation,   BF::HOST, true );
      setFieldReadOnly( ifds::SpouseEntityID,    BF::HOST, true );
      setFieldReadOnly( ifds::TaxJuris,          BF::HOST, true );
      setFieldReadOnly( ifds::EUSDTaxOption,     BF::HOST, true );
      setFieldReadOnly( ifds::UpdShrTaxJuris,    BF::HOST, true );
      setFieldReadOnly( ifds::TaxJurisDeff,      BF::HOST, true );
      setFieldReadOnly( ifds::WhereUse,          BF::HOST, true );
      setFieldReadOnly( ifds::Email2,            BF::HOST, true );
      setFieldReadOnly( ifds::SecondPhoneNum,    BF::HOST, true );
      setFieldReadOnly( ifds::SecondPhoneNumExt, BF::HOST, true );
      setFieldReadOnly( ifds::CountryOfExposure, BF::HOST, true );

      EntityRiskList *pEntityRiskList = NULL;
      if (getEntityRiskList(pEntityRiskList, BF::HOST) <= WARNING && pEntityRiskList)
      {
          pEntityRiskList->setAllRiskReadOnly(true, BF::HOST);
      }
   } 

   if( bUsedByEntityAlone )
   {
      setAllFieldsValid( BF::HOST );
      return GETCURRENTHIGHESTSEVERITY();
   }
//
// the code below is against our basic rules
// but it might be used by somebody, I won't delete them for now, 
// insead introduce a flag to skip it for my own purpose
// yingbao  Feb. 16, 2005
//
   if (_pErrMsgRulesList == NULL)
   {
      SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList (_pErrMsgRulesList);
   }
   if (_pErrMsgRulesList)
   {
      DString strErrValue;

      _pErrMsgRulesList->getEWIValue (IFASTERR::NATIONALITY_IS_NOT_POPULATED, BF::HOST, strErrValue);

      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::Nationality, BF::HOST, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("385"), BF::HOST, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::DofBirth, BF::HOST, false);
      }

      _pErrMsgRulesList->getEWIValue (I_("386"), BF::HOST, strErrValue);
      if (strErrValue == I_("E") || strErrValue == I_("W"))
      {
         setValidFlag (ifds::OccupationCode, BF::HOST, false);
      }
   }
   initVerifyStatus (BF::HOST, false);

   return (GETCURRENTHIGHESTSEVERITY ());
}

//support for refresh
//******************************************************************************
SEVERITY Entity::doPreClearFields ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doPreClearFields"));

   //no need to save anything here because we have the entityId
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::reInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("reInit"));

   if (!isNew ())
   {
      init (_entityId);
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//****************************************************************************
SEVERITY Entity::getAddressEntityList (AddressEntityList*& pAddressEntityList, 
                                       const BFDataGroupId& idDataGroup, 
                                       bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAddressEntityList"));
   DString ObjectDesc = AddressEntityListDesc;
   ObjectDesc += _entityId;
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pAddressEntityList = dynamic_cast< AddressEntityList * > (getObject (ObjectDesc, idDataGroup) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pAddressEntityList)
   {
      if (isNew ())
      {
         pAddressEntityList = new AddressEntityList (*this);
         pAddressEntityList->init ();
      }
      else if (inquireDatabase)
      {
         pAddressEntityList = new AddressEntityList (*this);
         pAddressEntityList->init (_entityId);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pAddressEntityList)
      {
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
         {
            setObject (pAddressEntityList, ObjectDesc, OBJ_ACTIVITY_NONE, idWorkingDataGroup);
            pAddressEntityList->setEntityId (_entityId);
         }
         else
         {
            delete pAddressEntityList;
            pAddressEntityList = NULL;
         }
      }
   }
   return (GETCURRENTHIGHESTSEVERITY ());
} 

//****************************************************************************
SEVERITY Entity::getEntityIdsList (EntityIdsList*& pEntityIdsList, 
                                   const BFDataGroupId& idDataGroup, 
                                   bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityIdsList"));

   //check the base to see if we've already built it
   //otherwise, create and store with base
   pEntityIdsList = dynamic_cast< EntityIdsList* > (getObject (EntityIdsListDesc, idDataGroup));
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pEntityIdsList)
   {
      if (isNew ())
      {
         pEntityIdsList = new EntityIdsList (*this);
         pEntityIdsList->init (_entityId, _entityType, idDataGroup);
      }
      else if (inquireDatabase)
      {
         pEntityIdsList = new EntityIdsList (*this);
         pEntityIdsList->init (_entityId, _entityType);

         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pEntityIdsList && GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         setObject ( pEntityIdsList, 
                     EntityIdsListDesc, 
                     OBJ_ACTIVITY_NONE, 
                     idWorkingDataGroup);
      }
      else
      {
         delete pEntityIdsList;
         pEntityIdsList = NULL;
      }
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         if (pEntityIdsList)
         {
            BFObjIter iter ( *pEntityIdsList, 
                             idDataGroup, 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end ())
            {
               DString dstrIdType;

               EntityIds *pEntityIds= dynamic_cast <EntityIds*> (iter.getObject ());
               if (pEntityIds && !isNew ())
               {
                  pEntityIds->getField (ifds::IdType, dstrIdType, idDataGroup);
                  if (dstrIdType != NULL_STRING)
                  {
                     pEntityIds->revalidateField (ifds::IdValue, idDataGroup);
                  }
               }
               ++iter;
            }
         }
         // Lets clear all the conditions raised by the revalidateField.   This is ugly, but fixes
         // a bug PTS 10013818. getPtrForContainer now will not throw when asking for the entityidslist
         // which contains a severe error.

         if (GETCURRENTHIGHESTSEVERITY () > WARNING) 
         {
            CLEARCURRENTCONDITIONS ();
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                 long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
   WhereUsedList* pList = NULL;

   if( getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if (pList)
      {
         if (isNew())
         {
            pList->validateAll( idDataGroup );
         }

         if (pList->isFundSponsor (idDataGroup))
            validateMandatoryId (idDataGroup);
		 else if (pList->isNEQEntity (idDataGroup))
			 doesNEQExists (idDataGroup);
      }
   }

   validateAreaOrPhoneNumber (idDataGroup);
   validateDeathClaimDocStatus (idDataGroup);
   validateTaxJurisForRESP (idDataGroup);
   validateTIN (idDataGroup);
//   validateMandatedIDforCPFTaxTypes(idDataGroup);

   //IN3198343
   validateRESPAcctHolder(idDataGroup);
 
   //IN3323509 - raise a warning if the tax jurisdiction changes and the effective date stays the same 	   	
   DString dstrOrgTaxJurisDeff, dstrTaxJurisDeff;  
   getFieldBeforeImage(ifds::TaxJurisDeff, dstrOrgTaxJurisDeff);
   getField(ifds::TaxJurisDeff, dstrTaxJurisDeff, idDataGroup);  

   if (isFieldChanged (ifds::TaxJuris, idDataGroup) && (DSTCommonFunctions::CompareDates (dstrTaxJurisDeff, dstrOrgTaxJurisDeff) == DSTCommonFunctions::EQUAL))
   {	   
	   ADDCONDITIONFROMFILE(CND::WARN_TAX_JURIS_CHANGED_EFFECTIVE_DATE_SAME);
   } 
   //

   DString dstrAccountNum;
   getAccountNum(dstrAccountNum, idDataGroup); 
   MFAccount *pMFAccount = NULL; 
   if (isUpdatedForDataGroup (idDataGroup)&&
	   getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
	   pMFAccount && (_entityType == I_("01")))//account owner
   {
	   if(!isNew())
	   {
		   bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
		   pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
		   if(bDisplyWarnSICAV)
			   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
		   if(bDisplyWarnOEIC)
			   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
	   }
	
	   /*
		 Copy the validations about taxjurisdiction from Account and Shareholder
		 As we are no longer to update the Shareholder tax jurisdiction.
	   */
	   DString dstrTaxJuris, dstrTaxJurisDesc,
		       dstrRecipientType, dstrRecipientTypeDesc,
			   dstrTaxType, dstrUpdShrTaxJuris;

	   getField(ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);
	   getField(ifds::TaxJuris, dstrTaxJurisDesc, idDataGroup, true);
	   getField(ifds::UpdShrTaxJuris, dstrUpdShrTaxJuris, idDataGroup, false);
	   pMFAccount->getField(ifds::RecipientType, dstrRecipientType, idDataGroup, false);
	   pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);

	   if (dstrUpdShrTaxJuris == I_("Y"))
	   {
		   //values 6 and 7 are only allowed for the provice of Quebec
		   if ( dstrTaxJuris != I_("0006") && 
			   dstrRecipientType == I_("7"))
		   {
			   //raise error
			   DString recCodeDescr,
				   idiStr;

			   pMFAccount->getField (ifds::RecipientType, dstrRecipientTypeDesc, idDataGroup, true);
			   addIDITagValue (idiStr, I_("REC"), dstrRecipientTypeDesc);
			   addIDITagValue (idiStr, I_("JURISD"), dstrTaxJurisDesc);
			   ADDCONDITIONFROMFILEIDI (CND::ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION, idiStr);
		   }

		   if( dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == RRIF_TAX_TYPE )
		   {
			   TaxTypeRule *ptaxTypeRule = NULL;

			   pMFAccount->getTaxTypeRule (ptaxTypeRule, idDataGroup);
			   if( ptaxTypeRule && !ptaxTypeRule->isValidPensionJurisdiction( dstrTaxJuris, idDataGroup ) )
			   {
				   DString idiStr, dstrTaxTypeDesc, dstrPensionJurisName;
				   if( dstrTaxType == RRSP_TAX_TYPE )
					   dstrTaxTypeDesc = I_("RRSP");
				   else
					   dstrTaxTypeDesc = I_("RRIF");

				   getField( ifds::TaxJuris, dstrPensionJurisName, idDataGroup, true );
				   addIDITagValue( idiStr, I_("TAXTYPE"), dstrTaxTypeDesc );
				   addIDITagValue( idiStr, I_("TAXJURIS"), dstrPensionJurisName );
				   ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION, idiStr);
			   }			

			   RRIF_LIF_LRIF_InfoList *rrifList = NULL;
			   if (dstrTaxType == RRIF_TAX_TYPE && pMFAccount->getRRIF_LIF_LRIF_InfoList(rrifList, idDataGroup) <= WARNING && rrifList){
					bool foundActiveRRIFInfo = false;
				    BFObjIter iterRRIFList(*rrifList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
					
					iterRRIFList.begin();
					
					while (!iterRRIFList.end()){
						DString dstrGoodBad, dstrStartDate, dstrStopDate, dstrBusinessDate;

						getWorkSession().getOption(ifds::CurrBusDate, dstrBusinessDate, BF::HOST, false);
						iterRRIFList.getObject()->getField(ifds::GoodBad, dstrGoodBad, idDataGroup);
						iterRRIFList.getObject()->getField(ifds::EffectiveFrom, dstrStartDate, idDataGroup);
						iterRRIFList.getObject()->getField(ifds::StopDate, dstrStopDate, idDataGroup);

						if (dstrGoodBad == Y && DSTCommonFunctions::IsDateBetween(dstrStartDate, dstrStopDate, dstrBusinessDate)){
							foundActiveRRIFInfo = true;
							break;
						}

						++iterRRIFList;
					}  

					if (foundActiveRRIFInfo){
						ADDCONDITIONFROMFILE(CND::WARN_TAX_JURIS_CHANGED_ENSURE_RRIF_IS_FOLLOWED_NEW_TAX);
					}
			   }
		   }
		   else if( dstrTaxType == TFSA_TAX_TYPE )
		   {
			   Residency* residency;
			   if( getWorkSession().getResidency( residency, dstrTaxType, dstrTaxJuris, idDataGroup ) <= WARNING && residency )
			   {
				   if( !residency->isTaxJurisdictionValid() )
				   {
					   getErrMsg ( IFASTERR::NON_RESIDENT_TAX_JURID,
						   CND::ERR_NON_RESIDENT_TAX_JURID,
						   CND::WARN_NON_RESIDENT_TAX_JURID,
						   idDataGroup,
						   NULL_STRING);
				   }
			   }
		   }
		   if (Shareholder::shareholderHasPACWithLSIF (
			   getWorkSession(), 
			   _shrNum, 
			   idDataGroup))
		   {
			   ADDCONDITIONFROMFILE (CND::WARN_ENSURE_PAC_IS_ALLOWED);
		   }
	   }
   }

   setFieldValid(ifds::EmployeeClass, idDataGroup, false);
   validateRisk(idDataGroup);
   validationForEmailPhone(idDataGroup);

   validateRDSPEntity (idDataGroup);
   validateTaxJurisForRDSP (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::doValidateField ( const BFFieldId& idField, 
                                   const DString& strValue, 
                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   WhereUsedList* pList =  NULL;

   if (idField == ifds::LastName && _entityType != I_("58"))
   {
      validateEntityType (idDataGroup);
      
      DString strEntityEffectiveDate;
      getField( ifds::EffectiveDate, strEntityEffectiveDate, idDataGroup, false );
      
      if ( !isNew() && !strEntityEffectiveDate.empty())
      {
         validateTFSAEntity(strEntityEffectiveDate,idDataGroup);
      }      
   }
   else if (idField == ifds::FirstName && _entityType == NOMINEE_OWNER)
   {
      validateEntityType (idDataGroup);
   }
   else if (idField == ifds::Salutation && _entityType == NOMINEE_OWNER)
   {
      validateEntityType (idDataGroup);
   }
   else if (idField == ifds::CompoundDate)
   {
      validateBirthAndDeathDate (idDataGroup);
   }
   else if (idField == ifds::BirthLastName)
   {
      DString dstrOption;
      getWorkSession ().getOption (ifds::BirthNameMand, dstrOption, idDataGroup, false);
      if (dstrOption.strip ().upperCase () == I_("Y") && strValue.empty ())
         ADDCONDITIONFROMFILE (CND::ERR_BIRTHNAME_REQUIRED);
   }
   else if (idField == ifds::BirthFirstName)
   {
   }
   else if (idField == ifds::DofBirth)
   {
      validateDateOfBirth (strValue, idDataGroup);
   }
   else if (idField == ifds::Gender)
   {
      validateGenderForRESP (strValue, idDataGroup);

      //PET 212427 FN 01 - cannot change annuitant gender if the account is elected, has a NMCR contract and is Single Life	  
      validateGenderForElectedSingleLifeNMCR (strValue, idDataGroup);

      validateGenderAgainstElectResetEvent (strValue, idDataGroup);
   }
   else if (idField == ifds::SIN)
   {
   }
   else if (idField == ifds::HomePhone || idField == ifds::BusinessPhone ||
            idField == ifds::HomeFax || idField == ifds::BusinessFax)
   {
      validateAreaOrPhoneNumber (strValue, idDataGroup);
   }
   else if (idField == ifds::HomePhoneArea || idField == ifds::BusinessPhoneArea ||
            idField == ifds::HomeFaxArea || idField == ifds::BusFaxArea)
   {
      validateAreaOrPhoneNumber (strValue, idDataGroup, true);
   } 
   else if (idField == ifds::BusinessExt)
   {
   }
   else if (idField == ifds::BusinessFax)
   {
      bool	bRequired = false;

      if (getWhereUsedList (pList,idDataGroup) <= WARNING && pList )
      {
         if (pList->isFundSponsor (idDataGroup))
            bRequired = true;

         setFieldRequired (ifds::BusinessFax, idDataGroup, bRequired);
         setFieldValid (ifds::BusinessFax, idDataGroup, !bRequired);
      }
   }
   else if (idField == ifds::Telex)
   {
   }
   else if (idField == ifds::Email)
   {
   }
   else if (idField == ifds::ContactName)
   {
      bool bRequired = false;

      if (getWhereUsedList (pList,idDataGroup) <= WARNING && pList )
      {
         if (pList->isFundSponsor (idDataGroup))
            bRequired = true;

         setFieldRequired (ifds::ContactName, idDataGroup, bRequired);
         setFieldValid (ifds::ContactName, idDataGroup, !bRequired);
      }
   }
   else if (idField == ifds::DofDeath)
   {
      if (isNew () && (!strValue.empty ()))
         ADDCONDITIONFROMFILE (CND::ERR_ADD_ENTITY_DEATH_DATE);

      DString str, str1;
      getField (ifds::DofBirth, str, idDataGroup, false);
      if (!str.empty () && !strValue.empty ())
      {
         if (DSTCommonFunctions::CompareDates (strValue, str) == DSTCommonFunctions::FIRST_EARLIER)
            ADDCONDITIONFROMFILE (CND::ERR_EARLY_DEATH_DATE);
      }

      getField (ifds::DofDeathNotice, str1, idDataGroup, false);
      if (!str1.empty () && !strValue.empty ())
      {
         if (DSTCommonFunctions::CompareDates (str1, strValue ) ==  DSTCommonFunctions::FIRST_EARLIER)
            ADDCONDITIONFROMFILE (CND::ERR_DEATH_NOTIF_BEFORE_DEATH_DATE);
      }

      if (!strValue.empty ())
      {
         DString currDate;
         getWorkSession ().getMgmtCoOptions ()->getField (ifds::CurrSysDate, currDate, BF::HOST, false);
		 if (_entityType == NOMINEE_OWNER) 
		 {
			ADDCONDITIONFROMFILE (CND::ERR_DEATHDATE_UPDATION_DISABLED);
		 }
         else if (DSTCommonFunctions::CompareDates (currDate, strValue) ==  DSTCommonFunctions::FIRST_EARLIER) 
		 {
            ADDCONDITIONFROMFILE (CND::ERR_FUTURE_DEATHDATE);
         }
      }
      
      //if(!isNew())
      //{
      //   validateDeceasedAnnuitantTFSA( strValue, idDataGroup);
      //}      
   }
   else if (idField == ifds::DofDeathNotice)
   {
      DString strCurDate;

      getWorkSession ().getMgmtCoOptions ()->getField (ifds::CurrSysDate, strCurDate, BF::HOST, false);

      if (!strValue.empty ())
      {
		 if (_entityType == NOMINEE_OWNER) 
		 {
			ADDCONDITIONFROMFILE (CND::ERR_DEATHDATE_NOTIFICATION_UPDATION_DISABLED);
		 }
         else if (DSTCommonFunctions::CompareDates (strCurDate, strValue) ==  DSTCommonFunctions::FIRST_EARLIER) 
		 {
            ADDCONDITIONFROMFILE (CND::ERR_FUTURE_DEATH_NOTIFY);
         }
      }
   }
   else if (idField == ifds::EffectiveDate)
   {
      if (strValue.empty ())
      {
         ADDCONDITIONFROMFILE (CND::ERR_EFFECTIVE_DATE_MUST_BE_ENTERED);
      }
   }
   else if (idField == ifds::LanguageCode)
   {
      //commented out to set other fields.
      //if (strValue.empty ())
      //   ADDCONDITIONFROMFILE (CND::ERR_LANGUAGE_MUST_BE_ENTERED);
   }
   else if (idField == ifds::Nationality) 
   {
      // Handle a blank nationality field
      validateNationality (strValue, idDataGroup);
   }
   else if (idField == ifds::OccupationCode)
   {
      validateOccupation (strValue, idDataGroup);
   }
   else if ( idField == ifds::TaxJurisDeff )
   {
      if( isAccountRelated( idDataGroup )  )
      {
         DString effectiveDate;
         getField(ifds::TaxJurisDeff,effectiveDate,idDataGroup,false);

         if( isNew() ) // new entity
         {
            MFAccountList* pAcctList = NULL;
            Shareholder* pShareholder= NULL;
            getWorkSession().getShareholder(idDataGroup,_shrNum,pShareholder );
            if( pShareholder )
            {
               pShareholder->getMFAccountList(pAcctList,idDataGroup );
               if( pAcctList )
               {
                  pAcctList->validateEffectivDateAgainstAllShereholder( effectiveDate,idDataGroup );
               }
            }
         }
         else
         {
            MFAccountList acctList( *this );
         
            if (acctList.init( _entityId, NULL_STRING, NULL_STRING, NULL_STRING)<= WARNING)
            {
              acctList.validateEffectivDateAgainstAllShereholder (effectiveDate,idDataGroup);
            }
         }
      }

      // validate taxjuris for taxtype 9 and M
      validateTaxJurisEffDateForRESP (strValue, idDataGroup);

      if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         if (_entityType == ACCOUNT_OWNER)
         {
            if (!isNew())
            {
               DString dstrOldTaxJurisDeff;
               getField(ifds::TaxJurisDeff, dstrOldTaxJurisDeff, BF::HOST, false);

               /* The default values for the tax jurisdeff is current business date
               if it is blank from database.
               The new record, deff will be set from shareholder.
               */
               if (dstrOldTaxJurisDeff.empty())
               {
                  getWorkSession ().getOption (ifds::CurrBusDate, dstrOldTaxJurisDeff, idDataGroup, false);
               }

               if (DSTCommonFunctions::CompareDates (strValue, dstrOldTaxJurisDeff) == DSTCommonFunctions::FIRST_EARLIER)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_DEFF_CANNOT_LESS_THAN_INIT_DEFF);				 
               }

            }

            // check with shareholder
            Shareholder* pShareholder= NULL;
            getWorkSession().getShareholder(idDataGroup,_shrNum,pShareholder );
            if( pShareholder )
            {
               DString dstrShrDeff, dstrShrDeffFmt;
               pShareholder->getField(ifds::EffectiveDate, dstrShrDeff, idDataGroup, false);
               pShareholder->getField(ifds::EffectiveDate, dstrShrDeffFmt, idDataGroup, true);
               if (DSTCommonFunctions::CompareDates (strValue, dstrShrDeff) == DSTCommonFunctions::FIRST_EARLIER)				
               {
                  DString dstrDate;
                  addIDITagValue( dstrDate, I_("DATE"), dstrShrDeffFmt );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER, dstrDate.c_str() );
               }
            }
         }

      }

   }
   else if ( idField == ifds::EmployeeClass )
   {
      validateEmployeeClass (strValue, idDataGroup);
   }
   else if( idField == ifds::TaxJuris)
   {
      validateTaxJuris (strValue, idDataGroup);	
   }
   else if ( idField == ifds::CountryOfExposure )
   {
      DString strRiskLevel, strCountryOfExposure(strValue);
      getField( ifds::RiskLevel, strRiskLevel, idDataGroup, false );
      strRiskLevel.strip().upperCase();
      strCountryOfExposure.strip().upperCase();

      if (POLITICALLY_EXPOSED_PERSON == strRiskLevel && 
         ( strCountryOfExposure.empty() || strCountryOfExposure == UNASSIGNED_COUNTRY)) {
         CND::CIFast_IFast_ifastcbo_warn_country_of_exposure_is_required warnCond;
         CND::CIFast_IFast_ifastcbo_err_country_of_exposure_is_required errCond;

         MFCanBFCbo::getErrMsg (IFASTERR::COUNTRY_OF_EXPOSURE_IS_REQUIRED,
                                errCond,
                                warnCond,
                                idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   SEVERITY sevRtn = NO_CONDITION;  

   if (idField == ifds::OccupationCode)
   {
      DString dstrOccupationCode;
      getField (idField, dstrOccupationCode, idDataGroup, false);
      if (dstrOccupationCode == I_("08"))   // Other
      {
         setFieldRequired (ifds::OtherOccupation, idDataGroup, true);
         setValidFlag (ifds::OtherOccupation, idDataGroup, false);
      }
      else
      {
         setFieldRequired (ifds::OtherOccupation, idDataGroup, false);
         setFieldNoValidate (ifds::OtherOccupation, NULL_STRING, idDataGroup, false, true, true); // Formatted, Valid, Side Effect
         setValidFlag (ifds::OtherOccupation, idDataGroup, true);
      }
   }
   else if (idField == ifds::EmployeeClass)
   {
      // Get and store maximum number of characters from category field
      DString dstrEmployeeClass, dstrCategory;
      getField (idField, dstrEmployeeClass, idDataGroup, false);
      TranslationTable* pTranslationTable = NULL;
      getMgmtCo ().getTranslationTable (GROUPCODE_EMPLOYEE_CLASS, pTranslationTable);
      if (pTranslationTable)
      {
         pTranslationTable->getCategory (dstrEmployeeClass, dstrCategory);
         // Set value into local field
         if (!dstrCategory.empty ())
         {
            setFieldNoValidate (ifds::NAME_LENGTH, dstrCategory, idDataGroup, false, true, true);  // Formatted, Valid, Side Effect
            setFieldUpdated (ifds::NAME_LENGTH, idDataGroup, false);
         }
      }

      // Clear fields and truncate Last name if appropriate
      if (dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE) // Corporate
      {
         setFieldNoValidate (ifds::FirstName, NULL_STRING, idDataGroup, false, true, true);
         setFieldNoValidate (ifds::Salutation, NULL_STRING, idDataGroup, false, true, true);
      }
      else
      {
         // Truncate Last Name
         if (dstrCategory.asInteger ())
         {
            DString dstrLastName, dstrTruncatedLastName;
            getField (ifds::LastName, dstrLastName, idDataGroup, false);
            dstrTruncatedLastName = dstrLastName.substr (0, dstrCategory.asInteger ());
            setFieldNoValidate (ifds::LastName, dstrTruncatedLastName, idDataGroup, false, true, true);
         }
      }

      //Make each xref to validate EmployeeClassForFATCA again in order to reflect this field change.
      AccountEntityXref *pAccountEntityXref = NULL;
      if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
      {
          BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);
         DString searchKey, dstrEntityId;
         getField(ifds::EntityId, dstrEntityId, idDataGroup, false);

         AccountEntityXref::buildPartialKeyForEntityId(searchKey, dstrEntityId);

         iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

         while (!iterAccountEntityXrefOut.end())
         {
             AccountEntityXrefObject *pXrefObject = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

             pXrefObject->setFieldValid(ifds::EmployeeClassForFATCA, idDataGroup, false);

             ++iterAccountEntityXrefOut;
         }
      }
   }    

   else if (idField == ifds::TaxJuris)
   {
      /*
      CHG0033572
      Whenever the TaxJurisdiction is changed and the effective date is empty that means
      the taxjurisdiction is changed from blank. The effective date should be default.
      This also trig the EntityTaxHist to be created because the TaxJurisDeff is mandatory for history.
      */
      DString dstrCurrBusDate,
         taxJurisDeff;

      setFieldValid(ifds::TaxJurisDeff, idDataGroup, false);
      getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup);
      getField (ifds::TaxJurisDeff, taxJurisDeff, idDataGroup);
      taxJurisDeff.strip ();
      if (taxJurisDeff.empty())
      {
         setFieldNoValidate (ifds::TaxJurisDeff, dstrCurrBusDate, idDataGroup, true, false, true);
      }
   }
   else if (idField == ifds::CurrentSelectedEntityType || idField == ifds::CurrentEntRegAcctNum)
   {
      setUpdatedFlag(idField,idDataGroup,false);
   }
   else if (idField == ifds::RiskLevel)
   {
      DString strRiskLevel;
      getField( ifds::RiskLevel, strRiskLevel, idDataGroup, false );
      strRiskLevel.strip().upperCase();

      if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
         setFieldNoValidate(ifds::CountryOfExposure,NULL_STRING,idDataGroup,false,true,true);
         setFieldValid( ifds::CountryOfExposure, idDataGroup, true);
      }
      else{
         setFieldValid( ifds::CountryOfExposure, idDataGroup, false);
      }
   }
   if(idField != ifds::CurrentSelectedEntityType)
		verifyStatusRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Entity::getEntityId (DString& entityId) const
{
   entityId = _entityId;
}

//********************************************************************************
BFAbstractCBO * Entity::getTopLevelAncestor () 
{
   return (this);
}

//********************************************************************************
SEVERITY Entity::validateBirthAndDeathDate (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBirthAndDeathDate"));
   DString strBirth,strDeath;
   getField (ifds::DofDeath, strDeath, idDataGroup, false);
   strDeath.strip ();
   getField (ifds::DofBirth, strBirth, idDataGroup, false);
   strBirth.strip ();
   if (strBirth != NULL_STRING)
   {
      if (DSTCommonFunctions::CompareDates (strDeath, strBirth) ==  DSTCommonFunctions::FIRST_EARLIER)
          ADDCONDITIONFROMFILE (CND::ERR_EARLY_DEATH_DATE);
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::doesNEQExists (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doesNEQExists"));

	EntityIdsList *pEntityIdsList = NULL;
	bool	  bFound = false;

	if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
	{
		BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		
		while (!iter.end())
		{
			DString idType; 
      
			iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
			
			if (idType.stripAll() == EXTERNAL_PRODUCT_PROVIDER ||
				idType.stripAll() == CLIENT) 
			{
				DString idValue;

				iter.getObject()->getField (ifds::IdValue, idValue, idDataGroup, false);
			
				if (!idValue.empty ())
					bFound = true;

				break;
			}

			++iter;
		}
	}

	if (!bFound)
	{
		getErrMsg (IFASTERR::MISSING_NEQ, 
                   CND::ERR_MISSING_NEQ, 
                   CND::WARN_MISSING_NEQ, 
                   idDataGroup);
	}
	
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::validateMandatoryId (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMandatoryId"));
   	
	EntityIdsList *pEntityIdsList = NULL;
	CND::CIFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification warnCond;
	CND::CIFast_IFast_ifastcbo_err_mandatory_field errCond;

	if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
	{
		BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		bool	  bFound = false;
		
		while (!iter.end())
		{
			DString idType; 
      
			iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
			if (idType.stripAll() == I_("12")) //code for Additional Account Number
			{
				DString idValue;

				bFound = true;
				iter.getObject()->getField (ifds::IdValue, idValue, idDataGroup, false);
				if (idValue.empty ())
					MFCanBFCbo::getErrMsg (IFASTERR::ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION,
                                errCond,
                                warnCond,
                                idDataGroup);
				break;
			}
			++iter;
		}
		
		if (!bFound)
			MFCanBFCbo::getErrMsg (IFASTERR::ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION,
                                errCond,
                                warnCond,
                                idDataGroup);
	}

	return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
void Entity::setFlagsUpdated (const BFDataGroupId& idDataGroup)
{
   // this function is called from the EntityProcess when an entity field is updated and 
   // we need to set the correspondent AccountEntityXref object as updated
   if (isNew ())
   {
      setFieldUpdated (ifds::LanguageCode, idDataGroup, true);
      if (_pErrMsgRulesList == NULL)
      {
         SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList (_pErrMsgRulesList);
      }
      if (_pErrMsgRulesList)
      {
         DString strErrValue;

         _pErrMsgRulesList->getEWIValue (IFASTERR::NATIONALITY_IS_NOT_POPULATED, idDataGroup, strErrValue);
         if (strErrValue == I_("E") || strErrValue == I_("W"))
         {
            setFieldUpdated (ifds::Nationality, idDataGroup, true);
         }
         _pErrMsgRulesList->getEWIValue (I_("385"), idDataGroup, strErrValue);
         if (strErrValue == I_("E") || strErrValue == I_("W"))
         {
            setFieldUpdated (ifds::DofBirth, idDataGroup, true);
         }
         _pErrMsgRulesList->getEWIValue (I_("386"), idDataGroup, strErrValue);
         if (strErrValue == I_("E") || strErrValue == I_("W"))
         {
            setFieldUpdated (ifds::OccupationCode, idDataGroup, true);
         }
      }   
   }
   else
   {
		DString language;
		getField (ifds::LanguageCode, language, BF::HOST,false );

		if (language.empty ())
		      setFieldUpdated (ifds::LanguageCode, idDataGroup, true);
   }
}

//******************************************************************************
int Entity::getEntityAge (const int & basedOn, const BFDataGroupId& idDataGroup)

{
	// basedOn = 0 user current business day
	// basedOn = 1 use Dec 31 of the current year
	// basedOn = 2 use Jan 1 of the current year

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityAge"));
   DString dstrCurrentDate;
   DString dstrDate;
   DString dstrAsOfDate;
   DString dstrAsOfDec31, dstrAsOfJan1;
   DString dstrCurrentYear;

   dstrAsOfDec31 = I_("1231");
   dstrAsOfJan1 = I_("0101");

   getWorkSession ().getOption (ifds::CurrSysDate, dstrCurrentDate, idDataGroup, false);

   DString dstrBirthDate = NULL_STRING, dstrAge, dstrMonth;

   getField (ifds::DofBirth, dstrBirthDate, idDataGroup, false);

   int nCurrentYear = DSTCommonFunctions::getYearFromUnFormattedDate(dstrCurrentDate);

   convertIntToString (nCurrentYear, dstrCurrentYear);

   if (basedOn == 0)
   {
		dstrAsOfDate = dstrCurrentDate;
		dstrDate = dstrCurrentDate;
   }
   else if (basedOn == 1)
   {
		dstrAsOfDate = dstrAsOfDec31 +  dstrCurrentYear;
		dstrDate = dstrAsOfDate;

   }
   else if (basedOn == 2)
   {
	   	dstrAsOfDate = dstrAsOfJan1 +  dstrCurrentYear;
		dstrDate = dstrAsOfDate;
   }

   DSTCommonFunctions::BuildAge (dstrBirthDate, dstrDate, dstrAge, dstrMonth);

   int age = convertToULong (dstrAge);

   if (!dstrBirthDate.empty() && ((basedOn == 0 || basedOn == 2) && dstrMonth == I_("0")))
   {
	    int nBirthDay = DSTCommonFunctions::getDayFromUnFormattedDate(dstrBirthDate);
		int nBirthMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(dstrBirthDate);
		
		DString birthday = NULL_STRING;

		if (nBirthMonth < 10)
			birthday = I_("0");

		birthday = birthday.appendInt (nBirthMonth);

		if (nBirthDay < 10)
			birthday += I_("0"); 

		birthday = birthday.appendInt (nBirthDay);
		birthday = birthday.appendInt (nCurrentYear);
	  
	
		if (DSTCommonFunctions::CompareDates (dstrAsOfDate, birthday) ==  DSTCommonFunctions::FIRST_EARLIER)
		{
			age = age - 1; //did not have birthday yet.
		}
   }

   return age;
}

//******************************************************************************
bool Entity::getEntityAge (DString& strYears, DString& strMths, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityAge"));

   strYears = NULL_STRING;
   strMths = NULL_STRING;

   DString dstrCurrentDate;
   getWorkSession ().getOption (ifds::CurrSysDate, dstrCurrentDate, idDataGroup, false);

   DString date1, date2, date_mo, date_yr, str, strDOB;

   getField (ifds::DofBirth, str, idDataGroup, false);
   getField (ifds::DofBirth, strDOB, idDataGroup, true);
   strDOB.strip ();
   str.strip ();

   date1.assign (str);
   date2.assign (dstrCurrentDate);

   if (!DSTCommonFunctions::BuildAge (date1, date2, date_yr, date_mo))//if valid date
   {
      strYears = date_yr;
      strMths = date_mo;
      return (true);
   }
   return (false);
}

//******************************************************************************
void Entity::doPopulateField (const BFFieldId& idField, DString & strValue, bool formattedReturn)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doPopulateField"));
   strValue = NULL_STRING;
   BFData* pResponse = NULL;
   getResponseData (pResponse);
   if (idField != ifds::EntityId && pResponse->exists (idField))
   {
      if (!_entityId.strip ().empty ())
         if (init (_entityId) <= WARNING)
            /*BFBase::*/getField (idField, strValue, BF::HOST, formattedReturn);
   }
}

//********************************************************************************
void Entity::getResponseData (BFData*& pResponse)
{
   if (!_pResponseData)
      _pResponseData = new BFData (ifds::DSTC0051_VW);
   pResponse = _pResponseData;
}


//******************************************************************************
SEVERITY Entity::validateNationality (const DString& dstrNationality, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateNationality"));

   long errEntityID  (CND::ERR_ENTITY_NATIONALITY_BLANK);
   long warnEntityID (CND::WARN_ENTITY_NATIONALITY_BLANK);

   // Default condition
   SEVERITY sevRtn = NO_CONDITION;

   if (dstrNationality.empty () || dstrNationality == I_(" "))
   {         
      // Determine whether a blank nationality is a warning or an error
      sevRtn = getErrMsg (IFASTERR::NATIONALITY_IS_NOT_POPULATED, errEntityID, warnEntityID, idDataGroup);
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::validateDateOfBirth (const DString& dstrDateOfBirth, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDateOfBirth"));

   // Default condition
   SEVERITY sevRtn = NO_CONDITION;

   if (dstrDateOfBirth.empty ())
   {
      sevRtn = getErrMsg (I_("385"), CND::ERR_DATE_OF_BIRTH_REQUIRED, CND::WARN_DATE_OF_BIRTH_EMPTY, idDataGroup);
   }
   else
   {
      DString dstrCurrDate;
      getWorkSession ().getMgmtCoOptions ()->getField (ifds::CurrSysDate, dstrCurrDate, BF::HOST, false);
      if (DSTCommonFunctions::CompareDates (dstrCurrDate, dstrDateOfBirth) ==  DSTCommonFunctions::FIRST_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_FUTURE_BIRTHDATE);
      }
   }

   if (!_entityType.empty() && _entityType == RESP_BENEFICIARY)
   {
      DString dstrAccountNum;

      getAccountNum (dstrAccountNum, idDataGroup);
      MFAccount *pMFAccount (NULL);

      if (!dstrAccountNum.empty() && 
           getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
           pMFAccount)
      {
         if (pMFAccount->isCommitmentApplicable (idDataGroup))
         {
            int age = getEntityAge (0, idDataGroup);
            if(age >= 15)
            {
               DString dstrOrigAccountNum;
               AccountCommitment *pAccountCommitment = NULL;
               bool isNewAccount = pMFAccount->isNew();
               if( !isNewAccount && pMFAccount->getAccountCommitment( pAccountCommitment, idDataGroup, !isNewAccount) && // we do not want to force creation of Commitment for new accounts
                  pAccountCommitment )
               {
                  pAccountCommitment->getField (ifds::OrigAccountNum, dstrOrigAccountNum, idDataGroup, false); // OrigAccountNum=1810006150
                  dstrOrigAccountNum.strip().upperCase();
               } 

               if (dstrOrigAccountNum.empty() || dstrOrigAccountNum == I_("0")) 
               {
                  ADDCONDITIONFROMFILE (CND::ERR_BENE_OVER_AGE_OF_15);
               }
            }
         }
      }
   }

   if( isFieldChanged(ifds::DofBirth, idDataGroup))
   {
	   AccountEntityXref *pAccountEntityXref(NULL);
	   if(getWorkSession().getAccountEntityXref(idDataGroup, pAccountEntityXref) <= WARNING)
	   {
		   BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref,
												idDataGroup,
												true,
												BFObjIter::ITERTYPE::NON_DELETED);
		   DString strEntityId,
			       strEntityType,
				   searchKey;
		   getField(ifds::EntityId, strEntityId, idDataGroup, false);

		   BFCBO *pCBO = NULL;
		   AccountEntityXref::buildPartialKeyForEntityId(searchKey,strEntityId);
		   iterAccountEntityXrefOut.begin(OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

		   while (!iterAccountEntityXrefOut.end())
		   {
			   DString key = iterAccountEntityXrefOut.getStringKey();
			   AccountEntityXref::getValueForTag(key, I_("EntityType"), strEntityType);

			   if(strEntityType == ANNUITANT || strEntityType == SUCCESSOR_ANNUITANT)
			   {
				   getErrMsg (IFASTERR::ANNUITANT_DOFBIRTH_IS_CHANGING,
							  CND::ERR_ANNUITANT_DOFBIRTH_IS_CHANGING,
							  CND::WARN_ANNUITANT_DOFBIRTH_IS_CHANGING,
							  idDataGroup);
					   break;
				   
			   }
			   ++iterAccountEntityXrefOut;
		   }
	   }

   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::validateOccupation (const DString& dstrOccupationCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateOccupation"));

   // Default condition
   SEVERITY sevRtn = NO_CONDITION;

   if (dstrOccupationCode.empty ())
   {         
      sevRtn = getErrMsg (I_("386"), CND::ERR_OCCUPATION_REQUIRED, CND::WARN_OCCUPATION_EMPTY, idDataGroup);
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::getErrMsg (DString dstrErrNum,       
                            long    lErrConditionId, 
                            long    lWarnConditionId, 
                            const BFDataGroupId& idDataGroup, 
                            DString idiStr)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getErrMsg"));

   if (_pErrMsgRulesList == NULL)
   {
      SEVERITY sevRtn = getMgmtCo ().getErrMsgRulesList (_pErrMsgRulesList);
   }

   if (_pErrMsgRulesList)
   {
      _pErrMsgRulesList->getEWI (dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr);
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
void Entity::initializeSubstitutionList (const BFFieldId& idField, 
                                         const DString &dstrGroupCode, 
                                         const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrSubstitutionList;

   getMgmtCo ().getTranslationTable (dstrGroupCode, pTranslationTable);
   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList (dstrSubstitutionList);
      setFieldAllSubstituteValues (idField, idDataGroup, dstrSubstitutionList);
   }
}

//******************************************************************************
SEVERITY Entity::setSINToEntity (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setSINToEntity"));

   EntityIdsList *pEntityIdsList = NULL;

   if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
      pEntityIdsList)
   {
      //if any of the ids is SIN assign the value to the SIN field of the entity
      BFObjIter iter (*pEntityIdsList, idDataGroup);

      while (!iter.end())
      {
         DString idType; 

         iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
         if (idType.stripAll() == I_("06")) //code for SIN
         {
            DString idValue;

            iter.getObject()->getField (ifds::IdValue, idValue, idDataGroup, false);
            setFieldNoValidate (ifds::SIN, idValue, idDataGroup, false, true, true);
            break;
         }
         ++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Entity::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   DString dstrEntityRiskLevel;
   getWorkSession ().getOption (ifds::EntityRiskLevel, dstrEntityRiskLevel, idDataGroup, false);
   
   WorkSessionEntityList*pList = dynamic_cast<WorkSessionEntityList* > ( getParent() ); 
   bool bFrBroker = false; 
   if( pList )
   {
       bFrBroker = pList->isFundBroker();
   }
   DString whereUse;
   if( bFrBroker )
   {
      whereUse = WHERE_USED_FUND_BROKER; // default to fundBroker
      setFieldNoValidate (ifds::RiskLevel, dstrEntityRiskLevel, idDataGroup);
   }
   else if(Entity::bUsedByEntityAlone )
   {
      whereUse = WHERE_USED_ENTITY_ALONE;   // default to paying agent
      setFieldNoValidate (ifds::RiskLevel, dstrEntityRiskLevel, idDataGroup);
   }
   else
   {
      whereUse = WHERE_USED_ACCOUNT;   // default to account 

       if (!getWorkSession().multipleRiskEnv())
           setFieldNoValidate (ifds::RiskLevel, dstrEntityRiskLevel, idDataGroup);
   }
   setFieldNoValidate (ifds::WhereUse, whereUse, idDataGroup);
   setFieldNoValidate (ifds::UpdShrTaxJuris, NO, idDataGroup);
   
   initEUSDRelatedFields (idDataGroup);
   setAllSubstituteValuesForTaxOption (idDataGroup);
   
   DString dstrCurrBusDate;
   
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup);  
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup );
   DString languageDefault;
   getWorkSession().getOption (ifds::LanguageDefault,languageDefault, idDataGroup, false );
   setFieldNoValidate(ifds::LanguageCode, languageDefault,idDataGroup,false,true,true,false);
   initVerifyStatus (idDataGroup, isNew());
   _bInit = false;
}

//****************************************************************************
SEVERITY Entity::getWhereUsedList (WhereUsedList*& pWhereUsedList, 
                                   const BFDataGroupId& idDataGroup, 
                                   bool inquireDatabase /*= true*/,
                                   bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getWhereUsedList"));

   pWhereUsedList = dynamic_cast< WhereUsedList* > (getObject (I_("WhereUsedList"), idDataGroup));
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pWhereUsedList && bCreate)
   {
      if (isNew ())
      {
         pWhereUsedList = new WhereUsedList (*this);
         pWhereUsedList->initNew (_entityId, idDataGroup);
      }
      else if (inquireDatabase)
      {
         pWhereUsedList = new WhereUsedList (*this);
         pWhereUsedList->init (_entityId);

         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pWhereUsedList && GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         setObject ( pWhereUsedList, 
                     I_("WhereUsedList"), 
                     OBJ_ACTIVITY_NONE, 
                     idWorkingDataGroup);
      }
      else
      {
         delete pWhereUsedList;
         pWhereUsedList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
void Entity::setAllSubstituteValuesForTaxOption (const BFDataGroupId &idDataGroup)
{
   DString dstrList = NULL_STRING;       
   DocumentTypeOverrideList* pDocList = NULL;
   if( getMgmtCo().getDocumentTypeOverrideList (I_("EO"), pDocList) <= WARNING && pDocList) 
   {
      if( isAccountRelated(idDataGroup) ) // for account related, look for category 1
      {
         pDocList->getDocumentTypeSubstituteByCategory(dstrList,0,I_("1") );
      }
      else if( isPayAgentRelated(idDataGroup) ) // for pay agent related, look for category great than or equal to 1
      {
         pDocList->getDocumentTypeSubstituteByCategory(dstrList,4,I_("1") );      
      }
   }
   // for rest, the substitution list is blank for EUSDTaxOption
   setFieldAllSubstituteValues( ifds::EUSDTaxOption, idDataGroup, dstrList );	
}

//*******************************************************************************
bool Entity::isAccountRelated( const BFDataGroupId& idDataGroup )
{
   //where use 01: fund broker; 02: account; 03: paying agent;

   DString whereUse;
   getField(ifds::WhereUse,whereUse,idDataGroup,false);
   whereUse.strip();
   bool bRet = whereUse.find(WHERE_USED_ACCOUNT) != DString::npos ;
   return bRet;
}

//*******************************************************************************
bool Entity::isDead( const BFDataGroupId& idDataGroup )
{
   DString deathDate, 
      deathNoitifDate;

   getField (ifds::DofDeath, deathDate, idDataGroup, false);
   getField (ifds::DofDeathNotice, deathNoitifDate, idDataGroup, false);

   return (!deathDate.empty () && deathDate != I_("12319999")) || 
          (!deathNoitifDate.empty () && deathNoitifDate != I_("12319999"));

}

//*******************************************************************************
DString Entity::getTheRegulatoryStandardComplyRule (const BFDataGroupId& idDataGroup)
{
   return !isDead (idDataGroup) ? I_("0") : I_("1");
}

//*******************************************************************************
bool Entity::isFundBrokerOnly( const BFDataGroupId& idDataGroup )
{
   //where use 01: fund broker; 02: account; 03: client; 04:fund

   DString whereUse;
   getField(ifds::WhereUse,whereUse,idDataGroup,false);
   whereUse.strip();

   bool bFundBroker = whereUse.find(WHERE_USED_FUND_BROKER)  != DString::npos;
   bool bAccount    = whereUse.find(WHERE_USED_ACCOUNT)      != DString::npos;
   bool bClient     = whereUse.find(WHERE_USED_ENTITY_ALONE) != DString::npos;
   bool bFund       = whereUse.find(WHERE_USED_FUND_BROKER)  != DString::npos;
   bool bRet = bFundBroker && !bAccount && !bClient && bFund;

   return bRet;
}

//******************************************************************************
bool Entity::isPayAgentRelated( const BFDataGroupId& idDataGroup )
{
   //where use 01: fund broker; 02: account; 03: client; 04:fund
   DString whereUse;
   getField (ifds::WhereUse, whereUse, idDataGroup, false);
   whereUse.strip();

   bool bFundBroker = whereUse.find(WHERE_USED_FUND_BROKER)    != DString::npos;
   bool bAccount    = whereUse.find(WHERE_USED_ACCOUNT)        != DString::npos;   
   bool bClient     = whereUse.find(WHERE_USED_ENTITY_ALONE)   != DString::npos;
   bool bFund       = whereUse.find(WHERE_USED_FUND)           != DString::npos;

   bool bRet = !bFundBroker && !bAccount && ( bClient || bFund ); 

   return bRet;
}

//*******************************************************************************
void Entity::setAllFieldsReadOnlyforAccountRelated( const BFDataGroupId& idDataGroup )
{
   bool bReadOnly = false;
   if (Entity::bUsedByEntityAlone)
   {
      bReadOnly = isAccountRelated (idDataGroup);
   }
   /*
	Registration Agent entity should be modifiable from All Entity screen and 
	non-modifiable from Entity Maintanence Screen. However in case of other entitites existing implementation is vice-versa.

	In 'ifds::WhereUse' field we are getting comma separated whereuse codes of entity-relationship in View 51 Resp. 
	If entity-reltionship is 14 (RA) then in All Entity screen set bReadOnly = false and in Entity Maintanence Screen
	set it true.
   */
   DString dstrWhereUse; 
   getField(ifds::WhereUse,dstrWhereUse,idDataGroup,false);
   if( DSTCommonFunctions::codeInList(WHERE_USED_REGISTRATION_AGENT, dstrWhereUse)) //entity is used as Registration Agent
   {
	   bReadOnly = !Entity::bUsedByEntityAlone; //readonly in entity and changable in Whereused
   }

   setFieldReadOnly( ifds::EntityId, idDataGroup, bReadOnly );          
   setFieldReadOnly( ifds::LastName, idDataGroup, bReadOnly );          
   setFieldReadOnly( ifds::FirstName, idDataGroup, bReadOnly );         
   setFieldReadOnly( ifds::Salutation, idDataGroup, bReadOnly );        
   setFieldReadOnly( ifds::BirthLastName, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::BirthFirstName, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::DofBirth, idDataGroup, bReadOnly );          
   setFieldReadOnly( ifds::BirthPlace, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::CountryOfBirth, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::RiskLevel, idDataGroup, bReadOnly );         
   setFieldReadOnly( ifds::Gender, idDataGroup, bReadOnly );            
   setFieldReadOnly( ifds::SIN, idDataGroup, bReadOnly );               
   setFieldReadOnly( ifds::Language, idDataGroup, bReadOnly );          
   setFieldReadOnly( ifds::LanguageCode, idDataGroup, bReadOnly );      
   setFieldReadOnly( ifds::Nationality, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::HomePhone, idDataGroup, bReadOnly );         
   setFieldReadOnly( ifds::BusinessPhone, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::BusinessExt, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::BusinessFax, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::Telex, idDataGroup, bReadOnly );             
   setFieldReadOnly( ifds::Email, idDataGroup, bReadOnly );             
   setFieldReadOnly( ifds::ContactName, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::DofDeath, idDataGroup, bReadOnly );          
   setFieldReadOnly( ifds::DofDeathNotice, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::EffectiveDate, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::HomeFax, idDataGroup, bReadOnly );           
   setFieldReadOnly( ifds::OccupationCode, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::OccupationDesc, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::ProcessDate, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::EntityIdentityVer, idDataGroup, bReadOnly ); 
   setFieldReadOnly( ifds::EntityIdentityRid, idDataGroup, bReadOnly ); 
   setFieldReadOnly( ifds::CompoundDate, idDataGroup, bReadOnly );      
   setFieldReadOnly( ifds::HomePhoneArea, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::BusinessPhoneArea, idDataGroup, bReadOnly ); 
   setFieldReadOnly( ifds::HomeFaxArea, idDataGroup, bReadOnly );       
   setFieldReadOnly( ifds::BusFaxArea, idDataGroup, bReadOnly );        

   setFieldReadOnly( ifds::EmployeeClass, idDataGroup, bReadOnly );     
   setFieldReadOnly( ifds::OtherOccupation, idDataGroup, bReadOnly );   
   setFieldReadOnly( ifds::SpouseEntityID, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::TaxJuris, idDataGroup, bReadOnly );          
   //setFieldReadOnly( ifds::EUSDTaxOption, idDataGroup, bReadOnly );   
   setFieldReadOnly( ifds::UpdShrTaxJuris, idDataGroup, bReadOnly );    
   setFieldReadOnly( ifds::TaxJurisDeff, idDataGroup, bReadOnly );      
   setFieldReadOnly( ifds::Email2, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::SecondPhoneNum, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::SecondPhoneNumExt, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::CountryOfExposure, idDataGroup, bReadOnly );

   EntityRiskList *pEntityRiskList = NULL;
   if (getEntityRiskList(pEntityRiskList, idDataGroup) <= WARNING && pEntityRiskList)
   {
       pEntityRiskList->setAllRiskReadOnly(bReadOnly, idDataGroup);
   }
   
   DString strFATCAApplicable;
   getWorkSession ().getOption (ifds::FATCAApplicable,strFATCAApplicable, idDataGroup, false); 
   strFATCAApplicable.strip().upperCase();
   //setFieldReadOnly( ifds::FATCAFFI, idDataGroup, bReadOnly || strFATCAApplicable == I_("N")); 
}

//*****************************************************************************
bool Entity::shouldUpdateShareholder (const  BFDataGroupId& idDataGroup)
{
   bool bUpdate = false;
   if(  isAccountRelated( idDataGroup ) )
   {
      if( isFieldChanged(ifds::TaxJuris,idDataGroup ) || isFieldChanged(ifds::TaxJurisDeff,idDataGroup ) )
      {
         bUpdate = true;
      }
   }
   return bUpdate;
}

//*******************************************************************************
bool Entity::isFieldChanged (const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   DString oldValue, newValue;
   getField( idField,oldValue, BF::HOST, false );
   getField( idField,newValue, idDataGroup, false );
   return ( newValue.strip() != oldValue.strip() );
}

//*******************************************************************************
SEVERITY Entity::initEUSDRelatedFields (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initEUSDRelatedFields"));
   DString eusdEnv;
   
   getWorkSession ().getOption (ifds::EUSDParticip, eusdEnv, idDataGroup, false);
   eusdEnv.strip().upperCase();   
   if (eusdEnv == YES && !isFundBrokerOnly (idDataGroup) &&
      _entityType != CLEARING_PLATFORM )  // for eusd environment
   {
        setFieldRequired (ifds::EUSDTaxOption, idDataGroup, true);
        setFieldReadOnly (ifds::EUSDTaxOption, idDataGroup, false);
        setFieldValid (ifds::EUSDTaxOption, idDataGroup, false);
        setFieldRequired (ifds::TaxJuris, idDataGroup, true);
        setFieldValid (ifds::TaxJuris, idDataGroup, false);
        if (!Entity::bUsedByEntityAlone && isNew ())
        {
            DString dstrDef; 
            getWorkSession ().getOption (ifds::DefEUSDOption, dstrDef, idDataGroup, false);
            setFieldNoValidate (ifds::EUSDTaxOption, dstrDef, idDataGroup, false);      
        }
   }
   else // non eusd environment 
   {
      setFieldRequired (ifds::EUSDTaxOption, idDataGroup, false);
      setFieldReadOnly( ifds::EUSDTaxOption, idDataGroup, true ); 
      setFieldRequired (ifds::TaxJuris, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************

SEVERITY Entity::getNetworkSenderCutOffTimesList( AcctCutOffTimesList*& pCutOffTimeList, 
                                                  const BFDataGroupId &idDataGroup, 
                                                  bool inquireDatabase /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCutOffTimeList" ) );

   pCutOffTimeList = dynamic_cast<AcctCutOffTimesList*>( BFCBO::getObject( I_( "AcctCutOffTimesList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pCutOffTimeList )
   {
      if( isNew() )
      {
         pCutOffTimeList = new AcctCutOffTimesList( *this );
         pCutOffTimeList->init();
      }
      else if (inquireDatabase)
      {
         pCutOffTimeList = new AcctCutOffTimesList( *this );

         DString dstrEntityId;
         DString dstrAccountNum = NULL_STRING;

         getField (ifds::EntityId, dstrEntityId, idDataGroup);

         pCutOffTimeList->init (dstrAccountNum, dstrEntityId);
         idWorkingDataGroup = BF::HOST;
      }
      if( pCutOffTimeList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject (pCutOffTimeList, I_( "AcctCutOffTimesList" ), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pCutOffTimeList;
            pCutOffTimeList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::getEntityRiskList(EntityRiskList*& pEntityRiskList, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool inquireDatabase)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntityRiskList" ) );

   pEntityRiskList = dynamic_cast<EntityRiskList*>(BFCBO::getObject(I_("EntityRiskList"), idDataGroup));
   BFDataGroupId idWorkingDataGroup = idDataGroup;

    DString dstrEntityId;
    getField(ifds::EntityId, dstrEntityId, idDataGroup);

   if (!pEntityRiskList)
   {
       pEntityRiskList = new EntityRiskList(*this);

      if (isNew())
      {
         pEntityRiskList->initNew(dstrEntityId, idDataGroup);
      }
      else if (inquireDatabase)
      {
         pEntityRiskList->init(dstrEntityId);
         idWorkingDataGroup = BF::HOST;
      }

      if (pEntityRiskList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject(pEntityRiskList, I_("EntityRiskList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pEntityRiskList;
            pEntityRiskList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
bool Entity::isNetworkSenderEntity (const BFDataGroupId& idDataGroup)
{
   bool bNetworkSender = false;

   WhereUsedList* pList = NULL;

   if( getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if( pList )
      {
         bNetworkSender = pList->isNetworkSender (idDataGroup);
      }
   }

   return bNetworkSender;
}

//*******************************************************************************
bool Entity::isNEQEntity (const BFDataGroupId& idDataGroup)
{
   bool bExternalProductProvider = false;

   WhereUsedList* pList = NULL;

   if( getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if( pList )
      {
         bExternalProductProvider = pList->isNEQEntity (idDataGroup);
      }
   }

   return bExternalProductProvider;
}

//*******************************************************************************
bool Entity::isFundSponsorEntity (const BFDataGroupId& idDataGroup)
{
   bool bFundSponsor = false;

   WhereUsedList* pList = NULL;

   if( getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if( pList )
      {
         bFundSponsor = pList->isFundSponsor (idDataGroup);
      }
   }

   return bFundSponsor;
}

//*******************************************************************************
bool Entity::checkForDuplicateBICCode (DString bicCodeValue, const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("chekcForDuplicateBICCode"));

	BFData	requestData (ifds::DSTC0003_REQ), responseData (ifds::DSTC0003_VW);
	DString mgmtCoIdOut;

    requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
    requestData.setElementValue( ifds::NextOrPrevious, NO );
    requestData.setElementValue( ifds::AllAccounts, NO );
    requestData.setElementValue( ifds::AllEntitys, YES );
    requestData.setElementValue (ifds::SortBy, SORTED_BY_LAST_NAME);
    requestData.setElementValue (ifds::SrchIdType, IDS::BIC_CODE);
    requestData.setElementValue (ifds::SrchIdValue, bicCodeValue);
     
	if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::SEARCH, requestData, responseData, 
		DSTCRequestor (getSecurity (), true)) <= WARNING)
	{
		int		cRepeats = responseData.getRepeatCount ();
		DString entityId;

		// get original Entity.
		getField (ifds::EntityId, entityId, idDataGroup, false);
		bool	isNetworkSender = isNetworkSenderEntity (idDataGroup);

      for (int i = 0; i < cRepeats; i++)
      {
         DString	searchEntityId;
         Entity	*srchEntity = NULL;
         bool    isSrchNetworkSender = false;
         const	BFData &data = responseData.getRepeat (i);

         searchEntityId = data.getElementValue (ifds::EntityId);

         // original entity is NS, cannot share bic with anybody
         if (isNetworkSender)
            return true;

         // check back-end entity
         Entity *pEntity = new Entity ((BFAbstractCBO&)(*this)); 
         pEntity->init (searchEntityId);

         WhereUsedList* pList = NULL;

         if (pEntity->getWhereUsedList (pList, idDataGroup, true, true) <= WARNING )
         {
            if( pList )
            {
               isSrchNetworkSender = pList->isNetworkSender (idDataGroup);
            }
         }

         delete pEntity;

         // original entity is not NS, but backend is
         if (isSrchNetworkSender)
            return true;
         //else both entities are not NS.
      }
	}

	return false;
}

//*******************************************************************************

SEVERITY Entity::validateBICCode (const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBICCode"));

	DString  dstrBICCode, dstrEntityId;
	EntityIdsList *entityIdsList = NULL;

	getEntityId (dstrEntityId); 
	getEntityIdsList (entityIdsList, idDataGroup, false);
	
	if (entityIdsList == NULL)
		return GETCURRENTHIGHESTSEVERITY ();
		
	entityIdsList->setListInvalid();
	BFObjIter iterIds (*entityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

	iterIds.begin();

	while (!iterIds.end())
	{	
		DString strIdType;
		iterIds.getObject()->getField (ifds::IdType, strIdType, idDataGroup, false);

		if (strIdType == IDS::BIC_CODE)
		{
			EntityIds* pEntityIds = dynamic_cast<EntityIds*>(iterIds.getObject());
			pEntityIds->getField (ifds::IdValue, dstrBICCode, idDataGroup, false);

			if(pEntityIds->validateBICCode(getWorkSession(), dstrBICCode, dstrEntityId, idDataGroup) <= WARNING)
				pEntityIds->checkForDuplicateBICCode(dstrBICCode, idDataGroup);
		}
		else
		{
			++iterIds;
			continue;
		}

		++iterIds;
	}
	return GETCURRENTHIGHESTSEVERITY ();
}

/*******************************************************************************/
SEVERITY Entity::validateDeathClaimDocStatus (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDeathClaimDocStatus"));

   DString dstrDeathClaimDocExist;
   getWorkSession ().getOption (ifds::DeathClaimDocExist, dstrDeathClaimDocExist, idDataGroup, false);

   if (dstrDeathClaimDocExist == Y && isDead (idDataGroup) && 
      !isNew () && _entityType == I_("01")) //account owner
   {
      DString entityId,
         accountNum;
   
      getField (ifds::EntityId, entityId, idDataGroup);
      AccountEntityXref *pAccountEntityXref (NULL);

      if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
      {
         BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);

         DString searchKey;

         AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
         iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
         while (!iterAccountEntityXrefOut.end())
         {
            DString key = iterAccountEntityXrefOut.getStringKey ();
            
            DString _entityId;
            
            AccountEntityXref::getValueForTag (key, I_("EntityId"), _entityId);
            if (_entityId == entityId)
            {
               AccountEntityXref::getValueForTag (key, I_("AccountNum"), accountNum);
               accountNum.stripLeading ('0');
               break;
            }
            ++iterAccountEntityXrefOut;
         }
         MFAccount *pMFAccount = NULL;
         if( !accountNum.empty() && 
             getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
             pMFAccount)
         {
            RegDocumentList *pRegDocumentList = NULL;
            
            if ( pMFAccount->getRegDocumentsList (pRegDocumentList, entityId, idDataGroup, true) <= WARNING && 
                  pRegDocumentList)
            {
               if (pRegDocumentList->isAnyStatusBlank (idDataGroup))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_DEATHCLAIM_DOC_BLANK);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

/*******************************************************************************/
SEVERITY Entity::validateAreaOrPhoneNumber (const DString &number, const BFDataGroupId& idDataGroup, bool isAreaCodeNumber) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFaxPhoneNumber"));
	
	DString	tmpNumber = number;
	const	int phoneNumLength = isAreaCodeNumber ? 3 : 7;
	int		length;

	if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
	{   
		tmpNumber.stripAll(I_('-'));
		tmpNumber.stripAll(I_(' '));
		length = tmpNumber.length ();

		if (length > 0 && length != phoneNumLength)
		{
			if (isAreaCodeNumber)
			{
				ADDCONDITIONFROMFILE (CND::WARN_INVALID_AREA_CODE);
			}
			else 
			{
				ADDCONDITIONFROMFILE (CND::WARN_INVALID_PHONE_FAX_NUMBER);
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

/*******************************************************************************/
SEVERITY Entity::validateAreaOrPhoneNumber (const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFaxPhoneNumber"));

   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      DString homeArea, homeFaxArea, businessArea, businessFaxArea;
      DString homePhone, homeFax, businessPhone, businessFax;

      getField (ifds::HomePhoneArea, homeArea, idDataGroup, false);
      getField (ifds::HomeFaxArea, homeFaxArea, idDataGroup, false);
      getField (ifds::BusinessPhoneArea, businessArea, idDataGroup, false);
      getField (ifds::BusFaxArea, businessFaxArea, idDataGroup, false);

      getField (ifds::HomePhone, homePhone, idDataGroup, false);
      getField (ifds::HomeFax, homeFax, idDataGroup, false);
      getField (ifds::BusinessPhone, businessPhone, idDataGroup, false);
      getField (ifds::BusinessFax, businessFax, idDataGroup, false);

      if (homeArea.empty ()      || homeFaxArea.empty ()     ||
          businessArea.empty ()  || businessFaxArea.empty () ||
          homePhone.empty ()     || homeFax.empty ()         || 
          businessPhone.empty () || businessFax.empty ())
      {
         // in#1281683 - Creating new account Warning,
         // Client doesn't want to see this warning
         //ADDCONDITIONFROMFILE (CND::WARN_EMPTY_AREA_CODE_PHONE_NUMBER);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
void Entity::setFundSponsorMandatoryFields (const BFDataGroupId& idDataGroup) 
{
   bool        bRequired = false;
   WhereUsedList  *pList = NULL;

   if( getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if (pList)
         bRequired = pList->isFundSponsor (idDataGroup);
   }

   setFieldRequired (ifds::ContactName, idDataGroup, bRequired);
   setFieldValid (ifds::ContactName, idDataGroup, !bRequired);
   setFieldRequired (ifds::BusinessFax, idDataGroup, bRequired);
   setFieldValid (ifds::BusinessFax, idDataGroup, !bRequired);
}

/*******************************************************************************/
SEVERITY Entity::validateEntityType (const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEntityType"));

   if (!isNew())
   {
      WhereUsedList* pList =  NULL;

      if( getWhereUsedList (pList,idDataGroup ) <= WARNING && pList )
      {
         BFObjIter iter( *pList, BF::HOST );

         int count = iter.getNumberOfItemsInList();

         if (count > 1)
         {
            if (_entityType == NOMINEE_OWNER)
            {
               ADDCONDITIONFROMFILE (CND::ERR_NOMINEE_ENTITY_INUSE);
            }
            else
            {
               ADDCONDITIONFROMFILE (CND::ERR_ENTITY_MAY_USED_BY_OTHER_PLACES );
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::getDemographicsList( Demographics*& pDemographics, 
                                      const BFDataGroupId& idDataGroup, 
                                      bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDemographicsList" ) );

   DString strWhereUsed = NULL_STRING;
   getField( ifds::WhereUse, strWhereUsed, idDataGroup);
   
   if (!DSTCommonFunctions::codeInList(WHERE_USED_ACCOUNT, strWhereUsed))
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   pDemographics = dynamic_cast<Demographics *>( getObject( DEMOGRAPHICS_LIST, idDataGroup ));

   if ( !pDemographics )
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;

      DString strAccountNum = I_( "0" );
      DString strEntityId;

      bool bNewShrhld =false;

      getField( ifds::EntityId, strEntityId, idDataGroup );
      strEntityId.strip();

      if ( isNew() )
      {
         // new empty list
         pDemographics = new Demographics( *this );
         pDemographics->initNew( strAccountNum, idWorkingDataGroup );
      }
      else if ( inquireDatabase )
      {
         pDemographics = new Demographics( *this );
         pDemographics->init( strAccountNum, strEntityId, idWorkingDataGroup );

         idWorkingDataGroup = BF::HOST;
      }

      if ( pDemographics )
      {
         if ( GETCURRENTHIGHESTSEVERITY() < WARNING )
         {
            setObject( pDemographics, DEMOGRAPHICS_LIST, OBJ_ACTIVITY_NONE, idWorkingDataGroup );
         }
         else
         {
            delete pDemographics;
            pDemographics = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::validateTaxJurisForRESP( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateTaxJurisForRESP" ) );

   if ( _entityType == RESP_BENEFICIARY )
   {
      Entity *pEntity (NULL);
      if ( getWorkSession().getEntity( idDataGroup, _entityId, pEntity) <= WARNING && 
           pEntity)
      {
         DString dstrTaxJuris, dstrOrgTaxJuris;

         pEntity->getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);
         if ( dstrTaxJuris == NULL_STRING ||
              dstrTaxJuris == UNASSIGNED_COUNTRY )
         {
            ADDCONDITIONFROMFILE (CND::ERR_TAX_JURIS_INVALID);
         }

		 if (getWorkSession().isSAGESClient())
		 { 
			 getFieldBeforeImage(ifds::TaxJuris, dstrOrgTaxJuris);
			 dstrOrgTaxJuris.stripAll();
			 dstrTaxJuris.stripAll();
			 if (isFieldChanged (ifds::TaxJuris, idDataGroup) && dstrOrgTaxJuris == I_("0003")) // Saskatchewan 
			 {				 
				 //ADDCONDITIONFROMFILE(CND::WARN_REVIEW_SAGES_APPLICATION_DUE_TO_TAX_JURISDICTION_CHANGES); // Review SAGES Application due to Tax Jurisdiction changes
			 }
		 }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************
SEVERITY Entity::validateTaxJurisEffDateForRESP( const DString& strValue,
                                                 const BFDataGroupId& idDataGroup )
{                                                         
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateTaxJurisEffDateForRESP" ) );

   // get accountnum
   DString dstrAccountNum;
   AccountEntityXref *pAccountEntityXref (NULL);
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
         BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);
         DString searchKey;
         AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
         iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
         while (!iterAccountEntityXrefOut.end())
         {
            DString key = iterAccountEntityXrefOut.getStringKey ();                                                         
            DString dstrEntityId;
            AccountEntityXref::getValueForTag (key, I_("EntityId"), dstrEntityId);
            dstrEntityId.stripLeading('0');
            // ensure same entityid
            if (dstrEntityId == _entityId)
            {
               AccountEntityXref::getValueForTag (key, I_("AccountNum"), dstrAccountNum);
               dstrAccountNum.stripLeading ('0');                        
               //break;
            }
            ++iterAccountEntityXrefOut;
         }         
   }
   
   MFAccount *pMFAccount = NULL;

   DString strTaxType,strTaxTypeFmt;
   if(  !dstrAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      pMFAccount->getField( ifds::TaxType, strTaxTypeFmt, idDataGroup, true );
      strTaxType.strip().upperCase();
   }

   if ( getWorkSession ().isRES2Client() && !strTaxType.empty() && 
      ( strTaxType == INDIVIDUAL_RESP_TAX_TYPE || strTaxType == FAMILY_RESP_TAX_TYPE ) &&
	    _entityType == RESP_BENEFICIARY )
   {
      // P0195459 Withholding Tax, Tax Jurisdiction - apply to check taxjurisdeff only RESP Beneficiary
      DString dstrCurrBusDate;
      getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);  

      if (DSTCommonFunctions::CompareDates (dstrCurrBusDate, strValue) == DSTCommonFunctions::SECOND_EARLIER)
      {
         // Can't be back date
         ADDCONDITIONFROMFILE( CND::ERR_BACKDATED_ENTITY_TAX_JURISDICTION_NOT_ALLOWED_FOR_RESP);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::validateGenderForRESP ( const DString& strValue,
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateGenderForRESP" ) );

   DString dstrAccountNum,
      strEntityType,
      strEntityTypeFmt;
   AccountEntityXref *pAccountEntityXref (NULL);
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                          idDataGroup, 
                                          true, 
                                          BFObjIter::ITERTYPE::NON_DELETED);
      DString searchKey;
      AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      
      while (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();                                                         
         DString dstrEntityId;
         AccountEntityXref::getValueForTag (key, I_("EntityId"), dstrEntityId);
         dstrEntityId.stripLeading('0');
         // ensure same entityid
         if (dstrEntityId == _entityId)
         {
            AccountEntityXref::getValueForTag (key, I_("AccountNum"), dstrAccountNum);
            dstrAccountNum.stripLeading ('0'); 
            
            if (iterAccountEntityXrefOut.getObject ())
            {
               iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityType, strEntityType, idDataGroup, false);
               iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityType, strEntityTypeFmt, idDataGroup, true);
            }
            break;
         }
         ++iterAccountEntityXrefOut;
      }         
   }
   
   MFAccount *pMFAccount (NULL);

   DString strTaxType,
      strTaxTypeFmt;
   
   if(  !dstrAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      pMFAccount->getField( ifds::TaxType, strTaxTypeFmt, idDataGroup, true );
      strTaxType.strip().upperCase();
   }


   if ( getWorkSession ().isRES2Client() && !strTaxType.empty() && 
      ( strTaxType == INDIVIDUAL_RESP_TAX_TYPE || strTaxType == FAMILY_RESP_TAX_TYPE ) )
   {
      if (strEntityType == RESP_BENEFICIARY && strValue.empty() )
      {
         getErrMsg ( IFASTERR::BENEFICIARY_GENDER_MISSING,
                     CND::ERR_GENDER_REQUIRED_FOR_ENTITY_TYPE,
                     CND::WARN_GENDER_REQUIRED_FOR_ENTITY_TYPE,
                     idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::validateTFSAEntity ( const DString& strValue, 
                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateTFSAEntity" ) );
                          
   DString dstrAccountNum;
   AccountEntityXref *pAccountEntityXref (NULL);
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                           idDataGroup, 
                                           true, 
                                           BFObjIter::ITERTYPE::NON_DELETED);
      DString searchKey,
         strTaxType;
         
      AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      if (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();
         AccountEntityXref::getValueForTag (key, I_("AccountNum"), dstrAccountNum);
         dstrAccountNum.stripLeading ('0');
         
         MFAccount *pMFAccount (NULL);

         if( !dstrAccountNum.empty() && 
              getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
              pMFAccount)
         {
            pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
            strTaxType.strip().upperCase();
         }
      }
      
      if ( strTaxType.empty() || (strTaxType != TFSA_TAX_TYPE) )
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
         
      DString strEntityId,
         strEntityType;
      getField( ifds::EntityId, strEntityId, idDataGroup, false );
         
      BFCBO *pCBO = NULL;
      AccountEntityXref::buildPartialKeyForEntityId (searchKey, strEntityId);
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      if (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();
         AccountEntityXref::getValueForTag (key, I_("EntityType"), strEntityType);
         pCBO = dynamic_cast<BFCBO*>(iterAccountEntityXrefOut.getObject());
      }
      
      if ( !strEntityType.empty() &&
            ((strEntityType == ACCOUNT_OWNER) || 
            (strEntityType == DECEASED_ANNUITANT) ||
            (strEntityType == FORMER_SPOUSE)))
      {
         DString strLatestAmendYear,
            strEffectiveDate,
            strEffectiveYear;
            
         strEffectiveDate = strValue;
         pCBO->getField( ifds::TFSALastAmendTaxYear, strLatestAmendYear, idDataGroup, false );
         int year_pos = DSTCommonFunctions::getYearPosition();
         strEffectiveYear.assign(strEffectiveDate,year_pos,4);
         
         unsigned long iLatestAmendYear = convertToULong (strLatestAmendYear);
         unsigned long iEffectiveYear = convertToULong (strEffectiveYear);

         if( abs((long)(iLatestAmendYear-iEffectiveYear)) != 0 )
         {
            //ADDCONDITIONFROMFILE( CND::WARN_TFSA_UPDATE_EFFECTIVE_DATE_REQUIRED);
         }               
      }         
   }                          
            
   return(GETCURRENTHIGHESTSEVERITY());            
}

//******************************************************************************
SEVERITY Entity::validateDeceasedAnnuitantTFSA(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateDeceasedAnnuitantTFSA" ) );

   DString accountNum,
      strAcctTaxType;
                                
   AccountEntityXref *pAccountEntityXref (NULL);

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
         idDataGroup, 
         true, 
         BFObjIter::ITERTYPE::NON_DELETED);

      DString searchKey;

      AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      
      if (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();

         AccountEntityXref::getValueForTag (key, I_("AccountNum"), accountNum);
         accountNum.stripLeading ('0');
      }
      
      AccountEntityXref::buildPartialKeyForEntityType (searchKey, DECEASED_ANNUITANT );
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      
      if (iterAccountEntityXrefOut.end()) // this account has no 'DECEASED_ANNUITANT'
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }      
      
      MFAccount *pMFAccount = NULL;

      DString strTaxType;
      if( !accountNum.empty() && 
           getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
           pMFAccount)
      {
         pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
         strTaxType.strip().upperCase();
         if ( strTaxType == TFSA_TAX_TYPE )
         {
            DString strEntityID, entityID;
            DString key = iterAccountEntityXrefOut.getStringKey ();
            AccountEntityXref::getValueForTag (key, I_("EntityId"), strEntityID);
            getField( ifds::EntityId, entityID, idDataGroup, false );

            if ( strEntityID == entityID )
            {
               DString strDOD;
               getFieldBeforeImage(ifds::DofDeath, strDOD);
               if( (DSTCommonFunctions::CompareDates (strDOD, strValue ) ==  DSTCommonFunctions::SECOND_EARLIER) ||
                   (DSTCommonFunctions::CompareDates (strDOD, strValue ) ==  DSTCommonFunctions::FIRST_EARLIER) )
               {
                  ADDCONDITIONFROMFILE( CND::WARN_TFSA_DECEASED_ANNUITANT_DOD_UPDATED);
               }
            }
         }
      }
   }
      
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
/*
SEVERITY Entity::validateLoanTypeLoanNumber( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateLoanTypeLoanNumber" ) );
     
   DString dstrIDTypeCheck; 
   bool bDuplicate = false, bExist = false, bLoanNumberRequired = false;
   
   if (_entityType == ESCROW_ENTITY)
      dstrIDTypeCheck = IDS::LOAN_TYPE;   
   else if (_entityType == ACCOUNT_OWNER)
      dstrIDTypeCheck = IDS::LOAN_NUMBER;  // For Account Holder 
      
   EntityIdsList *pEntityIdsList = NULL;
   
   int numberInList = 0;
	if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
	{
		BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		
		while (!iter.end())
		{
			DString idType; 
      
			iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
			
			if (idType.stripAll() == dstrIDTypeCheck) 
			{
			   numberInList++;
			   bExist = true;
			   
			   if(numberInList > 1)
			      bDuplicate = true;
			}

			++iter;			
		}
	}                          
   
   if (dstrIDTypeCheck == IDS::LOAN_NUMBER)
   {
      // check the valid Escrow and LoanType
      // find the escrow entity
      AccountEntityXref *pAccountEntityXref (NULL);
      DString dstrEntityType;
      
      if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
      {
         BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);
         iterAccountEntityXrefOut.begin();
         while (!iterAccountEntityXrefOut.end())
         {             
            iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityType, dstrEntityType, idDataGroup, false);

            if(dstrEntityType == ESCROW_ENTITY)
            {
               Entity *pEntity;
               DString dstrEntityId;
               // Find the Loan Type
               iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityId, dstrEntityId, idDataGroup, false);
               getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
               // get escrow ids list
               pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);

               EntityIdsList* pEntityIdsList = NULL;

               pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);
               if (pEntityIdsList)
               {
                  BFObjIter bfIterIds (*pEntityIdsList, idDataGroup, false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);

                  bfIterIds.begin();
                  while (!bfIterIds.end())
                  {
                     DString dstrIdType;
                     // check Loan Type
                     bfIterIds.getObject() -> getField(ifds::IdType, dstrIdType, idDataGroup, false);
                     if(dstrIdType == IDS::LOAN_TYPE)
                        bLoanNumberRequired = true;
                     ++bfIterIds;
                  }
               }
            }
            ++iterAccountEntityXrefOut;   
         }
      }

   }
   
   if (!bExist)
   {
      if (dstrIDTypeCheck == IDS::LOAN_TYPE)
         getErrMsg ( IFASTERR::LOAN_TYPE_MANDATORY,
                     CND::ERR_LOAN_TYPE_MANDATORY,
                     CND::WARN_LOAN_TYPE_MANDATORY,
                     idDataGroup );            
                           
      else if (dstrIDTypeCheck == IDS::LOAN_NUMBER)
      {
         if(bLoanNumberRequired)
         {
            getErrMsg ( IFASTERR::LOAN_NUM_MANDATORY,
                        CND::ERR_LOAN_NUM_MANDATORY,
                        CND::WARN_LOAN_NUM_MANDATORY,
                        idDataGroup );                  
         }
      }
                  
   }                                              
   else
   {
      // has loan type or loan number
      if (dstrIDTypeCheck == IDS::LOAN_TYPE)
      {
         if(bDuplicate)
            getErrMsg ( IFASTERR::DUPLICATE_LOAN_TYPE,
                        CND::ERR_DUPLICATE_LOAN_TYPE,
                        CND::WARN_DUPLICATE_LOAN_TYPE,
                        idDataGroup );  
         else
         {
            // check loan number, in case of existing account that is added the new escrow.
            // The accountholder would not be validated, need to call the validation for accountholder
            DString strEntityTypeTemp;
            BFObjIter iterEntityList (*getParent(), idDataGroup, false, 
                                      BFObjIter::ITERTYPE::NON_DELETED);

            iterEntityList.begin();
            while (!iterEntityList.end())
            {
               Entity* pEntity = dynamic_cast<Entity*>(iterEntityList.getObject());
               strEntityTypeTemp = pEntity->getEntityType();

               if( strEntityTypeTemp == ACCOUNT_OWNER )
               {                  
                  pEntity->validateLoanTypeLoanNumber(idDataGroup);                    
               } 
               ++iterEntityList;
            }
         }
      }      
      if (dstrIDTypeCheck == IDS::LOAN_NUMBER)
      {
      
         if ( !bLoanNumberRequired )
         {
            getErrMsg ( IFASTERR::LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                        CND::ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                        CND::WARN_LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                        idDataGroup );    
         }  
         else if ( bLoanNumberRequired && bDuplicate )
         {
            getErrMsg ( IFASTERR::DUPLICATE_LOAN_NUM,
                        CND::ERR_DUPLICATE_LOAN_NUM,
                        CND::WARN_DUPLICATE_LOAN_NUM,
                        idDataGroup );    
         }
      
      }
   }  
   
   //P0186486_FN01 - IN2738162 Loan Number vs shareholder
   validateLoanTypeLoanNumberForNotAllowedEntity(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());                          
}   
*/

//******************************************************************************
SEVERITY Entity::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initVerifyStatus"));

   bool bReadOnly = false;
   DString modUser;

   getField (ifds::ModUser, modUser, idDataGroup, false);

   modUser.strip().upperCase();

   if (modUser.empty())
   {
      getField (ifds::Username, modUser, idDataGroup, false);
	  modUser.strip().upperCase();
   }

   DString dstrCurrentUser = dynamic_cast<const DSTCSecurity *> (getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()))->getUserId(); 
   dstrCurrentUser.strip().upperCase();

   bool bDifferentUser = false;
   if ( modUser != dstrCurrentUser )
   {
	   bDifferentUser = true;
   }

   getWorkSession ().isVerificationEnabled (idDataGroup, 
                                            ENTITYSEARCH_CATEGORY, 
                                            ENTITYSEARCH_LEVEL, 
                                            _bVerificationEnabled);

   // enviroment level:
   if (_bVerificationEnabled)
   {
	   // field level:
	   bReadOnly = !bDifferentUser;

	   if ( bNew )
	   {
		   setFieldNoValidate (ifds::VerifyStatDetails, UNVERIFIED, idDataGroup, false);
		   bReadOnly = true;
	   }
	   else
	   {
		   DString strVerifyStatDetails;
		   getField( ifds::VerifyStatDetails, strVerifyStatDetails, idDataGroup, false );
		   strVerifyStatDetails.strip().upperCase();

		   if (strVerifyStatDetails == VERIFIED )
		   {
			   setFieldNoValidate (ifds::VerifyStatDetails, VERIFIED, idDataGroup, false);
			   bReadOnly = true;
		   }
		   else
		   {
			   setFieldNoValidate (ifds::VerifyStatDetails, UNVERIFIED, idDataGroup, false);
		   }
	   }
   }
   else
   {
	   // enviroment does not support verficaiton
	   // Verify Status is read only
	   // Verify Status on new IDSEARCH is set to Verified.

	   setFieldNoValidate (ifds::VerifyStatDetails, VERIFIED, idDataGroup, false);
	   bReadOnly = true;
   }
   
   if( _bVerificationEnabled && idDataGroup == BF::HOST  ) // if data is verified is from backend, lock verify stat
   { 
	   bReadOnly = !bDifferentUser;
	   DString strVerifyStatDetails;
	   getField( ifds::VerifyStatDetails, strVerifyStatDetails, idDataGroup, false );
	   strVerifyStatDetails.strip().upperCase();

	   if (strVerifyStatDetails == VERIFIED )
	   {
		   bReadOnly = true;
	   }
   }

   setFieldReadOnly (ifds::VerifyStatDetails, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
SEVERITY Entity::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChanges"));


   if (!_bVerificationEnabled || _bInit )
      return GETCURRENTHIGHESTSEVERITY ();

   if (idFieldId != ifds::VerifyStatDetails )
   {
      // if data in CBO never changed before
      if ( !_bIsDirty )
      { 
		 _bIsDirty = isObjectDirty (idDataGroup);
         if (_bIsDirty)
         {
			 setFieldNoValidate (ifds::VerifyStatDetails, UNVERIFIED, idDataGroup, false);
			 setValidFlag ( ifds::VerifyStatDetails, idDataGroup, true );
         }
      }
      else
      {
         DString strVerifyStatDetails;
         getField(ifds::VerifyStatDetails,strVerifyStatDetails,idDataGroup,false);

		 if ( strVerifyStatDetails == VERIFIED )
		 {
			 setFieldNoValidate (ifds::VerifyStatDetails, UNVERIFIED, idDataGroup, false);
			 setValidFlag ( ifds::VerifyStatDetails, idDataGroup, true );
		 }
      }
	  if(_bIsDirty)
		setFieldReadOnly (ifds::VerifyStatDetails, idDataGroup, _bIsDirty);
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
bool Entity::hasIDSByType (const DString &strIDCheck, 
                           const BFDataGroupId& idDataGroup )
{
   /* Checking EntityIds in list by Type */
   EntityIdsList *pEntityIdsList;
	if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
	{
		BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		
		while (!iter.end())
		{
			DString idType; 
      
			iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
			
			if (idType.strip() == strIDCheck) 
			{
            return true;
         }
			++iter;			
		}
	}                          
   return false;
}

//******************************************************************************
SEVERITY Entity::validateTIN (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateTIN"));

   if( getWorkSession().isIWTClient( idDataGroup ) )
   {
      //IN2766093 - IWT TIN Warning Message
      DString dstrAccountNum;
      getAccountNum(dstrAccountNum, idDataGroup);

      MFAccount *pMFAccount = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
         pMFAccount )
      {
         // if account is non taxable.
         if ( pMFAccount->isIWTNonTaxable( idDataGroup ) )
         {
            // check if there is TIN for AcctOwner or not.
            AccountEntityXref *pAccountEntityXref (NULL);
            if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
            {
               BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, 
                                                   idDataGroup, 
                                                   true, 
                                                   BFObjIter::ITERTYPE::NON_DELETED);
               DString strEntityId,
                  strEntityType,
                  searchKey;

               getField (ifds::EntityId, strEntityId, idDataGroup, false );

               BFCBO *pCBO = NULL;
               AccountEntityXref::buildPartialKeyForEntityId (searchKey, strEntityId);
               iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

               while (!iterAccountEntityXrefOut.end())
               {
                  DString key = iterAccountEntityXrefOut.getStringKey ();
                  AccountEntityXref::getValueForTag (key, I_("EntityType"), strEntityType);

                  if (strEntityType == I_("01")) //owner
                  {
                     if (!hasIDSByType (I_("08"), idDataGroup))
                     {
                        //raise warning...
                        ADDCONDITIONFROMFILE (CND::WARN_TAX_ID_NUMBER_NOT_PROVIDED);
                        break;
                     }
                  }
                  ++iterAccountEntityXrefOut;
               }
            }

         }//add cover condition IN2766093
      }//add cover condition IN2766093
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Entity::validateLoanTypeLoanNumberForNotAllowedEntity(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLoanTypeLoanNumber" ) );

	if (!_entityType.empty() && 
		(_entityType != ACCOUNT_OWNER) &&  
		(_entityType != ESCROW_ENTITY)) 
	{

		EntityIdsList *pEntityIdsList = NULL;

		if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
		{
			BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			bool bFoundLoanNumber = false;
			bool bFoundLoanType = false;

			while (!iter.end())
			{
				DString idType; 

				iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);

				if (idType == IDS::LOAN_NUMBER)
				{
					bFoundLoanNumber = true;

				}
				else if (idType == IDS::LOAN_TYPE)
				{
					bFoundLoanType = true;
				}

				++iter;			
			}

			if (bFoundLoanNumber)
			{ //Loan Number only applicable for Accountholder Entity.

				getErrMsg (IFASTERR::LOAN_NUM_FOR_ACCTHOLDER, 
					CND::ERR_LOAN_NUM_FOR_ACCTHOLDER, 
					CND::WARN_LOAN_NUM_FOR_ACCTHOLDER, 
					idDataGroup);
			}

			if (bFoundLoanType)
			{  //Loan Type only applicable for Escrow Entity.
				getErrMsg (IFASTERR::LOAN_TYPE_FOR_ESCROW, 
					CND::ERR_LOAN_TYPE_FOR_ESCROW, 
					CND::WARN_LOAN_TYPE_FOR_ESCROW, 
					idDataGroup);
			}
			
		}                   
	}
}

//******************************************************************************
void Entity::getAccountNum(DString& accountNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountNum" ) );
   
   /*
	   This method does not work if the environment support 1 entity under multiple accounts. 
       Use Inter process parameter at the process level is the option.
   */
   AccountEntityXref *pAccountEntityXref (NULL);
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
         idDataGroup, 
         true, 
         BFObjIter::ITERTYPE::NON_DELETED);
      DString searchKey;
      AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
      while (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();                                                         
         DString dstrEntityId;
         AccountEntityXref::getValueForTag (key, I_("EntityId"), dstrEntityId);
         dstrEntityId.stripLeading('0');
         // ensure same entityid
         if (dstrEntityId == _entityId)
         {
            AccountEntityXref::getValueForTag (key, I_("AccountNum"), accountNum);
            accountNum.stripLeading ('0');                        
            break;
         }
         ++iterAccountEntityXrefOut;
      }         
   }
}

/******************************************************************************
 Input:DatGroupID
 OutPut:none
 Return:Void
 Functionality:Validates the CPF taxtypes mandatory ID's
/******************************************************************************/
void Entity::validateMandatedIDforCPFTaxTypes(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMandatedIDforCPFTaxTypes( )" ));
   // added for cpf
   //look for tax type in MFAccount
   DString taxType;
   DString dstrAccountNum;
   MFAccount *pMFAccount = NULL;        
   DString dstrEntityType;
   getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
   dstrEntityType.stripAll();

   getAccountNum(dstrAccountNum,idDataGroup);
   if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	   pMFAccount)
   {
	   DString idType;
	   EntityIdsList *pEntityIdsList = NULL;
	   pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);		
	   if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
		{
			BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			bool bFound = false;
			int num=0; 
			while (!iter.end())
			{
				DString idType; 
				num++;
				iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
				if( idType.stripAll() == I_("05") && (taxType == TAX_TYPES::OA|| taxType == TAX_TYPES::SA )) 
				{
					bFound = true;
					break;
				}
				else if ((idType.stripAll() == I_("02") || idType.stripAll() == I_("05") )&&
					     taxType == TAX_TYPES::SRS)
				{
			     bFound = true;	
				 break;
				}
				++iter; 
			 }
			if (! bFound && (taxType == TAX_TYPES::OA|| taxType == TAX_TYPES::SA) )
						ADDCONDITIONFROMFILE(CND::ERR_NATIONAL_ID_REQUIRED_FOR_TAX_TYPE);
		    if( ! bFound && taxType == TAX_TYPES::SRS)
					    ADDCONDITIONFROMFILE(CND::ERR_NATIONAL_ID_OR_PASSPORT_REQUIRED_FOR_TAX_TYPE);
		}
   }
}

//******************************************************************************
SEVERITY Entity::validateEmployeeClass (const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEmployeeClass" ));
   
   DString strEmployeeClass(strValue),
      strFATCAApplicable;

   DString accountNum,
      searchKey,
      strAccountType,
      strErrValue;
   MFAccount *pMFAccount = NULL;
   
   AccountEntityXref *pAccountEntityXref (NULL);

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {
      BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, 
                                          idDataGroup, 
                                          true, 
                                          BFObjIter::ITERTYPE::NON_DELETED);

      AccountEntityXref::buildPartialKeyForEntityType (searchKey, I_("01"));
      iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

      if (!iterAccountEntityXrefOut.end())
      {
         DString key = iterAccountEntityXrefOut.getStringKey ();

         AccountEntityXref::getValueForTag (key, I_("AccountNum"), accountNum);
         accountNum.stripLeading ('0');
      }

      if( accountNum.empty() || 
          getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) > WARNING || 
         !pMFAccount)
      {
         return GETCURRENTHIGHESTSEVERITY ();
      }
   }

   if(!_entityType.empty() && 
       _entityType == ESTATE_OF_DECEASED)
   {
      DString strEntityId,
         strEntityType;
      getField (ifds::EntityId, strEntityId, idDataGroup );
      strEmployeeClass.strip().upperCase();

      Entity *pEntity (NULL);
      if ( getWorkSession().getEntity( idDataGroup, strEntityId, pEntity) <= WARNING && 
           pEntity)
      {
         EntityIdsList *pEntityIdsList = NULL;
         if ( pEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
              pEntityIdsList)
         {
            DString strEntCat(strEmployeeClass);
            BFDataField::formatValue( ifds::EmployeeClass, strEntCat  );
            strEntCat.strip().lowerCase();

            if( strEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL )
            {
               DString idiStr, strIDType;
               bool bFormatErrorMessage = false;

               if( pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                  !pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }
               else if( !pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::TRUST_ACCOUNT_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage =true;
               }
               else if( pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  DString strIDType2(IDS::TRUST_ACCOUNT_NUMBER);
                  BFDataField::formatValue( ifds::IdType, strIDType2  );
                  strIDType2.strip().lowerCase();

                  strIDType += I_(",");
                  strIDType += strIDType2;

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }

               if( bFormatErrorMessage )
               {
                  getErrMsg (IFASTERR::ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }

               if( !pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ))
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::SIN;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();
                  
                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                  getErrMsg (IFASTERR::ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }
            }
            else if ( strEmployeeClass == ENTITY_CATEGORY::CORPORATE)
            {
               DString idiStr, strIDType;
               bool bFormatErrorMessage = false;

               if( pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) && 
                  !pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::SIN;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }
               else if( !pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::TRUST_ACCOUNT_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage =true;
               }
               else if( pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::SIN;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  DString strIDType2(IDS::TRUST_ACCOUNT_NUMBER);
                  BFDataField::formatValue( ifds::IdType, strIDType2  );
                  strIDType2.strip().lowerCase();

                  strIDType += I_(",");
                  strIDType += strIDType2;

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }

               if( bFormatErrorMessage )
               {
                  getErrMsg (IFASTERR::ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }

               if( !pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ))
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                  getErrMsg (IFASTERR::ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }
            }
            else if ( strEmployeeClass == ENTITY_CATEGORY::TRUST)
            {
               DString idiStr, strIDType;
               bool bFormatErrorMessage = false;

               if( pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                  !pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }
               else if( !pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::SIN;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage =true;
               }
               else if( pEntityIdsList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup ) && 
                        pEntityIdsList->isIdTypeExistWithValue( IDS::SIN, idDataGroup ) )
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();

                  DString strIDType2(IDS::SIN);
                  BFDataField::formatValue( ifds::IdType, strIDType2  );
                  strIDType2.strip().lowerCase();

                  strIDType += I_(",");
                  strIDType += strIDType2;

                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );
                  bFormatErrorMessage = true;
               }

               if( bFormatErrorMessage )
               {
                  getErrMsg (IFASTERR::ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }

               if( !pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ))
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::TRUST_ACCOUNT_NUMBER;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  strIDType.strip();
                  
                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                  getErrMsg (IFASTERR::ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                           idDataGroup,
                           idiStr);
               }
            }
            else if ( strEmployeeClass == ENTITY_CATEGORY::NOT_APPICABLE )
            {
               ADDCONDITIONFROMFILE(CND::ERR_ENTITY_CATEGORY_IS_REQUIRED);
            }
         }
      }
   }

   //NULL_STRING means using EntityType from selected xref in the gui list.
   validateEmployeeClassForFATCA(idDataGroup, NULL_STRING);

   // Registered product changes
   if(pMFAccount)
   {
      DString strTaxtype;
      pMFAccount->getField (ifds::TaxType, strTaxtype, idDataGroup, false);
      strTaxtype.strip().upperCase();
      
      if( strTaxtype == INDIVIDUAL_RESP_TAX_TYPE || strTaxtype == FAMILY_RESP_TAX_TYPE )
      {
         pMFAccount->getField( ifds::AcctType, strAccountType, idDataGroup, false );
         strAccountType.strip().upperCase();

         if(strEmployeeClass.empty() || strEmployeeClass == ENTITY_CATEGORY::NOT_APPICABLE)
         {
            if( strAccountType == ACCOUNT_TYPE::CORPORATE )
            {
               ADDCONDITIONFROMFILE(CND::ERR_ENTITY_CATEGORY_IS_REQUIRED);
            }
         }

		 //IN3198343
		 /* In Family RESP(taxtype = 'M'), corporate don't be allowed to be an accountholder*/
		 if( strTaxtype == FAMILY_RESP_TAX_TYPE && strEmployeeClass == ENTITY_CATEGORY::CORPORATE){

			 DString searchKey(I_("")), entityID;
			 AccountEntityXref *xref;

			 if (getWorkSession().getAccountEntityXref (idDataGroup, xref) <= WARNING)
			 {
				 BFObjIter iterAccountEntityXrefOut( *xref, 
					 idDataGroup, 
					 true, 
					 BFObjIter::ITERTYPE::NON_DELETED);

				 getField (ifds::EntityId, entityID, idDataGroup );

				 AccountEntityXref::buildPartialKeyForEntityId (searchKey, entityID);

				 while (!iterAccountEntityXrefOut.end()){
					 DString entityType;
					 iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityType, entityType, idDataGroup, false);

					 if (entityType == ACCOUNT_OWNER){
						 ADDCONDITIONFROMFILE (CND::ERR_ONLY_RESP_CAN_HAVE_CORPORATE_AS_ACCOUNTHOLDER);
					 }
 
					 ++iterAccountEntityXrefOut;
				 }
			 }
		 }
         
         DString strEntityId,
            strEntityType;
         getField (ifds::EntityId, strEntityId, idDataGroup );

         Entity *pEntity (NULL);
         EntityIdsList* pList(NULL);
         if ( getWorkSession().getEntity( idDataGroup, strEntityId, pEntity) <= WARNING && 
            pEntity)
         {
            pEntity->getEntityIdsList(pList, idDataGroup);
         }

         if(pList)
         {
            DString idiStr, strIDType, strEntCat;
            bool bHasBIN =  pList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup );

            if (strEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL && 
                strAccountType == ACCOUNT_TYPE::CORPORATE)
            {
               if(!bHasBIN)
               {
                  idiStr = NULL_STRING;
                  strIDType = IDS::BUSINESS_NUMBER;
                  strEntCat = ENTITY_CATEGORY::INDIVIDUAL;
                  BFDataField::formatValue( ifds::IdType, strIDType  );
                  BFDataField::formatValue( ifds::EmployeeClass, strEntCat  );
                  strIDType.strip();
                  
                  addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                  addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                  getErrMsg (IFASTERR::ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                             CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                             CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                             idDataGroup,
                             idiStr);
               }
            }
         }
      }
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************************************
SEVERITY Entity::getActOwnerNationalIdAndPassport(DString& dstrNationalID,
                                                  DString& dstrPassport,
                                                  DString& dstrCOINationalID,
                                                  DString& dstrCOIPassport,
                                                  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getActOwnerNationalIdAndPassport"));

	EntityIdsList *pEntityIdsList = NULL;
	if (getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
	{
		BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

		while (!iter.end())
		{
			DString idType,entityType,countryOfIssue; 

			iter.getObject()->getField (ifds::EntityType, entityType, idDataGroup, false);
			if( entityType == ACCOUNT_OWNER ) //i.e. Account Holder
			{
				iter.getObject()->getField (ifds::IdType, idType, idDataGroup, false);
				if( idType == NATIONAL_ID)
				{
					iter.getObject()->getField (ifds::IdValue, dstrNationalID, idDataGroup, false);
					iter.getObject()->getField (ifds::CountryOfIssue, dstrCOINationalID, idDataGroup, false);
				}
				else if( idType == PASSPORT)
				{
					iter.getObject()->getField (ifds::IdValue, dstrPassport, idDataGroup, false);
					iter.getObject()->getField (ifds::CountryOfIssue, dstrCOIPassport, idDataGroup, false);			
				}
			}
			++iter;			
		}			
	}	

	return GETCURRENTHIGHESTSEVERITY ();
}

//************************************************************************************************************
SEVERITY Entity::validateAcctRegAgent(DString& dstrAccountNum,
                                      DString& dstrTaxType,
                                      DString& dstrEntityId,
                                      DString& dstrNationalID,
                                      DString& dstrCOINationalID,
                                      DString& dstrPassport,
                                      DString& dstrCOIPassport,
									  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAcctRegAgent"));

	DString dstrWarnCode ;
	AcctEntityValidation acctEntityValidation(*this);
	SEVERITY sevRtn = acctEntityValidation.init(dstrAccountNum, 
												dstrTaxType, 
												dstrEntityId, 
												dstrNationalID, 
												dstrCOINationalID, 
												dstrPassport, 
												dstrCOIPassport);
	if( sevRtn <= WARNING )
	{
		acctEntityValidation.getField(ifds::WarnCode, dstrWarnCode, idDataGroup, false);
	}	
	if( dstrWarnCode == I_("99") )
	{
		getErrMsg (IFASTERR::DIFFERENT_REG_AGENT, 
                             CND::ERR_DIFFERENT_REG_AGENT, 
                             CND::WARN_DIFFERENT_REG_AGENT, 
                             idDataGroup,
							 NULL_STRING); 
	}
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::validateTaxJuris(const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTaxJuris"));

   if(!_entityType.empty() && 
       _entityType == ESTATE_OF_DECEASED)
   {
      DString strEntityId,
         strEntityType,
         strEmployeeClass;
      getField (ifds::EntityId, strEntityId, idDataGroup );
      getField (ifds::EmployeeClass, strEmployeeClass, idDataGroup );
      strEmployeeClass.strip().upperCase();

      Entity *pEntity (NULL);
      if ( getWorkSession().getEntity( idDataGroup, strEntityId, pEntity) <= WARNING && 
           pEntity)
      {
         EntityIdsList *pEntityIdsList = NULL;
         if ( pEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
              pEntityIdsList)
         {
            if( strEmployeeClass == ENTITY_CATEGORY::TRUST )
            {
               DString idiStr, strIDType;
               bool bFormatErrorMessage = false;

               if( pEntityIdsList->isIdTypeExistWithValue( IDS::TRUST_ACCOUNT_NUMBER, idDataGroup ) )
               {
                  DString strTaxJuris(strValue),strResidency1, strResidency2, strResidency3;
                  strTaxJuris.strip().upperCase();

                  getWorkSession().getOption( ifds::Residency1, strResidency1, idDataGroup, false );
                  getWorkSession().getOption( ifds::Residency2, strResidency2, idDataGroup, false );
                  getWorkSession().getOption( ifds::Residency3, strResidency3, idDataGroup, false );

                  if( ( DSTCommonFunctions::codeInList( strTaxJuris, strResidency1 ) ||
                        DSTCommonFunctions::codeInList( strTaxJuris, strResidency2 ) ||
                        DSTCommonFunctions::codeInList( strTaxJuris, strResidency3 ) ))
                  {
                     BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                     
                     while (!iter.end())
                     {
                        EntityIds* pEntityIds = dynamic_cast<EntityIds*>(iter.getObject());
                        
                        if(pEntityIds)
                        {
                           pEntityIds->getField (ifds::IdType, strIDType, idDataGroup, false);
                           strIDType.strip().upperCase();
                        
                           if( strIDType == IDS::TRUST_ACCOUNT_NUMBER && 
                               pEntityIds->isTrustNumberValid(idDataGroup) <= WARNING)
                           {
                              // find for duplicate trust number within the same entity ?
                           }
                        }
                        ++iter;
                     }
                  }
               }
            }
         }
      }
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::responseIDRemoved(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("responseIDRemoved"));

   setFieldValid (ifds::EmployeeClass, idDataGroup, false);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Entity::refreshMe (bool bRefresh)
{
	_bRefresh = bRefresh;
}

//******************************************************************************
bool Entity::needsRefresh ()
{
	return _bRefresh;
}

//******************************************************************************
SEVERITY Entity::validateRESPAcctHolder(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRESPAcctHolder"));

	DString dstrAccountNum, strTaxtype, strEmployeeClass;

	getAccountNum (dstrAccountNum, idDataGroup);
	MFAccount *pMFAccount;

	if (getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
		pMFAccount){
			pMFAccount->getField (ifds::TaxType, strTaxtype, idDataGroup, false);
			
			if (strTaxtype != INDIVIDUAL_RESP_TAX_TYPE){
				return GETCURRENTHIGHESTSEVERITY ();
			}

			DString searchKey(I_("")), entityID;
			AccountEntityXref *xref;

			if (getWorkSession().getAccountEntityXref (idDataGroup, xref) <= WARNING)
			{
				BFObjIter iterAccountEntityXrefOut( *xref, 
					idDataGroup, 
					true, 
					BFObjIter::ITERTYPE::NON_DELETED);

				getField (ifds::EntityId, entityID, idDataGroup );

				AccountEntityXref::buildPartialKeyForEntityId (searchKey, entityID);
				iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
				while (!iterAccountEntityXrefOut.end()){
					DString entityType;
					EntityIdsList *entityIdList;

					iterAccountEntityXrefOut.getObject()->getField (ifds::EntityType, entityType, idDataGroup, false);
					iterAccountEntityXrefOut.getObject()->getField(ifds::EmployeeClass, strEmployeeClass, idDataGroup, false);
					if (entityType == ACCOUNT_OWNER &&
						strEmployeeClass == ENTITY_CATEGORY::CORPORATE &&
						getEntityIdsList(entityIdList, idDataGroup) <= WARNING
						&& entityIdList){

							if (entityIdList->isIdTypeExist(IDS::BUSINESS_NUMBER, idDataGroup)){
								// if id is pcg then calls validation
								BFObjIter iterEntityIds (*entityIdList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
								while (!iterEntityIds.end()){
									DString idval, idtype;
									EntityIds* pEntityIds = dynamic_cast<EntityIds*>(iterEntityIds.getObject());

									pEntityIds->getField(ifds::IdType, idtype, idDataGroup, false);
									if (idtype == IDS::BUSINESS_NUMBER){
										pEntityIds->getField(ifds::IdValue, idval, idDataGroup, false);
										pEntityIds->validateIDTypeValueEntity(getWorkSession(), 
											entityType, 
											entityID, 
											strTaxtype,
											IDS::BUSINESS_NUMBER,
											idval,
											idDataGroup);
									}
									++iterEntityIds;
								}
							}
							else{
								ADDCONDITIONFROMFILE (CND::ERR_PCG_REQURIED_FOR_COPORATE_RESP_ACCT_HOLDER);
							}
						}

						++iterAccountEntityXrefOut;
				}
			}
		}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Entity::getGender ( DString &dstrGender, 				
							 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("getGender"));

	getField(ifds::Gender, dstrGender, idDataGroup);
	dstrGender.stripAll().upperCase();

	return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
void Entity::setEmployeeClassWithoutValidation(const DString &empClass, const BFDataGroupId &idDataGroup)
{
    setFieldNoValidate(ifds::EmployeeClass, empClass, idDataGroup, false, false);
}



//******************************************************************************
SEVERITY Entity::validateEmployeeClassForFATCA(const BFDataGroupId &idDataGroup, const DString &dstrEntityType)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEmployeeClassForFATCA"));

    DString entityType, dstrAccountNum, dstrEmployeeClass, dstrCurrentSelectedEntityType, dstrFATCAApplicable;
    MFAccount *pMFAccount = NULL;
    EntityIdsList* pEntityIdsList = NULL;

    getField(ifds::CurrentSelectedEntityType, dstrCurrentSelectedEntityType, idDataGroup);
    getWorkSession ().getOption (ifds::FATCAApplicable, dstrFATCAApplicable, idDataGroup, false);
    getAccountNum (dstrAccountNum, idDataGroup);
    getField(ifds::EmployeeClass, dstrEmployeeClass, idDataGroup);

    entityType = dstrEntityType.empty() ? dstrCurrentSelectedEntityType:dstrEntityType;

    if (!dstrAccountNum.empty() && 
        getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount &&
        dstrEmployeeClass != ENTITY_CATEGORY::INDIVIDUAL && 
        entityType == RELATED_PARTY)
    {
        getErrMsg(IFASTERR::RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL, 
                  CND::ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL, 
                  CND::WARN_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL,
                  idDataGroup);
    }

    if (!dstrAccountNum.empty() && dstrFATCAApplicable.stripAll().upperCase() == YES &&
        getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount &&
        getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && pEntityIdsList)
    {
        DString strAccountType;

         pMFAccount->getField( ifds::AcctType, strAccountType, idDataGroup, false );
         strAccountType.strip().upperCase();

         if(dstrEmployeeClass.empty() || dstrEmployeeClass == ENTITY_CATEGORY::NOT_APPICABLE)
         {
            // for FATCA only corporate account type(4), entity category required
            if( strAccountType == ACCOUNT_TYPE::CORPORATE )
            {
               if(!entityType.empty() && 
                   entityType == ACCOUNT_OWNER)
               {
                  ADDCONDITIONFROMFILE(CND::ERR_ENTITY_CATEGORY_IS_REQUIRED);
               }
            }
         }


         DString idiStr, strIDType, strEntCat;
         bool bHasEIN =  pEntityIdsList->isIdTypeExistWithValue(IDS::EMPLOYER_NUMBER, idDataGroup);
         bool bHasTIN =  pEntityIdsList->isIdTypeExistWithValue(IDS::TAX_ID_NUMBER, idDataGroup);

         if (dstrEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL && 
             DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ))
         {
             if(!bHasTIN)
             {
                 idiStr = NULL_STRING;
                 strIDType = IDS::TAX_ID_NUMBER;
                 strEntCat = ENTITY_CATEGORY::INDIVIDUAL;
                 BFDataField::formatValue( ifds::IdType, strIDType  );
                 BFDataField::formatValue( ifds::EmployeeClass, strEntCat  );
                 strIDType.strip();

                 addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                 addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                 getErrMsg (IFASTERR::ID_NUMBER_IS_REQUIRED_FOR_INDIVIDUAL, 
                     CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     idDataGroup,
                     idiStr);
             }
         }
         else if (dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE &&
             !DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ))
         {
             if(!bHasEIN && entityType == ACCOUNT_OWNER)
             {
                 idiStr = NULL_STRING;
                 strIDType = IDS::EMPLOYER_NUMBER;
                 strEntCat = ENTITY_CATEGORY::CORPORATE;
                 BFDataField::formatValue( ifds::IdType, strIDType  );
                 BFDataField::formatValue( ifds::EmployeeClass, strEntCat  );
                 strIDType.strip();

                 addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                 addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                 getErrMsg (IFASTERR::EMPLOYER_NUMBER_IS_REQUIRED_FOR_CORPORATE, 
                     CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     idDataGroup,
                     idiStr);
             }

             if(bHasTIN)
             {
                 idiStr = NULL_STRING;
                 strIDType = IDS::TAX_ID_NUMBER;
                 BFDataField::formatValue( ifds::IdType, strIDType  );
                 strIDType.strip();

                 addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );

                 getErrMsg (IFASTERR::ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY, 
                     CND::ERR_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY, 
                     CND::WARN_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY, 
                     idDataGroup,
                     idiStr);
             }
         }
         else if (DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ) &&
             dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE && entityType == ACCOUNT_OWNER)
         {
             // invalid
             DString strTaxtype;
             pMFAccount->getField (ifds::TaxType, strTaxtype, idDataGroup, false);
             strTaxtype.strip().upperCase();

             if( !DSTCommonFunctions::codeInList (strTaxtype, RESP_TAX_TYPES) )
             {
                 ADDCONDITIONFROMFILE (CND::WARN_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY);
             }
         }
         else if ( !DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ) &&
             dstrEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL)
         {
             if(!bHasTIN)
             {
                 idiStr = NULL_STRING;
                 strIDType = IDS::TAX_ID_NUMBER;
                 strEntCat = ENTITY_CATEGORY::INDIVIDUAL;
                 BFDataField::formatValue( ifds::IdType, strIDType  );
                 BFDataField::formatValue( ifds::EmployeeClass, strEntCat  );
                 strIDType.strip();

                 addIDITagValue( idiStr, I_("ID_TYPE"), strIDType );
                 addIDITagValue( idiStr, I_("ENT_CAT"), strEntCat );

                 getErrMsg (IFASTERR::ID_NUMBER_IS_REQUIRED_FOR_INDIVIDUAL, 
                     CND::ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     CND::WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY, 
                     idDataGroup,
                     idiStr);
             }
         }
    }


    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Entity::validateRisk(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
						   CLASSNAME, 
						   I_( "validateRisk" ) );

    DString dstrRiskLevel, dstrRiskCntry, dstrCurrBusDate;
    EntityRiskList *pEntityRiskList = NULL;

    getField(ifds::RiskLevel, dstrRiskLevel, idDataGroup);
    getField(ifds::CountryOfExposure, dstrRiskCntry, idDataGroup);
    getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

    if (getWorkSession().multipleRiskEnv() &&
        getEntityRiskList(pEntityRiskList, idDataGroup) <= WARNING && pEntityRiskList)
    {
        if (dstrRiskLevel.empty())
        {
            ADDCONDITIONFROMFILE(CND::WARN_HIGHEST_RISK_LVL_IS_REQUIRED);
        }
        else if (!dstrRiskLevel.empty() || !dstrRiskCntry.empty())
        {
            bool found = false;
            BFObjIter iter(*pEntityRiskList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end())
            {
                DString iterRiskLevel, iterRiskCntry;

                iter.getObject()->getField(ifds::RiskLevel, iterRiskLevel, idDataGroup);
                iter.getObject()->getField(ifds::CountryOfExposure, iterRiskCntry, idDataGroup);

                if (dstrRiskLevel == iterRiskLevel &&
                    dstrRiskCntry == iterRiskCntry)
                {
                    found = true;
                    break;
                }

                iter++;
            }

            if (!found)
            {
                ADDCONDITIONFROMFILE(CND::WARN_HIGHEST_RISK_LVL_IS_REQUIRED);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Entity::validateGenderForElectedSingleLifeNMCR (const DString &dstrGender, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
						   CLASSNAME, 
						   I_( "validateAnnuitantGenderForElectedSingleLifeNMCR" ) );

	DString dstrAccountNum, dstrEntityType, dstrOrgGender;
	AccountEntityXref *pAccountEntityXref (NULL);	

	getFieldBeforeImage (ifds::Gender, dstrOrgGender);  
	dstrOrgGender.stripAll();	

	if (!dstrGender.empty () && !dstrOrgGender.empty () && dstrGender != dstrOrgGender) 
	{
		if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
		{
			BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
												 idDataGroup, 
												 true, 
												 BFObjIter::ITERTYPE::NON_DELETED);
			DString searchKey;
			AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
			iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

			while (!iterAccountEntityXrefOut.end())
			{
				DString key = iterAccountEntityXrefOut.getStringKey ();                                                         
				DString dstrEntityId;
				AccountEntityXref::getValueForTag (key, I_("EntityId"), dstrEntityId);
				dstrEntityId.stripLeading('0');

				if (dstrEntityId == _entityId) // ensure same entityid
				{					
					AccountEntityXref::getValueForTag (key, I_("AccountNum"), dstrAccountNum);
					dstrAccountNum.stripLeading ('0');	
					break;
				}
				++iterAccountEntityXrefOut;
			}         
		}

		MFAccount *pMFAccount = NULL;
		ContractInfoList* pContractInfoList = NULL;   
		bool bElectedSingleLifeNMCR = false;		

		if( !dstrAccountNum.empty() && 
			getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
			pMFAccount)
		{	   		
			if( pMFAccount->getContractInfoList(pContractInfoList, idDataGroup) && pContractInfoList )
			{		
				BFObjIter iterContractList( *pContractInfoList, idDataGroup );

				iterContractList.begin();
				while( !iterContractList.end() )
				{
					ContractInfo *pContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );

					if ( pContractInfo != NULL ) 
					{				  
						if (pContractInfo->isElectedSingleLifeNMCR (idDataGroup)) 
						{							  					   					  
							bElectedSingleLifeNMCR = true;
							break;					
						}
					}
					++iterContractList;
				}               
			}			
		}	

		if (bElectedSingleLifeNMCR) 
		{ 		 
			getErrMsg (IFASTERR::GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT,
					   CND::ERR_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT,
					   CND::WARN_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT,
					   idDataGroup);		
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::validateGenderAgainstElectResetEvent (const DString &dstrGender, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateGenderAgainstElectResetEvent" ) );

   DString dstrAccountNum, dstrEntityType, dstrOrgGender;
   AccountEntityXref *pAccountEntityXref (NULL);

   getFieldBeforeImage (ifds::Gender, dstrOrgGender);
   dstrOrgGender.stripAll();

   if (!dstrGender.empty () && dstrGender != dstrOrgGender) 
   {
      if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
      {
         BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);

         DString searchKey;
         AccountEntityXref::buildPartialKeyForEntityId (searchKey, _entityId);
         iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

         while (!iterAccountEntityXrefOut.end())
         {
            DString key = iterAccountEntityXrefOut.getStringKey ();
            DString dstrEntityId;
            AccountEntityXref::getValueForTag (key, I_("EntityId"), dstrEntityId);
            dstrEntityId.stripLeading('0');

            if (dstrEntityId == _entityId) // ensure same entityid
            {
               AccountEntityXref::getValueForTag (key, I_("AccountNum"), dstrAccountNum);
               dstrAccountNum.stripLeading ('0');	
               break;
            }
            ++iterAccountEntityXrefOut;
         }
      }

      MFAccount *pMFAccount = NULL;
      ContractInfoList* pContractInfoList = NULL;   
      bool bTOExisted = false;

      if( !dstrAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
      {
         if( pMFAccount->getContractInfoList(pContractInfoList, idDataGroup) && pContractInfoList )
         {
            BFObjIter iterContractList( *pContractInfoList, idDataGroup );

            iterContractList.begin();
            while( !iterContractList.end() )
            {
               ContractInfo *pContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );

               if ( pContractInfo != NULL ) 
               {
                  DString strTOExistAfterPreElectReset = NULL_STRING;
                  pContractInfo->getField(ifds::TOExistAfterPreElectReset, strTOExistAfterPreElectReset, idDataGroup,false);
                  strTOExistAfterPreElectReset.strip().upperCase();

                  if (strTOExistAfterPreElectReset == I_("Y")) 
                  {
                     bTOExisted = true;
                     break;
                  }
               }
               ++iterContractList;
            }
         }
      }

      if (bTOExisted) 
      {
         getErrMsg (IFASTERR::TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION,
                    CND::ERR_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION,
                    CND::WARN_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION,
                    idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::getEntityRegDetailsList(EntityRegDetailsList *&pEntityRegDetailsList,   
										 const BFDataGroupId &idDataGroup,
										 const DString &accountNum /* NULL_STRING */)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityRegDetailsList")); 

	//DString dstrAccountNum;
	//getAccountNum(dstrAccountNum, idDataGroup); 

	DString dstrKey = I_("EntRegDetails_Account=") + accountNum + I_("_EntityId=") + _entityId.strip();
	//DString dstrKey = I_("EntityRegDetailsList");
	pEntityRegDetailsList = dynamic_cast <EntityRegDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pEntityRegDetailsList )
	{
		pEntityRegDetailsList = new EntityRegDetailsList( *this );
		pEntityRegDetailsList->setField(ifds::AccountNum, accountNum, BF::HOST, false);

		if (!isNew())
		{
			pEntityRegDetailsList->init(accountNum , _entityId.strip());
		}

		if( pEntityRegDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{				
				setObject( pEntityRegDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pEntityRegDetailsList;
				pEntityRegDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Entity::getEntityRegJurisDetailsList(EntityRegJurisDetailsList *&pEntityRegJurisDetailsList,   
											  const BFDataGroupId &idDataGroup,
											  const DString &accountNum /* NULL_STRING */)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityRegJurisDetailsList")); 

	//DString dstrAccountNum;
	//getAccountNum(dstrAccountNum, idDataGroup); 

	DString dstrKey = I_("EntRegJurisDetails_Account=") + accountNum + I_("_EntityId=") + _entityId.strip ();
	//DString dstrKey = I_("EntityRegJurisDetailsList");	
	pEntityRegJurisDetailsList = dynamic_cast <EntityRegJurisDetailsList*>(getObject(dstrKey, idDataGroup));

	if( !pEntityRegJurisDetailsList )
	{
		pEntityRegJurisDetailsList = new EntityRegJurisDetailsList( *this );
		pEntityRegJurisDetailsList->setField(ifds::AccountNum, accountNum, BF::HOST, false);

		if (!isNew())
		{
			pEntityRegJurisDetailsList->init(accountNum , _entityId.strip());
		}

		if( pEntityRegJurisDetailsList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
				setObject( pEntityRegJurisDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pEntityRegJurisDetailsList;
				pEntityRegJurisDetailsList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

////******************************************************************************
bool Entity::isAccountHolderRiskApplicable( const BFDataGroupId &idDataGroup)
{
   bool bAccountHolderRiskApplicable = false;
   //check if the account holder risk comply rule is active at the environement.
   TranslationTable* pTranslationTable = NULL;
   getMgmtCo ().getTranslationTable (COMPLY_RULES_SET, pTranslationTable);
   bool bAccountHolderRiskActive = false;
   if (pTranslationTable)
   {
     BFObjIter iter( *pTranslationTable, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );     
     while(!iter.end() && !bAccountHolderRiskActive )
     {
       DString dstrMiscCode;
       iter.getObject()->getField( ifds::MiscCode, dstrMiscCode, idDataGroup, false );
       dstrMiscCode.upperCase();
       bAccountHolderRiskActive = COMPLY_RULE::AccountholderRisk == dstrMiscCode ? true : false;
       ++iter;
     }
   }
   if(!bAccountHolderRiskActive)
       return bAccountHolderRiskApplicable;

   AccountEntityXref* pAccountEntityXref = NULL;
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING &&
       pAccountEntityXref )
    {
          DString  dstrRiskApplEntity, dstrRiskApplEntitySeq, dstrRiskForAcctHldrRsk;
          DString  dstrEntityType, dstrEntityRisk, dstrEntitySeq, dstrEntityID;
          DString dstrAcctNum;
          getAccountNum(dstrAcctNum, idDataGroup);
          getWorkSession().getOption(ifds::RiskApplEntity, dstrRiskApplEntity, BF::HOST, false);
          getWorkSession().getOption(ifds::RiskApplEntitySeq, dstrRiskApplEntitySeq, BF::HOST, false);
          getWorkSession().getOption(ifds::RiskForAcctHldrRsk, dstrRiskForAcctHldrRsk, BF::HOST, false);
          BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                                 idDataGroup, 
                                                 true, 
                                                 BFObjIter::ITERTYPE::NON_DELETED);

          iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE );
          //1.Check for the applicable entity is in the entity crossref object based on the environement configuration.
          //2.Check for the applicable entity sequence is applicable based on the environement configuration.
          //3.Check for the applicable entity Risk is applicable based on the environement configuration.
          while (!iterAccountEntityXrefOut.end() && !bAccountHolderRiskApplicable )
          {
             AccountEntityXrefObject *pXrefObject = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());
             //The documents for the AccountHolder risk is attached by back-end based on the Entity Risk..
             //if the entity is new and not commited yet AccountHolderRisk is Not Applicable as the back-end had not created any documents yet.
             if(pXrefObject)// && !pXrefObject->isNew())
             {
               Entity* pEntity = NULL;
               pXrefObject->getField(ifds::EntityId, dstrEntityID, idDataGroup );
               getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity );  
               //the is new key will not work here as on the entity mainteneace you can add enity to account two ways
               //case 1.Add a totally new entity -like EntityID-999XXXXXX-this case it works
               //case 2.You can link an exisiting entity in the sytem to an account..This case your is new will fail...
               // so best place to check one step ahead if this is new to the account.. which is done by pXrefObject->isNew() in previous if           
               if( pEntity /*&& !pEntity->isNew()*/) 
               {
                  pXrefObject->getField(ifds::EntityType, dstrEntityType, idDataGroup );
                  if(!isNew())
                  {
                        pXrefObject->getField(ifds::EntityTypeSeq, dstrEntitySeq, idDataGroup );                 
                  }
                  else
                  {
                        pXrefObject->getField(ifds::SeqNumber, dstrEntitySeq, idDataGroup );                 
                  }
                  pEntity->getField(ifds::RiskLevel, dstrEntityRisk, idDataGroup ); 
                  bAccountHolderRiskApplicable = ( (isCodeInList( dstrEntityType, dstrRiskApplEntity)     || APPLICABLE_TO_ALL == dstrRiskApplEntity ))   &&
                                                 ( (isCodeInList( dstrEntitySeq, dstrRiskApplEntitySeq)   || APPLICABLE_TO_ALL == dstrRiskApplEntitySeq)) &&
                                                 ( (isCodeInList( dstrEntityRisk, dstrRiskForAcctHldrRsk) || APPLICABLE_TO_ALL == dstrRiskForAcctHldrRsk)) ;
               }        
             }
             ++iterAccountEntityXrefOut;
          } //while   
      } //if
   return bAccountHolderRiskApplicable;
}
//******************************************************************************
SEVERITY Entity::validationForCRM (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("valiateEmail"));

   // Default condition
   SEVERITY sevRtn = NO_CONDITION;

   DString dstrEmail;
   getField(ifds::Email,dstrEmail, idDataGroup);
   dstrEmail.strip();

   if (dstrEmail.empty () || dstrEmail == I_(" "))
   {  
		ADDCONDITIONFROMFILE(CND::ERR_EMAIL_IS_MISSING);  
   }

   DString firstName;
   getField(ifds::FirstName, firstName, idDataGroup);
   firstName.strip();

   DString dstrEmployeeClass;
   getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup);

   if ((dstrEmployeeClass != ENTITY_CATEGORY::CORPORATE) && (firstName.empty () || firstName == I_(" ")))
   {         
		ADDCONDITIONFROMFILE(CND::ERR_FIRST_NAME_IS_MISSING);	  
   }

   EntityIdsList *entityIdList = NULL;
   if(getEntityIdsList(entityIdList, idDataGroup) > WARNING ||
      !entityIdList ||
      !entityIdList->isIdTypeExist(IDS::ACCOUNT_MANAGER_UNIQUE_ID, idDataGroup))
   {
		ADDCONDITIONFROMFILE(CND::ERR_ACCOUNT_MANAGER_ID_MANDATORY);	  
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::validateTaxJurisForRDSP( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,	CLASSNAME, I_( "validateTaxJurisForRDSP" ) );

	MFAccount *pMFAccount = NULL;
	DString dstrAccountNum, dstrTaxType, dstrTaxJuris;

	getAccountNum(dstrAccountNum, idDataGroup); 
	if ( !dstrAccountNum.empty() && 
		 getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
		 pMFAccount)
	{
		pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
		dstrTaxType.strip().upperCase();
	}	
		
	getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);	

	if (dstrTaxType == RDSP_TAX_TYPE && _entityType == RDSP_BENEFICIARY)
	{
		if ( dstrTaxJuris == NULL_STRING ||	dstrTaxJuris == UNASSIGNED_COUNTRY )
		{
			ADDCONDITIONFROMFILE (CND::ERR_TAX_JURIS_INVALID);
		}

		if (!dstrTaxJuris.empty())
		{          
			// check if Canadian resident
			DString dstrResidency1, dstrResidency2, dstrResidency3;

			getWorkSession().getOption (ifds::Residency1, dstrResidency1, idDataGroup, false);
			getWorkSession().getOption (ifds::Residency2, dstrResidency2, idDataGroup, false);
			getWorkSession().getOption (ifds::Residency3, dstrResidency3, idDataGroup, false);

			if(!( DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency1) ||
				DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency2) ||
				DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency3) ) )
			{
				// 2049 - Beneficiary must be a Canadian resident  
				getErrMsg (IFASTERR::RDSP_BENEFICIARY_NON_RESIDENT,
						   CND::ERR_RDSP_BENEFICIARY_NON_RESIDENT,
						   CND::WARN_RDSP_BENEFICIARY_NON_RESIDENT,
						   idDataGroup);
			}		
		}	
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Entity::validateRDSPEntity (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPEntity"));

	MFAccount *pMFAccount = NULL;
	DString dstrAccountNum, dstrTaxType;

	getAccountNum(dstrAccountNum, idDataGroup); 
	if ( !dstrAccountNum.empty() && 
		 getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
		 pMFAccount)
	{
		pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
		dstrTaxType.strip().upperCase();
	}
	
	if (dstrTaxType == RDSP_TAX_TYPE)
	{
		DString dstrEmployeeClass, firstName;

		getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false);
		getField(ifds::FirstName, firstName, idDataGroup);
		firstName.strip();

		if ( !_entityType.empty() && 
			 (dstrEmployeeClass != ENTITY_CATEGORY::CORPORATE) &&
			 (firstName.empty () || firstName == I_(" ")) )
		{				  				 				  				 		  					 									        
			ADDCONDITIONFROMFILE(CND::ERR_FIRST_NAME_IS_MISSING);	  
		}
	}

	return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Entity::validationForEmailPhone (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validationForEmailPhone"));

   DString dstrEmail;
   getField(ifds::Email,dstrEmail, idDataGroup);
   dstrEmail.strip();

   DString dstrEmail2;
   getField(ifds::Email2,dstrEmail2, idDataGroup);
   dstrEmail2.strip();

   DString dstrHomePhone, dstrBusinessPhone, dstrSecondPhoneNum;
   getField(ifds::HomePhone,dstrHomePhone, idDataGroup);
   dstrHomePhone.strip();

   getField(ifds::BusinessPhone,dstrBusinessPhone, idDataGroup);
   dstrBusinessPhone.strip();

   getField(ifds::SecondPhoneNum,dstrSecondPhoneNum, idDataGroup);
   dstrBusinessPhone.strip();

    if ((dstrEmail.empty () && dstrEmail2.empty ()) ||
		(dstrHomePhone.empty () && dstrBusinessPhone.empty () && dstrSecondPhoneNum.empty ()) )
   {  
	    getErrMsg(IFASTERR::EMAIL_PHONE_CANNOT_BE_BLANK, 
		   CND::ERR_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK, 
		   CND::WARN_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK,
		   idDataGroup);  
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Entity.cpp-arc  $
 * 
 *    Rev 1.133   Aug 16 2012 10:52:34   wp040027
 * IN#3008167-P187485-CPF- Account Entity (RA) validation
 * 
 *    Rev 1.132   Jul 23 2012 17:09:34   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.131   Jul 16 2012 14:09:18   wp040133
 * work order #801810
 * IN#-3003878 PET: P0187485 Sync from 12.4
 * 
 *    Rev 1.130   Jul 16 2012 22:18:32   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, code review.
 * 
 *    Rev 1.129   Jul 16 2012 18:37:38   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts. Restore 1.127
 * 
 *    Rev 1.128   Jul 16 2012 15:04:20   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.127   Jul 12 2012 19:05:38   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.126   Jul 10 2012 12:12:30   wp040133
 * IN#-3003878
 * PET: P0187485 
 * Can update Registration Agent details via Account level screen
 * 
 *    Rev 1.125   Jun 04 2012 14:30:18   if991250
 * CPF - Account Entity 
 * 
 *    Rev 1.124   May 28 2012 10:38:18   if991250
 * CPF - Account Entity + Systematics
 * 
 *    Rev 1.123   Apr 30 2012 15:44:30   popescu
 * 2902002 - Synch-up P0186480FN02 - Diploma DSK Validation
 * 
 *    Rev 1.122   Apr 04 2012 22:35:02   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.121   Feb 06 2012 04:22:32   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.120   Dec 19 2011 04:38:50   panatcha
 * IN2766093 - IWT TIN Validation
 * 
 *    Rev 1.119   Nov 30 2011 04:14:34   panatcha
 * IN2738162 Loan Number vs shareholder
 * 
 *    Rev 1.118   Nov 27 2011 22:29:28   popescu
 * 2740236 - TIN Validation
 * 
 *    Rev 1.117   Nov 09 2011 01:56:18   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues - Modify validation for RRSP Loan when delete.
 * 
 *    Rev 1.116   Nov 08 2011 08:10:34   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues.
 * 
 *    Rev 1.115   Oct 14 2011 03:08:36   kitticha
 * PETP0186486 FN01 IN2685299 - RRSP Loan program issues.
 * 
 *    Rev 1.114   Oct 13 2011 18:52:04   popescu
 * PETP0186486 FN01 - RRSP Loan Program - fixed a linkage warning
 * 
 *    Rev 1.113   Sep 02 2011 13:04:30   kitticha
 * PETP0186486 FN01 - RRSP Loan Program.
 * 
 *    Rev 1.112   Jul 13 2011 12:27:50   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test, no need to raise up warning when there is change on deceased annuitant's date of death.
 * 
 *    Rev 1.111   Jul 11 2011 07:26:26   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test.
 * 
 *    Rev 1.110   Jul 07 2011 19:01:14   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.109   Jan 10 2011 04:27:42   wutipong
 * IN2261419 - Not able to add Clearing Platform Entity 
 * 
 *    Rev 1.108   Nov 29 2010 09:06:02   wutipong
 * IN#2143362 - Large delay when adding specific BIC code in AXA - Clean Up
 * 
 *    Rev 1.107   Nov 26 2010 06:17:20   wutipong
 * IN#2143362
 * 
 *    Rev 1.106   May 06 2010 23:35:56   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.105   Apr 30 2010 11:08:18   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.104   Apr 07 2010 09:36:46   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.103   Apr 06 2010 06:29:24   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, move validation logic from account entity cross reference to entity.
 * 
 *    Rev 1.102   Mar 23 2010 13:42:04   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.101   Mar 17 2010 06:49:30   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.100   Mar 12 2010 14:58:08   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.99   May 21 2009 14:26:18   dchatcha
 * PET 157825 FN18 - MF and MFR Day 2, issue found during test of adding non-account related by 'All Entity' screen.
 * 
 *    Rev 1.98   Mar 13 2009 15:49:00   jankovii
 * IN 1625664 - RL91 No control for the Language to be a mandatory field during entity update
 * 
 *    Rev 1.97   12 Mar 2009 15:34:02   kovacsro
 *  1624451 - Clearing Platform Entity Error display
 * 
 *    Rev 1.96   Feb 20 2009 14:41:34   jankovii
 * IN  1557042 - Accountholder less than 55 but no warning on Desktop and a/c created
 * 
 *    Rev 1.95   Feb 10 2009 14:08:22   jankovii
 * IN 1586269 - Able to future date the Death Notification Date
 * 
 *    Rev 1.94   23 Jan 2009 16:32:16   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.93   16 Jan 2009 17:23:04   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.92   Jan 16 2009 15:13:26   jankovii
 * IN 1557042 Accountholder less than 55 but no warning on Desktop and a/c created.
 * 
 *    Rev 1.91   Jan 16 2009 09:37:16   jankovii
 * IN 1555859 Entry of Notification Date
 * 
 *    Rev 1.90   Jan 08 2009 05:59:50   daechach
 * IN 1545482 - R91-MT535/MT536-users should not be able to create Clearing platform entities.
 * 
 *    Rev 1.89   Dec 15 2008 01:41:30   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.88   Nov 28 2008 14:31:54   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.87   Nov 12 2008 05:36:58   phiwponp
 * Sync up: IN 1405047-Invalid warning message when updating the last name of the entity.
 * 
 *    Rev 1.86   03 Nov 2008 17:32:38   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.85   31 Oct 2008 16:18:32   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.84   Oct 28 2008 08:31:44   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.83   Sep 26 2008 12:21:10   jankovii
 * Sync up: IN 1420802
 * 
 *    Rev 1.82   Sep 19 2008 04:54:22   daechach
 * Synch up from 1.78.1.3 for R90&R91
 * 
 *    Rev 1.81   Sep 19 2008 04:49:38   daechach
 * Synch up from Rev 1.78.1.2 for R90&R91
 * 
 *    Rev 1.80   Sep 19 2008 04:44:34   daechach
 * Synch up from 1.78.1.1 for R90&R91
 * 
 *    Rev 1.79   Sep 19 2008 04:38:48   daechach
 * Synch up from Rev 1.78.1.0 for R90&R91
 * 
 *    Rev 1.78   Jul 25 2008 14:42:50   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.77   Jun 12 2008 10:51:32   daechach
 * in#1281683 - Creating new account Warning, Remove warning displaying for blank phone/fax number.
 * 
 *    Rev 1.76   Apr 10 2008 11:04:48   jankovii
 * IN 1235879 - AIM database issue - Nominee Change Caused Locks.
 * 
 *    Rev 1.75   Feb 27 2008 15:57:14   jankovii
 * IN 820350 - validation for phone/fax number length.
 * 
 *    Rev 1.74   Jul 27 2007 16:53:38   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.73   27 Jun 2007 16:47:32   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.72   Nov 20 2006 13:52:52   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.71   Nov 09 2006 13:45:26   jankovii
 * Incident #737656. BIC code validation.
 * 
 *    Rev 1.70   Nov 06 2006 10:07:22   jankovii
 * Incident #737656: Bic code validation.
 * 
 *    Rev 1.69   Oct 19 2006 14:13:02   jankovii
 * Incident 737656 - No validation for unique BIC code during new entity setup.
 * 
 *    Rev 1.68   Oct 18 2006 09:41:58   jankovii
 * Sync up with Incident 736612: Validate BIC code only for network sender entities.
 * 
 *    Rev 1.67   Sep 06 2006 09:06:54   jankovii
 * IN 698431 - EUSD option is not updated.
 * 
 *    Rev 1.66   Jul 25 2006 15:59:02   jankovii
 * PET 2192 FN02 - Dealings Sender Cut Off Time.
 * 
 *    Rev 1.65   Jul 21 2006 13:56:10   jankovii
 * PET 2192 FN02 - Dealings-Sender Cut-Off Time.
 * 
 *    Rev 1.64   Jun 28 2006 17:32:56   popescu
 * Incident# 642164 - trigger validation for already exiting entities without a tax jurisd
 * 
 *    Rev 1.63   Apr 11 2006 14:19:48   AGUILAAM
 * IN_592181 : deathdate validation does not apply when birthdate is blank
 * 
 *    Rev 1.62   Dec 14 2005 10:49:16   popescu
 * Incindent# 485179 - fix will invalidate the two tax jurisdiction required fields after reset. This will result in the validation method to be triggered when user hits the OK button.
 * 
 *    Rev 1.61   Dec 02 2005 14:44:00   porteanm
 * Incident 468259 - EUSD Tax option should also be displayed now when the entity is linked to a Fund only, and not with any client.
 * 
 *    Rev 1.60   Nov 30 2005 14:13:24   jankovii
 * PET1228_FN02 - small fixes.
 * 
 *    Rev 1.59   Nov 30 2005 13:10:00   popescu
 * Incindent# 463650 - a dummy where used record was erroneous sent to back-end - re-synch
 * 
 *    Rev 1.58   Nov 24 2005 09:10:42   jankovii
 * PET1228_FN02 EU Saving Directive Phase 2
 * 
 *    Rev 1.57   May 19 2005 15:54:08   yingbaol
 * Incident 297032:  all fields should not be allowed to update if the stratus is bad. 
 * 
 *    Rev 1.56   May 02 2005 11:07:18   yingbaol
 * Incident300186: EUSD option is not applicable for FundBroker 
 * 
 *    Rev 1.55   Apr 11 2005 14:52:22   yingbaol
 * Incident 284670: change substitution list and default value according winnie's email.
 * 
 *    Rev 1.54   Apr 08 2005 16:27:40   yingbaol
 * Incident 284670: to be save check pointer before using it.
 * 
 *    Rev 1.53   Apr 08 2005 11:37:46   yingbaol
 * incident 284670, effectivedate issue in NASU flow
 * 
 *    Rev 1.52   Mar 30 2005 13:55:26   yingbaol
 * PET1171,FN01: set Taxjurisdiction as required based on the general control 
 * 
 *    Rev 1.51   Mar 11 2005 15:41:50   yingbaol
 * PET1171,FN01: EU saving: do not create stand alone where used list when do validation.
 * 
 *    Rev 1.50   Mar 09 2005 16:04:00   yingbaol
 * PET 1171,FN01: EU saving entity update
 * 
 *    Rev 1.49   Mar 01 2005 11:51:50   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.48   Jan 20 2005 13:49:44   Fengyong
 * 10038154 - warning message when change name for existing entity
 * 
 *    Rev 1.47   Dec 07 2004 17:15:24   popescu
 * Fixed NASU flow, due to EntityId field not being correctly set.
 * 
 *    Rev 1.46   Nov 25 2004 15:02:00   Fengyong
 * warning when chnage name for a entity used by other account or fund broker
 * 
 *    Rev 1.45   Nov 14 2004 14:36:30   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.44   Nov 08 2004 12:30:54   popescu
 * PET 1117/06 trade processing
 * 
 *    Rev 1.43   Nov 04 2004 17:37:24   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.42   Apr 23 2004 17:22:42   HERNANDO
 * PET1027 FN02 - Added RiskLevel; set RiskLevel based on EntityRiskLevel value.
 * 
 *    Rev 1.41   Nov 19 2003 10:17:48   linmay
 * added BirthPlace for SSB
 * 
 *    Rev 1.40   Nov 08 2003 21:46:04   popescu
 * PTS 10023438, performance issues fixes, do not call PopulateWhereUsed anymore, data is in memory
 * 
 *    Rev 1.39   Nov 05 2003 18:05:00   popescu
 * PTS 10023703, Erroneous warning 'Account owner SIN missing' pops-up, although the SIN number is correctly retrieved by Desktop from back-end,
 * 
 *    Rev 1.38   Oct 30 2003 16:30:28   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 *    Rev 1.37   Oct 14 2003 11:39:14   HERNANDO
 * PET859 FN08 / PET893 FN08 - Account name field enhancement and Salutation enhancement.
 * 
 *    Rev 1.36   Sep 15 2003 15:03:16   HERNANDO
 * Changed Error Message Numbers for Date of Birth and Occupation to #386 and #386 respectively.
 * 
 *    Rev 1.35   Aug 21 2003 19:52:38   FENGYONG
 * KYC Joint info enhancement
 * 
 *    Rev 1.34   Aug 01 2003 11:39:06   HERNANDO
 * Occupation Field enhancments.
 * 
 *    Rev 1.33   Jul 28 2003 15:54:06   HERNANDO
 * Use Date of Birth ErrMessageRule.
 * 
 *    Rev 1.32   Jul 25 2003 16:07:42   HERNANDO
 * Added doValidateDateOfBirth.
 * 
 *    Rev 1.31   Jul 22 2003 11:48:06   ZHANGCEL
 * Skip prevalidation of IdValue whenever IdType is empty
 * 
 *    Rev 1.30   May 20 2003 16:54:30   popescu
 * Fixed PTS 10014779 , crash in DSTCEntytIDs Builder because an iterator in getEntityIds method of the Entity object was built on an NULL pointer list
 * 
 *    Rev 1.29   Apr 09 2003 12:48:58   sanchez
 * For Nationality field, setFieldUpdated (ifds::Nationality, idDataGroup, true) only if Nationality blank is an error or a warning.
 * 
 *    Rev 1.28   Apr 03 2003 13:12:40   sanchez
 * For Nationality field, set field info  flags to REQUIRED and call setFieldUpdated from setFlagsUpdated.
 * 
 *    Rev 1.27   Mar 21 2003 18:07:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.26   Mar 12 2003 08:54:50   sanchez
 * Changes for adding the "Nationality" field to the Entity Maintenance dialog.
 * 
 *    Rev 1.25   Feb 20 2003 14:47:36   HSUCHIN
 * PTS - 10013818 : bug fix to desktop crash when duplicate sin check returns with an error.
 * 
 *    Rev 1.24   Nov 29 2002 15:41:06   ZHANGCEL
 * Synced  up to 1.25
 * 
 *    Rev 1.23   Oct 09 2002 23:54:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.22   Aug 29 2002 12:55:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.21   Jul 18 2002 14:19:58   FENGYONG
 * Init EntityId 
 * 
 *    Rev 1.20   Jul 06 2002 19:09:54   WINNIE
 * Add SIN validation for new Tax rule for redemption
 * 
 *    Rev 1.19   22 May 2002 18:28:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   30 Apr 2002 16:27:28   HERNANDO
 * Added EmployeeClass to classFieldInfo[].
 * 
 *    Rev 1.17   Feb 25 2002 18:55:40   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.16   20 Nov 2001 11:15:52   KOVACSRO
 * code clean up.
 * 
 *    Rev 1.15   19 Nov 2001 10:29:48   KOVACSRO
 * implemented doPopulateField.
 * 
 *    Rev 1.14   09 Aug 2001 13:21:10   HSUCHIN
 * added support for Area code for the Canadian market
 * 
 *    Rev 1.13   02 Aug 2001 15:16:42   YINGZ
 * fix delete problem
 * 
 *    Rev 1.12   Jul 29 2001 14:55:16   YINGBAOL
 * fix birth lastname issue
 * 
 *    Rev 1.11   03 May 2001 14:06:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   21 Feb 2001 18:11:34   KOVACSRO
 * Added an overloaded getEntityAge method.
 * 
 *    Rev 1.9   Feb 14 2001 17:05:32   DINACORN
 * EffectiveDate taken from AcctInfo in NASU
 * 
 *    Rev 1.8   Jan 17 2001 12:08:28   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions ()
 * 
 *    Rev 1.7   Dec 17 2000 20:23:16   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 05 2000 17:16:52   DINACORN
 * Synchronization to C2/C3: Implement getEntityAge () method
 * 
 *    Rev 1.5   Nov 16 2000 13:52:10   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.4   Oct 27 2000 13:24:14   YINGBAOL
 * add death notify validation and fix bug
 * 
 *    Rev 1.3   Jul 20 2000 14:35:48   HUANGSHA
 * validation for IDS and BirthName based on the system feature
 * 
 *    Rev 1.2   Jun 27 2000 10:52:12   HUANGSHA
 * removed the required flag for salutation
 * 
 *    Rev 1.1   Jun 08 2000 11:17:08   YINGZ
 * fix NASU dlg can close without lastname... problem
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.44   Feb 08 2000 13:40:18   VASILEAD
 * Fixed reset for EffectiveDate
 * 
 *    Rev 1.43   Jan 26 2000 20:22:10   POPESCUS
 * fix to the required list
 * 
 *    Rev 1.42   Jan 26 2000 19:43:10   VASILEAD
 * Fixes
 * 
 *    Rev 1.41   Jan 23 2000 19:34:26   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.40   Jan 17 2000 14:00:24   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.39   Jan 16 2000 16:59:48   POPESCUS
 * changes to the children lists
 * 
 *    Rev 1.38   Jan 10 2000 16:15:28   VASILEAD
 * Added Joint information in Entity screen
 * 
 *    Rev 1.37   Jan 10 2000 10:09:16   POPESCUS
 * none to the lists
 * 
 *    Rev 1.36   Jan 09 2000 19:11:20   POPESCUS
 * bug fixes?
 * 
 *    Rev 1.35   Jan 09 2000 14:58:30   VASILEAD
 * Corrected entity screen in the NASU
 * 
 *    Rev 1.34   Jan 08 2000 14:33:04   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.33   Jan 07 2000 17:02:46   VASILEAD
 * Validations for Entity screen
 * 
 *    Rev 1.32   Jan 06 2000 16:21:10   VASILEAD
 * Business edits for Entity screen
 * 
 *    Rev 1.31   Dec 24 1999 15:18:24   VASILEAD
 * Fixed transactions
 * 
 *    Rev 1.30   Dec 24 1999 10:29:50   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.29   Dec 22 1999 14:27:22   VASILEAD
 * fixed getEntityIds
 * 
 *    Rev 1.28   Dec 22 1999 14:21:04   VASILEAD
 * Added idDataGroup to getEntityIds and getEntityAddresses functions
 * 
 *    Rev 1.27   Dec 20 1999 11:15:58   BUZILA
 * added getTopLevelAncestor () method
 * 
 *    Rev 1.26   Dec 15 1999 11:08:10   POPESCUS
 * added new boolean param to the lists accessor methods; whether to inquire the database or not
 * 
 *    Rev 1.25   Dec 12 1999 16:25:18   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/