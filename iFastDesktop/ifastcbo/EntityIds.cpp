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
// ^FILE   : EntityIds.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : November 1999
//
// ^CLASS    : EntityIds
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <boost\regex.h>

#include "entityids.hpp"

#include <bfcbo\bfobjiter.hpp>

#include "acctentityvalidation.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "entity.hpp"
#include "entityidslist.hpp"
#include "entitysearchidvalidation.hpp"
#include "entitysearchlist.hpp"
#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "respinfoupdatevalidationlist.hpp" //QESI3FN03
#include "taxtyperulelist.hpp"
#include "translationtable.hpp" 
#include "whereusedlist.hpp"
#include "whereused.hpp"
#include "worksessionentitylist.hpp"
#include "EntitySearchIDValueValidation.hpp"

#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0079_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0417_req.hpp>
#include <ifastdataimpl\dse_dstc0417_vw.hpp>
#include <ifastdataimpl\dse_dstc0490_req.hpp>
#include <ifastdataimpl\dse_dstc0490_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEARCH;
   extern CLASS_IMPORT const DSTCRequest ENTITY_SEARCHID_VALIDATION_INQUIRY;
   extern CLASS_IMPORT const DSTCRequest ENTITYSEARCHID_VALIDATION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DuplicateSINcheck;
   extern CLASS_IMPORT const BFTextFieldId AllAccounts;
   extern CLASS_IMPORT const BFTextFieldId SrchSIN;
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFTextFieldId RoutingType;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerIDType;
   extern CLASS_IMPORT const BFTextFieldId XrefNum;
   extern CLASS_IMPORT const BFTextFieldId SINRequired;
   extern CLASS_IMPORT const BFTextFieldId ClearingPlatformID;
   extern CLASS_IMPORT const BFTextFieldId ValidInvalidIdStatus;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;//QESI3FN03
   extern CLASS_IMPORT const BFTextFieldId IsValid;
   extern CLASS_IMPORT const BFTextFieldId CountryOfIssue;
   extern CLASS_IMPORT const BFTextFieldId XrefCountryOfIssue;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFTextFieldId Residency1;
   extern CLASS_IMPORT const BFTextFieldId Residency2;
   extern CLASS_IMPORT const BFTextFieldId Residency3;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClass;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags
   {ifds::EntityId,           BFCBO::NONE,         0},
   {ifds::IdType,             BFCBO::NONE,         0},
   {ifds::IdValue,            BFCBO::NONE,         0},
   {ifds::IdDate,             BFCBO::NONE,         0},
   {ifds::IdStatus,           BFCBO::NONE,         0},
   {ifds::IdExpireDate,       BFCBO::NONE,         0},
   {ifds::CountryOfIssue,     BFCBO::NONE,         0},
   {ifds::IdAllowOverride,    BFCBO::NONE,         0},
   {ifds::EntitySearchIdVer,  BFCBO::NONE,         0},
   {ifds::EntitySearchRid,    BFCBO::NONE,         0},
   {ifds::SIN,                BFCBO::NONE,         0},
   {ifds::DuplicateSINcheck,  BFCBO::NONE,         0},
   {ifds::EntityType,         BFCBO::NONE,         0},
   {ifds::GoodBad,            BFCBO::NONE,         0},
   {ifds::ClearingPlatformID, BFCBO::NONE,         0}, //MT53Xs
   {ifds::XrefNum,            BFCBO::IMMEDIATE_VALIDATION, 0 },
   {ifds::XrefCountryOfIssue, BFCBO::IMMEDIATE_VALIDATION, 0 },
   {ifds::EmployeeClass,      BFCBO::NOT_ON_HOST,           0},
   {ifds::VerifyStat,         BFCBO::NONE,         0},
};

namespace CND
{
   extern const long ERR_NO_VALUE_FOR_ID;
   extern const long ERR_W_INVALID_SIN;
   extern const long ERR_E_INVALID_SIN;
   extern const long ERR_W_SIN_IS_MISSING;
   extern const long ERR_E_SIN_IS_MISSING;
   extern const long ERR_DUPLICATE_SIN;
   extern const long WARN_DUPLICATE_SIN;
   extern const long ERR_DUPLICATE_BICCODE;
   extern const long WARN_DUPLICATE_BICCODE;
   extern const long ERR_DUPLICATE_NEQ;
   extern const long WARN_DUPLICATE_NEQ;

   extern const long ERR_ACCTOWNER_SIN_MISSING;
   extern const long ERR_ACCTOWNER_SIN_INVALID;
   extern const long ERR_SPOUSE_SIN_MISSING;
   extern const long ERR_SPOUSE_SIN_INVALID;
   extern const long ERR_CANNOT_ADD_NEW_CIF;
   extern const long ERR_CANNOT_ADD_NEW_ACCESS_ID;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_ENTITY_NOT_FOUND;
   extern const long ERR_ONE_FS_ALT_ACCOUNT;
   extern const long ERR_INVALID_ACCESS_ID;
   extern const long ERR_OVERRIDE_IS_NOT_ALLOWED;
   extern const long ERR_INVALID_STATUS_FOR_ACCESS_ID;
   extern const long ERR_RESET_OVERRIDE_IS_NOT_ALLOWED;
   extern const long ERR_MULTIPLE_CLEARING_PLATFROM_ID_NOT_ALLOWED_FOR_CLEARING_PLATFORM;
   extern const long ERR_RELATIONSHIP_IDVALUE_NOT_CONSISTENT;
   extern const long ERR_ENTERED_ID_NOT_UNIQUE;
   extern const long ERR_FIELD_IS_BLANK;
   extern const long ERR_ID_TYPE_DUPLICATED_RECORD;
   extern const long ERR_RESP_BENEFICIARY_SIN_MISSING;
   extern const long WARN_RESP_BENEFICIARY_SIN_MISSING;
   extern const long ERR_RESP_BENEFICIARY_SIN_INVALID;
   extern const long WARN_RESP_BENEFICIARY_SIN_INVALID;
   extern const long ERR_RESP_PCG_INDIV_SIN_MISSING;
   extern const long WARN_RESP_PCG_INDIV_SIN_MISSING;
   extern const long ERR_RESP_PCG_INDIV_SIN_INVALID;
   extern const long WARN_RESP_PCG_INDIV_SIN_INVALID;
   extern const long ERR_E_INVALID_ID_VALUE;
   extern const long ERR_W_INVALID_ID_VALUE;
   extern const long ERR_E_ID_VALUE_IS_MISSING;
   extern const long ERR_W_ID_VALUE_IS_MISSING;
   extern const long ERR_PCG_INST_BUSINESS_NUMBER_MISSING;
   extern const long WARN_PCG_INST_BUSINESS_NUMBER_MISSING;
   extern const long ERR_PCG_INST_BUSINESS_NUMBER_INVALID;
   extern const long WARN_PCG_INST_BUSINESS_NUMBER_INVALID;
   extern const long ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long ERR_LOAN_TYPE_FOR_ESCROW;
   extern const long WARN_LOAN_TYPE_FOR_ESCROW;
   extern const long ERR_LOAN_NUM_FOR_ACCTHOLDER;
   extern const long WARN_LOAN_NUM_FOR_ACCTHOLDER;
   extern const long WARN_BLANK_CNTRY_OF_ISSUE;
   extern const long ERR_BLANK_CNTRY_OF_ISSUE;
   extern const long ERR_MULTIPLE_NATIONAL_ID_NOT_ALLOWED_FOR_AN_ENTITY;
   extern const long ERR_MULTIPLE_CPFB_ACCOUNT_NUMBER_NOT_ALLOWED_FOR_AN_ENTITY;
   extern const long ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern const long ERR_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern const long ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long WARN_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern const long ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long ERR_EXPIRY_DATE_REQUIRED;
   extern const long ERR_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY;
   extern const long WARN_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY;
   extern const long ERR_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long WARN_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY;
   extern const long ERR_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER;
   extern const long WARN_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER;
   extern const long ERR_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER;
   extern const long WARN_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER;
   extern const long ERR_INVALID_GIIN_FORMAT;
   extern const long WARN_INVALID_GIIN_FORMAT;
   extern const long WARN_MULTIPLE_NATIONAL_ID_NOT_ALLOWED_FOR_AN_ENTITY;
   extern const long ERR_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY;
   extern const long WARN_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY;
   extern const long ERR_CNTRY_OF_ISSUE_IS_BLANK;
   extern const long WARN_CNTRY_OF_ISSUE_IS_BLANK;
   extern const long ERR_IDTYPE_FOR_COUNTRY_EXISTED;
   extern const long WARN_IDTYPE_FOR_COUNTRY_EXISTED;
   extern const long ERR_TRANSMITTER_NUMBER_FORMAT_INCORRECT;
   extern const long WARN_TRANSMITTER_NUMBER_FORMAT_INCORRECT;
   extern const long ERR_INVALID_TFN_VALUE;
   extern const long WARN_INVALID_TFN_VALUE;
   extern const long ERR_INVALID_ABN_VALUE;
   extern const long WARN_INVALID_ABN_VALUE;
   extern const long ERR_DUPLICATE_BUSINESS_NUMBER;
   extern const long WARN_DUPLICATE_BUSINESS_NUMBER;
   extern const long ERR_WRONG_VERIFY_STATUS;
   extern const long WARN_BIC_CODE_LINKED_MSG;
   extern const long ERR_BIC_CODE_LINKED_MSG;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_SIN; 
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_NEQ;
   extern CLASS_IMPORT I_CHAR * const LOAN_TYPE_FOR_ESCROW;
   extern CLASS_IMPORT I_CHAR * const LOAN_NUM_FOR_ACCTHOLDER;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER;
   extern CLASS_IMPORT I_CHAR * const TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern CLASS_IMPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern CLASS_IMPORT I_CHAR * const ID_NUMBER_IS_REQUIRED_FOR_INDIVIDUAL;
   extern CLASS_IMPORT I_CHAR * const EMPLOYER_NUMBER_IS_REQUIRED_FOR_CORPORATE;
   extern CLASS_IMPORT I_CHAR * const INVALID_GIIN_FORMAT;
   extern CLASS_IMPORT I_CHAR * const MULTIPLE_NATIONAL_ID_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const MULTIPLE_GIIN_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const TRANSMITTER_NUMBER_FORMAT_INCORRECT;
   extern CLASS_IMPORT I_CHAR * const INVALID_TFN_VALUE;
   extern CLASS_IMPORT I_CHAR * const INVALID_ABN_VALUE;
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_BUSINESS_NUMBER;
   extern CLASS_IMPORT I_CHAR * const BIC_CODE_LINKED_MSG;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const APAC_SUPREGN;
}

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                        = I_ ("EntityIds");
   const I_CHAR * const ENTITY_ID                        = I_ ("ENTITY_ID");
   const I_CHAR * const ID_VALUE                         = I_ ("ID_VALUE");
   //used to check is SIN is required
   const I_CHAR * const ACCOUNT_OWNER                    = I_("01");
   const I_CHAR * const RESP_BENEFICIARY                 = I_("50");
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE         = I_("9");
   const I_CHAR * const FAMILY_RESP_TAX_TYPE             = I_("M");
   const I_CHAR * const SIN_REQ_ERR_MSG_CODE             = I_("395");

   //for SIN validation
   const I_CHAR * const RRSP_TAX_TYPE                    = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE                    = I_( "2" ); 
   const I_CHAR * const RPP_TAX_TYPE                     = I_( "8" );
   const I_CHAR * const PRIF_TAX_TYPE                    = I_( "R" );
   const I_CHAR * const TFSA                             = I_( "V" );
   const I_CHAR * const SPOUSAL_CONTRIBUTOR_ENTITY_TYPE  = I_( "06" );
   const I_CHAR * const RESP_PCG_INDIV                   = I_( "55" );
   const I_CHAR * const RESP_DSGN_INST                   = I_( "52" );

   //MT535/MT536
   const I_CHAR * const CLEARING_PLATFORM                = I_( "58" );
   //MT53X
   const I_CHAR * const GROUPCODE_CLEARING_PLATFORM_ID   = I_( "ZC" );

   //TA Automated Fund Transfer
   const I_CHAR * const ENTITY_TYPE_FUND_CUSTODIAN       = I_( "12" );
   const I_CHAR * const ENTITY_TYPE_FUND_ACCOUNTANT      = I_( "13" );

   // QESI
   const I_CHAR * const RESP_PCG_INST                    = I_( "56" ); 
   
   const I_CHAR * const ESCROW_ENTITY                    = I_( "11" );
   const I_CHAR * const INDIVIDUAL_ACCOUNT_TYPE_LIST     = I_( "0,1,2" );
   const I_CHAR * const OA_TAX_TYPE                      = I_("OA");
   const I_CHAR * const SA_TAX_TYPE                      = I_("SA");
   const I_CHAR * const SRS_TAX_TYPE                     = I_("SR");
   const I_CHAR * const	FAST							 = I_( "30" );
   const I_CHAR * const iFAST_SICAV						 = I_ ("31" );
   const I_CHAR * const iFAST_OEIC						 = I_ ("32" );
   const I_CHAR * const RESP_TAX_TYPES                   = I_("9,M");
   const I_CHAR * const RDSP_TAX_TYPE					 = I_("RS");
   const I_CHAR * const RDSP_BENEFICIARY				 = I_("79");
   const I_CHAR * const RDSP_PCG						 = I_("80");
   const I_CHAR * const IDSEARCH_LEVEL                   = I_("12");
   const I_CHAR * const IDSEARCH_CATEGORY                = I_("9");
   const I_CHAR * const UNVERIFIED                       = I_("02");
   const I_CHAR * const VERIFIED                         = I_("01");

}

namespace IDS
{
   extern CLASS_EXPORT const I_CHAR * const DRIVERS_LICENSE          = I_ ("01");
   extern CLASS_EXPORT const I_CHAR * const PASSPORT                 = I_ ("02");
   extern CLASS_EXPORT const I_CHAR * const BIRTH_CERTIFICATE        = I_ ("03");
   extern CLASS_EXPORT const I_CHAR * const CREDIT_CARD              = I_ ("04");
   extern CLASS_EXPORT const I_CHAR * const NATIONAL_ID              = I_ ("05");
   extern CLASS_EXPORT const I_CHAR * const SIN                      = I_ ("06");
   extern CLASS_EXPORT const I_CHAR * const TAX_ID_NUMBER            = I_ ("08");
   extern CLASS_EXPORT const I_CHAR * const BIC_CODE                 = I_ ("10");
   extern CLASS_EXPORT const I_CHAR * const ADDITIONAL_ACCT_NUMBER   = I_ ("12");
   extern CLASS_EXPORT const I_CHAR * const CIF                      = I_ ("15");
   extern CLASS_EXPORT const I_CHAR * const ACCESS_ID                = I_ ("16");
   extern CLASS_EXPORT const I_CHAR * const BUSINESS_NUMBER          = I_ ("17");
   extern CLASS_EXPORT const I_CHAR * const CLEARING_PLATFORM        = I_ ("18"); //MT535/MT536
   extern CLASS_EXPORT const I_CHAR * const FUND_ACCOUNTANT          = I_ ( "FNACGR" );
   extern CLASS_EXPORT const I_CHAR * const FUND_CUSTODIAN           = I_ ( "FNDCST" );
   extern CLASS_EXPORT const I_CHAR * const NEQ                      = I_ ("22");
   extern CLASS_EXPORT const I_CHAR * const LOAN_TYPE                = I_ ("25"); 
   extern CLASS_EXPORT const I_CHAR * const TRUST_ACCOUNT_NUMBER     = I_ ("24");
   extern CLASS_EXPORT const I_CHAR * const LOAN_NUMBER              = I_ ("26"); 
   extern CLASS_EXPORT const I_CHAR * const CPFB_ACCNUM              = I_ ("28");
   extern CLASS_EXPORT const I_CHAR * const EMPLOYER_NUMBER          = I_ ("29");
   extern CLASS_EXPORT const I_CHAR * const OTHER                    = I_ ("99");
   extern CLASS_EXPORT const I_CHAR * const FAST					 = I_ ("30" );
   extern CLASS_EXPORT const I_CHAR * const iFAST_SICAV				 = I_ ("31" );
   extern CLASS_EXPORT const I_CHAR * const iFAST_OEIC				 = I_ ("32" );
   extern CLASS_EXPORT const I_CHAR * const FSA_NUMBER				 = I_ ("33" );
   extern CLASS_EXPORT const I_CHAR * const FATCA_GIIN               = I_ ("35" );
   extern CLASS_EXPORT const I_CHAR * const SOCIAL_SECURITY_NUMBER   = I_ ("39" );
   extern CLASS_EXPORT const I_CHAR * const TRANSMITTER_NUMBER       = I_ ("43" );
   extern CLASS_EXPORT const I_CHAR * const ACCOUNT_MANAGER_UNIQUE_ID = I_("45");
   extern CLASS_EXPORT const I_CHAR * const TAX_FILE_NUMBER            = I_("46");         
   extern CLASS_EXPORT const I_CHAR * const AUSTRALIAN_BUSINESS_NUMBER = I_("47");
   extern CLASS_EXPORT const I_CHAR * const AEOI					 = I_("48");
}

namespace ID_STATUS
{
   extern CLASS_EXPORT const I_CHAR * const VALID                 = I_ ("01");
   extern CLASS_EXPORT const I_CHAR * const INVALID               = I_ ("02");
   extern CLASS_EXPORT const I_CHAR * const OVERRIDE              = I_ ("03");
   extern CLASS_EXPORT const I_CHAR * const EXPIRED               = I_ ("04");
   extern CLASS_EXPORT const I_CHAR * const RESET                 = I_ ("05");
   extern CLASS_EXPORT const I_CHAR * const UNVERIFIED            = I_ ("06");
}

namespace ENTITY_CATEGORY
{
   extern const I_CHAR * const NOT_APPICABLE;
   extern const I_CHAR * const INDIVIDUAL;
   extern const I_CHAR * const CORPORATE;
   extern const I_CHAR * const TRUST;
}

namespace ACCOUNT_TYPE
{
   extern const I_CHAR * const CORPORATE;
}

