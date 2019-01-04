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
// ^FILE   : FinancialInstitutionList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "financialinstitution.hpp"
#include "financialinstitutionlist.hpp"
#include <ifastdataimpl\dse_dstc0100_req.hpp>
#include <ifastdataimpl\dse_dstc0100_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("FinancialInstitutionList");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANKLIST;
}

namespace CND
{  // Conditions used
   extern const long ERR_DUPLICATE_RECORD;
}

namespace FI_CATEGORY
{
   extern I_CHAR * const BANK;
   extern I_CHAR * const INSTITUTION;
   extern I_CHAR * const OTHER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   {ifds::NullFieldId, BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
FinancialInstitutionList::FinancialInstitutionList (BFAbstractCBO &parent, 
   bool noDataIsErrorCondition /*=false*/)
: MFCanBFCbo(parent),
_pRequestData (NULL),
_institutionCategoryList (NULL_STRING),
_initCategory (NULL_STRING),
_initType (NULL_STRING),
_noDataIsErrorCondition (noDataIsErrorCondition)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   setObjectAsList();
   _institutionCategoryList = 
      DString(FI_CATEGORY::BANK) + I_(",") + 
      DString(FI_CATEGORY::INSTITUTION) + I_(",") + 
      DString(FI_CATEGORY::OTHER); 
}

//******************************************************************************
FinancialInstitutionList::~FinancialInstitutionList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//method returns 'A'll financial institutions, regardless of the category
//******************************************************************************
SEVERITY FinancialInstitutionList::initAll (
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initAll"));

   return initHelper (
      I_("A"), //search type
      NULL_STRING, //name
      _institutionCategoryList, //category
      NULL_STRING, //type
      NULL_STRING, //code
      dstrTrack, 
      dstrPageName);
}

//method returns the financial institutions that start with a given name, 
//regardless of the category and type
//******************************************************************************
SEVERITY FinancialInstitutionList::initAllForName (
   const DString &dstrName,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initAllForName"));

   return initHelper (
      I_("S"), //search type
      dstrName, //name
      _institutionCategoryList, //category
      NULL_STRING, //type
      NULL_STRING, //code
      dstrTrack, 
      dstrPageName);
}

//method returns the financial institutions for a given name, 
//within either a list of category or a category and a type
//******************************************************************************
SEVERITY FinancialInstitutionList::initForNameCategoryType (
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrName,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initForNameCategoryType"));
   return initHelper (
      I_("S"), //search type
      dstrName, //name
      dstrCategory, //category
      dstrType, //type
      NULL_STRING, //code
      dstrTrack, 
      dstrPageName);
}

//method returns the financial institutions for a given code, 
//within either a list of category or a category and a type
//******************************************************************************
SEVERITY FinancialInstitutionList::init(
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrCode,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _initCategory = dstrCategory;
   _initType = dstrType;
   return initHelper (
      I_("S"), //search type
      NULL_STRING, //name
      dstrCategory, //category
      dstrType, //type
      dstrCode, //code
      dstrTrack, 
      dstrPageName);
}

//******************************************************************************
SEVERITY FinancialInstitutionList::initHelper(
   const DString &dstrSearchType,
   const DString &dstrName,
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrCode,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString mgmtCoIdOut,
      name (dstrName),
      category (dstrCategory),
      type (dstrType),
      code (dstrCode);
   
   category.stripAll().upperCase();
   type.stripAll().upperCase();
   code.stripAll().upperCase();
   name.stripAll().upperCase();
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, dstrSearchType);
   _pRequestData->setElementValue (ifds::InstCategory, category);
   _pRequestData->setElementValue (ifds::BankType, type);
   _pRequestData->setElementValue (ifds::BankIdNum, code);
   _pRequestData->setElementValue (ifds::InstName, name);   
   _pRequestData->setElementValue (ifds::TransitNo, NULL_STRING);
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, 
      _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FinancialInstitutionList::doCreateNewObject(BFCBO* &pBase, 
   DString &strKey, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   FinancialInstitution *pFinancialInstitution = 
      new FinancialInstitution (*this);

   if (pFinancialInstitution->init (_initCategory, _initType, 
      idDataGroup) > WARNING)
   {
      ;
   }
   pBase = pFinancialInstitution;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   FinancialInstitution *pFinancialInstitution = 
      new FinancialInstitution (*this);

   if (pFinancialInstitution->init (data) > WARNING)
   {
      ;
   }
   pObjOut = pFinancialInstitution;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
         ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, 
         _noDataIsErrorCondition));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FinancialInstitutionList::getStrKey (DString &strKey, const BFData *data)
{
   if (data) 
   {
      DString dstrBankType    = data->getElementValue(ifds::BankIdType);
      DString dstrInstCode    = data->getElementValue(ifds::BankIdNum);
	  DString dstrTransitCode = data->getElementValue(ifds::FITransitCode);

      buildKey (strKey, dstrBankType, dstrInstCode,dstrTransitCode);
   }
   else
   {
      BFCBO::getStrKey(strKey, NULL);
   }
}

