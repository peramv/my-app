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
//    Copyright 1999 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : Address.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 10/06/99
//
// ^CLASS    : Address
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountmailinglist.hpp"
#include "accountmailinginfo.hpp"
#include "accountentityxref.hpp"
#include "address.hpp"
#include "addresslist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "entity.hpp"
#include "intermediary.hpp"
#include "intermediarylist.hpp"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtcooptions2.hpp"
#include "mgmtco.hpp"
#include "nomineeinteraddr.hpp"
#include "nomineeinteraddrlist.hpp"
#include "provincelist.hpp"
#include "residency.hpp"
#include "rrif_lif_lrif_info.hpp"
#include "rrif_lif_lrif_infolist.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "worksessionentitylist.hpp"

#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_req.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0114_req.hpp>

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_INSTITUTE_CODE;

   extern const long ERR_INNONE_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
   extern const long ERR_DEFF_STOP_DATE_RANGE_EXISTS;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_ADDRESS_LINE_MISSING;
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;
   extern const long ERR_DUPLICATE_ADDRESS_CODE;
   extern const long ERR_ADDRESS_TWO_LINE;
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;
   extern const long ERR_ADDRESS_LINE45;
   extern const long ERR_INVALID_POSTAL_CODE;
   extern const long ERR_FEDERAL_NOT_VALID_TAX;
   extern const long ERR_INVALID_POSTAL_CODE_PROVINCE;
   extern const long ERR_REG_ADDRESS_CODE_IS_NOT_APPLICABLE_FOR_ADDRESSCODE;
   extern const long ERR_REG_ADDRESS_CODE_IS_NOT_AVAILABLE;
   extern const long ERR_REG_ADDRESS_CODE_IS_NOT_BLANK;
   extern const long ERR_DATE_NUST_BEFORE_CURRBUSDATE;
   extern const long ERR_RETMAIL_MUST_BE_NO_WHEN_ADDRESS_CHANGED;
   extern const long WARN_ENSURE_PAC_IS_ALLOWED;
   extern const long ERR_REGISTER_ADDRESS_FOR_BROKER_CANNOT_BE_CHANGED; 
   extern const long WARN_RET_MAIL_CHANGED; 
   extern const long WARN_RET_MAIL_CHANGED_CHANGE_HOLD_FLAG; 
   extern const long WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET;
   extern const long WARN_APPLICABLE_ACCT_LEVEL_STOP_FLAG_MUST_BE_RELEASED;
   extern const long WARN_ONHOLD_FLAG_FOR_APPLICABLE_ADDR_MUST_BE_RELEASED;
   extern const long WARN_RETMAIL_REASON_IS_BLANK;
   extern const long ERR_NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern const long WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern const long ERR_PROVINCE_BLANK_FOR_USA;
   extern const long ERR_WRONG_VERIFY_STATUS;
   extern const long ERR_ADDRESS_NOT_VERIFY;
   extern const long WARN_ADDRESS_NOT_VERIFY;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION;
   extern const long ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_NON_RESIDENT_TAX_JURID;
   extern const long WARN_NON_RESIDENT_TAX_JURID;
   extern const long ERR_TAX_JURIS_EMPTY;
   extern const long WARN_TAX_JURIS_CHANGED_ENSURE_RRIF_IS_FOLLOWED_NEW_TAX;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Address;
   extern CLASS_IMPORT const BFTextFieldId KanaAddress;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId AddrCntryCode;
   extern CLASS_IMPORT const BFTextFieldId RegAddrCode;

   extern CLASS_IMPORT const BFTextFieldId Addr11Line1;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line2;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line3;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line4;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line5;
   extern CLASS_IMPORT const BFTextFieldId ShrAddressFormat;

   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId FieldAssignment;
   extern CLASS_IMPORT const BFTextFieldId AllowRetMailAutomation;
   extern CLASS_IMPORT const BFTextFieldId SalutationSetField;
//nominee/intermediary address handling
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId InterAccount;

   extern CLASS_IMPORT const BFTextFieldId RetMailReasonCode;
   extern CLASS_IMPORT const BFDateFieldId UnclmStmtDate;
   extern CLASS_IMPORT const BFDateFieldId UnclmRemitDate;
   extern CLASS_IMPORT const BFTextFieldId UnclmComment;
   extern CLASS_IMPORT const BFTextFieldId UnclmRetMailStage;
   extern CLASS_IMPORT const BFDateFieldId StageStampDate;

   extern CLASS_IMPORT const BFTextFieldId Authorization;

   extern CLASS_IMPORT const BFTextFieldId UpdShrProvRes;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisUpdateOpt;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFTextFieldId CountryProvinceUSA;
   extern CLASS_IMPORT const BFTextFieldId ClosedCountryApplicable;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId RecipientType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveFrom;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId RetMailUpdt;
}

namespace  
{
   const I_CHAR * const ADDRESS_CODE_K       = I_("K0123456789");
   const I_CHAR * const CLASSNAME            = I_("Address");
   const I_CHAR * const YES_STRING           = I_("Yes");
   const I_CHAR * const Y_STRING             = I_("Y");
   const I_CHAR * const N_STRING             = I_("N");
   const I_CHAR * const IDI_CODE             = I_("CODE");  
   const I_CHAR * const ONE                  = I_("1");  
   const I_CHAR * const TWO                  = I_("2");  
   const I_CHAR * const THREE                = I_("3");  
   const I_CHAR * const RETURN_STRING        = I_("\r\n");  
   const I_CHAR * const EMPTY_STR            = I_("");
   const I_CHAR * const GERMANY              = I_("004");
   const I_CHAR * const TFSA_TAX_TYPE        = I_("V");
   const I_CHAR * const EXT_TFSA_TAX_TYPE    = I_("Z");
   const I_CHAR * const RRSP_TAX_TYPE        = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE        = I_( "2" ); 
   const I_CHAR * const REGISTRATION_ADDRESS = I_("01");
   const I_CHAR * const SYSTEM_ASSIGNED      = I_("System");
   const I_CHAR * const USER_OVERRIDEN       = I_("User");
   const I_CHAR * const YES                  = I_("Y");
   const I_CHAR * const NO                   = I_("N");
   const I_CHAR * const CANADA_COUNTRY       = I_("0100");
   const I_CHAR * const USA_COUNTRY          = I_("0130");
   const I_CHAR * const SHRHLDR_LEVEL        = I_("01");
   const I_CHAR * const SHRHLDR_CATEGORY     = I_("3");
   const I_CHAR * const UNVERIFIED           = I_("02");
   const I_CHAR * const VERIFIED             = I_("01");
   const I_CHAR * const UNASSIGNED_COUNTRY   = I_("0000");

   const int MAIL_ASSIGN_COUNT               = 19;
   const int MAIL_ASSIGN_FIELD               = 3;

   const int FIELD_ADDR_CODE                 = 0;
   const int FIELD_ADDR_ONHOLD               = 1;
   const int FIELD_ADDR_AUTH                 = 2;
   
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_TRADE;
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURID;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RETURNED_MAIL_AUTOMATION;
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const UNCLAIM_RETURN_MAIL;
   extern CLASS_IMPORT I_CHAR * const SHR_ADDRESS_VERIFICATION;
}

namespace AUTHORIZATION_CODE
{
   extern const I_CHAR * const DEFAULT              = I_("D");
   extern const I_CHAR * const AUTHORIZATION        = I_("A");
   extern const I_CHAR * const PERMANENT            = I_("P");
   extern const I_CHAR * const RET_MAIL             = I_("R");
   extern const I_CHAR * const UNCLAIMED_PROPERTY   = I_("U");
}

namespace ACCT_DESIGNATION
{
   const I_CHAR * const CLIENT         = I_("1");
   const I_CHAR * const NOMINEE        = I_("2");
   const I_CHAR * const INTERMEDIARY   = I_("3");
}

//*****************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
#if 1
   {ifds::ShrNum,            BFCBO::NONE,                 0}, 
   {ifds::Confirm,           BFCBO::NONE,                 0}, 
   {ifds::AddrCode,          BFCBO::REQUIRED,             0}, 
   {ifds::AddrCodeDesc,      BFCBO::READ_ONLY,            0}, 
   {ifds::Name1,             BFCBO::NONE,                 0}, 
   {ifds::Name2,             BFCBO::NONE,                 0}, 
   {ifds::AddrLine1,         BFCBO::NONE,                 0}, 
   {ifds::AddrLine2,         BFCBO::NONE,                 0}, 
   {ifds::AddrLine3,         BFCBO::NONE,                 0}, 
   {ifds::AddrLine4,         BFCBO::NONE,                 0}, 
   {ifds::AddrLine5,         BFCBO::NONE,                 0}, 
   {ifds::PostalCode,        BFCBO::NONE,                 0}, 
   {ifds::CountryName,       BFCBO::NONE,                 0}, 
   {ifds::CountryCode,       BFCBO::REQUIRED,             0}, 
   {ifds::AddressFileRid,    BFCBO::NONE,                 0}, 
   {ifds::AddressFileVer,    BFCBO::NONE,                 0}, 
   {ifds::Salutation,        BFCBO::NONE,                 0}, 
   {ifds::EffectiveDate,     BFCBO::REQUIRED,             0}, 
   {ifds::StopDate,          BFCBO::REQUIRED,             0}, 
   {ifds::kAddrLine1,        BFCBO::NONE,                 0}, 
   {ifds::kAddrLine2,        BFCBO::NONE,                 0}, 
   {ifds::kAddrLine3,        BFCBO::NONE,                 0}, 
   {ifds::kAddrLine4,        BFCBO::NONE,                 0}, 
   {ifds::kAddrLine5,        BFCBO::NONE,                 0}, 
   {ifds::KAddrFileRid,      BFCBO::NONE,                 0}, 
   {ifds::KAddrFileVer,      BFCBO::NONE,                 0}, 
   {ifds::Address,           BFCBO::NONE,                 0}, 
   {ifds::KanaAddress,       BFCBO::NONE,                 0}, 
   {ifds::EffectiveStopDate, BFCBO::NONE,                 0}, 
   {ifds::AddrCntryCode,     BFCBO::NONE,                 0}, 
   {ifds::ProvinceCanadaUS,  BFCBO::NONE,                 0}, 
   {ifds::City,              BFCBO::NONE,                 0}, 
   {ifds::FieldAssignment,   BFCBO::IMMEDIATE_VALIDATION, 0}, 
   {ifds::RetMailFlag,       BFCBO::IMMEDIATE_VALIDATION, 0}, 
   {ifds::RetMailDate,       BFCBO::IMMEDIATE_VALIDATION, 0}, 

//fields used for the nominee/intermediary address handling
   {ifds::RegAddrCode,       BFCBO::NONE,                 0}, 
   {ifds::TaxType,           BFCBO::NONE,                 0}, 
   {ifds::BrokerCode,        BFCBO::NONE,                 0}, 
   {ifds::InterCode,         BFCBO::NONE,                 0}, 

// Unclaimed property related fields
   {ifds::RetMailReasonCode, BFCBO::NONE,                 0}, 
   {ifds::UnclmStmtDate,     BFCBO::READ_ONLY,            0}, 
   {ifds::UnclmRemitDate,    BFCBO::READ_ONLY,            0}, 
   {ifds::UnclmComment,      BFCBO::NONE,                 0}, 
   {ifds::UnclmRetMailStage, BFCBO::NONE,                 0}, 
   {ifds::StageStampDate,    BFCBO::NONE,                 0}, 
   {ifds::StageAssignBy,     BFCBO::NONE,                 0}, 

   {ifds::UpdShrTaxJuris,    BFCBO::NONE,                 0}, 
   {ifds::UpdShrProvRes ,    BFCBO::NONE,                 0}, 
   {ifds::IsNewOrUpdate ,    BFCBO::NONE,                 0}, 
   {ifds::CountryProvinceUSA, BFCBO::IMMEDIATE_VALIDATION, 0},
   {ifds::SkipValidate ,      BFCBO::NONE,                 0},
   {ifds::VerifyStat,         BFCBO::NONE,        0 },
#else
   // For .NET Conversion.  Ignore this for now...
   // CP20041108
   { ifds::ShrNum,            BFCBO::NONE,                 0 }, 
   { ifds::Confirm,           BFCBO::NONE,                 0 }, 
   { ifds::AddrCode,          BFCBO::REQUIRED,             0 }, 
   { ifds::AddrCodeDesc,      BFCBO::READ_ONLY,            0 }, 
   { ifds::Name1,             BFCBO::NONE,                 0 }, 
   { ifds::Name2,             BFCBO::NONE,                 0 }, 
   { ifds::AddrLine1,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine2,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine3,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine4,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine5,         BFCBO::NONE,                 0 }, 
   { ifds::PostalCode,        BFCBO::NONE,                 0 }, 
   { ifds::CountryName,       BFCBO::NONE,                 0 }, 
   { ifds::CountryCode,       BFCBO::REQUIRED,             0 }, 
   { ifds::AddressFileRid,    BFCBO::NONE,                 0 }, 
   { ifds::AddressFileVer,    BFCBO::NONE,                 0 }, 
   { ifds::Salutation,        BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,     BFCBO::REQUIRED,             0 }, 
   { ifds::StopDate,          BFCBO::REQUIRED,            0 },  
   { ifds::kAddrLine1,        BFCBO::NONE,                 0 }, 
   { ifds::kAddrLine2,        BFCBO::NONE,                 0 }, 
   { ifds::kAddrLine3,        BFCBO::NONE,                 0 }, 
   { ifds::kAddrLine4,        BFCBO::NONE,                 0 }, 
   { ifds::kAddrLine5,        BFCBO::NONE,                 0 }, 
   { ifds::KAddrFileRid,      BFCBO::NONE,                 0 }, 
   { ifds::KAddrFileVer,      BFCBO::NONE,                 0 }, 
   { ifds::Address,           BFCBO::NONE,                 0 }, 
   { ifds::KanaAddress,       BFCBO::NONE,                 0 }, 
   { ifds::EffectiveStopDate, BFCBO::NONE,                 0 }, 
   { ifds::AddrCntryCode,     BFCBO::NONE,                 0 },
   { ifds::City,              BFCBO::NONE,                 0 },
   { ifds::FieldAssignment,   BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::RetMailFlag,       BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::RetMailDate,       BFCBO::IMMEDIATE_VALIDATION, 0 },

//fields used for the nominee/intermediary address handling
   { ifds::RegAddrCode,       BFCBO::NONE,                 0 },
   { ifds::TaxType,           BFCBO::NONE,                 0 },
   { ifds::BrokerCode,        BFCBO::NONE,                 0 },
   { ifds::InterCode,         BFCBO::NONE,                 0 },
#endif

};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof(classObjectInfo) / sizeof(BFCBO::CLASS_OBJECT_INFO);

struct _countryPost
{
   const I_CHAR* _countryCode;
   const I_CHAR* _PostalCode;
};

