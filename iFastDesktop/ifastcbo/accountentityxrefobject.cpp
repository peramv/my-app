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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountEntityXrefObject.cpp
// ^AUTHOR : Adrian + Serban
// ^DATE   : 
//
//******************************************************************************
#include "stdafx.h"

#include "acctcategorylist.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "dstcommonfunction.hpp"
#include "dstcworksession.hpp"
#include "entity.hpp"
#include "entity.hpp"
#include "entityaddressmailinglist.hpp"
#include "entityids.hpp" //MT535/MT536
#include "entityidslist.hpp" //MT535/MT536
#include "errmsgruleslist.hpp"
#include "funddetaillist.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "respinfoupdatevalidationlist.hpp" //QESI3FN03
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "worksessionentitylist.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

#include <algorithm>

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME                  = I_( "AccountEntityXrefObject" );
   const I_CHAR * ACCOUNT_NUMBER_FIELD       = I_( "AccountNum" );
   const I_CHAR * ENTITY_ID_FIELD            = I_( "EntityId" );
   const I_CHAR * ENTITY_TYPE_FIELD          = I_( "EntityType" );
   const I_CHAR * ENTITY_SEQ_NUM_FIELD       = I_( "EntitySeq" );
   const I_CHAR * X_FIELD                    = I_( "X" );
   const I_CHAR * UNIT_AMOUNT_TYPE           = I_( "U" );

   const I_CHAR * ACCOUNT_OWNER              = I_( "01" );
   const I_CHAR * AUTHORIZED_REP             = I_( "02" );
   const I_CHAR * LEGAL_REP                  = I_( "03" );
   const I_CHAR * ECONOMIC_REP               = I_( "04" );
   const I_CHAR * ANNUITANT                  = I_( "05" );
   const I_CHAR * SPOUSAL_CONTRIBUTOR        = I_( "06" );
   const I_CHAR * PRIMARY_BENEFICARY         = I_( "07" );
   const I_CHAR * SECONDARY_BENEFICARY       = I_( "08" );
   const I_CHAR * SUCCESSOR                  = I_( "09" ); //CAN
   const I_CHAR * ESCROW_REPRESENTATIVE      = I_( "11" ); //can
   const I_CHAR * ALTERNATE_PAYEE            = I_( "12" );
   const I_CHAR * TRUSTEE                    = I_( "13" );
   const I_CHAR * ITF_INDIVIDUAL             = I_( "14" );
   const I_CHAR * NOMINEE_OWNER              = I_( "21" );
   const I_CHAR * EXECUTOR                   = I_( "22" );
   const I_CHAR * POWER_OF_ATTORNEY          = I_( "23" );
   const I_CHAR * RESP_BENEFICIARY           = I_( "50" ); //CAN
   const I_CHAR * PARENT_GUARDIAN            = I_( "51" );
   const I_CHAR * RESP_DSGN_INST             = I_( "52" );
   const I_CHAR * ASSIGNEE                   = I_( "53" );
   const I_CHAR * RESP_PCG_INDIV             = I_( "55" );
   const I_CHAR * RESP_PCG_INST              = I_( "56" );
   const I_CHAR * CLEARING_PLATFORM          = I_( "58" ); //MT535/MT536
   const I_CHAR * JOINT_LIFE                 = I_( "60" );
   const I_CHAR * ENTITY_TYPE_REG_AGENT      = I_( "64" );
   const I_CHAR * AUTHORIZED_SIGNATORY       = I_( "65" );
   const I_CHAR * PARTNER                    = I_( "66" );
   const I_CHAR * SETTLOR                    = I_( "67" );
   const I_CHAR * ESTATE_OF_DECEASED         = I_( "68" );
   const I_CHAR * RELATED_PARTY              = I_( "71" );
   const I_CHAR * LEAD_ACCOUNT_MANAGER       = I_( "76" );
   const I_CHAR * ACCOUNT_MANAGER            = I_( "77" );
   const I_CHAR * RELATED_PARTY_AML_ENTITY_TYPE = I_( "78" );
   const I_CHAR * OTHER                      = I_( "99" );

   const I_CHAR * NON_REGISTER  = I_( "0" );
   const I_CHAR * RRSP          = I_( "1" );
   const I_CHAR * EXTERNAL_RRSP = I_( "3" );

   const I_CHAR * RESP              = I_( "9" );
   const I_CHAR * FAMILY_PLAN_RESP  = I_( "M" );
   const I_CHAR * SPOUSAL_ACCOUNT   = I_( "1" );
   const I_CHAR * JOINT             = I_( "2" );
   const I_CHAR * TRUST             = I_( "3" );
   const I_CHAR * NOMINEE           = I_( "2" );
   const I_CHAR * INTERMEDIAR       = I_( "3" );

   const I_CHAR * BANKRUPTCY_REASON_CODE  = I_( "01" );
   const I_CHAR * RSP_LOAN_REASON_CODE    = I_( "05" );
   const I_CHAR * COLLATERAL_REASON_CODE  = I_( "06" );
   const I_CHAR * LOAD_REASON_CODE        = I_( "09" );

   const I_CHAR * const RRSP_TAX_TYPE                    = I_( "1" );
   const I_CHAR * const RRIF_TAX_TYPE                    = I_( "2" );
   const I_CHAR * const LRIF_TAX_TYPE                    = I_( "L" );
   const I_CHAR * const PRIF_TAX_TYPE                    = I_( "R" );  
   const I_CHAR * const LIF_TAX_TYPE                     = I_( "B" );
   const I_CHAR * const FAMILY_RESP_TAX_TYPE             = I_( "M" );
   const I_CHAR * const DPSP_TAX_TYPE                    = I_( "7" );
   const I_CHAR * const RPP_TAX_TYPE                     = I_( "8" );
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE         = I_( "9" ); 
   const I_CHAR * const LRSP_TAX_TYPE                    = I_( "U" ); 
   const I_CHAR * const RLIRA_TAX_TYPE                   = I_( "CR" ); 
   const I_CHAR * const RLIF_TAX_TYPE                    = I_( "BR" ); 
   const I_CHAR * const WILL_DEFIND_TAX_TYPE             = I_( "S" ); 
   const I_CHAR * const TFSA_TAX_TYPE                    = I_( "V" );
   const I_CHAR * const CLIENT_ACCT_DESIGNATION          = I_( "1" );
   const I_CHAR * const YES                              = I_( "Y" );
   const I_CHAR * const ACCOUNTHOLDER_ENTITY_TYPE        = I_( "01" );
   const I_CHAR * const SPOUSAL_ACCT_TYPE                = I_( "1" );
   const I_CHAR * const SPOUSAL_CONTRIBUTOR_ENTITY_TYPE  = I_( "06" );
   const I_CHAR * const HRDC_RELATECODE_UNCLE            = I_( "3" );
   const I_CHAR * const HRDC_RELATECODE_NOT_RELATED      = I_( "5" );
   const I_CHAR * const HRDC_RELATECODE_OTHER            = I_( "6" );

   const I_CHAR * const ADD_ENTITY                       = I_( "ADD_ENTITY" );
   const double dSmallValue                              = .0000000001;
   const I_CHAR * const YOUTH_POTFOLIO                   = I_( "YP" );
   const I_CHAR * OWNER_SPOUSAL                          = I_( "98" );

   const I_CHAR * const FUNDBROKER                       = I_( "01" );
   const I_CHAR * const UNASSIGNED_COUNTRY               = I_( "0000" );
   // ID Type
   const I_CHAR * const IDS_CLEARING_PLATFORM            = I_( "18" );

   const I_CHAR * const REF_CODE_TYPE_REGISTRATION_AGENT = I_( "01" );

   const I_CHAR * const TAX_TYPE_OA                      = I_( "OA" );
   const I_CHAR * const TAX_TYPE_SA                      = I_( "SA" );
   const I_CHAR * const TAX_TYPE_SRS                     = I_( "SR" );
   const I_CHAR * const NEW_COUNT_TAG                    = I_( "NewCountTag" );

   const I_CHAR * const CATEGORY_ESTATE                  = I_( "52" );
   const I_CHAR * const INDIVIDUAL_ACCOUNT_TYPE_LIST     = I_( "0,1,2" );
   const I_CHAR * const APPLICABLE_TO_ALL				 = I_( "*" );
   const I_CHAR * const RDSP_TAX_TYPE					 = I_( "RS" );
   const I_CHAR * const RDSP_BENEFICIARY				 = I_( "79" );
   const I_CHAR * const RDSP_PCG						 = I_( "80" );
   const I_CHAR * const ACCOUNTENTITY_CATEGORY           = I_( "8" );
   const I_CHAR * const ACCOUNTENTITY_LEVEL              = I_( "02" );
   const I_CHAR * const UNVERIFIED                       = I_("02");
   const I_CHAR * const VERIFIED                         = I_("01");
}

namespace ENTITY_CATEGORY
{
   extern const I_CHAR * const NOT_APPICABLE                 = I_( "00" );
   extern const I_CHAR * const INDIVIDUAL                    = I_( "01" );
   extern const I_CHAR * const CORPORATE                     = I_( "02" );
   extern const I_CHAR * const TRUST                         = I_( "03" );
}

namespace ACCOUNT_TYPE
{
   extern const I_CHAR * const CORPORATE;
}

namespace CND
{  // Conditions used
   extern const long ERR_DATA_NOT_FOUND;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_INVALID_RANGE_FOR_VALUE;
   extern const long ERR_NO_VALID_DECIMAL_VALUE;
   extern const long ERR_PERCENTAGE_NOT_EQUAL_100;
   extern const long ERR_TAX_TYPE_NO_NON_REGISTER;
   extern const long ERR_ANNUITANT_INVALID_FOR_ACCT_TYPE;
   extern const long ERR_SPOUSAL_INVALID_FOR_ACCT_TYPE;
   extern const long ERR_AVAILABLE_PERCENT_FOR_PRIMARY_BENEF;
   extern const long ERR_TRUSTEE_INVALID_FOR_ACCT_TYPE;
   extern const long ERR_INVALID_TAX_TYPE_FOR_RESP;
   extern const long ERR_DISPOSITION_NOT_UPDATABLE_FOR_ACCT_TYPE;
   extern const long ERR_JOINT_TYPE_NOT_UPDATABLE_FOR_ACCT_TYPE;
   extern const long ERR_RELATE_CODE_REQUIRED;
   extern const long ERR_NOMINEE_INVALID_FOR_ACCT_TYPE;
   extern const long ERR_BENEF_PERCENT_REQUIRED;
   extern const long ERR_IRREVOCABLE_NOT_UPDATABLE_FOR_ACCT_TYPE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_ESCROWFUND_ENTITY_TYPE;
   extern const long ERR_ESCROWFUND_CLASS;
   extern const long ERR_ESCROW_FUND_CLASS_BLANK;
   extern const long ERR_REASONCODE_RRSP_LOAN;
   extern const long ERR_REASONCODE_COLLATERAL;
   extern const long ERR_ESCROW_AMOUNT_TYPE;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_REASON_CODE_EMPTY;
   extern const long ERR_RELATE_CODE_EMPTY;
   extern const long ERR_FIELD_VAL_REQUIRED_PLS_SELECT;
   extern const long ERR_ESCROW_EFECTIVE_DATE_LESS_THAN_CURRENT_BUSSINES_DATE;
   extern const long ERR_AMOUNT_MUST_BE_ZERO_IF_ESCROW_REASON_CODE_IS_BANKRUPTCY;
   extern const long ERR_ENTITY_TYPE_EMPTY;

   extern const long ERR_WARN_CLIENT_BIRTHDAY_MISSING;
   extern const long ERR_CLIENT_AGE_BEYOND_ALLOW;
   extern const long ERR_ACCOUNT_OWNER_AGE_OVER_69;
   extern const long ERR_WARN_ACCOUNT_OWNER_AGE_OVER_69;
   extern const long ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING;
   extern const long ERR_WARN_SPOUSE_BIRTHDAY_MISSING;
   extern const long ERR_ENTITY_TYPE_ESCROW_NOT_PERMIT;
   extern const long ERR_WARN_ESCROW_UNITS_EXCESS_HOLDING;
   extern const long ERR_WARN_ESCROW_AMT_EXCESS_HOLDING;
   extern const long ERR_AMT_MUST_BE_ZERO_ESCROW_REASON_LOAN;
   extern const long ERR_FUND_CLASS_MUST_BOTH_BE_BLANK;
   extern const long ERR_FUND_CLASS_MUST_BLANK_FOR_BANKRUPTCY;
   extern const long ERR_WARN_PLANHOLDER_MINIMUM_AGE_LIMIT;
   extern const long ERR_PLANHOLDER_MAXIMUM_AGE_LIMIT;
   extern const long ERR_WARN_SHAREHOLDER_YOUNGER_THAN_18;
   extern const long ERR_WARN_ESCROW_AMT_EQUALS_HOLDING;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long WARN_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_RESP_BENEF_REASON_CANNOT_BE_MODIFIED;
   extern const long ERR_RESP_BENEF_REASON_MUST_BE_CURRENT_BENEF_FOR_NEW_ENTITY;
   extern const long ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING_NOCHECK;
   extern const long ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED;
   extern const long ERR_EFFECTIVE_DATE_MUST_BE_ENTERED;
   extern const long ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED;
   extern const long ERR_FUTURE_DATED_STOPDATE;
   extern const long ERR_INVALID_AGE;
   extern const long WARN_INVALID_AGE;
   extern const long WARN_DATE_OF_BIRTH_EMPTY;
   extern const long ERR_DATE_OF_BIRTH_REQUIRED;
   extern const long ERR_CLEARING_PLATFORM_MUST_BE_CORPORATE;
   extern const long ERR_CLEARING_PLATFORM_ID_TYPE_REQUIRED;
   extern const long ERR_CLEARING_PLATFORM_ID_VALUE_REQUIRED;
   extern const long ERR_PLANHOLDER_MINIMUM_AGE_LIMIT;
   extern const long ERR_BACKDATED_ENTITY_NOT_ALLOWED_FOR_RESP;
   extern const long ERR_SIN_DUPLIATE_WITH_OTHER_ACCOUNT_ENTITY;
   extern const long ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100;
   extern const long ERR_LANGUAGE_MUST_BE_ENTERED;
   extern const long ERR_ENITITY_NOT_ALLOWED_FOR_NON_RESP;
   extern const long ERR_ENITITY_NOT_ALLOWED_FOR_RESP_SIBLING_NOT_YES;
   extern const long ERR_ENTITY_BEING_LINKED_TO_OTHER_RESP_BENEF;
   extern const long ERR_DOB_RESP_BENEF_REQUIRED;
   extern const long ERR_INVALID_VALUE_FOR_PARENT_LEGAL_GUARDIAN;
   extern const long ERR_INVALID_VALUE_FOR_DESGN_INST;
   extern const long ERR_FUTURE_DATE_NOT_ALLOWED_FOR_RT511CUTOFF_DATE;
   extern const long ERR_TAX_JURIS_INVALID;
   extern const long WARN_DOB_RESP_BENEF_REQUIRED;
   extern const long ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long ERR_LETTER_REQUIRED_EMPTY;
   extern const long ERR_DELINK_PCG_WITH_RESP_BENEF_HAS_GRANT;
   extern const long ERR_NO_VALUE_FOR_ID;
   extern const long ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY;
   //QESI3FN03 - DOB,SIN
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   //IN2780013 - SOC Loan Number and Loan Type
   extern const long ERR_LOAN_NUM_MANDATORY;
   extern const long WARN_LOAN_NUM_MANDATORY;
   extern const long ERR_LOAN_TYPE_MANDATORY;
   extern const long WARN_LOAN_TYPE_MANDATORY;
   extern const long ERR_DUPLICATE_LOAN_TYPE;
   extern const long WARN_DUPLICATE_LOAN_TYPE;
   extern const long ERR_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT;
   extern const long WARN_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT;
   extern const long ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long ERR_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long WARN_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long ERR_W_SIN_IS_MISSING;
   extern const long ERR_E_SIN_IS_MISSING;
   extern const long ERR_W_INVALID_SIN;
   extern const long ERR_E_INVALID_SIN;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern const long WARN_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern const long ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern const long WARN_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern const long ERR_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern const long WARN_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern const long ERR_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS;
   extern const long WARN_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS;
   extern const long ERR_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE;
   extern const long WARN_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE;
   extern const long ERR_RDSP_BENEFICIARY_OVER_AGE_LIMIT;
   extern const long WARN_RDSP_BENEFICIARY_OVER_AGE_LIMIT;
   extern const long ERR_ACCTHOLDER_DOFBIRTH_MISSING;
   extern const long ERR_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED;
   extern const long WARN_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ESCROW;
   extern CLASS_IMPORT I_CHAR * const ESCROW_BAND;
   extern CLASS_IMPORT I_CHAR * const ASSIGNEE_ENTITY_TYPE_SETUP;
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY;
   extern CLASS_IMPORT I_CHAR * const RESP_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANTS_REQUEST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId BenDeff;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeE;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId AmountReason;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId EntityTypeDofB;
   extern CLASS_IMPORT const BFTextFieldId TitleRestrict;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFTextFieldId FromFundClass;
   extern CLASS_IMPORT const BFTextFieldId AmountPrecision;
   extern CLASS_IMPORT const BFTextFieldId SIN;
   extern CLASS_IMPORT const BFTextFieldId OwnerSpouseName;
   extern CLASS_IMPORT const BFNumericFieldId SpouseEntityID;
   extern CLASS_IMPORT const BFTextFieldId EntityWhereUseRelationship;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId AssigneeScreen;
   extern CLASS_IMPORT const BFTextFieldId JointDefaultDisposition;
   extern CLASS_IMPORT const BFTextFieldId OnLineEntExcept;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClass; //MT535/MT536
   extern CLASS_IMPORT const BFTextFieldId IdValue; //MT535/MT536
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFDateFieldId IdDate; //QESI3FN03
   extern CLASS_IMPORT const BFTextFieldId EmployeeClassXEntityType;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId QESIClient;
   extern CLASS_IMPORT const BFDecimalFieldId AllocationPercent; 
   extern CLASS_IMPORT const BFTextFieldId Gender; 
   extern CLASS_IMPORT const BFTextFieldId GrantRequest; 
   extern CLASS_IMPORT const BFTextFieldId Tainted; 
   extern CLASS_IMPORT const BFDateFieldId TaintEndDate; 
   extern CLASS_IMPORT const BFTextFieldId Rec400Sent;
   extern CLASS_IMPORT const BFTextFieldId CreateRec511;
   extern CLASS_IMPORT const BFDateFieldId Rec511CutOffDate;
   extern CLASS_IMPORT const BFTextFieldId LetterReq;
   extern CLASS_IMPORT const BFDateFieldId LetterDate; 
   extern CLASS_IMPORT const BFDecimalFieldId RESPPCGId;
   extern CLASS_IMPORT const BFTextFieldId RES2ParentLglList;
   extern CLASS_IMPORT const BFTextFieldId RES2DesInstList;
   extern CLASS_IMPORT const BFTextFieldId RES2PCGList;
   extern CLASS_IMPORT const BFTextFieldId CLBExists;
   extern CLASS_IMPORT const BFTextFieldId GrantExists;
   extern CLASS_IMPORT const BFTextFieldId PCGChange;
   extern CLASS_IMPORT const BFTextFieldId RESPBenefDeleted;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId CountryName;
   extern CLASS_IMPORT const BFDateFieldId CurrSysDate;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;//QESI3FN03
   extern CLASS_IMPORT const BFDateFieldId IdDate;
   extern CLASS_IMPORT const BFTextFieldId ValidRATaxType;
   extern CLASS_IMPORT const BFDecimalFieldId PercentOwner;
   extern CLASS_IMPORT const BFDecimalFieldId AssocEntityId;
   extern CLASS_IMPORT const BFTextFieldId CurrentSelectedEntityType;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClassForFATCA;
   extern CLASS_IMPORT const BFTextFieldId DepostitionDesc;
   extern CLASS_IMPORT const BFTextFieldId TOExistAfterPreElectReset;
   extern CLASS_IMPORT const BFTextFieldId CRSEntityList;
   extern CLASS_IMPORT const BFTextFieldId EntityAssociationAML;
   extern CLASS_IMPORT const BFTextFieldId NASUMode;
}

namespace IFASTERR
{
   // if order source is valid for account designation
   extern CLASS_IMPORT I_CHAR * const MIN_MAX_AGE;
   extern CLASS_IMPORT I_CHAR * const INVALID_SIN_FOR_RESP_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const BENEFICIARY_DOB_MISSING;
   extern CLASS_IMPORT I_CHAR * const BENEFICIARY_AGE_IS_OVER_21;
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_SIN; 
   //QESI3FN03 
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   //IN2780013 - SOC Loan Number and Loan Type
   extern CLASS_IMPORT I_CHAR * const LOAN_NUM_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const LOAN_TYPE_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_LOAN_TYPE;
   extern CLASS_IMPORT I_CHAR * const UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern CLASS_IMPORT I_CHAR * const TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE;
   extern CLASS_IMPORT I_CHAR * const RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL;
   extern CLASS_IMPORT I_CHAR * const TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION;
   extern CLASS_IMPORT I_CHAR * const PLANHOLDER_MINIMUM_AGE_LIMIT;
   extern CLASS_IMPORT I_CHAR * const ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS;
   extern CLASS_IMPORT I_CHAR * const FIRSTNAME_MANDATORY; 
   extern CLASS_IMPORT I_CHAR * const RDSP_BENEFICIARY_OVER_AGE_LIMIT;
   extern CLASS_IMPORT I_CHAR * const RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest WHERE_USED;
}

namespace IDS
{
   extern const I_CHAR * const SIN;
   extern const I_CHAR * const BUSINESS_NUMBER;
   extern const I_CHAR * const CLEARING_PLATFORM;
   extern const I_CHAR * const BIC_CODE;
   extern const I_CHAR * const TRUST_ACCOUNT_NUMBER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                 State Flags,            Group Flags 
   { ifds::AccountNum,           BFCBO::NONE,                 0 }, 
   { ifds::Salutation,           BFCBO::NONE,                 0 }, 
   { ifds::LastName,             BFCBO::REQUIRED,             0 }, 
   { ifds::FirstName,            BFCBO::NONE,                 0 }, 
   { ifds::SIN,                  BFCBO::NONE,                 0 }, 
   { ifds::EntityId,             BFCBO::REQUIRED,             0 }, 
   { ifds::EntityType,           BFCBO::REQUIRED,             0 }, 
   { ifds::SeqNumber,            BFCBO::REQUIRED,             0 }, 
   { ifds::RelateCode,           BFCBO::NONE,                 0 }, 
   { ifds::AddrCode,             BFCBO::NONE,                 0 }, 
   { ifds::AuthorizedToTrade,    BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,        BFCBO::NONE,                 0 }, 
   { ifds::ProcessDate,          BFCBO::NONE,                 0 }, 
   { ifds::BenPercentage,        BFCBO::NONE,                 0 }, 
   { ifds::Irrevocable,          BFCBO::NONE,                 0 }, 
   { ifds::DepositionCode,       BFCBO::NONE,                 0 }, 
   { ifds::JointType,            BFCBO::NONE,                 0 }, 
   { ifds::JointTypeDesc,        BFCBO::NONE,                 0 }, 
   { ifds::EscrowFund,           BFCBO::NONE,                 0 }, 
   { ifds::EscrowClass,          BFCBO::NONE,                 0 }, 
   { ifds::AmtAssigned,          BFCBO::NONE,                 0 }, 
   { ifds::AmountType,           BFCBO::NONE,                 0 }, 
   { ifds::AmountTypeDesc,       BFCBO::NONE,                 0 }, 
   { ifds::ReasonCode,           BFCBO::NONE,                 0 }, 
   { ifds::ReasonDesc,           BFCBO::NONE,                 0 }, 
   { ifds::EscrowDeff,           BFCBO::NONE,                 0 }, 
   { ifds::EscrowStopDate,       BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityVer,        BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityRid,        BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityBenefVer,   BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityBenefRid,   BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityJointVer,   BFCBO::NONE,                 0 }, 
   { ifds::AcctEntityJointRid,   BFCBO::NONE,                 0 }, 
   { ifds::AssignDetlVer,        BFCBO::NONE,                 0 }, 
   { ifds::AssignDetlRid,        BFCBO::NONE,                 0 }, 
   { ifds::HRDCRelateCode,       BFCBO::NONE,                 0 }, 
   { ifds::HRDCRelateDesc,       BFCBO::NONE,                 0 }, 
   { ifds::RESPReasonCode,       BFCBO::NONE,                 0 }, 
   { ifds::RESPReasonDesc,       BFCBO::NONE,                 0 }, 
   //{ ifds::AllocationPercent,  BFCBO::NONE,                 0 }, 
   { ifds::GrantRequest,         BFCBO::NONE,                 0 }, 
   { ifds::Tainted,              BFCBO::NONE,                 0 }, 
   { ifds::TaintEndDate,         BFCBO::NONE,                 0 }, 
   { ifds::CreateRec511,         BFCBO::NONE,                 0 }, 
   { ifds::Rec511CutOffDate,     BFCBO::NONE,                 0 },
   { ifds::LetterReq,            BFCBO::NONE,                 0 }, 
   { ifds::LetterDate,           BFCBO::NONE,                 0 },
   { ifds::BenDeff,              BFCBO::NONE,                 0 }, 
   { ifds::RESPPCGId,            BFCBO::NONE,                 0 },
   { ifds::FrFundNumber,         BFCBO::NONE,                 0 }, 
   { ifds::FundClass,            BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::RESPParentSeq,        BFCBO::NONE,                 0 }, 
   { ifds::RESPDesInstSeq,       BFCBO::NONE,                 0 },
   { ifds::RES2ParentLglList,    BFCBO::NONE,                 0 },
   { ifds::RES2DesInstList,      BFCBO::NONE,                 0 },
   { ifds::RES2PCGList,          BFCBO::NONE,                 0 },
   { ifds::CLBExists,            BFCBO::NONE,                 0 },
   { ifds::GrantExists,          BFCBO::NONE,                 0 },
   { ifds::EffectiveStopDate,    BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::AmountReason,         BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::TaxJurisCode,         BFCBO::NONE,                 0 }, 
   { ifds::DofBirth,             BFCBO::NONE,                 0 }, 
   { ifds::EntityTypeDofB,       BFCBO::NONE,                 0 }, 
   { ifds::FromFundClass,        BFCBO::NONE,                 0 }, 
   { ifds::AmountPrecision,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::OwnerSpouseName,      BFCBO::NONE,                 0 }, 