//******************************************************************************
void FinancialInstitutionList::buildKey (DString &dstrKey, 
   const DString &dstrBankType, const DString &dstrInstCode, const DString &dstrTransitCode)
{
   DString bankType (dstrBankType);
   DString instCode (dstrInstCode);
   DString transitCode (dstrTransitCode);

   dstrKey = 
      I_("BankType=") + bankType.stripAll().upperCase() + 
      I_(";InstCode=") + instCode.stripAll().upperCase() +
	  I_(";TransitCode=") + transitCode.stripAll().upperCase();
}

//********************************************************************
SEVERITY FinancialInstitutionList::checkDuplicate(
   const FinancialInstitution *pFinancialInstitutionToCheck,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));
   DString bankIdNum,
      bankIdType;

   //get the values for broker/branch/sales rep and payment for, to check against
   pFinancialInstitutionToCheck->getField (ifds::BankIdNum, 
      bankIdNum, idDataGroup, false);
   pFinancialInstitutionToCheck->getField (ifds::BankIdType, 
      bankIdType, idDataGroup, false);
   bankIdNum.stripAll().upperCase();
   bankIdType.stripAll().upperCase();
   
   bool hasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      FinancialInstitution *pFinancialInstitution = 
         dynamic_cast<FinancialInstitution*>(iter.getObject());

      if (pFinancialInstitution != pFinancialInstitutionToCheck)
      {
         DString bankIdNum_, bankIdType_;

         pFinancialInstitution->getField(ifds::BankIdNum, 
            bankIdNum_, idDataGroup, false);
         pFinancialInstitution->getField(ifds::BankIdType, 
            bankIdType_, idDataGroup, false);
         bankIdNum_.stripAll().upperCase();
         bankIdType_.stripAll().upperCase();
         if (bankIdType == bankIdType_ && bankIdNum == bankIdNum_)
         {
            hasDuplicate = true;
            break;
         }
      }
      ++iter;
   }
   //finally, if no duplicates in memory, check the back-end
   if (!hasDuplicate)
   {
      FinancialInstitutionList financialInstitutionList ((BFAbstractCBO&)(*this));

      //check duplicate, 
      if (financialInstitutionList.init (_institutionCategoryList, 
         bankIdType, bankIdNum) <= WARNING)
      {
         //we should get an exact match, 
         BFObjIter iter (financialInstitutionList, idDataGroup);
         
         hasDuplicate = iter.getNumberOfItemsInList() > 0;
         //but if we found a duplicate, this might have been already deleted 
         //in the memory
         if (hasDuplicate)
         { //check the memory again for possible deleted duplicates
            BFObjIter iterInMemory (*this, idDataGroup);

            while (!iterInMemory.end())
            {
               if (iterInMemory.getKey().getActivity() == 
                  OBJ_ACTIVITY_DELETED)
               {
                  FinancialInstitution *pDeletedFinancialInstitution = 
                     dynamic_cast<FinancialInstitution*>(iterInMemory.getObject());
                  DString deletedBankIdType, 
                     deletedBankIdNum;

                  pDeletedFinancialInstitution->getField(ifds::BankIdType, 
                     deletedBankIdType, idDataGroup, false);
                  pDeletedFinancialInstitution->getField(ifds::BankIdNum, 
                     deletedBankIdNum, idDataGroup, false);
                  deletedBankIdType.stripAll().upperCase();
                  deletedBankIdNum.stripAll().upperCase();
                  if (bankIdType == deletedBankIdType && 
                        bankIdNum == deletedBankIdNum)
                  {
                     hasDuplicate = false;
                     break;
                  }
               }
               ++iterInMemory;
            }
         }
      }
   }
   if (hasDuplicate)
   {
      ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionList.cpp-arc  $
// 
//    Rev 1.4   May 12 2005 11:54:52   porteanm
// Incident 265740 - Bank search.
// 
//    Rev 1.3   Nov 14 2004 14:40:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 27 2003 19:48:40   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.1   Oct 24 2003 17:19:38   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:08:44   popescu
// Initial revision.
// 
 */