const struct _countryPost cPostalCode[] = 
{
   I_("0001"),I_("V"),//B.C.
   I_("0002"),I_("T"),//Alberta
   I_("0003"),I_("S"),//Saskatchenwan
   I_("0004"),I_("R"),//Manitoba
   I_("0005"),I_("K"),//Ontario
   I_("0005"),I_("L"),//Ontario
   I_("0005"),I_("M"),//Ontario
   I_("0005"),I_("N"),//Ontario
   I_("0005"),I_("P"),//Ontario
   I_("0006"),I_("G"),//Quebec
   I_("0006"),I_("H"),//Quebec
   I_("0006"),I_("J"),//Quebec
   I_("0007"),I_("E"),//N.B.
   I_("0008"),I_("B"),//N.S.
   I_("0009"),I_("C"),//P.E.I.
   I_("0010"),I_("A"),//Newfoundland
   I_("0011"),I_("Y"),//Yukon
   I_("0012"),I_("X"),//North West Territories
   I_("0013"),I_("X0A"), // Nunavut
   I_("0013"),I_("X0B"), // Nunavut
   I_("0013"),I_("X0C"), // Nunavut
   I_("\0"),I_("\0")
};


//*****************************************************************************
SEVERITY Address::buildAddressLine1 (
      DSTCWorkSession &rpDSTCWorkSession,
      const DString &accountNum,
      DString& adressLine1, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("buildAddressLine1"));