   { ifds::Username,             BFCBO::NONE,                 0 }, 
   { ifds::EntityTypeDesc,       BFCBO::NONE,                 0 }, 
   { ifds::RelateCodeShip,       BFCBO::NONE,                 0 }, 
   { ifds::ModDate,              BFCBO::NONE,                 0 }, 
   { ifds::ModUser,              BFCBO::NONE,                 0 }, 
   { ifds::EmployeeClass,        BFCBO::NONE,                 0 },
   { ifds::EmployeeClassXEntityType, BFCBO::IMMEDIATE_VALIDATION,0 }, //MT535/MT536
   { ifds::TaxJuris,             BFCBO::NONE,                0 },
   { ifds::CountryCode,          BFCBO::NONE,                0 },
   { ifds::CountryName,          BFCBO::NONE,                0 },
   { ifds::RESPBenefInfoRid,     BFCBO::NONE,                0 },
   { ifds::RESPBenefInfoVer,     BFCBO::NONE,                0 },
   { ifds::TradeExists,          BFCBO::NONE,                0 },
   { ifds::Rec400Sent,           BFCBO::NONE,                0 },
   { ifds::DeathSettlementDate,  BFCBO::NONE,                0 },
   { ifds::LoanType,             BFCBO::NONE,                0 },  //IN2780013 - SOC Loan Number and Loan Type
   { ifds::LoanNumber,           BFCBO::NONE,                0 }, 
   { ifds::RefCode,              BFCBO::NONE,                0 }, 
   { ifds::RefType,              BFCBO::NONE,                0 }, 
   { ifds::ValidRATaxType,       BFCBO::NONE,                0 }, 
   { ifds::TFSALastAmendTaxYear, BFCBO::NONE,                0 }, 
   { ifds::AssocEntityId,        BFCBO::NONE,                0 },
   { ifds::PercentOwner,         BFCBO::NONE,                0 },
   { ifds::EmployeeClassForFATCA,BFCBO::NOT_ON_HOST,         0 },
   { ifds::DepostitionDesc,      BFCBO::NONE,				 0 },
   { ifds::EntityAssociation,    BFCBO::NONE,                0 },
   { ifds::RDSPRelntoBene,		 BFCBO::NONE,                0 },
   { ifds::RDSPConsent,			 BFCBO::NONE,                0 },
   { ifds::RDSPConsentDeff,		 BFCBO::NONE,                0 },
   { ifds::NASUMode,			 BFCBO::NONE,                0 },
   { ifds::VerifyStat,           BFCBO::NONE,                0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

struct _entityIDSeqOrder
{
   DString strEntityID;
   DString strEntitySeq;
};

typedef std::vector<_entityIDSeqOrder> vEntityIDSeqOrder;

//******************************************************************************
bool AccountEntityXrefObject::sortByEntityID(const _entityIDSeqOrder& input1, 
                                             const _entityIDSeqOrder& input2)
{
   DString strEntityID1 = input1.strEntityID;
   DString strEntityID2 = input2.strEntityID;
   strEntityID1.strip();
   strEntityID2.strip();

   I_CHAR *stopstring;

   unsigned int iEntityID1 = (unsigned int)wcstod( strEntityID1.c_str(), &stopstring );
   unsigned int iEntityID2 = (unsigned int)wcstod( strEntityID2.c_str(), &stopstring );

   if( iEntityID1 <= iEntityID2 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//******************************************************************************
AccountEntityXrefObject::AccountEntityXrefObject( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pErrMsgRulesList(NULL),_iCountNum(0),
_dstrVerifyFilter (NULL_STRING),
_bIsDirty (false),
_bVerificationEnabled (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   _pResponseData = NULL;

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
// following for Canadian
   addCrossEdit(ifds::FundClass, ifds::EscrowFund);
   addCrossEdit(ifds::FundClass, ifds::EscrowClass);

   addCrossEdit(ifds::FromFundClass, ifds::EscrowFund);
   addCrossEdit(ifds::FromFundClass, ifds::EscrowClass);

   addCrossEdit(ifds::EffectiveStopDate, ifds::EscrowDeff);
   addCrossEdit(ifds::EffectiveStopDate, ifds::EscrowStopDate);

   addCrossEdit(ifds::AmountReason, ifds::AmtAssigned );
   addCrossEdit(ifds::AmountReason, ifds::ReasonCode );

   addCrossEdit(ifds::EntityTypeDofB, ifds::EntityType );
   addCrossEdit(ifds::EntityTypeDofB, ifds::DofBirth );

   addCrossEdit(ifds::AmountPrecision, ifds::AmtAssigned);   //Trans type, FromFund and FromClass
   addCrossEdit(ifds::AmountPrecision, ifds::AmountType);  
   addCrossEdit(ifds::AmountPrecision, ifds::EscrowFund); 
   addCrossEdit(ifds::AmountPrecision, ifds::EscrowClass);

   addCrossEdit(ifds::EmployeeClassXEntityType, ifds::EmployeeClass );
   addCrossEdit(ifds::EmployeeClassXEntityType, ifds::EntityType );
}

//******************************************************************************
AccountEntityXrefObject::~AccountEntityXrefObject()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pResponseData )
      delete _pResponseData;
}

//******************************************************************************
void AccountEntityXrefObject::setInitialStrKey (const DString& strKey)
{
   objectKey = strKey;
}

//*******************************************************************************
SEVERITY AccountEntityXrefObject::init (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::init( const DString& strKey, 
                                        const BFData& data, 
                                        bool flg_where_used,
                                        bool bRefresh, 
                                        bool baseDelete)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
   if (bRefresh)
   {
      clearFieldMap ();
      eraseDataObjectContainers ();
   }

   objectKey = strKey;
   attachDataObject (const_cast <BFData&> ( data ), baseDelete);
   
   DString taxType;

   if (!flg_where_used)
   {
      Entity *pEntity;
      
      getWorkSession().PopulateEntity (BF::HOST, data, pEntity);

	  MFAccount *pMFAccount = NULL;
	  DString strAccountNum;
      getField( ifds::AccountNum, strAccountNum, BF::HOST, true );

      if( !strAccountNum.empty() && 
         getWorkSession().getMFAccount (BF::HOST, strAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
      {
         pMFAccount->getField( ifds::TaxType, taxType, BF::HOST, false );
      }
   }
   else if (flg_where_used)
   {
      DString _WhereUsedType;
      
      data.getElementValue (ifds::WhereUse, _WhereUsedType);
      if (_WhereUsedType == FUNDBROKER)
      {
         setFieldSubstituteValues (ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      }

	  taxType = data.getElementValue(ifds::TaxType);
   }

   taxType.strip();
   if(taxType == TAX_TYPE_OA || taxType == TAX_TYPE_SA || taxType == TAX_TYPE_SRS)
   {
      getField( ifds::TaxType, taxType, BF::HOST, false );
   }
   initDefaultValues (BF::HOST, taxType);

   DString strEntityType = data.getElementValue( ifds::EntityType );
   strEntityType.strip().upperCase();

   if ( strEntityType == RESP_PCG_INDIV  || strEntityType == RESP_PCG_INST ||
        strEntityType == PARENT_GUARDIAN || strEntityType == RESP_DSGN_INST)
   {
      AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
      pAccountEntityXref->setRESPSelectableFieldSubSet(strEntityType,NULL_STRING,BF::HOST);      
   }
   
   if( strEntityType == PRIMARY_BENEFICARY || strEntityType == SECONDARY_BENEFICARY || 
       strEntityType == RESP_BENEFICIARY )
   {
      setFieldReadOnly( ifds::DeathSettlementDate, BF::HOST, false );
   }
   else
   {
      setFieldReadOnly( ifds::DeathSettlementDate, BF::HOST, true );
   }

   if ( strEntityType == ENTITY_TYPE_REG_AGENT)
   {
      setFieldRequired( ifds::RefCode, BF::HOST, true );
   }
   else
   {
      setFieldRequired( ifds::RefCode, BF::HOST, false);
   }

   DString dstrCRSEntityList;
   getWorkSession().getOption ( ifds::CRSEntityList, dstrCRSEntityList, BF::HOST, false); 
	
   if (strEntityType != ACCOUNT_OWNER && (DSTCommonFunctions::codeInList(strEntityType, dstrCRSEntityList) || dstrCRSEntityList == APPLICABLE_TO_ALL || strEntityType == RELATED_PARTY_AML_ENTITY_TYPE))
   {
	   bool bRequired = (strEntityType == RELATED_PARTY);
       setFieldRequired(ifds::AssocEntityId, BF::HOST, bRequired);
       setFieldRequired(ifds::PercentOwner, BF::HOST, bRequired);

       DString dstrAssociateEntitySubList;
       AccountEntityXref *pAccountEntityXref = dynamic_cast<AccountEntityXref*>(getParent());

       pAccountEntityXref->getAssociateEntitySubList(dstrAssociateEntitySubList, BF::HOST, NULL_STRING, NULL_STRING);
       setFieldAllSubstituteValues(ifds::AssocEntityId, BF::HOST, dstrAssociateEntitySubList);
   }
   else
   {
       setFieldRequired(ifds::AssocEntityId, BF::HOST, false);
       setFieldRequired(ifds::PercentOwner, BF::HOST, false);
   }

   setEntityAssociationSubstitutions(BF::HOST);

   if(flg_where_used)
   {
      updateRegistrationAgentSubstitution(BF::HOST, taxType);
   }   

   loadRDSPRelntoBeneSetSubstList(BF::HOST, taxType);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
const DString * AccountEntityXrefObject::getInitialStrKey ()
{
   return(&objectKey);
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::doValidateAll (const BFDataGroupId& idDataGroup, 
                                                 long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   SEVERITY SvrRet = NO_CONDITION;
   SvrRet = validateEntityTypeDofB( idDataGroup );

   DString entityId;
   getField( ifds::EntityId, entityId, idDataGroup );

   Entity *pEntity;
   getWorkSession().getEntity( idDataGroup, entityId, pEntity );
   if( pEntity )
   {
       DString dstrEntityType;
       getField(ifds::EntityType, dstrEntityType, idDataGroup);
       pEntity->setField(ifds::CurrentSelectedEntityType, dstrEntityType, idDataGroup);

       pEntity->validateAll( idDataGroup );
   }

   DString dstrEntityType, percent;
   getField( ifds::EntityType, dstrEntityType, idDataGroup );

   if( pEntity && dstrEntityType == ACCOUNT_OWNER)
   {
      pEntity->validateMandatedIDforCPFTaxTypes(idDataGroup);
   }

   if( dstrEntityType == PRIMARY_BENEFICARY || dstrEntityType == SECONDARY_BENEFICARY )
   {
      getField( ifds::BenPercentage, percent, idDataGroup );
      AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
      if( pAccountEntityXref )
      {
         if( !( pAccountEntityXref->getAvailablePercentForBenef( dstrEntityType, percent, idDataGroup ) 
                || convertToULong( percent ) == 0L ) )
            ADDCONDITIONFROMFILE( CND::ERR_AVAILABLE_PERCENT_FOR_PRIMARY_BENEF );
      }
   }
   else if (dstrEntityType == RESP_BENEFICIARY)
   {
      validateIDForRESPEntity (IDS::SIN, idDataGroup);
      validateRESPBenefAlloc (idDataGroup);
      validatePCGList (idDataGroup );
   }
   else if (dstrEntityType == RESP_PCG_INST)
   {
      validateIDForRESPEntity (IDS::BUSINESS_NUMBER, idDataGroup);
   }
   else if (dstrEntityType == ACCOUNT_OWNER || dstrEntityType == RDSP_PCG || dstrEntityType == RDSP_BENEFICIARY)
   {
	   DString dstrAcctNum, dstrTaxType, dstrEmployeeClass, dstrRDSPRelntoBene;

	   getField( ifds::AccountNum, dstrAcctNum, idDataGroup, true );
	   MFAccount *pMFAccount = NULL;

	   if( !dstrAcctNum.empty() && 
		   getWorkSession().getMFAccount (idDataGroup, dstrAcctNum, pMFAccount) <= WARNING && 
		   pMFAccount)
	   {
		   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
		   dstrTaxType.strip().upperCase();
	   }

	   pEntity->getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false);

	   if (dstrTaxType == RDSP_TAX_TYPE)
	   {
		   if (dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE)
			   validateIDForRESPEntity (IDS::BUSINESS_NUMBER, idDataGroup);
		   else
			   validateIDForRESPEntity (IDS::SIN, idDataGroup);

		   if (dstrEntityType == ACCOUNT_OWNER)
		   {
			   getField (ifds::RDSPRelntoBene, dstrRDSPRelntoBene, idDataGroup, false);
			   
			   if (dstrRDSPRelntoBene.stripAll().empty())
			   {
				   // 2116 - Relationship between Accountholder and RDSP Beneficiary must be specified.  
				   getErrMsg (IFASTERR::RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED,
							  CND::ERR_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED,
							  CND::WARN_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED,
							  idDataGroup);
			   }
		   }
	   }
   }
   if (isFieldUpdated( ifds::RESPReasonCode, idDataGroup ) && !isNew())
   {
      ADDCONDITIONFROMFILE( CND::ERR_RESP_BENEF_REASON_CANNOT_BE_MODIFIED );	
   }

   if( ( dstrEntityType == ESCROW_REPRESENTATIVE ) && isUpdated( true ) &&
         !getWorkSession().hasUpdatePermission( UAF::ESCROW_BAND ))
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED );
   }

   if( ( dstrEntityType == ASSIGNEE ) && isUpdated( true ) &&
         !getWorkSession().hasUpdatePermission( UAF::ASSIGNEE_ENTITY_TYPE_SETUP ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED );
   }

   if (dstrEntityType == CLEARING_PLATFORM)
   {
      validateEntityIDForClearingPlatformEntity (idDataGroup);
   }

   validateTaxJurisForRESP( idDataGroup );
   validateClearingPlatform( idDataGroup );
   validateLoanTypeLoanNumberForEscrow(idDataGroup );//IN2780013 - SOC Loan Number and Loan Type

   if( dstrEntityType == ENTITY_TYPE_REG_AGENT && isNew() )
   {
	   validateAcctRegAgent( idDataGroup );
   }

   DString dstrFirstname, entityTypeDesc;
   getField(ifds::FirstName, dstrFirstname, idDataGroup, false);
   getField(ifds::EntityType, entityTypeDesc, idDataGroup, true);

   if (!entityTypeDesc.empty() && dstrEntityType == RELATED_PARTY_AML_ENTITY_TYPE && dstrFirstname.stripAll().empty())
   {
       DString idiStr;
       addIDITagValue(idiStr, I_("ENTITY_TYPE"), entityTypeDesc);

       getErrMsg(IFASTERR::FIRSTNAME_MANDATORY,
                 CND::ERR_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE,
                 CND::WARN_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE,
                 idDataGroup,
                 idiStr);
   }

   validateTaxJurisForRDSP( idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::doValidateField  ( const BFFieldId& idField, 
                                                     const DString& strValue, 
                                                     const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   DString taxType, accType, accDesignation, entityType;
   SEVERITY sevRtn = NO_CONDITION;

   if( idField == ifds::EntityType )
   {
      if( strValue == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_EMPTY );
      }
      else if( strValue == ACCOUNT_OWNER )
      {
      }
      else if( strValue == ESCROW_REPRESENTATIVE ) // || strValue == ASSIGNEE )
      {

         bool bPermit =  getWorkSession().hasCreatePermission( UAF::ESCROW_BAND ) && 
                         getWorkSession().hasCreatePermission( UAF::ESCROW );
         if( !bPermit )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_ESCROW_NOT_PERMIT );
         }
      }
      else if ( strValue == ASSIGNEE )
      {
         bool bPermit =  getWorkSession().hasCreatePermission( UAF::ASSIGNEE_ENTITY_TYPE_SETUP );
         DString dstrAssignee;

         getWorkSession ().getOption( ifds::AssigneeScreen, dstrAssignee, idDataGroup, false);

         if ( !bPermit || dstrAssignee != I_("Y"))
         {
            ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED );
         }
      }
      else if( strValue == ANNUITANT && idDataGroup != BF::HOST )
      {
         DString accNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::TaxType, taxType, idDataGroup );
            DString dstrSegClient, dstrCotClient;
            
            getWorkSession().getOption (ifds::SegClient, dstrSegClient, BF::HOST);
            getWorkSession().getOption (ifds::CotClient, dstrCotClient, BF::HOST);

            bool isSegClient = ( dstrSegClient.strip() == YES && dstrCotClient.strip() == YES );
            
            if ( !isSegClient && !getWorkSession().isNonRegLike( taxType ) )
               ADDCONDITIONFROMFILE( CND::ERR_ANNUITANT_INVALID_FOR_ACCT_TYPE );
         }
      }
      else if( strValue == SPOUSAL_CONTRIBUTOR && idDataGroup != BF::HOST )
      {
         DString accNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::AcctType, accType, idDataGroup );
            if( accType != SPOUSAL_ACCOUNT )
               ADDCONDITIONFROMFILE( CND::ERR_SPOUSAL_INVALID_FOR_ACCT_TYPE );
         }
      }
      else if( strValue == PRIMARY_BENEFICARY )
      {
      }
      else if( strValue == SECONDARY_BENEFICARY )
      {
         // Move below code to the doValidateAll(). The reason to do that is because it rise an error 
         // message which always complains the percentage of the first benificiary being wrong 
         // when a secondary beneficary is added even though the first benificiary without any problem.
         // this problem hapens when TaxType field is set in the LinkEntity() function call.
         /*  AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
           if( pAccountEntityXref )
           {
              DString percent;
              if( !( pAccountEntityXref->getAvailablePercentForBenef( PRIMARY_BENEFICARY, percent, idDataGroup ) 
                     && convertToULong( percent ) == 0L ) )
                 ADDCONDITIONFROMFILE( CND::ERR_AVAILABLE_PERCENT_FOR_PRIMARY_BENEF );
           }*/
      }
      else if( strValue == SUCCESSOR ) //CAN
      {
      }
      else if( strValue == TRUSTEE && idDataGroup != BF::HOST )
      {
         DString accNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::AcctType, accType, idDataGroup );
            if( accType != TRUST )
               ADDCONDITIONFROMFILE( CND::ERR_TRUSTEE_INVALID_FOR_ACCT_TYPE );
         }
      }
      else if( strValue == NOMINEE_OWNER && idDataGroup != BF::HOST )
      {
         DString strAccountNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, strAccountNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount ) <= WARNING )
         {
            DString dstrOnLineEntExcept;
            getWorkSession().getOption (ifds::OnLineEntExcept, dstrOnLineEntExcept, BF::HOST, false);

            if ( DSTCommonFunctions::codeInList(strValue,dstrOnLineEntExcept) == false )
            {
               pMFAccount->getField( ifds::AcctDesignation, accDesignation, idDataGroup );
               if( accDesignation != NOMINEE && accDesignation != INTERMEDIAR )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_NOMINEE_INVALID_FOR_ACCT_TYPE );
               }
            }
         }
      }
      else if( strValue == RESP_BENEFICIARY && idDataGroup != BF::HOST ) //CANADIAN CHANGES; 
      {
         // Skip validation when the group ID = HOST, this is to fix the error in LINKENTITY method
         DString accNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         accNum.strip().stripLeading( '0' );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::TaxType, taxType, idDataGroup );
            if( taxType != RESP && taxType != FAMILY_PLAN_RESP )
               ADDCONDITIONFROMFILE( CND::ERR_INVALID_TAX_TYPE_FOR_RESP );
         }
      }

      if(strValue == RESP_BENEFICIARY || strValue == ACCOUNT_OWNER)
      {
         validateSINDuplicateForRESP( idDataGroup );
      }
      else if ( strValue == RESP_PCG_INDIV && idDataGroup != BF::HOST )
      {
         validateIDForRESPEntity( IDS::SIN, idDataGroup);
      }
      //else if ( strValue == RESP_PCG_INST && idDataGroup != BF::HOST )
      //{
      //   validateIDForRESPEntity( IDS::BUSINESS_NUMBER, idDataGroup);
      //}
      else if (strValue == CLEARING_PLATFORM)
      {
         validateEntityIDForClearingPlatformEntity (idDataGroup);
      }
      else if( strValue == ESTATE_OF_DECEASED && idDataGroup != BF::HOST )
      {
         DString accNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            AcctCategoryList *pAcctCategoryList (NULL);
            if ( pMFAccount->getAcctCategoryList (pAcctCategoryList, idDataGroup) <= WARNING && 
                 pAcctCategoryList )
            {
               if( !pAcctCategoryList->isCategoryExist( idDataGroup, CATEGORY_ESTATE ))
               {
                  getErrMsg( IFASTERR::UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT, 
                             CND::ERR_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT, 
                             CND::WARN_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT,
                             idDataGroup ); 
               }
            }
         }
      }
      else if (strValue == JOINT_LIFE)
      {
         validateEntityTypeAgainstElectResetEvent(idDataGroup);
      }
   }
   else if( idField == ifds::DepositionCode && idDataGroup != BF::HOST )
   {
      DString accNum;
      MFAccount *pMFAccount = NULL;

      getField( ifds::AccountNum, accNum, idDataGroup, true );
      if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
      {
         pMFAccount->getField( ifds::AcctType, accType, idDataGroup );
         getField( ifds::EntityType, entityType, idDataGroup );
         if( accType == JOINT && entityType == ACCOUNT_OWNER && strValue == NULL_STRING )
            ADDCONDITIONFROMFILE( CND::ERR_DISPOSITION_NOT_UPDATABLE_FOR_ACCT_TYPE );
      }
   }
   else if( idField == ifds::JointType && idDataGroup != BF::HOST )
   {
      DString accNum;
      MFAccount *pMFAccount = NULL;

      getField( ifds::AccountNum, accNum, idDataGroup, true );
      if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
      {
         pMFAccount->getField( ifds::AcctType, accType, idDataGroup );
         if( accType == JOINT && entityType == ACCOUNT_OWNER && strValue == NULL_STRING )
            ADDCONDITIONFROMFILE( CND::ERR_JOINT_TYPE_NOT_UPDATABLE_FOR_ACCT_TYPE );
      }
   }
   else if( idField == ifds::RelateCode )
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if( ( entityType == PRIMARY_BENEFICARY || entityType == SECONDARY_BENEFICARY || entityType == SUCCESSOR ) && strValue == NULL_STRING )
         ADDCONDITIONFROMFILE( CND::ERR_RELATE_CODE_REQUIRED );
   }
   else if( idField == ifds::BenPercentage )
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if( entityType == PRIMARY_BENEFICARY || entityType == SECONDARY_BENEFICARY )
      {
         if( strValue == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_BENEF_PERCENT_REQUIRED );
         }
         else
         {
            long val;

            bool isDec = isDecimal( strValue );

            if( isDec )
            {
               val = convertToULong( strValue );
               if( val > 100 || val <= 0 )
                  ADDCONDITIONFROMFILE( CND::ERR_INVALID_RANGE_FOR_VALUE );
            }
            else
               ADDCONDITIONFROMFILE( CND::ERR_NO_VALID_DECIMAL_VALUE );
         }
      }
      else if ( entityType == RESP_BENEFICIARY )
      {
         // validate the NULL_STRING and RANGE of allocation percent
         if( strValue == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_BENEF_PERCENT_REQUIRED );
         }
         else
         {
            double val;

            bool isDec = isDecimal( strValue );

            if( isDec )
            {
               val = DSTCommonFunctions::convertToDouble(strValue);
               // not validate equal zero because Percentage for RESP Ben that older than 21 can be zero
               if( val > 100 || val < 0 )
                  ADDCONDITIONFROMFILE( CND::ERR_INVALID_RANGE_FOR_VALUE );
            }
            else
               ADDCONDITIONFROMFILE( CND::ERR_NO_VALID_DECIMAL_VALUE );
         }
      }

      //validateRESPBenefAlloc(strValue, idDataGroup);
   }
   else if( idField == ifds::Irrevocable )
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if( ( entityType ==PRIMARY_BENEFICARY || entityType == SECONDARY_BENEFICARY ) && strValue == NULL_STRING )
         ADDCONDITIONFROMFILE( CND::ERR_IRREVOCABLE_NOT_UPDATABLE_FOR_ACCT_TYPE );
   }
   else if( idField == ifds::FrFundNumber )
   {
      validateFundNumber(idDataGroup);
   }
   else if( idField == ifds::FundClass )
   {
      validateFundClass( idDataGroup );
   }
   else if( idField == ifds::FromFundClass )
   {
      validateEscrowFundClass( idDataGroup );
   }

   else if( idField == ifds::AmountType )
   {
      validateAmountType(strValue,idDataGroup);

      DString dstrAmtType (strValue);
      dstrAmtType.strip().upperCase();

      /*DString dstrAmt;
      getField( ifds::AmtAssigned, dstrAmt, idDataGroup );
      
      sevRtn = validateAmtExcessBalance ( dstrAmt, dstrAmtType, idDataGroup );*/
   }
   else if( idField ==  ifds::AmtAssigned )
   {
      DString dstrAmtType;
      getField( ifds::AmountType, dstrAmtType, idDataGroup );
      if( dstrAmtType.strip().upperCase() != NULL_STRING )
      {
         validateAmountType( dstrAmtType,idDataGroup);  
      }

      //sevRtn = validateAmtExcessBalance ( strValue, dstrAmtType, idDataGroup );
   }
   if( idField ==  ifds::AmountPrecision )
   {
      DString dstrAmt, dstrAmtType;
      getField( ifds::AmtAssigned, dstrAmt, idDataGroup );
      getField( ifds::AmountType, dstrAmtType, idDataGroup );

      sevRtn = validateAmtExcessBalance ( dstrAmt, dstrAmtType.strip().upperCase(), idDataGroup );
   }
   else if( idField == ifds::EffectiveStopDate )
   {
      validateEffectiveStopDate(idDataGroup);
   }
   else if( idField == ifds::EscrowDeff )
   {
      if (strValue.empty ())
      {
         ADDCONDITIONFROMFILE (CND::ERR_EFFECTIVE_DATE_MUST_BE_ENTERED);
      }
      else
      {
         // Rule: Edit check on the Escrow Effective Date is required. User cannot enter a date 
         //    that is earlier than the current business date.

         DString strEscrowEffectiveDate;
         getField(ifds::EscrowDeff, strEscrowEffectiveDate, idDataGroup, false);

         DString strCurrBussinesDate;
         if( getWorkSession().getOption( ifds::CurrBusDate, strCurrBussinesDate, idDataGroup, false ) <= WARNING )
         {
            if( DSTCommonFunctions::CompareDates( strEscrowEffectiveDate, strCurrBussinesDate ) == DSTCommonFunctions::FIRST_EARLIER )
            {
               ADDCONDITIONFROMFILE( CND::ERR_ESCROW_EFECTIVE_DATE_LESS_THAN_CURRENT_BUSSINES_DATE );
   //###       !!! don't show the yellow box message, only the red circle
               // The reason why yellow box message did not show is because you (don't know who)
               // put this validation logic in doApplyrelatedChange :)
            }
         }
      }
   }

   else if (idField == ifds::EscrowStopDate)
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if (entityType == ASSIGNEE || entityType == ESCROW_REPRESENTATIVE )
      {
         DString dstrEscrowStopDate,dstrDefStopDate,dstrCurrBussinesDate;

         DSTCommonFunctions::getFormat12319999Date(dstrDefStopDate);
         getField (ifds::EscrowStopDate, dstrEscrowStopDate, idDataGroup, false);

         if( getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false ) <= WARNING )
         {
            if (!dstrEscrowStopDate.empty () && 
                !DSTCommonFunctions::CompareDates (dstrEscrowStopDate, dstrDefStopDate)== 
                 DSTCommonFunctions::EQUAL)
            {
               if (DSTCommonFunctions::CompareDates (dstrCurrBussinesDate, dstrEscrowStopDate)==  
                   DSTCommonFunctions::FIRST_EARLIER)
                  ADDCONDITIONFROMFILE (CND::ERR_FUTURE_DATED_STOPDATE);
            }
         }
      }
   }

   else if( idField == ifds::ReasonCode )
   {
      validateReasonCode(strValue,idDataGroup);
   }
   else if( idField == ifds::RESPReasonCode )
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if( entityType == RESP_BENEFICIARY )
      {
         DString copyVal(strValue);
         if( copyVal.strip() == NULL_STRING )
            ADDCONDITIONFROMFILE( CND::ERR_REASON_CODE_EMPTY );	

         if ( isNew() &&
            I_( "00" ) != copyVal.strip() )
         {
            ADDCONDITIONFROMFILE( CND::ERR_RESP_BENEF_REASON_MUST_BE_CURRENT_BENEF_FOR_NEW_ENTITY );	
         }
      }
   }
   else if( idField == ifds::HRDCRelateCode )
   {
      getField( ifds::EntityType, entityType, idDataGroup );
      if( entityType == RESP_BENEFICIARY )
      {
         DString copyVal(strValue);
         if( copyVal.strip() == NULL_STRING )
         {
            //ADDCONDITIONFROMFILE( CND::ERR_RELATE_CODE_EMPTY );
            ADDCONDITIONFROMFILE( CND::ERR_FIELD_VAL_REQUIRED_PLS_SELECT );
         }
      }
   }
   else if( idField == ifds::AmountReason )
   {
      validateAmountReason( idDataGroup );
   }
   else if( idField == ifds::EntityTypeDofB )
   {
      validateEntityTypeDofB( idDataGroup );
   }
   // ifds::LastName will always be required, should not be controled by the error number.   
   else if( idField == ifds::EmployeeClassXEntityType)
   {
      DString entityId;

      getField (ifds::EntityId, entityId, idDataGroup);
      if (!entityId.empty())
      {
         Entity* pEntity (NULL);
         if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
             pEntity)
         {

            DString strEmployeeClass,
                  strEntityType;

            pEntity->getField (ifds::EmployeeClass, strEmployeeClass, idDataGroup, false);
            getField (ifds::EntityType, strEntityType, idDataGroup, false);

            if (strEntityType == CLEARING_PLATFORM)
            {
               if(!strEmployeeClass.empty() && strEmployeeClass != ENTITY_CATEGORY::CORPORATE)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_CLEARING_PLATFORM_MUST_BE_CORPORATE);
               }
            }

            if (strEntityType == RELATED_PARTY && strEmployeeClass != ENTITY_CATEGORY::INDIVIDUAL)
            {
                getErrMsg(IFASTERR::RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL, 
                          CND::ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL, 
                          CND::WARN_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL,
                          idDataGroup);
            }
         }
      }
   }
   else if (idField == ifds::EmployeeClassForFATCA)
   {
       //Validation of this field is in Entity.
       DString entityId;

       getField (ifds::EntityId, entityId, idDataGroup);

       if (!entityId.empty())
       {
           Entity* pEntity (NULL);
           if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
               pEntity)
           {

               DString strEmployeeClass,
                   strEntityType;

               pEntity->getField (ifds::EmployeeClass, strEmployeeClass, idDataGroup, false);
               getField (ifds::EntityType, strEntityType, idDataGroup, false);

               pEntity->validateEmployeeClassForFATCA(idDataGroup, strEntityType);
           }
       }
   }
   else if ( idField ==  ifds::SIN)
   {

   }
   else if (idField == ifds::EffectiveDate)
   {
   }
   else if (idField == ifds::RES2PCGList)
   {
      DString strEntityType;
      
      getField (ifds::EntityType, strEntityType, idDataGroup, false);

      if (strEntityType == RESP_BENEFICIARY)
      {
         validatePCGDelink (strValue, idDataGroup);
      }
   }
   else if (idField == ifds::RES2DesInstList)
   {
      DString strEntityType;
      getField( ifds::EntityType, strEntityType, idDataGroup, false );

      if ( strEntityType == RESP_BENEFICIARY )
      {
         DString strDesInst;
         getField( ifds::RES2DesInstList, strDesInst, idDataGroup, false );
         strDesInst.strip().upperCase();

         // This entity type is not mandatory to be linked but 
         // mandatory in account entity list per existing rule
         //if ( strDesInst.empty() || strDesInst == I_("0"))
         //{
         //   ADDCONDITIONFROMFILE(CND::ERR_INVALID_VALUE_FOR_DESGN_INST);
         //}
      }
   }
   else if ( idField == ifds::Rec511CutOffDate)
   {
      if ( getWorkSession ().isRES2Client() )
      {
         DString strRec511CutOffDate, strCurrBusDate;

         getWorkSession ().getOption (ifds::CurrBusDate, strCurrBusDate, idDataGroup);  
         getField( ifds::Rec511CutOffDate, strRec511CutOffDate, idDataGroup, false );
         strRec511CutOffDate.strip();

         if (DSTCommonFunctions::
            CompareDates (strCurrBusDate, strRec511CutOffDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            // Can't be future date
            ADDCONDITIONFROMFILE( CND::ERR_FUTURE_DATE_NOT_ALLOWED_FOR_RT511CUTOFF_DATE);
         }
      }
   }
   else if ( idField == ifds::DofBirth )
   {
      if(!isNew())
         validateDofBirthForRESPBenef(strValue,idDataGroup);
   }
    //IN2780013 - SOC Loan Number and Loan Type
   else if( idField == ifds::LoanType )
   {
		validateDuplicatedLoanTypeForEscrow(idDataGroup);
	//	validateLoanTypeLoanNumberForEscrow(idDataGroup );
   }
   else if (idField == ifds::PercentOwner)
   {
	   BigDecimal bdPercentOwner = DSTCommonFunctions::convertToBigDecimal (strValue);

       if ( (bdPercentOwner < 0)  ||  (bdPercentOwner > 100) )
       {
           ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::doApplyRelatedChanges ( const BFFieldId& idField, 
                                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   
   bool bIsRES2Client = getWorkSession ().isRES2Client();

   // for Canadaian yingbao

   // PTS 10007408
   // to ensure Entity object is being validated as soon as one field in this object is changed
   setValidFlag (ifds::LastName, idDataGroup, false);

   if (idField == ifds::FrFundNumber)
   {
      setFundClassCode(idField,idDataGroup);

   }
   else if( idField == ifds::EscrowFund || idField == ifds::EscrowClass )
   {
      setFundNumber(idField,idDataGroup);  
      setValidFlag( ifds::AmountReason, idDataGroup, false );
   }
   else if (idField == ifds::ReasonCode)
   {
      DString dstrReasonCode;
      getField( ifds::ReasonCode, dstrReasonCode, idDataGroup);
      if( dstrReasonCode.strip() == BANKRUPTCY_REASON_CODE )
      {
         setFieldNoValidate( ifds::EscrowFund, NULL_STRING, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::EscrowClass, NULL_STRING, idDataGroup, false, true, true );    
      }
   }
   else if( idField == ifds::RelateCode )
   {
      DString dstrBenPercentage;
      getField( ifds::BenPercentage, dstrBenPercentage, idDataGroup, false );
      BFDataField::formatValue( ifds::BenPercentage, dstrBenPercentage, false );
      setFieldNoValidate(ifds::BenPercentage, dstrBenPercentage, idDataGroup, false, true, true, false );
   } 
   else if ( idField == ifds::LastName || 
             idField == ifds::FirstName )
   {
      DString dstrEntityType;
      getField( ifds::EntityType, dstrEntityType, idDataGroup, false );
      if(dstrEntityType.strip() == OWNER_SPOUSAL)
      {
         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
         pAccountEntityXref->SetChildrenSpousalNameSubSet(idDataGroup, true);
      }
      else if (dstrEntityType.strip().upperCase() == RESP_PCG_INDIV  ||
               dstrEntityType.strip().upperCase() == RESP_PCG_INST   ||
               dstrEntityType.strip().upperCase() == PARENT_GUARDIAN ||
               dstrEntityType.strip().upperCase() == RESP_DSGN_INST )
      {
         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
         pAccountEntityXref->setRESPSelectableFieldSubSet(dstrEntityType,NULL_STRING,idDataGroup);
      }
      else if (dstrEntityType.strip().upperCase() == ACCOUNT_OWNER ||
               dstrEntityType.strip().upperCase() == ITF_INDIVIDUAL)
      {
         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
         pAccountEntityXref->updateAssociateEntityForAllRelatedPartyEntities(idDataGroup, NULL_STRING, NULL_STRING);
      }
   }
   else if (idField == ifds::EntityType)
   {
      setValidFlag( ifds::LastName, idDataGroup, false );

      DString entityType, entitySeq, accountNum;
      getField( ifds::EntityType, entityType, idDataGroup );
      getField( ifds::AccountNum, accountNum, idDataGroup );
      
      setFieldRequired( ifds::RefCode, idDataGroup, entityType == ENTITY_TYPE_REG_AGENT);
      
      AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
      if( pAccountEntityXref )
      {
         DString str;
         pAccountEntityXref->getValueForTag( objectKey, ENTITY_TYPE_FIELD, str );
         pAccountEntityXref->getValueForTag( objectKey, ENTITY_SEQ_NUM_FIELD, entitySeq );
         setFieldNoValidate( ifds::SeqNumber, NULL_STRING, idDataGroup, false, true, false );
         if( str != entityType )
            pAccountEntityXref->GetNextSeqNumber( idDataGroup, accountNum, entityType, entitySeq );
         setFieldNoValidate( ifds::SeqNumber, entitySeq, idDataGroup, false, true, false );
         /* Update objectKey since entityType is changed */
         DString entityID, currCount; 
         pAccountEntityXref->getValueForTag(  objectKey, ENTITY_ID_FIELD, entityID ); 
         pAccountEntityXref->getValueForTag(  objectKey, NEW_COUNT_TAG, currCount ); 
         pAccountEntityXref->buildKey( objectKey, 
                                       accountNum, 
                                       entityType, 
                                       entitySeq, 
                                       entityID, 
                                       currCount );
      }

      if( entityType == PRIMARY_BENEFICARY || entityType == SECONDARY_BENEFICARY || entityType == SUCCESSOR )
      {
         setValidFlag( ifds::RelateCode, idDataGroup, false );
         setFieldRequired( ifds::RelateCode, idDataGroup, true );
         setValidFlag( ifds::BenPercentage, idDataGroup, false );
         setFieldRequired( ifds::BenPercentage, idDataGroup, true );
      }
      else
      {
         setFieldRequired( ifds::RelateCode, idDataGroup, false );
         setFieldRequired( ifds::BenPercentage, idDataGroup, false );
      }

      if( entityType == ESCROW_REPRESENTATIVE || entityType == ASSIGNEE )
      {
         setValidFlag( ifds::FromFundClass, idDataGroup, false );
         setValidFlag( ifds::AmountType, idDataGroup, false );

         setFieldRequired( ifds::AmountType, idDataGroup, true );

         setFieldSubstituteValues( ifds::AmountType, idDataGroup, ifds::AmtTypeE );
         setFieldNoValidate( ifds::AmountType, I_("D"), idDataGroup, false, true, true );

         setValidFlag( ifds::ReasonCode, idDataGroup, false );
         setFieldRequired( ifds::ReasonCode, idDataGroup, true );
/*
         if(entityType == ESCROW_REPRESENTATIVE)//IN2780013 - SOC Loan Number and Loan Type
         {
            setValidFlag( ifds::LoanType, idDataGroup, false );
            setValidFlag( ifds::LoanNumber, idDataGroup, false );
         }
*/
         // Rule: Set the default value for EscrowDeff ( Effective Date of the Escrow screen) 
         //    to Current Business Date ( CurrBusDate of view 83 - getOptions). 
         DString strCurrBussinesDate;
         if( getWorkSession().getOption( ifds::CurrBusDate, strCurrBussinesDate, idDataGroup, false ) <= WARNING )
         {
            setFieldNoValidate( ifds::EscrowDeff, strCurrBussinesDate, idDataGroup, false, true, true );
         }
      }
      else
      {
         // for entity type other than escrow, we should set following fields
         setFieldRequired( ifds::AmountType, idDataGroup, false );
         setFieldRequired( ifds::ReasonCode, idDataGroup, false );
         setFieldNoValidate( ifds::EscrowFund, I_(""), idDataGroup, false, true, false );
         setFieldNoValidate( ifds::EscrowClass, I_(""), idDataGroup, false, true, false );
         DString str;
         getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
         //setFieldNoValidate( ifds::EscrowDeff, str, idDataGroup, false, true, false );
         setFieldNoValidate( ifds::EscrowStopDate, str, idDataGroup, false, true, false ); 

         DString strCurrBussinesDate;
         if( getWorkSession().getOption( ifds::CurrBusDate, strCurrBussinesDate, idDataGroup, false ) <= WARNING )
         {
            setFieldNoValidate( ifds::EscrowDeff, strCurrBussinesDate, idDataGroup, false, true, true );
         }
      }

      if( entityType == ACCOUNT_OWNER ||      
          entityType == AUTHORIZED_REP ||     
          entityType == LEGAL_REP ||          
          entityType == ECONOMIC_REP ||       
          entityType == ANNUITANT ||          
          entityType == SPOUSAL_CONTRIBUTOR ||
          entityType == ALTERNATE_PAYEE ||    
          entityType == ITF_INDIVIDUAL ||     
          entityType == NOMINEE_OWNER ||      
          entityType == PARENT_GUARDIAN ||    
          //entityType == ASSIGNEE ||
          entityType == EXECUTOR ||
          entityType == POWER_OF_ATTORNEY ||
          entityType == AUTHORIZED_SIGNATORY ||
          entityType == PARTNER ||
          entityType == SETTLOR )
      {
         // Incident #521433 the defaults for the AutorizeToTrade should be "Yes" for Nominee Owner, and "No"
         // for Account Owner Entity, for Nominee and Intermiar account
         DString accNum, accDesignation;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accNum, idDataGroup, true );
         if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::AcctDesignation, accDesignation, idDataGroup );
            if( accDesignation != NOMINEE && accDesignation != INTERMEDIAR ) 
            {
               if( entityType == ACCOUNT_OWNER )
               {
                  setFieldNoValidate( ifds::AuthorizedToTrade, I_("Y"), idDataGroup, false, true, false );
               }
               else
               {
                  setFieldNoValidate( ifds::AuthorizedToTrade, I_("N"), idDataGroup, false, true, false );
               }
            }

            else
            {
               if( entityType ==  NOMINEE_OWNER )
               {
                  setFieldNoValidate( ifds::AuthorizedToTrade, I_("Y"), idDataGroup, false, true, false );
               }
               else 
               {
                  setFieldNoValidate( ifds::AuthorizedToTrade, I_("N"), idDataGroup, false, true, false );
               }
            }
         }
         setFieldReadOnly( ifds::AuthorizedToTrade, idDataGroup, false );
      }
      else
      {
         setFieldNoValidate( ifds::AuthorizedToTrade, I_("N"), idDataGroup, false, true, false );
         setFieldReadOnly( ifds::AuthorizedToTrade, idDataGroup, true );
      }

      if (entityType == OWNER_SPOUSAL)
      {
         DString dstrLastName, 
            dstrFirstName;

         getField( ifds::LastName, dstrLastName, idDataGroup, false );
         getField( ifds::FirstName, dstrFirstName, idDataGroup, false );
         if( dstrLastName.strip() != NULL_STRING || dstrFirstName != NULL_STRING )
         {
            AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
            pAccountEntityXref->SetChildrenSpousalNameSubSet(idDataGroup, true);
         }
      }

      DString entityId;

      getField (ifds::EntityId, entityId, idDataGroup);
      if (!entityId.empty())
      {
         Entity* pEntity (NULL);
         if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
               pEntity)
         {
            pEntity->setEntityType (entityType);
            EntityIdsList* pEntityIdsList (NULL);

            if (pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, true) <= WARNING &&
                  pEntityIdsList)
            {
               pEntityIdsList->setEntityType (entityType);
               
               BFObjIter iter ( *pEntityIdsList, 
                                 idDataGroup, 
                                 true);
               while (!iter.end())
               {
                  EntityIds *pEntityIds = dynamic_cast <EntityIds *> (iter.getObject());

                  if (pEntityIds)
                  {
                     pEntityIds->setEntityType (idDataGroup);
                     if (entityType == CLEARING_PLATFORM)
                     {
                        pEntityIds->setBICCodeProperties (idDataGroup);
                     }
                  }
                  ++iter;
               }
            }
         }
      }

      DString strAccountNum;

      getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
      MFAccount *pMFAccount = NULL;

      DString strTaxType,
         strTaxTypeFmt;

      if( !strAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
      {
         pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
         pMFAccount->getField( ifds::TaxType, strTaxTypeFmt, idDataGroup, true );
         strTaxType.strip().upperCase();
      }

      if(bIsRES2Client && !strTaxType.empty())
      {
         if (strTaxType == FAMILY_RESP_TAX_TYPE)
         {
            initSubstitutionsRelateCodeForRESP (idDataGroup);
         }

         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
         
         pAccountEntityXref->setRESPSelectableFieldSubSet (PARENT_GUARDIAN,NULL_STRING,idDataGroup);
         pAccountEntityXref->setRESPSelectableFieldSubSet (RESP_DSGN_INST,NULL_STRING,idDataGroup);
         pAccountEntityXref->setRESPSelectableFieldSubSet (RESP_PCG_INDIV,NULL_STRING,idDataGroup);
         pAccountEntityXref->setRESPSelectableFieldSubSet (RESP_PCG_INST,NULL_STRING,idDataGroup);
      }
      if (entityType == PRIMARY_BENEFICARY ||
          entityType == SECONDARY_BENEFICARY ||
          entityType == RESP_BENEFICIARY)
      {
         // sync up TaxJuris and TaxJurisCode when entity type change to bene
         DString dstrEntityId;
         getField (ifds::EntityId, dstrEntityId, idDataGroup, false);

         WorkSessionEntityList *pWorkEntityList = NULL;
         Entity *pEntity (NULL);

         getWorkSession().getWorkSessionEntityList (pWorkEntityList);
         if (pWorkEntityList && 
             pWorkEntityList->getEntity (idDataGroup, dstrEntityId, pEntity) &&
             pEntity)
         {
            DString dstrTaxJuris;
            
            pEntity->getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);
            setFieldNoValidate (ifds::TaxJurisCode, dstrTaxJuris, idDataGroup, false);
         }

         if (entityType == RESP_BENEFICIARY)
         {
            MFAccount *pMFAccount = NULL;
            DString dstrAcctNum;
            getField( ifds::AccountNum, dstrAcctNum, idDataGroup, true );
            if( getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount ) <= WARNING )
            {
               DString dstrTaxType, dstrEntityType;
               pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup, false);
               getField( ifds::EntityType, dstrEntityType, idDataGroup, false );

               if (dstrTaxType == RESP && dstrEntityType == RESP_BENEFICIARY)
               {
                  setFieldNoValidate( ifds::BenPercentage, I_("100.0000"), idDataGroup, false );
               }
               else if ( dstrTaxType == FAMILY_RESP_TAX_TYPE && entityType == RESP_BENEFICIARY )
               {
                  setFieldNoValidate( ifds::BenPercentage, I_("0.0000"), idDataGroup, false );  
               }
            }
            DString dstrEntityId;
            getField (ifds::EntityId, dstrEntityId, idDataGroup);

            Entity* pEntity (NULL);
            if (getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING)
            {
               pEntity->setFieldValid (ifds::Gender, idDataGroup, false);
               pEntity->setFieldValid (ifds::DofBirth, idDataGroup, false);
            }

            /*setFieldReadOnly( ifds::Tainted, idDataGroup, true ); 
            setFieldReadOnly( ifds::TaintEndDate, idDataGroup, true );*/

            DString strGrantExists;
            
            getField (ifds::GrantExists, strGrantExists, idDataGroup, false );
            strGrantExists.strip().upperCase();

            // setup list of ParentLgl, DesInst and PCG around here
            if (strGrantExists == I_("Y"))
            {
               setFieldReadOnly( ifds::RES2PCGList, idDataGroup, true );
            }
            else
            {
               setFieldReadOnly( ifds::RES2PCGList, idDataGroup, false );
            }

            if (isNew())
            {
               setFieldNoValidate (ifds::RES2ParentLglList, I_("0"), idDataGroup, false );
               setFieldNoValidate (ifds::RES2DesInstList, I_("0"), idDataGroup, false );
               setFieldNoValidate (ifds::RES2PCGList, I_("0"), idDataGroup, false );

               //P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown'.
               // fix: Default SIN DATE with DOB when user selects EntityType = RESP_BENF after updating DOB
               doInitSINWithDofBirthForRESPBenf(idDataGroup);
            }
            else
            {
               DString strParentSeq, strDesInstSeq, strPCGId;
               getField( ifds::RESPParentSeq, strParentSeq, idDataGroup, false );
               getField( ifds::RESPDesInstSeq, strDesInstSeq, idDataGroup, false );
               getField( ifds::RESPPCGId, strPCGId, idDataGroup, false );
               strParentSeq.strip().upperCase();
               strDesInstSeq.strip().upperCase();
               strPCGId.strip().upperCase();

               setFieldNoValidate(ifds::RES2ParentLglList, strParentSeq, idDataGroup, false );
               setFieldNoValidate(ifds::RES2DesInstList, strDesInstSeq, idDataGroup, false );
               setFieldNoValidate(ifds::RES2PCGList, strPCGId, idDataGroup, false );
            }

            bool bRESPAllocAllow = getWorkSession().hasUpdatePermission (UAF::RESP_ALLOCATION);
            setFieldReadOnly (ifds::BenPercentage, idDataGroup, !bRESPAllocAllow);

            if (pMFAccount->isNew () && isNew () )
            {
               setFieldNoValidate (ifds::LetterReq, I_("Y"), idDataGroup, false);
               setFieldReadOnly (ifds::LetterReq, idDataGroup, true);
            }
            else if (isNew ()) //new entity & old account...
            {
               AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > (getParent());
               
               if (pAccountEntityXref && pAccountEntityXref->isRESPBeneficiaryDeleted (dstrAcctNum, idDataGroup))
               {
                  if(bIsRES2Client)
                  {
                     setFieldNoValidate (ifds::LetterReq, NULL_STRING, idDataGroup, false, false); //invalid
                     setFieldRequired (ifds::LetterReq, idDataGroup, true);
                     setFieldReadOnly (ifds::LetterReq, idDataGroup, false);
                  }
                  else
                  {
                     setFieldNoValidate (ifds::LetterReq, I_("Y"), idDataGroup, false, false); 
                     setFieldRequired (ifds::LetterReq, idDataGroup, false);
                     setFieldReadOnly (ifds::LetterReq, idDataGroup, true);
                  }
               }
               else
               {
                  setFieldNoValidate (ifds::LetterReq, I_("Y"), idDataGroup, false);
                  setFieldReadOnly (ifds::LetterReq, idDataGroup, true);
               }
            }
         }
      }

      DString dstrTaint;

      getField( ifds::Tainted, dstrTaint, idDataGroup, false );
      if (dstrTaint.empty ())
      {
         setFieldNoValidate (ifds::Tainted, I_("N"), idDataGroup, true);
      }

      setFieldReadOnly (ifds::Tainted, idDataGroup, true);
      setFieldReadOnly (ifds::TaintEndDate, idDataGroup, true);
      setFieldReadOnly( ifds::LetterDate, idDataGroup, true );
      setFieldValid( ifds::HRDCRelateCode, idDataGroup, false );
      DString strGrandFathered;
      pMFAccount->getField( ifds::GrandFathered, strGrandFathered, idDataGroup, false );
      // new entity for new account, it always be No and Readonly
      // new entity for existing account, if grandfather is yes, default it to No and it's not readonly.
      if (isNew())
      {
         // default value for new RESP Benef
         if (strGrandFathered.strip().upperCase() == I_("N"))
         {
            setFieldNoValidate( ifds::GrantRequest, I_("Y"), idDataGroup, false );
            setFieldReadOnly( ifds::GrantRequest, idDataGroup, false );
         }
         else
         {
            //setFieldNoValidate( ifds::GrantRequest, I_("N"), idDataGroup, false );
            setFieldReadOnly( ifds::GrantRequest, idDataGroup, true );
         }
      }
      else
      {
         if ( getWorkSession().hasUpdatePermission( UAF::RESP_GRANTS_REQUEST ) &&
              strGrandFathered.strip().upperCase() == I_("N") )
         {
            setFieldReadOnly( ifds::GrantRequest, idDataGroup, false );
         }

         else
         {
            setFieldNoValidate (ifds::GrantRequest, I_("N"), idDataGroup, false, false);
            setFieldReadOnly (ifds::GrantRequest, idDataGroup, true);
         }
      }

      if(entityType == ESTATE_OF_DECEASED)
      {
         DString dstrEntityId;
         getField (ifds::EntityId, dstrEntityId, idDataGroup, false);

         WorkSessionEntityList *pWorkEntityList = NULL;
         Entity *pEntity (NULL);

         getWorkSession().getWorkSessionEntityList (pWorkEntityList);
         if (pWorkEntityList && 
             pWorkEntityList->getEntity (idDataGroup, dstrEntityId, pEntity) &&
             pEntity)
         {      
            pEntity->setFieldValid (ifds::EmployeeClass, idDataGroup, false);
         }
      }

      if( entityType == ACCOUNT_OWNER )
      {
         DString strAccountType;
         pMFAccount->getField( ifds::AcctType, strAccountType, idDataGroup, false );
         
         if( !DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST) )
         {
            DString dstrEntityId;
            getField (ifds::EntityId, dstrEntityId, idDataGroup, false);

            WorkSessionEntityList *pWorkEntityList = NULL;
            Entity *pEntity (NULL);

            getWorkSession().getWorkSessionEntityList (pWorkEntityList);
            if (pWorkEntityList && 
               pWorkEntityList->getEntity (idDataGroup, dstrEntityId, pEntity) &&
               pEntity)
            {      
               // default entity category to corporate if account owner entity type of 
               // coroporate account
               pEntity->setEmployeeClassWithoutValidation(I_("02"), idDataGroup);  //ifds::EmployeeClass
               pEntity->setFieldValid (ifds::EmployeeClass, idDataGroup, false);
            }
         }
      }

	  DString dstrCRSEntityList;
	  getWorkSession().getOption ( ifds::CRSEntityList, dstrCRSEntityList, idDataGroup, false);    

	  if (entityType != ACCOUNT_OWNER && (DSTCommonFunctions::codeInList(entityType, dstrCRSEntityList) || dstrCRSEntityList == APPLICABLE_TO_ALL || entityType == RELATED_PARTY_AML_ENTITY_TYPE))
      {
		  bool bRequired = (entityType == RELATED_PARTY);
          setFieldRequired (ifds::AssocEntityId, idDataGroup, bRequired);
		  // Need to make field invalid to ensure it will be validated.
		  setFieldValid (ifds::AssocEntityId, idDataGroup, false);
          setFieldRequired (ifds::PercentOwner, idDataGroup, bRequired);
          setFieldNoValidate (ifds::PercentOwner, I_("0"), idDataGroup, false, false); // do not allow precision
          
          DString dstrAssociateEntitySubList;
          AccountEntityXref *pAccountEntityXref = dynamic_cast<AccountEntityXref*>(getParent());

          pAccountEntityXref->getAssociateEntitySubList(dstrAssociateEntitySubList, idDataGroup, NULL_STRING, NULL_STRING);
          updateAssociateEntity(dstrAssociateEntitySubList, idDataGroup);
      }
      else
      {
          setFieldNoValidate(ifds::AssocEntityId, NULL_STRING, idDataGroup, false);
          setFieldNoValidate(ifds::PercentOwner, I_("0"), idDataGroup, false, false);

          setFieldRequired(ifds::AssocEntityId, idDataGroup, false);
          setFieldRequired(ifds::PercentOwner, idDataGroup, false);

          AccountEntityXref *pAccountEntityXref = dynamic_cast<AccountEntityXref*>(getParent());
          pAccountEntityXref->updateAssociateEntityForAllRelatedPartyEntities(idDataGroup, NULL_STRING, NULL_STRING);
      }

      setFieldNoValidate(ifds::EntityAssociation, NULL_STRING, idDataGroup, false, false, true, true);
      setEntityAssociationSubstitutions(idDataGroup);

	  if (entityType == LEAD_ACCOUNT_MANAGER || entityType == ACCOUNT_MANAGER)
	  {
		   DString dstrEntityId;
           getField (ifds::EntityId, dstrEntityId, idDataGroup, false);
		   WorkSessionEntityList *pWorkEntityList = NULL;
           Entity *pEntity (NULL);

            getWorkSession().getWorkSessionEntityList (pWorkEntityList);
            if (pWorkEntityList && 
               pWorkEntityList->getEntity (idDataGroup, dstrEntityId, pEntity) &&
               pEntity)
            {      
               pEntity->setEmployeeClassWithoutValidation(I_("01"), idDataGroup);  //ifds::EmployeeClass
               pEntity->setFieldValid (ifds::EmployeeClass, idDataGroup, false);
            };
	  }

	  if (!strTaxType.empty() && strTaxType == RDSP_TAX_TYPE)
	  {	
		  DString dstrEntityId;
		  getField (ifds::EntityId, dstrEntityId, idDataGroup);		 

		  Entity* pEntity (NULL);
		  if (getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING)
		  {
			  DString dstrEmployeeClass;
			  pEntity->getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false);

			  if ((entityType == ACCOUNT_OWNER || entityType == RDSP_PCG) && dstrEmployeeClass != ENTITY_CATEGORY::CORPORATE)   
			  {				  				 				  				 		  					 									  
				  pEntity->setFieldRequired (ifds::LastName, idDataGroup, true);
				  pEntity->setFieldValid (ifds::LastName, idDataGroup, false);

				  if (entityType == ACCOUNT_OWNER)
				  {
					  pEntity->setFieldRequired (ifds::Gender, idDataGroup, true);
					  pEntity->setFieldValid (ifds::Gender, idDataGroup, false);
				  }
			  }		  
		  }
	  }

	  setFieldNoValidate(ifds::RDSPRelntoBene, NULL_STRING, idDataGroup, false, false, true, true);
	  loadRDSPRelntoBeneSetSubstList(idDataGroup, strTaxType);

	  initVerifyStatus (idDataGroup, isNew ());
      _bInit = false;
   } //entity type
   else if (idField == ifds::RES2PCGList)
   {
      DString strEntityType;
      getField (ifds::EntityType, strEntityType, idDataGroup, false);

      if (strEntityType == RESP_BENEFICIARY)
      {
         DString strFieldValue;
         getField(idField, strFieldValue, idDataGroup, false );
         setFieldNoValidate(ifds::RESPPCGId, strFieldValue,idDataGroup, false);

         DString strPCGChange, strRec400Sent;
         getField( ifds::PCGChange, strPCGChange, idDataGroup, false );
         getField( ifds::Rec400Sent, strRec400Sent, idDataGroup, false );
         strRec400Sent.strip().upperCase();

         if (strRec400Sent == I_("Y"))
         {
            setFieldNoValidate (ifds::CreateRec511, I_("Y"), idDataGroup, false);
            setFieldReadOnly (ifds::CreateRec511, idDataGroup, false );
            setFieldReadOnly (ifds::Rec511CutOffDate, idDataGroup, false );
         }
         else
         {
            setFieldNoValidate (ifds::CreateRec511, I_("N"), idDataGroup, false);
            setFieldReadOnly (ifds::CreateRec511, idDataGroup, true );
            setFieldReadOnly (ifds::Rec511CutOffDate, idDataGroup, true );
         }
      }
   }
   else if (idField == ifds::RES2ParentLglList)
   {
      DString strEntityType;
      getField( ifds::EntityType, strEntityType, idDataGroup, false );

      if ( strEntityType == RESP_BENEFICIARY )
      {
         DString strFieldValue;
         getField(idField, strFieldValue, idDataGroup, false );
         setFieldNoValidate(ifds::RESPParentSeq, strFieldValue,idDataGroup, false);
      }
   }
   else if (idField == ifds::RES2DesInstList)
   {
      DString strEntityType;
      
      getField (ifds::EntityType, strEntityType, idDataGroup, false);

      if (strEntityType == RESP_BENEFICIARY)
      {
         DString strFieldValue;
         getField(idField, strFieldValue, idDataGroup, false );
         setFieldNoValidate(ifds::RESPDesInstSeq, strFieldValue,idDataGroup, false);
      }
   }
   else if (idField == ifds::CreateRec511)
   {
      DString strCreateRec511;

      getField (ifds::CreateRec511, strCreateRec511, idDataGroup, false);
      strCreateRec511.strip().upperCase();

      if ( strCreateRec511 == I_("Y"))
      {
         DString strCurrBusDate, strCurrBusDateUnfmt;

         getWorkSession ().getOption (ifds::CurrBusDate, strCurrBusDate, idDataGroup); 
         DSTCommonFunctions::UnformatDate( strCurrBusDate, strCurrBusDateUnfmt);
         setFieldNoValidate( ifds::Rec511CutOffDate, strCurrBusDateUnfmt, idDataGroup, false );
         setFieldRequired( ifds::Rec511CutOffDate, idDataGroup, true );
      }
      else
      {
         DString str12319999;
         getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
         setFieldNoValidate( ifds::Rec511CutOffDate, str12319999, idDataGroup, false );
         setFieldRequired( ifds::Rec511CutOffDate, idDataGroup, false );
         setFieldValid( ifds::Rec511CutOffDate, idDataGroup, true );
      }
   } 
   else if (idField == ifds::TaxJurisCode)
   {
      DString strEntityType, 
         strEntityID;
      
      getField (ifds::EntityType, strEntityType, idDataGroup, false);
      getField (ifds::EntityId, strEntityID, idDataGroup, false);

      if ( getWorkSession ().isRES2Client() )
      {
         if ( strEntityType == PRIMARY_BENEFICARY ||
              strEntityType == SECONDARY_BENEFICARY ||
              strEntityType == RESP_BENEFICIARY )
         {
            WorkSessionEntityList *pWorkEntityList = NULL;
            Entity *pEntity (NULL);

            getWorkSession().getWorkSessionEntityList (pWorkEntityList);
            if (pWorkEntityList && 
                pWorkEntityList->getEntity (idDataGroup, strEntityID, pEntity) &&
                pEntity)
            {
               DString strFieldValue;
               getField( idField, strFieldValue, idDataGroup, false );
               pEntity->setField (ifds::TaxJuris, strFieldValue, idDataGroup, false);
            }
         }
      }
   }
   else if (idField == ifds::DofBirth)
   {
      // we have checked EntityType, TaxType, QESIClient in the method.
      if(isNew())
         doInitSINWithDofBirthForRESPBenf(idDataGroup);
   }
   if ( idField == ifds::AuthorizedToTrade ||
	    idField == ifds::AssocEntityId      ||
		idField == ifds::EntityAssociation ||
		idField == ifds::PercentOwner      ||
		idField == ifds::RefCode)
		   verifyStatusRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::setField( const BFFieldId& idField, 
                                            const DString& dstrValue,
                                            const BFDataGroupId& idDataGroup, 
                                            bool bFormatted, 
                                            bool bSideEffect, 
                                            bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   if( idField == ifds::AmtAssigned )
   {
      DString dstrAmtAssigned( dstrValue );
      getFormattedAmount( idDataGroup, dstrAmtAssigned );
      BFCBO::setField( idField, dstrAmtAssigned, idDataGroup, bFormatted, bSideEffect );
   }
   else if( idField == ifds::AmountType )
   {
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
      DString dstrAmtAssigned;
      getField( ifds::AmtAssigned, dstrAmtAssigned, idDataGroup );
      getFormattedAmount(idDataGroup, dstrAmtAssigned);
      BFCBO::setField(ifds::AmtAssigned, dstrAmtAssigned, idDataGroup, bFormatted, bSideEffect);
   }
   else if( idField == ifds::FrFundNumber )
   {
      setFieldNoValidate(ifds::EscrowFund, NULL_STRING, idDataGroup, false, true, false, false);
      setFieldNoValidate(ifds::EscrowClass, NULL_STRING, idDataGroup, false, true, false, false);
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bFormatted);
   }
   else if( idField == ifds::OwnerSpouseName )
   {
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bFormatted);

      DString strEntityType;
      getField(ifds::EntityType,strEntityType,idDataGroup,false);
      if(dstrValue != NULL_STRING && strEntityType.strip() == ACCOUNT_OWNER)
      {
         DString dstrEntityId;
         getField( ifds::EntityId, dstrEntityId, idDataGroup );

         Entity* pEntity;
         if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
         {
            pEntity->setField(ifds::SpouseEntityID, dstrValue, idDataGroup, bFormatted, bFormatted);
            if(dstrValue == I_("0") && isNew()) 
               pEntity->setFieldUpdated( ifds::SpouseEntityID, idDataGroup, false );
         }
      }
   }
   else
   {
	  
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

void AccountEntityXrefObject::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue) const
{
   DString dstrAmountType;

   getField(ifds::AmountType, dstrAmountType, idDataGroup, false);
   dstrAmountType.strip();

   int iUnitsPrecision = 0;

   if( dstrAmountType == I_( "U" ) )
   {
      DString dstrUnitsPrecision, dstrFundCode, dstrClassCode;

      getField(ifds::EscrowFund, dstrFundCode, idDataGroup, false);
      dstrFundCode.strip().upperCase();
      getField(ifds::EscrowClass, dstrClassCode, idDataGroup, false);
      dstrClassCode.strip().upperCase();

      FundDetailList *pFundDetailList = NULL;

      if( const_cast<MgmtCo &>(getMgmtCo()).getFundDetailList( pFundDetailList ) <= WARNING )
      {
         pFundDetailList->getField ( dstrFundCode, dstrClassCode, ifds::UnitsPrecision, 
                                     dstrUnitsPrecision, idDataGroup, false );
         iUnitsPrecision = dstrUnitsPrecision.asInteger(); 

      }
   }
   else
   {
      iUnitsPrecision = 2; 

   }
   dstrValue.strip().stripAll(I_(','));
   dstrValue.stripLeading(I_('+')).stripTrailing(I_('.'));
   const BFFieldId& idField = ifds::USDollar;
   DSTCommonFunctions::formattedField( idField, iUnitsPrecision, dstrValue ); 
}


