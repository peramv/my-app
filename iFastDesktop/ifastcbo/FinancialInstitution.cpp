//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : FinancialInstitution.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : October 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : FinancialInstitution
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <boost\regex.h>
#include <ifastdataimpl\dse_dstc0100_req.hpp>
#include <ifastdataimpl\dse_dstc0100_vw.hpp>
#include "financialinstitution.hpp"
#include "financialinstitutionlist.hpp"
#include "financialinstitutiontransitlist.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_("FinancialInstitution");
   const I_CHAR * OTHER = I_("07");
   const I_CHAR * INACTIVE = I_("0");
   const I_CHAR * ACTIVE = I_("1");
   const I_CHAR * EXTERNAL = I_("0");
   const I_CHAR * INTERNAL = I_("1");
   const I_CHAR * JIS = I_("0");
}

namespace CND
{  // Conditions used
}

namespace ifds
{
   //field ids used
   //search criteria subst sets
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchCriteria;
   extern CLASS_IMPORT const BFDecimalFieldId BankValid1;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId TransitsCategory;
   extern CLASS_IMPORT const BFTextFieldId InstCodeLabel;
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsCodeLabel;
   extern CLASS_IMPORT const BFTextFieldId InstPrimaryKey;   
}

namespace CND
{
   extern const long ERR_INSTCODE_TOO_BIG;
   extern const long ERR_INSTCODE_NUMERIC;
   extern const long ERR_INSTCODE_NOT_EXIST;
   extern const long ERR_TRANSITNO_TOO_BIG;
   extern const long ERR_TRANSITNO_NUMERIC;
   extern const long ERR_TRANSITNO_NOT_EXIST;
}

namespace FI_CATEGORY
{
   extern CLASS_EXPORT I_CHAR * const BANK = I_("01");
   extern CLASS_EXPORT I_CHAR * const BANK_TRANSIT = I_("02");
   extern CLASS_EXPORT I_CHAR * const INSTITUTION = I_("03");
   extern CLASS_EXPORT I_CHAR * const INSTITUTION_TRANSIT = I_("04");
   extern CLASS_EXPORT I_CHAR * const OTHER = I_("05");

}

extern BF_OBJ_TYPE OBJ_TYPE_TRANSITS_LIST;

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                           //  Field DD Id            State Flags,      Group Flags 
   {ifds::FITransitCode,    BFCBO::NONE,      0}, //part of the key if a transit
   {ifds::Name,             BFCBO::NONE,      0}, 
   {ifds::SwiftCode,        BFCBO::NONE,      0}, 
   {ifds::RefNumber,        BFCBO::NONE,      0}, 
   {ifds::BranchName,       BFCBO::NONE,      0}, 
   {ifds::BankIdNum,        BFCBO::REQUIRED,  0}, //part of the key
   {ifds::BankAddr1,        BFCBO::NONE,      0}, 
   {ifds::BankAddr2,        BFCBO::NONE,      0}, 
   {ifds::BankAddr3,        BFCBO::NONE,      0}, 
   {ifds::BankAddr4,        BFCBO::NONE,      0}, 
   {ifds::BankAddr5,        BFCBO::NONE,      0}, 
   {ifds::BankContact,      BFCBO::NONE,      0}, 
   {ifds::BankCountry,      BFCBO::REQUIRED,  0}, 
   {ifds::BankPostal,       BFCBO::NONE,      0}, 
   {ifds::BankId,           BFCBO::NONE,      0}, 
   {ifds::Telex,            BFCBO::NONE,      0}, 
   {ifds::FaxNumber,        BFCBO::NONE,      0}, 
   {ifds::PhoneNumber,      BFCBO::NONE,      0}, 
   {ifds::ShortName,        BFCBO::NONE,      0}, 
   {ifds::InstRole,         BFCBO::NONE,      0}, 
   {ifds::CodePage,         BFCBO::NONE,      0}, 
   {ifds::FIStatusCode,     BFCBO::NONE,      0}, 
   {ifds::BankIdType,       BFCBO::REQUIRED,  0}, //part of the key
   {ifds::InstCategory,     BFCBO::REQUIRED,  0}, //part of the key
   {ifds::FinancialYearEnd, BFCBO::NONE,      0}, 
   {ifds::InstCodeLabel,    BFCBO::NONE,      0}, 
   //cross edits
   {ifds::InstPrimaryKey,  BFCBO::IMMEDIATE_VALIDATION, 0}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