//build address line 1 for intermediary/nominee accounts
//pattern is: 'A/C' + MFAccount.AltAccount value + Primary Account owner's name
   MFAccount *pMFAccount = NULL;
   if (rpDSTCWorkSession.getMFAccount (idDataGroup, accountNum, 
      pMFAccount) <= WARNING &&
         pMFAccount)
   {
      AccountEntityXref *pAccountEntityXref = NULL;

      if (rpDSTCWorkSession.getAccountEntityXref (idDataGroup, 
               pAccountEntityXref) <= WARNING &&
            pAccountEntityXref)
      {
         DString entityIdSeq1;
      
         if (pAccountEntityXref->GetEntityIdForAccountOwnerSequence1 (
               accountNum, 
               idDataGroup, 
               entityIdSeq1) <= WARNING)
         {
            DString fullName,
               link;
            
//check whether account is joint
            if (pMFAccount->isJoint (idDataGroup))
            {
               DString xRefFey;            
               AccountEntityXref::buildKey (
                     xRefFey, 
                     accountNum, 
                     I_("01"), 
                     I_("1"), 
                     entityIdSeq1);
               BFObjIter iterXRef (
                  *pAccountEntityXref, 
                  idDataGroup, 
                  true, //match substrings
                  BFObjIter::ITERTYPE::NON_DELETED);

               if (iterXRef.positionByKey (xRefFey)) //find the deposition code
               {
                  DString deposition;

                  iterXRef.getObject()->getField (ifds::DepositionCode, deposition, 
                           idDataGroup, false);
                  if (deposition == I_("01")) //one to sign
                  {
                     link = I_(" or ");
                  }
                  else if (deposition == I_("02") || //all to sign
                     deposition == I_("03")) //not clear what to do if '03'
                  {
                     link = I_(" & ");
                  }
                  else 
                  {
                     link = I_(" ");
                  }
               }
               //get the list account owners
               std::vector< DString > ownerEntities;

               pAccountEntityXref->getAcctOwnerEntities (ownerEntities, accountNum, idDataGroup);
            for ( std::vector<DString>::size_type i = 0; i < ownerEntities.size(); ++i)
               {
                  Entity *pEntity = NULL;

                  if (rpDSTCWorkSession.getEntity (idDataGroup, 
                        ownerEntities [i], pEntity) <= WARNING &&
                     pEntity)
                  {
                     DString _firstName,
                        _lastName;

                     pEntity->getField (ifds::FirstName, _firstName, 
                        idDataGroup, false);
                     if (!_firstName.empty())
                     {
                        //pick first letter similar with IFast base
                        _firstName = _firstName.substr (0, 1) + I_(".");
                     }
                     pEntity->getField (ifds::LastName, _lastName, 
                        idDataGroup, false);
//if the last name is found in the fullname then do not add it any more,
//pick the already existing first name and add the second, third... first name 
//(string looks like 'J. or M. Blow', for a joint account of Joe and Mary Blow, 
//deposition 'either one to sign')
                     DString::size_type pos = fullName.find (_lastName);
                     if (pos != DString::npos) //found the last name
                     {
                        DString firstNames = fullName.substr (0, pos);

                        fullName = 
                           firstNames + 
                           (!firstNames.empty() ? link : I_("")) +
                           _firstName + 
                           (!_firstName.empty() ? I_(" ") : I_("")) +
                           fullName.substr (pos);
                     }
                     else // not found
                     {
                        fullName += 
                           (!fullName.empty() ? link : I_("")) +
                           _firstName + 
                           (!_firstName.empty() ? I_(" ") : I_("")) +
                           _lastName;
                     }
                  }
               }
            }
            else //not a joint account
            {
               Entity *pEntity = NULL;

               if (rpDSTCWorkSession.getEntity (idDataGroup, 
                     entityIdSeq1, pEntity) <= WARNING &&
                  pEntity)
               {
                  DString firstName,
                     lastName;

                  pEntity->getField (ifds::FirstName, firstName, idDataGroup, false);
                  pEntity->getField (ifds::LastName, lastName, idDataGroup, false);
                  fullName =  
                     firstName + 
                     (!firstName.empty() ? I_(" ") : I_("")) +
                     lastName;
               }
            }
            DString altIntAccount,
               acctDesignation;

            pMFAccount->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
            if (acctDesignation == I_("2")) //nominee
            {
               pMFAccount->getField (ifds::AltAccount, altIntAccount, idDataGroup, false);
            }
            else if (acctDesignation == I_("3")) //intermediary
            {
               pMFAccount->getField (ifds::InterAccount, altIntAccount, idDataGroup, false);
            }
            adressLine1 = 
                  I_("A/C ") + 
                  altIntAccount + 
                  (!altIntAccount.empty() ? I_(" ") : I_("")) +
                  fullName;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
Address::Address(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
_blRetMail(false),
_dstrVerifyStatus (NULL_STRING),
_bIsDirty (false),
_bCanVerify (false),
_bVerificationEnabled (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
   addCrossEdit(ifds::Address, ifds::AddrLine1);
   addCrossEdit(ifds::Address, ifds::AddrLine2);
   addCrossEdit(ifds::Address, ifds::AddrLine3);
   addCrossEdit(ifds::Address, ifds::AddrLine4);
   addCrossEdit(ifds::Address, ifds::AddrLine5);

   addCrossEdit(ifds::KanaAddress, ifds::kAddrLine1);
   addCrossEdit(ifds::KanaAddress, ifds::kAddrLine2);
   addCrossEdit(ifds::KanaAddress, ifds::kAddrLine3);
   addCrossEdit(ifds::KanaAddress, ifds::kAddrLine4);
   addCrossEdit(ifds::KanaAddress, ifds::kAddrLine5);
   addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
   addCrossEdit(ifds::FieldAssignment, ifds::PostalCode);
   addCrossEdit(ifds::FieldAssignment, ifds::CountryCode);
   
   addCrossEdit(ifds::CountryProvinceUSA, ifds::CountryCode);
   addCrossEdit(ifds::CountryProvinceUSA, ifds::ProvinceCanadaUS);

   _blRetMail = getWorkSession().hasUpdatePermission ( UAF::RETURNED_MAIL_AUTOMATION );
}

//*****************************************************************************
Address::~Address()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}     

//*****************************************************************************
SEVERITY Address::init (const DString &shrNum,
                        const BFData &instData, 
                        const BFData &kanaData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData *data = new BFData (ifds::DSTC0042_VW);

   DString dstrAddressLine;
   dstrAddressLine = kanaData.getElementValue(ifds::AddrLine1);
   data->setElementValue(ifds::kAddrLine1, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddrLine2);
   data->setElementValue(ifds::kAddrLine2, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddrLine3);
   data->setElementValue(ifds::kAddrLine3, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddrLine4);
   data->setElementValue(ifds::kAddrLine4, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddrLine5);
   data->setElementValue(ifds::kAddrLine5, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddressFileVer);
   data->setElementValue(ifds::KAddrFileVer, dstrAddressLine, false, false);
   dstrAddressLine = kanaData.getElementValue(ifds::AddressFileRid);
   data->setElementValue(ifds::KAddrFileRid, dstrAddressLine, false, false);

   Shareholder *pShareholder = NULL;
   DString designation, 
         addressCode;

   if (getWorkSession().getShareholder (BF::HOST, shrNum, pShareholder) <= WARNING &&
      pShareholder)
   {
      pShareholder->getField (ifds::AcctDesignation, designation, BF::HOST);
   }
   designation.strip();
   if (designation == I_("1")) //client
   {
      getField (ifds::AddrCode, addressCode, BF::HOST);
      addressCode.strip();
      if (addressCode == I_("01"))
      {
         setFieldsReadOnly (BF::HOST, true);
         setFieldReadOnly (ifds::kAddrLine1, BF::HOST, true);
         setFieldReadOnly (ifds::kAddrLine2, BF::HOST, true);
         setFieldReadOnly (ifds::kAddrLine3, BF::HOST, true);
         setFieldReadOnly (ifds::kAddrLine4, BF::HOST, true);
         setFieldReadOnly (ifds::kAddrLine5, BF::HOST, true);
      }
   }
   attachDataObject (const_cast<BFData&>(instData), false, true);  //true
   attachDataObject (*data, true, true);
   commonInit (shrNum, BF::HOST);

   initVerifyStatus (BF::HOST, false);

   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY Address::init (
                        const DString &shrNum, 
                        const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   attachDataObject(const_cast<BFData&>(data), false, true);  //true

   if (DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN)
   {
      BFData *data = new BFData (ifds::DSTC0042_VW);
      attachDataObject (*data, true, true);
   }
   commonInit (shrNum, BF::HOST);

   const DSTCSecurity *pSecurity = 
      dynamic_cast<const DSTCSecurity *>(getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()));
   DString dstrCurrentUser = pSecurity->getUserId();
   dstrCurrentUser.strip().upperCase();

   initVerifyStatus (BF::HOST, false);

   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY Address::init ( const DString &shrNum, 
                         const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init")) ;

   setFieldNoValidate(ifds::RetMailFlag,N_STRING,idDataGroup,false);
   commonInit (shrNum, idDataGroup);

   initVerifyStatus (idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY Address::commonInit ( const DString &shrNum,
                               const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init")) ; 
   setFieldNoValidate (ifds::ShrNum, shrNum, idDataGroup, false);
   setReturnedMailFields (idDataGroup);
   setFieldSubstituteValues (ifds::Salutation, idDataGroup, ifds::SalutationSetField);
   setProvinceSubstSet( idDataGroup );
   checkUpdatePermissionForRetmailRelated(idDataGroup);
   setFieldNoValidate (ifds::UpdShrTaxJuris, I_("Y"), idDataGroup, false);
   setFieldNoValidate (ifds::UpdShrProvRes,  I_("Y"), idDataGroup, false);
   setFieldValid (ifds::PostalCode, idDataGroup, true);
   if(isNew())
   {
      setFieldNoValidate(ifds::IsNewOrUpdate, I_("Y"), idDataGroup, false);
   }
   else
   {
      setFieldNoValidate(ifds::IsNewOrUpdate, I_("N"), idDataGroup, false);
   }

   _bIsDirty = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
void Address::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   AddressList *pParent = dynamic_cast<AddressList *>(getParent());

   if (pParent)
   {
      BFObjIter iter (
         *pParent, 
         idDataGroup, 
         true, 
         BFObjIter::ITERTYPE::NON_DELETED);

      int nCount = 0;
      for (iter.begin(); !iter.end(); ++iter)
      {
         nCount++;
         //find the current address in list
         if ((void*) iter.getObject() == (void*) this)
         {
            if (nCount == 1)
            {
               setFieldNoValidate (ifds::AddrCode, I_("01"), idDataGroup);

               AddressList *pParent = dynamic_cast<AddressList*>(getParent());

               if (pParent)
               {
                  pParent->refreshDefaultAddress01 (idDataGroup);
               }
            }
            else if (nCount == 2)
            {
               if (!isClient (idDataGroup))
               {
                  setFieldNoValidate (ifds::AddrCode, I_("02"), idDataGroup);
               }
            }
         }
      }

      DString currBusDate;

      getWorkSession().getMgmtCoOptions()->getField (ifds::CurrBusDate, 
         currBusDate, BF::HOST, false);

      DString effectiveDate (currBusDate);
      DString shrNum;
      Shareholder *pShareholder;

      getField (ifds::ShrNum, shrNum, idDataGroup, false);

      if (getWorkSession().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING && 
            pShareholder && 
            pShareholder->isNew())
      {
         pShareholder->getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
      }
      setFieldNoValidate (ifds::EffectiveDate, effectiveDate , idDataGroup, false, true, true);
      setFieldNoValidate (ifds::Confirm, I_("Y"), idDataGroup);
      setFieldNoValidate (ifds::SkipValidate, I_("0"), idDataGroup);

      DString stopDate;

      getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
      setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );
      setFieldRequired (ifds::AddrLine1, idDataGroup, true);
      if (DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN)
      {
         setFieldRequired (ifds::kAddrLine1, idDataGroup, true);
      }
      setFieldValid (ifds::EffectiveStopDate, idDataGroup, true);
      setFieldNoValidate (ifds::RetMailReasonCode, I_( "" ),idDataGroup, false );
      //clearField(ifds::RetMailReasonCode, idDataGroup);
      setFieldNoValidate (ifds::UnclmComment, NULL_STRING,idDataGroup, false );

      setFieldReadOnly (ifds::RetMailDate, idDataGroup, false );
      setFieldNoValidate (ifds::RetMailDate, I_( "12319999" ) ,idDataGroup, false );
      setFieldReadOnly (ifds::RetMailDate, idDataGroup, true );

      // by default
      // stage stamp
      setFieldNoValidate (ifds::StageStampDate, I_( "12319999" ) ,idDataGroup, false );
      setFieldReadOnly (ifds::StageStampDate, idDataGroup, true );
      // remittance
      setFieldNoValidate (ifds::UnclmRemitDate, I_( "12319999" ) ,idDataGroup, false );
      setFieldReadOnly (ifds::UnclmRemitDate, idDataGroup, true );
      // curator file

      checkUpdatePermissionForRetmailRelated (idDataGroup);
      
      initVerifyStatus (idDataGroup, isNew ());
      _bInit = false;
   }
}

//***************************************************************************************
SEVERITY Address::doValidateField(
                                  const BFFieldId &idField,
                                  const DString &strValue,
                                  const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));

   if (idField == ifds::RegAddrCode)
   {
      validateRegAddressCode (idDataGroup);
   }
   else if (idField == ifds::Address)
   {
      validateAddrLine (idField, strValue, idDataGroup);
   }
   else if (idField == ifds::KanaAddress)
   {
      validateAddrKanaLine (idField, strValue, idDataGroup);
   }
   else if (idField == ifds::EffectiveStopDate)  //cross edit
   {
      DString effectiveDate, 
         stopDate;

      getField (ifds::StopDate, stopDate, idDataGroup, false);
      getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

      if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) 
          == DSTCommonFunctions::FIRST_EARLIER)
      {
         ADDCONDITIONFROMFILE(CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
   }
   else if (idField == ifds::FieldAssignment)
   {
      DString postalCode, 
         countryCode;

      getField (ifds::PostalCode, postalCode, idDataGroup, false);
      getField (ifds::CountryCode, countryCode, idDataGroup, false);     
      if (!postalCode.empty())
      {
         validatePostalCode (postalCode, idDataGroup);
      }
      validateCountryCode (countryCode, idDataGroup);
   }
   else if (idField == ifds::RetMailFlag)
   {
      validateRetMailFlag (strValue, idDataGroup);
   }
   else if (idField == ifds::RetMailDate)
   {
      DString currBusDate, 
         retMailFlag;   

      getField (ifds::RetMailFlag, retMailFlag, idDataGroup, false);
      retMailFlag.strip();
      if (retMailFlag == I_("Y"))
      {
         getWorkSession().getDateInHostFormat (
               currBusDate, 
               DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
               idDataGroup);   
         if (DSTCommonFunctions::CompareDates (strValue, currBusDate) 
               == DSTCommonFunctions::SECOND_EARLIER)
         {
            ADDCONDITIONFROMFILE (CND::ERR_DATE_NUST_BEFORE_CURRBUSDATE);
         }
      }
   }
   
   else if (idField == ifds::CountryCode)
   {
      DString shrNum;

      getField (ifds::ShrNum, shrNum, idDataGroup, false);
      if (Shareholder::shareholderHasPACWithLSIF (
         getWorkSession(), 
         shrNum, 
         idDataGroup))
      {
         ADDCONDITIONFROMFILE (CND::WARN_ENSURE_PAC_IS_ALLOWED);
      }

      DString dstrAddCode, dstrCountryCode(strValue);
      getField( ifds::AddrCode, dstrAddCode, idDataGroup, false);
      if( !dstrAddCode.strip().empty() )
      {
         doResidencyCheck( dstrAddCode, dstrCountryCode.strip(), idDataGroup );
      }
   }

   else if (idField == ifds::RetMailReasonCode)
   {
      DString dstrRetMailFlag;
      getField (ifds::RetMailFlag, dstrRetMailFlag, idDataGroup, false);
      if(strValue.empty() && dstrRetMailFlag == I_("Y") )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RETMAIL_REASON_IS_BLANK);
      }
   }
   else if (idField == ifds::AddrCode)
   {
      DString dstrCountryCode, dstrAddrCode(strValue);
      getField( ifds::CountryCode, dstrCountryCode, idDataGroup, false);
      if( !dstrCountryCode.strip().empty() )
      {
         doResidencyCheck( dstrAddrCode.strip(), dstrCountryCode, idDataGroup );
      }
   }
   else if (idField == ifds::CountryProvinceUSA)
   {
      validateCountryProvinceUSA (idDataGroup);
   }
   else if (idField == ifds::VerifyStat && _bIsDirty && _bVerificationEnabled )
   {
      // make sure that even user who has right to verify can't chanege
      // verify status from verified to unverified by themself
      DString strVerifyStatus;
      getField( ifds::VerifyStat, strVerifyStatus, idDataGroup, false );
      if ( strVerifyStatus == VERIFIED && strValue == UNVERIFIED )
      {
         ADDCONDITIONFROMFILE (CND::ERR_WRONG_VERIFY_STATUS);
      }
   }

// this is for BP server, user should not allowed to change broker address    
// we should have a common mechanism to handle the issue
   if(  bfutil::isServerContext()   )
   {
      if( isRegisterAddressUpdateable( idDataGroup) && ( idField != ifds::TaxType && 
         idField != ifds::BrokerCode &&
         idField != ifds::InterCode ) )
      {  // this fix is ugly I would say, but we have a bad logic in MFAccount
         // when getfield from MFAccount will try to setField to Address and trigger all the
         // validation without the right reason
         // We may go back to revist the whole logic in MFAccount for Nominee account
         // Yingbao 
         // 
        ADDCONDITIONFROMFILE( CND::ERR_REGISTER_ADDRESS_FOR_BROKER_CANNOT_BE_CHANGED );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************

SEVERITY Address::doResidencyCheck( const DString& dstrAddrCode, const DString& dstrCountryCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReturnedMailDate"));
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
      BFCBO* pParent = getParent();
      if (pParent)
      {
         DString accountNum, strShrNum;
         pParent->getField (ifds::AccountNum, accountNum, idDataGroup, false);
         MFAccount *pMFAccount = NULL;
         if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING 
            && pMFAccount && !pMFAccount->isNew()
            && dstrAddrCode == REGISTRATION_ADDRESS )
         {
            pMFAccount->getField( ifds::ShrNum, strShrNum, idDataGroup, false );
            Residency * pResidency;
            if( getWorkSession().getResidencyForShareholder( pResidency, strShrNum, dstrCountryCode, idDataGroup ) <= WARNING && pResidency )
            {
               if( !pResidency->isTaxJurisdictionValid() )
               {
                  getErrMsg ( IFASTERR::NON_RESIDENT_TAX_JURISD_STOP_PAC,
                              CND::ERR_NON_RESIDENT_TAX_JURISD_STOP_PAC,
                              CND::WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC,
                              idDataGroup,
                              NULL_STRING);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY Address::doPreSetField (
         const BFFieldId &idField, 
         DString &value, 
         const BFDataGroupId &idDataGroup, 
         bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doPreSetField"));

   DString strCap;

   if((idField == ifds::Name1) ||  (idField == ifds::Name2) || 
       (idField == ifds::kAddrLine1) || (idField == ifds::kAddrLine2) || (idField == ifds::kAddrLine3)  || 
       (idField == ifds::kAddrLine4) || (idField == ifds::kAddrLine5) ||     
       (idField == ifds::AddrLine1) || (idField == ifds::AddrLine2) || (idField == ifds::AddrLine3)  || 
       (idField == ifds::AddrLine4) || (idField == ifds::AddrLine5) || (idField == ifds::PostalCode) 
       || (idField == ifds::Salutation))
   {
      DString cap;

      getWorkSession().getOption (ifds::CapAddress, cap, BF::HOST, false);
      cap.strip();
      if (cap == I_("Y"))
      {
         value.upperCase();
      }
   }
   if (idField == ifds::PostalCode)
   {
      setPostalCodeFieldValue (value, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************
SEVERITY Address::doApplyRelatedChanges (
                                          const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   DString strCountry, strPostCode;
   DString strPostalCode = I_("");

   if (idField == ifds::CountryCode)
   {
      DString countryCode;
      
      getField (ifds::CountryCode, countryCode, idDataGroup, false);
      setFieldNoValidate (ifds::CountryName, countryCode, idDataGroup, 
         true, true, true);
      doCountryCodeRelatedChanges( idDataGroup);
   }
   else if (idField == ifds::PostalCode)
   {
      DString postalCode;

      getField (ifds::PostalCode, postalCode, idDataGroup, false);
      if (!postalCode.empty())
      {
         if (validatePostalCode (postalCode, idDataGroup, false))
         {
            DString countryCode;

            if (determineCountryCode (countryCode, postalCode, idDataGroup))   // we set countryCode only if it is canada
            {
               setFieldNoValidate (ifds::CountryCode, countryCode, idDataGroup, 
                  true, true, true);
            }
         }
      }
   }
   else if (idField == ifds::RegAddrCode)
   {
      DString strMarket = DSTCommonFunctions::getMarket();

      if (strMarket != MARKET_IDS::JAPAN)
      {
         if (!refreshNomineeInterAddress (idDataGroup))
         {
            setFieldNoValidate (ifds::AddrLine1, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::AddrLine2, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::AddrLine3, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::AddrLine4, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::AddrLine5, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::CountryCode, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::PostalCode, NULL_STRING, idDataGroup, 
               false, false, true);
            setFieldNoValidate (ifds::RegAddrCode, NULL_STRING, idDataGroup, 
               false, false, true);
         }
      }  
   }
   else if (idField == ifds::AddrCode)
   {
      DString addrCode;
      bool bIsNoClient = isNominee (idDataGroup) || isIntermediary (idDataGroup);

      getField(ifds::AddrCode, addrCode, idDataGroup, false);
      addrCode.strip();
      if (addrCode == I_("01") || (addrCode == I_("02") && bIsNoClient))
      {
         if (addrCode == I_("02") && bIsNoClient && IsAddrCodeFirstTimeSetup(addrCode, idDataGroup))
         {
            setNonDummyFlag();
            DString shrNum;

            getField (ifds::ShrNum, shrNum, idDataGroup, false);
            Shareholder* pShareholder = NULL;
            if (getWorkSession().getShareholder (idDataGroup, shrNum, 
                  pShareholder) <= WARNING && 
                pShareholder)
            {
               AccountMailingList *pAccountMailingList = NULL;
               if (pShareholder->getAccountMailingList (pAccountMailingList, 
                        idDataGroup, false) <= WARNING && 
                     pAccountMailingList)
               {
                  DString strKey;

                  BFObjIter iter (
                        *pAccountMailingList, 
                        idDataGroup, 
                        true, 
                        BFObjIter::ITERTYPE::NON_DELETED);

                  iter.begin();
                  if (!iter.end())
                  {
                     AccountMailingInfo* pAccountMailingInfo =  
                           dynamic_cast<AccountMailingInfo*> (iter.getObject());
                     pAccountMailingInfo->setDefaultValue (idDataGroup);
                  }
               }
            }
         }
         else if ( addrCode == I_("01") && !bIsNoClient)
         {
            setFieldsReadOnly (idDataGroup, false);
         }
      }
      setReturnedMailFields (idDataGroup);

      DString dstrAutoRetMail;
      getWorkSession().getOption (ifds::AllowRetMailAutomation, 
         dstrAutoRetMail, idDataGroup, false);
      if (dstrAutoRetMail.stripAll().upperCase() == N_STRING )
      {
         RefreshMailingReturnField(addrCode, idDataGroup);
      }
   }
   else if (idField == ifds::AddrLine1 || 
            idField == ifds::AddrLine2)
   {
      DString dstrAutoRetMail;
      getWorkSession().getOption (ifds::AllowRetMailAutomation, 
         dstrAutoRetMail, idDataGroup, false);

      DString dstrAddressCode;
      getField (ifds::AddrCode, dstrAddressCode, idDataGroup, false);

      if (dstrAutoRetMail.stripAll().upperCase() == Y_STRING &&
          dstrAddressCode.stripAll().upperCase() == I_("01"))
      {
         DString dstrOrigAddrLine, dstrAddrLine;
         getFieldBeforeImage(idField, dstrOrigAddrLine);
         getField(idField, dstrAddrLine, idDataGroup);

         if (dstrOrigAddrLine.stripAll().upperCase() != dstrAddrLine.stripAll().upperCase())
         {
            setFieldNoValidate(ifds::RetMailFlag, N_STRING, idDataGroup);
         }
         else
         {
            DString dstrOrigAddrLine1, dstrOrigAddrLine2, dstrAddrLine1, dstrAddrLine2;
            getFieldBeforeImage(ifds::AddrLine1, dstrOrigAddrLine1);
            getField(ifds::AddrLine1, dstrAddrLine1, idDataGroup);
            getFieldBeforeImage(ifds::AddrLine2, dstrOrigAddrLine2);
            getField(ifds::AddrLine2, dstrAddrLine2, idDataGroup);

            if (dstrOrigAddrLine1.strip().upperCase() == dstrAddrLine1.strip().upperCase() &&
                 dstrOrigAddrLine2.strip().upperCase() == dstrAddrLine2.strip().upperCase())
            {
               DString dstrOrigRetMailFlag, dstrOrigRetMailDate;
               getFieldBeforeImage(ifds::RetMailFlag, dstrOrigRetMailFlag);
               getFieldBeforeImage(ifds::RetMailDate, dstrOrigRetMailDate);

               setField(ifds::RetMailFlag, dstrOrigRetMailFlag.stripAll(), idDataGroup);
               setField(ifds::RetMailDate, dstrOrigRetMailDate.stripAll(), idDataGroup);
            }
         }
      }

      if (dstrAutoRetMail.stripAll().upperCase() == Y_STRING )
      {
         DString dstrOrigAddrLine, dstrAddrLine;
         getFieldBeforeImage(idField, dstrOrigAddrLine);
         getField(idField, dstrAddrLine, idDataGroup);
         //we will not set this flag back if user change addressline back to the same as original.
         if (dstrOrigAddrLine.stripAll().upperCase() != dstrAddrLine.stripAll().upperCase())
         {
            RefreshMailingReturnField(dstrAddressCode, idDataGroup);
         }
      }
   }
   else if (idField == ifds::RetMailFlag)
   {
      DString retMailFlag;

      getField(ifds::RetMailFlag, retMailFlag, idDataGroup, false);
      retMailFlag.stripAll().upperCase();
      DString strOldRetMailFlag;
      getFieldBeforeImage (ifds::RetMailFlag, strOldRetMailFlag);
      if (retMailFlag == I_("N"))
      {
         setFieldNoValidate (ifds::RetMailDate, NULL_STRING, idDataGroup);
         setFieldReadOnly (ifds::RetMailDate, idDataGroup, true);
         setFieldRequired (ifds::RetMailDate, idDataGroup, false);
         setFieldNoValidate (ifds::RetMailReasonCode, I_(""), idDataGroup);
         setFieldValid(ifds::RetMailReasonCode, idDataGroup, false);
         //setFieldNoValidate (ifds::UnclmStmtDate, I_(""), idDataGroup);
         //setFieldNoValidate (ifds::UnclmRemitDate, I_(""), idDataGroup);
         setFieldNoValidate (ifds::UnclmComment,  I_(""),idDataGroup);
         setFieldNoValidate (ifds::UnclmRetMailStage, I_(""), idDataGroup);
         setFieldNoValidate (ifds::StageStampDate, I_(""), idDataGroup);

         if( strOldRetMailFlag == I_("Y") ) // Yes -> No
         {
            //ADDCONDITIONFROMFILE(CND::WARN_APPLICABLE_ACCT_LEVEL_STOP_FLAG_MUST_BE_RELEASED);
            //ADDCONDITIONFROMFILE(CND::WARN_ONHOLD_FLAG_FOR_APPLICABLE_ADDR_MUST_BE_RELEASED);
            //ADDCONDITIONFROMFILE(CND::WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET);

            setFieldNoValidate( ifds::StageAssignBy, I_( "" ), idDataGroup );

            DString dstrAddrCode;
            getField(ifds::AddrCode,dstrAddrCode,idDataGroup,false);
            RefreshMailingReturnField(dstrAddrCode, idDataGroup);
         }
      }
      else
      {
         setFieldReadOnly (ifds::RetMailDate, idDataGroup, !_blRetMail);
         setFieldRequired (ifds::RetMailDate, idDataGroup, _blRetMail);
         setValidFlag (ifds::RetMailDate, idDataGroup, false);

         setFieldValid(ifds::PostalCode, idDataGroup, false);
         //setFieldValid(ifds::CountryName, idDataGroup, false);
         setFieldValid(ifds::CountryCode, idDataGroup, false);
         setFieldValid(ifds::City, idDataGroup, false);
         setFieldValid(ifds::Address,idDataGroup, false);

         DString dstrAddrFormat;
         getWorkSession().getMgmtCoOptions()->getField(ifds::ShrAddressFormat,dstrAddrFormat,idDataGroup);

         if (dstrAddrFormat == I_("02"))
         {
            setFieldValid(ifds::ProvinceCanadaUS, idDataGroup, false);
         }         
         //setFieldValid(ifds::EffectiveStopDate, idDataGroup, false);
         setFieldValid(ifds::AddrCntryCode, idDataGroup, false);
         //setFieldValid(ifds::RegAddrCode, idDataGroup, false);
         setFieldValid(ifds::AddrLine1, idDataGroup, false);
         setFieldValid(ifds::AddrLine2, idDataGroup, false);
         setFieldValid(ifds::AddrLine3, idDataGroup, false);
         setFieldValid(ifds::AddrLine4, idDataGroup, false);
         setFieldValid(ifds::AddrLine5, idDataGroup, false);
         setFieldValid(ifds::ShrAddressFormat, idDataGroup, false);

         if( strOldRetMailFlag == I_("N") ) // No -> Yes
         {
            setFieldReadOnly (ifds::RetMailDate, idDataGroup, false);
            setFieldReadOnly (ifds::RetMailReasonCode, idDataGroup, false);

            setFieldNoValidate (ifds::RetMailReasonCode, I_("UN"), idDataGroup);

            setFieldNoValidate (ifds::UnclmComment, I_(""), idDataGroup,false);
            setFieldNoValidate (ifds::UnclmRetMailStage, I_("S1"), idDataGroup, false);
            setFieldNoValidate (ifds::StageAssignBy, SYSTEM_ASSIGNED, idDataGroup, false );

            DString currBusDate;

            getWorkSession().getMgmtCoOptions()->getField (ifds::CurrBusDate, 
               currBusDate, BF::HOST, false);
            setField(ifds::RetMailDate, currBusDate, idDataGroup, false);

            // because current business date (CurrBusDate from vw#83) is from Controlx.Next-NR
            setFieldNoValidate (ifds::StageStampDate, currBusDate, idDataGroup);

            checkUpdatePermissionForRetmailRelated(idDataGroup);
         }

      }

      DString dstrRetMailUpdt;
      getWorkSession().getOption(ifds::RetMailUpdt, dstrRetMailUpdt, BF::HOST, false);

      if (dstrRetMailUpdt == Y_STRING)
      {
          updateMailingInfoByRetmailForAddrCode(idDataGroup);
      }
   }
   else if (idField == ifds::TaxType)
   {
//reset the updated flag, this is a helper field      
      setFieldUpdated (ifds::TaxType, idDataGroup, false);
   }
   else if (idField == ifds::BrokerCode)
   {
      refreshNomineeInterAddress (idDataGroup);
//reset the updated flag, this is a helper field      
      setFieldUpdated (ifds::BrokerCode, idDataGroup, false);
   }
   else if (idField == ifds::InterCode)
   {
      refreshNomineeInterAddress (idDataGroup);
//reset the updated flag, this is a helper field      
      setFieldUpdated (ifds::InterCode, idDataGroup, false);
   }
   else if (idField == ifds::UnclmRetMailStage)
   {
      //DString dstrUnclmRetMailStage;
      //getField(ifds::UnclmRetMailStage,dstrUnclmRetMailStage, idDataGroup, false);
      //if(dstrUnclmRetMailStage == I_("S3"))
      //{
      //   DString dstrCurrBusDate;
      //   DSTCWorkSession* dstcWorkSession = &(getWorkSession());
      //   dstcWorkSession->getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup,false);
      //   setField(ifds::StageStampDate,dstrCurrBusDate, idDataGroup, false);
      //}
      //else
      //   setField(ifds::StageStampDate,I_(""), idDataGroup, false);

      // if UnclmRetMailStage value change, it would set currBusDate to StageStampDate
      DString dstrCurrBusDate;
      DSTCWorkSession* dstcWorkSession = &(getWorkSession());
      dstcWorkSession->getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup,false);
      setFieldNoValidate (ifds::StageStampDate, dstrCurrBusDate, idDataGroup);
      setFieldNoValidate (ifds::StageAssignBy, USER_OVERRIDEN, idDataGroup);
   }

   if( idField == ifds::PostalCode        ||
       //idField == ifds::CountryName       ||
       idField == ifds::CountryCode       ||
       idField == ifds::City              ||
       idField == ifds::Address           ||
       idField == ifds::ProvinceCanadaUS  ||
       idField == ifds::EffectiveStopDate ||
       idField == ifds::AddrCntryCode     ||
       idField == ifds::RegAddrCode       ||
       idField == ifds::AddrLine1         ||
       idField == ifds::AddrLine2         ||
       idField == ifds::AddrLine3         ||
       idField == ifds::AddrLine4         ||
       idField == ifds::AddrLine5         ||
       idField == ifds::ShrAddressFormat)
   {
      DString dstrRetMailFlag, dstrValue;
      getField(ifds::RetMailFlag, dstrRetMailFlag, idDataGroup);
      getField(idField,dstrValue, idDataGroup);
      
      if( I_("Y") == dstrRetMailFlag && idDataGroup != BF::HOST )
      //if( I_("Y") == dstrRetMailFlag )
      {
         //ADDCONDITIONFROMFILE ( CND::WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET);
         setFieldNoValidate (ifds::RetMailFlag,  I_("N"), idDataGroup);
      }
   }

   verifyStatusRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************
SEVERITY Address::setReturnedMailFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReturnedMailDate"));

   DString addressCode;

   getField (ifds::AddrCode, addressCode, idDataGroup, false);
   addressCode.stripAll();
/*
   if (addressCode != I_("01"))
   {
      setFieldNoValidate (ifds::RetMailFlag, I_("N"), idDataGroup, false);
      setFieldReadOnly (ifds::RetMailFlag, idDataGroup, true);
   }           
   else
   {
*/
   setFieldReadOnly(ifds::RetMailFlag, idDataGroup, !_blRetMail);
   setFieldReadOnly( ifds::StageStampDate, idDataGroup, true);
   setFieldReadOnly( ifds::UnclmRemitDate, idDataGroup, true);
   DString retMailFlag;

   getField(ifds::RetMailFlag, retMailFlag, idDataGroup, false);
   retMailFlag.stripAll().upperCase();
   if (!_blRetMail || I_("N") == retMailFlag)
   {        
      setFieldReadOnly (ifds::RetMailDate, idDataGroup, true);
      if (I_("N") == retMailFlag)
      {
         setFieldNoValidate(ifds::RetMailDate, NULL_STRING, idDataGroup);
      }
   }
   else if (_blRetMail && I_("Y") == retMailFlag)
   {
      setFieldReadOnly (ifds::RetMailDate, idDataGroup, false);
   }
  // }

   DString strGovntStmtDate, strUnknowDate;
   getField(ifds::UnclmStmtDate, strGovntStmtDate, idDataGroup);
   getWorkSession().getDateInHostFormat( strUnknowDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup );

   // curator file date has value, then set comment and remittance date  to be read-only 
   if(  !strGovntStmtDate.strip().empty() &&
         ( DSTCommonFunctions::CompareDates( strUnknowDate , strGovntStmtDate) == 
         DSTCommonFunctions::SECOND_EARLIER )
      )
   {
      setFieldReadOnly( ifds::UnclmComment, idDataGroup, true);
      setFieldReadOnly( ifds::UnclmRemitDate, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY Address::doPreValidateAll (
         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doPreValidateAll"));

   DString addrCode;

   getField (ifds::AddrCode, addrCode, idDataGroup);
   addrCode.strip();
   // if AccountDesgnation is Nominee or Intermediary, stop validation
   if (addrCode == I_("01") && !isClient(idDataGroup))
   {
      setValidFlag (ifds::AddrLine1, idDataGroup, true);
      setFieldValid (ifds::AddrLine1, idDataGroup, true);
      setValidFlag (ifds::AddrLine2, idDataGroup, true);
      setFieldValid (ifds::AddrLine2, idDataGroup, true);
      setValidFlag (ifds::CountryCode, idDataGroup, true);
      setFieldValid (ifds::CountryCode, idDataGroup, true);
      setValidFlag (ifds::PostalCode, idDataGroup, true);
      setFieldValid (ifds::PostalCode, idDataGroup, true);
      /*
      setValidFlag (ifds::CountryName, idDataGroup, true);
      setFieldValid (ifds::CountryName, idDataGroup, true);
      */
   }
   else
   {
      setValidFlag(ifds::AddrLine1, idDataGroup, false);
      setFieldValid (ifds::AddrLine1, idDataGroup, false);
      setValidFlag (ifds::AddrLine2, idDataGroup, false);
      setFieldValid (ifds::AddrLine2, idDataGroup, false);
      setValidFlag (ifds::CountryCode, idDataGroup, false);
      setFieldValid (ifds::CountryCode, idDataGroup, false);
      setValidFlag(ifds::PostalCode, idDataGroup, false);
      setFieldValid (ifds::PostalCode, idDataGroup, false);
      /*
      setValidFlag (ifds::CountryName, idDataGroup, false);
      setFieldValid (ifds::CountryName, idDataGroup, false);
      */


      DString addrFormat,
         country;
      
      getWorkSession().getOption (ifds::EuroAddrFormat, addrFormat, BF::HOST, false);
      getField (ifds::CountryCode, country, idDataGroup);
      country.strip();

      unsigned long val = convertToULong (country);

      if (addrFormat == I_("Y") || val > 12 || val == 0)
      {
         setFieldValid (ifds::PostalCode, idDataGroup, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY Address::validateRegAddressCode (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRegAddressCode"));
   DString regAddrCode,
      addrCode;

   getField (ifds::RegAddrCode, regAddrCode, idDataGroup, false);
   regAddrCode.strip();
   getField (ifds::AddrCode, addrCode, idDataGroup, false);
   addrCode.strip();
   if (!isClient(idDataGroup))
   {
      if (I_("01") != addrCode) // the code is for API
      {
         if (!regAddrCode.empty())
         {
            DString strTemp;
            addIDITagValue (strTemp, I_("ADDRCODE"), addrCode.asInteger());
            ADDCONDITIONFROMFILEIDI (CND::ERR_REG_ADDRESS_CODE_IS_NOT_APPLICABLE_FOR_ADDRESSCODE, addrCode);

         }
      }
      else
      {  
// address code "01" this is for desktop
         NomineeInterAddr* pNomineeInterAddr = NULL; 

         if (getNomineeInterAddress (pNomineeInterAddr, idDataGroup) > WARNING ||
            !pNomineeInterAddr)
         {
            ADDCONDITIONFROMFILE (CND::ERR_REG_ADDRESS_CODE_IS_NOT_AVAILABLE);
         }
      }
   }
   else // the following code is mainly for API, desktop won't not triger the case
   {
      if (!regAddrCode.empty())
      {
         ADDCONDITIONFROMFILE(CND::ERR_REG_ADDRESS_CODE_IS_NOT_BLANK);
      }  
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY Address::validateCountryCode (
         const DString &strValue, 
         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCountryCode"));

   DString addrFormat;
   
   getWorkSession().getOption (ifds::EuroAddrFormat, addrFormat, idDataGroup, false); 
   addrFormat.strip();
   if (addrFormat != I_("Y"))
   {
      if (strValue.length() != 0)//emptyness is checked in other place
      {

         DString strPostalCode;
         DString copyOfCountryCode(strValue);
         getField(ifds::PostalCode, strPostalCode, idDataGroup);
         if(copyOfCountryCode.compare(I_("9999")) == 0)
         {
            ADDCONDITIONFROMFILE(CND::ERR_FEDERAL_NOT_VALID_TAX);
         }
         
         if (!strPostalCode.empty())
         {
            unsigned long val = convertToULong(copyOfCountryCode.strip());
            if((val > 0) && (val < 12) && (copyOfCountryCode != GERMANY))  //only check for canadian provinces
            {                                            // Exclude GERMANY (code = 4 in CountryCodeSet)
               I_CHAR firstLetter = strPostalCode[0];    // in European market GERMANY's postal code is validated as 
                                                         // Canadian province and it it prodeces an error if the postal
                                                         // cod is not of a Canadian format (PTS# 10012589)
               if(!isValidPostalCodeValue(&copyOfCountryCode[0],&firstLetter))
                  ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE_PROVINCE);
            }
            else
            {
               DString dstrFirstThreePostCode(strPostalCode);
               dstrFirstThreePostCode = dstrFirstThreePostCode.left(3).upperCase();
               if(val == 12)
               {
                  if(dstrFirstThreePostCode == I_("X0A") || dstrFirstThreePostCode == I_("X0B") ||
                      dstrFirstThreePostCode == I_("X0C") || strPostalCode[0] != I_('X'))
                  {
                     ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE_PROVINCE);
                  }
               }
               if(val == 13)
               {
                  if(dstrFirstThreePostCode != I_("X0A") && dstrFirstThreePostCode != I_("X0B") &&
                      dstrFirstThreePostCode != I_("X0C"))
                  {
                     ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE_PROVINCE);
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
bool Address::validatePostalCode (
         const DString &strValue, 
         const BFDataGroupId &idDataGroup, 
         bool bAddCondition)
{
   /*the logic for postal-country Code validation is as following :
   - these 2 fields (PostalCode and CountryCode) are in a cross edit (FieldAssignment) because
   we don't know which one is entered first by the user; obviously their validation it is done
   after both fields are entered (or when user hits OK)
   - One BR requires that if the user enetered a postal code, check if it is canadian format,
   and if yes, populate the corresponding CountryCode, if not, don't do anything (for this reason
   I used a bool bAddCondition, as a parameter)
   - Another BR requires if the user enter the Country code, check if PostalCode already entered
   and if yes show an error message if the combination is not valid (done in validateCountryCode)
   - Another BR requires that if the user entered a canadian format postal code and it does not
   have the space in the middle, add it (done in doPresetField) - another reason for bAddCondition
*/
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePostalCode"));


   //if CountryCode is NULL_STRING it wasn't entered yet
   //but if already entered, have to check for canadian province
   //if CountryCode not entered and bAddCondition==true, just return (don't want to show any error messages on this cross edit in this case)
   DString strCountryCode;
   getField(ifds::CountryCode, strCountryCode, idDataGroup);
   if(strCountryCode == NULL_STRING)
   {
      if(bAddCondition)//don't want to add conditions on empty CountryCode
         return(true);
   }
   else
   {
      DString strCopyOfCountryCode(strCountryCode);
      int iCountryCode = strCopyOfCountryCode.stripAll().asInteger();
      //iCountryCode == 0 means 'unassigned'
      strCountryCode.stripAll();
      if((iCountryCode < 1) || (iCountryCode > 13) || (strCountryCode == GERMANY))//not Canadian
         return(true);                                                  // Exclude Germany(TAX) given a 
   }                                                                    // value of 4 in CountryCodeSet(PTS# 10012589)

   DString strAddrFormat;
   getWorkSession().getMgmtCoOptions()->getField(ifds::EuroAddrFormat, strAddrFormat, idDataGroup); 
   strAddrFormat.strip();
   if(strAddrFormat == Y_STRING)
      return(true);

   DString copyOfValue(strValue);
   copyOfValue.strip();
   copyOfValue.upperCase();
   if(copyOfValue.length() == 0) return(false);//emptyness is checked in other place

   if(copyOfValue.length() != 6)
   {
      if(copyOfValue.length() != 7)
      {
         if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);//??
         return(false);
      }
      else
      {
         if(copyOfValue[3] != ' ')
         {
            if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
            return(false);
         }
         else copyOfValue.stripAll();
         if(copyOfValue.length() != 6)
         {
            if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
            return(false);
         }
      }
   }
   //copyOfValue's length is 6
   if(!isValidFirstDigit(copyOfValue[0]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }
   if(!isDigit(copyOfValue[1]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }
   if(!isValidThirdFifthDigit(copyOfValue[2]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }
   if(!isDigit(copyOfValue[3]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }
   if(!isValidThirdFifthDigit(copyOfValue[4]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }
   if(!isDigit(copyOfValue[5]))
   {
      if(bAddCondition) ADDCONDITIONFROMFILE(CND::ERR_INVALID_POSTAL_CODE);
      return(false);
   }

   return(true);
}

//*******************************************************************************************
void Address::validateAddrKanaLine (
         const BFFieldId &idField, 
         DString strLine,
         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddrKanaLine(long,DString,long)"));
   
   DString strMandAddrLines;
   
   getWorkSession().getMgmtCoOptions()->getField (ifds::MandAddLines, strMandAddrLines,BF::HOST);
   
   strMandAddrLines.strip().stripLeading('0');
   if (DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN)
   {
      if (strMandAddrLines == ONE)
      { // 5 lines must be entered
         if((idField==ifds::kAddrLine4) || (idField == ifds::kAddrLine5))
            addAdrressEmptyCondition(strLine);
      }

      else if (strMandAddrLines == TWO)
      { //2 lines must be entered   
         if((getAddressLines(idField,strLine,idDataGroup,true) < 2))
            ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_TWO_LINE);
      }
      else if (strMandAddrLines == THREE)
      { // 1 line must be entered
         if((getAddressLines(idField,strLine,idDataGroup,true) < 1))
            ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_LINE_MISSING);

      }

      SEVERITY sev = GETCURRENTHIGHESTSEVERITY();
      if(sev < WARNING)
      {
         setFieldRequired (ifds::kAddrLine1, idDataGroup, false);
      }
      else 
      {
         setFieldRequired (ifds::kAddrLine1, idDataGroup, true);
      }
   }
}

//*******************************************************************************************
void Address::validateAddrLine (
         const BFFieldId &idField,
         DString strLine,
         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddrLine"));
   DString strMandAddrLines;
   getWorkSession().getMgmtCoOptions()->getField(ifds::MandAddLines,strMandAddrLines,BF::HOST);
   strMandAddrLines.strip().stripLeading('0');
   if(strMandAddrLines == ONE)
   { // 5 lines must be entered
      if((idField==ifds::AddrLine4) || (idField == ifds::AddrLine5))
         addAdrressEmptyCondition(strLine);
   }
   else if(strMandAddrLines == TWO)
   { //2 lines must be entered
      if((getAddressLines(idField,strLine,idDataGroup) < 2))
         ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_TWO_LINE);
   }
   else if(strMandAddrLines == THREE)
   { // 1 line must be entered
      if((getAddressLines(idField,strLine,idDataGroup) < 1))
         ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_LINE_MISSING);
   }
   setFieldRequired(ifds::AddrLine1, idDataGroup, GETCURRENTHIGHESTSEVERITY() >= WARNING);
}

//******************************************************************************
SEVERITY Address::validateRetMailFlag(
      const DString &retMailFlag, 
      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveStopDate"));

   if (I_("Y") == retMailFlag)
   {
      DString autoRetMail;
      getWorkSession().getOption (ifds::AllowRetMailAutomation, 
         autoRetMail, idDataGroup, false);
      
      DString addressCode;
      
      autoRetMail.stripAll().upperCase();
      addressCode.stripAll().upperCase();
      getField (ifds::AddrCode, addressCode, idDataGroup, false); 
      if (autoRetMail == I_("Y") && addressCode == I_("01"))
      {
         DString dstrOrigAddrLine1, 
            dstrOrigAddrLine2, 
            dstrAddrLine1, 
            dstrAddrLine2;

         getFieldBeforeImage (ifds::AddrLine1, dstrOrigAddrLine1);
         getField (ifds::AddrLine1, dstrAddrLine1, idDataGroup);
         getFieldBeforeImage (ifds::AddrLine2, dstrOrigAddrLine2);
         getField (ifds::AddrLine2, dstrAddrLine2, idDataGroup);

         if (dstrOrigAddrLine1.strip().upperCase() != dstrAddrLine1.strip().upperCase() ||
              dstrOrigAddrLine2.strip().upperCase() != dstrAddrLine2.strip().upperCase()) 
         {
            // Address 1 or 2 has been changed, Return Mail flag must be No
            ADDCONDITIONFROMFILE (CND::ERR_RETMAIL_MUST_BE_NO_WHEN_ADDRESS_CHANGED);            
         }
      }
   }
   DString oldRetMail;
   getField( ifds::RetMailFlag,oldRetMail,BF::HOST,false);
   oldRetMail.strip().upperCase();
   if( oldRetMail != retMailFlag )
   {

      SEVERITY svrRet = GETCURRENTHIGHESTSEVERITY();

      if ( svrRet > WARNING )
      {
          CLEARCONDITIONS();
      }

      //ADDCONDITIONFROMFILE(CND::WARN_APPLICABLE_ACCT_LEVEL_STOP_FLAG_MUST_BE_RELEASED);
      //ADDCONDITIONFROMFILE(CND::WARN_ONHOLD_FLAG_FOR_APPLICABLE_ADDR_MUST_BE_RELEASED);
      if(retMailFlag == I_("Y"))
      {
         ADDCONDITIONFROMFILE (CND::WARN_RET_MAIL_CHANGED_CHANGE_HOLD_FLAG);
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET);
         ADDCONDITIONFROMFILE (CND::WARN_RET_MAIL_CHANGED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Address::validateCountryProvinceUSA( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCountryProvinceUSA"));

   DString dstrAddrFormat,
           dstrClosedCountryApplicable,
           dstrProvRes,
           dstrCountryCode;
       
   getWorkSession().getOption(ifds::ShrAddressFormat, dstrAddrFormat, idDataGroup);
   getWorkSession().getOption(ifds::ClosedCountryApplicable, dstrClosedCountryApplicable, idDataGroup, false);
   getField (ifds::ProvinceCanadaUS, dstrProvRes, idDataGroup, false);
   getField (ifds::CountryCode, dstrCountryCode, idDataGroup, false);

   /*
      PET157837 FN02 Country Schedule - If country code is USA and ClosedCountry is applicable.
                                        So, province must be entered.
   */
   if ( dstrAddrFormat == I_("02") && 
        dstrClosedCountryApplicable.strip().upperCase() == YES &&
        dstrCountryCode == USA_COUNTRY &&
        dstrProvRes == NULL_STRING )
   {
      ADDCONDITIONFROMFILE(CND::ERR_PROVINCE_BLANK_FOR_USA);
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************
void Address::addAdrressEmptyCondition(DString strLine)
{   
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addAdrressEmptyCondition"));

   strLine.strip();
   if(strLine == I_(""))
      ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_LINE45);
}

//*******************************************************************
int Address::getAddressLines(const BFFieldId& idField, DString strLine,const BFDataGroupId& idDataGroup,bool bKana)
{
   int   _iLine = 0,iBase= bKana? 5:0;
   DString strAddr;
   strLine.strip();
   const BFFieldId idAddrLine[]=
   {
      ifds::AddrLine1,
      ifds::AddrLine2,
      ifds::AddrLine3,
      ifds::AddrLine4,
      ifds::AddrLine5,  
      ifds::kAddrLine1,
      ifds::kAddrLine2,
      ifds::kAddrLine3,
      ifds::kAddrLine4,
      ifds::kAddrLine5
   };
   DString dstrAddrFormat;
   getWorkSession().getMgmtCoOptions()->getField(ifds::ShrAddressFormat,dstrAddrFormat,idDataGroup);
   dstrAddrFormat.strip();
   int nLines = 5;
   if(dstrAddrFormat == I_("02")) nLines = 4;   
   if(strLine != I_("")) _iLine++;
   for(int i = iBase;i<iBase+nLines;i++)
   {
      if(idField != idAddrLine[i])
      {
         getField(idAddrLine[i],strAddr,idDataGroup);
         strAddr.strip();
         if(strAddr != I_("")) _iLine++;
      }

   }
   return(_iLine);
}

//*******************************************************************
bool Address::isDigit( const I_CHAR val )
{
   if( (val >= I_( '0' ) ) && (val <= I_( '9' ) ) ) 
   {
      return(true);
   }
   return(false);
}

//*******************************************************************
bool Address::isValidFirstDigit( const I_CHAR val )
{
   const I_CHAR firstDigitSet[] = { I_( 'A' ), I_( 'B' ), I_( 'C' ), I_( 'E' ), I_( 'G' ), I_( 'H' ), I_( 'J' ), I_( 'K' ), I_( 'L' ), I_( 'M' ), I_( 'N' ), I_( 'P' ), I_( 'R' ), I_( 'S' ), I_( 'T' ), I_( 'V' ), I_( 'X' ), I_( 'Y' ) };
   for(unsigned int i = 0;  i < ( sizeof(firstDigitSet)/sizeof( firstDigitSet[0])); ++i )
   {
      if(val == firstDigitSet[i]) 
      {
         return(true);
      }
   }
   return(false);
}

//*******************************************************************
bool Address::isValidThirdFifthDigit( const I_CHAR val )
{
   const I_CHAR thirdFifthDigitSet[] = { I_( 'A' ), I_( 'B' ), I_( 'C' ), I_( 'E' ), I_( 'G' ), I_( 'H' ), I_( 'J' ), I_( 'K' ), I_( 'L' ), I_( 'M' ), I_( 'N' ), I_( 'P' ), I_( 'R' ), I_( 'S' ), I_( 'T' ), I_( 'V' ), I_( 'W' ), I_( 'X' ), I_( 'Y' ), I_( 'Z' ) };
   for( unsigned int i = 0; i < ( sizeof( thirdFifthDigitSet ) / sizeof( thirdFifthDigitSet[0] ) ); ++i )
   {
      if(val == thirdFifthDigitSet[i]) return(true);
   }
   return(false);
}
//*******************************************************************
bool Address::isValidPostalCodeValue(I_CHAR* code,I_CHAR* cVal)
{
   int i=0;
   I_CHAR* end = I_("\0");
   DString strCountryCode = code;
   while(*cPostalCode[i]._countryCode != *end)
   {
      if(cPostalCode[i]._countryCode == strCountryCode && *cPostalCode[i]._PostalCode == *cVal)
      {
         return(true);
      }
      i++;
   }
   return(false);
}
//*******************************************************************
void Address::setFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bReadOnly)
{
   setFieldReadOnly(ifds::AddrCode,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Confirm,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrCodeDesc,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Name1,idDataGroup, bReadOnly);
   //setFieldReadOnly(ifds::Name2,idDataGroup, true);//??
   setFieldReadOnly(ifds::AddrLine1,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrLine2,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrLine3,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrLine4,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::AddrLine5,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::PostalCode,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::CountryName,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::CountryCode,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::Salutation,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::EffectiveDate,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::StopDate,idDataGroup, bReadOnly);
}

//*******************************************************************
void Address::setObjectUpdated(const BFDataGroupId& idDataGroup)
{
   setUpdatedFlag(ifds::AddrCode,idDataGroup,true);
}

//-------------------------------------------------------------------------------------
bool Address::IsAddrCodeDuplicated(const DString& strAddrCode, const BFDataGroupId& idDataGroup)
{
   TRACE_METHOD(CLASSNAME, I_("IsAddrCodeDuplicated"));
   bool _bRet = false;
   BFObjIter iterAddrlist(*getParent(), idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);


   DString  addrCode,addrCodekana,addrCodeKana;
   while(!iterAddrlist.end())
   {
      iterAddrlist.getObject()->getField(ifds::AddrCode, addrCode, idDataGroup);
      addrCodeKana = I_("K") + strAddrCode;
      addrCodekana = I_("k") + strAddrCode;
      if(this != iterAddrlist.getObject())
      {
         if((addrCode == strAddrCode) || (addrCode == addrCodeKana) || (addrCode == addrCodekana))
         {
            DString efftDate1,stopDate1,efftDate2,stopDate2;
            iterAddrlist.getObject()->getField(ifds::StopDate, stopDate1, idDataGroup);
            iterAddrlist.getObject()->getField(ifds::EffectiveDate, efftDate1, idDataGroup);
            getField(ifds::EffectiveDate, efftDate2, idDataGroup);
            getField(ifds::StopDate, stopDate2, idDataGroup);
            if(DSTCommonFunctions::dateRangesOverlap(efftDate1,stopDate1,efftDate2,stopDate2))
            {
               _bRet = true;
               break;
            }
         }
      }
      ++iterAddrlist;
   }
   return(_bRet);
}

//***************************************************************************
void  Address::getCountryCodeByPost(DString& countryCode, const DString& strPostCode)
{
   int i = 0;
   I_CHAR* end = I_("\0");
   countryCode = I_("0000");

   DString dstrFirstThreePostCode(strPostCode);
   dstrFirstThreePostCode = dstrFirstThreePostCode.left(3).upperCase();

   if(dstrFirstThreePostCode[0] != 'X')
   {

      while(*cPostalCode[i]._countryCode != *end)
      {

         if(*cPostalCode[i]._PostalCode == dstrFirstThreePostCode[0])
         {
            countryCode = cPostalCode[i]._countryCode;
            break;
         }
         i++;
      }
   }
   else
   {
      if((dstrFirstThreePostCode == I_("X0A")) || (dstrFirstThreePostCode == I_("X0B")) ||
          (dstrFirstThreePostCode == I_("X0C")))
         countryCode = "0013";
      else
         countryCode = "0012";

   }
}
//*****************************************************************************
bool Address::isRegisterAddressUpdateable(const BFDataGroupId& idDataGroup)
{
   bool bRet =  false;
   DString dstrAddr, dstrAcctDes;
   getAccountDesignation( dstrAcctDes,idDataGroup );
   getField(ifds::AddrCode,dstrAddr,BF::HOST,false);
   dstrAddr.strip();
   if( (dstrAcctDes == I_("2") || dstrAcctDes == I_("3")) && dstrAddr == I_("01") && !isNew() )
   {
      bRet = true;   
   }
   return bRet;

}
//-------------------------------------------------------------------------------
bool  Address::determineCountryCode(DString &strCountry, const DString& strPostalCode, const BFDataGroupId& idDataGroup){
   //postal code is already validated (I don't validate it here again)
   //but I still have to check if it is 6 or seven digit long and for the EuropeanAddrFormat NO
   strCountry = NULL_STRING;
   DString strAddrFormat;
   getWorkSession().getMgmtCoOptions()->getField(ifds::EuroAddrFormat, strAddrFormat, idDataGroup); 
   strAddrFormat.strip();
   if(strAddrFormat == Y_STRING)
      return(false);

   if(strPostalCode.length() != 6)
   {
      if(strPostalCode.length() != 7)
      {
         return(false);
      }
      else
      {
         if(strPostalCode[3] != ' ')
         {
            return(false);
         }
      }
   }
// I_CHAR firstDigit;
// firstDigit = strPostalCode[0];   
   getCountryCodeByPost(strCountry, strPostalCode);
   if(strCountry == NULL_STRING)
      return(false);
   return(true);
}
//--------------------------------------------------------------------------------
void Address::setPostalCodeFieldValue(DString &strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPostalCodeFieldValue"));
   //uppercase is already set in doPresetFieldValue
   //check for EuropeAddrFormat-83
   DString strAddrFormat;

   getWorkSession().getMgmtCoOptions()->getField(ifds::EuroAddrFormat,strAddrFormat, BF::HOST,false);
   strAddrFormat.strip();
   if(strAddrFormat == Y_STRING)
      return;

   strValue.stripAll();
   if(strValue.length() == 6)
   {
      if(validatePostalCode(strValue, idDataGroup, false))
         strValue = strValue.left(3) + I_(" ") + strValue.right(3);
   }
}

//*******************************************************************
SEVERITY Address::getAccountDesignation (
                                     DString &acctDesign,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAccountDesignation"));
   DString shrNum;
   Shareholder* pShareholder = NULL;

   getField (ifds::ShrNum, shrNum, idDataGroup, false);
   if ( getWorkSession().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
        pShareholder)
   {
      pShareholder->getField (ifds::AcctDesignation, acctDesign, idDataGroup);
      acctDesign.strip();
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************
bool Address::isClient (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isClient"));
   DString designation;
   getAccountDesignation (designation, idDataGroup);
   return designation == I_("1");
}

//*******************************************************************
bool Address::isNominee (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isNominee"));
   DString designation;
   getAccountDesignation (designation, idDataGroup);
   return designation == I_("2");
}

//*******************************************************************
bool Address::isIntermediary (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isIntermediary"));
   DString designation;
   getAccountDesignation (designation, idDataGroup);
   return designation == I_("3");
}

//***************************************************************************************
SEVERITY Address::getNomineeInterAddress ( NomineeInterAddr *&pNomineeInterAddr,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getNomineeAddress"));

   DString code,
      taxType,
      regAddrCode,
      key;

   if (isNominee (idDataGroup))
   {
      getField (ifds::BrokerCode, code, idDataGroup, false);
   }
   else if (isIntermediary (idDataGroup))
   {
      getField (ifds::InterCode, code, idDataGroup, false);
   }
   getField (ifds::TaxType, taxType, idDataGroup, false);
   getField (ifds::RegAddrCode, regAddrCode, idDataGroup, false);
   key = 
      I_("Code=") + code + 
      I_(";RegAddressCode=") + regAddrCode + 
      I_(";TaxType=") + taxType;
//get what we already have
   pNomineeInterAddr = dynamic_cast<NomineeInterAddr *> (getObject (key, idDataGroup, OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE));
   if (!pNomineeInterAddr)
   {
      NomineeInterAddrList* pNomineeInterAddrList = NULL;
      if (isNominee (idDataGroup))
      {
         BrokerList* pBrokerList = NULL;

         if ( getWorkSession().getBrokerList (pBrokerList) <= WARNING && 
              pBrokerList)
         {   
            Broker *pBroker = NULL;

            if ( pBrokerList->getBroker (code, pBroker) <= WARNING && 
                 pBroker)
            {
               pBroker->getNomineeInterAddressList (idDataGroup, pNomineeInterAddrList);
            }
         }
      }
      else if (isIntermediary (idDataGroup))
      {
         IntermediaryList* pIntermediaryList = NULL;
         
         if (getMgmtCo().getIntermediaryList (pIntermediaryList) <= WARNING &&
            pIntermediaryList)
         {
            Intermediary* pIntermediary = NULL;

            if ( pIntermediaryList->getIntermediary (idDataGroup, code, pIntermediary) && 
                 pIntermediary)
            {
               pIntermediary->getNomineeInterAddressList (idDataGroup, pNomineeInterAddrList);
            }
         }
      }
//if no errors from retrieving the nominee/intermediary address list
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING && pNomineeInterAddrList) 
      {
         if (regAddrCode != NULL_STRING)
         {
            pNomineeInterAddrList->getNomineeAddressByAddrCodeTaxType ( pNomineeInterAddr, 
                                                                        regAddrCode,
                                                                        taxType,
                                                                        idDataGroup);
         }
         else 
         {
            pNomineeInterAddrList->getNomineeAddressByTaxType ( pNomineeInterAddr, 
                                                                taxType,
                                                                idDataGroup);
         }
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING && pNomineeInterAddr) 
         {
            if (regAddrCode == NULL_STRING)
            {
               pNomineeInterAddr->getField (ifds::RegAddrCode, regAddrCode, idDataGroup, false);
               setFieldNoValidate ( ifds::RegAddrCode, 
                                    regAddrCode, 
                                    idDataGroup, 
                                    false,
                                    true,
                                    false,
                                    false);
            }
            key = 
               I_("Code=") + code + 
               I_(";RegAddressCode=") + regAddrCode + 
               I_(";TaxType=") + taxType;
            setObject ( pNomineeInterAddr, 
                        key,  //string key
                        OBJ_ACTIVITY_NONE, 
                        idDataGroup,
                        OBJ_TYPE_NONE,
//tell bfcbo destructor not to delete this object, it doesn't belong to Address
                        BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Address::refreshNomineeInterAddress (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("refreshNomineeInterAddress"));
   NomineeInterAddr *pNomineeInterAddr = NULL;

   bool bVerificationEnabled = false;
   bool bIsNomineeInterAddrValid = false;
   getWorkSession ().isVerificationEnabled (idDataGroup, 
                                            SHRHLDR_CATEGORY, 
                                            SHRHLDR_LEVEL, 
                                            bVerificationEnabled);

   if ( getNomineeInterAddress (pNomineeInterAddr, idDataGroup) <= WARNING &&
        pNomineeInterAddr)
   {
      DString strTemp,
         accountNum,
         addressLine1;
      bool bError = false;
      bIsNomineeInterAddrValid = true;

      AddressList *pParent = dynamic_cast<AddressList*>(getParent());

      if (pParent)
      {
         DString accountNum;

         pParent->getField (ifds::AccountNum, accountNum, idDataGroup, false);
         //here a severity can be raised
         bError = buildAddressLine1 (getWorkSession(), accountNum, addressLine1, idDataGroup) > WARNING;
      }
      pNomineeInterAddr->getField (ifds::Addr11Line1, strTemp, idDataGroup, false);
      if (!bError)
      {
         if (!addressLine1.empty())
         {
            setFieldNoValidate (ifds::AddrLine1, addressLine1, idDataGroup, false, true, true);
//push address line 1 to address line 2, and so on...
//in this case Addr11Line5 does not matter anymore...
            setFieldNoValidate (ifds::AddrLine2, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line2, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine3, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line3, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine4, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line4, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine5, strTemp, idDataGroup, false, true, true);
         }
         else
         {
            setFieldNoValidate (ifds::AddrLine1, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line2, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine2, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line3, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine3, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line4, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine4, strTemp, idDataGroup, false, true, true);
            pNomineeInterAddr->getField (ifds::Addr11Line5, strTemp, idDataGroup, false);
            setFieldNoValidate (ifds::AddrLine5, strTemp, idDataGroup, false, true, true);
         }
//refresh the Name1 - to broker name
         pNomineeInterAddr->getField (ifds::BrokerName, strTemp, idDataGroup, false);
         setFieldNoValidate (ifds::Name1, strTemp, idDataGroup, false, true, true);
         //and the rest of the fields....
         pNomineeInterAddr->getField (ifds::AddrCntryCode, strTemp, idDataGroup, false);
         setFieldNoValidate (ifds::CountryCode, strTemp, idDataGroup, false, true, true);
         pNomineeInterAddr->getField (ifds::PostalCode, strTemp, idDataGroup, false);
         setFieldNoValidate (ifds::PostalCode, strTemp, idDataGroup, false, true, true);
         setFieldsReadOnly (idDataGroup, true);
         setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false, true, true);
      }
   }
   return !!pNomineeInterAddr;
}

//-------------------------------------------------------------------------------------
bool Address::IsAddrCodeFirstTimeSetup(const DString& strAddrCode, const BFDataGroupId& idDataGroup)
{
   TRACE_METHOD(CLASSNAME, I_("IsAddrCodeFirstTimeSetup"));
   bool _bRet = false;

   if(isNew())
   {
      _bRet = true;
      BFObjIter iterAddrlist(*getParent(), idDataGroup, true, BFObjIter::ITERTYPE::ALL);

      DString  addrCode,addrCodekana,addrCodeKana;
      while(!iterAddrlist.end())
      {
         iterAddrlist.getObject()->getField(ifds::AddrCode, addrCode, idDataGroup);
         addrCodeKana = I_("K") + strAddrCode;
         addrCodekana = I_("k") + strAddrCode;
         if(this != iterAddrlist.getObject())
         {
            if((addrCode == strAddrCode) || (addrCode == addrCodeKana) || (addrCode == addrCodekana))
            {
               _bRet = false;
               break;
            }
         }
         ++iterAddrlist;
      }
   }

   return(_bRet);
}

//-------------------------------------------------------------------------------------
void Address::RefreshMailingReturnField(const DString& strAddrCode, const BFDataGroupId& idDataGroup)
{
   TRACE_METHOD(CLASSNAME, I_("RefreshMailingReturnField"));
   if(isNew() /*&& !IsAddrCodeDuplicated(strAddrCode, idDataGroup )*/)
   {
        DString shrNum;

        getField (ifds::ShrNum, shrNum, idDataGroup, false);
        Shareholder* pShareholder = NULL;
        if (getWorkSession().getShareholder (idDataGroup, shrNum, 
                pShareholder) <= WARNING && 
            pShareholder)
        {
            AccountMailingList *pAccountMailingList = NULL;
            if (pShareholder->getAccountMailingList (pAccountMailingList, 
                    idDataGroup, false) <= WARNING && 
                    pAccountMailingList)
            {
                DString strKey;
                
                BFObjIter iter (
                    *pAccountMailingList, 
                    idDataGroup, 
                    true, 
                    BFObjIter::ITERTYPE::NON_DELETED);
                
                iter.begin();
                if (!iter.end())
                {
                    AccountMailingInfo* pAccountMailingInfo =  
                        dynamic_cast<AccountMailingInfo*> (iter.getObject());
                    pAccountMailingInfo->setDefaultValueforReturnMail (strAddrCode, idDataGroup);
                }
            }
        }
   }
}

//******************************************************************************

SEVERITY Address::setProvinceSubstSet(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setProvinceSubstSet"));

   DString dstrProvinceListSubstSet;
   ProvinceList *pProvinceList = NULL;
   if ( getMgmtCo().getProvinceList( I_( "0015,0130"  ), pProvinceList ) <= WARNING && 
        NULL != pProvinceList )
   {
      pProvinceList->getProvinceSubstitutionSet( dstrProvinceListSubstSet, BF::HOST );
   }

   setFieldAllSubstituteValues( ifds::ProvinceCanadaUS, idDataGroup, dstrProvinceListSubstSet );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Address::checkUpdatePermissionForRetmailRelated(const BFDataGroupId & idDataGroup  )
{
   bool bPermit = getWorkSession().hasUpdatePermission( UAF::ADDRESS_BOOK )             && 
                  getWorkSession().hasUpdatePermission( UAF::RETURNED_MAIL_AUTOMATION ) &&
                  getWorkSession().hasUpdatePermission( UAF::UNCLAIM_RETURN_MAIL );

   setFieldReadOnly( ifds::UnclmRetMailStage, idDataGroup, !bPermit );
   // require #1
   setFieldReadOnly( ifds::StageAssignBy, idDataGroup, !bPermit );

   //setFieldReadOnly( ifds::RetMailReasonCode, idDataGroup, !bPermit );
   // comment out until phase 2
   //setFieldReadOnly( ifds::UnclmRemitDate, idDataGroup, !bPermit );

   //DString dstrRemitDate;
   //getField(ifds::UnclmRemitDate, dstrRemitDate, idDataGroup, false);

   //if(dstrRemitDate == I_("12319999") || dstrRemitDate.empty())
   //   setFieldReadOnly(ifds::UnclmStmtDate, idDataGroup, !bPermit);
   //else
      setFieldReadOnly(ifds::UnclmStmtDate, idDataGroup, true );

   //// Read-only status of field StageStampDate depend on user permission
   //setFieldReadOnly( ifds::StageStampDate, idDataGroup, !bPermit );

   return bPermit;
}

//******************************************************************************
SEVERITY Address::doCountryCodeRelatedChanges( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
         CLASSNAME, I_("doCountryCodeRelatedChanges"));
   
   bool bPresentConfirmDlg = false;
   DString strTaxJurisUpdateOpt;
   
   getWorkSession().getOption(ifds::TaxJurisUpdateOpt, strTaxJurisUpdateOpt, 
         idDataGroup, false);

   if(strTaxJurisUpdateOpt == I_("Y"))
   {
      DString strAddrCode;
      DString strResProvCode;
      DString strCountryCode;
      getField(ifds::AddrCode, strAddrCode, idDataGroup, false);
      strAddrCode.strip();
      
      Shareholder *pShareholder = NULL;
      DString dstrShrNum;
      getField(ifds::ShrNum, dstrShrNum, idDataGroup);
      dstrShrNum.strip();
            
      if(getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder) 
               <= WARNING && pShareholder)
      {
         pShareholder->getField(ifds::ResProvCode, strResProvCode, idDataGroup, false);
         getField(ifds::CountryCode, strCountryCode, idDataGroup, false);
         
         if(strCountryCode != strResProvCode)
         {
            if(isClient(idDataGroup))
            {
               bPresentConfirmDlg = (strAddrCode == REGISTRATION_ADDRESS)? true:false;
            }
            //Nominee or Intermediary
            else
            {
               AccountMailingList *pAccountMailingList = NULL;

               if(pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup,false) 
                     <= WARNING && pAccountMailingList)
               {
                  DString strKey;
                  BFObjIter iter(*pAccountMailingList,idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED);
                  iter.begin();
                  if(!iter.end())
                  {
                     DString dstrBenAddr;
                     iter.getObject()->getField(ifds::BenAddr, dstrBenAddr, idDataGroup);
                     bPresentConfirmDlg = (strAddrCode == dstrBenAddr)? true:false;
                  }
               }
            }
         }
      }
      setFieldNoValidate(ifds::IsNewOrUpdate, 
            bPresentConfirmDlg?I_("Y"):I_("N"),idDataGroup,false);
   }

   DString dstrAccountNum;
   MFAccount *pMFAccount = NULL;
   getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   dstrAccountNum.strip ().stripLeading ('0');

   AccountEntityXref *pAccountEntityXref (NULL);		
   WorkSessionEntityList *pWorkSessionEntityList = NULL;
   ENTITIES_VECTOR acctOwnerEntities;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
   {         
	   if (getWorkSession().getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
	   {
		   pAccountEntityXref->getAcctOwnerEntities(acctOwnerEntities, dstrAccountNum, idDataGroup);

		   if( !acctOwnerEntities.size() )
			   return GETHIGHESTSEVERITY();

		   for( ENTITIES_VECTOR::size_type i = 0; i < acctOwnerEntities.size(); ++i )
		   {
			   DString dstrEntityId;
			   Entity *pEntityOut;
			   dstrEntityId = acctOwnerEntities[i];

			   if( pWorkSessionEntityList->getEntity( idDataGroup, dstrEntityId, pEntityOut ) <= WARNING )
			   {
				   pEntityOut->refreshMe(true);
			   }

		   }
	   }
   }

   return GETHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Address::doValidateAll( const BFDataGroupId &idDataGroup, 
                                 long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));


   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA &&
	   getParent() && isUpdatedForDataGroup (idDataGroup) )
   {
	   AddressList *pParent = dynamic_cast<AddressList*>(getParent());

	   DString strTaxJurisUpdateOpt;
   
	   getWorkSession().getOption(ifds::TaxJurisUpdateOpt, strTaxJurisUpdateOpt, idDataGroup, false);
	   strTaxJurisUpdateOpt.strip().upperCase();


	   if( pParent->isAfterPopupTaxJurisUpdate() || (strTaxJurisUpdateOpt != I_("Y")) )
	   {
		   /* Require validation if the address is Beneficiary owner address depend on account designation */
		   if ( isBeneficiaryOwnerAddr(idDataGroup) )
		   {
			   DString dstrAccountNum, dstrTaxJurisUpdateOpt, dstrUpdShrTaxJuris;
			   MFAccount *pMFAccount = NULL;
			   getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
			   dstrAccountNum.strip ().stripLeading ('0');

			   if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) > WARNING )
				   return GETCURRENTHIGHESTSEVERITY ();

			   bool bUpdateShareholder = false;
			   getWorkSession().getOption(ifds::TaxJurisUpdateOpt, dstrTaxJurisUpdateOpt, idDataGroup, false);
			   getField(ifds::UpdShrTaxJuris, dstrUpdShrTaxJuris, idDataGroup, false);

			   /* 
			   If the option is active, depend on users select,
			   If the option is not active, always synch to shareholder.
			   So validation should be kicked in.
			   */
			   if (dstrTaxJurisUpdateOpt == I_("Y"))
				   bUpdateShareholder = dstrUpdShrTaxJuris == I_("Y")? true:false;
			   else
				   bUpdateShareholder = true;

			   if (pMFAccount && bUpdateShareholder)
			   {
				   /*
				   Copy the validations about taxjurisdiction from Account and Shareholder
				   As we are no longer to update the Shareholder tax jurisdiction.
				   */
				   DString dstrTaxJuris, dstrTaxJurisDesc,
					   dstrRecipientType, dstrRecipientTypeDesc,
					   dstrTaxType, dstrShrNum;
				   /*****************************************************************************************
				   // For the address screen, update the country -> update the entity tax and shareholder tax.
				   // So we should check country if it is valid before update the entity and shareholder tax.
				   ******************************************************************************************/
				   getField(ifds::CountryCode, dstrTaxJuris, idDataGroup, false);
				   getField(ifds::CountryCode, dstrTaxJurisDesc, idDataGroup, true);
				   pMFAccount->getField(ifds::RecipientType, dstrRecipientType, idDataGroup, false);
				   pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);	

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
						   getField( ifds::CountryCode, dstrPensionJurisName, idDataGroup, true );
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
				   // Warning Ensure pac is allow whenever change country code already has in this CBO, 
				   // do not need to copy
			   }
		   }
	   }
   }	// Canada Market

   if (!_bVerificationEnabled)
      return GETCURRENTHIGHESTSEVERITY ();

   DString verifyStatus;

   getField (ifds::VerifyStat, verifyStatus, idDataGroup, false);

   if ( verifyStatus== UNVERIFIED)
   {
      //getErrMsg( IFASTERR::SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_TRADE, 
      //           CND::ERR_ADDRESS_NOT_VERIFY, 
      //           CND::WARN_ADDRESS_NOT_VERIFY, 
      //           idDataGroup);
   }
   if (getParent() && !isNew()&& isUpdatedForDataGroup (idDataGroup))   
   {
	DString dstrAccountNum;
	MFAccount *pMFAccount = NULL;
	getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	dstrAccountNum.strip ().stripLeading ('0');
	if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING 
		&& pMFAccount)
	{	
	bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
	pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
	if(bDisplyWarnSICAV)
		ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
	if(bDisplyWarnOEIC)
		ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
	}
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Address::isBeneficiaryOwnerAddr (const BFDataGroupId &idDataGroup)
{
	bool bIsBenOwnerAddr = false;

	DString strAddrCode;
	DString strResProvCode;
	DString strCountryCode;
	getField(ifds::AddrCode, strAddrCode, idDataGroup, false);
	strAddrCode.strip();

	Shareholder *pShareholder = NULL;
	DString dstrShrNum;
	getField(ifds::ShrNum, dstrShrNum, idDataGroup);
	dstrShrNum.strip();

	if(getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder) 
		<= WARNING && pShareholder)
	{
		pShareholder->getField(ifds::ResProvCode, strResProvCode, idDataGroup, false);
		getField(ifds::CountryCode, strCountryCode, idDataGroup, false);

		if(strCountryCode != strResProvCode)
		{
			if(isClient(idDataGroup))
			{
				bIsBenOwnerAddr = (strAddrCode == REGISTRATION_ADDRESS)? true:false;
			}
			//Nominee or Intermediary
			else
			{
				AccountMailingList *pAccountMailingList = NULL;

				if(pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup,false) 
					<= WARNING && pAccountMailingList)
				{
					DString strKey;
					BFObjIter iter(*pAccountMailingList,idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED);
					iter.begin();
					if(!iter.end())
					{
						DString dstrBenAddr;
						iter.getObject()->getField(ifds::BenAddr, dstrBenAddr, idDataGroup);
						bIsBenOwnerAddr = (strAddrCode == dstrBenAddr)? true:false;
					}
				}
			}
		}
	}

	return bIsBenOwnerAddr;
}

//******************************************************************************
SEVERITY Address::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("initVerifyStatus"));

   bool bReadOnly = false;
   DString modUser;

   getField (ifds::VerifyStat, _dstrVerifyStatus, idDataGroup, false);
   getField (ifds::ModUser, modUser, idDataGroup, false);

   modUser.strip().upperCase();

   if (modUser.empty())
   {
      getField (ifds::Username, modUser, idDataGroup, false);
   }

   getWorkSession ().canVerify (idDataGroup, 
                                UAF::SHR_ADDRESS_VERIFICATION, 
                                SHRHLDR_CATEGORY, 
                                SHRHLDR_LEVEL, 
                                modUser, 
                                _bCanVerify);

   getWorkSession ().isVerificationEnabled (idDataGroup, 
                                            SHRHLDR_CATEGORY, 
                                            SHRHLDR_LEVEL, 
                                            _bVerificationEnabled);

   // enviroment level:
   if (_bVerificationEnabled)
   {
      // field level:
      bReadOnly = !_bCanVerify;

      if ( bNew )
      {
         DString strAddrCode;
         getField (ifds::AddrCode, strAddrCode, idDataGroup, false );
         strAddrCode.strip().upperCase();

         if ( isClient(idDataGroup) )
         {
            setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
         }
         else
         {
            if ( strAddrCode == I_("01" ) )
            {
               setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
            }
            else
            {
               setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            }
         }

         bReadOnly = true;
      }
      
      // if data is verified is from backend, lock verify stat
      if ( idDataGroup == BF::HOST )
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
   else
   {
      // enviroment does not support bank verficaiton
      // Verify Status is read only
      // Verify Status on new bank is set to Verified.
      if ( bNew )
      {
         setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
      }

      bReadOnly = true;
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Address::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChanges"));

   bool bFlipFlag = true;

   if (!_bVerificationEnabled || _bInit)
      return GETCURRENTHIGHESTSEVERITY ();

   DString strAddrCode;
   getField (ifds::AddrCode, strAddrCode, idDataGroup, false );
   strAddrCode.strip().upperCase();

   if (idFieldId != ifds::VerifyStat )
   {
      // if data in CBO never changed before
      if ( !_bIsDirty )
      { 
         _bIsDirty = isObjectDirty (idDataGroup);

         if (_bIsDirty && bFlipFlag)
         {
            // All address code of client designation are considered as static data 
            // but exclude address code 01 of nominee or intermediary, therefore
            // set verification status as unverified when there is any change

            if ( isClient(idDataGroup) )
            {
               setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            }
            else
            {
               if ( strAddrCode == I_("01" ) )
               {
                  setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
               }
               else
               {
                  setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
               }
            }

            setValidFlag ( ifds::VerifyStat, idDataGroup, true );
         }
      }
      else
      {
         DString strVerifyStat;
         getField(ifds::VerifyStat,strVerifyStat,idDataGroup,false);

         if ( strVerifyStat == VERIFIED )
         {
            if ( isClient(idDataGroup) )
            {
               setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            }
            else
            {
               if ( strAddrCode == I_("01" ) )
               {
                  setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
               }
               else
               {
                  setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
               }
            }

            setValidFlag ( ifds::VerifyStat, idDataGroup, true );
         }
      }
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, _bIsDirty);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Address::refreshFields( const BFFieldId fieldsArray[], 
                                 int numFields, 
                                 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("refreshFields"));

   // refresh specific field value by write value from getFieldBeforeImage
   for (int i = 0; i < numFields; i++)
   {
      DString strFieldBeforeImage;
      getFieldBeforeImage( fieldsArray[i],strFieldBeforeImage,false);
      
      if ( fieldsArray[i] == ifds::RegAddrCode && 
           strFieldBeforeImage.strip().upperCase().empty() )
      {
         // during NASU value of RegAddrCode returned from getFieldBeforeImage
         // is invalid value therefore acquire correct value from
         // NomineeInterAddr 
         NomineeInterAddr* pNomineeInterAddr = NULL; 

         if ( getNomineeInterAddress (pNomineeInterAddr, idDataGroup) <= WARNING &&
              pNomineeInterAddr )
         {
            pNomineeInterAddr->getField( ifds::RegAddrCode, strFieldBeforeImage, idDataGroup, false ); 
            strFieldBeforeImage.strip().upperCase();
         }
         else
         {
            // broker doesn't exist before, override with '01'
            strFieldBeforeImage = I_("01");
         }
      }

      setFieldNoValidate( fieldsArray[i],strFieldBeforeImage, idDataGroup, false, true, false, false );
   }

   // record is reset then dirty flag must be clear   
   if ( _bIsDirty )
   {
      _bIsDirty = false;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY Address::getFormattedAddress(DString& dstrAddress, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormattedAddress"));

   DString dstrAddrField;
   getField(ifds::AddrLine1, dstrAddrField, idDataGroup);  
   dstrAddress = dstrAddrField.strip();

   getField(ifds::AddrLine2, dstrAddrField, idDataGroup);  
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::AddrLine3, dstrAddrField, idDataGroup);  
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::AddrLine4, dstrAddrField, idDataGroup);
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::AddrLine5, dstrAddrField, idDataGroup);
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::PostalCode, dstrAddrField, idDataGroup);
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += dstrAddrField;

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY Address::updateMailingInfoByRetmailForAddrCode(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateMailingInfoByRetmailForAddrCode"));

	AccountMailingList *pAccountMailingList = NULL;
	Shareholder *pShareholder = NULL;
	DString dstrShrNum, dstrAddrCode, dstrRetMailFlag;

	getField(ifds::AddrCode, dstrAddrCode, idDataGroup);
	getField(ifds::RetMailFlag, dstrRetMailFlag, idDataGroup);
	getField(ifds::ShrNum, dstrShrNum, idDataGroup);
	dstrShrNum.strip();

	if (getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder) <= WARNING && pShareholder &&
		pShareholder->getAccountMailingList(pAccountMailingList, idDataGroup,false) <= WARNING && pAccountMailingList)
	{
		BFObjIter iterAccountMailingList(*pAccountMailingList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

		iterAccountMailingList.begin();
		while (!iterAccountMailingList.end())
		{
			AccountMailingInfo *pAccountMailingInfo = dynamic_cast<AccountMailingInfo*>(iterAccountMailingList.getObject());

			// For Return Mail Flag "NO", the Authorization and Hold Mail field of MailingInfo cbo will be set -
			// "Default" and "NO" only if the original value of Authorization is not "Default".
			if (dstrRetMailFlag == Y)
			{
				pAccountMailingInfo->setHoldFlagForAddrCode(dstrAddrCode, Y, dstrRetMailFlag, idDataGroup);
				pAccountMailingInfo->setAuthorizedFlagForAddrCode(dstrAddrCode, AUTHORIZATION_CODE::RET_MAIL, dstrRetMailFlag, idDataGroup);
			}
			else if (dstrRetMailFlag == N)
			{
				pAccountMailingInfo->setHoldFlagForAddrCode(dstrAddrCode, N, dstrRetMailFlag, idDataGroup);
				pAccountMailingInfo->setAuthorizedFlagForAddrCode(dstrAddrCode, AUTHORIZATION_CODE::DEFAULT, dstrRetMailFlag, idDataGroup);
			}

			++iterAccountMailingList;
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Address.cpp-arc  $
 * 
 *    Rev 1.96   Apr 05 2010 06:29:48   wichian
 * IN#2060041 - Address Code Verify Status
 * 
 *    Rev 1.95   Mar 03 2010 14:42:46   popescu
 * Incident 2033491 - User is able to select Verified or Unverified when hitting RESET - issue fixed for banking/address and distribution
 * 
 *    Rev 1.94   Jan 25 2010 10:51:50   dchatcha
 * IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
 * 
 *    Rev 1.93   Dec 03 2009 03:10:10   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.92   Oct 15 2009 11:33:54   popescu
 * Incident 1848356 - back out the code that sets the province field blank,
 * 
 *    Rev 1.91   Sep 17 2009 10:31:42   jankovii
 * IN 1837022 - Desktop is sending wrong value for SkipValidate during NASU
 * 
 *    Rev 1.90   20 Jul 2009 10:27:26   walkerro
 * PET156681 FN03 - Postal Code lookup enhancement
 * 
 *    Rev 1.89   Jun 09 2009 05:27:58   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.88   Jan 16 2009 09:51:46   jankovii
 * IN 1553375 Registered Address default not found
 * 
 *    Rev 1.87   Dec 30 2008 18:37:02   wongsakw
 * IN1535596 --RL90 - Unclaim Property: Unknown error shows on Address screen
 * 
 *    Rev 1.86   16 Dec 2008 16:51:10   popescu
 * Incident 1514836 - Return Mail Flag Field - do not invalidate ProvinceCanadaUS if address format is 01
 * 
 *    Rev 1.85   16 Dec 2008 16:43:28   popescu
 * Incident 1514836 - Return Mail Flag Field - do not invalidate ProvinceCanadaUS if address format is 01
 * 
 *    Rev 1.84   Nov 19 2008 14:19:10   wongsakw
 * IN1433224 - Changing  desktop warning message when updating address.
 * 
 *    Rev 1.83   Nov 14 2008 01:57:56   sopitwek
 * Unclaimed Property phase1: Comment out statement that set RegAddrCode invalid.
 * 
 *    Rev 1.82   Nov 06 2008 02:14:32   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.81   29 Oct 2008 13:30:46   kovacsro
 * synchup for IN#1461514 - TFSA- chg addr to Non-Res with active pac
 * 
 *    Rev 1.80   Oct 29 2008 21:06:00   wongsakw
 * PET0096390 FN01 Tax Jurisdiction Update
 * 
 *    Rev 1.79   Oct 28 2008 02:37:52   daechach
 * PET5517 FN71 Unclaimed Property Phase 1 , DOD 1.5
 * 
 *    Rev 1.78   Oct 27 2008 23:59:44   daechach
 * IN 1434870 - User s/b be able to flagged '01' address of Nom/Intermediary w/ ret. mail=yes
 * 
 *    Rev 1.77   Oct 14 2008 06:34:48   daechach
 * in# 1440522 - Stage Date for initial notification - Unclaimed Property.
 * 
 *    Rev 1.76   Oct 08 2008 14:58:42   wongsakw
 * IN 1435612 -- Return mail reason should default to 'Unspecified'.
 * 
 *    Rev 1.75   07 Oct 2008 09:53:48   kovacsro
 * PET142007 FN01 TFSA
 * 
 *    Rev 1.74   Sep 29 2008 07:56:30   wongsakw
 * PET5517 FN71 Unclaimed Property - Return Mail
 * 
 *    Rev 1.73   Sep 23 2008 07:19:20   daechach
 * PET5517 FN17 Unclaimed Property
 * 
 *    Rev 1.72   Sep 23 2008 00:23:22   wongsakw
 * PET5517 FN17 Unclaimed Property
 * 
 *    Rev 1.71   Sep 22 2008 08:45:44   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.70   06 Nov 2007 13:40:36   kovacsro
 * IN#1057338 - province CanadaUS substitution set read from view 252 now, rather than the DD
 * 
 *    Rev 1.69   Jul 28 2006 10:42:26   fengyong
 * Incident #672869 - Ret mail flag refresh
 * 
 *    Rev 1.68   Jan 12 2006 15:19:58   popescu
 * Incindent# 494405 - refresh the display of the address information if user changes the broker/branch/slsrep on the account information screen, and the account is either nominee or intermediary
 * 
 *    Rev 1.67   Dec 02 2005 11:32:20   yingbaol
 * Incident 468404: allow user to change return mail flag for any address code.
 * 
 *    Rev 1.66   Sep 21 2005 16:45:10   yingbaol
 * PEt1277,FN09: Investment Fund Continuous Disclosure
 * 
 *    Rev 1.65   Nov 14 2004 14:25:28   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.64   Nov 08 2004 11:30:58   PURDYECH
 * PET910 - Correct parameters for Address::isValidFirstDigit(), Address::isValidPostalCodeValue(), and Address::isValidThirdFifthDigit().
 * 
 *    Rev 1.63   19 Oct 2004 15:36:00   YINGBAOL
 * PET1145: Fix production issue: when user add shareholder remark, raise condition in Address
 * 
 *    Rev 1.62   Oct 04 2004 14:26:30   YINGBAOL
 * PET1145: FN01 Sync. up 1.53.1.1
 * 
 *    Rev 1.61   Jun 23 2004 15:53:24   popescu
 * PTS 10031679, follow the base convention for 'and', change to '&'
 * 
 *    Rev 1.60   Jun 23 2004 15:10:10   popescu
 * PTS 10031679, take into account joint accounts, when constructing address line 1 for nominee/intermediary accounts
 * 
 *    Rev 1.59   Jun 18 2004 17:54:06   popescu
 * PTS 10031514, intermediary account should be part of the address line 1 for accounts with intermediary designation
 * 
 *    Rev 1.58   Jun 01 2004 12:06:28   popescu
 * PTS 10026900, constructed the correct line 1 of the address for Nominee/Intermediary accounts
 * 
 *    Rev 1.57   May 25 2004 22:38:56   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.56   May 25 2004 20:32:08   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.55   May 20 2004 14:16:52   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.54   May 18 2004 17:14:58   popescu
 * PET 985, FN 01, Shareholder Tax Jurisdiction Warning
 * 
 *    Rev 1.53   Mar 17 2004 11:52:16   VADEANUM
 * PTS 10028158 - Return Mail functionality.
 * 
 *    Rev 1.52   Nov 26 2003 16:26:40   YINGBAOL
 * PTS 10021623
 * 
 *    Rev 1.51   Oct 14 2003 11:51:20   HERNANDO
 * PET893 FN08 - Salutation enhancement.
 * 
 *    Rev 1.50   Aug 22 2003 10:26:06   FENGYONG
 * set retmaildate required when retmailflag is true.
 * do not validate retmaildate when retmailfalg is no
 * 
 *    Rev 1.49   Jul 30 2003 11:26:32   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.48   Apr 07 2003 10:24:20   YINGBAOL
 * Fix validateCountryCode
 * 
 *    Rev 1.47   Apr 05 2003 14:54:10   YINGBAOL
 * Fix GerMany(Tax), Manitoba is integer 4 for CountryCode
 * 
 *    Rev 1.46   Apr 04 2003 10:45:26   sanchez
 * Exclude GERMANY (TAX)(code = 4 in th CountryCodeSet) postal code from being validated as a Canadian porvince
 * 
 *    Rev 1.45   Apr 03 2003 16:22:00   YINGBAOL
 * fix
 * 
 *    Rev 1.44   Apr 03 2003 09:25:02   YINGBAOL
 * Broker Address enhancement
 * 
 *    Rev 1.43   Mar 21 2003 17:56:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.42   Feb 27 2003 15:30:46   YINGBAOL
 * this change is help view Jacelin to fix the issue at view side(They need update Account mailing to change effective date at shareholder level)
 * 
 *    Rev 1.41   Feb 26 2003 13:41:10   YINGBAOL
 * fix  issues in  broker address set up
 * 
 *    Rev 1.40   Feb 06 2003 13:44:22   YINGBAOL
 * add city and province and change address lines
 * 
 *    Rev 1.39   Oct 09 2002 23:53:58   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.38   Aug 29 2002 12:54:58   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.37   Aug 06 2002 10:09:46   KOVACSRO
 * PTS 10009253. If acct. des. changes back to 1, enable address 01 fields.
 * 
 *    Rev 1.36   Aug 02 2002 14:42:24   KOVACSRO
 * PTS 10009253 : nominee, inter address changes
 * 
 *    Rev 1.35   Jun 21 2002 11:24:30   HSUCHIN
 * bug fix for unformatting in dopresetfield
 * 
 *    Rev 1.34   24 May 2002 15:05:22   KOVACSRO
 * doPresetField changes.
 * 
 *    Rev 1.33   22 May 2002 18:26:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.32   Feb 13 2002 17:16:12   ZHANGCEL
 * Bug fix for PTS 10007104: Allow user leave PostalCode to be blank.
 * 
 *    Rev 1.31   Jan 23 2002 13:57:48   ZHANGCEL
 * Added logic to set and validate CountryCode and PostalCode for Nunavut
 * 
 *    Rev 1.30   15 Oct 2001 12:02:26   KOVACSRO
 * took out data group from getBroker.
 * 
 *    Rev 1.29   Sep 12 2001 11:20:50   YINGBAOL
 * if countrycode is not Canadian province, postcode is not required 
 * 
 *    Rev 1.28   Jul 23 2001 15:39:18   YINGBAOL
 * sync up version 1.21.1.7 
 * 
 *    Rev 1.27   Jun 05 2001 17:35:00   ZHANGCEL
 * Fixed bugs regarding "EuroAddrFormat"
 * 
 *    Rev 1.26   23 May 2001 16:17:50   SMITHDAV
 * Sync-up fixes.
 * 
 *    Rev 1.25   May 18 2001 13:44:38   ZHANGCEL
 * Added the logic in the PreValidateAll() in order to stop validations when AccountDesgnation is Dominee or Intermediary.
 * 
 *    Rev 1.24   May 15 2001 16:00:58   ZHANGCEL
 * Bug fixed -- setting addrline1 to be REQUIRST only when accountdesgnation is client.
 * 
 *    Rev 1.23   09 May 2001 13:22:38   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.21.1.2   Apr 24 2001 09:34:16   YINGBAOL
 * address is valid if it is copied from broker's address
 * 
 *    Rev 1.21.1.1   12 Apr 2001 14:50:34   KOVACSRO
 * made postal code not required for european market.
 * 
 *    Rev 1.21.1.0   Apr 04 2001 10:18:20   YINGBAOL
 * for European market, PostCode is not required
 * 
 *    Rev 1.21   Mar 29 2001 15:54:32   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.20   19 Mar 2001 11:59:24   BUZILAMI
 * fixed a date formating problem
 * 
 *    Rev 1.19   Feb 14 2001 17:00:32   DINACORN
 * EffectiveDate taken from Shareholder in NASU
 * 
 *    Rev 1.18   Feb 12 2001 14:53:52   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.17   Jan 17 2001 12:08:36   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.16   Dec 17 2000 20:22:24   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.15   Oct 04 2000 16:40:58   KOVACSRO
 * Fixed PostalCode and CountryCode validation.
 * 
 *    Rev 1.14   Sep 29 2000 13:27:08   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.13   Sep 23 2000 11:09:32   YINGBAOL
 * change postcode and country validation to allow free format postcode input for other countries
 * 
 *    Rev 1.12   Sep 15 2000 16:04:00   KOVACSRO
 * added default AddrCode logic.
 * 
 *    Rev 1.11   Sep 06 2000 16:36:34   KOVACSRO
 * changes in checkAccDes()
 * 
 *    Rev 1.10   Aug 23 2000 11:49:08   YINGBAOL
 * let address line validation happan at the end rather than immediate
 * 
 *    Rev 1.9   Aug 21 2000 16:58:30   YINGBAOL
 * fix
 * 
 *    Rev 1.8   Aug 21 2000 11:58:26   YINGBAOL
 * add getCountryCodeByPost and isValidPostalCodeValue method
 * 
 *    Rev 1.7   Aug 15 2000 10:28:06   YINGBAOL
 * fix Nasu and other bugs for C2
 * 
 *    Rev 1.6   Aug 11 2000 14:22:54   KOVACSRO
 * added default broker/interm. address for AccDes 2/ 3, for NASU.
 * 
 *    Rev 1.5   Aug 02 2000 16:59:52   KOVACSRO
 * set address read-only for Acc.Des. 2 and 3, for AddrCode '01'
 * 
 *    Rev 1.4   Jul 18 2000 17:07:44   KOVACSRO
 * displaying Postal Code with a space in the middle, for non european format
 * 
 *    Rev 1.3   Jul 17 2000 16:54:16   KOVACSRO
 * Added some new BR  (validation for Postal Code and Country Code; RegAddress not updatable for Acc. Des. = 2 OR 3)
 * 
 *    Rev 1.2   Jun 06 2000 14:50:18   YINGBAOL
 * change validation for crossedit
 * 
 *    Rev 1.1   Jun 02 2000 16:52:48   YINGZ
 * fix nasu close problem
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.33   Feb 03 2000 10:51:04   BUZILA
 * INIT_TO_DEFAULT flag took out
 * 
 *    Rev 1.32   Feb 01 2000 14:36:24   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.31   Feb 01 2000 14:19:42   YINGBAOL
 * ?
 * 
 *    Rev 1.30   Jan 28 2000 14:44:20   YINGBAOL
 * check in for release
 * 
 *    Rev 1.29   Jan 27 2000 15:19:20   YINGBAOL
 * postcode required
 * 
 *    Rev 1.28   Jan 21 2000 16:44:32   YINGBAOL
 * change the way access other list
 * 
 *    Rev 1.27   Jan 14 2000 15:07:30   YINGBAOL
 * modify validation and default values
 * 
 *    Rev 1.26   Jan 08 2000 14:33:04   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.25   Jan 06 2000 16:55:28   YINGBAOL
 * change default value etc.
 * 
 *    Rev 1.24   Jan 04 2000 12:16:28   BUZILA
 * changes...
 * 
 *    Rev 1.23   Dec 30 1999 10:37:20   YINGBAOL
 * more validation added
 * 
 *    Rev 1.22   Dec 24 1999 11:37:48   WINNIE
 * misc
 * 
 *    Rev 1.21   Dec 22 1999 10:21:14   YINGBAOL
 * 
 *    Rev 1.20   Dec 21 1999 10:13:54   YINGBAOL
 * add validation
 * 
 *    Rev 1.19   Dec 13 1999 16:54:18   WINNIE
 * Add logic to update kana address
 * 
 *    Rev 1.18   Dec 13 1999 10:42:58   YINGBAOL
 * 
 *    Rev 1.17   Dec 12 1999 12:23:24   PRAGERYA
 * modify date
 * 
 *    Rev 1.16   Dec 10 1999 18:10:32   VASILEAD
 * Fixed to compile
 * 
 *    Rev 1.15   Dec 10 1999 17:54:02   YINGBAOL
 * 
 *    Rev 1.14   Dec 10 1999 11:50:30   YINGBAOL
 * add validate
 * 
 *    Rev 1.13   Dec 08 1999 09:37:30   YINGBAOL
 * add validation

  */