//******************************************************************************
void AccountEntityXrefObject::setFlagsUpdated( const BFDataGroupId& idDataGroup )
{
   // this function is called from the EntityProcess when an entity field is updated and 
   // we need to set the correspondent AccountEntityXref object as updated
   if( isNew() )
   {
      setFieldUpdated (ifds::LastName, idDataGroup, true);
   }
}
/***********************************************************************************
The following methods are all for Canadian market
Yingbao July 19, 2000 

*/
//**************************************************************************************
void AccountEntityXrefObject::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) )
   DString dstrFundNumber, dstrFundCode, dstrClassCode;

   getField( ifds::EscrowFund, dstrFundCode, idDataGroup, false);
   getField( ifds::EscrowClass, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {
      getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );

      DString oldFundNumber;
      getField( ifds::FrFundNumber, oldFundNumber, idDataGroup, false);
      if( oldFundNumber.strip() != dstrFundNumber )
      {
         setFieldNoValidate( ifds::FrFundNumber, dstrFundNumber, idDataGroup, false, true, true );   
      }
   }
}

//*************************************************************************************
void AccountEntityXrefObject::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) )
   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField( idField, dstrFundNumber, idDataGroup, false );
   if( dstrFundNumber.strip() != NULL_STRING )
   {
      if( getWorkSession().GetFundClassCode( dstrFundNumber, dstrFundCode, dstrClassCode) )
      {
         DString oldFundCode,oldClassCode;
         getField( ifds::EscrowFund, oldFundCode, idDataGroup, false );
         getField( ifds::EscrowClass, oldClassCode, idDataGroup, false );
         if( oldFundCode != dstrFundCode )
         {
             setField(ifds::EscrowFund, dstrFundCode, idDataGroup, false);
            //setFieldNoValidate( ifds::EscrowFund, dstrFundCode, idDataGroup );
         }
         if( oldClassCode != dstrClassCode )
         {
            setField(ifds::EscrowClass, dstrClassCode, idDataGroup, false);
            //setFieldNoValidate( ifds::EscrowClass, dstrClassCode, idDataGroup );            
         }
      }
   }
}
//****************************************************************************