struct _FITypeInfo
{
   const I_CHAR* _category;
   const I_CHAR* _typeId;
   int  _nFIIdLength;
   bool _bFIIdAllDigits;
   int  _nTransitLength;
   bool _bTransitAllDigits;
   int  _nFIAccLengthforCanada;
   int  _nFIAccLengthforLux;
   bool _bFIAccAllDigits;
};

const struct _FITypeInfo m_objFITypeInfo[] = 
{
   FI_CATEGORY::BANK,            I_("01"),  9, true ,  0, false, 12, 35, false, //ABA (US)
   FI_CATEGORY::BANK,            I_("02"),  5, true ,  0, false, 12, 35, false, //Austria
   FI_CATEGORY::BANK,            I_("03"),  3, true ,  5, true , 12, 35, false, //Canadian
   FI_CATEGORY::BANK,            I_("04"), 11, false,  0, false, 12, 35, false, //SWIFT
   FI_CATEGORY::BANK,            I_("05"),  8, true ,  0, false, 12, 35, false, //Germany
   FI_CATEGORY::BANK,            I_("06"),  4, true ,  3, true ,  7, 35, false, //Japanese
   FI_CATEGORY::BANK,            I_("07"), 12, false,  0, false, 12, 35, false, //Other
   FI_CATEGORY::BANK,            I_("08"),  6, true ,  0, false, 12, 35, false, //UK
   FI_CATEGORY::BANK,            I_("09"),  6, true ,  0, false, 6, 35, false, //HongKong
   FI_CATEGORY::BANK,            I_("10"),  6, true ,  0, true,  16, 35, true,  //Switzerland
	// PET 2132 - MFS BAFF File Changes
	FI_CATEGORY::BANK,            I_("11"), 11, false , 0, false, 12, 23, false, //BIC
   FI_CATEGORY::BANK,            I_("12"),  9, true ,  0, false, 12, 23, false, //CC
   FI_CATEGORY::BANK,            I_("13"),  6, true ,  0, false, 12, 6,  true,  //CH
   FI_CATEGORY::BANK,            I_("14"),  4, true ,  0, false, 12, 23, false, //CP
   FI_CATEGORY::BANK,            I_("15"),  9, true ,  0, false, 12, 23, false, //FW
   FI_CATEGORY::BANK,            I_("16"),  4, false , 0, false, 12, 23, false, //NA
   FI_CATEGORY::BANK,            I_("17"),  10, true , 0, false, 12, 23, false, //SC
   FI_CATEGORY::BANK,            I_("18"),  6, true ,  0, false, 12, 23, false, //SW
   FI_CATEGORY::BANK,            I_("19"),  8, true ,  0, false, 12, 23, false, //BL 

   FI_CATEGORY::OTHER,           I_("07"), 35, false, 35, false, 16, 35, false, //Other 'Institution'
   FI_CATEGORY::INSTITUTION,     I_("07"), 35, false, 35, false, 16, 35, false, //Financial Institution
   FI_CATEGORY::BANK,            I_("20"),  7, true ,  0, false, 7, 35, false, //singapore

   FI_CATEGORY::BANK,            I_("21"),  7, false ,  0, false, 12, 10, false, //BSB-Australia
};

static const int _numFIsInFITypeInfo = sizeof(m_objFITypeInfo) / sizeof(_FITypeInfo);

//static methods on the FI type info structure
//******************************************************************************
bool FinancialInstitution::getFICodeNumInfo (
   const DString &dstrCategory, 
   const DString &dstrType, 
   int &nFIIdMaxLength, 
   bool &bIsAllDigits, 
   int &nAllFIIdMaxLength)
{
   bool retVal = false;
   int nFIIdMaxLengthTemp = 0;

   nAllFIIdMaxLength = 0;
   for (int i = 0; i<_numFIsInFITypeInfo; i++)
   {
      if (dstrCategory == m_objFITypeInfo[i]._category)
      {
         nFIIdMaxLengthTemp = m_objFITypeInfo[i]._nFIIdLength;
         if (m_objFITypeInfo[i]._typeId == dstrType)
         {
            nFIIdMaxLength = nFIIdMaxLengthTemp;
            bIsAllDigits = m_objFITypeInfo[i]._bFIIdAllDigits;
            retVal = true;
         }
         if (nAllFIIdMaxLength < nFIIdMaxLengthTemp)
         {
            nAllFIIdMaxLength = nFIIdMaxLengthTemp;
         }
      }
   }
   return retVal;
}