//******************************************************************************
SEVERITY EntityIds::validateSINOnSystem ( DSTCWorkSession &rpDSTCWorkSession, 
                                          const DString &entityId,
                                          const DString &sin,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSINOnSystem"));

   AccountEntityXref *pAEXref = NULL;
   bool bIsValid = true;
   
   if (rpDSTCWorkSession.getAccountEntityXref (idDataGroup, pAEXref) <= WARNING)
   {
      //look whether SIN is required, in memory
      DString searchKey;
      BFObjIter iter (*pAEXref, idDataGroup, true, 
         BFObjIter::ITERTYPE::NON_DELETED);

      AccountEntityXref::buildPartialKeyForEntityId (searchKey, entityId);
      if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
      {
         while (!iter.end())
         {
            DString entityType, 
               taxType;

            iter.getObject()->getField (ifds::EntityType, entityType, 
               idDataGroup, false);
            //look for tax type in MFAccount
            DString accountNum;
            MFAccount *pMFAccount = NULL;

            iter.getObject()->getField (ifds::AccountNum, accountNum, 
               idDataGroup, false);
            if (rpDSTCWorkSession.getMFAccount (
               idDataGroup, accountNum, pMFAccount) <= WARNING &&
               pMFAccount)
            {
               pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
            }
            if (EntityIds::validateSIN (rpDSTCWorkSession, 
                                        taxType, 
                                        entityType, 
                                        sin,
                                        entityId,
                                        idDataGroup) >= WARNING)
            {
               break;
            }
            ++iter;
         }
      }
      if (bIsValid)
      {
         //back-end
         WhereUsedList whereUsed (rpDSTCWorkSession);
      
         if (whereUsed.init (entityId) > WARNING)
         {
            int count = CONDITIONCOUNT();
            Condition *c = NULL;
            for (int i = 0; i < count; i++)
            {
               c = GETCONDITION (i);
               int condCode = c->getCode();
               //clear conditions, we really do not care here, 
               //if the entity is not found to promote the error condition,
               //we only care if it is used somewhere else
               if (condCode == CND::ERR_DATA_NOT_FOUND ||
                   condCode == CND::ERR_ENTITY_NOT_FOUND)
               {
                  CLEARCONDITION(i);
                  break;
               }
            }
         }
         else
         {
            BFObjIter iter (whereUsed, 
                            idDataGroup, 
                            true, 
                            BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end())
            {            
               DString entityType, 
                  taxType;

               iter.getObject()->getField (ifds::EntityType, 
                                           entityType, 
                                           idDataGroup, false);
               iter.getObject()->getField (ifds::TaxType, taxType, 
                                           idDataGroup, false);

               if (EntityIds::validateSIN (rpDSTCWorkSession, 
                                           taxType, 
                                           entityType, 
                                           sin,
                                           entityId,
                                           idDataGroup) > WARNING)
               {
                  bIsValid = false;
                  break;
               }
               ++iter;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool EntityIds::isSINExcepted (DSTCWorkSession &rpDSTCWorkSession, 
                               const DString &sin,
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSINExcepted"));
   
   DString sinException,
      fmtSIN,
      sinCopy (sin);

   rpDSTCWorkSession.getOption (ifds::SinException, sinException, 
      idDataGroup, false);
   sinException = I_(",") + sinException + I_(",");
   fmtSIN = I_(",") + sinCopy.strip () + I_(",");

   return sinException.find (fmtSIN) != DString::npos;
}

//******************************************************************************
bool EntityIds::isSINRequired (DSTCWorkSession &rpDSTCWorkSession, 
                               const DString &taxType,
                               const DString &entityType,
                               const BFDataGroupId &idDataGroup,
                               //this will return whether the ErrorMsgRulesList has been checked
                               bool &bCheckedErrMsgList, 
                               DString &strErrValue /*=I_("W")*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSINRequired"));

   bool bSINRequired = false;

   if( ( taxType == INDIVIDUAL_RESP_TAX_TYPE || taxType == FAMILY_RESP_TAX_TYPE) &&
       ( entityType == ACCOUNT_OWNER || entityType == RESP_BENEFICIARY || 
         entityType == RESP_PCG_INDIV ) )
   {
      ErrMsgRulesList *pErrMsgRulesList = NULL;

      if ( rpDSTCWorkSession.getMgmtCo ().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
           pErrMsgRulesList)
      {
         pErrMsgRulesList->getEWIValue (SIN_REQ_ERR_MSG_CODE, //395
                                        idDataGroup, 
                                        strErrValue);
         bSINRequired = strErrValue == I_("E");
      }
   }
   else if( taxType == TFSA )
   {
      TaxTypeRuleList *ptaxTypeRuleList=NULL;
      if( rpDSTCWorkSession.getMgmtCo().getTaxTypeRuleList( ptaxTypeRuleList ) <= WARNING && ptaxTypeRuleList )
      {
         BFObjIter iterList( *ptaxTypeRuleList, BF::HOST, false );
         DString strKey;
         ptaxTypeRuleList->getStrKey( strKey, taxType, I_("00") );
         if( iterList.positionByKey( strKey ) )
         {
            DString strSINRequired = NULL_STRING;
            iterList.getObject()->getField( ifds::SINRequired, strSINRequired, BF::HOST, false );
            if( strSINRequired.strip() == I_("2"))
            {
               bSINRequired = true;
            }
         }
      }
   }
   else if( taxType == RDSP_TAX_TYPE )
   {
	   bSINRequired = true;
   }

   bCheckedErrMsgList = bSINRequired;
   return bSINRequired;
}

//********************************************************************************
DString EntityIds::getEntityTypeDescription ( DSTCWorkSession &rpDSTCWorkSession,
                                              const DString &entityType,
                                              const BFDataGroupId &idDataGroup)
{
   DString code,
      description,
      substList;

   BFProperties *pProperties = 
      rpDSTCWorkSession.getFieldProperties (ifds::EntityType, idDataGroup);

   pProperties->getAllSubstituteValues (substList);  

   I_CHAR *temp = const_cast<I_CHAR*> (substList.c_str());

   do
   {
      temp = parseIdiString (temp, code, description);
   } 
   while (code != entityType && temp && temp != NULL_STRING && *temp);

   return description;
}

//********************************************************************************
SEVERITY EntityIds::validateAdditionalAcctNumber (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAdditionalAcctNumber "));

   Entity         *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
   EntityIdsList  *pEntityIdsList = NULL;

   if (pEntity)
   {
      pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);

      if (pEntityIdsList)
      {
         BFObjIter iterIds (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         iterIds.begin();
         int count = 0;

         while (!iterIds.end())
         {
            DString strIdType;

            iterIds.getObject()->getField (ifds::IdType, strIdType, idDataGroup, false);

            if (strIdType == IDS::ADDITIONAL_ACCT_NUMBER && count == 0)
            {
               count++;
            }
            else if (strIdType == IDS::ADDITIONAL_ACCT_NUMBER)
            {
               ADDCONDITIONFROMFILEIDI (CND::ERR_ONE_FS_ALT_ACCOUNT, I_(""));
               break;
            }

            ++iterIds;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateBICCode (DSTCWorkSession &rpDSTCWorkSession,
                                     const DString &dstrBICCode,
                                     const DString &dstrEntityId,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBICCode"));

   DString                searchKey;
   WorkSessionEntityList *pWorkSessionEntityList;
   Entity                *pLstEntity;

   if ( getWorkSession().getWorkSessionEntityList (pWorkSessionEntityList, idDataGroup) <= WARNING &&	 
         pWorkSessionEntityList)
   {
      bool bNetworkSender = false;
      bool bLstNetworkSender = false;
      BFObjIter iter (*pWorkSessionEntityList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

      if (pEntity)
      {
         bNetworkSender = pEntity->isNetworkSenderEntity (idDataGroup);
      }

      while( !iter.end() )
      {
         pLstEntity = dynamic_cast<Entity*>( iter.getObject() );
         bool	found = false;

         if (pLstEntity != NULL)
         {
            EntityIdsList  *pEntityIdsList = NULL;
            DString         entityId;

            pLstEntity->getEntityId (entityId); 

            bLstNetworkSender = pLstEntity->isNetworkSenderEntity (idDataGroup);

            if (!bNetworkSender && !bLstNetworkSender)
            {
               // if both entites are not NS skip
               ++iter;
               continue;
            }

            // check other entities that are in the memory:
            pLstEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);

            if (pEntityIdsList)
            {
               BFObjIter iterIds (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iterIds.begin();
               int count = 0;
               while (!iterIds.end())
               {
                  DString strIdType, tmpBICCode,goodBad,lastName;

                  iterIds.getObject()->getField (ifds::IdType, strIdType, idDataGroup, false);

                  if (strIdType == IDS::BIC_CODE)
                  {
                     iterIds.getObject()->getField (ifds::IdValue, tmpBICCode, idDataGroup, false);
                     iterIds.getObject()->getField (ifds::GoodBad, goodBad, idDataGroup, false);

                     tmpBICCode.upperCase ();
                     DString bcode = dstrBICCode;
                     bcode.upperCase ();

                     if (entityId.stripLeading ('0') == dstrEntityId && bcode.stripLeading ('0') == tmpBICCode && goodBad.stripLeading ('0')==I_("Y"))
                     {
                        count++;

                        // there is more than one unique bic code in the same entity.
                        if (count > 1)
                        {
                           ADDCONDITIONFROMFILEIDI (CND::ERR_DUPLICATE_BICCODE, I_(""));
                           found = true;
                           break;
                        }
                     }
                     else if (bcode.stripAll() == tmpBICCode.stripAll() && goodBad.stripAll()==I_("Y"))
                     {
                        ADDCONDITIONFROMFILEIDI (CND::ERR_DUPLICATE_BICCODE, I_("") );
                        found = true;
                        break;
                     }
                  }
                  ++iterIds;
               }
            }
         }

         if (found)
            break;

         ++iter;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateNEQ (DSTCWorkSession &rpDSTCWorkSession,
                                 const DString &dstrNEQ,
                                 const DString &dstrEntityId,
                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateNEQ"));

   DString                searchKey;
   WorkSessionEntityList *pWorkSessionEntityList;
   Entity                *pLstEntity;

   if ( getWorkSession().getWorkSessionEntityList (pWorkSessionEntityList, idDataGroup) <= WARNING &&	 
         pWorkSessionEntityList)
   {
      bool bNEQEntity = false;
      bool bLstNEQEntity = false;
      BFObjIter iter (*pWorkSessionEntityList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

      if (pEntity)
      {
         bNEQEntity = pEntity->isNEQEntity (idDataGroup);
      }

      while( !iter.end() )
      {
         pLstEntity = dynamic_cast<Entity*>( iter.getObject() );
         bool	found = false;

         if (pLstEntity != NULL)
         {
            EntityIdsList  *pEntityIdsList = NULL;
            DString         entityId;

            pLstEntity->getEntityId (entityId); 

            bLstNEQEntity = pLstEntity->isNEQEntity (idDataGroup);

            if (!bNEQEntity && !bLstNEQEntity)
            {
               // if both entites are not NS skip
               ++iter;
               continue;
            }

            // check other entities that are in the memory:
            pLstEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);

            if (pEntityIdsList)
            {
               BFObjIter iterIds (*pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iterIds.begin();
               int count = 0;
               while (!iterIds.end())
               {
                  DString strIdType, tmpNEQ, goodBad,lastName;

                  iterIds.getObject()->getField (ifds::IdType, strIdType, idDataGroup, false);

                  if (strIdType == IDS::NEQ)
                  {
                     iterIds.getObject()->getField (ifds::IdValue, tmpNEQ, idDataGroup, false);
                     iterIds.getObject()->getField (ifds::GoodBad, goodBad, idDataGroup, false);

                     tmpNEQ.upperCase ();
                     DString neq = dstrNEQ;
                     neq.upperCase ();

                     if (entityId.stripLeading ('0') == dstrEntityId && neq.stripLeading ('0') == tmpNEQ && goodBad.stripAll () ==I_("Y"))
                     {
                        count++;

                        // there is more than one unique neq code in the same entity.
                        if (count > 1)
                        {
                           found = true;
                           break;
                        }
                     }
                     else if (neq.stripAll() == tmpNEQ.stripAll() && goodBad.stripAll()==I_("Y"))
                     {
                        found = true;
                        break;
                     }
                  }
                  ++iterIds;
               }
            }
         }

         if (found)
         {
            getErrMsg (IFASTERR::DUPLICATE_NEQ, 
                       CND::ERR_DUPLICATE_NEQ, 
                       CND::WARN_DUPLICATE_NEQ, 
                       idDataGroup);
            break;
         }

         ++iter;
      }
   }


   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateSIN (DSTCWorkSession &rpDSTCWorkSession,
                                 const DString &sin,
                                 const DString& strEntityTypeFmt,
                                 const BFDataGroupId &idDataGroup,
                                 bool bIsSINRequired /*=false*/,
                                 bool bIgnoreWarnings /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSIN"));

   DString sinCopy (sin);
   
   if (!sin.empty() || bIsSINRequired)
   {
      if (!EntityIds::isSINExcepted (rpDSTCWorkSession, sin, idDataGroup))
      {
         bool bSINInvalid = false;

         if (sinCopy.isAllDigits ())
         {
            if (sinCopy.length () == 9)
            {
               int even1, even2, even3, even4,
                  odd1, odd2, odd3, odd4;
               DString strEven, 
                  strOdd;

               strEven = sinCopy.substr (1, 1);
               even1   = strEven.asInteger () * 2;
               strEven = sinCopy.substr (3, 1);
               even2   = strEven.asInteger () * 2;
               strEven = sinCopy.substr (5, 1);
               even3   = strEven.asInteger () * 2;
               strEven = sinCopy.substr (7, 1);
               even4   = strEven.asInteger () * 2;
               strOdd = sinCopy.substr (0, 1);
               odd1   = strOdd.asInteger ();
               strOdd = sinCopy.substr (2, 1);
               odd2   = strOdd.asInteger ();
               strOdd = sinCopy.substr (4, 1);
               odd3   = strOdd.asInteger ();
               strOdd = sinCopy.substr (6, 1);
               odd4   = strOdd.asInteger ();
               if (even1 > 9)
               {
                  even1 = even1 - 9;
               }
               if (even2 > 9)
               {
                  even2 = even2 - 9;
               }
               if (even3 > 9)
               {
                  even3 = even3 - 9;
               }
               if (even4 > 9)
               {
                  even4 = even4 - 9;
               }
               even1 = even1 + even2 + even3 + even4;
               odd1  = odd1  + odd2  + odd3  + odd4;
               even1 = even1 + odd1;
               even1 = even1 % 10;
               if (even1 == 0)
               {
                  even1 = 0;
               }
               else
               {
                  even1 = 10 - even1;
               }
               if (even1 != (sinCopy.asInteger ()) % 10)
               {
                  bSINInvalid = true;
               }
            }
            else
            {
               bSINInvalid = true;
            }
         }
         else
         {
            bSINInvalid = true;
         }
         if (bSINInvalid)
         {
            DString idiString;
            addIDITagValue (idiString, I_("entitydescription"), strEntityTypeFmt);

            if (bIsSINRequired)
            {
					ADDCONDITIONFROMFILEIDI (CND::ERR_E_INVALID_SIN, idiString);
				}
            else if (!bIgnoreWarnings)
            {
					ADDCONDITIONFROMFILE (CND::ERR_W_INVALID_SIN);
				}
            }
         }
      else
      {
         if (bIsSINRequired)
         {
            ADDCONDITIONFROMFILE (CND::ERR_E_INVALID_SIN);
         }
         else if (!bIgnoreWarnings)
         {
            DString idiString;
            addIDITagValue (idiString, I_("entitydescription"), strEntityTypeFmt);

            ADDCONDITIONFROMFILEIDI (CND::ERR_W_INVALID_SIN, idiString);
         }
      }
   }
   else if (sin == NULL_STRING)
   {
      if (bIsSINRequired)
      {
         DString idiString;
         addIDITagValue (idiString, I_("entitydescription"), strEntityTypeFmt);

         ADDCONDITIONFROMFILEIDI (CND::ERR_E_SIN_IS_MISSING, idiString);
      }
      else if (!bIgnoreWarnings)
      {
         DString idiString;
         addIDITagValue (idiString, I_("entitydescription"), strEntityTypeFmt);
      
         ADDCONDITIONFROMFILEIDI (CND::ERR_W_SIN_IS_MISSING, idiString);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateIDType (DSTCWorkSession &rpDSTCWorkSession, 
                                    const DString &idType,
                                    const DString &idValue, 
                                    const BFDataGroupId &idDataGroup, 
                                    bool bIsIDTypeRequired, 
                                    bool bIgnoreWarnings )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateIDType"));

   DString strIDValueCopy(idValue);

   // only support for PCG busines number, copy logic of number check sum from SIN
   if ( idType ==  IDS::BUSINESS_NUMBER )
   {
      if ( !idValue.empty() || bIsIDTypeRequired )
      {
         bool bIDValueInvalid = false;

         if (strIDValueCopy.isAllDigits ())
         {
            if (strIDValueCopy.length () == 9)
            {
               int even1, even2, even3, even4,
                  odd1, odd2, odd3, odd4;
               DString strEven, 
                  strOdd;

               strEven = strIDValueCopy.substr (1, 1);
               even1   = strEven.asInteger () * 2;
               strEven = strIDValueCopy.substr (3, 1);
               even2   = strEven.asInteger () * 2;
               strEven = strIDValueCopy.substr (5, 1);
               even3   = strEven.asInteger () * 2;
               strEven = strIDValueCopy.substr (7, 1);
               even4   = strEven.asInteger () * 2;
               strOdd = strIDValueCopy.substr (0, 1);
               odd1   = strOdd.asInteger ();
               strOdd = strIDValueCopy.substr (2, 1);
               odd2   = strOdd.asInteger ();
               strOdd = strIDValueCopy.substr (4, 1);
               odd3   = strOdd.asInteger ();
               strOdd = strIDValueCopy.substr (6, 1);
               odd4   = strOdd.asInteger ();
               if (even1 > 9)
               {
                  even1 = even1 - 9;
               }
               if (even2 > 9)
               {
                  even2 = even2 - 9;
               }
               if (even3 > 9)
               {
                  even3 = even3 - 9;
               }
               if (even4 > 9)
               {
                  even4 = even4 - 9;
               }
               even1 = even1 + even2 + even3 + even4;
               odd1  = odd1  + odd2  + odd3  + odd4;
               even1 = even1 + odd1;
               even1 = even1 % 10;
               if (even1 == 0)
               {
                  even1 = 0;
               }
               else
               {
                  even1 = 10 - even1;
               }
               if (even1 != (strIDValueCopy.asInteger ()) % 10)
               {
                  bIDValueInvalid = true;
               }
            }
            else
            {
               bIDValueInvalid = true;
            }
         }
         else
         {
            bIDValueInvalid = true;
         }

         if (bIDValueInvalid)
         {
            if (bIsIDTypeRequired)
            {
               ADDCONDITIONFROMFILE (CND::ERR_E_INVALID_ID_VALUE);
            }
            else if (!bIgnoreWarnings)
            {
               ADDCONDITIONFROMFILE (CND::ERR_W_INVALID_ID_VALUE);
            }
         }
      }
      else if (idValue == NULL_STRING)
      {
         if (bIsIDTypeRequired)
         {
            ADDCONDITIONFROMFILE (CND::ERR_E_ID_VALUE_IS_MISSING);
         }
         else if (!bIgnoreWarnings)
         {
            ADDCONDITIONFROMFILE (CND::ERR_W_ID_VALUE_IS_MISSING);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateSIN (DSTCWorkSession &rpDSTCWorkSession, 
                                 const DString &taxType,
                                 const DString &entityType,
                                 const DString &sin,
                                 const DString &entityId,
                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSIN"));

   DString description (
      getEntityTypeDescription (rpDSTCWorkSession, 
         entityType, idDataGroup)),
         strErrValue (NULL_STRING);
   DString strEntityID(entityId);

   Entity* pEntity = NULL;
   DString strEmployeeClass(NULL_STRING),
      strEntityTypeFmt;
   rpDSTCWorkSession.getEntity (idDataGroup, strEntityID, pEntity);

   if(pEntity)
   {
      pEntity->getField( ifds::EmployeeClass, strEmployeeClass, idDataGroup, false );
      pEntity->getField( ifds::EntityType, strEntityTypeFmt, idDataGroup, true );
      strEmployeeClass.strip().upperCase();
   }

   bool bCheckedErrMsgList = false, 
        bIsSINRequired = isSINRequired ( rpDSTCWorkSession, 
                                         taxType, 
                                         entityType, 
                                         idDataGroup, 
                                         bCheckedErrMsgList, 
                                         strErrValue );

   EntityIds::validateSIN (rpDSTCWorkSession, 
                           sin,
                           !strEntityTypeFmt.empty()?strEntityTypeFmt:description, 
                           idDataGroup, 
                           bIsSINRequired, 
                           strErrValue == I_("I"));

   int count = CONDITIONCOUNT();
   Condition *c = NULL;

   for (int i = 0; i < count; i++)
   {
      c = GETCONDITION (i);
      int condCode = c->getCode();

      CLEARCONDITION (i);

      if ((condCode == CND::ERR_W_SIN_IS_MISSING || condCode == CND::ERR_E_SIN_IS_MISSING) &&
           strEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL && entityType == ACCOUNT_OWNER )
      {
         ADDCONDITIONFROMFILE (CND::ERR_ACCTOWNER_SIN_MISSING);
      }
      else if ((condCode == CND::ERR_W_SIN_IS_MISSING  || condCode == CND::ERR_E_SIN_IS_MISSING )&&
               entityType == ACCOUNT_OWNER && strEmployeeClass == ENTITY_CATEGORY::CORPORATE)
      {
         //not put condition for SIN if employee class is corporate
      }
      else if ((condCode == CND::ERR_W_INVALID_SIN  || condCode == CND::ERR_E_INVALID_SIN )&&
               entityType == ACCOUNT_OWNER && strEmployeeClass == ENTITY_CATEGORY::CORPORATE)
      {
         //not put condition for SIN if employee class is corporate
      }
      else if ((condCode == CND::ERR_W_SIN_IS_MISSING || condCode == CND::ERR_E_SIN_IS_MISSING )&&
                strEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL)
      {
         DString idiString;
         addIDITagValue (idiString, I_("entitydescription"), description);

         ADDCONDITIONFROMFILEIDI (condCode, idiString);
      }
      else if (condCode == CND::ERR_W_INVALID_SIN &&
               entityType == ACCOUNT_OWNER)
      {
         if (bCheckedErrMsgList ||
            //the following condition is being checked again, 
            //we have to live with it... 
            !EntityIds::isSINExcepted (rpDSTCWorkSession, sin, idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_ACCTOWNER_SIN_INVALID);
         }
      }
      else if ( condCode == CND::ERR_W_SIN_IS_MISSING &&
                entityType == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE &&
               ( taxType == RRIF_TAX_TYPE || 
                 taxType == RRSP_TAX_TYPE || 
                 taxType == RPP_TAX_TYPE || 
                 taxType == PRIF_TAX_TYPE))
      {
         ADDCONDITIONFROMFILE (CND::ERR_SPOUSE_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_W_INVALID_SIN &&
                entityType == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE &&
               (taxType == RRIF_TAX_TYPE || 
                taxType == RRSP_TAX_TYPE || 
                taxType == RPP_TAX_TYPE || 
                taxType == PRIF_TAX_TYPE))
      {
         ADDCONDITIONFROMFILE (CND::ERR_SPOUSE_SIN_INVALID);
      }
      else if ( condCode == CND::ERR_W_SIN_IS_MISSING &&
                entityType == RESP_BENEFICIARY &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RESP_BENEFICIARY_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_E_SIN_IS_MISSING &&
                entityType == RESP_BENEFICIARY &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEFICIARY_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_W_INVALID_SIN &&
                entityType == RESP_BENEFICIARY &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RESP_BENEFICIARY_SIN_INVALID);
      }
      else if ( condCode == CND::ERR_E_INVALID_SIN &&
                entityType == RESP_BENEFICIARY &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEFICIARY_SIN_INVALID);
      }
      else if ( condCode == CND::ERR_W_SIN_IS_MISSING &&
                entityType == RESP_PCG_INDIV &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_E_SIN_IS_MISSING &&
                entityType == RESP_PCG_INDIV &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_W_INVALID_SIN &&
                entityType == RESP_PCG_INDIV &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RESP_PCG_INDIV_SIN_INVALID);
      }
      else if ( condCode == CND::ERR_E_INVALID_SIN &&
                entityType == RESP_PCG_INDIV &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_INVALID);
      }
      else if ( condCode == CND::ERR_E_SIN_IS_MISSING &&
                entityType == RESP_PCG_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         //ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_W_SIN_IS_MISSING &&
                entityType == RESP_PCG_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         //ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_E_INVALID_SIN &&
                entityType == RESP_PCG_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         //ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_W_INVALID_SIN &&
                entityType == RESP_PCG_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         //ADDCONDITIONFROMFILE (CND::ERR_RESP_PCG_INDIV_SIN_MISSING);
      }
      else if ( condCode == CND::ERR_E_INVALID_SIN &&
                entityType == RESP_DSGN_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         // not put new condition of SIN validation for RESP Designated Inst 
      }
      else if ( condCode == CND::ERR_W_INVALID_SIN &&
                entityType == RESP_DSGN_INST &&
               ( taxType == INDIVIDUAL_RESP_TAX_TYPE || 
                 taxType == FAMILY_RESP_TAX_TYPE ) )
      {
         // not put new condition of SIN validation for RESP Designated Inst 
      }
	  else if ( condCode == CND::ERR_E_INVALID_SIN &&
			   ( entityType == RDSP_PCG || 
			     entityType == RDSP_BENEFICIARY ) && 
				sin.empty())
	  {
		  DString idiString;
		  addIDITagValue (idiString, I_("entitydescription"), description);
		  ADDCONDITIONFROMFILEIDI (CND::ERR_E_SIN_IS_MISSING, idiString);	
	  }
      else
      {
         DString strIDI;

         addIDITagValue (strIDI, I_("entitydescription"), description);
         ADDCONDITIONFROMFILEIDI (condCode, strIDI);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::validateTrustAccountNum (DSTCWorkSession &rpDSTCWorkSession,
                                             const DString &dstrTrustAccountNum,
                                             const DString &dstrEntityId,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTrustAccountNum"));

   Entity* pEntity = NULL;
   rpDSTCWorkSession.getEntity (idDataGroup, dstrEntityId, pEntity);

   if(pEntity)
   {
      DString strTaxJuris, strResidency1, strResidency2, strResidency3;
      pEntity->getField( ifds::TaxJuris, strTaxJuris, idDataGroup, false );
      strTaxJuris.strip().upperCase();

      rpDSTCWorkSession.getOption( ifds::Residency1, strResidency1, idDataGroup, false );
      rpDSTCWorkSession.getOption( ifds::Residency2, strResidency2, idDataGroup, false );
      rpDSTCWorkSession.getOption( ifds::Residency3, strResidency3, idDataGroup, false );

      if( ( DSTCommonFunctions::codeInList( strTaxJuris, strResidency1 ) ||
            DSTCommonFunctions::codeInList( strTaxJuris, strResidency2 ) ||
            DSTCommonFunctions::codeInList( strTaxJuris, strResidency3 ) ))
      {
         if(isTrustNumberValid(rpDSTCWorkSession,dstrTrustAccountNum,idDataGroup) <= WARNING)
         {
            // find for duplicate trust number within the same entity ?
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
EntityIds::EntityIds (BFAbstractCBO &parent) 
: MFCanBFCbo (parent),
_market (NULL_STRING),
_dstrVerifyFilter (NULL_STRING),
_bIsDirty (false),
_bVerificationEnabled (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   _market = DSTCommonFunctions::getMarket ();

   addCrossEdit(ifds::XrefNum, ifds::IdType );
   addCrossEdit(ifds::XrefNum, ifds::IdValue );
   addCrossEdit(ifds::XrefCountryOfIssue, ifds::IdType );
   addCrossEdit(ifds::XrefCountryOfIssue, ifds::CountryOfIssue);
}

//******************************************************************************
EntityIds::~EntityIds ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY EntityIds::init ( const BFDataGroupId &idDataGroup, 
                           const DString &entityId,
                           const DString &entityType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init, idDataGroup"));

   setFieldNoValidate (ifds::EntityId, entityId, idDataGroup, false, true);
   setFieldNoValidate (ifds::EntityType, entityType, idDataGroup, false, true);

   //MT535/MT536
   DString idType;
   
   getField (ifds::IdType, idType, idDataGroup, false);
   if (idType == IDS::CLEARING_PLATFORM)
   { //MT53X
      initializeClearingPlatformIDList(idDataGroup);

      if( isNew() )
      {
         setFieldNoValidate( ifds::IdValue, NULL_STRING, idDataGroup, false );
      }
      // MT53X - End
   }
   else
   {
      setFieldSubstituteValues (ifds::IdValue, idDataGroup, ifds::NullFieldId);
   }

   if (idType == IDS::BIC_CODE && entityType == I_("58"))
   {
      setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::ValidInvalidIdStatus);
   }
   else if (idType == IDS::FATCA_GIIN)
   {
      initStatusForGIIN (idDataGroup);
   }
   else
   {
      setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::IdStatus);
   }

   initalizeXrEnvRefIDTypes(idDataGroup);
   DString str12319999;
   getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);

   setFieldNoValidate( ifds::IdExpireDate, str12319999, idDataGroup, false );

   initVerifyStatus (idDataGroup, false);
   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::init ( const BFData &data, 
                           const DString &entityId,
                           const DString &entityType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init,data"));

   setFieldNoValidate (ifds::EntityId, entityId, BF::HOST, false, true);
   setFieldNoValidate (ifds::EntityType, entityType, BF::HOST, false, true);
   attachDataObject (const_cast<BFData&> (data), false, true);
   setAllFieldsReadOnly (BF::HOST);
   DString status; // if entity status is bad we should not allow user to change it. 
   Entity* pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
   if (pEntity)
   {
      pEntity->getField (ifds::GoodBad, status, BF::HOST, false);
      status.strip().upperCase();
      if( status == I_("N") )
      {
         setFieldReadOnly (ifds::EntityId, BF::HOST, true);
         setFieldReadOnly (ifds::IdType, BF::HOST, true);
         setFieldReadOnly (ifds::IdValue, BF::HOST, true);
         setFieldReadOnly (ifds::IdDate, BF::HOST, true);
         setFieldReadOnly (ifds::SIN, BF::HOST, true);
      }

      //MT535/MT536
      DString idType;

      getField (ifds::IdType, idType, BF::HOST, false);
      if (idType == IDS::CLEARING_PLATFORM)
      {  // MT53X    
         initializeClearingPlatformIDList(BF::HOST, true);
      }
      else
      {
         setFieldSubstituteValues (ifds::IdValue, BF::HOST, ifds::NullFieldId);
      }

      if (idType == IDS::BIC_CODE && entityType == I_("58"))
      {
         setFieldSubstituteValues (ifds::IdStatus, BF::HOST, ifds::ValidInvalidIdStatus);
      }
      else if(idType == IDS::FATCA_GIIN)
      {
         initStatusForGIIN(BF::HOST);
      }
      else if(idType == IDS::TAX_FILE_NUMBER)
	    {
	      //If user doesn't has read permission, entity id value will be masked as **** (Only band APAC_SUPREGN).	
	      if(!getWorkSession().hasReadPermission(UAF::APAC_SUPREGN))
		      setFieldNoValidate(ifds::IdValue, I_("********"),BF::HOST,false,true,false,false);
	    }
      else
      {
         setFieldSubstituteValues (ifds::IdStatus, BF::HOST, ifds::IdStatus);
      }

      if( idType == IDS::BIRTH_CERTIFICATE ||idType == IDS::DRIVERS_LICENSE || 
          idType == IDS::PASSPORT || idType == IDS::NATIONAL_ID || 
          idType == IDS::TRUST_ACCOUNT_NUMBER || idType == IDS::BIC_CODE || 
          idType == IDS::EMPLOYER_NUMBER || idType == IDS::TAX_ID_NUMBER || 
          idType == IDS::FATCA_GIIN || idType == IDS::SOCIAL_SECURITY_NUMBER ||
		  idType == IDS::AEOI)
      {
         setFieldReadOnly (ifds::CountryOfIssue, BF::HOST, false);
      }
      else
      {
         setFieldReadOnly (ifds::CountryOfIssue, BF::HOST, true); 
      }

	  initalizeXrEnvRefIDTypes(BF::HOST);

   }
   initVerifyStatus (BF::HOST, false);
   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::doValidateField  ( const BFFieldId &idField,
                                       const DString &strValue,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateField"));

   DString entityId,
      strFATCAApplicable;
   Entity *pEntity = NULL;
   bool    bNetworkSender = false;

   getWorkSession ().getOption (ifds::FATCAApplicable,strFATCAApplicable, idDataGroup, false);
   strFATCAApplicable.strip().upperCase();

   if (idField == ifds::XrefNum)
   {
      DString idValue, 
         idType;

      getField (ifds::IdType, idType, idDataGroup, false);
      getField (ifds::IdValue, idValue, idDataGroup, false);

      if (_market == MARKET_IDS::CANADA && idType == IDS::SIN)
      {
         DString entityId,
            strEntityTypeFmt;
         getField (ifds::EntityId, entityId, idDataGroup, false);
         getWorkSession().getEntity (idDataGroup, entityId, pEntity);
         if(pEntity)
         {
            pEntity->getField( ifds::EntityType, strEntityTypeFmt, idDataGroup, true );
         }

         if (Entity::bUsedByEntityAlone)
         {
            if ( validateSIN (getWorkSession(), idValue, strEntityTypeFmt, idDataGroup) <= WARNING )
            {
               checkForDuplicateSIN (idValue, idDataGroup);
            }
         }
         else
         {
            DString entityId;
            getField (ifds::EntityId, entityId, idDataGroup, false);
            if (EntityIds::validateSINOnSystem ( getWorkSession(), 
                                                 entityId, 
                                                 idValue, 
                                                 idDataGroup) < WARNING)
            {
                  //if DuplicateSINcheck == YES, check SIN for duplicity and add a condition 
                  //but only for a valid SIN - we presume there aren't invalid SINs in the database
               DString strDuplicateSIN;

               getField (ifds::DuplicateSINcheck, strDuplicateSIN, idDataGroup);
               if (strDuplicateSIN == Y)
               {
                  checkForDuplicateSIN (idValue, idDataGroup);
               }
            }
         }
      }
      else if (idType == IDS::BIC_CODE && !idValue.empty ())
      {
         getField (ifds::EntityId, entityId, idDataGroup, false);

         if (validateBICCode (getWorkSession(), idValue, entityId, idDataGroup ) <= WARNING)
         {
            checkForDuplicateBICCode (idValue,idDataGroup);
         }
      }
      else if (idType == IDS::NEQ)
      {
         getField (ifds::EntityId, entityId, idDataGroup, false);

         if (validateNEQ (getWorkSession(), idValue, entityId, idDataGroup ) <= WARNING)
         {
            checkForDuplicateNEQ (idValue,idDataGroup);
         }
      }

      else if (idType == IDS::ADDITIONAL_ACCT_NUMBER && !idValue.empty ())
      {
         Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

         if (pEntity)
         {
            if (pEntity->isFundSponsorEntity (idDataGroup))
            {
               validateAdditionalAcctNumber (idDataGroup);
            }
         }
      }
      else if (idType == IDS::FUND_ACCOUNTANT || 
               idType == IDS::FUND_CUSTODIAN  )
      {
         if ( idValue.empty() )
         {
            DString strIDI, strIDType;
            getField (ifds::IdType, strIDType, idDataGroup, true);
            addIDITagValue (strIDI, I_("BLANK_FIELD"), strIDType);
            ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_IS_BLANK, strIDI);
         }
         else
         {
            Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

            if (pEntity)
            {
               if (pEntity->isFundSponsorEntity (idDataGroup))
               {
                  validateIDValueForIDTypeOnSystem( idType, idValue, idDataGroup );
               }
            }
         }
      }
      else if ( _market == MARKET_IDS::CANADA && idType == IDS::TRUST_ACCOUNT_NUMBER && 
               !idValue.empty () )
      {
         DString dstrEntityId;
         getField( ifds::EntityId, dstrEntityId,idDataGroup, false );
         
         if(dstrEntityId.strip().upperCase().empty())
         {
            Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
            if(pEntity)
            {
               pEntity->getField( ifds::EntityId, dstrEntityId,idDataGroup, false );
               dstrEntityId.strip().upperCase();
            }
         }

         validateTrustAccountNum (getWorkSession(), idValue, dstrEntityId, idDataGroup );
      }
      else if( (idType == IDS::TAX_ID_NUMBER || 
                idType == IDS::EMPLOYER_NUMBER) && !idValue.empty () &&
                strFATCAApplicable == I_("Y"))
      {
         validateTaxIDEmployerIDForFATCA(idType,idDataGroup);
      }
      else if ( _market == MARKET_IDS::CANADA && idType == IDS::BUSINESS_NUMBER && 
               !idValue.empty () )
      {
         DString dstrEntityId,
            dstrSearchKey,
            dstrAccountNum,
            dstrAccountType,
            dstrTaxtype,
            dstrEmployeeClass;

         getField( ifds::EntityId, dstrEntityId,idDataGroup, false );
         dstrEntityId.strip().upperCase();

         AccountEntityXref *pAEXref = NULL;
         if (getWorkSession().getAccountEntityXref (idDataGroup, pAEXref) <= WARNING &&
             pAEXref)
         {
            BFObjIter iter (*pAEXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

            AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);

            Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

            if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey) && pEntity)
            {
               iter.positionByKey (dstrSearchKey);

               iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
               dstrAccountNum.strip().upperCase();

               MFAccount *pMFAccount = NULL;
               if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING )
               {
                  pEntity->getField (ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false);
                  pMFAccount->getField (ifds::AcctType, dstrAccountType, idDataGroup, false);
                  pMFAccount->getField (ifds::TaxType, dstrTaxtype, idDataGroup, false);
                  dstrEmployeeClass.strip().upperCase();
                  dstrAccountType.strip().upperCase();
                  dstrTaxtype.strip().upperCase();

                  if(!dstrAccountType.empty() && 
                     (dstrTaxtype == INDIVIDUAL_RESP_TAX_TYPE || dstrTaxtype == FAMILY_RESP_TAX_TYPE))
                  {
                     EntityIdsList* pList = dynamic_cast<EntityIdsList*>(getParent());
                     if(pList)
                     {
                        DString idiStr, strIDType, strEntCat;
                        bool bHasBIN =  pList->isIdTypeExistWithValue( IDS::BUSINESS_NUMBER, idDataGroup );
                        
                        if (dstrEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL && 
                            dstrAccountType == ACCOUNT_TYPE::CORPORATE)
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
            }
         }
      }
      else if( idType.strip().upperCase() == IDS::FATCA_GIIN && 
               !idValue.strip().upperCase().empty ())
      {
         validateGIINFormat(idDataGroup);
      }
      else if (idType.strip().upperCase() == IDS::TRANSMITTER_NUMBER && 
          !idValue.strip().upperCase().empty())
      {
          validateTransmitterNumberFormat(idDataGroup);
      }
      else
      {
         nonSINRelatedChanges (idDataGroup);
      }
   }
   else if (idField == ifds::XrefCountryOfIssue)
   {
      DString idType;
      getField (ifds::IdType, idType, idDataGroup, false);
      if( idType == IDS::BIRTH_CERTIFICATE ||idType == IDS::DRIVERS_LICENSE ||
          idType == IDS::PASSPORT || idType == IDS::FATCA_GIIN || 
          idType == IDS::TAX_ID_NUMBER || idType == IDS::EMPLOYER_NUMBER || 
          idType == IDS::NATIONAL_ID )
      {
         DString countryOfIssue;
         getField(ifds::CountryOfIssue,countryOfIssue,idDataGroup,false);
         if(countryOfIssue==NULL_STRING)
         {
            ADDCONDITIONFROMFILE(CND::WARN_BLANK_CNTRY_OF_ISSUE);
         }
         else
         {
            validateForOverlappingOfRecords(idType,idDataGroup);
         }
      }
      else if ( idType == IDS::TRUST_ACCOUNT_NUMBER || idType == IDS::BIC_CODE )
      {
         DString countryOfIssue;
         getField(ifds::CountryOfIssue,countryOfIssue,idDataGroup,false);
         if(countryOfIssue==NULL_STRING)
         {
            getErrMsg (IFASTERR::COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER, 
                       CND::ERR_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER, 
                       CND::WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER, 
                       idDataGroup);
         }
      }
      //else if (idType == IDS::TAX_ID_NUMBER || idType == IDS::EMPLOYER_NUMBER )
      //{
      //   DString countryOfIssue;
      //   getField(ifds::CountryOfIssue,countryOfIssue,idDataGroup,false);
      //   if(countryOfIssue==NULL_STRING)
      //   {
      //      getErrMsg (IFASTERR::COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER, 
      //                 CND::ERR_BLANK_CNTRY_OF_ISSUE,
      //                 CND::WARN_BLANK_CNTRY_OF_ISSUE,
      //                 idDataGroup);
      //   }
      //}
      //else if( idType == IDS::NATIONAL_ID )
      //{
      //   DString idValue,dstrCountryofIssue;
      //   getField (ifds::IdValue, idValue, idDataGroup, false); 
      //   getField (ifds::CountryOfIssue, dstrCountryofIssue, idDataGroup, false);
      //   if(!dstrCountryofIssue.empty())
      //   {
      //      //call this if country of issue is not blank also we need to check for dupliacte here before calling validation alogoroith
      //      // ValidateHKID_NRIC(getWorkSession(),idValue,entityId,idDataGroup);
      //      //this should display warning or error based on the rej Error Setup.
      //   }
      //   else
      //      ADDCONDITIONFROMFILE(CND::ERR_BLANK_CNTRY_OF_ISSUE);
      //}
      //else
      //{
      //   setFieldNoValidate (ifds::CountryOfIssue,NULL_STRING, idDataGroup, false, true, true );
      //}
      else
      {
         // do nothing
      }
   }

   else if (idField == ifds::IdType)
   {
      DString dstrEntityType, dstrEntityId;
      getParent()->getParent()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );         
      AccountEntityXref *pAEXref = NULL;
      
      if(getWorkSession().getAccountEntityXref (idDataGroup, pAEXref) <= WARNING &&
         pAEXref)
      {
         DString searchKey;
         BFObjIter iter (*pAEXref, idDataGroup, true, 
                         BFObjIter::ITERTYPE::NON_DELETED);

         AccountEntityXref::buildPartialKeyForEntityId (searchKey, dstrEntityId);
         if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
         {
            while (!iter.end())   /* it's only one */
            {
               iter.getObject()->getField (ifds::EntityType, dstrEntityType, idDataGroup, false);
               ++iter;
            }
         }
      }
      
      if (strValue == IDS::CIF)
      {
         ADDCONDITIONFROMFILE (CND::ERR_CANNOT_ADD_NEW_CIF);
      }
      if (strValue == IDS::ACCESS_ID)
      {
         ADDCONDITIONFROMFILE (CND::ERR_CANNOT_ADD_NEW_ACCESS_ID);
      }
      //MT535/MT536
      if (strValue == IDS::CLEARING_PLATFORM)
      {
         EntityIdsList	*pEntityIdsList = NULL;

         pEntityIdsList = dynamic_cast<EntityIdsList*>(getParent());
         if ( pEntityIdsList )
         {
            int numIdTypeRecord;
            bool bIsIdTypeExist;
            numIdTypeRecord = pEntityIdsList->getNumIdTypeRecord(IDS::CLEARING_PLATFORM, idDataGroup);
            bIsIdTypeExist  = pEntityIdsList->isIdTypeExist(IDS::CLEARING_PLATFORM, idDataGroup);
            if ( bIsIdTypeExist && numIdTypeRecord > 1 )
            {
               ADDCONDITIONFROMFILE (
                  CND::ERR_MULTIPLE_CLEARING_PLATFROM_ID_NOT_ALLOWED_FOR_CLEARING_PLATFORM);
            }
         }
      }

      if(strValue == IDS::CPFB_ACCNUM)
      {
         if(CheckForDuplicateID(strValue,idDataGroup))
            ADDCONDITIONFROMFILE  ( CND::ERR_MULTIPLE_CPFB_ACCOUNT_NUMBER_NOT_ALLOWED_FOR_AN_ENTITY);

      }
	 
	  if(strValue == IDS::FAST || strValue == IDS::iFAST_SICAV || strValue == IDS::iFAST_OEIC)
	  {
		  if(CheckForDuplicateID(strValue,idDataGroup))
		  {
			  DString dstrIDTypeFmt, dstrTemp; 
              getField( idField, dstrIDTypeFmt, idDataGroup, true );
			  addIDITagValue( dstrTemp, I_("IDTYPE"), dstrIDTypeFmt );
			  ADDCONDITIONFROMFILEIDI( CND::ERR_ID_TYPE_DUPLICATED_RECORD, dstrTemp )
		  }
	  }
	 
	
	  if(strValue == IDS::FSA_NUMBER)
	  {
		  if(CheckForDuplicateID(strValue,idDataGroup))
		  {
			  DString dstrIDTypeFmt, dstrTemp; 
			  getField( idField, dstrIDTypeFmt, idDataGroup, true );
			  addIDITagValue( dstrTemp, I_("IDTYPE"), dstrIDTypeFmt );
			  ADDCONDITIONFROMFILEIDI( CND::ERR_ID_TYPE_DUPLICATED_RECORD, dstrTemp )
		  }
	  }
      else if (strValue == IDS::FUND_CUSTODIAN || 
               strValue == IDS::FUND_ACCOUNTANT)
      {
         EntityIdsList *pEntityIdsList = NULL;

         pEntityIdsList = dynamic_cast<EntityIdsList*>(getParent());
         if ( pEntityIdsList )
         {
            int numIdTypeRecord = 0;
            bool bIsIdTypeExist = false;
            numIdTypeRecord = pEntityIdsList->getNumIdTypeRecord(strValue, idDataGroup);
            bIsIdTypeExist  = pEntityIdsList->isIdTypeExist(strValue, idDataGroup);
            if ( bIsIdTypeExist && numIdTypeRecord > 1 )
            {
               DString dstrIDTypeFmt, dstrTemp;

               getField( idField, dstrIDTypeFmt, idDataGroup, true );
               addIDITagValue( dstrTemp, I_("IDTYPE"), dstrIDTypeFmt );
               ADDCONDITIONFROMFILEIDI( CND::ERR_ID_TYPE_DUPLICATED_RECORD, dstrTemp );
            }
         }
      }
      //else if(strValue == IDS::FATCA_GIIN)
      //{
      //   validateForOverlappingOfRecords(strValue,idDataGroup);
      //}
   }
   else if (idField == ifds::IdValue)
   {
      DString idType;

      getField (ifds::IdType, idType, idDataGroup, false);

      if (idType == IDS::ACCESS_ID && !strValue.empty())
      {
         BFData requestData (ifds::DSTC0003_REQ),
                responseData (ifds::DSTC0003_VW);
         DString mgmtCoIdOut;

         requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
         requestData.setElementValue (ifds::NextOrPrevious, N);
         requestData.setElementValue (ifds::AllAccounts, N);
         requestData.setElementValue (ifds::AllEntitys, Y);
         requestData.setElementValue (ifds::SortBy, I_("LN"));
         requestData.setElementValue (ifds::SrchIdType, IDS::ACCESS_ID);
         requestData.setElementValue (ifds::SrchIdValue, strValue);
           
         if (BFDataBroker::getInstance ()->receive ( DSTC_REQUEST::SEARCH, 
                                                     requestData, 
                                                     responseData, 
                                                     DSTCRequestor (getSecurity (), true)) <= WARNING)
         {
            int cRepeats = responseData.getRepeatCount ();
            if (cRepeats <=0)
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_ACCESS_ID);
            }
         }
      }
      else if (idType == IDS::SIN && !strValue.empty())
      {
         if ( getWorkSession ().isRES2Client() )
         {
            validateSINDuplicateForRESP( strValue, idDataGroup );
            
            if(getWorkSession ().isQESIClient())
            {
               if(!isNew())
                  getEWIMsgforRESPBenfSINUpdate(idDataGroup);
            }
         }
      }	
	  else if( (idType == IDS::NATIONAL_ID || idType == IDS::PASSPORT) && !strValue.empty())
	  {
		  validateAcctRegAgent(idDataGroup );
	  }
	  else if( idType == IDS::TAX_FILE_NUMBER && !strValue.empty())
	  {
		   validateTaxFileNum(idDataGroup );
	  }
	  else if(idType == IDS::AUSTRALIAN_BUSINESS_NUMBER && !strValue.empty())
	  {
		   validateAusBusinessNum(idDataGroup);
	  }
	  validationEntitySearchID (idDataGroup);
   }
   else if (idField == ifds::IdStatus)
   {
      DString idType,
         idAllowOverride;

      getField (ifds::IdType, idType, idDataGroup, false);
      getField (ifds::IdAllowOverride, idAllowOverride, idDataGroup, false);

      if (idType == IDS::ACCESS_ID )
      {
         if( strValue == ID_STATUS::OVERRIDE && idAllowOverride == N )
         {
            ADDCONDITIONFROMFILE (CND::ERR_OVERRIDE_IS_NOT_ALLOWED);
         }
         if( strValue == ID_STATUS::INVALID ||
             strValue == ID_STATUS::VALID   ||
             strValue == ID_STATUS::EXPIRED )
         {
            DString idiStr;
            if( strValue == ID_STATUS::INVALID )
            {
               addIDITagValue( idiStr, I_("VAR"), I_( "Invalid" ) );
            }
            else if( strValue == ID_STATUS::VALID )
            {
               addIDITagValue( idiStr, I_("VAR"), I_( "Valid" ) );
            }
            else if( strValue == ID_STATUS::EXPIRED )
            {
               addIDITagValue( idiStr, I_("VAR"), I_( "Expired" ) );
            }
            ADDCONDITIONFROMFILEIDI (CND::ERR_INVALID_STATUS_FOR_ACCESS_ID, idiStr);
         }
         else if( strValue == ID_STATUS::RESET )
         {
            // don't allow reset for an overridden AccessId
            DString dstrOldValue;
            getFieldBeforeImage( ifds::IdStatus, dstrOldValue, false );
            if( dstrOldValue.strip() == ID_STATUS::OVERRIDE )
            {
               ADDCONDITIONFROMFILE (CND::ERR_RESET_OVERRIDE_IS_NOT_ALLOWED);
            }
         }
      }
   }
   else if (idField == ifds::IdDate)
   {   
      if ( getWorkSession ().isQESIClient() )
      {
         if(!isNew())
            getEWIMsgforRESPBenfSINUpdate(idDataGroup);
      }
   }
   else if (idField == ifds::IdExpireDate)
   {
      DString strFATCAApplicable;
      getWorkSession ().getOption (ifds::FATCAApplicable,strFATCAApplicable, idDataGroup, false); 
      strFATCAApplicable.strip().upperCase();
      
      if(strFATCAApplicable == I_("Y") && 
         (strValue.empty() || strValue == I_("12319999")))
      {
         // raise up error?
         ADDCONDITIONFROMFILE (CND::ERR_EXPIRY_DATE_REQUIRED);
      }
   } 
   else if (idField == ifds::CountryOfIssue)
   {
      DString idType,idValue;

      getField (ifds::IdType, idType, idDataGroup, false);
      getField (ifds::IdValue, idValue, idDataGroup, false);

      if( (idType == IDS::NATIONAL_ID || idType == IDS::PASSPORT) && !idValue.empty())
      {
         validateAcctRegAgent(idDataGroup );
      }
   }   
   return GETCURRENTHIGHESTSEVERITY ();
}

/**********************************************************************************
Input:DataGroupID,Dstring strVal
Output:None
Return:bool
Functionality:Checks for the duplicate ID's present or not
**********************************************************************************/
bool EntityIds::CheckForDuplicateID(const DString &idType ,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("CheckForDuplicateNID") );
   EntityIdsList *pEntityIdsList = NULL;
   bool bDuplicate = false;
   pEntityIdsList = dynamic_cast<EntityIdsList*>(getParent());
   if ( pEntityIdsList)
   {
      int numIdTypeRecord;
      bool bIsIdTypeExist;
      numIdTypeRecord = pEntityIdsList->getNumIdTypeRecord(idType, idDataGroup);
      bIsIdTypeExist  = pEntityIdsList->isIdTypeExist(idType, idDataGroup);
      if ( bIsIdTypeExist && numIdTypeRecord > 1 )
         bDuplicate = true;  
   }
   return bDuplicate;
}

//******************************************************************************
void EntityIds::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   DString defaultIdType;
   
   if (_market == MARKET_IDS::CANADA)
   {
      defaultIdType = IDS::SIN;
   }
   else if (_market == MARKET_IDS::JAPAN)
   {
      defaultIdType = IDS::NATIONAL_ID;
   }
   else if (_market == MARKET_IDS::LUXEMBOURG)
   {
      //defaultIdType = IDS::NATIONAL_ID;	// Explicit; LUX is defined.
      defaultIdType = NULL_STRING;
   }
   else
   {
      defaultIdType = IDS::DRIVERS_LICENSE;  // Default
   }
   setFieldNoValidate ( ifds::IdType, defaultIdType, idDataGroup, 
                        false, true, true);
   setAllFieldsReadOnly (idDataGroup);

   //MT535/MT536
   DString dstrIdType;
   getField (ifds::IdType, dstrIdType, idDataGroup, false);
   if (dstrIdType == IDS::CLEARING_PLATFORM)
   {  // MT53X
      initializeClearingPlatformIDList(idDataGroup);

      if( isNew() )
      {
         setFieldNoValidate( ifds::IdValue, NULL_STRING, idDataGroup, false );
      }
      // MT53X - End
   }

   if( dstrIdType == IDS::BIRTH_CERTIFICATE || dstrIdType == IDS::PASSPORT ||
       dstrIdType == IDS::DRIVERS_LICENSE   || dstrIdType == IDS::NATIONAL_ID ||
       dstrIdType == IDS::TRUST_ACCOUNT_NUMBER || dstrIdType == IDS::BIC_CODE ||
       dstrIdType == IDS::EMPLOYER_NUMBER   || dstrIdType == IDS::TAX_ID_NUMBER || 
       dstrIdType == IDS::SOCIAL_SECURITY_NUMBER || dstrIdType == IDS::AEOI)
   {
      setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, false);
   }
   else if (dstrIdType == IDS::FATCA_GIIN)
   {
      setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, false);
      initStatusForGIIN (idDataGroup);
      setFieldNoValidate ( ifds::IdStatus, ID_STATUS::UNVERIFIED, idDataGroup, false);
   }
   else
   {
      setFieldReadOnly (ifds::IdValue, idDataGroup, false);
      setFieldSubstituteValues (ifds::IdValue, idDataGroup, ifds::NullFieldId);
      setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, true);
   }
   initalizeXrEnvRefIDTypes(idDataGroup);
   
   if (dstrIdType == IDS::SIN)
   {
	   initSinIdDateForTFSATaxType (idDataGroup);
   }

   initVerifyStatus (idDataGroup, false);
   _bInit = false;

}

//**************************************************************************************
SEVERITY EntityIds::checkForDuplicateSIN (const DString &sinValue, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkForDuplicateSIN"));

   DString _sinValue(sinValue);
   
   _sinValue.stripLeading ('0'); //check if SIN # is 000000000 or empty before calling vew# 3
   if (!EntityIds::isSINExcepted (getWorkSession(), sinValue, idDataGroup) || !_sinValue.empty())
   {
      BFData requestData (ifds::DSTC0003_REQ),
         responseData (ifds::DSTC0003_VW);
      DString mgmtCoIdOut, 
         strCopyOfSIN (sinValue);

      requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      if(Entity::bUsedByEntityAlone)
      {
        requestData.setElementValue( ifds::NextOrPrevious, N );
        requestData.setElementValue( ifds::AllAccounts, N );
        requestData.setElementValue( ifds::AllEntitys, Y );
      }
      else
      {
         requestData.setElementValue (ifds::AllAccounts, Y);
      }
      requestData.setElementValue (ifds::SortBy, I_("LN"));
      strCopyOfSIN.stripAll ('-');
      requestData.setElementValue (ifds::SrchSIN, strCopyOfSIN);
      if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::SEARCH, 
            requestData, responseData, DSTCRequestor (getSecurity (), true)) <= WARNING)
      {
         int cRepeats = responseData.getRepeatCount ();
         for (int i = 0; i < cRepeats; i++)
         {
            DString entityId, 
               searchEntityId;
            const BFData &data = responseData.getRepeat (i);

            getField (ifds::EntityId, entityId, idDataGroup, false);
            searchEntityId = data.getElementValue (ifds::EntityId);
            if (entityId.strip () != searchEntityId.strip ())
            {               
               // SIN already exists in the system. 
               getErrMsg ( IFASTERR::DUPLICATE_SIN, 
                           CND::ERR_DUPLICATE_SIN, 
                           CND::WARN_DUPLICATE_SIN, 
                           idDataGroup); 
               break;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************
SEVERITY EntityIds::checkForDuplicateBICCode (const DString &bicCodeValue,const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkForDuplicateBICCode"));

   DString dstrWhereUse, dstrRelationShip, mgmtCoIdOut, dstrEntityId;

   Entity* pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
   if(pEntity != NULL && pEntity->isNetworkSenderEntity(idDataGroup) )
   {
      dstrWhereUse = I_( "03" ); //CLIENT
      dstrRelationShip = I_( "06" ); // NETWORK_SENDER
   }
   pEntity->getField(ifds::EntityId, dstrEntityId, idDataGroup);

   EntitySearchIDValidation entitySearchIDValidation(*this);

   DString dstrIsValid;
   //call view 417

   if( entitySearchIDValidation.init( dstrWhereUse,
                                      dstrRelationShip, 
                                      IDS::BIC_CODE, 
                                      bicCodeValue, 
                                      dstrEntityId ) <= WARNING )
   {
      entitySearchIDValidation.getField(ifds::IsValid,dstrIsValid,BF::HOST,false);
      dstrIsValid.strip().upperCase();
   }

   if( dstrIsValid == I_("N") )
   {
      ADDCONDITIONFROMFILEIDI (CND::ERR_DUPLICATE_BICCODE, I_(""));
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************
SEVERITY EntityIds::checkForDuplicateNEQ (const DString &neqValue,const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkForDuplicateNEQ"));

   BFData  requestData (ifds::DSTC0003_REQ), responseData (ifds::DSTC0003_VW);
   DString mgmtCoIdOut;
   Entity   *pEntity = NULL;

   // get original Entity.
   pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

   if (pEntity && !pEntity->isNEQEntity (idDataGroup))
   {
      return GETCURRENTHIGHESTSEVERITY ();
   }

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::NextOrPrevious, N);
   requestData.setElementValue (ifds::AllAccounts, N);
   requestData.setElementValue (ifds::AllEntitys, Y);
   requestData.setElementValue (ifds::SortBy, I_("LN"));
   requestData.setElementValue (ifds::SrchIdType, IDS::NEQ);
   requestData.setElementValue (ifds::SrchIdValue, neqValue);

   if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::SEARCH, requestData, responseData, 
      DSTCRequestor (getSecurity (), true)) <= WARNING)
   {
      int      cRepeats = responseData.getRepeatCount ();
      bool     bNEQEntity = false;

      for (int i = 0; i < cRepeats; i++)
      {
         DString	searchEntityId;
         Entity	*srchEntity = NULL;
         bool    bSrchNEQEntity = false;
         const	BFData &data = responseData.getRepeat (i);

         searchEntityId = data.getElementValue (ifds::EntityId);

         // check back-end entity
         bSrchNEQEntity = isNEQEntity (idDataGroup, searchEntityId);

         if (bSrchNEQEntity && data.getElementValue (ifds::GoodBad)==I_("Y"))
         {
            getErrMsg (IFASTERR::DUPLICATE_NEQ, 
                       CND::ERR_DUPLICATE_NEQ, 
                       CND::WARN_DUPLICATE_NEQ, 
                       idDataGroup);
            break;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************
SEVERITY EntityIds::doApplyRelatedChanges (const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doApplyRelatedChanges"));
   if (_market == MARKET_IDS::CANADA && 
      (idField == ifds::IdValue || idField == ifds::IdType))
   {
      DString dstrIdType;
      getField(ifds::IdType, dstrIdType, idDataGroup);

      if(idField == ifds::IdType || dstrIdType == IDS::SIN)
      {
         EntityIdsList *pEntityIdsList = NULL;

         pEntityIdsList = dynamic_cast<EntityIdsList*>(getParent());
         if(pEntityIdsList != NULL)
            pEntityIdsList->updateParentEntitySIN(idDataGroup);
      }
   }

   if (idField == ifds::IdValue)
   {  
/*    setting the status on SIN is done by a database trigger...
      kept the commented code just in case... and as a sample.

      DString idType,
         status (I_("01")); //valid

      getField (ifds::IdType, idType, idDataGroup, false);      
      if (idType.stripAll () == IDS::SIN)
      {
         CONDITIONVECTOR *pConditionVector = NULL;
            
         getFieldConditionVector (ifds::XrefNum, idDataGroup, pConditionVector);

         if (pConditionVector)
         {
            CONDITIONVECTOR::iterator iter = pConditionVector->begin();
            while (iter != pConditionVector->end())
            {
               int condCode = (**iter).getCode();
               if ( condCode == CND::ERR_W_INVALID_SIN ||
                    condCode == CND::ERR_ACCTOWNER_SIN_INVALID ||
                    condCode == CND::ERR_SPOUSE_SIN_INVALID)
               {
                  status = I_("02");// invalid
                  break;
               }
               ++iter;
            }
         }
      }
      setFieldNoValidate (ifds::IdStatus, status, idDataGroup, false, true);
*/
   }
   else if (idField == ifds::DuplicateSINcheck)
   {
      DString strDuplicateSIN;
      getField (ifds::DuplicateSINcheck, strDuplicateSIN, idDataGroup);
      if (strDuplicateSIN == Y)
      {
         DString dstrTemp;

         getField (ifds::IdType, dstrTemp, idDataGroup, false);
         if (_market == MARKET_IDS::CANADA && dstrTemp == IDS::SIN)
         {
            // This will trigger SIN check for both new entities and 
            // existing ones (when SIN has been changed)
            DString dstrExistingSIN, 
               dstrNewSIN;

            getFieldBeforeImage( ifds::IdValue, dstrExistingSIN );
            getField( ifds::IdValue, dstrNewSIN, idDataGroup );
            if (dstrExistingSIN.strip() != dstrNewSIN.strip())
               setValidFlag (ifds::IdValue, idDataGroup, false);
         }
      }
   }
   else if (idField == ifds::IdStatus)
   {
//for access ids and when user changes the status to override or reset - enable the id value
      DString idType;

      getField (ifds::IdType, idType, idDataGroup);
      if (idType == IDS::ACCESS_ID)
      {
         DString idStatus;
         getField (ifds::IdStatus, idStatus, idDataGroup, false);

         setFieldReadOnly (ifds::IdValue, 
                           idDataGroup, 
                           idStatus != ID_STATUS::OVERRIDE && idStatus != ID_STATUS::RESET);
      }
   }

   //MT535/MT536
   else if (idField == ifds::IdType)
   {
      /*
        IdType changed, IdValue should be invalid,
        To force validate the field when user switch IdType.
        Don't want to clear IdValue for some case that 
        user just want to change entitytype but want to leave the old value.
        In case of user enters the correct Id value but select the wrong entitytype.
        After that user switches entitytype.
      */
      setFieldValid(ifds::IdValue, idDataGroup, false);
      DString idType;

      getField (ifds::IdType, idType, idDataGroup);
      if (idType == IDS::CLEARING_PLATFORM)
      {  // MT53X     
         initializeClearingPlatformIDList(idDataGroup);

         if( isNew() )
         {
            setFieldNoValidate( ifds::IdValue, NULL_STRING, idDataGroup, false, false, true, true);
         }
         // MT53X - End
      }
      else
      {
         setFieldSubstituteValues (ifds::IdValue, idDataGroup, ifds::NullFieldId);
      }

      DString entityType;
      getField (ifds::EntityType, entityType, idDataGroup);

      if (idType == IDS::BIC_CODE )
      {
         if( isNew() )
         {
            //if entityType unknown, only set the Status to 'valid' for new BIC codes (leave it unchanged for existing BIC Codes)
            setFieldNoValidate(ifds::IdStatus, I_("01"), idDataGroup, false, true, true );
         }
         if( entityType == I_("58") )
         {
            setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::ValidInvalidIdStatus);	
            //for 58, set the Status to 'valid' regardless if it's a new record or existing
            setFieldNoValidate(ifds::IdStatus, I_("01"), idDataGroup, false, true, true );
         }
         else
         {
            setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::IdStatus);
         }
      }

      if(idType == IDS::BIRTH_CERTIFICATE    || idType == IDS::PASSPORT ||
         idType == IDS::DRIVERS_LICENSE      || idType == IDS::NATIONAL_ID ||
         idType == IDS::TRUST_ACCOUNT_NUMBER || idType == IDS::BIC_CODE ||
         idType == IDS::EMPLOYER_NUMBER      || idType == IDS::TAX_ID_NUMBER ||
         idType == IDS::SOCIAL_SECURITY_NUMBER || idType == IDS::AEOI)
      {
         setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, false);
      }
      else if (idType == IDS::FATCA_GIIN)
      {
         setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, false);
         initStatusForGIIN (idDataGroup);
         setFieldNoValidate ( ifds::IdStatus, ID_STATUS::UNVERIFIED, idDataGroup, false);
      }
      else
      {
         setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::IdStatus);
         setFieldNoValidate(ifds::CountryOfIssue, NULL_STRING, idDataGroup, false, true, true );
         setFieldReadOnly (ifds::CountryOfIssue, idDataGroup, true);    
      }
	  
	  if (idType == IDS::SIN)
	  {
		  initSinIdDateForTFSATaxType (idDataGroup);
	  }

	  initVerifyStatus (idDataGroup, isNew());
	  _bInit = false;
   }
   if( idField == ifds::IdStatus      ||
	   idField == ifds::IdExpireDate  ||
	   idField == ifds::IdDate  ||
	   idField == ifds::CountryOfIssue ||
	   idField == ifds::IdValue
	)
   {
	   verifyStatusRelatedChanges (idField, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************
SEVERITY EntityIds::doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

	//QESI3FN03
   DString dstrIdType;
   
   getField (ifds::IdType, dstrIdType, idDataGroup);
   dstrIdType.strip();  

   if (dstrIdType != IDS::SIN)
   {
      nonSINRelatedChanges (idDataGroup);
   }

   if(!isNew())
   {
	   DString  dstrSearchKey,dstrAccountNum,dstrEntityType,dstrEntityId; 
	   AccountEntityXref *pAEXref = NULL;
	   if (getWorkSession().getAccountEntityXref (idDataGroup, pAEXref) <= WARNING &&
		   pAEXref)
	   {
		   BFObjIter iter (*pAEXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);  
		   AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);  
		   Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
		   if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey) && pEntity)
		   {
			   iter.positionByKey (dstrSearchKey);  
			   iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
			   iter.getObject()->getField (ifds::EntityType, dstrEntityType, idDataGroup);
			   dstrAccountNum.strip().upperCase();
			   MFAccount *pMFAccount = NULL;
			   if( !isNew()&& isUpdatedForDataGroup (idDataGroup)&&
				   getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING 
				   && pMFAccount && dstrEntityType == I_("01") )	//ACCOUNTHOLDER_ENTITY_TYPE 
			   {	
				   bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
				   pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup,bDisplyWarnSICAV,bDisplyWarnOEIC);
				   if(bDisplyWarnSICAV)
					   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
				   if(bDisplyWarnOEIC)
					   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
			   } 
		   }
	   }
   }
	
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************
SEVERITY EntityIds::validIdType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validIdType"));

   DString dstrIdType,dstrRoutingType; 

   getParent()->getField (ifds::RoutingType, dstrRoutingType, idDataGroup, false);
   getField (ifds::IdType, dstrIdType, idDataGroup);
   
   //do not validate here, move the validation to final check

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::setSINToParentEntity (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setSINToParentEntity"));

   DString idType;

   getField (ifds::IdType, idType, idDataGroup, false);
   if (idType.stripAll () == IDS::SIN)
   {
      DString entityId;
      Entity *pEntity = NULL;

      getField (ifds::EntityId, entityId, idDataGroup, false);
      if (getWorkSession ().getEntity (idDataGroup, entityId, pEntity) && 
          pEntity)
      {
         DString dstrIdValue;

         getField (ifds::IdValue, dstrIdValue, idDataGroup, false);
         pEntity->setField (ifds::SIN, dstrIdValue, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::nonSINRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("nonSINRelatedChanges"));

   DString idType, idValue,
      entityId;

   getField (ifds::IdType, idType, idDataGroup, false);
   getField (ifds::IdValue, idValue, idDataGroup, false);
   getField (ifds::EntityId, entityId, idDataGroup, false);
   if (!idType.empty () && idType != IDS::ACCESS_ID && idType != IDS::AUSTRALIAN_BUSINESS_NUMBER && idValue.empty ())
   {
      DString idiString;

      getField (ifds::IdType, idType, idDataGroup, true);
      addIDITagValue (idiString, ID_VALUE, idType);
      addIDITagValue (idiString, ENTITY_ID, entityId);
      ADDCONDITIONFROMFILEIDI (CND::ERR_NO_VALUE_FOR_ID, idiString);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
void EntityIds::setAllFieldsReadOnly (const BFDataGroupId& idDataGroup)
{
   bool bReadOnly = false;
   DString idAllowOverride,
      idType;

   getField (ifds::IdAllowOverride, idAllowOverride, idDataGroup, false);
   getField (ifds::IdType, idType, idDataGroup, false);
   if (Entity::bUsedByEntityAlone)
   {
      bReadOnly = dynamic_cast<Entity* >( getParent()->getParent() )->isAccountRelated( idDataGroup );
   }
   else  //for AIM
   {
      bReadOnly = idType == IDS::CIF || idType == IDS::ACCESS_ID;
   }
   setFieldReadOnly (ifds::IdType, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::IdValue, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::IdDate, idDataGroup, bReadOnly);
//for all ids (but access id) this is not updatable - check doApplyRelatedChanges for more rules..
//as of AIM project...
   setFieldReadOnly (ifds::IdStatus, idDataGroup, idType != IDS::ACCESS_ID && idAllowOverride == N);
   
   if (idType == IDS::BIC_CODE) //MT535/536
   {
      DString entityType;

      getField (ifds::EntityType, entityType, idDataGroup);

      if (entityType == I_("58")) //clearing platform entity
      {
         setFieldReadOnly (ifds::IdStatus, idDataGroup, false);
         setFieldReadOnly (ifds::IdDate, idDataGroup, false);
      }
   }
}

//********************************************************************************
SEVERITY EntityIds::setEntityType (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setEntityType"));

   DString entityType,
      entityId;

   getField (ifds::EntityType, entityType, idDataGroup);
   getField (ifds::EntityId, entityId, idDataGroup);

   AccountEntityXref *pAEXref = NULL;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAEXref) <= WARNING &&
      pAEXref)
   {
      BFObjIter iter (*pAEXref, idDataGroup, true, 
         BFObjIter::ITERTYPE::NON_DELETED);

      DString searchKey;
      AccountEntityXref::buildPartialKeyForEntityId (searchKey, entityId);
      if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
      {
         iter.positionByKey (searchKey);
         if (!iter.end())
         {
            DString entityType;

            iter.getObject()->getField (ifds::EntityType, entityType, 
               idDataGroup, false);
            setFieldNoValidate (ifds::EntityType, entityType, idDataGroup, false, true);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY EntityIds::setBICCodeProperties (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setBICCodeProperties"));

   DString idType;

   getField (ifds::IdType, idType, idDataGroup, false);

   if (idType == IDS::BIC_CODE) //MT535/536
   {
      setFieldSubstituteValues (ifds::IdStatus, idDataGroup, ifds::ValidInvalidIdStatus);
      setFieldReadOnly (ifds::IdStatus, idDataGroup, false);
      setFieldReadOnly (ifds::IdDate, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
bool EntityIds::isNetworkSenderEntity (const BFDataGroupId &idDataGroup, 
                                       const DString& strEntityNum)
{
   bool bNetworkSender = false;

   Entity *pEntity = new Entity (*this); 
   pEntity->init (strEntityNum);

   WhereUsedList* pList = NULL;

   if (pEntity->getWhereUsedList (pList, idDataGroup, true, true) <= WARNING )
   {
      if( pList )
      {
         bNetworkSender = pList->isNetworkSender (idDataGroup);
      }
   }
   delete pEntity;

   return bNetworkSender;
}

//********************************************************************************
bool EntityIds::isNEQEntity (const BFDataGroupId &idDataGroup, 
                             const DString& strEntityNum)
{
   bool bNEQEntity = false;

   Entity *pEntity = new Entity (*this); 
   pEntity->init (strEntityNum);

   WhereUsedList* pList = NULL;

   if (pEntity->getWhereUsedList (pList, idDataGroup, true, true) <= WARNING )
   {
      if( pList )
      {
         bNEQEntity = pList->isNEQEntity (idDataGroup);
      }
   }
   delete pEntity;

   return bNEQEntity;
}

//******************************************************************************
SEVERITY EntityIds::validateIDValueForIDTypeOnSystem( const DString &IDType, 
                                                      const DString &IDValue, 
                                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_ ("validateIDValueForIDTypeOnSystem"));

   EntitySearchList* pEntitySearchList = new EntitySearchList ( getWorkSession());

   pEntitySearchList->init( I_("IDTYPE"), // searchBy
                            NULL_STRING,  // first name
                            NULL_STRING,  // last name
                            NULL_STRING,  // SIN
                            IDType,
                            IDValue,
                            NULL_STRING ); // whereUse

   if ( GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      DString strEntityID1;
      Entity *pEntity1 = dynamic_cast<Entity* >( getParent()->getParent() );
      Entity *pEntity2 = NULL;
      pEntity1->getField( ifds::EntityId, strEntityID1,idDataGroup, false );

      bool bFoundExisting = false;
      BFObjIter iter( *pEntitySearchList, 
                       idDataGroup, 
                       true, 
                       BFObjIter::ITERTYPE::NON_DELETED );
      while (!iter.end())
      {
         DString strEntityID2, strEntityType2,strIDType;
         iter.getObject()->getField( ifds::EntityId, strEntityID2, idDataGroup );
         iter.getObject()->getField( ifds::EntityType, strEntityType2, idDataGroup );

         EntityIdsList* pEntityIdsList = NULL;
         getWorkSession ().getEntity (idDataGroup, strEntityID2, pEntity2);
         pEntityIdsList = new EntityIdsList(*pEntity2);
         pEntityIdsList->init(strEntityID2,strEntityType2);

         if ( GETCURRENTHIGHESTSEVERITY() <= WARNING && pEntityIdsList )
         {
            BFObjIter iterIds( *pEntityIdsList, 
                                 idDataGroup, 
                                 false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
            while (!iterIds.end())
            {
               DString strIDType, strIDValue;
               iterIds.getObject()->getField( ifds::IdType, strIDType, idDataGroup );
               iterIds.getObject()->getField( ifds::IdValue, strIDValue, idDataGroup );

               if ( strIDType == IDType && strIDValue == IDValue )
               {
                  bFoundExisting = true;
                  break;
               }
               ++iterIds;
            }
         }
         delete pEntityIdsList;
         pEntityIdsList = NULL;

         if ( bFoundExisting )
         {
            break;
         }
         ++iter;
      }

      if ( bFoundExisting )
      {
         ADDCONDITIONFROMFILE (CND::ERR_ENTERED_ID_NOT_UNIQUE);
      }
   }
   else
   {
      int count = CONDITIONCOUNT();
      Condition *c = NULL;
      for (int i = 0; i < count; i++)
      {
         c = GETCONDITION (i);
         int condCode = c->getCode();
         if (condCode == CND::ERR_DATA_NOT_FOUND ||
             condCode == CND::ERR_ENTITY_NOT_FOUND)
         {
            CLEARCONDITION(i);
            break;
         }
      }
   }

   delete pEntitySearchList;
   pEntitySearchList = NULL;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityIds::validateIDTypeValueEntity( DSTCWorkSession &rpDSTCWorkSession, 
                                               const DString &entityType,
                                               const DString &entityID,
                                               const DString &taxType,
                                               const DString &idType,
                                               const DString &idValue,
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateIDTypeValueEntity"));

   DString description (
      getEntityTypeDescription (rpDSTCWorkSession, 
         entityType, idDataGroup)),
         strErrValue (NULL_STRING);

   bool bCheckedErrMsgList = false, 
        bIsIDTypeRequired = isIDTypeRequired ( rpDSTCWorkSession, 
                                               taxType, 
                                               entityType,
                                               idType,
                                               idDataGroup, 
                                               strErrValue );

   EntityIds::validateIDType (rpDSTCWorkSession, 
                              idType,
                              idValue, 
                              idDataGroup, 
                              bIsIDTypeRequired, 
                              strErrValue == I_("I"));

   int count = CONDITIONCOUNT();
   Condition *c = NULL;

   for (int i = 0; i < count; i++)
   {
      c = GETCONDITION (i);
      int condCode = c->getCode();

      CLEARCONDITION (i);

      if (condCode == CND::ERR_E_ID_VALUE_IS_MISSING &&
          entityType == RESP_PCG_INST )
      {
         ADDCONDITIONFROMFILE (CND::ERR_PCG_INST_BUSINESS_NUMBER_MISSING);
      }
      else if (condCode == CND::ERR_W_ID_VALUE_IS_MISSING &&
               entityType == RESP_PCG_INST )
      {
         ADDCONDITIONFROMFILE (CND::WARN_PCG_INST_BUSINESS_NUMBER_MISSING);
      }
      else if (condCode == CND::ERR_E_INVALID_ID_VALUE &&
               entityType == RESP_PCG_INST )
      {
         ADDCONDITIONFROMFILE (CND::ERR_PCG_INST_BUSINESS_NUMBER_INVALID);
      }
      else if(condCode == CND::ERR_W_INVALID_ID_VALUE &&
              entityType == RESP_PCG_INST )
      {
         ADDCONDITIONFROMFILE (CND::WARN_PCG_INST_BUSINESS_NUMBER_INVALID);
      }
	  else if (condCode == CND::ERR_E_ID_VALUE_IS_MISSING && //IN3198343
          entityType == ACCOUNT_OWNER )
      {
         ADDCONDITIONFROMFILE (CND::ERR_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER);
      }
      else if (condCode == CND::ERR_W_ID_VALUE_IS_MISSING &&
               entityType == ACCOUNT_OWNER )
      {
         ADDCONDITIONFROMFILE (CND::WARN_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER);
      }
	  else if (condCode == CND::ERR_E_INVALID_ID_VALUE &&
               entityType == ACCOUNT_OWNER )
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER);
      }
      else if(condCode == CND::ERR_W_INVALID_ID_VALUE &&
              entityType == ACCOUNT_OWNER )
      {
         ADDCONDITIONFROMFILE (CND::WARN_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool EntityIds::isIDTypeRequired( DSTCWorkSession &rpDSTCWorkSession, 
                                  const DString &taxType,
                                  const DString &entityType,
                                  const DString &idType,
                                  const BFDataGroupId &idDataGroup,
                                  DString &strErrValue /*=I_("W")*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSINRequired"));

   bool bIDRequired = false;

   if( ( taxType == INDIVIDUAL_RESP_TAX_TYPE || taxType == FAMILY_RESP_TAX_TYPE) &&
       ( entityType == RESP_PCG_INST && idType == IDS::BUSINESS_NUMBER ) )
   {
      bIDRequired = true;
   }
   else if(taxType == INDIVIDUAL_RESP_TAX_TYPE && entityType == ACCOUNT_OWNER && 
	       idType == IDS::BUSINESS_NUMBER)
   {
	   bIDRequired = true;
   }
   else if( taxType == RDSP_TAX_TYPE && (entityType == ACCOUNT_OWNER || entityType == RDSP_PCG) )
   {
	   bIDRequired = true;
   }

   return bIDRequired;
}

//******************************************************************************
SEVERITY EntityIds::validatePCGAgainstSystem(const DString &strObjIDValue,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validatePCGAgainstSystem"));

	validateIDValueForIDTypeOnSystem(IDS::BUSINESS_NUMBER, strObjIDValue, idDataGroup);

	auto count = CONDITIONCOUNT();
	for(int i = 0; i<count; i++)
	{
		auto c = GETCONDITION(i);
		if(c->getCode() == CND::ERR_ENTERED_ID_NOT_UNIQUE)
		{
			CLEARCONDITION(i);

			getErrMsg(IFASTERR::DUPLICATE_BUSINESS_NUMBER,
				CND::ERR_DUPLICATE_BUSINESS_NUMBER,
				CND::WARN_DUPLICATE_BUSINESS_NUMBER,
				idDataGroup);

			break;
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//MT53X
void EntityIds::initializeClearingPlatformIDList(const BFDataGroupId& idDataGroup, bool bReadOnly )
{
   DString dstrSubstitutionList;

   initializeSubstitutionList (ifds::ClearingPlatformID, GROUPCODE_CLEARING_PLATFORM_ID, idDataGroup);

   BFProperties *pBFProperties = getFieldProperties( ifds::ClearingPlatformID, idDataGroup );
   pBFProperties->getAllSubstituteValues( dstrSubstitutionList );

   setFieldAllSubstituteValues (ifds::IdValue, idDataGroup, dstrSubstitutionList);
   
   BFProperties *pBFIdValueProperties = getFieldProperties( ifds::IdValue, idDataGroup );
   pBFIdValueProperties->setSubstituteValues(NULL);

   setFieldReadOnly( ifds::IdValue, idDataGroup, bReadOnly );

}

//******************************************************************************
SEVERITY EntityIds::validateSINDuplicateForRESP(const DString &sin, 
                                                const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateSINDuplicateForRESP"));

   // if sin is blank there should be error like SIN missing,
   // it shouldn't populate the error like SIN is same as some entity
   if ( sin.empty() )
      return GETCURRENTHIGHESTSEVERITY();

   AccountEntityXref *pAcctEXref = NULL;
   DString dstrEntityType;
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAcctEXref) <= WARNING &&
       pAcctEXref)
   {
      BFObjIter iter (*pAcctEXref, idDataGroup, true, 
                       BFObjIter::ITERTYPE::NON_DELETED);

      DString dstrSearchKey, dstrEntityId;
      getField( ifds::EntityId, dstrEntityId,idDataGroup, false );

      AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);

      if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey))
      {
         iter.positionByKey (dstrSearchKey);
         // check taxtype first
         DString dstrAccountNum;
         MFAccount* pMFAccount;
         iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
              pMFAccount )
         {
            DString taxType;
            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
            taxType.strip().upperCase();
            if(taxType != FAMILY_RESP_TAX_TYPE)
               return GETCURRENTHIGHESTSEVERITY(); 
         }
         if (!iter.end())
         {
            // prepare to loop check
            AccountEntityXrefObject* pObj = dynamic_cast<AccountEntityXrefObject*>(iter.getObject());
            // get EntityType
            pObj->getField( ifds::EntityType, dstrEntityType,idDataGroup, false );

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
                                 if ( sin == strOppSIN )
                                 {
                                    DString strEntityTypeFmt, strOppEntityTypeFmt;
                                    pObj->getField (ifds::EntityType, strEntityTypeFmt, idDataGroup, true);
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
                  } // end if entitytype
                
                  ++oppositeIter;
               } // end while

            }

         }
      }

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//MT53X
void EntityIds::initializeSubstitutionList( const BFFieldId& idField, 
                                            const DString &dstrGroupCode, 
                                            const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrSubstitutionList;

   getMgmtCo().getTranslationTable (dstrGroupCode, pTranslationTable);

   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList(dstrSubstitutionList, true);	 
      setFieldAllSubstituteValues (idField, idDataGroup, dstrSubstitutionList);
   }
}

//******************************************************************************
//QESI3FN03
void EntityIds::doInitIdDate (const DString& dstrEntityType, const DString& dstrIDType, const DString& dstrValue, const BFDataGroupId &idDataGroup)
{
   if(dstrEntityType == RESP_BENEFICIARY)
   {
      if (dstrIDType == IDS::SIN)
      {
         if(isNew())
         {
            //QESIFN03: default SIN IdDate with DOfB 
            setFieldNoValidate( ifds::IdDate, dstrValue, idDataGroup, false, false, true );
         }
      }
   }
}

//***************************************************************************************
//QESI3FN03
SEVERITY EntityIds::getEWIMsgforRESPBenfSINUpdate(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEWIMsgforRESPBenfSINUpdate" ) );

   AccountEntityXref *pAcctEXref = NULL;
   DString dstrEntityType;

   getField( ifds::EntityType, dstrEntityType, idDataGroup, false );

   if(dstrEntityType == RESP_BENEFICIARY)
   {
      if (getWorkSession().getAccountEntityXref (idDataGroup, pAcctEXref) <= WARNING &&
         pAcctEXref)
      {
         BFObjIter iter (*pAcctEXref, idDataGroup, true, 
            BFObjIter::ITERTYPE::NON_DELETED);

         DString dstrSearchKey, dstrEntityId;
         getField( ifds::EntityId, dstrEntityId,idDataGroup, false );

         AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);

         if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey))
         {
            iter.positionByKey (dstrSearchKey);

            DString dstrAccountNum,
               dstrTransID = NULL_STRING, 
               dstrNewTaxJuris = NULL_STRING, 
               dstrNewSibling = I_("N"), 
               dstrValidateType = I_("SIN"), 
               dstrBenefIdList = dstrEntityId;

            iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

            MFAccount *pMFAccount = NULL;
            if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING )
            {   

                //call for VEW415 to issue EW msg
                RESPInfoUpdateValidationList *pRESPInfoUpdateValidationList = NULL;
               
                if( !pMFAccount->isNew() && pMFAccount->getRESPInfoUpdateValidationList( pRESPInfoUpdateValidationList,
                                                                 dstrTransID, /*TransId*/
                                                                 dstrNewTaxJuris, /*NewTaxJuris*/
                                                                 dstrNewSibling, /*NewSibling*/
                                                                 dstrValidateType, /*ValidationType*/
                                                                 dstrBenefIdList, /*BenefIdList*/
                                                                 idDataGroup ) <= WARNING )    
                {

                   pRESPInfoUpdateValidationList->displayAllRESPError(idDataGroup);

                }
                //delete pRESPInfoUpdateValidationList;
                pRESPInfoUpdateValidationList = NULL;

            }
                  
            //delete pMFAccount;
            pMFAccount = NULL;
         }  
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::isTrustNumberValid (DSTCWorkSession &rpDSTCWorkSession,
                                        const DString& strTrustNum,
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isTrustNumberValid" ) );

   bool bNumberInvalid = true;

   DString strCopyTrustNum(strTrustNum);
   Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

   strCopyTrustNum.upperCase();

   if(strCopyTrustNum.left(1) == I_("T"))
   {
      strCopyTrustNum = strCopyTrustNum.right(strCopyTrustNum.length()-1);
      if(strCopyTrustNum.isAllDigits())
      {
         if (strCopyTrustNum.length () == 8)
         {
            DString validatingTrustNum = NULL_STRING;
            validatingTrustNum = I_("3");
            validatingTrustNum += strCopyTrustNum;

            int condCode = 0;
            
            int even1, even2, even3, even4,
               odd1, odd2, odd3, odd4;
            DString strEven, 
               strOdd;

            strEven = validatingTrustNum.substr (1, 1);
            even1   = strEven.asInteger () * 2;
            strEven = validatingTrustNum.substr (3, 1);
            even2   = strEven.asInteger () * 2;
            strEven = validatingTrustNum.substr (5, 1);
            even3   = strEven.asInteger () * 2;
            strEven = validatingTrustNum.substr (7, 1);
            even4   = strEven.asInteger () * 2;
            strOdd = validatingTrustNum.substr (0, 1);
            odd1   = strOdd.asInteger ();
            strOdd = validatingTrustNum.substr (2, 1);
            odd2   = strOdd.asInteger ();
            strOdd = validatingTrustNum.substr (4, 1);
            odd3   = strOdd.asInteger ();
            strOdd = validatingTrustNum.substr (6, 1);
            odd4   = strOdd.asInteger ();
            if (even1 > 9)
            {
               even1 = even1 - 9;
            }
            if (even2 > 9)
            {
               even2 = even2 - 9;
            }
            if (even3 > 9)
            {
               even3 = even3 - 9;
            }
            if (even4 > 9)
            {
               even4 = even4 - 9;
            }
            even1 = even1 + even2 + even3 + even4;
            odd1  = odd1  + odd2  + odd3  + odd4;
            even1 = even1 + odd1;
            even1 = even1 % 10;
            if (even1 == 0)
            {
               even1 = 0;
            }
            else
            {
               even1 = 10 - even1;
            }

            int iValidatingTrustNum = validatingTrustNum.asInteger ();
            iValidatingTrustNum %= 10;

            if (even1 != iValidatingTrustNum)
            {
               if (!EntityIds::isSINExcepted (rpDSTCWorkSession, validatingTrustNum, idDataGroup))
               {
                  bNumberInvalid = true;
               }
               else
               {
                  bNumberInvalid = false;
               }
            }
            else
            {
               bNumberInvalid = false;
            }
         }
         else
         {
            bNumberInvalid = true;
         }
      }
      else
      {
         bNumberInvalid = true;
      }
   }
   else
   {
      bNumberInvalid = true;
   }

   if(bNumberInvalid)
   {
      getErrMsg (IFASTERR::TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID, 
                 CND::ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID, 
                 CND::WARN_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID, 
                 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY EntityIds::isTrustNumberValid (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isTrustNumberValid" ));
   
   DString strIDType, strIDValue;
   
   getField (ifds::IdType, strIDType, idDataGroup, false);
   getField (ifds::IdValue, strIDValue, idDataGroup, false);
   strIDType.strip().upperCase();
   strIDValue.strip().upperCase();
   
   if (strIDType == IDS::TRUST_ACCOUNT_NUMBER)
   {
      isTrustNumberValid(getWorkSession (),strIDValue,idDataGroup);
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY EntityIds::validateAcctRegAgent(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctRegAgent" ) );

	AccountEntityXref *pAcctEXref = NULL;

	DString dstrEntityType, dstrAccountNum, dstrTaxType;
	if (getWorkSession().getAccountEntityXref (idDataGroup, pAcctEXref) <= WARNING &&
		pAcctEXref)
	{
		BFObjIter iter (*pAcctEXref, idDataGroup, true, 
			BFObjIter::ITERTYPE::NON_DELETED);

		DString dstrSearchKey, dstrEntityId;
		getField( ifds::EntityId, dstrEntityId,idDataGroup, false );

		AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);

		if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey))
		{
			iter.positionByKey (dstrSearchKey);
			// check taxtype first
			MFAccount* pMFAccount;
			iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
			if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
				pMFAccount )
			{
				pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup, false);
				dstrTaxType.strip().upperCase();

				bool bCPFTaxType = (dstrTaxType == OA_TAX_TYPE || dstrTaxType == SA_TAX_TYPE || dstrTaxType == SRS_TAX_TYPE);
				if(!bCPFTaxType)
				{
					return GETCURRENTHIGHESTSEVERITY(); 
				}
			}
			if (!iter.end())
			{
				// prepare to loop check
				AccountEntityXrefObject* pObj = dynamic_cast<AccountEntityXrefObject*>(iter.getObject());
				// get EntityType
				pObj->getField( ifds::EntityType, dstrEntityType,idDataGroup, false );
				if( dstrEntityType == ACCOUNT_OWNER )
				{
					DString dstrCOINationalID,dstrCOIPassport,dstrIdType,dstrNationalID,dstrPassport,dstrRAEntityId;
					
					getField(ifds::IdType,dstrIdType,idDataGroup);						
					
					if( dstrIdType == IDS::NATIONAL_ID )
					{
						getField(ifds::IdValue,dstrNationalID,idDataGroup);
						getField(ifds::CountryOfIssue,dstrCOINationalID,idDataGroup);
					}
					else if( dstrIdType == IDS::PASSPORT )
					{
						getField(ifds::IdValue,dstrPassport,idDataGroup);
						getField(ifds::CountryOfIssue,dstrCOIPassport,idDataGroup);
					}
					Entity *pEntity = NULL;					
					getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
					if( pEntity )
					{
						pEntity->validateAcctRegAgent( dstrAccountNum, 
														dstrTaxType, 
														dstrRAEntityId, 
														dstrNationalID, 
														dstrCOINationalID, 
														dstrPassport, 
														dstrCOIPassport,
														idDataGroup );
					}
				
				}
		    }
		}
	}
	return GETCURRENTHIGHESTSEVERITY ();
}

//*********************************************************************************************************//
SEVERITY EntityIds::initalizeXrEnvRefIDTypes(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initalizeXrEnvRefIDTypes" ) );

	ErrMsgRulesList *pErrMsgRulesList = NULL;
	if ( getMgmtCo ().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
		pErrMsgRulesList)
	{
		DString dstrErrValueSICAV, dstrErrValueOEIC;
      pErrMsgRulesList->getEWIValue (IFASTERR::DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV, 
         idDataGroup, 
         dstrErrValueSICAV);
      pErrMsgRulesList->getEWIValue(IFASTERR::DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC, 
         idDataGroup, 
         dstrErrValueOEIC);
      dstrErrValueSICAV.strip().upperCase();
      dstrErrValueOEIC.strip().upperCase();

		BFProperties *pBFPropertiesIdTypeSet = getFieldProperties (ifds::IdType, idDataGroup);
		assert (pBFPropertiesIdTypeSet);
		if(pBFPropertiesIdTypeSet)
		{
         DString IdTypeSetSubst;
         pBFPropertiesIdTypeSet->getAllSubstituteValues (IdTypeSetSubst);
         if(dstrErrValueSICAV == I_("W"))
         { 
            IdTypeSetSubst = removeItemFromSubtList ( IdTypeSetSubst, IDS::iFAST_SICAV);
            setFieldAllSubstituteValues (ifds::IdType, idDataGroup, IdTypeSetSubst);
         }
         else if(dstrErrValueOEIC == I_("W"))
         {
            IdTypeSetSubst = removeItemFromSubtList ( IdTypeSetSubst,IDS::iFAST_OEIC);
            setFieldAllSubstituteValues (ifds::IdType, idDataGroup, IdTypeSetSubst);
         }
         else if ( dstrErrValueSICAV != I_("W")  && dstrErrValueOEIC != I_("W")  )
         {
            IdTypeSetSubst = removeItemFromSubtList ( IdTypeSetSubst,(IDS::FAST));
            IdTypeSetSubst = removeItemFromSubtList ( IdTypeSetSubst,(IDS::iFAST_SICAV));
            IdTypeSetSubst = removeItemFromSubtList ( IdTypeSetSubst,(IDS::iFAST_OEIC));
            setFieldAllSubstituteValues (ifds::IdType, idDataGroup, IdTypeSetSubst);
         }
      }		
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::validateTransmitterNumberFormat(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTransmitterNumberFormat" ) );

    DString strIDValue;

    getField(ifds::IdValue, strIDValue, idDataGroup, false);

    bool bRaisingError = false;

    if (strIDValue.size() != 10) 
    {
        bRaisingError = true;
    }
    else
    {
        // 1-MM111111
        boost::RegEx rgVal("[1-4]{1}-MM(\\d{6})");
        DStringA straVal(strIDValue);
        bRaisingError = !rgVal.Match(straVal.c_str());
    }

    if(bRaisingError)
    {
        getErrMsg(IFASTERR::TRANSMITTER_NUMBER_FORMAT_INCORRECT, 
            CND::ERR_TRANSMITTER_NUMBER_FORMAT_INCORRECT, 
            CND::WARN_TRANSMITTER_NUMBER_FORMAT_INCORRECT, 
            idDataGroup);
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::validateGIINFormat(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGIINFormat" ) );

   DString strIDValue;

   getField (ifds::IdValue, strIDValue, idDataGroup, false);
   strIDValue.strip().upperCase();

   bool bRaisingError = false;
   if(strIDValue.size() != 19) bRaisingError = true;
   else
   {
      // format must be in form XXXXXX.XXXXX.YY.999
      // where the first group is alphanumeric, secound group is alphanumeric 
      // and separator of each group must be only period character
      boost::RegEx rgVal("(\\w{6})(\\.)(\\w{5})(\\.)(\\D{2})(\\.)(\\d{3})");
      DStringA straVal(strIDValue.upperCase());
      bRaisingError = !rgVal.Match(straVal.c_str());
   }

   if(bRaisingError)
   {
      // do raising error here
      getErrMsg ( IFASTERR::INVALID_GIIN_FORMAT, 
                  CND::ERR_INVALID_GIIN_FORMAT, 
                  CND::WARN_INVALID_GIIN_FORMAT, 
                  idDataGroup);
   }

return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::initStatusForGIIN(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initStatusForGIIN" ) );

   BFProperties *pBFPropertiesIdStatus = getFieldProperties (ifds::IdStatus, idDataGroup);
   assert (pBFPropertiesIdStatus);
   if(pBFPropertiesIdStatus)
   {
      DString idStatusSetSubst;
      pBFPropertiesIdStatus->getAllSubstituteValues (idStatusSetSubst);
      idStatusSetSubst = removeItemFromSubtList (idStatusSetSubst, ID_STATUS::OVERRIDE);
      idStatusSetSubst = removeItemFromSubtList (idStatusSetSubst, ID_STATUS::EXPIRED);
      idStatusSetSubst = removeItemFromSubtList (idStatusSetSubst, ID_STATUS::RESET);
      setFieldAllSubstituteValues (ifds::IdStatus, idDataGroup, idStatusSetSubst);
      pBFPropertiesIdStatus = getFieldProperties( ifds::IdStatus, idDataGroup );
      pBFPropertiesIdStatus->setSubstituteValues(NULL);
      setFieldValid(ifds::IdStatus, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::validateForOverlappingOfRecords(const DString& strValue,const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateForOverlappingOfRecords" ) );

   bool bFoundOverlapping = false;

   EntityIdsList *pEntityIdsList = NULL;
   pEntityIdsList = dynamic_cast<EntityIdsList*>(getParent());
   if (pEntityIdsList)
   {
      DString dstrIdTypeIn(strValue);
      dstrIdTypeIn.strip();
      EntityIds* pIDs = NULL;
      BFObjIter iter( *pEntityIdsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         DString dstrIdType;
		 iter.getObject()->getField(ifds::IdType, dstrIdType, idDataGroup, false);

         if( dstrIdType.strip() == dstrIdTypeIn && 
            iter.getObject() != this)
         {
			 DString dstrEffectiveDate, dstrStopDate, dstrCountry,
					 tmpEffectiveDate, tmpStopDate, tmpCountry;

			 getField(ifds::IdDate,dstrEffectiveDate,idDataGroup,false);
			 getField(ifds::IdExpireDate,dstrStopDate,idDataGroup,false);
			 getField(ifds::CountryOfIssue,dstrCountry,idDataGroup,false);

			 iter.getObject()->getField(ifds::IdDate,tmpEffectiveDate,idDataGroup,false);
			 iter.getObject()->getField(ifds::IdExpireDate,tmpStopDate,idDataGroup,false);
			 iter.getObject()->getField(ifds::CountryOfIssue,tmpCountry,idDataGroup,false);
			 dstrCountry.strip().upperCase();
			 tmpCountry.strip().upperCase();

			 if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDate, dstrStopDate,
				 tmpEffectiveDate, tmpStopDate))
			 {
				 if(dstrCountry == tmpCountry)
				 {
					 bFoundOverlapping = true;
					 break;
				 }
			 }

         }
         ++iter; 
      }
   }

   // the intention of this logic is prevent user to enter national id which overlapped 
   // within same period, and issued by same country, account entities is allowed to 
   // attach multiple citizenship which is valid within same period.
   if(bFoundOverlapping)
   {
      // include more type of id, also display id type as well may need to separate reject error for each of id type
      if(strValue == IDS::NATIONAL_ID || strValue == IDS::PASSPORT || 
         strValue == IDS::TAX_ID_NUMBER || strValue == IDS::EMPLOYER_NUMBER ) 
      {
         DString idiString, strCountry;
         getField(ifds::CountryOfIssue, strCountry, idDataGroup, true);
         strCountry.strip();

         DString idTypeFMT(strValue),
            countryFmt(strCountry);
         BFDataField::formatValue( ifds::IdType, idTypeFMT  );
         BFDataField::formatValue( ifds::CountryOfIssue, countryFmt  );
         countryFmt.strip();

         addIDITagValue (idiString, I_("COUNTRY"), countryFmt);
         addIDITagValue (idiString, I_("ID_TYPE"), idTypeFMT);
         getErrMsg (IFASTERR::MULTIPLE_NATIONAL_ID_NOT_ALLOWED, 
                    CND::ERR_IDTYPE_FOR_COUNTRY_EXISTED,
                    CND::WARN_IDTYPE_FOR_COUNTRY_EXISTED,
                    idDataGroup,
                    idiString);
      }
      else if(strValue == IDS::FATCA_GIIN)
      {
         getErrMsg (IFASTERR::MULTIPLE_GIIN_NOT_ALLOWED, 
                    CND::ERR_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY, 
                    CND::WARN_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY, 
                    idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIds::validateTaxIDEmployerIDForFATCA(const DString& againstedIDType, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTaxIDEmployerIDForFATCA" ) );

   // check against individual account and account propietorship
   DString dstrEntityId,
      dstrSearchKey,
      dstrAccountNum = NULL_STRING,
      dstrAccountType,
      dstrEmployeeClass;

   getField( ifds::EntityId, dstrEntityId,idDataGroup, false );
   dstrEntityId.strip().upperCase();
   
   AccountEntityXref *pAEXref = NULL;
   Entity *pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
   MFAccount *pMFAccount = NULL;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAEXref) <= WARNING &&
         pAEXref)
   {
      BFObjIter iter (*pAEXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

      AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);
      
      if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey) && pEntity)
      {
         iter.positionByKey (dstrSearchKey);

         iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         dstrAccountNum.strip().upperCase();
      }
   }

   if( dstrAccountNum != NULL_STRING &&
       getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING )
   {
      pEntity->getField( ifds::EmployeeClass, dstrEmployeeClass, idDataGroup, false );
      pMFAccount->getField( ifds::AcctType, dstrAccountType, idDataGroup, false );
      dstrEmployeeClass.strip().upperCase();
      dstrAccountType.strip().upperCase();

      if(!dstrAccountType.empty() )
      {
         EntityIdsList* pList = dynamic_cast<EntityIdsList*>(getParent());
         if(pList)
         {
            DString idiStr, strIDType, strEntCat;
            bool bHasEIN =  pList->isIdTypeExistWithValue( IDS::EMPLOYER_NUMBER, idDataGroup );
            bool bHasTIN =  pList->isIdTypeExistWithValue( IDS::TAX_ID_NUMBER, idDataGroup );

            // case 1
            if (dstrEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL && 
               DSTCommonFunctions::codeInList( dstrAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ))
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
            else if (dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE && // corporate - corporate
               !DSTCommonFunctions::codeInList( dstrAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST )) 
            {
               if(!bHasEIN && againstedIDType == IDS::TAX_ID_NUMBER )
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

               if(bHasTIN && againstedIDType == IDS::TAX_ID_NUMBER)
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
            else if (DSTCommonFunctions::codeInList( dstrAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ) &&
               dstrEmployeeClass == ENTITY_CATEGORY::CORPORATE)
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
            else if (!DSTCommonFunctions::codeInList( dstrAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST ) &&
               dstrEmployeeClass == ENTITY_CATEGORY::INDIVIDUAL) // corporate - individual
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
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//CHG0037322
void EntityIds::initSinIdDateForTFSATaxType (const BFDataGroupId& idDataGroup)
{
   AccountEntityXref *pAcctEXref = NULL;
   DString dstrEntityType;
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAcctEXref) <= WARNING &&
       pAcctEXref)
   {
      BFObjIter iter (*pAcctEXref, idDataGroup, true, 
                       BFObjIter::ITERTYPE::NON_DELETED);

      DString dstrSearchKey, dstrEntityId;
      getField( ifds::EntityId, dstrEntityId,idDataGroup, false );

      AccountEntityXref::buildPartialKeyForEntityId (dstrSearchKey, dstrEntityId);

      if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, dstrSearchKey))
      {
         iter.positionByKey (dstrSearchKey);
         // To init Current BusinessDate for TFSA account tax type.
         DString dstrAccountNum;
         MFAccount* pMFAccount;
         iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
              pMFAccount )
         {
            DString taxType, dstrCurrBusDate;
            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
            taxType.strip().upperCase();
            if(taxType == TFSA)
            {
               getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
               setFieldNoValidate( ifds::IdDate, dstrCurrBusDate, idDataGroup ); 
            }
         }
      }
   }

}
//******************************************************************************************************************
SEVERITY EntityIds::validateTaxFileNum(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTaxFileNum" ) );

	int iRemValue,iResult = 0,iIdValue,idValueInput[9];
	int tfn8_wf[8] = {10,7,8,4,6,3,5,1} ;
	int tfn9_wf[9] = {10,7,8,4,6,3,5,2,1} ;
	DString dstrIdValue;

	getField( ifds::IdValue, dstrIdValue,idDataGroup, false );
	if(dstrIdValue.isAllDigits()){
		iIdValue = atoi( dstrIdValue.asA().c_str() ) ;
		if(dstrIdValue.size()==8){
			for( int i=dstrIdValue.size()-1;i>=0;--i)		
			{
				idValueInput[i] = iIdValue % 10;
				iResult += idValueInput[i] * tfn8_wf[i];
				iIdValue /= 10;
			}
		}
		else{
			for( int i=dstrIdValue.size()-1;i>=0;--i)		
			{
				idValueInput[i] = iIdValue % 10;
				iResult += idValueInput[i] * tfn9_wf[i];
				iIdValue /= 10;
			}
		}
		iRemValue=iResult % 11;
		if(iRemValue)
		{
			getErrMsg ( IFASTERR::INVALID_TFN_VALUE,
				CND::ERR_INVALID_TFN_VALUE,
				CND::WARN_INVALID_TFN_VALUE,
				idDataGroup);
			setFieldNoValidate(ifds::IdStatus, I_("02"), idDataGroup, false, true, true );
		} else {
			setFieldNoValidate(ifds::IdStatus, I_("01"), idDataGroup, false, true, true );
		}
	}
	else {
			getErrMsg ( IFASTERR::INVALID_TFN_VALUE,
				CND::ERR_INVALID_TFN_VALUE,
				CND::WARN_INVALID_TFN_VALUE,
				idDataGroup);
		    setFieldNoValidate(ifds::IdStatus, I_("02"), idDataGroup, false, true, true );
	}
	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************************************************
SEVERITY EntityIds::validateAusBusinessNum(const BFDataGroupId& idDataGroup )
{
		MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAusBusinessNum" ) );
		    int iRemValue,iResult = 0,idValueInput[11];
			int weightingFactor[11]={10,1,3,5,7,9,11,13,15,17,19};
			DString dstrIdValue;

			getField( ifds::IdValue, dstrIdValue,idDataGroup, false );
			INT64 iIdValue = atof( dstrIdValue.asA().c_str() ) ;

			for( int i=dstrIdValue.size()-1;i>=0;--i)		
			{
				idValueInput[i] = iIdValue % 10;
				if(i==0)
				{
					idValueInput[i] -= 1;
				}
				iResult += idValueInput[i] * weightingFactor[i];
				iIdValue /= 10;
			}	
			iRemValue=iResult % 89;
			if(iRemValue)
			{
				getErrMsg ( IFASTERR::INVALID_ABN_VALUE,
							 CND::ERR_INVALID_ABN_VALUE,
		                     CND::WARN_INVALID_ABN_VALUE,
		                     idDataGroup);
				setFieldNoValidate(ifds::IdStatus, I_("02"), idDataGroup, false, true, true );
			} else {
				setFieldNoValidate(ifds::IdStatus, I_("01"), idDataGroup, false, true, true );
			}

	return GETCURRENTHIGHESTSEVERITY ();

}
//******************************************************************************************************************
SEVERITY EntityIds::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew)
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
                                            IDSEARCH_CATEGORY, 
                                            IDSEARCH_LEVEL, 
                                            _bVerificationEnabled,
											_dstrVerifyFilter);

   DString strEntityIDSearchValue;
   getField(ifds::IdType,strEntityIDSearchValue,idDataGroup,false);

   bool entityIDSearchFound = DSTCommonFunctions::codeInList (strEntityIDSearchValue, _dstrVerifyFilter) ? true : false;
   // enviroment level:
   if (_bVerificationEnabled && entityIDSearchFound)
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
   else if (!entityIDSearchFound)
   {
	   // enviroment does not support verficaiton
	   // Verify Status is read only
	   // Verify Status on new IDSEARCH is set to Verified.

	   setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
	   bReadOnly = true;
   }
   else if( _bVerificationEnabled && idDataGroup == BF::HOST  ) // if data is verified is from backend, lock verify stat
   { 
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
SEVERITY EntityIds::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChanges"));

   DString strEntityIDSearchValue;
   getField(ifds::IdType,strEntityIDSearchValue,idDataGroup,false);

   bool entityIDSearchFound = DSTCommonFunctions::codeInList (strEntityIDSearchValue, _dstrVerifyFilter) ? true : false;

   if (!_bVerificationEnabled || _bInit )
      return GETCURRENTHIGHESTSEVERITY ();
   else if (!entityIDSearchFound)
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
SEVERITY EntityIds::validationEntitySearchID (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validationEntitySearchID"));

    DString entityId,
            strEntityTypeFmt;
	Entity *pEntity = NULL;
    getField (ifds::EntityId, entityId, idDataGroup, false);
    getWorkSession().getEntity (idDataGroup, entityId, pEntity);
    if(pEntity)
    {
		strEntityTypeFmt= pEntity->getEntityType ();
    }

   EntitySearchIDValueValidation pEntitySearchIDValueValidation(*this);

   DString SrchEntType,
			SrchIdType,
			dstrErrDesc,
			dstrErrorCode,
			dstrEwi;
  getField (ifds::IdType, SrchIdType, idDataGroup, false);    

   if( pEntitySearchIDValueValidation.init( strEntityTypeFmt,
                             SrchIdType,
							 entityId
                           ) <= WARNING )
   {
	  pEntitySearchIDValueValidation.getField(ifds::ErrorCode,dstrErrorCode,idDataGroup,false);
	  pEntitySearchIDValueValidation.getField(ifds::EWI,dstrEwi,idDataGroup,false);     
   }

 if(dstrErrorCode == "2222")
 {
	 if(dstrEwi.stripAll().upperCase() == I_( "E" ))
	 {
		ADDCONDITIONFROMFILE (CND::ERR_BIC_CODE_LINKED_MSG);
	 }
	 else if(dstrEwi.stripAll().upperCase() == I_( "W" ))
	 {
		 ADDCONDITIONFROMFILE (CND::WARN_BIC_CODE_LINKED_MSG);
	 }
 }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityIds.cpp-arc  $
 * 
 *    Rev 1.118   Aug 16 2012 10:53:18   wp040027
 * IN#3008167-P187485-CPF- Account Entity (RA) validation
 * 
 *    Rev 1.117   Aug 10 2012 15:08:48   dchatcha
 * IN#3053906 - P0179630 FN01 FATCA - Acct Doc List and Entitymaintenance screen issues, country of issue is not allowed to enter for TIN\EIN.
 * 
 *    Rev 1.116   Aug 02 2012 16:13:52   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, fix for trust account number format validation always failed.
 * 
 *    Rev 1.115   Jul 23 2012 19:04:02   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.114   Jul 23 2012 17:06:52   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.113   Jul 16 2012 15:02:54   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.112   Jul 12 2012 19:02:36   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.111   Apr 27 2012 09:53:28   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.110   Apr 04 2012 21:24:38   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.109   Apr 04 2012 21:17:24   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.108   Feb 06 2012 04:23:40   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.107   Jan 04 2012 11:11:18   wutipong
 * IN2717890 - Cannot open RESPs in Desktop
 * 
 *    Rev 1.106   Oct 14 2011 03:10:54   kitticha
 * PETP0186486 FN01 IN2685299 - RRSP Loan program issues.
 * 
 *    Rev 1.105   Sep 02 2011 13:07:10   kitticha
 * PETP0186486 FN01 - RRSP Loan Program.
 * 
 *    Rev 1.104   Jul 26 2011 00:43:20   wutipong
 * IN#2473119 - ECF Marketing File - revised
 * 
 *    Rev 1.103   Apr 08 2011 12:06:16   wutipong
 * IN#2473119 - Acct Marketing File Issue
 * 
 *    Rev 1.102   Dec 28 2010 21:36:36   dchatcha
 * IN# 2360999 - unable to add Fund Broker at System Level in AFT Desktop,just ensure result would be capital letter.
 * 
 *    Rev 1.101   Dec 27 2010 02:14:20   dchatcha
 * IN# 2360999 - unable to add Fund Broker at System Level in AFT Desktop
 * 
 *    Rev 1.100   Nov 26 2010 06:18:28   wutipong
 * IN#2143362
 * 
 *    Rev 1.99   Nov 25 2010 08:14:52   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.98   Nov 23 2010 08:50:12   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.97   Oct 29 2010 07:18:08   panatcha
 * PET165541_FN03_QESI_Phase3_Non_Finance
 * 
 *    Rev 1.96   Oct 08 2010 04:46:46   kitticha
 * PETP0172931_FN01_IN#2283060
 * 
 *    Rev 1.95   Aug 16 2010 06:26:30   panatcha
 * P0172931_FN01_MT53X_Entity Creation
 * 
 *    Rev 1.94   May 14 2010 02:03:20   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Removed adding default conditions for RESP Designated Inst.
 * 
 *    Rev 1.93   Apr 30 2010 11:12:10   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.92   Apr 07 2010 11:37:08   kitticha
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading, recheck in 1.89.
 * 
 *    Rev 1.91   Apr 07 2010 11:29:08   kitticha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fix Tax type issue.
 * 
 *    Rev 1.90   Apr 07 2010 11:11:24   kitticha
 * PET165541_FN01_QESI - RESp Gap_Dsk_NASU - Fix a bit taxtype issue.
 * 
 *    Rev 1.89   Apr 07 2010 09:35:38   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.88   Apr 03 2010 01:22:58   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.87   Mar 29 2010 07:05:00   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.86   Mar 23 2010 16:32:38   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU - remove a check for PCG empty
 * 
 *    Rev 1.85   Mar 12 2010 14:59:44   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.84   Oct 01 2009 11:37:54   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer, Code review.
 * 
 *    Rev 1.83   Sep 28 2009 08:02:34   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer.
 * 
 *    Rev 1.82   04 Jun 2009 12:01:10   sibuhatm
 * Validation is added to reuse the BAD Entity's BIC Code value.
 * 
 * Here after User cannot enter the duplicate BIC Code in the same Entity as well as any Entity.
 * 
 * User can reuse the BAD Entity BIC Code
 * 
 * IN 1707813 - Not possible to add a new Network Sender Entity Record - AXAUAT1
 * 
 *    Rev 1.81   16 Mar 2009 13:43:34   kovacsro
 * 1628042 - ReceiverNetworkAddr not populated for Clearing Accounts
 * 
 *    Rev 1.80   09 Mar 2009 17:58:02   popescu
 * Incident #1616419 - Desktop freezes when change SIN# from a valid# to Invalid#000-000-000
 * 
 *    Rev 1.79   Jan 27 2009 06:22:18   daechach
 * IN 1548019 - New CBO level error codes for MT535/536.
 * 
 *    Rev 1.78   23 Jan 2009 16:32:30   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.77   16 Jan 2009 17:23:08   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.76   Jan 07 2009 04:46:00   daechach
 * IN 1544134 - R91-MT535/MT536-Clearing platform BIC code disp blank, etc.
 * 
 *    Rev 1.75   Dec 15 2008 01:45:44   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.74   06 Oct 2008 13:16:54   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.73   16 Oct 2007 09:21:48   kovacsro
 * IN#1040650 - show error message when user attempts to reset an overridden Access ID
 * 
 *    Rev 1.72   15 Oct 2007 15:10:38   kovacsro
 * IN#1041113 added parameter to ERR_INVAID_STATUS_FOR_ACCESS_ID
 * 
 *    Rev 1.71   21 Sep 2007 14:01:02   kovacsro
 * IN1003607 - added   ERR_INVALID_STATUS_FOR_ACCESS_ID
 * 
 *    Rev 1.70   20 Sep 2007 17:21:20   popescu
 * GAP 6 - do not allow AccessId override if flag from back-end is set to no.
 * 
 *    Rev 1.69   10 Sep 2007 16:32:08   popescu
 * GAP 6 - restrict updates to id status only for access ids 
 * 
 *    Rev 1.68   04 Sep 2007 12:51:42   popescu
 * GAP 6 - added id status to the entity maintenance screen
 * 
 *    Rev 1.67   16 Aug 2007 12:51:12   popescu
 * Incident# 977474 - access id shhould not be created by the user
 * 
 *    Rev 1.66   17 Jul 2007 15:19:04   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.65   12 Jul 2007 18:41:16   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 *    Rev 1.64   06 Jul 2007 14:43:16   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.63   Nov 20 2006 13:52:30   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.62   Nov 09 2006 13:44:08   jankovii
 * Incident #737656. BIC code validation.
 * 
 *    Rev 1.61   Nov 06 2006 10:06:36   jankovii
 * Incident #737656: Bic code validation.
 * 
 *    Rev 1.60   Oct 24 2006 17:45:06   jankovii
 * Incident 737656 - BIC code validation.
 * 
 *    Rev 1.59   Oct 19 2006 14:14:50   jankovii
 * Incident 737656 - No validation for unique BIC code during new entity setup. 
 * 
 *    Rev 1.58   Oct 17 2006 13:06:48   jankovii
 * Incident xxxx: Validate BIC code only if entity is network sender.
 * 
 *    Rev 1.57   Jul 26 2006 13:43:52   jankovii
 * PET 2192 FN02 - Dealings Sender Cut Off Time.
 * 
 *    Rev 1.56   Jul 24 2006 11:46:28   jankovii
 * PET 2192 FN02 Dealings Sender Cut Off Time.
 * 
 *    Rev 1.55   Jun 23 2005 14:48:54   porteanm
 * Incident 332074 - Duplicate SIN rej-error.
 * 
 *    Rev 1.54   May 19 2005 15:54:32   yingbaol
 * Incident 297032:  all fields should not be allowed to update if the stratus is bad. 
 * 
 *    Rev 1.53   Mar 30 2005 14:34:36   porteanm
 * Incident 275271 - SIN validation, syncup from 1.51.1.0
 * 
 *    Rev 1.52   Mar 01 2005 11:52:14   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.51   Nov 23 2004 17:24:58   Fengyong
 * PET1117FN54 - adjustment after first day intergretion test
 * 
 *    Rev 1.50   Nov 22 2004 12:36:10   popescu
 * Routing type no longer needed, comment out the code
 * 
 *    Rev 1.49   Nov 19 2004 15:36:38   hernando
 * PTS10034703 - When validating SIN, check for duplicate SIN.
 * 
 *    Rev 1.48   Nov 15 2004 15:41:52   Fengyong
 * Syncup - after .net conversion
 * 
 *    Rev 1.47   Nov 14 2004 14:36:38   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.46   Nov 04 2004 11:01:06   FENGYONG
 * PET1117 FN54 - Fund broker static temp check in for 59 build
 * 
 *    Rev 1.45   Jan 02 2004 15:12:02   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.44   Nov 25 2003 12:17:50   popescu
 * PTS 10024062, before checking for a duplicate SIN see whether SIN is part of the exception list
 * 
 *    Rev 1.43   Nov 17 2003 14:32:58   popescu
 * PTS 10023438, SIN RESP validation, do not to add warnings if ErrorValue from err msg rule list return 'I'
 * 
 *    Rev 1.42   Nov 12 2003 15:40:18   popescu
 * PTS 10023438, do not treat warning comming from view 142 (ErrMsgRules) as an error. 
 * 
 *    Rev 1.41   Nov 10 2003 11:25:56   popescu
 * Removed a not used boolean declaration, should not impact anything
 * 
 *    Rev 1.40   Nov 08 2003 21:46:08   popescu
 * PTS 10023438, performance issues fixes, do not call PopulateWhereUsed anymore, data is in memory
 * 
 *    Rev 1.39   Nov 06 2003 09:41:00   popescu
 * PTS 10023703, fixed error message for non-sin type of id's.
 * 
 *    Rev 1.38   Nov 05 2003 18:05:16   popescu
 * PTS 10023703, Erroneous warning 'Account owner SIN missing' pops-up, although the SIN number is correctly retrieved by Desktop from back-end,
 * 
 *    Rev 1.37   Nov 05 2003 14:25:52   popescu
 * PTS 10023438, SIN should be required and valid if acct is RESP or family RESP and  entity is acct owner or beneficiary
 * 
 *    Rev 1.36   Nov 05 2003 10:41:04   popescu
 * PTS 10023711
 * 
 *    Rev 1.35   Oct 30 2003 17:26:10   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 *    Rev 1.34   Oct 30 2003 16:30:32   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 *    Rev 1.33   Apr 07 2003 18:05:18   ZHANGCEL
 * Bug fix for PTS tickts 10011373, 10011967 : Make Entity IDValue validation being correct
 * 
 *    Rev 1.32   Mar 21 2003 18:08:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.31   Oct 09 2002 23:54:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.30   Sep 23 2002 15:10:44   KOVACSRO
 * Fixed checking for duplicate SIN.
 * 
 *    Rev 1.29   Aug 29 2002 12:55:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.28   Aug 16 2002 12:58:52   HSUCHIN
 * change default values for Lux market for Id Type
 * 
 *    Rev 1.27   Jul 10 2002 17:44:04   ZHANGCEL
 * Minor changes
 * 
 *    Rev 1.26   Jul 04 2002 18:34:38   ZHANGCEL
 * Bug fix for SIN checking
 * 
 *    Rev 1.25   22 May 2002 18:28:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.24   31 Jul 2001 09:56:16   WINNIE
 * default value for LUX change to 'Non Provided'  ('05')
 * 
 *    Rev 1.23   May 23 2001 15:49:18   JANKAREN
 * Sync up SSB (1.21.1.0)
 * 
 *    Rev 1.22   03 May 2001 14:06:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.21   Mar 29 2001 15:59:24   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.20   Mar 28 2001 14:12:54   HERNANDO
 * Revised Default values; commented-out optimized ValidateSIN
 * 
 *    Rev 1.19   Mar 27 2001 14:46:16   HERNANDO
 * Change market literal.
 * 
 *    Rev 1.18   Mar 27 2001 13:24:22   HERNANDO
 * Added doInitWithDefaultValues; SIN default, Driver's License for LUX
 * 
 *    Rev 1.17   Mar 21 2001 09:37:16   YINGZ
 * fix checkForDuplicateSIN
 * 
 *    Rev 1.16   Mar 18 2001 19:22:26   WINNIE
 * fix crash for calling view 3 to check duplicate SIN;
 * comment out duplicateSIN check due to it is still causing problem when committing data
 * 
 *    Rev 1.15   Jan 19 2001 11:13:22   OLTEANCR
 * fix
 * 
 *    Rev 1.14   Jan 18 2001 14:09:14   OLTEANCR
 * changed checkForDuplicateSIN (..) to use new data brokering syst.
 * 
 *    Rev 1.13   Jan 17 2001 12:08:28   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions ()
 * 
 *    Rev 1.12   Dec 17 2000 20:23:18   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.11   Nov 30 2000 12:18:04   WINNIE
 * logic continue to check duplicate SIN regardless; remove duplicate check of SIN in the doValidateAll since doValidateField already handle it.
 * 
 *    Rev 1.10   Nov 29 2000 15:10:20   WINNIE
 * validateSIN allow user to enter its own SIN number
 * 
 *    Rev 1.9   Nov 13 2000 16:55:58   KOVACSRO
 * bug fixed.
 * 
 *    Rev 1.8   Nov 13 2000 15:29:04   KOVACSRO
 * cleanup after BFBase modifications.
 * 
 *    Rev 1.7   Nov 13 2000 10:22:26   KOVACSRO
 * Added checkForDuplicateSIN () called from ValidateSIN  (whenever necessary) and always from doValidateAll.
 * 
 *    Rev 1.6   Sep 29 2000 13:27:10   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.5   Aug 15 2000 10:55:48   ZHANGCEL
 * Added more logic for ValidateSIN ()
 * 
 *    Rev 1.4   Aug 11 2000 10:39:30   YINGBAOL
 * fix bug in validation and add condition
 * 
 *    Rev 1.3   Aug 08 2000 12:06:12   ZHANGCEL
 * Change the name of ValidateIdValue to ValidateSIN
 * 
 *    Rev 1.2   Aug 01 2000 15:58:52   ZHANGCEL
 * Added doApplyRelateChanged () and ValidateIdValue ()
 * 
 *    Rev 1.1   Jul 20 2000 14:37:12   HUANGSHA
 * validation for IDS and BirthName based on the system feature
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Feb 03 2000 10:51:04   BUZILA
// INIT_TO_DEFAULT flag took out
// 
//    Rev 1.7   Feb 01 2000 14:36:26   BUZILA
// added lValidateGroup parameter to doValidateAll method
// 
//    Rev 1.6   Jan 06 2000 16:21:10   VASILEAD
// Business edits for Entity screen
// 
//    Rev 1.5   Dec 24 1999 15:18:24   VASILEAD
// Fixed transactions
// 
//    Rev 1.4   Dec 12 1999 16:25:18   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/