void AccountEntityXrefObject::validateFundNumber(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundNumber" ) );
   DString dstrFundCode,dstrClassCode, strValue;
   getField(ifds::FrFundNumber, strValue, idDataGroup, false);
   if( !getWorkSession().GetFundClassCode( strValue,dstrFundCode,dstrClassCode) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
      return;
   }
   validateFundClass(idDataGroup, dstrFundCode, dstrClassCode);
}

//****************************************************************************
void AccountEntityXrefObject::validateFundClass(const BFDataGroupId& idDataGroup, DString strEscrowFund, DString strEscrowClass)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFundCode" ) );

   DString strKey, EntityType, accNum;
   if( strEscrowFund.strip().empty() )
      getField(ifds::EscrowFund, strEscrowFund, idDataGroup, false);
   if( strEscrowClass.strip().empty() )
      getField(ifds::EscrowClass, strEscrowClass, idDataGroup, false);
   strEscrowFund.strip().upperCase();
   strEscrowClass.strip().upperCase();
   getField(ifds::EntityType,EntityType,idDataGroup,false);
   EntityType.strip();

   if( EntityType != ESCROW_REPRESENTATIVE && EntityType != ASSIGNEE )
   {
      if( strEscrowFund != NULL_STRING || strEscrowClass != NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ESCROWFUND_ENTITY_TYPE );
      }
      return ; 
   }


   // if EntityType = ESCROW_REPRESENTATIVE and Amount Type = U fundcode and classcode can not be blank
   DString dstrAmountType, dstrAmount;
   getField(ifds::AmountType,dstrAmountType,idDataGroup,false);
   getField(ifds::AmtAssigned,dstrAmount,idDataGroup,false);
   dstrAmountType.strip();

   double dec_amount = DSTCommonFunctions::convertToDouble( dstrAmount ) ;


   if( ( EntityType == ESCROW_REPRESENTATIVE || EntityType == ASSIGNEE ) && dstrAmountType == UNIT_AMOUNT_TYPE && dec_amount != 0 )
   {
      if( strEscrowFund == NULL_STRING || strEscrowClass == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ESCROW_FUND_CLASS_BLANK );
         return;  
      }
   }
   if( strEscrowFund != NULL_STRING && strEscrowClass != NULL_STRING )
   {
      /* replace by the new logic below to check balance. 
         If holding exist but balance is zero, same error applies
      MFAccountHoldingList* _pMFAccountHoldingList = NULL;
      MFAccount *pMFAccount = NULL;
      getField( ifds::AccountNum, accNum, idDataGroup, true );

      if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
      {
         pMFAccount->getAccountHoldingList(_pMFAccountHoldingList,idDataGroup,true);
         if (_pMFAccountHoldingList)
         {
            BFObjIter acctHoldIter( *_pMFAccountHoldingList, idDataGroup,false, BFObjIter::ITERTYPE::NON_DELETED );
         
            Data data;
            data.setElementValue( ifds::rxFundCode, strEscrowFund, true, false );
            data.setElementValue( ifds::rxClassCode, strEscrowClass, true, false );
            _pMFAccountHoldingList->getStrKey(strKey,&data );
            acctHoldIter.positionByKey( strKey );
            if( acctHoldIter.end() )
            { // have not fund 
               ADDCONDITIONFROMFILE( CND::ERR_ESCROWFUND_CLASS );
               return;
            }
         }
      }*/

      DString dstrReasonCode;
      getField( ifds::ReasonCode, dstrReasonCode, idDataGroup);
      if( dstrReasonCode.strip() == BANKRUPTCY_REASON_CODE )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_MUST_BLANK_FOR_BANKRUPTCY );
      }
      else
      {
         bool bFundValid ( false );
         double dFundBalance = getFundBalance ( bFundValid, ifds::SettledUnits, idDataGroup );
         if( bFundValid && dFundBalance == 0 )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ESCROWFUND_CLASS );
         }
      }

   }

// Rule: User is allow to leave Escrow Fund and Class blank. But if they leave 
//    Fund blank, class must be blank before the leave the screen and vice versa.

   //IN2780013 - SOC Loan Number and Loan Type
	if( EntityType == ESCROW_REPRESENTATIVE )
	{
		validateDuplicatedLoanTypeForEscrow(idDataGroup);
	}

}

//******************************************************************************
void AccountEntityXrefObject::initDefaultValues (const BFDataGroupId& idDataGroup, const DString& taxType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefaultValues" ) );
   
   DString dstrFrFundNumber,
       dstrFundCode,
       dstrFundClass,
       strAcctPurpose, 
       strInTrustFor;

   getField (ifds::EscrowFund,  dstrFundCode,  idDataGroup, false);
   getField (ifds::EscrowClass, dstrFundClass, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrFundClass.strip().upperCase();  

   getWorkSession().GetFundNumber (dstrFundCode, dstrFundClass, dstrFrFundNumber);

   setFieldNoValidate (ifds::FrFundNumber, dstrFrFundNumber, BF::HOST);
   setFieldSubstituteValues (ifds::AmountType, idDataGroup, ifds::AmtTypeE);

   setValidFlag (ifds::DofBirth, idDataGroup, false);
   setFieldRequired (ifds::DofBirth, idDataGroup, true); 

   DString entityType;

   getField (ifds::EntityType, entityType, idDataGroup, false);
   if (entityType == CLEARING_PLATFORM)
   {
      DString entityId;

      getField (ifds::EntityId, entityId, idDataGroup);
      if (!entityId.empty())
      {
         Entity* pEntity (NULL);
         if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
             pEntity)
         {
            pEntity->setField (ifds::EmployeeClass, I_("02"), idDataGroup, false);
            pEntity->setFieldReadOnly (ifds::EmployeeClass, idDataGroup, true);
            pEntity->setFieldReadOnly (ifds::LastName, idDataGroup, true);
            setFieldReadOnly (ifds::EntityType, idDataGroup, true);
         }
      }
   }

   setFieldReadOnly (ifds::LetterReq, idDataGroup, true);
   if (getWorkSession ().isRES2Client() && !taxType.empty())
   {
      if (taxType == FAMILY_RESP_TAX_TYPE)
      {
         initSubstitutionsRelateCodeForRESP (idDataGroup);
      }

      if (entityType == RESP_BENEFICIARY)
      {
         setFieldReadOnly( ifds::LetterDate, idDataGroup, true );
         setFieldValid( ifds::HRDCRelateCode, idDataGroup, false );

         bool bRESPAllocAllow = getWorkSession().hasUpdatePermission (UAF::RESP_ALLOCATION);

         setFieldReadOnly (ifds::BenPercentage, idDataGroup, !bRESPAllocAllow);

         DString strParentSeq, 
            strDesInstSeq, 
            strPCGId;
         
         getField( ifds::RESPParentSeq, strParentSeq, idDataGroup, false );
         getField( ifds::RESPDesInstSeq, strDesInstSeq, idDataGroup, false );
         getField( ifds::RESPPCGId, strPCGId, idDataGroup, false );
         strParentSeq.strip().upperCase();
         strDesInstSeq.strip().upperCase();
         strPCGId.strip().upperCase();

         setFieldNoValidate(ifds::RES2ParentLglList, strParentSeq, idDataGroup, false );
         setFieldNoValidate(ifds::RES2DesInstList, strDesInstSeq, idDataGroup, false );
         setFieldNoValidate(ifds::RES2PCGList, strPCGId, idDataGroup, false, true, true, false );

         setFieldValid (ifds::HRDCRelateCode, idDataGroup, false);

         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > (getParent());
         
         DString letterReq, acctNum;
         getField( ifds::AccountNum, acctNum, idDataGroup, true );
         getField (ifds::LetterReq, letterReq, idDataGroup, false );
         if (pAccountEntityXref && pAccountEntityXref->isRESPBeneficiaryDeleted (acctNum, idDataGroup) &&
             letterReq == I_("N")) //open it up...
         {
            setFieldReadOnly (ifds::LetterReq, idDataGroup, false);
         }
      }
   }

   DString strGrantRequest;
   
   getField (ifds::GrantRequest, strGrantRequest, idDataGroup, false);
   strGrantRequest.strip().upperCase();
// ensure that it's not blank for RESP and others entities
//   if (strGrantRequest.empty()  || 
//       !getWorkSession().hasUpdatePermission (UAF::RESP_GRANTS_REQUEST))
   if (strGrantRequest.empty() )
   {
      setFieldNoValidate (ifds::GrantRequest, I_("N"), idDataGroup, false);
   }
   setFieldReadOnly (ifds::GrantRequest, idDataGroup, !getWorkSession().hasUpdatePermission (UAF::RESP_GRANTS_REQUEST));

   DString strCreateRec511;
   getField (ifds::CreateRec511, strCreateRec511, idDataGroup, false);
   strCreateRec511.strip().upperCase();

   if (strCreateRec511.empty())
   {
      setFieldNoValidate (ifds::CreateRec511, I_("N"), idDataGroup, false);
   }
   setFieldReadOnly (ifds::CreateRec511, idDataGroup, true);
   setFieldReadOnly (ifds::Rec511CutOffDate, idDataGroup, true);

   DString dstrTaint;
   getField (ifds::Tainted, dstrTaint, idDataGroup, false);
   if (dstrTaint.empty ())
   {
      setFieldNoValidate (ifds::Tainted, I_("N"), idDataGroup, true);
   }
   setFieldReadOnly (ifds::Tainted, idDataGroup, true);
   setFieldReadOnly (ifds::TaintEndDate, idDataGroup, true);

   loadRDSPRelntoBeneSetSubstList(idDataGroup, taxType);

   initVerifyStatus (idDataGroup, false);
   _bInit = false;
}

//******************************************************************************
void AccountEntityXrefObject::SetSpousalEntityNameSubSet( const BFDataGroupId& idDataGroup, DString SpousalNameSubSet, DString FSpouseEntity, bool setdefault )
{
   setFieldAllSubstituteValues( ifds::OwnerSpouseName,    idDataGroup, SpousalNameSubSet );
   setFieldAllSubstituteValues( ifds::OwnerSpouseName,    BF::HOST, SpousalNameSubSet );

   //getField is const and get entity is not const, can not put this part of code to the override getField function
   DString dstrSpouseEntityID, dstrOwnerSpouseName;	
   getField(ifds::OwnerSpouseName, dstrOwnerSpouseName, idDataGroup, false);
   if(dstrOwnerSpouseName.strip() == NULL_STRING )
   {
      DString dstrEntityId;
      getField( ifds::EntityId, dstrEntityId, idDataGroup );
      Entity* pEntity;
      if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
      {
         pEntity->getField(ifds::SpouseEntityID, dstrSpouseEntityID, idDataGroup, false);
         if( dstrSpouseEntityID != NULL_STRING ) 
            setFieldNoValidate( ifds::OwnerSpouseName, dstrSpouseEntityID, idDataGroup, false,false,false,false );
      }
   }

   if( FSpouseEntity != NULL_STRING && setdefault )
   {
      DString dstrAcctType, acctNum, dstrSeqNumber;
      MFAccount *pMFAccount = NULL;
      getField( ifds::AccountNum, acctNum, idDataGroup, true );
      if( getWorkSession().getMFAccount( idDataGroup, acctNum, pMFAccount ) <= WARNING )
      {
         pMFAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup);
         dstrAcctType.strip();
         getField( ifds::SeqNumber, dstrSeqNumber, idDataGroup );

         if(dstrAcctType != JOINT && asInteger( dstrSeqNumber ) == 1 )
         {
            setField(ifds::OwnerSpouseName, FSpouseEntity, idDataGroup, false, true );
            setField(ifds::OwnerSpouseName, FSpouseEntity, BF::HOST, false, true);
         }
      }
   }
}
//******************************************************************************
void AccountEntityXrefObject::getErrMsgValue( DString dstrErrNum,       
                                              const BFDataGroupId& idDataGroup, 
                                              DString& dstrErrValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if (_pErrMsgRulesList == NULL)
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if (_pErrMsgRulesList)
   {
      _pErrMsgRulesList->getEWIValue (dstrErrNum, idDataGroup, dstrErrValue);
   }
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::getErrMsg( DString dstrErrNum,
                                             long    lErrConditionId, 
                                             long    lWarnConditionId, 
                                             const   BFDataGroupId& idDataGroup, 
                                             DString idiStr )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {
      _pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
void AccountEntityXrefObject::validateReasonCode(const DString& dstrReason,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateReasonCode" ) );

   DString acctNum,TaxType;
   MFAccount *pMFAccount = NULL;
   getField( ifds::AccountNum, acctNum, idDataGroup, true );
   if( getWorkSession().getMFAccount( idDataGroup, acctNum, pMFAccount ) <= WARNING )
   {
      pMFAccount->getField(ifds::TaxType,TaxType,idDataGroup,false);
      TaxType.strip();
      if( dstrReason == RSP_LOAN_REASON_CODE )
      {
         if( TaxType != RRSP && TaxType != EXTERNAL_RRSP )
         {
            ADDCONDITIONFROMFILE( CND::ERR_REASONCODE_RRSP_LOAN );
            return;
         }
      }
      else if( dstrReason == COLLATERAL_REASON_CODE )
      {
         if( !getWorkSession().isNonRegLike( TaxType ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_REASONCODE_COLLATERAL );
            return;
         }
      }


      // Add escrow Representives
      DString dstrTitleRestrict, dstrEntityType, dstrEffectiveDate;

      getField( ifds::EntityType, dstrEntityType, idDataGroup );
      getField( ifds::EscrowDeff, dstrEffectiveDate, idDataGroup );

      dstrEntityType.strip().upperCase();

      getWorkSession().getOption( ifds::TitleRestrict, dstrTitleRestrict, idDataGroup, false );

      if( dstrTitleRestrict == YES && isNew() && ( dstrEntityType == ESCROW_REPRESENTATIVE ||
                                                   dstrEntityType == ASSIGNEE ) )
      {
         AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
         if( pAccountEntityXref )
         {
            DString dstrSeqNumber;
            getField( ifds::SeqNumber, dstrSeqNumber, idDataGroup );

            pAccountEntityXref->escrowAccount( acctNum, ADD_ENTITY, dstrEntityType, dstrEffectiveDate, idDataGroup, dstrReason, dstrSeqNumber);
         }
      } // Add escrow Representives

   } // if MFAccount available
}


//*****************************************************************************
void AccountEntityXrefObject::validateAmountType(const DString& strValue, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmountType" ) );
   DString entityType;
   getField( ifds::EntityType, entityType, idDataGroup );
   if( strValue != NULL_STRING && ( entityType != ESCROW_REPRESENTATIVE && entityType != ASSIGNEE ) )
      ADDCONDITIONFROMFILE( CND::ERR_ESCROW_AMOUNT_TYPE );
   if( strValue == I_("U") && ( entityType == ESCROW_REPRESENTATIVE || entityType == ASSIGNEE ) )
   {

      DString dstrEscrowFund, dstrEscrowClass, dstrAmount;
      getField( ifds::EscrowFund, dstrEscrowFund, idDataGroup );
      getField( ifds::EscrowClass, dstrEscrowClass, idDataGroup );
      getField( ifds::AmtAssigned, dstrAmount, idDataGroup );

      double dec_amount = DSTCommonFunctions::convertToDouble( dstrAmount ) ;

      if( dec_amount != 0 && (dstrEscrowFund == NULL_STRING || dstrEscrowClass == NULL_STRING) )
         ADDCONDITIONFROMFILE( CND::ERR_ESCROW_FUND_CLASS_BLANK );
   }
}

//********************************************************************************
void AccountEntityXrefObject::validateEffectiveStopDate(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopDate" ) );
   DString strEscrowEffectiveDate, strEscrowStopDate;
   getField( ifds::EscrowStopDate, strEscrowStopDate, idDataGroup, false );
   getField( ifds::EscrowDeff, strEscrowEffectiveDate, idDataGroup, false );
   if( DSTCommonFunctions::CompareDates( strEscrowStopDate, strEscrowEffectiveDate ) 
       == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_STOP_DATE_LESS_THAN_DEFF );
   }
}

//******************************************************************************
void AccountEntityXrefObject::validateAmountReason( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmountReason" ) );

// Rule: If the Escrow reason code is '01' (bankruptcy), the amount must be zero.
//    Include this business rule in the edit check for the amount.
   DString strAmtAssigned, strReasonCode;
   getField( ifds::ReasonCode, strReasonCode, idDataGroup );
   getField( ifds::AmtAssigned, strAmtAssigned, idDataGroup );
   if( strReasonCode.strip() == BANKRUPTCY_REASON_CODE )
   {
      double dec_amount = DSTCommonFunctions::convertToDouble ( strAmtAssigned );

      if( dec_amount != 0 )
      {
         // Do not automatically assign value to zero, let user update it. This works better for all products (API etc).
         //setFieldNoValidate( ifds::AmtAssigned, I_( "0" ), idDataGroup, true, true, false );
         ADDCONDITIONFROMFILE( CND::ERR_AMOUNT_MUST_BE_ZERO_IF_ESCROW_REASON_CODE_IS_BANKRUPTCY );
      }
   }
   else if( strReasonCode.strip() == LOAD_REASON_CODE )
   {
      double dec_amount = DSTCommonFunctions::convertToDouble ( strAmtAssigned );

      DString dstrFundCode, dstrClassCode;
      getField(ifds::EscrowFund, dstrFundCode, idDataGroup, false);
      dstrFundCode.strip().upperCase();
      getField(ifds::EscrowClass, dstrClassCode, idDataGroup, false);
      dstrClassCode.strip().upperCase();

      if( dec_amount != 0 && dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_AMT_MUST_BE_ZERO_ESCROW_REASON_LOAN);
      }
   }
   else
   {
//    	setFieldReadOnly( ifds::AmtAssigned, idDataGroup, false );
   }
}

//******************************************************************************
bool AccountEntityXrefObject::isEntityEffective ( const DString& dstrDate, const BFDataGroupId& idDataGroup )
{
   DString strEntityType;
   bool isEffective (true);

   getField( ifds::EntityType, strEntityType, idDataGroup, false );

   if( ESCROW_REPRESENTATIVE == strEntityType || ASSIGNEE == strEntityType )
   {
      DString escrowStart, escrowEnd;

      getField( ifds::EscrowDeff, escrowStart, idDataGroup, false );
      getField( ifds::EscrowStopDate, escrowEnd, idDataGroup, false );
      escrowStart.strip();
      escrowEnd.strip();

      if( escrowStart == NULL_STRING || escrowEnd == NULL_STRING )
      {
         isEffective= false;
      }
      else isEffective = DSTCommonFunctions::IsDateBetween(escrowStart, escrowEnd, dstrDate);
   }
   else
   {
      DString dstrEffective;
      getField( ifds::EffectiveDate, dstrEffective, idDataGroup, false );
      isEffective = (DSTCommonFunctions::CompareDates( dstrEffective, dstrDate ) 
                     == DSTCommonFunctions::FIRST_EARLIER );
   }

   return(isEffective);
}

//******************************************************************************
void AccountEntityXrefObject::ModelOffer(AccountEntityXrefObject *Model, DString strSeqNum, 
                                         const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0050_VWRepeat_Record);

//CP	DataComponentProperties *dcpPtr  = NULL;

   BFDataFieldIter dIter( *tmp );
   DString str;
   for( ;dIter; ++dIter )
   {
//CP      dcpPtr = const_cast< DataComponentProperties * >(dIter().getProperties());
//CP      dcpPtr->getId( idField );
      BFDataField& idField = dIter();

      if (idField.getId() == ifds::EscrowDeff ||
          idField.getId() == ifds::EscrowStopDate)
      {
         setEscrowRelatedDate(idField.getId(), idDataGroup);
      }
      else
      {
         Model->getField( idField.getId(), str, idDataGroup );
         setField(idField.getId(), str, idDataGroup);
      }
   };

   setFieldNoValidate( ifds::SeqNumber, strSeqNum, idDataGroup, false, true, false );
   setFieldNoValidate( ifds::EntityType, NULL_STRING, idDataGroup, false, false, false );
//   setField ( ifds::EntityType, NULL_STRING, idDataGroup );

   delete tmp;

}

