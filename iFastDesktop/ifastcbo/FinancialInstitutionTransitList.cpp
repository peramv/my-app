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
// ^FILE   : FinancialInstitutionTransitList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionTransitList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "financialinstitutiontransit.hpp"
#include "financialinstitutiontransitlist.hpp"
#include <ifastdataimpl\dse_dstc0100_req.hpp>
#include <ifastdataimpl\dse_dstc0100_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("FinancialInstitutionTransitList");
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
   extern I_CHAR * const BANK_TRANSIT;
   extern I_CHAR * const INSTITUTION_TRANSIT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   {ifds::NullFieldId, BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
FinancialInstitutionTransitList::FinancialInstitutionTransitList (BFAbstractCBO &parent, 
   bool noDataIsErrorCondition /*=false*/)
: MFCanBFCbo(parent),
_pRequestData(NULL),
_transitsCategoryList(NULL_STRING),
_category (NULL_STRING),
_type (NULL_STRING),
_instCode (NULL_STRING),
_noDataIsErrorCondition(noDataIsErrorCondition)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   setObjectAsList();
   _transitsCategoryList = 
      DString(FI_CATEGORY::BANK_TRANSIT) + I_(",") + 
      DString(FI_CATEGORY::INSTITUTION_TRANSIT);
}

//******************************************************************************
FinancialInstitutionTransitList::~FinancialInstitutionTransitList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//method returns 'All' financial institutions transits, regardless of the category
//******************************************************************************
SEVERITY FinancialInstitutionTransitList::initAll (
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initAll"));

   DString mgmtCoIdOut;
  
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, I_("A"));
   _pRequestData->setElementValue (ifds::InstCategory, 
      _transitsCategoryList);
   _pRequestData->setElementValue (ifds::BankType, NULL_STRING);
   _pRequestData->setElementValue (ifds::BankIdNum, NULL_STRING);
   _pRequestData->setElementValue (ifds::TransitNo, NULL_STRING);
   _pRequestData->setElementValue (ifds::InstName, NULL_STRING);   
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);

   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, 
      _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//method returns the financial institutions transits  that start with a given name, 
//regardless of the category and type
//******************************************************************************
SEVERITY FinancialInstitutionTransitList::initAllForName (
   const DString &dstrName,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initAllForName"));

   DString mgmtCoIdOut,
      name (dstrName);

   name.stripAll().upperCase();
   assert (!name.empty());
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, I_("S"));
   _pRequestData->setElementValue (ifds::InstCategory, 
      _transitsCategoryList);
   _pRequestData->setElementValue (ifds::BankType, NULL_STRING);
   _pRequestData->setElementValue (ifds::BankIdNum, NULL_STRING);
   _pRequestData->setElementValue (ifds::TransitNo, NULL_STRING);
   _pRequestData->setElementValue (ifds::InstName, name);   
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, 
      _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//method returns the transits that start with a given name, 