//******************************************************************************
bool FinancialInstitution::getBankIdNumInfo (
   const DString &dstrType, 
   int &nBankIdMaxLength, 
   bool &bIsAllDigits, 
   int &nAllFIIdMaxLength)
{
   return getFICodeNumInfo (FI_CATEGORY::BANK, dstrType, nBankIdMaxLength, 
      bIsAllDigits, nAllFIIdMaxLength);
}

//******************************************************************************
bool FinancialInstitution::getFITransitNumInfo (
   const DString &dstrCategory, 
   const DString &dstrType, 
   int &nTransitMaxLength, 
   bool &bIsAllDigits, 
   int &nAllTransitMaxLength)
{
   bool retVal = false;
   int nTransitMaxLengthTemp = 0;

   nAllTransitMaxLength = 0;
   for (int i = 0; i < _numFIsInFITypeInfo; i++)
   {
      if (dstrCategory == m_objFITypeInfo[i]._category)
      {
         nTransitMaxLengthTemp = m_objFITypeInfo[i]._nTransitLength;
         if (m_objFITypeInfo[i]._typeId == dstrType)
         {
            nTransitMaxLength = nTransitMaxLengthTemp;
            bIsAllDigits = m_objFITypeInfo[i]._bTransitAllDigits;
            retVal = true;
         }
         if (nAllTransitMaxLength < nTransitMaxLengthTemp)
         {
            nAllTransitMaxLength = nTransitMaxLengthTemp;
         }
      }
   }
   return retVal;
}

//******************************************************************************
bool FinancialInstitution::getBankTransitNumInfo (
   const DString &dstrType, 
   int &nTransitMaxLength, 
   bool &bIsAllDigits, 
   int &nAllTransitMaxLength)
{
   return getFITransitNumInfo (FI_CATEGORY::BANK, dstrType, nTransitMaxLength, 
      bIsAllDigits, nAllTransitMaxLength);
}

//******************************************************************************
bool FinancialInstitution::hasTransits (
   const DString &dstrCategory, 
   const DString &dstrType)
{
   bool bHasTransit = false;
   int nTransitMaxLength = -1,
      nAllTransitMaxLength = -1;
   bool bIsAllDigits = false; 

   assert (dstrCategory == FI_CATEGORY::BANK ||
      dstrCategory == FI_CATEGORY::INSTITUTION ||
      dstrCategory == FI_CATEGORY::OTHER);

   return getFITransitNumInfo (dstrCategory, dstrType, 
      nTransitMaxLength, bIsAllDigits, nAllTransitMaxLength) && 
      nTransitMaxLength > 0;
}