//******************************************************************************
bool AccountEntityXrefObject::acctOwnerAgeEligibleForTFSA(const BFDataGroupId& idDataGroup)
{
    bool ageElgb = false;
    DString dstrAcctNum, dstrTaxType, dstrEntityType, dstrSeqNumber, dstrDofBirth;
	DString acctJurisdiction, entityId, dstrCurrBussinesDate;
    MFAccount *pMFAccount = NULL;
    Entity *pEntity = NULL;
    TaxTypeRuleList *ptaxTypeRuleList = NULL;

    getField(ifds::AccountNum, dstrAcctNum, idDataGroup);
    getField(ifds::EntityType, dstrEntityType, idDataGroup);
    getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup);
    getField(ifds::DofBirth, dstrDofBirth, idDataGroup);
    getField(ifds::EntityId, entityId, idDataGroup);
	getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false);

    if (getWorkSession().getMFAccount(idDataGroup, dstrAcctNum, pMFAccount) <= WARNING && pMFAccount)
        pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup);

    if (dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE && 
        asInteger(dstrSeqNumber) == 1 &&
        dstrTaxType == TFSA_TAX_TYPE &&
        !dstrDofBirth.empty() &&
        pMFAccount &&
        getMgmtCo().getTaxTypeRuleList(ptaxTypeRuleList) <= WARNING && ptaxTypeRuleList &&
        getWorkSession().getEntity(idDataGroup, entityId, pEntity ) <= WARNING && pEntity)
    {
        int TFSAEligibleAge;

        pEntity->getField(ifds::TaxJuris, acctJurisdiction, idDataGroup );

        if (ptaxTypeRuleList->checkEligibleAge(dstrTaxType) && 
            ptaxTypeRuleList->getTFSAEligibleAge(getWorkSession(), acctJurisdiction, TFSAEligibleAge))
        {
			BFDate bfdCurrentBusDate(dstrCurrBussinesDate, BFDate::DATE_FORMAT::DF_HOST);
			BFDate bfdEligibleDate(dstrDofBirth, BFDate::DATE_FORMAT::DF_HOST);
			bfdEligibleDate.addYears(TFSAEligibleAge);

			if (bfdCurrentBusDate >= bfdEligibleDate) // Exact age
				ageElgb = true;
        }
    }

    return ageElgb;
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateEntityTypeDofB (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOfBirth" ) );

   SEVERITY sevRtn = NO_CONDITION;

   DString dstrTaxType, dstrLockedIn, dstrAcctDesignation, dstrAcctType, acctJurisdiction;
   DString dstrTaxTypeRules, dstrDefTaxTypeRules, dstrMinAge, dstrMaxAge, dstrDofBirth;
   DString dstrEntityType, dstrAcctNum, dstrSeqNumber, dstrEntityId;

   getField( ifds::EntityType, dstrEntityType, idDataGroup );
   dstrEntityType.strip();

   getField( ifds::SeqNumber, dstrSeqNumber, idDataGroup );
   dstrSeqNumber.strip();

   getField( ifds::EntityId, dstrEntityId, idDataGroup );

   Entity* pEntity;
   int iEntityAge;
   DString dstrEntityAge;

   getField( ifds::AccountNum, dstrAcctNum, idDataGroup, true );
   MFAccount *pMfAccount = NULL;
   sevRtn = getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMfAccount ); 

   if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
   {
      DString dstrLastName;
      pEntity->getField( ifds::LastName, dstrLastName, idDataGroup );
      if( dstrLastName == NULL_STRING )
         return(GETCURRENTHIGHESTSEVERITY());

      TaxTypeRule *pTaxTypeRule = NULL;
      pMfAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup);

      int ageCalcBasedOn = 0;

      if( pTaxTypeRule )
      {
         DString dstrJurisdiction;

         pMfAccount->getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
         pTaxTypeRule->getAgeCalcBasedOn (ageCalcBasedOn, dstrJurisdiction, idDataGroup);
      }

      iEntityAge = pEntity->getEntityAge (ageCalcBasedOn, idDataGroup);
      dstrEntityAge.appendInt( iEntityAge);
      pEntity->getField( ifds::DofBirth, dstrDofBirth, idDataGroup );
      pEntity->getField( ifds::TaxJuris, acctJurisdiction, idDataGroup );
   }

   if( sevRtn <= WARNING )
   {
      pMfAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup);
      dstrTaxType.strip().upperCase();
   }

   if ( dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE && asInteger( dstrSeqNumber ) == 1 )
   {
      if( dstrTaxType == TFSA_TAX_TYPE )
      {
         ErrMsgRulesList * pErrMsgRulesList = NULL;
         if( !dstrDofBirth.empty() )
         {
             TaxTypeRuleList *ptaxTypeRuleList=NULL;

            if (getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList ) <= WARNING && ptaxTypeRuleList)
            {
                int TFSAElgbAge;

                if (pMfAccount && pMfAccount->isNew() &&
                    ptaxTypeRuleList->checkEligibleAge(dstrTaxType) && 
                    ptaxTypeRuleList->getTFSAEligibleAge(getWorkSession(), acctJurisdiction, TFSAElgbAge))
                {
					DString dstrCurrBussinesDate;
					getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false);

					BFDate bfdCurrentBusDate(dstrCurrBussinesDate, BFDate::DATE_FORMAT::DF_HOST);
					BFDate bfdEligibleDate(dstrDofBirth, BFDate::DATE_FORMAT::DF_HOST);
					bfdEligibleDate.addYears(TFSAElgbAge);

                    if (bfdCurrentBusDate < bfdEligibleDate) // Exact age
                    {
                        getErrMsg(IFASTERR::ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS, 
                                  CND::ERR_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS, 
                                  CND::WARN_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS,
                                  idDataGroup);
                    }
                }
                else
                {
                    BFObjIter iterList( *ptaxTypeRuleList, BF::HOST, false );
                    DString strKey;
                    ptaxTypeRuleList->getStrKey( strKey, dstrTaxType, I_("00") );
                    if( iterList.positionByKey( strKey ) )
                    {
                        iterList.getObject()->getField( ifds::MinAge, dstrMinAge, BF::HOST, false );
                        iterList.getObject()->getField( ifds::MaxAge, dstrMaxAge, BF::HOST, false );
                        if( (!dstrMinAge.strip().empty() && dstrMinAge != I_("0") && iEntityAge < DSTCommonFunctions::convertToDouble(dstrMinAge) ) ||
                            (!dstrMaxAge.strip().empty() && dstrMaxAge != I_("0") && iEntityAge > DSTCommonFunctions::convertToDouble(dstrMaxAge) ))
                        {
                            if( getMgmtCo ().getErrMsgRulesList( pErrMsgRulesList) <= WARNING && pErrMsgRulesList )
                            {
                                pErrMsgRulesList->getEWI (IFASTERR::MIN_MAX_AGE, CND::ERR_INVALID_AGE,CND::WARN_INVALID_AGE,idDataGroup);
                            }
                        }
                    }
                }
            }
         }
         else
         {
            if( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING )
            {
               pErrMsgRulesList->getEWI(IFASTERR::MIN_MAX_AGE, CND::ERR_DATE_OF_BIRTH_REQUIRED,CND::WARN_DATE_OF_BIRTH_EMPTY,idDataGroup);
            }
         }
      }
      else if( !dstrDofBirth.empty() && iEntityAge < 18 )
       {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_SHAREHOLDER_YOUNGER_THAN_18 );
       }
   }

   if( sevRtn <= WARNING )
   {
      pMfAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup);
      dstrTaxType.strip().upperCase();

      pMfAccount->getField( ifds::LockedIn, dstrLockedIn, idDataGroup);
      dstrLockedIn.strip().upperCase();

      pMfAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
      dstrAcctDesignation.strip();

      //pMfAccount->getField( ifds::TaxTypeRules, dstrTaxTypeRules, idDataGroup);
      //dstrTaxTypeRules.strip().upperCase();

      //pMfAccount->getField( ifds::DefTaxTypeRules, dstrDefTaxTypeRules, idDataGroup);
      //dstrDefTaxTypeRules.strip().upperCase();

      pMfAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup);
      dstrAcctType.strip();
      bool bRule1MessageSelected = false;

      if( dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE && asInteger( dstrSeqNumber ) == 1 )
      {

         if( !getWorkSession().isNonRegLike( dstrTaxType ) && dstrAcctDesignation == CLIENT_ACCT_DESIGNATION )
         {
            //Rule 1: For TaxType is B(LIF), C(LIRA) or L(LRIF) and AcctDesignation is 1(client),
            //         and LockedIn is YES, DofB should not be unknown(blank), if it is unknown,
            //         issue warning that Client's Date of Birth is missing.
            //
            if( dstrLockedIn == YES && dstrDofBirth == NULL_STRING )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING_NOCHECK );
               bRule1MessageSelected = true;
            }

            // Rule (3) in the RRIF LIF LRIF EBS V2.0.doc: 
            //          If TaxType is LIF or LRIF, validate the minimum age of the account owner against
            //          the Taxtype and shareholder->TaxJuris. If the Planholder does not meet the minimum
            //          age requirements to hold this particular registered account Type, Issue a Warning Message

            DString dstrJurisdiction;
            if( dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == RRIF_TAX_TYPE  )
            {
               DString dstrShareholderNum;
               pMfAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
               Shareholder* pShareholder;
               if( getWorkSession().getShareholder( idDataGroup, dstrShareholderNum, pShareholder )<= WARNING )
               {
                  if( pShareholder )
                  {
                     pShareholder->getField( ifds::TaxJurisCode, dstrJurisdiction, idDataGroup );
                  }
               }
            }
            else if( getWorkSession().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE || 
                     getWorkSession().isLIRALike (dstrTaxType)|| dstrTaxType == PRIF_TAX_TYPE  )
            {
               pMfAccount->getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
            }
            TaxTypeRule *pTaxTypeRule = NULL;
            pMfAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup);

            if( pTaxTypeRule && dstrDofBirth != NULL_STRING && dstrJurisdiction != NULL_STRING )
            {
               if( pTaxTypeRule->isValidPensionJurisdiction( dstrJurisdiction, idDataGroup ) )
               {
                  if( getWorkSession().isLIFLike (dstrTaxType) || dstrTaxType == LRIF_TAX_TYPE ||
                      dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == PRIF_TAX_TYPE ||
                      dstrTaxType == RLIRA_TAX_TYPE)
                  {
                     if( !pTaxTypeRule->isValidMinimumAge( dstrEntityAge, dstrJurisdiction, idDataGroup ) )
                     {
                        if (dstrTaxType == RLIRA_TAX_TYPE || dstrTaxType == RLIF_TAX_TYPE)
                        {
                           // this need to be fixed later all tax types should display error
                           // fixed tmp for rel 91
                           ADDCONDITIONFROMFILE( CND::ERR_PLANHOLDER_MINIMUM_AGE_LIMIT );
                        }
                        else if (dstrTaxType == LIF_TAX_TYPE)
                        {
                           // LIF account would depend on a new reject error 1762
                           getErrMsg ( IFASTERR::PLANHOLDER_MINIMUM_AGE_LIMIT,
                                       CND::ERR_PLANHOLDER_MINIMUM_AGE_LIMIT,
                                       CND::ERR_WARN_PLANHOLDER_MINIMUM_AGE_LIMIT,
                                       idDataGroup);
                        }
                        else
                        {
                           // Condition - Warning - "Planholder does not meet the minimum age requirements for this particular registered account"
                           ADDCONDITIONFROMFILE( CND::ERR_WARN_PLANHOLDER_MINIMUM_AGE_LIMIT );
                        }
                     }
                  }
                  // If the TaxType is LIF or LIRA or LRSP, Validate the Maxmum age of the account owner against
                  // the TaxType and ShareHolder->TaxJuris. If the Planholder does not meet the maxmum age
                  // requirements to hold this particular registered account type, Issue a Error Massage to
                  // stop user continual

                  if( getWorkSession().isLIFLike (dstrTaxType) || 
                      getWorkSession().isLIRALike (dstrTaxType) ||
                      dstrTaxType == PRIF_TAX_TYPE ) // Incident 831600 - Remove RRSP because only locked in taxtype need to check Jurisdiction
                  {
                     if( !pTaxTypeRule->isValidMaximumAge( dstrEntityAge, dstrJurisdiction, idDataGroup ) )
                     {
                        // Condition - Error - "Planholder exceeds the maximum age limit to hold for this particular registered account"
                        ADDCONDITIONFROMFILE( CND::ERR_PLANHOLDER_MAXIMUM_AGE_LIMIT );
                     }
                  }
               }
            }
         }

         //Rule 3: If TaxType is 1(RRSP), C(LIRA) or S(WILL_DEFIND) and DofB is not blank, then check
         //        if account owner already reach age 69, Issue error message with severity depending
         //        on the vew 142 as follows: Find record with ErrNum_142 = 233. 
         //
         if( ( dstrTaxType == RRSP_TAX_TYPE || getWorkSession().isLIRALike (dstrTaxType) ||
               dstrTaxType == WILL_DEFIND_TAX_TYPE ) && dstrDofBirth != NULL_STRING )
         {
            if( iEntityAge >= 72 )
            {
               long errorConID2    = CND::ERR_ACCOUNT_OWNER_AGE_OVER_69; 
               long warningConID1  = CND::ERR_WARN_ACCOUNT_OWNER_AGE_OVER_69;    

               pMfAccount->getErrMsg( I_("233"), errorConID2, warningConID1, idDataGroup ); 
            }
         }

         //Rule 4: If TaxType is one of 1,2,7,8,9,B,BR,C,CR,L,or M and AccountType is not SPOUSAL,
         //        and DofBirth( EntityType is 01, EntitySeq is 1) is unknown, issue warning
         //        that Accountholder's birth date is missing.
         //

         if( ( dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == DPSP_TAX_TYPE || 
               dstrTaxType == RPP_TAX_TYPE  || dstrTaxType == INDIVIDUAL_RESP_TAX_TYPE || 
               getWorkSession ().isIntRIFPlan (dstrTaxType) ||
               getWorkSession().isLIRALike (dstrTaxType) ||
               dstrTaxType == FAMILY_RESP_TAX_TYPE ) 
               && dstrAcctType != SPOUSAL_ACCT_TYPE )
         {
            if( dstrDofBirth == NULL_STRING && !bRule1MessageSelected )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING ); 
            }
         }
      }

      // Rule 5: If TaxType is one of 1,2,8 and AccountType is SPOUSE and DofBirth ( EntityType
      //         is 06, EntitySeq is 1) is unknown, then issue warning that spouse's birth
      //         date is missing.
      //
      if( ( dstrEntityType   == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE && asInteger( dstrSeqNumber ) == 1 ) &&
          ( dstrTaxType == RRSP_TAX_TYPE  || dstrTaxType == RRIF_TAX_TYPE || dstrTaxType == PRIF_TAX_TYPE 
           || dstrTaxType == RPP_TAX_TYPE ) && dstrAcctType == SPOUSAL_ACCT_TYPE )
      {

         if( dstrDofBirth == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_WARN_SPOUSE_BIRTHDAY_MISSING ); 
         }
      }

/*    Following code is no longer needed because above code has already handle it.
      // RRSP, LRIF, LIRA - Account Holder, Date of Birth Empty - display Warning
      if ( (dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == LIRA_TAX_TYPE || dstrTaxType == LRIF_TAX_TYPE) &&
           (dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE) )
      {
         if (dstrDofBirth.empty())
         {
            ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING );
         }
      }
*/
/*     Following logic should be put into RIF_LIF_RRIF, because during the NASU fullow, the BirthDate of the 
       Spouse has not been entered yet.
      // LIF - Account Holder or Spouse, Date of Birth Empty - display Account Holder warning or Spouse warning
      if ( (getWorkSession ().isLIFLike (dstrTaxType)) && 
         ( dstrEntityType == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE) )
      {
         if (dstrDofBirth.empty())
         {
            ADDCONDITIONFROMFILE( (dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE) ?
               CND::ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING : CND::ERR_WARN_SPOUSE_BIRTHDAY_MISSING );
         }
      } */

      if (dstrEntityType == RESP_BENEFICIARY)
      {
         DString strTaxType;
         
         pMfAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
         strTaxType.strip().upperCase();

         if ( getWorkSession ().isRES2Client() && !strTaxType.empty() && 
             (strTaxType == INDIVIDUAL_RESP_TAX_TYPE || strTaxType == FAMILY_RESP_TAX_TYPE))
         {
            if (dstrDofBirth == NULL_STRING)
            {
               getErrMsg ( IFASTERR::BENEFICIARY_DOB_MISSING,
                           CND::ERR_DOB_RESP_BENEF_REQUIRED,
                           CND::WARN_DOB_RESP_BENEF_REQUIRED,
                           idDataGroup);
            }
         }
      }

	  if (dstrTaxType == RDSP_TAX_TYPE)
	  {
		  if (!dstrDofBirth.empty())
		  {
			  validateRDSPBeneDateOfBirth (dstrDofBirth, idDataGroup);
		  }
		  else if( dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE)
		  {
			  ADDCONDITIONFROMFILE( CND::ERR_ACCTHOLDER_DOFBIRTH_MISSING );
		  }
	  }
   }

   return(GETCURRENTHIGHESTSEVERITY());
} 
//********************************************************************
void AccountEntityXrefObject::doReset (const BFDataGroupId &idDataGroup)
{
   DString entityId;
   getField (ifds::EntityId, entityId, idDataGroup);
   entityId.stripLeading( '0' );
   if (entityId.empty())
   {
      AccountEntityXref::getValueForTag (objectKey, I_("EntityId"), entityId);
   }
   if (!entityId.empty())
   {
      Entity* pEntity (NULL);
      if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING)
      {
         pEntity->reset (idDataGroup);
      }
   }
}


//******************************************************************************
void AccountEntityXrefObject::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString entityId, accountNum, entityType, seqNumber;
   getField (ifds::EntityId, entityId, idDataGroup);
   entityId.stripLeading( '0' );
   if (entityId.empty() && !objectKey.empty() )
   {
      AccountEntityXref::getValueForTag (objectKey, I_("EntityId"), entityId);
      if( !entityId.strip().empty() )
      {
         setFieldNoValidate(ifds::EntityId, entityId, idDataGroup, false);
      }
      AccountEntityXref::getValueForTag (objectKey, I_("AccountNum"), accountNum);
      if( !accountNum.strip().empty() )
      {
         setFieldNoValidate(ifds::AccountNum, accountNum, idDataGroup, false);
      }
      AccountEntityXref::getValueForTag (objectKey, I_("EntityType"), entityType);
      if( !entityType.strip().empty() )
      {
         setFieldNoValidate(ifds::EntityType, entityType, idDataGroup, false);
      }
      AccountEntityXref::getValueForTag (objectKey, I_("SeqNumber"), seqNumber);
      if( !seqNumber.strip().empty() )
      {
         setFieldNoValidate(ifds::SeqNumber, seqNumber, idDataGroup, false);
      }
   }
//MT535/MT536

   getField (ifds::EntityType, entityType, idDataGroup, false);
   if (entityType == CLEARING_PLATFORM)
   {
      DString entityId;

      getField (ifds::EntityId, entityId, idDataGroup);
      entityId.stripLeading( '0' );
      if (!entityId.empty())
      {
         Entity* pEntity (NULL);
         if (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
             pEntity)
         {
            pEntity->setField (ifds::EmployeeClass, I_("02"), idDataGroup, false);
            pEntity->setFieldReadOnly (ifds::EmployeeClass, idDataGroup, true);
            pEntity->setFieldReadOnly (ifds::LastName, idDataGroup, true);
            setFieldReadOnly (ifds::EntityType, idDataGroup, true);
         }
      }
   }

   DString dstrJointDisposition;
   getWorkSession ().getOption (ifds::JointDefaultDisposition, dstrJointDisposition, idDataGroup, false);
   setFieldNoValidate (ifds::DepositionCode, dstrJointDisposition, idDataGroup);

   DString dstrEffective;
   
   getField (ifds::EffectiveDate, dstrEffective, idDataGroup, false);

   if (dstrEffective.empty() && 
       getWorkSession().getOption (ifds::CurrBusDate, dstrEffective, idDataGroup, false) <= WARNING)
   {
      setFieldNoValidate (ifds::EffectiveDate, dstrEffective, idDataGroup, false);
   }

   MFAccount *pMFAccount = NULL;
   
   getField( ifds::AccountNum, accountNum, idDataGroup, true );
   if (getWorkSession().getMFAccount( idDataGroup, accountNum, pMFAccount ) <= WARNING)
   {
      DString dstrTaxType;
      pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
      getField( ifds::EntityType, entityType, idDataGroup, false );

      if (dstrTaxType == INDIVIDUAL_RESP_TAX_TYPE && entityType == RESP_BENEFICIARY)
      {
         setFieldNoValidate (ifds::BenPercentage, I_("100.0000"), idDataGroup, false);
      }
      else if ( dstrTaxType == FAMILY_RESP_TAX_TYPE && entityType == RESP_BENEFICIARY )
      {
         setFieldNoValidate (ifds::BenPercentage, I_("0.0000"), idDataGroup, false);
      }
   }

   DString dstrTaint;
   
   getField( ifds::Tainted, dstrTaint, idDataGroup, false );
   if (dstrTaint.empty ())
   {
      setFieldNoValidate( ifds::Tainted, I_("N"), idDataGroup, true );
   }
   setFieldReadOnly (ifds::Tainted, idDataGroup, true);
   setFieldReadOnly (ifds::TaintEndDate, idDataGroup, true);

   DString dstrTaxType;
   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
   if ( getWorkSession ().isRES2Client() && !dstrTaxType.empty() )
   {
      if ( dstrTaxType == FAMILY_RESP_TAX_TYPE  )
      {
         initSubstitutionsRelateCodeForRESP(idDataGroup);
      }
   }


   setFieldNoValidate (ifds::RefType, REF_CODE_TYPE_REGISTRATION_AGENT, idDataGroup, false);

   updateRegistrationAgentSubstitution(idDataGroup);

   /*/Enhanced for CIBC.
   MFAccount *pMFAccount = NULL;
   getField( ifds::AccountNum, acctNum, idDataGroup, true );
   if( getWorkSession().getMFAccount( idDataGroup, acctNum, pMFAccount ) <= WARNING )
   {      
	   pMFAccount->getField( ifds::AcctPurpose, strAcctPurpose, idDataGroup, false );
	   strAcctPurpose.strip().upperCase();

	   pMFAccount->getField( ifds::InTrustFor, strInTrustFor, idDataGroup );
	   strInTrustFor.strip().upperCase();

	   pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
	   strTaxType.strip().upperCase();

	   if( strAcctPurpose == YOUTH_POTFOLIO )
	   {
		   if( strInTrustFor == YES )
		   {
			   setFieldNoValidate( ifds::EntityType, ITF_INDIVIDUAL, idDataGroup, false, false, false );
		   }
		   else
			   setFieldNoValidate( ifds::EntityType, OTHER, idDataGroup, false, false, false );

   		   setFieldRequired( ifds::FirstName, idDataGroup, true );
		   setFieldRequired( ifds::LastName, idDataGroup, true );			   		   
   		   setFieldRequired( ifds::SIN, idDataGroup, true );				
  		   setFieldRequired( ifds::DofBirth, idDataGroup, true );				

		   setFieldReadOnly( ifds::EntityType, idDataGroup, true );
	   }
	   else
	   {
		   if( TaxTypeRule::isNonRegLike( strTaxType ) && strInTrustFor == YES )
		   {
			   setFieldNoValidate( ifds::EntityType, ITF_INDIVIDUAL, idDataGroup, false, false, false );
			   setFieldReadOnly( ifds::EntityType, idDataGroup, true );
		   }
	   }
   }*/

   if ( dstrTaxType == RDSP_TAX_TYPE  )
   {
	   DString dstrCurrBusDate;
	   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

	   setFieldNoValidate (ifds::RDSPConsent, I_("N"), idDataGroup);
	   setFieldNoValidate( ifds::RDSPConsentDeff, dstrCurrBusDate, idDataGroup, false );	     
   }
    
   if ( pMFAccount->isNew () && isNew () )
	   setFieldNoValidate (ifds::NASUMode, I_("Y"), idDataGroup);
   else
	   setFieldNoValidate (ifds::NASUMode, I_("N"), idDataGroup);

   initVerifyStatus (idDataGroup, false);
   _bInit = false;

}
//******************************************************************************
void AccountEntityXrefObject::getField( const BFFieldId& idField,
                                        DString& strFieldValue,
                                        const BFDataGroupId& idDataGroup,
                                        bool formattedReturn ) const
{
   if ( idField == ifds::PCGChange)
   {
      DString strPCGHost, strCurPCG;
      BFCBO::getField( ifds::RES2PCGList, strCurPCG, idDataGroup, false );
      BFCBO::getFieldBeforeImage( ifds::RES2PCGList, strPCGHost);
      
      strCurPCG.strip().upperCase();
      strPCGHost.strip().upperCase();
      
      if ( strCurPCG == strPCGHost || 
           ( strCurPCG == I_("0") && strPCGHost.empty()) )
      {
         strFieldValue = I_("N");
      }
      else
      {
         strFieldValue = I_("Y");
      }
   }
   else
   {
      BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
      if( idField == ifds::AccountBalance && formattedReturn )
      {
         DString currency;
         getField( ifds::Currency, currency, idDataGroup, false );
         currency.strip();

         BFCBO::getField( idField, strFieldValue, idDataGroup, false );
         CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
      }
      else if( idField == ifds::AccountNum )
      {
         strFieldValue.strip().stripLeading( I_CHAR( '0' ) );
      }
      else if( idField == ifds::TaxType )
      {
         strFieldValue.strip().upperCase() ;
      }
      else if( idField == ifds::AmtAssigned )
      {
         BFCBO::getField( idField, strFieldValue, idDataGroup, false );
         getFormattedAmount(idDataGroup, strFieldValue);
      }
   }
}
//********************************************************************************

void AccountEntityXrefObject::getResponseData( BFData*& pResponse )
{
   if( !_pResponseData )
      _pResponseData = new BFData(ifds::DSTC0061_VW);
   pResponse = _pResponseData;
}
//********************************************************************************

void AccountEntityXrefObject::doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPopulateField" ) );
   //for now only implement doPopulateField for view 61. Later we can extend for view 50, too
   strValue = NULL_STRING;
   DString strAccountNum, strEntityId;
   BFData* pResponse = NULL;
   getResponseData( pResponse );
   //TODO ... check what getData( DEFAULT_REPEAT_RECORD ) does. - CP 10Apr2002
   if( idField != ifds::AccountNum && 
       idField != ifds::EntityId && 
       BFData::exists( pResponse->getRepeatId(), idField ) )
   {
      if( PopulateWhereUsedForAccount(BF::HOST) <= WARNING )
         BFCBO::getField( idField, strValue, BF::HOST, formattedReturn );
   }
}
//********************************************************************************

SEVERITY AccountEntityXrefObject::getRAEntityValidTaxType(const DString& strEntityId, 
                                                          DString& dstrValidTaxType, 
                                                          const BFDataGroupId& idDataGroup,
                                                          const DString& dstrTrack,
                                                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PopulateWhereUsedForAccount" ) );

   BFData queryData(ifds::DSTC0061_REQ);
   BFData *response = new BFData(ifds::DSTC0061_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::EntityId, strEntityId  );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::WHERE_USED, 
                                             queryData, 
                                             *response, 
                                             DSTCRequestor( getSecurity(), true, true ) ) <= WARNING )
   {
      int cRepeats = response->getRepeatCount();
      for( int i = 0; i < cRepeats; i++ )
      {
         const BFData& repeat = response->getRepeat( i );
         DString dstrTaxType;
         DString strWhereUse = repeat.getElementValue( ifds::WhereUse );
         if( strWhereUse.strip() == I_("14"))
         {
            DString dstrTaxType = repeat.getElementValue( ifds::EntityType );
            dstrTaxType.strip();
            if(dstrTaxType == I_("14"))
            {
               dstrValidTaxType = I_("SA");
            }
            else if(dstrTaxType == I_("15"))
            {
               dstrValidTaxType = I_("OA");
            }
            else if(dstrTaxType == I_("16"))
            {
               dstrValidTaxType = I_("SR");
            }

            break;
         }
      }
   }
   delete response;

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************

SEVERITY AccountEntityXrefObject::PopulateWhereUsedForAccount(const BFDataGroupId& idDataGroup,
                                                              const DString& dstrTrack,
                                                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PopulateWhereUsedForAccount" ) );

   DString strEntityId, strAccountNum;
   getField(ifds::EntityId, strEntityId, idDataGroup, false);
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   strEntityId.strip().stripLeading( '0' );
   strAccountNum.strip().stripLeading( '0' );

   BFData queryData(ifds::DSTC0061_REQ);
   BFData *response = new BFData(ifds::DSTC0061_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::EntityId, strEntityId  );
   queryData.setElementValue( ifds::AccountNum, strAccountNum  ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );


   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::WHERE_USED, 
                                             queryData, 
                                             *response, 
                                             DSTCRequestor( getSecurity(), true, true ) ) <= WARNING )
   {
      DString strEntityType, strSeqNumber;
      getField(ifds::EntityType, strEntityType, idDataGroup, false);
      getField(ifds::SeqNumber, strSeqNumber, idDataGroup, false);

      int cRepeats = response->getRepeatCount();
      if( !strEntityType.strip().empty() && !strSeqNumber.strip().empty() )
      {
         for( int i = 0; i < cRepeats; i++ )
         {
            BFData* repeat = new BFData( response->getRepeat( i ));
            DString strEntType, strSeqNum;
            DString dstrTaxType;
            strEntType = repeat->getElementValue( ifds::EntityType );
            strSeqNum = repeat->getElementValue( ifds::EntityTypeSeq );
//temp - setting the ValidRATaxType based on the account tax type
            if(strEntType.strip() == ENTITY_TYPE_REG_AGENT)
            {
               DString dstrValidTaxType;
               getRAEntityValidTaxType(strEntityId, dstrValidTaxType, idDataGroup,
                                       dstrTrack, dstrPageName);
               
               //dstrTaxType = repeat->getElementValue( ifds::TaxType );
               //dstrTaxType.strip().upperCase();
               setField(ifds::ValidRATaxType, dstrValidTaxType, BF::HOST, false, false, false);
            }
//end temp - setting the ValidRATaxType based on the account tax type
            if( strEntType.strip() == strEntityType.strip() && 
                strSeqNum.strip() == strSeqNumber.strip() )
            {
               attachDataObject( *repeat, true, false );
               break;
            }
            delete repeat;
         }
      }
   }
   delete response;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