//within a list of categories or a category and a type 
//******************************************************************************
SEVERITY FinancialInstitutionTransitList::initForNameCategoryType (
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrName,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initForNameCategoryType"));
   DString mgmtCoIdOut,
      category (dstrCategory),
      type (dstrType),
      name (dstrName);

   name.stripAll().upperCase();
   category.stripAll().upperCase();
   type.stripAll().upperCase();
   _category = category;
   _type = type;
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, I_("S"));
   _pRequestData->setElementValue (ifds::InstCategory, category);
   _pRequestData->setElementValue (ifds::BankType, type);
   _pRequestData->setElementValue (ifds::BankIdNum, NULL_STRING);
   _pRequestData->setElementValue (ifds::TransitNo, NULL_STRING);
   _pRequestData->setElementValue (ifds::InstName, name);   
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//method returns the transits that start with a given name, 
//within a list of categories or a category, a type and an financial institution code
//******************************************************************************
SEVERITY FinancialInstitutionTransitList::initForNameCategoryTypeInstitutionCode (
   const DString &dstrCategory, 
   const DString &dstrType, 
   const DString &dstrInstCode, 
   const DString &dstrName,
   const DString &dstrTrack /*= I_("N")*/,
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initForNameCategoryType"));
   DString mgmtCoIdOut,
      category (dstrCategory),
      type (dstrType),
      instCode (dstrInstCode),
      name (dstrName);

   name.stripAll().upperCase();
   category.stripAll().upperCase();
   type.stripAll().upperCase();
   instCode.stripAll().upperCase();
   _category = category;
   _type = type;
   _instCode = instCode;
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, I_("S"));
   _pRequestData->setElementValue (ifds::InstCategory, category);
   _pRequestData->setElementValue (ifds::BankType, type);
   _pRequestData->setElementValue (ifds::BankIdNum, instCode);
   _pRequestData->setElementValue (ifds::TransitNo, NULL_STRING);
   _pRequestData->setElementValue (ifds::InstName, name);   
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//method returns the financial institutions transits for a given code, 
//within a list of categories or a category and a type 
//******************************************************************************
SEVERITY FinancialInstitutionTransitList::init(
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrInstCode,
   const DString &dstrTransitNo,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString mgmtCoIdOut,
      category (dstrCategory),
      type (dstrType),
      instCode (dstrInstCode),
      transitNo (dstrTransitNo);
   
   category.stripAll().upperCase();
   type.stripAll().upperCase();
   instCode.stripAll().upperCase();
   transitNo.stripAll().upperCase();
   _category = category;
   _type = type;
   _instCode = instCode;
   _pRequestData = new BFData (ifds::DSTC0100_REQ);
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::SearchType, I_("S"));
   _pRequestData->setElementValue (ifds::InstCategory, category);
   _pRequestData->setElementValue (ifds::BankType, type);
   _pRequestData->setElementValue (ifds::BankIdNum, instCode);
   _pRequestData->setElementValue (ifds::TransitNo, transitNo);
   _pRequestData->setElementValue (ifds::InstName, NULL_STRING);   
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::BANKLIST, *_pRequestData, 
      ifds::DSTC0100_VW, DSTCRequestor(getSecurity(), false, 
      _noDataIsErrorCondition));
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FinancialInstitutionTransitList::doCreateNewObject(BFCBO* &pBase, 
   DString &strKey, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   FinancialInstitutionTransit *pFinancialInstitutionTransit = 
      new FinancialInstitutionTransit (*this);

   if (pFinancialInstitutionTransit->init (_category, _type, 
      _instCode, idDataGroup) > WARNING)
   {
      ;
   }
   pBase = pFinancialInstitutionTransit;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionTransitList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   FinancialInstitutionTransit *pFinancialInstitutionTransit = 
      new FinancialInstitutionTransit (*this);

   if (pFinancialInstitutionTransit->init (data) > WARNING)
   {
      ;
   }
   pObjOut = pFinancialInstitutionTransit;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionTransitList::getMore()
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
void FinancialInstitutionTransitList::getStrKey (DString &strKey, const BFData *data)
{
   if (data) 
   {
      DString dstrBankType = data->getElementValue(ifds::BankIdType);
      DString dstrInstCode = data->getElementValue(ifds::BankIdNum);
      DString dstrTransitCode = data->getElementValue(ifds::FITransitCode);

      buildKey (strKey, dstrBankType, dstrInstCode, dstrTransitCode);
   }
   else
   {
      BFCBO::getStrKey(strKey, NULL);
   }
}

//******************************************************************************
void FinancialInstitutionTransitList::buildKey (DString &dstrKey, 
   const DString &dstrBankType,
   const DString &dstrInstCode,
   const DString &dstrTransitCode)
{
   DString bankType (dstrBankType);
   DString instCode (dstrInstCode);
   DString transitCode (dstrTransitCode);

   dstrKey = 
      I_(";BankType=") + bankType.stripAll().upperCase() + 
      I_(";InstCode=") + instCode.stripAll().upperCase() +
      I_(";TransitCode=") + transitCode.stripAll().upperCase();
}

//********************************************************************
SEVERITY FinancialInstitutionTransitList::checkDuplicate(
   const FinancialInstitutionTransit *pFinancialInstitutionTransitToCheck,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));
   DString bankIdNum,
      bankIdType,
      transitCode;

   //get the values for broker/branch/sales rep and payment for, to check against
   pFinancialInstitutionTransitToCheck->getField (ifds::BankIdNum, 
      bankIdNum, idDataGroup, false);
   pFinancialInstitutionTransitToCheck->getField (ifds::BankIdType, 
      bankIdType, idDataGroup, false);
   pFinancialInstitutionTransitToCheck->getField (ifds::FITransitCode, 
      transitCode, idDataGroup, false);
   
   bankIdNum.stripAll().upperCase();
   bankIdType.stripAll().upperCase();
   transitCode.stripAll().upperCase();
   
   bool hasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      FinancialInstitutionTransit *pFinancialInstitutionTransit = 
         dynamic_cast<FinancialInstitutionTransit*>(iter.getObject());

      if (pFinancialInstitutionTransit != pFinancialInstitutionTransitToCheck)
      {
         DString bankIdNum_, bankIdType_, transitCode_;

         pFinancialInstitutionTransit->getField(ifds::BankIdNum, 
            bankIdNum_, idDataGroup, false);
         pFinancialInstitutionTransit->getField(ifds::BankIdType, 
            bankIdType_, idDataGroup, false);
         pFinancialInstitutionTransit->getField (ifds::FITransitCode, 
            transitCode_, idDataGroup, false);
         bankIdNum_.stripAll().upperCase();
         bankIdType_.stripAll().upperCase();
         transitCode_.stripAll().upperCase();
         if (bankIdType == bankIdType_ && 
            bankIdNum == bankIdNum_ && 
            transitCode_ == transitCode)
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
      FinancialInstitutionTransitList financialInstitutionTransitList ((BFAbstractCBO&)(*this));

      //check duplicate, 
      if (financialInstitutionTransitList.init (_transitsCategoryList, 
         bankIdType, bankIdNum, transitCode) <= WARNING)
      {
         //we should get an exact match, 
         BFObjIter iter (financialInstitutionTransitList, idDataGroup);
         
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
                  FinancialInstitutionTransit *pDeletedFinancialInstitutionTransit = 
                     dynamic_cast<FinancialInstitutionTransit*>(iterInMemory.getObject());
                  DString deletedBankIdType, 
                     deletedBankIdNum,
                     deletedFITransitCode;

                  pDeletedFinancialInstitutionTransit->getField (ifds::BankIdType, 
                     deletedBankIdType, idDataGroup, false);
                  pDeletedFinancialInstitutionTransit->getField (ifds::BankIdNum, 
                     deletedBankIdNum, idDataGroup, false);
                  pDeletedFinancialInstitutionTransit->getField (ifds::FITransitCode, 
                     deletedFITransitCode, idDataGroup, false);
                  deletedBankIdType.stripAll().upperCase();
                  deletedBankIdNum.stripAll().upperCase();
                  deletedFITransitCode.stripAll().upperCase();
                  if (bankIdType == deletedBankIdType && 
                        bankIdNum == deletedBankIdNum &&
                        transitCode == deletedFITransitCode)
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionTransitList.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:41:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jan 12 2004 17:55:16   popescu
// PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
// 
//    Rev 1.0   Oct 24 2003 17:21:18   popescu
// Initial revision.
// 
//    Rev 1.0   Oct 04 2003 16:08:44   popescu
// Initial revision.
// 
 */