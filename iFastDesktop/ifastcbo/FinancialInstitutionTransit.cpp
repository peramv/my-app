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
//    ^FILE   : FinancialInstitutionTransit.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : October 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : FinancialInstitutionTransit
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0100_req.hpp>
#include <ifastdataimpl\dse_dstc0100_vw.hpp>
#include "financialinstitution.hpp"
#include "financialinstitutiontransit.hpp"
#include "financialinstitutiontransitlist.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_("FinancialInstitutionTransit");
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
   extern CLASS_IMPORT const BFTextFieldId TransitsCategory;
   extern CLASS_IMPORT const BFTextFieldId TransitPrimaryKey;   
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId InstCodeLabel;
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsCodeLabel;
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
   extern I_CHAR * const BANK;
   extern I_CHAR * const BANK_TRANSIT;
   extern I_CHAR * const INSTITUTION;
   extern I_CHAR * const INSTITUTION_TRANSIT;
   extern I_CHAR * const OTHER;
}

extern BF_OBJ_TYPE OBJ_TYPE_TRANSITS_LIST;

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                           //  Field DD Id            State Flags,      Group Flags 
   {ifds::FITransitCode,    BFCBO::REQUIRED,  0}, //part of the key
   {ifds::Name,             BFCBO::NONE,      0}, 
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
   {ifds::Telex,            BFCBO::NONE,      0}, 
   {ifds::FaxNumber,        BFCBO::NONE,      0}, 
   {ifds::PhoneNumber,      BFCBO::NONE,      0}, 
   {ifds::ShortName,        BFCBO::NONE,      0}, 
   {ifds::InstRole,         BFCBO::NONE,      0}, 
   {ifds::CodePage,         BFCBO::NONE,      0}, 
   {ifds::FIStatusCode,     BFCBO::NONE,      0}, 
   {ifds::BankIdType,       BFCBO::REQUIRED,  0}, //part of the key
   {ifds::InstCategory,     BFCBO::REQUIRED,  0},
   {ifds::InstCodeLabel,    BFCBO::NONE,      0}, 
   //cross edits
   {ifds::TransitPrimaryKey,  BFCBO::IMMEDIATE_VALIDATION, 0}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FinancialInstitutionTransit::FinancialInstitutionTransit (BFAbstractCBO &parent) : 
   MFCanBFCbo(parent),
_readOnlyTransitsCategory (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   addCrossEdit (ifds::TransitPrimaryKey, ifds::BankIdNum);
   addCrossEdit (ifds::TransitPrimaryKey, ifds::BankIdType);
   addCrossEdit (ifds::TransitPrimaryKey, ifds::FITransitCode);
}