double AccountEntityXrefObject::getFundBalance ( bool& bFundValid, const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   DString dstrFundCode, dstrClassCode, dstrEffectiveDate;
   bool recordFound (false);
   double dec_fundbalance (0);

   DString accNum;
   MFAccount *pMFAccount = NULL;

   getField(ifds::EscrowFund, dstrFundCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   getField(ifds::EscrowClass, dstrClassCode, idDataGroup, false);
   dstrClassCode.strip().upperCase();

   getField(ifds::EscrowDeff, dstrEffectiveDate, idDataGroup, false);


   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )
   {
      bFundValid = false;
      return(dec_fundbalance);
   }

   bFundValid = true;

   getField( ifds::AccountNum, accNum, idDataGroup, true );
   if( getWorkSession().getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
   {
      dec_fundbalance = pMFAccount->fundClassBalance( dstrFundCode, dstrClassCode, recordFound, idField, idDataGroup, dstrEffectiveDate );
   }

   return(dec_fundbalance );
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateAmtExcessBalance ( const DString& dstrAmt, const DString& dstrAmtType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmtExcessBalance" ) );

   bool bFundValid (false);
   double dFundBalance (0);
   double dec_amount = DSTCommonFunctions::convertToDouble( dstrAmt ) ;
   DString dstrEntityType;
   SEVERITY sevRtn = NO_CONDITION;

   getField(ifds::EntityType,dstrEntityType,idDataGroup,false);

   if( dstrEntityType.strip() == ESCROW_REPRESENTATIVE || dstrEntityType.strip() == ASSIGNEE )
   {
      if( dec_amount == 0 )
         return(GETCURRENTHIGHESTSEVERITY());

      if( dstrAmtType == UNIT_AMOUNT_TYPE )
      {
         dFundBalance = getFundBalance ( bFundValid, ifds::SettledUnits, idDataGroup );
         if( bFundValid && dec_amount > dFundBalance )
         {
            DString idiStr;
            DString dstrBalance = DSTCommonFunctions::doubleToDString( ifds::SettledUnits, dFundBalance );
            DSTCommonFunctions::DisplayFormat( dstrBalance, ifds::SettledUnits );
            addIDITagValue( idiStr, I_( "SETTLEUNIT" ), dstrBalance );
            ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_ESCROW_UNITS_EXCESS_HOLDING, idiStr  );
         }
      }
      else//dollars
      {
         dFundBalance = getFundBalance ( bFundValid, ifds::SettledValue, idDataGroup );
         if ( bFundValid && fabs(dec_amount-dFundBalance)<dSmallValue)//if amount equal to fund balance, issue
            //a warning PTS 10008907
         {
            DString idiStr;
            dFundBalance = getFundBalance ( bFundValid, ifds::SettledUnits, idDataGroup );
            DString dstrBalance = DSTCommonFunctions::doubleToDString( ifds::SettledUnits, dFundBalance );
            DSTCommonFunctions::DisplayFormat( dstrBalance, ifds::SettledUnits );
            addIDITagValue( idiStr, I_( "SETTLEUNIT" ), dstrBalance );
            ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_ESCROW_AMT_EQUALS_HOLDING, idiStr  );
         }
         else if ( bFundValid && dec_amount > dFundBalance )
         {
            DString idiStr;
            DString dstrBalance = DSTCommonFunctions::doubleToDString( ifds::SettledValue, dFundBalance );
            DSTCommonFunctions::DisplayFormat( dstrBalance, ifds::SettledValue );
            addIDITagValue( idiStr, I_( "SETTLEVALUE" ), dstrBalance );
            ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_ESCROW_AMT_EXCESS_HOLDING, idiStr  );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************		
SEVERITY AccountEntityXrefObject::validateEscrowFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEscrowFundClass" ) );

   DString dstrEntityType;

   getField(ifds::EntityType,dstrEntityType,idDataGroup,false);

   if( dstrEntityType.strip() == ESCROW_REPRESENTATIVE  || dstrEntityType.strip() == ASSIGNEE )
   {
      DString strEscrowFund (NULL_STRING), strEscrowClass ( NULL_STRING );
      getField(ifds::EscrowFund, strEscrowFund, idDataGroup, false);
      getField(ifds::EscrowClass, strEscrowClass, idDataGroup, false);
      strEscrowFund.strip().upperCase();
      strEscrowClass.strip().upperCase();

      if( strEscrowFund != NULL_STRING && strEscrowClass == NULL_STRING || 
          strEscrowFund == NULL_STRING && strEscrowClass != NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_MUST_BOTH_BE_BLANK ); 
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}
//**********************************************************************************
SEVERITY AccountEntityXrefObject::getEntityMailingList( EntityAddressMailingList *&pEntityAddressMailingList, 
                                                        const BFDataGroupId& idDataGroup, bool inquireDatabase /*=true*/ ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntityMailingList" ) );
   DString accountNum,entityType,seqNumber;
   pEntityAddressMailingList = NULL;
   getField( ifds::AccountNum, accountNum, idDataGroup );
   getField( ifds::EntityType, entityType, idDataGroup );
   getField( ifds::SeqNumber, seqNumber, idDataGroup );
   entityType.strip();
   seqNumber.strip();
/*

   if(entityType == ACCOUNT_OWNER && seqNumber == I_("1") )
      return(GETCURRENTHIGHESTSEVERITY());	
*/
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pEntityAddressMailingList = dynamic_cast<EntityAddressMailingList *>( BFCBO::getObject( I_( "EntityAddressMailingList" ), idDataGroup ) );
   if( !pEntityAddressMailingList )
   {
      if( isNew() ) //check if account is new
      {
         pEntityAddressMailingList = new EntityAddressMailingList( *this );
         pEntityAddressMailingList->initNew( accountNum,entityType,seqNumber,idDataGroup);
      }
      else if( inquireDatabase ) //make the view call
      {
         pEntityAddressMailingList = new EntityAddressMailingList( *this );
         pEntityAddressMailingList->init( accountNum, entityType,seqNumber,idDataGroup);
         //if we inquire the database the group id should be the host
//CP20030319         idDataGroup = BF::HOST;
      }
      if( pEntityAddressMailingList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pEntityAddressMailingList, I_( "EntityAddressMailingList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 
         }
         else
         {
            delete pEntityAddressMailingList;
            pEntityAddressMailingList = NULL;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateEntityIDForClearingPlatformEntity (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateEntityIDForClearingPlatformEntity" ) );

   DString strEntityId;
   getField (ifds::EntityId, strEntityId, idDataGroup );

   Entity *pEntity (NULL);
   if ( getWorkSession().getEntity( idDataGroup, strEntityId, pEntity) <= WARNING && 
        pEntity)
   {
      DString employeeClass;

      pEntity->getField (ifds::EmployeeClass, employeeClass, idDataGroup, false);

      if (employeeClass == ENTITY_CATEGORY::CORPORATE) 
      {
         EntityIdsList *pEntityIdsList = NULL;

         if ( pEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
              pEntityIdsList)
         {
            BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            bool bFound = false;
            DString strIDType,
                  strIDValue; 

            while (!iter.end())
            {
               iter.getObject()->getField (ifds::IdType, strIDType, idDataGroup, false);

               if (strIDType == IDS::CLEARING_PLATFORM)
               {
                  iter.getObject()->getField (ifds::IdValue, strIDValue, idDataGroup, false);
                  bFound = true;
                  break;
               }
               ++iter;
            }

            if (!bFound)
            {
               ADDCONDITIONFROMFILE (CND::ERR_CLEARING_PLATFORM_ID_TYPE_REQUIRED);
            }
            else
            {
               if (strIDValue.empty())
               {
                  ADDCONDITIONFROMFILE (CND::ERR_CLEARING_PLATFORM_ID_VALUE_REQUIRED);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::initSubstitutionsRelateCodeForRESP(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "initSubstitutionsRelateCodeForRESP" ) );

   DString respRelateCodeSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::HRDCRelateCode, idDataGroup);

   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (respRelateCodeSubstList);

      respRelateCodeSubstList = 
         removeItemFromSubtList ( respRelateCodeSubstList, 
                                  HRDC_RELATECODE_UNCLE);
      respRelateCodeSubstList = 
         removeItemFromSubtList ( respRelateCodeSubstList, 
                                  HRDC_RELATECODE_NOT_RELATED);
      respRelateCodeSubstList = 
         removeItemFromSubtList ( respRelateCodeSubstList, 
                                  HRDC_RELATECODE_OTHER);

      setFieldAllSubstituteValues ( ifds::HRDCRelateCode, 
                                    idDataGroup, 
                                    respRelateCodeSubstList);

      // set default value
      // do not use setField because don't want validate field when user search entity and select into account
	  if (isNew())
     {
         setFieldNoValidate (ifds::HRDCRelateCode, 0, idDataGroup, false);
     }
      setFieldValid (ifds::HRDCRelateCode, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::resetSubstitutionsRelateCodeForRESP(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "resetSubstitutionsRelateCodeForRESP" ) );

   DString respRelateCodeSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::HRDCRelateCode, BF::HOST );

   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (respRelateCodeSubstList);
      setFieldAllSubstituteValues ( ifds::HRDCRelateCode, 
                                    idDataGroup, 
                                    respRelateCodeSubstList);
      // set default value
      // do not use setField because don't want validate field when user search entity and select into account
      if (isNew())
      {
         setFieldNoValidate(ifds::HRDCRelateCode, 0, idDataGroup, false);
      }
      setFieldValid( ifds::HRDCRelateCode, idDataGroup, false );
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::setEntityAssociationSubstitutions(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setEntityAssociationSubstitutions"));

    DString entityType;
    BFFieldId templateSubset;

    getField(ifds::EntityType, entityType, idDataGroup, false);

    if (entityType == RELATED_PARTY_AML_ENTITY_TYPE)
        templateSubset = ifds::EntityAssociationAML;
    else 
        templateSubset = ifds::EntityAssociation;

    BFProperties* pSubset = getFieldProperties(templateSubset, BF::HOST);
    DString dstrSubSet;
    pSubset->getAllSubstituteValues(dstrSubSet);

    setFieldAllSubstituteValues(ifds::EntityAssociation, idDataGroup, dstrSubSet);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateLangCodeForRESP(const DString& strValue,
                                                          const BFDataGroupId&  idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateLangCodeForRESP" ) );

   DString strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType,strTaxTypeFmt;
   if( !strAccountNum.empty() && 
        getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
        pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      strTaxType.strip().upperCase();
   }

   DString strEntityType;
   getField( ifds::EntityType, strEntityType, idDataGroup, false );
   if ( getWorkSession ().isRES2Client() && !strTaxType.empty() && 
      ( strTaxType == INDIVIDUAL_RESP_TAX_TYPE || strTaxType == FAMILY_RESP_TAX_TYPE ) && 
        strEntityType == RESP_BENEFICIARY )
   {
      if (strValue.empty ())
         ADDCONDITIONFROMFILE (CND::ERR_LANGUAGE_MUST_BE_ENTERED);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateRESPBenefAlloc( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateRESPBenefAlloc" ) );

   DString strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType,strTaxTypeFmt;
   if( !strAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      pMFAccount->getField( ifds::TaxType, strTaxTypeFmt, idDataGroup, true );
      strTaxType.strip().upperCase();
   }

   if ( !getWorkSession ().isRES2Client() || strTaxType.empty() || 
        !( strTaxType == INDIVIDUAL_RESP_TAX_TYPE || strTaxType == FAMILY_RESP_TAX_TYPE)  )
   {
      // not QESI support env and tax type is neither 9,M ... do nothing.
      return(GETCURRENTHIGHESTSEVERITY());
   }
   
   if ( !getWorkSession().isQESIClient() && ( strTaxType == FAMILY_RESP_TAX_TYPE ) && 
        !getWorkSession().hasUpdatePermission( UAF::RESP_ALLOCATION ) )
   {
      // Tax type is M and user has no permission
      // on updating beneficiary allocation... do nothing, as well.
      return(GETCURRENTHIGHESTSEVERITY());
   }
   

   // only positive number is allowed
   I_CHAR *stopstring;

   // total sum of resp benef allocation must be 100.
   AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );

   if ( pAccountEntityXref )
   {
      BFObjIter iterAccountEntityXref (*pAccountEntityXref, 
                                        idDataGroup, 
                                        true, 
                                        BFObjIter::ITERTYPE::NON_DELETED);

      DString strEntityTypeFmt, strEntityId;
      getField (ifds::EntityId, strEntityId, idDataGroup, false);
      strEntityId.strip().upperCase();

      DString strEntityType, strCurrAccountNum;
      getField (ifds::EntityType, strEntityType, idDataGroup, false);
      double dTotalPercent = 0;
      iterAccountEntityXref.begin ();

      int iNumRESPBenef = 0, iNumOlder21 = 0;
      while (!iterAccountEntityXref.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

         pObj->getField (ifds::EntityType, strEntityType, idDataGroup, false);
         pObj->getField (ifds::EntityType, strEntityTypeFmt, idDataGroup, true);
		 pObj->getField (ifds::AccountNum, strCurrAccountNum, idDataGroup, false);

         if ( strAccountNum == strCurrAccountNum && strEntityType == RESP_BENEFICIARY )
		 {
            DString strAllocPrcnt, strObjEntityId, strDOB, strCurrentDate,
                    strYears, strMonths;

            pObj->getField (ifds::BenPercentage, strAllocPrcnt, idDataGroup, false);
            pObj->getField (ifds::DofBirth, strDOB, idDataGroup, false);
            pObj->getField (ifds::EntityId, strObjEntityId, idDataGroup, false);
            getWorkSession().getDateInHostFormat( strCurrentDate, 
                                                  DSTCWorkSession::CURRENT_SYSTEM_DAY, 
                                                  idDataGroup );
            DSTCommonFunctions::BuildAge( strDOB, strCurrentDate, strYears, strMonths );

            strObjEntityId.strip().upperCase();

            double dAgeYears = 0, dAgeMonths = 0;
            strAllocPrcnt.strip().stripAll( I_CHAR( ',' ) );

            dTotalPercent += wcstod( strAllocPrcnt.c_str(), &stopstring );
            dAgeYears = wcstod( strYears.c_str(), &stopstring );
            iNumRESPBenef++;

            if ( dAgeYears >= 21 )
            {
               iNumOlder21++;
            }

         }

         ++iterAccountEntityXref;
      }
      
      // all of the are older than 21, then benef percent may be 0
      if( iNumOlder21 != iNumRESPBenef )
      {
         if( fabs( dTotalPercent - 100 ) > .0000000001 )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100 );
         }
      }
      else
      {
         if ( dTotalPercent < 0 ||
              dTotalPercent > 100 ||
              ( dTotalPercent > 0 && dTotalPercent < 100 )
            )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100 );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateIDForRESPEntity( const DString& strIDType, 
                                                           const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateIDForRESPEntity" ) );

   DString strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType;
   if( !strAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      strTaxType.strip().upperCase();
      //if( strTaxType != FAMILY_RESP_TAX_TYPE)
	  if ( DSTCommonFunctions::codeInList(strTaxType,I_("9,M,RS")) == false )
		return GETCURRENTHIGHESTSEVERITY();
   }

   DString strEntityId;
   getField (ifds::EntityId, strEntityId, idDataGroup );

   Entity *pEntity (NULL);
   if ( getWorkSession().getEntity( idDataGroup, strEntityId, pEntity) <= WARNING && 
        pEntity)
   {
      EntityIdsList *pEntityIdsList = NULL;

      if ( pEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
           pEntityIdsList)
      {
         BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         bool bFound = false;
         DString strObjIDType,
                 strObjIDValue; 

         while (!iter.end())
         {
            iter.getObject()->getField (ifds::IdType, strObjIDType, idDataGroup, false);

            if ( strIDType == strObjIDType)
            {
               iter.getObject()->getField (ifds::IdValue, strObjIDValue, idDataGroup, false);
               if ( strIDType == IDS::SIN )
               {
                  DString strSIN, strEntityType, strEntityID;

                  pEntity->getField (ifds::SIN, strSIN, idDataGroup, false);
                  getField(ifds::EntityId, strEntityID, idDataGroup, false);
                  getField(ifds::EntityType, strEntityType, idDataGroup, false);
                  EntityIds::validateSIN( getWorkSession(),
                                          strTaxType, 
                                          strEntityType, 
                                          strSIN,
                                          strEntityID,
                                          idDataGroup);
               }
               else if ( strObjIDType == IDS::BUSINESS_NUMBER )
               {
                  bFound = true;
                  DString strIDValue, strEntityType, strEntityID;
                  getField(ifds::EntityType, strEntityType, idDataGroup, false);
                  getField(ifds::EntityId, strEntityID, idDataGroup, false);
                  if ( !strObjIDValue.empty() )
                  {
                     DString strPCGSIN = strObjIDValue.left(9);
                     EntityIds::validateIDTypeValueEntity( getWorkSession(), 
                                                           strEntityType,
                                                           strEntityID,
                                                           strTaxType,
                                                           strIDType,
                                                           strPCGSIN,
                                                           idDataGroup );
                     // validate against system existing
                     EntityIds* pEntityIds = dynamic_cast<EntityIds*>(iter.getObject());

                     if ( pEntityIds && isNew() )
                     {
                        pEntityIds->validatePCGAgainstSystem(strObjIDValue,idDataGroup);
                     }
                  }
                  else
                  {
                     // add condition PCG Business is missing
                     DString idiString;
                     addIDITagValue (idiString, I_("ID_VALUE"), I_("PCG Business Number"));
                     addIDITagValue (idiString, I_("ENTITY_ID"), strEntityID);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_NO_VALUE_FOR_ID, idiString);
                  }
               }

               break;
            }
            ++iter;
         }
         
         if( !bFound )
         {
            DString strEntityType, strEntityID;
            getField(ifds::EntityType, strEntityType, idDataGroup, false);
            getField(ifds::EntityId, strEntityID, idDataGroup, false);

			DString dstrEmployeeClass;
			pEntity->getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false);

            if ( (strEntityType.strip().upperCase() == RESP_PCG_INST || 
				 (strTaxType == RDSP_TAX_TYPE && (strEntityType.strip().upperCase() == RDSP_PCG || strEntityType.strip().upperCase() == ACCOUNT_OWNER) && dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE)) && 
                  strIDType == IDS::BUSINESS_NUMBER )
            {
               if ( !strObjIDValue.empty() )
               {
                  DString strPCGSIN = strObjIDValue.left(9);
                  EntityIds::validateIDTypeValueEntity( getWorkSession(), 
                                                        strEntityType,
                                                        I_(""),
                                                        strTaxType,
                                                        strIDType,
                                                        strPCGSIN,
                                                        idDataGroup );
               }
               else
               {
                  // add condition PCG Business is missing
                  DString idiString;
				  if (strTaxType == RDSP_TAX_TYPE && strEntityType.strip().upperCase() == ACCOUNT_OWNER)
					  addIDITagValue (idiString, I_("ID_VALUE"), I_("Account Owner Business Number"));
				  else
					  addIDITagValue (idiString, I_("ID_VALUE"), I_("PCG Business Number"));
                  addIDITagValue (idiString, I_("ENTITY_ID"), strEntityID);
                  ADDCONDITIONFROMFILEIDI (CND::ERR_NO_VALUE_FOR_ID, idiString);
               }
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AccountEntityXrefObject::validateSINDuplicateForRESP( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateSINDuplicateForRESP" ) );

   // This method is used for validate SIN number when user put SIN number and change entitytype
   // logic is almost similar to EntityIds
   // May be it is not best soltion, but it's work.

   DString strAccountNum;
   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType;
   if( !strAccountNum.empty() && 
        getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
        pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      strTaxType.strip().upperCase();
      if( strTaxType != FAMILY_RESP_TAX_TYPE )
         return GETCURRENTHIGHESTSEVERITY();
   }
   
   DString dstrEntityType, dstrEntityId, dstrSIN;
   getField( ifds::EntityType, dstrEntityType, idDataGroup, false );
   getField( ifds::EntityId, dstrEntityId, idDataGroup, false);
   // get SIN number for this entity
   Entity *pEntity = NULL;
   if (getWorkSession().getEntity (idDataGroup, 
                                   dstrEntityId.strip(), pEntity) <= WARNING && 
       pEntity)
   {
      EntityIdsList* pEntityIdsList = NULL;
      pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false); 
      // search for SIN of opposite entity
      if (pEntityIdsList)
      { 
         BFObjIter bfIterIds (*pEntityIdsList, idDataGroup, false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);

         bfIterIds.begin();
         DString strIdType;
         while (!bfIterIds.end())
         {
            bfIterIds.getObject()->getField (ifds::IdType, strIdType, idDataGroup, false);
            if (strIdType == IDS::SIN)
            {
               bfIterIds.getObject()->getField (ifds::IdValue, dstrSIN, idDataGroup, false);
               break;
            }
            ++bfIterIds;
         }
         
      }

   }
   // if sin is blank there should be error like SIN missing,
   // it shouldn't populate the error like SIN is same as some entity
   if ( dstrSIN.empty() )
      return GETCURRENTHIGHESTSEVERITY();

   AccountEntityXref *pAcctEXrefForOpposite = NULL;
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAcctEXrefForOpposite) <= WARNING &&
       pAcctEXrefForOpposite)
   {
      BFObjIter oppositeIter (*pAcctEXrefForOpposite, idDataGroup, true, 
                               BFObjIter::ITERTYPE::NON_DELETED);
      oppositeIter.begin();
      while( !oppositeIter.end() )
      {
         AccountEntityXrefObject* pOppositeObj = dynamic_cast<AccountEntityXrefObject*>(oppositeIter.getObject());
         DString dstrOppEntityType;
         pOppositeObj->getField(ifds::EntityType, dstrOppEntityType, idDataGroup);
         
         if ( (dstrEntityType == ACCOUNT_OWNER && dstrOppEntityType == RESP_BENEFICIARY) ||
              (dstrEntityType == RESP_BENEFICIARY && dstrOppEntityType == ACCOUNT_OWNER)
            )
         {
            DString dstrOppSIN, dstrOppEntityId;
            // create opposite ids list
            pOppositeObj->getField(ifds::EntityId, dstrOppEntityId, idDataGroup);

            Entity *pOppEntity = NULL;
            if (getWorkSession().getEntity (idDataGroup, 
                                            dstrOppEntityId.strip(), pOppEntity) <= WARNING && 
                pOppEntity)
            {

               EntityIdsList* pOppEntityIdsList = NULL;
               pOppEntity->getEntityIdsList (pOppEntityIdsList, idDataGroup, false);   
               // search for SIN of opposite entity
               if (pOppEntityIdsList)
               { 
                  BFObjIter bfOppIterIds (*pOppEntityIdsList, idDataGroup, false, 
                                           BFObjIter::ITERTYPE::NON_DELETED);

                  bfOppIterIds.begin();
                  while (!bfOppIterIds.end())
                  {
                     DString strOppIdType, 
                             strOppSIN;
                     
                     bfOppIterIds.getObject()->getField (ifds::IdType, strOppIdType, idDataGroup, false);
                     if (strOppIdType == IDS::SIN)
                     {
                        bfOppIterIds.getObject()->getField (ifds::IdValue, strOppSIN, idDataGroup, false);
                        
                        // if sins are duplicate
                        if ( dstrSIN == strOppSIN )
                        {
                           DString strEntityTypeFmt, strOppEntityTypeFmt;
                           getField (ifds::EntityType, strEntityTypeFmt, idDataGroup, true);
                           pOppositeObj->getField (ifds::EntityType, strOppEntityTypeFmt, idDataGroup, true);
                           
                           DString dstrTemp;
                           addIDITagValue( dstrTemp, I_("ENTITY_1"), strEntityTypeFmt );
                           addIDITagValue( dstrTemp, I_("ENTITY_2"), strOppEntityTypeFmt );

                           getErrMsg ( IFASTERR::DUPLICATE_SIN, 
                                       CND::ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2, 
                                       CND::WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2, 
                                       idDataGroup,
                                       dstrTemp); 
                           break;
                        }
                     }
                     ++bfOppIterIds;
                  }

               }
            }
         }
         ++oppositeIter;
      }
   }


   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AccountEntityXrefObject::setFieldSubSetForRESPEntity(const DString& strEntityType,
                                                              const DString& strSubset,
                                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "setFieldSubSetForRESPEntity" ) );

   DString strObjEntityType;
   getField (ifds::EntityType, strObjEntityType, idDataGroup, false);

   if( !strSubset.empty() ) // allow to update list even entity is not RESP related
   {
      BFFieldId fieldId;
      if ( strEntityType == RESP_PCG_INDIV || strEntityType == RESP_PCG_INST )
      {
         fieldId = ifds::RES2PCGList;
      }
      else if ( strEntityType == PARENT_GUARDIAN )
      {
         fieldId = ifds::RES2ParentLglList;
      }
      else if ( strEntityType == RESP_DSGN_INST )
      {
         fieldId = ifds::RES2DesInstList;
      }


      if( fieldId == ifds::RES2PCGList || fieldId == ifds::RES2ParentLglList ||
          fieldId == ifds::RES2DesInstList )
      {
         BFProperties *pBFProperties = 
            getFieldProperties (fieldId, idDataGroup);

         assert (pBFProperties);
         if (pBFProperties)
         {
            setFieldAllSubstituteValues ( fieldId, idDataGroup, strSubset);
            setFieldAllSubstituteValues ( fieldId, BF::HOST, strSubset);

            setFieldValid( fieldId, idDataGroup, false);
            setFieldValid( fieldId, BF::HOST, false);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::refreshSelectableListForRESP(const DString& strEntityType,
                                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "refreshSelectableListForRESP" ) );

   DString strSelectableList;
   if ( strEntityType == RESP_PCG_INDIV || strEntityType == RESP_PCG_INST )
   {
      DString strPCGIndivList, strPCGInstList;

      // make list of RESP_PCG_INDIV and RESP_PCG_INST
      buildEntitySSList(RESP_PCG_INDIV,strPCGIndivList, idDataGroup);
      buildEntitySSList(RESP_PCG_INST,strPCGInstList, idDataGroup);

      strSelectableList  = I_("0= ;");
      strSelectableList += strPCGIndivList;
      strSelectableList += strPCGInstList;

      setFieldSubSetForRESPEntity(RESP_PCG_INDIV,strSelectableList,idDataGroup);
   }
   else 
   {
      DString strEntitySSetList;
      strSelectableList  = I_("0= ;");
      buildEntitySSList(strEntityType,strEntitySSetList,idDataGroup);
      strSelectableList += strEntitySSetList;
      setFieldSubSetForRESPEntity(strEntityType,strSelectableList,idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::buildEntitySSList(const DString& strEntityType, 
                                                    DString& strSelectableList, 
                                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "buildEntitySSList" ) );

   AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );

   if ( pAccountEntityXref )
   {
      BFObjIter iterAccountEntityXref (*pAccountEntityXref, 
                                        idDataGroup, 
                                        true, 
                                        BFObjIter::ITERTYPE::NON_DELETED);

      iterAccountEntityXref.begin ();

      while (!iterAccountEntityXref.end())
      {
         DString strObjKey = iterAccountEntityXref.getStringKey ();

         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

         DString strObjEntityType , strObjEntityId, strObjSeqNumber;

         pObj->getField (ifds::EntityType, strObjEntityType, idDataGroup, false);
         pObj->getField (ifds::EntityId, strObjEntityId, idDataGroup, false);
         pObj->getField (ifds::SeqNumber, strObjSeqNumber, idDataGroup, false);
         strObjEntityType.strip().upperCase();

         if ( strObjEntityType == strEntityType )
         {
            DString strLastName, strFirstName, strSubstitue = NULL_STRING;
            pObj->getField (ifds::LastName, strLastName, idDataGroup, false);
            pObj->getField (ifds::FirstName, strFirstName, idDataGroup, false);
            if ( strObjEntityType == PARENT_GUARDIAN || strObjEntityType == RESP_DSGN_INST )
            {
               strSubstitue += strObjSeqNumber;
            }
            else
            {
               strSubstitue += strObjEntityId;
            }

            strSubstitue += I_("=");
            strSubstitue += strLastName;
            strSubstitue += I_(",");
            strSubstitue += strFirstName;
            strSubstitue += I_(";");
            strSelectableList += strSubstitue;
         }

         ++iterAccountEntityXref;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validatePCGDelink (const DString& strValue,
                                                     const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validatePCGDelink" ) );

   DString strPCGOld, 
      strPCGNew(strValue);
   getField (ifds::RES2PCGList, strPCGOld, BF::HOST, false);
   strPCGOld.strip().upperCase();
   strPCGNew.strip().upperCase();

   if (strPCGOld != strPCGNew /*&& !strPCGOld.empty() && strPCGOld != I_("0")*/)
   {
      DString strGrantExists;
      getField (ifds::GrantExists, strGrantExists, idDataGroup, false);
      strGrantExists.strip().upperCase();

      if (strGrantExists == I_("Y"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_DELINK_PCG_WITH_RESP_BENEF_HAS_GRANT);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateTaxJurisForRESP (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateTaxJurisForRESP" ) );

   // This method will check the taxjuris for resp benefiary,
   // if there is any taxjuris equal to blank or unassign or there are not sync up, error will be appeared.
   DString dstrEntityType;
   getField( ifds::EntityType, dstrEntityType, idDataGroup, false );

   if ( dstrEntityType == PRIMARY_BENEFICARY ||
        dstrEntityType == SECONDARY_BENEFICARY ||
        dstrEntityType == RESP_BENEFICIARY )
   {
      // taxjuris code is contained in view 50, It's taxjuris for resp ben entity level
      DString dstrEntityId, dstrTaxJurisCode;
      getField( ifds::EntityId, dstrEntityId, idDataGroup, false );
      getField( ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup, false );

      Entity *pEntity (NULL);
      if ( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity) <= WARNING && 
            pEntity)
      {
         // taxjuris is contained in view 51, It's taxjuris for entity level
         DString dstrTaxJuris;
         pEntity->getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);

         if ( dstrEntityType == RESP_BENEFICIARY )
         {
            if ( dstrTaxJurisCode == NULL_STRING ||
                  dstrTaxJurisCode == UNASSIGNED_COUNTRY ||
                  dstrTaxJuris == NULL_STRING ||
                  dstrTaxJuris == UNASSIGNED_COUNTRY ||
                  dstrTaxJurisCode != dstrTaxJuris )
            {
               ADDCONDITIONFROMFILE (CND::ERR_TAX_JURIS_INVALID);
            }
         }
         else
         {
            // For Primary and Secondary Ben, TaxJuris can be unassign or blank,
            // But they should be synced up.
            if ( dstrTaxJurisCode != dstrTaxJuris )
            {
               ADDCONDITIONFROMFILE (CND::ERR_TAX_JURIS_INVALID);
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validatePCGList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePCGList" ) );
   
   if ( getWorkSession ().isRES2Client() )
   {
      int iEntityAge = getEntityAge( idDataGroup ); 
            
      if ( iEntityAge < 19 )
      {
         DString strParentLgl;
         getField( ifds::RES2ParentLglList, strParentLgl, idDataGroup, false );
         strParentLgl.strip().upperCase();

         if ( strParentLgl.empty() || strParentLgl == I_("0") )
         {
            ADDCONDITIONFROMFILE(CND::ERR_INVALID_VALUE_FOR_PARENT_LEGAL_GUARDIAN);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AccountEntityXrefObject::isLinkedToRESPBenef ( const DString& strEntityId,
                                                    const BFDataGroupId& idDataGroup)
{
   bool bResult = false;

   AccountEntityXref *pAccountEntityXref = 
      dynamic_cast < AccountEntityXref * > ( getParent() );

   if( pAccountEntityXref )
   {
      BFObjIter iterAccountEntityXref( *pAccountEntityXref, 
                                        idDataGroup, 
                                        true, 
                                        BFObjIter::ITERTYPE::NON_DELETED );

      iterAccountEntityXref.begin();
      while (!iterAccountEntityXref.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

         DString strEntityType;
         pObj->getField( ifds::EntityType, strEntityType, idDataGroup, false);
         strEntityType.strip().upperCase();

         if ( strEntityType == RESP_BENEFICIARY )
         {
            DString strRES2PCG;
            pObj->getField( ifds::RES2PCGList, strRES2PCG, idDataGroup, false );
            strRES2PCG.strip().upperCase();

            if ( strRES2PCG == strEntityId )
            {
               bResult = true;
               break;
            }
         }

         ++iterAccountEntityXref;
      }
   }

   return bResult;
}

//***********************************************************************************************
int AccountEntityXrefObject::getEntityAge (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityAge"));

   // including search for basedOn
   int basedOn = 0;

   DString dstrAcctNum;
   getField( ifds::AccountNum, dstrAcctNum, idDataGroup, true );

   MFAccount *pMfAccount = NULL;
   if ( getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMfAccount ) <= WARNING )
   {
      TaxTypeRule *pTaxTypeRule = NULL;
      pMfAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup);
      
      if( pTaxTypeRule )
      {
         DString dstrJurisdiction;

         pMfAccount->getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
         pTaxTypeRule->getAgeCalcBasedOn (basedOn, dstrJurisdiction, idDataGroup);
      }     
   }

   // basedOn = 0 user current business day
   // basedOn = 1 use Dec 31 of the current year
   // basedOn = 2 use Jan 1 of the current year
   DString dstrCurrentDate;
   DString dstrDate;
   DString dstrAsOfDate;
   DString dstrAsOfDec31, dstrAsOfJan1;
   DString dstrCurrentYear;

   dstrAsOfDec31 = I_("1231");
   dstrAsOfJan1 = I_("0101");

   getWorkSession ().getOption (ifds::CurrSysDate, dstrCurrentDate, idDataGroup, false);

   DString dstrBirthDate = NULL_STRING, dstrAge, dstrMonth, dstrEntityId;

   getField( ifds::EntityId, dstrEntityId, idDataGroup );
   Entity* pEntity;

   if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
   {
      pEntity->getField( ifds::DofBirth, dstrBirthDate, idDataGroup );
   }

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
//***********************************************************************************************
void AccountEntityXrefObject::setEscrowRelatedDate (const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setEscrowRelatedDate"));
   // set EscrowDeff because if the Model entity is not Escrow, EscrowDeff is NULL,
   // so it's not valid for escrow deff. Condition will be added. Copy logic from doApplyRelatedChanges().
   if( idField == ifds::EscrowStopDate )
   {
      DString dstrDateHostFmt;
      getWorkSession().getDateInHostFormat(dstrDateHostFmt, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
      setFieldNoValidate( ifds::EscrowStopDate, dstrDateHostFmt, idDataGroup, false, true, false ); 
   }
   else
   {
      DString strCurrBussinesDate;
      if( getWorkSession().getOption( ifds::CurrBusDate, strCurrBussinesDate, idDataGroup, false ) <= WARNING )
      {
         setFieldNoValidate( ifds::EscrowDeff, strCurrBussinesDate, idDataGroup, false, true, true );
      }
   }
   
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateClearingPlatform( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClearingPlatform" ) );
   
   DString dstrEntityId;
   getField (ifds::EntityId, dstrEntityId, idDataGroup);
   dstrEntityId.strip().stripLeading( '0' );
   if (!dstrEntityId.empty())
   {
      Entity* pEntity (NULL);
      if (getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity) <= WARNING && 
           pEntity)
      {
         EntityIdsList* pEntityIdsList (NULL);

         if (pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, true) <= WARNING &&
              pEntityIdsList)
         {                  
            BFObjIter iter ( *pEntityIdsList, 
                             idDataGroup, 
                             true);
               
            while (!iter.end())
            {
               EntityIds *pEntityIds = dynamic_cast <EntityIds *> (iter.getObject());

               if (pEntityIds)
               {
                  DString dstrIdType;
                  pEntityIds->getField(ifds::IdType, dstrIdType, idDataGroup, false);
                  
                  if(dstrIdType == IDS_CLEARING_PLATFORM)
                  {
                     DString dstrEntityType;
                     getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
                     
                     if(dstrEntityType != CLEARING_PLATFORM)
                     {
                        ADDCONDITIONFROMFILE (CND::ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY);
                     }
                  }
               }
               ++iter;
            }
         }
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateDofBirthForRESPBenef( const DString& strEntityDOfB, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateDofBirthForRESPBenef" ) );

   //validate for QESI clients
   if ( !getWorkSession ().isQESIClient() )
   {
      return GETCURRENTHIGHESTSEVERITY ();
   }
   
   DString strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType;
   if( !strAccountNum.empty() && 
        getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
        pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      strTaxType.strip().upperCase();
      if ( DSTCommonFunctions::codeInList(strTaxType,I_("9,M")) == false )
         return GETCURRENTHIGHESTSEVERITY();
   }

   //------------------------------------------------------
   //PET165541.FN03.R3.3 - Display EW msg for Changing of Year of DofBirth
   validateYearOfBirthForRESPBenf(strEntityDOfB,idDataGroup); 
   //PET165541.FN03.R3.4 - Validate if updated DofBirth is earlier than SIN effective date
   //validateDofBirthAgainstSINIdDateForRESPBenf(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateDofBirthAgainstSINIdDateForRESPBenf(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateDofBirthAgainstSINIdDateForRESPBenf" ) );

   if ( !getWorkSession ().isQESIClient() )
   {
      return GETCURRENTHIGHESTSEVERITY ();
   }
   //validate updated DofBirth against SIN effective date
   // -- search in EntityIds find EntityId match, 
   // -- then validate SIN IdDate for that Entity whose DofB updated   
   DString dstrEntityType,
      dstrEntityId,
      dstrDofBirth,
      dstrSINIdDate,
      dstrWarnCode = NULL_STRING; 

   getField(ifds::EntityType, dstrEntityType, idDataGroup, false);

   if(dstrEntityType != RESP_BENEFICIARY)
      return GETCURRENTHIGHESTSEVERITY();  

   getField(ifds::EntityId, dstrEntityId, idDataGroup);  
   
   // get SIN effective date of the entity (whose DofB is updated)
   Entity *pEntity = NULL;
   if (getWorkSession().getEntity (idDataGroup, 
                                   dstrEntityId.strip(), pEntity) <= WARNING && 
       pEntity)
   {
      EntityIdsList* pEntityIdsList = NULL;
      pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false); 
	  pEntity->getField(ifds::DofBirth, dstrDofBirth, idDataGroup);
      // search for its SIN effective date
      if (pEntityIdsList)
      { 
         BFObjIter bfIterIds (*pEntityIdsList, idDataGroup, false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);

         bfIterIds.begin();
         DString dstrIdType;
         while (!bfIterIds.end())
         {
            bfIterIds.getObject()->getField (ifds::IdType, dstrIdType, idDataGroup, false);
            if (dstrIdType == IDS::SIN)
            {
               bfIterIds.getObject()->getField (ifds::IdDate, dstrSINIdDate, idDataGroup, false);
               break;
            }
            ++bfIterIds;
         }
         
      }

   }

   DString dstrCurrBussinesDate;
   MgmtCoOptions *pMgmtCoOptions = NULL;
   getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   if( pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false );

   }
   pMgmtCoOptions = NULL;

   DString str12319999;
   getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   if( dstrSINIdDate == NULL_STRING || dstrSINIdDate == str12319999)
   {
      getErrMsg(IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN,
                idDataGroup);
   }
   else if(DSTCommonFunctions::CompareDates (dstrSINIdDate, dstrDofBirth) ==  DSTCommonFunctions::FIRST_EARLIER)
   {
      getErrMsg(IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB,
                idDataGroup);
   }
   else if(DSTCommonFunctions::CompareDates (dstrSINIdDate, dstrCurrBussinesDate) ==  DSTCommonFunctions::SECOND_EARLIER)
   {
      //dstrWarnCode = IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;

      getErrMsg(IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE,
                idDataGroup);
   }

   //displayRESPError(dstrWarnCode, idDataGroup);	

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//QESI3FN03
SEVERITY AccountEntityXrefObject::doInitSINWithDofBirthForRESPBenf(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doInitSINWithDofBirthForRESPBenf" ) );

   if ( !getWorkSession ().isQESIClient() )
   {
      return GETCURRENTHIGHESTSEVERITY ();
   }

   DString strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   MFAccount *pMFAccount = NULL;

   DString strTaxType;
   if( !strAccountNum.empty() && 
         getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && 
         pMFAccount)
   {
      pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
      strTaxType.strip().upperCase();
      if ( DSTCommonFunctions::codeInList(strTaxType,I_("9,M")) == false )
         return GETCURRENTHIGHESTSEVERITY();
   }
   //------------------------------------------------------
   DString strEntityId;
   getField (ifds::EntityId, strEntityId, idDataGroup );
   
   Entity *pEntity (NULL);
   if ( getWorkSession().getEntity( idDataGroup, strEntityId.strip(), pEntity) <= WARNING && 
        pEntity)
   {
      EntityIdsList *pEntityIdsList = NULL;

      if ( pEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING && 
           pEntityIdsList)
      {
         BFObjIter iter (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         DString strObjIDType;

         while (!iter.end())
         {
            iter.getObject()->getField (ifds::IdType, strObjIDType, idDataGroup, false);

            if ( strObjIDType == IDS::SIN)
            {
                DString strSIN, strEntityType;

                getField(ifds::EntityType, strEntityType, idDataGroup, false);

                if (strEntityType == RESP_BENEFICIARY)
                {
                   DString dstrDofBirth;
                   getField(ifds::DofBirth, dstrDofBirth, idDataGroup );
                   if(!dstrDofBirth.empty()) 
                   {  //Req1: default SIN IdDate with DOB
                      EntityIds* pEntityIds = dynamic_cast<EntityIds*>(iter.getObject());

                      if ( pEntityIds )
                      {
                         DString dstrIdDate, str12319999;
                         iter.getObject()->getField (ifds::IdDate, dstrIdDate, idDataGroup, false);                                 
                         getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
						
						  //P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown'.
						  // fix: Default SIN DATE with DOB when user selects EntityType = RESP_BENF after updating DOB
						  //      Do not default SIN Date if user sets up the value
                         if(dstrIdDate.empty() || dstrIdDate == str12319999)
                         {
                            pEntityIds->doInitIdDate(strEntityType, IDS::SIN, dstrDofBirth, idDataGroup);
                         }
                      }
                  }
               }//end - if (strEntityType == RESP_BENEFICIARY)
            }// end - if ( strObjIDType == IDS::SIN)
            ++ iter;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//QESI3FN03
SEVERITY AccountEntityXrefObject::validateYearOfBirthForRESPBenf(const DString& strEntityDOfB, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateYearOfBirthForRESPBenf" ) );

   DString dstrDofBirthReEntry(strEntityDOfB), dstrYearOfBirthReEntry;
   //get the re-entry of birth year
   //getField(ifds::DofBirth, dstrDofBirthReEntry, idDataGroup );
   dstrDofBirthReEntry.strip();

   if( dstrDofBirthReEntry.empty() )
   {
      getErrMsg ( IFASTERR::BENEFICIARY_DOB_MISSING,
                  CND::ERR_DOB_RESP_BENEF_REQUIRED,
                  CND::WARN_DOB_RESP_BENEF_REQUIRED,
                  idDataGroup);
   }
   else
   {
      //get previous DoB
      DString dstrDofBirth;
      getField(ifds::DofBirth, dstrDofBirth, BF::HOST  );
	  if(!dstrDofBirth.empty())
	  {
		  DString dstrYearOfBirth;

		  int year_pos = DSTCommonFunctions::getYearPosition();
		  dstrYearOfBirthReEntry.assign(dstrDofBirthReEntry,year_pos,4);
		  dstrYearOfBirth.assign(dstrDofBirth,year_pos,4);

		  if (dstrYearOfBirth != dstrYearOfBirthReEntry)
		  {
			 //call vew415
			 getEWIMsgforRESPBenfDofBirthUpdate(idDataGroup);
		  }
	  }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::getEWIMsgforRESPBenfDofBirthUpdate( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEWIMsgforRESPBenfDofBirthUpdate" ) );
//call for VEW415 to issue EW msg
   DString dstrEntityType, 
      dstrEntityID;

   getField (ifds::EntityType,dstrEntityType, idDataGroup, false);
   getField (ifds::EntityId, dstrEntityID, idDataGroup, false);

   if (dstrEntityType == RESP_BENEFICIARY)
   {
      DString dstrAccountNum,
              dstrTransID = NULL_STRING, 
              dstrNewTaxJuris = NULL_STRING, 
              dstrNewSibling = I_("N"), 
              dstrValidateType = I_("DOFB"), 
              dstrBenefIdList = dstrEntityID;

      getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
//have to create the validation object always since user can change DOB
      RESPInfoUpdateValidationList respInfoUpdateValidationList (*this);

      if (respInfoUpdateValidationList.init (dstrAccountNum,
                                             dstrTransID,
                                             dstrNewTaxJuris,
                                             dstrNewSibling,
                                             dstrValidateType,
                                             dstrBenefIdList,
                                             idDataGroup) <= WARNING)
      {
         respInfoUpdateValidationList.displayAllRESPError (idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//IN2780013 - SOC Loan Number and Loan Type
SEVERITY AccountEntityXrefObject::validateLoanTypeLoanNumberForEscrow( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLoanTypeLoanNumberForEscrow" ) );
   // validate either load type or loan number is not empty.
   DString EntityType;
   getField(ifds::EntityType,EntityType,idDataGroup,false);
   EntityType.strip();

   if (EntityType == ESCROW_REPRESENTATIVE)
   {
      DString dstrLoanType,
         dstrLoanNumber;

      getField (ifds::LoanNumber, dstrLoanNumber, idDataGroup, false);
      getField (ifds::LoanType, dstrLoanType, idDataGroup, false);

      if(!dstrLoanType.empty())
      {
         if(dstrLoanNumber.empty())
         {
            getErrMsg ( IFASTERR::LOAN_NUM_MANDATORY,
                        CND::ERR_LOAN_NUM_MANDATORY,
                        CND::WARN_LOAN_NUM_MANDATORY,
                        idDataGroup ); 
         }
      }
      else
      {
         getErrMsg ( IFASTERR::LOAN_TYPE_MANDATORY,
                     CND::ERR_LOAN_TYPE_MANDATORY,
                     CND::WARN_LOAN_TYPE_MANDATORY,
                     idDataGroup ); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateDuplicatedLoanTypeForEscrow ( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDuplicatedLoanTypeForEscrow" ) );


   if(isDuplicateLoanTypeForEscrow(this, idDataGroup))
   {
      getErrMsg ( IFASTERR::DUPLICATE_LOAN_TYPE, //ERROR NO.1128 (E/W/I)
                  CND::ERR_DUPLICATE_LOAN_TYPE,
                  CND::WARN_DUPLICATE_LOAN_TYPE,
                  idDataGroup );  
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool AccountEntityXrefObject::isDuplicateLoanTypeForEscrow ( const AccountEntityXrefObject *pAEXToCheck,
                                                             const BFDataGroupId& idDataGroup)
{
   bool bHasDuplicate = false;
   DString strEntityIdToCheck, 
      strEntityTypeToCheck, 
      strLoanTypeToCheck;

   pAEXToCheck->getField( ifds::EntityType, strEntityTypeToCheck, idDataGroup );

   if(strEntityTypeToCheck != ESCROW_REPRESENTATIVE) return false;

   pAEXToCheck->getField( ifds::EntityId, strEntityIdToCheck, idDataGroup );
   pAEXToCheck->getField( ifds::LoanType, strLoanTypeToCheck, idDataGroup );

   // Only allow duplicated loan type & number in case holding different fund 
   DString strEscrowFundToCheck (NULL_STRING), strEscrowClassToCheck ( NULL_STRING );
   getField(ifds::EscrowFund, strEscrowFundToCheck, idDataGroup, false);
   getField(ifds::EscrowClass, strEscrowClassToCheck, idDataGroup, false);
   strEscrowFundToCheck.strip().upperCase();
   strEscrowClassToCheck.strip().upperCase();

   AccountEntityXref *pAccountEntityXref = 
      dynamic_cast < AccountEntityXref * > ( getParent() );

   if( pAccountEntityXref )
   {
      BFObjIter iterAccountEntityXref( *pAccountEntityXref, 
                                        idDataGroup, 
                                        true, 
                                        BFObjIter::ITERTYPE::NON_DELETED );

      iterAccountEntityXref.begin();

      while (!iterAccountEntityXref.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

         DString strEntityId,
            strEntityType,
            strLoanType,
            strEscrowFund,
            strEscrowClass;

         pObj->getField( ifds::EntityType, strEntityType, idDataGroup, false);	 
         strEntityType.strip().upperCase();

         if(strEntityType == ESCROW_REPRESENTATIVE)
         {
            pObj->getField( ifds::EntityId, strEntityId, idDataGroup, false);
            strEntityId.strip().upperCase();

            if(strEntityIdToCheck != strEntityId)
            {
               pObj->getField( ifds::LoanType, strLoanType, idDataGroup, false);
               strLoanType.strip().upperCase();

               if(strLoanTypeToCheck == strLoanType)
               {
                  pObj->getField(ifds::EscrowFund, strEscrowFund, idDataGroup, false);
                  pObj->getField(ifds::EscrowClass, strEscrowClass, idDataGroup, false);
                  strEscrowFund.strip().upperCase();
                  strEscrowClass.strip().upperCase();

                  if((strEscrowFundToCheck == strEscrowFund) && (strEscrowClassToCheck == strEscrowClass))
                  {
                     bHasDuplicate = true;
                     break;
                  }
               }

            }

         }
         ++iterAccountEntityXref;
      }
   }

   return bHasDuplicate;
}

//******************************************************************************
void AccountEntityXrefObject::updateRegistrationAgentSubstitution(const BFDataGroupId& idDataGroup, const DString& dstrTaxType)
{
   DString dstrAccountNum;
   DString dstrAcctTaxType = dstrTaxType;

   if(dstrAcctTaxType == I_(""))
   {
      MFAccount* pMFAccount = NULL;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup, true );
      if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING && pMFAccount)
      {
         pMFAccount->getField( ifds::TaxType, dstrAcctTaxType, idDataGroup );
      }
   }

   if(dstrAcctTaxType != TAX_TYPE_OA && 
      dstrAcctTaxType != TAX_TYPE_SA &&
      dstrAcctTaxType != TAX_TYPE_SRS)
   {
      DString dstrEntityTypeSubst;
      BFProperties *pBFPropertiesHost = getFieldProperties( ifds::EntityType, BF::HOST );
      pBFPropertiesHost->getAllSubstituteValues (dstrEntityTypeSubst);

      dstrEntityTypeSubst = removeItemFromSubtList ( dstrEntityTypeSubst, ENTITY_TYPE_REG_AGENT);

      BFProperties *pBFPropertiesLocal = getFieldProperties( ifds::EntityType, idDataGroup );
      pBFPropertiesLocal->setSubstituteValues(NULL);

      setFieldAllSubstituteValues (ifds::EntityType, idDataGroup, dstrEntityTypeSubst);
   }
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateEntityRegistrationAgentType(const DString& dstrTaxType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEntityRegistrationAgentType" ) );

   DString dstrEntityType;
   if(dstrTaxType == TAX_TYPE_OA )
   {
      dstrEntityType = I_("15");
   }
   else if(dstrTaxType == TAX_TYPE_SA)
   {
      dstrEntityType = I_("14");
   }
   else if(dstrTaxType == TAX_TYPE_SRS)
   {
      dstrEntityType = I_("16");
   }
   return GETCURRENTHIGHESTSEVERITY ();

   if(dstrEntityType != I_(""))
   {
      DString dstrEntityId;
      getField( ifds::EntityId, dstrEntityId, idDataGroup );
      DString retSameCIFAcct = I_("N");
      DString  dstrTrack = I_("N");
      DString  dstrPageName = NULL_STRING;

      DString dstrAccountNum;
      BFData queryData(ifds::DSTC0061_REQ);
      BFData *response = new BFData(ifds::DSTC0061_VW);


      DString mgmtCoIdOut;
      queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      queryData.setElementValue (ifds::EntityId, dstrEntityId); 
      queryData.setElementValue (ifds::EntityType, dstrEntityType); 
      queryData.setElementValue (ifds::RetSameCIFAcct, retSameCIFAcct);
      queryData.setElementValue (ifds::Track, dstrTrack);
      queryData.setElementValue (ifds::Activity, dstrPageName);


      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::WHERE_USED, 
                                                queryData, 
                                                *response, 
                                                DSTCRequestor( getSecurity() ) ) <= WARNING )
      {
         int cRepeats = response->getRepeatCount();
         if(cRepeats > 0)
         {
            const BFData& repeat = response->getRepeat( 0 );
            DString dstrWhereUseCode;
            repeat.getElementValue( ifds::WhereUse, dstrWhereUseCode);
         }
      }

      delete response;
      response = NULL;
   }

   return GETCURRENTHIGHESTSEVERITY ();
};
//************************************************************************************************
SEVERITY AccountEntityXrefObject::validateAcctRegAgent(const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctRegAgent" ) );

   DString	dstrNationalID,
			dstrPassport,
			dstrCOINationalID,
			dstrCOIPassport,
			dstrAccountNum,
			dstrEntityId,
			dstrTaxType;
   
   getAccountHolderIDs( idDataGroup,
						dstrNationalID, 
						dstrPassport, 
						dstrCOINationalID,
						dstrCOIPassport );

   getField( ifds::AccountNum, dstrAccountNum, idDataGroup, true ); 
   MFAccount *pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING && pMFAccount)
   {
	   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );
   }
   getField( ifds::EntityId, dstrEntityId, idDataGroup );

   Entity *pEntity = NULL;
   getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
   if( pEntity )
   {
	   pEntity->validateAcctRegAgent( dstrAccountNum, 
									  dstrTaxType, 
									  dstrEntityId, 
									  dstrNationalID, 
									  dstrCOINationalID, 
									  dstrPassport, 
									  dstrCOIPassport,
									  idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//**************************************************************************************************************
SEVERITY AccountEntityXrefObject::getAccountHolderIDs(const BFDataGroupId& idDataGroup, DString& dstrNID, 
												      DString &dstrPassport, DString& dstrCOINationalID,
													  DString& dstrCOIPassport )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountHolderIDs" ) );

   DString AcctNum;
   getField( ifds::AccountNum, AcctNum, idDataGroup, true );
   
   AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( getParent() );
 
   if( pAccountEntityXref->PopulateAccountOwner( idDataGroup, NULL_STRING, AcctNum, NULL_STRING, NULL_STRING ) <= WARNING )
   {
	   BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	   DString searchKey;
	   AccountEntityXref::buildPartialKeyForRetrievingEntity( searchKey, AcctNum, I_( "01" ), I_( "1" ) );

	   if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
	   {
		   DString dstrEntityId;
		   iterAccountEntityXrefOut.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );

		   Entity *pEntity = NULL;
		   getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
		   if( pEntity )
		   {
			   pEntity->getActOwnerNationalIdAndPassport(dstrNID, 
														 dstrPassport, 
														 dstrCOINationalID, 
														 dstrCOIPassport,
														 idDataGroup);
		   }       
	   }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY AccountEntityXrefObject::updateAssociateEntity(const DString &subList, const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateAssociateEntity"));

    //1. Update substitution list of Associate Entity field.
    setFieldAllSubstituteValues(ifds::AssocEntityId, idDataGroup, subList);

    //2. If the selected Associate Entity is not in the new sublist then set it to NULL.
    DString dstrAssocEntityId;
    getField(ifds::AssocEntityId, dstrAssocEntityId, idDataGroup);

    if (subList.find(dstrAssocEntityId) == -1)
    {
        setFieldNoValidate(ifds::AssocEntityId, NULL_STRING, idDataGroup, false);
        getField(ifds::AssocEntityId, dstrAssocEntityId, idDataGroup, false); // Update value
    }

    //3. If there is only one entity in the new substitution list, assign that entity to be Associate Entity; otherwise, 
    //   let user selects manually.
    //if (dstrAssocEntityId.empty() && !subList.empty() && (subList.find_first_of(I_("=")) == subList.find_last_of(I_("="))))
    //{
    //    DString firstEntityId = subList.substr(0, subList.find(I_("=")));
    //    setFieldNoValidate(ifds::AssocEntityId, firstEntityId, idDataGroup, false);
    //}

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateAcctSAGESBalance( const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctSAGESBalance" ) );

	if ( getWorkSession ().isSAGESClient() )
	{
		validateAcctGrantBalance (idDataGroup, I_("SAGES"));
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateAcctBCTESGBalance( const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctBCTESGBalance" ) );

	if ( getWorkSession ().isBCTESGClient() )
	{
		validateAcctGrantBalance (idDataGroup, I_("BCTESG"));
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateAcctGrantBalance( const BFDataGroupId &idDataGroup, const DString &dstrValidateType)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctGrantBalance" ) );

	//call for VEW415 to issue EW msg
	DString dstrEntityID;
	getField (ifds::EntityId, dstrEntityID, idDataGroup, false);

	//check grant balance at the account level when a beneficiary is added on an account
	DString dstrAccountNum,
			dstrTransID = NULL_STRING, 
			dstrNewTaxJuris = NULL_STRING, 
			dstrNewSibling = I_("Y"), 
			dstrBenefIdList = dstrEntityID;

	getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	RESPInfoUpdateValidationList respInfoUpdateValidationList (*this);

	//if grant balance is greater than zero, display ’Account must be Sibling Only for ...' warning message
	if (respInfoUpdateValidationList.init (dstrAccountNum,
		dstrTransID,
		dstrNewTaxJuris,
		dstrNewSibling,
		dstrValidateType,
		dstrBenefIdList,
		idDataGroup) <= WARNING)
	{
		respInfoUpdateValidationList.displayAllRESPError (idDataGroup);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateEntityTypeAgainstElectResetEvent(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateEntityTypeAgainstElectResetEvent " ) );

   MFAccount *pMFAccount = NULL;
   ContractInfoList* pContractInfoList = NULL;   
   bool bTOExisted = false;
   DString dstrAccountNum;

   getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
   dstrAccountNum.strip().upperCase();
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

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************************************************
SEVERITY AccountEntityXrefObject::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew)
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
                                            ACCOUNTENTITY_CATEGORY, 
                                            ACCOUNTENTITY_LEVEL, 
                                            _bVerificationEnabled,
											_dstrVerifyFilter);

   DString strEntityValue;
   getField (ifds::EntityType, strEntityValue, idDataGroup, false);
   bool entityTypeFound = DSTCommonFunctions::codeInList (strEntityValue, _dstrVerifyFilter) ? true : false;
		
   // enviroment level:
   if (_bVerificationEnabled && entityTypeFound )
   {
	   // field level:
	   bReadOnly = !bDifferentUser;
	   if ( bNew )
	   {
		   setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
		   bReadOnly = true;
	   }
	   else
	   {
		   DString strVerifyStat;
		   getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
		   strVerifyStat.strip().upperCase();

		   if (strVerifyStat == VERIFIED )
		   {
			   bReadOnly = true;
		   }
	   }
   }
   else if (!entityTypeFound)
   {
      // enviroment does not support verficaiton
      // Verify Status is read only
      // Verify Status on new EntityType is set to Verified.
	   setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
	   bReadOnly = true;
   }
   else if (_bVerificationEnabled && idDataGroup == BF::HOST ) // if data is verified is from backend, lock verify stat
   {
	   // field level:
	   bReadOnly = !bDifferentUser;
	   DString strVerifyStat;
	   getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
	   strVerifyStat.strip().upperCase();

	   if (strVerifyStat == VERIFIED )
	   {
		   bReadOnly = true;
	   }
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
SEVERITY AccountEntityXrefObject::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChanges"));

   DString strEntityValue;
   getField (ifds::EntityType, strEntityValue, idDataGroup, false);
   bool entityTypeFound = DSTCommonFunctions::codeInList (strEntityValue, _dstrVerifyFilter) ? true : false;

   if (!_bVerificationEnabled || _bInit)
      return GETCURRENTHIGHESTSEVERITY ();
   else if (!entityTypeFound)
	  return GETCURRENTHIGHESTSEVERITY ();

   if (idFieldId != ifds::VerifyStat )
   {
      // if data in CBO never changed before
      if ( !_bIsDirty )
      { 
		  _bIsDirty = isObjectDirty (idDataGroup);
		  if (_bIsDirty)
		  {
			  setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
			  setValidFlag ( ifds::VerifyStat, idDataGroup, true );
		  }
      }
      else
      {
         DString strVerifyStat;
         getField(ifds::VerifyStat,strVerifyStat,idDataGroup,false);

		 if ( strVerifyStat == VERIFIED )
		 {
			 setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
			 setValidFlag ( ifds::VerifyStat, idDataGroup, true );
		 }
      }
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, _bIsDirty);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
SEVERITY AccountEntityXrefObject::updateVerifyStatFlag(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateVerifyStatFlag"));
	DString strEntityValue;
	getField (ifds::EntityType, strEntityValue, idDataGroup, false);
	if (_bVerificationEnabled && (DSTCommonFunctions::codeInList (strEntityValue, _dstrVerifyFilter) ? true : false) )
	{
		setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY AccountEntityXrefObject::validateTaxJurisForRDSP( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,	CLASSNAME, I_( "validateTaxJurisForRDSP" ) );

	DString dstrEntityId;

	Entity *pEntity (NULL);
	if ( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
	{
		pEntity->validateTaxJurisForRDSP(idDataGroup);			
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::validateRDSPBeneDateOfBirth (const DString& dstrDateOfBirth, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPBeneDateOfBirth"));

	DString dstrEntityType;
	getField( ifds::EntityType, dstrEntityType, idDataGroup, false );

	if (!dstrEntityType.empty() && dstrEntityType == RDSP_BENEFICIARY)
	{
		DString dstrAccountNum, dstrEffectiveDate, dstrDate, dstrAsOfDec31, dstrEffectiveYear, dstrAge, dstrMonth;
		MFAccount *pMFAccount (NULL);

		getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );

		// Beneficiary must be no more than 59 years of age by December 31 of the calendar year in which the RDSP account is opened.
		if (!dstrAccountNum.empty() && getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
		{
			if ( pMFAccount->isNew() )
				pMFAccount->getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
			else
				pMFAccount->getField ( ifds::FirstEffective, dstrEffectiveDate, idDataGroup, false );
		
			int nEffectiveYear = DSTCommonFunctions::getYearFromUnFormattedDate(dstrEffectiveDate);
			convertIntToString (nEffectiveYear, dstrEffectiveYear);

			dstrAsOfDec31 = I_("1231");
			dstrDate = dstrAsOfDec31 +  dstrEffectiveYear;
			DSTCommonFunctions::BuildAge (dstrDateOfBirth, dstrDate, dstrAge, dstrMonth);
			int age = convertToULong (dstrAge);

			if(age > 59)
			{
				// 2050 - Beneficiary must be no more than 59 years of age.
				getErrMsg (IFASTERR::RDSP_BENEFICIARY_OVER_AGE_LIMIT,
						   CND::ERR_RDSP_BENEFICIARY_OVER_AGE_LIMIT,
						   CND::WARN_RDSP_BENEFICIARY_OVER_AGE_LIMIT,
						   idDataGroup);
			}
		}
	}

	return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY AccountEntityXrefObject::loadRDSPRelntoBeneSetSubstList(const BFDataGroupId& idDataGroup, const DString& dstrTaxType)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadRDSPRelntoBeneSetSubstList"));

	DString entityType, rdspRelntoBeneSubstSet;	

	getField (ifds::EntityType, entityType, idDataGroup);	

	if (!entityType.empty() && entityType == ACCOUNT_OWNER && !dstrTaxType.empty() && dstrTaxType == RDSP_TAX_TYPE)
	{
		BFProperties* pBFProperties = getFieldProperties(ifds::RDSPRelntoBene, BF::HOST);
		if (pBFProperties)
		{						
			pBFProperties->getAllSubstituteValues(rdspRelntoBeneSubstSet);
			setFieldAllSubstituteValues(ifds::RDSPRelntoBene, idDataGroup, rdspRelntoBeneSubstSet);			
		}
	}			

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/accountentityxrefobject.cpp-arc  $
// 
//    Rev 1.145   Aug 16 2012 10:51:44   wp040027
// IN#3008167-P187485-CPF- Account Entity (RA) validation
// 
//    Rev 1.144   Aug 09 2012 18:10:26   wp040133
// IN#3028337
// Ztauat2 accounts cannot be accessed via iFast DSK
// pMFAccount Null pointer check addedd
// 
//    Rev 1.143   Aug 02 2012 09:17:50   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, change of code from '04' to '03' for 'Trust' of EmployeeClass Substitution set.
// 
//    Rev 1.142   Jul 23 2012 17:10:40   dchatcha
// P0179630 FN01 FATCA Project - Entity level
// 
//    Rev 1.141   Jul 12 2012 18:38:54   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
// 
//    Rev 1.140   Jul 10 2012 15:48:52   wp040132
// IN3015613 - WO799075-P0196611_SSII - iFAST Addition of Entity Types - authorized to trade field
// 
//    Rev 1.139   Jun 29 2012 05:33:32   wichian
// IN#2957273 - Update objectKey when entityType is changed
// 
//    Rev 1.138   Jun 27 2012 18:04:38   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, fix for crashing when copy entity
// 
//    Rev 1.137   May 28 2012 10:38:04   if991250
// CPF - Account Entity + Systematics
// 
//    Rev 1.136   May 13 2012 16:57:00   if991250
// CPF - PAC
// 
//    Rev 1.135   May 09 2012 16:17:20   if991250
// CPF - IN 2945051 get the account tax type from Where used for axisting accounts
// 
//    Rev 1.134   May 02 2012 17:14:04   if991250
// CPF - retrieve entity valid tax type from view 61
// 
//    Rev 1.133   May 01 2012 10:19:14   if991250
// CPF Temp - setting the ValidRATaxType for the entity to the account value of TaxType for RA type entities
// 
//    Rev 1.132   May 01 2012 09:49:34   if991250
// Synch up 2902002 - P0186480FN02 - Diploma DSK Validation
// 
//    Rev 1.131   May 01 2012 09:25:26   if991250
// CPF - validating that the Registration agent has the appropriate tax type for the CPF account
// 
//    Rev 1.130   Apr 27 2012 16:34:56   if991250
// CPF search for Reg agents
// 
//    Rev 1.129   Apr 27 2012 09:53:00   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.128   Apr 16 2012 17:26:20   if991250
// CPF Account Setup
// 
//    Rev 1.127   Feb 06 2012 05:55:04   panatcha
// IN2780013 - SOC Loan Number and Loan Type
// 
//    Rev 1.126   Feb 06 2012 04:31:26   panatcha
// IN2780013 - SOC Loan Number and Loan Type
// 
//    Rev 1.125   Jan 04 2012 11:13:32   wutipong
// IN2717890 - Cannot open RESPs in Desktop
// 
//    Rev 1.124   Nov 22 2011 13:43:22   kitticha
// P0188150 FN01 IN2740236 - There is no warning message after save entity maintenance without any TIN.
// 
//    Rev 1.123   Oct 28 2011 07:20:02   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.122   Jul 20 2011 17:58:06   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
// 
//    Rev 1.121   Feb 10 2011 23:07:02   wichian
// IN#2399532 - Beneficiary Allocations Percent Error.
// 
//    Rev 1.120   Feb 10 2011 13:05:08   dchatcha
// Synch up: P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown', fix crashing after user change DOfB of existing RESP beneficiary to 12/31/9999.
// 
//    Rev 1.119   Feb 08 2011 04:21:16   panatcha
// P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown'.
// 
//    Rev 1.118   Feb 07 2011 11:32:34   panatcha
// [sync up] P0165541FN12_IN2407181 : Error message'SIN Effective Date Cannot be Unknown'.
// 
//    Rev 1.117   Feb 07 2011 19:06:58   dchatcha
// Incident 2409562 - Fix to return warning message for DOFB changes
// 
//    Rev 1.116   Jan 18 2011 14:22:04   dchatcha
// IN# 2389426 - P0165541FN12 - DSK Edits and Labels, issue#4 always change IDS date along to RESP Benef DOB
// 
//    Rev 1.115   Jan 10 2011 03:50:56   wutipong
// IN2311277 - Unable to access FDP accounts in Desktop
// 
//    Rev 1.114   Dec 03 2010 00:01:10   wichian
// IN#2291912 - Apply logic to send nextkey to vew61 in next vew call
// 
//    Rev 1.113   Nov 25 2010 11:15:10   kitticha
// PET165541_FN03_QESI_Phase3_Non_Finance - revise.
// 
//    Rev 1.112   Nov 25 2010 08:10:22   kitticha
// PET165541_FN03_QESI_Phase3_Non_Finance - revise
// 
//    Rev 1.111   Nov 23 2010 08:38:22   kitticha
// PET165541_FN03_QESI_Phase3_Non_Finance - revise
// 
//    Rev 1.110   Oct 29 2010 07:14:58   panatcha
// PET165541_FN03_QESI_Phase3_Non_Finance
// 
//    Rev 1.109   Oct 14 2010 00:33:42   kitticha
// PETP0172931_FN01_IN#2283060
// 
//    Rev 1.108   Oct 08 2010 04:44:00   kitticha
// PETP0172931_FN01_IN#2283060
// 
//    Rev 1.107   Jun 25 2010 07:32:16   panatcha
// IN#2157424-PET0165541_FN02__WO517185 LetterReq field validation
// 
//    Rev 1.106   Jun 25 2010 07:20:06   panatcha
// IN#2157424-PET0165541_FN02__WO517185 LetterReq field validation
// 
//    Rev 1.105   Jun 17 2010 03:17:20   dchatcha
// IN# 2148841 - QESI - PET165541 - invalid BN missing error message, Validate first 9 digits of PCG Business Number.
// 
//    Rev 1.104   Jun 14 2010 08:14:10   dchatcha
// IN# 2149355 - BIP QA- Unable to set up RESP account in DSK with error. (issue#2)
// 
//    Rev 1.103   Jun 11 2010 07:03:48   dchatcha
// IN# 2148841 - QESI - PET165541 - inavalid BN missing error message.
// 
//    Rev 1.102   Jun 10 2010 08:36:22   dchatcha
// IN# 2149300 - NASU for family RESP account cannot pass through entity setup screen
// 
//    Rev 1.101   Jun 09 2010 08:07:58   dchatcha
// IN# 2145170 - QESI - PET165541 - Request Federal Grant field
// 
//    Rev 1.100   May 27 2010 16:35:40   popescu
// IN 2130000 - PET165541 -  the grant request field is guarded by UAF 192
// 
//    Rev 1.99   May 27 2010 02:36:48   dchatcha
// Incident 2112443 - PET165541 - RT511 and Generate Notification letter - Generate RT511 and RT511 cut-off-date is read-only when PCG is changed.
// 
//    Rev 1.98   May 12 2010 22:04:48   popescu
// Incident 2112443 - PET165541 - RT511 and Generate Notification letter - aditional fix
// 
//    Rev 1.97   May 12 2010 12:09:54   popescu
// Incident 2112443 - PET165541 - RT511 and Generate Notification letter - aditional fix for cloned accounts
// 
//    Rev 1.96   May 10 2010 16:49:32   popescu
// Incident 2112443 - PET165541 - RT511 and Generate Notification letter
// 
//    Rev 1.95   May 06 2010 23:35:34   popescu
// RESP/QESI fixes
// 
//    Rev 1.94   May 03 2010 17:44:44   popescu
// PET0165541 FN01 QESI RESP Trading - New account set-up fixes
// 
//    Rev 1.93   Apr 26 2010 03:38:24   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU, RT511 related fields still open for changing.
// 
//    Rev 1.92   Apr 13 2010 13:17:50   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU  - few issues with crashes on the account details screen
// 
//    Rev 1.91   Apr 07 2010 07:14:22   kitticha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU, Fix a littlebit bugs.
// 
//    Rev 1.90   Apr 07 2010 05:45:16   kitticha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU.
// 
//    Rev 1.89   Apr 06 2010 06:39:54   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU, several fixes for issues found during VEW-DSK integration test, some logic moved to Entity though.
// 
//    Rev 1.88   Apr 03 2010 02:25:36   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.87   Mar 31 2010 09:02:40   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU, accidentaly  put wrong initial value.
// 
//    Rev 1.86   Mar 31 2010 08:23:38   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.85   Mar 29 2010 07:14:58   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.84   Mar 26 2010 09:23:56   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.83   Mar 23 2010 13:51:48   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.82   Mar 17 2010 06:39:28   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.81   Mar 12 2010 15:01:06   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.80   Sep 25 2009 14:11:02   jankovii
// IN 1850287 - Escrow Functionality
// 
//    Rev 1.79   Mar 24 2009 00:55:46   wutipong
// IN#1591003 Annuitant Contract Maturity date issue
// 
//    Rev 1.78   05 Mar 2009 16:02:36   kovacsro
// IN#1573014 - RL91-MT535/MT536-adding clearing platform, click on Reset, weird error message
// 
//    Rev 1.77   Feb 23 2009 11:52:34   jankovii
// IN 1596652 - RLSP/RLIF - DSK please issue ERROR when owner age < 55
// 
//    Rev 1.76   Feb 19 2009 09:24:14   jankovii
// IN 1596652 No warning message when creating Restricted LIRA where age<55
// 
//    Rev 1.75   Jan 27 2009 06:25:12   daechach
// IN 1548019 - fix crashing while manualy add new clearing platform.
// 
//    Rev 1.74   23 Jan 2009 16:32:14   popescu
// Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
// 
//    Rev 1.73   16 Jan 2009 17:23:00   popescu
// Incident 1544134 - various fixes
// 
//    Rev 1.72   Jan 08 2009 06:02:26   daechach
// IN 1545482 - R91-MT535/MT536-users should not be able to create Clearing platform entities.
// 
//    Rev 1.71   Dec 15 2008 01:39:28   phiwponp
// PET0007773_FN01_MT535-MT536 Enhancement.
// 
//    Rev 1.70   Nov 28 2008 14:35:14   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.69   Nov 25 2008 11:13:24   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.68   06 Oct 2008 14:39:18   kovacsro
// synch up 1.65.1.1 - TFSA
// 
//    Rev 1.67   15 Sep 2008 08:56:36   kovacsro
// synch up 1.65.1.0 PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.66   Aug 20 2008 06:56:36   phiwponp
// Incident # 1349605 - R86 - Incident 1210968 - Stop Date for Assignee and Escrow.
// 
//    Rev 1.65   Jun 09 2008 07:33:48   daechach
// IN # 1062864 - Allow nominee owner to be set up for client account.
// 
//    Rev 1.64   23 Nov 2007 11:30:56   kovacsro
// PET5685FN25 - age71 changes for RRSP&RIF
// 
//    Rev 1.63   Oct 08 2007 12:15:50   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.62   Aug 17 2007 13:23:24   kovacsro
// IN 946661 - fixed required fields for beneficiary entities
// 
//    Rev 1.61   Feb 27 2007 16:37:50   ZHANGCEL
// Incident #831600 -- Fix problem to check Jurisdiction for RRSP
// 
//    Rev 1.60   Oct 26 2006 13:31:20   jankovii
// PET 1310 FN45 - Joint account default disposition.
// 
//    Rev 1.59   Aug 29 2006 10:58:44   ZHANGCEL
// Incident #694914 -- Remove logic to check AssigneScreen
// 
//    Rev 1.58   Aug 25 2006 16:05:16   ZHANGCEL
// Incident #694914 -- Add permission check for "Assignee Entity Type Setup"
// 
//    Rev 1.55   Aug 23 2006 17:12:04   ZHANGCEL
// Incident #697104 -- Fix problem that did not pass effectivedate to the function call MFAccount->fundClassBalance
// 
//    Rev 1.54   Aug 23 2006 15:38:46   ZHANGCEL
// Incident #696937 -- An error will be raised when user enter an invalid EffectiveDate
// 
//    Rev 1.53   Aug 23 2006 12:05:08   ZHANGCEL
// Incident #696937 & 695312 -- Fix problem with Escrow EffectiveDate validation and FundClass validation
// 
//    Rev 1.52   Jul 04 2006 13:46:38   ZHANGCEL
// PET2145 FN01 -- Change logic to handle Assignee entity type
// 
//    Rev 1.51   Jan 18 2006 16:18:46   ZHANGCEL
// Incident #521433 -- Change default value for AuthorizedToTrade
// 
//    Rev 1.50   Jul 11 2005 17:21:42   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.49   Jun 09 2005 13:36:04   Fengyong
// #Incident 285146 - fix crash when copy entity
// 
//    Rev 1.48   Feb 10 2005 08:19:34   porteanm
// PTS 10038225 - Enable/Disable Entity controls for Escrow based on escrow band - just an extra measure as all controls should already be disabled in the dialog.
// 
//    Rev 1.47   Dec 14 2004 15:01:38   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.46   Dec 02 2004 15:05:44   Fengyong
// PET1117 FN54 - Fund Broker static
// 
//    Rev 1.45   Dec 02 2004 14:28:12   Fengyong
// PET972
// 
//    Rev 1.44   Nov 14 2004 14:24:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.43   Sep 23 2004 09:42:44   HERNANDO
// PTS10030155 - Will display Rule 1 message if both Rule 1 and Rule 4 messages are required.
// 
//    Rev 1.42   Jun 07 2004 14:34:00   HERNANDO
// PTS10030155 - Changed the rule for displaying the Warning message for validateEntityTypeDofB.
// 
//    Rev 1.41   May 18 2004 15:12:46   HERNANDO
// PTS10030155 - Display an alternate message -- contains 'No age check' -- for LIF and LRIF according to Hiral (UAT).
// 
//    Rev 1.40   Dec 22 2003 14:45:48   VADEANUM
// PTS 10025202 - When adding new Entity 'Executor' or "Power Of Attorney', open for updates the 'Authorize to Trade' field.
// 
//    Rev 1.39   Oct 30 2003 17:03:18   VADEANUM
// PTS 10023301 - Part II Extra error message - added ERR_RESP_BENEF_REASON_MUST_BE_CURRENT_BENEF_FOR_NEW_ENTITY.
// 
//    Rev 1.38   Oct 30 2003 15:42:42   VADEANUM
// PTS 10023301 - Reason not saved - added ERR_RESP_BENEF_REASON_CANNOT_BE_MODIFIED.
// 
//    Rev 1.37   Oct 22 2003 11:41:52   YINGBAOL
// PTS10022062 and PTS10022418
// 
//    Rev 1.36   Aug 28 2003 16:39:02   FENGYONG
// lastname always required, should not controled be error number. the field validation of firstname, lastname sin number, dofbirth will never be called, moved to validateOneAccount.
// 
//    Rev 1.35   Aug 26 2003 15:03:14   FENGYONG
// When copy an account owner with spouse setup, show the spouse name on the spouse box for that owner
// 
//    Rev 1.34   Aug 26 2003 10:37:22   FENGYONG
// link ownerspousename and spouseentityid 
// 
//    Rev 1.33   Aug 25 2003 10:04:22   FENGYONG
// remove Account purpose restriction on EntityType lodic
// 
//    Rev 1.32   Aug 22 2003 12:22:26   FENGYONG
// set spouse info only for onwer
// 
//    Rev 1.31   Aug 21 2003 19:52:36   FENGYONG
// KYC Joint info enhancement
// 
//    Rev 1.30   Aug 19 2003 11:11:02   WINNIE
// Remove the Account Purpose restriction on EntityType logic as this will stop user from setting up account owner entity. Validation should be implement to the AccountEnittyXref.cpp instead. 
// 
//    Rev 1.29   Aug 11 2003 16:46:54   YINGBAOL
// set several field to host, which will solve rollback issue
// 
//    Rev 1.28   Aug 11 2003 16:29:32   FENGYONG
// temp checkin
// 
//    Rev 1.27   Jul 31 2003 15:45:32   FENGYONG
// control required field by error Number
// 
//    Rev 1.26   Jul 30 2003 16:57:56   FENGYONG
// Doinitwithdefaultvalue
// 
//    Rev 1.25   Jul 30 2003 11:26:30   FENGYONG
// CIBC enhancement PET809_FN46
// 
//    Rev 1.24   Jun 11 2003 15:33:48   YINGBAOL
// temporarily comment 2 line of code, need to put it back and base code support.
// 
//    Rev 1.23   May 16 2003 18:23:54   YINGBAOL
// check if it is account owner for entity mailing list
// 
//    Rev 1.22   Mar 21 2003 17:54:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.21   Dec 06 2002 09:31:56   YINGBAOL
// PRIF Enhancement
// 
//    Rev 1.20   Nov 29 2002 15:39:10   ZHANGCEL
// Synced up to 1.15
// 
//    Rev 1.19   Nov 14 2002 10:10:34   KOVACSRO
// restored ver. 1.17 since there was no bug. Equals is a better name than close to, for this condition.
// 
//    Rev 1.17   Oct 24 2002 17:29:52   KOVACSRO
// PTS 1008907 : sync-up for 1.16
// 
//    Rev 1.16   Oct 22 2002 13:51:40   KOVACSRO
// sync-up 1.16 (ERR_WARN_ESCROW_AMT_EQUALS_HOLDING)
// 
//    Rev 1.15   Oct 09 2002 23:53:52   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.14   Sep 12 2002 10:06:10   YINGBAOL
// added getEntityMailingList(...) method
// 
//    Rev 1.13   Aug 29 2002 12:54:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.12   Jul 29 2002 14:28:10   ZHANGCEL
// PTS 10009207: Issue a warning whenever shareholder is younger than 18
// 
//    Rev 1.11   Jul 26 2002 14:52:50   YINGBAOL
// fix refersh issue---PTS10009183
// 
//    Rev 1.10   Jul 18 2002 11:00:00   HSUCHIN
// bug fix for error icon that shows when a new beneficiary is added.
// 
//    Rev 1.9   Jul 12 2002 13:02:24   KOVACSRO
// hasCraetePermission should decide if an escrow entity type can be created or not, rather than hasReadPermission.
// 
//    Rev 1.8   Jul 10 2002 15:56:30   KOVACSRO
// Bug fixed for doPopulateField (for the same EntityId we can get multiple repeats)
// 
//    Rev 1.7   Jul 04 2002 14:16:04   ZHANGCEL
// Bug fix for the getting PensionJurist correctly
// 
//    Rev 1.6   Jul 02 2002 16:15:48   ZHANGCEL
// minor fix
// 
//    Rev 1.5   Jun 27 2002 17:06:20   ZHANGCEL
// Added proper logic for the locked_in taxtype account setup
// 
//    Rev 1.4   Jun 17 2002 15:31:18   ZHANGCEL
// PTS 10008207: Bug fix for the Benificiary validation
// 
//    Rev 1.3   Jun 14 2002 17:22:08   ZHANGCEL
// 1. PTS 10008207 bug fix; 2. Added new logic into the validateEntityTypeDofB() for the RIF_LIF_LRIF enhancement stuffs.
// 
//    Rev 1.2   08 Jun 2002 18:25:06   HERNANDO
// Added additional checking to validateEntityTypeDofB for Tax Jurisdiction, Age and Tax Type, and Date of Birth.
// 
//    Rev 1.1   May 30 2002 16:20:14   ZHANGCEL
// Syn up to 1.47.1.0
// 
//    Rev 1.0   22 May 2002 21:24:20   PURDYECH
// Initial revision.
 * 
 *    Rev 1.47   May 16 2002 14:52:20   ZHANGCEL
 * PTS 10008202: Set default value of field "Authorized to Trade" to "No" for all entities except for the Account Owner.
 *
 *    Rev 1.46   06 Mar 2002 14:20:44   WINNIE
 * PTS 10007408 : ensure lastname being validated
 * 
 *    Rev 1.45   Mar 05 2002 17:15:00   ZHANGCEL
 * Fix Runtime error when user hit OK whth the blank LastName and blank Laguage 
 * 
 *    Rev 1.44   28 Feb 2002 13:14:54   WINNIE
 * sync up 1.39.1; PTS 10007234 : escrow fund balancing checking; edit check for load reason code '09'; edit check for bankruptcy code with input of escrow fund
 * 
 *    Rev 1.43   Feb 26 2002 16:33:14   ZHANGCEL
 * Bug fix of PTS 10007298: Set the default value of AmtType to be "Dollar"
 * 
 *    Rev 1.42   Feb 25 2002 14:30:36   ZHANGCEL
 * PTS 10007232 again
 * 
 *    Rev 1.41   Feb 22 2002 16:16:26   ZHANGCEL
 * PTS 10007232: Set AmtType and ReasonCode to be mandatory when EntittyType is "11"
 * 
 *    Rev 1.40   12 Feb 2002 13:37:26   KOVACSRO
 * Bug fixes for Escrow Fund code and Class.
 * 
 *    Rev 1.39   12 Feb 2002 13:23:00   KOVACSRO
 * PTS 10007091. Don't validate against Escrow fund class until both fund and class are entered.
 *
 *    Rev 1.38   Feb 08 2002 11:11:04   ZHANGCEL
 * Bug Fix of PTS 10006914: Added logic to validate Primary Beneficiary for a  RRIF account
 * 
 *    Rev 1.37   Jan 28 2002 18:03:24   ZHANGCEL
 * Fixed the bug of ticket 10006765, Added logic to check escrowFund and escrowClass when AmountType is "Unit"
 * 
 *    Rev 1.36   Jan 17 2002 17:41:14   ZHANGCEL
 * Fix bug of RTS 10006765 -- Added a new function: getFormattedAmount()
 * 
 *    Rev 1.35   27 Dec 2001 17:19:26   KOVACSRO
 * one more fix for PopulateWhereUsedForAccount.
 * 
 *    Rev 1.34   27 Dec 2001 13:46:46   KOVACSRO
 * changed PopulateWhereUsedForAccount.
 * 
 *    Rev 1.33   27 Dec 2001 13:06:44   KOVACSRO
 * minor bug fixed.
 * 
 *    Rev 1.32   03 Dec 2001 12:59:54   KOVACSRO
 * Implemented doPopulateField()
 * 
 *    Rev 1.31   29 Nov 2001 12:06:22   KOVACSRO
 * overwrite for getField.
 * 
 *    Rev 1.30   05 Nov 2001 14:54:56   KOVACSRO
 * hasPermission() changes.
 * 
 *    Rev 1.29   Nov 01 2001 11:15:18   YINGBAOL
 * change condition
 * 
 *    Rev 1.28   Nov 01 2001 09:59:30   YINGBAOL
 * 1. check permistion if entitytype is escrow representative;
 * 2. set reasoncode as required if it is an escrow representative
 * 
 *    Rev 1.27   30 Oct 2001 14:33:38   WINNIE
 * title restriction for pending trade exists; default value for effective date of acctentitiyxref 
 * 
 *    Rev 1.26   26 Sep 2001 14:03:54   WINNIE
 * escrow title restriction enhancement
 * 
 *    Rev 1.25   17 Sep 2001 11:49:02   WINNIE
 * bug fix for warning, check the decmial value instead of DString value
 * 
 *    Rev 1.24   Jul 29 2001 14:50:00   YINGBAOL
 * add doreset
 * 
 *    Rev 1.23   Jul 09 2001 11:51:12   ZHANGCEL
 * Added logic for Date of Birth edit check 
 * 
 *    Rev 1.22   Jun 26 2001 12:54:56   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.21   03 May 2001 14:05:50   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.20   Feb 27 2001 13:24:14   WINNIE
 * bug fix for condition check for RRSP loan
 * 
 *    Rev 1.19   Jan 04 2001 17:00:28   ZHANGCEL
 * Remove the redefination header file: #include "DataIter.hpp"
 * 
 *    Rev 1.18   Jan 04 2001 11:38:44   ZHANGCEL
 * Set the value of new entity copy's EntityType to be NULL_STRING and added logic for EntityType validation
 * 
 *    Rev 1.17   Dec 20 2000 10:08:28   ZHANGCEL
 * Added logic for CopyEntity requirement ( added a new function ModelOffer() )
 * 
 *    Rev 1.16   Dec 01 2000 10:35:12   ZHANGCEL
 * Added DofBirth into the ClassFieldInfo[]
 * 
 *    Rev 1.15   Nov 24 2000 12:10:18   WINNIE
 * new method to check if entity is effective based on the input date
 * 
 *    Rev 1.14   Oct 31 2000 12:13:44   KOVACSRO
 * Fixed TaxJurisCode for RESP Beneficiary.
 * 
 *    Rev 1.13   Oct 13 2000 10:25:06   DINACORN
 * Enabled condition ERR_AMOUNT_MUST_BE_ZERO_IF_…
 * 
 *    Rev 1.12   Sep 29 2000 13:58:36   DINACORN
 * Fixed bugs; Create new method member; Create CrossEdir Amount-Reason.
 * 
 *    Rev 1.11   Sep 26 2000 14:02:02   KOVACSRO
 * Added validation for ReasonCode and HRDCRelateCode.
 * 
 *    Rev 1.10   Sep 25 2000 19:18:22   WINNIE
 * do validation only if DataGroupID not equal BF::HOST
 * 
 *    Rev 1.8   Aug 11 2000 10:30:48   YINGBAOL
 * fix NASU issues
 * 
 *    Rev 1.7   Aug 10 2000 13:45:02   YINGBAOL
 * change getNextSeq and fix bug
 * 
 *    Rev 1.6   Jul 26 2000 14:31:12   KOVACSRO
 * added some fields
 * 
 *    Rev 1.5   Jul 26 2000 11:15:18   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.4   Jul 20 2000 14:33:50   HUANGSHA
 * validate the BirthName based on the system feature
 * 
 *    Rev 1.3   Jun 27 2000 10:55:10   HUANGSHA
 * removed the required flag for salutation field
 * 
 *    Rev 1.2   Jun 13 2000 16:21:50   HUANGSHA
 * disable the AuthorizedToTrade field for entityType 01, ...
 * 
 *    Rev 1.1   Jun 08 2000 11:17:06   YINGZ
 * fix NASU dlg can close without lastname... problem
 * 
 *    Rev 1.0   Feb 15 2000 10:59:46   SMITHDAV
 * Initial revision.
// 
//    Rev 1.24   Feb 01 2000 14:36:22   BUZILA
// added lValidateGroup parameter to doValidateAll method
// 
//    Rev 1.23   Jan 31 2000 11:46:46   VASILEAD
// Took out the old initDefaults
// 
//    Rev 1.22   Jan 23 2000 19:34:24   VASILEAD
// Reset functionality
// 
//    Rev 1.21   Jan 23 2000 16:44:44   VASILEAD
// Reset functionality
// 
//    Rev 1.20   Jan 21 2000 11:11:42   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.19   Jan 21 2000 08:14:18   VASILEAD
// took out init to default flag
// 
//    Rev 1.18   Jan 18 2000 18:38:14   VASILEAD
// Updates fix
// 
//    Rev 1.17   Jan 13 2000 17:39:36   VASILEAD
// Added support for catching errors
// 
//    Rev 1.16   Jan 11 2000 11:11:24   VASILEAD
// Fix validation
// 
//    Rev 1.15   Jan 11 2000 10:28:54   VASILEAD
// Business edits for Entity screen
// 
//    Rev 1.14   Jan 10 2000 16:15:26   VASILEAD
// Added Joint information in Entity screen
// 
//    Rev 1.13   Jan 09 2000 14:58:28   VASILEAD
// Corrected entity screen in the NASU
// 
//    Rev 1.12   Jan 07 2000 17:02:44   VASILEAD
// Validations for Entity screen
// 
//    Rev 1.11   Jan 06 2000 16:21:08   VASILEAD
// Business edits for Entity screen
// 
//    Rev 1.10   Dec 24 1999 15:18:22   VASILEAD
// Fixed transactions
// 
//    Rev 1.9   Dec 12 1999 16:25:06   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/