//******************************************************************************
bool FinancialInstitution::getFIAccNumInfo (
   const DString &dstrCategory, 
   const DString &dstrType, 
   int &nAccountMaxLength, 
   bool &bIsAllDigits, 
   int &nAllAccountMaxLength)
{
   bool retVal = false;
   int nAccountMaxLengthTemp = 0;

   nAllAccountMaxLength = 0;
   for (int i = 0; i < _numFIsInFITypeInfo; i++)
   {
      if (dstrCategory == m_objFITypeInfo[i]._category)
      {
         if (DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
         {
            nAccountMaxLengthTemp = m_objFITypeInfo[i]._nFIAccLengthforLux;
         }
         else
         {
            nAccountMaxLengthTemp = m_objFITypeInfo[i]._nFIAccLengthforCanada;
         }
         if (m_objFITypeInfo[i]._typeId == dstrType)
         {
            nAccountMaxLength = nAccountMaxLengthTemp;
            bIsAllDigits = m_objFITypeInfo[i]._bFIAccAllDigits;
            retVal = true;
         }
         if (nAllAccountMaxLength < nAccountMaxLengthTemp)
         {
            nAllAccountMaxLength = nAccountMaxLengthTemp;
         }
      }
   }
   return retVal;
}

//******************************************************************************
bool FinancialInstitution::getBankAccNumInfo (
   const DString &dstrType, 
   int &nAccountMaxLength, 
   bool &bIsAllDigits, 
   int &nAllAccountMaxLength)
{
   return getFIAccNumInfo (FI_CATEGORY::BANK, dstrType, nAccountMaxLength, 
      bIsAllDigits, nAllAccountMaxLength);
}

//******************************************************************************
SEVERITY FinancialInstitution::validateFICode (
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrCode)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFICode"));

   DString category(dstrCategory),
      type(dstrType),
      code(dstrCode);

   category.stripAll().upperCase();
   type.stripAll().upperCase();
   code.stripAll().upperCase();

   int nFIIdMaxLength = -1;
   int nAllFIIdMaxLength = -1;
   bool bIsAllDigits = false;

   if (getFICodeNumInfo (category, type, nFIIdMaxLength, 
      bIsAllDigits, nAllFIIdMaxLength))
   {
      // TODO: nFIIdMaxLength uses -1, but length() returns -1 (or actually 0xffffffff) as 
      // the 'nothing'
      if ((int)code.length() > nFIIdMaxLength)
      {
         ADDCONDITIONFROMFILE (CND::ERR_INSTCODE_TOO_BIG);
      }
      else if (bIsAllDigits && !code.isAllDigits())
      {
         ADDCONDITIONFROMFILE (CND::ERR_INSTCODE_NUMERIC);
      }
   }
   else
   {
      //FI info not found for this category and type; add FI info 
      assert (0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::validateBankCode(DSTCWorkSession &workSession,
   const DString &dstrType, const DString &dstrCode)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBankCode"));

   if (validateFICode (FI_CATEGORY::BANK, dstrType, dstrCode) <= WARNING)
   {
      //an extra check should be made
      DString dstrBankValid1;

      //Bank validation is needed (make view call 100) only if this field is equal '3'
      workSession.getOption (ifds::BankValid1, dstrBankValid1, BF::HOST, false);
      if (dstrBankValid1.strip() == I_("3"))
      {
         FinancialInstitutionList fiSearch (workSession);
         bool bRecordExists = fiSearch.init (FI_CATEGORY::BANK, dstrType, 
            dstrCode, I_("N"), NULL_STRING) <= WARNING;

         if (bRecordExists)
         {
            BFObjIter bfIter (fiSearch, BF::HOST);

            bfIter.begin();
            bRecordExists = !bfIter.end();
         }
         if (!bRecordExists)
         {
            ADDCONDITIONFROMFILE (CND::ERR_INSTCODE_NOT_EXIST);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FinancialInstitution::validateFITransitNum (
   const DString &dstrCategory,
   const DString &dstrType, 
   const DString &dstrTransitNo)
{ 
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransitNo"));

   int nTransitMaxLength = -1;
   int nAllTransitMaxLength = -1;
   bool bIsAllDigits = false;
   
   DString category (dstrCategory),
      type(dstrType),
      transitNo(dstrTransitNo);

   category.stripAll().upperCase();
   type.stripAll().upperCase();
   transitNo.stripAll().upperCase();

   bool bNotEmpty = !category.empty() && !type.empty();

   if (bNotEmpty && 
      getFITransitNumInfo (category, type, 
         nTransitMaxLength, bIsAllDigits, nAllTransitMaxLength))
   {
      // TODO nTransitLength being -1 is problematic
      if ((int)transitNo.length() > nTransitMaxLength)
      {
         ADDCONDITIONFROMFILE (CND::ERR_TRANSITNO_TOO_BIG);
      }
      else if (bIsAllDigits && !transitNo.isAllDigits())
      {
         ADDCONDITIONFROMFILE (CND::ERR_TRANSITNO_NUMERIC);
      }
   }
   else if (bNotEmpty)
   {
      //FI info not found for this category and type; add FI info 
      assert (0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::validateBankTransitNum (DSTCWorkSession &workSession,
   const DString &dstrType, 
   const DString &dstrCode, 
   const DString &dstrTransitNo)
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransitNo"));
   DString type (dstrType),
      code (dstrCode),
      transitNo (dstrTransitNo);

   type.stripAll().upperCase();
   code.stripAll().upperCase();
   transitNo.stripAll().upperCase();
   if (validateFITransitNum (FI_CATEGORY::BANK, type, transitNo) <= WARNING)
   {
      //an extra check to be made
      DString dstrBankValid1;

      //Bank validation is needed (make view call 100) only if this field is equal '3'
      workSession.getOption(ifds::BankValid1, dstrBankValid1, BF::HOST, false);
      if (dstrBankValid1.strip() == I_("3"))
      {
         FinancialInstitutionTransitList transitSearch (workSession);
         bool bRecordExists = transitSearch.init (FI_CATEGORY::BANK_TRANSIT, type, 
            code, transitNo, I_("N"), NULL_STRING) <= WARNING;

         if (bRecordExists)
         {
            BFObjIter bfIter (transitSearch, BF::HOST);

            bfIter.begin();
            bRecordExists = !bfIter.end();
         }
         if (!bRecordExists)
         {
            ADDCONDITIONFROMFILE (CND::ERR_TRANSITNO_NOT_EXIST);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FinancialInstitution::institution (const DString &dstrCategory)
{
   return dstrCategory == FI_CATEGORY::BANK ||
      dstrCategory == FI_CATEGORY::INSTITUTION ||
      dstrCategory == FI_CATEGORY::OTHER;
}

//******************************************************************************
bool FinancialInstitution::transit (const DString &dstrCategory)
{
   return dstrCategory == FI_CATEGORY::BANK_TRANSIT ||
      dstrCategory == FI_CATEGORY::INSTITUTION_TRANSIT;
}

//******************************************************************************
DString FinancialInstitution::getParentCategory (const DString &category)
{
   DString parentCategory (category);

   if (category == FI_CATEGORY::BANK_TRANSIT)
   {
      parentCategory = FI_CATEGORY::BANK;
   }
   else if (category == FI_CATEGORY::INSTITUTION_TRANSIT)
   {
      parentCategory = FI_CATEGORY::INSTITUTION;
   }
   return parentCategory;
}


//******************************************************************************
FinancialInstitution::FinancialInstitution (BFAbstractCBO &parent) : 
   MFCanBFCbo(parent),
_initCategory (NULL_STRING),
_initType (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   addCrossEdit (ifds::InstPrimaryKey, ifds::BankIdNum);
   addCrossEdit (ifds::InstPrimaryKey, ifds::BankIdType);
}

//******************************************************************************
FinancialInstitution::~FinancialInstitution()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FinancialInstitution::init ( 
   const DString &initCategory, 
   const DString &initType, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _initCategory = initCategory;
   _initType = initType;
   commonInit (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject(const_cast<BFData&>(viewData), false, true);
   commonInit (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::commonInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   bool keyFieldsReadOnly = idDataGroup == BF::HOST && !isNew();
   
   setFieldReadOnly (ifds::InstCategory, idDataGroup, keyFieldsReadOnly);
   setFieldReadOnly (ifds::BankIdNum, idDataGroup, keyFieldsReadOnly); 
   setFieldReadOnly (ifds::BankIdType, idDataGroup, keyFieldsReadOnly); 
   setFieldReadOnly (ifds::FITransitCode, idDataGroup, keyFieldsReadOnly);

   DString financialYearEnd;

   getField (ifds::FinancialYearEnd, financialYearEnd, 
      idDataGroup, false);
   if (financialYearEnd.stripAll () == NULL_STRING)
   {
      getWorkSession ().getDateInHostFormat (financialYearEnd, 
         DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
      setFieldNoValidate (ifds::FinancialYearEnd, financialYearEnd, idDataGroup, 
         false, true, true);
   }
   assignInstCodeLabel (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FinancialInstitution::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   if (_initCategory != NULL_STRING)
   {
      setFieldNoValidate (ifds::InstCategory, _initCategory, idDataGroup, false);
   }
   else 
   {
      setFieldNoValidate (ifds::InstCategory, FI_CATEGORY::BANK, idDataGroup, false);
   }
   if (_initType != NULL_STRING) //forget about InstCategory doApplyRelatedChanges
   {
      setFieldNoValidate (ifds::BankIdType, _initType, idDataGroup, false);
   }
   setFieldNoValidate (ifds::InstRole, EXTERNAL, idDataGroup, false);
   setFieldNoValidate (ifds::FIStatusCode, ACTIVE, idDataGroup, false);
   setFieldNoValidate (ifds::CodePage, JIS, idDataGroup, false);
}

//******************************************************************************
SEVERITY FinancialInstitution::doApplyRelatedChanges (const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::InstCategory)
   {
      DString category;

      getField (ifds::InstCategory, category, idDataGroup, false);
      if (category == FI_CATEGORY::BANK)
      {
         //try to set the default bank type, based on the system configuration            
         DString defaultBankType;

         getWorkSession().getOption (ifds::DefaultBankType, defaultBankType, 
            BF::HOST, false);
         if (!defaultBankType.empty())
         {
            setFieldNoValidate (ifds::BankIdType, 
               defaultBankType, idDataGroup, false);
         }
         setFieldReadOnly (ifds::BankIdType, idDataGroup, false);
      }
      else if (category == FI_CATEGORY::INSTITUTION ||
         category == FI_CATEGORY::OTHER)
      {
         setFieldNoValidate (ifds::BankIdType, 
            OTHER, idDataGroup, false);
         setFieldReadOnly(ifds::BankIdType, idDataGroup, true);
      }
   }
   else if (idField == ifds::BankIdType)
   {
      DString category, 
         type;

      getField (ifds::InstCategory, category, idDataGroup, false);
      getField (ifds::BankIdType, type, idDataGroup, false);
      //look whether we support transits
      setFieldReadOnly (ifds::FITransitCode, idDataGroup, 
         FinancialInstitution::hasTransits (category, type));
      assignInstCodeLabel (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::doValidateField (const BFFieldId &idField, 
   const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::InstPrimaryKey)
   {
      //check duplicate
      FinancialInstitutionList *pFinancialInstitutionList = 
         dynamic_cast<FinancialInstitutionList*>(getParent());
      
      pFinancialInstitutionList->checkDuplicate (this, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitution::assignInstCodeLabel (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("FinancialInstitution"));
      
   setFieldNoValidate (ifds::InstCodeLabel, NULL_STRING, 
      idDataGroup, false, true, false);

   DString type,
      values;

   BFProperties *pProperties = getFieldProperties (
      ifds::FinancialInstitutionsCodeLabel, 
      idDataGroup);
   
   pProperties->getAllSubstituteValues (values);
   getField (ifds::BankIdType, type, idDataGroup, false);

   I_CHAR *temp = const_cast<I_CHAR*> (values.c_str ());

   do
   {
      DString fullLabelCode;
      DString labelDescription;

      temp = parseIdiString (temp, fullLabelCode, labelDescription);
      
      DString::size_type labelPos = fullLabelCode.find (type);

      if (labelPos != DString::npos)
      {
         setFieldNoValidate (ifds::InstCodeLabel, labelDescription, 
            idDataGroup, false, true, true);
         break;
      }
   } while (temp && temp != NULL_STRING && *temp);
   //do not need to trigger transaction updates if this field is changed
   setFieldUpdated (ifds::InstCodeLabel, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool FinancialInstitution::validatePreformatted(const DString &dstrType,const DString &dstrBankIdValue)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validatePreformatted"));
	
	bool bMatch = true;
	if (dstrType == I_("21"))
	{
		boost::RegEx rgVal("[0-9]{3}-[0-9]{3}");
        DStringA straVal(dstrBankIdValue);
        bMatch = rgVal.Match(straVal.c_str());
	}

	return bMatch;
}
bool FinancialInstitution::validateAcctNbrformatted(const DString &dstrType,const DString &dstrCurrency,const DString &dstrBankAcctValue)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateAcctNbrformatted"));

	bool bMatch = true;
	if (dstrType == I_("21"))
	{
		DStringA straVal(dstrBankAcctValue);
		if(dstrCurrency == I_("AUD"))
		{
			boost::RegEx rgVal("[0-9]{6,10}");
			bMatch = rgVal.Match(straVal.c_str());
		}
		else
		{
			boost::RegEx rgVal(".{6,10}");
			bMatch = rgVal.Match(straVal.c_str());
		}
	}
	return bMatch;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitution.cpp-arc  $
// 
//    Rev 1.9   Apr 03 2012 22:06:04   wp040039
// PETP0187485-Registartion Agent  Banking
// 
//    Rev 1.8   Jan 14 2007 14:08:20   porteanm
// Incident #779479 -- Add a new BankId (BL).
// 
//    Rev 1.7   Mar 21 2006 16:07:22   ZHANGCEL
// PET 2132 -- Include PayType "S" and "M" for PaymentInstructions.
// 
//    Rev 1.6   Nov 17 2004 15:02:14   PURDYECH
// PET910 - .NET Conversion:  Fixed compiler warning messages
// 
//    Rev 1.5   Nov 14 2004 14:40:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Nov 19 2003 18:14:12   popescu
// Field TransitNo should be set as required. Fixed a broken code while working on PET 809, FN 17
// 
//    Rev 1.3   Nov 19 2003 10:02:40   popescu
// CIBC PET 809, FN13
// 
//    Rev 1.2   Oct 27 2003 19:48:36   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.1   Oct 24 2003 17:19:32   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:08:42   popescu
// Initial revision.
 */