//******************************************************************************
FinancialInstitutionTransit::~FinancialInstitutionTransit()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::init (const DString &dstrCategory,
   const DString &type, 
   const DString &code,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString category (dstrCategory);

   category.stripAll().upperCase();
   _readOnlyTransitsCategory = category != NULL_STRING;
   if (category == NULL_STRING)
   {
      category = FI_CATEGORY::BANK_TRANSIT;
   }
   setFieldNoValidate (ifds::InstCategory, category, idDataGroup, false);
   setFieldNoValidate (ifds::BankIdType, type, idDataGroup, false);
   setFieldNoValidate (ifds::BankIdNum, code, idDataGroup, false);
   
   commonInit (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject(const_cast<BFData&>(viewData), false, true);
   commonInit (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FinancialInstitutionTransit::doReset(const BFDataGroupId& idDataGroup)
{
   init (NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup);
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::commonInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   bool keyFieldsReadOnly = idDataGroup == BF::HOST && !isNew();
   
   setFieldReadOnly (ifds::InstCategory, idDataGroup, keyFieldsReadOnly || 
      _readOnlyTransitsCategory);
   setFieldReadOnly (ifds::BankIdNum, idDataGroup, keyFieldsReadOnly); 
   setFieldReadOnly (ifds::BankIdType, idDataGroup, keyFieldsReadOnly); 
   setFieldReadOnly (ifds::FITransitCode, idDataGroup, keyFieldsReadOnly);
   
   setFieldAllSubstituteValues(ifds::InstCategory, 
      idDataGroup, ifds::TransitsCategory);
   filterType (idDataGroup);
   assignInstCodeLabel (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FinancialInstitutionTransit::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   setFieldNoValidate (ifds::InstRole, EXTERNAL, idDataGroup, false);
   setFieldNoValidate (ifds::FIStatusCode, ACTIVE, idDataGroup, false);
   setFieldNoValidate (ifds::CodePage, JIS, idDataGroup, false);
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::doApplyRelatedChanges (const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::InstCategory)
   {
      DString category;

      getField (ifds::InstCategory, category, idDataGroup, false);
      filterType (idDataGroup);
      if (category == FI_CATEGORY::BANK_TRANSIT)
      {
         //try to set the default bank type, based on the system configuration            
         DString defaultBankType;

         getWorkSession().getOption (ifds::DefaultBankType, defaultBankType, 
            BF::HOST, false);
         if (!defaultBankType.empty())
         {
            if (FinancialInstitution::hasTransits (
               FinancialInstitution::getParentCategory (category),
               defaultBankType))
            {
               setFieldNoValidate (ifds::BankIdType, 
                  defaultBankType, idDataGroup, false);
            }
            else 
            {
               setFieldNoValidate (ifds::BankIdType, 
                  I_("03"), idDataGroup, false); //set Canadian as default
            }
         }
         setFieldReadOnly (ifds::BankIdType, idDataGroup, false);
      }
      else if (category == FI_CATEGORY::INSTITUTION_TRANSIT)
      {
         setFieldNoValidate (ifds::BankIdType, 
            OTHER, idDataGroup, false);
         setFieldReadOnly (ifds::BankIdType, idDataGroup, true);
      }
   }
   else if (idField == ifds::BankIdType)
   {
      DString category, 
         type;

      getField (ifds::InstCategory, category, idDataGroup, false);
      getField (ifds::BankIdType, type, idDataGroup, false);
      assignInstCodeLabel (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::doValidateField (const BFFieldId &idField, 
   const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::TransitPrimaryKey)
   {
      //check duplicate
      FinancialInstitutionTransitList *pFinancialInstitutionList = 
         dynamic_cast<FinancialInstitutionTransitList*>(getParent());
      
      pFinancialInstitutionList->checkDuplicate (this, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionTransit::assignInstCodeLabel (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("assignInstCodeLabel"));
      
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
SEVERITY FinancialInstitutionTransit::filterType (
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("filterType "));
   DString category,
      values,
      fValues;

   BFProperties *pProperties = getFieldProperties (
      ifds::BankIdType, 
      idDataGroup);
   
   pProperties->getAllSubstituteValues (values);

   I_CHAR *temp = const_cast<I_CHAR*> (values.c_str ());

   do
   {
      DString type;
      DString description;

      temp = parseIdiString (temp, type, description);

      if (FinancialInstitution::hasTransits (FI_CATEGORY::BANK, type) ||
         FinancialInstitution::hasTransits (FI_CATEGORY::INSTITUTION, type))
      {
         fValues += type + I_("=") + description + I_(";");
      }      
   } while (temp && temp != NULL_STRING && *temp);
   
   if (fValues != NULL_STRING)
   {
      setFieldAllSubstituteValues (ifds::BankIdType, idDataGroup, fValues);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionTransit.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:40:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 19 2003 10:02:44   popescu
// CIBC PET 809, FN13
// 
//    Rev 1.1   Oct 27 2003 19:48:46   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.0   Oct 24 2003 17:21:14   popescu
// Initial revision.
// 
//    Rev 1.0   Oct 04 2003 16:08:42   popescu
// Initial revision.
 */